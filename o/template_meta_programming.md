<!-- deep/md/template_meta_programming.md -->
# テンプレートメタプログラミング <a id="SS_13"></a>

本章でのテンプレートメタプログラミングとは、下記の2つを指す。

* ジェネリックプログラミング
* メタプログラミング

C++においては、この2つはテンプレートを用いたプログラミングとなる。

ジェネリックプログラミングとは、具体的なデータ型に依存しない抽象的プログラミングであり、
その代表的な成果物はSTLのコンテナやそれらを扱うアルゴリズム関数テンプレートである。

この利点は、

* i種の型
* j種のコンテナ
* k種のアルゴリズム

の開発を行うことを考えれば明らかである。

ジェネリックプログラミングが無ければ、コンテナの種類はi x j個必要になり、
それらに適用するアルゴリズム関数は、i x j x k個必要になる。
また、サポートする型の増加に伴いコンテナやアルゴリズム関数は指数関数的に増えて行く。
C言語のqsort()のように強引なキャストを使い、この増加をある程度食い止めることはできるが、
それによりコンパイラによる型チェックは無効化され、
静的な型付け言語を使うメリットの多くを失うことになる。

メタプログラミングとは、

* ジェネリックのサポート
* 実行時コードの最適化
* 関数やクラスを生成するコードのプログラミング

のような目的で行われるテンプレートプログラミングの総称である。

ジェネリックプログラミングとメタプログラミングに明確な境界はない、
また明確にしたところで大きなメリットはと思われるため、
本章では、これらをまとめた概念であるテンプレートメタプログラミングとして扱い、
ログ取得ライブラリやSTLを応用したNstdライブラリの実装を通して、
これらのテクニックや、使用上の注意点について解説する。

