	var PoiRadar = {

		show: function showFn() {
			AR.radar.enabled = true;
		},

		hide: function hideFn() {
			AR.radar.enabled = false;
		},

		init: function initFn() {
			// set the back-ground image for the radar
			AR.radar.background = new AR.ImageResource("img/radar_bg.png");

			// set the north-indicator image for the radar (not necessary if you don't want to display a north-indicator)
			AR.radar.northIndicator.image = new AR.ImageResource("img/radar_north.png");
			AR.radar.positionX = 0.04;
			AR.radar.positionY = 0.06;
			AR.radar.width = 0.3;
			AR.radar.centerX = 0.5;
			AR.radar.centerY = 0.5;
			AR.radar.radius = 0.3;
			AR.radar.northIndicator.radius = 0.0;
			AR.radar.enabled = false;

			// set the onClick-trigger for the radar.
			AR.radar.onClick = PoiRadar.clickedRadar;
		},

		// you may define some custom action when user pressed radar, e.g. display distance, custom filtering etc.
		clickedRadar: function clickedRadarFn() {
			alert("Radar Clicked");
		}
	};

	// init radar to start loading required assets upfront. That way SimpleRadar.show() is way more responsive and displays radar almost immediately (all assets are already in place)
	PoiRadar.init();