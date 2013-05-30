/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.cocostudio.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef COCOSTUDIO_CSUTILMATH_H
#define COCOSTUDIO_CSUTILMATH_H


#include <math.h>
#include "cocos2d.h"
#include "CSArmatureDefine.h"
#include "CSBone.h"


#define CS_PI M_PI

#define CS_DOUBLE_PI (CS_PI*2)

#define CS_HALF_PI  (CS_PI * 0.5f)

#define ANGLE_TO_RADIAN  (M_PI / 180)

namespace cs {

//! hit test function
bool isSpriteContainPoint(cocos2d::CCSprite *sprite, cocos2d::CCPoint point);
bool isSpriteContainPoint(cocos2d::CCSprite *sprite, cocos2d::CCPoint point,cocos2d::CCPoint &outPoint);

#define CS_SPRITE_CONTAIN_POINT(sprite, point) isSpriteContainPoint((sprite), (point))

#define CS_SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point, outPoint) isSpriteContainPoint((sprite), (point), outPoint)


//! motion curve function
cocos2d::CCPoint bezierTo(float t, cocos2d::CCPoint &point1, cocos2d::CCPoint &point2, cocos2d::CCPoint &point3);
cocos2d::CCPoint bezierTo(float t, cocos2d::CCPoint &point1, cocos2d::CCPoint &point2, cocos2d::CCPoint &point3, cocos2d::CCPoint &point4);

cocos2d::CCPoint circleTo(float t, cocos2d::CCPoint &center, float radius, float fromRadian, float radianDif);



//! Hit test function
bool isSpriteContainPoint(cocos2d::CCSprite *_sprite, cocos2d::CCPoint _point);
bool isSpriteContainPoint(cocos2d::CCSprite *_sprite, cocos2d::CCPoint _point, cocos2d::CCPoint &_outPoint);

#define CS_SPRITE_CONTAIN_POINT(sprite, point) isSpriteContainPoint((sprite), (point))
#define CS_SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point, outPoint) isSpriteContainPoint((sprite), (point), outPoint)


//! Motion curve function
cocos2d::CCPoint bezierTo(float t, cocos2d::CCPoint &point1, cocos2d::CCPoint &point2, cocos2d::CCPoint &point3);
cocos2d::CCPoint bezierTo(float t, cocos2d::CCPoint &point1, cocos2d::CCPoint &point2, cocos2d::CCPoint &point3, cocos2d::CCPoint &point4);

cocos2d::CCPoint circleTo(float t, cocos2d::CCPoint &center, float radius, float fromRadian, float radianDif);


//! IK function

enum CCD_Result
{
	Success,
	Processing,
	Failure
};

double simplifyAngle(double angle);
float simplifyAngle(float angle);

CS_EXTERN CCD_Result CalcIK_CCD(Bone *startBone, Bone *endBone, cocos2d::CCPoint &targetPoint, float arrivalDist);

}

#endif