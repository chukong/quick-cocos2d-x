package com.quick2dx.sdk;

import java.util.ArrayList;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxLuaJavaBridge;

import com.coco.CCPush;

public class CocoPushSDK {

    public static CocoPushSDK getInstance() {
        if (null == gInstance) {
            gInstance = new CocoPushSDK();
        }
        return gInstance;
    }

    public static void init(Cocos2dxActivity activity) {
        getInstance();

        CCPush.init(activity);
        mContext = activity;
    }

    public static void startPush() {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                CCPush.startPush(mContext);
            }
        });
    }

    public static void stopPush() {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                CCPush.stopPush(mContext);
            }
        });
    }

    public static void setTags(final String tags) {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                CCPush.setTags(mContext, str2list(tags));
            }
        });
    }

    public static void delTags(final String tags) {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                CCPush.delTags(mContext, str2list(tags));
            }
        });
    }

    public static void setAlias(final String alias) {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                CCPush.setAlias(mContext, alias);
            }
        });
    }

    public static void delAlias() {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                CCPush.delAlias(mContext);
            }
        });
    }

    public static List<String> str2list(String str) {
        String[] arrString = str.split(",");
        List<String> listString = new ArrayList<String>(arrString.length);
        for (int i = 0; i < arrString.length; i++) {
            listString.add(arrString[i]);
        }

        return listString;
    }

    public static void addScriptListener(final int listener_) {
        removeScriptListener();
        mListener = listener_;
    }

    public static void removeScriptListener() {
        if (mListener != 0) {
            mContext.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    Cocos2dxLuaJavaBridge.releaseLuaFunction(mListener);
                    mListener = 0;
                }
            });
        }
    }

    //on CocoPushReceiver callback
    public void onReceiverInfo(final String tags) {
        if (0 == mListener) {
            return ;
        }

        mContext.runOnGLThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxLuaJavaBridge.callLuaFunctionWithString(mListener, tags);
            }
        });
    }

    private static CocoPushSDK gInstance;
    private static Cocos2dxActivity mContext;
    private static int mListener;
}
