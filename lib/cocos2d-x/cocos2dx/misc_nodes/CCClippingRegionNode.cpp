
#include "CCClippingRegionNode.h"
#include "CCDirector.h"
#include "CCEGLView.h"

NS_CC_BEGIN

CCClippingRegionNode* CCClippingRegionNode::create(const CCRect& clippingRegion)
{
    CCClippingRegionNode* node = new CCClippingRegionNode();
    node->setClippingRegion(clippingRegion);
    node->autorelease();
    return node;
}

CCClippingRegionNode* CCClippingRegionNode::create(void)
{
    CCClippingRegionNode* node = new CCClippingRegionNode();
    node->autorelease();
    return node;
}

void CCClippingRegionNode::setClippingRegion(const CCRect &clippingRegion)
{
    m_clippingRegion = clippingRegion;
    setContentSize(clippingRegion.size);
}

void CCClippingRegionNode::visit() 
{
    if (m_clippingEnabled)
    {
        glEnable(GL_SCISSOR_TEST);
        
        const CCPoint pos = convertToWorldSpace(CCPoint(m_clippingRegion.origin.x, m_clippingRegion.origin.y));
        CCDirector::sharedDirector()->getOpenGLView()->setScissorInPoints(pos.x * m_fScaleX,
                                                                          pos.y * m_fScaleX,
                                                                          m_clippingRegion.size.width * m_fScaleY,
                                                                          m_clippingRegion.size.height * m_fScaleY);
    }
    
    CCNode::visit();
    
    if (m_clippingEnabled)
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

NS_CC_END
