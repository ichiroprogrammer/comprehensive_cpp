#include <chrono>
#include <complex>
#include <sstream>
#include <tuple>
#include <utility>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 3:0

template <typename Tuple, std::size_t... I>
std::string tuple2string(Tuple const& t, std::index_sequence<I...>)
{
    std::ostringstream os;

    ((os << std::get<I>(t) << " "), ...);  // Tupleの各要素を出力

    return os.str();
}

template <typename... Args>
std::string process_tuple(std::tuple<Args...> const& t)
{
    return tuple2string(t, std::index_sequence_for<Args...>{});
}
// @@@ sample end

TEST(cpp14, integer_sequence)
{
    // @@@ sample begin 3:1

    std::tuple<int, double, char const*> t(1, 2.5, "test");

    auto ret = process_tuple(t);  // タプルの要素を出力 (1, 2.5, test)
    ASSERT_EQ("1 2.5 test ", ret);
    ASSERT_EQ(1, std::get<0>(t));
    ASSERT_EQ(2.5, std::get<1>(t));
    ASSERT_STREQ("test", std::get<2>(t));
    // @@@ sample end
}

TEST(cpp14, tupple_get)
{
    // @@@ sample begin 4:0

    std::tuple<int, float, std::string> my_tuple(1, 3.14f, "hello");

    // 異なる型のオーバーロードされた std::get を使用
    ASSERT_EQ(std::get<int>(my_tuple), 1);
    ASSERT_FLOAT_EQ(std::get<float>(my_tuple), 3.14f);
    ASSERT_EQ(std::get<std::string>(my_tuple), "hello");
    // @@@ sample end
}
}  // namespace
