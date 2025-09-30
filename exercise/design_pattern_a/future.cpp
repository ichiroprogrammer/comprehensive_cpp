#include <algorithm>
#include <filesystem>
#include <future>
#include <thread>

#include "gtest_wrapper.h"

namespace {

std::vector<std::string> find_files(std::string const& path)
{
    auto files = std::vector<std::string>{};

    namespace fs = std::filesystem;
    std::for_each(fs::recursive_directory_iterator{path}, fs::recursive_directory_iterator{}, [&](fs::path const& p) {
        if (fs::is_regular_file(p)) {
            files.emplace_back(p.generic_string());
        }
    });

    return files;
}

// @@@ sample begin 0:0
// [A]
// 下記のfind_files_concurrentlyはスレッドの出力の結果をキャプチャリファレンスで受け取るため、
// 入出力の関係が明確でない。Futureパターンを使用しそれを明確にするリファクタリングを行え。

std::vector<std::string> find_files_concurrently()
{
    std::future<std::vector<std::string>> result0
        = std::async(std::launch::async, [] { return find_files("../programming_convention_a/"); });

    std::future<std::vector<std::string>> result1
        = std::async(std::launch::async, [] { return find_files("../programming_convention_q/"); });

    auto pca = result0.get();
    auto pcq = result1.get();

    pca.insert(pca.end(), pcq.begin(), pcq.end());

    return pca;
}

TEST(DesignPatternA, Future)
{
    auto files = find_files_concurrently();

    ASSERT_GT(files.size(), 10);
}
// @@@ sample end
}  // namespace
