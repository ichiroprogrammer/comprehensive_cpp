#pragma once

#ifdef __CYGWIN__  // -std=c++14を指定したcygwin g++9.3でのコンパイルには以下の宣言が必要
#include <string.h>
extern char* strdup(char const* str1);

#include <stdio.h>
extern int       fileno(FILE* stream);
extern FILE*     fdopen(int handle, char const* mode);
extern "C" FILE* popen(char const*, char const*);
#endif

#if defined(__clang__)
_Pragma("clang diagnostic push");
_Pragma("clang diagnostic ignored \"-Wsign-compare\"");
#else
_Pragma("GCC diagnostic push");
_Pragma("GCC diagnostic ignored \"-Wsign-compare\"");
_Pragma("GCC diagnostic ignored \"-Weffc++\"");
#endif

#include "gtest/gtest.h"

#if defined(__clang__)
_Pragma("clang diagnostic pop");
#else
_Pragma("GCC diagnostic pop");
#endif
