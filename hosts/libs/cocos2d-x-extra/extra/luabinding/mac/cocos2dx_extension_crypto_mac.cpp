/*
** Lua binding: cocos2dx_extension_crypto_mac
** Generated automatically by tolua++-1.0.92 on Tue Jan 29 11:54:27 2013.
*/

#include "cocos2dx_extension_crypto_mac.h"



#include "crypto/CCCrypto.h"
using namespace cocos2d::extra;

/* function to release collected object via destructor */
#ifdef __cplusplus


#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCCrypto");
 
}

/* method: encodeBase64Lua of class  CCCrypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extension_crypto_mac_CCCrypto_encodeBase64Lua00
static int tolua_cocos2dx_extension_crypto_mac_CCCrypto_encodeBase64Lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCCrypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* input = ((const char*)  tolua_tostring(tolua_S,2,0));
  int inputLength = ((int)  tolua_tonumber(tolua_S,3,0));
  {
     CCCrypto::encodeBase64Lua(input,inputLength);
   
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'encodeBase64Lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: decodeBase64Lua of class  CCCrypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extension_crypto_mac_CCCrypto_decodeBase64Lua00
static int tolua_cocos2dx_extension_crypto_mac_CCCrypto_decodeBase64Lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCCrypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* input = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
     CCCrypto::decodeBase64Lua(input);
   
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'decodeBase64Lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MD5Lua of class  CCCrypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extension_crypto_mac_CCCrypto_MD5Lua00
static int tolua_cocos2dx_extension_crypto_mac_CCCrypto_MD5Lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCCrypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* input = ((char*)  tolua_tostring(tolua_S,2,0));
  bool isRawOutput = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
     CCCrypto::MD5Lua(input,isRawOutput);
   
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MD5Lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sha1Lua of class  CCCrypto */
#ifndef TOLUA_DISABLE_tolua_cocos2dx_extension_crypto_mac_CCCrypto_sha1Lua00
static int tolua_cocos2dx_extension_crypto_mac_CCCrypto_sha1Lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCCrypto",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* input = ((char*)  tolua_tostring(tolua_S,2,0));
  char* key = ((char*)  tolua_tostring(tolua_S,3,0));
  bool isRawOutput = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
     CCCrypto::sha1Lua(input,key,isRawOutput);
   
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sha1Lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_cocos2dx_extension_crypto_mac_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CCCrypto","CCCrypto","",NULL);
  tolua_beginmodule(tolua_S,"CCCrypto");
   tolua_function(tolua_S,"encodeBase64Lua",tolua_cocos2dx_extension_crypto_mac_CCCrypto_encodeBase64Lua00);
   tolua_function(tolua_S,"decodeBase64Lua",tolua_cocos2dx_extension_crypto_mac_CCCrypto_decodeBase64Lua00);
   tolua_function(tolua_S,"MD5Lua",tolua_cocos2dx_extension_crypto_mac_CCCrypto_MD5Lua00);
   tolua_function(tolua_S,"sha1Lua",tolua_cocos2dx_extension_crypto_mac_CCCrypto_sha1Lua00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_cocos2dx_extension_crypto_mac (lua_State* tolua_S) {
 return tolua_cocos2dx_extension_crypto_mac_open(tolua_S);
};
#endif

