/*
** Lua binding: ExtensionsDragonBones
** Generated automatically by tolua++-1.0.92 on Wed Oct 22 01:19:15 2014.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

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
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

/* Exported function */
TOLUA_API int  tolua_ExtensionsDragonBones_open (lua_State* tolua_S);

#include "DragonBones/DragonBonesHeaders.h"
using namespace dragonBones;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_DBTransform (lua_State* tolua_S)
{
 DBTransform* self = (DBTransform*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Slot (lua_State* tolua_S)
{
 Slot* self = (Slot*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_FrameEvent (lua_State* tolua_S)
{
 FrameEvent* self = (FrameEvent*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_dragonBones__CCDBNode (lua_State* tolua_S)
{
 dragonBones::CCDBNode* self = (dragonBones::CCDBNode*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCDBAtlasNode (lua_State* tolua_S)
{
 CCDBAtlasNode* self = (CCDBAtlasNode*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Object (lua_State* tolua_S)
{
 Object* self = (Object*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Armature (lua_State* tolua_S)
{
 Armature* self = (Armature*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Animation (lua_State* tolua_S)
{
 Animation* self = (Animation*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_DBObject (lua_State* tolua_S)
{
 DBObject* self = (DBObject*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Bone (lua_State* tolua_S)
{
 Bone* self = (Bone*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_AnimationData (lua_State* tolua_S)
{
 AnimationData* self = (AnimationData*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"DBTransform");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(DBTransform)), "DBTransform");
 tolua_usertype(tolua_S,"TransformTimeline");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(TransformTimeline)), "TransformTimeline");
 tolua_usertype(tolua_S,"Timeline");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(Timeline)), "Timeline");
 tolua_usertype(tolua_S,"IDisplayBridge");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(IDisplayBridge)), "IDisplayBridge");
 tolua_usertype(tolua_S,"CCDragonBones");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCDragonBones)), "CCDragonBones");
 tolua_usertype(tolua_S,"AnimationData");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(AnimationData)), "AnimationData");
 tolua_usertype(tolua_S,"CCArray");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCArray)), "CCArray");
 tolua_usertype(tolua_S,"dragonBones::CCDBNode");
 tolua_usertype(tolua_S,"CCDBAtlasNode");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCDBAtlasNode)), "CCDBAtlasNode");
 tolua_usertype(tolua_S,"AnimationEvent");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(AnimationEvent)), "AnimationEvent");
 tolua_usertype(tolua_S,"CCTextureProtocol");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCTextureProtocol)), "CCTextureProtocol");
 tolua_usertype(tolua_S,"Bone");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(Bone)), "Bone");
 tolua_usertype(tolua_S,"CCDBFactory");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCDBFactory)), "CCDBFactory");
 tolua_usertype(tolua_S,"CCNode");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCNode)), "CCNode");
 tolua_usertype(tolua_S,"ccColor3B");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(ccColor3B)), "ccColor3B");
 tolua_usertype(tolua_S,"IAnimatable");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(IAnimatable)), "IAnimatable");
 tolua_usertype(tolua_S,"dragonBones::Object");
 tolua_usertype(tolua_S,"GLubyte");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(GLubyte)), "GLubyte");
 tolua_usertype(tolua_S,"CCDBManager");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCDBManager)), "CCDBManager");
 tolua_usertype(tolua_S,"Animation");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(Animation)), "Animation");
 tolua_usertype(tolua_S,"FrameEvent");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(FrameEvent)), "FrameEvent");
 tolua_usertype(tolua_S,"AnimationState");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(AnimationState)), "AnimationState");
 tolua_usertype(tolua_S,"Event");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(Event)), "Event");
 tolua_usertype(tolua_S,"std::pair<int,Bone*>");
 tolua_usertype(tolua_S,"EventDispatcher");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(EventDispatcher)), "EventDispatcher");
 tolua_usertype(tolua_S,"TimelineState");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(TimelineState)), "TimelineState");
 tolua_usertype(tolua_S,"Object");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(Object)), "Object");
 tolua_usertype(tolua_S,"Armature");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(Armature)), "Armature");
 
 tolua_usertype(tolua_S,"Frame");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(Frame)), "Frame");
 tolua_usertype(tolua_S,"DBObject");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(DBObject)), "DBObject");
 tolua_usertype(tolua_S,"Slot");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(Slot)), "Slot");
}

