var World = {

	markerDrawable_idle: new AR.ImageResource("assets/marker_idle.png"),
	markerDrawable_selected: new AR.ImageResource("assets/marker_selected.png"),
	markerDrawable_directionIndicator: new AR.ImageResource("assets/indi.png"),


	markerList: [],

	// called to inject new POI data
	loadPoisFromJsonData: function loadPoisFromJsonDataFn(poiData) {

		// show radar
		PoiRadar.show();

		document.getElementById("statusElement").innerHTML = 'Loading JSON objects';

		var poiImage = new AR.ImageResource("img/marker.png", {
			onError: World.errorLoadingImage
		});


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
	}

};

// forward locationChanges to custom function
AR.context.onLocationChanged = World.locationChanged;