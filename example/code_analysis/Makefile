# This source codes can be compiled g++9.3.0 on ubuntu20.04.

SRCS:=code_analysis.cpp

SHARED:=../../deep/
include $(SHARED)make/env.mk
include $(SHARED)make/example.mk
include $(SHARED)make/gtest.mk

.PHONY : scan-build, cppcheck
scan-build: cppcheck
	rm -f $$(find scan-build/ -type f ! -name ".gitignore")
	scan-build -o $(SCAN_BUILD_DIR) $(MAKE) O=$(SCAN_BUILD_DIR) \
		2> $(SCAN_BUILD_DIR)scan-build.txt | tee $(SCAN_BUILD_DIR)scan-build_bugs.txt
	grep "scan-build: [56] bugs found." scan-build/scan-build_bugs.txt > /dev/null;
	rm -rf scan-build/20*

#現在のコードでは、あえてバグを入れているから、エラーが3個指摘されるはずなので -eq 2
cppcheck:
	cppcheck --suppress=nullPointer:$(GTEST_DIR)/src/gtest.cc \
		     --project=compile_commands.json 2> scan-build/cppcheck_bugs.txt
	[ $$(grep error: scan-build/cppcheck_bugs.txt | wc -l) -ge 2 ]


# clang 8 on cygwin だと 5 bugs found
# clang 10 on ubuntu だと 6 bugs found

scan-build-row:
	scan-build -o $(SCAN_BUILD_DIR) $(MAKE) --always-make O=$(SCAN_BUILD_DIR)

