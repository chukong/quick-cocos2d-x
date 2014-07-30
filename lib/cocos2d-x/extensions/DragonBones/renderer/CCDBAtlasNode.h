
#ifndef __COCOS2DX_ATLAS_NODE_H__
#define __COCOS2DX_ATLAS_NODE_H__

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "ccTypes.h"
#include "utils/preDB.h"
#include "utils/BytesType.h"

NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

class CCTextureAtlas;

/** @brief CCDBAtlasNode is a subclass of CCNode that implements the CCRGBAProtocol and CCTextureProtocol protocol

It knows how to render a TextureAtlas object.
If you are going to render a TextureAtlas consider subclassing CCDBAtlasNode (or a subclass of CCDBAtlasNode)

All features from CCNode are valid, plus the following features:
- opacity and RGB colors
*/
class CCDBAtlasNode : public CCNodeRGBA, public CCTextureProtocol , public dragonBones::Object
{
protected:
    
    ccColor3B    m_tColorUnmodified;

    CC_PROPERTY(CCTextureAtlas*, m_pTextureAtlas, TextureAtlas);

    // protocol variables
    bool m_bIsOpacityModifyRGB;
    
    CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc);

    // color uniform
    GLint    m_nUniformColor;
    // This varible is only used for CCLabelAtlas FPS display. So plz don't modify its value.
    bool m_bIgnoreContentScaleFactor;

    // 要画哪个矩形
    unsigned int m_nQuadIndex;
    
public:
    CCDBAtlasNode();
    virtual ~CCDBAtlasNode();

    /** creates a CCDBAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
    static CCDBAtlasNode * create(CCTextureAtlas* textureAtlas , unsigned int quadIndex , const CCRect &sourceRect);
    bool initWithTextureAtlas(CCTextureAtlas* textureAtlas , unsigned int quadIndex , const CCRect &sourceRect);
    

    virtual void draw();

    // CC Texture protocol

    /** returns the used texture*/
    virtual CCTexture2D* getTexture(void);

    /** sets a new texture. it will be retained*/
    virtual void setTexture(CCTexture2D *texture);
    
    virtual bool isOpacityModifyRGB();
    virtual void setOpacityModifyRGB(bool isOpacityModifyRGB);
    virtual const ccColor3B& getColor(void);
    virtual void setColor(const ccColor3B& color);
    virtual void setOpacity(GLubyte opacity);

private :
    void updateBlendFunc();
    void updateOpacityModifyRGB();
    
    friend class CCDirector;
    void setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor);
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCATLAS_NODE_H__


