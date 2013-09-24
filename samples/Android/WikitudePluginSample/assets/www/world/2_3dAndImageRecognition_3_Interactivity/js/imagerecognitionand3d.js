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
			onClick: this.toggleAnimateModel,
			scale: {
				x: 0.0,
				y: 0.0,
				z: 0.0
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

		// Appearing Animation
		this.appearingAnimation = this.createAppearingAnimation(this.modelCar, 0.045);

		// Rotation Animation
		this.rotationAnimation = new AR.PropertyAnimation(this.modelCar, "rotate.roll", -25, 335, 10000);

		var imgRotate = new AR.ImageResource("assets/rotateButton.png");
		var buttonRotate = new AR.ImageDrawable(imgRotate, 0.2, {
			offsetX: 0.25,
			offsetY: 0.4,
			onClick: this.toggleAnimateModel
		});

		var trackable = new AR.Trackable2DObject(this.tracker, "carAd", {
			drawables: {
				cam: [this.modelCar, buttonRotate]
			},
			onEnterFieldOfVision: this.appear
		});
	},

	loadingStep: function loadingStepFn() {
		if (!World.loaded && World.tracker.isLoaded() && World.modelCar.isLoaded()) {
			World.loaded = true;
			document.body.removeChild(document.getElementById('loadingMessage'));
		}
	},

	createAppearingAnimation: function createAppearingAnimationFn(model, scale) {
		var sx = new AR.PropertyAnimation(model, "scale.x", 0, scale, 1500, {
			type: AR.CONST.EASING_CURVE_TYPE.EASE_OUT_ELASTIC
		});
		var sy = new AR.PropertyAnimation(model, "scale.y", 0, scale, 1500, {
			type: AR.CONST.EASING_CURVE_TYPE.EASE_OUT_ELASTIC
		});
		var sz = new AR.PropertyAnimation(model, "scale.z", 0, scale, 1500, {
			type: AR.CONST.EASING_CURVE_TYPE.EASE_OUT_ELASTIC
		});

		return new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.PARALLEL, [sx, sy, sz]);
	},

	appear: function appearFn() {
		World.resetModel();
		World.appearingAnimation.start();
	},

	resetModel: function resetModelFn() {
		World.rotationAnimation.stop();
		World.rotating = false;
		World.modelCar.rotate.roll = -25;
	},

	toggleAnimateModel: function toggleAnimateModelFn() {
		if (!World.rotationAnimation.isRunning()) {
			if (!World.rotating) {
				World.rotationAnimation.start(-1);
				World.rotating = true;
			} else {
				World.rotationAnimation.resume();
			}
		} else {
			World.rotationAnimation.pause();
		}

		return false;
	}
};

World.init();