//
//  ObjectTarget.hpp
//  WikitudeUniversalSDK
//
//  Created by Thibault Jochem on Wed Nov 08 2017
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef OBJECTTARGET_HPP
#define OBJECTTARGET_HPP

#ifdef __cplusplus

#include <string>

#include "Geometry.hpp"
#include "CompilerAttributes.hpp"

namespace wikitude::sdk {

        /** @addtogroup ObjectTracking
        *  @{
        */
        /** @class ObjectTarget
          * @brief A class that represents object targets that are found by an object tracer.
          *
          * Scale values can be used to convert the ‘unit cube’ modelView matrix into a box that covers just the outer 
          * dimensions of the object. Example: Consider a truck like shaped object target. In case a cube
          * with edge length of one would be drawn with the modelView matrix, the cube would be drawn without 
          * distortions in the center of the object. To render a box around the truck, x/y/z scale values are used to
          * create another scale matrix that is multiplied with the given modelView matrix. The result is then a box 
          * that encompasses the object target at it’s outer dimensions.
          */
        class Matrix4;
        class ObjectTracker;
        class WT_EXPORT_API ObjectTarget{
        public:
            virtual ~ObjectTarget() = default;

            /** @brief Gets the name of the associated target object in the wikitude object target collection(.wto).
             *
             *	@return The name of the image target.
             */
            virtual const std::string& getName() const = 0;

            /** @brief Gets the unique id of the ObjectTarget. This unique id is incremented with every recognition of the same target.
             *
             * @return The unique id of the object target.
             */
            virtual long getUniqueId() const = 0;

            /** @brief Gets the address of the Tracker the target has been created by. Use to distinguish between trackers in case multiple simultaneous trackers are used.
             *
             * @return The address of the tracker the target has been created by
             */
            virtual const ObjectTracker* getTracker() const = 0;
            
            /** @brief Gets the depth factor that needs to be applied to the matrix to get real world scaling.
             *
             * Note: This getter only returns valid information in case depth camera information are passed to the SDK.
             *
             * @return The depth factor of the object target.
             */
            virtual float getDepthFactor() const = 0;
            
            /** @brief Gets a scale value that represents the object dimensions proportionally to the uniform scaling
             *  given through the matrix returned from getMatrix();
             *
             * @return The normalized scale of the object target.
             */
            virtual const Scale3D<float> getTargetScale() const = 0;

            /** @brief Gets the combined modelview matrix that should be applied to augmentations when rendering.
             * In cases where the orientation of the rendering surface and orientation of the camera do not match, and a correct cameraToRenderSurfaceRotation is passed to the SDK,
             * this matrix will also be rotate to account for the mismatch.
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

#endif /* __cplusplus */

#endif /* OBJECTTARGET_HPP */
