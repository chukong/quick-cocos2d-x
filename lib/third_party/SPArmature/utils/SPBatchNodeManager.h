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

#ifndef __SPArmature__SPBatchNodeManager__
#define __SPArmature__SPBatchNodeManager__

#include <iostream>
#include "cocos2d.h"
#include "SPBatchNode.h"

using namespace cocos2d;

namespace sp{
    

class BatchNodeManager {
    
public:
    /*
     *  @brief   If you want to reset the AlphaTestValue, you can use this method.
     *          You should note this method will effect all CCNode used cocos2dx's Alpha Test Shader
     *
     *  @param  _value  the value you want to set to Alpha Test, 
     */
    static void setBatchNodeAlphaTestValue(float _value);
public:
    
    static BatchNodeManager *sharedBatchNodeManager();
    
    /*
     *  @brief   init members with a CCLayer
     */
    virtual bool initWithLayer(CCLayer *_layer, std::string _layerName);
    
    /*
     *  @brief   add a BatchNode to current layer
     *
     *  @param  _name   the image name used by _batchNode, used for a key
     *
     *  @param  _batchNode  the BatchNode you want to added to current layer
     *
     *  @param  _zOrder BatchNode's zorder, defualt is 0
     */
    void addBatchNode(std::string _name, BatchNode *_batchNode, int _zOrder = 0);
    
    /*
     *  @brief   Get a BatchNode which used a image named _name from current layer. 
     *          If do not exsit, create a new BatchNode named _name and add to current layer
     */
    BatchNode *getBatchNode(std::string _name);
    
    /*
     *  @brief   set the zorder of BatchNode named _name
     *
     *  @param  _name BatchNode's name
     *
     *  @param  _zOrder the zorder you want to set
     */
    void setBatchNodeZOrder(std::string _name, int _zOrder);
    
    void setBatchNodeBlendFunc(std::string _name, unsigned int _src, unsigned int _dst);
    
    /*
     *  @brief   remove all BatchNodes added to the layer named _layerName
     *
     *  @param  _name the layer's name
     */
    void removeBatchNodes(std::string _layerName);
    
    CCLayer *getCurrentLayer();
private:
    /*
     *  @brief   when create a BatchNodeManager, it will set Alpha Test to 0.5
     */
    BatchNodeManager();
    ~BatchNodeManager();
    
    static BatchNodeManager *m_sBatchNodeManager;
    
    /*
     *  @key the image name the CCSpriteBatchNode use
     *
     *  @value  CCSpriteBatchNode*
     */
    CCDictionary *m_pBatchNodeDic;
    
    /*
     *  @key layer's name
     *
     *  @value  BatchNode dictionary
     */
    CCDictionary *m_pLayer2BatchNodeDic;
    
    //! current CCLayer
    CCLayer *m_pLayer;
    
    /*
     *  a map used to judge if a layer with a name is the same with the layer in the map named with the same name.
     */
    CCDictionary *m_pLayerMap;
};

}

#endif /* defined(__SPArmature__SPBatchNodeManager__) */
