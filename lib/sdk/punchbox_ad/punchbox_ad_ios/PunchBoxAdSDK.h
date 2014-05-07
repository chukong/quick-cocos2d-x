
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "PBBannerView.h"

@interface PunchBoxAdSDK : NSObject


+ (PunchBoxAdSDK*) getInstance;

// public interface

+ (void) start:(NSDictionary*)options;
+ (void) stop;
+ (void) show:(NSDictionary*)options;
+ (void) remove;
+ (void) addScriptListener:(NSDictionary*)options;
+ (void) removeScriptListener;

+ (UIWindow*)getMainWindow;

@end

