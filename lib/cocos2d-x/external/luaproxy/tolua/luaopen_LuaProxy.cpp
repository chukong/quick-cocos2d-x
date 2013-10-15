
#include "luaopen_LuaProxy.h"
#include "../LuaProxy.hpp"
#include "tolua_LuaProxy.h"
#include "tolua_CursorTextField.h"
#include "../ui/UIUtil.h"

const char * getFullPathForFile(const char *p){
#if COCOS2D_VERSION < 0x00020100
	return CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(p);
#else
	return CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(p, "");
#endif
}

// isFileExist
static int tolua_LuaProxy_isFileExist(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isstring(l, 1, 0, &err)){
		tolua_error(l,"#ferror in function 'isFileExist'.",&err);
		return 0;
	}
#endif
	const char *f = tolua_tostring(l, 1, NULL);
	tolua_pushboolean(l, f? CCFileUtils::sharedFileUtils()->isFileExist(f) : false);
	return 1;
}

//copyAssetFileToData(const char *src, const char *tar)
static int tolua_LuaProxy_copyAssetFileToData(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isstring(l, 1, 0, &err) || !tolua_isstring(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'copyAssetFileToData'.",&err);
		return 0;
	}
#endif
	CCFileUtils *fu = CCFileUtils::sharedFileUtils();
	unsigned long len = 0;
	std::string src = tolua_tostring(l, 1, NULL),
		tar = tolua_tostring(l, 2, NULL),
		p;
	if(tar.length() == 0){tar = src;}
	src = getFullPathForFile(src.c_str());
#if COCOS2D_VERSION < 0x00020100
	p = fu->getWriteablePath();
#else
	p = fu->getWritablePath();
#endif
	tar.insert(0, p);
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	unsigned char *c = fu->getFileData(src.c_str(), "r", &len);
	if(len > 0){
		FILE *f = fopen(tar.c_str(), "w+");
		len = fwrite(c, len, 1, f) > 0;
		fclose(f);
		delete[] c;
		c = NULL;
	}
#endif
	if(len){tolua_pushstring(l, tar.c_str());}
	return 1;
}
// touchedNodesChild(CCNode *node, int x, int y, const char *toTypeName)
static int tolua_LuaProxy_touchedNodesChild(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCNode", 0, &err) || !tolua_isnumber(l, 2, 0, &err) || !tolua_isnumber(l, 3, 0, &err)
		|| !(tolua_isnoobj(l, 4, &err) || tolua_isstring(l, 4, 0, &err))){
			tolua_error(l, "#ferror in function 'touchedNodesChild'.", &err);
			return 0;
	}
#endif
	CCNode *n = (CCNode *)tolua_tousertype(l, 1, NULL),
		*r = NULL;
	if(n){
		int x = tolua_tonumber(l, 2, 0), y = tolua_tonumber(l, 3, 0);
		CCPoint p = n->convertToNodeSpace(ccp(x, y));
		CCObject *o;
		CCNode *ns;
		CCARRAY_FOREACH(n->getChildren(), o){
			ns = (CCNode *)o;
			if(ns->boundingBox().containsPoint(p)){
				r = ns;
				break;
			}
		}
	}
	if(r){	tolua_pushusertype(l, r, tolua_tostring(l, 4, NULL));}
	return 1;
}
/*
static int tolua_LuaProxy_repeatTexParams(lua_State *l){
	ccTexParams *p = Mtolua_new((ccTexParams)());
	p->minFilter = GL_LINEAR;
	p->magFilter = GL_LINEAR;
	p->wrapS = GL_REPEAT;
	p->wrapT = GL_REPEAT;
	tolua_pushusertype(l, p, "ccTexParams");
	return 1;
}
*/

static int tolua_LuaProxy_fileContentsForPath(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isstring(l, 1, 0, &err)){
		tolua_error(l, "#ferror in function 'fileContentsForPath'.", &err);
		return 0;
	}
