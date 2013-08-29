#include "UIUtil.h"

CCRenderTexture * UIUtil::createStroke(CCLabelTTF *label, float size, ccColor3B color){
	if(!label || size <= 0){ return NULL;}
	float x = label->getTexture()->getContentSize().width+size*2;
	float y = label->getTexture()->getContentSize().height+size*2;
	CCRenderTexture *rt = CCRenderTexture::create(x, y);
	CCPoint originalPos = label->getPosition();
	ccColor3B originalColor = label->getColor();
	label->setColor(color);
	ccBlendFunc originalBlend = label->getBlendFunc();
	ccBlendFunc tempBlend = {GL_SRC_ALPHA, GL_ONE};
	label->setBlendFunc(tempBlend);
	CCPoint center = ccp(x/2+size, y/2+size);
	rt->begin();
	for (int i = 0; i < 360; i += 15) {
		x = center.x+sin(CC_DEGREES_TO_RADIANS(i))*size;
		y = center.y+cos(CC_DEGREES_TO_RADIANS(i))*size;
		label->setPosition(ccp(x, y));
		label->visit();
	}
	rt->end();
	label->setPosition(originalPos);
	label->setColor(originalColor);
	label->setBlendFunc(originalBlend);
	x = originalPos.x-size;
	x = originalPos.y-size;
	rt->setPosition(ccp(x, y));
	return rt;
}

// Gray = R*0.299 + G*0.587 + B*0.114
CCGLProgram * UIUtil::shaderForKey(const char *key, const char *v, const char *f){
	CCGLProgram *p = CCShaderCache::sharedShaderCache()->programForKey(key);
	if(!p){
		p = new CCGLProgram();
		if(p && p->initWithVertexShaderByteArray(v, f)){
			p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
			p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
			p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
			p->link();
			p->updateUniforms();
			CHECK_GL_ERROR_DEBUG();
			CCShaderCache::sharedShaderCache()->addProgram(p, key);
			p->autorelease();
		}else{
			CC_SAFE_DELETE(p);
		}
	}
	return p;
}

