#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
// 下記クラスXxxDataFormatterXml、XxxDataFormatterCsvは同様の処理を行い、
// それぞれのフォーマットで文字列を出力する。このような処理のクローンはTemplate Method
// パターンにより排除できる。
// このパターンを用い、下記2クラスをリファクタリングせよ。
// また、他の問題があれば合わせて修正せよ。

// [解説]
// * Template Methodのインターフェースクラスとして、XxxDataFormatterIFを定義した。
//      * header()、footer()はstd::stringのリファレンスを返すが、
//        body()は返すstd::stringが引数に依存して変わるため、実態を返す。
// * その他の修正
//      * header_やfooter_はそれぞれのクラスで同じオブジェクトであるため、
//        static constインスタンスとして、それぞれheader()、footer()の内部で定義した。
//      * XxxDataFormatterXml、XxxDataFormatterCsvはそれ以上派生する必要がないためfinalとした。

struct XxxData {
    int a;
    int b;
    int c;
};

class XxxDataFormatterIF {
public:
    XxxDataFormatterIF() noexcept                            = default;
    virtual ~XxxDataFormatterIF()                            = default;
    XxxDataFormatterIF(XxxDataFormatterIF const&)            = delete;
    XxxDataFormatterIF& operator=(XxxDataFormatterIF const&) = delete;

    std::string ToString(XxxData const& xxx_data) const { return header() + body(xxx_data) + footer(); }

    std::string ToString(std::vector<XxxData> const& xxx_datas) const
    {
        auto ret = std::string{header()};

        for (auto const& xxx_data : xxx_datas) {
            ret += body(xxx_data);
        }

        return ret + footer();
    }

private:
    virtual std::string const& header() const                      = 0;
    virtual std::string const& footer() const                      = 0;
    virtual std::string        body(XxxData const& xxx_data) const = 0;
};

class XxxDataFormatterXml final : public XxxDataFormatterIF {
public:
    XxxDataFormatterXml()                   = default;
    virtual ~XxxDataFormatterXml() override = default;

private:
    virtual std::string const& header() const override
    {
        static auto const header = std::string{"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<XxxDataFormatterXml>\n"};

        return header;
    }

    virtual std::string const& footer() const override
    {
        static auto const footer = std::string{"</XxxDataFormatterXml>\n"};

        return footer;
    }

    virtual std::string body(XxxData const& xxx_data) const override
    {
        auto content = std::string{"<Item>\n"};

        content += "    <XxxData a=\"" + std::to_string(xxx_data.a) + "\">\n";
        content += "    <XxxData b=\"" + std::to_string(xxx_data.b) + "\">\n";
        content += "    <XxxData c=\"" + std::to_string(xxx_data.c) + "\">\n";

        return content + "</Itemp>\n";
    }
};

class XxxDataFormatterCsv final : public XxxDataFormatterIF {
public:
    XxxDataFormatterCsv()                   = default;
    virtual ~XxxDataFormatterCsv() override = default;

private:
    virtual std::string const& header() const override
    {
        static auto const header = std::string{"a, b, c\n"};

        return header;
    }

    virtual std::string const& footer() const override
    {
        static auto const footer = std::string{};

        return footer;
    }

    virtual std::string body(XxxData const& xxx_data) const override
    {
        return std::string{std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
                           + std::to_string(xxx_data.b) + "\n"};
    }
};

TEST(DesignPatternA, TemplateMethod)
{
    auto xml = XxxDataFormatterXml{};
    {
        auto const expect_scalar = std::string{
            "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
            "<XxxDataFormatterXml>\n"
            "<Item>\n"
            "    <XxxData a=\"1\">\n"
            "    <XxxData b=\"100\">\n"
            "    <XxxData c=\"10\">\n"
            "</Itemp>\n"
            "</XxxDataFormatterXml>\n"};
        auto const actual_scalar = xml.ToString({1, 100, 10});
        ASSERT_EQ(expect_scalar, actual_scalar);

        auto const expect_array = std::string{
            "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
            "<XxxDataFormatterXml>\n"
            "<Item>\n"
            "    <XxxData a=\"1\">\n"
            "    <XxxData b=\"100\">\n"
            "    <XxxData c=\"10\">\n"
            "</Itemp>\n"
            "<Item>\n"
            "    <XxxData a=\"2\">\n"
            "    <XxxData b=\"200\">\n"
            "    <XxxData c=\"20\">\n"
            "</Itemp>\n"
            "</XxxDataFormatterXml>\n"};
        auto const actual_array = xml.ToString({{1, 100, 10}, {2, 200, 20}});
        ASSERT_EQ(expect_array, actual_array);
    }

    auto csv = XxxDataFormatterCsv{};
    {
        auto expect_scalar = std::string{
            "a, b, c\n"
            "1, 100, 100\n"};
        auto const actual_scalar = csv.ToString({1, 100, 10});
        ASSERT_EQ(expect_scalar, actual_scalar);

        auto const expect_array = std::string{
            "a, b, c\n"
            "1, 100, 100\n"
            "2, 200, 200\n"};
        auto const actual_array = csv.ToString({{1, 100, 10}, {2, 200, 20}});
        ASSERT_EQ(expect_array, actual_array);
    }
}
// @@@ sample end
}  // namespace