#endif
	const char *p = tolua_tostring(l, 1, NULL);
	if(p && strlen(p) > 0){
		unsigned long size = 0;
		const char *fullPath = getFullPathForFile(p);
		unsigned char *d = CCFileUtils::sharedFileUtils()->getFileData(fullPath, "rb", &size);
		tolua_pushstring(l, CCString::createWithData(d, size)->getCString());
	}
	return 1;
}
//######################################## UIUtil ##########################
// Util::createStroke(CCLabelTTF *l, float s, ccColor3B c)
static int tolua_UIUtil_createStroke(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "UIUtil", 0, &err) || !tolua_isusertype(l, 2, "CCLabelTTF", 0, &err) || !tolua_isnumber(l, 3, 0, &err)
		|| !tolua_isusertype(l, 4, "ccColor3B", 0, &err)){
			tolua_error(l, "#ferror in function 'UIUtil.createStroke'.", &err);
			return 0;
	}
#endif
	CCLabelTTF *o = (CCLabelTTF *)tolua_tousertype(l, 2, NULL);
	ccColor3B *c = (ccColor3B *)tolua_tousertype(l, 4, NULL);
	CCRenderTexture *r = UIUtil::createStroke(o, tolua_tonumber(l, 3, 1), c? *c : ccc3(0,0,0));
	tolua_pushusertype(l, r, "CCRenderTexture");
	return 1;
}

static int tolua_UIUtil_shaderForKey(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "UIUtil", 0, &err) || !tolua_isstring(l, 2, 0, &err)
		|| !(tolua_isstring(l, 3, 0, &err) || tolua_isnoobj(l, 3, &err))
		|| !(tolua_isstring(l, 4, 0, &err) || tolua_isnoobj(l, 4, &err))){
			tolua_error(l, "#ferror in function 'UIUtil.shaderForKey'.", &err);
			return 0;
	}
#endif
	const char *k = tolua_tostring(l, 2, NULL);
	if(k && strlen(k) > 0){
		tolua_pushusertype(l, UIUtil::shaderForKey(k, tolua_tostring(l, 3, NULL), tolua_tostring(l, 4, NULL)), "CCGLProgram");
	}
	return 1;
}
// UIUtil::setShaderWithChildren(CCNode *n, CCGLProgram *p = NULL)
static int tolua_UIUtil_setShaderWithChildren(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "UIUtil", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err)
		|| !(tolua_isusertype(l, 3, "CCGLProgram", 0, &err) || tolua_isnoobj(l, 3, &err))){
			tolua_error(l, "#ferror in function 'UIUtil.setShaderWithChildren'.", &err);
			return 0;
	}
#endif
	CCNode *n = (CCNode *)tolua_tousertype(l, 2, NULL);
	if(n){
		UIUtil::setShaderWithChildren(n, (CCGLProgram *)tolua_tousertype(l, 3, NULL));
	}
	return 1;
}
// UIUtil::fixLabel(CCNode *n, float rate, bool withChild, const char *font = NULL)
static int tolua_UIUtil_fixLabel(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "UIUtil", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err) ||
		!tolua_isnumber(l, 3, 0, &err) || !tolua_isboolean(l, 4, false, &err)){
		tolua_error(l,"#ferror in function 'UIUtil.fixLabel'.",&err);
		return 0;
	}
#endif
	CCNode *n = (CCNode *)tolua_tousertype(l, 2, NULL);
	if(n){
		UIUtil::fixLabel(n, tolua_tonumber(l, 3, 1), tolua_toboolean(l, 4, false) > 0, tolua_tostring(l, 5, NULL));
	}
	return 1;
}
// UIUtil::fixParticle(CCNode *n, float dur, float life, bool withChild)
static int tolua_UIUtil_fixParticle(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "UIUtil", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err) ||
		!tolua_isnumber(l, 3, 0, &err) || !tolua_isnumber(l, 4, 0, &err)){
		tolua_error(l,"#ferror in function 'UIUtil.fixParticle'.",&err);
		return 0;
	}
