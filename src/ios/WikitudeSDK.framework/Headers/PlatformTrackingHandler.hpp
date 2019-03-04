//
//  PlatformTrackingHandler.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 13.12.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef PlatformTrackingHandler_hpp
#define PlatformTrackingHandler_hpp

#ifdef __cplusplus

#include <functional>


namespace wikitude { namespace sdk {

    namespace impl {


        using ProcessedFrameIdChangedHandler = std::function<void(const long processedFrameId_)>;
    }
    using impl::ProcessedFrameIdChangedHandler;
}}

#endif /* __cplusplus */

#endif /* PlatformTrackingHandler_hpp */
