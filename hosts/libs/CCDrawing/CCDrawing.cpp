

#include "CCDrawing.h"

NS_CC_BEGIN

CCCircleGraph* CCCircleGraph::create(float radius,
                                     float angle,
                                     unsigned int segments,
                                     bool drawLineToCenter)
{
    CCCircleGraph* circle = new CCCircleGraph();
    circle->m_radius = radius;
    circle->m_angle = angle;
    circle->m_segments = m_segments;
    circle->m_drawLineToCenter = drawLineToCenter;
    circle->autorelease();
    return circle;
}

void CCCircleGraph::draw(void)
{
    ccDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
    ccDrawCircle(getPosition(), m_radius, m_angle, m_segments, m_drawLineToCenter);
}


#pragma mark -

CCRectGraph* CCRectGraph::create(const cocos2d::CCSize &size, bool fill)
{
    CCRectGraph* rect = new CCRectGraph();
    rect->m_size = size;
    rect->m_fill = fill;
    rect->autorelease();
    return rect;
}

void CCRectGraph::draw(void)
{
    CCPoint destination = getPosition();
    destination.x += m_size.width;
    destination.y -= m_size.height;
    
    if (m_fill)
    {
        ccDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
        ccDrawRect(getPosition(), destination);
    }
    else
    {
        ccDrawSolidRect(getPosition(), destination, m_color);
    }
}


#pragma mark -

CCPointGraph* CCPointGraph::create(void)
{
    CCPointGraph* point = new CCPointGraph();
    point->autorelease();
    return point;
}

void CCPointGraph::draw(void)
{
    ccDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
    ccDrawPoint(getPosition());
}


#pragma mark -

CCPolygonGraph* CCPolygonGraph::create(cocos2d::CCArray *vertices, bool fill, bool close)
{
    CCPolygonGraph* polygon = new CCPolygonGraph();
    polygon->m_numberOfVertices = vertices->count();
    polygon->m_vertices = new CCPoint[polygon->m_numberOfVertices];
    for (int i = 0; i < polygon->m_numberOfVertices; ++i)
    {
        polygon->m_vertices[i] = *(static_cast<CCPoint*>(vertices->objectAtIndex(i)));
    }
    polygon->m_fill = fill;
    polygon->m_close = close;
    polygon->autorelease();
    return polygon;
}

CCPolygonGraph::~CCPolygonGraph(void)
{
    delete[] m_vertices;
}

void CCPolygonGraph::draw(void)
{
    if (m_fill)
    {
        ccDrawSolidPoly(m_vertices, m_numberOfVertices, m_color);
    }
    else
    {
        ccDrawColor4F(m_color.r, m_color.g, m_color.b, m_color.a);
        ccDrawPoly(m_vertices, m_numberOfVertices, m_close);
    }
}

NS_CC_END
