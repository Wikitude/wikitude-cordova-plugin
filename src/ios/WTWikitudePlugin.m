//
//  WTWikitudePlugin.m
//  Wikitude
//
//  Copyright (c) 2012 Wikitude. All rights reserved.
//

#import "WTWikitudePlugin.h"

#import "WTARViewController.h"
#import "WikitudeSDK.h"
#import "WTSDKBuildInformation.h"

//------------ Start-up Configuration - begin -------
//
// Note: The keys and values used here have to be in accordance with those specified in WikitudePlungin.js
//

NSString * const kWTWikitudePlugin_ArgumentKeyLicenseKey = @"SDKKey";

NSString * const kWTWikitudePlugin_ArgumentKeyARchitectWorldURL     = @"ARchitectWorldURL";

NSString * const kWTWikitudePlugin_ArgumentFeatureConfiguration     = @"StartupConfiguration";
NSString * const kWTWikitudePlugin_ArgumentIOSConfiguration         = @"iOS";

NSString * const kWTWikitudePlugin_ArgumentRequiredFeatures         = @"RequiredFeatures";
NSString * const kWTWikitudePlugin_requiredFeature_Geo              = @"geo";
NSString * const kWTWikitudePlugin_requiredFeature_ImageTracking    = @"image_tracking";
NSString * const kWTWikitudePlugin_requiredFeature_InstantTracking  = @"instant_tracking";
NSString * const kWTWikitudePlugin_requiredFeature_PhotoLibraryScreenshotImport  = @"photo_library_screenshot_import";
NSString * const kWTWikitudePlugin_requiredFeature_2DTracking       = @"2d_tracking"; /* deprecated in Wikitude SDK version 6.0.0 */

NSString * const kWTWikitudePlugin_ArgumentCaptureDeviceResolution  = @"camera_resolution";
NSString * const kWTWikitudePlugin_captureDeviceResolution_SD_640x480 = @"sd_640x480";
NSString * const kWTWikitudePlugin_captureDeviceResolution_HD_1280x720 = @"hd_1280x720";
NSString * const kWTWikitudePlugin_captureDeviceResolution_FULL_HD_1920x1080 = @"full_hd_1920x1080";
NSString * const kWTWikitudePlugin_captureDeviceResolution_AUTO     = @"auto";

NSString * const kWTWikitudePlugin_ArgumentCameraPosition           = @"camera_position";
NSString * const kWTWikitudePlugin_cameraPosition_Undefined         = @"undefined";
NSString * const kWTWikitudePlugin_cameraPosition_Front             = @"front";
NSString * const kWTWikitudePlugin_cameraPosition_Back              = @"back";

NSString * const kWTWikitudePlugin_ArgumentCameraFocusMode          = @"cameraFocusMode";
NSString * const kWTWikitudePlugin_cameraFocusMode_Locked           = @"locked";
NSString * const kWTWikitudePlugin_cameraFocusMode_AutoFocus        = @"autoFocus";
NSString * const kWTWikitudePlugin_cameraFocusMode_ContinuousAutoFocus = @"continuousAutoFocus";

NSString * const kWTWikitudePlugin_ArgumentCaptureDeviceFocusDistance = @"camera_manual_focus_distance";

NSString * const kWTWikitudePlugin_ArgumentCaptureDeviceFocusRangeRestriction = @"cameraFocusRangeRestriction";
NSString * const kWTWikitudePlugin_cameraFocusRange_None            = @"none";
NSString * const kWTWikitudePlugin_cameraFocusRange_Near            = @"near";
NSString * const kWTWikitudePlugin_cameraFocusRange_Far             = @"far";

NSString * const kWTWikitudePlugin_ArgumentSystemDeviceSensorCalibrationDisplay     = @"shouldUseSystemDeviceSensorCalibrationDisplay";
NSString * const kWTWikitudePlugin_useSystemDeviceSensorCalibrationDispaly_NO       = @"NO";
NSString * const kWTWikitudePlugin_useSystemDeviceSensorCalibrationDispaly_YES      = @"YES";

