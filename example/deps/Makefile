OBJDIR:=
SHARED:=../../deep/
include $(SHARED)make/env.mk

EXES_UT:=$(addprefix $(O),lib_ut app_ut file_utils_ut dependency_ut logging_ut)
EXES_UT_DONE:=$(addsuffix .done,$(EXES_UT))
EXE_IT:=$(O)deps
EXE_IT_DONE:=$(addsuffix .done,$(EXE_IT))

WARN_ERROR:=-Werror
WARN:=-Wall -Wextra -Weffc++
UT_COMP_OPT:=-g -D_GLIBCXX_USE_CXX11_ABI=0

CCFLAGS:=-std=c++20 $(WARN) $(WARN_ERROR) $(UT_COMP_OPT) -I$(SHARED)h -I../h

#
FILE_UTILS_SRCS:=$(addprefix file_utils/src/,path_utils.cpp load_store_row.cpp)
FILE_UTILS_OBJS:=$(addprefix $(O),$(FILE_UTILS_SRCS:.cpp=.o))
FILE_UTILS_A:=$(O)file_utils.a

FILE_UTILS_UT_SRCS:=$(addprefix file_utils/ut/,path_utils_ut.cpp load_store_row_ut.cpp)
FILE_UTILS_UT_OBJS:=$(addprefix $(O),$(FILE_UTILS_UT_SRCS:.cpp=.o))

LIB_UT_SRCS:=lib/ut/nstd_ut.cpp
LIB_UT_OBJS:=$(addprefix $(O),$(LIB_UT_SRCS:.cpp=.o))

DEPENDENCY_SRCS:= cpp_src.cpp cpp_dir.cpp cpp_deps.cpp deps_scenario.cpp arch_pkg.cpp \
	       	      load_store_format.cpp
DEPENDENCY_SRCS:=$(addprefix dependency/src/,$(DEPENDENCY_SRCS))
DEPENDENCY_OBJS:=$(addprefix $(O),$(DEPENDENCY_SRCS:.cpp=.o))
DEPENDENCY_A:=$(O)dependency.a

DEPENDENCY_UT_SRCS:=cpp_src_ut.cpp cpp_dir_ut.cpp cpp_deps_ut.cpp \
                    deps_scenario_ut.cpp arch_pkg_ut.cpp load_store_format_ut.cpp
DEPENDENCY_UT_SRCS:=$(addprefix dependency/ut/,$(DEPENDENCY_UT_SRCS))
DEPENDENCY_UT_OBJS:=$(addprefix $(O),$(DEPENDENCY_UT_SRCS:.cpp=.o))

LOGGER_SRCS:=logging/src/logger.cpp
LOGGER_OBJS:=$(addprefix $(O),$(LOGGER_SRCS:.cpp=.o))
LOGGER_A:=$(O)logging.a

LOGGER_UT_SRCS:=logging/ut/logger_ut.cpp
LOGGER_UT_OBJS:=$(addprefix $(O),$(LOGGER_UT_SRCS:.cpp=.o))

MAIN_SRCS:=app/src/main.cpp
MAIN_OBJS:=$(addprefix $(O),$(MAIN_SRCS:.cpp=.o))

APP_SRCS:=app/src/deps_opts.cpp 
APP_OBJS:=$(addprefix $(O),$(APP_SRCS:.cpp=.o))
APP_A:=$(O)app.a

APP_UT_SRCS:=app/ut/deps_opts_ut.cpp 
APP_UT_OBJS:=$(addprefix $(O),$(APP_UT_SRCS:.cpp=.o))

SRCS:=$(FILE_UTILS_SRCS)  $(FILE_UTILS_UT_SRCS) $(LIB_UT_SRCS) \
	  $(DEPENDENCY_SRCS) $(DEPENDENCY_UT_SRCS) \
	  $(LOGGER_SRCS) $(LOGGER_UT_SRCS) \
	  $(MAIN_SRCS) $(APP_SRCS) $(APP_UT_SRCS)

DPDS:=$(addprefix $(D),$(SRCS:.cpp=.d))

NOT_NEED_D:=$(patsubst clean%,true, $(MAKECMDGOALS))
ifeq ($(MAKECMDGOALS), clang)
NOT_NEED_D=true
endif
ifeq ($(MAKECMDGOALS), help)
NOT_NEED_D=true
endif

