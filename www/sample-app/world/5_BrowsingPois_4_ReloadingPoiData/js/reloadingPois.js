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

	// location updates
	locationChanged: function locationChangedFn(lat, lon, alt, acc) {
		World.userLocation = {
			'latitude': lat,
			'longitude': lon,
			'altitude': alt,
			'accuracy': acc
		};
	},

	/* new in this sample: called when user presses reload button */
	clickedReload: function clickedReloadFn() {
		// you must use 'document.location = "architectsdk://...' to pass information from JS to native. this will cause HTTP error if you didn't registerUrlListener in architectView!
		document.location = "architectsdk://button?type=refresh";
	}

};

/* forward locationChanges to custom function */
AR.context.onLocationChanged = World.locationChanged;