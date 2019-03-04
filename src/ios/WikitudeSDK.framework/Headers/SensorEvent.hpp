//
//  SensorEvent.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 07/11/17.
//  Copyright (c) 2017 com.wikitude. All rights reserved.
//

#ifndef SensorEvent_hpp
#define SensorEvent_hpp

#ifdef __cplusplus

#include <memory>


namespace wikitude { namespace sdk {
    
    namespace impl {


        struct DeviceMotionData {
            DeviceMotionData(std::shared_ptr<float> motion_)
            :
            _motion(std::move(motion_))
            { /* Intentionally Left Blank */ }

            std::shared_ptr<float> _motion;
        };

        typedef struct AccelerationData {
            AccelerationData(double x_, double y_, double z_)
            :
            _x(x_),
            _y(y_),
            _z(z_)
            { /* Intentionally Left Blank */ }

            double  _x;
            double  _y;
            double  _z;
        } AccelerationData;

        typedef struct HeadingData {
            HeadingData(double x_, double y_, double z_, double trueHeading_, double magneticHeading_)
            :
            _x(x_),
            _y(y_),
            _z(z_),
            _trueHeading(trueHeading_),
            _magneticHeading(magneticHeading_)
            { /* Intentionally Left Blank */ }

            double headingDeviation() const {
                return _trueHeading - _magneticHeading;
            }

            double  _x;
            double  _y;
            double  _z;

            double _trueHeading;
            double _magneticHeading;
        } HeadingData;


        class SensorEvent {
        public:
            enum SensorEventType {
                DeviceRotation,
                DeviceOrientation,
                DeviceAcceleration,
                DeviceHeading
            };

        public:
            SensorEvent(SensorEventType eventType_);
            virtual ~SensorEvent();

            const SensorEventType& getEventType() const;
            
        private:
            SensorEventType                 _eventType;
        };


        class DeviceRotationEvent : public SensorEvent {
        public:
            DeviceRotationEvent(DeviceMotionData rotationData_);

            const DeviceMotionData& getDeviceMotionData() const;

        private:
            DeviceMotionData            _rotationData;
        };

        class DeviceOrientationEvent : public SensorEvent {
        public:
            DeviceOrientationEvent(DeviceMotionData orientationData_);

            const DeviceMotionData& getDeviceMotionData() const;
        private:
            DeviceMotionData            _orientationData;
        };

        class AccelerationEvent : public SensorEvent {
        public:
            AccelerationEvent(AccelerationData acceleration_);

            const AccelerationData& getAccelerationData() const;

        private:
            AccelerationData     _acceleration;
        };

        class HeadingEvent : public SensorEvent {
        public:
            HeadingEvent(HeadingData heading_);

            const HeadingData& getHeadingData() const;

        private:
            HeadingData     _heading;
        };
    }
    using impl::SensorEvent;
    using impl::DeviceMotionData;
    using impl::AccelerationData;
    using impl::HeadingData;
    using impl::DeviceRotationEvent;
    using impl::DeviceOrientationEvent;
    using impl::AccelerationEvent;
    using impl::HeadingEvent;
}}

#endif /* __cplusplus */

#endif /* defined(SensorEvent_hpp) */
