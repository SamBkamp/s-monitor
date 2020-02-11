var splitInfo;

function loadDoc() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
	  splitInfo = this.responseText.split("\n");
	  document.getElementById("info1").innerHTML = splitInfo[0];
	  document.getElementById("info2").innerHTML = splitInfo[1];
    }
  };
  xhttp.open("GET", "info.txt", true);
  xhttp.send();
}

setInterval(loadDoc, 1000);
