#include "Cocos2dxDisplayBridge.h"
#include "Cocos2dxFactory.h"
#include "base_nodes/CCNode.h"
namespace dragonBones
{

        bool Cocos2dxDisplayBridge::getVisible()
        {
            return true;
        }
        void Cocos2dxDisplayBridge::setVisible(bool value)
        {
            mDisplayNode->getNode()->setVisible(value);
        }
        
        /**
         * Indicates the original display object relative to specific display engine.
         */
        Object *Cocos2dxDisplayBridge::getDisplay()
        {
            return mDisplay;
        }
        void Cocos2dxDisplayBridge::setDisplay(Object *value)
        {
            cocos2d::CCNode *parent = 0;
            int zOrder = 0;
            if(mDisplayNode)
            {
                parent = mDisplayNode->node->getParent();
                zOrder = mDisplayNode->node->getZOrder();

                removeDisplay();
            }

            mDisplay = value;
            mDisplayNode = dynamic_cast<CocosNode*>(value);
            if(mDisplayNode && parent)
            {
                CocosNode parentNode(parent);
                addDisplay(&parentNode , zOrder);
            }
        }
        
        /**
         * Cleans up resources used by this IDisplayBridge instance.
         */
        void Cocos2dxDisplayBridge::dispose()
        {
        }
        
        /**
         * Updates the transform of the display object
         * @param    matrix
         * @param    transform
         */
        void Cocos2dxDisplayBridge::updateTransform(Matrix &matrix, DBTransform &transform)
        {
            if(mDisplayNode)
            {
                cocos2d::CCNode *n = mDisplayNode->node;
                n->setPosition(matrix.tx , -matrix.ty);
                n->setScaleX(transform.scaleX);
                n->setScaleY(transform.scaleY);
                n->setRotationX(CC_RADIANS_TO_DEGREES(transform.skewX));
                n->setRotationY(CC_RADIANS_TO_DEGREES(transform.skewY));
            }
        }
        
        /**
         * Updates the color of the display object
         * @param    a
         * @param    r
         * @param    g
         * @param    b
         * @param    aM
         * @param    rM
         * @param    gM
         * @param    bM
         */
        void Cocos2dxDisplayBridge::updateColor(
            Number aOffset, 
            Number rOffset, 
            Number gOffset, 
            Number bOffset, 
            Number aMultiplier, 
            Number rMultiplier, 
            Number gMultiplier, 
            Number bMultiplier
        )
        {
            if(mDisplayNode)
            {
                cocos2d::CCNodeRGBA *n = dynamic_cast<cocos2d::CCNodeRGBA*>(mDisplayNode->node);
                n->setColor(cocos2d::ccc3(rMultiplier * 255 , gMultiplier * 255 , bMultiplier * 255));
                n->setOpacity(aMultiplier * 255);
            }
        }
        
        /**
         * Update the blend mode of the display object
         * @param blendMode The blend mode to use. 
         */
        void Cocos2dxDisplayBridge::updateBlendMode(const String &blendMode)
        {
        }
        
        /**
         * Adds the original display object to another display object.
         * @param    container
         * @param    index
         */
        void Cocos2dxDisplayBridge::addDisplay(Object *container, int index)
        {
            if(mDisplayNode)
            {
                CocosNode *parent = dynamic_cast<CocosNode*>(container);
                if(parent)
                {
                    if(mDisplayNode->node->getParent())
                    {
                        mDisplayNode->node->removeFromParentAndCleanup(false);
                    }
                    static int zorder = 0;
                    parent->node->addChild(mDisplayNode->node , index == -1 ? zorder-- : index);
                }
            }
            //if(mDisplayObject)
            //{
            //    CocosNode *parent = dynamic_cast<CocosNode*>(container);
            //    if(parent)
            //    {
            //        if(mDisplayObject->atlasNode->getParent())
            //        {
            //            mDisplayObject->atlasNode->removeFromParent();
            //        }
            //        parent->node->addChild(mDisplayObject->atlasNode);
            //    }
            //}
        }
        
        /**
         * remove the original display object from its parent.
         */
        void Cocos2dxDisplayBridge::removeDisplay()
        {
            if(mDisplayNode && mDisplayNode->node->getParent())
            {
                mDisplayNode->node->removeFromParent();
            }
        }

        Cocos2dxDisplayBridge::~Cocos2dxDisplayBridge()
        {
            dispose();
        }

        Cocos2dxDisplayBridge::Cocos2dxDisplayBridge()
            : mDisplayNode(0)
            , mDisplay(0)
        {

        }

}
