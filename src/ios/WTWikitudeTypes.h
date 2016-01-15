//
//  WTArchitectTypes.h
//  WikitudeSDK
//
//  Created by Andreas Schacherbauer on 15/05/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#ifndef WikitudeSDK_WTWikitudeTypes_h
#define WikitudeSDK_WTWikitudeTypes_h

#define WT_DEPRECATED_SINCE(__version__, __msg__) __attribute__((deprecated("Deprecated in Wikitude SDK " #__version__ ". " __msg__)))

/**
 *
 * WTFeatures define which features of the Wikitude SDK are used in an ARchitect World. Based on features, different device capabilities are required.
 *
 * By specifying the required features when loading an ARchitect World, the best performance can be achieved.
 */
typedef NS_OPTIONS(NSUInteger, WTFeatures) {
    
    /**
     * Specifies that 2d tracking is used in an ARchitect World
     * This feature requires access to the camera. When using the 'NSCameraUsageDescription' key in the *-Info.plist, a custom text can be displayed when the camera access alert is shown.
     */
    WTFeature_2DTracking = 1 << 0,
    
    /**
     * Specifies that 3d tracking is used in an ARchitect World
     * This feature requires access to the camera and the gyroscope. When using the 'NSCameraUsageDescription' key in the *-Info.plist, a custom text can be displayed when the camera access alert is shown.
     */
    WTFeature_3DTracking = 1 << 1,
    
    /**
     * Specifies that geo based augmented reality is used where objects are placed on certain locations by providing latitude/longitude values.
     * This feature requires access to the camera and the user location so please make sure to specify a value for the 'NSLocationWhenInUseUsageDescription' key in your *-Info.plist when using the SDK on iOS 8 or later.
     */
    WTFeature_Geo = 1 << 2
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


#endif