/* method: new of class  Object */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Object_new00
static int tolua_ExtensionsDragonBones_Object_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Object* tolua_ret = (Object*)  Mtolua_new((Object)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Object");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Object */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Object_new00_local
static int tolua_ExtensionsDragonBones_Object_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Object* tolua_ret = (Object*)  Mtolua_new((Object)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Object");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Object */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Object_delete00
static int tolua_ExtensionsDragonBones_Object_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Object* self = (Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getType of class  Event */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Event_getType00
static int tolua_ExtensionsDragonBones_Event_getType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Event",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Event* self = (Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getType'", NULL);
#endif
  {
    std::string tolua_ret = (  std::string)  self->getType();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name of class  Armature */
#ifndef TOLUA_DISABLE_tolua_get_Armature_name
static int tolua_get_Armature_name(lua_State* tolua_S)
{
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  Armature */
#ifndef TOLUA_DISABLE_tolua_set_Armature_name
static int tolua_set_Armature_name(lua_State* tolua_S)
{
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name = ((  std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimation of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_getAnimation00
static int tolua_ExtensionsDragonBones_Armature_getAnimation00(lua_State* tolua_S)
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
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Animation");
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

/* method: new of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_new00
static int tolua_ExtensionsDragonBones_Armature_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Object* display = ((Object*)  tolua_tousertype(tolua_S,2,0));
  {
   Armature* tolua_ret = (Armature*)  Mtolua_new((Armature)(display));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Armature");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_new00_local
static int tolua_ExtensionsDragonBones_Armature_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Object* display = ((Object*)  tolua_tousertype(tolua_S,2,0));
  {
   Armature* tolua_ret = (Armature*)  Mtolua_new((Armature)(display));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Armature");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dispose of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_dispose00
static int tolua_ExtensionsDragonBones_Armature_dispose00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dispose'", NULL);
#endif
  {
   self->dispose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dispose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: invalidUpdate of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_invalidUpdate00
static int tolua_ExtensionsDragonBones_Armature_invalidUpdate00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'invalidUpdate'", NULL);
#endif
  {
   self->invalidUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'invalidUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: advanceTime of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_advanceTime00
static int tolua_ExtensionsDragonBones_Armature_advanceTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
   float passedTime = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'advanceTime'", NULL);
#endif
  {
   self->advanceTime(passedTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'advanceTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSlot of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_getSlot00
static int tolua_ExtensionsDragonBones_Armature_getSlot00(lua_State* tolua_S)
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
  const char* slotName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSlot'", NULL);
#endif
  {
   Slot* tolua_ret = (Slot*)  self->getSlot(slotName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Slot");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSlotByDisplay of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_getSlotByDisplay00
static int tolua_ExtensionsDragonBones_Armature_getSlotByDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  Object* display = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSlotByDisplay'", NULL);
#endif
  {
   Slot* tolua_ret = (Slot*)  self->getSlotByDisplay(display);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Slot");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSlotByDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSlot of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_removeSlot00
static int tolua_ExtensionsDragonBones_Armature_removeSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Slot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  Slot* slot = ((Slot*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSlot'", NULL);
#endif
  {
   self->removeSlot(slot);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSlotByName of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_removeSlotByName00
static int tolua_ExtensionsDragonBones_Armature_removeSlotByName00(lua_State* tolua_S)
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
  const char* slotName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSlotByName'", NULL);
#endif
  {
   self->removeSlotByName(slotName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSlotByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBone of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_getBone00
static int tolua_ExtensionsDragonBones_Armature_getBone00(lua_State* tolua_S)
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
  const char* boneName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBone'", NULL);
#endif
  {
   Bone* tolua_ret = (Bone*)  self->getBone(boneName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Bone");
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

/* method: getBoneByDisplay of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_getBoneByDisplay00
static int tolua_ExtensionsDragonBones_Armature_getBoneByDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  Object* display = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBoneByDisplay'", NULL);
#endif
  {
   Bone* tolua_ret = (Bone*)  self->getBoneByDisplay(display);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Bone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBoneByDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeBone of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_removeBone00
static int tolua_ExtensionsDragonBones_Armature_removeBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  Bone* bone = ((Bone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeBone'", NULL);
#endif
  {
   self->removeBone(bone);
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

/* method: removeBoneByName of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_removeBoneByName00
static int tolua_ExtensionsDragonBones_Armature_removeBoneByName00(lua_State* tolua_S)
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
  const char* boneName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeBoneByName'", NULL);
#endif
  {
   self->removeBoneByName(boneName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeBoneByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_addChild00
static int tolua_ExtensionsDragonBones_Armature_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DBObject",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  DBObject* object = ((DBObject*)  tolua_tousertype(tolua_S,2,0));
  const char* parentName = ((const char*)  tolua_tostring(tolua_S,3,""));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(object,parentName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addBone of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_addBone00
static int tolua_ExtensionsDragonBones_Armature_addBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Bone",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  Bone* bone = ((Bone*)  tolua_tousertype(tolua_S,2,0));
  const char* parentName = ((const char*)  tolua_tostring(tolua_S,3,""));
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

/* method: updateSlotsZOrder of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_updateSlotsZOrder00
static int tolua_ExtensionsDragonBones_Armature_updateSlotsZOrder00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateSlotsZOrder'", NULL);
#endif
  {
   self->updateSlotsZOrder();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateSlotsZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDBObject of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_addDBObject00
static int tolua_ExtensionsDragonBones_Armature_addDBObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  DBObject* object = ((DBObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDBObject'", NULL);
#endif
  {
   self->addDBObject(object);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addDBObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeDBObject of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_removeDBObject00
static int tolua_ExtensionsDragonBones_Armature_removeDBObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  DBObject* object = ((DBObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeDBObject'", NULL);
#endif
  {
   self->removeDBObject(object);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeDBObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sortBone of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_sortBone00
static int tolua_ExtensionsDragonBones_Armature_sortBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Armature",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const std::pair<int,Bone*>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const std::pair<int,Bone*>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::pair<int,Bone*>* a = ((const std::pair<int,Bone*>*)  tolua_tousertype(tolua_S,2,0));
  const std::pair<int,Bone*>* b = ((const std::pair<int,Bone*>*)  tolua_tousertype(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  Armature::sortBone(*a,*b);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sortBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sortBoneList of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_sortBoneList00
static int tolua_ExtensionsDragonBones_Armature_sortBoneList00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sortBoneList'", NULL);
#endif
  {
   self->sortBoneList();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sortBoneList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: arriveAtFrame of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_arriveAtFrame00
static int tolua_ExtensionsDragonBones_Armature_arriveAtFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Frame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"TimelineState",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"AnimationState",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
  Frame* frame = ((Frame*)  tolua_tousertype(tolua_S,2,0));
  TimelineState* timelineState = ((TimelineState*)  tolua_tousertype(tolua_S,3,0));
  AnimationState* animationState = ((AnimationState*)  tolua_tousertype(tolua_S,4,0));
  bool isCross = ((bool)  tolua_toboolean(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'arriveAtFrame'", NULL);
#endif
  {
   self->arriveAtFrame(frame,timelineState,animationState,isCross);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'arriveAtFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sortSlot of class  Armature */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Armature_sortSlot00
static int tolua_ExtensionsDragonBones_Armature_sortSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Slot",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Slot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* slot1 = ((Slot*)  tolua_tousertype(tolua_S,2,0));
  Slot* slot2 = ((Slot*)  tolua_tousertype(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  Armature::sortSlot(slot1,slot2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sortSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __EventDispatcher__ of class  Armature */
#ifndef TOLUA_DISABLE_tolua_get_Armature___EventDispatcher__
static int tolua_get_Armature___EventDispatcher__(lua_State* tolua_S)
{
  Armature* self = (Armature*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__EventDispatcher__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<EventDispatcher*>(self), "EventDispatcher");
#else
   tolua_pushusertype(tolua_S,(void*)((EventDispatcher*)self), "EventDispatcher");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_new00
static int tolua_ExtensionsDragonBones_Bone_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Bone* tolua_ret = (Bone*)  Mtolua_new((Bone)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Bone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_new00_local
static int tolua_ExtensionsDragonBones_Bone_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Bone* tolua_ret = (Bone*)  Mtolua_new((Bone)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Bone");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_delete00
static int tolua_ExtensionsDragonBones_Bone_delete00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildArmature of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_getChildArmature00
static int tolua_ExtensionsDragonBones_Bone_getChildArmature00(lua_State* tolua_S)
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
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Armature");
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

/* method: getDisplay of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_getDisplay00
static int tolua_ExtensionsDragonBones_Bone_getDisplay00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplay'", NULL);
#endif
  {
   Object* tolua_ret = (Object*)  self->getDisplay();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Object");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDisplay of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_setDisplay00
static int tolua_ExtensionsDragonBones_Bone_setDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  Object* value = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDisplay'", NULL);
#endif
  {
   self->setDisplay(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: displayController of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_displayController
static int tolua_get_Bone_displayController(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'displayController'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->displayController);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: displayController of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_displayController
static int tolua_set_Bone_displayController(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'displayController'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->displayController = ((  std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_setVisible00
static int tolua_ExtensionsDragonBones_Bone_setVisible00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setArmature of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_setArmature00
static int tolua_ExtensionsDragonBones_Bone_setArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  Armature* value = ((Armature*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setArmature'", NULL);
#endif
  {
   self->setArmature(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dispose of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_dispose00
static int tolua_ExtensionsDragonBones_Bone_dispose00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dispose'", NULL);
#endif
  {
   self->dispose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dispose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: contains of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_contains00
static int tolua_ExtensionsDragonBones_Bone_contains00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  DBObject* child = ((DBObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'contains'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->contains(child);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'contains'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_addChild00
static int tolua_ExtensionsDragonBones_Bone_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  DBObject* child = ((DBObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_removeChild00
static int tolua_ExtensionsDragonBones_Bone_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
  DBObject* child = ((DBObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   self->removeChild(child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateColor of class  Bone */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Bone_updateColor00
static int tolua_ExtensionsDragonBones_Bone_updateColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,10,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
   float aOffset = ((  float)  tolua_tonumber(tolua_S,2,0));
   float rOffset = ((  float)  tolua_tonumber(tolua_S,3,0));
   float gOffset = ((  float)  tolua_tonumber(tolua_S,4,0));
   float bOffset = ((  float)  tolua_tonumber(tolua_S,5,0));
   float aMultiplier = ((  float)  tolua_tonumber(tolua_S,6,0));
   float rMultiplier = ((  float)  tolua_tonumber(tolua_S,7,0));
   float gMultiplier = ((  float)  tolua_tonumber(tolua_S,8,0));
   float bMultiplier = ((  float)  tolua_tonumber(tolua_S,9,0));
  bool isColorChanged = ((bool)  tolua_toboolean(tolua_S,10,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateColor'", NULL);
#endif
  {
   self->updateColor(aOffset,rOffset,gOffset,bOffset,aMultiplier,rMultiplier,gMultiplier,bMultiplier,isColorChanged);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_new00
static int tolua_ExtensionsDragonBones_Slot_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"IDisplayBridge",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDisplayBridge* displayBrideg = ((IDisplayBridge*)  tolua_tousertype(tolua_S,2,0));
  {
   Slot* tolua_ret = (Slot*)  Mtolua_new((Slot)(displayBrideg));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Slot");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_new00_local
static int tolua_ExtensionsDragonBones_Slot_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"IDisplayBridge",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDisplayBridge* displayBrideg = ((IDisplayBridge*)  tolua_tousertype(tolua_S,2,0));
  {
   Slot* tolua_ret = (Slot*)  Mtolua_new((Slot)(displayBrideg));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Slot");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_delete00
static int tolua_ExtensionsDragonBones_Slot_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getZOrder of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_getZOrder00
static int tolua_ExtensionsDragonBones_Slot_getZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getZOrder'", NULL);
#endif
  {
    float tolua_ret = (  float)  self->getZOrder();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setZOrder of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_setZOrder00
static int tolua_ExtensionsDragonBones_Slot_setZOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
   float value = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setZOrder'", NULL);
#endif
  {
   self->setZOrder(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setZOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBlendMode of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_getBlendMode00
static int tolua_ExtensionsDragonBones_Slot_getBlendMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBlendMode'", NULL);
#endif
  {
    std::string tolua_ret = (  std::string)  self->getBlendMode();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBlendMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendMode of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_setBlendMode00
static int tolua_ExtensionsDragonBones_Slot_setBlendMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
  const std::string value = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendMode'", NULL);
#endif
  {
   self->setBlendMode(value);
   tolua_pushcppstring(tolua_S,(const char*)value);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplay of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_getDisplay00
static int tolua_ExtensionsDragonBones_Slot_getDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplay'", NULL);
#endif
  {
   Object* tolua_ret = (Object*)  self->getDisplay();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Object");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDisplayValue of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_setDisplayValue00
static int tolua_ExtensionsDragonBones_Slot_setDisplayValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
  Object* value = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDisplayValue'", NULL);
#endif
  {
   self->setDisplayValue(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDisplayValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildArmature of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_getChildArmature00
static int tolua_ExtensionsDragonBones_Slot_getChildArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildArmature'", NULL);
#endif
  {
   Armature* tolua_ret = (Armature*)  self->getChildArmature();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Armature");
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

/* method: setChildArmature of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_setChildArmature00
static int tolua_ExtensionsDragonBones_Slot_setChildArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
  Armature* value = ((Armature*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setChildArmature'", NULL);
#endif
  {
   self->setChildArmature(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setChildArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDisplay of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_setDisplay00
static int tolua_ExtensionsDragonBones_Slot_setDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
  Object* display = ((Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDisplay'", NULL);
#endif
  {
   self->setDisplay(display);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeDisplay of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_changeDisplay00
static int tolua_ExtensionsDragonBones_Slot_changeDisplay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
  int displayIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeDisplay'", NULL);
#endif
  {
   self->changeDisplay(displayIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeDisplay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_setVisible00
static int tolua_ExtensionsDragonBones_Slot_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setArmature of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_setArmature00
static int tolua_ExtensionsDragonBones_Slot_setArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
  Armature* value = ((Armature*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setArmature'", NULL);
#endif
  {
   self->setArmature(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dispose of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_dispose00
static int tolua_ExtensionsDragonBones_Slot_dispose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dispose'", NULL);
#endif
  {
   self->dispose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dispose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_update00
static int tolua_ExtensionsDragonBones_Slot_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateVisible of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_updateVisible00
static int tolua_ExtensionsDragonBones_Slot_updateVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateVisible'", NULL);
#endif
  {
   self->updateVisible(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateChildArmatureAnimation of class  Slot */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Slot_updateChildArmatureAnimation00
static int tolua_ExtensionsDragonBones_Slot_updateChildArmatureAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slot",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slot* self = (Slot*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateChildArmatureAnimation'", NULL);
#endif
  {
   self->updateChildArmatureAnimation();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateChildArmatureAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBObject_new00
static int tolua_ExtensionsDragonBones_DBObject_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DBObject* tolua_ret = (DBObject*)  Mtolua_new((DBObject)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DBObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBObject_new00_local
static int tolua_ExtensionsDragonBones_DBObject_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DBObject* tolua_ret = (DBObject*)  Mtolua_new((DBObject)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DBObject");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBObject_delete00
static int tolua_ExtensionsDragonBones_DBObject_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: global of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_get_DBObject_global
static int tolua_get_DBObject_global(lua_State* tolua_S)
{
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'global'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->global,"DBTransform");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: global of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_set_DBObject_global
static int tolua_set_DBObject_global(lua_State* tolua_S)
{
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'global'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DBTransform",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->global = *((DBTransform*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: origin of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_get_DBObject_origin
static int tolua_get_DBObject_origin(lua_State* tolua_S)
{
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'origin'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->origin,"DBTransform");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: origin of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_set_DBObject_origin
static int tolua_set_DBObject_origin(lua_State* tolua_S)
{
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'origin'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DBTransform",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->origin = *((DBTransform*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: offset of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_get_DBObject_offset
static int tolua_get_DBObject_offset(lua_State* tolua_S)
{
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offset'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->offset,"DBTransform");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: offset of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_set_DBObject_offset
static int tolua_set_DBObject_offset(lua_State* tolua_S)
{
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offset'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DBTransform",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->offset = *((DBTransform*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tween of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_get_DBObject_tween
static int tolua_get_DBObject_tween(lua_State* tolua_S)
{
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tween'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->tween,"DBTransform");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tween of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_set_DBObject_tween
static int tolua_set_DBObject_tween(lua_State* tolua_S)
{
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tween'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"DBTransform",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tween = *((DBTransform*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBObject_setVisible00
static int tolua_ExtensionsDragonBones_DBObject_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
  bool visible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVisible of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBObject_getVisible00
static int tolua_ExtensionsDragonBones_DBObject_getVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArmature of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBObject_getArmature00
static int tolua_ExtensionsDragonBones_DBObject_getArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArmature'", NULL);
#endif
  {
   Armature* tolua_ret = (Armature*)  self->getArmature();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Armature");
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

/* method: setArmature of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBObject_setArmature00
static int tolua_ExtensionsDragonBones_DBObject_setArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
  Armature* value = ((Armature*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setArmature'", NULL);
#endif
  {
   self->setArmature(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setArmature'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dispose of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBObject_dispose00
static int tolua_ExtensionsDragonBones_DBObject_dispose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dispose'", NULL);
#endif
  {
   self->dispose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dispose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  DBObject */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBObject_update00
static int tolua_ExtensionsDragonBones_DBObject_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBObject* self = (DBObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: NONE of class  Animation */
#ifndef TOLUA_DISABLE_tolua_get_Animation_NONE
static int tolua_get_Animation_NONE(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)Animation::NONE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SAME_LAYER of class  Animation */
#ifndef TOLUA_DISABLE_tolua_get_Animation_SAME_LAYER
static int tolua_get_Animation_SAME_LAYER(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)Animation::SAME_LAYER);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SAME_GROUP of class  Animation */
#ifndef TOLUA_DISABLE_tolua_get_Animation_SAME_GROUP
static int tolua_get_Animation_SAME_GROUP(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)Animation::SAME_GROUP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SAME_LAYER_AND_GROUP of class  Animation */
#ifndef TOLUA_DISABLE_tolua_get_Animation_SAME_LAYER_AND_GROUP
static int tolua_get_Animation_SAME_LAYER_AND_GROUP(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)Animation::SAME_LAYER_AND_GROUP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ALL of class  Animation */
#ifndef TOLUA_DISABLE_tolua_get_Animation_ALL
static int tolua_get_Animation_ALL(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)Animation::ALL);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLastAnimationName of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_getLastAnimationName00
static int tolua_ExtensionsDragonBones_Animation_getLastAnimationName00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLastAnimationName'", NULL);
#endif
  {
    std::string tolua_ret = (  std::string)  self->getLastAnimationName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLastAnimationName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLastAnimationName of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_getMovementID00
static int tolua_ExtensionsDragonBones_Animation_getMovementID00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLastAnimationName'", NULL);
#endif
  {
    std::string tolua_ret = (  std::string)  self->getLastAnimationName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMovementID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnimationData of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_getAnimationData00
static int tolua_ExtensionsDragonBones_Animation_getAnimationData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
   std::string name = ((  std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimationData'", NULL);
#endif
  {
   AnimationData* tolua_ret = (AnimationData*)  self->getAnimationData(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationData");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnimationData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLastAnimationState of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_getLastAnimationState00
static int tolua_ExtensionsDragonBones_Animation_getLastAnimationState00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLastAnimationState'", NULL);
#endif
  {
   AnimationState* tolua_ret = (AnimationState*)  self->getLastAnimationState();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLastAnimationState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsPlaying of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_getIsPlaying00
static int tolua_ExtensionsDragonBones_Animation_getIsPlaying00(lua_State* tolua_S)
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

/* method: getIsComplete of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_getIsComplete00
static int tolua_ExtensionsDragonBones_Animation_getIsComplete00(lua_State* tolua_S)
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

/* method: getTimeScale of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_getTimeScale00
static int tolua_ExtensionsDragonBones_Animation_getTimeScale00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getTimeScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTimeScale of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_setTimeScale00
static int tolua_ExtensionsDragonBones_Animation_setTimeScale00(lua_State* tolua_S)
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
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTimeScale'", NULL);
#endif
  {
   self->setTimeScale(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTimeScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_new00
static int tolua_ExtensionsDragonBones_Animation_new00(lua_State* tolua_S)
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
   Animation* tolua_ret = (Animation*)  Mtolua_new((Animation)(armature));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Animation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_new00_local
static int tolua_ExtensionsDragonBones_Animation_new00_local(lua_State* tolua_S)
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
   Animation* tolua_ret = (Animation*)  Mtolua_new((Animation)(armature));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Animation");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dispose of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_dispose00
static int tolua_ExtensionsDragonBones_Animation_dispose00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dispose'", NULL);
#endif
  {
   self->dispose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dispose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gotoAndPlay of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_gotoAndPlay00
static int tolua_ExtensionsDragonBones_Animation_gotoAndPlay00(lua_State* tolua_S)
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
     !tolua_isstring(tolua_S,7,1,&tolua_err) ||
     !tolua_isstring(tolua_S,8,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,9,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,10,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,11,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  const char* animationName = ((const char*)  tolua_tostring(tolua_S,2,0));
  float fadeInTime = ((float)  tolua_tonumber(tolua_S,3,-1));
  float duration = ((float)  tolua_tonumber(tolua_S,4,-1));
  float loop = ((float)  tolua_tonumber(tolua_S,5,NaN));
  int layer = ((int)  tolua_tonumber(tolua_S,6,0));
  const char* group = ((const char*)  tolua_tostring(tolua_S,7,""));
  const char* fadeOutMode = ((const char*)  tolua_tostring(tolua_S,8,"sameLayerAndGroup"));
  bool displayControl = ((bool)  tolua_toboolean(tolua_S,9,true));
  bool pauseFadeOut = ((bool)  tolua_toboolean(tolua_S,10,true));
  bool pauseFadeIn = ((bool)  tolua_toboolean(tolua_S,11,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoAndPlay'", NULL);
#endif
  {
   AnimationState* tolua_ret = (AnimationState*)  self->gotoAndPlay(animationName,fadeInTime,duration,loop,layer,group,fadeOutMode,displayControl,pauseFadeOut,pauseFadeIn);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gotoAndPlay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_play00
static int tolua_ExtensionsDragonBones_Animation_play00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play();
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

/* method: stop of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_stop00
static int tolua_ExtensionsDragonBones_Animation_stop00(lua_State* tolua_S)
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

/* method: getState of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_getState00
static int tolua_ExtensionsDragonBones_Animation_getState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int layer = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getState'", NULL);
#endif
  {
   AnimationState* tolua_ret = (AnimationState*)  self->getState(name,layer);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasAnimation of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_hasAnimation00
static int tolua_ExtensionsDragonBones_Animation_hasAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  const char* animationName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasAnimation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasAnimation(animationName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: advanceTime of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_advanceTime00
static int tolua_ExtensionsDragonBones_Animation_advanceTime00(lua_State* tolua_S)
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
  float passedTime = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'advanceTime'", NULL);
#endif
  {
   self->advanceTime(passedTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'advanceTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActive of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_setActive00
static int tolua_ExtensionsDragonBones_Animation_setActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimationState",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  AnimationState* animationState = ((AnimationState*)  tolua_tousertype(tolua_S,2,0));
  bool active = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActive'", NULL);
#endif
  {
   self->setActive(animationState,active);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addLayer of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_addLayer00
static int tolua_ExtensionsDragonBones_Animation_addLayer00(lua_State* tolua_S)
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
  int layer = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addLayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->addLayer(layer);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addState of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_addState00
static int tolua_ExtensionsDragonBones_Animation_addState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  AnimationState* animationState = ((AnimationState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addState'", NULL);
#endif
  {
   self->addState(animationState);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeState of class  Animation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_Animation_removeState00
static int tolua_ExtensionsDragonBones_Animation_removeState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Animation* self = (Animation*)  tolua_tousertype(tolua_S,1,0);
  AnimationState* animationState = ((AnimationState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeState'", NULL);
#endif
  {
   self->removeState(animationState);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: borrowObject of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_borrowObject00
static int tolua_ExtensionsDragonBones_AnimationState_borrowObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AnimationState* tolua_ret = (AnimationState*)  AnimationState::borrowObject();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'borrowObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: returnObject of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_returnObject00
static int tolua_ExtensionsDragonBones_AnimationState_returnObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* animationState = ((AnimationState*)  tolua_tousertype(tolua_S,2,0));
  {
   AnimationState::returnObject(animationState);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'returnObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_clear00
static int tolua_ExtensionsDragonBones_AnimationState_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AnimationState::clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClip of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getClip00
static int tolua_ExtensionsDragonBones_AnimationState_getClip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClip'", NULL);
#endif
  {
   AnimationData* tolua_ret = (AnimationData*)  self->getClip();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLoopCount of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getLoopCount00
static int tolua_ExtensionsDragonBones_AnimationState_getLoopCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLoopCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getLoopCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLoopCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLoop of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getLoop00
static int tolua_ExtensionsDragonBones_AnimationState_getLoop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLoop'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getLoop();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLoop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLayer of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getLayer00
static int tolua_ExtensionsDragonBones_AnimationState_getLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayer'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->getLayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsPlaying of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getIsPlaying00
static int tolua_ExtensionsDragonBones_AnimationState_getIsPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getIsComplete of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getIsComplete00
static int tolua_ExtensionsDragonBones_AnimationState_getIsComplete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getFadeInTime of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getFadeInTime00
static int tolua_ExtensionsDragonBones_AnimationState_getFadeInTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFadeInTime'", NULL);
#endif
  {
    float tolua_ret = (  float)  self->getFadeInTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFadeInTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTotalTime of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getTotalTime00
static int tolua_ExtensionsDragonBones_AnimationState_getTotalTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTotalTime'", NULL);
#endif
  {
    float tolua_ret = (  float)  self->getTotalTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTotalTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentTime of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getCurrentTime00
static int tolua_ExtensionsDragonBones_AnimationState_getCurrentTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentTime'", NULL);
#endif
  {
    float tolua_ret = (  float)  self->getCurrentTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCurrentTime of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_setCurrentTime00
static int tolua_ExtensionsDragonBones_AnimationState_setCurrentTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
   float value = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCurrentTime'", NULL);
#endif
  {
   self->setCurrentTime(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCurrentTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimeScale of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getTimeScale00
static int tolua_ExtensionsDragonBones_AnimationState_getTimeScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeScale'", NULL);
#endif
  {
    float tolua_ret = (  float)  self->getTimeScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTimeScale of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_setTimeScale00
static int tolua_ExtensionsDragonBones_AnimationState_setTimeScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
   float value = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTimeScale'", NULL);
#endif
  {
   self->setTimeScale(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTimeScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fadeIn of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_fadeIn00
static int tolua_ExtensionsDragonBones_AnimationState_fadeIn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Armature",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"AnimationData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,8,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  Armature* armature = ((Armature*)  tolua_tousertype(tolua_S,2,0));
  AnimationData* clip = ((AnimationData*)  tolua_tousertype(tolua_S,3,0));
   float fadeInTime = ((  float)  tolua_tonumber(tolua_S,4,0));
   float timeScale = ((  float)  tolua_tonumber(tolua_S,5,0));
  int loop = ((int)  tolua_tonumber(tolua_S,6,0));
  unsigned int layer = (( unsigned int)  tolua_tonumber(tolua_S,7,0));
  bool displayControl = ((bool)  tolua_toboolean(tolua_S,8,0));
  bool pauseBeforeFadeInComplete = ((bool)  tolua_toboolean(tolua_S,9,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fadeIn'", NULL);
#endif
  {
   self->fadeIn(armature,clip,fadeInTime,timeScale,loop,layer,displayControl,pauseBeforeFadeInComplete);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fadeIn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fadeOut of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_fadeOut00
static int tolua_ExtensionsDragonBones_AnimationState_fadeOut00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
   float fadeOutTime = ((  float)  tolua_tonumber(tolua_S,2,0));
  bool pause = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fadeOut'", NULL);
#endif
  {
   self->fadeOut(fadeOutTime,pause);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fadeOut'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_play00
static int tolua_ExtensionsDragonBones_AnimationState_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play();
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

/* method: stop of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_stop00
static int tolua_ExtensionsDragonBones_AnimationState_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
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

/* method: getMixingTransform of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_getMixingTransform00
static int tolua_ExtensionsDragonBones_AnimationState_getMixingTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  const std::string timelineName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMixingTransform'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMixingTransform(timelineName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)timelineName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMixingTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addMixingTransform of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_addMixingTransform00
static int tolua_ExtensionsDragonBones_AnimationState_addMixingTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  const std::string timelineName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,2));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addMixingTransform'", NULL);
#endif
  {
   self->addMixingTransform(timelineName,type,recursive);
   tolua_pushcppstring(tolua_S,(const char*)timelineName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addMixingTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeMixingTransform of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_removeMixingTransform00
static int tolua_ExtensionsDragonBones_AnimationState_removeMixingTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeMixingTransform'", NULL);
#endif
  {
   self->removeMixingTransform();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeMixingTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeMixingTransform of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_removeMixingTransform01
static int tolua_ExtensionsDragonBones_AnimationState_removeMixingTransform01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  const std::string timelineName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeMixingTransform'", NULL);
#endif
  {
   self->removeMixingTransform(timelineName,recursive);
   tolua_pushcppstring(tolua_S,(const char*)timelineName);
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsDragonBones_AnimationState_removeMixingTransform00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: advanceTime of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_advanceTime00
static int tolua_ExtensionsDragonBones_AnimationState_advanceTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
   float passedTime = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'advanceTime'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->advanceTime(passedTime);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'advanceTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateTimelineStates of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_updateTimelineStates00
static int tolua_ExtensionsDragonBones_AnimationState_updateTimelineStates00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateTimelineStates'", NULL);
#endif
  {
   self->updateTimelineStates();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateTimelineStates'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTimelineState of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_addTimelineState00
static int tolua_ExtensionsDragonBones_AnimationState_addTimelineState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  const std::string timelineName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTimelineState'", NULL);
#endif
  {
   self->addTimelineState(timelineName);
   tolua_pushcppstring(tolua_S,(const char*)timelineName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTimelineState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTimelineState of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_removeTimelineState00
static int tolua_ExtensionsDragonBones_AnimationState_removeTimelineState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  const std::string timelineName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTimelineState'", NULL);
#endif
  {
   self->removeTimelineState(timelineName);
   tolua_pushcppstring(tolua_S,(const char*)timelineName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeTimelineState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearAll of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationState_clearAll00
static int tolua_ExtensionsDragonBones_AnimationState_clearAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearAll'", NULL);
#endif
  {
   self->clearAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  dragonBones::CCDBNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_dragonBones_CCDBNode_new00
static int tolua_ExtensionsDragonBones_dragonBones_CCDBNode_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"dragonBones::CCDBNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* n = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   dragonBones::CCDBNode* tolua_ret = (dragonBones::CCDBNode*)  Mtolua_new((dragonBones::CCDBNode)(n));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"dragonBones::CCDBNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  dragonBones::CCDBNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_dragonBones_CCDBNode_new00_local
static int tolua_ExtensionsDragonBones_dragonBones_CCDBNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"dragonBones::CCDBNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* n = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   dragonBones::CCDBNode* tolua_ret = (dragonBones::CCDBNode*)  Mtolua_new((dragonBones::CCDBNode)(n));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"dragonBones::CCDBNode");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  dragonBones::CCDBNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_dragonBones_CCDBNode_delete00
static int tolua_ExtensionsDragonBones_dragonBones_CCDBNode_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"dragonBones::CCDBNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  dragonBones::CCDBNode* self = (dragonBones::CCDBNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNode of class  dragonBones::CCDBNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_dragonBones_CCDBNode_getNode00
static int tolua_ExtensionsDragonBones_dragonBones_CCDBNode_getNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const dragonBones::CCDBNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const dragonBones::CCDBNode* self = (const dragonBones::CCDBNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNode'", NULL);
#endif
  {
   const CCNode* tolua_ret = (const CCNode*)  self->getNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNode of class  dragonBones::CCDBNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_dragonBones_CCDBNode_getNode01
static int tolua_ExtensionsDragonBones_dragonBones_CCDBNode_getNode01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"dragonBones::CCDBNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  dragonBones::CCDBNode* self = (dragonBones::CCDBNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getNode();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsDragonBones_dragonBones_CCDBNode_getNode00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_create00
static int tolua_ExtensionsDragonBones_CCDragonBones_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Armature",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Armature* arm = ((Armature*)  tolua_tousertype(tolua_S,2,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::create(arm);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
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

/* method: createByName of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByName00
static int tolua_ExtensionsDragonBones_CCDragonBones_createByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByName(armatureName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByName of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByName01
static int tolua_ExtensionsDragonBones_CCDragonBones_createByName01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByName(armatureName,animationName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
  }
 }
 return 3;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByName00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByName of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByName02
static int tolua_ExtensionsDragonBones_CCDragonBones_createByName02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByName(armatureName,animationName,skeletonName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
  }
 }
 return 4;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByName01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByName of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByName03
static int tolua_ExtensionsDragonBones_CCDragonBones_createByName03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByName(armatureName,animationName,skeletonName,textureAtlasName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
  }
 }
 return 5;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByName02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByName of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByName04
static int tolua_ExtensionsDragonBones_CCDragonBones_createByName04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  const std::string skinName = ((const std::string)  tolua_tocppstring(tolua_S,6,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByName(armatureName,animationName,skeletonName,textureAtlasName,skinName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
   tolua_pushcppstring(tolua_S,(const char*)skinName);
  }
 }
 return 6;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByName03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByDir of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByDir00
static int tolua_ExtensionsDragonBones_CCDragonBones_createByDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string path = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByDir(path,armatureName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)path);
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createByDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByDir of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByDir01
static int tolua_ExtensionsDragonBones_CCDragonBones_createByDir01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string path = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByDir(path,armatureName,animationName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)path);
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
  }
 }
 return 4;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByDir00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByDir of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByDir02
static int tolua_ExtensionsDragonBones_CCDragonBones_createByDir02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string path = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByDir(path,armatureName,animationName,skeletonName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)path);
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
  }
 }
 return 5;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByDir01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByDir of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByDir03
static int tolua_ExtensionsDragonBones_CCDragonBones_createByDir03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string path = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,6,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByDir(path,armatureName,animationName,skeletonName,textureAtlasName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)path);
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
  }
 }
 return 6;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByDir02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByDir of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByDir04
static int tolua_ExtensionsDragonBones_CCDragonBones_createByDir04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,6,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string path = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,6,0));
  const std::string skinName = ((const std::string)  tolua_tocppstring(tolua_S,7,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByDir(path,armatureName,animationName,skeletonName,textureAtlasName,skinName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)path);
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
   tolua_pushcppstring(tolua_S,(const char*)skinName);
  }
 }
 return 7;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByDir03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByFiles of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByFiles00
static int tolua_ExtensionsDragonBones_CCDragonBones_createByFiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string skeletonXMLFile = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string textureXMLFile = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByFiles(skeletonXMLFile,textureXMLFile,armatureName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)skeletonXMLFile);
   tolua_pushcppstring(tolua_S,(const char*)textureXMLFile);
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
  }
 }
 return 4;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createByFiles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByFiles of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByFiles01
static int tolua_ExtensionsDragonBones_CCDragonBones_createByFiles01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string skeletonXMLFile = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string textureXMLFile = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByFiles(skeletonXMLFile,textureXMLFile,armatureName,animationName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)skeletonXMLFile);
   tolua_pushcppstring(tolua_S,(const char*)textureXMLFile);
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
  }
 }
 return 5;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByFiles00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByFiles of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByFiles02
static int tolua_ExtensionsDragonBones_CCDragonBones_createByFiles02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string skeletonXMLFile = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string textureXMLFile = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,6,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByFiles(skeletonXMLFile,textureXMLFile,armatureName,animationName,skeletonName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)skeletonXMLFile);
   tolua_pushcppstring(tolua_S,(const char*)textureXMLFile);
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
  }
 }
 return 6;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByFiles01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByFiles of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByFiles03
static int tolua_ExtensionsDragonBones_CCDragonBones_createByFiles03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,6,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string skeletonXMLFile = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string textureXMLFile = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,6,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,7,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByFiles(skeletonXMLFile,textureXMLFile,armatureName,animationName,skeletonName,textureAtlasName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)skeletonXMLFile);
   tolua_pushcppstring(tolua_S,(const char*)textureXMLFile);
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
  }
 }
 return 7;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByFiles02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createByFiles of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_createByFiles04
static int tolua_ExtensionsDragonBones_CCDragonBones_createByFiles04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,6,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,7,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,8,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string skeletonXMLFile = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string textureXMLFile = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string armatureName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string animationName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,6,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,7,0));
  const std::string skinName = ((const std::string)  tolua_tocppstring(tolua_S,8,0));
  {
   CCDragonBones* tolua_ret = (CCDragonBones*)  CCDragonBones::createByFiles(skeletonXMLFile,textureXMLFile,armatureName,animationName,skeletonName,textureAtlasName,skinName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragonBones");
   tolua_pushcppstring(tolua_S,(const char*)skeletonXMLFile);
   tolua_pushcppstring(tolua_S,(const char*)textureXMLFile);
   tolua_pushcppstring(tolua_S,(const char*)armatureName);
   tolua_pushcppstring(tolua_S,(const char*)animationName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
   tolua_pushcppstring(tolua_S,(const char*)skinName);
  }
 }
 return 8;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDragonBones_createByFiles03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayNode of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_getDisplayNode00
static int tolua_ExtensionsDragonBones_CCDragonBones_getDisplayNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getDisplayNode();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getArmature of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_getArmature00
static int tolua_ExtensionsDragonBones_CCDragonBones_getArmature00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getArmature'", NULL);
#endif
  {
   Armature* tolua_ret = (Armature*)  self->getArmature();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Armature");
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

/* method: getAnimation of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_getAnimation00
static int tolua_ExtensionsDragonBones_CCDragonBones_getAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimation'", NULL);
#endif
  {
   Animation* tolua_ret = (Animation*)  self->getAnimation();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Animation");
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

/* method: getAnimationList of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_getAnimationList00
static int tolua_ExtensionsDragonBones_CCDragonBones_getAnimationList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnimationList'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getAnimationList();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnimationList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gotoAndPlay of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_gotoAndPlay00
static int tolua_ExtensionsDragonBones_CCDragonBones_gotoAndPlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isstring(tolua_S,7,1,&tolua_err) ||
     !tolua_isstring(tolua_S,8,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,9,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,10,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,11,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
  const char* animationName = ((const char*)  tolua_tostring(tolua_S,2,0));
  float fadeInTime = ((float)  tolua_tonumber(tolua_S,3,-1));
  float duration = ((float)  tolua_tonumber(tolua_S,4,-1));
  float loop = ((float)  tolua_tonumber(tolua_S,5,NaN));
  int layer = ((int)  tolua_tonumber(tolua_S,6,0));
  const char* group = ((const char*)  tolua_tostring(tolua_S,7,""));
  const char* fadeOutMode = ((const char*)  tolua_tostring(tolua_S,8,"sameLayerAndGroup"));
  bool displayControl = ((bool)  tolua_toboolean(tolua_S,9,true));
  bool pauseFadeOut = ((bool)  tolua_toboolean(tolua_S,10,true));
  bool pauseFadeIn = ((bool)  tolua_toboolean(tolua_S,11,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gotoAndPlay'", NULL);
#endif
  {
   self->gotoAndPlay(animationName,fadeInTime,duration,loop,layer,group,fadeOutMode,displayControl,pauseFadeOut,pauseFadeIn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gotoAndPlay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBoneTexture of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_setBoneTexture00
static int tolua_ExtensionsDragonBones_CCDragonBones_setBoneTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
  const char* boneName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* textureName = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* textureAtlasName = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBoneTexture'", NULL);
#endif
  {
   self->setBoneTexture(boneName,textureName,textureAtlasName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBoneTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptHandler of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_registerScriptHandler00
static int tolua_ExtensionsDragonBones_CCDragonBones_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION funId = (  toluafix_ref_function(tolua_S,2,0));
   std::string type = ((  std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptHandler'", NULL);
#endif
  {
   self->registerScriptHandler(funId,type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptHandler of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_unregisterScriptHandler00
static int tolua_ExtensionsDragonBones_CCDragonBones_unregisterScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
   std::string type = ((  std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptHandler'", NULL);
#endif
  {
   self->unregisterScriptHandler(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterAllScriptHandler of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_unregisterAllScriptHandler00
static int tolua_ExtensionsDragonBones_CCDragonBones_unregisterAllScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterAllScriptHandler'", NULL);
#endif
  {
   self->unregisterAllScriptHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterAllScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasScriptHandler of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_hasScriptHandler00
static int tolua_ExtensionsDragonBones_CCDragonBones_hasScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
   std::string type = ((  std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasScriptHandler'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasScriptHandler(type);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)type);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScriptHandler of class  CCDragonBones */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDragonBones_getScriptHandler00
static int tolua_ExtensionsDragonBones_CCDragonBones_getScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragonBones",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragonBones* self = (CCDragonBones*)  tolua_tousertype(tolua_S,1,0);
   std::string type = ((  std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScriptHandler'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getScriptHandler(type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  CCDBManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBManager_getInstance00
static int tolua_ExtensionsDragonBones_CCDBManager_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDBManager* tolua_ret = (CCDBManager*)  CCDBManager::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDBManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroyInstance of class  CCDBManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBManager_destroyInstance00
static int tolua_ExtensionsDragonBones_CCDBManager_destroyInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDBManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDBManager::destroyInstance();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroyInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadData of class  CCDBManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBManager_loadData00
static int tolua_ExtensionsDragonBones_CCDBManager_loadData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBManager* self = (CCDBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string skeletonFile = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string textureAtlasFile = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadData'", NULL);
#endif
  {
   self->loadData(skeletonFile,textureAtlasFile,skeletonName,textureAtlasName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonFile);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasFile);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
  }
 }
 return 4;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadDataAsync of class  CCDBManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBManager_loadDataAsync00
static int tolua_ExtensionsDragonBones_CCDBManager_loadDataAsync00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !toluafix_isfunction(tolua_S,6,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBManager* self = (CCDBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string skeletonFile = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string textureAtlasFile = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,5,0));
  LUA_FUNCTION scriptHandler = (  toluafix_ref_function(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadDataAsync'", NULL);
#endif
  {
   self->loadDataAsync(skeletonFile,textureAtlasFile,skeletonName,textureAtlasName,scriptHandler);
   tolua_pushcppstring(tolua_S,(const char*)skeletonFile);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasFile);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
  }
 }
 return 4;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadDataAsync'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadDataByDir of class  CCDBManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBManager_loadDataByDir00
static int tolua_ExtensionsDragonBones_CCDBManager_loadDataByDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBManager* self = (CCDBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string path = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadDataByDir'", NULL);
#endif
  {
   self->loadDataByDir(path,skeletonName,textureAtlasName);
   tolua_pushcppstring(tolua_S,(const char*)path);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadDataByDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadDataByDirAsync of class  CCDBManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBManager_loadDataByDirAsync00
static int tolua_ExtensionsDragonBones_CCDBManager_loadDataByDirAsync00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !toluafix_isfunction(tolua_S,5,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBManager* self = (CCDBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string path = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  LUA_FUNCTION scriptHandler = (  toluafix_ref_function(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadDataByDirAsync'", NULL);
#endif
  {
   self->loadDataByDirAsync(path,skeletonName,textureAtlasName,scriptHandler);
   tolua_pushcppstring(tolua_S,(const char*)path);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadDataByDirAsync'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unloadData of class  CCDBManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBManager_unloadData00
static int tolua_ExtensionsDragonBones_CCDBManager_unloadData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBManager* self = (CCDBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unloadData'", NULL);
#endif
  {
   self->unloadData(skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unloadData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unloadData of class  CCDBManager */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBManager_unloadData01
static int tolua_ExtensionsDragonBones_CCDBManager_unloadData01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCDBManager* self = (CCDBManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string skeletonName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string textureAtlasName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unloadData'", NULL);
#endif
  {
   self->unloadData(skeletonName,textureAtlasName);
   tolua_pushcppstring(tolua_S,(const char*)skeletonName);
   tolua_pushcppstring(tolua_S,(const char*)textureAtlasName);
  }
 }
 return 2;
tolua_lerror:
 return tolua_ExtensionsDragonBones_CCDBManager_unloadData00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCDBAtlasNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBAtlasNode_new00
static int tolua_ExtensionsDragonBones_CCDBAtlasNode_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDBAtlasNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDBAtlasNode* tolua_ret = (CCDBAtlasNode*)  Mtolua_new((CCDBAtlasNode)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDBAtlasNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCDBAtlasNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBAtlasNode_new00_local
static int tolua_ExtensionsDragonBones_CCDBAtlasNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDBAtlasNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDBAtlasNode* tolua_ret = (CCDBAtlasNode*)  Mtolua_new((CCDBAtlasNode)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDBAtlasNode");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCDBAtlasNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBAtlasNode_delete00
static int tolua_ExtensionsDragonBones_CCDBAtlasNode_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBAtlasNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBAtlasNode* self = (CCDBAtlasNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOpacityModifyRGB of class  CCDBAtlasNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBAtlasNode_isOpacityModifyRGB00
static int tolua_ExtensionsDragonBones_CCDBAtlasNode_isOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBAtlasNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBAtlasNode* self = (CCDBAtlasNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOpacityModifyRGB'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOpacityModifyRGB();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOpacityModifyRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacityModifyRGB of class  CCDBAtlasNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBAtlasNode_setOpacityModifyRGB00
static int tolua_ExtensionsDragonBones_CCDBAtlasNode_setOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBAtlasNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBAtlasNode* self = (CCDBAtlasNode*)  tolua_tousertype(tolua_S,1,0);
  bool isOpacityModifyRGB = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacityModifyRGB'", NULL);
#endif
  {
   self->setOpacityModifyRGB(isOpacityModifyRGB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacityModifyRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getColor of class  CCDBAtlasNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBAtlasNode_getColor00
static int tolua_ExtensionsDragonBones_CCDBAtlasNode_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBAtlasNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBAtlasNode* self = (CCDBAtlasNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
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

/* method: setColor of class  CCDBAtlasNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBAtlasNode_setColor00
static int tolua_ExtensionsDragonBones_CCDBAtlasNode_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBAtlasNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBAtlasNode* self = (CCDBAtlasNode*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
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

/* method: setOpacity of class  CCDBAtlasNode */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_CCDBAtlasNode_setOpacity00
static int tolua_ExtensionsDragonBones_CCDBAtlasNode_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDBAtlasNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDBAtlasNode* self = (CCDBAtlasNode*)  tolua_tousertype(tolua_S,1,0);
  GLubyte opacity = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCTextureProtocol__ of class  CCDBAtlasNode */
#ifndef TOLUA_DISABLE_tolua_get_CCDBAtlasNode___CCTextureProtocol__
static int tolua_get_CCDBAtlasNode___CCTextureProtocol__(lua_State* tolua_S)
{
  CCDBAtlasNode* self = (CCDBAtlasNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCTextureProtocol__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCTextureProtocol*>(self), "CCTextureProtocol");
#else
   tolua_pushusertype(tolua_S,(void*)((CCTextureProtocol*)self), "CCTextureProtocol");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __dragonBones of class  CCDBAtlasNode */
#ifndef TOLUA_DISABLE_tolua_get_CCDBAtlasNode___dragonBones__Object__
static int tolua_get_CCDBAtlasNode___dragonBones__Object__(lua_State* tolua_S)
{
  CCDBAtlasNode* self = (CCDBAtlasNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__dragonBones'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<dragonBones::Object*>(self), "dragonBones::Object");
#else
   tolua_pushusertype(tolua_S,(void*)((dragonBones::Object*)self), "dragonBones::Object");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: MOVEMENT_CHANGE of class  AnimationEvent */
#ifndef TOLUA_DISABLE_tolua_get_AnimationEvent_MOVEMENT_CHANGE
static int tolua_get_AnimationEvent_MOVEMENT_CHANGE(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)AnimationEvent::MOVEMENT_CHANGE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FADE_IN of class  AnimationEvent */
#ifndef TOLUA_DISABLE_tolua_get_AnimationEvent_FADE_IN
static int tolua_get_AnimationEvent_FADE_IN(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)AnimationEvent::FADE_IN);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FADE_OUT of class  AnimationEvent */
#ifndef TOLUA_DISABLE_tolua_get_AnimationEvent_FADE_OUT
static int tolua_get_AnimationEvent_FADE_OUT(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)AnimationEvent::FADE_OUT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: START of class  AnimationEvent */
#ifndef TOLUA_DISABLE_tolua_get_AnimationEvent_START
static int tolua_get_AnimationEvent_START(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)AnimationEvent::START);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: COMPLETE of class  AnimationEvent */
#ifndef TOLUA_DISABLE_tolua_get_AnimationEvent_COMPLETE
static int tolua_get_AnimationEvent_COMPLETE(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)AnimationEvent::COMPLETE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LOOP_COMPLETE of class  AnimationEvent */
#ifndef TOLUA_DISABLE_tolua_get_AnimationEvent_LOOP_COMPLETE
static int tolua_get_AnimationEvent_LOOP_COMPLETE(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)AnimationEvent::LOOP_COMPLETE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FADE_IN_COMPLETE of class  AnimationEvent */
#ifndef TOLUA_DISABLE_tolua_get_AnimationEvent_FADE_IN_COMPLETE
static int tolua_get_AnimationEvent_FADE_IN_COMPLETE(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)AnimationEvent::FADE_IN_COMPLETE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FADE_OUT_COMPLETE of class  AnimationEvent */
#ifndef TOLUA_DISABLE_tolua_get_AnimationEvent_FADE_OUT_COMPLETE
static int tolua_get_AnimationEvent_FADE_OUT_COMPLETE(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)AnimationEvent::FADE_OUT_COMPLETE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMovementID of class  AnimationEvent */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationEvent_getMovementID00
static int tolua_ExtensionsDragonBones_AnimationEvent_getMovementID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationEvent* self = (AnimationEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMovementID'", NULL);
#endif
  {
    std::string tolua_ret = (  std::string)  self->getMovementID();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMovementID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: MOVEMENT_FRAME_EVENT of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_get_FrameEvent_MOVEMENT_FRAME_EVENT
static int tolua_get_FrameEvent_MOVEMENT_FRAME_EVENT(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)FrameEvent::MOVEMENT_FRAME_EVENT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ANIMATION_FRAME_EVENT of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_get_FrameEvent_ANIMATION_FRAME_EVENT
static int tolua_get_FrameEvent_ANIMATION_FRAME_EVENT(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)FrameEvent::ANIMATION_FRAME_EVENT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: BONE_FRAME_EVENT of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_get_FrameEvent_BONE_FRAME_EVENT
static int tolua_get_FrameEvent_BONE_FRAME_EVENT(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)FrameEvent::BONE_FRAME_EVENT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: frameLabel of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_get_FrameEvent_frameLabel
static int tolua_get_FrameEvent_frameLabel(lua_State* tolua_S)
{
  FrameEvent* self = (FrameEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'frameLabel'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->frameLabel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: frameLabel of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_set_FrameEvent_frameLabel
static int tolua_set_FrameEvent_frameLabel(lua_State* tolua_S)
{
  FrameEvent* self = (FrameEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'frameLabel'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->frameLabel = ((  std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bone of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_get_FrameEvent_bone_ptr
static int tolua_get_FrameEvent_bone_ptr(lua_State* tolua_S)
{
  FrameEvent* self = (FrameEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bone'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->bone,"Bone");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bone of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_set_FrameEvent_bone_ptr
static int tolua_set_FrameEvent_bone_ptr(lua_State* tolua_S)
{
  FrameEvent* self = (FrameEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bone'",NULL);
  if (!tolua_isusertype(tolua_S,2,"Bone",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bone = ((Bone*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: armature of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_get_FrameEvent_armature_ptr
static int tolua_get_FrameEvent_armature_ptr(lua_State* tolua_S)
{
  FrameEvent* self = (FrameEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'armature'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->armature,"Armature");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: armature of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_set_FrameEvent_armature_ptr
static int tolua_set_FrameEvent_armature_ptr(lua_State* tolua_S)
{
  FrameEvent* self = (FrameEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'armature'",NULL);
  if (!tolua_isusertype(tolua_S,2,"Armature",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->armature = ((Armature*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: animationState of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_get_FrameEvent_animationState_ptr
static int tolua_get_FrameEvent_animationState_ptr(lua_State* tolua_S)
{
  FrameEvent* self = (FrameEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'animationState'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->animationState,"AnimationState");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: animationState of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_set_FrameEvent_animationState_ptr
static int tolua_set_FrameEvent_animationState_ptr(lua_State* tolua_S)
{
  FrameEvent* self = (FrameEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'animationState'",NULL);
  if (!tolua_isusertype(tolua_S,2,"AnimationState",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->animationState = ((AnimationState*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_FrameEvent_new00
static int tolua_ExtensionsDragonBones_FrameEvent_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FrameEvent",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string type = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   FrameEvent* tolua_ret = (FrameEvent*)  Mtolua_new((FrameEvent)(type));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FrameEvent");
   tolua_pushcppstring(tolua_S,(const char*)type);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  FrameEvent */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_FrameEvent_new00_local
static int tolua_ExtensionsDragonBones_FrameEvent_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FrameEvent",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string type = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   FrameEvent* tolua_ret = (FrameEvent*)  Mtolua_new((FrameEvent)(type));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FrameEvent");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushcppstring(tolua_S,(const char*)type);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: frameRate of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_get_AnimationData_unsigned_frameRate
static int tolua_get_AnimationData_unsigned_frameRate(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'frameRate'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->frameRate);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: frameRate of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_set_AnimationData_unsigned_frameRate
static int tolua_set_AnimationData_unsigned_frameRate(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'frameRate'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->frameRate = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_get_AnimationData_name
static int tolua_get_AnimationData_name(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_set_AnimationData_name
static int tolua_set_AnimationData_name(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name = ((  std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: loop of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_get_AnimationData_loop
static int tolua_get_AnimationData_loop(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'loop'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->loop);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: loop of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_set_AnimationData_loop
static int tolua_set_AnimationData_loop(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'loop'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->loop = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tweenEasing of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_get_AnimationData_tweenEasing
static int tolua_get_AnimationData_tweenEasing(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tweenEasing'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->tweenEasing);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tweenEasing of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_set_AnimationData_tweenEasing
static int tolua_set_AnimationData_tweenEasing(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tweenEasing'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tweenEasing = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fadeInTime of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_get_AnimationData_fadeInTime
static int tolua_get_AnimationData_fadeInTime(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fadeInTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fadeInTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fadeInTime of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_set_AnimationData_fadeInTime
static int tolua_set_AnimationData_fadeInTime(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fadeInTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fadeInTime = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: duration of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_get_AnimationData_duration
static int tolua_get_AnimationData_duration(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'duration'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->duration);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: duration of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_set_AnimationData_duration
static int tolua_set_AnimationData_duration(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'duration'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->duration = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scale of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_get_AnimationData_scale
static int tolua_get_AnimationData_scale(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scale'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->scale);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scale of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_set_AnimationData_scale
static int tolua_set_AnimationData_scale(lua_State* tolua_S)
{
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scale'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scale = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationData_new00
static int tolua_ExtensionsDragonBones_AnimationData_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AnimationData* tolua_ret = (AnimationData*)  Mtolua_new((AnimationData)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationData_new00_local
static int tolua_ExtensionsDragonBones_AnimationData_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AnimationData* tolua_ret = (AnimationData*)  Mtolua_new((AnimationData)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationData");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationData_delete00
static int tolua_ExtensionsDragonBones_AnimationData_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFadeInTime of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationData_setFadeInTime00
static int tolua_ExtensionsDragonBones_AnimationData_setFadeInTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
   float value = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFadeInTime'", NULL);
#endif
  {
   self->setFadeInTime(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFadeInTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dispose of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationData_dispose00
static int tolua_ExtensionsDragonBones_AnimationData_dispose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dispose'", NULL);
#endif
  {
   self->dispose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dispose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimeline of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationData_getTimeline00
static int tolua_ExtensionsDragonBones_AnimationData_getTimeline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationData",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
  const std::string timelineName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimeline'", NULL);
#endif
  {
   TransformTimeline* tolua_ret = (TransformTimeline*)  self->getTimeline(timelineName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TransformTimeline");
   tolua_pushcppstring(tolua_S,(const char*)timelineName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimeline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTimeline of class  AnimationData */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_AnimationData_addTimeline00
static int tolua_ExtensionsDragonBones_AnimationData_addTimeline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationData",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"TransformTimeline",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationData* self = (AnimationData*)  tolua_tousertype(tolua_S,1,0);
  TransformTimeline* timeline = ((TransformTimeline*)  tolua_tousertype(tolua_S,2,0));
  const std::string timelineName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTimeline'", NULL);
#endif
  {
   self->addTimeline(timeline,timelineName);
   tolua_pushcppstring(tolua_S,(const char*)timelineName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTimeline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_get_DBTransform_x
static int tolua_get_DBTransform_x(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_set_DBTransform_x
static int tolua_set_DBTransform_x(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_get_DBTransform_y
static int tolua_get_DBTransform_y(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_set_DBTransform_y
static int tolua_set_DBTransform_y(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skewX of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_get_DBTransform_skewX
static int tolua_get_DBTransform_skewX(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skewX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->skewX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skewX of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_set_DBTransform_skewX
static int tolua_set_DBTransform_skewX(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skewX'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skewX = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skewY of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_get_DBTransform_skewY
static int tolua_get_DBTransform_skewY(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skewY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->skewY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skewY of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_set_DBTransform_skewY
static int tolua_set_DBTransform_skewY(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skewY'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skewY = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scaleX of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_get_DBTransform_scaleX
static int tolua_get_DBTransform_scaleX(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scaleX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->scaleX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scaleX of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_set_DBTransform_scaleX
static int tolua_set_DBTransform_scaleX(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scaleX'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scaleX = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scaleY of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_get_DBTransform_scaleY
static int tolua_get_DBTransform_scaleY(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scaleY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->scaleY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scaleY of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_set_DBTransform_scaleY
static int tolua_set_DBTransform_scaleY(lua_State* tolua_S)
{
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scaleY'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scaleY = ((  float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRotation of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBTransform_getRotation00
static int tolua_ExtensionsDragonBones_DBTransform_getRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRotation'", NULL);
#endif
  {
    float tolua_ret = (  float)  self->getRotation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRotation of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBTransform_setRotation00
static int tolua_ExtensionsDragonBones_DBTransform_setRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBTransform",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
   float value = ((  float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRotation'", NULL);
#endif
  {
   self->setRotation(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBTransform_new00
static int tolua_ExtensionsDragonBones_DBTransform_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DBTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DBTransform* tolua_ret = (DBTransform*)  Mtolua_new((DBTransform)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DBTransform");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBTransform_new00_local
static int tolua_ExtensionsDragonBones_DBTransform_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DBTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DBTransform* tolua_ret = (DBTransform*)  Mtolua_new((DBTransform)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DBTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBTransform_new01
static int tolua_ExtensionsDragonBones_DBTransform_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DBTransform",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const DBTransform",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DBTransform* transform = ((const DBTransform*)  tolua_tousertype(tolua_S,2,0));
  {
   DBTransform* tolua_ret = (DBTransform*)  Mtolua_new((DBTransform)(*transform));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DBTransform");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsDragonBones_DBTransform_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBTransform_new01_local
static int tolua_ExtensionsDragonBones_DBTransform_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DBTransform",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const DBTransform",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DBTransform* transform = ((const DBTransform*)  tolua_tousertype(tolua_S,2,0));
  {
   DBTransform* tolua_ret = (DBTransform*)  Mtolua_new((DBTransform)(*transform));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DBTransform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsDragonBones_DBTransform_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: toString of class  DBTransform */
#ifndef TOLUA_DISABLE_tolua_ExtensionsDragonBones_DBTransform_toString00
static int tolua_ExtensionsDragonBones_DBTransform_toString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBTransform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBTransform* self = (DBTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toString'", NULL);
#endif
  {
    std::string tolua_ret = (  std::string)  self->toString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ExtensionsDragonBones_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Object","Object","",tolua_collect_Object);
  #else
  tolua_cclass(tolua_S,"Object","Object","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Object");
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_Object_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_Object_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_Object_new00_local);
   tolua_function(tolua_S,"delete",tolua_ExtensionsDragonBones_Object_delete00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Event","Event","",NULL);
  tolua_beginmodule(tolua_S,"Event");
   tolua_function(tolua_S,"getType",tolua_ExtensionsDragonBones_Event_getType00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Armature","Armature","IAnimatable",tolua_collect_Armature);
  #else
  tolua_cclass(tolua_S,"Armature","Armature","IAnimatable",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Armature");
   tolua_variable(tolua_S,"name",tolua_get_Armature_name,tolua_set_Armature_name);
   tolua_function(tolua_S,"getAnimation",tolua_ExtensionsDragonBones_Armature_getAnimation00);
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_Armature_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_Armature_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_Armature_new00_local);
   tolua_function(tolua_S,"dispose",tolua_ExtensionsDragonBones_Armature_dispose00);
   tolua_function(tolua_S,"invalidUpdate",tolua_ExtensionsDragonBones_Armature_invalidUpdate00);
   tolua_function(tolua_S,"advanceTime",tolua_ExtensionsDragonBones_Armature_advanceTime00);
   tolua_function(tolua_S,"getSlot",tolua_ExtensionsDragonBones_Armature_getSlot00);
   tolua_function(tolua_S,"getSlotByDisplay",tolua_ExtensionsDragonBones_Armature_getSlotByDisplay00);
   tolua_function(tolua_S,"removeSlot",tolua_ExtensionsDragonBones_Armature_removeSlot00);
   tolua_function(tolua_S,"removeSlotByName",tolua_ExtensionsDragonBones_Armature_removeSlotByName00);
   tolua_function(tolua_S,"getBone",tolua_ExtensionsDragonBones_Armature_getBone00);
   tolua_function(tolua_S,"getBoneByDisplay",tolua_ExtensionsDragonBones_Armature_getBoneByDisplay00);
   tolua_function(tolua_S,"removeBone",tolua_ExtensionsDragonBones_Armature_removeBone00);
   tolua_function(tolua_S,"removeBoneByName",tolua_ExtensionsDragonBones_Armature_removeBoneByName00);
   tolua_function(tolua_S,"addChild",tolua_ExtensionsDragonBones_Armature_addChild00);
   tolua_function(tolua_S,"addBone",tolua_ExtensionsDragonBones_Armature_addBone00);
   tolua_function(tolua_S,"updateSlotsZOrder",tolua_ExtensionsDragonBones_Armature_updateSlotsZOrder00);
   tolua_function(tolua_S,"addDBObject",tolua_ExtensionsDragonBones_Armature_addDBObject00);
   tolua_function(tolua_S,"removeDBObject",tolua_ExtensionsDragonBones_Armature_removeDBObject00);
   tolua_function(tolua_S,"sortBone",tolua_ExtensionsDragonBones_Armature_sortBone00);
   tolua_function(tolua_S,"sortBoneList",tolua_ExtensionsDragonBones_Armature_sortBoneList00);
   tolua_function(tolua_S,"arriveAtFrame",tolua_ExtensionsDragonBones_Armature_arriveAtFrame00);
   tolua_function(tolua_S,"sortSlot",tolua_ExtensionsDragonBones_Armature_sortSlot00);
   tolua_variable(tolua_S,"__EventDispatcher__",tolua_get_Armature___EventDispatcher__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Bone","Bone","DBObject",tolua_collect_Bone);
  #else
  tolua_cclass(tolua_S,"Bone","Bone","DBObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Bone");
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_Bone_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_Bone_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_Bone_new00_local);
   tolua_function(tolua_S,"delete",tolua_ExtensionsDragonBones_Bone_delete00);
   tolua_function(tolua_S,"getChildArmature",tolua_ExtensionsDragonBones_Bone_getChildArmature00);
   tolua_function(tolua_S,"getDisplay",tolua_ExtensionsDragonBones_Bone_getDisplay00);
   tolua_function(tolua_S,"setDisplay",tolua_ExtensionsDragonBones_Bone_setDisplay00);
   tolua_variable(tolua_S,"displayController",tolua_get_Bone_displayController,tolua_set_Bone_displayController);
   tolua_function(tolua_S,"setVisible",tolua_ExtensionsDragonBones_Bone_setVisible00);
   tolua_function(tolua_S,"setArmature",tolua_ExtensionsDragonBones_Bone_setArmature00);
   tolua_function(tolua_S,"dispose",tolua_ExtensionsDragonBones_Bone_dispose00);
   tolua_function(tolua_S,"contains",tolua_ExtensionsDragonBones_Bone_contains00);
   tolua_function(tolua_S,"addChild",tolua_ExtensionsDragonBones_Bone_addChild00);
   tolua_function(tolua_S,"removeChild",tolua_ExtensionsDragonBones_Bone_removeChild00);
   tolua_function(tolua_S,"updateColor",tolua_ExtensionsDragonBones_Bone_updateColor00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Slot","Slot","DBObject",tolua_collect_Slot);
  #else
  tolua_cclass(tolua_S,"Slot","Slot","DBObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Slot");
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_Slot_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_Slot_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_Slot_new00_local);
   tolua_function(tolua_S,"delete",tolua_ExtensionsDragonBones_Slot_delete00);
   tolua_function(tolua_S,"getZOrder",tolua_ExtensionsDragonBones_Slot_getZOrder00);
   tolua_function(tolua_S,"setZOrder",tolua_ExtensionsDragonBones_Slot_setZOrder00);
   tolua_function(tolua_S,"getBlendMode",tolua_ExtensionsDragonBones_Slot_getBlendMode00);
   tolua_function(tolua_S,"setBlendMode",tolua_ExtensionsDragonBones_Slot_setBlendMode00);
   tolua_function(tolua_S,"getDisplay",tolua_ExtensionsDragonBones_Slot_getDisplay00);
   tolua_function(tolua_S,"setDisplayValue",tolua_ExtensionsDragonBones_Slot_setDisplayValue00);
   tolua_function(tolua_S,"getChildArmature",tolua_ExtensionsDragonBones_Slot_getChildArmature00);
   tolua_function(tolua_S,"setChildArmature",tolua_ExtensionsDragonBones_Slot_setChildArmature00);
   tolua_function(tolua_S,"setDisplay",tolua_ExtensionsDragonBones_Slot_setDisplay00);
   tolua_function(tolua_S,"changeDisplay",tolua_ExtensionsDragonBones_Slot_changeDisplay00);
   tolua_function(tolua_S,"setVisible",tolua_ExtensionsDragonBones_Slot_setVisible00);
   tolua_function(tolua_S,"setArmature",tolua_ExtensionsDragonBones_Slot_setArmature00);
   tolua_function(tolua_S,"dispose",tolua_ExtensionsDragonBones_Slot_dispose00);
   tolua_function(tolua_S,"update",tolua_ExtensionsDragonBones_Slot_update00);
   tolua_function(tolua_S,"updateVisible",tolua_ExtensionsDragonBones_Slot_updateVisible00);
   tolua_function(tolua_S,"updateChildArmatureAnimation",tolua_ExtensionsDragonBones_Slot_updateChildArmatureAnimation00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"DBObject","DBObject","",tolua_collect_DBObject);
  #else
  tolua_cclass(tolua_S,"DBObject","DBObject","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"DBObject");
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_DBObject_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_DBObject_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_DBObject_new00_local);
   tolua_function(tolua_S,"delete",tolua_ExtensionsDragonBones_DBObject_delete00);
   tolua_variable(tolua_S,"global",tolua_get_DBObject_global,tolua_set_DBObject_global);
   tolua_variable(tolua_S,"origin",tolua_get_DBObject_origin,tolua_set_DBObject_origin);
   tolua_variable(tolua_S,"offset",tolua_get_DBObject_offset,tolua_set_DBObject_offset);
   tolua_variable(tolua_S,"tween",tolua_get_DBObject_tween,tolua_set_DBObject_tween);
   tolua_function(tolua_S,"setVisible",tolua_ExtensionsDragonBones_DBObject_setVisible00);
   tolua_function(tolua_S,"getVisible",tolua_ExtensionsDragonBones_DBObject_getVisible00);
   tolua_function(tolua_S,"getArmature",tolua_ExtensionsDragonBones_DBObject_getArmature00);
   tolua_function(tolua_S,"setArmature",tolua_ExtensionsDragonBones_DBObject_setArmature00);
   tolua_function(tolua_S,"dispose",tolua_ExtensionsDragonBones_DBObject_dispose00);
   tolua_function(tolua_S,"update",tolua_ExtensionsDragonBones_DBObject_update00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Animation","Animation","",tolua_collect_Animation);
  #else
  tolua_cclass(tolua_S,"Animation","Animation","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Animation");
   tolua_variable(tolua_S,"NONE",tolua_get_Animation_NONE,NULL);
   tolua_variable(tolua_S,"SAME_LAYER",tolua_get_Animation_SAME_LAYER,NULL);
   tolua_variable(tolua_S,"SAME_GROUP",tolua_get_Animation_SAME_GROUP,NULL);
   tolua_variable(tolua_S,"SAME_LAYER_AND_GROUP",tolua_get_Animation_SAME_LAYER_AND_GROUP,NULL);
   tolua_variable(tolua_S,"ALL",tolua_get_Animation_ALL,NULL);
   tolua_function(tolua_S,"getLastAnimationName",tolua_ExtensionsDragonBones_Animation_getLastAnimationName00);
   tolua_function(tolua_S,"getMovementID",tolua_ExtensionsDragonBones_Animation_getMovementID00);
   tolua_function(tolua_S,"getAnimationData",tolua_ExtensionsDragonBones_Animation_getAnimationData00);
   tolua_function(tolua_S,"getLastAnimationState",tolua_ExtensionsDragonBones_Animation_getLastAnimationState00);
   tolua_function(tolua_S,"getIsPlaying",tolua_ExtensionsDragonBones_Animation_getIsPlaying00);
   tolua_function(tolua_S,"getIsComplete",tolua_ExtensionsDragonBones_Animation_getIsComplete00);
   tolua_function(tolua_S,"getTimeScale",tolua_ExtensionsDragonBones_Animation_getTimeScale00);
   tolua_function(tolua_S,"setTimeScale",tolua_ExtensionsDragonBones_Animation_setTimeScale00);
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_Animation_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_Animation_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_Animation_new00_local);
   tolua_function(tolua_S,"dispose",tolua_ExtensionsDragonBones_Animation_dispose00);
   tolua_function(tolua_S,"gotoAndPlay",tolua_ExtensionsDragonBones_Animation_gotoAndPlay00);
   tolua_function(tolua_S,"play",tolua_ExtensionsDragonBones_Animation_play00);
   tolua_function(tolua_S,"stop",tolua_ExtensionsDragonBones_Animation_stop00);
   tolua_function(tolua_S,"getState",tolua_ExtensionsDragonBones_Animation_getState00);
   tolua_function(tolua_S,"hasAnimation",tolua_ExtensionsDragonBones_Animation_hasAnimation00);
   tolua_function(tolua_S,"advanceTime",tolua_ExtensionsDragonBones_Animation_advanceTime00);
   tolua_function(tolua_S,"setActive",tolua_ExtensionsDragonBones_Animation_setActive00);
   tolua_function(tolua_S,"addLayer",tolua_ExtensionsDragonBones_Animation_addLayer00);
   tolua_function(tolua_S,"addState",tolua_ExtensionsDragonBones_Animation_addState00);
   tolua_function(tolua_S,"removeState",tolua_ExtensionsDragonBones_Animation_removeState00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"AnimationState","AnimationState","",NULL);
  tolua_beginmodule(tolua_S,"AnimationState");
   tolua_function(tolua_S,"borrowObject",tolua_ExtensionsDragonBones_AnimationState_borrowObject00);
   tolua_function(tolua_S,"returnObject",tolua_ExtensionsDragonBones_AnimationState_returnObject00);
   tolua_function(tolua_S,"clear",tolua_ExtensionsDragonBones_AnimationState_clear00);
   tolua_function(tolua_S,"getClip",tolua_ExtensionsDragonBones_AnimationState_getClip00);
   tolua_function(tolua_S,"getLoopCount",tolua_ExtensionsDragonBones_AnimationState_getLoopCount00);
   tolua_function(tolua_S,"getLoop",tolua_ExtensionsDragonBones_AnimationState_getLoop00);
   tolua_function(tolua_S,"getLayer",tolua_ExtensionsDragonBones_AnimationState_getLayer00);
   tolua_function(tolua_S,"getIsPlaying",tolua_ExtensionsDragonBones_AnimationState_getIsPlaying00);
   tolua_function(tolua_S,"getIsComplete",tolua_ExtensionsDragonBones_AnimationState_getIsComplete00);
   tolua_function(tolua_S,"getFadeInTime",tolua_ExtensionsDragonBones_AnimationState_getFadeInTime00);
   tolua_function(tolua_S,"getTotalTime",tolua_ExtensionsDragonBones_AnimationState_getTotalTime00);
   tolua_function(tolua_S,"getCurrentTime",tolua_ExtensionsDragonBones_AnimationState_getCurrentTime00);
   tolua_function(tolua_S,"setCurrentTime",tolua_ExtensionsDragonBones_AnimationState_setCurrentTime00);
   tolua_function(tolua_S,"getTimeScale",tolua_ExtensionsDragonBones_AnimationState_getTimeScale00);
   tolua_function(tolua_S,"setTimeScale",tolua_ExtensionsDragonBones_AnimationState_setTimeScale00);
   tolua_function(tolua_S,"fadeIn",tolua_ExtensionsDragonBones_AnimationState_fadeIn00);
   tolua_function(tolua_S,"fadeOut",tolua_ExtensionsDragonBones_AnimationState_fadeOut00);
   tolua_function(tolua_S,"play",tolua_ExtensionsDragonBones_AnimationState_play00);
   tolua_function(tolua_S,"stop",tolua_ExtensionsDragonBones_AnimationState_stop00);
   tolua_function(tolua_S,"getMixingTransform",tolua_ExtensionsDragonBones_AnimationState_getMixingTransform00);
   tolua_function(tolua_S,"addMixingTransform",tolua_ExtensionsDragonBones_AnimationState_addMixingTransform00);
   tolua_function(tolua_S,"removeMixingTransform",tolua_ExtensionsDragonBones_AnimationState_removeMixingTransform00);
   tolua_function(tolua_S,"removeMixingTransform",tolua_ExtensionsDragonBones_AnimationState_removeMixingTransform01);
   tolua_function(tolua_S,"advanceTime",tolua_ExtensionsDragonBones_AnimationState_advanceTime00);
   tolua_function(tolua_S,"updateTimelineStates",tolua_ExtensionsDragonBones_AnimationState_updateTimelineStates00);
   tolua_function(tolua_S,"addTimelineState",tolua_ExtensionsDragonBones_AnimationState_addTimelineState00);
   tolua_function(tolua_S,"removeTimelineState",tolua_ExtensionsDragonBones_AnimationState_removeTimelineState00);
   tolua_function(tolua_S,"clearAll",tolua_ExtensionsDragonBones_AnimationState_clearAll00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"dragonBones",0);
  tolua_beginmodule(tolua_S,"dragonBones");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CCDBNode","dragonBones::CCDBNode","Object",tolua_collect_dragonBones__CCDBNode);
   #else
   tolua_cclass(tolua_S,"CCDBNode","dragonBones::CCDBNode","Object",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CCDBNode");
    tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_dragonBones_CCDBNode_new00);
    tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_dragonBones_CCDBNode_new00_local);
    tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_dragonBones_CCDBNode_new00_local);
    tolua_function(tolua_S,"delete",tolua_ExtensionsDragonBones_dragonBones_CCDBNode_delete00);
    tolua_function(tolua_S,"getNode",tolua_ExtensionsDragonBones_dragonBones_CCDBNode_getNode00);
    tolua_function(tolua_S,"getNode",tolua_ExtensionsDragonBones_dragonBones_CCDBNode_getNode01);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCDragonBones","CCDragonBones","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCDragonBones");
   tolua_function(tolua_S,"create",tolua_ExtensionsDragonBones_CCDragonBones_create00);
   tolua_function(tolua_S,"createByName",tolua_ExtensionsDragonBones_CCDragonBones_createByName00);
   tolua_function(tolua_S,"createByName",tolua_ExtensionsDragonBones_CCDragonBones_createByName01);
   tolua_function(tolua_S,"createByName",tolua_ExtensionsDragonBones_CCDragonBones_createByName02);
   tolua_function(tolua_S,"createByName",tolua_ExtensionsDragonBones_CCDragonBones_createByName03);
   tolua_function(tolua_S,"createByName",tolua_ExtensionsDragonBones_CCDragonBones_createByName04);
   tolua_function(tolua_S,"createByDir",tolua_ExtensionsDragonBones_CCDragonBones_createByDir00);
   tolua_function(tolua_S,"createByDir",tolua_ExtensionsDragonBones_CCDragonBones_createByDir01);
   tolua_function(tolua_S,"createByDir",tolua_ExtensionsDragonBones_CCDragonBones_createByDir02);
   tolua_function(tolua_S,"createByDir",tolua_ExtensionsDragonBones_CCDragonBones_createByDir03);
   tolua_function(tolua_S,"createByDir",tolua_ExtensionsDragonBones_CCDragonBones_createByDir04);
   tolua_function(tolua_S,"createByFiles",tolua_ExtensionsDragonBones_CCDragonBones_createByFiles00);
   tolua_function(tolua_S,"createByFiles",tolua_ExtensionsDragonBones_CCDragonBones_createByFiles01);
   tolua_function(tolua_S,"createByFiles",tolua_ExtensionsDragonBones_CCDragonBones_createByFiles02);
   tolua_function(tolua_S,"createByFiles",tolua_ExtensionsDragonBones_CCDragonBones_createByFiles03);
   tolua_function(tolua_S,"createByFiles",tolua_ExtensionsDragonBones_CCDragonBones_createByFiles04);
   tolua_function(tolua_S,"getDisplayNode",tolua_ExtensionsDragonBones_CCDragonBones_getDisplayNode00);
   tolua_function(tolua_S,"getArmature",tolua_ExtensionsDragonBones_CCDragonBones_getArmature00);
   tolua_function(tolua_S,"getAnimation",tolua_ExtensionsDragonBones_CCDragonBones_getAnimation00);
   tolua_function(tolua_S,"getAnimationList",tolua_ExtensionsDragonBones_CCDragonBones_getAnimationList00);
   tolua_function(tolua_S,"gotoAndPlay",tolua_ExtensionsDragonBones_CCDragonBones_gotoAndPlay00);
   tolua_function(tolua_S,"setBoneTexture",tolua_ExtensionsDragonBones_CCDragonBones_setBoneTexture00);
   tolua_function(tolua_S,"registerScriptHandler",tolua_ExtensionsDragonBones_CCDragonBones_registerScriptHandler00);
   tolua_function(tolua_S,"unregisterScriptHandler",tolua_ExtensionsDragonBones_CCDragonBones_unregisterScriptHandler00);
   tolua_function(tolua_S,"unregisterAllScriptHandler",tolua_ExtensionsDragonBones_CCDragonBones_unregisterAllScriptHandler00);
   tolua_function(tolua_S,"hasScriptHandler",tolua_ExtensionsDragonBones_CCDragonBones_hasScriptHandler00);
   tolua_function(tolua_S,"getScriptHandler",tolua_ExtensionsDragonBones_CCDragonBones_getScriptHandler00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCDBManager","CCDBManager","CCDBFactory",NULL);
  tolua_beginmodule(tolua_S,"CCDBManager");
   tolua_function(tolua_S,"getInstance",tolua_ExtensionsDragonBones_CCDBManager_getInstance00);
   tolua_function(tolua_S,"destroyInstance",tolua_ExtensionsDragonBones_CCDBManager_destroyInstance00);
   tolua_function(tolua_S,"loadData",tolua_ExtensionsDragonBones_CCDBManager_loadData00);
   tolua_function(tolua_S,"loadDataAsync",tolua_ExtensionsDragonBones_CCDBManager_loadDataAsync00);
   tolua_function(tolua_S,"loadDataByDir",tolua_ExtensionsDragonBones_CCDBManager_loadDataByDir00);
   tolua_function(tolua_S,"loadDataByDirAsync",tolua_ExtensionsDragonBones_CCDBManager_loadDataByDirAsync00);
   tolua_function(tolua_S,"unloadData",tolua_ExtensionsDragonBones_CCDBManager_unloadData00);
   tolua_function(tolua_S,"unloadData",tolua_ExtensionsDragonBones_CCDBManager_unloadData01);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCDBAtlasNode","CCDBAtlasNode","CCNode",tolua_collect_CCDBAtlasNode);
  #else
  tolua_cclass(tolua_S,"CCDBAtlasNode","CCDBAtlasNode","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCDBAtlasNode");
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_CCDBAtlasNode_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_CCDBAtlasNode_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_CCDBAtlasNode_new00_local);
   tolua_function(tolua_S,"delete",tolua_ExtensionsDragonBones_CCDBAtlasNode_delete00);
   tolua_function(tolua_S,"isOpacityModifyRGB",tolua_ExtensionsDragonBones_CCDBAtlasNode_isOpacityModifyRGB00);
   tolua_function(tolua_S,"setOpacityModifyRGB",tolua_ExtensionsDragonBones_CCDBAtlasNode_setOpacityModifyRGB00);
   tolua_function(tolua_S,"getColor",tolua_ExtensionsDragonBones_CCDBAtlasNode_getColor00);
   tolua_function(tolua_S,"setColor",tolua_ExtensionsDragonBones_CCDBAtlasNode_setColor00);
   tolua_function(tolua_S,"setOpacity",tolua_ExtensionsDragonBones_CCDBAtlasNode_setOpacity00);
   tolua_variable(tolua_S,"__CCTextureProtocol__",tolua_get_CCDBAtlasNode___CCTextureProtocol__,NULL);
   tolua_variable(tolua_S,"__dragonBones__Object__",tolua_get_CCDBAtlasNode___dragonBones__Object__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"AnimationEvent","AnimationEvent","Event",NULL);
  tolua_beginmodule(tolua_S,"AnimationEvent");
   tolua_variable(tolua_S,"MOVEMENT_CHANGE",tolua_get_AnimationEvent_MOVEMENT_CHANGE,NULL);
   tolua_variable(tolua_S,"FADE_IN",tolua_get_AnimationEvent_FADE_IN,NULL);
   tolua_variable(tolua_S,"FADE_OUT",tolua_get_AnimationEvent_FADE_OUT,NULL);
   tolua_variable(tolua_S,"START",tolua_get_AnimationEvent_START,NULL);
   tolua_variable(tolua_S,"COMPLETE",tolua_get_AnimationEvent_COMPLETE,NULL);
   tolua_variable(tolua_S,"LOOP_COMPLETE",tolua_get_AnimationEvent_LOOP_COMPLETE,NULL);
   tolua_variable(tolua_S,"FADE_IN_COMPLETE",tolua_get_AnimationEvent_FADE_IN_COMPLETE,NULL);
   tolua_variable(tolua_S,"FADE_OUT_COMPLETE",tolua_get_AnimationEvent_FADE_OUT_COMPLETE,NULL);
   tolua_function(tolua_S,"getMovementID",tolua_ExtensionsDragonBones_AnimationEvent_getMovementID00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"FrameEvent","FrameEvent","Event",tolua_collect_FrameEvent);
  #else
  tolua_cclass(tolua_S,"FrameEvent","FrameEvent","Event",NULL);
  #endif
  tolua_beginmodule(tolua_S,"FrameEvent");
   tolua_variable(tolua_S,"MOVEMENT_FRAME_EVENT",tolua_get_FrameEvent_MOVEMENT_FRAME_EVENT,NULL);
   tolua_variable(tolua_S,"ANIMATION_FRAME_EVENT",tolua_get_FrameEvent_ANIMATION_FRAME_EVENT,NULL);
   tolua_variable(tolua_S,"BONE_FRAME_EVENT",tolua_get_FrameEvent_BONE_FRAME_EVENT,NULL);
   tolua_variable(tolua_S,"frameLabel",tolua_get_FrameEvent_frameLabel,tolua_set_FrameEvent_frameLabel);
   tolua_variable(tolua_S,"bone",tolua_get_FrameEvent_bone_ptr,tolua_set_FrameEvent_bone_ptr);
   tolua_variable(tolua_S,"armature",tolua_get_FrameEvent_armature_ptr,tolua_set_FrameEvent_armature_ptr);
   tolua_variable(tolua_S,"animationState",tolua_get_FrameEvent_animationState_ptr,tolua_set_FrameEvent_animationState_ptr);
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_FrameEvent_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_FrameEvent_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_FrameEvent_new00_local);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"AnimationData","AnimationData","Timeline",tolua_collect_AnimationData);
  #else
  tolua_cclass(tolua_S,"AnimationData","AnimationData","Timeline",NULL);
  #endif
  tolua_beginmodule(tolua_S,"AnimationData");
   tolua_variable(tolua_S,"frameRate",tolua_get_AnimationData_unsigned_frameRate,tolua_set_AnimationData_unsigned_frameRate);
   tolua_variable(tolua_S,"name",tolua_get_AnimationData_name,tolua_set_AnimationData_name);
   tolua_variable(tolua_S,"loop",tolua_get_AnimationData_loop,tolua_set_AnimationData_loop);
   tolua_variable(tolua_S,"tweenEasing",tolua_get_AnimationData_tweenEasing,tolua_set_AnimationData_tweenEasing);
   tolua_variable(tolua_S,"fadeInTime",tolua_get_AnimationData_fadeInTime,tolua_set_AnimationData_fadeInTime);
   tolua_variable(tolua_S,"duration",tolua_get_AnimationData_duration,tolua_set_AnimationData_duration);
   tolua_variable(tolua_S,"scale",tolua_get_AnimationData_scale,tolua_set_AnimationData_scale);
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_AnimationData_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_AnimationData_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_AnimationData_new00_local);
   tolua_function(tolua_S,"delete",tolua_ExtensionsDragonBones_AnimationData_delete00);
   tolua_function(tolua_S,"setFadeInTime",tolua_ExtensionsDragonBones_AnimationData_setFadeInTime00);
   tolua_function(tolua_S,"dispose",tolua_ExtensionsDragonBones_AnimationData_dispose00);
   tolua_function(tolua_S,"getTimeline",tolua_ExtensionsDragonBones_AnimationData_getTimeline00);
   tolua_function(tolua_S,"addTimeline",tolua_ExtensionsDragonBones_AnimationData_addTimeline00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"DBTransform","DBTransform","",tolua_collect_DBTransform);
  #else
  tolua_cclass(tolua_S,"DBTransform","DBTransform","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"DBTransform");
   tolua_variable(tolua_S,"x",tolua_get_DBTransform_x,tolua_set_DBTransform_x);
   tolua_variable(tolua_S,"y",tolua_get_DBTransform_y,tolua_set_DBTransform_y);
   tolua_variable(tolua_S,"skewX",tolua_get_DBTransform_skewX,tolua_set_DBTransform_skewX);
   tolua_variable(tolua_S,"skewY",tolua_get_DBTransform_skewY,tolua_set_DBTransform_skewY);
   tolua_variable(tolua_S,"scaleX",tolua_get_DBTransform_scaleX,tolua_set_DBTransform_scaleX);
   tolua_variable(tolua_S,"scaleY",tolua_get_DBTransform_scaleY,tolua_set_DBTransform_scaleY);
   tolua_function(tolua_S,"getRotation",tolua_ExtensionsDragonBones_DBTransform_getRotation00);
   tolua_function(tolua_S,"setRotation",tolua_ExtensionsDragonBones_DBTransform_setRotation00);
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_DBTransform_new00);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_DBTransform_new00_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_DBTransform_new00_local);
   tolua_function(tolua_S,"new",tolua_ExtensionsDragonBones_DBTransform_new01);
   tolua_function(tolua_S,"new_local",tolua_ExtensionsDragonBones_DBTransform_new01_local);
   tolua_function(tolua_S,".call",tolua_ExtensionsDragonBones_DBTransform_new01_local);
   tolua_function(tolua_S,"toString",tolua_ExtensionsDragonBones_DBTransform_toString00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ExtensionsDragonBones (lua_State* tolua_S) {
 return tolua_ExtensionsDragonBones_open(tolua_S);
};
#endif

