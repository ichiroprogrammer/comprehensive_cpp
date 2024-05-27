#include <filesystem>

#include "gtest_wrapper.h"

#include "arg.h"

namespace {

template <typename T, std::size_t SIZE>
constexpr std::size_t array_length(T const (&)[SIZE]) noexcept
{
    return SIZE;
}

std::string const ofilename = "ofile.txt";
std::string const ifilename = "ifile.txt";

// @@@ sample begin 0:0

class Refactorin_5 : public ::testing::Test {  // google testクラス
protected:
    virtual void SetUp() noexcept override
    {
        remove_file(ofilename);  // ファイルがあると、テストがエラーするので。
        remove_file(ifilename);
    }

    virtual void TearDown() noexcept override
    {
        remove_file(ofilename);  // ローカルリポジトリにゴミを残さない。
        remove_file(ifilename);
    }

    static void remove_file(std::string const& filename) noexcept
    {
        if (std::filesystem::exists(filename)) {
            std::filesystem::remove(filename);
        }
    }
};

TEST_F(Refactorin_5, IOStreamSelector)
{
    {
        auto ios = IOStreamSelector{"", ofilename};

        ASSERT_TRUE(ios.Open());
        ASSERT_TRUE(&std::cin == &ios.GetIStream());
    }
    ASSERT_TRUE(std::filesystem::exists(ofilename));

    {
        {  // テスト用ファイルの作成
            auto ofs = std::ofstream{};

            ofs.open(ifilename);
            ASSERT_TRUE(ofs);

            ofs << "test";
        }
        ASSERT_TRUE(std::filesystem::exists(ifilename));

        auto ios = IOStreamSelector{ifilename, ""};

        ASSERT_TRUE(ios.Open());
        ASSERT_TRUE(&std::cout == &ios.GetOStream());

        auto file_contents = std::string{};

        ios.GetIStream() >> file_contents;
        ASSERT_EQ("test", file_contents);
    }
}

TEST_F(Refactorin_5, getopt)
{
    {
        char        p[]    = "p";
        char* const argv[] = {p};

        auto ret = getopt(array_length(argv), argv);

        ASSERT_TRUE(ret);
        ASSERT_EQ("", ret.value().ifile);
        ASSERT_EQ("", ret.value().ofile);
    }
    // @@@ ignore begin
    {
        char        p[]      = "p";
        char        dash_a[] = "-a";
        char* const argv[]   = {p, dash_a};

        auto ret = getopt(array_length(argv), argv);

        ASSERT_FALSE(ret);
    }
    {
        char        p[]      = "p";
        char        dash_i[] = "-i";
        char        if_[]    = "if";
        char* const argv[]   = {p, dash_i, if_};

        auto ret = getopt(array_length(argv), argv);

        ASSERT_TRUE(ret);
        ASSERT_EQ("if", ret.value().ifile);
        ASSERT_EQ("", ret.value().ofile);
    }
    {
        char        p[]      = "p";
        char        dash_o[] = "-o";
        char        of[]     = "of";
        char* const argv[]   = {p, dash_o, of};

        auto ret = getopt(array_length(argv), argv);

        ASSERT_TRUE(ret);
        ASSERT_EQ("", ret.value().ifile);
        ASSERT_EQ("of", ret.value().ofile);
    }
    {
        char        p[]      = "p";
        char        dash_i[] = "-i";
        char        if_[]    = "if";
        char        dash_o[] = "-o";
        char        of[]     = "of";
        char* const argv[]   = {p, dash_i, if_, dash_o, of};

        auto ret = getopt(array_length(argv), argv);

        ASSERT_TRUE(ret);
        ASSERT_EQ("if", ret.value().ifile);
        ASSERT_EQ("of", ret.value().ofile);
    }
    // @@@ ignore end
}
// @@@ sample end
}  // namespace
