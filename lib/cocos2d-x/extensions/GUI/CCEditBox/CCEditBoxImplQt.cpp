/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013 Jozef Pridavok
 
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
#include "CCEditBoxImplQt.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_QT)

#include <QLineEdit>
#include <QInputDialog>
#include "CCEditBox.h"

NS_CC_EXT_BEGIN

CCEditBoxImpl* __createSystemEditBox(CCEditBox* pEditBox)
{
    return new CCEditBoxImplQt(pEditBox);
}

CCEditBoxImplQt::CCEditBoxImplQt(CCEditBox* pEditText)
: CCEditBoxImpl(pEditText)
, m_pLabel(NULL)
, m_pLabelPlaceHolder(NULL)
, m_eEditBoxInputMode(kEditBoxInputModeSingleLine)
, m_eEditBoxInputFlag(kEditBoxInputFlagInitialCapsAllCharacters)
, m_eKeyboardReturnType(kKeyboardReturnTypeDefault)
, m_colText(ccWHITE)
, m_colPlaceHolder(ccGRAY)
, m_nMaxLength(-1)
{
    
}

CCEditBoxImplQt::~CCEditBoxImplQt()
{
}

void CCEditBoxImplQt::doAnimationWhenKeyboardMove(float duration, float distance)
{
}

bool CCEditBoxImplQt::initWithSize(const CCSize& size)
{
    //! int fontSize = getFontSizeAccordingHeightJni(size.height-12);
    m_pLabel = CCLabelTTF::create("", "", size.height-12);
	// align the text vertically center
    m_pLabel->setAnchorPoint(ccp(0, 0.5f));
    m_pLabel->setPosition(ccp(5, size.height / 2.0f));
    m_pLabel->setColor(m_colText);
    m_pEditBox->addChild(m_pLabel);

    m_pLabelPlaceHolder = CCLabelTTF::create("", "", size.height-12);
	// align the text vertically center
    m_pLabelPlaceHolder->setAnchorPoint(ccp(0, 0.5f));
    m_pLabelPlaceHolder->setPosition(ccp(5, size.height / 2.0f));
    m_pLabelPlaceHolder->setVisible(false);
    m_pLabelPlaceHolder->setColor(m_colPlaceHolder);
    m_pEditBox->addChild(m_pLabelPlaceHolder);
    
    m_EditSize = size;
    return true;
}

void CCEditBoxImplQt::setFont(const char* pFontName, int fontSize)
{
	if(m_pLabel != NULL) {
		m_pLabel->setFontName(pFontName);
		m_pLabel->setFontSize(fontSize);
	}
	
	if(m_pLabelPlaceHolder != NULL) {
		m_pLabelPlaceHolder->setFontName(pFontName);
		m_pLabelPlaceHolder->setFontSize(fontSize);
	}
}

void CCEditBoxImplQt::setFontColor(const ccColor3B& color)
{
    m_colText = color;
    m_pLabel->setColor(color);
}

void CCEditBoxImplQt::setPlaceholderFont(const char* pFontName, int fontSize)
{
	if(m_pLabelPlaceHolder != NULL) {
		m_pLabelPlaceHolder->setFontName(pFontName);
		m_pLabelPlaceHolder->setFontSize(fontSize);
	}
}

void CCEditBoxImplQt::setPlaceholderFontColor(const ccColor3B& color)
{
    m_colPlaceHolder = color;
    m_pLabelPlaceHolder->setColor(color);
}

void CCEditBoxImplQt::setInputMode(EditBoxInputMode inputMode)
{
    m_eEditBoxInputMode = inputMode;
}

void CCEditBoxImplQt::setMaxLength(int maxLength)
{
    m_nMaxLength = maxLength;
}

int CCEditBoxImplQt::getMaxLength()
{
    return m_nMaxLength;
}

void CCEditBoxImplQt::setInputFlag(EditBoxInputFlag inputFlag)
{
    m_eEditBoxInputFlag = inputFlag;
}

void CCEditBoxImplQt::setReturnType(KeyboardReturnType returnType)
{
    m_eKeyboardReturnType = returnType;
}

bool CCEditBoxImplQt::isEditing()
{
    return false;
}

