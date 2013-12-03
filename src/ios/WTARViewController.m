//
//  WTARViewController.m
//  HelloWorld
//
//  Created by Andreas Schacherbauer on 2/7/13.
//
//

#import "WTARViewController.h"
#import "WTArchitectView.h"


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
            
            
            if ([self.architectView respondsToSelector:@selector(setSDKOrigin:)]) {
                [self.architectView performSelector:@selector(setSDKOrigin:) withObject:@"ORIGIN_PHONEGAP"];
            }
            if ([self.architectView respondsToSelector:@selector(setPresentingViewController:)]) {
                [self.architectView performSelector:@selector(setPresentingViewController:) withObject:self];
            }
            
            [self.architectView initializeWithKey:sdkKeyorNil motionManager:cmMotionManagerOrNil];
            
            
            self.view = self.architectView;
            self.view.backgroundColor = [UIColor clearColor];
            
            
            UISwipeGestureRecognizer *swipeBackRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipeBack:)];
            swipeBackRecognizer.direction = UISwipeGestureRecognizerDirectionRight;
            
            [self.view addGestureRecognizer:swipeBackRecognizer];
        }
    }
    return self;
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    [self.architectView setShouldRotate:YES
                 toInterfaceOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
    
}

- (void)didSwipeBack:(UISwipeGestureRecognizer *)recognizer
{
    if (self.delegate) {
        if ([self.delegate respondsToSelector:@selector(arViewControllerWillDisappear:)]) {
            [self.delegate arViewControllerWillDisappear:self];
        }
    }
}


#pragma mark - Orientation handling iOS 6

- (BOOL)shouldAutorotate
{
    return YES;
}

- (NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskAll;
}

#pragma mark Orientation handling iOS 5
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    return YES;
}

#pragma mark Orientation handling Wikitude
- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    BOOL shouldRotate = UIInterfaceOrientationIsLandscape(toInterfaceOrientation);
    
    [self.architectView setShouldRotate:shouldRotate toInterfaceOrientation:toInterfaceOrientation];
}

@end
