/*
 * LANES.C                              Copyright (c) 2007-08, Asko Kauppi
 *                                      Copyright (C) 2009-13, Benoit Germain
 *
 * Multithreading in Lua.
 * 
 * History:
 *      See CHANGES
 *
 * Platforms (tested internally):
 *      OS X (10.5.7 PowerPC/Intel)
 *      Linux x86 (Ubuntu 8.04)
 *      Win32 (Windows XP Home SP2, Visual C++ 2005/2008 Express)
 *
 * Platforms (tested externally):
 *      Win32 (MSYS) by Ross Berteig.
 *
 * Platforms (testers appreciated):
 *      Win64 - should work???
 *      Linux x64 - should work
 *      FreeBSD - should work
 *      QNX - porting shouldn't be hard
 *      Sun Solaris - porting shouldn't be hard
 *
 * References:
 *      "Porting multithreaded applications from Win32 to Mac OS X":
 *      <http://developer.apple.com/macosx/multithreadedprogramming.html>
 *
 *      Pthreads:
 *      <http://vergil.chemistry.gatech.edu/resources/programming/threads.html>
 *
 *      MSDN: <http://msdn2.microsoft.com/en-us/library/ms686679.aspx>
 *
 *      <http://ridiculousfish.com/blog/archives/2007/02/17/barrier>
 *
 * Defines:
 *      -DLINUX_SCHED_RR: all threads are lifted to SCHED_RR category, to
 *          allow negative priorities (-2,-1) be used. Even without this,
 *          using priorities will require 'sudo' privileges on Linux.
 *
 *		-DUSE_PTHREAD_TIMEDJOIN: use 'pthread_timedjoin_np()' for waiting
 *          for threads with a timeout. This changes the thread cleanup
 *          mechanism slightly (cleans up at the join, not once the thread
 *          has finished). May or may not be a good idea to use it.
 *          Available only in selected operating systems (Linux).
 *
 * Bugs:
 *
 * To-do:
 *
 * Make waiting threads cancellable.
 *      ...
 */

char const* VERSION = "3.6.3";

/*
===============================================================================

Copyright (C) 2007-10 Asko Kauppi <akauppi@gmail.com>
              2011-13 Benoit Germain <bnt.germain@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

===============================================================================
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lua.h"
#include "lauxlib.h"

#include "threading.h"
#include "tools.h"
#include "keeper.h"
#include "lanes.h"

#if !(defined( PLATFORM_XBOX) || defined( PLATFORM_WIN32) || defined( PLATFORM_POCKETPC))
# include <sys/time.h>
#endif

/* geteuid() */
#ifdef PLATFORM_LINUX
# include <unistd.h>
# include <sys/types.h>
#endif

/*
 * Do we want to activate full lane tracking feature? (EXPERIMENTAL)
 */
#define HAVE_LANE_TRACKING 1

/* Do you want full call stacks, or just the line where the error happened?
*
* TBD: The full stack feature does not seem to work (try 'make error').
*/
#define ERROR_FULL_STACK

/*
 * Lane cancellation request modes
 */
enum e_cancel_request
{
	CANCEL_NONE, // no pending cancel request
	CANCEL_SOFT, // user wants the lane to cancel itself manually on cancel_test()
	CANCEL_HARD  // user wants the lane to be interrupted (meaning code won't return from those functions) from inside linda:send/receive calls
};

// NOTE: values to be changed by either thread, during execution, without
//       locking, are marked "volatile"
//
struct s_lane
{
	THREAD_T thread;
	//
	// M: sub-thread OS thread
	// S: not used

	char const* debug_name;

	lua_State* L;
	//
	// M: prepares the state, and reads results
	// S: while S is running, M must keep out of modifying the state

	volatile enum e_status status;
	// 
	// M: sets to PENDING (before launching)
	// S: updates -> RUNNING/WAITING -> DONE/ERROR_ST/CANCELLED

	SIGNAL_T * volatile waiting_on;
	//
	// When status is WAITING, points on the linda's signal the thread waits on, else NULL

	volatile enum e_cancel_request cancel_request;
	//
	// M: sets to FALSE, flags TRUE for cancel request
	// S: reads to see if cancel is requested

#if THREADWAIT_METHOD == THREADWAIT_CONDVAR
	SIGNAL_T done_signal;
	//
	// M: Waited upon at lane ending  (if Posix with no PTHREAD_TIMEDJOIN)
	// S: sets the signal once cancellation is noticed (avoids a kill)

	MUTEX_T done_lock;
	// 
	// Lock required by 'done_signal' condition variable, protecting
	// lane status changes to DONE/ERROR_ST/CANCELLED.
#endif // THREADWAIT_METHOD == THREADWAIT_CONDVAR

	volatile enum { 
		NORMAL,         // normal master side state
		KILLED          // issued an OS kill
	} mstatus;
	//
	// M: sets to NORMAL, if issued a kill changes to KILLED
	// S: not used

	struct s_lane * volatile selfdestruct_next;
	//
	// M: sets to non-NULL if facing lane handle '__gc' cycle but the lane
	//    is still running
	// S: cleans up after itself if non-NULL at lane exit

#if HAVE_LANE_TRACKING
	struct s_lane * volatile tracking_next;
#endif // HAVE_LANE_TRACKING
	//
	// For tracking only
};

static enum e_cancel_request cancel_test( lua_State* L);
static void cancel_error( lua_State*L );

#define CANCEL_TEST_KEY ((void*)cancel_test)    // used as registry key
#define CANCEL_ERROR ((void*)cancel_error)      // 'cancel_error' sentinel

/*
* registry[FINALIZER_REG_KEY] is either nil (no finalizers) or a table
* of functions that Lanes will call after the executing 'pcall' has ended.
*
* We're NOT using the GC system for finalizer mainly because providing the
* error (and maybe stack trace) parameters to the finalizer functions would
* anyways complicate that approach.
*/
#define FINALIZER_REG_KEY ((void*)LG_set_finalizer)

struct s_Linda;

#if 1
# define DEBUG_SIGNAL( msg, signal_ref ) /* */
#else
# define DEBUG_SIGNAL( msg, signal_ref ) \
    { int i; unsigned char *ptr; char buf[999]; \
      sprintf( buf, ">>> " msg ": %p\t", (signal_ref) ); \
      ptr= (unsigned char *)signal_ref; \
      for( i=0; i<sizeof(*signal_ref); i++ ) { \
        sprintf( strchr(buf,'\0'), "%02x %c ", ptr[i], ptr[i] ); \
      } \
      fprintf( stderr, "%s\n", buf ); \
    }
#endif

/*
* Push a table stored in registry onto Lua stack.
*
* If there is no existing table, create one if 'create' is TRUE.
* 
* Returns: TRUE if a table was pushed
*          FALSE if no table found, not created, and nothing pushed
*/
static bool_t push_registry_table( lua_State*L, void *key, bool_t create ) {

    STACK_GROW(L,3);
    
    lua_pushlightuserdata( L, key );
    lua_gettable( L, LUA_REGISTRYINDEX );
    
    if (lua_isnil(L,-1)) {
        lua_pop(L,1);

        if (!create) return FALSE;  // nothing pushed

        lua_newtable(L);
        lua_pushlightuserdata( L, key );
        lua_pushvalue(L,-2);    // duplicate of the table
        lua_settable( L, LUA_REGISTRYINDEX );
        
        // [-1]: table that's also bound in registry
    }
    return TRUE;    // table pushed
}

#if HAVE_LANE_TRACKING

static MUTEX_T tracking_cs;
struct s_lane* volatile tracking_first = NULL; // will change to TRACKING_END if we want to activate tracking

// The chain is ended by '(struct s_lane*)(-1)', not NULL:
// 'tracking_first -> ... -> ... -> (-1)'
#define TRACKING_END ((struct s_lane *)(-1))

/*
 * Add the lane to tracking chain; the ones still running at the end of the
 * whole process will be cancelled.
 */
static void tracking_add( struct s_lane *s)
{

	MUTEX_LOCK( &tracking_cs);
	{
		assert( s->tracking_next == NULL);

		s->tracking_next = tracking_first;
		tracking_first = s;
	}
	MUTEX_UNLOCK( &tracking_cs);
}

/*
 * A free-running lane has ended; remove it from tracking chain
 */
static bool_t tracking_remove( struct s_lane *s )
{
	bool_t found = FALSE;
	MUTEX_LOCK( &tracking_cs);
	{
		// Make sure (within the MUTEX) that we actually are in the chain
		// still (at process exit they will remove us from chain and then
		// cancel/kill).
		//
		if (s->tracking_next != NULL)
		{
			struct s_lane **ref= (struct s_lane **) &tracking_first;

			while( *ref != TRACKING_END)
			{
				if( *ref == s)
				{
					*ref = s->tracking_next;
					s->tracking_next = NULL;
					found = TRUE;
					break;
				}
				ref = (struct s_lane **) &((*ref)->tracking_next);
			}
			assert( found);
		}
	}
	MUTEX_UNLOCK( &tracking_cs);
	return found;
}

#endif // HAVE_LANE_TRACKING

//---
// low-level cleanup

static void lane_cleanup( struct s_lane* s)
{
	// Clean up after a (finished) thread
	//
#if THREADWAIT_METHOD == THREADWAIT_CONDVAR
	SIGNAL_FREE( &s->done_signal);
	MUTEX_FREE( &s->done_lock);
#endif // THREADWAIT_METHOD == THREADWAIT_CONDVAR

#if HAVE_LANE_TRACKING
	if( tracking_first)
	{
		// Lane was cleaned up, no need to handle at process termination
		tracking_remove( s);
	}
#endif // HAVE_LANE_TRACKING

	free( s);
}

/*
 * ###############################################################################################
 * ############################################ Linda ############################################
 * ###############################################################################################
 */

/*
* Actual data is kept within a keeper state, which is hashed by the 's_Linda'
* pointer (which is same to all userdatas pointing to it).
*/
struct s_Linda {
    SIGNAL_T read_happened;
    SIGNAL_T write_happened;
    char name[1];
};

static void linda_id( lua_State*, char const * const which);

#define lua_toLinda(L,n) ((struct s_Linda *)luaG_todeep( L, linda_id, n ))


static void check_key_types( lua_State*L, int _start, int _end)
{
	int i;
	for( i = _start; i <= _end; ++ i)
	{
		int t = lua_type( L, i);
		if( t == LUA_TBOOLEAN || t == LUA_TNUMBER || t == LUA_TSTRING || t == LUA_TLIGHTUSERDATA)
		{
			continue;
		}
		(void) luaL_error( L, "argument #%d: invalid key type (not a boolean, string, number or light userdata)", i);
	}
}

