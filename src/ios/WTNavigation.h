//
//  WTNavigation.h
//  WikitudeSDK
//
//  Copyright (c) 2014 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>



/**
 * WTNavigation class
 *
 * A `WTNavigation` object represents the Architect World URL during it's loading state.
 * It might be the case that the URL that was passed to the `-loadArchitectWorldFromURL:withAugmentedRealityMode:` is causing some redirects during it's loading.
 * The returned navigation object can now be used to determine which Architect World finished loading when the `-architectView:didFinishLoadArchitectWorldNavigation:` delegate method is called.
 * A `-isEqual:` call on the navigation objects will return `YES` if the original URL is the same but the finally resolved URL differs.
 * A simple scenario would be a short URL. Passing a short URL to the `-loadArchitectWorldFromURL:withAugmentedRealityMode:` method will return the finally resolved URL to the previously prefered `-architectView:didFinishLoad:` delegate method.
 * The problem was that the initial load URL is no longer the same URL that finished loading.
 * The new `-architectView:didFinishLoadArchitectWorldNavigation:` mehthod now provides the navigation object that was returned by the `-loadArchitectWorldFromURL:withAugmentedRealityMode:` method.
 * A simple `-isEqual:` call now provides the information if the original URL is the same as the final URL and if the load request finished successfully. 
 */
@interface WTNavigation : NSObject <NSCopying>

/**
 * The URL that was given at the loadArchitectWorldFromURL:augmentedRealityMode method of WTArchitectView
 */
@property (nonatomic, strong, readonly) NSURL           *originalURL;

/**
 * The final URL that was loaded by the WTArchitectView's web view
 */
@property (nonatomic, strong, readonly) NSURL           *finalURL;

@end
