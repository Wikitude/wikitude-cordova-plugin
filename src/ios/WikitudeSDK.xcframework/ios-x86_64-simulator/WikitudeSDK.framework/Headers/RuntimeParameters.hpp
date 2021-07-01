//
//  RuntimeParameters.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 24.10.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef RuntimeParameters_hpp
#define RuntimeParameters_hpp

#ifdef __cplusplus

#include "PlatformRuntimeHandler.hpp"
#include "CompilerAttributes.hpp"


namespace wikitude::universal_sdk {
    class RuntimeParametersInternal;
}

namespace wikitude::sdk {

        /**
         * @brief RuntimeParameters provide access to runtime specific information.
         *
         * Calling getter methods will always return the most recent data available.
         *
         * PlatformComponent developer typically create a subclass and add more getter that are related to platform specific information.
         */
        class WT_EXPORT_API RuntimeParameters {
        public:

            /**
             * @brief This method returns the most recent surface size that is available.
             *
             * Surface size is considered to be the size of a rendering UI component that renders the camera image and/or augmentations.
             *
             * @return The last know surface size in pixel.
             */
            sdk::Size<int> getSurfaceSize() const;

            /**
             * @brief Use this method to register a handler function that is called every time the surface size changes.
             *
             * @param surfaceSizeChangedHandler_ represents a lambda expression or method that is called in case a new surface size is reported.
             */
            void addSurfaceSizeChangedHandler(std::uintptr_t handleOwner_, SurfaceSizeChangedHandler surfaceSizeChangedHandler_);

            void removeSurfaceSizeChangedHandler(std::uintptr_t handleOwner_);

            /**
             * @brief This method returns the most recent scaling information between the last known surface size and camera frame size.
             *
             * This information is usefull to render the camera frame 'aspect fill' into the rendering UI component.
             *
             * @return The most recent scaling value in pixel.
             */
            sdk::Scale2D<float> getCameraToSurfaceScaling();

            /**
             * @brief Use this method to register a handler function that is called every time the camera to surface scaling changes.
             *
             * @param cameraToSurfaceScalingChangedHandler_ represents a lambda expression or method that is called in case a new camera to surface scaling is calculated.
             */
            void addCameraToSurfaceScalingChangedHandler(std::uintptr_t handleOwner_, CameraToSurfaceScalingChangedHandler cameraToSurfaceScalingChangedHandler_);

            void removeCameraToSurfaceScalingChangedHandler(std::uintptr_t handleOwner_);


            /**
             * @brief This method returns the most recent angle between the camera and the render surface that is available.
             *
             * The camera to surface angle can be used to rotate augmentations or other digital content that is rendered on screen.
             *
             * @return The most recent angle between the camera and the rendering surface in degree.
             */
            float getCameraToSurfaceAngle() const;

            /**
             * @brief Use this method to register a handler function that is called every time the angle between the camera and the rendering surface changes.
             *
             * @param cameraToSurfaceAngleChangedHandler_ represents a lambda expression or method that is called in case a new angle between camera and rendering surface was reported.
             */
            void addCameraToSurfaceAngleChangedHandler(std::uintptr_t handleOwner_, CameraToSurfaceAngleChangedHandler cameraToSurfaceAngleChangedHandler_);

            void removeCameraToSurfaceAngleChangedHandler(std::uintptr_t handleOwner_);

            void setInternalRuntimeParameters(universal_sdk::RuntimeParametersInternal* internalRuntimeParameters_);

        protected:
            universal_sdk::RuntimeParametersInternal*   _internalRuntimeParameters;
        };
}

#endif /* __cplusplus */

#endif /* RuntimeParameters_hpp */
