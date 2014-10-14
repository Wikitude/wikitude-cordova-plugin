//
//  WTWikitudePlugin.m
//  Wikitude
//
//  Copyright (c) 2012 Wikitude. All rights reserved.
//

#import "WTWikitudePlugin.h"

#import "WTARViewController.h"
#import "WTArchitectView.h"


#define kWTWikitudePlugin_ArgumentKeySDKKey @"SDKKey"
#define kWTWikitudePlugin_ArgumentKeyARchitectWorldPath @"ARchitectWorldPath"
#define kWTWikitudePlugin_ArgumentKeyAugmentedRealityMode @"AugmentedRealityMode"

#define kWTWikitudePlugin_AugmentedRealityModeBothCombined @"irandgeo"
#define kWTWikitudePlugin_AugmentedRealityModeBoth @"both"
#define kWTWikitudePlugin_AugmentedRealityModeGeo @"geo"
#define kWTWikitudePlugin_AugmentedRealityModeIR @"ir"

#define kWTWikitudePlugin_RemoteURLPrefix @"http"



@interface WTWikitudePlugin () <WTArchitectViewDelegate, WTArchitectViewControllerDelegate>

@property (nonatomic, strong) WTArchitectViewController                     *arViewController;

@property (nonatomic, strong) NSString                                      *loadArchitectWorldCallbackId;
@property (nonatomic, strong) NSString                                      *urlInvokedCallbackId;
@property (nonatomic, strong) NSString                                      *screenshotCallbackId;

@property (nonatomic, assign) BOOL                                          isUsingInjectedLocation;
@property (nonatomic, assign) BOOL                                          isDeviceSupported;

@end


@implementation WTWikitudePlugin

+ (WTAugmentedRealityMode)augmentedRealityModeFromString:(NSString *)string
{
    WTAugmentedRealityMode augmentedRealityMode = WTAugmentedRealityMode_GeoAndImageRecognition;
    
    if ( [[string lowercaseString] isEqualToString:kWTWikitudePlugin_AugmentedRealityModeBothCombined]
        ||
        [[string lowercaseString] isEqualToString:kWTWikitudePlugin_AugmentedRealityModeBoth] )
    {
        augmentedRealityMode = WTAugmentedRealityMode_Geo;
    }
    else if ( [[string lowercaseString] isEqualToString:kWTWikitudePlugin_AugmentedRealityModeGeo] )
    {
        augmentedRealityMode = WTAugmentedRealityMode_Geo;
    }
    else if ( [[string lowercaseString] isEqualToString:kWTWikitudePlugin_AugmentedRealityModeIR] )
    {
        augmentedRealityMode = WTAugmentedRealityMode_ImageRecognition;
    }
    
    return augmentedRealityMode;
}

+ (NSURL *)architectWorldURLFromString:(NSString *)architectWorldFilePath
{
    NSURL *architectWorldURL = nil;
    
    
    if ( architectWorldFilePath && ![architectWorldFilePath isKindOfClass:[NSNull class]] )
    {
        // remote URL
        if ([architectWorldFilePath hasPrefix:kWTWikitudePlugin_RemoteURLPrefix])
        {
            architectWorldURL = [NSURL URLWithString:architectWorldFilePath];
        }
        else // bundle URL
        {
            NSString *worldName = [architectWorldFilePath lastPathComponent];
            worldName = [worldName stringByDeletingPathExtension];
            NSString *worldNameExtension = [architectWorldFilePath pathExtension];
            
            NSString *architectWorldDirectoryPath = [architectWorldFilePath stringByDeletingLastPathComponent];
            
            architectWorldURL = [[NSBundle mainBundle] URLForResource:worldName withExtension:worldNameExtension subdirectory:architectWorldDirectoryPath];
        }
    }
    
    return architectWorldURL;
}


#pragma mark - Plugin Methods
#pragma mark Device Support

- (void)isDeviceSupported:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    

    self.isDeviceSupported = NO;
    
    if ( [command.arguments count] >= 1 )
    {
        NSString *augmentedRealityModeArgument = [command.arguments objectAtIndex:0];
        WTAugmentedRealityMode augmentedRealityMode = [WTWikitudePlugin augmentedRealityModeFromString:augmentedRealityModeArgument];
        
        self.isDeviceSupported = [WTArchitectViewController isDeviceSupportedForAugmentedRealityMode:augmentedRealityMode];
    }
    
    
    if (self.isDeviceSupported)
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:self.isDeviceSupported];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsInt:self.isDeviceSupported];
    }

    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


#pragma mark Plugin Lifecycle

