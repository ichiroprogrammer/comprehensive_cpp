#!/bin/bash -e

readonly BASE_DIR=$(cd $(dirname $0); pwd)
readonly BASENAME="$(basename $0)"

# @@@ sample begin 0:0
function help(){
    echo "$BASENAME  [option]"
    echo "    -a BIN : BIN is test target(default:./g++/deps)"
    echo "    -d     : debug mode"
    echo "    -h     : show this message"

    exit $1
}

# @@@ ignore begin
while getopts "a::dh" flag; do
    case $flag in 
    a)  declare -r APP_ARG=$(realpath "$OPTARG") ;; 
    d)  set -x ;;
    h)  help 0 ;; 
    \?) help 1 ;; 
    esac
done

if [[ -z "$APP_ARG" ]]; then
    declare -r APP="./g++/deps"
else
    declare -r APP=$APP_ARG
fi

shift $(expr ${OPTIND} - 1)

cd ${BASE_DIR} > /dev/null

function exit_trap() {
    local -r exit_code=$?

    [[ $exit_code -ne 0 ]] && echo "Exit with $exit_code"
    [[ $exit_code -eq 0 ]] && echo "OK"

    exit $exit_code
}

trap exit_trap EXIT

function test_unknown_opt() {
    local -r exp=it_data/unknown_opt_exp.txt
    local -r act=${exp}.act

    rm -f $act

    err_occured=false
    $APP -G > $act || err_occured=true

    if $err_occured; then
        diff $exp $act
    else
        echo "test error"
        exit $LINENO
    fi

    rm $act
}

function test_help() {
    local -r exp=it_data/help_exp.txt
    local -r act=${exp}.act

    rm -f $act

    $APP -h > $act
    diff $exp $act

    $APP --help > $act
    diff $exp $act

    rm $act
}

function test_p() {
    local -r exp=$1
    shift
    local -r dir=$@
    local -r act=${exp}.act
    rm -f $act

    $APP p -R -o $act $dir
    diff $exp $act

    rm $act
}

function test_s() {
    local -r exp=$1
    shift
    local -r dir=$@
    local -r act=${exp}.act
    rm -f $act

    $APP s -R -o $act $dir
    diff $exp $act

    rm $act
}

function test_log() {
    local -r exp=$1
    local -r dir=$2
    local -r act=${exp}.act
    rm -f $act

    $APP p -R -l $act $dir
    diff $exp $act

    rm $act
}

function test_p_i() {
    local -r exp=$1
    local -r dir=$2
    local -r act=${exp}.act
    rm -f $act

    $APP p -R -o $act -i $dir
    diff $exp $act

    rm $act
}

function test_p2s() {
    local -r exp=$1
    shift
    local -r dir=$@
    local -r act=${exp}.act
    rm -f $act

    $APP p2s -R -o $act $dir
    diff $exp $act

    rm $act
}

function test_p2s_s() {
    local -r exp=$1
    shift
    local -r dir=$@
    local -r act=${exp}.act
    rm -f $act

    $APP p2s -s -o $act $dir
    diff $exp $act

    rm $act
}

function test_p2s_Rs() {
    local -r exp=$1
    shift
    local -r dir=$@
    local -r act=${exp}.act
    rm -f $act

    $APP p2s -s -R -o $act $dir
    diff $exp $act

    rm $act
}

function test_p2p() {
    local -r exp=$1
    shift
    local -r dir=$@
    local -r act=${exp}.act
    rm -f $act

    $APP p2p -R -o $act $dir
    diff $exp $act

    rm $act
}

function test_p2p_e() {
    local -r exp=$1
    shift
    local -r dir=$@
    local -r act=${exp}.act
    rm -f $act

    $APP p2p -e '.*/mod2/?.*' -R -o $act $dir
    diff $exp $act

    rm $act
}

function test_p2p_i() {
    local -r exp=$1
    local -r in=$2
    local -r act=${exp}.act
    rm -f $act

    $APP p2p -i $in -o $act $dir
    diff $exp $act

    rm $act
}

function test_p2p_s() {
    local -r exp=$1
    shift
    local -r dir=$@
    local -r act=${exp}.act
    rm -f $act

    $APP p2p -s -R -o $act $dir
    diff $exp $act

    rm $act
}

function test_a() {
    local -r exp=$1
    local -r in=$2
    local -r act=${exp}.act
    rm -f $act

    $APP a -i $in -o $act $dir
    diff $exp $act

    rm $act
}

# @@@ ignore end

function test_a2pu() {
    local -r exp=$1
    local -r in=$2
    local -r act=${exp}.act
    rm -f $act

    $APP a2pu -i $in -o $act $dir
    diff $exp $act

    rm $act
}

