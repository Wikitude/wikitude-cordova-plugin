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
#import <WikitudeSDK/WTArchitectView.h>




@interface WTWikitudePlugin () <WTArchitectViewDelegate>

@property (nonatomic, strong) WTARViewController                            *arViewController;

@property (nonatomic, strong) NSString                                      *currentARchitectViewCallbackID;
@property (nonatomic, strong) NSString                                      *currentPlugInErrorCallback;

@property (nonatomic, assign) BOOL                                          isUsingInjectedLocation;
@property (nonatomic, assign) BOOL                                          isDeviceSupported;

@end


@implementation WTWikitudePlugin



#pragma mark - View Lifecycle
/* View Lifecycle */
- (void)isDeviceSupported:(CDVInvokedUrlCommand *)command
{
<<<<<<< HEAD
        
=======
    
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    CDVPluginResult* pluginResult = nil;
    
    
    @try {
<<<<<<< HEAD

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

=======
        
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
            
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
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
<<<<<<< HEAD

=======
    
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    CDVPluginResult* pluginResult = nil;
    
    
    @try {
<<<<<<< HEAD

=======
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
        
        BOOL enabled = self.isDeviceSupported;
        if ( enabled && 2 == command.arguments.count ) {
            
            NSString *sdkKey = [command.arguments objectAtIndex:0];
            NSString *architectWorldFilePath = [command.arguments objectAtIndex:1];
            
            if (!_arViewController) {
                self.arViewController = [[WTARViewController alloc] initWithNibName:nil bundle:nil sdkKey:sdkKey motionManager:nil];
                self.arViewController.architectView.delegate = self;
                self.arViewController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
            }
            
<<<<<<< HEAD

            [self.viewController presentViewController:self.arViewController animated:YES completion:^{
                // completion code
            }];
=======
            
            [self.viewController presentViewController:self.arViewController animated:YES completion:^{
                // completion code
            }];
            
            
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
            
                        
            // and finaly load the architect world, specified in the open function in js
            if (architectWorldFilePath) {
                
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
                
<<<<<<< HEAD
                NSString *architectWorldDirectoryPath = [architectWorldFilePath stringByDeletingLastPathComponent];

                NSString *loadablePath = [[NSBundle mainBundle] pathForResource:worldName ofType:worldNameExtension inDirectory:architectWorldDirectoryPath];
                [self.arViewController.architectView loadArchitectWorldFromUrl:loadablePath];
=======
                [self.arViewController.architectView loadArchitectWorldFromUrl:architectWorldURL];
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
            }
        }
        
        // start the sdk view updates
        [self.arViewController.architectView start];
        self.arViewController.isARchitectViewRunning = YES;
        
        
        if ( enabled ) {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:nil];
<<<<<<< HEAD

        } else {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];

        }
    } @catch (NSException* exception) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];

=======
            
        } else {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
            
        }
    } @catch (NSException* exception) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)close:(CDVInvokedUrlCommand *)command
{
<<<<<<< HEAD

=======
    
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
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
<<<<<<< HEAD
    
=======
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)show:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    @try {
<<<<<<< HEAD
        
        if (self.arViewController) {

            [self.viewController presentViewController:self.arViewController animated:YES completion:^{
                
            }];
            
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:nil];
        }else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_INVALID_ACTION messageAsString:@"Wikitude Plugin not loaded. You first have to call load and then show."];
            NSLog(@"Wikitude Plugin not loaded. You first have to call load and then show.");
        }        

=======
        
        if (self.arViewController) {
            
            [self.viewController presentViewController:self.arViewController animated:YES completion:^{
                
            }];
            
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:nil];
        }else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_INVALID_ACTION messageAsString:@"Wikitude Plugin not loaded. You first have to call load and then show."];
            NSLog(@"Wikitude Plugin not loaded. You first have to call load and then show.");
        }
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
<<<<<<< HEAD

=======
    
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)hide:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    @try {
        
        if (self.arViewController) {
            
            [self.viewController dismissModalViewControllerAnimated:YES];
<<<<<<< HEAD

=======
            
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:nil];
        }else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        }
<<<<<<< HEAD

=======
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)onResume:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    @try {
<<<<<<< HEAD

=======
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
        if (self.arViewController && !self.arViewController.isARchitectViewRunning) {
            [self.arViewController.architectView start];
            self.arViewController.isARchitectViewRunning = YES;
        }
        
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT messageAsString:nil];
<<<<<<< HEAD

=======
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
<<<<<<< HEAD

=======
    
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)onPause:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
    
    @try {
<<<<<<< HEAD

=======
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
        if (self.arViewController && self.arViewController.isARchitectViewRunning) {
            [self.arViewController.architectView stop];
            self.arViewController.isARchitectViewRunning = NO;
        }
        
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT messageAsString:nil];
        
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
<<<<<<< HEAD

=======
    
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - Location Handling

- (void)setLocation:(CDVInvokedUrlCommand *)command
{
    
    CDVPluginResult* pluginResult = nil;
<<<<<<< HEAD
 
=======
    
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    
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
<<<<<<< HEAD
    
=======
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    } @catch (NSException* exception) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION messageAsString:[exception reason]];
    }
    
<<<<<<< HEAD

=======
    
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}


#pragma mark - Javascript

- (void)callJavascript:(CDVInvokedUrlCommand *)command
{
<<<<<<< HEAD

=======
    
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
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
<<<<<<< HEAD

=======
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
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

- (void)urlWasInvoked:(NSString *)url
{
    
    CDVPluginResult *pluginResult = nil;
    
    
    if (url && self.currentARchitectViewCallbackID) {
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:url];
        [pluginResult setKeepCallbackAsBool:YES];
<<<<<<< HEAD

=======
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.currentARchitectViewCallbackID];
        
    }else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
<<<<<<< HEAD
    
=======
        
>>>>>>> Updates iOS PhoneGap package to Wikitude SDK 3.0 and PhoneGap 2.8;
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.currentPlugInErrorCallback];
    }
    
}

@end
