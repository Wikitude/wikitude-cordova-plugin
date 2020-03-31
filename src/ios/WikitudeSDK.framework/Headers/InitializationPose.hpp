//
//  InitializationPose.hpp
//  WikitudeUniversalSDK
//
//  Created by Alexandru Florea on 07/11/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef InitializationPose_hpp
#define InitializationPose_hpp

#ifdef __cplusplus

#include "CompilerAttributes.hpp"


namespace wikitude { namespace sdk {
    
    namespace impl {


        /** @addtogroup InstantTracking
         *  @{
         */
        /** @class InitializationPose
         *  @brief A class that represents a gravity aligned plane, as reported by an instant tracker.
         */
        class Matrix4;
        class WT_EXPORT_API InitializationPose {
        public:
            virtual ~InitializationPose() = default;
            
            /** @brief Gets the combined modelview matrix that should be applied to augmentations when rendering.
             * In cases where the orientation of the rendering surface and orientation of the camera do not match, and a correct cameraToRenderSurfaceRotation is passed to the SDK, this matrix will also be rotate to account for the mismatch.
             *
             * For example, on mobile devices running in portrait mode, that have a camera sensor is landscape right position, the cameraToRenderSurfaceRotation should be 90 degrees.
             * The matrix will be rotated by 90 degrees around the Z axis.
             *
             * @return The matrix that should be applied to the target augmentation when rendering.
             */
            virtual const Matrix4& getMatrix() const = 0;

            /** @brief Gets the transformation from local space to world space.
             * When the CameraFrame doesn't contain a valid device pose, world space and camera space are the same.
             * When combined with the viewMatrix, this results in the modelViewMatrix that should be applied to the target augmentation when rendering.
             *
             * @return The matrix that transforms the target from local space to world space.
             */
            virtual const Matrix4& getModelMatrix() const = 0;

            /** @brief Gets the transformation from world space to camera space.
             * When the CameraFrame doesn't contain a valid device pose, world space and camera space are the same.
             * When combined with the modelMatrix, this results in the modelViewMatrix that should be applied to the target augmentation when rendering.
             *
             * @return The matrix that transform the target from world space to camera space.
             */
            virtual const Matrix4& getViewMatrix() const = 0;
        };
        /** @}*/
    }
    using impl::InitializationPose;
}}

#endif /* __cplusplus */

#endif /* InitializationPose_hpp */
