#ifndef __CCPLATFORMDEFINE_H__
#define __CCPLATFORMDEFINE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_QT)
    #include <QtCore/qglobal.h>
    #undef CC_DLL
    #if defined(_USRDLL)
//#ifdef Q_OS_WIN
////        #define CC_DLL     __declspec(dllexport)
//        #define CC_DLL
//#else
        #define CC_DLL     Q_DECL_EXPORT
//#endif
    #else 		/* use a DLL library */
//#ifdef Q_OS_WIN
//        #define CC_DLL     __declspec(dllimport)
//#else
        #define CC_DLL     Q_DECL_IMPORT
//#endif
    #endif
#else
    #if defined(_USRDLL)
        #define CC_DLL     __declspec(dllexport)
    #else         /* use a DLL library */
        #define CC_DLL     __declspec(dllimport)
    #endif
#endif

#include <assert.h>

#if CC_DISABLE_ASSERT > 0
#define CC_ASSERT(cond)
#else
#define CC_ASSERT(cond)    assert(cond)
#endif
#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif



#endif /* __CCPLATFORMDEFINE_H__*/