.PHONY : all
all: $(EXE_IT) $(EXES_UT)

ifneq ($(NOT_NEED_D), true)
-include $(DPDS)
endif

INC_UT=-Iut -I$(GTEST_INC) 

### lib 
$(O)lib/ut/%.o : lib/ut/%.cpp
	$(CXX) -Ilib/h $(INC_UT) $(SANITIZER_OPT) $(CCFLAGS) -c -o $@ $<

$(O)lib_ut : $(LIB_UT_OBJS) $(GTEST_LIB)
	$(CXX) -o $@ $^ -lpthread  -lstdc++fs $(SANITIZER_OPT) 

# @@@ sample begin 0:0
### logging
INC_LOGGER=-Ilib/h -Ilogging/h  # インクルードパスの指定

# 指定されたインクルードパスを使用したコンパイル
$(O)logging/src/%.o : logging/src/%.cpp
	$(CXX) $(INC_LOGGER) $(SANITIZER_OPT) $(CCFLAGS) -c -o $@ $<

# 指定されたインクルードパスを使用したUTのコンパイル
$(O)logging/ut/%.o : logging/ut/%.cpp
	$(CXX) $(INC_UT) $(INC_LOGGER) $(SANITIZER_OPT) $(CCFLAGS) -c -o $@ $<

# ライブラリの生成
$(LOGGER_A) : $(LOGGER_OBJS)
	ar cr $@ $^

# UT実行バイナリの生成
$(O)logging_ut : $(LOGGER_UT_OBJS) $(FILE_UTILS_A) $(LOGGER_A) $(DEPENDENCY_A) $(GTEST_LIB)
	$(CXX) -o $@ $^ -lpthread  -lstdc++fs $(SANITIZER_OPT) 

### file_utils
INC_FILE_UTILS:=-Ilib/h -Ilogging/h -Ifile_utils/h  # インクルードパスの指定

# 指定されたインクルードパスを使用したコンパイル
$(O)file_utils/src/%.o : file_utils/src/%.cpp
	$(CXX) $(INC_FILE_UTILS) $(SANITIZER_OPT) $(CCFLAGS) -c -o $@ $<

# 指定されたインクルードパスを使用したUTのコンパイル
$(O)file_utils/ut/%.o : file_utils/ut/%.cpp
	$(CXX) $(INC_UT) $(INC_FILE_UTILS) $(SANITIZER_OPT) $(CCFLAGS) -c -o $@ $<

# ライブラリの生成
$(FILE_UTILS_A) : $(FILE_UTILS_OBJS)
	ar cr $@ $^

# UT実行バイナリの生成
$(O)file_utils_ut : $(FILE_UTILS_UT_OBJS) $(FILE_UTILS_A) $(LOGGER_A) $(GTEST_LIB)
	$(CXX) -o $@ $^ -lpthread -lstdc++fs $(SANITIZER_OPT) 
# @@@ sample end

### dependency
INC_DEPENDENCY:=-Ilib/h -Ifile_utils/h -Idependency/h
$(O)dependency/src/%.o : dependency/src/%.cpp
	$(CXX) $(INC_DEPENDENCY) $(SANITIZER_OPT) $(CCFLAGS) -c -o $@ $<

$(O)dependency/ut/%.o : dependency/ut/%.cpp
	$(CXX) $(INC_UT) $(INC_DEPENDENCY) -Idependency/src $(SANITIZER_OPT) $(CCFLAGS) -c -o $@ $<

$(DEPENDENCY_A) : $(DEPENDENCY_OBJS)
	ar cr $@ $^

$(O)dependency_ut : $(DEPENDENCY_UT_OBJS) $(FILE_UTILS_A) $(DEPENDENCY_A) $(GTEST_LIB)
	$(CXX) -o $@ $^ -lpthread  -lstdc++fs $(SANITIZER_OPT) 

### app
INC_APP:=-Ilib/h -Ilogging/h -Ifile_utils/h -Idependency/h
$(O)app/src/%.o : app/src/%.cpp
	$(CXX) $(INC_APP) $(SANITIZER_OPT) $(CCFLAGS) -c -o $@ $<

