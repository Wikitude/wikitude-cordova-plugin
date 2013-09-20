var World = {

	markerDrawable: new AR.ImageResource("assets/marker.png"),

	init: function initFn() {

		AR.context.onLocationChanged = World.onLocationChanged;
	},

	onLocationChanged: function onLocationChangedFn(latitude, longitude, altitude, accuracy) {

		AR.context.onLocationChanged = null;

		World.createMarkerAtLocation(latitude + 0.01, longitude - 0.0005, altitude - 0.06, 'Titel', 'Description');
	},

	// New: Two additional parameters: title, description
	createMarkerAtLocation: function createMarkerAtLocationFn(latitude, longitude, altitude, title, description) {

		var markerLocation = new AR.GeoLocation(latitude, longitude, altitude);
		var markerDrawable = new AR.ImageDrawable(World.markerDrawable, 2.5, {

			// New: Rendering order (zOrder)
			zOrder: 0
		});

		// New: Title Label with options who define rendering order, offsets and label style
		var titleLabel = new AR.Label(title, 1, {
			zOrder: 1,
			offsetY: 0.55,
			style: {
				textColor: '#FFFFFF',
				fontStyle: AR.CONST.FONT_STYLE.BOLD
			}
		});

		// New: Description Label (same new options as for the title label)
		var descriptionLable = new AR.Label(description, 0.8, {
			zOrder: 1,
			offsetY: -0.55,
			style: {
				textColor: '#FFFFFF'
			}
		});

		var markerObject = new AR.GeoObject(markerLocation, {
			drawables: {

				// New: two more cam drawables: title and description label
				cam: [markerDrawable, titleLabel, descriptionLable]
			}
		});
	}
};

World.init();