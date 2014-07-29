#include "TransformUtil.h"
#include <cmath>
namespace dragonBones
{

        const Number TransformUtil::PI = 3.14159265f;
        const Number TransformUtil::HALF_PI = TransformUtil::PI * 0.5f;
        const Number TransformUtil::DOUBLE_PI = TransformUtil::PI * 2;        
        Matrix _helpMatrix;

        void transformToMatrix(DBTransform &transform, Matrix &matrix)
        {
            matrix.a = transform.scaleX * cos(transform.skewY);
            matrix.b = transform.scaleX * sin(transform.skewY);
            matrix.c = -transform.scaleY * sin(transform.skewX);
            matrix.d = transform.scaleY * cos(transform.skewX);
            matrix.tx = transform.x;
            matrix.ty = transform.y;
        }

        void TransformUtil::transformPointWithParent(DBTransform &transform, DBTransform &parent)
        {
            transformToMatrix(parent, _helpMatrix);
            _helpMatrix = MatrixInvert(_helpMatrix);

            Number x = transform.x;
            Number y = transform.y;

            transform.x = _helpMatrix.a * x + _helpMatrix.c * y + _helpMatrix.tx;
            transform.y = _helpMatrix.d * y + _helpMatrix.b * x + _helpMatrix.ty;

            transform.skewX = formatRadian(transform.skewX - parent.skewX);
            transform.skewY = formatRadian(transform.skewY - parent.skewY);
        }


        Number TransformUtil::formatRadian(Number radian)
        {
            radian = fmod(radian , DOUBLE_PI);
            if (radian > PI)
            {
                radian -= DOUBLE_PI;
            }
            if (radian < -PI)
            {
                radian += DOUBLE_PI;
            }
            return radian;
        }

};
