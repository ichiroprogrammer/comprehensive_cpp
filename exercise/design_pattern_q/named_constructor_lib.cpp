#include <cassert>

#include "named_constructor_lib.h"

namespace DesignPatternQ_NamedConstructor {

namespace {
class XxxDataFormatterXml final : public XxxDataFormatterIF {
public:
    XxxDataFormatterXml() noexcept          = default;
    virtual ~XxxDataFormatterXml() override = default;

private:
    virtual std::string const& header() const override
    {
        static auto const header
            = std::string{"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<XxxDataFormatterXml>\n"};

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
    XxxDataFormatterCsv() noexcept          = default;
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
        return std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
               + std::to_string(xxx_data.b) + "\n";
    }
};

class XxxDataFormatterTable final : public XxxDataFormatterIF {
public:
    XxxDataFormatterTable() noexcept          = default;
    virtual ~XxxDataFormatterTable() override = default;

private:
    virtual std::string const& header() const override
    {
        static auto const header = border() + "| a      | b      | c      |\n" + border();
        return header;
    }

    virtual std::string const& footer() const override
    {
        static auto const footer = std::string{};
        return footer;
    }

    virtual std::string body(XxxData const& xxx_data) const override
    {
        auto a = std::string{"| "} + std::to_string(xxx_data.a);
        auto b = std::string{"| "} + std::to_string(xxx_data.b);
        auto c = std::string{"| "} + std::to_string(xxx_data.c);

        a += std::string(colomun_ - a.size() + 1, ' ');
        b += std::string(colomun_ - b.size() + 1, ' ');
        c += std::string(colomun_ - c.size() + 1, ' ');

        static std::string const border_str = border();

        return a + b + c + "|\n" + border_str;
    }

    static std::string border()
    {
        static auto const border_str = std::string{"+"} + std::string(colomun_, '-') + "|"
                                       + std::string(colomun_, '-') + "|"
                                       + std::string(colomun_, '-') + "+\n";

        return border_str;
    }

    static constexpr size_t colomun_{8};
};
}  // namespace

// @@@ sample begin 0:0

XxxDataFormatterIF const& XxxDataFormatterFactory(XxxDataFormatterType type) noexcept
{
    static auto const xml   = XxxDataFormatterXml{};
    static auto const csv   = XxxDataFormatterCsv{};
    static auto const table = XxxDataFormatterTable{};

    switch (type) {
    case XxxDataFormatterType::Xml:
        return xml;
    case XxxDataFormatterType::Csv:
        return csv;
    case XxxDataFormatterType::Table:
        return table;
    default:
        assert("unknown type");
        return csv;
    }
}
// @@@ sample end
}  // namespace DesignPatternQ_NamedConstructor
