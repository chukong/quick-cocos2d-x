 (function(){
/**
 * edit by peter 重构QQApi
 */
  var QQApi = {
    isQQSupportApiForWallet : function() {
  
        var urlStr="mqqapiwallet://";
        var json=JSON.stringify({url:urlStr});
        return nativeApi.appCanOpenURL(json);
    },
  
    isQQAppSatisfy:function(urlStr){
        var json=JSON.stringify({url:urlStr});
        return nativeApi.appCanOpenURL(json);
    },
  
    getQQScheme:function(){
        return nativeApi.getQQScheme();
    },
  
    isQQSupportApiGeneralPastboard:function(){
  
        var urlStr="mqqopensdkapiV2://";
        var json=JSON.stringify({url:urlStr});
        return nativeApi.appCanOpenURL(json);
    },
  
    handleWPAMessageShare:function(urlStr){
  
        
        var result= nativeApi.openURL(urlStr);
        if(result!==0)
        {
            urlStr="http://itunes.apple.com/cn/app/id444934666";
            nativeApi.openURL(urlStr);
  
        }
        return true;
    },
  
    isRegistScheme:function(urlStr)
    {
        return nativeApi.isRegistScheme(urlStr);
    },
  
  
    isLargeDataLengthLegal:function(type)
    {
        return nativeApi.isLargeDataLengthLegal(type);
    },
  
    checkQQApiURLMessage:function(){
        return nativeApi.checkQQApiURLMessage();
    },
  
    resendUrlObjectSyncShare:function(){
        return nativeApi.resendUrlObjectSyncShare();
    },
  
    getAppName:function(){
        return nativeApi.getAppName();
    },
  
    setURLObjectPasteBoardDatas:function(){
        return nativeApi.setURLObjectPasteBoardDatas();
    },
  
    setImageObjectPasteBoardDatas:function(){
        return nativeApi.setImageObjectPasteBoardDatas();
    },
  
    setExtendObjectPasteBoardDatas:function(){
        return nativeApi.setExtendObjectPasteBoardDatas();
    },
  
    setCommonObjectPasteBoardDatas:function(){
        return nativeApi.setCommonObjectPasteBoardDatas();
    }
  
  };
  window.local.QQApi = window.QQApi = QQApi;
  })();﻿(function(){
/**
 * 获取本地的appid，accessToken，openId，expireIn等信息
 * 
 */
var QQToken = {
	getAppId : function() {
	    return tencent.oauth.appid;
	},
	getOpenId: function () {
	    return tencent.oauth.openId;
	},
	getAccessToken: function () {
	    return tencent.oauth.accessToken;
	},
	getExpiresIn: function () {
	    return tencent.oauth.expirationDate;
	}
};
window.local.QQToken = window.QQToken = QQToken;
})();var appUtils = {
    openNativeWebView: function(url, title) {
        return oauth.openNativeWebView(url, title);  
    },
    
    nativeWebViewCallback: function(url) {
        log.d('nativeWebviewCallback', url);
        if (url.indexOf('tencent://cancel') !== -1) {
            oauth.closeNativeWebView();
           return false;
        }
        
        if (url.indexOf('auth://browser') !== -1) {
            return false;
        }
        return true;
    },
    
    setPermissions: function (a) {
        JSTencentOauth.permissions = a
    },
    getQzoneVersion: function () {
        
        Order.Qzoneversion=0;
        var systemOS=openapi.getSystemOSVersion();
        //1
        var a = JSON.stringify({
            kOPEN_ZONE_TEST: ios_constants.kOPEN_ZONE_TEST
        });
        if(openApi.isAppVersion(a)==='true') {
            Order.Qzoneversion = ios_constants.kQZONE_VERSION_3_4;
        }
        //2
        
        var a = JSON.stringify({
            kOPEN_ZONE_3_6_TEST: ios_constants.kOPEN_ZONE_3_6_TEST
        });
        if(openApi.isAppVersion(a)==='true') {
            Order.Qzoneversion = ios_constants.kQZONE_VERSION_3_6;
        }
        
        //3
        
        var a = JSON.stringify({
            kOPEN_ZONE_4_0_TEST: ios_constants.kOPEN_ZONE_4_0_TEST
        });
        if(openApi.isAppVersion(a)==='true') {
            Order.Qzoneversion = ios_constants.kQZONE_VERSION_4_0;
        }
        
        //4
        var a = JSON.stringify({
            kOPEN_ZONE_5_0_TEST: ios_constants.kOPEN_ZONE_5_0_TEST
        });
        if(openApi.isAppVersion(a)==='true') {
            Order.Qzoneversion = ios_constants.kQZONE_VERSION_5_0;
        }
        
        
        if(systemOS>=7&&Order.Qzoneversion<=3)
        {
            Order.Qzoneversion=0;
        }
        
        var res = Order.Qzoneversion;
        return res;
    },
    getQQVersion: function () {
        
        Order.QQversion=0;
        var systemOS=openapi.getSystemOSVersion();
        
        //0
        var a = JSON.stringify({
            kOLD_QQ_TEST:ios_constants.kOLD_QQ_TEST
        });
        if(openApi.isAppVersion(a)==='true') {
            Order.QQversion = ios_constants.kQQ_VERSION_3_0;
        }
        
        //1
        var a = JSON.stringify({
            kOPEN_QQ_TEST: ios_constants.kOPEN_QQ_TEST
        });
        if(openApi.isAppVersion(a)==='true') {
            Order.QQversion = ios_constants.kQQ_VERSION_4_0;
        }
       
        //2
        var a = JSON.stringify({
            kOPEN_QQ_4_2_TEST:ios_constants.kOPEN_QQ_4_2_TEST
        });
        if(openApi.isAppVersion(a)==='true') {
            Order.QQversion = ios_constants.kQQ_VERSION_4_2;
        }
        
        //3
        var a = JSON.stringify({
                               kOPEN_QQ_5_0_TEST:ios_constants.kOPEN_QQ_5_0_TEST
                               });
        if(openApi.isAppVersion(a)==='true') {
            Order.QQversion = ios_constants.kQQ_VERSION_5_0;
        }
        
        if(systemOS>=7&&Order.QQversion<=1)
        {
            Order.QQversion=0;
        }
        var res = Order.QQversion;
        return res;
    },
    compareVersion: function (a, b) {
        return a >= b ? 1 : a == b ? 0 : -1
    },
    getAppId: function () {
        return tencent.oauth.appid
    },
    getAppName: function() {
        return QQApi.getAppName();
    }
};var config_version = {
    QzoneLeastVersion: 2,
    QQLeastVersion: 1
};var httpUtils = {
    httpPost: function (a, b) {
        try {
            var c = JSON.stringify({
                url: a,
                accesstoken: tencent.oauth.accessToken,
                openid: tencent.oauth.openId,
                appid: tencent.oauth.appid,
                callback: b,
                key: b
            });
            oauth.httpPost(c);
            return !0
        } catch (d) {
            return d.message
        }
    },

    httpGet: function (a, b) {
        try {
            var c = JSON.stringify({
                url: a,
                accesstoken: tencent.oauth.accessToken,
                openid: tencent.oauth.openId,
                appid: tencent.oauth.appid,
                callback: b,
                key: b
            });
            oauth.httpGet(c);
            return !0
        } catch (d) {
            return d.message
        }
    }
};var jump = {
    jump: function (dic) {
        return "qq" == jumpParams.source ? jump.startQQ(dic) : "qzone" == jumpParams.source ? jump.startQzone(dic): !1
        
    },
    
    startApp:function(myurl,dic,appurl,device){
        var appname=openapi.getAppName();
        if(JSTencentOauth.loacl_appid===null||appname===null)
        {
            return false;
        }
        var pbName=openapi.saveDictionary(dic);
        var json=JSON.stringify({url:myurl});
        var result=openapi.isSupportPastboard(json);
        if(result==='true')
        {
            pbName=openapi.saveDictionaryByGeneralPastboardWithSchema(dic);
            var url;
            if(device=="QQ")
            {
                url=appurl+pbName+"?generalpastboard=1";
            }
            else if(device="Qzone")
            {
                url=appurl+pbName+"/"+0+"?generalpastboard=1";
            }
            var json=JSON.stringify({url:url});
            result=openapi.openURL(json);
            return true;
            
        }
        else
        {
            pbName=openapi.saveDictionary(dic);
            if(device=="QQ")
            {
                url=appurl+pbName+"?generalpastboard=0";
            }
            else if(device=="Qzone")
            {
                url=appurl+pbName+"/"+0+"?generalpastboard=0";
            }
            var json=JSON.stringify({url:url});
            result=openapi.openURL(json);
            return true;
        }
        return true;
    },
    
    startQQ:function(dic){
        var QQURl="mqqopensdkapiV2://";
        var url=ios_constants.kOPEN_QQ_API_SCHEMA+"://"+ios_constants.kOPEN_QQ_HOST+"/"+loacl_appSchema+"/";
        return jump.startApp(QQURl,dic,url,"QQ");
    },
    
    startQzone:function(dic){
      
        var QzoneURl="mqzoneopensdkapiV2://";
       
        var url=ios_constants.kOPEN_QZONE_API_SCHEMA+"://"+ios_constants.kOPEN_QZONE_HOST+"/"+loacl_appSchema+"/";
        return jump.startApp(QzoneURl,dic,url,"Qzone");
    },
    getJumpParams: function (a) {
        var jsversion=openapi.getJSVersion();
        var Bundleid=openapi.getBundleIdentifier();
        return JSON.stringify({
            appScheme: loacl_appSchema,
            permission: JSTencentOauth.permissions,
            appid: JSTencentOauth.loacl_appid,
            QQApiScheme: ios_constants.kOPEN_QQ_API_SCHEMA,
            QQHost: ios_constants.kOPEN_QQ_HOST,
            QZoneApiScheme: ios_constants.kOPEN_QZONE_API_SCHEMA,
            QZoneHost: ios_constants.kOPEN_QZONE_HOST,
            ResponseType: ios_constants.responseType,
            source: jumpParams.source,
            jsVersion:jsversion,
            bundleId:Bundleid,
        })
    },
    setSchema: function (a) {
        jumpParams.action = JSON.stringify({
            appSchema: loacl_appSchema
        })
    },
    startBrowser: function () {
        return oauth.authorizeInWebviewKitWithParams(JSON.stringify(tencent.oauth.isAdd ? {
            appid: JSTencentOauth.loacl_appid,
            appScheme: loacl_appSchema,
            redirecURI: JSTencentOauth.loacl_redirectURI,
            permission: JSTencentOauth.permissions,
            isAdd: tencent.constants.IS_ADD,
            accessToken: tencent.oauth.accessToken
        } : {
            appid: JSTencentOauth.loacl_appid,
            appScheme: loacl_appSchema,
            redirecURI: JSTencentOauth.loacl_redirectURI,
            permission: JSTencentOauth.permissions
        }))
    }
};var jumpParams = {
    packageName: null,
    className: null,
    action: null,
    scope: null,
    source: null
};var listener = {
    onComplete: function (a, b) { }
};(function(){

    //ios 定向分享常量
    var qqApiConstants={
        qqShareScheme  : null,
        //base message
        kQQINSTALLSCHEME        :"mqq://",
        kQQSUPPORTSCHEME        :"mqqapi://",
        kQQWALLETSCHEME         :"mqqapiwallet://",
        kQQBrowserScheme        :"mttbrowser://",
        kNewQQBrowserScheme     :"mqqbrowser://"
    };
/**
 * 手Q定向分享
 */
var qqShareUtils = {

    /**
     *手Q定向分享，平台是否支持，比如手Q是否安装等
     *@method isPlatformSupport
     *edit by peter must change
     */
    isPlatformSupport:function(){
        log.d('isPlatformSupport',qqApiConstants.kQQINSTALLSCHEME);

        //手Q没装
        if(QQApi.isQQAppSatisfy(qqApiConstants.kQQINSTALLSCHEME) === 'NO'){
            return 1;//RESULTCODE_QQNOTINSTALLED
        }
        //手Q版本不支持
        if(QQApi.isQQAppSatisfy(qqApiConstants.kQQSUPPORTSCHEME) === 'NO'){
            return 2;//RESULTCODE_QQNOTSUPPORTAPI
        }
        //没注册
        var temp = QQApi.getQQScheme();
        if(temp && temp.length)
            return 10;//JSAPI.Constants.RESULTCODE_LEGAL
        else
            return 6;//RESULTCODE_APPNOTREGISTED
    },

    /**
     *手Q定向分享，主要为了兼容android，把部分初始化内容放到这里.
     *@method initMsg
     */
    initMsg:function(MessageJson)
    {
        log.d('qqShareUtils','initMessageJson');
        return MessageJson;
    },

    /**
     *手Q定向分享，拉起手Q进行分享
     *@method callNativeQQShare
     * edit by peter shareWithQQ changed to js_canOpenURL
     */    
    callNativeQQShare:function(url){
        if(url && url.length > 1){
            var temp = nativeApi.openURL(url);
            return temp;
        }
        log.d("param error: illegal object param");
        return 5;
    },

    /**
     *手Q定向分享，获取设备和系统的信息
     *@method getSDKInfo
     */    
    getSDKInfo:function() {
        // body...
        var ret =  nativeApi.getSDKInfo();
        return eval('('+ret+')');
    },

    /**
     * 拉起H5 QQ进行分享
     */
    _openH5QQToShare:function(localhost)
    {
        var result=qqShareUtils.isNewQQBrowserInstall();
        if(result==='YES')
        {
            var url='mqqbrowser://url='+localhost;
            nativeApi.openURL(url);
            return true;
        }
 
        var resultold=qqShareUtils.isOldQQBrowserInstall();
        var systemOS=openapi.getSystemOSVersion();
        if(result==='YES'&&systemOS<=6)
        {
            var url='mqqbrowser://url='+localhost;
            nativeApi.openURL(url);
            return true;
        }
        nativeApi.openH5QQ(localhost);
    },
 
    /**
     * 判断新旧QQ浏览器
     */
    isNewQQBrowserInstall:function()
    {
        var urlStr="mqqbrowser://";
        var json=JSON.stringify({url:urlStr});
        return nativeApi.appCanOpenURL(json);
    },
 
    isOldQQBrowserInstall:function()
    {
        var urlStr="mttbrowser://";
        var json=JSON.stringify({url:urlStr});
        return nativeApi.appCanOpenURL(json);
    }

};
    window.qqShareUtils = qqShareUtils;
})();
var requestListener = {
    dealResponse: function (a, b) { }
};