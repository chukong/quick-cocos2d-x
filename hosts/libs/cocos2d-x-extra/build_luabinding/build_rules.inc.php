<?php


$FIX = array();

// remove unused header
$find = <<<EOT
#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
EOT;
$replace = '#include "##LUABINDING_FILENAME##.h"';
$FIX[$find] = $replace;

// remove unused functions
$find = <<<EOT
/* Exported function */
TOLUA_API int  tolua_##LUABINDING_FILENAME##_open (lua_State* tolua_S);
EOT;
$replace = '';
$FIX[$find] = $replace;

// fix LUA_FUNCTION
$find = '*((LUA_FUNCTION*)';
$replace = '(';
$FIX[$find] = $replace;

$find = 'tolua_usertype(tolua_S,"LUA_FUNCTION");';
$replace = '';
$FIX[$find] = $replace;

// fix LUA_TABLE
$find = '*((LUA_TABLE*)';
$replace = '(';
$FIX[$find] = $replace;

$find = 'tolua_usertype(tolua_S,"LUA_TABLE");';
$replace = '';
$FIX[$find] = $replace;

$find = <<<EOT
{
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LUA_TABLE)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LUA_TABLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LUA_TABLE));
     tolua_pushusertype(tolua_S,tolua_obj,"LUA_TABLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
EOT;
$replace = '';
$FIX[$find] = $replace;

$find = 'LUA_TABLE tolua_ret = (LUA_TABLE)';
$replace = '';
$FIX[$find] = $replace;

$find = <<<EOT
static int tolua_collect_LUA_TABLE (lua_State* tolua_S)
{
 LUA_TABLE* self = (LUA_TABLE*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
EOT;
$replace = '';
$FIX[$find] = $replace;

// fix push ccobject
$find = 'toluafix_pushusertype_ccobject(tolua_S,(void*)tolua_ret';
$replace = <<<EOT
int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret
EOT;
$FIX[$find] = $replace;

// fix LUA_STRING
$find = '((LUA_STRING*)';
$replace = '(';
$FIX[$find] = $replace;

$find = 'tolua_usertype(tolua_S,"LUA_STRING");';
$replace = '';
$FIX[$find] = $replace;

$find = <<<EOT
{
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LUA_STRING)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LUA_STRING");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LUA_STRING));
     tolua_pushusertype(tolua_S,tolua_obj,"LUA_STRING");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
EOT;
$replace = '';
$FIX[$find] = $replace;

$find = 'LUA_STRING tolua_ret = (LUA_STRING)';
$replace = '';
$FIX[$find] = $replace;

$find = <<<EOT
static int tolua_collect_LUA_STRING (lua_State* tolua_S)
{
 LUA_STRING* self = (LUA_STRING*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
EOT;
$replace = '';
$FIX[$find] = $replace;

// ----

return $FIX;
