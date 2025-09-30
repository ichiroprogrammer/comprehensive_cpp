#pragma once
#include <memory>
#include <string>
#include <vector>

namespace DesignPatternA_NamedConstructor {

struct XxxData {
    int a;
    int b;
    int c;
};

// @@@ sample begin 0:0
// [A]
// 下記関数XxxDataFormatterFactoryはインターフェースクラスXxxDataFormatterIFのファクトリ関数
// である。これをnamed constructorパターンで実装しなおせ。

// [解説]
// * XxxDataFormatterIFの特性から、Named ConstructorはXxxDataFormatterIFのconstリファレンスを返す
//   仕様としたが、戻すオブジェクトの特性より戻り値型は以下のようにすべき。
//
//      const/非const | 静的/動的 | 戻す型
//      --------------+-----------+-----------------------------------
//      const         | 静的      | XxxDataFormatterIFのconstリファレンス
//                    | 動的      | std::unique_ptr<const XxxDataFormatterIF>
//      非const       | 静的      | XxxDataFormatterIFのリファレンス
//                    | 動的      | std::unique_ptr<XxxDataFormatterIF>
//
// * FactoryとNamed Constructorはほぼ等価であり、どちらを使っても派生型の隠蔽という効果は等しい。
// * 筆者は、今回の例のように静的オブジェクトを返す場合、Named Constructor、
//   動的オブジェクトを返す場合、Factoryを使用している。

class XxxDataFormatterIF {
public:
    XxxDataFormatterIF() = default;
    static XxxDataFormatterIF const& Xml() noexcept;
    static XxxDataFormatterIF const& Csv() noexcept;
    static XxxDataFormatterIF const& Table() noexcept;

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
// @@@ sample end
}  // namespace DesignPatternA_NamedConstructor
