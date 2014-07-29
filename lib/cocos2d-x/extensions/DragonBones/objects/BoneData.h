#ifndef __BONE_DATA_H__
#define __BONE_DATA_H__
#include "utils/preDB.h"
#include "DBTransform.h"
namespace dragonBones
{
    class BoneData
    {
    public:
        String name;
        String parent;
        Number length;
        
        DBTransform global;
        DBTransform transform;
        
        int scaleMode;
        bool fixedRotation;
        
        BoneData()
        {
            length = 0;
            //global = new DBTransform();
            //transform = new DBTransform();
            scaleMode = 1;
            fixedRotation = false;
        }
        
        void dispose()
        {
            //global = null;
            //transform = null;
        }
    };
};
#endif // __BONE_DATA_H__
