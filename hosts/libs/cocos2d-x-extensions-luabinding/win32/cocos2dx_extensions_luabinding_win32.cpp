/*
** Lua binding: cocos2dx_extensions_luabinding_win32
** Generated automatically by tolua++-1.0.92 on Wed Dec 26 11:12:00 2012.
*/

#include "cocos2dx_extensions_luabinding_win32.h"



#include "CCScale9Sprite.h"
using namespace cocos2d::extension;

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCScale9Sprite");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"CCRect");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCSpriteFrame");
}

/* method: create of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_create00
static int tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  CCRect capInsets = *((CCRect*)  tolua_tousertype(tolua_S,4,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::create(file,rect,capInsets);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_create01
static int tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::create(file,rect);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrame of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_createWithSpriteFrame00
static int tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_createWithSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSpriteFrame* spriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::createWithSpriteFrame(spriteFrame);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrameName of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_createWithSpriteFrameName00
static int tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_createWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* spriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  CCScale9Sprite::createWithSpriteFrameName(spriteFrameName);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithSpriteFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentSize of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_setContentSize00
static int tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_setContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScale9Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScale9Sprite* self = (CCScale9Sprite*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentSize'", NULL);
#endif
  {
   self->setContentSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_cocos2dx_extensions_luabinding_win32_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CCScale9Sprite","CCScale9Sprite","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCScale9Sprite");
   tolua_function(tolua_S,"create",tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_create00);
   tolua_function(tolua_S,"create",tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_create01);
   tolua_function(tolua_S,"createWithSpriteFrame",tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_createWithSpriteFrame00);
   tolua_function(tolua_S,"createWithSpriteFrameName",tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_createWithSpriteFrameName00);
   tolua_function(tolua_S,"setContentSize",tolua_cocos2dx_extensions_luabinding_win32_CCScale9Sprite_setContentSize00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_cocos2dx_extensions_luabinding_win32 (lua_State* tolua_S) {
 return tolua_cocos2dx_extensions_luabinding_win32_open(tolua_S);
};
#endif

