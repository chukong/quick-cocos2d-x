#!/bin/sh
DIR=$( cd $( dirname ${BASH_SOURCE[0]} ) && pwd )
ROOT_DIR=`dirname "$DIR"`

# player/proj.win32

cat $ROOT_DIR/player/proj.win32/quick-x-player_2012.sln | sed 's/Microsoft Visual Studio Solution File, Format Version 12.00/Microsoft Visual Studio Solution File, Format Version 11.00/' | sed 's/Visual Studio 2012/Visual Studio 2010/' | sed 's/_2012/_2010/' > $ROOT_DIR/player/proj.win32/quick-x-player_2010.sln

cp $ROOT_DIR/player/proj.win32/quick-x-player_2012.vcxproj $ROOT_DIR/player/proj.win32/quick-x-player_2010.vcxproj
cat $ROOT_DIR/player/proj.win32/quick-x-player_2012.vcxproj | sed 's|<PlatformToolset>v110_xp</PlatformToolset>|<PlatformToolset>v100</PlatformToolset>|' | sed 's/_2012/_2010/' > $ROOT_DIR/player/proj.win32/quick-x-player_2010.vcxproj

cp $ROOT_DIR/player/proj.win32/quick-x-player_2012.vcxproj.filters $ROOT_DIR/player/proj.win32/quick-x-player_2010.vcxproj.filters


# lib/proj.win32

cp $ROOT_DIR/lib/proj.win32/cocos2dx_2012.vcxproj $ROOT_DIR/lib/proj.win32/cocos2dx_2010.vcxproj
cat $ROOT_DIR/lib/proj.win32/cocos2dx_2012.vcxproj | sed 's|<PlatformToolset>v110_xp</PlatformToolset>|<PlatformToolset>v100</PlatformToolset>|' | sed 's/_2012/_2010/' > $ROOT_DIR/lib/proj.win32/cocos2dx_2010.vcxproj

cp $ROOT_DIR/lib/proj.win32/cocos2dx_2012.vcxproj.filters $ROOT_DIR/lib/proj.win32/cocos2dx_2010.vcxproj.filters


# lib/cocos2dx_extra/proj.win32

cp $ROOT_DIR/lib/cocos2dx_extra/proj.win32/cocos2dx_extra_2012.vcxproj $ROOT_DIR/lib/cocos2dx_extra/proj.win32/cocos2dx_extra_2010.vcxproj
cat $ROOT_DIR/lib/cocos2dx_extra/proj.win32/cocos2dx_extra_2012.vcxproj | sed 's|<PlatformToolset>v110_xp</PlatformToolset>|<PlatformToolset>v100</PlatformToolset>|' | sed 's/_2012/_2010/' > $ROOT_DIR/lib/cocos2dx_extra/proj.win32/cocos2dx_extra_2010.vcxproj

cp $ROOT_DIR/lib/cocos2dx_extra/proj.win32/cocos2dx_extra_2012.vcxproj.filters $ROOT_DIR/lib/cocos2dx_extra/proj.win32/cocos2dx_extra_2010.vcxproj.filters


# lib/lua_extensions/proj.win32

cp $ROOT_DIR/lib/lua_extensions/proj.win32/lua_extensions_2012.vcxproj $ROOT_DIR/lib/lua_extensions/proj.win32/lua_extensions_2010.vcxproj
cat $ROOT_DIR/lib/lua_extensions/proj.win32/lua_extensions_2012.vcxproj | sed 's|<PlatformToolset>v110_xp</PlatformToolset>|<PlatformToolset>v100</PlatformToolset>|' | sed 's/_2012/_2010/' > $ROOT_DIR/lib/lua_extensions/proj.win32/lua_extensions_2010.vcxproj

cp $ROOT_DIR/lib/lua_extensions/proj.win32/lua_extensions_2012.vcxproj.filters $ROOT_DIR/lib/lua_extensions/proj.win32/lua_extensions_2010.vcxproj.filters


# lib/third_party/proj.win32

cp $ROOT_DIR/lib/third_party/proj.win32/third_party_2012.vcxproj $ROOT_DIR/lib/third_party/proj.win32/third_party_2010.vcxproj
cat $ROOT_DIR/lib/third_party/proj.win32/third_party_2012.vcxproj | sed 's|<PlatformToolset>v110_xp</PlatformToolset>|<PlatformToolset>v100</PlatformToolset>|' | sed 's/_2012/_2010/' > $ROOT_DIR/lib/third_party/proj.win32/third_party_2010.vcxproj

cp $ROOT_DIR/lib/third_party/proj.win32/third_party_2012.vcxproj.filters $ROOT_DIR/lib/third_party/proj.win32/third_party_2010.vcxproj.filters
