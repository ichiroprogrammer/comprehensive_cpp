#include <algorithm>
#include <cstdint>
#include <future>
#include <thread>
#include <vector>

#include "gtest_wrapper.h"

#include "do_heavy_algorithm.h"

namespace {

// @@@ sample begin 0:0
class Pred {  // 0を最大3個まで見つける
public:
    Pred() noexcept {}
    bool operator()(int32_t i) noexcept
    {
        if (found_ > 2) {
            return false;
        }

        if (i == 0) {
            ++found_;
            return true;
        }

        return false;
    }

private:
    size_t found_{0};
};

TEST(Debug, no_ref)
{
    auto v = std::vector{0, 0, 0, 0, 1, 2, 3, 4, 5};

    v.erase(std::remove_if(v.begin(), v.end(), Pred{}), v.end());

#if 0  // 本来ならば下記のテストがパスするはずだが。
    ASSERT_EQ((std::vector<int32_t>{0, 1, 2, 3, 4, 5}), v);
#else
    ASSERT_EQ((std::vector<int32_t>{1, 2, 3, 4, 5}), v);
#endif
}
// @@@ sample end

// @@@ sample begin 0:1
TEST(Debug, ref)
{
    auto v    = std::vector{0, 0, 0, 0, 1, 2, 3, 4, 5};
    auto pred = Pred{};

    v.erase(std::remove_if(v.begin(), v.end(), std::ref(pred)), v.end());

    ASSERT_EQ((std::vector<int32_t>{0, 1, 2, 3, 4, 5}), v);
}
// @@@ sample end

// @@@ sample begin 0:2
TEST(Debug, lambda)
{
    auto v = std::vector{0, 0, 0, 0, 1, 2, 3, 4, 5};

    auto found = 0;
    auto it    = std::remove_if(v.begin(), v.end(), [&found](int32_t i) noexcept {
        if (found > 2) {
            return false;
        }

        if (i == 0) {
            ++found;
            return true;
        }

        return false;
    });
    v.erase(it, v.end());

    ASSERT_EQ((std::vector<int32_t>{0, 1, 2, 3, 4, 5}), v);
}
// @@@ sample end

namespace NG {
// @@@ sample begin 1:0

std::string gen_str(std::string const& str)
{
    return do_heavy_algorithm(str);  // 何らかの重い処理
}
// @@@ sample end

TEST(Debug, rvalue_ref)
{
    // @@@ sample begin 1:1

    auto str = gen_str("haha");  // "haha"は、std::string{"haha"}に変換される
    // @@@ sample end

    ASSERT_EQ("HAHA", str);
}

// @@@ sample begin 1:2

std::future<std::string> gen_future(std::string const& str)
{
    return std::async(std::launch::async, [&str] { return do_heavy_algorithm(str); });
}
// @@@ sample end

TEST(Debug, future_lvalue_ref_capture)
{
    auto str = std::string{"haha"};
    auto f   = gen_future(str);

    ASSERT_EQ("HAHA", f.get());
}

#define CLASH_FUTURE_TEST 0

#if CLASH_FUTURE_TEST
#define future_lvalue_ref_capture_clash_Opt future_lvalue_ref_capture_clash
#else
#define future_lvalue_ref_capture_clash_Opt DISABLED_future_lvalue_ref_capture_clash
#endif
TEST(Debug, future_lvalue_ref_capture_clash_Opt)
{
    // @@@ sample begin 1:3

    auto f = gen_future("haha");
    // @@@ sample end

    ASSERT_EQ("HAHA", f.get());
}
}  // namespace NG

namespace OK {
// @@@ sample begin 1:4

std::future<std::string> gen_future(std::string const& str)
{
    return std::async(std::launch::async, [str] { return do_heavy_algorithm(str); });
    //                                     ^^^ コピーキャプチャ
}
// @@@ sample end

TEST(Debug, future_lvalue_copy_capture)
{
    {
        auto str = std::string{"haha"};
        auto f   = gen_future(str);

        ASSERT_EQ("HAHA", f.get());
    }

    {
        auto f = gen_future("haha");

        ASSERT_EQ("HAHA", f.get());
    }
}
}  // namespace OK

namespace NG {
// @@@ sample begin 1:5

std::thread gen_thread_lambda(std::string const& str, std::string& str_out)  // str_outに結果出力
{
    return std::thread{[&str, &str_out] { str_out = do_heavy_algorithm(str); }};
}
// @@@ sample end

TEST(Debug, thread_lambda_lvalue_ref_capture)
{
    auto str     = std::string{"haha"};
    auto str_out = std::string{};
    auto t       = gen_thread_lambda(str, str_out);

    t.join();
    ASSERT_EQ("HAHA", str_out);
}

#define CLASH_THREAD_LAMBDA_TEST 0

#if CLASH_THREAD_LAMBDA_TEST
#define thread_lambda_lvalue_ref_capture_clash_Opt thread_lambda_lvalue_ref_capture_clash
#else
#define thread_lambda_lvalue_ref_capture_clash_Opt DISABLED_thread_lambda_lvalue_ref_capture_clash
#endif
TEST(Debug, thread_lambda_lvalue_ref_capture_clash_Opt)
{
    // @@@ sample begin 1:6

    auto str_out = std::string{};
    auto t       = gen_thread_lambda("haha", str_out);

    t.join();
    // @@@ sample end

    ASSERT_EQ("HAHA", str_out);
}
}  // namespace NG

namespace OK {
// @@@ sample begin 1:7

std::thread gen_thread_lambda(std::string const& str, std::string& str_out)  // str_outに結果出力
{
    return std::thread{[str, &str_out] { str_out = do_heavy_algorithm(str); }};
    //                  ^^^ コピーキャプチャ
}
// @@@ sample end

TEST(Debug, thread_lambda_lvalue_copy_capture)
{
    {
        auto str     = std::string{"haha"};
        auto str_out = std::string{};
        auto t       = gen_thread_lambda(str, str_out);

        t.join();
        ASSERT_EQ("HAHA", str_out);
    }
    {
        auto str_out = std::string{};
        auto t       = gen_thread_lambda("haha", str_out);

        t.join();
        ASSERT_EQ("HAHA", str_out);
    }
}
}  // namespace OK

namespace NG {
// @@@ sample begin 1:8

void thread_entry(std::string const& str, std::string& str_out)
{
    str_out = do_heavy_algorithm(str);
}

std::thread gen_thread_func(std::string const& str, std::string& str_out)  // str_outに結果出力
{
    return std::thread{thread_entry, std::ref(str), std::ref(str_out)};
}
// @@@ sample end

TEST(Debug, thread_func_lvalue_ref_capture)
{
    auto str     = std::string{"haha"};
    auto str_out = std::string{};
    auto t       = gen_thread_func(str, str_out);

    t.join();
    ASSERT_EQ("HAHA", str_out);
}

#define CLASH_THREAD_FUNC_TEST 0

#if CLASH_THREAD_FUNC_TEST
#define thread_func_lvalue_ref_capture_clash_Opt thread_func_lvalue_ref_capture_clash
#else
#define thread_func_lvalue_ref_capture_clash_Opt DISABLED_thread_func_lvalue_ref_capture_clash
#endif

TEST(Debug, thread_func_lvalue_ref_capture_clash_Opt)
{
    auto str_out = std::string{};
    auto t       = gen_thread_func("haha", str_out);

    t.join();
    ASSERT_EQ("HAHA", str_out);
}
}  // namespace NG

namespace OK {
// @@@ sample begin 1:9

void thread_entry(std::string str, std::string& str_out)
//                            ^^^ コピー渡し
{
    str_out = do_heavy_algorithm(str);
}

std::thread gen_thread_func(std::string const& str, std::string& str_out)  // str_outに結果出力
{
    return std::thread{thread_entry, str, std::ref(str_out)};
    //                               ^^^ コピー渡し
}
// @@@ sample end

TEST(Debug, thread_func_lvalue_copy_capture)
{
    {
        auto str     = std::string{"haha"};
        auto str_out = std::string{};
        auto t       = gen_thread_func(str, str_out);

        t.join();
        ASSERT_EQ("HAHA", str_out);
    }
    {
        auto str_out = std::string{};
        auto t       = gen_thread_func("haha", str_out);

        t.join();
        ASSERT_EQ("HAHA", str_out);
    }
}
}  // namespace OK
}  // namespace
