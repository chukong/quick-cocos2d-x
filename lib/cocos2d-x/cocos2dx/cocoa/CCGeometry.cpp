/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCGeometry.h"
#include "ccMacros.h"

// implementation of CCPoint
NS_CC_BEGIN

CCPoint::CCPoint(void)
{
    setPoint(0.0f, 0.0f);
}

CCPoint::CCPoint(float x, float y)
{
    setPoint(x, y);
}

CCPoint::CCPoint(const CCPoint& other)
{
    setPoint(other.x, other.y);
}

CCPoint& CCPoint::operator= (const CCPoint& other)
{
    setPoint(other.x, other.y);
    return *this;
}

void CCPoint::setPoint(float x, float y)
{
    this->x = x;
    this->y = y;
}

bool CCPoint::equals(const CCPoint& target) const
{
    return ((x == target.x) && (y == target.y));
}


/*
 *  Implementation of CCPointArray
 */

CCPointArray* CCPointArray::create(unsigned int capacity)
{
    CCPointArray* ret = new CCPointArray();
    if (ret)
    {
        if (ret->initWithCapacity(capacity))
        {
            ret->autorelease();
        }
        else 
        {
            delete ret;
            ret = NULL;
        }
    }
    
    return ret;
}


bool CCPointArray::initWithCapacity(unsigned int capacity)
{
    m_pPoints = new vector<CCPoint*>();
    
    return true;
}

CCObject* CCPointArray::copyWithZone(cocos2d::CCZone *zone)
{
    vector<CCPoint*> *newArray = new vector<CCPoint*>();
    vector<CCPoint*>::iterator iter;
    for (iter = m_pPoints->begin(); iter != m_pPoints->end(); ++iter)
    {
        newArray->push_back(new CCPoint((*iter)->x, (*iter)->y));
    }
    
    CCPointArray *points = new CCPointArray();
    points->initWithCapacity(10);
    points->setPoints(newArray);
    
    return points;
}

CCPointArray::~CCPointArray()
{
    removeAll();
    delete m_pPoints;
}

CCPointArray::CCPointArray() :m_pPoints(NULL){}

const std::vector<CCPoint*>* CCPointArray::getPoints()
{
    return m_pPoints;
}

void CCPointArray::setPoints(vector<CCPoint*> *points)
{
    CCAssert(points != NULL, "points should not be NULL");
    
    // delete old points
    vector<CCPoint*>::iterator iter;
    for (iter = m_pPoints->begin(); iter != m_pPoints->end(); ++iter)
    {
        delete *iter;
    }
    delete m_pPoints;
    
    m_pPoints = points;
}

void CCPointArray::add(CCPoint point)
{    
    m_pPoints->push_back(new CCPoint(point.x, point.y));
}

void CCPointArray::insert(CCPoint &point, unsigned int index)
{
    CCPoint *temp = new CCPoint(point.x, point.y);
    m_pPoints->insert(m_pPoints->begin() + index, temp);
}

CCPoint CCPointArray::get(unsigned int index)
{
    index = MIN(m_pPoints->size()-1, MAX(index, 0));
    return *(m_pPoints->at(index));
}

void CCPointArray::replace(cocos2d::CCPoint &point, unsigned int index)
{
    
    CCPoint *temp = m_pPoints->at(index);
    temp->x = point.x;
    temp->y = point.y;
}

void CCPointArray::remove(unsigned int index)
{
    vector<CCPoint*>::iterator iter = m_pPoints->begin() + index;
    CCPoint* pRemovedPoint = *iter;
    m_pPoints->erase(iter);
    delete pRemovedPoint;
}

void CCPointArray::removeAll(void)
{
    vector<CCPoint*>::iterator iter;
    for (iter = m_pPoints->begin(); iter != m_pPoints->end(); ++iter)
    {
        delete *iter;
    }
    m_pPoints->clear();
}

unsigned int CCPointArray::count()
{
    return m_pPoints->size();
}

