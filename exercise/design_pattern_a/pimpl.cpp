#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A] 下記クラスCollectionの宣言はクラスWidgetの宣言に依存している。
// Pimplパターンを使用し、Collectionの宣言がWidgetの宣言に依存しないようにせよ。

class Widget;
class Collection {
public:
    Collection();
    char const* Name(size_t i) const;
    void        AddName(char const* name);
    size_t      Count() const noexcept;

private:
    class Pimpl;
    std::unique_ptr<Pimpl> pimpl_{};
};

TEST(DesignPatternA, Pimpl)
{
    auto c = Collection{};

    ASSERT_EQ(0, c.Count());
    ASSERT_THROW(c.Name(0), std::out_of_range);

    c.AddName("n0");
    c.AddName("n1");
    c.AddName("n2");

    ASSERT_EQ(3, c.Count());
    ASSERT_STREQ("n0", c.Name(0));
    ASSERT_STREQ("n1", c.Name(1));
    ASSERT_STREQ("n2", c.Name(2));
    ASSERT_THROW(c.Name(4), std::out_of_range);
}

class Widget {
public:
    explicit Widget(char const* name) : name_{name} {}
    char const* Name() const noexcept { return name_; }

private:
    char const* name_;
};

class Collection::Pimpl {
public:
    char const* Name(size_t i) const { return widgets_.at(i).Name(); }
    void        AddName(char const* name) { widgets_.emplace_back(name); }

    size_t Count() const noexcept { return widgets_.size(); }

private:
    std::vector<Widget> widgets_{};
};

Collection::Collection() : pimpl_{std::make_unique<Collection::Pimpl>()} {}
char const* Collection::Name(size_t i) const { return pimpl_->Name(i); }
void        Collection::AddName(char const* name) { pimpl_->AddName(name); }
size_t      Collection::Count() const noexcept { return pimpl_->Count(); }
// @@@ sample end
}  // namespace
