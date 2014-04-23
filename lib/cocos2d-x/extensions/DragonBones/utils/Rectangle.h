#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__
#include "BytesType.h"
namespace dragonBones
{    
    class Rectangle
    {
    public:
        Rectangle()
            : x(0)
            , y(0)
            , width(0)
            , height(0)
        {

        }
        int x;
        int y;
        int width;
        int height;
    };
};
#endif // __RECTANGLE_H__