/*
* bool= linda_send( linda_ud, [timeout_secs=-1,] key_num|str|bool|lightuserdata, ... )
*
* Send one or more values to a Linda. If there is a limit, all values must fit.
*
* Returns:  'true' if the value was queued
*           'false' for timeout (only happens when the queue size is limited)
*/
LUAG_FUNC( linda_send)
{
	struct s_Linda *linda = lua_toLinda( L, 1);
	bool_t ret;
	enum e_cancel_request cancel = CANCEL_NONE;
	int pushed;
	time_d timeout= -1.0;
	uint_t key_i = 2; // index of first key, if timeout not there

	luaL_argcheck( L, linda, 1, "expected a linda object!");

	if( lua_type( L, 2) == LUA_TNUMBER) // we don't want to use lua_isnumber() because of autocoercion
	{
		timeout = SIGNAL_TIMEOUT_PREPARE( lua_tonumber( L,2));
		++ key_i;
	}
	else if( lua_isnil( L, 2)) // alternate explicit "no timeout" by passing nil before the key
	{
		++ key_i;
	}

	// make sure the keys are of a valid type
	check_key_types( L, key_i, key_i);

	// make sure there is something to send
	if( (uint_t)lua_gettop( L) == key_i)
	{
		return luaL_error( L, "no data to send");
	}

	// convert nils to some special non-nil sentinel in sent values
	keeper_toggle_nil_sentinels( L, key_i + 1, 1);

	STACK_GROW(L, 1);
	{
		struct s_Keeper *K = keeper_acquire( linda);
		lua_State *KL = K->L;    // need to do this for 'STACK_CHECK'
		STACK_CHECK( KL);
		for( ;;)
		{
			STACK_MID( KL, 0);
			pushed = keeper_call( KL, KEEPER_API( send), L, linda, key_i);
			if( pushed < 0)
			{
				break;
			}
			ASSERT_L( pushed == 1);

			ret = lua_toboolean( L, -1);
			lua_pop( L, 1);

			if( ret)
			{
				// Wake up ALL waiting threads
				//
				SIGNAL_ALL( &linda->write_happened);
				break;

			}
			if( timeout == 0.0)
			{
				break;  /* no wait; instant timeout */
			}
			/* limit faced; push until timeout */

			cancel = cancel_test( L);   // testing here causes no delays
			if( cancel != CANCEL_NONE) // if user wants to cancel, the call returns without sending anything
			{
				break;
			}

			// change status of lane to "waiting"
			{
				struct s_lane *s;
				enum e_status prev_status = ERROR_ST; // prevent 'might be used uninitialized' warnings
				STACK_GROW(L, 1);

				STACK_CHECK( L);
				lua_pushlightuserdata( L, CANCEL_TEST_KEY);
				lua_rawget( L, LUA_REGISTRYINDEX);
				s = lua_touserdata( L, -1);     // lightuserdata (true 's_lane' pointer) or nil if in the main Lua state
				lua_pop(L, 1);
				STACK_END( L, 0);
				if( s)
				{
					prev_status = s->status; // RUNNING, most likely
					ASSERT_L( prev_status == RUNNING); // but check, just in case
					s->status = WAITING;
					ASSERT_L( s->waiting_on == NULL);
					s->waiting_on = &linda->read_happened;
				}
				// could not send because no room: wait until some data was read before trying again, or until timeout is reached
				if( !SIGNAL_WAIT( &linda->read_happened, &K->lock_, timeout))
				{
					if( s)
					{
						s->waiting_on = NULL;
						s->status = prev_status;
					}
					break;
				}
				if( s)
				{
					s->waiting_on = NULL;
					s->status = prev_status;
				}
			}
		}
		STACK_END( KL, 0);
		keeper_release( K);
	}

	// must trigger error after keeper state has been released
	if( pushed < 0)
	{
		return luaL_error( L, "tried to copy unsupported types");
	}

	// raise an error interrupting execution only in case of hard cancel
	if( cancel == CANCEL_HARD)
		cancel_error( L);

	lua_pushboolean( L, ret);
	return 1;
}


/*
 * 2 modes of operation
 * [val, key]= linda_receive( linda_ud, [timeout_secs_num=-1], key_num|str|bool|lightuserdata [, ...] )
 * Consumes a single value from the Linda, in any key.
 * Returns: received value (which is consumed from the slot), and the key which had it

 * [val1, ... valCOUNT]= linda_receive( linda_ud, [timeout_secs_num=-1], linda.batched, key_num|str|bool|lightuserdata, min_COUNT[, max_COUNT])
 * Consumes between min_COUNT and max_COUNT values from the linda, from a single key.
 * returns the actual consumed values, or nil if there weren't enough values to consume
 *
 */
#define BATCH_SENTINEL "270e6c9d-280f-4983-8fee-a7ecdda01475"
LUAG_FUNC( linda_receive)
{
	struct s_Linda *linda = lua_toLinda( L, 1);
	int pushed, expected_pushed_min, expected_pushed_max;
	enum e_cancel_request cancel = CANCEL_NONE;
	keeper_api_t keeper_receive;
	
	time_d timeout = -1.0;
	uint_t key_i = 2;

	luaL_argcheck( L, linda, 1, "expected a linda object!");

	if( lua_type( L, 2) == LUA_TNUMBER) // we don't want to use lua_isnumber() because of autocoercion
	{
		timeout = SIGNAL_TIMEOUT_PREPARE( lua_tonumber( L, 2));
		++ key_i;
	}
	else if( lua_isnil( L, 2)) // alternate explicit "no timeout" by passing nil before the key
	{
		++ key_i;
	}

	// are we in batched mode?
	{
		int is_batched;
		lua_pushliteral( L, BATCH_SENTINEL);
		is_batched = lua_equal( L, key_i, -1);
		lua_pop( L, 1);
		if( is_batched)
		{
			// no need to pass linda.batched in the keeper state
			++ key_i;
			// make sure the keys are of a valid type
			check_key_types( L, key_i, key_i);
			// receive multiple values from a single slot
			keeper_receive = KEEPER_API( receive_batched);
			// we expect a user-defined amount of return value
			expected_pushed_min = (int)luaL_checkinteger( L, key_i + 1);
			expected_pushed_max = (int)luaL_optinteger( L, key_i + 2, expected_pushed_min);
			// don't forget to count the key in addition to the values
			++ expected_pushed_min;
			++ expected_pushed_max;
			if( expected_pushed_min > expected_pushed_max)
			{
				return luaL_error( L, "batched min/max error");
			}
		}
		else
		{
			// make sure the keys are of a valid type
			check_key_types( L, key_i, lua_gettop( L));
			// receive a single value, checking multiple slots
			keeper_receive = KEEPER_API( receive);
			// we expect a single (value, key) pair of returned values
			expected_pushed_min = expected_pushed_max = 2;
		}
	}

	{
		struct s_Keeper *K = keeper_acquire( linda);
		for( ;;)
		{
			// all arguments of receive() but the first are passed to the keeper's receive function
			pushed = keeper_call( K->L, keeper_receive, L, linda, key_i);
			if( pushed < 0)
			{
				break;
			}
			if( pushed > 0)
			{
				ASSERT_L( pushed >= expected_pushed_min && pushed <= expected_pushed_max);
				// replace sentinels with real nils
				keeper_toggle_nil_sentinels( L, lua_gettop( L) - pushed, 0);
				// To be done from within the 'K' locking area
				//
				SIGNAL_ALL( &linda->read_happened);
				break;

			}
			if( timeout == 0.0)
			{
				break;  /* instant timeout */
			}
			/* nothing received; wait until timeout */

			cancel = cancel_test( L);   // testing here causes no delays
			if( cancel != CANCEL_NONE) // if user wants to cancel, the call returns without providing anything
			{
				break;
			}

			// change status of lane to "waiting"
			{
				struct s_lane* s;
				enum e_status prev_status = ERROR_ST; // prevent 'might be used uninitialized' warnings
				STACK_GROW( L, 1);

				STACK_CHECK( L);
				lua_pushlightuserdata( L, CANCEL_TEST_KEY);
				lua_rawget( L, LUA_REGISTRYINDEX);
				s = lua_touserdata( L, -1);     // lightuserdata (true 's_lane' pointer) or nil if in the main Lua state
				lua_pop( L, 1);
				STACK_END( L, 0);
				if( s)
				{
					prev_status = s->status; // RUNNING, most likely
					ASSERT_L( prev_status == RUNNING); // but check, just in case
					s->status = WAITING;
					ASSERT_L( s->waiting_on == NULL);
					s->waiting_on = &linda->write_happened;
				}
				// not enough data to read: wakeup when data was sent, or when timeout is reached
				if( !SIGNAL_WAIT( &linda->write_happened, &K->lock_, timeout))
				{
					if( s)
					{
						s->waiting_on = NULL;
						s->status = prev_status;
					}
					break;
				}
				if( s)
				{
					s->waiting_on = NULL;
					s->status = prev_status;
				}
			}
		}
		keeper_release( K);
	}

	// must trigger error after keeper state has been released
	if( pushed < 0)
	{
		return luaL_error( L, "tried to copy unsupported types");
	}

	// raise an error interrupting execution only in case of hard cancel
	if( cancel == CANCEL_HARD)
		cancel_error( L);

	return pushed;
}


/*
* = linda_set( linda_ud, key_num|str|bool|lightuserdata [,value] )
*
* Set a value to Linda.
* TODO: what do we do if we set to non-nil and limit is 0?
*
* Existing slot value is replaced, and possible queue entries removed.
*/
LUAG_FUNC( linda_set)
{
	struct s_Linda *linda = lua_toLinda( L, 1);
	bool_t has_value = !lua_isnil( L, 3);
	luaL_argcheck( L, linda, 1, "expected a linda object!");
	luaL_argcheck( L, lua_gettop( L) <= 3, 4, "too many arguments");

	// make sure the key is of a valid type
	check_key_types( L, 2, 2);

	{
		int pushed;
		struct s_Keeper *K = keeper_acquire( linda);
		// no nil->sentinel toggling, we really clear the linda contents for the given key with a set()
		pushed = keeper_call( K->L, KEEPER_API( set), L, linda, 2);
		if( pushed >= 0) // no error?
		{
			ASSERT_L( pushed == 0);

			/* Set the signal from within 'K' locking.
			*/
			if( has_value)
			{
				SIGNAL_ALL( &linda->write_happened);
			}
		}
		keeper_release( K);
		// must trigger error after keeper state has been released
		if( pushed < 0)
		{
			return luaL_error( L, "tried to copy unsupported types");
		}
	}

	return 0;
}


/*
 * [val] = linda_count( linda_ud, [key [, ...]])
 *
 * Get a count of the pending elements in the specified keys
 */
LUAG_FUNC( linda_count)
{
	struct s_Linda *linda= lua_toLinda( L, 1);
	int pushed;

	luaL_argcheck( L, linda, 1, "expected a linda object!");
	// make sure the keys are of a valid type
	check_key_types( L, 2, lua_gettop( L));

	{
		struct s_Keeper *K = keeper_acquire( linda);
		pushed = keeper_call( K->L, KEEPER_API( count), L, linda, 2);
		keeper_release( K);
		if( pushed < 0)
		{
			return luaL_error( L, "tried to count an invalid key");
		}
	}
	return pushed;
}


/*
* [val]= linda_get( linda_ud, key_num|str|bool|lightuserdata )
*
* Get a value from Linda.
* TODO: add support to get multiple values?
*/
LUAG_FUNC( linda_get)
{
	struct s_Linda *linda= lua_toLinda( L, 1);
	int pushed;

	luaL_argcheck( L, linda, 1, "expected a linda object!");
	// make sure the key is of a valid type
	check_key_types( L, 2, 2);

	{
		struct s_Keeper *K = keeper_acquire( linda);
		pushed = keeper_call( K->L, KEEPER_API( get), L, linda, 2);
		ASSERT_L( pushed==0 || pushed==1 );
		if( pushed > 0)
		{
			keeper_toggle_nil_sentinels( L, lua_gettop( L) - pushed, 0);
		}
		keeper_release(K);
		// must trigger error after keeper state has been released
		if( pushed < 0)
		{
			return luaL_error( L, "tried to copy unsupported types");
		}
	}

	return pushed;
}


/*
* = linda_limit( linda_ud, key_num|str|bool|lightuserdata, uint [, ...] )
*
* Set limits to 1 or more Linda keys.
*/
LUAG_FUNC( linda_limit)
{
	struct s_Linda* linda= lua_toLinda( L, 1 );

	luaL_argcheck( L, linda, 1, "expected a linda object!");
	// make sure we got a key and a limit
	luaL_argcheck( L, lua_gettop( L) == 3, 2, "wrong number of arguments");
	// make sure we got a numeric limit
	luaL_checknumber( L, 3);
	// make sure the key is of a valid type
	check_key_types( L, 2, 2);

	{
		struct s_Keeper* K = keeper_acquire( linda);
		int pushed = keeper_call( K->L, KEEPER_API( limit), L, linda, 2);
		ASSERT_L( pushed <= 0); // either error or no return values
		keeper_release( K);
		// must trigger error after keeper state has been released
		if( pushed < 0)
		{
			return luaL_error( L, "tried to copy unsupported types");
		}
	}

	return 0;
}


/*
* lightuserdata= linda_deep( linda_ud )
*
* Return the 'deep' userdata pointer, identifying the Linda.
*
* This is needed for using Lindas as key indices (timer system needs it);
* separately created proxies of the same underlying deep object will have
* different userdata and won't be known to be essentially the same deep one
* without this.
*/
LUAG_FUNC( linda_deep ) {
    struct s_Linda *linda= lua_toLinda( L, 1 );
    luaL_argcheck( L, linda, 1, "expected a linda object!");
    lua_pushlightuserdata( L, linda );      // just the address
    return 1;
}


/*
* string = linda:__tostring( linda_ud)
*
* Return the stringification of a linda
*
* Useful for concatenation or debugging purposes
*/

