

#ifndef __CCPHYSICS_WORLD_DATA_SUPPORT_H_
#define __CCPHYSICS_WORLD_DATA_SUPPORT_H_

#include "cocos2d.h"
#include "chipmunk.h"

using namespace cocos2d;

class cpVectArray : public CCObject
{
public:
    static cpVectArray *createFromCCPointArray(CCPointArray *points);
    static cpVectArray *createFromCCPoint(int numPoints, CCPoint *points);

#if CC_LUA_ENGINE_ENABLED > 0
    static cpVectArray *createFromLuaTable(int vertexes);
#endif

    ~cpVectArray(void);

    int count(void) {
        return m_count;
    }

    cpVect *data(void) {
        return m_verts;
    }

private:
    cpVectArray(void)
    : m_verts(NULL)
    , m_count(0)
    {
    }
    bool initWithCCPointArray(CCPointArray *points);
    bool initWithCCPoint(CCPoint *points, int numPoints);

#if CC_LUA_ENGINE_ENABLED > 0
    bool initWithLuaTable(int vertexes);
#endif

    cpVect *m_verts;
    int m_count;
};

#endif // __CCPHYSICS_WORLD_DATA_SUPPORT_H_
