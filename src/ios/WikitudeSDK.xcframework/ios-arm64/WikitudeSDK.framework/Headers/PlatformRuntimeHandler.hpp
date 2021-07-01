//
//  PlatformRuntimeHandler.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 24.10.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef PlatformRuntimeHandler_hpp
#define PlatformRuntimeHandler_hpp

#ifdef __cplusplus

#include <functional>

#include "Geometry.hpp"


namespace wikitude::sdk {

        using SurfaceSizeChangedHandler = std::function<void(const sdk::Size<int> surfaceSize_)>;
        using CameraToSurfaceScalingChangedHandler = std::function<void(const sdk::Scale2D<float> cameraToSurfaceScaling_)>;
        using CameraToSurfaceAngleChangedHandler = std::function<void(const float cameraToSurfaceAngle_)>;
}

#endif /* __cplusplus */

#endif /* PlatformRuntimeHandler_hpp */
