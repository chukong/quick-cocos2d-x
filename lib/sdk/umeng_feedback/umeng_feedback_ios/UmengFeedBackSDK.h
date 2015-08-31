
@interface UmengFeedBackSDK : NSObject

- (void) setView:(UIViewController*)view;
+ (void) showFeedback:(NSDictionary*)option;
+ (void) checkReplies:(NSDictionary*)option;

@end
