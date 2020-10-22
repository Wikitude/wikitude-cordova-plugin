//
//  ImageTarget.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 12.08.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef ImageTarget_hpp
#define ImageTarget_hpp

#ifdef __cplusplus

#include <string>
#include <functional>

#include "Geometry.hpp"
#include "Vector3.hpp"
#include "ImageTargetType.hpp"
#include "CompilerAttributes.hpp"


namespace wikitude::sdk {

        /** @addtogroup ImageTracking
        *  @{
        */
        /** @class ImageTarget
         *  @brief A class that represents image targets that are found by an image tracker.
         */
        class ImageTracker;
        class Matrix4;
        class WT_EXPORT_API ImageTarget {
        public:
            using DistanceToTargetChangedHandler = std::function<void(int distance_, ImageTarget& firstTarget_, ImageTarget& secondTarget_)>;
            using RotationToTargetChangedHandler = std::function<void(std::array<float, 3> rotation_, ImageTarget& firstTarget_, ImageTarget& secondTarget_)>;
            using TranslationToTargetChangedHandler = std::function<void(std::array<float, 3> translation_, ImageTarget& firstTarget_, ImageTarget& secondTarget_)>;

        public:
            virtual ~ImageTarget() = default;
            
            /** @brief Gets the name of the associated target image in the wikitude target collection(.wtc).
             *
             *	@return The name of the image target.
             */
            virtual const std::string& getName() const = 0;

            /** @brief Gets the address of the Tracker the target has been created by. Use to distinguish between trackers in case multiple simultaneous trackers are used.
             *
             * @return The address of the tracker the target has been created by
             */
            virtual const ImageTracker* getTracker() const = 0;
            
            /** @brief Gets the unique id of the ImageTarget. This unique id is incremented with every recognition of the same target.
             *
             * @return The unique id of the image target.
             */
            virtual long getUniqueId() const = 0;
            
            /** @brief Gets the depth factor that needs to be applied to the matrix to get real world scaling.
             *
             * Note: This getter only returns valid information in case depth camera information are passed to the SDK.
             *
             * @return The depth factor of the image target.
             */
            virtual float getDepthFactor() const = 0;

            /**
             * @brief Gets the size of the image target in pixels.
             *
             * @return The size of the image in pixels.
             */
            virtual Size<int> getTargetSize() const = 0;
            
            /** @brief Gets a scale value that represents the image dimensions proportionally to the uniform scaling given through the matrix returned from getMatrix();
             *
             * @return The normalized scale of the image target.
             */
            virtual const Scale2D<float> getTargetScale() const = 0;

            /** @brief Gets the physical height of the image target as it is defined in the .wtc or through the ImageTrackerConfiguration property set with ImageTrackerConfiguration::setPhysicalTargetImageHeights()
             *
             * @return The physical target height in millimeter.
             */
            virtual int getPhysicalTargetHeight() const = 0;

            /** @brief Gets the distance from the camera to the image target in millimeter.
             *
             * This value only contains reliable values if the .wtc file or the cloud archive included physical image target heights.
             * @return The physical distance in millimeter between the camera and the image target.
             */
            virtual int getDistanceToTarget() const = 0;

            /** @brief Gets the physical distance between two image targets
             *
             * @param otherTarget_ The image target to which the distance should be calculated to.
             * @return The physical distance in millimeter between this target and imageTarget.
             */
            virtual int getDistanceTo(const ImageTarget& otherTarget_) const = 0;

            /** @brief Sets a handler to observe changes in the distance between this and other ImageTargets
             *
             */
            virtual void setDistanceToTargetChangedHandler(DistanceToTargetChangedHandler handler_) = 0;
            
            virtual Vector3 getRotationTo(const ImageTarget& otherTarget_) const = 0;
            
            /** @brief Sets a handler to observe changes in the rotation between this and other ImageTargets
             *
             */
            virtual void setRotationToTargetChangedHandler(RotationToTargetChangedHandler handler_) = 0;
            
            virtual Vector3 getTranslationTo(const ImageTarget& otherTarget_) const = 0;
            
            /** @brief Sets a handler to observe changes in the translation between this and other ImageTargets
             *
             */
            virtual void setTranslationToTargetChangedHandler(TranslationToTargetChangedHandler handler_) = 0;

            virtual Rectangle<int> getTargetAreaInCameraFrame() const = 0;
            virtual Rectangle<int> getTargetAreaInScreenSpace(Size<int> cameraFrameSize_, Size<int> surfaceSize_, const Matrix4& projectionMatrix_, float angle_) const = 0;

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

            /** @brief Gets the type from the image target.
             *
             * Please refer to the ImageTargetType documentation for more details.
             *
             * @return The image target type.
             */
            virtual ImageTargetType getImageTargetType() const = 0;

            /** @brief Gets the base circumference of the cylinder target as it is defined in the .metadata file through the "circumference"->"base" value
             *
             * @return The cylinder target base circumference in millimeter.
             */
            virtual int getCircumferenceBase() const = 0;

            /** @brief Gets the top circumference of the cylinder target as it is defined in the .metadata file through the "circumference"->"top" value
             *
             * @return The cylinder target top circumference in millimeter.
             */
            virtual int getCircumferenceTop() const = 0;
        };
        /** @}*/
}

#endif /* __cplusplus */

#endif /* ImageTarget_hpp */
