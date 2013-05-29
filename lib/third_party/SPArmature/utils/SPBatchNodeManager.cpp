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

#include "SPBatchNodeManager.h"
#include "SPBatchNode.h"

namespace sp{
        
BatchNodeManager *BatchNodeManager::m_sBatchNodeManager = NULL;

BatchNodeManager *BatchNodeManager::sharedBatchNodeManager()
{
    if (m_sBatchNodeManager == NULL)
    {
        m_sBatchNodeManager = new BatchNodeManager();
        if (!m_sBatchNodeManager)
        {
            CC_SAFE_DELETE(m_sBatchNodeManager);
        }
    }
    return m_sBatchNodeManager;
}

BatchNodeManager::BatchNodeManager()
:m_pLayer(NULL)
,m_pLayer2BatchNodeDic(NULL)
{
    setBatchNodeAlphaTestValue(0.5f);
}

BatchNodeManager::~BatchNodeManager()
{
   
}



bool BatchNodeManager::initWithLayer(CCLayer *_layer, std::string _layerName)
{
    bool bRet = false;
    do
    {
        if(m_pLayer2BatchNodeDic == NULL)
        {
            m_pLayer2BatchNodeDic = new CCDictionary();
            CCAssert(m_pLayer2BatchNodeDic, "create m_pLayer2BatchNodeDic fail!");
        }
        
        // test whether the layer is the same with current layer
        if (m_pLayer == _layer)
        {
            return true;
        }
        
        m_pLayer = _layer;
        
        /*
         *  get the BatchNode dictionary belong to the current layer
         *  if current layer is new created, create a new BatchNode dictionary for this layer
         */
        m_pBatchNodeDic = (CCDictionary*)m_pLayer2BatchNodeDic->objectForKey(_layerName);
        
        if(m_pBatchNodeDic != NULL)
        {
            break;
        }
        
        m_pBatchNodeDic = CCDictionary::create();
        m_pLayer2BatchNodeDic->setObject(m_pBatchNodeDic, _layerName);
        
        
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void BatchNodeManager::addBatchNode(std::string _name, BatchNode *_batchNode, int _zOrder)
{
    // if current layer already add _batchNode, then return
    if(m_pLayer->getChildren() && m_pLayer->getChildren()->indexOfObject(_batchNode) != UINT_MAX)
    {
        return;
    }
    
    m_pBatchNodeDic->setObject(_batchNode, _name);
    
    m_pLayer->addChild(_batchNode, _zOrder);
    
}

BatchNode *BatchNodeManager::getBatchNode(std::string _name)
{
    BatchNode *_batchNode = (BatchNode*)m_pBatchNodeDic->objectForKey(_name);
    
    if(_batchNode == NULL)
    {
        _batchNode = BatchNode::create( _name.c_str() );
        addBatchNode(_name, _batchNode);
    }
    
    return _batchNode;
}

void BatchNodeManager::setBatchNodeZOrder(std::string _name, int _zOrder)
{
    CCSpriteBatchNode *_batchNode = getBatchNode(_name);
    if(_batchNode != NULL)
    {
        _batchNode->_setZOrder(_zOrder);
    }
}
    
void BatchNodeManager::setBatchNodeBlendFunc(std::string _name, unsigned int _src, unsigned int _dst)
{
    CCSpriteBatchNode *_batchNode = getBatchNode(_name);
    
    if(_batchNode != NULL)
    {
        ccBlendFunc blendFunc;
        blendFunc.src = _src;
        blendFunc.dst = _dst;
        
        _batchNode->setBlendFunc(blendFunc);
    }
}

void BatchNodeManager::setBatchNodeAlphaTestValue(float _value)
{
    CCGLProgram* alphashader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest);
    CHECK_GL_ERROR_DEBUG();
    
    
    alphashader->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccPositionTextureColorAlphaTest_frag);
    
    alphashader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    alphashader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    alphashader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    alphashader->link();
    
    alphashader->updateUniforms();
    
    unsigned loc = glGetUniformLocation(alphashader->getProgram(), kCCUniformAlphaTestValue);
    CHECK_GL_ERROR_DEBUG();
    
    alphashader->setUniformLocationWith1f(loc, _value);
    CHECK_GL_ERROR_DEBUG();
}

void BatchNodeManager::removeBatchNodes(std::string _layerName)
{
    CCDictionary *_batchNodeDic = (CCDictionary*)m_pLayer2BatchNodeDic->objectForKey(_layerName);
    CCAssert(_batchNodeDic, "_batchNodeDic should not be null!");
    
    _batchNodeDic->removeAllObjects();
    m_pLayer2BatchNodeDic->removeObjectForKey(_layerName);
}
    
CCLayer *BatchNodeManager::getCurrentLayer()
{
    return m_pLayer;
}

}