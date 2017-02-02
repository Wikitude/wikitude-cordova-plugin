//
//  WTArchitectStartupConfiguration.h
//  WikitudeSDK
//
//  Created by Andreas Schacherbauer on 28/11/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#import "WTStartupConfiguration.h"

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
 * Defines if the underlying UIWebView scroll view is allowed to scroll horizontally/vertically or zoom.
 *
 * @Discussion This property should only be set to YES if scroll and zoom can not be disable in the Architect Worlds html/css.
 *
 * The default value is NO.
 */
@property (nonatomic, assign) BOOL                                                      disableWebViewScrollAndZoom;


/**
 * Utility method to transfer a certain Architect startup configuration to a different one.
 *
 * @Discussion Also WTStartupConfiguration specific values are transfered.
 *
 * @param sourceArchitectStartupConfiguration The startup configuration from which values are read
 * @param destinationArchitectStartupConfiguraiton The startup configuraiton to which values should be written to
 */
+ (void)transferArchitectStartupConfiguration:(WTArchitectStartupConfiguration *)sourceArchitectStartupConfiguration toArchitectStartupConfiguration:(WTArchitectStartupConfiguration *)destinationArchitectStartupConfiguration;

@end
