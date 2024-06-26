#include <filesystem>
#include <regex>
#include <vector>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記クラスFileEntityから派生しクラスFile、Dir、OtherEntityは、
// Visitorパターンを利用しているため、そのすべてで下記のコードクローンを持つ。
//
//    virtual std::string to_string(Visitor const& to_s) const { return to_s.Visit(*this); }
//
// このコードクローンのthisの型は、それぞれFile、Dir、OtherEntityとなるため、
// この関数をFileEntityで定義すると動作が変わってしまい、単純には統一できない。
// CRTPを用い、このクローンを削除せよ。

class Visitor;

class FileEntity {
public:
    explicit FileEntity(std::string const& pathname) : pathname_{strip(pathname)} {}
    virtual ~FileEntity() = default;
    std::string const& Pathname() const { return pathname_; }
    std::string        ToString(Visitor const& to_s) const { return to_string(to_s); }

private:
    std::string const pathname_;

    virtual std::string to_string(Visitor const& to_s) const = 0;
    static std::string  strip(std::string const& pathname)
    {
        return std::regex_replace(pathname, std::regex{R"(/+$)"}, "");
    }
};

class File;
class Dir;
class OtherEntity;

class Visitor {
public:
    virtual ~Visitor() = default;
    std::string Visit(File const& file) const { return visit(file); }
    std::string Visit(Dir const& dir) const { return visit(dir); }
    std::string Visit(OtherEntity const& other) const { return visit(other); }

private:
    virtual std::string visit(File const& file) const     = 0;
    virtual std::string visit(Dir const& dir) const       = 0;
    virtual std::string visit(OtherEntity const& f) const = 0;
};

class File final : public FileEntity {
public:
    explicit File(std::string const& pathname) : FileEntity{pathname} {}

private:
    virtual std::string to_string(Visitor const& to_s) const { return to_s.Visit(*this); }
};

class Dir final : public FileEntity {
public:
    explicit Dir(std::string const& pathname) : FileEntity{pathname} {}

private:
    virtual std::string to_string(Visitor const& to_s) const { return to_s.Visit(*this); }
};

class OtherEntity final : public FileEntity {
public:
    explicit OtherEntity(std::string const& pathname) : FileEntity{pathname} {}

private:
    virtual std::string to_string(Visitor const& to_s) const { return to_s.Visit(*this); }
};

class ToStringNormal : public Visitor {
private:
    virtual std::string visit(File const& file) const override { return file.Pathname(); }
    virtual std::string visit(Dir const& dir) const override { return dir.Pathname() + '/'; }
    virtual std::string visit(OtherEntity const& other) const override { return other.Pathname(); }
};

class ToStringWithChar : public Visitor {
private:
    virtual std::string visit(File const& file) const override { return file.Pathname(); }
    virtual std::string visit(Dir const& dir) const override { return dir.Pathname() + '/'; }
    virtual std::string visit(OtherEntity const& other) const override
    {
        return other.Pathname() + '+';
    }
};

class ToStringWithChildren : public Visitor {
private:
    virtual std::string visit(File const& file) const override { return file.Pathname(); }
    virtual std::string visit(Dir const& dir) const override { return find_files(dir.Pathname()); }
    virtual std::string visit(OtherEntity const& other) const override { return other.Pathname(); }

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

TEST(DesignPatternQ, CRTP)
{
    auto ts_normal   = ToStringNormal{};
    auto ts_char     = ToStringWithChar{};
    auto ts_children = ToStringWithChildren{};

    auto const f0 = File{"../ut_data/a.cpp"};
    auto const f1 = File{"../ut_data/a.cpp///"};

    ASSERT_EQ("../ut_data/a.cpp", f0.Pathname());
    ASSERT_EQ("../ut_data/a.cpp", f0.Pathname());

    ASSERT_EQ("../ut_data/a.cpp", f0.ToString(ts_normal));
    ASSERT_EQ("../ut_data/a.cpp", f0.ToString(ts_char));
    ASSERT_EQ("../ut_data/a.cpp", f0.ToString(ts_children));

    auto const dir = Dir{"../ut_data/lib/"};

    ASSERT_EQ("../ut_data/lib", dir.Pathname());
    ASSERT_EQ("../ut_data/lib/", dir.ToString(ts_normal));
    ASSERT_EQ("../ut_data/lib/", dir.ToString(ts_char));
    ASSERT_EQ("../ut_data/lib ../ut_data/lib/lib.cpp ../ut_data/lib/lib.h",
              dir.ToString(ts_children));

    auto const other = OtherEntity{"symbolic_link"};

    ASSERT_EQ("symbolic_link", other.Pathname());
    ASSERT_EQ("symbolic_link", other.ToString(ts_normal));
    ASSERT_EQ("symbolic_link+", other.ToString(ts_char));
    ASSERT_EQ("symbolic_link", other.ToString(ts_children));
}
// @@@ sample end
}  // namespace
