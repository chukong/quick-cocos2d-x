#ifndef __TOLUA_CCSCALE9SPRITE__
#define __TOLUA_CCSCALE9SPRITE__

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "CCBProxy.h"

//######################################## CCScale9Sprite ##########################
// CCScale9Sprite::create(const char *file, CCRect *rect = CCRectZero, CCRect capInsets = CCRectZero)
static int tolua_CCScale9Sprite_create(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CCScale9Sprite", 0, &err) || !tolua_isstring(l, 2, 0, &err) ||
		!(tolua_isnoobj(l, 3, &err) || tolua_isusertype(l, 3, "CCRect", 0, &err)) ||
		!(tolua_isnoobj(l, 4, &err) || tolua_isusertype(l, 4, "CCRect", 0, &err))){
		tolua_error(l,"#ferror in function 'CCScale9Sprite.create'.",&err);
		return 0;
	}
#endif
	const char *f = tolua_tostring(l, 2, NULL);
	CCRect *r = (CCRect *)tolua_tousertype(l, 3, NULL);
	CCRect *insets = (CCRect *)tolua_tousertype(l, 4, NULL);
	CCScale9Sprite *o;
	if(f)o = CCScale9Sprite::create(f, r? *r : CCRectZero, insets? *insets : CCRectZero);
	else o = CCScale9Sprite::create();
	tolua_pushusertype(l, o, "CCScale9Sprite");
	return 1;
}
// CCScale9Sprite::createWithSpriteFrame(CCSpriteFrame *f, CCRect capInsets = CCRectZero)
static int tolua_CCScale9Sprite_createWithSpriteFrame(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CCScale9Sprite", 0, &err) ||
		!tolua_isusertype(l, 2, "CCSpriteFrame", 0, &err) ||
		!(tolua_isnoobj(l, 3, &err) || tolua_isusertype(l, 3, "CCRect", 0, &err))){
		tolua_error(l,"#ferror in function 'createWithSpriteFrame'.",&err);
		return 0;
	}
