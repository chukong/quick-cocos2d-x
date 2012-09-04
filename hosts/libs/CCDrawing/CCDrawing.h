/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.
 
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

#ifndef __CCDRAWING_H_
#define __CCDRAWING_H_

#include "CCDrawingPrimitives.h"
#include "base_nodes/CCNode.h"

NS_CC_BEGIN

class CCGraphNode : public CCNode
{
    const ccColor4F& getColor(void)
    {
        return m_color;
    }
    
    void setColor(const ccColor4F& color)
    {
        m_color = color;
    }
    
protected:
    ccColor4F m_color;

    CCGraphNode(void)
    {
        m_color = ccc4f(0, 0, 0, 1);
    }
};


#pragma mark -

class CCCircleGraph : public CCGraphNode
{
public:
    CCCircleGraph* create(float radius,
                          float angle = 0,
                          unsigned int segments = 10,
                          bool drawLineToCenter = false);
    
    float getRadius(void)
    {
        return m_radius;
    }
    
    void setRadius(float radius)
    {
        m_radius = radius;
    }
    
    float getAngle(void)
    {
        return m_angle;
    }
    
    void setAngle(float angle)
    {
        m_angle = angle;
    }
    
    unsigned int getSegments(void)
    {
        return m_segments;
    }
    
    void setSegments(unsigned int segments)
    {
        m_segments = segments;
    }
    
    bool getDrawLineToCenter(void)
    {
        return m_drawLineToCenter;
    }
    
    void setDrawLineToCenter(bool drawLineToCenter)
    {
        m_drawLineToCenter = drawLineToCenter;
    }
    
    virtual void draw(void);
    
protected:
    float m_radius;
    float m_angle;
    unsigned int m_segments;
    bool m_drawLineToCenter;
};


#pragma mark -

class CCRectGraph : public CCGraphNode
{
public:
    CCRectGraph* create(const CCSize& size, bool fill);
    
    const CCSize& getSize(void)
    {
        return m_size;
    }
    
    void setSize(const CCSize& size)
    {
        m_size = size;
    }
    
    bool getFill(void)
    {
        return m_fill;
    }
    
    void setFill(bool fill)
    {
        m_fill = fill;
    }
    
    virtual void draw(void);
    
protected:
    CCSize m_size;
    bool m_fill;
};


#pragma mark -

class CCPointGraph : public CCGraphNode
{
public:
    CCPointGraph* create(void);
    virtual void draw(void);
};


#pragma mark -

class CCPolygonGraph : public CCGraphNode
{
public:
    CCPolygonGraph* create(CCArray* vertices, bool fill, bool close);
    ~CCPolygonGraph(void);
    
    bool getFill(void)
    {
        return m_fill;
    }
    
    void setFill(bool fill)
    {
        m_fill = fill;
    }
    
    bool getClose(void)
    {
        return m_close;
    }
    
    void setClose(bool close)
    {
        m_close = close;
    }
    
    virtual void draw(void);
    
protected:
    CCPoint* m_vertices;
    unsigned int m_numberOfVertices;
    bool m_fill;
    bool m_close;
};


NS_CC_END

#endif /* __CCDRAWING_H_ */

