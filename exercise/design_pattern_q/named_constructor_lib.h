#pragma once
#include <memory>
#include <string>
#include <vector>

namespace DesignPatternQ_NamedConstructor {

struct XxxData {
    int a;
    int b;
    int c;
};

// @@@ sample begin 0:0
// [Q]
// 下記関数XxxDataFormatterFactoryはインターフェースクラスXxxDataFormatterIFのファクトリ関数
// である。これをnamed constructorパターンで実装しなおせ。

class XxxDataFormatterIF {
public:
    XxxDataFormatterIF() noexcept                            = default;
    virtual ~XxxDataFormatterIF()                            = default;
    XxxDataFormatterIF(XxxDataFormatterIF const&)            = delete;
    XxxDataFormatterIF& operator=(XxxDataFormatterIF const&) = delete;

    std::string ToString(XxxData const& xxx_data) const
    {
        return header() + body(xxx_data) + footer();
    }

    std::string ToString(std::vector<XxxData> const& xxx_datas) const
    {
        auto ret = header();

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

enum class XxxDataFormatterType { Xml, Csv, Table };

XxxDataFormatterIF const& XxxDataFormatterFactory(XxxDataFormatterType type) noexcept;
// @@@ sample end
}  // namespace DesignPatternQ_NamedConstructor
