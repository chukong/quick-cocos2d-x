/*
** Lua binding: CCPhysicsWorld_luabinding
** Generated automatically by tolua++-1.0.92 on 08/15/14 00:08:55.
*/

#include "CCPhysicsWorld_luabinding.h"
#include "CCLuaEngine.h"

using namespace cocos2d;




#include "CCPhysicsShape.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"
#include "CCPhysicsDebugNode.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCPoint (lua_State* tolua_S)
{
 CCPoint* self = (CCPoint*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPivotJoint"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCPivotJoint)), "CCPivotJoint");
 tolua_usertype(tolua_S,"CCPinJoint"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCPinJoint)), "CCPinJoint");
 tolua_usertype(tolua_S,"CCPhysicsVector"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCPhysicsVector)), "CCPhysicsVector");
 tolua_usertype(tolua_S,"CCPhysicsDebugNode"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCPhysicsDebugNode)), "CCPhysicsDebugNode");
 tolua_usertype(tolua_S,"CCNode"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCNode)), "CCNode");
 tolua_usertype(tolua_S,"CCArray"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCArray)), "CCArray");
 tolua_usertype(tolua_S,"CCPoint"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCPoint)), "CCPoint");
 tolua_usertype(tolua_S,"CCDampedSpringJoint"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCDampedSpringJoint)), "CCDampedSpringJoint");
 tolua_usertype(tolua_S,"CCPhysicsWorld"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCPhysicsWorld)), "CCPhysicsWorld");
 tolua_usertype(tolua_S,"CCPointArray"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCPointArray)), "CCPointArray");
 tolua_usertype(tolua_S,"CCGrooveJoint"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCGrooveJoint)), "CCGrooveJoint");
 tolua_usertype(tolua_S,"CCPhysicsCollisionEvent"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCPhysicsCollisionEvent)), "CCPhysicsCollisionEvent");
 tolua_usertype(tolua_S,"CCJoint"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCJoint)), "CCJoint");
 tolua_usertype(tolua_S,"CCPhysicsBody"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCPhysicsBody)), "CCPhysicsBody");
 
 tolua_usertype(tolua_S,"cpConstraint"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(cpConstraint)), "cpConstraint");
 
 tolua_usertype(tolua_S,"CCObject"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCObject)), "CCObject");
 tolua_usertype(tolua_S,"CCSlideJoint"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCSlideJoint)), "CCSlideJoint");
 tolua_usertype(tolua_S,"CCPhysicsShape"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCPhysicsShape)), "CCPhysicsShape");
}

