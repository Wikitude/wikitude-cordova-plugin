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
#import <WikitudeSDK/WTDeprecation.h>
#import <WikitudeSDK/WTSDKBuildInformation.h>
#import <WikitudeSDK/WTAuthorizationRequestManager.h>

#import <WikitudeSDK/WTArchitectView.h>
#import <WikitudeSDK/WTArchitectViewDebugDelegate.h>
#import <WikitudeSDK/WTArchitectStartupConfiguration.h>
#import <WikitudeSDK/WTNavigation.h>
//#import <WikitudeSDK/WTExternalCMMotionManagerDataAccessMode.h>

#import <WikitudeSDK/ArchitectPlugin.hpp>
#import <WikitudeSDK/CameraFrame.hpp>
#import <WikitudeSDK/CameraFrameInputPluginModule.hpp>
#import <WikitudeSDK/CameraFramePlane.hpp>
#import <WikitudeSDK/CameraParameters.hpp>
#import <WikitudeSDK/CameraPosition.hpp>
#import <WikitudeSDK/ColorSpace.hpp>
#import <WikitudeSDK/CompilerAttributes.hpp>
#import <WikitudeSDK/DepthDataFormat.hpp>
#import <WikitudeSDK/DeviceMotionInputPluginModule.hpp>
#import <WikitudeSDK/Error.hpp>
#import <WikitudeSDK/ErrorHandling.hpp>
#import <WikitudeSDK/Geometry.hpp>
#import <WikitudeSDK/ImageTarget.hpp>
#import <WikitudeSDK/ImageTrackingPluginModule.hpp>
#import <WikitudeSDK/InstantTarget.hpp>
#import <WikitudeSDK/InstantTrackingPluginModule.hpp>
#import <WikitudeSDK/InstantTrackingState.hpp>
#import <WikitudeSDK/InterfaceOrientation.h>
#import <WikitudeSDK/InitializationPose.hpp>
#import <WikitudeSDK/JavaScriptPluginModule.hpp>
#import <WikitudeSDK/ManagedCameraFrame.hpp>
#import <WikitudeSDK/Matrix4.hpp>
#import <WikitudeSDK/MetalRenderingObjects.h>
#import <WikitudeSDK/MetalRenderingPluginModule.hpp>
#import <WikitudeSDK/OpenGLESRenderingPluginModule.hpp>
#import <WikitudeSDK/ObjectTarget.hpp>
#import <WikitudeSDK/ObjectTrackingPluginModule.hpp>
#import <WikitudeSDK/Plane.hpp>
#import <WikitudeSDK/PlaneType.hpp>
#import <WikitudeSDK/PlatformCameraHandler.hpp>
#import <WikitudeSDK/PlatformRuntimeHandler.hpp>
#import <WikitudeSDK/PlatformTrackingHandler.hpp>
#import <WikitudeSDK/Plugin.hpp>
#import <WikitudeSDK/PluginModule.hpp>
#import <WikitudeSDK/PluginParameterCollection.hpp>
#import <WikitudeSDK/Positionable.hpp>
#import <WikitudeSDK/RecognizedTargetsBucket.hpp>
#import <WikitudeSDK/RenderingAPI.hpp>
#import <WikitudeSDK/RenderingParameters.hpp>
#import <WikitudeSDK/RuntimeParameters.hpp>
#import <WikitudeSDK/RenderableCameraFrame.hpp>
#import <WikitudeSDK/RenderableCameraFrameBucket.hpp>
#import <WikitudeSDK/RenderingPluginModule.hpp>
#import <WikitudeSDK/SensorEvent.hpp>
#import <WikitudeSDK/State.hpp>
#import <WikitudeSDK/Timestamp.hpp>
#import <WikitudeSDK/TrackingParameters.hpp>
#import <WikitudeSDK/TrackingPluginModule.hpp>
#import <WikitudeSDK/Unit.h>
#import <WikitudeSDK/Vector3.hpp>
