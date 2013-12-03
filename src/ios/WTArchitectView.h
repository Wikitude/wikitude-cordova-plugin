//
//  WikitudeArchitectSDK.h
//  WikitudeArchitectSDK
//
//  Copyright (c) 2012 Wikitude. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>


@protocol WTScreenshotSaver;

@class CMMotionManager;
@class WTArchitectView;


extern NSString * const kWTScreenshotBundleDirectoryKey;
extern NSString * const kWTScreenshotSaveModeKey;
extern NSString * const kWTScreenshotCaptureModeKey;
extern NSString * const kWTScreenshotImageKey;


typedef NS_ENUM(NSUInteger, WTARMode){
    WTARMode_Geo,
    WTARMode_IR
};

typedef NS_ENUM(NSUInteger, WTScreenshotCaptureMode){

    WTScreenshotCaptureMode_Cam,
    WTScreenshotCaptureMode_CamAndWebView
};

typedef NS_ENUM(NSUInteger, WTScreenshotSaveMode){

    WTScreenshotSaveMode_PhotoLibrary       = 1,
    WTScreenshotSaveMode_BundleDirectory    = 2,
    WTScreenshotSaveMode_Delegate           = 3
};

typedef NS_OPTIONS(NSUInteger, WTScreenshotSaveOptions){

    WTScreenshotSaveOption_CallDelegateOnSuccess        = 1 << 0,
    WTScreenshotSaveOption_SavingWithoutOverwriting     = 1 << 1,
    WTScreenshotSaveOption_None                         = 0
};


/**
 * WTArchitectViewDelegate
 *
 * The ArchitectUrlListener offers the native app the possibility to react on events that are triggered inside the ARchitect World. To initiate such an event, the ARchitect World simply has to make an request for an url with the "architectsdk" as protocol. E.g.: architectsdk://opendetails?id=123.
 *
 * An registered WTArchitectViewDelegate receives all requested "architectsdk://" urls and must therefore be able to parse the url and parameters to react accordingly.
 *
 */
@protocol WTArchitectViewDelegate <NSObject>


@optional
/**
 * Supplied URL was called and should be opened. URL starts with architectsdk:// protocol prefix and is otherwise custom to the ARchitect World that requests it.
 *
 * @param architectView The WTArchitectView object which invoked the url.
 *
 * @param url The url which was called in javascript.
*/ 
- (void)architectView:(WTArchitectView *)architectView invokedURL:(NSURL *)url;


/**
 * This method is called when the provided architect world url failed to load.
 *
 * @param architectView The ArchitectView which failed to load the url.
 *
 * @param error An NSError object containing more informations why the load did fail.
*/
- (void)architectView:(WTArchitectView *)architectView didFailLoadWithError:(NSError *)error;


/**
 * This method is called when the WTArchitectView did finish capturing a screenshot
 *
 * @param architectView The ArchitectView which generated the screenshot.
 *
 * @param context A NSDictionary, containig at least CaptureMode (Key = WTScreenshotCaptureMode) and SavingMode (Key = WTScreenshotSaveMode). Optional objects are given for the different SaveModes. 
 *
 * @discussion The context contains different objects depending on the SaveMode. SaveMode PhotoLibrary contains the two standard objects (CaptureMode & SaveMode). SaveMode PhotoLibrary contains additional a UIImage object (the Screenshot, Key = WTScreenshotKey). SaveMode BundleDirectory contains a NSString object representing the file path in the bundle (Key = WTScreenshotPath).
*/
- (void)architectView:(WTArchitectView *)architectView didCaptureScreenWithContext:(NSDictionary *)context;

/**
 * This method is called when the WTArchitectView couldn't finish capturing a screenshot
 *
 * @param architectView The ArchitectView which couldn't finish the capturing.
 *
 * @param error A NSError, providing more information on what was failing.
 */
- (void)architectView:(WTArchitectView *)architectView didFailCaptureScreenWithError:(NSError *)error;

@end



/**
 * WTArchitectView class
 *
 *This class allows you to load and display the content from ARchitect Worlds.
 *It is the "Entry Point" to the SDK which exposes all SDK functionality. Instantiating and adding this Component to the UI should be sufficient to use ARchitect in any application. 
 *
 */
@interface WTArchitectView : UIView

/** @name Managing the Delegate */
/**
 * The object that acts as the delegate of the receiving WTArchitectView
 *
*/ 
@property (nonatomic, weak) id<WTArchitectViewDelegate>                                 delegate;
@property (nonatomic, readonly) BOOL                                                    isRunning;
@property (nonatomic, assign) CLLocationAccuracy                                        desiredLocationAccuracy;
@property (nonatomic, assign) CLLocationDistance                                        desiredDistanceFilter;
@property (nonatomic, assign) BOOL                                                      shouldWebViewRotate;


/** @name Accessing Device Compatibility */
/**
 * Returns true if the device supports the requested ARMode, false otherwise.
 *
 * @param supportedARMode Enum value which describes the required ARMode.
 *
 * @return true if the requested ARMode is supported for the current device, false otherwise.
 *
 * @discussion If the device supports ARMode_Geo, also ARMode_IR is supported.
 */
+ (BOOL)isDeviceSupportedForARMode:(WTARMode)supportedARMode;


