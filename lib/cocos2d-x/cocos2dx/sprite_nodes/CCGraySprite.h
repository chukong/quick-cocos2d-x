
#ifndef _GRAY_SCPRITE_H_
#define _GRAY_SCPRITE_H_

#include "sprite_nodes/CCSprite.h"
#include "textures/CCTexture2D.h"

using namespace cocos2d;

class CCGraySprite: public CCSprite
{
public:
	static CCGraySprite* create(const char *filename);
	virtual bool initWithTexture(CCTexture2D *texture, const CCRect &rect);
	virtual void draw(void);
};

#endif
