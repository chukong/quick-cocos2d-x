#include "CCDBDisplayBridge.h"
#include "base_nodes/CCNode.h"
#include "CCDBNode.h"
namespace dragonBones
{

        bool CCDBDisplayBridge::getVisible()
        {
            return true;
        }
        void CCDBDisplayBridge::setVisible(bool value)
        {
            mDisplayNode->getNode()->setVisible(value);
        }
        
        /**
         * Indicates the original display object relative to specific display engine.
         */
        Object *CCDBDisplayBridge::getDisplay()
        {
            return mDisplay;
        }
        void CCDBDisplayBridge::setDisplay(Object *value)
        {
            cocos2d::CCNode *parent = 0;
            int zOrder = 0;
            if(mDisplayNode)
            {
                parent = mDisplayNode->getNode()->getParent();
                zOrder = mDisplayNode->getNode()->getZOrder();

                removeDisplay();
            }

            mDisplay = value;
            mDisplayNode = dynamic_cast<CCDBNode*>(value);
            if(mDisplayNode && parent)
            {
                CCDBNode parentNode(parent);
                addDisplay(&parentNode , zOrder);
            }
        }
        
        /**
         * Cleans up resources used by this IDisplayBridge instance.
         */
        void CCDBDisplayBridge::dispose()
        {
        }
        
        /**
         * Updates the transform of the display object
         * @param    matrix
         * @param    transform
         */
        void CCDBDisplayBridge::updateTransform(Matrix &matrix, DBTransform &transform)
        {
            if(mDisplayNode)
            {
                cocos2d::CCNode *n = mDisplayNode->getNode();
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
        void CCDBDisplayBridge::updateColor(
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
                cocos2d::CCNodeRGBA *n = dynamic_cast<cocos2d::CCNodeRGBA*>(mDisplayNode->getNode());
                n->setColor(cocos2d::ccc3(rMultiplier * 255 , gMultiplier * 255 , bMultiplier * 255));
                n->setOpacity(aMultiplier * 255);
            }
        }
        
        /**
         * Update the blend mode of the display object
         * @param blendMode The blend mode to use. 
         */
        void CCDBDisplayBridge::updateBlendMode(const String &blendMode)
        {
        }
        
        /**
         * Adds the original display object to another display object.
         * @param    container
         * @param    index
         */
        void CCDBDisplayBridge::addDisplay(Object *container, int index)
        {
            if(mDisplayNode)
            {
                CCDBNode *parent = dynamic_cast<CCDBNode*>(container);
                if(parent)
                {
                    if(mDisplayNode->getNode()->getParent())
                    {
                        mDisplayNode->getNode()->removeFromParentAndCleanup(false);
                    }
                    static int zorder = 0;
                    parent->getNode()->addChild(mDisplayNode->getNode() , index == -1 ? zorder-- : index);
                }
            }
            //if(mDisplayObject)
            //{
            //    CCDBNode *parent = dynamic_cast<CCDBNode*>(container);
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
        void CCDBDisplayBridge::removeDisplay()
        {
            if(mDisplayNode && mDisplayNode->getNode()->getParent())
            {
                mDisplayNode->getNode()->removeFromParent();
            }
        }

        CCDBDisplayBridge::~CCDBDisplayBridge()
        {
            dispose();
        }

        CCDBDisplayBridge::CCDBDisplayBridge()
            : mDisplayNode(0)
            , mDisplay(0)
        {

        }

}
