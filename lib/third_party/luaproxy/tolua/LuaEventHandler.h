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

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum {
	kLuaEventKeyBack,
	kLuaEventKeyMenu,
	kLuaEventAppEnterBackground,
	kLuaEventAppEnterForeground
} LuaEvents;

class LuaEventHandler : public CCLayer, public CCBAnimationManagerDelegate,
public CCTableViewDelegate, public CCTableViewDataSource
#ifdef LUAPROXY_CCEDITBOX_ENABLED
,public CCEditBoxDelegate
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
	CCBAnimationManager *_aniMGR;
	LuaEventHandler() : _aniMGR(NULL), _lua(NULL), _handler(0), _handlerRef(0){}
public:
	static LuaEventHandler * app;
	~LuaEventHandler();
	static LuaEventHandler * createAppHandler(lua_State *l, int handler);
	static LuaEventHandler * create(lua_State *l = NULL);
	static void pushInt(int v);
	static void pushFloat(float v);
	static void pushBoolean(bool v);
	static void pushString(const char *v);
	static void pushCCObject(CCObject *v, const char *t);
	static void pushNil();
	static int runFunctionHandler(int hnd, int argNum, bool retInt = false);
	static void runString(const char *s);
	static lua_State * defaultState();
	// Handle with function, for layer event, allow other three options
	LuaEventHandler * handle(int handler, bool multiTouches = false, int priority = 0, bool swallows = false);
	// Handle for CCBAnimationManager with optional function
	LuaEventHandler * handle(CCBAnimationManager *m, int handler = 0);
	inline void unhandle();
	int getHandler();
	LuaEventHandler * setTypename(const char *n);
	void executeHandler(unsigned int argNum = 0);

	// Application enter background or foreground
	void applicationStateChange(LuaEvents e);
	// CCControl event
	void controlAction(CCObject *sender, CCControlEvent e);
	// Default event recever
	void action(CCObject *sender);
	// An animation of ccb complated
	void completedAnimationSequenceNamed(const char *n);
	// Call lua func with a string
	void call(const char *s);
#ifdef LUAPROXY_CCEDITBOX_ENABLED
	virtual void editBoxEditingDidBegin(CCEditBox *eb);
	virtual void editBoxEditingDidEnd(CCEditBox *eb);
	virtual void editBoxTextChanged(CCEditBox *eb);
	virtual void editBoxReturn(CCEditBox *eb);
	void editBoxEvent(const char *e, CCEditBox *eb);
#endif
	// CCTableView events
	virtual CCSize tableCellSizeForIndex(CCTableView *t, unsigned int i);
	virtual CCSize cellSizeForTable(CCTableView *t);
	virtual CCTableViewCell * tableCellAtIndex(CCTableView *t, unsigned int i);
	virtual unsigned int numberOfCellsInTableView(CCTableView *t);
	void tableCellEvent(const char *e, CCTableView *t, CCTableViewCell *c, CCObject *v = NULL, const char *type = NULL);
	virtual void tableCellTouched(CCTableView *t, CCTableViewCell *c);
	// Touched event, pass the point that touch in table
	virtual void tableCellTouched(CCTableView *t, CCTableViewCell *c, CCTouch *touch);
	virtual void tableCellTouchBegan(CCTableView *t, CCTableViewCell *c, CCTouch *touch);
	virtual void tableCellTouchEnded(CCTableView *t, CCTableViewCell *c, CCTouch *touch);
	virtual void tableCellHighlight(CCTableView* t, CCTableViewCell* c);
	virtual void tableCellUnhighlight(CCTableView *t, CCTableViewCell* c);
	virtual void tableCellWillRecycle(CCTableView *t, CCTableViewCell* c);
	virtual void scrollViewDidScroll(CCScrollView *s);
	virtual void scrollViewDidZoom(CCScrollView *s);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
};

class LuaCallFuncInterval : public CCActionInterval{
public:
	int _handler;
	int _handlerRef;
	LuaCallFuncInterval() : _handler(0), _handlerRef(0){}
	~LuaCallFuncInterval();
	static LuaCallFuncInterval * create(float dur, int handler);
	virtual void startWithTarget(CCNode *tar);
	virtual void update(float time);
};
#endif