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

#ifndef __CCBPROXY_H_
#define __CCBPROXY_H_

#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "LuaEventHandler.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCBProxy : public CCLayer, public CCBScriptOwnerProtocol, public CCBSelectorResolver, public CCBMemberVariableAssigner{
protected:
	lua_State *_lua;
	CCDictionary *_memVars;
	CCArray *_handlers;
	LuaEventHandler *_selectorHandler;
public:
	CCBProxy();
	~CCBProxy();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCBProxy, create);
	void releaseMembers();
	CCBProxy * initProxy(lua_State *l);

	//interface methods
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
	virtual bool onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode);
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);

	//create LuaEventHandler contains a lua function(handler), for handler control's event
	void handleEvent(CCControl *n, const int handler, bool multiTouches = false, CCControlEvent e = CCControlEventTouchUpInside);
#ifdef LUAPROXY_CCEDITBOX_ENABLED
	void handleEvent(CCEditBox *n, const int handler);
#endif
	void handleEvent(CCBAnimationManager *m, const int handler);
	void handleKeypad(const int handler);
	LuaEventHandler * addHandler(const int handler, bool multiTouches = false);
	LuaEventHandler * getHandler(const int handler);
	// Remove LuaEventHandler for lua function handler, and return it
	LuaEventHandler * removeHandler(LuaEventHandler *h);
	LuaEventHandler * removeFunction(int handler);
	LuaEventHandler * removeKeypadHandler(int handler);

	inline LuaEventHandler * getSelectorHandler(){ return _selectorHandler;}
	void setSelectorHandler(LuaEventHandler *h);
	LuaEventHandler * handleSelector(const int handler);
	
	virtual CCBSelectorResolver * createNew();
	void menuItemCallback(CCObject *pSender);
	void controlCallback(CCObject *pSender, CCControlEvent event);
	void setCallbackProperty(const char *prop);
	
	CCDictionary *getMemberVariables();
	const char * getMemberName(CCObject *n);
	// Get member variable in node for key
	CCNode * getNode(const char *n);
	// Dynamic cast (o) to type (t), and push it by usertype into lua state.
	static void nodeToTypeForLua(lua_State *l, CCObject *o, const char *t);
	// Read ccbi file (f). 2nd argument not use yet.
	CCNode * readCCBFromFile(const char *f);
//	void changeResolutionScale(CCNode *n, CCBAnimationManager *m, float resolutionScale);
};
#endif // __CCBPROXY_H_