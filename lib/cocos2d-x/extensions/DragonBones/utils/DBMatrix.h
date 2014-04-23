
#ifndef __DG_MATRIX_H__
#define __DG_MATRIX_H__
#include "preDB.h"
#include "Point.h"
namespace dragonBones
{


    struct DBMatrix {
        float a, b, c, d;
        float tx, ty;
    };

    DBMatrix __MatrixMake(float a, float b, float c, float d, float tx, float ty);
#define MatrixMake __MatrixMake

    Point __PointApplyMatrix(const Point& point, const DBMatrix& t);
#define PointApplyMatrix __PointApplyMatrix

    //CCSize __CCSizeApplyMatrix(const CCSize& size, const DBMatrix& t);
    //#define CCSizeApplyMatrix __CCSizeApplyMatrix

    DBMatrix MatrixMakeIdentity();
    //CCRect CCRectApplyMatrix(const CCRect& rect, const DBMatrix& anMatrix);

    DBMatrix MatrixTranslate(const DBMatrix& t, float tx, float ty);
    DBMatrix MatrixRotate(const DBMatrix& aTransform, float anAngle);
    DBMatrix MatrixScale(const DBMatrix& t, float sx, float sy);
    DBMatrix MatrixConcat(const DBMatrix& t1, const DBMatrix& t2);
    bool MatrixEqualToTransform(const DBMatrix& t1, const DBMatrix& t2);
    DBMatrix MatrixInvert(const DBMatrix& t);

    extern const DBMatrix MatrixIdentity;
};
#endif // __COCOA_CGAFFINETRANSFORM_H__
