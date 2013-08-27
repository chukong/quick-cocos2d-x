#ifndef __TOLUA_CCGLPROGRAM_H__
#define __TOLUA_CCGLPROGRAM_H__

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
USING_NS_CC;

//######################################## CCGLProgram ##########################
// CCGLProgram::getUniformLocationForName(const char *n)
static int tolua_CCGLProgram_getUniformLocationForName(lua_State *l){
#if COCOS2D_VERSION >= 0x00020100
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCGLProgram", 0, &err) || !tolua_isstring(l, 2, 0, &err)){
		tolua_error(l,"#ferror in function 'CCGLProgram.getUniformLocationForName'.",&err);
		return 0;
	}
#endif
	CCGLProgram * o = (CCGLProgram *)tolua_tousertype(l, 1, NULL);
	if(o){tolua_pushnumber(l, o->getUniformLocationForName(tolua_tostring(l, 2, "")));}
#endif
	return 1;
}
// CCGLProgram::setUniformLocationWith(const char *with, GLint loc / const char *name, ...)
static int tolua_CCGLProgram_setUniformLocationWith(lua_State *l){
#if COCOS2D_VERSION >= 0x00020100
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCGLProgram", 0, &err) || !tolua_isstring(l, 2, 0, &err) ||
		!(tolua_isnumber(l, 3, 0, &err) || tolua_isstring(l, 3, 0, &err))){
		tolua_error(l,"#ferror in function 'CCGLProgram.setUniformLocationWith'.",&err);
		return 0;
	}
#endif
	CCGLProgram * o = (CCGLProgram *)tolua_tousertype(l, 1, NULL);
	const char * w = tolua_tostring(l, 2, NULL);
	if(o && w){
		GLint loc = tolua_tonumber(l, 3, 0);
		if(loc == 0){loc = o->getUniformLocationForName(tolua_tostring(l, 3, 0));}
		if(strcmp(w, "1i") == 0){		o->setUniformLocationWith1i(loc, (GLint)tolua_tonumber(l, 4, 0));}
		else if(strcmp(w, "2i") == 0){	o->setUniformLocationWith2i(loc, tolua_tonumber(l, 4, 0), tolua_tonumber(l, 5, 0));}
		else if(strcmp(w, "3i") == 0){	o->setUniformLocationWith3i(loc, tolua_tonumber(l, 4, 0), tolua_tonumber(l, 5, 0), tolua_tonumber(l, 6, 0));}
		else if(strcmp(w, "4i") == 0){	o->setUniformLocationWith4i(loc, tolua_tonumber(l, 4, 0), tolua_tonumber(l, 5, 0), tolua_tonumber(l, 6, 0), tolua_tonumber(l, 7, 0));}
		else if(strcmp(w, "2iv") == 0){
			GLint vs[] = {static_cast<GLint>(tolua_tonumber(l, 4, 0)), static_cast<GLint>(tolua_tonumber(l, 5, 0))};
			o->setUniformLocationWith2iv(loc, vs, 2);}
		else if(strcmp(w, "3iv") == 0){
			GLint vs[] = {static_cast<GLint>(tolua_tonumber(l, 4, 0)), static_cast<GLint>(tolua_tonumber(l, 5, 0)),
				static_cast<GLint>(tolua_tonumber(l, 6, 0))};
			o->setUniformLocationWith3iv(loc, vs, 3);}
		else if(strcmp(w, "4iv") == 0){
			GLint vs[] = {static_cast<GLint>(tolua_tonumber(l, 4, 0)), static_cast<GLint>(tolua_tonumber(l, 5, 0)),
				static_cast<GLint>(tolua_tonumber(l, 6, 0)), static_cast<GLint>(tolua_tonumber(l, 7, 0))};
			o->setUniformLocationWith4iv(loc, vs, 4);}
		else if(strcmp(w, "1f") == 0){	o->setUniformLocationWith1f(loc, (GLfloat)tolua_tonumber(l, 4, 0));}
		else if(strcmp(w, "2f") == 0){	o->setUniformLocationWith2f(loc, tolua_tonumber(l, 4, 0), tolua_tonumber(l, 5, 0));}
		else if(strcmp(w, "3f") == 0){	o->setUniformLocationWith3f(loc, tolua_tonumber(l, 4, 0), tolua_tonumber(l, 5, 0), tolua_tonumber(l, 6, 0));}
		else if(strcmp(w, "4f") == 0){	o->setUniformLocationWith4f(loc, tolua_tonumber(l, 4, 0), tolua_tonumber(l, 5, 0), tolua_tonumber(l, 6, 0), tolua_tonumber(l, 7, 0));}
		else if(strcmp(w, "2fv") == 0){
			GLfloat vs[] = {static_cast<GLfloat>(tolua_tonumber(l, 4, 0)), static_cast<GLfloat>(tolua_tonumber(l, 5, 0))};
			o->setUniformLocationWith2fv(loc, vs, 2);}
		else if(strcmp(w, "3fv") == 0){
			GLfloat vs[] = {static_cast<GLfloat>(tolua_tonumber(l, 4, 0)), static_cast<GLfloat>(tolua_tonumber(l, 5, 0)),
				static_cast<GLfloat>(tolua_tonumber(l, 6, 0))};
			o->setUniformLocationWith3fv(loc, vs, 3);}
		else if(strcmp(w, "4fv") == 0){
			GLfloat vs[] = {static_cast<GLfloat>(tolua_tonumber(l, 4, 0)), static_cast<GLfloat>(tolua_tonumber(l, 5, 0)),
				static_cast<GLfloat>(tolua_tonumber(l, 6, 0)), static_cast<GLfloat>(tolua_tonumber(l, 7, 0))};
			o->setUniformLocationWith4fv(loc, vs, 4);}
		else if(strcmp(w, "m4fv") == 0){
			GLfloat vs[] = {static_cast<GLfloat>(tolua_tonumber(l, 4, 0)), static_cast<GLfloat>(tolua_tonumber(l, 5, 0)),
				static_cast<GLfloat>(tolua_tonumber(l, 6, 0)), static_cast<GLfloat>(tolua_tonumber(l, 7, 0))};
			o->setUniformLocationWithMatrix4fv(loc, vs, 4);}
	}
	tolua_pushusertype(l, o, "CCGLProgram");
#endif
	return 1;
}
// CCGLProgram::addAttribute(const char* attributeName, GLuint index)
static int tolua_CCGLProgram_addAttribute(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCGLProgram", 0, &err) || !tolua_isstring(l, 2, 0, &err) || !tolua_isnumber(l, 3, 0, &err)){
		tolua_error(l,"#ferror in function 'CCGLProgram.addAttribute'.",&err);
		return 0;
	}
#endif
	CCGLProgram * o = (CCGLProgram *)tolua_tousertype(l, 1, NULL);
	if(o){o->addAttribute(tolua_tostring(l, 2, NULL), tolua_tonumber(l, 3, 0));}
	tolua_pushusertype(l, o, "CCGLProgram");
	return 1;
}

#endif //__TOLUA_CCGLPROGRAM_H__