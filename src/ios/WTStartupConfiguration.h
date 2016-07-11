//
//  WTRuntimeConfiguration.h
//  WikitudeSDK
//
//  Copyright (c) 2014 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <OpenGLES/gltypes.h>


static inline CMTime WTMakeTargetFrameRate60FPS()
{
    return CMTimeMake(1, 60);
}

static inline CMTime WTMakeTargetFrameRate30FPS()
{
    return CMTimeMake(1, 30);
}



/**
 * WTStartupConfiguration represents configuration values that are used during the SDK startup.
 * If any of the defined properties can not be applied, an error is given to the debug delegate and also an error message is printed in the Xcode console.
 */
@interface WTStartupConfiguration : NSObject

/**
 * The capture device preset that should be used when the SDK starts.
 * If the preset is not supported by the current device, then a default preset is used.
 */
@property (nonatomic, strong) NSString                              *captureDevicePreset;


/**
 * The capture device position that should be used when the SDK starts.
 * If the position is not supported by the current device, then a default position is used.
 */
@property (nonatomic, assign) AVCaptureDevicePosition               captureDevicePosition;


/**
 * The capture device focus mode that should be used when the SDK starts.
 * If the given focus mode is not supported by the current device, then a default focus mode is used.
 *
 * @warning Most front cameras do not support a specific focus mode. They will always fall back to a continuous focus mode
 */
@property (nonatomic, assign) AVCaptureFocusMode                    captureDeviceFocusMode;


/**
 * The capture device focus range restriction that should be used when the SDK starts.
 * If the given focus range restriction is not supported by the current device, then this property is ignored.
 *
 * @discussion Please refer to the official AVCaptureAutoFocusRangeRestriction documentation for more information.
 */
@property (nonatomic, assign) AVCaptureAutoFocusRangeRestriction    captureDeviceFocusRangeRestriction;


/**
 * The target frame rate at which the SDK should run.
 *
 * @discussion Use the convenience function WTMakeTargetFrameRate60FPS or WTMakeTargetFrameRate30FPS to construct a correct CMTime struct for a desired frame rate. The default value is 30 FPS.
 * @warning If the given frame rate can not be applied for the current device, the default value will be used.
 */
@property (nonatomic, assign) CMTime                                targetFrameRate;


/**
 * The target texture that should be used to draw the camera frame onto.
 *
 * @default -1
 * @discussion You should only use this property if your application has already setup a fixed rendering pipeline and wants the Wikitude SDK to draw the camera frame onto a very specific OpenGL ES 2 texture. Under normal circumstances, WTRenderingMode_External should be used if the Wikitude SDK should draw the camera frame in an already existing rendering environment.
 */
@property (nonatomic, assign) GLuint                                cameraRenderingTargetTexture;


/**
 * Defines if the iOS SDK device sensor calibration display should be shown or not in case device sensors calibration is needed.
 *
 * @default NO
 * @discussion For iOS 9, the current view controller will receive calls to -viewWillDisappear:/-viewWillAppear: in case the system calibration screen is shown. Please make sure that the Wikitude SDK is not stopped/started as this would constantly switch between the calibration view and Wikitude SDK view. Implement the Wikitude SDK delegate method -: in order to observe the calibration status and to not pause the Wikitude SDK during that time.
 */
@property (nonatomic, assign) BOOL                                  shouldUseSystemDeviceSensorCalibrationDisplay;

@end
