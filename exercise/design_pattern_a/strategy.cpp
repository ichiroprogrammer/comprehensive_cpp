#include <filesystem>
#include <functional>
#include <string>
#include <vector>

#include "gtest_wrapper.h"

namespace {

namespace fs = std::filesystem;

// @@@ sample begin 0:0
// [A]
// 下記find_filesは醜悪であるだけでなく、拡張性もない。
// Strategyパターンを用い、この問題に対処せよ。

using FindCondition = std::function<bool(std::filesystem::path const&)>;

std::vector<std::string> find_files(std::string const& path, FindCondition condition)
{
    auto files = std::vector<fs::path>{};

    // recursive_directory_iteratorはファイルシステム依存するため、その依存を排除する他の処理
    std::copy(fs::recursive_directory_iterator{path}, fs::recursive_directory_iterator{}, std::back_inserter(files));

    std::sort(files.begin(), files.end());

    auto ret = std::vector<std::string>{};

    std::for_each(files.cbegin(), files.cend(), [&](fs::path const& p) {
        if (condition(p)) {
            ret.emplace_back(p.generic_string());
        }
    });

    return ret;
}

bool is_cpp_file(std::filesystem::path const& path)
{
    auto const        filename = path.filename().generic_string();
    static auto const cpp_file = std::string{".cpp"};

    return (filename.length() > cpp_file.length())
           && (filename.substr(filename.length() - cpp_file.length()) == cpp_file);
}

TEST(DesignPatternA, Strategy)
{
    auto sort = [](auto&& v) {
        std::sort(v.begin(), v.end());
        return v;
    };

    {
        auto exp = sort(std::vector<std::string>{"../ut_data/a.cpp", "../ut_data/a.h", "../ut_data/abc.cpp",
                                                 "../ut_data/abc.h", "../ut_data/d/a.d", "../ut_data/efghij.cpp",
                                                 "../ut_data/efghij.h", "../ut_data/lib/lib.cpp",
                                                 "../ut_data/lib/lib.h", "../ut_data/o/a.o"});
        auto act = find_files("../ut_data", [](fs::path const& p) noexcept { return fs::is_regular_file(p); });

        ASSERT_EQ(exp, act);
    }
    {
        auto exp = sort(std::vector<std::string>{"../ut_data/d", "../ut_data/lib", "../ut_data/o"});
        auto act = find_files("../ut_data", [](fs::path const& p) noexcept { return fs::is_directory(p); });

        ASSERT_EQ(exp, act);
    }
    {
        auto exp = sort(std::vector<std::string>{"../ut_data/a.cpp", "../ut_data/abc.cpp", "../ut_data/efghij.cpp",
                                                 "../ut_data/lib/lib.cpp"});
        auto act = find_files("../ut_data", is_cpp_file);

        ASSERT_EQ(exp, act);
    }
}
// @@@ sample end
}  // namespace
