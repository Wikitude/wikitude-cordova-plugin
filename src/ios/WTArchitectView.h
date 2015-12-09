//
//  WTArchitectView.h
//  WikitudeSDK
//
//  Copyright (c) 2014 Wikitude. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

#import "WTWikitudeTypes.h"


@class CMMotionManager;
@class WTNavigation;
@class WTArchitectView;
@class WTStartupConfiguration;

@protocol WTArchitectViewDebugDelegate;


extern NSString * const kWTScreenshotBundleDirectoryKey;
extern NSString * const kWTScreenshotSaveModeKey;
extern NSString * const kWTScreenshotCaptureModeKey;
extern NSString * const kWTScreenshotImageKey;



/**
 * The WTArchitectViewDelegate offers the possibility to either react on events that are triggered inside the ARchitect World or events that are triggerd because of some interaction with the WTArchitectView.
 *
 */
@protocol WTArchitectViewDelegate <NSObject>


@optional

/** @name ARchitect World */

/**
 * This method is called when the provided architect world url finished loading. The resulting navigation object contains the original load url as well as the final resolved url.
 *
 * @param architectView The architect view that finished loading.
 * @param navigation The navigation that finished loading.
 */
- (void)architectView:(WTArchitectView *)architectView didFinishLoadArchitectWorldNavigation:(WTNavigation *)navigation;


/**
 * This method is called when the provided architect world url failed to load.
 *
 * @param architectView The ArchitectView which failed to load the url.
 * @param navigation The navigation which failed to load.
 * @param error An error object containing more informations why the load did fail.
 */
- (void)architectView:(WTArchitectView *)architectView didFailToLoadArchitectWorldNavigation:(WTNavigation *)navigation withError:(NSError *)error;


/**
 * This method offers the possibility to react on events that are triggered inside the ARchitect World. To initiate such an event, the ARchitect World simply has to make an request for an url with the "architectsdk://" scheme. E.g.: architectsdk://opendetails?id=123.
 *
 * @param architectView The WTArchitectView object which invoked the url.
 * @param URL The url which was called in javascript.
 */
- (void)architectView:(WTArchitectView *)architectView invokedURL:(NSURL *)URL;


/** @name Screen capturing */
/**
 * This method is called when the WTArchitectView did finish capturing a screenshot
 *
 * @param architectView The ArchitectView which generated the screenshot.
 * @param context A NSDictionary, containig at least CaptureMode (Key = WTScreenshotCaptureMode) and SavingMode (Key = WTScreenshotSaveMode). Optional objects are given for the different SaveModes.
 *
 * @discussion The context contains different objects depending on the SaveMode. SaveMode PhotoLibrary contains the two standard objects (CaptureMode & SaveMode). SaveMode PhotoLibrary contains additional a UIImage object (the Screenshot, Key = WTScreenshotKey). SaveMode BundleDirectory contains a NSString object representing the file path in the bundle (Key = WTScreenshotPath).
 */
- (void)architectView:(WTArchitectView *)architectView didCaptureScreenWithContext:(NSDictionary *)context;


/**
 * This method is called when the WTArchitectView couldn't finish capturing a screenshot
 *
 * @param architectView The ArchitectView which couldn't finish the capturing.
 * @param error A NSError, providing more information on what was failing.
 */
- (void)architectView:(WTArchitectView *)architectView didFailCaptureScreenWithError:(NSError *)error;


/** @name View controller presentation */
/**
 * This method is called every time the architect view want’s to present a view controller.
 *
 * @param architectView The architect view which want's to present a view controller.
 *
 * @return A view controller which can be used for presentation.
 *
 * @discussion if nil is returned or the method is not implemented, the architect view tries to grab an appropriate view controller from the current view controller hierarchy.
 */
- (UIViewController *)presentingViewControllerForViewControllerPresentationInArchitectView:(WTArchitectView *)architectView;


/**
 * This method is called every time the architect view presents a view controller on top of itself. If the architect view is presented using a navigation controller, additional view controller will be pushed onto the navigation controller stack. On all other controller (e.g. tab bar controller) a modal presentation will be used.
 *
 * @param architectView The architect view which is about to present a view controller.
 * @param presentedViewController The view controller which will be presented.
 * @param presentingViewController The view controller which will present the new view controller. This can be an internally created view controller or the view controller which was returned from the -presentingViewControllerForViewControllerPresentationInArchitectView: delegate method.
 *
 * @discussion Use this method to e.g. stype the UI elements on the presented view controller or change the modal presentation style.
 */
