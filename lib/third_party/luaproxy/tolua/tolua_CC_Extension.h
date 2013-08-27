#pragma once
#ifndef __TOLUA_CC_EXTENSION_H__
#define __TOLUA_CC_EXTENSION_H__

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "tolua_CCBAnimationManager.h"
#include "tolua_CCControl.h"
#include "tolua_CCEditBox.h"
#include "tolua_CCScrollView.h"
#include "tolua_CCTableView.h"
#include "tolua_CCScale9Sprite.h"
#include "tolua_CCGLProgram.h"

//######################################## CCBFile ##########################
//CCBFile::getCCBFileNode
static int tolua_CCBFile_getCCBFileNode(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBFile", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCBFile.getCCBFileNode'.",&err);
		return 0;
	}
#endif
	CCBFile *o = (CCBFile *)tolua_tousertype(l, 1, NULL);
	tolua_pushusertype(l, o? o->getCCBFileNode() : 0, "CCNode");
	return 1;
}
//CCBFile::setCCBFileNode
static int tolua_CCBFile_setCCBFileNode(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBFile", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCBFile.setDuration'.",&err);
		return 0;
	}
#endif
	CCBFile *o = (CCBFile *)tolua_tousertype(l, 1, NULL);
	if(o)o->setCCBFileNode((CCNode *)tolua_tousertype(l, 2, 0));
	tolua_pushusertype(l, o, "CCBFile");
	return 1;
}
//######################################## CCBSequence ##########################
//CCBSequence::getDuration
static int tolua_CCBSequence_getDuration(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBSequence", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCBSequence.getDuration'.",&err);
		return 0;
	}
#endif
	CCBSequence *o = (CCBSequence *)tolua_tousertype(l, 1, NULL);
	tolua_pushnumber(l, o? o->getDuration() : 0);
	return 1;
}
//CCBSequence::setDuration
static int tolua_CCBSequence_setDuration(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBSequence", 0, &err) || !tolua_isnumber(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCBSequence.setDuration'.",&err);
		return 0;
	}
#endif
	CCBSequence *o = (CCBSequence *)tolua_tousertype(l, 1, NULL);
	if(o)o->setDuration(tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCBSequence");
	return 1;
}
//CCBSequence::getName
static int tolua_CCBSequence_getName(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBSequence", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCBSequence.getName'.",&err);
		return 0;
	}
#endif
	CCBSequence *o = (CCBSequence *)tolua_tousertype(l, 1, NULL);
	tolua_pushstring(l, o? o->getName() : "");
	return 1;
}
//CCBSequence::setName
static int tolua_CCBSequence_setName(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBSequence", 0, &err) || !tolua_isnumber(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCBSequence.setName'.",&err);
		return 0;
	}
#endif
	CCBSequence *o = (CCBSequence *)tolua_tousertype(l, 1, NULL);
	if(o)o->setName(tolua_tostring(l, 2, ""));
	tolua_pushusertype(l, o, "CCBSequence");
	return 1;
}
//CCBSequence::getSequenceId
static int tolua_CCBSequence_getSequenceId(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBSequence", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCBSequence.getSequenceId'.",&err);
		return 0;
	}
#endif
	CCBSequence *o = (CCBSequence *)tolua_tousertype(l, 1, NULL);
	tolua_pushnumber(l, o? o->getSequenceId() : 0);
	return 1;
}
//CCBSequence::setSequenceId
static int tolua_CCBSequence_setSequenceId(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBSequence", 0, &err) || !tolua_isnumber(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCBSequence.setSequenceId'.",&err);
		return 0;
	}
#endif
	CCBSequence *o = (CCBSequence *)tolua_tousertype(l, 1, NULL);
	if(o)o->setSequenceId(tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCBSequence");
	return 1;
}
//CCBSequence::getChainedSequenceId
static int tolua_CCBSequence_getChainedSequenceId(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBSequence", 0, &err) || !tolua_isnoobj(l, 2, &err)){
		tolua_error(l,"#ferror in function 'CCBSequence.getChainedSequenceId'.",&err);
		return 0;
	}
