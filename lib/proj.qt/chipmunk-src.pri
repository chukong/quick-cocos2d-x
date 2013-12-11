# 行首插入
# :%s/^/xo
# 行尾添加
# :%s/$/xo
# 删除包含某字符串的行
# :1,$ s/.*Word.*\n*//         #\n* 是防止在文件尾出现, 没有\n结尾

SOURCES += \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/chipmunk.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpConstraint.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpDampedRotarySpring.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpDampedSpring.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpGearJoint.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpGrooveJoint.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpPinJoint.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpPivotJoint.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpRatchetJoint.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpRotaryLimitJoint.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpSimpleMotor.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/constraints/cpSlideJoint.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpArbiter.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpArray.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpBB.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpBBTree.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpBody.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpCollision.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpHashSet.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpPolyShape.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpShape.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpace.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpaceComponent.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpaceHash.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpaceQuery.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpaceStep.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSpatialIndex.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpSweep1D.c \
$${ROOT}/lib/cocos2d-x/external/chipmunk/src/cpVect.c
