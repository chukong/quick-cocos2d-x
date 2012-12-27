/*
** Lua binding: LuaFlurry_luabinding
** Generated automatically by tolua++-1.0.92 on Thu Dec 27 22:07:49 2012.
*/

#include "LuaFlurry_luabinding.h"



#include "LuaFlurry.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"LuaFlurry");
 
}

/* method: logEvent of class  LuaFlurry */
#ifndef TOLUA_DISABLE_tolua_LuaFlurry_luabinding_LuaFlurry_logEvent00
static int tolua_LuaFlurry_luabinding_LuaFlurry_logEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaFlurry",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventName = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool timed = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   LuaFlurry::logEvent(eventName,timed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'logEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: logEventWithParameters of class  LuaFlurry */
#ifndef TOLUA_DISABLE_tolua_LuaFlurry_luabinding_LuaFlurry_logEventWithParameters00
static int tolua_LuaFlurry_luabinding_LuaFlurry_logEventWithParameters00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaFlurry",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_istable(tolua_S,3,"LUA_TABLE",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventName = ((const char*)  tolua_tostring(tolua_S,2,0));
  LUA_TABLE parameters = (  toluafix_totable(tolua_S,3,0));
  bool timed = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   LuaFlurry::logEventWithParameters(eventName,parameters,timed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'logEventWithParameters'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: endTimedEvent of class  LuaFlurry */
#ifndef TOLUA_DISABLE_tolua_LuaFlurry_luabinding_LuaFlurry_endTimedEvent00
static int tolua_LuaFlurry_luabinding_LuaFlurry_endTimedEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaFlurry",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   LuaFlurry::endTimedEvent(eventName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'endTimedEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_LuaFlurry_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"LuaFlurry","LuaFlurry","",NULL);
  tolua_beginmodule(tolua_S,"LuaFlurry");
   tolua_function(tolua_S,"logEvent",tolua_LuaFlurry_luabinding_LuaFlurry_logEvent00);
   tolua_function(tolua_S,"logEventWithParameters",tolua_LuaFlurry_luabinding_LuaFlurry_logEventWithParameters00);
   tolua_function(tolua_S,"endTimedEvent",tolua_LuaFlurry_luabinding_LuaFlurry_endTimedEvent00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_LuaFlurry_luabinding (lua_State* tolua_S) {
 return tolua_LuaFlurry_luabinding_open(tolua_S);
};
#endif

