//
//  WTRuntimeConfiguration.h
//  WikitudeSDK
//
//  Copyright (c) 2014 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>



/**
 * WTStartupConfiguration represents configuration values that are used during the SDK startup.
 * If any of the defined properties can not be applied, an error is given to the debug delegate and also an error message is printed in the Xcode console.
 */
@interface WTStartupConfiguration : NSObject


/**
 * The capture device position that should be used when the SDK starts.
 * If the position is not supported by the current device, then a default position is used.
 */
@property (nonatomic, assign) AVCaptureDevicePosition               captureDevicePosition;


/**
 * The capture device focus range restriction that should be used when the SDK starts.
 * If the given focus range restriction is not supported by the current device, then this property is ignored.
 *
 * @discussion Please refer to the official AVCaptureAutoFocusRangeRestriction documentation for more information.
 */
@property (nonatomic, assign) AVCaptureAutoFocusRangeRestriction    captureDeviceFocusRangeRestriction;

/**
 * Specifies if the capture device output should be mirrored or not.
 *
 * The default value is YES
 *
 * @warning This property is only available for AVCaptureDevicePositionFront. All other camera positions ignore this option.
 */
@property (nonatomic, assign) BOOL                                  videoMirrored;

@end
