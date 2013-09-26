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

#include "LuaEventHandler.hpp"

class LuaTableView : public CCTableView{
protected:
	LuaEventHandler *_handler;
	LuaTableView():_scrollOffset(0), _handler(0), _scrollNode(0), _scrollBar(0), _scrollTrack(0), _scrollTrackDelta(0){}
	CCNode *_scrollNode;
	CCScale9Sprite *_scrollBar;
	CCScale9Sprite *_scrollTrack;
	float _scrollOffset;
	float _scrollTrackDelta;
public:
	~LuaTableView(){
		CC_SAFE_RELEASE(_handler);
		setScrollNode(NULL);
		setScrollBar(NULL);
		setScrollTrack(NULL);
	}
	static LuaTableView * createWithHandler(LuaEventHandler *h, CCSize s, CCNode *c){
		LuaTableView *r = new LuaTableView();
		CC_SAFE_RETAIN(h);
		r->_handler = h;
		r->setDataSource(h);
		r->initWithViewSize(s, c);
		r->setDelegate(h);
		r->autorelease();
		r->reloadData();
		return r;
	}
	CCTableViewDelegate * getTableViewDelegate(){
#if COCOS2D_VERSION >= 0x00030000
		return _tableViewDelegate;
#else
		return m_pTableViewDelegate;
#endif
	}
	CCTableViewCell * cellForTouch(CCTouch *t){
		unsigned int index;
		CCPoint point = getContainer()->convertTouchToNodeSpace(t);
		index = _indexFromOffset(point);
		return cellAtIndex(index);
	}
	virtual bool ccTouchBegan(CCTouch *t, CCEvent *e){
		bool r = CCTableView::ccTouchBegan(t, e);
		if(r){
			CCTableViewCell *c = cellForTouch(t);
			LuaEventHandler *h = dynamic_cast<LuaEventHandler *>(getTableViewDelegate());
			if(c && h){
				h->tableCellTouchBegan(this, c, t);
			}
		}
		return r;
	}
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
		if(!isVisible()){
			return;
		}
		CCTableViewCell *cell = cellForTouch(pTouch);
		if(cell){
			CCTableViewDelegate *dele = getTableViewDelegate();
			LuaEventHandler *h = dynamic_cast<LuaEventHandler *>(dele);
#if COCOS2D_VERSION >= 0x00030000
			Array *touches = _touches;
#else
			CCArray *touches = m_pTouches;
#endif
			if(touches->count() == 1 && !isTouchMoved()){
				if(h){	h->tableCellTouched(this, cell, pTouch);}
				else{	dele->tableCellTouched(this, cell);}
				dele->tableCellUnhighlight(this, cell);
			}else if(h){
				h->tableCellTouchEnded(this, cell, pTouch);
			}
		}else{
			printf("LuaTableView.touchEnded cell is null %f,%f\n", pTouch->getLocation().x, pTouch->getLocation().y);
		}
		CCScrollView::ccTouchEnded(pTouch, pEvent);
	}
	virtual void scrollViewDidScroll(CCScrollView *s){
		CCTableView::scrollViewDidScroll(s);
		_handler->scrollViewDidScroll(this);
		updateScroll();
	}
	virtual void scrollViewDidZoom(CCScrollView *s){
		CCTableView::scrollViewDidZoom(s);
		_handler->scrollViewDidZoom(this);
	}
	virtual void reloadData(){
		CCTableView::reloadData();
		resetScroll();
	}
	void setScrollNode(CCNode *n){
		if(_scrollNode){ _scrollNode->removeAllChildrenWithCleanup(true);}
		_scrollNode = n;
		if(n){
			addChild(n, 255);
		}
	}
	void setScrollBar(CCScale9Sprite *s){
		if(_scrollBar){ _scrollBar->removeAllChildrenWithCleanup(true);}
		_scrollBar = s;
		if(s){
			addChild(s, 255);
		}
	}
	void setScrollTrack(CCScale9Sprite *st){
		if(_scrollTrack){ _scrollTrack->removeAllChildrenWithCleanup(true);}
		_scrollTrack = st;
		if(st){
			addChild(st, 254);
		}
	}
	void setScrollOffset(float o){
		_scrollOffset = o;
	}
	void resetScroll(){
		if(!_scrollBar){ return;}
		CCSize vs = getViewSize(), cs = getContentSize();
		bool vert = getDirection() == kCCScrollViewDirectionVertical;
		bool v = vert? vs.height < cs.height : vs.width < cs.height;
		_scrollBar->setVisible(v);
		CCPoint p = ccp(0, 0), ap = vert? ccp(1,0) : CCPointZero;
		if(v){
			CCSize s = _scrollBar->getPreferredSize(),
				st = _scrollTrack? _scrollTrack->getPreferredSize() : CCSizeZero;
			if(vert){
				p.x = vs.width + _scrollOffset - (st.width > 0? (st.width - s.width) / 2 : 0);
				_scrollTrackDelta = st.height > 0? (st.height - s.height) / 2 : 0;
				s.height = vs.height / cs.height * vs.height - _scrollTrackDelta * 2;
			}else{
				p.y = vs.height + _scrollOffset - (st.height > 0? (st.height - s.height) / 2 : 0);
				_scrollTrackDelta = st.width > 0? (st.width - s.width) / 2 : 0;
				s.width = vs.width / cs.width * vs.width - _scrollTrackDelta * 2;
			}
			_scrollBar->setAnchorPoint(ap);
			_scrollBar->setPreferredSize(s);
			_scrollBar->setPosition(p);
//CCLog("LuaTableView vScroll.size=%d,%d vh=%d ch=%d", (int)s.width, (int)s.height, (int)vs.height, (int)cs.height);
		}
		if(_scrollTrack){
			_scrollTrack->setVisible(v);
			if(v){
				CCSize s = _scrollTrack->getPreferredSize();
				if(vert){
					p.x = vs.width + _scrollOffset;
					s.height = vs.height;
				}else{
					p.y = vs.height + _scrollOffset;
					s.width = vs.width;
				}
				_scrollTrack->setAnchorPoint(ap);
				_scrollTrack->setPreferredSize(s);
				_scrollTrack->setPosition(p);
			}
		}
//CCLog("LuaTableView reload vscr=%x visible=%d", _scroller, _scrollBar->isVisible());
		updateScroll();
	}

	void updateScroll(){
		bool vBar = _scrollBar && _scrollBar->isVisible(),
			vNode = _scrollNode && _scrollNode->isVisible();
		if(!vBar || !vNode){
			return;
		}
		bool vert = getDirection() == kCCScrollViewDirectionVertical;
		CCPoint p, cp = getContentOffset();
		CCSize vs = getViewSize(),
			cs = getContentSize();
		float rate = 1 - (vert? fabsf(cp.y) / (cs.height - vs.height) : fabsf(cp.x) / (cs.width - vs.width));
		if(vBar){
			CCSize ss = _scrollBar->getPreferredSize();
			p = _scrollBar->getPosition();
			if(vert){	p.y = cs.height - (cs.height - ss.height) * rate - ss.height - _scrollTrackDelta;
			}else{		p.x = cs.width - (cs.width - ss.width) * rate - ss.width - _scrollTrackDelta;
			}
			_scrollBar->setPosition(p);
		}
		if(vNode){
			p = _scrollNode->getPosition();
			if(vert){	p.y = cp.y + vs.height * rate;
			}else{		p.x = cp.x + vs.width * rate;
			}
			_scrollNode->setPosition(p);
		}
		if(_scrollTrack){
			p = _scrollTrack->getPosition();
			if(vert){	p.y = fabsf(cp.y);
			}else{		p.x = fabsf(cp.x);
			}
			_scrollTrack->setPosition(p);
		}
//CCLog("LuaTableView.updateScroll ss=%d,%d vh=%d cy=%d ch=%d y=%d", (int)ss.width, (int)ss.height, (int)vs.height, (int)p.y, (int)cs.height, (int)_scrollBar->getPositionY());
	}
};

#endif //__LUATABLEVIEW__