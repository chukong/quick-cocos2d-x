/*
** Lua binding: CSArmature_luabinding
** Generated automatically by tolua++-1.0.92 on Thu May 30 17:18:37 2013.
*/

#include "CSArmature_luabinding.h"
#include "CCLuaEngine.h"

using namespace cocos2d;




#include "cocos2d.h"
#include "CSArmatureDataManager.h"
#include "CSArmature.h"
using namespace cocos2d;
using namespace cs;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ccBlendFunc (lua_State* tolua_S)
{
 ccBlendFunc* self = (ccBlendFunc*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCNodeRGBA");
 tolua_usertype(tolua_S,"Animation");
 tolua_usertype(tolua_S,"ProcessBase");
 tolua_usertype(tolua_S,"ArmatureDataManager");
 tolua_usertype(tolua_S,"Armature");
 tolua_usertype(tolua_S,"Bone");
 tolua_usertype(tolua_S,"ccBlendFunc");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CCDictionary");
 tolua_usertype(tolua_S,"CCArray");
}

/* method: play of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_play00
static int tolua_CSArmature_luabinding_ProcessBase_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
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
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  void* animation = ((void*)  tolua_touserdata(tolua_S,2,0));
  int durationTo = ((int)  tolua_tonumber(tolua_S,3,0));
  int durationTween = ((int)  tolua_tonumber(tolua_S,4,0));
  int loop = ((int)  tolua_tonumber(tolua_S,5,0));
  int tweenEasing = ((int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play(animation,durationTo,durationTween,loop,tweenEasing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_pause00
static int tolua_CSArmature_luabinding_ProcessBase_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
  {
   self->pause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_resume00
static int tolua_CSArmature_luabinding_ProcessBase_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resume'", NULL);
#endif
  {
   self->resume();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_stop00
static int tolua_CSArmature_luabinding_ProcessBase_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
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

/* method: gotoFrame of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_gotoFrame00
static int tolua_CSArmature_luabinding_ProcessBase_gotoFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  int frameIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoFrame'", NULL);
#endif
  {
   self->gotoFrame(frameIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gotoFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentFrameIndex of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_getCurrentFrameIndex00
static int tolua_CSArmature_luabinding_ProcessBase_getCurrentFrameIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentFrameIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCurrentFrameIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentFrameIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsPause of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_getIsPause00
static int tolua_CSArmature_luabinding_ProcessBase_getIsPause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsPause'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getIsPause();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIsPause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsPause of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_setIsPause00
static int tolua_CSArmature_luabinding_ProcessBase_setIsPause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsPause'", NULL);
#endif
  {
   self->setIsPause(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsPause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsComplete of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_getIsComplete00
static int tolua_CSArmature_luabinding_ProcessBase_getIsComplete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsComplete'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getIsComplete();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIsComplete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsComplete of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_setIsComplete00
static int tolua_CSArmature_luabinding_ProcessBase_setIsComplete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsComplete'", NULL);
#endif
  {
   self->setIsComplete(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsComplete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsPlaying of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_getIsPlaying00
static int tolua_CSArmature_luabinding_ProcessBase_getIsPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsPlaying'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getIsPlaying();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIsPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsPlaying of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_setIsPlaying00
static int tolua_CSArmature_luabinding_ProcessBase_setIsPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsPlaying'", NULL);
#endif
  {
   self->setIsPlaying(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentPercent of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_getCurrentPercent00
static int tolua_CSArmature_luabinding_ProcessBase_getCurrentPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentPercent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getCurrentPercent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCurrentPercent of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_setCurrentPercent00
static int tolua_CSArmature_luabinding_ProcessBase_setCurrentPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCurrentPercent'", NULL);
#endif
  {
   self->setCurrentPercent(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCurrentPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRawDuration of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_getRawDuration00
static int tolua_CSArmature_luabinding_ProcessBase_getRawDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRawDuration'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getRawDuration();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRawDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRawDuration of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_setRawDuration00
static int tolua_CSArmature_luabinding_ProcessBase_setRawDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRawDuration'", NULL);
#endif
  {
   self->setRawDuration(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRawDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLoopType of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_getLoopType00
static int tolua_CSArmature_luabinding_ProcessBase_getLoopType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLoopType'", NULL);
#endif
  {
   AnimationType tolua_ret = (AnimationType)  self->getLoopType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLoopType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLoopType of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_setLoopType00
static int tolua_CSArmature_luabinding_ProcessBase_setLoopType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  AnimationType value = ((AnimationType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLoopType'", NULL);
#endif
  {
   self->setLoopType(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLoopType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTweenEasing of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_getTweenEasing00
static int tolua_CSArmature_luabinding_ProcessBase_getTweenEasing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTweenEasing'", NULL);
#endif
  {
   TweenType tolua_ret = (TweenType)  self->getTweenEasing();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTweenEasing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTweenEasing of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_setTweenEasing00
static int tolua_CSArmature_luabinding_ProcessBase_setTweenEasing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  TweenType value = ((TweenType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTweenEasing'", NULL);
#endif
  {
   self->setTweenEasing(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTweenEasing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimationInternal of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_getAnimationInternal00
static int tolua_CSArmature_luabinding_ProcessBase_getAnimationInternal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimationInternal'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getAnimationInternal();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnimationInternal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationInternal of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_setAnimationInternal00
static int tolua_CSArmature_luabinding_ProcessBase_setAnimationInternal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationInternal'", NULL);
#endif
  {
   self->setAnimationInternal(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationInternal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimationScale of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_getAnimationScale00
static int tolua_CSArmature_luabinding_ProcessBase_getAnimationScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimationScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getAnimationScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnimationScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationScale of class  ProcessBase */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ProcessBase_setAnimationScale00
static int tolua_CSArmature_luabinding_ProcessBase_setAnimationScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProcessBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProcessBase* self = (ProcessBase*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationScale'", NULL);
#endif
  {
   self->setAnimationScale(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  Animation */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Animation_create00
static int tolua_CSArmature_luabinding_Animation_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* armature = ((Armature*)  tolua_tousertype(tolua_S,2,0));
  {
   Animation* tolua_ret = (Animation*)  Animation::create(armature);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Animation");
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

/* method: setAnimationScale of class  Animation */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Animation_setAnimationScale00
static int tolua_CSArmature_luabinding_Animation_setAnimationScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  float animationScale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationScale'", NULL);
#endif
  {
   self->setAnimationScale(animationScale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  Animation */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Animation_play00
static int tolua_CSArmature_luabinding_Animation_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  const char* animationName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int durationTo = ((int)  tolua_tonumber(tolua_S,3,-1));
  int durationTween = ((int)  tolua_tonumber(tolua_S,4,-1));
  int loop = ((int)  tolua_tonumber(tolua_S,5,-1));
  int tweenEasing = ((int)  tolua_tonumber(tolua_S,6,TWEEN_EASING_MAX));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play(animationName,durationTo,durationTween,loop,tweenEasing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playByIndex of class  Animation */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Animation_playByIndex00
static int tolua_CSArmature_luabinding_Animation_playByIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  int animationIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int durationTo = ((int)  tolua_tonumber(tolua_S,3,-1));
  int durationTween = ((int)  tolua_tonumber(tolua_S,4,-1));
  int loop = ((int)  tolua_tonumber(tolua_S,5,-1));
  int tweenEasing = ((int)  tolua_tonumber(tolua_S,6,TWEEN_EASING_MAX));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playByIndex'", NULL);
#endif
  {
   self->playByIndex(animationIndex,durationTo,durationTween,loop,tweenEasing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playByIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  Animation */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Animation_pause00
static int tolua_CSArmature_luabinding_Animation_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
  {
   self->pause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  Animation */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Animation_resume00
static int tolua_CSArmature_luabinding_Animation_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resume'", NULL);
#endif
  {
   self->resume();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  Animation */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Animation_stop00
static int tolua_CSArmature_luabinding_Animation_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getMovementCount of class  Animation */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Animation_getMovementCount00
static int tolua_CSArmature_luabinding_Animation_getMovementCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMovementCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMovementCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMovementCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedArmatureDataManager of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ArmatureDataManager_sharedArmatureDataManager00
static int tolua_CSArmature_luabinding_ArmatureDataManager_sharedArmatureDataManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ArmatureDataManager* tolua_ret = (ArmatureDataManager*)  ArmatureDataManager::sharedArmatureDataManager();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ArmatureDataManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedArmatureDataManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeArmatureSystem of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ArmatureDataManager_purgeArmatureSystem00
static int tolua_CSArmature_luabinding_ArmatureDataManager_purgeArmatureSystem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureDataManager* self = (ArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'purgeArmatureSystem'", NULL);
#endif
  {
   self->purgeArmatureSystem();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeArmatureSystem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addArmatureFileInfo of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ArmatureDataManager_addArmatureFileInfo00
static int tolua_CSArmature_luabinding_ArmatureDataManager_addArmatureFileInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureDataManager* self = (ArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
  const char* armatureName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* useExistFileInfo = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* imagePath = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* plistPath = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* configFilePath = ((const char*)  tolua_tostring(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addArmatureFileInfo'", NULL);
#endif
  {
   self->addArmatureFileInfo(armatureName,useExistFileInfo,imagePath,plistPath,configFilePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addArmatureFileInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addArmatureFileInfo of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ArmatureDataManager_addArmatureFileInfo01
static int tolua_CSArmature_luabinding_ArmatureDataManager_addArmatureFileInfo01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ArmatureDataManager* self = (ArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
  const char* imagePath = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* plistPath = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* configFilePath = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addArmatureFileInfo'", NULL);
#endif
  {
   self->addArmatureFileInfo(imagePath,plistPath,configFilePath);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CSArmature_luabinding_ArmatureDataManager_addArmatureFileInfo00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addSpriteFrameFromFile of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ArmatureDataManager_addSpriteFrameFromFile00
static int tolua_CSArmature_luabinding_ArmatureDataManager_addSpriteFrameFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureDataManager* self = (ArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
  const char* plistPath = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* imagePath = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSpriteFrameFromFile'", NULL);
#endif
  {
   self->addSpriteFrameFromFile(plistPath,imagePath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSpriteFrameFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAll of class  ArmatureDataManager */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_ArmatureDataManager_removeAll00
static int tolua_CSArmature_luabinding_ArmatureDataManager_removeAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArmatureDataManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArmatureDataManager* self = (ArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAll'", NULL);
#endif
  {
   self->removeAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_create00
static int tolua_CSArmature_luabinding_Bone_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Bone* tolua_ret = (Bone*)  Bone::create(name);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Bone");
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

/* method: create of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_create01
static int tolua_CSArmature_luabinding_Bone_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   Bone* tolua_ret = (Bone*)  Bone::create();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Bone");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CSArmature_luabinding_Bone_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChildBone of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_addChildBone00
static int tolua_CSArmature_luabinding_Bone_addChildBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  Bone* _child = ((Bone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChildBone'", NULL);
#endif
  {
   self->addChildBone(_child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChildBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParentBone of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_setParentBone00
static int tolua_CSArmature_luabinding_Bone_setParentBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  Bone* parent = ((Bone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParentBone'", NULL);
#endif
  {
   self->setParentBone(parent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParentBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParentBone of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_getParentBone00
static int tolua_CSArmature_luabinding_Bone_getParentBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParentBone'", NULL);
#endif
  {
   Bone* tolua_ret = (Bone*)  self->getParentBone();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Bone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParentBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeFromParent of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_removeFromParent00
static int tolua_CSArmature_luabinding_Bone_removeFromParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  bool recursion = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeFromParent'", NULL);
#endif
  {
   self->removeFromParent(recursion);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFromParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChildBone of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_removeChildBone00
static int tolua_CSArmature_luabinding_Bone_removeChildBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Bone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  Bone* bone = ((Bone*)  tolua_tousertype(tolua_S,2,0));
  bool recursion = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChildBone'", NULL);
#endif
  {
   self->removeChildBone(bone,recursion);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChildBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildren of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_getChildren00
static int tolua_CSArmature_luabinding_Bone_getChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildren'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getChildren();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArmature of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_getArmature00
static int tolua_CSArmature_luabinding_Bone_getArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArmature'", NULL);
#endif
  {
   Armature* tolua_ret = (Armature*)  self->getArmature();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Armature");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildArmature of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_getChildArmature00
static int tolua_CSArmature_luabinding_Bone_getChildArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildArmature'", NULL);
#endif
  {
   Armature* tolua_ret = (Armature*)  self->getChildArmature();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Armature");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIgnoreMovementBoneData of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_getIgnoreMovementBoneData00
static int tolua_CSArmature_luabinding_Bone_getIgnoreMovementBoneData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIgnoreMovementBoneData'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getIgnoreMovementBoneData();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIgnoreMovementBoneData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIgnoreMovementBoneData of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_setIgnoreMovementBoneData00
static int tolua_CSArmature_luabinding_Bone_setIgnoreMovementBoneData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIgnoreMovementBoneData'", NULL);
#endif
  {
   self->setIgnoreMovementBoneData(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIgnoreMovementBoneData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_getName00
static int tolua_CSArmature_luabinding_Bone_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  Bone */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Bone_setName00
static int tolua_CSArmature_luabinding_Bone_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  string name = ((string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_create00
static int tolua_CSArmature_luabinding_Armature_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  Bone* parentBone = ((Bone*)  tolua_tousertype(tolua_S,3,0));
  {
   Armature* tolua_ret = (Armature*)  Armature::create(name,parentBone);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Armature");
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

/* method: create of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_create01
static int tolua_CSArmature_luabinding_Armature_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Armature* tolua_ret = (Armature*)  Armature::create(name);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Armature");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CSArmature_luabinding_Armature_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_create02
static int tolua_CSArmature_luabinding_Armature_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   Armature* tolua_ret = (Armature*)  Armature::create();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Armature");
  }
 }
 return 1;
tolua_lerror:
 return tolua_CSArmature_luabinding_Armature_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendFunc of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_setBlendFunc00
static int tolua_CSArmature_luabinding_Armature_setBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  ccBlendFunc blendFunc = *((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendFunc'", NULL);
#endif
  {
   self->setBlendFunc(blendFunc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBlendFunc of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_getBlendFunc00
static int tolua_CSArmature_luabinding_Armature_getBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBlendFunc'", NULL);
#endif
  {
   ccBlendFunc tolua_ret = (ccBlendFunc)  self->getBlendFunc();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccBlendFunc)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccBlendFunc));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBone of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_addBone00
static int tolua_CSArmature_luabinding_Armature_addBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Bone",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  Bone* bone = ((Bone*)  tolua_tousertype(tolua_S,2,0));
  const char* parentName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addBone'", NULL);
#endif
  {
   self->addBone(bone,parentName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBone of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_getBone00
static int tolua_CSArmature_luabinding_Armature_getBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBone'", NULL);
#endif
  {
   Bone* tolua_ret = (Bone*)  self->getBone(name);
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Bone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeBoneParent of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_changeBoneParent00
static int tolua_CSArmature_luabinding_Armature_changeBoneParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Bone",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  Bone* bone = ((Bone*)  tolua_tousertype(tolua_S,2,0));
  const char* parentName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeBoneParent'", NULL);
#endif
  {
   self->changeBoneParent(bone,parentName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeBoneParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeBone of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_removeBone00
static int tolua_CSArmature_luabinding_Armature_removeBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Bone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  Bone* bone = ((Bone*)  tolua_tousertype(tolua_S,2,0));
  bool recursion = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeBone'", NULL);
#endif
  {
   self->removeBone(bone,recursion);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBoneDic of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_getBoneDic00
static int tolua_CSArmature_luabinding_Armature_getBoneDic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBoneDic'", NULL);
#endif
  {
   CCDictionary* tolua_ret = (CCDictionary*)  self->getBoneDic();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDictionary");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBoneDic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParentBone of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_getParentBone00
static int tolua_CSArmature_luabinding_Armature_getParentBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParentBone'", NULL);
#endif
  {
   Bone* tolua_ret = (Bone*)  self->getParentBone();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Bone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParentBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimation of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_getAnimation00
static int tolua_CSArmature_luabinding_Armature_getAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimation'", NULL);
#endif
  {
   Animation* tolua_ret = (Animation*)  self->getAnimation();
    int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Animation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimation of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_setAnimation00
static int tolua_CSArmature_luabinding_Armature_setAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  Animation* value = ((Animation*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimation'", NULL);
#endif
  {
   self->setAnimation(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_getName00
static int tolua_CSArmature_luabinding_Armature_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setName of class  Armature */
#ifndef TOLUA_DISABLE_tolua_CSArmature_luabinding_Armature_setName00
static int tolua_CSArmature_luabinding_Armature_setName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  string name = ((string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setName'", NULL);
#endif
  {
   self->setName(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CSArmature_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"SINGLE_FRAME",SINGLE_FRAME);
  tolua_constant(tolua_S,"ANIMATION_NO_LOOP",ANIMATION_NO_LOOP);
  tolua_constant(tolua_S,"ANIMATION_TO_LOOP_FRONT",ANIMATION_TO_LOOP_FRONT);
  tolua_constant(tolua_S,"ANIMATION_TO_LOOP_BACK",ANIMATION_TO_LOOP_BACK);
  tolua_constant(tolua_S,"ANIMATION_LOOP_FRONT",ANIMATION_LOOP_FRONT);
  tolua_constant(tolua_S,"ANIMATION_LOOP_BACK",ANIMATION_LOOP_BACK);
  tolua_constant(tolua_S,"ANIMATION_MAX",ANIMATION_MAX);
  tolua_constant(tolua_S,"TWEEN_EASING_MIN",TWEEN_EASING_MIN);
  tolua_constant(tolua_S,"Linear",Linear);
  tolua_constant(tolua_S,"Sine_EaseIn",Sine_EaseIn);
  tolua_constant(tolua_S,"Sine_EaseInOut",Sine_EaseInOut);
  tolua_constant(tolua_S,"Sine_EaseOut",Sine_EaseOut);
  tolua_constant(tolua_S,"Quad_EaseIn",Quad_EaseIn);
  tolua_constant(tolua_S,"Quad_EaseOut",Quad_EaseOut);
  tolua_constant(tolua_S,"Quad_EaseInOut",Quad_EaseInOut);
  tolua_constant(tolua_S,"Cubic_EaseIn",Cubic_EaseIn);
  tolua_constant(tolua_S,"Cubic_EaseOut",Cubic_EaseOut);
  tolua_constant(tolua_S,"Cubic_EaseInOut",Cubic_EaseInOut);
  tolua_constant(tolua_S,"Quart_EaseIn",Quart_EaseIn);
  tolua_constant(tolua_S,"Quart_EaseOut",Quart_EaseOut);
  tolua_constant(tolua_S,"Quart_EaseInOut",Quart_EaseInOut);
  tolua_constant(tolua_S,"Quint_EaseIn",Quint_EaseIn);
  tolua_constant(tolua_S,"Quint_EaseOut",Quint_EaseOut);
  tolua_constant(tolua_S,"Quint_EaseInOut",Quint_EaseInOut);
  tolua_constant(tolua_S,"Expo_EaseIn",Expo_EaseIn);
  tolua_constant(tolua_S,"Expo_EaseOut",Expo_EaseOut);
  tolua_constant(tolua_S,"Expo_EaseInOut",Expo_EaseInOut);
  tolua_constant(tolua_S,"Circ_EaseIn",Circ_EaseIn);
  tolua_constant(tolua_S,"Circ_EaseOut",Circ_EaseOut);
  tolua_constant(tolua_S,"Circ_EaseInOut",Circ_EaseInOut);
  tolua_constant(tolua_S,"Elastic_EaseIn",Elastic_EaseIn);
  tolua_constant(tolua_S,"Elastic_EaseOut",Elastic_EaseOut);
  tolua_constant(tolua_S,"Elastic_EaseInOut",Elastic_EaseInOut);
  tolua_constant(tolua_S,"Back_EaseIn",Back_EaseIn);
  tolua_constant(tolua_S,"Back_EaseOut",Back_EaseOut);
  tolua_constant(tolua_S,"Back_EaseInOut",Back_EaseInOut);
  tolua_constant(tolua_S,"Bounce_EaseIn",Bounce_EaseIn);
  tolua_constant(tolua_S,"Bounce_EaseOut",Bounce_EaseOut);
  tolua_constant(tolua_S,"Bounce_EaseInOut",Bounce_EaseInOut);
  tolua_constant(tolua_S,"TWEEN_EASING_MAX",TWEEN_EASING_MAX);
  tolua_cclass(tolua_S,"ProcessBase","ProcessBase","CCObject",NULL);
  tolua_beginmodule(tolua_S,"ProcessBase");
   tolua_function(tolua_S,"play",tolua_CSArmature_luabinding_ProcessBase_play00);
   tolua_function(tolua_S,"pause",tolua_CSArmature_luabinding_ProcessBase_pause00);
   tolua_function(tolua_S,"resume",tolua_CSArmature_luabinding_ProcessBase_resume00);
   tolua_function(tolua_S,"stop",tolua_CSArmature_luabinding_ProcessBase_stop00);
   tolua_function(tolua_S,"gotoFrame",tolua_CSArmature_luabinding_ProcessBase_gotoFrame00);
   tolua_function(tolua_S,"getCurrentFrameIndex",tolua_CSArmature_luabinding_ProcessBase_getCurrentFrameIndex00);
   tolua_function(tolua_S,"getIsPause",tolua_CSArmature_luabinding_ProcessBase_getIsPause00);
   tolua_function(tolua_S,"setIsPause",tolua_CSArmature_luabinding_ProcessBase_setIsPause00);
   tolua_function(tolua_S,"getIsComplete",tolua_CSArmature_luabinding_ProcessBase_getIsComplete00);
   tolua_function(tolua_S,"setIsComplete",tolua_CSArmature_luabinding_ProcessBase_setIsComplete00);
   tolua_function(tolua_S,"getIsPlaying",tolua_CSArmature_luabinding_ProcessBase_getIsPlaying00);
   tolua_function(tolua_S,"setIsPlaying",tolua_CSArmature_luabinding_ProcessBase_setIsPlaying00);
   tolua_function(tolua_S,"getCurrentPercent",tolua_CSArmature_luabinding_ProcessBase_getCurrentPercent00);
   tolua_function(tolua_S,"setCurrentPercent",tolua_CSArmature_luabinding_ProcessBase_setCurrentPercent00);
   tolua_function(tolua_S,"getRawDuration",tolua_CSArmature_luabinding_ProcessBase_getRawDuration00);
   tolua_function(tolua_S,"setRawDuration",tolua_CSArmature_luabinding_ProcessBase_setRawDuration00);
   tolua_function(tolua_S,"getLoopType",tolua_CSArmature_luabinding_ProcessBase_getLoopType00);
   tolua_function(tolua_S,"setLoopType",tolua_CSArmature_luabinding_ProcessBase_setLoopType00);
   tolua_function(tolua_S,"getTweenEasing",tolua_CSArmature_luabinding_ProcessBase_getTweenEasing00);
   tolua_function(tolua_S,"setTweenEasing",tolua_CSArmature_luabinding_ProcessBase_setTweenEasing00);
   tolua_function(tolua_S,"getAnimationInternal",tolua_CSArmature_luabinding_ProcessBase_getAnimationInternal00);
   tolua_function(tolua_S,"setAnimationInternal",tolua_CSArmature_luabinding_ProcessBase_setAnimationInternal00);
   tolua_function(tolua_S,"getAnimationScale",tolua_CSArmature_luabinding_ProcessBase_getAnimationScale00);
   tolua_function(tolua_S,"setAnimationScale",tolua_CSArmature_luabinding_ProcessBase_setAnimationScale00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Animation","Animation","ProcessBase",NULL);
  tolua_beginmodule(tolua_S,"Animation");
   tolua_function(tolua_S,"create",tolua_CSArmature_luabinding_Animation_create00);
   tolua_function(tolua_S,"setAnimationScale",tolua_CSArmature_luabinding_Animation_setAnimationScale00);
   tolua_function(tolua_S,"play",tolua_CSArmature_luabinding_Animation_play00);
   tolua_function(tolua_S,"playByIndex",tolua_CSArmature_luabinding_Animation_playByIndex00);
   tolua_function(tolua_S,"pause",tolua_CSArmature_luabinding_Animation_pause00);
   tolua_function(tolua_S,"resume",tolua_CSArmature_luabinding_Animation_resume00);
   tolua_function(tolua_S,"stop",tolua_CSArmature_luabinding_Animation_stop00);
   tolua_function(tolua_S,"getMovementCount",tolua_CSArmature_luabinding_Animation_getMovementCount00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ArmatureDataManager","ArmatureDataManager","CCObject",NULL);
  tolua_beginmodule(tolua_S,"ArmatureDataManager");
   tolua_function(tolua_S,"sharedArmatureDataManager",tolua_CSArmature_luabinding_ArmatureDataManager_sharedArmatureDataManager00);
   tolua_function(tolua_S,"purgeArmatureSystem",tolua_CSArmature_luabinding_ArmatureDataManager_purgeArmatureSystem00);
   tolua_function(tolua_S,"addArmatureFileInfo",tolua_CSArmature_luabinding_ArmatureDataManager_addArmatureFileInfo00);
   tolua_function(tolua_S,"addArmatureFileInfo",tolua_CSArmature_luabinding_ArmatureDataManager_addArmatureFileInfo01);
   tolua_function(tolua_S,"addSpriteFrameFromFile",tolua_CSArmature_luabinding_ArmatureDataManager_addSpriteFrameFromFile00);
   tolua_function(tolua_S,"removeAll",tolua_CSArmature_luabinding_ArmatureDataManager_removeAll00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Bone","Bone","CCNodeRGBA",NULL);
  tolua_beginmodule(tolua_S,"Bone");
   tolua_function(tolua_S,"create",tolua_CSArmature_luabinding_Bone_create00);
   tolua_function(tolua_S,"create",tolua_CSArmature_luabinding_Bone_create01);
   tolua_function(tolua_S,"addChildBone",tolua_CSArmature_luabinding_Bone_addChildBone00);
   tolua_function(tolua_S,"setParentBone",tolua_CSArmature_luabinding_Bone_setParentBone00);
   tolua_function(tolua_S,"getParentBone",tolua_CSArmature_luabinding_Bone_getParentBone00);
   tolua_function(tolua_S,"removeFromParent",tolua_CSArmature_luabinding_Bone_removeFromParent00);
   tolua_function(tolua_S,"removeChildBone",tolua_CSArmature_luabinding_Bone_removeChildBone00);
   tolua_function(tolua_S,"getChildren",tolua_CSArmature_luabinding_Bone_getChildren00);
   tolua_function(tolua_S,"getArmature",tolua_CSArmature_luabinding_Bone_getArmature00);
   tolua_function(tolua_S,"getChildArmature",tolua_CSArmature_luabinding_Bone_getChildArmature00);
   tolua_function(tolua_S,"getIgnoreMovementBoneData",tolua_CSArmature_luabinding_Bone_getIgnoreMovementBoneData00);
   tolua_function(tolua_S,"setIgnoreMovementBoneData",tolua_CSArmature_luabinding_Bone_setIgnoreMovementBoneData00);
   tolua_function(tolua_S,"getName",tolua_CSArmature_luabinding_Bone_getName00);
   tolua_function(tolua_S,"setName",tolua_CSArmature_luabinding_Bone_setName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Armature","Armature","CCNodeRGBA",NULL);
  tolua_beginmodule(tolua_S,"Armature");
   tolua_function(tolua_S,"create",tolua_CSArmature_luabinding_Armature_create00);
   tolua_function(tolua_S,"create",tolua_CSArmature_luabinding_Armature_create01);
   tolua_function(tolua_S,"create",tolua_CSArmature_luabinding_Armature_create02);
   tolua_function(tolua_S,"setBlendFunc",tolua_CSArmature_luabinding_Armature_setBlendFunc00);
   tolua_function(tolua_S,"getBlendFunc",tolua_CSArmature_luabinding_Armature_getBlendFunc00);
   tolua_function(tolua_S,"addBone",tolua_CSArmature_luabinding_Armature_addBone00);
   tolua_function(tolua_S,"getBone",tolua_CSArmature_luabinding_Armature_getBone00);
   tolua_function(tolua_S,"changeBoneParent",tolua_CSArmature_luabinding_Armature_changeBoneParent00);
   tolua_function(tolua_S,"removeBone",tolua_CSArmature_luabinding_Armature_removeBone00);
   tolua_function(tolua_S,"getBoneDic",tolua_CSArmature_luabinding_Armature_getBoneDic00);
   tolua_function(tolua_S,"getParentBone",tolua_CSArmature_luabinding_Armature_getParentBone00);
   tolua_function(tolua_S,"getAnimation",tolua_CSArmature_luabinding_Armature_getAnimation00);
   tolua_function(tolua_S,"setAnimation",tolua_CSArmature_luabinding_Armature_setAnimation00);
   tolua_function(tolua_S,"getName",tolua_CSArmature_luabinding_Armature_getName00);
   tolua_function(tolua_S,"setName",tolua_CSArmature_luabinding_Armature_setName00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CSArmature_luabinding (lua_State* tolua_S) {
 return tolua_CSArmature_luabinding_open(tolua_S);
};
#endif

