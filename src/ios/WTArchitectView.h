//
//  WikitudeArchitectSDK.h
//  WikitudeArchitectSDK
//
//  Copyright (c) 2012 Wikitude. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>


#define WT_DEPRECATED_SINCE(__version__, __msg__) __attribute__((deprecated("Deprecated in Wikitude SDK " #__version__ ". " __msg__)))


@protocol WTScreenshotSaver;

@class CMMotionManager;
@class WTArchitectView;


extern NSString * const kWTScreenshotBundleDirectoryKey;
extern NSString * const kWTScreenshotSaveModeKey;
extern NSString * const kWTScreenshotCaptureModeKey;
extern NSString * const kWTScreenshotImageKey;

/**
 *
 * The WTARMode is used to specify which type of augmented reality is used in an ARchitect World. Based on the ARMode, different device capabilities are required and the -isDeviceSupported: method returns different results.
 *
 * When only image recognition Worlds are loaded, more devices are supported because e.g. the iPod touch 5th gen is missing an compass and can therefore not support geo augmented reality.
 *
 */
typedef NS_ENUM(NSUInteger, WTAugmentedRealityMode){
    /** The ARchitect World is using both, geo augmented reality and image recognition */
    WTAugmentedRealityMode_Geo = 1,
    
    /** The ARchitect World is only using image recongnition. */
    WTAugmentedRealityMode_IR,
    
    /** A combinded mode for mixed ARchitect Worlds */
    WTAugmentedRealityMode_Both
};

/**
 *
 * The WTScreenshotCaptureMode defines if the screenshot should also include the web view (The Html hud) or only the cam content.
 *
 */
typedef NS_ENUM(NSUInteger, WTScreenshotCaptureMode){
    
    /** Only the camera content with all augmentations will be captured */
    WTScreenshotCaptureMode_Cam,
    
    /** Also the web view is composed into the final screenshot */
    WTScreenshotCaptureMode_CamAndWebView
};


/**
 *
 * The WTScreenshotSaveMode can be used to defines the output location of the generated screenshot.
 *
 */
typedef NS_ENUM(NSUInteger, WTScreenshotSaveMode){
    
    /** The generated screenshot will be added to the Camera Roll in the Photos application */
    WTScreenshotSaveMode_PhotoLibrary       = 1,
    
    /** The generated screenshot will be saved in the application bundle. File name and path can be passed into the -captureScreenWithMode:usingSaveMode:saveOptions:context: method by the context dictionary. The key for the NSString object is kWTScreenshotBundleDirectoryKey. */
    WTScreenshotSaveMode_BundleDirectory    = 2,
    
    /** The generated screenshot will be passed to the -architectView:didCaptureScreenWithContext: context dictionary. The key is  kWTScreenshotImageKey. */
    WTScreenshotSaveMode_Delegate           = 3
};


/**
 *
 * WTScreenshotSaveOption are used to define specific instructions that should be considered before or after the screenshot saving.
 *
 * The values can be chained together using the | operator.
 *
 */
