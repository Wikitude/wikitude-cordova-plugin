//
//  WTArchitectViewController.h
//  Wikitude
//
//  Copyright (c) 2014 Wikitude. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "WikitudeSDK.h"
#import "WTArchitectViewDebugDelegate.h"



extern NSString * const WTArchitectDidLoadWorldNotification;
extern NSString * const WTArchitectDidFailToLoadWorldNotification;
extern NSString * const WTArchitectInvokedURLNotification;
extern NSString * const WTArchitectDidCaptureScreenNotification;
extern NSString * const WTArchitectDidFailToCaptureScreenNotification;

extern NSString * const WTArchitectNeedsHeadingCalibrationNotification;

extern NSString * const WTArchitectDebugDelegateNotification;

extern NSString * const WTArchitectNotificationURLKey;
extern NSString * const WTArchitectNotificationContextKey;
extern NSString * const WTArchitectNotificationErrorKey;

extern NSString * const WTArchitectDebugDelegateMessageKey;



@class WTArchitectViewController;
@class CMMotionManager;

@protocol WTArchitectViewControllerDelegate <NSObject>

- (void)architectViewControllerWillDisappear:(WTArchitectViewController *)architectViewController;

@end


@interface WTArchitectViewController : UIViewController <WTArchitectViewDelegate, WTArchitectViewDebugDelegate>

@property (nonatomic, weak) id<WTArchitectViewControllerDelegate>       architectDelegate;
@property (nonatomic, readonly) WTArchitectView                         *architectView;

@property (nonatomic, strong) WTStartupConfiguration                    *startupConfiguration;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil motionManager:(CMMotionManager *)motionManagerOrNil;

@end
