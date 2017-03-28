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
NSString * const WTArchitectReceivedJSONObjectNotification = @"WTArchitectReceivedJSONObjectNotification";
NSString * const WTArchitectDidCaptureScreenNotification = @"WTArchitectDidCaptureScreenNotification";
NSString * const WTArchitectDidFailToCaptureScreenNotification = @"WTArchitectDidFailToCaptureScreenNotification";

NSString * const WTArchitectNeedsDeviceSensorCalibration = @"WTArchitectNeedsDeviceSensorCalibration";
NSString * const WTArchitectFinishedDeviceSensorCalibration = @"WTArchitectFinishedDeviceSensorCalibration";

NSString * const WTArchitectDebugDelegateNotification = @"WTArchitectDebugDelegateNotification";

NSString * const WTArchitectNotificationURLKey = @"URL";
NSString * const WTArchitectNotificationContextKey = @"Context";
NSString * const WTArchitectNotificationJSONObjectKey = @"JSONObject";
NSString * const WTArchitectNotificationErrorKey = @"Error";

NSString * const WTArchitectDebugDelegateMessageKey = @"WTArchitectDebugDelegateMessageKey";



@interface WTArchitectViewController () <UIGestureRecognizerDelegate>

@property (nonatomic, strong) WTArchitectView                               *architectView;
@property (nonatomic, assign) UIInterfaceOrientationMask                    supportedInterfaceOrientationsMask;

@end

@implementation WTArchitectViewController


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil motionManager:(CMMotionManager *)motionManagerOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        _startupConfiguration = [[WTArchitectStartupConfiguration alloc] init];
        
        self.architectView = [[WTArchitectView alloc] initWithFrame:[[UIScreen mainScreen] bounds] motionManager:motionManagerOrNil];
        self.architectView.delegate = self;
        self.architectView.debugDelegate = self;
        _startSDKAfterAppResume = YES;
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveDeviceWillResignActiveNotification:) name:UIApplicationWillResignActiveNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveDeviceDidBecomeActiveNotification:) name:UIApplicationDidBecomeActiveNotification object:nil];
    }
    
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}


#pragma mark - UIViewController Overriding

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self.architectView setFrame:self.view.bounds];
    [self.view addSubview:self.architectView];
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
#pragma clang diagnostic ignored "-Wundeclared-selector"
    if ([self.architectView respondsToSelector:@selector(setPresentingViewController:)]) {
        [self.architectView performSelector:@selector(setPresentingViewController:) withObject:self];
    }
#pragma clang diagnostic pop

    [self.architectView setShouldRotate:YES toInterfaceOrientation:[[UIApplication sharedApplication] statusBarOrientation]];


    UISwipeGestureRecognizer *swipeBackRecognizer = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(didSwipeBack:)];
    swipeBackRecognizer.direction = UISwipeGestureRecognizerDirectionRight;
    swipeBackRecognizer.delegate = self;
    
    [self.view addGestureRecognizer:swipeBackRecognizer];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];

    if ( self.presentingViewController && ![self.architectView isRunning] ) {
        [self.architectView start:^(WTArchitectStartupConfiguration *configuration) {
            [WTArchitectStartupConfiguration transferArchitectStartupConfiguration:self.startupConfiguration toArchitectStartupConfiguration:configuration];
        } completion:nil];
    }

    [self.architectView setShouldRotate:YES toInterfaceOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    if ( self.presentingViewController && [self.architectView isRunning] ) {
        [self.architectView stop];
    }
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
#pragma mark UIGestureRecognizerDelegate
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}

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

- (void)architectView:(WTArchitectView *)architectView receivedJSONObject:(NSDictionary *)jsonObject
{
    [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectReceivedJSONObjectNotification object:self userInfo:@{WTArchitectNotificationJSONObjectKey: jsonObject}];
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

- (void)architectViewNeedsDeviceSensorCalibration:(WTArchitectView *)architectView
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectNeedsDeviceSensorCalibration object:self];
    });
}

- (void)architectViewFinishedDeviceSensorsCalibration:(WTArchitectView *)architectView
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [[NSNotificationCenter defaultCenter] postNotificationName:WTArchitectFinishedDeviceSensorCalibration object:self];
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

- (void)didReceiveDeviceWillResignActiveNotification:(NSNotification *)aNotification
{
    /* If we’re presented then we need to stop the sdk view */
    if ( [self.architectView isRunning] ) {
        [self.architectView stop];
    }
}

- (void)didReceiveDeviceDidBecomeActiveNotification:(NSNotification *)aNotification
{
    if ( _startSDKAfterAppResume && ![self.architectView isRunning] ) {
        [self.architectView start:^(WTArchitectStartupConfiguration *configuration) {
            [WTArchitectStartupConfiguration transferArchitectStartupConfiguration:self.startupConfiguration toArchitectStartupConfiguration:configuration];
        } completion:nil];
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
