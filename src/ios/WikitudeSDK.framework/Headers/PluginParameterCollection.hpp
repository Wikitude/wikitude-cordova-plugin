//
//  PluginParameterCollection.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 29.06.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef PluginParameterCollection_hpp
#define PluginParameterCollection_hpp

#ifdef __cplusplus

#include "CompilerAttributes.hpp"


namespace wikitude::sdk {

        class RuntimeParameters;
        class CameraParameters;
        class TrackingParameters;
        class WT_EXPORT_API PluginParameterCollection {
        public:
            virtual ~PluginParameterCollection() = default;

            virtual const RuntimeParameters& getRuntimeParameters() const = 0;
            virtual RuntimeParameters& getRuntimeParameters() = 0;

            virtual const CameraParameters& getCameraParameters() const = 0;
            virtual CameraParameters& getCameraParameters() = 0;

            virtual const TrackingParameters& getTrackingParameters() const = 0;
            virtual TrackingParameters& getTrackingParameters() = 0;
        };
}

#endif /* __cplusplus */

#endif /* PluginParameterCollection_hpp */
