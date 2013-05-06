
### INSTALL ANDROID SDK

1.  Download latest **ADT Bundle for Mac** from [http://developer.android.com/sdk/index.html](http://developer.android.com/sdk/index.html)
2.  Decompress adt-bundle-mac-x86\_64-2013XXXX.zip
3.  Rename folder **adt-bundle-mac-x86\_64-2013XXXX** to **android**
4.  Rename folder **android/sdk** to **android/android\_sdk\_macosx**
5.  Run **tools/android**, Select **Android SDK 2.2**, Install packages

![](https://raw.github.com/dualface/quick-cocos2d-x/master/doc/img/INSTALL_ANDROID_SDK_MAC_01.png)

<br />

### INSTALL ANDROID NDK

1.  **Android NDK r8b Recommended**, download from [http://dl.google.com/android/ndk/android-ndk-r8b-darwin-x86.tar.bz2](http://dl.google.com/android/ndk/android-ndk-r8b-darwin-x86.tar.bz2) .
2.  Decompress android-ndk-r8b-darwin-x86.tar.bz2
3.  Move folder android-ndk-r8b to android/android-ndk-r8b

<br />

Directory structure:

```
<PATH_TO>/android/android_sdk_macosx
<PATH_TO>/android/android_ndk_r8b
<PATH_TO>/android/eclipse
```

<br />

### SETUP ENVIRONMENT VARIABLE

``` bash
vi ~/.profile

# CHANGE PATH_TO
export QUICK_COCOS2DX_ROOT=/<PATH_TO>/quick-cocos2d-x
export ANDROID_SDK_ROOT=/<PATH_TO>/android-sdk-macosx
export ANDROID_NDK_ROOT=/<PATH_TO>/android-ndk-r8b

export COCOS2DX_ROOT=$QUICK_COCOS2DX_ROOT/lib/cocos2d-x
export ANDROID_HOME=$ANDROID_SDK_ROOT
```

<br />