//------------ Start-up Configuration - end ---------


//------------ plist keys - begin -------
NSString * const kWTWikitudePlugin_localPathPrefix                  = @"WTCordovaPluginLocalPathPrefix";
//------------ plist keys - end ---------



@interface WTWikitudePlugin () <WTArchitectViewDelegate, WTArchitectViewControllerDelegate>

@property (nonatomic, strong) WTAuthorizationRequestManager         *authorizationRequestManager;
@property (nonatomic, strong) WTArchitectViewController             *arViewController;

@property (nonatomic, strong) NSString                              *loadArchitectWorldCallbackId;
@property (nonatomic, strong) NSString                              *urlInvokedCallbackId;
@property (nonatomic, strong) NSString                              *receivedJSONObjectCallbackId;
@property (nonatomic, strong) NSString                              *screenshotCallbackId;
@property (nonatomic, strong) NSString                              *errorHandlerCallbackId;
@property (nonatomic, strong) NSString                              *accessRequestCallbackId;
@property (nonatomic, strong) NSString                              *deviceSensorsNeedCalibrationCallbackId;
@property (nonatomic, strong) NSString                              *deviceSensorsFinishedCalibrationCallbackId;

@property (nonatomic, assign) BOOL                                  isUsingInjectedLocation;
@property (nonatomic, assign) BOOL                                  isDeviceSupported;

@end


@implementation WTWikitudePlugin

