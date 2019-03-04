//
//  ArchitectPlugin.hpp
//  ArchitectCore
//
//  Created by Andreas Schacherbauer on 23.11.18.
//  Copyright © 2018 Andreas Schacherbauer. All rights reserved.
//

#ifndef ArchitectPlugin_hpp
#define ArchitectPlugin_hpp

#ifdef __cplusplus

#include "Plugin.hpp"

#include "JavaScriptPluginModule.hpp"


namespace wikitude { namespace sdk {

    namespace impl {


        class WT_EXPORT_API ArchitectPlugin : public Plugin {
        public:
            ArchitectPlugin(const std::string& identifier_);
            virtual ~ArchitectPlugin() = default;

            JavaScriptPluginModule* getJavaScriptPluginModule() const;

            PluginType getPluginType() const;

        protected:
            void setJavaScriptPluginModule(std::unique_ptr<JavaScriptPluginModule> javaScriptPluginModule_);

        private:
            std::unique_ptr<JavaScriptPluginModule>     _javaScriptPluginModule;
        };
    }
    using impl::ArchitectPlugin;
}}

#endif /* __cplusplus */

#endif /* ArchitectPlugin_hpp */
