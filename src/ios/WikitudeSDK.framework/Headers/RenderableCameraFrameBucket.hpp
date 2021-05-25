//
//  RenderableCameraFrameBucket.hpp
//  WikitudeUniversalSDK
//
//  Created by Alexander Bendl on 26.06.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef RenderableCameraFrameBucket_h
#define RenderableCameraFrameBucket_h

#ifdef __cplusplus

#include <functional>

#include "Error.hpp"
#include "CompilerAttributes.hpp"


namespace wikitude::sdk {

        class RenderableCameraFrame;
        class WT_EXPORT_API RenderableCameraFrameBucket {
        public:
            virtual ~RenderableCameraFrameBucket() = default;
            
            virtual void getRenderableCameraFrameForId(long id_, std::function<void(RenderableCameraFrame&)> successHandler_, std::function<void(Error&)> errorHandler_) = 0;
        };
}

#endif /* __cplusplus */

#endif /* RenderableCameraFrameBuckett_h */
