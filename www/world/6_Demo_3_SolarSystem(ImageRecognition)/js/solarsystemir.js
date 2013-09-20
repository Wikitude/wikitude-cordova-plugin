var World = {
    planetsInfo: null,
    rotating: false,
    selectedPlanet: null,

    init: function initFn() {
        var tracker = new AR.Tracker("assets/SolarSystem.wtc");

        var sizeFactor = 0.01;
        var distanceFactor = 0.01;

        this.sunLocation = {
            x: 0,
            y: 0,
            z: 0.2
        };

        this.planetsInfo = [{
            name: "Sun",
            distance: 0,
            modelFile: "assets/sun.wt3",
            realSize: 109.2 * sizeFactor,
            description: "The Sun is the star at the center of the Solar System. It is almost perfectly spherical and consists of hot plasma interwoven with magnetic fields.",
            mass: "2&nbsp;10<sup>30</sup>&nbsp;kg",
            diameter: "1,392,684&nbsp;km"
        },

        {
            name: "Mercury",
            distance: 3.9 * distanceFactor,
            modelFile: "assets/mercury.wt3",
            realSize: 0.383 * sizeFactor,
            description: "Is the innermost planet in the Solar System. It is also the smallest, and its orbit is the most eccentric (that is, the least perfectly circular).",
            mass: "3.3&nbsp;10<sup>23</sup>&nbsp;kg",
            diameter: "4,880&nbsp;km"
        },

        {
            name: "Venus",
            distance: 7.2 * distanceFactor,
            modelFile: "assets/venus.wt3",
            realSize: 0.95 * sizeFactor,
            description: "Is named after the Roman goddess of love and beauty. After the Moon, it is the brightest natural object in the night sky, bright enough to cast shadows.",
            mass: "4.9&nbsp;10<sup>24</sup>",
            diameter: "12,092&nbsp;km"
        },

        {
            name: "Earth",
            distance: 10 * distanceFactor,
            modelFile: "assets/earth.wt3",
            realSize: 1 * sizeFactor,
            description: "Is the third planet from the Sun, and the densest and fifth-largest of the eight planets in the Solar System. It is sometimes referred to as the world, the Blue Planet, Terra.",
            mass: " 6&nbsp;10<sup>24</sup>&nbsp;kg",
            diameter: "12,742&nbsp;km"
        },

        {
            name: "Mars",
            distance: 15 * distanceFactor,
            modelFile: "assets/mars.wt3",
            realSize: 0.532 * sizeFactor,
            description: "Is named after the Roman god of war, it is often described as the &quot;Red Planet&quot;, as the iron oxide prevalent on its surface gives it a reddish appearance.",
            mass: "6.4&nbsp;10<sup>23</sup>&nbsp;kg",
            diameter: "6794&nbsp;km"
        },

        {
            name: "Jupiter",
            distance: 50.2 * distanceFactor,
            modelFile: "assets/jupiter.wt3",
            realSize: 10.97 * sizeFactor,
            description: "Is the largest planet within the Solar System. It is a gas giant with mass one-thousandth that of the Sun but is two and a half times the mass of all the other planets in our Solar System combined.",
            mass: "1.9&nbsp;10<sup>27</sup>&nbsp;kg",
            diameter: "142,984&nbsp;km"
        },

        {
            name: "Saturn",
            distance: 95.3 * distanceFactor,
            modelFile: "assets/saturn.wt3",
            realSize: 9.14 * sizeFactor,
            description: "Is the second largest planet in the Solar System, after Jupiter. Named after the Roman god Saturn. Saturn is a gas giant with an average radius about nine times that of Earth.",
            mass: "5.7&nbsp;10<sup>26</sup>&nbsp;kg",
            diameter: "25,000&nbsp;km"
        },

        {
            name: "Uranus",
            distance: 192 * distanceFactor,
            modelFile: "assets/uranus.wt3",
            realSize: 3.98 * sizeFactor,
            description: "It has the third-largest planetary radius and fourth-largest planetary mass in the Solar System. It is named after the ancient Greek deity of the sky Uranus.",
            mass: "8.7&nbsp;10<sup>25</sup>&nbsp;kg",
            diameter: "51,118&nbsp;km"
        },

        {
            name: "Neptune",
            distance: 301 * distanceFactor,
            modelFile: "assets/neptune.wt3",
            realSize: 3.86 * sizeFactor,
            description: "Is the farthest planet from the Sun in the Solar System. It is the fourth-largest planet by diameter and the third-largest by mass.",
            mass: "1&nbsp;10 <sup>26</sup>&nbsp;kg",
            diameter: "49,532&nbsp;km"
        },

        {
            name: "Pluto",
            distance: 394 * distanceFactor,
            modelFile: "assets/pluto.wt3",
            realSize: 0.181 * sizeFactor,
            description: "Originally classified as the ninth planet from the Sun, Pluto was recategorized as a dwarf planet and plutoid owing to the discovery that it is only one of several large bodies within the Kuiper belt.",
            mass: "1.3&nbsp;10<sup>22</sup>&nbsp;kg",
            diameter: "2,306&nbsp;km"
        }];

        var planets = [];
        this.planetAnimations = [];

        for (var i = 0; i < this.planetsInfo.length; i++) {
            var info = this.planetsInfo[i];

            info.size = Math.log(info.realSize * 1000) * 0.01;
            if (i > 0) {
                info.distance = this.planetsInfo[i - 1].distance + this.planetsInfo[i - 1].size + info.size + 0.05;
            }

            planets[i] = new AR.Model(info.modelFile, {
                scale: {
                    x: info.size,
                    y: info.size,
                    z: info.size
                },
                translate: {
                    x: this.sunLocation.x + info.distance,
                    y: this.sunLocation.y,
                    z: this.sunLocation.z
                }
            });

            info.planetModel = planets[i];
            info.selectedAnimation = this.createSelectedAnimation(info);
            info.select = this.selectPlanet;

            planets[i].onClick = this.planetClicked(info);
            if (i > 0) {
                this.planetAnimations.push(this.createOrbitAnimation(planets[i], info));
            }
        }

        var backdropImg = new AR.ImageResource("assets/backdrop.png");
        var backdrop = [new AR.ImageDrawable(backdropImg, 2)];

        var overlay = new AR.Trackable2DObject(tracker, "solarsystem", {
            drawables: {
                cam: backdrop.concat(planets)
            }
        });

        AR.context.onScreenClick = this.screenClick;
    },

    createOrbitAnimation: function createOrbitAnimationFn(planet, info) {
        var distance = info.distance;
        var roundingTime = distance * 10000;

        var yAnimation1 = new AR.PropertyAnimation(planet, 'translate.y', this.sunLocation.y + distance * 1, this.sunLocation.y + distance * 0, roundingTime / 4, {
            type: AR.CONST.EASING_CURVE_TYPE.EASE_IN_SINE
        });
        var xAnimation1 = new AR.PropertyAnimation(planet, 'translate.x', this.sunLocation.x + distance * 0, this.sunLocation.x + distance * 1, roundingTime / 4, {
            type: AR.CONST.EASING_CURVE_TYPE.EASE_OUT_SINE
        });

        var yAnimation2 = new AR.PropertyAnimation(planet, 'translate.y', this.sunLocation.y + distance * 0, this.sunLocation.y + distance * -1, roundingTime / 4, {
            type: AR.CONST.EASING_CURVE_TYPE.EASE_OUT_SINE
        });
        var xAnimation2 = new AR.PropertyAnimation(planet, 'translate.x', this.sunLocation.x + distance * 1, this.sunLocation.x + distance * 0, roundingTime / 4, {
            type: AR.CONST.EASING_CURVE_TYPE.EASE_IN_SINE
        });

        var yAnimation3 = new AR.PropertyAnimation(planet, 'translate.y', this.sunLocation.y + distance * -1, this.sunLocation.y + distance * 0, roundingTime / 4, {
            type: AR.CONST.EASING_CURVE_TYPE.EASE_IN_SINE
        });
        var xAnimation3 = new AR.PropertyAnimation(planet, 'translate.x', this.sunLocation.x + distance * 0, this.sunLocation.x + distance * -1, roundingTime / 4, {
            type: AR.CONST.EASING_CURVE_TYPE.EASE_OUT_SINE
        });

        var yAnimation4 = new AR.PropertyAnimation(planet, 'translate.y', this.sunLocation.y + distance * 0, this.sunLocation.y + distance * 1, roundingTime / 4, {
            type: AR.CONST.EASING_CURVE_TYPE.EASE_OUT_SINE
        });
        var xAnimation4 = new AR.PropertyAnimation(planet, 'translate.x', this.sunLocation.x + distance * -1, this.sunLocation.x + distance * 0, roundingTime / 4, {
            type: AR.CONST.EASING_CURVE_TYPE.EASE_IN_SINE
        });

        var q1 = new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.PARALLEL, [yAnimation1, xAnimation1]);
        var q2 = new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.PARALLEL, [yAnimation2, xAnimation2]);
        var q3 = new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.PARALLEL, [yAnimation3, xAnimation3]);
        var q4 = new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.PARALLEL, [yAnimation4, xAnimation4]);

        return new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.SEQUENTIAL, [q2, q3, q4, q1]);
    },

    createSelectedAnimation: function createSelectedAnimationFn(planet) {
        var scaleUp = new AR.PropertyAnimation(planet.planetModel, "scale.x", planet.size, planet.size * 1.2, 500);
        var scaleDown = new AR.PropertyAnimation(planet.planetModel, "scale.x", planet.size * 1.2, planet.size, 500);

        return new AR.AnimationGroup(AR.CONST.ANIMATION_GROUP_TYPE.SEQUENTIAL, [scaleUp, scaleDown]);
    },

    selectPlanet: function selectPlanetFn(select) {
        if (select) {
            if (World.selectedPlanet !== null) {
                World.selectedPlanet.select(false);
            }
            World.selectedPlanet = this;
            this.selectedAnimation.start(-1);
        } else {
            this.selectedAnimation.stop();
            this.planetModel.scale = {
                x: this.size,
                y: this.size,
                z: this.size
            };
        }
    },

    planetClicked: function planetClickedFn(planet) {
        return function() {
            planet.select(true);
            document.getElementById("info").setAttribute("class", "info");
            document.getElementById("name").innerHTML = planet.name;
            document.getElementById("mass").innerHTML = planet.mass;
            document.getElementById("diameter").innerHTML = planet.diameter;
            document.getElementById("info").setAttribute("class", "infoVisible");
            return true;
        };
    },

    screenClick: function onScreenClickFn() {
        if (World.selectedPlanet !== null) {
            World.selectedPlanet.select(false);
        }

        document.getElementById("info").setAttribute("class", "info");
    },

    toggleAnimatePlanets: function toggleAnimatePlanetsFn() {
        if (!this.planetAnimations[0].isRunning()) {
            if (!this.rotating) {
                this.planetAnimations.forEach(function startAnimFn(a) {
                    a.start(-1);
                });
                this.rotating = true;
            } else {
                this.planetAnimations.forEach(function resumeAnimFn(a) {
                    a.resume();
                });
            }
        } else {
            this.planetAnimations.forEach(function pauseAnimFn(a) {
                a.pause();
            });
        }

        return true;
    }
};

World.init();