- (void)open:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    
    BOOL enabled = self.isDeviceSupported;
    if ( enabled && 1 == command.arguments.count )
    {
        id argumentDictionary = [command.arguments firstObject];
        
        if ( [argumentDictionary isKindOfClass:[NSDictionary class]] )
        {
            NSDictionary *arguments = (NSDictionary *)argumentDictionary;
            
            
            NSString *sdkKey = [arguments objectForKey:kWTWikitudePlugin_ArgumentKeySDKKey];
            NSString *architectWorldFilePath = [arguments objectForKey:kWTWikitudePlugin_ArgumentKeyARchitectWorldPath];
            
            WTAugmentedRealityMode augmentedRealityMode = [WTWikitudePlugin augmentedRealityModeFromString:[arguments objectForKey:kWTWikitudePlugin_ArgumentKeyAugmentedRealityMode]];
            
            if (!_arViewController)
            {
                self.arViewController = [[WTArchitectViewController alloc] initWithNibName:nil bundle:nil motionManager:nil];
                
                [self.arViewController.architectView setLicenseKey:sdkKey];
                
                self.arViewController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
                self.arViewController.architectDelegate = self;
            }
            
            [self.viewController presentViewController:self.arViewController animated:YES completion:nil];
            
            [self addNotificationObserver];
            
            
            NSURL *architectWorldURL = [WTWikitudePlugin architectWorldURLFromString:architectWorldFilePath];
            if ( architectWorldURL )
            {
                [self.arViewController.architectView loadArchitectWorldFromURL:architectWorldURL withAugmentedRealityMode:augmentedRealityMode];
                
                self.loadArchitectWorldCallbackId = command.callbackId;
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
                [pluginResult setKeepCallbackAsBool:YES];
            }
            else
            {
                self.loadArchitectWorldCallbackId = nil;
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[NSString stringWithFormat:@"Unable to determine what the url to load should be: %@", architectWorldFilePath]];
            }
            
            
            [self.arViewController.architectView start];
        }
    }
    

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)close:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;

    
    if (self.arViewController)
    {
        [self.arViewController.architectView stop];
        
        [self removeNotificationObserver];
        
        [self.viewController dismissViewControllerAnimated:YES completion:^
        {
            /* nil out the strong reference because it’s not longer needed. ‘show’ and ‘hide’ can handle nil controller and are supposed to only used during a active presentation of our plugin */
            self.arViewController = nil;
        }];
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    
    
    if (command) {
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

- (void)show:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    

    if (self.arViewController)
    {
        [self.viewController presentViewController:self.arViewController animated:YES completion:nil];
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_INVALID_ACTION messageAsString:@"Wikitude Plugin not loaded. You first have to call load and then show."];
        NSLog(@"Wikitude Plugin not loaded. You first have to call load and then show.");
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)hide:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    
    if (self.arViewController)
    {
        [self.viewController dismissViewControllerAnimated:YES completion:nil];
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)onResume:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    

    /* Intentionally left blank */
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)onPause:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    

    /* Intentionally left blank */
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


#pragma mark Screen Capturing

- (void)captureScreen:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;

    
    if (self.arViewController && [self.arViewController.architectView isRunning])
    {
        if ( 2 == command.arguments.count ) // only proceed if the two required parameters are given
        {
            self.screenshotCallbackId = command.callbackId;
            
            
            WTScreenshotCaptureMode captureMode = [[command.arguments objectAtIndex:0] boolValue] ? WTScreenshotCaptureMode_CamAndWebView : WTScreenshotCaptureMode_Cam;
            
            
            WTScreenshotSaveMode saveMode;
            NSString *screenshotBundlePath = nil;
            if ( [[command.arguments objectAtIndex:1] isKindOfClass:[NSString class]] )
            {
                saveMode = WTScreenshotSaveMode_BundleDirectory;
                screenshotBundlePath = [command.arguments objectAtIndex:1];
            }
            else
            {
                saveMode = WTScreenshotSaveMode_PhotoLibrary;
            }
            
            WTScreenshotSaveOptions options = WTScreenshotSaveOption_SavingWithoutOverwriting | WTScreenshotSaveOption_CallDelegateOnSuccess;
            
            [self.arViewController.architectView captureScreenWithMode:captureMode usingSaveMode:saveMode saveOptions:options context: screenshotBundlePath ? @{kWTScreenshotBundleDirectoryKey: screenshotBundlePath} : nil];
        }
    }
    
    
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
    [pluginResult setKeepCallbackAsBool:YES];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


#pragma mark Location Injection

