#pragma once

#if (!defined(SUPPRESS_WARN_OFF)) && defined(__clang__)

#define SUPPRESS_WARN_CLANG_BEGIN _Pragma("clang diagnostic push")
#define SUPPRESS_WARN_CLANG_END _Pragma("clang diagnostic pop")

#define SUPPRESS_WARN_CLANG_ARRAY_BOUNDS _Pragma("clang diagnostic ignored \"-Warray-bounds\"")
#define SUPPRESS_WARN_CLANG_ADDRESS \
    _Pragma("clang diagnostic ignored \"-Wtautological-pointer-compare\"")
#define SUPPRESS_WARN_CLANG_COMMENT _Pragma("clang diagnostic ignored \"-Wcomment\"")
#define SUPPRESS_WARN_CLANG_CONV_NULL _Pragma("clang diagnostic ignored \"-Wconversion-null\"")
#define SUPPRESS_WARN_CLANG_DEL_INCOMP _Pragma("clang diagnostic ignored \"-Wdelete-incomplete\"")
#define SUPPRESS_WARN_CLANG_EMPTY_BODY _Pragma("clang diagnostic ignored \"-Wempty-body\"")
#define SUPPRESS_WARN_CLANG_FORMAT_SEC _Pragma("clang diagnostic ignored \"-Wformat-security\"")
#define SUPPRESS_WARN_CLANG_IGNORE_QUAL _Pragma("clang diagnostic ignored \"-Wignored-qualifiers\"")
#define SUPPRESS_WARN_CLANG_MISLEADING_INDENT \
    _Pragma("clang diagnostic ignored \"-Wmisleading-indentation\"")
#define SUPPRESS_WARN_CLANG_DEPRECATED_COPY \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-copy\"")
#define SUPPRESS_WARN_CLANG_DEPRECATED_DECL \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#define SUPPRESS_WARN_CLANG_IMPLICIT_INT _Pragma("clang diagnostic ignored \"-Wimplicit-int\"")
#define SUPPRESS_WARN_CLANG_IMPLICIT_CONST_FLOAT \
    _Pragma("clang diagnostic ignored \"-Wimplicit-const-int-float-conversion\"")
#define SUPPRESS_WARN_CLANG_INIT_OVERRIDE \
    _Pragma("clang diagnostic ignored \"-Winitializer-overrides\"")
#define SUPPRESS_WARN_CLANG_MISSING_BRACES _Pragma("clang diagnostic ignored \"-Wmissing-braces\"")
#define SUPPRESS_WARN_CLANG_NON_VIRTUAL_DTOR \
    _Pragma("clang diagnostic ignored \"-Wnon-virtual-dtor\"")
#define SUPPRESS_WARN_CLANG_PARENTHESES _Pragma("clang diagnostic ignored \"-Wparentheses\"")
#define SUPPRESS_WARN_CLANG_PESSIMIZING_MOVE \
    _Pragma("clang diagnostic ignored \"-Wpessimizing-move\"")
#define SUPPRESS_WARN_CLANG_SHIFT_COUNT_OVERFLOW \
    _Pragma("clang diagnostic ignored \"-Wshift-count-overflow\"")
#define SUPPRESS_WARN_CLANG_SIGN_COMPARE _Pragma("clang diagnostic ignored \"-Wsign-compare\"")
#define SUPPRESS_WARN_CLANG_SIZEOF_ARRAY_ARG \
    _Pragma("clang diagnostic ignored \"-Wsizeof-array-argument\"")
#define SUPPRESS_WARN_CLANG_SIZEOF_POINTER_DIV \
    _Pragma("clang diagnostic ignored \"-Wsizeof-pointer-div\"")
