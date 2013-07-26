
#include "sprite_nodes/CCGraySprite.h"
#include "shaders/ccShaders.h"

USING_NS_CC;

CCGraySprite* CCGraySprite::create(const char *filename)
{
	CCGraySprite* sprite = new CCGraySprite();
	if (sprite && sprite->initWithFile(filename))
    {
		sprite->autorelease();
		return sprite;
	}
    else
    {
		CC_SAFE_RELEASE(sprite);
		return NULL;
	}
}

bool CCGraySprite::initWithTexture(CCTexture2D *texture, const CCRect &rect)
{
	do{
		CC_BREAK_IF(!CCSprite::initWithTexture(texture, rect));

		const GLchar* pszFragSource =
        "#ifdef GL_ES \n \
        precision mediump float; \n \
#endif \n \
uniform sampler2D u_texture; \n \
varying vec2 v_texCoord; \n \
varying vec4 v_fragmentColor; \n \
void main(void) \n \
{ \n \
// Convert to greyscale using NTSC weightings \n \
vec4 col = texture2D(u_texture, v_texCoord); \n \
float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114));  \n \
gl_FragColor = vec4(grey, grey, grey, col.a); \n \
}";

		CCGLProgram* pProgram = new CCGLProgram();
		pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
		this->setShaderProgram(pProgram);
		pProgram->release();
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->link();
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->updateUniforms();
		CHECK_GL_ERROR_DEBUG();

		return true;
	} while (0);
	return false;
}

void CCGraySprite::draw()
{
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

	this->getShaderProgram()->use();
	this->getShaderProgram()->setUniformsForBuiltins();

	ccGLBindTexture2D( this->getTexture()->getName() );

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