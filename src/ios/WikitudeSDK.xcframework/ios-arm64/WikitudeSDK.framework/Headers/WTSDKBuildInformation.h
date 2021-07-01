//
// WTSDKBuildInformation.h
// Wikitude SDK
//
// Copyright (c) 2016 Wikitude. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>


/**
 * Use this class to get more information about this specific version of the SDK. 
 *
 * @Discussion Usually this class is used if Wikitude support is contacted
 */
@interface WTSDKBuildInformation : NSObject

/**
 * The build date of the SDK
 */
@property(nonatomic, copy, readonly) NSString *buildDate;

/**
 * The build number of the SDK
 */
@property(nonatomic, copy, readonly) NSString *buildNumber;

/**
 * The build configuration that was used to build this SDK
 */
@property(nonatomic, copy, readonly) NSString *buildConfiguration;

/**
 * This method can be used to get a JSON representation of the above properties
 */
- (NSString *)toJSONString;

@end
