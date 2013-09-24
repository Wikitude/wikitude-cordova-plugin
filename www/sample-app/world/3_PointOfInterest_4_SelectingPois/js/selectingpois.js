var World = {

	markerDrawable_idle: new AR.ImageResource("assets/marker_idle.png"),
	markerDrawable_selected: new AR.ImageResource("assets/marker_selected.png"),

	// New: Direction Indicator image resource
	markerDrawable_directionIndicator: new AR.ImageResource("assets/indi.png"),

	markerList: [],


	init: function initFn() {
		AR.context.onLocationChanged = World.onLocationChanged;
		AR.context.onScreenClick = World.onScreenClick;
	},

	onLocationChanged: function onLocationChangedFn(latitude, longitude, altitude, accuracy) {

		AR.context.onLocationChanged = null;

		var poiData = {
			"latitude": latitude + 0.01,
			"longitude": longitude - 0.01,
			"altitude": altitude,
			"title": "Marker 1",
			"description": "This is marker 1"
		};
		World.markerList.push(new Marker(poiData));

		poiData = {
			"latitude": latitude + 0.01,
			"longitude": longitude,
			"altitude": altitude,
			"title": "Marker 2",
			"description": "This is marker 2"
		};
		World.markerList.push(new Marker(poiData));

		poiData = {
			"latitude": latitude + 0.01,
			"longitude": longitude + 0.01,
			"altitude": altitude,
			"title": "Marker 3",
			"description": "This is marker 3"
		};
		World.markerList.push(new Marker(poiData));
	},

	onScreenClick: function onScreenClickFn() {

		for (var i = World.markerList.length - 1; i >= 0; i--) {
			if (World.markerList[i].isSelected) {
				World.markerList[i].setDeselected(World.markerList[i]);
			}
		}
	}
};

World.init();