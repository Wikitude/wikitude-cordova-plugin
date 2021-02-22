//
//  JavaScriptPluginModule.hpp
//  ArchitectCore
//
//  Created by Andreas Schacherbauer on 23.11.18.
//  Copyright © 2018 Andreas Schacherbauer. All rights reserved.
//

#ifndef JavaScriptPluginModule_hpp
#define JavaScriptPluginModule_hpp

#ifdef __cplusplus

#include <string>
#include <vector>
#include <unordered_map>

#include "PluginModule.hpp"


namespace wikitude::sdk {

        class Positionable;
        class WT_EXPORT_API JavaScriptPluginModule : public PluginModule {
        public:
            class JavaScriptAPI {
            public:
                std::string     _jsAPI;
                std::unordered_map<std::string, std::function<void(const std::string)>> _jsMethodBindings;
            };

        public:
            JavaScriptPluginModule();
            virtual ~JavaScriptPluginModule() = default;

            /* Public API */
            void callJavaScript(const std::string& javaScript_);
            
            /* Called from the Wikitude SDK */
            virtual JavaScriptAPI getJavaScriptAPI();

            virtual void createInstance(const std::string& className_, long id_, const std::string& parameters_);
            virtual void callInstance(long id_, const std::string& jsCall);
            
            virtual void updatePositionables(const std::unordered_map<std::string, Positionable*>& positionables_);

            void registerCallJavaScriptHandler(std::function<void(const std::string& javaScript_)> callJavaScriptHandler_);
        
        private:
            std::function<void(const std::string&)> _callJavaScriptHandler;
            std::vector<std::string>                _pendingJavaScriptCalls;
        };
}

#endif /* __cplusplus */

#endif /* JavaScriptPluginModule_hpp */
