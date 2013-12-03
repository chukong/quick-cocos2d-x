/****************************************************************************
Copyright (c) 2013 Shawn Clovie

http://mcspot.com

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

#ifndef __LUAPROXY_H__
#define __LUAPROXY_H__

#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "LuaEventHandler.hpp"

USING_NS_CC;
USING_NS_CC_EXT;

class LuaProxy : public CCLayer, public CCBScriptOwnerProtocol, public CCBSelectorResolver, public CCBMemberVariableAssigner{
protected:
	lua_State *_lua;
	CCDictionary *_memVars;
	CCArray *_handlers;
	LuaEventHandler *_selectorHandler;
public:
	LuaProxy() : _selectorHandler(NULL){
		_memVars = CCDictionary::create();
		_memVars->retain();
		_handlers = CCArray::create();
		_handlers->retain();
	}
	~LuaProxy(){
		CC_SAFE_RELEASE(_memVars);
		CC_SAFE_RELEASE(_handlers);
		CC_SAFE_RELEASE(_selectorHandler);
	}
	
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LuaProxy, create);
	void releaseMembers(){
		_memVars->removeAllObjects();
		_handlers->removeAllObjects();
	}
	LuaProxy * initProxy(lua_State *l){
		_lua = l;
		return this;
	}

	//interface methods
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * o, const char * sel){
		return menu_selector(LuaProxy::menuItemCallback);
	}

	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName){
		return NULL;
	}

	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * o, const char * sel){
		return cccontrol_selector(LuaProxy::controlCallback);
	}

	// o:self, v:var, n:node
	virtual bool onAssignCCBMemberVariable(CCObject * o, const char * var, CCNode * n){
		if(n && var && strlen(var) > 0){
			if(_memVars->objectForKey(var) != NULL){
				CCLog("LuaProxy.onAssignCCBMemberVariable() node name %s was exists.\n", var);
			}
			_memVars->setObject(n, var);
		}else{
			CCLog("LuaProxy.onAssignCCBMemberVariable() node (%s:%p) didn't saved.\n", var, n);
		}
		return true;
	}

	virtual bool onAssignCCBCustomProperty(CCObject* o, const char* var, CCBValue* v) {
		return false;
	}

	virtual void onNodeLoaded(CCNode * n, CCNodeLoader * l){
	}

	virtual CCBSelectorResolver * createNew(){
		LuaProxy *p = new LuaProxy();
		return dynamic_cast<CCBSelectorResolver *>(p);
	}

	//create LuaEventHandler contains a lua function(handler), for handler control's event

	void handleEvent(CCControl *n, const int handler, bool multiTouches = false,
#if COCOS2D_VERSION < 0x00030000
		CCControlEvent e = CCControlEventTouchUpInside){
#else
		Control::EventType e = Control::EventType::TOUCH_UP_INSIDE){
#endif
		LuaEventHandler *h = getHandler(handler);
		if(!h){
			h = addHandler(handler, multiTouches)
				->setTypename("CCControlButton");
		}
		n->addTargetWithActionForControlEvents(h, cccontrol_selector(LuaEventHandler::controlAction), e);
	}

#ifdef LUAPROXY_CCEDITBOX_ENABLED
	void handleEvent(EditBox *n, const int handler){
		LuaEventHandler *h = addHandler(handler, false)
			->setTypename("CCEditBox");
		n->setDelegate(h);
	}
#endif
	void handleEvent(CCBAnimationManager *m, const int handler){
		addHandler(handler)->handle(m);
	}

	void handleKeypad(const int handler){
		LuaEventHandler::sharedDirector()->getKeypadDispatcher()->addDelegate(addHandler(handler));
	}

	LuaEventHandler * addHandler(const int handler, bool multiTouches = false){
		LuaEventHandler *h = LuaEventHandler::create(_lua)
			->handle(handler, multiTouches, 0, false);
		_handlers->addObject(h);
		return h;
	}

	LuaEventHandler * getHandler(const int handler){
		CCObject *o;
		LuaEventHandler *h;
		CCARRAY_FOREACH(_handlers, o){
			h = (LuaEventHandler *)o;
			if(h->getHandler() == handler){
				return h;
			}
		}
		return NULL;
	}
        
    void nodeToTypeForLua(lua_State *l, CCObject *o, const char *t){
        if(strcmp("CCSprite", t) == 0)				tolua_pushusertype(l, dynamic_cast<CCSprite *>(o), t);
        else if(strcmp("CCControlButton", t) == 0)	tolua_pushusertype(l, dynamic_cast<CCControlButton *>(o), t);
        else if(strcmp("CCLayer", t) == 0)			tolua_pushusertype(l, dynamic_cast<CCLayer *>(o), t);
        else if(strcmp("CCLayerColor", t) == 0)		tolua_pushusertype(l, dynamic_cast<CCLayerColor *>(o), t);
        else if(strcmp("CCLayerGradient", t) == 0)	tolua_pushusertype(l, dynamic_cast<CCLayerGradient *>(o), t);
        else if(strcmp("CCScrollView", t) == 0)		tolua_pushusertype(l, dynamic_cast<CCScrollView *>(o), t);
        else if(strcmp("CCScale9Sprite", t) == 0)	tolua_pushusertype(l, dynamic_cast<CCScale9Sprite *>(o), t);
        else if(strcmp("CCLabelTTF", t) == 0)		tolua_pushusertype(l, dynamic_cast<CCLabelTTF *>(o), t);
        else if(strcmp("CCLabelBMFont", t) == 0)	tolua_pushusertype(l, dynamic_cast<CCLabelBMFont *>(o), t);
        else if(strcmp("CCMenu", t) == 0)			tolua_pushusertype(l, dynamic_cast<CCMenu *>(o), t);
        else if(strcmp("CCMenuItemImage", t) == 0)	tolua_pushusertype(l, dynamic_cast<CCMenuItemImage *>(o), t);
        else if(strcmp("CCString", t) == 0)			tolua_pushusertype(l, dynamic_cast<CCString *>(o), t);
        else if(strcmp("CCParticleSystemQuad", t) == 0)tolua_pushusertype(l, dynamic_cast<CCParticleSystemQuad *>(o), t);
        else if(strcmp("CCBFile", t) == 0)			tolua_pushusertype(l, dynamic_cast<CCBFile *>(o), t);
        else if(strcmp("CCBAnimationManager", t) == 0)			tolua_pushusertype(l, dynamic_cast<CCBAnimationManager *>(o), t);
        else tolua_pushusertype(l, dynamic_cast<CCNode *>(o), "CCNode");
    }

	// Remove LuaEventHandler for lua function handler, and return it
	LuaEventHandler * removeHandler(LuaEventHandler *h){
		if(h){
			_handlers->removeObject(h);
		}
		return h;
	}
	
	LuaEventHandler * removeFunction(int handler){
		return removeHandler(getHandler(handler));
	}

	LuaEventHandler * removeKeypadHandler(int handler){
		LuaEventHandler *h = removeFunction(handler);
		if(h){
			LuaEventHandler::sharedDirector()->getKeypadDispatcher()->removeDelegate(h);
		}
		return h;
	}
	inline LuaEventHandler * getSelectorHandler(){
		return _selectorHandler;
	}
	
	void setSelectorHandler(LuaEventHandler *h){
		CC_SAFE_RELEASE(_selectorHandler);
		_selectorHandler = h;
		CC_SAFE_RETAIN(h);
	}
	
	LuaEventHandler * handleSelector(const int handler){
		LuaEventHandler *h = NULL;
		if(handler > 0){
			h = LuaEventHandler::create(_lua)->handle(handler);
		}
		setSelectorHandler(h);
		return h;
	}
	
	void menuItemCallback(CCObject *pSender){
		if(_selectorHandler){
			_selectorHandler->action(pSender);
		}
	}
	
	void controlCallback(CCObject *pSender,
#if COCOS2D_VERSION >= 0x00030000
		Control::EventType e){
#else
		CCControlEvent e){
#endif
		if(_selectorHandler){
			_selectorHandler->controlAction(pSender, e);
		}
	}
	
	CCDictionary *getMemberVariables(){
		return _memVars;
	}
	const char * getMemberName(CCObject *n){
		CCDictElement *e;
		CCDICT_FOREACH(_memVars, e){
			if(e->getObject() == n){
				return e->getStrKey();
			}
		}
		return "";
	}
	// Get member variable in node for key
	CCNode * getNode(const char *n){
		return (CCNode *)_memVars->objectForKey(n);
	}
	// Read ccbi file (f). 2nd argument not use yet.
	CCNode * readCCBFromFile(const char *f){
		//assert(f && strlen(f) > 0, "File name must not be null or empty string.");
		CCBReader * reader = new CCBReader(
#if COCOS2D_VERSION >= 0x00030000
			NodeLoaderLibrary::getInstance());
#else
			CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
#endif
		CCNode *node = reader->readNodeGraphFromFile(f, this);
		CCBAnimationManager *m = reader->getAnimationManager();
		reader->autorelease();
		node->setUserObject(m);
		return node;
	}
//	void changeResolutionScale(CCNode *n, CCBAnimationManager *m, float resolutionScale);
};
#endif // __LUAPROXY_H__