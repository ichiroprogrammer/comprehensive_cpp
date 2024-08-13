#!/bin/bash -e

readonly BASE_DIR=$(cd $(dirname $0); pwd)
readonly BASENAME="$(basename $0)"

readonly MD_GEN=$(cd $BASE_DIR/../../md_gen/export/; pwd)

# scriptオプション
#   CLANG_BUILD     make clangを実行するかどうか。デフォルトは実行
#   SCAN_BUILD      make scan-buildを実行するかどうか。デフォルトは実行
#   SAN_BUILD       make sanを実行するかどうか。デフォルトは実行

set -e

function help(){
    echo "$BASENAME  [option]"
    echo "    -a    : equal -ce"
    echo "    -c    : clean before build"
    echo "    -d    : dry run"
    echo "    -e    : find files which encoding is not utf-8"
    echo "    -g    : build by g++ only"
    echo "    -i    : execute IT"
    echo "    -j N  : make -j N for sample build [default:0]"
    echo "    -h    : show this message"
    echo "    -x    : set -x"

    exit $1
}

CLEAN=false
DRY_RUN=false
CHECK_ENCODING=false
CLANG_BUILD=true
SCAN_BUILD=true
SAN_BUILD=true

while getopts ":aCcdeghij:x" flag; do
    case $flag in 
    a) CLEAN=true; CHECK_ENCODING=true ;;
    c) CLEAN=true ;; 
    d) DRY_RUN=true ;; 
    e) CHECK_ENCODING=true ;; 
    g) CLANG_BUILD=false; SCAN_BUILD=false; SAN_BUILD=false ;;
    i) ;; 
    j) PARALLEL="$OPTARG" ;; 
    h) help 0 ;; 
    x) set -x ;; 
    \?) help 1 ;; 
    esac
done

readonly PARA="-j$([ -z "$PARALLEL" ] && : || echo $PARALLEL)"

shift $(expr ${OPTIND} - 1)

$CLEAN && echo "CLEAN"
$DRY_RUN && echo "DRY_RUN"
$CHECK_ENCODING && echo "CHECK_ENCODING"
$CLANG_BUILD && echo "CLANG_BUILD"
$SCAN_BUILD && echo "SCAN_BUILD"
$SAN_BUILD && echo "SCAN_BUILD"

$DRY_RUN && set -x

function cmd_launcher()
{
    $DRY_RUN || eval "$@"
}

function find_not_utf8() {
    pushd $BASE_DIR > /dev/null
    cmd_launcher $MD_GEN/sh/find_not_utf8.sh
    popd > /dev/null
}


$CHECK_ENCODING && find_not_utf8

function build_by() {
    local -r compiler="$1"
    local -r build_dir="${BASE_DIR}/build_${compiler}"


    $CLEAN && rm -rf $build_dir 

    [ -d $build_dir ] || mkdir -p $build_dir
    cd $build_dir > /dev/null

    local cmake_opt="-DUSE_SANITIZERS=ON"
    if [[ "$compiler" == "g++" ]]; then
        local cmake_opt="$cmake_opt -DCMAKE_CXX_COMPILER=$compiler"
    fi

    if $SCAN_BUILD; then
        scan-build cmake $cmake_opt ..
        scan-build make
        cppcheck --project=$build_dir/compile_commands.json

        run-clang-tidy -p $build_dir
    fi

    cmake ..
    make
    ctest

    cd - > /dev/null
}

cmd_launcher build_by "g++"

$CLANG_BUILD && cmd_launcher build_by "clang++"