+ (void)readStartupConfigurationFrom:(NSDictionary *)arguments andApplyTo:(WTStartupConfiguration *)configuration
{
    if (arguments && configuration)
    {
        NSDictionary *featureConfiguration = [arguments objectForKey:kWTWikitudePlugin_ArgumentFeatureConfiguration];
        if(featureConfiguration)
        {
            NSString* captureDeviceResolution = [featureConfiguration objectForKey:kWTWikitudePlugin_ArgumentCaptureDeviceResolution];
            if (captureDeviceResolution)
            {
                if ( [kWTWikitudePlugin_captureDeviceResolution_SD_640x480 isEqualToString:captureDeviceResolution] )
                {
                    configuration.captureDeviceResolution = WTCaptureDeviceResolution_SD_640x480;
                }
                else if ( [kWTWikitudePlugin_captureDeviceResolution_HD_1280x720 isEqualToString:captureDeviceResolution] )
                {
                    configuration.captureDeviceResolution = WTCaptureDeviceResolution_HD_1280x720;
                }
                else if ( [kWTWikitudePlugin_captureDeviceResolution_FULL_HD_1920x1080 isEqualToString:captureDeviceResolution] )
                {
                    configuration.captureDeviceResolution = WTCaptureDeviceResolution_FULL_HD_1920x1080;
                }
                else if ( [kWTWikitudePlugin_captureDeviceResolution_AUTO isEqualToString:captureDeviceResolution] )
                {
                    configuration.captureDeviceResolution = WTCaptureDeviceResolution_AUTO;
                }
            }

            NSString *cameraPosition = [featureConfiguration objectForKey:kWTWikitudePlugin_ArgumentCameraPosition];
            if(cameraPosition)
            {
                if ( [kWTWikitudePlugin_cameraPosition_Front isEqualToString:cameraPosition] )
                {
                    configuration.captureDevicePosition = AVCaptureDevicePositionFront;
                }
                else if ( [kWTWikitudePlugin_cameraPosition_Back isEqualToString:cameraPosition] )
                {
                    configuration.captureDevicePosition = AVCaptureDevicePositionBack;
                }
                else
                {
                    configuration.captureDevicePosition = AVCaptureDevicePositionUnspecified;
                }
            }

            NSString *cameraFocusMode = [[featureConfiguration objectForKey:kWTWikitudePlugin_ArgumentCameraFocusMode] stringValue];
            if(cameraFocusMode)
            {
                if ( [kWTWikitudePlugin_cameraFocusMode_Locked isEqualToString:cameraFocusMode] )
                {
                    configuration.captureDeviceFocusMode = AVCaptureFocusModeLocked;
                }
                else if ( [kWTWikitudePlugin_cameraFocusMode_AutoFocus isEqualToString:cameraFocusMode] )
                {
                    configuration.captureDeviceFocusMode = AVCaptureFocusModeAutoFocus;
                }
                else if ( [kWTWikitudePlugin_cameraFocusMode_ContinuousAutoFocus isEqualToString:cameraFocusMode] )
                {
                    configuration.captureDeviceFocusMode = AVCaptureFocusModeContinuousAutoFocus;
                }
            }

            NSNumber *captureDeviceFocusDistance = [featureConfiguration objectForKey:kWTWikitudePlugin_ArgumentCaptureDeviceFocusDistance];
            if (captureDeviceFocusDistance)
            {
                configuration.captureDeviceFocusDistance = captureDeviceFocusDistance.floatValue;
            }

            NSDictionary* iOSConfiguration = [featureConfiguration objectForKey:kWTWikitudePlugin_ArgumentIOSConfiguration];
            if(iOSConfiguration)
            {
                NSString *captureDeviceFocusRestriction = [iOSConfiguration objectForKey:kWTWikitudePlugin_ArgumentCaptureDeviceFocusRangeRestriction];
                if(captureDeviceFocusRestriction)
                {
                    if ( [kWTWikitudePlugin_cameraFocusRange_None isEqualToString:captureDeviceFocusRestriction] )
                    {
                        configuration.captureDeviceFocusRangeRestriction = AVCaptureAutoFocusRangeRestrictionNone;
                    }
                    else if ( [kWTWikitudePlugin_cameraFocusRange_Near isEqualToString:captureDeviceFocusRestriction] )
                    {
                        configuration.captureDeviceFocusRangeRestriction = AVCaptureAutoFocusRangeRestrictionNear;
                    }
                    else if ( [kWTWikitudePlugin_cameraFocusRange_Far isEqualToString:captureDeviceFocusRestriction] )
                    {
                        configuration.captureDeviceFocusRangeRestriction = AVCaptureAutoFocusRangeRestrictionFar;
                    }
                }

                NSString *systemDeviceSensorCalibrationSetting = [iOSConfiguration objectForKey:kWTWikitudePlugin_ArgumentSystemDeviceSensorCalibrationDisplay];
                if (systemDeviceSensorCalibrationSetting)
                {
                    if ( [kWTWikitudePlugin_useSystemDeviceSensorCalibrationDispaly_NO isEqualToString:systemDeviceSensorCalibrationSetting] )
                    {
                        configuration.shouldUseSystemDeviceSensorCalibrationDisplay = NO;
                    }
                    else if ( [kWTWikitudePlugin_useSystemDeviceSensorCalibrationDispaly_YES isEqualToString:systemDeviceSensorCalibrationSetting] )
                    {
                        configuration.shouldUseSystemDeviceSensorCalibrationDisplay = YES;
                    }
                }
            }
        }
    }
}


+ (WTFeatures)requiredFeaturesFromArray:(NSArray *)stringArray
{
    WTFeatures requiredFeatures = 0;

    for (id object in stringArray)
    {
        if ( [object isKindOfClass:[NSString class]] )
        {
            NSString *featureString = (NSString *)object;

            if ( [featureString isEqualToString:kWTWikitudePlugin_requiredFeature_Geo] )
            {
                requiredFeatures |= WTFeature_Geo;
            }
            else if ( [featureString isEqualToString:kWTWikitudePlugin_requiredFeature_ImageTracking] || [featureString isEqualToString:kWTWikitudePlugin_requiredFeature_2DTracking] )
            {
                requiredFeatures |= WTFeature_ImageTracking;
            }
            else if ( [featureString isEqualToString:kWTWikitudePlugin_requiredFeature_InstantTracking] )
            {
                requiredFeatures |= WTFeature_InstantTracking;
            }
            else if ( [featureString isEqualToString:kWTWikitudePlugin_requiredFeature_PhotoLibraryScreenshotImport] )
            {
                requiredFeatures |= WTFeature_PhotoLibraryScreenshotImport;
            }
        }
    }

    return requiredFeatures;
}

