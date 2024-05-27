#!/bin/bash -e

# @@@ sample begin 0:0

readonly BASE_DIR=$(cd $(dirname $0); pwd)
readonly BASENAME="$(basename $0)"

$BASE_DIR/../../deep/build/build_core.sh $BASE_DIR $@ -i
# build_core.shによって下記が行われ、何らかのエラーが発生した場合、非0でexitする。
# * ビルド & UT & IT
# * 静的解析
# * 動的解析
# @@@ sample end
