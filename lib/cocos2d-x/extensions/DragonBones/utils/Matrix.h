
#ifndef __DG_MATRIX_H__
#define __DG_MATRIX_H__
#include "preDB.h"
#include "Point.h"
namespace dragonBones
{


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
};
#endif // __COCOA_CGAFFINETRANSFORM_H__