#endif
	CCNode *n = (CCNode *)tolua_tousertype(l, 2, 0);
	if(n){
		UIUtil::fixParticle(n, tolua_tonumber(l, 3, 1), tolua_tonumber(l, 4, 0), tolua_toboolean(l, 5, false) > 0);
	}
	return 1;
}
// UIUtil::fixParticleWithHandler(CCNode *n, LuaEventHandler, bool withChild)
static int tolua_UIUtil_fixParticleWithHandler(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "UIUtil", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err) ||
		!tolua_isusertype(l, 3, "LuaEventHandler", 0, &err)){
		tolua_error(l,"#ferror in function 'UIUtil.fixParticle'.",&err);
		return 0;
	}
#endif
	CCNode *n = (CCNode *)tolua_tousertype(l, 2, 0);
	LuaEventHandler *h = (LuaEventHandler *)tolua_tousertype(l, 3, 0);
	if(n){
		UIUtil::fixParticleWithHandler(n, h, tolua_toboolean(l, 4, false) > 0);
	}
	return 1;
}
// UIUtil::copyNode(CCNode *n)
static int tolua_UIUtil_copyNode(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "UIUtil", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err) ||
		!(tolua_isboolean(l, 3, 0, &err) || tolua_isnoobj(l, 3, &err))){
		tolua_error(l,"#ferror in function 'UIUtil.copyNode'.",&err);
		return 0;
	}
#endif
	CCNode *n = (CCNode *)tolua_tousertype(l, 2, 0);
	CCNode *r = n? UIUtil::copyNode(n, tolua_toboolean(l, 3, 1) == 1) : NULL;
	tolua_pushusertype(l, r, "CCNode");
	return 1;
}
// UIUtil::duplicate(CCNode *node, CCNode *nodeFrom, const char *type)
static int tolua_UIUtil_duplicate(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "UIUtil", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err) ||
		!tolua_isusertype(l, 3, "CCNode", 0, &err) || !tolua_isstring(l, 4, 0, &err)){
		tolua_error(l,"#ferror in function 'UIUtil.duplicate'.",&err);
		return 0;
	}
#endif
	CCNode *n = (CCNode *)tolua_tousertype(l, 2, NULL);
	CCNode *o = (CCNode *)tolua_tousertype(l, 3, NULL);
	const char *t = tolua_tostring(l, 4, NULL);
	if(strcmp(t, "CCScale9Sprite") == 0){		UIUtil::duplicate(dynamic_cast<CCScale9Sprite *>(n), dynamic_cast<CCScale9Sprite *>(o));}
	else if(strcmp(t, "CCSprite") == 0){		UIUtil::duplicate(dynamic_cast<CCSprite *>(n), dynamic_cast<CCSprite *>(o));}
	else if(strcmp(t, "CCLabelBMFont") == 0){	UIUtil::duplicate(dynamic_cast<CCLabelBMFont *>(n), dynamic_cast<CCLabelBMFont *>(o));}
	else if(strcmp(t, "CCLabelTTF") == 0){		UIUtil::duplicate(dynamic_cast<CCLabelTTF *>(n), dynamic_cast<CCLabelTTF *>(o));}
	else if(strcmp(t, "CCParticleSystem") == 0){UIUtil::duplicate(dynamic_cast<CCParticleSystem *>(n), dynamic_cast<CCParticleSystem *>(o));}
	else if(strcmp(t, "CCParticleSystemQuad") == 0){UIUtil::duplicate(dynamic_cast<CCParticleSystemQuad *>(n), dynamic_cast<CCParticleSystemQuad *>(o));}
	else if(strcmp(t, "CCControlButton") == 0){	UIUtil::duplicate(dynamic_cast<CCControlButton *>(n), dynamic_cast<CCControlButton *>(o));}
	else if(strcmp(t, "CCLayer") == 0){			UIUtil::duplicate(dynamic_cast<CCLayer *>(n), dynamic_cast<CCLayer *>(o));}
	else{	UIUtil::duplicate(n, o);}
	return 1;
}
// UIUtil::changeParent(CCNode *n)
static int tolua_UIUtil_changeParent(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "UIUtil", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err) ||
		!tolua_isusertype(l, 3, "CCNode", 0, &err) ||
		!(tolua_isnumber(l, 4, 0, &err) || tolua_isnoobj(l, 4, &err)) ||
		!(tolua_isnumber(l, 5, 0, &err) || tolua_isnoobj(l, 5, &err))){
		tolua_error(l,"#ferror in function 'UIUtil.changeParent'.",&err);
		return 0;
	}
