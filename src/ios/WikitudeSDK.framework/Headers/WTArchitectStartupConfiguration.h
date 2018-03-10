//
//  WTArchitectStartupConfiguration.h
//  WikitudeSDK
//
//  Created by Andreas Schacherbauer on 28/11/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#import "WTStartupConfiguration.h"

#import <UIKit/UIScrollView.h>
#import <UIKit/UIDataDetectors.h>
#import <CoreLocation/CLLocation.h>


/**
 * WTArchitectStartupConfiguration represents Wikitude iOS SDK (JS API) specific configuration values taht are used during the SDK starup.
 */
@interface WTArchitectStartupConfiguration : WTStartupConfiguration

/**
 * The location accuracy that should be used when Geo augmented reality is used. Please refer to the CLLocationAccuracy documentation for more information about possible values.
 *
 * The default value is kCLLocationAccuracyNearestTenMeters
 */
@property (nonatomic, assign) CLLocationAccuracy                                        desiredLocationAccuracy;

/**
 * The location distance filter that should be used when Geo augmented reality is used. Please refer to the CLLocationDistance documentation for more information about possible values.
 *
 * The default value is kCLDistanceFilterNone
 */
@property (nonatomic, assign) CLLocationDistance                                        desiredLocationDistanceFilter;

/**
 * The heading filter that should be used when Geo augmented reality is used and the gyro can not be used (iOS 10.0 - 10.1)
 *
 * The default value is kCLHeadingFilterNone
 */
@property (nonatomic, assign) CLLocationDegrees                                         desiredHeadingFilter;

/**
 * A Boolean value that determines whether pressing on a link displays a preview of the destination for the link.
 *
 * Please refer to the UIWebView documentation for more information
 *
 * The default value is NO
 */
@property (nonatomic, assign) BOOL                                                      webViewAllowsLinkPreview;

/**
 * A Boolean value indicating whether web content can programmatically display the keyboard.
 *
 * Please refer to the UIWebView documentation for more information
 *
 * The default value is YES
 */
@property (nonatomic, assign) BOOL                                                      webViewKeyboardDisplayRequiresUserAction;

/**
 * The types of data converted to clickable URLs in the web view’s content.
 *
 * Please refer to the UIWebView documentation for more information
 */
@property (nonatomic, assign) UIDataDetectorTypes                                       webViewDataDetectorTypes;

/**
 * A Boolean value that determines whether HTML5 videos play inline or use the native full-screen controller.
 *
 * Please refer to the UIWebView documentation for more information
 *
 * The default value is NO on iPhone and YES on iPad
 */
@property (nonatomic, assign) BOOL                                                      webViewAllowsInlineMediaPlayback;

/**
 * A Boolean value that determines whether HTML5 videos can play automatically or require the user to start playing them.
 *
 * Please refer to the UIWebView documentation for more information
 *
 * The default value is YES
 */
@property (nonatomic, assign) BOOL                                                      webViewMediaPlaybackRequiresUserAction;

/**
 * A Boolean value that determines whether Air Play is allowed from this view.
 *
 * Please refer to the UIWebView documentation for more information
 *
 * The default value is YES
 */
@property (nonatomic, assign) BOOL                                                      webViewMediaPlaybackAllowsAirPlay;

/**
 * A Boolean value that determines whether Picture in Picture playback is allowed from this view.
 *
 * Please refer to the UIWebView documentation for more information
 *
 * The default value is YES for devices that support PiP and NO on all other devices
 */
@property (nonatomic, assign) BOOL                                                      webViewAllowsPictureInPictureMediaPlayback;

/**
 * Defines if the underlying UIWebView scroll view is allowed to scroll horizontally/vertically or zoom.
 *
 * @Discussion This property should only be set to YES if scroll and zoom can not be disable in the Architect Worlds html/css.
 *
 * The default value is NO.
 */
@property (nonatomic, assign) BOOL                                                      disableWebViewScrollAndZoom;

/**
 * Defines the contentInsetAdjustment that is used by the web views scroll view.
 *
 * Please refer to the UIScrollView documentation for more information
 *
 * The default value is UIScrollViewContentInsetAdjustmentNever so that the SDK behaves the same on iOS 11 as it did on iOS 10 and below.
 */
@property (nonatomic, assign) UIScrollViewContentInsetAdjustmentBehavior                webViewsScrollViewContentInsetAdjustmentBehavior API_AVAILABLE(ios(11.0));

/**
 * Utility method to transfer a certain Architect startup configuration to a different one.
 *
 * @Discussion Also WTStartupConfiguration specific values are transfered.
 *
 * @param sourceArchitectStartupConfiguration The startup configuration from which values are read
 * @param destinationArchitectStartupConfiguration The startup configuraiton to which values should be written to
 */
+ (void)transferArchitectStartupConfiguration:(WTArchitectStartupConfiguration *)sourceArchitectStartupConfiguration toArchitectStartupConfiguration:(WTArchitectStartupConfiguration *)destinationArchitectStartupConfiguration;

@end
