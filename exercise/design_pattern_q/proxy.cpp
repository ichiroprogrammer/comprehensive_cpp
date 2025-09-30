#include <memory>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記クラスLsDirのFileListはlsコマンドをpopenにより実行し、その戻り値をstd::stringで返す。
// popenはコストの高いコールなので、パフォーマンスを上げるためにlsの戻り値をキャッシュしたいが、
// 現行のLsDirも必要である。
// Proxyパターンを使い、この問題に対処するためのLsDirCachedを作れ。

class LsDir {
public:
    LsDir()  = default;
    ~LsDir() = default;

    void               SetArgs(std::string_view args) { args_ = args; }
    std::string const& GetArgs() const noexcept { return args_; }

    std::string FileList() const
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

TEST(DesignPatternQ, Proxy)
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
// @@@ sample end
}  // namespace