$(O)app/ut/%.o : app/ut/%.cpp
	$(CXX) $(INC_UT) $(INC_APP) -Iapp/src $(SANITIZER_OPT) $(CCFLAGS) -c -o $@ $<

$(APP_A) : $(APP_OBJS)
	ar cr $@ $^

$(O)app_ut : $(APP_UT_OBJS) $(APP_A) $(FILE_UTILS_A) $(DEPENDENCY_A) $(GTEST_LIB)
	$(CXX) -o $@ $^ -lpthread  -lstdc++fs $(SANITIZER_OPT) 

### deps
$(O)deps: $(MAIN_OBJS) $(APP_A) $(FILE_UTILS_A) $(DEPENDENCY_A) $(LOGGER_A)
	$(CXX) -o $@ $^ -lpthread  -lstdc++fs $(SANITIZER_OPT) 

### *.d
INC_D:=$(addprefix -I,lib/h logging/h file_utils/h dependency/h) \
	   $(addprefix -I,$(addsuffix /src,app logging file_utils dependency)) \
	   -I$(SHARED)h -I../h
$(D)%.d : %.cpp
	$(CXX) $(INC_UT) $(INC_D) -E -MM -w $< | sed -e 's@^\([^ ]\)@$$(O)$(dir $<)\1@g' > $@

include $(SHARED)make/gtest.mk

$(O)%.done : $(O)%
	./$< $(UT_OPT) && touch $@

$(EXE_IT_DONE) : $(EXE_IT)
	./it.sh -a $< $(IT_OPT) && touch $@

.PHONY : ut it
# @@@ sample begin 1:0

ut: $(EXES_UT_DONE)  # 単体テスト用ターゲット

it: $(EXE_IT_DONE)  # 統合テスト用ターゲット

SANITIZER_DIR=sanitizer/
.PHONY : sanitizer
san:  # g++ sanitizerビルド
	$(MAKE) O=$(SANITIZER_DIR) \
		SANITIZER_OPT="-fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow"

san-ut: sanitizer  # g++ sanitizerバイナリでの単体テスト
	make O=$(SANITIZER_DIR) ut

san-it: sanitizer  # g++ sanitizerバイナリでの統合テスト
	make O=$(SANITIZER_DIR) it
# @@@ sample end

SCAN_BUILD_DIR=scan-build/
.PHONY : scan-build
scan-build: $(SCAN_BUILD_DIR)/scan-build.txt

$(SCAN_BUILD_DIR)/scan-build.txt : $(EXE_IT) $(EXES_UT)
	scan-build -o $(SCAN_BUILD_DIR) make O=$(SCAN_BUILD_DIR) \
		| tee $(SCAN_BUILD_DIR)/scan-build.txt
	grep "scan-build: No bugs found." $(SCAN_BUILD_DIR)/scan-build.txt > /dev/null \
		|| (rm $(SCAN_BUILD_DIR)/scan-build.txt; exit 1)

.PHONY : format complete
format:
	clang-format -i $$(find -name "*.cpp" -o -name "*.h")

complete : 
	bear -- $(MAKE) --always-make
	sed -i -e "s@$$(pwd)@.@" compile_commands.json # 絶対パスの変換

CLANG_DIR=clang++/
.PHONY : clang
clang:
	$(MAKE) CXX=clang++

clang-ut:
	$(MAKE) CXX=clang++ ut

help:
	@echo "make [target]"
	@echo "  all             : all target are built."
	@echo "  ut [UT_OPT=...] : all ut are executed."
	@echo "  clean           : delete files created on build."
	@echo "  format          : format *.cpp *.h by clang-formatter."
	@echo "  clang           : build by clang."
	@echo "  clang-ut        : all ut built by clang are executed."
	@echo "  sanitizer       : build with sanitizeer."
	@echo "  san-ut          : all ut built with sanitizer are executed."
	@echo "  san-it          : it built with sanitizer are executed."
	@echo "  scan-build      : static analysis by scan-build."
	@echo "  complete        : make compile_commands.json to complete by clang"

CLEAN_DIRS=d/ g++/ clang++/ sanitizer/ scan-build/
clean:
	rm -f $$(find $(CLEAN_DIRS) -type f ! -name ".gitignore")

clean_gtest:
	rm -f $$(find $(addprefix ../gtest/,$(CLEAN_DIRS)) -type f ! -name ".gitignore")

