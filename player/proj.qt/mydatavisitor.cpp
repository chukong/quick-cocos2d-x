#include "mydatavisitor.h"
#include "mydatapriter.h"

USING_NS_CC;

MyDataVisitor::MyDataVisitor(int /*indentLevel*/)
    : CCDataVisitor()
{
    m_data = CCDictionary::create();
}

MyDataVisitor::~MyDataVisitor()
{
    if (m_data) {
        m_data->release();
    }

    m_data = NULL;
}

void MyDataVisitor::visitObject(const CCObject *p)
{
    CCNode *pNode = dynamic_cast<CCNode *>(const_cast<CCObject*>(p));
    std::string className;
    if (pNode) {
        className = "CCNode";

        // position
        m_data->setObject(CCString::createWithFormat("{%.2f,%.2f}", pNode->getPositionX(), pNode->getPositionY())
                          , "position");

        // rotation
        m_data->setObject(CCFloat::create(pNode->getRotation()), "rotation");

        // scale
        m_data->setObject(CCFloat::create(pNode->getScaleX()), "scaleX");
        m_data->setObject(CCFloat::create(pNode->getScaleY()), "scaleY");

        // zOrder
        m_data->setObject(CCInteger::create(pNode->getZOrder()), "zOrder");

        // skew
        m_data->setObject(CCFloat::create(pNode->getSkewX()), "skewX");
        m_data->setObject(CCFloat::create(pNode->getSkewY()), "skewY");

        // anchorPoint
        m_data->setObject(CCString::createWithFormat("{%.2f,%.2f}", pNode->getAnchorPoint().x, pNode->getAnchorPoint().y)
                          , "anchorPoint");

        // visible
        m_data->setObject(CCBool::create(pNode->isVisible()), "visible");

        // contentSize
        m_data->setObject(CCString::createWithFormat("{%.2f,%.2f}", pNode->getContentSize().width, pNode->getContentSize().height)
                          , "contentSize");

        // tag
        m_data->setObject(CCInteger::create(pNode->getTag()), "tag");
    }
#if 0
    CCNodeRGBA *pNodeRGBA = dynamic_cast<CCSprite*>(const_cast<CCObject*>(p));
    if (pNodeRGBA) {
        className = "CCNodeRGBA";

        m_data->setObject(CCString::createWithFormat("{%d,%d,%d}"
                                                     , pNodeRGBA->getColor().r
                                                     , pNodeRGBA->getColor().g
                                                     , pNodeRGBA->getColor().b), "color");
        m_data->setObject(CCFloat::create(pNodeRGBA->getOpacity()), "opacity");
    }
#endif
    CCSprite *pSprite = dynamic_cast<CCSprite*>(const_cast<CCObject*>(p));
    if (pSprite) {
        className = "CCSprite";

        // flip
        m_data->setObject(CCBool::create(pSprite->isFlipX()), "isFlipX");
        m_data->setObject(CCBool::create(pSprite->isFlipY()), "isFlipY");

        // texture
        CCDictionary *textureDict = CCTextureCache::sharedTextureCache()->snapshotTextures();
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(textureDict, pElement)
        {
            if (pElement->getObject() == pSprite->getTexture()) {
                m_data->setObject(CCString::create(pElement->getStrKey()), "textureFileName");
            }
        }
    }

    CCScene *pScene = dynamic_cast<CCScene*>(const_cast<CCObject*>(p));
    if (pScene) {
        className = "CCScene";
    }

    CCLayer *pLayer = dynamic_cast<CCLayer*>(const_cast<CCObject*>(p));
    if (pLayer) {
        className = "CCLayer";

        m_data->setObject(CCBool::create(pLayer->isTouchEnabled()), "isTouchEnabled");
        m_data->setObject(CCBool::create(pLayer->isAccelerometerEnabled()), "isAcceleEnabled");

    }
#if 0
    CCLayerRGBA *pLayerRGBA = dynamic_cast<CCLayerRGBA*>(const_cast<CCObject*>(p));
    if (pLayerRGBA) {
        className = "CCLayerRGBA";

        m_data->setObject(CCString::createWithFormat("{%d,%d,%d}"
                                                     , pLayerRGBA->getColor().r
                                                     , pLayerRGBA->getColor().g
                                                     , pLayerRGBA->getColor().b), "color");
        m_data->setObject(CCFloat::create(pLayerRGBA->getOpacity()), "opacity");
    }

    m_data->setObject(CCString::create(className), "className");
#endif
    unsigned int cnt = pNode->getChildrenCount();
    if (cnt > 0) {
        CCArray *childrenData = CCArray::createWithCapacity(cnt);
        for (unsigned int i = 0; i < cnt; i++) {
            CCNode *childNode = (CCNode*) pNode->getChildren()->objectAtIndex(i);
            MyDataVisitor dv;
            childNode->acceptVisitor(dv);
            childrenData->addObject(dv.getDict());
        }
        m_data->setObject(childrenData, "children");
    }
}

string MyDataVisitor::getResult()
{
    if (m_data) {
//        cocos2d::CCPrettyPrinter dataVisit;
        MyDataPriter dataVisit;
        m_data->acceptVisitor(dataVisit);
        return dataVisit.getResult();
    }
    return std::string();
}


void MyDataVisitor::clear()
{
    if (m_data)
        m_data->removeAllObjects();
}

CCDictionary *MyDataVisitor::getDict()
{
    return m_data;
}