static int linda_tostring( lua_State* L, int _idx, bool_t _opt)
{
	struct s_Linda* linda = lua_toLinda( L, _idx);
	if( !_opt)
	{
		luaL_argcheck( L, linda, _idx, "expected a linda object!");
	}
	if( linda)
	{
		char text[32];
		int len;
		if( linda->name[0])
			len = sprintf( text, "Linda: %.*s", (int)sizeof(text) - 8, linda->name);
		else
			len = sprintf( text, "Linda: %p", linda);
		lua_pushlstring( L, text, len);
		return 1;
	}
	return 0;
}

LUAG_FUNC( linda_tostring)
{
	return linda_tostring( L, 1, FALSE);
}


/*
* string = linda:__concat( a, b)
*
* Return the concatenation of a pair of items, one of them being a linda
*
* Useful for concatenation or debugging purposes
*/
LUAG_FUNC( linda_concat)
{                                   // linda1? linda2?
	bool_t atLeastOneLinda = FALSE;
	// Lua semantics enforce that one of the 2 arguments is a Linda, but not necessarily both.
	if( linda_tostring( L, 1, TRUE))
	{
		atLeastOneLinda = TRUE;
		lua_replace( L, 1);
	}
	if( linda_tostring( L, 2, TRUE))
	{
		atLeastOneLinda = TRUE;
		lua_replace( L, 2);
	}
	if( !atLeastOneLinda) // should not be possible
	{
		return luaL_error( L, "internal error: linda_concat called on non-Linda");
	}
	lua_concat( L, 2);
	return 1;
}

/*
 * table = linda:dump()
 * return a table listing all pending data inside the linda
 */
LUAG_FUNC( linda_dump)
{
	struct s_Linda* linda = lua_toLinda( L, 1);
	return keeper_push_linda_storage( L, linda);
}

/*
* Identity function of a shared userdata object.
* 
*   lightuserdata= linda_id( "new" [, ...] )
*   = linda_id( "delete", lightuserdata )
*
* Creation and cleanup of actual 'deep' objects. 'luaG_...' will wrap them into
* regular userdata proxies, per each state using the deep data.
*
*   tbl= linda_id( "metatable" )
*
* Returns a metatable for the proxy objects ('__gc' method not needed; will
* be added by 'luaG_...')
*
*   string= linda_id( "module")
*
* Returns the name of the module that a state should require
* in order to keep a handle on the shared library that exported the idfunc
*
*   = linda_id( str, ... )
*
* For any other strings, the ID function must not react at all. This allows
* future extensions of the system. 
*/
static void linda_id( lua_State*L, char const * const which)
{
    if (strcmp( which, "new" )==0)
    {
        struct s_Linda *s;
        size_t name_len = 0;
        char const* linda_name = NULL;
        int const top = lua_gettop( L);

        if( top > 0 && lua_type( L, top) == LUA_TSTRING)
        {
            linda_name = lua_tostring( L, top);
            name_len = strlen( linda_name);
        }

        /* The deep data is allocated separately of Lua stack; we might no
        * longer be around when last reference to it is being released.
        * One can use any memory allocation scheme.
        */
        s= (struct s_Linda *) malloc( sizeof(struct s_Linda) + name_len); // terminating 0 is already included
        ASSERT_L(s);

        SIGNAL_INIT( &s->read_happened );
        SIGNAL_INIT( &s->write_happened );
        s->name[0] = 0;
        memcpy( s->name, linda_name, name_len ? name_len + 1 : 0);

        lua_pushlightuserdata( L, s );
    }
    else if( strcmp( which, "delete" ) == 0)
    {
        struct s_Keeper* K;
        struct s_Linda* l= lua_touserdata( L, 1);
        ASSERT_L( l);

        /* Clean associated structures in the keeper state.
        */
        K = keeper_acquire( l);
        if( K && K->L) // can be NULL if this happens during main state shutdown (lanes is GC'ed -> no keepers -> no need to cleanup)
        {
            keeper_call( K->L, KEEPER_API( clear), L, l, 0);
            keeper_release( K);
        }

        /* There aren't any lanes waiting on these lindas, since all proxies
        * have been gc'ed. Right?
        */
        SIGNAL_FREE( &l->read_happened);
        SIGNAL_FREE( &l->write_happened);
        free( l);
    }
    else if (strcmp( which, "metatable" )==0)
    {

        STACK_CHECK( L);
        lua_newtable(L);
        // metatable is its own index
        lua_pushvalue( L, -1);
        lua_setfield( L, -2, "__index");

        // protect metatable from external access
        lua_pushliteral( L, "Linda");
        lua_setfield( L, -2, "__metatable");

        lua_pushcfunction( L, LG_linda_tostring);
        lua_setfield( L, -2, "__tostring");

        // Decoda __towatch support
        lua_pushcfunction( L, LG_linda_dump);
        lua_setfield( L, -2, "__towatch");

        lua_pushcfunction( L, LG_linda_concat);
        lua_setfield( L, -2, "__concat");

        //
        // [-1]: linda metatable
        lua_pushcfunction( L, LG_linda_send );
        lua_setfield( L, -2, "send" );

        lua_pushcfunction( L, LG_linda_receive );
        lua_setfield( L, -2, "receive" );

        lua_pushcfunction( L, LG_linda_limit );
        lua_setfield( L, -2, "limit" );

        lua_pushcfunction( L, LG_linda_set );
        lua_setfield( L, -2, "set" );
    
        lua_pushcfunction( L, LG_linda_count );
        lua_setfield( L, -2, "count" );
    
        lua_pushcfunction( L, LG_linda_get );
        lua_setfield( L, -2, "get" );

        lua_pushcfunction( L, LG_linda_deep );
        lua_setfield( L, -2, "deep" );

        lua_pushcfunction( L, LG_linda_dump);
        lua_setfield( L, -2, "dump" );
        
        lua_pushliteral( L, BATCH_SENTINEL);
        lua_setfield(L, -2, "batched");

        STACK_END( L, 1);
    }
    else if( strcmp( which, "module") == 0)
    {
        // linda is a special case because we know lanes must be loaded from the main lua state
        // to be able to ever get here, so we know it will remain loaded as long a the main state is around
        // in other words, forever.
        lua_pushnil( L);
        // other idfuncs must push a string naming the module they come from
        //lua_pushliteral( L, "lanes.core");
    }
}

/*
 * ud = lanes.linda()
 *
 * returns a linda object
 */
LUAG_FUNC( linda)
{
	int const top = lua_gettop( L);
	luaL_argcheck( L, top <= 1, top, "too many arguments");
	if( top == 1)
		luaL_checktype( L, 1, LUA_TSTRING);
	return luaG_deep_userdata( L, linda_id);
}

/*
 * ###############################################################################################
 * ########################################## Finalizer ##########################################
 * ###############################################################################################
 */

//---
// void= finalizer( finalizer_func )
//
// finalizer_func( [err, stack_tbl] )
//
// Add a function that will be called when exiting the lane, either via
// normal return or an error.
//
LUAG_FUNC( set_finalizer )
{
    STACK_GROW(L,3);
    
    // Get the current finalizer table (if any)
    //
    push_registry_table( L, FINALIZER_REG_KEY, TRUE /*do create if none*/ );

    lua_pushinteger( L, lua_rawlen(L,-1)+1 );
    lua_pushvalue( L, 1 );  // copy of the function
    lua_settable( L, -3 );
    
    lua_pop(L,1);
    return 0;
}


//---
// Run finalizers - if any - with the given parameters
//
// If 'rc' is nonzero, error message and stack index are available as:
//      [-1]: stack trace (table)
//      [-2]: error message (any type)
//
// Returns:
//      0 if finalizers were run without error (or there were none)
//      LUA_ERRxxx return code if any of the finalizers failed
//
// TBD: should we add stack trace on failing finalizer, wouldn't be hard..
//
static int run_finalizers( lua_State*L, int lua_rc )
{
    unsigned error_index, tbl_index;
    unsigned n;
    int rc= 0;
    
    if (!push_registry_table(L, FINALIZER_REG_KEY, FALSE /*don't create one*/))
        return 0;   // no finalizers

    tbl_index= lua_gettop(L);
    error_index= (lua_rc!=0) ? tbl_index-2 : 0;   // absolute indices

    STACK_GROW(L,4);

    // [-1]: { func [, ...] }
    //
    for( n = (unsigned int)lua_rawlen( L, -1); n > 0; -- n)
    {
        unsigned args= 0;
        lua_pushinteger( L,n );
        lua_gettable( L, -2 );
        
        // [-1]: function
        // [-2]: finalizers table

        if (error_index) {
            lua_pushvalue( L, error_index );
            lua_pushvalue( L, error_index+1 );  // stack trace
            args= 2;
        }

        rc= lua_pcall( L, args, 0 /*retvals*/, 0 /*no errfunc*/ );
            //
            // LUA_ERRRUN / LUA_ERRMEM
    
        if( rc != LUA_OK)
        {
            // [-1]: error message
            //
            // If one finalizer fails, don't run the others. Return this
            // as the 'real' error, preceding that we could have had (or not)
            // from the actual code.
            //
            break;
        }
    }
    
    lua_remove(L,tbl_index);   // take finalizer table out of stack

    return rc;
}

/*
 * ###############################################################################################
 * ########################################### Threads ###########################################
 * ###############################################################################################
 */

//---
// = thread_cancel( lane_ud [,timeout_secs=0.0] [,force_kill_bool=false] )
//
// The originator thread asking us specifically to cancel the other thread.
//
// 'timeout': <0: wait forever, until the lane is finished
//            0.0: just signal it to cancel, no time waited
//            >0: time to wait for the lane to detect cancellation
//
// 'force_kill': if true, and lane does not detect cancellation within timeout,
//            it is forcefully killed. Using this with 0.0 timeout means just kill
//            (unless the lane is already finished).
//
// Returns: true if the lane was already finished (DONE/ERROR_ST/CANCELLED) or if we
//          managed to cancel it.
//          false if the cancellation timed out, or a kill was needed.
//

typedef enum
{
	CR_Timeout,
	CR_Cancelled,
	CR_Killed
} cancel_result;

static cancel_result thread_cancel( struct s_lane *s, double secs, bool_t force)
{
	cancel_result result;

	// remember that lanes are not transferable: only one thread can cancel a lane, so no multithreading issue here
	// We can read 's->status' without locks, but not wait for it (if Posix no PTHREAD_TIMEDJOIN)
	if( s->mstatus == KILLED)
	{
		result = CR_Killed;
	}
	else if( s->status < DONE)
	{
		// signal the linda the wake up the thread so that it can react to the cancel query
		// let us hope we never land here with a pointer on a linda that has been destroyed...
		if( secs < 0.0)
		{
			s->cancel_request = CANCEL_SOFT;    // it's now signaled to stop
			// negative timeout: we don't want to truly abort the lane, we just want it to react to cancel_test() on its own
			// say we succeeded though
			result = CR_Cancelled;
		}
		else
		{
			s->cancel_request = CANCEL_HARD;    // it's now signaled to stop
			{
				SIGNAL_T *waiting_on = s->waiting_on;
				if( s->status == WAITING && waiting_on != NULL)
				{
					SIGNAL_ALL( waiting_on);
				}
			}

			result = THREAD_WAIT( &s->thread, secs, &s->done_signal, &s->done_lock, &s->status) ? CR_Cancelled : CR_Timeout;

			if( (result == CR_Timeout) && force)
			{
				// Killing is asynchronous; we _will_ wait for it to be done at
				// GC, to make sure the data structure can be released (alternative
				// would be use of "cancellation cleanup handlers" that at least
				// PThread seems to have).
				//
				THREAD_KILL( &s->thread);
				s->mstatus = KILLED;     // mark 'gc' to wait for it
				// note that s->status value must remain to whatever it was at the time of the kill
				// because we need to know if we can lua_close() the Lua State or not.
				result = CR_Killed;
			}
		}
	}
	else
	{
		// say "ok" by default, including when lane is already done
		result = CR_Cancelled;
	}
	return result;
}

static MUTEX_T selfdestruct_cs;
    //
    // Protects modifying the selfdestruct chain

#define SELFDESTRUCT_END ((struct s_lane *)(-1))
    //
    // The chain is ended by '(struct s_lane*)(-1)', not NULL:
    //      'selfdestruct_first -> ... -> ... -> (-1)'

