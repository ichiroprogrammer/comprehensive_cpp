#include "gtest_wrapper.h"

#include "factory_lib.h"

using namespace DesignPatternQ_Factory;

namespace {

// @@@ sample begin 0:0

TEST(DesignPatternQ, Factory)
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
    }

    auto csv = XxxDataFormatterCsv{};
    {
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
