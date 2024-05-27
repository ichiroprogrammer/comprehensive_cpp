#pragma once

#if (!defined(SUPPRESS_WARN_OFF)) && (!defined(__clang__)) && defined(__GNUC__)

#define SUPPRESS_WARN_GCC_BEGIN _Pragma("GCC diagnostic push")
#define SUPPRESS_WARN_GCC_END _Pragma("GCC diagnostic pop")

#define SUPPRESS_WARN_GCC_ARRAY_BOUNDS _Pragma("GCC diagnostic ignored \"-Warray-bounds\"")
#define SUPPRESS_WARN_GCC_ADDRESS _Pragma("GCC diagnostic ignored \"-Waddress\"")
#define SUPPRESS_WARN_GCC_COMMENT _Pragma("GCC diagnostic ignored \"-Wcomment\"")
#define SUPPRESS_WARN_GCC_CONV_NULL _Pragma("GCC diagnostic ignored \"-Wconversion-null\"")
#define SUPPRESS_WARN_GCC_DEL_INCOMP _Pragma("GCC diagnostic ignored \"-Wdelete-incomplete\"")
#define SUPPRESS_WARN_GCC_EMPTY_BODY _Pragma("GCC diagnostic ignored \"-Wempty-body\"")
#define SUPPRESS_WARN_GCC_DEPRECATED_COPY _Pragma("GCC diagnostic ignored \"-Wdeprecated-copy\"")
#define SUPPRESS_WARN_GCC_DEPRECATED_DECL \
    _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"");
#define SUPPRESS_WARN_GCC_FORMAT_SEC _Pragma("GCC diagnostic ignored \"-Wformat-security\"")
#define SUPPRESS_WARN_GCC_IGNORE_QUAL _Pragma("GCC diagnostic ignored \"-Wignored-qualifiers\"")
#define SUPPRESS_WARN_GCC_IMPLICIT_INT _Pragma("GCC diagnostic ignored \"-Wimplicit-int\"")
#define SUPPRESS_WARN_GCC_MISLEADING_INDENT \
    _Pragma("GCC diagnostic ignored \"-Wmisleading-indentation\"")
#define SUPPRESS_WARN_GCC_INIT_OVERRIDE _Pragma("GCC diagnostic ignored \"-Woverride-init\"");
#define SUPPRESS_WARN_GCC_MISSING_BRACES _Pragma("GCC diagnostic ignored \"-Wmissing-braces\"")
#define SUPPRESS_WARN_GCC_NON_VIRTUAL_DTOR _Pragma("GCC diagnostic ignored \"-Wnon-virtual-dtor\"")
#define SUPPRESS_WARN_GCC_PARENTHESES _Pragma("GCC diagnostic ignored \"-Wparentheses\"")
#define SUPPRESS_WARN_GCC_PESSIMIZING_MOVE _Pragma("GCC diagnostic ignored \"-Wpessimizing-move\"")
#define SUPPRESS_WARN_GCC_SHIFT_COUNT_OVERFLOW \
    _Pragma("GCC diagnostic ignored \"-Wshift-count-overflow\"")
#define SUPPRESS_WARN_GCC_SIGN_COMPARE _Pragma("GCC diagnostic ignored \"-Wsign-compare\"")
#define SUPPRESS_WARN_GCC_SIZEOF_ARRAY_ARG \
    _Pragma("GCC diagnostic ignored \"-Wsizeof-array-argument\"")
#define SUPPRESS_WARN_GCC_SIZEOF_POINTER_DIV \
    _Pragma("GCC diagnostic ignored \"-Wsizeof-pointer-div\"")
#define SUPPRESS_WARN_GCC_UNINIT _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")
#define SUPPRESS_WARN_GCC_UNUSED_FUNC _Pragma("GCC diagnostic ignored \"-Wunused-function\"")
#define SUPPRESS_WARN_GCC_UNUSED_LOCAL_TYPEDEF \
    _Pragma("GCC diagnostic ignored \"-Wunused-local-typedefs\"")
