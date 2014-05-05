LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := cocos_extension_static

LOCAL_MODULE_FILENAME := libextension

LOCAL_SRC_FILES := \
    GUI/CCControlExtension/CCControl.cpp \
    GUI/CCControlExtension/CCControlButton.cpp \
    GUI/CCControlExtension/CCInvocation.cpp \
    GUI/CCControlExtension/CCScale9Sprite.cpp \
    GUI/CCControlExtension/CCControlUtils.cpp \
    GUI/CCEditBox/CCEditBox.cpp \
    GUI/CCEditBox/CCEditBoxImplAndroid.cpp

ifndef $(QUICK_MINI_TARGET)

    LOCAL_SRC_FILES += \
        AssetsManager/AssetsManager.cpp \
        CCBReader/CCBAnimationManager.cpp \
        CCBReader/CCBFileLoader.cpp \
        CCBReader/CCBKeyframe.cpp \
        CCBReader/CCBReader.cpp \
        CCBReader/CCBSequence.cpp \
        CCBReader/CCBSequenceProperty.cpp \
        CCBReader/CCBValue.cpp \
        CCBReader/CCControlButtonLoader.cpp \
        CCBReader/CCControlLoader.cpp \
        CCBReader/CCData.cpp \
        CCBReader/CCLabelBMFontLoader.cpp \
        CCBReader/CCLabelTTFLoader.cpp \
        CCBReader/CCLayerColorLoader.cpp \
        CCBReader/CCLayerGradientLoader.cpp \
        CCBReader/CCLayerLoader.cpp \
        CCBReader/CCMenuItemImageLoader.cpp \
        CCBReader/CCMenuItemLoader.cpp \
        CCBReader/CCNode+CCBRelativePositioning.cpp \
        CCBReader/CCNodeLoader.cpp \
        CCBReader/CCNodeLoaderLibrary.cpp \
        CCBReader/CCParticleSystemQuadLoader.cpp \
        CCBReader/CCScale9SpriteLoader.cpp \
        CCBReader/CCScrollViewLoader.cpp \
        CCBReader/CCSpriteLoader.cpp \
        CCArmature/animation/CCArmatureAnimation.cpp \
        CCArmature/animation/CCProcessBase.cpp \
        CCArmature/animation/CCTween.cpp \
        CCArmature/CCArmature.cpp \
        CCArmature/CCBone.cpp \
        CCArmature/datas/CCDatas.cpp \
        CCArmature/display/CCBatchNode.cpp \
        CCArmature/display/CCDecorativeDisplay.cpp \
        CCArmature/display/CCDisplayFactory.cpp \
        CCArmature/display/CCDisplayManager.cpp \
        CCArmature/display/CCShaderNode.cpp \
        CCArmature/display/CCSkin.cpp \
        CCArmature/external_tool/CCTexture2DMutable.cpp \
        CCArmature/external_tool/Json/CSContentJsonDictionary.cpp \
        CCArmature/external_tool/Json/lib_json/json_reader.cpp \
        CCArmature/external_tool/Json/lib_json/json_value.cpp \
        CCArmature/external_tool/Json/lib_json/json_writer.cpp \
        CCArmature/utils/CCArmatureDataManager.cpp \
        CCArmature/utils/CCDataReaderHelper.cpp \
        CCArmature/utils/CCSpriteFrameCacheHelper.cpp \
        CCArmature/utils/CCTransformHelp.cpp \
        CCArmature/utils/CCTweenFunction.cpp \
        CCArmature/utils/CCUtilMath.cpp \
        GUI/CCControlExtension/CCControlColourPicker.cpp \
        GUI/CCControlExtension/CCControlHuePicker.cpp \
        GUI/CCControlExtension/CCControlPotentiometer.cpp \
        GUI/CCControlExtension/CCControlSaturationBrightnessPicker.cpp \
        GUI/CCControlExtension/CCControlSlider.cpp \
        GUI/CCControlExtension/CCControlStepper.cpp \
        GUI/CCControlExtension/CCControlSwitch.cpp \
        GUI/CCScrollView/CCScrollView.cpp \
        GUI/CCScrollView/CCSorting.cpp \
        GUI/CCScrollView/CCTableView.cpp \
        GUI/CCScrollView/CCTableViewCell.cpp \
        filters/filters/CCFilter.cpp \
		filters/filters/CCBlurFilter.cpp \
		filters/filters/CCBrightnessFilter.cpp \
		filters/filters/CCContrastFilter.cpp \
		filters/filters/CCDropShadowFilter.cpp \
		filters/filters/CCExposureFilter.cpp \
		filters/filters/CCGammaFilter.cpp \
		filters/filters/CCGrayFilter.cpp \
		filters/filters/CCHazeFilter.cpp \
		filters/filters/CCHueFilter.cpp \
		filters/filters/CCMaskFilter.cpp \
		filters/filters/CCRGBFilter.cpp \
		filters/filters/CCSaturationFilter.cpp \
		filters/filters/CCSepiaFilter.cpp \
		filters/filters/CCSharpenFilter.cpp \
		filters/filters/CCTestFilter.cpp \
		filters/nodes/CCFilteredSprite.cpp \
		filters/shaders/ccFilterShaders.cpp \
        network/WebSocket.cpp

endif


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static

ifndef $(QUICK_MINI_TARGET)

    LOCAL_WHOLE_STATIC_LIBRARIES += cocos_chipmunk_static
    LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
    LOCAL_WHOLE_STATIC_LIBRARIES += libwebsockets_static

endif


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                           $(LOCAL_PATH)/GUI/CCControlExtension \
                           $(LOCAL_PATH)/GUI/CCEditBox


ifndef $(QUICK_MINI_TARGET)

    LOCAL_EXPORT_C_INCLUDES += \
                               $(LOCAL_PATH)/network \
                               $(LOCAL_PATH)/CCBReader \
                               $(LOCAL_PATH)/Components \
                               $(LOCAL_PATH)/GUI/CCScrollView \
                               $(LOCAL_PATH)/CCArmature \
                               $(LOCAL_PATH)/CCArmature/animation \
                               $(LOCAL_PATH)/CCArmature/datas \
                               $(LOCAL_PATH)/CCArmature/display \
                               $(LOCAL_PATH)/CCArmature/external_tool \
                               $(LOCAL_PATH)/CCArmature/external_tool/Json \
                               $(LOCAL_PATH)/CCArmature/external_tool/Json/lib_json \
                               $(LOCAL_PATH)/CCArmature/utils \
                               $(LOCAL_PATH)/filters

endif


LOCAL_C_INCLUDES = $(LOCAL_EXPORT_C_INCLUDES)

LOCAL_CFLAGS := -fexceptions

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,scripting/lua/proj.android)

ifndef $(QUICK_MINI_TARGET)
    $(call import-module,external/libwebsockets/android)
endif
