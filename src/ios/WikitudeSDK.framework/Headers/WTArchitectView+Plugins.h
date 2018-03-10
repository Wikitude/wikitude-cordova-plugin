//
//  WTArchitectView+Plugins.h
//  WikitudeSDK
//
//  Created by Andreas Schacherbauer on 17/05/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#ifndef WikitudeSDK_WTArchitectView_Plugins_h
#define WikitudeSDK_WTArchitectView_Plugins_h

#ifdef __cplusplus

#include <memory>


namespace wikitude {
    namespace sdk {
        namespace impl {
            class Plugin;
        }
        using impl::Plugin;
    }
}

/**
 * WTArchitectView+Plugins defines some methods that can be used to register C++ plugins.
 *
 * To use C++ code within your Objective-C class, set the file extension to .mm or change the type to Objective-C++ source in the Xcode Identity and Type inspector.
 *
 * Plugins need to derive from wikitude::sdk::Plugin and have to be passed as std::shared_ptr.
 */
@interface WTArchitectView (Plugins)

/**
 * Use this method to register a custom plugin which derives from wikitude::sdk::Plugin.
 *
 * @param plugin The wikitude::sdk::Plugin sublclass that should be registered
 * @param error An error object that will be filled when plugin registration fails
 *
 * @return BOOL YES if the plugin could be registered with the given identifier, NO otherwise.
 */
- (BOOL)registerPlugin:(std::shared_ptr<wikitude::sdk::Plugin>)plugin error:(NSError * __autoreleasing *)error;

/**
 * Use this method to register a custom plugin which derives from wikitude::sdk::Plugin.
 *
 * @deprecated Since version 6.1.0. Use -registerPlugin:error: instead.
 * 
 * @param plugin The wikitude::sdk::Plugin sublclass that should be registered
 *
 * @return BOOL YES if the plugin could be registered with the given identifier, NO otherwise.
 */
- (BOOL)registerPlugin:(std::shared_ptr<wikitude::sdk::Plugin>)plugin WT_DEPRECATED_SINCE(6.1.0, "Use -registerPlugin:error instead.");

/**
 * Use this method to remove an already registered plugin.
 *
 * @param plugin The wikitude::sdk::Plugin sublclass that should be removed
 *
 * @return BOOL YES if the plugin could be removed, NO otherwise.
 */
- (BOOL)removePlugin:(std::shared_ptr<wikitude::sdk::Plugin>)plugin;

/**
 * @brief Call this method to remove an already registered plugin.
 *
 * @discussion Same as -removePlugin but searches for the plugin to remove by the given identifier. Using this method, no shared_ptr property needs to be added to any object because the Wikitude Architect SDK takes ownership of any plugin.
 *
 * @param pluginIdentifier The Identifier that uniquely identifies the plugin that should be removed.
 * @return BOOL YES if the plugin was known and could be removed, NO otherwise.
 */
- (BOOL)removeNamedPlugin:(NSString *)pluginIdentifier;

@end

#endif /* __cplusplus */
#endif /* WikitudeSDK_WTArchitectView_Plugins_h */
