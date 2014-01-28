WikitudePlugin = {

    /**
     *	This is the SDK Key, provided to you after you purchased the Wikitude SDK from http://www.wikitude.com/store/.
     *	If you're having a trial version, leave this string empty.
     */
    SDKKey: "ENTER-YOUR-KEY-HERE",

    /**
     *	This variable represents if the current device is capable of running ARchitect Worlds.
     */
    isDeviceSupported: false,

    /**
     *	The Wikitude SDK can run in different modes. Geo means that objects are placed on latitude/longitude positions. IR means that only image recognition is used in the ARchitect World.
     *  When your ARchitect World uses both, geo and ir content, than leave this to "Geo". When you only need image recognition, placing "IR" will require less features from the device. 
     */
    arMode: "Geo", // "IR" for image recognition worlds only

    /**
     *	Callbacks that are used during device compatibilty checks.
     */
    onDeviceSupportedCallback: null,
    onDeviceNotSupportedCallback: null,

    /**
     *	Callbacks that are used if an ARchitect World was launched successfully or not.
     */
    onARchitectWorldLaunchedCallback: null,
    onARchitectWorldFailedLaunchingCallback: null,


    /*
     *	=============================================================================================================================
     *
     *	PUBLIC API
     *
     *	=============================================================================================================================
     */

    /* Managing ARchitect world loading */

    /**
     *  Use this function to check if the current device is capable of running ARchitect Worlds.
     *
     * @param {function} successCallback A callback which is called if the device is capable of running ARchitect Worlds.
     * @param {function} errorCallback A callback which is called if the device is not capable of running ARchitect Worlds.
     */
    isDeviceSupported: function(successCallback, errorCallback) {

        // Store a reference to the success and error callback function because we intercept the callbacks ourself but need to call the developer ones afterwards
        WikitudePlugin.onDeviceSupportedCallback = successCallback;
        WikitudePlugin.onDeviceNotSupportedCallback = errorCallback;


        // Check if the current device is capable of running Architect Worlds
        cordova.exec(WikitudePlugin.deviceIsARchitectReady, WikitudePlugin.deviceIsNotARchitectReady, "WikitudePlugin", "isDeviceSupported", [WikitudePlugin.arMode]);
    },

    /**
     *	Use this function to load an ARchitect World.
     *
     * 	@param {String} worldPath The path to an ARchitect world, ether on the device or on e.g. your Dropbox.
     */
    loadARchitectWorld: function(worldPath) {

        // before we actually call load, we check again if the device is able to open the world
        if (WikitudePlugin.isDeviceSupported) {

            //	the 'open' function of the Wikitude Plugin requires a option dictionary with two keys:
            //	@param {Object} options (required)
            //	@param {String} options.sdkKey License key for the Wikitude SDK
            //	@param {String} options.filePath The path to a local ARchitect world or to a ARchitect world on a server or your dropbox
            cordova.exec(WikitudePlugin.worldLaunched, WikitudePlugin.worldFailedLaunching, "WikitudePlugin", "open", [WikitudePlugin.SDKKey, worldPath]);


            // We add an event listener on the resume and pause event of the application lifecycle
            document.addEventListener("resume", WikitudePlugin.onResume, false);
            document.addEventListener("pause", WikitudePlugin.onPause, false);

        } else {

            // If the device is not supported, we call the device not supported callback again.
            if (WikitudePlugin.onDeviceNotSupportedCallback {
                WikitudePlugin.onDeviceNotSupportedCallback();
            }
        }
    },

    /* Managing the Wikitude SDK Lifecycle */
    /**
     *	Use this function to stop the Wikitude SDK and to remove it from the screen.
     */
    close: function() {
        document.removeEventListener("pause", WikitudePlugin.onPause, false);
        document.removeEventListener("resume", WikitudePlugin.onResume, false);


        cordova.exec(WikitudePlugin.onWikitudeOK, WikitudePlugin.onWikitudeError, "WikitudePlugin", "close", [""]);
    },

    /**
     *	Use this function to only hide the Wikitude SDK. All location and rendering updates are still active.
     */
    hide: function() {
        cordova.exec(WikitudePlugin.onWikitudeOK, WikitudePlugin.onWikitudeError, "WikitudePlugin", "hide", [""]);
    },

    /**
     *	Use this function to show the Wikitude SDK again if it was hidden before.
     */
    show: function() {
        cordova.exec(WikitudePlugin.onWikitudeOK, WikitudePlugin.onWikitudeError, "WikitudePlugin", "show", [""]);
    },

    /* Interacting with the Wikitude SDK */

    /**
     *	Use this function to call javascript which will be executed in the context of the currently loaded ARchitect World.
     *
     * @param js The JavaScript that should be evaluated in the ARchitect View.
     */
    callJavaScript: function(js) {
        cordova.exec(WikitudePlugin.onWikitudeOK, WikitudePlugin.onWikitudeError, "WikitudePlugin", "callJavascript", [js]);
    },

    /**
     *	Use this function to set a callback which will be invoked when the ARchitect World opens an architectsdk:// url.
     *	document.location = "architectsdk://opendetailpage?id=9";
     *
     *	@param onUrlInvokeCallback A function which will be called when the ARchitect World invokes a call to "document.location = architectsdk://"
     */
    setOnUrlInvokeCallback: function(onUrlInvokeCallback) {
        cordova.exec(onUrlInvokeCallback, WikitudePlugin.onWikitudeError, "WikitudePlugin", "onUrlInvoke", [""]);
    },

    /**
     *  Use this function to generate a screenshot from the current Wikitude SDK view.
     *
     *  @param includeWebView Indicates if the ARchitect web view should be included in the generated screenshot or not.
     *  @param imagePathInBundleorNullForPhotoLibrary If a file path or file name is given, the generated screenshot will be saved in the application bundle. Passing null will save the photo in the device photo library.
     */
    captureScreen: function(includeWebView, imagePathInBundleOrNullForPhotoLibrary, successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "WikitudePlugin", "captureScreen", [includeWebView, imagePathInBundleOrNullForPhotoLibrary]);
    },

    /*
     *	=============================================================================================================================
     *
     *	Callbacks of public functions
     *
     *	=============================================================================================================================
     */


    /**
     *  This function gets called if the Wikitude Plugin reports that the device is able to start the Wikitude SDK
     */
    deviceIsARchitectReady: function() {
        
        // Keep track of the device status
        WikitudePlugin.isDeviceSupported = true;

        // if the developer passed in a device supported callback, call it
        if (WikitudePlugin.onDeviceSupportedCallback) {
            WikitudePlugin.onDeviceSupportedCallback();
        }
    },

    /**
     *  This function gets called if the Wikitude Plugin reports that the device is not able of starting the Wikitude SDK.
     */
    deviceIsNotARchitectReady: function() {

        // Keep track of the device status
        WikitudePlugin.isDeviceSupported = false;

        // if the developer passed in a device not supported callback, call it
        if (WikitudePlugin.onDeviceNotSupportedCallback) {
            WikitudePlugin.onDeviceNotSupportedCallback();
        }
    },

    /**
     *	Use this callback to get notified when the ARchitect World was loaded successfully.
     */
    worldLaunched: function() {
        if (WikitudePlugin.onARchitectWorldLaunchedCallback) {
            WikitudePlugin.onARchitectWorldLaunchedCallback();
        }
    },

    /**
     *	Use this callback to get notified when the ARchitect World could not be loaded.
     */
    worldFailedLaunching: function(err) {
        if (WikitudePlugin.onARchitectWorldFailedLaunchingCallback) {
            WikitudePlugin.onARchitectWorldFailedLaunchingCallback(err);
        }
    },

    /* Lifecycle updates */
    /**
     *	This function gets called every time the application did become active.
     */
    onResume: function() {

        // Call the Wikitude SDK that it should resume.
        cordova.exec(WikitudePlugin.onWikitudeOK, WikitudePlugin.onWikitudeError, "WikitudePlugin", "onResume", [""]);
    },

    /**
     *	This function gets called every time the application is about to become inactive.
     */
    onPause: function() {

        // Call the Wikitude SDK that the application did become inactive
        cordova.exec(WikitudePlugin.onWikitudeOK, WikitudePlugin.onWikitudeError, "WikitudePlugin", "onPause", [""]);
    },

    /**
     *	Android specific!
     *	This function gets called if the user presses the back button
     */
    onBackButton: function() {

        cordova.exec(WikitudePlugin.onWikitudeOK, WikitudePlugin.onWikitudeError, "WikitudePlugin", "close", [""]);
        WikitudePlugin.stopLocationUpdates();

        document.removeEventListener("backbutton", WikitudePlugin.onBackButton, false);
    },

    /**
     *	A generic success callback used inside this wrapper.
     */
    onWikitudeOK: function() {},

    /**
     *  A generic error callback used inside this wrapper.
     */
    onWikitudeError: function() {}
};

module.exports = WikitudePlugin;