(function(){
	
	var Base64 = {
		encode : function(str){
			return window.btoa(unescape(encodeURIComponent(str)));
			},
		};

	window.BASE64 = Base64;
})
();(function(){
    /**
     * 控制类，用来控制启动本地客户端和浏览器的一个类
     * @class control
     * @type {{initWithAppId: Function, startQzone: Function, startQQ: Function, startBrower: Function, initWithAppIdself: Function, registerAppself: Function, SetConnectAppid: Function, _registerQQApi: Function, setPermissions: Function}}
     */
	var control = {
        initWithAppId: function (appid) {
            //空方法，ios需要该接口
            this.initWithAppIdself();
            this.SetConnectAppid(appid);
            this.registerAppself();
            //haowen for regist qq appid
            this._registerQQApi(appid);
            return JSTencentOauth.loacl_appid;
        },
        /**
         * 尝试启动Qzone
         * @method  startQzone
         * @returns {Boolean}启动成功返回true，否则返回false
         */
        startQzone: function () {
            log.d("control", "startQzone");

            //ios only
            jump.setSchema();

            var info = openUi.getQZoneInfo(jumpParams.action);
            if (info == null) return false;
            else {
                //android only
                jumpParams.packageName = info.packageName;
                jumpParams.className = info.className;
                //ios only
                jumpParams.source = "qzone";

                var json = jump.getJumpParams(jumpParams);
                //ios跳转结果只有调用后才知道，android可以考虑jump.jump()直接返回true。
                return jump.jump(json);
            }
        },
        /**
         * 启动QQ
         * @method startQQ
         * @returns {Boolean} 启动成功则返回true，否则返回false
         */
        startQQ: function () {
            log.d("local.js", "startQQ()");

            //ios only
            jump.setSchema();

            var info = openUi.getQQInfo(jumpParams.action);
            if (info == null) return false;
            else {
                //android only
                jumpParams.packageName = info.packageName;
                jumpParams.className = info.className;
                //ios only
                jumpParams.source = "qq";

                var json = jump.getJumpParams(jumpParams);
                //ios跳转结果只有调用后才知道，android可以考虑jump.jump()直接返回true。
                return jump.jump(json);
            }
        },
        /**
         *启动浏览器
         * @method startBrower
         * @returns {Boolean}启动成功返回true，否则返回false
         */
        startBrower: function () {
            return jump.startBrowser();
        },
        initWithAppIdself: function () {
            JSTencentOauth.loacl_redirectURI =
                ios_constants.kRedirectURL;
            JSTencentOauth.loacl_userGetUserInfo = true;

        },
        registerAppself: function () {
            loacl_appSchema = ios_constants.kOPEN_APP_SCHEMA_PREFIX +
                JSTencentOauth.loacl_appid;
        },

        SetConnectAppid: function (appid) {
            var appid_url = {
                "appid": appid
            };
            var json = JSON.stringify(appid_url);
            var temp =
                oauth.convertAppIdJs(json);
            JSTencentOauth.loacl_appid =
                temp;

        },
        _registerQQApi: function (appid) {
            var appid_url = {
                "appid": appid
            };
            var json = JSON.stringify(appid_url);
            oauth.registQQAPIWithQQAppId(json);
        },
        setPermissions: function (params) {
            JSTencentOauth.permissions = params;
        }
    };
    tencent.control = control;
})();(function () {
    /**
     * 存储跳转的时候需要的数据，是一个全局变量
     * @class jumpParams
     * @type {{packageName: null, className: null, action: null, scope: null, source: null}}
     */
    var jumpParams = {
        /**
         * 跳转的包名
         * @property packageName
         * @type {String}
         * @default null
         */
        packageName: null,
        /**
         * 跳转的类名
         * @property className
         * @type {String}
         * @default null
         */
        className: null,
        /**
         * 跳转对应的动作
         * @property action
         * @type {String}
         * @default null
         */
        action: null,
        /**
         * 跳转对应的权限
         * @property scope
         * @type {String}
         * @default null
         */
        scope: null,
        /**
         * 数据来源
         * @property source
         * @type {String}
         * @default null
         */
        source: null

    };
    window.utils.jumpParams = window.jumpParams = jumpParams;
})();(function (){
    var reportUtils = {


         /*
          初始化开始数据上报
         * @method startQQ4Connect
         * */
        startQQ4Connect:function(isAutoCaugth){
            sdk_reportUtils.startQQ4Connect(isAutoCaugth);
        } ,

        /**
         * 上报openid到QQ
         * @method reportQQ
         */
        reportQQ : function(openid){
            log.d("reportUtils","reportQQ");
            sdk_reportUtils.reportQQ(openid);
        },
        /**
         *
         * @method  trackCustomEvent
         * @param eventId
         * @param arrayStr 用“，”分割的字符串数组
         */
        trackCustomEvent : function(eventId,arrayStr){
            log.d("reportUtils","trackCustomEvent");
            sdk_reportUtils.trackCustomEvent(eventId,arrayStr);
			log.d("reportUtils","trackCustomEvent-end");
        },
        /**
         * @method reportError
         * @param error
         */
        reportError:function(error){

            sdk_reportUtils.reportError(error);
        },
        /* 次数统计 带key-value参数的事件
        * @method trackCustomEndKVEvent
         * @param key
         * @param value
         * @param event
        * */
        trackCustomKVEvent:function(key,value,event){

            sdk_reportUtils.trackCustomKVEvent(key,value,event);

        },
         /* 时长统计开始
         * @method trackCustomBeginKVEvent
         *
         * */
        trackCustomBeginKVEvent:function(key,value,event){
            sdk_reportUtils.trackCustomBeginKVEvent(key,value,event);

        },
         /*
         *  时长统计结束
         * */
        trackCustomEndKVEvent:function(){
            sdk_reportUtils.trackCustomEndKVEvent();

        },

        /*
        * 接口监控
        * @method startMonitor
        * @param ip
        * @param cmd
        *
        * */
        startMonitor:function(ip,cmd){
          sdk_reportUtils.startMonitor(ip,cmd);
        },


        /**
         * 非业务上报, 上报到即通, 同步给罗盘和腾讯分析
         * @method reportGraphPath
         * @param graphPath
         */
        reportGraphPath : function(graphPath){
            log.d("reportUtils","reportGraphPath");
            this.trackCustomEvent( "requireApi",graphPath);
        },
        reportBernoulli : function(reportId,costTime,appId){
            sdk_reportUtils.reportBernoulli(reportId,costTime,appId);
        },


    };
     window.reportUtils = reportUtils;
})();(function () {
    /**
     * 本类提供字符串的一些操作
     * @class strUtil
     * @type {{stringToArray: Function, isEmpty: Function}}
     */
    var strUtil = {
        /**
         *将[a,b,c]格式的数组转换成string数组
         * @method stringToArray
         * @params {String} str [a,b,c]格式的字符串
         */
        stringToArray: function (str) {
            if (str == null || str == undefined) return null;
            if(str.length < 2)return null;
            var subStr = str.substr(1, str.length - 2);
            return subStr.split(",");
        },
        /**
         * 判断一个字符串是否为空
         * @method isEmpty
         * @param {String}str
         * @returns {Boolean} 如果str为null或者undefined或者“”则返回true否则返回false
         */
        isEmpty: function (str) {
            return    str === null || str === undefined || str === "";
        } ,

        isUrlValidate:function(str){
            var i= str.indexOf("http://");
            var j=str.indexOf("https://");
            return i==0||j==0;
        }


    };
    window.local.strUtil = window.strUtil = strUtil;
})();