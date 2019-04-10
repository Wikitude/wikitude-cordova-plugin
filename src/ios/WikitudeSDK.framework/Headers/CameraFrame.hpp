//
//  FrameInfo.hpp
//  CommonLibrary
//
//  Created by Andreas Schacherbauer on 19.10.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef FrameInfo_hpp
#define FrameInfo_hpp

#ifdef __cplusplus

#include <memory>
#include <cstdint>
#include <vector>

#include "Geometry.hpp"
#include "ColorSpace.hpp"
#include "CameraPosition.hpp"
#include "DepthDataFormat.hpp"
#include "CameraFramePlane.hpp"
#include "Matrix4.hpp"


namespace wikitude { namespace sdk {

    namespace impl {

        /** @class DepthCameraFrameMetadata
         *  @brief A class that encapsulates additional information about depth camera frames.
         */
        class DepthCameraFrameMetadata {
        public:
            DepthCameraFrameMetadata(float horizontalFov_, sdk::Size<int> pixelSize_, unsigned int dataSize_, DepthDataFormat depthDataFormat_, bool inverted_, std::int32_t timestampTimescale_);

            /** @brief Returns the horizontal field of view in degrees of the depth camera used to capture the depth frame.
             */
            float getHorizontalFieldOfView() const;

            /** @brief Returns the size in pixels of the depth camera frame.
             */
            sdk::Size<int> getPixelSize() const;

            /** @brief Returns the size in bytes of the depth camera frame.
             */
            unsigned int getDataSize() const;

            /** @brief Returns the format of the depth camera frame.
             */
            DepthDataFormat getDepthDataFormat() const;

            /** @brief If true, lower values in the depth data mean a greater depth.
             */
            bool getIsInverted() const;

            /** @brief Returns the timestamp timescale that corresponds to the DepthTimestamp set in the CameraFrame.
             */
            std::int32_t getTimestampTimescale() const;

        protected:
            float                   _horizontalFov;
            sdk::Size<int>          _pixelSize;
            unsigned int            _dataSize;
            DepthDataFormat         _depthDataFormat;
            bool                    _inverted;
            std::int32_t            _timestampTimescale;
        };

        enum class DistortionMode {
            None = 0,
            Equidistant,
            RadialTangential,
            Atan,
        };

        class IntrinsicsCalibration {
        public:
            IntrinsicsCalibration(DistortionMode distortionMode_, Point<float> principalPoint_, Point<float> focalLength_, const std::vector<float>& distortion_);

            DistortionMode getDistortionMode() const;
            Point<float> getPrincipalPoint() const;
            Point<float> getFocalLength() const;
            const std::vector<float> getDistortion() const;

        protected:
            DistortionMode              _distortionMode;
            Point<float>                _principalPoint;
            Point<float>                _focalLength;
            std::vector<float>          _distortion;
        };

        /** @class ColorCameraFrameMetadata
         *  @brief A class that encapsulates additional information about color camera frames.
         */
        class ColorCameraFrameMetadata {
        public:
            ColorCameraFrameMetadata(float horizontalFov_, sdk::Size<int> pixelSize_, CameraPosition cameraPosition_, ColorSpace frameColorSpace_, std::int32_t timestampTimescale_);

            ColorCameraFrameMetadata(IntrinsicsCalibration intrinsicsCalibration_, sdk::Size<int> pixelSize_, CameraPosition cameraPosition_, ColorSpace frameColorSpace_, std::int32_t timestampTimescale_);

            /** @brief Returns the horizontal field of view in degrees of the color camera used to capture the color frame.
             */
            float getHorizontalFieldOfView() const;

            const IntrinsicsCalibration& getIntrinsicsCalibration() const;

            /** @brief Returns the size in pixels of the color camera frame.
             */
            sdk::Size<int> getPixelSize() const;

