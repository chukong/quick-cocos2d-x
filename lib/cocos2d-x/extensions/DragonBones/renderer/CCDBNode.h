//
//  CCDBNode.h
//  quickcocos2dx
//
//  Created by zrong on 7/22/14.
//  Copyright (c) 2014 qeeplay.com. All rights reserved.
//
#ifndef __CCDBNODE_H__
#define __CCDBNODE_H__

#include "base_nodes/CCNode.h"
#include "utils/BytesType.h"

namespace dragonBones
{
    class CCDBNode : public Object
    {
    public:
        CCDBNode(cocos2d::CCNode *n)
        : node(n)
        {
            if(node)
            {
                node->retain();
            }
        }
        virtual ~CCDBNode()
        {
            if(node)
            {
                node->release();
            }
        }
        
        const cocos2d::CCNode *getNode() const { return node; }
        cocos2d::CCNode *getNode() { return node; }
    private:
        cocos2d::CCNode *node;
    };
}

#endif /*__CCDBNODE_H__*/
