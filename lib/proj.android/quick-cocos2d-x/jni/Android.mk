LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := quickcocos2dx
LOCAL_SRC_FILES := quickcocos2dx.cpp

include $(BUILD_SHARED_LIBRARY)
