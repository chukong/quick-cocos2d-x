#ifndef __TOLUA_CCBANIMATIONMANAGER__
#define __TOLUA_CCBANIMATIONMANAGER__

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

//######################################## CCBAnimationManager ##########################
//CCBAnimationManager::pickFromNode(CCNode *n)
static int tolua_CCBAnimationManager_pickFromNode(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertable(l, 1, "CCBAnimationManager", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err)){
		tolua_error(l,"#ferror in function 'CCBAnimationManager.pickFromNode'.",&err);
		return 0;
	}
#endif
	CCNode *n = (CCNode *)tolua_tousertype(l, 2, NULL);
	tolua_pushusertype(l, n? dynamic_cast<CCBAnimationManager *>(n->getUserObject()) : NULL, "CCBAnimationManager");
	return 1;
}
//CCBAnimationManager::getSequences()
static int tolua_CCBAnimationManager_getSequences(lua_State *l){
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	if(m){tolua_pushusertype(l, m->getSequences(), "CCArray");}
	return 1;
}
//CCBAnimationManager::getAutoPlaySequenceId()
static int tolua_CCBAnimationManager_getAutoPlaySequenceId(lua_State *l){
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	tolua_pushnumber(l, m? m->getAutoPlaySequenceId() : -1);
	return 1;
}
//CCBAnimationManager::setAutoPlaySequenceId(int)
static int tolua_CCBAnimationManager_setAutoPlaySequenceId(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBAnimationManager", 0, &err) || !tolua_isnumber(l, 2, -1, &err)){
		tolua_error(l,"#ferror in function 'CCBAnimationManager.setAutoPlaySequenceId'.",&err);
		return 0;
	}
#endif
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	if(m){m->setAutoPlaySequenceId(tolua_tonumber(l, 2, -1));}
	tolua_pushusertype(l, m, "CCBAnimationManager");
	return 1;
}
//CCBAnimationManager::getRootNode()
static int tolua_CCBAnimationManager_getRootNode(lua_State *l){
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	tolua_pushusertype(l, m? m->getRootNode() : NULL, "CCNode");
	return 1;
}
//CCBAnimationManager::setRootNode(CCNode *)
static int tolua_CCBAnimationManager_setRootNode(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBAnimationManager", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err)){
		tolua_error(l,"#ferror in function 'CCBAnimationManager.setRootNode'.",&err);
		return 0;
	}
#endif
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	if(m){m->setRootNode((CCNode *)tolua_tousertype(l, 2, NULL));}
	tolua_pushusertype(l, m, "CCBAnimationManager");
	return 1;
}
//CCBAnimationManager::getRootContainerSize()
static int tolua_CCBAnimationManager_getRootContainerSize(lua_State *l){
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	tolua_pushusertype(l, Mtolua_new((CCSize)(m? m->getRootContainerSize() : CCSizeZero)), "CCSize");
	return 1;
}
//CCBAnimationManager::setRootContainerSize(CCSize *)
static int tolua_CCBAnimationManager_setRootContainerSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBAnimationManager", 0, &err) || !tolua_isusertype(l, 2, "CCSize", 0, &err)){
		tolua_error(l,"#ferror in function 'CCBAnimationManager.setRootContainerSize'.",&err);
		return 0;
	}
#endif
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	if(m){m->setRootContainerSize(*(CCSize *)tolua_tousertype(l, 2, NULL));}
	tolua_pushusertype(l, m, "CCBAnimationManager");
	return 1;
}
//CCBAnimationManager::getRunningSequenceName()
static int tolua_CCBAnimationManager_getRunningSequenceName(lua_State *l){
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	tolua_pushstring(l, m? m->getRunningSequenceName() : "");
	return 1;
}
//CCBAnimationManager::getContainerSize(CCNode *p)
static int tolua_CCBAnimationManager_getContainerSize(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBAnimationManager", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err)){
		tolua_error(l,"#ferror in function 'CCBAnimationManager.getContainerSize'.",&err);
		return 0;
	}
