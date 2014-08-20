/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCEditBox.h"
#include "CCEditBoxImpl.h"

NS_CC_EXT_BEGIN

const static unsigned char transImgData[] = {
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00,
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x0A,
	0x00, 0x00, 0x00, 0x0A, 0x08, 0x06, 0x00, 0x00, 0x00, 0x8D,
	0x32, 0xCF, 0xBD, 0x00, 0x00, 0x00, 0x06, 0x62, 0x4B, 0x47,
	0x44, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xA0, 0xBD, 0xA7,
	0x93, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00,
	0x00, 0x0B, 0x13, 0x00, 0x00, 0x0B, 0x13, 0x01, 0x00, 0x9A,
	0x9C, 0x18, 0x00, 0x00, 0x00, 0x07, 0x74, 0x49, 0x4D, 0x45,
	0x07, 0xDE, 0x08, 0x01, 0x06, 0x36, 0x3A, 0x27, 0xB1, 0xCF,
	0x2E, 0x00, 0x00, 0x00, 0x0C, 0x69, 0x54, 0x58, 0x74, 0x43,
	0x6F, 0x6D, 0x6D, 0x65, 0x6E, 0x74, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xBC, 0xAE, 0xB2, 0x99, 0x00, 0x00, 0x00, 0x0E, 0x49,
	0x44, 0x41, 0x54, 0x18, 0xD3, 0x63, 0x60, 0x18, 0x05, 0x83,
	0x13, 0x00, 0x00, 0x01, 0x9A, 0x00, 0x01, 0x0B, 0xA2, 0x9D,
	0x1F, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE,
	0x42, 0x60, 0x82
};

CCScale9Sprite* newTransParentSprite() {
    CCScale9Sprite* sp = NULL;
    CCSpriteFrame* spFrame = nullptr;
    CCTexture2D* texture = nullptr;
    
    texture = new CCTexture2D();
    texture->initWithData(transImgData, CCTexture2DPixelFormat::kCCTexture2DPixelFormat_RGBA8888, 10, 10, CCSize(10, 10));
    spFrame = CCSpriteFrame::createWithTexture(texture, CCRect(0, 0, 10, 10));
    sp = CCScale9Sprite::createWithSpriteFrame(spFrame);
    sp->setOpacity(0);

    texture->release();
    return sp;
}

CCEditBox::CCEditBox(void)
: m_pEditBoxImpl(NULL)
, m_pDelegate(NULL)
, m_eEditBoxInputMode(kEditBoxInputModeSingleLine)
, m_eEditBoxInputFlag(kEditBoxInputFlagInitialCapsAllCharacters)
, m_eKeyboardReturnType(kKeyboardReturnTypeDefault)
, m_nFontSize(-1)
, m_nPlaceholderFontSize(-1)
, m_colText(ccWHITE)
, m_colPlaceHolder(ccGRAY)
, m_nMaxLength(0)
, m_fAdjustHeight(0.0f)
, m_nScriptEditBoxHandler(0)
{
}

CCEditBox::~CCEditBox(void)
{
    CC_SAFE_DELETE(m_pEditBoxImpl);
    unregisterScriptEditBoxHandler();
}


void CCEditBox::touchDownAction(CCObject *sender, CCControlEvent controlEvent)
{
    m_pEditBoxImpl->openKeyboard();
}