#define SUPPRESS_WARN_CLANG_UNINIT _Pragma("clang diagnostic ignored \"-Wuninitialized\"")
#define SUPPRESS_WARN_CLANG_UNUSED_FUNC _Pragma("clang diagnostic ignored \"-Wunused-function\"")
#define SUPPRESS_WARN_CLANG_UNUSED_LOCAL_TYPEDEF \
    _Pragma("clang diagnostic ignored \"-Wunused-local-typedefs\"")
#define SUPPRESS_WARN_CLANG_UNUSED_LABEL _Pragma("clang diagnostic ignored \"-Wunused-label\"")
#define SUPPRESS_WARN_CLANG_UNUSED_PARAM _Pragma("clang diagnostic ignored \"-Wunused-parameter\"")
#define SUPPRESS_WARN_CLANG_UNUSED_RESULT _Pragma("clang diagnostic ignored \"-Wunused-result\"")
#define SUPPRESS_WARN_CLANG_UNUSED_VAR _Pragma("clang diagnostic ignored \"-Wunused-variable\"")
#define SUPPRESS_WARN_CLANG_UNUSED_VAL _Pragma("clang diagnostic ignored \"-Wunused-value\"")
#define SUPPRESS_WARN_CLANG_USER_DEFINED_LITERAL \
    _Pragma("clang diagnostic ignored \"-Wuser-defined-literals\"")
#define SUPPRESS_WARN_CLANG_SWITCH _Pragma("clang diagnostic ignored \"-Wswitch\"")
#define SUPPRESS_WARN_CLANG_CONVERSION_VEXING_PARSE \
    _Pragma("clang diagnostic ignored \"-Wvexing-parse\"")

#define SUPPRESS_WARN_CLANG_COMP _Pragma("clang diagnostic ignored \"-Wenum-compare\"")
#define SUPPRESS_WARN_CLANG_ENUM_COMP_SWITCH \
    _Pragma("clang diagnostic ignored \"-Wenum-compare-switch\"")
// only clang
#define SUPPRESS_WARN_CLANG_CONST_CONV _Pragma("clang diagnostic ignored \"-Wconstant-conversion\"")
#define SUPPRESS_WARN_CLANG_DANGLING_GSL _Pragma("clang diagnostic ignored \"-Wdangling-gsl\"")
#define SUPPRESS_WARN_CLANG_DEPRECATED_INCREMENT_BOOL \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-increment-bool\"")
#define SUPPRESS_WARN_CLANG_EXCEPTIONS _Pragma("clang diagnostic ignored \"-Wexceptions\"")
#define SUPPRESS_WARN_CLANG_INCONSISTENT_MISSING_OVERRIDE \
    _Pragma("clang diagnostic ignored \"-Winconsistent-missing-override\"")
#define SUPPRESS_WARN_CLANG_LITERAL_CONVERSION \
    _Pragma("clang diagnostic ignored \"-Wliteral-conversion\"")
#define SUPPRESS_WARN_CLANG_LOGICAL_OP_PARENTHESES \
    _Pragma("clang diagnostic ignored \"-Wlogical-op-parentheses\"")
#define SUPPRESS_WARN_CLANG_MISMATCHED_NEW_DELETE \
    _Pragma("clang diagnostic ignored \"-Wmismatched-new-delete\"")
#define SUPPRESS_WARN_CLANG_NON_POD_VARARGS \
    _Pragma("clang diagnostic ignored \"-Wnon-pod-varargs\"")
#define SUPPRESS_WARN_CLANG_OVERLOADED_VIRTUAL \
    _Pragma("clang diagnostic ignored \"-Woverloaded-virtual\"")
#define SUPPRESS_WARN_CLANG_POINTER_BOOL_CONVERSION \
    _Pragma("clang diagnostic ignored \"-Wpointer-bool-conversion\"")
#define SUPPRESS_WARN_CLANG_POTENTIALLY_EVALUATED_EXPRESSION \
    _Pragma("clang diagnostic ignored \"-Wpotentially-evaluated-expression\"")
