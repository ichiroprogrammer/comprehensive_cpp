#!/bin/bash

# refactor_4の自動IT

declare -r TARGET=$1

# IFILE     std::cinの代わりとなるファイル
# OFILE_EXP std::coutの予想値
# OFILE_ACT std::coutの代わりとなるファイル

declare -r IFILE=${TARGET}_i.txt
declare -r OFILE_EXP=${TARGET}_o_exp.txt
declare -r OFILE_ACT=${TARGET}_o_act.txt

function gen_expect {
    echo $1
    echo $1
    echo $2
    echo $1
    echo $2
    echo $3
}

# test 1

# IFILEの作成
cat << IFILE_END > $IFILE
+abcdef
.
+ddd
.
+ffff
.
=
IFILE_END

gen_expect "ABCDEF" "DDD" "FFFF" > $OFILE_EXP
$TARGET -i $IFILE -o $OFILE_ACT
declare -r diff_result0=$(diff $OFILE_EXP $OFILE_ACT)

[[ -n "$diff_result0" ]] && exit $LINENO

# test 2

# // @@@ sample begin 0:0

# $IFILEの作成
cat << IFILE_END > $IFILE
+abcdef
+ddd
+ffff
=
IFILE_END

# expectの生成
gen_expect "ABCDEF" "DDD" "FFFF" > $OFILE_EXP

$TARGET -i $IFILE -o $OFILE_ACT

declare -r diff_result1=$(diff $OFILE_EXP $OFILE_ACT)

# $TARGETが正常動作すれば、文字列diff_result1の長さは0
[[ -n "$diff_result1" ]] && exit $LINENO
# // @@@ sample end

rm -rf $IFILE $OFILE_EXP $OFILE_ACT 

