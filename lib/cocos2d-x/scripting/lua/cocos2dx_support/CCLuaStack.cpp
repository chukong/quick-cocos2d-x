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

#include "LuaCocos2d.h"
#include "platform/CCZipFile.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/ios/CCLuaObjcBridge.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Cocos2dxLuaLoader.h"
#endif

#include <string>

NS_CC_BEGIN

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
    m_state = lua_open();
    luaL_openlibs(m_state);
    tolua_Cocos2d_open(m_state);
    toluafix_open(m_state);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    CCLuaObjcBridge::luaopen_luaoc(m_state);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    addLuaLoader(loader_Android);
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
    for (int i = lua_objlen(m_state, -2) + 1; i > 2; --i)
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
    ++m_callFromLua;
    int nRet = luaL_dofile(m_state, filename);
    --m_callFromLua;
    CC_ASSERT(m_callFromLua >= 0);
    // lua_gc(m_state, LUA_GCCOLLECT, 0);
    
    if (nRet != 0)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, -1));
        lua_pop(m_state, 1);
        return nRet;
    }
    return 0;
#endif
}

int CCLuaStack::executeGlobalFunction(const char* functionName)
{
    lua_getglobal(m_state, functionName);       /* query function by name, stack: function */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", functionName);
        lua_pop(m_state, 1);
        return 0;
    }
    return executeFunction(0);
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

int CCLuaStack::executeFunction(int numArgs)
{
    int functionIndex = -(numArgs + 1);
    if (!lua_isfunction(m_state, functionIndex))
    {
        CCLOG("value at stack [%d] is not function", functionIndex);
        lua_pop(m_state, numArgs + 1); // remove function and arguments
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
    error = lua_pcall(m_state, numArgs, 1, traceback);                  /* L: ... [G] ret */
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
    
    // get return value
    int ret = 0;
    if (lua_isnumber(m_state, -1))
    {
        ret = lua_tointeger(m_state, -1);
    }
    else if (lua_isboolean(m_state, -1))
    {
        ret = lua_toboolean(m_state, -1);
    }
    // remove return value from stack
    lua_pop(m_state, 1);                                                /* L: ... [G] */
    
    if (traceback)
    {
        lua_pop(m_state, 1); // remove __G__TRACKBACK__ from stack      /* L: ... */
    }
    
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

bool CCLuaStack::executeAssert(bool cond, const char *msg)
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
    lua_call(L, 0, 1);
    return 1;
}

int CCLuaStack::lua_print(lua_State *L)
{
    int nargs = lua_gettop(L);

    std::string t;
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
            t += "\t";
    }
    CCLOG("[LUA-print] %s", t.c_str());

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
        string tmpFilePath = utils->getWriteablePath().append("cc_load_chunks.tmp");
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
            
            CCLOG("CCLoadChunksFromZip() - began");
            int count = 0;
            string filename = zip->getFirstFilename();
            while (filename.length())
            {
                unsigned long bufferSize = 0;
                unsigned char *buffer = zip->getFileData(filename.c_str(), &bufferSize);
                if (bufferSize)
                {
                    luaL_loadbuffer(L, (char*)buffer, bufferSize, filename.c_str());
                    lua_pushcclosure(L, &cc_lua_require, 1);
                    lua_setfield(L, -2, filename.c_str());
                    delete []buffer;
                    ++count;
                    // CCLOG("CCLoadChunksFromZip() - chunk %s", filename.c_str());
                }
                filename = zip->getNextFilename();
            }
            
            CCLOG("CCLoadChunksFromZip() - ended, chunks count %d", count);
            
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

NS_CC_END
