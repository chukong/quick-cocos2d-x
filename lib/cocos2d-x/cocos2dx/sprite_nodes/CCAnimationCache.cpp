/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Ricardo Quesada
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
#include "CCAnimationCache.h"
#include "ccMacros.h"
#include "CCAnimation.h"
#include "CCSpriteFrame.h"
#include "CCSpriteFrameCache.h"
#include "cocoa/CCString.h"
#include "platform/CCFileUtils.h"
#include <queue>

using namespace std;

NS_CC_BEGIN

using AsyncStruct = struct _AsyncStruct
{
    int plistCount = 0;
    CCDictionary* animations;
    CCObject* target;
    SEL_CallFuncO selector;
    int handler;
};

static std::queue<AsyncStruct*>* s_pAsyncStructQueue = nullptr;

CCAnimationCache* CCAnimationCache::s_pSharedAnimationCache = NULL;

CCAnimationCache* CCAnimationCache::sharedAnimationCache(void)
{
    if (! s_pSharedAnimationCache)
    {
        s_pSharedAnimationCache = new CCAnimationCache();
        s_pSharedAnimationCache->init();
    }

    return s_pSharedAnimationCache;
}

void CCAnimationCache::purgeSharedAnimationCache(void)
{
    CC_SAFE_RELEASE_NULL(s_pSharedAnimationCache);
}

bool CCAnimationCache::init()
{
    m_pAnimations = new CCDictionary();
    return true;
}

CCAnimationCache::CCAnimationCache()
: m_pAnimations(NULL)
{
}

CCAnimationCache::~CCAnimationCache()
{
    CCLOGINFO("cocos2d: deallocing %p", this);
    CC_SAFE_RELEASE(m_pAnimations);
    if(!s_pAsyncStructQueue)
    {
        delete s_pAsyncStructQueue;
        s_pAsyncStructQueue = nullptr;
    }
}

void CCAnimationCache::addAnimation(CCAnimation *animation, const char * name)
{
    m_pAnimations->setObject(animation, name);
}

void CCAnimationCache::removeAnimationByName(const char* name)
{
    if (! name)
    {
        return;
    }

    m_pAnimations->removeObjectForKey(name);
}

CCAnimation* CCAnimationCache::animationByName(const char* name)
{
    return (CCAnimation*)m_pAnimations->objectForKey(name);
}

void CCAnimationCache::parseVersion1(CCDictionary* animations)
{
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();

    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(animations, pElement)
    {
        CCDictionary* animationDict = (CCDictionary*)pElement->getObject();
        CCArray* frameNames = (CCArray*)animationDict->objectForKey("frames");
        float delay = animationDict->valueForKey("delay")->floatValue();
        CCAnimation* animation = NULL;

        if ( frameNames == NULL ) 
        {
            CCLOG("cocos2d: CCAnimationCache: Animation '%s' found in dictionary without any frames - cannot add to animation cache.", pElement->getStrKey());
            continue;
        }

        CCArray* frames = CCArray::createWithCapacity(frameNames->count());
        frames->retain();

        CCObject* pObj = NULL;
        CCARRAY_FOREACH(frameNames, pObj)
        {
            const char* frameName = ((CCString*)pObj)->getCString();
            CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(frameName);

            if ( ! spriteFrame ) {
                CCLOG("cocos2d: CCAnimationCache: Animation '%s' refers to frame '%s' which is not currently in the CCSpriteFrameCache. This frame will not be added to the animation.", pElement->getStrKey(), frameName);

                continue;
            }

            CCAnimationFrame* animFrame = new CCAnimationFrame();
            animFrame->initWithSpriteFrame(spriteFrame, 1, NULL);
            frames->addObject(animFrame);
            animFrame->release();
        }

        if ( frames->count() == 0 ) {
            CCLOG("cocos2d: CCAnimationCache: None of the frames for animation '%s' were found in the CCSpriteFrameCache. Animation is not being added to the Animation Cache.", pElement->getStrKey());
            continue;
        } else if ( frames->count() != frameNames->count() ) {
            CCLOG("cocos2d: CCAnimationCache: An animation in your dictionary refers to a frame which is not in the CCSpriteFrameCache. Some or all of the frames for the animation '%s' may be missing.", pElement->getStrKey());
        }

        animation = CCAnimation::create(frames, delay, 1);

        CCAnimationCache::sharedAnimationCache()->addAnimation(animation, pElement->getStrKey());
        frames->release();
    }    
}

