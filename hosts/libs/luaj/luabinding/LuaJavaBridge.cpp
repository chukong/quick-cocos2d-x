
#include "LuaJavaBridge.h"
#include <android/log.h>
#include <string.h>

#define  LOG_TAG    "LuaJavaBridge_c"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define LUAJ_TYPE_NOT_SUPPORT       -1
#define LUAJ_TYPE_VOID              0
#define LUAJ_TYPE_INT               1
#define LUAJ_TYPE_FLOAT             2
#define LUAJ_TYPE_BOOLEAN           3
#define LUAJ_TYPE_STRING            4
#define LUAJ_TYPE_FUNCTION          5

#define LUAJ_TYPE_INT_CHAR          '1'
#define LUAJ_TYPE_FLOAT_CHAR        '2'
#define LUAJ_TYPE_BOOLEAN_CHAR      '3'
#define LUAJ_TYPE_STRING_CHAR       '4'
#define LUAJ_TYPE_FUNCTION_CHAR     '5'

#define LUAJ_ERR_INVALID_PARAMETERS -2
#define LUAJ_ERR_METHOD_NOT_FOUND   -3
#define LUAJ_ERR_EXCEPTION_OCCURRED -4

#define LUAJ_REGISTRY_FUNCTION      "luajb_function_id"     // table[function] = id
#define LUAJ_REGISTRY_RETAIN        "luajb_id_retain_count" // table[id] = retain count

extern "C" {

#include "tolua_fix.h"

typedef union
{
    int         intValue;
    float       floatValue;
    int         boolValue;
    const char *stringValue;
} LuaJavaBridge_Return;

class LuaJavaBridge_CallInfo
{
public:
    JNIEnv                 *env;
    jclass                  classID;
    jmethodID               methodID;
    char                   *argsType;
    LuaJavaBridge_Return    ret;
    jstring                 retjs;
    int                     retType;

    LuaJavaBridge_CallInfo(void)
    : env(NULL)
    , classID(NULL)
    , methodID(NULL)
    , argsType(NULL)
    , retjs(NULL)
    , retType(LUAJ_TYPE_VOID)
    {
        memset(&ret, 0, sizeof(ret));
    }

    ~LuaJavaBridge_CallInfo(void)
    {
        if (argsType) delete []argsType;
    }

    void setArgsType(const char *type)
    {
        argsType = new char[strlen(type) + 1];
        strcpy(argsType, type);
    }
};

int callJavaStaticMethodWithArgs(lua_State *L);
int callJavaStaticMethodWithArray(lua_State *L);
int checkParameters(lua_State *L, LuaJavaBridge_CallInfo *call);
int checkArgsType(const char typeChar);
int retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn);
int getMethodInfo(LuaJavaBridge_CallInfo *call, const char *className, const char *methodName, const char *paramCode);
int fetchArrayElements(lua_State *L, int index);
int callAndPushReturnValue(lua_State *L, LuaJavaBridge_CallInfo *call, jvalue *args);

static JavaVM    *s_jvm = NULL;
static lua_State *s_LuaState = NULL;
static int        s_newFunctionId = 0;

void LuaJavaBridge_setJavaVM(JavaVM *vm)
{
    s_jvm = vm;
}

void LuaJavaBridge_setLuaState(lua_State *L)
{
    s_LuaState = L;
}

void LuaJavaBridge_luabinding_open(lua_State *L)
{
    LuaJavaBridge_setLuaState(L);

    lua_newtable(L);

    lua_pushstring(L, "callStaticMethod");
    lua_pushcfunction(L, callJavaStaticMethodWithArgs);
    lua_rawset(L, -3);

    lua_pushstring(L, "callStaticMethodWithArray");
    lua_pushcfunction(L, callJavaStaticMethodWithArray);
    lua_rawset(L, -3);

    lua_setglobal(L, "LuaJavaBridge");
}

