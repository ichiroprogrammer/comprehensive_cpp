#!/bin/bash -e

readonly BASE_DIR=$(cd $(dirname $0); pwd)
readonly BASENAME="$(basename $0)"

# arg0:clean arg1:sanitizer arg2:compiler
function build() {
    local -r clean=$1
    local -r sanitizer=$2
    local -r analysis=$3
    local -r compiler=$4

    local -r build_dir="${BASE_DIR}/build_${compiler}"

    [[ $clean == "CLEAN" ]] && rm -rf $build_dir

    [ -d  $build_dir ] || mkdir -p $build_dir
    cd $build_dir


    local -r SANITIZER_FLAGS="-fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow"

    CMAKE_OPT="-DCMAKE_CXX_COMPILER=$compiler -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"

    if [[ $sanitizer == "SANITIZER" ]]; then
        CMAKE_OPT=$CMAKE_OPT
        CMAKE_OPT="$CMAKE_OPT -DCMAKE_CXX_FLAGS=\"$SANITIZER_FLAGS\""
        CMAKE_OPT="$CMAKE_OPT -DCMAKE_EXE_LINKER_FLAGS=\"$SANITIZER_FLAGS\""
    fi

    if [[ $analysis == "ANALYSIS" ]]; then
        scan-build cmake $CMAKE_OPT ..
        scan-build --use-cc=clang --use-c++=clang++ make
        cppcheck --project=$build_dir/compile_commands.json
    else
        cmake $CMAKE_OPT ..
        make
    fi
}

function help(){
    echo "$BASENAME  [option]"
    echo "    -g     : build b g++ only"
    echo "    -c     : clean before build"
    echo "    -d     : debug mode"
    echo "    -A     : analysis cocde"
    echo "    -h     : show this message"

    exit $1
}


while getopts "Acdghs" flag; do
    case $flag in 
    c)  declare -r CLEAN="CLEAN";;
    d)  set -x ;;
    g)  declare -r GCC_ONLY_temp=false ;; 
    s)  declare -r SANITIZER="SANITIZER";;
    A)  declare -r ANALYSIS="ANALYSIS";;
    h)  help 0 ;; 
    \?) help 1 ;; 
    esac
done


$GCC_ONLY_temp && declare -r GCC_ONLY=false || declare -r GCC_ONLY=true

echo $CLEAN
echo $SANITIZER
$GCC_ONLY && echo "GCC_ONLY"


build "$CLEAN" "$SANITIZER" "$ANALYSIS" "g++"

if $GCC_ONLY ; then
: 
else
    build "$CLEAN" "$SANITIZER" "$ANALYSIS" "clang++"
fi
