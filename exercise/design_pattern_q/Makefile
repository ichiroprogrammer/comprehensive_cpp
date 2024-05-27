SRCS:=\
    accessor.cpp clone.cpp copy_and_swap.cpp di.cpp enum_bitmask.cpp factory_lib.cpp factory.cpp \
    future.cpp guard.cpp immutable.cpp named_constructor_lib.cpp named_constructor.cpp \
    null_object.cpp nvi.cpp observer.cpp pimpl.cpp proxy.cpp raii.cpp singleton.cpp state.cpp \
    strategy.cpp template_method.cpp visitor.cpp crtp.cpp \

SUPPRESS_WARN=-Wno-effc++ -Wno-unused-variable -Wno-delete-incomplete -Wno-unused-function \
              -Wno-sizeof-array-argument -Wno-unused-parameter -Wno-conversion-null \
		      -Wno-literal-conversion

SHARED:=../../../shared/
include $(SHARED)make/env.mk
include $(SHARED)make/example.mk
include $(SHARED)make/gtest.mk
