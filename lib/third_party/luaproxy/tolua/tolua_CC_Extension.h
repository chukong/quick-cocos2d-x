#pragma once
#ifndef __TOLUA_CC_EXTENSION_H__
#define __TOLUA_CC_EXTENSION_H__

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "tolua_CCBAnimationManager.h"
#include "tolua_CCScrollView.h"
#include "tolua_CCTableView.h"
#include "tolua_CCGLProgram.h"

//######################################## CCPhysicsWorld ##########################
//######################################## CCPhysicsSprite ##########################
//CCDrawNode
static int tolua_CCDrawNode_create(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CCDrawNode", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCDrawNode.create'.",&err);
		return 0;
	}
#endif
	CCDrawNode *o = CCDrawNode::create();
	tolua_pushusertype(l, o, "CCDrawNode");
	return 1;
}

static int tolua_CCDrawNode_drawDot(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCDrawNode", 0, &err) || !tolua_isusertype(l, 2, "CCPoint", 0, &err)
		|| !tolua_isnumber(l, 3, 0, &err) || !tolua_isusertype(l, 4, "ccColor4F", 0, &err)){
		tolua_error(l,"#ferror in function 'CCDrawNode.drawDot'.",&err);
		return 0;
	}
#endif
	CCDrawNode *o = (CCDrawNode *)tolua_tousertype(l, 1, NULL);
	CCPoint p = *((CCPoint *)tolua_tousertype(l, 2, NULL));
	ccColor4F c = *((ccColor4F *)tolua_tousertype(l, 4, NULL));
	o->drawDot( p, (float)tolua_tonumber(l, 3, 0), c );
	return 1;
}

static int tolua_CCDrawNode_drawSegment(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCDrawNode", 0, &err) || !tolua_isusertype(l, 2, "CCPoint", 0, &err)
		|| !tolua_isusertype(l, 3, "CCPoint", 0, &err) || !tolua_isnumber(l, 4, 0, &err) || !tolua_isusertype(l, 5, "ccColor4F", 0, &err)){
		tolua_error(l,"#ferror in function 'CCDrawNode.drawSegment'.",&err);
		return 0;
	}
#endif
	CCDrawNode *o = (CCDrawNode *)tolua_tousertype(l, 1, NULL);
	CCPoint fp = *((CCPoint *)tolua_tousertype(l, 2, NULL));
	CCPoint tp = *((CCPoint *)tolua_tousertype(l, 3, NULL));
	ccColor4F c = *((ccColor4F *)tolua_tousertype(l, 5, NULL));
	o->drawSegment(fp, tp, (float)tolua_tonumber(l, 4, 0), c);
	return 1;
}

static int tolua_CCDrawNode_clear(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCDrawNode", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCDrawNode.clear'.",&err);
		return 0;
	}
#endif
	CCDrawNode *o = (CCDrawNode *)tolua_tousertype(l, 1, NULL);
	o->clear();
	return 1;
}

static int tolua_CCDrawNode_getBlendFunc(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCDrawNode", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCDrawNode.getBlendFunc'.",&err);
		return 0;
	}
#endif
 {
  CCDrawNode *o = (CCDrawNode *)tolua_tousertype(l, 1, NULL);
#ifndef TOLUA_RELEASE
  if (!o) tolua_error(l,"invalid 'self' in function 'getBlendFunc'", NULL);
#endif
  {
   ccBlendFunc tolua_ret = (ccBlendFunc)  o->getBlendFunc();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccBlendFunc)(tolua_ret));
     tolua_pushusertype(l,tolua_obj,"ccBlendFunc");
    tolua_register_gc(l,lua_gettop(l));
#else
    void* tolua_obj = tolua_copy(l,(void*)&tolua_ret,sizeof(ccBlendFunc));
     tolua_pushusertype(l,tolua_obj,"ccBlendFunc");
    tolua_register_gc(l,lua_gettop(l));
#endif
   }
  }
 }
 return 1;
}

static int tolua_CCDrawNode_setBlendFunc(lua_State *l){
#ifndef TOLUA_RELEASE
 tolua_Error err;
 if (!tolua_isusertype(l, 1, "CCDrawNode", 0, &err) || (tolua_isvaluenil(l, 2, &err) || !tolua_isusertype(l, 2, "ccBlendFunc", 0, &err))
	 || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCDrawNode.setBlendFunc'.",&err);
		return 0;
	}
#endif
	CCDrawNode *o = (CCDrawNode *)tolua_tousertype(l, 1, NULL);
	o->setBlendFunc( *((ccBlendFunc *)tolua_tousertype(l, 2, NULL)) );
	return 1;
}



