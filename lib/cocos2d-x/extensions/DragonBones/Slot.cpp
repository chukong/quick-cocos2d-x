#include "Slot.h"
#include "Armature.h"
#include "display/IDisplayBridge.h"
#include "objects/DisplayData.h"
#include "animation/Animation.h"
#include "animation/AnimationState.h"
namespace dragonBones
{    
        Number Slot::getZOrder()
        {
            return _originZOrder + _tweenZorder + _offsetZOrder;
        }
        
        void Slot::setZOrder(Number value)
        {
            if(getZOrder() != value)
            {
                _offsetZOrder = value - _originZOrder - _tweenZorder;
                if(_armature)
                {
                    _armature->_slotsZOrderChanged = true;
                }
            }
        }
        
        String Slot::getBlendMode()
        {
            return _blendMode;
        }
        
        void Slot::setBlendMode(const String &value)
        {
            if(_blendMode != value)
            {
                _blendMode = value;
                if (_displayBridge->getDisplay())
                {
                    _displayBridge->updateBlendMode(_blendMode);
                }
            }
        }
        
        /**
         * The DisplayObject belonging to this Bone instance. Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
         */
        Object *Slot::getDisplay()
        {
            Object *display = _displayList[_displayIndex];
            if(dynamic_cast<Armature*>(display))
            {
                return static_cast<Armature*>(display)->getDisplay();
            }
            return display;
        }
        void Slot::setDisplayValue(Object *value)
        {
            _displayList[_displayIndex] = value;
            setDisplay(value);
        }
        
        /**
         * The sub-armature of this Slot instance.
         */
        Armature *Slot::getChildArmature()
        {
            if(dynamic_cast<Armature*>(_displayList[_displayIndex]))
            {
                return static_cast<Armature*>(_displayList[_displayIndex]);
            }
            return 0;
        }
        void Slot::setChildArmature(Armature *value)
        {
            _displayList[_displayIndex] = value;
            if(value)
            {
                setDisplay(value->getDisplay());
            }
        }
        
        /**
         * The DisplayObject list belonging to this Slot instance.
         */
        const std::vector<Object*> &Slot::getDisplayList()
        {
            return _displayList;
        }
        void Slot::setDisplayList(const std::vector<Object*> &value)
        {
            int i = value.size();
            _displayList.resize(i);
            while(i --)
            {
                _displayList[i] = value[i];
            }
            
            if(_displayIndex >= 0)
            {
                int displayIndexBackup = _displayIndex;
                _displayIndex = -1;
                changeDisplay(displayIndexBackup);
            }
        }
        
        void Slot::setDisplay(Object *display)
        {
            if(_displayBridge->getDisplay())
            {
                _displayBridge->setDisplay(display);
            }
            else
            {
                _displayBridge->setDisplay(display);
                if(_armature)
                {
                    _displayBridge->addDisplay(_armature->getDisplay());
                    _armature->_slotsZOrderChanged = true;
                }
            }
            
            updateChildArmatureAnimation();
            
            if(!_isHideDisplay && _displayBridge->getDisplay())
            {
                _isDisplayOnStage = true;
                _displayBridge->updateBlendMode(_blendMode);
            }
            else
            {
                _isDisplayOnStage = false;
            }
        }
        
        /** @private */
        void Slot::changeDisplay(int displayIndex)
        {
            if(displayIndex < 0)
            {
                if(!_isHideDisplay)
                {
                    _isHideDisplay = true;
                    _displayBridge->removeDisplay();
                    updateChildArmatureAnimation();
                }
            }
            else
            {
                bool changeShowState = false;
                if(_isHideDisplay)
                {
                    _isHideDisplay = false;
                    changeShowState = true;
                    if(_armature)
                    {
                        _displayBridge->addDisplay(_armature->getDisplay());
                        _armature->_slotsZOrderChanged = true;
                    }
                }
                
                int length = _displayList.size();
                if(displayIndex >= length && length > 0)
                {
                    displayIndex = length - 1;
                }
                if(_displayIndex != displayIndex)
                {
                    _displayIndex = displayIndex;
                    
                    Object* content = _displayList[_displayIndex];
                    if(dynamic_cast<Armature*>(content))
                    {
                        setDisplay(static_cast<Armature*>(content)->getDisplay());
                    }
                    else
                    {
                        setDisplay(content);
                    }
                    
                    if(!_dislayDataList.empty() && _displayIndex <= (int)_dislayDataList.size())
                    {
                        origin = _dislayDataList[_displayIndex]->transform;
                    }
                }
                else if(changeShowState)
                {
                    updateChildArmatureAnimation();
                }
            }
            
            if(!_isHideDisplay && _displayBridge->getDisplay())
            {
                _isDisplayOnStage = true;
            }
            else
            {
                _isDisplayOnStage = false;
            }
        }
        
