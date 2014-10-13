//
//  WTArchitectViewController.m
//  Wikitude
//
//  Copyright (c) 2014 Wikitude. All rights reserved.
//

#import "WTARViewController.h"
#import "WTArchitectView.h"


NSString * const WTArchitectDidLoadWorldNotification = @"WTArchitectDidLoadWorldNotification";
NSString * const WTArchitectDidFailToLoadWorldNotification = @"WTArchitectDidFailToLoadWorldNotification";
NSString * const WTArchitectInvokedURLNotification = @"WTArchitectInvokedURLNotification";
NSString * const WTArchitectDidCaptureScreenNotification = @"WTArchitectDidCaptureScreenNotification";
NSString * const WTArchitectDidFailToCaptureScreenNotification = @"WTArchitectDidFailToCaptureScreenNotification";

NSString * const WTArchitectNotificationURLKey = @"URL";
NSString * const WTArchitectNotificationContextKey = @"Context";
NSString * const WTArchitectNotificationErrorKey = @"Error";



@interface WTArchitectViewController ()

@property (nonatomic, strong) WTArchitectView                               *architectView;
@property (nonatomic, assign) UIInterfaceOrientationMask                    supportedInterfaceOrientationsMask;

@end

@implementation WTArchitectViewController

+ (BOOL)isDeviceSupportedForAugmentedRealityMode:(WTAugmentedRealityMode)augmentedRealityMode
{
    return [WTArchitectView isDeviceSupportedForAugmentedRealityMode:augmentedRealityMode];
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil motionManager:(CMMotionManager *)motionManagerOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        
        self.architectView = [[WTArchitectView alloc] initWithFrame:[[UIScreen mainScreen] bounds] motionManager:motionManagerOrNil];
        self.architectView.delegate = self;
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceivedDeviceWillResignActiveNotification:) name:UIApplicationWillResignActiveNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceivedDeviceDidBecomeActiveNotification:) name:UIApplicationDidBecomeActiveNotification object:nil];
    }
    
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}


#pragma mark - UIViewController Overriding

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self.architectView setFrame:self.view.bounds];
    [self.view addSubview:self.architectView];
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
#pragma clang diagnostic ignored "-Wundeclared-selector"
    if ([self.architectView respondsToSelector:@selector(setSDKOrigin:)]) {
        [self.architectView performSelector:@selector(setSDKOrigin:) withObject:@"phonegap"];
    }
    if ([self.architectView respondsToSelector:@selector(setPresentingViewController:)]) {
        [self.architectView performSelector:@selector(setPresentingViewController:) withObject:self];
    }
#pragma clang diagnostic pop
    
    [self.architectView setShouldRotate:YES
                 toInterfaceOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
    
    
    UISwipeGestureRecognizer *swipeBackRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipeBack:)];
    swipeBackRecognizer.direction = UISwipeGestureRecognizerDirectionRight;
    
    [self.view addGestureRecognizer:swipeBackRecognizer];
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}


#pragma mark - Public Methods

/* No public methods defined in WTArchitectViewController.h */


#pragma mark - Orientation Handling
#pragma mark iOS 6

- (BOOL)shouldAutorotate
{
    return [self.presentingViewController shouldAutorotate];
}

- (NSUInteger)supportedInterfaceOrientations
{
    return [self.presentingViewController supportedInterfaceOrientations];
}

#pragma mark iOS 5

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    return [self.presentingViewController shouldAutorotateToInterfaceOrientation:toInterfaceOrientation];
}

#pragma mark Wikitude SDK

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    [self.architectView setShouldRotate:YES toInterfaceOrientation:toInterfaceOrientation];
}


#pragma mark - Delegation
#pragma mark WTArchitectView

- (void)architectView:(WTArchitectView *)architectView didFinishLoad:(NSURL *)url
{
    [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectDidLoadWorldNotification object:self userInfo:@{WTArchitectNotificationURLKey: url}];
}

- (void)architectView:(WTArchitectView *)architectView didFailLoadWithError:(NSError *)error
{
    [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectDidFailToLoadWorldNotification object:self userInfo:@{WTArchitectNotificationErrorKey: error}];
}

- (void)architectView:(WTArchitectView *)architectView invokedURL:(NSURL *)url
{
    [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectInvokedURLNotification object:self userInfo:@{WTArchitectNotificationURLKey: url}];
}

- (void)architectView:(WTArchitectView *)architectView didCaptureScreenWithContext:(NSDictionary *)context
{
    [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectDidCaptureScreenNotification object:self userInfo:@{WTArchitectNotificationContextKey: context}];
}

- (void)architectView:(WTArchitectView *)architectView didFailCaptureScreenWithError:(NSError *)error
{
    [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectDidFailToCaptureScreenNotification object:self userInfo:@{WTArchitectNotificationErrorKey: error}];
}


- (UIViewController *)presentingViewControllerForViewControllerPresentationInArchitectView:(WTArchitectView *)architectView
{
    return self;
}

- (void)architectView:(WTArchitectView *)architectView willPresentViewController:(UIViewController *)presentedViewController onViewController:(UIViewController *)presentingViewController
{
    /* Intentionally left blank */
}


#pragma mark - Notifications

- (void)didReceivedDeviceWillResignActiveNotification:(NSNotification *)aNotification
{
    /* If we’re presented then we need to stop the sdk view */
    if ( self.presentingViewController && [self.architectView isRunning] ) {
        [self.architectView stop];
    }
}

- (void)didReceivedDeviceDidBecomeActiveNotification:(NSNotification *)aNotification
{
    if ( self.presentingViewController && ![self.architectView isRunning] ) {
        [self.architectView start];
    }
}


#pragma mark - Private Methods

- (void)didSwipeBack:(UISwipeGestureRecognizer *)recognizer
{
    if (self.architectDelegate) {
        if ([self.architectDelegate respondsToSelector:@selector(architectViewControllerWillDisappear:)]) {
            [self.architectDelegate architectViewControllerWillDisappear:self];
        }
    }
}

@end
