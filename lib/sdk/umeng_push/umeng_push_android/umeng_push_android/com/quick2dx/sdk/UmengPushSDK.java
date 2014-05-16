package com.quick2dx.sdk;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxLuaJavaBridge;

import android.content.Context;
import android.os.AsyncTask;

import com.umeng.message.PushAgent;
import com.umeng.message.UTrack;
import com.umeng.message.UmengMessageHandler;
import com.umeng.message.UmengNotificationClickHandler;
import com.umeng.message.entity.UMessage;
import com.umeng.message.tag.TagManager;

public class UmengPushSDK {

    public static UmengPushSDK getInstance() {
        if (null == gInstance) {
            gInstance = new UmengPushSDK();
        }

        return gInstance;
    }

    /*
     * 必须在application的onCreate中调用此函数
     */
    public void initInApplication(Context context) {
        mPushAgent = PushAgent.getInstance(context);
        mPushAgent.setDebugMode(true);

        /**
         * 该Handler是在IntentService中被调用，故
         * 1. 如果需启动Activity，需添加Intent.FLAG_ACTIVITY_NEW_TASK
         * 2. IntentService里的onHandleIntent方法是并不处于主线程中，因此，如果需调用到主线程，需如下所示;
         *        或者可以直接启动Service
         * */
        UmengMessageHandler messageHandler = new UmengMessageHandler(){
            @Override
            public void dealWithCustomMessage(final Context context, final UMessage msg) {
                UTrack.getInstance(context).trackMsgClick(msg);

                /*
                 * 这是自定义消息，不会在notification中显示
                 * 如果需要直接在原生代码中处理不传到lua中，可以在这里修改
                 */
                StringBuilder sb = new StringBuilder("customMsg|");
                sb.append(msg.custom);
                UmengPushSDK.getInstance().onReceiverInfo(sb.toString());
            }
        };
        mPushAgent.setMessageHandler(messageHandler);

        /**
         * 该Handler是在BroadcastReceiver中被调用，故
         * 如果需启动Activity，需添加Intent.FLAG_ACTIVITY_NEW_TASK
         * */
        UmengNotificationClickHandler notificationClickHandler = new UmengNotificationClickHandler(){
            @Override
            public void dealWithCustomAction(Context context, UMessage msg) {
                /*
                 * 这是在notification显示的自定义消息
                 * 如果需要直接在原生代码中处理不传到lua中，可以在这里修改
                 */
                StringBuilder sb = new StringBuilder("notifyMsg|");
                sb.append(msg.custom);
                UmengPushSDK.getInstance().onReceiverInfo(sb.toString());
            }
        };
        mPushAgent.setNotificationClickHandler(notificationClickHandler);
    }

    /*
     * 必须在应用的主activity中onCreate调用此函数
     */
    public void init(Cocos2dxActivity activity) {
        mContext = activity;

        mPushAgent = PushAgent.getInstance(mContext);
        mPushAgent.onAppStart();

        mPushAgent.enable();

    }

