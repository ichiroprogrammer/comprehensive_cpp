#!/bin/bash -e

readonly BASE_DIR=$(cd $(dirname $0); pwd)
readonly BASENAME="$(basename $0)"

# arg0:clean arg1:sanitizer arg2:compiler
function build() {
    local -r clean=$1
    local -r sanitizer=$2
    local -r analysis=$3
    local -r compiler="$4"

    local -r build_dir="${BASE_DIR}/build_${compiler}"

    [[ $clean == "CLEAN" ]] && rm -rf $build_dir

    [ -d  $build_dir ] || mkdir -p $build_dir
    cd $build_dir


    if [[ "$compiler" == "g++" ]]; then
        CMAKE_OPT=
    else
        CMAKE_OPT="-DCMAKE_CXX_COMPILER=$compiler"
    fi

    [[ $sanitizer == "SANITIZER" ]] && CMAKE_OPT="$CMAKE_OPT -DUSE_SANITIZERS=ON"

    if [[ $analysis == "ANALYSIS" ]]; then
        scan-build cmake $CMAKE_OPT ..
        scan-build make
        cppcheck --project=$build_dir/compile_commands.json

        #https://github.com/llvm/llvm-project/blob/main/clang-tools-extra/clang-tidy/tool/run-clang-tidy.py
       ${BASE_DIR}/run-clang-tidy.py -p $build_dir
    else
        make
    fi
}

function help(){
    echo "$BASENAME  [option]"
    echo "    -g     : build by g++"
    echo "    -C     : build by clang++"
    echo "    -c     : clean before build"
    echo "    -d     : debug mode"
    echo "    -A     : analysis cocde"
    echo "    -h     : show this message"

    exit $1
}

COMPILER="g++"
while getopts "ACcdghs" flag; do
    case $flag in 
    c)  declare -r CLEAN="CLEAN";;
    d)  set -x ;;
    C)  COMPILER="clang++";;
    g)  COMPILER="g++";;
    s)  declare -r SANITIZER="SANITIZER";;
    A)  declare -r ANALYSIS="ANALYSIS";;
    h)  help 0 ;; 
    \?) help 1 ;; 
    esac
done


echo $CLEAN
echo $SANITIZER
echo $COMPILER
echo $ANALYSIS  #scan-buildの効果を確かめるためには、 SCAN_BUILD_ERRORをgrepせよ


if [[ "$COMPILER" == "g++" ]]; then
    build "$CLEAN" "$SANITIZER" "$ANALYSIS" "g++"
else
    build "$CLEAN" "$SANITIZER" "$ANALYSIS" "clang++"
fi
