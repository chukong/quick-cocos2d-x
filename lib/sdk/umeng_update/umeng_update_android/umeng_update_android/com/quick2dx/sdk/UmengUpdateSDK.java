package com.quick2dx.sdk;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxLuaJavaBridge;

import com.umeng.update.UmengDialogButtonListener;
import com.umeng.update.UmengDownloadListener;
import com.umeng.update.UmengUpdateAgent;
import com.umeng.update.UmengUpdateListener;
import com.umeng.update.UpdateResponse;
import com.umeng.update.UpdateStatus;

public class UmengUpdateSDK {

    static void init() {
        mContext = (Cocos2dxActivity)Cocos2dxActivity.getContext();

        //监听检测更新的结果
        UmengUpdateAgent.setUpdateListener(new UmengUpdateListener() {
            @Override
            public void onUpdateReturned(int updateStatus,UpdateResponse updateInfo) {
                switch (updateStatus) {
                    case UpdateStatus.Yes: // has update
                        UmengUpdateAgent.showUpdateDialog(mContext, updateInfo);
                        callListener("update|haveUpdate");
                        break;
                    case UpdateStatus.No: // has no update
                        callListener("update|noUpdate");
                        break;
                    case UpdateStatus.NoneWifi: // none wifi
                        callListener("update|noWifi");
                        break;
                    case UpdateStatus.Timeout: // time out
                        callListener("update|timeout");
                        break;
                }
            }
        });

        //监听对话框按键操作
        UmengUpdateAgent.setDialogListener(new UmengDialogButtonListener() {

            @Override
            public void onClick(int status) {
                switch (status) {
                    case UpdateStatus.Update:
                        callListener("update|userUpdate");
                        break;
                    case UpdateStatus.Ignore:
                        callListener("update|userIgnore");
                        break;
                    case UpdateStatus.NotNow:
                        callListener("update|userLater");
                        break;
                }
            }
        });

        //监听下载进度
        UmengUpdateAgent.setDownloadListener(new UmengDownloadListener(){

            @Override
            public void OnDownloadStart() {
                callListener("download|start");
            }

            @Override
            public void OnDownloadUpdate(int progress) {
                callListener("download|downloading|" + progress);
            }

            @Override
            public void OnDownloadEnd(int result, String file) {
                String strReponed = "download|end|";
                switch (result) {
                    case UpdateStatus.DOWNLOAD_COMPLETE_FAIL:
                        strReponed += "fail";
                        break;
                    case UpdateStatus.DOWNLOAD_COMPLETE_SUCCESS:
                        strReponed += "sucess|";
                        strReponed += file;
                        break;
                    case UpdateStatus.DOWNLOAD_NEED_RESTART:
                        // 增量更新请求全包更新(请勿处理这种情况)
                        strReponed += "needRestart";
                        break;
                }

                callListener(strReponed);
            }
        });
    }

    static void update() {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                UmengUpdateAgent.update(mContext);
            }

        });

    }

    static void forceUpdate() {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                UmengUpdateAgent.forceUpdate(mContext);
            }

        });
    }

    static void silentUpdate() {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                UmengUpdateAgent.silentUpdate(mContext);
            }

        });
    }

    public static void addScriptListener(final int listener_) {
        removeScriptListener();
        listener = listener_;
    }

    public static void removeScriptListener() {
        if (listener != 0) {
            mContext.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    Cocos2dxLuaJavaBridge.releaseLuaFunction(listener);
                    listener = 0;
                }
            });
        }
    }

    public static void callListener(final String strResp) {
        if (0 == listener) {
            return ;
        }
        mContext.runOnGLThread(new Runnable() {
            @Override
            public void run() {
                Cocos2dxLuaJavaBridge.callLuaFunctionWithString(listener, strResp);
            }
        });
    }

    private static Cocos2dxActivity mContext;
    private static int listener;
}
