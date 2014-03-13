
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "PunchBoxAdHandler.h"
#import "PunchBoxAdDelegate.h"

@interface PunchBoxAdSDK : NSObject <PunchBoxAdDelegate>
{
    NSString* appId;
    int listener;
    PunchBoxAdHandler* adHandler;
}

+ (PunchBoxAdSDK*) getInstance;
+ (void) purgeInstance;

// script interface

+ (BOOL) start:(NSDictionary*)options;
+ (void) stop;
+ (BOOL) show:(NSDictionary*)options;
+ (void) remove;
+ (BOOL) addScriptListener:(NSDictionary*)options;
+ (void) removeScriptListener;


// internal interface

- (BOOL) start:(NSString*)appId;
- (void) stop;
- (BOOL) show:(NSString*)adType withId:(NSString*)adId andPosition:(NSString*)adPosition;
- (void) remove;
- (void) addScriptListener:(int)listener;
- (void) removeScriptListener;


// PunchBoxAdDelegate

- (void) onReceiveAd;
- (void) onDismissScreen;
- (void) onFailedToReceiveAd:(PBRequestError*)requestError;
- (void) onPresentScreen;

@end

