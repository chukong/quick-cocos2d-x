#include "DBGeometry.h"
#include <algorithm>
#include <math.h>

using namespace std;

namespace dragonBones
{


    Matrix __MatrixMake(float a, float b, float c, float d, float tx, float ty)
    {
        Matrix t;
        t.a = a; t.b = b; t.c = c; t.d = d; t.tx = tx; t.ty = ty;
        return t;
    }

    Point __PointApplyMatrix(const Point& point, const Matrix& t)
    {
        Point p;
        p.x = (float)((double)t.a * point.x + (double)t.c * point.y + t.tx);
        p.y = (float)((double)t.b * point.x + (double)t.d * point.y + t.ty);
        return p;
    }



    Matrix MatrixMakeIdentity()
    {
        return __MatrixMake(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    }

    extern const Matrix MatrixIdentity = MatrixMakeIdentity();

    //
    //CCRect CCRectApplyMatrix(const CCRect& rect, const Matrix& anMatrix)
    //{
    //    float top    = rect.getMinY();
    //    float left   = rect.getMinX();
    //    float right  = rect.getMaxX();
    //    float bottom = rect.getMaxY();
    //    
    //    Point topLeft = PointApplyMatrix(PointMake(left, top), anMatrix);
    //    Point topRight = PointApplyMatrix(PointMake(right, top), anMatrix);
    //    Point bottomLeft = PointApplyMatrix(PointMake(left, bottom), anMatrix);
    //    Point bottomRight = PointApplyMatrix(PointMake(right, bottom), anMatrix);
    //
    //    float minX = min(min(topLeft.x, topRight.x), min(bottomLeft.x, bottomRight.x));
    //    float maxX = max(max(topLeft.x, topRight.x), max(bottomLeft.x, bottomRight.x));
    //    float minY = min(min(topLeft.y, topRight.y), min(bottomLeft.y, bottomRight.y));
    //    float maxY = max(max(topLeft.y, topRight.y), max(bottomLeft.y, bottomRight.y));
    //        
    //    return CCRectMake(minX, minY, (maxX - minX), (maxY - minY));
    //}

    Matrix MatrixTranslate(const Matrix& t, float tx, float ty)
    {
        return __MatrixMake(t.a, t.b, t.c, t.d, t.tx + t.a * tx + t.c * ty, t.ty + t.b * tx + t.d * ty);
    }

    Matrix MatrixScale(const Matrix& t, float sx, float sy)
    {
        return __MatrixMake(t.a * sx, t.b * sx, t.c * sy, t.d * sy, t.tx, t.ty);
    }

    Matrix MatrixRotate(const Matrix& t, float anAngle)
    {
        float fSin = sin(anAngle);
        float fCos = cos(anAngle);

        return __MatrixMake(t.a * fCos + t.c * fSin,
            t.b * fCos + t.d * fSin,
            t.c * fCos - t.a * fSin,
            t.d * fCos - t.b * fSin,
            t.tx,
            t.ty);
    }

    /* Concatenate `t2' to `t1' and return the result:
    t' = t1 * t2 */
    Matrix MatrixConcat(const Matrix& t1, const Matrix& t2)
    {
        return __MatrixMake(t1.a * t2.a + t1.b * t2.c, t1.a * t2.b + t1.b * t2.d, //a,b
            t1.c * t2.a + t1.d * t2.c, t1.c * t2.b + t1.d * t2.d, //c,d
            t1.tx * t2.a + t1.ty * t2.c + t2.tx,                  //tx
            t1.tx * t2.b + t1.ty * t2.d + t2.ty);                  //ty
    }

    /* Return true if `t1' and `t2' are equal, false otherwise. */
    bool MatrixEqualToTransform(const Matrix& t1, const Matrix& t2)
    {
        return (t1.a == t2.a && t1.b == t2.b && t1.c == t2.c && t1.d == t2.d && t1.tx == t2.tx && t1.ty == t2.ty);
    }

    Matrix MatrixInvert(const Matrix& t)
    {
        float determinant = 1 / (t.a * t.d - t.b * t.c);

        return __MatrixMake(determinant * t.d, -determinant * t.b, -determinant * t.c, determinant * t.a,
            determinant * (t.c * t.ty - t.d * t.tx), determinant * (t.b * t.tx - t.a * t.ty));
    }
};