CCEditBox* CCEditBox::create(const CCSize& size, CCScale9Sprite* pNormal9SpriteBg, CCScale9Sprite* pPressed9SpriteBg/* = NULL*/, CCScale9Sprite* pDisabled9SpriteBg/* = NULL*/)
{
    CCEditBox* pRet = new CCEditBox();
    
    if (NULL == pNormal9SpriteBg) {
        pNormal9SpriteBg = newTransParentSprite();
    }
    if (pRet != NULL && pRet->initWithSizeAndBackgroundSprite(size, pNormal9SpriteBg))
    {
        if (pPressed9SpriteBg != NULL)
        {
            pRet->setBackgroundSpriteForState(pPressed9SpriteBg, CCControlStateHighlighted);
        }
        
        if (pDisabled9SpriteBg != NULL)
        {
            pRet->setBackgroundSpriteForState(pDisabled9SpriteBg, CCControlStateDisabled);
        }
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool CCEditBox::initWithSizeAndBackgroundSprite(const CCSize& size, CCScale9Sprite* pPressed9SpriteBg)
{
    if (CCControlButton::initWithBackgroundSprite(pPressed9SpriteBg))
    {
        m_pEditBoxImpl = __createSystemEditBox(this);
        m_pEditBoxImpl->initWithSize(size);
        
        this->setZoomOnTouchDown(false);
        this->setPreferredSize(size);
        this->setPosition(ccp(0, 0));
        this->addTargetWithActionForControlEvent(this, cccontrol_selector(CCEditBox::touchDownAction), CCControlEventTouchUpInside);
        
        return true;
    }
    return false;
}

void CCEditBox::setDelegate(CCEditBoxDelegate* pDelegate)
{
    m_pDelegate = pDelegate;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setDelegate(pDelegate);
    }
}

CCEditBoxDelegate* CCEditBox::getDelegate()
{
    return m_pDelegate;
}

void CCEditBox::setText(const char* pText)
{
    if (pText != NULL)
    {
        m_strText = pText;
        if (m_pEditBoxImpl != NULL)
        {
            m_pEditBoxImpl->setText(pText);
        }
    }
}

const char* CCEditBox::getText(void)
{
    if (m_pEditBoxImpl != NULL)
    {
		const char* pText = m_pEditBoxImpl->getText();
		if(pText != NULL)
			return pText;
    }
    
    return "";
}

void CCEditBox::setFont(const char* pFontName, int fontSize)
{
    m_strFontName = pFontName;
    m_nFontSize = fontSize;
    if (pFontName != NULL)
    {
        if (m_pEditBoxImpl != NULL)
        {
            m_pEditBoxImpl->setFont(pFontName, fontSize);
        }
    }
}

void CCEditBox::setFontName(const char* pFontName)
{
    m_strFontName = pFontName;
    if (m_pEditBoxImpl != NULL && m_nFontSize != -1)
    {
        m_pEditBoxImpl->setFont(pFontName, m_nFontSize);
    }
}

void CCEditBox::setFontSize(int fontSize)
{
    m_nFontSize = fontSize;
    if (m_pEditBoxImpl != NULL && m_strFontName.length() > 0)
    {
        m_pEditBoxImpl->setFont(m_strFontName.c_str(), m_nFontSize);
    }
}

void CCEditBox::setFontColor(const ccColor3B& color)
{
    m_colText = color;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setFontColor(color);
    }
}

void CCEditBox::setPlaceholderFont(const char* pFontName, int fontSize)
{
    m_strPlaceholderFontName = pFontName;
    m_nPlaceholderFontSize = fontSize;
    if (pFontName != NULL)
    {
        if (m_pEditBoxImpl != NULL)
        {
            m_pEditBoxImpl->setPlaceholderFont(pFontName, fontSize);
        }
    }
}

void CCEditBox::setPlaceholderFontName(const char* pFontName)
{
    m_strPlaceholderFontName = pFontName;
    if (m_pEditBoxImpl != NULL && m_nPlaceholderFontSize != -1)
    {
        m_pEditBoxImpl->setPlaceholderFont(pFontName, m_nFontSize);
    }
}

void CCEditBox::setPlaceholderFontSize(int fontSize)
{
    m_nPlaceholderFontSize = fontSize;
    if (m_pEditBoxImpl != NULL && m_strPlaceholderFontName.length() > 0)
    {
        m_pEditBoxImpl->setPlaceholderFont(m_strPlaceholderFontName.c_str(), m_nFontSize);
    }
}

void CCEditBox::setPlaceholderFontColor(const ccColor3B& color)
{
    m_colText = color;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setPlaceholderFontColor(color);
    }
}

void CCEditBox::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        m_strPlaceHolder = pText;
        if (m_pEditBoxImpl != NULL)
        {
            m_pEditBoxImpl->setPlaceHolder(pText);
        }
    }
}

