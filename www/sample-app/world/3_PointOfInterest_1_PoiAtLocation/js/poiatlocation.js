var World = {

	markerDrawable: new AR.ImageResource("assets/marker.png"),

	init: function initFn() {

		AR.context.onLocationChanged = World.onLocationChanged;
	},

	onLocationChanged: function onLocationChangedFn(latitude, longitude, altitude, accuracy) {

		AR.context.onLocationChanged = null;

		World.createMarkerAtLocation(latitude + 0.01, longitude - 0.0005, altitude - 0.06);
	},

	createMarkerAtLocation: function createMarkerAtLocationFn(latitude, longitude, altitude) {

		var markerLocation = new AR.GeoLocation(latitude, longitude, altitude);
		var markerDrawable = new AR.ImageDrawable(World.markerDrawable, 1.5);
		var markerObject = new AR.GeoObject(markerLocation, {
			drawables: {
				cam: markerDrawable
			}
		});
	}
};

World.init();