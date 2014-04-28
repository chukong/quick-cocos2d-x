#ifndef __DB_GEOMETRY_H__
#define __DB_GEOMETRY_H__

#include "BytesType.h"

namespace dragonBones
{
    class Point
    {
    public:
        Point(Number xx, Number yy)
            : x(xx)
            , y(yy)
        {

        }
        Point()
            : x(0)
            , y(0)
        {

        }
        Number x;
        Number y;
    };

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

    struct Matrix {
        float a, b, c, d;
        float tx, ty;
    };

    Matrix __MatrixMake(float a, float b, float c, float d, float tx, float ty);
#define MatrixMake __MatrixMake

    Point __PointApplyMatrix(const Point& point, const Matrix& t);
#define PointApplyMatrix __PointApplyMatrix

    //CCSize __CCSizeApplyMatrix(const CCSize& size, const Matrix& t);
    //#define CCSizeApplyMatrix __CCSizeApplyMatrix

    Matrix MatrixMakeIdentity();
    //CCRect CCRectApplyMatrix(const CCRect& rect, const Matrix& anMatrix);

    Matrix MatrixTranslate(const Matrix& t, float tx, float ty);
    Matrix MatrixRotate(const Matrix& aTransform, float anAngle);
    Matrix MatrixScale(const Matrix& t, float sx, float sy);
    Matrix MatrixConcat(const Matrix& t1, const Matrix& t2);
    bool MatrixEqualToTransform(const Matrix& t1, const Matrix& t2);
    Matrix MatrixInvert(const Matrix& t);

    extern const Matrix MatrixIdentity;
}

#endif //__DB_GEOMETRY_H__