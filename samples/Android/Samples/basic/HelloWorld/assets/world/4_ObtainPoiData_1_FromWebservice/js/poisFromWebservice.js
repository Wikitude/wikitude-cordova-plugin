// holds server information
var ServerInformation = {
	POIDATA_SERVER: "http://example.wikitude.com/GetSamplePois/",
	POIDATA_SERVER_ARG_LAT: "lat",
	POIDATA_SERVER_ARG_LON: "lon",
	POIDATA_SERVER_ARG_NR_POIS: "nrPois"
};


var World = {

	markerDrawable_idle: null,
	markerDrawable_selected: null,
	markerDrawable_directionIndicator: null,

	markerList: [],

	// called to inject new POI data
	loadPoisFromJsonData: function loadPoisFromJsonDataFn(poiData) {

		AR.context.destroyAll();

		World.markerDrawable_idle = new AR.ImageResource("assets/marker_idle.png"),
		World.markerDrawable_selected = new AR.ImageResource("assets/marker_selected.png"),
		World.markerDrawable_directionIndicator = new AR.ImageResource("assets/indi.png"),

		document.getElementById("statusElement").innerHTML = 'Loading JSON objects';

		for (var i = 0; i < poiData.length; i++) {

			var singlePoi = {
				"latitude": parseFloat(poiData[i].latitude),
				"longitude": parseFloat(poiData[i].longitude),
				"altitude": parseFloat(poiData[i].altitude),
				"title": poiData[i].name,
				"description": poiData[i].description
			};

			World.markerList.push(new Marker(singlePoi));
		}

		document.getElementById("statusElement").innerHTML = 'JSON objects loaded properly';

	},

	//  user's latest known location, accessible via userLocation.latitude, userLocation.longitude, userLocation.altitude
	userLocation: null,

	// you may request new data from server periodically, however: in this sample data is only requested once
	alreadyRequestedData: false,

	// location updates
	locationChanged: function locationChangedFn(lat, lon, alt, acc) {
		World.userLocation = {
			'latitude': lat,
			'longitude': lon,
			'altitude': alt,
			'accuracy': acc
		};

		/* NEW in this sample: request data from server */
		if (!World.alreadyRequestedData) {
			World.requestDataFromServer(lat, lon);
			World.alreadyRequestedData = true;
		}
	},

	// request POI data
	requestDataFromServer: function requestDataFromServerFn(lat, lon) {
		var serverUrl = ServerInformation.POIDATA_SERVER + "?" + ServerInformation.POIDATA_SERVER_ARG_LAT + "=" + lat + "&" + ServerInformation.POIDATA_SERVER_ARG_LON + "=" + lon + "&" + ServerInformation.POIDATA_SERVER_ARG_NR_POIS + "=20";
		var jqxhr = $.getJSON(serverUrl, function(data) {
			World.loadPoisFromJsonData(data);
		})
			.error(function(err) {
			alert("JSON error occured! " + err.message);
		})
			.complete(function() {});
	}

};

/* forward locationChanges to custom function */
AR.context.onLocationChanged = World.locationChanged;