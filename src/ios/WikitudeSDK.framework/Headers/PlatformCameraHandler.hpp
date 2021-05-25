//
//  PlatformCameraHandler.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 22.10.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef PlatformCameraHandler_hpp
#define PlatformCameraHandler_hpp

#ifdef __cplusplus

#include <functional>

#include "Geometry.hpp"
#include "CameraPosition.hpp"


namespace wikitude::sdk {

        class ManagedCameraFrame;
        using CameraFrameSizeChangedHandler = std::function<void(const sdk::Size<int>& cameraFrameSize_)>;
        using CameraVerticalFieldOfViewChangedHandler = std::function<void(const float verticalFieldOfView_)>;
        using CameraToSurfaceCorrectedFieldOfViewChangedHandler = std::function<void(const float cameraToSurfaceCorrectedFieldOfView_)>;
        using CameraPositionChangedHandler = std::function<void(CameraPosition cameraPosition_)>;
        using CameraDataOutputHandler = std::function<void(ManagedCameraFrame& managedCameraFrame_)>;

        using CameraVerticalFieldOfViewCorrectionHandler = std::function<float(float originalVerticalFieldOfView_)>;
}

#endif /* __cplusplus */

#endif /* PlatformCameraHandler_hpp */
