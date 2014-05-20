package com.quick2dx.sdk;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.umeng.fb.FeedbackAgent;

public class UmengFeedbackSDK {

    public static void init(Cocos2dxActivity context) {
        mContext = context;
        mFeedbackAgent = new FeedbackAgent(mContext);
        mFeedbackAgent.sync();
    }

    public static void showFeedback() {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                mFeedbackAgent.startFeedbackActivity();
            }
        });
    }

    private static Cocos2dxActivity mContext;
    private static FeedbackAgent mFeedbackAgent;
}
