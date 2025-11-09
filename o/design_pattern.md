<!-- essential/md/design_pattern.md -->
# デザインパターン <a id="SS_9"></a>
ソースコードを劣化させるアンチパターンには、

* 大きすぎる関数、クラス、ファイル等のソフトウェア構成物
* 複雑怪奇な依存関係
* コードクローン

等があるだろう。
こういった問題は、ひどいソースコードを書かないという強い意志を持ったプログラマの不断の努力と、
そのプログラマを支えるソフトウェア工学に基づいた知識によって回避可能である。
本章ではその知識の一翼をになうデザインパターン、イデオム等を解説、例示する。

なお、ここに挙げるデザインパターン、イデオム等は「適切な場所に適用される場合、
ソースコードをよりシンプルに記述できる」というメリットがある一方で、
「不適切な場所に適用される場合、ソースコードの複雑度を不要に上げてしまう」
という負の一面を持つ。

また、デザインパターン、イデオム等を覚えたてのプログラマは、
自分のスキルが上がったという一種の高揚感や顕示欲を持つため、
それをむやみやたらに多用してしまう状態に陥ることある。このようなプログラマの状態を 

* パターン病に罹患した
* パターン猿になった、もしくは単に、猿になった  

と呼ぶ。
猿になり不要に複雑なソースコードを書かないために、デザインパターン、イデオム等を使用する場合、
本当にそれが必要か吟味し、不要な場所への適用を避けなければならない。

___

__この章の構成__