#endif
	CCBSequence *o = (CCBSequence *)tolua_tousertype(l, 1, NULL);
	tolua_pushnumber(l, o? o->getChainedSequenceId() : 0);
	return 1;
}
//CCBSequence::setChainedSequenceId
static int tolua_CCBSequence_setChainedSequenceId(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBSequence", 0, &err) || !tolua_isnumber(l, 2, 0, &err) || !tolua_isnoobj(l, 3, &err)){
		tolua_error(l,"#ferror in function 'CCBSequence.setChainedSequenceId'.",&err);
		return 0;
	}
#endif
	CCBSequence *o = (CCBSequence *)tolua_tousertype(l, 1, NULL);
	if(o)o->setChainedSequenceId(tolua_tonumber(l, 2, 0));
	tolua_pushusertype(l, o, "CCBSequence");
	return 1;
}


TOLUA_API int tolua_CC_Extension_open(lua_State* l){
	tolua_open(l);
	tolua_usertype(l, "CCBAnimationManager");
	tolua_usertype(l, "CCBFile");
	tolua_usertype(l, "CCBReader");
	tolua_usertype(l, "CCBSequence");
	tolua_usertype(l, "CCControl");
	tolua_usertype(l, "CCControlButton");
	tolua_usertype(l, "CCHttpClient");
	tolua_usertype(l, "CCHttpRequest");
	tolua_usertype(l, "CCHttpResponse");
	tolua_usertype(l, "CCScale9Sprite");
	tolua_usertype(l, "CCScrollView");
	tolua_usertype(l, "CCTableView");
	tolua_usertype(l, "CCTableViewCell");
	tolua_usertype(l, "CCTableViewDataSource");
	tolua_usertype(l, "CCTableViewDelegate");
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
		tolua_cclass(l, "CCControl", "CCControl", "CCLayer", NULL);
		tolua_beginmodule(l, "CCControl");
			tolua_function(l, "isEnabled", tolua_CCControl_isEnabled);
			tolua_function(l, "isHighlighted", tolua_CCControl_isHighlighted);
			tolua_function(l, "isSelected", tolua_CCControl_isSelected);
			tolua_function(l, "setSelected", tolua_CCControl_setSelected);
			tolua_function(l, "getState", tolua_CCControl_getState);
			tolua_function(l, "isTouchInside", tolua_CCControl_isTouchInside);
			tolua_function(l, "getTouchLocation", tolua_CCControl_getTouchLocation);
			tolua_function(l, "hasVisibleParents", tolua_CCControl_hasVisibleParents);
			tolua_function(l, "sendActionsForControlEvents", tolua_CCControl_sendActionsForControlEvents);
		tolua_endmodule(l);
		tolua_constant(l, "CCControlEventTouchDown", CCControlEventTouchDown);
		tolua_constant(l, "CCControlEventTouchDragInside", CCControlEventTouchDragInside);
		tolua_constant(l, "CCControlEventTouchDragOutside", CCControlEventTouchDragOutside);
		tolua_constant(l, "CCControlEventTouchDragEnter", CCControlEventTouchDragEnter);
		tolua_constant(l, "CCControlEventTouchDragExit", CCControlEventTouchDragExit);
		tolua_constant(l, "CCControlEventTouchUpInside", CCControlEventTouchUpInside);
		tolua_constant(l, "CCControlEventTouchUpOutside", CCControlEventTouchUpOutside);
		tolua_constant(l, "CCControlEventTouchCancel", CCControlEventTouchCancel);
		tolua_constant(l, "CCControlEventValueChanged", CCControlEventValueChanged);
		tolua_cclass(l, "CCControlButton", "CCControlButton", "CCControl", NULL);
		tolua_beginmodule(l, "CCControlButton");
			tolua_function(l, "create", tolua_CCControlButton_create);
			tolua_function(l, "getBackgroundSprite", tolua_CCControlButton_getBackgroundSprite);
			tolua_function(l, "setBackgroundSprite", tolua_CCControlButton_setBackgroundSprite);
			tolua_function(l, "getBackgroundSpriteForState", tolua_CCControlButton_getBackgroundSpriteForState);
			tolua_function(l, "setBackgroundSpriteForState", tolua_CCControlButton_setBackgroundSpriteForState);
			tolua_function(l, "setBackgroundSpriteFrameForState", tolua_CCControlButton_setBackgroundSpriteFrameForState);
			tolua_function(l, "getCurrentTitle", tolua_CCControlButton_getCurrentTitle);
			tolua_function(l, "setEnabled", tolua_CCControlButton_setEnabled);
			tolua_function(l, "getLabelAnchorPoint", tolua_CCControlButton_getLabelAnchorPoint);
			tolua_function(l, "setLabelAnchorPoint", tolua_CCControlButton_setLabelAnchorPoint);
			tolua_function(l, "setMargins", tolua_CCControlButton_setMargins);
			tolua_function(l, "getOpacity", tolua_CCControlButton_getOpacity);
			tolua_function(l, "setOpacity", tolua_CCControlButton_setOpacity);
			tolua_function(l, "getPreferredSize", tolua_CCControlButton_getPreferredSize);
			tolua_function(l, "setPreferredSize", tolua_CCControlButton_setPreferredSize);
			tolua_function(l, "isPushed", tolua_CCControlButton_isPushed);
			tolua_function(l, "getTitleLabel", tolua_CCControlButton_getTitleLabel);
			tolua_function(l, "setTitleLabel", tolua_CCControlButton_setTitleLabel);
			tolua_function(l, "getTitleBMFontForState", tolua_CCControlButton_getTitleBMFontForState);
			tolua_function(l, "setTitleBMFontForState", tolua_CCControlButton_setTitleBMFontForState);
			tolua_function(l, "getTitleColorForState", tolua_CCControlButton_getTitleColorForState);
			tolua_function(l, "setTitleColorForState", tolua_CCControlButton_setTitleColorForState);
			tolua_function(l, "getTitleTTFForState", tolua_CCControlButton_getTitleTTFForState);
			tolua_function(l, "setTitleTTFForState", tolua_CCControlButton_setTitleTTFForState);
			tolua_function(l, "getTitleForState", tolua_CCControlButton_getTitleForState);
			tolua_function(l, "setTitleForState", tolua_CCControlButton_setTitleForState);
		tolua_endmodule(l);
		tolua_constant(l, "CCControlStateNormal", CCControlStateNormal);
		tolua_constant(l, "CCControlStateHighlighted", CCControlStateHighlighted);
		tolua_constant(l, "CCControlStateDisabled", CCControlStateDisabled);
		tolua_constant(l, "CCControlStateSelected", CCControlStateSelected);
#ifdef LUAPROXY_CCEDITBOX_ENABLED
		tolua_cclass(l, "CCEditBox", "CCEditBox", "CCControlButton", NULL);
		tolua_beginmodule(l, "CCEditBox");
			tolua_function(l, "create", tolua_CCEditBox_create);
			tolua_function(l, "setContentSize", tolua_CCEditBox_setContentSize);
			tolua_function(l, "setFontColor", tolua_CCEditBox_setFontColor);
			tolua_function(l, "setInputFlag", tolua_CCEditBox_setInputFlag);
			tolua_function(l, "setInputMode", tolua_CCEditBox_setInputMode);
			tolua_function(l, "setMaxLength", tolua_CCEditBox_setMaxLength);
			tolua_function(l, "setPlaceHolder", tolua_CCEditBox_setPlaceHolder);
			tolua_function(l, "setPlaceHolderFontColor", tolua_CCEditBox_setPlaceHolderFontColor);
			tolua_function(l, "setReturnType", tolua_CCEditBox_setReturnType);
			tolua_function(l, "getText", tolua_CCEditBox_getText);
			tolua_function(l, "setText", tolua_CCEditBox_setText);
		tolua_endmodule(l);
		tolua_constant(l, "kEditBoxInputFlagPassword", kEditBoxInputFlagPassword);
		tolua_constant(l, "kEditBoxInputFlagSensitive", kEditBoxInputFlagSensitive);
		tolua_constant(l, "kEditBoxInputFlagInitialCapsWord", kEditBoxInputFlagInitialCapsWord);
		tolua_constant(l, "kEditBoxInputFlagInitialCapsSentence", kEditBoxInputFlagInitialCapsSentence);
		tolua_constant(l, "kEditBoxInputFlagInitialCapsAllCharacters", kEditBoxInputFlagInitialCapsAllCharacters);
		tolua_constant(l, "kEditBoxInputModeAny", kEditBoxInputModeAny);
		tolua_constant(l, "kEditBoxInputModeEmailAddr", kEditBoxInputModeEmailAddr);
		tolua_constant(l, "kEditBoxInputModeNumeric", kEditBoxInputModeNumeric);
		tolua_constant(l, "kEditBoxInputModePhoneNumber", kEditBoxInputModePhoneNumber);
		tolua_constant(l, "kEditBoxInputModeUrl", kEditBoxInputModeUrl);
		tolua_constant(l, "kEditBoxInputModeDecimal", kEditBoxInputModeDecimal);
		tolua_constant(l, "kEditBoxInputModeSingleLine", kEditBoxInputModeSingleLine);
		tolua_constant(l, "kKeyboardReturnTypeDefault", kKeyboardReturnTypeDefault);
		tolua_constant(l, "kKeyboardReturnTypeDone", kKeyboardReturnTypeDone);
		tolua_constant(l, "kKeyboardReturnTypeSend", kKeyboardReturnTypeSend);
		tolua_constant(l, "kKeyboardReturnTypeSearch", kKeyboardReturnTypeSearch);
		tolua_constant(l, "kKeyboardReturnTypeGo", kKeyboardReturnTypeGo);
#endif
		
		tolua_cclass(l, "CCScale9Sprite", "CCScale9Sprite", "CCNode", NULL);
		tolua_beginmodule(l, "CCScale9Sprite");
			tolua_function(l, "create", tolua_CCScale9Sprite_create);
			tolua_function(l, "createWithSpriteFrame", tolua_CCScale9Sprite_createWithSpriteFrame);
			tolua_function(l, "setContentSize", tolua_CCScale9Sprite_setContentSize);
			tolua_function(l, "getCapInsets", tolua_CCScale9Sprite_getCapInsets);
			tolua_function(l, "setCapInsets", tolua_CCScale9Sprite_setCapInsets);
			tolua_function(l, "getColor", tolua_CCScale9Sprite_getColor);
			tolua_function(l, "setColor", tolua_CCScale9Sprite_setColor);
			tolua_function(l, "getOpacity", tolua_CCScale9Sprite_getOpacity);
			tolua_function(l, "setOpacity", tolua_CCScale9Sprite_setOpacity);
			tolua_function(l, "isOpacityModifyRGB", tolua_CCScale9Sprite_isOpacityModifyRGB);
			tolua_function(l, "setOpacityModifyRGB", tolua_CCScale9Sprite_setOpacityModifyRGB);
			tolua_function(l, "getPreferredSize", tolua_CCScale9Sprite_getPreferredSize);
			tolua_function(l, "setPreferredSize", tolua_CCScale9Sprite_setPreferredSize);
			tolua_function(l, "copyPreferredSize", tolua_CCScale9Sprite_copyPreferredSize);
			tolua_function(l, "setSpriteFrame", tolua_CCScale9Sprite_setSpriteFrame);
			tolua_function(l, "resizableSpriteWithCapInsets", tolua_CCScale9Sprite_resizableSpriteWithCapInsets);
			tolua_function(l, "updateWithBatchNode", tolua_CCScale9Sprite_updateWithBatchNode);
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
	tolua_endmodule(l);
	return 1;
}
#endif // __TOLUA_CC_EXTENSION_H__
