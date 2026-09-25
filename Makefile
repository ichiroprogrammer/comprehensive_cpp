MAKEFILE:=$(word $(words $(MAKEFILE_LIST)), $(MAKEFILE_LIST))

TARGET:=o/seminer_text.md
TITLE=C++ 中級/上級セミナー($(VERSION))

MD_SEC_NUM:=--sec_num

MD_GEN:=./md_gen/export/py

VPATH=./md:practical/md/::deep/md/::essential/md

MDS:=seminer_intro.md \
     programming_convention.md code_analysis.md \
     coding_style.md naming_practice.md \
     comment.md solid.md design_pattern.md \
     architecture.md process_and_infra.md concurrency.md template_meta_programming.md \
     dynamic_memory_allocation.md cpp_improve.md \
     core_lang_spec.md stdlib_and_concepts.md cpp_idioms.md \
     exercise_q.md exercise_a.md bibliography.md

INDEX_OPT:=--exclude $(addsuffix :1,$(MDS) sample_code.md)

include essential/make/md.mk
