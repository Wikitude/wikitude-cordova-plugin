//
//  DeviceMotionInputPluginModule.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 02.03.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef DeviceMotionInputPluginModule_hpp
#define DeviceMotionInputPluginModule_hpp

#ifdef __cplusplus

#include <functional>

#include "CompilerAttributes.hpp"
#include "PluginModule.hpp"
#include "SensorEvent.hpp"


namespace wikitude::sdk {

        class WT_EXPORT_API DeviceMotionInputPluginModule : public PluginModule {
        public:
            virtual ~DeviceMotionInputPluginModule() {}

            /* Called from the Wikitude SDK */
            void registerNotifyNewDeviceRotationEventHandler(std::function<void(sdk::DeviceRotationEvent notifyNewDeviceRotationEventHandler_)>);
            void registerNotifyNewDeviceOrientationEventHandler(std::function<void(sdk::DeviceOrientationEvent)> notifyNewDeviceOrientationEventHandler_);

        protected:
            /**
             * Call this method to notify a new device rotation event to the Wikitude SDK
             */
            void notifyNewDeviceRotationEvent(sdk::DeviceRotationEvent deviceRotationEvent_);

            /**
             * Call this method to notify a new device orientation event to the Wikitude SDK
             */
            void notifyNewDeviceOrientationEvent(sdk::DeviceOrientationEvent deviceOrientationEvent_);

        protected:
            std::function<void(sdk::DeviceRotationEvent)>       _notifyNewDeviceRotationEventHandler;
            std::function<void(sdk::DeviceOrientationEvent)>    _notifyNewDeviceOrientationEventHandler;
        };
}

#endif /* __cplusplus */

#endif /* DeviceMotionInputPluginModule_hpp */
