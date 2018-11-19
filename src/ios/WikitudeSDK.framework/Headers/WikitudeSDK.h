//
//  WikitudeSDK.h
//  WikitudeSDK
//
//  Created by Andreas Schacherbauer on 07.07.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for WikitudeSDK.
FOUNDATION_EXPORT double WikitudeSDKVersionNumber;

//! Project version string for WikitudeSDK.
FOUNDATION_EXPORT const unsigned char WikitudeSDKVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <WikitudeSDK/PublicHeader.h>
#import <WikitudeSDK/WTWikitudeTypes.h>
#import <WikitudeSDK/WTSDKBuildInformation.h>
#import <WikitudeSDK/WTAuthorizationRequestManager.h>

#import <WikitudeSDK/WTArchitectView.h>
#import <WikitudeSDK/WTArchitectViewDebugDelegate.h>
#import <WikitudeSDK/WTArchitectStartupConfiguration.h>
#import <WikitudeSDK/WTNavigation.h>
#import <WikitudeSDK/WTExternalCMMotionManagerDataAccessMode.h>

#import <WikitudeSDK/WTArchitectView+Plugins.h>
#import <WikitudeSDK/Frame.h>
#import <WikitudeSDK/Matrix4.h>
#import <WikitudeSDK/Geometry.hpp>
#import <WikitudeSDK/FrameColorSpace.h>
#import <WikitudeSDK/RecognizedTarget.h>
#import <WikitudeSDK/InterfaceOrientation.h>
#import <WikitudeSDK/Plugin.h>
#import <WikitudeSDK/InputRenderSettings.h>
#import <WikitudeSDK/InputFrameSettings.h>
#import <WikitudeSDK/InputPlugin.h>
#import <WikitudeSDK/RenderingAPI.h>
#import <WikitudeSDK/RenderingContext.h>
#import <WikitudeSDK/RecognizedTargetsBucket.h>
#import <WikitudeSDK/PositionableWrapper.h>