            /** @brief Returns whether the camera used to capture the color frame was a back or front facing camera, or if this information is unspecified.
             */
            CameraPosition getCameraPosition() const;

            /** @brief Returns the color space of the color camera frame.
             */
            ColorSpace getFrameColorSpace() const;

            /** @brief Returns the timestamp timescale that corresponds to the ColorTimestamp set in the CameraFrame.
             */
            std::int32_t getTimestampTimescale() const;

            /** @brief Returns if intrinsics calibration are default or provided.
             */
            bool getHasDefaultIntrinsicsCalibration() const;

        protected:
            float                   _horizontalFov;
            IntrinsicsCalibration   _intrinsicsCalibration;
            sdk::Size<int>          _pixelSize;
            CameraPosition          _cameraPosition;
            ColorSpace              _frameColorSpace;
            std::int32_t            _timestampTimescale;
            bool _hasDefaultIntrinsicsCalibration;
        };

        /** @addtogroup UniversalComponent
         *  @{
         */
        /** @class CameraFrame
         *  @brief A class that color and depth frames, along with their metadata and optional pose. The CameraFrame class doesn't copy or retain the color and depth data in any way.
         */
        class CameraFrame {
        public:
            CameraFrame(long id_, std::int64_t colorTimestamp_, ColorCameraFrameMetadata colorMetadata_, const std::vector<CameraFramePlane>& colorData_);
            CameraFrame(long id_, std::int64_t colorTimestamp_, ColorCameraFrameMetadata colorMetadata_, const std::vector<CameraFramePlane>& colorData_, const Matrix4& pose_);
            CameraFrame(long id_, std::int64_t colorTimestamp_, ColorCameraFrameMetadata colorMetadata_, const std::vector<CameraFramePlane>& colorData_, std::int64_t depthTimestamp_, DepthCameraFrameMetadata depthMetadata_, const void* depthData_);

            /** @brief Returns unique id used to identify individual frames.
             */
            long getId() const;

            /** @brief Returns the timestamp for the color frame.
             */
            std::int64_t getColorTimestamp() const;

            /** @brief Returns the metadata associated with the color frame.
             */
            const ColorCameraFrameMetadata& getColorMetadata() const;

            /** @brief Returns a vector of planes of the camera data, as it was passed through the constructor. When passed to the constructor, it must not be empty.
             */
            const std::vector<CameraFramePlane>& getColorData() const;

            /** @brief Returns the timestamp for the depth frame.
             */
            std::int64_t getDepthTimestamp() const;

            /** @brief Returns the metadata associated with the depth frame.
             */
            const DepthCameraFrameMetadata& getDepthMetadata() const;

            /** @brief Returns a pointer to the depth data, as it was passed through the constructor. When passed to the constructor, it may be nullptr to indicate the absence of depth data.
             */
            const void* getDepthData() const;

            /** @brief Returns whether this camera frame was initialized with a camera pose. Accessing the camera pose when this method returns false is undefined behaviour.
             */
            bool hasPose() const;

            /** @brief Returns the camera pose associated with this camera frame. Use `hasPose` to verify that the camera contains a valid pose.
             */
            const Matrix4& getPose() const;

        protected:
            long                                    _id;

            std::int64_t        	                _colorTimestamp;
            ColorCameraFrameMetadata                _colorMetadata;
            std::vector<CameraFramePlane>           _colorData;

            std::int64_t                            _depthTimestamp;
            DepthCameraFrameMetadata                _depthMetadata;
            const void*                             _depthData;

            Matrix4                                 _pose;
            bool                                    _hasPose;
        };
        /** @}*/
    }
    using impl::DepthDataFormat;
    using impl::DepthCameraFrameMetadata;
    using impl::ColorCameraFrameMetadata;
    using impl::DistortionMode;
    using impl::IntrinsicsCalibration;
    using impl::CameraFrame;
}}

#endif /* __cplusplus */

#endif /* FrameInfo_hpp */
