/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCLuaStack.h"

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua_fix.h"
#include "snapshot.h"
}

#include "ccMacros.h"
#include "LuaCocos2d.h"
#include "platform/CCZipFile.h"
#include "platform/CCFileUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/ios/CCLuaObjcBridge.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Cocos2dxLuaLoader.h"
#include "platform/android/CCLuaJavaBridge.h"
#endif

#include "cocos-ext.h"

#include <string>

using namespace std;

NS_CC_BEGIN

struct cc_timeval CCLuaStack::m_lasttime = {0};

CCLuaStack *CCLuaStack::create(void)
{
    CCLuaStack *stack = new CCLuaStack();
    stack->init();
    stack->autorelease();
    return stack;
}

CCLuaStack *CCLuaStack::attach(lua_State *L)
{
    CCLuaStack *stack = new CCLuaStack();
    stack->initWithLuaState(L);
    stack->autorelease();
    return stack;
}

bool CCLuaStack::init(void)
{
    CCTime::gettimeofdayCocos2d(&m_lasttime, NULL);
    m_state = lua_open();
    CCAssert(m_state, "create Lua VM failed");
    luaL_openlibs(m_state);
    toluafix_open(m_state);
    tolua_Cocos2d_open(m_state);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    CCLuaObjcBridge::luaopen_luaoc(m_state);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    addLuaLoader(cocos2dx_lua_loader);
    CCLuaJavaBridge::luaopen_luaj(m_state);
#endif

    // register lua print
    lua_pushcfunction(m_state, lua_print);
    lua_setglobal(m_state, "print");

    // register CCLuaLoadChunksFromZip
    lua_pushcfunction(m_state, lua_loadChunksFromZip);
    lua_setglobal(m_state, "CCLuaLoadChunksFromZip");
    lua_pushcfunction(m_state, lua_loadChunksFromZip);
    lua_setglobal(m_state, "CCLuaLoadChunksFromZIP");

    // faster value type check
    lua_pushcfunction(m_state, lua_typen);
    lua_setglobal(m_state, "typen");
    lua_pushinteger(m_state, LUA_TNIL);
    lua_setglobal(m_state, "LUA_TNIL");
    lua_pushinteger(m_state, 1);
    lua_setglobal(m_state, "LUA_TBOOLEAN");
    lua_pushinteger(m_state, 2);
    lua_setglobal(m_state, "LUA_TLIGHTUSERDATA");
    lua_pushinteger(m_state, 3);
    lua_setglobal(m_state, "LUA_TNUMBER");
    lua_pushinteger(m_state, 4);
    lua_setglobal(m_state, "LUA_TSTRING");
    lua_pushinteger(m_state, 5);
    lua_setglobal(m_state, "LUA_TTABLE");
    lua_pushinteger(m_state, 6);
    lua_setglobal(m_state, "LUA_TFUNCTION");
    lua_pushinteger(m_state, 7);
    lua_setglobal(m_state, "LUA_TUSERDATA");
    lua_pushinteger(m_state, 8);
    lua_setglobal(m_state, "LUA_TTHREAD");

    // register CCLuaStackSnapshot
    luaopen_snapshot(m_state);

    return true;
}

bool CCLuaStack::initWithLuaState(lua_State *L)
{
    m_state = L;
    return true;
}

void CCLuaStack::addSearchPath(const char* path)
{
    lua_getglobal(m_state, "package");                                  /* L: package */
    lua_getfield(m_state, -1, "path");                /* get package.path, L: package path */
    const char* cur_path =  lua_tostring(m_state, -1);
    lua_pushfstring(m_state, "%s;%s/?.lua", cur_path, path);            /* L: package path newpath */
    lua_setfield(m_state, -3, "path");          /* package.path = newpath, L: package path */
    lua_pop(m_state, 2);                                                /* L: - */
}

