#include "Cocos2dxAtlasNode.h"
#include "textures/CCTextureAtlas.h"
#include "textures/CCTextureCache.h"
#include "CCDirector.h"
#include "shaders/CCGLProgram.h"
#include "shaders/CCShaderCache.h"
#include "shaders/ccGLStateCache.h"
#include "CCDirector.h"
#include "support/TransformUtils.h"

// external
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

// implementation Cocos2dxAtlasNode

// Cocos2dxAtlasNode - Creation & Init

Cocos2dxAtlasNode::Cocos2dxAtlasNode()
: m_pTextureAtlas(NULL)
, m_bIsOpacityModifyRGB(false)
, m_nUniformColor(0)
, m_bIgnoreContentScaleFactor(false)
{
}

Cocos2dxAtlasNode::~Cocos2dxAtlasNode()
{
    CC_SAFE_RELEASE(m_pTextureAtlas);
}

Cocos2dxAtlasNode * Cocos2dxAtlasNode::create(CCTextureAtlas* textureAtlas , unsigned int quadIndex , const CCRect &sourceRect)
{
    Cocos2dxAtlasNode * pRet = new Cocos2dxAtlasNode();
    if (pRet->initWithTextureAtlas(textureAtlas , quadIndex , sourceRect))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool Cocos2dxAtlasNode::initWithTextureAtlas( CCTextureAtlas* textureAtlas , unsigned int quadIndex , const CCRect &sourceRect)
{
    m_nQuadIndex = quadIndex;

    m_tColorUnmodified = ccWHITE;
    m_bIsOpacityModifyRGB = true;

    m_tBlendFunc.src = CC_BLEND_SRC;
    m_tBlendFunc.dst = CC_BLEND_DST;

    m_pTextureAtlas = textureAtlas;

    if (! m_pTextureAtlas)
    {
        CCLOG("cocos2d: Could not initialize Cocos2dxAtlasNode. Invalid Texture.");
        return false;
    }
    m_pTextureAtlas->retain();

    this->updateBlendFunc();
    this->updateOpacityModifyRGB();


    // shader stuff
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture_uColor));
    m_nUniformColor = glGetUniformLocation( getShaderProgram()->getProgram(), "u_color");


    // ���¶�������
    cocos2d::ccV3F_C4B_T2F_Quad & quad = textureAtlas->getQuads()[quadIndex];

    quad.bl.vertices.x = sourceRect.getMinX();
	quad.bl.vertices.y = sourceRect.getMinY();
	quad.bl.vertices.z = 0;
	quad.br.vertices.x = sourceRect.getMaxX();
	quad.br.vertices.y = sourceRect.getMinY();
	quad.br.vertices.z = 0;
	quad.tl.vertices.x = sourceRect.getMinX();
	quad.tl.vertices.y = sourceRect.getMaxY();
	quad.tl.vertices.z = 0;
	quad.tr.vertices.x = sourceRect.getMaxX();
	quad.tr.vertices.y = sourceRect.getMaxY();
	quad.tr.vertices.z = 0;


    //*(cocos2d::CCPoint*)&quad.bl.vertices = CCPointApplyAffineTransform(*(cocos2d::CCPoint*)&(quad.bl.vertices), matrix);
    //*(cocos2d::CCPoint*)&quad.br.vertices = CCPointApplyAffineTransform(*(cocos2d::CCPoint*)&(quad.br.vertices), matrix);
    //*(cocos2d::CCPoint*)&quad.tl.vertices = CCPointApplyAffineTransform(*(cocos2d::CCPoint*)&(quad.tl.vertices), matrix);
    //*(cocos2d::CCPoint*)&quad.tr.vertices = CCPointApplyAffineTransform(*(cocos2d::CCPoint*)&(quad.tr.vertices), matrix);

    //quad.bl.vertices.y = -quad.bl.vertices.y;
    //quad.br.vertices.y = -quad.br.vertices.y;
    //quad.tl.vertices.y = -quad.tl.vertices.y;
    //quad.tr.vertices.y = -quad.tr.vertices.y;
    return true;
}

