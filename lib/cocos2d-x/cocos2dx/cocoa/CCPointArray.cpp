
#include "cocoa/CCPointArray.h"
#include "ccMacros.h"

NS_CC_BEGIN

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

const CCPoint CCPointArray::get(unsigned int index)
{
    index = MIN((unsigned int)m_pPoints->size() - 1, MAX(index, 0));
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
    return (unsigned int)m_pPoints->size();
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
    size_t l = m_pPoints->size();
    CCPoint *p1 = NULL;
    CCPoint *p2 = NULL;
    int x, y;
    for (size_t i = 0; i < l/2; ++i)
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

NS_CC_END
