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

		/* Load data from local file, means loading data defined in local JS as global variable, holding POI data as JSON object */
		if (!World.alreadyRequestedData) {
			World.requestDataFromLocal(lat, lon);
			World.alreadyRequestedData = true;
		}
	},

	// request POI data
	requestDataFromLocal: function requestDataFromLocalFn(lat, lon) {

		// comment this line to NOT modify JSON lat/lon values
		var poisNearby = Helper.bringPlacesToUser(myJsonData, World.userLocation);
		World.loadPoisFromJsonData(poisNearby);
	}

};

var Helper = {
	bringPlacesToUser: function bringPlacesToUserFn(poiData, centerPoint) {
		for (var i = 0; i < poiData.length; i++) {
			poiData[i].latitude = centerPoint.latitude + (Math.random() / 5 - 0.1);
			poiData[i].longitude = centerPoint.longitude + (Math.random() / 5 - 0.1);
		}
		return poiData;
	}
}

/* forward locationChanges to custom function */
AR.context.onLocationChanged = World.locationChanged;