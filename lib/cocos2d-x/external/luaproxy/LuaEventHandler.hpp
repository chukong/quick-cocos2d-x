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

#ifndef __LUAEVENTHANDLER_H_
#define __LUAEVENTHANDLER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "tolua++.h"
#include "tolua_fix.h"
#include "CCLuaEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

#if COCOS2D_VERSION >= 0x00030000
typedef LuaEngine CCLuaEngine;
typedef LuaStack CCLuaStack;
typedef DictElement CCDictElement;
#endif

class LuaEventHandler : public CCLayer,
public CCTableViewDelegate, public CCTableViewDataSource
#ifdef LUAPROXY_CCEDITBOX_ENABLED
,public EditBoxDelegate
#endif
{
protected:
	lua_State *_lua;
	std::string _typename;
	int _handler;
	int _handlerRef;
	bool _multiTouches;
	int _priority;
	bool _swallows;
public:
	enum class Events{
		KeyBack = 1,
		KeyMenu = 2,
		AppEnterBackground = 4,
		AppEnterForeground = 8
	};
	static LuaEventHandler * app;
	~LuaEventHandler(){
		unhandle();
	}
	static LuaEventHandler * createAppHandler(lua_State *l, int handler){
		if(!app){
			app = new LuaEventHandler();
		}
		app->_lua = l;
		app->handle(handler);
		return app;
	}
	static CCLuaEngine * engine(){
#if COCOS2D_VERSION >= 0x00030000
		return LuaEngine::getInstance();
#else
		return CCLuaEngine::defaultEngine();
#endif
	}
	static CCLuaStack * luaStack(){
		return engine()->getLuaStack();
	}

	static LuaEventHandler * create(lua_State *l = NULL){
		LuaEventHandler *h = new LuaEventHandler();
		h->_lua = l == NULL? luaStack()->getLuaState() : l;
		h->autorelease();
		return h;
	}
	static void pushInt(int v){ luaStack()->pushInt(v);}
	static void pushFloat(float v){ luaStack()->pushFloat(v);}
	static void pushBoolean(bool v){ luaStack()->pushBoolean(v);}
	static void pushString(const char *v){ luaStack()->pushString(v);}
	static void pushCCObject(CCObject *v, const char *t){
#if COCOS2D_VERSION >= 0x00030000
		luaStack()->pushObject(v, t);
#else
		luaStack()->pushCCObject(v, t);
#endif
	}
	static void pushUsertype(void *v, const char *t){
		tolua_pushusertype(luaStack()->getLuaState(), v, t);
	}
	static void pushNil(){ luaStack()->pushNil();}
	static int runFunctionHandler(int hnd, int argNum, bool retInt = false){
		int r = 0;
		if(retInt){	r = runLuaFunction(hnd, argNum, true);}
		else{		luaStack()->executeFunctionByHandler(hnd, argNum);}
		return r;
	}
	static void runString(const char *s){
		luaL_dostring(luaStack()->getLuaState(), s);
	}
	static bool pushLuaFunction(int nHandler){
		lua_State *l = luaStack()->getLuaState();
		toluafix_get_function_by_refid(l, nHandler);          /* stack: ... func */
		if(!lua_isfunction(l, -1)){
			CCLog("[LUA ERROR] function refid '%d' does not reference a Lua function", nHandler);
			lua_pop(l, 1);
			return false;
		}
		return true;
	}
	// Run lua function but do not get return value.
	// If (retInt) is true, try to return int and bool value, and auto finish function call.
	// Else, should manual call finishRunLuaFunction()
	static int runLuaFunction(int h, int numArgs, bool retInt = false){
		lua_State *l = luaStack()->getLuaState();
		if(pushLuaFunction(h)){                                         /* stack: ... arg1 arg2 ... func */
			if(numArgs > 0){
				lua_insert(l, -(numArgs + 1));                        /* stack: ... func arg1 arg2 ... */
			}
			int traceback = 0;
			lua_getglobal(l, "__G__TRACKBACK__");                     /* stack: ... func arg1 arg2 ... G */
			if (!lua_isfunction(l, -1)){
				lua_pop(l, 1);                                        /* stack: ... func arg1 arg2 ... */
			}else{
				traceback = -(numArgs + 2);
				lua_insert(l, traceback);                             /* stack: ... G func arg1 arg2 ... */
			}
			int error = 0;
			error = lua_pcall(l, numArgs, 1, traceback);              /* stack: ... ret */
			if (error){
				if (traceback == 0){
					CCLog("[LUA ERROR] %s", lua_tostring(l, - 1));    /* stack: ... error */
					lua_pop(l, 1); // remove error message from stack
				}
				return 0;
			}
			// get return value
			int ret = 1;
			if(retInt){
				if (lua_isnumber(l, -1)){
					ret = (int)lua_tointeger(l, -1);
				}else if (lua_isboolean(l, -1)){
					ret = lua_toboolean(l, -1);
				}
				lua_pop(l, 1); // remove return value from stack
			}
			return ret;
		}else{
			lua_pop(l, numArgs); // remove args from stack
			return 0;
		}
	}
	static void finishRunLuaFunction(lua_State *l){
		lua_pop(l, 1);
	}
	static CCDirector * sharedDirector(){
#if COCOS2D_VERSION >= 0x00030000
		return Director::getInstance();
#else
		return CCDirector::sharedDirector();
#endif
	}
	// Handle with function, for layer event, allow other three options
	LuaEventHandler * handle(int handler, bool multiTouches = false, int priority = 0, bool swallows = false){
		unhandle();
		_handler = handler;
		_multiTouches = multiTouches;
		_priority = priority;
		_swallows = swallows;
		_handlerRef = lua_ref(_lua, _handler);
		return this;
	}
	inline void unhandle(){
		if(_handler > 0){
			toluafix_remove_function_by_refid(_lua, _handler);
			lua_unref(_lua, _handlerRef);
			_handlerRef = 0;
			_handler = 0;
		}
	}
	int getHandler(){
		return _handler;
	}
	LuaEventHandler * setTypename(const char *n){
		_typename = n;
		return this;
	}
	void executeHandler(unsigned int argNum = 0){
		runFunctionHandler(_handler, argNum);
	}

	// Application enter background or foreground
	void applicationStateChange(Events e){
		if(_handler){
			pushInt((int)e);
			runFunctionHandler(_handler, 1);
		}
	}
	// CCControl event
	void controlAction(CCObject *sender,
#if COCOS2D_VERSION >= 0x00030000
		Control::EventType e){
#else
		CCControlEvent e){
#endif
		if(_handler){
			pushCCObject(sender, _typename.empty()? "CCControl" : _typename.c_str());
			pushInt(static_cast<int>(e));
			runFunctionHandler(_handler, 2);
		}
	}

	// Default event recever
	void action(CCObject *sender){
		if(_handler){
			pushCCObject(sender, _typename.empty()? "CCObject" : _typename.c_str());
			runFunctionHandler(_handler, 1); 
		}
	}
	// Call lua func with a string
	void call(const char *s){
		if(_handler){
			pushString(s);
			runFunctionHandler(_handler, 1);
		}
	}
#ifdef LUAPROXY_CCEDITBOX_ENABLED
	virtual void editBoxEditingDidBegin(CCEditBox *eb){
		editBoxEvent("begin", eb);
	}
	virtual void editBoxEditingDidEnd(CCEditBox *eb){
		editBoxEvent("end", eb);
	}
	virtual void editBoxTextChanged(CCEditBox *eb){
		editBoxEvent("change", eb);
	}
	virtual void editBoxReturn(CCEditBox *eb){
		editBoxEvent("return", eb);
	}
	void editBoxEvent(const char *e, CCEditBox *eb){
		if(_handler && e){
			pushString(e);
			pushCCObject(eb, "CCEditBox");
			runFunctionHandler(_handler, 2);
		}
	}
#endif
	// CCTableView events
	virtual CCSize tableCellSizeForIndex(CCTableView *t, unsigned int i){
		CCSize r = CCSizeZero;
		if(_handler){
			pushString("cellSize");
			pushCCObject(t, "CCTableView");
			pushInt(i);
			runLuaFunction(_handler, 3);
			lua_State *l = luaStack()->getLuaState();
			tolua_Error err;
			if(tolua_isusertype(l, -1, "CCSize", 0, &err)){
				CCSize *v = (CCSize *)tolua_tousertype(l, -1, NULL);
				if(v)r = *v;
			}
			lua_pop(l, 1);
		}
		return r;
	}
	virtual CCSize cellSizeForTable(CCTableView *t){
		return tableCellSizeForIndex(t, -1);
	}
	virtual CCTableViewCell * tableCellAtIndex(CCTableView *t, unsigned int i){
		CCTableViewCell *cell = t->dequeueCell();
		if(_handler){
			int argNum = 3;
			pushString("cellAtIndex");
			pushCCObject(t, "CCTableView");
			pushInt(i);
			if(cell){
				pushCCObject(cell, "CCTableViewCell");
				argNum ++;
			}
			runLuaFunction(_handler, argNum);
			lua_State *l = luaStack()->getLuaState();
			tolua_Error err;
			if(tolua_isusertype(l, -1, "CCTableViewCell", 0, &err)){
				cell = (CCTableViewCell *)tolua_tousertype(l, -1, NULL);
			}
			lua_pop(l, 1);
		}
		return cell;
	}
	virtual unsigned int numberOfCellsInTableView(CCTableView *t){
		int r = 0;
		if(_handler){
			pushString("numberOfCells");
			pushCCObject(t, "CCTableView");
			r = runLuaFunction(_handler, 2, true);
		}
		return r;
	}
	void tableCellEvent(const char *e, CCTableView *t, CCTableViewCell *c, CCObject *v = NULL, const char *type = NULL){
		if(_handler){
			pushString(e);
			pushCCObject(t, "CCTableView");
			if(c){	pushCCObject(c, "CCTableViewCell");}
			else{	pushNil();}
			if(v && type){	pushCCObject(v, type);}
			else{	pushNil();}
			runLuaFunction(_handler, 4, true);
		}
	}
	virtual void tableCellTouched(CCTableView *t, CCTableViewCell *c){
		tableCellTouched(t, c, NULL);
	}
	// Touched event, pass the point that touch in table
	virtual void tableCellTouched(CCTableView *t, CCTableViewCell *c, CCTouch *touch){
		tableCellEvent("cellTouched", t, c, touch, "CCTouch");
	}
	virtual void tableCellTouchBegan(CCTableView *t, CCTableViewCell *c, CCTouch *touch){
		tableCellEvent("cellTouchBegan", t, c, touch, "CCTouch");
	}
	virtual void tableCellTouchEnded(CCTableView *t, CCTableViewCell *c, CCTouch *touch){
		tableCellEvent("cellTouchEnded", t, c, touch, "CCTouch");
	}
	virtual void tableCellHighlight(CCTableView* t, CCTableViewCell* c){
		tableCellEvent("cellHighlight", t, c);
	}
	virtual void tableCellUnhighlight(CCTableView *t, CCTableViewCell* c){
		tableCellEvent("cellUnhighlight", t, c);
	}
	virtual void tableCellWillRecycle(CCTableView *t, CCTableViewCell* c){
		tableCellEvent("cellWillRecycle", t, c);
	}
	virtual void scrollViewDidScroll(CCScrollView *s){
		if(_handler){
			pushString("scroll");
			pushCCObject(s, "CCScrollView");
			runLuaFunction(_handler, 2, true);
		}
	}
	virtual void scrollViewDidZoom(CCScrollView *s){
		if(_handler){
			pushString("zoom");
			pushCCObject(s, "CCScrollView");
			runLuaFunction(_handler, 2, true);
		}
	}
	virtual void keyBackClicked(){
		if(_handler){
			pushInt((int)Events::KeyBack);
			runLuaFunction(_handler, 1);
		}
	}
	virtual void keyMenuClicked(){
		if(_handler){
			pushInt((int)Events::KeyMenu);
			runLuaFunction(_handler, 1);
		}
	}
};