#define SUPPRESS_WARN_GCC_UNUSED_LABEL _Pragma("GCC diagnostic ignored \"-Wunused-label\"")
#define SUPPRESS_WARN_GCC_UNUSED_PARAM _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
#define SUPPRESS_WARN_GCC_UNUSED_RESULT _Pragma("GCC diagnostic ignored \"-Wunused-result\"")
#define SUPPRESS_WARN_GCC_UNUSED_VAL _Pragma("GCC diagnostic ignored \"-Wunused-value\"")
#define SUPPRESS_WARN_GCC_UNUSED_VAR _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")
#define SUPPRESS_WARN_GCC_USER_DEFINED_LITERAL \
    _Pragma("GCC diagnostic ignored \"-Wliteral-suffix\"")
#define SUPPRESS_WARN_GCC_SWITCH _Pragma("GCC diagnostic ignored \"-Wswitch\"")
#define SUPPRESS_WARN_GCC_CONVERSION_VEXING_PARSE \
    _Pragma("GCC diagnostic ignored \"-Wvexing-parse\"")
#define SUPPRESS_WARN_GCC_ENUM_COMP_SWITCH \
    _Pragma("GCC diagnostic ignored \"-Wenum-compare-switch\"")
#define SUPPRESS_WARN_GCC_COMP _Pragma("GCC diagnostic ignored \"-Wenum-compare\"")

// only gcc
#define SUPPRESS_WARN_GCC_DANGLING_ELSE _Pragma("GCC diagnostic ignored \"-Wdangling-else\"");
#define SUPPRESS_WARN_GCC_FORMAT_EQ _Pragma("GCC diagnostic ignored \"-Wformat=\"")
#define SUPPRESS_WARN_GCC_CAST_FUNC_TYPE _Pragma("GCC diagnostic ignored \"-Wcast-function-type\"")
#define SUPPRESS_WARN_GCC_CATCH_ASSIGN _Pragma("GCC diagnostic ignored \"-Wcatch-value=\"")
#define SUPPRESS_WARN_GCC_CLASS_MEMACCESS _Pragma("GCC diagnostic ignored \"-Wclass-memaccess\"")
#define SUPPRESS_WARN_GCC_DEPRECATED _Pragma("GCC diagnostic ignored \"-Wdeprecated\"")
#define SUPPRESS_WARN_GCC_INACCESSIBLE_BASE \
    _Pragma("GCC diagnostic ignored \"-Winaccessible-base\"")
#define SUPPRESS_WARN_GCC_ENUM_COMP _Pragma("GCC diagnostic ignored \"-Wenum-compare\"")
#define SUPPRESS_WARN_GCC_TYPE_LIMITS _Pragma("GCC diagnostic ignored \"-Wtype-limits\"")
#define SUPPRESS_WARN_GCC_FALLTHROUGH _Pragma("GCC diagnostic ignored \"-Wimplicit-fallthrough\"")
#define SUPPRESS_WARN_GCC_INACCESS_BASE _Pragma("GCC diagnostic ignored \"-Winaccessible-base\"")
#define SUPPRESS_WARN_GCC_LOCAL_RETURN _Pragma("GCC diagnostic ignored \"-Wreturn-local-addr\"")
#define SUPPRESS_WARN_GCC_NON_NULL_COMP _Pragma("GCC diagnostic ignored \"-Wnonnull-compare\"")
#define SUPPRESS_WARN_GCC_NOT_EFF_CPP _Pragma("GCC diagnostic ignored \"-Weffc++\"")
#define SUPPRESS_WARN_GCC_OVERFLOW _Pragma("GCC diagnostic ignored \"-Woverflow\"")
#define SUPPRESS_WARN_GCC_REORDER _Pragma("GCC diagnostic ignored \"-Wreorder\"")
#define SUPPRESS_WARN_GCC_RETURN_TYPE _Pragma("GCC diagnostic ignored \"-Wreturn-type\"")
#define SUPPRESS_WARN_GCC_SEQ_POINT _Pragma("GCC diagnostic ignored \"-Wsequence-point\"")
#define SUPPRESS_WARN_GCC_STRING_OVERFLOW _Pragma("GCC diagnostic ignored \"-Wstringop-overflow=\"")
#define SUPPRESS_WARN_GCC_TERMINATE _Pragma("GCC diagnostic ignored \"-Wterminate\"");

