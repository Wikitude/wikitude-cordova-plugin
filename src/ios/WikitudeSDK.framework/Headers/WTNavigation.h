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
 * It might be the case that the URL that was passed to the `-loadArchitectWorldFromURL:withRequiredFeatures:` is causing some redirects during it's loading.
 * The returned navigation object can now be used to determine which Architect World finished loading when the `-architectView:didFinishLoadArchitectWorldNavigation:` delegate method is called.
 * A `-isEqual:` call on the navigation objects will return `YES` if the original URL is the same but the finally resolved URL differs.
 * A simple scenario would be a short URL. Passing a short URL to the `-loadArchitectWorldFromURL:withRequiredFeatures:` method will return the finally resolved URL to the previously prefered `-architectView:didFinishLoad:` delegate method.
 * The problem here is, that the initial load URL is no longer the same URL that finished loading.
 * The new `-architectView:didFinishLoadArchitectWorldNavigation:` mehthod now provides the navigation object that was returned by the `-loadArchitectWorldFromURL:withRequiredFeatures:` method.
 * A simple `-isEqual:` call now provides the information if the original URL is the same as the final URL and if the load request finished successfully.
 *
 * A `WTNavigation` object also provides information about the current loading status on an Architect World. It's `isLoading` property represents the underlying web view loading status and can be used to determine the loading status.
 * It might be the case that the `WTArchitectView` is stopped during an active Architect World load request. If that's the case, the `wasInterrupted` property is set to YES and can be used to determine if a reload is required at a later point in time.
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

/**
 * Represents the underlying web view load request status.
 * It's value is YES from the moment the navigation object was created and returned from the `-loadArchitectWorldFromURL:withRequiredFeatures:` method until either the `-architectView:didFinishLoadArchitectWorldNavigation:` or `-architectView:didFailToLoadArchitectWorldNavigation:withError:` delegate method is called. If a reload is triggered, `isLoading` represents the load request status again.
 */
@property (nonatomic, assign, readonly) BOOL            isLoading;

/**
 * If the `WTArchitectView` is stopped during an active Architect World request, the `wasInterrupted` property is set to YES. This information can be used to determine if an Architect World needs to be reloaded because it never finished loading.
 */
@property (nonatomic, assign, readonly) BOOL            wasInterrupted;

@end
