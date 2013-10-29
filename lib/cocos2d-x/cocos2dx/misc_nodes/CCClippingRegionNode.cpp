
#include "CCClippingRegionNode.h"
#include "CCDirector.h"
#include "CCEGLView.h"

NS_CC_BEGIN

namespace detail {

    class ClipHelper
    {
    public:
        ClipHelper() : m_clipped(false)
        {
            m_alreadyClipped = CCEGLView::sharedOpenGLView()->isScissorEnabled();
            if(m_alreadyClipped)
                m_parentClipRect = CCEGLView::sharedOpenGLView()->getScissorRect();
        }

        bool clip(const CCRect &rect)
        {
            CCRect realClipRect = rect;

            if(m_alreadyClipped)
            {
                if(!rect.intersectsRect(m_parentClipRect))
                    return false;

                realClipRect = intersect(rect, m_parentClipRect);
            }

            m_clipped = true;
            if(!m_alreadyClipped)
                glEnable(GL_SCISSOR_TEST);
            CCEGLView::sharedOpenGLView()->setScissorInPoints(
                    realClipRect.getMinX(),
                    realClipRect.getMinY(),
                    realClipRect.size.width,
                    realClipRect.size.height);

            return true;
        }

        ~ClipHelper()
        {
            if(m_alreadyClipped && m_clipped)
                CCEGLView::sharedOpenGLView()->setScissorInPoints(
                        m_parentClipRect.getMinX(),
                        m_parentClipRect.getMinY(),
                        m_parentClipRect.size.width,
                        m_parentClipRect.size.height);

            if(m_clipped && !m_alreadyClipped)
                glDisable(GL_SCISSOR_TEST);
        }

    private:
        bool m_clipped;
        bool m_alreadyClipped;
        CCRect m_parentClipRect;

        float min_(float x, float y) { return x < y ? x : y; }
        float max_(float x, float y) { return x < y ? y : x; }

        CCRect intersect(const CCRect &r1, const CCRect &r2)
        {
            float minX = max_(r1.getMinX(), r2.getMinX());
            float minY = max_(r1.getMinY(), r2.getMinY());
            float width = min_(r1.getMaxX(), r2.getMaxX()) - minX;
            float height = min_(r1.getMaxY(), r2.getMaxY()) - minY;

            return CCRect(minX, minY, width, height);
        }
    };

}

CCClippingRegionNode* CCClippingRegionNode::create(void)
{
    CCClippingRegionNode* node = new CCClippingRegionNode();
    node->autorelease();
    return node;
}

void CCClippingRegionNode::visit()
{
    if(!isVisible())
        return;

    detail::ClipHelper helper;
    if(helper.clip(getViewRect()))
        CCNode::visit();
}

CCRect CCClippingRegionNode::getViewRect()
{
    CCPoint screenPos = convertToWorldSpace(CCPointZero);

    float scaleX = getScaleX();
    float scaleY = getScaleY();

    for(CCNode *p = m_pParent; p != NULL; p = p->getParent())
    {
        scaleX *= p->getScaleX();
        scaleY *= p->getScaleY();
    }

    CCSize size = getContentSize();
    if(scaleX < 0.0f)
    {
        screenPos.x += size.width * scaleX;
        scaleX = -scaleX;
    }

    if(scaleY < 0.0f)
    {
        screenPos.y += size.height * scaleY;
        scaleY = -scaleY;
    }

    return CCRectMake(screenPos.x, screenPos.y, size.width * scaleX, size.height * scaleY);
}

NS_CC_END
