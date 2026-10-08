<!-- deep/md/design_pattern.md -->
# デザインパターン <a id="SS_9"></a>

ソースコードを劣化させるアンチパターンには、以下のようなものがある。

* 大きすぎる関数、クラス、ファイル等のソフトウェア構成物
* 複雑怪奇な依存関係
* コードクローン

こういった問題は、良質なコードを書くという意識を持ったプログラマの継続的な努力と、
ソフトウェア工学の知識によって回避可能である。
本章ではその知識の一翼を担うイディオム、デザインパターンを解説、例示する。

なお、ここに挙げるイディオム、デザインパターンは「適切な場所に適用される場合、
ソースコードをよりシンプルに記述できる」というメリットがある一方で、
「不適切な場所に適用される場合、ソースコードの複雑度を不要に上げてしまう」という負の一面を持つ。
また、この章で取り扱うパターンを覚えたてのプログラマは、自分のスキルが向上したという一種の高揚感や顕示欲から、
それらをむやみに多用してしまう状態に陥ることがある。

___

__この章の構成__

[イディオム](design_pattern.md#SS_9_1)  
&emsp;[ガード節(Early Return)](design_pattern.md#SS_9_1_1)  
&emsp;[前方宣言ヘッダ(`_fwd.h`)](design_pattern.md#SS_9_1_2)  
&emsp;[RAII(scoped guard)](design_pattern.md#SS_9_1_3)  
&emsp;[Copy-And-Swap](design_pattern.md#SS_9_1_4)  
&emsp;[CRTP(curiously recurring template pattern)](design_pattern.md#SS_9_1_5)  
&emsp;[Accessor](design_pattern.md#SS_9_1_6)  
&emsp;[Immutable](design_pattern.md#SS_9_1_7)  
&emsp;[NVI(non virtual interface)](design_pattern.md#SS_9_1_8)  
&emsp;[二段階文字列化(STRINGIZE) ](design_pattern.md#SS_9_1_9)  

[実装パターン](design_pattern.md#SS_9_2)  
&emsp;[Pimpl](design_pattern.md#SS_9_2_1)  
&emsp;[lightweight Pimpl](design_pattern.md#SS_9_2_2)  
&emsp;[BitmaskType](design_pattern.md#SS_9_2_3)  
&emsp;[Future](design_pattern.md#SS_9_2_4)  
&emsp;[Null Object](design_pattern.md#SS_9_2_5)  
&emsp;[Cでのクラス表現](design_pattern.md#SS_9_2_6)  

[オブジェクト生成系デザインパターン](design_pattern.md#SS_9_3)  
&emsp;[Singleton](design_pattern.md#SS_9_3_1)  
&emsp;[Named Constructor](design_pattern.md#SS_9_3_2)  
&emsp;[Clone(仮想コンストラクタ)](design_pattern.md#SS_9_3_3)  
&emsp;[Factory](design_pattern.md#SS_9_3_4)  

[オブジェクトの動作/協調に関するデザインパターン](design_pattern.md#SS_9_4)  
&emsp;[Templateメソッド](design_pattern.md#SS_9_4_1)  
&emsp;[Strategy](design_pattern.md#SS_9_4_2)  
&emsp;[State](design_pattern.md#SS_9_4_3)  
&emsp;[Observer](design_pattern.md#SS_9_4_4)  
&emsp;[Visitor](design_pattern.md#SS_9_4_5)  
&emsp;[Proxy](design_pattern.md#SS_9_4_6)  
&emsp;[Active Object](design_pattern.md#SS_9_4_7)  

[アーキテクチャパターン(システムレベルの構造)](design_pattern.md#SS_9_5)  
&emsp;[DI(dependency injection)](design_pattern.md#SS_9_5_1)  
&emsp;[MVC](design_pattern.md#SS_9_5_2)  
  
  


[インデックス](comprehensive_intro.md#SS_1_3)に戻る。  

___

## イディオム <a id="SS_9_1"></a>

### ガード節(Early Return) <a id="SS_9_1_1"></a>
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

---

### 前方宣言ヘッダ(`_fwd.h`) <a id="SS_9_1_2"></a>
class, struct, enum, enum class等の前方宣言により、特定ヘッダの依存関係を解消することは、
ビルド時間の短縮やリファクタリングを容易にするなど、多くの利点をもたらす。
しかし、前方宣言を必要とする各ヘッダファイルに個別にそれを記述する方式には、看過できない問題が存在する。
実体（クラスや列挙型の定義）側の名前空間、クラス名、あるいはテンプレート引数などが変更された場合、
これを利用する側に散在する前方宣言がその変更に追随せず、両者の間に不整合が生じ得るという点である。
この種の不整合(例えば[ODR](core_lang_spec.md#SS_19_14_10)違反)は、たとえ発生してもコンパイラが直ちに検出できるとは限らず、
実行時の[未定義動作](core_lang_spec.md#SS_19_14_3)や、原因の特定に長時間を要する難解なコンパイルエラーという形で顕在化することも少なくない。

本節で述べる手法は、この問題に対し、前方宣言を単一のヘッダファイル（以下 `*_fwd.h`）
に集約するとともに、実体を定義するヘッダファイル自身にも同じファイルをincludeさせるという構成を取る。
これにより、前方宣言と実体定義との整合性はコンパイラによって機械的に保証されることとなり、
前方宣言の記述を利用側の各ヘッダに分散させる従来の方式が内包していた保守上のリスクを、
設計レベルで排除することが可能となる。

以下に、`a.h`、`a_fwd.h`、`b.h`の3ファイルによる具体的な実装例を示す。

```cpp
// in a.h     class Aの宣言

#include "a_fwd.h"  // NS1::Aの前方宣言のためのヘッダファイル
                    // このincludeによりコンパイル時にa.hとa_fwd.hに矛盾がないことが保証される

namespace NS1 {
class A {
public:
    // 何らかの宣言、定義
    //  ...
};
}
```
```cpp
// in a_fwd.h     class Aの前方宣言

namespace NS1 {
class A;
}
```
```cpp
// in b.h     class Bの宣言

#include "a_fwd.h"  // NS1::Aの前方宣言のためのヘッダファイル

namespace NS2 {
class B {
public:
    // 何らかの宣言、定義
    //  ...

    // ※ ~B()はb.cppで定義する(NS1::Aが不完全型のため、unique_ptrのデフォルトデリータをここで実体化できない)

private:
    std::unique_ptr<NS1::A> a_;
};
}
```
---

### RAII(scoped guard) <a id="SS_9_1_3"></a>
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
    //  essential/h/scoped_guard.h 7

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

---

### Copy-And-Swap <a id="SS_9_1_4"></a>
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

* copy代入演算子には、[エクセプション安全性の保証](core_lang_spec.md#SS_19_13_7)がない。
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
これにより[エクセプション安全性の保証](core_lang_spec.md#SS_19_13_7)を持つ4関数をコードクローンすることなく実装できる。

[演習-Copy-And-Swap](exercise_q.md#SS_22_9_6)  

---

### CRTP(curiously recurring template pattern) <a id="SS_9_1_5"></a>
CRTPとは、

```cpp
    //  example/design_pattern/crtp_ut.cpp 12

    template <typename T>
    class Base {
        // ...
    };

    class Derived : public Base<Derived> {
        // ...
    };
```

のようなテンプレートによる再帰構造を用いて、静的ポリモーフィズムを実現するためのパターンである。
以下にこのパターンを使用した[ミックスイン](glossary.md#SS_21_5_7)の例を示す。

```cpp
    //  example/design_pattern/crtp_ut.cpp 25

    std::atomic<uint32_t> DerivedClass_Count = 0;  // Counterの派生クラスのインスタンス数

    template <typename T>
    class Counter {  // 派生クラスのインスタンスを計測するミックスイン
    public:
        Counter() { ++DerivedClass_Count; }
        Counter(Counter const&) { ++DerivedClass_Count; }
        ~Counter() { --DerivedClass_Count; }
    };

    class A : public Counter<A> {
        // クラスAの実装
        // ...
    };

    class B : public Counter<B> {
        // クラスBの実装
        // ...
    };
```
```cpp
    //  example/design_pattern/crtp_ut.cpp 50

    A a0;
    B b0;

    ASSERT_EQ(2, DerivedClass_Count);  // インスタンスが２個のテスト

    {
        auto a1 = a0;
        ASSERT_EQ(3, DerivedClass_Count);  // コピーによりインスタンスの増加のテスト
    }
    ASSERT_EQ(2, DerivedClass_Count);  // a1のスコープアウトによりインスタンスが減少
```

なお、このパターンは、[std::enable_shared_from_this](stdlib_and_concepts.md#SS_20_6_1_3_2)の使用において前提知識となっている。

---

### Accessor <a id="SS_9_1_6"></a>
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

---

### Immutable <a id="SS_9_1_7"></a>
クラスに対するimmutable、immutabilityの定義を以下のように定める。

* immutable(不変な)なクラスとは、初期化後、状態の変更ができないクラスを指す。
* immutability(不変性)が高いクラスとは、
  状態を変更するメンバ関数(非constなメンバ関数)が少ないクラスを指す。

immutabilityが高いほど、そのクラスの使用方法は制限される。
これにより、そのクラスやそのクラスを使用しているソースコードの可読性やデバッグ容易性が向上する。
また、クラスがimmutableでなくても、そのクラスのオブジェクトをconstハンドル経由でアクセスすることで、
immutableとして扱うことができる。

一方で、「[Accessor](design_pattern.md#SS_9_1_6)」で紹介したsetterは、クラスのimmutabilityを下げる。
いつでも状態が変更できるため、ソースコードの可読性やデバッグ容易性が低下する。
また、マルチスレッド環境においてはこのことが競合問題や、
それを回避するためのロックがパフォーマンス問題やデッドロックを引き起こしてしまう。

従って、クラスを宣言、定義する場合、immutabilityを出来るだけ高くするべきであり、
そのクラスのオブジェクトを使う側は、
可能な限りimmutableオブジェクト(constオブジェクト)として扱うべきである。

[演習-Immutable](exercise_q.md#SS_22_9_7)  

---

### NVI(non virtual interface) <a id="SS_9_1_8"></a>
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

---

### 二段階文字列化(STRINGIZE)  <a id="SS_9_1_9"></a>
本節では、プリプロセッサの文字列化演算子 `#` を二段階のマクロで包むイディオムと、
その代表的な応用2つを解説する。

典型的な二段階文字列化(STRINGIZE)イデオムは以下のようなコードを指す。

```cpp
    //  example/design_pattern/stringize_ut.cpp 5

    // 二段階文字列化イデオムマクロ
    #define STRINGIZE_INTERNAL(x) #x
    #define STRINGIZE(x) STRINGIZE_INTERNAL(x)
```

通常、関数形式マクロの実引数は、置換リストに代入される前に完全にマクロ展開される。ただし、
その仮引数が `#` または `##` の被演算子である場合は例外であり、実引数は書かれたままの形で使われる。

```c
    #define LINE_A STRINGIZE_INTERNAL(__LINE__)   // -> "__LINE__"
    #define LINE_B STRINGIZE(__LINE__)            // -> "42" など
```

STRINGIZEを使ったコードの場所の文字列化('__LINE__'の文字列への取り込み)は以下のように実装できる。


```cpp
    //  example/design_pattern/stringize_ut.cpp 11

    #define WHERE __FILE__ ":" STRINGIZE(__LINE__)
```
```cpp
    //  example/design_pattern/stringize_ut.cpp 18

    std::stringstream oss;
    auto              line_no = __LINE__ + 2;  // テスト対象の行は2行下

    char const whare[]{WHERE};
    oss << __FILE__ ":" << line_no;

    ASSERT_EQ(oss.str(), whare);
```

gccの警告の抑止を行うための以下のようなマクロは、

```cpp
    #define SUPPRESS_WARN_GCC_ARRAY_BOUNDS _Pragma("GCC diagnostic ignored \"-Warray-bounds\"")
    #define SUPPRESS_WARN_GCC_BOOL_OP _Pragma("GCC diagnostic ignored \"-Wbool-operation\"")
    #define SUPPRESS_WARN_GCC_ADDRESS _Pragma("GCC diagnostic ignored \"-Waddress\"")
```

このSTRINGIZEを使って、以下のようにすっきりと実装できる。

```cpp
    #define IGNORE_GCC_DIAGNOSTIC(s) _Pragma(STRINGIZE(GCC diagnostic ignored s))

    #define SUPPRESS_WARN_GCC_ARRAY_BOUNDS IGNORE_GCC_DIAGNOSTIC("-Warray-bounds")
    #define SUPPRESS_WARN_GCC_BOOL_OP IGNORE_GCC_DIAGNOSTIC("-Wbool-operation\"")
```

---

## 実装パターン <a id="SS_9_2"></a>
### Pimpl <a id="SS_9_2_1"></a>
このパターンは、「クラスA(a.cpp、a.hで宣言、定義)を使用するクラスにAの実装の詳細を伝搬させたくない」
ような場合に使用する。
そのため[オープン・クローズドの原則(OCP)](class_design.md#SS_8_1_2)の実装方法としても有用である。

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

<!-- pu:deep/plant_uml/pimpl_pattern.pu--><p><img src="data:image/png;base64,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" /></p>

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

<!-- pu:deep/plant_uml/widget_ng.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAg4AAADJCAIAAADEqy1LAAAAKnRFWHRjb3B5bGVmdABHZW5lcmF0ZWQgYnkgaHR0cHM6Ly9wbGFudHVtbC5jb212zsofAAABTGlUWHRwbGFudHVtbAABAAAAeJxlkU1vwjAMhu/+FRYnOBQ6GAz1MKGNbVJXNDQ+dkShDSVTm1aJwzZN++8zHwXGckhi+3ltxxlYEoZcnoGNRSYxF5944/v4oRJaA4hUasJaStJSa7c31zUUFnf3BRNGxiR0ytJapJa7GJ/4DcjrIF+3OF0qK+3eYPEZYk1cQXFZnmNsnoOODtzC/UPdnv6p+o4zxQdAVRC9TK7Iuz12fyqBnis5cGztT8bL4D7vpRcGUifbScI4E5pmowg30lhVaLxqtv12t+nX32SCodDo99FvB51u0OlhOJniNtyA+tM4Qls4E0tMlCWjlo5Y34BQbAS+Ok0qlwG+lFKHw+fKgQ96o0yh8+1jw/noBPSuvTtFOJGGO8H5CIZyJVxGrIiLROk0wNn00etDxF/oeGgBvgu4Lziv+QowHMMvtGKyjUdjpWoAACcaSURBVHhe7Z17XFTVFse91bWs7Pawl6VoegPlIQKKkmKKr0QUH6BeK8gSDbTMV1GaLxIDTSvNSm734jUfPEozobymGGoqfLREsRDQNOQl6umhgoh3fdifzh32zJkZD3PYZ85a3z/4nNlrn8fs/Vv7t/fM4Uyz6wRBEARhlWZ8AUEQBEE0hKyCIAiCsAFZBUEQBGEDsgqCIAjCBmQVBEEQhA3IKgiCIAgbkFUI4/Lly4sWLQoICHiIIAjnoXXr1kFBQbm5uXxKGxqyCmFMmjQpOjr6xIkTfIAgCH2zZcsWcAu+1NCQVQijffv2ly5d4ksJgtA9tbW1bdq04UsNDVmFMGAlyxcRBOEkYMtfsgphYJMaQRgJbPlLViEMbFIjCCOBLX/JKoSBTWqGJCkpKSYm5tq1a1z5+vXrly9fXldXB9sjR47s3LkzV4FwdrDlL1mFMLBJzZCMGjWqWbNmV69e5cp9fX3l8qCgoAcffJCrQDg72PKXrEIY2KRmSJSsIj09ffXq1WxVQVZhSLDlL1mFMLBJzZAoWcWaNWvefPNNts2sIi0tbezYsWFhYevWrWtYl3BKsOUvWYUwsEnNkChZxaBBg+677z62DVbxl7/8Bar16dPHzc0NNqZOndqwOuF8YMtfsgphYJOaIbHTKqBOUlISbNfU1PTq1Quco6CgoMEOhLOBLX/JKoSBTWqGxE6ruPfee+XQunXrYJd//etfcgnhjGDLX7IKYWCTmiGx0ypMv9beunUr7LJ69Wq5hHBGsOUvWYUwsEnNkNhpFbfccktZWRl7OXPmTNhl586d/69NOCHY8pesQhjYpGZImFWMHDly1J/MmTPnuplVQJ1OnTr985//XLBgQfPmzbt27Wr+X3uEc4Etf8kqhIFNaoZkypQpHRoyZswYKH/uuee6devG6oSFhYWGho4ePbpFPeArpaWlDY5COCHY8pesQhjYpEbASqK2tpYvJZwTbPlLViEMbFIjCCOBLX/JKoSBTWoEYSSw5S9ZhTCwSY0gjAS2/CWrEAY2qRGEkcCWv2QVwsAmNYIwEtjyl6xCGNikRhBGAlv+klUIA5vUCMJIYMtfsgphYJMaQRgJbPlLViEMbFIjCCOBLX/JKoSBTWoEYSSw5S9ZhTCwSY0gjAS2/CWrEAY2qRGEkcCWv2QVwsAmNYIwEtjyl6xCGNikRhBGAlv+klUIA5vUCMJIYMtfsgphYJMaQRgJbPlLViEMbFIjCCOBLX/JKoSBTWoEYSSw5S9ZhTCwSY0gjAS2/LVsFRcuXEhISFi8ePFbhC2glaCtoMX4RrQFNqlpCilWJi4uLisri28gwtFgy1/LVpGYmHjmzBmJsA9oK2gxvhFtgU1qmkKKNSUlJWXjxo18GxEOBVv+WrYKmJvw6iOsAi3GN6ItsElNU0ixHCoESdwQ2PKXrMIxqMhMbFLTFFIsR0JCAt9GhEPBlr9kFY6BrEIspFgOsgqtwZa/ZBWOgaxCLKRYDrIKrcGWv2QVjoGsQiykWA6yCq3Blr9kFY6BrEIspFgOsgqtwZa/ZBWOgaxCLKRYDrIKrcGWv2QVjoGsQiykWA6yCq3Blr9kFY6BrEIspFgOsgqtwZa/ZBWOgaxCLKRYDrIKrcGWv2QVjoGsQiykWA6yCq3Blr9kFY6BrEIspFgOsgqtwZa/TmAVycnJfJHGrFmzZvv27XypVaxbRVVV1YcffnjixAnTQmxS0xSbirWnTx2iNOjorKwsvrRx2HPxHGQVWoMtfx1vFadPn+aL7MPijnl5eeHh4XypGRb3tQeLO/bp02f+/Pl8qVWUrOI///lPWFhYp06d9u3bx4WwSU1TbCrWZp/aqTSGt7f3xIkT+dJ6evTokZiYyJfah0U1SnZcvDlkFVqDLX8dbBUg6KioKL7UDpR2fO211zZv3syXNkRpX5so7agiMzmrqK6ufvPNNzt06AB6euyxx8x94jo+qWmKTcXa7FN7lCazbt26r776ii+tR7VVKKlRsuPizSGr0Bps+aveKkpLS3ft2pWTk3P8+HHQ8alTp3755Zfx9UAJbLNq5eXlsHbetm0b1DfdfefOnampqYWFhbBtcUfg4sWLvXr1unDhglzSmJOanlFSPqn0Z2bCebOzs3Nzc01DSshWcfbs2YiIiEcffRSU1LNnz8cff9yiT1zHJzVNsalY631qqrSCgoKysjJWXlFRceLECbkaiIcpqri4uKSkRC6HTs/IyABlwnE4qzBXrGRJn1bUKNm6eIuQVWgNtvxVaRVbt26FlgoJCenateutt94aGxsLmfP+++8/XA9kHWxDtaysLBcXlwEDBgwdOrR169bffPMN2x1e+vv7jxgxolWrVklJSeY7Mr788svZs2fLLxtzUu6MUGK+owxk5oQJEzw8PDw9Pe+8885hw4aZRi0CLXbgwIGBAwfCAR+q5+mnn4YjKPnEdXxS0xSbirXep6ZKGzx48EsvvcS2Fy1adNtttzFXOHfuXMuWLdl3BkFBQXPmzGF1duzY8eCDD4JD9OvXr3fv3p07d5atwqJiLerTiholWxdvEbIKrcGWvyqtomPHjqtWrZLqp2OBgYGQUax8Yj1sG1KrTZs2ixcvZi+XL18Oe8HM6NixYzfddFNlZSUUHjp0iH0+a7qjzLhx477//nv5peqT5uXlmZ+R29EUyMy77rprz549sA0XAPvu3buXr9SQKVOmwIkeeeQRODuzinbt2rENogmwqVjrfWqqtI8//hi6km37+fm5u7tDCWxv2bIFFougPcnEKkBvHTp0mDFjBqsPC4VbbrlFtgpzxVrUJ1vNKKlRsnXxFiGr0JqHyCqu22EVLVq0gMkU246MjJQlbip3mH81a9ZsxYoVH9QDWQEvYaSGIRvSIzQ01PRGEfM8gfkXTNJNS1SfFOb75mfkdjQFMvPll1+WX8LU79NPPzWJWwBarKqq6p133oGpH/vc6aF6t4D05hv3T7BJTVNsKtZKn3JKg5ewksjNzc3Pz2/fvj3M8WGdAeWTJ0+WVxuyVcCqEQT2888/y7v7+PjIVmGuWIv6hKSQlNUoWb14JcgqtAZb/qq0iujoaF9f3/T0dEgkmO9kZmayclO5p6SkwKJ7ZkOOHDkCoVOnTsE2KB4OAlN+bkfGe++9t3r1atOSxpzU/IzcjqZw3yLCNHDt2rUmcQvI31VUV1dv2LDhySef7Nq1KxhG27ZtldwCm9Q0xaZirfSpudJCQkIWLlwYHx8PAzQo5/bbbwczAOOXpxqyVaSlpTVv3tx0X9PvKswVq6RPSVmNktWLV4KsQmuw5a9Kq4BpEaTTlClTpk+fnp2dLZebyv3w4cMwY5LHZeD8+fPytlS/eB89evTw4cMlS3nSv39/7pvwxp/U9IySpZMyVGSmbBUyMKyMHz8e9OTi4mLRLbBJTVNsKtZKn5orLTk5uVevXoGBgbt375bqv72YNWsWrDDkCrJV7N+/H/Qmf9UMK0s4smwV5oq1ok8lNUpWL14JsgqtwZa/Kq3C29t77NixGzduhPW1fE8RMG3atGHDhoH62Z0eTz31FKQcu4cEUsXNzQ1mZ0ePHo2Kijp58iQUxsbGBgcHm+8IS/Jnn31WPixD9Un37dtnfkbzHSdMmMA+WVaRmeZWwSgoKIBpI/1fhdbYVKxSn1pUWllZ2d133+3q6speJiUlwcJC/kJCavi1tr+/f9++fUtKSiorK1944YWWLVvKVmFRseb6ZJ9fKalRUr54K5BVaA22/FVpFampqR07doQxd9CgQa1atRoxYgT7ag6mz+xGDvZN4OnTpyMiIu65554HHngAUgJW4lL9nYWRkZF33HHH/fff7+7unpOTY74jzMLM71tXfVKLZzTf0cfHh90GM27cOJgPyueFxGZXbgUlq2DQf2trjU3FKvWpRaUB4eHh4PFsG9YcYABg9nL06aefXrZsGduG2QCM/uAl0KHz5s2DSQmTk6SgWHN9sspKapSUL94KZBVagy1/1VgFLAuaN29eVFTEXoL0b775Znn8tUhFRQVXAjljXsiAECQDV9j4k1o5Y+OxbhUWwSY1TbGuWCUsKk0dMBtgN0fJ2FSsdmqUyCq0B1v+qrEKUD/M0JcuXZqfn5+bmwsL53bt2pWXl/P11LJ///74+HiuUOuTNhKyCrFYV6wSFpXmKMQqlqxCa7DlrxqrAA4ePDh16tQhQ4YMHz587ty5xcXFfA0NEHJSOyGrEItNxQpBoGLJKrQGW/6qtAqCg6xCLKRYDrIKrcGWv2QVjoGsQiykWA6yCq3Blr9kFY6BrEIspFgOsgqtwZa/ZBWOgaxCLKRYDrIKrcGWv2QVjoGsQiykWA6yCq3Blr9kFY6BrEIspFgOsgqtwZa/ZBWOgaxCLKRYDrIKrcGWv2QVjoGsQiykWI63336bbyPCoWDLX8tWERcXxz2lgLACtBW0GN+ItsAmNU0hxZpSUFDw0Ucf8W1EOBRs+WvZKrKyslJSUngBEgpAW0GL8Y1oC2xS0xTtFHvq1Cn2TGLHAsdkT5B1OOATr776anV1Nd9GhEPBlr+WrQJIS0tLSEh4m7AFzGc3btzIN58dYJOa1jhcsdOnT/f29m7Tps3ChQv5WKOBY7Zt29bd3X3q1Kl87AaZMWPGI4888pAyLi4uERERqampv/32G99qhFoeQpa/ilZBaA02qTkRGRkZAQEBrVu3fvjhh8ePH8+HHQQM3+3atYNT+Pr6wpKID98ImZmZHTp0kL3By8srMDDw73//OzmEdmDLX7IKYWCTmv6prq7+5JNPPD095Ul6p06dYLHC13MQcOQePXqwE4FhuLq6vvvuu6o/OPrwww/hCOxQsF4JCwvLy8vjKxGOA1v+klUIA5vU9ExVVdVbb7312GOPyQM324BZ/6+//srXdhBwZPmMsjm5uLjExsbC9fC17WD27NngbXCQV155JTEx0cPD47nnnsvJyeHrEY7gIWT5S1YhDGxS0yfsF21hyPbz8wsNDYVhetmyZd7e3mzgHjlyJL+DQ3nmmWfat28PJ4Izrly5cu7cueHh4d26dYNCuCq4Nn4Hq9TW1sJiAuzt8ccfh5dXrlyBRVLPnj1DQkIyMjKuXbvG70A0Amz5S1YhDGxS0xtXr17Nzc394osv8vPza2pqWGFZWZmvr++2bdvYBD81NbXBPo4mLS2tS5cucK7MzEwfH5/S0lJWDtcDVwXXBlcI19lwJ2v89ttvgYGBcED5ljxwCHg7Q4YMCQgISE5OBv9ouAehEmz5S1YhDGxS0z8wjMKQumLFiuv1vdO2bVvtPn1iwPHZqgK2V61a1b9//z/++IOvdIOUlJR4eHiYr4cOHDgQGRnp6ekJyyZ1H3ARpmDLX7IKYWCTmv558cUXo6Oj2Tb0zqBBgxrGNWHs2LGyEqZPnw6jeeM/Kfrhhx/c3NwuXLjAB65fLywsnDlzpqura2xs7MmTJ/kwYTfY8pesQhjYpKZz3nnnneDgYPnzGeidtWvXNqyiCWlpabISampqRo8evWDBgoZV1JCZmZmUlMSX/kllZeWSJUvc3d2ff/75Q4cO8WHCDrDlL1mFMLBJTc9s3brVz8+vvLxcLnFxcdH60ycGnAXOJb+8ePHiE088sW7duv/XUMuuXbv4ooZcunQJ7KR79+7Dhw//6quv6urq+BqEMtjyl6xCGNikpluOHDkC8+ujR4+aFkZERJi+1BTuXMXFxV5eXtnZ2aaF2lFbW/vFF18MGjSod+/eYFGq/7EDG9jyl6xCGNikpk9KS0t9fHwyMzO5cu3+884c83N99913np6eJ06c4Mo1Ze/evc888wy41IoVK2Bxw4eJhmDLX7IKYWCTmg65fPny4MGD33vvPT5Q/7kQX6QZFs+Vmprq7+/f9Lcq/fTTT9OmTXNzc5s7d+7p06f5MPEn2PKXrEIY2KSmN+rq6qKioqZMmcIHdMOSJUtCQkKE/CdEWVlZXFxc586dJ02adOTIET5M4MtfsgphYJOa3khMTISBWM8fzYOZTZ48+cUXXxT1hfPvv//+0Ucf+fr6jh49+ptvvuHDuMGWv2QVwsAmNV2xefPmbt26VVZW8gGdAUsK8LO3hf6k3dWrV9PT04OCgvr27btp0yb5P9uRgy1/ySqEgU1q+uHw4cMeHh75+fl8QJecO3fO399f60eM2ENWVtaYMWO8vb0/+OADSZL4MDKw5S9ZhTCwSU0nnD17tmvXrl9//TUf0DEFBQWenp7fffcdHxDB0aNHY2JiOnXqNH/+fPmhVQjBlr9kFcLAJjU9cOnSpf79+8OkmA/onm+//dbLy6uoqIgPCKKkpGTevHlgGFOmTHGW9ZljwZa/ZBXCwCY14dTV1U2YMOGVV17hA07C+vXre/bsef78eT4gDkmSVq5c2aVLl3HjxoGZ8WFDgy1/ySqEgU1qwomPjw8NDXXqb2UXL148fPhwvd21BU26YcOGPn36DBgw4PPPP7+hp6Y7L9jyl6xCGNikJhb266S6mpKrgP0vSHR0tKjbZ63z3//+d+TIkX5+fh9//HHjn6auc7DlL1mFMLBJTSA5OTmenp4//fQTH3BCrly5EhwcnJCQwAd0w/fffz9x4kR3d3dYxlVUVPBho4Atf8kqhIFNaqI4c+aMt7e3zcesOhHnzp3r3r17SkoKH9ATP//88xtvvOHq6jpjxowmfphV04Atf8kqhIFNakL4/fff+/Xrt2bNGj7g5LDbZ/ft28cHdMb58+ffeecduNSIiIgDBw7wYWcGW/6SVQgDm9SanmvXrj377LOzZ8/mA4YgOzsbhuDCwkI+oD+uXLmSnJwcEBAQHBy8bdu2xv/Mnx7Alr9kFcLAJrWmZ8GCBWFhYQa+IWfDhg09evRo+qfPqgMcIiMjY+jQoeAZ//73v4U8BtGBYMtfsgphYJNaE7N+/XoYkgz/uwvx8fE6f+ihOQcPHoyMjIQl0bJly5zF58zBlr9kFcLAJrWmhP00kH7+t1k76urqJk2aJPDps6opLCycOXOmq6vr66+/furUKT6se7DlL1mFMLBJrcmAcacpf3BUOOzps0uWLOEDzkBFRQUsjNzd3V944YXDhw/zYR2DLX/JKoSBTWpNgyRJgYGBa9eu5QOGpqqqqkePHps2beIDTsIff/yxZs2abt26jRgxYvv27XxYl2DLX7IKYWCTWhNQW1s7duzYOXPm8AEEFBYWenp67tmzhw84D1evXt28efOAAQPA7Dds2KDzR7Bgy1+yCmFgk1oT8MYbb4wbNw4Mgw/gYO/eveAWBvh/t+zs7H/84x9dunRZuXKlbn8YA1v+klUIA5vUtCY5ORlmo7odWZqGlJQUf3//c+fO8QEnJD8/f+rUqZ06dZo3b15JSQkfFg22/CWrEAY2qWkK+zkHZ7yRxuG8/fbbQ4cOdfb/WpApLS2dP38+GEZMTMyxY8f4sDiw5S9ZhTCwSU07ioqK9PMjccKpq6uLjo6OiopyuttnrQCLxQ8++MDb23vs2LG7d+/mwyLAlr9kFcLAJjWNuHjxYkBAwIYNG/gAYqqrq4cNG7Z48WI+4OTU1NRs2rTpySefDAoK+uyzz8T+Hz62/CWrEAY2qWkBDBajR49euHAhH0DP+fPne/bsuX79ej5gCHbs2DFq1Cj2wxi///47H24SsOUvWYUwsElNC2bNmhUREWGMx885HPa5nIF/x/SHH36Iiopyd3eH9VN5eTkf1hhs+UtWIQxsUnM4a9as6devn6hJpVPAHnBijN90UkLUD2Ngy1+yCmFgk5pj2blzp7e39y+//MIHiIakpaV17969srKSDxiLCxcuLF++nP0wxv79+/mwBmDLX7IKYWCTmgOBabKHh0dOTg4fICyRmJgYHBx8+fJlPmA4qqur165dGxAQMGTIEK1/GANb/pJVCAOb1BxFVVWVv79/eno6HyCUiYmJmThxopFun7UCvM3MzMyQkJCePXtq98MY2PKXrEIY2KTmEGpqakJDQ+Pj4/kAYRWYbkO7xcXF8QFDI/8wxtKlSx3+wxjY8pesQhjYpOYQpk2b9vzzzyOZHTuW8+fPBwQEfPrpp3zA6LAfxnj88cdjY2NPnjzJh9WCLX/JKoSBTWqNZ9WqVQMGDLh06RIfIOyjqKjIy8vLwLfPWqGystKxP4yBLX/JKoSBTWqN5Ouvv+7atevZs2f5AHEj7N+/39PTs6CggA/gAOYZjvphDGz5S1YhDGxSawzHjh3z8PBwyGSQSEtLM8zTZ9VRW1u7efPmgQMHBgYGrl+/Xt0PY2DLX7IKYWCTmmoqKythGrhlyxY+QKglISHBSE+fVc2ePXvGjx/fpUuX999//0YfX48tf8kqhIFNauqorq4OCQlZunQpHyAaAXv67OTJk+kGAeD48eMvvfSSm5vbm2++af8PY2DLX7IKYWCTmjpiYmImTZpEI5rDYR68ZMkSPoCV0tLSBQsWdO7cGUz06NGjfNgMbPlLViEMbFJTwbvvvjt48GAM/2YshKqqqh49eqSkpPABxPz666+rV6/29vYeM2ZMVlYWHzYBW/6SVQgDm9RulIyMDF9f37KyMj5AOI4TJ054enru27ePD+CmpqYGHLRv375BQUHp6ekWv/fGlr9kFcLAJrUb4ujRo+7u7keOHOEDhKPJzs728vIqLi7mA0T9UynDwsJ8fHw++uij3377zTSELX/JKoSBTWr2U15e7ufn9+WXX/IBQhvWrVv3xBNPXLx4kQ8Q9eTl5U2ePLlz586LFi2Sl7nY8pesQhjYpGYnV65cCQ4OXr58OR8gtGTBggWjRo2y+EkLwThz5szcuXPd3NymTZv2448/YstfsgphYJOanURHR7/44ot8KaEx165di4yMnD59Oh8gGgJrr3fffdfLywvyd+/evXzYuJBVCIOswpwVK1YMGTKE/jVMCH/88Uf//v1XrVrFBwgzqqurIX979+49cODALVu21NbW8jUMB1mFMMgqOLZt2+br69v0P5JMyJSWlvr4+GRmZvIBwgzI37q6uq+//jo0NLR79+5JSUnGfpAlWYUwyCpMgSltt27d8vLy+ADRtBw5cgQ6ArqDDxANMc3fQ4cOPf/88+7u7vHx8RUVFSa1jANZhTBUWMWFCxcSEhIWL178lhFZsGABX9SEQKsmJibe6IOAGoNue1NsRzQx0P7QCyru/jLP35MnT8bGxrq6us6cObOwsJCLmrJr1664uDj+UnSDxTYhqxCGudRsAmPZmTNnJEIboG2XLVvGN7pmUG/qBOgF6Au+e2yhlL9VVVWgIk9Pz8jIyAMHDvDh69fT09NTUlL4i9AZ5m1CViEMJalZAQyf71LCoTTlM5GoN/UD9AXfPbawnr9XrlxJTk4OCAgYMmTItm3brl27JodAY/zpdQnXJmQVwrAuNYvQ4KI1ZBU4cbhVMMAhMjIyQkJCevbs+cknn7Bb+8gqiBvDHqlx0OCiNWQVONHIKmRycnKee+45Dw+PxMTEefPm8afXJWQVeuGGpMagwUVryCpworVVMIqKil599dUOHTpUVFTwV6A/yCr0ggqp0eCiNWQVOGkaq2A4S7+TVegFFVJzFpE5L2QVOGlKq6DvKogbQ4XUaHDRGrIKnJBVmENWoRdUSI0GF60hq8AJWYU5ZBV6QYXUaHDRGrIKnJBVmENWoRdUSI0GF60hq8AJWYU5ZBV6QYXUaHDRGrIKnJBVmENWoRdUSI0GF60hq8AJWYU5ZBV6QYXUmmZwSU5O5otunA8//DArK4sv1T3ObhWY+64xOIVVrFmzZvv27XypZpBV6AUVUtNicOHIy8sLDw/nSxXw9vaeOHEiX1pPjx492DO9VXD69Gm+qKlwFquw2ETO3neN2beROIVV9OnTZ/78+WzbSvfZgz1NTVahF1RIrTGDi5289tprmzdv5ksVWLdu3VdffcWX1qN6uIFkiIqK4kubCqewCqUmcuq+a8y+jcfprMJK99nEzqYmq9ALKqRmz+Cyc+fO1NTUwsJC9rKoqKisni+++OLixYussKKi4ptvvvnss89+/vnn/+8pSVChV69eFy5cgO2CggLYS65/4sQJuRocvLS0FDaKi4tLSkrk8rNnz2ZkZOzatQuOYzrcQGUozMnJOX78OMj01KlTrLy8vBwW1Nu2bWNHA3755Zfx9UBN2GaFpphfuekb3Ldvn2llKyEldGUVpl0AQJucO3dOqYn033eMG3pTMub9Lin3r1K5FXRoFeZv2dQquO4z7w7pz3Y4f/787t27Dx8+zAptNrUMWYVeUCE1m4PL0KFD/f39R4wY0apVq6SkJKl+hrhy5Up3d/f27duzOnv27OnQoYOHh0f//v3vuusumJ7Iu3/55ZezZ89m24MHD37ppZfY9qJFi2677TYmTUjsli1bss9Mg4KC5syZw+rs2LHjwQcfhNP169evd+/enTt3ZsPN1q1b4Z2GhIR07dr11ltvjY2NZcfJyspycXEZMGAAXHPr1q0hK6Dw/ffff7geGPVgmx1ZxuKVwxlfeeUVNzc3uBi4APgLox6rbyWkhK6sArrsk08+YdtVVVXNmjWDFlBqIp33ncwNvSmGxX6XlPtXqdwKerMKi2/Z1CpMu89id0j17TBr1ixoB09Pz9tvvx3sQbK7mySzNiGrEIYKqVkfXI4dO3bTTTdVVlbC9qFDh9jHkSAXMI9NmzaxOjDFgFyVP+XcvHnzqFGj/jyANG7cuO+//55tf/zxxx07dmTbfn5+YDZQAttbtmx59NFH2QJF1iuMQaDsGTNmsPowu7nlllvYcAMHWbVqlVQ/7Q0MDISRi9Vv06bN4sWLWf3ly5dDNTYjnlgPKzdF6crhDUJLssuG+RdcRkxMDKtjJaSE/q1CUmgiPfedKTf0piTlfpeU+1ep3Aq6sgqlt2zRKqx0B7TDfffdd+DAAdj+7rvvoKlZmyg1NQdZhV5QITXrgwuYBKgkNDTU9PYVkAssMuSXMOMAxZw8eVIukYEJ48CBA01fwmw0Nzc3Pz8fhAsTEJirQvnkyZPlGausV1jmw2FNPxzw8fFhw02LFi1g0soKIyMjmUZhYgv1V6xY8UE9oG94CfYmKetY6crhDb7xxhvyS8gZmGHZDCnhpFah874zxf43xVDqd0m5f5XKraArq1B6yxatwkp3QDvIC00AVicwV5CUm5qDrEIvqJCazcHl1KlTM2fOhEWor69vXl6eVC8X071SU1Mh//+/gwnvvffe6tWrTUtCQkIWLlwYHx//8ssvw5FhDQsDSrt27WQrkvWalpbWvHlz0317/Pl5d3R0NFxMeno6DFgg1szMTChMSUm59dZbZzbkyJEjkrKOla5cPhEjOTn5zjvvtBlSwkmtQud9Z4r9b4qh1O+Scv8qlVtBV1ah9JYtWoWV7oB2AAHIu997773QlZJyU3OQVegFFVKzObgwYE06evTo4cOHS2ZygZkmJGdOTo5ccubMGbbRv39/0+/EpPoc69WrV2Bg4O7du6X6T8BnzZolf+chmeh1//79cFg4OCuHIQAWxSxdYb4Dw9aUKVOmT5+enZ3NKhw+fBjqMzNjwKKbbSjpWOnK4Q1CbsiFcD2dOnVi21ZCSujKKuBqYZ7ItqHprIyqOu87U+x/UwylfpeU+1ep3Aq6sgqlt2zRKqx0B1mFQVAhNeuDy9GjR6Oioti6NTY2Njg4WDKTC9CvX7/u3btD5YsXL0LStm3btrKyElaszz77rGk1oKys7O6773Z1dWUvk5KSYHIqf6gtNfxuzd/fv2/fviUlJXC0F154oWXLlmy48fb2Hjt27MaNG3fs2CHflwU89dRTMJaxm3NgyHBzc2OfgUybNm3YsGEgd3azzYQJE9jH5ZLClcMb/Nvf/paRkSHV59h9990np6KVkBK6sooxY8ZAkxYXF+/du9fPz++vf/0rG1W5JtJt31nEzjdls98l5f5VKreCrqxCUnjLFq1CUu4OJauwp5skszYhqxCGCqlZH1zOnj0bGRl5xx133H///e7u7mxWMnLkSHkSx4AZyjPPPAPDAaxbfXx82GwRpo0Wb9MODw+XJ2gwb4W9TO8+fPrpp5ctW8a2CwoKQLIwHsH7mjdvHpgW+yoVVtMdO3YE3xo0aFCrVq1GjBjBvnM7ffp0RETEPffc88ADD4C4mYil+ns/2B0abHe4QvnzVotXDvkA0ofUgoNDMrz++uvyPcFWQkroyip+/PHHJ598skWLFp6entu3b/fy8jp48KBk1kS67TuL2PmmbPa7pNy/SuVW0JtVWHzL48aNg3Ueq2DafUrdweU+HId9hGhPN0lmbUJWIQwVUrM5uACQzHb+ci+bmkn1u8CspGFQJVVVVaZpCdOi5s2bFxUVsZeg6Ztvvtl0ZS3V3z9u+tIe5CuX6scFNgU2P46VkBK6sgp70G3fnbYEX+kGMe13Sbl/lcqtoDerkOHesnXsf7/2QFahF1RIzSGDizn79+/nPqRyFDDQwCpn6dKl+fn5ubm5MNdr165deXk5X68RyOOCOVZCSjidVei278ItwVdqHEr9q1RuBd1ahUDIKvSCCqk5ZHBpYg4ePDh16tQhQ4YMHz587ty5xcXFfI3G8dprr33++ed8aT1WQko4nVVoitZ910iU+lep3ApkFeaQVegFFVLT/+Di7JBV4ISswhyyCr2gQmo0uGgNWQVOyCrMIavQCyqkRoOL1pBV4ISswhyyCr2gQmo0uGgNWQVOyCrMIavQCyqkRoOL1pBV4ISswhyyCr2gQmo0uGgNWQVOyCrMIavQCyqkRoOL1pBV4ISswhyyCr2gQmo0uGgNWQVOyCrMIavQCyqkFhcXZ/NpNoRqoG3j4+P5RtcM6k2dAL3QlFaxevXqgoIC/iJ0hnmbkFUIQ4XUsrKyUlJS+F4lHERaWtq3337LN7pmUG/qBOgF6Au+e2yhIn8Z1dXVs2fP1rlbmLcJWYUw1EkNhrOEhIS3CUcDc6hNmzbxza0x1JvCgbXdxo0b+Y6xA3X5y6ipqYG1BX8pusFim5BVCKMxUiMIQizY8pesQhjYpEYQRgJb/pJVCAOb1AjCSGDLX7IKYWCTGkEYCWz5S1YhDGxSIwgjgS1/ySqEgU1qBGEksOUvWYUwsEmNIIwEtvwlqxAGNqkRhJHAlr9kFcLAJjWCMBLY8pesQhjYpEYQRgJb/pJVCAOb1AjCSGDLX7IKYWCTGkEYCWz5S1YhDBcXlytXrvClBEHontra2kcffZQvNTRkFcIIDw9v+keZEgTReIqKirp3786XGhqyCmEcP37cw8MjJSWF1hYE4URcvnw5JiYmLi6ODxgasgqRgFuEhYW5uLg8RBCEk9C6devIyEhsMzyyCoIgCMIGZBUEQRCEDcgqCIIgCBuQVRAEQRA2+B/ije93z14TJQAAAABJRU5ErkJggg==" /></p>

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

<!-- pu:deep/plant_uml/widget_ok.pu--><p><img src="data:image/png;base64,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" /></p>
[演習-Pimpl](exercise_q.md#SS_22_9_3)  

---

### lightweight Pimpl <a id="SS_9_2_2"></a>
[Pimpl](design_pattern.md#SS_9_2_1)の解説で示したように依存関係をシンプルに保つには極めて有効なパターンではあるが、
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

---

### BitmaskType <a id="SS_9_2_3"></a>
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

---

### Future <a id="SS_9_2_4"></a>
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

---

### Null Object <a id="SS_9_2_5"></a>
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

---

### Cでのクラス表現 <a id="SS_9_2_6"></a>
このドキュメントは、C++でのソフトウェア開発を前提としているため、
ここで示したコードもC++で書いているが、

* 何らかの事情でCを使わざるを得ないプログラマがデザインパターンを使用できるようにする
* クラスの理解が曖昧なC++プログラマの理解を助ける(「[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)」参照)

ような目的のためにCでのクラスの実現方法を例示する。

下記のような基底クラスPointとその派生クラスPoint3Dがあった場合、

<!-- pu:deep/plant_uml/class_c.pu--><p><img src="data:image/png;base64,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" /></p>

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

---

## オブジェクト生成系デザインパターン <a id="SS_9_3"></a>
### Singleton <a id="SS_9_3_1"></a>
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
(「[Named Constructor](design_pattern.md#SS_9_3_2)」参照)と呼ばれる。

[演習-Singleton](exercise_q.md#SS_22_9_14)  

___

### Named Constructor <a id="SS_9_3_2"></a>
Named Connstructorは、[Singleton](design_pattern.md#SS_9_3_1)のようなオブジェクトを複数、生成するためのパターンである。

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

次に示したのは「[Factory](design_pattern.md#SS_9_3_4)」の例にこのパターンを適応したコードである。

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

___

### Clone(仮想コンストラクタ) <a id="SS_9_3_3"></a>
オブジェクトコピーによる[スライシング](class_design.md#SS_8_3_4_3)を回避するためのイデオムである。

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

___

### Factory <a id="SS_9_3_4"></a>
Factoryは、専用関数(Factory関数)にオブジェクト生成をさせるためのパターンである。
オブジェクトを生成するクラスや関数をそのオブジェクトの生成方法に依存させたくない場合や、
オブジェクトの生成に統一されたルールを適用したい場合等に用いられる。
DI(「[DI(dependency injection)](design_pattern.md#SS_9_5_1)」参照)と組み合わせて使われることが多い。

「[Templateメソッド](design_pattern.md#SS_9_4_1)」の例にFactoryを適用したソースコードを下記する。

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

___

## オブジェクトの動作/協調に関するデザインパターン <a id="SS_9_4"></a>

___

### Templateメソッド <a id="SS_9_4_1"></a>
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
この性質は、[Factory](design_pattern.md#SS_9_3_4)や[Named Constructor](design_pattern.md#SS_9_3_2)の実装には不可欠であるが、
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

___

### Strategy <a id="SS_9_4_2"></a>
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
その属性の追加に対して「[オープン・クローズドの原則(OCP)](class_design.md#SS_8_1_2)」に対応した構造となった。

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

あるいは、[DI(dependency injection)](design_pattern.md#SS_9_5_1)と組み合わせて、下記のような改善も有用である。

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

___

### State <a id="SS_9_4_3"></a>
Stateは、オブジェクトの状態と、それに伴う振る舞いを分離して記述するためのパターンである。
これにより状態の追加、削減、変更に伴う修正範囲が限定される
(「[オープン・クローズドの原則(OCP)](class_design.md#SS_8_1_2)」参照)。
またオブジェクトのインターフェース変更(パブリックメンバ関数の変更)に関しても、修正箇所が明確になる。

<!-- pu:deep/plant_uml/state_machine.pu--><p><img src="data:image/png;base64,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" /></p>

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

    ThreadOldStyleState thread_old_style_state;  // 状態の保存
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

    // スレッドをrunning状態に移行させる
    void ThreadOldStyleRun()
    {
        switch (thread_old_style_state) {
        case ThreadOldStyleState::Idle:
        case ThreadOldStyleState::Running:
            thread_old_style_state = ThreadOldStyleState::Running;
            break;
        case ThreadOldStyleState::Suspending:  // suspend状態
            --thread_old_style_suspend_count;  // suspend状態はネスティングする
            if (thread_old_style_suspend_count == 0) {
                thread_old_style_state = ThreadOldStyleState::Running;  // suspend状態 ->  running状態
            }
            break;
        default:
            assert(false);  // バグ以外でここに来ることはない
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

<!-- pu:deep/plant_uml/state_machine_class.pu--><p><img src="data:image/png;base64,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" /></p>

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

___

### Observer <a id="SS_9_4_4"></a>
Observerは、クラスSubjectと複数のクラスObserverN(N = 0, 1, 2 ...)があり、
この関係が下記の条件を満たさなければならない場合に使用されるパターンである。

* ObserverNオブジェクトはSubjectオブジェクトが変更された際、その変更通知を受け取る。
* SubjectはObserverNへ依存してはならない。

GUIアプリケーションを[MVC](design_pattern.md#SS_9_5_2)で実装する場合のModelがSubjectであり、
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

<!-- pu:deep/plant_uml/observer_class_ng.pu--><p><img src="data:image/png;base64,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" /></p>

このようなクラス間の依存関係は下記のようにファイル間の依存関係に反映される。
このような相互依存は、差分ビルドの長時間化等の問題も引き起こす。

<!-- pu:deep/plant_uml/observer_file_ng.pu--><p><img src="data:image/png;base64,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" /></p>

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

<!-- pu:deep/plant_uml/observer_class_ok.pu--><p><img src="data:image/png;base64,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EEg50/DJJ5+cPn3aLb0lfPTRR27RDeDLL788dOiQW6q4ip9//vnTTz91S68iXZuGs2fP7ty50y29JZw6dQoiuaWh8Ouvv27atIl/3R2Kq9i+fftvv/3mlvpI76Zhx44d586dc0tvCbcmfYcPH74F0mYcXLhwgSzpll6FmoYQCGoannrqKUfQt27dWrVqVbskJGrWrLlw4UK39Oaxfv36du3asfHHH38MGTIkZ86c2bNnL1KkyMyZM92q1+K555575pln3FLPS0xMrF+/vlt68+B6pkyZUqxYsXz58mXLlq1hw4b4JLO3V69eEydONB+7d+/eqFGjn376yZSkJjZs2FCiRInChQvXqVPHyBkpjY/XE5dwmQZySXR0tFPYokWL5cuXO4VJ4O23337ggQfc0pvHL7/8AlXEetK5XBgdnTlz5pYtW544ccKtbeH8+fNEIt7F3eF57du3X7p0qVt689i/f3+TJk2IhbvvvptwGD9+vMnBBw8evO+++0zN3bt3ly5dmjYxJamJy5cvt27dulChQtBv/vz5pnzevHkDBw78bz0LYTQNMG3x4sV2ydq1axs0aGCXhES5cuXee+89t/TmsWLFiq5du7JBz6In2Xzce++9zhUGolOnTqifW+p57777bkJCglt68+B6Ro8eTYfmz5+fS2rWrBmUM3s7dOgwY8YM2f7999+feOIJWhUamAqpiVWrVhUvXrxgwYJNmzY18st4qVatWidPnry27v+HmoYQCGoaaF874QGGTffcc49dEhIhTcPIkSPffPNNt/RakNjKli177NgxthcsWID0SJLbtm0bQrlnzx6nvo3rmYZdu3Z17NjRLb0BECe23Hfr1g1p5krYvnTpEnuJHw4uex977LHnn39etrmSUqVKJZ1mkhE//vgjjW+XIDQIEBsEMMbLlCOI8fHx/61nIVymYfPmzXnz5nUKY2Ji5s6d6xQmgZCmAR9A4ndLA8AV9uzZ0/O1r2jRoiNGjGAb6UGUyf1ubQtJmAbI8P7777uloXDkyJFHHnnEfNy3b9+dd945dOhQ5M+7aguefPJJ2bt3797bbrtNtrlTXEXQBJlCoNFsVeEjbCSQcTkECD7M7KpSpUrQAV8YTUNsbKwzGlm5cuX9999vl4RESNPQp0+fdevWuaXXgp5FXsTiT5s2rWTJkt988w3bGzduJAV+9dVX7hcs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" /></p>

最後に、上記のファイルの依存関係を示す。
ファイル(パッケージ)の依存関係においてもSubjectOKはObserverOKに依存していないことがわかる
(MVCに置き換えると、ModelはViewに依存していない状態であるといえる)。

<!-- pu:deep/plant_uml/observer_file_ok.pu--><p><img src="data:image/png;base64,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" /></p>

[演習-Observer](exercise_q.md#SS_22_9_24)  

___

### Visitor <a id="SS_9_4_5"></a>
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

<!-- pu:deep/plant_uml/visitor_ng1.pu--><p><img src="data:image/png;base64,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" /></p>

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

<!-- pu:deep/plant_uml/visitor_ng2.pu--><p><img src="data:image/png;base64,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" /></p>

これはポリモーフィズムによるリファクタリングの良い例と言えるが、
SRP(「[単一責任の原則(SRP)](class_design.md#SS_8_1_1)」)に反するため、
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

        virtual void Accept(FileEntityVisitor&) const = 0;  // Acceptの仕様は安定しているのでNVIは使わない。
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

<!-- pu:deep/plant_uml/visitor_ok.pu--><p><img src="data:image/png;base64,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U1OVXONMurBhwwZzc3PShatXr0qrAdA6irU0MK5du+bg4DBkyBC8rqK48ddff0VEROjr66vbDf3KRtOlwc3NTUdHh5UPHDhgbGycnp7+fhOlQ0OOdevWmZmZ/fTTT7QPkVYDoKVAGv4HP14dFxcnrQPaTlpamrOzM40UMzMzpXVaikZLw++//163bl12pOHo0aOGhoY3b96UNlImpAuxsbGtW7emkUZqaqq0GgCtBtLwNzRY6datW69evSiLSOuAVvPmzZvly5cXn9txNVoatm7dWqtWrdq1a586dcrAwKAoTwqQLkRHR5uamg4fPvzGjRvSagCKAZCG93j79u2GDRsoecyePfvFixfSaqDVkDV26dJlwIABqrqersjQaGno1KlTtWrVdHR0qomoX79+cHCw8p77Sbqwdu1aExMTT0/PIj6wAYBaAWlQgCAI/v7+NJ5ISEiQ1gGt5s2bN5GRkVp/okpzpeH333+vVauWWBdq167dr1+/J0+eSJsWEq9evVq9erWxsbGXl9ft27el1QAUMyAN+XL16lVnZ+eePXveuXNHWge0mrt373bt2pVSkbYectBcaVi1ahVzhQYyJkyYoLyjC6QLK1euNDIyGjVqFHYCADAgDf8AjTgNDAxmzZr166+/SuuA9vL27VtKGPr6+hs2bJDWaT6aKw1t27Zt0qRJ06ZNZ86cqTxdePnyZWRkpKGhobe3N65wAkAMpOGfEQQhICCA1CE6OvrPP/+UVgPt5d69e926devbt6/80e/ff/998eLFYWFhszWQ2rVrS0OaQEhISP369UePHq08Xfjjjz9IF+g/u4+PT9HfxgmA+gNp+FhoDzJkyBArK6t9+/ZJ64D28vbt29WrV+vr669bt04cX7Jkyd27dwVQhJDD3b9/f8OGDTt37hRvi0KBdGHZsmWkC2PGjKEFSasBADIgDZ/G6dOnnZycXF1dL126JK0D2gvlqu7du/fu3fvx48csEhYWJs1poKiYO3fu+9vns/j999+XLl1KXjhu3Dja0NJqAIAISENBoIGOubm5l5eXSp5cC1TC27dv165dS6klJiaGPv7rX/+SpjJQVPz73/+Wbp4C8eLFi8WLF9M2HT9+/IMHD6TVAAA5IA0F5PXr1+zevMmTJ2vrNfZAHkotbm5uvXr1CggIkKYyUFR8vjT89ttv4eHh9P93woQJUH8A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" /></p>

このリファクタリングには、

* FileEntityのインターフェースを小さくできる
* FileEntityVisitorから派生できるアルゴリズムについては、
  FileEntityのインターフェースに影響を与えずに追加できる
  (「[オープン・クローズドの原則(OCP)](class_design.md#SS_8_1_2)」参照)

という利点がある。
一方で、この程度の複雑さの(単純な)例では、Visitorの適用によって以前よりも構造が複雑になり、
改悪してしまった可能性があるため、デザインパターンを使用する場合には注意が必要である。

なお、上記の抜粋である下記コード

```cpp
    //  example/design_pattern/visitor.h 38

    virtual void Accept(FileEntityVisitor& visitor) const override { visitor.Visit(*this); }
```

はコードクローンだが、thisの型が違うため、
各Acceptが呼び出すFileEntityVisitor::Visit()も異り、単純に統一することはできない。
これを改めるためには、「[CRTP(curiously recurring template pattern)](design_pattern.md#SS_9_1_5)」が必要になる。

このパターンを用いて、前記したFileEntityの3つの派生クラスが持つコードクローンを解消した例を以下に示す。

```cpp
    //  example/design_pattern/visitor_crtp.h 31

    class FileEntity {  // VisitorのFileEntityと同じ
    public:
        explicit FileEntity(std::string&& pathname) : pathname_{std::move(pathname)} {}
        virtual ~FileEntity() {}
        std::string const& Pathname() const { return pathname_; }

        virtual void Accept(FileEntityVisitor&) const = 0;  // Acceptの仕様は安定しているのでNVIは使わない。
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

---

次に示すソースコードはVisitorとは関係がないが、
FileEntityVisitorから派生するクラスを下記クラス図が示すように改善することで、
単体テストが容易になる例である(「[DI(dependency injection)](design_pattern.md#SS_9_5_1)」参照)。

<!-- pu:deep/plant_uml/visitor_ut.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAV0AAAHLCAIAAADk1dy+AAAAKnRFWHRjb3B5bGVmdABHZW5lcmF0ZWQgYnkgaHR0cHM6Ly9wbGFudHVtbC5jb212zsofAAABO2lUWHRwbGFudHVtbAABAAAAeJytkU1PwkAQhu/7K+ZkyqGkFCGkB0MUMKkQGvnwPNAR1rS7ZHeWhKj/3QVtlBov6t7mnXeemdnpW0bDriyEWBdoLYxkQUPFkg9LaSVrA88C/DtFwTF70fgiDKQ5i6e8JfNe7/XXijon32dVUGakYqqYNTXQlg1heQb8bccMeauwrNitf1mjBo3/CK3/Suh24cvV9xOIb8t8OGuAui/+ySf6pPLT0bMCFS8mY9iTsVIraDXjKO40o+CBckhRQdSDKE7anaTdhXQ2h2O6IYLbbAxWO7MmyKW/m1w59vUNkeIe4d75+UtKYLojlQ7uKgGGai+NViUpFuly8mnoXobXkmFGxk8Cy4kY0CO6gn3FWudSbRJYzEdhT4xRbRxuPPsJxY32XHNIIM3EG4Vm5akPEQsRAABOjUlEQVR4Xu2dCVhUR7r33XdjBCXGLwaNGwqocQ9igiKTEEUR9xnnwz0mjsbda77ojcYlRolEHSaKJi4YBSUOKiF6VVA0xkhEDY4xLnGL+8KZu8y988zM/f7pGouiqvvQTZ/TdHPe39MPT52qOnVqeet/qk4f3q7wvwRBEMWpIEcQBGF5SBcIgpAhXSAIQoZ0gSAIGdIFgiBkSBcIgpAhXTCG7OzsRYsWLSbKmiVLlixfvlzTNHmECFcgXTCA9PT0tLQ0jfAObty4kZCQIA8S4QqkCwbwwQcfyLZJlCkYEXmQCFcgXTAA0gVvY+nSpfIgEa5AumAApAveBumCm5AuGIC+LhQWFmZk7X5z2lthET3ahLRp1KgR/iKMGMQjVT6BcBvSBTchXTAAHV1I3/1F957dO4d1GTfnjYS0jzcc3JR+Zjf+IowYxCMVeeTTCPcgXXAT0gUDsKsLjx49mjTtd+06tZuXtABa4OiDVORBTuSXiyBKC+mCm5AuGICqC5jkAwbHRsb02Xo8VdUC6YM8yIn8JA1GQbrgJqQLBqDqwuQZUzDVd+T/UVUBux/kRH6cJZVDlA7SBTchXTAASRf2Zma269Q+5Wv7K4X31r0//K1fT5w/6fMTO8R45MdZOFcsCvz444/5xbl8+bKYITk5ef/+/WKMSomFGMjp06d//vlnKfLatWvff/+9FGkepAtuQrpgAKIuFBYWhr8S7uiZwsAxgys8IbBV08+/SRNTcRbOlb6h6N+/f7Vq1Z4SmDRpEuI7dOgwfvx4BF555ZX33ntPPEUFhdSsWdNPYPLkyXImhevXr/Mwv5wUr9K9e/dRo0ZJka+//npsbKxWvBwVKVX/QjqQLrgJ6YIBiLpw4MCBLj26qoqAz4fbPqpYseLwSb/Zcmx7z9dfgTT8+ncjpTw4FyUIFv7LlH7zzTfFGEZKSspXX32lOa0LzgiBCMqcMGECP+SXk+JVkpKSIF53797lMVibVK1adffu3ZpQjl3E1BIvpAPpgpuQLhiAqAsz5swcP+cNVRTwiR7e92n/p9lDh7VfbYAuPPdCEykPzkUJgoU71IUrV66w5bqkC5iQ2FZkZmbevn2bRzrSBczYO3fuPHr06PDhw9hc8PibN2/+xsb58+cR1p5cToq/cOHCrVu3+FnIcOnSJRRYt27dDRs28PglS5a88MILbB3Eq804dOjQjh07cBY75KlqBTTb09yvv/4aTRPXEawJALrDl1qkC25CumAAoi680jsiIfVjVRTwadq6Wdfe3flhw2cDIA0pX28X8+BclMBL0xzrQmRk5LvvvqsV14WcnJzAwMCoqKh+/fo1btz44MGDLN6RLmDNP2vWrKCgoNDQ0Fq1amEesvjVq1c/ayM8PBxh7cnlpPhBgwbFxMTw0qKjo9kdfvTo0b179+bxISEhCxYsYGFebYBKduvWbeDAgQ0aNFi/fr2YqlYgLy8P5XTq1AlX9Pf3X7lyJSsETVizZk1wcHCzZs1YjEa64DakCwYg6kJwaMiGQ5tVUcCnZu1a0SP6qvHiB+eiBF6aZpvSmAYhAuzrTFUXHjx40KRJE9yc2YmYOS1atHj8+DErJCAgoIMAKwSTCoWfOHEC4ePHj0OnTp8+zU4fb4OFNeFyYnx2djY2CBcvXtSebBZYUVh9VKpUCbd6hI8dO1atWjW+IuDlnDt3Dnnu37+P8KlTp9gSQFQN8UKobatWrfghykeZe/fu1WxNgLikpqayJAbpgpuQLhiAqAuYmWnf7VInPD4VK1WMHR2nxosfnIsSBAv/ZUrHxcUdEGDxqi5g+4CJnZiYmGQDuoBDTDlWyLBhw3IEWCGYVLNnz/7nlTTtqaeeysjIYGFndAG89NJLbC2AqYh7O4/HAmT+/PkIvPXWW1gR8HheDhQBshUbG8srI6ZqigChLVxcAFYN8fHxmq0JYvkM0gU3IV0wAFEXQhyvF6pUrdL//8aq8eIH54Yo6wUn9xFpaWnVq1efWZyzZ89quvsITCF+6Ofnl56ezsJO6kJKSkrz5s0RaNeu3caNG3n8ihUrWrZsifs81il79uzh8eLMv3r1KmqI/Q52B+xbTEe6sGPHDiwQWJiBDQu2LZqtCYsXLxaTNNIFtyFdMABRF3pH9nb0fMEvwL/XgEh+OOHdNweOGZR8YKOYB+eiBMHCXdCF/Px83FTF1wT4C5Tm6QL2KU2bNl21atUzzzyDjQyPx76gZs2aixYt4k8cGeLMZ+CswYMHDxgwQEoVL/Ttt9+iad999x0/q0ePHhMnTtSUJjBIF9yEdMEARF2YO3fum3N/p4oCPu1ferFlSCt+yJ47fpazRcyDc1GCYOEu6IJme/KHxTzb8Ofm5gYFBV27dk2zFTJkyBBxM8IeBOjowtSpU3EWlAV3dU24nBQPli1bVqtWLXE/wsDOpUaNGgsXLhQjeTkFBQW45//000+ardP69u0rpmrKhSIiIl5++WX2GOKjjz5CyRALTWkCg3TBTUgXDEB6fyGsZw9VFPAZM2d8xUoVV2f8AeHl23/Z/Ae2DJTy4Fz+BIGByTNv3jwxhjFy5MiEhAQERowYkZiYyCIxbbDrrl+/PlbvEAU+yVFIs+LExcUhHn+TkpKeFKl17NgxKyuLhY8ePcq+EVi3bp0mXE6K12wvOFauXJk9ZRT58ssvsfiXXqzk5dy6dWvUqFG1a9du2LBhcHDwyZMnxVRNudCNGzfQNH8bqCfvJakJDNIFNyFdMADpfcdevXsv+GSRqgtbj6cFNA5o8GzD14a9Xr9BfejClMXTxAw4C+ca4pHh3r17cpRpvPPOO/369ZNjnQPbEFerKu5WHEG64CakCwYg/X8Ebrmdu3a2+/8Rv9+7LrRb+6rVq/k/02DM7PFiEvLjLH679gkuXbqETT42EdnZ2XJamUK64CakCwag/j/lnDlz+g2Mcen/KZEfZ0nleDm41Y8fP17nveaygnTBTUgXDEDVhUePHmHb3z9uAPYOqgpIH+RBTuQn/wtGQbrgJqQLBqDqgmaTBtz/u3Ttsix5haoF/INU5EFOEgUDIV1wE9IFA7CrC4ysrKxevXq9/MrLs+bP/mTX+i0526AF+IswYhCPVN96puATkC64CemCAejogmb7huLAgQNz586Niopq3759o0aN8BdhxCDekG8fCAnSBTchXTAAfV0gPA/pgpuQLhgA6YK3QbrgJqQLBkC64G2QLrgJ6YIBkC54G6QLbkK6YADQhc8++2wx4R1s3LiRdMFNSBcMgNYL3gbpgpuQLhgA6YK3QbrgJqQLBkC64G2QLrgJ6YIBkC54G6QLbkK6YACkC94G6YKbkC4YAOmCt0G64CakCwZAuuBtkC64CemCAdD7C14Fvb/gPqQLBkDrBW+DdMFNSBcMgHTB2yBdcBPSBQMgXfA2SBfchHTBAEgXvA3SBTchXTAA0gVvg3TBTUgXDIB0wdsgXXAT0gUDIF3wNkgX3IR0wQDs6sLp06d//vlnKfLatWvi702XjoULF966dQuBH3/8Mb840o9BguTk5P3790uRKgUFBRkZGShQjNy1a5f0Y5m+AumCm5AuGIBdXejevfuoUaOkyNdffz02NrZDhw7iT8WriBnYLzhzPv3006FDh7Jw//79q1Wr9pTApEmTtOKni7927QjU/9lnn42Li2vQoMH27dt5/JUrV4KDg9lPTvsWpAtuQrpgAHZ1ISkpCRP17t27PAY386pVq+7evTslJUX/t9t4BkzpCRMm8Ph79+4999xzZ86cYYfQhTfffJOncsTyS9SFx48f16pVKzMzE+FVq1ZBzsTUd999d8qUKWKMT0C64CakCwZgVxfu3LlTt27dDRs28JglS5a88MILhYWFuA+LW4xDhw7t2LHj0qVLPIZluHnz5m9snD9/HmHNtimIiIjg2Rzpgli+pAvQKWwroAK3b99mMagP6sl0JCEhQSxfs21VateuLaqbT0C64CakCwZgVxfA6NGje/fuzQ9DQkIWLFiAQGRkJO7DLLJfv37dunUbOHAg1vDr169nkSzD6tWrn7URHh6OMOKHDBkyf/78J+U51AWxfFEXcnJyAgMDo6KicNHGjRsfPHiQxU+bNg1ysGvXLkSyhYNIUFAQkqRIL4d0wU1IFwzAkS4cPny4UqVKuNsjfOzYsWrVqrFFAZ+3586dQ4b79+8jfOrUKf4ogWcYb4MX2LZtW3H/D13w9/cPEWA/cmlXFx48eNCkSROsWVj8ypUrW7RogU0Ewtu2batYsWL9+vVRYc22W7l27RrLBgYNGrRw4UJ+6BOQLrgJ6YIBONIFEBoayu7wb731FhYFLJLPWygCJmdsbCzu5MJJDnXhmWee2bdvHz+ELsTFxR0QYPF2dQHbhwoVKiQmJibZgC7gEGL0/vvvN23a9PPPP2/VqtXcuXORMzU1tV27dk8uok2YMOHtt9/mhz4B6YKbkC4YgI4urFixomXLlriNBwQE7Nmzh0WK8/bq1aszZ87EAr5Tp078K0xHuoBsX375JT90aR+RlpZWvXr1mcXJzc3FKoap0oULF5o3b449BfY+ixYt4qVhNzR9+nR+6BOQLrgJ6YIB6OgCtgY1a9bENGNPHFmkOG8ZWOQPHjx4wIABUgZJF9q3b79lyxZ+6JIu5OfnY4Egvj0Btfrmm28QeeXKFRaDLQ+kp1atWuJjUVxFp4HeCemCm5AuGID+tBk2bFiNGjXELTqftwUFBVilsxcEsIbv27evlGHq1KmYlpjAWFbgcOzYsbjJ83Jc0gUQHR0dHh5+8eJFhLFSCAoKunz5cpMmTYYOHYoAqrFgwQKsaxAfFhaG5QM76/nnn/e5t5tIF9yEdMEA9HUBK3+s1cU3EUeOHJmQkIDArVu3Ro0aVbt27YYNGwYHB588eVLKcPToUfaVxLp163C4c+fOF198kZcDTZk3bx4/5PDTwYgRIxITE1kYi5f4+Pj69euzyZ+eno5ILBl69uyJRU29evWwZjl79ixqFRMT88UXXyD1u+++e+aZZ9jjTB+CdMFNSBcMQF8XSuTx48f37t2TY+2BnUhISAj71sAdnLwcwHqEf4XhQ5AuuAnpggG4qQsusX//fmwN+KMKU8nLy+vWrZvzIuI9kC64CemCAXhSF8COHTv424qmkpOTU1BQIMf6AqQLbkK6YAAe1gWiREgX3IR0wQBIF7wN0gU3IV0wANIFb4N0wU1IFwyAdMHbIF1wE9IFA7CrC57014QyWYyrqG6afNdHkwjpgpuQLhiAXV3wjL+mGjVq+Pn51a1bt1KlSm3atFm1apWYWf9CH9hz0+S7PppESBfchHTBAOzqgof9Nd28eXPt2rUNGzYUxUjnQjpumt71TR9NIqQLbkK6YAB2daFM/DUdOXIEC4e9e/eyQ34hSNIdG1Al9k6UjpsmH/XRJEK64CakCwZgVxe0MvLXhMxjx45lYX4hLAfWrFmDDUKzZs14Th03Tb7oo0mEdMFNSBcMwJEueMBfk6oL8fHxffr0YWFRF6A+qampYk4dN02+6KNJhHTBTUgXDMCRLmjm+2tSdWH48OFYg7CwqAv86gx9N02+6KNJhHTBTUgXDEBHFzzsr6mwsBBCM2fOHHYo6sLixYt5NlxU302TL/poEiFdcBPSBQPQ0QUP+2uCDOFyZ8+eZYeiLmCq8GwlumnyRR9NIqQLbkK6YAD6U8hUf03M72tWVtb69etjYmJwoU2bNvEMjnSB+YbWcdPkiz6aREgX3IR0wQD0dcFUf03NbLRp06ZXr16QjHPnzvFUTSgH8pGUlCQm6bhp8lEfTSKkC25CumAA+rpQIp7316SPj/poEiFdcBPSBQNwUxdcwmx/Tb7ro0mEdMFNSBcMwJO6oJnsr8l3fTSJkC64CemCAXhYF4gSIV1wE9IFAyBd8DZIF9yEdMEASBe8DdIFNyFdMADSBW+DdMFNSBcMwK4ueMBfE+PRo0cHDx5MSUnJysrS/x4hOTl5//79cqwrcA9RHPG9DJMohVMp0gU3IV0wALu64AF/TSAzMzMwMLBx48aRkZFNmzZt2LDh5s2bhezFThd/q7J09O/fv2bNmn4CkydPljMVR6yA1HCpaXb5oFROpUgX3IR0wQDs6oIH/DUdO3YMs3TGjBkPHz5kMR9++GHlypXZT0tqyumG6EKJQiAiVUBsuJRkl1I7lSJdcBPSBQOwqwse8NeENQJ3tcAZPXp069atNZtnN+l0pguYbLm5uXl5eeJZ0C9sMTADxTcjVC9PjnSB5cSO5vDhw9hcsEi1ArzhUtKFCxfEnRHysN4otVMp0gU3IV0wALu6oJnsrwnzsEqVKhs3bmSHHKhMhQoVTp8+rZ4OXRgzZgyqERoaWqdOHUxydkpOTg42I1FRUagMtiQHDx5k8aqXJ0e6gJyzZs0KCgpCybjDY8IjUq0Ab7iUNGjQoJiYGF5adHQ0X0qUzqkU6YKbkC4YgCNdMNVfE/Jj/h85coSnMq5evYp43OE15XToArY2R48e1WyPRXFp1Ir9byX/h4iVK1e2aNECawrNnpcn6EJAQEAHAfbvVcjp7+9/4sQJhI8fP86ESVMqIAqimJSdnY0d1sWLF7Unuy1WlFZap1KkC25CumAAjnRBM9NfU0FBAaYfv7dzfvjhB8SzW6uqC6IXJtyBt27diu0D8icmJibZgC7gEKKj2fPyBF0YNmxYjgCLR87Zs2fzbFCfjIwMTamAI10AL730EltMYUpjEcEiS+1UinTBTUgXDEBHF8zz14QyMf3Yv1GLYEGBGyxbmKi6ID53xDJh8+bNaWlp1atXn1kc5tlF8vKk6e4jlgr+Hfz8/NLT0zWlAjq6kJKS0rx5cwQw7dnmyB2nUqQLbkK6YAA6umCqv6axY8dCdO7cucNjsP4PCwvjDyOd0YX8/HwsEMS3KrjnBWm2a2bqAmqOpcGqVauwJkJvaO45lSJdcBPSBQNwZJ0M8/w1IRJ30S5dumA3cffuXWzsX3311QYNGnA/btLpdnVBsz3nw9Kdbe9zc3ODgoLYHt6uLgwZMuSAAHsQ4EgXpAqIuiAlgWXLlmHa8/2IO06lSBfchHTBAPR1wTx/TZrtm7/4+Ph69erh1oqFycCBA8U7v3T6iBEjEhMTeSq0gM1eLGpQSP369dnEY5GaPS9P3EMUB3nUnB07dszKytKUCvB2qUma7VFo5cqV2WNaRqmdSpEuuAnpggHo60KJGOKvCbsJ9521OFkNk3jnnXe4h/sS0XcqRbrgJqQLBuCmLriE2f6ayoRLly5NnDgRm4js7Gw5zR4lOpUiXXAT0gUD8KQuaCb7ayoTMMPHjx+v/264SIlOpUgX3IR0wQA8rAtEiZAuuAnpggGQLngbpAtuQrpgAPxNG8JLgFLLg0S4AumCAWzbti0tLU22TaKMuHHjRkJCgjxIhCuQLhhDdnY2Vg2LfZxf//rXcpSvgR3E8uXLoQ7yCBGuQLpA/JM///nPrVq1wl85gbAepAvEP9m5c2ejRo3wV04grAfpAvFP4uPjR4wYgb9yAmE9SBeIX2CbiFu3btFWgvhf0gWCge0DWyngL20lCNIF4he4HHCBIKwM6QJR7JsI+laC+F/SBeJ/lTUCbSUI0gVCFgLaShCkC1ZH3TioMYTVIF2wOnZXB7SVsDikC1bHrgTYFQvCOpAuWBpHWwZH8YRFIF2wNDrrArvrCMIikC5YGp3JryMZRLmHdMG66G8W9FOJ8g3pgnUpcUWgs5ogyjekC9alxGlfonAQ5RXSBYuCDUJgYGCjkkAe2kpYENIFoggIgRxFWBLSBaII0gWCQbpAFEG6QDBIF4giSBcIBukCUQTpAsEgXSCKIF0gGKQLRBGkCwSDdIEognSBYJAuEEWQLhAM0gWiCNIFgkG6QBRBukAwSBeIIkgXCAbpAlEE6QLBIF0giiBdIBikC0QRpAsEg3SBKIJ0gWCQLhBFkC4QDNIFogjSBYJBukAUQbpAMEgXiCJIFwgG6QJRBOkCwSBdIIogXSAYpAtEEaQLBIN0gSiCdIFgkC4QRZAuEAzSBaII0gWCQbpAFEG6QDBIF4giSBcIBukCUQTpAsEgXSCKIF0gGKQLRBGkCwSDdIEognSBYJAuEEWQLhAM0gWiCNIFgkG6QBRBukAwSBeIIkgXCAbpAlEE6QLBIF0giiBdIBikC0QRpAsEg3SBKIJ0gWCQLhBFkC4QDEvrQnZ29qJFixYThD1gGzk5ObLRWAPr6kJ6enpaWppGEI6BhWzfvl02HQtgXV344IMPZCsgCAUsHGTTsQCkCwShx4cffiibjgUgXSAIPUgXrIUHdKGwsPDLfVm/mz65R0R4m5A2jRo1wt+XIsImTH1jZ2b6w8eP5BMI74N0wVqYrQt7MveGvdyjc48u4+a8kZD28YaDm9LP7MZfhBHTOaxL1/CuW9JTCrVC+UzCmyBdsBbm6cKjR4+mz5revlP7eUkLoAWOPkgN7dRuzORx9x/el4sgvAbSBWthki5AFIYMGxIZE7X1eKqqBdIHeSJj+kQPfP3BwwdyQYR3QLpgLUzShZmzZkb1/9WO/D+qKmD3g5yQhrFTxssFEd4B6YK1MEMXsrKyXuz8YsrXdlYK27/dOW7uG33ifjV80m8+y9kiJiE/NhTbdm2Xi3vC48eP8x1w/fp1ObfbJCcn79+/X461oZPE+fHHH1ndzp8///DhQznZ1yBdsBaG60JhYWFEr4j59p4pYFEQ0iW0whMaNGogScO8pAXdenZHCXKhNm7cuPHUE2rUqFG5cmV+uHz5cjl3SZQoJa+88sp7770nx9rQSeL0798fFWvWrFmjRo2qVq0aHR197tw5OZONDh06jB9f8kKpxAqbCumCtTBcFw4cOBDWM0wVBXwmzp8EOWjTMXjxpmXd+4QhHD2ir5Snc48uGVm75UIV3n333e7du8uxToNZPWHCBDm2ODqTXyeJA1148803WfjixYsRERFhYWHFs/yTlJSUr776So4tjjMVNhXSBWthuC7MnTt30juTVVHAp3X7IGjBirREhLFSqFSpUj2/elKe8XPeeHPaW3KhCnZ14e7du1jeZ2Zm3r59W4w/dOjQjh07Ll26xA5v3rz5GxtY4SPMIu/cubNv376jR48+evTP9ynY5EeZu3fvRry4ipF0we51RV0A6enpVapUefDglwerly9fvmMDJaPYK1eu/PzzzywbS0IdDh8+jD0Ii7RbYbsXlUrm8e5DumAtDNeFPn36JKR+rIpCat4XEIJadWrxmAHxA1/uG7Hl2HYxG87tEdFDLlRB1YWcnJzAwMCoqKh+/fo1btz44MGDLB6H3bp1GzhwYIMGDdavX4+Y1atXP2sjPDwcYcTs2bMnICCgV69ewcHBHTt2ZDMNk3/kyJGtW7eOjIxEgT179uQreVEXHF1X0oWVK1f6+/uzMGq+Zs0aXAu7DByifDSHJ82aNSsoKCg0NLRWrVrQAs1ehR1dVCrZQEgXrIXhutCuXbsNhzarurBmzydYLAS2DFSTxA/ObRPSVi5UQdIF3IebNGmyZMkSdohJ2KJFi8ePH2NLDzG6f/+XNyNOnTrFJ/Z4G/z0xYsXb9myRbM9HOnSpUtiYqJmm/yYyXl5eZrtjo25Onr0aJaf64Kj62o2XRg8eDAmMEQHmevUqTN//nyWDTWHVKWmprJDSRdw0RMnTiB8/Phx9Njp06e14hXWuahUsoGQLlgLw3WhyfNN0r7bpU74D7d9BCvHVkJNEj8497kmz8mFKki6gBU1Csd8TrKBqYJDCAEUAXMmNjYW81M4W9YF8NNPP2HtvXbtWqwLpk+frtkm/4wZM3iGjz/++JlnnmFhrguOrqvZdAF3eFQSy5Df/va3O3fu5EUhEusXfijpwuzZs3nSU089lZGRoRWvsM5FpZINhHTBWhiuC1gvfHqo2LcMoi60atdaTRI/WC+0dX29kJaWVr169ZnFOXv2LJKuXr2KMBbbnTp1+v7771l+SRcgBMgwatQo3NKxVp86daqmPETAxK5atSoL8ySd60r7CBHUHCsUfijpwtKlS3mSn59fenq6VrzCOheVSjYQ0gVrYbgu9OnT5/fpn6gT/vd710EXmjR/nsfM/2Th20umb8r9XMyWkPpxz1495UIVJF3Iz89H4Xzaa7YXLnlYs629saofMGAAOxSn2ZkzZ8Rzhw8fznVhypQpLBJg3c437VwXdK6rrwvi5HdVF3QuKp1uIKQL1sJwXZg7d+6sf52t6gI2CFWqVqles8bO/AwW83+aPQf7Tv63z8Rs4+e8MX32L8t4fdTnjtHR0bjVX7x4EeHc3NygoKBr164VFBRMmDABewTNVrG+ffuyzJj5mLeYTlhNnD9/vlKlSmyjsWvXrnr16o0bN06zTX6E9+zZgzA2+dhE8OWDuJSwe13NaF0QK6w5vijpgrGQLhjGgQMHXn7l5S/O7FGlIbhzCIRgwfrFCCcf2FixUkW/hn5Snq49uqEEuVCFhISEuLg4Meb69evx8fH169cPCAjAPGHT6datW9gd1K5du2HDhsHBwSdPnmSZjx49yp7wr1u3DofLly9/+umn/f39X3vtte3bt7OSY2NjP/nkk169euFcFIttP3u2B0aMGMGeTTq6LoAezZs3j4UlUH5SUhI/HDlyJJpjN6ljx45ZWVmaUmFHF5VONxDSBWthuC4UFhb27t37o09/eUlB+sxYPhu68OzzjSfOmxTUoQ3CsaPjxAzzkha8HPGym1+837t3T4rBfFYjJXBR9rWFiqN4iRIvYQYeuyjpgrUwXBc02/9HdO3adccJO99K9I7tU+EJzYJeSPm66OWFlK9TX+z8Irs9Et4G6YK1MEMXwJw5c+IGx31xWtYFfBZuWDJ61riZK+ak5n3BI3fk//HVAa+JX9ERXgXpgrUwSRcePXqETfigIYN2nij5X623Hk+Njn19+Ijh0pcIhPdAumAtTNIFzSYNWDV07dZ11Wdrdp3dq8oB+yz8ZHGnLp1mz5lNouDNkC5YC/N0gZGVldWrV69XIl75l/fmbsj4LOVwKjRiU/bWP3yxbtq86eEv90QqPVPwfkgXrIXZuqDZHvUfOHBg7ty5UVFR7du3b9SoEf4ijBjEu/ntA+EZSBeshQd0gSgHkC5YC9IFwhlIF6wF6QLhDKQL1oJ0gXAG0gVrAV347LPPFhOEYzZu3Ei6YC1ovUA4A+mCtSBdIJyBdMFakC4QzkC6YC1IFwhnIF2wFqQLhDOQLlgL0gXCGUgXrAXpAuEMpAvWgt5fIEqE3l+wHLReIJyBdMFakC4QzkC6YC1IFwhnIF2wFqQLhDOQLlgL0gXCGUgXrAXpAuEMpAvWgnSBcAbSBWuh6sLjx4/zHXD9+nUps/skJyfv379fjrWhk8T48ccfWcXOnz//8OFDOdmDLFy48NatW3Kst1JQUJCRkYHeEyN37dql88ugpAvWQtWFGzduPPWEGjVqVK5cmR8uX75cyqyPMzoi/ja0hE4So3///qhVs2bNGjVqVLVq1ejo6HPnzsmZbHTo0IH/TrwOzlRY5dNPPx06dKgc6xylu6I7YMSfffbZuLi4Bg0abN++ncdfuXIlODiY/fa3CumCtVB1QUT9OXnnwZSeMGGCHKugM/l1khjib8lfvHgxIiIiLCyseJZ/kpKS8tVXX8mxxXGywhL37t177rnnzpw5Iyc4Qemu6A5YDNaqVSszMxPhVatWSYOL4Z4yZYoYwyFdsBal0IW7d+9ieQ/bun37thh/6NChHTt2XLp0CeGbN2/+xgZW+AizDHfu3Nm3b9/Ro0fFn5Zikx9l7t69G0niz0mIumD3oqIugPT09CpVqjx48ADhy5cv37GBYlEmboY///wzy8aSUIfDhw9jD8Ii7VbY7kWlkrHZgR7xVM32Q1tff/01zlLXAvpdJJWsOaiA5qAn2enXrl07ePAg29Tg9OzsbHEJgGLr1q3LJDIhIUGqOXYWtWvXxlliJIN0wVq4qgs5OTmBgYFRUVH9+vVr3LgxTJDF47Bbt24DBw7E6nT9+vWrV69+1kZ4eDjCyLBnz56AgIBevXphsdqxY0du6Jj8I0eObN26dWRkJArs2bMnn05cFxxdVNKFlStX+vv7szCqvWbNGlwLuwwconC0hSfNmjUrKCgoNDQUN0/MTESqFXZ0UankIUOGzJ8/nyWBvLy8kJCQTp06xcTEoDKoEk8qsYukkh1VwFFP4vQxY8bg3Hbt2iFDVlYW2ti1a1dM9a1btz6phTZt2jTIwa5du1AmWziI4BQkSZEa6YLVcEkXcCtu0qTJkiVL2CGMvkWLFliaYldfqVKl+/fvI/LUqVNsYo+3wc9dvHjxli1bNNstq0uXLomJiSwekx/zB9NJs91CYZejR4/mSdAFRxfVbLowePBgzB9MFeSsU6cOn6KoNiZhamoqO5R0AVc8ceIEwsePH69QocLp06e14hXWuahUctu2bfkuHXfvVq1a8UKwHqlWrdrevXsRdqaLxJJ1KuCoJ3E6rs5KhprUrFkTCwqEly1bhl5lecC2bdsqVqxYv359VE+z7YOwxOCpgwYNWrhwIT/kkC5YC5d0AWtazCIYYpINGCsOYeUwd1htbGwspijPLBk9wIIWK+S1a9diUTB9+nQWick/Y8YMnufjjz9+5plneBJmu6OLajZdwP0WNcTN87e//e3OnTt5OYjEnZkfSrowe/ZsnvTUU09lZGRoxSusc1GpZNQWS3oWxqId2dg2gYFVQ3x8PALOdJFYsk4FNAc9idP5tguLAvQJC6N61atXZ+H333+/adOmn3/+ORRk7ty5iIEMYX3BUsGECRPefvttfsghXbAWLulCWloaLGxmcc6ePYukq1evIoylKZbQ33//vaYYPcwXqaNGjcItHSvnqVOnsnjp4SLmdtWqVcUknYtK+wgRVBv3VX4o6cLSpUt5kp+fX3p6ula8wjoXlUpGo7788ksW3rFjBxYIPEmzTbPo6GgWLrGLxJJ1KuCoJ8V2IXPfvn1Z+MCBA5UrV9ZsFUD1mDBduHChefPmkI/evXsvWrSI5QRYrHGhESFdsBYu6UJ+fj7uWsymGdKP02P1i4X9gAEDtOJGf+bMGfHE4cOHi7ogPgPHypntrlkSdEHnovq6IE5+V3VB56LS6e3bt2erevDtt9/irO+++46n9ujRY+LEifxQc9xFWvGSHVVApydL1IVvvvkG5165coXFnz9/HvpSq1Yt/kRWs3WpXZMgXbAWdo2Aoz53xN0P96iLFy8inJubi40rdqcFBQW4MbLn3lidMouEvcLIYM24TcEEsbtmd6pdu3bVq1dv3LhxrEBMfhzu2bMHYezzsSznywe+lLB7Uc1oXRArrDm+qHT62LFjMQn5YURExMsvv8w2+R999FGNGjUgFprtVSL9LtKUku1WQKcnS9QF9sxi6NChly9fRk0WLFgQEBCAYsPCwrB8YJmff/55u283kS5YC31dSEhIiIuLE2Ng8dgw169fn5kUm1G3bt3CsrZ27doNGzYMDg4+efIkIo8ePcqet69btw6Hy5cvf/rpp/39/V977bXt27fzYrHl/uSTT7AZxrkoFjt/9nQNjBgxgj1Us3tRzbZKnzdvHgtLoHxsy/nhyJEj0Ra7SR07dszKytKUCju6qHQ6Nj4vvvgiP7xx4wbO8reBkvkcc6aLpJIdVcBRT4qnY9k1ZswYFsZVWrZsycJYMvTs2bNmzZoQFCxbsDFBxWJiYr744gukYqUDXZbWgAzSBWuhrws63Lt3T4rBfFYjRQoLC9kDebvoJHH0yzcJ/YuiUSEhIezZvgh7jUKixC6yi3qKfk+WGiy++DcgEqQL1qLUukBw9u/fjy2P+EaWL5KXl9etWzdVgxikC9aCdMEQduzYIb2S6HPk5OQUFBTIsU8gXbAWpAuEM5AuWAvSBcIZSBesBekC4QykC9aCdIFwBtIFa2FXF06fPi2+A8e4du2a+Ppd6eB+jbirJc7ly5elzCX6a2KUwvsQ4SqkC9bCri5079591KhRUuTrr78eGxtbouMjMYPkgED0a9S/f/9q1apxT1Bg0qRJWvHTS/TLopXW+xDhKqQL1sKuLiQlJWGiiv45cDOvWrXq7t27S3R8xDNIzogkv0aOXmEWyy9RF0rtfYhwFdIFa2FXF+7cuVO3bt0NGzbwmCVLlrzwwguS4yOtuAMiBsugOiOS/Bo50gWxfEkXVOdFpfY+RLgK6YK1sKsLmu3/bXv37s0PQ0JCFixYoBX/ByTJARGLZBlUZ0SSXyNHuiCWL+qCI+dFpfM+RLgK6YK1cKQLhw8frlSpEu72CB87dqxatWpsUcDnrV0HRGIG6Z+IRb9Gmk0X/P39QwTYv+vY1QUd50Wl8z5EuArpgrVwpAsgNDSU3eHfeust7keIz1u7DojEDJIuiH6NNJsuxMXFHRBg8XZ1wZHzolJ7HyJchXTBWujowooVK1q2bInbeEBAAPOPoBWft6oDIjGDpAuiXyPNxX2EXedFubm5pfY+RLgK6YK10NEFbA1q1qyJacaeOLJIcd4yRAdEYgZJF0S/RpqLumDXeZE73ocIVyFdsBb602bYsGE1atQQt+h83tp1QCRmkJwRSX6NXNIFzZ7zosuXL5fa+xDhKqQL1kJfF7Dyx1pdfBOROz6y64BIzCA5I5L8GjlytSQ6VuL+mjQHzotK7X2IcBXSBWuhrwsl4rwDIkd+jVzFyctput6HCFchXbAWbuqCS3jSr5G+9yHCVUgXrIUndUHzoF8jfe9DhKuQLlgLD+sC4aOQLlgL0gXCGUgXrAXpAuEMpAvWgnSBcAbSBWthVxc86a8JZbIYV1HdNJGPJvMgXbAWdnXBM/6aatSo4efnV7du3UqVKrVp02bVqlViZv0LfWDPTRP5aDIP0gVrYVcXPOyv6ebNm2vXrm3YsKEoRjoX0nHT9C75aDIH0gVrYVcXysRf05EjR7Bw2Lt3LzvkF4Ik3bEBVWLvROm4aSIfTSZBumAt7OqCVkb+mpB57NixLMwvhOXAmjVrsEFo1qwZz6njpol8NJkB6YK1cKQLHvDXpOpCfHx8nz59WFjUBahPamqqmFPHTRP5aDID0gVr4UgXNPP9Nam6MHz4cKxBWFjUBX51hr6bJvLRZAakC9ZCRxc87K+psLAQQjNnzhx2KOrC4sWLeTZcVN9NE/loMgPSBWuhowse9tcEGcLlzp49yw5FXVi6dCnPVqKbJvLRZAakC9ZCfwqZ6q+J+X3Nyspav359TEwMLrRp0yaewZEuMN/QOm6ayEeTGZAuWAt9XTDVX1MzG23atOnVqxck49y5czxVE8qBfCQlJYlJOm6ayEeTSZAuWAt9XSgRz/tr0od8NJkE6YK1cFMXXMJsf03ko8k8SBeshSd1QTPZXxP5aDIP0gVr4WFdIHwU0gVrQbpAOAPpgrUgXSCcgXTBWpAuEM5AumAtSBcIZyBdsBZ2dcEDftwYjx49OnjwYEpKSlZWlv73i8nJyfv375djXYF7juOI72uZRLlxNke6YC3s6oIH/LiBzMzMwMDAxo0bR0ZGNm3atGHDhps3bxayFztd/A3b0tG/f/+aNWv6CUyePFnOVByxAlLDpabZ5YNy5GyOdMFa2NUFD/hxO3bsGGbpjBkzHj58yGJgeZUrV2Y/OasppxuiCyUKgYhUAbHhUpJdypmzOdIFa2FXFzzgxw1rBO6ChTN69OjWrVtrNo+P0ulMFzDZcnNz8/LyxLOgX9hiYAaKb0yp3t8c6QLLiR3N4cOHsblgkWoFeMOlpAsXLog7I+RhvVHOnM2RLlgLu7qgmezHDfOwSpUqGzduZIccqEyFChVOnz6tng5dGDNmDKoRGhpap04dTHJ2Sk5ODjYjUVFRqAy2JAcPHmTxqvc3R7qAnLNmzQoKCkLJuMNjwiNSrQBvuJQ0aNCgmJgYXlp0dDRfSpQnZ3OkC9bCkS6Y6scN+TH/jxw5wlMZV69eRTzu8JpyOnQBW5ujR49qtseiuDRqxf7nmv+j1MqVK1u0aIE1hWbP+xt0ISAgoIMA+7dL5PT39z9x4gTCx48fZ8KkKRUQBVFMys7Oxg7r4sWL2pPdFitKK1/O5kgXrIUjXdDM9ONWUFCA6cfv7ZwffvgB8ezWquqC6J0Nd+CtW7di+4D8iYmJSTagCziE6Gj2vL9BF4YNG5YjwOKRc/bs2Twb1CcjI0NTKuBIF8BLL73EFlNLly7FIoJFljNnc6QL1kJHF8zz44YyMf2YewURLChwg2ULE1UXxOeOWCZs3rw5LS2tevXqM4vDPD5J3t803X2E6PfFz88vPT1dUyqgowspKSnNmzdHANOebY7Kn7M50gVroaMLpvpxGzt2LETnzp07PAbr/7CwMP4w0hldyM/PxwJBfKuCe2SRZrtmpi6g5lgarFq1Cmsi9IZWHp3NkS5YC33rNM+PGyJxF+3SpQt2E3fv3sXG/tVXX23QoAH37yidblcXNNtzPizd2fY+Nzc3KCiI7eHt6sKQIUMOCLAHAY50QaqAqAtSEli2bBmmPd+PlD9nc6QL1kJfF8zz46bZvvmLj4+vV68ebq1YmAwcOFC880unjxgxIjExkadCC9jsxaIGhdSvX59NPBap2fP+xj3HcZBHzdmxY8esrCxNqQBvl5qk2R6FVq5cmT2mZZQzZ3OkC9ZCXxdKxBA/bthNuO/EyclqmMQ777zDf/miRHzR2RzpgrVwUxdcwmw/bmXCpUuXJk6ciE1Edna2nGYPH3U2R7pgLTypC5rJftzKBMzw8ePH678bLuKjzuZIF6yFh3WB8FFIF6wF6QLhDMuWLZNNxwJYVxf+8Ic/iN4BCEIFFrJ27VrZdCyAdXXhf/7nf2bPnu1D0oD9uQ/V1i6ov/TyuDeD2s6ZMwd2IpuOBbCuLoC//vWvWDV86AtMmjQpMDBw6dKlcoJPgfqjFWiLnOCVfPLJJ7AQ2WisgaV1wVfYvXt306ZNe/ToISf4IGgF2oIWyQmEN0G64O2kpKR06NBhxYoVo0aNktN8ELQCbUGL0C45jfAaSBe8mtWrV3fr1u2nn35KTExctGiRnOyDoBVoC1qEdqF1cjLhHZAueC8LFy6MiIi4c+cOwtiTp6amyjl8ELQCbUEA7ULr0EY5B+EFkC54I3/7299mzJjRt2/fx48fs5jXXnvtu+++K57LJ0Er0BYWRuvQRrQU7S2eiyhjSBe8jr/+9a/jxo0bNmzYf/7nf7KYf/zjHy1atNA0rXhGnwStQFvQInaINqKlaK9ln/x7J6QL3oXdeXLr1q0OHToIuXwbtAUt4oeqDhJlDumCF+FoXX348OFBgwaJMT4N2oIWiTHqvokoW0gXvAWd53Dr16//l3/5FznWZ0Fb0CI5tvhzVqJsIV3wCvS/t3M0kXwUHZnj38vKCYRnIV0oe/70pz/pv+ejLrx9Gv1tEXuPC30iJxAehHShjDl58mRoaKj+e8HSgzpfp8THqOgN9Al6Rk4gPAXpQlly//79tm3bsh+Ak9OeIH2xVw4o8WtXJKFP0DPoHzmN8AikC2XM7du3p02bhttjcnKy3e/wxReByg2OXtNCD6Af0BvoE/SMnEx4CtIFr+CHH34YOXJk9+7dd+3a9d///d9iEn9xuDyhvtaNVqPt6AH0A3pDTCI8D+mCF3Hs2LHIyMgmTZocOnSIR7J/NBJylQekfwNDe9FqtB09IOQiygzSBe9i6tSpo0aNEm+bOMzMzJTz+ThoEfu3cb5QwiHaLucjygjSBS/iT3/6U7t27f785z+L2+zOnTtfuHBBzurjoEVol/hgBa1G2+nrSS+BdMGL+PWvf71hwwZ+qNl+P75ly5Z2n0f6NGgR2sV+HZNHou3oASEXUWaQLngLhw8fDgsLUyXg0aNHUkz5QG0X2o4eKE9vcPkupAtewd///vfIyMjy9xzBVdAD6Af0hpxAeBbSBa8gLS0tJiZGjrUk6Af0hhxLeBbShbLnL3/5S6dOnfLy8uQES4J+QG+gT+QEwoOQLpQ9iYmJEyZMkGMtDHqj/L2y4VuQLpQx7F8krl69KidYGPQG/XNE2UK6UMbMnj37X//1X+VYy4M+Qc/IsYSnIF0oSy5cuBASElJYWCgnWB70CXqm/L3Q5SuQLpQlI0eOXLdunRxL2EDPoH/kWMIjkC6UGY5eZCIY9JpTGUK6UDb8/e9/7927d1ZWlpxACKB/0Ev0mpPnIV0oG1JSUgYOHCjHEgroJR3Pl4RJkC6UAf/xH//RoUOHs2fPygmEAnoJfYUekxMIMyFdKAOWLl06ZcoUOZZwAPoKPSbHEmZCuuBpbty40bZtW3Je6DzoK/QY+k1OIEyDdMHTvPnmmwkJCXIsoQt6DP0mxxKmQbrgUU6ePNmxY8f/+q//khMIXdBj6Df6RQmPQbrgOf7xj3/07dt3586dcgLhBOg39F55+h0Nb4Z0wXOkp6dHR0eTZZcO9Bt6D30oJxAmQLrgIf7yl7907tz522+/lRMIp0HvoQ/JNYMHIF3wECtXriQnC+6DPkRPyrGE0ZAueII7d+60bdv2+vXrcgLhIuhD9CT6U04gDIV0wRNMnTp18eLFcixRKtCT9As0ZkO6YDrff/99+/bt//3f/11OIEoFehL9iV6VEwjjIF0wnUGDBm3ZskWOJdwA/YlelWMJ4yBdMJevvvoqIiLib3/7m5xAuAH6E72KvpUTCIMgXTAR5lkkJydHTiDcBr1KXm3Mg3TBRJKTk+kHF80DfYselmMJIyBdMIvCwsLQ0FDyXGoe6Fv0MHnNNQPSBbN47733Zs2aJccShoIeRj/LsYTbkC6YAv0yimegX+UxCdIFU6BfUvMY9Ct+ZkC6YDx5eXkdO3akf+/xDOhn9Db96q+xkC4YD/1Su4dBb6PP5VjCDUgXDCYzMzMyMpJ+8sCToLfR5+h5OYEoLaQLRkI/kVRW0I93GQvpgpFs2LCBXmQqK9Dz6H85ligVpAuG8ec//7ldu3Z/+tOf5ATCI6Dn0f8YBTmBcB3SBcNYunQp+QUoW9D/9As0hkC6YAzMkTn9WkzZgv4nN/yGYF8XHj9+/OGHHy5ZsmQx4TQLFy6Uo8oCjBrGzpP/NeBV1uIlo+ArOLIW+7qwfPnyGzduaIRvgrHDCMqDahpkLT6NXWuxrwsQEvlswqdY7EF3kmQtvo5qLaQL5RN1pM2DrMXXUa2FdKF8oo60eZC1+DqqtZRGFx48epC6J23c2xNeeiUsKKRNo0aN2oS0De8VPnnGlH3/tq+wsFA+gfA46kibB1mLr6Nai2u68Kjw8Wc7N3UJ79o5rMu4OW8kpH284eCm9DO78RdhxHTu0aXHy+GZX2bKZxKeRR1p8yBr8XVUa3FBF27dux3/u9GhndrNS1qA0XX0QWr7Th1mzJr56NEjuQjCU6gjbR5kLb6Oai3O6gKG+dXY1yJj+mw9nqqOrvRBnqj+vxo6fBgNdlmhjrR5kLX4Oqq1OKULWBBC+zHMO/L/qI6r3Q9yvjrgtdmzZ4vlEB5DHWnzIGvxdVRrcUoXsEvEgjDla1n7t3+7c9zcN/rE/Wr4pN98lrNFSkX+Tl06ZWVliUX9+OOP+TbOnz//8OFDMckZkpOT9+/fL8d6HDdbYSCPHz/OyMg4c+aMFK+OtHmQtejjZisM5Jtvvtm+ffuRI0dgNmK8ai0l68KDRw+6hndTd4nQ+JAuoRWe0KBRA3Ww3/vD+7169xKfOffv3/+pp55q1qxZo0aNqlatGh0dfe7cOZ5ql+vXr/PwK6+88t577wmJZYPzrejQocP48ePlWAWxjU6Sl5c3efLkJk2aoPNXrVolpaojbR5kLfo43wrzrOXOnTuvvvpqgwYNevXqhWp069btp59+4qmqtZSsC6l70jr36CINIT4T50/CALfpGLx407LufcIQjh7RV80W/nL4gQMHeGnoozfffJOFL168GBERERYWxlNVMK4TJkzgh94z0k62IiUl5auvvpJjiyO10Ulwa50/f352dnbz5s29RxfIWlScb4V51vL222936dLl9u3bmk0jXnzxxbFjx/JU1VpK1oVxb08YP+cNdQhbtw/C6K5IS0QY2l+pUqV6fvXUbFPnTZ87dy4vTewjkJ6eXqVKlQcPHrBD1Hjfvn1Hjx5lj6Bu3rz5GxtYgCGsPRlprIJyc3Nxw+TlgMuXL+N0nHj48GGs2cQkqVgGy3/t2rWDBw/eunULMXfv3sU0E3WURWItmpmZyfqUodMKVizYvXs3bn1Xrlz5+eefWTa7NVTbqDm4qFQyj2/ZsqX36AJZizpwOq3wmLUsX75cFNxZs2Z17tyZH6rWUrIuvPTKSwmpH0vjl5r3BYa2Vp1aPGZA/MCX+0ZsObZdyvn79E/69OnDS5P6aOXKlf7+/iy8Z8+egIAArHOCg4PZ/yyvXr36WRvh4eEIa7aRHjNmTEhISGhoaJ06dVAaL6p79+5obVBQEJJq1aqFvnNULM+PorC6a9euHTLg9otzu3btWrt27a1bt7I8OTk5gYGBUVFR/fr1a9y4MWyCxeu0AsWuWbMG10LJOIyMjHz33Xd5klpDtY2OLiqVzPEqXSBrUQdOpxWetxbNpiMoc9y4cTxGtZaSdSEoOGjDoc3S+K3Z8wnkP7BloBSvfjZmb23fvj0vDX00ePBgNAYDAC3HaGExzJJw0S1btiAAecOaJzExEeHxNvjpGGls1aDlCJ8+fRrWduzYMZaEjkB3nzhxAuHjx4+jesjgqFiWv1WrVmyrhm6tWbMmK3bZsmUYDASg6Ni9L1myhOXHcLZo0YI9sNFpBYrF5i01NZUdSiNtt4ZiG3UuKpXM8SpdIGth+b3WWgoKCtCuDh06XL16lUeq1lKyLjzX5Lm073ZJ4/fhto9QUSwO1aGVP6d2P//887w09BHUDpWGJP/2t7/duXMnTwJYlWHZs3bt2p49e06fPl2zN9LYKfFDCCRXa5QpftEFg8jIyGBhtViWn28+p02bhvqwMNaQ1atXRwBrM7QRlpFkA52Ow1OnTmm6rUDkwIED+aE00nZrKLZR56JSyRyv0gWyFnXgdFrhYWuB5Pn5+U2ePPnevXtivGotJetCm5A26h2AjXSrdq3lcVU+247skO4A4ppKBGOAkRs1ahTUFMukqVOnavZGWnySBLHcvHkzC6Mjli5dypPQfmzkNAfFSvlnzpzZt29fFsY2rHLlygikpaVhyGcW5+zZs5puK1Cs2HvSSNutodhGnYtKJXO8ShfIWtSB02mFJ60FywpoLt9oiKjWUrIu9Ijooe4Yf793HUa6SfPnecz8Txa+vWT6ptzPpZyf7t6os2PknDlzBgV+//337HD48OGGjLSjYqX8M+2NdH5+vngu4A+iHLVCU6rh6kjrXFQ6neNVukDWwuI1L7OWbdu2ofkXLlzgMSKqtZSsC5NnTFGfMGOtWKVqleo1a+zMz2Ax/6fZc6hi8r99JuV8Z+H/03nCzDl//jy2f9iDIbxr16569eqx5yIYGJyC1rLtkKsj7ahYKb/dkQbR0dG4aVy8eBHh3Nxc7CSvXbumOW6FplTDmZGW2ujooj6hC2Qt6sA5aoWmVMMkayksLETbsSvJLA4vXLWWknVh37/t69KjqzR++AR3DsHQLli/GOHkAxsrVqro19BPypPx/ZcRERHiFyQTJkyYN28ePxRZvnz5008/7e/v/9prr23fvj0uLg6RR48eZQ9g161bh8MRI0bwR0EAPcI6CyA/tlg8qWPHjuzlObvFSvmxxBozZgwL44qYaSx8/fr1+Pj4+vXrBwQEoMf5tXRaIVVj5MiRCQkJdpN4DaU2OrqodDqnd+/emzZtkiLVkTYPshYWdjRwOq3wjLVARJrZ40nZdqylZF2A2IS/Eq6+wTZj+WyM9LPPN544b1JQhzYIx46Ok/IkbfoDrNb5/7FHzvv378uxbuN+sdJzGs/gzkXVkTYPshYJdwau1LhzUdVaStYFkPllZvtOHdQ33nvH9qnwhGZBL6R8Xezr6IyTmd26dZPeeCc8gzrS5kHW4uuo1uKULoAZs2ZG9f+V+h9yCzcsGT1r3MwVc1LzvhDjd5/9cvCQwXPmzJHKITyDOtLmQdbi66jW4qwuYIsydPiwVwe85sx/1O/O+2WYsbsT3yQlPIk60uZB1uLrqNbirC5otsGePXt2py6d3vvD++rosk/G919il4gFIbSfhrkMUUfaPMhafB3VWlzQBQZ2gL169erxcvjb7077/RefbDyU8sezmZ8fSf1s96Z3Fvy/iIgIpNIuscxRR9o8yFp8HdVaXNYFzfbA9sCBA3Pnzo2Kimrfvn2jRo3wF2HEIN7558mEeagjbR5kLb6Oai2l0QXC+1FH2jzIWnwd1VpIF8on6kibB1mLr6NaC+lC+UQdafMga/F1VGshXSifqCNtHmQtvo5qLQ514bPPPltM+CYbN25crIy0eSwma/Fl7FqLQ12QJYXwKdSRNg+yFl9HtRbShfKJOtLmQdbi66jWQrpQPlFH2jzIWnwd1VpIF8on6kibB1mLr6NaC+lC+UQdafMga/F1VGshXSifqCNtHmQtvo5qLaQL5RN1pM2DrMXXUa3FoS7QN9K+i91vpM1jMVmLL2PXWhzqgiwphE+hjrR5kLX4Oqq1kC6UT9SRNg+yFl9HtRbShfKJOtLmQdbi66jWQrpQPlFH2jzIWnwd1VpIF8on6kibB1mLr6NaC+lC+UQdafMga/F1VGshXSifqCNtHmQtvo5qLc7qwunTp3/++Wcp8tq1a+Jv6ZaahQsX3rp168cff8wvzuXLl6WcycnJ+/fvlyLtUlBQkJGRgTLFyF27dok/f1iOUUfaPMhafB3VWpzVhe7du48aNUqKfP3112NjYxHo0KGD+PviElLq9evXhUTt008/HTp0qGb72d9q1ao9JTBp0iSt+OnSLxQ74oMPPnj22Wfj4uIaNGiwfft2Hn/lypXg4OCffvpJyFs+UUfaPMhafB3VWpzVhaSkJHT93bt3eQzkuWrVqrt370Y4JSXlq6++KspdHDEV4zRhwgSedO/eveeee+7MmTOa458DF093ZqQfP35cq1Yt9jPeq1atgo2Kqe++++6UKVPEmHKJOtLmQdbi66jW4qwu3Llzp27duhs2bOAxS5YseeGFF5j/fyiruG48dOjQjh07Ll26xA556s2bN39j4/z58whrtpVeREQEy+ZopMXCpZGG5WGhiEG9ffs2j0SVUFVmHAkJCbx8BtaKtWvXFk22XKKOtHmQtfg6qrU4qwtg9OjRvXv35ochISELFixg4cjISCgrC/fr169bt24DBw7Eqmz9+vVi6urVq5+1ER4ejjBihgwZMn/+fHaio5EWCxdHOicnJzAwMCoqClds3LjxwYMH+SnTpk3DAGN/iHh2KxAJCgpCkhRZzlBH2jzIWnwd1Vpc0IXDhw9XqlQJ4o3wsWPHsLvjGs8H49y5c8hz//59hE+dOsU2h+JQjbfBwqBt27Z8R4eR9vf3DxFgv1lod6QfPHjQpEkT3IVY/MqVK1u0aIE1ITvctm1bxYoV69evjzprtvXntWvXWBIYNGjQwoUL+WG5RB1p8yBr8XVUa3FBF0BoaCgT7Lfeegsaz+P5YGCM0eOxsbGQZzVVU0b6mWee2bdvHwtjpOPi4g4IsHi7I40FYYUKFRITE5NsYKRxCNtC0vvvv9+0adPPP/+8VatWc+fORUxqamq7du1YCQBb1rfffpsflkvUkTYPshZfR7UW13RhxYoVLVu2hDAHBATs2bOHx4uDcfXq1ZkzZ2JJ1qlTJ/a9lM5II9uXX37Jwi6tDNPS0qpXrz6zOGfPnsXVcWtidnbhwoXmzZtjlYgF7aJFi3iBWOJOnz6dH5ZL1JE2D7IWX0e1Ftd0ASu9mjVrotf4MySGOBgMrNwGDx48YMAAKVUa6fbt22/ZsoWFXRrp/Px8SL74fThbRn7zzTeIv3LlCovEOhbGVKtWLfFBFy70wQcf8MNyiTrS5kHW4uuo1uKaLoBhw4bVqFFD2nHxwSgoKMC6i33li1VZ3759xVQwdepUdDRGBVKNw7Fjx0K5WZJLIw2io6PDw8MvXryIcG5ublBQELaFbCc5dOjQy5cvoxoLFizAzQpJYWFhuCGwE59//nm+7CyvqCNtHmQtvo5qLS7rAhZyWHpJ75aNHDkyISEBgVu3bo0aNap27doNGzYMDg4+efKkmAqOHj3KHjKvW7cOhzt37nzxxRdZEkxk3rx5LCwinj5ixAjsElkYt6P4+Pj69euzsUxPT2fxuAn07NkTd6p69erhLoTlImoVExPzxRdfIPW7777DNpXdLsox6kibB1mLr6Nai8u64AyPHz++d++eHGsPLC9DQkLYc+BS4+S1GLjJ8OfS5Rh1pM2DrMXXUa3FFF1wif3792O9J+4/zSMvL69bt24uWYaPoo60eZC1+DqqtZS9LoAdO3aIr6CZR05ODva0cmx5RB1p8yBr8XVUa/EKXSAMRx1p8yBr8XVUayFdKJ+oI20eZC2+jmotpAvlE3WkzYOsxddRrYV0oXyijrR5kLX4Oqq1OKsLnvTAgzJxKGdyAot73RFRR9o8yFp8HdVanNUFz3jgqVGjhp+fX926dStVqtSmTZtVq1aJOfWvQl53RNSRNg+yFl9HtRZndcHDHnhu3ry5du3ahg0biualcxXyuiOhjrR5kLX4Oqq1OKsLZeKB58iRI7gV7N27lx2KV4Gd3bEBUyu0QV53RNSRNg+yFl9HtRZndUErIw88yDl27FgWFq8CjV+zZg2WfM2aNWMx5HVHRB1p8yBr8XVUa3FBFzzggUcd6fj4+D59+rCwNNKwp9TUVJ6TvO6IqCNtHmQtvo5qLS7ogma+Bx51pIcPH45bCgtLIy1WgLzuSKgjbR5kLb6Oai2u6YKHPfBgHwi7mTNnDjuURppXkrzuqKgjbR5kLb6Oai2u6YKHPfDAsHC5s2fPskNppJcuXcrC5HVHRR1p8yBr8XVUa3FNFzSTPfAwT55ZWVnr16+PiYnBhTZt2sRSpXLEkSavOyrqSJsHWYuvo1qLy7pgqgeeZjbatGnTq1cvWMC5c+dYEkMsBzaRlJTEk8jrjoQ60uZB1uLrqNbisi44g4c98JSIRbzuiKgjbR5kLb6Oai2m6IJLmO2Bxzped0TUkTYPshZfR7WWstcFzWQPPNbxuiOijrR5kLX4Oqq1eIUuEIajjrR5kLX4Oqq1kC6UT9SRNg+yFl9HtRbShfKJOtLmQdbi66jWQrpQPlFH2jzIWnwd1Vqc1QUPeOBh4UePHh08eDAlJSUrK0v/sXBycvL+/fvlWFfgPn840jftZuAZN0HqSJsHWYt5lJW1OKsLHvDAAzIzMwMDAxs3bhwZGdm0adOGDRtu3rxZzKwJp4u/Plg6+vfvX7NmTT+ByZMny5kUxPrrN03FY26C1JE2D7IWHXzUWpzVBQ944Dl27Bj6fcaMGQ8fPmSpH374YeXKldlbaAzxdENG2pmhFZHqr9M0FU+6CVJH2jzIWhzhu9birC54wAMPVJ//8zxn9OjRrVu3ZmHpdDbS6L7c3Ny8vLzi52kwSqwb0a3id92S3x5HI82yYY16+PBhLBd5vFp/u007deqU6IkUGVhXeNJNkDrS5kHWUv6sxVld0Ez2wIOerVKlysaNG1khHBhNhQoVsF9VT8dIjxkzBtUIDQ2tU6cOho2flZOTgxVmVFQUKoN1JragLF7y2+NopJFt1qxZQUFBKBmajfFj8Wr97TatU6dOMTExvLTo6Gh+Z/CYmyB1pM2DrKX8WYsLumCqBx5kxogeOXKEJzGuXr2KeLb+1IqfjpHGYvXo0aOa7UEXrotaaU/+YY6/4r5y5coWLVrgRqEpfnsw0gEBAR0E2H/LIJu/v/+JEycQPn78ODc1Tam/3aZlZ2djzXzx4kXtyfqZFaV50E2QOtLmQdZS/qzFBV3QzPTAU1BQgA7lUs354YcfEM/FUhpp0akONHXr1q2a7RV6nJKYmJhkAyONQ1iSZhtCsdoY6WHDhuUIsHhkmz17Ns8Ge8rIyGBhZ0YavPTSS+z2uHTpUtwTWKQn3QSpI20eZC3lz1pc0wXzPPCgTHQo/8dYDu4PkEx+q5FGWnySBNVnj6PT0tKqV68+szjMXUd3wW+Pprsy5P+uD/z8/NLT01nYyZFOSUlp3rw5AhhIttz1sJsgdaTNg6yl/FmLa7pgqgeesWPHwoywdeSpWM6FhYWJj5ecGen8/HxIvvhVOf9femkIzRtp1Bxiv2rVKtzi0BWax90EqSNtHmQt5c9aXNMFzUwPPIiBLnbp0gXrw7t372Kr9uqrrzZo0IB75pJOdzTSmu3hDdZjbM+Wm5sbFBTENmbqSA8ZMuSAANva6Yy0VH+dpi1btgwDyVeYHnYTpI60eZC1lD9rcVkXzPPAo9m+yImPj69Xrx7EErca7O6kN+TE00eMGIFtIU/C0PLxwJ0K5dSvX5/1Jo+X/PZwnz8cZFCzdezYMSsri4Wl+us07fTp05UrV2YP3hiedBOkjrR5kLWUP2txWRecwX0PPFgfGuJ7w8lqmME777zDfZY7g7FugtSRNg+yFvfxNmsxRRdcwmwPPJ7n0qVLEydOxLIwOztbTnOA4W6C1JE2D7IWd/BOayl7XdBM9sDjeTBg48eP13nVVyXHaDdB6kibB1mLO3intXiFLhCGo460eZC1+DqqtZAulE/UkTYPshZfR7UW0oXyiTrS5kHW4uuo1mJfF5YvX37jxg35bMJHwNhhBOVBNQ2yFp/GrrXY14XCwsIPP/xwyZIliwlfA6OGscMIyoNqGmQtvosja7GvCwRBWBnSBYIgZEgXCIKQIV0gCEKGdIEgCJn/Dy5Y+3rNROGaAAAAAElFTkSuQmCC" /></p>

```cpp
    //  example/design_pattern/visitor.h 71

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

___

### Proxy <a id="SS_9_4_6"></a>
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

<!-- pu:deep/plant_uml/proxy.pu--><p><img src="data:image/png;base64,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" /></p>

なお、正確には下記のようなクラス構造をProxyパターンと呼ぶことが多いが、
ここでは単純さを優先した。

<!-- pu:deep/plant_uml/proxy_general.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAS4AAADNCAIAAACJhQqMAAAAKnRFWHRjb3B5bGVmdABHZW5lcmF0ZWQgYnkgaHR0cHM6Ly9wbGFudHVtbC5jb212zsofAAABF2lUWHRwbGFudHVtbAABAAAAeJyNkEtLw0AUhff3V9xlskiJqS0lCyk2KowJhqat62kyplMmM2UewaL+d8dHMAiCd3nOud99LI2l2rpOANSCGoOV2x9ZbfEF0FemKtUxe+CyDUJ4G0JrRsW/gqVWz+e/Il9m5E7R69UwF8boXxasBGfSy5q3BxuNjG/SoI8YAEsmm8/7SkGl3RY59kwbriReTJI4mU3i4JE1SKjEeIFxkk5n6XSOpNrghx1CcFfmaJTTNcOGG6v53lnfHwKhPcW1k5Z3LMWHE5Mkux8EvJE910p2fmUgu+InML+MrrnFimm/Ce4KyNgTdcL6jlo1/j0pbje30QJyKltHW88+Ulgpz9XnFEkJ73n5jC/u0+8pAAAsXklEQVR4Xu2dCVQUx9r3ozGK+xUUCAq4AwKyKaggDooa4oZoFK/6qSjGXVHUF6NGTSRxCRqNGyYKuCCIG4hEowFEyXXBPSGuiUFjXAD73HPvMcnN6/d36rVvU9UzDjPTMDPW78zhVFdVd1fXU/+qp7qGqTeeczgcE+ANOoLD4VQHXIocjknApcjhmARcihyOScClyOGYBFyKHI5JwKVofMrLy1euXBkfH7+coy+ovdWrVwuCQFeu5cKlaHxWrVpVUlIicAwDdZiQkEBXruXCpWh80KnTzYqjF59++ilduZYLl6Lx4VI0FlyKHIPgUjQWXIocgzCKFJ+UPUnLSp8wc2LXHt1cPdzs7e3dPDoEhQRNnzPj6DdHnz59Sp9giXApcgzCQCmWPy3fnpHcOci/U7fOE+a//1n651+dSN53ORN/EUZMp8DOgcGB2dnZ9JkWB5cixyAMkeKDx7+NnRbl6ddx0calkJ+mD1K9/Lxj58WWlZXRl7AguBQ5BqG3FKHDvuHv9BoQuuu7NFZ+1Ad5eg/sMyxyuAWrkUvRohap8RR4Fkyu6IdUjOV6SRF+KcZD6HDvxYOs8GQ/yNlnUN958+bR17IUuBQtbZEaz4Inoh9SMfSTYlJGCvzSnYUy4+GSxI8ip/x90uKpu8/spZKQ37ezX05ODn25l/z666+YVaalpV2/fp1Ok2Pr1q3Hjh2jY6sJLkU9G5MpgyeiH1Ix9Ki9J2Wl/kEBsvPDwVFD33iJc/uWu/+RTmX4cONHIT1DZN+pQlR2dnZeXl5BQUF169adPXs2nYOhR48eS5YsoWMFwcPDY/LkyXSszvzyyy90lA5wKerTmEwcE5di+uGMToGdWR2uTE2oUaNG5NSRO07v6f5uD6jx79NGsdkCg4OOHz9OX1QQ3N3dY2JiSLioqMjb27u4uLhCDgZNUkxJSdF7tMQFJ06cSMfqAJeiPo3JxDFxKUbPnBg9/31WY2GR/f5m8zcye9zy9VeQYovWjmy2mQtj4uLi6IsKgpWV1c6dO+lYQbhx48Zvv/0mHkKfT548IWEixYcPH2ZmZp46dUocbO/cuXP//n3xFGSAMuH6PnjwQIwEjx49OnHixP79++/evUti7t27N1IN7oKwNPMr4VJ8RWMyx9VnE5ciavKztM9ZjbV0aeXfs4t42OxtW6hxZ+EeKtv6jE2hoaH0RQUhPDy8VatWEBUVj8ht27aRcGlpKa4J1ZFDSHHUqFEuLi69evVycHDo3r078S2lo2VeXp6zs3Pv3r379++PPNAeicdF2rRpA1cWhWnUqBHpBdavX/+2GjjJCJOcOsKlqLExlem0+hyUfcTkVp9NXIro0b76NoWVYt369cJG9GPjqc/23J2YENIXFQQMffAM69SpA3kkJiaWl5eTeO1StLGxOX/+vKAe0FxdXceNG0fiiRQxfjo6OsbHx5P8a9asadu2La5cVlaGy0ZHR5P4gwcPDhkyhISj1ZBwpeBSlG9Mvz56MGbaOB1Xn+fMNa3VZxOXYgvHFulFB9jKrFGzRvi4CDae+mRcOOTk5ERf9CW3bt1asGBBgwYNMI4Ro2iX4pw5c8RzP//8czs7OxJPpAi/FPnXrl27UQ2kiMMLFy5gbETgp59+Es8V4VLUBV2lCB2a9eqziUvRTcOoWOutWgP/XzgbT3125afJjopSMNDVrVs3JSVFeJUUpa9tMjIy3nrrLWl8eno6htnYily5cmXv3r24vniiFC5FXdBJivBLMR5WdvW576B3TGf12cSlGKgKkp0rWtvahAzqJR5OXDh5cNSQrceTqGxfHtwuO1csLCyUHrZr1478a7ybmxsGNBJZUFBASXHGjBniKXBEoVsST6R48eJF5L969aqYh3S4kDriz507J8aLS9NcirqgkxQxP5Rdfd5zNmNC3PuhEX0ip47cnreDSkV+Pw2rz5ha5ObmYloPbwe9shiv3PqyiUtxRuxM2TeoXl192nm0Fw/Jaxu2qhcs+4B9g3rz5k04pZMmTSouLsakESLEaHbmzBkkDR8+PCQk5M6dO6dPn+7UqRPGPakUGzdunJWVhfClS5fgnRIFSkfLsLCwoKAgXF9QKxnzSfK+tGfPnv7+/teuXXv69CmkDp/58ePHiJ81a9bAgQOh2J9//plcQUe4FCs0pidlT2RXnzHueXT2fLHwrKapfVO2iSzZJLP6/O2336J7btq0adeuXR0cHN5++21ieKGivb29vfXrSgnUmrKJS/HoN8c6B/pTtYdP1PxoTBfXH9qE8Ko9L2Zlzu2cqTwHr2T3UPWQXVeETlQqVa1atWrUqOHi4pKamkrif/zxR8TDn/T09ETf17Fjx7Nnz5Kk8PDwzZs3Q6jNmjVr0qQJ/Brysqd79+7Lli0jeVC3Y8aMQaqtrS10uG/fPhKPYXD06NENGzaE5n19fXF3Eg+dk5eoiYmJJEZHuBQrNKa0rHTZ1edJi6eiZbj5ui9PXtEltBvCsu/6giquPsONQVeNbpIsZMHMH374IdrE5cuXhYpSxJj59ddfiydWCnZN2cSliN4qqEd3tr/b9V26rYNt07ebvTP83SZNm6CSZyyPofJ8kbwRw5GWNSRUMhmdKoX0FFzc0dExOTlZkv6CR48eUTEEPW4nC5dihcY0QcPqs4uXK1rG6vS1CGM8rFmzZmPrxmy2WYtmS32nfv36+fn5Ue3miy++IG/epFLUZU359u3bcL3g+eTn52MOQyJl15RNXIog+0i2t583OwvYcDjRM8DrrTq1beyaRs2LplIPnMsKCAiQnQUYiwsXLowYMQJjWmXdS8PhUqzQmLr26Mq+UUg7vx/aq9egnhgzaMzg4H6qHafp1ecN+zaLbxQgp9q1a2/YsEG8OIVUir169Vq4cCEJa1pT7tKly9y5c+EjwdGqV68e5CdoWFM2fSmC2HmxvQf20f3dWOaVnKHvDZ0/fz59IaOC+SRcDLGnq0q4FCs0Jld3V/Y9+xdZm2XnLewnKXeX+J6dvHw7evSoeHEKWSlqWlMW1FK0sbEhryK+++47XPzSpUuC3Cs7s5AihvfhkcP7DnpHlxWjg+cPQ4cYr0xnxcjocClWaEyyq88rUxPQ7uGjsk2E/lzIFFefr1y5grO0/BKErBQ1rSkLailK10saNWp06NAhwWylKKjViCfy6+y3ZNNHdE2+/By6mr0heSP8UoyHFqxDgUvxecXGJLv6TKTYvqML21CoT+rJveKoWFpaWr9+fS0tVVaKmtaUBbUUP/nkE/F0a2tr8jbPfKVIwNwvJCQkMDho5sKYDfs3J3278+CV7N35adszk+OWLOihUiFV0fmhicClWKExBaoC2bnihsOJkKJjGycxZvHmZTPjZycX7KZybstMkq4+jxkzBrM46Tf0nz59OmzYMDL9k5WipjVlwXKlKKir5fjx43FxcZghoy+zt7fHX4QRg3gt70stCS7FCo1p+pwZ7BtUuKy13qpVp65VxsVDJKZ5qxYQzNZvtlM5qdXnn376qU2bNt7e3keOHCkpKSksLBwwYICzszP7BlX62kbTmrImKbJrysaSIsqwefNmDO90ggSjSJEjcCk+r9iYjn5zVHb12b2TB7S39MvlCG89nlSjZg3rZtZUnkNXj6hUKmr1+c6dO1FRUU2avFgls7GxGTt27O3bt0nSiBEjMCck4VGjRn322WckrGlNOSIiQvwCF/D19SVuG7umbCwpAnQfbm5uGMmTk5PpNDVcisaCS7FCY1KvPgexq89zVs2Dlt52cpi0aKqrtxvC7P8QbEzepGX1+eHDh3TUq9C0pvxKjCjF52o1tm7dGk4j/n7wwQfPnj2TpnIpGgsuRboxZR/J9pJbfe4ZHvrGS1q5tqb+pfXQuWylV591x7hSfK5WY/v27eE2Q5DNmzcfPXo0JsAkiUvRWHApyjSmOXPlV5+XfRU/bu6E2NXz087vl8ZnXjlSBavPumN0KT5Xq9HDwwMOtr0a+MOhoaGIxL22b9++nGMYSUlJXIoyUiwrKxum8+pz5vkXOjSp1Wc8ERGM0WnZsiUJtGjRwsHBoU2bNtOmTaNvz9ELLkUZKQq6rj4fwfzQBFeflyswKp4+fZrosF27dl26dMEImZCQUFpaKlt7HD3gUpSXIkF+9fnki9XnBUs/UJnq6rPRpQgdOjk5QYTe3t546tTU1N9//50kaak9TqXgUnxFYzLH1WfjShE6dHZ2xoOPHDkyLy+PStVeexzd4VK0wMZkRCmSdcXY2NgbN27QaWosr/aqCy5FC2xMxpIi/7ZNVcKlaIGNyVhS1AXLq73qgkvRAhtTFUuRrysaDl9XfMFyy2pMMOryqpUi3RNw9IJL0QIbE5eiOcKlaIGNiUvRHOFStMDGxKVojnApWmBj4lI0R7gULbAxcSmaI1yKFtiYuBTNES5FC2xM1S7FGzduXFRz9erVX3/9lU7WCvJnZ2enpaVdv36dTlMY5TYUWrZsGZ7rwIEDsrt9ELgUXzQmvq6oN8vlpDhw4EArKytra+uGDRvWrFnTzc1t3bp1dCY5oAQ7OzsvL6+goKC6devOnj2bzmFspDv/UNstihi4udC2bduGDRsmqH/oyN3dXXaDVIFL8bmGxmTWmIIUJ0+eTML37t3bsmVLs2bNxo4dWzGXDGipMTExJFxUVAQNFBcXV8hhVKidfzRJ0ZDNhR49etSiRQuyYRFYuHChdEdHKVyK8o3JrDEpKRJOnjyJ4fHw4cNiTFlZWWFhIXxR6biEsRTtXjyUIptfeLmrz927d0+cOEGc4YcPH+bm5lKDD7sjELvzD5FieXl5QUHB+fPnxXOlmwvJbiJEwJVx33PnzuGCuA75LUw4vSqVSswD171+/fqyvznGpSjfmMwaE5QigM85fvx4EkZD9/Dw8PPzGzBggI2NzZo1a0h8eHh4q1atMjMz/3uaGk35BfXPw0ZFReGsjh072tra5uTkuLq6+vv7o8Xv2rWL5JHdEYjd+QdSxKVwI09PzwYNGuApyOnSX6mV3UQIZGVl2dvbo3g+Pj516tSJi4sj6n3vvfcWL15M8hBwLiaN0hgCl6J8YzJrTFOKY8aMIT+djiGlffv24uwLw0vt2rXJgIkBBx4jmjL0kJiYSPbt0ZJfUGsDqWSohNgwwySbCq9YsQKNXtC6IxD1w+qQYqNGjcjply5dwjB++vRpgZGi7CZCuCbZNezp06fBwcEfffQRyd+hQ4c9e/aQMGHIkCHiPqpSuBTlG5NZY5pSjIyMxKCEALw4tOBbt26JSRhMIFTxEEkLFizAuARpQYfa80Mb4gQP88yQkBASPnr0KCQtaN0RiJXizJkzxUOMn2RcpaQou4kQugDx7ShmxeJl7ezsqN3E0NdI7yLCpfiiMZnm72LoB57FBKWIUmHcIL9PuXfvXgxr0lS0zrCwMGmMoHZK0b5TUlK055fuXxAbG9uvXz8ShjDefPNNQeuOQKwUpa9tMJbi7gIjRdntEqZMmQL/GWH4utCn+ItH0PORI0fE/GDcuHGyb4a5FJ+fPHkyIyODrhizBc+CJ6IfUjF0lOLq1auhKyKAs2fPYlwqKioSUwMDAydNmoRAYWGhGAnatWuHE7XkF3SQopYdgYwoRYy6GKunTZsGmRUUFIgZvLy8duzYIR4K6sqB6qQxBC7FF6A2V1sEmBGlpaXRj6ckmqQYEREBMWBw+PLLL9FGrayspLvbq1QqTKjIBC8hIQGp0NvNmzfhlEJjxcXFmDTicTCakVmZbH5yqVdKUdC8IxC1848hUvT29oYHjmkh7iv1pcePH49SiYfAyclJdqGfS5FjELJShAPZSo2bmxsmb2iL33//vTRDSUkJJns2anx9fcWmCZ1AdbVq1apRo4aLi0tqaqr2/ELFXX3QE0VFRZHwqVOnMKiSsKYdgaidf6QbCgnqV74kp3RzIU2bCMGLhgeOjqBv375NmzYdPHgweTMEJ8XHx0fMj7Eds0fZX83lUuQYhKwUdefJkyd0lCCgET9+/JiOVSObX3f03hFIO9euXcNsVtwjDMrHgHzu3DlBPUn28PDIz88nSfDbxXe5FFyKHIMwUIqWAURYv359eNQ//PDD+fPn4fe2bNlSXMc/duwYXF9oEkkBAQGaugMuRY5BcCkSMHedPn36u+++O2jQoEWLFt25c0eaCvf1wYMHeXl5GD+l8VK4FDkGwaVoLLgUOQbBpWgsuBQ5BvHxxx9b0hckqgvUIZcixyAw/0lPT6dbljIUFhaK/21UBeBe1FcOlCMjI6OgoICuXMuFS1ER0IxWrly5QmEmTpzo7OwcHx9PJygG7oU74r50grGBk1/FX8yodrgUzZUtW7Y4OjqGhYXRCQqDO+K+uDudwDEMLkXz4z//+c/8+fN79uy5UA2drDDkprg7yoCS0MkcfeFSNDP++c9/jlCDQFRU1IEDB+gcCoM74r7SYtA5OHrBpWhO3L9/XzoceXt7l5SU0JkUBnfEfZ9LBmeUis7EqTxcimbD5cuXfXx8xEmaKImqR9oFoDwoFcpWMQun0nApmgc5OTkeHh74K8YQR1GSpeqgHGO2bBw94FI0A2RHnoULF27cuFEaU2XgvtTrImrE5ugBl6JJo2U+FhYWdubMGSqyasB92UUUah7LqSxciqaLlreUz549a926Nf5S8VWDprtrKTDnlXApmijaBxnZcakq0TQmaxnGOdrhUjRFXjn1YmdrVYz2mars5JajHS5Fk+Phw4fu7u6jR4/+448/6LSXVMvivhTt729RcpQfT4FnodM4GuBSNEVKSkrGjRvXrVu3b7/9lk5TUy2L+1K0rGqizCg5yl+9JTQ7uBRNF7FN37p1SxqvRQZVCdsdoJzaexCOFrgUTRp4esuWLXNwcFi1apXor2p3DqsMqZOMsqGEKCdKq8Wv5miBS9HUiY6OXrJkiXS00f7KpMoQXx2JozfKidLS+Ti6waVo0pw6dcrf35+s4IktPjg4WHYhoYpBGVASaR+BcqK0KDOdlaMDXIqmy59//qlSqaTf7YTvt3bt2vbt27PL61UPyoCSoDxSjxSlRZlRcklGjk5wKZouiYmJw4cPp2OfPy8rK6OjqgnZkqDMKDkdy3kVXIomyuPHj93d3W/evEknmDwoM0qO8tMJHK1wKZooMTExS5cupWPNBJQc5adjOVrhUjRFLly44O3tbb5fqkbJUX48BZ3A0QyXosnxv//7v2FhYXv37qUTzAqUH0+BZ6ETOBrgUjQ5du/ePWDAAHNvxCg/ngLPQidwNMClaFoIgtCxY8erV6/SCWYIngLPgieiEzhycCmaFgsXLpw3bx4da7bgWar3n7nMCC5FE6K4uNjT01N2sc5MwbPgifBcdAKHgUvRhIiIiEhKSqJjzRw8EZ6LjuUwcCmaCgcPHgwNDf3rr7/oBDMHT4TnwtPRCZyKcCmaBP/61798fX3Pnj1LJ1gEeC48HZ6RTuBI4FI0CeLj46dNm0bHWhB4OjwjHcuRwKVY/dy+fbtDhw6//fYbnWBB4OnwjHhSOoHzEi7F6mfkyJGbNm2iYy0OPCOelI7lvIRLsZo5evRo9+7dX4cfocAz4knxvHQCRw2XYnXy7NmzgICA/Px8OsFCwZPieU3h/55NEC7F6mTNmjXjx4+nYy0aPC+emo7lcClWI/fu3evQoQP+0gkWzev51LrApVhtYHxISEigY18D8NSvmy+gC1yK1cPJkydf21kTmSGjBuiE1xsuxWrgjz/+CA4Ofp3fJeLZUQOvw3tj3eFSrAY2bdr097//nY59zUANvA6rqbrDpVjVPHz4kH/v5PnL7xjxraZEuBSrGv5tTBGL/+ZtpeBSrFL4/yhIsez/R6ksXIpVB//PPRZL/S9NPeBSrDqSk5P5/7OzoE5QM3Ts6weXYhXBf+VFE5b3iz76waVYRfDfPtOChf3OnX5wKVYF/BdBtWNJv/6qN1yKisN/J1sXLOM30Q2BS1Fx+O4RumAZO4UYApeisvA9lXTH3PfPMhAuRWXhOw1WCrPeVdJAuBQVhO+/W1nMd69lw+FSVJDIyEi+K31lQY2h3ujY1wAuRaXIyclRqVR//vknncDRCmoM9YbaoxMsHS5FRXj27Jm/v/+pU6foBI4OoN5Qe6/bTxxwKSpCQkJCdHQ0HcvRGdTe6/bDP1yKxuff//63n58f/1EzQ0DtoQ5Rk3SC5VJtUiwvL1+5cmV8fPxyS2Tp0qV0lAKg9lavXl2V36erSqtVTR1WPZqsVm1SXLVqVUlJicAxDNRhVTpy3GpGQdZq1SZFdA90ATl68emnn9KVqxjcasaCtRqXotnDGlU5uNWMBWs1LkWzhzWqcnCrGQvWapYmxbLysvTDGdEzJ3bt0c3Vw83e3t7Nwy0wJGj6nBk5x75++vQpfYL5wxpVObRbDZWfcXjfxFnvd1V1cxMrXxU0dfa0nGM5Fln5esNazXKkCEun7NvZOci/U7fOE+a//1n651+dSN53ORN/EUZMp8DO3YIDD2cfps80c1ijKocWq+3cv9s/KEBr5XfLys6iT3tdYa1mIVJ89OTRuGnjPf06Ltq4FC1A0wepXn5es+fOKSsroy9htrBGVQ5Zqz0pfTJ+erSOlR8TG2NJla83rNUsQYrQ4TuDw3oNCN31XRrbAqgP8oQO6P3e8GEW0yBYoyoHa7XHpU/CBvfTvfJ7Deg9dPhQi6l8vWGtZvZSfCo8jZo+Hk1h78WDrO1lP8jZe2CfufPm0tcyT1ijKgdrtQkzoitb+aED+8TOi6Wu87rBWs3spYgpClyjnYV0l7znbMaEuPdDI/pETh25PW8HlYr8Pp18c3Jy6Mu95MaNGxfVFBcXl5aW0smmBGtU5aCslnYwXd/K96EqX6zwa9euPXr0SJpUWbZu3Xrs2DHx8Ndff83Ozk5LS7t+/boklzzUucrBWs28pVhWXubfPYCdoqDr9ejs+cZLmto3ZRvEhxuXqUJUml7rDRw4sFGjRq1atbK3t3/rrbfCwsK+//57OpNpwBpVOaRWQ9UFdO+iX+XjLKryxQp3cHCoXbt2nz59rl69KqZWih49eixZsoSEoSs7OzsvL6+goKC6devOnj27Yl4a6bkUHh4ekydPpmN145dffqFiWKuZtxQPHDnYKbAzZWZ8Ji2eikbg5uu+PHlFl9BuCIeN6Mdm6xYcePz4cfqiatAyxHq/efOmSqXq1q1bxSymAmtU5ZBaLevoYUMqv2v3btLKl1b4zz//3L9/f29vbzG1Ukjl5O7uHhMTQ8JFRUW4JtwcMSeLFimmpKToN2DighMnTqQiWauZtxTfj5kcPf991swuXq5oAavT1yKMLrlmzZqNrRuz2aZ9MCMuLo6+qBppywD79u2rVavWkydPEL59+/ZvajIzM0m/XlZWVlhYCC9I2vnduXMHTUo8xFklJSXwkeAviZH379+/deuWeKgfrFGVQ2q1KbOnGlL5k+OmSiufqvCsrCxc5OHDh+QQAcgANfzgwQMxD4AVjh49eurUKel7IKmcrKysdu7cKSaJwB/GueIh9EmMS87F7WBcXFY6bsOgsJd4qKlI8K5PnDixf//+u3fv4vDevXsj1eAWCIvZWKuZtxS79Qj8LO1zysZp5/fD/PUa1BNjBo0ZHNxPteP0HirnmvR1oaGh9EXVUC1jzZo1NjY2JNylS5cvvvgC3S28KRyeP38eroufn9+AAQOQBzlJth07djRu3Jj0wWfPnoX3VVBQMGTIEGR7eVUBfi/bX1YW1qjKIbVaoCrIkMrHudLKpyp86dKlLVu2JOG8vDxnZ+fevXtjqIT7ioZO4iFXW1vbkJAQ2MLX11eUhFSK4eHhMBN0RQ5FELlt2zYSLi0thewhPEF97qhRo1xcXHr16oV7de/eXexepZfVVCRcpE2bNmgPeDRYHL3A+vXr31YDDxlhkk2Qs5p5S9HNw+2rb1MoG3+RtRk169zOmYpnPziX/Gg3C1rG0KFDUeOwNwzQoEGDxYsXkyRIMSAgIC0tTVCPh+3bt4+OjiZJ+fn5mOccPvx/3yIYO3YsTAJL+/j4fPLJJ4jJzc3FzBMer6AeJxE+c+YMyaw3rFGVQ2o1N48ORqx8VDga66pVqyBC1HyHDh1OnjyJeAxWjo6O8fHxJBt6urZt25aXlyOMwqC/E9Sz1s6dO69du5bkkWoGQx86uzp16kAeiYmJ5ERBqxTRn6J7FdQDmqur67hx40g28bKaioTGgMuKjeHgwYPoeRGIVkMiRVirmbcUWzi2SC86QNl4ZWoCahZuEmt+6oNznZyc6IuqQctATwbVodMdPXp0RkaGmITIwYMHkzCkhXtJnUwMemPGjCFhtAPYsmvXrn369BFdHRyitSEAcaLxiSfqDWtU5ZBazfDKR4MWr4YKR4c1Y8aMnj17Nm/eHJ0aiYcTiAtCZhvVoN3j8MKFCyT1p59+woi3ZcsWDF/iKxl2vgcDLViwAP0pxjHiymqR4pw5c8QTP//8czs7OxIWL6upSBgbEUCRxNMJr4UUZTtm0hrad3RhzU99knJ3enl50RdVQ/lLUiBFsfB79+7FMChNRR8Mt1M8/PDDD1GY3bt3izFwWuDDCOpdIpKSksR4vWGNqhxSq3UwrPLZUVGscIyN1tbW5JV1eno6xrTYily5cgVJ0B6cQ7gecFjQqc2aNYuczkqRgLGubt26KSkpglYpSs9FFwzPhYTFJE1FQmPA9cVzRV4LKQapurPTlQ2HE1Gzjm2cxJjFm5fNjJ+dXLCbyrl5/1Yd54pSIEXibQrqSSDuVVRUJKYGBgZOmjSJhP/xj3+gSWEMRDcvvsKBJ4NZ0Lp169DdklcFBsIaVTmkVuseEmxI5a/P2KhlrtitWzfiely8eBEXlC5skGHt8uXL0vjIyEhZKRYWFpIAoV27duQ/6N3c3DCgkUjM4aVSxMgs5ocXSt4IkCRyWU1FgtQRf+7cOTGe/Jv1ayHFmLkx7Es8eD613qpVp65VxsVDJKZ5qxaoo63fbKdyzl/yPzq+QZUilSJQqVTBwcFkcp+QkGBlZQV9Ci+90xUrViA8fPhw6dsaRNarV2/evHlijCGwRlUOqdXmzI81pPJjP5yr5Q0q5ts4C3N1Qf1yC4MemWBDNqjVu3fvFhcX16xZk2Q4cOBA48aNJ0yYQM4VNYNT4JSiZ0RmmAMixGhGJuewCKYed+7cOX36dKdOnTD0iVLEpbKyXnxt/dKlS+guRVVLFS5bJIThXfv7+1+7dg3zEUgd05/Hjx+jj8DTQa7SN+qs1cxbit8c/6ZzoD9lY3zcO3nAkEu/XI7w1uNJNWrWsG5mTeU5cOVwD1UPTeuK8DMXLVpEx6qJiIgQO1RB3fNhcmijxtfXV7wgvKb+/fuTKSKEiomQ6KbCxm+++ab2BS7dYY2qHFKr4Un9gwL0q3x8gnsESyufrXB0XuPHjxfUtYcabtKkia2tLRr9vn37SAb4sX/7299Q7e+8886ePXtgFxI/YsQI8RUOdIK+slatWjVq1HBxcUlNTSXxP/74I+LhT3p6emLuB1eZdKDh4eGbN2+GSps1a4Y7orsU3/RgOrps2TIS1lQkNIbRo0c3bNgQmkdjwN0F9WtV8hI1MTGRZBPkrGbeUkRD764KZr/wMWfVPLSGt50cJi2a6urthnD4uAgqz9rt69CHafq2jR7o7m0uWLAAKqVj9YU1qnJIrYaqQ1+mX+Wv/mqNHpXPfiEOV8CwQ0WyQE66ZJNC5ceNHB0dk5OTpZGCXJEIr7wdazXzliI4knPEu5MP+zXInuGhb7yklWvrnYUV1rUyzhz0D/DX8h1Uhbh16xb8JXinubm5dJq+sEZVDspqqECfyld+2pn91VL5enPhwgWMtBjWpB6mgbBWM3spgrnz5vYZ1Jf954BlX8WPmzshdvX8tPP7pfEHLh8eMnTI/Pnz6QspDzpRzOC//vprOsEAWKMqB2s1uHB9B72je+Xvv5w1eGhEtVS+3mA+Cf/54sWLdIIBsFazBCliQhwZGfnOoDBd/mVu/7nMIe8NQSdnMf8yxxpVOVirvaj8EZFh4e/qUvkZZw9GDI2wpMrXG9ZqliBFQd0g0D37dfZbuvnF2wLZz8Erh9cnfQHXCF2yJTUF1qjKIWs1VCaq1K9zp4+2xLPVTj4HrhzG5NzyKl9vWKtZiBQJmH6EhIQEBQfNWjh74/4tybm7Dl7N3pWf9lVmUtySBT1UPZBqRlMUHWGNqhxarPay8rvHLJqzaX9icu5uyG9nftqXh7b/z5I4S618vWGtZlFSFNRvuo4fPx4XF9e7d28vLy97e3v8RRgxiK/sKzuzgDWqcmi32mtY+XrDWs3SpPgawhpVP27evLl58+bS0lI6QQK3mrFgrcalaPawRtWbwsJCNze3QYMGZWVl0WlquNWMBWs1LkWzhzWqIUCNrVu3hm/p6uq6atWqv/76S5rKrWYsWKtxKZo9rFENBGps165dx44dIUgnJ6cpU6aUl5eTJG41Y8FarTqluH379uUcw0hKSmKNajhQo7u7e2hoqL0aBweHgQMHFhcXL+dWMwayVqtOKdIdBUcvYFQiGKPj6OhIAnBZmzdv3rZt22nTptG35+gFl6IFwhrVcHJzc4kOvby8goODPT09ExISSktLudWMBWs1LkWzhzWqgUCHLVq08PDw6NSpU0hISGpq6u+//06SuNWMBWs1LkWzhzWqIZw8edLJyQnj4ciRI/Py8qhUbjVjwVqNS9HsYY2qN2RdMTY29saNG3SaGm41Y8FajUvR7GGNqh/82zZVCWs1LkWzhzWqcnCrGQvWatUpRb5CZTiyK1TKsZxbzRjIWq06pUh3FBy9YI2qHNxqxoK1Gpei2cMaVTm41YwFazUuRbOHNapycKsZC9ZqXIpmD2tU5eBWMxas1bgUzR7WqMrBrWYsWKtxKZo9rFGVg1vNWLBW41I0e1ijKge3mrFgrWZaUrxx48ZFNVevXpVulK0LyJ+dnZ2Wlnb9+nU6TWG2bt2q3y7tr2TZsmV4rgMHDmja20OQM6pycKvpgn5WMy0pDhw40MrKytraumHDhjVr1nRzc1u3bh2dSQ7UqZ2dnZeXV1BQUN26dcVdL5VD3BdaYDblE/H29mZ389Kdbdu2DRs2TFDvAu/u7s7uoUlgjaoc3GqvRG+rmZwUxZ297t27t2XLlmbNmo0dO7ZiLhnwzDExMSRcVFSE2jTWPk2ywIQTJ04UDzUZdefOnXr/Jv+jR49atGhx+fJlcrhw4ULpvn9SWKMqB7eadgyxmulKkXDy5El0tOLu9oL6t6gLCwvh1Uh7OPTKqEHxUIpsfnD79u3ffvvt7t27J06cIG7Vw4cPc3NzqW4Mkei8cfqDBw9IDFrbSDVoNwgLL41aXl5eUFBAtnEnoF+8f/8+CZPboTD5+fnU7gu4Mu577tw5XBDXIXukwH1SqVRiHjiB9evXR2H+e9pLWKMqB7eaiNGtZupSBPBeyD57gnpjVw8PDz8/vwEDBtjY2KxZs4bEh4eHt2rVKjMz87+nqdGUX1DvWBoVFYWzOnbsaGtrm5OT4+rq6u/vj7rbtWsXyZOXl+fs7Ny7d+/+/fs7ODjA/Ihcv3492S4PBUNYUBsVl8KNPD09GzRogKcgp/fq1Qv9oni7uXPn4hbIU69ePbQJEp+VlWVvb4/i+fj41KlTJy4ujrSD9957b/HixSQPAedi+iGNIbBGVQ5uNRKvhNXMQIpjxowhO0Wjc2rfvr3ox6Ojql27Nul60XXB90CloGYTExPJ9pRa8gvqWkYq6XRhNsxVyL6zK1asQPUJ6v0SHR0d4+PjSX40iLZt25IrU1s6w6iNGjUip1+6dAkDwunTpwXGqGhVZMvb77777o033kBOhHHNDRs2COqf1g4ODv7oo49I/g4dOuzZs4eECUOGDBG32pTCGlU5uNWUs5oZSDEyMpJsDAp/AHVx69YtMQndEkwuHiJpwYIF6OFgJFhUe37UsjhVwIwlJCSEhI8ePYrGIahfKuD0tWvXblQDo+LwwoULgpxRZ86cKR6iJyY9NGVU6Y7faASHDh1CAI1JfM+G+ZV4WTs7O5TkZfYXoNVK7yLCGlU5uNWUs5qpSxG9Dnogsh3f3r170UFKU/GcYWFh0hhB7d6gplJSUrTnRy1/8sknJBwbG9uvXz8SRhW/+eabCKSnp8O6sRW5cuWKIGdU6QsA9Mq4u8AYVbwdsLa2JrtGT5kyBZ4YwvCaYGlxgxe0jCNHjoj5wbhx42TfMbJGVQ5uNeWsZupSXL16NSxEqvLs2bPo4YqKisTUwMDASZMmIYApvhgJ2rVrhxO15Bd0MCqm6Tj96tWrJF5Q+04kYESjov9Grz9t2jQYjGzdTvDy8tqxY4d4KKgrB/aTxhBYoyoHt5pyVjM5KUZERKBa0c18+eWXeForKyvpBugqlQquOZkqJCQkIBWWu3nzJtwbWKu4uBjTD5gT/SLx72Xzk0u90qgAnTFm+bg+wqhxzEbu3r2L8KxZs1BU2Ji8NzPEqN7e3vDlMMHAfaVe2fjx41Eq8RA4OTnJLhmzRlUObjXlrGZaUoQr0kqNm5sbpgF4qu+//16aoaSkBNMGGzW+vr7iQ6LGYb9atWrVqFHDxcUlNTVVe36A1oO5BAljlh8VFUXCmMejeyZhtAac3qRJE1tbW1iUmIHkIa/jEhMTcThixAh0kyRJUL88JDlHjRr12WefkUjp7QAKQ7wa+GPw5dCk+vbt27Rp08GDB5N3DBkZGT4+PmJ+jBKYh4gdvBTWqMrBraac1UxLirrz5MkTOkoQUB2PHz+mY9XI5tedR48e0VHG4Nq1a5gX3b59mxyiDaFrP3funKCebnl4eOTn55MkeIDiW0EK1qjKwa0mKGY1c5WiZQBz1q9fH77ZDz/8cP78eXhQLVu2FFeEjx07BicK1kVSQECApobFGlU5uNUExazGpVjNYBY0ffr0d999d9CgQYsWLbpz5440FY7QgwcP8vLy0BNL46WwRlUObjWCElbjUjR7WKMqB7easWCtxqVo9rBGVQ5uNWPBWq3apPjxxx/Dn6YLyKkkqEPWqMrBrWYUZK1WbVKEJ52enk6XkVNJMjIyCgoK6MpVDG41oyBrtWqTIkCBVq5cuYKjL3AX09LS6GpVGG41A9FkteqUIofDEeFS5HBMAi5FDsck4FLkcEwCLkUOxyT4/1pXclhQ6QiVAAAAAElFTkSuQmCC" /></p>

[演習-Proxy](exercise_q.md#SS_22_9_20)  

___

### Active Object <a id="SS_9_4_7"></a>

Active Objectは、メソッドの呼び出しと実行を別のスレッドに分離するデザインパターンである。

通常のメソッド呼び出しでは、呼び出したスレッドがそのままメソッドを実行し、完了するまで戻らない。
Active Objectでは、呼び出しは要求としてキューに積まれ、直ちに戻る。
キューに積まれた要求は、オブジェクトが内包するワーカスレッドが1つずつ取り出して実行する。
実行結果は、呼び出し時に返されたfutureを通して受け取る。

<!-- pu:deep/plant_uml/active_object_seq.pu--><p><img src="data:image/png;base64,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" /></p>

<!-- pu:deep/plant_uml/active_object_class.pu--><p><img src="data:image/png;base64,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" /></p>

この構造により、以下の性質が得られる。

呼び出し側のスレッドは、処理の完了を待たずに次の処理を進められる。
実際の処理を行うServantはワーカスレッドからのみ呼び出されるため、Servant自身はロックを持つ必要がない。
複数のスレッドからの要求はキューによって直列化され、受け付け順に実行される。

これらを実現するコードを以下に示す。

```cpp
    //  example/design_pattern/active_object_ut.cpp 11

    class Servant {  // 実際の処理。ワーカスレッドからのみ呼ばれるため、ロックは不要
    public:
        int Add(int a, int b) { return a + b; }
    };

    class ActiveObject {
    public:
        // 全メンバの初期化後にworker_が構築され、その時点でワーカスレッドがdispatch()を開始する
        ActiveObject() : worker_{&ActiveObject::dispatch, this} {}
        ~ActiveObject();

        ActiveObject(ActiveObject const&)            = delete;  // worker_がthisを保持するため、
        ActiveObject& operator=(ActiveObject const&) = delete;  // コピーもムーブも禁止する

        // Proxyに相当する。Servant::Addの呼び出しを要求としてキューに積み、結果を待たずに戻る。
        // 引数は値でキャプチャする。要求の実行時には、呼び出し側の変数はすでに存在しない可能性があるためである。
        // thisのキャプチャが安全なのは、デストラクタがワーカスレッドの終了を待つためである。
        std::future<int> Add(int a, int b)
        {
            return enqueue([this, a, b] { return servant_.Add(a, b); });
        }

    private:
        template <typename F>
        auto enqueue(F func) -> std::future<decltype(func())>;
        void dispatch();  // Schedulerに相当する。ワーカスレッドのメイン関数

        Servant servant_{};  // ワーカスレッドからのみアクセスされる

        // 以下はクライアントスレッドとワーカスレッドで共有される。requests_とstop_はmtx_で保護する
        std::list<std::packaged_task<void()>> requests_{};   // Activation Listに相当する。未実行の要求
        bool                                  stop_{false};  // デストラクタからの終了要求
        std::mutex                            mtx_{};
        std::condition_variable cv_{};  // 要求の追加と終了要求をワーカスレッドに通知する

        // ワーカスレッドは構築と同時に他のメンバへアクセスし始める。
        // メンバは宣言順に初期化されるため、worker_は必ず最後に宣言する。
        std::thread worker_;
    };

    // func()をワーカスレッドで実行する要求を生成してキューに積み、結果を受け取るfutureを返す。
    //
    // std::packaged_task<R()>は、func()の戻り値、またはfunc()が送出した例外をfutureに格納する。
    // 戻り値型Rはメンバ関数ごとに異なるため、そのままでは1つのキューに積めない。
    // そこで、R()のtaskを呼び出すだけのラムダ式を作り、packaged_task<void()>に包んでキューに積む。
    // 外側のpackaged_task<void()>は、ムーブ専用のラムダ式を保持する入れ物として使うだけであり、
    // そのfuture(future<void>)は使用しない。
    // なお、std::function<void()>はコピー構築可能な関数オブジェクトしか保持できないため、
    // ムーブ専用のtaskをキャプチャしたラムダ式を保持できない。
    template <typename F>
    auto ActiveObject::enqueue(F func) -> std::future<decltype(func())>
    {
        using R = decltype(func());

        auto task   = std::packaged_task<R()>{std::move(func)};
        auto future = task.get_future();  // taskをムーブする前に取得する
        {
            std::lock_guard<std::mutex> lock{mtx_};
            requests_.emplace_back([task = std::move(task)]() mutable { task(); });
        }
        cv_.notify_one();  // ロック解放後に通知し、起床したワーカスレッドがすぐにロックを取れるようにする

        return future;
    }

    inline void ActiveObject::dispatch()
    {
        for (;;) {
            std::packaged_task<void()> request;
            {
                std::unique_lock<std::mutex> lock{mtx_};

                // 要求が来るか終了要求が出るまでウエイトする。
                cv_.wait(lock, [this] { return !requests_.empty() || stop_; });
                if (requests_.empty()) {  // 終了要求済みかつキューが空。残りの要求は実行済み
                    return;
                }
                request = std::move(requests_.front());
                requests_.pop_front();
            }
            request();  // 内側のtask()が実行され、結果がfutureに届く。ロックの外で実行する。実行中もクライアントスレッドは要求を追加できる
        }
    }

    inline ActiveObject::~ActiveObject()
    {
        {
            std::lock_guard<std::mutex> lock{mtx_};
            stop_ = true;  // dispatchのwaitのブロックから起こす
        }
        cv_.notify_one();
        worker_.join();  // 受け付け済みの要求をすべて実行し終えるまで待つ。この後にservant_等が破棄される
    }
```
```cpp
    //  example/design_pattern/active_object_ut.cpp 110

    ActiveObject ao{};

    std::future<int> future = ao.Add(1, 2);  // 直ちに戻る
    // この間、呼び出し側は他の処理を行える

    ASSERT_EQ(future.get(), 3);  // 結果が出るまでブロックする
```

___

## アーキテクチャパターン(システムレベルの構造) <a id="SS_9_5"></a>
### DI(dependency injection) <a id="SS_9_5_1"></a>
メンバ関数内でクラスDependedのオブジェクトを直接、生成する
(もしくは[Singleton](design_pattern.md#SS_9_3_1)オブジェクトや静的オブジェクト(std::coutやstd::cin等)に直接アクセスする)
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

<!-- pu:deep/plant_uml/di.pu--><p><img src="data:image/png;base64,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" /></p>

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


___

### MVC <a id="SS_9_5_2"></a>

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

<!-- pu:deep/plant_uml/mvc.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAjoAAAEYCAIAAADapss3AAApo0lEQVR4Xu3de3BU1R0H8LuLQB6EJBAoD1FJBR+joFMKM1AtxRl1NGlHU1tj7QjKwzpRpFL5w0GqNRJSrKklYBkmCyLDBsOjdnjEEAhxJOZBY4j5I8myE0KjIYHNc8k79Nc99dzNSTYuSXf3nrPfzx/O2XN/9+59nD3fXNzcaNcBAAAMTxM7AAAAjAdxBQAAEtDjqh8AAMBgEFcAACABxBUAAEgAcQUAABJAXAEAgAQQVwAAIAHEFQAASABxBQAAEkBcAQCABBBXAAAgAcQVAABIAHEFAAASQFwBAIAEEFcAACABxBUAAEgAcQUAABJAXAEAgAQQVwAAIAHEFQAASABxBQAAEkBcAQCABBBXAAAgAcQVAABIAHEFAAASQFwBAIAEEFcAACABxBUAAEgAcQUAABJAXAEAgAQQVwAAIAHEFQAASABxBQAAEkBcgWS++uqrxMTEGTNmaOAvdLbpnNOZFy8GgB8hrkAmx44di46OTk1NtdvtfMSCr9HZpnNOZ/7gwYNOp7Ozs7Onp6evr0+8PAC+xAck4gqMzuFwTJ06NScnh49V8Cc68zExMZWVlXQh2tvbu7q6kFjgT3woIq7A6NLT0xMSEvhABf+Li4vbtGlTbW1tY2NjW1tbd3e3eJEAfIaPQ8QVGF18fLzVauUDFfzPYrE88MADFRUVNTU1lFhOp7O3t1e8TgC+wcch4gqMLjY2tqqqig9U8D8KqunTpxcUFFDj0qVLzc3NuMECv+HjEHEFRhcREdHW1sYHKvhfS0tLaGjoiRMnioqKqqurGxoaOjo6xOsE4Bt8HCKuwOjMZnO/25AF/6PzbzKZjhw5kp+fX15eXldX53Q6xesE4Bt8HCKugkV3d7ekX+jSNH2UQqDQVcjKysrNzS0tLa2pqWltbRWvE4Bv6IOQt8QSMJjt27d//fXXYq/XaLqhLYi9A3377bf0s7PYG2iIKyOgq5CZmZmTk1NSUmK325uamsTrBOAb+iDkLbEEDMabvBmGN6uHh4d/b43/Ia6MgK6C1WrNzs4uLi622WwOh0O8TgC+oQ9C3hJLYHRo3v/yyy8//vjjPXv2fPPNN62trfRpP3LkiPs/+ldXV9PSo0ePdnV1ua9I/efOnfvoo4+ERe6orLKyMjc3l96Cpg/3fvebMP5ycFwJ7753716qeeaZZ6js8uXLvKyjo+P48eO083Tvpa/sR4grI6CrsH//foqroqIiGm9Xr14Vr1MgeBrt5NSpUxaLpaKigi/tN8BghhHQByFviSUwOvTxvummm/775DVNmzZt2rx581j7xz/+MfsS8NatW81mM+tctGgRjyV6effdd7N+93ptYN7Qy5kzZ7KacePG7du3j/cLZeyl0D/43W+99Vb2ktCUxMoot/ieT5w48ezZs3wLfqMhrgxAM2RcaR5G+8svv8wGrclk2rJlC1tqhMEMI6APQt4SS2B06CNx++23V1VV0Sec2nPnzq2pqaFbGWrTz3cUD88+++zy5cvpI/TJJ59Q56effspXjIiIYPdhdINFL0+cOMH6hU9mTExMXl5eU1PTqlWroqKirly5MmTZ4Ljy9O7CuuTFF1+cP3/+hQsXzp8/f/PNNy9ZssR9qX9oiCsD0Fxxxb/LbvC4mjBhQlJSksPh2LFjR0NDA1tqhMEMI6APQt4SS2B06JPz/vvvU6O3t5faf/nLX3j773//O7X7+vqOHTu2YcOGp59+mjrpc8VXfPvtt1mb7qt4/eBP5ubNm1m7trZWc6XgkGWD46rfw7sLNeS222574YUXtrs8/vjjdEPW2dnpXuAHGuLKADSp4mrp0qWzZs3at29fT08PX2qEwQwjoA9C3hJLYHTcP0hDtl955ZUxY8Y89NBDK1euHLJAeOmpn7S1tdFLuhUbpkzoH/LdhRoSFhamDURTlXuBH2iIKwPQpIor2j0a4aGhoYsWLbp27RpbaoTBDCOgD0LeEktgdNw/SEO2IyMj33jjDWrYbLYhC4SXg/tfffVV1mb/xlhQUNDv+kympKSwfrp/8rT6kO8u1JD58+fv3r2btenW0P0rGH6jIa4MQDNkXHka7ey2qaysTHN9/54VGGEwwwjog5C3xBIYHU8JxNt33333Pffck5qaSg2TyfTOO+8MLnZ/Obif1lq9evW77747bdq0hQsXst8CXrZsGb2kz/D69evDw8M9rT7ku1P9I4888tZbb/EnwmVkZNCPqGvXrt28efPixYtpyy0tLXwj/oG4MgJjxtWQoz0/P3/KlCnUk5SUpH33v377jTGYYQT0QchbYgmMzpAR5d6mm6G77rqLfjxcvnw5hURcXNzgYveXg/tprdmzZ0+YMOGxxx6rra1l/Xa7/eGHH6ZOWpScnDxx4sQhVx/y3d98803queOOO4QvB8+dOzckJGTRokVnzpzh/X6DuDICY8bVkKO9qamJfoyLjo6OjIxct26de33ABzOMgD4IeUssAWMT4kdhiCsjMGZcQTDQByFviSVgbIgr8CfEFQSKPgh5SywBY1uzZk2Q/GsG4soIvIwrh8ORmJgo9gKMgj4IeUssATCG4Ikr9ktCnl4GljdxlZubO2vWLKoUFwCMgj4IeUssATAGv8WV0+k8duxYRkbG0aNHR/MHIevr67/++mux1wua6/e1Pb0MrOHjqqOj47XXXuOP9XJfBDBK+iDkLbEEwBj8E1cUUVOnTmWzLZkwYYLFYhGLvBMeHj6ymJE0rsrKyviz+Bi3qwcwWvog5C2xBMAYNN/HVWlp6fjx4x999NHz58/TfVVJSckjjzyyZMkSh8NBS7u6uk6ePJmZmVlXV+e+FmWJzWb717/+tXfvXrot6+7ups6PP/5Ycz3Ynj2tjlfa7fbi4uK//e1vrGfIbQ4fV52dnZQWtArdvfHOwVv2kSHjqq+vb+vWrXTq3LNKQ1zB/5U+CHlLLAEwBs33cfXkk0/GxsZ2dHSIC65fv3LlyoIFC9gsTLdNhw4d4ou0Qc/O7+npcX+wPaUIr1y3bp3JZIqLixtmm5rnuKLkc3+aeEFBAa9x37LvaIPi6uLFi8uWLWO7JBAvIcAo6IOQt8QSAGPQfB9XkydPfv3118Vel5deeoni4YsvvqCMiY+Pp8rm5ma2SHM9O/8f//jHtWvX2F8Ly87OZv3CP+JRz/Tp0/Pz8+mmaphtCiu6v2RPE6cbqfLycvY0cV7jvmXf0QbG1c6dO6Oiong+CcRLCDAK+iDkLbEE+vtpHhE/iBAIfJT6yNixY9977z2x1+WWW25Zv349a9M0rbke6sNeUvtPf/oTa9N9Fb2kSZz1D46rNWvW8Jeetims6P6SPU18hwt7mjjLJ2HLvqPdSFxBQNB8JU5hStAHIW+JJeD6uV7sAr/TfB9XsbGxFAbuPf2up6Bed31vgidZe3s77QzdSLGXmod0EfpZz/bt2/lLT9v0tEEy+GniNpuN1bhv2Xc0/GOg4al65vVByFtiCah7+eWi+T6u/vCHP4wbN+78+fO8JzU1dc6cOf/+97/vu+++J554gnWyZ35/+eWX7KXmIV2E/sE9nrbpaYNk/vz5e/bsYe2+vj7+JY7B7+Uj2qC46sdXLQxG1TOvD0LeEktA3csvF833cdXS0nLPPfdERESsW7cuLS3tV7/6Fb1pfHw8LcrIyKD2ihUrkpOTp06dunjx4v7vPj+ah3RhD7Z/++23e3p6hqz0tE1PGyQWi4U9TTwlJYU9Tby1tXXwKr6jDRVXDL7IbhCqnnl9EPKWWALqXn65aL6PK9Lc3Pz73/9+1qxZdK9w5513btmyhX95gQIsNjY2Kirqqaee4rc11wdFBX/JH2xfUVExZOV1D9v0tEGG2vxp4vn5+UPW+I7mOa768WvCxqDqmdcHIW+JJaDu5ZeLf+IKhjd8XDF4CFNgqXrm9UHIW2IJqHv55YK4MgJv4qofj7gNKFXnK30Q8pZYAupefrkgrozAy7iCAFJ1vtIHIW+JJaDu5ZcL4soIEFfGp+p8pQ9C3hJLQN3LLxfElREgroxP1flKH4S8JZaAupdfLogrI0BcGZ+q85U+CHlLLAF1L79cEFdGgLgyPlXnK30Q8pZYAupefrkgrowAcWV8qs5X+iDkLbEE1L38ckFcGQHiyvhUna/0QchbYgmoe/nlgrgyAsSV8ak6X+mDkLfEElD38ssFcWUEiCvjU3W+0gchb4kloO7llwviyggQV8an6nylD0LeEktA3csvF8SVESCujE/V+UofhLwlloC6l18uiCsjQFwZn6rzlT4IeUssAXUvv1wQV0aAuDI+VecrfRDyllgC6l5+uSCujABxZXyqzlf6IOQtsQTUvfxyMZvN/W5DFvyvt7fXZDIhrgxO1fmKj0PE1XBUvfxyiYiIaGtr4wMV/K+xsTEkJITiKjs7m+LKZrMhrgxI1fmKj0PE1XBUvfxyiY2Nraqq4gMV/O/s2bMxMTGIK4NTdb7i4xBxNRxVL79c4uPjrVYrH6jgfykpKffeey9dBYqr4uJiiiuHwyFeJwg0VecrPg4RV8NR9fLLZdu2bQkJCXyggp/RJVi4cGFiYmJmZmZOTk5JSYndbm9qahKvEwSaqvMVH4qIq+GoevnlQj/IT5kyhSZKPlbBn9LT0yMiItLS0rKysnJzc0tLS2tqalpbW8XrBIGm6nzFhyLiajiqXn7pHD58OCoqKjk5ubq6mo9Y8Knu7u7CwsJVq1aFhYUlJSVZLJYjR47k5+eXl5fX1dU5nU7xIkGgqTpf8TGJuBqOqpdfOh0dHXl5eXFxcXSbpYG/REZGLliwYOPGjbt27XL/FntDQwNdEfEiQaDNmTNH7FIC4sorGuLKGOgn/ebm5kuXLlVUVBQUFNC8eejQoQMHDlit1v3gS3SG6TzT2aZzTmeezj9dBboWdEXEiwTgG4grryCuDKK3t9fpdDY2NtbU1NCMWVhYePr06ZycnGyXE+Ab7PTSeaazTeeczjydf7oKdC3oiogXCcA3EFdeQVwZB/0439bWRnNlbW1tZWVlWVnZuXPniouLi8CX6AzTeaazTeeczjydf7oKuLUCf0JceQVxZRx9fX1dXV3t7e0Oh6O+vp6mTrvdbnOpBt9gp5fOM51tOud05un801WgayFeHgCfQVx5BXFlKDRL9vT0dHZ2Op1O+hm/ubmZJtCr4Et0huk809mmc05nns4/sgr8DHHlFcQVAEBgIa6GNm/ePPcv8rqjRWI1AAD4GOJqaCkpKWJMfYcWidUAAOBjiKuhXbx40Ww2i0mladRJi8RqAADwMcSVR0uXLhXDStOoU6wDAADfQ1x5tHPnTjGsNI06xToAAPA9xJVHDodj/Pjx7llFL/HXfQAAAgJxNZwnn3zSPa7opVgBAAB+gbgaTlZWlntc0UuxAgAgQL766qvExMQZM2a4T1NDohqqpHpxE1JBXA2no6MjOjqaXW9q4G8lAIBBHDt2jCal1NRUu93OZ29PqIYqqf7gwYPyPpeEHw7iamgrV65kcUUNcRkAQCA4HI6pU6fe6F/WpvqYmJjKykpJn/rIDwRxNbRTp06xuKKGuAwAIBDS09MTEhL4pO29uLi4TZs2SfpMfX4UiKuh0U8fs1zk+jEEABQWHx9vtVr5pO09i8XywAMPSPoXy/hRIK482uAi9gIABEhsbGxVVRWftL1HQTV9+nRJ/x40PwrElUdlLmIvAECAREREtLW18Unbey0tLaGhoSdOnCgqKqqurm5oaJDoG2T8KBBXAAByGDNmTG9vL5+0vUf3Umaz+ciRI/n5+eXl5XV1dU6nU9y6UfGjQFwBAMhhxHdXjY2NISEhWVlZubm5paWlNTU1ra2t4taNih8F4goAQA4j/n9XZ8+ejYmJOXDgQE5Ozrlz5+x2e3Nzs7h1o+JHgbgCAJDDiL8ZmJKSMm/evMzMzM8++6ykpOTChQtNTU3i1o2KHwXiCgBADtu2bRvB713RigsXLkxMTMTdFQAA+IPD4ZgyZcqNPtUiPT09IiIiLS0N/+8KAAD85PDhw1FRUcnJydXV1Xz2HlJ3d3dhYeGqVavCwsKSkpIsFgu+Geg/3j+HWEZqPDsZAHyqo6MjLy8vLi6ObrPESWSQyMjIBQsWbNy4cdeuXfv378fvXfnJDT2HWEZ2JZ6dDAA+RfdMzc3Nly5dqqioKCgooAQ6dOjQgQMHrFYr5dP+QaifllINVeKpFv4wsucQy0j2ZycDgE/19vbSj7ONjY01NTWUPYWFhadPn6Z5Izs7m+LqxEDZLrSUaqgSzwz0hxE/h1hGUj87GQB8jeYEmhlofqBZgn60LSsrO3fuXHFxMcVV0SDUT0uphiolnVX43ChHXI34tw1kJPWzkwHA1/r6+rq6utrb2x0OR319PYWQ3W632WwUV9UD2VxoKdVQpaT/ZsPnRjniasS/yy0jqZ+dDAB+QHnT09PT2dlJP87S3RLNEhRFFFdXB6F+Wko18v4fcT43yhFXI35SloykfnYyAAQKxZXYpQQ+N8oRV2azud9tp9VGR2oymST9DQkACBTElSHQZeD7GQzoeCX9/XMACBTElSEEYVxlZmbm5OSUlJTY7XaJHkYJAIGCuDKEIIwrq9WanZ1dXFxss9kcDod4RgAABkJcGUIQxtX+/fsproqKiiiurl69Kp4RAICBEFeGgLgSzwgAwECIK0MIzrji32VHXAHA90JcGQLiSjwjACCnOXPmaLKhfRYPw4/0iZG3xBIj0RBXAADD0nB3ZQSIK/GMAAAMhLgyBMSVeEYAAAZCXBkC4ko8IwAAAyGuDAFxJZ4RAICBEFeGgLgSzwgAwECIK0NAXIlnBABgIMSVIRgqrjZs2PDll1+KvW56enr6R/fnThBXAHCjEFeGMMq42rFjx86dO/sHRsjnn39O/RUVFe6d3qCdoRXFXjffW/C9EFcAcKNGH1e/+MUvjh8/7k2nP+kTI2+JJUYyyrjSXHJycngPbfP2228fWa5871rfW/C9EFcAcKNGH1e0he3bt3vT6U/6xMhbYomRjD6uJk6c+Mtf/pL3UHSNGTNm2rRp7rnS1dV18uTJzMzMuro63sk4nc5//vOftOjbb791T6POzk4KFeqvr6/nxYgrAPA/P8TVqVOnLBZLRUWFe0FHRwfdflmtVpoeWQ/VX7hwgaavDz74wL1yZPSJkbfEEiMZfVz97Gc/Gzt2LA+Vp556aunSpTNmzOC5cuXKlQULFmgu4eHhhw4d4qt/8803c+fOZYso9ngaNTQ0zJs3j/cXFBSwel4wYhriCgBukObjuHr55ZfZdGcymbZs2cKWXr582X0aPHv2LFtl3bp1VBYXF+e+qZHRJ0beEkuMRBt1XKWmplJcvfvuu/SSzu+4ceMo9kNDQ3muvPTSS3Suv/jiC8qt+Pj4yZMnNzc3s0UrVqyYNGlSSUlJU1PT2rVreRq9+OKL8+fPt9vt5eXlN99885IlS/jbIa4AwM80H8fVhAkTkpKSHA4HzW/0wzpbyqZBupc6f/48mwbZKtOnTz9z5kxnZ6f7pkZGnxh5SywxktHH1YcffpiQkDB79mzaWkpKCsVVY2Oje67ccsst69evZ21KCFpEacFezpo1a8OGDazd3d3N17rtttteeOGFHS6PP/642Wzu6uq6jrgCgEDwdVwtXbqUJsN9+/axLz8zbBrc7sKmQYooWmXNmjX6JkZHnxh5SywxktHHFeXHZ599Ro3PP//8zjvvTExM5P2sJjw8/L333mPt9vZ2WrR3797Bi667rRUWFqYNZLPZ3AtGTENcAcAN0kYdVxQ2aWlp7j0se9g3q2kieuWVV0JDQxctWnTt2jVWMHgaZD/up6enu29nNPSJkbfEEiPR/h9xRduJjY195pln6GVeXh7vZzX33XffE088wdrHjh2jRfyXq+6///74+HjWLikp4WvRLfCePXtYf19fH90ds7b7ZkdGQ1wBwA3SRh1Xc+bMefTRR2k24z0HDx6kzebm5va7oov+W1ZWRj2ZmZmsgKbB3bt3s3Zvb+/ly5f7PdyljZg+MfKWWGIk/5e4osbmzZvHjBlzxx13CP0kIyODXq5YsSI5OXnq1KmLFy/u/+40USbRoueee+6Pf/zjpEmT+FoWi4V+0Fi7dm1KSgrVT5s2rbW1VdjsyCCuAOBGjT6u2DRIP6Bv2rTpz3/+87PPPnvTTTf95Cc/oQDLz8+fMmXK+vXrk5KSNNf/K+GrsGmQZlc2Dba0tCCuRo7nR319fUhIyPvvvy/0M3QXTLdfUVFRTz31FL9VYlJTU2fOnElZ9fzzz0dGRvK1qDF37lzaJt0d0+VknYgrAPC/0ccVOXz48IMPPhgRETF27Ngf/vCHGzZsoJ/Cqb+pqWn16tXR0dE0Aa5bt859FUomPg2eOXOmH3dXfD9H4Pjx47W1tWKv5/6AQ1wBwI36v8SVAekTI2+JJUYyyriSDuIKAG4U4soQEFfiGQEAGAhxZQiIK/GMAAAMhLgyBMSVeEYAAAZCXBkC4ko8IwAAAyGuDAFxJZ4RAICBEFeGgLgSzwgAwECIK0NAXIlnBABgIMSVISCuxDMCACqaPHmyNlImk0ns8hq9r7grhqFPjLwllhiJhrgCgCCgBegOKVDv6w19YuQtscRIEFfiGQEAFQUqNgL1vt7QJ0beEkuMBHElnhEAUFGgYiNQ7+sNfWLkLbHESBBX4hkBABUFKjYC9b7e0CdG3hJLjARxJZ4RAFBRoGIjUO/rDX1i5C2xxEgQV+IZAQAVBSo2AvW+3tAnRt4SS4zEbDb3u+202np7e00mE+IKIAgFKjYC9b7e4HOjHHEVERHR1tbGd1VtjY2NISEhFFfZ2dkUVzabDXEFECQCFRuBel9v8LlRjriKjY2tqqriu6q2s2fPxsTEIK4AglCgYiNQ7+sNPjfKEVfx8fFWq5XvqtpSUlLuvfdeOl6Kq+LiYoorh8MhnhEAUFGgYiNQ7+sNPjfKEVfbtm1LSEjgu6owOtiFCxcmJiZmZmbm5OSUlJTY7fampibxjACAigIVG4F6X2/w6VGOuKLbiylTptD0zfdWVenp6REREWlpaVlZWbm5uaWlpTU1Na2treIZAQAVBSo2AvW+3uDToxxxRQ4fPhwVFZWcnFxdXc33WRnd3d2FhYWrVq0KCwtLSkqyWCxHjhzJz88vLy+vq6tzOp3i6QAAFQUqNgL1vt7g86Q0cdXR0ZGXlxcXF0e3WZqKIiMjFyxYsHHjxl27drl/i72hoYGOXTwdAKCiOXPmiF1+Eaj39YZ8cUX3H83NzZcuXaqoqCgoKKDZ/NChQwcOHLBarft9RnP9uq7f0LHQEdFx0dHRMdKR0vHSUdOxi6cDACA4yBdXvb29TqezsbGxpqaG5vHCwsLTp0/n5ORku5zwDYorsctn2IHQEdFx0dHRMdKR0vHSUdOxi6cDACA4yBdX/a4brLa2NprBa2trKysry8rKzp07V1xcXOQzFFdily/RsdAR0XHR0dEx0pHS8eLWCgCCmZRx1dfX19XV1d7e7nA46uvraUK32+02l2rfoLgSu3yGHQgdER0XHR0dIx0pHS8dtXgiAACChpRx1e9KrJ6ens7OTqfTSXcezc3NNK1f9RmKK7HLl+hY6IjouOjo6BjpSJFVABDkZI0rP9MM/OVOAIBggLjyCuIKAKRQ5iL2KgFx5RXEFQBIYYOL2KsExJVXEFcAYHx9fX2zXJT8v92IK68grgDA+E6dOsUejkMNcZn8EFdeQVwBgPGtXLmSxRU1xGXyQ1x5BXEFAAbX0dERHR3N4ooa6j1iFHHlFcQVABhcVlYWyyqGXooVkkNceQVxFQy++uqrxMTEGTNmuH/mJUJ7TvtPRyEeGASHJ5980n080EuxQnKIK69oiCvVHTt2LDo6OjU11W6388+CXGjPaf/pKA4ePIjnoQQbh8Mxfvx497iil9Qp1smMD3XE1XAQV2qjT/XUqVPV+CvVdBQxMTGVlZV42mRQ2blzp3tWMdQp1smMD3LE1XA0xJXS0tPTExIS+EdAdnFxcZs2bcKz/IPK0qVLxbDSNOoU62TGRzjiajga4kpp8fHxVquVfwRkZ7FYHnjgAfyltOBx8eJFs9kshpWmUSctEqulxUc44mo4GuJKabGxsVVVVfwjIDsKqunTp+PvUAePlJQUMam+Q4vEamnxEY64Go6GuFJaREREW1sb/wjIrqWlJTQ09MSJE0VFRdXV1Q0NDer9Cg64mzdvnhhT36FFYrW0+AhHXA1HQ1wpzWw297t9GGRHx2IymY4cOZKfn19eXl5XV+d0OsVjBnWpOl/xEY64Go6qlx8Yur58/KtBc/2WaG5ubmlpaU1NTWtrq3jMoC5V5yt9ePOWWALqXn5glIyrzMzMnJyckpISu93e1NQkHjOoS9X5Sh/evCWWgLqXHxgl48pqtWZnZxcXF9tsNsV+XRSGp+p8pQ9v3hJLQN3LD4yScbV//36Kq6KiIoqrq1eviscM6lJ1vtKHN2+JJaDu5QcGcQUqUXW+0oc3b4kloO7lB0bVuOLfZUdcBRVV5yt9ePOWWALqXn5gEFegElXnK31485ZYAupefmAQV6ASVecrfXjzllgC6l5+YBBXoBJV5yt9ePOWWALqXn5gEFegElXnK31485ZYAupefmAQV6ASVecrfXjzllgC6l5+YBBXoBJV5yt9ePOWWALqXn5gEFegElXnK31485ZYAupefoUlJiZ6/+QhxBWoRNX5Sh/evCWWgLqXX2F0yWbNmpWbmysuGAriClSi6nylD2/eEktA3cuvMM3FbDa/9tpr3/vHCUccV729vR9++CGlgnsnbXDnzp3Hjx/fsWNHRUWF+yK/QVwFM1XnK31485ZYAupefoWxuGLmzZtXVlYmVrgZcVyRBx98cPLkyV1dXbzn5MmTtMFt27bRfymx3Gr9B3EVzFSdr/ThzVtiCah7+RXmHldk/PjxW7du7evrE+tctFHE1UcffaS5/hYi7/ntb38bFhbW3NzsVvU/nZ2dFCGZmZn19fX0cvfu3Z999hlblJeX98knn7A2hSvlnNPp5CveKA1xFcQ0RecrfXjzllgC6l5+hQ0Iq+8sW7bs4sWLYuno4uratWtRUVFxcXHsZVtbW3h4+IoVK667MsP97qqhoYHu89ieTJw4saCg4Oc//3lsbCxbSovGjRvX0tJC7d/85je33norX3EENMRVENMUna/04c1bYgmoe/kVxiNKQNGyb9++wcV8/I/ASy+9dNNNN7EbpoyMDNoaRdH1QXH14osvzp8/3263l5eX33zzzUuWLKG7K6qpqqqqra2lRmhoKGUM7c/UqVNfffVVvuIIaIirIKYpOl/pw5u3xBLo7588ebI+4YHMfBFXpaWltIWtW7dS+6c//SndJ7F+bWBc3XbbbS+88MIOl8cff9xsNlPCjR079oMPPti+ffuMGTMeffTRX//61+fOnaMV8/Pz+YojMPCgIbjQfCWMcDXow5u3xBIACYmfYBdf/GMg86Mf/YhSijZuMpm2bdvGOrWBcRUWFibsj81me/jhh+Pi4uLj43/3u9/99a9/nThx4ttvv/2DH/ygr6+PrzgCGu6uQDn68OYtsQRAQkIw+O6rFgzFEm3k9ddfd/+ShTYwrubPn79nzx7Wpj1paGigxocffkjhNG3atJMnT9bV1VHazZ49e/Xq1XytkdEQV6AcfXjzllgCICH3rPLpF9mZlpYWCir+JQtGiCuLxRIaGrp27dqUlJTFixdTRLW2ttbX15vN5smTJ/f09FDNkiVLaC3hF7lGAHEF6tGHN2+JJQASYkHl618Tdrd8+XLtuy9ZMEJcXXfdhM2dOzckJGTRokX8/049+OCDzz//PGunpaVFRUV1d3fr64wI4grUow9v3hJLACSk+f0hTDabLSMjQ+wNEMQVqEcf3rwllgBICI+4RVyBYvThzVtiCYDqEFcAxqcPb94SSyA4bNiwoaCgQOwNDogrAOPThzdviSUQHGiC2759u9jr5ttvvy0vLxd7lYC4AjA+fXjzllgCweF74yo8PHz4AnkhrgCMTx/evCWWgAwoSL7++uvBL6lRWVmZm5v78ccf22w2fQWX9vb2Tz/91Gq1fvPNN+5xRRPcnj17jh492tXVxXr27t1LBc888wzVXL58mXV2dHQcP36cVqcbL9YjKcSVGk6dOmWxWCoqKniPpyHqqR+MTB/evCWWgAyEeyP+khozZ87UXMaNG+f+uLy6urq5c+eyRRMnTuSrbN261Ww2s/5FixaxxLr11ltZD6EZkHootNyfL3727Fm+ZeloiCv5vfzyy2w0mkymLVu29Hseop76weD04c1bYgnIQPMcVzExMXl5eU1NTatWrYqKirpy5QqrWbFixaRJk4qLix0Ox9q1a9kqFE7PPvvs8uXL6SP9ySefUCfdfg35Fuz54hcuXDh//jx7vjhfJB0NcSW/CRMmJCUl0WDesWNHQ0NDv+ch6qkfDE4f3rwlloAMhomrzZs3s072VyqOHz/OXs6aNWvDhg2sTSnFV+nr6zt27BgtevrppzXXcxlYjfAW7Pni213Y88U7Ozv5UrkgrhSwdOlSGtL79u3r6elhPZ6GqKd+MDh9ePOWWAIyGCaueH9bWxu9/Oijj9jL8PDwrVu3Dl7llVdeGTNmzEMPPbRy5Ur31YW3GPx8cZoW+VK5aIgr+dEx0tANDQ1dtGjRtWvX+j0PUU/9YHD68OYtsQRkQJ/AlJQU1qZ7I80trl599VXWf/ToUc31UDv28v7774+Pj2ft4uJivkpkZOQbb7xBDZvNxjv7B8XV/Pnzd+/ezdq9vb38+xcy0hBX8mN3SGVlZXTsmZmZ/Z6HqKd+MDh9ePOWWAIyWLZs2bRp0yix1q9fT7dN7nFlMplWr1797rvvUsHChQv5H9Fgf8r2ueee27Rp06RJk/gqd9999z333JOamkoNWvedd95h9bTZRx555K233uru7qaXGRkZ7PnimzdvZs8Xb2lp+d/eyAZxJbv8/PwpU6bQ4E9KStJcj7Tv9zxEPfWDwenDm7fEEpCB3W5/+OGHJ0yYMHv27OTk5IkTJ/K4ooyhTlr02GOP1dbWuq+1ZcuWmTNnUlY9//zzdFPFVqHbr7vuuotu15YvX07rxsXFseI333yTOu+44w7+jXmq588XP3PmDN+sdBBXsmtqaqKfyaKjo2kYr1u3jvd7GqKe+sHI9OHNW2IJyEz4FzwYEuIKwPj04c1bYgnIDHHlDcQVgPHpw5u3xBKQ2Zo1a/BvHd/LbDb3u30YZNfb22symRBXoBg+whFXELwiIiLa2tr4R0B2jY2NISEhFFfZ2dkUVzabDXEFCuAjHHEFwSs2Nraqqop/BGR39uzZmJgYxBUoho9wxBUEr/j4eKvVyj8CsktJSbn33nvpiCiuiouLKa68/8PKAIbFRzjiCoLXtm3bEhIS+EdAanQ4CxcuTExMzMzMzMnJKSkpsdvtTU1N4jEDyIYPcsQVBC+6+ZgyZQpN7vxTIK/09PSIiIi0tLSsrKzc3NzS0tKamprW1lbxmAFkwwc54gqC2uHDh6OiopKTk6urq/lnQSLd3d2FhYWrVq0KCwtLSkqyWCxHjhzJz88vLy+vq6tzOp3iAQPIho92xBUEtY6Ojry8vLi4OLrN0uQUGRm5YMGCjRs37tq1y/1b7A0NDXR04gEDyAZxBfBfdHfS3Nx86dKlioqKgoICmusPHTp04MABq9W6Xx60t7TPtOe0/3QUdCx0RHRc7DGPAFJDXAH8V29vr9PpbGxsrKmpoVm+sLDw9OnTOTk52S4nZMB2lfaZ9pz2n46CjoWOiI6Ljk48YADZIK4A/oduQdra2mh+r62traysLCsrO3fuXHFxcZE8aG9pn2nPaf/pKOhY6IhwawVqQFwB/E9fX19XV1d7e7vD4aivr6fp3m6321yqZcB2lfaZ9pz2n46CjoWOiP/JGACpIa4AdDSz9/T0dHZ2Op1Oui9pbm6mSf+qPGhvaZ9pz2n/6SjoWJBVoAzEFQAASABxBQAAEkBcAQCABBBXAAAgAcQVAABIAHEFAAASQFwBAIAEEFcAACABxBUAAEgAcQUAABJAXAEAgAQQVwAAIAHEFQAASABxBQAAEkBcAQCABBBXAAAgAcQVAABIAHEFAAASQFwBAIAEEFcAACABxBUAAEgAcQUAABJAXAEAgAQQVwAAIAHEFQAASABxBQAAEhgirgAAAAwLcQUAABJAXAEAgAT+A0IroVoiR5fwAAAAAElFTkSuQmCC" /></p>

制御の流れは、

1. ユーザの入力に応じてControllerのメソッドが呼び出される。
2. Controllerのメソッドは、ユーザの入力に応じた引数とともにModelのメソッドを呼び出す。
3. Modelは、それに対応するビジネスロジック等の処理を(通常、非同期に)行い、
自分自身の状態を変える(変わらないこともある)。
4. Modelの状態変化は、そのModelのオブザーバーとして登録されているViewに通知される。
5. Viewは関連するデータをModelから取得し、それを出力(UIに表示)する。

ViewはModelの[Observer](design_pattern.md#SS_9_4_4)であるため、ModelはViewへ依存しない。
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


