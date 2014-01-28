//
//  WTWikitudeSDK.m
//  HelloWorld
//
//  Created by Andreas Schacherbauer on 8/24/12.
//
//

#import "WTWikitudePlugin.h"

// Wikitude SDK
#import "WTARViewController.h"
#import "WTArchitectView.h"




@interface WTWikitudePlugin () <WTArchitectViewDelegate, WTARViewControllerDelegate>

@property (nonatomic, strong) WTARViewController                            *arViewController;

@property (nonatomic, strong) NSString                                      *currentARchitectViewCallbackID;
@property (nonatomic, strong) NSString                                      *currentPlugInErrorCallback;

@property (nonatomic, strong) NSString                                      *currentARchitectViewScreenshotCallbackId;

@property (nonatomic, assign) BOOL                                          isUsingInjectedLocation;
@property (nonatomic, assign) BOOL                                          isDeviceSupported;

@end


@implementation WTWikitudePlugin



#pragma mark - View Lifecycle
/* View Lifecycle */
- (void)isDeviceSupported:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    
    @try {
        
        self.isDeviceSupported = false;
        
        if ( [command.arguments count] >= 1 ) {
            
            NSString *geoMode = [command.arguments objectAtIndex:0];
            if ( [[geoMode lowercaseString] isEqualToString:@"geo"] ) {
                
                self.isDeviceSupported = [WTARViewController isGeoSupported];
            }else if ( [[geoMode lowercaseString] isEqualToString:@"ir"] ) {
                
                self.isDeviceSupported = [WTARViewController isIRSupported];
            }
        }
        
        
        if (self.isDeviceSupported) {
            
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:self.isDeviceSupported];
            
        } else {
            
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsInt:self.isDeviceSupported];
        }
        
        
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


- (void)open:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    
    @try {
        
        
        BOOL enabled = self.isDeviceSupported;
        if ( enabled && 2 == command.arguments.count ) {
            
            NSString *sdkKey = [command.arguments objectAtIndex:0];
            NSString *architectWorldFilePath = [command.arguments objectAtIndex:1];
            
            if (!_arViewController) {
                self.arViewController = [[WTARViewController alloc] initWithNibName:nil bundle:nil sdkKey:sdkKey motionManager:nil];
                self.arViewController.architectView.delegate = self;
                self.arViewController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
                self.arViewController.delegate = self;
            }
            
            
            [self.viewController presentViewController:self.arViewController animated:YES completion:^{
                // completion code
            }];
            
            
            
            // and finaly load the architect world, specified in the open function in js
            if ( architectWorldFilePath && ![architectWorldFilePath isKindOfClass:[NSNull class]] ) {
                
                NSURL *architectWorldURL;
                if ([architectWorldFilePath hasPrefix:@"http"]) {
                    
                    architectWorldURL = [NSURL URLWithString:architectWorldFilePath];
                    
                } else {
                    
                    NSString *worldName = [architectWorldFilePath lastPathComponent];
                    worldName = [worldName stringByDeletingPathExtension];
                    NSString *worldNameExtension = [architectWorldFilePath pathExtension];
                    
                    NSString *architectWorldDirectoryPath = [architectWorldFilePath stringByDeletingLastPathComponent];
                    
                    architectWorldURL = [[NSBundle mainBundle] URLForResource:worldName withExtension:worldNameExtension subdirectory:architectWorldDirectoryPath];
                    
                }
                
                [self.arViewController.architectView loadArchitectWorldFromUrl:architectWorldURL];
            }
        }
        
        // start the sdk view updates
        [self.arViewController.architectView start];
        self.arViewController.isARchitectViewRunning = YES;
        
        
        if ( enabled ) {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:nil];
            
        } else {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
            
        }
    } @catch (NSException* exception) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
        
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)close:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    @try {
        
        if (self.arViewController) {
            
            [self.arViewController.architectView stop];
            self.arViewController.isARchitectViewRunning = NO;
            
            [self.viewController dismissModalViewControllerAnimated:YES];
            
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:nil];
        }else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        }
        
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)show:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    @try {
        
        if (self.arViewController) {
            
            [self.viewController presentViewController:self.arViewController animated:YES completion:nil];
            
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:nil];
        }else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_INVALID_ACTION messageAsString:@"Wikitude Plugin not loaded. You first have to call load and then show."];
            NSLog(@"Wikitude Plugin not loaded. You first have to call load and then show.");
        }
        
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    
    if (command) {
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

- (void)hide:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    @try {
        
        if (self.arViewController) {
            
            [self.viewController dismissViewControllerAnimated:YES completion:nil];
            
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:nil];
        }else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        }
        
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)onResume:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    @try {
        
        /* Intentionally left blank */
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT messageAsString:nil];
        
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)onPause:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    @try {

        /* Intentionally left blank */
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT messageAsString:nil];
        
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - Capture Screen