/*
args:
    const char *className
    const char *methodName
    const char*methodSig
    LUA_TABLE args
    const char *argsType
    const char *retType
*/
int callJavaStaticMethodWithArgs(lua_State *L)
{
    LuaJavaBridge_CallInfo call;
    int check = checkParameters(L, &call);
    if (check) return check;

    // check args
    int count = fetchArrayElements(L, -1);                      /* L: args e1 e2 e3 e4 ... */
    if (count == 0)
    {
        return callAndPushReturnValue(L, &call, NULL);
    }

    jvalue *args = new jvalue[count];
    for (int i = 0; i < count; ++i)
    {
        int index = -count + i;
        switch (checkArgsType(call.argsType[i]))
        {
            case LUAJ_TYPE_INT:
                args[i].i = (int)lua_tonumber(L, index);
                break;

            case LUAJ_TYPE_FLOAT:
                args[i].f = lua_tonumber(L, index);
                break;

            case LUAJ_TYPE_BOOLEAN:
                args[i].z = lua_toboolean(L, index) != 0 ? JNI_TRUE : JNI_FALSE;
                break;

            case LUAJ_TYPE_FUNCTION:
                args[i].i = retainLuaFunction(L, index, NULL);
                break;

            case LUAJ_TYPE_STRING:
            default:
                args[i].l = call.env->NewStringUTF(lua_tostring(L, index));
        }
    }
    lua_pop(L, count);                                          /* L: args */

    check = callAndPushReturnValue(L, &call, args);

    for (int i = 0; i < count; ++i)
    {
        if (checkArgsType(call.argsType[i]) == LUAJ_TYPE_FUNCTION)
        {
            LuaJavaBridge_releaseLuaFunctionById(args[i].i);
        }
    }

    delete []args;
    return check;
}

int callJavaStaticMethodWithArray(lua_State *L)
{
    LuaJavaBridge_CallInfo call;
    int check = checkParameters(L, &call);
    if (check) return check;

    // create Java vector, copy args from lua table
    JNIEnv *env = call.env;

    jclass jvectorClass  = env->FindClass("java/util/Vector");
    jmethodID jvectorAdd = env->GetMethodID(jvectorClass, "add", "(Ljava/lang/Object;)Z");
    jobject jvector      = env->NewObject(jvectorClass, env->GetMethodID(jvectorClass, "<init>", "()V"));

    jclass jintClass     = env->FindClass("java/lang/Integer");
    jmethodID jintCtor   = env->GetMethodID(jintClass, "<init>", "(I)V");

    jclass jfloatClass   = env->FindClass("java/lang/Float");
    jmethodID jfloatCtor = env->GetMethodID(jfloatClass, "<init>", "(F)V");

    jclass jboolClass    = env->FindClass("java/lang/Boolean");
    jmethodID jboolCtor  = env->GetMethodID(jboolClass, "<init>", "(Z)V");

    // check array length
    int count = fetchArrayElements(L, -1);                      /* L: args e1 e2 e3 e4 ... */
    int *functionsID = new int[count];
    memset(functionsID, 0, sizeof(int) * count);
    int functionIndex = 0;
    for (int i = 0; i < count; ++i)
    {
        int index = -count + i;
        jobject value;
        switch (checkArgsType(call.argsType[i]))
        {
            case LUAJ_TYPE_INT:
                value = env->NewObject(jintClass, jintCtor, lua_tonumber(L, index));
                break;

            case LUAJ_TYPE_FLOAT:
                value = env->NewObject(jfloatClass, jfloatCtor, lua_tonumber(L, index));
                break;

            case LUAJ_TYPE_BOOLEAN:
                value = env->NewObject(jboolClass, jboolCtor, lua_toboolean(L, index) != 0);
                break;

            case LUAJ_TYPE_FUNCTION:
                functionsID[functionIndex] = retainLuaFunction(L, index, NULL);
                value = env->NewObject(jintClass, jintCtor, functionsID[functionIndex]);
                functionIndex++;
                break;

            case LUAJ_TYPE_STRING:
            default:
                value = env->NewStringUTF(lua_tostring(L, index));
        }
        env->CallBooleanMethod(jvector, jvectorAdd, value);
    }
    lua_pop(L, count);                                          /* L: args */

    for (int i = 0; i < count; ++i)
    {
        if (functionsID[i])
        {
            LuaJavaBridge_releaseLuaFunctionById(functionsID[i]);
        }
    }
    delete []functionsID;

    jvalue args[1];
    args[0].l = jvector;
    return check = callAndPushReturnValue(L, &call, args);
}

