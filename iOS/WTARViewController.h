//
//  WTARViewController.h
//  HelloWorld
//
//  Created by Andreas Schacherbauer on 2/7/13.
//
//

#import <UIKit/UIKit.h>


typedef NS_ENUM(NSUInteger, WTARViewLifecycleBehavior)
{
    WTARViewLifecycleBehavior_Will,
    WTARViewLifecycleBehavior_Did
};

@class WTArchitectView;
@class CMMotionManager;


@interface WTARViewController : UIViewController

@property (nonatomic, readonly) WTArchitectView         *architectView;
@property (nonatomic, assign) BOOL                      isARchitectViewRunning;

+ (BOOL)isGeoSupported;
+ (BOOL)isIRSupported;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil sdkKey:(NSString *)sdkKeyorNil motionManager:(CMMotionManager *)cmMotionManagerOrNil;

- (void)setLifecycleBehaviour:(WTARViewLifecycleBehavior)lifecycleBehavior;




@end
