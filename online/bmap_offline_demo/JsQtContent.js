var context;
// 初始化
function init()
{
    if (typeof qt != 'undefined')
    {
        new QWebChannel(qt.webChannelTransport, function(channel)
        {
            context = channel.objects.context;

           //方法二：接收qt发送的消息    通过消息
           context.sendToJSMsgSignal.connect(function (msg1, msg2) {
           alert("接收到Qt发送的消息2：" + msg1+" "+msg2);  
           map.clearOverlays(); 
           var new_point = new BMap.Point(msg1,msg2);
           var marker = new BMap.Marker(new_point);  // 创建标注
           map.addOverlay(marker);              // 将标注添加到地图中
           });

            
        }
        );
    }
    else
    {
        alert("qt对象获取失败！");
    }
}

// 方法一：接收qt发送的消息    直接调用函数
function recvMessage(msg1, msg2)
{
    alert("接收到Qt发送的消息1：" + msg1+" "+msg2);

    map.clearOverlays(); 
    var new_point = new BMap.Point(msg1,msg2);
    var marker = new BMap.Marker(new_point);  // 创建标注
    map.addOverlay(marker);              // 将标注添加到地图中

}


// 向qt发送消息
function sendToQtMessage(msg)
{
    if(typeof context == 'undefined')
    {
        alert("context对象获取失败！");
    }
    else
    {
        context.recvFromJsMsg(msg);
    }
}


init();

