//
//  MetalRenderingPluginModule.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 17.06.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef MetalRenderingPluginModule_hpp
#define MetalRenderingPluginModule_hpp

#ifdef __cplusplus

#include "CompilerAttributes.hpp"
#include "RenderingPluginModule.hpp"


namespace wikitude { namespace sdk {
    
    namespace impl {
        class RenderableCameraFrameBucket;
    }
    using impl::RenderableCameraFrameBucket;
}}

namespace wikitude { namespace sdk {

    namespace impl {

        class MetalRenderingObjects;
        class WT_EXPORT_API MetalRenderingPluginModule : public RenderingPluginModule {
        public:
            virtual void startRender(const MetalRenderingObjects& metalRenderingObjects, RenderableCameraFrameBucket& frameBucket_) = 0;
            virtual void endRender(const MetalRenderingObjects& metalRenderingObjects, RenderableCameraFrameBucket& frameBucket_) = 0;
        };
    }
    using impl::MetalRenderingPluginModule;
}}

#endif /* __cplusplus */

#endif /* MetalRenderingPluginModule_hpp */
