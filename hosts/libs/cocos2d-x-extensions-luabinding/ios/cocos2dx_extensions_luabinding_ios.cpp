/*
** Lua binding: cocos2dx_extensions_luabinding_ios
** Generated automatically by tolua++-1.0.92 on Wed Dec 26 11:08:44 2012.
*/

#include "cocos2dx_extensions_luabinding_ios.h"



#include "CCScale9Sprite.h"
#include "CCEditBox.h"
using namespace cocos2d::extension;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ccColor3B (lua_State* tolua_S)
{
 ccColor3B* self = (ccColor3B*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"CCString");
 tolua_usertype(tolua_S,"CCControl");
 tolua_usertype(tolua_S,"CCEditBox");
 tolua_usertype(tolua_S,"CCControlButton");
 tolua_usertype(tolua_S,"CCScale9Sprite");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"ccColor3B");
 
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCSpriteFrame");
 tolua_usertype(tolua_S,"CCRect");
}

/* method: create of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_create00
static int tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_create00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_create01
static int tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_create01(lua_State* tolua_S)
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
 return tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrame of class  CCScale9Sprite */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_createWithSpriteFrame00
static int tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_createWithSpriteFrame00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_createWithSpriteFrameName00
static int tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_createWithSpriteFrameName00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_setContentSize00
static int tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_setContentSize00(lua_State* tolua_S)
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

