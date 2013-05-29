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

#include "SPDisplayFactoryManager.h"

#include "SPSpriteDisplayFactory.h"
#include "SPArmatureDisplayFactory.h"
#include "SPParticleDisplayFactory.h"
#include "SPShaderDisplayFactory.h"

#include "SPSpriteDisplayData.h"
#include "SPArmatureDisplayData.h"
#include "SPParticleDisplayData.h"
#include "SPShaderDisplayData.h"



namespace sp{
    
CCDictionary *DisplayFactoryManager::g_DisplayFactoryMap = new CCDictionary();
    
void DisplayFactoryManager::addtoMap(DisplayType _displayType, DisplayFactory *_factory)
{
    g_DisplayFactoryMap->setObject(_factory, _displayType);
}

DisplayFactory *DisplayFactoryManager::getFactory(DisplayType _displayType)
{
    DisplayFactory *_factory = NULL;    
    _factory = (DisplayFactory*)g_DisplayFactoryMap->objectForKey(_displayType);

    if(!_factory)
    {
        switch (_displayType) {
            case SP_DISPLAY_SPRITE:
                _factory = new SpriteDisplayFactory();
                break;
            case SP_DISPLAY_ARMATURE:
                _factory = new ArmatureDisplayFactory();
                break;
			case SP_DISPLAY_PARTICLE:
				_factory = new ParticleDisplayFactory();
				break;
			case SP_DISPLAY_SHADER:
                _factory = new ShaderDisplayFactory();
                break;
            default:
                _factory = new SpriteDisplayFactory();
                break;
        }
        
        _factory->autorelease();
        addtoMap(_displayType, _factory);
    }
    
    return _factory;
}
    
DisplayData *DisplayFactoryManager::createDisplayData(DisplayType _displayType)
{
    DisplayData *_data = NULL;
    
    switch (_displayType) {
        case SP_DISPLAY_SPRITE:
            _data = SpriteDisplayData::create();
            break;
        case SP_DISPLAY_ARMATURE:
            _data = ArmatureDisplayData::create();
            break;
		case SP_DISPLAY_PARTICLE:
			_data = ParticleDisplayData::create();
			break;
		case SP_DISPLAY_SHADER:
			_data = ShaderDisplayData::create();
			break;
        default:
            _data = SpriteDisplayData::create();
            break;
    }
    
    return _data;
}


}