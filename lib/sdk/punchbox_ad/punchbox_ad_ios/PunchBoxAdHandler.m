
#import "PunchBoxAdHandler.h"

@implementation PunchBoxAdHandler

- (id)initWithDelegate:(id<PunchBoxAdDelegate>)delegate_
               andType:(NSString*)adType_
               andAdId:(NSString*)adId_
           andPosition:(NSString*)adPosition_
{
    delegate = delegate_;
    adType = [[NSString stringWithString:adType_] retain];
    adId = [[NSString stringWithString:adId_] retain];
    adPosition = [[NSString stringWithString:adPosition_] retain];
    return [self init];
}

- (void)dealloc
{
    NSLog(@"[PunchBoxAdHandler] dealloc");
    [adType release];
    [adId release];
    [adPosition release];
    [super dealloc];
}

- (void)show
{
    if (adRequest) {
        NSLog(@"[PunchBoxAdHandler] a request already exists");
        return;
    }
    
    PBADRequest* request = [PBADRequest request];
    [request setPlacementID:adId];
    
    if ([adType compare:@"banner" options:NSCaseInsensitiveSearch] == NSOrderedSame) {
        CGRect frameBanner = CGRectMake(0.0f, 0.0f, 320.0f, 50.0f);
        bannerView = [[PBBannerView alloc] initWithFrame:frameBanner];
        [bannerView setDelegate:self];
        [bannerView loadRequest:request];
        UIWindow* rootView = [[[UIApplication sharedApplication] windows] objectAtIndex:0];
        [rootView addSubview:bannerView];
        [bannerView release];
    } else if ([adType compare:@"interstitial" options:NSCaseInsensitiveSearch] == NSOrderedSame) {
        [[PBInterstitial sharedInterstitial] loadInterstitial:request];
        [[PBInterstitial sharedInterstitial] setDelegate:self];
    } else if ([adType compare:@"moregame" options:NSCaseInsensitiveSearch] == NSOrderedSame) {
        [[PBMoreGame sharedMoreGame] loadMoreGame:request];
        [[PBMoreGame sharedMoreGame] setDelegate:self];
    } else {
        NSLog(@"[PunchBoxAdHandler] invalid ad type %@", adType);
    }
}

- (void)remove
{
    if (!adVisible) {
        NSLog(@"[PunchBoxAdHandler] no request");
        return;
    }
    
    NSLog(@"[PunchBoxAdHandler] remove");
    
    adVisible = NO;
    adRequest = NO;
    
    if ([adType compare:@"banner" options:NSCaseInsensitiveSearch] == NSOrderedSame) {
        [bannerView setDelegate:nil];
        [bannerView removeFromSuperview];
        bannerView = nil;
    } else if ([adType compare:@"interstitial" options:NSCaseInsensitiveSearch] == NSOrderedSame) {
        [[PBInterstitial sharedInterstitial] setDelegate:nil];
        [[PBInterstitial sharedInterstitial] closeInterstitial];
        [PunchBoxAd closeInterstitial];
    } else if ([adType compare:@"moregame" options:NSCaseInsensitiveSearch] == NSOrderedSame) {
        [[PBMoreGame sharedMoreGame] setDelegate:nil];
        [[PBMoreGame sharedMoreGame] closeMoreGame];
        [PunchBoxAd closeMoreGame];
    }
}


// PBBannerViewDelegate

- (void)pbBannerViewDidReceiveAd:(PBBannerView*)pbBannerView
{
    [delegate onReceiveAd];
}

- (void)pbBannerView:(PBBannerView*)pbBannerView receiveAdError:(PBRequestError*)requestError
{
    [delegate onFailedToReceiveAd:requestError];
}

- (void)pbBannerViewWillPresentScreen:(PBBannerView*)pbBannerView
{
    adVisible = YES;
    [delegate onPresentScreen];
}

- (void)pbBannerViewDidDismissScreen:(PBBannerView*)pbBannerView
{
    if (adVisible) {
        [delegate onDismissScreen];
        adVisible = NO;
    }
}


// PBInterstitialDelegate

- (void)pbInterstitialDidLoadAd:(PBInterstitial*)pbInterstitial
{
    adVisible = YES;
    [delegate onReceiveAd];
    [[PBInterstitial sharedInterstitial] showInterstitialWithScale:1.0f];
}

- (void)pbInterstitial:(PBInterstitial*)pbInterstitial loadAdFailureWithError:(PBRequestError*)requestError
{
    [delegate onFailedToReceiveAd:requestError];
}

- (void)pbInterstitialDidPresentScreen:(PBInterstitial*)pbInterstitial
{
    [delegate onPresentScreen];
}

- (void)pbInterstitialWillDismissScreen:(PBInterstitial*)pbInterstitial
{
    
}

- (void)pbInterstitialDidDismissScreen:(PBInterstitial*)pbInterstitial
{
    if (adVisible) {
        [delegate onDismissScreen];
        adVisible = NO;
    }
}


// PBMoreGameDelegate

- (void)pbMoreGameDidLoadAd:(PBMoreGame*)pbMoreGame
{
    adVisible = YES;
    [delegate onReceiveAd];
    [[PBMoreGame sharedMoreGame] showMoreGameWithScale:1.0f];
}

- (void)pbMoreGame:(PBMoreGame*)pbMoreGame loadAdFailureWithError:(PBRequestError*)requestError
{
    [delegate onFailedToReceiveAd:requestError];
}

- (void)pbMoreGameDidPresentScreen:(PBMoreGame*)pbMoreGame
{
    [delegate onPresentScreen];
}

- (void)pbMoreGameWillDismissScreen:(PBMoreGame*)pbMoreGame
{
    
}

- (void)pbMoreGameDidDismissScreen:(PBMoreGame*)pbMoreGame;
{
    if (adVisible) {
        [delegate onDismissScreen];
        adVisible = NO;
    }
}

@end