// Cocos2dxAtlasNode - draw
void Cocos2dxAtlasNode::draw()
{
    CC_NODE_DRAW_SETUP();

    ccGLBlendFunc( m_tBlendFunc.src, m_tBlendFunc.dst );

    GLfloat colors[4] = {_displayedColor.r / 255.0f, _displayedColor.g / 255.0f, _displayedColor.b / 255.0f, _displayedOpacity / 255.0f};
    getShaderProgram()->setUniformLocationWith4fv(m_nUniformColor, colors, 1);

    m_pTextureAtlas->drawNumberOfQuads(1, m_nQuadIndex);
	m_pTextureAtlas->getQuads();
}

// Cocos2dxAtlasNode - RGBA protocol

const ccColor3B& Cocos2dxAtlasNode::getColor()
{
    if(m_bIsOpacityModifyRGB)
    {
        return m_tColorUnmodified;
    }
    return CCNodeRGBA::getColor();
}

void Cocos2dxAtlasNode::setColor(const ccColor3B& color3)
{
    ccColor3B tmp = color3;
    m_tColorUnmodified = color3;

    if( m_bIsOpacityModifyRGB )
    {
        tmp.r = tmp.r * _displayedOpacity/255;
        tmp.g = tmp.g * _displayedOpacity/255;
        tmp.b = tmp.b * _displayedOpacity/255;
    }
    CCNodeRGBA::setColor(tmp);
}

void Cocos2dxAtlasNode::setOpacity(GLubyte opacity)
{
    CCNodeRGBA::setOpacity(opacity);

    // special opacity for premultiplied textures
    if( m_bIsOpacityModifyRGB )
        this->setColor(m_tColorUnmodified);
}

void Cocos2dxAtlasNode::setOpacityModifyRGB(bool bValue)
{
    ccColor3B oldColor = this->getColor();
    m_bIsOpacityModifyRGB = bValue;
    this->setColor(oldColor);
}

bool Cocos2dxAtlasNode::isOpacityModifyRGB()
{
    return m_bIsOpacityModifyRGB;
}

void Cocos2dxAtlasNode::updateOpacityModifyRGB()
{
    m_bIsOpacityModifyRGB = m_pTextureAtlas->getTexture()->hasPremultipliedAlpha();
}

void Cocos2dxAtlasNode::setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor)
{
    m_bIgnoreContentScaleFactor = bIgnoreContentScaleFactor;
}

// Cocos2dxAtlasNode - CocosNodeTexture protocol

ccBlendFunc Cocos2dxAtlasNode::getBlendFunc()
{
    return m_tBlendFunc;
}

void Cocos2dxAtlasNode::setBlendFunc(ccBlendFunc blendFunc)
{
    m_tBlendFunc = blendFunc;
}

void Cocos2dxAtlasNode::updateBlendFunc()
{
    if( ! m_pTextureAtlas->getTexture()->hasPremultipliedAlpha() ) {
        m_tBlendFunc.src = GL_SRC_ALPHA;
        m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
    }
}

void Cocos2dxAtlasNode::setTexture(CCTexture2D *texture)
{
    m_pTextureAtlas->setTexture(texture);
    this->updateBlendFunc();
    this->updateOpacityModifyRGB();
}

CCTexture2D * Cocos2dxAtlasNode::getTexture()
{
    return m_pTextureAtlas->getTexture();
}

void Cocos2dxAtlasNode::setTextureAtlas(CCTextureAtlas* var)
{
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(m_pTextureAtlas);
    m_pTextureAtlas = var;
}

CCTextureAtlas * Cocos2dxAtlasNode::getTextureAtlas()
{
    return m_pTextureAtlas;
}


NS_CC_END
