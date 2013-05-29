/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.sweetpome.com
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

#include "SPArmature.h"
#include "SPArmatureDataManager.h"
#include "SPDisplayData.h"
#include "SPBatchNodeManager.h"
#include "SPArmatureDefine.h"
#include "SPDataReaderHelper.h"
#include "SPSpriteDisplayData.h"
#include "SPContourSprite.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#endif

namespace sp{

    
std::map<int, Armature*> Armature::m_sArmatureIndexDic;
CCDictionary *Armature::m_sArmatureMap = new CCDictionary();
    
int Armature::m_siMaxArmatureZorder = 0;

    
Armature *Armature::create()
{
    Armature *_armature = new Armature();
    if (_armature && _armature->init())
    {
        _armature->autorelease();
        return _armature;
    }
    CC_SAFE_DELETE(_armature);
    return NULL;
}

    
Armature *Armature::create(const char* _name)
{
    Armature *_armature = new Armature();
    if (_armature && _armature->init(_name))
    {
        _armature->autorelease();
        return _armature;
    }
    CC_SAFE_DELETE(_armature);
    return NULL;
}
    
Armature::Armature()
    :m_pAnimation(NULL)
    ,m_pBoneDic(NULL)
    ,m_pBoneList(NULL)
	,m_fZOrder(0)
	,m_fInternalZOrder(0)
	,m_fActualZOrder(0)
    ,m_bBonesIndexChanged(false)
	,m_pRootBone(NULL)
	,m_pArmature(NULL)
{
}


Armature::~Armature(void)
{
    // remove this Armature's m_fInternalZOrder from m_sArmatureMap, so other Armature can use this internal zorder
    m_sArmatureMap->removeObjectForKey(m_fInternalZOrder);

    if(NULL != m_pBoneDic)
    {
        m_pBoneDic->removeAllObjects();
        CC_SAFE_DELETE(m_pBoneDic);
    }
    if(NULL != m_pBoneList)
    {
        m_pBoneList->removeAllObjects();
        CC_SAFE_DELETE(m_pBoneList);
    }
    
    CC_SAFE_DELETE(m_pAnimation);

	CC_SAFE_DELETE(m_pRootBone);
}

    
bool Armature::init()
{
    return init(NULL);
}


bool Armature::init(const char *_name)
{
    bool bRet = false;
    do
    {
        cocos2d::CCLog("Armature (%s)  create.", _name);

		CC_SAFE_DELETE(m_pAnimation);
        m_pAnimation = Animation::create(this);
        CCAssert(m_pAnimation, "create Armature::m_pAnimation fail!");
        m_pAnimation->retain();

		CC_SAFE_DELETE(m_pBoneDic);
        m_pBoneDic	= CCDictionary::create();
        CCAssert(m_pBoneDic, "create Armature::m_pBoneDic fail!");
        m_pBoneDic->retain();
        
		CC_SAFE_DELETE(m_pBoneList);
        m_pBoneList = CCArray::createWithCapacity(4);
        CCAssert(m_pBoneList, "create Armature::m_pBoneList fail!");
        m_pBoneList->retain();

        
        if(_name == NULL)
        {
           m_strName = ""; 
        }
        else
        {
            m_strName = _name;
        }

		initRootBone();

        ArmatureDataManager *_armatureDataManager = ArmatureDataManager::sharedArmatureDataManager();
        
        if(m_strName.compare("") != 0)
        {
            m_strName = _name;
            
            AnimationData* _animationData = _armatureDataManager->getAnimationData(_name);
            CCAssert(_animationData, "AnimationData not exist! ");
            
            m_pAnimation->setAnimationData(_animationData);
            
            
            ArmatureData *_armatureData = _armatureDataManager->getArmatureData(_name);
            CCAssert(_armatureData, "");
            
            m_pArmatureData = _armatureData;
            
            
            CCDictElement *_element = NULL;
            CCDictionary *_boneDataDic = _armatureData->getBoneDic();
            CCDICT_FOREACH(_boneDataDic, _element)
            {
                Bone *_bone = createBone(_element->getStrKey());
                
                //! init bone's  Tween to 1st movement's 1st frame
                do {
                    
                    MovementData *_movData = _animationData->getMovement(_animationData->getMovNames().at(0).c_str());
                    CC_BREAK_IF(!_movData);
                    
                    MovementBoneData *_movBoneData = _movData->getMovementBoneData(_bone->getName().c_str());
                    CC_BREAK_IF(!_movBoneData);
                    
                    FrameData *_frameData = _movBoneData->getFrameData(0);
                    CC_BREAK_IF(!_frameData);
                    
                    _bone->getTween()->getTweenNode()->copy(_frameData);
                } while (0);
            }
            
        }
        else
        {
            m_strName = "new_armature";
            m_pArmatureData = ArmatureData::create();
            m_pArmatureData->setName(m_strName);
            
            AnimationData *_animationData = AnimationData::create();
            _animationData->setName(m_strName);
            
            
            _armatureDataManager->addArmatureData(m_strName.c_str(), m_pArmatureData);
            _armatureDataManager->addAnimationData(m_strName.c_str(), _animationData);
            
            m_pAnimation->setAnimationData(_animationData);
            

        }

		internalSort();

		setZOrder(0);
        
        bRet = true;
    }
    while (0);

    return bRet;
}
 

void Armature::setVisible(bool _visible)
{
	m_bVisible = _visible;

	CCObject *_object = NULL;
	CCARRAY_FOREACH(m_pBoneList, _object)
	{
		Bone *_bone = (Bone*)_object;
		_bone->getDisplayManager()->setVisible(_visible);
	}
}

bool Armature::getVisible()
{
	return m_bVisible;
}

Bone *Armature::createBone(const char *_boneName)
{
    
	if(getBone(_boneName) != NULL)
	{
		return getBone(_boneName);
	}
    
    BoneData *_boneData = (BoneData*)m_pArmatureData->getBoneData(_boneName);
    std::string _parentName = _boneData->m_strParent;

    Bone *_bone = NULL;
    
    if( _parentName.compare("") !=0 )
    {
        createBone(_parentName.c_str());
        _bone = Bone::create(_boneName);
        addBone(_bone, _parentName.c_str());
    }else{
        _bone = Bone::create(_boneName);
        addBone(_bone, "");
    }
    
    _bone->setBoneData(_boneData);
	_bone->getDisplayManager()->changeDisplayByIndex(-1, false);
    
    return _bone;
}


void Armature::addBone(Bone *_bone, const char *_parentName)
{
    CCAssert( _bone != NULL, "Argument must be non-nil");
    CCAssert(m_pBoneDic->objectForKey(_bone->getName()) == NULL, "_bone already added. It can't be added again");

    if (NULL == _parentName)
    {
        m_pRootBone->addChildBone(_bone);
    }
    else
    {
        Bone *_boneParent = (Bone*)m_pBoneDic->objectForKey(_parentName);
        
        if (_boneParent)
        {
            _boneParent->addChildBone(_bone);
        }
        else
        {
            m_pRootBone->addChildBone(_bone);
        }
    }
    
    
    _bone->setArmature(this);
    
    connectBoneSignal(_bone);
    
    m_pBoneDic->setObject(_bone, _bone->getName());
    m_pBoneList->addObject(_bone);
}


void Armature::removeBone(Bone *_bone, bool _cleanup)
{
    CCAssert(_bone != NULL, "_bone must be added to the bone dictionary!");
    
    _bone->setArmature(NULL);
    _bone->removeFromParent(_cleanup);
    
    m_pBoneDic->removeObjectForKey(_bone->getName());
    m_pBoneList->removeObject(_bone);
    
    
}


Bone *Armature::getBone(const char* _name)
{
    return (Bone*)m_pBoneDic->objectForKey(_name);
}


void Armature::changeBoneParent(Bone *_bone, const char *_parentName)
{
    CCAssert(_bone != NULL, "_bone must be added to the bone dictionary!");
    
    _bone->removeFromParent(false);
    
    if (_parentName != NULL)
    {
        Bone *_boneParent = (Bone*)m_pBoneDic->objectForKey(_parentName);
        CCAssert(_boneParent, "_boneParent must be added to the bone dictionary!");
        
        _boneParent->addChildBone(_bone);
    }
    else
    {
        m_pRootBone->addChildBone(_bone);
    }
}

void Armature::editName(const char *_name)
{
    setName(_name);
    
    m_pArmatureData->setName(_name);
    m_pAnimation->getAnimationData()->setName(_name);
}

CCNode *Armature::getDisplayRenderNode()
{
    return m_pRootBone->getDisplayManager()->getDisplayRenderNode();
}

void Armature::addEditBone(Bone *_bone, const char *_parentName)
{
    m_pArmatureData->addBoneData(_bone->getBoneData());
    _bone->getBoneData()->m_strParent = _parentName;
    
    addBone(_bone, _parentName);
}

void Armature::removeEditBone(Bone *_bone, bool _cleanUp)
{
    removeBone(_bone, _cleanUp);
    
    m_pArmatureData->removeBoneData(_bone->getName().c_str());
    

    CCDictionary *_movmentDataDic = m_pAnimation->getAnimationData()->getMovementDic();
    CCDictElement *_element = NULL;
    CCDICT_FOREACH(_movmentDataDic, _element)
    {
        MovementData *_movmentData = (MovementData*)_element->getObject();
        if(_movmentData)
        {
            _movmentData->removeMovementBoneData(_bone->getName().c_str());
        }
    }
    
    
    _bone->getBoneData()->m_strParent = "";
}

void Armature::changeEditBoneParent(Bone *_bone, const char *_parentName)
{
    changeBoneParent(_bone, _parentName);
    
    _bone->getBoneData()->m_strName = _bone->getName();
    _bone->getBoneData()->m_strParent = _bone->getParentBone()->getBoneData()->m_strName;
}

    
void Armature::onMovementEvent(const char *_eventType, const char *_movementID)
{
//     if(NULL != m_pComArmature)
//     {
//         m_pComArmature->onMovementEvent(_eventType, _movementID);
//     }
}

    
void Armature::setZOrder(int _zOrder)
{

	m_fZOrder = _zOrder;

	/*
	 *	Calculate the actial zorder of this armature every time the m_iZOrder be set.
     *  Every m_fZOrder have at most ARMATURE_MAX_COUNT Armatures
     *  It's like a two dimensional table, m_fInternalZOrder is column number, and m_fZOrder is row number. Then m_fActualZOrder is the actual index.
     *  It can ensure every Armature have different vertexZ
	 */
	if(m_fZOrder >= 0)
	{
		m_fActualZOrder = m_fZOrder * ARMATURE_MAX_COUNT;
		m_fActualZOrder += m_fInternalZOrder;
	}else{
		m_fActualZOrder = m_fZOrder * ARMATURE_MAX_COUNT;
		m_fActualZOrder -= m_fInternalZOrder;
	}
	
    if(m_eRenderType == BATCHNODE_VERTEXZ)
    {
        /*
         *  also every Armature have max child count, we allocate ARMATURE_MAX_CHILD vertexz number for each Armature
         */
        m_pRootBone->getDisplayManager()->getDisplayRenderNode()->setVertexZ(m_fActualZOrder * ARMATURE_MAX_CHILD);
        
        int _i = 0;
        sortBoneHelper(m_pRootBone->getDisplayManager()->getDisplayRenderNode()->getVertexZ(), _i);
    }
    else
    {
        /*
         *  also every Armature have max child count, we allocate ARMATURE_MAX_CHILD vertexz number for each Armature
         */
        m_pRootBone->getDisplayManager()->getDisplayRenderNode()->_setZOrder(m_fActualZOrder * ARMATURE_MAX_CHILD);
        
        int _i = 0;
        sortBoneHelper(m_pRootBone->getDisplayManager()->getDisplayRenderNode()->getZOrder(), _i);
    }
    
    return;
}
    
int Armature::getZOrder()
{
    return m_fZOrder;
}

    
CCDictionary *Armature::getBoneDic()
{
    return m_pBoneDic;
}

    
void Armature::update(float dt)
{
    m_pAnimation->update(dt);

    m_pRootBone->update(dt);

    
    if (m_bBonesIndexChanged)
    {
		if(m_pArmature)
		{
			m_pArmature->setBonesIndexChanged(true);
			m_bBonesIndexChanged = false;
		}
		else
		{
			int i = 0;

			if(m_eRenderType == BATCHNODE_VERTEXZ)
			{
				sortBoneHelper(m_pRootBone->getDisplayManager()->getDisplayRenderNode()->getVertexZ(), i);
			}
			else
			{
				sortBoneHelper(m_pRootBone->getDisplayManager()->getDisplayRenderNode()->getZOrder(), i);
			}

			m_bBonesIndexChanged = false;
		}
    }
    
}


void Armature::initRootBone()
{
	CC_SAFE_DELETE(m_pRootBone);
	m_pRootBone = Bone::create((m_strName + "_root_bone").c_str());
	CCAssert(m_pRootBone, "create Armature::m_pRootBone fail!");
	m_pRootBone->retain();

	SpriteDisplayData *param = SpriteDisplayData::create();
	param->setParam("");

	m_pRootBone->getDisplayManager()->addDisplay(param, 0);
	m_pRootBone->getDisplayManager()->changeDisplayByIndex(0, true);
	m_pRootBone->setIgnoreMovementBoneData(true);
    m_pRootBone->getDisplayManager()->setVisible(false);
	m_pRootBone->setArmature(this);
	m_pRootBone->setRootBone(true);
}

void Armature::internalSort()
{
    if (m_sArmatureMap->count() >= ARMATURE_MAX_COUNT)
    {
        cocos2d::CCLog("warnning : current Armature count is more than ARMATURE_MAX_COUNT(%i), we will do not sort this Armature!!! ", ARMATURE_MAX_COUNT);
        m_fInternalZOrder = 0;
        return;
    }
    
    /*
     *  if m_siMaxArmatureZorder is more than ARMATURE_MAX_COUNT, we will find from 0
     */
    if(m_siMaxArmatureZorder >= ARMATURE_MAX_COUNT)
    {
        m_siMaxArmatureZorder = 0;
    }
    
    /*
     *  Stop until find out a index is not used. 
     */
    while (m_sArmatureMap->objectForKey(m_siMaxArmatureZorder) != NULL) {
        m_siMaxArmatureZorder ++;
    }
    
	m_fInternalZOrder = m_siMaxArmatureZorder;
    
    cocos2d::CCLog("Armature internal zorder : %f", m_fInternalZOrder);
    
    m_sArmatureMap->setObject(this, m_fInternalZOrder);
}

    
void Armature::sortBoneHelper(int _baseVertexz, int &_index)
{
    int i,j,length = m_pBoneList->data->num;
    Bone **x = (Bone**)m_pBoneList->data->arr;
    Bone *tempItem;
    
    // insertion sort
    for(i=1; i<length; i++)
    {
        tempItem = x[i];
        j = i-1;
        
        // if display of x[i] or x[j] is null, then continue.
        if(x[j]->getDisplayManager()->getDisplayRenderNode() == NULL || x[i]->getDisplayManager()->getDisplayRenderNode() == NULL)
        {
            continue;
        }
        
        
        int tempItemZ = tempItem->getZOrder();
        int jZ = x[j]->getZOrder();

        
        int tempOrderArrival = tempItem->getDisplayManager()->getDisplayRenderNode()->getOrderOfArrival();
        int jOrderArrival = x[j]->getDisplayManager()->getDisplayRenderNode()->getOrderOfArrival();
        
        //continue moving element downwards while zOrder is smaller or when zOrder is the same but mutatedIndex is smaller
        while(j>=0 && ( tempItemZ < jZ || ( tempItemZ== jZ &&  tempOrderArrival < jOrderArrival ) ) )
        {
            x[j+1] = x[j];
            j = j-1;
            
            
            if (j >= 0) {
                
                jZ = x[j]->getZOrder();
                
                // if display of x[j] is null, then continue.
                if(x[j]->getDisplayManager()->getDisplayRenderNode() == NULL)
                {
                    continue;
                }
                
                jOrderArrival = x[j]->getDisplayManager()->getDisplayRenderNode()->getOrderOfArrival();
            }
        }
        x[j+1] = tempItem;
    }
    
    // sort children children recursively
    for (i=0; i<length; i++)
    {
        if(x[i]->getChildArmature() != NULL)
        {
            x[i]->getChildArmature()->sortBoneHelper(_baseVertexz, _index);
            continue;
        }
        
        if(x[i]->getDisplayManager()->getDisplayRenderNode() != NULL)
        {
            if(m_eRenderType == BATCHNODE_VERTEXZ)
            {
                x[i]->getDisplayManager()->getDisplayRenderNode()->setVertexZ((float)(_baseVertexz + _index++) / 10000);
            }
            else
            {
                x[i]->getDisplayManager()->getDisplayRenderNode()->_setZOrder(_baseVertexz + _index++);
            }
            
            cocos2d::CCLog("%s : vertexz - %f,  zorder - %i", x[i]->getName().c_str(), x[i]->getDisplayManager()->getDisplayRenderNode()->getVertexZ(), x[i]->getDisplayManager()->getDisplayRenderNode()->getZOrder());
        }
                
    }
    
}
    
void boneNameChanged(Bone *bone, const char *_newName)
{
    
}
    
void Armature::setPosition(float _x, float _y)
{
    m_pRootBone->setPosition(_x, _y);
    m_pRootBone->updateTransform();
}

void Armature::setPositionX(float _x)
{
    m_pRootBone->setPositionX(_x);
    m_pRootBone->updateTransform();
}

void Armature::setPositionY(float _y)
{
    m_pRootBone->setPositionY(_y);
    m_pRootBone->updateTransform();
}

void Armature::setRotation(float _r)
{
    m_pRootBone->setRotation(_r);
    m_pRootBone->updateTransform();
}


void Armature::setScale(float _scale)
{
    m_pRootBone->setScale(_scale);
    m_pRootBone->updateTransform();
}

void Armature::setScaleX(float _scaleX)
{
    m_pRootBone->setScaleX(_scaleX);
    m_pRootBone->updateTransform();
}

void Armature::setScaleY(float _scaleY)
{
    m_pRootBone->setScaleY(_scaleY);
    m_pRootBone->updateTransform();
}

CCRect Armature::getBoundingBox()
{
	float minx, miny, maxx, maxy = 0;

	bool first = true;

	CCRect boundingBox = CCRectMake(0, 0, 0, 0);

	CCObject *_object = NULL;
	CCARRAY_FOREACH(m_pBoneList, _object)
	{
		Bone *_bone = (Bone*)_object;
		CCRect r = _bone->getDisplayManager()->getBoundingBox();
		

		if(first)
		{
			minx = r.getMinX();
			miny = r.getMinY();
			maxx = r.getMaxX();
			maxy = r.getMaxY();

			first = false;
		}
		else
		{
			minx = r.getMinX() < boundingBox.getMinX() ? r.getMinX() : boundingBox.getMinX();
			miny = r.getMinY() < boundingBox.getMinY() ? r.getMinY() : boundingBox.getMinY();
			maxx = r.getMaxX() > boundingBox.getMaxX() ? r.getMaxX() : boundingBox.getMaxX();
			maxy = r.getMaxY() > boundingBox.getMaxY() ? r.getMaxY() : boundingBox.getMaxY();
		}
		

		boundingBox.setRect(minx, miny, maxx - minx, maxy - miny);
	}

	return boundingBox;
}

Bone *Armature::getBoneAtPoint(float _x, float _y)
{
    int _length = m_pBoneList->data->num;
    Bone **_bs = (Bone**)m_pBoneList->data->arr;
    
    for(int i = _length-1; i>=0; i--)
    {
        if(_bs[i]->getDisplayManager()->containPoint(_x, _y))
        {
            return _bs[i];
        }
    }    
    return NULL;
}
    
void Armature::saveJsonToFile(const char *_fileName)
{
    DataReaderHelper::saveArmatureDataToJson(_fileName, m_pArmatureData);
    DataReaderHelper::saveAnimationDataToJson(_fileName, m_pAnimation->getAnimationData());
}
    
void Armature::setRenderType(RENDER_TYPE _renderType)
{
    m_eRenderType = _renderType;
    
    ArmatureFileInfo *fileInfo = ArmatureDataManager::sharedArmatureDataManager()->getArmatureFileInfo(m_strName.c_str());
    CCLOG("%i", fileInfo->imageInfoVector.size());
    for (std::vector<ImageInfo>::iterator it = fileInfo->imageInfoVector.begin(); it != fileInfo->imageInfoVector.end(); it++)
    {
        CCLOG(it->imagePath.c_str());
        BatchNode  *batchNode = BatchNodeManager::sharedBatchNodeManager()->getBatchNode(it->imagePath.c_str());
        batchNode->setRenderType((RENDER_TYPE)m_eRenderType);
    }
    
    cocos2d::CCLog("%s  change rendertype to %i", m_strName.c_str(), (int)m_eRenderType);
}
    
RENDER_TYPE Armature::getRenderType()
{
    return m_eRenderType;
}
    

void Armature::connectBoneSignal(Bone *_bone)
{
    _bone->NameChanedSignal.connect(this, &Armature::boneNameChangedSlot);
}

void Armature::disconnectBoneSignal(Bone *_bone)
{
    _bone->NameChanedSignal.disconnect(this);
}

    
void Armature::boneNameChangedSlot(Bone *_bone, const char *_newName)
{
    m_pBoneDic->removeObjectForKey(_bone->getName());
    m_pBoneDic->setObject(_bone, _newName);
    
    m_pArmatureData->addBoneData(_bone->getBoneData());
}

}