// increase lua function refernece counter, return counter
int LuaJavaBridge_retainLuaFunctionById(int functionId)
{
    lua_State *L = s_LuaState;

    lua_pushstring(L, LUAJ_REGISTRY_RETAIN);                    /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        return 0;
    }

    // get counter
    lua_pushinteger(L, functionId);                             /* L: id_r id */
    lua_rawget(L, -2);                                          /* L: id_r r */
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        lua_pop(L, 2);
        return 0;
    }

    // increase counter
    int retainCount = lua_tonumber(L, -1);
    retainCount++;
    lua_pop(L, 1);                                              /* L: id_r */
    lua_pushinteger(L, functionId);                             /* L: id_r id */
    lua_pushinteger(L, retainCount);                            /* L: id_r id r */
    lua_rawset(L, -3);                            /* id_r[id] = r, L: id_r */
    lua_pop(L, 1);

    LOGD("LuaJavaBridge_retainLuaFunctionById(%d) - retain count = %d", functionId, retainCount);

    return retainCount;
}

// decrease lua function reference counter, return counter
int LuaJavaBridge_releaseLuaFunctionById(int functionId)
{
    lua_State *L = s_LuaState;
                                                                /* L: */
    lua_pushstring(L, LUAJ_REGISTRY_FUNCTION);                  /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        LOGD("LuaJavaBridge_releaseLuaFunctionById() - LUAJ_REGISTRY_FUNCTION not exists");
        return 0;
    }

    lua_pushstring(L, LUAJ_REGISTRY_RETAIN);                    /* L: f_id key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f_id id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 2);
        LOGD("LuaJavaBridge_releaseLuaFunctionById() - LUAJ_REGISTRY_RETAIN not exists");
        return 0;
    }

    lua_pushinteger(L, functionId);                             /* L: f_id id_r id */
    lua_rawget(L, -2);                                          /* L: f_id id_r r */
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        lua_pop(L, 3);
        LOGD("LuaJavaBridge_releaseLuaFunctionById() - function id %d not found", functionId);
        return 0;
    }

    int retainCount = lua_tonumber(L, -1);
    retainCount--;

    if (retainCount > 0)
    {
        // update counter
        lua_pop(L, 1);                                          /* L: f_id id_r */
        lua_pushinteger(L, functionId);                         /* L: f_id id_r id */
        lua_pushinteger(L, retainCount);                        /* L: f_id id_r id r */
        lua_rawset(L, -3);                        /* id_r[id] = r, L: f_id id_r */
        lua_pop(L, 2);
        LOGD("LuaJavaBridge_releaseLuaFunctionById() - function id %d retain count = %d", functionId, retainCount);
        return retainCount;
    }

    // remove lua function reference
    lua_pop(L, 1);                                              /* L: f_id id_r */
    lua_pushinteger(L, functionId);                             /* L: f_id id_r id */
    lua_pushnil(L);                                             /* L: f_id id_r id nil */
    lua_rawset(L, -3);                          /* id_r[id] = nil, L: f_id id_r */

    lua_pop(L, 1);                                              /* L: f_id */
    lua_pushnil(L);                                             /* L: f_id nil */
    while (lua_next(L, -2) != 0)                                /* L: f_id f id */
    {
        int value = lua_tonumber(L, -1);
        lua_pop(L, 1);                                          /* L: f_id f */
        if (value == functionId)
        {
            lua_pushnil(L);                                     /* L: f_id f nil */
            lua_rawset(L, -3);                   /* f_id[f] = nil, L: f_id */
            break;
        }
    }                                                           /* L: f_id */

    lua_pop(L, 1);
    LOGD("LuaJavaBridge_releaseLuaFunctionById() - function id %d released", functionId);
    return 0;
}

int LuaJavaBridge_callLuaFunctionById(int functionId, const char *arg)
{
    lua_State *L = s_LuaState;
    int top = lua_gettop(L);
                                                                /* L: */
    lua_pushstring(L, LUAJ_REGISTRY_FUNCTION);                  /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        return -1;
    }

    lua_pushnil(L);                                             /* L: f_id nil */
    while (lua_next(L, -2) != 0)                                /* L: f_id f id */
    {
        int value = lua_tonumber(L, -1);
        lua_pop(L, 1);                                          /* L: f_id f */
        if (value == functionId)
        {
            lua_pushstring(L, arg);                             /* L: f_id f arg */
            int ok = lua_pcall(L, 1, 1, 0);                     /* L: f_id ret|err */
            int ret;
            if (ok == 0)
            {
                ret = lua_tonumber(L, -1);
            }
            else
            {
                ret = -ok;
            }

            lua_settop(L, top);
            return ret;
        }
    }                                                           /* L: f_id */

    lua_settop(L, top);
    return -1;
}

