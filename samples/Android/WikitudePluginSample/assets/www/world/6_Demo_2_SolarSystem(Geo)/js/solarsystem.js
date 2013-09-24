var Solar = {
    planetsInfo: null,

    init: function() {
        var distanceFactor = 580.2;

        /* null means: use relative to user, sun is NORTH to the user */
        var locationSun = new AR.RelativeLocation(null, 25000, 0, 5000);

        /* sizes & distances are far away from real values! used these scalings to be able to show within user range */
        var sizeFactor = 0.5;
        var sizeEarth = 12.8*25;

        /* every object in space has a name, location and a circle (drawable) */
        var sunImg = new AR.ImageResource("assets/Sun-icon.png");
        var mercuryImg = new AR.ImageResource("assets/Mercury-icon.png");
        var venusImg = new AR.ImageResource("assets/Venus-icon.png");
        var earthImg = new AR.ImageResource("assets/Earth-icon.png");
        var marsImg = new AR.ImageResource("assets/Mars-icon.png");
        var jupiterImg = new AR.ImageResource("assets/Jupiter-icon.png");
        var saturnImg = new AR.ImageResource("assets/Saturn-icon.png");
        var uranusImg = new AR.ImageResource("assets/Uranus-icon.png");
        var neptuneImg = new AR.ImageResource("assets/Neptune-icon.png");
        var plutoImg = new AR.ImageResource("assets/Pluto-icon.png");
        var indicatorImg = new AR.ImageResource("assets/indi.png");

        var sunSize =  ( ( (109*sizeEarth)/sizeEarth ) *0.3) *sizeFactor;
        var mercurySize = (4.9*sizeEarth / sizeEarth) *sizeFactor;
        var venusSize = (12.0*sizeEarth / sizeEarth) *sizeFactor;
        var earthSize = (10*sizeEarth / sizeEarth) *sizeFactor;
        var marsSize = (6.8*sizeEarth / sizeEarth) *sizeFactor;
        var jupiterSize = (14.4*sizeEarth / sizeEarth) *sizeFactor;
        var saturnSize = (12.0*sizeEarth / sizeEarth) *sizeFactor;
        var uranusSize = (5.20*sizeEarth / sizeEarth) *sizeFactor;
        var neptunSize = (5.0*sizeEarth / sizeEarth) *sizeFactor;
        var plutoSize = (0.23*sizeEarth / sizeEarth) *sizeFactor;

        var sun = {name: "Sun",
                        distance: 0,
                        location: locationSun,
                        imgDrawable: new AR.ImageDrawable( sunImg, sunSize),
                        size: sunSize,
                        description: "The Sun is the star at the center of the Solar System. It is almost perfectly spherical and consists of hot plasma interwoven with magnetic fields.",
                        mass: "2&nbsp;10<sup>30</sup>&nbsp;kg",
                        diameter: "1,392,684&nbsp;km"};

        var mercury = {name: "Mercury",
                        distance: 3.9*distanceFactor,
                        location: new AR.RelativeLocation(locationSun, 0, -3.9*distanceFactor, 0),
                        imgDrawable: new AR.ImageDrawable(mercuryImg, mercurySize),
                        size: mercurySize,
                        description: "Is the innermost planet in the Solar System. It is also the smallest, and its orbit is the most eccentric (that is, the least perfectly circular).",
                        mass: "3.3&nbsp;10<sup>23</sup>&nbsp;kg",
                        diameter: "4,880&nbsp;km"};

        var venus = {name: "Venus",
                        distance: 7.2*distanceFactor,
                        location: new AR.RelativeLocation(locationSun, 0, -7.2*distanceFactor, 0),
                        imgDrawable: new AR.ImageDrawable(venusImg, venusSize),
                        size: venusSize,
                        description: "Is named after the Roman goddess of love and beauty. After the Moon, it is the brightest natural object in the night sky, bright enough to cast shadows.",
                        mass: "4.9&nbsp;10<sup>24</sup>",
                        diameter: "12,092&nbsp;km"};

        var earth = {name: "Earth",
                        distance: 10*distanceFactor,
                        location: new AR.RelativeLocation(locationSun, 0, -10*distanceFactor, 0),
                        imgDrawable: new AR.ImageDrawable(earthImg, earthSize),
                        size: earthSize,
                        description: "Is the third planet from the Sun, and the densest and fifth-largest of the eight planets in the Solar System. It is sometimes referred to as the world, the Blue Planet, Terra.",
                        mass: " 6&nbsp;10<sup>24</sup>&nbsp;kg",
                        diameter: "12,742&nbsp;km"};

        var mars = {name: "Mars",
                        distance: 15*distanceFactor,
                        location: new AR.RelativeLocation(locationSun, 0, -15*distanceFactor, 0),
                        imgDrawable: new AR.ImageDrawable(marsImg, marsSize),
                        size: marsSize,
                        description: "Is named after the Roman god of war, it is often described as the &quot;Red Planet&quot;, as the iron oxide prevalent on its surface gives it a reddish appearance.",
                        mass: "6.4&nbsp;10<sup>23</sup>&nbsp;kg",
                        diameter: "6794&nbsp;km"};

        var jupiter = {name: "Jupiter",
                        distance: 50.2*distanceFactor*0.35,
                        location: new AR.RelativeLocation(locationSun, 0, -50.2*distanceFactor*0.35, 0),
                        imgDrawable: new AR.ImageDrawable(jupiterImg, jupiterSize),
                        size: jupiterSize,
                        description: "Is the largest planet within the Solar System. It is a gas giant with mass one-thousandth that of the Sun but is two and a half times the mass of all the other planets in our Solar System combined.",
                        mass: "1.9&nbsp;10<sup>27</sup>&nbsp;kg",
                        diameter: "142,984&nbsp;km"};

        var saturn = {name: "Saturn",
                        distance: 95.3*distanceFactor*0.2,
                        location: new AR.RelativeLocation(locationSun, 0, -95.3*distanceFactor*0.2, 0),
                        imgDrawable: new AR.ImageDrawable(saturnImg, saturnSize),
                        size: saturnSize,
                        description: "Is the second largest planet in the Solar System, after Jupiter. Named after the Roman god Saturn. Saturn is a gas giant with an average radius about nine times that of Earth.",
                        mass: "5.7&nbsp;10<sup>26</sup>&nbsp;kg",
                        diameter: "25,000&nbsp;km"};

        var uranus = {name: "Uranus",
                        distance: 192*distanceFactor*0.1,
                        location: new AR.RelativeLocation(locationSun, 0, -192*distanceFactor*0.1, 0),
                        imgDrawable: new AR.ImageDrawable(uranusImg, uranusSize),
                        size: uranusSize,
                        description: "It has the third-largest planetary radius and fourth-largest planetary mass in the Solar System. It is named after the ancient Greek deity of the sky Uranus.",
                        mass: "8.7&nbsp;10<sup>25</sup>&nbsp;kg",
                        diameter: "51,118&nbsp;km"};

        var neptun = {name: "Neptune",
                        distance: 301*distanceFactor*0.07,
                        location: new AR.RelativeLocation(locationSun, 0, -301*distanceFactor*0.07, 0),
                        imgDrawable: new AR.ImageDrawable(neptuneImg, neptunSize),
                        size: neptunSize,
                        description: "Is the farthest planet from the Sun in the Solar System. It is the fourth-largest planet by diameter and the third-largest by mass.",
                        mass: "1&nbsp;10 <sup>26</sup>&nbsp;kg",
                        diameter: "49,532&nbsp;km"};

        var pluto = {name: "Pluto",
                        distance: 394*distanceFactor*0.063,
                        location: new AR.RelativeLocation(locationSun, 0, -394*distanceFactor*0.063, 0),
                        imgDrawable: new AR.ImageDrawable(plutoImg, plutoSize),
                        size: plutoSize,
                        description: "Originally classified as the ninth planet from the Sun, Pluto was recategorized as a dwarf planet and plutoid owing to the discovery that it is only one of several large bodies within the Kuiper belt.",
                        mass: "1.3&nbsp;10<sup>22</sup>&nbsp;kg",
                        diameter: "2,306&nbsp;km"};


        /* put sun, planets (and pluto) in an array */
        this.planetsInfo = [sun, mercury, venus , earth, mars, jupiter, saturn, uranus, neptun,pluto];

        /* create helper array to create goeObjects out of given information */
        var planetsGeoObjects = [];
        for (var i = 0; i < this.planetsInfo.length; i++) {

            /* show name of object below*/
            var label = new AR.Label(this.planetsInfo[i].name, 3, {
                offsetY : -this.planetsInfo[i].size/2,
                verticalAnchor : AR.CONST.VERTICAL_ANCHOR.TOP,
                opacity : 0.9,
                zOrder: 1, style : {textColor : '#FFFFFF', backgroundColor : '#00000005'}
                });

            /* drawable in cam of object -> image and label */
            var drawables = [];
            drawables[0] = this.planetsInfo[i].imgDrawable;
            drawables[1] = label;

            /* Create objects in AR*/
            planetsGeoObjects[i] = new AR.GeoObject(this.planetsInfo[i].location, { drawables: { cam: drawables }, onClick: this.planetClicked(this.planetsInfo[i]) } );
            if (i > 0) {
                this.animate(this.planetsInfo[i]);
            } else {
                var sunHackAnim = new AR.PropertyAnimation(this.planetsInfo[i].location, 'northing', 10000, 10000, 1000, {type:AR.CONST.EASING_CURVE_TYPE.EASE_IN_SINE});
                sunHackAnim.start(-1);
            }
        }

        // Add indicator to sun
        var imageDrawable = new AR.ImageDrawable(indicatorImg, 0.1, { verticalAnchor: AR.CONST.VERTICAL_ANCHOR.TOP });
        planetsGeoObjects[0].drawables.addIndicatorDrawable(imageDrawable);
    },

    animate: function(planet) {
        var relLocation = planet.location;
        var distance = planet.distance;
        var roundingTime = distance*2*2;

        var northSouthAnimation1 = new AR.PropertyAnimation(relLocation, 'northing', distance*1, distance*0, roundingTime/4, {type:AR.CONST.EASING_CURVE_TYPE.EASE_IN_SINE});
        var eastWestAnimation1 = new AR.PropertyAnimation(relLocation, 'easting', distance*0, distance*1, roundingTime/4 , {type:AR.CONST.EASING_CURVE_TYPE.EASE_OUT_SINE});

        var northSouthAnimation2 = new AR.PropertyAnimation(relLocation, 'northing', distance*0, distance*-1, roundingTime/4, {type:AR.CONST.EASING_CURVE_TYPE.EASE_OUT_SINE});
        var eastWestAnimation2 = new AR.PropertyAnimation(relLocation, 'easting', distance*1, distance*0, roundingTime/4 , {type:AR.CONST.EASING_CURVE_TYPE.EASE_IN_SINE});

        var northSouthAnimation3 = new AR.PropertyAnimation(relLocation, 'northing', distance*-1, distance*0, roundingTime/4, {type:AR.CONST.EASING_CURVE_TYPE.EASE_IN_SINE});
        var eastWestAnimation3 = new AR.PropertyAnimation(relLocation, 'easting', distance*0, distance*-1, roundingTime/4 , {type:AR.CONST.EASING_CURVE_TYPE.EASE_OUT_SINE});

        var northSouthAnimation4 = new AR.PropertyAnimation(relLocation, 'northing', distance*0, distance*1, roundingTime/4, {type:AR.CONST.EASING_CURVE_TYPE.EASE_OUT_SINE});
        var eastWestAnimation4 = new AR.PropertyAnimation(relLocation, 'easting', distance*-1, distance*0, roundingTime/4 , {type:AR.CONST.EASING_CURVE_TYPE.EASE_IN_SINE});

        var q1 = new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.PARALLEL, [northSouthAnimation1, eastWestAnimation1]);
        var q2 = new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.PARALLEL, [northSouthAnimation2, eastWestAnimation2]);
        var q3 = new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.PARALLEL, [northSouthAnimation3, eastWestAnimation3]);
        var q4 = new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.PARALLEL, [northSouthAnimation4, eastWestAnimation4]);

        var cicularAnimationGroup = new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.SEQUENTIAL, [ q4, q1, q2, q3]);

        cicularAnimationGroup.start(-1);
    },

    planetClicked: function (planet) {
        return function() {
            document.getElementById("info").setAttribute("class", "info");
            document.getElementById("name").innerHTML = planet.name;
            document.getElementById("mass").innerHTML = planet.mass;
            document.getElementById("diameter").innerHTML = planet.diameter;
            document.getElementById("info").setAttribute("class", "infoVisible");
        };
    }
};

Solar.init();
