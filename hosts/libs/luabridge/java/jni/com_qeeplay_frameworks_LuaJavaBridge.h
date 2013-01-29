
#include <jni.h>

#ifndef __COM_QEEPLAY_FRAMEWORKS_LUAJAVABRIDGE_H_
#define __COM_QEEPLAY_FRAMEWORKS_LUAJAVABRIDGE_H_

extern "C" {

/*
 * Class:     com_qeeplay_frameworks_LuaJavaBridge
 * Method:    callLuaFunctionWithString
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_qeeplay_frameworks_LuaJavaBridge_callLuaFunctionWithString
  (JNIEnv *, jclass, jint, jstring);

/*
 * Class:     com_qeeplay_frameworks_LuaJavaBridge
 * Method:    callLuaGlobalFunctionWithString
 * Signature: (Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_qeeplay_frameworks_LuaJavaBridge_callLuaGlobalFunctionWithString
  (JNIEnv *env, jclass, jstring, jstring);

/*
 * Class:     com_qeeplay_frameworks_LuaJavaBridge
 * Method:    retainLuaFunction
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_qeeplay_frameworks_LuaJavaBridge_retainLuaFunction
  (JNIEnv *env, jclass, jint);

/*
 * Class:     com_qeeplay_frameworks_LuaJavaBridge
 * Method:    releaseLuaFunction
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_qeeplay_frameworks_LuaJavaBridge_releaseLuaFunction
  (JNIEnv *env, jclass, jint);

} // extern "C"

#endif // __COM_QEEPLAY_FRAMEWORKS_LUAJAVABRIDGE_H_