/* method: getState of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControl_getState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControl_getState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getState'", NULL);
#endif
  {
   CCControlState tolua_ret = (CCControlState)  self->getState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEnabled of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControl_setEnabled00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControl_setEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  bool bEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEnabled'", NULL);
#endif
  {
   self->setEnabled(bEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEnabled of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControl_isEnabled00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControl_isEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSelected of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControl_setSelected00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControl_setSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  bool bSelected = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSelected'", NULL);
#endif
  {
   self->setSelected(bSelected);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSelected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isSelected of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControl_isSelected00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControl_isSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isSelected'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isSelected();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isSelected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHighlighted of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControl_setHighlighted00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControl_setHighlighted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
  bool bHighlighted = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHighlighted'", NULL);
#endif
  {
   self->setHighlighted(bHighlighted);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHighlighted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isHighlighted of class  CCControl */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControl_isHighlighted00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControl_isHighlighted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControl* self = (CCControl*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isHighlighted'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isHighlighted();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isHighlighted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVerticalMargin of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getVerticalMargin00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getVerticalMargin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVerticalMargin'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getVerticalMargin();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVerticalMargin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHorizontalOrigin of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getHorizontalOrigin00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getHorizontalOrigin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHorizontalOrigin'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getHorizontalOrigin();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHorizontalOrigin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMargins of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setMargins00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setMargins00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  int marginH = ((int)  tolua_tonumber(tolua_S,2,0));
  int marginV = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMargins'", NULL);
#endif
  {
   self->setMargins(marginH,marginV);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMargins'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* label = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCScale9Sprite* backgroundSprite = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,3,0));
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::create(label,backgroundSprite);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCControlButton");
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

/* method: create of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create01
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  std::string title = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,3,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::create(title,fontName,fontSize);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCControlButton");
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create02
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCScale9Sprite* sprite = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
  {
   CCControlButton* tolua_ret = (CCControlButton*)  CCControlButton::create(sprite);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCControlButton");
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleForState'", NULL);
#endif
  {
   CCString* tolua_ret = (CCString*)  self->getTitleForState(state);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCString");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCString* title = ((CCString*)  tolua_tousertype(tolua_S,2,0));
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleForState'", NULL);
#endif
  {
   self->setTitleForState(title,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleColorForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleColorForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleColorForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleColorForState'", NULL);
#endif
  {
   const ccColor3B tolua_ret = (const ccColor3B)  self->getTitleColorForState(state);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccColor3B)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const ccColor3B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const ccColor3B));
     tolua_pushusertype(tolua_S,tolua_obj,"const ccColor3B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleColorForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleColorForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleColorForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleColorForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3B",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  ccColor3B color = *((ccColor3B*)  tolua_tousertype(tolua_S,2,0));
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleColorForState'", NULL);
#endif
  {
   self->setTitleColorForState(color,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleColorForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleLabelForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleLabelForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleLabelForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleLabelForState'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getTitleLabelForState(state);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleLabelForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleLabelForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleLabelForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleLabelForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCNode* label = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleLabelForState'", NULL);
#endif
  {
   self->setTitleLabelForState(label,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleLabelForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleTTFForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleTTFForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleTTFForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  const char* fntFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleTTFForState'", NULL);
#endif
  {
   self->setTitleTTFForState(fntFile,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleTTFForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleTTFForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleTTFForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleTTFForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleTTFForState'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getTitleTTFForState(state);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleTTFForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleTTFSizeForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleTTFSizeForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleTTFSizeForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  float size = ((float)  tolua_tonumber(tolua_S,2,0));
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleTTFSizeForState'", NULL);
#endif
  {
   self->setTitleTTFSizeForState(size,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleTTFSizeForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleTTFSizeForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleTTFSizeForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleTTFSizeForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleTTFSizeForState'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getTitleTTFSizeForState(state);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleTTFSizeForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTitleBMFontForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleBMFontForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleBMFontForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  const char* fntFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTitleBMFontForState'", NULL);
#endif
  {
   self->setTitleBMFontForState(fntFile,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTitleBMFontForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTitleBMFontForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleBMFontForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleBMFontForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTitleBMFontForState'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getTitleBMFontForState(state);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTitleBMFontForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBackgroundSpriteForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getBackgroundSpriteForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getBackgroundSpriteForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBackgroundSpriteForState'", NULL);
#endif
  {
   CCScale9Sprite* tolua_ret = (CCScale9Sprite*)  self->getBackgroundSpriteForState(state);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScale9Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBackgroundSpriteForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundSpriteForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setBackgroundSpriteForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setBackgroundSpriteForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCScale9Sprite* sprite = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,2,0));
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundSpriteForState'", NULL);
#endif
  {
   self->setBackgroundSpriteForState(sprite,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundSpriteForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBackgroundSpriteFrameForState of class  CCControlButton */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setBackgroundSpriteFrameForState00
static int tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setBackgroundSpriteFrameForState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCControlButton* self = (CCControlButton*)  tolua_tousertype(tolua_S,1,0);
  CCSpriteFrame* spriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  CCControlState state = ((CCControlState) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBackgroundSpriteFrameForState'", NULL);
#endif
  {
   self->setBackgroundSpriteFrameForState(spriteFrame,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBackgroundSpriteFrameForState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_create00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"CCScale9Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCScale9Sprite",1,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCScale9Sprite",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
  CCScale9Sprite* pNormal9SpriteBg = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,3,0));
  CCScale9Sprite* pPressed9SpriteBg = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,4,NULL));
  CCScale9Sprite* pDisabled9SpriteBg = ((CCScale9Sprite*)  tolua_tousertype(tolua_S,5,NULL));
  {
   CCEditBox* tolua_ret = (CCEditBox*)  CCEditBox::create(*size,pNormal9SpriteBg,pPressed9SpriteBg,pDisabled9SpriteBg);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCEditBox");
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

/* method: registerScriptEditboxHandler of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_registerScriptEditboxHandler00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_registerScriptEditboxHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptEditboxHandler'", NULL);
#endif
  {
   self->registerScriptEditboxHandler(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptEditboxHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptEditboxHandler of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_unregisterScriptEditboxHandler00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_unregisterScriptEditboxHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptEditboxHandler'", NULL);
#endif
  {
   self->unregisterScriptEditboxHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterScriptEditboxHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setText00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  const char* pText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(pText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getText of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_getText00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_getText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getText'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getText();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFontColor of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setFontColor00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setFontColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFontColor'", NULL);
#endif
  {
   self->setFontColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFontColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlaceholderFontColor of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setPlaceholderFontColor00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setPlaceholderFontColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlaceholderFontColor'", NULL);
#endif
  {
   self->setPlaceholderFontColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlaceholderFontColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPlaceHolder of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setPlaceHolder00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  const char* pText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPlaceHolder'", NULL);
#endif
  {
   self->setPlaceHolder(pText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPlaceHolder of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_getPlaceHolder00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_getPlaceHolder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPlaceHolder'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getPlaceHolder();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPlaceHolder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInputMode of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setInputMode00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setInputMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  EditBoxInputMode inputMode = ((EditBoxInputMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInputMode'", NULL);
#endif
  {
   self->setInputMode(inputMode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInputMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxLength of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setMaxLength00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  int maxLength = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxLength'", NULL);
#endif
  {
   self->setMaxLength(maxLength);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxLength of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_getMaxLength00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_getMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxLength'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInputFlag of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setInputFlag00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setInputFlag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  EditBoxInputFlag inputFlag = ((EditBoxInputFlag) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInputFlag'", NULL);
#endif
  {
   self->setInputFlag(inputFlag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInputFlag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setReturnType of class  CCEditBox */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setReturnType00
static int tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setReturnType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCEditBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEditBox* self = (CCEditBox*)  tolua_tousertype(tolua_S,1,0);
  KeyboardReturnType returnType = ((KeyboardReturnType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setReturnType'", NULL);
#endif
  {
   self->setReturnType(returnType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setReturnType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_cocos2dx_extensions_luabinding_ios_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CCScale9Sprite","CCScale9Sprite","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCScale9Sprite");
   tolua_function(tolua_S,"create",tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_create00);
   tolua_function(tolua_S,"create",tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_create01);
   tolua_function(tolua_S,"createWithSpriteFrame",tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_createWithSpriteFrame00);
   tolua_function(tolua_S,"createWithSpriteFrameName",tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_createWithSpriteFrameName00);
   tolua_function(tolua_S,"setContentSize",tolua_cocos2dx_extensions_luabinding_ios_CCScale9Sprite_setContentSize00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"CCControlStateNormal",CCControlStateNormal);
  tolua_constant(tolua_S,"CCControlStateHighlighted",CCControlStateHighlighted);
  tolua_constant(tolua_S,"CCControlStateDisabled",CCControlStateDisabled);
  tolua_constant(tolua_S,"CCControlStateSelected",CCControlStateSelected);
  tolua_cclass(tolua_S,"CCControl","CCControl","CCLayer",NULL);
  tolua_beginmodule(tolua_S,"CCControl");
   tolua_function(tolua_S,"getState",tolua_cocos2dx_extensions_luabinding_ios_CCControl_getState00);
   tolua_function(tolua_S,"setEnabled",tolua_cocos2dx_extensions_luabinding_ios_CCControl_setEnabled00);
   tolua_function(tolua_S,"isEnabled",tolua_cocos2dx_extensions_luabinding_ios_CCControl_isEnabled00);
   tolua_function(tolua_S,"setSelected",tolua_cocos2dx_extensions_luabinding_ios_CCControl_setSelected00);
   tolua_function(tolua_S,"isSelected",tolua_cocos2dx_extensions_luabinding_ios_CCControl_isSelected00);
   tolua_function(tolua_S,"setHighlighted",tolua_cocos2dx_extensions_luabinding_ios_CCControl_setHighlighted00);
   tolua_function(tolua_S,"isHighlighted",tolua_cocos2dx_extensions_luabinding_ios_CCControl_isHighlighted00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCControlButton","CCControlButton","CCControl",NULL);
  tolua_beginmodule(tolua_S,"CCControlButton");
   tolua_function(tolua_S,"getVerticalMargin",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getVerticalMargin00);
   tolua_function(tolua_S,"getHorizontalOrigin",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getHorizontalOrigin00);
   tolua_function(tolua_S,"setMargins",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setMargins00);
   tolua_function(tolua_S,"create",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create00);
   tolua_function(tolua_S,"create",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create01);
   tolua_function(tolua_S,"create",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_create02);
   tolua_function(tolua_S,"getTitleForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleForState00);
   tolua_function(tolua_S,"setTitleForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleForState00);
   tolua_function(tolua_S,"getTitleColorForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleColorForState00);
   tolua_function(tolua_S,"setTitleColorForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleColorForState00);
   tolua_function(tolua_S,"getTitleLabelForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleLabelForState00);
   tolua_function(tolua_S,"setTitleLabelForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleLabelForState00);
   tolua_function(tolua_S,"setTitleTTFForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleTTFForState00);
   tolua_function(tolua_S,"getTitleTTFForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleTTFForState00);
   tolua_function(tolua_S,"setTitleTTFSizeForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleTTFSizeForState00);
   tolua_function(tolua_S,"getTitleTTFSizeForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleTTFSizeForState00);
   tolua_function(tolua_S,"setTitleBMFontForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setTitleBMFontForState00);
   tolua_function(tolua_S,"getTitleBMFontForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getTitleBMFontForState00);
   tolua_function(tolua_S,"getBackgroundSpriteForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_getBackgroundSpriteForState00);
   tolua_function(tolua_S,"setBackgroundSpriteForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setBackgroundSpriteForState00);
   tolua_function(tolua_S,"setBackgroundSpriteFrameForState",tolua_cocos2dx_extensions_luabinding_ios_CCControlButton_setBackgroundSpriteFrameForState00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"kKeyboardReturnTypeDefault",kKeyboardReturnTypeDefault);
  tolua_constant(tolua_S,"kKeyboardReturnTypeDone",kKeyboardReturnTypeDone);
  tolua_constant(tolua_S,"kKeyboardReturnTypeSend",kKeyboardReturnTypeSend);
  tolua_constant(tolua_S,"kKeyboardReturnTypeSearch",kKeyboardReturnTypeSearch);
  tolua_constant(tolua_S,"kKeyboardReturnTypeGo",kKeyboardReturnTypeGo);
  tolua_constant(tolua_S,"kEditBoxInputModeAny",kEditBoxInputModeAny);
  tolua_constant(tolua_S,"kEditBoxInputModeEmailAddr",kEditBoxInputModeEmailAddr);
  tolua_constant(tolua_S,"kEditBoxInputModeNumeric",kEditBoxInputModeNumeric);
  tolua_constant(tolua_S,"kEditBoxInputModePhoneNumber",kEditBoxInputModePhoneNumber);
  tolua_constant(tolua_S,"kEditBoxInputModeUrl",kEditBoxInputModeUrl);
  tolua_constant(tolua_S,"kEditBoxInputModeDecimal",kEditBoxInputModeDecimal);
  tolua_constant(tolua_S,"kEditBoxInputModeSingleLine",kEditBoxInputModeSingleLine);
  tolua_constant(tolua_S,"kEditBoxInputFlagPassword",kEditBoxInputFlagPassword);
  tolua_constant(tolua_S,"kEditBoxInputFlagSensitive",kEditBoxInputFlagSensitive);
  tolua_constant(tolua_S,"kEditBoxInputFlagInitialCapsWord",kEditBoxInputFlagInitialCapsWord);
  tolua_constant(tolua_S,"kEditBoxInputFlagInitialCapsSentence",kEditBoxInputFlagInitialCapsSentence);
  tolua_constant(tolua_S,"kEditBoxInputFlagInitialCapsAllCharacters",kEditBoxInputFlagInitialCapsAllCharacters);
  tolua_cclass(tolua_S,"CCEditBox","CCEditBox","CCControlButton",NULL);
  tolua_beginmodule(tolua_S,"CCEditBox");
   tolua_function(tolua_S,"create",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_create00);
   tolua_function(tolua_S,"registerScriptEditboxHandler",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_registerScriptEditboxHandler00);
   tolua_function(tolua_S,"unregisterScriptEditboxHandler",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_unregisterScriptEditboxHandler00);
   tolua_function(tolua_S,"setText",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setText00);
   tolua_function(tolua_S,"getText",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_getText00);
   tolua_function(tolua_S,"setFontColor",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setFontColor00);
   tolua_function(tolua_S,"setPlaceholderFontColor",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setPlaceholderFontColor00);
   tolua_function(tolua_S,"setPlaceHolder",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setPlaceHolder00);
   tolua_function(tolua_S,"getPlaceHolder",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_getPlaceHolder00);
   tolua_function(tolua_S,"setInputMode",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setInputMode00);
   tolua_function(tolua_S,"setMaxLength",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setMaxLength00);
   tolua_function(tolua_S,"getMaxLength",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_getMaxLength00);
   tolua_function(tolua_S,"setInputFlag",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setInputFlag00);
   tolua_function(tolua_S,"setReturnType",tolua_cocos2dx_extensions_luabinding_ios_CCEditBox_setReturnType00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_cocos2dx_extensions_luabinding_ios (lua_State* tolua_S) {
 return tolua_cocos2dx_extensions_luabinding_ios_open(tolua_S);
};
#endif

