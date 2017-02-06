// Put your zillow.com API key here

var username = "????";
var request = new XMLHttpRequest();


//initMap() which initiates map to a location
function initMap() {

	//initialize map
	
	//Initialize a mouse click event on map which then calls reversegeocode function
 
}



// Reserse Geocoding 
function reversegeocode() {

  //get the latitude and longitude from the mouse click and get the address.
  //call geoname api asynchronously with latitude and longitude 
  
}// end of geocodeLatLng()



function displayResult () {
    if (request.readyState == 4) {
        var xml = request.responseXML.documentElement;
        var temperature = xml.getElementsByTagName("temperature");
	document.getElementById("output").innerHTML = value;
    }
}

function sendRequest () {
    request.onreadystatechange = displayResult;
    var lat = "";
    var lng = "";
    request.open("GET"," http://api.geonames.org/findNearByWeatherXML?lat="+lat+"&lng="+lng+"&username="+username);
    request.withCredentials = "true";
    request.send(null);
}
