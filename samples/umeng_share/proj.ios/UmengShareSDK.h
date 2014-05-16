
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface UmengShareSDK : NSObject

- (void) setAppKey:(NSString*) appid;
- (void) setUIView:(UIViewController*) view;

+ (UmengShareSDK*) getInstance;
+ (void) share:(NSDictionary*)options;
+ (void) addScriptListener:(NSDictionary*)options;
+ (void) removeScriptListener;
@end
