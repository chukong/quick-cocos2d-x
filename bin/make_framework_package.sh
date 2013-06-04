#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR/../"
"$DIR/compile_scripts.sh" -zip -x framework.server -p framework framework lib/framework_precompiled/framework_precompiled

cp lib/framework_precompiled/framework_precompiled.zip sample/coinflip/res/
cp lib/framework_precompiled/framework_precompiled.zip sample/benchmark/res/
cp lib/framework_precompiled/framework_precompiled.zip sample/network/res/
cp lib/framework_precompiled/framework_precompiled.zip sample/physics/res/
cp lib/framework_precompiled/framework_precompiled.zip template/PROJECT_TEMPLATE_01/res/
