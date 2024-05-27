#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

#include "suppress_warning.h"

namespace NamingRule {
void f() noexcept
{
    // clang-format off
    // @@@ sample begin 0:0

    int32_t     _max;           // NG
    int32_t     max;            // OK
    void        _func();        // NG
    void        func();         // OK

    #define     _FOO_BAR_H_     // NG
    #define     FOO_BAR_H_      // OK
    // @@@ sample end
    // clang-format on
    IGNORE_UNUSED_VAR(_max, max);

    // @@@ sample begin 0:1

    int32_t s32_read_counter;  // NG
    int32_t read_counter;      // OK
    // @@@ sample end
    IGNORE_UNUSED_VAR(s32_read_counter, read_counter);

    // @@@ sample begin 0:2

    int32_t name1;         // NG
    int32_t name2;         // NG
    int32_t utf16code;     // OK
    int32_t storage1K;     // OK
    bool    image1_onoff;  // image1が正式な名前ならOK
    // @@@ sample end
    IGNORE_UNUSED_VAR(name1, name2, utf16code, storage1K, image1_onoff);

    // @@@ sample begin 0:3

    int32_t acnt;            // NG
    int32_t account;         // OK
    int32_t sig_handler;     // NG
    int32_t signal_handler;  // OK

    // その他やってしまいがちな例
    // ctrl     ->  control
    // no       -> number
    // ttl      -> total
    // cb       -> callback
    // fn       -> function, func
    // @@@ sample end
    IGNORE_UNUSED_VAR(acnt, account, sig_handler, signal_handler);
}
}  // namespace NamingRule
// @@@ sample begin 1:0

// NGの例 一見同じに見える
class XxxCallBack {
    // @@@ ignore begin
    // @@@ ignore end
};

class XxxCallback {
    // @@@ ignore begin
    // @@@ ignore end
};
// @@@ sample end

// @@@ sample begin 2:0

class XxxController;                     // OK
class xxx_control;                       // NG
struct SomeStruct;                       // OK
enum class SomeEnumeration;              // OK
enum class some_enumeration;             // OK
using Container = std::vector<int32_t>;  // OK
class TCP_IP;                            // OK
// @@@ sample end
SUPPRESS_WARN_BEGIN;
SUPPRESS_WARN_CLANG_UNUSED_CONST_VAR;
SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD;
// @@@ sample begin 3:0

constexpr int SOME_CONSTANT{0};  // NG  定数
constexpr int SomeConstant{0};   // OK  定数

struct Xxx {
    static constexpr int SOME_CONSTANT{0};  // NG  定数
    static constexpr int SomeConstant{0};   // OK  定数
};

template <typename T>
constexpr bool IsSameAsXxxV = std::is_same_v<Xxx, T>;  // OK 定数テンプレート
// @@@ sample end

static_assert(IsSameAsXxxV<Xxx>);
static_assert(!IsSameAsXxxV<int>);
// @@@ sample begin 4:0

class Foo {
private:
    int32_t read_counter;   // NG
    int32_t read_counter_;  // OK
    int32_t m_ReadCounter;  // NG
};

struct Hoo {
    int32_t bar;   // OK
    int32_t bar_;  // NG
};
// @@@ sample end
SUPPRESS_WARN_END;
// @@@ sample begin 5:0

enum class SignalType {
    RED,    // NG
    Green,  // OK
    yellow  // NG
};
// @@@ sample end
// @@@ sample begin 6:0

class Fee {
public:
    void PrintMessage();   // OK
    void Print_Message();  // NG _は不要
    bool WatchdogExit();   // NG ExitByWatchdog等の方が良い
    bool DoSomething();    // OK
    bool doSomething();    // NG

private:
    bool print_system_message_async();  // OK privateで非同期
    void do_something();                // OK
};
// @@@ sample end
// @@@ sample begin 7:0

class Fii {
public:
    int32_t GetFoo() const noexcept;      // OK 変数の値の取得
    void    SetFoo(int32_t foo) noexcept  // OK 変数に値を設定
    {
        foo_ = foo;  // OK setterの仮引数はメンバ名から'\_'を除いたもの
    }

    bool IsCurrency() const noexcept;        // OK bool値の問い合わせ
    bool IsGettableMemory() const noexcept;  // OK
    bool HasHoge() const noexcept;           // OK
    bool CanGet() const noexcept;            // OK
    bool CheckHoge() const noexcept;         // NG true/falseの意味が明確でない

private:
    int32_t foo_;
};
// @@@ sample end
// @@@ sample begin 8:0

class StringCollector {  // OK 文字列の集合を扱うことを示す
public:
    std::vector<std::string> const& GetStrings() const;  // OK 戻り値が集合であることを示す
    // clang-format off
    std::vector<std::string> const& GetString() const;   // NG 複数形にしてvectorであることを
                                                         //    示すべき
    // clang-format on
private:
    std::vector<std::string> strings_;  // OK インスタンスが集合であることを示す
    std::vector<std::string> string_;   // NG
};
// @@@ sample end

// @@@ sample begin 8:1

// 下記例のXXX_YYY_R0は、XXX回路のYYYサブ回路のR0レジスタを表す。
volatile auto& XXX_YYY_R0 = *reinterpret_cast<uint32_t*>(0x1300'0000);
volatile auto& XXX_YYY_R1 = *reinterpret_cast<uint32_t*>(0x1300'0100);
volatile auto& XXX_YYY_Q0 = *reinterpret_cast<uint32_t*>(0x1300'0200);
volatile auto& XXX_ZZZ_R0 = *reinterpret_cast<uint32_t*>(0x1400'0200);
// @@@ sample end
// @@@ sample begin 8:2

// OK DataFormatterという概念のインターフェース クラス
class DataFormatterIF {
    // @@@ ignore begin
public:
    virtual ~DataFormatterIF() = default;
    // @@@ ignore end
};

// OK DataFormatterという概念の具象クラスDataFormatterXml。XmlDataFormatterとしない。
class DataFormatterXml final : public DataFormatterIF {
    // @@@ ignore begin
    // @@@ ignore end
};

// OK DataFormatterという概念の具象クラスDataFormatterCsv。CsvDataFormatterとしない。
class DataFormatterCsv final : public DataFormatterIF {
    // @@@ ignore begin
    // @@@ ignore end
};
// @@@ sample end