/** @name Initializing a WTArchitectView Object */
/**
 * Initializes the ARchitect view with the specified license key and motion manager that will be shared by the Wikitude SDK and the third party application.
 * If a motion manager instance is passed, it will be set to Wikitudes preferred settings (update intervals etc.)
 * The motion manager argument may be nil in which case Wikitude creates and manages its own motion manager instance.
 *
 *  -
 *
 * @param key Your developer key, provided with your licence information.
 * @param motionManager The CMMotionManager instance which should be used from the SDK.
*/
- (void)initializeWithKey:(NSString*)key motionManager:(CMMotionManager*)motionManager;


/** @name Loading Architect Worlds */
/**
 * Replaces the existing content of the ArchitectView with the one from the supplied URL.
 *  @param architectWorldUrl The url that points to the Architect world. This can be eather a local .html file or a url, pointing to a file on a server or to your dropbox.
 *
 * @discussion
*/
- (void)loadArchitectWorldFromUrl:(NSURL *)architectWorldUrl;


/** @name Interacting with Architect Worlds */
/**
 * Executes the passed JavaScript string in the context of the currently loaded ARchitect World. This can be used to pass data to the ARchitect World or to notify it of external events.
 * @param javaScript A string, representing the javascript code which should be executed.
*/ 
- (void)callJavaScript:(NSString*)javaScript;


/** @name Injecting Locations */
/**
 * Injects the supplied location information. To use the injected location setUseInjectedLocation(true) has to be called. 
 * @param latitude The latitude that has to be simulated.
 * @param longitude The longitude that has to be simulated.
 * @param altitude The to altitude that has to be simulated.
 * @param accuracy The accuracy of the simulated location.
*/ 
- (void)injectLocationWithLatitude:(float)latitude longitude:(float)longitude altitude:(float)altitude accuracy:(float)accuracy;


/**
* Injects the supplied location information. To use the injected location setUseInjectedLocation(true) has to be called. 
 * @param latitude The latitude that has to be simulated.
 * @param longitude The longitude that has to be simulated.
 * @param accuracy The accuracy of the simulated location.
*/ 
- (void)injectLocationWithLatitude:(float)latitude longitude:(float)longitude accuracy:(float)accuracy;


/**
 * If true is supplied the injected location will be used. If false is supplied the default location provider will be used.
 * @param useInjectedLocation The location simulation status
*/ 
- (void)setUseInjectedLocation:(BOOL)useInjectedLocation;


/**
 * True if an injected location is currently used. false if default location provider is used.
 * @return Indicates, if the location provider is simulating the injected location.
*/ 
- (BOOL)isUsingInjectedLocation;


/** @name Manipulating Object Visibility */
/**
 * Sets the culling distance in meters. Objects in AR that are further away won’t be visible. The default value is 50000 meters (= 50 km).
 * @param cullingDistance The culling distance that has to be applied to your AR objects.
*/
- (void)setCullingDistance:(float)cullingDistance;


/**
 * Retrieves the current culling distance in meters.
 * @return The current culling distance, used by the SDK.
*/
- (float)cullingDistance;


/** @name Accessing ARchitect settings */
/**
 * Use this method to get the current ARchitect version number
 *
 * @return The current available ARchitect verison within the SDK.
*/
- (NSString *)versionNumber;


/**
 * Use this method to clear all cached data and requests.
 *
 * This method clears the internal SDK cache, as well as the cache used by the webView.
 * 
*/
- (void)clearCache;


/** @name Managing the WTArchitectView rotation behavior */
/**
 * Use this method to set the auto rotation behavior for the WTArchitectview.
 *
 * You should pass YES if you wan't your WTArchitectView to autoamtically change rotation to the new interface orientation.
 *
 * @param shouldAutoRotate Should your SDK view change orientation automatically
 * @param interfaceOrientation The interface orientation the device is going to take on
*/
- (void)setShouldRotate:(BOOL)shouldAutoRotate toInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation;


/**
 * Retrieves the current auto rotate behavior.
 *
 * @return The current auto rotation option, used by the SDK.
*/
- (BOOL)isRotatingToInterfaceOrientation;


/** @name Managing the WTArchitectView updates */
/**
 * Stops all activity of the ARchitect view (suspends UI updates of background camera, AR objects etc).
*/
- (void)stop;


/**
 * Starts activity of the ARchitect view (starts UI updates of background camera, AR objects etc).
*/ 
- (void)start;


/** @name Interacting with Device Motion */
/**
 * Returns the motion manager used by the Wikitude SDK.
 * @return  The CMMotionManager instance, provided in the method "InitializeWithKey:motionManager", otherwise nil;
*/ 
- (CMMotionManager*)motionManager;


/** @name Accessing WTArchitectView content */
/**
 * Triggers the generation of a UIImage which contains a screenshot of the next available frame.
 *
 * @param captureMode Defines if the WebView is included in the screenshot or not.
 * @param saveMode Defines how the captured screenshot should be processed. Possible ways are to save it to the Photo Library, to a specific bundle directory or to receive a delegate call where the image is passed in.
 * @param options Defines more option for a specific SaveMode. 
 * @param context A NSDictionary containing information about the CaptureMode, SaveMode and SaveMode specific objects. See Protocol reference for more information.
*/
- (void)captureScreenWithMode:(WTScreenshotCaptureMode)captureMode usingSaveMode:(WTScreenshotSaveMode)saveMode saveOptions:(WTScreenshotSaveOptions)options context:(NSDictionary *)context;


@end