#endif
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	CCNode *p = (CCNode *)tolua_tousertype(l, 2, NULL);
	tolua_pushusertype(l, Mtolua_new((CCSize)(m && p? m->getContainerSize(p) : CCSizeZero)), "CCSize");
	return 1;
}
//CCBAnimationManager::addNode(CCNode *p, CCDictionary *d)
static int tolua_CCBAnimationManager_addNode(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBAnimationManager", 0, &err) || !tolua_isusertype(l, 2, "CCNode", 0, &err)
		|| !tolua_isusertype(l, 3, "CCDictionary", 0, &err)){
		tolua_error(l,"#ferror in function 'CCBAnimationManager.addNode'.",&err);
		return 0;
	}
#endif
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	CCNode *p = (CCNode *)tolua_tousertype(l, 2, NULL);
	CCDictionary *d = (CCDictionary *)tolua_tousertype(l, 3, NULL);
	if(m && p && d){m->addNode(p, d);}
	tolua_pushusertype(l, m, "CCBAnimationManager");
	return 1;
}
//CCBAnimationManager::setBaseValue(CCObject *o, CCNode *n, char *p)
static int tolua_CCBAnimationManager_setBaseValue(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBAnimationManager", 0, &err) || !tolua_isusertype(l, 2, "CCObject", 0, &err)
		|| !tolua_isusertype(l, 3, "CCNode", 0, &err) || !tolua_isstring(l, 4, 0, &err)){
		tolua_error(l,"#ferror in function 'CCBAnimationManager.setBaseValue'.",&err);
		return 0;
	}
#endif
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	CCObject *o = (CCObject *)tolua_tousertype(l, 2, NULL);
	CCNode *n = (CCNode *)tolua_tousertype(l, 3, NULL);
	const char *p = tolua_tostring(l, 4, NULL);
	if(m && o && n && p){m->setBaseValue(o, n, p);}
	tolua_pushusertype(l, m, "CCBAnimationManager");
	return 1;
}
//CCBAnimationManager::runAnimations(char *n, float dur=0) int seqId
static int tolua_CCBAnimationManager_runAnimations(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBAnimationManager", 0, &err) || !tolua_isstring(l, 2, 0, &err) ||
		!(tolua_isnoobj(l, 3, &err) || tolua_isnumber(l, 3, 0, &err))){
		tolua_error(l,"#ferror in function 'CCBAnimationManager.runAnimations'.",&err);
		return 0;
	}
#endif
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	int seqId = -1;
	if(m){
		const char *n = tolua_tostring(l, 2, "");
		CCObject *pElement = NULL;
		CCARRAY_FOREACH(m->getSequences(), pElement){
			CCBSequence *seq = (CCBSequence*)pElement;
			if(strcmp(n, seq->getName()) == 0){
				seqId = seq->getSequenceId();
				break;
			}
		}
		if(seqId >= 0){
			float dur = tolua_tonumber(l, 3, 0);
#if COCOS2D_VERSION < 0x00020100
			m->runAnimations(seqId, dur);
#else
			m->runAnimationsForSequenceIdTweenDuration(seqId, dur);
#endif
		}
	}
	tolua_pushnumber(l, seqId);
	return 1;
}
//CCBAnimationManager::runAnimationsForSequenceIdTweenDuration(int seqId, float dur=0)
static int tolua_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration(lua_State *l){
#ifndef TOLUA_RELEASE
	tolua_Error err;
	if(!tolua_isusertype(l, 1, "CCBAnimationManager", 0, &err) || !tolua_isnumber(l, 2, -1, &err) ||
		!(tolua_isnoobj(l, 3, &err) || tolua_isnumber(l, 3, 0, &err))){
		tolua_error(l,"#ferror in function 'CCBAnimationManager.runAnimationsForSequenceIdTweenDuration'.",&err);
		return 0;
	}
#endif
	CCBAnimationManager *m = (CCBAnimationManager *)tolua_tousertype(l, 1, NULL);
	if(m){
		int seqId = tolua_tonumber(l, 2, -1);
		if(seqId >= 0){
			float dur = tolua_tonumber(l, 3, 0);
#if COCOS2D_VERSION < 0x00020100
			m->runAnimations(seqId, dur);
#else
			m->runAnimationsForSequenceIdTweenDuration(seqId, dur);
#endif
		}
	}
	tolua_pushusertype(l, m, "CCBAnimationManager");
	return 1;
}

#endif //__TOLUA_CCBANIMATIONMANAGER__
