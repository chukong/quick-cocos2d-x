#ifndef __COLOR_TRANSFORM_H__
#define __COLOR_TRANSFORM_H__

#include "preDB.h"
namespace dragonBones
{    
    /** @private */
    class ColorTransform
    {
    public:
        ColorTransform()
        {
            alphaMultiplier = 0;
            alphaOffset = 0;
            blueMultiplier = 0;
            blueOffset = 0;
            color = 0;
            greenMultiplier = 0;
            greenOffset = 0;
            redMultiplier = 0;
            redOffset = 0;
        }
        // 与 Alpha 透明度通道值相乘的十进制值。 ColorTransform 
        Number alphaMultiplier;

        // -255 到 255 之间的数字，它先与 alphaMultiplier 值相乘，再与 Alpha 透明度通道值相加。 ColorTransform 
        Number alphaOffset;

        // 与蓝色通道值相乘的十进制值。 ColorTransform 
        Number blueMultiplier;

        // -255 到 255 之间的数字，它先与 blueMultiplier 值相乘，再与蓝色通道值相加。 ColorTransform 
        Number blueOffset;

        // ColorTransform 对象的 RGB 颜色值。 ColorTransform 
        uint color;

        // 与绿色通道值相乘的十进制值。 ColorTransform 
        Number greenMultiplier;

        // -255 到 255 之间的数字，它先与 greenMultiplier 值相乘，再与绿色通道值相加。 ColorTransform 
        Number greenOffset;

        // 与红色通道值相乘的十进制值。 ColorTransform 
        Number redMultiplier;

        // -255 到 255 之间的数字，它先与 redMultiplier 值相乘，再与红色通道值相加。 
        Number redOffset;        
    };
    
};
#endif // __COLOR_TRANSFORM_H__
