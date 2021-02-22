//
//  PluginModule.hpp
//  WikitudeUniversalSDK
//
//  Created by Andreas Schacherbauer on 26.03.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef PluginModule_hpp
#define PluginModule_hpp

#ifdef __cplusplus

#include "CompilerAttributes.hpp"

namespace wikitude::sdk {

        class ManagedCameraFrame;
        class WT_EXPORT_API PluginModule {
        public:
            virtual ~PluginModule() = default;

            virtual void pause();
            virtual void resume(unsigned int pausedTime_);

            virtual void cameraFrameAvailable(ManagedCameraFrame& managedCameraFrame_);
            virtual void prepareUpdate();
            virtual void update();

            void setEnabled(bool enabled_);
            bool isEnabled() const;

        protected:
            bool    _isEnabled = true;
        };
}

#endif /* __cplusplus */

#endif /* PluginModule_hpp */
