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

#ifndef COCOSTUDIO_CSARMATUREDEFINE_H
#define COCOSTUDIO_CSARMATUREDEFINE_H

#ifndef CS_TOOL_PLATFORM
#define CS_TOOL_PLATFORM 0
#endif


#if CS_TOOL_PLATFORM
	#include "CSPlatformDefine.h"
	#include "CSFile.h"

    #include "CSGame.h"
#else
	#define CS_EXTERN 
#endif


#ifndef CS_DEBUG_FOR_EDIT
#define CS_DEBUG_FOR_EDIT 0
#endif


#ifndef ENABLE_PHYSICS_DEBUG
#define ENABLE_PHYSICS_DEBUG 0
#endif 

#ifndef ENABLE_PHYSICS_DETECT
#define ENABLE_PHYSICS_DETECT 0
#endif 


#define MAX_VERTEXZ_VALUE 5000000.0f
#define ARMATURE_MAX_CHILD 50.0f
#define ARMATURE_MAX_ZORDER 100
#define ARMATURE_MAX_COUNT ((MAX_VERTEXZ_VALUE) / (ARMATURE_MAX_CHILD) / ARMATURE_MAX_ZORDER)

#define CS_RETURN_IF(cond) if (cond) return
#define CS_RETURN_NULL_IF(cond) if (cond) return NULL;

#endif
