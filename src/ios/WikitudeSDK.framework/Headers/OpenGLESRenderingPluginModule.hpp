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


namespace wikitude::sdk {

        class RenderableCameraFrameBucket;
        class WT_EXPORT_API OpenGLESRenderingPluginModule : public RenderingPluginModule {
        public:
            virtual void startRender(RenderableCameraFrameBucket& frameBucket_) = 0;
            virtual void endRender(RenderableCameraFrameBucket& frameBucket_) = 0;
        };
}

#endif /* __cplusplus */

#endif /* OpenGLESRenderingPluginModule_hpp */
