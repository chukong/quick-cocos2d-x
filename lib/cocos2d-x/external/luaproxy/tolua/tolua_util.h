extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
/*
#ifndef TOLUA_RELEASE
#define TOLUA_ERROR_WHILE(L,x,e,fn) if(x){tolua_error(L,"#ferror in function "##fn,&e);return 0;}
#define TOLUA_ERROR_CHECK tolua_Error err;
#else
#define TOLUA_ERROR_WHILE(L,x,fn)
#define TOLUA_ERROR_CHECK while(0)
#endif
*/