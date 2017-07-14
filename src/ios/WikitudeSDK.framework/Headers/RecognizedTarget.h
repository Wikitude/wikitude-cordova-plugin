//
// Created by simon on 08/04/15.
// Copyright (c) 2015 Wikitude. All rights reserved.
//


#ifndef RECOGNIZEDTARGET_H_
#define RECOGNIZEDTARGET_H_

#ifdef __cplusplus

#include <string>

#include "Matrix4.h"
#include "Geometry.h"

#define DEPRECATED_SINCE(__version__, __msg__) __attribute__((deprecated("Deprecated in Wikitude SDK " #__version__ ". " __msg__)))

namespace wikitude { namespace sdk {
    
    namespace impl {

        class ImageTarget {
        public:
            ImageTarget(const std::string& name, const long uniqueId, const bool isExtended, const int extendedTrackingQuality, const unsigned int physicalTargetImageHeight, const unsigned int distanceToTarget, const sdk::Scale2D<float> targetScale, const Rectangle<int>& targetRectInCameraFrame, const Matrix4& modelView, const Matrix4& projection);
            ~ImageTarget() = default;

            const std::string& getName() const;
            const long& getUniqueId() const;
            const bool isExtended() const;
            const int& getExtendedTrackingQuality() const;
            const unsigned int& getPhysicalTargetImageHeight() const;
            const unsigned int& getDistanceToTarget() const;
            const Scale2D<float>& getTargetScale() const;
            const Rectangle<int>& getTargetPositionInCameraFrame() const;
            const Matrix4& getModelViewMatrix() const;
            const Matrix4& getProjectionMatrix() const;

        protected:
            const std::string       _name;
            const long              _uniqueId;
            const bool              _isExtended;
            const int               _extendedTrackingQuality;
            const unsigned int      _physicalTargetImageHeight;
            unsigned int            _distanceToTarget;
            const Scale2D<float>    _targetScale;
            const Rectangle<int>    _targetRectInCameraFrame;
            Matrix4                 _modelView;
            Matrix4                 _projection;
        };

        class ObjectTarget {
        public:
            ObjectTarget(const std::string& name_, sdk::Scale3D<float> targetScale_, const Matrix4& modelView_, const Matrix4& projection_);
            ~ObjectTarget() = default;

            const std::string& getName() const;
            const sdk::Scale3D<float>& getTargetScale() const;
            const Matrix4& getModelViewMatrix() const;
            const Matrix4& getProjectionMatrix() const;

        protected:
            const std::string       _name;
            const Scale3D<float>    _targetScale;
            Matrix4                 _modelView;
            Matrix4                 _projection;
        };

        class InstantTarget {
        public:
            InstantTarget(const Matrix4& modelView_, const Matrix4& projection_);
            ~InstantTarget() = default;

            const Matrix4& getModelViewMatrix() const;
            const Matrix4& getProjectionMatrix() const;

        protected:
            Matrix4                 _modelView;
            Matrix4                 _projection;
        };

        class RecognizedTarget {
        public:
            RecognizedTarget(const std::string& name, const long uniqueId, const bool isExtended, const unsigned int distanceToTarget, const Rectangle<int>& targetRectInCameraFrame, const Matrix4& modelView, const Matrix4& projection);

            const std::string& getName() const DEPRECATED_SINCE("7.0.0", "Use ImageTarget.getName instead!");
            const long& getUniqueId() const DEPRECATED_SINCE("7.0.0", "Use ImageTarget.getUniqueId instead!");
            const bool isExtended() const DEPRECATED_SINCE("7.0.0", "Use ImageTarget.isExtended instead!");
            const unsigned int& getDistanceToTarget() const DEPRECATED_SINCE("7.0.0", "Use ImageTarget.getDistanceToTarget instead!");
            const Rectangle<int>& getTargetPositionInCameraFrame() const DEPRECATED_SINCE("7.0.0", "Use ImageTarget.getTargetPositionInCameraFrame instead!");
            const Matrix4& getModelViewMatrix() const DEPRECATED_SINCE("7.0.0", "Use ImageTarget.getModelViewMatrix instead!");
            const Matrix4& getProjectionMatrix() const DEPRECATED_SINCE("7.0.0", "Use ImageTarget.getProjectionMatrix instead!");

        protected:
            const std::string       _name;
            const long              _uniqueId;
            const bool              _isExtended;
            unsigned int            _distanceToTarget;
            const Rectangle<int>    _targetRectInCameraFrame;
            Matrix4                 _modelView;
            Matrix4                 _projection;
        } DEPRECATED_SINCE("7.0.0", "Use ImageTarget instead!");
    }
    
    using impl::RecognizedTarget;
    using impl::ImageTarget;
    using impl::ObjectTarget;
    using impl::InstantTarget;
}}

#endif /* __cplusplus */

#endif
