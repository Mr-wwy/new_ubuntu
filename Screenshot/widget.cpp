#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/new/1"));
    createWidgets();
    createConnects();
    createEventFilter();
    //setWindowFlags(Qt::Desktop);//使窗口不可见
    //showMinimized();
    //resize(1,1);
    //setWindowFlags(Qt::CustomizeWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground,true);

    grapWindowScreen();
}

Widget::~Widget()
{
    delete ui;

    delete fullScreenLabel;
    delete shotScreenLabel;
}

bool Widget::eventFilter(QObject *o, QEvent *e)
{
    if (o != fullScreenLabel)
    {
        return Widget::eventFilter(o, e);
    }

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (e);


    if((mouseEvent->button() == Qt::LeftButton)
        && (mouseEvent->type() == QEvent::MouseButtonPress))
    {
        leftMousePress = true;

        origin = mouseEvent->pos();

        if (!rubberBand)
        {
            rubberBand = new QRubberBand(QRubberBand::Rectangle, fullScreenLabel);
        }

        rubberBand->setGeometry(QRect(origin,QSize()));
        rubberBand->show();

        return true;
    }


    if ((mouseEvent->type() == QEvent::MouseMove)
        && (leftMousePress))
    {
        if (rubberBand)
        {
            rubberBand->setGeometry(QRect(origin, mouseEvent->pos()).normalized());
        }

        return true;
    }


    if ((mouseEvent->button() == Qt::LeftButton)
        && (mouseEvent->type() == QEvent::MouseButtonRelease))
    {

        leftMousePress = false;

        if (rubberBand)
        {
            rubberBand->hide();
            termination = mouseEvent->pos();
            if(termination.x()==origin.x() || termination.y()==origin.y())
                return true;

            if(termination.x()<origin.x()){
                int tmp = origin.x();
                origin.setX(termination.x());
                termination.setX(tmp);
            }
            if(termination.y()<origin.y()){
                int tmp = origin.y();
                origin.setY(termination.y());
                termination.setY(tmp);
            }

            QRect rect = QRect(origin, termination);

            //获取鼠标选中区域的图片
            shotScreenPixmap = fullScreenPixmap.grabWidget(fullScreenLabel,
                                                           rect.x(),
                                                           rect.y(),
                                                           rect.width(),
                                                           rect.height());
            shotScreenLabel->setPixmap(shotScreenPixmap);
            this->setGeometry(origin.x(),origin.y(),shotScreenPixmap.width(),shotScreenPixmap.height());
            shotScreenLabel->setGeometry(0,0,this->width(),this->height());
            shotScreenLabel->setVisible(true);


            fullScreenLabel->hide();
        }

        return true;
    }

    return false;
}

void Widget::createWidgets()
{
    fullScreenLabel = new QLabel();
    shotScreenLabel = new QLabel(this);

    rubberBand = new QRubberBand(QRubberBand::Rectangle, fullScreenLabel);

    leftMousePress = false;

    savePixmap = new QAction(tr("save"), shotScreenLabel);

    shotScreenLabel->addAction(savePixmap);
    shotScreenLabel->setContextMenuPolicy(Qt::ActionsContextMenu);
    shotScreenLabel->setVisible(false);
}

void Widget::createConnects()
{
    connect(savePixmap, SIGNAL(triggered()), this, SLOT(saveShotPixmap()));

}

void Widget::createEventFilter()
{
    fullScreenLabel->installEventFilter(this); //事件过滤
}


QString Widget::getSaveShotPixmap()
{
    return QFileDialog::getSaveFileName(shotScreenLabel,
                                        tr("Open Image"),
                                        ".",
                                        tr("Image Files(*.JPG *.PNG)"));
}

void Widget::grapWindowScreen()
{
    if (!fullScreenLabel)
    {
        fullScreenLabel = new QLabel();
    }

    fullScreenPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    fullScreenLabel->setPixmap(fullScreenPixmap);

    fullScreenLabel->showFullScreen();
}

void Widget::saveShotPixmap()
{
    QString fileName = getSaveShotPixmap();

    if (!fileName.isNull())
    {
        shotScreenPixmap.save(fileName);
    }

}