#define SUPPRESS_WARN_CLANG_REINTERPRET_BASE_CLASS \
    _Pragma("clang diagnostic ignored \"-Wreinterpret-base-class\"")
#define SUPPRESS_WARN_CLANG_REORDER_CTOR _Pragma("clang diagnostic ignored \"-Wreorder-ctor\"")
#define SUPPRESS_WARN_CLANG_RESERVED_USER_DEFINED_LITERAL \
    _Pragma("clang diagnostic ignored \"-Wreserved-user-defined-literal\"")
#define SUPPRESS_WARN_CLANG_RETURN_STACK_ADDRESS \
    _Pragma("clang diagnostic ignored \"-Wreturn-stack-address\"")
#define SUPPRESS_WARN_CLANG_RETURN_TYPE _Pragma("clang diagnostic ignored \"-Wreturn-type\"")
#define SUPPRESS_WARN_CLANG_SELF_ASSIGN_OVERLOADED \
    _Pragma("clang diagnostic ignored \"-Wself-assign-overloaded\"")
#define SUPPRESS_WARN_CLANG_SELF_MOVE _Pragma("clang diagnostic ignored \"-Wself-move\"")
#define SUPPRESS_WARN_CLANG_UNDEFINED_INTERNAL \
    _Pragma("clang diagnostic ignored \"-Wundefined-internal\"")
#define SUPPRESS_WARN_CLANG_UNDEF_COMP \
    _Pragma("clang diagnostic ignored \"-Wtautological-undefined-compare\"")
#define SUPPRESS_WARN_CLANG_OVERLAP_COMP \
    _Pragma("clang diagnostic ignored \"-Wtautological-overlap-compare\"")

#define SUPPRESS_WARN_CLANG_UNEVALUATED_EXPRESSION \
    _Pragma("clang diagnostic ignored \"-Wunevaluated-expression\"")
#define SUPPRESS_WARN_CLANG_UNKNOWN_ESCAPE_SEQUENCE
_Pragma("clang diagnostic ignored \"-Wunknown-escape-sequence\"")
#define SUPPRESS_WARN_CLANG_UNSEQUENCED _Pragma("clang diagnostic ignored \"-Wunsequenced\"")
#define SUPPRESS_WARN_CLANG_UNUSED_CONST_VAR \
    _Pragma("clang diagnostic ignored \"-Wunused-const-variable\"")
#define SUPPRESS_WARN_CLANG_UNUSED_INTERNAL_DECL \
    _Pragma("clang diagnostic ignored \"-Wunneeded-internal-declaration\"")
#define SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD \
    _Pragma("clang diagnostic ignored \"-Wunused-private-field\"")

#else

#define SUPPRESS_WARN_CLANG_BEGIN
#define SUPPRESS_WARN_CLANG_END

