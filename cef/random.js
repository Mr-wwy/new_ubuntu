function getrandom(min, max){
	document.getElementById('demo').innerHTML=Math.floor(Math.random() * (max-min)) + min;
}

