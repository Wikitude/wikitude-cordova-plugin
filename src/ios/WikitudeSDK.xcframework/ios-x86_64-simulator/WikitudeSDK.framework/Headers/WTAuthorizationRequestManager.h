//
//  WTAuthorizationRequestManager.h
//  WikitudeSDK
//
//  Created by Andreas Schacherbauer on 11/12/2016.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <AVFoundation/AVCaptureDevice.h>
#import <CoreLocation/CLLocationManager.h>
#import <Photos/PHPhotoLibrary.h>

#import "WTWikitudeTypes.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * In case not all restriced APIs are authorized, the NSError's userInfo contains a dictionary containing more information about which APIs are not authorized and why. 
 * This key can be used to get this dictionary from the userInfo object.
 */
extern NSString * const kWTUnauthorizedAppleiOSSDKAPIsKey;


/**
 * WTAuthorizationRequestManager class
 *
 * Some Apple APIs need authorization from the end user in order to be used.
 * This class can be used to request those required authorizations for restricted Apple APIs.
 *
 * Restricted Apple APIs are:
 * * Camera access
 * * Location access (GPS access)
 * * Camera Roll album access
 *
 * Without access to those APIs, the Wikitude SDK might not be able to work properly.
 */
@interface WTAuthorizationRequestManager : NSObject

/**
 * YES if there is an authorization process currently running, NO otherwise.
 */
@property (nonatomic, assign) BOOL              isRequestingRestrictedAppleiOSSDKAPIAuthorization;

/**
 * Use this method to convert WTFeatures into a NSOrderedSet of WTRestrictedAppleiOSSDKAPI (NSNumber is used as enums can't be used with Foundation container classes).
 * Depending on the features passed, all relevant WTRestrictedAppleiOSSDKAPIs are determined and returned in an ordered set.
 *
 * @param requiredFeatures A combination of WTFeatures that are intended to be used.
 *
 * @return NSOrderedSet<NSNumber *> a ordered set of WTRestrictedAppleiOSSDKAPIs based on the features passed as requiredFeatures
 *
 * @discussion It is possible to change the order of elements in the returned set in order to customize the sequence of which authorization dialogs are shown.
 */
+ (NSOrderedSet<NSNumber *> *)restrictedAppleiOSSDKAPIAuthorizationsForRequiredFeatures:(WTFeatures)requiredFeatures;

/**
 * By calling this method, all WTRestrictedAppleiOSSDKAPIs that are passed in the set are requested. The order of the elements in the set determine the sequence in which individual authorization dialogs are shown.
 *
 * @param requiredAppleiOSSDKAPIAuthorizations The restricted Apple APIs for which authorization is asked for.
 * @param completionHandler The block that is called once all authorization states are determined. This block is guaranteed to be called exactly once.
 */
- (void)requestRestrictedAppleiOSSDKAPIAuthorization:(NSOrderedSet<NSNumber *> *)requiredAppleiOSSDKAPIAuthorizations completion:(void (^)(BOOL success, NSError *error))completionHandler;

@end


/**
 * This class category can be used to generate pretty error logs or user interface dialogs from the NSError object given in `-requestRestrictedAppleiOSSDKAPIAuthorization:completion` completion handler.
 */
@interface WTAuthorizationRequestManager (ErrorMessageFormatting)

/**
 * Converts the keys from the `kWTUnauthorizedAppleiOSSDKAPIsKey` dictionary into human readable string representations.
 *
 * @param unauthorizedAppleiOSSDKAPI One of the string keys of the `kWTUnauthorizedAppleiOSSDKAPIsKey` dictionary.
 *
 * @return String * A human readable string representation for one of the WTRestrictedAppleiOSSDKAPI constants.
 */
+ (NSString *)humanReadableDescriptionForUnauthorizedAppleiOSSDKAPI:(NSString *)unauthorizedAppleiOSSDKAPI;

/**
 * Converts a given value from the `kWTUnauthorizedAppleiOSSDKAPIsKey` dictionary into human readable string representations.
 *
 * @param authorizationStatus One of the NSInteger values of the `kWTUnauthorizedAppleiOSSDKAPIsKey` dictionary.
 * @param unauthorizedAppleiOSSDKAPI One of the string keys of the `kWTUnauthorizedAppleiOSSDKAPIsKey` dictionary.
 *
 * @return String * A human readable string representation for one of the authorization status enums that represent a restricted API.
 *
 * @discussion This method is just a convenience method that calls either
 *  - stringFromAVFoundationAuthenticationStatus
 *  - stringFromCoreLocationAuthenticationStatus or
 *  - stringFromPhotosAuthenticationStatus
 * based on the given `unauthorizedAppleiOSSDKAPI` parameter.
 */
+ (NSString *)stringFromAuthorizationStatus:(NSInteger)authorizationStatus forUnauthorizedAppleiOSSDKAPI:(NSString *)unauthorizedAppleiOSSDKAPI;

/**
 * Converts the given AVAuthorizationStatus constant into a string.
 *
 * @param authorizationStatus one of the AVAuthorizationStatus enum constants.
 *
 * @return NSString * A string representation of the given AVAuthorizationStatus constant.
 */
+ (NSString *)stringFromAVFoundationAuthenticationStatus:(AVAuthorizationStatus)authorizationStatus;

/**
 * Converts the given CLAuthorizationStatus constant into a string.
 *
 * @param authorizationStatus one of the CLAuthorizationStatus enum constants.
 *
 * @return NSString * A string representation of the given CLAuthorizationStatus constant.
 */
+ (NSString *)stringFromCoreLocationAuthenticationStatus:(CLAuthorizationStatus)authorizationStatus;

/**
 * Converts the given PHAuthorizationStatus constant into a string.
 *
 * @param authorizationStatus one of the PHAuthorizationStatus enum constants.
 *
 * @return NSString * A string representation of the given PHAuthorizationStatus constant.
 */
+ (NSString *)stringFromPhotosAuthenticationStatus:(PHAuthorizationStatus)authorizationStatus;

@end

NS_ASSUME_NONNULL_END
