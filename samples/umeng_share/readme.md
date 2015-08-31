
### android工程注意事项 ###

* **工程依赖源代码位置**
$QUICK_COCOS2DX_ROOT/lib/sdk/umeng_share/umeng_share_android/umeng_share_android

* **工程依赖库位置**
$QUICK_COCOS2DX_ROOT/lib/sdk/umeng_share/umeng_share_android/social_sdk_library_project

* **集成版本**

集成的是umeng_android_social_sdk_3.3.6版本 网址<http://dev.umeng.com/social/android/share/quick-integration>

### ios工程注意事项 ###

* **工程依赖源代码位置**
$QUICK_COCOS2DX_ROOT/lib/sdk/umeng_feedback/umeng_share_ios/*

* **集成版本**

集成的是umeng_ios_social_sdk_3.3.7版本 网址<http://dev.umeng.com/social/ios/share/quick-integration>

**如果没有请加手动加到工程中**

### android分享图片说明 ###

默认是支持分享网络图片
如果要分享本地图片，需要自行修改UmengShareSDK类中的shareImg函数中else部分，

是本地图片的话，传入的路径，方式可能有各种情况，所以按自已的需要修改，不好意思，这里有点麻烦