+ (NSURL *)architectWorldURLFromString:(NSString *)architectWorldFilePath
{
    NSURL *architectWorldURL = nil;

    if ( architectWorldFilePath && ![architectWorldFilePath isKindOfClass:[NSNull class]] )
    {
        NSString *worldName = [architectWorldFilePath lastPathComponent];
        worldName = [worldName stringByDeletingPathExtension];
        NSString *worldNameExtension = [architectWorldFilePath pathExtension];

        NSString *architectWorldDirectoryPath = [architectWorldFilePath stringByDeletingLastPathComponent];

        architectWorldURL = [[NSBundle mainBundle] URLForResource:worldName withExtension:worldNameExtension subdirectory:architectWorldDirectoryPath];
    }

    return architectWorldURL;
}

+ (NSString *)readOptionalPathPrefixFromApplicationPlist
{
    NSString *optionalPathPrefix = nil;

    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    if ( infoDictionary )
    {
        if ( [infoDictionary objectForKey:kWTWikitudePlugin_localPathPrefix] )
        {
            optionalPathPrefix = [infoDictionary objectForKey:kWTWikitudePlugin_localPathPrefix];
        }
    }

    return optionalPathPrefix;
}

+ (NSURL *)addPathPrefix:(NSString *)pathPrefix toArchitectWorldURL:(NSURL *)architectWorldURL
{
    if ( pathPrefix && architectWorldURL )
    {
        NSString *architectWorldString = [architectWorldURL absoluteString];
        NSRange wwwRange = [architectWorldString rangeOfString:@"www"];
        if ( NSNotFound != wwwRange.location )
        {
            NSString *leadingPart = [architectWorldString substringToIndex:wwwRange.location];
            NSString *trailingPart = [architectWorldString substringFromIndex:wwwRange.location];
            NSString *modifiedArchitectWorldString = [leadingPart stringByAppendingPathComponent:pathPrefix];
            modifiedArchitectWorldString = [modifiedArchitectWorldString stringByAppendingPathComponent:trailingPart];

            NSURL *modifiedArchitectWorldURL = [NSURL URLWithString:modifiedArchitectWorldString];
            return modifiedArchitectWorldURL;
        }
        else
        {
            return architectWorldURL;
        }
    }
    else
    {
        return architectWorldURL;
    }
}

#pragma mark - Plugin Methods
#pragma mark Device Support

