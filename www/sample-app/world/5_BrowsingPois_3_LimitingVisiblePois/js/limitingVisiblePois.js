var World = {

	markerDrawable_idle: new AR.ImageResource("assets/marker_idle.png"),
	markerDrawable_selected: new AR.ImageResource("assets/marker_selected.png"),
	markerDrawable_directionIndicator: new AR.ImageResource("assets/indi.png"),

	markerList: [],

	// called to inject new POI data
	loadPoisFromJsonData: function loadPoisFromJsonDataFn(poiData) {

		PoiRadar.show();

		document.getElementById("statusElement").innerHTML = 'Loading JSON objects';

		var poiImage = new AR.ImageResource("img/marker.png", {
			onError: World.errorLoadingImage
		});

		// TODO: call single POI-creation statement instead
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

	// called from slider.js every time the slider value changes
	onSliderChanged: function onSliderChangedFn(value) {
		if (value > 0) {
			var valueMeters = value * 1000;
			PoiRadar.setMaxDistance(valueMeters);
			AR.context.scene.cullingDistance = valueMeters;
		}
	}

};

// forward locationChanges to custom function
AR.context.onLocationChanged = World.locationChanged;