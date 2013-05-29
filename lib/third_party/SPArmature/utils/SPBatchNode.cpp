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

#include "SPBatchNode.h"
#include "SPArmatureDefine.h"

namespace sp{

BatchNode *BatchNode::create(const char *_fileName)
{
	BatchNode *_batchNode = new BatchNode();
	if (_batchNode && _batchNode->initWithFile(_fileName, kDefaultSpriteBatchCapacity))
	{
		_batchNode->autorelease();
		return _batchNode;
	}
	CC_SAFE_DELETE(_batchNode);
	return NULL;
}

BatchNode::BatchNode()
    :m_eRenderType(BATCHNODE_ZORDER)
{
}
    
void BatchNode::setRenderType(RENDER_TYPE _renderType)
{
    if (m_eRenderType == _renderType)
    {
        return;
    }
    m_eRenderType = _renderType;
    
    switch (m_eRenderType) {
        case SIMPLE_ZORDER:
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
            break;
        case BATCHNODE_ZORDER:
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
            break;
        case BATCHNODE_VERTEXZ:
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest));
            break;
        default:
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
            break;
    }

}

RENDER_TYPE BatchNode::getRenderType()
{
    return m_eRenderType;
}
    
void BatchNode::draw()
{
    ccDirectorProjection _originProjection;
    if (m_eRenderType == BATCHNODE_VERTEXZ)
    {
        // enable depth test
        CCDirector::sharedDirector()->setDepthTest(true);
        _originProjection = CCDirector::sharedDirector()->getProjection();
        
        CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
        
        // enable alpha test, used for opengl es 1.0
//        glEnable(GL_ALPHA_TEST);
//        glAlphaFunc(GL_GREATER, 0.5f);
        
//        
//        CCSize size = CCDirector::sharedDirector()->getWinSize();
//        
//        
//        //  open 2d projection. We not use CCDirector::setProjection(kCCDirectorProjection2D),
//        //  because it's near value and far value is 1024, small for us
//        
//        kmGLMatrixMode(KM_GL_PROJECTION);
//        kmGLLoadIdentity();
//        kmMat4 orthoMatrix;
//        kmMat4OrthographicProjection(&orthoMatrix, 0, size.width / CC_CONTENT_SCALE_FACTOR(), 0, size.height / CC_CONTENT_SCALE_FACTOR(), -MAX_VERTEXZ_VALUE, MAX_VERTEXZ_VALUE );
//        kmGLMultMatrix(&orthoMatrix); 
//        kmGLMatrixMode(KM_GL_MODELVIEW);
//        kmGLLoadIdentity();
    }
	
    
	CCSpriteBatchNode::draw();
    

    if (m_eRenderType == BATCHNODE_VERTEXZ)
    {
        CCDirector::sharedDirector()->setDepthTest(false);
        
        //disable alpha test, used for opengl es 1.0
//        glDisable(GL_ALPHA_TEST);
        
        CCDirector::sharedDirector()->setProjection(_originProjection);
    }
}

}