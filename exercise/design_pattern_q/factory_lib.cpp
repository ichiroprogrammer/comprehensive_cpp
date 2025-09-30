#include "factory_lib.h"

namespace DesignPatternQ_Factory {

// @@@ sample begin 0:0

std::string const& XxxDataFormatterXml::header() const
{
    static auto const header = std::string{"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<XxxDataFormatterXml>\n"};

    return header;
}

std::string const& XxxDataFormatterXml::footer() const
{
    static auto const footer = std::string{"</XxxDataFormatterXml>\n"};

    return footer;
}

std::string XxxDataFormatterXml::body(XxxData const& xxx_data) const
{
    auto content = std::string{"<Item>\n"};

    content += "    <XxxData a=\"" + std::to_string(xxx_data.a) + "\">\n";
    content += "    <XxxData b=\"" + std::to_string(xxx_data.b) + "\">\n";
    content += "    <XxxData c=\"" + std::to_string(xxx_data.c) + "\">\n";

    return content + "</Itemp>\n";
}

std::string const& XxxDataFormatterCsv::header() const
{
    static auto const header = std::string{"a, b, c\n"};

    return header;
}

std::string const& XxxDataFormatterCsv::footer() const
{
    static auto const footer = std::string{};

    return footer;
}

std::string XxxDataFormatterCsv::body(XxxData const& xxx_data) const
{
    return std::string{std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
                       + std::to_string(xxx_data.b) + "\n"};
}
// @@@ sample end
}  // namespace DesignPatternQ_Factory
