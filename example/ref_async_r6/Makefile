SRCS:=arg_ut.cpp controller_ut.cpp model_ut.cpp lib_ut.cpp \
	  arg.cpp controller.cpp model.cpp view.cpp lib.cpp 

SRCS2:=main.cpp arg.cpp controller.cpp model.cpp view.cpp lib.cpp 

OBJDIR:=
SHARED:=../../essential/
include $(SHARED)make/env.mk
include $(SHARED)make/example.mk
include $(SHARED)make/gtest.mk

$(EXE2_DONE) : $(EXE2)
	../ref_it/it.sh ./$< && touch $@

it : $(EXE2_DONE)