#endif
	CCNode *n = (CCNode *)tolua_tousertype(l, 2, NULL);
	CCNode *np = (CCNode *)tolua_tousertype(l, 3, NULL);
	UIUtil::changeParent(n, np, tolua_tonumber(l, 4, 0), tolua_tonumber(l, 5, -1));
	tolua_pushusertype(l, n, "CCNode");
	return 1;
}
// UIUtil::positionRelative(CCNode *n)
static int tolua_UIUtil_positionRelative(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "UIUtil", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err) ||
		!tolua_isusertype(l, 3, "CCNode", 0, &err)){
		tolua_error(l,"#ferror in function 'UIUtil.positionRelative'.",&err);
		return 0;
	}
#endif
	CCNode *n = (CCNode *)tolua_tousertype(l, 2, NULL);
	CCNode *np = (CCNode *)tolua_tousertype(l, 3, NULL);
	CCPoint p = UIUtil::positionRelative(n, np);
	tolua_pushusertype(l, Mtolua_new((CCPoint)(p)), "CCPoint");
	return 1;
}

//######################################## CCCameraEyeAction ##########################
//CCCameraEyeAction::create(float dur, bool bTo, float x, float y, float z)
static int tolua_CCCameraEyeAction_create(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CCCameraEyeAction", 0, &err) || !tolua_isnumber(l, 2, 0, &err) ||
		!tolua_isboolean(l, 3, 0, &err) || !tolua_isnumber(l, 4, 0, &err) || !tolua_isnumber(l, 5, 0, &err) || !tolua_isnumber(l, 6, 0, &err)){
		tolua_error(l,"#ferror in function 'CCCameraEyeAction.create'.",&err);
		return 0;
	}
#endif
	CCCameraEyeAction *o = CCCameraEyeAction::create(tolua_tonumber(l, 2, 0), tolua_toboolean(l, 3, 0) == 1,
		vertex3(tolua_tonumber(l, 4, 0), tolua_tonumber(l, 5, 0), tolua_tonumber(l, 6, 0)));
	tolua_pushusertype(l, o, "CCCameraEyeAction");
	return 1;
}
//CCCameraEyeAction::setStart(float x, float y, float z)
static int tolua_CCCameraEyeAction_setStart(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCCameraEyeAction", 0, &err) || !tolua_isnumber(l, 2, 0, &err) ||
		!tolua_isnumber(l, 3, 0, &err) || !tolua_isnumber(l, 4, 0, &err)){
		tolua_error(l,"#ferror in function 'CCCameraEyeAction.setStart'.",&err);
		return 0;
	}
#endif
	CCCameraEyeAction *o = (CCCameraEyeAction *)tolua_tousertype(l, 1, NULL);
	if(o){
		o->setStart(vertex3(tolua_tonumber(l, 2, 0), tolua_tonumber(l, 3, 0), tolua_tonumber(l, 4, 0)));
	}
	tolua_pushusertype(l, o, "CCCameraEyeAction");
	return 1;
}

