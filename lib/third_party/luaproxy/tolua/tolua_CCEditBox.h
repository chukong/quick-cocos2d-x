#ifndef __TOLUA_CCEDITBOX__
#define __TOLUA_CCEDITBOX__

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

//######################################## CCEditBox ##########################
//CCEditBox::create
static int tolua_CCEditBox_create(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CCEditBox", 0, &err) ||
		!tolua_isnumber(l, 2, 0, &err) || !tolua_isnumber(l, 3, 0, &err) ||
		!tolua_isusertype(l, 4, "CCScale9Sprite", 0, &err) || !tolua_isnoobj(l, 5, &err)){
		tolua_error(l,"#ferror in function 'create'.",&err);
		return 0;
	}
#endif
	int w = tolua_tonumber(l, 2, 0), h = tolua_tonumber(l, 3, 0);
	CCScale9Sprite *sp = (CCScale9Sprite *)tolua_tousertype(l, 4, NULL);
	tolua_pushusertype(l, CCEditBox::create(CCSizeMake(w, h), sp), "CCEditBox");
	return 1;
}
//CCEditBox::setContentSize
static int tolua_CCEditBox_setContentSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCEditBox", 0, &err) || !tolua_isnumber(l, 2, 0, &err) ||
		!tolua_isnumber(l, 3, 0, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'setContentSize'.",&err);
		return 0;
	}
#endif
	CCEditBox *o = (CCEditBox *)tolua_tousertype(l, 1, NULL);
	if(o)o->setContentSize(CCSizeMake(tolua_tonumber(l, 2, 0), tolua_tonumber(l, 3, 0)));
	tolua_pushusertype(l, o, "CCEditBox");
	return 1;
}
//CCEditBox::setFontColor
static int tolua_CCEditBox_setFontColor(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCEditBox", 0, &err) || !tolua_isusertype(l, 2, "ccColor3B", 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'setFontColor'.",&err);
		return 0;
	}
#endif
	CCEditBox *o = (CCEditBox *)tolua_tousertype(l, 1, NULL);
	ccColor3B c = *((ccColor3B*)tolua_tousertype(l, 2, NULL));
	if(o)o->setFontColor(c);
	tolua_pushusertype(l, o, "CCEditBox");
	return 1;
}
//CCEditBox::setInputFlag
static int tolua_CCEditBox_setInputFlag(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCEditBox", 0, &err) || !tolua_isnumber(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'setInputFlag'.",&err);
		return 0;
	}
#endif
	CCEditBox *o = (CCEditBox *)tolua_tousertype(l, 1, NULL);
	if(o)o->setInputFlag((EditBoxInputFlag)(int)tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCEditBox");
	return 1;
}
//CCEditBox::setInputMode
static int tolua_CCEditBox_setInputMode(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCEditBox", 0, &err) || !tolua_isnumber(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'setInputMode'.",&err);
		return 0;
	}
#endif
	CCEditBox *o = (CCEditBox *)tolua_tousertype(l, 1, NULL);
	if(o)o->setInputMode((EditBoxInputMode)(int)tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCEditBox");
	return 1;
}
//CCEditBox::setMaxLength
static int tolua_CCEditBox_setMaxLength(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCEditBox", 0, &err) || !tolua_isnumber(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'setMaxLength'.",&err);
		return 0;
	}
#endif
	CCEditBox *o = (CCEditBox *)tolua_tousertype(l, 1, NULL);
	if(o)o->setMaxLength(tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCEditBox");
	return 1;
}
//CCEditBox::setPlaceHolder
static int tolua_CCEditBox_setPlaceHolder(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCEditBox", 0, &err) || !tolua_isstring(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'setPlaceHolder'.",&err);
		return 0;
	}
#endif
	CCEditBox *o = (CCEditBox *)tolua_tousertype(l, 1, NULL);
	if(o)o->setPlaceHolder(tolua_tostring(l, 2, ""));
	tolua_pushusertype(l, o, "CCEditBox");
	return 1;
}
//CCEditBox::setPlaceHolderFontColor
static int tolua_CCEditBox_setPlaceHolderFontColor(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCEditBox", 0, &err) || !tolua_isusertype(l, 2, "ccColor3B", 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'setPlaceHolderFontColor'.",&err);
		return 0;
	}
#endif
	CCEditBox *o = (CCEditBox *)tolua_tousertype(l, 1, NULL);
	ccColor3B c = *((ccColor3B*)tolua_tousertype(l, 2, NULL));
	if(o)o->setPlaceholderFontColor(c);
	tolua_pushusertype(l, o, "CCEditBox");
	return 1;
}
//CCEditBox::setReturnType
static int tolua_CCEditBox_setReturnType(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCEditBox", 0, &err) || !tolua_isnumber(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'setReturnType'.",&err);
		return 0;
	}
#endif
	CCEditBox *o = (CCEditBox *)tolua_tousertype(l, 1, NULL);
	if(o)o->setReturnType((KeyboardReturnType)(int)tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCEditBox");
	return 1;
}
//CCEditBox::getText
static int tolua_CCEditBox_getText(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCEditBox", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'getText'.",&err);
		return 0;
	}
#endif
	CCEditBox *o = (CCEditBox *)tolua_tousertype(l, 1, NULL);
	tolua_pushstring(l, o? o->getText() : "");
	return 1;
}
//CCEditBox::setText
static int tolua_CCEditBox_setText(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCEditBox", 0, &err) ||
		!tolua_isstring(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'setText'.",&err);
		return 0;
	}
#endif
	CCEditBox *o = (CCEditBox *)tolua_tousertype(l, 1, NULL);
	if(o)o->setText(tolua_tostring(l, 2, ""));
	tolua_pushusertype(l, o, "CCEditBox");
	return 1;
}

#endif //__TOLUA_CCEDITBOX__