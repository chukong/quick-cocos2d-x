#include "BytesType.h"

namespace dragonBones
{
    
    bool checkBytesTailisXML(const ByteArray &bytes)
    {
        size_t offset = bytes.size();
        
        size_t count1 = 20;
        while(count1 --)
        {
            if(offset --)
            {
                switch(bytes[offset])
                {
                    case ' ':
                    case '\t':
                    case '\r':
                    case '\n':
                        //
                    break;
                    case '>':
                        size_t count2 = 20;
                        while(count2 --)
                        {
                            if(offset --)
                            {
                                if(bytes[offset] == '<')
                                {
                                    return true;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        return false;
                    break;
                }
            }
        }
        return false;
    }
};
