
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_csarmature_static
LOCAL_MODULE_FILENAME := libcsarmature

LOCAL_SRC_FILES := ../animation/CSAnimation.cpp \
    ../animation/CSProcessBase.cpp \
    ../animation/CSTween.cpp \
    ../CSArmature.cpp \
    ../CSBone.cpp \
    ../datas/CSDatas.cpp \
    ../display/CSBatchNode.cpp \
    ../display/CSDecorativeDisplay.cpp \
    ../display/CSDisplayFactory.cpp \
    ../display/CSDisplayManager.cpp \
    ../display/CSShaderNode.cpp \
    ../display/CSSkin.cpp \
    ../external_tool/CCTexture2DMutable.cpp \
    ../external_tool/Json/CSContentJsonDictionary.cpp \
    ../external_tool/Json/lib_json/json_reader.cpp \
    ../external_tool/Json/lib_json/json_value.cpp \
    ../external_tool/Json/lib_json/json_writer.cpp \
    ../utils/CSArmatureDataManager.cpp \
    ../utils/CSDataReaderHelper.cpp \
    ../utils/CSSpriteFrameCacheHelper.cpp \
    ../utils/CSTransformHelp.cpp \
    ../utils/CSTweenFunction.cpp \
    ../utils/CSUtilMath.cpp

LOCAL_C_INCLUDES := $(QUICK_COCOS2DX_ROOT)/lib/third_party/CSArmature/animation \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/CSArmature/datas \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/CSArmature/display \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/CSArmature/external_tool \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/CSArmature/external_tool/Json \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/CSArmature/external_tool/Json/json \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/CSArmature/external_tool/Json/lib_json \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/CSArmature/utils \
    $(QUICK_COCOS2DX_ROOT)/lib/third_party/CSArmature \
    $(QUICK_COCOS2DX_ROOT)/lib/cocos2d-x/cocos2dx/support/tinyxml2

LOCAL_CFLAGS := -Wno-psabi -fexceptions

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