- (void)isDeviceSupported:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult* pluginResult = nil;

    self.isDeviceSupported = NO;

    if ( [command.arguments count] >= 1 )
    {
        if ( [[command.arguments objectAtIndex:0] isKindOfClass:[NSArray class]] )
        {
            WTFeatures requiredFeatures = [WTWikitudePlugin requiredFeaturesFromArray:[command.arguments objectAtIndex:0]];

            NSError *isDeviceSupportedError = nil;
            self.isDeviceSupported = [WTArchitectView isDeviceSupportedForRequiredFeatures:requiredFeatures error:&isDeviceSupportedError];


            if (self.isDeviceSupported)
            {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:self.isDeviceSupported];
            }
            else
            {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[isDeviceSupportedError localizedDescription]];
            }
        }
    }
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)requestAccess:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;

    if ( [command.arguments count] >= 1 )
    {
        id componentsArray = [command.arguments objectAtIndex:0];
        if ( [componentsArray isKindOfClass:[NSArray class]] )
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
            [pluginResult setKeepCallbackAsBool:YES];
            self.accessRequestCallbackId = command.callbackId;

            if ( !_authorizationRequestManager )
            {
                _authorizationRequestManager = [[WTAuthorizationRequestManager alloc] init];
            }

            WTFeatures requiredFeatures = [WTWikitudePlugin requiredFeaturesFromArray:(NSArray *)componentsArray];
            NSOrderedSet<NSNumber *> *restrictedAppleiOSSDKAPIs = [WTAuthorizationRequestManager restrictedAppleiOSSDKAPIAuthorizationsForRequiredFeatures:requiredFeatures];
            [_authorizationRequestManager requestRestrictedAppleiOSSDKAPIAuthorization:restrictedAppleiOSSDKAPIs completion:^(BOOL success, NSError * _Nonnull error) {
                if ( success )
                {
                    CDVPluginResult *delayedResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
                    [self.commandDelegate sendPluginResult:delayedResult callbackId:self.accessRequestCallbackId];
                }
                else
                {
                    /* Collect information to show an alert and log a message to the console that explains what is missing and how it can be fixed */
                    NSDictionary *unauthorizedAPIInfo = [[error userInfo] objectForKey:kWTUnauthorizedAppleiOSSDKAPIsKey];

                    NSMutableString *detailedAuthorizationErrorLogMessage = [[NSMutableString alloc] initWithFormat:@"The following authorization states do not meet the requirements:"];
                    NSMutableString *missingAuthorizations = [[NSMutableString alloc] initWithFormat:@"In order to use the Wikitude SDK, please grant access to the following:"];
                    for (NSString *unauthorizedAPIKey in [unauthorizedAPIInfo allKeys])
                    {
                        [missingAuthorizations appendFormat:@"\n* %@", [WTAuthorizationRequestManager humanReadableDescriptionForUnauthorizedAppleiOSSDKAPI:unauthorizedAPIKey]];

                        [detailedAuthorizationErrorLogMessage appendFormat:@"\n%@ = %@", unauthorizedAPIKey, [WTAuthorizationRequestManager stringFromAuthorizationStatus:[[unauthorizedAPIInfo objectForKey:unauthorizedAPIKey] integerValue] forUnauthorizedAppleiOSSDKAPI:unauthorizedAPIKey]];
                    }

                    NSDictionary *cordovaAPIErrorInfo = @{@"userDescription": missingAuthorizations, @"developerDescription": detailedAuthorizationErrorLogMessage};

                    CDVPluginResult *delayedResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:cordovaAPIErrorInfo];
                    [self.commandDelegate sendPluginResult:delayedResult callbackId:self.accessRequestCallbackId];
                }
            }];
        }
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)openAppSettings:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    
    NSURL *appSettingsURL = [NSURL URLWithString:UIApplicationOpenSettingsURLString];
    [[UIApplication sharedApplication] openURL:appSettingsURL];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - SDK Informations

- (void)getSDKBuildInformation:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[[WTArchitectView SDKBuildInformation] toJSONString]];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)getSDKVersion:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[WTArchitectView sdkVersion]];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark Plugin Lifecycle