// call lua global function
int LuaJavaBridge_callLuaGlobalFunction(const char *functionName, const char *arg)
{
    lua_State *L = s_LuaState;

    int ret = -1;
    int top = lua_gettop(L);

    lua_getglobal(L, functionName);
    if (lua_isfunction(L, -1))
    {
        lua_pushstring(L, arg);
        int ok = lua_pcall(L, 1, 1, 0);
        if (ok == 0)
        {
            ret = lua_tonumber(L, -1);
        }
        else
        {
            ret = -ok;
        }
    }

    lua_settop(L, top);
    return ret;
}

// ----------------------------------------

// increase lua function reference counter, return functionId
int retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn)
{
                                                                /* L: f ... */
    lua_pushstring(L, LUAJ_REGISTRY_FUNCTION);                  /* L: f ... key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f ... f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushstring(L, LUAJ_REGISTRY_FUNCTION);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }

    lua_pushstring(L, LUAJ_REGISTRY_RETAIN);                    /* L: f ... f_id key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f ... f_id id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushstring(L, LUAJ_REGISTRY_RETAIN);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }

    // get function id
    lua_pushvalue(L, functionIndex - 2);                        /* L: f ... f_id id_r f */
    lua_rawget(L, -3);                                          /* L: f ... f_id id_r id */

    int functionId;
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        // first retain, create new id
        lua_pop(L, 1);                                          /* L: f ... f_id id_r */
        s_newFunctionId++;
        functionId = s_newFunctionId;

        lua_pushvalue(L, functionIndex - 2);                    /* L: f ... f_id id_r f */
        lua_pushinteger(L, functionId);                         /* L: f ... f_id id_r f id */
        lua_rawset(L, -4);                        /* f_id[f] = id, L: f ... f_id id_r */
        lua_pushinteger(L, functionId);                         /* L: f ... f_id id_r id */
    }
    else
    {
        functionId = lua_tonumber(L, -1);
    }

    // get function retain
    lua_pushvalue(L, -1);                                       /* L: f ... f_id id_r id id */
    lua_rawget(L, -3);                                          /* L: f ... f_id id_r id r */
    int retainCount = 1;
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        // first retain, set retain count = 1
        lua_pop(L, 1);
        lua_pushinteger(L, retainCount);
    }
    else
    {
        // add retain count
        retainCount = lua_tonumber(L, -1);
        retainCount++;
        lua_pop(L, 1);
        lua_pushinteger(L, retainCount);
    }

    lua_rawset(L, -3);                            /* id_r[id] = r, L: f ... f_id id_r */
    lua_pop(L, 2);                                              /* L: f ... */

    if (retainCountReturn) *retainCountReturn = retainCount;
    return functionId;
}

/*
args:
    -6  const char *className
    -5  const char *methodName
    -4  const char *methodSig
    -3  const char *argsType
    -2  int         retType
    -1  LUA_TABLE   args
*/
int checkParameters(lua_State *L, LuaJavaBridge_CallInfo *call)
{
    memset(call, 0, sizeof(call));

    if (!lua_isstring(L, -6)
            || !lua_isstring(L, -5)
            || !lua_isstring(L, -4)
            || !lua_isstring(L, -3)
            || !lua_isnumber(L, -2)
            || !lua_istable(L, -1))
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, LUAJ_ERR_INVALID_PARAMETERS);
        return 2;
    }

    // check java method
    const char *className  = lua_tostring(L, -6);
    const char *methodName = lua_tostring(L, -5);
    const char *methodSig  = lua_tostring(L, -4);

    if (getMethodInfo(call, className, methodName, methodSig) != 0)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, LUAJ_ERR_METHOD_NOT_FOUND);
        return 2;
    }

    call->setArgsType(lua_tostring(L, -3));
    call->retType = lua_tonumber(L, -2);

    if (call->retType == LUAJ_TYPE_NOT_SUPPORT)
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, LUAJ_TYPE_NOT_SUPPORT);
        return 2;
    }

    return 0;
}

