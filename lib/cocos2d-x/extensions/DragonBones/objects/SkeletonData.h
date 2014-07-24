#ifndef __SKELETON_DATA_H__
#define __SKELETON_DATA_H__
#include "utils/preDB.h"
#include "ArmatureData.h"
namespace dragonBones
{

    class SkeletonData
    {
    public:
        String name;
        
        std::map<std::string , Point> _subTexturePivots;
        
        std::vector<String> getArmatureNames()
        {
            std::vector<String> nameList;
            for(size_t i = 0 ; i < _armatureDataList.size() ; i ++)
            {
                nameList.push_back(_armatureDataList[i]->name);
            }
            return nameList;
        }
        
        std::vector<ArmatureData*> _armatureDataList;
        
        SkeletonData()
        {
        }
        virtual ~SkeletonData()
        {
            dispose();
        }
        
        void dispose()
        {
            for(size_t i = 0 ; i < _armatureDataList.size() ; i ++)
            {
                _armatureDataList[i]->dispose();
                delete _armatureDataList[i];
            }
            _armatureDataList.clear();
            _subTexturePivots.clear();
        }
        
        ArmatureData* getArmatureData(const String &armatureName)
        {
            for(size_t i = 0 ; i < _armatureDataList.size() ; i ++)
            {
                if(_armatureDataList[i]->name == armatureName)
                {
                    return _armatureDataList[i];
                }
            }
            
            return nullptr;
        }
        
        void addArmatureData(ArmatureData *armatureData)
        {
            _armatureDataList.push_back(armatureData);
        }
        
        void removeArmatureData(ArmatureData *armatureData)
        {
            removeArmatureDataByName(armatureData->name);
        }
        
        void removeArmatureDataByName(const String &armatureName)
        {
            for(size_t i = 0 ; i < _armatureDataList.size() ; i ++)
            {
                if(_armatureDataList[i]->name == armatureName)
                {
                    std::vector<ArmatureData*>::iterator iter = _armatureDataList.begin() + i;
                    delete *iter;
                    _armatureDataList.erase(_armatureDataList.begin() + i);
                    return;
                }
            }
        }
        
        Point *getSubTexturePivot(const String &subTextureName)
        {
            std::map<std::string , Point>::iterator i = _subTexturePivots.find(subTextureName);
            if(i != _subTexturePivots.end())
            {
                return &i->second;
            }
            else
            {
                return nullptr;
            }
        }
        
        Point addSubTexturePivot(Number x, Number y, const String &subTextureName)
        {
            std::map<std::string , Point>::iterator i = _subTexturePivots.find(subTextureName);
            if(i != _subTexturePivots.end())
            {
                i->second.x = x;
                i->second.y = y;
                return i->second;
            }
            else
            {
                Point &pt = _subTexturePivots[subTextureName];
                pt.x = x;
                pt.y = y;
                return pt;
            }
        }

        void removeSubTexturePivot(const String &subTextureName)
        {
            std::map<std::string , Point>::iterator i = _subTexturePivots.find(subTextureName);
            if(i != _subTexturePivots.end())
            {
                _subTexturePivots.erase(i);
            }        
        }

        void removeAllSubTexturePivots()
        {
            _subTexturePivots.clear();
        }
    };
};
#endif // __SKELETON_DATA_H__
