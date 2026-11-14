MAKEFILE:=$(word $(words $(MAKEFILE_LIST)), $(MAKEFILE_LIST))

TARGET:=o/seminer_text.md
TITLE=C++ 中級/上級セミナー($(VERSION))

MD_SEC_NUM:=--sec_num

MD_GEN:=./md_gen/export/py

VPATH=./md:practical/md/::deep/md/::essential/md

MDS:=seminer_intro.md \
     programming_convention.md coding_style.md naming_practice.md comment.md cpp_improve.md \
     architecture.md class_design.md design_pattern.md \
     process_and_infra.md refactring_expamples.md concurrency.md template_meta_programming.md \
     dynamic_memory_allocation.md \
     core_lang_spec.md stdlib_and_concepts.md glossary.md \
     exercise_q.md exercise_a.md code_analysis.md bibliography.md

# mainをマージすると以下が削除されるかもしれない
# exercise_q.md exercise_a.md \		

INDEX_OPT:=--exclude $(addsuffix :1,$(MDS) sample_code.md)

include essential/make/md.mk
