#include <filesystem>
#include <regex>
#include <vector>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記クラスFile、Dir、OtherEntityはクラスFileEntityから派生し、
// それぞれが自身をstd::stringに変換するアルゴリズム関数
//      * to_string_normal()
//      * to_string_with_char()
//      * to_string_with_children()
// をオーバーライドしている。これはポリモーフィズムの使用方法としては正しいが、
// to_string_xxx系統のインターフェースがが大量に増えた場合に、
// FileEntityのインターフェースがそれに比例して増えてしまう問題を持っている。
// Visitorパターンを使用しこれに対処せよ。

class FileEntity {
public:
    explicit FileEntity(std::string const& pathname) : pathname_{strip(pathname)} {}
    virtual ~FileEntity() = default;
    std::string const& Pathname() const noexcept { return pathname_; }

    std::string ToStringNormal() const { return to_string_normal(); }
    std::string ToStringWithChar() const { return to_string_with_char(); }
    std::string ToStringWithChildren() const { return to_string_with_children(); }

private:
    std::string const pathname_;

    virtual std::string to_string_normal() const        = 0;
    virtual std::string to_string_with_char() const     = 0;
    virtual std::string to_string_with_children() const = 0;

    static std::string strip(std::string const& pathname)
    {
        return std::regex_replace(pathname, std::regex{R"(/+$)"}, "");
    }
};

class File final : public FileEntity {
public:
    explicit File(std::string const& pathname) : FileEntity{pathname} {}

private:
    virtual std::string to_string_normal() const override { return Pathname(); }
    virtual std::string to_string_with_char() const override { return Pathname(); };
    virtual std::string to_string_with_children() const override { return Pathname(); };
};

class Dir final : public FileEntity {
public:
    explicit Dir(std::string const& pathname) : FileEntity{pathname} {}

private:
    virtual std::string to_string_normal() const override { return Pathname() + '/'; }
    virtual std::string to_string_with_char() const override { return to_string_normal(); };
    virtual std::string to_string_with_children() const override { return find_files(Pathname()); };

    static std::string find_files(std::string const& dir)
    {
        namespace fs = std::filesystem;

        auto files = std::vector<std::string>{};

        std::for_each(fs::recursive_directory_iterator{dir}, fs::recursive_directory_iterator{},
                      [&files](fs::path const& p) { files.emplace_back(p.generic_string()); });

        std::sort(files.begin(), files.end());

        auto ret = std::string{dir};

        for (auto f : files) {
            ret += ' ' + f;
        }

        return ret;
    }
};

class OtherEntity final : public FileEntity {
public:
    explicit OtherEntity(std::string const& pathname) : FileEntity{pathname} {}

private:
    virtual std::string to_string_normal() const override { return Pathname(); }
    virtual std::string to_string_with_char() const override { return Pathname() + '+'; };
    virtual std::string to_string_with_children() const override { return Pathname(); };
};

TEST(DesignPatternQ, Visitor)
{
    auto const f0 = File{"../ut_data/a.cpp"};
    auto const f1 = File{"../ut_data/a.cpp///"};

    ASSERT_EQ("../ut_data/a.cpp", f0.Pathname());
    ASSERT_EQ("../ut_data/a.cpp", f0.Pathname());
    ASSERT_EQ("../ut_data/a.cpp", f0.ToStringNormal());
    ASSERT_EQ("../ut_data/a.cpp", f0.ToStringWithChar());
    ASSERT_EQ("../ut_data/a.cpp", f0.ToStringWithChildren());

    auto const dir = Dir{"../ut_data/lib/"};

    ASSERT_EQ("../ut_data/lib", dir.Pathname());
    ASSERT_EQ("../ut_data/lib/", dir.ToStringNormal());
    ASSERT_EQ("../ut_data/lib/", dir.ToStringWithChar());
    ASSERT_EQ("../ut_data/lib ../ut_data/lib/lib.cpp ../ut_data/lib/lib.h",
              dir.ToStringWithChildren());

    auto const other = OtherEntity{"symbolic_link"};

    ASSERT_EQ("symbolic_link", other.Pathname());
    ASSERT_EQ("symbolic_link", other.ToStringNormal());
    ASSERT_EQ("symbolic_link+", other.ToStringWithChar());
    ASSERT_EQ("symbolic_link", other.ToStringWithChildren());
}
// @@@ sample end
}  // namespace
