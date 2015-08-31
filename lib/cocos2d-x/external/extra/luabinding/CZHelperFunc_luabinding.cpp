/*
** Lua binding: CZHelperFunc_luabinding
** Generated automatically by tolua++-1.0.92 on Wed Oct 22 00:31:06 2014.
*/

#include "CZHelperFunc_luabinding.h"
#include "CCLuaEngine.h"

using namespace cocos2d;




#include "../apptools/HelperFunc.h"

/* function to release collected object via destructor */
#ifdef __cplusplus


#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CZHelperFunc"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CZHelperFunc)), "CZHelperFunc");
 
}

/* method: getFileData of class  CZHelperFunc */
#ifndef TOLUA_DISABLE_tolua_CZHelperFunc_luabinding_CZHelperFunc_getFileData00
static int tolua_CZHelperFunc_luabinding_CZHelperFunc_getFileData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CZHelperFunc",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pPathFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
     CZHelperFunc::getFileData(pPathFile);
   
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CZHelperFunc_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CZHelperFunc","CZHelperFunc","",NULL);
  tolua_beginmodule(tolua_S,"CZHelperFunc");
   tolua_function(tolua_S,"getFileData",tolua_CZHelperFunc_luabinding_CZHelperFunc_getFileData00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CZHelperFunc_luabinding (lua_State* tolua_S) {
 return tolua_CZHelperFunc_luabinding_open(tolua_S);
};
#endif

