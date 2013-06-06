#!/bin/sh
DIR=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )
# cp $DIR/quick-x-player_2012.vcxproj $DIR/quick-x-player_2010.vcxproj

cat $DIR/quickcocos2dx_2012.vcxproj | sed 's|<PlatformToolset>v110_xp</PlatformToolset>|<PlatformToolset>v100</PlatformToolset>|' | sed 's/_2012\.vcxproj/_2010\.vcxproj/' > $DIR/quickcocos2dx_2010.vcxproj

cp $DIR/quickcocos2dx_2012.vcxproj.filters $DIR/quickcocos2dx_2010.vcxproj.filters