CCPointArray* CCPointArray::reverse()
{
    vector<CCPoint*> *newArray = new vector<CCPoint*>();
    vector<CCPoint*>::reverse_iterator iter;
    CCPoint *point = NULL;
    for (iter = m_pPoints->rbegin(); iter != m_pPoints->rend(); ++iter)
    {
        point = *iter;
        newArray->push_back(new CCPoint(point->x, point->y));
    }
    CCPointArray *config = CCPointArray::create(0);
    config->setPoints(newArray);
    
    return config;
}

void CCPointArray::reverseInline()
{
    unsigned int l = m_pPoints->size();
    CCPoint *p1 = NULL;
    CCPoint *p2 = NULL;
    int x, y;
    for (unsigned int i = 0; i < l/2; ++i)
    {
        p1 = m_pPoints->at(i);
        p2 = m_pPoints->at(l-i-1);
        
        x = p1->x;
        y = p1->y;
        
        p1->x = p2->x;
        p1->y = p2->y;
        
        p2->x = x;
        p2->y = y;
    }
}

CCPoint *CCPointArray::fetchPoints(void)
{
    if (m_pPoints->size() == 0) return NULL;
    
    CCPoint *points = new CCPoint[m_pPoints->size()];
    vector<CCPoint*>::iterator iter;
    int index = 0;
    for (iter = m_pPoints->begin(); iter != m_pPoints->end(); ++iter)
    {
        points[index++] = *(*iter);
    }
    return points;
}

// implementation of CCSize

CCSize::CCSize(void)
{
    setSize(0.0f, 0.0f);
}

CCSize::CCSize(float width, float height)
{
    setSize(width, height);
}

CCSize::CCSize(const CCSize& other)
{
    setSize(other.width, other.height);
}

CCSize& CCSize::operator= (const CCSize& other)
{
    setSize(other.width, other.height);
    return *this;
}

void CCSize::setSize(float width, float height)
{
    this->width = width;
    this->height = height;
}

bool CCSize::equals(const CCSize& target) const
{
    return ((width == target.width) && (height == target.height));
}

// implementation of CCRect

CCRect::CCRect(void)
{
    setRect(0.0f, 0.0f, 0.0f, 0.0f);
}

CCRect::CCRect(float x, float y, float width, float height)
{
    setRect(x, y, width, height);
}

CCRect::CCRect(const CCRect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
}

CCRect& CCRect::operator= (const CCRect& other)
{
    setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
    return *this;
}

void CCRect::setRect(float x, float y, float width, float height)
{
    // CGRect can support width<0 or height<0
    // CCAssert(width >= 0.0f && height >= 0.0f, "width and height of Rect must not less than 0.");

    origin.x = x;
    origin.y = y;

    size.width = width;
    size.height = height;
}

bool CCRect::equals(const CCRect& rect) const
{
    return (origin.equals(rect.origin) && 
            size.equals(rect.size));
}

float CCRect::getMaxX() const
{
    return (float)(origin.x + size.width);
}

float CCRect::getMidX() const
{
    return (float)(origin.x + size.width / 2.0);
}

float CCRect::getMinX() const
{
    return origin.x;
}

float CCRect::getMaxY() const
{
    return origin.y + size.height;
}

float CCRect::getMidY() const
{
    return (float)(origin.y + size.height / 2.0);
}

float CCRect::getMinY() const
{
    return origin.y;
}

bool CCRect::containsPoint(const CCPoint& point) const
{
    bool bRet = false;

    if (point.x >= getMinX() && point.x <= getMaxX()
        && point.y >= getMinY() && point.y <= getMaxY())
    {
        bRet = true;
    }

    return bRet;
}

bool CCRect::intersectsRect(const CCRect& rect) const
{
    return !(     getMaxX() < rect.getMinX() ||
             rect.getMaxX() <      getMinX() ||
                  getMaxY() < rect.getMinY() ||
             rect.getMaxY() <      getMinY());
}

NS_CC_END
