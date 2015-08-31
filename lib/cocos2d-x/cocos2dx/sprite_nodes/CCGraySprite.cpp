
#include "sprite_nodes/CCGraySprite.h"
#include "sprite_nodes/CCSpriteFrame.h"
#include "sprite_nodes/CCSpriteFrameCache.h"
#include "textures/CCTexture2D.h"
#include "shaders/ccShaders.h"
#include "shaders/CCShaderCache.h"

USING_NS_CC;

/**
 * Creates an empty sprite without texture. You can call setTexture method subsequently.
 *
 * @return An empty sprite object that is marked as autoreleased.
 */
CCGraySprite* CCGraySprite::create()
{
    CCGraySprite *pSprite = new CCGraySprite();
    if (pSprite && pSprite->init())
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

/**
 * Creates a sprite with an image filename.
 *
 * After creation, the rect of sprite will be the size of the image,
 * and the offset will be (0,0).
 *
 * @param   pszFileName The string which indicates a path to image file, e.g., "scene1/monster.png".
 * @return  A valid sprite object that is marked as autoreleased.
 */
CCGraySprite* CCGraySprite::create(const char *pszFileName)
{
    CCGraySprite *pobSprite = new CCGraySprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

/**
 * Creates a sprite with an image filename and a rect.
 *
 * @param   pszFileName The string wich indicates a path to image file, e.g., "scene1/monster.png"
 * @param   rect        Only the contents inside rect of pszFileName's texture will be applied for this sprite.
 * @return  A valid sprite object that is marked as autoreleased.
 */
CCGraySprite* CCGraySprite::create(const char *pszFileName, const CCRect& rect)
{
    CCGraySprite *pobSprite = new CCGraySprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

/**
 * Creates a sprite with an exsiting texture contained in a CCTexture2D object
 * After creation, the rect will be the size of the texture, and the offset will be (0,0).
 *
 * @param   pTexture    A pointer to a CCTexture2D object.
 * @return  A valid sprite object that is marked as autoreleased.
 */
CCGraySprite* CCGraySprite::createWithTexture(CCTexture2D *pTexture)
{
    CCGraySprite *pobSprite = new CCGraySprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture, CCRectZero, false))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

/**
 * Creates a sprite with a texture and a rect.
 *
 * After creation, the offset will be (0,0).
 *
 * @param   pTexture    A pointer to an existing CCTexture2D object.
 *                      You can use a CCTexture2D object for many sprites.
 * @param   rect        Only the contents inside the rect of this texture will be applied for this sprite.
 * @return  A valid sprite object that is marked as autoreleased.
 */
CCGraySprite* CCGraySprite::createWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    CCGraySprite *pobSprite = new CCGraySprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture, rect, false))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

/**
 * Creates a sprite with an sprite frame.
 *
 * @param   pSpriteFrame    A sprite frame which involves a texture and a rect
 * @return  A valid sprite object that is marked as autoreleased.
 */
CCGraySprite* CCGraySprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    CCGraySprite *pobSprite = new CCGraySprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

/**
 * Creates a sprite with an sprite frame name.
 *
 * A CCSpriteFrame will be fetched from the CCSpriteFrameCache by pszSpriteFrameName param.
 * If the CCSpriteFrame doesn't exist it will raise an exception.
 *
 * @param   pszSpriteFrameName A null terminated string which indicates the sprite frame name.
 * @return  A valid sprite object that is marked as autoreleased.
 */
CCGraySprite* CCGraySprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif

    return createWithSpriteFrame(pFrame);
}

bool CCGraySprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect, bool rotated)
{
	do
    {
		CC_BREAK_IF(!CCSprite::initWithTexture(pTexture, rect, rotated));

        CCGLProgram* pProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureGray);
		setShaderProgram(pProgram);
		CHECK_GL_ERROR_DEBUG();

		getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		CHECK_GL_ERROR_DEBUG();

		getShaderProgram()->link();
		CHECK_GL_ERROR_DEBUG();

		getShaderProgram()->updateUniforms();
		CHECK_GL_ERROR_DEBUG();

		return true;
	} while (0);

	return false;
}

void CCGraySprite::draw()
{
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
	ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);

	this->getShaderProgram()->use();
	this->getShaderProgram()->setUniformsForBuiltins();

	ccGLBindTexture2D(this->getTexture()->getName());

#define kQuadSize sizeof(m_sQuad.bl)
	long offset = (long)&m_sQuad;

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CC_INCREMENT_GL_DRAWS(1);
}