/* method: create of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_create00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float gravityX = ((float)  tolua_tonumber(tolua_S,2,0));
  float gravityY = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCPhysicsWorld* tolua_ret = (CCPhysicsWorld*)  CCPhysicsWorld::create(gravityX,gravityY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsWorld");
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

/* method: create of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_create01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   CCPhysicsWorld* tolua_ret = (CCPhysicsWorld*)  CCPhysicsWorld::create();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsWorld");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createDebugNode of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createDebugNode00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createDebugNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createDebugNode'", NULL);
#endif
  {
   CCPhysicsDebugNode* tolua_ret = (CCPhysicsDebugNode*)  self->createDebugNode();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsDebugNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createDebugNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGravity of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getGravity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float gravityX = ((float)  tolua_tonumber(tolua_S,2,0));
  float gravityY = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGravity'", NULL);
#endif
  {
   self->getGravity(&gravityX,&gravityY);
   tolua_pushnumber(tolua_S,(lua_Number)gravityX);
   tolua_pushnumber(tolua_S,(lua_Number)gravityY);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGravity of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_setGravity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_setGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float gravityX = ((float)  tolua_tonumber(tolua_S,2,0));
  float gravityY = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGravity'", NULL);
#endif
  {
   self->setGravity(gravityX,gravityY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDamping of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getDamping00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDamping'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDamping();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDamping of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_setDamping00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_setDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float damping = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDamping'", NULL);
#endif
  {
   self->setDamping(damping);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIdleSpeedThreshold of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getIdleSpeedThreshold00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getIdleSpeedThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIdleSpeedThreshold'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getIdleSpeedThreshold();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIdleSpeedThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIdleSpeedThreshold of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_setIdleSpeedThreshold00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_setIdleSpeedThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float threshold = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIdleSpeedThreshold'", NULL);
#endif
  {
   self->setIdleSpeedThreshold(threshold);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIdleSpeedThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createCircleBody of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createCircleBody00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createCircleBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,4,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createCircleBody'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->createCircleBody(mass,radius,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createCircleBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createBoxBody of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createBoxBody00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createBoxBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
  float height = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createBoxBody'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->createBoxBody(mass,width,height);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createBoxBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createPolygonBody of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createPolygonBody00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createPolygonBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCPointArray",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
  CCPointArray* vertexes = ((CCPointArray*)  tolua_tousertype(tolua_S,3,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,4,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createPolygonBody'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->createPolygonBody(mass,vertexes,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createPolygonBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createPolygonBody of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createPolygonBody01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createPolygonBody01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_istable(tolua_S,3,"LUA_TABLE",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
  LUA_TABLE vertexes = (  toluafix_totable(tolua_S,3,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,4,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createPolygonBody'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->createPolygonBody(mass,vertexes,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createPolygonBody00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAllBodies of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getAllBodies00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getAllBodies00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAllBodies'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getAllBodies();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAllBodies'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBody of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addBody00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* body = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBody'", NULL);
#endif
  {
   self->addBody(body);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBodyByTag of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getBodyByTag00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getBodyByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBodyByTag'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->getBodyByTag(tag);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBodyByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeBodyByTag of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeBodyByTag00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeBodyByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  bool unbind = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeBodyByTag'", NULL);
#endif
  {
   self->removeBodyByTag(tag,unbind);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeBodyByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeBody of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeBody00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* body = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
  bool unbind = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeBody'", NULL);
#endif
  {
   self->removeBody(body,unbind);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllBodies of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeAllBodies00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeAllBodies00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  bool unbind = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllBodies'", NULL);
#endif
  {
   self->removeAllBodies(unbind);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllBodies'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: start of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_start00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'start'", NULL);
#endif
  {
   self->start();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_stop00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: step of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_step00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_step00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'step'", NULL);
#endif
  {
   self->step(dt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'step'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addCollisionScriptListener of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addCollisionScriptListener00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addCollisionScriptListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
  int collisionTypeA = ((int)  tolua_tonumber(tolua_S,3,0));
  int collisionTypeB = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addCollisionScriptListener'", NULL);
#endif
  {
   self->addCollisionScriptListener(handler,collisionTypeA,collisionTypeB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addCollisionScriptListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeCollisionScriptListener of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeCollisionScriptListener00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeCollisionScriptListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  int collisionTypeA = ((int)  tolua_tonumber(tolua_S,2,0));
  int collisionTypeB = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeCollisionScriptListener'", NULL);
#endif
  {
   self->removeCollisionScriptListener(collisionTypeA,collisionTypeB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeCollisionScriptListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllCollisionListeners of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeAllCollisionListeners00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeAllCollisionListeners00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllCollisionListeners'", NULL);
#endif
  {
   self->removeAllCollisionListeners();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllCollisionListeners'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: defaultStaticBody of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_defaultStaticBody00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_defaultStaticBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* world = ((CCPhysicsWorld*)  tolua_tousertype(tolua_S,2,0));
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  CCPhysicsBody::defaultStaticBody(world);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'defaultStaticBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createStaticBody of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_createStaticBody00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_createStaticBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* world = ((CCPhysicsWorld*)  tolua_tousertype(tolua_S,2,0));
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  CCPhysicsBody::createStaticBody(world);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createStaticBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_create00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* world = ((CCPhysicsWorld*)  tolua_tousertype(tolua_S,2,0));
  float mass = ((float)  tolua_tonumber(tolua_S,3,0));
  float moment = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  CCPhysicsBody::create(world,mass,moment);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
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

/* method: getName of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getName00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setName00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isSleeping of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_isSleeping00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_isSleeping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isSleeping'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isSleeping();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isSleeping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: activate of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_activate00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_activate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'activate'", NULL);
#endif
  {
   self->activate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'activate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sleep of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_sleep00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_sleep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sleep'", NULL);
#endif
  {
   self->sleep();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sleep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTag of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getTag00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTag'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTag();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTag of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setTag00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTag'", NULL);
#endif
  {
   self->setTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMass of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getMass00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMass'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMass();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMass of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setMass00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMass'", NULL);
#endif
  {
   self->setMass(mass);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInertia of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getInertia00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getInertia00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInertia'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getInertia();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInertia'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInertia of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setInertia00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setInertia00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float inertia = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInertia'", NULL);
#endif
  {
   self->setInertia(inertia);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInertia'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVelocity of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getVelocity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float velocityX = ((float)  tolua_tonumber(tolua_S,2,0));
  float velocityY = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVelocity'", NULL);
#endif
  {
   self->getVelocity(&velocityX,&velocityY);
   tolua_pushnumber(tolua_S,(lua_Number)velocityX);
   tolua_pushnumber(tolua_S,(lua_Number)velocityY);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVelocity of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float velocityX = ((float)  tolua_tonumber(tolua_S,2,0));
  float velocityY = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVelocity'", NULL);
#endif
  {
   self->setVelocity(velocityX,velocityY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVelocity of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPoint velocity = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVelocity'", NULL);
#endif
  {
   self->setVelocity(velocity);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVelocity of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity02
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* velocity = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVelocity'", NULL);
#endif
  {
   self->setVelocity(velocity);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVelocityLimit of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getVelocityLimit00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getVelocityLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVelocityLimit'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getVelocityLimit();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVelocityLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVelocityLimit of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocityLimit00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocityLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float limit = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVelocityLimit'", NULL);
#endif
  {
   self->setVelocityLimit(limit);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVelocityLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAngleVelocity of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getAngleVelocity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getAngleVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAngleVelocity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getAngleVelocity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAngleVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAngleVelocity of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setAngleVelocity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setAngleVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float velocity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAngleVelocity'", NULL);
#endif
  {
   self->setAngleVelocity(velocity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAngleVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAngleVelocityLimit of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getAngleVelocityLimit00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getAngleVelocityLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAngleVelocityLimit'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getAngleVelocityLimit();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAngleVelocityLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAngleVelocityLimit of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setAngleVelocityLimit00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setAngleVelocityLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float limit = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAngleVelocityLimit'", NULL);
#endif
  {
   self->setAngleVelocityLimit(limit);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAngleVelocityLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getForce of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getForce00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float forceX = ((float)  tolua_tonumber(tolua_S,2,0));
  float forceY = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getForce'", NULL);
#endif
  {
   self->getForce(&forceX,&forceY);
   tolua_pushnumber(tolua_S,(lua_Number)forceX);
   tolua_pushnumber(tolua_S,(lua_Number)forceY);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setForce of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float forceX = ((float)  tolua_tonumber(tolua_S,2,0));
  float forceY = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setForce'", NULL);
#endif
  {
   self->setForce(forceX,forceY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setForce of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPoint force = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setForce'", NULL);
#endif
  {
   self->setForce(force);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setForce of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce02
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* force = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setForce'", NULL);
#endif
  {
   self->setForce(force);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTorque of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getTorque00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTorque'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getTorque();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTorque of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setTorque00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float force = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTorque'", NULL);
#endif
  {
   self->setTorque(force);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetForces of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_resetForces00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_resetForces00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetForces'", NULL);
#endif
  {
   self->resetForces();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetForces'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: applyForce of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float forceX = ((float)  tolua_tonumber(tolua_S,2,0));
  float forceY = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,4,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyForce'", NULL);
#endif
  {
   self->applyForce(forceX,forceY,offsetX,offsetY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'applyForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: applyForce of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPoint force = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyForce'", NULL);
#endif
  {
   self->applyForce(force,offsetX,offsetY);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: applyForce of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce02
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* force = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyForce'", NULL);
#endif
  {
   self->applyForce(force,offsetX,offsetY);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: applyImpulse of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float forceX = ((float)  tolua_tonumber(tolua_S,2,0));
  float forceY = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,4,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyImpulse'", NULL);
#endif
  {
   self->applyImpulse(forceX,forceY,offsetX,offsetY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'applyImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: applyImpulse of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPoint force = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyImpulse'", NULL);
#endif
  {
   self->applyImpulse(force,offsetX,offsetY);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: applyImpulse of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse02
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* force = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyImpulse'", NULL);
#endif
  {
   self->applyImpulse(force,offsetX,offsetY);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getPosition00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   self->getPosition(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPositionX of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getPositionX00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getPositionX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPositionX'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getPositionX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPositionX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPositionY of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getPositionY00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getPositionY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPositionY'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getPositionY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPositionY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPosition00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(x,y);
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

/* method: setPosition of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPosition01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPosition01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPoint pos = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(pos);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPosition00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPositionX of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPositionX00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPositionX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPositionX'", NULL);
#endif
  {
   self->setPositionX(x);
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

/* method: setPositionY of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPositionY00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPositionY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float y = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPositionY'", NULL);
#endif
  {
   self->setPositionY(y);
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

/* method: getAngle of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getAngle00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAngle'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getAngle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAngle of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setAngle00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAngle'", NULL);
#endif
  {
   self->setAngle(angle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotation of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getRotation00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotation'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRotation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotation of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setRotation00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float rotation = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotation'", NULL);
#endif
  {
   self->setRotation(rotation);
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

/* method: getElasticity of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getElasticity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getElasticity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getElasticity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getElasticity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getElasticity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setElasticity of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setElasticity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setElasticity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float elasticity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setElasticity'", NULL);
#endif
  {
   self->setElasticity(elasticity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setElasticity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFriction of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getFriction00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getFriction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFriction'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getFriction();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFriction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFriction of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setFriction00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setFriction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float friction = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFriction'", NULL);
#endif
  {
   self->setFriction(friction);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFriction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isSensor of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_isSensor00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_isSensor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isSensor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isSensor();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsSensor of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setIsSensor00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setIsSensor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  bool isSensor = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsSensor'", NULL);
#endif
  {
   self->setIsSensor(isSensor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCollisionType of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getCollisionType00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getCollisionType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCollisionType'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCollisionType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCollisionType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionType of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setCollisionType00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setCollisionType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionType'", NULL);
#endif
  {
   self->setCollisionType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCollisionGroup of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getCollisionGroup00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getCollisionGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCollisionGroup'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCollisionGroup();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCollisionGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionGroup of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setCollisionGroup00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setCollisionGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  int group = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionGroup'", NULL);
#endif
  {
   self->setCollisionGroup(group);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCollisionLayers of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getCollisionLayers00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getCollisionLayers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCollisionLayers'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCollisionLayers();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCollisionLayers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionLayers of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setCollisionLayers00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setCollisionLayers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  int layers = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionLayers'", NULL);
#endif
  {
   self->setCollisionLayers(layers);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionLayers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dist of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_dist00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_dist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* other = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dist'", NULL);
#endif
  {
   float tolua_ret = (float)  self->dist(other);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: bind of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_bind00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_bind00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bind'", NULL);
#endif
  {
   self->bind(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bind'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unbind of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_unbind00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_unbind00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unbind'", NULL);
#endif
  {
   self->unbind();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unbind'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNode of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getNode00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getNode();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addSegmentShape of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addSegmentShape00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addSegmentShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPoint lowerLeft = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCPoint lowerRight = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  float thickness = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSegmentShape'", NULL);
#endif
  {
   CCPhysicsShape* tolua_ret = (CCPhysicsShape*)  self->addSegmentShape(lowerLeft,lowerRight,thickness);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsShape");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSegmentShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addCircleShape of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addCircleShape00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addCircleShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addCircleShape'", NULL);
#endif
  {
   CCPhysicsShape* tolua_ret = (CCPhysicsShape*)  self->addCircleShape(radius,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsShape");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addCircleShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBoxShape of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addBoxShape00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addBoxShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,4,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBoxShape'", NULL);
#endif
  {
   CCPhysicsShape* tolua_ret = (CCPhysicsShape*)  self->addBoxShape(width,height,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsShape");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addBoxShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addPolygonShape of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addPolygonShape00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addPolygonShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPointArray",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPointArray* vertexes = ((CCPointArray*)  tolua_tousertype(tolua_S,2,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPolygonShape'", NULL);
#endif
  {
   CCPhysicsShape* tolua_ret = (CCPhysicsShape*)  self->addPolygonShape(vertexes,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsShape");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addPolygonShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addPolygonShape of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addPolygonShape01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addPolygonShape01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  int vertexes = ((int)  tolua_tonumber(tolua_S,2,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPolygonShape'", NULL);
#endif
  {
   CCPhysicsShape* tolua_ret = (CCPhysicsShape*)  self->addPolygonShape(vertexes,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsShape");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addPolygonShape00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeShapeAtIndex of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeShapeAtIndex00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeShapeAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeShapeAtIndex'", NULL);
#endif
  {
   self->removeShapeAtIndex(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeShapeAtIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeShape of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeShape00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsShape* shapeObject = ((CCPhysicsShape*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeShape'", NULL);
#endif
  {
   self->removeShape(shapeObject);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllShape of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeAllShape00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeAllShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllShape'", NULL);
#endif
  {
   self->removeAllShape();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pinJoint of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pinJoint00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pinJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* otherBody = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pinJoint'", NULL);
#endif
  {
   CCPinJoint* tolua_ret = (CCPinJoint*)  self->pinJoint(otherBody);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCPinJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pinJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pinJoint of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pinJoint01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pinJoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* otherBody = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
  CCPhysicsVector* archrThis = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,3,0));
  CCPhysicsVector* archrOther = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pinJoint'", NULL);
#endif
  {
   CCPinJoint* tolua_ret = (CCPinJoint*)  self->pinJoint(otherBody,archrThis,archrOther);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCPinJoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pinJoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: dampedSpringJoint of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_dampedSpringJoint00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_dampedSpringJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* otherBody = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
  float restLength = ((float)  tolua_tonumber(tolua_S,3,0));
  float stiffness = ((float)  tolua_tonumber(tolua_S,4,0));
  float damping = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dampedSpringJoint'", NULL);
#endif
  {
   CCDampedSpringJoint* tolua_ret = (CCDampedSpringJoint*)  self->dampedSpringJoint(otherBody,restLength,stiffness,damping);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDampedSpringJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dampedSpringJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dampedSpringJoint of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_dampedSpringJoint01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_dampedSpringJoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* otherBody = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
  CCPhysicsVector* archrThis = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,3,0));
  CCPhysicsVector* archrOther = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,4,0));
  float restLength = ((float)  tolua_tonumber(tolua_S,5,0));
  float stiffness = ((float)  tolua_tonumber(tolua_S,6,0));
  float damping = ((float)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dampedSpringJoint'", NULL);
#endif
  {
   CCDampedSpringJoint* tolua_ret = (CCDampedSpringJoint*)  self->dampedSpringJoint(otherBody,archrThis,archrOther,restLength,stiffness,damping);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDampedSpringJoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_dampedSpringJoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: slideJoint of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_slideJoint00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_slideJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* otherBody = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
  float min = ((float)  tolua_tonumber(tolua_S,3,0));
  float max = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'slideJoint'", NULL);
#endif
  {
   CCSlideJoint* tolua_ret = (CCSlideJoint*)  self->slideJoint(otherBody,min,max);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSlideJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'slideJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: slideJoint of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_slideJoint01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_slideJoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* otherBody = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
  CCPhysicsVector* archrThis = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,3,0));
  CCPhysicsVector* archrOther = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,4,0));
  float min = ((float)  tolua_tonumber(tolua_S,5,0));
  float max = ((float)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'slideJoint'", NULL);
#endif
  {
   CCSlideJoint* tolua_ret = (CCSlideJoint*)  self->slideJoint(otherBody,archrThis,archrOther,min,max);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSlideJoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_slideJoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: pivotJoint of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* otherBody = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pivotJoint'", NULL);
#endif
  {
   CCPivotJoint* tolua_ret = (CCPivotJoint*)  self->pivotJoint(otherBody);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCPivotJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pivotJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pivotJoint of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* otherBody = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
  CCPhysicsVector* archrThis = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,3,0));
  CCPhysicsVector* archrOther = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pivotJoint'", NULL);
#endif
  {
   CCPivotJoint* tolua_ret = (CCPivotJoint*)  self->pivotJoint(otherBody,archrThis,archrOther);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCPivotJoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: pivotJoint of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint02
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* otherBody = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
  CCPhysicsVector* pivot = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pivotJoint'", NULL);
#endif
  {
   CCPivotJoint* tolua_ret = (CCPivotJoint*)  self->pivotJoint(otherBody,pivot);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCPivotJoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getJointsWith of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getJointsWith00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getJointsWith00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsBody* otherBody = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getJointsWith'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getJointsWith(otherBody);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getJointsWith'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: breakAllJoints of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_breakAllJoints00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_breakAllJoints00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'breakAllJoints'", NULL);
#endif
  {
   self->breakAllJoints();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'breakAllJoints'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: breakJointByType of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_breakJointByType00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_breakJointByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  JointType jointType = ((JointType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'breakJointByType'", NULL);
#endif
  {
   self->breakJointByType(jointType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'breakJointByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSelf of class  CCPhysicsBody */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeSelf00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeSelf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  bool unbind = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSelf'", NULL);
