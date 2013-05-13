/*
** Lua binding: PhysicsWorld_luabinding
** Generated automatically by tolua++-1.0.92 on Mon May 13 12:55:17 2013.
*/

#include "PhysicsWorld_luabinding.h"
#include "CCLuaEngine.h"

using namespace cocos2d;




#include "PhysicsShape.h"
#include "PhysicsBody.h"
#include "PhysicsWorld.h"
#include "PhysicsDebugNode.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"PhysicsDebugNode");
 tolua_usertype(tolua_S,"PhysicsWorld");
 
 tolua_usertype(tolua_S,"PhysicsBody");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"PhysicsShape");
 tolua_usertype(tolua_S,"CCPointArray");
}

/* method: create of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_create00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
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
   PhysicsWorld* tolua_ret = (PhysicsWorld*)  PhysicsWorld::create(gravityX,gravityY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PhysicsWorld");
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

/* method: create of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_create01
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   PhysicsWorld* tolua_ret = (PhysicsWorld*)  PhysicsWorld::create();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PhysicsWorld");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PhysicsWorld_luabinding_PhysicsWorld_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createDebugNode of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_createDebugNode00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_createDebugNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createDebugNode'", NULL);
#endif
  {
   PhysicsDebugNode* tolua_ret = (PhysicsDebugNode*)  self->createDebugNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsDebugNode");
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

/* method: getGravity of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_getGravity00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_getGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setGravity of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_setGravity00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_setGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
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

/* method: addCircleShape of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_addCircleShape00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_addCircleShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
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
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,4,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addCircleShape'", NULL);
#endif
  {
   PhysicsBody* tolua_ret = (PhysicsBody*)  self->addCircleShape(mass,radius,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PhysicsBody");
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

/* method: addBoxShape of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_addBoxShape00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_addBoxShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
  float height = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBoxShape'", NULL);
#endif
  {
   PhysicsBody* tolua_ret = (PhysicsBody*)  self->addBoxShape(mass,width,height);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PhysicsBody");
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

/* method: addPolygonShape of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_addPolygonShape00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_addPolygonShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
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
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
  CCPointArray* vertexes = ((CCPointArray*)  tolua_tousertype(tolua_S,3,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,4,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPolygonShape'", NULL);
#endif
  {
   PhysicsBody* tolua_ret = (PhysicsBody*)  self->addPolygonShape(mass,vertexes,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PhysicsBody");
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

/* method: addPolygonShape of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_addPolygonShape01
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_addPolygonShape01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_istable(tolua_S,3,"LUA_TABLE",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
  LUA_TABLE vertexes = (  toluafix_totable(tolua_S,3,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,4,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPolygonShape'", NULL);
#endif
  {
   PhysicsBody* tolua_ret = (PhysicsBody*)  self->addPolygonShape(mass,vertexes,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PhysicsBody");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PhysicsWorld_luabinding_PhysicsWorld_addPolygonShape00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: bindNodeToBody of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_bindNodeToBody00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_bindNodeToBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"PhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  PhysicsBody* body = ((PhysicsBody*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bindNodeToBody'", NULL);
#endif
  {
   self->bindNodeToBody(node,body);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bindNodeToBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unbindNode of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_unbindNode00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_unbindNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unbindNode'", NULL);
#endif
  {
   self->unbindNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unbindNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unbindAllNodes of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_unbindAllNodes00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_unbindAllNodes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unbindAllNodes'", NULL);
#endif
  {
   self->unbindAllNodes();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unbindAllNodes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBodyByNode of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_getBodyByNode00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_getBodyByNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBodyByNode'", NULL);
#endif
  {
   PhysicsBody* tolua_ret = (PhysicsBody*)  self->getBodyByNode(node);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PhysicsBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBodyByNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: start of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_start00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
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

/* method: stop of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsWorld_stop00
static int tolua_PhysicsWorld_luabinding_PhysicsWorld_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
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

/* method: defaultStaticBody of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_defaultStaticBody00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_defaultStaticBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* world = ((PhysicsWorld*)  tolua_tousertype(tolua_S,2,0));
  {
   PhysicsBody* tolua_ret = (PhysicsBody*)  PhysicsBody::defaultStaticBody(world);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PhysicsBody");
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

/* method: createStaticBody of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_createStaticBody00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_createStaticBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* world = ((PhysicsWorld*)  tolua_tousertype(tolua_S,2,0));
  {
   PhysicsBody* tolua_ret = (PhysicsBody*)  PhysicsBody::createStaticBody(world);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PhysicsBody");
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

/* method: create of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_create00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* world = ((PhysicsWorld*)  tolua_tousertype(tolua_S,2,0));
  float mass = ((float)  tolua_tonumber(tolua_S,3,0));
  float moment = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   PhysicsBody* tolua_ret = (PhysicsBody*)  PhysicsBody::create(world,mass,moment);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"PhysicsBody");
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

/* method: setMass of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_setMass00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_setMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBody* self = (PhysicsBody*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setInertia of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_setInertia00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_setInertia00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBody* self = (PhysicsBody*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setPosition of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_setPosition00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBody* self = (PhysicsBody*)  tolua_tousertype(tolua_S,1,0);
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

/* method: addSegmentShape of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_addSegmentShape00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_addSegmentShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBody* self = (PhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float lowerLeftX = ((float)  tolua_tonumber(tolua_S,2,0));
  float lowerLeftY = ((float)  tolua_tonumber(tolua_S,3,0));
  float lowerRightX = ((float)  tolua_tonumber(tolua_S,4,0));
  float lowerRightY = ((float)  tolua_tonumber(tolua_S,5,0));
  float thickness = ((float)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSegmentShape'", NULL);
#endif
  {
   PhysicsShape* tolua_ret = (PhysicsShape*)  self->addSegmentShape(lowerLeftX,lowerLeftY,lowerRightX,lowerRightY,thickness);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsShape");
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

/* method: addCircleShape of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_addCircleShape00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_addCircleShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBody* self = (PhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addCircleShape'", NULL);
#endif
  {
   PhysicsShape* tolua_ret = (PhysicsShape*)  self->addCircleShape(radius,offsetX,offsetY);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsShape");
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

/* method: addBoxShape of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_addBoxShape00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_addBoxShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBody* self = (PhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBoxShape'", NULL);
#endif
  {
   PhysicsShape* tolua_ret = (PhysicsShape*)  self->addBoxShape(width,height);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsShape");
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

/* method: addPolygonShape of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_addPolygonShape00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_addPolygonShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCPointArray",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBody* self = (PhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  CCPointArray* vertexs = ((CCPointArray*)  tolua_tousertype(tolua_S,2,0));
  float offsetX = ((float)  tolua_tonumber(tolua_S,3,0));
  float offsetY = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPolygonShape'", NULL);
#endif
  {
   PhysicsShape* tolua_ret = (PhysicsShape*)  self->addPolygonShape(vertexs,offsetX,offsetY);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsShape");
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

/* method: removeShapeAtIndex of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_removeShapeAtIndex00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_removeShapeAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBody* self = (PhysicsBody*)  tolua_tousertype(tolua_S,1,0);
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

/* method: removeAllShape of class  PhysicsBody */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsBody_removeAllShape00
static int tolua_PhysicsWorld_luabinding_PhysicsBody_removeAllShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsBody* self = (PhysicsBody*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getElasticity of class  PhysicsShape */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsShape_getElasticity00
static int tolua_PhysicsWorld_luabinding_PhysicsShape_getElasticity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsShape* self = (PhysicsShape*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setElasticity of class  PhysicsShape */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsShape_setElasticity00
static int tolua_PhysicsWorld_luabinding_PhysicsShape_setElasticity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsShape* self = (PhysicsShape*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getFriction of class  PhysicsShape */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsShape_getFriction00
static int tolua_PhysicsWorld_luabinding_PhysicsShape_getFriction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsShape* self = (PhysicsShape*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setFriction of class  PhysicsShape */
#ifndef TOLUA_DISABLE_tolua_PhysicsWorld_luabinding_PhysicsShape_setFriction00
static int tolua_PhysicsWorld_luabinding_PhysicsShape_setFriction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsShape* self = (PhysicsShape*)  tolua_tousertype(tolua_S,1,0);
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

/* Open function */
TOLUA_API int tolua_PhysicsWorld_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"PhysicsWorld","PhysicsWorld","CCNode",NULL);
  tolua_beginmodule(tolua_S,"PhysicsWorld");
   tolua_function(tolua_S,"create",tolua_PhysicsWorld_luabinding_PhysicsWorld_create00);
   tolua_function(tolua_S,"create",tolua_PhysicsWorld_luabinding_PhysicsWorld_create01);
   tolua_function(tolua_S,"createDebugNode",tolua_PhysicsWorld_luabinding_PhysicsWorld_createDebugNode00);
   tolua_function(tolua_S,"getGravity",tolua_PhysicsWorld_luabinding_PhysicsWorld_getGravity00);
   tolua_function(tolua_S,"setGravity",tolua_PhysicsWorld_luabinding_PhysicsWorld_setGravity00);
   tolua_function(tolua_S,"addCircleShape",tolua_PhysicsWorld_luabinding_PhysicsWorld_addCircleShape00);
   tolua_function(tolua_S,"addBoxShape",tolua_PhysicsWorld_luabinding_PhysicsWorld_addBoxShape00);
   tolua_function(tolua_S,"addPolygonShape",tolua_PhysicsWorld_luabinding_PhysicsWorld_addPolygonShape00);
   tolua_function(tolua_S,"addPolygonShape",tolua_PhysicsWorld_luabinding_PhysicsWorld_addPolygonShape01);
   tolua_function(tolua_S,"bindNodeToBody",tolua_PhysicsWorld_luabinding_PhysicsWorld_bindNodeToBody00);
   tolua_function(tolua_S,"unbindNode",tolua_PhysicsWorld_luabinding_PhysicsWorld_unbindNode00);
   tolua_function(tolua_S,"unbindAllNodes",tolua_PhysicsWorld_luabinding_PhysicsWorld_unbindAllNodes00);
   tolua_function(tolua_S,"getBodyByNode",tolua_PhysicsWorld_luabinding_PhysicsWorld_getBodyByNode00);
   tolua_function(tolua_S,"start",tolua_PhysicsWorld_luabinding_PhysicsWorld_start00);
   tolua_function(tolua_S,"stop",tolua_PhysicsWorld_luabinding_PhysicsWorld_stop00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PhysicsBody","PhysicsBody","CCObject",NULL);
  tolua_beginmodule(tolua_S,"PhysicsBody");
   tolua_function(tolua_S,"defaultStaticBody",tolua_PhysicsWorld_luabinding_PhysicsBody_defaultStaticBody00);
   tolua_function(tolua_S,"createStaticBody",tolua_PhysicsWorld_luabinding_PhysicsBody_createStaticBody00);
   tolua_function(tolua_S,"create",tolua_PhysicsWorld_luabinding_PhysicsBody_create00);
   tolua_function(tolua_S,"setMass",tolua_PhysicsWorld_luabinding_PhysicsBody_setMass00);
   tolua_function(tolua_S,"setInertia",tolua_PhysicsWorld_luabinding_PhysicsBody_setInertia00);
   tolua_function(tolua_S,"setPosition",tolua_PhysicsWorld_luabinding_PhysicsBody_setPosition00);
   tolua_function(tolua_S,"addSegmentShape",tolua_PhysicsWorld_luabinding_PhysicsBody_addSegmentShape00);
   tolua_function(tolua_S,"addCircleShape",tolua_PhysicsWorld_luabinding_PhysicsBody_addCircleShape00);
   tolua_function(tolua_S,"addBoxShape",tolua_PhysicsWorld_luabinding_PhysicsBody_addBoxShape00);
   tolua_function(tolua_S,"addPolygonShape",tolua_PhysicsWorld_luabinding_PhysicsBody_addPolygonShape00);
   tolua_function(tolua_S,"removeShapeAtIndex",tolua_PhysicsWorld_luabinding_PhysicsBody_removeShapeAtIndex00);
   tolua_function(tolua_S,"removeAllShape",tolua_PhysicsWorld_luabinding_PhysicsBody_removeAllShape00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PhysicsShape","PhysicsShape","CCObject",NULL);
  tolua_beginmodule(tolua_S,"PhysicsShape");
   tolua_function(tolua_S,"getElasticity",tolua_PhysicsWorld_luabinding_PhysicsShape_getElasticity00);
   tolua_function(tolua_S,"setElasticity",tolua_PhysicsWorld_luabinding_PhysicsShape_setElasticity00);
   tolua_function(tolua_S,"getFriction",tolua_PhysicsWorld_luabinding_PhysicsShape_getFriction00);
   tolua_function(tolua_S,"setFriction",tolua_PhysicsWorld_luabinding_PhysicsShape_setFriction00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PhysicsDebugNode","PhysicsDebugNode","CCNode",NULL);
  tolua_beginmodule(tolua_S,"PhysicsDebugNode");
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_PhysicsWorld_luabinding (lua_State* tolua_S) {
 return tolua_PhysicsWorld_luabinding_open(tolua_S);
};
#endif

