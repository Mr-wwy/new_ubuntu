#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>

#include <QLabel>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QRubberBand>
#include <QMouseEvent>
#include <QFileDialog>
#include <QDesktopWidget>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    virtual bool eventFilter(QObject *o, QEvent *e);

private:
    void createWidgets();
    void createConnects();
    void createEventFilter();
    QString getSaveShotPixmap();

private slots:
    void grapWindowScreen();
    void saveShotPixmap();

private:
    Ui::Widget *ui;

    QLabel *fullScreenLabel;
    QLabel *shotScreenLabel;

    QAction *savePixmap;

    QRubberBand *rubberBand;

    QPoint origin;
    QPoint termination;

    QPixmap fullScreenPixmap;
    QPixmap shotScreenPixmap;


    bool leftMousePress;
};

#endif // WIDGET_H