    public static void startPush() {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                if (!UmengPushSDK.getInstance().mPushAgent.isEnabled()) {
                    UmengPushSDK.getInstance().mPushAgent.enable();
                }

                UmengPushSDK.getInstance().onReceiverInfo("startPush|0");
            }
        });
    }

    public static void stopPush() {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                if (UmengPushSDK.getInstance().mPushAgent.isEnabled()) {
                    UmengPushSDK.getInstance().mPushAgent.disable();
                }

                UmengPushSDK.getInstance().onReceiverInfo("stopPush|0");
            }
        });
    }

    public static void setTags(final String tags) {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                if (UmengPushSDK.getInstance().mPushAgent.isRegistered()) {
                    new AsyncTask<Void, Void, Boolean>() {
                        @Override
                        protected Boolean doInBackground(Void... params) {
                            try {
                                PushAgent pushAgent = UmengPushSDK.getInstance().mPushAgent;
                                TagManager.Result result = pushAgent.getTagManager().add(str2Arr(tags));
                                if ("ok".equalsIgnoreCase(result.status)) {
                                    return true;
                                }
                            } catch (Exception e) {
                                // network error, try it later.
                                e.printStackTrace();
                            }
                            return false;
                        }

                        @Override
                        protected void onPostExecute(Boolean result) {
                            StringBuilder sb = new StringBuilder("setTags");
                            if (Boolean.TRUE.equals(result)) {
                                sb.append("|0");
                            } else {
                                sb.append("|1");
                            }
                            UmengPushSDK.getInstance().onReceiverInfo(sb.toString());
                        }

                    }.execute(null, null, null);
                }
            }
        });
    }

    public static void delTags(final String tags) {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                if (UmengPushSDK.getInstance().mPushAgent.isRegistered()) {
                    new AsyncTask<Void, Void, Boolean>() {
                        @Override
                        protected Boolean doInBackground(Void... params) {
                            try {
                                PushAgent pushAgent = UmengPushSDK.getInstance().mPushAgent;
                                TagManager.Result result = pushAgent.getTagManager().delete(str2Arr(tags));
                                if ("ok".equalsIgnoreCase(result.status)) {
                                    return true;
                                }
                            } catch (Exception e) {
                                // network error, try it later.
                                e.printStackTrace();
                            }
                            return false;
                        }

                        @Override
                        protected void onPostExecute(Boolean result) {
                            StringBuilder sb = new StringBuilder("delTags");
                            if (Boolean.TRUE.equals(result)) {
                                sb.append("|0");
                            } else {
                                sb.append("|1");
                            }
                            UmengPushSDK.getInstance().onReceiverInfo(sb.toString());
                        }

                    }.execute(null, null, null);
                }
            }
        });
    }

    public static void setAlias(final String alias, final String aliasType) {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                if (UmengPushSDK.getInstance().mPushAgent.isRegistered()) {
                    new AsyncTask<String, Void, Boolean>() {
                        @Override
                        protected Boolean doInBackground(String... params) {
                            try {
                                return UmengPushSDK.getInstance().mPushAgent.addAlias(params[0], params[1]);
                            } catch (Exception e) {
                                // network error, try it later.
                                e.printStackTrace();
                            }
                            return false;
                        }

                        @Override
                        protected void onPostExecute(Boolean result) {
                            StringBuilder sb = new StringBuilder("setAlias");
                            if (Boolean.TRUE.equals(result)) {
                                sb.append("|0");
                            } else {
                                sb.append("|1");
                            }
                            UmengPushSDK.getInstance().onReceiverInfo(sb.toString());
                        }

                    }.execute(alias, aliasType);
                }
            }
        });
    }

    public static void delAlias(final String alias, final String aliasType) {
        mContext.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                if (UmengPushSDK.getInstance().mPushAgent.isRegistered()) {
                    new AsyncTask<String, Void, Boolean>() {
                        @Override
                        protected Boolean doInBackground(String... params) {
                            try {
                                return UmengPushSDK.getInstance().mPushAgent.removeAlias(params[0], params[1]);
                            } catch (Exception e) {
                                // network error, try it later.
                                e.printStackTrace();
                            }
                            return false;
                        }

                        @Override
                        protected void onPostExecute(Boolean result) {
                            StringBuilder sb = new StringBuilder("delAlias");
                            if (Boolean.TRUE.equals(result)) {
                                sb.append("|0");
                            } else {
                                sb.append("|1");
                            }
                            UmengPushSDK.getInstance().onReceiverInfo(sb.toString());
                        }

                    }.execute(alias, aliasType);
                }
            }
        });
    }

    public static String[] str2Arr(String str) {
        String[] arrString = str.split(",");

        return arrString;
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

    private static UmengPushSDK gInstance;
    private static Cocos2dxActivity mContext;
    private static int mListener;
    private PushAgent mPushAgent;
}