int callAndPushReturnValue(lua_State *L, LuaJavaBridge_CallInfo *call, jvalue *args)
{
    JNIEnv *env = call->env;

    if (!args)
    {
        switch (call->retType)
        {
            case LUAJ_TYPE_VOID:
                env->CallStaticVoidMethod(call->classID, call->methodID);
                break;

            case LUAJ_TYPE_INT:
                call->ret.intValue = env->CallStaticIntMethod(call->classID, call->methodID);
                break;

            case LUAJ_TYPE_FLOAT:
                call->ret.floatValue = env->CallStaticFloatMethod(call->classID, call->methodID);
                break;

            case LUAJ_TYPE_BOOLEAN:
                call->ret.boolValue = env->CallStaticBooleanMethod(call->classID, call->methodID);
                break;

            case LUAJ_TYPE_STRING:
                call->retjs = (jstring)env->CallStaticObjectMethod(call->classID, call->methodID);
                call->ret.stringValue = env->GetStringUTFChars(call->retjs, 0);
               break;
        }
    }
    else
    {
        switch (call->retType)
        {
            case LUAJ_TYPE_VOID:
                env->CallStaticVoidMethodA(call->classID, call->methodID, args);
                break;

            case LUAJ_TYPE_INT:
                call->ret.intValue = env->CallStaticIntMethodA(call->classID, call->methodID, args);
                break;

            case LUAJ_TYPE_FLOAT:
                call->ret.floatValue = env->CallStaticFloatMethodA(call->classID, call->methodID, args);
                break;

            case LUAJ_TYPE_BOOLEAN:
                call->ret.boolValue = env->CallStaticBooleanMethodA(call->classID, call->methodID, args);
                break;

            case LUAJ_TYPE_STRING:
                call->retjs = (jstring)env->CallStaticObjectMethodA(call->classID, call->methodID, args);
                call->ret.stringValue = env->GetStringUTFChars(call->retjs, 0);
               break;
        }
    }

    if (env->ExceptionCheck() == JNI_TRUE)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();

        if (call->retjs)
        {
            env->ReleaseStringUTFChars(call->retjs, call->ret.stringValue);
        }

        lua_pushboolean(L, 0);
        lua_pushinteger(L, LUAJ_ERR_EXCEPTION_OCCURRED);
        return 2;
    }

    lua_pushboolean(L, 1);
    switch (call->retType)
    {
        case LUAJ_TYPE_INT:
            lua_pushinteger(L, call->ret.intValue);
            break;

        case LUAJ_TYPE_FLOAT:
            lua_pushnumber(L, call->ret.floatValue);
            break;

        case LUAJ_TYPE_BOOLEAN:
            lua_pushboolean(L, call->ret.boolValue);
            break;

        case LUAJ_TYPE_STRING:
            lua_pushstring(L, call->ret.stringValue);
            env->ReleaseStringUTFChars(call->retjs, call->ret.stringValue);
           break;

        case LUAJ_TYPE_VOID:
        default:
            lua_pushnil(L);
    }
    return 2;
}

int getMethodInfo(LuaJavaBridge_CallInfo *call, const char *className, const char *methodName, const char *methodSig)
{
    jmethodID methodID = 0;
    JNIEnv *env = 0;

    jint ret = s_jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
    switch (ret) {
        case JNI_OK:
            break;

        case JNI_EDETACHED :
            if (s_jvm->AttachCurrentThread(&env, NULL) < 0)
            {
                LOGD("Failed to get the environment using AttachCurrentThread()");
                return -1;
            }
            break;

        case JNI_EVERSION :
            LOGD("JNI interface version 1.4 not supported");
        default :
            LOGD("Failed to get the environment using GetEnv()");
            return -1;
    }

    jclass classID = env->FindClass(className);
    methodID = env->GetStaticMethodID(classID, methodName, methodSig);
    if (!methodID)
    {
        env->ExceptionClear();
        LOGD("Failed to find method id of %s.%s %s", className, methodName, methodSig);
        return -1;
    }

    call->env      = env;
    call->classID  = classID;
    call->methodID = methodID;

    return 0;
}

int checkArgsType(const char typeChar)
{
    switch (typeChar)
    {
        case LUAJ_TYPE_INT_CHAR:
            return LUAJ_TYPE_INT;

        case LUAJ_TYPE_FLOAT_CHAR:
            return LUAJ_TYPE_FLOAT;

        case LUAJ_TYPE_BOOLEAN_CHAR:
            return LUAJ_TYPE_BOOLEAN;

        case LUAJ_TYPE_FUNCTION_CHAR:
            return LUAJ_TYPE_FUNCTION;

        default:
            return LUAJ_TYPE_STRING;
    }
}

int fetchArrayElements(lua_State *L, int index)
{
    int count = 0;
    do
    {
        lua_rawgeti(L, index - count, count + 1);
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            break;
        }
        ++count;
    } while (1);
    return count;
}

} // extern "C"
