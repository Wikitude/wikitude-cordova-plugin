//
//  OpenGLESRenderingPluginModule.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 17.06.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef OpenGLESRenderingPluginModule_hpp
#define OpenGLESRenderingPluginModule_hpp

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


        class WT_EXPORT_API OpenGLESRenderingPluginModule : public RenderingPluginModule {
        public:
            virtual void startRender(RenderableCameraFrameBucket& frameBucket_) = 0;
            virtual void endRender(RenderableCameraFrameBucket& frameBucket_) = 0;
        };
    }
    using impl::OpenGLESRenderingPluginModule;
}}

#endif /* __cplusplus */

#endif /* OpenGLESRenderingPluginModule_hpp */