class LuaCallFuncInterval : public CCActionInterval{
public:
	int _handler;
	int _handlerRef;
	LuaCallFuncInterval() : _handler(0), _handlerRef(0){}
	~LuaCallFuncInterval(){}
	virtual void startWithTarget(CCNode *tar){
		CCActionInterval::startWithTarget(tar);
		if(_handler){
			LuaEventHandler::pushString("start");
			LuaEventHandler::pushCCObject(getTarget(), "CCNode");
			LuaEventHandler::runLuaFunction(_handler, 2);
		}
	}
	virtual void update(float time){
		if(_handler){
			LuaEventHandler::pushFloat(time);
			LuaEventHandler::pushCCObject(getTarget(), "CCNode");
			LuaEventHandler::runLuaFunction(_handler, 2);
		}
	}
#if COCOS2D_VERSION >= 0x00030000
	virtual LuaCallFuncInterval * reverse() const override{
		return const_cast<LuaCallFuncInterval *>(this);
	}
	virtual LuaCallFuncInterval * clone() const override{
		return const_cast<LuaCallFuncInterval *>(this);
	}
#endif
	static LuaCallFuncInterval * create(float dur, int handler){
		LuaCallFuncInterval *o = new LuaCallFuncInterval();
		o->initWithDuration(dur);
		o->_handler = handler;
		o->autorelease();
		return o;
	}
};
#endif
