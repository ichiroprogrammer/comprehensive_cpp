#include <algorithm>
#include <cstdio>
#include <exception>
#include <memory>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// CppFilesはLsCppを直に生成するため、LsCpp::FileList()がエラーした場合の単体テスト実施が
// 困難である。CppFilesにDIパターンを適用するとともに、LsCppを適切に変更することによって、
// LsCpp::FileList()がエラーした場合のCppFilesの単体テストを行え。

class LsCpp {
public:
    virtual ~LsCpp() {}

    std::string const& FileList() { return file_list(); }

private:
    std::string files_{};

    virtual std::string const& file_list()  // 単体テストのためにvirtual
    {
        if (files_.size() != 0) {  // キャッシュを使う
            return files_;
        }

        auto stream = std::unique_ptr<FILE, decltype(&fclose)>{popen("ls ../ut_data/*.cpp", "r"), fclose};

        if (stream.get() == NULL) {
            throw std::exception{};
        }

        char buff[256];
        while (fgets(buff, sizeof(buff) - 1, stream.get()) != NULL) {
            files_ += buff;
        }

        return files_;
    }
};

class CppFiles {
public:
    explicit CppFiles(std::unique_ptr<LsCpp>&& ls_cpp = std::make_unique<LsCpp>()) : ls_cpp_{std::move(ls_cpp)} {}

    std::vector<std::string> FileList() const
    {
        auto files = std::string{};

        try {
            files = ls_cpp_->FileList();
        }
        catch (...) {
            ;  // 例外発生時には空のベクタを返すので何もしない。
        }

        return split_cr(files);
    }

private:
    std::unique_ptr<LsCpp> ls_cpp_;

    static std::vector<std::string> split_cr(std::string const& str)
    {
        auto ss  = std::stringstream{str};
        auto ret = std::vector<std::string>{};

        for (std::string line; std::getline(ss, line);) {
            ret.emplace_back(line);
        }

        return ret;
    }
};

class LsCppError : public LsCpp {
public:
    LsCppError() noexcept {}
    virtual ~LsCppError() override {}

private:
    [[noreturn]] virtual std::string const& file_list() override { throw std::exception{}; }
};

TEST(DesignPatternA, DI)
{
    auto        files = CppFiles{};
    auto const& act   = files.FileList();
    auto        exp   = std::vector<std::string>{"../ut_data/a.cpp", "../ut_data/abc.cpp", "../ut_data/efghij.cpp"};

    ASSERT_EQ(exp, act);

    // エラー系のテスト
    auto files2 = CppFiles{std::make_unique<LsCppError>()};

    ASSERT_EQ(0, files2.FileList().size());
}
// @@@ sample end
}  // namespace
