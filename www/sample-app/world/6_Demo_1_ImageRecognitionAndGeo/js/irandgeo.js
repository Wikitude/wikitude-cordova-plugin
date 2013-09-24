IrAndGeo = {};

IrAndGeo.markerNames = ['Union Circle', 'Eastminster', 'Small Ben', 'Silver Gate', 'Uptown', 'Downtown', 'Countryside', 'Outer Circle'];
IrAndGeo.stores = [];
IrAndGeo.markerAnimations = [];
IrAndGeo.error = false;
IrAndGeo.receivedLocation = false;

IrAndGeo.res = {};

IrAndGeo.setupScene = function(lat, lon, alt) {
    // create 8 random markers
    for (var i = 0; i < 8; i++) {
        var objLat = lat + ((Math.random() - 0.5) / 1000);
        var objLon = lon + ((Math.random() - 0.5) / 1000);
        IrAndGeo.createMarker(objLat, objLon, IrAndGeo.markerNames[i]);
    }

    // create appearing animation
    IrAndGeo.showMarkersAnimation = new AR.AnimationGroup('parallel', IrAndGeo.markerAnimations);
};

IrAndGeo.createMarker = function(lat, lon, name) {
    var loc = new AR.GeoLocation(lat, lon);
    var imageDrawable = new AR.ImageDrawable(IrAndGeo.res.marker, 2, {
        scale: 0.0,
        onClick: function() {
            alert("clicked");
        }
    });

    IrAndGeo.markerAnimations.push(new AR.PropertyAnimation(imageDrawable, 'scale', 0.0, 1.0, 1000, {
        type: AR.CONST.EASING_CURVE_TYPE.EASE_OUT_BOUNCE
    }));
    IrAndGeo.stores.push(new AR.GeoObject(loc, {
        drawables: {
            cam: imageDrawable
        },
        enabled: false
    }));
};

IrAndGeo.showStores = function() {
    // enable all geoobjects
    IrAndGeo.stores.forEach(function(x, idx) {
        x.enabled = true;
    });

    // nicely animate appearing of markers
    IrAndGeo.showMarkersAnimation.start();

    document.getElementById("messageElement").innerHTML = "Look around for stores nearby!";
    document.getElementById("messageElement").style.display = "block";
};

IrAndGeo.hideStores = function() {
    // disable all geoobjects and reset to 0 size
    IrAndGeo.stores.forEach(function(obj, idx) {
        obj.enabled = false;
        obj.drawables.cam[0].scale = 0.0;
    });
    document.getElementById("messageElement").style.display = "none";
};

IrAndGeo.showDeal = function() {
    IrAndGeo.hideStores();
    IrAndGeo.menuDrawables.forEach(function(obj, idx) {
        obj.enabled = false;
    });
    IrAndGeo.dealDrawable.enabled = true;
};

IrAndGeo.hideDeal = function() {
    IrAndGeo.dealDrawable.enabled = false;
    IrAndGeo.menuDrawables.forEach(function(obj, idx) {
        obj.enabled = true;
    });
};

IrAndGeo.showWeb = function() {
    IrAndGeo.hideStores();

    AR.context.openInBrowser("http://www.wikitude.com");
};

IrAndGeo.loadingStepDone = function() {
    if (!IrAndGeo.error && IrAndGeo.res.buttonStores.isLoaded() && IrAndGeo.res.buttonWeb.isLoaded() && IrAndGeo.res.buttonDeal.isLoaded() && IrAndGeo.res.marker.isLoaded() && IrAndGeo.receivedLocation && IrAndGeo.tracker && IrAndGeo.tracker.isLoaded()) {
        //everything is loaded
        document.getElementById("messageElement").style.display = "none";
    }
};

IrAndGeo.errorLoading = function() {
    document.getElementById("messageElement").innerHTML = "Unable to load image or tracker!";
    IrAndGeo.error = true;
};

IrAndGeo.initIr = function() {
    // Create the tracker to recognize the shop ad
    var trackerDataSetPath = "assets/ShopAd.wtc";
    IrAndGeo.tracker = new AR.Tracker(trackerDataSetPath, {
        onLoaded: IrAndGeo.loadingStepDone,
        onError: IrAndGeo.errorLoading
    });

    // Create drawables to display on the recognized image
    var buttonDeal = new AR.ImageDrawable(IrAndGeo.res.buttonDeal, 0.15, {
        onClick: IrAndGeo.showDeal,
        offsetX: 0.35,
        offsetY: -0.275
    });
    var buttonWeb = new AR.ImageDrawable(IrAndGeo.res.buttonWeb, 0.15, {
        onClick: IrAndGeo.showWeb,
        offsetX: 0.175,
        offsetY: -0.525
    });
    var buttonStores = new AR.ImageDrawable(IrAndGeo.res.buttonStores, 0.15, {
        onClick: IrAndGeo.showStores,
        offsetX: -0.1,
        offsetY: -0.275
    });

    IrAndGeo.menuDrawables = [buttonDeal, buttonWeb, buttonStores];
    IrAndGeo.dealDrawable = new AR.ImageDrawable(IrAndGeo.res.deal, 0.3, {
        enabled: false,
        onClick: IrAndGeo.hideDeal
    });

    // Create the object by defining the tracker, target name and its drawables
    var trackable2DObject = new AR.Trackable2DObject(IrAndGeo.tracker, "ShopAd", {
        drawables: {
            cam: [buttonDeal, buttonWeb, buttonStores, IrAndGeo.dealDrawable]
        }
    });

};

AR.context.onLocationChanged = function(latitude, longitude, altitude, accuracy) {
    AR.context.onLocationChanged = null;
    IrAndGeo.receivedLocation = true;
    IrAndGeo.setupScene(latitude, longitude, altitude);
    IrAndGeo.loadingStepDone();
};

IrAndGeo.res.marker = new AR.ImageResource("assets/YourShop_Marker.png", {
    onLoaded: IrAndGeo.loadingStepDone,
    onError: IrAndGeo.errorLoading
});
IrAndGeo.res.buttonWeb = new AR.ImageResource("assets/YourShop_OpenWebsite.png", {
    onLoaded: IrAndGeo.loadingStepDone,
    onError: IrAndGeo.errorLoading
});
IrAndGeo.res.buttonStores = new AR.ImageResource("assets/YourShop_FindShops.png", {
    onLoaded: IrAndGeo.loadingStepDone,
    onError: IrAndGeo.errorLoading
});
IrAndGeo.res.buttonDeal = new AR.ImageResource("assets/YourShop_GetADeal.png", {
    onLoaded: IrAndGeo.loadingStepDone,
    onError: IrAndGeo.errorLoading
});
IrAndGeo.res.deal = new AR.ImageResource("assets/YourShop_Deal.png", {
    onLoaded: IrAndGeo.loadingStepDone,
    onError: IrAndGeo.errorLoading
});

IrAndGeo.initIr();

IrAndGeo.loadingStepDone();