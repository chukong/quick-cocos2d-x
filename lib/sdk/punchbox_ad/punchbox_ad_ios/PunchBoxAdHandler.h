
#import <Foundation/Foundation.h>

#import "PunchBoxAd.h"
#import "PBBannerView.h"
#import "PBInterstitial.h"
#import "PBMoreGame.h"

#import "PunchBoxAdDelegate.h"

@interface PunchBoxAdHandler : NSObject <PBBannerViewDelegate, PBInterstitialDelegate, PBMoreGameDelegate>
{
    id <PunchBoxAdDelegate> delegate;
    NSString* adType;
    NSString* adId;
    NSString* adPosition;
    
    PBBannerView* bannerView;
    BOOL adRequest;
    BOOL adVisible;
}

- (id)initWithDelegate:(id<PunchBoxAdDelegate>)delegate_
               andType:(NSString*)adType_
               andAdId:(NSString*)adId_
           andPosition:(NSString*)adPosition_;

- (void)show;
- (void)remove;

@end
