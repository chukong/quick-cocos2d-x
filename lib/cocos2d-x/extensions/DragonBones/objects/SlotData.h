#ifndef __SLOT_DATA_H__
#define __SLOT_DATA_H__
#include "utils/preDB.h"
#include "DisplayData.h"
namespace dragonBones
{
    /** @private */
    class SlotData
    {
    public:
        String name;
        String parent;
        Number zOrder;
        String blendMode;
        
        std::vector<DisplayData*> displayDataList;
        
        SlotData()
        {
            zOrder = 0;
            blendMode = "normal";
        }
        virtual ~SlotData()
        {
            dispose();
        }
        
        void dispose()
        {
            for(size_t i = 0 ; i < displayDataList.size() ; i ++)
            {
                displayDataList[i]->dispose();
                delete displayDataList[i];
            }
            displayDataList.clear();
        }
        
        void addDisplayData(DisplayData *displayData)
        {
            displayDataList.push_back(displayData);
        }
        
        DisplayData* getDisplayData(const String &displayName)
        {
            for(size_t i = 0 ; i < displayDataList.size() ; i ++)
            {
                if(displayDataList[i]->name == displayName)
                {
                    return displayDataList[i];
                }
            }
            
            return 0;
        }
    };
};
#endif // __SLOT_DATA_H__
