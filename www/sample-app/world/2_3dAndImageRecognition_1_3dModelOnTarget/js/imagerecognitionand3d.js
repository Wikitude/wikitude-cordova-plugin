var World = {
	loaded: false,
	rotating: false,

	init: function initFn() {
		this.createOverlays();
	},

	createOverlays: function createOverlaysFn() {
		// Initialize Tracker
		this.tracker = new AR.Tracker("assets/tracker.wtc", {
			onLoaded: this.loadingStep
		});

		this.modelCar = new AR.Model("assets/car.wt3", {
			onLoaded: this.loadingStep,
			scale: {
				x: 0.045,
				y: 0.045,
				z: 0.045
			},
			translate: {
				x: 0.0,
				y: 0.05,
				z: 0.0
			},
			rotate: {
				roll: -25
			}
		});

		var trackable = new AR.Trackable2DObject(this.tracker, "carAd", {
			drawables: {
				cam: [this.modelCar]
			},
			onEnterFieldOfVision: this.appear
		});
	},

	loadingStep: function loadingStepFn() {
		if (!World.loaded && World.tracker.isLoaded() && World.modelCar.isLoaded()) {
			World.loaded = true;
			document.body.removeChild(document.getElementById('loadingMessage'));
		}
	}
};

World.init();