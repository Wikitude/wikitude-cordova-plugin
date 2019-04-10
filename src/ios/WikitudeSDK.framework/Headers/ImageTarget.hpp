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


namespace wikitude { namespace sdk {

    namespace impl {


        /** @addtogroup ImageTracking
        *  @{
        */
        /** @class ImageTarget
         *  @brief A class that represents image targets that are found by an image tracker.
         */
        class Matrix4;
        class ImageTarget {
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

            /** @brief Gets the transformation from local space to world space. This matrix is valid only if the CameraFrame contains a valid device pose.
             * This is useful when the application needs to know the movement of the target relative to it's environment. When only the camera moves, this
             * transformation stays constant from frame to frame.
             *
             * When combined with the viewMatrix, this results in the modelViewMatrix that should be applied to the target augmentation when rendering.
             *
             * @return The matrix that transforms the target from local space to world space.
             */
            virtual const Matrix4& getModelMatrix() const = 0;

            /** @brief Gets the transformation from world space to camera space. This matrix is valid only if the CameraFrame contains a valid device pose.
             * This is useful when the application needs to know the movement of the camera relative to it's environmet. When only the target moves, this
             * transformation stays constant from frame to frame.
             *
             * When combined with the modelMatrix, this results in the modelViewMatrix that should be applied to the target augmentation when rendering.
             *
             * @return The matrix that transform the target from world space to camera space.
             */
            virtual const Matrix4& getViewMatrix() const = 0;
        };
        /** @}*/
    }    
    using impl::ImageTarget;
}}

#endif /* __cplusplus */

#endif /* ImageTarget_hpp */
