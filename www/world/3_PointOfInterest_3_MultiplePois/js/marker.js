function Marker(poiData) {

    this.poiData = poiData;

    this.isSelected = false;


    var markerLocation = new AR.GeoLocation(poiData.latitude, poiData.longitude, poiData.altitude);

    this.markerDrawable_idle = new AR.ImageDrawable(World.markerDrawable_idle, 2.5, {
        zOrder: 0,
        enabled: true,
        onClick: Marker.prototype.getOnClickTrigger(this)
    });

    this.markerDrawable_selected = new AR.ImageDrawable(World.markerDrawable_selected, 2.5, {
        zOrder: 0,
        enabled: false,
        onClick: Marker.prototype.getOnClickTrigger(this)
    });


    this.titleLabel = new AR.Label(poiData.title, 1, {
        zOrder: 1,
        offsetY: 0.55,
        style: {
            textColor: '#FFFFFF',
            fontStyle: AR.CONST.FONT_STYLE.BOLD
        }
    });

    this.descriptionLabel = new AR.Label(poiData.description, 0.8, {
        zOrder: 1,
        offsetY: -0.55,
        style: {
            textColor: '#FFFFFF'
        }
    });


    var markerObject = new AR.GeoObject(markerLocation, {
        drawables: {
            cam: [this.markerDrawable_idle, this.markerDrawable_selected, this.titleLabel, this.descriptionLabel]
        }
    });

    return this;
}

Marker.prototype.getOnClickTrigger = function(marker) {

    return function() {

        if (marker.isSelected) {

            Marker.prototype.setDeselected(marker);

        } else {

            World.onScreenClick(marker);

            Marker.prototype.setSelected(marker);
        }

        return true;
    };
};

Marker.prototype.setSelected = function(marker) {

    marker.isSelected = true;

    marker.markerDrawable_idle.enabled = false;
    marker.markerDrawable_selected.enabled = true;
};

Marker.prototype.setDeselected = function(marker) {

    marker.isSelected = false;

    marker.markerDrawable_idle.enabled = true;
    marker.markerDrawable_selected.enabled = false;
};