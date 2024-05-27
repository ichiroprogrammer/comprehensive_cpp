#include <cxxabi.h>

#include <cstdio>
#include <typeinfo>

#include "gtest_wrapper.h"

// @@@ sample begin 0:0
// [A]
// RAIIを行うための下記クラスscoped_guardをstd::functionを使わずに再実装せよ。

template <typename FUNC>
class scoped_guard {
public:
    explicit scoped_guard(FUNC&& f) noexcept : f_{f}
    {
        static_assert(std::is_nothrow_invocable_r_v<void, FUNC>, "FUNC()() must return void");
    }
    ~scoped_guard() { f_(); }

    scoped_guard(scoped_guard const&)   = delete;   // copy禁止
    scoped_guard(scoped_guard&&)        = default;  // move
    void operator=(scoped_guard const&) = delete;   // copy代入禁止
    void operator=(scoped_guard&&)      = delete;   // move代入禁止

private:
    FUNC f_;
};

namespace {

TEST(TemplateMetaProgrammingA, scoped_guard)
{
    {
        auto demangled = abi::__cxa_demangle(typeid(std::vector<int>).name(), 0, 0, nullptr);
        auto f         = [demangled]() noexcept { free(demangled); };
        auto sg        = scoped_guard<decltype(f)>{std::move(f)};  // C++14までの記法

        ASSERT_STREQ("std::vector<int, std::allocator<int> >", demangled);
    }
    {
        auto demangled = abi::__cxa_demangle(typeid(std::vector<int>).name(), 0, 0, nullptr);
        auto gs = scoped_guard{[demangled]() noexcept { free(demangled); }};  // C++17からの記法

        ASSERT_STREQ("std::vector<int, std::allocator<int> >", demangled);
    }
    {
        auto stream = popen("ls " __FILE__, "r");
        auto f      = [stream]() noexcept { fclose(stream); };
        auto sg     = scoped_guard<decltype(f)>{std::move(f)};  // C++14までの記法

        char buff[256]{};
        fgets(buff, sizeof(buff) - 1, stream);

        ASSERT_STREQ("scoped_guard.cpp\n", buff);
    }
    {
        auto stream = popen("ls " __FILE__, "r");
        auto gs = scoped_guard{[stream]() noexcept { fclose(stream); }};  // C++17からの記法

        char buff[256]{};
        fgets(buff, sizeof(buff) - 1, stream);

        ASSERT_STREQ("scoped_guard.cpp\n", buff);
    }
}
}  // namespace
// @@@ sample end