void CCLuaStack::addLuaLoader(lua_CFunction func)
{
    if (!func) return;

    lua_getglobal(m_state, "package");                                  /* L: package */
    lua_getfield(m_state, -1, "loaders");                               /* L: package, loaders */
    lua_pushcfunction(m_state, func);                                   /* L: package, loaders, func */
    for (int i = (int)lua_objlen(m_state, -2) + 1; i > 2; --i)
    {
        lua_rawgeti(m_state, -2, i - 1);                                /* L: package, loaders, func, function */
        lua_rawseti(m_state, -3, i);                                    /* L: package, loaders, func */
    }
    lua_rawseti(m_state, -2, 2);                                        /* L: package, loaders */
    lua_setfield(m_state, -2, "loaders");                               /* L: package */

    lua_pop(m_state, 1);
}

void CCLuaStack::removeScriptObjectByCCObject(CCObject* pObj)
{
    toluafix_remove_ccobject_by_refid(m_state, pObj->m_nLuaID);
}

void CCLuaStack::removeScriptHandler(int nHandler)
{
    toluafix_remove_function_by_refid(m_state, nHandler);
}

int CCLuaStack::executeString(const char *codes)
{
    luaL_loadstring(m_state, codes);
    return executeFunction(0);
}

int CCLuaStack::executeScriptFile(const char* filename)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string code("require \"");
    code.append(filename);
    code.append("\"");
    return executeString(code.c_str());
#else
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filename);
    luaL_loadfile(m_state, fullPath.c_str());
    return executeFunction(0);
#endif
}

int CCLuaStack::executeGlobalFunction(const char* functionName, int numArgs /* = 0 */)
{
    lua_getglobal(m_state, functionName);       /* query function by name, stack: function */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", functionName);
        lua_pop(m_state, 1);
        return 0;
    }
    return executeFunction(numArgs);
}

void CCLuaStack::clean(void)
{
    lua_settop(m_state, 0);
}

void CCLuaStack::pushInt(int intValue)
{
    lua_pushinteger(m_state, intValue);
}

void CCLuaStack::pushFloat(float floatValue)
{
    lua_pushnumber(m_state, floatValue);
}

void CCLuaStack::pushBoolean(bool boolValue)
{
    lua_pushboolean(m_state, boolValue);
}

void CCLuaStack::pushString(const char* stringValue)
{
    lua_pushstring(m_state, stringValue);
}

void CCLuaStack::pushString(const char* stringValue, int length)
{
    lua_pushlstring(m_state, stringValue, length);
}

void CCLuaStack::pushNil(void)
{
    lua_pushnil(m_state);
}

void CCLuaStack::pushCCObject(CCObject* objectValue, const char* typeName)
{
    toluafix_pushusertype_ccobject(m_state, objectValue->m_uID, &objectValue->m_nLuaID, objectValue, typeName);
}

void CCLuaStack::pushCCLuaValue(const CCLuaValue& value)
{
    const CCLuaValueType type = value.getType();
    if (type == CCLuaValueTypeInt)
    {
        return pushInt(value.intValue());
    }
    else if (type == CCLuaValueTypeFloat)
    {
        return pushFloat(value.floatValue());
    }
    else if (type == CCLuaValueTypeBoolean)
    {
        return pushBoolean(value.booleanValue());
    }
    else if (type == CCLuaValueTypeString)
    {
        return pushString(value.stringValue().c_str());
    }
    else if (type == CCLuaValueTypeDict)
    {
        pushCCLuaValueDict(value.dictValue());
    }
    else if (type == CCLuaValueTypeArray)
    {
        pushCCLuaValueArray(value.arrayValue());
    }
    else if (type == CCLuaValueTypeCCObject)
    {
        pushCCObject(value.ccobjectValue(), value.getCCObjectTypename().c_str());
    }
}

void CCLuaStack::pushCCLuaValueDict(const CCLuaValueDict& dict)
{
    lua_newtable(m_state);                                              /* L: table */
    for (CCLuaValueDictIterator it = dict.begin(); it != dict.end(); ++it)
    {
        lua_pushstring(m_state, it->first.c_str());                     /* L: table key */
        pushCCLuaValue(it->second);                                     /* L: table key value */
        lua_rawset(m_state, -3);                     /* table.key = value, L: table */
    }
}

