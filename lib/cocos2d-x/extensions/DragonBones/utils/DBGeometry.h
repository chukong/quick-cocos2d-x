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
        Number alphaMultiplier;
        Number alphaOffset;
        Number blueMultiplier;
        Number blueOffset;
        uint color;
        Number greenMultiplier;
        Number greenOffset;
        Number redMultiplier;
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