- (void)captureScreen:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    
    @try {
        
        if (self.arViewController && self.arViewController.isARchitectViewRunning) {
            
            if ( 2 == command.arguments.count ) { // only proceed if the two required parameters are given
                
                self.currentARchitectViewScreenshotCallbackId = command.callbackId;
                
                
                WTScreenshotCaptureMode captureMode = [[command.arguments objectAtIndex:0] boolValue] ? WTScreenshotCaptureMode_CamAndWebView : WTScreenshotCaptureMode_Cam;
                
                
                WTScreenshotSaveMode saveMode;
                NSString *screenshotBundlePath = nil;
                if ( [[command.arguments objectAtIndex:1] isKindOfClass:[NSString class]] ) {
                    
                    saveMode = WTScreenshotSaveMode_BundleDirectory;
                    screenshotBundlePath = [command.arguments objectAtIndex:1];
                    
                } else {
                    
                    saveMode = WTScreenshotSaveMode_PhotoLibrary;
                }
                
                WTScreenshotSaveOptions options = WTScreenshotSaveOption_SavingWithoutOverwriting | WTScreenshotSaveOption_CallDelegateOnSuccess;
                
                [self.arViewController.architectView captureScreenWithMode:captureMode usingSaveMode:saveMode saveOptions:options context: screenshotBundlePath ? @{kWTScreenshotBundleDirectoryKey: screenshotBundlePath} : nil];
            }
        }
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
        [pluginResult setKeepCallbackAsBool:YES];
    }
    @catch (NSException *exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - Location Handling

- (void)setLocation:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    
    @try {
        
        if ( self.arViewController && 4 == command.arguments.count ) {
            
            float latitude = [[command.arguments objectAtIndex:0] floatValue];
            float longitude = [[command.arguments objectAtIndex:1] floatValue];
            float altitude = [[command.arguments objectAtIndex:2] floatValue];
            float accuracy = [[command.arguments objectAtIndex:3] floatValue];
            
            
            if (!self.isUsingInjectedLocation) {
                [self.arViewController.architectView setUseInjectedLocation:YES];
                self.isUsingInjectedLocation = YES;
            }
            
            [self.arViewController.architectView injectLocationWithLatitude:latitude longitude:longitude altitude:altitude accuracy:accuracy];
            
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        }
        
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


#pragma mark - Javascript

- (void)callJavascript:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    
    @try {
        
        if ( 1 == command.arguments.count ) {
            
            NSMutableString *javascriptToCall = [[command.arguments objectAtIndex:0] mutableCopy];
            
            if (self.arViewController) {
                [self.arViewController.architectView callJavaScript:javascriptToCall];
            }
            
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:nil];
            
        }else
        {
            // return error no javascript to call found
        }
        
        
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


- (void)onUrlInvoke:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    
    @try {
        
        self.currentARchitectViewCallbackID = command.callbackId;
        self.currentPlugInErrorCallback = command.callbackId;
        
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
        [pluginResult setKeepCallbackAsBool:YES];
        
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - WTArchitectView Delegate

- (void)architectView:(WTArchitectView *)architectView invokedURL:(NSURL *)url
{
    
    CDVPluginResult *pluginResult = nil;
    
    
    if (url && self.currentARchitectViewCallbackID) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[url absoluteString]];
        [pluginResult setKeepCallbackAsBool:YES];
        
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.currentARchitectViewCallbackID];
        
    }else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.currentPlugInErrorCallback];
    }
    
}

- (void)architectView:(WTArchitectView *)architectView didFailLoadWithError:(NSError *)error
{
    NSLog(@"Error loading world with error: %@", [error localizedDescription]);
}

- (void)architectView:(WTArchitectView *)architectView didCaptureScreenWithContext:(NSDictionary *)context
{
    
    if (self.currentARchitectViewScreenshotCallbackId) {
        
        WTScreenshotSaveMode mode = [[context objectForKey:kWTScreenshotSaveModeKey] integerValue];
        
        NSString *resultMessage = nil;
        if (WTScreenshotSaveMode_BundleDirectory == mode) {
            resultMessage = [context objectForKey:kWTScreenshotBundleDirectoryKey];
        } else {
            resultMessage = @"Screenshot was added to the device Photo Library";
        }
        
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:resultMessage];
        [pluginResult setKeepCallbackAsBool:YES];

        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.currentARchitectViewScreenshotCallbackId];
    }
}

- (void)architectView:(WTArchitectView *)architectView didFailCaptureScreenWithError:(NSError *)error
{
    
    if (self.currentARchitectViewScreenshotCallbackId) {
        
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[error localizedDescription]];
        [pluginResult setKeepCallbackAsBool:YES];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.currentARchitectViewScreenshotCallbackId];
    }
}

#pragma mark - WTARViewControllerDelegate

- (void)arViewControllerWillDisappear:(WTARViewController *)arViewcontroller
{
    [self close:nil];
}

@end