struct s_lane* volatile selfdestruct_first = SELFDESTRUCT_END;

/*
 * Add the lane to selfdestruct chain; the ones still running at the end of the
 * whole process will be cancelled.
 */
static void selfdestruct_add( struct s_lane *s ) {

    MUTEX_LOCK( &selfdestruct_cs );
    {
        assert( s->selfdestruct_next == NULL );

        s->selfdestruct_next= selfdestruct_first;
        selfdestruct_first= s;
    }
    MUTEX_UNLOCK( &selfdestruct_cs );
}

/*
 * A free-running lane has ended; remove it from selfdestruct chain
 */
static bool_t selfdestruct_remove( struct s_lane *s )
{
    bool_t found = FALSE;
    MUTEX_LOCK( &selfdestruct_cs );
    {
        // Make sure (within the MUTEX) that we actually are in the chain
        // still (at process exit they will remove us from chain and then
        // cancel/kill).
        //
        if (s->selfdestruct_next != NULL) {
            struct s_lane **ref= (struct s_lane **) &selfdestruct_first;
    
            while( *ref != SELFDESTRUCT_END ) {
                if (*ref == s) {
                    *ref= s->selfdestruct_next;
                    s->selfdestruct_next= NULL;
                    found= TRUE;
                    break;
                }
                ref= (struct s_lane **) &((*ref)->selfdestruct_next);
            }
            assert( found );
        }
    }
    MUTEX_UNLOCK( &selfdestruct_cs );
    return found;
}

// Initialized by 'init_once_LOCKED()': the deep userdata Linda object
// used for timers (each lane will get a proxy to this)
//
volatile DEEP_PRELUDE* timer_deep;  // = NULL

/*
** mutex-protected allocator for use with Lua states that have non-threadsafe allocators (such as LuaJIT)
*/
struct ProtectedAllocator_s
{
	lua_Alloc allocf;
	void* ud;
	MUTEX_T lock;
};
void * protected_lua_Alloc( void *ud, void *ptr, size_t osize, size_t nsize)
{
	void* p;
	struct ProtectedAllocator_s* s = (struct ProtectedAllocator_s*) ud;
	MUTEX_LOCK( &s->lock);
	p = s->allocf( s->ud, ptr, osize, nsize);
	MUTEX_UNLOCK( &s->lock);
	return p;
}

/*
* Process end; cancel any still free-running threads
*/
static int selfdestruct_gc( lua_State* L)
{
	while( selfdestruct_first != SELFDESTRUCT_END) // true at most once!
	{
		// Signal _all_ still running threads to exit (including the timer thread)
		//
		MUTEX_LOCK( &selfdestruct_cs );
		{
			struct s_lane* s = selfdestruct_first;
			while( s != SELFDESTRUCT_END )
			{
				// attempt a regular unforced hard cancel with a small timeout
				bool_t cancelled = THREAD_ISNULL( s->thread) || thread_cancel( s, 0.0001, FALSE);
				// if we failed, and we know the thread is waiting on a linda
				if( cancelled == FALSE && s->status == WAITING && s->waiting_on != NULL)
				{
					// signal the linda the wake up the thread so that it can react to the cancel query
					// let us hope we never land here with a pointer on a linda that has been destroyed...
					SIGNAL_T *waiting_on = s->waiting_on;
					//s->waiting_on = NULL; // useful, or not?
					SIGNAL_ALL( waiting_on);
				}
				s = s->selfdestruct_next;
			}
		}
		MUTEX_UNLOCK( &selfdestruct_cs );

		// When noticing their cancel, the lanes will remove themselves from
		// the selfdestruct chain.

		// TBD: Not sure if Windows (multi core) will require the timed approach,
		//      or single Yield. I don't have machine to test that (so leaving
		//      for timed approach).    -- AKa 25-Oct-2008

		// OS X 10.5 (Intel) needs more to avoid segfaults.
		//
		// "make test" is okay. 100's of "make require" are okay.
		//
		// Tested on MacBook Core Duo 2GHz and 10.5.5:
		//  -- AKa 25-Oct-2008
		//
		{
			lua_Number const shutdown_timeout = lua_tonumber( L, lua_upvalueindex( 1));
			double const t_until = now_secs() + shutdown_timeout;

			while( selfdestruct_first != SELFDESTRUCT_END)
			{
				YIELD();    // give threads time to act on their cancel
				{
					// count the number of cancelled thread that didn't have the time to act yet
					int n = 0;
					double t_now = 0.0;
					MUTEX_LOCK( &selfdestruct_cs);
					{
						struct s_lane* s = selfdestruct_first;
						while( s != SELFDESTRUCT_END)
						{
							if( s->cancel_request == CANCEL_HARD)
								++ n;
							s = s->selfdestruct_next;
						}
					}
					MUTEX_UNLOCK( &selfdestruct_cs);
					// if timeout elapsed, or we know all threads have acted, stop waiting
					t_now = now_secs();
					if( n == 0 || ( t_now >= t_until))
					{
						DEBUGSPEW_CODE( fprintf( stderr, "%d uncancelled lane(s) remain after waiting %fs at process end.\n", n, shutdown_timeout - (t_until - t_now)));
						break;
					}
				}
			}
		}

		//---
		// Kill the still free running threads
		//
		if( selfdestruct_first != SELFDESTRUCT_END)
		{
			unsigned int n = 0;
			// first thing we did was to raise the linda signals the threads were waiting on (if any)
			// therefore, any well-behaved thread should be in CANCELLED state
			// these are not running, and the state can be closed
			MUTEX_LOCK( &selfdestruct_cs);
			{
				struct s_lane* s= selfdestruct_first;
				while( s != SELFDESTRUCT_END)
				{
					struct s_lane* next_s = s->selfdestruct_next;
					s->selfdestruct_next = NULL;     // detach from selfdestruct chain
					if( !THREAD_ISNULL( s->thread)) // can be NULL if previous 'soft' termination succeeded
					{
						THREAD_KILL( &s->thread);
#if THREADAPI == THREADAPI_PTHREAD
						// pthread: make sure the thread is really stopped!
						THREAD_WAIT( &s->thread, -1, &s->done_signal, &s->done_lock, &s->status);
#endif // THREADAPI == THREADAPI_PTHREAD
					}
					// NO lua_close() in this case because we don't know where execution of the state was interrupted
					lane_cleanup( s);
					s = next_s;
					++ n;
				}
				selfdestruct_first = SELFDESTRUCT_END;
			}
			MUTEX_UNLOCK( &selfdestruct_cs);

			DEBUGSPEW_CODE( fprintf( stderr, "Killed %d lane(s) at process end.\n", n));
		}
	}
#if !HAVE_KEEPER_ATEXIT_DESINIT
	close_keepers();
#endif // !HAVE_KEEPER_ATEXIT_DESINIT

	// remove the protected allocator, if any
	{
		void* ud;
		lua_Alloc allocf = lua_getallocf( L, &ud);

		if( allocf == protected_lua_Alloc)
		{
			struct ProtectedAllocator_s* s = (struct ProtectedAllocator_s*) ud;
			lua_setallocf( L, s->allocf, s->ud);
			MUTEX_FREE( &s->lock);
			s->allocf( s->ud, s, sizeof( struct ProtectedAllocator_s), 0);
		}
	}

	return 0;
}


// To allow free-running threads (longer lifespan than the handle's)
// 'struct s_lane' are malloc/free'd and the handle only carries a pointer.
// This is not deep userdata since the handle's not portable among lanes.
//
#define lua_toLane(L,i)  (* ((struct s_lane**) lua_touserdata(L,i)))


/*
* Check if the thread in question ('L') has been signalled for cancel.
*
* Called by cancellation hooks and/or pending Linda operations (because then
* the check won't affect performance).
*
* Returns TRUE if any locks are to be exited, and 'cancel_error()' called,
* to make execution of the lane end.
*/
static enum e_cancel_request cancel_test( lua_State* L)
{
	struct s_lane* s;

	STACK_GROW( L, 1);

	STACK_CHECK( L);
	lua_pushlightuserdata( L, CANCEL_TEST_KEY);
	lua_rawget( L, LUA_REGISTRYINDEX);
	s = lua_touserdata( L, -1);     // lightuserdata (true 's_lane' pointer) / nil
	lua_pop( L, 1);
	STACK_END( L, 0);

	// 's' is NULL for the original main state (no-one can cancel that)
	//
	return s ? s->cancel_request : CANCEL_NONE;
}

static void cancel_error( lua_State*L ) {
    STACK_GROW(L,1);
    lua_pushlightuserdata( L, CANCEL_ERROR );    // special error value
    lua_error(L);   // no return
}

static void cancel_hook( lua_State*L, lua_Debug *ar )
{
	(void)ar;
	if( cancel_test( L) != CANCEL_NONE)
		cancel_error( L);
}


//---
// bool = cancel_test()
//
// Available inside the global namespace of lanes
// returns a boolean saying if a cancel request is pending
//
LUAG_FUNC( cancel_test)
{
	enum e_cancel_request test = cancel_test( L);
	lua_pushboolean( L, test != CANCEL_NONE);
	return 1;
}

//---
// = _single( [cores_uint=1] )
//
// Limits the process to use only 'cores' CPU cores. To be used for performance
// testing on multicore devices. DEBUGGING ONLY!
//
LUAG_FUNC( set_singlethreaded)
{
	uint_t cores = luaG_optunsigned( L, 1, 1);
	(void) cores; // prevent "unused" warning

#ifdef PLATFORM_OSX
#ifdef _UTILBINDTHREADTOCPU
	if( cores > 1)
	{
		return luaL_error( L, "Limiting to N>1 cores not possible");
	}
	// requires 'chudInitialize()'
	utilBindThreadToCPU(0);     // # of CPU to run on (we cannot limit to 2..N CPUs?)
#else
	return luaL_error( L, "Not available: compile with _UTILBINDTHREADTOCPU");
#endif
#else
	return luaL_error( L, "not implemented");
#endif

	return 0;
}


/*
* str= lane_error( error_val|str )
*
* Called if there's an error in some lane; add call stack to error message 
* just like 'lua.c' normally does.
*
* ".. will be called with the error message and its return value will be the 
*     message returned on the stack by lua_pcall."
*
* Note: Rather than modifying the error message itself, it would be better
*     to provide the call stack (as string) completely separated. This would
*     work great with non-string error values as well (current system does not).
*     (This is NOT possible with the Lua 5.1 'lua_pcall()'; we could of course
*     implement a Lanes-specific 'pcall' of our own that does this). TBD!!! :)
*       --AKa 22-Jan-2009
*/
#ifdef ERROR_FULL_STACK

# define STACK_TRACE_KEY ((void*)lane_error)     // used as registry key
# define EXTENDED_STACK_TRACE_KEY ((void*)LG_set_error_reporting)     // used as registry key

LUAG_FUNC( set_error_reporting)
{
	bool_t equal;
	luaL_checktype( L, 1, LUA_TSTRING);
	lua_pushliteral( L, "extended");
	equal = lua_rawequal( L, -1, 1);
	lua_pop( L, 1);
	if( equal)
	{
		goto done;
	}
	lua_pushliteral( L, "basic");
	equal = !lua_rawequal( L, -1, 1);
	lua_pop( L, 1);
	if( equal)
	{
		return luaL_error( L, "unsupported error reporting model");
	}
done:
	lua_pushlightuserdata( L, EXTENDED_STACK_TRACE_KEY);
	lua_pushboolean( L, equal);
	lua_rawset( L, LUA_REGISTRYINDEX);
	return 0;
}

