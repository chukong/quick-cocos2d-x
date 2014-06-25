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
        network/WebSocket.cpp \
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
		DragonBones/animation/Animation.cpp \
		DragonBones/animation/AnimationState.cpp \
		DragonBones/animation/TimelineState.cpp \
		DragonBones/Armature.cpp \
		DragonBones/Bone.cpp \
		DragonBones/core/DBObject.cpp \
		DragonBones/core/DragonBones.cpp \
		DragonBones/events/AnimationEvent.cpp \
		DragonBones/events/ArmatureEvent.cpp \
		DragonBones/events/Event.cpp \
		DragonBones/events/FrameEvent.cpp \
		DragonBones/events/SoundEvent.cpp \
		DragonBones/events/SoundEventManager.cpp \
		DragonBones/factories/BaseFactory.cpp \
		DragonBones/objects/dbtinyxml2.cpp \
		DragonBones/objects/DisplayData.cpp \
		DragonBones/objects/TransformTimeline.cpp \
		DragonBones/objects/XMLDataParser.cpp \
		DragonBones/renderer/CCDragonBones.cpp \
		DragonBones/renderer/Cocos2dxAtlasNode.cpp \
		DragonBones/renderer/Cocos2dxDisplayBridge.cpp \
		DragonBones/renderer/Cocos2dxFactory.cpp \
		DragonBones/renderer/Cocos2dxTextureAtlas.cpp \
		DragonBones/Slot.cpp \
		DragonBones/utils/BytesType.cpp \
		DragonBones/utils/ConstValues.cpp \
		DragonBones/utils/DBDataUtil.cpp \
		DragonBones/utils/DBGeometry.cpp \
		DragonBones/utils/TransformUtil.cpp \
		webview/android/CCWebView.cpp \

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
                               $(LOCAL_PATH)/Components \
                               $(LOCAL_PATH)/GUI/CCScrollView \
                               $(LOCAL_PATH)/filters \
                               $(LOCAL_PATH)/DragonBones \
                               $(LOCAL_PATH)/webview

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
