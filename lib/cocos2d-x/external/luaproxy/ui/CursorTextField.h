#pragma once
#ifndef __CURSORTEXTFIELD_H__
#define __CURSORTEXTFIELD_H__
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "UIUtil.h"
#endif
USING_NS_CC;

class CursorTextField : public CCTextFieldTTF, public CCTextFieldDelegate
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	, public UIEventDelegate
#endif
{
private:
	CCPoint _touchBeginPos;
	CCSprite *_cursor;
	CCAction *_cursorAction;
	CCPoint _cursorPos;
	bool _password;
	unsigned int _maxLength;
	CCSize _designedSize;
public:
	CursorTextField();
	~CursorTextField();
	static CursorTextField * create(const char *fontName, float fontSize);
	static CursorTextField * createWithPlaceHolder(const char *ph, const char *fontName, float fontSize);
	//CCLayer
	void onEnter();
	void onExit();
	void initCursorSprite(int height);
	//CCTextFieldDelegate
	virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *s);
	virtual bool onTextFieldDetachWithIME(CCTextFieldTTF *s);
	virtual bool onTextFieldInsertText(CCTextFieldTTF *s, const char *t, int len);
	virtual bool onTextFieldDeleteBackward(CCTextFieldTTF *s, const char *delText, int len);

	//CCLayer
	int ccTouchBegan(CCTouch *t, CCEvent *e);
	void ccTouchEnded(CCTouch *t, CCEvent *e);
	bool isInTextField(CCTouch *t);
	CCRect getRect();
	void openIME();
	void closeIME();
	bool isPassword();
	void setPassword(bool b);
	unsigned int getMaxLength();
	void setMaxLength(unsigned int n);

	//overload for display "*"
	void setString(const char *t);
	void updateDisplay();
	void setColor(const ccColor3B& c);

	//area for touch to open IME
	CCSize getDesignedSize();
	void setDesignedSize(CCSize s);
	//UIEventDelegate
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	void keyEvent(UINT m, WPARAM w, LPARAM l);
#endif
};

#endif //__CURSORTEXTFIELD_H__