#else

#define SUPPRESS_WARN_GCC_BEGIN
#define SUPPRESS_WARN_GCC_END

#define SUPPRESS_WARN_GCC_ADDRESS
#define SUPPRESS_WARN_GCC_ARRAY_BOUNDS
#define SUPPRESS_WARN_GCC_COMMENT
#define SUPPRESS_WARN_GCC_CONV_NULL
#define SUPPRESS_WARN_GCC_DEL_INCOMP
#define SUPPRESS_WARN_GCC_EMPTY_BODY
#define SUPPRESS_WARN_GCC_DEPRECATED_COPY
#define SUPPRESS_WARN_GCC_DEPRECATED_DECL
#define SUPPRESS_WARN_GCC_FORMAT_SEC
#define SUPPRESS_WARN_GCC_IGNORE_QUAL
#define SUPPRESS_WARN_GCC_IMPLICIT_INT
#define SUPPRESS_WARN_GCC_MISLEADING_INDENT
#define SUPPRESS_WARN_GCC_INIT_OVERRIDE
#define SUPPRESS_WARN_GCC_MISSING_BRACES
#define SUPPRESS_WARN_GCC_NON_VIRTUAL_DTOR
#define SUPPRESS_WARN_GCC_PARENTHESES
#define SUPPRESS_WARN_GCC_PESSIMIZING_MOVE
#define SUPPRESS_WARN_GCC_SHIFT_COUNT_OVERFLOW
#define SUPPRESS_WARN_GCC_SIGN_COMPARE
#define SUPPRESS_WARN_GCC_SIZEOF_ARRAY_ARG
#define SUPPRESS_WARN_GCC_SIZEOF_POINTER_DIV
#define SUPPRESS_WARN_GCC_UNINIT
#define SUPPRESS_WARN_GCC_UNUSED_FUNC
#define SUPPRESS_WARN_GCC_UNUSED_LOCAL_TYPEDEF
#define SUPPRESS_WARN_GCC_UNUSED_LABEL
#define SUPPRESS_WARN_GCC_UNUSED_PARAM
#define SUPPRESS_WARN_GCC_UNUSED_RESULT
#define SUPPRESS_WARN_GCC_UNUSED_VAL
#define SUPPRESS_WARN_GCC_UNUSED_VAR
#define SUPPRESS_WARN_GCC_USER_DEFINED_LITERAL
#define SUPPRESS_WARN_GCC_CONVERSION_VEXING_PARSE
#define SUPPRESS_WARN_GCC_ENUM_COMP_SWITCH
#define SUPPRESS_WARN_GCC_COMP

// only gcc
#define SUPPRESS_WARN_GCC_DANGLING_ELSE
#define SUPPRESS_WARN_GCC_FORMAT_EQ
#define SUPPRESS_WARN_GCC_CAST_FUNC_TYPE
#define SUPPRESS_WARN_GCC_CATCH_ASSIGN
#define SUPPRESS_WARN_GCC_CLASS_MEMACCESS
#define SUPPRESS_WARN_GCC_DEPRECATED
#define SUPPRESS_WARN_GCC_INACCESSIBLE_BASE
#define SUPPRESS_WARN_GCC_ENUM_COMP
#define SUPPRESS_WARN_GCC_FALLTHROUGH
#define SUPPRESS_WARN_GCC_INACCESS_BASE
#define SUPPRESS_WARN_GCC_TYPE_LIMITS
#define SUPPRESS_WARN_GCC_LOCAL_RETURN
#define SUPPRESS_WARN_GCC_NON_NULL_COMP
#define SUPPRESS_WARN_GCC_NOT_EFF_CPP
#define SUPPRESS_WARN_GCC_OVERFLOW
#define SUPPRESS_WARN_GCC_REORDER
#define SUPPRESS_WARN_GCC_RETURN_TYPE
#define SUPPRESS_WARN_GCC_SEQ_POINT
#define SUPPRESS_WARN_GCC_STRING_OVERFLOW
#define SUPPRESS_WARN_GCC_SWITCH
#define SUPPRESS_WARN_GCC_TERMINATE

#endif