#endif
  {
   self->removeSelf(unbind);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSelf'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getElasticity of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getElasticity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getElasticity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getElasticity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getElasticity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getElasticity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setElasticity of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setElasticity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setElasticity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
  float elasticity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setElasticity'", NULL);
#endif
  {
   self->setElasticity(elasticity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setElasticity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFriction of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getFriction00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getFriction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFriction'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getFriction();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFriction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFriction of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setFriction00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setFriction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
  float friction = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFriction'", NULL);
#endif
  {
   self->setFriction(friction);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFriction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isSensor of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_isSensor00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_isSensor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isSensor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isSensor();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsSensor of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setIsSensor00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setIsSensor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
  bool isSensor = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsSensor'", NULL);
#endif
  {
   self->setIsSensor(isSensor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCollisionType of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getCollisionType00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getCollisionType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCollisionType'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCollisionType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCollisionType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionType of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setCollisionType00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setCollisionType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
  int collisionType = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionType'", NULL);
#endif
  {
   self->setCollisionType(collisionType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCollisionGroup of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getCollisionGroup00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getCollisionGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCollisionGroup'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCollisionGroup();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCollisionGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionGroup of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setCollisionGroup00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setCollisionGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
  int group = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionGroup'", NULL);
#endif
  {
   self->setCollisionGroup(group);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCollisionLayers of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getCollisionLayers00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getCollisionLayers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCollisionLayers'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCollisionLayers();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCollisionLayers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionLayers of class  CCPhysicsShape */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setCollisionLayers00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setCollisionLayers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsShape* self = (CCPhysicsShape*)  tolua_tousertype(tolua_S,1,0);
  int layers = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionLayers'", NULL);
#endif
  {
   self->setCollisionLayers(layers);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionLayers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBodyA of class  CCJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCJoint_getBodyA00
static int tolua_CCPhysicsWorld_luabinding_CCJoint_getBodyA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCJoint* self = (CCJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBodyA'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->getBodyA();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBodyA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBodyB of class  CCJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCJoint_getBodyB00
static int tolua_CCPhysicsWorld_luabinding_CCJoint_getBodyB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCJoint* self = (CCJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBodyB'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->getBodyB();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBodyB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getJointType of class  CCJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCJoint_getJointType00
static int tolua_CCPhysicsWorld_luabinding_CCJoint_getJointType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCJoint* self = (CCJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getJointType'", NULL);
#endif
  {
   JointType tolua_ret = (JointType)  self->getJointType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getJointType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getConstraint of class  CCJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCJoint_getConstraint00
static int tolua_CCPhysicsWorld_luabinding_CCJoint_getConstraint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCJoint* self = (CCJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getConstraint'", NULL);
#endif
  {
   cpConstraint* tolua_ret = (cpConstraint*)  self->getConstraint();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"cpConstraint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getConstraint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: breakJoint of class  CCJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCJoint_breakJoint00
static int tolua_CCPhysicsWorld_luabinding_CCJoint_breakJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCJoint* self = (CCJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'breakJoint'", NULL);
#endif
  {
   self->breakJoint();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'breakJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDist of class  CCPinJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPinJoint_getDist00
static int tolua_CCPhysicsWorld_luabinding_CCPinJoint_getDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPinJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPinJoint* self = (CCPinJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDist'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDist();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDist of class  CCPinJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPinJoint_setDist00
static int tolua_CCPhysicsWorld_luabinding_CCPinJoint_setDist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPinJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPinJoint* self = (CCPinJoint*)  tolua_tousertype(tolua_S,1,0);
  float dist = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDist'", NULL);
#endif
  {
   self->setDist(dist);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchrA of class  CCPinJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPinJoint_getAnchrA00
static int tolua_CCPhysicsWorld_luabinding_CCPinJoint_getAnchrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPinJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPinJoint* self = (CCPinJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchrA'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getAnchrA();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchrA of class  CCPinJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPinJoint_setAnchrA00
static int tolua_CCPhysicsWorld_luabinding_CCPinJoint_setAnchrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPinJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPinJoint* self = (CCPinJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* anchrA = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchrA'", NULL);
#endif
  {
   self->setAnchrA(anchrA);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchrB of class  CCPinJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPinJoint_getAnchrB00
static int tolua_CCPhysicsWorld_luabinding_CCPinJoint_getAnchrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPinJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPinJoint* self = (CCPinJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchrB'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getAnchrB();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchrB of class  CCPinJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPinJoint_setAnchrB00
static int tolua_CCPhysicsWorld_luabinding_CCPinJoint_setAnchrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPinJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPinJoint* self = (CCPinJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* anchrB = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchrB'", NULL);
#endif
  {
   self->setAnchrB(anchrB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchrA of class  CCDampedSpringJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_getAnchrA00
static int tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_getAnchrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDampedSpringJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDampedSpringJoint* self = (CCDampedSpringJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchrA'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getAnchrA();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchrA of class  CCDampedSpringJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_setAnchrA00
static int tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_setAnchrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDampedSpringJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDampedSpringJoint* self = (CCDampedSpringJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* anchrA = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchrA'", NULL);
#endif
  {
   self->setAnchrA(anchrA);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchrB of class  CCDampedSpringJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_getAnchrB00
static int tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_getAnchrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDampedSpringJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDampedSpringJoint* self = (CCDampedSpringJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchrB'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getAnchrB();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchrB of class  CCDampedSpringJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_setAnchrB00
static int tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_setAnchrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDampedSpringJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDampedSpringJoint* self = (CCDampedSpringJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* anchrB = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchrB'", NULL);
#endif
  {
   self->setAnchrB(anchrB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchrA of class  CCSlideJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getAnchrA00
static int tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getAnchrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSlideJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSlideJoint* self = (CCSlideJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchrA'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getAnchrA();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchrA of class  CCSlideJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setAnchrA00
static int tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setAnchrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSlideJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSlideJoint* self = (CCSlideJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* anchrA = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchrA'", NULL);
#endif
  {
   self->setAnchrA(anchrA);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchrB of class  CCSlideJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getAnchrB00
static int tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getAnchrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSlideJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSlideJoint* self = (CCSlideJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchrB'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getAnchrB();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchrB of class  CCSlideJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setAnchrB00
static int tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setAnchrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSlideJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSlideJoint* self = (CCSlideJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* anchrB = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchrB'", NULL);
#endif
  {
   self->setAnchrB(anchrB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMin of class  CCSlideJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getMin00
static int tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getMin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSlideJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSlideJoint* self = (CCSlideJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMin'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMin();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMin of class  CCSlideJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setMin00
static int tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setMin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSlideJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSlideJoint* self = (CCSlideJoint*)  tolua_tousertype(tolua_S,1,0);
  float min = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMin'", NULL);
#endif
  {
   self->setMin(min);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMax of class  CCSlideJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getMax00
static int tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getMax00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSlideJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSlideJoint* self = (CCSlideJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMax'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMax();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMax'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMax of class  CCSlideJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setMax00
static int tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setMax00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSlideJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSlideJoint* self = (CCSlideJoint*)  tolua_tousertype(tolua_S,1,0);
  float max = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMax'", NULL);
#endif
  {
   self->setMax(max);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMax'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchrA of class  CCPivotJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPivotJoint_getAnchrA00
static int tolua_CCPhysicsWorld_luabinding_CCPivotJoint_getAnchrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPivotJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPivotJoint* self = (CCPivotJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchrA'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getAnchrA();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchrA of class  CCPivotJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPivotJoint_setAnchrA00
static int tolua_CCPhysicsWorld_luabinding_CCPivotJoint_setAnchrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPivotJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPivotJoint* self = (CCPivotJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* anchrA = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchrA'", NULL);
#endif
  {
   self->setAnchrA(anchrA);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchrB of class  CCPivotJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPivotJoint_getAnchrB00
static int tolua_CCPhysicsWorld_luabinding_CCPivotJoint_getAnchrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPivotJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPivotJoint* self = (CCPivotJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchrB'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getAnchrB();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchrB of class  CCPivotJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPivotJoint_setAnchrB00
static int tolua_CCPhysicsWorld_luabinding_CCPivotJoint_setAnchrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPivotJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPivotJoint* self = (CCPivotJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* anchrB = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchrB'", NULL);
#endif
  {
   self->setAnchrB(anchrB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGrooveA of class  CCGrooveJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getGrooveA00
static int tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getGrooveA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrooveJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrooveJoint* self = (CCGrooveJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGrooveA'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getGrooveA();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGrooveA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGrooveA of class  CCGrooveJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setGrooveA00
static int tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setGrooveA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrooveJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrooveJoint* self = (CCGrooveJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* grooveA = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGrooveA'", NULL);
#endif
  {
   self->setGrooveA(grooveA);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGrooveA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGrooveB of class  CCGrooveJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getGrooveB00
static int tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getGrooveB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrooveJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrooveJoint* self = (CCGrooveJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGrooveB'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getGrooveB();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGrooveB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGrooveB of class  CCGrooveJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setGrooveB00
static int tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setGrooveB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrooveJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrooveJoint* self = (CCGrooveJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* grooveB = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGrooveB'", NULL);
#endif
  {
   self->setGrooveB(grooveB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGrooveB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchrA of class  CCGrooveJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getAnchrA00
static int tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getAnchrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrooveJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrooveJoint* self = (CCGrooveJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchrA'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getAnchrA();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchrA of class  CCGrooveJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setAnchrA00
static int tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setAnchrA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrooveJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrooveJoint* self = (CCGrooveJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* anchrA = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchrA'", NULL);
#endif
  {
   self->setAnchrA(anchrA);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchrA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchrB of class  CCGrooveJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getAnchrB00
static int tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getAnchrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrooveJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrooveJoint* self = (CCGrooveJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchrB'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->getAnchrB();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnchrB of class  CCGrooveJoint */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setAnchrB00
static int tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setAnchrB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrooveJoint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrooveJoint* self = (CCGrooveJoint*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* anchrB = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnchrB'", NULL);
#endif
  {
   self->setAnchrB(anchrB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnchrB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorld of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getWorld00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorld'", NULL);
#endif
  {
   CCPhysicsWorld* tolua_ret = (CCPhysicsWorld*)  self->getWorld();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsWorld");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBody1 of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getBody100
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getBody100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBody1'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->getBody1();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBody1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBody2 of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getBody200
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getBody200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBody2'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->getBody2();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBody2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isFirstContact of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_isFirstContact00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_isFirstContact00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isFirstContact'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isFirstContact();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isFirstContact'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getElasticity of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getElasticity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getElasticity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getElasticity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getElasticity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getElasticity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setElasticity of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setElasticity00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setElasticity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  float elasticity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setElasticity'", NULL);
#endif
  {
   self->setElasticity(elasticity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setElasticity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFriction of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getFriction00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getFriction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFriction'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getFriction();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFriction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFriction of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setFriction00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setFriction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  float friction = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFriction'", NULL);
#endif
  {
   self->setFriction(friction);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFriction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSurfaceVelocities of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getSurfaceVelocities00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getSurfaceVelocities00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSurfaceVelocities'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->getSurfaceVelocities();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSurfaceVelocities'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSurfaceVelocities of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getSurfaceVelocities01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getSurfaceVelocities01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  float velocityX = ((float)  tolua_tonumber(tolua_S,2,0));
  float velocityY = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSurfaceVelocities'", NULL);
#endif
  {
   self->getSurfaceVelocities(&velocityX,&velocityY);
   tolua_pushnumber(tolua_S,(lua_Number)velocityX);
   tolua_pushnumber(tolua_S,(lua_Number)velocityY);
  }
 }
 return 2;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getSurfaceVelocities00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSurfaceVelocities of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setSurfaceVelocities00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setSurfaceVelocities00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  float velocityX = ((float)  tolua_tonumber(tolua_S,2,0));
  float velocityY = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSurfaceVelocities'", NULL);
#endif
  {
   self->setSurfaceVelocities(velocityX,velocityY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSurfaceVelocities'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSurfaceVelocities of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setSurfaceVelocities01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setSurfaceVelocities01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  CCPoint velocity = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSurfaceVelocities'", NULL);
#endif
  {
   self->setSurfaceVelocities(velocity);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setSurfaceVelocities00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCount of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getCount00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNormal of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getNormal00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getNormal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNormal'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->getNormal(index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNormal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNormal of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getNormal01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getNormal01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNormal'", NULL);
#endif
  {
   self->getNormal(index,&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getNormal00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPoint of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getPoint00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPoint'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->getPoint(index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPoint of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getPoint01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getPoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPoint'", NULL);
#endif
  {
   self->getPoint(index,&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getPoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDepth of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getDepth00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getDepth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDepth'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDepth(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDepth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUserData of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getUserData00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getUserData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUserData'", NULL);
#endif
  {
   void* tolua_ret = (void*)  self->getUserData();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUserData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUserData of class  CCPhysicsCollisionEvent */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setUserData00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setUserData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsCollisionEvent",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsCollisionEvent* self = (CCPhysicsCollisionEvent*)  tolua_tousertype(tolua_S,1,0);
  void* userdata = ((void*)  tolua_touserdata(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUserData'", NULL);
#endif
  {
   self->setUserData(userdata);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUserData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_create00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  CCPhysicsVector::create(x,y);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
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

/* method: create of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_create01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPoint vector = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  CCPhysicsVector::create(vector);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createForAngle of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_createForAngle00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_createForAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  CCPhysicsVector::createForAngle(angle);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createForAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createForRotation of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_createForRotation00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_createForRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float degrees = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  CCPhysicsVector::createForRotation(degrees);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createForRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getValue of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_getValue00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_getValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getValue'", NULL);
#endif
  {
   self->getValue(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: equal of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_equal00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_equal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'equal'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->equal(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'equal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: equal of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_equal01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_equal01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* other = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'equal'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->equal(other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_equal00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: add of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_add00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'add'", NULL);
#endif
  {
   self->add(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: add of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_add01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* other = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'add'", NULL);
#endif
  {
   self->add(other);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: sub of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_sub00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sub'", NULL);
#endif
  {
   self->sub(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sub of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_sub01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* other = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sub'", NULL);
#endif
  {
   self->sub(other);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: negate of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_negate00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_negate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'negate'", NULL);
#endif
  {
   self->negate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'negate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: multi of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_multi00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_multi00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'multi'", NULL);
#endif
  {
   self->multi(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'multi'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dot of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dot00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dot'", NULL);
#endif
  {
   float tolua_ret = (float)  self->dot(x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dot of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dot01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dot01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* other = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dot'", NULL);
#endif
  {
   float tolua_ret = (float)  self->dot(other);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dot00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: cross of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_cross00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_cross00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cross'", NULL);
#endif
  {
   float tolua_ret = (float)  self->cross(x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cross'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cross of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_cross01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_cross01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* other = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cross'", NULL);
#endif
  {
   float tolua_ret = (float)  self->cross(other);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_cross00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: perp of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_perp00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_perp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'perp'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->perp();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'perp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rperp of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rperp00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rperp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rperp'", NULL);
#endif
  {
   CCPhysicsVector* tolua_ret = (CCPhysicsVector*)  self->rperp();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rperp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotate of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rotate00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotate'", NULL);
#endif
  {
   self->rotate(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotate of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rotate01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rotate01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* other = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotate'", NULL);
#endif
  {
   self->rotate(other);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rotate00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: length of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_length00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'length'", NULL);
#endif
  {
   float tolua_ret = (float)  self->length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: lengthsq of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_lengthsq00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_lengthsq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'lengthsq'", NULL);
#endif
  {
   float tolua_ret = (float)  self->lengthsq();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'lengthsq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dist of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dist00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dist'", NULL);
#endif
  {
   float tolua_ret = (float)  self->dist(x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dist of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dist01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dist01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* other = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dist'", NULL);
#endif
  {
   float tolua_ret = (float)  self->dist(other);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dist00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: distsq of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_distsq00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_distsq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'distsq'", NULL);
#endif
  {
   float tolua_ret = (float)  self->distsq(x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'distsq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: distsq of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_distsq01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_distsq01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
  CCPhysicsVector* other = ((CCPhysicsVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'distsq'", NULL);
#endif
  {
   float tolua_ret = (float)  self->distsq(other);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_distsq00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: angle of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_angle00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_angle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'angle'", NULL);
#endif
  {
   float tolua_ret = (float)  self->angle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'angle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rotation of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rotation00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rotation'", NULL);
#endif
  {
   float tolua_ret = (float)  self->rotation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sum of class  CCPhysicsVector */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_sum00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_sum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsVector* self = (CCPhysicsVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sum'", NULL);
#endif
  {
   float tolua_ret = (float)  self->sum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCPhysicsWorld_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CCPhysicsWorld","CCPhysicsWorld","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCPhysicsWorld");
   tolua_function(tolua_S,"create",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_create00);
   tolua_function(tolua_S,"create",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_create01);
   tolua_function(tolua_S,"createDebugNode",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createDebugNode00);
   tolua_function(tolua_S,"getGravity",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getGravity00);
   tolua_function(tolua_S,"setGravity",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_setGravity00);
   tolua_function(tolua_S,"getDamping",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getDamping00);
   tolua_function(tolua_S,"setDamping",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_setDamping00);
   tolua_function(tolua_S,"getIdleSpeedThreshold",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getIdleSpeedThreshold00);
   tolua_function(tolua_S,"setIdleSpeedThreshold",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_setIdleSpeedThreshold00);
   tolua_function(tolua_S,"createCircleBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createCircleBody00);
   tolua_function(tolua_S,"createBoxBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createBoxBody00);
   tolua_function(tolua_S,"createPolygonBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createPolygonBody00);
   tolua_function(tolua_S,"createPolygonBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_createPolygonBody01);
   tolua_function(tolua_S,"getAllBodies",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getAllBodies00);
   tolua_function(tolua_S,"addBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addBody00);
   tolua_function(tolua_S,"getBodyByTag",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getBodyByTag00);
   tolua_function(tolua_S,"removeBodyByTag",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeBodyByTag00);
   tolua_function(tolua_S,"removeBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeBody00);
   tolua_function(tolua_S,"removeAllBodies",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeAllBodies00);
   tolua_function(tolua_S,"start",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_start00);
   tolua_function(tolua_S,"stop",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_stop00);
   tolua_function(tolua_S,"step",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_step00);
   tolua_function(tolua_S,"addCollisionScriptListener",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addCollisionScriptListener00);
   tolua_function(tolua_S,"removeCollisionScriptListener",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeCollisionScriptListener00);
   tolua_function(tolua_S,"removeAllCollisionListeners",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_removeAllCollisionListeners00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPhysicsBody","CCPhysicsBody","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CCPhysicsBody");
   tolua_function(tolua_S,"defaultStaticBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_defaultStaticBody00);
   tolua_function(tolua_S,"createStaticBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_createStaticBody00);
   tolua_function(tolua_S,"create",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_create00);
   tolua_function(tolua_S,"getName",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getName00);
   tolua_function(tolua_S,"setName",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setName00);
   tolua_function(tolua_S,"isSleeping",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_isSleeping00);
   tolua_function(tolua_S,"activate",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_activate00);
   tolua_function(tolua_S,"sleep",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_sleep00);
   tolua_function(tolua_S,"getTag",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getTag00);
   tolua_function(tolua_S,"setTag",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setTag00);
   tolua_function(tolua_S,"getMass",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getMass00);
   tolua_function(tolua_S,"setMass",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setMass00);
   tolua_function(tolua_S,"getInertia",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getInertia00);
   tolua_function(tolua_S,"setInertia",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setInertia00);
   tolua_function(tolua_S,"getVelocity",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getVelocity00);
   tolua_function(tolua_S,"setVelocity",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity00);
   tolua_function(tolua_S,"setVelocity",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity01);
   tolua_function(tolua_S,"setVelocity",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocity02);
   tolua_function(tolua_S,"getVelocityLimit",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getVelocityLimit00);
   tolua_function(tolua_S,"setVelocityLimit",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setVelocityLimit00);
   tolua_function(tolua_S,"getAngleVelocity",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getAngleVelocity00);
   tolua_function(tolua_S,"setAngleVelocity",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setAngleVelocity00);
   tolua_function(tolua_S,"getAngleVelocityLimit",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getAngleVelocityLimit00);
   tolua_function(tolua_S,"setAngleVelocityLimit",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setAngleVelocityLimit00);
   tolua_function(tolua_S,"getForce",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getForce00);
   tolua_function(tolua_S,"setForce",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce00);
   tolua_function(tolua_S,"setForce",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce01);
   tolua_function(tolua_S,"setForce",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setForce02);
   tolua_function(tolua_S,"getTorque",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getTorque00);
   tolua_function(tolua_S,"setTorque",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setTorque00);
   tolua_function(tolua_S,"resetForces",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_resetForces00);
   tolua_function(tolua_S,"applyForce",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce00);
   tolua_function(tolua_S,"applyForce",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce01);
   tolua_function(tolua_S,"applyForce",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyForce02);
   tolua_function(tolua_S,"applyImpulse",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse00);
   tolua_function(tolua_S,"applyImpulse",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse01);
   tolua_function(tolua_S,"applyImpulse",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_applyImpulse02);
   tolua_function(tolua_S,"getPosition",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getPosition00);
   tolua_function(tolua_S,"getPositionX",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getPositionX00);
   tolua_function(tolua_S,"getPositionY",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getPositionY00);
   tolua_function(tolua_S,"setPosition",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPosition00);
   tolua_function(tolua_S,"setPosition",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPosition01);
   tolua_function(tolua_S,"setPositionX",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPositionX00);
   tolua_function(tolua_S,"setPositionY",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPositionY00);
   tolua_function(tolua_S,"getAngle",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getAngle00);
   tolua_function(tolua_S,"setAngle",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setAngle00);
   tolua_function(tolua_S,"getRotation",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getRotation00);
   tolua_function(tolua_S,"setRotation",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setRotation00);
   tolua_function(tolua_S,"getElasticity",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getElasticity00);
   tolua_function(tolua_S,"setElasticity",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setElasticity00);
   tolua_function(tolua_S,"getFriction",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getFriction00);
   tolua_function(tolua_S,"setFriction",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setFriction00);
   tolua_function(tolua_S,"isSensor",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_isSensor00);
   tolua_function(tolua_S,"setIsSensor",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setIsSensor00);
   tolua_function(tolua_S,"getCollisionType",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getCollisionType00);
   tolua_function(tolua_S,"setCollisionType",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setCollisionType00);
   tolua_function(tolua_S,"getCollisionGroup",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getCollisionGroup00);
   tolua_function(tolua_S,"setCollisionGroup",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setCollisionGroup00);
   tolua_function(tolua_S,"getCollisionLayers",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getCollisionLayers00);
   tolua_function(tolua_S,"setCollisionLayers",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setCollisionLayers00);
   tolua_function(tolua_S,"dist",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_dist00);
   tolua_function(tolua_S,"bind",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_bind00);
   tolua_function(tolua_S,"unbind",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_unbind00);
   tolua_function(tolua_S,"getNode",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getNode00);
   tolua_function(tolua_S,"addSegmentShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addSegmentShape00);
   tolua_function(tolua_S,"addCircleShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addCircleShape00);
   tolua_function(tolua_S,"addBoxShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addBoxShape00);
   tolua_function(tolua_S,"addPolygonShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addPolygonShape00);
   tolua_function(tolua_S,"addPolygonShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addPolygonShape01);
   tolua_function(tolua_S,"removeShapeAtIndex",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeShapeAtIndex00);
   tolua_function(tolua_S,"removeShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeShape00);
   tolua_function(tolua_S,"removeAllShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeAllShape00);
   tolua_function(tolua_S,"pinJoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pinJoint00);
   tolua_function(tolua_S,"pinJoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pinJoint01);
   tolua_function(tolua_S,"dampedSpringJoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_dampedSpringJoint00);
   tolua_function(tolua_S,"dampedSpringJoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_dampedSpringJoint01);
   tolua_function(tolua_S,"slideJoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_slideJoint00);
   tolua_function(tolua_S,"slideJoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_slideJoint01);
   tolua_function(tolua_S,"pivotJoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint00);
   tolua_function(tolua_S,"pivotJoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint01);
   tolua_function(tolua_S,"pivotJoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_pivotJoint02);
   tolua_function(tolua_S,"getJointsWith",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_getJointsWith00);
   tolua_function(tolua_S,"breakAllJoints",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_breakAllJoints00);
   tolua_function(tolua_S,"breakJointByType",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_breakJointByType00);
   tolua_function(tolua_S,"removeSelf",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeSelf00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPhysicsShape","CCPhysicsShape","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CCPhysicsShape");
   tolua_function(tolua_S,"getElasticity",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getElasticity00);
   tolua_function(tolua_S,"setElasticity",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setElasticity00);
   tolua_function(tolua_S,"getFriction",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getFriction00);
   tolua_function(tolua_S,"setFriction",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setFriction00);
   tolua_function(tolua_S,"isSensor",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_isSensor00);
   tolua_function(tolua_S,"setIsSensor",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setIsSensor00);
   tolua_function(tolua_S,"getCollisionType",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getCollisionType00);
   tolua_function(tolua_S,"setCollisionType",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setCollisionType00);
   tolua_function(tolua_S,"getCollisionGroup",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getCollisionGroup00);
   tolua_function(tolua_S,"setCollisionGroup",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setCollisionGroup00);
   tolua_function(tolua_S,"getCollisionLayers",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getCollisionLayers00);
   tolua_function(tolua_S,"setCollisionLayers",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setCollisionLayers00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"UNKNOWN",UNKNOWN);
  tolua_constant(tolua_S,"PIN_JOINT",PIN_JOINT);
  tolua_constant(tolua_S,"SLIDE_JOINT",SLIDE_JOINT);
  tolua_constant(tolua_S,"PIVOT_JOINT",PIVOT_JOINT);
  tolua_constant(tolua_S,"GROOVE_JOINT",GROOVE_JOINT);
  tolua_constant(tolua_S,"DAMPED_SPRING",DAMPED_SPRING);
  tolua_constant(tolua_S,"DAMPED_ROTARY_SPRING",DAMPED_ROTARY_SPRING);
  tolua_constant(tolua_S,"ROTARY_LIMIT",ROTARY_LIMIT);
  tolua_constant(tolua_S,"RATCHET_JOINT",RATCHET_JOINT);
  tolua_constant(tolua_S,"GEAR_JOINT",GEAR_JOINT);
  tolua_constant(tolua_S,"SIMPLE_MOTOR",SIMPLE_MOTOR);
  tolua_cclass(tolua_S,"CCJoint","CCJoint","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CCJoint");
   tolua_function(tolua_S,"getBodyA",tolua_CCPhysicsWorld_luabinding_CCJoint_getBodyA00);
   tolua_function(tolua_S,"getBodyB",tolua_CCPhysicsWorld_luabinding_CCJoint_getBodyB00);
   tolua_function(tolua_S,"getJointType",tolua_CCPhysicsWorld_luabinding_CCJoint_getJointType00);
   tolua_function(tolua_S,"getConstraint",tolua_CCPhysicsWorld_luabinding_CCJoint_getConstraint00);
   tolua_function(tolua_S,"breakJoint",tolua_CCPhysicsWorld_luabinding_CCJoint_breakJoint00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPinJoint","CCPinJoint","CCJoint",NULL);
  tolua_beginmodule(tolua_S,"CCPinJoint");
   tolua_function(tolua_S,"getDist",tolua_CCPhysicsWorld_luabinding_CCPinJoint_getDist00);
   tolua_function(tolua_S,"setDist",tolua_CCPhysicsWorld_luabinding_CCPinJoint_setDist00);
   tolua_function(tolua_S,"getAnchrA",tolua_CCPhysicsWorld_luabinding_CCPinJoint_getAnchrA00);
   tolua_function(tolua_S,"setAnchrA",tolua_CCPhysicsWorld_luabinding_CCPinJoint_setAnchrA00);
   tolua_function(tolua_S,"getAnchrB",tolua_CCPhysicsWorld_luabinding_CCPinJoint_getAnchrB00);
   tolua_function(tolua_S,"setAnchrB",tolua_CCPhysicsWorld_luabinding_CCPinJoint_setAnchrB00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCDampedSpringJoint","CCDampedSpringJoint","CCJoint",NULL);
  tolua_beginmodule(tolua_S,"CCDampedSpringJoint");
   tolua_function(tolua_S,"getAnchrA",tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_getAnchrA00);
   tolua_function(tolua_S,"setAnchrA",tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_setAnchrA00);
   tolua_function(tolua_S,"getAnchrB",tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_getAnchrB00);
   tolua_function(tolua_S,"setAnchrB",tolua_CCPhysicsWorld_luabinding_CCDampedSpringJoint_setAnchrB00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCSlideJoint","CCSlideJoint","CCJoint",NULL);
  tolua_beginmodule(tolua_S,"CCSlideJoint");
   tolua_function(tolua_S,"getAnchrA",tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getAnchrA00);
   tolua_function(tolua_S,"setAnchrA",tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setAnchrA00);
   tolua_function(tolua_S,"getAnchrB",tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getAnchrB00);
   tolua_function(tolua_S,"setAnchrB",tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setAnchrB00);
   tolua_function(tolua_S,"getMin",tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getMin00);
   tolua_function(tolua_S,"setMin",tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setMin00);
   tolua_function(tolua_S,"getMax",tolua_CCPhysicsWorld_luabinding_CCSlideJoint_getMax00);
   tolua_function(tolua_S,"setMax",tolua_CCPhysicsWorld_luabinding_CCSlideJoint_setMax00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPivotJoint","CCPivotJoint","CCJoint",NULL);
  tolua_beginmodule(tolua_S,"CCPivotJoint");
   tolua_function(tolua_S,"getAnchrA",tolua_CCPhysicsWorld_luabinding_CCPivotJoint_getAnchrA00);
   tolua_function(tolua_S,"setAnchrA",tolua_CCPhysicsWorld_luabinding_CCPivotJoint_setAnchrA00);
   tolua_function(tolua_S,"getAnchrB",tolua_CCPhysicsWorld_luabinding_CCPivotJoint_getAnchrB00);
   tolua_function(tolua_S,"setAnchrB",tolua_CCPhysicsWorld_luabinding_CCPivotJoint_setAnchrB00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCGrooveJoint","CCGrooveJoint","CCJoint",NULL);
  tolua_beginmodule(tolua_S,"CCGrooveJoint");
   tolua_function(tolua_S,"getGrooveA",tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getGrooveA00);
   tolua_function(tolua_S,"setGrooveA",tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setGrooveA00);
   tolua_function(tolua_S,"getGrooveB",tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getGrooveB00);
   tolua_function(tolua_S,"setGrooveB",tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setGrooveB00);
   tolua_function(tolua_S,"getAnchrA",tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getAnchrA00);
   tolua_function(tolua_S,"setAnchrA",tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setAnchrA00);
   tolua_function(tolua_S,"getAnchrB",tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_getAnchrB00);
   tolua_function(tolua_S,"setAnchrB",tolua_CCPhysicsWorld_luabinding_CCGrooveJoint_setAnchrB00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPhysicsDebugNode","CCPhysicsDebugNode","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCPhysicsDebugNode");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPhysicsCollisionEvent","CCPhysicsCollisionEvent","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CCPhysicsCollisionEvent");
   tolua_function(tolua_S,"getWorld",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getWorld00);
   tolua_function(tolua_S,"getBody1",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getBody100);
   tolua_function(tolua_S,"getBody2",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getBody200);
   tolua_function(tolua_S,"isFirstContact",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_isFirstContact00);
   tolua_function(tolua_S,"getElasticity",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getElasticity00);
   tolua_function(tolua_S,"setElasticity",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setElasticity00);
   tolua_function(tolua_S,"getFriction",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getFriction00);
   tolua_function(tolua_S,"setFriction",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setFriction00);
   tolua_function(tolua_S,"getSurfaceVelocities",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getSurfaceVelocities00);
   tolua_function(tolua_S,"getSurfaceVelocities",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getSurfaceVelocities01);
   tolua_function(tolua_S,"setSurfaceVelocities",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setSurfaceVelocities00);
   tolua_function(tolua_S,"setSurfaceVelocities",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setSurfaceVelocities01);
   tolua_function(tolua_S,"getCount",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getCount00);
   tolua_function(tolua_S,"getNormal",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getNormal00);
   tolua_function(tolua_S,"getNormal",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getNormal01);
   tolua_function(tolua_S,"getPoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getPoint00);
   tolua_function(tolua_S,"getPoint",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getPoint01);
   tolua_function(tolua_S,"getDepth",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getDepth00);
   tolua_function(tolua_S,"getUserData",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_getUserData00);
   tolua_function(tolua_S,"setUserData",tolua_CCPhysicsWorld_luabinding_CCPhysicsCollisionEvent_setUserData00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPhysicsVector","CCPhysicsVector","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CCPhysicsVector");
   tolua_function(tolua_S,"create",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_create00);
   tolua_function(tolua_S,"create",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_create01);
   tolua_function(tolua_S,"createForAngle",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_createForAngle00);
   tolua_function(tolua_S,"createForRotation",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_createForRotation00);
   tolua_function(tolua_S,"getValue",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_getValue00);
   tolua_function(tolua_S,"equal",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_equal00);
   tolua_function(tolua_S,"equal",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_equal01);
   tolua_function(tolua_S,"add",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_add00);
   tolua_function(tolua_S,"add",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_add01);
   tolua_function(tolua_S,"sub",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_sub00);
   tolua_function(tolua_S,"sub",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_sub01);
   tolua_function(tolua_S,"negate",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_negate00);
   tolua_function(tolua_S,"multi",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_multi00);
   tolua_function(tolua_S,"dot",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dot00);
   tolua_function(tolua_S,"dot",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dot01);
   tolua_function(tolua_S,"cross",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_cross00);
   tolua_function(tolua_S,"cross",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_cross01);
   tolua_function(tolua_S,"perp",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_perp00);
   tolua_function(tolua_S,"rperp",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rperp00);
   tolua_function(tolua_S,"rotate",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rotate00);
   tolua_function(tolua_S,"rotate",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rotate01);
   tolua_function(tolua_S,"length",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_length00);
   tolua_function(tolua_S,"lengthsq",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_lengthsq00);
   tolua_function(tolua_S,"dist",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dist00);
   tolua_function(tolua_S,"dist",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_dist01);
   tolua_function(tolua_S,"distsq",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_distsq00);
   tolua_function(tolua_S,"distsq",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_distsq01);
   tolua_function(tolua_S,"angle",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_angle00);
   tolua_function(tolua_S,"rotation",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_rotation00);
   tolua_function(tolua_S,"sum",tolua_CCPhysicsWorld_luabinding_CCPhysicsVector_sum00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCPhysicsWorld_luabinding (lua_State* tolua_S) {
 return tolua_CCPhysicsWorld_luabinding_open(tolua_S);
};
#endif

