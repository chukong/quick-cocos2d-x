/*
** Lua binding: CCPhysicsWorld_luabinding
** Generated automatically by tolua++-1.0.92 on Tue May 14 16:52:52 2013.
*/

#include "CCPhysicsWorld_luabinding.h"
#include "CCLuaEngine.h"

using namespace cocos2d;




#include "CCPhysicsShape.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsWorld.h"
#include "CCPhysicsDebugNode.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"CCPhysicsWorld");
 tolua_usertype(tolua_S,"CCPointArray");
 tolua_usertype(tolua_S,"CCPhysicsBody");
 
 tolua_usertype(tolua_S,"CCPhysicsDebugNode");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCPhysicsShape");
 tolua_usertype(tolua_S,"CCObject");
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

/* method: addCircleShape of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addCircleShape00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addCircleShape00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addCircleShape'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->addCircleShape(mass,radius,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
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

/* method: addBoxShape of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addBoxShape00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addBoxShape00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBoxShape'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->addBoxShape(mass,width,height);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
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

/* method: addPolygonShape of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addPolygonShape00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addPolygonShape00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPolygonShape'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->addPolygonShape(mass,vertexes,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
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

/* method: addPolygonShape of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addPolygonShape01
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addPolygonShape01(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPolygonShape'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->addPolygonShape(mass,vertexes,offsetX,offsetY);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addPolygonShape00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: bindNodeToBody of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_bindNodeToBody00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_bindNodeToBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCPhysicsBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCPhysicsBody* body = ((CCPhysicsBody*)  tolua_tousertype(tolua_S,3,0));
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

/* method: unbindNode of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_unbindNode00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_unbindNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
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

/* method: unbindAllNodes of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_unbindAllNodes00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_unbindAllNodes00(lua_State* tolua_S)
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

/* method: getBodyByNode of class  CCPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getBodyByNode00
static int tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getBodyByNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsWorld* self = (CCPhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBodyByNode'", NULL);
#endif
  {
   CCPhysicsBody* tolua_ret = (CCPhysicsBody*)  self->getBodyByNode(node);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPhysicsBody");
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
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPhysicsBody* self = (CCPhysicsBody*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBoxShape'", NULL);
#endif
  {
   CCPhysicsShape* tolua_ret = (CCPhysicsShape*)  self->addBoxShape(width,height);
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
   tolua_function(tolua_S,"addCircleShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addCircleShape00);
   tolua_function(tolua_S,"addBoxShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addBoxShape00);
   tolua_function(tolua_S,"addPolygonShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addPolygonShape00);
   tolua_function(tolua_S,"addPolygonShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_addPolygonShape01);
   tolua_function(tolua_S,"bindNodeToBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_bindNodeToBody00);
   tolua_function(tolua_S,"unbindNode",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_unbindNode00);
   tolua_function(tolua_S,"unbindAllNodes",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_unbindAllNodes00);
   tolua_function(tolua_S,"getBodyByNode",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_getBodyByNode00);
   tolua_function(tolua_S,"start",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_start00);
   tolua_function(tolua_S,"stop",tolua_CCPhysicsWorld_luabinding_CCPhysicsWorld_stop00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPhysicsBody","CCPhysicsBody","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CCPhysicsBody");
   tolua_function(tolua_S,"defaultStaticBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_defaultStaticBody00);
   tolua_function(tolua_S,"createStaticBody",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_createStaticBody00);
   tolua_function(tolua_S,"create",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_create00);
   tolua_function(tolua_S,"setMass",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setMass00);
   tolua_function(tolua_S,"setInertia",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setInertia00);
   tolua_function(tolua_S,"setPosition",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_setPosition00);
   tolua_function(tolua_S,"addSegmentShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addSegmentShape00);
   tolua_function(tolua_S,"addCircleShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addCircleShape00);
   tolua_function(tolua_S,"addBoxShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addBoxShape00);
   tolua_function(tolua_S,"addPolygonShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addPolygonShape00);
   tolua_function(tolua_S,"addPolygonShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_addPolygonShape01);
   tolua_function(tolua_S,"removeShapeAtIndex",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeShapeAtIndex00);
   tolua_function(tolua_S,"removeShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeShape00);
   tolua_function(tolua_S,"removeAllShape",tolua_CCPhysicsWorld_luabinding_CCPhysicsBody_removeAllShape00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPhysicsShape","CCPhysicsShape","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CCPhysicsShape");
   tolua_function(tolua_S,"getElasticity",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getElasticity00);
   tolua_function(tolua_S,"setElasticity",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setElasticity00);
   tolua_function(tolua_S,"getFriction",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_getFriction00);
   tolua_function(tolua_S,"setFriction",tolua_CCPhysicsWorld_luabinding_CCPhysicsShape_setFriction00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPhysicsDebugNode","CCPhysicsDebugNode","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCPhysicsDebugNode");
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCPhysicsWorld_luabinding (lua_State* tolua_S) {
 return tolua_CCPhysicsWorld_luabinding_open(tolua_S);
};
#endif

