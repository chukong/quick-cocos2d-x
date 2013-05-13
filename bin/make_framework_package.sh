#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR/../"
"$DIR/compile_scripts.sh" -zip -x framework.server -p framework framework lib/framework_precompiled/framework_precompiled

cp lib/framework_precompiled/framework_precompiled.zip sample/CoinFlip/res/
cp lib/framework_precompiled/framework_precompiled.zip sample/Benchmark/res/
cp lib/framework_precompiled/framework_precompiled.zip sample/network/res/
cp lib/framework_precompiled/framework_precompiled.zip template/PROJECT_TEMPLATE_01/res/
