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

#ifndef COCOSTUDIO_CSDISPLAYFACTORY_H
#define COCOSTUDIO_CSDISPLAYFACTORY_H

#include "cocos2d.h"
#include "CSDatas.h"


namespace cs {
    
class Skin;
class Bone;
class DecorativeDisplay;
class DisplayData;


void CS_DISPLAY_ADD(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
void CS_DISPLAY_CREATE(Bone *bone, DecorativeDisplay *decoDisplay);
void CS_DISPLAY_UPDATE(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty);

void CS_DISPLAY_SPRITE_ADD(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
void CS_DISPLAY_SPRITE_CREATE(Bone *bone, DecorativeDisplay *decoDisplay);
void CS_DISPLAY_SPRITE_UPDATE(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty);

void CS_DISPLAY_ARMATURE_ADD(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
void CS_DISPLAY_ARMATURE_CREATE(Bone *bone, DecorativeDisplay *decoDisplay);
void CS_DISPLAY_ARMATURE_UPDATE(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty);

void CS_DISPLAY_PARTICLE_ADD(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
void CS_DISPLAY_PARTICLE_CREATE(Bone *bone, DecorativeDisplay *decoDisplay);
void CS_DISPLAY_PARTICLE_UPDATE(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty);

void CS_DISPLAY_SHADER_ADD(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData);
void CS_DISPLAY_SHADER_CREATE(Bone *bone, DecorativeDisplay *decoDisplay);
}

#endif