        /**
         * @inheritDoc
         */
        void Slot::setVisible(bool value)
        {
            if(value != _visible)
            {
                _visible = value;
                updateVisible(_visible);
            }
        }
        
        /** @private */
        void Slot::setArmature(Armature *value)
        {
            DBObject::setArmature(value);
            if(_armature)
            {
                _armature->_slotsZOrderChanged = true;
                _displayBridge->addDisplay(_armature->getDisplay());
            }
            else
            {
                _displayBridge->removeDisplay();
            }
        }
        
        Slot::Slot(IDisplayBridge *displayBrideg)
        {
            _displayBridge = displayBrideg;
            _displayIndex = -1;
            _scaleType = 1;
            
            _originZOrder = 0;
            _tweenZorder = 0;
            _offsetZOrder = 0;
            
            _isDisplayOnStage = false;
            _isHideDisplay = false;
            
            _blendMode = "normal";
            if(_displayBridge->getDisplay())
            {
                _displayBridge->updateBlendMode(_blendMode);
            }
        }
        
        /**
         * @inheritDoc
         */
        void Slot::dispose()
        {
            if(!_displayBridge)
            {
                return;
            }
            DBObject::dispose();
            

            for(size_t i = 0 ; i < _displayList.size() ; i ++)
            {
                delete _displayList[i];
            }
            _displayList.clear();

            DB_SAFE_DELETE(_displayBridge);
            _dislayDataList.clear();
        }
        
        /** @private */
        void Slot::update()
        {
            DBObject::update();
            
            if(_isDisplayOnStage)
            {
                Number pivotX = parent->_tweenPivot.x;
                Number pivotY = parent->_tweenPivot.y;
                if(pivotX || pivotY)
                {
                    Matrix parentMatrix = parent->_globalTransformMatrix;
                    _globalTransformMatrix.tx += parentMatrix.a * pivotX + parentMatrix.c * pivotY;
                    _globalTransformMatrix.ty += parentMatrix.b * pivotX + parentMatrix.d * pivotY;
                }
                
                _displayBridge->updateTransform(_globalTransformMatrix, global);
            }
        }
        
        /** @private */
        void Slot::updateVisible(bool value)
        {
            _displayBridge->setVisible(parent->getVisible() && getVisible() && value);
        }
        
        void Slot::updateChildArmatureAnimation()
        {        
            Armature *childArmature = getChildArmature();
            if(childArmature)
            {
                if(_isHideDisplay)
                {
                    childArmature->getAnimation()->stop();
                    childArmature->getAnimation()->_lastAnimationState = 0;
                }
                else
                {
                    if(
                        _armature &&
                        _armature->getAnimation()->getLastAnimationState() &&
                        childArmature->getAnimation()->hasAnimation(_armature->getAnimation()->getLastAnimationState()->name)
                    )
                    {
                        childArmature->getAnimation()->gotoAndPlay(_armature->getAnimation()->getLastAnimationState()->name);
                    }
                    else
                    {
                        childArmature->getAnimation()->play();
                    }
                }
            }
        }
        
        /**
         * Change all DisplayObject attached to this Bone instance.
         * @param    displayList An array of valid DisplayObject to attach to this Bone.
         */
        void Slot::changeDisplayList(const std::vector<Object*> &displayList)
        {
            _displayList = displayList;
        }

        Slot::~Slot()
        {
            dispose();
        }

}