typedef NS_OPTIONS(NSUInteger, WTScreenshotSaveOptions){
    
    /** Independent of the save mode, the delegate method -architectView:didCaptureScreenWithContext: will be called. The context dictionary contains all informations regarding capture and save mode. */
    WTScreenshotSaveOption_CallDelegateOnSuccess        = 1 << 0,
    
    /** This option is only considered when using the save mode WTScreenshotSaveMode_BundleDirectory. It defines if a existing screenshot with the same name should be replaced or not. When a file with the same name already exists and the overwriting option is not set, the screen capture will fail and the delegate method -architectView:didFailCaptureScreenWithError will be invoked. */
    WTScreenshotSaveOption_SavingWithoutOverwriting     = 1 << 1,
    
    /** No options should be considered during the screenshot saving. */
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
 * This method is called when the provided architect world url finished loading.
 *
 * @param architectView The ArchitectView which finished loading.
 *
 * @param url The URL that is loaded.
 */
- (void)architectView:(WTArchitectView *)architectView didFinishLoad:(NSURL *)url;


/**
 * This method is called when the provided architect world url failed to load.
 *
 * @param architectView The ArchitectView which failed to load the url.
 *
 * @param error An NSError object containing more informations why the load did fail.
 */
- (void)architectView:(WTArchitectView *)architectView didFailLoadWithError:(NSError *)error;


/** @name ARchitect World */
/**
 * Supplied URL was called and should be opened. URL starts with architectsdk:// protocol prefix and is otherwise custom to the ARchitect World that requests it.
 *
 * @param architectView The WTArchitectView object which invoked the url.
 *
 * @param url The url which was called in javascript.
 */
- (void)architectView:(WTArchitectView *)architectView invokedURL:(NSURL *)url;


/** @name Screen capturing */
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
+ (BOOL)isDeviceSupportedForAugmentedRealityMode:(WTAugmentedRealityMode)supportedARMode;


/** @name Accessing ARchitect settings */
/**
 * Use this method to get the current ARchitect version number
 *
 * @return The current available ARchitect verison within the SDK.
 */
+ (NSString *)versionNumber;


/** @name Initializing a WTArchitectView Object */
/**
 * Returns a newly initialized architect view with the given motion manager object, capable of running ARchitect Worlds in the given augmented reality mode.
 *
 * @param frame A CGRect describing the size of the view
 * @param motionManagerOrNil  A CMMotionManager object which should be used from the SDK. If nil is given, the SDK will create there own CMMotionManager object.
 * @param augmentedRealityMode The ARMode which describes the ARchitectWorld best.
 *
 * @return A newly initialized WTArchitectView object.
 *
 * @discussion This is the designated initializer for this class.
 *
 * If your ARchitect World is only using image recognition, it is sufficient to pass WTAugmentedRealityMode_IR as augmentedRealityMode. Doing so will disable all location relevant components of the SDK.
 *
 * @warning If the architect view object is initialized with WTAugmentedRealityMode_IR, it is not possible to load an ARchitect World correctly that uses ARGeoObjects or ARGeoLocations objects.
 *
 */
- (id)initWithFrame:(CGRect)frame motionManager:(CMMotionManager *)motionManagerOrNil augmentedRealityMode:(WTAugmentedRealityMode)augmentedRealityMode;


/**
 * Initializes the ARchitectView with the specified license key and motion manager that will be shared by the Wikitude SDK and the third party application.
 * If a motion manager instance is passed, it will be set to Wikitudes preferred settings (update intervals etc.)
 * The motion manager argument may be nil in which case Wikitude creates and manages its own motion manager instance.
 *
 * @param key Your developer key, provided with your licence information.
 * @param motionManager The CMMotionManager instance which should be used from the SDK.
 *
 * @deprecated since version 3.2.2
 */
- (void)initializeWithKey:(NSString*)key motionManager:(CMMotionManager*)motionManager WT_DEPRECATED_SINCE(3.2.1, "Use -setLicenseKey: instead.");


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
 * Replaces the existing content of the ArchitectView with the one from the supplied URL.
 *
 *  @param architectWorldUrl The url that points to the Architect world. This can be eather a local .html file or a url, pointing to a file on a server or to your dropbox.
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
- (void)injectLocationWithLatitude:(CLLocationDegrees)latitude longitude:(CLLocationDegrees)longitude altitude:(CLLocationDistance)altitude accuracy:(CLLocationAccuracy)accuracy;


/**
 * Injects the supplied location information. To use the injected location setUseInjectedLocation(true) has to be called.
 * @param latitude The latitude that has to be simulated.
 * @param longitude The longitude that has to be simulated.
 * @param accuracy The accuracy of the simulated location.
 */
- (void)injectLocationWithLatitude:(CLLocationDegrees)latitude longitude:(CLLocationDegrees)longitude accuracy:(CLLocationAccuracy)accuracy;


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
- (NSString *)versionNumber WT_DEPRECATED_SINCE(3.2.1, "Use +versionNumer instead.");


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
