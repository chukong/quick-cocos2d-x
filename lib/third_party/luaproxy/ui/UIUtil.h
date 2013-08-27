#ifndef __UIUTIL_H__
#define __UIUTIL_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "../tolua/LuaEventHandler.h"

USING_NS_CC;
USING_NS_CC_EXT;

static inline ccVertex3F ccV3Add(const ccVertex3F& a, const ccVertex3F& b){
	return vertex3(a.x + b.x, a.y + b.y, a.z + b.z);
}
static inline ccVertex3F ccV3Sub(const ccVertex3F& a, const ccVertex3F& b){
	return vertex3(a.x - b.x, a.y - b.y, a.z - b.z);
}
static inline ccVertex3F ccV3Mult(const ccVertex3F& a, const float v){
	return vertex3(a.x * v, a.y * v, a.z * v);
}

class UIUtil{
public:
	// Label Stroke
	static CCRenderTexture * createStroke(CCLabelTTF *label, float size, ccColor3B color);
	// Get shader for key
	// If the shader not exist, try to create new with (v) and (f) if both of they are not null
	static CCGLProgram * shaderForKey(const char *key, const char *v = NULL, const char *f = NULL);
	static void setShaderWithChildren(CCNode *n, CCGLProgram *s = NULL);
	// Fix label text blur when scaled
	// Change (o) and the children's scale and font size (scale/=rate and fontSize*=rate), and set font name if assigned (font)
	static void fixLabel(CCNode *o, const float rate, bool withChild, const char *font = NULL);
	static void fixParticle(CCNode *o, const float dur, const float life, bool withChild);
	static void fixParticleWithHandler(CCNode *o, LuaEventHandler *h, bool withChild);
	static CCNode * copyNode(CCNode *n, bool deep = true);
	// Duplicate (o)'s properties to (n)
	static void duplicate(CCNode *n, CCNode *o);
	static void duplicate(CCScale9Sprite *n, CCScale9Sprite *o);
	static void duplicate(CCSprite *n, CCSprite *o);
	static void duplicate(CCLayer *n, CCLayer *o);
	static void duplicate(CCLabelBMFont *n, CCLabelBMFont *o);
	static void duplicate(CCLabelTTF *n, CCLabelTTF *o);
	static void duplicate(CCParticleSystemQuad *n, CCParticleSystemQuad *o);
	static void duplicate(CCParticleSystem *n, CCParticleSystem *o);
	static void duplicate(CCControl *n, CCControl *o);
	static void duplicate(CCControlButton *n, CCControlButton *o);
	// Move node (n) from its original parent to new one (np), and set z order (zOrd=0) and (tag=1)
	static CCNode * changeParent(CCNode *n, CCNode *np, int zOrd = 0, int tag = -1);
	// Get node (n)'s position relative another node (np), np may not parent of n.
	static CCPoint positionRelative(CCNode *n, CCNode *np);
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
class UIEventDelegate{
public:
	virtual void keyEvent(UINT m, WPARAM w, LPARAM l) = 0;
};

class UIEventDispatcher : public CCObject{
protected:
	std::vector<UIEventDelegate *> _listener;
	static UIEventDispatcher *_instance;
public:
	static UIEventDispatcher * sharedDispatcher();
	UIEventDispatcher(){}
	~UIEventDispatcher(){}
	void win32Key(UINT m, WPARAM w, LPARAM l);
	void addListener(UIEventDelegate *l);
	void removeListener(UIEventDelegate *l);
};
void UIEventDispatcherHook(UINT m, WPARAM w, LPARAM l);
#endif // WIN32 only

class CCCameraEyeAction : public CCActionInterval{
public:
	ccVertex3F _vtDelta;
	ccVertex3F _vtStart;
	ccVertex3F _vtPrev;
	bool _bTo;
	bool _bCustomStart;
	CCCameraEyeAction() : _bTo(true), _bCustomStart(false){}
	~CCCameraEyeAction(){}
	// Create camera eye action, move to vertex, or move by vertex
	static CCCameraEyeAction * create(float dur, bool bTo, const ccVertex3F& d);
	virtual bool initWithDuration(float dur, bool bTo, const ccVertex3F& d);
	virtual void startWithTarget(CCNode *tar);
	virtual void update(float time);
	CCCameraEyeAction * setStart(ccVertex3F v);
};

#endif //__UIUTIL_H__