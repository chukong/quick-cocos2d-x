#ifndef __I_TEXTURE_ATLAS_H__
#define __I_TEXTURE_ATLAS_H__
#include "utils/preDB.h"
namespace dragonBones
{
    /**
     * The ITextureAtlas interface defines the methods used by all ITextureAtlas within the dragonBones system (flash or starling DisplayObject based).
     * @see dragonBones.Armature
     */
    class ITextureAtlas : public Object
    {
    public:
        /**
         * The name of this ITextureAtlas.
         */
        virtual const String &getName() = 0;
        /**
         * Clean up resources.
         */
        virtual void dispose() = 0;
        /**
         * Get the specific region of the TextureAtlas occupied by assets defined by that name.
         * @param    name The name of the assets represented by that name.
         * @return Rectangle The rectangle area occupied by those assets.
         */
        virtual Rectangle getRegion(const String &name) = 0;
    };
};
#endif // __I_TEXTURE_ATLAS_H__
