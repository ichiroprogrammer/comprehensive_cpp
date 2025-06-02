MAKEFILE:=$(word $(words $(MAKEFILE_LIST)), $(MAKEFILE_LIST))

TARGET:=o/comprehensive_cpp.md
TITLE=Comprehensive Knowledge of C++($(VERSION))

#MD_SEC_NUM:=--sec_num

MD_GEN:=./md_gen/export/py

VPATH=./md:deep/md/:deps/md

MDS:=introduction.md \
     software_practice.md programming_convention.md code_analysis.md \
     coding_style.md naming_practice.md \
     comment.md solid.md design_pattern.md \
     architecture.md process_and_infra.md concurrency.md template_meta_programming.md \
     dynamic_memory_allocation.md debug.md dev_tools.md deps.md cpp_improve.md \
     term_explanation.md exercise_q.md exercise_a.md bibliography.md afterword.md

INDEX_OPT:=--exclude $(addsuffix :1,$(MDS) sample_code.md)

include deep/make/md.mk