- (void)open:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult* pluginResult = nil;

    if ( self.isDeviceSupported && command.arguments.count )
    {
        id argumentDictionary = [command.arguments firstObject];

        if ( [argumentDictionary isKindOfClass:[NSDictionary class]] )
        {
            NSDictionary *arguments = (NSDictionary *)argumentDictionary;

            NSString *sdkKey = [arguments objectForKey:kWTWikitudePlugin_ArgumentKeyLicenseKey];
            NSString *architectWorldURLString = [arguments objectForKey:kWTWikitudePlugin_ArgumentKeyARchitectWorldURL];


            WTFeatures requiredFeatures = [WTWikitudePlugin requiredFeaturesFromArray:[arguments objectForKey:kWTWikitudePlugin_ArgumentRequiredFeatures]];

            if (!_arViewController)
            {
                self.arViewController = [[WTArchitectViewController alloc] initWithNibName:nil bundle:nil motionManager:nil];
                
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
#pragma clang diagnostic ignored "-Wundeclared-selector"
                if ([self.arViewController.architectView respondsToSelector:@selector(setSDKOrigin:)]) {
                    [self.arViewController.architectView performSelector:@selector(setSDKOrigin:) withObject:@"ORIGIN_PHONEGAP"];
                }
#pragma clang diagnostic pop
                
                [self.arViewController.architectView setLicenseKey:sdkKey];

                self.arViewController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
                self.arViewController.architectDelegate = self;
            }
            self.arViewController.startSDKAfterAppResume = YES;
            self.arViewController.architectView.requiredFeatures = requiredFeatures;
            [self.viewController presentViewController:self.arViewController animated:YES completion:nil];

            [self addNotificationObserver];


            NSURL *architectWorldURL = [NSURL URLWithString:architectWorldURLString];
            if ( !architectWorldURL || ![architectWorldURL scheme] )
            {
                architectWorldURL = [WTWikitudePlugin architectWorldURLFromString:architectWorldURLString];
            }
            if ( architectWorldURL )
            {
                NSString *optionalPathPrefix = [WTWikitudePlugin readOptionalPathPrefixFromApplicationPlist];
                if ( optionalPathPrefix ) {
                    architectWorldURL = [WTWikitudePlugin addPathPrefix:optionalPathPrefix toArchitectWorldURL:architectWorldURL];
                }
                self.arViewController.currentArchitectWorldNavigation = [self.arViewController.architectView loadArchitectWorldFromURL:architectWorldURL];

                self.loadArchitectWorldCallbackId = command.callbackId;
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
                [pluginResult setKeepCallbackAsBool:YES];
            }
            else
            {
                self.loadArchitectWorldCallbackId = nil;
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[NSString stringWithFormat:@"Unable to determine the url to load: %@", architectWorldURLString]];
                [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
            }

            __weak WTWikitudePlugin *weakSelf = self;
            [self.arViewController.architectView start:^(WTArchitectStartupConfiguration *configuration) {
                [WTWikitudePlugin readStartupConfigurationFrom:arguments andApplyTo:configuration];
                [WTArchitectStartupConfiguration transferArchitectStartupConfiguration:configuration toArchitectStartupConfiguration:weakSelf.arViewController.startupConfiguration];
            } completion:nil];
        }
    }
}

- (void)close:(CDVInvokedUrlCommand *)command
{

    CDVPluginResult* pluginResult = nil;


    if (self.arViewController)
    {
        [self.arViewController.architectView stop];

        [self removeNotificationObserver];

        __weak WTWikitudePlugin *weakSelf = self;
        [self.viewController dismissViewControllerAnimated:YES completion:^
         {
             /* nil out the strong reference because it’s not longer needed. ‘show’ and ‘hide’ can handle nil controller and are supposed to be only used during an active presentation of our plugin */
             weakSelf.arViewController = nil;
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
        [self.arViewController setStartSDKAfterAppResume:YES];
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
        [self.arViewController setStartSDKAfterAppResume:NO];
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

- (void)onJSONObjectReceived:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    
    self.receivedJSONObjectCallbackId = command.callbackId;
    
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
    [pluginResult setKeepCallbackAsBool:YES];
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark Device sensor calibration
- (void)setDeviceSensorsNeedCalibrationHandler:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;

    self.deviceSensorsNeedCalibrationCallbackId = command.callbackId;

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
    [pluginResult setKeepCallbackAsBool:YES];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)setDeviceSensorsFinishedCalibrationHandler:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;

    self.deviceSensorsFinishedCalibrationCallbackId = command.callbackId;

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
    [pluginResult setKeepCallbackAsBool:YES];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark Error handling
- (void)setErrorHandler:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;

    self.errorHandlerCallbackId = command.callbackId;

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
    [pluginResult setKeepCallbackAsBool:YES];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - Notifications
#pragma mark WTArchitectViewController

- (void)didReceiveWorldDidLoadNotification:(NSNotification *)aNotification
{
    NSURL *worldURL = [[aNotification userInfo] objectForKey:WTArchitectNotificationURLKey];

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:[worldURL absoluteString]];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.loadArchitectWorldCallbackId];
}

- (void)didReceiveWorldDidFailToLoadNotification:(NSNotification *)aNotification
{
    NSError *error = [[aNotification userInfo] objectForKey:WTArchitectNotificationErrorKey];

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:[error localizedDescription]];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.loadArchitectWorldCallbackId];
}

