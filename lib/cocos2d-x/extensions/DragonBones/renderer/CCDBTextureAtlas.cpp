#include "CCDBTextureAtlas.h"
#include "objects/TextureAtlasData.h"
#include "textures/CCTextureAtlas.h"
#include "textures/CCTexture2D.h"
#include "cocoa/CCGeometry.h"
namespace dragonBones
{
    CCDBTextureAtlas::CCDBTextureAtlas(TextureAtlasData *data)
        : _textureAtlasRawData(data)
    {
        textureAtlas = cocos2d::CCTextureAtlas::create(data->imagePath.c_str() , data->rects.size());
        textureAtlas->retain();
        uint atlasWidth = textureAtlas->getTexture()->getPixelsWide();
        uint atlasHeight = textureAtlas->getTexture()->getPixelsHigh();
        cocos2d::ccV3F_C4B_T2F_Quad quad;
        uint index = 0;
        for(TextureAtlasData::Rects::iterator iter = _textureAtlasRawData->rects.begin(); iter != _textureAtlasRawData->rects.end() ; iter ++)
        {
			const Rectangle &rect = iter->second;
			float left    = rect.x/(float)atlasWidth;
			float right   = (rect.x + rect.width) / (float)atlasWidth;
			float top     = rect.y/(float)atlasHeight;
			float bottom  = (rect.y + rect.height) / (float)atlasHeight;
			
			quad.bl.texCoords.u = left;
			quad.bl.texCoords.v = bottom;
			quad.br.texCoords.u = right;
			quad.br.texCoords.v = bottom;
			quad.tl.texCoords.u = left;
			quad.tl.texCoords.v = top;
			quad.tr.texCoords.u = right;
			quad.tr.texCoords.v = top;

            quad.bl.colors = cocos2d::ccc4(255,255,255,255);
            quad.br.colors = cocos2d::ccc4(255,255,255,255);
            quad.tl.colors = cocos2d::ccc4(255,255,255,255);
            quad.tr.colors = cocos2d::ccc4(255,255,255,255);

            _textureNames[iter->first] = index;
            textureAtlas->insertQuad(&quad , index++);
        }
    }
    CCDBTextureAtlas::~CCDBTextureAtlas()
    {
        dispose();
    }
    /**
    * The name of this ITextureAtlas.
    */
    const String &CCDBTextureAtlas::getName()
    {
        return _textureAtlasRawData->name;
    }
    
    /**
     * The image path of this ITextureAtlas.
     */
    const String &CCDBTextureAtlas::getImagePath()
    {
        return _textureAtlasRawData->imagePath;
    }
    /**
    * Clean up resources.
    */
    void CCDBTextureAtlas::dispose()
    {
		DB_SAFE_DELETE(_textureAtlasRawData);
        _textureAtlasRawData = 0;
        CC_SAFE_RELEASE_NULL(textureAtlas);
    }
    /**
    * Get the specific region of the TextureAtlas occupied by assets defined by that name.
    * @param    name The name of the assets represented by that name.
    * @return Rectangle The rectangle area occupied by those assets.
    */
    Rectangle CCDBTextureAtlas::getRegion(const String &name)
    {
        TextureAtlasData::Rects::iterator iter = _textureAtlasRawData->rects.find(name);
        if(iter != _textureAtlasRawData->rects.end())
        {
            return iter->second;
        }
        else
        {
            return Rectangle();
        }
    }
/*
    void CCDBTextureAtlas::updateTransform(DisplayObject *displayObject , Matrix &matrix, DBTransform &transform )
    {
        cocos2d::ccV3F_C4B_T2F_Quad & quad = textureAtlas->getQuads()[_textureNames[displayObject->fullName]];

        cocos2d::CCRect rect;
        rect.origin.x = displayObject->pivotX;
        rect.origin.y = displayObject->pivotY;
        Rectangle region = getRegion(displayObject->fullName);
        rect.size.width = region.width;
        rect.size.height = region.height;


        quad.bl.vertices.x = rect.getMinX();
        quad.bl.vertices.y = rect.getMaxY();
        quad.bl.vertices.z = 0;
        quad.br.vertices.x = rect.getMinX();
        quad.br.vertices.y = rect.getMinY();
        quad.br.vertices.z = 0;
        quad.tl.vertices.x = rect.getMaxX();
        quad.tl.vertices.y = rect.getMaxY();
        quad.tl.vertices.z = 0;
        quad.tr.vertices.x = rect.getMaxX();
        quad.tr.vertices.y = rect.getMinY();
        quad.tr.vertices.z = 0;

        *(cocos2d::CCPoint*)&quad.bl.vertices = CCPointApplyAffineTransform(*(cocos2d::CCPoint*)&(quad.bl.vertices), matrix);
        *(cocos2d::CCPoint*)&quad.br.vertices = CCPointApplyAffineTransform(*(cocos2d::CCPoint*)&(quad.br.vertices), matrix);
        *(cocos2d::CCPoint*)&quad.tl.vertices = CCPointApplyAffineTransform(*(cocos2d::CCPoint*)&(quad.tl.vertices), matrix);
        *(cocos2d::CCPoint*)&quad.tr.vertices = CCPointApplyAffineTransform(*(cocos2d::CCPoint*)&(quad.tr.vertices), matrix);

        quad.bl.vertices.y = -quad.bl.vertices.y;
        quad.br.vertices.y = -quad.br.vertices.y;
        quad.tl.vertices.y = -quad.tl.vertices.y;
        quad.tr.vertices.y = -quad.tr.vertices.y;
    }

    void CCDBTextureAtlas::updateColor( DisplayObject *displayObject , Number aOffset, Number rOffset, Number gOffset, Number bOffset, Number aMultiplier, Number rMultiplier, Number gMultiplier, Number bMultiplier )
    {
        cocos2d::ccV3F_C4B_T2F_Quad & quad = textureAtlas->getQuads()[_textureNames[displayObject->fullName]];
        quad.bl.colors.a = aMultiplier * 255;
        quad.bl.colors.r = rMultiplier * 255;
        quad.bl.colors.g = gMultiplier * 255;
        quad.bl.colors.b = bMultiplier * 255;

        quad.br.colors = quad.bl.colors;
        quad.tl.colors = quad.bl.colors;
        quad.tr.colors = quad.bl.colors;
    }*/

}
