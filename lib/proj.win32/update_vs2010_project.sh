q#!/bin/sh
DIR=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )

cat $DIR/cocos2dx_2012.vcxproj | sed 's|<PlatformToolset>v110_xp</PlatformToolset>|<PlatformToolset>v100</PlatformToolset>|' | sed 's/_2012\.vcxproj/_2010\.vcxproj/' > $DIR/cocos2dx_2010.vcxproj

cp $DIR/cocos2dx_2012.vcxproj.filters $DIR/cocos2dx_2010.vcxproj.filters
