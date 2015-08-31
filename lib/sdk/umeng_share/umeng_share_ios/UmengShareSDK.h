
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface UmengShareSDK : NSObject

- (void) setUIView:(UIViewController*) view;

+ (UmengShareSDK*) getInstance;
+ (void) share:(NSDictionary*)options;
+ (void) addScriptListener:(NSDictionary*)options;
+ (void) removeScriptListener;
+ (void) addPlatform:(NSDictionary*)options;
+ (void) removePlatform:(NSDictionary*)options;
+ (void) reorderPlatform:(NSDictionary*)options;
@end
