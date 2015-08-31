package com.quick2dx.sdk;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.util.Log;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import com.punchbox.ads.AdRequest;
import com.punchbox.ads.AdView;
import com.punchbox.ads.InterstitialAd;
import com.punchbox.ads.MoreGameAd;
import com.punchbox.exception.PBException;
import com.punchbox.listener.AdListener;

public class AdHandler implements AdListener {
    private AdListener listener;
    private Cocos2dxActivity context;
    private String appId;
    private String adType;
    private String adId;
    private String adPosition;

    private AdView bannerAd;
    private InterstitialAd interstitialAd;
    private MoreGameAd moreGameAd;

    public AdHandler(AdListener listener_, Cocos2dxActivity context_, String appId_, String adType_, String adId_, String adPosition_) {
        listener = listener_;
        context = context_;
        appId = appId_;
        adType = adType_;
        adId = adId_;
        adPosition = adPosition_;
    }

    public void show() {
        if (adType.compareToIgnoreCase("banner") == 0) {
            showBannerAd(adId, adPosition);
        } else if (adType.compareToIgnoreCase("interstitial") == 0) {
            showInterstitialAd(adId);
        } else if (adType.compareToIgnoreCase("moregame") == 0) {
            showMoreGameAd(adId);
        } else {
            Log.d("PunchBoxAd", "invalid ad type");
        }
    }

    public void remove() {
        removeBannerAd();
        removeInterstitialAd();
        removeMoreGameAd();
    }

    // banner ad

    private void showBannerAd(final String adId, final String adPosition) {
        removeBannerAd();
        if (adId.length() > 0) {
            bannerAd = new AdView(context, adId);
        } else {
            bannerAd = new AdView(context);
        }
        bannerAd.setPublisherId(appId);

        if (adPosition.compareToIgnoreCase("bottom") == 0) {
            RelativeLayout relativeLayout = new RelativeLayout(context);
            RelativeLayout.LayoutParams relativeParams = new RelativeLayout.LayoutParams(LayoutParams.FILL_PARENT,
                    LayoutParams.WRAP_CONTENT);
            relativeParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
            context.addContentView(relativeLayout, new LayoutParams(LayoutParams.MATCH_PARENT,
                    LayoutParams.MATCH_PARENT));
            relativeLayout.addView(bannerAd, relativeParams);
            relativeLayout.setFocusable(false);
        } else {
            LinearLayout bannerAdLayout = new LinearLayout(context);
            bannerAdLayout.setOrientation(LinearLayout.VERTICAL);
            context.addContentView(bannerAdLayout, new LayoutParams(LayoutParams.MATCH_PARENT,
                    LayoutParams.MATCH_PARENT));
            bannerAdLayout.addView(bannerAd);
            bannerAdLayout.setFocusable(false);
        }

        ViewGroup group = (ViewGroup)bannerAd.getParent().getParent();
        group.findViewById(Cocos2dxActivity.GLVIEW_ID).requestFocus();

        bannerAd.setFocusable(false);
        bannerAd.setAdListener(this);
        bannerAd.loadAd(new AdRequest());
    }

    private void removeBannerAd() {
        if (bannerAd != null) {
            bannerAd.setAdListener(null);
            ViewGroup bannerAdParent = (ViewGroup) bannerAd.getParent();
            ViewGroup group = (ViewGroup) bannerAdParent.getParent();
            group.removeView(bannerAdParent);
            bannerAd = null;
            listener.onDismissScreen();
        }
    }

    // interstitial ad

    private void showInterstitialAd(final String adId) {
        removeInterstitialAd();
        interstitialAd = new InterstitialAd(context);
        interstitialAd.setPublisherId(appId);
        interstitialAd.setAdListener(this);
        interstitialAd.loadAd(new AdRequest());
    }

    private void removeInterstitialAd() {
        if (interstitialAd != null) {
            interstitialAd.setAdListener(null);
            interstitialAd.destroy();
            interstitialAd = null;
        }
    }

    // more game ad

    private void showMoreGameAd(final String adId) {
        removeMoreGameAd();
        moreGameAd = new MoreGameAd(context);
        moreGameAd.setPublisherId(appId);
        moreGameAd.setAdListener(this);
        moreGameAd.loadAd(new AdRequest());
    }

    private void removeMoreGameAd() {
        if (moreGameAd != null) {
            moreGameAd.setAdListener(null);
            moreGameAd.destroy();
            moreGameAd = null;
        }
    }

    // listener

    @Override
    public void onReceiveAd() {
        Log.d("PunchBoxAd", "AdHandler.onReceiveAd");
        if (adType.compareToIgnoreCase("moregame") == 0 && moreGameAd != null) {
            try {
                moreGameAd.showFloatView(context, 1.0, adId);
            } catch (PBException e) {
                e.printStackTrace();
            }
        } else if (adType.compareToIgnoreCase("interstitial") == 0 && interstitialAd != null) {
            try {
                interstitialAd.showFloatView(context, 1.0, adId);
            } catch (PBException e) {
                e.printStackTrace();
            }
        }
        listener.onReceiveAd();
    }

    @Override
    public void onDismissScreen() {
        Log.d("PunchBoxAd", "AdHandler.onDismissScreen");
        if (adType.compareToIgnoreCase("banner") != 0) {
            remove();
            listener.onDismissScreen();
        }
    }

    @Override
    public void onFailedToReceiveAd(PBException arg0) {
        Log.d("PunchBoxAd", "AdHandler.onFailedToReceiveAd");
        listener.onFailedToReceiveAd(arg0);
    }

    @Override
    public void onPresentScreen() {
        Log.d("PunchBoxAd", "AdHandler.onPresentScreen");

        if (adType.compareToIgnoreCase("banner") == 0) {
            ViewGroup group = (ViewGroup)bannerAd.getParent().getParent();
            group.findViewById(Cocos2dxActivity.GLVIEW_ID).requestFocus();
        }

        listener.onPresentScreen();
    }

}
