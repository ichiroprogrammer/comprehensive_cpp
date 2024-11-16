SRCS:=arg.cpp model.cpp view.cpp controller.cpp \
      arg_ut.cpp model_ut.cpp view_ut.cpp controller_ut.cpp 

SRCS2:=main.cpp arg.cpp model.cpp view.cpp controller.cpp

OBJDIR:=
SHARED:=../../deep/
include $(SHARED)make/env.mk
include $(SHARED)make/example.mk
include $(SHARED)make/gtest.mk

$(EXE2_DONE) : $(EXE2)
	../ref_it/it.sh ./$< && touch $@

it : $(EXE2_DONE)

