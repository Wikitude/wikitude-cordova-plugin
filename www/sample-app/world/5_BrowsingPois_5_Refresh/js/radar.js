	var PoiRadar = {

		hide: function hideFn() {
			AR.radar.enabled = false;
		},

		show: function initFn() {
			// set the back-ground image for the radar
			AR.radar.background = new AR.ImageResource("assets/radar_bg.png");

			// set the north-indicator image for the radar (not necessary if you don't want to display a north-indicator)
			AR.radar.northIndicator.image = new AR.ImageResource("assets/radar_north.png");

			AR.radar.width = 0.3;
			AR.radar.centerX = 0.5;
			AR.radar.centerY = 0.5;
			AR.radar.radius = 0.3;
			AR.radar.northIndicator.radius = 0.0;
			AR.radar.enabled = true;
			AR.radar.horizontalAnchor = AR.CONST.HORIZONTAL_ANCHOR.RIGHT;
			AR.radar.offsetX = 0.01;
			AR.radar.offsetY = 0.1;
			// set the onClick-trigger for the radar.
			AR.radar.onClick = PoiRadar.clickedRadar;
		},

		// you may define some custom action when user pressed radar, e.g. display distance, custom filtering etc.
		clickedRadar: function clickedRadarFn() {
			// alert("Radar Clicked");
		},

		setMaxDistance: function setMaxDistanceFn(maxDistanceMeters) {
			AR.radar.maxDistance = maxDistanceMeters;
		}
	};