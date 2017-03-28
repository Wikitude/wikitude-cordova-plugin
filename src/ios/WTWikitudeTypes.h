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
     * Specifies that image recognition and tracking is used in an ARchitect World
     * This feature requires access to the camera.
     */
    WTFeature_ImageTracking = 1 << 0,

    /**
     * Specifies that instant tracking is used in an ARchitect World
     * This feature requires access to the camera.
     */
    WTFeature_InstantTracking = 1 << 2,

    /** Deprecated, please use WTFeature_ImageTracking instead. */
    WTFeature_2DTracking WT_DEPRECATED_SINCE(6.0.0, "Use WTFeature_ImageTracking instead.") = WTFeature_ImageTracking,
    
    WTFeature_3DTracking = 1 << 5,

    /**
     * Specifies that geo based augmented reality is used where objects are placed on certain locations by providing latitude/longitude values.
     * This feature requires access to the camera and the user location.
     */
    WTFeature_Geo = 1 << 6,

    /**
     * Specifies that screenshots taken from the WTArchitectView are imported into the Photos.app Camera Roll album.
     */
    WTFeature_PhotoLibraryScreenshotImport = 1 << 7
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
 * The WTRenderingAPI can be used choose which OpenGL version should be used by the SDK for rendering
 *
 */
typedef NSString * WTRenderingAPI NS_EXTENSIBLE_STRING_ENUM;

/**
 * Specifies that an OpenGL ES 2 context should be used by the SDK for rendering
 */
FOUNDATION_EXPORT WTRenderingAPI const WTRenderingAPI_OpenGL_ES_2;

/**
 * Specifies that an OpenGL ES 3 context should be used by the SDK for rendering
 */
FOUNDATION_EXPORT WTRenderingAPI const WTRenderingAPI_OpenGL_ES_3;

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
 *
 * WTCaptureDeviceResolution can be used to define the desired capture device resolution.
 *
 */
typedef NS_ENUM(NSUInteger, WTCaptureDeviceResolution){
    
    /** The captureSessionPreset will be set to AVCaptureSessionPreset640x480. */
    WTCaptureDeviceResolution_SD_640x480            = 1,
    
    /** The captureSessionPreset will be set to AVCaptureSessionPreset1280x720. */
    WTCaptureDeviceResolution_HD_1280x720           = 2,
    
    /** The captureSessionPreset will be set to AVCaptureSessionPreset1920x1080. */
    WTCaptureDeviceResolution_FULL_HD_1920x1080     = 3,
    
    /** The captureSessionPreset will be set to AVCaptureSessionPreset640x480 on 32-bit devices and to AVCaptureSessionPreset1920x1080 on 64-bit devices. */
    WTCaptureDeviceResolution_AUTO                  = 4
};

/**
 * 
 * WTRestrictedAppleiOSSDKAPI represents Apple APIs that need to be authorized by the end user in order to access them.
 *
 * These constants represent APIs that are potentially used by the Wikitude SDK, depending on the features that are used.
 *
 */
typedef NS_ENUM(NSUInteger, WTRestrictedAppleiOSSDKAPI) {
    /** 
     * Represents access to the device camera.
     * Please note that the 'NSCameraUsageDescription' key needs to be defined in the applications *-Info.plist.
     */
    WTRestrictedAppleiOSSDKAPI_Camera = 0,

    /** 
     * Represents access to the current GPS position of the device 
     * Please note that the 'NSLocationWhenInUseUsageDescription' key needs to be defined in the applications *-Info.plist.
     */
    WTRestrictedAppleiOSSDKAPI_Location,

    /** Represents access to the Camera Roll album in Photos.app */
    WTRestrictedAppleiOSSDKAPI_PhotoLibrary
};

#endif
