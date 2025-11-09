#!/bin/bash -e

readonly BASE_DIR=$(cd $(dirname $0); pwd)
readonly BASENAME="$(basename $0)"

$BASE_DIR/essential/build/build_all.sh $BASE_DIR $BASENAME $@
