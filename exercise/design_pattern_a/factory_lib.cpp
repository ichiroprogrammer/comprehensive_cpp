#include <cassert>

#include "factory_lib.h"

namespace DesignPatternA_Factory {

namespace {
class XxxDataFormatterXml final : public XxxDataFormatterIF {
public:
    XxxDataFormatterXml() noexcept          = default;
    virtual ~XxxDataFormatterXml() override = default;

private:
    virtual std::string const& header() const noexcept override;
    virtual std::string const& footer() const noexcept override;
    virtual std::string        body(XxxData const& xxx_data) const override;
};

std::string const& XxxDataFormatterXml::header() const noexcept
{
    static auto const header = std::string{"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<XxxDataFormatterXml>\n"};

    return header;
}

std::string const& XxxDataFormatterXml::footer() const noexcept
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

class XxxDataFormatterCsv final : public XxxDataFormatterIF {
public:
    XxxDataFormatterCsv() noexcept          = default;
    virtual ~XxxDataFormatterCsv() override = default;

private:
    virtual std::string const& header() const noexcept override;
    virtual std::string const& footer() const noexcept override;
    virtual std::string        body(XxxData const& xxx_data) const override;
};

std::string const& XxxDataFormatterCsv::header() const noexcept
{
    static auto const header = std::string{"a, b, c\n"};

    return header;
}

std::string const& XxxDataFormatterCsv::footer() const noexcept
{
    static auto const footer = std::string{};

    return footer;
}

std::string XxxDataFormatterCsv::body(XxxData const& xxx_data) const
{
    return std::string{std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
                       + std::to_string(xxx_data.b) + "\n"};
}
}  // namespace

// @@@ sample begin 0:0

std::unique_ptr<XxxDataFormatterIF const> XxxDataFormatterFactory(XxxDataFormatterType type)
{
    switch (type) {
    case XxxDataFormatterType::Xml:
        return std::make_unique<XxxDataFormatterXml>();
    case XxxDataFormatterType::Csv:
        return std::make_unique<XxxDataFormatterCsv>();
    default:
        assert("unknown type");
        return std::unique_ptr<XxxDataFormatterIF const>{};
    }
}

XxxDataFormatterIF const& XxxDataFormatterFactory2(XxxDataFormatterType type) noexcept
{
    static auto const xml = XxxDataFormatterXml{};
    static auto const csv = XxxDataFormatterCsv{};

    switch (type) {
    case XxxDataFormatterType::Xml:
        return xml;
    case XxxDataFormatterType::Csv:
        return csv;
    default:
        assert("unknown type");
        return csv;
    }
}
// @@@ sample end
}  // namespace DesignPatternA_Factory
