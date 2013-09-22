/*
* TOOLS.H
*/
#ifndef TOOLS_H
#define TOOLS_H

#include "lauxlib.h"
#include "threading.h"
#include "deep.h"
    // MUTEX_T

#include <assert.h>

// M$ compiler doesn't support 'inline' keyword in C files...
#if defined( _MSC_VER)
#define inline __inline
#endif

// code is now using Lua 5.2 API
// add Lua 5.2 API when building for Lua 5.1
#if LUA_VERSION_NUM == 501
#define lua_absindex( L, idx) (((idx) >= 0 || (idx) <= LUA_REGISTRYINDEX) ? (idx) : lua_gettop(L) + (idx) +1)
#define lua_pushglobaltable(L) lua_pushvalue( L, LUA_GLOBALSINDEX)
#define lua_setuservalue lua_setfenv
#define lua_getuservalue lua_getfenv
#define lua_rawlen lua_objlen
#define luaG_registerlibfuncs( L, _funcs) luaL_register( L, NULL, _funcs)
#define LUA_OK 0
#define LUA_ERRGCMM 666 // doesn't exist in Lua 5.1, we don't care about the actual value
void luaL_requiref (lua_State* L, const char* modname, lua_CFunction openf, int glb); // implementation copied from Lua 5.2 sources
#endif // LUA_VERSION_NUM == 501

// wrap Lua 5.2 calls under Lua 5.1 API when it is simpler that way
#if LUA_VERSION_NUM == 502
#define lua_equal( L, a, b) lua_compare( L, a, b, LUA_OPEQ)
#define lua_lessthan( L, a, b) lua_compare( L, a, b, LUA_OPLT)
#define luaG_registerlibfuncs( L, _funcs) luaL_setfuncs( L, _funcs, 0)
#endif // LUA_VERSION_NUM == 502

#define USE_DEBUG_SPEW 0
#if USE_DEBUG_SPEW
extern char const* debugspew_indent;
extern int debugspew_indent_depth;
#define INDENT_BEGIN "%.*s "
#define INDENT_END , debugspew_indent_depth, debugspew_indent
#define DEBUGSPEW_CODE(_code) _code
#else // USE_DEBUG_SPEW
#define DEBUGSPEW_CODE(_code)
#endif // USE_DEBUG_SPEW


#ifdef NDEBUG
  #define _ASSERT_L(lua,c)  /*nothing*/
  #define STACK_CHECK(L)    /*nothing*/
  #define STACK_MID(L,c)    /*nothing*/
  #define STACK_END(L,c)    /*nothing*/
  #define STACK_DUMP(L)    /*nothing*/
#else
  #define _ASSERT_L(lua,c)  do { if (!(c)) luaL_error( lua, "ASSERT failed: %s:%d '%s'", __FILE__, __LINE__, #c ); } while( 0)
  //
  #define STACK_CHECK(L)     { int const _oldtop_##L = lua_gettop( L)
  #define STACK_MID(L,change) \
	do \
	{ \
		int a = lua_gettop( L) - _oldtop_##L; \
		int b = (change); \
		if( a != b) \
			luaL_error( L, "STACK ASSERT failed (%d not %d): %s:%d", a, b, __FILE__, __LINE__ ); \
	} while( 0)
  #define STACK_END(L,change)  STACK_MID(L,change); }

  #define STACK_DUMP(L)    luaG_dump(L);
#endif
#define ASSERT_L(c) _ASSERT_L(L,c)

#define STACK_GROW(L,n) do { if (!lua_checkstack(L,n)) luaL_error( L, "Cannot grow stack!" ); } while( 0)

#define LUAG_FUNC( func_name ) static int LG_##func_name( lua_State *L )

#define luaG_optunsigned(L,i,d) ((uint_t) luaL_optinteger(L,i,d))
#define luaG_tounsigned(L,i) ((uint_t) lua_tointeger(L,i))

void luaG_dump( lua_State* L );

lua_State* luaG_newstate( lua_State* _from, int const _on_state_create, char const* libs);

typedef struct {
    volatile int refcount;
    void *deep;
} DEEP_PRELUDE;

void luaG_push_proxy( lua_State *L, luaG_IdFunction idfunc, DEEP_PRELUDE *deep_userdata);
void luaG_inter_copy_package( lua_State* L, lua_State* L2, int _idx);

int luaG_inter_copy( lua_State *L, lua_State *L2, uint_t n);
int luaG_inter_move( lua_State *L, lua_State *L2, uint_t n);

int luaG_nameof( lua_State* L);
int luaG_new_require( lua_State* L);

// Lock for reference counter inc/dec locks (to be initialized by outside code)
//
extern MUTEX_T deep_lock;
extern MUTEX_T mtid_lock;

void populate_func_lookup_table( lua_State* L, int _i, char const* _name);
void serialize_require( lua_State *L);
extern MUTEX_T require_cs;

// for verbose errors
extern bool_t GVerboseErrors;

#endif
    // TOOLS_H
