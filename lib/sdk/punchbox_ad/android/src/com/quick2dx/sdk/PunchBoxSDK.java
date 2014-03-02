
package com.quick2dx.sdk;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxLuaJavaBridge;

import com.punchbox.ads.InterstitialAd;
import com.punchbox.exception.PBException;
import com.punchbox.listener.AdListener;

import android.util.Log;

public class PunchBoxSDK implements AdListener
{
	private static PunchBoxSDK instance;
    private static Cocos2dxActivity context;
    private static int listener;
    private static AdHandler adHandler;
    
    // public interface
    
    public static PunchBoxSDK getInstance() {
    	if (instance == null) {
    		instance = new PunchBoxSDK();
    	}
    	return instance;
    }
    
    public static void start() {
        context = (Cocos2dxActivity)Cocos2dxActivity.getContext();
        Log.d("PunchBoxAd", "start()");
    }
    
    public static void stop() {
    	remove();
    	removeScriptListener();
    }

    public static void show(final String adType, final String adId, final String adPosition) {
    	if (adHandler != null) {
    		Log.d("PunchBoxAd", "One Ad already exists");
    		return;
    	}
    	
    	context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				adHandler = new AdHandler(getInstance(), context, adType, adId, adPosition);
				adHandler.show();
			}
		});
    }
    
    public static void remove() {
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (adHandler != null) {
					adHandler.remove();
					adHandler = null;
				}
			}
		});
    }
    
    public static void addScriptListener(final int listener_) {
        removeScriptListener();
        listener = listener_;
    }

    public static void removeScriptListener() {
        if (listener != 0) {
            Cocos2dxLuaJavaBridge.releaseLuaFunction(listener);
            listener = 0;
        }
    }
    
    // listener
    
	@Override
	public void onReceiveAd() {
		Log.d("PunchBoxAd", "onReceiveAd");
	}

	@Override
	public void onDismissScreen() {
		Log.d("PunchBoxAd", "onDismissScreen");
		remove();
	}

	@Override
	public void onFailedToReceiveAd(PBException arg0) {
		Log.d("PunchBoxAd", "onFailedToReceiveAd");
	}

	@Override
	public void onPresentScreen() {
		Log.d("PunchBoxAd", "onPresentScreen");
	}
}