- (void)didReceiveInvokedURLNotification:(NSNotification *)aNotification
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

- (void)didReceiveReceivedJSONObjectNotification:(NSNotification *)aNotification
{
    CDVPluginResult *pluginResult = nil;
    
    if (self.receivedJSONObjectCallbackId)
    {
        NSDictionary *jsonObject = [[aNotification userInfo] objectForKey:WTArchitectNotificationJSONObjectKey];
        
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:jsonObject];
        [pluginResult setKeepCallbackAsBool:YES];
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }
    
    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.receivedJSONObjectCallbackId];
}

- (void)didReceiveDidCapturedScreenNotification:(NSNotification *)aNotification
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

- (void)didReceiveCaptureScreenDidFailNotification:(NSNotification *)aNotification
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

- (void)didReceiveArchitectNeedsDeviceSensorCalibrationNotification:(NSNotification *)aNotification
{
    if ( self.deviceSensorsNeedCalibrationCallbackId )
    {
        CDVPluginResult *pluginResult = nil;

        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];

        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.deviceSensorsNeedCalibrationCallbackId];
    }
}

- (void)didReceiveArchitectFinishedDeviceSensorCalibrationNotification:(NSNotification *)aNotification
{
    if ( self.deviceSensorsFinishedCalibrationCallbackId )
    {
        CDVPluginResult *pluginResult = nil;

        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];

        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.deviceSensorsFinishedCalibrationCallbackId];
    }
}

- (void)didReceiveArchitectDebugMessageNotification:(NSNotification *)aNotification
{
    if ( self.errorHandlerCallbackId )
    {
        CDVPluginResult *pluginResult = nil;

        NSError *error = [[aNotification userInfo] objectForKey:WTArchitectDebugDelegateMessageKey];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsDictionary:@{@"code": @(error.code), @"message": [error localizedDescription]}];

        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.errorHandlerCallbackId];
    }
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
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveWorldDidLoadNotification:) name:WTArchitectDidLoadWorldNotification object:self.arViewController];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveWorldDidFailToLoadNotification:) name:WTArchitectDidFailToLoadWorldNotification object:self.arViewController];


    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveInvokedURLNotification:) name:WTArchitectInvokedURLNotification object:self.arViewController];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveReceivedJSONObjectNotification:) name:WTArchitectReceivedJSONObjectNotification object: self.arViewController];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveDidCapturedScreenNotification:) name:WTArchitectDidCaptureScreenNotification object:self.arViewController];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveCaptureScreenDidFailNotification:) name:WTArchitectDidFailToCaptureScreenNotification object:self.arViewController];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveArchitectNeedsDeviceSensorCalibrationNotification:) name:WTArchitectNeedsDeviceSensorCalibration object:self.arViewController];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveArchitectFinishedDeviceSensorCalibrationNotification:) name:WTArchitectFinishedDeviceSensorCalibration object:self.arViewController];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didReceiveArchitectDebugMessageNotification:) name:WTArchitectDebugDelegateNotification object:self.arViewController];
}

- (void)removeNotificationObserver
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
