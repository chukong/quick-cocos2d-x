#include "CursorTextField.h"

static int _calcCharCount(const char *t){
	int n = 0;
	char ch = 0;
	while(ch == *t){
		CC_BREAK_IF(!ch);
		if(0x80 != (0xC0 & ch))
			++ n;
		++ t;
	}
	return n;
}
const static float DELTA = 20.0f;

CursorTextField::CursorTextField()
: _cursor(NULL)
, _cursorAction(NULL)
, _password(false)
, _maxLength(30){
	CCTextFieldTTF();
}
CursorTextField::~CursorTextField(){
	CC_SAFE_RELEASE(_cursorAction);
}
CursorTextField * CursorTextField::create(const char *fontName, float fontSize){
	return createWithPlaceHolder("", fontName, fontSize);
}
CursorTextField * CursorTextField::createWithPlaceHolder(const char *ph, const char *fontName, float fontSize){
	CursorTextField *o = new CursorTextField();
	if(o && o->initWithString("", fontName, fontSize)){
		o->autorelease();
		if(ph)
			o->setPlaceHolder(ph);
		o->initCursorSprite(fontSize);
		return o;
	}
	CC_SAFE_DELETE(o);
	return NULL;
}
void CursorTextField::initCursorSprite(int height){
	int column = 4;
	int *pixels = new int[height * column];
	for(int i = 0; i < height * column; i ++)
		pixels[i] = 0xffffffff;
	CCTexture2D *ttr = new CCTexture2D();
	ttr->initWithData(pixels, kCCTexture2DPixelFormat_RGB888, 1, 1, CCSizeMake(column, height));
	delete pixels;
	CCSize s = getContentSize();
	_cursorPos = ccp(0, s.height / 2);
	_cursor = CCSprite::createWithTexture(ttr);
	_cursor->setPosition(_cursorPos);
	_cursor->setVisible(false);
	addChild(_cursor);
	_cursorAction = CCRepeatForever::create((CCActionInterval *)
		CCSequence::create(CCFadeOut::create(0.25f), CCFadeIn::create(0.25f), NULL));
	_cursorAction->retain();
}
void CursorTextField::onEnter(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//	UIEventDispatcher::sharedDispatcher()->addListener(this);
#endif
	CCTextFieldTTF::onEnter();
    setTouchEnabled(true);
	setDelegate(this);
	_cursor->runAction(_cursorAction);
}
void CursorTextField::onExit(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//	UIEventDispatcher::sharedDispatcher()->removeListener(this);
#endif
	_cursor->stopAction(_cursorAction);
	detachWithIME();
	CCTextFieldTTF::onExit();
    setTouchEnabled(false);
}
int CursorTextField::ccTouchBegan(CCTouch *t, CCEvent *e){
	_touchBeginPos = CCDirector::sharedDirector()->convertToGL(t->getLocationInView());
	return true;
}
void CursorTextField::ccTouchEnded(CCTouch *t, CCEvent *e){
	CCPoint ep = CCDirector::sharedDirector()->convertToGL(t->getLocationInView());
	if(fabsf(ep.x - _touchBeginPos.x) > DELTA || fabsf(ep.y - _touchBeginPos.y) > DELTA){
		_touchBeginPos.x = _touchBeginPos.y = -1;
	}else
		isInTextField(t)? openIME() : closeIME();
}
CCRect CursorTextField::getRect(){
	CCSize s = &_designedSize != NULL? _designedSize : getContentSize();
	return CCRectMake(0 - s.width * getAnchorPoint().x, 0 - s.height * getAnchorPoint().y, s.width, s.height);
}
CCSize CursorTextField::getDesignedSize(){return _designedSize;}
void CursorTextField::setDesignedSize(CCSize s){_designedSize = s;}
bool CursorTextField::isInTextField(CCTouch *t){
	return getRect().containsPoint(convertTouchToNodeSpaceAR(t));
}
// ############################# Delegate functions ###############################
bool CursorTextField::onTextFieldAttachWithIME(CCTextFieldTTF *s){
	if(!m_pInputText->empty())
		_cursor->setPositionX(getContentSize().width);
	return false;
}
bool CursorTextField::onTextFieldInsertText(CCTextFieldTTF *s, const char *t, int len){
	if(strcmp(t, "\n") == 0){
		closeIME();
		return false;
	}
	if(m_pInputText->length() + len > _maxLength)
		return true;
//std::cout<<"CTF.onInsTxt()"<<t<<"\n";
	m_pInputText->append(t);
	updateDisplay();
	_cursor->setPositionX(getTextureRect().size.width);
//	_cursor->setPositionX(getContentSize().width);
	return true;
}
bool CursorTextField::onTextFieldDeleteBackward(CCTextFieldTTF *s, const char *delText, int len){
	if((int)m_pInputText->length() < len)
		return false;
	std::string::iterator it = m_pInputText->end();
	for(int i = 0; i < len; i ++)it --;
	m_pInputText->erase(it, m_pInputText->end());
	updateDisplay();
	_cursor->setPositionX(m_pInputText->empty()? 0 : getContentSize().width);
	return true;
}
bool CursorTextField::onTextFieldDetachWithIME(CCTextFieldTTF *s){return false;}

void CursorTextField::openIME(){
	_cursor->setVisible(true);
	attachWithIME();
}
void CursorTextField::closeIME(){
	_cursor->setVisible(false);
	detachWithIME();
}
bool CursorTextField::isPassword(){return _password;}
void CursorTextField::setPassword(bool b){_password = b;}
unsigned int CursorTextField::getMaxLength(){return _maxLength;}
void CursorTextField::setMaxLength(unsigned int n){_maxLength = n;}
void CursorTextField::setString(const char *t){
	m_pInputText->replace(0, m_pInputText->length(), t? t : "");
	updateDisplay();
}
void CursorTextField::updateDisplay(){
	const char *s = m_pInputText->length() == 0? m_pPlaceHolder->c_str() :
		(_password? NULL : m_pInputText->c_str());
	if(_password){
		std::string ts;
		for(unsigned int i = 0; i < m_pInputText->size(); i ++)
			ts.append("*");
		s = ts.c_str();
	}
//std::cout<<"CTF.upDisp()lbl.setString(s)"<<s;
	CCLabelTTF::setString(s);
}
void CursorTextField::setColor(const ccColor3B& c){
#if COCOS2D_VERSION < 0x00020100
	m_sColor = m_sColorUnmodified = c;
	if(m_bOpacityModifyRGB){
		m_sColor.r = c.r * m_nOpacity/255.0f;
		m_sColor.g = c.g * m_nOpacity/255.0f;
		m_sColor.b = c.b * m_nOpacity/255.0f;
	}
#endif
	updateColor();
	_cursor->setColor(c);
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
void CursorTextField::keyEvent(UINT m, WPARAM w, LPARAM l){
	if(!_cursor->isVisible())
		return;
	if(m == WM_CHAR){
//CCLOG("CursorTextField.keyEvent %d %d %c", m, w, w);
		if(VK_BACK == w){
			onTextFieldDeleteBackward(this, NULL, 1);
		}else if(VK_RETURN == w){

		}else{
			char s[2];
			sprintf(s, "%c", w);
			onTextFieldInsertText(this, s, 1);
		}
	}

}
#endif
