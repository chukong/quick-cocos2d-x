
#include "CCDrawing.h"
#include "support/CCPointExtension.h"

NS_CC_BEGIN

void CCShapeNode::draw(void)
{
    beforeDraw();
    drawProc();
    afterDraw();
}

void CCShapeNode::beforeDraw(void)
{
    glLineWidth(m_lineWidth);
    ccDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
#ifdef GL_LINE_STIPPLE
    if (m_lineStippleEnabled)
    {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, m_lineStipple);
    }
#endif
}

void CCShapeNode::afterDraw(void)
{
    glLineWidth(1);    
    ccDrawColor4F(1, 1, 1, 1);
#ifdef GL_LINE_STIPPLE
    if (m_lineStippleEnabled)
    {
        glDisable(GL_LINE_STIPPLE);
        glLineStipple(1, 0xFFFF);
    }
#endif
}

CCCircleShape* CCCircleShape::create(float radius,
                                     float angle,
                                     unsigned int segments,
                                     bool drawLineToCenter)
{
    CCCircleShape* circle = new CCCircleShape();
    circle->m_radius = radius;
    circle->m_angle = angle;
    circle->m_segments = segments;
    circle->m_drawLineToCenter = drawLineToCenter;
    circle->m_scaleX = 1.0f;
    circle->m_scaleY = 1.0f;
    circle->autorelease();
    return circle;
}

void CCCircleShape::drawProc(void)
{
    ccDrawCircle(getDrawPosition(), m_radius, m_angle, m_segments, m_drawLineToCenter, m_scaleX, m_scaleY);
}


#pragma mark -

CCRectShape* CCRectShape::create(const cocos2d::CCSize &size, bool fill)
{
    CCRectShape* rect = new CCRectShape();
    rect->m_size = size;
    rect->m_fill = fill;
    rect->autorelease();
    return rect;
}

void CCRectShape::drawProc(void)
{
    const CCPoint center = getDrawPosition();
    float w = m_size.width / 2;
    float h = m_size.height / 2;
    
    if (m_fill)
    {
        ccDrawSolidRect(ccp(center.x - w, center.y + h), ccp(center.x + w, center.y - h), m_color);
    }
    else
    {
        ccDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
        ccDrawRect(ccp(center.x - w, center.y + h), ccp(center.x + w, center.y - h));
    }
}


#pragma mark -

CCPointShape* CCPointShape::create(void)
{
    CCPointShape* point = new CCPointShape();
    point->autorelease();
    return point;
}

void CCPointShape::drawProc(void)
{
    ccDrawPoint(getDrawPosition());
}


#pragma mark -

CCPolygonShape* CCPolygonShape::create(cocos2d::CCArray *vertices, bool fill, bool close)
{
    CCAssert(vertices->count() > 0, "vertices->count() > 0");
    CCPolygonShape* polygon = new CCPolygonShape();
    polygon->m_numberOfVertices = vertices->count();
    polygon->m_vertices         = new CCPoint[polygon->m_numberOfVertices];
    polygon->m_verticesDraw     = new CCPoint[polygon->m_numberOfVertices];
    for (unsigned int i = 0; i < polygon->m_numberOfVertices; ++i)
    {
        CCPoint* pt = static_cast<CCPoint*>(vertices->objectAtIndex(i));
        polygon->m_vertices[i]     = *pt;
        polygon->m_verticesDraw[i] = *pt;
    }
    polygon->m_fill  = fill;
    polygon->m_close = close;
    polygon->autorelease();
    return polygon;
}

CCPolygonShape::~CCPolygonShape(void)
{
    delete[] m_vertices;
    delete[] m_verticesDraw;
}

void CCPolygonShape::drawProc(void)
{
    const CCPoint center = getDrawPosition();
    for (unsigned int i = 0; i < m_numberOfVertices; ++i)
    {
        m_verticesDraw[i].x = m_vertices[i].x + center.x;
        m_verticesDraw[i].y = m_vertices[i].y + center.y;
    }
    
    if (m_fill)
    {
        ccDrawSolidPoly(m_verticesDraw, m_numberOfVertices, m_color);
    }
    else
    {
        ccDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
        ccDrawPoly(m_verticesDraw, m_numberOfVertices, m_close);
    }
}

NS_CC_END
