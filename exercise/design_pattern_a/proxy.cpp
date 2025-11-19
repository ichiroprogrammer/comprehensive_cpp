#include <chrono>
#include <memory>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// 下記クラスLsDirのFileListはlsコマンドをpopenにより実行し、その戻り値をstd::stringで返す。
// popenはコストの高いコールなので、パフォーマンスを上げるためにlsの戻り値をキャッシュしたいが、
// 現行のLsDirも必要である。
// Proxyパターンを使い、この問題に対処するためのLsDirCachedを作れ。

#define USE_ACCURATE_PROXY
#ifdef USE_ACCURATE_PROXY  // 本来#ifdefは問題を発生させるため使うべきではないが、例なので。
class LsDirIF {
public:
    LsDirIF()          = default;
    virtual ~LsDirIF() = default;

    void               SetArgs(std::string_view args) { args_ = args; }
    std::string const& GetArgs() const noexcept { return args_; }
    std::string const  FileList() const { return file_list(); }

private:
    std::string         args_{};
    virtual std::string file_list() const = 0;
};

class LsDir : public LsDirIF {
public:
    LsDir()          = default;
    virtual ~LsDir() = default;

private:
    virtual std::string file_list() const override
    {
        auto cmd      = std::string{"ls "} + GetArgs();
        auto to_close = [](FILE* f) { fclose(f); };
        auto stream   = std::unique_ptr<FILE, decltype(to_close)>{popen(cmd.c_str(), "r"), to_close};

        auto files = std::string{};
        char buff[256];

        while (fgets(buff, sizeof(buff) - 1, stream.get()) != NULL) {
            files += buff;
        }

        return files;
    }
};

class LsDirCached : public LsDirIF {
public:
    LsDirCached()                   = default;
    virtual ~LsDirCached() override = default;

private:
    mutable std::string latest_ls_{};
    mutable LsDir       ld_no_cache_{};

    virtual std::string file_list() const override
    {
        if (GetArgs() == ld_no_cache_.GetArgs()) {
            return latest_ls_;
        }

        ld_no_cache_.SetArgs(GetArgs());
        latest_ls_ = ld_no_cache_.FileList();

        return latest_ls_;
    }
};
#else  // not USE_ACCURATE_PROXY
class LsDir {
public:
    LsDir()          = default;
    virtual ~LsDir() = default;

    void               SetArgs(std::string_view args) { args_ = args; }
    std::string const& GetArgs() const { return args_; }
    std::string const  FileList() const { return file_list(); }

protected:
    virtual std::string file_list() const
    {
        auto cmd      = std::string{"ls "} + GetArgs();
        auto to_close = [](FILE* f) { fclose(f); };
        auto stream   = std::unique_ptr<FILE, decltype(to_close)>{popen(cmd.c_str(), "r"), to_close};

        auto files = std::string{};
        char buff[256];

        while (fgets(buff, sizeof(buff) - 1, stream.get()) != NULL) {
            files += buff;
        }

        return files;
    }

private:
    std::string args_{};
};

class LsDirCached : public LsDir {
public:
    LsDirCached()                   = default;
    virtual ~LsDirCached() override = default;

protected:
    virtual std::string file_list() const override
    {
        if (GetArgs() == latest_args_) {
            return latest_ls_;
        }

        latest_args_ = GetArgs();
        latest_ls_   = LsDir::file_list();

        return latest_ls_;
    }

private:
    mutable std::string latest_ls_{};
    mutable std::string latest_args_{};
};
#endif

TEST(DesignPatternA, Proxy)
{
    auto ld = LsDir{};

    {
        ld.SetArgs("../ut_data/");

        auto exp = std::string{"a.cpp\na.h\nabc.cpp\nabc.h\nd\nefghij.cpp\nefghij.h\nlib\no\n"};
        auto act = ld.FileList();

        ASSERT_EQ(exp, act);
        ASSERT_EQ(act, ld.FileList());
    }
    {
        ld.SetArgs("../ut_data/lib/");

        auto exp = std::string{"lib.cpp\nlib.h\n"};
        auto act = ld.FileList();

        ASSERT_EQ(exp, act);
        ASSERT_EQ(act, ld.FileList());
    }
}

TEST(DesignPatternA, Proxy2)
{
    auto ld = LsDirCached{};

    {
        ld.SetArgs("../ut_data/");

        auto exp = std::string{"a.cpp\na.h\nabc.cpp\nabc.h\nd\nefghij.cpp\nefghij.h\nlib\no\n"};
        auto act = ld.FileList();

        ASSERT_EQ(exp, act);
        ASSERT_EQ(act, ld.FileList());
    }
    {
        ld.SetArgs("../ut_data/lib/");

        auto exp = std::string{"lib.cpp\nlib.h\n"};
        auto act = ld.FileList();

        ASSERT_EQ(exp, act);
        ASSERT_EQ(act, ld.FileList());
    }
}

template <typename LSDIR>
uint32_t measure_performance(LSDIR const& ls_dir, uint32_t count) noexcept
{
    auto const start = std::chrono::system_clock::now();
    {
        for (decltype(count) i = 0; i < count; ++i) {
            auto const volatile list = ls_dir.FileList();
        }
    }

    auto const stop = std::chrono::system_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

TEST(DesignPatternA, ProxyPerformance)
{
    auto ld               = LsDir{};
    auto elapsed_no_cache = uint32_t{measure_performance(ld, 10)};
    std::cout << "No Cache Elapse:" << elapsed_no_cache << " usec" << std::endl;

    auto ldc           = LsDirCached{};
    auto elapsed_cache = uint32_t{measure_performance(ldc, 10)};
    std::cout << "Cached Elapse:" << elapsed_cache << " usec" << std::endl;

    ASSERT_LT(30 * elapsed_cache, elapsed_no_cache);  // 30倍に理由はない。
}
// @@@ sample end
}  // namespace
