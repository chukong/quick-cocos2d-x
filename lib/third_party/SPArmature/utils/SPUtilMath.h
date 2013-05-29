/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.sweetpome.com
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

#pragma  once
#include <math.h>
#include "cocos2d.h"

using namespace cocos2d;

#define SP_PI M_PI

#define SP_DOUBLE_PI (SP_PI*2)

#define SP_HALF_PI  (SP_PI * 0.5f)

#define ANGLE_TO_RADIAN  (M_PI / 180)


bool isSpriteContainPoint(CCSprite *_sprite, CCPoint _point);
bool isSpriteContainPoint(CCSprite *_sprite, CCPoint _point, CCPoint &_outPoint);

#define SP_SPRITE_CONTAIN_POINT(sprite, point) isSpriteContainPoint((sprite), (point))

#define SP_SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point, outPoint) isSpriteContainPoint((sprite), (point), outPoint)




CCPoint bezierTo(float t, CCPoint &point1, CCPoint &point2, CCPoint &point3);
CCPoint bezierTo(float t, CCPoint &point1, CCPoint &point2, CCPoint &point3, CCPoint &point4);

CCPoint circleTo(float t, CCPoint &center, float radius, float fromRadian, float radianDif);


