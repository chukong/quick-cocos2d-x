#ifndef __SKIN_DATA_H__
#define __SKIN_DATA_H__
#include "utils/preDB.h"
#include "SlotData.h"
namespace dragonBones
{
    /** @private */
    class SkinData
    {
    public:
        String name;        
        std::vector<SlotData*> slotDataList;

        SkinData()
        {

        }
        virtual ~SkinData()
        {
            dispose();
        }
        
        void dispose()
        {
            for(size_t i = 0 ; i < slotDataList.size() ; i ++)
            {
                slotDataList[i]->dispose();
                delete slotDataList[i];
            }
            slotDataList.clear();
        }
        
        SlotData* getSlotData(const String &slotName)
        {
            for(size_t i = 0 ; i < slotDataList.size() ; i ++)
            {
                if(slotDataList[i]->name == slotName)
                {
                    return slotDataList[i];
                }
            }
            return 0;
        }
        
        void addSlotData(SlotData *slotData)
        {            
            slotDataList.push_back(slotData);
        }
    };
};
#endif // __SKIN_DATA_H__
