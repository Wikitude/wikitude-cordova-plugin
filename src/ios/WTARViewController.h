//
//  WTARViewController.h
//  HelloWorld
//
//  Created by Andreas Schacherbauer on 2/7/13.
//
//

#import <UIKit/UIKit.h>


@class WTARViewController;
@class WTArchitectView;
@class CMMotionManager;


@protocol WTARViewControllerDelegate <NSObject>

- (void)arViewControllerWillDisappear:(WTARViewController *)arViewcontroller;

@end


@interface WTARViewController : UIViewController

@property (nonatomic, weak) id<WTARViewControllerDelegate>      delegate;
@property (nonatomic, readonly) WTArchitectView                 *architectView;
@property (nonatomic, assign) BOOL                              isARchitectViewRunning;


+ (BOOL)isGeoSupported;
+ (BOOL)isIRSupported;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil sdkKey:(NSString *)sdkKeyorNil motionManager:(CMMotionManager *)cmMotionManagerOrNil;

@end
