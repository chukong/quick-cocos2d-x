#!/bin/sh
DIR=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )
# cp $DIR/quick-x-player_2012.vcxproj $DIR/quick-x-player_2010.vcxproj

cat $DIR/quick-x-player_2012.sln | sed 's/Microsoft Visual Studio Solution File, Format Version 12.00/Microsoft Visual Studio Solution File, Format Version 11.00/' | sed 's/Visual Studio 2012/Visual Studio 2010/' | sed 's/_2012\.vcxproj/_2010\.vcxproj/' > $DIR/quick-x-player_2010.sln

cat $DIR/quick-x-player_2012.vcxproj | sed 's|<PlatformToolset>v110_xp</PlatformToolset>|<PlatformToolset>v100</PlatformToolset>|' | sed 's/_2012\.vcxproj/_2010\.vcxproj/' > $DIR/quick-x-player_2010.vcxproj

cp $DIR/quick-x-player_2012.vcxproj.filters $DIR/quick-x-player_2010.vcxproj.filters

