
#include "CCPhysicsWorldDataSupport.h"


#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#include "CCLuaStack.h"
#endif

cpVectArray *cpVectArray::createFromCCPointArray(CCPointArray *points)
{
    cpVectArray *array = new cpVectArray();
    array->initWithCCPointArray(points);
    array->autorelease();
    return array;
}

cpVectArray *cpVectArray::createFromCCPoint(int numPoints, CCPoint *points)
{
    cpVectArray *array = new cpVectArray();
    array->initWithCCPoint(points, numPoints);
    array->autorelease();
    return array;
}

cpVectArray *cpVectArray::createFromLuaTable(int vertexes)
{
    cpVectArray *array = new cpVectArray();
    array->initWithLuaTable(vertexes);
    array->autorelease();
    return array;
}

cpVectArray::~cpVectArray(void)
{
    free(m_verts);
}

bool cpVectArray::initWithCCPointArray(CCPointArray *points)
{
    CCAssert(points->count() > 0, "cpVectArray::initWithCCPointArray() - can't convert empty array");
    m_count = points->count();
    m_verts = (cpVect*)malloc(sizeof(cpVect) * m_count);
    for (int i = 0; i < m_count; ++i)
    {
        const CCPoint pos = points->get(i);
        m_verts[i] = cpv(pos.x, pos.y);
    }
    return true;
}

bool cpVectArray::initWithCCPoint(CCPoint *points, int numPoints)
{
    CCAssert(numPoints > 0, "cpVectArray::initWithCCPoint() - can't convert empty array");
    m_count = numPoints;
    m_verts = (cpVect*)malloc(sizeof(cpVect) * m_count);
    for (int i = 0; i < m_count; ++i)
    {
        const CCPoint &pos = points[i];
        m_verts[i] = cpv(pos.x, pos.y);
    }
    return true;
}

bool cpVectArray::initWithLuaTable(int vertexes)
{
    lua_State *L = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    if (!lua_istable(L, vertexes)) return NULL;

    m_count = 0;
    lua_pushnil(L);
    while (lua_next(L, vertexes) != 0)
    {
        if (lua_istable(L, -1)) m_count++;
        lua_pop(L, 1);
    }

    m_verts = (cpVect*)malloc(sizeof(cpVect) * m_count);
    lua_pushnil(L);
    int i = 0;
    while (lua_next(L, vertexes) != 0)
    {
        if (!lua_istable(L, -1)) continue;
        lua_rawgeti(L, -1, 1);
        float x = lua_tonumber(L, -1);
        lua_pop(L, 1);
        lua_rawgeti(L, -1, 2);
        float y = lua_tonumber(L, -1);
        lua_pop(L, 1);
        m_verts[i] = cpv(x, y);
        i++;
        lua_pop(L, 1);
    }
    return true;
}