- (void)architectView:(WTArchitectView *)architectView willPresentViewController:(UIViewController *)presentedViewController onViewController:(UIViewController *)presentingViewController;

/**
 * This method is called when the underlaying CLLocationManager needs a heading calibration and the WTStartupConfiguration 'shouldUseSystemHeadingCalibrationDisplay' parameter is set to NO.
 *
 * Once the method is called, a custom view or dialog can be shown, saying that the user should perform the compass calibration motion.
 *
 */
- (void)architectViewNeedsHeadingCalibration:(WTArchitectView *)architectView;

@end



/**
 * WTArchitectView class
 *
 * This class allows you to load and display the content from ARchitect Worlds.
 * It is the "Entry Point" to the SDK which exposes all SDK functionality. Instantiating and adding this Component to the UI should be sufficient to use ARchitect in any application.
 *
 */
@interface WTArchitectView : UIView

/** @name Managing the Delegate */
/**
 * The object that acts as the delegate of the receiving WTArchitectView
 */
@property (nonatomic, weak) id<WTArchitectViewDelegate>                                 delegate;
@property (nonatomic, weak) id<WTArchitectViewDebugDelegate>                            debugDelegate;

@property (nonatomic, readonly) BOOL                                                    isRunning;
@property (nonatomic, assign) CLLocationAccuracy                                        desiredLocationAccuracy;
@property (nonatomic, assign) CLLocationDistance                                        desiredDistanceFilter;
@property (nonatomic, assign) BOOL                                                      shouldWebViewRotate;


/** @name Accessing Device Compatibility */
/**
 * This method should be used to determine if the current device supports all features that are required.
 *
 * @param requiredFeatures Bitmask that describes wich features are used from the Wikitude SDK.
 * @param error An error object containing more information why the device is not supported if the return value is NO.
 *
 * @return true if the device supports all required features, false otherwise.
 */
+ (BOOL)isDeviceSupportedForRequiredFeatures:(WTFeatures)requiredFeatures error:(NSError **)error;

/** @name Accessing ARchitect settings */
/**
 * Use this method to get the current ARchitect version number
 *
 * @return The current available ARchitect verison within the SDK.
 */
+ (NSString *)sdkVersion;


/** @name Initializing a WTArchitectView Object */
/**
 * Returns a newly initialized architect view with the given motion manager object.
 *
 * @param frame A CGRect describing the size of the view
 * @param motionManagerOrNil A CMMotionManager object which should be used from the SDK. If nil is given, the SDK will create there own CMMotionManager object.
 *
 * @return A newly initialized WTArchitectView object.
 *
 * @discussion This is the designated initializer for this class.
 */
- (instancetype)initWithFrame:(CGRect)frame motionManager:(CMMotionManager *)motionManagerOrNil;//NS_DESIGNATED_INITIALIZER;

/**
 * Enables SDK features based on the given license key.
 *
 * @param licenseKey Your developer key, provided with your licence information.
 *
 * @return YES if the license key was valid for this app bundle name, NO otherwise.
 */
- (void)setLicenseKey:(NSString *)licenseKey;

/** @name Loading Architect Worlds */

/**
 * Loads the ARchitect World specified by the given URL. If an ARchitect World is already loaded all it's created objects are destroyed before the new one will be loaded.
 *
 * Architect Worlds can be either loaded from the application bundle or a remote server.
 *
 * Architect Worlds can be loaded with different required features. Features specifies which SDK functionalities are required by the World. For example the WTFeature_2DTracking does not start any GPS location related APIs and the user is not interrupted with a location access alert. As a result any geo related SDK functionalities do not work but the target image recognition is faster and the SDK does not cosume as much CPU performance than with an enabled GPS module. Choose the most suitable mode for your ARchitect World to experience the full functionality and the best performance.
 *
 * It is possible to load a different Architect World with a different augmented reality mode using the same architect view instance.
 *
 * @param architectWorldURL The URL that points to the ARchitect world.
 * @param requiredFeatures Required features who specifies in more detail which functionality is used by the ARchitect World.
 *
 * @return WTNavigation a navigation object representing the requested URL load and the finally loaded URL (They may differ because of some redirects)
 */
