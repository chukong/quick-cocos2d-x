#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include "utils/preDB.h"

namespace dragonBones
{    
    class AnimationData;
    class AnimationState;
    class Armature;
    /**
     * An Animation instance is used to control the animation state of an Armature.
     * @example
     * <p>Download the example files <a href='http://dragonbones.github.com/downloads/DragonBones_Tutorial_Assets.zip'>here</a>: </p>
     * <listing>    
     *    package  
     *    {
     *        import dragonBones.Armature;
     *        import dragonBones.factorys.NativeFactory;
     *        import flash.display.Sprite;
     *        import flash.events.Event;    
     *
     *        public class DragonAnimation extends Sprite 
     *        {        
     *            [Embed(source = "Dragon1.swf", mimeType = "application/octet-stream")]  
     *            private static const ResourcesData:Class;
     *            
     *            private var factory:NativeFactory;
     *            private var armature:Armature;        
     *            
     *            public function DragonAnimation() 
     *            {                
     *                factory = new NativeFactory();
     *                factory.addEventListener(Event.COMPLETE, handleParseData);
     *                factory.parseData(new ResourcesData(), 'Dragon');
     *            }
     *            
     *            private function handleParseData(e:Event):void 
     *            {            
     *                armature = factory.buildArmature('Dragon');
     *                addChild(armature.display as Sprite);             
     *                armature.animation.play();
     *                addEventListener(Event.ENTER_FRAME, updateAnimation);            
     *            }
     *            
     *            private function updateAnimation(e:Event):void 
     *            {
     *                armature.advanceTime(stage.frameRate / 1000);
     *            }        
     *        }
     *    }
     * </listing>
     * @see dragonBones.Armature
     * @see dragonBones.animation.Animation
     * @see dragonBones.animation.AnimationState
     */
    class Animation
    {
    public:
        static const String NONE;
        static const String SAME_LAYER;
        static const String SAME_GROUP;
        static const String SAME_LAYER_AND_GROUP;
        static const String ALL;
        
        /**
         * Whether animation tweening is enabled or not.
         */
        bool tweenEnabled;
        
        /** @private */
        std::vector<std::vector<AnimationState*>* > _animationLayer;
        
        Armature* _armature;
        bool _isActive;
        
        /**
         * Unrecommended API. Recommend use getAnimationList.
         */
        const std::vector<String> &getMovementList();
        
        /**
         * Unrecommended API. Recommend use getLastAnimationName.
         */
        const String &getMovementID();
        
        /**
         * The name of the last AnimationData played.
         * @see dragonBones.objects.animationData->
         */
        const String &getLastAnimationName();
        
        AnimationState *_lastAnimationState;
        /**
         * The last AnimationData this Animation played.
         * @see dragonBones.objects.animationData->
         */
        AnimationState *getLastAnimationState();
        
        std::vector<String> _animationList;
        /**
         * An vector containing all AnimationData names the Animation can play.
         * @see dragonBones.objects.animationData->
         */
        const std::vector<String> &getAnimationList();
        
        bool _isPlaying;
        bool getIsPlaying();
        bool getIsComplete();
        
        std::vector<AnimationData*> _animationDataList;
        /**
         * The AnimationData list associated with this Animation instance.
         * @see dragonBones.objects.animationData->
         */
        const std::vector<AnimationData*>& getAnimationDataList();
        void setAnimationDataList(const std::vector<AnimationData*> &value);

        AnimationData* getAnimationData(std::string &name);
        
        Number _timeScale;
        /**
         * The amount by which passed time should be scaled. Used to slow down or speed up animations. Defaults to 1.
         */
        Number getTimeScale();
        void setTimeScale(Number value);
        
        /**
         * Creates a new Animation instance and attaches it to the passed Armature.
         * @param    An Armature to attach this Animation instance to.
         */
        Animation(Armature *armature);
        
        /**
         * Qualifies all resources used by this Animation instance for garbage collection.
         */
        void dispose();
        
        /**
         * Move the playhead to that AnimationData
         * @param animationName The name of the AnimationData to play.
         * @param fadeInTime A fade time to apply (> 0)
         * @param duration The duration of that animationData->
         * @param loop Loop(0:loop forever, 1~+OO:loop times, -1~-OO:will fade animation after loop complete).
         * @param layer The layer of the animation.
         * @param group The group of the animation.
         * @param fadeOutMode Fade out mode.
         * @param displayControl Display control.
         * @param pauseFadeOut Pause other animation playing.
         * @param pauseFadeIn Pause this animation playing before fade in complete.
         * @see dragonBones.objects.animationData->
         * @see dragonBones.animation.animationState->
         */
        AnimationState* gotoAndPlay(
            const String &animationName, 
            Number fadeInTime = -1, 
            Number duration = -1, 
            Number loop = NaN, 
            uint layer = 0, 
            const String &group = "",
            const String &fadeOutMode = SAME_LAYER_AND_GROUP,
            bool displayControl = true,
            bool pauseFadeOut = true,
            bool pauseFadeIn = true
        );
        
        /**
         * Play the animation from the current position.
         */
        void play();
        
        void stop();
        
        /**
         * Returns the AnimationState named name.
         * @return A AnimationState instance.
         * @see dragonBones.animation.animationState->
         */
        AnimationState* getState(const String &name, uint layer = 0);
        
        bool hasAnimation(const String &animationName);
        
        void advanceTime(Number passedTime);
        
        /** @private */
        void setActive(AnimationState *animationState, bool active);
        
        uint addLayer(uint layer);
        
        void addState(AnimationState *animationState);
        
        void removeState(AnimationState *animationState);
    };
};
#endif // __ANIMATION_H__