void CCLuaStack::pushCCLuaValueArray(const CCLuaValueArray& array)
{
    lua_newtable(m_state);                                              /* L: table */
    int index = 1;
    for (CCLuaValueArrayIterator it = array.begin(); it != array.end(); ++it)
    {
        pushCCLuaValue(*it);                                            /* L: table value */
        lua_rawseti(m_state, -2, index);          /* table[index] = value, L: table */
        ++index;
    }
}

bool CCLuaStack::pushFunctionByHandler(int nHandler)
{
    toluafix_get_function_by_refid(m_state, nHandler);                  /* L: ... func */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", nHandler);
        lua_pop(m_state, 1);
        return false;
    }
    return true;
}

int execute_lua_function(lua_State *L, int numArgs, bool removeResult)
{
    int functionIndex = -(numArgs + 1);
    if (!lua_isfunction(L, functionIndex))
    {
        CCLOG("value at stack [%d] is not function", functionIndex);
        lua_pop(L, numArgs + 1); // remove function and arguments
        return 0;
    }

    int traceback = 0;
    lua_getglobal(L, "__G__TRACKBACK__");                         /* L: ... func arg1 arg2 ... G */
    if (!lua_isfunction(L, -1))
    {
        lua_pop(L, 1);                                            /* L: ... func arg1 arg2 ... */
    }
    else
    {
        lua_insert(L, functionIndex - 1);                         /* L: ... G func arg1 arg2 ... */
        traceback = functionIndex - 1;
    }

    int error = 0;
    error = lua_pcall(L, numArgs, 1, traceback);                  /* L: ... [G] ret */
    if (error)
    {
        if (traceback == 0)
        {
            CCLOG("[LUA ERROR] %s", lua_tostring(L, - 1));        /* L: ... error */
            lua_pop(L, 1); // remove error message from stack
        }
        else                                                            /* L: ... G error */
        {
            lua_pop(L, 2); // remove __G__TRACKBACK__ and error message from stack
        }
        return 0;
    }

    int ret = 0;
    if (removeResult)
    {
        if (lua_isnumber(L, -1))
        {
            ret = (int)lua_tointeger(L, -1);
        }
        else if (lua_isboolean(L, -1))
        {
            ret = lua_toboolean(L, -1);
        }
        // remove return value from stack
        lua_pop(L, 1);                                            /* L: ... [G] */
    }
    else
    {
        ret = 1;
    }

    if (traceback)
    {
        lua_remove(L, removeResult ? -1 : -2);
    }

    return ret;
}

int CCLuaStack::executeFunction(int numArgs)
{
    ++m_callFromLua;
    int ret = execute_lua_function(m_state, numArgs, true);
    --m_callFromLua;
    return ret;
}

int CCLuaStack::executeFunctionByHandler(int nHandler, int numArgs)
{
    int ret = 0;
    if (pushFunctionByHandler(nHandler))                                /* L: ... arg1 arg2 ... func */
    {
        if (numArgs > 0)
        {
            lua_insert(m_state, -(numArgs + 1));                        /* L: ... func arg1 arg2 ... */
        }
        ret = executeFunction(numArgs);
    }
    lua_settop(m_state, 0);
    return ret;
}

bool CCLuaStack::handleAssert(const char *msg)
{
    if (m_callFromLua == 0) return false;

    lua_pushfstring(m_state, "ASSERT FAILED ON LUA EXECUTE: %s", msg ? msg : "unknown");
    lua_error(m_state);
    return true;
}

int CCLuaStack::loadChunksFromZip(const char *zipFilePath)
{
    pushString(zipFilePath);
    lua_loadChunksFromZip(m_state);
    int ret = lua_toboolean(m_state, -1);
    lua_pop(m_state, 1);
    return ret;
}

int cc_lua_require(lua_State *L)
{
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_pushvalue(L, lua_upvalueindex(2));
    return execute_lua_function(L, 1, false);
}

