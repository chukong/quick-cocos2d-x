#ifndef __TOLUA_CCCONTROL__
#define __TOLUA_CCCONTROL__

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

//######################################## CCControl ##########################
//CCControl::isEnabled
static int tolua_CCControl_isEnabled(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControl", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'isEnabled'.",&err);
		return 0;
	}
#endif
	CCControl *o = (CCControl *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushboolean(l, o->isEnabled());
	return 1;
}
//CCControl::isHighlighted
static int tolua_CCControl_isHighlighted(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControl", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'isHighlighted'.",&err);
		return 0;
	}
#endif
	CCControl *o = (CCControl *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushboolean(l, o->isHighlighted());
	return 1;
}
//CCControl::isSelected
static int tolua_CCControl_isSelected(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControl", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'isSelected'.",&err);
		return 0;
	}
#endif
	CCControl *o = (CCControl *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushboolean(l, o->isSelected());
	return 1;
}
//CCControl::setSelected
static int tolua_CCControl_setSelected(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControl", 0, &err) || !tolua_isboolean(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'setSelected'.",&err);
		return 0;
	}
#endif
	CCControl *o = (CCControl *)tolua_tousertype(l, 1, NULL);
	if(o){
		o->setSelected(tolua_toboolean(l, 2, false) > 0);
		tolua_pushusertype(l, o, "CCControl");
	}
	return 1;
}
//CCControl::getState
static int tolua_CCControl_getState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControl", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'getState'.",&err);
		return 0;
	}
#endif
	CCControl *o = (CCControl *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushnumber(l, o->getState());
	return 1;
}
//CCControl::isTouchInside
static int tolua_CCControl_isTouchInside(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControl", 0, &err) || !tolua_isusertype(l, 2, "CCTouch", 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'isTouchInside'.",&err);
		return 0;
	}
#endif
	CCControl *o = (CCControl *)tolua_tousertype(l, 1, NULL);
	CCTouch *t = (CCTouch *)tolua_tousertype(l, 2, NULL);
	tolua_pushboolean(l, o && t? o->isTouchInside(t) : false);
	return 1;
}
//CCControl::getTouchLocation
static int tolua_CCControl_getTouchLocation(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControl", 0, &err) || !tolua_isusertype(l, 2, "CCTouch", 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'getTouchLocation'.",&err);
		return 0;
	}
#endif
	CCControl *o = (CCControl *)tolua_tousertype(l, 1, NULL);
	CCTouch *t = (CCTouch *)tolua_tousertype(l, 2, NULL);
	CCPoint p = o && t? o->getTouchLocation(t) : CCPointMake(0, 0);
	tolua_pushusertype(l, Mtolua_new((CCPoint)(p)), "CCPoint");
	return 1;
}
//CCControl::hasVisibleParents
static int tolua_CCControl_hasVisibleParents(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControl", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'hasVisibleParents'.",&err);
		return 0;
	}
#endif
	CCControl *o = (CCControl *)tolua_tousertype(l, 1, NULL);
	tolua_pushboolean(l, o? o->hasVisibleParents() : false);
	return 1;
}
//CCControl::sendActionsForControlEvents(CCControlEvent)
static int tolua_CCControl_sendActionsForControlEvents(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControl", 0, &err) || !tolua_isnumber(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'sendActionsForControlEvents'.",&err);
		return 0;
	}
