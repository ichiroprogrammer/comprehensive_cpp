#include <filesystem>
#include <string>
#include <vector>

#include "gtest_wrapper.h"

namespace {

namespace fs = std::filesystem;

// @@@ sample begin 0:0
// [Q]
// 下記find_filesは醜悪であるだけでなく、拡張性もない。
// Strategyパターンを用い、この問題に対処せよ。

enum class FindCondition {
    File,
    Dir,
    FileCpp,
};

std::vector<std::string> find_files(std::string const& path, FindCondition condition)
{
    namespace fs = std::filesystem;

    auto files = std::vector<fs::path>{};

    // recursive_directory_iteratorはファイルシステム依存するため、その依存を排除する他の処理
    std::copy(fs::recursive_directory_iterator{path}, fs::recursive_directory_iterator{},
              std::back_inserter(files));

    std::sort(files.begin(), files.end());

    auto ret = std::vector<std::string>{};

    for (fs::path const& p : files) {
        auto is_match = false;

        switch (condition) {
        case FindCondition::File:
            if (fs::is_regular_file(p)) {
                is_match = true;
            }
            break;
        case FindCondition::Dir:
            if (fs::is_directory(p)) {
                is_match = true;
            }
            break;
        case FindCondition::FileCpp: {
            auto const filename = p.filename().generic_string();
            auto const cpp_file = std::string{".cpp"};

            if (filename.length() > cpp_file.length()
                && (filename.substr(filename.length() - cpp_file.length()) == cpp_file)) {
                is_match = true;
            }
            break;
        }
        default:
            assert(false);
        }

        if (is_match) {
            ret.emplace_back(p.generic_string());
        }
    }

    return ret;
}

TEST(DesignPatternQ, Strategy)
{
    auto sort = [](auto&& v) {
        std::sort(v.begin(), v.end());
        return v;
    };

    {
        auto exp = sort(std::vector<std::string>{
            "../ut_data/a.cpp", "../ut_data/a.h", "../ut_data/abc.cpp", "../ut_data/abc.h",
            "../ut_data/d/a.d", "../ut_data/efghij.cpp", "../ut_data/efghij.h",
            "../ut_data/lib/lib.cpp", "../ut_data/lib/lib.h", "../ut_data/o/a.o"});
        auto act = find_files("../ut_data", FindCondition::File);

        ASSERT_EQ(exp, act);
    }
    {
        auto exp = sort(std::vector<std::string>{"../ut_data/d", "../ut_data/lib", "../ut_data/o"});
        auto act = find_files("../ut_data", FindCondition::Dir);

        ASSERT_EQ(exp, act);
    }
    {
        auto exp
            = sort(std::vector<std::string>{"../ut_data/a.cpp", "../ut_data/abc.cpp",
                                            "../ut_data/efghij.cpp", "../ut_data/lib/lib.cpp"});
        auto act = find_files("../ut_data", FindCondition::FileCpp);

        ASSERT_EQ(exp, act);
    }
}
// @@@ sample end
}  // namespace
