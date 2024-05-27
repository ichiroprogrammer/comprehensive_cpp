#!/bin/bash -e

# @@@ sample begin 0:0

readonly BASE_DIR=$(cd $(dirname $0); pwd)
readonly BASENAME="$(basename $0)"

$BASE_DIR/../deep/build/build_foreach.sh $BASE_DIR $@
          
# @@@ sample end
