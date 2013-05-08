#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR/../"
"$DIR/compile_scripts.sh" -zip -x framework.server -p framework framework lib/framework_precompiled/framework_precompiled

cp lib/framework_precompiled/framework_precompiled.zip samples/CoinFlip/res/
cp lib/framework_precompiled/framework_precompiled.zip samples/Benchmark/res/
