#ifndef __FRAME_H__
#define __FRAME_H__
#include "utils/preDB.h"
namespace dragonBones
{
    /** @private */
    class Frame
    {
    public:
        Number position;
        Number duration;
        
        String action;
        String event;
        String sound;
        
        Frame()
        {
            position = 0;
            duration = 0;
        }
        
        virtual void dispose()
        {
        }
    };
};
#endif // __FRAME_H__
