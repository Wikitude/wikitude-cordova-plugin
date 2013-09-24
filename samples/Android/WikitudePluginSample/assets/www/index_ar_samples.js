/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
var app = {

    isDeviceSupported: false,

    // Application Constructor
    initialize: function() {
        this.bindEvents();
    },
    /**
     *  This function extracts an url parameter
     */
    getUrlParameterForKey: function(url, requestedParam) {
        requestedParam = requestedParam.replace(/[\[]/, "\\\[").replace(/[\]]/, "\\\]");
        var regexS = "[\\?&]" + requestedParam + "=([^&#]*)";
        var regex = new RegExp(regexS);
        var results = regex.exec(url);

        if (results == null)
            return "";
        else {
            var result = decodeURIComponent(results[1]);
            return result;
        }
    },
    // Bind Event Listeners
    //
    // Bind any events that are required on startup. Common events are:
    // 'load', 'deviceready', 'offline', and 'online'.
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
    },
    // --- Wikitude Plugin ---
    /**
     *  This function gets called if you call "document.location = architectsdk://" in your ARchitect World
     *  @param url The url which was called in ARchitect World
     */
    onClickInARchitectWorld: function(url) {
        app.report('url: ' + url);

        if (app.getUrlParameterForKey(url, 'text')) {

            app.report("you clicked on a label with text: " + app.getUrlParameterForKey(url, 'text'));

        } else if (app.getUrlParameterForKey(url, 'action')) {

            WikitudePlugin.onBackButton();

        } else if (app.getUrlParameterForKey(url, 'status')) {
            WikitudePlugin.hide();
        }


    },
    // A callback which gets called if the device is able to launch ARchitect Worlds
    onDeviceSupportedCallback: function() {
        app.isDeviceSupported = true;
    },

    // A callback which gets called if the device is not able to start ARchitect Worlds
    onDeviceNotSupportedCallback: function() {
        app.receivedEvent('Unable to launch ARchitect Worlds on this device');
    },

    loadARchitectWorld: function(samplePath) {
        if (app.isDeviceSupported) {
        	WikitudePlugin.loadARchitectWorld(samplePath);
        } else {
        	alert("Device is not supported");
        }
    },
    // --- End Wikitude Plugin ---
    // deviceready Event Handler
    //
    // The scope of 'this' is the event. In order to call the 'receivedEvent'
    // function, we must explicity call 'app.receivedEvent(...);'
    onDeviceReady: function() {

        app.receivedEvent('deviceready');

        // check if the current device is able to launch ARchitect Worlds
        WikitudePlugin.isDeviceSupported(app.onDeviceSupportedCallback, app.onDeviceNotSupportedCallback);
    },
    // Update DOM on a Received Event
    receivedEvent: function(id) {
        var parentElement = document.getElementById(id);
        var listeningElement = parentElement.querySelector('.listening');
        var receivedElement = parentElement.querySelector('.received');

        listeningElement.setAttribute('style', 'display:none;');
        receivedElement.setAttribute('style', 'display:block;');

        console.log('Received Event: ' + id);
    },
    report: function(id) {
        console.log("report:" + id);
    }
};



var samples = [];

	samples[0] = ["assets/www/world/1_ImageRecognition_1_ImageOnTarget/index.html",
	              "assets/www/world/1_ImageRecognition_2_MultipleTargets/index.html",
	              "assets/www/world/1_ImageRecognition_3_Interactivity/index.html",
	              "assets/www/world/1_ImageRecognition_4_HtmlDrawable/index.html",
	              "assets/www/world/1_ImageRecognition_5_Bonus-Sparkles/index.html"
	              ];
	samples[1] = ["assets/www/world/2_3dAndImageRecognition_1_3dModelOnTarget/index.html",
	             "assets/www/world/2_3dAndImageRecognition_2_AppearingAnimation/index.html",
	             "assets/www/world/2_3dAndImageRecognition_3_Interactivity/index.html"
             ];
	
	samples[2] = ["assets/www/world/3_PointOfInterest_1_PoiAtLocation/index.html",
	             "assets/www/world/3_PointOfInterest_2_PoiWithLabel/index.html",
	             "assets/www/world/3_PointOfInterest_3_MultiplePois/index.html",
	             "assets/www/world/3_PointOfInterest_4_SelectingPois/index.html"
             ];
	
	samples[3] = ["assets/www/world/4_ObtainPoiData_1_FromWebservice/index.html",
	             "assets/www/world/4_ObtainPoiData_2_FromLocalResource/index.html",
	             "assets/www/world/4_ObtainPoiData_3_FromApplicationModel/index.html"
             ];
	
	samples[4] = ["assets/www/world/5_BrowsingPois_1_PresentingPoiDetails/index.html",
	             "assets/www/world/5_BrowsingPois_2_PoiRadar/index.html",
	             "assets/www/world/5_BrowsingPois_3_LimitingVisiblePois/index.html",
	             "assets/www/world/5_BrowsingPois_4_ReloadingPoiData/index.html",
                 "assets/www/world/5_BrowsingPois_5_Refresh/index.html",
             ];
	
	samples[5] = ["assets/www/world/6_Demo_1_ImageRecognitionAndGeo/index.html",
	             "assets/www/world/6_Demo_2_SolarSystem(Geo)/index.html",
	             "assets/www/world/6_Demo_3_SolarSystem(ImageRecognition)/index.html"
             ];

function loadAR(categoryNr, sampleNr){
	// when user presses back-button -> execute default function -> close AR-view
	/*
	document.removeEventListener("backbutton", WikitudePlugin.onBackButton, false);
	document.addEventListener("backbutton", WikitudePlugin.onBackButton, false);
	*/
	
    app.loadARchitectWorld(samples[categoryNr][sampleNr]);
	
    // inject poi data using phonegap's GeoLocation API and inject data using World.loadPoisFromJsonData
	if (categoryNr == 3 && sampleNr == 2) {
		navigator.geolocation.getCurrentPosition(onLocationUpdated,
	    		onLocationError);	
	}
}



/* - - - - - -  relevant for sample 4.3 only  - BEGIN */

/* this is a dummy implementation to create poi-data, which are passed over to JS / Wikitude SDK on first location update */
function onLocationUpdated(position) {
	var latitude = position.coords.latitude;
	var longitude = position.coords.longitude;
	var altitude = position.coords.altitude;
	var placesAmount = 10;
	var poiData = [];
	
	// creates dummy poi-data around given lat/lon
	for (var i=0; i< placesAmount; i++) {
		poiData.push({ 'id': (i+1), 'longitude': longitude + 0.001 * ( 5 - getRandomInt(1,10) ), 'latitude' : latitude + 0.001 * (5 - getRandomInt(1,10)), 'description': 'This is the description of POI#'+(i+1), 'altitude' : 100.0, 'name': 'POI#'+(i+1)})
	}
	
	// inject POI data in JSON-format to JS
	WikitudePlugin.callJavaScript( "World.loadPoisFromJsonData(" + JSON.stringify( poiData ) +");");
}

function onLocationError(error) {
	alert("Not able to fetch location.");
}

function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1) + min);
}

/* - - - - - -  relevant for sample 4.3 only  - END */


app.initialize();
