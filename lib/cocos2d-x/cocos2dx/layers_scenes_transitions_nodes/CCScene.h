/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CCSCENE_H__
#define __CCSCENE_H__

#include <vector>

#include "layers_scenes_transitions_nodes/CCLayer.h"

using namespace std;

NS_CC_BEGIN

/**
 * @addtogroup scene
 * @{
 */

class CC_DLL CCTouchableNode : public CCObject
{
public:
    static CCTouchableNode *create(CCNode *node);
    ~CCTouchableNode();

    CCNode *getNode();

    int getTouchMode();

    int getTouchId();
    void setTouchId(int touchId);

    CCTouch *getTouch();
    void setTouch(CCTouch *touch);

    void addTouchIdForMultiTouches(int touchId);
    bool hasTouchIdForMultiTouches(int touchId);

    CCSet *getTouchesForMultiTouches();
    void addTouchForMultiTouches(CCTouch *touch);

    void cleanupTouchAndTouches();
    void setInvalid();

    bool isValid();

private:
    CCTouchableNode(CCNode *node);

    CCNode *m_node;
    int m_touchMode;
    int m_touchId;
    vector<int> m_touchIds;

    CCTouch *m_touch;
    CCSet *m_touches;

    bool m_valid;
};

/** @brief CCScene is a subclass of CCNode that is used only as an abstract concept.

 CCScene an CCNode are almost identical with the difference that CCScene has it's
 anchor point (by default) at the center of the screen.

 For the moment CCScene has no other logic than that, but in future releases it might have
 additional logic.

 It is a good practice to use and CCScene as the parent of all your nodes.
 */
class CC_DLL CCScene : public CCLayer
{
public:
    /**
     *  @js ctor
     */
    CCScene();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCScene();
    bool init();

    static CCScene *create(void);

    virtual CCScene *getScene();

    void addTouchableNode(CCNode *node);
    void removeTouchableNode(CCNode *node);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

    virtual void visit();

protected:
    CCArray *m_touchableNodes;
    CCArray *m_touchingNodes;
    bool m_touchDispatchingEnabled;

    CCTouchableNode *findTouchingNode(CCNode *node);
    void sortAllTouchableNodes(CCArray *nodes);
    void enableTouchDispatching();
    void disableTouchDispatching();
};

// end of scene group
/// @}

NS_CC_END

#endif // __CCSCENE_H__
