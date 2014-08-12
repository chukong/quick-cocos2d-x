#ifndef __BYTES_TYPE_H__
#define __BYTES_TYPE_H__
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <float.h>
namespace dragonBones
{
    typedef std::vector<char> ByteArray;
    typedef std::string String;
    typedef unsigned int uint;
    typedef float Number;
    static Number Infinite = FLT_MAX;
    Number round(Number x);

    const unsigned int maxU = ~0;
    const Number NaN =  *((Number*)&maxU);

    bool isNaN(Number num);

    class Object
    {
    public:
        Object(){};
        virtual ~Object(){};
    };

    template<typename T>
    int indexOf(std::vector<T> &vec , const T &value)
    {
        for(size_t i = 0 ; i < vec.size() ; i ++)
        {
            if(vec[i] == value)
            {
                return i;
            }
        }
        return -1;
    }

    /** @private */
    class BytesType
    {
    public:
        static const String BLANK;
        static const String SWF;
        static const String PNG;
        static const String JPG;
        static const String ATF;
        static const String ZIP;
        
        static const String &getType(const ByteArray &bytes)
        {
            uint b1 = bytes[0];
            uint b2 = bytes[1];
            uint b3 = bytes[2];
            uint b4 = bytes[3];
            if ((b1 == 0x46 || b1 == 0x43 || b1 == 0x5A) && b2 == 0x57 && b3 == 0x53)
            {
                //CWS FWS ZWS
                return SWF;
            }
            else if (b1 == 0x89 && b2 == 0x50 && b3 == 0x4E && b4 == 0x47)
            {
                //89 50 4e 47 0d 0a 1a 0a
                return PNG;
            }
            else if (b1 == 0xFF)
            {
                return JPG;
            }
            else if (b1 == 0x41 && b2 == 0x54 && b3 == 0x46)
            {
                return ATF;
            }
            else if (b1 == 0x50 && b2 == 0x4B)
            {
                return ZIP;
            }
            else
            {
                return BLANK;
            }
        }
    };
};
#endif // __BYTES_TYPE_H__