- (WTNavigation *)loadArchitectWorldFromURL:(NSURL *)architectWorldURL withRequiredFeatures:(WTFeatures)requiredFeatures;

/**
 * Reloads the Architect World URL that was passed at last to the `-loadArchitectWorldFromURL:withRequiredFeatures` method.
 *
 * @discussion Reloading an Architect World does not produce a new `WTNavigation` object. Instead the old one is still valid but with all parameters resetted. This means that both, `isLoading` and `wasInterrupted` will represent the current Architect World reload status.
 */
- (void)reloadArchitectWorld;

/** @name Managing the WTArchitectView updates */


/**
 * Starts activity of the ARchitect view (starts UI updates of background camera, AR objects etc).
 *
 * @discussion Since version 4.1 of the Wikitude SDK, the SDK startup behaviour can be defined in more detail. It is now possible to define the camera position and camera options when the SDK starts. See WTStartupConfiguration for more information about the available options and there possible values. Most of the settings can also be set using the JS API.
 *
 * As a specific example, use the configuration object to start the SDK with an active front camera instead of the default rear cam.
 *
 * @param startupHandler A block which contains a configuration object as parameter. The WTStartupConfiguration parameter can be used to specify the startup behaviour in more detail.
 * @param completionHandler A block which provices information if the SDK could be started or not.
 */
- (void)start:(void (^)(WTStartupConfiguration *configuration))startupHandler completion:(void (^)(BOOL isRunning, NSError *error))completionHandler;

/**
 * Stops all activity of the ARchitect view (suspends UI updates of background camera, AR objects etc).
 */
- (void)stop;


/** @name Interacting with Architect Worlds */
/**
 * Executes the passed JavaScript string in the context of the currently loaded ARchitect World.
 * This can be used to pass data to the ARchitect World or to notify it of external events.
 *
 * @param javaScript A string, representing the javascript code which should be executed.
 */
- (void)callJavaScript:(NSString*)javaScript;


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


/** @name Injecting Locations */
/**
 * Injects the supplied location information. To use the injected location setUseInjectedLocation(true) has to be called.
 *
 * @param latitude The latitude that has to be simulated.
 * @param longitude The longitude that has to be simulated.
 * @param altitude The to altitude that has to be simulated.
 * @param accuracy The accuracy of the simulated location.
 */
- (void)injectLocationWithLatitude:(CLLocationDegrees)latitude longitude:(CLLocationDegrees)longitude altitude:(CLLocationDistance)altitude accuracy:(CLLocationAccuracy)accuracy;


/**
 * Injects the supplied location information. To use the injected location setUseInjectedLocation(true) has to be called.
 *
 * @param latitude The latitude that has to be simulated.
 * @param longitude The longitude that has to be simulated.
 * @param accuracy The accuracy of the simulated location.
 */
- (void)injectLocationWithLatitude:(CLLocationDegrees)latitude longitude:(CLLocationDegrees)longitude accuracy:(CLLocationAccuracy)accuracy;


/**
 * If true is supplied the injected location will be used. If false is supplied the default location provider will be used.
 *
 * @param useInjectedLocation The location simulation status
 */
- (void)setUseInjectedLocation:(BOOL)useInjectedLocation;


/**
 * True if an injected location is currently used. false if default location provider is used.
 *
 * @return Indicates, if the location provider is simulating the injected location.
 */
- (BOOL)isUsingInjectedLocation;


/** @name Manipulating Object Visibility */
/**
 * Sets the culling distance in meters. Objects in AR that are further away won’t be visible. The default value is 50000 meters (= 50 km).
 *
 * @param cullingDistance The culling distance that has to be applied to your AR objects.
 */
- (void)setCullingDistance:(float)cullingDistance;


/**
 * Retrieves the current culling distance in meters.
 *
 * @return The current culling distance, used by the SDK.
 */
- (float)cullingDistance;


/**
 * Use this method to clear all cached data and requests.
 *
 * This method clears the cache used by the webView.
 */
- (void)clearCache;


/** @name Interacting with Device Motion */
/**
 * Returns the motion manager used by the Wikitude SDK.
 *
 * @return  The CMMotionManager instance, provided in the method "InitializeWithKey:motionManager", otherwise nil;
 */
- (CMMotionManager*)motionManager;

@end
