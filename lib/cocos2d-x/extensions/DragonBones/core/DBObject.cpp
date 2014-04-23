#include "DBObject.h"
#include "Armature.h"
#include <cmath>
namespace dragonBones
{    
    DBObject::DBObject()
    {
        tween.scaleX = tween.scaleY = 0;            
        _visible = true;
        _armature = 0;
        parent = 0;
        fixedRotation = false;
        userData = 0;
        _scaleType = 0;
        _isColorChanged = false;
    }

    DBObject::~DBObject()
    {
        dispose();
    }


        void DBObject::setVisible(bool visible)
        {
            _visible = visible;
        }
        bool DBObject::getVisible()
        {
            return _visible;
        }
        /**
         * The armature this DBObject instance belongs to.
         */
        Armature* DBObject::getArmature()
        {
            return _armature;
        }

    /** @private */
    void DBObject::setArmature(Armature *value)
    {
        if(_armature)
        {
            _armature->removeDBObject(this);
        }
        _armature = value;
        if(_armature)
        {
            _armature->addDBObject(this);
        }
    }
    /**
        * Cleans up any resources used by this DBObject instance.
        */
    void DBObject::dispose()
    {
        userData = 0;
        parent = 0;
        _armature = 0;
        fixedRotation = false;
        _scaleType = 0;
        _isColorChanged = false;
        global = DBTransform();
        origin = DBTransform();
        offset = DBTransform();
        tween = DBTransform();
        _globalTransformMatrix = Matrix();
    }
        
    /** @private */
    void DBObject::update()
    {
        global.scaleX = (origin.scaleX + tween.scaleX) * offset.scaleX;
        global.scaleY = (origin.scaleY + tween.scaleY) * offset.scaleY;
            
        if(parent)
        {
            Number x = origin.x + offset.x + tween.x;
            Number y = origin.y + offset.y + tween.y;
            Matrix parentMatrix = parent->_globalTransformMatrix;
                
            _globalTransformMatrix.tx = global.x = parentMatrix.a * x + parentMatrix.c * y + parentMatrix.tx;
            _globalTransformMatrix.ty = global.y = parentMatrix.d * y + parentMatrix.b * x + parentMatrix.ty;
                
            if(fixedRotation)
            {
                global.skewX = origin.skewX + offset.skewX + tween.skewX;
                global.skewY = origin.skewY + offset.skewY + tween.skewY;
            }
            else
            {
                global.skewX = origin.skewX + offset.skewX + tween.skewX + parent->global.skewX;
                global.skewY = origin.skewY + offset.skewY + tween.skewY + parent->global.skewY;
            }
                
            if(parent->scaleMode >= _scaleType)
            {
                global.scaleX *= parent->global.scaleX;
                global.scaleY *= parent->global.scaleY;
            }
        }
        else
        {
            _globalTransformMatrix.tx = global.x = origin.x + offset.x + tween.x;
            _globalTransformMatrix.ty = global.y = origin.y + offset.y + tween.y;
                
            global.skewX = origin.skewX + offset.skewX + tween.skewX;
            global.skewY = origin.skewY + offset.skewY + tween.skewY;
        }
            
        _globalTransformMatrix.a = global.scaleX * cos(global.skewY);
        _globalTransformMatrix.b = global.scaleX * sin(global.skewY);
        _globalTransformMatrix.c = -global.scaleY * sin(global.skewX);
        _globalTransformMatrix.d = global.scaleY * cos(global.skewX);
    }
};