#define SUPPRESS_WARN_CLANG_ADDRESS
#define SUPPRESS_WARN_CLANG_ARRAY_BOUNDS
#define SUPPRESS_WARN_CLANG_COMP
#define SUPPRESS_WARN_CLANG_ENUM_COMP_SWITCH
#define SUPPRESS_WARN_CLANG_COMMENT
#define SUPPRESS_WARN_CLANG_CONV_NULL
#define SUPPRESS_WARN_CLANG_DEL_INCOMP
#define SUPPRESS_WARN_CLANG_EMPTY_BODY
#define SUPPRESS_WARN_CLANG_FORMAT_SEC
#define SUPPRESS_WARN_CLANG_IGNORE_QUAL
#define SUPPRESS_WARN_CLANG_MISLEADING_INDENT
#define SUPPRESS_WARN_CLANG_DEPRECATED_COPY
#define SUPPRESS_WARN_CLANG_DEPRECATED_DECL
#define SUPPRESS_WARN_CLANG_IMPLICIT_INT
#define SUPPRESS_WARN_CLANG_IMPLICIT_CONST_FLOAT
#define SUPPRESS_WARN_CLANG_INIT_OVERRIDE
#define SUPPRESS_WARN_CLANG_MISSING_BRACES
#define SUPPRESS_WARN_CLANG_NON_VIRTUAL_DTOR
#define SUPPRESS_WARN_CLANG_PARENTHESES
#define SUPPRESS_WARN_CLANG_PESSIMIZING_MOVE
#define SUPPRESS_WARN_CLANG_SHIFT_COUNT_OVERFLOW
#define SUPPRESS_WARN_CLANG_SIGN_COMPARE
#define SUPPRESS_WARN_CLANG_SIZEOF_ARRAY_ARG
#define SUPPRESS_WARN_CLANG_SIZEOF_POINTER_DIV
#define SUPPRESS_WARN_CLANG_UNINIT
#define SUPPRESS_WARN_CLANG_UNUSED_FUNC
#define SUPPRESS_WARN_CLANG_UNUSED_LOCAL_TYPEDEF
#define SUPPRESS_WARN_CLANG_UNUSED_LABEL
#define SUPPRESS_WARN_CLANG_UNUSED_PARAM
#define SUPPRESS_WARN_CLANG_UNUSED_RESULT
#define SUPPRESS_WARN_CLANG_UNUSED_VAL
#define SUPPRESS_WARN_CLANG_UNUSED_VAR
#define SUPPRESS_WARN_CLANG_USER_DEFINED_LITERAL
#define SUPPRESS_WARN_CLANG_SWITCH

// only clang
#define SUPPRESS_WARN_CLANG_CONVERSION_VEXING_PARSE
#define SUPPRESS_WARN_CLANG_CONST_CONV
#define SUPPRESS_WARN_CLANG_DANGLING_GSL
#define SUPPRESS_WARN_CLANG_DEPRECATED_INCREMENT_BOOL
#define SUPPRESS_WARN_CLANG_EXCEPTIONS
#define SUPPRESS_WARN_CLANG_INCONSISTENT_MISSING_OVERRIDE
#define SUPPRESS_WARN_CLANG_LITERAL_CONVERSION
#define SUPPRESS_WARN_CLANG_LOGICAL_OP_PARENTHESES
#define SUPPRESS_WARN_CLANG_MISMATCHED_NEW_DELETE
#define SUPPRESS_WARN_CLANG_NON_POD_VARARGS
#define SUPPRESS_WARN_CLANG_OVERLOADED_VIRTUAL
#define SUPPRESS_WARN_CLANG_POINTER_BOOL_CONVERSION
#define SUPPRESS_WARN_CLANG_POTENTIALLY_EVALUATED_EXPRESSION
#define SUPPRESS_WARN_CLANG_REINTERPRET_BASE_CLASS
#define SUPPRESS_WARN_CLANG_REORDER_CTOR
#define SUPPRESS_WARN_CLANG_RESERVED_USER_DEFINED_LITERAL
#define SUPPRESS_WARN_CLANG_RETURN_STACK_ADDRESS
#define SUPPRESS_WARN_CLANG_RETURN_TYPE
#define SUPPRESS_WARN_CLANG_SELF_ASSIGN_OVERLOADED
#define SUPPRESS_WARN_CLANG_SELF_MOVE
#define SUPPRESS_WARN_CLANG_UNDEFINED_INTERNAL
#define SUPPRESS_WARN_CLANG_UNDEF_COMP
#define SUPPRESS_WARN_CLANG_OVERLAP_COMP
#define SUPPRESS_WARN_CLANG_UNEVALUATED_EXPRESSION
#define SUPPRESS_WARN_CLANG_UNKNOWN_ESCAPE_SEQUENCE
#define SUPPRESS_WARN_CLANG_UNSEQUENCED
#define SUPPRESS_WARN_CLANG_UNUSED_CONST_VAR
#define SUPPRESS_WARN_CLANG_UNUSED_INTERNAL_DECL
#define SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD

#endif
    // @@@ sample end
