/*
** Lua binding: ExtensionsAssetsManager
** Generated automatically by tolua++-1.0.92 on Wed Oct 22 01:19:15 2014.
*/

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

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

/* Exported function */
TOLUA_API int  tolua_ExtensionsAssetsManager_open (lua_State* tolua_S);

#include "cocos-ext.h"
using namespace cocos2d::extension;
using namespace std;
#include "AssetsManager/AssetsManager.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_AssetsManager (lua_State* tolua_S)
{
 AssetsManager* self = (AssetsManager*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 
 tolua_usertype(tolua_S,"AssetsManager");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(AssetsManager)), "AssetsManager");
}

/* method: new of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_new00
static int tolua_ExtensionsAssetsManager_AssetsManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* packageUrl = ((const char*)  tolua_tostring(tolua_S,2,NULL));
  const char* versionFileUrl = ((const char*)  tolua_tostring(tolua_S,3,NULL));
  const char* storagePath = ((const char*)  tolua_tostring(tolua_S,4,NULL));
  {
   AssetsManager* tolua_ret = (AssetsManager*)  Mtolua_new((AssetsManager)(packageUrl,versionFileUrl,storagePath));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AssetsManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_new00_local
static int tolua_ExtensionsAssetsManager_AssetsManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* packageUrl = ((const char*)  tolua_tostring(tolua_S,2,NULL));
  const char* versionFileUrl = ((const char*)  tolua_tostring(tolua_S,3,NULL));
  const char* storagePath = ((const char*)  tolua_tostring(tolua_S,4,NULL));
  {
   AssetsManager* tolua_ret = (AssetsManager*)  Mtolua_new((AssetsManager)(packageUrl,versionFileUrl,storagePath));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AssetsManager");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_delete00
static int tolua_ExtensionsAssetsManager_AssetsManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkUpdate of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_checkUpdate00
static int tolua_ExtensionsAssetsManager_AssetsManager_checkUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkUpdate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkUpdate();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_update00
static int tolua_ExtensionsAssetsManager_AssetsManager_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPackageUrl of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_getPackageUrl00
static int tolua_ExtensionsAssetsManager_AssetsManager_getPackageUrl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPackageUrl'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getPackageUrl();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPackageUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPackageUrl of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_setPackageUrl00
static int tolua_ExtensionsAssetsManager_AssetsManager_setPackageUrl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
  const char* packageUrl = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPackageUrl'", NULL);
#endif
  {
   self->setPackageUrl(packageUrl);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPackageUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVersionFileUrl of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_getVersionFileUrl00
static int tolua_ExtensionsAssetsManager_AssetsManager_getVersionFileUrl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersionFileUrl'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getVersionFileUrl();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVersionFileUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVersionFileUrl of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_setVersionFileUrl00
static int tolua_ExtensionsAssetsManager_AssetsManager_setVersionFileUrl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
  const char* versionFileUrl = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVersionFileUrl'", NULL);
#endif
  {
   self->setVersionFileUrl(versionFileUrl);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVersionFileUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVersion of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_getVersion00
static int tolua_ExtensionsAssetsManager_AssetsManager_getVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersion'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getVersion();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: deleteVersion of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_deleteVersion00
static int tolua_ExtensionsAssetsManager_AssetsManager_deleteVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'deleteVersion'", NULL);
#endif
  {
   self->deleteVersion();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'deleteVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStoragePath of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_getStoragePath00
static int tolua_ExtensionsAssetsManager_AssetsManager_getStoragePath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStoragePath'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getStoragePath();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStoragePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStoragePath of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_setStoragePath00
static int tolua_ExtensionsAssetsManager_AssetsManager_setStoragePath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
  const char* storagePath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStoragePath'", NULL);
#endif
  {
   self->setStoragePath(storagePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStoragePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setConnectionTimeout of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_setConnectionTimeout00
static int tolua_ExtensionsAssetsManager_AssetsManager_setConnectionTimeout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int timeout = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setConnectionTimeout'", NULL);
#endif
  {
   self->setConnectionTimeout(timeout);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setConnectionTimeout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getConnectionTimeout of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_getConnectionTimeout00
static int tolua_ExtensionsAssetsManager_AssetsManager_getConnectionTimeout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getConnectionTimeout'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getConnectionTimeout();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getConnectionTimeout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptHandler of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_registerScriptHandler00
static int tolua_ExtensionsAssetsManager_AssetsManager_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptHandler'", NULL);
#endif
  {
   self->registerScriptHandler(handler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptHandler of class  AssetsManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsAssetsManager_AssetsManager_unregisterScriptHandler00
static int tolua_ExtensionsAssetsManager_AssetsManager_unregisterScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AssetsManager* self = (AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptHandler'", NULL);
#endif
  {
   self->unregisterScriptHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ExtensionsAssetsManager_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"AssetsManager","AssetsManager","",tolua_collect_AssetsManager);
  #else
  tolua_cclass(tolua_S,"AssetsManager","AssetsManager","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"AssetsManager");
   tolua_function(tolua_S,"new",tolua_ExtensionsAssetsManager_AssetsManager_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsAssetsManager_AssetsManager_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsAssetsManager_AssetsManager_new00_local);
   tolua_function(tolua_S,"delete",tolua_ExtensionsAssetsManager_AssetsManager_delete00);
   tolua_function(tolua_S,"checkUpdate",tolua_ExtensionsAssetsManager_AssetsManager_checkUpdate00);
   tolua_function(tolua_S,"update",tolua_ExtensionsAssetsManager_AssetsManager_update00);
   tolua_function(tolua_S,"getPackageUrl",tolua_ExtensionsAssetsManager_AssetsManager_getPackageUrl00);
   tolua_function(tolua_S,"setPackageUrl",tolua_ExtensionsAssetsManager_AssetsManager_setPackageUrl00);
   tolua_function(tolua_S,"getVersionFileUrl",tolua_ExtensionsAssetsManager_AssetsManager_getVersionFileUrl00);
   tolua_function(tolua_S,"setVersionFileUrl",tolua_ExtensionsAssetsManager_AssetsManager_setVersionFileUrl00);
   tolua_function(tolua_S,"getVersion",tolua_ExtensionsAssetsManager_AssetsManager_getVersion00);
   tolua_function(tolua_S,"deleteVersion",tolua_ExtensionsAssetsManager_AssetsManager_deleteVersion00);
   tolua_function(tolua_S,"getStoragePath",tolua_ExtensionsAssetsManager_AssetsManager_getStoragePath00);
   tolua_function(tolua_S,"setStoragePath",tolua_ExtensionsAssetsManager_AssetsManager_setStoragePath00);
   tolua_function(tolua_S,"setConnectionTimeout",tolua_ExtensionsAssetsManager_AssetsManager_setConnectionTimeout00);
   tolua_function(tolua_S,"getConnectionTimeout",tolua_ExtensionsAssetsManager_AssetsManager_getConnectionTimeout00);
   tolua_function(tolua_S,"registerScriptHandler",tolua_ExtensionsAssetsManager_AssetsManager_registerScriptHandler00);
   tolua_function(tolua_S,"unregisterScriptHandler",tolua_ExtensionsAssetsManager_AssetsManager_unregisterScriptHandler00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ExtensionsAssetsManager (lua_State* tolua_S) {
 return tolua_ExtensionsAssetsManager_open(tolua_S);
};
#endif