int CCLuaStack::reallocateScriptHandler(int nHandler)
{
    LUA_FUNCTION  nNewHandle = -1;

    if (pushFunctionByHandler(nHandler))
    {
        nNewHandle = toluafix_ref_function(m_state,lua_gettop(m_state),0);
    }
    /*
     toluafix_get_function_by_refid(m_state,nNewHandle);
     if (!lua_isfunction(m_state, -1))
     {
     CCLOG("Error!");
     }
     lua_settop(m_state, 0);
     */
    return nNewHandle;

}

int CCLuaStack::lua_print(lua_State *L)
{
    struct cc_timeval now;

    float deltatime = 0;
    if (CCTime::gettimeofdayCocos2d(&now, NULL) != 0)
    {
        CCLOG("CCLuaStack:lua_print() - error in gettimeofday");
    }
    else
    {
        if (m_lasttime.tv_sec)
        {
            deltatime = now.tv_sec - m_lasttime.tv_sec + (now.tv_usec - m_lasttime.tv_usec) / 1000000.0f;
        }
        else
        {
            m_lasttime = now;
            deltatime = 0;
        }
    }

    int nargs = lua_gettop(L);
    std::string t("[");
    char timestr[32];
    memset(timestr, 0, sizeof(timestr));
    sprintf(timestr, "%.4f", deltatime);
    t += timestr;
    t += "] ";
    for (int i=1; i <= nargs; i++)
    {
        if (lua_istable(L, i))
            t += "table";
        else if (lua_isnone(L, i))
            t += "none";
        else if (lua_isnil(L, i))
            t += "nil";
        else if (lua_isboolean(L, i))
        {
            if (lua_toboolean(L, i) != 0)
                t += "true";
            else
                t += "false";
        }
        else if (lua_isfunction(L, i))
            t += "function";
        else if (lua_islightuserdata(L, i))
            t += "lightuserdata";
        else if (lua_isthread(L, i))
            t += "thread";
        else
        {
            const char * str = lua_tostring(L, i);
            if (str)
                t += lua_tostring(L, i);
            else
                t += lua_typename(L, lua_type(L, i));
        }
        if (i!=nargs)
            t += "  ";
    }
    CCLuaLog(t.c_str());

    return 0;
}

int CCLuaStack::lua_loadChunksFromZip(lua_State *L)
{
    const char *zipFilename = lua_tostring(L, -1);
    CCFileUtils *utils = CCFileUtils::sharedFileUtils();
    string zipFilePath = utils->fullPathForFilename(zipFilename);

    lua_pop(L, 1);
    zipFilename = NULL;

    do
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        string tmpFilePath = utils->getWritablePath().append("cc_load_chunks.tmp");
        unsigned long size = 0;
        unsigned char *buffer = utils->getFileData(zipFilePath.c_str(), "rb", &size);
        bool success = false;
        do
        {
            if (size == 0 || !buffer)
            {
                CCLOG("CCLoadChunksFromZip() - read source file %s failure", zipFilePath.c_str());
                break;
            }

            FILE *tmp = fopen(tmpFilePath.c_str(), "wb");
            if (!tmp)
            {
                CCLOG("CCLoadChunksFromZip() - create tmp file %s failure", tmpFilePath.c_str());
                break;
            }

            success = fwrite(buffer, 1, size, tmp) > 0;
            fclose(tmp);

            if (success)
            {
                zipFilePath = tmpFilePath;
                CCLOG("CCLoadChunksFromZip() - copy zip file to %s ok", tmpFilePath.c_str());
            }
        } while (0);

        if (buffer)
        {
            delete []buffer;
        }

        if (!success)
        {
            lua_pushboolean(L, 0);
            break;
        }
#endif

        CCZipFile *zip = CCZipFile::create(zipFilePath.c_str());
        if (zip)
        {
            CCLOG("CCLoadChunksFromZip() - load zip file: %s", zipFilePath.c_str());
            lua_getglobal(L, "package");
            lua_getfield(L, -1, "preload");

            int count = 0;
            string filename = zip->getFirstFilename();
            while (filename.length())
            {
                unsigned long bufferSize = 0;
                unsigned char *buffer = zip->getFileData(filename.c_str(), &bufferSize);
                if (bufferSize)
                {
                    luaL_loadbuffer(L, (char*)buffer, bufferSize, filename.c_str());
                    lua_setfield(L, -2, filename.c_str());
                    delete []buffer;
                    ++count;
                    // CCLOG("CCLoadChunksFromZip() - chunk %s", filename.c_str());
                }
                filename = zip->getNextFilename();
            }

            CCLOG("CCLoadChunksFromZip() - loaded chunks count: %d", count);

            lua_pop(L, 2);
            lua_pushboolean(L, 1);
        }
        else
        {
            CCLOG("CCLoadChunksFromZip() - not found zip file: %s", zipFilePath.c_str());
            lua_pushboolean(L, 0);
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        unlink(tmpFilePath.c_str());
#endif
    } while (0);
    
    return 1;
}

