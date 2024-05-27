#!/bin/bash -e

declare -r BASE_DIR=$(cd $(dirname $0); pwd)

set -x

cd $BASE_DIR

make clean

# gcc
make WARN_ERROR= SUPPRESS_WARN=-DSUPPRESS_WARN_OFF 2> gcc_warnings.txt

sed -e '0,/\(.*warning: comparison of integer.*\)/ s//@@@ sample begin 0:0\n\n\1/' \
    -e '/bool b1{.*;/,+1 s/\(.*~~^~~.*$\)/\1\n@@@ sample end/' \
    -e '0,/\(.*In destructor ‘Pimpl::.*\)/ s//@@@ sample begin 0:1\n\n\1/' \
    -e '/class PimplCore;/,+1 s/\(.*^~\+.*$\)/\1\n@@@ sample end/' \
    -e '0,/\(.*prevent_copy_elision.*\)/ s//@@@ sample begin 0:2\n\n\1/' \
    -e  '/note: remove ‘std::move/a// @@@ sample end' \
    gcc_warnings.txt > warnings/GCC.txt

rm gcc_warnings.txt

# clang
make WARN_ERROR= SUPPRESS_WARN=-DSUPPRESS_WARN_OFF clang 2> clang_warnings.txt

sed -e '/OverloadVirtualDerived::DoSomething/i@@@ sample begin 1:0\n' \
    -e  '/virtual void DoSomething(int32_t)/a@@@ sample end' \
    clang_warnings.txt > warnings/CLANG.txt

rm clang_warnings.txt

# scan-build
make scan-build-row 2> scan-build_warnings.txt

sed -e '/Attempt to free released memory/i@@@ sample begin 2:0\n' \
    -e '/Attempt to free released memory/,+2 s/\(.*^~\+.*$\)/\1\n@@@ sample end/' \
    -e '/Potential leak of memory pointed to by/i@@@ sample begin 2:1\n' \
    -e '/Potential leak of memory pointed to by/,+2 s/\(.*^~\+.*$\)/\1\n@@@ sample end/' \
    scan-build_warnings.txt > warnings/scan-build.txt

rm scan-build_warnings.txt

# cppcheck
make cppcheck

sed -e '/accessed at index 8, which is out of bounds/i@@@ sample begin 1:0\n' \
    -e '/note: Array index out of bounds/,+2 s/\(.*^$\)/\1\n@@@ sample end/' \
    scan-build/cppcheck_bugs.txt > warnings/cppcheck.txt

# sanitizer
#
# sudo sysctl -w kernel.randomize_va_space=0
# によってASLRを無効にしておくと、試行のたびにアドレスが変わることを防げるため、
# diffが少なくなる。
make san-ut 2> sanitizer_warnings.txt # --always-makeしてはいけない

sed -e '/ERROR: AddressSanitizer: new-delete-type-mismatch/i@@@ sample begin 3:0\n' \
    -e '0,/\(.*non_virtual_destructor()\) .*\(\/org\/.*\)/ s//\1 ...\2\n\n@@@ ignore begin\n/' \
    -e '/SUMMARY: AddressSanitizer: new-delete-type-mismatch/i@@@ ignore end\n' \
    -e '/SUMMARY: AddressSanitizer: new-delete-type-mismatch/a@@@ sample end\n' \
    -e '/is outside the range of representable values of type/i@@@ sample begin 3:1\n' \
    -e '/is outside the range of representable values of type/a@@@ sample end' \
    sanitizer_warnings.txt > warnings/sanitizer.txt

rm sanitizer_warnings.txt
