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

#ifndef __LUATABLEVIEW__
#define __LUATABLEVIEW__

#include "LuaEventHandler.h"

class LuaTableView : public CCTableView{
protected:
	LuaEventHandler *_handler;
	LuaTableView();
	CCNode *_scrollNode;
	CCScale9Sprite *_scrollBar;
	CCScale9Sprite *_scrollTrack;
	float _scrollOffset;
	float _scrollTrackDelta;
public:
	~LuaTableView();
	static LuaTableView * createWithHandler(LuaEventHandler *h, CCSize s, CCNode *c);
	CCTableViewCell * cellForTouch(CCTouch *t);
	virtual bool ccTouchBegan(CCTouch *t, CCEvent *e);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void scrollViewDidScroll(CCScrollView *s);
	virtual void scrollViewDidZoom(CCScrollView *s);
	virtual void reloadData();
	void setScrollNode(CCNode *n);
	void setScrollBar(CCScale9Sprite *s);
	void setScrollTrack(CCScale9Sprite *t);
	void setScrollOffset(float o);
	void resetScroll();
	void updateScroll();
};

#endif //__LUATABLEVIEW__