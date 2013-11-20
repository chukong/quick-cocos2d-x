#ifndef __TOLUA_CCTABLEVIEW__
#define __TOLUA_CCTABLEVIEW__

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "LuaProxy.hpp"

//######################################## CCTableView ##########################
//CCTableView::create
static int tolua_CCTableView_create(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CCTableView", 0, &err) || !tolua_isusertype(l, 2, "CCTableViewDataSource", 0, &err) ||
		!tolua_isusertype(l, 3, "CCSize", 0, &err) ||
		!(tolua_isusertype(l, 4, "CCNode", 0, &err) || tolua_isnoobj(l, 4, &err))){
		tolua_error(l,"#ferror in function 'CCTableView.create'.",&err);
		return 0;
	}
#endif
	CCTableViewDataSource *ds = (CCTableViewDataSource *)tolua_tousertype(l, 2, NULL);
	CCSize *s = (CCSize *)tolua_tousertype(l, 3, NULL);
	CCNode *c = (CCNode *)tolua_tousertype(l, 4, NULL);
	if(ds){
		CCSize ts = s? *s : CCSizeZero;
		CCTableView *t = c? CCTableView::create(ds, ts, c) : CCTableView::create(ds, ts);
		tolua_pushusertype(l, t, "CCTableView");
	}
	return 1;
}
//CCTableView::getDataSource
static int tolua_CCTableView_getDataSource(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.getDataSource'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushusertype(l, o->getDataSource(), "CCTableViewDataSource");
	return 1;
}
//CCTableView::setDataSource
static int tolua_CCTableView_setDataSource(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err) || !tolua_isusertype(l, 2, "CCTableViewDataSource", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.setDataSource'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	if(o)o->setDataSource((CCTableViewDataSource *)tolua_tousertype(l, 2, NULL));
	tolua_pushusertype(l, o, "CCTableView");
	return 1;
}
//CCTableView::getDelegate
static int tolua_CCTableView_getDelegate(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.getDelegate'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushusertype(l, o->getDelegate(), "CCTableViewDelegate");
	return 1;
}
//CCTableView::setDelegate
static int tolua_CCTableView_setDelegate(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err) || !tolua_isusertype(l, 2, "CCTableViewDelegate", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.setDelegate'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	if(o)o->setDelegate((CCTableViewDelegate *)tolua_tousertype(l, 2, NULL));
	tolua_pushusertype(l, o, "CCTableView");
	return 1;
}
//CCTableView::getVerticalFillOrder
static int tolua_CCTableView_getVerticalFillOrder(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.getVerticalFillOrder'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushnumber(l, o->getVerticalFillOrder());
	return 1;
}
//CCTableView::setVerticalFillOrder
static int tolua_CCTableView_setVerticalFillOrder(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err) || !tolua_isnumber(l, 2, kCCTableViewFillTopDown, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.setVerticalFillOrder'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	if(o)o->setVerticalFillOrder((CCTableViewVerticalFillOrder)(int)tolua_tonumber(l, 2, kCCTableViewFillTopDown));
	tolua_pushusertype(l, o, "CCTableView");
	return 1;
}
//CCTableView::updateCellAtIndex
static int tolua_CCTableView_updateCellAtIndex(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err) || !tolua_isnumber(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.updateCellAtIndex'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	if(o)o->updateCellAtIndex(tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCTableView");
	return 1;
}
//CCTableView::insertCellAtIndex
static int tolua_CCTableView_insertCellAtIndex(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err) || !tolua_isnumber(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.insertCellAtIndex'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	if(o)o->insertCellAtIndex(tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCTableView");
	return 1;
}
//CCTableView::removeCellAtIndex
static int tolua_CCTableView_removeCellAtIndex(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err) || !tolua_isnumber(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.removeCellAtIndex'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	if(o)o->removeCellAtIndex(tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCTableView");
	return 1;
}
//CCTableView::reloadData
static int tolua_CCTableView_reloadData(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.reloadData'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	if(o)o->reloadData();
	tolua_pushusertype(l, o, "CCTableView");
	return 1;
}
//CCTableView::dequeueCell
static int tolua_CCTableView_dequeueCell(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.dequeueCell'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	CCTableViewCell *c = o? o->dequeueCell() : NULL;
	tolua_pushusertype(l, c, "CCTableViewCell");
	return 1;
}
//CCTableView::cellAtIndex
static int tolua_CCTableView_cellAtIndex(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableView", 0, &err) || !tolua_isnumber(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableView.cellAtIndex'.",&err);
		return 0;
	}
#endif
	CCTableView *o = (CCTableView *)tolua_tousertype(l, 1, NULL);
	CCTableViewCell *c = o? o->cellAtIndex(tolua_tonumber(l, 2, 0)) : NULL;
	tolua_pushusertype(l, c, "CCTableViewCell");
	return 1;
}
//######################################## CCTableViewCell ##########################
//CCTableViewCell::create
static int tolua_CCTableViewCell_create(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CCTableViewCell", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableViewCell.create'.",&err);
		return 0;
	}
#endif
	CCTableViewCell *c = new CCTableViewCell();
	c->autorelease();
	tolua_pushusertype(l, c, "CCTableViewCell");
	return 1;
}
//CCTableViewCell::getIdx
static int tolua_CCTableViewCell_getIdx(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableViewCell", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableViewCell.getIdx'.",&err);
		return 0;
	}
#endif
	CCTableViewCell *o = (CCTableViewCell *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushnumber(l, o->getIdx());
	return 1;
}
//CCTableViewCell::setIdx
static int tolua_CCTableViewCell_setIdx(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableViewCell", 0, &err) || !tolua_isnumber(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableViewCell.setIdx'.",&err);
		return 0;
	}
#endif
	CCTableViewCell *o = (CCTableViewCell *)tolua_tousertype(l, 1, NULL);
	if(o)o->setIdx(tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCTableViewCell");
	return 1;
}
//CCTableViewCell::reset
static int tolua_CCTableViewCell_reset(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableViewCell", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableViewCell.reset'.",&err);
		return 0;
	}
#endif
	CCTableViewCell *o = (CCTableViewCell *)tolua_tousertype(l, 1, NULL);
	if(o)o->reset();
	tolua_pushusertype(l, o, "CCTableViewCell");
	return 1;
}
//CCTableViewCell::getObjectID
static int tolua_CCTableViewCell_getObjectID(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableViewCell", 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableViewCell.getObjectID'.",&err);
		return 0;
	}
#endif
	CCTableViewCell *o = (CCTableViewCell *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushnumber(l, o->getObjectID());
	return 1;
}
//CCTableViewCell::setObjectID
static int tolua_CCTableViewCell_setObjectID(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCTableViewCell", 0, &err) || !tolua_isnumber(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'CCTableViewCell.setObjectID'.",&err);
		return 0;
	}
#endif
	CCTableViewCell *o = (CCTableViewCell *)tolua_tousertype(l, 1, NULL);
	if(o)o->setObjectID(tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCTableViewCell");
	return 1;
}

#endif //__TOLUA_CCTABLEVIEW__
