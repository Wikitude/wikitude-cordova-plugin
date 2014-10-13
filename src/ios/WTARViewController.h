//
//  WTArchitectViewController.h
//  Wikitude
//
//  Copyright (c) 2014 Wikitude. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "WTArchitectView.h"


extern NSString * const WTArchitectDidLoadWorldNotification;
extern NSString * const WTArchitectDidFailToLoadWorldNotification;
extern NSString * const WTArchitectInvokedURLNotification;
extern NSString * const WTArchitectDidCaptureScreenNotification;
extern NSString * const WTArchitectDidFailToCaptureScreenNotification;

extern NSString * const WTArchitectNotificationURLKey;
extern NSString * const WTArchitectNotificationContextKey;
extern NSString * const WTArchitectNotificationErrorKey;



@class WTArchitectViewController;
@class CMMotionManager;

@protocol WTArchitectViewControllerDelegate <NSObject>

- (void)architectViewControllerWillDisappear:(WTArchitectViewController *)architectViewController;

@end


@interface WTArchitectViewController : UIViewController <WTArchitectViewDelegate>

@property (nonatomic, weak) id<WTArchitectViewControllerDelegate>       architectDelegate;
@property (nonatomic, readonly) WTArchitectView                         *architectView;


+ (BOOL)isDeviceSupportedForAugmentedRealityMode:(WTAugmentedRealityMode)augmentedRealityMode;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil motionManager:(CMMotionManager *)motionManagerOrNil;

@end
