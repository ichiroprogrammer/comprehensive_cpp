#pragma once
#include <memory>
#include <string>
#include <vector>

namespace DesignPatternA_Factory {

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

// @@@ sample begin 0:0
// [A]
// 下記クラスXxxDataFormatterXml、XxxDataFormatterCsvはヘッダファイルで宣言・定義を行ったために
// 他の.cppファイルから直接アクセスできてしまう。
// Factoryパターンを用いて、XxxDataFormatterXml、XxxDataFormatterCsvを他の.cppファイルから
// 直接アクセスできないようにせよ。

// [解説]
// 一般的には、Factory関数は
//      std::unique_ptr<XxxDataFormatterIF> XxxDataFormatterFactory(XxxDataFormatterType type);
// のような形状になるが、今回の例では生成オブジェクトの提供するサービスがconst関数のみであるため、
// constなunique_ptrを返している。
// また、さらにこの考え方を進め、newしてオブジェクトの生成をする必要はないことに気づけば、
// XxxDataFormatterFactory2のようにconstリファレンスを返すこともできる。

enum class XxxDataFormatterType { Xml, Csv };

std::unique_ptr<XxxDataFormatterIF const> XxxDataFormatterFactory(XxxDataFormatterType type);
XxxDataFormatterIF const&                 XxxDataFormatterFactory2(XxxDataFormatterType type) noexcept;
// @@@ sample end
}  // namespace DesignPatternA_Factory
