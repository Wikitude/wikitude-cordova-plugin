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

    loadARchitectWorld: function(sample) {
        if (app.isDeviceSupported) {

        	
            if (sample==1) {
            	WikitudePlugin.loadARchitectWorld("assets/www/world/4_ObtainPoiData_1_FromWebservice/index.html");
            } else {
            	WikitudePlugin.loadARchitectWorld("assets/www/world/1_ImageRecognition_1_ImageOnTarget/index.html");
            }
            

            // if you want to listen to document.location = architectsdk://yourhost?param1=foo&param2=bar simply set the onUrlInvoceCallback
            // WikitudePlugin.setOnUrlInvokeCallback( yourcallback);
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