c++20から導入された[コンセプト](term_explanation.md#SS_19_11_2)によりジェネリックプログラミングは、
開発容易性、可読性、保守性が大きく向上しため、この章のコード例には、
[コンセプト](term_explanation.md#SS_19_11_2)(`concept`, `requires`)を多用した。

が、この副作用として、
c++17までしか使えない読者の参考にならないコードが増えてしまうことを避けるため、
以下のような`#ifdef`を使うことによりc++17でも使えるコード例となるようにした
(本来、`#ifdef`は使うべきではないが、`#ifdef`の数少ない使いどころだと判断した)。

```cpp
    //  example/template/cplusplus.cpp 4

    #if __cplusplus >= 202002L  // c++20
    // c++20以上の機能を使い、c++17以下の機能ではill-formedとなるコード
    template <typename T, typename U>
    concept same_as = requires(T const* t, U const* u)
    {
        {t = u, u = t};
    };

    #else  // c++17以下の機能を使い上記のコードと同じ機能を持つ実装
    template <typename T, typename U>
    inline constexpr bool same_as = std::is_same_t<T, U>;
    #endif
```
___

__この章の構成__

&emsp;&emsp; [ログ取得ライブラリの開発](template_meta_programming.md#SS_13_1)  
&emsp;&emsp;&emsp; [要件](template_meta_programming.md#SS_13_1_1)  
&emsp;&emsp;&emsp; [ログ取得ライブラリのインターフェース](template_meta_programming.md#SS_13_1_2)  
&emsp;&emsp;&emsp; [パラメータパック](template_meta_programming.md#SS_13_1_3)  
&emsp;&emsp;&emsp; [Loggerの実装](template_meta_programming.md#SS_13_1_4)  
&emsp;&emsp;&emsp; [ユーザ定義型とそのoperator\<\<のname lookup](template_meta_programming.md#SS_13_1_5)  
&emsp;&emsp;&emsp; [Ints_tのログ登録](template_meta_programming.md#SS_13_1_6)  

&emsp;&emsp; [Nstdライブラリの開発](template_meta_programming.md#SS_13_2)  
&emsp;&emsp;&emsp; [Nstdライブラリを使用したリファクタリング](template_meta_programming.md#SS_13_2_1)  
&emsp;&emsp;&emsp; [安全なvector](template_meta_programming.md#SS_13_2_2)  
&emsp;&emsp;&emsp; [安全な配列型コンテナ](template_meta_programming.md#SS_13_2_3)  
&emsp;&emsp;&emsp; [初期化子リストの副作用](template_meta_programming.md#SS_13_2_4)  

&emsp;&emsp; [メタ関数のテクニック](template_meta_programming.md#SS_13_3)  
&emsp;&emsp;&emsp; [STLのtype_traits](template_meta_programming.md#SS_13_3_1)  
&emsp;&emsp;&emsp; [is_void_xxxの実装](template_meta_programming.md#SS_13_3_2)  
&emsp;&emsp;&emsp; [is_same_xxxの実装](template_meta_programming.md#SS_13_3_3)  
&emsp;&emsp;&emsp; [AreConvertibleXxxの実装](template_meta_programming.md#SS_13_3_4)  
&emsp;&emsp;&emsp; [関数の存在の診断](template_meta_programming.md#SS_13_3_5)  

&emsp;&emsp; [Nstdライブラリの開発2](template_meta_programming.md#SS_13_4)  
&emsp;&emsp;&emsp; [SafeArray2の開発](template_meta_programming.md#SS_13_4_1)  
&emsp;&emsp;&emsp; [Nstd::SafeIndexの開発](template_meta_programming.md#SS_13_4_2)  
&emsp;&emsp;&emsp; [Nstd::SafeIndexのoperator\<\<の開発](template_meta_programming.md#SS_13_4_3)  
&emsp;&emsp;&emsp; [コンテナ用Nstd::operator\<\<の開発](template_meta_programming.md#SS_13_4_4)  

&emsp;&emsp; [Nstdライブラリの開発3(浮動小数点関連)](template_meta_programming.md#SS_13_5)  
&emsp;&emsp;&emsp; [浮動小数点の比較](template_meta_programming.md#SS_13_5_1)  
&emsp;&emsp;&emsp; [固定小数点クラス](template_meta_programming.md#SS_13_5_2)  
&emsp;&emsp;&emsp; [固定小数点リテラル](template_meta_programming.md#SS_13_5_3)  
&emsp;&emsp;&emsp; [有理数クラス](template_meta_programming.md#SS_13_5_4)  
&emsp;&emsp;&emsp; [有理数リテラル](template_meta_programming.md#SS_13_5_5)  

&emsp;&emsp; [ログ取得ライブラリの開発2](template_meta_programming.md#SS_13_6)  
&emsp;&emsp; [その他のテンプレートテクニック](template_meta_programming.md#SS_13_7)  
&emsp;&emsp;&emsp; [forwardingリファレンスとstd::forward](template_meta_programming.md#SS_13_7_1)  
&emsp;&emsp;&emsp; [ジェネリックラムダによる関数内での関数テンプレートの定義](template_meta_programming.md#SS_13_7_2)  
&emsp;&emsp;&emsp; [クラステンプレートと継承の再帰構造](template_meta_programming.md#SS_13_7_3)  
&emsp;&emsp;&emsp; [意図しないname lookupの防止](template_meta_programming.md#SS_13_7_4)  
&emsp;&emsp;&emsp; [Nstd::Type2Strの開発](template_meta_programming.md#SS_13_7_5)  
&emsp;&emsp;&emsp; [静的な文字列オブジェクト](template_meta_programming.md#SS_13_7_6)  
&emsp;&emsp;&emsp; [関数型をテンプレートパラメータで使う](template_meta_programming.md#SS_13_7_7)  

&emsp;&emsp; [注意点まとめ](template_meta_programming.md#SS_13_8)  
  
  

[このドキュメントの構成](introduction.md#SS_1_7)に戻る。  
___

## ログ取得ライブラリの開発 <a id="SS_13_1"></a>
ここではログ取得ライブラリの開発を行う。

### 要件 <a id="SS_13_1_1"></a>

ログ取得ライブラリの要件は、

* ソースコードの場所とそこで指示されたオブジェクトの値を文字列で保持する
* 後からそれらを取り出せる

ことのみとする。下記はその文字列を取り出した例である。

```
    app/src/main.cpp: 96:Options
                         cmd       : GenPkg
                         in        : 
                         out       : 
                         recursive : true
                         src_as_pkg: false
        ...

    app/src/main.cpp: 51:start GenPkg

    file_utils/ut/path_utils.cpp: 38:1
    file_utils/ut/path_utils.cpp: 48:ut_data/app1
                         ut_data/app1/mod1
                         ut_data/app1/mod2

        ...

    app/src/main.cpp:100:Exit:0
```

単純化のためログの番号やタイムスタンプのサポートはしない。
また、実行速度や仕様メモリ量の制限等も本章の趣旨とは離れるため考慮しない。

### ログ取得ライブラリのインターフェース <a id="SS_13_1_2"></a>

ログ取得コードにより、コードクローンが増えたり、主なロジックの可読性が下がったのでは、
本末転倒であるため、下記のようにワンライナーで記述できるべきだろう。

```cpp
    LOGGER("start GenPkg", objA, objB, objC);
```

また、要件で述べた通り、ソースコード位置を特定できなければならないため、
上記LOGGERは下記のような関数型マクロにならざるを得ない。

```cpp
    #define LOGGER(...) CppLoggerFunc(__FILE__, __LINE__, __VA_ARGS__)
```

CppLoggerFuncをクラス外の関数として実装した場合、ログ保持のための静的なオブジェクトが必要になる。
これは避けるべきなので、「[Singleton](design_pattern.md#SS_9_13)」で述べた構造を導入すると、

```cpp
    #define LOGGER(...) Logger::Inst().Set(__FILE__, __LINE__, __VA_ARGS__)
```

のような関数型マクロとなる。これがログ取得ライブラリの主なインターフェースとなる。

C言語プログラミングばかりをやりすぎて、
視神経と手の運動神経が直結してしまった大脳レス・プログラマーは、

```cpp
    __VA_ARGS__
```

を見るとprintf(...)のような可変長引数を取る関数を思い浮かべる。
「人は一昨日も行ったことを昨日も行ったという理由で、今日もそれを行う」
という諺を思い出すと気持ちは分からなくもないが、 
C++ではprintf(...)のような危険な可変長引数を取る関数を作ってはならない。
パラメータパックを使って実装するべきである。

### パラメータパック <a id="SS_13_1_3"></a>
C++11で導入されたパラメータパックはやや複雑なシンタックスを持つため、
まずは単純な例から説明する。

次のような単体テストをパスする関数テンプレートsumをパラメータパックで実装することを考える。

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 26

    ASSERT_EQ(1, sum(1));
    ASSERT_EQ(3, sum(1, 2));
    ASSERT_EQ(6, sum(1, 2, 3));
    ASSERT_FLOAT_EQ(6.0, sum(1, 2.0, 3.0));
    ASSERT_EQ(10, sum(1, 2, 3, 4));

    // ...

    ASSERT_EQ(55, sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));

    // ...
```

sumの要件は、

* 可変長引数を持つ
* [算術型](term_explanation.md#SS_19_1_3)の引数と戻り値を持つ
* すべての引数の和を返す

のようなものになるため、関数テンプレートsumは下記のように書ける。

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 9

    template <typename HEAD>
    int sum(HEAD head)
    {
        return head;
    }

    template <typename HEAD, typename... TAIL>
    int sum(HEAD head, TAIL... tails)
    {
        return head + sum(tails...);
    }
```

1つ目の関数テンプレートsumは引数が一つの場合に対応する。
2つ目の関数テンプレートsumは引数が2つ以上の場合に対応する。

2つ目の関数テンプレートsumのテンプレートパラメータ

```cpp
    typename... TAIL
```

がパラメータパックであり、0個以上の型が指定されることを意味する。
これを関数の引数として表すシンタックスが

```cpp
    TAIL... tails
```

であり、同様に0個以上のインスタンスが指定されることを表している。

HEADとTAILより、2つ目のsumは1個以上の引数を取れることになるため、
引数が1つの場合、どちらのsumを呼び出すかが曖昧になるように思えるが、
ベストマッチの観点から1つ目のsumが呼び出される。

sum(1, 2, 3)の呼び出し時のsumの展開を見てみることでパラメータパックの振る舞いを解説する。

この呼び出しは、2つ目のsumにマッチする。従って下記のように展開される。

```cpp
    return 1 + sum(2, 3);
```

sum(2, 3)も同様に展開されるため、上記コードは下記のようになる。

```cpp
    return 1 + 2 + sum(3);
```

sum(3)は1つ目のsumにマッチするため、最終的には下記のように展開される。

```cpp
    return 1 + 2 + 3;
```

これで基本的な要件は満たしたが、このsumでは下記のようなコードもコンパイルできてしまう。

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 43

    ASSERT_EQ(2, sum(1, true, false));
```

これを認めるかどうかはsumの仕様次第だが、ここではこれらを認めないようにしたい。
また、引数に浮動小数が与えられた場合でも、sumの戻り値の型がintなる仕様には問題がある。
合わせてそれも修正する。

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 53

    template <typename HEAD>
    auto sum(HEAD head)
    {
        // std::is_sameの2パラメータが同一であれば、std::is_same<>::value == true
        static_assert(!std::is_same<HEAD, bool>::value, "arguemnt type must not be bool.");

        return head;
    }

    template <typename HEAD, typename... TAIL>
    auto sum(HEAD head, TAIL... tails)
    {
        // std::is_sameの2パラメータが同一であれば、std::is_same<>::value == true
        static_assert(!std::is_same<HEAD, bool>::value, "arguemnt type must not be bool.");

        return head + sum(tails...);
    }
```
```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 83

    // boolを除く算術型のみ認めるため、下記はコンパイルできない。
    // ASSERT_EQ(2, sum(1, true, false));

    auto i1 = sum(1);
    auto i2 = sum(1, 2);

    static_assert(std::is_same<int, decltype(i1)>::value);  // 1の型はint
    static_assert(std::is_same<int, decltype(i2)>::value);  // 1 + 2の型はint

    auto u1 = sum(1U);
    auto u2 = sum(1U, 2);

    static_assert(std::is_same<unsigned int, decltype(u1)>::value);  // 1Uの型はunsigned int
    static_assert(std::is_same<unsigned int, decltype(u2)>::value);  // 1U + 2の型はunsigned int

    auto f0 = sum(1.0, 1.2);
    static_assert(std::is_same<double, decltype(f0)>::value);

    // ただし、戻り型をautoにしたため、下記も認められるようになった。
    // これに対しての対処は別の関数で行う。
    auto str = sum(std::string{"1"}, std::string{"2"});

    ASSERT_EQ(str, "12");
    static_assert(std::is_same<std::string, decltype(str)>::value);
```

以上で示したようにパラメータパックにより、
C言語での可変長引数関数では不可能だった引数の型チェックができるようになったため、
C言語でのランタイムエラーがコンパイルエラーにできるようになった。

なお、上記コードで使用した[std::is_same](template_meta_programming.md#SS_13_3_1_3)は、
与えられた2つのテンプレートパラメータが同じ型であった場合、
valueをtrueで初期化するクラステンプレートであり、 type_traitsで定義されている
(後ほど使用するstd::is_same_vはstd::is_same<>::valueと等価な定数テンプレート)。
この実装については、後ほど説明する。

[演習-パラメータパック](exercise_q.md#SS_20_11_1)  

#### パラメータパックの畳みこみ式 <a id="SS_13_1_3_1"></a>
上記したsumは、パラメータパックの展開に汎用的な再帰構造を用いたが、
C++17で導入された畳みこみ式を用い、以下の様に簡潔に記述することもできる。

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 123

    template <typename... ARGS>
    auto sum(ARGS... args)
    {
        return (args + ...);  // 畳みこみ式は()で囲まなければならない。
    }
```
```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 134

    ASSERT_EQ(1, sum(1));
    ASSERT_EQ(3, sum(1, 2));
    ASSERT_EQ(6, sum(1, 2, 3));
    ASSERT_EQ(6.0, sum(1, 2.0, 3.0));
    ASSERT_EQ(10, sum(1, 2, 3, 4));
    ASSERT_EQ(55, sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
```

畳みこみ式で使用できる演算子を以下に示す。

```
    + - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*
```

これらの演算子がオーバーロードである場合でも、畳みこみ式は利用できる。


#### 前から演算するパラメータパック <a id="SS_13_1_3_2"></a>
パラメータパックを使うプログラミングでは、
上記したHEADとTAILによるリカーシブコールがよく使われるパターンであるが、
これには後ろから処理されるという、微妙な問題点がある。

これまでのsumに代えて下記のようなproduct(掛け算)を考える。

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 149

    template <typename HEAD>
    auto product(HEAD head)
    {
        static_assert(!std::is_same_v<HEAD, bool>, "arguemnt type must not be bool.");
        static_assert(std::is_arithmetic_v<HEAD>, "arguemnt type must be arithmetic.");

        return head;
    }

    template <typename HEAD, typename... TAIL>
    auto product(HEAD head, TAIL... tails)
    {
        static_assert(!std::is_same_v<HEAD, bool>, "arguemnt type must not be bool.");
        static_assert(std::is_arithmetic_v<HEAD>, "arguemnt type must be arithmetic.");

        return head * product(tails...);
    }
```

このコードの単体テストは、

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 173

    ASSERT_EQ(1, product(100, 0.1, 0.1));
```

のようになるだろうが、
std::numeric_limits<>::epsilonを使用していないため
(「[浮動小数点型](term_explanation.md#SS_19_1_12)」参照)
、このテストはパスしない。一方で、以下のテストはパスする。

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 178

    ASSERT_EQ(1, product(0.1, 0.1, 100));

```

一般に0.01の2進数表現は無限小数になるため、これを含む演算にはepsilon以下の演算誤差が発生する。
前者単体テストでは、後ろから演算されるために処理の途中に0.01が現れるが、
後者では現れないため、この誤差の有無が結果の差になる。

このような演算順序による微妙な誤差が問題になるような関数を開発する場合、
演算は見た目の順序通りに行われた方が良いだろう。
ということで、productを前から演算するように修正する。

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 196

    template <typename HEAD>
    auto product(HEAD head)
    {
        static_assert(!std::is_same_v<HEAD, bool>, "arguemnt type must not be bool.");
        static_assert(std::is_arithmetic_v<HEAD>, "arguemnt type must be arithmetic.");

        return head;
    }

    template <typename HEAD, typename HEAD2, typename... TAIL>
    auto product(HEAD head, HEAD2 head2, TAIL... tails)
    {
        static_assert(!std::is_same_v<HEAD, bool>, "arguemnt type must not be bool.");
        static_assert(std::is_arithmetic_v<HEAD>, "arguemnt type must be arithmetic.");

        return product(head * head2, tails...);
    }
```

HEAD、TAILに加えHEAD2を導入することで、前からの演算を実装できる
(引数が一つのproductに変更はない)。当然ながら、これにより、

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 220

    ASSERT_EQ(1, product(100, 0.1, 0.1));
```

はパスし、下記はパスしなくなる。

```cpp
    //  example/template_cpp17/parameter_pack_ut.cpp 225

    ASSERT_EQ(1, product(0.1, 0.1, 100));

```


### Loggerの実装 <a id="SS_13_1_4"></a>

パラメータパックを使用したログ取得コードは以下のようになる。

```cpp
    //  example/template/logger_0.h 48

    #define LOGGER_P(...) Logging::Logger::Inst().Set(__FILE__, __LINE__)
    #define LOGGER(...) Logging::Logger::Inst().Set(__FILE__, __LINE__, __VA_ARGS__)
```

予定していたものと若干違う理由は、\_\_VA\_ARGS\_\_が1個以上の識別子を表しているからである。
従って、通過ポイントのみをロギングしたい場合、LOGGER_P()を使うことになる。
gcc拡張を使えば、LOGGER_PとLOGGERを統一できるが、そのようなことをすると別のコンパイラや、
静的解析ツールが使用できなくなることがあるため、残念だが上記のように実装するべきである。

Loggerクラスの実装は、下記のようになる。

```cpp
    //  example/template/logger_0.h 6

    namespace Logging {
    class Logger {
    public:
        static Logger&       Inst();
        static Logger const& InstConst() { return Inst(); }

        std::string Get() const;  // ログデータの取得
        void        Clear();      // ログデータの消去

        template <typename... ARGS>  // ログの登録
        void Set(char const* filename, uint32_t line_no, ARGS const&... args)
        {
            oss_.width(32);
            oss_ << filename << ":";

            oss_.width(3);
            oss_ << line_no;

            set_inner(args...);
        }

        Logger(Logger const&)            = delete;
        Logger& operator=(Logger const&) = delete;

    private:
        void set_inner() { oss_ << std::endl; }

        template <Nstd::Printable HEAD, Nstd::Printable... TAIL>
        void set_inner(HEAD const& head, TAIL const&... tails)
        {
            oss_ << ":" << head;
            set_inner(tails...);
        }

        Logger() {}
        std::ostringstream oss_{};
    };
    }  // namespace Logging
```

すでに述べた通り、

* クラスはシングルトンにする
* パラメータパックにより可変長引数を実現する

ようにした。
また、識別子の衝突を避けるために、名前空間Loggingを導入し、Loggerはその中で宣言した。

次に、どのように動作するのかを単体テストで示す。

```cpp
    //  example/template/logger_0_ut.cpp 16

    auto a = 1;
    auto b = std::string{"b"};

    LOGGER_P();               // (1)
    LOGGER(5, "hehe", a, b);  // (2)
    auto line_num = __LINE__;

    auto s = Logging::Logger::InstConst().Get();

    auto exp = std::string{log_str_exp(__FILE__, line_num - 2, "\n")};  // (1)のログ
    exp += log_str_exp(__FILE__, line_num - 1, ":5:hehe:1:b\n");        // (2)のログ
    ASSERT_EQ(exp, s);

    Logging::Logger::Inst().Clear();  // クリアの確認
    ASSERT_EQ("", Logging::Logger::InstConst().Get());
```

行を含む出力の期待値をソースコードに直接書くと行増減のたびにそれらを修正する必要ある。
期待値の一部を自動計算する下記コード(上記コードで使用)を単体テストに導入することで、
そういった修正を避けている。

```cpp
    //  example/template/logger_ut.h 4

    inline std::string line_to_str(uint32_t line)
    {
        if (line < 10) {
            return ":  ";
        }
        else if (line < 100) {
            return ": ";
        }
        else if (line < 1000) {
            return ":";
        }
        else {
            assert(false);  // 1000行を超える単体テストファイルを認めない
            return "";
        }
    }

    inline std::string log_str_exp(char const* filename_cstr, uint32_t line, char const* str)
    {
        auto const filename = std::string{filename_cstr};
        auto const len      = 32 > filename.size() ? 32 - filename.size() : 0;
        auto       ret      = std::string(len, ' ');

        ret += filename;
        ret += line_to_str(line);
        ret += std::to_string(line);
        ret += str;

        return ret;
    }
```

アプリケーションの開発では、
下記のようなユーザが定義した名前空間とクラスを用いることがほとんどである。

```cpp
    //  example/template/app_ints.h 12

    namespace App {

    class X {
    public:
        X(std::string str, int num) : str_{std::move(str)}, num_{num} {}
        std::string ToString() const { return str_ + "/" + std::to_string(num_); }
        // ...
    };
    }  // namespace App
```

このApp::Xのインスタンスのログを取得できることも、当然Logging::Loggerの要件となる。
従って、下記の単体テストはコンパイルでき、且つパスすることが必要になる。


```cpp
    //  example/template/logger_0_ut.cpp 42

    auto x = App::X{"name", 3};

    LOGGER(1, x);
    auto line_num = __LINE__;

    auto s = Logging::Logger::InstConst().Get();

    auto exp = std::string{log_str_exp(__FILE__, line_num - 1, ":1:name/3\n")};
    ASSERT_EQ(exp, s);
```

Logging::Loggerのコードからオブジェクトのログを登録するためには、
Logging::Logger::set_innerがコンパイルできなければならない。
つまり、

```cpp
    std::ostream& operator<<(std::ostream&, ログ登録オブジェクトの型)
```

の実装が必要条件となる。App::Xでは下記のようなコードになる。

```cpp
    //  example/template/app_ints.h 28

    namespace App {

    inline std::ostream& operator<<(std::ostream& os, X const& x) { return os << x.ToString(); }
    }  // namespace App
```

他の任意のユーザ定義型に対しても、このようにすることでログ登録が可能になる。

なお、ヒューマンリーダブルな文字列でその状態を表示できる関数をユーザ定義型に与えることは、
デバッガを使用したデバッグ時にも有用である。

### ユーザ定義型とそのoperator\<\<のname lookup <a id="SS_13_1_5"></a>

ここで、一旦Logging::Loggerの開発を止め、
Logging::Logger::set_innerでのApp::operator<<の[name lookup](term_explanation.md#SS_19_10_2)について考えてみることにする。

ここまでで紹介したログ取得ライブラリやそれを使うユーザ定義型等の定義、宣言の順番は、

1. Logging::Logger
2. App::X
3. App::operator<<
4. 単体テスト(Logger::set_innerのインスタンス化される場所)

となっている。
name lookupの原則に従い、App::Xの宣言は、App::operator<<より前に行われている。
これを逆にするとコンパイルできない。
しかし、Logging::Loggerは、後から宣言されたApp::operator<<を使うことができる。
多くのプログラマは、これについて気づいていないか、その理由を間違っての認識している。

その認識とは、「テンプレート内の識別子の[name lookup](term_explanation.md#SS_19_10_2)は、
それがインスタンス化される時に行われる」というものであり、これにより
「 Logging::Loggerのname lookupは単体テスト内で行われる。
それはApp::operator<<宣言後であるためコンパイルできる」と考えることができるが、
[two phase name lookup](term_explanation.md#SS_19_10_3)で行われるプロセスと反するため誤りである。

まずは、この認識の誤りを下記のコードで説明する。

```cpp
    //  example/template/logger_0_ut.cpp 68

    namespace App2 {
    class X {
    public:
        explicit X(std::string str, int num) : str_{std::move(str)}, num_{num} {}
        std::string ToString() const { return str_ + "/" + std::to_string(num_); }
        // ...
    };
    }  // namespace App2

    namespace App3 {  // App3をApp2にすればコンパイルできる
    std::ostream& operator<<(std::ostream& os, App2::X const& x) { return os << x.ToString(); }
    }  // namespace App3

    namespace {

    TEST(Template, logger_0_X_in_AppX)
    {
        Logging::Logger::Inst().Clear();

        auto x = App2::X{"name", 3};

        using namespace App3;  // この記述は下記のエラーに効果がない

        LOGGER(1, x);  // ここがコンパイルエラーとなる
        auto line_num = __LINE__;

        auto s = Logging::Logger::InstConst().Get();

        auto exp = std::string{log_str_exp(__FILE__, line_num - 1, ":1:name/3\n")};
        ASSERT_EQ(exp, s);
    }
    }  // namespace
```

このコードは、もともとのコードの名前空間名をApp2とApp3にしただけのものである。
もし、前記した「認識」の内容が正しいのであれば、このコードもコンパイルできるはずであるが
(実際にApp3と書いた部分をApp2に書き換えればコンパイルできる)、
実際には下記のようなエラーが発生する。


```
    logger_0.h:37:21: error: no match for ‘operator<<’ 
    (operand types are ‘std::basic_ostream<char>’ and ‘const App2::X’)
       37 |         oss_ << ":" << head;
          |         ~~~~~~~~~~~~^~~~~~~

```

エラー内容からoperator<<が発見できないことは明らかである。
単体テスト内でのusing namespace App3はLogging::Logger::set_innerの宣言より後に書かれているため、
このエラーを防ぐ効果はない。

Logging::Logger::set_innerの中でusing namespace App3とした上で、
two phase name lookupの原則に従い、
App2::XとApp3::operator<<をLogging::Loggerの宣言より前に宣言することで、
ようやくコンパイルすることができる。

名前空間Appの例と名前空間App2、App3の例での本質的な違いは、
「型Xとそのoperator<<が同じ名前空間で宣言されているかどうか」である。

名前空間Appの例の場合、型Xとそのoperator<<が同じ名前空間で宣言されているため、
[ADL](term_explanation.md#SS_19_10_5)(実引数依存探索)が働く。
また、Logging::Logger::set_inner(x)はテンプレートであるため、[two phase name lookup](term_explanation.md#SS_19_10_3)
が使用される。
その結果、Logging::Logger::set_inner(x)でのname lookupの対象には、
「Logging::Logger::set_inner(x)がインスタンス化される場所
(単体テスト内でのLOGGER_PやLOGGERが使われている場所)より前方で宣言された名前空間App」も含まれる。
こういったメカニズムにより、
Logging::Logger::set_inner定義位置の後方で宣言されたApp::operator<<も発見できることになる。

一方で、名前空間App2、App3の例では、型XがApp2で宣言されているため、
Logging::Logger::set_inner(x)でのname lookupの対象にApp3は含ず、
App3::operator<<は発見されない(繰り返すが、インスタン化の場所直前でのusing nameには効果がない)。

型Xとそのoperator<<を同じ名前空間で宣言することは本質的に重要なことであるが、
名前空間を使用する場合、自然にそのような構造になるため、
その重要性の理由を知る必要はないように思われる。
しかし、次の例で示すようにこのメカニズムを知らずに解決することができないケースが存在する。

### Ints_tのログ登録 <a id="SS_13_1_6"></a>
話題はログ取得ライブラリの開発に戻る。
アプリケーションの開発では、下記のように宣言された型エイリアスを使うことは珍しくない。

```cpp
    //  example/template/app_ints.h 6

    namespace App {
    using Ints_t = std::vector<int>;
    }
```

そのoperator<<を下記のように定義したとする。

```cpp
    //  example/template/logger_0_ut.cpp 109

    namespace App {
    std::ostream& operator<<(std::ostream& os, Ints_t const& ints)
    {
        auto sep = "";

        for (auto const i : ints) {
            os << std::exchange(sep, ", ") << i;
        }

        return os;
    }
    }  // namespace App
```

単体テストは下記のように書けるが、残念ながらコンパイルエラーになり、

```cpp
    //  example/template/logger_0_ut.cpp 131

    auto ints = App::Ints_t{1, 2, 3};

    auto oss = std::ostringstream{};

    oss << ints;
    ASSERT_EQ("1, 2, 3", oss.str());
```

下記のようなエラーメッセージが表示される。

```
    logger_0_ut.cpp:140:9: error: no match for ‘operator<<’
        (operand types are ‘std::ostringstream’ {aka ‘std::basic_ostringstream<char>’}
         and ‘App::Ints_t’ {aka ‘std::vector<int>’})
      140 |     oss << ints;
          |     ~~~ ^~ ~~~~
          |     |      |
          |     |      App::Ints_t {aka std::vector<int>}
          |     std::ostringstream {aka std::basic_ostringstream<char>}
```

Ints_tはAppで定義されているが、実際の型はstdで定義されているため、
instsの[関連名前空間](term_explanation.md#SS_19_10_6)もstdであり、Appではない。
その結果App::operator<<は発見できず、このようなエラーになった。

LOGGERからApp::operator<<を使う場合の単体テストは下記のようになるが、
[ADL](term_explanation.md#SS_19_10_5)によってLogging::Logger::set_inner(ints)内に導入される名前空間はstdのみであり、
前記単体テスト同様にコンパイルできない。

```cpp
    //  example/template/logger_0_ints_ut.h 8

    auto ints = App::Ints_t{1, 2, 3};

    LOGGER("Ints", ints);
    auto line_num = __LINE__;

    auto s = Logging::Logger::InstConst().Get();

    auto exp = std::string{log_str_exp(__FILE__, line_num - 1, ":Ints:1, 2, 3\n")};
    ASSERT_EQ(exp, s);
```

この解決方法は、

* [operator\<\<をstd内で宣言する](template_meta_programming.md#SS_13_1_6_1)
* [operator\<\<をグローバル名前空間内で宣言する](template_meta_programming.md#SS_13_1_6_2)
* [operator\<\<をLogging内で宣言する](template_meta_programming.md#SS_13_1_6_3)
* [Logging::Logger::set_inner(ints)内でusing namespace Appを行う](template_meta_programming.md#SS_13_1_6_4)
* [Ints_tを構造体としてApp内に宣言する](template_meta_programming.md#SS_13_1_6_5)
* [operator\<\<を使わない](template_meta_programming.md#SS_13_1_6_6)

のようにいくつか考えられる。以下では、順を追ってこれらの問題点について解説を行う。


#### operator\<\<をstd内で宣言する <a id="SS_13_1_6_1"></a>
ここで解決したい問題は、すでに示した通り、
「[ADL](term_explanation.md#SS_19_10_5)によってLogging::Logger::set_inner(ints)内に導入される名前空間はstdである」
ことにって発生する。であれば、App内でのoperator<<の宣言をstdで行えばコンパイルできるはずである。
下記はその変更を行ったコードである。

```cpp
    //  example/template/app_ints.h 6

    namespace App {
    using Ints_t = std::vector<int>;
    }
```
```cpp
    //  example/template/logger_0_std_ut.cpp 11

    namespace std {  // operator<<の定義をstdで行う
    ostream& operator<<(std::ostream& os, App::Ints_t const& ints)
    {
        auto sep = "";

        for (auto const& i : ints) {
            os << std::exchange(sep, ", ") << i;
        }

        return os;
    }
    }  // namespace std
```

上記コードは[two phase name lookup](term_explanation.md#SS_19_10_3)等の効果により、想定通りコンパイルできるが、
stdをユーザが拡張することは一部の例外を除き未定義動作を引き起こす可能性があり、
たとえこのコードがうまく動作したとしても
(実際、このコードはこのドキュメント作成時には正常動作している)、
未来においてその保証はなく、このようなプログラミングは厳に避けるべきである。


#### operator\<\<をグローバル名前空間内で宣言する <a id="SS_13_1_6_2"></a>
すでに述べた通り、
「ADLによってLogging::Logger::set_inner(ints)内に導入される名前空間はstdのみである」ため、
この関数の中でのname lookupに使用される名前空間は、std、グローバル名前空間、
Loggerを宣言しているLoggingの3つである。

ここでは、下記のコードのようにグローバル名前空間内でのoperator<<の宣言を試す。

```cpp
    //  example/template/app_ints.h 6

    namespace App {
    using Ints_t = std::vector<int>;
    }
```
```cpp
    //  example/template/logger_0_global_ut.cpp 10

    // グローバル名前空間
    std::ostream& operator<<(std::ostream& os, App::Ints_t const& ints)
    {
        auto sep = "";

        for (auto const& i : ints) {
            os << std::exchange(sep, ", ") << i;
        }

        return os;
    }
```

このドキュメントで使用している[g++](term_explanation.md#SS_19_20_1)ではこのコードはコンパイルでき、
動作も問題ないように思われるが、[clang++](term_explanation.md#SS_19_20_2)では以下のようなエラーが発生し、コンパイルできない。

```
    ./logger_0.h:37:21: error: call to function 'operator<<' that is neither 
    visible in the tem plate definition nor found by argument-dependent lookup
            oss_ << ":" << head;
```

この理由は「[two phase name lookup](term_explanation.md#SS_19_10_3)」の後半で詳しく解説したので、ここでは繰り返さないが、
このようなコードを使うと、コード解析ツール等が使用できなくなることがあるため、
避けるべきである
(「[scan-buildによる静的解析](code_analysis.md#SS_4_2)」参照)
。

多くのプログラマは、コードに問題があるとしても、
それが意図通りに動くように見えるのであればその問題を無視する。
今回のような難題に対しては、なおさらそのような邪悪な欲求に負けやすい。
そのような観点でclang++が吐き出したエラーメッセージを眺めると、上記したメッセージの後に、
下記のような出力を見つけるかもしれない。

```
    logger_0_global_ut.cpp:13:15: note: 'operator<<' should be declared prior to the call site
    std::ostream& operator<<(std::ostream& os, App::Ints_t const& ints)
```

clang++は「LOGGERの前にoperator<<を宣言せよ」と言っている。
実際そうすれば、clang++でのコンパイルも通り、単体テストもパスする。
しかし、それには下記のような問題がある。

* operator<<(std::ostream& os, App::Ints_t const& ints)
  という名前空間Appローカルな宣言をグローバル名前空間で行うことによって、
  グローバル名前空間を汚染してしまう
  (このコードは名前空間を正しく使うことに対しての割れ窓
  (「[割れ窓理論](term_explanation.md#SS_19_22_1)」参照)になってしまうかもしれない)。
* 例示したコードでのoperator<<(std::ostream& os, App::Ints_t const& ints)の定義は、
  単体テストファイル内にあったが、実際には何らかのヘッダファイル内で定義されることになる。
  その場合、ロガーのヘッダファイルよりも、
  そのヘッダファイルを先にインクルードしなければならなくなる。
  これは大した問題ではないように見えるが、
  ヘッダファイル間の暗黙の依存関係を生み出し将来の保守作業を難しくさせる。


以上述べた理由からこのアイデアを選択するべきではない。


#### operator\<\<をLogging内で宣言する <a id="SS_13_1_6_3"></a>
前節でのグローバル名前空間内でのoperator<<の宣言はうまく行かなかったので、
同様のことをLoggingで試す。

```cpp
    //  example/template/app_ints.h 6

    namespace App {
    using Ints_t = std::vector<int>;
    }
```
```cpp
    //  example/template/logger_0_logging_ut.cpp 10

    namespace Logging {  // operator<<の定義をLoggingで行う
    std::ostream& operator<<(std::ostream& os, App::Ints_t const& ints)
    {
        auto sep = "";

        for (auto const& i : ints) {
            os << std::exchange(sep, ", ") << i;
        }

        return os;
    }
    }  // namespace Logging
```

動作はするものの、当然ながら結果は「[operator\<\<をグローバル名前空間内で宣言する](template_meta_programming.md#SS_13_1_6_2)」
で述べた状況とほぼ同様であるため、このアイデアを採用することはできない。

#### Logging::Logger::set_inner(ints)内でusing namespace Appを行う <a id="SS_13_1_6_4"></a>
Logging::Logger::set_inner(ints)内でusing namespace Appを行えば、
意図通りに動作させることができるが、App内のロギングは名前空間Loggingに依存するため、
AppとLoggingが循環した依存関係を持ってしまう。
また、LoggingはAppに対して上位概念であるため、[依存関係逆転の原則(DIP)](solid.md#SS_8_5)にも反する。
よって、このアイデアを採用することはできない。

#### Ints_tを構造体としてApp内に宣言する <a id="SS_13_1_6_5"></a>

App::Ints_t用のoperator<<がLogging::Logger::set_inner内でname lookup出来ない理由は、
これまで述べてきたようにApp::Inst_tの[関連名前空間](term_explanation.md#SS_19_10_6)がAppではなく、stdになってしまうからである。

これを回避するためにはその原因を取り払えばよく、
つまり、App::Inst_tの[関連名前空間](term_explanation.md#SS_19_10_6)がAppになるようにすればよい。
これを実現するために、次のコードを試してみる。

```cpp
    //  example/template/logger_0_struct_ut.cpp 10

    namespace App {                     // Ints_tの宣言はApp
    struct Ints_t : std::vector<int> {  // エイリアスではなく、継承を使う
        using vector::vector;           // 継承コンストラクタ
    };

    // App内
    std::ostream& operator<<(std::ostream& os, Ints_t const& ints)
    {
        auto sep = "";

        for (auto const& i : ints) {
            os << std::exchange(sep, ", ") << i;
        }

        return os;
    }
    }  // namespace App
```

上記のコードでは、

* App::Ints_tをstd::vectorからpublic継承
* using宣言によりstd::vectorのすべてのコンストラクタをApp::Ints_tに導入
  (「[継承コンストラクタ](term_explanation.md#SS_19_5_4)」参照)

としているため、エイリアスで宣言されたInts_tと等価である。
C++03では、[継承コンストラクタ](term_explanation.md#SS_19_5_4)が使えなかったため、
上記のような構造体を定義するためには、
std::vectorのすべてのコンストラクタと等価なコンストラクタをApp::Ints_t内に定義することが必要で、
実践的にはこのようなアイデアは使い物にならなかったが、
C++11での改善により、実践的なアイデアとして使用できるようになった。

実際、名前空間の問題もなく、すでに示した単体テストもパスするので有力な候補となるが、
若干の「やりすぎ感」は否めない。


#### operator\<\<を使わない <a id="SS_13_1_6_6"></a>
色々なアイデアを試してみたが、これまでの議論ではこれといった解決方法を発見できなかった。
「[バーニーの祈り](https://ja.wikipedia.org/wiki/%E3%83%8B%E3%83%BC%E3%83%90%E3%83%BC%E3%81%AE%E7%A5%88%E3%82%8A)」
が言っている通り、時にはどうにもならないことを受け入れることも重要である。
LOGGERの中でname lookupできる、エイリアスApp::Ints_tのoperator<<の開発をあきらめ、
ここでは一旦、下記のような受け入れがたいコードを受け入れることにする。


```cpp
    //  example/template/app_ints.h 6

    namespace App {
    using Ints_t = std::vector<int>;
    }
```
```cpp
    //  example/template/logger_0_no_put_to_ut.cpp 10

    namespace App {  // App::Ints_tのoperator<<とToStringをApp内で定義
    namespace {      // operator<<は外部から使わない
    std::ostream& operator<<(std::ostream& os, Ints_t const& ints)
    {
        auto sep = "";

        for (auto const& i : ints) {
            os << std::exchange(sep, ", ") << i;
        }

        return os;
    }
    }  // namespace

    // Ints_tオブジェクトをstd::stringに変換する
    // この変換によりロガーに渡すことができる
    std::string ToString(Ints_t const& inst)
    {
        auto oss = std::ostringstream{};

        oss << inst;

        return oss.str();
    }
    }  // namespace App
```

当然だが、恥を忍んで受け入れたコードにも単体テストは必要である。

```cpp
    //  example/template/logger_0_no_put_to_ut.cpp 44

    auto ints = App::Ints_t{1, 2, 3};

    // ToStringのテスト
    ASSERT_EQ("1, 2, 3", App::ToString(ints));

    // LOGGERのテスト
    LOGGER("Ints", App::ToString(ints));
    auto line_num = __LINE__;

    auto s = Logging::Logger::InstConst().Get();

    auto exp = std::string{log_str_exp(__FILE__, line_num - 1, ":Ints:1, 2, 3\n")};
    ASSERT_EQ(exp, s);
```

上記コードから明らかな通り、App::Ints_tのインスタンスをログ登録する場合、
App::ToString()によりstd::stringへ変換する必要があり、残念なインターフェースとなっている。


#### Ints_tのログ登録のまとめ <a id="SS_13_1_6_7"></a>
製品開発では、満足できる仕様の関数やクラスが作れず、妥協せざるを得ないことはよくあることである。
このような場合、将来、良いアイデアが見つかった時に備えて、
妥協コードを簡単に修正できるようなレベルにした後、捲土重来を期してさっさと退却するのがベストである。
ただし、漫然と過ごしても良いアイデアは浮かばない。
時間を作り、関連書籍やウェブドキュメント等を読み、学習を継続する必要があることは言うまでもない。


## Nstdライブラリの開発 <a id="SS_13_2"></a>

「[operator\<\<を使わない](template_meta_programming.md#SS_13_1_6_6)」で導入したコードは、短いながらも汎用性が高い。
このようなコードをローカルなファイルに閉じ込めてしまうと、
コードクローンや、[車輪の再発明](term_explanation.md#SS_19_22_2)による開発効率の低下につながることがある。

通常、プロジェクトの全ファイルから参照可能で且つ、
プロジェクトの他のパッケージに非依存なパッケージを用意することで、このような問題を回避できる。

ここでは、そのようなパッケージをNstd(not standard library)とし、名前空間も同様に宣言する。
そうした場合、この章の例題で使用している名前空間の依存関係は下記のようになる。

<!-- pu:deep/plant_uml/template_dependency.pu--><p><img src="data:image/png;base64,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" /></p>

このように整理された依存関係は、
「[パッケージとその構成ファイル](programming_convention.md#SS_3_7)」でも述べた通り、
大規模ソフトウェア開発においては特に重要であり、決して循環しないように維持しなければならない。


### Nstdライブラリを使用したリファクタリング <a id="SS_13_2_1"></a>
すでに述べた通り、「[operator\<\<を使わない](template_meta_programming.md#SS_13_1_6_6)」で導入したコードは、Nstdで定義するべきである。
その場合、下記のようにさらに一般化するのが良いだろう。

```cpp
    //  example/template/nstd_0.h 4

    namespace Nstd {

    template <typename T>
    std::ostream& operator<<(std::ostream& os, std::vector<T> const& vec)
    {
        auto sep = "";

        for (auto const& i : vec) {
            os << std::exchange(sep, ", ") << i;
        }

        return os;
    }

    template <typename T>
    std::string ToString(std::vector<T> const& vec)
    {
        auto oss = std::ostringstream{};

        oss << vec;

        return oss.str();
    }
    }  // namespace Nstd
```

その単体テストは下記のようになる。

```cpp
    //  example/template/nstd_0_ut.cpp 13

    auto const ints = App::Ints_t{1, 2, 3};

    {
        auto oss = std::ostringstream{};

        using namespace Nstd;
        oss << ints << 4;
        ASSERT_EQ("1, 2, 34", oss.str());
    }
    {
        auto oss = std::ostringstream{};

        Nstd::operator<<(oss, ints) << 4;  // 念のためこの形式でもテスト
        ASSERT_EQ("1, 2, 34", oss.str());
    }

    ASSERT_EQ("1, 2, 3", Nstd::ToString(ints));
```

勘のいい読者なら、このコードをLOGGERから利用することで、
App:Ints_tのログ登録問題を解消できると思うかもしれない。
実際その通りなのであるが、そうした場合、
std::list等の他のコンテナや配列には対応できないという問題が残るため、
以降もしばらくNstdの開発を続ける。


### 安全なvector <a id="SS_13_2_2"></a>
std::vector、std::basic_string、std::array等の配列型コンテナは、

* operator[]経由でのメンバアクセスについて範囲の妥当性をチェックしない
* 範囲のチェックが必要ならばat()を使用する

という仕様になっているが、
ここではoperator[]にも範囲のチェックを行う配列型コンテナが必要になった場合について考える。

手始めにoperator[]にも範囲のチェックを行うstd::vector相当のコンテナSafeVectorを作ると、
下記のコードのようになる。

```cpp
    //  example/template/safe_vector_ut.cpp 10

namespace Nstd {

template <typename T>
struct SafeVector : std::vector<T> {
    using std::vector<T>::vector;  // 継承コンストラクタ

    using base_type = std::vector<T>;
    using size_type = typename base_type::size_type;

    typename base_type::reference       operator[](size_type i) { return this->at(i); }
    typename base_type::const_reference operator[](size_type i) const { return this->at(i); }
};
}  // namespace Nstd
```

このコードで行ったことは、

* std::vectorからSafeVectorをpublic継承する
* 継承コンストラクタの機能を使い、std::vectorのコンストラクタをSafeVectorで宣言する
* std::vector::atを使い、SafeVector::operator[]を定義する

である。単体テストは下記のようになる。

```cpp
    //  example/template/safe_vector_ut.cpp 30

    {
        auto v = Nstd::SafeVector<int>(10);  // ()での初期化

        ASSERT_EQ(10, v.size());
    }
    {
        auto const v = Nstd::SafeVector<int>{10};

        ASSERT_EQ(1, v.size());
        ASSERT_EQ(10, v[0]);
        ASSERT_THROW(v[1], std::out_of_range);  // エクセプションの発生
    }
    {
        auto v = Nstd::SafeVector<std::string>{"1", "2", "3"};

        ASSERT_EQ(3, v.size());
        ASSERT_EQ((std::vector<std::string>{"1", "2", "3"}), v);
        ASSERT_THROW(v[3], std::out_of_range);  // エクセプションの発生
    }
    {
        auto const v = Nstd::SafeVector<std::string>{"1", "2", "3"};

        ASSERT_EQ(3, v.size());
        ASSERT_EQ((std::vector<std::string>{"1", "2", "3"}), v);
        ASSERT_THROW(v[3], std::out_of_range);  // エクセプションの発生
    }
```

[演習-std::arrayの継承](exercise_q.md#SS_20_11_4)  

### 安全な配列型コンテナ <a id="SS_13_2_3"></a>
配列型コンテナはすでに述べたようにstd::vectorの他にすくなともstd::basic_string、
std::arrayがあるため、それらにも範囲チェックを導入する。

std::basic_stringはstd::vectorとほぼ同様に下記のようになる。

```cpp
    //  example/template/safe_vector_ut.cpp 62
    namespace Nstd {

    struct SafeString : std::string {
        using std::string::string;  // 継承コンストラクタ

        using base_type = std::string;
        using size_type = typename base_type::size_type;

        typename base_type::reference       operator[](size_type i) { return this->at(i); }
        typename base_type::const_reference operator[](size_type i) const { return this->at(i); }
    };
    }  // namespace Nstd
```

std::stringはstd::basic_string\<char>のエイリアスであるため、
上記では、通常使われる形式であるstd::stringを継承したSafeStringを定義した。

この単体テストはSafeVectorの場合と同様に下記のようになる。

```cpp
    //  example/template/safe_vector_ut.cpp 80

    {
        auto s = Nstd::SafeString{"0123456789"};

        ASSERT_EQ(10, s.size());
        ASSERT_EQ("0123456789", s);
        ASSERT_THROW(s[10], std::out_of_range);
    }
    {
        auto const s = Nstd::SafeString(3, 'c');  // ()での初期化が必要

        ASSERT_EQ(3, s.size());
        ASSERT_EQ("ccc", s);
    }
```

std::arrayでは少々事情が異なるが、
std::vectorのコードパターンをそのまま適用すると下記のようになる。

```cpp
    //  example/template/safe_vector_ut.cpp 101

    namespace Nstd {

    template <typename T, size_t N>
    struct SafeArray : std::array<T, N> {
        using std::array<T, N>::array;  // 継承コンストラクタ

        using base_type = std::array<T, N>;
        using size_type = typename base_type::size_type;

        typename base_type::reference       operator[](size_type i) { return this->at(i); }
        typename base_type::const_reference operator[](size_type i) const { return this->at(i); }
    };
    }  // namespace Nstd
```

ただし、この実装には問題がある。

```cpp
    //  example/template/safe_vector_ut.cpp 122

    auto sa_not_init = Nstd::SafeArray<int, 3>{};

    ASSERT_EQ(3, sa_not_init.size());
    ASSERT_THROW(sa_not_init[3], std::out_of_range);
```

上記コードでは、その問題が露見することはないが、以下のコードはコンパイルできない。

```cpp
    //  example/template/safe_vector_ut.cpp 132

    // std::initializer_listを引数とするコンストラクタが未定義
    auto sa_init = Nstd::SafeArray<int, 3>{1, 2, 3};

    // デフォルトコンストラクタがないため、未初期化
    Nstd::SafeArray<int, 3> const sa_const;
```

std::arrayにはコンストラクタが明示的に定義されていないため、
std::arrayにはデフォルトで自動生成される

* デフォルトコンストラクタ
* copyコンストラクタ
* moveコンストラクタ

以外のコンストラクタがないことが原因である。
従って、SafeArray(std::initializer_list)が定義されず前述したようにコンパイルエラーとなる。

この問題に対処したのが以下のコードである。

```cpp
    //  example/template/safe_vector_ut.cpp 146

    namespace Nstd {

    template <typename T, size_t N>
    struct SafeArray : std::array<T, N> {
        using std::array<T, N>::array;  // 継承コンストラクタ
        using base_type = std::array<T, N>;

        template <typename... ARGS>  // コンストラクタを定義
        SafeArray(ARGS... args) : base_type{args...}
        {
        }

        using size_type = typename base_type::size_type;

        typename base_type::reference       operator[](size_type i) { return this->at(i); }
        typename base_type::const_reference operator[](size_type i) const { return this->at(i); }
    };
    }  // namespace Nstd
```

上記コードで注目すべきは、パラメータパックをテンプレートパラメータとしたコンストラクタである。
これにより、前例ではコンパイルすらできなかった下記のような初期化子リストを用いた単体テストが、
このコンストラクタによりパスするようになった。

```cpp
    //  example/template/safe_vector_ut.cpp 181
    {
        auto sa_init = Nstd::SafeArray<int, 3>{1, 2, 3};

        ASSERT_EQ(3, sa_init.size());
        ASSERT_EQ(1, sa_init[0]);
        ASSERT_EQ(2, sa_init[1]);
        ASSERT_EQ(3, sa_init[2]);
        ASSERT_THROW(sa_init[3], std::out_of_range);
    }
    {
        auto const sa_string_const = Nstd::SafeArray<std::string, 5>{"1", "2", "3"};

        ASSERT_EQ(5, sa_string_const.size());
        ASSERT_EQ("1", sa_string_const[0]);
        ASSERT_EQ("2", sa_string_const[1]);
        ASSERT_EQ("3", sa_string_const[2]);
        ASSERT_EQ("", sa_string_const[3]);
        ASSERT_EQ("", sa_string_const[4]);
        ASSERT_THROW(sa_string_const[5], std::out_of_range);
    }
```

この効果を生み出した上記を抜粋した下記のコードには解説が必要だろう。

```cpp
    //  example/template/safe_vector_ut.cpp 155

    template <typename... ARGS>  // コンストラクタを定義
    SafeArray(ARGS... args) : base_type{args...}
    {
    }
```

一般にコンストラクタには「メンバ変数の初期化」と「基底クラスの初期化」が求められるが、
SafeArrayにはメンバ変数が存在しないため、
このコンストラクタの役割は「基底クラスの初期化」のみとなる。
基底クラスstd::array(上記例ではbase_typeにエイリアスしている)
には名前が非規定の配列メンバのみを持つため、
これを初期化するためには初期化子リスト
(「[初期化子リストコンストラクタ](term_explanation.md#SS_19_5_3)」、
「[一様初期化](term_explanation.md#SS_19_5_2)」参照)を用いるのが良い。

ということは、SafeArrayの初期化子リストコンストラクタには、
「基底クラスstd::arrayに初期子リストを与えて初期化する」形式が必要になる。
値を持つパラメータパックは初期化子リストに展開できるため、
ここで必要な形式はパラメータパックとなる。
これを実現したのが上記に抜粋したわずか数行のコードである。


### 初期化子リストの副作用 <a id="SS_13_2_4"></a>
上記SafeArrayの初期化子リストコンストラクタは以下のようなコードを許可しない。

```cpp
    //  example/template/safe_vector_ut.cpp 213
    {
        auto sa_init = Nstd::SafeArray<int, 3>{1.0, 2, 3};

        ASSERT_EQ(3, sa_init.size());
        ASSERT_EQ(1, sa_init[0]);
        ASSERT_EQ(2, sa_init[1]);
        ASSERT_EQ(3, sa_init[2]);
        ASSERT_THROW(sa_init[3], std::out_of_range);
    }
```

このコードをコンパイルすると、

```
    safe_vector_ut.cpp:147:41: error: narrowing conversion of ‘
                                        args#0’ from ‘double’ to ‘int’ -Werror=narrowing]
      147 |     SafeArray(ARGS... args) : base_type{args...}
          |                                         ^~~~
```

のようなエラーが出力されるが、

* double(上記例では1.0)をintに変換する際に縮小変換(narrowing conversio)nが起こる
* 初期化子リストでの縮小変換は許可されない

が原因である。これは意図しない縮小変換によるバグを防ぐ良い機能だと思うが、
ここではテンプレートメタプログラミングのテクニックを解説するため、
あえてこのコンパイルエラーを起こさないSafeArray2を開発する
(言うまでもないが、通常のソフトウェア開発では、
縮小変換によるコンパイルエラーを回避するようなコードを書いてはならない)。

SafeArray2のコードは、

* STLのtype_traitsの使用
* テンプレートの特殊化
* メンバ関数テンプレートとオーバーロードによる静的ディスパッチ(コンパイル時ディスパッチ)
* [SFINAE](term_explanation.md#SS_19_11_1)

等のメタ関数系のテクニックが必要になるため、
まずはこれらを含めたテンプレートのテクニックについて解説し、
その後SafeArray2を見ていくことにする。

## メタ関数のテクニック <a id="SS_13_3"></a>
本章で扱うメタ関数とは、型、定数、クラステンプレート等からなるテンプレート引数から、
型、エイリアス、定数等を宣言、定義するようなクラステンプレート、関数テンプレート、
定数テンプレート、エイリアステンプレートを指す
(本章ではこれらをまとめて単にテンプレート呼ぶことがある)。

[演習-エイリアステンプレート](exercise_q.md#SS_20_11_2)  

### STLのtype_traits <a id="SS_13_3_1"></a>
メタ関数ライブラリの代表的実装例はSTLの
[type_traits](https://cpprefjp.github.io/reference/type_traits.html)である。

ここでは、よく使ういくつかのtype_traitsテンプレートの使用例や解説を示す。


#### std::true_type/std::false_type <a id="SS_13_3_1_1"></a>
std::true_type/std::false_typeは真/偽を返すSTLメタ関数群の戻り型となる型エイリアスであるため、
最も使われるテンプレートの一つである。

これらは、下記で確かめられる通り、後述する[std::integral_constant](template_meta_programming.md#SS_13_3_1_2)を使い定義されている。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 13

    // std::is_same_vの2パラメータが同一であれば、std::is_same_v<> == true
    static_assert(std::is_same_v<std::integral_constant<bool, true>, std::true_type>);
    static_assert(std::is_same_v<std::integral_constant<bool, false>, std::false_type>);
```

それぞれの型が持つvalue定数は、下記のように定義されている。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 20

    static_assert(std::true_type::value, "must be true");
    static_assert(!std::false_type::value, "must be false");
```

これらが何の役に立つのか直ちに理解することは難しいが、
true/falseのメタ関数版と考えれば、追々理解できるだろう。

以下に簡単な使用例を示す。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 29

    // 引数の型がintに変換できるかどうかを判定する関数
    // decltypeの中でのみ使用されるため、定義は不要
    constexpr std::true_type  IsCovertibleToInt(int);  // intに変換できる型はこちら
    constexpr std::false_type IsCovertibleToInt(...);  // それ以外はこちら
```

上記の単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 40

    static_assert(decltype(IsCovertibleToInt(1))::value);
    static_assert(decltype(IsCovertibleToInt(1u))::value);
    static_assert(!decltype(IsCovertibleToInt(""))::value);  // ポインタはintに変換不可

    struct ConvertibleToInt {
        operator int();
    };

    struct NotConvertibleToInt {};

    static_assert(decltype(IsCovertibleToInt(ConvertibleToInt{}))::value);
    static_assert(!decltype(IsCovertibleToInt(NotConvertibleToInt{}))::value);

    // なお、IsCovertibleToInt()やConvertibleToInt::operator int()は実際に呼び出されるわけでは
    // ないため、定義は必要なく宣言のみがあれば良い。
```

IsCovertibleToIntの呼び出しをdecltypeのオペランドにすることで、
std::true_typeかstd::false_typeを受け取ることができる。

#### std::integral_constant <a id="SS_13_3_1_2"></a>
std::integral_constantは
「テンプレートパラメータとして与えられた型とその定数から新たな型を定義する」
クラステンプレートである。

以下に簡単な使用例を示す。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 62

    using int3 = std::integral_constant<int, 3>;

    // std::is_same_vの2パラメータが同一であれば、std::is_same_v<> == true
    static_assert(std::is_same_v<int, int3::value_type>);
    static_assert(std::is_same_v<std::integral_constant<int, 3>, int3::type>);
    static_assert(int3::value == 3);

    using bool_true = std::integral_constant<bool, true>;

    static_assert(std::is_same_v<bool, bool_true::value_type>);
    static_assert(std::is_same_v<std::integral_constant<bool, true>, bool_true::type>);
    static_assert(bool_true::value == true);
```

また、すでに示したようにstd::true_type/std::false_typeを実装するためのクラステンプレートでもある。

#### std::is_same <a id="SS_13_3_1_3"></a>

すでに上記の例でも使用したが、std::is_sameは2つのテンプレートパラメータが

* 同じ型である場合、std::true_type
* 違う型である場合、std::false_type

から派生した型となる。

以下に簡単な使用例を示す。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 99

    static_assert(std::is_same<int, int>::value);
    static_assert(std::is_same<int, int32_t>::value);   // 64ビットg++/clang++
    static_assert(!std::is_same<int, int64_t>::value);  // 64ビットg++/clang++
    static_assert(std::is_same<std::string, std::basic_string<char>>::value);
    static_assert(std::is_same<typename std::vector<int>::reference, int&>::value);
```

また、 C++17で導入されたstd::is_same_vは、定数テンプレートを使用し、
下記のように定義されている。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 90

    template <typename T, typename U>
    constexpr bool is_same_v{std::is_same<T, U>::value};
```

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 108

    static_assert(is_same_v<int, int>);
    static_assert(is_same_v<int, int32_t>);   // 64ビットg++/clang++
    static_assert(!is_same_v<int, int64_t>);  // 64ビットg++/clang++
    static_assert(is_same_v<std::string, std::basic_string<char>>);
    static_assert(is_same_v<typename std::vector<int>::reference, int&>);
```

このような簡潔な記述の一般形式は、

```
   T::value  -> T_v
   T::type   -> T_t
```

のように定義されている(このドキュメントのほとんど場所では、簡潔な形式を用いる)。

第1テンプレートパラメータが第2テンプレートパラメータの基底クラスかどうかを判断する
std::is_base_ofを使うことで下記のようにstd::is_sameの基底クラス確認することもできる。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 117

    static_assert(std::is_base_of_v<std::true_type, std::is_same<int, int>>);
    static_assert(std::is_base_of_v<std::false_type, std::is_same<int, char>>);
```


#### std::enable_if <a id="SS_13_3_1_4"></a>
std::enable_ifは、bool値である第1テンプレートパラメータが

* trueである場合、型である第2テンプレートパラメータをメンバ型typeとして宣言する。
* falseである場合、メンバ型typeを持たない。

下記のコードはクラステンプレートの特殊化を用いたstd::enable_ifの実装例である。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 124

    template <bool T_F, typename T = void>
    struct enable_if;

    template <typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    template <typename T>
    struct enable_if<false, T> {  // メンバエイリアスtypeを持たない
    };

    template <bool COND, typename T = void>
    using enable_if_t = typename enable_if<COND, T>::type;
```

std::enable_ifの使用例を下記に示す。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 148

    static_assert(std::is_same_v<void, std::enable_if_t<true>>);
    static_assert(std::is_same_v<int, std::enable_if_t<true, int>>);
```

実装例から明らかなように

* std::enable_if\<true>::typeは[well-formed](term_explanation.md#SS_19_19_6)
* std::enable_if\<false>::typeは[ill-formed](term_explanation.md#SS_19_19_5)

となるため、下記のコードはコンパイルできない。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 155

    // 下記はill-formedとなるため、コンパイルできない。
    static_assert(std::is_same_v<void, std::enable_if_t<false>>);
    static_assert(std::is_same_v<int, std::enable_if_t<false, int>>);
```

std::enable_ifのこの特性と後述する[SFINAE](term_explanation.md#SS_19_11_1)により、
様々な静的ディスパッチを行うことができる。


#### std::conditional <a id="SS_13_3_1_5"></a>

std::conditionalは、bool値である第1テンプレートパラメータが

* trueである場合、第2テンプレートパラメータ
* falseである場合、第3テンプレートパラメータ

をメンバ型typeとして宣言する。

下記のコードはクラステンプレートの特殊化を用いたstd::conditionalの実装例である。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 164

    template <bool T_F, typename, typename>
    struct conditional;

    template <typename T, typename U>
    struct conditional<true, T, U> {
        using type = T;
    };

    template <typename T, typename U>
    struct conditional<false, T, U> {
        using type = U;
    };

    template <bool COND, typename T, typename U>
    using conditional_t = typename conditional<COND, T, U>::type;
```

std::conditionalの使用例を下記に示す。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 189

    static_assert(std::is_same_v<int, std::conditional_t<true, int, char>>);
    static_assert(std::is_same_v<char, std::conditional_t<false, int, char>>);
```

#### std::is_void <a id="SS_13_3_1_6"></a>
std::is_voidはテンプレートパラメータの型が

* voidである場合、std::true_type
* voidでない場合、std::false_type

から派生した型となる。

以下に簡単な使用例を示す。

```cpp
    //  example/template_cpp17/type_traits_ut.cpp 82

    static_assert(std::is_void<void>::value);
    static_assert(!std::is_void<int>::value);
    static_assert(!std::is_void<std::string>::value);
```

### is_void_xxxの実装 <a id="SS_13_3_2"></a>
ここではstd::is_voidに似た以下のような仕様を持ついくつかのテンプレートis_void_xxxの実装を考える。

|テンプレートパラメータ|戻り値            |
|----------------------|------------------|
|void                  |true              |
|非void                |false             |

それぞれのis_void_xxxは下記テーブルで示した言語機能を使用して実装する。

|is_void_xxx                  |実装方法                                               |
|-----------------------------|-------------------------------------------------------|
|[is_void_f](template_meta_programming.md#SS_13_3_2_1)             |関数テンプレートの特殊化                               |
|[is_void_s](template_meta_programming.md#SS_13_3_2_2)             |クラステンプレートの特殊化                             |
|[is_void_sfinae_f](template_meta_programming.md#SS_13_3_2_3)      |FINAEと関数テンプレートのオーバーロード                |
|[is_void_sfinae_s](template_meta_programming.md#SS_13_3_2_4)      |FINAEとクラステンプレートの特殊化                      |
|[is_void_concept_s](template_meta_programming.md#SS_13_3_2_5)     |コンセプトとクラステンプレートの特殊化                 |
|[is_void_ena_s](template_meta_programming.md#SS_13_3_2_6)         |std::enable_ifによるSFINAEとクラステンプレートの特殊化 |
|[is_void_cond_s](template_meta_programming.md#SS_13_3_2_7)        |std::conditionalと関数テンプレートの特殊化             |

なお、実装例をシンプルに保つため、
理解の妨げとなり得る下記のような正確性(例外条件の対応)等のためのコードを最低限に留めた。

* テンプレートパラメータの型のチェック
* テンプレートパラメータの型からのポインタ/リファレンス/const/volatileの削除
* 戻り型からのconst/volatileの削除

これは、「テンプレートプログラミングでの有用なテクニックの解説」
というここでの目的を見失わないための措置である。


#### is_void_f <a id="SS_13_3_2_1"></a>
関数テンプレートの特殊化を使用したis_void_fの実装は以下のようになる。

```cpp
    //  example/template/is_void_ut.cpp 8

    template <typename T>
    constexpr bool is_void_f() noexcept
    {
        return false;
    }

    template <>
    constexpr bool is_void_f<void>() noexcept
    {
        return true;
    }

    template <typename T>
    constexpr bool is_void_f_v{is_void_f<T>()};
```

単純なので解説は不要だろう。これらの単体テストは下記のようになる。

```cpp
    //  example/template/is_void_ut.cpp 28

    static_assert(!is_void_f_v<int>);
    static_assert(!is_void_f_v<std::string>);
    static_assert(is_void_f_v<void>);
```

関数テンプレートの特殊化には、

* 特殊化された関数テンプレートとそのプライマリテンプレートのシグネチャ、
  戻り値は一致しなければならない
* クラステンプレートのような部分特殊化は許可されない

のような制限があるため用途は限られるが、関数テンプレートはオーバーロードすることが可能である。

[演習-SFINAEを利用しない関数テンプレートの特殊化によるis_void](exercise_q.md#SS_20_11_5)

#### is_void_s <a id="SS_13_3_2_2"></a>
クラステンプレートの特殊化を使用したis_void_sの実装は以下のようになる。

```cpp
    //  example/template/is_void_ut.cpp 36

    template <typename T>
    struct is_void_s {
        static constexpr bool value{false};
    };

    template <>
    struct is_void_s<void> {
        static constexpr bool value{true};
    };

    template <typename T>
    constexpr bool is_void_s_v{is_void_s<T>::value};
```

is_void_fと同様に単純なので解説は不要だろう。これらの単体テストは下記のようになる。

```cpp
    //  example/template/is_void_ut.cpp 54

    static_assert(!is_void_s_v<int>);
    static_assert(!is_void_s_v<std::string>);
    static_assert(is_void_s_v<void>);
```

[演習-SFINAEを利用しないクラステンプレートの特殊化によるis_void](exercise_q.md#SS_20_11_6)

#### is_void_sfinae_f <a id="SS_13_3_2_3"></a>
[SFINAE](term_explanation.md#SS_19_11_1)を使用した関数テンプレートis_void_sfinae_fの実装は以下のようになる。

```cpp
    //  example/template/is_void_ut.cpp 62

    namespace Inner_ {

    // T == void
    template <typename T>
    constexpr auto is_void_sfinae_f_detector(void const* v, T const* t) noexcept
        -> decltype(t = v, bool{})  // T != voidの場合、t = vはill-formed
                                    // T == voidの場合、well-formedでbool型生成
    {
        return true;
    }

    // T != void
    template <typename T>
    constexpr auto is_void_sfinae_f_detector(void const*, T const*) noexcept
        -> decltype(sizeof(T), bool{})  // T != voidの場合、well-formedでbool型生成
                                        // T == voidの場合、sizeof(T)はill-formed
    {
        return false;
    }
    }  // namespace Inner_

    template <typename T>
    constexpr bool is_void_sfinae_f() noexcept
    {
        return Inner_::is_void_sfinae_f_detector(nullptr, static_cast<T*>(nullptr));
    }

    template <typename T>
    constexpr bool is_void_sfinae_f_v{is_void_sfinae_f<T>()};
```

関数テンプレートである2つのis_void_sfinae_f_detectorのオーバーロードにSFINAEを使用している。

1つ目のis_void_sfinae_f_detectorでは、

| T       | t = v の診断(コンパイル) |
|---------|--------------------------|
| == void | well-formed              |
| != void | ill-formed               |

であるため、Tがvoidの時のみ[name lookup](term_explanation.md#SS_19_10_2)の対象になる。

2つ目のis_void_sfinae_f_detectorでは、

| T       | sizeof(T)の診断(コンパイル) |
|---------|-----------------------------|
| == void | ill-formed                  |
| != void | well-formed                 |

であるため、Tが非voidの時のみ[name lookup](term_explanation.md#SS_19_10_2)の対象になる。

is_void_sfinae_fはこの性質を利用し、

* T == voidの場合、1つ目のis_void_sfinae_f_detectorが選択され、戻り値はtrue
* T != voidの場合、2つ目のis_void_sfinae_f_detectorが選択され、戻り値はfalse

となる。念のため単体テストを示すと下記のようになる。

```cpp
    //  example/template/is_void_ut.cpp 97

    static_assert(!is_void_sfinae_f_v<int>);
    static_assert(!is_void_sfinae_f_v<std::string>);
    static_assert(is_void_sfinae_f_v<void>);
```

一般にファイル外部に公開するテンプレートは、
コンパイルの都合上ヘッダファイルにその全実装を記述することになる。
これは、本来外部公開すべきでない実装の詳細である
is_void_sfinae_f_detectorのようなテンプレートに関しては大変都合が悪い。
というのは、外部から使用されたくない実装の詳細が使われてしまうことがあり得るからである。
上記の例では、こういうことに備え
「これは外部非公開である」ということを示す名前空間Inner\_
(「[名前空間](programming_convention.md#SS_3_8_2)」参照)
を導入した。

関数テンプレートはクラステンプレート内にも定義することができるため、
is_void_sfinae_fは下記のように実装することも可能である。この場合、名前空間Inner\_は不要になる。

```cpp
    //  example/template/is_void_ut.cpp 106

    template <typename T>
    class is_void_sfinae_f {
        // U == void
        template <typename U>
        static constexpr auto detector(void const* v, U const* u) noexcept
            -> decltype(u = v, bool{})  // U != voidの場合、t = vはill-formed
                                        // U == voidの場合、well-formedでbool型生成
        {
            return true;
        }

        // U != void
        template <typename U>
        static constexpr auto detector(void const*, U const*) noexcept
            -> decltype(sizeof(U), bool{})  // U != voidの場合、well-formedでbool型生成
                                            // U == voidの場合、ill-formed
        {
            return false;
        }

    public:
        static constexpr bool value{is_void_sfinae_f::detector(nullptr, static_cast<T*>(nullptr))};
    };

    template <typename T>
    constexpr bool is_void_sfinae_f_v{is_void_sfinae_f<T>::value};
```

```cpp
    //  example/template/is_void_ut.cpp 138

    static_assert(!is_void_sfinae_f_v<int>);
    static_assert(!is_void_sfinae_f_v<std::string>);
    static_assert(is_void_sfinae_f_v<void>);
```

[演習-SFINAEを利用した関数テンプレートの特殊化によるis_void](exercise_q.md#SS_20_11_7)

#### is_void_sfinae_s <a id="SS_13_3_2_4"></a>
[SFINAE](term_explanation.md#SS_19_11_1)を使用したクラステンプレートis_void_sfinae_sの実装は以下のようになる。

```cpp
    //  example/template/is_void_ut.cpp 147

    namespace Inner_ {
    template <typename T>
    T*& t2ptr();  // 定義は不要
    }  // namespace Inner_

    template <typename T, typename = void*&>
    struct is_void_sfinae_s : std::false_type {
    };

    template <typename T>
    struct is_void_sfinae_s<
        T,
        // T != voidの場合、ill-formed
        // T == voidの場合、well-formedでvoid*&生成
        decltype(Inner_::t2ptr<T>() = Inner_::t2ptr<void>())

        > : std::true_type {
    };

    template <typename T>
    constexpr bool is_void_sfinae_s_v{is_void_sfinae_s<T>::value};
```

1つ目のis_void_sfinae_sはプライマリテンプレートである。
is_void_sfinae_sの特殊化が[name lookup](term_explanation.md#SS_19_10_2)の対象の中に見つからなかった場合、
これが使われる。

2つ目のis_void_sfinae_sは、上記を抜粋した下記のコード

```cpp
    //  example/template/is_void_ut.cpp 163

    // T != voidの場合、ill-formed
    // T == voidの場合、well-formedでvoid*&生成
    decltype(Inner_::t2ptr<T>() = Inner_::t2ptr<void>())
```

がT == voidの時のみ、well-formedになり、このテンプレートは下記のようにインスタンス化される。

```cpp
    struct is_void_sfinae_s<void, void*&>
```

この形状はプライマリテンプレートの

* 第1パラメータにvoidを与える
* 第2パラメータには何も与えない(デフォルトのまま)

とした場合の、つまりプライマリテンプレートを

```cpp
    struct is_void_sfinae_s<void>   // プライマリテンプレート
```

としてインスタンス化した場合と一致する。
プライマリと特殊化が一致した場合、特殊化されたものがname lookupで選択される。

T != voidの場合、 2つ目のis_void_sfinae_sはill-formedになり、name lookupの対象から外れるため、
プライマリが選択される。

以上をまとめると、

| T       | is_void_sfinae_sの基底クラス |
|---------|------------------------------|
| == void | std::true_type               |
| != void | std::false_type              |

となる。以下の単体テストによって、このことを確かめることができる。

```cpp
    //  example/template/is_void_ut.cpp 180

    static_assert(!is_void_sfinae_s_v<int>);
    static_assert(std::is_base_of_v<std::false_type, is_void_sfinae_s<int>>);

    static_assert(!is_void_sfinae_s_v<std::string>);
    static_assert(std::is_base_of_v<std::false_type, is_void_sfinae_s<std::string>>);

    static_assert(is_void_sfinae_s_v<void>);
    static_assert(std::is_base_of_v<std::true_type, is_void_sfinae_s<void>>);
```

上記コードのように「プライマリテンプレートのデフォルトパラメータ」と、

```cpp
    //  example/template/is_void_ut.cpp 163

    // T != voidの場合、ill-formed
    // T == voidの場合、well-formedでvoid*&生成
    decltype(Inner_::t2ptr<T>() = Inner_::t2ptr<void>())
```

が「well-formedであった場合に生成される型」が一致することを利用した静的ディスパッチは、
SFINAEとクラステンプレートの特殊化を組み合わせたメタ関数の典型的な実装パターンである。
ただし、一般にはill-formedを起こすためにst::enable_ifを使うことが多いため、
「[is_void_ena_s](template_meta_programming.md#SS_13_3_2_6)の実装」でその例を示す。

[演習-SFINAEを利用したクラステンプレートの特殊化によるis_void](exercise_q.md#SS_20_11_8)

#### is_void_concept_s <a id="SS_13_3_2_5"></a>
[is_void_sfinae_s](template_meta_programming.md#SS_13_3_2_4)の実装で使用したSFINAEを回避し、
コンセプトを使用することで可読性の向上が見込める。
以下の実装で使用した[same_as](template_meta_programming.md#SS_13_3_3_6)は\<concepts>で定義されているコンセプトと同様のものである。

```cpp
    //  example/template/is_void_ut.cpp 193

    template <typename T>
    struct is_void_concept_s : std::false_type {
    };

    template <typename T>
    requires std::same_as<T, void>  // コンセプトによるTの制約
    struct is_void_concept_s<T> : std::true_type {
    };
```
```cpp
    //  example/template/is_void_ut.cpp 207

    static_assert(!is_void_concept_s<int>::value);
    static_assert(std::is_base_of_v<std::false_type, is_void_concept_s<int>>);

    static_assert(!is_void_concept_s<std::string>::value);
    static_assert(std::is_base_of_v<std::false_type, is_void_concept_s<std::string>>);

    static_assert(is_void_concept_s<void>::value);
    static_assert(std::is_base_of_v<std::true_type, is_void_concept_s<void>>);
```

下記に示した通り、テンプレート特殊化はクラスのみなく定数に対しても使用することができる。

```cpp
    //  example/template/is_void_ut.cpp 220

    template <typename T>
    constexpr bool is_void_concept_s_v = false;

    template <typename T>
    requires std::same_as<T, void>
    constexpr bool is_void_concept_s_v<T> = true;
```

以下に示した通り、[is_void_sfinae_s](template_meta_programming.md#SS_13_3_2_4)の実装で示した定数テンプレートのテストと同様になっている。

```cpp
    //  example/template/is_void_ut.cpp 232

    static_assert(!is_void_concept_s_v<int>);
    static_assert(!is_void_concept_s_v<std::string>);
    static_assert(is_void_concept_s_v<void>);
```

#### is_void_ena_s <a id="SS_13_3_2_6"></a>
[std::enable_if](template_meta_programming.md#SS_13_3_1_4)による[SFINAE](term_explanation.md#SS_19_11_1)とクラステンプレートの特殊化を使用した
is_void_ena_sの実装は以下のようになる。

```cpp
    //  example/template/is_void_ut.cpp 240
    template <typename T, typename = void>
    struct is_void_ena_s : std::false_type {
    };

    template <typename T>
    struct is_void_ena_s<
        T,
        typename std::enable_if_t<is_void_f<T>()>
        > : std::true_type {
    };

    template <typename T>
    constexpr bool is_void_ena_s_v{is_void_ena_s<T>::value};
```

この例では、「[is_void_sfinae_s](template_meta_programming.md#SS_13_3_2_4)の実装」の

```cpp
    //  example/template/is_void_ut.cpp 163

    // T != voidの場合、ill-formed
    // T == voidの場合、well-formedでvoid*&生成
    decltype(Inner_::t2ptr<T>() = Inner_::t2ptr<void>())
```

で示したSFINAEの処理を上記を抜粋した下記のコード

```cpp
    //  example/template/is_void_ut.cpp 250

    typename std::enable_if_t<is_void_f<T>()>
```

で行っている。
std::enable_ifの値パラメータis_void_f\<T>()は、「[is_void_f](template_meta_programming.md#SS_13_3_2_1)の実装」で示したものである。

単体テストは、「[is_void_sfinae_s](template_meta_programming.md#SS_13_3_2_4)の実装」で示したものとほぼ同様で、以下のようになる。

```cpp
    //  example/template/is_void_ut.cpp 264

    static_assert(!is_void_ena_s_v<int>);
    static_assert(std::is_base_of_v<std::false_type, is_void_ena_s<int>>);

    static_assert(!is_void_ena_s_v<std::string>);
    static_assert(std::is_base_of_v<std::false_type, is_void_ena_s<std::string>>);

    static_assert(is_void_ena_s_v<void>);
    static_assert(std::is_base_of_v<std::true_type, is_void_ena_s<void>>);
```


#### is_void_cond_s <a id="SS_13_3_2_7"></a>
[std::conditional](template_meta_programming.md#SS_13_3_1_5)と関数テンプレートの特殊化を使用したis_void_cond_sの実装は以下のようになる。

```cpp
    //  example/template/is_void_ut.cpp 277
    template <typename T>
    struct is_void_cond_s : std::conditional_t<is_void_f<T>(), std::true_type, std::false_type> {
    };

    template <typename T>
    constexpr bool is_void_cond_s_v{is_void_cond_s<T>::value};
```

std::conditionalの値パラメータis_void_f\<T>()は、「[is_void_f](template_meta_programming.md#SS_13_3_2_1)の実装」で示したものである。
この例では、SFINAEもクラステンプレートの特殊化も使用していないが、
下記単体テストからわかる通り、「[is_void_sfinae_s](template_meta_programming.md#SS_13_3_2_4)の実装」と同じ機能を備えている。

```cpp
    //  example/template/is_void_ut.cpp 288

    static_assert(!is_void_cond_s_v<int>);
    static_assert(std::is_base_of_v<std::false_type, is_void_cond_s<int>>);

    static_assert(!is_void_cond_s_v<std::string>);
    static_assert(std::is_base_of_v<std::false_type, is_void_cond_s<std::string>>);

    static_assert(is_void_cond_s_v<void>);
    static_assert(std::is_base_of_v<std::true_type, is_void_cond_s<void>>);
```


### is_same_xxxの実装 <a id="SS_13_3_3"></a>
ここではstd::is_same\<T, U>に似た、
以下のような仕様を持ついくつかのテンプレートis_same_xxxの実装を考える。

|テンプレートパラメータ|戻り値            |
|----------------------|------------------|
|T == U                |true              |
|T != U                |false             |

それぞれのis_same_xxxは下記テーブルで示された言語機能を使用して実装する。

|is_same_xxx                   |実装方法                                               |
|------------------------------|-------------------------------------------------------|
|[is_same_f](template_meta_programming.md#SS_13_3_3_1)              |関数テンプレートのオーバーロード                       |
|[is_same_v](template_meta_programming.md#SS_13_3_3_2)              |定数テンプレートの特殊化                               |
|[is_same_s](template_meta_programming.md#SS_13_3_3_3)              |クラステンプレートの特殊化                             |
|[is_same_sfinae_f](template_meta_programming.md#SS_13_3_3_4)       |SFINAEと関数テンプレート/関数のオーバーロード          |
|[is_same_sfinae_s](template_meta_programming.md#SS_13_3_3_5)       |SFINAEとクラステンプレートの特殊化                     |
|[same_as](template_meta_programming.md#SS_13_3_3_6)                |[コンセプト](term_explanation.md#SS_19_11_2)よるis_same_sfinae_sと同一の機能      |
|[is_same_templ](template_meta_programming.md#SS_13_3_3_7)          |テンプレートテンプレートパラメータ                     |
|[IsSameSomeOf](template_meta_programming.md#SS_13_3_3_8)           |パラメータパックと再帰                                 |
|[OneOf](template_meta_programming.md#SS_13_3_3_9)                  |IsSameSomeOfをコンセプトに                             |

#### is_same_f <a id="SS_13_3_3_1"></a>
関数テンプレートのオーバーロードを用いたis_same_fの実装は以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 9

    template <typename T, typename U>
    constexpr bool is_same_f_helper(T const*, U const*) noexcept
    {
        return false;
    }

    template <typename T>
    constexpr bool is_same_f_helper(T const*, T const*) noexcept
    {
        return true;
    }

    template <typename T, typename U>
    constexpr bool is_same_f() noexcept
    {
        return is_same_f_helper(static_cast<T*>(nullptr), static_cast<U*>(nullptr));
    }

    template <typename T, typename U>
    constexpr bool is_same_f_v{is_same_f<T, U>()};
```

すでに述べたように関数テンプレートの部分特殊化は言語仕様として認められておらず、

```cpp
    //  example/template_cpp17/is_same_ut.cpp 34

    template <typename T, typename U>
    constexpr bool is_same_f()
    {
        return true;
    }

    template <typename T>
    constexpr bool is_same_f<T, T>()
    {
        return true;
    }
```

上記のようなのようなコードは、以下のようなコンパイルエラーになる
(g++/clang++のような優れたコンパイラを使えば、
以下のメッセージのように簡単に問題点が理解できることもある)。

```
    is_same_ut.cpp:35:32: error: non-class, non-variable partial specialization ‘
                                          is_same_f<T, T>’ is not allowed
        35 | constexpr bool is_same_f<T, T>()
```

関数テンプレートは部分特殊化が出来ない代わりに、
同じ識別子を持つ関数や関数テンプレートとのオーバーロードができる。関数とのオーバーロードの場合、
is_same_f_helper\<T>()のようなテンプレートパラメータを直接使用した静的ディスパッチが出来ないため、
常に型推測によるディスパッチが必要になる。

単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 52

    static_assert(!is_same_f_v<int, void>);
    static_assert(is_same_f_v<int, int>);
    static_assert(!is_same_f_v<int, uint32_t>);
    static_assert(is_same_f_v<std::string, std::basic_string<char>>);
```

#### is_same_v <a id="SS_13_3_3_2"></a>
定数テンプレートの特殊化を用いたis_same_vの実装は以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 61

    template <typename T, typename U>
    constexpr bool is_same_v{false};

    template <typename T>
    constexpr bool is_same_v<T, T>{true};
```

単純であるため、解説は不要だろう。 単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 72

    static_assert(!is_same_v<int, void>);
    static_assert(is_same_v<int, int>);
    static_assert(!is_same_v<int, uint32_t>);
    static_assert(is_same_v<std::string, std::basic_string<char>>);
```


#### is_same_s <a id="SS_13_3_3_3"></a>
クラステンプレートの特殊化を用いたis_same_sの実装は以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 81

    template <class T, class U>
    struct is_same_s : std::false_type {
    };

    template <class T>
    struct is_same_s<T, T> : std::true_type {
    };

    template <typename T, typename U>
    constexpr bool is_same_s_v{is_same_s<T, U>::value};
```

「[is_same_v](template_meta_programming.md#SS_13_3_3_2)の実装」と同様に単純であるため、解説は不要だろう。 単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 97

    static_assert(!is_same_s_v<int, void>);
    static_assert(is_same_s_v<int, int>);
    static_assert(!is_same_s_v<int, uint32_t>);
    static_assert(is_same_s_v<std::string, std::basic_string<char>>);
```


#### is_same_sfinae_f <a id="SS_13_3_3_4"></a>
SFINAEと関数テンプレート/関数のオーバーロードを用いたis_same_sfinae_f実装は以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 106

    namespace Inner_ {
    template <typename T, typename U>
    constexpr auto is_same_sfinae_f_detector(T const* t, U const* u) noexcept
        -> decltype(t = u, u = t, bool{})  // T != Uの場合、t = u, u = tはill-formed
                                           // T == Uの場合、well-formedでbool型生成
    {
        return true;
    }

    constexpr bool is_same_sfinae_f_detector(...) noexcept { return false; }
    }  // namespace Inner_

    template <typename T, typename U>
    constexpr bool is_same_sfinae_f() noexcept
    {
        return Inner_::is_same_sfinae_f_detector(static_cast<T*>(nullptr), static_cast<U*>(nullptr));
    }

    template <typename T, typename U>
    constexpr bool is_same_sfinae_f_v{is_same_sfinae_f<T, U>()};
```

上記の抜粋である下記コードのコメントで示したように、

```cpp
    //  example/template_cpp17/is_same_ut.cpp 112

    -> decltype(t = u, u = t, bool{})  // T != Uの場合、t = u, u = tはill-formed
                                       // T == Uの場合、well-formedでbool型生成
```

T != Uの場合、この関数テンプレートはill-formedとなりname lookupの対象ではなくなる。
その結果、関数is_same_sfinae_f_detectorが選択される。
省略記号"..."(ellipsis)を引数とする関数は、そのオーバーロード群の中での最後の選択となるため、
T == Uの場合は、関数テンプレートis_same_sfinae_f_detectorが選択される。

単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 136

    static_assert(!is_same_sfinae_f_v<int, void>);
    static_assert(is_same_sfinae_f_v<int, int>);
    static_assert(!is_same_sfinae_f_v<int, uint32_t>);
    static_assert(is_same_sfinae_f_v<std::string, std::basic_string<char>>);
```

#### is_same_sfinae_s <a id="SS_13_3_3_5"></a>
SFINAEとクラステンプレートの特殊化を用いたis_same_sfinae_sの実装は以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 144

    namespace Inner_ {
    template <typename T>
    T*& t2ptr();
    }

    template <typename T, typename U, typename = T*&>
    struct is_same_sfinae_s : std::false_type {
    };

    template <typename T, typename U>
    struct is_same_sfinae_s<
        T, U,

        // T != Uの場合、ill-formed
        // T == Uの場合、well-formedでT*&生成
        decltype(Inner_::t2ptr<T>() = Inner_::t2ptr<U>(), Inner_::t2ptr<U>() = Inner_::t2ptr<T>())
        > : std::true_type {
    };

    template <typename T, typename U>
    constexpr bool is_same_sfinae_s_v{is_same_sfinae_s<T, U>::value};
```

「[is_void_sfinae_s](template_meta_programming.md#SS_13_3_2_4)の実装」とほぼ同様であるため、解説は不要だろう。 
単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 172

    static_assert(!is_same_sfinae_s_v<int, void>);
    static_assert(is_same_sfinae_s_v<int, int>);
    static_assert(!is_same_sfinae_s_v<int, uint32_t>);
    static_assert(is_same_sfinae_s_v<std::string, std::basic_string<char>>);
```

#### same_as <a id="SS_13_3_3_6"></a>
[SFINAE](term_explanation.md#SS_19_11_1)による[is_same_sfinae_s](template_meta_programming.md#SS_13_3_3_5)の難解なコードを[コンセプト](term_explanation.md#SS_19_11_2)
よりリファクタリングしたコードを以下に示す。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 181

    #if __cplusplus >= 202002L  // c++20
    template <typename T, typename U>
    concept same_as = requires(T const* t, U const* u)
    {
        {t = u, u = t};
    };

    #else  // c++17
    template <typename T, typename U>
    inline constexpr bool same_as = is_same_sfinae_s_v<T, U>;

    #endif
```
is_same_sfinae_sは定数テンプレートであり、same_asはコンセプトであるが、
下記のテストから明らかな通り、ほぼ同様に同様に使用することができる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 196

    static_assert(!same_as<int, void>);
    static_assert(same_as<int, int>);
    static_assert(!same_as<int, uint32_t>);
    static_assert(same_as<std::string, std::basic_string<char>>);
```

「[is_same_s](template_meta_programming.md#SS_13_3_3_3)」で紹介した特殊化のテクニックを下記のように使用することができる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 203

    #if __cplusplus >= 202002L  // c++20
    template <typename T, typename U>
    struct is_same_concept_s : std::false_type {
    };

    template <typename T, typename U>
    requires same_as<T, U>
    struct is_same_concept_s<T, U> : std::true_type {
    };

    #else  // c++17
    template <typename T, typename U, typename = void>
    struct is_same_concept_s : std::false_type {
    };

    template <typename T, typename U>
    struct is_same_concept_s<T, U, std::enable_if_t<same_as<T, U>, void>> : std::true_type {
    };

    #endif

    static_assert(!is_same_concept_s<int, void>::value);
    static_assert(is_same_concept_s<int, int>::value);
    static_assert(!is_same_concept_s<int, uint32_t>::value);
    static_assert(is_same_concept_s<std::string, std::basic_string<char>>::value);
```

#### is_same_templ <a id="SS_13_3_3_7"></a>
例えば、std::stringとstd::basic_string\<T>が同じもしくは違う型であることを確認するためには、
すでに示したis_same_sを使用し、

```cpp
    //  example/template_cpp17/is_same_ut.cpp 246

    static_assert(is_same_s_v<std::string, std::basic_string<char>>);
    static_assert(!is_same_s_v<std::string, std::basic_string<signed char>>);
```

のようにすればよいが、
以下に示したコードのようにテンプレートテンプレートパラメータを使うことでも実装できる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 234

    template <typename T, template <class...> class TEMPL, typename... ARGS>
    struct is_same_templ : is_same_sfinae_s<T, TEMPL<ARGS...>> {
    };

    template <typename T, template <class...> class TEMPL, typename... ARGS>
    constexpr bool is_same_templ_v{is_same_templ<T, TEMPL, ARGS...>::value};
```

上記のis_same_templは、第2引数にクラステンプレート、
第3引数以降にそのクラステンプレートの1個以上の引数を取ることができる。
使用例を兼ねた単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 251

    static_assert(is_same_templ_v<std::string, std::basic_string, char>);
    static_assert(!is_same_templ_v<std::string, std::basic_string, signed char>);
```

これを応用したエイリアステンプレート

```cpp
    //  example/template_cpp17/is_same_ut.cpp 258

    template <typename T>
    using gen_std_string = is_same_templ<std::string, std::basic_string, T>;

    template <typename T>
    constexpr bool gen_std_string_v{gen_std_string<T>::value};
```

は与えられたテンプレートパラメータがstd::stringを生成するかどうかを判定することができる。

```cpp
    //  example/template_cpp17/is_same_ut.cpp 269

    static_assert(gen_std_string_v<char>);
    static_assert(!gen_std_string_v<signed char>);
```

[演習-テンプレートテンプレートパラメータ](exercise_q.md#SS_20_11_9)

#### IsSameSomeOf <a id="SS_13_3_3_8"></a>
IsSameSomeOfはこれまでの例とは少々異なり、

* 第1パラメータが第2パラメータ以降で指定された型のどれかと一致する
  SameAsSomeOfという名前の[コンセプト](term_explanation.md#SS_19_11_2)を[畳み込み式](term_explanation.md#SS_19_11_3)を使用し定義する
* SameAsSomeOfで制約したテンプレートパラメータをstd::bool_constantからIsSameSomeOfを派生させる

のような特徴のを持つ。
このようなIsSameSomeOfの実装はは以下のようになる。

```cpp
    //  example/h/nstd_type_traits.h 13

    namespace Nstd {
    namespace Inner_ {
    template <typename T, typename U, typename... Us>
    struct is_same_as_some_of_impl {  // 型特性の補助クラス: 複数の型と比較する再帰的な実装
        static constexpr bool value = std::is_same<T, U>::value || is_same_as_some_of_impl<T, Us...>::value;
    };

    // 再帰の終端条件: 比較する型が1つの場合
    template <typename T, typename U>
    struct is_same_as_some_of_impl<T, U> {
        static constexpr bool value = std::is_same<T, U>::value;
    };
    }  // namespace Inner_

    #if __cplusplus >= 202002L  // c++20
    // コンセプト: 複数の型のいずれかがTと同じかどうかをチェック
    template <typename T, typename U, typename... Us>
    concept SameAsSomeOf = (std::same_as<T, U> || (std::same_as<T, Us> || ...));

    #else  // c++17
    // コンセプトが使えない場合、上と同じ機能を持つ変数テンプレート
    template <typename T, typename U, typename... Us>
    constexpr bool SameAsSomeOf = Inner_::is_same_as_some_of_impl<T, U, Us...>::value;
    #endif

    // 型特性: TがUsのいずれかと同じ場合true_type、そうでない場合false_typeを継承
    template <typename T, typename U, typename... Us>
    struct IsSameSomeOf : std::bool_constant<SameAsSomeOf<T, U, Us...>> {
    };

    // 便利な定数テンプレート
    template <typename T, typename U, typename... Us>
    constexpr bool IsSameSomeOfV = IsSameSomeOf<T, U, Us...>::value;
    }  // namespace Nstd
```

IsSameSomeOfは、TがUsのいずれかと一致するかどうかのほとんどの処理をSameAsSomeOfに移譲する。

Usが1つだった場合、SameAsSomeOfは処理をstd::same_as(「[same_as](template_meta_programming.md#SS_13_3_3_6)」参照)に委譲する。
Usが複数だった場合、[畳み込み式](--)を使用し上記の処理をその数分、繰り返す。

単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/nstd_type_traits_ut.cpp 14

    static_assert(!Nstd::IsSameSomeOfV<int, int8_t, int16_t, uint16_t>);
    static_assert(Nstd::IsSameSomeOfV<int, int8_t, int16_t, uint16_t, int32_t>);
    static_assert(Nstd::IsSameSomeOfV<int&, int8_t, int16_t, int32_t&, int32_t>);
    static_assert(!Nstd::IsSameSomeOfV<int&, int8_t, int16_t, uint32_t&, int32_t>);
    static_assert(Nstd::IsSameSomeOfV<std::string, int, char*, std::string>);
    static_assert(!Nstd::IsSameSomeOfV<std::string, int, char*>);
```

[演習-テンプレートパラメータを可変長にしたstd::is_same](exercise_q.md#SS_20_11_10)

#### OneOf <a id="SS_13_3_3_9"></a>
OneOfは、[IsSameSomeOf](template_meta_programming.md#SS_13_3_3_8)同様の機能を持つコンセプトである。
OneOfの実装にはシンプルに記述するための[畳み込み式](term_explanation.md#SS_19_11_3)を使用した。

```cpp
    //  h/nstd_concepts.h 52

    template <typename T, typename... Us>
    concept OneOf = (std::same_as<T, Us> || ...);
```
単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/nstd_type_traits_ut.cpp 29

    static_assert(!Nstd::OneOf<int, int8_t, int16_t, uint16_t>);
    static_assert(Nstd::OneOf<int, int8_t, int16_t, uint16_t, int32_t>);
    static_assert(Nstd::OneOf<int&, int8_t, int16_t, int32_t&, int32_t>);
    static_assert(!Nstd::OneOf<int&, int8_t, int16_t, uint32_t&, int32_t>);
    static_assert(Nstd::OneOf<std::string, int, char*, std::string>);
    static_assert(!Nstd::OneOf<std::string, int, char*>);
```

### AreConvertibleXxxの実装 <a id="SS_13_3_4"></a>
std::is_convertible\<FROM, TO>は、

* 型FROMが型TOに変換できる場合、std::true_typeから派生する
* 型FROMが型TOに変換できない場合、std::false_typeから派生する

のような仕様を持つテンプレートである。

ここでは、

* std::is_convertibleを複数のFROMが指定できるように拡張したNstd::AreConvertible
* 縮小無しでの型変換ができるかどうかを判定するAreConvertibleWithoutNarrowConv

の実装を考える。

|AreConvertibleXxx                     |実装方法                                     |
|--------------------------------------|---------------------------------------------|
|[AreConvertible](template_meta_programming.md#SS_13_3_4_1)                 |クラステンプレートの特殊化                   |
|[ConvertibleToAll](template_meta_programming.md#SS_13_3_4_3)               |AreConvertibleをコンセプトへ                 |
|[AreConvertibleWithoutNarrowConv](template_meta_programming.md#SS_13_3_4_2)|SFINAEとクラステンプレートの特殊化           |
|[ConvertibleWithoutNarrowing](template_meta_programming.md#SS_13_3_4_4)    |AreConvertibleWithoutNarrowConvをコンセプトへ|


#### AreConvertible <a id="SS_13_3_4_1"></a>
AreConvertibleの実装は以下のようになる。

```cpp
    //  example/h/nstd_type_traits.h 53

    namespace Nstd {
    namespace Inner_ {

    template <typename TO, typename FROM, typename... FROMs>
    struct are_convertible {
        static constexpr bool value{std::is_convertible_v<FROM, TO> && are_convertible<TO, FROMs...>::value};
    };

    template <typename TO, typename FROM>
    struct are_convertible<TO, FROM> {
        static constexpr bool value{std::is_convertible_v<FROM, TO>};
    };

    template <typename TO, typename... FROMs>
    constexpr bool are_convertible_v{are_convertible<TO, FROMs...>::value};
    }  // namespace Inner_

    template <typename TO, typename... FROMs>
    struct AreConvertible : std::conditional_t<Inner_::are_convertible_v<TO, FROMs...>, std::true_type, std::false_type> {
    };

    template <typename TO, typename... FROMs>
    constexpr bool AreConvertibleV{AreConvertible<TO, FROMs...>::value};
    }  // namespace Nstd
```


「[IsSameSomeOf](template_meta_programming.md#SS_13_3_3_8)の実装」のコードパターンとほぼ同様であるため、解説は不要だろうが、

* パラメータパックの都合上、TOとFROMのパラメータの位置がstd::is_convertibleとは逆になる
* IsSameSomeOfでは条件の一つがtrueであればIsSameSomeOf::valueがtrueとなるが、
  AreConvertibleでは全条件がtrueとならない限り、AreConvertible::valueがtrueとならない

ので注意が必要である。

単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/nstd_type_traits_ut.cpp 43

    static_assert(Nstd::AreConvertibleV<int, int8_t, int16_t, int>);
    static_assert(Nstd::AreConvertibleV<int, char, int, int>);
    static_assert(!Nstd::AreConvertibleV<int, char*, int, int>);
    static_assert(Nstd::AreConvertibleV<std::string, std::string, char*, char[3]>);
    static_assert(!Nstd::AreConvertibleV<std::string, std::string, char*, int>);
```


#### AreConvertibleWithoutNarrowConv <a id="SS_13_3_4_2"></a>
縮小無しの型変換ができるかどうかを判定するAreConvertibleWithoutNarrowConvは、
AreConvertibleと同じように実装できるが、
その場合、AreConvertibleに対してstd::is_convertibleが必要になったように、
AreConvertibleWithoutNarrowConvに対しis_convertible_without_narrow_convが必要になる。

縮小無しでFROMからTOへの型変換ができるかどうかを判定するis_convertible_without_narrow_convは、
SFINAEと関数テンプレート/関数のオーバーライドを使用し以下のように実装できる。

```cpp
    //  example/h/nstd_type_traits.h 85

    namespace Nstd {
    namespace Inner_ {

    template <typename TO, typename FROM>
    class is_convertible_without_narrow_conv {
        template <typename T = TO, typename U = FROM>
        static constexpr auto detector(T* t, U* u) noexcept
            // 縮小無しでFROMからTOへ変換可能な場合、*t = T{*u}はwell-formed
            // 上記ではない場合、*t = T{*u}はill-formed
            -> decltype(*t = T{*u}, bool{})
        {
            return true;
        }

        static constexpr bool detector(...) noexcept { return false; }

    public:
        static constexpr bool value{
            is_convertible_without_narrow_conv::detector(static_cast<TO*>(nullptr), static_cast<FROM*>(nullptr))};
    };

    template <typename TO, typename FROM>
    constexpr bool is_convertible_without_narrow_conv_v{is_convertible_without_narrow_conv<TO, FROM>::value};
    }  // namespace Inner_
    }  // namespace Nstd
```

AreConvertibleWithoutNarrowConvはNstdで定義するため、その内部のみで用いる
is_convertible_without_narrow_convはNstd::Inner\_で定義している。

上記を抜粋した下記のコードは「縮小型変換を発生さる{}による初期化は[ill-formed](term_explanation.md#SS_19_19_5)になる」
ことをSFINAEに利用している。

```cpp
    //  example/h/nstd_type_traits.h 95

    // 縮小無しでFROMからTOへ変換可能な場合、*t = T{*u}はwell-formed
    // 上記ではない場合、*t = T{*u}はill-formed
    -> decltype(*t = T{*u}, bool{})
```

単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/nstd_type_traits_ut.cpp 55

    static_assert(Nstd::Inner_::is_convertible_without_narrow_conv_v<int, int>);
    static_assert(Nstd::Inner_::is_convertible_without_narrow_conv_v<int, int16_t>);
    static_assert(!Nstd::Inner_::is_convertible_without_narrow_conv_v<int16_t, int>);
    static_assert(Nstd::Inner_::is_convertible_without_narrow_conv_v<std::string, char*>);
    static_assert(!Nstd::Inner_::is_convertible_without_narrow_conv_v<char*, std::string>);
```

is_convertible_without_narrow_convを利用したAreConvertibleWithoutNarrowConv
の実装は以下のようになる。

```cpp
    //  example/h/nstd_type_traits.h 117

    namespace Nstd {
    namespace Inner_ {

    template <typename TO, typename FROM, typename... FROMs>
    struct are_convertible_without_narrow_conv {
        static constexpr bool value{
            is_convertible_without_narrow_conv_v<TO, FROM> 
                  && are_convertible_without_narrow_conv<TO, FROMs...>::value};
    };

    template <typename TO, typename FROM>
    struct are_convertible_without_narrow_conv<TO, FROM> {
        static constexpr bool value{is_convertible_without_narrow_conv_v<TO, FROM>};
    };

    template <typename TO, typename FROM, typename... FROMs>
    constexpr bool are_convertible_without_narrow_conv_v{are_convertible_without_narrow_conv<TO, FROM, FROMs...>::value};
    }  // namespace Inner_

    template <typename TO, typename FROM, typename... FROMs>
    struct AreConvertibleWithoutNarrowConv
        : std::conditional_t<Inner_::are_convertible_without_narrow_conv_v<TO, FROM, FROMs...>, std::true_type,
                             std::false_type> {
    };

    template <typename TO, typename FROM, typename... FROMs>
    constexpr bool AreConvertibleWithoutNarrowConvV{AreConvertibleWithoutNarrowConv<TO, FROM, FROMs...>::value};
    }  // namespace Nstd
```

単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/nstd_type_traits_ut.cpp 63

    static_assert(Nstd::AreConvertibleWithoutNarrowConvV<int, char, int16_t, uint16_t>);
    static_assert(!Nstd::AreConvertibleWithoutNarrowConvV<int, char, int16_t, uint32_t>);
    static_assert(Nstd::AreConvertibleWithoutNarrowConvV<std::string, char[5], char*>);
    static_assert(Nstd::AreConvertibleWithoutNarrowConvV<double, float>);

    // int8_t -> doubleは縮小型変換
    static_assert(!Nstd::AreConvertibleWithoutNarrowConvV<double, float, int8_t>);
```

#### ConvertibleToAll <a id="SS_13_3_4_3"></a>
ConvertibleToAllの実装は下記のようになる。

```cpp
    //  h/nstd_concepts.h 57

// 複数の型 FROMs がすべて TO に変換可能かどうかを制約するコンセプト
template <typename TO, typename... FROMs>
concept ConvertibleToAll = (std::convertible_to<FROMs, TO> && ...);
```

使用方法を含めて、単体テストは以下のようになる。

```cpp
    //  example/template/nstd_concepts_ut.cpp 137

    // ConvertibleToAll_Test テンプレートの定義
    template <typename TO, typename... FROMs>
    struct ConvertibleToAll_Test : std::false_type {
    };

    // すべての FROMs が TO に変換可能な場合の部分特殊化
    template <typename TO, typename... Us>
    requires ConvertibleToAll<TO, Us...>
    struct ConvertibleToAll_Test<TO, Us...> : std::true_type {
    };

    struct convert_bool {
        operator bool() const { return false; }
    };

    static_assert(!ConvertibleToAll_Test<bool, int, std::string>::value);
    static_assert(ConvertibleToAll_Test<bool, int, convert_bool>::value);
```

#### ConvertibleWithoutNarrowing <a id="SS_13_3_4_4"></a>
ConvertibleWithoutNarrowingは以下のようなコンセプトである。

* [AreConvertibleWithoutNarrowConv](template_meta_programming.md#SS_13_3_4_2)と同様の機能を持つ
* [ConvertibleToAll](template_meta_programming.md#SS_13_3_4_3)と同様構造を持つ

実装は以下のようになる。

```cpp
    //  h/nstd_concepts.h 63

namespace Inner_ {

template <typename TO, typename FROM>
concept convertible_without_narrowing = requires(FROM from)
{
    { TO {from} } -> std::same_as<TO>;
};

// 複数の型が変換可能かどうかを確認するバージョン
template <typename TO, typename... FROMs>
concept all_convertible_without_narrowing = (convertible_without_narrowing<TO, FROMs> && ...);

}  // namespace Inner_

// コンセプトを使用
template <typename TO, typename... FROMs>
concept ConvertibleWithoutNarrowing = Inner_::all_convertible_without_narrowing<TO, FROMs...>;
```

単体テストは他の似たコンセプトとほぼ同様になるため省略する。


### 関数の存在の診断 <a id="SS_13_3_5"></a>
Nstdライブラリの開発には関数の存在の診断が欠かせない。
例えば、

* テンプレートパラメータに特定のメンバ関数がある場合、特殊化を作る
* テンプレートパラメータに範囲for文が適用できる場合にのみoperator<<を適用する
* テンプレートパラメータに適用できるoperator<<がすでにあった場合、
  自作operator<<を不活性化する

等、応用範囲は多岐にわたる。
ここでは、上記の場合分けを可能とするようなメタ関数に必要なテクニックや、
それらを使用したNstdのメタ関数の実装を下記のように示す。

* テンプレートパラメータである型が、メンバ関数void func()を持つかどうかの診断について、
  次の表のように実装を示す。

|メタ関数名                              |メタ関数の目的                                    |
|----------------------------------------|--------------------------------------------------|
|[exists_void_func_sfinae_f](template_meta_programming.md#SS_13_3_5_1)        |メンバ関数void func()を持つかどうかの判断         |
|[exists_void_func_sfinae_s](template_meta_programming.md#SS_13_3_5_2)        |同上                                              |
|[exists_void_func_sfinae_s2](template_meta_programming.md#SS_13_3_5_3)       |同上                                              |
|[exists_void_func_concept](template_meta_programming.md#SS_13_3_5_4)         |同上。コンセプトによるSFINAEの回避                |

* テンプレートパラメータに範囲for文ができるかどうかの診断について、
  次の表のように実装を示す。

|メタ関数名                            |メタ関数の目的                                                     |
|--------------------------------------|-------------------------------------------------------------------|
|[exists_begin/exsits_end](template_meta_programming.md#SS_13_3_5_5)        |SFINAEを使用したstd::begin(T)/std::end(T)が存在するか否かの診断    |
|[Array](template_meta_programming.md#SS_13_3_5_7)                          |型が配列である制約を行うためのコンセプト                           |
|[Beginable/Endable](template_meta_programming.md#SS_13_3_5_8)              |[コンセプト](term_explanation.md#SS_19_11_2)を使用したexists_begin/exsits_endを単純化した例   |
|[IsRange](template_meta_programming.md#SS_13_3_5_6)                        |exists_begin/exsits_endを使し、範囲forのオペランドになれるか?の判断|
|[Ranged](template_meta_programming.md#SS_13_3_5_9)                         |機能はIsRangeと同一だが、[コンセプト](term_explanation.md#SS_19_11_2)を使用しSFINAEの回避     |
|[Container](template_meta_programming.md#SS_13_3_5_10)                      |Ranged且つ!Arrayをコンテナと便宜的に決めつける                     |

* テンプレートパラメータにoperator<<(put toと発音する)ができるかどうかの診断について、
  次の表のように実装を示す。

|メタ関数名                            |メタ関数の目的                                         |
|--------------------------------------|-------------------------------------------------------|
|[exists_put_to_as_member](template_meta_programming.md#SS_13_3_5_11)        |std::ostream::operator<<(T)が存在するか否かの診断      |
|[exists_put_to_as_non_member](template_meta_programming.md#SS_13_3_5_12)    |operator<<(std::ostream&, T)が存在するか否かの診断     |
|[ExistsPutTo](template_meta_programming.md#SS_13_3_5_13)                    |std::ostream& << Tができるかどうかの診断               |
|[Printable](template_meta_programming.md#SS_13_3_5_14)                      |std::ostream& << Tができるかどうか制約コンセプト       |

* テンプレートパラメータがT[N]やC\<T>の形式である時のTに、
  operator<<が適用できるかの診断については、Tの型を取り出す必要がある。
  そのようなメタ関数ValueTypeの実装を示す。


#### exists_void_func_sfinae_f <a id="SS_13_3_5_1"></a>
「テンプレートパラメータである型が、メンバ関数void func()を持つかどうかを診断する」
exists_void_func_sfinae_f
のSFINAEと関数テンプレート/関数のオーバーロードを用いた実装は以下のようになる。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 13

    namespace Inner_ {

    template <typename T>
    using exists_void_func_void =
        // メンバvoid func(void)があれば、voidを生成
        // メンバvoid func(void)がなければ、ill-formed
        typename std::enable_if_t<std::is_same_v<decltype(std::declval<T>().func()), void>>;
    }  // namespace Inner_

    template <typename T, typename = Inner_::exists_void_func_void<T>>
    constexpr bool exists_void_func_sfinae_f(T) noexcept
    {
        return true;
    }

    constexpr bool exists_void_func_sfinae_f(...) noexcept { return false; }
```

decltypeの中での関数呼び出しは、実際には呼び出されず関数の戻り値の型になる。
上記の抜粋である下記のコードはこの性質を利用してSFINAEによる静的ディスパッチを行っている。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 20

    // メンバvoid func(void)があれば、voidを生成
    // メンバvoid func(void)がなければ、ill-formed
    typename std::enable_if_t<std::is_same_v<decltype(std::declval<T>().func()), void>>;
```

単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 40

    // テスト用クラス
    struct X {
        void func();
    };

    struct Y {
        int func();
    };

    struct Z {
    private:
        void func();  // privateなvoid func()は外部からは呼び出せない
    };
```

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 60

    static_assert(!exists_void_func_sfinae_f(int{}));
    static_assert(exists_void_func_sfinae_f(X{}));
    static_assert(!exists_void_func_sfinae_f(Y{}));
    static_assert(!exists_void_func_sfinae_f(Z{}));
```


#### exists_void_func_sfinae_s <a id="SS_13_3_5_2"></a>
「テンプレートパラメータである型が、メンバ関数void func()を持つかどうかを診断」する
exists_void_func_sfinae_s
のSFINAEとクラステンプレートの特殊化を用いた実装は以下のようになる。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 69

    template <typename T, typename U = void>
    struct exists_void_func_sfinae_s : std::false_type {
    };

    template <typename T>
    struct exists_void_func_sfinae_s<T,
        // メンバvoid func()が呼び出せれば、voidを生成
        // メンバvoid func()が呼び出せなければ、ill-formed
        decltype(std::declval<T>().func())
        > : std::true_type {
    };

    template <typename T>
    constexpr bool exists_void_func_sfinae_s_v{exists_void_func_sfinae_s<T>::value};
```

exists_void_func_sfinae_fとほぼ等しいSFINAEを利用したクラステンプレートの特殊化により、
静的ディスパッチを行っている。

単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 91

    static_assert(!exists_void_func_sfinae_s_v<int>);
    static_assert(exists_void_func_sfinae_s_v<X>);
    static_assert(!exists_void_func_sfinae_s_v<Y>);
    static_assert(!exists_void_func_sfinae_s_v<Z>);
```


#### exists_void_func_sfinae_s2 <a id="SS_13_3_5_3"></a>
exists_void_func_sfinae_sとほぼ同様の仕様を持つexists_void_func_sfinae_s2の

* SFINAE
* メンバ関数テンプレート/メンバ関数のオーバーロード
* メンバ関数へのポインタ

を用いた実装は以下のようになる。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 100

    template <typename T>
    class exists_void_func_sfinae_s2 {

        // メンバvoid func()が呼び出せれば、メンバ関数テンプレートはtrueを返す
        // メンバvoid func()が呼び出せなければ、ill-formed
        template <typename U, void (U::*)() = &U::func>
        static constexpr bool detector(U*) noexcept
        {
            return true;
        }

        static constexpr bool detector(...) noexcept { return false; }

    public:
        static constexpr bool value{exists_void_func_sfinae_s2::detector(static_cast<T*>(nullptr))};
    };

    template <typename T>
    constexpr bool exists_void_func_sfinae_s2_v{exists_void_func_sfinae_s2<T>::value};
```

前2例とは異なり、上記の抜粋である下記コードのように、
メンバ関数へのポインタを使用しSFINAEを実装している。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 105

    // メンバvoid func()が呼び出せれば、メンバ関数テンプレートはtrueを返す
    // メンバvoid func()が呼び出せなければ、ill-formed
    template <typename U, void (U::*)() = &U::func>
    static constexpr bool detector(U*) noexcept
    {
        return true;
    }
```

あまり応用範囲が広くない方法ではあるが、
decltypeを使っていないのでC++03コンパイラにも受け入れられるメリットがある。

exists_void_func_sfinae_fと同じテスト用クラスを用いた単体テストは以下のようになる。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 129

    static_assert(!exists_void_func_sfinae_s2_v<int>);
    static_assert(exists_void_func_sfinae_s2_v<X>);
    static_assert(!exists_void_func_sfinae_s2_v<Y>);
    static_assert(!exists_void_func_sfinae_s2_v<Z>);
```

[演習-メンバ関数の存在の診断](exercise_q.md#SS_20_11_11)

#### exists_void_func_concept <a id="SS_13_3_5_4"></a>
[exists_void_func_sfinae_s](template_meta_programming.md#SS_13_3_5_2)や[exists_void_func_sfinae_s2](template_meta_programming.md#SS_13_3_5_3)
の実装で見たようなSFINAEによるテンプレートの特殊化は難解なコードを生み出す。
また、シンタックスエラー時、ほぼ理解できない大量のコンパイラのメッセージを生成する。
このため、このようなテクニックはきわめて有用である一方で、開発に多くの時間を消費する、
保守員を選んでしまう、といった問題があった。
以下に示すように、C++20から導入された[コンセプト](term_explanation.md#SS_19_11_2)はこのような問題の軽減につながる。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 138

    #if __cplusplus >= 202002L  // c++20
    template <typename T>  // C++20スタイル。concept/requiresによるSFINAEの回避
    concept exists_void_func_concept = requires(T& t)
    {
        { t.func() } -> std::same_as<void>;
    };

    #else  // c++17
    namespace Inner_ {
    template <typename T, typename = void>
    struct exists_void_func_impl : std::false_type {
    };

    template <typename T>  // C++17スタイル。SFINAEでの実装
    struct exists_void_func_impl<T,
                                 std::void_t<decltype(std::declval<T&>().func())>>  // func()が呼び出し可能か確認
        : std::is_same<void, decltype(std::declval<T&>().func())>                   // 戻り値がvoidか確認
    {
    };
    }  // namespace Inner_

    template <typename T>
    inline constexpr bool exists_void_func_concept = Inner_::exists_void_func_impl<T>::value;
    #endif
```
```cpp
    //  example/template_cpp17/exists_func_ut.cpp 170
    static_assert(!exists_void_func_concept<decltype(int{})>);
    static_assert(exists_void_func_concept<decltype(X{})>);
    static_assert(!exists_void_func_concept<decltype(Y{})>);  // Y::funcの戻りはint
    static_assert(!exists_void_func_concept<decltype(Z{})>);  // Z::funcは呼び出せない
```

#### exists_begin/exsits_end <a id="SS_13_3_5_5"></a>
「テンプレートパラメータTに対して、
std::begin(T)が存在するか否かの診断」をするexists_beginの実装は、
「[exists_void_func_sfinae_s](template_meta_programming.md#SS_13_3_5_2)」
で用いたパターンのメンバ関数を非メンバ関数に置き換えて使えば以下のようになる。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 180

    template <typename, typename = void>
    struct exists_begin : std::false_type {
    };

    template <typename T>
    struct exists_begin<T, std::void_t<decltype(std::begin(std::declval<T>()))>> : std::true_type {
    };

    template <typename T>
    constexpr bool exists_begin_v{exists_begin<T>::value};
```

上記で使用したstd::void_tは、テンプレートパラメータが

* [ill-formed](term_explanation.md#SS_19_19_5)ならばill-formedになる
* [well-formed](term_explanation.md#SS_19_19_6)ならvoidを生成する

テンプレートである。

下記単体テストでは問題ないように見えるが、

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 196

    static_assert(exists_begin_v<std::string>);
    static_assert(!exists_begin_v<int>);
    static_assert(exists_begin_v<int const[3]>);
```

下記の単体テストはstatic_assertがフェールするためコンパイルできない。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 206

    // 以下が問題
    static_assert(exists_begin_v<int[3]>);
```

理由は、

```cpp
    std::declval<int[3]>())
```

の戻り型が配列型の[rvalue](term_explanation.md#SS_19_14_1_2)である"int (&&) [3]"となり、
これに対応するstd::beginが定義されていないためである。

これに対処する方法方はいくつかあるが、
すべての配列は常にstd::beginの引数になれることに気づけば、
テンプレートパラメータが配列か否かで場合分けしたクラステンプレートの特殊化を使い、
下記のように実装できることにも気付けるだろう。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 223

    template <typename, typename = void>
    struct exists_begin : std::false_type {
    };

    // Tが非配列の場合の特殊化
    template <typename T>
    struct exists_begin<
        T, typename std::enable_if_t<!std::is_array_v<T>, std::void_t<decltype(std::begin(std::declval<T>()))>>>
        : std::true_type {
    };

    // Tが配列の場合の特殊化
    template <typename T>
    struct exists_begin<T, typename std::enable_if_t<std::is_array_v<T>>> : std::true_type {
    };

    template <typename T>
    constexpr bool exists_begin_v{exists_begin<T>::value};
```

2個目のexists_beginはTが配列でない場合、
3個目のexists_beginはTが配列ある場合にそれぞれが対応しているが、複雑すぎて何とも醜い。
ということで、このコードは却下して、別のアイデアを試そう。

テンプレートパラメータが配列である場合でも、
そのオブジェクトが[lvalue](term_explanation.md#SS_19_14_1_1)(この例ではint (&)[3])であれば、
std::beginはそのオブジェクトを使用できるので、
decltype内で使用できるlvalueのT型オブジェクトを生成できれば、
と考えれば下記のような実装を思いつくだろう。

```cpp
    //  example/h/nstd_type_traits.h 158

    template <typename, typename = void>
    struct exists_begin : std::false_type {
    };

    template <typename T>
    struct exists_begin<T, std::void_t<decltype(std::begin(std::declval<T&>()))>> : std::true_type {
    };

    template <typename T>
    constexpr bool exists_begin_v{exists_begin<T>::value};
```

十分にシンプルなのでこれを採用し、exists_endも同様に実装する。

```cpp
    //  example/h/nstd_type_traits.h 171

    template <typename, typename = void>
    struct exists_end : std::false_type {
    };

    template <typename T>
    struct exists_end<T, std::void_t<decltype(std::end(std::declval<T&>()))>> : std::true_type {
    };
    template <typename T>
    constexpr bool exists_end_v{exists_end<T>::value};
```

単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/nstd_type_traits_ut.cpp 97

    static_assert(exists_begin_v<std::string>);
    static_assert(!exists_begin_v<int>);
    static_assert(exists_begin_v<int const[3]>);
    static_assert(exists_begin_v<int[3]>);  // 問題が解決

    static_assert(exists_end_v<std::string>);
    static_assert(!exists_end_v<int>);
    static_assert(exists_end_v<int const[3]>);
    static_assert(exists_end_v<int[3]>);
```

#### IsRange <a id="SS_13_3_5_6"></a>
[範囲for文](https://cpprefjp.github.io/lang/cpp11/range_based_for.html)
文の":"の後ろにT型オブジェクトが指定できる要件は、

* std::begin(T)、std::end(T)がTのイテレータであるITOR型のオブジェクトを返す
* std::begin(T)が返すITORオブジェクトはTが保持する先頭の要素を指す
* std::end(T)が返すITORオブジェクトはTが保持する最後の要素の次を指す
* ++ITORによりTが保持する全要素にアクセスできる

ようなことである。多くの要件はセマンティクス的なものであり、
メタ関数で診断できることは前項で見たようなstd::begin(T)、std::end(T)の可否のみであると考えれば、
IsRangeの実装は以下のようになる。

```cpp
    //  example/h/nstd_type_traits.h 185

    template <typename T>
    struct IsRange
        : std::conditional_t<Inner_::exists_begin_v<T> && Inner_::exists_end_v<T>, std::true_type, std::false_type> {
    };

    template <typename T>
    constexpr bool IsRangeV{IsRange<T>::value};
```

なお、上記のコードでは、exists_begin/exsits_endは、IsRangeの実装の詳細であるため、
名前空間Inner\_で宣言している。

```cpp
    //  example/template_cpp17/nstd_type_traits_ut.cpp 116

    static_assert(IsRangeV<std::string>);
    static_assert(!IsRangeV<int>);
    static_assert(IsRangeV<int const[3]>);
    static_assert(IsRangeV<int[3]>);
```

[演習-範囲for文のオペランドになれるかどうかの診断](exercise_q.md#SS_20_11_12)

#### Array <a id="SS_13_3_5_7"></a>

以降の節で使用するため、テンプレートパラメータが配列である制約を下記のように宣言する。

```cpp
    //  h/nstd_concepts.h 9

    template <typename T>
    concept Array = std::is_array_v<T>;
```
```cpp
    //  example/template/nstd_concepts_ut.cpp 18

    int  a[3];
    int* ptr = a;
    auto v   = std::vector{1, 2, 3};

    static_assert(Array<decltype(a)>);

    static_assert(Array<decltype(a)>);
    static_assert(!Array<decltype(ptr)>);
```

#### Beginable/Endable <a id="SS_13_3_5_8"></a>
コンセプトを使用し、[exists_begin/exsits_end](template_meta_programming.md#SS_13_3_5_5)をリファクタリングした例を以下に示す。

```cpp
    //  h/nstd_concepts.h 15

    template <typename T>
    concept Beginable = Array<T> || requires(T& t)
    {
        { std::begin(t) } -> std::same_as<typename T::iterator>;
    };

    template <typename T>
    concept Endable = Array<T> || requires(T& t)
    {
        { std::end(t) } -> std::same_as<typename T::iterator>;
    };
```
```cpp
    //  example/template/nstd_concepts_ut.cpp 34

    int  a[3];
    int* ptr = a;
    auto v   = std::vector{1, 2, 3};

    static_assert(Array<decltype(a)>);

    static_assert(Beginable<decltype(a)>);
    static_assert(!Beginable<decltype(ptr)>);
    static_assert(Beginable<decltype(v)>);
```


#### Ranged <a id="SS_13_3_5_9"></a>
IsRangeと同一の機能を持つコンセプトRangedを以下のように定義する。

```cpp
    //  h/nstd_concepts.h 33

    template <typename T>
    concept Ranged = Beginable<T> && Endable<T>;
```

単体テストは以下のようになる。

```cpp
    //  example/template/nstd_concepts_ut.cpp 53

    static_assert(Ranged<std::string>);
    static_assert(!Ranged<int>);
    static_assert(Ranged<int const[3]>);
    static_assert(Ranged<int[3]>);
```

すでにみたようにRangedは[exists_begin/exsits_end](template_meta_programming.md#SS_13_3_5_5)の醜いコードを使用しないことで、
Rangedの可読性はIsRangedに比べ格段に改善している。

#### Container <a id="SS_13_3_5_10"></a>
与えられた型をコンテナに制約するためのコンセプトを下記のように便宜的に宣言する。

```cpp
    //  h/nstd_concepts.h 33

    template <typename T>
    concept Ranged = Beginable<T> && Endable<T>;
```

単体テストには少々の工夫が必要になる。

```cpp
    //  example/template/nstd_concepts_ut.cpp 62

    struct X {
        std::vector<int> data{1, 2, 3, 4, 5};

        auto begin() { return data.begin(); }  // std::begin
        auto end() { return data.end(); }      // std::end
    };

    //  example/template/nstd_concepts_ut.cpp 74

    static_assert(Container<std::string>);
    static_assert(!Container<int>);
    static_assert(!Container<int const[3]>);

    static_assert(!Ranged<X>);  // begin/endがあるが、value_typeをもっていない

```

#### exists_put_to_as_member <a id="SS_13_3_5_11"></a>
std::ostreamのメンバ関数operator<<の戻り型はstd::ostream&であるため、
exists_put_to_as_memberの実装は以下のようになる("<<"は英語で"put to"と発音する)。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 258

    template <typename, typename = std::ostream&>
    struct exists_put_to_as_member : std::false_type {
    };

    template <typename T>
    struct exists_put_to_as_member<T, decltype(std::declval<std::ostream&>().operator<<(std::declval<T>()))>
        : std::true_type {
    };

    template <typename T>
    constexpr bool exists_put_to_as_member_v{exists_put_to_as_member<T>::value};
```

「[exists_void_func_sfinae_f](template_meta_programming.md#SS_13_3_5_1)の実装」と同様のパターンを使用したので解説は不要だろう。

単体テストは以下のようになる。

```cpp
    //  example/template/test_class.h 3

    class test_class_exits_put_to {
    public:
        test_class_exits_put_to(int i = 0) noexcept : i_{i} {}
        int get() const noexcept { return i_; }

    private:
        int i_;
    };

    inline std::ostream& operator<<(std::ostream& os, test_class_exits_put_to const& p) { return os << p.get(); }

    class test_class_not_exits_put_to {};
```

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 275

    static_assert(exists_put_to_as_member_v<bool>);
    static_assert(!exists_put_to_as_member_v<std::string>);
    static_assert(!exists_put_to_as_member_v<std::vector<int>>);
    static_assert(exists_put_to_as_member_v<std::vector<int>*>);
    static_assert(!exists_put_to_as_member_v<test_class_exits_put_to>);
    static_assert(!exists_put_to_as_member_v<test_class_not_exits_put_to>);
    static_assert(exists_put_to_as_member_v<test_class_not_exits_put_to[3]>);  // 驚き!
```

やや驚きなのは、上記の抜粋である下記コードがコンパイルできることである。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 284

    static_assert(exists_put_to_as_member_v<test_class_not_exits_put_to[3]>);  // 驚き!
```

これは、

```cpp
    std::ostream& std::ostream::operator<<(void const*)
```

が定義されているため、配列がポインタに変換されてこのメンバ関数にバインドした結果である。


#### exists_put_to_as_non_member <a id="SS_13_3_5_12"></a>
exists_put_to_as_non_memberの実装は以下のようになる。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 293

    template <typename, typename = std::ostream&>
    struct exists_put_to_as_non_member : std::false_type {
    };

    template <typename T>
    struct exists_put_to_as_non_member<T, decltype(operator<<(std::declval<std::ostream&>(), std::declval<T>()))>
        : std::true_type {
    };

    template <typename T>
    constexpr bool exists_put_to_as_non_member_v{exists_put_to_as_non_member<T>::value};
```

「[exists_begin/exsits_end](template_meta_programming.md#SS_13_3_5_5)や[exists_put_to_as_member](template_meta_programming.md#SS_13_3_5_11)の実装」
で使用したパターンを混合しただけなので解説や単体テストは省略する。


#### ExistsPutTo <a id="SS_13_3_5_13"></a>
テンプレートパラメータT、T型オブジェクトtに対して、
std::ostream << tができるかどうかを判断するExistsPutToの実装は以下のようになる。

```cpp
    //  example/template_cpp17/exists_func_ut.cpp 322

    template <typename T>
    struct ExistsPutTo
        : std::conditional_t<Inner_::exists_put_to_as_member_v<T> || Inner_::exists_put_to_as_non_member_v<T>,
                             std::true_type, std::false_type> {
    };

    template <typename T>
    constexpr bool ExistsPutToV{ExistsPutTo<T>::value};
```

「[IsRange](template_meta_programming.md#SS_13_3_5_6)の実装」に影響されて、一旦このように実装したが、先に書いた通り、
そもそものExistsPutToの役割はstd::ostream << tができるかどうかの診断であることを思い出せば、
下記のように、もっとシンプルに実装できることに気づくだろう。

```cpp
    //  example/h/nstd_type_traits.h 200

    namespace Nstd {

    template <typename, typename = std::ostream&>
    struct ExistsPutTo : std::false_type {
    };

    template <typename T>
    struct ExistsPutTo<T, decltype(std::declval<std::ostream&>() << std::declval<T>())> : std::true_type {
    };

    template <typename T>
    constexpr bool ExistsPutToV{ExistsPutTo<T>::value};
    }  // namespace Nstd
```

単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/nstd_type_traits_ut.cpp 127

    static_assert(Nstd::ExistsPutToV<bool>);
    static_assert(Nstd::ExistsPutToV<std::string>);
    static_assert(!Nstd::ExistsPutToV<std::vector<int>>);
    static_assert(Nstd::ExistsPutToV<std::vector<int>*>);
    static_assert(Nstd::ExistsPutToV<test_class_exits_put_to>);
    static_assert(!Nstd::ExistsPutToV<test_class_not_exits_put_to>);
    static_assert(Nstd::ExistsPutToV<test_class_not_exits_put_to[3]>);
```

#### Printable <a id="SS_13_3_5_14"></a>
これまでのパターンに従ってPrintableを以下のように作る。

* [SFINAE](term_explanation.md#SS_19_11_1)を利用した[ExistsPutTo](template_meta_programming.md#SS_13_3_5_13)は複雑で醜いため、リファクタリングする。
* リファクタリングに合わせてコンセプト化し、それらしい名称にする。

```cpp
    //  h/nstd_concepts.h 42

    template <typename T>
    concept Printable = requires(T t, std::ostream& os)
    {
        { os << t } -> std::same_as<std::ostream&>;
    };
```
```cpp
    //  example/template/nstd_concepts_ut.cpp 86

    struct X {};  // Non-pritable
    struct Y {};  // Printable

    std::ostream& operator<<(std::ostream& os, Y)
    {
        return os;  // 何もしない
    }

    //  example/template/nstd_concepts_ut.cpp 99

    static_assert(Printable<bool>);
    static_assert(Printable<std::string>);
    static_assert(!Printable<std::vector<int>>);
    static_assert(Printable<std::vector<int>*>);
    static_assert(!Printable<X>);
    static_assert(Printable<Y>);
```

これ以降は、[ExistsPutTo](template_meta_programming.md#SS_13_3_5_13)ではなくPrintableを使用する。

#### ValueTypeの実装 <a id="SS_13_3_5_15"></a>
下記で示す通り、

```cpp
    //  example/template_cpp17/nstd_type_traits_ut.cpp 145

    struct T {};

    std::ostream& operator<<(std::ostream& os, std::vector<T> const& x) { return os << "T:" << x.size(); }

    std::ostream& operator<<(std::ostream&, T const&) = delete;

    static_assert(!Nstd::ExistsPutToV<T>);              // std::cout << T{} はできない
    static_assert(Nstd::ExistsPutToV<std::vector<T>>);  // std::cout << std::vector<T>{} はできる
    static_assert(Nstd::ExistsPutToV<T[3]>);            // std::cout << T[3]{} はできる
```

型Xが与えれ、その形式が、

* クラステンプレートCとその型パラメータTにより、C\<T>
* 型Tと定数整数Nにより、T[N]

のような場合、Printable\<X>がtrueであっても、Printable\<T>の真偽はわからない。
従って上記のようなTに対して、Printable\<T>がtrueかどうかを診断するためには、
XからTを導出することが必要になる。ここでは、そのようなメタ関数ValueTypeの実装を考える。
このValueTypeは上記のX、Tに対して、

```cpp
    static_assert(std::is_same<ValueType<X>::type, T>);
    // もしくは、
    static_assert(std::is_same<ValueType<X, T>);
```

となるような機能を持たなければならないことは明らかだろう。
その他の機能については実装しながら決定していく。

一見、難しそうなテンプレートを作るコツは、条件を絞って少しずつ作っていくことである。
いきなり大量のテンプレートを書いてしまうと、
その何十倍ものコンパイルエラーに打ちのめされること必至である。

ということで、まずは、1次元の配列に対してのみ動作するValueTypeの実装を示す
(下記で使用するstd::remove_extent_t\<T>は、テンプレートパラメータが配列だった場合に、
その次元を一つだけ除去するメタ関数である)。

```cpp
    //  example/template/value_type_ut.cpp 18

    template <typename T, typename = void>
    struct ValueType {
        using type = void;
    };

    template <typename T, size_t N>
    struct ValueType<T[N]> {  // 配列型の特殊化
        using type = T;
    };

    template <typename T>
    using ValueTypeT = typename ValueType<T>::type;
```

このコードは問題なく動作するが、下記の通り、2次元配列に対するValueType::typeは1次元配列となる。

```cpp
    //  example/template/value_type_ut.cpp 36

    static_assert(std::is_same_v<int, ValueTypeT<int[1]>>);
    static_assert(std::is_same_v<void, ValueTypeT<int>>);
    static_assert(std::is_same_v<int[2], ValueTypeT<int[1][2]>>);
```

これを多次元配列に拡張する前に、配列の次元をで返すValueType::Nestや、extent、type_directを追加することにすると、
コードは下記のようになるだろう。

```cpp
    //  example/template/value_type_ut.cpp 49

    template <typename T, typename = void>
    struct ValueType {
        using type        = void;
        using type_direct = T;
        static constexpr size_t Nest{0};
    };

    template <typename T, size_t N>
    struct ValueType<T[N]> {  // 配列型の特殊化
        using type                     = T;
        using type_direct              = T;  // T = S[N]の場合、Tを保存
        static constexpr size_t extent = N;  // T = S[N]の場合、Nを保存
        static constexpr size_t Nest{ValueType<type>::Nest + 1};
    };

    template <typename T>
    using ValueTypeT = typename ValueType<T>::type;
```

動作は下記のようになる。

```cpp
    //  example/template/value_type_ut.cpp 76

    static_assert(0 == ValueType<int>::Nest);
    static_assert(1 == ValueType<int[1]>::Nest);
    static_assert(2 == ValueType<int[1][2]>::Nest);
    static_assert(1 == ValueType<int[1]>::extent);
    static_assert(1 == ValueType<int[1][2]>::extent);  // int[1][2] == (int[1])[2]
```

ここで、下記のような仕様をもつValueType::type_n\<N>を考える。

```
    ValueType<int[1][2][3]>::type_n<0>が表す型は、int[1][2][3]
    ValueType<int[1][2][3]>::type_n<1>が表す型は、int[2][3]
    ValueType<int[1][2][3]>::type_n<2>が表す型は、int[3]
    ValueType<int[1][2][3]>::type_n<3>が表す型は、int
```

ValueType::type_n\<N>は玉ねぎの皮を一枚ずつむくようなメンバテンプレートになる。
プライマリの実装は以下のようになる。

```cpp
    //  example/template/value_type_ut.cpp 91

    template <typename T>
    struct ValueType {
        using type                     = T;
        using type_direct              = T;
        static constexpr size_t extent = 0;
        static constexpr size_t Nest   = 0;

        template <size_t N>
        using type_n = std::conditional_t<N == 0, T, void>;  // Nが0のときはT、それ以外はvoidを返す
    };
```

Nが非0の場合、Value::type_n\<N>はvoidになる仕様にした。

配列に対する特殊化は以下のようになる。

```cpp
    //  example/template/value_type_ut.cpp 104

    template <typename T, size_t N>  // Array Tを使わずに配列の一般的な表現を使用してNを取り出す
    struct ValueType<T[N]> {         // 配列型の特殊化
        using type                     = typename ValueType<T>::type;
        using type_direct              = T;
        static constexpr size_t extent = N;
        static constexpr size_t Nest   = ValueType<T>::Nest + 1;

        template <size_t M>
        using type_n = std::conditional_t<M == 0, T[N], typename ValueType<T>::template type_n<M - 1>>;
    };
```

Value::type_n\<>のリカーシブ展開を頭の中で行うことは難しいので、
読者の理解を確かめるため、以下のように順を追って一枚づつ配列の階層を剝ぎ取る様子を見ていく。

```cpp
    //  example/template/value_type_ut.cpp 126

    // ValueType<int[1][2][3]>の展開について、考えよう。

    // int[1][2][3]は == (int[2][3])[1]であるため、下記の式が成立する
    static_assert(std::is_same_v<ValueType<int[1][2][3]>::type_direct, int[2][3]>);
    static_assert(ValueType<int[1][2][3]>::extent == 1);

    // type_n<M>の仕様は、Mが1の時、配列から1階層を1枚剥ぎ取ることである
    using T1 = ValueType<int[1][2][3]>::type_n<1>;  // 長い式は可読性が劣化するからT1を宣言

    // int[2][3] == (int[3])[2]であるため、下記の式が成立する
    static_assert(std::is_same_v<T1, int[2][3]>);
    static_assert(ValueType<T1>::extent == 2);

    // 上記T1と同様にT2を宣言する
    using T2 = ValueType<T1>::type_n<1>;

    // int[2][3] == (int[3])[2]であるため、下記の式が成立する
    static_assert(std::is_same_v<T2, int[3]>);
    static_assert(ValueType<T2>::extent == 3);

    // 上記T1、T2と同様にT3を宣言する
    using T3 = ValueType<T2>::type_n<1>;

    static_assert(std::is_same_v<T3, int>);
    static_assert(ValueType<T3>::extent == 0);
```

単体テストは下記のようになる。

```cpp
    //  example/template/value_type_ut.cpp 155

    using T = int[1][2][3];

    static_assert(std::is_same_v<int[1][2][3], ValueType<T>::type_n<0>>);  // 0枚剝く
    static_assert(std::is_same_v<int[2][3], ValueType<T>::type_n<1>>);     // 1枚剝く
    static_assert(std::is_same_v<int[3], ValueType<T>::type_n<2>>);        // 2枚剝く
    static_assert(std::is_same_v<int, ValueType<T>::type_n<3>>);           // 3枚剝く
    static_assert(std::is_same_v<void, ValueType<T>::type_n<4>>);          // 全部剝く
```

また、ValueType::NestとValueType::type_n<>の関係に注目すれば、
上記エイリアスTに対して下記が成立する。

```cpp
    //  example/template/value_type_ut.cpp 178

    using T = ValueTypeT_n<int[1][2][3], 3>;

    static_assert(std::is_same_v<int, T>);
    static_assert(std::is_same_v<int, ValueTypeT_n<T, ValueType<T>::Nest>>);
```


このテンプレートにコンテナが渡された時の特殊化を与えることができればValueTypeは完成するが、
こういったタイミングで、リファクタリングを行い名前の整理や不要になったコードを削除することは良い習慣である。

これによりValueTypeは下記のようになる。

```cpp
    //  example/template/value_type_ut.cpp 240

    template <typename T>
    struct ValueType {  // プライマリ
        using type                   = T;
        static constexpr size_t Nest = 0;

        template <size_t N>
        using type_n = std::conditional_t<N == 0, T, void>;
    };

    template <typename T, size_t N>
    struct ValueType<T[N]> {  // 配列型の特殊化
        using type                   = typename ValueType<T>::type;
        static constexpr size_t Nest = ValueType<T>::Nest + 1;

        template <size_t M>
        using type_n = std::conditional_t<M == 0, T[N], typename ValueType<T>::template type_n<M - 1>>;
    };
```

準備は整ったので上記のValueTypeに下記のようなコンテナ用特殊化を追加する。
この特殊化のテンプレートパラメータの制約にはすでに開発したコンセプト[Container](template_meta_programming.md#SS_13_3_5_10)を使用する。

```cpp
    //  example/template/value_type_ut.cpp 261

    template <Container T>
    struct ValueType<T> {  // コンテナ型の特殊化
        using type                   = typename ValueType<typename T::value_type>::type;
        static constexpr size_t Nest = ValueType<typename T::value_type>::Nest + 1;

        template <size_t N>
        using type_n = std::conditional_t<N == 0, T, typename ValueType<typename T::value_type>::template type_n<N - 1>>;
    };
```

まずは、追加した特殊化の機能を下記のように単体テストを行う。

```cpp
    //  example/template/value_type_ut.cpp 278

    using T = int[1][2][3];

    // コンテナ特殊化以外の機能チェック
    static_assert(std::is_same_v<T, ValueType<T>::type_n<0>>);
    static_assert(std::is_same_v<int[2][3], ValueType<T>::type_n<1>>);
    static_assert(std::is_same_v<int[3], ValueType<T>::type_n<2>>);
    static_assert(std::is_same_v<int, ValueType<T>::type_n<3>>);
    static_assert(std::is_same_v<int, ValueType<T>::type>);
```

次に特殊化がデグレードを起こしていないことを下記のように証明する。

```cpp
    //  example/template/value_type_ut.cpp 291

    // コンテナ特殊化の機能の機能チェック
    using T = std::vector<std::vector<std::vector<int>>>;

    static_assert(std::is_same_v<T, ValueType<T>::type_n<0>>);
    static_assert(std::is_same_v<int, ValueType<T>::type_n<3>>);
    static_assert(ValueType<T>::Nest == 3);
    static_assert(std::is_same_v<int, ValueType<T>::type>);
```

ValueTypeの最終的な単体テストのために上記を統合したテストを行う。

```cpp
    //  example/template/value_type_ut.cpp 303

    // 統合した機能チェック
    using T = std::vector<int[1][2][3]>;

    static_assert(std::is_same_v<T, ValueType<T>::type_n<0>>);
    static_assert(std::is_same_v<int[1][2][3], ValueType<T>::type_n<1>>);
    static_assert(std::is_same_v<int[2][3], ValueType<T>::type_n<2>>);
    static_assert(std::is_same_v<int[3], ValueType<T>::type_n<3>>);
    static_assert(std::is_same_v<int, ValueType<T>::type_n<4>>);
    static_assert(std::is_same_v<int, ValueType<T>::type>);
    static_assert(ValueType<T>::Nest == 4);

    using L = std::list<T>;

    static_assert(std::is_same_v<T, ValueType<L>::type_n<1>>);
    static_assert(std::is_same_v<int[1][2][3], ValueType<L>::type_n<2>>);
    static_assert(std::is_same_v<int, ValueType<T>::type>);
    static_assert(ValueType<L>::Nest == 5);
```

以上でValueTypeは完成したが、これ以降のこのドキュメントの前準備として、
多少のメンバの追加や調整をした最終のコードを以下に示す。

```cpp
    //  example/h/nstd_type_traits.h 220

    namespace Nstd {
    template <typename T, typename = void>  // ValueTypeのプライマリ
    struct ValueType {
        using type_direct = void;

        static constexpr bool   IsBuiltinArray{false};
        static constexpr size_t Nest{0};

        template <size_t N>
        using type_n = typename std::conditional_t<N == 0, T, void>;

        using type = type_n<Nest>;
    };

    #if __cplusplus <= 201703L  // c++17
    namespace Inner_ {

    template <typename T, size_t N>
    struct conditional_value_type_n {
        using type =
            typename std::conditional_t<ValueType<T>::Nest != 0,
                                        typename ValueType<typename ValueType<T>::type_direct>::template type_n<N - 1>, T>;
    };

    template <typename T>
    struct conditional_value_type_n<T, 0> {
        using type = T;
    };

    template <typename T, typename = void>
    struct array_or_container : std::false_type {
    };

    template <typename T>
    struct array_or_container<T, typename std::enable_if_t<std::is_array_v<T>>> : std::true_type {
        using type = typename std::remove_extent_t<T>;
    };

    // Tが配列でなく、且つT型インスタンスに範囲for文が適用できるならばstdコンテナと診断する
    template <typename T>
    constexpr bool is_container_v{Nstd::IsRange<T>::value && !std::is_array_v<T>};

    template <typename T>
    struct array_or_container<T, typename std::enable_if_t<is_container_v<T>>> : std::true_type {
        using type = typename T::value_type;
    };

    template <typename T>
    constexpr bool array_or_container_v{array_or_container<T>::value};
    }  // namespace Inner_

    template <typename T>  // ValueTypeの特殊化
    struct ValueType<T, typename std::enable_if_t<Inner_::array_or_container_v<T>>> {
        using type_direct = typename Inner_::array_or_container<T>::type;

        static constexpr bool   IsBuiltinArray{std::is_array_v<T>};
        static constexpr size_t Nest{ValueType<type_direct>::Nest + 1};

        template <size_t N>
        using type_n = typename Inner_::conditional_value_type_n<T, N>::type;

        using type = type_n<Nest>;
    };
    #else  // c++17

    template <typename T, size_t N>
    struct ValueType<T[N]> {  // 配列型の特殊化
        using type_direct = T;

        static constexpr bool   IsBuiltinArray{true};
        static constexpr size_t Nest{ValueType<type_direct>::Nest + 1};

        template <size_t M>
        using type_n = std::conditional_t<M == 0, T[N], typename ValueType<T>::template type_n<M - 1>>;

        using type = type_n<Nest>;
    };

    template <Container T>  // ValueTypeの特殊化
    struct ValueType<T> {   // コンセプトによるSFINAEの回避
        using type_direct = typename T::value_type;

        static constexpr bool   IsBuiltinArray{false};
        static constexpr size_t Nest{ValueType<type_direct>::Nest + 1};

        template <size_t N>
        using type_n = std::conditional_t<N == 0, T, typename ValueType<typename T::value_type>::template type_n<N - 1>>;

        using type = type_n<Nest>;
    };
    #endif

    template <typename T>
    using ValueTypeT = typename ValueType<T>::type;

    template <typename T, size_t N>
    using ValueTypeT_n = typename ValueType<T>::template type_n<N>;
    }  // namespace Nstd
```

[演習-配列の長さの取り出し](exercise_q.md#SS_20_11_13)
[演習-配列の次元の取り出し](exercise_q.md#SS_20_11_14)

## Nstdライブラリの開発2 <a id="SS_13_4"></a>
ここでは予定していた通りSafeArray2を開発し、その後Nstdに必要なライブラリの開発を続ける。


### SafeArray2の開発 <a id="SS_13_4_1"></a>
「[安全な配列型コンテナ](template_meta_programming.md#SS_13_2_3)」で断念したSafeArray2の開発を再開する前に、
SafeArray2の要件をまとめると、

* std::arrayを基底クラスとする
* operator[]に範囲チェックを行う
* SafeArrayでのパラメータパックによる初期化機能はそのまま残す
* SafeArrayではできなかった縮小型変換が起こる初期化にも対応する
* 新規要件として、
  縮小型変換により初期化されたかどうかを示すメンバ関数InitWithNarrowing()を持つ。

となる。この要件を満たすためには、SafeArrayが

```cpp
    //  example/template/safe_vector_ut.cpp 155

    template <typename... ARGS>  // コンストラクタを定義
    SafeArray(ARGS... args) : base_type{args...}
    {
    }
```

で行っていた初期化を、SafeArray2では、
「縮小型変換が起こるか否かによる場合分けを行い、
それぞれの場合に対応するコンストラクタテンプレートによって初期化」
するようにすれば良いことがわかる。

パラメータパックによるコンストラクタのシグネチャは上記した一種類しかないため、
関数のシグネチャの差異よるオーバーロードは使えない。
とすれば、テンプレートパラメータの型の差異によるオーバーロードを使うしか方法がない。
縮小型変換が起こるか否かの場合分けは、
コンセプト[ConvertibleWithoutNarrowing](template_meta_programming.md#SS_13_3_4_4)を使用したSFINAEで実現させることができる。
という風な思考の変遷により以下のコードにたどり着く。


```cpp
    //  example/template/safe_vector_ut.cpp 228
namespace Nstd {

template <typename T, size_t N>
struct SafeArray2 : std::array<T, N> {
    using std::array<T, N>::array;  // 継承コンストラクタ
    using base_type = std::array<T, N>;

    // 縮小型変換した場合には、ill-formedになるコンストラクタ
    /* c++17スタイルのSFINAE
    template <typename... ARGS,
              typename = 
                  typename std::enable_if_t<
                       AreConvertibleWithoutNarrowConvV<T, ARGS...>>>
    */ 
    template <typename... ARGS> // C++20のコンセプトを使用したSFINAE
    requires ConvertibleWithoutNarrowing<T, ARGS...>
    SafeArray2(ARGS... args) : base_type{args...} // 初期化子リストによるarrayの初期化
    {
    }

    // 縮小型変換しない場合には、ill-formedになるコンストラクタ
    /* C++17までのSFINAE
    template <typename... ARGS, 
              typename std::enable_if_t<
                  !AreConvertibleWithoutNarrowConvV<T, ARGS...>>* = nullptr>
    */
    template <typename... ARGS> // C++20のコンセプトを使用したSFINAE
    requires (!ConvertibleWithoutNarrowing<T, ARGS...>)  // この行には()が必要
    SafeArray2(ARGS... args) :
        base_type{T(args)...},  // 縮小型変換を抑止するため、T(args)が必要
        is_with_narrow_conv_{true}
    {
    }

    using size_type = typename base_type::size_type;

    typename base_type::reference       operator[](size_type i) { return this->at(i); }
    typename base_type::const_reference operator[](size_type i) const { return this->at(i); }

    bool InitWithNarrowing() const noexcept { return is_with_narrow_conv_; }

private:
    bool const is_with_narrow_conv_{false};
};
}  // namespace Nstd
```

下記のようなコードでのコンストラクタ呼び出しには、

```cpp
    //  example/template/safe_vector_ut.cpp 299

    auto sa_init = Nstd::SafeArray2<int, 3>{1, 2, 3};
```

上記の抜粋である下記のコンストラクタが置換失敗により排除される(SFINAE)。

```cpp
    //  example/template/safe_vector_ut.cpp 252

    // 縮小型変換しない場合には、ill-formedになるコンストラクタ
    /* C++17までのSFINAE
    template <typename... ARGS, 
              typename std::enable_if_t<
                  !AreConvertibleWithoutNarrowConvV<T, ARGS...>>* = nullptr>
    */
    template <typename... ARGS> // C++20のコンセプトを使用したSFINAE
    requires (!ConvertibleWithoutNarrowing<T, ARGS...>)  // この行には()が必要
    SafeArray2(ARGS... args) :
        base_type{T(args)...},  // 縮小型変換を抑止するため、T(args)が必要
        is_with_narrow_conv_{true}
    {
    }
```

従って、マッチするコンストラクタは

```cpp
    //  example/template/safe_vector_ut.cpp 237

    // 縮小型変換した場合には、ill-formedになるコンストラクタ
    /* c++17スタイルのSFINAE
    template <typename... ARGS,
              typename = 
                  typename std::enable_if_t<
                       AreConvertibleWithoutNarrowConvV<T, ARGS...>>>
    */ 
    template <typename... ARGS> // C++20のコンセプトを使用したSFINAE
    requires ConvertibleWithoutNarrowing<T, ARGS...>
    SafeArray2(ARGS... args) : base_type{args...} // 初期化子リストによるarrayの初期化
    {
    }
```

のみとなり、無事にコンパイルが成功し、下記の単体テストもパスする。

```cpp
    //  example/template/safe_vector_ut.cpp 299

    auto sa_init = Nstd::SafeArray2<int, 3>{1, 2, 3};

    ASSERT_FALSE(sa_init.InitWithNarrowing());  // 縮小型変換なし
    ASSERT_EQ(3, sa_init.size());
    ASSERT_EQ(1, sa_init[0]);
    ASSERT_EQ(2, sa_init[1]);
    ASSERT_EQ(3, sa_init[2]);
    ASSERT_THROW(sa_init[3], std::out_of_range);
```

下記の単体テストの場合、SFINAEにより、先述の例とは逆のコンストラクタが選択され、
コンパイルも単体テストもパスする。

```cpp
    //  example/template/safe_vector_ut.cpp 314
    auto const sa_init = Nstd::SafeArray2<int, 3>{10, 20, 30.0};  // 30.0はintに縮小型変換される

    ASSERT_TRUE(sa_init.InitWithNarrowing());  // 縮小型変換あり
    ASSERT_EQ(3, sa_init.size());
    ASSERT_EQ(10, sa_init[0]);
    ASSERT_EQ(20, sa_init[1]);
    ASSERT_EQ(30, sa_init[2]);
    ASSERT_THROW(sa_init[3], std::out_of_range);
```

ここで紹介したC++17スタイルの2つのコンストラクタテンプレートの最後のパラメータには、
かなりの違和感があるだろうが、
引数や戻り値に制限の多いコンストラクタテンプレートでSFINAEを起こすためには、
このような記述が必要になる。
一方で[コンセプト](term_explanation.md#SS_19_11_2)を使用したC++20スタイルのSFINAEの可読性の高さを実感できただろう。

なお、2つ目のコンストラクタテンプレートの中で使用した下記のコードは、
パラメータパックで与えられた全引数をそれぞれにT型オブジェクトに変換するための記法である。

```cpp
    //  example/template/safe_vector_ut.cpp 264

    base_type{T(args)...},  // 縮小型変換を抑止するため、T(args)が必要
```

これにより、std::array\<T, N>のstd::initializer_listによる初期化が縮小変換を検出しなくなる。


### Nstd::SafeIndexの開発 <a id="SS_13_4_2"></a>
「[安全なvector](template_meta_programming.md#SS_13_2_2)」、「[安全な配列型コンテナ](template_meta_programming.md#SS_13_2_3)」等の中で、

* Nstd::SafeVector
* Nstd::SafeString
* Nstd::SafeArray

を定義した。これらは少しだけランタイム速度を犠牲にすることで、
安全な(未定義動作を起こさない)インデックスアクセスを保障するため、
一般のソフトウェア開発にも有用であると思われるが、コードクローンして作ったため、
リファクタリングを行う必要がある。

まずは、Nstd::SafeVectorとNstd::SafeStringの統一を考える。

std::stringは、実際にはstd::basic_string\<char>のエイリアスであることに注目すれば、
Nstd::SafeStringの基底クラスはstd::basic_string\<char>であることがわかる。
この形式は、std::vector\<T>と同形であるため、
Nstd::SafeVectorとNstd::SafeStringの共通コードはテンプレートテンプレートパラメータ
(「[is_same_templ](template_meta_programming.md#SS_13_3_3_7)」参照)を使用し下記のように書ける。


```cpp
    //  example/template/nstd_safe_index.h 8

    namespace Nstd {

    template <template <class...> class C, typename... Ts>
    struct SafeIndex : C<Ts...> {
        using C<Ts...>::C;

        using base_type = C<Ts...>;
        using size_type = typename base_type::size_type;

        typename base_type::reference       operator[](size_type i) { return this->at(i); }
        typename base_type::const_reference operator[](size_type i) const { return this->at(i); }
    };
    }  // namespace Nstd
```

このコードの使用例を兼ねた単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/nstd_safe_index_ut.cpp 8

    auto v_i = Nstd::SafeIndex<std::vector, int>{1, 2};

    static_assert(std::is_same_v<int&, decltype(v_i[0])>);
    static_assert(std::is_base_of_v<std::vector<int>, decltype(v_i)>);
    ASSERT_EQ(1, v_i[0]);
    ASSERT_EQ(2, v_i[1]);
    ASSERT_THROW(v_i[2], std::out_of_range);

    auto str = Nstd::SafeIndex<std::basic_string, char>{"123"};

    static_assert(std::is_same_v<char&, decltype(str[0])>);
    static_assert(std::is_base_of_v<std::string, decltype(str)>);
    ASSERT_EQ(3, str.size());
    ASSERT_EQ("123", str);
    ASSERT_THROW(str[3], std::out_of_range);
```

このままでは使いづらいので下記のようにエイリアスを使い、元のテンプレートと同じ名前を与える。

```cpp
    //  example/template/nstd_safe_index.h 24

    namespace Nstd {

    template <typename T>
    using SafeVector = Nstd::SafeIndex<std::vector, T>;

    using SafeString = Nstd::SafeIndex<std::basic_string, char>;
    }  // namespace Nstd
```

このコードの単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/nstd_safe_index_ut.cpp 54

    auto v_i = Nstd::SafeVector<int>{1, 2};

    static_assert(std::is_same_v<int&, decltype(v_i[0])>);
    static_assert(std::is_base_of_v<std::vector<int>, decltype(v_i)>);
    ASSERT_EQ(1, v_i[0]);
    ASSERT_EQ(2, v_i[1]);
    ASSERT_THROW(v_i[2], std::out_of_range);

    auto str = Nstd::SafeString{"123"};

    static_assert(std::is_same_v<char&, decltype(str[0])>);
    static_assert(std::is_base_of_v<std::string, decltype(str)>);
    ASSERT_EQ(3, str.size());
    ASSERT_EQ("123", str);
    ASSERT_THROW(str[3], std::out_of_range);
```

これで、Nstd::SafeVectorとNstd::SafeStringは統一できたので、
Nstd::SafeIndexにNstd::SafeArrayの実装が取り込めれば、リファクタリングは終了となるが、
残念ながら、下記のコードはコンパイルできない。

```cpp
    //  example/template_cpp17/nstd_safe_index_ut.cpp 44

    // 下記のように書きたいが、パラメータパックは型と値を混在できないのでコンパイルエラー
    auto a_i = Nstd::SafeIndex<std::array, int, 5>{};
```

理由は、パラメータパックにはそのすべてに型を指定するか、そのすべてに値を指定しなければならず、
上記のコードのような型と値の混在が許されていないからである。

値を型に変換する[std::integral_constant](template_meta_programming.md#SS_13_3_1_2)を使用し、この問題を解決できる。
std::arrayから派生した下記のStdArrayLikeは、std::integral_constant::valueから値を取り出し、
基底クラスstd::arrayの第2テンプレートパラメータとする。
この仕組みにより、StdArrayLikeは、
Nstd::SafeIndexのテンプレートテンプレートパラメータとして使用できるようになる。

```cpp
    //  example/template/nstd_safe_index.h 34

    namespace Nstd {
    namespace Inner_ {

    template <typename T, typename U>
    struct std_array_like : std::array<T, U::value> {
        using std::array<T, U::value>::array;

        template <typename... ARGS>
        std_array_like(ARGS... args) noexcept(std::is_nothrow_constructible_v<T, ARGS...>)
            : std::array<T, U::value>{args...}
        {
            static_assert(ConvertibleToAll<T, ARGS...>, "arguemnt error");
        }
    };
    }  // namespace Inner_
    }  // namespace Nstd
```

まずは、このコードの使用例を兼ねた単体テストを下記に示す。

```cpp
    //  example/template_cpp17/nstd_safe_index_ut.cpp 134

    auto sal = Nstd::Inner_::std_array_like<int, std::integral_constant<size_t, 3>>{1, 2, 3};

    static_assert(std::is_nothrow_constructible_v<decltype(sal), int>);  // エクセプション無し生成
    static_assert(std::is_same_v<int&, decltype(sal[0])>);
    static_assert(std::is_base_of_v<std::array<int, 3>, decltype(sal)>);
    ASSERT_EQ(1, sal[0]);
    ASSERT_EQ(2, sal[1]);
    ASSERT_EQ(3, sal[2]);

    using T   = Nstd::Inner_::std_array_like<std::string, std::integral_constant<size_t, 3>>;
    auto sal2 = T{"1", "2", "3"};

    static_assert(!std::is_nothrow_constructible_v<std::string, char const*>);
    static_assert(!std::is_nothrow_constructible_v<T, char const*>);  // エクセプション有り生成
    static_assert(std::is_same_v<std::string&, decltype(sal2[0])>);
    static_assert(std::is_base_of_v<std::array<std::string, 3>, decltype(sal2)>);
    ASSERT_EQ("1", sal2[0]);
    ASSERT_EQ("2", sal2[1]);
    ASSERT_EQ("3", sal2[2]);
```

これを使えば、下記のような記述が可能となる。

```cpp
    //  example/template_cpp17/nstd_safe_index_ut.cpp 157

    using T2   = Nstd::SafeIndex<Nstd::Inner_::std_array_like, std::string, std::integral_constant<size_t, 4>>;
    auto sal_s = T2{"1", "2", "3"};

    static_assert(!std::is_nothrow_constructible_v<T2, char const*>);  // エクセプション有り生成
    static_assert(std::is_same_v<std::string&, decltype(sal_s[0])>);
    static_assert(std::is_base_of_v<std::array<std::string, 4>, decltype(sal_s)>);
    ASSERT_EQ("1", sal_s[0]);
    ASSERT_EQ("2", sal_s[1]);
    ASSERT_EQ("3", sal_s[2]);
    ASSERT_EQ("", sal_s[3]);
    ASSERT_THROW(sal_s[4], std::out_of_range);
```

このままでは使いづらいのでNstd::SafeVector、Nstd::Stringと同様にエイリアスを使えば、
下記のようになる。

```cpp
    //  example/template/nstd_safe_index.h 53

    namespace Nstd {

    template <typename T, size_t N>
    using SafeArray = Nstd::SafeIndex<Nstd::Inner_::std_array_like, T, std::integral_constant<size_t, N>>;
    }  // namespace Nstd
```

このコードの単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/nstd_safe_index_ut.cpp 89

    auto sal_s = Nstd::SafeArray<std::string, 4>{"1", "2", "3"};

    static_assert(std::is_same_v<std::string&, decltype(sal_s[0])>);
    static_assert(std::is_base_of_v<std::array<std::string, 4>, decltype(sal_s)>);
    ASSERT_EQ("1", sal_s[0]);
    ASSERT_EQ("2", sal_s[1]);
    ASSERT_EQ("3", sal_s[2]);
    ASSERT_EQ("", sal_s[3]);
    ASSERT_THROW(sal_s[4], std::out_of_range);
```

これにより、当初の目的であったコードクローンの除去が完了した。
この効果により、下記に示したような拡張もコードクローンせずに簡単に行えるようになった。

```cpp
    //  example/template/nstd_safe_index.h 61

    namespace Nstd {

    using SafeStringU16 = Nstd::SafeIndex<std::basic_string, char16_t>;
    using SafeStringU32 = Nstd::SafeIndex<std::basic_string, char32_t>;
    }  // namespace Nstd
```

```cpp
    //  example/template_cpp17/nstd_safe_index_ut.cpp 112

    auto u16str = Nstd::SafeStringU16{u"あいうえお"};

    static_assert(std::is_same_v<char16_t&, decltype(u16str[0])>);
    static_assert(std::is_base_of_v<std::u16string, decltype(u16str)>);
    ASSERT_EQ(5, u16str.size());
    ASSERT_EQ(u"あいうえお", u16str);
    ASSERT_THROW(u16str[5], std::out_of_range);

    auto u32str = Nstd::SafeStringU32{U"かきくけこ"};

    static_assert(std::is_same_v<char32_t&, decltype(u32str[0])>);
    static_assert(std::is_base_of_v<std::u32string, decltype(u32str)>);
    ASSERT_EQ(5, u32str.size());
    ASSERT_EQ(U"かきくけこ", u32str);
    ASSERT_THROW(u32str[5], std::out_of_range);
```

### Nstd::SafeIndexのoperator\<\<の開発 <a id="SS_13_4_3"></a>
ここでは、Nstd::SafeIndexのoperator\<\<の開発を行う。

他のoperator\<\<との間で定義が曖昧にならないようにするためには、
テンプレートテンプレートパラメータを使って以下のようにすることが考えられる。

```cpp
    //  example/template_cpp17/safe_index_put_to_ut.cpp 8

    template <template <class...> class C, typename... Ts>
    std::ostream& operator<<(std::ostream& os, Nstd::SafeIndex<C, Ts...> const& safe_index)
    {
        auto sep = "";

        for (auto const& i : safe_index) {
            os << std::exchange(sep, ", ") << i;
        }

        return os;
    }
```

以下の単体テストで動作確認する。

```cpp
    //  example/template_cpp17/safe_index_put_to_ut.cpp 25
    {
        auto v_i = Nstd::SafeVector<int>{1, 2};

        auto oss = std::ostringstream{};
        oss << v_i;
        ASSERT_EQ("1, 2", oss.str());
    }
    {
        auto sal_s = Nstd::SafeArray<std::string, 4>{"1", "2", "3"};
        auto oss   = std::ostringstream{};
        oss << sal_s;
        ASSERT_EQ("1, 2, 3, ", oss.str());  // 4番目には何も入っていない
    }
```

ここまではうまく行っているが、以下の単体テストによりバグが発覚する。

```cpp
    //  example/template_cpp17/safe_index_put_to_ut.cpp 40

    {
        auto s_str = Nstd::SafeString{"hello"};
        auto oss   = std::ostringstream{};
        oss << s_str;

        // ASSERT_EQ("hello", oss.s_str());     // これがパス出来たらよいが、
        ASSERT_EQ("h, e, l, l, o", oss.str());  // 実際にはこのようになる。
    }
    {
        auto str = std::string{"hello"};  // 上記と比較のためのstd::stringでのoperator<<

        auto oss = std::ostringstream{};
        oss << str;
        ASSERT_EQ("hello", oss.str());
    }
```

この原因は、Nstd::SafeStringオブジェクトに対して、std::operator<<が使用されなかったからである。

「[メタ関数のテクニック](template_meta_programming.md#SS_13_3)」で紹介したSFINAEによりこの問題を回避できるが、
ここでも、すでにみてきた[コンセプト](term_explanation.md#SS_19_11_2)による制約によりこの問題に対処する。

```cpp
    //  example/template_cpp17/safe_index_put_to_ut.cpp 98


    #if __cplusplus >= 202002L  // c++20
    namespace Inner_ {
    template <typename T>
    concept not_safe_string = !std::is_same_v<T, Nstd::SafeString>;
    }
    #endif

    template <template <class...> class C, typename... Ts>
    #if __cplusplus >= 202002L  // c++20
    auto operator<<(std::ostream& os, Nstd::SafeIndex<C, Ts...> const& safe_index) -> std::ostream& 
        requires Inner_::not_safe_string<Nstd::SafeIndex<C, Ts...>> // enable_ifによるSFINAEを避け、

    #else  // c++17
    auto operator<<(std::ostream& os, Nstd::SafeIndex<C, Ts...> const& safe_index) ->
        typename std::enable_if_t<    // safe_indexがSafeString型ならば、SFINAEにより非活性化
            !std::is_same_v<Nstd::SafeIndex<C, Ts...>, Nstd::SafeString>, std::ostream&>
    #endif
    {  // コンセプトによる制約
        auto sep = "";

        for (auto const& i : safe_index) {
            os << std::exchange(sep, ", ") << i;
        }

        return os;
    }
```

これにより先ほど問題が発生した単体テストも下記のようにパスする。

```cpp
    //  example/template_cpp17/safe_index_put_to_ut.cpp 145

    auto str = Nstd::SafeString{"hello"};
    auto oss = std::ostringstream{};
    oss << str;
    ASSERT_EQ("hello", oss.str());  // std::operator<<が使われる
    // ASSERT_EQ("h, e, l, l, o", oss.str());
```


### コンテナ用Nstd::operator\<\<の開発 <a id="SS_13_4_4"></a>
「[Nstd::SafeIndexのoperator\<\<の開発](template_meta_programming.md#SS_13_4_3)」で定義したNstd::operator\<\<の構造は、
範囲for文に適用できる配列やstdコンテナにも使えるため、ここではその拡張を考える。

すでに述べたように注意すべきは、

* 使い勝手の良いstd::operator\<\<(例えばchar[N]やstd::stringのoperator\<\<)はそのまま使う
* ほとんど使い物にならないstd::operator\<\<(例えば、int[N]のような配列に対するoperator\<\<(void\*))
  の代わりに、ここで拡張するNstd::operator\<\<を使う

であるため、型Tが新しいNstd::operator\<\<を使用できる条件は、

* Tの型が、以下の条件を満たす
    * T == U[N]であった場合、Uはcharではない
    * std::stringおよびその派生型ではない
* Nstd::ValueType\<T>::typeがoperator\<\<を持つ

となるだろう。この条件を診断するためのメタ関数は以下のようになる。

```cpp
    //  example/template/nstd_put_to.h 17

    namespace Nstd {
    namespace Inner_ {

    template <typename T>  // Nstd::Printableを使用するとg++のバグで、問題が発生するため、
                           // バグ回避のため敢えてここでNstd::Inner_::Printableを宣言する
    concept Printable = requires(T t, std::ostream& os)
    {
        { os << t } -> std::same_as<std::ostream&>;
    };

    template <typename T>
    constexpr bool enable_range_put_to() noexcept
    {
        if constexpr (Nstd::ValueType<T>::IsBuiltinArray) {  // Tは配列
            if constexpr (std::is_same_v<char,
                                         typename Nstd::ValueType<T>::type_direct>) {  // Tはchar配列
                return false;
            }
            else {
                return Nstd::Printable<typename Nstd::ValueTypeT<T>>;
            }
        }
        else {  // Tは配列ではない
            if constexpr (Printable<T>) {
                return false;
            }
            else {
                if constexpr (Nstd::IsRangeV<T>) {  // 範囲for文に適用できる
                    return Nstd::Printable<typename Nstd::ValueTypeT<T>>;
                }
                else {
                    return false;
                }
            }
        }
    }

    template <typename T>
    constexpr bool enable_range_put_to_v{enable_range_put_to<T>()};
    }  // namespace Inner_
    }  // namespace Nstd
```

ただし、このようなコードはコンパイラのバグによりコンパイルできないことがある。
実際、現在使用中の[g++](term_explanation.md#SS_19_20_1)ではこのコードはコンパイルできず、
上記コードでコメントにも書いた通り、Inner_の中でPrintableを再定義することで、
そのワークアラウンドを行っている。

このような場合、条件分岐に三項演算子や中間式にconstexprを使うことで回避できることが多い。
このような複雑なメタ関数には単体テストは必須である。

```cpp
    //  example/template/test_class.h 3

    class test_class_exits_put_to {
    public:
        test_class_exits_put_to(int i = 0) noexcept : i_{i} {}
        int get() const noexcept { return i_; }

    private:
        int i_;
    };

    inline std::ostream& operator<<(std::ostream& os, test_class_exits_put_to const& p) { return os << p.get(); }

    class test_class_not_exits_put_to {};
```

```cpp
    //  example/template/nstd_put_to_ut.cpp 31

    static_assert(enable_range_put_to_v<int[3]>);                         // Nstd::operator<<
    static_assert(!enable_range_put_to_v<char[3]>);                       // std::operator<<
    static_assert(!enable_range_put_to_v<int>);                           // std::operator<<
    static_assert(enable_range_put_to_v<std::vector<int>>);               // Nstd::operator<<
    static_assert(enable_range_put_to_v<std::vector<std::vector<int>>>);  // Nstd::operator<<
    static_assert(!enable_range_put_to_v<std::string>);                   // std::operator<<
    static_assert(enable_range_put_to_v<std::vector<std::string>>);       // Nstd::operator<<

    static_assert(!enable_range_put_to_v<test_class_not_exits_put_to>);               // operator<<無し
    static_assert(!enable_range_put_to_v<test_class_exits_put_to>);                   // ユーザ定義operator<<
    static_assert(!enable_range_put_to_v<std::vector<test_class_not_exits_put_to>>);  // operator<<無し
    static_assert(enable_range_put_to_v<std::vector<test_class_exits_put_to>>);       // Nstd::operator<<
    static_assert(!enable_range_put_to_v<std::list<test_class_not_exits_put_to>>);    // operator<<無し
    static_assert(enable_range_put_to_v<std::list<test_class_exits_put_to>>);         // Nstd::operator<<
```

以上によりstd::enable_ifの第1引数に渡す値(enable_range_put_to_vはconstexpr)が用意できたので、
Nstd::operator\<\<は下記のように定義できる。

```cpp
    //  example/template/nstd_put_to.h 64

    namespace Nstd {
    namespace Inner_ {

    template <size_t N>
    constexpr std::string_view range_put_to_sep() noexcept
    {
        static_assert(N != 0);
        switch (N) {
        case 1:
            return ", ";
        case 2:
            return " | ";
        case 3:
        default:
            return " # ";
        }
    };

    template <typename T>
    concept range_put_to = Inner_::enable_range_put_to_v<T>;
    }  // namespace Inner_

    template <typename T>
    auto operator<<(std::ostream& os, T const& t) ->
        typename std::enable_if_t<Inner_::enable_range_put_to_v<T>, std::ostream&>
    // std::enable_if_t<Inner_::enable_range_put_to_v<T>を使わずに上のrange_put_toを使いたいが、
    // コンパイラのバグによりコンパイルできない
    {
        auto sep = std::string_view("");
        auto s   = Inner_::range_put_to_sep<ValueType<T>::Nest>();

        for (auto const& i : t) {
            os << std::exchange(sep, s) << i;
        }

        return os;
    }
    }  // namespace Nstd
```

値表示用のセパレータに","のみを用いるとコンテナや配列が多次元(ValueType::Nest > 2)の場合、
各次元でのデータの判別が難しくなるため、ValueType::Nestの値によってセパレータの種類を変える
range_put_to_sep<>()を用意した。
下記単体テストでわかる通り、この効果により値の構造が見やすくなっている。

まずは、配列の単体テストを示す。

```cpp
    //  example/template/nstd_put_to_ut.cpp 111

    using namespace Nstd;
    {
        char str[] = "abcdef";
        auto oss   = std::ostringstream{};

        oss << str;  // std::operator<<
        ASSERT_EQ(str, oss.str());
    }
    {
        char str[2][4] = {"abc", "def"};
        auto oss       = std::ostringstream{};

        oss << str;  // Nstd::operator<<
        ASSERT_EQ("abc | def", oss.str());
    }
    {
        test_class_exits_put_to p1[3]{1, 2, 3};
        auto                    oss = std::ostringstream{};

        oss << p1;  // Nstd::operator<<
        ASSERT_EQ("1, 2, 3", oss.str());
    }
    {
        char const* str[] = {"abc", "def", "ghi"};
        auto        oss   = std::ostringstream{};

        oss << str;  // Nstd::operator<<
        ASSERT_EQ("abc, def, ghi", oss.str());
    }
    {
        int  v[2][3][2]{{{0, 1}, {2, 3}, {4, 5}}, {{6, 7}, {8, 9}, {10, 11}}};
        auto oss = std::ostringstream{};

        oss << v;
        ASSERT_EQ("0, 1 | 2, 3 | 4, 5 # 6, 7 | 8, 9 | 10, 11", oss.str());
    }
```

次に、コンテナの単体テストを示す。

```cpp
    //  example/template/nstd_put_to_ut.cpp 168

    using namespace Nstd;
    {
        auto v   = std::vector<int>{1, 2, 3};
        auto oss = std::ostringstream{};

        oss << v;
        ASSERT_EQ("1, 2, 3", oss.str());
    }
    {
        auto p1  = std::list<test_class_exits_put_to>{1, 2, 3, 4};
        auto oss = std::ostringstream{};

        oss << p1;
        ASSERT_EQ("1, 2, 3, 4", oss.str());
    }
    {
        std::vector<int> v[2]{{1, 2}, {3, 4, 5}};  // std::vectorの配列
        auto             oss = std::ostringstream{};

        oss << v;
        ASSERT_EQ("1, 2 | 3, 4, 5", oss.str());
    }
```

最後に、Nstd::SafeIndexの単体テストを示す。

```cpp
    //  example/template/nstd_put_to_ut.cpp 218

    {
        auto sal_s = Nstd::SafeArray<std::string, 4>{"1", "2", "3"};
        auto oss   = std::ostringstream{};

        oss << sal_s;
        ASSERT_EQ("1 | 2 | 3 | ", oss.str());
    }
    {
        auto sv  = Nstd::SafeVector<Nstd::SafeArray<Nstd::SafeString, 2>>{{"ab", "cd"}, {"ef", "gh"}};
        auto oss = std::ostringstream{};

        oss << sv;
        ASSERT_EQ("ab | cd # ef | gh", oss.str());
    }
```

## Nstdライブラリの開発3(浮動小数点関連) <a id="SS_13_5"></a>
[浮動小数点型](term_explanation.md#SS_19_1_12)を頻繁に使用するソフトウェアの開発を行うに場合、
ソースコードの中で、場当たり的に浮動小数点型を使用すると、
[浮動小数点の誤差](term_explanation.md#SS_19_1_12_2)や[浮動小数点の演算エラー](term_explanation.md#SS_19_1_12_4)
にまつわるバグの修正に多くの工数をロスしてしまうことになる。

これらの課題に対処するため、この節は浮動小数点演算によるバグを未然に防ぎ、
精度を確保するための機能を提供することを目的としている。
[浮動小数点の比較](template_meta_programming.md#SS_13_5_1)方法や、
浮動小数点を避けて高精度な演算を実現する[固定小数点クラス](template_meta_programming.md#SS_13_5_2)および[有理数クラス](template_meta_programming.md#SS_13_5_4)を導入し、
さらにそれらを簡単に使用できるリテラル表記もサポートしている。

### 浮動小数点の比較 <a id="SS_13_5_1"></a>
浮動小数点の演算には下記に示したような問題が起こり得るため、単純な==の比較はできない。

```cpp
    //  example/template_cpp17/nstd_float_ut.cpp 9

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    ASSERT_FALSE(0.05F == a + b);  // a + b == 0.05Fは一般には成立しない。
```

この問題に対処するのが以下のコードである。

```cpp
    //  example/template_cpp17/nstd_float_ut.cpp 17

    float epsilon  = std::abs(0.05F - (a + b));
    bool  is_equal = epsilon <= std::numeric_limits<float>::epsilon();
    ASSERT_TRUE(is_equal);
```

単なる浮動小数変数の比較にこのようなコードを書くのは間違えやすいし、非効率であるため、
下記のような関数(float用とdouble用)で対処することが一般的である。

```cpp
    //  example/template_cpp17/nstd_float_ut.cpp 25

    namespace Nstd {

    /// @brief float比較用関数
    bool is_equal_f(float lhs, float rhs) noexcept { return std::abs(lhs - rhs) <= std::numeric_limits<float>::epsilon(); }

    /// @brief double比較用関数
    bool is_equal_d(double lhs, double rhs) noexcept
    {
        return std::abs(lhs - rhs) <= std::numeric_limits<double>::epsilon();
    }
```
実際に使う場面を以下に示す。

```cpp
    //  example/template_cpp17/nstd_float_ut.cpp 41

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    // floatの比較はis_equal_fのような関数を使う。
    bool is_equal = Nstd::is_equal_f(0.05F, a + b);
    ASSERT_TRUE(is_equal);
```

一見これで万事うまくいくように見えるが、そうは行かないことを以下の例で示す。

```cpp
    //  example/template_cpp17/nstd_float_ut.cpp 56

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    // a + bはfloatの精度のまま、is_equal_dの引数の型であるdoubleに昇格される。
    // 一方、0.05はdoubleであるため(循環小数をdoubleの精度で切り捨てた値であるため)、
    // a + b(floatの精度の値)と0.05の差はdoubleのepsilonを超える。
    //  ASSERT_TRUE(is_equal_d(0.05, a + b));  // NG
    ASSERT_FALSE(Nstd::is_equal_d(0.05, a + b));
```

dobuleとfloatを1つの式に混載するとfloatがdoubleに昇格されるため、このような問題が起こり得る。
これに対処する方法を以下に示す。

```cpp
    //  example/template_cpp17/nstd_float_ut.cpp 71

    namespace Nstd {
    // is_equal_dを改良して、引数の型が統一されていない呼び出しをコンパイルエラーにできるようにした。
    /// @brief 浮動小数点比較用関数
    template <typename FLOAT_0, typename FLOAT_1>
    bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs) noexcept
    {
        static_assert(std::is_floating_point_v<FLOAT_0>);
        static_assert(std::is_same_v<FLOAT_0, FLOAT_1>);

        return std::abs(lhs - rhs) <= std::numeric_limits<FLOAT_0>::epsilon();
    }
    }  // namespace Nstd
```

この関数のテストは以下の通りである。

```cpp
    //  example/template_cpp17/nstd_float_ut.cpp 88

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    // a + bはfloatであり、0.05はdoubleであるため、下記コードはコンパイルできない。
    // ASSERT_TRUE(Nstd::is_equal(0.05, a + b));
    ASSERT_TRUE(Nstd::is_equal(0.05F, a + b));  // OK リテラルに型を指定して、引数の型を統一
```

通常の浮動小数の比較は相対誤差を指定できる必要性がある場合が多いため、
さらに下記のように拡張変更した。

```cpp
    //  example/template_cpp17/nstd_float_ut.cpp 103

    /// @brief 浮動小数点比較用関数
    /// 相対誤差を考慮して、lhs と rhs の絶対値に基づくトレランスの範囲内での比較を行う。
    /// これにより、数値の大小に関わらず、適切な誤差で比較できる。
    template <typename FLOAT_0, typename FLOAT_1>
    bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs, FLOAT_0 tolerance = std::numeric_limits<FLOAT_0>::epsilon()) noexcept
    {
        static_assert(std::is_floating_point_v<FLOAT_0>);
        static_assert(std::is_same_v<FLOAT_0, FLOAT_1>);

        return std::abs(lhs - rhs) <= tolerance * std::max(std::abs(lhs), std::abs(rhs));
    }
```

この関数のテストは以下の通りである。

```cpp
    //  example/template_cpp17/nstd_float_ut.cpp 121

    float a = 1000000.0F;
    float b = 1000000.1F;

    ASSERT_FALSE(Nstd::is_equal(a, b));       // a, bはほぼ同じだが。
    ASSERT_TRUE(Nstd::is_equal(a, b, 0.1F));  // 相対誤差を指定できる。
```

### 固定小数点クラス <a id="SS_13_5_2"></a>
以上で見てきたように浮動小数点の扱いはやや面倒であるため、
浮動小数点のダイナミックレンジが必要な場合以外では安易に浮動小数点を使うべきでない。

従って、intやlong等のダイナミックレンジで表現できる1未満の値が必要な場合、
intやlongの値を100倍などのスケーリングして使うのが、浮動小数点の微妙な問題を避ける手段となる。
スケーリングとは、
整数型変数変数のスケーリングとは、intやlongの値を、
特定の倍率で拡大することで小数点以下の値を扱う方法を指す。
例えば、100倍にスケーリングして「1.23」を「123」として整数で表現するようする。
この方法は浮動小数点の代わりに使えるが、
スケーリング値を常に意識する必要があり、コードの可読性や保守性に影響を与える問題がある。

以下に示す固定小数点クラス(FixedPoint)はこれらの問題を解決できる。

```cpp
    //  example/template_cpp17/fixed_point.h 7

    namespace Nstd {
    /// @brief BASIC_TYPEで指定する基本型のビット長を持つ固定小数点を扱うためのクラス
    /// @tparam BASIC_TYPE       全体のビット長や、符号を指定するための整数型
    /// @tparam FRACTION_BIT_NUM 小数点保持のためのビット長
    template <typename BASIC_TYPE, uint32_t FRACTION_BIT_NUM>
    class FixedPoint {
    public:
        constexpr FixedPoint(BASIC_TYPE integer = 0, typename std::make_unsigned_t<BASIC_TYPE> fraction = 0) noexcept
            : value_{get_init_value(integer, fraction)}
        {
            // signedに対する右ビットシフトの仕様が、算術右ビットシフトでないと
            // このクラスは成立しない。下記のstatic_assertはその確認。
            static_assert(IsSigned() ? (-1 >> 1 == -1) : true, "need logical right bit sift");

            // BASIC_TYPEをcharにすることは認めない。
            static_assert(!std::is_same_v<BASIC_TYPE, char>, "BASIC_TYPE should not be char");
        }

        // 以下、特殊メンバ定義
        ~FixedPoint()                                = default;
        FixedPoint(FixedPoint const&)                = default;
        FixedPoint& operator=(FixedPoint const&)     = default;
        FixedPoint(FixedPoint&&) noexcept            = default;
        FixedPoint& operator=(FixedPoint&&) noexcept = default;

        // 以下、インターフェース定義
        constexpr BASIC_TYPE GetValue() const noexcept { return value_; }
        constexpr BASIC_TYPE GetInteger() const noexcept { return value_ >> fraction_bit_num_; }
        constexpr BASIC_TYPE GetFraction() const noexcept { return value_ & fraction_bit_mask_; }

        /// @brief doubleに変換する
        constexpr double ToFloatPoint() const noexcept
        {
            return GetInteger() + (static_cast<double>(GetFraction()) / (fraction_bit_mask_ + 1));
        }

        /// @brief 小数部のビット長を返す
        constexpr typename std::make_unsigned_t<BASIC_TYPE> GetFractionMask() const noexcept { return fraction_bit_mask_; }

        /// @brief 整数部のビット長を返す
        constexpr typename std::make_unsigned_t<BASIC_TYPE> GetIntegerMask() const noexcept { return integer_bit_mask_; }

        static constexpr bool IsSigned() noexcept { return std::is_signed_v<BASIC_TYPE>; }

        static constexpr bool IsUnsigned() noexcept { return std::is_unsigned_v<BASIC_TYPE>; }

        /// @brief    以下operator @=の定義
        FixedPoint& operator+=(FixedPoint rhs) noexcept
        {
            value_ += rhs.value_;
            return *this;
        }

        FixedPoint& operator-=(FixedPoint rhs) noexcept
        {
            value_ -= rhs.value_;
            return *this;
        }

        FixedPoint& operator*=(FixedPoint rhs) noexcept
        {
            value_ *= rhs.value_ >> fraction_bit_num_;
            return *this;
        }

        FixedPoint& operator/=(FixedPoint rhs) noexcept
        {
            using T = std::conditional_t<IsSigned(), int64_t, uint64_t>;

            value_ = (static_cast<T>(value_) << fraction_bit_num_) / rhs.value_;

            return *this;
        }

    private:
        BASIC_TYPE value_;  // FixedPointの実際の値

        static constexpr uint32_t bit_mask(uint32_t bit_len) noexcept
        {
            if (bit_len == 0) {
                return 0x0;
            }

            return bit_mask(bit_len - 1) | (0x01 << (bit_len - 1));
        }

        static constexpr uint32_t fraction_bit_num_{FRACTION_BIT_NUM};
        static constexpr uint32_t fraction_bit_mask_{bit_mask(fraction_bit_num_)};
        static constexpr uint32_t integer_bit_num_{sizeof(BASIC_TYPE) * 8 - FRACTION_BIT_NUM};
        static constexpr uint32_t integer_bit_mask_{bit_mask(integer_bit_num_) << fraction_bit_num_};

        static constexpr BASIC_TYPE get_init_value(BASIC_TYPE integer, BASIC_TYPE fraction) noexcept
        {
            // 本来は左シフト<<を使いたいが、signedに対しての<<ランタイム実装依存であるので、
            // return (integer << fraction_bit_num_) | fraction;

            return (integer * (fraction_bit_mask_ + 1)) | fraction;
        }

        /// 以下比較演算子の定義

    #if __cplusplus >= 202002L  // c++20
        friend auto operator<=>(FixedPoint lhs, FixedPoint rhs) noexcept = default;

    #else  // c++17
        friend bool operator==(FixedPoint lhs, FixedPoint rhs) noexcept { return lhs.value_ == rhs.value_; }

        friend bool operator!=(FixedPoint lhs, FixedPoint rhs) noexcept { return !(lhs == rhs); }

        friend bool operator>(FixedPoint lhs, FixedPoint rhs) noexcept { return lhs.value_ > rhs.value_; }

        friend bool operator>=(FixedPoint lhs, FixedPoint rhs) noexcept { return (lhs > rhs) || (lhs == rhs); }

        friend bool operator<(FixedPoint lhs, FixedPoint rhs) noexcept { return (rhs > lhs); }

        friend bool operator<=(FixedPoint lhs, FixedPoint rhs) noexcept { return (lhs < rhs) || (lhs == rhs); }
    #endif

        /// @brief FixedPoint() + intのようなオーバーロードを作るためにあえてfriend
        friend FixedPoint operator+(FixedPoint lhs, FixedPoint rhs) noexcept
        {
            lhs += rhs;
            return lhs;
        }

        friend FixedPoint operator-(FixedPoint lhs, FixedPoint rhs) noexcept
        {
            lhs -= rhs;
            return lhs;
        }

        friend FixedPoint operator*(FixedPoint lhs, FixedPoint rhs) noexcept
        {
            lhs *= rhs;
            return lhs;
        }

        friend FixedPoint operator/(FixedPoint lhs, FixedPoint rhs) noexcept
        {
            lhs /= rhs;
            return lhs;
        }
    };
```

FixedPointの単体テストコードを以下に示す。

```cpp
    //  example/template_cpp17/fixed_point_ut.cpp 21

    // 以下は、FixedPoint<>の使用例である。
    using FP4 = Nstd::FixedPoint<uint8_t, 4>;  // 基本型uint8_t、小数点4ビット
    auto fp0  = FP4{};

    ASSERT_FALSE(fp0.IsSigned());
    ASSERT_TRUE(fp0.IsUnsigned());

    fp0 = 7;    ASSERT_EQ(7, fp0);
    fp0 = 7;    ASSERT_NE(6, fp0);
    fp0 += 2;   ASSERT_EQ(FP4{9}, fp0);         
                ASSERT_DOUBLE_EQ(9.0, fp0.ToFloatPoint());
    fp0 /= 2;   ASSERT_EQ((FP4{4, 8}), fp0);    
                ASSERT_DOUBLE_EQ(4.5, fp0.ToFloatPoint());
    fp0 /= 2;   ASSERT_EQ((FP4{2, 4}), fp0);    
                ASSERT_DOUBLE_EQ(2.25, fp0.ToFloatPoint());
    fp0 *= 4;   ASSERT_EQ(FP4{9}, fp0);
    fp0 += 7;   ASSERT_EQ(FP4{0}, fp0);
```

### 固定小数点リテラル <a id="SS_13_5_3"></a>
[固定小数点クラス](template_meta_programming.md#SS_13_5_2)のようなクラス定義には、以下に示すようにユーザ定義リテラルを定義し、
使い勝手のよい環境をユーザに提供するべきである。

```cpp
    //  example/template_cpp17/fixed_point.h 156

    namespace Nstd {
    namespace fixed_point_literals {
    // FixedPoint<int32_t, 8> 用のユーザ定義リテラル
    FixedPoint<int32_t, 8> operator"" _fxp(unsigned long long int val)
    {
        // 整数部分を取り、FixedPoint<int32_t, 8>のインスタンスを作成
        return FixedPoint<int32_t, 8>(static_cast<int32_t>(val));
    }

    FixedPoint<int32_t, 8> operator"" _fxp(long double val)
    {
        // 浮動小数点数からFixedPoint<int32_t, 8>のインスタンスを作成
        int32_t integer_part  = static_cast<int32_t>(val);
        int32_t fraction_part = static_cast<int32_t>((val - integer_part) * 256);  // 2^8 = 256
        return FixedPoint<int32_t, 8>(integer_part, fraction_part);
    }
    }  // namespace fixed_point_literals
    }  // namespace Nstd
```

以上のコードの単体テストを以下に示す。これにより使用方も明らかになるだろう。

```cpp
    //  example/template_cpp17/fixed_point_ut.cpp 171

    using namespace Nstd::fixed_point_literals;

    auto a = 123_fxp;  // 整数リテラル

    EXPECT_EQ(a.GetInteger(), 123);
    EXPECT_EQ(a.GetFraction(), 0);  // 小数部は0のはず

    auto b      = 50.25_fxp;
    auto result = a + b;

    EXPECT_NEAR(result.ToFloatPoint(), 173.25, 0.01);
```

### 有理数クラス <a id="SS_13_5_4"></a>
[固定小数点クラス](template_meta_programming.md#SS_13_5_2)では精度が足りず、浮動小数点を使用したくない場合、
以下のコードで示す有理数クラスがちょうどよい選択となることがある。

```cpp
    //  example/template_cpp17/rational.h 10

    namespace Nstd {
    /// @brief ユーザー指定の型で分数を扱うためのクラス
    /// @tparam T 基本の整数型（デフォルトはint32_t）
    #if __cplusplus >= 202002L  // c++20
    template <std::signed_integral T = int32_t>
    #else  // c++17
    template <typename T = int32_t>
    #endif
    class Rational {
    public:
        using underlying_type_t = T;
        /// @brief コンストラクタ
        /// @param num 分子
        /// @param deno 分母
        constexpr Rational(T num, T deno = 1) : value_{reduce(num, deno)} {}
        T getNumerator() const noexcept { return value_.num; }
        T getDenominator() const noexcept { return value_.deno; }
        /// @brief 2項演算子(四則演算)の定義
        Rational operator+(const Rational& rhs) const noexcept
        {
            T num  = value_.num * rhs.value_.deno + rhs.value_.num * value_.deno;
            T deno = value_.deno * rhs.value_.deno;
            return Rational{num, deno};
        }
        Rational operator-(const Rational& rhs) const noexcept
        {
            T num  = value_.num * rhs.value_.deno - rhs.value_.num * value_.deno;
            T deno = value_.deno * rhs.value_.deno;
            return Rational{num, deno};
        }
        Rational operator*(const Rational& rhs) const noexcept
        {
            return Rational{value_.num * rhs.value_.num, value_.deno * rhs.value_.deno};
        }
        Rational operator/(const Rational& rhs) const noexcept
        {
            return Rational(value_.num * rhs.value_.deno, value_.deno * rhs.value_.num);
        }
        /// @brief 複合代入演算子(四則演算)の定義
        Rational& operator+=(Rational const& rhs)
        {
            *this = *this + rhs;
            return *this;
        }
        Rational& operator-=(Rational const& rhs)
        {
            *this = *this - rhs;
            return *this;
        }
        Rational& operator*=(Rational const& rhs)
        {
            *this = *this * rhs;
            return *this;
        }
        Rational& operator/=(Rational const& rhs)
        {
            *this = *this / rhs;
            return *this;
        }
        /// @brief 単項演算子の定義
        constexpr Rational operator+() const noexcept { return *this; }
        constexpr Rational operator-() const noexcept { return Rational{-value_.num, value_.deno}; }
        /// @brief 比較演算子の定義
    #if __cplusplus >= 202002L  // c++20
        friend bool operator==(Rational const& lhs, Rational const& rhs) noexcept = default;
        friend auto operator<=>(Rational const& lhs, Rational const& rhs) noexcept
        {
            return (lhs.value_.num * rhs.value_.deno) <=> (rhs.value_.num * lhs.value_.deno);
        }

    #else  // c++17
        friend bool operator==(Rational const& lhs, Rational const& rhs) noexcept
        {
            return (lhs.value_.num * rhs.value_.deno) == (rhs.value_.num * lhs.value_.deno);
        }
        friend bool operator!=(Rational const& lhs, Rational const& rhs) noexcept { return !(lhs == rhs); }
        friend bool operator<(Rational const& lhs, Rational const& rhs) noexcept
        {
            return (lhs.value_.num * rhs.value_.deno) < (rhs.value_.num * lhs.value_.deno);
        }
        friend bool operator<=(Rational const& lhs, Rational const& rhs) noexcept { return !(rhs < lhs); }
        friend bool operator>(Rational const& lhs, Rational const& rhs) noexcept { return rhs < lhs; }
        friend bool operator>=(Rational const& lhs, Rational const& rhs) noexcept { return !(lhs < rhs); }
    #endif
        /// @brief put-to演算子の定義
        friend std::ostream& operator<<(std::ostream& os, const Rational& rhs)
        {
            return (rhs.value_.deno == 1) ? os << rhs.value_.num : os << rhs.value_.num << "/" << rhs.value_.deno;
        }

        /// @brief doubleへの変換演算子
        /// @brief doubleで表現可能な場合のみ利用可能
        template <typename U = T>
        explicit operator double() const noexcept
    #if __cplusplus >= 202002L  // c++20
            requires std::is_convertible_v<U, double>
    #endif
        {
            return static_cast<double>(value_.num) / static_cast<double>(value_.deno);
        }

    private:
        struct rational_t {
            T num;
            T deno;

    #if __cplusplus >= 202002  // c++20
            friend bool operator==(rational_t const& lhs, rational_t const& rhs) noexcept = default;

    #else  // c++17
            friend bool operator==(rational_t const& lhs, rational_t const& rhs) noexcept
            {
                return lhs.num == rhs.num && lhs.deno == rhs.deno;
            }
    #endif
        };
        /// @brief num/denoを約分して、rational_tで返す
        static rational_t reduce(T num, T deno) noexcept
        {
            T const gcd = std::gcd(num, deno);
            num /= gcd;
            deno /= gcd;
            if (deno < 0) {  // 分母を正に保つ
                return {-num, -deno};
            }
            else {
                return {num, deno};
            }
        }

    private:
        rational_t value_;
    };
    }  // namespace Nstd
```
```cpp
    //  example/template_cpp17/rational_ut.cpp 12

    auto       r1    = Rational{1, 2};
    const auto r1_sv = r1;
    auto       r2    = Rational{1, 3};

    ASSERT_GE(r1, r2);

    r1 += r2;  // operator+
    ASSERT_EQ((Rational{5, 6}), r1);
    r1 = r1_sv;

    r1 -= r2;
    ASSERT_EQ((Rational{1, 6}), r1);
    r1 = r1_sv;

    auto oss = std::ostringstream{};
    oss << r1;
    ASSERT_EQ("1/2", oss.str());  // operator<<
```

### 有理数リテラル <a id="SS_13_5_5"></a>
[固定小数点クラス](template_meta_programming.md#SS_13_5_2)に対して、[固定小数点リテラル](template_meta_programming.md#SS_13_5_3)を定義したように、
使い勝手のよい環境をユーザに提供するために、
[有理数クラス](template_meta_programming.md#SS_13_5_4)に対して、有理数リテラルを定義するべきである。

```cpp
    //  example/template_cpp17/rational.h 147

    namespace Nstd {
    /// @brief Rational<int32_t>をユーザ定義リテラルとして扱うためのオペレータ
    ///        _rn: rational number
    ///  @param N/Mの形式の文字列リテラル
    Rational<int32_t> operator"" _rn(char const* str, size_t)
    {
        std::string_view input{str};
        size_t           sep = input.find('/');

        if (sep == std::string::npos) {
            throw std::invalid_argument("invalid formt for user-defined rational number");
        }

        int32_t num  = std::stoi(str);
        int32_t deno = std::stoi(input.substr(sep + 1).data());

        return {num, deno};
    }
    }  // namespace Nstd
```
```cpp
    //  example/template_cpp17/rational_ut.cpp 55

    auto r1 = "1/2"_rn;
    auto r2 = "1/3"_rn;

    ASSERT_GE(r1, r2);
    ASSERT_DOUBLE_EQ(static_cast<double>(r1), 0.5);
```

## ログ取得ライブラリの開発2 <a id="SS_13_6"></a>
ログ取得ライブラリでの問題は「Logging名前空間が依存してよい名前空間」に

```cpp
    //  example/template/app_ints.h 6

    namespace App {
    using Ints_t = std::vector<int>;
    }
```

のようなコンテナに共通したoperator<<を定義することで解決する。
それは 「[コンテナ用Nstd::operator\<\<の開発](template_meta_programming.md#SS_13_4_4)」で示したコードそのものであるため、
これを使い、問題を解決したログ取得ライブラリを以下に示す。

```cpp
    //  example/template/logger.h 7

    namespace Logging {
    class Logger {
    public:
        static Logger&       Inst();
        static Logger const& InstConst() { return Inst(); }

        std::string Get() const;  // ログデータの取得
        void        Clear();      // ログデータの消去

        template <typename... ARGS>  // ログの登録
        void Set(char const* filename, uint32_t line_no, ARGS const&... args)
        {
            oss_.width(32);
            oss_ << filename << ":";

            oss_.width(3);
            oss_ << line_no;

            set_inner(args...);
        }

        Logger(Logger const&)            = delete;
        Logger& operator=(Logger const&) = delete;

    private:
        void set_inner() { oss_ << std::endl; }

        template <typename HEAD, typename... TAIL>
        void set_inner(HEAD const& head, TAIL const&... tails)
        {
            using Nstd::operator<<;  // Nstd::operator<<もname lookupの対象にする

            oss_ << ":" << head;
            set_inner(tails...);
        }

        Logger() {}
        std::ostringstream oss_{};
    };
    }  // namespace Logging

    #define LOGGER_P(...) Logging::Logger::Inst().Set(__FILE__, __LINE__)
    #define LOGGER(...) Logging::Logger::Inst().Set(__FILE__, __LINE__, __VA_ARGS__)
```

問題のあったコードとの差分は、メンバ関数テンプレートset_innerの

```cpp
    //  example/template/logger.h 40

    using Nstd::operator<<;  // Nstd::operator<<もname lookupの対象にする
```

のみである。実際に解決できたことを以下の単体テストで示す。

```cpp
    //  example/template/logger_0_ints_ut.h 8

    auto ints = App::Ints_t{1, 2, 3};

    LOGGER("Ints", ints);
    auto line_num = __LINE__;

    auto s = Logging::Logger::InstConst().Get();

    auto exp = std::string{log_str_exp(__FILE__, line_num - 1, ":Ints:1, 2, 3\n")};
    ASSERT_EQ(exp, s);
```

また、

```cpp
    //  example/template/app_ints.h 12

    namespace App {

    class X {
    public:
        X(std::string str, int num) : str_{std::move(str)}, num_{num} {}
        std::string ToString() const { return str_ + "/" + std::to_string(num_); }
        // ...
    };
    }  // namespace App
```

のように定義されたクラスも、

```cpp
    //  example/template/app_ints.h 28

    namespace App {

    inline std::ostream& operator<<(std::ostream& os, X const& x) { return os << x.ToString(); }
    }  // namespace App
```

のような型専用のoperator<<があれば、そのオブジェクトのみではなく、
コンテナや配列に対しても下記のようにログ取得が可能となる。

```cpp
    //  example/template/logger_ut.cpp 37

    using namespace Nstd;

    auto         x  = App::X{"name", 3};
    auto         lx = std::list<App::X>{{"lx3", 3}, {"lx4", 1}};
    App::X const x3[3]{{"x0", 0}, {"x1", 1}, {"x2", 2}};

    LOGGER(1, x, x3, lx);
    auto line_num = __LINE__;

    auto s = Logging::Logger::InstConst().Get();

    auto const exp = log_str_exp(__FILE__, line_num - 1, ":1:name/3:x0/0, x1/1, x2/2:lx3/3, lx4/1\n");
    ASSERT_EQ(exp, s);
```

「[Nstdライブラリの開発](template_meta_programming.md#SS_13_2)」で示した依存関係も維持されており、
これでログ取得ライブラリは完成したと言って良いだろう。


## その他のテンプレートテクニック <a id="SS_13_7"></a>
ここでは、これまでの議論の対象にならなかったテンプレートのテクニックや注意点について記述する。

### forwardingリファレンスとstd::forward <a id="SS_13_7_1"></a>
2個の文字列からstd::vector\<std::string>を生成する下記のような関数について考える。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 9

    std::vector<std::string> gen_vector(std::string const& s0, std::string const& s1)
    {
        auto ret = std::vector<std::string>{};

        ret.push_back(s0);
        ret.push_back(s1);

        return ret;
    }
```

これは下記のように動作する。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 25

    auto a = std::string{"a"};
    auto b = std::string{"b"};

    auto v = gen_vector(a, std::move(b));

    ASSERT_EQ((std::vector<std::string>{"a", "b"}), v);
    ASSERT_EQ("a", a);
    ASSERT_EQ("b", b);  // bはmoveされない
```

このコードは正しく動作するものの、move代入できず、パフォーマンス問題を引き起こす可能性があるため、
[forwardingリファレンス](term_explanation.md#SS_19_15_3)を使って下記のように書き直した。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 41

    template <typename STR0, typename STR1>
    std::vector<std::string> gen_vector(STR0&& s0, STR1&& s1)
    {
        auto ret = std::vector<std::string>{};

        ret.push_back(s0);
        ret.push_back(s1);

        return ret;
    }
```

残念ながら、このコードは意図したようには動作せず、下記に示した通り相変わらずmove代入ができない。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 58

    auto a = std::string{"a"};
    auto b = std::string{"b"};

    auto v = gen_vector(a, std::move(b));

    ASSERT_EQ((std::vector<std::string>{"a", "b"}), v);
    ASSERT_EQ("a", a);
    ASSERT_EQ("b", b);  // bはmoveされない
```

この原因は、
「関数が受け取った[rvalue](term_explanation.md#SS_19_14_1_2)リファレンスは、
その関数から別の関数に受け渡される時に[lvalue](term_explanation.md#SS_19_14_1_1)リファレンスとして扱われる」からである。

この現象について下記の関数テンプレートを用いて解説を行う。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 71

    enum class ExpressionType { Lvalue, Rvalue };

    template <typename T>
    constexpr ExpressionType forwarding_ref2(T&& t)
    {
        return std::is_lvalue_reference_v<decltype(t)> ? ExpressionType::Lvalue : ExpressionType::Rvalue;
    }

    // std::pair<>::first  : forwarding_refの中のtのExpressionType
    // std::pair<>::second : forwarding_ref2の中でtのExpressionType
    template <typename T>
    constexpr std::pair<ExpressionType, ExpressionType> forwarding_ref(T&& t)
    {
        return std::make_pair(std::is_lvalue_reference_v<decltype(t)> ? ExpressionType::Lvalue : ExpressionType::Rvalue,
                              forwarding_ref2(t));
    }
```

下記に示した通り、forwarding_refとforwarding_ref2のパラメータが同じ型であるとは限らない。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 94

    auto i = 0;

    constexpr auto p = forwarding_ref(i);
    static_assert(forwarding_ref2(i) == ExpressionType::Lvalue);  // iはlvalue
    static_assert(p.first == ExpressionType::Lvalue);             // forwarding_refの引数はlvalue
    static_assert(p.second == ExpressionType::Lvalue);            // forwarding_ref中のforwarding_ref2の引数はlvalue

    constexpr auto pm = forwarding_ref(std::move(i));                        // forwarding_refの引数はrvalue
    static_assert(forwarding_ref2(std::move(i)) == ExpressionType::Rvalue);  // forwarding_ref2の引数はrvalue
    static_assert(pm.first == ExpressionType::Rvalue);                       // forwarding_refの引数はrvalue
    static_assert(pm.second == ExpressionType::Lvalue);                      // forwarding_ref中のforwarding_ref2の引数はrvalue

    constexpr auto pm2 = forwarding_ref(int{});
    static_assert(forwarding_ref2(int{}) == ExpressionType::Rvalue);  // forwarding_ref2の引数はrvalue
    static_assert(pm2.first == ExpressionType::Rvalue);               // forwarding_refの引数はrvalue
    static_assert(pm2.second == ExpressionType::Lvalue);              // forwarding_ref中のforwarding_ref2の引数はrvalue
```

この問題はstd::forwardにより対処できる。これによって改良されたコードを下記に示す。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 122

    template <typename STR0, typename STR1>
    std::vector<std::string> gen_vector(STR0&& s0, STR1&& s1)
    {
        auto ret = std::vector<std::string>{};

        ret.push_back(std::forward<STR0>(s0));
        ret.push_back(std::forward<STR1>(s1));

        return ret;
    }
```

下記単体テストが示す通り、rvalueリファレンスはmove代入され、lvalueリファレンスはcopy代入されている。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 140

    auto a = std::string{"a"};
    auto b = std::string{"b"};

    auto v = gen_vector(a, std::move(b));

    ASSERT_EQ((std::vector<std::string>{"a", "b"}), v);
    ASSERT_EQ("a", a);
    ASSERT_EQ("", b);  // bはmoveされた
```

しかし残念ながら、このコードにも改良すべき点がある。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 153

    auto a = std::string{"a"};

    auto v = gen_vector(a, "b");

    ASSERT_EQ((std::vector<std::string>{"a", "b"}), v);
    ASSERT_EQ("a", a);
```

上記の"b"のような文字列リテラルを引数にした場合、
それをstd::vector\<std::string>::push_backに渡した時に、
"b"はテンポラリオブジェクトstd::string("b")のに変換されてしまう。
std::vector\<std::string>へのオブジェクトの挿入は、文字列リテラルから行うことが出来るため、
このテンポラリオブジェクトの生成は明らかに不要な処理である。

下記は、この対策を施すとともに任意の数の引数を受け取れるように改良したコードである。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 169

    void emplace_back(std::vector<std::string>&) {}

    template <typename HEAD, typename... TAIL>
    void emplace_back(std::vector<std::string>& strs, HEAD&& head, TAIL&&... tails)
    {
        strs.emplace_back(std::forward<HEAD>(head));

        if constexpr (sizeof...(tails) != 0) {
            emplace_back(strs, std::forward<TAIL>(tails)...);
        }
    }

    template <typename... STR>
    std::vector<std::string> gen_vector(STR&&... ss)
    {
        auto ret = std::vector<std::string>{};

        emplace_back(ret, std::forward<STR>(ss)...);

        return ret;
    }
```

上記の

```cpp
    sizeof...(tails)
```

はパラメータパックの個数を受け取るための記法である。
従ってこのコードではすべてのパラメータパック変数を消費するまでリカーシブコールを続けることになる
(が、このリカーシブコールはコンパイル時に行われるため、実行時の速度低下は起こさない)。

上記の

```cpp
    std::forward<TAIL>(tails)...
```

は、それぞれのパラメータパック変数をstd::forwardに渡した戻り値を、
再びパラメータパックにするための記法である。

このコードは下記の単体テストが示すように正しく動作する
(が、残念ならがテンポラリオブジェクトが生成されていないことを単体テストで証明することはできない)。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 195

    auto a = std::string{"a"};
    auto b = std::string{"b"};

    auto v = gen_vector(a, std::move(b), "c");

    ASSERT_EQ((std::vector<std::string>{"a", "b", "c"}), v);
    ASSERT_EQ("a", a);
    ASSERT_EQ("", b);  // bはmoveされた
```

上記のgen_vectorはリカーシブコールを使って実装したが、
[畳み込み式](term_explanation.md#SS_19_11_3)を使用した下記の実装の方がより明確である。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 209

    template <typename... STR>
    std::vector<std::string> gen_vector(STR&&... ss)
    {
        auto ret = std::vector<std::string>{};

        (ret.emplace_back(std::forward<STR>(ss)), ...);

        return ret;
    }
```

forwardingリファレンスはconstにすることができないが
(T const&&はconstな[rvalue](term_explanation.md#SS_19_14_1_2)リファレンスである)、
forwardingリファレンスが[lvalue](term_explanation.md#SS_19_14_1_1)リファレンスであった場合は、
constなlvalueリファレンスとして扱うべきである。

従って、下記のようなコードは書くべきではない。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 238

    template <typename STR0, typename STR1>
    std::vector<std::string> gen_vector(STR0&& s0, STR1&& s1)
    {
        auto ret = std::vector<std::string>{};

        ret.push_back(std::move(s0));
        ret.push_back(std::move(s1));

        return ret;
    }
```

もしそのようにしてしまえば、
下記単体テストが示すように非constな実引数はmoveされてしまうことになる。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 255

    auto       a = std::string{"a"};
    auto const b = std::string{"b"};

    auto v = gen_vector(a, std::move(b));

    ASSERT_EQ((std::vector<std::string>{"a", "b"}), v);
    ASSERT_EQ("", a);   // aはmoveされてしまう
    ASSERT_EQ("b", b);  // bはconstなのでmoveされない
```

任意の型Tのrvalueのみを引数に取る関数テンプレートを下記のように記述した場合、
すでに述べたように引数はforwardingリファレンスとなってしまうため、lvalueにもバインドしてしまう。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 271

    template <typename T>
    void f(T&& t) noexcept
    {
        // ...
    }
```

このような場合、下記の記述が必要になる。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 290

    template <typename T>
    void f(T&) = delete;
```

この効果により、下記に示した通りlvalueにはバインドできなくなり、
当初の目的通り、rvalueのみを引数に取る関数テンプレートが定義できたことになる。

```cpp
    //  example/template_cpp17/universal_ref_ut.cpp 298

    auto s = std::string{};

    // f(s);           // f(std::string&)はdeleteされたため、コンパイルエラー
    f(std::string{});  // f(std::string&&)にはバインドできる
```

なお、forwardingリファレンスは、[リファレンスcollapsing](term_explanation.md#SS_19_15_6)の一機能としても理解できる。

### ジェネリックラムダによる関数内での関数テンプレートの定義 <a id="SS_13_7_2"></a>
下記のようなクラスとoperator<<があった場合を考える。

```cpp
    //  example/template_cpp17/generic_lambda_ut.cpp 13

    struct XYZ {
        XYZ(int ax, int ay, int az) noexcept : x{ax}, y{ay}, z{az} {}
        int x;
        int y;
        int z;
    };

    std::ostream& operator<<(std::ostream& os, XYZ const& xyz)
    {
        return os << std::to_string(xyz.x) + "/" + std::to_string(xyz.y) + "/" + std::to_string(xyz.z);
    }
```

「[Nstd::SafeIndexの開発](template_meta_programming.md#SS_13_4_2)」や「[コンテナ用Nstd::operator\<\<の開発](template_meta_programming.md#SS_13_4_4)」
の成果物との組み合わせの単体テストは下記のように書けるだろう。

```cpp
    //  example/template_cpp17/generic_lambda_ut.cpp 31

    auto v   = Nstd::SafeVector<XYZ>{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}, {0, 1, 2}};
    auto oss = std::ostringstream{};

    oss << v;
    ASSERT_EQ("9/8/7, 6/5/4, 3/2/1, 0/1/2", oss.str());
```

std::sortによるソートができるかどうかのテストは、C++11までは、

```cpp
    //  example/template_cpp17/generic_lambda_ut.cpp 41

    auto v = Nstd::SafeVector<XYZ>{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}, {0, 1, 2}};

    // C++11 lambda                  型の明示が必要
    //                               ↓               ↓
    std::sort(v.begin(), v.end(), [](XYZ const& lhs, XYZ const& rhs) noexcept {
        return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
    });
    auto oss = std::ostringstream{};

    oss << v;
    ASSERT_EQ("0/1/2, 3/2/1, 6/5/4, 9/8/7", oss.str());
```

のように書くのが一般的だろう。ラムダ式の引数の型を指定しなければならないのは、
範囲for文でautoが使用出来ること等と比べると見劣りがするが、
C++14からは下記のコードで示した通り引数にautoが使えるようになった。

```cpp
    //  example/template_cpp17/generic_lambda_ut.cpp 57

    auto v = Nstd::SafeVector<XYZ>{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}, {0, 1, 2}};

    // C++14 generic lambda          型の明示が不要
    //                               ↓                ↓
    std::sort(v.begin(), v.end(), [](auto const& lhs, auto const& rhs) noexcept {
        return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
    });
    auto oss = std::ostringstream{};

    oss << v;
    ASSERT_EQ("0/1/2, 3/2/1, 6/5/4, 9/8/7", oss.str());
```

この記法は[ジェネリックラムダ](term_explanation.md#SS_19_11_4)と呼ばれる。
この機能により関数の中で関数テンプレートと同等のものが定義できるようになった。

#### ジェネリックラムダの内部構造 <a id="SS_13_7_2_1"></a>
ジェネリックラムダは下記のように使用することができる。

```cpp
    //  example/template_cpp17/generic_lambda_ut.cpp 73

    template <typename PUTTO>
    void f(PUTTO&& p)
    {
        p(1);       // ラムダの引数elemの型はint
        p(2.71);    // ラムダの引数elemは型はdouble
        p("hehe");  // ラムダの引数elemは型はchar [5]
    }

    TEST(Template, generic_lambda)
    {
        auto oss = std::ostringstream{};

        f([&oss](auto const& elem) { oss << elem << std::endl; });

        ASSERT_EQ("1\n2.71\nhehe\n", oss.str());
    }
```

この例で使用しているクロージャは一見、型をダイナミックに扱っているように見えるが、
下記のような「テンプレートoperator()を持つ関数型」オブジェクトとして展開されていると考えれば、
理解できる。

```cpp
    //  example/template_cpp17/generic_lambda_ut.cpp 92

    class Closure {
    public:
        Closure(std::ostream& os) : os_{os} {}

        template <typename T>
        void operator()(T&& t)
        {
            os_ << t << std::endl;
        }

    private:
        std::ostream& os_;
    };
```
```cpp
    //  example/template_cpp17/generic_lambda_ut.cpp 111

    auto oss = std::ostringstream{};

    auto closure = Closure{oss};
    f(closure);

    ASSERT_EQ("1\n2.71\nhehe\n", oss.str());
```

#### std::variantとジェネリックラムダ <a id="SS_13_7_2_2"></a>
unionは、オブジェクトを全く無関係な複数の型に切り替えることができるため、
これが必要な場面では有用な機能であるが、未定義動作を誘発してしまう問題がある。
この対策としてC++17で導入されたものが、std::variantである。

まずは、std::variantの使用例を下記する。

```cpp
    //  example/template_cpp17/variant_ut.cpp 13

    auto v = std::variant<int, std::string, double>{};  // 3つの型を切り替える

    // std::get<N>()の戻り値型は、下記の通りで、
    // N == 0, 1, 2 は、それぞれint, std::string, doubleに対応
    static_assert(std::is_same_v<decltype(std::get<0>(v)), int&>);
    static_assert(std::is_same_v<decltype(std::get<1>(v)), std::string&>);
    static_assert(std::is_same_v<decltype(std::get<2>(v)), double&>);

    v = int{3};  // int型の3を代入

    ASSERT_EQ(v.index(), 0);                                // intを保持
    ASSERT_EQ(std::get<0>(v), 3);                           // intなので問題なくアクセス
    ASSERT_THROW(std::get<1>(v), std::bad_variant_access);  // std::stringではないのでエクセプション
    ASSERT_THROW(std::get<2>(v), std::bad_variant_access);  // doubleではないのでエクセプション

    v = std::string{"str"};  // std::stringオブジェクトを代入

    ASSERT_EQ(v.index(), 1);                                // std::stringを保持
    ASSERT_THROW(std::get<0>(v), std::bad_variant_access);  // intではないのでエクセプション
    ASSERT_EQ(std::get<1>(v), std::string{"str"});          // std::stringなので問題なくアクセス
    ASSERT_THROW(std::get<2>(v), std::bad_variant_access);  // doubleではないのでエクセプション
```

上記からわかる通り、std::variantオブジェクトは、直前に代入されたオブジェクトの型以外で、
値を読み出した場合、問題なく読み出せるが、それ以外ではエクセプションを発生させる。

このstd::variantオブジェクトの保持する型とその値を文字列として取り出すラムダ式は、
下記のように書ける。

```cpp
    //  example/template_cpp17/variant_ut.cpp 37

    auto oss = std::ostringstream{};

    // type_valueはvが保持する型をその値を文字列で返す
    auto type_value = [&oss](auto const& v) {  // ジェネリックラムダでなくても実装可能
        if (v.index() == 0) {
            auto a  = std::get<0>(v);
            using T = std::remove_const_t<std::remove_reference_t<decltype(a)>>;
            oss << Nstd::Type2Str<T>() << " : " << a;  // Nstd::Type2Str<T>はTの型を文字列にする
        }
        else if (v.index() == 1) {
            auto a  = std::get<1>(v);
            using T = std::remove_const_t<std::remove_reference_t<decltype(a)>>;
            oss << Nstd::Type2Str<T>() << " : " << a;  // Nstd::Type2Str<T>はTの型を文字列にする
        }
        else if (v.index() == 2) {
            auto a  = std::get<2>(v);
            using T = std::remove_const_t<std::remove_reference_t<decltype(a)>>;
            oss << Nstd::Type2Str<T>() << " : " << a;  // Nstd::Type2Str<T>はTの型を文字列にする
        }
        else {
            assert(false);  // ここには来ないはず
        }
    };

    v = 3;  // int型の3を代入
    type_value(v);
    ASSERT_EQ("int : 3", oss.str());
    oss = std::ostringstream{};  // ossのリセット

    v = std::string{"str"};  // std::stringオブジェクトを代入
    type_value(v);
    ASSERT_EQ("std::string : str", oss.str());
    oss = std::ostringstream{};  // ossのリセット

    v = 1.1;  // double型の1.1を代入
    type_value(v);
    ASSERT_EQ("double : 1.1", oss.str());
```

このラムダは、
3つの型をテンプレートパラメータとするstd::variantオブジェクト以外には適用できないため、
型の個数に制限のない方法を考える。

この実装は、

* 保持する型が何番目かを見つけるための関数テンプレート
* 関数テンプレートの引数となるジェネリックラムダ

の2つによって下記のように行うことができる。

```cpp
    //  example/template_cpp17/variant_ut.cpp 79

    template <typename VARIANT, typename F, size_t INDEX = 0>
    void org_visit(const F& f, const VARIANT& v)
    {
        constexpr auto n = std::variant_size_v<VARIANT>;

        if constexpr (INDEX < n) {
            if (v.index() == INDEX) {  // 保持する型が見つかった
                f(std::get<INDEX>(v));
                return;
            }
            else {  // 保持する型が見つかるまでリカーシブ
                org_visit<VARIANT, F, INDEX + 1>(f, v);
            }
        }
        else {
            assert(false);  // ここには来ないはず
        }
    }
```
```cpp
    //  example/template_cpp17/variant_ut.cpp 103

    auto oss = std::ostringstream{};

    // 文字列を返すためのジェネリックラムダ
    auto type_value = [&oss](auto const& a) {
        using T = std::remove_const_t<std::remove_reference_t<decltype(a)>>;
        oss << Nstd::Type2Str<T>() << " : " << a;
    };
```

単体テストは、以下のようになる。

```cpp
    //  example/template_cpp17/variant_ut.cpp 113
    {
        auto v = std::variant<int, std::string, double>{};  // 3つの型を切り替える

        v = 3;
        org_visit(type_value, v);
        ASSERT_EQ("int : 3", oss.str());
        oss = std::ostringstream{};  // ossのリセット

        // ...
    }
    {
        auto v = std::variant<char, int, std::string, double>{};  // 4つの型を切り替える

        v = 3;
        org_visit(type_value, v);
        ASSERT_EQ("int : 3", oss.str());
        oss = std::ostringstream{};  // ossのリセット

        v = 'c';
        org_visit(type_value, v);
        ASSERT_EQ("char : c", oss.str());
        oss = std::ostringstream{};  // ossのリセット

        // ...
    }
```

下記のように継承関係のない複数のクラスが同じシグネチャのメンバ関数を持つ場合、

```cpp
    //  example/template_cpp17/variant_ut.cpp 177

    class A {
    public:
        char f() const noexcept { return 'A'; }
    };

    class B {
    public:
        char f() const noexcept { return 'B'; }
    };

    class C {
    public:
        char f() const noexcept { return 'C'; }
    };
```

std::variant、上に示した関数テンプレート、ジェネリックラムダを使い、
下記に示したような疑似的なポリモーフィズムを実現できる。

```cpp
    //  example/template_cpp17/variant_ut.cpp 197

    char ret{};
    auto call_f = [&ret](auto const& a) { ret = a.f(); };

    auto v = std::variant<A, B, C>{};

    org_visit(call_f, v);  // 疑似的なポリモーフィズム
    ASSERT_EQ('A', ret);

    v = B{};
    org_visit(call_f, v);  // 疑似的なポリモーフィズム
    ASSERT_EQ('B', ret);

    v = C{};
    org_visit(call_f, v);  // 疑似的なポリモーフィズム
    ASSERT_EQ('C', ret);
```

ここで示した関数テンプレートは、デザインパターン[Visitor](design_pattern.md#SS_9_21)の例であり、
ほぼこれと同様のものがstd::visitとして定義されている。

```cpp
    //  example/template_cpp17/variant_ut.cpp 215

    v = A{};
    std::visit(call_f, v);  // 疑似的なポリモーフィズム
    ASSERT_EQ('A', ret);

    v = B{};
    std::visit(call_f, v);  // 疑似的なポリモーフィズム
    ASSERT_EQ('B', ret);

    v = C{};
    std::visit(call_f, v);  // 疑似的なポリモーフィズム
    ASSERT_EQ('C', ret);
```

### クラステンプレートと継承の再帰構造 <a id="SS_13_7_3"></a>
クラステンプレートと継承の再帰構造はCRTPと呼ばれる。
このコードパターンについては、
「[CRTP(curiously recurring template pattern)](design_pattern.md#SS_9_22)」で説明している。


### 意図しないname lookupの防止 <a id="SS_13_7_4"></a>
下記のようにクラスや関数テンプレートが定義されている場合を考える。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 11

    namespace App {

    struct XY {
        int x;
        int y;
    };

    // このような関数テンプレートは適用範囲が広すぎるので定義すべきではないが、
    // 危険な例を示すためあえて定義している
    template <typename T, typename U>
    inline auto is_equal(T const& lhs, U const& rhs) noexcept -> decltype(lhs.x == rhs.x, lhs.y == rhs.y)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    }  // namespace App
```

これに対しての単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 36

    auto xy0 = App::XY{0, 1};
    auto xy1 = App::XY{0, 2};
    auto xy2 = App::XY{0, 1};

    ASSERT_FALSE(is_equal(xy0, xy1));
    ASSERT_TRUE(is_equal(xy0, xy2));

    struct point {
        int x;
        int y;
    };
    auto p0 = point{0, 1};

    // 下記のような比較ができるようにするためis_equalはテンプレートで実装している
    ASSERT_TRUE(is_equal(p0, xy0));
    ASSERT_FALSE(is_equal(p0, xy1));
```

上記の抜粋である

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 42

    ASSERT_FALSE(is_equal(xy0, xy1));
    ASSERT_TRUE(is_equal(xy0, xy2));
```

が名前空間Appの指定なしでコンパイルできる理由は、
[ADL](term_explanation.md#SS_19_10_5)(実引数依存探索)により、Appもis_equalの[name lookup](term_explanation.md#SS_19_10_2)の対象になるからである。
これは便利な機能であるが、その副作用として意図しないname
lookupによるバグの混入を起こしてしまうことがある。

上記の名前空間での定義が可視である状態で、下記のようなコードを書いた場合を考える。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 62

    namespace App2 {
    struct XYZ {
        int x;
        int y;
        int z;
    };

    inline bool is_equal(XYZ const& lhs, XYZ const& rhs) noexcept
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }
    }  // namespace App2
```

この単体テストは、やはりADLを使い下記のように書ける。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 83
    auto xyz0 = App2::XYZ{0, 2, 2};
    auto xyz1 = App2::XYZ{0, 1, 2};

    ASSERT_TRUE(is_equal(xyz0, xyz0));
    ASSERT_FALSE(is_equal(xyz0, xyz1));
```

これに問題はないが、下記のテストもコンパイルでき、且つテストもパスしてしまうことには問題がある。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 92

    auto xyz0 = App2::XYZ{0, 2, 2};
    auto xyz1 = App2::XYZ{0, 1, 2};
    auto xy0  = App::XY{0, 1};

    ASSERT_FALSE(is_equal(xy0, xyz0));  // これがコンパイルできてしまう
    ASSERT_TRUE(is_equal(xy0, xyz1));   // このis_equalはAppで定義されたもの
```

このセマンティクス的に無意味な(もしくは混乱を引き起こしてしまうであろう)コードは、

* is_equalの引数の型XY、XYZはそれぞれ名前空間App、App2で定義されている
* 従って、ADLによりis_equalのname lookupには名前空間App、App2も使われる
* 引数の型XY、XYZを取り得るis_equalはAppで定義されたもののみである

というメカニズムによりコンパイルできてしまう。

こういったname lookup、特にADLの問題に対処する方法は、

* [ジェネリックすぎるテンプレートを書かない](template_meta_programming.md#SS_13_7_4_1)
* [ADLが本当に必要でない限り名前を修飾する](template_meta_programming.md#SS_13_7_4_2)
* [ADL Firewallを使う](template_meta_programming.md#SS_13_7_4_3)

のようにいくつか考えられる。これらについて以下で説明を行う。

#### ジェネリックすぎるテンプレートを書かない <a id="SS_13_7_4_1"></a>
ここでの「ジェネリックすぎるテンプレート」とは、
シンタックス的には適用範囲が広いにもかかわらず、セマンティクス的な適用範囲は限られているものを指す。
従って下記のような関数テンプレートを指す概念ではない。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 107

    template <typename T, size_t N>
    constexpr auto array_length(T const (&)[N]) noexcept
    {
        return N;
    }
```

前記で問題を起こした関数テンプレート

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 20

    // このような関数テンプレートは適用範囲が広すぎるので定義すべきではないが、
    // 危険な例を示すためあえて定義している
    template <typename T, typename U>
    inline auto is_equal(T const& lhs, U const& rhs) noexcept -> decltype(lhs.x == rhs.x, lhs.y == rhs.y)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
    }  // namespace App
```

が典型的な「ジェネリックすぎるテンプレート」である。
これに対する最も安全な対処は下記コードで示す通りテンプレートを使わないことである。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 125

    namespace App {

    struct XY {
        int x;
        int y;
    };

    inline bool is_equal(XY const& lhs, XY const& rhs) noexcept { return lhs.x == rhs.x && lhs.y == rhs.y; }
    }  // namespace App
```

ジェネリックなis_equalが必要であれば下記単体テストのように
[ジェネリックラムダによる関数内での関数テンプレートの定義](template_meta_programming.md#SS_13_7_2)を行えばよい。
こうすることでその適用範囲はそれを定義した関数内に留まる。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 149

    // 下記のpointのようなクラスが他にもいくつかあった場合、
    // このジェネリックラムダでコードの被りは回避できる
    auto is_equal = [](auto const& lhs, auto const& rhs) noexcept { return lhs.x == rhs.x && lhs.y == rhs.y; };

    struct point {
        int x;
        int y;
    };
    auto p0 = point{0, 1};

    ASSERT_TRUE(is_equal(p0, xy0));
    ASSERT_FALSE(is_equal(p0, xy1));
```

上記で示した

* テンプレートを使わない
* 適用範囲の広いテンプレート(ジェネリック)に対してはアクセスできる箇所を局所化する

といった方法の他にも、「[コンテナ用Nstd::operator\<\<の開発](template_meta_programming.md#SS_13_4_4)」で示した

* [std::enable_if](template_meta_programming.md#SS_13_3_1_4)や[コンセプト](term_explanation.md#SS_19_11_2)等を使用してテンプレートに適用できる型を制約する

ことも考えられる。
ベストな方法は状況に大きく依存するため一概には決められない。
その状況でのもっとも単純は方法を選ぶべきだろう(が、何が単純かも一概に決めることは難しい)。


#### ADLが本当に必要でない限り名前を修飾する <a id="SS_13_7_4_2"></a>
下記のコードについて考える。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 170

    struct A {
        int f(int i) noexcept { return i * 3; }
    };

    int f(int i) noexcept { return i * 2; }

    namespace App {

    template <typename T>
    class ExecF : public T {
    public:
        int operator()(int i) noexcept
        {
            return f(i);  // T::fの呼び出しにも見えるが、::fの呼び出し
        }

        // Tを使ったコード
        // ...
    };
    }  // namespace App
```

基底クラスのメンバ関数を呼び出す場合は、T::f()、もしくは、this->f()と書く必要があるため、
下記コードで呼び出した関数fは外部関数fの呼び出しになる
([two phase name lookup](term_explanation.md#SS_19_10_3)の一回目のname lookupでfがバインドされるため)。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 197

    auto ef = App::ExecF<A>{};

    ASSERT_EQ(4, ef(2));  // ::fの呼び出しなので、2 * 2 == 4となる
```

これだけでも十分わかりづらいが、
ExecFのテンプレートパラメータにはクラスAしか使われないことがわかったので、
下記のようにリファクタリングしたとしよう。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 207

    struct A {
        int f(int i) noexcept { return i * 3; }
    };

    int f(int i) noexcept { return i * 2; }

    namespace App {

    class ExecF : public A {
    public:
        int operator()(int i) noexcept { return f(i); }

        // Tを使ったコード
        // ...
    };
    }  // namespace App
```

すると、fのname lookupの対象が変わってしまい、元の単体テストはパスしなくなる。

```cpp
    //  example/template_cpp17/suppress_adl_ut.cpp 230

    auto ef = App::ExecF{};

    // ASSERT_EQ(4, ef(2));
    ASSERT_EQ(6, ef(2));  // リファクタリングでname lookupの対象が変わり、A::fが呼ばれる
```

こういった場合に備え単体テストを実行すべきなのだが、この程度の問題はコンパイルで検出したい。
[ADL](term_explanation.md#SS_19_10_5)や[two phase name lookup](term_explanation.md#SS_19_10_3)が絡む場合ならなおさらである。

こういう意図しない[name lookup](term_explanation.md#SS_19_10_2)に備えるためには、
修飾されていない識別子を使わないこと、つまり、
識別子には、名前空間、クラス名、this->等による修飾を施すことが重要である。

ただし、「[コンテナ用Nstd::operator\<\<の開発](template_meta_programming.md#SS_13_4_4)」で示したコード等にはADLが欠かせないため、
修飾することをルール化することはできない。場合に合わせた運用が唯一の解となる。


#### ADL Firewallを使う <a id="SS_13_7_4_3"></a>
下記のコードについて考える。

```cpp
    //  example/template_cpp17/adl_firewall_0_ut.cpp 10

    namespace App {

    template <typename T>
    std::string ToString(std::vector<T> const& t)
    {
        auto oss = std::ostringstream{};

        using Nstd::operator<<;
        oss << t;  // Nstd::operator<<もname lookupの対象に含める

        return oss.str();
    }
    }  // namespace App

    // ...

    namespace App {
    struct XY {
        XY(int ax, int ay) noexcept : x{ax}, y{ay} {}
        int x;
        int y;
    };

    std::ostream& operator<<(std::ostream& os, XY const& xyz)
    {
        return os << std::to_string(xyz.x) + "/" + std::to_string(xyz.y);
    }
    }  // namespace App
```

上記のApp::ToStringは「[コンテナ用Nstd::operator\<\<の開発](template_meta_programming.md#SS_13_4_4)」のコードを使用し、
std::vectorオブジェクトをstd::stringに変換する。

これに対しての単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/adl_firewall_0_ut.cpp 47

    auto xys = std::vector<App::XY>{{9, 8}, {7, 6}};

    ASSERT_EQ("9/8, 7/6", App::ToString(xys));
```

これは想定通りの動作だが、上記のAppの後に下記のコードを追加するとApp::ToStringは影響を受ける。

```cpp
    //  example/template_cpp17/adl_firewall_1_ut.cpp 40

    // Appに下記を追加
    namespace App {
    template <typename T>
    std::ostream& operator<<(std::ostream& os, std::vector<T> const& t)
    {
        return os << "size:" << t.size();
    }
    }  // namespace App
```

これにより元の単体テストはエラーとなり、新しい単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/adl_firewall_1_ut.cpp 56

    auto xys = std::vector<App::XY>{{9, 8}, {7, 6}};

    // App::operator<<の追加で、App::ToStringの出力が影響を受ける
    // ASSERT_EQ("9/8, 7/6", App::ToString(xys));
    ASSERT_EQ("size:2", App::ToString(xys));
```

これが意図通りなら問題ないが、
ここでは「新たに追加した関数テンプレートApp::operator<<はstd::vector\<App::XY>用ではなかった」
としよう。その場合、これは意図しないADLによるバグの混入となる。
「[ジェネリックすぎるテンプレートを書かない](template_meta_programming.md#SS_13_7_4_1)」
で述べたように追加した関数テンプレートの適用範囲が広すぎることが原因であるが、
XY型から生成されたオブジェクト(std::vector\<App::XY>も含む)によるADLのため、
Appの宣言がname lookupの対象になったことにも原因がある。

下記のコードは後者の原因を解消する。

```cpp
    //  example/template_cpp17/adl_firewall_2_ut.cpp 23

    // Appの中の新たな名前空間XY_Firewall_でstruct XYとoperator<<を宣言
    namespace App {
    namespace XY_Firewall_ {

    struct XY {
        XY(int ax, int ay) noexcept : x{ax}, y{ay} {}
        int x;
        int y;
    };

    std::ostream& operator<<(std::ostream& os, XY const& xyz)
    {
        return os << std::to_string(xyz.x) + "/" + std::to_string(xyz.y);
    }
    }  // namespace XY_Firewall_

    using XY = XY_Firewall_::XY;

    }  // namespace App
```

XY型オブジェクトを引数にした関数呼び出しによる[関連名前空間](term_explanation.md#SS_19_10_6)は、
極小なApp::XY_Firewall\_であるため、意図しないADLは起こりづらく、起こっても発見しやすい。
また、XY型用operator<<もApp::XY_Firewall\_で定義し、
App内でusing XYを宣言したことで、これまで通りApp::XYが使える。

このようなテクニックをADL firewallと呼ぶ。


### Nstd::Type2Strの開発 <a id="SS_13_7_5"></a>
「[Nstdライブラリの開発](template_meta_programming.md#SS_13_2)」等で行ったメタ関数の実装は、

* 入り組んだ<>や()の対応漏れ
* &や&&のつけ忘れ
* typenameやtemplateキーワードの漏れ
* メタ関数メンバー::valueや::typeの漏れ

等によるコンパイルエラーとの戦いである。
また、これをクリアしても[two phase name lookup](term_explanation.md#SS_19_10_3)や[ADL](term_explanation.md#SS_19_10_5)が次の関門になる。
これには、デバッガのステップ実行が強力な武器となるが、
型を文字列に変換する関数があればこれもまた強力な武器となる。

以下に示すNstd::Type2Strは、「[Nstdライブラリの開発](template_meta_programming.md#SS_13_2)」等で実際に使用したそのような関数である。

```cpp
    //  h/nstd_type2str.h 9

    namespace Nstd {
    namespace Inner_ {

    inline std::string demangle(char const* to_demagle)
    {
        int status;

        auto demangled
            = std::unique_ptr<char, decltype(&std::free)>{abi::__cxa_demangle(to_demagle, 0, 0, &status), &std::free};

        return demangled.get();
    }

    template <typename>  // typenameを取り出すためだけのクラステンプレート
    struct type_capture {
    };
    }  // namespace Inner_

    template <typename T>
    std::string Type2Str()
    {
        // typeid(T)とした場合、const/volatile/&の情報が捨てられるため、
        // typeid(type_capture<T>)とし、それを防ぐ。
        auto str = std::string{Inner_::demangle(typeid(Inner_::type_capture<T>).name())};

        // T   == const int ならば、
        // str == Nstd::Inner_::type_capture<int const>
        //        <----------- 27 ----------><-- x --> 下記ではxを切り出す
        constexpr auto beg  = 27U;                                    // 先頭の不要な文字列数
        auto           name = str.substr(beg, str.size() - beg - 1);  // 最後の文字は>なので不要

        while (name.back() == ' ') {  // 無駄なスペースを消す
            auto last = --name.end();
            name.erase(last);
        }

        return name;
    }
    }  // namespace Nstd
```

typeid::name()が返す文字列リテラルは引数の型の文字列表現を持つが、
マングリングされているためヒューマンリーダブルではない。
それをデマングルするのがabi::\_\_cxa\_demangleであるが、
残念なことにこの関数は非標準であるため、
それを使っているNstd::Inner\_::demangleは[g++](term_explanation.md#SS_19_20_1)/[clang++](term_explanation.md#SS_19_20_2)
でなければコンパイルできないだろう。

それを除けば、
複雑なシンタックスを持つ型を文字列で表現できるNstd::Type2Strは、
テンプレートプログラミングおける有効なデバッグツールであると言える。

下記単体テストは、そのことを示している。

```cpp
    //  example/template/nstd_type2str_ut.cpp 11

    ASSERT_EQ("int const", Nstd::Type2Str<int const>());
    ASSERT_EQ("std::string", Nstd::Type2Str<std::string>());
    ASSERT_EQ("std::vector<int, std::allocator<int> >", Nstd::Type2Str<std::vector<int>>());

    extern void f(int);
    ASSERT_EQ("void (int)", Nstd::Type2Str<decltype(f)>());  // 関数の型

    auto lamda = []() noexcept {};
    ASSERT_NE("", Nstd::Type2Str<decltype(lamda)>());  // XXX::{lambda()#1}な感じになる

    ASSERT_EQ("std::ostream& (std::ostream&, int const (&) [3])",
              Nstd::Type2Str<decltype(Nstd::operator<< <int[3]>)>());

    // std::declvalはrvalueリファレンスを返す
    ASSERT_EQ("int (&&) [3]", Nstd::Type2Str<decltype(std::declval<int[3]>())>());

    int i3[3];
    ASSERT_EQ("int [3]", Nstd::Type2Str<decltype(i3)>());
    ASSERT_EQ("int (&) [3]", Nstd::Type2Str<decltype((i3))>());  // (i3)はlvalueリファレンス

    auto& r = i3;
    ASSERT_EQ("int (&) [3]", Nstd::Type2Str<decltype(r)>());
```

### 静的な文字列オブジェクト <a id="SS_13_7_6"></a>
std::stringは文字列を扱うことにおいて、非常に有益なクラスではあるが、
コンパイル時に文字列が決定できる場合でも、動的にメモリを確保する。

この振る舞いは、

* ランタイム時にnew/deleteを行うため、処理の遅さにつながる。
* 下記のようにエクセプションオブジェクトにファイル位置を埋め込むことは、
  デバッグに便利であるが、メモリ確保失敗を通知するような場面ではこの方法は使えない。

```cpp
    //  example/template_cpp17/nstd_exception_ut.cpp 6

    class Exception : std::exception {
    public:
        Exception(char const* filename, uint32_t line_num, char const* msg)
            : what_str_{std::string{filename} + ":" + std::to_string(line_num) + ":" + msg}
        {
        }

        char const* what() const noexcept override { return what_str_.c_str(); }

    private:
        std::string what_str_;
    };

    int32_t div(int32_t a, int32_t b)
    {
        if (b == 0) {
            throw Exception{__FILE__, __LINE__, "divided by 0"};  // 24行目
        }

        return a / b;
    }
```
```cpp
    //  example/template_cpp17/nstd_exception_ut.cpp 34

    auto caught = false;
    try {
        div(1, 0);
    }
    catch (Exception const& e) {
        ASSERT_STREQ("nstd_exception_ut.cpp:24:divided by 0", e.what());
        caught = true;
    }
    ASSERT_TRUE(caught);
```

このような問題を回避するために、ここでは静的に文字列を扱うためのクラスStaticStringを開発する。

#### StaticStringのヘルパークラスの開発 <a id="SS_13_7_6_1"></a>
StaticStringオブジェクトは、char配列をメンバとして持つが、
コンパイル時に解決できる配列の初期化にはパラメータパックが利用できる。
そのパラメータパック生成クラスを下記のように定義する。

```cpp
    //  example/template_cpp17/nstd_seq.h 4

    // パラメータパック展開ヘルパクラス
    template <size_t... Ns>
    struct index_sequence {
    };

    // index_sequence<0, 1, 2, ...>を作るためのクラステンプレート
    // make_index_sequence<3>
    // -> make_index_sequence<2, 2>
    // -> make_index_sequence<1, 1, 2>
    // -> make_index_sequence<0, 0, 1, 2>
    // -> index_sequence<0, 1, 2>
    template <size_t N, size_t... Ns>
    struct make_index_sequence : make_index_sequence<N - 1, N - 1, Ns...> {
    };

    template <size_t... Ns>
    struct make_index_sequence<0, Ns...> : index_sequence<Ns...> {
    };

```

このクラスにより、下記のような配列メンバの初期ができるようになる。

```cpp
    //  example/template_cpp17/nstd_seq_ut.cpp 7

    template <size_t N>
    struct seq_test {
        template <size_t... S>
        constexpr seq_test(index_sequence<S...>) noexcept : data{S...}
        {
        }
        int const data[N];
    };
```
```cpp
    //  example/template_cpp17/nstd_seq_ut.cpp 24

    constexpr auto st = seq_test<3>{index_sequence<1, 2, 3>()};
    ASSERT_EQ(1, st.data[0]);
    ASSERT_EQ(2, st.data[1]);
    ASSERT_EQ(3, st.data[2]);
```

これを下記のように使うことで、メンバである文字列配列のコンパイル時初期化ができるようになる。

```cpp
    //  example/template_cpp17/nstd_seq_ut.cpp 33

    template <size_t N>
    class seq_test2 {
    public:
        template <size_t... S>
        constexpr seq_test2(char const (&str)[N], index_sequence<S...>) noexcept : string_{str[S]...}
        {
        }

        constexpr char const (&String() const noexcept)[N] { return string_; }

    private:
        char const string_[N];
    };
```
```cpp
    //  example/template_cpp17/nstd_seq_ut.cpp 52

    constexpr char const str[]{"123"};

    constexpr auto st = seq_test2<4>{str, index_sequence<0, 1, 2>()};
    ASSERT_STREQ("123", st.String());

    constexpr auto st2 = seq_test2<4>{str, make_index_sequence<sizeof(str) - 1>()};
    ASSERT_STREQ("123", st2.String());
```

上記とほぼ同様のクラステンプレートstd::index_sequence、std::make_index_sequenceが、
utilityで定義されているため、以下ではこれらを使用する。

#### StaticStringの開発 <a id="SS_13_7_6_2"></a>
StaticStringはすでに示したテクニックを使い、下記のように定義できる。

```cpp
    //  example/h/nstd_static_string.h 10

    template <size_t N>
    class StaticString {
    public:
        constexpr StaticString(char const (&str)[N]) noexcept : StaticString{0, str, std::make_index_sequence<N - 1>{}} {}

        template <size_t M>
        constexpr StaticString(size_t offset, StaticString<M> ss) noexcept
            : StaticString{offset, ss.string_, std::make_index_sequence<N - 1>{}}
        {
        }

        constexpr StaticString(std::initializer_list<char> args) noexcept
            : StaticString{0, args, std::make_index_sequence<N - 1>{}}
        {
        }

        constexpr char const (&String() const noexcept)[N] { return string_; }
        constexpr size_t Size() const noexcept { return N; }

    private:
        char const string_[N];

    #if __cplusplus >= 202002L  // c++20
        template <Beginable T, size_t... I>
    #else  // c++17
        template <typename T, size_t... I>
    #endif
        // offsetは部分StaticString切り出しのため(TopStr, BottomStr)
        constexpr StaticString(size_t offset, T& t, std::index_sequence<I...>) noexcept
            : string_{std::begin(t)[I + offset]...}
        {
        }

        template <size_t M>
        friend class StaticString;
    };
```

文字列リテラルからStaticStringを生成する単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/nstd_static_string_ut.cpp 12

    const auto fs = StaticString{"abc"};  // C++17からのNの指定は不要

    static_assert(sizeof(4) == fs.Size());
    ASSERT_STREQ("abc", fs.String());

    // 文字列不足であるため、下記はコンパイルさせない
    // constexpr StaticString<4> fs2{"ab"};
```

また、std::initializer_list\<char>による初期化の単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/nstd_static_string_ut.cpp 24

    const auto fs = StaticString<4>{'a', 'b', 'c'};  // C++17でもNの指定は必要

    static_assert(sizeof(4) == fs.Size());
    ASSERT_STREQ("abc", fs.String());

    // 文字列不足であるため、下記はコンパイルさせない
    // constexpr StaticString<4> fs2{'a', 'b'};
```

次にこのクラスにc++17用に`operator==`とc++20用に`operator<=>`を追加する。

```cpp
    //  example/h/nstd_static_string.h 49

    namespace Inner_ {
    template <size_t N>
    constexpr bool equal_n(size_t n, StaticString<N> const& lhs, StaticString<N> const& rhs) noexcept
    {
        if (n == N) {
            return true;
        }
        else {
            return lhs.String()[n] != rhs.String()[n] ? false : equal_n(n + 1, lhs, rhs);
        }
    }
    }  // namespace Inner_

    #if __cplusplus <= 201703L  // c++17
    template <size_t N1, size_t N2>
    constexpr bool operator==(StaticString<N1> const&, StaticString<N2> const&) noexcept
    {
        return false;
    }

    template <size_t N1, size_t N2>
    constexpr bool operator!=(StaticString<N1> const& lhs, StaticString<N2> const& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <size_t N>
    constexpr bool operator==(StaticString<N> const& lhs, StaticString<N> const& rhs) noexcept
    {
        return Inner_::equal_n(0, lhs, rhs);
    }

    template <size_t N>
    constexpr bool operator!=(StaticString<N> const& lhs, StaticString<N> const& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <size_t N1, size_t N2>
    constexpr bool operator==(StaticString<N1> const& lhs, char const (&rhs)[N2]) noexcept
    {
        return lhs == StaticString{rhs};
    }

    template <size_t N1, size_t N2>
    constexpr bool operator!=(StaticString<N1> const& lhs, char const (&rhs)[N2]) noexcept
    {
        return !(lhs == rhs);
    }

    template <size_t N1, size_t N2>
    constexpr bool operator==(char const (&lhs)[N1], StaticString<N2> const& rhs) noexcept
    {
        return StaticString{lhs} == rhs;
    }

    template <size_t N1, size_t N2>
    constexpr bool operator!=(char const (&lhs)[N1], StaticString<N2> const& rhs) noexcept
    {
        return !(lhs == rhs);
    }
    #elif __cplusplus >= 202002L  // c++20
    // 以下、operator==とoperator!=を<=>に置き換え
    template <size_t N1, size_t N2>
    constexpr auto operator<=>(StaticString<N1> const& lhs, StaticString<N2> const& rhs) noexcept
    {
        if constexpr (N1 != N2) {
            return N1 <=> N2;  // サイズが異なる場合は直接サイズを比較
        }
        else {
            return std::lexicographical_compare_three_way(lhs.String(), lhs.String() + N1 - 1, rhs.String(),
                                                          rhs.String() + N2 - 1);
        }
    }

    template <size_t N1, size_t N2>
    constexpr auto operator<=>(StaticString<N1> const& lhs, char const (&rhs)[N2]) noexcept
    {
        return lhs <=> StaticString{rhs};
    }

    template <size_t N1, size_t N2>
    constexpr auto operator<=>(char const (&lhs)[N1], StaticString<N2> const& rhs) noexcept
    {
        return StaticString{lhs} <=> rhs;
    }

    // operator==は明示的に定義する必要がある（<=>からは自動生成されない）
    template <size_t N1, size_t N2>
    constexpr bool operator==(StaticString<N1> const& lhs, StaticString<N2> const& rhs) noexcept
    {
        return (lhs <=> rhs) == 0;
    }

    template <size_t N1, size_t N2>
    constexpr bool operator==(StaticString<N1> const& lhs, char const (&rhs)[N2]) noexcept
    {
        return lhs == StaticString{rhs};
    }

    template <size_t N1, size_t N2>
    constexpr bool operator==(char const (&lhs)[N1], StaticString<N2> const& rhs) noexcept
    {
        return StaticString{lhs} == rhs;
    }
    #endif
```

単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/nstd_static_string_ut.cpp 70

    static_assert(StaticString{"123"} == StaticString{"123"});
    static_assert(StaticString{"123"} != StaticString{"1234"});
    static_assert(StaticString{"123"} == "123");
    static_assert("123" == StaticString{"123"});
    static_assert(StaticString{"123"} != "1234");
    static_assert("1234" != StaticString{"123"});
```

[暗黙の型変換](term_explanation.md#SS_19_13_1)を利用した文字列リテラルからStaticStringオブジェクトへの変換は、
StaticStringがテンプレートであるため機能せず、上記のように書く必要がある。

同様にoperator + を追加する。

```cpp
    //  example/h/nstd_static_string.h 158

    namespace Inner_ {
    template <size_t N1, size_t... I1, size_t N2, size_t... I2>
    constexpr StaticString<N1 + N2 - 1> concat(char const (&str1)[N1], std::index_sequence<I1...>, char const (&str2)[N2],
                                               std::index_sequence<I2...>) noexcept
    {
        return {str1[I1]..., str2[I2]...};
    }
    }  // namespace Inner_

    template <size_t N1, size_t N2>
    constexpr auto operator+(StaticString<N1> const& lhs, StaticString<N2> const& rhs) noexcept
    {
        return Inner_::concat(lhs.String(), std::make_index_sequence<N1 - 1>{}, rhs.String(),
                              std::make_index_sequence<N2>{});
    }

    template <size_t N1, size_t N2>
    constexpr auto operator+(StaticString<N1> const& lhs, char const (&rhs)[N2]) noexcept
    {
        return lhs + StaticString{rhs};
    }

    template <size_t N1, size_t N2>
    constexpr auto operator+(char const (&lhs)[N1], StaticString<N2> const& rhs) noexcept
    {
        return StaticString{lhs} + rhs;
    }
```

```cpp
    //  example/template_cpp17/nstd_static_string_ut.cpp 83

    constexpr auto fs0 = StaticString{"1234"} + StaticString{"567"};
    static_assert(std::is_same_v<StaticString<fs0.Size()> const, decltype(fs0)>);
    static_assert("1234567" == fs0);

    constexpr auto fs1 = StaticString{"1234"} + ":";
    static_assert(std::is_same_v<StaticString<fs1.Size()> const, decltype(fs1)>);
    static_assert("1234:" == fs1);

    constexpr auto fs2 = ":" + StaticString{"567"};
    static_assert(std::is_same_v<StaticString<fs2.Size()> const, decltype(fs2)>);
    static_assert(":567" == fs2);

    constexpr auto fs3 = StaticString{"1234"} + ":" + StaticString{"567"};
    static_assert(std::is_same_v<StaticString<fs3.Size()> const, decltype(fs3)>);
    static_assert("1234:567" == fs3);
```

以上でstd::stringのように=、==、+などの演算が可能となった。
さらに下記の関数を追加することで、任意の位置、
任意のサイズの文字列を切り出せるようにすることでStaticStringはより便利に使用できるようになる。

```cpp
    //  example/h/nstd_static_string.h 188

    template <size_t SIZE, size_t N>  // StaticString<SiZE>の部分文字列生成
    constexpr auto TopStr(StaticString<N> ss) noexcept
    {
        return StaticString<SIZE + 1>{0, ss};  // SIZE文字 + 終端文字
    }

    template <size_t OFFSET, size_t N>  // 先頭からオフセット2文字～終端文字まで
    constexpr auto BottomStr(StaticString<N> ss) noexcept
    {
        return StaticString<N - OFFSET>{OFFSET, ss};
    }
```

```cpp
    //  example/template_cpp17/nstd_static_string_ut.cpp 53

    constexpr auto ss  = StaticString{"0123456789"};
    auto           ss2 = TopStr<2>(ss);  // 先頭2文字
    static_assert(3 == ss2.Size());      // 先頭2文字 + 終端文字
    ASSERT_STREQ("01", ss2.String());

    auto ss8 = BottomStr<2>(ss);     // 先頭からオフセット2文字～終端文字まで
    static_assert(9 == ss8.Size());  // 先頭からオフセット2文字～終端文字までは結果的に9文字
    ASSERT_STREQ("23456789", ss8.String());

    ASSERT_EQ(ss2 + ss8, ss);  // 元に戻す。+、= が使用される。
```

#### 整数をStaticStringに変換する関数の開発 <a id="SS_13_7_6_3"></a>
コンパイル時に__LINE__をStaticStringに変換できれば、
ファイル位置をStaticStringで表現できるため、
ここではその変換関数Int2StaticString\<>()の実装を行う。

行番号を10進数での文字列で表現するため、いくつかのヘルパ関数を下記のように定義する。

```cpp
    //  example/h/nstd_static_string_num.h 8

    namespace Inner_ {

    // 10進数桁数を返す
    constexpr size_t num_of_digits(size_t n) noexcept { return n > 0 ? 1 + num_of_digits(n / 10) : 0; }

    // 10のn乗を返す
    constexpr uint32_t ten_to_nth_power(uint32_t n) noexcept { return n == 0 ? 1 : 10 * ten_to_nth_power(n - 1); }

    // 10進数の桁の若い順番に左から並べなおす(12345 -> 54321)
    constexpr uint32_t reverse_num(uint32_t num) noexcept
    {
        return num != 0 ? (num % 10) * ten_to_nth_power(num_of_digits(num) - 1) + reverse_num(num / 10) : 0;
    }

    // 10進数一桁をacsii文字に変換
    constexpr char digit_to_char(uint32_t num, uint32_t n_th) noexcept
    {
        return '0' + (num % (ten_to_nth_power(n_th + 1))) / ten_to_nth_power(n_th);
    }

    // Int2StaticStringのヘルパ関数
    template <size_t N, size_t... Cs>
    constexpr StaticString<num_of_digits(N) + 1> make_static_string(std::index_sequence<Cs...>) noexcept
    {
        return {digit_to_char(reverse_num(N), Cs)...};
    }
    }  // namespace Inner_
```

単体テストは下記のようになる。

```cpp
    //  example/template/nstd_static_string_num_ut.cpp 47

    constexpr auto ns       = make_static_string<__LINE__>(std::make_index_sequence<Inner_::num_of_digits(__LINE__)>());
    auto           line_num = __LINE__ - 1;

    ASSERT_EQ(std::to_string(line_num), ns.String());
```

このままでは使いづらいため、これをラッピングした関数を下記のように定義することで、
Int2StaticString\<>()が得られる。

```cpp
    //  example/h/nstd_static_string_num.h 38

    template <size_t N>
    constexpr StaticString<Inner_::num_of_digits(N) + 1> Int2StaticString() noexcept
    {
        return Inner_::make_static_string<N>(std::make_index_sequence<Inner_::num_of_digits(N)>());
    }
```

単体テストは下記のようになる。

```cpp
    //  example/template/nstd_static_string_num_ut.cpp 65

    constexpr auto ns       = Int2StaticString<__LINE__>();
    auto           line_num = __LINE__ - 1;

    ASSERT_EQ(std::to_string(line_num), ns.String());
```

#### ファイル位置を静的に保持したエクセプションクラスの開発 <a id="SS_13_7_6_4"></a>
「[静的な文字列オブジェクト](template_meta_programming.md#SS_13_7_6)」で見たように、
ファイル位置を動的に保持するエクセプションクラスは使い勝手が悪い。
ここでは、その問題を解決するためのExceptionクラスの実装を示す。

```cpp
    //  example/h/nstd_exception.h 11

    /// @class Exception
    /// @brief StaticString<>を使ったエクセプションクラス
    ///        下記のMAKE_EXCEPTIONを使い生成
    /// @tparam E   std::exceptionから派生したエクセプションクラス
    /// @tparam N   StaticString<N>
    template <typename E, size_t N>
    #if __cplusplus >= 202002L  // c++20
    requires std::derived_from<E, std::exception>
    #endif
    class Exception : public E {
    public:
        static_assert(std::is_base_of_v<std::exception, E>);

        Exception(StaticString<N> const& what_str) noexcept : what_str_{what_str} {}
        char const* what() const noexcept override { return what_str_.String(); }

    private:
        StaticString<N> const what_str_;
    };
```

StaticStringと同様に、このままでは不便であるため、下記の関数を定義する。

```cpp
    //  example/h/nstd_exception.h 33

    namespace Inner_ {
    template <typename E, template <size_t> class STATIC_STR, size_t N>
    #if __cplusplus >= 202002L  // c++20
    requires std::derived_from<E, std::exception>
    #endif
    auto make_exception(STATIC_STR<N> exception_str) noexcept { return Exception<E, N>{exception_str}; }
    }  // namespace Inner_

    template <typename E, size_t LINE_NUM, size_t F_N, size_t M_N>
    #if __cplusplus >= 202002L  // c++20
    requires std::derived_from<E, std::exception>
    #endif
    auto MakeException(char const (&filename)[F_N], char const (&msg)[M_N]) noexcept
    {
        return Inner_::make_exception<E>(StaticString{filename} + ":" + Int2StaticString<LINE_NUM>() + ":" + msg);
    }
```

単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/nstd_exception_ut.cpp 89

    auto caught   = false;
    auto line_num = __LINE__ + 2;  // 2行下の行番号
    try {
        throw MakeException<std::exception, __LINE__>(__FILE__, "some error message");
    }
    catch (std::exception const& e) {
        auto oss = std::ostringstream{};
        oss << __FILE__ << ":" << line_num << ":some error message";

        ASSERT_EQ(oss.str(), e.what());
        caught = true;
    }

    ASSERT_TRUE(caught);
```

Exceptionクラスの利便性をさらに高めるため、下記の定義を行う。

```cpp
    //  example/h/nstd_exception.h 54

    #define MAKE_EXCEPTION(E__, msg__) Nstd::MakeException<E__, __LINE__>(__FILE__, msg__)
```

上記は、関数型マクロの数少ない使いどころである。

単体テストは下記のようになる。

```cpp
    //  example/template_cpp17/nstd_exception_ut.cpp 109

    uint32_t line_num_div;  // エクセプション行を指定

    int32_t div(int32_t a, int32_t b)
    {
        if (b == 0) {
            line_num_div = __LINE__ + 1;  // 次の行番号
            throw MAKE_EXCEPTION(std::exception, "divided by 0");
        }

        return a / b;
    }
```
```cpp
    //  example/template_cpp17/nstd_exception_ut.cpp 126

    auto caught = false;

    try {
        div(1, 0);
    }
    catch (std::exception const& e) {  // リファレンスでcatchしなければならない
        auto oss = std::ostringstream{};
        oss << __FILE__ << ":" << line_num_div << ":divided by 0";
        ASSERT_EQ(oss.str(), e.what());
        caught = true;
    }

    ASSERT_TRUE(caught);
```

### 関数型をテンプレートパラメータで使う <a id="SS_13_7_7"></a>
ここで使う「関数型」とは、

* 関数へのポインタの型
* クロージャの型、もしくはラムダ式の型
* 関数オブジェクトの型

の総称を指す。

std::unique_ptrは、

* 第1パラメータにポインタの型
* 第2パラメータにそのポインタの解放用の関数ポインタの型

を取ることができるが、通常は第2パラメータは省略される。
省略時にはstd::default_deleteが割り当てられ、そのオブジェクトによって、
第1パラメータに対応するポインタがdeleteされる。

下記コードではこの第2パラメータにstd::freeのポインタの型を与え、
それから生成されるstd::unique_ptrオブジェクトを、

* abi::\__cxa_demangleがstd::mallocで取得したchar型ポインタ
* std::freeのポインタ

で初期化することでメモリの解放を行っている。

```cpp
    //  h/nstd_type2str.h 18

    auto demangled
        = std::unique_ptr<char, decltype(&std::free)>{abi::__cxa_demangle(to_demagle, 0, 0, &status), &std::free};
```

std::unique_ptrの第2パラメータには、上記のような関数へのポインタのみではなく、
関数型を取ることができる。

そのことを順を追って示す。
まずは、std::unique_ptrの動作を確かめるためのクラスを下記のように定義する。

```cpp
    //  example/template_cpp17/func_type_ut.cpp 8

    // デストラクタが呼び出された時に、外部から渡されたフラグをtrueにする
    struct A {
        explicit A(bool& destructor_called) noexcept : destructor_called{destructor_called} {}
        ~A() { destructor_called = true; };

        bool& destructor_called;
    };
```

次に示すのは、第2パラメータに何も指定しないパターンである。
テスト用クラスAの動作確認ができるはずである。

```cpp
    //  example/template_cpp17/func_type_ut.cpp 25

    {  // 第2パラメータに何も指定しない
        auto is_called = false;
        {
            auto ua = std::unique_ptr<A>{new A{is_called}};
            ASSERT_FALSE(is_called);  // uaのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_called);  // uaのデストラクタは呼ばれた
    }
```

次に示すのは、

```cpp
    //  example/template_cpp17/func_type_ut.cpp 18

    void delete_func(A* a) noexcept { delete a; }
```

のポインタをstd::unique_ptrの第2パラメータに与えた例である。

```cpp
    //  example/template_cpp17/func_type_ut.cpp 36

    {  // 第2パラメータに関数ポインタを与える
        auto is_called = false;
        {
            auto ua = std::unique_ptr<A, void (*)(A*)>{new A{is_called}, &delete_func};
            ASSERT_FALSE(is_called);  // uaのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_called);  // uaのデストラクタは呼ばれた
    }
```

次に示すのは、std::unique_ptrの第2パラメータにラムダを与えた例である。

```cpp
    //  example/template_cpp17/func_type_ut.cpp 47

    {  // 第2パラメータにラムダを与える
        auto is_called = false;
        {
            auto delete_lambda = [](A* a) noexcept { delete a; };

            // ラムダ式の型はインスタンス毎に異なるため、
            // ラムダ式の型を取得するためには下記のようにdecltypeを使う必要がある
            auto ua = std::unique_ptr<A, decltype(delete_lambda)>{new A{is_called}, delete_lambda};
            ASSERT_FALSE(is_called);  // uaのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_called);  // uaのデストラクタは呼ばれた
    }
```

次に示すのは、
std::unique_ptrの第2パラメータに関数型オブジェクトの型(std::function)を与えた例である。

```cpp
    //  example/template_cpp17/func_type_ut.cpp 62

    {  // 第2パラメータにstd::function型オブジェクトを与える
        auto is_called = false;
        {
            auto delete_obj = std::function<void(A*)>{[](A* a) noexcept { delete a; }};
            auto ua         = std::unique_ptr<A, std::function<void(A*)>&>{new A{is_called}, delete_obj};
            ASSERT_FALSE(is_called);  // uaのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_called);  // uaのデストラクタは呼ばれた
    }
```

以上で見てきたようにstd::unique_ptrの第2パラメータには、
第1パラメータのポインタを引数に取る関数型であれば指定できる。

このようなテンプレートパラメータを持つクラステンプレートの実装例を示すため、
「[RAII(scoped guard)](design_pattern.md#SS_9_10)でも示したScopedGuardの実装を下記する。

やや意外だが、このようなテンプレートパラメータに特別な記法はなく、以下のようにすれば良い。

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

上記コードの抜粋である下記は、テンプレートパラメータを関数型に制約するためのものである。

```cpp
    //  h/scoped_guard.h 7

    /// @brief RAIIのためのクラス。コンストラクタ引数の関数オブジェクトをデストラクタから呼び出す
    ///
    #if __cplusplus >= 202002L   // c++20

    template <std::invocable F>  // Fが呼び出し可能であることを制約
    #else  // c++17

    template <typename F>
    #endif
```

これがなければ、誤った型の関数型をテンプレートパラメータに指定できてしまう。

以下にこのクラステンプレートの単体テストを示す。

まずは、以下の関数と静的変数の組み合わせ

```cpp
    //  example/template_cpp17/func_type_ut.cpp 78

    bool is_caleded_in_static{false};
    void caleded_by_destructor() noexcept { is_caleded_in_static = true; }
```

を使った例である。

```cpp
    //  example/template_cpp17/func_type_ut.cpp 86

    {  // Fに関数ポインタを与える
        is_caleded_in_static = false;
        {
            auto sg = ScopedGuard{&caleded_by_destructor};
            ASSERT_FALSE(is_caleded_in_static);  // sgのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_caleded_in_static);  // sgのデストラクタは呼ばれた
    }
```

次に示すのは、それぞれにラムダ式とstd::functionを使った2例である。

```cpp
    //  example/template_cpp17/func_type_ut.cpp 101

    {  // Fにラムダ式を与える
        auto is_called = false;
        {
            auto gs = ScopedGuard{[&is_called]() noexcept { is_called = true; }};
            ASSERT_FALSE(is_called);  // sgのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_called);  // sgのデストラクタは呼ばれた
    }
    {  // Fにstd::function型オブジェクトを与える
        auto is_called = false;
        {
            auto f  = std::function<void(void)>{[&is_called]() noexcept { is_called = true; }};
            auto gs = ScopedGuard{std::move(f)};  // sgのデストラクタは呼ばれていない
            ASSERT_FALSE(is_called);              // sgのデストラクタは呼ばれた
        }
        ASSERT_TRUE(is_called);
    }
```

次に示すのは関数型オブジェクト

```cpp
    //  example/template_cpp17/func_type_ut.cpp 123

    struct TestFunctor {
        explicit TestFunctor(bool& is_called) : is_called_{is_called} {}
        void  operator()() noexcept { is_called_ = true; }
        bool& is_called_;
    };
```

を使った例である。

```cpp
    //  example/template_cpp17/func_type_ut.cpp 134

    {  // Fに関数型オブジェクトを与える
        auto is_called = false;
        auto tf        = TestFunctor{is_called};
        {
            auto sg = ScopedGuard{std::move(tf)};  // C++17以降の記法
            ASSERT_FALSE(is_called);               // sgのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_called);  // sgのデストラクタは呼ばれた
    }
```

C++17からサポートされた「クラステンプレートのテンプレートパラメータ推論」が使えないC++14以前では、
下記に示すようにScopedGuardのテンプレートラメータ型を指定しなければならない煩雑さがある。

```cpp
    //  example/template_cpp17/func_type_ut.cpp 146
    {  // Fに関数型オブジェクトを与える
        auto is_called = false;
        auto tf        = TestFunctor{is_called};
        {
            auto sg = ScopedGuard<TestFunctor>{std::move(tf)};  // C++14以前の記法
            ASSERT_FALSE(is_called);                            // sgのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_called);  // sgのデストラクタは呼ばれた
    }
```

これを回避するためには下記のような関数テンプレートを用意すればよい。

```cpp
    //  h/scoped_guard.h 38

    template <typename F>
    ScopedGuard<F> MakeScopedGuard(F&& f) noexcept
    {
        return ScopedGuard<F>(std::move(f));
    }
```

下記に示した単体テストから明らかな通り、関数テンプレートの型推測の機能により、
テンプレートパラメータを指定する必要がなくなる。

```cpp
    //  example/template_cpp17/func_type_ut.cpp 161

    {  // Fに関数ポインタを与える
        is_caleded_in_static = false;
        {
            auto sg = MakeScopedGuard(&caleded_by_destructor);
            ASSERT_FALSE(is_caleded_in_static);  // sgのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_caleded_in_static);  // sgのデストラクタは呼ばれた
    }
    {  // Fにラムダ式を与える
        auto is_called = false;
        {
            auto sg = MakeScopedGuard([&is_called]() noexcept { is_called = true; });
            ASSERT_FALSE(is_called);  // sgのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_called);  // sgのデストラクタは呼ばれた
    }
    {  // Fにstd::function型オブジェクトを与える
        auto is_called = false;
        {
            auto f  = std::function<void(void)>{[&is_called]() noexcept { is_called = true; }};
            auto sg = MakeScopedGuard(std::move(f));
            ASSERT_FALSE(is_called);  // sgのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_called);  // sgのデストラクタは呼ばれた
    }
    {  // Fに関数型オブジェクトを与える
        auto is_called = false;
        auto tf        = TestFunctor{is_called};
        {
            auto sg = MakeScopedGuard(std::ref(tf));  // std::refが必要
            ASSERT_FALSE(is_called);                  // sgのデストラクタは呼ばれていない
        }
        ASSERT_TRUE(is_called);  // sgのデストラクタは呼ばれた
    }
```

このような便利なテンプレートは、Nstdのようなライブラリで定義、宣言し、
ソースコード全域からアクセスできるようにするとプロジェクトの開発効率が少しだけ高まる。

[演習-関数型のテンプレートパラメータを持つクラステンプレート](exercise_q.md#SS_20_11_15)  

## 注意点まとめ <a id="SS_13_8"></a>
本章では、テンプレートメタプログラミングのテクニックや注意点について解説したが、
本章の情報量は多く、また他の章で行ったものもあるため以下にそれらをまとめる。

* [name lookup](term_explanation.md#SS_19_10_2)には複雑なルールが適用されるため、非直感的なバインドが行われる場合がある。
  従って、テンプレートライブラリの開発には単体テストは必須である。

* 使用しているコンパイラが[two phase name lookup](term_explanation.md#SS_19_10_3)をサポートしているか否かに気を付ける。
  それがオプションである場合は、two phase name lookupを活性化させる。

* 関数型マクロはそれ以外に実装方法がない時のみに使用する
  (「[関数型マクロ](programming_convention.md#SS_3_6_1)」参照)
  。

* 可変長引数を持つ関数の実装には[パラメータパック](template_meta_programming.md#SS_13_1_3)を使う。

* 処理速度や関数のリターンの型に影響する場合があるため、
  パラメータパックの処理の順番に気を付ける(「[前から演算するパラメータパック](template_meta_programming.md#SS_13_1_3_2)」参照)。

* [ADL](term_explanation.md#SS_19_10_5)を利用しない場合、テンプレートで使う識別子は名前空間名やthis->等で修飾する
  (「[意図しないname lookupの防止](template_meta_programming.md#SS_13_7_4)」参照)。

* テンプレートのインターフェースではないが、実装の都合上ヘッダファイルに記述する定義は、
  "namespace Inner\_"を使用し、非公開であることを明示する。
  また、"namespace Inner\_"で宣言、定義されている宣言、定義は単体テストを除き、
  外部から参照しない(「[is_void_sfinae_f](template_meta_programming.md#SS_13_3_2_3)の実装」参照)。

* [forwardingリファレンス](term_explanation.md#SS_19_15_3)の実際の型がlvalueリファレンスであるならば、
  constなlvalueリファレンスとして扱う
  (「[実引数/仮引数](programming_convention.md#SS_3_3_3_5)」参照)
  。

* ユニバーサルリファレンス引数を他の関数に渡すのであれば、std::forwardを使う
  (「[forwardingリファレンス](term_explanation.md#SS_19_15_3)」、「[forwardingリファレンスとstd::forward](template_meta_programming.md#SS_13_7_1)」参照)。

* 関数テンプレートとその特殊化はソースコード上なるべく近い位置で定義する
  (「[two phase name lookup](term_explanation.md#SS_19_10_3)」参照)。

* [two phase name lookup](term_explanation.md#SS_19_10_3)により意図しない副作用が発生する可能性があるため、
  STLが特殊化を想定しているstd::hash等を除き、STLの拡張は行わない。

* ユーザが定義するテンプレートは適切に定義された名前空間内で定義する
  (「[スコープの定義と原則](programming_convention.md#SS_3_8_1)」参照)
  。

* 型とその2項演算子オーバーロードは同じ名前空間で定義する
  (「[two phase name lookup](term_explanation.md#SS_19_10_3)」参照)。

* 関数テンプレートのオーバーロードと特殊化の[name lookup](term_explanation.md#SS_19_10_2)の優先度に気を付ける。
  オーバーロードのベストマッチ選択後に特殊化された関数テンプレートがname lookupの対象になるため、
  下記コードが示すように直感に反する関数が選択される場合がある。

```cpp
    //  example/template_cpp17/etc_ut.cpp 7

    template <typename T> constexpr int32_t f(T) noexcept { return 0; }                   // f-0
    template <typename T> constexpr int32_t f(T*) noexcept { return 1; }                  // f-1
    template <>           constexpr int32_t f<int32_t*>(int32_t*) noexcept { return 2; }  // f-2
    // f-2はf-1の特殊化のように見えるが、T == int32_t*の場合のf-0の特殊化である。
```
```cpp
    //  example/template_cpp17/etc_ut.cpp 18

    // 以下、f-0/f-1/f-2のテスト
    auto c   = char{0};
    auto i32 = 0;

    // 以下はおそらく直感通り
    static_assert(f(0) == 0);               // f-0が呼ばれる
    static_assert(f(&c) == 1);              // f-1が呼ばれる
    static_assert(f<int32_t*>(&i32) == 2);  // f-2が呼ばれる

    // 以下はおそらく直感に反する
    static_assert(f(nullptr) == 0);  // f-1ではなく、f-0が呼ばれる
    static_assert(f(&i32) == 1);     // f-2ではなく、f-1が呼ばれる
```

* forwardingリファレンスを持つ関数テンプレートをオーバーロードしない。
  「[forwardingリファレンスとstd::forward](template_meta_programming.md#SS_13_7_1)」で述べたように、
  forwardingリファレンスはオーバーロードするためのものではなく、
  lvalue、rvalue両方を受け取ることができる関数テンプレートを、
  オーバーロードを使わずに実現するための記法である。

* テンプレートに関数型オブジェクトを渡す場合、リファレンスの付け忘れに気を付ける
  (「[関数型をテンプレートパラメータで使う](template_meta_programming.md#SS_13_7_7)」
  、「[現象6 - STLのバグ?](debug.md#SS_15_9_6)」
  参照)。

* 意図しないテンプレートパラメータによるインスタンス化の防止や、
  コンパイルエラーを解読しやすくするために、適切にstatic_assert使うことは重要であるが、
  static_assertによるテンプレートパラメータの制約よりも、[コンセプト](term_explanation.md#SS_19_11_2)による制約を優先する。

* ランタイム時の処理を削減する、static_assertを適切に用いる等の目的のために、
  関数テンプレートには適切にconstexprを付けて宣言する
  (「[コンテナ用Nstd::operator\<\<の開発](template_meta_programming.md#SS_13_4_4)」
  参照)。


