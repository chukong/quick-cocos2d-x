/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CC_STD_C_H__
#define __CC_STD_C_H__

#include "platform/CCPlatformMacros.h"
#include <float.h>

#if !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES       // make M_PI can be use
#endif

#ifndef snprintf
#define snprintf  qsnprintf   //_snprintf
#endif

#include <typeinfo>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Qt
#include <QPainter>
#include <QFontDatabase>
#include <QtCore/QDateTime>
#include <QtCore/qnumeric.h>

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#if ! defined(isnan)
    #define isnan   qIsNaN
#endif

#ifdef Q_OS_WIN
#include <Winsock2.h>
#include <WinSock.h>    // for struct timeval
//#include "compat/stdint.h"
//#include <QtGlobal>
#include <stdint.h>

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

#endif

#ifdef _WIN32
//struct timeval {
//    long    tv_sec;         /* seconds */
//    long    tv_usec;        /* and microseconds */
//};
#endif

//size_t CC_DLL hash_code( const std::type_info& info );
int CC_DLL gettimeofday(struct timeval *, struct timezone *);

//#define HASH_CODE( x ) hash_code(x)
//#define HASH_CODE( x ) x.hash_code()

#endif  // __CC_STD_C_H__

