//
//  InstantTrackingPluginModule.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 28.02.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef InstantTrackingPluginModule_hpp
#define InstantTrackingPluginModule_hpp

#ifdef __cplusplus

#include "ErrorHandling.hpp"
#include "Geometry.hpp"
#include "ManagedCameraFrame.hpp"
#include "CompilerAttributes.hpp"

#include "TrackingPluginModule.hpp"
#include "State.hpp"
#include "InstantTrackingState.hpp"


namespace wikitude { namespace sdk {

    namespace impl {

        class WT_EXPORT_API InstantTrackingPluginModule : public TrackingPluginModule {
        public:
            virtual ~InstantTrackingPluginModule() = default;

            virtual universal_sdk::InstantState getInitializationState(/*float deviceHeightAboveGround*/) const = 0;
            virtual universal_sdk::InstantState getTrackingState() const = 0;
        };
    }
    using impl::InstantTrackingPluginModule;
}}

#endif /* __cplusplus */

#endif /* InstantTrackingPluginModule_hpp */
