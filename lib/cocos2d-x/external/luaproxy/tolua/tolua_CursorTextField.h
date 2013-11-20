#ifndef __TOLUA_CURSORTEXTFIELD_H__
#define __TOLUA_CURSORTEXTFIELD_H__

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "../ui/CursorTextField.h"

//######################################## CursorTextField ##########################
//CursorTextField::create
static int tolua_CursorTextField_create(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CursorTextField", 0, &err) || !tolua_isstring(l, 2, 0, &err)
		|| !tolua_isnumber(l, 3, 0, &err) || !tolua_isnoobj(l, 4, &err)){
		tolua_error(l,"#ferror in function 'CursorTextField.create'.",&err);
		return 0;
	}
#endif
	tolua_pushusertype(l, CursorTextField::create(tolua_tostring(l, 2, "Arial"), tolua_tonumber(l, 3, 16)), "CursorTextField");
	return 1;
}
//CursorTextField::createWithPlaceHolder
static int tolua_CursorTextField_createWithPlaceHolder(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CursorTextField", 0, &err) || !tolua_isstring(l, 2, 0, &err)
		|| !tolua_isstring(l, 3, 0, &err) || !tolua_isnumber(l, 4, 0, &err) || !tolua_isnoobj(l, 5, &err)){
		tolua_error(l,"#ferror in function 'createWithPlaceHolder'.",&err);
		return 0;
	}
#endif
	tolua_pushusertype(l, CursorTextField::createWithPlaceHolder(
		tolua_tostring(l, 2, ""), tolua_tostring(l, 3, "Arial"), tolua_tonumber(l, 4, 16)), "CursorTextField");
	return 1;
}
//CursorTextField::setColor
static int tolua_CursorTextField_setColor(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CursorTextField", 0, &err) || !tolua_isusertype(l, 2, "ccColor3B", 0, &err)
		|| !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'setColor'.",&err);
		return 0;
	}
#endif
	CursorTextField *p = (CursorTextField *)tolua_tousertype(l, 1, NULL);
	if(p)p->setColor(*((ccColor3B *)tolua_tousertype(l, 2, NULL)));
	tolua_pushusertype(l, p, "CursorTextField");
	return 1;
}
//CursorTextField::getDesignedSize
static int tolua_CursorTextField_getDesignedSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CursorTextField", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CursorTextField.getDesignedSize'.",&err);
		return 0;
	}
#endif
	CursorTextField *p = (CursorTextField *)tolua_tousertype(l, 1, NULL);
	if(p)tolua_pushusertype(l, Mtolua_new((CCSize)(p->getDesignedSize())), "CCSize");
	return 1;
}
//CursorTextField::setDesignedSize
static int tolua_CursorTextField_setDesignedSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CursorTextField", 0, &err) || !tolua_isusertype(l, 2, "CCSize", 0, &err)
		|| !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CursorTextField.setDesignedSize'.",&err);
		return 0;
	}
#endif
	CursorTextField *p = (CursorTextField *)tolua_tousertype(l, 1, NULL);
	if(p)p->setDesignedSize(*((CCSize *)tolua_tousertype(l, 2, NULL)));
	tolua_pushusertype(l, p, "CursorTextField");
	return 1;
}
//CursorTextField::getMaxLength
static int tolua_CursorTextField_getMaxLength(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CursorTextField", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CursorTextField.getMaxLength'.",&err);
		return 0;
	}
#endif
	CursorTextField *p = (CursorTextField *)tolua_tousertype(l, 1, NULL);
	if(p)tolua_pushnumber(l, p->getMaxLength());
	return 1;
}
//CursorTextField::setMaxLength
static int tolua_CursorTextField_setMaxLength(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CursorTextField", 0, &err) || !tolua_isnumber(l, 2, 0, &err)
		|| !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CursorTextField.setMaxLength'.",&err);
		return 0;
	}
#endif
	CursorTextField *p = (CursorTextField *)tolua_tousertype(l, 1, NULL);
	if(p)p->setMaxLength(tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, p, "CursorTextField");
	return 1;
}
//CursorTextField::isPassword
static int tolua_CursorTextField_isPassword(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CursorTextField", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CursorTextField.isPassword'.",&err);
		return 0;
	}
#endif
	CursorTextField *p = (CursorTextField *)tolua_tousertype(l, 1, NULL);
	if(p)tolua_pushboolean(l, p->isPassword());
	return 1;
}
//CursorTextField::setPassword
static int tolua_CursorTextField_setPassword(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CursorTextField", 0, &err) || !tolua_isboolean(l, 2, 0, &err)
		|| !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CursorTextField.setPassword'.",&err);
		return 0;
	}
#endif
	CursorTextField *p = (CursorTextField *)tolua_tousertype(l, 1, NULL);
	if(p)p->setPassword(tolua_toboolean(l, 2, 0) > 0);
	tolua_pushusertype(l, p, "CursorTextField");
	return 1;
}
//CursorTextField::getRect
static int tolua_CursorTextField_getRect(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CursorTextField", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CursorTextField.getRect'.",&err);
		return 0;
	}
#endif
	CursorTextField *p = (CursorTextField *)tolua_tousertype(l, 1, NULL);
	if(p)tolua_pushusertype(l, Mtolua_new((CCRect)(p->getRect())), "CCRect");
	return 1;
}
//CursorTextField::setString
static int tolua_CursorTextField_setString(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CursorTextField", 0, &err) || !tolua_isstring(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CursorTextField.setString'.",&err);
		return 0;
	}
#endif
	CursorTextField *p = (CursorTextField *)tolua_tousertype(l, 1, NULL);
	if(p)p->setString(tolua_tostring(l, 2, ""));
	tolua_pushusertype(l, p, "CursorTextField");
	return 1;
}

#endif //__TOLUA_CURSORTEXTFIELD_H__