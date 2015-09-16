//
//  WTArchitectView+Plugins.h
//  WikitudeSDK
//
//  Created by Andreas Schacherbauer on 17/05/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#ifndef WikitudeSDK_WTArchitectView_Plugins_h
#define WikitudeSDK_WTArchitectView_Plugins_h

#include <memory>


namespace wikitude {
    namespace sdk {
        namespace impl {
            class Plugin;
        }
        using impl::Plugin;
    }
}


@interface WTArchitectView (Plugins)

/**
 * Use this method to register a custom plugin which derives from wikitude::sdk::Plugin.
 * 
 * @param plugin The wikitude::sdk::Plugin sublclass that should be registered
 *
 * @return BOOL YES if the plugin could be registered with the given identifier, NO otherwise.
 */
- (BOOL)registerPlugin:(std::shared_ptr<wikitude::sdk::Plugin>)plugin;

/**
 * Use this method to remove an already registered plugin.
 *
 * @param plugin The wikitude::sdk::Plugin sublclass that should be removed
 *
 * @return BOOL YES if the plugin could be removed, NO otherwise.
 */
- (BOOL)removePlugin:(std::shared_ptr<wikitude::sdk::Plugin>)plugin;

- (BOOL)removeNamedPlugin:(NSString *)pluginIdentifier;

@end

#endif
