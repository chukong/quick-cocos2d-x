#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
OUTPUT_DIR="$DIR"
MAKE_LUABINDING="$QUICK_COCOS2DX_ROOT"/bin/compile_luabinding.sh
$MAKE_LUABINDING -E CCOBJECTS=CCPhysicsWorld,CCPhysicsBody,CCPhysicsShape,CCPhysicsDebugNode,CCPhysicsCollisionEvent,CCPhysicsVector -d "$OUTPUT_DIR" CCPhysicsWorld_luabinding.tolua
