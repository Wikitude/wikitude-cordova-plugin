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
#include "CompilerAttributes.hpp"


namespace wikitude::universal_sdk {
    class TrackingParametersInternal;
}

namespace wikitude::sdk {

        class WT_EXPORT_API TrackingParameters {
        public:
            long getProcessedFrameId();
            void addProcessedFrameIdChangedHandler(std::uintptr_t handleOwner_, ProcessedFrameIdChangedHandler processedFrameIdChangedHandler_);
            void removeProcessedFrameIdChangedHandler(std::uintptr_t handleOwner_);

            void setInternalTrackingParameters(universal_sdk::TrackingParametersInternal* internalTrackingParameters_);

        protected:
            universal_sdk::TrackingParametersInternal*  _internalTrackingParameters;
        };
}

#endif /* __cplusplus */

#endif /* TrackingParameters_hpp */