static int lane_error( lua_State* L)
{
	lua_Debug ar;
	unsigned lev, n;
	bool_t extended;

	// [1]: error message (any type)

	assert( lua_gettop( L) == 1);

	// Don't do stack survey for cancelled lanes.
	//
#if 1
	if( lua_touserdata( L, 1) == CANCEL_ERROR)
		return 1;   // just pass on
#endif

	lua_pushlightuserdata( L, EXTENDED_STACK_TRACE_KEY);
	lua_gettable( L, LUA_REGISTRYINDEX);
	extended = lua_toboolean( L, -1);
	lua_pop( L, 1);

	// Place stack trace at 'registry[lane_error]' for the 'lua_pcall()'
	// caller to fetch. This bypasses the Lua 5.1 limitation of only one
	// return value from error handler to 'lua_pcall()' caller.

	// It's adequate to push stack trace as a table. This gives the receiver
	// of the stack best means to format it to their liking. Also, it allows
	// us to add more stack info later, if needed.
	//
	// table of { "sourcefile.lua:<line>", ... }
	//
	STACK_GROW( L, 4);
	lua_newtable( L);

	// Best to start from level 1, but in some cases it might be a C function
	// and we don't get '.currentline' for that. It's okay - just keep level
	// and table index growing separate.    --AKa 22-Jan-2009
	//
	lev = 0;
	n = 1;
	while( lua_getstack( L, ++ lev, &ar))
	{
		lua_getinfo( L, extended ? "Sln" : "Sl", &ar);
		if( extended)
		{
			lua_newtable( L);

			lua_pushstring( L, ar.source);
			lua_setfield( L, -2, "source");

			lua_pushinteger( L, ar.currentline);
			lua_setfield( L, -2, "currentline");

			lua_pushstring( L, ar.name);
			lua_setfield( L, -2, "name");

			lua_pushstring( L, ar.namewhat);
			lua_setfield( L, -2, "namewhat");

			lua_pushstring( L, ar.what);
			lua_setfield( L, -2, "what");

			lua_rawseti(L, -2, n ++);
		}
		else if (ar.currentline > 0)
		{
			lua_pushinteger( L, n++ );
			lua_pushfstring( L, "%s:%d", ar.short_src, ar.currentline );
			lua_settable( L, -3 );
		}
	}

	lua_pushlightuserdata( L, STACK_TRACE_KEY);
	lua_insert( L ,-2);
	lua_settable( L, LUA_REGISTRYINDEX);

	assert( lua_gettop( L) == 1);

	return 1;   // the untouched error value
}
#endif // ERROR_FULL_STACK

LUAG_FUNC( set_debug_threadname)
{
	struct s_lane* s = lua_touserdata( L, lua_upvalueindex( 1));
	luaL_checktype( L, -1, LUA_TSTRING);                           // "name"
	// store a hidden reference in the registry to make sure the string is kept around even if a lane decides to manually change the "decoda_name" global...
	lua_pushlightuserdata( L, LG_set_debug_threadname);            // "name" lud
	lua_pushvalue( L, -2);                                         // "name" lud "name"
	lua_rawset( L, LUA_REGISTRYINDEX);                             // "name"
	s->debug_name = lua_tostring( L, -1);
	// keep a direct pointer on the string
	THREAD_SETNAME( s->debug_name);
	// to see VM name in Decoda debugger Virtual Machine window
	lua_setglobal( L, "decoda_name");                              //
	return 0;
}

#if USE_DEBUG_SPEW
// can't use direct LUA_x errcode indexing because the sequence is not the same between Lua 5.1 and 5.2 :-(
// LUA_ERRERR doesn't have the same value
struct errcode_name
{
	int code;
	char const* name;
};

static struct errcode_name s_errcodes[] =
{
	{ LUA_OK, "LUA_OK"},
	{ LUA_YIELD, "LUA_YIELD"},
	{ LUA_ERRRUN, "LUA_ERRRUN"},
	{ LUA_ERRSYNTAX, "LUA_ERRSYNTAX"},
	{ LUA_ERRMEM, "LUA_ERRMEM"},
	{ LUA_ERRGCMM, "LUA_ERRGCMM"},
	{ LUA_ERRERR, "LUA_ERRERR"},
};
static char const* get_errcode_name( int _code)
{
	int i;
	for( i = 0; i < 7; ++ i)
	{
		if( s_errcodes[i].code == _code)
		{
			return s_errcodes[i].name;
		}
	}
	return "<NULL>";
}
#endif // USE_DEBUG_SPEW

//---
static THREAD_RETURN_T THREAD_CALLCONV lane_main( void *vs)
{
    struct s_lane *s= (struct s_lane *)vs;
    int rc, rc2;
    lua_State*L= s->L;

#if HAVE_LANE_TRACKING
    if( tracking_first)
    {
        tracking_add( s);
    }
#endif // HAVE_LANE_TRACKING

   s->status= RUNNING;  // PENDING -> RUNNING

    // Tie "set_finalizer()" to the state
    //
    lua_pushcfunction( L, LG_set_finalizer );
    lua_setglobal( L, "set_finalizer" );

    // Tie "set_debug_threadname()" to the state
    //
    lua_pushlightuserdata( L, s);
    lua_pushcclosure( L, LG_set_debug_threadname, 1);
    lua_setglobal( L, "set_debug_threadname" );

    // Tie "cancel_test()" to the state
    //
    lua_pushcfunction( L, LG_cancel_test);
    lua_setglobal( L, "cancel_test");

#ifdef ERROR_FULL_STACK
    // Tie "set_error_reporting()" to the state
    //
    lua_pushcfunction( L, LG_set_error_reporting);
    lua_setglobal( L, "set_error_reporting");

    STACK_GROW( L, 1 );
    lua_pushcfunction( L, lane_error );
    lua_insert( L, 1 );

    // [1]: error handler
    // [2]: function to run
    // [3..top]: parameters
    //
    rc= lua_pcall( L, lua_gettop(L)-2, LUA_MULTRET, 1 /*error handler*/ );
        // 0: no error, body return values are on the stack
        // LUA_ERRRUN: cancellation or a runtime error (error pushed on stack)
        // LUA_ERRMEM: memory allocation error
        // LUA_ERRERR: error while running the error handler (if any)

    assert( rc!=LUA_ERRERR );   // since we've authored it

    lua_remove(L,1);    // remove error handler

    // Lua 5.1 error handler is limited to one return value; taking stack trace via registry
    if( rc != LUA_OK)
    {
        STACK_GROW(L,1);
        lua_pushlightuserdata( L, STACK_TRACE_KEY );
        lua_gettable(L, LUA_REGISTRYINDEX); // yields nil if no stack was generated (in case of cancellation for example)

        // For cancellation, a stack trace isn't placed
        //
        assert( lua_istable(L,2) || (lua_touserdata(L,1)==CANCEL_ERROR) );
        
        // Just leaving the stack trace table on the stack is enough to get
        // it through to the master.
    }

#else
    // This code does not use 'lane_error'
    //
    // [1]: function to run
    // [2..top]: parameters
    //
    rc= lua_pcall( L, lua_gettop(L)-1, LUA_MULTRET, 0 /*no error handler*/ );
        // LUA_OK(0): no error
        // LUA_ERRRUN(2): a runtime error (error pushed on stack)
        // LUA_ERRMEM(4): memory allocation error
#endif

    DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "Lane %p body: %s (%s)\n" INDENT_END, L, get_errcode_name( rc), (lua_touserdata(L,1)==CANCEL_ERROR) ? "cancelled" : lua_typename( L, lua_type( L, 1))));
    //STACK_DUMP(L);
    // Call finalizers, if the script has set them up.
    //
    rc2 = run_finalizers( L, rc);
    DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "Lane %p finalizer: %s\n" INDENT_END, L, get_errcode_name( rc2)));
    if( rc2 != LUA_OK)
    {
        // Error within a finalizer!  
        // 
        // [-1]: error message

        rc= rc2;    // we're overruling the earlier script error or normal return

        lua_insert( L,1 );  // make error message [1]
        lua_settop( L,1 );  // remove all rest

        // Place an empty stack table just to keep the API simple (always when
        // there's an error, there's also stack table - though it may be empty).
        //
        lua_newtable(L);
    }
    s->waiting_on = NULL; // just in case
    if( selfdestruct_remove( s)) // check and remove (under lock!)
    {
        // We're a free-running thread and no-one's there to clean us up.
        //
        lua_close( s->L );
        s->L = L = 0;

        lane_cleanup( s);
    }
    else
    {
        // leave results (1..top) or error message + stack trace (1..2) on the stack - master will copy them

        enum e_status st= 
            (rc==0) ? DONE 
                    : (lua_touserdata(L,1)==CANCEL_ERROR) ? CANCELLED 
                    : ERROR_ST;

        // Posix no PTHREAD_TIMEDJOIN:
        // 		'done_lock' protects the -> DONE|ERROR_ST|CANCELLED state change
        //
#if THREADWAIT_METHOD == THREADWAIT_CONDVAR
        MUTEX_LOCK( &s->done_lock);
        {
#endif // THREADWAIT_METHOD == THREADWAIT_CONDVAR
            s->status = st;
#if THREADWAIT_METHOD == THREADWAIT_CONDVAR
            SIGNAL_ONE( &s->done_signal);   // wake up master (while 's->done_lock' is on)
        }
        MUTEX_UNLOCK( &s->done_lock);
#endif // THREADWAIT_METHOD == THREADWAIT_CONDVAR
    }
    return 0;   // ignored
}

// --- If a client wants to transfer stuff of a given module from the current state to another Lane, the module must be required
// with lanes.require, that will call the regular 'require', then populate lookup databases in source and keeper states
// module = lanes.require( "modname")
// upvalue[1]: _G.require
LUAG_FUNC( require)
{
	char const* name = lua_tostring( L, 1);
	DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "lanes.require %s BEGIN\n" INDENT_END, name));
	DEBUGSPEW_CODE( ++ debugspew_indent_depth);
	lua_pushvalue( L, lua_upvalueindex(1));   // "name" require
	lua_pushvalue( L, 1);                     // "name" require "name"
	lua_call( L, 1, 1);                       // "name" module
	populate_func_lookup_table( L, -1, name);
	lua_insert( L, -2);                       // module "name"
	populate_keepers( L);
	lua_pop( L, 1);                           // module
	DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "lanes.require %s END\n" INDENT_END, name));
	DEBUGSPEW_CODE( -- debugspew_indent_depth);
	return 1;
}

//---
// lane_ud= thread_new( function, [libs_str], 
//                          [cancelstep_uint=0], 
//                          [prio_int=0],
//                          [globals_tbl],
//                          [package_tbl],
//                          [required],
//                          [... args ...] )
//
// Upvalues: metatable to use for 'lane_ud'
//

