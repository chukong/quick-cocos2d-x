#ifndef __ARMATURE_DATA_H__
#define __ARMATURE_DATA_H__
#include "utils/preDB.h"
#include "BoneData.h"
#include "SkinData.h"
#include "AnimationData.h"
namespace dragonBones
{
    class ArmatureData
    {
    public:
        String name;
        
        std::vector<BoneData*> boneDataList;
        std::vector<SkinData*> skinDataList;
        std::vector<AnimationData*> animationDataList;
        
        ArmatureData()
        {
        }
        virtual ~ArmatureData()
        {
            dispose();
        }
        
        void dispose()
        {
            for(size_t i = 0 ; i < boneDataList.size() ; i ++)
            {
                boneDataList[i]->dispose();
                delete boneDataList[i];
            }
            for(size_t i = 0 ; i < skinDataList.size() ; i ++)
            {
                skinDataList[i]->dispose();
                delete skinDataList[i];
            }
            for(size_t i = 0 ; i < animationDataList.size() ; i ++)
            {
                animationDataList[i]->dispose();
                delete animationDataList[i];
            }
            boneDataList.clear();
            skinDataList.clear();
            animationDataList.clear();
        }
        
        BoneData *getBoneData(const String &boneName)
        {
            for(size_t i = 0 ; i < boneDataList.size() ; i ++)
            {
                if(boneDataList[i]->name == boneName)
                {
                    return boneDataList[i];
                }
            }
            return nullptr;
        }
        
        SkinData* getSkinData(const String &skinName)
        {
            if(skinName.empty())
            {
                return skinDataList[0];
            }
            for(size_t i = 0 ; i < skinDataList.size() ; i ++)
            {
                if(skinDataList[i]->name == skinName)
                {
                    return skinDataList[i];
                }
            }
            
            return nullptr;
        }
        
        AnimationData* getAnimationData(const String &animationName)
        {
            for(size_t i = 0 ; i < animationDataList.size() ; i ++)
            {
                if(animationDataList[i]->name == animationName)
                {
                    return animationDataList[i];
                }
            }
            return nullptr;
        }
        
        void addBoneData(BoneData *boneData)
        {
            boneDataList.push_back(boneData);
        }
        
        void addSkinData(SkinData *skinData)
        {
            skinDataList.push_back(skinData);
        }
        
        void addAnimationData(AnimationData *animationData)
        {
            animationDataList.push_back(animationData);
        }
        
        static bool sortBone(const std::pair<int , BoneData*>& a , const std::pair<int , BoneData*>& b)
        {
            return a.first < b.first;
        }
        void sortBoneDataList()
        {
            if(boneDataList.empty())
            {
                return;
            }
            
            std::vector<std::pair<int , BoneData*> > helpArray;
            for(size_t i = 0 ; i < boneDataList.size() ; i ++)
            {
                BoneData* boneData = boneDataList[i];
                int level = 0;
                BoneData *parentData = boneData;
                while(parentData && !parentData->parent.empty())
                {
                    level ++;
                    parentData = getBoneData(parentData->parent);
                }
                helpArray.push_back(std::make_pair(level , boneData));
            }
            
            std::sort(helpArray.begin() , helpArray.end() , sortBone);
            
            size_t i = helpArray.size();
            while(i --)
            {
                boneDataList[i] = helpArray[i].second;
            }
        }
    };
};
#endif // __ARMATURE_DATA_H__
