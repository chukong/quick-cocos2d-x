#ifndef __PRE_DB_H__
#define __PRE_DB_H__

#include "BytesType.h"
#include "DBGeometry.h"

#define DB_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)

#define CCNodeRGBA CCNode
#define _displayedColor m_displayedColor
#define _displayedOpacity m_displayedOpacity

#endif // __PRE_DB_H__
