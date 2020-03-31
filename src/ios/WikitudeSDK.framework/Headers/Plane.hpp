//
//  Plane.hpp
//  WikitudeUniversalSDK
//
//  Created by Alexandru Florea on 01.08.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp

#ifdef __cplusplus

#include <vector>

#include "PlaneType.hpp"
#include "Geometry.hpp"
#include "CompilerAttributes.hpp"


namespace wikitude { namespace sdk {

    namespace impl {


        /** @addtogroup InstantTracking
         *  @{
         */
        /** @class Plane
         *  @brief A class that represents a plane found by an instant tracker.
         */

        class Matrix4;
        class Vector3;
        class WT_EXPORT_API Plane {
        public:
            virtual ~Plane() = default;

            /** @brief Gets the combined modelview matrix that should be applied to augmentations when rendering.
             *  In cases where the orientation of the rendering surface and orientation of the camera do not match, and a correct cameraToRenderSurfaceRotation is passed to the SDK,
             *  this matrix will also be rotate to account for the mismatch.
             *
             *  For example, on mobile devices running in portrait mode, that have a camera sensor is landscape right position, the cameraToRenderSurfaceRotation should be 90 degrees.
             *  The matrix will be rotated by 90 degrees around the Z axis.
             *
             *  @return The matrix that should be applied to the target augmentation when rendering.
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

            /** @brief Gets the unique id of the Plane.
             *
             *  @return The unique id of the plane.
             */
            virtual long getUniqueId() const = 0;

            /** @brief Gets the type for this plane.
             *
             *  Please refer to the PlaneType documentation for more details.
             *
             *  @return The plane type.
             */
            virtual PlaneType getPlaneType() const = 0;

            /** @brief Returns the confidence level for the plane.
             *
             *  The confidence level is mapped between 0 and 1.
             *
             *  @return The confidence level for the plane.
             */
            virtual float getConfidence() const = 0;

            /** @brief Gets the extents of the plane in the X axis.
             *
             *  @return The extents of the plane in the X axis.
             */
            virtual const Extent<float>& getExtentX() const = 0;

            /** @brief Gets the extents of the plane in the Y axis.
             *
             *  @return The extents of the plane in the Y axis.
             */
            virtual const Extent<float>& getExtentY() const = 0;

            /** @brief Gets the convex hull of the plane.
             *
             *  The convex hull can be used to render the plane mesh as a triangle fan.
             *  All the points are relative to the plane coordinate system and can also be used as texture coordinates.
             *
             *  @return The convex hull of the plane.
             */
            virtual const std::vector<Point<float>>& getConvexHull() const = 0;
        };
    }

    using impl::Plane;
}}

#endif /* __cplusplus */

#endif /* Plane_hpp */
