#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
OUTPUT_DIR="$DIR"
MAKE_LUABINDING="$QUICK_COCOS2DX_ROOT"/bin/make_luabinding.sh
$MAKE_LUABINDING -E CCOBJECTS=PhysicsWorld,PhysicsBody -d "$OUTPUT_DIR" PhysicsWorld_luabinding.tolua
