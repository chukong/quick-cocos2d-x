#ifndef __DB_OBJECT_H__
#define __DB_OBJECT_H__
#include "utils/preDB.h"
#include "objects/DBTransform.h"
namespace dragonBones
{    
    class Bone;
    class Armature;
    class DBObject
    {    
    protected:
        /** @private */
        bool _visible;
    public:
        DBObject();
        virtual ~DBObject();

        /**
         * The name of this DBObject instance's Armature instance.
         */
        String name;
        
        /**
         * An object that can contain any user extra data.
         */
        Object* userData;
        
        /**
         * 
         */
        bool fixedRotation;

        /** @private */
        DBTransform global;
        /** @private */
        DBTransform origin;

        /** @private */
        DBTransform offset;
        /** @private */
        DBTransform tween;


        /** @private */
        Bone *parent;

        virtual void setVisible(bool visible);
        virtual bool getVisible();
        /**
         * The armature this DBObject instance belongs to.
         */
        virtual Armature* getArmature();
        /** @private */
        virtual void setArmature(Armature *value);
        /**
         * Cleans up any resources used by this DBObject instance.
         */
        virtual void dispose();
        
        /** @private */
        virtual void update();
        /** @private */
        Matrix _globalTransformMatrix;

        /** @private */
        int _scaleType;
        /** @private */
        bool _isColorChanged;
        /** @private */
        Armature *_armature;        
    };
};
#endif // __DB_OBJECT_H__
