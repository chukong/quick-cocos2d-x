#ifndef __TOLUA_LuaProxy__
#define __TOLUA_LuaProxy__

#include "../LuaProxy.hpp"
#include "../LuaTableView.hpp"
#include "tolua_util.h"

//######################################## LuaProxy ##########################
//LuaProxy::create
static int tolua_LuaProxy_create(lua_State *l){
	LuaProxy *p = LuaProxy::create();
	p->initProxy(l);
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
//LuaProxy::releaseMembers
static int tolua_LuaProxy_releaseMembers(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.releaseMembers'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	if(p){
		p->releaseMembers();
		tolua_pushusertype(l, p, "LuaProxy");
	}
	return 1;
}
//LuaProxy::getMemberName
static int tolua_LuaProxy_getMemberName(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !tolua_isusertype(l, 2, "CCObject", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.getMemberName'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	CCObject *n = (CCObject *)tolua_tousertype(l, 2, NULL);
	tolua_pushstring(l, p && n? p->getMemberName(n) : "");
	return 1;
}
//LuaProxy::getMemberVariables
static int tolua_LuaProxy_getMemberVariables(lua_State *l){
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	tolua_pushusertype(l, p->getMemberVariables(), "CCDictionary");
	return 1;
}
//LuaProxy::getNode
static int tolua_LuaProxy_getNode(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !tolua_isstring(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.getNode'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	if(p)tolua_pushusertype(l, p->getNode(tolua_tostring(l, 2, NULL)), "CCNode");
	return 1;
}
//LuaProxy::handleButtonEvent
static int tolua_LuaProxy_handleControlEvent(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !tolua_isusertype(l, 2, "CCControl", 0, &err) ||
		!toluafix_isfunction(l, 3, "LUA_FUNCTION", 0, &err) || !tolua_isnumber(l, 4, 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.handleButtonEvent'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	CCControl *n = (CCControl *)tolua_tousertype(l, 2, NULL);
	CCControlEvent e = tolua_tonumber(l, 4, 0);
	if(p && n){
		p->handleEvent(n, toluafix_ref_function(l, 3, 0), false, e > 0? e : CCControlEventTouchUpInside);}
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
//LuaProxy::handleKeypad
static int tolua_LuaProxy_handleKeypad(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !toluafix_isfunction(l, 2, "LUA_FUNCTION", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.handleKeypad'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	if(p){p->handleKeypad(toluafix_ref_function(l, 2, 0));}
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
//LuaProxy::handleMenuEvent
static int tolua_LuaProxy_handleMenuEvent(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !tolua_isusertype(l, 2, "CCObject", 0, &err) ||
		!toluafix_isfunction(l, 3, "LUA_FUNCTION", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.handleMenuEvent'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	CCMenuItem *i = dynamic_cast<CCMenuItem *>((CCObject *)tolua_tousertype(l, 2, NULL));
	if(i){i->registerScriptTapHandler(toluafix_ref_function(l, 3, 0));}
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
//LuaProxy::handleEditEvent
static int tolua_LuaProxy_handleEditEvent(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !tolua_isusertype(l, 2, "CCEditBox", 0, &err) ||
		!toluafix_isfunction(l, 3, "LUA_FUNCTION", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.handleEditEvent'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	CCEditBox *n = (CCEditBox *)tolua_tousertype(l, 2, NULL);
	if(p && n){p->handleEvent(n, toluafix_ref_function(l, 3, 0));}
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
//LuaProxy::handleAnimationComplate
static int tolua_LuaProxy_handleAnimationComplate(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !tolua_isusertype(l, 2, "CCBAnimationManager", 0, &err) ||
		!toluafix_isfunction(l, 3, "LUA_FUNCTION", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.handleAnimationComplate'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 2, NULL);
	if(p && m){p->handleEvent(m, toluafix_ref_function(l, 3, 0));}
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
//LuaProxy::handleSelector
static int tolua_LuaProxy_handleSelector(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !toluafix_isfunction(l, 2, "LUA_FUNCTION", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.handleSelector'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	if(p){p->handleSelector(toluafix_ref_function(l, 2, 0));}
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
//LuaProxy::removeFunction
static int tolua_LuaProxy_removeFunction(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !toluafix_isfunction(l, 2, "LUA_FUNCTION", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.removeFunction'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	if(p){p->removeFunction(toluafix_ref_function(l, 3, 0));}
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
//LuaProxy::removeHandler
static int tolua_LuaProxy_removeHandler(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !tolua_isusertype(l, 2, "LuaEventHandler", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.removeHandler'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	LuaEventHandler *h = (LuaEventHandler *)tolua_tousertype(l, 2, NULL);
	if(p && h){p->removeHandler(h);}
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
//LuaProxy::removeKeypadHandler
static int tolua_LuaProxy_removeKeypadHandler(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !toluafix_isfunction(l, 2, "LUA_FUNCTION", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.removeKeypadHandler'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	if(p){p->removeKeypadHandler(toluafix_ref_function(l, 3, 0));}
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
//LuaProxy::getSelectorHandler
static int tolua_LuaProxy_getSelectorHandler(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.getSelectorHandler'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	if(p){tolua_pushusertype(l, p->getSelectorHandler(), "LuaEventHandler");}
	return 1;
}
//LuaProxy::setSelectorHandler
static int tolua_LuaProxy_setSelectorHandler(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !tolua_isusertype(l, 2, "LuaEventHandler", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.setSelectorHandler'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	if(p){p->setSelectorHandler((LuaEventHandler *)tolua_tousertype(l, 2, NULL));}
	tolua_pushusertype(l, p, "LuaProxy");
	return 1;
}
// Remove every children in "nf", and add them to "nt"
//LuaProxy::deliverChildren(CCNode *nf, CCNode *nt)
static int tolua_LuaProxy_deliverChildren(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 2, "CCNode", 0, &err) || !tolua_isusertype(l, 3, "CCNode", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.deliverChildren'.",&err);
		return 0;
	}
#endif
	CCNode *nf = (CCNode *)tolua_tousertype(l, 2, NULL);
	CCNode *nt = (CCNode *)tolua_tousertype(l, 3, NULL);
	if(nf && nt){
		CCObject *o;
		CCNode *n;
		CCARRAY_FOREACH(nf->getChildren(), o){
			n = (CCNode *)o;
			n->removeFromParentAndCleanup(true);
			nt->addChild(n);
		}
	}
	return 1;
}
//LuaProxy::readCCBFromFile(const char *f)
static int tolua_LuaProxy_readCCBFromFile(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaProxy", 0, &err) || !tolua_isstring(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'LuaProxy.readCCBFromFile'.",&err);
		return 0;
	}
#endif
	LuaProxy *p = (LuaProxy *)tolua_tousertype(l, 1, NULL);
	const char *f = tolua_tostring(l, 2, 0);
	if(p){
		tolua_pushusertype(l, p->readCCBFromFile(f), "CCNode");
	}
	return 1;
}

//######################################## LuaCallFuncInterval ##########################
//LuaCallFuncInterval::create(LUA_FUNCTION hnd = 0)
static int tolua_LuaCallFuncInterval_create(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "LuaCallFuncInterval", 0, &err) || !tolua_isnumber(l, 2, 0, &err) ||
		!toluafix_isfunction(l, 3, "LUA_FUNCTION", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaCallFuncInterval.create'.",&err);
		return 0;
	}
#endif
	LuaCallFuncInterval *h = LuaCallFuncInterval::create(tolua_tonumber(l, 2, 0), toluafix_ref_function(l, 3, 0));
	tolua_pushusertype(l, h, "LuaCallFuncInterval");
	return 1;
}
//######################################## LuaEventHandler ##########################
//LuaEventHandler::create(LUA_FUNCTION hnd = 0)
static int tolua_LuaEventHandler_create(lua_State *l){
	LuaEventHandler *h = LuaEventHandler::create(l);
	int hnd = toluafix_ref_function(l, 2, 0);
	if(hnd > 0){ h->handle(hnd);}
	tolua_pushusertype(l, h, "LuaEventHandler");
	return 1;
}
//LuaEventHandler::createAppHandler(LUA_FUNCTION hnd)
static int tolua_LuaEventHandler_createAppHandler(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "LuaEventHandler", 0, &err) || !toluafix_isfunction(l, 2, "LUA_FUNCTION", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaEventHandler.createAppHandler'.",&err);
		return 0;
	}
#endif
	int hnd = toluafix_ref_function(l, 2, 0);
	LuaEventHandler *h = LuaEventHandler::createAppHandler(l, hnd);
	tolua_pushusertype(l, h, "LuaEventHandler");
	return 1;
}

//######################################## LuaTableView ##########################
//LuaTableView::createWithHandler(LuaEventHandler *h, CCSize *s, CCNode *c = NULL)
static int tolua_LuaTableView_createWithHandler(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "LuaTableView", 0, &err) || !tolua_isusertype(l, 2, "LuaEventHandler", 0, &err) ||
		!tolua_isusertype(l, 3, "CCSize", 0, &err) ||
		!(tolua_isusertype(l, 4, "CCNode", 0, &err) || tolua_isnoobj(l, 4, &err))){
		tolua_error(l,"#ferror in function 'LuaTableView.createWithHandler'.",&err);
		return 0;
	}
#endif
	LuaEventHandler *h = (LuaEventHandler *)tolua_tousertype(l, 2, NULL);
	CCSize *s = (CCSize *)tolua_tousertype(l, 3, NULL);
	CCNode *c = (CCNode *)tolua_tousertype(l, 4, NULL);
	LuaTableView *t = LuaTableView::createWithHandler(h, s? *s : CCSizeZero, c);
	tolua_pushusertype(l, t, "LuaTableView");
	return 1;
}
//LuaTableView::reloadData()
static int tolua_LuaTableView_reloadData(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaTableView", 0, &err)){
		tolua_error(l,"#ferror in function 'LuaTableView.reloadData'.",&err);
		return 0;
	}
#endif
	LuaTableView *o = (LuaTableView *)tolua_tousertype(l, 1, NULL);
	if(o){
		o->reloadData();
		tolua_pushusertype(l, o, "LuaTableView");
	}
	return 1;
}
//LuaTableView::setScrollNode(CCNode *n)
static int tolua_LuaTableView_setScrollNode(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaTableView", 0, &err) ||
		!(tolua_isusertype(l, 2, "CCNode", 0, &err) || tolua_isnoobj(l, 2, &err))){
		tolua_error(l,"#ferror in function 'LuaTableView.setScrollNode'.",&err);
		return 0;
	}
#endif
	LuaTableView *o = (LuaTableView *)tolua_tousertype(l, 1, NULL);
	if(o){
		o->setScrollNode((CCNode *)tolua_tousertype(l, 2, NULL));
		tolua_pushusertype(l, o, "LuaTableView");
	}
	return 1;
}
//LuaTableView::setScrollBar(CCScale9Sprite *s)
static int tolua_LuaTableView_setScrollBar(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaTableView", 0, &err) ||
		!(tolua_isusertype(l, 2, "CCScale9Sprite", 0, &err) || tolua_isnoobj(l, 2, &err))){
		tolua_error(l,"#ferror in function 'LuaTableView.setScrollBar'.",&err);
		return 0;
	}
#endif
	LuaTableView *o = (LuaTableView *)tolua_tousertype(l, 1, NULL);
	if(o){
		o->setScrollBar((CCScale9Sprite *)tolua_tousertype(l, 2, NULL));
		tolua_pushusertype(l, o, "LuaTableView");
	}
	return 1;
}
//LuaTableView::setScrollTrack(CCScale9Sprite *s)
static int tolua_LuaTableView_setScrollTrack(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaTableView", 0, &err) ||
		!(tolua_isusertype(l, 2, "CCScale9Sprite", 0, &err) || tolua_isnoobj(l, 2, &err))){
		tolua_error(l,"#ferror in function 'LuaTableView.setScrollTrack'.",&err);
		return 0;
	}
#endif
	LuaTableView *o = (LuaTableView *)tolua_tousertype(l, 1, NULL);
	if(o){
		o->setScrollTrack((CCScale9Sprite *)tolua_tousertype(l, 2, NULL));
		tolua_pushusertype(l, o, "LuaTableView");
	}
	return 1;
}
//LuaTableView::setScrollOffset(CCScale9Sprite *h, CCScale9Sprite *v)
static int tolua_LuaTableView_setScrollOffset(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "LuaTableView", 0, &err) || !tolua_isnumber(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'LuaTableView.setScrollOffset'.",&err);
		return 0;
	}
#endif
	LuaTableView *o = (LuaTableView *)tolua_tousertype(l, 1, NULL);
	if(o){
		o->setScrollOffset(tolua_tonumber(l, 2, 0));
		tolua_pushusertype(l, o, "LuaTableView");
	}
	return 1;
}

#endif //__TOLUA_LuaProxy__