TOLUA_API int luaopen_LuaProxy(lua_State* l){
	tolua_open(l);
	tolua_usertype(l, "LuaProxy");
	tolua_usertype(l, "CCCameraEyeAction");
	tolua_usertype(l, "CursorTextField");
	tolua_usertype(l, "LuaCallFuncInterval");
	tolua_usertype(l, "LuaEventHandler");
	tolua_usertype(l, "LuaTableView");
	tolua_usertype(l, "UIUtil");
	tolua_module(l, NULL, 0);
	tolua_beginmodule(l, NULL);
		tolua_function(l, "copyAssetFileToData", tolua_LuaProxy_copyAssetFileToData);
		tolua_function(l, "touchedNodesChild", tolua_LuaProxy_touchedNodesChild);
//		tolua_function(l, "repeatTexParams", tolua_LuaProxy_repeatTexParams);
		tolua_function(l, "fileContentsForPath", tolua_LuaProxy_fileContentsForPath);
		tolua_function(l, "isFileExist", tolua_LuaProxy_isFileExist);
		tolua_constant(l, "GL_LINEAR", GL_LINEAR);
		tolua_constant(l, "GL_REPEAT", GL_REPEAT);
		tolua_constant(l, "GL_NEAREST", GL_NEAREST);
		tolua_constant(l, "GL_CLAMP_TO_EDGE", GL_CLAMP_TO_EDGE);
		tolua_constant(l, "GL_TEXTURE", GL_TEXTURE);
		tolua_constant(l, "CC_TARGET_PLATFORM", CC_TARGET_PLATFORM);
// Not availiable for android
//		tolua_constant(l, "GL_CLAMP", GL_CLAMP);
//		tolua_constant(l, "GL_TEXTURE_WIDTH", GL_TEXTURE_WIDTH);
		tolua_constant(l, "CC_PLATFORM_IOS", CC_PLATFORM_IOS);
		tolua_constant(l, "CC_PLATFORM_ANDROID", CC_PLATFORM_ANDROID);
		tolua_constant(l, "CC_PLATFORM_WIN32", CC_PLATFORM_WIN32);
		tolua_constant(l, "CC_PLATFORM_MAC", CC_PLATFORM_MAC);
		tolua_constant(l, "CC_PLATFORM_LINUX", CC_PLATFORM_LINUX);
		tolua_constant(l, "CC_PLATFORM_UNKNOW", CC_PLATFORM_UNKNOWN);
		tolua_cclass(l,"LuaProxy","LuaProxy","CCLayer",NULL);
		tolua_beginmodule(l,"LuaProxy");
			tolua_function(l, "create", tolua_LuaProxy_create);
			tolua_function(l, "releaseMembers", tolua_LuaProxy_releaseMembers);
			tolua_function(l, "getMemberName", tolua_LuaProxy_getMemberName);
			tolua_function(l, "getMemberVariables", tolua_LuaProxy_getMemberVariables);
			tolua_function(l, "getNode", tolua_LuaProxy_getNode);
#ifdef LUAPROXY_CCEDITBOX_ENABLED
			tolua_function(l, "handleEditEvent", tolua_LuaProxy_handleEditEvent);
#endif
			// Kept for compatible
			tolua_function(l, "handleButtonEvent", tolua_LuaProxy_handleControlEvent);
			tolua_function(l, "handleControlEvent", tolua_LuaProxy_handleControlEvent);
			tolua_function(l, "handleKeypad", tolua_LuaProxy_handleKeypad);
			tolua_function(l, "handleMenuEvent", tolua_LuaProxy_handleMenuEvent);
			tolua_function(l, "handleAnimationComplate", tolua_LuaProxy_handleAnimationComplate);
			tolua_function(l, "handleSelector", tolua_LuaProxy_handleSelector);
			tolua_function(l, "removeHandler", tolua_LuaProxy_removeHandler);
			tolua_function(l, "removeFunction", tolua_LuaProxy_removeFunction);
			tolua_function(l, "removeKeypadHandler", tolua_LuaProxy_removeKeypadHandler);
			tolua_function(l, "getSelectorHandler", tolua_LuaProxy_getSelectorHandler);
			tolua_function(l, "setSelectorHandler", tolua_LuaProxy_setSelectorHandler);
			tolua_function(l, "deliverChildren", tolua_LuaProxy_deliverChildren);
			tolua_function(l, "readCCBFromFile", tolua_LuaProxy_readCCBFromFile);
		tolua_endmodule(l);
		tolua_cclass(l, "CCCameraEyeAction", "CCCameraEyeAction", "CCActionInterval", NULL);
		tolua_beginmodule(l, "CCCameraEyeAction");
			tolua_function(l, "create", tolua_CCCameraEyeAction_create);
			tolua_function(l, "setStart", tolua_CCCameraEyeAction_setStart);
		tolua_endmodule(l);
		tolua_cclass(l, "CursorTextField", "CursorTextField", "CCTextFieldTTF", NULL);
		tolua_beginmodule(l, "CursorTextField");
			tolua_function(l, "create", tolua_CursorTextField_create);
			tolua_function(l, "createWithPlaceHolder", tolua_CursorTextField_createWithPlaceHolder);
			tolua_function(l, "setColor", tolua_CursorTextField_setColor);
			tolua_function(l, "getDesignedSize", tolua_CursorTextField_getDesignedSize);
			tolua_function(l, "setDesignedSize", tolua_CursorTextField_setDesignedSize);
			tolua_function(l, "getMaxLength", tolua_CursorTextField_getMaxLength);
			tolua_function(l, "setMaxLength", tolua_CursorTextField_setMaxLength);
			tolua_function(l, "isPassword", tolua_CursorTextField_isPassword);
			tolua_function(l, "setPassword", tolua_CursorTextField_setPassword);
			tolua_function(l, "getRect", tolua_CursorTextField_getRect);
			tolua_function(l, "setString", tolua_CursorTextField_setString);
		tolua_endmodule(l);
		tolua_constant(l, "kLuaEventKeyBack", (int)LuaEventHandler::Events::KeyBack);
		tolua_constant(l, "kLuaEventKeyMenu", (int)LuaEventHandler::Events::KeyMenu);
		tolua_constant(l, "kLuaEventAppEnterBackground", (int)LuaEventHandler::Events::AppEnterBackground);
		tolua_constant(l, "kLuaEventAppEnterForeground", (int)LuaEventHandler::Events::AppEnterForeground);
		tolua_cclass(l, "LuaCallFuncInterval", "LuaCallFuncInterval", "CCActionInterval", NULL);
		tolua_beginmodule(l, "LuaCallFuncInterval");
			tolua_function(l, "create", tolua_LuaCallFuncInterval_create);
		tolua_endmodule(l);
		tolua_cclass(l, "LuaEventHandler", "LuaEventHandler", "CCLayer", NULL);
		tolua_beginmodule(l, "LuaEventHandler");
			tolua_function(l, "create", tolua_LuaEventHandler_create);
			tolua_function(l, "createAppHandler", tolua_LuaEventHandler_createAppHandler);
		tolua_endmodule(l);
		tolua_cclass(l, "LuaTableView", "LuaTableView", "CCTableView", NULL);
		tolua_beginmodule(l, "LuaTableView");
			tolua_function(l, "createWithHandler", tolua_LuaTableView_createWithHandler);
			tolua_function(l, "reloadData", tolua_LuaTableView_reloadData);
			tolua_function(l, "setScrollNode", tolua_LuaTableView_setScrollNode);
			tolua_function(l, "setScrollBar", tolua_LuaTableView_setScrollBar);
			tolua_function(l, "setScrollTrack", tolua_LuaTableView_setScrollTrack);
			tolua_function(l, "setScrollOffset", tolua_LuaTableView_setScrollOffset);
		tolua_endmodule(l);
		tolua_cclass(l, "UIUtil", "UIUtil", "", NULL);
		tolua_beginmodule(l, "UIUtil");
			tolua_function(l, "createStroke", tolua_UIUtil_createStroke);
			tolua_function(l, "shaderForKey", tolua_UIUtil_shaderForKey);
			tolua_function(l, "setShaderWithChildren", tolua_UIUtil_setShaderWithChildren);
			tolua_function(l, "fixLabel", tolua_UIUtil_fixLabel);
			tolua_function(l, "fixParticle", tolua_UIUtil_fixParticle);
			tolua_function(l, "fixParticleWithHandler", tolua_UIUtil_fixParticleWithHandler);
			tolua_function(l, "copyNode", tolua_UIUtil_copyNode);
			tolua_function(l, "duplicate", tolua_UIUtil_duplicate);
			tolua_function(l, "changeParent", tolua_UIUtil_changeParent);
			tolua_function(l, "positionRelative", tolua_UIUtil_positionRelative);
		tolua_endmodule(l);
	tolua_endmodule(l);
	return 1;
}
