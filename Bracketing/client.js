function count() {
	document.getElementById("partic").innerHTML="Number of Challenjours: " + 
	counting++;
	console.log('hi');
}

function getCounts() {
	var request = new XMLHttpRequest();
	request.addEventListener("load", showCounts);
	request.open("GET", "/clicks");
	request.send();
}

function showCounts() {
	var count = this.response;
	countDisplay.innerHTML = "Hello: " + count;
}