const char* CCEditBox::getPlaceHolder(void)
{
    return m_strPlaceHolder.c_str();
}

void CCEditBox::setInputMode(EditBoxInputMode inputMode)
{
    m_eEditBoxInputMode = inputMode;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setInputMode(inputMode);
    }
}

void CCEditBox::setMaxLength(int maxLength)
{
    m_nMaxLength = maxLength;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setMaxLength(maxLength);
    }
}


int CCEditBox::getMaxLength()
{
    return m_nMaxLength;
}

void CCEditBox::setInputFlag(EditBoxInputFlag inputFlag)
{
    m_eEditBoxInputFlag = inputFlag;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setInputFlag(inputFlag);
    }
}

void CCEditBox::setReturnType(KeyboardReturnType returnType)
{
    m_eKeyboardReturnType = returnType;
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setReturnType(returnType);
    }
}

KeyboardReturnType CCEditBox::getReturnType()
{
    return m_eKeyboardReturnType;
}

/* override function */
void CCEditBox::setPosition(const CCPoint& pos)
{
    CCControlButton::setPosition(pos);
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setPosition(pos);
    }
}

void CCEditBox::setVisible(bool visible)
{
    CCControlButton::setVisible(visible);
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setVisible(visible);
    }
}

void CCEditBox::setContentSize(const CCSize& size)
{
    CCControlButton::setContentSize(size);
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setContentSize(size);
    }
}

void CCEditBox::setAnchorPoint(const CCPoint& anchorPoint)
{
    CCControlButton::setAnchorPoint(anchorPoint);
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->setAnchorPoint(anchorPoint);
    }
}

void CCEditBox::visit(void)
{
    CCControlButton::visit();
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->visit();
    }
}

void CCEditBox::onEnter(void)
{
    CCControlButton::onEnter();
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->onEnter();
    }
}

void CCEditBox::onExit(void)
{
    CCControlButton::onExit();
    if (m_pEditBoxImpl != NULL)
    {
        // remove system edit control
        m_pEditBoxImpl->closeKeyboard();
    }
}

static CCRect getRect(CCNode * pNode)
{
	CCSize contentSize = pNode->getContentSize();
	CCRect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
	return CCRectApplyAffineTransform(rect, pNode->nodeToWorldTransform());
}

void CCEditBox::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    // CCLOG("CCEditBox::keyboardWillShow");
    CCRect rectTracked = getRect(this);
	// some adjustment for margin between the keyboard and the edit box.
	rectTracked.origin.y -= 4;

    // if the keyboard area doesn't intersect with the tracking node area, nothing needs to be done.
    if (!rectTracked.intersectsRect(info.end))
    {
        CCLOG("needn't to adjust view layout.");
        return;
    }
    
    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    m_fAdjustHeight = info.end.getMaxY() - rectTracked.getMinY();
    // CCLOG("CCEditBox:needAdjustVerticalPosition(%f)", m_fAdjustHeight);
    
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->doAnimationWhenKeyboardMove(info.duration, m_fAdjustHeight);
    }
}

void CCEditBox::keyboardDidShow(CCIMEKeyboardNotificationInfo& info)
{
	
}

void CCEditBox::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
{
    // CCLOG("CCEditBox::keyboardWillHide");
    if (m_pEditBoxImpl != NULL)
    {
        m_pEditBoxImpl->doAnimationWhenKeyboardMove(info.duration, -m_fAdjustHeight);
    }
}

void CCEditBox::keyboardDidHide(CCIMEKeyboardNotificationInfo& info)
{
	
}

void CCEditBox::registerScriptEditBoxHandler(int handler)
{
    unregisterScriptEditBoxHandler();
    m_nScriptEditBoxHandler = handler;
}

void CCEditBox::unregisterScriptEditBoxHandler(void)
{
    if (0 != m_nScriptEditBoxHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptEditBoxHandler);
        m_nScriptEditBoxHandler = 0;
    }
}


NS_CC_EXT_END
