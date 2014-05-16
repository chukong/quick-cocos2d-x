/*
** Lua binding: MobClickCppForLua_luabinding
** Generated automatically by tolua++-1.0.92 on Fri May 16 14:45:30 2014.
*/

#include "MobClickCppForLua_luabinding.h"
#include "CCLuaEngine.h"

using namespace cocos2d;

#include "MobClickCppForLua.h"


#include <typeinfo>

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"MobClickCppForLua"); toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(MobClickCppForLua)), "MobClickCppForLua");
}

/* method: setAppVersion of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setAppVersion00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setAppVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* appVersion = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::setAppVersion(appVersion);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAppVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCrashReportEnabled of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setCrashReportEnabled00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setCrashReportEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   MobClickCppForLua::setCrashReportEnabled(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCrashReportEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLogEnabled of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setLogEnabled00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setLogEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   MobClickCppForLua::setLogEnabled(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLogEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startWithAppkey of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_startWithAppkey00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_startWithAppkey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* appKey = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* channelId = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   MobClickCppForLua::startWithAppkey(appKey,channelId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startWithAppkey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: applicationDidEnterBackground of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_applicationDidEnterBackground00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_applicationDidEnterBackground00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MobClickCppForLua::applicationDidEnterBackground();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'applicationDidEnterBackground'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: applicationWillEnterForeground of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_applicationWillEnterForeground00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_applicationWillEnterForeground00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MobClickCppForLua::applicationWillEnterForeground();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'applicationWillEnterForeground'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: endAnalytics of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endAnalytics00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endAnalytics00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MobClickCppForLua::endAnalytics();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'endAnalytics'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: event of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_event00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_event00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventId = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* label = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   MobClickCppForLua::event(eventId,label);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'event'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: eventCustom of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_eventCustom00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_eventCustom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventId = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* attributes = ((const char*)  tolua_tostring(tolua_S,3,0));
  int counter = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   MobClickCppForLua::eventCustom(eventId,attributes,counter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'eventCustom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: beginEvent of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginEvent00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventId = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::beginEvent(eventId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'beginEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: endEvent of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endEvent00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventId = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::endEvent(eventId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'endEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: beginEventWithLabel of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginEventWithLabel00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginEventWithLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventId = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* label = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   MobClickCppForLua::beginEventWithLabel(eventId,label);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'beginEventWithLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: endEventWithLabel of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endEventWithLabel00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endEventWithLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventId = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* label = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   MobClickCppForLua::endEventWithLabel(eventId,label);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'endEventWithLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: beginEventWithAttributes of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginEventWithAttributes00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginEventWithAttributes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventId = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* primarykey = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* attributes = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   MobClickCppForLua::beginEventWithAttributes(eventId,primarykey,attributes);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'beginEventWithAttributes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: endEventWithAttributes of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endEventWithAttributes00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endEventWithAttributes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* eventId = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* primarykey = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   MobClickCppForLua::endEventWithAttributes(eventId,primarykey);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'endEventWithAttributes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: beginLogPageView of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginLogPageView00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginLogPageView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pageName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::beginLogPageView(pageName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'beginLogPageView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: endLogPageView of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endLogPageView00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endLogPageView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pageName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::endLogPageView(pageName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'endLogPageView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkUpdate of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_checkUpdate00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_checkUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MobClickCppForLua::checkUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkUpdate of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_checkUpdate01
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_checkUpdate01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* title = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* cancelTitle = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* otherTitle = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   MobClickCppForLua::checkUpdate(title,cancelTitle,otherTitle);
  }
 }
 return 0;
tolua_lerror:
 return tolua_MobClickCppForLua_luabinding_MobClickCppForLua_checkUpdate00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUpdateOnlyWifi of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setUpdateOnlyWifi00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setUpdateOnlyWifi00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool updateOnlyWifi = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   MobClickCppForLua::setUpdateOnlyWifi(updateOnlyWifi);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUpdateOnlyWifi'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateOnlineConfig of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_updateOnlineConfig00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_updateOnlineConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MobClickCppForLua::updateOnlineConfig();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateOnlineConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getConfigParams of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_getConfigParams00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_getConfigParams00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   const char* tolua_ret = (const char*)  MobClickCppForLua::getConfigParams(key);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getConfigParams'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUserLevel of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setUserLevel00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setUserLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* level = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::setUserLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUserLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setUserInfo of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setUserInfo00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setUserInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* userId = ((const char*)  tolua_tostring(tolua_S,2,0));
  int sex = ((int)  tolua_tonumber(tolua_S,3,0));
  int age = ((int)  tolua_tonumber(tolua_S,4,0));
  const char* platform = ((const char*)  tolua_tostring(tolua_S,5,0));
  {
   MobClickCppForLua::setUserInfo(userId,sex,age,platform);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUserInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startLevel of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_startLevel00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_startLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* level = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::startLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: finishLevel of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_finishLevel00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_finishLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* level = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::finishLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'finishLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: failLevel of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_failLevel00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_failLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* level = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::failLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'failLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pay of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_pay00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_pay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double cash = ((double)  tolua_tonumber(tolua_S,2,0));
  int source = ((int)  tolua_tonumber(tolua_S,3,0));
  double coin = ((double)  tolua_tonumber(tolua_S,4,0));
  {
   MobClickCppForLua::pay(cash,source,coin);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pay of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_pay01
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_pay01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double cash = ((double)  tolua_tonumber(tolua_S,2,0));
  int source = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* item = ((const char*)  tolua_tostring(tolua_S,4,0));
  int amount = ((int)  tolua_tonumber(tolua_S,5,0));
  double price = ((double)  tolua_tonumber(tolua_S,6,0));
  {
   MobClickCppForLua::pay(cash,source,item,amount,price);
  }
 }
 return 0;
tolua_lerror:
 return tolua_MobClickCppForLua_luabinding_MobClickCppForLua_pay00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: buy of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_buy00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_buy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* item = ((const char*)  tolua_tostring(tolua_S,2,0));
  int amount = ((int)  tolua_tonumber(tolua_S,3,0));
  double price = ((double)  tolua_tonumber(tolua_S,4,0));
  {
   MobClickCppForLua::buy(item,amount,price);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'buy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: use of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_use00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_use00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* item = ((const char*)  tolua_tostring(tolua_S,2,0));
  int amount = ((int)  tolua_tonumber(tolua_S,3,0));
  double price = ((double)  tolua_tonumber(tolua_S,4,0));
  {
   MobClickCppForLua::use(item,amount,price);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'use'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: bonus of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_bonus00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_bonus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double coin = ((double)  tolua_tonumber(tolua_S,2,0));
  int source = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   MobClickCppForLua::bonus(coin,source);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bonus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: bonus of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_bonus01
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_bonus01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* item = ((const char*)  tolua_tostring(tolua_S,2,0));
  int amount = ((int)  tolua_tonumber(tolua_S,3,0));
  double price = ((double)  tolua_tonumber(tolua_S,4,0));
  int source = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   MobClickCppForLua::bonus(item,amount,price,source);
  }
 }
 return 0;
tolua_lerror:
 return tolua_MobClickCppForLua_luabinding_MobClickCppForLua_bonus00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: beginScene of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginScene00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* sceneName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::beginScene(sceneName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'beginScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: endScene of class  MobClickCppForLua */
