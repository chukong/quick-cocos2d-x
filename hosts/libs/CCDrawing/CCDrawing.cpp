
#include "CCDrawing.h"
#include "support/CCPointExtension.h"

NS_CC_BEGIN

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
    circle->autorelease();
    return circle;
}

void CCCircleShape::draw(void)
{
    ccDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
    ccDrawCircle(getDrawPosition(), m_radius, m_angle, m_segments, m_drawLineToCenter);
    ccDrawColor4F(1, 1, 1, 1);
}


#pragma mark -

CCRectShape* CCRectShape::create(const cocos2d::CCSize &size, bool fill)
{
    CCRectShape* rect = new CCRectShape();
    rect->setSize(size);
    rect->setFill(fill);
    rect->autorelease();
    return rect;
}

void CCRectShape::draw(void)
{
    const CCPoint center = getDrawPosition();
    float w = m_size.width / 2;
    float h = m_size.height / 2;
    
    if (m_fill)
    {
        ccDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
        ccDrawRect(ccp(center.x - w, center.y + h), ccp(center.x + w, center.y - h));
    }
    else
    {
        ccDrawSolidRect(ccp(center.x - w, center.y + h), ccp(center.x + w, center.y - h), m_color);
    }
}


#pragma mark -

CCPointShape* CCPointShape::create(void)
{
    CCPointShape* point = new CCPointShape();
    point->autorelease();
    return point;
}

void CCPointShape::draw(void)
{
    ccDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
    ccDrawPoint(getDrawPosition());
}


#pragma mark -

CCPolygonShape* CCPolygonShape::create(cocos2d::CCArray *vertices, bool fill, bool close)
{
    CCPolygonShape* polygon = new CCPolygonShape();
    polygon->m_numberOfVertices = vertices->count();
    polygon->m_vertices = new CCPoint[polygon->m_numberOfVertices];
    polygon->m_verticesDraw = new CCPoint[polygon->m_numberOfVertices];
    for (unsigned int i = 0; i < polygon->m_numberOfVertices; ++i)
    {
        polygon->m_vertices[i] = *(static_cast<CCPoint*>(vertices->objectAtIndex(i)));
        polygon->m_verticesDraw[i] = polygon->m_vertices[i];
    }
    polygon->m_fill = fill;
    polygon->m_close = close;
    
    
    polygon->autorelease();
    return polygon;
}

CCPolygonShape::~CCPolygonShape(void)
{
    delete[] m_vertices;
}

void CCPolygonShape::draw(void)
{
    const CCPoint center = getDrawPosition();
    for (unsigned int i = 0; i < m_numberOfVertices; ++i)
    {
        m_verticesDraw[i] = ccpAdd(m_vertices[i], center);
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
