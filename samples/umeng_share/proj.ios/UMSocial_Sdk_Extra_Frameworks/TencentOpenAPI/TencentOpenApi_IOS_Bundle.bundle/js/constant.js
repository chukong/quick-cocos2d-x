(function(){
var JSTencentOauth = {
    loacl_appid: null,
    loacl_redirectURI: null,
    loacl_userGetUserInfo: false,
    permissions: null
};
window.constant.JSTencentOauth = window.JSTencentOauth = JSTencentOauth;
})();(function () {
    /**
     * Android平台相关的常量
     * @class  android_contants
     * @type {{TAG: string, SDK_VERSION: number, WEBVIEW_LOGIN: number, CODE_RESULT_MIN: number, CODE_RESULT_MAX: number, ACTIVITY_OK: number, ACTIVITY_CANCEL: number, KEY_ERROR_CODE: string, KEY_ERROR_MSG: string, KEY_ERROR_DETAIL: string, KEY_RESPONSE: string, KEY_ACTION: string, KEY_PARAMS: string, PARAM_SCOPE: string, PARAM_CLIENT_ID: string, KEY_APP_NAME: string, PACKAGE_QQ: string, PACKAGE_QZONE: string, PACKAGE_SAMPLE: string, UI_ACTIVITY: number, UI_DIALOG: number, ACTIVITY_AGENT: string, ACTIVITY_CHALLENGE: string, ACTIVITY_ENCRY_TOKEN: string, ACTIVITY_BRAG: string, ACTIVITY_ASK_GIFT: string, ACTIVITY_INVITE: string, ACTIVITY_STORY: string, ACTIVITY_IMAGE: string, ACTION_LOGIN: string, ACTION_INVITE: string, ACTION_STORY: string, ACTION_PAY: string, ACTION_CHALLENGE: string, ACTION_BRAG: string, ACTION_ASK: string, ACTION_GIFT: string, ACTION_SETAVATAR: string, ACTION_CHECK_TOKEN: string, SHAREQQ_SCHEME_URL: string, SHAREQQ_H5_URL: string, PARAM_AVATAR_URI: string, PARAM_APP_ID: string, PARAM_ACCESS_TOKEN: string, PARAM_EXPIRES_IN: string, PARAM_OPEN_ID: string, PARAM_KEY_STR: string, EXCEPTION_IO: string, EXCEPTION_MALFORMEDURL: string, EXCEPTION_JSON: string, EXCEPTION_CONNECTTIMEOUT: string, EXCEPTION_SOCKETTIMEOUT: null}}
     */
    var android_contants = {
        TAG: "localjs",
        //sdk版本
        SDK_VERSION: 2.0,
        //通过webview登陆的flag
        WEBVIEW_LOGIN: 3,
        //requestCode相关
        CODE_RESULT_MIN: 5656,
        CODE_RESULT_MAX: 6656,

        //resultCode相关
        ACTIVITY_OK: -1,
        ACTIVITY_CANCEL: 0,

        //intent key相关
        KEY_ERROR_CODE: "key_error_code",
        KEY_ERROR_MSG: "key_error_msg",
        KEY_ERROR_DETAIL: "key_error_detail",
        KEY_RESPONSE: "key_response",
        KEY_ACTION: "key_action",
        KEY_PARAMS: "key_params",

        //param key 相关
        PARAM_SCOPE: "scope",
        PARAM_CLIENT_ID: "client_id",
        KEY_APP_NAME: "oauth_app_name",

        //package相关
        PACKAGE_QQ: "com.tencent.mobileqq",
        PACKAGE_QZONE: "com.qzone",
        PACKAGE_SAMPLE: "com.tencent.sample",
        //UI相关
        UI_ACTIVITY: 1,
        UI_DIALOG: 2,

        //QQconstant
        ACTIVITY_AGENT: "com.tencent.open.agent.AgentActivity",
        ACTIVITY_CHALLENGE: "com.tencent.open.agent.ChallengeActivity",
        ACTIVITY_ENCRY_TOKEN: "com.tencent.open.agent.EncryTokenActivity",
        ACTIVITY_BRAG: "com.tencent.open.agent.BragActivity",
        ACTIVITY_ASK_GIFT: "com.tencent.open.agent.RequestFreegiftActivity",
        ACTIVITY_INVITE: "com.tencent.open.agent.AppInvitationActivity",
        ACTIVITY_STORY: "com.tencent.open.agent.SendStoryActivity",
        //设置头像相关
        ACTIVITY_IMAGE: "com.tencent.plus.ImageActivity",
        //action相关：
        ACTION_LOGIN: "action_login",
        ACTION_INVITE: "action_invite",
        ACTION_STORY: "action_story",
        ACTION_PAY: "action_pay",
        ACTION_CHALLENGE: "action_challenge",
        ACTION_BRAG: "action_brag",
        ACTION_ASK: "action_ask",
        ACTION_GIFT: "action_gift",
        ACTION_SETAVATAR: "action_avatar",
        ACTION_CHECK_TOKEN: "action_check_token",
        //定向分享相关
        SHAREQQ_SCHEME_URL: "mqqapi://share/to_fri?src_type=app&version=1&file_type=news",
        SHAREQQ_H5_URL: "http://openmobile.qq.com/api/check?page=shareindex.html&style=9",


        //设置头像相关
        PARAM_AVATAR_URI: "picture",
        PARAM_APP_ID: "appid",
        PARAM_ACCESS_TOKEN: "access_token",
        PARAM_EXPIRES_IN: "expires_in",
        PARAM_OPEN_ID: "openid",
        PARAM_KEY_STR: "ksystr",

        //Exception
        EXCEPTION_IO: "io",
        EXCEPTION_MALFORMEDURL: "malformed_url",
        EXCEPTION_JSON: "json",
        EXCEPTION_CONNECTTIMEOUT: "connect_timeout",
        EXCEPTION_SOCKETTIMEOUT: "socket_timeout",
        EXCEPTION_NETWORKUNAVAILABLE: "network_unavailabe",
        EXCEPTION_HTTPSTATUS: "http_status",
        EXCEPTION_UNKNOW: "unknow",

        //社交API H5 URL
        DEFAULT_REDIRECT_URI: "auth://tauth.qq.com/",
        DEFAULT_CGI_AUTHORIZE: "https://openmobile.qq.com/oauth2.0/m_authorize?",
        DEFAULT_URL_SEND_STORY: "http://qzs.qq.com/open/mobile/sendstory/sdk_sendstory_v1.3.html?",
        DEFAULT_URL_INVITE: "http://qzs.qq.com/open/mobile/invite/sdk_invite.html?",
        DEFAULT_URL_BRAG: "http://qzs.qq.com/open/mobile/brag/sdk_brag.html?",
        DEFAULT_URL_ASK: "http://qzs.qq.com/open/mobile/request/sdk_request.html?",
        DEFAULT_URL_GIFT: "http://qzs.qq.com/open/mobile/request/sdk_request.html?"
    };
    window.constant.android_contants = window.android_contants = android_contants;
})();(function(){
var global_settings = {
    device: "ios"
};
window.constant.global_settings = window.global_settings = global_settings;
})();(function(){
var ios_constants = {
    kRedirectURL: "www.qq.com",
    kOPEN_APP_SCHEMA_PREFIX: "tencent",
    kDATA_REPORT_ENABLE: "DataReportEnable",
    kSAFARI_ENABLE: "SafariEnable",
    kWEB_VIEW_ENABLE: "WebViewEnable",
    kCONFIG_TIME_STAMP: "ConfigTimeStamp",
    kCONFIG_TIME_FREQUENCY: "ConfigTimeFrequency",
    kCONFIG_SSO: "CommonSSo",
    kCONFIG_SSO_QZONEVERSION: "CommonSSoQZoneVersion",
    kCONFIG_SSO_QZONESCHEMA: "CommonSSOQZoneSchema",
    KAppIphoneQQ: 1,
    KAppIphoneQQZone: 0,
    KReportTypeBonuliData: 0,
    KOpenSDKIncrAuthFromQZoneReportAction: "10786",

    //haowen openapi
    //edit by peter
    //Qzone schema
    kOPEN_ZONE_TEST: "mqzoneopensdk://qzapp", //3_4
    kOPEN_ZONE_3_6_TEST: "mqzoneopensdkapi://qzapp", //3_6
    kOPEN_ZONE_4_0_TEST: "mqzoneopensdkapi19://qzapp", //4_0
    //配合ios7 剪贴板
    kOPEN_ZONE_5_0_TEST:"mqzoneopensdkapiV2://qzapp",
 
 
    //QQ schema
    kOPEN_QQ_TEST:"mqqOpensdkSSoLogin://qqapp",
    kOPEN_QQ_4_2_TEST :"mqqopensdkapiV2://qqapp",
    kOPEN_QQ_5_0_TEST :"mqqopensdkapiV3://qqapp",
 
    kOLD_QQ_TEST :"mqq://qqapp",
    
 

    kQZONE_VERSION_3_3: 0,
    kQZONE_VERSION_3_4: 1,
    kQZONE_VERSION_3_6: 2,
    kQZONE_VERSION_4_0: 3,
    kQZONE_VERSION_5_0: 4,
 

    kQQ_VERSION_3_0: 0,
    kQQ_VERSION_4_0: 1,
    kQQ_VERSION_4_2: 2,
    kQQ_VERSION_5_0: 3,

    //QQ,QZone Schema;
    kOPEN_QZONE_API_SCHEMA: "mqzoneopensdkapi",
    kOPEN_QQ_API_SCHEMA: "mqqOpensdkSSoLogin",
    kOPEN_QZONE_HOST: "qzapp",
    kOPEN_QQ_HOST: "SSoLogin",
    responseType: "token"
};
window.constant.ios_constants = window.ios_constants = ios_constants;
})();(function(){
var Order = {
    QQversion: null,
    Qzoneversion: null,
    finallOrder: null
};
window.constant.Order = window.Order = Order;
})();(function () {
    /**
     * 启动顺序
     * @class start_order
     * @type {{start: string, start_list: Array}}
     */
    var start_order = {
        start: "QQ",
        /**
         * 启动顺序数组
         * @property start_list
         * @type {Object} 数组类型
         * @default ["QQ", "Qzone", "Browser"]
         */
       start_list: ["QQ","Qzone", "Browser"]
       // start_list: ["Browser","Qzone", "QQ"]
    };
    window.constant.start_order = window.start_order = start_order;
})();