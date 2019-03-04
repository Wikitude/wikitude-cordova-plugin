//
//  TrackingParameters.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 13.12.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef TrackingParameters_hpp
#define TrackingParameters_hpp

#ifdef __cplusplus

#include "PlatformTrackingHandler.hpp"


namespace wikitude {
    namespace universal_sdk {
        namespace impl {
            class TrackingParametersInternal;
        }
        using impl::TrackingParametersInternal;
    }
}

namespace wikitude { namespace sdk {

    namespace impl {


        class TrackingParameters {
        public:
            long getProcessedFrameId();
            void addProcessedFrameIdChangedHandler(std::uintptr_t handleOwner_, ProcessedFrameIdChangedHandler processedFrameIdChangedHandler_);
            void removeProcessedFrameIdChangedHandler(std::uintptr_t handleOwner_);

            void setInternalTrackingParameters(universal_sdk::TrackingParametersInternal* internalTrackingParameters_);

        protected:
            universal_sdk::TrackingParametersInternal*  _internalTrackingParameters;
        };
    }
    using impl::TrackingParameters;
}}

#endif /* __cplusplus */

#endif /* TrackingParameters_hpp */
