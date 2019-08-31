
// 接收qt发送的消息
function recvMessage(msg)
{
    //alert("接收到Qt发送的消息：" + msg);

	//json格式的数据解析
	var obj = eval('(' + msg + ')');

	document.getElementById('demo_id').innerHTML=obj[0].id;
	document.getElementById('demo_log').innerHTML=obj[0].longitude;
	document.getElementById('demo_lat').innerHTML=obj[0].latitude;
}


// file:///home/abc/test/cef/cef测试demo.html
// 网页发送消息给qt
function onBtnSendMsg()
{
	var data = {"id":document.getElementById('demo_id').innerHTML,
			   "longitude":document.getElementById('demo_log').innerHTML,
			   "latitude":document.getElementById('demo_lat').innerHTML};
	var msg = [document.getElementById('demo_id').innerHTML,
			   document.getElementById('demo_log').innerHTML,
			   document.getElementById('demo_lat').innerHTML];

    var cmd = document.getElementById("待发送消息").value;
    //window.getWebMessage(msg[0]+cmd,msg[1]+cmd,msg[2]+cmd);
	window.getWebMessage(msg);
	//window.getWebMessage(data);


	//alert(window.myArray[0]) //获取qt数组数据
	//alert(window.myObject.longitude); //获取qt对象数据
	
}
