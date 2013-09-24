var World = {

    markerDrawable_idle: new AR.ImageResource("assets/marker_idle.png"),

    // New: a second image resource which represents a selected marker
    markerDrawable_selected: new AR.ImageResource("assets/marker_selected.png"),

    // New: a array holding a reference to all marker objects
    markerList: [],


    init: function initFn() {

        AR.context.onLocationChanged = World.onLocationChanged;

        // New: a custom callback which will be invoked when the user taps on an empty screen space
        AR.context.onScreenClick = World.onScreenClick;
    },

    onLocationChanged: function onLocationChangedFn(latitude, longitude, altitude, accuracy) {

        AR.context.onLocationChanged = null;

        // New: Markers are now created using the new operator.
        //      The marker definition is in `marker.js`.
        //      Title, description and location are supplied in the json compatible format
        var poiData = {
            "latitude": latitude + 0.01,
            "longitude": longitude - 0.01,
            "altitude": altitude,
            "title": "Marker 1",
            "description": "Description 1"
        };
        World.markerList.push(new Marker(poiData));

        poiData = {
            "latitude": latitude + 0.01,
            "longitude": longitude,
            "altitude": altitude,
            "title": "Marker 2",
            "description": "Description 2"
        };
        World.markerList.push(new Marker(poiData));

        poiData = {
            "latitude": latitude + 0.01,
            "longitude": longitude + 0.01,
            "altitude": altitude,
            "title": "Marker 3",
            "description": "Description 3"
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