//
//  WTARViewController.m
//  HelloWorld
//
//  Created by Andreas Schacherbauer on 2/7/13.
//
//

#import "WTARViewController.h"
#import <WikitudeSDK/WTArchitectView.h>


@interface WTARViewController ()

@property (nonatomic, strong) WTArchitectView                               *architectView;

@end

@implementation WTARViewController
@synthesize architectView=_architectView;


+ (BOOL)isGeoSupported
{
    return [WTArchitectView isDeviceSupportedForARMode:WTARMode_Geo];
}


+ (BOOL)isIRSupported
{
    return [WTArchitectView isDeviceSupportedForARMode:WTARMode_IR];
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil sdkKey:(NSString *)sdkKeyorNil motionManager:(CMMotionManager *)cmMotionManagerOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        
        if ( !_architectView ) {
            self.architectView = [[WTArchitectView alloc] initWithFrame:self.view.bounds];;
            [self.architectView initializeWithKey:sdkKeyorNil motionManager:cmMotionManagerOrNil];
            
            self.view = self.architectView;
            self.view.backgroundColor = [UIColor clearColor];
        }
    }
    return self;
}

- (void)setLifecycleBehaviour:(WTARViewLifecycleBehavior)lifecycleBehavior
{
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    [self.architectView setShouldRotate:YES toInterfaceOrientation:toInterfaceOrientation];
}

@end
