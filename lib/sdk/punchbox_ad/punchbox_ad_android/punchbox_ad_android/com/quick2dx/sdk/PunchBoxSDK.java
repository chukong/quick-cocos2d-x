package com.quick2dx.sdk;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxLuaJavaBridge;

import android.util.Log;

import com.punchbox.exception.PBException;
import com.punchbox.listener.AdListener;

public class PunchBoxSDK implements AdListener {
    private static PunchBoxSDK instance;
    private static Cocos2dxActivity context;
    private static String appId;
    private static int listener;
    private static AdHandler adHandler;

    private PunchBoxSDK() {
    }

    public static PunchBoxSDK getInstance() {
        if (instance == null) {
            instance = new PunchBoxSDK();
        }
        return instance;
    }

    // public interface

    public static void start(String appId_) {
        context = (Cocos2dxActivity) Cocos2dxActivity.getContext();
        appId = appId_;
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
                adHandler = new AdHandler(getInstance(), context, appId, adType, adId, adPosition);
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
            context.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    Cocos2dxLuaJavaBridge.releaseLuaFunction(listener);
                    listener = 0;
                }
            });
        }
    }

    // AdHandler callback

    @Override
    public void onReceiveAd() {
        Log.d("PunchBoxAd", "onReceiveAd");
        if (listener != 0) {
            context.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    Cocos2dxLuaJavaBridge.callLuaFunctionWithString(listener, "received");
                }
            });
        }
    }

    @Override
    public void onDismissScreen() {
        Log.d("PunchBoxAd", "onDismissScreen");
        remove();
        if (listener != 0) {
            context.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    Cocos2dxLuaJavaBridge.callLuaFunctionWithString(listener, "dismiss");
                }
            });
        }
    }

    @Override
    public void onFailedToReceiveAd(PBException arg0) {
        Log.d("PunchBoxAd", "onFailedToReceiveAd");
        remove();
        final int errcode = arg0.getErrorCode();
        if (listener != 0) {
            context.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    Cocos2dxLuaJavaBridge.callLuaFunctionWithString(listener, "failed," + Integer.toString(errcode));
                }
            });
        }
    }

    @Override
    public void onPresentScreen() {
        Log.d("PunchBoxAd", "onPresentScreen");
        if (listener != 0) {
            context.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    Cocos2dxLuaJavaBridge.callLuaFunctionWithString(listener, "present");
                }
            });
        }
    }
}