&emsp;&emsp; [ガード節](design_pattern.md#SS_9_1)  
&emsp;&emsp; [BitmaskType](design_pattern.md#SS_9_2)  
&emsp;&emsp; [Pimpl](design_pattern.md#SS_9_3)  
&emsp;&emsp; [lightweight Pimpl](design_pattern.md#SS_9_4)  
&emsp;&emsp; [Accessor](design_pattern.md#SS_9_5)  
&emsp;&emsp; [Copy-And-Swap](design_pattern.md#SS_9_6)  
&emsp;&emsp; [Immutable](design_pattern.md#SS_9_7)  
&emsp;&emsp; [Clone(仮想コンストラクタ)](design_pattern.md#SS_9_8)  
&emsp;&emsp; [NVI(non virtual interface)](design_pattern.md#SS_9_9)  
&emsp;&emsp; [RAII(scoped guard)](design_pattern.md#SS_9_10)  
&emsp;&emsp; [Future](design_pattern.md#SS_9_11)  
&emsp;&emsp; [DI(dependency injection)](design_pattern.md#SS_9_12)  
&emsp;&emsp; [Singleton](design_pattern.md#SS_9_13)  
&emsp;&emsp; [State](design_pattern.md#SS_9_14)  
&emsp;&emsp; [Null Object](design_pattern.md#SS_9_15)  
&emsp;&emsp; [Templateメソッド](design_pattern.md#SS_9_16)  
&emsp;&emsp; [Factory](design_pattern.md#SS_9_17)  
&emsp;&emsp; [Named Constructor](design_pattern.md#SS_9_18)  
&emsp;&emsp; [Proxy](design_pattern.md#SS_9_19)  
&emsp;&emsp; [Strategy](design_pattern.md#SS_9_20)  
&emsp;&emsp; [Visitor](design_pattern.md#SS_9_21)  
&emsp;&emsp; [CRTP(curiously recurring template pattern)](design_pattern.md#SS_9_22)  
&emsp;&emsp; [Observer](design_pattern.md#SS_9_23)  
&emsp;&emsp; [MVC](design_pattern.md#SS_9_24)  
&emsp;&emsp; [Cでのクラス表現](design_pattern.md#SS_9_25)  
  
  

[インデックス](introduction.md#SS_1_4)に戻る。  
___

## ガード節 <a id="SS_9_1"></a>
ガード節とは、
「可能な場合、処理を早期に打ち切るために関数やループの先頭に配置される短い条件文(通常はif文)」
であり、以下のような利点がある。

* 処理の打ち切り条件が明確になる。
* 関数やループのネストが少なくなる。

まずは、ガード節を使っていない例を上げる。

```cpp
    //  example/design_pattern/guard_ut.cpp 24

    /// @brief a(配列へのリファレンス)の要素について、先頭から'a'が続く数を返す
    /// @param 配列へのリファレンス
    int32_t SequentialA(char const (&a)[3]) noexcept
    {
        if (a[0] == 'a') {
            if (a[1] == 'a') {
                if (a[2] == 'a') {
                    return 3;
                }
                else {
                    return 2;
                }
            }
            else {
                return 1;
            }
        }
        else {
            return 0;
        }
    }
```

上記の例を読んで一目で何が行われているか、理解できる人は稀である。
一方で、上記と同じロジックである下記関数を一目で理解できない人も稀である。

```cpp
    //  example/design_pattern/guard_ut.cpp 77

    int32_t SequentialA(char const (&a)[3]) noexcept
    {
        if (a[0] != 'a') {  // ガード節
            return 0;
        }
        if (a[1] != 'a') {  // ガード節
            return 1;
        }
        if (a[2] != 'a') {  // ガード節
            return 2;
        }

        return 3;
    }
```

ここまで効果的な例はあまりない。

もう一例、(ガード節導入の効果が前例ほど明確でない)ガード節を使っていないコードを示す。

```cpp
    //  example/design_pattern/guard_ut.cpp 48

    std::optional<std::vector<uint32_t>> PrimeNumbers(uint32_t max_num)
    {
        auto result = std::vector<uint32_t>{};

        if (max_num < 65536) {  // 演算コストが高いためエラーにする
            if (max_num >= 2) {
                auto is_num_prime = std::vector<bool>(max_num + 1, true);  // falseなら素数でない
                is_num_prime[0] = is_num_prime[1] = false;
                auto prime_num                    = 2U;  // 最初の素数

                do {
                    result.emplace_back(prime_num);
                    prime_num = next_prime_num(prime_num, is_num_prime);
                } while (prime_num < is_num_prime.size());
            }

            return result;
        }

        return std::nullopt;
    }
```

上記にガード節を適用した例を下記する。

```cpp
    //  example/design_pattern/guard_ut.cpp 94

    std::optional<std::vector<uint32_t>> PrimeNumbers(uint32_t max_num)
    {
        if (max_num >= 65536) {  // ガード節。演算コストが高いためエラーにする。
            return std::nullopt;
        }

        auto result = std::vector<uint32_t>{};

        if (max_num < 2) {  // ガード節。2未満の素数はない。
            return result;
        }

        auto is_num_prime = std::vector<bool>(max_num + 1, true);  // falseなら素数でない。
        is_num_prime[0] = is_num_prime[1] = false;
        auto prime_num                    = 2U;  // 最初の素数

        do {
            result.emplace_back(prime_num);
            prime_num = next_prime_num(prime_num, is_num_prime);
        } while (prime_num < is_num_prime.size());

        return result;
    }
```

ガード節を使っていない例に比べて、

* ネストが減って読みやすくなった
* max_numが1, 2, 65535, 65536である場合がロジックの境界値であることが一目でわかるようになった

といった改善はされたものの、最初の例ほどのレベル差はない。
しかし、ソースコードの改善やリファクタリングのほとんどは、このようなものであり、
この少しのレベルアップが数か月後、数年後に大きな差を生み出すことを忘れてはならない。

[演習-ガード節](exercise_q.md#SS_22_9_1)  

## BitmaskType <a id="SS_9_2"></a>
下記のようなビットマスク表現は誤用しやすいインターフェースである。
修正や拡張等に関しても脆弱であるため、避けるべきである。

```cpp
    //  example/design_pattern/enum_operator.h 6

    class Animal {
    public:
        struct PhisicalAbility {  // オブジェクトの状態を表すためのビットマスク
            static constexpr auto Run  = 0b0001U;
            static constexpr auto Fly  = 0b0010U;
            static constexpr auto Swim = 0b0100U;
        };

        // paにはPhisicalAbilityのみを受け入れたいが、実際にはすべてのuint32_tを受け入れる。
        explicit Animal(uint32_t pa) noexcept : phisical_ability_{pa} {}

        uint32_t GetPhisicalAbility() const noexcept { return phisical_ability_; }
        // ...
    };
```

```cpp
    //  example/design_pattern/enum_operator_ut.cpp 13

    Animal dolphin{Animal::PhisicalAbility::Swim};  // OK
    ASSERT_EQ(Animal::PhisicalAbility::Swim, dolphin.GetPhisicalAbility());

    Animal uma{0xff};  // NG 誤用だが、コンストラクタの仮引数の型がuint32_tなのでコンパイル可能
```

上記のような誤用を防ぐために、
enumによるビットマスク表現を使用して型チェックを強化した例を以下に示す。
このテクニックは、STLのインターフェースとしても使用されている強力なイデオムである。

```cpp
    //  example/design_pattern/enum_operator.h 30

    class Animal {
    public:
        enum class PhisicalAbility : uint32_t {
            Run  = 0b0001,
            Fly  = 0b0010,
            Swim = 0b0100,
        };

        explicit Animal(PhisicalAbility pa) noexcept : phisical_ability_{pa} {}

        PhisicalAbility GetPhisicalAbility() const noexcept { return phisical_ability_; }

    private:
        PhisicalAbility const phisical_ability_;
    };

    // &, | &=, |=, IsTrue, IsFalseの定義
    constexpr Animal::PhisicalAbility operator&(Animal::PhisicalAbility x, Animal::PhisicalAbility y) noexcept
    {
        return static_cast<Animal::PhisicalAbility>(static_cast<uint32_t>(x) & static_cast<uint32_t>(y));
    }

    constexpr Animal::PhisicalAbility operator|(Animal::PhisicalAbility x, Animal::PhisicalAbility y) noexcept
    {
        return static_cast<Animal::PhisicalAbility>(static_cast<uint32_t>(x) | static_cast<uint32_t>(y));
    }

    inline Animal::PhisicalAbility& operator&=(Animal::PhisicalAbility& x, Animal::PhisicalAbility y) noexcept
    {
        return x = x & y;
    }

    // ...
```

```cpp
    //  example/design_pattern/enum_operator_ut.cpp 28

    // コンストラクタの仮引数の型が厳密になったためコンパイル不可
    // これにより誤用を防ぐ
    // Animal uma{0xff};

    // C++17から下記はコンパイル可能となったが、アクシデントでこのようなミスはしないだろう
    auto uma = Animal{Animal::PhisicalAbility{0xff}};

    auto dolphin = Animal{Animal::PhisicalAbility::Swim};
    ASSERT_EQ(Animal::PhisicalAbility::Swim, dolphin.GetPhisicalAbility());

    auto pa = Animal::PhisicalAbility{Animal::PhisicalAbility::Run};
    pa |= Animal::PhisicalAbility::Swim;

    auto human = Animal{pa};
    ASSERT_TRUE(IsTrue(Animal::PhisicalAbility::Run & human.GetPhisicalAbility()));
```

この改善により、Animalのコンストラクタに域値外の値を渡すことは困難になった
(少なくとも不注意で間違うことはないだろう)。
この修正の延長で、Animal::GetPhisicalAbility()の戻り値もenumになり、これも誤用が難しくなった。

[演習-BitmaskType](exercise_q.md#SS_22_9_2)  

## Pimpl <a id="SS_9_3"></a>
このパターンは、「クラスA(a.cpp、a.hで宣言、定義)を使用するクラスにAの実装の詳細を伝搬させたくない」
ような場合に使用する。
そのため[オープン・クローズドの原則(OCP)](solid.md#SS_8_2)の実装方法としても有用である。

一般的に、STLライブラリのパースは多くのCPUタイムを消費する。
クラスAがSTLクラスをメンバに使用し、a.hにそのSTLヘッダファイルがインクルードされた場合、
a.hをインクルードするファイルをコンパイルする度にそのSTLヘッダファイルはパースされる。
これはさらに多くのCPUタイムの消費につながり、ソースコード全体のビルドは遅くなる。
こういった問題をあらかじめ避けるためにも有効な手段ではあるが、
そのトレードオフとして実行速度は若干遅くなる。

下記は、Pimplイデオム未使用の、std::stringに依存したクラスStringHolderOldの例である。

```cpp
    //  example/design_pattern/string_holder_old.h 3
    // このファイルには<string>が必要

    #include <memory>
    #include <string>

    class StringHolderOld final {
    public:
        StringHolderOld();

        void        Add(char const* str);
        char const* GetStr() const;

    private:
        std::unique_ptr<std::string> str_;
    };
```

```cpp
    //  example/design_pattern/string_holder_old.cpp 1

    #include "string_holder_old.h"

    StringHolderOld::StringHolderOld() : str_{std::make_unique<std::string>()} {}

    void StringHolderOld::Add(char const* str) { *str_ += str; }

    char const* StringHolderOld::GetStr() const { return str_->c_str(); }
```


下記は、上記クラスStringHolderOldにPimplイデオムを適用したクラスStringHolderNewの例である。

```cpp
    //  example/design_pattern/string_holder_new.h 3
    // このファイルには<string>は不要

    #include <memory>

    class StringHolderNew final {
    public:
        StringHolderNew();

        void        Add(char const* str);
        char const* GetStr() const;
        ~StringHolderNew();  // デストラクタは.cppで=defaultで定義

    private:
        class StringHolderNewCore;  // StringHolderNewの振る舞いは、StringHolderNewCoreに移譲
        std::unique_ptr<StringHolderNewCore> core_;
    };
```

```cpp
    //  example/design_pattern/string_holder_new.cpp 1
    // このファイルには<string>が必要

    #include <string>

    #include "string_holder_new.h"

    class StringHolderNew::StringHolderNewCore final {
    public:
        StringHolderNewCore() = default;
        void Add(char const* str) { str_ += str; }

        char const* GetStr() const noexcept { return str_.c_str(); }

    private:
        std::string str_{};
    };

    StringHolderNew::StringHolderNew() : core_{std::make_unique<StringHolderNewCore>()} {}

    void StringHolderNew::Add(char const* str) { core_->Add(str); }

    char const* StringHolderNew::GetStr() const { return core_->GetStr(); }

    // この宣言、定義をしないと、StringHolderNewをインスタンス化した場所では、
    // StringHolderNewCoreが不完全型であるため、std::unique_ptrが実体化できず、コンパイルエラーとなる。
    // この場所であれば、StringHolderNewCoreは完全型であるためstd::unique_ptrが実体化できる。
    StringHolderNew::~StringHolderNew() = default;
```

下記図は、上記ファイルやそれらを使用するファイルの依存関係である。
string_holder_old.hは、std::stringに依存しているが、string_holder_new.hは、
std::stringに依存していないこと、
それによってStringHolderNewを使用するファイルから、std::stringへの依存を排除できていることがわかる。

<!-- pu:essential/plant_uml/pimpl_pattern.pu--><p><img src="data:image/png;base64,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" /></p>

このパターンを使用して問題のある依存関係をリファクタリングする例を示す。

まずは、リファクタリング前のコードを下記する。

```cpp
    // in lib/h/widget.h

    #include "gtest/gtest.h"

    class Widget {
    public:
        void     DoSomething();
        uint32_t GetValue() const;
        // 何らかの宣言

    private:
        uint32_t gen_xxx_data(uint32_t a);
        uint32_t xxx_data_{1};
        FRIEND_TEST(Pimpl, widget_ng);  // 単体テストをfriendにする
    };
```
```cpp
    // in lib/src/widget.cpp

    #include "widget.h"

    void Widget::DoSomething()
    {
        // 何らかの処理
        xxx_data_ = gen_xxx_data(xxx_data_);
    }

    uint32_t Widget::GetValue() const { return xxx_data_; }

    uint32_t WidgetNG::Widget::gen_xxx_data(uint32_t a) { return a * 3; }
```
```cpp
    // in lib/ut/widget_ut.cpp

    #include "widget.h"

    TEST(Pimpl, widget_ng)
    {
        Widget w;

        ASSERT_EQ(1, w.xxx_data_);  // privateのテスト
        w.DoSomething();
        ASSERT_EQ(3, w.xxx_data_);        // privateのテスト
        ASSERT_EQ(9, w.gen_xxx_data(3));  // privateのテスト

        ASSERT_EQ(3, w.GetValue());
    }
```

何らかの事情により、単体テストでprivateなメンバにアクセスする必要があったため、
単体テストクラスをテスト対象クラスのfriendすることで、それを実現している。

単体テストクラスをテスト対象クラスのfriendにするためには、
上記コードの抜粋である下記を記述する必要がある。

```cpp
        FRIEND_TEST(Pimpl, widget_ng);  // 単体テストをfriendにする
```

このマクロは、gtest.h内で定義されているため、widget.hからgtest.hをインクルードしている。

このため、ファイルの依存関係は下記のようになる。

<!-- pu:essential/plant_uml/widget_ng.pu--><p><img src="data:image/png;base64,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" /></p>

この依存関係は、Widgetのクライアントに不要な依存関係を強要してしまう問題のある構造を作り出す。

この問題をPimplによるリファクタリングで解決したコードを以下に示す
(コンパイラのインクルードパスにはlib/hのみが入っていることを前提とする)。

```cpp
    // in lib/h/widget.h

    #include <memory>

    class Widget {
    public:
        Widget();   // widget_pimplは不完全型であるため、コンストラクタ、
        ~Widget();  // デストラクタはインラインにできない
        void     DoSomething();
        uint32_t GetValue() const;
        // 何らかの宣言

        struct widget_pimpl;  // 単体テストのため、publicとするが、実装はsrc/の下に置くため、
                              // 単体テスト以外の外部からのアクセスはできない

    private:
        std::unique_ptr<widget_pimpl> widget_pimpl_;
    };
```
```cpp
    // in lib/src/widget.cpp

    #include "widget_internal.h"

    // widget_pimpl
    void Widget::widget_pimpl::DoSomething()
    {
        // 何らかの処理
        xxx_data_ = gen_xxx_data(xxx_data_);
    }

    uint32_t Widget::widget_pimpl::gen_xxx_data(uint32_t a) { return a * 3; }

    // Widget
    void     Widget::DoSomething() { widget_pimpl_->DoSomething(); }
    uint32_t Widget::GetValue() const { return widget_pimpl_->xxx_data_; }

    // ヘッダファイルの中では、widget_pimplは不完全型であるため、コンストラクタ、
    // デストラクタは下記に定義する
    Widget::Widget() : widget_pimpl_{std::make_unique<Widget::widget_pimpl>()} {}
    Widget::~Widget() = default;
```
```cpp
    // in lib/src/widget_internal.h

    #include "widget.h"

    struct Widget::widget_pimpl {
        void     DoSomething();
        uint32_t gen_xxx_data(uint32_t a);
        uint32_t xxx_data_{1};
    };
```
```cpp
    // in lib/ut/widget_ut.cpp

    #include "../src/widget_internal.h"  // 単体テストのみに、このようなインクルードを認める
    #include "gtest/gtest.h"

    TEST(Pimpl, widget_ok)
    {
        Widget::widget_pimpl wi;

        ASSERT_EQ(1, wi.xxx_data_);
        wi.DoSomething();
        ASSERT_EQ(3, wi.xxx_data_);
        ASSERT_EQ(9, wi.gen_xxx_data(3));

        Widget w;

        w.DoSomething();
        ASSERT_EQ(3, w.GetValue());
    }
```

このリファクタリングにより、ファイルの依存は下記のようになり、
問題のある構造は解消された。

<!-- pu:essential/plant_uml/widget_ok.pu--><p><img src="data:image/png;base64,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" /></p>
[演習-Pimpl](exercise_q.md#SS_22_9_3)  

## lightweight Pimpl <a id="SS_9_4"></a>
[Pimpl](design_pattern.md#SS_9_3)の解説で示したように依存関係をシンプルに保つには極めて有効なパターンではあるが、
このパターンで実装されたクラスのインスタンス化のたびに一回以上のヒープからのアロケーションが必要になるため、
このオーバーヘッドが気になるような場合に備えて、アロケーションを少なくするテクニックを以下に示す
(なお、lightweight Pimplとは筆者の造語であり、ここで紹介するパターンはPimplの一種である)。

```cpp
    //  example/design_pattern/light_pimpl.h 8

    class LightPimpl {
    public:
        LightPimpl(std::string const& name);
        ~LightPimpl();
        LightPimpl(LightPimpl const&)            = delete;  // コピーは禁止
        LightPimpl& operator=(LightPimpl const&) = delete;  // コピーは禁止

        std::vector<uint8_t> const& GetVector() const;
        std::string const&          GetName() const;

        static constexpr size_t BufferLen = 10;
        uint8_t (&GetBuffer())[BufferLen];
        uint8_t const (&GetBuffer() const)[BufferLen];  // const を追加

    private:
        // Impl_tをプレースメントnewでインスタンス化する時に使用するメモリ
        alignas(std::max_align_t) uint8_t memory_[48];  // 配列長はsizeof(Impl_t)以上になるよう調整
        struct Impl_t;
        struct Impl_t* pimpl_;
    };
```

このクラスの実装を以下に示す。

```cpp
    //  example/design_pattern/light_pimpl_ut.cpp 5

    namespace {
    bool constructor_called = false;  // テスト用フラグであるため、実装には無関係
    bool destructor_called  = false;  // テスト用フラグであるため、実装には無関係
    }  // namespace

    struct LightPimpl::Impl_t {
        Impl_t(std::string const& name) : name_{name} { constructor_called = true; /* コンストラクタが呼ばれたマーク */ }
        std::vector<uint8_t> vect_{};
        std::string          name_{};
        uint8_t              buffer_[BufferLen]{};

        ~Impl_t() { destructor_called = true; /* デストラクタが呼ばれたマーク */ }
    };

    LightPimpl::LightPimpl(std::string const& name) : pimpl_{new (memory_) Impl_t{name}}  // プレースメントnew
    {
        static_assert(sizeof(Impl_t) <= sizeof(memory_), "Buffer size mismatch");
        static_assert(sizeof(memory_) - sizeof(Impl_t) < 16, "Buffer has excessive padding");
        static_assert(alignof(Impl_t) <= alignof(std::max_align_t), "Buffer alignment mismatch");
    }

    LightPimpl::~LightPimpl() { pimpl_->~Impl_t(); }  // Impl_tのデストラクタを直接呼び出す

    std::vector<uint8_t> const& LightPimpl::GetVector() const { return pimpl_->vect_; }
    std::string const&          LightPimpl::GetName() const { return pimpl_->name_; }

    uint8_t (&LightPimpl::GetBuffer())[LightPimpl::BufferLen] { return pimpl_->buffer_; }

    uint8_t const (&LightPimpl::GetBuffer() const)[LightPimpl::BufferLen] { return pimpl_->buffer_; }
```

ヒープ以外のメモリからnewするための[プレースメントnew](core_lang_spec.md#SS_19_6_9)を使用しているため、
上記の抜粋である以下のコードはやや見慣れないかもしれない。

```cpp
    //  example/design_pattern/light_pimpl_ut.cpp 21

    LightPimpl::LightPimpl(std::string const& name) : pimpl_{new (memory_) Impl_t{name}}  // プレースメントnew
    {
        static_assert(sizeof(Impl_t) <= sizeof(memory_), "Buffer size mismatch");
        static_assert(sizeof(memory_) - sizeof(Impl_t) < 16, "Buffer has excessive padding");
        static_assert(alignof(Impl_t) <= alignof(std::max_align_t), "Buffer alignment mismatch");
    }
```

プレースメントnewで構築したオブジェクトの解放にはdeleteは使えない。
オブジェクトがその上で構築されているメモリはヒープのものではないため、deleteすると未定義動作につながる。

deleteを使わずにプレースメントnewで構築したオブジェクトの各メンバのデストラクタを呼び出さなければ、
リソースリークにつながる。この問題を解決するためのコードは、上記の抜粋である以下のようなものになる。

```cpp
    //  example/design_pattern/light_pimpl_ut.cpp 30

    LightPimpl::~LightPimpl() { pimpl_->~Impl_t(); }  // Impl_tのデストラクタを直接呼び出す
```

上記のクラスの動作を以下の単体テストにより示す。

```cpp
    //  example/design_pattern/light_pimpl_ut.cpp 48

    {
        ASSERT_FALSE(constructor_called);
        LightPimpl lp{"lp"};

        ASSERT_EQ(lp.GetName(), "lp");
        ASSERT_EQ(lp.GetVector().size(), 0);
        ASSERT_EQ(lp.GetBuffer()[0], 0x0);

        ASSERT_TRUE(constructor_called);
        ASSERT_FALSE(destructor_called);
    };  // この行で、lpは解放される

    ASSERT_TRUE(destructor_called);
```

**[ 通常のPimplとの比較 ]**

| 特徴                 | 通常のPimpl                   | Lightweight Pimpl           |
|----------------------|-------------------------------|-----------------------------|
| メモリ確保           | ヒープ                        | スタック(オブジェクト内)    |
| アロケーション回数   | インスタンス毎に1回以上       | 0回                         |
| パフォーマンス       | new/deleteのオーバーヘッド    | 通常のPimplより良い         |
| 実装の複雑さ         | シンプル                      | やや複雑(プレースメントnew) |
| メモリサイズの柔軟性 | 高い                          | 低い(コンパイル時に固定)    |

## Accessor <a id="SS_9_5"></a>
publicメンバ変数とそれにアクセスするソースコードは典型的なアンチパターンであるため、
このようなコードを禁じるのが一般的なプラクティスである。

```cpp
    //  example/design_pattern/accessor_ut.cpp 8

    class A {  // アンチパターン
    public:
        int32_t a_{0};
    };

    void f(A& a) noexcept
    {
        a.a_ = 3;

        // Do something
        // ...
    }
```

とはいえ、ソフトウェアのプラクティスには必ずといってほど例外があり、
製品開発の現場において、オブジェクトのメンバ変数にアクセスせざるを得ないような場面は、
稀にではあるが発生する。
このような場合に適用するがのこのイデオムである。

```cpp
    //  example/design_pattern/accessor_ut.cpp 28

    class A {  // Accessorの実装例
    public:
        void SetA(int32_t a) noexcept  // setter
        {
            a_ = a;
        }

        int32_t GetA() const noexcept  // getter
        {
            return a_;
        }

    private:
        int32_t a_{0};
        // ...
    };

    void f(A& a) noexcept
    {
        a.SetA(3);

        // Do something
        // ...
    }
```

メンバ変数への直接のアクセスに比べ、以下のようなメリットがある。

* アクセスのログを入れることができる。
* メンバ変数へのアクセスをデバッガで捕捉しやすくなる。
* setterに都合の悪い値が渡された場合、何らかの手段を取ることができる(assertや、エラー処理)。
* リファクタリングや機能修正により対象のメンバ変数がなくなった場合においても、
  クラスのインターフェースの変更を回避できる(修正箇所を局所化できる)。

一方で、クラスに対するこのような細かい制御は、カプセル化に対して問題を起こしやすい。
下記はその典型的なアンチパターンである。

```cpp
    //  example/design_pattern/accessor_ut.cpp 62

    class A {  // Accessorを使用して細かすぎる制御をしてしまうアンチパターン
    public:
        void SetA(int32_t a) noexcept  // setter
        {
            a_ = a;
        }

        int32_t GetA() const noexcept  // getter
        {
            return a_;
        }

        void Change(bool is_changed) noexcept  // setter
        {
            is_changed_ = is_changed;
        }

        bool IsChanged() const noexcept  // getter
        {
            return is_changed_;
        }

        void DoSomething() noexcept  // is_changed_がtrueの時に、呼び出してほしい
        {
            // Do something
            // ...
        }
        // ...
    };

    void f(A& a) noexcept
    {
        if (a.GetA() != 3) {
            a.SetA(3);
            a.Change(true);
        }

        // ...
    }

    void g(A& a) noexcept
    {
        if (!a.IsChanged()) {
            return;
        }

        a.Change(false);
        a.DoSomething();  // a.IsChanged()がtrueの時に実行する。

        // ...
    }
```

上記ソースコードは、オブジェクトaのA::a\_が変更された場合、
その後、それをもとに何らかの動作を行うこと(a.DoSomething)を表しているが、
本来オブジェクトaの状態が変わったかどうかはオブジェクトa自体が判断すべきであり、
a.DoSomething()の実行においても、それが必要かどうかはオブジェクトaが判断すべきである。
この考えに基づいた修正ソースコードを下記に示す。

```cpp
    //  example/design_pattern/accessor_ut.cpp 130

    class A {  // 上記アンチパターンからChange()とIsChanged()を削除し、状態の隠蔽レベルを強化
    public:
        void SetA(int32_t a) noexcept  // setter
        {
            if (a_ == a) {
                return;
            }

            a_          = a;
            is_changed_ = true;
        }

        void DoSomething() noexcept
        {
            if (!is_changed_) {
                return;
            }

            // Do something
            // ...

            is_changed_ = false;  // 状態変更の取り消し
        }
        // ...
    };

    void f(A& a) noexcept
    {
        a.SetA(3);

        // ...
    }

    void g(A& a) noexcept
    {
        a.DoSomething();  // DoSomethingは無条件で呼び出す。
                          // 実際に何かをするかどうかは、オブジェクトaが決める。
        // ...
    }
```

setterを使用する場合、上記のように処理の隠蔽化には特に気を付ける必要がある。

[演習-Accessorの副作用](exercise_q.md#SS_22_9_4)  
[演習-Accessor](exercise_q.md#SS_22_9_5)  

## Copy-And-Swap <a id="SS_9_6"></a>
メンバ変数にポインタやスマートポインタを持つクラスに

* copyコンストラクタ
* copy代入演算子
* moveコンストラクタ
* move代入演算子

が必要になった場合、コンパイラが生成するデフォルトの
[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)では機能が不十分であることが多い。

下記に示すコードは、そのような場合の上記4関数の実装例である。

```cpp
    //  example/design_pattern/no_copy_and_swap_ut.cpp 8

    class NoCopyAndSwap final {
    public:
        explicit NoCopyAndSwap(char const* name0, char const* name1)
            : name0_{name0 == nullptr ? "" : name0}, name1_{name1 == nullptr ? "" : name1}
        {
        }

        NoCopyAndSwap(NoCopyAndSwap const& rhs) : name0_{rhs.name0_}, name1_{rhs.name1_} {}

        NoCopyAndSwap(NoCopyAndSwap&& rhs) noexcept
            : name0_{std::exchange(rhs.name0_, nullptr)}, name1_{std::move(rhs.name1_)}
        {
            // move後には、
            //  * name0_はnullptr
            //  * name1_はnullptrを保持したunique_ptr
            // となる。
        }

        NoCopyAndSwap& operator=(NoCopyAndSwap const& rhs)
        {
            if (this == &rhs) {
                return *this;
            }

            // copyコンストラクタのコードクローン
            name0_ = rhs.name0_;
            name1_ = rhs.name1_;  // ここでエクセプションが発生すると*thisが壊れる

            return *this;
        }

        NoCopyAndSwap& operator=(NoCopyAndSwap&& rhs) noexcept
        {
            if (this == &rhs) {
                return *this;
            }

            // moveコンストラクタのコードクローン
            name0_ = std::exchange(rhs.name0_, nullptr);
            name1_ = std::string{};  // これがないと、name1_の値がrhs.name1_にスワップされる
            name1_ = std::move(rhs.name1_);

            return *this;
        }

        char const*        GetName0() const noexcept { return name0_; }
        std::string const& GetName1() const noexcept { return name1_; }
        ~NoCopyAndSwap() = default;

    private:
        char const* name0_;  // 問題やその改善を明示するために、敢えてname0_をchar const*としたが、
                             // 本来ならば、std::stringかstd::string_viewを使うべき
        std::string name1_;
    };
```

コード内のコメントで示したように、このコードには以下のような問題がある。

* copy代入演算子には、[エクセプション安全性の保証](core_lang_spec.md#SS_19_13)がない。
* 上記4関数は似ているにも関わらず、微妙な違いがあるためコードクローンとなっている。

ここで紹介するCopy-And-Swapはこのような問題を解決するためのイデオムである。

実装例を以下に示す。

```cpp
    //  example/design_pattern/copy_and_swap_ut.cpp 6

    class CopyAndSwap final {
    public:
        explicit CopyAndSwap(char const* name0, char const* name1)
            : name0_{name0 == nullptr ? "" : name0}, name1_{name1 == nullptr ? "" : name1}
        {
        }

        CopyAndSwap(CopyAndSwap const& rhs) : name0_{rhs.name0_}, name1_{rhs.name1_} {}

        CopyAndSwap(CopyAndSwap&& rhs) noexcept : name0_{std::exchange(rhs.name0_, nullptr)}, name1_{std::move(rhs.name1_)}
        {
            // move後には、
            //  * name0_はnullptr
            //  * name1_は""を保持したstd::string
            // となる。
        }

        CopyAndSwap& operator=(CopyAndSwap const& rhs)
        {
            if (this == &rhs) {
                return *this;
            }

            // copyコンストラクタの使用
            CopyAndSwap tmp{rhs};  // ここでエクセプションが発生しても、tmp以外、壊れない

            Swap(tmp);

            return *this;
        }

        CopyAndSwap& operator=(CopyAndSwap&& rhs) noexcept
        {
            if (this == &rhs) {
                return *this;
            }

            CopyAndSwap tmp{std::move(rhs)};  // moveコンストラクタ

            Swap(tmp);

            return *this;
        }

        void Swap(CopyAndSwap& rhs) noexcept
        {
            std::swap(name0_, rhs.name0_);
            std::swap(name1_, rhs.name1_);
        }

        char const*        GetName0() const noexcept { return name0_; }
        std::string const& GetName1() const noexcept { return name1_; }
        ~CopyAndSwap() = default;

    private:
        char const* name0_;  // 問題やその改善を明示するために、敢えてname0_をchar const*としたが、
                             // 本来ならば、std::stringかstd::string_viewを使うべき
        std::string name1_;
    };
```

上記CopyAndSwapのcopyコンストラクタ、moveコンストラクタに変更はない。
また、CopyAndSwap::Swapに関してもstd::vector等が持つswapと同様のものである。
このイデオムの特徴は、copy代入演算子、
move代入演算子が各コンストラクタとSwap関数により実装されている所にある。
これにより[エクセプション安全性の保証](core_lang_spec.md#SS_19_13)を持つ4関数をコードクローンすることなく実装できる。

[演習-Copy-And-Swap](exercise_q.md#SS_22_9_6)  

## Immutable <a id="SS_9_7"></a>
クラスに対するimmutable、immutabilityの定義を以下のように定める。

* immutable(不変な)なクラスとは、初期化後、状態の変更ができないクラスを指す。
* immutability(不変性)が高いクラスとは、
  状態を変更するメンバ関数(非constなメンバ関数)が少ないクラスを指す。

immutabilityが高いほど、そのクラスの使用方法は制限される。
これにより、そのクラスやそのクラスを使用しているソースコードの可読性やデバッグ容易性が向上する。
また、クラスがimmutableでなくても、そのクラスのオブジェクトをconstハンドル経由でアクセスすることで、
immutableとして扱うことができる。

一方で、「[Accessor](design_pattern.md#SS_9_5)」で紹介したsetterは、クラスのimmutabilityを下げる。
いつでも状態が変更できるため、ソースコードの可読性やデバッグ容易性が低下する。
また、マルチスレッド環境においてはこのことが競合問題や、
それを回避するためのロックがパフォーマンス問題やデッドロックを引き起こしてしまう。

従って、クラスを宣言、定義する場合、immutabilityを出来るだけ高くするべきであり、
そのクラスのオブジェクトを使う側は、
可能な限りimmutableオブジェクト(constオブジェクト)として扱うべきである。

[演習-Immutable](exercise_q.md#SS_22_9_7)  

## Clone(仮想コンストラクタ) <a id="SS_9_8"></a>
オブジェクトコピーによる[スライシング](cpp_idioms.md#SS_21_7_3)を回避するためのイデオムである。

下記は、オブジェクトコピーによるスライシングを起こしてしまう例である。

```cpp
    //  example/design_pattern/clone_ut.cpp 8

    class BaseSlicing {
    public:
        // ...
        virtual char const* Name() const noexcept { return "BaseSlicing"; }
    };

    class DerivedSlicing final : public BaseSlicing {
    public:
        // ...
        virtual char const* Name() const noexcept override { return "DerivedSlicing"; }
    };

    TEST(Clone, object_slicing)
    {
        auto b = BaseSlicing{};
        auto d = DerivedSlicing{};

        BaseSlicing* b_ptr   = &b;
        BaseSlicing* b_ptr_d = &d;

        ASSERT_STREQ("BaseSlicing", b_ptr->Name());
        ASSERT_STREQ("DerivedSlicing", b_ptr_d->Name());

        *b_ptr = *b_ptr_d;  // コピーしたつもりだがスライシングにより、*b_ptrは、
                            // DerivedSlicingのインスタンスではなく、BaseSlicingのインスタンス

    #if 0
        ASSERT_STREQ("DerivedSlicing", b_ptr->Name());
    #else
        ASSERT_STREQ("BaseSlicing", b_ptr->Name());  // "DerivedSlicing"が返るはずだが、
                                                     // スライシングにより"BaseSlicing"が返る
    #endif
    }
```

下記は、上記にcloneイデオムを適用した例である。

```cpp
    //  example/design_pattern/clone_ut.cpp 50

    // スライシングを起こさないようにコピー演算子の代わりにClone()を実装。
    class BaseNoSlicing {
    public:
        // ...
        virtual char const* Name() const noexcept { return "BaseNoSlicing"; }

        virtual std::unique_ptr<BaseNoSlicing> Clone() { return std::make_unique<BaseNoSlicing>(); }

        BaseNoSlicing(BaseNoSlicing const&)            = delete;  // copy生成の禁止
        BaseNoSlicing& operator=(BaseNoSlicing const&) = delete;  // copy代入の禁止
    };

    class DerivedNoSlicing final : public BaseNoSlicing {
    public:
        // ...
        virtual char const* Name() const noexcept override { return "DerivedNoSlicing"; }

        std::unique_ptr<DerivedNoSlicing> CloneOwn() { return std::make_unique<DerivedNoSlicing>(); }

        // DerivedNoSlicingはBaseNoSlicingの派生クラスであるため、
        // std::unique_ptr<DerivedNoSlicing>オブジェクトから
        // std::unique_ptr<BaseNoSlicing>オブジェクトへのmove代入可能
        virtual std::unique_ptr<BaseNoSlicing> Clone() override { return CloneOwn(); }
    };

    TEST(Clone, object_slicing_avoidance)
    {
        auto b = BaseNoSlicing{};
        auto d = DerivedNoSlicing{};

        BaseNoSlicing* b_ptr   = &b;
        BaseNoSlicing* b_ptr_d = &d;

        ASSERT_STREQ("BaseNoSlicing", b_ptr->Name());
        ASSERT_STREQ("DerivedNoSlicing", b_ptr_d->Name());

    #if 0
        *b_ptr = *b_ptr_d;                // コピー演算子をdeleteしたのでコンパイルエラー
    #else
        auto b_uptr = b_ptr_d->Clone();              // コピー演算子の代わりにClone()を使う。
    #endif

        ASSERT_STREQ("DerivedNoSlicing", b_uptr->Name());  // 意図通り"DerivedNoSlicing"が返る。
    }
```

B1::Clone()やそのオーバーライドであるD1::Clone()を使うことで、
スライシングを起こすことなくオブジェクトのコピーを行うことができるようになった。

[演習-Clone](exercise_q.md#SS_22_9_8)  

## NVI(non virtual interface) <a id="SS_9_9"></a>
NVIとは、「virtualなメンバ関数をpublicにしない」という実装上の制約である。

下記のようにクラスBaseが定義されているとする。

```cpp
    //  example/design_pattern/nvi_ut.cpp 7

    class Base {
    public:
        virtual bool DoSomething(int something) const noexcept
        {
            // ...
        }

        virtual ~Base() = default;

    private:
        // ...
    };
```

これを使うクラスはBase::DoSomething()に依存する。
また、このクラスから派生した下記のクラスDerivedもBase::DoSomething()に依存する。

```cpp
    //  example/design_pattern/nvi_ut.cpp 26

    class Derived : public Base {
    public:
        virtual bool DoSomething(int something) const noexcept override
        {
            // ...
        }

    private:
        // ...
    };
```

この条件下ではBase::DoSomething()へ依存が集中し、この関数の修正や機能追加の作業コストが高くなる。
このイデオムは、この問題を軽減する。

これを用いた上記2クラスのリファクタリング例を以下に示す。

```cpp
    //  example/design_pattern/nvi_ut.cpp 57

    class Base {
    public:
        bool DoSomething(int something) const noexcept { return do_something(something); }
        virtual ~Base() = default;

    private:
        virtual bool do_something(int something) const noexcept
        {
            // ...
        }

        // ...
    };

    class Derived : public Base {
    private:
        virtual bool do_something(int something) const noexcept override
        {
            // ...
        }

        // ...
    };
```

オーバーライド元の関数とそのオーバーライドのデフォルト引数の値は一致させる必要がある。

それに従わない下記のようなクラスとその派生クラス

```cpp
    //  example/design_pattern/nvi_ut.cpp 105

    class NotNviBase {
    public:
        virtual std::string Name(bool mangled = false) const { return mangled ? typeid(*this).name() : "NotNviBase"; }

        virtual ~NotNviBase() = default;
    };

    class NotNviDerived : public NotNviBase {
    public:
        virtual std::string Name(bool mangled = true) const override  // NG デフォルト値が違う
        {
            return mangled ? typeid(*this).name() : "NotNviDerived";
        }
    };
```

には下記の単体テストで示したような、
メンバ関数の振る舞いがその表層型に依存してしまう問題を持つことになる。

```cpp
    //  example/design_pattern/nvi_ut.cpp 126

    NotNviDerived const d;
    NotNviBase const&   d_ref = d;

    ASSERT_EQ("NotNviDerived", d.Name(false));   // OK
    ASSERT_EQ("13NotNviDerived", d.Name(true));  // OK

    ASSERT_EQ("NotNviDerived", d_ref.Name(false));   // OK
    ASSERT_EQ("13NotNviDerived", d_ref.Name(true));  // OK

    ASSERT_EQ("13NotNviDerived", d.Name());    // mangled == false
    ASSERT_EQ("NotNviDerived", d_ref.Name());  // mangled == true

    ASSERT_NE(d.Name(), d_ref.Name());  // NG d_refの実態はdであるが、d.Name()と動きが違う
```

この例のように継承階層が浅く、デフォルト引数の数も少ない場合、
この値を一致させることは難しくないが、
これよりも遥かに複雑な実際のコードではこの一致の維持は困難になる。

下記のようにNVIに従わせることでこのような問題に対処できる。

```cpp
    //  example/design_pattern/nvi_ut.cpp 145
    class NviBase {
    public:
        std::string Name(bool mangled = false) const { return name(mangled); }
        virtual ~NviBase() = default;

    private:
        virtual std::string name(bool mangled) const { return mangled ? typeid(*this).name() : "NviBase"; }
    };

    class NviDerived : public NviBase {
    private:
        virtual std::string name(bool mangled) const override  // OK デフォルト値を持たない
        {
            return mangled ? typeid(*this).name() : "NviDerived";
        }
    };
```

下記の単体テストにより、この問題の解消が確認できる。

```cpp
    //  example/design_pattern/nvi_ut.cpp 167

    NviBase const    b;
    NviDerived const d;
    NviBase const&   d_ref = d;

    ASSERT_EQ("NviDerived", d.Name(false));   // OK
    ASSERT_EQ("10NviDerived", d.Name(true));  // OK

    ASSERT_EQ("NviDerived", d_ref.Name(false));   // OK
    ASSERT_EQ("10NviDerived", d_ref.Name(true));  // OK

    ASSERT_EQ("NviDerived", d.Name());      // mangled == false
    ASSERT_EQ("NviDerived", d_ref.Name());  // mangled == false

    ASSERT_EQ(d.Name(), d_ref.Name());  // OK
```

なお、メンバ関数のデフォルト引数は、
そのクラス外部からのメンバ関数呼び出しを簡潔に記述するための記法であるため、
privateなメンバ関数はデフォルト引数を持つべきではない。

[演習-NVI](exercise_q.md#SS_22_9_9)  

## RAII(scoped guard) <a id="SS_9_10"></a>
RAIIとは、「Resource Acquisition Is Initialization」の略語であり、
リソースの確保と解放をオブジェクトの初期化と破棄処理に結びつけるパターンもしくはイデオムである。
特にダイナミックにオブジェクトを生成する場合、
RAIIに従わないとメモリリークを防ぐことは困難である。

下記は、関数終了付近でdeleteする素朴なコードである。

```cpp
    //  example/design_pattern/raii_ut.cpp 19

    // Aは外部の変数をリファレンスcounter_として保持し、
    //  * コンストラクタ呼び出し時に++counter_
    //  * デストラクタタ呼び出し時に--counter_
    // とするため、生成と解放が同じだけ行われれば外部の変数の値は0となる
    class A {
    public:
        A(uint32_t& counter) noexcept : counter_{++counter} {}
        ~A() { --counter_; }

    private:
        uint32_t& counter_;
    };

    char not_use_RAII_for_memory(size_t index, uint32_t& object_counter)
    {
        auto a = new A{object_counter};  // RAIIでない例
        auto s = std::string{"hehe"};

        auto ret = s.at(index);  // index >= 5でエクセプション発生

        // 何らかの処理

        delete a;         //  この行以前に関数を抜けるとaはメモリリーク

        return ret;
    }
```

このコードは下記の単体テストが示す通り、第1パラメータが5以上の場合、
エクセプションが発生しメモリリークしてしまう。

```cpp
    //  example/design_pattern/raii_ut.cpp 72

    auto object_counter = 0U;

    // 第1引数が5なのでエクセプション発生
    ASSERT_THROW(not_use_RAII_for_memory(5, object_counter), std::exception);

    // 上記のnot_use_RAII_for_memoryではエクセプションが発生し、メモリリークする
    ASSERT_EQ(1, object_counter);
```

以下は、std::unique_ptrによってRAIIを導入し、この問題に対処した例である。

```cpp
    //  example/design_pattern/raii_ut.cpp 84

    char use_RAII_for_memory(size_t index, uint32_t& object_counter)
    {
        auto a = std::make_unique<A>(object_counter);
        auto s = std::string{"hehe"};

        auto ret = s.at(index);  // index >= 5でエクセプション発生

        // 何らかの処理

        return ret;  // aは自動解放される
    }
```

下記単体テストで確認できるように、
エクセプション発生時にもstd::unique_ptrによる自動解放によりメモリリークは発生しない。

```cpp
    //  example/design_pattern/raii_ut.cpp 101

    auto object_counter = 0U;

    // 第1引数が5なのでエクセプション発生
    ASSERT_THROW(use_RAII_for_memory(5, object_counter), std::exception);

    // 上記のuse_RAII_for_memoryではエクセプションが発生するがメモリリークはしない
    ASSERT_EQ(0, object_counter);
```

RAIIのテクニックはメモリ管理のみでなく、ファイルディスクリプタ(open-close、socket-close)
等のリソース管理においても有効であるという例を示す。

下記は、生成したソケットを関数終了付近でcloseする素朴なコードである。

```cpp
    //  example/design_pattern/raii_ut.cpp 112

    // RAIIをしない例
    // 複数のclose()を書くような関数は、リソースリークを起こしやすい。
    void not_use_RAII_for_socket()
    {
        auto fd = socket(AF_INET, SOCK_STREAM, 0);

        try {
            // Do something
            // ...
        }
        catch (std::exception const& e) {  // エクセプションはconstリファレンスで受ける。
            close(fd);                     // NG RAII未使用
            // Do something to recover
            // ...

            return;
        }
        // ...
        close(fd);  // NG RAII未使用
    }
```

エクセプションを扱うために関数の2か所でソケットをcloseしている。
この程度であれば大きな問題にはならないだろうが、実際には様々な条件が重なるため、
リソースの解放コードは醜悪にならざるを得ない。

このような場合には、下記するようなリソース解放用クラス

```cpp
    //  h/scoped_guard.h 7

    /// @brief RAIIのためのクラス。コンストラクタ引数の関数オブジェクトをデストラクタから呼び出す
    ///
    #if __cplusplus >= 202002L   // c++20

    template <std::invocable F>  // Fが呼び出し可能であることを制約
    #else  // c++17

    template <typename F>
    #endif
    class ScopedGuard {
    public:
        explicit ScopedGuard(F&& f) noexcept : f_{f}
        {
        }

        ~ScopedGuard() { f_(); }
        ScopedGuard(ScopedGuard const&)            = delete;  // copyは禁止
        ScopedGuard& operator=(ScopedGuard const&) = delete;  // copyは禁止

    private:
        F f_;
    };
```

を使用し、下記のようにすることで安全なコードをすっきりと書くことができる。

```cpp
    //  example/design_pattern/raii_ut.cpp 139

    // RAIIをScopedGuardで行った例。
    // close()が自動実行されるためにリソース解放を忘れない。
    void use_RAII_for_socket()
    {
        auto fd    = socket(AF_INET, SOCK_STREAM, 0);
        auto guard = ScopedGuard{[fd] { close(fd); }};  // 関数終了時に自動実行

        try {
            // Do something
        }
        catch (...) {
            // Do something to recover

            return;
        }

        // Do something
    }
```

クリティカルセクションの保護をlock/unlockで行うstd::mutex等を使う場合にも、
std::lock_guard<>によってunlockを行うことで、同様の効果が得られる。

[演習-RAIIの効果](exercise_q.md#SS_22_9_10)  
[演習-RAII](exercise_q.md#SS_22_9_11)  

## Future <a id="SS_9_11"></a>
[Future](https://ja.wikipedia.org/wiki/Future_%E3%83%91%E3%82%BF%E3%83%BC%E3%83%B3)とは、
並行処理のためのデザインパターンであり、別スレッドに何らかの処理をさせる際、
その結果の取得を、必要になるまで後回しにする手法である。

C++11では、std::future, std::promise, std::asyncによって実現できる。

まずは、C++03以前のスタイルから示す。

```cpp
    //  example/design_pattern/future_ut.cpp 11

    int do_something(std::string_view str0, std::string_view str1) noexcept
    {
        // ...

        return ret0 + ret1;
    }

    TEST(Future, old_style)
    {
        auto str0 = std::string{};
        auto th0  = std::thread{[&str0]() noexcept { str0 = do_heavy_algorithm("thread 0"); }};

        auto str1 = std::string{};
        auto th1  = std::thread{[&str1]() noexcept { str1 = do_heavy_algorithm("thread 1"); }};

        //
        // このスレッドで行うべき何らかの処理
        //

        th0.join();
        th1.join();

        ASSERT_EQ("THREAD 0", str0);
        ASSERT_EQ("THREAD 1", str1);

        ASSERT_EQ(16, do_something(str0, str1));
    }
```

上記は、

1. 時間がかかる処理を並行して行うために、スレッドを二つ作る。
2. それぞれの完了をthread::join()で待ち合わせる。
3. その結果を参照キャプチャによって受け取る。
4. その2つの結果を別の関数に渡す。

という処理を行っている。

この程度の単純なコードでは特に問題にはならないが、目的外の処理が多いことがわかるだろう。

次にFutureパターンによって上記をリファクタリングした例を示す。

```cpp
    //  example/design_pattern/future_ut.cpp 45

    TEST(Future, new_style)
    {
        std::future<std::string> result0
            = std::async(std::launch::async, []() noexcept { return do_heavy_algorithm("thread 0"); });

        std::future<std::string> result1
            = std::async(std::launch::async, []() noexcept { return do_heavy_algorithm("thread 1"); });

        // futre::get()は処理の待ち合わせと値の取り出しを行う。
        auto str0 = result0.get();
        auto str1 = result1.get();
        ASSERT_EQ(16, do_something(str0, str1));

        ASSERT_EQ("THREAD 0", str0);
        ASSERT_EQ("THREAD 1", str1);
    }
```

リファクタリングした例では、時間のかかる処理をstd::future型のオブジェクトにし、
その結果を必要とする関数に渡すことができるため、目的をよりダイレクトに表すことができる。

なお、

```cpp
    std::async(関数オブジェクト)
```

という形式を使った場合、関数オブジェクトは、

```cpp
    std::launch::async | std::launch::deferred
```

が指定されたとして実行される。この場合、

```cpp
    std::launch::deferred
```

の効果により、関数オブジェクトは、並行に実行されるとは限らない
(この仕様はランタイム系に依存しており、std::future::get()のコンテキストで実行されることもあり得る)。
従って、並行実行が必要な場合、上記例のように

```cpp
    std::launch::async
```

のみを明示的に指定するべきである。

[演習-Future](exercise_q.md#SS_22_9_12)  

## DI(dependency injection) <a id="SS_9_12"></a>
メンバ関数内でクラスDependedのオブジェクトを直接、生成する
(もしくは[Singleton](design_pattern.md#SS_9_13)オブジェクトや静的オブジェクト(std::coutやstd::cin等)に直接アクセスする)
クラスNotDIがあるとする。
この場合、クラスNotDIはクラスDependedのインスタンスに依存してしまう。
このような依存関係はクラスNotDIの可用性とテスト容易性を下げる。
これは、「仮にクラスDependedがデータベースをラップするクラスだった場合、
クラスNotDIの単体テストにデータベースが必要になる」ことからも容易に理解できる。

```cpp
    //  example/design_pattern/di_ut.cpp 8

    /// @brief NotDIや、DIから依存されるクラス
    class Depended {
        // ...
    };

    /// @brief NotDIを使わない例。そのため、NotDIは、Dependedのインスタンスに依存している。
    class NotDI {
    public:
        NotDI() : not_di_depended_{std::make_unique<Depended>()} {}

        void DoSomething() { not_di_depended_->DoSomething(); }

    private:
        std::unique_ptr<Depended> not_di_depended_;
    };
```

下記は上記NotDIにDIパターンを適用した例である。
この場合、クラスDIは、クラスDependedの型にのみ依存する。

```cpp
    //  example/design_pattern/di_ut.cpp 37

    /// @brief DIを使う例。そのため、DIは、Dependedの型に依存している。
    class DI {
    public:
        explicit DI(std::unique_ptr<Depended>&& di_depended) noexcept : di_depended_{std::move(di_depended)} {}

        void DoSomething() { di_depended_->DoSomething(); }

    private:
        std::unique_ptr<Depended> di_depended_;
    };
```

下記は、クラスNotDIとクラスDIがそれぞれのDoSomething()を呼び出すまでのシーケンス図である。

<!-- pu:essential/plant_uml/di.pu--><p><img src="data:image/png;base64,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" /></p>

このパターンの効果により、
DIオブジェクトにはDependedかその派生クラスのオブジェクトを渡すことができるようになった。
これによりクラスDIは拡張性に対して柔軟になっただけでなく、テスト容易性も向上した。

次に示すのは、このパターンを使用して問題のある単体テストを修正した例である。

まずは、問題があるクラスとその単体テストを下記する。

```cpp
    // in device_io.h

    class DeviceIO {
    public:
        uint8_t read()
        {
            // ハードウェアに依存した何らかの処理
        }

        void write(uint8_t a)
        {
            // ハードウェアに依存した何らかの処理
        }

    private:
        // 何らかの宣言
    };

    #ifdef UNIT_TEST       // 単体テストビルドでは定義されるマクロ
    class DeviceIO_Mock {  // 単体テスト用のモック
    public:
        uint8_t read()
        {
            // ハードウェアに依存しない何らかの処理
        }

        void write(uint8_t a)
        {
            // ハードウェアに依存しない何らかの処理
        }

    private:
        // 何らかの宣言
    };
    #endif
```
```cpp
    // in widget.h
    
    #include "device_io.h"

    class Widget {
    public:
        void DoSomething()
        {
            // io_を使った何らかの処理
        }

        uint8_t GetResp()
        {
            // io_を使った何らかの処理
        }

    private:
    #ifdef UNIT_TEST
        DeviceIO_Mock io_;
    #else
        DeviceIO io_;
    #endif
    };
```
```cpp
    // in widget_ut.cpp

    // UNIT_TESTマクロが定義されたWidgetの単体テスト
    Widget w;

    w.DoSomething();
    ASSERT_EQ(0, w.GetResp());
```

当然であるが、この単体テストは、UNIT_TESTマクロを定義している場合のWidgetの評価であり、
UNIT_TESTを定義しない実際のコードの評価にはならない。

以下では、DIを用い、この問題を回避する。

```cpp
    // in device_io.h

    class DeviceIO {
    public:
        virtual uint8_t read()  // モックでオーバーライドするためvirtual
        {
            // ハードウェアに依存した何らかの処理
        }

        virtual void write(uint8_t a)  // モックでオーバーライドするためvirtual
        {
            // ハードウェアに依存した何らかの処理
        }
        virtual ~DeviceIO() = default;

    private:
        // 何らかの宣言
    };
```
```cpp
    // in widget.h

    class Widget {
    public:
        Widget(std::unique_ptr<DeviceIO> io = std::make_unique<DeviceIO>()) : io_{std::move(io)} {}

        void DoSomething()
        {
            // io_を使った何らかの処理
        }

        uint8_t GetResp()
        {
            // io_を使った何らかの処理
        }

    private:
        std::unique_ptr<DeviceIO> io_;
    };
```
```cpp
    // in widget_ut.cpp

    class DeviceIO_Mock : public DeviceIO {  // 単体テスト用のモック
    public:
        uint8_t read() override
        {
            // ハードウェアに依存しない何らかの処理
        }

        void write(uint8_t a) override
        {
            // ハードウェアに依存しない何らかの処理
        }

    private:
        // 何らかの宣言
    };
```
```cpp
    // 上記DeviceIO_Mockと同様に、in widget_ut.cpp

    Widget w{std::unique_ptr<DeviceIO>(new DeviceIO_Mock)};  // モックのインジェクション

    // Widgetの単体テスト
    w.DoSomething();
    ASSERT_EQ(1, w.GetResp());
```

この例では、単体テストのためだけに仮想関数を導入しているため、多少やりすぎの感がある。
そのような場合、下記のようにテンプレートを用いればよい。

```cpp
    // in device_io.h

    class DeviceIO {
    public:
        uint8_t read()  // Widgetがテンプレートであるため非virtualで良い
        {
            // ハードウェアに依存した何らかの処理
        }

        void write(uint8_t a)  // Widgetがテンプレートであるため非virtualで良い
        {
            // ハードウェアに依存した何らかの処理
        }
        virtual ~DeviceIO() = default;

    private:
        // 何らかの宣言
    };
```
```cpp
    // in widget.h

    template <class T = DeviceIO>
    class Widget {
    public:
        void DoSomething()
        {
            // io_を使った何らかの処理
        }

        uint8_t GetResp()
        {
            // io_を使った何らかの処理
        }

    private:
        T io_;
    };
```
```cpp
    // in widget_ut.cpp

    class DeviceIO_Mock {  // 単体テスト用のモック
    public:
        uint8_t read()  // Widgetがテンプレートであるため非virtualで良い
        {
            // ハードウェアに依存しない何らかの処理
        }

        void write(uint8_t a)  // Widgetがテンプレートであるため非virtualで良い
        {
            // ハードウェアに依存しない何らかの処理
        }

    private:
        // 何らかの宣言
    };
```
```cpp
    // 上記DeviceIO_Mockと同様に、in widget_ut.cpp

    Widget<DeviceIO_Mock> w;

    // Widget<>の単体テスト
    w.DoSomething();
    ASSERT_EQ(2, w.GetResp());
```

以上からわかるように、
ここで紹介したDIは単体テストを容易にするクラス設計のためにも非常に有用なパターンである。

[演習-DI](exercise_q.md#SS_22_9_13)  

## Singleton <a id="SS_9_13"></a>
このパターンにより、特定のクラスのインスタンスをシステム全体で唯一にすることができる。
これにより、グローバルオブジェクトを規律正しく使用しやすくなる。

以下は、Singletonの実装例である。

```cpp
    //  example/design_pattern/singleton_ut.cpp 7

    class Singleton final {
    public:
        static Singleton&       Inst();
        static Singleton const& InstConst() noexcept  // constインスタンスを返す
        {
            return Inst();
        }
        // ...

    private:
        Singleton() noexcept {}  // コンストラクタをprivateにすることで、
                                 // Inst()以外ではこのオブジェクトを生成できない。
        // ...
    };

    Singleton& Singleton::Inst()
    {
        static Singleton inst;  //  instの初期化が同時に行われることはない。

        return inst;
    }

    TEST(Singleton, how_to_use)
    {
        auto&       inst       = Singleton::Inst();
        auto const& inst_const = Singleton::InstConst();

        ASSERT_EQ(0, inst.GetXxx());
        ASSERT_EQ(0, inst_const.GetXxx());
    #if 0
        inst_const.SetXxx(10);  // inst_constはconstオブジェクトなのでコンパイルエラー
    #else
        inst.SetXxx(10);
    #endif
        ASSERT_EQ(10, inst.GetXxx());
        ASSERT_EQ(10, inst_const.GetXxx());

        inst.SetXxx(0);
        ASSERT_EQ(0, inst.GetXxx());
        ASSERT_EQ(0, inst_const.GetXxx());
    }
    }  // namespace
```

このパターンを使用する場合、以下に注意する。  

* Singletonはデザインパターンの中でも、特にパターン猿病を発生しやすい。
  Singletonは「ほとんどグローバル変数である」ことを理解した上で、控えめに使用する。
* Singletonを定義する場合、以下の二つを定義する。
    * インスタンスを返すstaticメンバ関数Inst()
    * constインスタンスを返すstaticメンバ関数InstConst()
* InstConst()は、Inst()が返すオブジェクトと同じオブジェクトを返すようにする。
* Singletonには、可能な限りInstConst()経由でアクセスする。

Singletonオブジェクトの初期化(最初のコンストラクタ呼び出し)は、
C++03以前はスレッドセーフでなかったため、「 Double Checked Lockingを使って競合を避ける」か、
「他のスレッドを起動する前にメインスレッドから各SingletonのInstConst()を呼び出す」
ことが必要であった。
C++11から上記例のようなSingletonオブジェクトのコンストラクタ呼び出しはスレッドセーフとなったため、
このような黒魔術が不要になった。

なお、Inst()のような関数を複数定義する場合、そのパターンはNamed Constructor
(「[Named Constructor](design_pattern.md#SS_9_18)」参照)と呼ばれる。

[演習-Singleton](exercise_q.md#SS_22_9_14)  

## State <a id="SS_9_14"></a>
Stateは、オブジェクトの状態と、それに伴う振る舞いを分離して記述するためのパターンである。
これにより状態の追加、削減、変更に伴う修正範囲が限定される
(「[オープン・クローズドの原則(OCP)](solid.md#SS_8_2)」参照)。
またオブジェクトのインターフェース変更(パブリックメンバ関数の変更)に関しても、修正箇所が明確になる。

<!-- pu:essential/plant_uml/state_machine.pu--><p><img src="data:image/png;base64,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" /></p>

上記ステートマシン図の「オールドスタイルによる実装」と、「stateパターンによる実装」、
それぞれを例示する。

まずは、下記にオールドスタイルな実装例を示す。
この実装では、状態を静的なenum変数thread_old_style_stateで管理するため、
ThreadOldStyleStateStr()、ThreadOldStyleRun()、ThreadOldStyleAbort()、ThreadOldStyleSuspend()
には、thread_old_style_stateに対する同型のswitch文が入ることになる(下記例では一部省略)。
これは醜悪で、バグを起こしやすい構造である。
ただし、要求される状態遷移がこの例程度であり、状態ごとに決められた振る舞いの数が少なければ、
この構造でも問題ないともいえる。

```cpp
    //  example/design_pattern/state_machine_old.h 4

    extern std::string_view ThreadOldStyleStateStr() noexcept;
    extern void             ThreadOldStyleRun();
    extern void             ThreadOldStyleAbort();
    extern void             ThreadOldStyleSuspend();
```

```cpp
    //  example/design_pattern/state_machine_old.cpp 6

    namespace {
    enum class ThreadOldStyleState {
        Idle,
        Running,
        Suspending,
    };

    ThreadOldStyleState thread_old_style_state;
    // ...
    }  // namespace

    std::string_view ThreadOldStyleStateStr() noexcept
    {
        switch (thread_old_style_state) {  // このswitch文と同型switch文が何度も記述される
        case ThreadOldStyleState::Idle:
            return "Idle";
        case ThreadOldStyleState::Running:
            return "Running";
        case ThreadOldStyleState::Suspending:
            return "Suspending";
        default:
            assert(false);
            return "";
        }
    }

    void ThreadOldStyleRun()
    {
        switch (thread_old_style_state) {
        case ThreadOldStyleState::Idle:
        case ThreadOldStyleState::Running:
            thread_old_style_state = ThreadOldStyleState::Running;
            break;
        case ThreadOldStyleState::Suspending:
            --thread_old_style_suspend_count;
            if (thread_old_style_suspend_count == 0) {
                thread_old_style_state = ThreadOldStyleState::Running;
            }
            break;
        default:
            assert(false);
        }
    }

    void ThreadOldStyleAbort()
    {
        // ...
    }

    void ThreadOldStyleSuspend()
    {
        // ...
    }
```

```cpp
    //  example/design_pattern/state_machine_ut.cpp 15

    // ステートのテスト。仕様書よりも単体テストでその仕様や使用法を記述したほうが正確に理解できる。
    TEST(StateMachine, old_style)
    {
        ASSERT_EQ("Idle", ThreadOldStyleStateStr());

        ThreadOldStyleAbort();
        ASSERT_EQ("Idle", ThreadOldStyleStateStr());

        ThreadOldStyleRun();
        ASSERT_EQ("Running", ThreadOldStyleStateStr());

        ThreadOldStyleRun();
        ASSERT_EQ("Running", ThreadOldStyleStateStr());

        ThreadOldStyleSuspend();
        ASSERT_EQ("Suspending", ThreadOldStyleStateStr());  // suspend_count_ == 1

        ThreadOldStyleSuspend();
        ASSERT_EQ("Suspending", ThreadOldStyleStateStr());  // suspend_count_ == 2

        ThreadOldStyleRun();
        ASSERT_EQ("Suspending", ThreadOldStyleStateStr());  // suspend_count_ == 1

        // ...
    }
```

下記は、上記例へstateパターンを適用した例である。
まずは、stateパターンを形成するクラスの関係をクラス図で示す。

<!-- pu:essential/plant_uml/state_machine_class.pu--><p><img src="data:image/png;base64,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" /></p>

次に上記クラス図の実装例を示す。

```cpp
    //  example/design_pattern/state_machine_new.h 6

    /// @brief ThreadNewStyleのステートを表す基底クラス
    class ThreadNewStyleState {
    public:
        ThreadNewStyleState()          = default;
        virtual ~ThreadNewStyleState() = default;

        std::unique_ptr<ThreadNewStyleState> Abort()  // NVI
        {
            return abort_thread();
        }

        std::unique_ptr<ThreadNewStyleState> Run()  // NVI
        {
            return run_thread();
        }

        std::unique_ptr<ThreadNewStyleState> Suspend()  // NVI
        {
            return suspend_thread();
        }

        std::string_view GetStateStr() const noexcept { return get_state_str(); }

    private:
        virtual std::unique_ptr<ThreadNewStyleState> abort_thread()
        {
            return {};  // デフォルトでは何もしない。
        }

        virtual std::unique_ptr<ThreadNewStyleState> run_thread()
        {
            return {};  // デフォルトでは何もしない。
        }

        virtual std::unique_ptr<ThreadNewStyleState> suspend_thread()
        {
            return {};  // デフォルトでは何もしない。
        }

        virtual std::string_view get_state_str() const noexcept = 0;
    };
```

```cpp
    //  example/design_pattern/state_machine_new.h 51

    class ThreadNewStyle final {
    public:
        ThreadNewStyle();

        void Abort() { change_state(state_->Abort()); }

        void Run() { change_state(state_->Run()); }

        void Suspend() { change_state(state_->Suspend()); }

        std::string_view GetStateStr() const noexcept { return state_->GetStateStr(); }

    private:
        std::unique_ptr<ThreadNewStyleState> state_;

        void change_state(std::unique_ptr<ThreadNewStyleState>&& new_state) noexcept
        {
            if (new_state) {
                state_ = std::move(new_state);
            }
        }
    };
```

```cpp
    //  example/design_pattern/state_machine_new.cpp 10

    class ThreadNewStyleState_Idle final : public ThreadNewStyleState {
        // ...
    };

    class ThreadNewStyleState_Running final : public ThreadNewStyleState {
        // ...
    };

    class ThreadNewStyleState_Suspending final : public ThreadNewStyleState {
    public:
        // ...
    private:
        virtual std::unique_ptr<ThreadNewStyleState> abort_thread() override
        {
            // do something to abort
            // ...

            return std::make_unique<ThreadNewStyleState_Idle>();
        }

        virtual std::unique_ptr<ThreadNewStyleState> run_thread() override
        {
            --suspend_count_;

            if (suspend_count_ == 0) {
                // do something to resume
                // ...
                return std::make_unique<ThreadNewStyleState_Running>();
            }
            else {
                return {};
            }
        }

        virtual std::unique_ptr<ThreadNewStyleState> suspend_thread() override
        {
            ++suspend_count_;

            return {};
        }
        // ...
    };
```

```cpp
    //  example/design_pattern/state_machine_ut.cpp 57

    TEST(StateMachine, new_style)
    {
        auto tns = ThreadNewStyle{};

        ASSERT_EQ("Idle", tns.GetStateStr());

        tns.Abort();
        ASSERT_EQ("Idle", tns.GetStateStr());

        tns.Run();
        ASSERT_EQ("Running", tns.GetStateStr());

        tns.Run();
        ASSERT_EQ("Running", tns.GetStateStr());

        tns.Suspend();
        ASSERT_EQ("Suspending", tns.GetStateStr());  // suspend_count_ == 1

        tns.Suspend();
        ASSERT_EQ("Suspending", tns.GetStateStr());  // suspend_count_ == 2

        tns.Run();
        ASSERT_EQ("Suspending", tns.GetStateStr());  // suspend_count_ == 1

        // ...
    }
```

オールドスタイルな構造に比べると一見複雑に見えるが同型のswitch構造がないため、
状態の増減や振る舞いの変更等への対応が容易である。
一方で、前述したとおり、この例程度の要求であれば、
シンプルさという意味においてオールドスタイルのソースコードの方が優れているともいえる。
従って、オールドスタイルとstateパターンの選択は、
その要求の複雑さと安定度によって決定されるべきものである。

なお、C++でのstateパターンの実装には、下記に示すようなメンバ関数を使う方法もある。
多くのクラスを作る必要はないが、
各状態での状態管理変数を別の状態のものと分けて管理することができないため、
複雑な状態管理が必要な場合には使えないが、単純な状態管理で十分な場合には便利なパターンである。

```cpp
    //  example/design_pattern/state_machine_new.h 76

    class ThreadNewStyle2 final {
    public:
        ThreadNewStyle2() noexcept {}

        void             Abort() { (this->*abort_)(); }
        void             Run() { (this->*run_)(); }
        void             Suspend() { (this->*suspend_)(); }
        std::string_view GetStateStr() const noexcept { return state_str_; }

    private:
        void (ThreadNewStyle2::*abort_)()   = &ThreadNewStyle2::abort_idle;
        void (ThreadNewStyle2::*run_)()     = &ThreadNewStyle2::run_idle;
        void (ThreadNewStyle2::*suspend_)() = &ThreadNewStyle2::suspend_idle;
        std::string_view state_str_{state_str_idle_};

        void                                 abort_idle() {}  // do nothing
        void                                 run_idle();
        void                                 suspend_idle() {}  // do nothing
        static inline std::string_view const state_str_idle_{"Idle"};

        void                                 abort_running();
        void                                 run_running() {}  // do nothing
        void                                 suspend_running();
        static inline std::string_view const state_str_running_{"Running"};

        void                                 abort_suspending();
        void                                 run_suspending();
        void                                 suspend_suspending() {}  // do nothing
        static inline std::string_view const state_str_suspending_{"Suspending"};
    };
```

```cpp
    //  example/design_pattern/state_machine_new.cpp 106

    void ThreadNewStyle2::run_idle()
    {
        // スレッドの始動処理
        // ...

        // ステートの切り替え
        run_       = &ThreadNewStyle2::run_running;
        suspend_   = &ThreadNewStyle2::suspend_running;
        state_str_ = state_str_running_;
    }

    void ThreadNewStyle2::abort_running()
    {
        // スレッドのアボート処理
        // ...

        // ステートの切り替え
        run_       = &ThreadNewStyle2::run_idle;
        suspend_   = &ThreadNewStyle2::suspend_idle;
        state_str_ = state_str_idle_;
    }

    void ThreadNewStyle2::suspend_running()
    {
        // スレッドのサスペンド処理
        // ...

        // ステートの切り替え
        run_       = &ThreadNewStyle2::run_suspending;
        suspend_   = &ThreadNewStyle2::suspend_suspending;
        state_str_ = state_str_suspending_;
    }

    void ThreadNewStyle2::run_suspending()
    {
        // スレッドのレジューム処理
        // ...

        // ステートの切り替え
        run_       = &ThreadNewStyle2::run_running;
        suspend_   = &ThreadNewStyle2::suspend_running;
        state_str_ = state_str_running_;
    }
```

```cpp
    //  example/design_pattern/state_machine_ut.cpp 95

    TEST(StateMachine, new_style2)
    {
        auto tns = ThreadNewStyle2{};

        ASSERT_EQ("Idle", tns.GetStateStr());

        tns.Run();
        ASSERT_EQ("Running", tns.GetStateStr());

        tns.Suspend();
        ASSERT_EQ("Suspending", tns.GetStateStr());

        tns.Suspend();
        ASSERT_EQ("Suspending", tns.GetStateStr());
    }
```

[演習-State](exercise_q.md#SS_22_9_15)  

## Null Object <a id="SS_9_15"></a>
オブジェクトへのポインタを受け取った関数が
「そのポインタがnullptrでない場合、そのポインタが指すオブジェクトに何かをさせる」
というような典型的な条件文を削減するためのパターンである。

```cpp
    //  example/design_pattern/null_object_ut.cpp 7

    class A {
    public:
        // ...
        bool Action() noexcept
        {
            // do something
            // ...
            return result;
        }
        // ...
    };

    bool ActionOldStyle(A* a) noexcept
    {
        if (a != nullptr) {  // ←このif文を消すためのパターン。
            return a->Action();
        }
        else {
            return false;
        }
    }
```

上記例にNull Objectパターンを適用した例を下記する。

```cpp
    //  example/design_pattern/null_object_ut.cpp 41

    class A {
    public:
        // ...
        bool Action() noexcept { return action(); }

    private:
        virtual bool action() noexcept
        {
            // do something
            // ...
            return result;
        }
        // ...
    };

    class ANull final : public A {
        // ...
    private:
        virtual bool action() noexcept override { return false; }
    };

    bool ActionNewStyle(A& a) noexcept
    {
        return a.Action();  // ←Null Objectによりif文が消えた。
    }
```

この単純な例では、逆にソースコードが複雑化したように見えるが、

```cpp
    if(a != nullptr)
```

を頻繁に使うような関数、
クラスではソースコードの単純化やnullptrチェック漏れの防止に非常に有効である。

[演習-Null Object](exercise_q.md#SS_22_9_16)  

## Templateメソッド <a id="SS_9_16"></a>
Templateメソッドは、雛形の形式(書式等)を定めるメンバ関数(templateメソッド)と、
それを埋めるための振る舞いやデータを定めるメンバ関数を分離するときに用いるパターンである。

以下に実装例を示す。

```cpp
    //  example/design_pattern/template_method.h 6

    /// @brief 何かのデータを入れる箱
    struct XxxData {
        int a;
        int b;
        int c;
    };

    /// @brief data_storer_if.cppに定義すべきだが、サンプルであるため便宜上同じファイルで定義する
    ///        データフォーマットを行うクラスのインターフェースクラス
    class XxxDataFormatterIF {
    public:
        explicit XxxDataFormatterIF(std::string_view formatter_name) noexcept : formatter_name_{formatter_name} {}
        virtual ~XxxDataFormatterIF() = default;

        std::string ToString(XxxData const& xxx_data) const { return header() + body(xxx_data) + footer(); }

        std::string ToString(std::vector<XxxData> const& xxx_datas) const
        {
            std::string ret{header()};

            for (auto const& xxx_data : xxx_datas) {
                ret += body(xxx_data);
            }

            return ret + footer();
        }
        // ...
    private:
        virtual std::string const& header() const                      = 0;
        virtual std::string const& footer() const                      = 0;
        virtual std::string        body(XxxData const& xxx_data) const = 0;

        // ...
    };
```

上記XxxDataFormatterIFでは、以下のようなメンバ関数を宣言、定義している。

|メンバ関数  |                      | 振る舞い                                                 |
|:-----------|:---------------------|:---------------------------------------------------------|
| header()   | private pure-virtual | ヘッダをstd::stringオブジェクトとして生成                |
| footer()   | private pure-virtual | フッタをstd::stringオブジェクトとして生成                |
| body()     | private pure-virtual | XxxDataからボディをstd::stringオブジェクトとして生成     |
| ToString() | public  normal       | header(),body(),footer()の出力を組み合わせた全体像を生成 |

この構造により、XxxDataFormatterIFは、

* 全体の書式を定義している。
* 各行の生成をXxxDataFormatterIFから派生した具象クラスに委譲している。

下記XxxDataFormatterXml、XxxDataFormatterCsv、XxxDataFormatterTableでは、
header()、body()、footer()をオーバーライドすることで、それぞれの機能を実現している。

```cpp
    //  example/design_pattern/template_method.cpp 8

    /// @class XxxDataFormatterXml
    /// @brief XxxDataをXmlに変換
    class XxxDataFormatterXml final : public XxxDataFormatterIF {
        // ...
    private:
        virtual std::string const& header() const noexcept final { return header_; }
        virtual std::string const& footer() const noexcept final { return footer_; }
        virtual std::string        body(XxxData const& xxx_data) const override
        {
            auto content = std::string{"<Item>\n"};

            content += "    <XxxData a=\"" + std::to_string(xxx_data.a) + "\">\n";
            content += "    <XxxData b=\"" + std::to_string(xxx_data.b) + "\">\n";
            content += "    <XxxData c=\"" + std::to_string(xxx_data.c) + "\">\n";

            return content + "</Itemp>\n";
        }

        static inline std::string const header_{"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<XxxDataFormatterXml>\n"};
        static inline std::string const footer_{"</XxxDataFormatterXml>\n"};
    };

    /// @class XxxDataFormatterCsv
    /// @brief XxxDataをCsvに変換
    class XxxDataFormatterCsv final : public XxxDataFormatterIF {
        // ...
    private:
        virtual std::string const& header() const noexcept final { return header_; }
        virtual std::string const& footer() const noexcept final { return footer_; }
        virtual std::string        body(XxxData const& xxx_data) const override
        {
            return std::string{std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
                               + std::to_string(xxx_data.b) + "\n"};
        }

        static inline std::string const header_{"a, b, c\n"};
        static inline std::string const footer_{};
    };

    /// @class XxxDataFormatterTable
    /// @brief XxxDataをTableに変換
    class XxxDataFormatterTable final : public XxxDataFormatterIF {
        // ...
    private:
        virtual std::string const& header() const noexcept final { return header_; }
        virtual std::string const& footer() const noexcept final { return footer_; }
        virtual std::string        body(XxxData const& xxx_data) const override
        {
            auto a = std::string{std::string{"| "} + std::to_string(xxx_data.a)};
            auto b = std::string{std::string{"| "} + std::to_string(xxx_data.b)};
            auto c = std::string{std::string{"| "} + std::to_string(xxx_data.c)};

            a += std::string(colomun_ - a.size() + 1, ' ');
            b += std::string(colomun_ - b.size() + 1, ' ');
            c += std::string(colomun_ - c.size() + 1, ' ');

            return a + b + c + "|\n" + border_;
        }
        // ...
    };
```

以下の単体テストで、これらのクラスの振る舞いを示す。

```cpp
    //  example/design_pattern/template_method_ut.cpp 6

    TEST(TemplateMethod, xml)
    {
        auto xml = XxxDataFormatterXml{};

        {
            auto const xd     = XxxData{1, 100, 10};
            auto const expect = std::string_view{
                "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
                "<XxxDataFormatterXml>\n"
                "<Item>\n"
                "    <XxxData a=\"1\">\n"
                "    <XxxData b=\"100\">\n"
                "    <XxxData c=\"10\">\n"
                "</Itemp>\n"
                "</XxxDataFormatterXml>\n"};
            auto const actual = xml.ToString(xd);

            ASSERT_EQ(expect, actual);
        }
        {
            auto const xds    = std::vector<XxxData>{{1, 100, 10}, {2, 200, 20}};
            auto const expect = std::string_view{
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
            auto const actual = xml.ToString(xds);

            ASSERT_EQ(expect, actual);
        }
    }

    TEST(TemplateMethod, csv)
    {
        auto csv = XxxDataFormatterCsv{};

        {
            auto const xd     = XxxData{1, 100, 10};
            auto const expect = std::string_view{
                "a, b, c\n"
                "1, 100, 100\n"};
            auto const actual = csv.ToString(xd);

            ASSERT_EQ(expect, actual);
        }
        {
            auto const xds    = std::vector<XxxData>{{1, 100, 10}, {2, 200, 20}};
            auto const expect = std::string_view{
                "a, b, c\n"
                "1, 100, 100\n"
                "2, 200, 200\n"};
            auto const actual = csv.ToString(xds);

            ASSERT_EQ(expect, actual);
        }
    }

    TEST(TemplateMethod, table)
    {
        auto table = XxxDataFormatterTable{};

        // ...
    }
```

上記で示した実装例は、public継承による動的ポリモーフィズムを使用したため、
XxxDataFormatterXml、XxxDataFormatterCsv、XxxDataFormatterTableのインスタンスやそのポインタは、
XxxDataFormatterIFのリファレンスやポインタとして表現できる。
この性質は、[Factory](design_pattern.md#SS_9_17)や[Named Constructor](design_pattern.md#SS_9_18)の実装には不可欠であるが、
逆にこのようなポリモーフィズムが不要な場合、このよう柔軟性も不要である。

そういった場合、private継承を用いるか、
テンプレートを用いた静的ポリモーフィズムを用いることでこの柔軟性を排除できる。

下記のコードはそのような実装例である。

```cpp
    //  example/design_pattern/template_method_ut.cpp 112

    #if __cplusplus >= 202002L // c++20
    template <typename T>
    concept DataFormattable = requires(T t, const XxxData& xxx_data) {
        { t.Header() } -> std::convertible_to<std::string>;
        { t.Body(xxx_data) } -> std::convertible_to<std::string>;
        { t.Footer() } -> std::convertible_to<std::string>;
    };
    template <DataFormattable T>  // TはDataFormattableに制約される

    #else // c++17
    template <typename T>  // Tは下記のXxxDataFormatterXmlのようなクラス
    #endif
    class XxxDataFormatter : private T {
    public:
        std::string ToString(XxxData const& xxx_data) const { return T::Header() + T::Body(xxx_data) + T::Footer(); }

        std::string ToString(std::vector<XxxData> const& xxx_datas) const
        {
            auto ret = std::string{T::Header()};

            for (auto const& xxx_data : xxx_datas) {
                ret += T::Body(xxx_data);
            }

            return ret + T::Footer();
        }
    };

    class XxxDataFormatterXml_Impl {
    public:
        std::string const& Header() const noexcept { return header_; }
        std::string const& Footer() const noexcept { return footer_; }
        std::string        Body(XxxData const& xxx_data) const
        {
            auto content = std::string{"<Item>\n"};

            content += "    <XxxData a=\"" + std::to_string(xxx_data.a) + "\">\n";
            content += "    <XxxData b=\"" + std::to_string(xxx_data.b) + "\">\n";
            content += "    <XxxData c=\"" + std::to_string(xxx_data.c) + "\">\n";

            return content + "</Itemp>\n";
        }

    private:
        inline static std::string const header_{"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<XxxDataFormatterXml>\n"};
        inline static std::string const footer_{"</XxxDataFormatterXml>\n"};
    };

    using XxxDataFormatterXml = XxxDataFormatter<XxxDataFormatterXml_Impl>;
```

上記の単体テストは下記のようになる。

```cpp
    //  example/design_pattern/template_method_ut.cpp 168

        auto xml = XxxDataFormatterXml{};

        {
            auto const xd     = XxxData{1, 100, 10};
            auto const expect = std::string{
                "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
                "<XxxDataFormatterXml>\n"
                "<Item>\n"
                "    <XxxData a=\"1\">\n"
                "    <XxxData b=\"100\">\n"
                "    <XxxData c=\"10\">\n"
                "</Itemp>\n"
                "</XxxDataFormatterXml>\n"};
            auto const actual = xml.ToString(xd);

            ASSERT_EQ(expect, actual);
        }
        {
            auto const xds    = std::vector<XxxData>{{1, 100, 10}, {2, 200, 20}};
            auto const expect = std::string{
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
            auto const actual = xml.ToString(xds);

            ASSERT_EQ(expect, actual);
        }
```

[演習-Templateメソッド](exercise_q.md#SS_22_9_17)  

## Factory <a id="SS_9_17"></a>
Factoryは、専用関数(Factory関数)にオブジェクト生成をさせるためのパターンである。
オブジェクトを生成するクラスや関数をそのオブジェクトの生成方法に依存させたくない場合や、
オブジェクトの生成に統一されたルールを適用したい場合等に用いられる。
DI(「[DI(dependency injection)](design_pattern.md#SS_9_12)」参照)と組み合わせて使われることが多い。

「[Templateメソッド](design_pattern.md#SS_9_16)」の例にFactoryを適用したソースコードを下記する。

下記のXxxDataFormatterFactory関数により、

* XxxDataFormatterIFオブジェクトはstd::unique_ptrで保持されることを強制できる
* XxxDataFormatterIFから派生したクラスはtemplate_method.cppの無名名前空間で宣言できるため、
  これらのクラスは他のクラスから直接依存されることがない

といった効果がある。

```cpp
    //  example/design_pattern/template_method.h 65

    enum class XxxDataFormatterMethod {
        Xml,
        Csv,
        Table,
    };

    /// @brief std::unique_ptrで保持されたXxxDataFormatterIFオブジェクトを生成するFactory関数
    /// @param method XxxDataFormatterMethodのいずれか
    /// @return std::unique_ptr<const XxxDataFormatterIF>
    ///         XxxDataFormatterIFはconstメンバ関数のみを持つため、戻り値もconstオブジェクト
    std::unique_ptr<XxxDataFormatterIF const> XxxDataFormatterFactory(XxxDataFormatterMethod method);
```

```cpp
    //  example/design_pattern/template_method.cpp 108

    std::unique_ptr<XxxDataFormatterIF const> XxxDataFormatterFactory(XxxDataFormatterMethod method)
    {
        switch (method) {
        case XxxDataFormatterMethod::Xml:
            return std::unique_ptr<XxxDataFormatterIF const>{new XxxDataFormatterXml};  // C++11
        case XxxDataFormatterMethod::Csv:
            return std::make_unique<XxxDataFormatterCsv const>();  // C++14 make_uniqueもFactory
        case XxxDataFormatterMethod::Table:
            return std::make_unique<XxxDataFormatterTable const>();
        default:
            assert(false);
            return {};
        }
    }
```

以下に上記クラスの単体テストを示す。

```cpp
    //  example/design_pattern/template_method_factory_ut.cpp 7

    TEST(Factory, xml)
    {
        auto xml = XxxDataFormatterFactory(XxxDataFormatterMethod::Xml);

        // ...
    }

    TEST(Factory, csv)
    {
        auto csv = XxxDataFormatterFactory(XxxDataFormatterMethod::Csv);

        // ...
    }

    TEST(Factory, table)
    {
        auto table = XxxDataFormatterFactory(XxxDataFormatterMethod::Table);

        {
            auto const xd     = XxxData{1, 100, 10};
            auto const expect = std::string_view{
                "+--------|--------|--------+\n"
                "| a      | b      | c      |\n"
                "+--------|--------|--------+\n"
                "| 1      | 100    | 10     |\n"
                "+--------|--------|--------+\n"};
            auto const actual = table->ToString(xd);

            ASSERT_EQ(expect, actual);
        }
        {
            auto const xds    = std::vector<XxxData>{{1, 100, 10}, {2, 200, 20}};
            auto const expect = std::string_view{
                "+--------|--------|--------+\n"
                "| a      | b      | c      |\n"
                "+--------|--------|--------+\n"
                "| 1      | 100    | 10     |\n"
                "+--------|--------|--------+\n"
                "| 2      | 200    | 20     |\n"
                "+--------|--------|--------+\n"};
            auto const actual = table->ToString(xds);

            ASSERT_EQ(expect, actual);
        }
    }
```

一般にFactory関数はヒープを使用してオブジェクトを生成する場合が多いため、
それを例示する目的でXxxDataFormatterFactoryもヒープを使用している。

この例ではその必要はないため、ヒープを使用しないFactory関数の例を下記する。

```cpp
    //  example/design_pattern/template_method.cpp 125

    XxxDataFormatterIF const& XxxDataFormatterFactory2(XxxDataFormatterMethod method) noexcept
    {
        static auto xml   = XxxDataFormatterXml{};
        static auto csv   = XxxDataFormatterCsv{};
        static auto table = XxxDataFormatterTable{};

        switch (method) {
        case XxxDataFormatterMethod::Xml:
            return xml;
        case XxxDataFormatterMethod::Csv:
            return csv;
        case XxxDataFormatterMethod::Table:
            return table;
        default:
            assert(false);
            return xml;
        }
    }
```

次に示すのは、このパターンを使用して、プリプロセッサ命令を排除するリファクタリングの例である。

まずは、出荷仕分け向けのプリプロセッサ命令をロジックの内部に記述している問題のあるコードを示す。
このようなオールドスタイルなコードは様々な開発阻害要因になるため、避けるべきである。

```cpp
    // in shipping.h

    #define SHIP_TO_JAPAN 1
    #define SHIP_TO_US 2
    #define SHIP_TO_EU 3

    class ShippingOp {
    public:
        virtual int32_t DoSomething() = 0;
        virtual ~ShippingOp()         = default;
    };
```
```cpp
    // in shipping_japan.h

    class ShippingOp_Japan : public ShippingOp {
    public:
        ShippingOp_Japan();
        int32_t DoSomething() override;
        ~ShippingOp_Japan() override;

    private:
        // 何らかの宣言
    };
```
```cpp
    // in xxx.cpp 仕分けに依存した処理

    // SHIPPINGはmake等のビルドツールから渡される

    #if SHIPPING == SHIP_TO_JAPAN
        auto shipping = ShippingOp_Japan{};
    #elif SHIPPING == SHIP_TO_US
        auto shipping = ShippingOp_US{};
    #elif SHIPPING == SHIP_TO_EU
        auto shipping = ShippingOp_EU{};
    #else
    #error "SHIPPING must be defined"
    #endif

        shipping.DoSomething();
```

このコードは、
関数テンプレートの特殊化を利用したFactoryを以下のように定義することで改善することができる。

```cpp
    // in shipping.h

    // ShippingOpクラスは改善前のコードと同じ

    enum class ShippingRegion { Japan, US, EU };

    template <ShippingRegion>
    std::unique_ptr<ShippingOp> ShippingOpFactory();  // ShippingOpFactory特殊化のための宣言

    template <>
    std::unique_ptr<ShippingOp> ShippingOpFactory<ShippingRegion::Japan>();  // 特殊化関数の宣言

    template <>
    std::unique_ptr<ShippingOp> ShippingOpFactory<ShippingRegion::US>();  // 特殊化関数の宣言

    template <>
    std::unique_ptr<ShippingOp> ShippingOpFactory<ShippingRegion::EU>();  // 特殊化関数の宣言
```
```cpp
    // in shipping_japan.cpp
    // ファクトリーの効果で、ShippingOp_Japanは外部への公開が不要

    class ShippingOp_Japan : public ShippingOp {
    public:
        ShippingOp_Japan();
        int32_t DoSomething() override;
        ~ShippingOp_Japan() override;

    private:
        // 何らかの宣言
    };

    template <>
    std::unique_ptr<ShippingOp> ShippingOpFactory<ShippingRegion::Japan>()
    {
        return std::unique_ptr<ShippingOp>{new ShippingOp_Japan};
    }
```
```cpp
    // in xxx.cpp 仕分けに依存した処理

    // SHIPPINGはmake等のビルドツールからShippingRegionのいづれかとして渡される
    auto shipping = ShippingOpFactory<SHIPPING>();

    shipping->DoSomething();
```

もしくは、
関数オーバーロードを利用したFactoryを以下のように定義することで改善することもできる。

```cpp
    // in shipping.h

    // ShippingOpクラスは改善前のコードと同じ

    enum class ShippingRegion { Japan, US, EU };

    template <ShippingRegion R>
    class ShippingRegion2Type : std::integral_constant<ShippingRegion, R> {
    };

    using ShippingRegionType_Japan = ShippingRegion2Type<ShippingRegion::Japan>;
    using ShippingRegionType_US    = ShippingRegion2Type<ShippingRegion::US>;
    using ShippingRegionType_EU    = ShippingRegion2Type<ShippingRegion::EU>;

    std::unique_ptr<ShippingOp> ShippingOpFactory(ShippingRegionType_Japan);
    std::unique_ptr<ShippingOp> ShippingOpFactory(ShippingRegionType_US);
    std::unique_ptr<ShippingOp> ShippingOpFactory(ShippingRegionType_EU);
```
```cpp
    // in shipping_japan.cpp
    // ファクトリーの効果で、ShippingOp_Japanは外部への公開が不要

    class ShippingOp_Japan : public ShippingOp {
    public:
        ShippingOp_Japan();
        int32_t DoSomething() override;
        ~ShippingOp_Japan() override;

    private:
        // 何らかの宣言
    };

    std::unique_ptr<ShippingOp> ShippingOpFactory(ShippingRegionType_Japan)
    {
        return std::unique_ptr<ShippingOp>{new ShippingOp_Japan};
    }
```
```cpp
    // in xxx.cpp 仕分けに依存した処理

    // SHIPPINGはmake等のビルドツールからShippingRegionのいづれかとして渡される
    auto shipping = ShippingOpFactory(ShippingRegion2Type<SHIPPING>{});

    shipping->DoSomething();
```

[演習-Factory](exercise_q.md#SS_22_9_18)  

## Named Constructor <a id="SS_9_18"></a>
Named Connstructorは、[Singleton](design_pattern.md#SS_9_13)のようなオブジェクトを複数、生成するためのパターンである。

```cpp
    //  example/design_pattern/enum_operator.h 76

    class Mammals : public Animal {  // 哺乳類
    public:
        static Mammals& Human() noexcept
        {
            static auto inst = Mammals{PhisicalAbility::Run | PhisicalAbility::Swim};
            return inst;
        }

        static Mammals& Bat() noexcept
        {
            static auto inst = Mammals{PhisicalAbility::Run | PhisicalAbility::Fly};
            return inst;
        }

        static Mammals& Whale() noexcept
        {
            static auto inst = Mammals{PhisicalAbility::Swim};
            return inst;
        }

        bool Act();

    private:
        Mammals(PhisicalAbility pa) noexcept : Animal{pa} {}
    };
```

上記例のHuman()、Bat()、Whale()は、人、コウモリ、クジラに対応するクラスMammalsオブジェクトを返す。

次に示したのは「[Factory](design_pattern.md#SS_9_17)」の例にこのパターンを適応したコードである。

```cpp
    //  example/design_pattern/template_method.h 15

    /// @brief data_storer_if.cppに定義すべきだが、サンプルであるため便宜上同じファイルで定義する
    ///        データフォーマットを行うクラスのインターフェースクラス
    class XxxDataFormatterIF {
    public:
        explicit XxxDataFormatterIF(std::string_view formatter_name) noexcept : formatter_name_{formatter_name} {}
        virtual ~XxxDataFormatterIF() = default;

        static XxxDataFormatterIF const& Xml() noexcept;
        static XxxDataFormatterIF const& Csv() noexcept;
        static XxxDataFormatterIF const& Table() noexcept;

        // ...
    };
```

```cpp
    //  example/design_pattern/template_method.cpp 146

    XxxDataFormatterIF const& XxxDataFormatterIF::Xml() noexcept
    {
        static auto xml = XxxDataFormatterXml{};

        return xml;
    }

    XxxDataFormatterIF const& XxxDataFormatterIF::Csv() noexcept
    {
        static auto csv = XxxDataFormatterCsv{};

        return csv;
    }

    XxxDataFormatterIF const& XxxDataFormatterIF::Table() noexcept
    {
        static auto table = XxxDataFormatterTable{};

        return table;
    }
```

これまでにXxxDataFormatterIFオブジェクトを取得するパターンを以下のように3つ示した。

1. Factory関数によってstd::unique_ptr\<XxxDataFormatterIF>オブジェクトを返す。
2. Factory関数によってstaticなXxxDataFormatterIFオブジェクトを返す。
3. Named ConstructorによってstaticなXxxDataFormatterIFオブジェクトを返す。

最も汎用的な方法はパターン1であるが、
上記例のようにオブジェクトが状態を持たない場合、これは過剰な方法であり、
パターン3が最適であるように思える。このような考察からわかるように、
(単にnewする場合も含めて)オブジェクトの取得にどのような方法を用いるかは、
クラスの性質に依存する。

[演習-Named Constructor](exercise_q.md#SS_22_9_19)  

## Proxy <a id="SS_9_19"></a>
Proxyとは代理人という意味で、
本物のクラスに代わり代理クラス(Proxy)が処理を受け取る
(実際は、処理自体は本物クラスに委譲されることもある)パターンである。

以下の順番で例を示すことで、Proxyパターンの説明を行う。

1. 内部構造を外部公開しているサーバ クラス
2. そのサーバをラッピングして、使いやすくしたサーバ クラス(Facadeパターン)
3. サーバをラップしたクラスのProxyクラス

まずは、内部構造を外部公開しているの醜悪なサーバの実装例である。

```cpp
    //  example/design_pattern/bare_server.h 5

    enum class Cmd {
        SayHello,
        SayGoodbye,
        Shutdown,
    };

    struct Packet {
        Cmd cmd;
    };

    class BareServer final {
    public:
        BareServer() noexcept;
        ~BareServer();
        int GetPipeW() const noexcept  // クライアントのwrite用
        {
            return to_server_[1];
        }

        int GetPipeR() const noexcept  // クライアントのread用
        {
            return to_client_[0];
        }

        void Start();
        void Wait() noexcept;

    private:
        int         to_server_[2];  // サーバへの通信用
        int         to_client_[2];  // クライアントへの通信用
        std::thread thread_;
    };
```

```cpp
    //  example/design_pattern/bare_server.cpp 9

    namespace {
    bool cmd_dispatch(int wfd, Cmd cmd) noexcept
    {
        static char const hello[]   = "Hello";
        static char const goodbye[] = "Goodbye";

        switch (cmd) {
        case Cmd::SayHello:
            write(wfd, hello, sizeof(hello));
            break;
        case Cmd::SayGoodbye:
            write(wfd, goodbye, sizeof(goodbye));
            break;
        case Cmd::Shutdown:
        default:
            std::cout << "Shutdown" << std::endl;
            return false;
        }

        return true;
    }

    void thread_entry(int rfd, int wfd) noexcept
    {
        for (;;) {
            auto packet = Packet{};

            if (read(rfd, &packet, sizeof(packet)) < 0) {
                continue;
            }

            if (!cmd_dispatch(wfd, packet.cmd)) {
                break;
            }
        }
    }
    }  // namespace

    BareServer::BareServer() noexcept : to_server_{-1, -1}, to_client_{-1, -1}, thread_{}
    {
        auto ret = pipe(to_server_);
        assert(ret >= 0);

        ret = pipe(to_client_);
        assert(ret >= 0);
    }

    BareServer::~BareServer()
    {
        close(to_server_[0]);
        close(to_server_[1]);
        close(to_client_[0]);
        close(to_client_[1]);
    }

    void BareServer::Start()
    {
        thread_ = std::thread{thread_entry, to_server_[0], to_client_[1]};
        std::cout << "thread started !!!" << std::endl;
    }

    void BareServer::Wait() noexcept { thread_.join(); }
```

下記は、上記BareServerを使用するクライアントの実装例である。通信がpipe()によって行われ、
その中身がPacket{}であること等、不要な依存関係をbare_client()に強いていることがわかる。
このような構造は、機能追加、保守作業を非効率、困難にするアンチパターンである。

```cpp
    //  example/design_pattern/proxy_ut.cpp 17

    /// @brief 非同期サービスを隠蔽していないBareServerを使用したときのクライアントの例
    std::vector<std::string> bare_client(BareServer& bs)
    {
        auto const wfd = bs.GetPipeW();
        auto const rfd = bs.GetPipeR();
        auto       ret = std::vector<std::string>{};

        bs.Start();

        auto packet = Packet{};
        char buffer[30];

        packet.cmd = Cmd::SayHello;
        write(wfd, &packet, sizeof(packet));

        auto read_ret = read(rfd, buffer, sizeof(buffer));
        assert(read_ret > 0);

        ret.emplace_back(buffer);

        packet.cmd = Cmd::SayGoodbye;
        write(wfd, &packet, sizeof(packet));

        read_ret = read(rfd, buffer, sizeof(buffer));
        assert(read_ret > 0);

        ret.emplace_back(buffer);

        packet.cmd = Cmd::Shutdown;
        write(wfd, &packet, sizeof(packet));

        bs.Wait();

        return ret;
    }
```

次に、このむき出しの構造をラッピングする例を示す(このようなラッピングをFacadeパターンと呼ぶ)。

```cpp
    //  example/design_pattern/bare_server_wrapper.h 6

    enum class Cmd;  // C++11からenumは前方宣言できる。
    class BareServer;

    class BareServerWrapper final {
    public:
        BareServerWrapper();

        void        Start();
        std::string SayHello();
        std::string SayGoodbye();
        void        Shutdown() noexcept;

    private:
        void                        send_message(enum Cmd cmd) noexcept;
        std::unique_ptr<BareServer> bare_server_;
    };
```

```cpp
    //  example/design_pattern/bare_server_wrapper.cpp 8

    BareServerWrapper::BareServerWrapper() : bare_server_{std::make_unique<BareServer>()} {}

    void BareServerWrapper::Start() { bare_server_->Start(); }

    void BareServerWrapper::send_message(enum Cmd cmd) noexcept
    {
        auto packet = Packet{cmd};

        write(bare_server_->GetPipeW(), &packet, sizeof(packet));
    }

    std::string BareServerWrapper::SayHello()
    {
        char buffer[30];

        send_message(Cmd::SayHello);
        read(bare_server_->GetPipeR(), buffer, sizeof(buffer));

        return buffer;
    }

    std::string BareServerWrapper::SayGoodbye()
    {
        char buffer[30];

        send_message(Cmd::SayGoodbye);
        read(bare_server_->GetPipeR(), buffer, sizeof(buffer));

        return buffer;
    }

    void BareServerWrapper::Shutdown() noexcept
    {
        send_message(Cmd::Shutdown);

        bare_server_->Wait();
    }
```

下記は、上記BareServerWrapperのクライアントの実装例である。
BareServerWrapperがむき出しの通信をラップしたことで、bare_wrapper_client()は、
bare_client()に比べてシンプルになったことがわかる。

```cpp
    //  example/design_pattern/proxy_ut.cpp 56

    /// @brief BareServerを使いやすくラップしたBareServerWrapperを使用したときのクライアントの例
    std::vector<std::string> bare_wrapper_client(BareServerWrapper& bsw)
    {
        auto ret = std::vector<std::string>{};

        bsw.Start();

        ret.emplace_back(bsw.SayHello());

        ret.emplace_back(bsw.SayGoodbye());

        bsw.Shutdown();

        return ret;
    }
```

次の例は、BareServerとBareServerWrapperを統合し、
さらに全体をシンプルにリファクタリングしたWrappedServerである。
Packet{}やpipe等の通信の詳細がwrapped_server.cppの無名名前空間に閉じ込められ、
クラスの隠蔽性が強化されたことで、より機能追加、保守が容易になった。

```cpp
    //  example/design_pattern/wrapped_server.h 5

    class WrappedServer {
    public:
        WrappedServer() noexcept;
        virtual ~WrappedServer();

        void        Start();
        std::string SayHello() { return say_hello(); }
        std::string SayGoodbye() { return say_goodbye(); }
        void        Shutdown() noexcept;

    protected:
        virtual std::string say_hello();    // 後で拡張するためにvirtual
        virtual std::string say_goodbye();  // 同上

    private:
        int         to_server_[2];
        int         to_client_[2];
        std::thread thread_;
    };
```

```cpp
    //  example/design_pattern/wrapped_server.cpp 8

    namespace {
    enum class Cmd {
        // ...
    };

    struct Packet {
        Cmd cmd;
    };
    }  // namespace

    // 以下、bare_server_wrapper.cppのコードとほぼ同じであるため省略。

    // ...
```

WrappedServerの使用例を下記する。当然ながらbare_wrapper_client()とほぼ同様になる。

```cpp
    //  example/design_pattern/proxy_ut.cpp 75

    /// @brief 非同期サービスを隠蔽しているWrappedServerを使用したときのクライアントの例
    std::vector<std::string> wrapped_client(WrappedServer& ws)
    {
        auto ret = std::vector<std::string>{};

        ws.Start();

        ret.emplace_back(ws.SayHello());

        ret.emplace_back(ws.SayGoodbye());

        ws.Shutdown();

        return ret;
    }
```

WrappedServerが提供する機能はスレッド間通信を含むため処理コストが高い。
その対策として、サーバから送られてきた文字列をキャッシュするクラス(Proxyパターン)の導入により、
そのコストを削減する例を下記する。

```cpp
    //  example/design_pattern/wrapped_server_proxy.h 7

    class WrappedServerProxy final : public WrappedServer {
    public:
        WrappedServerProxy() = default;

    private:
        std::string         hello_cashe_{};
        virtual std::string say_hello() override;
        virtual std::string say_goodbye() override;
    };
```

```cpp
    //  example/design_pattern/wrapped_server_proxy.cpp 7

    std::string WrappedServerProxy::say_hello()
    {
        if (hello_cashe_.size() == 0) {
            hello_cashe_ = WrappedServer::say_hello();  // キャッシュとし保存
        }

        return hello_cashe_;
    }

    std::string WrappedServerProxy::say_goodbye()
    {
        hello_cashe_ = std::string{};  // helloキャッシュをクリア

        return WrappedServer::say_goodbye();
    }
```

下記図のようにWrappedServerProxyはWrappedServerからのパブリック継承であるため、
WrappedServerのクライアントは、そのままWrappedServerProxyのクライアントとして利用できる。

<!-- pu:essential/plant_uml/proxy.pu--><p><img src="data:image/png;base64,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" /></p>

なお、正確には下記のようなクラス構造をProxyパターンと呼ぶことが多いが、
ここでは単純さを優先した。

<!-- pu:essential/plant_uml/proxy_general.pu--><p><img src="data:image/png;base64,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" /></p>

[演習-Proxy](exercise_q.md#SS_22_9_20)  

## Strategy <a id="SS_9_20"></a>
関数f(args)の振る舞いが、

* 全体の制御
* 部分的な振る舞い(何らかの条件を探す等)

に分けられるような場合、関数fを

* 「全体の制御」を行う関数g
* 「部分的な振る舞い」を規定するStrategyオブジェクト(関数へのポインタ、関数オブジェクト、ラムダ式)

に分割し、下記のように、Strategyオブジェクトをgの引数として外部から渡せるようにしたパターンである
(std::sort()のようなパターン)。

```cpp
    g(args, Strategyオブジェクト)
```

Strategyオブジェクトにいろいろなバリエーションがある場合、このパターンを使うと良い。
なお、このパターンの対象はクラスになる場合もある。

「ディレクトリをリカーシブに追跡し、引数で指定された属性にマッチしたファイルの一覧を返す関数」
を開発することを要求されたとする。

まずは、拡張性のない実装例を示す。

```cpp
    //  example/design_pattern/find_files_old_style.h 4

    /// @enum FindCondition
    /// find_files_recursivelyの条件
    enum class FindCondition {
        File,              ///< pathがファイル
        Dir,               ///< pathがディレクトリ
        FileNameHeadIs_f,  ///< pathがファイル且つ、そのファイル名の先頭が"f"
    };
```

```cpp
    //  example/design_pattern/find_files_old_style.cpp 9

    /// @brief 条件にマッチしたファイルをリカーシブに探して返す
    /// @param path      リカーシブにディレクトリをたどるための起点となるパス
    /// @param condition どのようなファイルかを指定する
    /// @return 条件にマッチしたファイルをstd::vector<std::string>で返す
    std::vector<std::string> find_files_recursively(std::string const& path, FindCondition condition)
    {
        auto files = std::vector<fs::path>{};

        // recursive_directory_iteratorはファイルシステム依存するため、その依存を排除する他の処理
        std::copy(fs::recursive_directory_iterator{path}, fs::recursive_directory_iterator{}, std::back_inserter(files));

        std::sort(files.begin(), files.end());

        auto ret = std::vector<std::string>{};

        std::for_each(files.begin(), files.end(), [&](fs::path const& p) noexcept {
            auto is_match = false;

            switch (condition) {
            case FindCondition::File:
                if (fs::is_regular_file(p)) {
                    is_match = true;
                }
                break;
            case FindCondition::Dir:
                if (fs::is_directory(p)) {
                    is_match = true;
                }
                break;
                // ...
            }

            if (is_match) {
                ret.emplace_back(p.generic_string());
            }
        });

        return ret;
    }
```

```cpp
    //  example/design_pattern/find_files_ut.cpp 29

    TEST(Strategy, old_style)
    {
        assure_test_files_exist();  // test用のファイルがあることの確認

        auto const files_actual = find_files_recursively(test_dir, FindCondition::File);
        auto const files_expect = sort(std::vector{
            test_dir + "dir0/file2",
            test_dir + "dir0/gile3",
            test_dir + "dir1/dir2/file4",
            test_dir + "file0",
            test_dir + "gile1"
        });
        ASSERT_EQ(files_expect, files_actual);

        auto const dirs_actual = find_files_recursively(test_dir, FindCondition::Dir);
        auto const dirs_expect = sort(std::vector{
            test_dir + "dir0",
            test_dir + "dir1",
            test_dir + "dir1/dir2"
        });
        ASSERT_EQ(dirs_expect, dirs_actual);

        auto const f_actual = find_files_recursively(test_dir, FindCondition::FileNameHeadIs_f);
        auto const f_expect = sort(std::vector{
            test_dir + "dir0/file2",
            test_dir + "dir1/dir2/file4",
            test_dir + "file0"
        });
        ASSERT_EQ(f_expect, f_actual);
    }
```

この関数は、見つかったファイルが「引数で指定された属性」にマッチするかどうかを検査する。
検査は、「引数で指定された属性」に対するswitch文によって行われる。
これにより、この関数は「引数で指定された属性」の変更に強く影響を受ける。

下記は、この関数にStrategyパターンを適用したものである。

```cpp
    //  example/design_pattern/find_files_strategy.h 7

    /// @typedef find_condition
    /// @brief find_files_recursively仮引数conditionの型(関数オブジェクトの型)
    using find_condition = std::function<bool(std::filesystem::path const&)>;

    // Strategyパターン
    /// @fn std::vector<std::string> find_files_recursively(std::string const& path,
    ///                                                     find_condition     condition);
    /// @brief 条件にマッチしたファイルをリカーシブに探索して返す
    /// @param path      リカーシブにディレクトリを辿るための起点となるパス
    /// @param condition 探索するファイルの条件
    /// @return 条件にマッチしたファイルをstd::vector<std::string>で返す
    extern std::vector<std::string> find_files_recursively(std::string const& path, find_condition condition);
```

```cpp
    //  example/design_pattern/find_files_strategy.cpp 6

    std::vector<std::string> find_files_recursively(std::string const& path, find_condition condition)
    {
        namespace fs = std::filesystem;

        auto files = std::vector<fs::path>{};

        // recursive_directory_iteratorはファイルシステム依存するため、その依存を排除する他の処理
        std::copy(fs::recursive_directory_iterator{path}, fs::recursive_directory_iterator{}, std::back_inserter(files));

        std::sort(files.begin(), files.end());

        auto ret = std::vector<std::string>{};

        std::for_each(files.cbegin(), files.cend(), [&](fs::path const& p) {
            if (condition(p)) {
                ret.emplace_back(p.generic_string());
            }
        });

        return ret;
    }
```

```cpp
    //  example/design_pattern/find_files_ut.cpp 69

    TEST(Strategy, strategy_lamda)
    {
        namespace fs = std::filesystem;

        assure_test_files_exist();  // test用のファイルがあることの確認

        // ラムダ式で実装
        auto const files_actual
            = find_files_recursively(test_dir, [](fs::path const& p) noexcept { return fs::is_regular_file(p); });

        auto const files_expect = sort(std::vector{
            test_dir + "dir0/file2",
            test_dir + "dir0/gile3",
            test_dir + "dir1/dir2/file4",
            test_dir + "file0",
            test_dir + "gile1"
        });
        ASSERT_EQ(files_expect, files_actual);

        auto const dirs_actual
            = find_files_recursively(test_dir, [](fs::path const& p) noexcept { return fs::is_directory(p); });
        auto const dirs_expect = sort(std::vector{
            test_dir + "dir0",
            test_dir + "dir1",
            test_dir + "dir1/dir2"
        });
        ASSERT_EQ(dirs_expect, dirs_actual);

        auto const f_actual = find_files_recursively(
            test_dir, [](fs::path const& p) noexcept { return p.filename().generic_string()[0] == 'f'; });

        auto const f_expect = sort(std::vector{
            test_dir + "dir0/file2",
            test_dir + "dir1/dir2/file4",
            test_dir + "file0"
        });
        ASSERT_EQ(f_expect, f_actual);
    }

    /// @brief find_files_recursivelyの第2仮引数に渡すためのファイル属性を決める関数
    bool condition_func(std::filesystem::path const& path) { return path.filename().generic_string().at(0) == 'f'; }

    TEST(Strategy, strategy_func_pointer)
    {
        assure_test_files_exist();  // test用のファイルがあることの確認

        // FindCondition::FileNameHeadIs_fで行ったことを関数ポインタで実装。
        auto const f_actual = find_files_recursively(test_dir, condition_func);
        auto const f_expect = sort(std::vector{
            test_dir + "dir0/file2",
            test_dir + "dir1/dir2/file4",
            test_dir + "file0"
        });
        ASSERT_EQ(f_expect, f_actual);
    }

    /// @brief
    ///  find_files_recursivelyの第2仮引数に渡すためのファイル属性を決める関数オブジェクトクラス。
    ///  検索条件に状態が必要な場合、関数オブジェクトを使うとよい。
    class ConditionFunctor {
    public:
        ConditionFunctor()  = default;
        ~ConditionFunctor() = default;

        /// @brief 先頭が'f'のファイルを最大2つまで探す
        bool operator()(std::filesystem::path const& path)
        {
            if (path.filename().generic_string().at(0) != 'f') {
                return false;
            }

            return ++count_ < 3;
        }

    private:
        int32_t count_{0};
    };

    TEST(Strategy, strategy_func_obj)
    {
        // 条件に状態が必要な場合(この例では最大2つまでを判断するのに状態が必要)、
        // 関数ポインタより、ファンクタの方が便利。
        auto const f_actual = find_files_recursively(test_dir, ConditionFunctor{});
        auto const f_expect = sort(std::vector{
            test_dir + "dir0/file2",
            test_dir + "dir1/dir2/file4",
        });
        ASSERT_EQ(f_expect, f_actual);
    }
```

捜査対象のファイル属性の指定をfind_files_recursively()の外に出しため、
その属性の追加に対して「[オープン・クローズドの原則(OCP)](solid.md#SS_8_2)」に対応した構造となった。

なお、上記find_files_recursivelyの第2パラメータをテンプレートパラメータとすることで、

```cpp
    //  example/design_pattern/find_files_strategy.h 22

    #if __cplusplus >= 202002L  // c++20
    // ファンクタがboolを返し、std::filesystem::path const&を引数に取るかを確認するコンセプト
    namespace Inner_ {
    template <typename F>
    concept find_condition = requires(F f, std::filesystem::path const& p)
    {
        { f(p) } -> std::same_as<bool>;
    };
    }  // namespace Inner_

    template <Inner_::find_condition F>
    auto find_files_recursively2(std::string const& path, F condition)
        -> std::enable_if_t<std::is_invocable_r_v<bool, F, std::filesystem::path const&>, std::vector<std::string>>

    #else  // c++17
    template <typename F>  // Fはファンクタ
    auto find_files_recursively2(std::string const& path, F&& condition) -> std::vector<std::string>
    #endif
    {
        namespace fs = std::filesystem;

        auto files = std::vector<fs::path>{};

        // recursive_directory_iteratorでディレクトリ内のファイルを再帰的に取得
        std::copy(fs::recursive_directory_iterator{path}, fs::recursive_directory_iterator{}, std::back_inserter(files));

        std::sort(files.begin(), files.end());  // ファイルリストをソート

        auto ret = std::vector<std::string>{};

        std::for_each(files.cbegin(), files.cend(), [&](fs::path const& p) {
            if (condition(p)) {  // 条件を満たすファイルをretに追加
                ret.emplace_back(p.generic_string());
            }
        });

        return ret;
    }
```

のように書くこともできる。

次に示すのは、このパターンを使用して、プリプロセッサ命令を排除するリファクタリングの例である。

まずは、出荷仕分け向けのプリプロセッサ命令をロジックの内部に記述している問題のあるコードを示す。
このようなオールドスタイルなコードは様々な開発阻害要因になるため、避けるべきである。

```cpp
    //  example/design_pattern/strategy_shipping_ut.cpp 11

    class X {
    public:
        X() = default;

        int32_t DoSomething()
        {
            int32_t ret{0};

    #if SHIPPING == SHIP_TO_JAPAN
            // 日本向けの何らかの処理
    #elif SHIPPING == SHIP_TO_US
            // US向けの何らかの処理
    #elif SHIPPING == SHIP_TO_JAPAN
            // EU向けの何らかの処理
    #else
    #error "SHIPPING must be defined"
    #endif
            return ret;
        }

    private:
        // 何らかの宣言
    };
```
```cpp
    //  example/design_pattern/strategy_shipping_ut.cpp 43

    X x;

    x.DoSomething();
```

このコードは、Strategyを使用し以下のようにすることで、改善することができる。

```cpp
    //  example/design_pattern/strategy_shipping_ut.cpp 56

    class ShippingOp {
    public:
        virtual int32_t DoSomething() = 0;
        virtual ~ShippingOp()         = default;
    };

    class X {
    public:
        X() = default;

        int32_t DoSomething(ShippingOp& shipping)
        {
            int32_t ret = shipping.DoSomething();

            // 何らかの処理

            return ret;
        }

    private:
        // 何らかの宣言
    };
```
```cpp
    //  example/design_pattern/strategy_shipping_ut.cpp 81

    class ShippingOp_Japan : public ShippingOp {
    public:
        ShippingOp_Japan();
        int32_t DoSomething() override;
        ~ShippingOp_Japan() override;

    private:
        // 何らかの宣言
    };
```
```cpp
    //  example/design_pattern/strategy_shipping_ut.cpp 100

    X                x;
    ShippingOp_Japan sj;

    x.DoSomething(sj);
```

あるいは、[DI(dependency injection)](design_pattern.md#SS_9_12)と組み合わせて、下記のような改善も有用である。

```cpp
    //  example/design_pattern/strategy_shipping_ut.cpp 112

    class ShippingOp {
    public:
        virtual int32_t DoSomething() = 0;
        virtual ~ShippingOp()         = default;
    };

    class X {
    public:
        explicit X(std::unique_ptr<ShippingOp> shipping) : shipping_{std::move(shipping)} {}

        int32_t DoSomething()
        {
            int32_t ret = shipping_->DoSomething();

            // 何らかの処理

            return ret;
        }

    private:
        std::unique_ptr<ShippingOp> shipping_;
        // 何らかの宣言
    };
```
```cpp
    //  example/design_pattern/strategy_shipping_ut.cpp 138

    class ShippingOp_Japan : public ShippingOp {
    public:
        ShippingOp_Japan();
        int32_t DoSomething() override;
        ~ShippingOp_Japan() override;

    private:
        // 何らかの宣言
    };
```
```cpp
    //  example/design_pattern/strategy_shipping_ut.cpp 157

    X x{std::unique_ptr<ShippingOp>(new ShippingOp_Japan)};

    x.DoSomething();
```

[演習-Strategy](exercise_q.md#SS_22_9_21)  

## Visitor <a id="SS_9_21"></a>
このパターンは、クラス構造とそれに関連するアルゴリズムを分離するためのものである。

最初に
「クラス構造とそれに関連するアルゴリズムは分離できているが、
それ以前にオブジェクト指向の原則に反している」
例を示す。

```cpp
    //  example/design_pattern/visitor.cpp 42

    /// @brief
    ///  ファイルシステムの構成物(ファイル、ディレクトリ等)を表すクラスの基底クラス
    class FileEntity {
    public:
        explicit FileEntity(std::string pathname) : pathname_{std::move(pathname)} {}
        virtual ~FileEntity() {}
        std::string const& Pathname() const { return pathname_; }

        // ...

    private:
        std::string const pathname_;
    };

    class File final : public FileEntity {
        // ...
    };

    class Dir final : public FileEntity {
        // ...
    };

    class OtherEntity final : public FileEntity {
        // ...
    };

    class Printer {
    public:
        static void PrintPathname1(FileEntity const& file_entity)
        {
            if (typeid(File) == typeid(file_entity)) {
                std::cout << file_entity.Pathname();
            }
            else if (typeid(Dir) == typeid(file_entity)) {
                std::cout << file_entity.Pathname() + "/";
            }
            else if (typeid(OtherEntity) == typeid(file_entity)) {
                std::cout << file_entity.Pathname() + "(o1)";
            }
            else {
                assert(false);
            }
        }

        static void PrintPathname2(FileEntity const& file_entity)
        {
            if (typeid(File) == typeid(file_entity)) {
                std::cout << file_entity.Pathname();
            }
            else if (typeid(Dir) == typeid(file_entity)) {
                std::cout << find_files(file_entity.Pathname());
            }
            else if (typeid(OtherEntity) == typeid(file_entity)) {
                std::cout << file_entity.Pathname() + "(o2)";
            }
            else {
                assert(false);
            }
        }
    };
```

下記クラス図からもわかる通り、ポリモーフィズムに反したこのような構造は複雑な依存関係を作り出す。
このアンチパターンにより同型の条件文が2度出てきてしまうため、
Printerのアルゴリズム関数が増えれば、この繰り返しはそれに比例して増える。
またFileEntityの派生が増えれば、それら条件文はすべて影響を受ける。
このようなソースコードは、このようにして等比級数的に複雑化する。

<!-- pu:essential/plant_uml/visitor_ng1.pu--><p><img src="data:image/png;base64,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" /></p>

これをポリモーフィズムの導入で解決した例を示す。

```cpp
    //  example/design_pattern/visitor.cpp 142

    class FileEntity {
    public:
        explicit FileEntity(std::string pathname) : pathname_{std::move(pathname)} {}
        // ...
        virtual void PrintPathname1() const = 0;
        virtual void PrintPathname2() const = 0;

    private:
        std::string const pathname_;
    };

    class File final : public FileEntity {
    public:
        // ...
        virtual void PrintPathname1() const override { std::cout << Pathname(); }
        virtual void PrintPathname2() const override { std::cout << Pathname(); }
    };

    class Dir final : public FileEntity {
    public:
        // ...
        virtual void PrintPathname1() const override { std::cout << Pathname() + "/"; }
        virtual void PrintPathname2() const override { std::cout << find_files(Pathname()); }
    };

    class OtherEntity final : public FileEntity {
    public:
        // ...
        virtual void PrintPathname1() const override { std::cout << Pathname() + "(o1)"; }
        virtual void PrintPathname2() const override { std::cout << Pathname() + "(o2)"; }
    };

    class Printer {
    public:
        static void PrintPathname1(FileEntity const& file_entity) { file_entity.PrintPathname1(); }
        static void PrintPathname2(FileEntity const& file_entity) { file_entity.PrintPathname2(); }
    };
```

上記例では、PrinterのアルゴリズムをFileEntityの各派生クラスのメンバ関数で実装することで、
Printerの各関数は単純化された。

<!-- pu:essential/plant_uml/visitor_ng2.pu--><p><img src="data:image/png;base64,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" /></p>

これはポリモーフィズムによるリファクタリングの良い例と言えるが、
SRP(「[単一責任の原則(SRP)](solid.md#SS_8_1)」)に反するため、
Printerの関数が増えるたびにPrintPathname1、
PrintPathname2のようなFileEntityのインターフェースが増えてしまう。

このようなインターフェースの肥大化に対処するパターンがVisitorである。

上記例にVisitorを適用してリファクタリングした例を示す。

```cpp
    //  example/design_pattern/visitor.h 9

    class FileEntityVisitor {
    public:
        virtual void Visit(File const&)        = 0;
        virtual void Visit(Dir const&)         = 0;
        virtual void Visit(OtherEntity const&) = 0;
        // ...
    };

    class FileEntity {
    public:
        explicit FileEntity(std::string pathname) : pathname_{std::move(pathname)} {}
        // ...
        std::string const& Pathname() const { return pathname_; }

        virtual void Accept(FileEntityVisitor&) const = 0;  // Acceptの仕様は安定しているので
                                                            // NVIは使わない。
    private:
        std::string const pathname_;
    };

    class File final : public FileEntity {
    public:
        using FileEntity::FileEntity;
        virtual void Accept(FileEntityVisitor& visitor) const override { visitor.Visit(*this); }
    };

    class Dir final : public FileEntity {
    public:
        using FileEntity::FileEntity;
        virtual void Accept(FileEntityVisitor& visitor) const override { visitor.Visit(*this); }
    };

    class OtherEntity final : public FileEntity {
    public:
        using FileEntity::FileEntity;
        virtual void Accept(FileEntityVisitor& visitor) const override { visitor.Visit(*this); }
    };

    class PathnamePrinter1 final : public FileEntityVisitor {
    public:
        virtual void Visit(File const&) override;
        virtual void Visit(Dir const&) override;
        virtual void Visit(OtherEntity const&) override;
    };

    class PathnamePrinter2 final : public FileEntityVisitor {
    public:
        virtual void Visit(File const&) override;
        virtual void Visit(Dir const&) override;
        virtual void Visit(OtherEntity const&) override;
    };
```

```cpp
    //  example/design_pattern/visitor.cpp 218

    void PathnamePrinter1::Visit(File const& file) { std::cout << file.Pathname(); }
    void PathnamePrinter1::Visit(Dir const& dir) { std::cout << dir.Pathname() + "/"; }
    void PathnamePrinter1::Visit(OtherEntity const& other) { std::cout << other.Pathname() + "(o1)"; }

    void PathnamePrinter2::Visit(File const& file) { std::cout << file.Pathname(); }
    void PathnamePrinter2::Visit(Dir const& dir) { std::cout << find_files(dir.Pathname()); }
    void PathnamePrinter2::Visit(OtherEntity const& other) { std::cout << other.Pathname() + "(o2)"; }

    class Printer {
    public:
        static void PrintPathname1(FileEntity const& file_entity)
        {
            auto visitor = PathnamePrinter1{};

            file_entity.Accept(visitor);
        }

        static void PrintPathname2(FileEntity const& file_entity)
        {
            auto visitor = PathnamePrinter2{};

            file_entity.Accept(visitor);
        }
    };
```

上記クラスの関係は下記のようになる。

<!-- pu:essential/plant_uml/visitor_ok.pu--><p><img src="data:image/png;base64,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U1OVXONMurBhwwZzc3PShatXr0qrAdA6irU0MK5du+bg4DBkyBC8rqK48ddff0VEROjr66vbDf3KRtOlwc3NTUdHh5UPHDhgbGycnp7+fhOlQ0OOdevWmZmZ/fTTT7QPkVYDoKVAGv4HP14dFxcnrQPaTlpamrOzM40UMzMzpXVaikZLw++//163bl12pOHo0aOGhoY3b96UNlImpAuxsbGtW7emkUZqaqq0GgCtBtLwNzRY6datW69evSiLSOuAVvPmzZvly5cXn9txNVoatm7dWqtWrdq1a586dcrAwKAoTwqQLkRHR5uamg4fPvzGjRvSagCKAZCG93j79u2GDRsoecyePfvFixfSaqDVkDV26dJlwIABqrqersjQaGno1KlTtWrVdHR0qomoX79+cHCw8p77Sbqwdu1aExMTT0/PIj6wAYBaAWlQgCAI/v7+NJ5ISEiQ1gGt5s2bN5GRkVp/okpzpeH333+vVauWWBdq167dr1+/J0+eSJsWEq9evVq9erWxsbGXl9ft27el1QAUMyAN+XL16lVnZ+eePXveuXNHWge0mrt373bt2pVSkbYectBcaVi1ahVzhQYyJkyYoLyjC6QLK1euNDIyGjVqFHYCADAgDf8AjTgNDAxmzZr166+/SuuA9vL27VtKGPr6+hs2bJDWaT6aKw1t27Zt0qRJ06ZNZ86cqTxdePnyZWRkpKGhobe3N65wAkAMpOGfEQQhICCA1CE6OvrPP/+UVgPt5d69e926devbt6/80e/ff/998eLFYWFhszWQ2rVrS0OaQEhISP369UePHq08Xfjjjz9IF+g/u4+PT9HfxgmA+gNp+FhoDzJkyBArK6t9+/ZJ64D28vbt29WrV+vr669bt04cX7Jkyd27dwVQhJDD3b9/f8OGDTt37hRvi0KBdGHZsmWkC2PGjKEFSasBADIgDZ/G6dOnnZycXF1dL126JK0D2gvlqu7du/fu3fvx48csEhYWJs1poKiYO3fu+9vns/j999+XLl1KXjhu3Dja0NJqAIAISENBoIGOubm5l5eXSp5cC1TC27dv165dS6klJiaGPv7rX/+SpjJQVPz73/+Wbp4C8eLFi8WLF9M2HT9+/IMHD6TVAAA5IA0F5PXr1+zevMmTJ2vrNfZAHkotbm5uvXr1CggIkKYyUFR8vjT89ttv4eHh9P93woQJUH8A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" /></p>

このリファクタリングには、

* FileEntityのインターフェースを小さくできる
* FileEntityVisitorから派生できるアルゴリズムについては、
  FileEntityのインターフェースに影響を与えずに追加できる
  (「[オープン・クローズドの原則(OCP)](solid.md#SS_8_2)」参照)

という利点がある。
一方で、この程度の複雑さの(単純な)例では、Visitorの適用によって以前よりも構造が複雑になり、
改悪してしまった可能性があるため、デザインパターンを使用する場合には注意が必要である。

なお、上記の抜粋である下記コード

```cpp
    //  example/design_pattern/visitor.h 39

    virtual void Accept(FileEntityVisitor& visitor) const override { visitor.Visit(*this); }
```

はコードクローンだが、thisの型が違うため、
各Acceptが呼び出すFileEntityVisitor::Visit()も異り、単純に統一することはできない。
これを改めるためには、「[CRTP(curiously recurring template pattern)](design_pattern.md#SS_9_22)」が必要になる。

次に示すソースコードはVisitorとは関係がないが、
FileEntityVisitorから派生するクラスを下記クラス図が示すように改善することで、
単体テストが容易になる例である(「[DI(dependency injection)](design_pattern.md#SS_9_12)」参照)。

<!-- pu:essential/plant_uml/visitor_ut.pu--><p><img src="data:image/png;base64,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" /></p>

```cpp
    //  example/design_pattern/visitor.h 72

    class TestablePrinter : public FileEntityVisitor {
    public:
        explicit TestablePrinter(std::ostream& os) : ostream_{os} {}

    protected:
        std::ostream& ostream_;
    };

    class TestablePathnamePrinter1 final : public TestablePrinter {
    public:
        explicit TestablePathnamePrinter1(std::ostream& os) : TestablePrinter{os} {}
        virtual void Visit(File const& file) override;
        virtual void Visit(Dir const& dir) override;
        virtual void Visit(OtherEntity const& other) override;
    };

    class TestablePathnamePrinter2 final : public TestablePrinter {
    public:
        explicit TestablePathnamePrinter2(std::ostream& os) : TestablePrinter{os} {}
        virtual void Visit(File const& file) override;
        virtual void Visit(Dir const& dir) override;
        virtual void Visit(OtherEntity const& other) override;
    };
```

```cpp
    //  example/design_pattern/visitor.cpp 245

    void TestablePathnamePrinter1::Visit(File const& file) { ostream_ << file.Pathname(); }
    void TestablePathnamePrinter1::Visit(Dir const& dir) { ostream_ << dir.Pathname() + "/"; }
    void TestablePathnamePrinter1::Visit(OtherEntity const& other) { ostream_ << other.Pathname() + "(o1)"; }

    void TestablePathnamePrinter2::Visit(File const& file) { ostream_ << file.Pathname(); }

    void TestablePathnamePrinter2::Visit(Dir const& dir) { ostream_ << find_files(dir.Pathname()); }

    void TestablePathnamePrinter2::Visit(OtherEntity const& other) { ostream_ << other.Pathname() + "(o2)"; }
```

```cpp
    //  example/design_pattern/visitor_ut.cpp 28

    TEST(Visitor, testable_visitor)
    {
        auto oss = std::ostringstream{};

        // 出力をキャプチャするため、std::coutに代えてossを使う
        auto visitor1 = TestablePathnamePrinter1{oss};
        auto visitor2 = TestablePathnamePrinter2{oss};

        auto file = File{"visitor.cpp"};
        {
            file.Accept(visitor1);
            ASSERT_EQ("visitor.cpp", oss.str());
            oss = {};
        }
        {
            file.Accept(visitor2);
            ASSERT_EQ("visitor.cpp", oss.str());
            oss = {};
        }

        auto dir = Dir{"find_files_ut_dir/dir0"};
        {
            dir.Accept(visitor1);
            ASSERT_EQ("find_files_ut_dir/dir0/", oss.str());
            oss = {};
        }
        {
            dir.Accept(visitor2);
            ASSERT_EQ("find_files_ut_dir/dir0/file2,find_files_ut_dir/dir0/gile3", oss.str());
            oss = {};
        }
    }
```

[演習-Visitor](exercise_q.md#SS_22_9_22)  

## CRTP(curiously recurring template pattern) <a id="SS_9_22"></a>
CRTPとは、

```cpp
    //  example/design_pattern/crtp_ut.cpp 8

    template <typename T>
    class Base {
        // ...
    };

    class Derived : public Base<Derived> {
        // ...
    };
```

のようなテンプレートによる再帰構造を用いて、静的ポリモーフィズムを実現するためのパターンである。

このパターンを用いて、「[Visitor](design_pattern.md#SS_9_21)」のFileEntityの3つの派生クラスが持つコードクローン

```cpp
    //  example/design_pattern/visitor.h 39

    virtual void Accept(FileEntityVisitor& visitor) const override { visitor.Visit(*this); }
```

を解消した例を以下に示す。

```cpp
    //  example/design_pattern/crtp.h 31

    class FileEntity {  // VisitorのFileEntityと同じ
    public:
        explicit FileEntity(std::string&& pathname) : pathname_{std::move(pathname)} {}
        virtual ~FileEntity() {}
        std::string const& Pathname() const { return pathname_; }

        virtual void Accept(FileEntityVisitor&) const = 0;  // Acceptの仕様は安定しているので
                                                            // NVIは使わない。
    private:
        std::string const pathname_;
    };

    template <typename T>
    class AcceptableFileEntity : public FileEntity {  // CRTP
    public:
        virtual void Accept(FileEntityVisitor& visitor) const override { visitor.Visit(*static_cast<T const*>(this)); }

    private:
        // T : public AcceptableFileEntity<T> { ... };
        // 以外の使い方をコンパイルエラーにする
        AcceptableFileEntity(std::string&& pathname) : FileEntity{std::move(pathname)} {}
        friend T;
    };

    class File final : public AcceptableFileEntity<File> {  // CRTPでクローンを解消
    public:
        explicit File(std::string pathname) : AcceptableFileEntity{std::move(pathname)} {}
    };

    class Dir final : public AcceptableFileEntity<Dir> {  // CRTPでクローンを解消
    public:
        explicit Dir(std::string pathname) : AcceptableFileEntity{std::move(pathname)} {}
    };

    class OtherEntity final : public AcceptableFileEntity<OtherEntity> {  // CRTPでクローンを解消
    public:
        explicit OtherEntity(std::string pathname) : AcceptableFileEntity{std::move(pathname)} {}
    };
```

## Observer <a id="SS_9_23"></a>
Observerは、クラスSubjectと複数のクラスObserverN(N = 0, 1, 2 ...)があり、
この関係が下記の条件を満たさなければならない場合に使用されるパターンである。

* ObserverNオブジェクトはSubjectオブジェクトが変更された際、その変更通知を受け取る。
* SubjectはObserverNへ依存してはならない。

GUIアプリケーションを[MVC](design_pattern.md#SS_9_24)で実装する場合のModelがSubjectであり、
ViewがObserverNである。

まずは、このパターンを使用しない実装例を示す。

```cpp
    //  example/design_pattern/observer_ng.h 6

    /// @brief SubjectNGからの変更通知をUpdate()で受け取る。
    ///        Observerパターンを使用しない例。
    class ObserverNG_0 {
    public:
        ObserverNG_0() = default;

        virtual void Update(SubjectNG const& subject)  // テストのためにvirtual
        {
            // 何らかの処理
        }

        virtual ~ObserverNG_0() = default;
        // 何らかの定義、宣言
    };

    class ObserverNG_1 {
    public:
        // ...
    };

    class ObserverNG_2 {
    public:
        // ...
    };
```

```cpp
    //  example/design_pattern/observer_ng.cpp 6

    void ObserverNG_1::Update(SubjectNG const& subject)
    {
        // ...
    }

    void ObserverNG_2::Update(SubjectNG const& subject)
    {
        // ...
    }
```

```cpp
    //  example/design_pattern/subject_ng.h 9

    /// @class SubjectNG
    /// @brief 監視されるクラス。SetNumでの状態変更をObserverNG_Nに通知する。
    ///        Observerパターンを使用しない例。
    class SubjectNG final {
    public:
        explicit SubjectNG(ObserverNG_0& ng_0, ObserverNG_1& ng_1, ObserverNG_2& ng_2) noexcept
            : num_{0}, ng_0_{ng_0}, ng_1_{ng_1}, ng_2_{ng_2}
        {
        }

        void SetNum(uint32_t num);
        // ...
    };
```

```cpp
    //  example/design_pattern/subject_ng.cpp 4

    void SubjectNG::SetNum(uint32_t num)
    {
        if (num_ == num) {
            return;
        }

        num_ = num;

        notify();  // subjectが変更されたことをobserverへ通知
    }

    void SubjectNG::notify()
    {
        ng_0_.Update(*this);
        ng_1_.Update(*this);
        ng_2_.Update(*this);
    }
```

```cpp
    //  example/design_pattern/observer_ut.cpp 15

    struct ObserverNG_0_Test : ObserverNG_0 {  // テスト用クラス
        virtual void Update(SubjectNG const& subject) final
        {
            ++call_count;
            num = subject.GetNum();
        }

        uint32_t                call_count{0};
        std::optional<uint32_t> num{};
    };

    auto ng0 = ObserverNG_0_Test{};
    auto ng1 = ObserverNG_1{};
    auto ng2 = ObserverNG_2{};

    auto subject = SubjectNG{ng0, ng1, ng2};

    ASSERT_EQ(0, ng0.call_count);  // まだ何もしていない
    ASSERT_FALSE(ng0.num);

    subject.SetNum(1);
    subject.SetNum(2);

    ASSERT_EQ(2, ng0.call_count);
    ASSERT_EQ(2, *ng0.num);

    subject.SetNum(2);  // 同じ値をセットしたため、Updateは呼ばれないはず
    ASSERT_EQ(2, ng0.call_count);
    ASSERT_EQ(2, *ng0.num);
```

上記実装例のクラス図を下記する。
これを見ればわかるように、クラスSubjectNGとクラスObserverNG_Nは相互依存しており、機能追加、
修正が難しいだけではなく、この図の通りにパッケージを分割した場合
(パッケージがライブラリとなると前提）、リンクすら難しくなる。

<!-- pu:essential/plant_uml/observer_class_ng.pu--><p><img src="data:image/png;base64,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adMmLi4uICBg4sSJao376dq168yZM9VSk1atWo0dO1YtLR7W7j3zzDM44x9++KFlvfHII4988skn8uWhQ4datGhRt27dJ598Mszk008/lWvnzp376KOPDho0CBU2b94sy69cuRIVFXX16lVZYkVXXydQUVfc9YeKSqioK1RUUhoVtZ3fy0IIwAlOTU1VS+/n5s2bDRo0+O6779QVXqCI/uB0vvbaa2L5xIkTOEoI+/fVuJ8i9F23bp1n8VbpHvTt3bt3zZo1v//+e1lo1ff48eOBgYETJky4deuWYYbZGTNm4NpD8hUvq1evjlSO5Y8++gjnS24EvPXWW+PGjbOWSHT1dQIVVSiiP1RUQkUVqKiklCpqO7/7JgRcvnz5hsnu3buPHTumVLt+/fq+ffvQh3v37in6oslnn3129OjRO3fuiJKff/75BRN4gGWUFBYW4rzigP7666+y4fLly7t16yZfGqbQBw8e3L59+48//mgtx5bRJTS3Bj3RYaz6/PPPT506Zan+F4h4mZmZly5dMuz6Y6VatWobNmxQCg3zbpL1xhHaCleEvhgRDhRGbb3dhIT4yy+/yJe2ozZchunaPeg7bdq0gQMHPv3007KVVd+kpKSYmBjlTteSJUvQASygHOqL0zp//nzlIGNcNWrUsL17qauvE6goFaWichUVlXXKm6K287tvQgCkRJSLjIzEIQsNDcX/8kOmnJwclKBCYmJifHz8448/LvXds2dPvXr1EhISkATbt28vztPixYsfNYmLi8Py4cOHGzVq1KNHj379+oWFheHMibbPPffc9OnTxTKACs2aNWvVqlX37t1r1aollUJeQyHOVv/+/YODgxcuXCjK0Z/Jkyejw9HR0YhsOP1yU9hRx44dcfrr1q27YsUKpT+ymiA5OblJkyZwUSlH4apVq8Ty7du3cQrQQ8PUd8SIES1btsQhwnBwQORFZY237kbtOkzX7kFfDA2e1a5dOz09XTSU+sK8KlWqLF26VJTbglMJa3fs2IFdizBrBQcNq5RCQ19fJ1BRKkpFxSoqWp4VtZ3ffRYC6tevL+6EIFvhEL/yyitYRnDD8uuvvy7q41hUqlRJ6osdrV+/3jBzU2xsrPwA5iUT0Tw8PHzOnDmiHPI1b9787t27WMZlID9oQRSFLqIJ2Llz57PPPivKIyIiZDniKs6c+NgGHYbNX331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" /></p>

このようなクラス間の依存関係は下記のようにファイル間の依存関係に反映される。
このような相互依存は、差分ビルドの長時間化等の問題も引き起こす。

<!-- pu:essential/plant_uml/observer_file_ng.pu--><p><img src="data:image/png;base64,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" /></p>

次に、上記にObserverパターンを適用した実装例
(Subjectを抽象クラスにすることもあるが、下記例ではSubjectを具象クラスにしている)を示す。

```cpp
    //  example/design_pattern/observer_ok.h 3

    /// @brief SubjectOKからの変更通知をUpdate()で受け取る。
    ///        Observerパターンの使用例。
    class ObserverOK_0 : public Observer {
        // ...
    private:
        virtual void update(SubjectOK const& subject) override;
    };

    class ObserverOK_1 : public Observer {
        // ...
    private:
        virtual void update(SubjectOK const& subject) override;
    };

    class ObserverOK_2 : public Observer {
        // ...
    private:
        virtual void update(SubjectOK const& subject) override;
    };
```

```cpp
    //  example/design_pattern/observer_ok.cpp 5

    void ObserverOK_0::update(SubjectOK const& subject)
    {
        // ...
    }

    void ObserverOK_1::update(SubjectOK const& subject)
    {
        // ...
    }

    void ObserverOK_2::update(SubjectOK const& subject)
    {
        // ...
    }
```

```cpp
    //  example/design_pattern/subject_ok.h 8

    /// @brief 監視されるクラス。SetNumでの状態変更をObserverOK_Nに通知する。
    ///        Observerパターンの使用例。
    class SubjectOK final {
    public:
        SubjectOK() : observers_{}, num_{0} {}

        void SetNum(uint32_t num)
        {
            if (num_ == num) {
                return;
            }

            num_ = num;

            notify();  // subjectが変更されたことをobserverへ通知
        }

        void     Attach(Observer& observer);           // Observerの登録
        void     Detach(Observer& observer) noexcept;  // Observerの登録解除
        uint32_t GetNum() const noexcept { return num_; }

    private:
        void notify() const;

        std::list<Observer*> observers_;
        // ...
    };

    /// @brief SubjectOKを監視するクラスの基底クラス
    class Observer {
    public:
        Observer() = default;
        void Update(SubjectOK const& subject) { update(subject); }

        // ...
    private:
        virtual void update(SubjectOK const& subject) = 0;
        // ...
    };
```

```cpp
    //  example/design_pattern/subject_ok.cpp 3

    void SubjectOK::Attach(Observer& observer_to_attach) { observers_.push_back(&observer_to_attach); }

    void SubjectOK::Detach(Observer& observer_to_detach) noexcept
    {
        observers_.remove_if([&observer_to_detach](Observer* observer) { return &observer_to_detach == observer; });
    }

    void SubjectOK::notify() const
    {
        for (auto observer : observers_) {
            observer->Update(*this);
        }
    }
```

```cpp
    //  example/design_pattern/observer_ut.cpp 51

    struct ObserverOK_Test : Observer {  // テスト用クラス
        virtual void update(SubjectOK const& subject) final
        {
            ++call_count;
            num = subject.GetNum();
        }

        uint32_t                call_count{0};
        std::optional<uint32_t> num{};
    };

    auto ok0 = ObserverOK_Test{};
    auto ok1 = ObserverOK_1{};
    auto ok2 = ObserverOK_2{};

    auto subject = SubjectOK{};

    subject.Attach(ok0);
    subject.Attach(ok1);
    subject.Attach(ok2);

    ASSERT_EQ(0, ok0.call_count);  // まだ何もしていない
    ASSERT_FALSE(ok0.num);

    subject.SetNum(1);
    subject.SetNum(2);

    ASSERT_EQ(2, ok0.call_count);
    ASSERT_EQ(2, *ok0.num);

    subject.SetNum(2);  // 同じ値をセットしたため、Updateは呼ばれないはず
    ASSERT_EQ(2, ok0.call_count);
    ASSERT_EQ(2, *ok0.num);
```

上記実装例のクラス図を下記する。
Observerパターンを使用しない例と比べると、
クラスSubjectOKとクラスObserverOK_Nとの相互依存が消えたことがわかる。

<!-- pu:essential/plant_uml/observer_class_ok.pu--><p><img src="data:image/png;base64,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grTuiRTpiygwDSJ9fccNCKRZ0D9YGlddpS9DQE1DCKSpaViyZEmjZo998NVaJ0I++HLtsGkjnxvYcczc8c4uTPcjMY/oQ76wI9JNAxQqG1M26BxDcvSDqA0SGi5astg9lyJ9EQWmYfGSxQ2bNbpR6YOxKn1hh5qGEEg70/D777/HVY2b/tEsJzb4q9agxv9cRf2WDZ29/ScM7Nyls3u6YPjll182b968fv16ZxFyUlLS1KlT7ZKwY9++fVznjh07fvvtN7scjeAuzMcff/zxyJEjNJ1VxcXevXs51YEDB9wdqYpINw1dXugyMHFIIPdSph90rVylcsrtb3Do0CE6Ytu2bZcvX7bLp02blta9c0M4d+7ceh+nTp2yy3/++efjx4+bjwyO4R4MtKoEAbEGmd3SVEWkm4ablr4BiYPhrXu6YKDvNm7cSJ86JgNxmDFjhl0SduzZs4fr3LVrlzOHd+zYMXv18Q8//BDyXZLdu3dzqrT+SS41DSGQdqZhw4YNjNsCw2bo6yO4yIGThyzbvbJsXAzbiYtfsSu898Xq8pUqoF/uGa8FKSdHjhw1atRo1qxZrly5EhISzp49K7s++OCDEiVKXFs9bCC1lC9fvkiRIq1atSpTpkyhQoXWrl1r9j700ENvvfWWbH/99df58+cfPny42esApahduzanql+/fp48eVq2bOlYkFRERJsGyFOxcsWgKx9D0i++af1P1n/invFaoHcQr0CBAnQBnZs3b96VK1eavY888siKFSus6mED2WvYsGHZsmWLj49v0qQJG506dbp06ZLsnTt3boUKFUzlnj17Fi1aNIWRLv1Vr16922+//fHHH3f3pSoi3TQgffWbNrgJ7sHYCtchfYmJidmzZ69Vqxaid++997Zt2xZlkF0LFy6sXLnytdXDBuzCww8/XLx4caSvVKlSbHz66adm7/33379u3TrZ3r9/f86cOSdPnmz2Orhw4ULNmjVLliwJ97hlO9xSHWoaQiDtTMOQYUP6TQiymgGvXfThYrI9bsFELrjZsy2cOt2GdE95qmDBggVZs2bdvHmzfDx//nzdunXRcTGzGcc0YIpJLcixye6MA+6++27CST4a03DixAkke8iQIebYQPTt2xfVll+c/f7778lV6L5bKZUQ0aYB8vR6sU8g966HfpB2wJAB7hktoF+IV7t27cxP/9KDmTNn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" /></p>

最後に、上記のファイルの依存関係を示す。
ファイル(パッケージ)の依存関係においてもSubjectOKはObserverOKに依存していないことがわかる
(MVCに置き換えると、ModelはViewに依存していない状態であるといえる)。

<!-- pu:essential/plant_uml/observer_file_ok.pu--><p><img src="data:image/png;base64,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" /></p>

[演習-Observer](exercise_q.md#SS_22_9_24)  

## MVC <a id="SS_9_24"></a>

MVCはデザインパターンと言うよりもアーキテクチャパターンである。
一般にGUIアプリケーションのアーキテクチャに使用されるが、
外部からの非同期要求を処理するアプリケーションのアーキテクチャにも相性が良い。

MVCのそれぞれのアルファベットの意味は、下記テーブルの通りである。

|   | MVC            | 主な役割                        |
|:-:|:---------------|:--------------------------------|
| M | Model          | ビジネスロジックの処理          |
| V | View           | UIへの出力                      |
| C | Controller     | 入力をModelへ送信               |

下記はMVCの概念モデルである(矢印は制御の流れであって、依存関係ではない)。

<!-- pu:essential/plant_uml/mvc.pu--><p><img src="data:image/png;base64,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" /></p>

制御の流れは、

1. ユーザの入力に応じてControllerのメソッドが呼び出される。
2. Controllerのメソッドは、ユーザの入力に応じた引数とともにModelのメソッドを呼び出す。
3. Modelは、それに対応するビジネスロジック等の処理を(通常、非同期に)行い、
自分自身の状態を変える(変わらないこともある)。
4. Modelの状態変化は、そのModelのオブザーバーとして登録されているViewに通知される。
5. Viewは関連するデータをModelから取得し、それを出力(UIに表示)する。

ViewはModelの[Observer](design_pattern.md#SS_9_23)であるため、ModelはViewへ依存しない。
多々あるMVC派生パターンすべてで、そのような依存関係は存在しない
(具体的なパターンの選択はプロジェクトで使用するGUIフレームワークに強く依存する)。

そのようにする理由は下記の通りで、極めて重要な規則である。

* GUIのテストは目で見る必要がある(ことが多い)ため、Viewに自動単体テストを実施することは困難である。
  一方、ViewがModelに依存しないのであれば、Modelは自動単体テストをすることが可能である。
* 通常、Viewの仕様は不安定で、Modelの仕様は安定しているため、Modelのソースコード変更は
  Viewのそれよりもかなり少ない。
  しかし、ModelがViewに依存してしまうと、Viewに影響されModelのソースコード変更も多くなる。

[演習-デザインパターン選択1](exercise_q.md#SS_22_9_25)  
[演習-デザインパターン選択2](exercise_q.md#SS_22_9_26)  
[演習-デザインパターン選択3](exercise_q.md#SS_22_9_27)  

## Cでのクラス表現 <a id="SS_9_25"></a>
このドキュメントは、C++でのソフトウェア開発を前提としているため、
ここで示したコードもC++で書いているが、

* 何らかの事情でCを使わざるを得ないプログラマがデザインパターンを使用できるようにする
* クラスの理解が曖昧なC++プログラマの理解を助ける(「[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)」参照)

ような目的のためにCでのクラスの実現方法を例示する。

下記のような基底クラスPointとその派生クラスPoint3Dがあった場合、

<!-- pu:essential/plant_uml/class_c.pu--><p><img src="data:image/png;base64,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" /></p>

C++では、Pointのコードは下記のように表すことが一般的である。

```cpp
    //  example/design_pattern/class_ut.cpp 7

    class Point {
    public:
        explicit Point(int x, int y) noexcept : x_{x}, y_{y} {}
        virtual ~Point() = default;

        void SetXY(int x, int y) noexcept
        {
            x_ = x;
            y_ = y;
        }

        void GetXY(int& x, int& y) const noexcept
        {
            x = x_;
            y = y_;
        }

        virtual int Quantity() const noexcept { return x_ * y_; }

        virtual void Multipy(int m) noexcept
        {
            x_ *= m;
            y_ *= m;
        }

    private:
        int x_;
        int y_;
    };
```

この単体テストは、下記のようになる。

```cpp
    //  example/design_pattern/class_ut.cpp 42

    Point a{1, 2};

    int x;
    int y;
    a.GetXY(x, y);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    a.SetXY(3, 4);

    a.GetXY(x, y);
    ASSERT_EQ(x, 3);
    ASSERT_EQ(y, 4);

    ASSERT_EQ(a.Quantity(), 12);

    a.Multipy(2);
    ASSERT_EQ(a.Quantity(), 48);
```

これをCで表した場合、下記のようになる。

```cpp
    //  example/design_pattern/class_ut.cpp 124

    struct Point {
        int x;
        int y;

        int (*const Quantity)(Point const* self);
        void (*const Multipy)(Point* self, int m);
    };

    static int point_quantity(Point const* self) { return self->x * self->y; }

    static void point_multipy(Point* self, int m)
    {
        self->x *= m;
        self->y *= m;
    }

    Point Point_Construct(int x, int y)
    {
        Point ret = {x, y, point_quantity, point_multipy};  // C言語のつもり

        return ret;
    }

    void Point_SetXY(Point* self, int x, int y)
    {
        self->x = x;
        self->y = y;
    }

    void Point_GetXY(Point* self, int* x, int* y)
    {
        *x = self->x;
        *y = self->y;
    }
```

C++のメンバ関数はプログラマから見えない引数thisを持つ。
これを表したものが各関数の第1引数selfである。
また、ポリモーフィックな関数は関数ポインタで、
非ポリモーフィックな関数は通常の関数で表される。

この単体テストは、下記のようになる。

```cpp
    //  example/design_pattern/class_ut.cpp 164

    Point a = Point_Construct(1, 2);

    int x;
    int y;

    Point_GetXY(&a, &x, &y);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    Point_SetXY(&a, 3, 4);

    Point_GetXY(&a, &x, &y);
    ASSERT_EQ(x, 3);
    ASSERT_EQ(y, 4);

    ASSERT_EQ(a.Quantity(&a), 12);

    a.Multipy(&a, 2);
    ASSERT_EQ(a.Quantity(&a), 48);
```

Pointから派生したクラスPoint3DのC++での実装を以下に示す。

```cpp
    //  example/design_pattern/class_ut.cpp 65

    class Point3D : public Point {
    public:
        explicit Point3D(int x, int y, int z) noexcept : Point{x, y}, z_{z} {}

        void SetXYZ(int x, int y, int z) noexcept
        {
            SetXY(x, y);
            z_ = z;
        }

        void GetXYZ(int& x, int& y, int& z) const noexcept
        {
            GetXY(x, y);
            z = z_;
        }

        virtual int Quantity() const noexcept override { return Point::Quantity() * z_; }

        virtual void Multipy(int m) noexcept override
        {
            Point::Multipy(m);
            z_ *= m;
        }

    private:
        int z_;
    };
```

この単体テストは、下記のようになる。

```cpp
    //  example/design_pattern/class_ut.cpp 98

    auto  a = Point3D{1, 2, 3};
    auto& b = a;

    auto x = int{};
    auto y = int{};
    b.GetXY(x, y);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    b.SetXY(3, 4);

    b.GetXY(x, y);
    ASSERT_EQ(x, 3);
    ASSERT_EQ(y, 4);

    ASSERT_EQ(b.Quantity(), 36);

    b.Multipy(2);
    ASSERT_EQ(b.Quantity(), 288);
```

これをCで実装したものが下記である。

```cpp
    //  example/design_pattern/class_ut.cpp 188

    struct Point3D {
        Point point;
        int   z;
    };

    static int point3d_quantity(Point const* self)
    {
        Point3D const* self_derived = (Point3D const*)self;

        return point_quantity(self) * self_derived->z;
    }

    static void point3d_multipy(Point* self, int m)
    {
        point_multipy(self, m);

        Point3D* self_derived = (Point3D*)self;

        self_derived->z *= m;
    }

    Point3D Point3D_Construct(int x, int y, int z)
    {
        Point3D ret{{x, y, point3d_quantity, point3d_multipy}, z};

        return ret;
    }
```

この単体テストは、下記のようになる。

```cpp
    //  example/design_pattern/class_ut.cpp 221

    Point3D a = Point3D_Construct(1, 2, 3);
    Point*  b = &a.point;

    int x;
    int y;

    Point_GetXY(b, &x, &y);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    Point_SetXY(b, 3, 4);

    Point_GetXY(b, &x, &y);
    ASSERT_EQ(x, 3);
    ASSERT_EQ(y, 4);

    ASSERT_EQ(b->Quantity(b), 36);

    b->Multipy(b, 2);
    ASSERT_EQ(b->Quantity(b), 288);
```

以上からわかる通り、Cでのクラス実装はC++のものに比べ、

* 記述が多い
* キャストを使わざるを得ない
* リファレンスが使えないため、NULLにならないハンドル変数をポインタにせざるを得ない

等といった問題があるため、「何らかの事情でC++が使えない」チームは、
なるべく早い時期にその障害を乗り越えることをお勧めする。

どうしてもその障害を超えられない場合は、
[モダンC言語プログラミング](https://www.amazon.co.jp/%E3%83%A2%E3%83%80%E3%83%B3C%E8%A8%80%E8%AA%9E%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0-%E3%82%A2%E3%82%B9%E3%82%AD%E3%83%BC%E6%9B%B8%E7%B1%8D-%E8%8A%B1%E4%BA%95-%E5%BF%97%E7%94%9F-ebook/dp/B00HWLJEKW)
が役に立つだろう。