void CCEditBoxImplQt::setText(const char* pText)
{
    if (pText != NULL)
    {
        m_strText = pText;

        if (m_strText.length() > 0)
        {
            m_pLabelPlaceHolder->setVisible(false);

            std::string strToShow;

            if (kEditBoxInputFlagPassword == m_eEditBoxInputFlag)
            {
                long length = cc_utf8_strlen(m_strText.c_str(), -1);
                for (long i = 0; i < length; i++)
                {
                    strToShow.append("*");
                }
            }
            else
            {
                strToShow = m_strText;
            }

            //! std::string strWithEllipsis = getStringWithEllipsisJni(strToShow.c_str(), m_EditSize.width, m_EditSize.height-12);
            //! m_pLabel->setString(strWithEllipsis.c_str());
			m_pLabel->setString(strToShow.c_str());
        }
        else
        {
            m_pLabelPlaceHolder->setVisible(true);
            m_pLabel->setString("");
        }

    }
}

const char*  CCEditBoxImplQt::getText(void)
{
    return m_strText.c_str();
}

void CCEditBoxImplQt::setPlaceHolder(const char* pText)
{
    if (pText != NULL)
    {
        m_strPlaceHolder = pText;
        if (m_strPlaceHolder.length() > 0 && m_strText.length() == 0)
        {
            m_pLabelPlaceHolder->setVisible(true);
        }

        m_pLabelPlaceHolder->setString(m_strPlaceHolder.c_str());
    }
}

void CCEditBoxImplQt::setPosition(const CCPoint& pos)
{
	//m_pLabel->setPosition(pos);
	//m_pLabelPlaceHolder->setPosition(pos);
}

void CCEditBoxImplQt::setVisible(bool visible)
{ // don't need to be implemented on win32 platform.
}

void CCEditBoxImplQt::setContentSize(const CCSize& size)
{
}

void CCEditBoxImplQt::setAnchorPoint(const CCPoint& anchorPoint)
{ // don't need to be implemented on win32 platform.
	
}

void CCEditBoxImplQt::visit(void)
{   
}

static void editBoxCallbackFunc(const char* pText, void* ctx)
{
    CCEditBoxImplQt* thiz = (CCEditBoxImplQt*)ctx;
    thiz->setText(pText);

    if (thiz->getDelegate() != NULL)
    {
        thiz->getDelegate()->editBoxTextChanged(thiz->getCCEditBox(), thiz->getText());
        thiz->getDelegate()->editBoxEditingDidEnd(thiz->getCCEditBox());
        thiz->getDelegate()->editBoxReturn(thiz->getCCEditBox());
    }
    
    CCEditBox* pEditBox = thiz->getCCEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "ended",pEditBox);
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "return",pEditBox);
    }
}

void CCEditBoxImplQt::openKeyboard()
{
    if (m_pDelegate != NULL)
    {
        m_pDelegate->editBoxEditingDidBegin(m_pEditBox);
    }
    
    CCEditBox* pEditBox = this->getCCEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
    }
    
	std::string placeHolder = m_pLabelPlaceHolder->getString();
	if (placeHolder.length() == 0)
		placeHolder = "Enter value";

	std::string text = getText();
    QString orignText = QString::fromUtf8(text.data());
    bool ok;
    QString retText = QInputDialog::getText(0, "InputDialog::getText()",
                                        "Input:", QLineEdit::Normal,
                                        orignText, &ok);
    bool didChange = (ok && retText != orignText);

	if (didChange) 	
        setText(retText.toStdString().data());

	if (m_pDelegate != NULL) {
		if (didChange)
			m_pDelegate->editBoxTextChanged(m_pEditBox, getText());
		m_pDelegate->editBoxEditingDidEnd(m_pEditBox);
		m_pDelegate->editBoxReturn(m_pEditBox);
	}

    if (pEditBox && pEditBox->getScriptEditBoxHandler())
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "changed",pEditBox);
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "ended",pEditBox);
        pEngine->executeEvent(pEditBox->getScriptEditBoxHandler(), "return",pEditBox);
    }
}

void CCEditBoxImplQt::closeKeyboard()
{

}

void CCEditBoxImplQt::onEnter(void)
{

}

NS_CC_EXT_END

#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_QT) */
