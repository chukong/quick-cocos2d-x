#include "SPContourPoints.h"
#include "SPUtilMath.h"

USING_NS_CC;

namespace sp{
    
CCTexture2DMutable *ContourPoints::m_pTextureMutable = NULL;

void ContourPoints::setPointFile(const char* file)
{
    m_pPointFile = file;
}

ContourPoints::ContourPoints(const char* file)
{
    m_AnchorPoint = ccp(0.5f, 0.5f);
    
    m_pLeftUp = CCSprite::create(file) ;
    m_pRightUp  = CCSprite::create(file);
    m_pLeftDown  = CCSprite::create(file);
    m_pRightDown  = CCSprite::create(file);
    m_pCenter = CCSprite::create(file);
    m_pRotation = CCSprite::create(file);
    
    m_pRotation->setTag(101);
    m_pCenter->setTag(100);
    m_pLeftUp->setRotation(-270);
    m_pRightUp->setRotation(-180);
    m_pRightDown->setRotation(-90);

    m_pRenderNode = new CCNode;
    m_pRenderNode->addChild(m_pLeftUp, 0, POINT_LEFTUP);
    m_pRenderNode->addChild(m_pRightUp, 0, POINT_RIGHTUP);
    m_pRenderNode->addChild(m_pLeftDown, 0, POINT_LEFTDOWN);
    m_pRenderNode->addChild(m_pRightDown, 0, POINT_RIGHTDOWN);
    m_pRenderNode->addChild(m_pCenter, 0, POINT_CENTER);
    m_pRenderNode->addChild(m_pRotation, 0, POINT_ROTATION);
    
    m_eContourPointType = POINT_MIN;
    
    
    CCSize _texSize = m_pLeftUp->getContentSize();
    
    if(m_pTextureMutable == NULL)
    {
        m_pTextureMutable = new CCTexture2DMutable();
        m_pTextureMutable->initWithImageFile(file);
    }

	m_pRenderNode->setVisible(false);
}

ContourPoints::~ContourPoints()
{
    m_pRenderNode->removeFromParentAndCleanup(true);
    CC_SAFE_DELETE(m_pRenderNode);
}

void ContourPoints::setSize(float width, float height )
{
    m_Width = width;
    m_Height = height;

    float leftX = -width/2;
    float rightX = -leftX;
    float upY = height / 2;
    float downY = -upY;

    m_pLeftUp->setPosition( ccp(leftX, upY) );
    m_pRightUp->setPosition( ccp(rightX, upY) );
    m_pLeftDown->setPosition( ccp(leftX, downY) );
    m_pRightDown->setPosition( ccp(rightX, downY) );
    m_pCenter->setPosition( ccp(0, 0) );
    m_pRotation->setPosition( ccp(width/2+20, 0) );
}

void ContourPoints::setVisible( bool isVisible )
{
    m_pRenderNode->setVisible(isVisible);
}

bool ContourPoints::isVisible()
{
	return m_pRenderNode->isVisible();
}

int ContourPoints::isClickAnchorPoint( float x, float y )
{
    CCPoint position = this->m_pRenderNode->convertToNodeSpace(ccp(x, y));

    CCArray* children = m_pRenderNode->getChildren();
    CCObject* pObj = NULL;
    int i=0;
    CCARRAY_FOREACH( children, pObj )
    {
        CCRect rect = ( (CCSprite*)pObj )->boundingBox();

        if ( rect.containsPoint(position))
        {
            return i+1;
        }
        i++;
    }

    return 0;
}

CCNode* ContourPoints::getRenderNode()
{
    return m_pRenderNode;
}


void ContourPoints::setBoundingBox(CCRect box)
{
    m_pLeftDown->setPosition(box.origin);
    m_pLeftUp->setPosition(ccp(box.origin.x, box.origin.y + box.size.height));
    m_pRightDown->setPosition(ccp(box.origin.x + box.size.width, box.origin.y));
    m_pRightUp->setPosition(ccp(box.origin.x + box.size.width, box.origin.y + box.size.height));
    m_pCenter->setPosition(ccp( box.origin.x + m_AnchorPoint.x * box.size.width, box.origin.y + m_AnchorPoint.y * box.size.height));
    m_pRotation->setPosition( ccp(box.origin.x + box.size.width, box.origin.y + box.size.height/2) );
}

    
void ContourPoints::scalePointPosition(float scaleX, float scaleY)
{
    m_pLeftDown->setScaleX(scaleX);
    m_pLeftDown->setScaleY(scaleY);
    
    m_pLeftUp->setScaleX(scaleX);
    m_pLeftUp->setScaleY(scaleY);
    
    m_pRightDown->setScaleX(scaleX);
    m_pRightDown->setScaleY(scaleY);
    
    m_pRightUp->setScaleX(scaleX);
    m_pRightUp->setScaleY(scaleY);
    
    m_pCenter->setScaleX(scaleX);
    m_pCenter->setScaleY(scaleY);
    
    m_pRotation->setScaleX(scaleX);
    m_pRotation->setScaleY(scaleY);
    
}
    
ContourPointType ContourPoints::containWorldPoint(cocos2d::CCPoint &_point)
{
   
    do
    {
//        cocos2d::CCPoint p = _point;
//        cocos2d::CCPoint outP;
//        
//        
//        m_eContourPointType = POINT_LEFTDOWN;
//        
//        if(SP_SPRITE_CONTAIN_POINT_WITH_RETURN(m_pLeftDown, p, outP))
//        {
//            CC_BREAK_IF(m_pTextureMutable->pixelAt(outP).a != 0);
//            return m_eContourPointType = POINT_MIN;
//        }
//        
//        
//        m_eContourPointType = POINT_LEFTUP;
//        
//        if(SP_SPRITE_CONTAIN_POINT_WITH_RETURN(m_pLeftUp, p, outP))
//        {
//            CC_BREAK_IF(m_pTextureMutable->pixelAt(outP).a != 0);
//            return m_eContourPointType = POINT_MIN;
//        }
//        
//        m_eContourPointType = POINT_RIGHTDOWN;
//        
//        if(SP_SPRITE_CONTAIN_POINT_WITH_RETURN(m_pRightDown, p, outP))
//        {
//            CC_BREAK_IF(m_pTextureMutable->pixelAt(outP).a != 0);
//            return m_eContourPointType = POINT_MIN;
//        }
//        
//        m_eContourPointType = POINT_RIGHTUP;
//        
//        if(SP_SPRITE_CONTAIN_POINT_WITH_RETURN(m_pRightUp, p, outP))
//        {
//            CC_BREAK_IF(m_pTextureMutable->pixelAt(outP).a != 0);
//            return m_eContourPointType = POINT_MIN;
//        }
//        
//        m_eContourPointType = POINT_CENTER;
//        
//        if(SP_SPRITE_CONTAIN_POINT_WITH_RETURN(m_pCenter, p, outP))
//        {
//            CC_BREAK_IF(m_pTextureMutable->pixelAt(outP).a != 0);
//            return m_eContourPointType = POINT_MIN;
//        }
//        
//        m_eContourPointType = POINT_ROTATION;
//        
//        if(SP_SPRITE_CONTAIN_POINT_WITH_RETURN(m_pRotation, p, outP))
//        {
//            CC_BREAK_IF(m_pTextureMutable->pixelAt(outP).a != 0);
//            return m_eContourPointType = POINT_MIN;
//        }
        
        m_eContourPointType = POINT_MIN;
    }while (0);
    
    CCLog("anchor point type : %i", m_eContourPointType);
    
    return m_eContourPointType;
}
    
ContourPointType ContourPoints::getClickedPointType()
{
    return m_eContourPointType;
}

    
void ContourPoints::setAnchorPoint(cocos2d::CCPoint &p)
{
    m_AnchorPoint = p;
}

}

