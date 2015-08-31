/*
** Lua binding: ExtensionsFilters
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
TOLUA_API int  tolua_ExtensionsFilters_open (lua_State* tolua_S);

#include "filters/cocos2dFilters.h"
using namespace cocos2d;
using namespace cocos2d::extension;

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCHBlurFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCHBlurFilter)), "CCHBlurFilter");
 tolua_usertype(tolua_S,"CCTexture2D");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCTexture2D)), "CCTexture2D");
 tolua_usertype(tolua_S,"CCString");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCString)), "CCString");
 tolua_usertype(tolua_S,"CCSharpenFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCSharpenFilter)), "CCSharpenFilter");
 tolua_usertype(tolua_S,"CCContrastFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCContrastFilter)), "CCContrastFilter");
 tolua_usertype(tolua_S,"CCMotionBlurFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCMotionBlurFilter)), "CCMotionBlurFilter");
 tolua_usertype(tolua_S,"CCFilteredSprite");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCFilteredSprite)), "CCFilteredSprite");
 tolua_usertype(tolua_S,"CCBrightnessFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCBrightnessFilter)), "CCBrightnessFilter");
 tolua_usertype(tolua_S,"CCObject");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCObject)), "CCObject");
 tolua_usertype(tolua_S,"CCDropShadowFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCDropShadowFilter)), "CCDropShadowFilter");
 tolua_usertype(tolua_S,"CCFilteredSpriteWithOne");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCFilteredSpriteWithOne)), "CCFilteredSpriteWithOne");
 tolua_usertype(tolua_S,"CCRGBFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCRGBFilter)), "CCRGBFilter");
 tolua_usertype(tolua_S,"CCZoomBlurFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCZoomBlurFilter)), "CCZoomBlurFilter");
 tolua_usertype(tolua_S,"CCVBlurFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCVBlurFilter)), "CCVBlurFilter");
 tolua_usertype(tolua_S,"CCArray");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCArray)), "CCArray");
 tolua_usertype(tolua_S,"CCMaskFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCMaskFilter)), "CCMaskFilter");
 tolua_usertype(tolua_S,"CCExposureFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCExposureFilter)), "CCExposureFilter");
 tolua_usertype(tolua_S,"CCSaturationFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCSaturationFilter)), "CCSaturationFilter");
 tolua_usertype(tolua_S,"CCGrayFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCGrayFilter)), "CCGrayFilter");
 tolua_usertype(tolua_S,"CCBlurBaseFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCBlurBaseFilter)), "CCBlurBaseFilter");
 tolua_usertype(tolua_S,"CCFilteredSpriteWithMulti");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCFilteredSpriteWithMulti)), "CCFilteredSpriteWithMulti");
 tolua_usertype(tolua_S,"CCGammaFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCGammaFilter)), "CCGammaFilter");
 tolua_usertype(tolua_S,"CCHueFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCHueFilter)), "CCHueFilter");
 tolua_usertype(tolua_S,"CCGaussianVBlurFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCGaussianVBlurFilter)), "CCGaussianVBlurFilter");
 tolua_usertype(tolua_S,"CCGaussianHBlurFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCGaussianHBlurFilter)), "CCGaussianHBlurFilter");
 tolua_usertype(tolua_S,"CCSprite");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCSprite)), "CCSprite");
 tolua_usertype(tolua_S,"CCFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCFilter)), "CCFilter");
 tolua_usertype(tolua_S,"CCSingleFloatParamFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCSingleFloatParamFilter)), "CCSingleFloatParamFilter");
 tolua_usertype(tolua_S,"CCRect");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCRect)), "CCRect");
 tolua_usertype(tolua_S,"CCHazeFilter");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCHazeFilter)), "CCHazeFilter");
 tolua_usertype(tolua_S,"CCSpriteFrame");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCSpriteFrame)), "CCSpriteFrame");
}

/* method: getFilter of class  CCFilteredSprite */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSprite_getFilter00
static int tolua_ExtensionsFilters_CCFilteredSprite_getFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFilteredSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFilteredSprite* self = (CCFilteredSprite*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFilter'", NULL);
#endif
  {
   CCFilter* tolua_ret = (CCFilter*)  self->getFilter(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilter");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFilter of class  CCFilteredSprite */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSprite_setFilter00
static int tolua_ExtensionsFilters_CCFilteredSprite_setFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFilteredSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFilteredSprite* self = (CCFilteredSprite*)  tolua_tousertype(tolua_S,1,0);
  CCFilter* pFilter = ((CCFilter*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFilter'", NULL);
#endif
  {
   self->setFilter(pFilter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFilters of class  CCFilteredSprite */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSprite_getFilters00
static int tolua_ExtensionsFilters_CCFilteredSprite_getFilters00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFilteredSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFilteredSprite* self = (CCFilteredSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFilters'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getFilters();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFilters'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFilters of class  CCFilteredSprite */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSprite_setFilters00
static int tolua_ExtensionsFilters_CCFilteredSprite_setFilters00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFilteredSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFilteredSprite* self = (CCFilteredSprite*)  tolua_tousertype(tolua_S,1,0);
  CCArray* pFilters = ((CCArray*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFilters'", NULL);
#endif
  {
   self->setFilters(pFilters);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFilters'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearFilter of class  CCFilteredSprite */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSprite_clearFilter00
static int tolua_ExtensionsFilters_CCFilteredSprite_clearFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFilteredSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFilteredSprite* self = (CCFilteredSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearFilter'", NULL);
#endif
  {
   self->clearFilter();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCFilteredSpriteWithOne */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithOne",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCFilteredSpriteWithOne* tolua_ret = (CCFilteredSpriteWithOne*)  CCFilteredSpriteWithOne::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithOne");
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

/* method: create of class  CCFilteredSpriteWithOne */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create01
static int tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithOne",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCFilteredSpriteWithOne* tolua_ret = (CCFilteredSpriteWithOne*)  CCFilteredSpriteWithOne::create(pszFileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithOne");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCFilteredSpriteWithOne */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create02
static int tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithOne",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const CCRect* rect = ((const CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCFilteredSpriteWithOne* tolua_ret = (CCFilteredSpriteWithOne*)  CCFilteredSpriteWithOne::create(pszFileName,*rect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithOne");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithTexture of class  CCFilteredSpriteWithOne */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithTexture00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithOne",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTexture2D* pTexture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  {
   CCFilteredSpriteWithOne* tolua_ret = (CCFilteredSpriteWithOne*)  CCFilteredSpriteWithOne::createWithTexture(pTexture);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithOne");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithTexture of class  CCFilteredSpriteWithOne */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithTexture01
static int tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithTexture01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithOne",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCTexture2D* pTexture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  const CCRect* rect = ((const CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCFilteredSpriteWithOne* tolua_ret = (CCFilteredSpriteWithOne*)  CCFilteredSpriteWithOne::createWithTexture(pTexture,*rect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithOne");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithTexture00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrame of class  CCFilteredSpriteWithOne */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithSpriteFrame00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithOne",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSpriteFrame* pSpriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  {
   CCFilteredSpriteWithOne* tolua_ret = (CCFilteredSpriteWithOne*)  CCFilteredSpriteWithOne::createWithSpriteFrame(pSpriteFrame);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithOne");
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

/* method: createWithSpriteFrameName of class  CCFilteredSpriteWithOne */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithSpriteFrameName00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithOne",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszSpriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCFilteredSpriteWithOne* tolua_ret = (CCFilteredSpriteWithOne*)  CCFilteredSpriteWithOne::createWithSpriteFrameName(pszSpriteFrameName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithOne");
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

/* method: getFilter of class  CCFilteredSpriteWithOne */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithOne_getFilter00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithOne_getFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFilteredSpriteWithOne",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFilteredSpriteWithOne* self = (CCFilteredSpriteWithOne*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFilter'", NULL);
#endif
  {
   CCFilter* tolua_ret = (CCFilter*)  self->getFilter(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilter");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFilters of class  CCFilteredSpriteWithOne */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithOne_setFilters00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithOne_setFilters00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFilteredSpriteWithOne",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFilteredSpriteWithOne* self = (CCFilteredSpriteWithOne*)  tolua_tousertype(tolua_S,1,0);
  CCArray* pFilters = ((CCArray*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFilters'", NULL);
#endif
  {
   self->setFilters(pFilters);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFilters'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFilter of class  CCFilteredSpriteWithOne */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithOne_setFilter00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithOne_setFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFilteredSpriteWithOne",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFilteredSpriteWithOne* self = (CCFilteredSpriteWithOne*)  tolua_tousertype(tolua_S,1,0);
  CCFilter* pFilter = ((CCFilter*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFilter'", NULL);
#endif
  {
   self->setFilter(pFilter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCFilteredSpriteWithMulti */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithMulti",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCFilteredSpriteWithMulti* tolua_ret = (CCFilteredSpriteWithMulti*)  CCFilteredSpriteWithMulti::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithMulti");
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

/* method: create of class  CCFilteredSpriteWithMulti */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create01
static int tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithMulti",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCFilteredSpriteWithMulti* tolua_ret = (CCFilteredSpriteWithMulti*)  CCFilteredSpriteWithMulti::create(pszFileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithMulti");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCFilteredSpriteWithMulti */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create02
static int tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithMulti",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const CCRect* rect = ((const CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCFilteredSpriteWithMulti* tolua_ret = (CCFilteredSpriteWithMulti*)  CCFilteredSpriteWithMulti::create(pszFileName,*rect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithMulti");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithTexture of class  CCFilteredSpriteWithMulti */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithTexture00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithMulti",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTexture2D* pTexture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  {
   CCFilteredSpriteWithMulti* tolua_ret = (CCFilteredSpriteWithMulti*)  CCFilteredSpriteWithMulti::createWithTexture(pTexture);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithMulti");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithTexture of class  CCFilteredSpriteWithMulti */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithTexture01
static int tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithTexture01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithMulti",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCTexture2D* pTexture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  const CCRect* rect = ((const CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCFilteredSpriteWithMulti* tolua_ret = (CCFilteredSpriteWithMulti*)  CCFilteredSpriteWithMulti::createWithTexture(pTexture,*rect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithMulti");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithTexture00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrame of class  CCFilteredSpriteWithMulti */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithSpriteFrame00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithMulti",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSpriteFrame* pSpriteFrame = ((CCSpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  {
   CCFilteredSpriteWithMulti* tolua_ret = (CCFilteredSpriteWithMulti*)  CCFilteredSpriteWithMulti::createWithSpriteFrame(pSpriteFrame);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithMulti");
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

/* method: createWithSpriteFrameName of class  CCFilteredSpriteWithMulti */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithSpriteFrameName00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFilteredSpriteWithMulti",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszSpriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCFilteredSpriteWithMulti* tolua_ret = (CCFilteredSpriteWithMulti*)  CCFilteredSpriteWithMulti::createWithSpriteFrameName(pszSpriteFrameName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFilteredSpriteWithMulti");
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

/* method: setFilter of class  CCFilteredSpriteWithMulti */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_setFilter00
static int tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_setFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFilteredSpriteWithMulti",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFilteredSpriteWithMulti* self = (CCFilteredSpriteWithMulti*)  tolua_tousertype(tolua_S,1,0);
  CCFilter* pFilter = ((CCFilter*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFilter'", NULL);
#endif
  {
   self->setFilter(pFilter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initSprite of class  CCFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCFilter_initSprite00
static int tolua_ExtensionsFilters_CCFilter_initSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFilter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCFilteredSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFilter* self = (CCFilter*)  tolua_tousertype(tolua_S,1,0);
  CCFilteredSprite* sprite = ((CCFilteredSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initSprite'", NULL);
#endif
  {
   self->initSprite(sprite);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: shaderName of class  CCFilter */
#ifndef TOLUA_DISABLE_tolua_get_CCFilter_shaderName
static int tolua_get_CCFilter_shaderName(lua_State* tolua_S)
{
  CCFilter* self = (CCFilter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'shaderName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->shaderName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCSingleFloatParamFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCSingleFloatParamFilter_setParameter00
static int tolua_ExtensionsFilters_CCSingleFloatParamFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSingleFloatParamFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSingleFloatParamFilter* self = (CCSingleFloatParamFilter*)  tolua_tousertype(tolua_S,1,0);
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCBlurBaseFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCBlurBaseFilter_setParameter00
static int tolua_ExtensionsFilters_CCBlurBaseFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBlurBaseFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBlurBaseFilter* self = (CCBlurBaseFilter*)  tolua_tousertype(tolua_S,1,0);
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCHBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCHBlurFilter_create00
static int tolua_ExtensionsFilters_CCHBlurFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCHBlurFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCHBlurFilter* tolua_ret = (CCHBlurFilter*)  CCHBlurFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCHBlurFilter");
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

/* method: create of class  CCHBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCHBlurFilter_create01
static int tolua_ExtensionsFilters_CCHBlurFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCHBlurFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCHBlurFilter* tolua_ret = (CCHBlurFilter*)  CCHBlurFilter::create(param);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCHBlurFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCHBlurFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCVBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCVBlurFilter_create00
static int tolua_ExtensionsFilters_CCVBlurFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCVBlurFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCVBlurFilter* tolua_ret = (CCVBlurFilter*)  CCVBlurFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCVBlurFilter");
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

/* method: create of class  CCVBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCVBlurFilter_create01
static int tolua_ExtensionsFilters_CCVBlurFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCVBlurFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCVBlurFilter* tolua_ret = (CCVBlurFilter*)  CCVBlurFilter::create(param);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCVBlurFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCVBlurFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCGaussianHBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCGaussianHBlurFilter_create00
static int tolua_ExtensionsFilters_CCGaussianHBlurFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGaussianHBlurFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCGaussianHBlurFilter* tolua_ret = (CCGaussianHBlurFilter*)  CCGaussianHBlurFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGaussianHBlurFilter");
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

/* method: create of class  CCGaussianHBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCGaussianHBlurFilter_create01
static int tolua_ExtensionsFilters_CCGaussianHBlurFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGaussianHBlurFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCGaussianHBlurFilter* tolua_ret = (CCGaussianHBlurFilter*)  CCGaussianHBlurFilter::create(param);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGaussianHBlurFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCGaussianHBlurFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCGaussianVBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCGaussianVBlurFilter_create00
static int tolua_ExtensionsFilters_CCGaussianVBlurFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGaussianVBlurFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCGaussianVBlurFilter* tolua_ret = (CCGaussianVBlurFilter*)  CCGaussianVBlurFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGaussianVBlurFilter");
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

/* method: create of class  CCGaussianVBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCGaussianVBlurFilter_create01
static int tolua_ExtensionsFilters_CCGaussianVBlurFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGaussianVBlurFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCGaussianVBlurFilter* tolua_ret = (CCGaussianVBlurFilter*)  CCGaussianVBlurFilter::create(param);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGaussianVBlurFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCGaussianVBlurFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCZoomBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCZoomBlurFilter_create00
static int tolua_ExtensionsFilters_CCZoomBlurFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCZoomBlurFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCZoomBlurFilter* tolua_ret = (CCZoomBlurFilter*)  CCZoomBlurFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCZoomBlurFilter");
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

/* method: create of class  CCZoomBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCZoomBlurFilter_create01
static int tolua_ExtensionsFilters_CCZoomBlurFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCZoomBlurFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float blurSize = ((float)  tolua_tonumber(tolua_S,2,0));
  float centerX = ((float)  tolua_tonumber(tolua_S,3,0));
  float centerY = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCZoomBlurFilter* tolua_ret = (CCZoomBlurFilter*)  CCZoomBlurFilter::create(blurSize,centerX,centerY);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCZoomBlurFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCZoomBlurFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCZoomBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCZoomBlurFilter_setParameter00
static int tolua_ExtensionsFilters_CCZoomBlurFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCZoomBlurFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCZoomBlurFilter* self = (CCZoomBlurFilter*)  tolua_tousertype(tolua_S,1,0);
  float blurSize = ((float)  tolua_tonumber(tolua_S,2,0));
  float centerX = ((float)  tolua_tonumber(tolua_S,3,0));
  float centerY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(blurSize,centerX,centerY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCMotionBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCMotionBlurFilter_create00
static int tolua_ExtensionsFilters_CCMotionBlurFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMotionBlurFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCMotionBlurFilter* tolua_ret = (CCMotionBlurFilter*)  CCMotionBlurFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCMotionBlurFilter");
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

/* method: create of class  CCMotionBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCMotionBlurFilter_create01
static int tolua_ExtensionsFilters_CCMotionBlurFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMotionBlurFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float blurSize = ((float)  tolua_tonumber(tolua_S,2,0));
  float blurAngle = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCMotionBlurFilter* tolua_ret = (CCMotionBlurFilter*)  CCMotionBlurFilter::create(blurSize,blurAngle);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCMotionBlurFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCMotionBlurFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCMotionBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCMotionBlurFilter_setParameter00
static int tolua_ExtensionsFilters_CCMotionBlurFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMotionBlurFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMotionBlurFilter* self = (CCMotionBlurFilter*)  tolua_tousertype(tolua_S,1,0);
  float blurSize = ((float)  tolua_tonumber(tolua_S,2,0));
  float blurAngle = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(blurSize,blurAngle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initSprite of class  CCMotionBlurFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCMotionBlurFilter_initSprite00
static int tolua_ExtensionsFilters_CCMotionBlurFilter_initSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMotionBlurFilter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCFilteredSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMotionBlurFilter* self = (CCMotionBlurFilter*)  tolua_tousertype(tolua_S,1,0);
  CCFilteredSprite* sprite = ((CCFilteredSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initSprite'", NULL);
#endif
  {
   self->initSprite(sprite);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCBrightnessFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCBrightnessFilter_create00
static int tolua_ExtensionsFilters_CCBrightnessFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBrightnessFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCBrightnessFilter* tolua_ret = (CCBrightnessFilter*)  CCBrightnessFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCBrightnessFilter");
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

/* method: create of class  CCBrightnessFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCBrightnessFilter_create01
static int tolua_ExtensionsFilters_CCBrightnessFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCBrightnessFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float brightness = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCBrightnessFilter* tolua_ret = (CCBrightnessFilter*)  CCBrightnessFilter::create(brightness);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCBrightnessFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCBrightnessFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCBrightnessFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCBrightnessFilter_setParameter00
static int tolua_ExtensionsFilters_CCBrightnessFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCBrightnessFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCBrightnessFilter* self = (CCBrightnessFilter*)  tolua_tousertype(tolua_S,1,0);
  float brightness = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(brightness);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCContrastFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCContrastFilter_create00
static int tolua_ExtensionsFilters_CCContrastFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCContrastFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCContrastFilter* tolua_ret = (CCContrastFilter*)  CCContrastFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCContrastFilter");
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

/* method: create of class  CCContrastFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCContrastFilter_create01
static int tolua_ExtensionsFilters_CCContrastFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCContrastFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCContrastFilter* tolua_ret = (CCContrastFilter*)  CCContrastFilter::create(param);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCContrastFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCContrastFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCContrastFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCContrastFilter_setParameter00
static int tolua_ExtensionsFilters_CCContrastFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCContrastFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCContrastFilter* self = (CCContrastFilter*)  tolua_tousertype(tolua_S,1,0);
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCDropShadowFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCDropShadowFilter_create00
static int tolua_ExtensionsFilters_CCDropShadowFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDropShadowFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDropShadowFilter* tolua_ret = (CCDropShadowFilter*)  CCDropShadowFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDropShadowFilter");
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

/* method: create of class  CCDropShadowFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCDropShadowFilter_create01
static int tolua_ExtensionsFilters_CCDropShadowFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDropShadowFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float resolation = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCDropShadowFilter* tolua_ret = (CCDropShadowFilter*)  CCDropShadowFilter::create(resolation);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDropShadowFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCDropShadowFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCDropShadowFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCDropShadowFilter_setParameter00
static int tolua_ExtensionsFilters_CCDropShadowFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDropShadowFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDropShadowFilter* self = (CCDropShadowFilter*)  tolua_tousertype(tolua_S,1,0);
  float resolation = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(resolation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initSprite of class  CCDropShadowFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCDropShadowFilter_initSprite00
static int tolua_ExtensionsFilters_CCDropShadowFilter_initSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDropShadowFilter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCFilteredSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDropShadowFilter* self = (CCDropShadowFilter*)  tolua_tousertype(tolua_S,1,0);
  CCFilteredSprite* sprite = ((CCFilteredSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initSprite'", NULL);
#endif
  {
   self->initSprite(sprite);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCExposureFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCExposureFilter_create00
static int tolua_ExtensionsFilters_CCExposureFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCExposureFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCExposureFilter* tolua_ret = (CCExposureFilter*)  CCExposureFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCExposureFilter");
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

/* method: create of class  CCExposureFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCExposureFilter_create01
static int tolua_ExtensionsFilters_CCExposureFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCExposureFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCExposureFilter* tolua_ret = (CCExposureFilter*)  CCExposureFilter::create(param);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCExposureFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCExposureFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCExposureFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCExposureFilter_setParameter00
static int tolua_ExtensionsFilters_CCExposureFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCExposureFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCExposureFilter* self = (CCExposureFilter*)  tolua_tousertype(tolua_S,1,0);
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCGammaFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCGammaFilter_create00
static int tolua_ExtensionsFilters_CCGammaFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGammaFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCGammaFilter* tolua_ret = (CCGammaFilter*)  CCGammaFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGammaFilter");
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

/* method: create of class  CCGammaFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCGammaFilter_create01
static int tolua_ExtensionsFilters_CCGammaFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGammaFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCGammaFilter* tolua_ret = (CCGammaFilter*)  CCGammaFilter::create(param);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGammaFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCGammaFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCGammaFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCGammaFilter_setParameter00
static int tolua_ExtensionsFilters_CCGammaFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGammaFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGammaFilter* self = (CCGammaFilter*)  tolua_tousertype(tolua_S,1,0);
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCGrayFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCGrayFilter_create00
static int tolua_ExtensionsFilters_CCGrayFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGrayFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCGrayFilter* tolua_ret = (CCGrayFilter*)  CCGrayFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGrayFilter");
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

/* method: create of class  CCGrayFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCGrayFilter_create01
static int tolua_ExtensionsFilters_CCGrayFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGrayFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float r = ((float)  tolua_tonumber(tolua_S,2,0));
  float g = ((float)  tolua_tonumber(tolua_S,3,0));
  float b = ((float)  tolua_tonumber(tolua_S,4,0));
  float a = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   CCGrayFilter* tolua_ret = (CCGrayFilter*)  CCGrayFilter::create(r,g,b,a);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGrayFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCGrayFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCGrayFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCGrayFilter_setParameter00
static int tolua_ExtensionsFilters_CCGrayFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrayFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrayFilter* self = (CCGrayFilter*)  tolua_tousertype(tolua_S,1,0);
  float r = ((float)  tolua_tonumber(tolua_S,2,0));
  float g = ((float)  tolua_tonumber(tolua_S,3,0));
  float b = ((float)  tolua_tonumber(tolua_S,4,0));
  float a = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(r,g,b,a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCHazeFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCHazeFilter_create00
static int tolua_ExtensionsFilters_CCHazeFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCHazeFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCHazeFilter* tolua_ret = (CCHazeFilter*)  CCHazeFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCHazeFilter");
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

/* method: create of class  CCHazeFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCHazeFilter_create01
static int tolua_ExtensionsFilters_CCHazeFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCHazeFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float hazeDistance = ((float)  tolua_tonumber(tolua_S,2,0));
  float slope = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCHazeFilter* tolua_ret = (CCHazeFilter*)  CCHazeFilter::create(hazeDistance,slope);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCHazeFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCHazeFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCHazeFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCHazeFilter_setParameter00
static int tolua_ExtensionsFilters_CCHazeFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCHazeFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCHazeFilter* self = (CCHazeFilter*)  tolua_tousertype(tolua_S,1,0);
  float hazeDistance = ((float)  tolua_tonumber(tolua_S,2,0));
  float slope = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(hazeDistance,slope);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCHueFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCHueFilter_create00
static int tolua_ExtensionsFilters_CCHueFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCHueFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCHueFilter* tolua_ret = (CCHueFilter*)  CCHueFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCHueFilter");
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

/* method: create of class  CCHueFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCHueFilter_create01
static int tolua_ExtensionsFilters_CCHueFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCHueFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCHueFilter* tolua_ret = (CCHueFilter*)  CCHueFilter::create(param);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCHueFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCHueFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCHueFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCHueFilter_setParameter00
static int tolua_ExtensionsFilters_CCHueFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCHueFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCHueFilter* self = (CCHueFilter*)  tolua_tousertype(tolua_S,1,0);
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCMaskFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCMaskFilter_create00
static int tolua_ExtensionsFilters_CCMaskFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMaskFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCMaskFilter* tolua_ret = (CCMaskFilter*)  CCMaskFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCMaskFilter");
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

/* method: create of class  CCMaskFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCMaskFilter_create01
static int tolua_ExtensionsFilters_CCMaskFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMaskFilter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCString* maskImage = ((CCString*)  tolua_tousertype(tolua_S,2,0));
  {
   CCMaskFilter* tolua_ret = (CCMaskFilter*)  CCMaskFilter::create(maskImage);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCMaskFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCMaskFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrameName of class  CCMaskFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCMaskFilter_createWithSpriteFrameName00
static int tolua_ExtensionsFilters_CCMaskFilter_createWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMaskFilter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCString* maskImage = ((CCString*)  tolua_tousertype(tolua_S,2,0));
  {
   CCMaskFilter* tolua_ret = (CCMaskFilter*)  CCMaskFilter::createWithSpriteFrameName(maskImage);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCMaskFilter");
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

/* method: setParameter of class  CCMaskFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCMaskFilter_setParameter00
static int tolua_ExtensionsFilters_CCMaskFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMaskFilter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCString",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMaskFilter* self = (CCMaskFilter*)  tolua_tousertype(tolua_S,1,0);
  CCString* param = ((CCString*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initSprite of class  CCMaskFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCMaskFilter_initSprite00
static int tolua_ExtensionsFilters_CCMaskFilter_initSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMaskFilter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCFilteredSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMaskFilter* self = (CCMaskFilter*)  tolua_tousertype(tolua_S,1,0);
  CCFilteredSprite* sprite = ((CCFilteredSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initSprite'", NULL);
#endif
  {
   self->initSprite(sprite);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsSpriteFrame of class  CCMaskFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCMaskFilter_setIsSpriteFrame00
static int tolua_ExtensionsFilters_CCMaskFilter_setIsSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMaskFilter",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMaskFilter* self = (CCMaskFilter*)  tolua_tousertype(tolua_S,1,0);
  bool isSpriteFrame = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsSpriteFrame'", NULL);
#endif
  {
   self->setIsSpriteFrame(isSpriteFrame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCRGBFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCRGBFilter_create00
static int tolua_ExtensionsFilters_CCRGBFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCRGBFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCRGBFilter* tolua_ret = (CCRGBFilter*)  CCRGBFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRGBFilter");
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

/* method: create of class  CCRGBFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCRGBFilter_create01
static int tolua_ExtensionsFilters_CCRGBFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCRGBFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float redAdj = ((float)  tolua_tonumber(tolua_S,2,0));
  float greenAdj = ((float)  tolua_tonumber(tolua_S,3,0));
  float blueAdj = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCRGBFilter* tolua_ret = (CCRGBFilter*)  CCRGBFilter::create(redAdj,greenAdj,blueAdj);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRGBFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCRGBFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCRGBFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCRGBFilter_setParameter00
static int tolua_ExtensionsFilters_CCRGBFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRGBFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRGBFilter* self = (CCRGBFilter*)  tolua_tousertype(tolua_S,1,0);
  float redAdj = ((float)  tolua_tonumber(tolua_S,2,0));
  float greenAdj = ((float)  tolua_tonumber(tolua_S,3,0));
  float blueAdj = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(redAdj,greenAdj,blueAdj);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCSaturationFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCSaturationFilter_create00
static int tolua_ExtensionsFilters_CCSaturationFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSaturationFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSaturationFilter* tolua_ret = (CCSaturationFilter*)  CCSaturationFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSaturationFilter");
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

/* method: create of class  CCSaturationFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCSaturationFilter_create01
static int tolua_ExtensionsFilters_CCSaturationFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSaturationFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCSaturationFilter* tolua_ret = (CCSaturationFilter*)  CCSaturationFilter::create(param);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSaturationFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCSaturationFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCSaturationFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCSaturationFilter_setParameter00
static int tolua_ExtensionsFilters_CCSaturationFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSaturationFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSaturationFilter* self = (CCSaturationFilter*)  tolua_tousertype(tolua_S,1,0);
  float param = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCSharpenFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCSharpenFilter_create00
static int tolua_ExtensionsFilters_CCSharpenFilter_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSharpenFilter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSharpenFilter* tolua_ret = (CCSharpenFilter*)  CCSharpenFilter::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSharpenFilter");
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

/* method: create of class  CCSharpenFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCSharpenFilter_create01
static int tolua_ExtensionsFilters_CCSharpenFilter_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSharpenFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float sharpness = ((float)  tolua_tonumber(tolua_S,2,0));
  float widthFactor = ((float)  tolua_tonumber(tolua_S,3,0));
  float heightFactor = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCSharpenFilter* tolua_ret = (CCSharpenFilter*)  CCSharpenFilter::create(sharpness,widthFactor,heightFactor);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSharpenFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCSharpenFilter_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCSharpenFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCSharpenFilter_create02
static int tolua_ExtensionsFilters_CCSharpenFilter_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSharpenFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float sharpness = ((float)  tolua_tonumber(tolua_S,2,0));
  int amount = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   CCSharpenFilter* tolua_ret = (CCSharpenFilter*)  CCSharpenFilter::create(sharpness,amount);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSharpenFilter");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsFilters_CCSharpenFilter_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCSharpenFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCSharpenFilter_setParameter00
static int tolua_ExtensionsFilters_CCSharpenFilter_setParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSharpenFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSharpenFilter* self = (CCSharpenFilter*)  tolua_tousertype(tolua_S,1,0);
  float sharpness = ((float)  tolua_tonumber(tolua_S,2,0));
  float widthFactor = ((float)  tolua_tonumber(tolua_S,3,0));
  float heightFactor = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(sharpness,widthFactor,heightFactor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParameter of class  CCSharpenFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCSharpenFilter_setParameter01
static int tolua_ExtensionsFilters_CCSharpenFilter_setParameter01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSharpenFilter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCSharpenFilter* self = (CCSharpenFilter*)  tolua_tousertype(tolua_S,1,0);
  float sharpness = ((float)  tolua_tonumber(tolua_S,2,0));
  int amount = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParameter'", NULL);
#endif
  {
   self->setParameter(sharpness,amount);
  }
 }
 return 0;
tolua_lerror:
 return tolua_ExtensionsFilters_CCSharpenFilter_setParameter00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initSprite of class  CCSharpenFilter */
#ifndef TOLUA_DISABLE_tolua_ExtensionsFilters_CCSharpenFilter_initSprite00
static int tolua_ExtensionsFilters_CCSharpenFilter_initSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSharpenFilter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCFilteredSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSharpenFilter* self = (CCSharpenFilter*)  tolua_tousertype(tolua_S,1,0);
  CCFilteredSprite* sprite = ((CCFilteredSprite*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initSprite'", NULL);
#endif
  {
   self->initSprite(sprite);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ExtensionsFilters_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CCFilteredSprite","CCFilteredSprite","CCSprite",NULL);
  tolua_beginmodule(tolua_S,"CCFilteredSprite");
   tolua_function(tolua_S,"getFilter",tolua_ExtensionsFilters_CCFilteredSprite_getFilter00);
   tolua_function(tolua_S,"setFilter",tolua_ExtensionsFilters_CCFilteredSprite_setFilter00);
   tolua_function(tolua_S,"getFilters",tolua_ExtensionsFilters_CCFilteredSprite_getFilters00);
   tolua_function(tolua_S,"setFilters",tolua_ExtensionsFilters_CCFilteredSprite_setFilters00);
   tolua_function(tolua_S,"clearFilter",tolua_ExtensionsFilters_CCFilteredSprite_clearFilter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCFilteredSpriteWithOne","CCFilteredSpriteWithOne","CCFilteredSprite",NULL);
  tolua_beginmodule(tolua_S,"CCFilteredSpriteWithOne");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create01);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCFilteredSpriteWithOne_create02);
   tolua_function(tolua_S,"createWithTexture",tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithTexture00);
   tolua_function(tolua_S,"createWithTexture",tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithTexture01);
   tolua_function(tolua_S,"createWithSpriteFrame",tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithSpriteFrame00);
   tolua_function(tolua_S,"createWithSpriteFrameName",tolua_ExtensionsFilters_CCFilteredSpriteWithOne_createWithSpriteFrameName00);
   tolua_function(tolua_S,"getFilter",tolua_ExtensionsFilters_CCFilteredSpriteWithOne_getFilter00);
   tolua_function(tolua_S,"setFilters",tolua_ExtensionsFilters_CCFilteredSpriteWithOne_setFilters00);
   tolua_function(tolua_S,"setFilter",tolua_ExtensionsFilters_CCFilteredSpriteWithOne_setFilter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCFilteredSpriteWithMulti","CCFilteredSpriteWithMulti","CCFilteredSprite",NULL);
  tolua_beginmodule(tolua_S,"CCFilteredSpriteWithMulti");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create01);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_create02);
   tolua_function(tolua_S,"createWithTexture",tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithTexture00);
   tolua_function(tolua_S,"createWithTexture",tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithTexture01);
   tolua_function(tolua_S,"createWithSpriteFrame",tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithSpriteFrame00);
   tolua_function(tolua_S,"createWithSpriteFrameName",tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_createWithSpriteFrameName00);
   tolua_function(tolua_S,"setFilter",tolua_ExtensionsFilters_CCFilteredSpriteWithMulti_setFilter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCFilter","CCFilter","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CCFilter");
   tolua_function(tolua_S,"initSprite",tolua_ExtensionsFilters_CCFilter_initSprite00);
   tolua_variable(tolua_S,"shaderName",tolua_get_CCFilter_shaderName,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCSingleFloatParamFilter","CCSingleFloatParamFilter","CCFilter",NULL);
  tolua_beginmodule(tolua_S,"CCSingleFloatParamFilter");
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCSingleFloatParamFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCBlurBaseFilter","CCBlurBaseFilter","CCSingleFloatParamFilter",NULL);
  tolua_beginmodule(tolua_S,"CCBlurBaseFilter");
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCBlurBaseFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCHBlurFilter","CCHBlurFilter","CCBlurBaseFilter",NULL);
  tolua_beginmodule(tolua_S,"CCHBlurFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCHBlurFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCHBlurFilter_create01);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCVBlurFilter","CCVBlurFilter","CCBlurBaseFilter",NULL);
  tolua_beginmodule(tolua_S,"CCVBlurFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCVBlurFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCVBlurFilter_create01);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCGaussianHBlurFilter","CCGaussianHBlurFilter","CCBlurBaseFilter",NULL);
  tolua_beginmodule(tolua_S,"CCGaussianHBlurFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCGaussianHBlurFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCGaussianHBlurFilter_create01);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCGaussianVBlurFilter","CCGaussianVBlurFilter","CCBlurBaseFilter",NULL);
  tolua_beginmodule(tolua_S,"CCGaussianVBlurFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCGaussianVBlurFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCGaussianVBlurFilter_create01);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCZoomBlurFilter","CCZoomBlurFilter","CCFilter",NULL);
  tolua_beginmodule(tolua_S,"CCZoomBlurFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCZoomBlurFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCZoomBlurFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCZoomBlurFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCMotionBlurFilter","CCMotionBlurFilter","CCFilter",NULL);
  tolua_beginmodule(tolua_S,"CCMotionBlurFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCMotionBlurFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCMotionBlurFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCMotionBlurFilter_setParameter00);
   tolua_function(tolua_S,"initSprite",tolua_ExtensionsFilters_CCMotionBlurFilter_initSprite00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCBrightnessFilter","CCBrightnessFilter","CCSingleFloatParamFilter",NULL);
  tolua_beginmodule(tolua_S,"CCBrightnessFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCBrightnessFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCBrightnessFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCBrightnessFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCContrastFilter","CCContrastFilter","CCSingleFloatParamFilter",NULL);
  tolua_beginmodule(tolua_S,"CCContrastFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCContrastFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCContrastFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCContrastFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCDropShadowFilter","CCDropShadowFilter","CCFilter",NULL);
  tolua_beginmodule(tolua_S,"CCDropShadowFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCDropShadowFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCDropShadowFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCDropShadowFilter_setParameter00);
   tolua_function(tolua_S,"initSprite",tolua_ExtensionsFilters_CCDropShadowFilter_initSprite00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCExposureFilter","CCExposureFilter","CCSingleFloatParamFilter",NULL);
  tolua_beginmodule(tolua_S,"CCExposureFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCExposureFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCExposureFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCExposureFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCGammaFilter","CCGammaFilter","CCSingleFloatParamFilter",NULL);
  tolua_beginmodule(tolua_S,"CCGammaFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCGammaFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCGammaFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCGammaFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCGrayFilter","CCGrayFilter","CCFilter",NULL);
  tolua_beginmodule(tolua_S,"CCGrayFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCGrayFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCGrayFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCGrayFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCHazeFilter","CCHazeFilter","CCFilter",NULL);
  tolua_beginmodule(tolua_S,"CCHazeFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCHazeFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCHazeFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCHazeFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCHueFilter","CCHueFilter","CCSingleFloatParamFilter",NULL);
  tolua_beginmodule(tolua_S,"CCHueFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCHueFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCHueFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCHueFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCMaskFilter","CCMaskFilter","CCFilter",NULL);
  tolua_beginmodule(tolua_S,"CCMaskFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCMaskFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCMaskFilter_create01);
   tolua_function(tolua_S,"createWithSpriteFrameName",tolua_ExtensionsFilters_CCMaskFilter_createWithSpriteFrameName00);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCMaskFilter_setParameter00);
   tolua_function(tolua_S,"initSprite",tolua_ExtensionsFilters_CCMaskFilter_initSprite00);
   tolua_function(tolua_S,"setIsSpriteFrame",tolua_ExtensionsFilters_CCMaskFilter_setIsSpriteFrame00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCRGBFilter","CCRGBFilter","CCFilter",NULL);
  tolua_beginmodule(tolua_S,"CCRGBFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCRGBFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCRGBFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCRGBFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCSaturationFilter","CCSaturationFilter","CCSingleFloatParamFilter",NULL);
  tolua_beginmodule(tolua_S,"CCSaturationFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCSaturationFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCSaturationFilter_create01);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCSaturationFilter_setParameter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCSharpenFilter","CCSharpenFilter","CCFilter",NULL);
  tolua_beginmodule(tolua_S,"CCSharpenFilter");
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCSharpenFilter_create00);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCSharpenFilter_create01);
   tolua_function(tolua_S,"create",tolua_ExtensionsFilters_CCSharpenFilter_create02);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCSharpenFilter_setParameter00);
   tolua_function(tolua_S,"setParameter",tolua_ExtensionsFilters_CCSharpenFilter_setParameter01);
   tolua_function(tolua_S,"initSprite",tolua_ExtensionsFilters_CCSharpenFilter_initSprite00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ExtensionsFilters (lua_State* tolua_S) {
 return tolua_ExtensionsFilters_open(tolua_S);
};
#endif

