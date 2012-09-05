/*
** Lua binding: CCDrawing
** Generated automatically by tolua++-1.0.92 on Tue Sep  4 23:10:14 2012.
*/


#include "LuaCCDrawing.h"






/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCPointShape");
 tolua_usertype(tolua_S,"CCShapeNode");
 tolua_usertype(tolua_S,"CCPolygonShape");
 tolua_usertype(tolua_S,"CCRectShape");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"CCCircleShape");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"ccColor4F");
 tolua_usertype(tolua_S,"CCArray");
}

/* method: getColor of class  CCShapeNode */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCShapeNode_getColor00
static int tolua_CCDrawing_CCShapeNode_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCShapeNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCShapeNode* self = (CCShapeNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColor'", NULL);
#endif
  {
   const ccColor4F& tolua_ret = (const ccColor4F&)  self->getColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor4F");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  CCShapeNode */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCShapeNode_setColor00
static int tolua_CCDrawing_CCShapeNode_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCShapeNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4F",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCShapeNode* self = (CCShapeNode*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4F* color = ((const ccColor4F*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCCircleShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCCircleShape_create00
static int tolua_CCDrawing_CCCircleShape_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCCircleShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
  float angle = ((float)  tolua_tonumber(tolua_S,3,0));
  unsigned int segments = ((unsigned int)  tolua_tonumber(tolua_S,4,10));
  bool drawLineToCenter = ((bool)  tolua_toboolean(tolua_S,5,false));
  {
   CCCircleShape* tolua_ret = (CCCircleShape*)  CCCircleShape::create(radius,angle,segments,drawLineToCenter);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCCircleShape");
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

/* method: getRadius of class  CCCircleShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCCircleShape_getRadius00
static int tolua_CCDrawing_CCCircleShape_getRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCCircleShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCCircleShape* self = (CCCircleShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRadius'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getRadius();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRadius of class  CCCircleShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCCircleShape_setRadius00
static int tolua_CCDrawing_CCCircleShape_setRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCCircleShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCCircleShape* self = (CCCircleShape*)  tolua_tousertype(tolua_S,1,0);
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRadius'", NULL);
#endif
  {
   self->setRadius(radius);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAngle of class  CCCircleShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCCircleShape_getAngle00
static int tolua_CCDrawing_CCCircleShape_getAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCCircleShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCCircleShape* self = (CCCircleShape*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setAngle of class  CCCircleShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCCircleShape_setAngle00
static int tolua_CCDrawing_CCCircleShape_setAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCCircleShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCCircleShape* self = (CCCircleShape*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getSegments of class  CCCircleShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCCircleShape_getSegments00
static int tolua_CCDrawing_CCCircleShape_getSegments00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCCircleShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCCircleShape* self = (CCCircleShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSegments'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getSegments();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSegments'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSegments of class  CCCircleShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCCircleShape_setSegments00
static int tolua_CCDrawing_CCCircleShape_setSegments00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCCircleShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCCircleShape* self = (CCCircleShape*)  tolua_tousertype(tolua_S,1,0);
  unsigned int segments = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSegments'", NULL);
#endif
  {
   self->setSegments(segments);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSegments'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDrawLineToCenter of class  CCCircleShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCCircleShape_getDrawLineToCenter00
static int tolua_CCDrawing_CCCircleShape_getDrawLineToCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCCircleShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCCircleShape* self = (CCCircleShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDrawLineToCenter'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getDrawLineToCenter();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDrawLineToCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDrawLineToCenter of class  CCCircleShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCCircleShape_setDrawLineToCenter00
static int tolua_CCDrawing_CCCircleShape_setDrawLineToCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCCircleShape",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCCircleShape* self = (CCCircleShape*)  tolua_tousertype(tolua_S,1,0);
  bool drawLineToCenter = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDrawLineToCenter'", NULL);
#endif
  {
   self->setDrawLineToCenter(drawLineToCenter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDrawLineToCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCRectShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCRectShape_create00
static int tolua_CCDrawing_CCRectShape_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCRectShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
  bool fill = ((bool)  tolua_toboolean(tolua_S,3,false));
  {
   CCRectShape* tolua_ret = (CCRectShape*)  CCRectShape::create(*size,fill);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCRectShape");
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

/* method: getSize of class  CCRectShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCRectShape_getSize00
static int tolua_CCDrawing_CCRectShape_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRectShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRectShape* self = (CCRectShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSize of class  CCRectShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCRectShape_setSize00
static int tolua_CCDrawing_CCRectShape_setSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRectShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRectShape* self = (CCRectShape*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSize'", NULL);
#endif
  {
   self->setSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFill of class  CCRectShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCRectShape_getFill00
static int tolua_CCDrawing_CCRectShape_getFill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRectShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRectShape* self = (CCRectShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFill'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getFill();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFill of class  CCRectShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCRectShape_setFill00
static int tolua_CCDrawing_CCRectShape_setFill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRectShape",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRectShape* self = (CCRectShape*)  tolua_tousertype(tolua_S,1,0);
  bool fill = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFill'", NULL);
#endif
  {
   self->setFill(fill);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCPointShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCPointShape_create00
static int tolua_CCDrawing_CCPointShape_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPointShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float size = ((float)  tolua_tonumber(tolua_S,2,1));
  {
   CCPointShape* tolua_ret = (CCPointShape*)  CCPointShape::create(size);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPointShape");
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

/* method: getSize of class  CCPointShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCPointShape_getSize00
static int tolua_CCDrawing_CCPointShape_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPointShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPointShape* self = (CCPointShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSize of class  CCPointShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCPointShape_setSize00
static int tolua_CCDrawing_CCPointShape_setSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPointShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPointShape* self = (CCPointShape*)  tolua_tousertype(tolua_S,1,0);
  float size = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSize'", NULL);
#endif
  {
   self->setSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCPolygonShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCPolygonShape_create00
static int tolua_CCDrawing_CCPolygonShape_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCPolygonShape",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* vertices = ((CCArray*)  tolua_tousertype(tolua_S,2,0));
  bool fill = ((bool)  tolua_toboolean(tolua_S,3,false));
  bool close = ((bool)  tolua_toboolean(tolua_S,4,false));
  {
   CCPolygonShape* tolua_ret = (CCPolygonShape*)  CCPolygonShape::create(vertices,fill,close);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCPolygonShape");
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

/* method: getFill of class  CCPolygonShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCPolygonShape_getFill00
static int tolua_CCDrawing_CCPolygonShape_getFill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPolygonShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPolygonShape* self = (CCPolygonShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFill'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getFill();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFill of class  CCPolygonShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCPolygonShape_setFill00
static int tolua_CCDrawing_CCPolygonShape_setFill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPolygonShape",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPolygonShape* self = (CCPolygonShape*)  tolua_tousertype(tolua_S,1,0);
  bool fill = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFill'", NULL);
#endif
  {
   self->setFill(fill);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClose of class  CCPolygonShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCPolygonShape_getClose00
static int tolua_CCDrawing_CCPolygonShape_getClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPolygonShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPolygonShape* self = (CCPolygonShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClose'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getClose();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setClose of class  CCPolygonShape */
#ifndef TOLUA_DISABLE_tolua_CCDrawing_CCPolygonShape_setClose00
static int tolua_CCDrawing_CCPolygonShape_setClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCPolygonShape",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPolygonShape* self = (CCPolygonShape*)  tolua_tousertype(tolua_S,1,0);
  bool close = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setClose'", NULL);
#endif
  {
   self->setClose(close);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CCDrawing_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CCShapeNode","CCShapeNode","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCShapeNode");
   tolua_function(tolua_S,"getColor",tolua_CCDrawing_CCShapeNode_getColor00);
   tolua_function(tolua_S,"setColor",tolua_CCDrawing_CCShapeNode_setColor00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCCircleShape","CCCircleShape","CCShapeNode",NULL);
  tolua_beginmodule(tolua_S,"CCCircleShape");
   tolua_function(tolua_S,"create",tolua_CCDrawing_CCCircleShape_create00);
   tolua_function(tolua_S,"getRadius",tolua_CCDrawing_CCCircleShape_getRadius00);
   tolua_function(tolua_S,"setRadius",tolua_CCDrawing_CCCircleShape_setRadius00);
   tolua_function(tolua_S,"getAngle",tolua_CCDrawing_CCCircleShape_getAngle00);
   tolua_function(tolua_S,"setAngle",tolua_CCDrawing_CCCircleShape_setAngle00);
   tolua_function(tolua_S,"getSegments",tolua_CCDrawing_CCCircleShape_getSegments00);
   tolua_function(tolua_S,"setSegments",tolua_CCDrawing_CCCircleShape_setSegments00);
   tolua_function(tolua_S,"getDrawLineToCenter",tolua_CCDrawing_CCCircleShape_getDrawLineToCenter00);
   tolua_function(tolua_S,"setDrawLineToCenter",tolua_CCDrawing_CCCircleShape_setDrawLineToCenter00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCRectShape","CCRectShape","CCShapeNode",NULL);
  tolua_beginmodule(tolua_S,"CCRectShape");
   tolua_function(tolua_S,"create",tolua_CCDrawing_CCRectShape_create00);
   tolua_function(tolua_S,"getSize",tolua_CCDrawing_CCRectShape_getSize00);
   tolua_function(tolua_S,"setSize",tolua_CCDrawing_CCRectShape_setSize00);
   tolua_function(tolua_S,"getFill",tolua_CCDrawing_CCRectShape_getFill00);
   tolua_function(tolua_S,"setFill",tolua_CCDrawing_CCRectShape_setFill00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPointShape","CCPointShape","CCShapeNode",NULL);
  tolua_beginmodule(tolua_S,"CCPointShape");
   tolua_function(tolua_S,"create",tolua_CCDrawing_CCPointShape_create00);
   tolua_function(tolua_S,"getSize",tolua_CCDrawing_CCPointShape_getSize00);
   tolua_function(tolua_S,"setSize",tolua_CCDrawing_CCPointShape_setSize00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCPolygonShape","CCPolygonShape","CCShapeNode",NULL);
  tolua_beginmodule(tolua_S,"CCPolygonShape");
   tolua_function(tolua_S,"create",tolua_CCDrawing_CCPolygonShape_create00);
   tolua_function(tolua_S,"getFill",tolua_CCDrawing_CCPolygonShape_getFill00);
   tolua_function(tolua_S,"setFill",tolua_CCDrawing_CCPolygonShape_setFill00);
   tolua_function(tolua_S,"getClose",tolua_CCDrawing_CCPolygonShape_getClose00);
   tolua_function(tolua_S,"setClose",tolua_CCDrawing_CCPolygonShape_setClose00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CCDrawing (lua_State* tolua_S) {
 return tolua_CCDrawing_open(tolua_S);
};
#endif

