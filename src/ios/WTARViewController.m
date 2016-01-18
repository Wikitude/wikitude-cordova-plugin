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

NSString * const WTArchitectNeedsHeadingCalibrationNotification = @"WTArchitectNeedsHeadingCalibrationNotification";

NSString * const WTArchitectDebugDelegateNotification = @"WTArchitectDebugDelegateNotification";

NSString * const WTArchitectNotificationURLKey = @"URL";
NSString * const WTArchitectNotificationContextKey = @"Context";
NSString * const WTArchitectNotificationErrorKey = @"Error";

NSString * const WTArchitectDebugDelegateMessageKey = @"WTArchitectDebugDelegateMessageKey";



@interface WTArchitectViewController ()

@property (nonatomic, strong) WTArchitectView                               *architectView;
@property (nonatomic, assign) UIInterfaceOrientationMask                    supportedInterfaceOrientationsMask;

@end

@implementation WTArchitectViewController


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil motionManager:(CMMotionManager *)motionManagerOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        
        self.architectView = [[WTArchitectView alloc] initWithFrame:[[UIScreen mainScreen] bounds] motionManager:motionManagerOrNil];
        self.architectView.delegate = self;
        self.architectView.debugDelegate = self;
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceivedDeviceWillResignActiveNotification:) name:UIApplicationWillResignActiveNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceivedDeviceDidBecomeActiveNotification:) name:UIApplicationDidBecomeActiveNotification object:nil];

        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveDeviceWillChangeStatusBarOrientationNotification:) name:UIApplicationWillChangeStatusBarOrientationNotification object:nil];
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

    [self.architectView setShouldRotate:YES toInterfaceOrientation:[[UIApplication sharedApplication] statusBarOrientation]];


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

- (UIInterfaceOrientationMask)supportedInterfaceOrientations
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

- (void)architectView:(WTArchitectView *)architectView didFinishLoadArchitectWorldNavigation:(WTNavigation *)navigation
{
    [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectDidLoadWorldNotification object:self userInfo:@{WTArchitectNotificationURLKey: navigation.finalURL}];
}

- (void)architectView:(WTArchitectView *)architectView didFailToLoadArchitectWorldNavigation:(WTNavigation *)navigation withError:(NSError *)error
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

- (void)architectViewNeedsHeadingCalibration:(WTArchitectView *)architectView
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectNeedsHeadingCalibrationNotification object:self];
    });
}

#pragma mark WTArchitectViewDebugDelegate
- (void)architectView:(WTArchitectView *)architectView didEncounterInternalWarning:(WTWarning *)warning
{
    /* Intentionally Left Blank */
}

- (void)architectView:(WTArchitectView *)architectView didEncounterInternalError:(NSError *)error
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectDebugDelegateNotification object:self userInfo:@{WTArchitectDebugDelegateMessageKey: error}];
    });
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
        [self.architectView start:^(WTStartupConfiguration *configuration) {
            configuration = self.startupConfiguration;
        } completion:nil];
    }
}

- (void)didReceiveDeviceWillChangeStatusBarOrientationNotification:(NSNotification *)aNotification
{
    if ( !self.presentingViewController )
    {
        UIInterfaceOrientation newInterfaceOrientation = [[[aNotification userInfo] objectForKey:UIApplicationStatusBarOrientationUserInfoKey] integerValue];
        [self.architectView setShouldRotate:YES toInterfaceOrientation:newInterfaceOrientation];
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