- (void)setLocation:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    
    if ( self.arViewController && 4 == command.arguments.count )
    {
        float latitude = [[command.arguments objectAtIndex:0] floatValue];
        float longitude = [[command.arguments objectAtIndex:1] floatValue];
        float altitude = [[command.arguments objectAtIndex:2] floatValue];
        float accuracy = [[command.arguments objectAtIndex:3] floatValue];
        
        
        if (!self.isUsingInjectedLocation)
        {
            [self.arViewController.architectView setUseInjectedLocation:YES];
            self.isUsingInjectedLocation = YES;
        }
        
        [self.arViewController.architectView injectLocationWithLatitude:latitude longitude:longitude altitude:altitude accuracy:accuracy];
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }

    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


#pragma mark JavaScript

- (void)callJavascript:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    
    if ( 1 == command.arguments.count )
    {
        NSMutableString *javascriptToCall = [[command.arguments objectAtIndex:0] mutableCopy];
        
        if (self.arViewController) {
            [self.arViewController.architectView callJavaScript:javascriptToCall];
        }
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_INVALID_ACTION messageAsString:@"No JavaScript given to evaluate"];
    }

    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


- (void)onUrlInvoke:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    
    self.urlInvokedCallbackId = command.callbackId;
    
    
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
    [pluginResult setKeepCallbackAsBool:YES];
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - Notifications
#pragma mark WTArchitectViewController

- (void)didReceivedWorldDidLoadNotification:(NSNotification *)aNotification
{
    NSURL *worldURL = [[aNotification userInfo] objectForKey:WTArchitectNotificationURLKey];
    
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[worldURL absoluteString]];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.loadArchitectWorldCallbackId];
}

- (void)didReceivedWorldDidFailToLoadNotification:(NSNotification *)aNotification
{
    NSError *error = [[aNotification userInfo] objectForKey:WTArchitectNotificationErrorKey];

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[error localizedDescription]];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.loadArchitectWorldCallbackId];
}

- (void)didReceivedInvokedURLNotification:(NSNotification *)aNotification
{
    CDVPluginResult *pluginResult = nil;
    
    
    NSURL *url = [[aNotification userInfo] objectForKey:WTArchitectNotificationURLKey];
    if (url && self.urlInvokedCallbackId)
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[url absoluteString]];
        [pluginResult setKeepCallbackAsBool:YES];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.urlInvokedCallbackId];
}

- (void)didReceivedDidCatpuredScreenNotification:(NSNotification *)aNotification
{
    CDVPluginResult *pluginResult = nil;
    
    
    if (self.screenshotCallbackId)
    {
        NSDictionary *context = [[aNotification userInfo] objectForKey:WTArchitectNotificationContextKey];
        WTScreenshotSaveMode mode = [[context objectForKey:kWTScreenshotSaveModeKey] integerValue];
        
        
        NSString *resultMessage = nil;
        if (WTScreenshotSaveMode_BundleDirectory == mode)
        {
            resultMessage = [context objectForKey:kWTScreenshotBundleDirectoryKey];
        }
        else
        {
            resultMessage = @"Screenshot was added to the device Photo Library";
        }
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:resultMessage];
        [pluginResult setKeepCallbackAsBool:YES];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.screenshotCallbackId];
}

- (void)didReceivedCaptureScreenDidFailNotification:(NSNotification *)aNotification
{
    CDVPluginResult *pluginResult = nil;
    
    
    if (self.screenshotCallbackId)
    {
        NSError *error = [[aNotification userInfo] objectForKey:WTArchitectNotificationErrorKey];
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[error localizedDescription]];
        [pluginResult setKeepCallbackAsBool:YES];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.screenshotCallbackId];
}


#pragma mark - Delegation
#pragma mark WTARViewControllerDelegate

- (void)architectViewControllerWillDisappear:(WTArchitectViewController *)architectViewController
{
    [self close:nil];
}


#pragma mark - Private Methods

- (void)addNotificationObserver
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceivedWorldDidLoadNotification:) name:WTArchitectDidLoadWorldNotification object:self.arViewController];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceivedWorldDidFailToLoadNotification:) name:WTArchitectDidFailToLoadWorldNotification object:self.arViewController];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceivedInvokedURLNotification:) name:WTArchitectInvokedURLNotification object:self.arViewController];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceivedDidCatpuredScreenNotification:) name:WTArchitectDidCaptureScreenNotification object:self.arViewController];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceivedCaptureScreenDidFailNotification:) name:WTArchitectDidFailToCaptureScreenNotification object:self.arViewController];
}

- (void)removeNotificationObserver
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