# @@@ ignore begin
function test_deps_fake() {
    local -r target_dir=it_data/fake

    local -r p_e_exp=it_data/fake_p_e.txt
    local -r p_e_act=${p_e_exp}.act

    $APP p -R -o $p_e_act $target_dir
    diff $p_e_exp $p_e_act
    rm $p_e_act

    local -r p2p_e_exp=it_data/fake_p2p_e.txt
    local -r p2p_e_act=${p2p_e_exp}.act

    $APP p2p -i $p_e_exp -o $p2p_e_act
    diff $p2p_e_exp $p2p_e_act
    rm $p2p_e_act

    local -r a2pu_e_exp=it_data/fake_a2pu_e.pu
    local -r a2pu_e_act=${a2pu_e_exp}.act

    $APP a2pu -i $p2p_e_exp -o $a2pu_e_act
    diff $a2pu_e_exp $a2pu_e_act
    rm $a2pu_e_act

    local -r cyc_e_exp=it_data/fake_cyc_e.txt
    local -r cyc_e_act=${cyc_e_exp}.act

    $APP cyc -i $p2p_e_exp -o $cyc_e_act
    diff $cyc_e_exp $cyc_e_act
    rm $cyc_e_act

    local -r p_exp=it_data/fake_p.txt
    local -r p_act=${p_exp}.act
    $APP p -R -e ".*/fake/.*/e$" -o $p_act $target_dir
    diff $p_exp $p_act
    rm $p_act

    local -r p2p_exp=it_data/fake_p2p.txt
    local -r p2p_act=${p2p_exp}.act
    $APP p2p -i $p_exp -o $p2p_act
    diff $p2p_exp $p2p_act
    rm $p2p_act

    local -r a2pu_exp=it_data/fake_a2pu.pu
    local -r a2pu_act=${a2pu_exp}.act
    $APP a2pu -i $p2p_exp -o $a2pu_act
    diff $a2pu_exp $a2pu_act
    rm $a2pu_act

    local -r cyc_exp=it_data/fake_cyc.txt
    local -r cyc_act=${cyc_exp}.act

    err_occured=false
    $APP cyc -i $p2p_exp -o $cyc_act || err_occured=true
    if $err_occured; then
        diff $cyc_exp $cyc_act
        rm $cyc_act
    else
        echo "test error"
        exit $LINENO
    fi
}

function test_deps_dep() {
    local -r p2p_exp=it_data/deps.p2p
    local -r p2p_act=${p2p_exp}.act

    local -r pu_exp=../../plant_uml/deps.pu
    local -r pu_act=${pu_exp}.act

    $APP p2p -R -e "(.*/h/?.*)|(.*/src/?.*)|(.*/ut/?.*)" \
        -o $p2p_act app/ dependency/ file_utils/ lib/ logging/
    diff $p2p_exp $p2p_act
    rm $p2p_act

    $APP a2pu -i $p2p_exp -o $pu_act
    diff $pu_exp $pu_act
    rm $pu_act

    local -r cyc_exp=it_data/deps_cyc.txt
    local -r cyc_act=${cyc_exp}.act

    $APP cyc -i $p2p_exp -o $cyc_act
    diff $cyc_exp $cyc_act
    rm $cyc_act
}

function test_deps_dep2() {
    local -r p2p_exp=it_data/deps_2.p2p
    local -r p2p_act=${p2p_exp}.act

    local -r pu_exp=../../plant_uml/deps_2.pu
    local -r pu_act=${pu_exp}.act

    $APP p2p -R -e "(.*/h/?.*)|(.*/src/?.*)" \
        -o $p2p_act app/ dependency/ file_utils/ lib/ logging/
    diff $p2p_exp $p2p_act
    rm $p2p_act

    $APP a2pu -i $p2p_exp -o $pu_act
    diff $pu_exp $pu_act
    rm $pu_act

    local -r cyc_exp=it_data/deps_cyc.txt
    local -r cyc_act=${cyc_exp}.act

    $APP cyc -i $p2p_exp -o $cyc_act
    diff $cyc_exp $cyc_act
    rm $cyc_act
}

echo test_unknown_opt && test_unknown_opt
echo test_help        && test_help
echo test_p 0         && test_p it_data/p_ut_data_exp.txt ut_data 
echo test_p 1         && test_p it_data/p_ut_data_app1_exp.txt ut_data/app1/ ut_data/app3/ 
echo test_s 0         && test_s it_data/s_ut_data_exp.txt ut_data 
echo test_s 1         && test_s it_data/s_ut_data_app1_exp.txt ut_data/app1/ ut_data/app3/ 
echo test_log 0       && test_log it_data/log_exp.txt ut_data
echo test_p_i 0       && test_p_i it_data/p_ut_data_exp.txt it_data/dir_app1_app2.txt
echo test_p2s 0       && test_p2s it_data/p2s_ut_data_app1_app2.txt ut_data
echo test_p2s 1       && test_p2s it_data/p2s_ut_data_app1_app2.txt ut_data/app1  ut_data/app2
echo test_p2s_s 0     && test_p2s_s it_data/p2s_ut_data_s.txt ut_data/

echo test_p2s_s 1     && test_p2s_s it_data/p2s_ut_data_app1_s.txt ut_data/app1
echo test_p2s_s 2     && test_p2s_s it_data/p2s_ut_data_app1_app2_s.txt ut_data/app1 ut_data/app2
echo test_p2s_Rs 0    && test_p2s_Rs it_data/p2s_ut_data_rs.txt ut_data/
echo test_p2p 0       && test_p2p it_data/p2p_ut_data.txt ut_data
echo test_p2p_e 0     && test_p2p_e it_data/p2p_e_ut_data.txt ut_data
echo test_p2p_i 0     && test_p2p_i it_data/p2p_ut_data_s.txt it_data/p2s_ut_data_rs.txt
echo test_p2p_s 0     && test_p2p_s it_data/p2p_ut_data_s.txt ut_data
# @@@ ignore end

echo test_a 0         && test_a it_data/a_ut_data.txt it_data/p2p_ut_data.txt 
echo test_a2pu 0      && test_a2pu it_data/pu_ut_data.pu it_data/p2p_ut_data.txt 
echo test_a2pu 1      && test_a2pu it_data/pu_ut_data_s.pu it_data/p2p_ut_data_s.txt
echo test_deps_fake   && test_deps_fake
echo test_deps_dep    && test_deps_dep
echo test_deps_dep2   && test_deps_dep2
# @@@ sample end
