#include <cxxabi.h>

#include <cstdio>
#include <typeinfo>

#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [Q]
// RAIIを行うための下記クラスscoped_guardをstd::functionを使わずに再実装せよ。

class scoped_guard {
public:
    explicit scoped_guard(std::function<void()> f) noexcept : f_{f} {}
    ~scoped_guard() { f_(); }

    scoped_guard(scoped_guard const&)   = delete;
    void operator=(scoped_guard const&) = delete;

private:
    std::function<void()> f_;
};

namespace {

TEST(TemplateMetaProgrammingQ, scoped_guard)
{
    {
        auto demangled = abi::__cxa_demangle(typeid(std::vector<int>).name(), 0, 0, nullptr);
        auto sg        = scoped_guard{[demangled]() noexcept { free(demangled); }};

        ASSERT_STREQ("std::vector<int, std::allocator<int> >", demangled);
    }
    {
        auto stream = popen("ls " __FILE__, "r");
        auto sg     = scoped_guard{[stream]() noexcept { fclose(stream); }};

        char buff[256]{};
        fgets(buff, sizeof(buff) - 1, stream);

        ASSERT_STREQ("scoped_guard.cpp\n", buff);
    }
}
}  // namespace
// @@@ sample end