int CCLuaStack::lua_typen(lua_State *L)
{
    lua_pushinteger(L, lua_type(L, -1));
    return 1;
}

int CCLuaStack::executeFunctionReturnArray(int nHandler,int nNumArgs,int nNummResults,CCArray* pResultArray)
{
    if (NULL == pResultArray)
        return 0;

    if (pushFunctionByHandler(nHandler))                 /* L: ... arg1 arg2 ... func */
    {
        if (nNumArgs > 0)
        {
            lua_insert(m_state, -(nNumArgs + 1));         /* L: ... func arg1 arg2 ... */
            int functionIndex = -(nNumArgs + 1);
            if (!lua_isfunction(m_state, functionIndex))
            {
                CCLOG("value at stack [%d] is not function", functionIndex);
                lua_pop(m_state, nNumArgs + 1); // remove function and arguments
                return 0;
            }

            int traceback = 0;
            lua_getglobal(m_state, "__G__TRACKBACK__");                         /* L: ... func arg1 arg2 ... G */
            if (!lua_isfunction(m_state, -1))
            {
                lua_pop(m_state, 1);                                            /* L: ... func arg1 arg2 ... */
            }
            else
            {
                lua_insert(m_state, functionIndex - 1);                         /* L: ... G func arg1 arg2 ... */
                traceback = functionIndex - 1;
            }

            int error = 0;
            ++m_callFromLua;
            error = lua_pcall(m_state, nNumArgs, nNummResults, traceback);                  /* L: ... [G] ret1 ret2 ... retResults*/
            --m_callFromLua;
            if (error)
            {
                if (traceback == 0)
                {
                    CCLOG("[LUA ERROR] %s", lua_tostring(m_state, - 1));        /* L: ... error */
                    lua_pop(m_state, 1); // remove error message from stack
                }
                else                                                            /* L: ... G error */
                {
                    lua_pop(m_state, 2); // remove __G__TRACKBACK__ and error message from stack
                }
                return 0;
            }

            // get return value,don't pass LUA_MULTRET to numResults,
            if (nNummResults <= 0)
                return 0;

            for (int i = 0 ; i < nNummResults; i++)
            {
                if (lua_type(m_state, -1) == LUA_TBOOLEAN) {

                    bool value = lua_toboolean(m_state, -1);
                    pResultArray->addObject(CCBool::create(value)) ;

                }else if (lua_type(m_state, -1) == LUA_TNUMBER) {

                    double value = lua_tonumber(m_state, -1);
                    pResultArray->addObject(CCDouble::create(value));

                }else if (lua_type(m_state, -1) == LUA_TSTRING) {

                    const char* value = lua_tostring(m_state, -1);
                    pResultArray->addObject(CCString::create(value));

                }else{

                    pResultArray->addObject(static_cast<CCObject*>(tolua_tousertype(m_state, -1, NULL)));
                }
                // remove return value from stack
                lua_pop(m_state, 1);                                                /* L: ... [G] ret1 ret2 ... ret*/
            }
            /* L: ... [G]*/

            if (traceback)
            {
                lua_pop(m_state, 1); // remove __G__TRACKBACK__ from stack      /* L: ... */
            }
        }
    }

    lua_settop(m_state, 0);

    return 1;
}

NS_CC_END
