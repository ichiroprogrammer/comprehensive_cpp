#include <algorithm>
#include <filesystem>
#include <thread>

#include "gtest_wrapper.h"

namespace {

std::vector<std::string> find_files(std::string const& path)
{
    auto files = std::vector<std::string>{};

    namespace fs = std::filesystem;
    std::for_each(fs::recursive_directory_iterator{path}, fs::recursive_directory_iterator{},
                  [&](fs::path const& p) {
                      if (fs::is_regular_file(p)) {
                          files.emplace_back(p.generic_string());
                      }
                  });

    return files;
}

// @@@ sample begin 0:0
// [Q]
// 下記のfind_files_concurrentlyはスレッドの出力の結果をキャプチャリファレンスで受け取るため、
// 入出力の関係が明確でない。Futureパターンを使用しそれを明確にするリファクタリングを行え。

std::vector<std::string> find_files_concurrently()
{
    auto pca = std::vector<std::string>{};
    auto pcq = std::vector<std::string>{};

    auto th0 = std::thread{[&pca] { pca = find_files("../programming_convention_a/"); }};
    auto th1 = std::thread{[&pcq] { pcq = find_files("../programming_convention_q/"); }};

    th0.join();
    th1.join();

    pca.insert(pca.end(), pcq.begin(), pcq.end());

    return pca;
}

TEST(DesignPatternQ, Future)
{
    auto files = find_files_concurrently();

    ASSERT_GT(files.size(), 10);
}
// @@@ sample end
}  // namespace
