
#import <Foundation/Foundation.h>

#import "PunchBoxAd.h"

@protocol PunchBoxAdDelegate <NSObject>

@optional

- (void) onReceiveAd;
- (void) onDismissScreen;
- (void) onFailedToReceiveAd:(PBRequestError*)requestError;;
- (void) onPresentScreen;

@end