LUAG_FUNC( thread_new)
{
	lua_State* L2;
	struct s_lane* s;
	struct s_lane** ud;

	char const* libs = lua_tostring( L, 2);
	int const on_state_create = lua_isfunction( L, 3) ? 3 : 0;
	uint_t cs = luaG_optunsigned( L, 4, 0);
	int prio = (int) luaL_optinteger( L, 5, 0);
	uint_t glob = lua_isnoneornil( L, 6) ? 0 : 6;
	uint_t package = lua_isnoneornil( L,7) ? 0 : 7;
	uint_t required = lua_isnoneornil( L, 8) ? 0 : 8;

#define FIXED_ARGS 8
	uint_t args= lua_gettop(L) - FIXED_ARGS;

	if( prio < THREAD_PRIO_MIN || prio > THREAD_PRIO_MAX)
	{
		return luaL_error( L, "Priority out of range: %d..+%d (%d)", THREAD_PRIO_MIN, THREAD_PRIO_MAX, prio);
	}

	/* --- Create and prepare the sub state --- */
	DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "thread_new: setup\n" INDENT_END));
	DEBUGSPEW_CODE( ++ debugspew_indent_depth);

	// populate with selected libraries at  the same time
	//
	L2 = luaG_newstate( L, on_state_create, libs);

	STACK_GROW( L, 2);
	STACK_GROW( L2, 3);

	// give a default "Lua" name to the thread to see VM name in Decoda debugger
	lua_pushfstring( L2, "Lane #%p", L2);
	lua_setglobal( L2, "decoda_name");

	ASSERT_L( lua_gettop(L2) == 0);

	DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "thread_new: update 'package'\n" INDENT_END));
	// package
	if( package)
	{
		luaG_inter_copy_package( L, L2, package);
	}

	// modules to require in the target lane *before* the function is transfered!

	STACK_CHECK( L);
	STACK_CHECK( L2);
	if( required)
	{
		int nbRequired = 1;
		DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "thread_new: require 'required' list\n" INDENT_END));
		DEBUGSPEW_CODE( ++ debugspew_indent_depth);
		// should not happen, was checked in lanes.lua before calling thread_new()
		if( lua_type( L, required) != LUA_TTABLE)
		{
			return luaL_error( L, "expected required module list as a table, got %s", luaL_typename( L, required));
		}

		lua_pushnil( L);
		while( lua_next( L, required) != 0)
		{
			if( lua_type( L, -1) != LUA_TSTRING || lua_type( L, -2) != LUA_TNUMBER || lua_tonumber( L, -2) != nbRequired)
			{
				return luaL_error( L, "required module list should be a list of strings");
			}
			else
			{
				// require the module in the target state, and populate the lookup table there too
				size_t len;
				char const* name = lua_tolstring( L, -1, &len);

				// require the module in the target lane
				STACK_GROW( L2, 2);
				STACK_CHECK( L2);
				lua_getglobal( L2, "require");                       // require()?
				if( lua_isnil( L2, -1))
				{
					lua_pop( L2, 1);                                   //
					luaL_error( L, "cannot pre-require modules without loading 'package' library first");
				}
				else
				{
					lua_pushlstring( L2, name, len);                   // require() name
					lua_pcall( L2, 1, 1, 0);                           // ret
					STACK_MID( L2, 1);
					// after requiring the module, register the functions it exported in our name<->function database
					populate_func_lookup_table( L2, -1, name);
					STACK_MID( L2, 1);
					lua_pop( L2, 1);
					// don't require this module in the keeper states as well, use lanes.require() for that!
					//populate_keepers( L);
				}
				STACK_END( L2, 0);
			}
			lua_pop( L, 1);
			++ nbRequired;
		}
		DEBUGSPEW_CODE( -- debugspew_indent_depth);
	}
	STACK_END( L2, 0);
	STACK_END( L, 0);

	// Appending the specified globals to the global environment
	// *after* stdlibs have been loaded and modules required, in case we transfer references to native functions they exposed...
	//
	if( glob != 0)
	{
		DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "thread_new: transfer globals\n" INDENT_END));
		STACK_CHECK( L);
		STACK_CHECK( L2);
		if( !lua_istable( L, glob))
		{
			return luaL_error( L, "Expected table, got %s", luaL_typename( L, glob));
		}

		DEBUGSPEW_CODE( ++ debugspew_indent_depth);
		lua_pushnil( L);
		lua_pushglobaltable( L2); // Lua 5.2 wants us to push the globals table on the stack
		while( lua_next( L, glob))
		{
			luaG_inter_copy( L, L2, 2);     // moves the key/value pair to the L2 stack
			// assign it in L2's globals table
			lua_rawset( L2, -3);
			lua_pop( L, 1);
		}
		lua_pop( L2, 1);

		STACK_END( L2, 0);
		STACK_END( L, 0);
		DEBUGSPEW_CODE( -- debugspew_indent_depth);
	}

	ASSERT_L( lua_gettop( L2) == 0);

	// Lane main function
	//
	STACK_CHECK( L);
	if( lua_type( L, 1) == LUA_TFUNCTION)
	{
		int res;
		DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "thread_new: transfer lane body\n" INDENT_END));
		DEBUGSPEW_CODE( ++ debugspew_indent_depth);
		lua_pushvalue( L, 1);
		res = luaG_inter_move( L, L2, 1);    // L->L2
		DEBUGSPEW_CODE( -- debugspew_indent_depth);
		if( res != 0)
		{
			return luaL_error( L, "tried to copy unsupported types");
		}
		STACK_MID( L, 0);
	}
	else if( lua_type( L, 1) == LUA_TSTRING)
	{
		// compile the string
		if( luaL_loadstring( L2, lua_tostring( L, 1)) != 0)
		{
			return luaL_error( L, "error when parsing lane function code");
		}
	}

	ASSERT_L( lua_gettop( L2) == 1);
	ASSERT_L( lua_isfunction( L2, 1));

	// revive arguments
	//
	if( args > 0)
	{
		int res;
		DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "thread_new: transfer lane arguments\n" INDENT_END));
		DEBUGSPEW_CODE( ++ debugspew_indent_depth);
		res = luaG_inter_copy( L, L2, args);    // L->L2
		DEBUGSPEW_CODE( -- debugspew_indent_depth);
		if( res != 0)
			return luaL_error( L, "tried to copy unsupported types");
	}
	STACK_MID( L, 0);

	ASSERT_L( (uint_t)lua_gettop( L2) == 1+args);
	ASSERT_L( lua_isfunction( L2, 1));

	// 's' is allocated from heap, not Lua, since its life span may surpass 
	// the handle's (if free running thread)
	//
	ud = lua_newuserdata( L, sizeof( struct s_lane*));
	ASSERT_L( ud);

	s = *ud = malloc( sizeof( struct s_lane));
	ASSERT_L( s);

	//memset( s, 0, sizeof(struct s_lane) );
	s->L= L2;
	s->status= PENDING;
	s->waiting_on = NULL;
	s->debug_name = NULL;
	s->cancel_request = CANCEL_NONE;

#if THREADWAIT_METHOD == THREADWAIT_CONDVAR
	MUTEX_INIT( &s->done_lock);
	SIGNAL_INIT( &s->done_signal);
#endif // THREADWAIT_METHOD == THREADWAIT_CONDVAR
	s->mstatus= NORMAL;
	s->selfdestruct_next= NULL;
#if HAVE_LANE_TRACKING
	s->tracking_next = NULL;
#endif // HAVE_LANE_TRACKING

	// Set metatable for the userdata
	//
	lua_pushvalue( L, lua_upvalueindex(1) );
	lua_setmetatable( L, -2 );
	STACK_MID( L, 1);

	// Clear environment for the userdata
	//
	lua_newtable( L);
	lua_setuservalue( L, -2);

	// Place 's' in registry, for 'cancel_test()' (even if 'cs'==0 we still
	// do cancel tests at pending send/receive).
	//
	lua_pushlightuserdata( L2, CANCEL_TEST_KEY );
	lua_pushlightuserdata( L2, s );
	lua_rawset( L2, LUA_REGISTRYINDEX );

	if (cs)
	{
		lua_sethook( L2, cancel_hook, LUA_MASKCOUNT, cs );
	}

	DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "thread_new: launching thread\n" INDENT_END));
	THREAD_CREATE( &s->thread, lane_main, s, prio );
	STACK_END( L, 1);

	DEBUGSPEW_CODE( -- debugspew_indent_depth);

	return 1;
}


//---
// = thread_gc( lane_ud )
//
// Cleanup for a thread userdata. If the thread is still executing, leave it
// alive as a free-running thread (will clean up itself).
//
// * Why NOT cancel/kill a loose thread: 
//
// At least timer system uses a free-running thread, they should be handy
// and the issue of canceling/killing threads at gc is not very nice, either
// (would easily cause waits at gc cycle, which we don't want).
//
LUAG_FUNC( thread_gc)
{
	struct s_lane* s = lua_toLane( L, 1);

	// We can read 's->status' without locks, but not wait for it
	// test KILLED state first, as it doesn't need to enter the selfdestruct chain
	if( s->mstatus == KILLED)
	{
		// Make sure a kill has proceeded, before cleaning up the data structure.
		//
		// NO lua_close() in this case because we don't know where execution of the state was interrupted
		DEBUGSPEW_CODE( fprintf( stderr, "** Joining with a killed thread (needs testing) **"));
		// make sure the thread is no longer running, just like thread_join()
		if(! THREAD_ISNULL( s->thread))
			THREAD_WAIT( &s->thread, -1, &s->done_signal, &s->done_lock, &s->status);
		// we know the thread was killed while the Lua VM was not doing anything: we should be able to close it without crashing
		// now, thread_cancel() will not forcefully kill a lane with s->status >= DONE, so I am not sure it can ever happen
		if( s->status >= DONE && s->L)
		{
			lua_close( s->L);
			s->L = 0;
		}
		DEBUGSPEW_CODE( fprintf( stderr, "** Joined ok **"));
	}
	else if( s->status < DONE)
	{
		// still running: will have to be cleaned up later
		selfdestruct_add( s);
		assert( s->selfdestruct_next);
		return 0;

	}
	else if( s->L)
	{
		// no longer accessing the Lua VM: we can close right now
		lua_close( s->L);
		s->L = 0;
	}

	// Clean up after a (finished) thread
	lane_cleanup( s);
	return 0;
}

LUAG_FUNC( thread_cancel)
{
	if( lua_gettop( L) < 1 || lua_type( L, 1) != LUA_TUSERDATA)
	{
		return luaL_error( L, "invalid argument #1, did you use ':' as you should?");
	}
	else
	{
		struct s_lane* s = lua_toLane( L, 1);
		double secs = 0.0;
		uint_t force_i = 2;
		cancel_result result;
		bool_t force;

		if( lua_isnumber( L, 2))
		{
			secs = lua_tonumber( L, 2);
			if( secs < 0.0 && lua_gettop( L) > 2)
			{
				return luaL_error( L, "can't force a soft cancel");
			}
			++ force_i;
		}
		else if( lua_isnil( L, 2))
		{
			++ force_i;
		}

		force = lua_toboolean( L, force_i);     // FALSE if nothing there

		result = thread_cancel( s, secs, force);
		switch( result)
		{
			case CR_Timeout:
			lua_pushboolean( L, 0);
			lua_pushstring( L, "timeout");
			return 2;

			case CR_Cancelled:
			lua_pushboolean( L, 1);
			return 1;
			
			case CR_Killed:
			lua_pushboolean( L, 0);
			lua_pushstring( L, "killed");
			return 2;
		}
	}
	// should never happen, only here to prevent the compiler from complaining of "not all control paths returning a value"
	return 0;
}

//---
// str= thread_status( lane )
//
// Returns: "pending"   not started yet
//          -> "running"   started, doing its work..
//             <-> "waiting"   blocked in a receive()
//                -> "done"     finished, results are there
//                   / "error"     finished at an error, error value is there
//                   / "cancelled"   execution cancelled by M (state gone)
//
static char const * thread_status_string( struct s_lane *s)
{
	enum e_status st = s->status;    // read just once (volatile)
	char const * str =
		(s->mstatus == KILLED) ? "killed" : // new to v3.3.0!
		(st==PENDING) ? "pending" :
		(st==RUNNING) ? "running" :    // like in 'co.status()'
		(st==WAITING) ? "waiting" :
		(st==DONE) ? "done" :
		(st==ERROR_ST) ? "error" :
		(st==CANCELLED) ? "cancelled" : NULL;
	return str;
}

static int push_thread_status( lua_State*L, struct s_lane *s)
{
	char const * const str = thread_status_string( s);
	ASSERT_L( str);

	lua_pushstring( L, str );
	return 1;
}


//---
// [...] | [nil, err_any, stack_tbl]= thread_join( lane_ud [, wait_secs=-1] )
//
//  timeout:   returns nil
//  done:      returns return values (0..N)
//  error:     returns nil + error value + stack table
//  cancelled: returns nil
//
LUAG_FUNC( thread_join)
{
	struct s_lane* const s = lua_toLane( L, 1);
	double wait_secs= luaL_optnumber(L,2,-1.0);
	lua_State*L2= s->L;
	int ret;
	bool_t done;

	done = THREAD_ISNULL( s->thread) || THREAD_WAIT( &s->thread, wait_secs, &s->done_signal, &s->done_lock, &s->status);
	if (!done || !L2)
		return 0;      // timeout: pushes none, leaves 'L2' alive

	// Thread is DONE/ERROR_ST/CANCELLED; all ours now

	STACK_GROW( L, 1);

	if( s->mstatus == KILLED) // OS thread was killed if thread_cancel was forced
	{
		// in that case, even if the thread was killed while DONE/ERROR_ST/CANCELLED, ignore regular return values
		
		lua_pushnil( L);
		lua_pushliteral( L, "killed");
		ret = 2;
	}
	else
	{
		switch( s->status)
		{
			case DONE:
			{
				uint_t n = lua_gettop( L2);       // whole L2 stack
				if( (n > 0) && (luaG_inter_move( L2, L, n) != 0))
				{
					return luaL_error( L, "tried to copy unsupported types");
				}
				ret = n;
			}
			break;

			case ERROR_ST:
			lua_pushnil( L);
			if( luaG_inter_move( L2, L, 2) != 0)    // error message at [-2], stack trace at [-1]
			{
				return luaL_error( L, "tried to copy unsupported types");
			}
			ret= 3;
			break;

			case CANCELLED:
			ret= 0;
			break;

			default:
			DEBUGSPEW_CODE( fprintf( stderr, "Status: %d\n", s->status));
			ASSERT_L( FALSE ); ret= 0;
		}
		lua_close( L2);
	}
	s->L = 0;

	return ret;
}


