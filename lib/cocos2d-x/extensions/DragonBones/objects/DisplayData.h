#ifndef __DISPLAY_DATA_H__
#define __DISPLAY_DATA_H__
#include "utils/preDB.h"
#include "objects/DBTransform.h"
namespace dragonBones
{
    /** @private */
    class DisplayData
    {
    public:
        static const String ARMATURE;
        static const String IMAGE;
        
        String name;
        String type;
        DBTransform transform;
        Point pivot;
        
        DisplayData()
        {
        }
        
        void dispose()
        {

        }
    };
};
#endif // __DISPLAY_DATA_H__
