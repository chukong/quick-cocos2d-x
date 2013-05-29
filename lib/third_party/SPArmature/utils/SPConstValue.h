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

#pragma once



static const char *SKELETON = "skeleton";
static const char *ARMATURES = "armatures";
static const char *ARMATURE = "armature";
static const char *BONE = "b";
static const char *DISPLAY = "d";
static const char *ANIMATIONS = "animations";
static const char *ANIMATION = "animation";
static const char *MOVEMENT = "mov";
static const char *EVENT = "event";
static const char *FRAME = "f";
static const char *TEXTURE_ATLAS = "TextureAtlas";
static const char *SUB_TEXTURE = "SubTexture";
static const char *AT = "@";
static const char *A_BONE_TYPE = "bT";
static const char *A_NAME = "name";
static const char *A_DURATION = "dr";
static const char *A_DURATION_TO = "to";
static const char *A_DURATION_TWEEN = "drTW";
static const char *A_LOOP = "lp";
static const char *A_MOVEMENT_SCALE = "sc";
static const char *A_MOVEMENT_DELAY = "dl";
static const char *A_DISPLAY_INDEX = "dI";
static const char *A_VERT = "vert";
static const char *A_FRAG = "frag";
static const char *A_PLIST = "plist";
static const char *A_PARENT = "parent";
static const char *A_SKEW_X = "kX";
static const char *A_SKEW_Y = "kY";
static const char *A_SCALE_X = "cX";
static const char *A_SCALE_Y = "cY";
static const char *A_Z = "z";
static const char *A_HIDE = "hide";
static const char *A_IMAGE = "img";
static const char *A_EVENT = "evt";
static const char *A_SOUND = "sd";
static const char *A_SOUND_EFFECT = "sdE";
static const char *A_TWEEN_EASING ="twE";
static const char *A_TWEEN_ROTATE ="twR";
static const char *A_IS_ARMATURE = "isArmature";
static const char *A_DISPLAY_TYPE = "displayType";
static const char *A_MOVEMENT = "mov";
static const char *A_X = "x";
static const char *A_Y = "y";
static const char *A_WIDTH = "width";
static const char *A_HEIGHT = "height";
static const char *A_PIVOT_X = "pX";
static const char *A_PIVOT_Y = "pY";
static const char *A_ALPHA = "alpha";
static const char *A_RED = "red";
static const char *A_GREEN = "green";
static const char *A_BLUE = "blue";
static const char *A_ROTATION = "rotation";
static const char *A_BONE_IMAGE = "bi";
static const char *V_SOUND_LEFT = "l";
static const char *V_SOUND_RIGHT = "r";
static const char *V_SOUND_LEFT_TO_RIGHT = "lr";
static const char *V_SOUND_RIGHT_TO_LEFT = "rl";
static const char *V_SOUND_FADE_IN = "in";
static const char *V_SOUND_FADE_OUT = "out";
static const char *CONTOUR = "con";
static const char *CONTOUR_VERTEX = "con_vt";
static const char *START = "start";
static const char *COMPLETE = "complete";
static const char *LOOP_COMPLETE = "loopComplete";
static const char *IN_FRAME = "inFrame";
static const char *MOVEMENT_EVENT_FRAME = "movementEventFrame";
static const char *SOUND_FRAME = "soundFrame";
static const char *FL_NAN = "NaN";
static const char *DATA_TYPE = "data_type";
static const char *FRAME_DATA = "frame_data";
static const char *MOVEMENT_BONE_DATA = "mov_bone_data";
static const char *MOVEMENT_FRAME_DATA = "mov_frame_data";
static const char *MOVEMENT_DATA = "mov_data";
static const char *ANIMATION_DATA = "animation_data";
static const char *DISPLAY_DATA = "display_data";
static const char *BONE_DATA = "bone_data";
static const char *ARMATURE_DATA = "armature_data";
static const char *CONTOUR_DATA = "contour_data";
static const char *TEXTURE_DATA = "texture_data";
static const char *VERTEX_POINT = "vertex";

#pragma unused (SKELETON)
#pragma unused (ARMATURES)
#pragma unused (ARMATURE)
#pragma unused (BONE)
#pragma unused (DISPLAY)
#pragma unused (ANIMATIONS)
#pragma unused (ANIMATION)
#pragma unused (MOVEMENT)
#pragma unused (EVENT)
#pragma unused (FRAME)
#pragma unused (TEXTURE_ATLAS)
#pragma unused (SUB_TEXTURE)
#pragma unused (AT)
#pragma unused (A_BONE_TYPE)
#pragma unused (A_NAME)
#pragma unused (A_DURATION)
#pragma unused (A_DURATION_TO)
#pragma unused (A_DURATION_TWEEN)
#pragma unused (A_LOOP)
#pragma unused (A_MOVEMENT_SCALE)
#pragma unused (A_MOVEMENT_DELAY)
#pragma unused (A_DISPLAY_INDEX)
#pragma unused (A_VERT)
#pragma unused (A_FRAG)
#pragma unused (A_PLIST)
#pragma unused (A_PARENT)
#pragma unused (A_SKEW_X)
#pragma unused (A_SKEW_Y)
#pragma unused (A_SCALE_X)
#pragma unused (A_SCALE_Y)
#pragma unused (A_Z)
#pragma unused (A_HIDE)
#pragma unused (A_IMAGE)
#pragma unused (A_EVENT)
#pragma unused (A_SOUND)
#pragma unused (A_SOUND_EFFECT)
#pragma unused (A_TWEEN_EASING)
#pragma unused (A_TWEEN_ROTATE)
#pragma unused (A_IS_ARMATURE)
#pragma unused (A_DISPLAY_TYPE)
#pragma unused (A_MOVEMENT)
#pragma unused (A_X)
#pragma unused (A_Y)
#pragma unused (A_WIDTH)
#pragma unused (A_HEIGHT)
#pragma unused (A_PIVOT_X)
#pragma unused (A_PIVOT_Y)
#pragma unused (A_ALPHA)
#pragma unused (A_RED)
#pragma unused (A_GREEN)
#pragma unused (A_BLUE)
#pragma unused (A_ROTATION)
#pragma unused (A_BONE_IMAGE)
#pragma unused (V_SOUND_LEFT)
#pragma unused (V_SOUND_RIGHT)
#pragma unused (V_SOUND_LEFT_TO_RIGHT)
#pragma unused (V_SOUND_RIGHT_TO_LEFT)
#pragma unused (V_SOUND_FADE_IN)
#pragma unused (V_SOUND_FADE_OUT)
#pragma unused (CONTOUR)
#pragma unused (CONTOUR_VERTEX)
#pragma unused (START)
#pragma unused (COMPLETE)
#pragma unused (LOOP_COMPLETE)
#pragma unused (IN_FRAME)
#pragma unused (MOVEMENT_EVENT_FRAME)
#pragma unused (SOUND_FRAME)
#pragma unused (FL_NAN)
#pragma unused (DATA_TYPE)
#pragma unused (FRAME_DATA)
#pragma unused (MOVEMENT_BONE_DATA)
#pragma unused (MOVEMENT_FRAME_DATA)
#pragma unused (MOVEMENT_DATA)
#pragma unused (ANIMATION_DATA)
#pragma unused (DISPLAY_DATA)
#pragma unused (BONE_DATA)
#pragma unused (ARMATURE_DATA)
#pragma unused (CONTOUR_DATA)
#pragma unused (TEXTURE_DATA)
#pragma unused (VERTEX_POINT)
