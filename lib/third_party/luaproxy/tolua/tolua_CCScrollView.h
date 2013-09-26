#ifndef __TOLUA_CCSCROLLVIEW__
#define __TOLUA_CCSCROLLVIEW__

#include "../LuaProxy.hpp"
#include "tolua_util.h"

//######################################## CCScrollView ##########################
//CCScrollView::create()
//CCScrollView::create(CCSize *, CCNode * = NULL)
static int tolua_CCScrollView_create(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.create'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = NULL;
	if(tolua_isusertype(l, 2, "CCSize", 0, NULL)){
		CCSize *s = static_cast<CCSize *>(tolua_tousertype(l, 2, NULL));
		o = CCScrollView::create(s? *s : CCSizeZero, static_cast<CCNode *>(tolua_tousertype(l, 3, NULL)));
	}else{
		o = CCScrollView::create();
	}
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::isBounceable()
static int tolua_CCScrollView_isBounceable(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.isBounceable'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	tolua_pushboolean(l, o? o->isBounceable() : false);
	return 1;
}
//CCScrollView::setBounceable(bool)
static int tolua_CCScrollView_setBounceable(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isboolean(l, 2, false, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.setBounceable'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o){ o->setBounceable(tolua_toboolean(l, 2, false) > 0);}
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::addChild(CCNode *node, int order = 0, int tag = node->getTag())
static int tolua_CCScrollView_addChild(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err) ||
			!(tolua_isnoobj(l, 3, &err) || tolua_isnumber(l, 3, 0, &err)) ||
			!(tolua_isnoobj(l, 4, &err) || tolua_isnumber(l, 4, 0, &err))){
		tolua_error(l,"#ferror in function 'CCScrollView.addChild'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	CCNode *n = (CCNode *)tolua_tousertype(l, 2, NULL);
	if(o && n)o->addChild(n, tolua_tonumber(l, 3, 0), tolua_tonumber(l, 4, n->getTag()));
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::isClippingToBounds()
static int tolua_CCScrollView_isClippingToBounds(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.isClippingToBounds'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	tolua_pushboolean(l, o? o->isClippingToBounds() : false);
	return 1;
}
//CCScrollView::setClippingToBounds(bool)
static int tolua_CCScrollView_setClippingToBounds(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isboolean(l, 2, false, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.setClippingToBounds'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o)o->setClippingToBounds(tolua_toboolean(l, 2, false) > 0);
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::getContainer()
static int tolua_CCScrollView_getContainer(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.getContainer'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushusertype(l, o->getContainer(), "CCNode");
	return 1;
}
//CCScrollView::setContainer(CCNode *)
static int tolua_CCScrollView_setContainer(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.setContainer'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o)o->setContainer((CCNode *)tolua_tousertype(l, 2, NULL));
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::getContentOffset()
static int tolua_CCScrollView_getContentOffset(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.getContentOffset'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	tolua_pushusertype(l, Mtolua_new((CCPoint)(o? o->getContentOffset() : CCPointZero)), "CCPoint");
	return 1;
}
//CCScrollView::setContentOffset(CCPoint *, bool animated = false)
static int tolua_CCScrollView_setContentOffset(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isusertype(l, 2, "CCPoint", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.setContentOffset'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o){
		void *ps = tolua_tousertype(l, 2, NULL);
		o->setContentOffset(ps? *((CCPoint *)ps) : CCPointZero, tolua_toboolean(l, 3, false) == 1);
	}
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::setContentOffsetInDuration(CCPoint *, float)
static int tolua_CCScrollView_setContentOffsetInDuration(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isusertype(l, 2, "CCPoint", 0, &err) ||
		!tolua_isnumber(l, 3, 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.setContentOffsetInDuration'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o){
		void *ps = tolua_tousertype(l, 2, NULL);
		o->setContentOffsetInDuration(ps? *((CCPoint *)ps) : CCPointZero, tolua_tonumber(l, 3, 0));
	}
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::getContentSize()
static int tolua_CCScrollView_getContentSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.getContentSize'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	tolua_pushusertype(l, Mtolua_new((CCSize)(o? o->getContentSize() : CCSizeZero)), "CCSize");
	return 1;
}
//CCScrollView::setContentSize(CCSize *)
static int tolua_CCScrollView_setContentSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isusertype(l, 2, "CCSize", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.setContentSize'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o){
		void *ps = tolua_tousertype(l, 2, NULL);
		o->setContentSize(ps? *((CCSize *)ps) : CCSizeZero);
	}
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::getDirection
static int tolua_CCScrollView_getDirection(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.getDirection'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	tolua_pushnumber(l, o? o->getDirection() : kCCScrollViewDirectionBoth);
	return 1;
}
//CCScrollView::setDirection
static int tolua_CCScrollView_setDirection(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isnumber(l, 2, 0, &err) ||
		!tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.setDirection'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o)o->setDirection((CCScrollViewDirection)(int)tolua_tonumber(l, 2, kCCScrollViewDirectionBoth));
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::isDragging
static int tolua_CCScrollView_isDragging(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.isDragging'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	tolua_pushnumber(l, o? o->isDragging() : false);
	return 1;
}
//CCScrollView::isNodeVisible
static int tolua_CCScrollView_isNodeVisible(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.isNodeVisible'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	tolua_pushnumber(l, o? o->isNodeVisible((CCNode *)tolua_tousertype(l, 2, NULL)) : false);
	return 1;
}
//CCScrollView::isTouchMoved
static int tolua_CCScrollView_isTouchMoved(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.isTouchMoved'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	tolua_pushnumber(l, o? o->isTouchMoved() : false);
	return 1;
}
//CCScrollView::getViewSize
static int tolua_CCScrollView_getViewSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.getViewSize'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	tolua_pushusertype(l, Mtolua_new((CCSize)(o? o->getViewSize() : CCSizeZero)), "CCSize");
	return 1;
}
//CCScrollView::setViewSize
static int tolua_CCScrollView_setViewSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isusertype(l, 2, "CCSize", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.setViewSize'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o){
		void *ps = tolua_tousertype(l, 2, NULL);
		CCSize s = ps? *((CCSize *)ps) : CCSizeZero;
		o->setViewSize(s);
	}
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::getZoomScale
static int tolua_CCScrollView_getZoomScale(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.getZoomScale'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	tolua_pushnumber(l, o? o->getZoomScale() : 1.0f);
	return 1;
}
//CCScrollView::setZoomScale
static int tolua_CCScrollView_setZoomScale(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isnumber(l, 2, 0, &err) ||
		!(tolua_isnoobj(l, 3, &err) || tolua_isboolean(l, 3, false, &err))){
		tolua_error(l,"#ferror in function 'CCScrollView.setZoomScale'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o){
		float s = tolua_tonumber(l, 2, 1);
		if(tolua_toboolean(l, 3, false) > 0)o->setZoomScale(s, true);
		else o->setZoomScale(s);
	}
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}
//CCScrollView::setZoomScaleInDuration
static int tolua_CCScrollView_setZoomScaleInDuration(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScrollView", 0, &err) || !tolua_isnumber(l, 2, 0, &err) ||
		!tolua_isnumber(l, 3, 0, &err)){
		tolua_error(l,"#ferror in function 'CCScrollView.setZoomScaleInDuration'.",&err);
		return 0;
	}
#endif
	CCScrollView *o = (CCScrollView *)tolua_tousertype(l, 1, NULL);
	if(o)o->setZoomScaleInDuration(tolua_tonumber(l, 2, 1), tolua_tonumber(l, 2, 0.15f));
	tolua_pushusertype(l, o, "CCScrollView");
	return 1;
}

#endif //__TOLUA_CCSCROLLVIEW__
