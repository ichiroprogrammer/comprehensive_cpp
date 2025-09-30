#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記クラスXxxDataFormatterXml、XxxDataFormatterCsvは同様の処理を行い、
// それぞれのフォーマットで文字列を出力する。このような処理のクローンはTemplate Method
// パターンにより排除できる。
// このパターンを用い、下記2クラスをリファクタリングせよ。
// また、他の問題があれば合わせて修正せよ。

struct XxxData {
    int a;
    int b;
    int c;
};

class XxxDataFormatterXml {
public:
    XxxDataFormatterXml() = default;

    std::string ToString(XxxData const& xxx_data) const
    {
        auto body = std::string{"<Item>\n"};

        body += "    <XxxData a=\"" + std::to_string(xxx_data.a) + "\">\n";
        body += "    <XxxData b=\"" + std::to_string(xxx_data.b) + "\">\n";
        body += "    <XxxData c=\"" + std::to_string(xxx_data.c) + "\">\n";
        body += "</Itemp>\n";

        return header_ + body + footer_;
    }

    std::string ToString(std::vector<XxxData> const& xxx_datas) const
    {
        auto ret = std::string{header_};

        for (auto const& xxx_data : xxx_datas) {
            ret += "<Item>\n";
            ret += "    <XxxData a=\"" + std::to_string(xxx_data.a) + "\">\n";
            ret += "    <XxxData b=\"" + std::to_string(xxx_data.b) + "\">\n";
            ret += "    <XxxData c=\"" + std::to_string(xxx_data.c) + "\">\n";
            ret += "</Itemp>\n";
        }

        return ret + footer_;
    }

private:
    std::string header_ = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<XxxDataFormatterXml>\n";
    std::string footer_ = "</XxxDataFormatterXml>\n";
};

class XxxDataFormatterCsv {
public:
    XxxDataFormatterCsv() = default;

    std::string ToString(XxxData const& xxx_data) const
    {
        auto body = std::string{std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
                                + std::to_string(xxx_data.b) + "\n"};

        return header_ + body;
    }

    std::string ToString(std::vector<XxxData> const& xxx_datas) const
    {
        auto ret = std::string{header_};

        for (auto const& xxx_data : xxx_datas) {
            ret += std::string{std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
                               + std::to_string(xxx_data.b) + "\n"};
        }

        return ret;
    }

private:
    std::string const header_ = "a, b, c\n";
};

TEST(DesignPatternQ, TemplateMethod)
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
