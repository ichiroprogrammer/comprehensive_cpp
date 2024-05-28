SRCS:=\
	class.cpp operator.cpp etc.cpp syntax.cpp func.cpp type.cpp

# @@@ sample begin 0:0
 
SUPPRESS_WARN=-Wno-effc++ -Wno-unused-variable -Wno-delete-incomplete -Wno-unused-function \
              -Wno-sizeof-array-argument -Wno-unused-parameter -Wno-conversion-null \
		      -Wno-literal-conversion
# @@@ sample end

SHARED:=../../deep/
include $(SHARED)make/env.mk
include $(SHARED)make/example.mk
include $(SHARED)make/gtest.mk
