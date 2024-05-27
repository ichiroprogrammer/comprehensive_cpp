#pragma once
#include <string>
#include <vector>

namespace DesignPatternQ_Factory {
// @@@ sample begin 0:0
// [Q]
// 下記クラスXxxDataFormatterXml、XxxDataFormatterCsvはヘッダファイルで宣言・定義を行ったために
// 他の.cppファイルから直接アクセスできてしまう。
// Factoryパターンを用いて、XxxDataFormatterXml、XxxDataFormatterCsvを他の.cppファイルから
// 直接アクセスできないようにせよ。

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

class XxxDataFormatterXml final : public XxxDataFormatterIF {
public:
    XxxDataFormatterXml()                   = default;
    virtual ~XxxDataFormatterXml() override = default;

private:
    virtual std::string const& header() const override;
    virtual std::string const& footer() const override;
    virtual std::string        body(XxxData const& xxx_data) const override;
};

class XxxDataFormatterCsv final : public XxxDataFormatterIF {
public:
    XxxDataFormatterCsv()                   = default;
    virtual ~XxxDataFormatterCsv() override = default;

private:
    virtual std::string const& header() const override;
    virtual std::string const& footer() const override;
    virtual std::string        body(XxxData const& xxx_data) const override;
};
// @@@ sample end
}  // namespace DesignPatternQ_Factory