TOLUA_API int tolua_CC_Extension_open(lua_State* l){
	tolua_open(l);
	tolua_usertype(l, "CCBAnimationManager");
	tolua_usertype(l, "CCBFile");
	tolua_usertype(l, "CCBReader");
	tolua_usertype(l, "CCBSequence");
	tolua_usertype(l, "CCScrollView");
	tolua_usertype(l, "CCTableView");
	tolua_usertype(l, "CCTableViewCell");
	tolua_usertype(l, "CCTableViewDataSource");
	tolua_usertype(l, "CCTableViewDelegate");
	tolua_usertype(l, "CCDrawNode");
	tolua_module(l, NULL, 0);
	tolua_beginmodule(l, NULL);
		tolua_cclass(l,"CCBAnimationManager","CCBAnimationManager","CCObject",NULL);
		tolua_beginmodule(l,"CCBAnimationManager");
			tolua_function(l, "pickFromNode", tolua_CCBAnimationManager_pickFromNode);
			tolua_function(l, "getSequences", tolua_CCBAnimationManager_getSequences);
			tolua_function(l, "getAutoPlaySequenceId", tolua_CCBAnimationManager_getAutoPlaySequenceId);
			tolua_function(l, "setAutoPlaySequenceId", tolua_CCBAnimationManager_setAutoPlaySequenceId);
			tolua_function(l, "getRootNode", tolua_CCBAnimationManager_getRootNode);
			tolua_function(l, "setRootNode", tolua_CCBAnimationManager_setRootNode);
			tolua_function(l, "getRootContainerSize", tolua_CCBAnimationManager_getRootContainerSize);
			tolua_function(l, "setRootContainerSize", tolua_CCBAnimationManager_setRootContainerSize);
			tolua_function(l, "getRunningSequenceName", tolua_CCBAnimationManager_getRunningSequenceName);
			tolua_function(l, "getContainerSize", tolua_CCBAnimationManager_getContainerSize);
			tolua_function(l, "addNode", tolua_CCBAnimationManager_addNode);
			tolua_function(l, "setBaseValue", tolua_CCBAnimationManager_setBaseValue);
			tolua_function(l, "runAnimations", tolua_CCBAnimationManager_runAnimations);
			tolua_function(l, "runAnimationsForSequenceIdTweenDuration", tolua_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration);
		tolua_endmodule(l);
		tolua_cclass(l,"CCBFile","CCBFile","CCNode",NULL);
		tolua_beginmodule(l,"CCBFile");
			tolua_function(l, "getCCBFileNode", tolua_CCBFile_getCCBFileNode);
			tolua_function(l, "setCCBFileNode", tolua_CCBFile_setCCBFileNode);
		tolua_endmodule(l);
		tolua_cclass(l,"CCBReader","CCBReader","CCObject",NULL);
		tolua_beginmodule(l,"CCBReader");
//			tolua_function(l,"load",tolua_CCBReader_load);
		tolua_endmodule(l);
		tolua_cclass(l,"CCBSequence","CCBSequence","CCObject",NULL);
		tolua_beginmodule(l,"CCBSequence");
			tolua_function(l,"getDuration",tolua_CCBSequence_getDuration);
			tolua_function(l,"setDuration",tolua_CCBSequence_setDuration);
			tolua_function(l,"getName",tolua_CCBSequence_getName);
			tolua_function(l,"setName",tolua_CCBSequence_setName);
			tolua_function(l,"getSequenceId",tolua_CCBSequence_getSequenceId);
			tolua_function(l,"setSequenceId",tolua_CCBSequence_setSequenceId);
			tolua_function(l,"getChainedSequenceId",tolua_CCBSequence_getChainedSequenceId);
			tolua_function(l,"setChainedSequenceId",tolua_CCBSequence_setChainedSequenceId);
		tolua_endmodule(l);

    
    tolua_constant(l, "kCCScrollViewDirectionNone", kCCScrollViewDirectionNone);
		tolua_constant(l, "kCCScrollViewDirectionHorizontal", kCCScrollViewDirectionHorizontal);
		tolua_constant(l, "kCCScrollViewDirectionVertical", kCCScrollViewDirectionVertical);
		tolua_constant(l, "kCCScrollViewDirectionBoth", kCCScrollViewDirectionBoth);
		tolua_cclass(l, "CCScrollView", "CCScrollView", "CCLayer", NULL);
		tolua_beginmodule(l, "CCScrollView");
			tolua_function(l, "create", tolua_CCScrollView_create);
			tolua_function(l, "isBounceable", tolua_CCScrollView_isBounceable);
			tolua_function(l, "setBounceable", tolua_CCScrollView_setBounceable);
			tolua_function(l, "addChild", tolua_CCScrollView_addChild);
			tolua_function(l, "isClippingToBounds", tolua_CCScrollView_isClippingToBounds);
			tolua_function(l, "setClippingToBounds", tolua_CCScrollView_setClippingToBounds);
			tolua_function(l, "getContainer", tolua_CCScrollView_getContainer);
			tolua_function(l, "setContainer", tolua_CCScrollView_setContainer);
			tolua_function(l, "getContentOffset", tolua_CCScrollView_getContentOffset);
			tolua_function(l, "setContentOffset", tolua_CCScrollView_setContentOffset);
			tolua_function(l, "setContentOffsetInDuration", tolua_CCScrollView_setContentOffsetInDuration);
			tolua_function(l, "getContentSize", tolua_CCScrollView_getContentSize);
			tolua_function(l, "setContentSize", tolua_CCScrollView_setContentSize);
			tolua_function(l, "getDirection", tolua_CCScrollView_getDirection);
			tolua_function(l, "setDirection", tolua_CCScrollView_setDirection);
			tolua_function(l, "isDragging", tolua_CCScrollView_isDragging);
			tolua_function(l, "isNodeVisible", tolua_CCScrollView_isNodeVisible);
			tolua_function(l, "isTouchMoved", tolua_CCScrollView_isTouchMoved);
			tolua_function(l, "getViewSize", tolua_CCScrollView_getViewSize);
			tolua_function(l, "setViewSize", tolua_CCScrollView_setViewSize);
			tolua_function(l, "getZoomScale", tolua_CCScrollView_getZoomScale);
			tolua_function(l, "setZoomScale", tolua_CCScrollView_setZoomScale);
			tolua_function(l, "setZoomScaleInDuration", tolua_CCScrollView_setZoomScaleInDuration);
		tolua_endmodule(l);
		tolua_constant(l, "kCCTableViewFillTopDown", kCCTableViewFillTopDown);
		tolua_constant(l, "kCCTableViewFillBottomUp", kCCTableViewFillBottomUp);
		tolua_cclass(l, "CCTableViewDataSource", "CCTableViewDataSource", "", NULL);
		tolua_cclass(l, "CCTableViewDelegate", "CCTableViewDelegate", "", NULL);
		tolua_cclass(l, "CCTableView", "CCTableView", "CCScrollView", NULL);
		tolua_beginmodule(l, "CCTableView");
			tolua_function(l, "create", tolua_CCTableView_create);
			tolua_function(l, "getDataSource", tolua_CCTableView_getDataSource);
			tolua_function(l, "setDataSource", tolua_CCTableView_setDataSource);
			tolua_function(l, "getDelegate", tolua_CCTableView_getDelegate);
			tolua_function(l, "setDelegate", tolua_CCTableView_setDelegate);
			tolua_function(l, "getVerticalFillOrder", tolua_CCTableView_getVerticalFillOrder);
			tolua_function(l, "setVerticalFillOrder", tolua_CCTableView_setVerticalFillOrder);
			tolua_function(l, "updateCellAtIndex", tolua_CCTableView_updateCellAtIndex);
			tolua_function(l, "insertCellAtIndex", tolua_CCTableView_insertCellAtIndex);
			tolua_function(l, "removeCellAtIndex", tolua_CCTableView_removeCellAtIndex);
			tolua_function(l, "reloadData", tolua_CCTableView_reloadData);
			tolua_function(l, "dequeueCell", tolua_CCTableView_dequeueCell);
			tolua_function(l, "cellAtIndex", tolua_CCTableView_cellAtIndex);
		tolua_endmodule(l);
		tolua_cclass(l, "CCTableViewCell", "CCTableViewCell", "CCNode", NULL);
		tolua_beginmodule(l, "CCTableViewCell");
			tolua_function(l, "create", tolua_CCTableViewCell_create);
			tolua_function(l, "getIdx", tolua_CCTableViewCell_getIdx);
			tolua_function(l, "setIdx", tolua_CCTableViewCell_setIdx);
			tolua_function(l, "reset", tolua_CCTableViewCell_reset);
			tolua_function(l, "getObjectID", tolua_CCTableViewCell_getObjectID);
			tolua_function(l, "setObjectID", tolua_CCTableViewCell_setObjectID);
		tolua_endmodule(l);

		tolua_cclass(l, "CCGLProgram", "CCGLProgram", "CCObject", NULL);
		tolua_beginmodule(l, "CCGLProgram");
			tolua_function(l, "addAttribute", tolua_CCGLProgram_addAttribute);
			tolua_function(l, "getUniformLocationForName", tolua_CCGLProgram_getUniformLocationForName);
			tolua_function(l, "setUniformLocationWith", tolua_CCGLProgram_setUniformLocationWith);
		tolua_endmodule(l);

		tolua_cclass(l, "CCDrawNode", "CCDrawNode", "CCNode", NULL);
		tolua_beginmodule(l, "CCDrawNode");
			tolua_function(l, "create", tolua_CCDrawNode_create);
			tolua_function(l, "drawDot", tolua_CCDrawNode_drawDot);
			tolua_function(l, "drawSegment", tolua_CCDrawNode_drawSegment);
			tolua_function(l, "clear", tolua_CCDrawNode_clear);
			tolua_function(l, "getBlendFunc", tolua_CCDrawNode_getBlendFunc);
			tolua_function(l, "setBlendFunc", tolua_CCDrawNode_setBlendFunc);
		tolua_endmodule(l);
	tolua_endmodule(l);
	return 1;
}
#endif // __TOLUA_CC_EXTENSION_H__