#endif
	CCSpriteFrame *s = (CCSpriteFrame *)tolua_tousertype(l, 2, NULL);
	CCRect *insets = (CCRect *)tolua_tousertype(l, 3, NULL);
	CCScale9Sprite *o;
	if(s)o = CCScale9Sprite::createWithSpriteFrame(s, insets? *insets : CCRectZero);
	else o = CCScale9Sprite::create();
	tolua_pushusertype(l, o, "CCScale9Sprite");
	return 1;
}
// CCScale9Sprite::setContentSize(number, number)
// CCScale9Sprite::setContentSize(CCSize *)
static int tolua_CCScale9Sprite_setContentSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err)){
		tolua_error(l,"#ferror in function 'setContentSize'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	if(o){
		if(tolua_isusertype(l, 2, "CCSize", NULL, NULL)){
			o->setContentSize(*static_cast<CCSize *>(tolua_tousertype(l, 2, NULL)));
		}else{
			o->setContentSize(CCSize(tolua_tonumber(l, 2, 0), tolua_tonumber(l, 3, 0)));
		}
	}
	tolua_pushusertype(l, o, "CCScale9Sprite");
	return 1;
}
// CCScale9Sprite::getCapInsets()
static int tolua_CCScale9Sprite_getCapInsets(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err)){
		tolua_error(l,"#ferror in function 'getCapInsets'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushusertype(l, Mtolua_new((CCRect)(o->getCapInsets())), "CCRect");
	return 1;
}
// CCScale9Sprite::setCapInsets(CCRect *)
static int tolua_CCScale9Sprite_setCapInsets(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err) || !tolua_isusertype(l, 2, "CCRect", 0, &err)){
		tolua_error(l,"#ferror in function 'setCapInsets'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	CCRect *r = (CCRect *)tolua_tousertype(l, 2, 0);
	if(o && r){o->setCapInsets(*r);}
	tolua_pushusertype(l, o, "CCScale9Sprite");
	return 1;
}
// CCScale9Sprite::getColor()
static int tolua_CCScale9Sprite_getColor(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err)){
		tolua_error(l,"#ferror in function 'getColor'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushusertype(l, Mtolua_new((ccColor3B)(o->getColor())), "ccColor3B");
	return 1;
}
// CCScale9Sprite::setColor(ccColor3B *)
static int tolua_CCScale9Sprite_setColor(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err) || !tolua_isusertype(l, 2, "ccColor3B", 0, &err)){
		tolua_error(l,"#ferror in function 'setColor'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	ccColor3B *c = (ccColor3B *)tolua_tousertype(l, 2, 0);
	if(o && c)o->setColor(*c);
	tolua_pushusertype(l, o, "CCScale9Sprite");
	return 1;
}
// CCScale9Sprite::getOpacity()
static int tolua_CCScale9Sprite_getOpacity(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScale9Sprite.getOpacity'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushnumber(l, o->getOpacity());
	return 1;
}
// CCScale9Sprite::setOpacity(number)
static int tolua_CCScale9Sprite_setOpacity(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err) || !tolua_isnumber(l, 2, 255, &err)){
		tolua_error(l,"#ferror in function 'CCScale9Sprite.setOpacity'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	if(o)o->setOpacity(tolua_tonumber(l, 2, 255));
	tolua_pushusertype(l, o, "CCScale9Sprite");
	return 1;
}
// CCScale9Sprite::isOpacityModifyRGB
static int tolua_CCScale9Sprite_isOpacityModifyRGB(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err)){
		tolua_error(l,"#ferror in function 'isOpacityModifyRGB'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	if(o)tolua_pushboolean(l, o->isOpacityModifyRGB());
	return 1;
}
// CCScale9Sprite::setOpacityModifyRGB(bool)
static int tolua_CCScale9Sprite_setOpacityModifyRGB(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err) || !tolua_isboolean(l, 2, true, &err)){
		tolua_error(l,"#ferror in function 'setOpacityModifyRGB'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	if(o)o->setOpacityModifyRGB(tolua_toboolean(l, 2, true) > 0);
	tolua_pushusertype(l, o, "CCScale9Sprite");
	return 1;
}
// CCScale9Sprite::getPreferredSize()
static int tolua_CCScale9Sprite_getPreferredSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScale9Sprite.getPreferredSize'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	if(o){
		tolua_pushusertype(l, Mtolua_new((CCSize)(o->getPreferredSize())), "CCSize");
	}
	return 1;
}
// CCScale9Sprite::setPreferredSize(CCSize *)
static int tolua_CCScale9Sprite_setPreferredSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err) || !tolua_isusertype(l, 2, "CCSize", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScale9Sprite.setPreferredSize'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	if(o){
		CCSize *s = (CCSize *)tolua_tousertype(l, 2, NULL);
		o->setPreferredSize(s? *s : CCSizeZero);
	}
	tolua_pushusertype(l, o, "CCScale9Sprite");
	return 1;
}
// CCScale9Sprite::copyPreferredSize(CCScale9Sprite *)
static int tolua_CCScale9Sprite_copyPreferredSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err) || !tolua_isusertype(l, 2, "CCScale9Sprite", 0, &err)){
		tolua_error(l,"#ferror in function 'CCScale9Sprite.copyPreferredSize'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL),
		*t = (CCScale9Sprite *)tolua_tousertype(l, 2, NULL);
	if(o && t){o->setPreferredSize(t->getPreferredSize());}
	tolua_pushusertype(l, o, "CCScale9Sprite");
	return 1;
}
// CCScale9Sprite::setSpriteFrame(CCSpriteFrame *)
static int tolua_CCScale9Sprite_setSpriteFrame(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err) || !tolua_isusertype(l, 2, "CCSpriteFrame", 0, &err)){
		tolua_error(l,"#ferror in function 'setSpriteFrame'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	if(o)o->setSpriteFrame((CCSpriteFrame *)tolua_tousertype(l, 2, NULL));
	tolua_pushusertype(l, o, "CCScale9Sprite");
	return 1;
}
// CCScale9Sprite::resizableSpriteWithCapInsets(CCRect *)
static int tolua_CCScale9Sprite_resizableSpriteWithCapInsets(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err) || !tolua_isusertype(l, 2, "CCRect", 0, &err)){
		tolua_error(l,"#ferror in function 'resizableSpriteWithCapInsets'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	CCRect *r = (CCRect *)tolua_tousertype(l, 2, 0);
	if(o){tolua_pushusertype(l, o->resizableSpriteWithCapInsets(r? *r : o->getCapInsets()), "CCScale9Sprite");}
	return 1;
}
// CCScale9Sprite::updateWithBatchNode(CCSpriteBatchNode *, CCRect *, bool, CCRect *)
static int tolua_CCScale9Sprite_updateWithBatchNode(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCScale9Sprite", 0, &err) || !tolua_isusertype(l, 2, "CCSpriteBatchNode", 0, &err)
		|| !tolua_isusertype(l, 3, "CCRect", 0, &err) || !tolua_isboolean(l, 4, false, &err)
		|| !tolua_isusertype(l, 5, "CCRect", 0, &err)){
		tolua_error(l,"#ferror in function 'updateWithBatchNode'.",&err);
		return 0;
	}
#endif
	CCScale9Sprite *o = (CCScale9Sprite *)tolua_tousertype(l, 1, NULL);
	bool r = false;
	if(o){
		CCRect *rect = (CCRect *)tolua_tousertype(l, 3, 0),
			*ci = (CCRect *)tolua_tousertype(l, 5, 0);
		r = o->updateWithBatchNode((CCSpriteBatchNode *)tolua_tousertype(l, 2, NULL),
			rect? *rect : CCRectMake(0, 0, 0, 0),
			tolua_toboolean(l, 4, false) > 0,
			ci? *ci : o->getCapInsets());
	}
	tolua_pushboolean(l, r);
	return 1;
}

#endif //__TOLUA_CCSCALE9SPRITE__