//---
// thread_index( ud, key) -> value
//
// If key is found in the environment, return it
// If key is numeric, wait until the thread returns and populate the environment with the return values
// If the return values signal an error, propagate it
// If key is "status" return the thread status
// Else raise an error
LUAG_FUNC( thread_index)
{
	int const UD = 1;
	int const KEY = 2;
	int const USR = 3;
	struct s_lane *s = lua_toLane( L, UD);
	ASSERT_L( lua_gettop( L) == 2);

	STACK_GROW( L, 8); // up to 8 positions are needed in case of error propagation

	// If key is numeric, wait until the thread returns and populate the environment with the return values
	if( lua_type( L, KEY) == LUA_TNUMBER)
	{
		// first, check that we don't already have an environment that holds the requested value
		{
			// If key is found in the uservalue, return it
			lua_getuservalue( L, UD);
			lua_pushvalue( L, KEY);
			lua_rawget( L, USR);
			if( !lua_isnil( L, -1))
			{
				return 1;
			}
			lua_pop( L, 1);
		}
		{
			// check if we already fetched the values from the thread or not
			bool_t fetched;
			lua_Integer key = lua_tointeger( L, KEY);
			lua_pushinteger( L, 0);
			lua_rawget( L, USR);
			fetched = !lua_isnil( L, -1);
			lua_pop( L, 1); // back to our 2 args + uservalue on the stack
			if( !fetched)
			{
				lua_pushinteger( L, 0);
				lua_pushboolean( L, 1);
				lua_rawset( L, USR);
				// wait until thread has completed
				lua_pushcfunction( L, LG_thread_join);
				lua_pushvalue( L, UD);
				lua_call( L, 1, LUA_MULTRET); // all return values are on the stack, at slots 4+
				switch( s->status)
				{
					default:
					if( s->mstatus != KILLED)
					{
						// this is an internal error, we probably never get here
						lua_settop( L, 0);
						lua_pushliteral( L, "Unexpected status: ");
						lua_pushstring( L, thread_status_string( s));
						lua_concat( L, 2);
						lua_error( L);
						break;
					}
					// fall through if we are killed, as we got nil, "killed" on the stack

					case DONE: // got regular return values
					{
						int i, nvalues = lua_gettop( L) - 3;
						for( i = nvalues; i > 0; -- i)
						{
							// pop the last element of the stack, to store it in the uservalue at its proper index
							lua_rawseti( L, USR, i);
						}
					}
					break;

					case ERROR_ST: // got 3 values: nil, errstring, callstack table
					// me[-2] could carry the stack table, but even 
					// me[-1] is rather unnecessary (and undocumented);
					// use ':join()' instead.   --AKa 22-Jan-2009
					ASSERT_L( lua_isnil( L, 4) && !lua_isnil( L, 5) && lua_istable( L, 6));
					// store errstring at key -1
					lua_pushnumber( L, -1);
					lua_pushvalue( L, 5);
					lua_rawset( L, USR);
					break;

					case CANCELLED:
					 // do nothing
					break;
				}
			}
			lua_settop( L, 3);                                                // UD KEY ENV
			if( key != -1)
			{
				lua_pushnumber( L, -1);                                         // UD KEY ENV -1
				lua_rawget( L, USR);                                            // UD KEY ENV "error"
				if( !lua_isnil( L, -1)) // an error was stored
				{
					// Note: Lua 5.1 interpreter is not prepared to show
					//       non-string errors, so we use 'tostring()' here
					//       to get meaningful output.  --AKa 22-Jan-2009
					//
					//       Also, the stack dump we get is no good; it only
					//       lists our internal Lanes functions. There seems
					//       to be no way to switch it off, though.
					//
					// Level 3 should show the line where 'h[x]' was read
					// but this only seems to work for string messages
					// (Lua 5.1.4). No idea, why.   --AKa 22-Jan-2009
					lua_getmetatable( L, UD);                                     // UD KEY ENV "error" mt
					lua_getfield( L, -1, "cached_error");                         // UD KEY ENV "error" mt error()
					lua_getfield( L, -2, "cached_tostring");                      // UD KEY ENV "error" mt error() tostring()
					lua_pushvalue( L, 4);                                         // UD KEY ENV "error" mt error() tostring() "error"
					lua_call( L, 1, 1); // tostring( errstring) -- just in case   // UD KEY ENV "error" mt error() "error"
					lua_pushinteger( L, 3);                                       // UD KEY ENV "error" mt error() "error" 3
					lua_call( L, 2, 0); // error( tostring( errstring), 3)        // UD KEY ENV "error" mt
				}
				else
				{
					lua_pop( L, 1); // back to our 3 arguments on the stack
				}
			}
			lua_rawgeti( L, USR, (int)key);
		}
		return 1;
	}
	if( lua_type( L, KEY) == LUA_TSTRING)
	{
		char const * const keystr = lua_tostring( L, KEY);
		lua_settop( L, 2); // keep only our original arguments on the stack
		if( strcmp( keystr, "status") == 0)
		{
			return push_thread_status( L, s); // push the string representing the status
		}
		// return UD.metatable[key]
		lua_getmetatable( L, UD); // UD KEY mt
		lua_replace( L, -3);      // mt KEY
		lua_rawget( L, -2);       // mt value
		// only "cancel" and "join" are registered as functions, any other string will raise an error
		if( lua_iscfunction( L, -1))
		{
			return 1;
		}
		return luaL_error( L, "can't index a lane with '%s'", keystr);
	}
	// unknown key
	lua_getmetatable( L, UD);
	lua_getfield( L, -1, "cached_error");
	lua_pushliteral( L, "Unknown key: ");
	lua_pushvalue( L, KEY);
	lua_concat( L, 2);
	lua_call( L, 1, 0); // error( "Unknown key: " .. key) -> doesn't return
	return 0;
}

#if HAVE_LANE_TRACKING
//---
// threads() -> {}|nil
//
// Return a list of all known lanes
LUAG_FUNC( threads)
{
	int const top = lua_gettop( L);
	// List _all_ still running threads
	//
	MUTEX_LOCK( &tracking_cs);
	if( tracking_first && tracking_first != TRACKING_END)
	{
		struct s_lane* s = tracking_first;
		lua_newtable( L);                                          // {}
		while( s != TRACKING_END)
		{
			if( s->debug_name)
				lua_pushstring( L, s->debug_name);                     // {} "name"
			else
				lua_pushfstring( L, "Lane %p", s);                     // {} "name"
			push_thread_status( L, s);                               // {} "name" "status"
			lua_rawset( L, -3);                                      // {}
			s = s->tracking_next;
		}
	}
	MUTEX_UNLOCK( &tracking_cs);
	return lua_gettop( L) - top;
}
#endif // HAVE_LANE_TRACKING

/*
 * ###############################################################################################
 * ######################################## Timer support ########################################
 * ###############################################################################################
 */

/*
* secs= now_secs()
*
* Returns the current time, as seconds (millisecond resolution).
*/
LUAG_FUNC( now_secs )
{
    lua_pushnumber( L, now_secs() );
    return 1;
}

/*
* wakeup_at_secs= wakeup_conv( date_tbl )
*/
LUAG_FUNC( wakeup_conv )
{
    int year, month, day, hour, min, sec, isdst;
    struct tm t;
    memset( &t, 0, sizeof( t));
        //
        // .year (four digits)
        // .month (1..12)
        // .day (1..31)
        // .hour (0..23)
        // .min (0..59)
        // .sec (0..61)
        // .yday (day of the year)
        // .isdst (daylight saving on/off)

  STACK_CHECK( L);
    lua_getfield( L, 1, "year" ); year= (int)lua_tointeger(L,-1); lua_pop(L,1);
    lua_getfield( L, 1, "month" ); month= (int)lua_tointeger(L,-1); lua_pop(L,1);
    lua_getfield( L, 1, "day" ); day= (int)lua_tointeger(L,-1); lua_pop(L,1);
    lua_getfield( L, 1, "hour" ); hour= (int)lua_tointeger(L,-1); lua_pop(L,1);
    lua_getfield( L, 1, "min" ); min= (int)lua_tointeger(L,-1); lua_pop(L,1);
    lua_getfield( L, 1, "sec" ); sec= (int)lua_tointeger(L,-1); lua_pop(L,1);

    // If Lua table has '.isdst' we trust that. If it does not, we'll let
    // 'mktime' decide on whether the time is within DST or not (value -1).
    //
    lua_getfield( L, 1, "isdst" );
    isdst= lua_isboolean(L,-1) ? lua_toboolean(L,-1) : -1;
    lua_pop(L,1);
  STACK_END( L, 0);

    t.tm_year= year-1900;
    t.tm_mon= month-1;     // 0..11
    t.tm_mday= day;        // 1..31
    t.tm_hour= hour;       // 0..23
    t.tm_min= min;         // 0..59
    t.tm_sec= sec;         // 0..60
    t.tm_isdst= isdst;     // 0/1/negative

    lua_pushnumber( L, (double) mktime( &t));   // ms=0
    return 1;
}

/*
 * ###############################################################################################
 * ######################################## Module linkage #######################################
 * ###############################################################################################
 */

static const struct luaL_Reg lanes_functions [] = {
    {"linda", LG_linda},
    {"now_secs", LG_now_secs},
#if HAVE_LANE_TRACKING
    {"threads", LG_threads},
#endif // HAVE_LANE_TRACKING
    {"wakeup_conv", LG_wakeup_conv},
    {"nameof", luaG_nameof},
    {"set_singlethreaded", LG_set_singlethreaded},
    {NULL, NULL}
};


/*
 * minimal function registration for keepers, just so that we can populate the transfer databases with them
 * without recursively deadlocking ourselves during one-time inits
 */
void register_core_libfuncs_for_keeper( lua_State* L)
{
	DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "lanes.register_core_libfuncs_for_keeper()\n" INDENT_END));
	DEBUGSPEW_CODE( ++ debugspew_indent_depth);
	STACK_GROW( L, 1);
	STACK_CHECK( L);
	lua_newtable( L);
	luaG_registerlibfuncs( L, lanes_functions);
	STACK_MID( L, 1);
	populate_func_lookup_table( L, -1, "lanes.core");
	lua_pop( L, 1);
	STACK_END( L, 0);
	DEBUGSPEW_CODE( -- debugspew_indent_depth);
}

