#pragma once

#include <cxxabi.h>

#include <memory>
#include <string>
#include <typeinfo>

// @@@ sample begin 0:0

namespace Nstd {
namespace Inner_ {

inline std::string demangle(char const* to_demagle)
{
    int status;
    // @@@ sample end
    // @@@ sample begin 0:1

    std::unique_ptr<char, decltype(&std::free)> demangled{
        abi::__cxa_demangle(to_demagle, 0, 0, &status), &std::free};
    // @@@ sample end
    // @@@ sample begin 0:2

    return demangled.get();
}

template <typename>  // typenameを取り出すためだけのクラステンプレート
struct type_capture {
};
}  // namespace Inner_

template <typename T>
std::string Type2Str()
{
    // typeid(T)とした場合、const/volatile/&の情報が捨てられるため、
    // typeid(type_capture<T>)とし、それを防ぐ。
    auto str = std::string{Inner_::demangle(typeid(Inner_::type_capture<T>).name())};

    // T   == const int ならば、
    // str == Nstd::Inner_::type_capture<int const>
    //        <----------- 27 ----------><-- x --> 下記ではxを切り出す
    constexpr auto beg = 27U;                           // 先頭の不要な文字列数
    auto name = str.substr(beg, str.size() - beg - 1);  // 最後の文字は>なので不要

    while (name.back() == ' ') {  // 無駄なスペースを消す
        auto last = --name.end();
        name.erase(last);
    }

    return name;
}
}  // namespace Nstd
// @@@ sample end
