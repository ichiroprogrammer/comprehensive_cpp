#!/bin/bash -e

readonly BASE_DIR=$(cd $(dirname $0); pwd)
readonly BASENAME="$(basename $0)"

$BASE_DIR/../../deep/build/build_core.sh $BASE_DIR $@