/*
** One-time initializations
*/
static void init_once_LOCKED( lua_State* L, int const _on_state_create, int const nbKeepers, lua_Number _shutdown_timeout, bool_t _track_lanes, bool_t verbose_errors)
{
	GVerboseErrors = verbose_errors;
#if (defined PLATFORM_WIN32) || (defined PLATFORM_POCKETPC)
	now_secs();     // initialize 'now_secs()' internal offset
#endif

#if (defined PLATFORM_OSX) && (defined _UTILBINDTHREADTOCPU)
	chudInitialize();
#endif

#if HAVE_LANE_TRACKING
	tracking_first = _track_lanes ? TRACKING_END : NULL;
#endif // HAVE_LANE_TRACKING

	// Locks for 'tools.c' inc/dec counters
	//
	MUTEX_INIT( &deep_lock );
	MUTEX_INIT( &mtid_lock );

	// Serialize calls to 'require' from now on, also in the primary state
	//
	MUTEX_RECURSIVE_INIT( &require_cs );

	serialize_require( L);

	// Linked chains handling
	//
	MUTEX_INIT( &selfdestruct_cs );
#if HAVE_LANE_TRACKING
	MUTEX_INIT( &tracking_cs);
#endif // HAVE_LANE_TRACKING

	//---
	// Linux needs SCHED_RR to change thread priorities, and that is only
	// allowed for sudo'ers. SCHED_OTHER (default) has no priorities.
	// SCHED_OTHER threads are always lower priority than SCHED_RR.
	//
	// ^-- those apply to 2.6 kernel.  IF **wishful thinking** these 
	//     constraints will change in the future, non-sudo priorities can 
	//     be enabled also for Linux.
	//
#ifdef PLATFORM_LINUX
	sudo= geteuid()==0;     // we are root?

	// If lower priorities (-2..-1) are wanted, we need to lift the main
	// thread to SCHED_RR and 50 (medium) level. Otherwise, we're always below 
	// the launched threads (even -2).
	//
#ifdef LINUX_SCHED_RR
	if (sudo) {
		struct sched_param sp= {0}; sp.sched_priority= _PRIO_0;
		PT_CALL( pthread_setschedparam( pthread_self(), SCHED_RR, &sp) );
	}
#endif // LINUX_SCHED_RR
#endif // PLATFORM_LINUX
	{
		char const* err = init_keepers( L, _on_state_create, nbKeepers);
		if (err)
		{
			(void) luaL_error( L, "Unable to initialize: %s", err );
		}
	}

	// Initialize 'timer_deep'; a common Linda object shared by all states
	//
	ASSERT_L( timer_deep == NULL);

	STACK_CHECK( L);
	{
		// proxy_ud= deep_userdata( idfunc )
		//
		lua_pushliteral( L, "lanes-timer"); // push a name for debug purposes
		luaG_deep_userdata( L, linda_id);
		STACK_MID( L, 2);
		lua_remove( L, -2); // remove the name as we no longer need it

		ASSERT_L( lua_isuserdata(L,-1) );

		// Proxy userdata contents is only a 'DEEP_PRELUDE*' pointer
		//
		timer_deep = * (DEEP_PRELUDE**) lua_touserdata( L, -1);
		ASSERT_L( timer_deep && (timer_deep->refcount == 1) && timer_deep->deep);

		// The host Lua state must always have a reference to this Linda object in order for the timer_deep pointer to be valid.
		// So store a reference that we will never actually use.
		// at the same time, use this object as a 'desinit' marker:
		// when the main lua State is closed, this object will be GC'ed
		{
			lua_newuserdata( L, 1);
			lua_newtable( L);
			lua_pushnumber( L, _shutdown_timeout);
			lua_pushcclosure( L, selfdestruct_gc, 1);
			lua_setfield( L, -2, "__gc");
			lua_pushliteral( L, "AtExit");
			lua_setfield( L, -2, "__metatable");
			lua_setmetatable( L, -2);
		}
		lua_insert( L, -2); // Swap key with the Linda object
		lua_rawset( L, LUA_REGISTRYINDEX);

	}
	STACK_END( L, 0);
}

static volatile long s_initCount = 0;

// upvalue 1: module name
// upvalue 2: module table
LUAG_FUNC( configure)
{
	char const* name = luaL_checkstring( L, lua_upvalueindex( 1));
	// all parameter checks are done lua-side
	int const nbKeepers = (int)lua_tointeger( L, 1);
	// all these can be nil when lanes.core is required internally! (but are only processed at first init anyway)
	int const on_state_create = lua_isfunction( L, 2) ? 2 : 0;
	lua_Number shutdown_timeout = lua_tonumber( L, 3);
	bool_t track_lanes = lua_toboolean( L, 4);
	bool_t protect_allocator = lua_toboolean( L, 5);
	bool_t verbose_errors = lua_toboolean( L, 6);

	DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "%p: lanes.configure() BEGIN\n" INDENT_END, L));
	DEBUGSPEW_CODE( ++ debugspew_indent_depth);
	STACK_CHECK( L);

	// not in init_once_LOCKED because we can have several hosted "master" Lua states where Lanes is require()d.
	if( protect_allocator)
	{
		void* ud;
		lua_Alloc allocf = lua_getallocf( L, &ud);
		if( allocf != protected_lua_Alloc) // just in case
		{
			struct ProtectedAllocator_s* s = (struct ProtectedAllocator_s*) allocf( ud, NULL, 0, sizeof( struct ProtectedAllocator_s));
			s->allocf = allocf;
			s->ud = ud;
			MUTEX_INIT( &s->lock);
			lua_setallocf( L, protected_lua_Alloc, s);
		}
	}

	// Create main module interface table
	lua_pushvalue( L, lua_upvalueindex( 2));                               // ... M
	// remove configure() (this function) from the module interface
	lua_pushnil( L);                                                       // ... M nil
	lua_setfield( L, -2, "configure");                                     // ... M
	// add functions to the module's table
	luaG_registerlibfuncs( L, lanes_functions);
	STACK_MID( L, 1);

	// metatable for threads
	// contains keys: { __gc, __index, cached_error, cached_tostring, cancel, join }
	//
	lua_newtable( L);                                                      // ... M mt
	lua_pushcfunction( L, LG_thread_gc);                                   // ... M mt LG_thread_gc
	lua_setfield( L, -2, "__gc");                                          // ... M mt
	lua_pushcfunction( L, LG_thread_index);                                // ... M mt LG_thread_index
	lua_setfield( L, -2, "__index");                                       // ... M mt
	lua_getglobal( L, "error");                                            // ... M mt error
	ASSERT_L( lua_isfunction( L, -1));
	lua_setfield( L, -2, "cached_error");                                  // ... M mt
	lua_getglobal( L, "tostring");                                         // ... M mt tostring
	ASSERT_L( lua_isfunction( L, -1));
	lua_setfield( L, -2, "cached_tostring");                               // ... M mt
	lua_pushcfunction( L, LG_thread_join);                                 // ... M mt LG_thread_join
	lua_setfield( L, -2, "join");                                          // ... M mt
	lua_pushcfunction( L, LG_thread_cancel);                               // ... M mt LG_thread_cancel
	lua_setfield( L, -2, "cancel");                                        // ... M mt
	lua_pushliteral( L, "Lane");                                           // ... M mt "Lane"
	lua_setfield( L, -2, "__metatable");                                   // ... M mt

	lua_pushcclosure( L, LG_thread_new, 1);                                // ... M LG_thread_new
	lua_setfield(L, -2, "thread_new");                                     // ... M

	// we can't register 'lanes.require' normally because we want to create an upvalued closure
	lua_getglobal( L, "require");                                          // ... M require
	lua_pushcclosure( L, LG_require, 1);                                   // ... M lanes.require
	lua_setfield( L, -2, "require");                                       // ... M

	lua_pushstring(L, VERSION);                                            // ... M VERSION
	lua_setfield(L, -2, "version");                                        // ... M

	lua_pushinteger(L, THREAD_PRIO_MAX);                                   // ... M THREAD_PRIO_MAX
	lua_setfield(L, -2, "max_prio");                                       // ... M

	lua_pushlightuserdata( L, CANCEL_ERROR);                               // ... M CANCEL_ERROR
	lua_setfield(L, -2, "cancel_error");                                   // ... M

	// register all native functions found in that module in the transferable functions database
	// we process it before _G because we don't want to find the module when scanning _G (this would generate longer names)
	// for example in package.loaded["lanes.core"].*
	populate_func_lookup_table( L, -1, name);

	// record all existing C/JIT-fast functions
	// Lua 5.2 no longer has LUA_GLOBALSINDEX: we must push globals table on the stack
	lua_pushglobaltable( L);                                               // ... M _G
	populate_func_lookup_table( L, -1, NULL);
	lua_pop( L, 1);                                                        // ... M

	STACK_MID( L, 1);
	/*
	** Making one-time initializations.
	**
	** When the host application is single-threaded (and all threading happens via Lanes)
	** there is no problem. But if the host is multithreaded, we need to lock around the
	** initializations.
	** we must do this after the populate_func_lookup_table is called, else populating the keepers will fail
	** because this makes a copy of packages.loaders, which requires the lookup tables to exist!
	*/
#if THREADAPI == THREADAPI_WINDOWS
	{
		static volatile int /*bool*/ go_ahead; // = 0
		if( InterlockedCompareExchange( &s_initCount, 1, 0) == 0)
		{
			init_once_LOCKED( L, on_state_create, nbKeepers, shutdown_timeout, track_lanes, verbose_errors);
			go_ahead = 1;    // let others pass
		}
		else
		{
			while( !go_ahead ) { Sleep(1); }    // changes threads
		}
	}
#else // THREADAPI == THREADAPI_PTHREAD
	if( s_initCount == 0)
	{
		static pthread_mutex_t my_lock = PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_lock( &my_lock);
		{
			// Recheck now that we're within the lock
			//
			if( s_initCount == 0)
			{
				init_once_LOCKED( L, on_state_create, nbKeepers, shutdown_timeout, track_lanes, verbose_errors);
				s_initCount = 1;
			}
		}
		pthread_mutex_unlock( &my_lock);
	}
#endif // THREADAPI == THREADAPI_PTHREAD
	STACK_MID( L, 1);

	assert( timer_deep != NULL);
	// init_once_LOCKED initializes timer_deep, so we must do this after, of course
	luaG_push_proxy( L, linda_id, (DEEP_PRELUDE*) timer_deep);             // ... M timer_deep
	lua_setfield( L, -2, "timer_gateway");                                 // ... M

	lua_pop( L, 1);                                                        // ...
	STACK_END( L, 0);
	DEBUGSPEW_CODE( fprintf( stderr, INDENT_BEGIN "%p: lanes.configure() END\n" INDENT_END, L));
	DEBUGSPEW_CODE( -- debugspew_indent_depth);
	// Return nothing
	return 0;
}

// helper to have correct callstacks when crashing a Win32 running on 64 bits Windows
// don't forget to toggle Debug/Exceptions/Win32 in visual Studio too!
void EnableCrashingOnCrashes()
{ 
#if 0 && defined PLATFORM_WIN32
	typedef BOOL (WINAPI *tGetPolicy)(LPDWORD lpFlags);
	typedef BOOL (WINAPI *tSetPolicy)(DWORD dwFlags);
	const DWORD EXCEPTION_SWALLOWING = 0x1;

	HMODULE kernel32 = LoadLibraryA("kernel32.dll");
	tGetPolicy pGetPolicy = (tGetPolicy)GetProcAddress(kernel32, "GetProcessUserModeExceptionPolicy");
	tSetPolicy pSetPolicy = (tSetPolicy)GetProcAddress(kernel32, 	"SetProcessUserModeExceptionPolicy");
	if (pGetPolicy && pSetPolicy)
	{
		DWORD dwFlags;
		if (pGetPolicy(&dwFlags))
		{
			// Turn off the filter
			pSetPolicy(dwFlags & ~EXCEPTION_SWALLOWING);
		}
	}
#endif // PLATFORM_WIN32
}

int LANES_API luaopen_lanes_core( lua_State* L)
{
	EnableCrashingOnCrashes();

	STACK_GROW( L, 3);
	STACK_CHECK( L);

	// Create main module interface table
	// we only have 1 closure, which must be called to configure Lanes
	lua_newtable(L);                         // M
	lua_pushvalue(L, 1);                     // M "lanes.core"
	lua_pushvalue(L, -2);                    // M "lanes.core" M
	lua_pushcclosure( L, LG_configure, 2);   // M LG_configure()
	if( s_initCount == 0)
	{
		lua_setfield( L, -2, "configure");     // M
	}
	else // already initialized: call it immediately and be done
	{
		// any parameter value will do, they will be ignored
		lua_pushinteger( L, 666);              // M LG_configure() 666
		lua_pushnil( L);                       // M LG_configure() 666 nil
		lua_call( L, 2, 0);                    // M
	}

	STACK_END( L, 1);
	return 1;
}

static int default_luaopen_lanes( lua_State* L)
{
	int rc = luaL_loadfile( L, "lanes.lua") || lua_pcall( L, 0, 1, 0);
	if( rc != LUA_OK)
	{
		return luaL_error( L, "failed to initialize embedded Lanes");
	}
	return 1;
}

// call this instead of luaopen_lanes_core() when embedding Lua and Lanes in a custom application
void LANES_API luaopen_lanes_embedded( lua_State* L, lua_CFunction _luaopen_lanes)
{
	STACK_CHECK( L);
	// pre-require lanes.core so that when lanes.lua calls require "lanes.core" it finds it is already loaded
	luaL_requiref( L, "lanes.core", luaopen_lanes_core, 0);                                       // ... lanes.core
	lua_pop( L, 1);                                                                               // ...
	STACK_MID( L, 0);
	// call user-provided function that runs the chunk "lanes.lua" from wherever they stored it
	luaL_requiref( L, "lanes", _luaopen_lanes ? _luaopen_lanes : default_luaopen_lanes, 0);       // ... lanes
	STACK_END( L, 1);
}
