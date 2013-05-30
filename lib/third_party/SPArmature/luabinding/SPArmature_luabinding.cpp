/*
** Lua binding: SPArmature_luabinding
** Generated automatically by tolua++-1.0.92 on Thu May 30 10:47:00 2013.
*/

#include "SPArmature_luabinding.h"
#include "CCLuaEngine.h"

using namespace cocos2d;




#include "cocos2d.h"
#include "SPArmature.h"
#include "SPArmatureDataManager.h"
#include "SPBatchNodeManager.h"
#include "SPSpriteDisplayData.h"
using namespace cocos2d;
using namespace sp;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCRect (lua_State* tolua_S)
{
 CCRect* self = (CCRect*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCRect");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"Armature");
 tolua_usertype(tolua_S,"ArmatureDataManager");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"BatchNodeManager");
 tolua_usertype(tolua_S,"BatchNode");
}

/* method: sharedBatchNodeManager of class  BatchNodeManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_BatchNodeManager_sharedBatchNodeManager00
static int tolua_SPArmature_luabinding_BatchNodeManager_sharedBatchNodeManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BatchNodeManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BatchNodeManager* tolua_ret = (BatchNodeManager*)  BatchNodeManager::sharedBatchNodeManager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BatchNodeManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedBatchNodeManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithLayer of class  BatchNodeManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_BatchNodeManager_initWithLayer00
static int tolua_SPArmature_luabinding_BatchNodeManager_initWithLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BatchNodeManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCLayer",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BatchNodeManager* self = (BatchNodeManager*)  tolua_tousertype(tolua_S,1,0);
  CCLayer* _layer = ((CCLayer*)  tolua_tousertype(tolua_S,2,0));
  std::string _layerName = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithLayer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithLayer(_layer,_layerName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBatchNode of class  BatchNodeManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_BatchNodeManager_addBatchNode00
static int tolua_SPArmature_luabinding_BatchNodeManager_addBatchNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BatchNodeManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"BatchNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BatchNodeManager* self = (BatchNodeManager*)  tolua_tousertype(tolua_S,1,0);
  std::string _name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  BatchNode* _batchNode = ((BatchNode*)  tolua_tousertype(tolua_S,3,0));
  int _zOrder = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBatchNode'", NULL);
#endif
  {
   self->addBatchNode(_name,_batchNode,_zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addBatchNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBatchNode of class  BatchNodeManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_BatchNodeManager_getBatchNode00
static int tolua_SPArmature_luabinding_BatchNodeManager_getBatchNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BatchNodeManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BatchNodeManager* self = (BatchNodeManager*)  tolua_tousertype(tolua_S,1,0);
  std::string _name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBatchNode'", NULL);
#endif
  {
   BatchNode* tolua_ret = (BatchNode*)  self->getBatchNode(_name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BatchNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBatchNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBatchNodeZOrder of class  BatchNodeManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_BatchNodeManager_setBatchNodeZOrder00
static int tolua_SPArmature_luabinding_BatchNodeManager_setBatchNodeZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BatchNodeManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BatchNodeManager* self = (BatchNodeManager*)  tolua_tousertype(tolua_S,1,0);
  std::string _name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  int _zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBatchNodeZOrder'", NULL);
#endif
  {
   self->setBatchNodeZOrder(_name,_zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBatchNodeZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBatchNodeBlendFunc of class  BatchNodeManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_BatchNodeManager_setBatchNodeBlendFunc00
static int tolua_SPArmature_luabinding_BatchNodeManager_setBatchNodeBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BatchNodeManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BatchNodeManager* self = (BatchNodeManager*)  tolua_tousertype(tolua_S,1,0);
  std::string _name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  unsigned int _src = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int _dst = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBatchNodeBlendFunc'", NULL);
#endif
  {
   self->setBatchNodeBlendFunc(_name,_src,_dst);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBatchNodeBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeBatchNodes of class  BatchNodeManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_BatchNodeManager_removeBatchNodes00
static int tolua_SPArmature_luabinding_BatchNodeManager_removeBatchNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BatchNodeManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BatchNodeManager* self = (BatchNodeManager*)  tolua_tousertype(tolua_S,1,0);
  std::string _layerName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeBatchNodes'", NULL);
#endif
  {
   self->removeBatchNodes(_layerName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeBatchNodes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentLayer of class  BatchNodeManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_BatchNodeManager_getCurrentLayer00
static int tolua_SPArmature_luabinding_BatchNodeManager_getCurrentLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BatchNodeManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BatchNodeManager* self = (BatchNodeManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentLayer'", NULL);
#endif
  {
   CCLayer* tolua_ret = (CCLayer*)  self->getCurrentLayer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedArmatureDataManager of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_ArmatureDataManager_sharedArmatureDataManager00
static int tolua_SPArmature_luabinding_ArmatureDataManager_sharedArmatureDataManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ArmatureDataManager* tolua_ret = (ArmatureDataManager*)  ArmatureDataManager::sharedArmatureDataManager();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ArmatureDataManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedArmatureDataManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addArmatureFileInfo of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_ArmatureDataManager_addArmatureFileInfo00
static int tolua_SPArmature_luabinding_ArmatureDataManager_addArmatureFileInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureDataManager* self = (ArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
  const char* _armatureName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* _useExistFileInfo = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* _imagePath = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* _plistPath = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* _configFilePath = ((const char*)  tolua_tostring(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addArmatureFileInfo'", NULL);
#endif
  {
   self->addArmatureFileInfo(_armatureName,_useExistFileInfo,_imagePath,_plistPath,_configFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addArmatureFileInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addSpriteFrameFromFile of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_ArmatureDataManager_addSpriteFrameFromFile00
static int tolua_SPArmature_luabinding_ArmatureDataManager_addSpriteFrameFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureDataManager* self = (ArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
  const char* _plistPath = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* _imagePath = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSpriteFrameFromFile'", NULL);
#endif
  {
   self->addSpriteFrameFromFile(_plistPath,_imagePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSpriteFrameFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayImagePath of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_ArmatureDataManager_getDisplayImagePath00
static int tolua_SPArmature_luabinding_ArmatureDataManager_getDisplayImagePath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureDataManager* self = (ArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
  const char* _displayName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayImagePath'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getDisplayImagePath(_displayName);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayImagePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAll of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_ArmatureDataManager_removeAll00
static int tolua_SPArmature_luabinding_ArmatureDataManager_removeAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureDataManager* self = (ArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAll'", NULL);
#endif
  {
   self->removeAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_create00
static int tolua_SPArmature_luabinding_Armature_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* _name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Armature* tolua_ret = (Armature*)  Armature::create(_name);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Armature");
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

/* method: create of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_create01
static int tolua_SPArmature_luabinding_Armature_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   Armature* tolua_ret = (Armature*)  Armature::create();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Armature");
  }
 }
 return 1;
tolua_lerror:
 return tolua_SPArmature_luabinding_Armature_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZOrder of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_setZOrder00
static int tolua_SPArmature_luabinding_Armature_setZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  int _zOrder = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZOrder'", NULL);
#endif
  {
   self->setZOrder(_zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZOrder of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_getZOrder00
static int tolua_SPArmature_luabinding_Armature_getZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZOrder'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getZOrder();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_setPosition00
static int tolua_SPArmature_luabinding_Armature_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  float _x = ((float)  tolua_tonumber(tolua_S,2,0));
  float _y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(_x,_y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPositionX of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_setPositionX00
static int tolua_SPArmature_luabinding_Armature_setPositionX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  float _x = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPositionX'", NULL);
#endif
  {
   self->setPositionX(_x);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPositionX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPositionY of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_setPositionY00
static int tolua_SPArmature_luabinding_Armature_setPositionY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  float _y = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPositionY'", NULL);
#endif
  {
   self->setPositionY(_y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPositionY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotation of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_setRotation00
static int tolua_SPArmature_luabinding_Armature_setRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  float _r = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotation'", NULL);
#endif
  {
   self->setRotation(_r);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_setScale00
static int tolua_SPArmature_luabinding_Armature_setScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  float _scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale'", NULL);
#endif
  {
   self->setScale(_scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleX of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_setScaleX00
static int tolua_SPArmature_luabinding_Armature_setScaleX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  float _scaleX = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleX'", NULL);
#endif
  {
   self->setScaleX(_scaleX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScaleY of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_setScaleY00
static int tolua_SPArmature_luabinding_Armature_setScaleY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  float _scaleY = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScaleY'", NULL);
#endif
  {
   self->setScaleY(_scaleY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScaleY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBoundingBox of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_getBoundingBox00
static int tolua_SPArmature_luabinding_Armature_getBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBoundingBox'", NULL);
#endif
  {
   CCRect tolua_ret = (CCRect)  self->getBoundingBox();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCRect));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_update00
static int tolua_SPArmature_luabinding_Armature_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(dt);
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

/* method: getVisible of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_getVisible00
static int tolua_SPArmature_luabinding_Armature_getVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  Armature */
#ifndef TOLUA_DISABLE_tolua_SPArmature_luabinding_Armature_setVisible00
static int tolua_SPArmature_luabinding_Armature_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  bool visible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SPArmature_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"BatchNodeManager","BatchNodeManager","",NULL);
  tolua_beginmodule(tolua_S,"BatchNodeManager");
   tolua_function(tolua_S,"sharedBatchNodeManager",tolua_SPArmature_luabinding_BatchNodeManager_sharedBatchNodeManager00);
   tolua_function(tolua_S,"initWithLayer",tolua_SPArmature_luabinding_BatchNodeManager_initWithLayer00);
   tolua_function(tolua_S,"addBatchNode",tolua_SPArmature_luabinding_BatchNodeManager_addBatchNode00);
   tolua_function(tolua_S,"getBatchNode",tolua_SPArmature_luabinding_BatchNodeManager_getBatchNode00);
   tolua_function(tolua_S,"setBatchNodeZOrder",tolua_SPArmature_luabinding_BatchNodeManager_setBatchNodeZOrder00);
   tolua_function(tolua_S,"setBatchNodeBlendFunc",tolua_SPArmature_luabinding_BatchNodeManager_setBatchNodeBlendFunc00);
   tolua_function(tolua_S,"removeBatchNodes",tolua_SPArmature_luabinding_BatchNodeManager_removeBatchNodes00);
   tolua_function(tolua_S,"getCurrentLayer",tolua_SPArmature_luabinding_BatchNodeManager_getCurrentLayer00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ArmatureDataManager","ArmatureDataManager","CCObject",NULL);
  tolua_beginmodule(tolua_S,"ArmatureDataManager");
   tolua_function(tolua_S,"sharedArmatureDataManager",tolua_SPArmature_luabinding_ArmatureDataManager_sharedArmatureDataManager00);
   tolua_function(tolua_S,"addArmatureFileInfo",tolua_SPArmature_luabinding_ArmatureDataManager_addArmatureFileInfo00);
   tolua_function(tolua_S,"addSpriteFrameFromFile",tolua_SPArmature_luabinding_ArmatureDataManager_addSpriteFrameFromFile00);
   tolua_function(tolua_S,"getDisplayImagePath",tolua_SPArmature_luabinding_ArmatureDataManager_getDisplayImagePath00);
   tolua_function(tolua_S,"removeAll",tolua_SPArmature_luabinding_ArmatureDataManager_removeAll00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Armature","Armature","CCNode",NULL);
  tolua_beginmodule(tolua_S,"Armature");
   tolua_function(tolua_S,"create",tolua_SPArmature_luabinding_Armature_create00);
   tolua_function(tolua_S,"create",tolua_SPArmature_luabinding_Armature_create01);
   tolua_function(tolua_S,"setZOrder",tolua_SPArmature_luabinding_Armature_setZOrder00);
   tolua_function(tolua_S,"getZOrder",tolua_SPArmature_luabinding_Armature_getZOrder00);
   tolua_function(tolua_S,"setPosition",tolua_SPArmature_luabinding_Armature_setPosition00);
   tolua_function(tolua_S,"setPositionX",tolua_SPArmature_luabinding_Armature_setPositionX00);
   tolua_function(tolua_S,"setPositionY",tolua_SPArmature_luabinding_Armature_setPositionY00);
   tolua_function(tolua_S,"setRotation",tolua_SPArmature_luabinding_Armature_setRotation00);
   tolua_function(tolua_S,"setScale",tolua_SPArmature_luabinding_Armature_setScale00);
   tolua_function(tolua_S,"setScaleX",tolua_SPArmature_luabinding_Armature_setScaleX00);
   tolua_function(tolua_S,"setScaleY",tolua_SPArmature_luabinding_Armature_setScaleY00);
   tolua_function(tolua_S,"getBoundingBox",tolua_SPArmature_luabinding_Armature_getBoundingBox00);
   tolua_function(tolua_S,"update",tolua_SPArmature_luabinding_Armature_update00);
   tolua_function(tolua_S,"getVisible",tolua_SPArmature_luabinding_Armature_getVisible00);
   tolua_function(tolua_S,"setVisible",tolua_SPArmature_luabinding_Armature_setVisible00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SPArmature_luabinding (lua_State* tolua_S) {
 return tolua_SPArmature_luabinding_open(tolua_S);
};
#endif