void CCAnimationCache::parseVersion2(CCDictionary* animations)
{
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();

    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(animations, pElement)
    {
        const char* name = pElement->getStrKey();
        CCDictionary* animationDict = (CCDictionary*)pElement->getObject();

        const CCString* loops = animationDict->valueForKey("loops");
        bool restoreOriginalFrame = animationDict->valueForKey("restoreOriginalFrame")->boolValue();

        CCArray* frameArray = (CCArray*)animationDict->objectForKey("frames");

        if ( frameArray == NULL ) {
            CCLOG("cocos2d: CCAnimationCache: Animation '%s' found in dictionary without any frames - cannot add to animation cache.", name);
            continue;
        }

        // Array of AnimationFrames
        CCArray* array = CCArray::createWithCapacity(frameArray->count());
        array->retain();

        CCObject* pObj = NULL;
        CCARRAY_FOREACH(frameArray, pObj)
        {
            CCDictionary* entry = (CCDictionary*)(pObj);

            const char* spriteFrameName = entry->valueForKey("spriteframe")->getCString();
            CCSpriteFrame *spriteFrame = frameCache->spriteFrameByName(spriteFrameName);

            if( ! spriteFrame ) {
                CCLOG("cocos2d: CCAnimationCache: Animation '%s' refers to frame '%s' which is not currently in the CCSpriteFrameCache. This frame will not be added to the animation.", name, spriteFrameName);

                continue;
            }

            float delayUnits = entry->valueForKey("delayUnits")->floatValue();
            CCDictionary* userInfo = (CCDictionary*)entry->objectForKey("notification");

            CCAnimationFrame *animFrame = new CCAnimationFrame();
            animFrame->initWithSpriteFrame(spriteFrame, delayUnits, userInfo);

            array->addObject(animFrame);
            animFrame->release();
        }

        float delayPerUnit = animationDict->valueForKey("delayPerUnit")->floatValue();
        CCAnimation *animation = new CCAnimation();
        animation->initWithAnimationFrames(array, delayPerUnit, 0 != loops->length() ? loops->intValue() : 1);
        array->release();

        animation->setRestoreOriginalFrame(restoreOriginalFrame);

        CCAnimationCache::sharedAnimationCache()->addAnimation(animation, name);
        animation->release();
    }
}

void CCAnimationCache::addAnimationsWithDictionary(CCDictionary* dictionary)
{
    CCDictionary* animations = (CCDictionary*)dictionary->objectForKey("animations");

    if ( animations == NULL ) {
        CCLOG("cocos2d: CCAnimationCache: No animations were found in provided dictionary.");
        return;
    }

    unsigned int version = 1;
    CCDictionary* properties = (CCDictionary*)dictionary->objectForKey("properties");
    if( properties )
    {
        version = properties->valueForKey("format")->intValue();
        CCArray* spritesheets = (CCArray*)properties->objectForKey("spritesheets");

        CCObject* pObj = NULL;
        CCARRAY_FOREACH(spritesheets, pObj)
        {
            CCString* name = (CCString*)(pObj);
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(name->getCString());
        }
    }

    switch (version) {
        case 1:
            parseVersion1(animations);
            break;
        case 2:
            parseVersion2(animations);
            break;
        default:
            CCAssert(false, "Invalid animation format");
    }
}