void UIUtil::setShaderWithChildren(CCNode *n, CCGLProgram *s){
	if(n){
		n->setShaderProgram(s);
		CCObject *o;
		CCARRAY_FOREACH(n->getChildren(), o){
			setShaderWithChildren((CCNode *)o, s);
		}
	}
}
void UIUtil::fixLabel(CCNode *o, const float rate, bool withChild, const char *font){
	CCLabelTTF *l = dynamic_cast<CCLabelTTF *>(o);
	if(l){
		l->setScale(1 / rate);
		l->setFontSize(l->getFontSize() * rate);
		CCSize s = l->getDimensions();
		s.width *= rate;
		s.height *= rate;
		l->setDimensions(s);
		if(font){
			l->setFontName(font);
		}
	}
	if(withChild){
		CCObject *s;
		CCARRAY_FOREACH(o->getChildren(), s){
			fixLabel((CCNode *)s, rate, true, font);
		}
	}
}
void UIUtil::fixParticle(CCNode *o, const float dur, const float life, bool withChild){
	CCParticleSystemQuad *e = dynamic_cast<CCParticleSystemQuad *>(o);
	if(e){
		//CCLog("UIUtil.fixPar %x %x\n", e, e->getTexture());
		e->setDuration(dur);
		e->setLife(life);
		e->setAutoRemoveOnFinish(true);
	}
	if(withChild){
		CCObject *s;
		CCARRAY_FOREACH(o->getChildren(), s){
			fixParticle((CCNode *)s, dur, life, true);
		}
	}
}
void UIUtil::fixParticleWithHandler(CCNode *o, LuaEventHandler *h, bool withChild){
	CCParticleSystemQuad *e = dynamic_cast<CCParticleSystemQuad *>(o);
	if(e){
		h->action(e);
	}
	if(withChild){
		CCObject *s;
		CCARRAY_FOREACH(o->getChildren(), s){
			fixParticleWithHandler((CCNode *)s, h, true);
		}
	}
}
#define CREATE_AND_DUPLICATE(r,T,n) if(dynamic_cast<T *>(n)){T *e = T::create();duplicate(e, (T *)n);r = e;}
CCNode * UIUtil::copyNode(CCNode *n, bool deep){
	CCNode *r = NULL;
	if(n){
		if(!r){	CREATE_AND_DUPLICATE(r, CCLabelTTF, n);}
		if(!r){	CREATE_AND_DUPLICATE(r, CCLabelBMFont, n);}
		if(!r){	CREATE_AND_DUPLICATE(r, CCParticleSystemQuad, n);}
		if(!r){	CREATE_AND_DUPLICATE(r, CCSprite, n);}
		if(!r){	CREATE_AND_DUPLICATE(r, CCScale9Sprite, n);}
		if(!r){
			CREATE_AND_DUPLICATE(r, CCControlButton, n);
			if(r){
				deep = false;
			}
		}
		if(!r){
			r = CCNode::create();
			duplicate(r, n);
		}
		if(deep){
			CCObject *o = NULL;
			CCARRAY_FOREACH(n->getChildren(), o){
				r->addChild(copyNode((CCNode *)o));
			}
		}
	}
	return r;
}
void UIUtil::duplicate(CCScale9Sprite *n, CCScale9Sprite *o){
	if(!n || !o)return;
	n->setPreferredSize(o->getPreferredSize());
	n->setCapInsets(o->getCapInsets());
	n->setOpacity(o->getOpacity());
	n->setColor(o->getColor());
	duplicate((CCNode *)n, (CCNode *)o);
}
void UIUtil::duplicate(CCSprite *n, CCSprite *o){
	if(!n || !o)return;
	n->setDisplayFrame(o->displayFrame());
	n->setOpacity(o->getOpacity());
	n->setColor(o->getColor());
	n->setFlipX(o->isFlipX());
	n->setFlipY(o->isFlipY());
	n->setBlendFunc(o->getBlendFunc());
	duplicate((CCNode *)n, (CCNode *)o);
}
void UIUtil::duplicate(CCLayer *n, CCLayer *o){
	if(!n || !o)return;
	duplicate((CCNode *)n, (CCNode *)o);
}
void UIUtil::duplicate(CCLabelBMFont *n, CCLabelBMFont *o){
	if(!n || !o)return;
	n->setFntFile(o->getFntFile());
	n->setOpacity(o->getOpacity());
	n->setColor(o->getColor());
	n->setBlendFunc(o->getBlendFunc());
	duplicate((CCNode *)n, (CCNode *)o);
}
void UIUtil::duplicate(CCLabelTTF *n, CCLabelTTF *o){
	if(!n || !o)return;
	n->setFontName(o->getFontName());
	n->setFontSize(o->getFontSize());
	n->setOpacity(o->getOpacity());
	n->setDimensions(o->getDimensions());
	n->setHorizontalAlignment(o->getHorizontalAlignment());
	n->setVerticalAlignment(o->getVerticalAlignment());
	duplicate((CCNode *)n, (CCNode *)o);
}
void UIUtil::duplicate(CCNode *n, CCNode *o){
	if(!n || !o)return;
	n->setPosition(o->getPosition());
	n->setContentSize(o->getContentSize());
	n->setAnchorPoint(o->getAnchorPoint());
	n->setScaleX(o->getScaleX());
	n->setScaleY(o->getScaleY());
	n->setRotation(o->getRotation());
	n->setVisible(o->isVisible());
	n->setVertexZ(o->getVertexZ());
	n->setSkewX(o->getSkewX());
	n->setSkewY(o->getSkewY());
	n->setOrderOfArrival(o->getOrderOfArrival());
	n->ignoreAnchorPointForPosition(o->isIgnoreAnchorPointForPosition());
	n->setGLServerState(o->getGLServerState());
}
void UIUtil::duplicate(CCParticleSystemQuad *n, CCParticleSystemQuad *o){
	if(!n || !o)return;
	duplicate((CCParticleSystem *)n, (CCParticleSystem *)o);
}
void UIUtil::duplicate(CCParticleSystem *n, CCParticleSystem *o){
	if(!n || !o)return;
	n->setEmitterMode(o->getEmitterMode());
	n->setBatchNode(o->getBatchNode());
	n->setDuration(o->getDuration());
	n->setSourcePosition(o->getSourcePosition());
	n->setPosVar(o->getPosVar());
	n->setLife(o->getLife());
	n->setLifeVar(o->getLifeVar());
	n->setAngle(o->getAngle());
	n->setAngleVar(o->getAngleVar());
	if(n->getEmitterMode() == kCCParticleModeRadius){
		n->setStartRadius(o->getStartRadius());
		n->setStartRadiusVar(o->getStartRadiusVar());
		n->setEndRadius(o->getEndRadius());
		n->setEndRadiusVar(o->getEndRadiusVar());
		n->setRotatePerSecond(o->getRotatePerSecond());
		n->setRotatePerSecondVar(o->getRotatePerSecondVar());
	}else if(n->getEmitterMode() == kCCParticleModeGravity){
		n->setTangentialAccel(o->getTangentialAccel());
		n->setTangentialAccelVar(o->getTangentialAccelVar());
		n->setGravity(o->getGravity());
		n->setSpeed(o->getSpeed());
		n->setSpeedVar(o->getSpeedVar());
		n->setRadialAccel(o->getRadialAccel());
		n->setRadialAccelVar(o->getRadialAccelVar());
	}
	n->setScaleX(o->getScaleX());
	n->setScaleY(o->getScaleY());
	n->setRotation(o->getRotation());
	n->setBlendAdditive(o->isBlendAdditive());
	n->setStartSize(o->getStartSize());
	n->setStartSizeVar(o->getStartSizeVar());
	n->setEndSize(o->getEndSize());
	n->setEndSizeVar(o->getEndSizeVar());
	n->setStartColor(o->getStartColor());
	n->setStartColorVar(o->getStartColorVar());
	n->setEndColor(o->getEndColor());
	n->setEndColorVar(o->getEndColorVar());
	n->setStartSpin(o->getStartSpin());
	n->setStartSpinVar(o->getStartSpinVar());
	n->setEndSpin(o->getEndSpin());
	n->setEndSpinVar(o->getEndSpinVar());
	n->setEmissionRate(o->getEmissionRate());
	n->setTotalParticles(o->getTotalParticles());
	n->setTexture(o->getTexture());
	n->setBlendFunc(o->getBlendFunc());
	n->setOpacityModifyRGB(o->getOpacityModifyRGB());
	n->setPositionType(o->getPositionType());
	n->setAutoRemoveOnFinish(o->isAutoRemoveOnFinish());
	duplicate((CCNode *)n, (CCNode *)o);
}
void UIUtil::duplicate(CCControl *n, CCControl *o){
	if(!n || !o)return;
	duplicate((CCLayer *)n, (CCLayer *)o);
}
void UIUtil::duplicate(CCControlButton *n, CCControlButton *o){
	if(!n || !o)return;
	duplicate((CCControl *)n, (CCControl *)o);
	CCControlState states[] = {CCControlStateNormal, CCControlStateHighlighted, CCControlStateDisabled};
	CCControlState s;
	for(int i = 0; i < 3; i ++){
		s = states[i];
		n->setTitleForState(o->getTitleForState(s), s);
		n->setTitleColorForState(o->getTitleColorForState(s), s);
	}
	n->setEnabled(o->isEnabled());
	n->setSelected(o->isSelected());
	n->setHighlighted(o->isHighlighted());
	n->setAdjustBackgroundImage(o->doesAdjustBackgroundImage());
	n->setPreferredSize(o->getPreferredSize());
	n->setZoomOnTouchDown(o->getZoomOnTouchDown());
	n->setOpacity(o->getOpacity());
	n->setOpacityModifyRGB(o->isOpacityModifyRGB());
	n->setColor(o->getColor());
}
CCNode * UIUtil::changeParent(CCNode *n, CCNode *np, int zOrd, int tag){
	if(n && np){
		n->retain();
		if(n->getParent()){ n->removeFromParentAndCleanup(true);}
		np->addChild(n, zOrd ? zOrd : 0, tag ? tag : -1);
		n->release();
	}
	return n;
}
CCPoint UIUtil::positionRelative(CCNode *n, CCNode *np){
	return n && np? np->convertToNodeSpace(n->getParent()->convertToWorldSpace(n->getPosition())) : CCPointZero;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
UIEventDispatcher * UIEventDispatcher::_instance = NULL;
UIEventDispatcher * UIEventDispatcher::sharedDispatcher(){
	if(!_instance){
		_instance = new UIEventDispatcher();
	}
	return _instance;
}
void UIEventDispatcher::win32Key(UINT m, WPARAM w, LPARAM l){
	for(std::vector<UIEventDelegate *>::iterator i = _listener.begin(); i != _listener.end(); i ++)
		(*i)->keyEvent(m, w, l);
}
void UIEventDispatcher::addListener(UIEventDelegate *l){
	_listener.push_back(l);
}
void UIEventDispatcher::removeListener(UIEventDelegate *l){
	for(std::vector<UIEventDelegate *>::iterator i = _listener.begin(); i != _listener.end(); i ++)
		if(*i == l){
			_listener.erase(i);
			break;
		}
}
void UIEventDispatcherHook(UINT m, WPARAM w, LPARAM l){
	UIEventDispatcher::sharedDispatcher()->win32Key(m, w, l);
}
#endif // WIN32 only

CCCameraEyeAction * CCCameraEyeAction::create(float dur, bool bTo, const ccVertex3F& d){
	CCCameraEyeAction *o = new CCCameraEyeAction();
	o->initWithDuration(dur, bTo, d);
	o->autorelease();
	return o;
}
bool CCCameraEyeAction::initWithDuration(float dur, bool bTo, const ccVertex3F& d){
	if(CCActionInterval::initWithDuration(dur)){
		_vtDelta = d;
		_bTo = bTo;
		return true;
	}
	return false;
}
void CCCameraEyeAction::startWithTarget(CCNode *tar){
	CCActionInterval::startWithTarget(tar);
	float x = 0, y = 0, z = 0;
	tar->getCamera()->getEyeXYZ(&x, &y, &z);
	if(!_bTo){
		_vtDelta.x += x;
		_vtDelta.y += y;
		_vtDelta.z += z;
	}
	_vtPrev = vertex3(x, y, z);
	if(!_bCustomStart){ _vtStart = _vtPrev;}
}
void CCCameraEyeAction::update(float time){
	if(m_pTarget){
		float x = 0, y = 0, z = 0;
		m_pTarget->getCamera()->getEyeXYZ(&x, &y, &z);
		ccVertex3F cur = vertex3(x, y, z);
		ccVertex3F diff = ccV3Sub(cur, _vtPrev);
//CCLog("eye sta:%f,%f,%f",_vtStart.x,_vtStart.y,_vtStart.z);
		_vtStart = ccV3Add(_vtStart, diff);
//CCLog("eye sta:%f,%f,%f",_vtStart.x,_vtStart.y,_vtStart.z);
		ccVertex3F np =  ccV3Add(_vtStart, ccV3Mult(_vtDelta, time));
		m_pTarget->getCamera()->setEyeXYZ(np.x, np.y, np.z);
//CCLog("eye  np:%f,%f,%f",np.x,np.y,np.z);
		_vtPrev = np;
	}
}
CCCameraEyeAction * CCCameraEyeAction::setStart(ccVertex3F v){
	_vtStart = v;
	_bCustomStart = true;
	return this;
}
