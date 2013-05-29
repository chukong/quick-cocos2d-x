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

#include "SPArmatureDefine.h"
#include "SPArmatureDisplayFactory.h"
#include "SPDisplayData.h"
#include "SPArmature.h"
#include "SPDisplayFactoryManager.h"
#include "SPArmatureDisplayData.h"

namespace sp{
    
    
CCObject *ArmatureDisplayFactory::addDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay, DisplayData *_DisplayData)
{
    ArmatureDisplayData *_adp = ArmatureDisplayData::create(); ;
    _adp->copy((ArmatureDisplayData*)_DisplayData);
    
    _decoDisplay->setDisplayData(_adp);
    
    return createDisplay(_bone, _decoDisplay);
}
    
CCObject *ArmatureDisplayFactory::createDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
    CCObject *_display;
    
    ArmatureDisplayData *_displayData = (ArmatureDisplayData*)_decoDisplay->getDisplayData();
    
    Armature *_armature = Armature::create(_displayData->getDisplayName().c_str());
    
    /*
     *  here use the whole Armature to be a display
     */
    _display = _armature;
    
    /*
     *  because this bone have called this name, so _armature should change it's name, or it can't add to
     *  Armature's bone children.
     */
    _armature->setName((_bone->getName() + "_armatureChild").c_str());
    
    _decoDisplay->setDisplay(_display);
    
    return _display;
}
    
void ArmatureDisplayFactory::changeDisplay(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
    
    Armature *_armature = (Armature*)_decoDisplay->getDisplay();
    
    _armature->getAnimation()->playByIndex(0);
    
	CCNode * _renderNode = getRenderNode(_bone, _decoDisplay);
    
    _bone->setChildArmature(_armature);
    
    /*
     *  add child armature to armature's bone list
     */
    if(_bone->getArmature())
    {
        _bone->getArmature()->addBone(_armature->getRootBone(), _bone->getName().c_str());
    }
    
    setDisplay(_bone, _decoDisplay, _renderNode);
}
    
CCNode *ArmatureDisplayFactory::getRenderNode(Bone *_bone, DecorativeDisplay *_decoDisplay)
{
	Armature *_armature = (Armature*)_decoDisplay->getDisplay();
	return _armature->getRootBone()->getDisplayManager()->getDisplayRenderNode();
}

}