/** Read an NSDictionary from a plist file and parse it automatically for animations */
void CCAnimationCache::addAnimationsWithFile(const char* plist)
{
    CCAssert( plist, "Invalid texture file name");

    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist);
    CCDictionary* dict = CCDictionary::createWithContentsOfFile(path.c_str());

    CCAssert( dict, "CCAnimationCache: File could not be found");

    addAnimationsWithDictionary(dict);
}

void CCAnimationCache::addAnimationsWithFileAsync(const char* plist, cocos2d::CCObject *target, SEL_CallFuncO selector)
{
    addAnimationsWithFileAsyncImpl(plist, target, selector);
}

void CCAnimationCache::addAnimationsWithFileAsync(const char* plist, int handler)
{
    addAnimationsWithFileAsyncImpl(plist, nullptr, nullptr, handler);
}

void CCAnimationCache::addAnimationsWithFileAsyncImpl(const char *plist, CCObject *target, SEL_CallFuncO selector, int handler)
{
    CCAssert( plist, "Invalid texture file name");
    
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist);
    CCDictionary* dict = CCDictionary::createWithContentsOfFile(path.c_str());
    CCAssert( dict, "CCAnimationCache: File could not be found");
    
    CCDictionary* animations = (CCDictionary*)dict->objectForKey("animations");
    
    if ( animations == NULL ) {
        CCLOG("cocos2d: CCAnimationCache: No animations were found in provided dictionary.");
        return;
    }
    
    unsigned int version = 1;
    CCDictionary* properties = (CCDictionary*)dict->objectForKey("properties");
    if( properties )
    {
        if (!s_pAsyncStructQueue)
        {
            s_pAsyncStructQueue = new queue<AsyncStruct*>();
        }
        
        AsyncStruct *data = new AsyncStruct();
        data->plistCount = 0;
        data->animations = CCDictionary::createWithDictionary(animations);
        data->animations->retain();
        data->target = target;
        data->selector = selector;
        data->handler = handler;
        s_pAsyncStructQueue->push(data);
        
        version = properties->valueForKey("format")->intValue();
        CCArray* spritesheets = (CCArray*)properties->objectForKey("spritesheets");
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(spritesheets, pObj)
        {
            CCString* name = (CCString*)(pObj);
            ++data->plistCount;
            //CCLOG("addAnimationsWithFileAsyncImpl: %s %d", name->getCString(), data->plistCount);
            CCSpriteFrameCache::sharedSpriteFrameCache()
                ->addSpriteFramesWithFileAsync(name->getCString(),
                                                 this,
                                                 callfuncO_selector(CCAnimationCache::addSpriteFramesAsyncCallBack));
        }
    }
    if(version > 2)
    {
        CCAssert(false, "Invalid animation format");
    }
    // The metadata version1 does't support async loading.
    if(version == 1)
    {
        parseVersion1(animations);
    }
}

void CCAnimationCache::addSpriteFramesAsyncCallBack(CCObject* obj)
{
    //CCLOG("CCAnimationCache::addSpriteFramesAsyncCallBack");
    AsyncStruct *pAsyncStruct = nullptr;
    if(s_pAsyncStructQueue->empty())
    {
        // do nothing
    }
    else
    {
        pAsyncStruct = s_pAsyncStructQueue->front();
        --pAsyncStruct->plistCount;
        if(pAsyncStruct->plistCount <= 0)
        {
            s_pAsyncStructQueue->pop();
            
            CCObject *target = pAsyncStruct->target;
            SEL_CallFuncO selector = pAsyncStruct->selector;
            int handler = pAsyncStruct->handler;
            
            parseVersion2(pAsyncStruct->animations);
            
            doAsyncCallBack(target, selector, handler);
            CC_SAFE_RELEASE(pAsyncStruct->animations);
            delete pAsyncStruct;
        }

    }
}

void CCAnimationCache::doAsyncCallBack(CCObject* target, SEL_CallFuncO selector, int handler)
{
    if (target && selector)
    {
        (target->*selector)(target);
    }
    if (handler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()
            ->executeEvent(handler, "addAnimationsWithFileAsync");
    }
}

NS_CC_END