package com.quick2dx.sdk;

import java.util.List;

import android.content.Context;

import com.coco.CCPushRecevier;

public class CocoPushReceiver extends CCPushRecevier {
    @Override
    public void onSetTags(Context context, int retCode, List<String> sucessTags, List<String> failTags) {
        String info = "setTags" + "|" + retCode + "|" + strlist2str(sucessTags) + "|" + strlist2str(failTags);
        notifyCocoPushSDK(info);
    }

    @Override
    public void onDelTags(Context context, int retCode, List<String> sucessTags, List<String> failTags) {
        String info = "delTags" + "|" + retCode + "|" + strlist2str(sucessTags) + "|" + strlist2str(failTags);
        notifyCocoPushSDK(info);
    }

    @Override
    public void onStartPush(Context context, int retCode) {
        String info = "startPush" + "|" + retCode;
        notifyCocoPushSDK(info);
    }

    @Override
    public void onStopPush(Context context, int retCode) {
        String info = "stopPush" + "|" + retCode;
        notifyCocoPushSDK(info);
    }

    @Override
    public void onSetAlias(Context context, int retCode, String alias) {
        String info = "setAlias" + "|" + retCode;
        notifyCocoPushSDK(info);
    }

    @Override
    public void onDelAlias(Context context, int retCode) {
        String info = "delAlias" + "|" + retCode;
        notifyCocoPushSDK(info);
    }

    public String strlist2str(List<String> listStr) {
        if (null == listStr
                || 0 == listStr.size()) {
            return "";
        }

        StringBuffer sb = new StringBuffer();
        for (String str : listStr) {
            sb.append(str);
            sb.append(',');
        }
        int length = sb.length();
        if (length < 2) {
            return "";
        }
        return sb.substring(0, length - 1);
    }

    public void notifyCocoPushSDK(String str) {
        CocoPushSDK.getInstance().onReceiverInfo(str);
    }
}
