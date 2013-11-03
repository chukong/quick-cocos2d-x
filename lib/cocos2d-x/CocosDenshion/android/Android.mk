LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocosdenshion_static

LOCAL_MODULE_FILENAME := libcocosdenshion

LOCAL_SRC_FILES := SimpleAudioEngine.cpp \
                   jni/SimpleAudioEngineJni.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include \
                    $(LOCAL_PATH)/../../cocos2dx \
                    $(LOCAL_PATH)/../../cocos2dx/include \
                    $(LOCAL_PATH)/../../cocos2dx/kazmath/include \
                    $(LOCAL_PATH)/../../cocos2dx/platform/android

LOCAL_CFLAGS += -Wno-psabi $(ANDROID_COCOS2D_BUILD_FLAGS)
LOCAL_EXPORT_CFLAGS += -Wno-psabi

include $(BUILD_STATIC_LIBRARY)