#ifndef TOLUA_DISABLE_tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endScene00
static int tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MobClickCppForLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* sceneName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   MobClickCppForLua::endScene(sceneName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'endScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_MobClickCppForLua_luabinding_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"MobClickCppForLua","MobClickCppForLua","",NULL);
  tolua_beginmodule(tolua_S,"MobClickCppForLua");
   tolua_function(tolua_S,"setAppVersion",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setAppVersion00);
   tolua_function(tolua_S,"setCrashReportEnabled",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setCrashReportEnabled00);
   tolua_function(tolua_S,"setLogEnabled",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setLogEnabled00);
   tolua_function(tolua_S,"startWithAppkey",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_startWithAppkey00);
   tolua_function(tolua_S,"applicationDidEnterBackground",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_applicationDidEnterBackground00);
   tolua_function(tolua_S,"applicationWillEnterForeground",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_applicationWillEnterForeground00);
   tolua_function(tolua_S,"endAnalytics",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endAnalytics00);
   tolua_function(tolua_S,"event",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_event00);
   tolua_function(tolua_S,"eventCustom",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_eventCustom00);
   tolua_function(tolua_S,"beginEvent",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginEvent00);
   tolua_function(tolua_S,"endEvent",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endEvent00);
   tolua_function(tolua_S,"beginEventWithLabel",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginEventWithLabel00);
   tolua_function(tolua_S,"endEventWithLabel",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endEventWithLabel00);
   tolua_function(tolua_S,"beginEventWithAttributes",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginEventWithAttributes00);
   tolua_function(tolua_S,"endEventWithAttributes",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endEventWithAttributes00);
   tolua_function(tolua_S,"beginLogPageView",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginLogPageView00);
   tolua_function(tolua_S,"endLogPageView",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endLogPageView00);
   tolua_function(tolua_S,"checkUpdate",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_checkUpdate00);
   tolua_function(tolua_S,"checkUpdate",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_checkUpdate01);
   tolua_function(tolua_S,"setUpdateOnlyWifi",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setUpdateOnlyWifi00);
   tolua_function(tolua_S,"updateOnlineConfig",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_updateOnlineConfig00);
   tolua_function(tolua_S,"getConfigParams",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_getConfigParams00);
   tolua_function(tolua_S,"setUserLevel",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setUserLevel00);
   tolua_function(tolua_S,"setUserInfo",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_setUserInfo00);
   tolua_function(tolua_S,"startLevel",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_startLevel00);
   tolua_function(tolua_S,"finishLevel",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_finishLevel00);
   tolua_function(tolua_S,"failLevel",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_failLevel00);
   tolua_function(tolua_S,"pay",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_pay00);
   tolua_function(tolua_S,"pay",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_pay01);
   tolua_function(tolua_S,"buy",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_buy00);
   tolua_function(tolua_S,"use",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_use00);
   tolua_function(tolua_S,"bonus",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_bonus00);
   tolua_function(tolua_S,"bonus",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_bonus01);
   tolua_function(tolua_S,"beginScene",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_beginScene00);
   tolua_function(tolua_S,"endScene",tolua_MobClickCppForLua_luabinding_MobClickCppForLua_endScene00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_MobClickCppForLua_luabinding (lua_State* tolua_S) {
 return tolua_MobClickCppForLua_luabinding_open(tolua_S);
};
#endif

