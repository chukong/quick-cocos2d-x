package org.cocos2d_x.samples.umeng_push;

import android.app.Application;

import com.quick2dx.sdk.UmengPushSDK;

public class UmengPushApplication extends Application {

    @Override
    public void onCreate() {
        UmengPushSDK.getInstance().initInApplication(this);

        super.onCreate();
    }
}
