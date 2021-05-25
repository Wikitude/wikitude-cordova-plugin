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


namespace wikitude::sdk {

        using ProcessedFrameIdChangedHandler = std::function<void(const long processedFrameId_)>;
}

#endif /* __cplusplus */

#endif /* PlatformTrackingHandler_hpp */