#endif
	CCControl *o = (CCControl *)tolua_tousertype(l, 1, NULL);
	if(o){
		o->sendActionsForControlEvents((CCControlEvent)(int)tolua_tonumber(l, 2, CCControlEventTouchUpInside));
	}
	tolua_pushusertype(l, o, "CCControl");
	return 1;
}
//######################################## CCControlButton ##########################
//CCControlButton::create
static int tolua_CCControlButton_create(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CCControlButton", 0, &err)
		|| !(tolua_isnoobj(l, 2, &err) || tolua_isusertype(l, 2, "CCScale9Sprite", 0, &err))
		|| !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.create'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *s = (CCScale9Sprite *)tolua_tousertype(l, 2, NULL);
	CCControlButton *o = s? CCControlButton::create(s) : CCControlButton::create();
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::getBackgroundSprite
static int tolua_CCControlButton_getBackgroundSprite(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getBackgroundSprite'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushusertype(l, o->getBackgroundSprite(), "CCScale9Sprite");
	return 1;
}
//CCControlButton::setBackgroundSprite
static int tolua_CCControlButton_setBackgroundSprite(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isusertype(l, 2, "CCScale9Sprite", 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setBackgroundSprite'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setBackgroundSprite((CCScale9Sprite *)tolua_tousertype(l, 2, NULL));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::getBackgroundSpriteForState
static int tolua_CCControlButton_getBackgroundSpriteForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnumber(l, 2, CCControlStateNormal, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getBackgroundSpriteForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushusertype(l, o->getBackgroundSpriteForState(tolua_tonumber(l, 2, CCControlStateNormal)), "CCScale9Sprite");
	return 1;
}
//CCControlButton::setBackgroundSpriteForState
static int tolua_CCControlButton_setBackgroundSpriteForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isusertype(l, 2, "CCScale9Sprite", 0, &err)
		|| !tolua_isnumber(l, 3, CCControlStateNormal, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setBackgroundSpriteForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setBackgroundSpriteForState((CCScale9Sprite *)tolua_tousertype(l, 2, NULL),
		tolua_tonumber(l, 3, CCControlStateNormal));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::setBackgroundSpriteFrameForState
static int tolua_CCControlButton_setBackgroundSpriteFrameForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isusertype(l, 2, "CCSpriteFrame", 0, &err)
		|| !tolua_isnumber(l, 3, CCControlStateNormal, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setBackgroundSpriteFrameForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setBackgroundSpriteFrameForState((CCSpriteFrame *)tolua_tousertype(l, 2, NULL),
		tolua_tonumber(l, 3, CCControlStateNormal));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::getCurrentTitle
static int tolua_CCControlButton_getCurrentTitle(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getCurrentTitle'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushstring(l, o->getCurrentTitle()->getCString());
	return 1;
}
//CCControlButton::setEnabled
static int tolua_CCControlButton_setEnabled(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isboolean(l, 2, false, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setEnabled'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setEnabled(tolua_toboolean(l, 2, true) > 0);
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::getLabelAnchorPoint
static int tolua_CCControlButton_getLabelAnchorPoint(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getLabelAnchorPoint'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushusertype(l, Mtolua_new((CCPoint)(o->getLabelAnchorPoint())), "CCPoint");
	return 1;
}
//CCControlButton::setLabelAnchorPoint
static int tolua_CCControlButton_setLabelAnchorPoint(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnumber(l, 2, 0, &err)
		|| !tolua_isnumber(l, 3, 0, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setLabelAnchorPoint'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setLabelAnchorPoint(ccp(tolua_tonumber(l, 2, 0), tolua_tonumber(l, 3, 0)));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::setMargins
static int tolua_CCControlButton_setMargins(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnumber(l, 2, 0, &err)
		|| !tolua_isnumber(l, 3, 0, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setMargins'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setMargins(tolua_tonumber(l, 2, 0), tolua_tonumber(l, 3, 0));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::getOpacity
static int tolua_CCControlButton_getOpacity(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getOpacity'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushnumber(l, o->getOpacity());
	return 1;
}
//CCControlButton::setOpacity
static int tolua_CCControlButton_setOpacity(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnumber(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setOpacity'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setOpacity(tolua_tonumber(l, 2, 255));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::getPreferredSize
static int tolua_CCControlButton_getPreferredSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getPreferredSize'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushusertype(l, Mtolua_new((CCSize)(o->getPreferredSize())), "CCSize");
	return 1;
}
//CCControlButton::setPreferredSize
static int tolua_CCControlButton_setPreferredSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnumber(l, 2, 0, &err)
		|| !tolua_isnumber(l, 3, 0, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setPreferredSize'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setPreferredSize(CCSizeMake(tolua_tonumber(l, 2, 0), tolua_tonumber(l, 3, 0)));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::isPushed
static int tolua_CCControlButton_isPushed(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.isPushed'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushboolean(l, o->isPushed());
	return 1;
}
//CCControlButton::getTitleLabel
static int tolua_CCControlButton_getTitleLabel(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getTitleLabel'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o){
		CCNode *n = o->getTitleLabel();
		CCLabelTTF *ttf = dynamic_cast<CCLabelTTF *>(n);
		if(ttf)tolua_pushusertype(l, ttf, "CCLabelTTF");
		else{
			CCLabelBMFont *bm = dynamic_cast<CCLabelBMFont *>(n);
			if(bm)tolua_pushusertype(l, bm, "CCLabelBMFont");
			else{
				CCLabelAtlas *at = dynamic_cast<CCLabelAtlas *>(n);
				tolua_pushusertype(l, at? at : n, at? "CCLabelAtlas" : "CCNode");
			}
		}
	}
	return 1;
}
//CCControlButton::setTitleLabel
static int tolua_CCControlButton_setTitleLabel(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setTitleLabel'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setTitleLabel((CCNode *)tolua_tousertype(l, 2, NULL));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::getTitleBMFontForState
static int tolua_CCControlButton_getTitleBMFontForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnumber(l, 2, CCControlStateNormal, &err)
		|| !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getTitleBMFontForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushstring(l, o->getTitleBMFontForState(tolua_tonumber(l, 2, CCControlStateNormal)));
	return 1;
}
//CCControlButton::setTitleBMFontForState
static int tolua_CCControlButton_setTitleBMFontForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isstring(l, 2, 0, &err)
		|| !tolua_isnumber(l, 3, CCControlStateNormal, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setTitleBMFontForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setTitleBMFontForState(tolua_tostring(l, 2, NULL), tolua_tonumber(l, 3, CCControlStateNormal));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::getTitleColorForState
static int tolua_CCControlButton_getTitleColorForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnumber(l, 2, CCControlStateNormal, &err)
		|| !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getTitleColorForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushusertype(l, Mtolua_new((ccColor3B)(o->getTitleColorForState(tolua_tonumber(l, 2, CCControlStateNormal)))), "ccColor3B");
	return 1;
}
//CCControlButton::setTitleColorForState
static int tolua_CCControlButton_setTitleColorForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isusertype(l, 2, "ccColor3B", 0, &err)
		|| !tolua_isnumber(l, 3, CCControlStateNormal, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setTitleColorForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o){
		o->setTitleColorForState(*(ccColor3B *)tolua_tousertype(l, 2, NULL), tolua_tonumber(l, 3, CCControlStateNormal));
	}
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::getTitleTTFForState
static int tolua_CCControlButton_getTitleTTFForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnumber(l, 2, CCControlStateNormal, &err)
		|| !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getTitleTTFForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushstring(l, o->getTitleTTFForState(tolua_tonumber(l, 2, CCControlStateNormal)));
	return 1;
}
//CCControlButton::setTitleTTFForState
static int tolua_CCControlButton_setTitleTTFForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isstring(l, 2, 0, &err)
		|| !tolua_isnumber(l, 3, CCControlStateNormal, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setTitleTTFForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setTitleTTFForState(tolua_tostring(l, 2, NULL), tolua_tonumber(l, 3, CCControlStateNormal));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
//CCControlButton::getTitleForState
static int tolua_CCControlButton_getTitleForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isnumber(l, 2, CCControlStateNormal, &err)
		|| !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.getTitleForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushstring(l, o->getTitleForState(tolua_tonumber(l, 2, CCControlStateNormal))->getCString());
	return 1;
}
//CCControlButton::setTitleForState
static int tolua_CCControlButton_setTitleForState(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCControlButton", 0, &err) || !tolua_isstring(l, 2, 0, &err)
		|| !tolua_isnumber(l, 3, CCControlStateNormal, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'CCControlButton.setTitleForState'.",&err);
		return 0;
	}
#endif
	CCControlButton *o = (CCControlButton *)tolua_tousertype(l, 1, NULL);
	if(o)o->setTitleForState(CCString::create(tolua_tostring(l, 2, NULL)), tolua_tonumber(l, 3, CCControlStateNormal));
	tolua_pushusertype(l, o, "CCControlButton");
	return 1;
}
#endif //__TOLUA_CCCONTROL__