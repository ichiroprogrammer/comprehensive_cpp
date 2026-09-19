<!-- practical/md/programming_convention.md -->
# プログラミング規約 <a id="SS_3"></a>
組織に秩序を与える法、道徳、慣習等をここではルールと呼ぶことにする。
当然ながら、秩序ある組織には良いルールがあり、混沌とした組織には悪いルールがあるか、
ルールはあっても守られていないか、そもそもルールが存在しない。

秩序あるソースコードとは、

* 可読性が高い。
    * 簡潔に記述されている。
    * 記述スタイルが統一されている(「[コーディングスタイル](coding_style.md#SS_5)」参照)。
    * ファイルや識別子の名前に規則性があり、適切に命名されている(「[命名規則](naming_practice.md#SS_6)」参照)。 
    * コメントの記法が統一されており、内容が適切である(「[コメント](comment.md#SS_7)」参照)。 
* 保守、テスト、移植等が容易である。
* 型安全性が配慮されている。
* コンパイル警告レベルが高く、かつ指摘がない。

のような特性を満たすものであるが、そうあるためには秩序ある組織と同様に良いルールが必要である。
本章の目的は、C++プログラミングにおけるそのようなルール(=プログラミング規約)を示すことである。

なお、型安全性とは、「正しく型付けされたソースコードは未定義動作をしない」
ことが保証されるという言語の特性である。
配列のオーバランが未定義動作を引き起こすことを考えれば明らかである通り、
C++は型安全性を保証しない。このことは、C++の劣等性を意味しないが、
それに配慮したプログラミング(型システムの最大限の利用等)が必要となることは事実である。

___

__この章の構成__

[型とインスタンス](programming_convention.md#SS_3_1)  
&emsp;[算術型](programming_convention.md#SS_3_1_1)  
&emsp;&emsp;[整数型](programming_convention.md#SS_3_1_1_1)  
&emsp;&emsp;[char型](programming_convention.md#SS_3_1_1_2)  
&emsp;&emsp;[std::byte型](programming_convention.md#SS_3_1_1_3)  
&emsp;&emsp;[bool型](programming_convention.md#SS_3_1_1_4)  
&emsp;&emsp;[浮動小数点型](programming_convention.md#SS_3_1_1_5)  

&emsp;[enum](programming_convention.md#SS_3_1_2)  
&emsp;[bit field](programming_convention.md#SS_3_1_3)  
&emsp;[class](programming_convention.md#SS_3_1_4)  
&emsp;[struct](programming_convention.md#SS_3_1_5)  
&emsp;[union](programming_convention.md#SS_3_1_6)  
&emsp;[配列](programming_convention.md#SS_3_1_7)  
&emsp;[型エイリアス](programming_convention.md#SS_3_1_8)  
&emsp;[const/constexprインスタンス](programming_convention.md#SS_3_1_9)  
&emsp;[リテラル](programming_convention.md#SS_3_1_10)  
&emsp;&emsp;[生文字列リテラル](programming_convention.md#SS_3_1_10_1)  

&emsp;[型推論](programming_convention.md#SS_3_1_11)  
&emsp;&emsp;[auto](programming_convention.md#SS_3_1_11_1)  

&emsp;[インスタンスの初期化](programming_convention.md#SS_3_1_12)  
&emsp;[rvalue](programming_convention.md#SS_3_1_13)  

[クラスとオブジェクト](programming_convention.md#SS_3_2)  
&emsp;[ファイルの使用方法](programming_convention.md#SS_3_2_1)  
&emsp;[クラスの規模](programming_convention.md#SS_3_2_2)  
&emsp;&emsp;[行数](programming_convention.md#SS_3_2_2_1)  
&emsp;&emsp;[メンバの数](programming_convention.md#SS_3_2_2_2)  
&emsp;&emsp;[凝集性](programming_convention.md#SS_3_2_2_3)  

&emsp;[アクセスレベルと隠蔽化](programming_convention.md#SS_3_2_3)  
&emsp;[メンバ関数](programming_convention.md#SS_3_2_4)  
&emsp;&emsp;[特殊メンバ関数](programming_convention.md#SS_3_2_4_1)  
&emsp;&emsp;[コンストラクタ](programming_convention.md#SS_3_2_4_2)  
&emsp;&emsp;[copyコンストラクタ、copy代入演算子](programming_convention.md#SS_3_2_4_3)  
&emsp;&emsp;[moveコンストラクタ、move代入演算子](programming_convention.md#SS_3_2_4_4)  
&emsp;&emsp;[初期化子リストコンストラクタ](programming_convention.md#SS_3_2_4_5)  
&emsp;&emsp;[デストラクタ](programming_convention.md#SS_3_2_4_6)  
&emsp;&emsp;[オーバーライド](programming_convention.md#SS_3_2_4_7)  

&emsp;[メンバ変数](programming_convention.md#SS_3_2_5)  
&emsp;&emsp;[メンバ変数の数 ](programming_convention.md#SS_3_2_5_1)  
&emsp;&emsp;[非静的なメンバ変数](programming_convention.md#SS_3_2_5_2)  
&emsp;&emsp;[静的なメンバ変数/定数の初期化](programming_convention.md#SS_3_2_5_3)  
&emsp;&emsp;[mutableなメンバ変数](programming_convention.md#SS_3_2_5_4)  

&emsp;[継承/派生](programming_convention.md#SS_3_2_6)  
&emsp;&emsp;[インターフェースの継承](programming_convention.md#SS_3_2_6_1)  
&emsp;&emsp;[多重継承](programming_convention.md#SS_3_2_6_2)  

&emsp;[オブジェクト](programming_convention.md#SS_3_2_7)  
&emsp;&emsp;[スライシング](programming_convention.md#SS_3_2_7_1)  
&emsp;&emsp;[オブジェクトの所有権](programming_convention.md#SS_3_2_7_2)  
&emsp;&emsp;[オブジェクトのライフタイム](programming_convention.md#SS_3_2_7_3)  

[関数](programming_convention.md#SS_3_3)  
&emsp;[関数構造のクライテリア](programming_convention.md#SS_3_3_1)  
&emsp;[オーバーロード](programming_convention.md#SS_3_3_2)  
&emsp;[演算子オーバーロード](programming_convention.md#SS_3_3_3)  
&emsp;[実引数/仮引数](programming_convention.md#SS_3_3_4)  
&emsp;[自動変数](programming_convention.md#SS_3_3_5)  
&emsp;[戻り値型](programming_convention.md#SS_3_3_6)  
&emsp;[constexpr関数](programming_convention.md#SS_3_3_7)  
&emsp;[スレッドセーフ性](programming_convention.md#SS_3_3_8)  
&emsp;[エクセプション処理](programming_convention.md#SS_3_3_9)  
&emsp;[ビジーループ](programming_convention.md#SS_3_3_10)  
&emsp;[非メンバ関数](programming_convention.md#SS_3_3_11)  

[構文](programming_convention.md#SS_3_4)  
&emsp;[複合文](programming_convention.md#SS_3_4_1)  
&emsp;[switch文](programming_convention.md#SS_3_4_2)  
&emsp;[if文](programming_convention.md#SS_3_4_3)  
&emsp;[while文](programming_convention.md#SS_3_4_4)  
&emsp;[範囲for文](programming_convention.md#SS_3_4_5)  
&emsp;[制御文のネスト](programming_convention.md#SS_3_4_6)  
&emsp;[return文](programming_convention.md#SS_3_4_7)  
&emsp;[goto文](programming_convention.md#SS_3_4_8)  
&emsp;[ラムダ式](programming_convention.md#SS_3_4_9)  
&emsp;[マクロの中の文](programming_convention.md#SS_3_4_10)  

[演算子](programming_convention.md#SS_3_5)  
&emsp;[優先順位](programming_convention.md#SS_3_5_1)  
&emsp;[代入演算](programming_convention.md#SS_3_5_2)  
&emsp;[ビット演算](programming_convention.md#SS_3_5_3)  
&emsp;[論理演算](programming_convention.md#SS_3_5_4)  
&emsp;[条件演算子](programming_convention.md#SS_3_5_5)  
&emsp;[メモリアロケーション](programming_convention.md#SS_3_5_6)  
&emsp;&emsp;[new](programming_convention.md#SS_3_5_6_1)  
&emsp;&emsp;[delete](programming_convention.md#SS_3_5_6_2)  

&emsp;[sizeof](programming_convention.md#SS_3_5_7)  
&emsp;[ポインタ間の演算](programming_convention.md#SS_3_5_8)  
&emsp;[RTTI](programming_convention.md#SS_3_5_9)  
&emsp;[キャスト、暗黙の型変換](programming_convention.md#SS_3_5_10)  

[プリプロセッサ命令](programming_convention.md#SS_3_6)  
&emsp;[関数型マクロ](programming_convention.md#SS_3_6_1)  
&emsp;[マクロ定数](programming_convention.md#SS_3_6_2)  

[ソースコードファイルとディレクトリ](programming_convention.md#SS_3_7)  
&emsp;[識別子の宣言、定義](programming_convention.md#SS_3_7_1)  
&emsp;[依存関係](programming_convention.md#SS_3_7_2)  
&emsp;[二重読み込みの防御](programming_convention.md#SS_3_7_3)  
&emsp;[ヘッダファイル内の#include](programming_convention.md#SS_3_7_4)  
&emsp;[#includeするファイルの順番](programming_convention.md#SS_3_7_5)  
&emsp;[#includeで指定するパス名](programming_convention.md#SS_3_7_6)  

[スコープ](programming_convention.md#SS_3_8)  
&emsp;[スコープの定義と原則](programming_convention.md#SS_3_8_1)  
&emsp;[名前空間](programming_convention.md#SS_3_8_2)  
&emsp;[using宣言/usingディレクティブ](programming_convention.md#SS_3_8_3)  
&emsp;[ADLと名前空間による修飾の省略](programming_convention.md#SS_3_8_4)  
&emsp;[名前空間のエイリアス](programming_convention.md#SS_3_8_5)  

[ランタイムの効率](programming_convention.md#SS_3_9)  
&emsp;[前置/後置演算子の選択](programming_convention.md#SS_3_9_1)  
&emsp;[operator X、operator x=の選択](programming_convention.md#SS_3_9_2)  
&emsp;[関数の戻り値オブジェクト](programming_convention.md#SS_3_9_3)  
&emsp;[move処理](programming_convention.md#SS_3_9_4)  
&emsp;[std::string vs std::string const& vs std::string_view](programming_convention.md#SS_3_9_5)  
&emsp;[extern template](programming_convention.md#SS_3_9_6)  

[標準クラス、関数の使用制限](programming_convention.md#SS_3_10)  
&emsp;[標準ライブラリ](programming_convention.md#SS_3_10_1)  
&emsp;&emsp;[スマートポインタの使用制限](programming_convention.md#SS_3_10_1_1)  
&emsp;&emsp;[配列系コンテナクラスの使用制限](programming_convention.md#SS_3_10_1_2)  
&emsp;&emsp;[std::stringの使用制限](programming_convention.md#SS_3_10_1_3)  
&emsp;&emsp;[std::string_viewの使用制限](programming_convention.md#SS_3_10_1_4)  

&emsp;[POSIX系関数](programming_convention.md#SS_3_10_2)  
&emsp;&emsp;[使用禁止関数一覧](programming_convention.md#SS_3_10_2_1)  
&emsp;&emsp;[使用禁止関数の理由や注意点](programming_convention.md#SS_3_10_2_2)  
&emsp;&emsp;[典型的な注意点](programming_convention.md#SS_3_10_2_3)  

[その他](programming_convention.md#SS_3_11)  
&emsp;[assertion](programming_convention.md#SS_3_11_1)  
&emsp;[アセンブラ](programming_convention.md#SS_3_11_2)  
&emsp;[言語拡張機能](programming_convention.md#SS_3_11_3)  

[特に重要なプログラミング規約](programming_convention.md#SS_3_12)  
  
  

[インデックス](comprehensive_intro.md#SS_1_3)に戻る。  

___

## 型とインスタンス <a id="SS_3_1"></a>

### 算術型 <a id="SS_3_1_1"></a>

#### 整数型 <a id="SS_3_1_1_1"></a>
* [整数型](core_lang_spec.md#SS_19_1_5)には、整数の基本型(intやlong等)を直接使わずに、
  [cstdint](https://cpprefjp.github.io/reference/cstdint.html)
  で定義されている型エイリアスを使用する。
    * 標準ライブラリやPOSIX等の標準クラスや関数のインターフェースが基本型を直接使用している場合は、
      その型に合わせるために基本型を直接使用する。
* 整数型には、特に理由がない限りに、int32\_tを使用する。
* 整数型の変数が負にならないのであれば、uint32\_tを使用する。
    * 符号あり型との演算がある場合は、その変数が負にならなくともint32\_tを使用する。
    * 符号あり型と符号なし型との比較をしない。
* sizeofの値や配列の長さの保持等には、size\_tを使用する。
* int32_tからint16_tや、int32_tからuint32_t等の値が変わる可能性がある代入を避ける。
  やむを得ずそのような代入をする場合、下記のようなnarrow_castを使いこのような問題を緩和する。

```cpp
    //  example/programming_convention/type_ut.cpp 9

    template <typename DST, typename SRC>
    DST narrow_cast(SRC v)
    {
        static_assert(std::is_integral_v<DST> && std::is_integral_v<DST>, "DST, SRC shoud be integral-type.");
        auto r = static_cast<DST>(v);

        assert((r < 0) == (v < 0));        // 符号が変わっていないことの確認
        assert(static_cast<SRC>(r) == v);  // bit落ちしていないことの確認

        return r;
    }
```

```cpp
    //  example/programming_convention/type_ut.cpp 27

    auto ui32 = narrow_cast<uint32_t>(128);                // 安全なint32_t -> uint32_t
    ASSERT_EQ(ui32, 128);                                  //
    ASSERT_DEATH(ui32 = narrow_cast<uint32_t>(-128), "");  // 危険なint32_t -> uint32_t

    auto i8 = narrow_cast<int8_t>(127);                    // 安全なint32_t -> int8_t
    ASSERT_EQ(i8, 127);                                    //
    ASSERT_DEATH(i8 = narrow_cast<int8_t>(128), "");       // 危険なint32_t -> int8_t

    i8 = narrow_cast<int8_t>(-1);                          // 安全なint32_t -> int8_t
    ASSERT_EQ(i8, -1);                                     //
    ASSERT_DEATH(i8 = narrow_cast<int8_t>(-129), "");      // 危険なint32_t -> int8_t
```

* [演習-汎整数型の選択](exercise_q.md#SS_22_1_1)

#### char型 <a id="SS_3_1_1_2"></a>
* charはascii文字の保持のみに使用する。
* char\*をvoid\*の代わりに使わない。
* charがsingedかunsignedかは処理系に依存するため、char型を[汎整数型](core_lang_spec.md#SS_19_1_4)として扱わない。
  8ビット整数には、int8\_tまたは、uint8\_tを使用する。
    * バイトストリームを表現する場合、int8_t\*、int8_t[]、uint8_t\*、uint8_t[]のいずれかを使う。

* [演習-汎整数型の演算](exercise_q.md#SS_22_1_2)

#### std::byte型 <a id="SS_3_1_1_3"></a>
* intよりもビット幅の小さい組み込み型の演算の結果は[汎整数型拡張](core_lang_spec.md#SS_19_1_8)によりint型になるため、
  uint8_tのビット演算の型もintとなる。
  intへの拡張が意図したものかどうかの判別は困難であるため、
  uint8_tインスタンスにビット演算が必要な場合、
  uint8_tの代わりに下記のようにstd::byte(「[BitmaskType](cpp_idioms.md#SS_21_2_3)」参照)を用いる。

```cpp
    //  example/programming_convention/type_ut.cpp 49
    // uint8_tのビット演算例

    auto u    = uint8_t{0b1000'0001};
    auto ret0 = u << 1;
    // uint8_t ret1{u << 1};  // 縮小型変換のため、コンパイルエラー
    uint8_t ret1 = u << 1;

    static_assert(std::is_same_v<decltype(ret0), int>);  // u << 1はintになる
    ASSERT_EQ(0b1'0000'0010, ret0);
    ASSERT_EQ(0b0000'0010, ret1);
```

```cpp
    //  example/programming_convention/type_ut.cpp 63
    // uint8_tに代わりstd::byteを使用したビット演算例

    auto b    = std::byte{0b1000'0001};
    auto ret0 = b << 1;
    auto ret1 = std::byte{b << 1};

    static_assert(std::is_same_v<decltype(ret0), std::byte>);  // b << 1はstd::byteになる
    ASSERT_EQ(std::byte{0b0000'0010}, ret0);
    ASSERT_EQ(std::byte{0b0000'0010}, ret1);
```

* std::byteの初期化には{}を用いる(static_castを使用しない)。

```cpp
    //  example/programming_convention/type_ut.cpp 76

    std::byte b0{0b1000'0001};                           // OK
    auto      b1 = std::byte{0b1000'0001};               // OK
    std::byte b2 = static_cast<std::byte>(0b1000'0001);  // NG
    // std::byte b3 = 0b1000'0001;                       // NG コンパイルエラー
```

#### bool型 <a id="SS_3_1_1_4"></a>
* bool型は、bool型リテラル(true/false)やbool型オブジェクトの保持のみに使用する。
* bool型を[汎整数型](core_lang_spec.md#SS_19_1_4)として扱わない。bool型に++を使用しない(--はコンパイルできない)。

```cpp
    //  example/programming_convention/type_ut.cpp 94

    #if __cplusplus < 201703L  // 以下のコードはC++14以前ではコンパイルできるが、
                               // C++17以降ではコンパイルエラー

        auto b = false;

        ASSERT_EQ(1, ++b);  // NG 予想通り動作するが、boolの目的外使用
        ASSERT_EQ(1, ++b);  // NG bは2ではなく1
        // ASSERT_EQ(1, --b);  // NG コンパイルエラー
    #endif
```

* ポインタ型やboolを除く汎整数型のインスタンスをbool値として使用しない。

```cpp
    //  example/programming_convention/type_ut.cpp 110

    void g(int32_t* ptr0, int32_t* ptr1) noexcept
    {
        if (ptr0) {  // NG ポインタ型をbool値として使用
            return;
        }

        if (ptr1 == nullptr) {  // OK
            return;
        }

        // ...
    }
```

#### 浮動小数点型 <a id="SS_3_1_1_5"></a>
* 小数演算に安易に[浮動小数点型](core_lang_spec.md#SS_19_1_12)を使用せず、
  [浮動小数点型のダイナミックレンジ](core_lang_spec.md#SS_19_1_12_1)が必要な場合のみにこれらの型を使用する。
  ちなみに銀河系の直径は1e+21メートル程度、プランク長は1.616229e-35メートルであるため、
  銀河から素粒子までのサイズを一つの基本型で表す場合においても、
  floatのダイナミックレンジに収まる。
  従って、floatやdoubleが必要になる場合は極めて限られる。

* [浮動小数点の誤差](core_lang_spec.md#SS_19_1_12_2)は避けられないため、浮動小数点型のインスタンスを==、!=で比較しない。
  代わりに[浮動小数点の比較](template_meta_programming.md#SS_13_5_1)で定義した関数テンプレートを使用する。

```cpp
    //  example/programming_convention/float_ut.cpp 11

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    //  ASSERT_EQ(0.05F, a + b);  // NG  a + b == 0.05Fは一般には成立しない。
    ASSERT_NE(0.05F, a + b);
```
```cpp
    //  example/programming_convention/float_ut.cpp 22

    /// @brief float比較用関数
    bool is_equal_f(float lhs, float rhs) noexcept { return std::abs(lhs - rhs) <= std::numeric_limits<float>::epsilon(); }
```
```cpp
    //  example/programming_convention/float_ut.cpp 30

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    // floatの比較はis_equal_fのような関数を使う。
    ASSERT_TRUE(is_equal_f(0.05F, a + b));  // OK
```

* 一つの式にfloatとdoubleを混在してしまうと、
  [イプシロン](core_lang_spec.md#SS_19_1_12_3)を使用した比較の定義ができなくなるので、
  一つの式に複数の浮動小数型のインスタンスを混在させない。

```cpp
    //  example/programming_convention/float_ut.cpp 42

    // 上記例と似たソースコードであるが、下記のような問題が起こる
    /// @brief double比較用関数
    bool is_equal_d(double lhs, double rhs) noexcept
    {
        return std::abs(lhs - rhs) <= std::numeric_limits<double>::epsilon();
    }
```
```cpp
    //  example/programming_convention/float_ut.cpp 54

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    // a + bはfloatの精度のまま、is_equal_dの引数の型であるdoubleに昇格される。
    // 一方、0.05はdoubleであるため(循環小数をdoubleの精度で切り捨てた値であるため)、
    // a + b(floatの精度の値)と0.05の差はdoubleのepsilonを超える。
    //  ASSERT_TRUE(is_equal_d(0.05, a + b));  // NG
    ASSERT_FALSE(is_equal_d(0.05, a + b));
```
```cpp
    //  example/programming_convention/float_ut.cpp 68

    // is_equal_dを改良して、引数の型が統一されていない呼び出しをコンパイルエラーにできるようにした。
    /// @brief 浮動小数点比較用関数
    template <typename FLOAT_0, typename FLOAT_1>
    bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs) noexcept
    {
        static_assert(std::is_floating_point_v<FLOAT_0>, "FLOAT_0 shoud be float or double.");
        static_assert(std::is_same_v<FLOAT_0, FLOAT_1>, "FLOAT_0 and FLOAT_1 shoud be a same type.");

        return std::abs(lhs - rhs) <= std::numeric_limits<FLOAT_0>::epsilon();
    }
```
```cpp
    //  example/programming_convention/float_ut.cpp 84

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    // a + bはfloatであり、0.05はdoubleであるため、下記コードはコンパイルできない。
    // ASSERT_TRUE(is_equal(0.05, a + b));
    ASSERT_TRUE(is_equal(0.05F, a + b));  // OK リテラルに型を指定して、引数の型を統一
```

* INFや、NANを演算で使用しない(「[浮動小数点の演算エラー](core_lang_spec.md#SS_19_1_12_4)」参照)。
* [汎整数型](core_lang_spec.md#SS_19_1_4)の演算とは違い、0除算等の[浮動小数点の演算エラー](core_lang_spec.md#SS_19_1_12_4)は、
  通常、プログラム終了シグナルを発生させないため、
  浮動小数点演算のエラーを捕捉する必要がある場合(ほとんどの場合、そうなる)は、
  `std::fetestexcept()`、`std::isnan()`、`std::isinf()`等を使用してエラーを捕捉する。

* 扱うダイナミックレンジに収まる限り、安易に浮動小数点を使わず、
  代わりに[固定小数点クラス](template_meta_programming.md#SS_13_5_2)や[有理数クラス](template_meta_programming.md#SS_13_5_4)を使用する。

* [演習-浮動小数点型](exercise_q.md#SS_22_1_3)

### enum <a id="SS_3_1_2"></a>
* C++の強力な型システムや、コンパイラの静的解析機能(switchでのcase抜け)を効果的に使用するために、
  一連の定数の列挙にはenumを使用する。
* 使用範囲や方法が明示しづらく、且つ整数型への[算術変換](core_lang_spec.md#SS_19_1_6)が行われてしまう旧来のenum
  (非スコープドenum)は、一部の例外を除き定義しない。
  代わりに、より型安全なスコープドenumを使用する。

```cpp
    //  example/programming_convention/type_ut.cpp 132

    enum CarLight { CL_Red, CL_Yellow, CL_Blue };
    enum WalkerLight { WL_Red, WL_Yellow, WL_Blue };

    bool f(CarLight cl) noexcept
    {
        switch (cl) {
        // 非スコープドenumは下記のようなコードを許容する(if文でも同様)。
        // スコープドenumであればこのような間違いはコンパイルエラーで発見できる。
        case WL_Red:  // CL_Redの間違い?
            // ...
            break;
        case CL_Yellow:  // これは正しい
        case CL_Blue:
        default:
            // ...
            break;
        }

        // ...
    }
```

* 列挙子に値を設定する必要がない場合（具体的な値に意味を持たない場合）には、値を設定しない。
  値を設定する場合にはそれらを最初に書き、同じ値を設定しない。

```cpp
    //  example/programming_convention/type_ut.cpp 162

    enum Colour {   // NG スコープドになっていない。
        Red   = 0,  // NG 配列インデックスでない場合、0を定義する必要はない。
        Green = 1,  // NG 連続値を定義する必要はない。
        Blue  = 2
    };

    // ...

    enum class Colour {  // OK
        Red,             // OK 不要な記述がない。
        Green,
        Blue
    };
```

* enumを配列のインデックスとして使う場合は以下のようにする。
    * スコープドenumの代わりに、旧来のenumをstruct内で定義する。
    * 最初に定義されるenumメンバは0で初期化する。
    * 最後の要素のシンボル名はMaxで終わることにより、
      その要素が最大値であることを示す。

```cpp
    //  example/programming_convention/type_ut.cpp 184

    enum class Foo { FooA = 0, FooB, FooMAX };

    struct Hoo  // structによるスコーピング
    {
        enum {
            HooA = 0,  // OK
            HooB,      // OK 値は暗黙に定義
            HooMAX     // OK
        };
    };

    void f() noexcept
    {
    //  int32_t a0[Foo::FooMAX];                       // NG コンパイルエラー
        int32_t a1[static_cast<size_t>(Foo::FooMAX)];  // NG castが必要になる
        int32_t a2[Hoo::HooMAX];                       // OK
        // ...
    }
```

* enumはC++11から前方宣言できるようになったため、
  この機能を使用して、不要なヘッダファイルの依存関係を作らないようにする。

```cpp
    //  example/programming_convention/type_ut.cpp 210

    enum class IncompleteEnum;
    enum class IncompleteEnum2 : uint64_t;

    // このファイルから可視である範囲にIncompleteEnum、IncompleteEnum2の定義はないが、
    // 前方宣言することで以下の関数宣言をすることができる。
    extern void g(IncompleteEnum);
    extern void g(IncompleteEnum2);
```

* アプリケーションの設定ファイルに保存された情報を復元させるような場合や、
  「[BitmaskType](cpp_idioms.md#SS_21_2_3)」を使用する場合を除き、enumへのキャストをしない。
* クラスのstatic constの整数定数の代わりにenumを使うことは、
  C++言語仕様やコンパイラの機能が不十分だった頃のテクニックであり、もはや不要である。
  代わりにstatic constexprインスタンス(「[constexpr関数](core_lang_spec.md#SS_19_5_3)」参照)を使用する。
  こうすることで定数の型を明示できる。

* [演習-定数列挙](exercise_q.md#SS_22_1_4)
* [演習-enum](exercise_q.md#SS_22_1_5)

### bit field <a id="SS_3_1_3"></a>
* ハードウエアレジスタにアクセスをする目的でのみ使用する。
* bit fieldの型は、unsigned intにする。

### class <a id="SS_3_1_4"></a>
* 「[クラスとオブジェクト](programming_convention.md#SS_3_2)」を参照せよ。

### struct <a id="SS_3_1_5"></a>
* メンバ変数を持つ構造体は、[POD](core_lang_spec.md#SS_19_4_5)としてのみ使用する。
* メンバ変数を持つ構造体を基底クラスとした継承をしない。
  従ってそのような構造体は常にfinalであるが、finalの明示はしない。
* メンバ変数(static constやstatic constexprメンバは定数とする)を持たない構造体は、
  templateや非スコープドenumのスコーピング
  (「[enum](programming_convention.md#SS_3_1_2)」や「[enum](core_lang_spec.md#SS_19_3_1)」参照)等に使用しても良い。
* コンストラクタ以外のメンバ関数を定義しない。
    * [ディープコピー](cpp_idioms.md#SS_21_12_2)(「[コンストラクタ](programming_convention.md#SS_3_2_4_2)」参照)が必要な型は、structでなくclassで表す。
    * デフォルトコンストラクタを除く[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)に対して、
      = defaultの明示をしない。

```cpp
    //  example/programming_convention/type_ut.cpp 223

    struct Pod final {                        // NG finalは不要
        Pod()                     = default;  // OK
        ~Pod()                    = default;  // NG = defaultは不要
        Pod(Pod const&)           = delete;   // OK copyを禁止する場合
        Pod operator=(Pod const&) = delete;   // OK copyを禁止する場合

        int32_t x;
        int32_t y;
    };
```

* Cとシェアしない構造体を無名構造体とそのtypedefで定義しない。

```cpp
    //  example/programming_convention/type_ut.cpp 236

    typedef struct {  // NG   無名構造体
        int32_t x;
        int32_t y;
    } StructNG;  // NG   無名構造体をtypedef

    typedef struct StructOK_C_Share {  // Cとシェアする場合OK
        int32_t x;
        int32_t y;
    } StructOK_C_Share;

    struct StructOK {  // OK   Cとシェアしない場合このように書く
        int32_t x;
        int32_t y;
    };
```

### union <a id="SS_3_1_6"></a>
* ハードウエアレジスタにアクセスをする目的以外で使用しない(以下のような使い方のみ認められる)。

```cpp
    //  example/programming_convention/type_ut.cpp 257

    union XXX_REG {
        uint8_t  bytes[4];
        uint32_t word32;
    };

    uint8_t f() noexcept
    {
        // 0x14000000はハードウェアレジスタのアドレスとする
        auto& XXX_REG_INST = *reinterpret_cast<XXX_REG*>(0x14000000);
        auto  byte_1       = XXX_REG_INST.bytes[1];

        return byte_1;
    }
```

* 上記のようなunionはランタイム依存性が強いため、それへの依存を最小にする。
  従って、unionの定義を外部[パッケージ](cpp_idioms.md#SS_21_9_2)に公開(「[ソースコードファイルとディレクトリ](programming_convention.md#SS_3_7)」参照)しない。

* 上記以外でunionのような機能が必要な場合、
  [std::variant](stdlib_and_concepts.md#SS_20_10)(「[std::variantとジェネリックラムダ](template_meta_programming.md#SS_13_7_2_2)」参照)を使用する
  (std::anyはunionの代替えにはならないので、このような場合には使用しない)。

### 配列 <a id="SS_3_1_7"></a>
* 列型オブジェクトは以下で述べるような問題や、
  [AAAスタイル](cpp_idioms.md#SS_21_11_1)で生成できない等の様々な問題を起こしやすいため、
  使用を可避できない場合を除き使用しない。代わりに`std::array`を使う。
* new[]を使用しない。new[]で生成した配列オブジェクトはdelete[]で解放しなければならない。
  これは発見困難なバグの発生源になりやすい。
  可変長配列が必要な場合は、std::vectorを使用する(「[new](programming_convention.md#SS_3_5_6_1)」参照)。
  固定長配列を動的に確保する場合は、std::arrayをnewする。
* 配列からポインタへの暗黙の型変換をしない(「[キャスト、暗黙の型変換](programming_convention.md#SS_3_5_10)」参照)。
  特に、オブジェクトの配列をそのオブジェクトの基底クラスへのポインタに代入しないことは重要である
  (「[スライシング](programming_convention.md#SS_3_2_7_1)」参照)。
* 関数の仮引数を一見、配列に見える型にしない
  (「[実引数/仮引数](programming_convention.md#SS_3_3_4)」参照)。
* char型の配列を文字列リテラルで初期化する場合、配列の長さを指定しない。

```cpp
    //  example/programming_convention/type_ut.cpp 278

    #if 0
        // g++では通常コンパイルエラーとなるが、-fpermissiveを付ければコンパイルできてしまう。
        char a[3]{"abc"};  // NG aはヌル終端されない
    #else
        char a[]{"abc"};  // OK
    #endif
```

* 配列の全要素にアクセスするような繰り返し処理には[範囲for文](core_lang_spec.md#SS_19_9_2)を使用する。

* [演習-配列の範囲for文](exercise_q.md#SS_22_1_6)

### 型エイリアス <a id="SS_3_1_8"></a>
* Cとシェアされる型エイリアスを除き、typedefではなくusingを使用する。

```cpp
    //  example/programming_convention/type_ut.cpp 295

    // C90スタイル
    typedef unsigned int uint;                 // NG
    typedef void (*void_func_int32)(int32_t);  // NG

    // ...

    // C++11スタイル
    using uint            = unsigned int;       // OK
    using void_func_int32 = void (*)(int32_t);  // OK

    template <class T>                      // templateで型エイリアスを作ることもできる。
    using Dict = std::map<std::string, T>;  // OK
```

* 型へのポインタのエイリアスは、それを使用してconstポインタが定義できないため、
  型へのポインタ(関数ポインタを除く)のエイリアスを作らない。

```cpp
    //  example/programming_convention/type_ut.cpp 319

    using pint32_t = int32_t*;  // pint32_tにはconstポインタを代入できない。

    pint32_t const pint32_0_c = nullptr;  // 一見pint32_0_cはconstポインタに見えるが。
    int32_t const* pint32_1_c = nullptr;

    // pint32_0_cの型とpint32_1_cの型が同じであれば問題ないのだが、
    // エイリアスのため結合順が変わった影響でそうはならない。
    // *pint32_0_cはconstではなく、pint32_0_cがconstとなる。
    static_assert(std::is_same_v<decltype(pint32_0_c),  int32_t* const>);
    static_assert(std::is_same_v<decltype(*pint32_0_c), int32_t&>);
    static_assert(std::is_same_v<decltype(pint32_1_c),  int32_t const*>);
    static_assert(std::is_same_v<decltype(*pint32_1_c), int32_t const&>);
```

* [演習-エイリアス](exercise_q.md#SS_22_1_7)

### const/constexprインスタンス <a id="SS_3_1_9"></a>
* インスタンス、インスタンスへのポインタ、インスタンスへのリファレンス等に対して、
    * [constexpr変数](core_lang_spec.md#SS_19_5_2)をパラメータにした場合、コンパイル時に定数として評価できる関数は、
      [constexpr関数](core_lang_spec.md#SS_19_5_3)として宣言する。
    * コンパイル時に必ず定数として評価したい[constexpr関数](core_lang_spec.md#SS_19_5_3)には、
      [consteval](core_lang_spec.md#SS_19_5_7)を使用する。
    * constexprにはできないが、const(「[constインスタンス](core_lang_spec.md#SS_19_4_12)」にはできるインスタンスは、
      constとして定義する。関数の仮引数になっているリファレンスやポインタをconstにすることは特に重要である
    * 文字列リテラルのアドレスを非constポインタ型変数に代入しない(「[リテラル](core_lang_spec.md#SS_19_2)」参照)。
    * イテレータにおいても、可能な場合は、イテレータをconstするか、const_iteratorを使う。

```cpp
    //  example/programming_convention/type_const_ut.cpp 13

    // name0は文字列リテラルを指すポインタなのでconstでなければならない。
    char const* name0 = "hoge";

    // name1は文字列リテラルでないのでconstでなくてよい。
    char name1[] = "hoge";

    char const* get_str();
    // 左側のconstはname2の指す先をconstにする。
    // 右側のconstはname2自体をconstにする。
    char const* const name2 = get_str();

    // name2の右辺がリテラルならば、下記のようにするべきである。
    constexpr char const* name3 = "hoge";

    void f(std::vector<int32_t>& vec)
    {
        std::vector<int32_t>::iterator const iter = vec.begin();  // iter自体がconst

        *iter = 10;
        // ++iter;      // 意図的にコンパイルエラー

        std::vector<int32_t>::const_iterator const_iter_0 = vec.begin();   // *const_iter_0がconst
        auto                                 const_iter_1 = vec.cbegin();  // *const_iter_1がconst
        static_assert(std::is_same_v<std::vector<int32_t>::const_iterator, decltype(const_iter_1)>);

        // *const_iter_0 = 10;   // 意図的にコンパイルエラー
        ++const_iter_0;

        // *const_iter_1 = 10;   // 意図的にコンパイルエラー
        ++const_iter_1;

        // ...
    }
```

* constは[west-const](cpp_idioms.md#SS_21_11_3)に従って記述する。

```cpp
    //  example/programming_convention/type_const_ut.cpp 52

    const std::string s;  // NG
    std::string const t;  // OK

    std::string const* s_ptr;  // NG
    std::string const* t_ptr;  // OK

    std::string const& f();  // NG 関数の宣言
    std::string const& g();  // OK 関数の宣言

    char        abc[]{"abc"};
    char const* a = abc;  // NG *aはconst
    char const* b = abc;  // OK *aはconst
    char* const c = abc;  // NG *aではなく、aがconstになり、意味が変わる

    char const* const d = abc;  // NG
    char const* const e = abc;  // OK
```

* [演習-constの意味](exercise_q.md#SS_22_1_8)
* [演習-const/constexpr](exercise_q.md#SS_22_1_9)

### リテラル <a id="SS_3_1_10"></a>
* ヌルポインタを表すポインタリテラルとして、nullptrを使用する(0やNULLを使用しない)。

```cpp
    //  example/programming_convention/type_ut.cpp 342

    int32_t* a{0};        // NG   オールドスタイル
    int32_t* b{NULL};     // NG   C90の書き方
    int32_t* c{nullptr};  // OK   C++11
```
```cpp
    //  example/programming_convention/type_ut.cpp 360

    extern int16_t g(long a) noexcept;
    extern int8_t  g(int* a) noexcept;

    // NULLを使ったことで、わかりづらいバグが発生する例
    g(NULL);  // NG NULLの型はポインタではなく、longであるため、この呼び出しはg(long)を呼び出す
    static_assert(std::is_same_v<int16_t, decltype(g(NULL))>);

    g(nullptr);  // OK 意図通り、g(int*)を呼び出す。
    static_assert(std::is_same_v<int8_t, decltype(g(nullptr))>);
```

* 文字列リテラル("xxx")はconstオブジェクトとして扱う
  (「[const/constexprインスタンス](programming_convention.md#SS_3_1_9)」、「[std::string型リテラル](core_lang_spec.md#SS_19_2_6_2)」参照)。
* 長い[汎整数型](core_lang_spec.md#SS_19_1_4)リテラルを使用する場合は、適切に区切りを入れる(C++14)。
* ビットマスク等2進数を使用した方が直感的な場合には2進数リテラルを使用する(C++14)。

```cpp
    //  example/programming_convention/type_ut.cpp 381

    auto a = 123'456'789U;       // = 123456789
    auto b = 0x123'456'789U;     // = 0x123456789
    auto c = 0b1001'0001'0101U;  // = 0x915
```

* bool型を表すリテラルにはtrue、falseを使用する。代わりに0、1、!0等を使わない。

```cpp
    //  example/programming_convention/type_ut.cpp 392

    bool a{0};          // NG
    bool b{!0};         // NG
    bool c{false};      // OK
    auto d = bool{0};   // NG
    auto e = bool{!0};  // NG
    auto f = true;      // OK
```

* long値リテラルを表す文字には"l"ではなく、"L"を使う。

```cpp
    //  example/programming_convention/type_ut.cpp 405

    auto a = 432l;  // NG 4321と区別が難しい
    auto b = 432L;  // OK
```

#### 生文字列リテラル <a id="SS_3_1_10_1"></a>
* 正規表現を表す文字列リテラルを使用する場合、文字列内のエスケープシーケンスをエスケープするのでなく、
  には[生文字列リテラル](core_lang_spec.md#SS_19_2_1)を使用する。これにより正規表現の可読性が向上する。

```cpp
    //  example/programming_convention/raw_literal_ut.cpp 9

    std::pair<std::string, std::string> url2addr(std::string const& url)
    {
    #if 0  // 正規表現のエスケープ
        std::regex re("^(https?|ftp):\\/\\/([^\\/\\s]+)(\\/.*)?$");
    #else
        std::regex re(R"(^(https?|ftp)://([^/\s]+)(/.*)?$)");  // 生文字リテラル
    #endif
        std::smatch match;

        if (std::regex_search(url, match, re) && match.size() > 3) {
            std::string host = match.str(2);
            std::string path = match.str(3);
            return {host, path};
        }
        else {
            return {"", ""};
        }
    }

    //  example/programming_convention/raw_literal_ut.cpp 33

    std::string const url = "https://www.example.com/path/to/resource";

    auto [host, path] = url2addr(url);
    ASSERT_EQ("www.example.com", host);
    ASSERT_EQ("/path/to/resource", path);
```

* [演習-危険なconst_cast](exercise_q.md#SS_22_1_10)
* [演習-リテラル](exercise_q.md#SS_22_1_11)

### 型推論 <a id="SS_3_1_11"></a>
#### auto <a id="SS_3_1_11_1"></a>
* [AAAスタイル](cpp_idioms.md#SS_21_11_1)に従い適切にautoを使用する。

```cpp
    //  example/programming_convention/type_ut.cpp 419

    void f(std::vector<std::string> const& strs)
    {
        auto s0 = std::string{"hehe"};  // OK
        auto s1{std::string{"hehe"}};   // OKだが、通常は代入を使用する
        auto s2 = s0;                   // OK
        auto s3 = get_name();           // NG get_name()の戻り値を見ないとs3の型が不明

        for (auto const& str : strs) {  // OK strsの型が明らかであるため、strの型も明らか
            // ...
        }
    }
```

* autoを使用する場合、&、\*、const等の付け忘れに注意する。

```cpp
    //  example/programming_convention/type_ut.cpp 439

    class A {
    public:
        A() = default;

    #if 0  // NG この関数を呼び出すとクラッシュ
        std::string const& Get(char first_byte) const noexcept
        {
            static std::string const empty;
            for (auto const str : strs) {       // NG &の付け忘れのため、スタック上の
                if (str.at(0) == first_byte) {  //    オブジェクトのリファレンスをreturnする。
                    return str;
                }
            }
            return empty;
        }

    #else  // OK 上のGetの修正。
        std::string const& Get(char first_byte) const noexcept
        {
            static std::string const empty;
            for (auto const& str : strs) {      // OK &を付けて、インスタンスのオブジェクトの
                if (str.at(0) == first_byte) {  //    リファレンスを返せるようになった。
                    return str;
                }
            }
            return empty;
        }
    #endif

    private:
        std::vector<std::string> strs{"aha", "ihi", "uhu"};
    };
```

* autoと= {}を使用した変数の宣言には以下のような紛らわしさがあるため、
  そのような記述を行わない(「[インスタンスの初期化](programming_convention.md#SS_3_1_12)」参照)。

```cpp
    //  example/programming_convention/type_ut.cpp 490

    auto a = 1;                                 // OK aの型はint
    auto b(1);                                  // 別の規制でNG ()より{}を優先的に使うべき
    auto c{1};                                  // OK cの型はint
    auto d = {1};                               // NG dの型はstd::initializer_list<int>
    auto e = {1, 2};                            // NG eの型はstd::initializer_list<int>
    auto f = std::initializer_list<int>{1, 2};  // OK

    static_assert(std::is_same_v<decltype(a), int>, "type not same");
    static_assert(std::is_same_v<decltype(b), int>, "type not same");
    static_assert(std::is_same_v<decltype(c), int>, "type not same");
    static_assert(std::is_same_v<decltype(d), std::initializer_list<int>>, "type not same");
    static_assert(std::is_same_v<decltype(e), std::initializer_list<int>>, "type not same");
    static_assert(std::is_same_v<decltype(f), std::initializer_list<int>>, "type not same");
```

* auto、[decltype](core_lang_spec.md#SS_19_11_15), decltype(auto)の微妙な違いに気を付ける。

```cpp
    //  example/programming_convention/type_ut.cpp 512

    short  s0{0};
    short& s0_ref{s0};

    {  // autoとdecltypeが同じ動作をするパターン
        auto a = s0;
        static_assert(std::is_same_v<decltype(a), short>);

        decltype(s0) d = s0;
        static_assert(std::is_same_v<decltype(d), short>);

        decltype(auto) da = s0;
        static_assert(std::is_same_v<decltype(da), short>);
    }
    {  // autoとdecltypeに違いが出るパターン
        auto a = s0_ref;
        static_assert(std::is_same_v<decltype(a), short>);

        decltype(s0_ref) d = s0_ref;  // dはリファレンス
        static_assert(std::is_same_v<decltype(d), short&>);

        decltype(auto) da = s0_ref;  // daはリファレンス
        static_assert(std::is_same_v<decltype(da), short&>);
    }

    short s1{0};
    {  // 微妙な違いで出るパターン
        auto a = s0 + s1;
        static_assert(std::is_same_v<decltype(a), int>);

        decltype(s0) d = s0 + s1;  // これが意図的ならよいが
        static_assert(std::is_same_v<decltype(d), short>);

        decltype(s0 + s1) d2 = s0 + s1;  // int&&にはならない
        static_assert(std::is_same_v<decltype(d2), int>);

        decltype(auto) da = s0 + s1;  // この方がクローンがないため上よりも良い
        static_assert(std::is_same_v<decltype(da), int>);
    }
```

* 通常の関数の定義に「[autoパラメータによる関数テンプレートの簡易定義](core_lang_spec.md#SS_19_11_13)」の使用を避ける。
  [autoパラメータによる関数テンプレートの簡易定義](core_lang_spec.md#SS_19_11_13)を使ったインライン関数は柔軟すぎる。

* [演習-適切なautoの使い方](exercise_q.md#SS_22_1_12)

### インスタンスの初期化 <a id="SS_3_1_12"></a>
* 関数内のオブジェクトは、出来る限り[AAAスタイル](cpp_idioms.md#SS_21_11_1)を用いて宣言し、同時に初期化する。
* [算術型](core_lang_spec.md#SS_19_1_3)の宣言に[AAAスタイル](cpp_idioms.md#SS_21_11_1)が使えない場合、
  「代入演算子を伴わない[一様初期化](core_lang_spec.md#SS_19_6_6)」を使用する。
  「代入演算子を伴う一様初期化」、「()、=による初期化」を使用しない。

```cpp
    //  example/programming_convention/type_ut.cpp 569

    int32_t a0(0);            // NG
    int32_t a1 = 0;           // NG
    int32_t a2{0};            // OK 一様初期化
    int32_t a3 = {0};         // NG 代入演算子を伴う一様初期化
    auto    a4 = 0;           // OK AAAの場合は一様初期を使わなくても問題ない
    auto    a5 = int32_t{0};  // OK AAA且つ一様初期
```

* リファレンスやポインタの宣言に[AAAスタイル](cpp_idioms.md#SS_21_11_1)が使えない場合、
  「代入演算子を伴わない[一様初期化](core_lang_spec.md#SS_19_6_6)」か「=による初期化」を使用する。
  「代入演算子を伴う一様初期化」、「()による初期化」を使用しない。

```cpp
    //  example/programming_convention/type_ut.cpp 578

    int32_t& r0(a0);     // NG
    int32_t& r1 = a0;    // OK
    int32_t& r2{a0};     // OK 一様初期化
    int32_t& r3 = {a0};  // NG 代入演算子を伴う一様初期化
    auto& r4 = a0;  // OK AAAの場合は一様初期を使わなくても問題ないが、&の付け忘れに気を付ける

    int32_t* p0(&a0);     // NG
    int32_t* p1 = &a0;    // OK
    int32_t* p2{&a0};     // OK 一様初期化
    int32_t* p3 = {&a0};  // NG 代入演算子を伴う一様初期化
    auto     p4 = &a0;    // OK AAAの場合は一様初期を使わなくても問題ない
    auto*    p5 = &a0;    // OK AAAの場合は一様初期を使わなくても問題ない
```

* 構造体やクラス型オブジェクトの宣言に[AAAスタイル](cpp_idioms.md#SS_21_11_1)が使えない場合、
    * 「代入演算子を伴わない[一様初期化](core_lang_spec.md#SS_19_6_6)」を使用する。
    * 上記では意図したコンストラクタが呼び出せない場合にのみ「()による初期化」を使用する。
  ただし、std::string、std::string_viewに関しては「 = "xxx"」を使用しても良い。

```cpp
    //  example/programming_convention/type_ut.cpp 606

    // 構造体の初期化
    struct Struct {
        int32_t     a;
        char const* str;
    };

    Struct s0{1, "1"};                          // OK 代入演算子を伴わない一様初期化
    Struct s1 = {2, "2"};                       // NG 代入演算子による一様初期化
    Struct s2{};                                // OK s2.aは0、s2.strはnullptrに初期化される。
    Struct s3;                                  // NG s3は未初期化
    auto   s4 = Struct{1, "1"};                 // OK AAAスタイル
    auto   s5 = Struct{};                       // OK AAAスタイル

    // クラスの初期化
    std::unique_ptr<Widget> a{std::make_unique<Widget>()};   // OK
    std::unique_ptr<Widget> b(std::make_unique<Widget>());   // NG {}を使うべき
    auto                    c{std::make_unique<Widget>()};   // OK
    auto                    d = std::make_unique<Widget>();  // OK
    // このような場合、重複を避けるため、変数宣言の型はautoが良い

    // std::string、std::string_viewの初期化
    std::string str0{"222"};                // OK
    std::string str1 = {"222"};             // NG = は不要
    std::string str2("222");                // NG {}で初期化できない時のみ、()を使う。
    std::string str3(3, '2');               // OK {}では初期化できない。str3 == "222"
    std::string str4 = "222";               // OK 例外的に認める
    auto        str5 = std::string{"222"};  // OK AAAスタイル

    std::string_view sv0 = "222";                    // OK 例外的に認める
    auto             sv1 = std::string_view{"222"};  // OK AAAスタイル

    // {}、()による初期化の違い
    std::vector<int32_t> vec0_i{1, 2, 3};                // OK vec0_i.size() == 3 && vec0_i[0] == 1 ...
    std::vector<int32_t> vec1_i{10};                     // OK vec1_i.size() == 1 && vec1_i[0] == 10
    std::vector<int32_t> vec2_i(10);                     // OK vec1_i.size() == 10
    auto                 vec3_i = std::vector{1, 2, 3};  // OK vec0_iと同じ

    std::vector<std::string> vec1_s{10};                             // OK vec1_s.size() == 10
    std::vector<std::string> vec2_s(10);                             // NG vec2_s.size() == 10  {}を優先するべき
    auto                     vec3_s = std::vector<std::string>{10};  // OK vec1_sと同じ

    // vec1_i、vec2_i、vec1_sの初期化は似ているが、結果は全く異なる。
    // vec1_iは、vector(std::initializer_list<>)を呼び出す。
    // vec2_iは、vector(int)を呼び出す。
    // vec1_sは、vector(int)を呼び出す。

    ASSERT_EQ(3, vec0_i.size());
    ASSERT_EQ(1, vec1_i.size());
    ASSERT_EQ(10, vec2_i.size());
    ASSERT_EQ(vec0_i, vec3_i);
    ASSERT_EQ(10, vec1_s.size());  // vec1_iと同じ形式で初期化したが結果は全く異なる。
    ASSERT_EQ(10, vec2_s.size());
    ASSERT_EQ(10, vec3_s.size());
```

* decltypeによるオブジェクトの宣言は、[AAAスタイル](cpp_idioms.md#SS_21_11_1)と同様に行う。

```cpp
    //  example/programming_convention/type_ut.cpp 674

    auto  a = 0;
    auto& b = a;

    decltype(a)    c = a;    // OKがautoの方が良い
    decltype(a)    d = {a};  // NG
    decltype(b)    e = a;    // OK
    decltype(auto) f = b;    // OK

    static_assert(std::is_same_v<decltype(c), int>);
    static_assert(std::is_same_v<decltype(d), int>);
    static_assert(std::is_same_v<decltype(e), int&>);
    static_assert(std::is_same_v<decltype(f), int&>);
```

* 配列の宣言には、「代入演算子を伴わない[一様初期化](core_lang_spec.md#SS_19_6_6)」を使用する。
  char[]に関しては、「代入演算子を伴わない一様初期化」か「 = "xxx"」を使用する。

```cpp
    //  example/programming_convention/type_ut.cpp 697

    int32_t array0[3]{1, 2, 3};     // OK 代入演算子を伴わない一様初期化
    int32_t array1[3] = {1, 2, 3};  // NG 代入演算子による一様初期化
    int32_t array2[3]{};            // OK 代入演算子を伴わない一様初期化
    int32_t array3[3] = {};         // NG 代入演算子による一様初期化

    char c_str0[]{'1', '2', '\0'};     // OKだが、非推奨
    char c_str1[] = {'1', '2', '\0'};  // NG 代入演算子による一様初期化
    char c_str2[] = {"12"};            // NG 代入演算子による一様初期化
    char c_str3[]{"12"};               // OK
    char c_str4[] = "12";              // OK
```

* 宣言時にポインタ変数の初期値が決まらない場合、nullptrで初期化する(「[リテラル](core_lang_spec.md#SS_19_2)」参照)。

```cpp
    //  example/programming_convention/type_ut.cpp 720

    int32_t*       ptr1 = nullptr;  // OK
    int32_t*       ptr2{nullptr};   // OK
    char const*    pchar0 = 0;      // NG
    char*          pchar1 = NULL;   // NG
    int32_t const* ptr0(nullptr);   // NG {}か=で初期化する
```

* 初期化順序が不定になるため、
  別のコンパイル単位で定義された静的なオブジェクトに依存した静的オブジェクトの初期化を行わない
  (同じファイルの上方にある静的なオブジェクトや、
  [Singleton](design_pattern.md#SS_9_1_1)に依存した初期化を行うことには問題はない)。
* コンパイル時に値が確定する「基本型」や「コンストラクタがconstexprであるクラス」のインスタンスは、
  constexpr(「[const/constexprインスタンス](programming_convention.md#SS_3_1_9)」参照)と宣言する。

```cpp
    //  example/programming_convention/type_ut.cpp 732

    constexpr int32_t f_constexpr(int32_t a) noexcept { return a * 3; }
    int32_t           f_normal(int32_t a) noexcept { return a * 3; }
```
```cpp
    //  example/programming_convention/type_ut.cpp 740

    constexpr auto a = f_constexpr(3);  // OK
    auto const     b = f_constexpr(3);  // NG constexprにできる
    // constexpr auto c = f_normal(3);  // NG コンパイルエラー
    auto const d = f_normal(3);  // OK

```

* constなオブジェクトが複雑な初期化を必要とする場合、その初期化にはラムダ式を使用する。

```cpp
    //  example/programming_convention/type_ut.cpp 753

    int32_t len{10};  // ここではlenは固定だが、関数引数等で外部から与えられるとする

    auto vc0 = std::vector<int32_t>(len);  // vc0が初期化以外で変更されないのであれば、NG
    std::iota(vc0.begin(), vc0.end(), 1);  // vc0の初期化

    auto const vc1 = [len]() {  // OK vc1の初期化
        std::vector<int32_t> ret(len);
        std::iota(ret.begin(), ret.end(), 1);
        return ret;
    }();  // ラムダ式の生成と呼び出し
```


* [演習-インスタンスの初期化](exercise_q.md#SS_22_1_15)
* [演習-vector初期化](exercise_q.md#SS_22_1_14)
* [演習-ポインタの初期化](exercise_q.md#SS_22_1_13)


### rvalue <a id="SS_3_1_13"></a>
* 関数の仮引数以外のリファレンスで[rvalue](core_lang_spec.md#SS_19_7_1_2)をバインドしない
  (「[オブジェクトのライフタイム](programming_convention.md#SS_3_2_7_3)」参照)。
* rvalueの内部ハンドルを使用しない(「[std::string_viewの使用制限](programming_convention.md#SS_3_10_1_4)」参照)。

```cpp
    //  example/programming_convention/type_ut.cpp 787

    char const* str = std::string{"str"}.c_str();
    // strが指すポインタはこの行では解放済

    ASSERT_STREQ(str, "str");  //    strは無効なポインタを保持であるため、未定義動作
```

* 非constなリファレンスでrvalueをバインドしない。


## クラスとオブジェクト <a id="SS_3_2"></a>
### ファイルの使用方法 <a id="SS_3_2_1"></a>
* 下記の例外を除き、一つのクラスはそれを宣言、定義する1つのヘッダファイルと、
  一つの.cppファイルによって構成する。
    * ファイル外部から使用されないクラスは、一つの.cppファイルの無名名前空間で宣言、定義する。
    * ファイル外部から使用されるインラインクラス(クラステンプレート等)は、
      一つのヘッダファイルで宣言、定義する。
    * 「一つのヘッダファイル(a.h)と、一つの.cpp(a.cpp)で構成されたクラスA」のみをサポートするクラス
      (Aのインターフェースや実装専用に定義されたクラス(「[Pimpl](cpp_idioms.md#SS_21_2_1)」参照))は、
      a.h、a.cppで宣言、定義する。

### クラスの規模 <a id="SS_3_2_2"></a>
#### 行数 <a id="SS_3_2_2_1"></a>
* それ以外に方法がない場合を除き、ヘッダファイル内のクラスの定義、
  宣言はコメントを含め200行程度に収める。
* クラス内定義関数が大きくなると下記のような問題が発生しやすくなるため、
  10行を超える関数はクラス内で定義しない。
    * 関数のインポートする外部シンボルが多くなり、
      このクラスを使用する別のクラスに不要な依存関係を作ってしまう
      (「[インターフェース分離の原則(ISP)](solid.md#SS_8_4)」参照)。
    * クラスの定義が間延びして、クラスの全体構造を把握することが困難になる。

#### メンバの数 <a id="SS_3_2_2_2"></a>
* それ以外に方法がない場合を除き、publicメンバ関数の数は、最大7個程度に収める
  (ただし、オーバーロードにより同じ名前を持つ関数群は、全部で1個とカウントする)。
* オブジェクトの状態を保持するメンバ変数の数は、最大4個程度に留める。
  constやconstexprメンバ・インスタンスは定数(状態を保持するメンバ変数ではない)であるため、
  この数に含めない。

#### 凝集性 <a id="SS_3_2_2_3"></a>
* 単なるデータホルダー(アプリケーションの設定データを保持するようなクラス等)や、
  ほとんどの振る舞いを他のクラスに委譲するようなクラスを除き、
  [凝集性](cpp_idioms.md#SS_21_14_14)が高くなるように設計する。
* [クラス凝集性のクライテリア](cpp_idioms.md#SS_21_7_3)に従い、凝集性を判断し、凝集性が著しく低いクラスを作らないようにする。

* [演習-凝集性の意味](exercise_q.md#SS_22_2_1)
* [演習-凝集性の向上](exercise_q.md#SS_22_2_2)


### アクセスレベルと隠蔽化 <a id="SS_3_2_3"></a>
* アクセスレベルは、特別な理由がない限り、上からpublic、protected、privateの順番で明示する。

```cpp
    //  example/programming_convention/class_ut.cpp 12

    class A {
        void f0();  // NG デフォルト private を使用しない。
    public:
        void f1();  // OK
    private:
        void f2();  // OK
    protected:
        void f3();  // NG privateの前に定義すべき。
    };
```

* 全てのメンバ変数はprivateにする。
    * メンバ変数にアクセスしたい場合は、Accessorメンバ関数を経由させる
      (「[Accessor](cpp_idioms.md#SS_21_1_6)」参照)。その場合でもsetterは控えめに使用する。
    * 派生クラスから基底クラスの変数の値が必要になる場合は、protectedなAccessorを定義する。
    * 単体テスト用クラスでは、protectedメンバ変数を定義してよい。
* アクセスレベルによるカプセル化が破壊されるため、
  メンバ変数のハンドル(リファレンスやポインタ)を返さない。
  それが避けがたい場合においては、constハンドルを返す。

```cpp
    //  example/programming_convention/class_ut.cpp 28

    class B {
    public:
        // ...

        void* f0() noexcept  // NG メンバ変数が保持するポインタを返している
        {
            return v_ptr_;
        }

        std::string* f1() noexcept  // NG メンバ変数へのポインタを返している
        {
            return &str_;
        }

        std::string& f2() noexcept  // NG メンバ変数へのリファレンスを返している
        {
            return str_;
        }

        std::string f3() const noexcept  // OK ただし、パフォーマンスに注意
        {
            return str_;
        }

        std::string const& f4() const noexcept  // OK
        {
            return str_;
        }

    private:
        void*       v_ptr_ = nullptr;
        std::string str_{};
    };
```

* 以下のような場合を除き、friendを使用しない。
    * 単体テスト用クラス
    * 二項演算子をオーバーロードした関数

```cpp
    //  example/programming_convention/class_ut.cpp 68

    class Integer {
    public:
        Integer(int32_t integer) noexcept : integer_{integer} {}

        // メンバ関数に見えるが、非メンバ関数
        friend bool operator==(Integer lhs, Integer rhs) noexcept  // OK
        {
            return lhs.integer_ == rhs.integer_;
        }

    private:
        int32_t const integer_;
    };

    bool operator!=(Integer lhs, Integer rhs) noexcept { return !(lhs == rhs); }
```

* [NVI(non virtual interface)](cpp_idioms.md#SS_21_1_8)に従う。従って、
  virtualな関数はprivateかprotectedと宣言し、それをpublicな非仮想メンバ関数から呼び出す。

```cpp
    //  example/programming_convention/class_ut.cpp 86

    class Widget {
    public:
        virtual int32_t DoSomething() noexcept  // NG virtualでpublic
        {
            // ...
        }

        int32_t DoSomething(bool b) noexcept  // OK non-virtualでpublic
        {
            return do_something(b);
        }
        // ...
    private:
        virtual int32_t do_something(bool b) noexcept  // OK virtualでprivate
        {
            // ...
        }
        // ...
    };
```

### メンバ関数 <a id="SS_3_2_4"></a>
* 可能な場合(メンバに直接アクセスしない場合)、メンバ関数をstaticにする。
* コンパイル時に戻り値が確定するメンバ関数は[constexpr関数](core_lang_spec.md#SS_19_5_3)と宣言する。
* オブジェクトの状態を変えないメンバ関数は、constと宣言する。
    * getter(下記の例ではGetString)はconstと宣言する。
    * 下記のSetPtrのような関数はconstにしない。

```cpp
    //  example/programming_convention/member_func_ut.cpp 21

    class A {
    public:
        A() : s_ptr_{std::make_unique<std::string>("haha")}, s_inst_{"hihi"} {}

        std::string const& GetString() const noexcept  // OK 必ずconst
        {
            return s_inst_;
        }

        // SetPtrと、SetInstは実質的には同じことを行っている。
        // SetInstはconstと宣言できない(コンパイルエラー)。
        // 従ってSetPtrもconstと宣言してはならない。
        // なお、この問題はstd::experimental::propagate_constを使用することで解決できるが、
        // 名前空間からわかるように、このライブラリが将来にわたって有効かどうかは不明である。
        void SetPtr(std::string_view name) const  // NG このconstはつけてはならない。
        {
            *s_ptr_ = name;
        }

        void SetInst(std::string_view name)  // OK
        {
            s_inst_ = name;
        }

    private:
        std::unique_ptr<std::string> s_ptr_;
        std::string                  s_inst_;
    };

    void f()
    {
        A const a;

        a.SetPtr("0");  // constオブジェクトaを変更できてしまう。
    //  a.SetInst("1"); // constオブジェクトaを変更しようとしたため、
                        // 正しく(constの目的通り)コンパイルエラー。
    }
```

* クラス内部のハンドル（ポインタやリファレンス）を戻り値に使用しない。
    * それが避けがたい場合は、戻り値のハンドルをconstにする。
    * ハンドルがconstにできない場合(関数が非constなハンドルを返す場合)、
      そのハンドル経由でクラスの状態を変更できるため、その関数をconstにしない。

```cpp
    //  example/programming_convention/member_func_ut.cpp 64

    class B {
    public:
        B() noexcept {}

        // GetStringsは、避けがたい理由で、strings_のリファレンスを返さざるを得ないとする。
        // この場合、GetStringsはconstにしてはならない。
        std::vector<std::string>& GetStrings() noexcept { return strings_; }

    private:
        std::vector<std::string> strings_{};
    };
```

* 非静的メンバの[ハンドル](cpp_idioms.md#SS_21_14_8)を返すメンバ関数を持つオブジェクトが
  [rvalue](core_lang_spec.md#SS_19_7_1_2)である場合、
  そのオブジェクトからその関数を呼び出した戻り値(メンバへのハンドル)を変数で保持しない
  (そのハンドルは[danglingリファレンス](cpp_idioms.md#SS_21_13_2)/[danglingポインタ](cpp_idioms.md#SS_21_13_3)になっている)。
  そういった使用方法が必要ならばlvalue修飾、[rvalue修飾](core_lang_spec.md#SS_19_8_7_1)を用いたオーバーロード関数を定義する。

```cpp
    //  example/programming_convention/member_func_ut.cpp 84

    char const* s = std::string{"hehe"}.c_str();  // std::string{"hehe"}はrvalue

    std::cout << s << std::endl;  // この時点ではsは解放されている。
```

* [演習-メンバ関数の修飾](exercise_q.md#SS_22_3_2)

#### 特殊メンバ関数 <a id="SS_3_2_4_1"></a>
* [特殊メンバ関数](core_lang_spec.md#SS_19_6_1)
    * デフォルトコンストラクタ
    * copyコンストラクタ
    * copy代入演算子(operator =)
    * moveコンストラクタ
    * move代入演算子
    * デストラクタ

  について、デフォルトコンストラクタ以外を定義する場合、
  その他の関数には以下のいずれかを選択する(不要な代入演算子を= deleteすることは特に重要である)。

|コンパイラ生成関数を |定義方法                      |
|:-------------------:|------------------------------|
|使用する             | = default                    |
|使用しない           | = delete、もしくは自分で実装 |

* クラスを宣言、定義する場合、下記のClassStationery(クラスのひな形)を参考にし、
  不要なコンパイラ生成関数が作られないようにする。

```cpp
    //  example/programming_convention/class_ut.cpp 454

    /// @brief クラスのひな形。クラスを定義、宣言するときには、このクラスの下記6関数を適切に
    ///        定義、宣言すること。
    class ClassStationery final {
    public:
        ClassStationery()  = delete;
        ~ClassStationery() = delete;

        ClassStationery(ClassStationery const&)                = delete;
        ClassStationery& operator=(ClassStationery const&)     = delete;
        ClassStationery(ClassStationery&&) noexcept            = delete;
        ClassStationery& operator=(ClassStationery&&) noexcept = delete;
    };
```

* リソース管理等の都合からコンパイラが生成するデストラクタでは機能が不十分な場合、
  プログラマがそのクラスのデストラクタを定義する。
  この場合、コンパイラが生成するcopyコンストラクタ、copy代入演算子、moveコンストラクタ、
  move代入演算子では機能が不十分であることが予測されるため、
  これらを使用しない(「[Copy-And-Swap](cpp_idioms.md#SS_21_1_4)」参照)。

* [演習-特殊メンバ関数の削除](exercise_q.md#SS_22_3_3)

#### コンストラクタ <a id="SS_3_2_4_2"></a>
* クラスが複数の初期化方法を提供する場合でも、
  デフォルト引数を使用し、できる限りコンストラクタを一つに集約する。
* 一つのコンストラクタに集約できない場合、[委譲コンストラクタ](core_lang_spec.md#SS_19_6_1_3)等により処理の重複を防ぐ。
  [非静的なメンバ変数](programming_convention.md#SS_3_2_5_2)処理の重複を避けることは特に重要である。
* オブジェクトの初期化が完了するまでは派生クラスの仮想関数呼び出し等の
  [RTTI](programming_convention.md#SS_3_5_9)機能を使うことはできないため(「[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)」参照)、
  コンストラクタの中でRTTI機能を使わない(デストラクタでも同様)。
  以下のコードはコンストラクタ内で仮想関数呼び出しを行ったため、想定通りの動作にならない例である。

```cpp
    //  example/programming_convention/member_func_ut.cpp 97

    class Base {
    public:
        Base(std::ostream& os) : os_{os} { os_ << Name() << "::" << __func__ << " -> "; }

        virtual ~Base() { os_ << Name() << "::" << __func__; }

        virtual std::string_view Name() const { return "Base"; }

    protected:
        std::ostream& os_;  // protectedなメンバ変数を定義すべきではないが、コードの動作例示のため
    };

    class Derived : public Base {
    public:
        Derived(std::ostream& os) : Base{os} { os_ << Name() << "::" << __func__ << " -> "; }

        virtual ~Derived() { os_ << Name() << "::" << __func__ << " -> "; }

        virtual std::string_view Name() const override { return "Derived"; }
    };
```
```cpp
    //  example/programming_convention/member_func_ut.cpp 124

    auto oss = std::ostringstream{};

    {
        auto d = Derived{oss};
    }

    ASSERT_EQ("Base::Base -> Derived::Derived -> Derived::~Derived -> Base::~Base", oss.str());
    // つまり、
    // * Base::Base()でのName()の呼び出しは、Derived::Name()ではなくBase::Name()が呼ばれる。
    // * Base::~Base()でのName()の呼び出しは、Derived::Name()ではなくDerived::Name()が呼ばれる。
    // * Derived::~Derived()でのName()の呼び出しは、Derived::Name()ではなくDerived::Name()が呼ばれる。
    // * Base::~Base()でのName()の呼び出しは、Derived::Name()ではなくBase::Name()が呼ばれる。
```

* コンストラクタからのエクセプションを発生をできるだけ避ける([エクセプション処理](programming_convention.md#SS_3_3_9))。
* コンストラクタのボディの使用してのメンバ変数の初期化はバグにつながりやすいため、
  この方法を避ける(「[非静的なメンバ変数](programming_convention.md#SS_3_2_5_2)」参照)。
* クラスが解放責務を持つポインタ型メンバ変数を持つならば、copyコンストラクタ、
  copy代入演算子に対して以下のいずれかを行い、[シャローコピー](cpp_idioms.md#SS_21_12_1)が行われないようにする
  (このルールはファイルディスクリプタ等のリソース管理をするクラス全般に当てはまる)。
    * [ディープコピー](cpp_idioms.md#SS_21_12_2)をさせる。
    * = deleteする(「[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)」参照)。

  またこの場合、moveコンストラクタ、move代入演算子の定義を検討する(「[Copy-And-Swap](cpp_idioms.md#SS_21_1_4)」参照)。

* 非explicitなコンストラクタによる[暗黙の型変換](core_lang_spec.md#SS_19_6_2_2)
  が不要なクラスのコンストラクタに関しては、下記の目的のためにexplicitと宣言する。

    * 仮引数一つのコンストラクタに関しては、[暗黙の型変換抑止](core_lang_spec.md#SS_19_6_2_3)する。
    * 仮引数二つ以上のコンストラクタに関しては、
      代入演算子での[一様初期化](core_lang_spec.md#SS_19_6_6)ができないようにする。  

```cpp
    //  example/programming_convention/member_func_ut.cpp 147

    class A0 {
    public:
        // NG int32_tからA0への暗黙の型変換が起こる。
        A0(int32_t a) noexcept : a_{a} {}
        // ...
    };

    class A1 {
    public:
        // OK int32_tからA1への暗黙の型変換をさせない。
        explicit A1(int32_t a) noexcept : a_{a} {}
        // ...
    };

    class A2 {
    public:
        // NG 代入演算子でのリスト初期化ができてしまう。
        A2(int32_t a, int32_t* b) noexcept : a_{a}, b_{b} {}
        // ...
    };

    class A3 {
    public:
        // OK 代入演算子でのリスト初期化をさせない。
        explicit A3(int32_t a, int32_t* b) noexcept : a_{a}, b_{b} {}
        // ...
    };

    void f_A0(A0) noexcept {}
    void f_A1(A1) noexcept {}
    void f_A2(A2) noexcept {}
    void f_A3(A3) noexcept {}
```
```cpp
    //  example/programming_convention/member_func_ut.cpp 200

    A0 a0 = 1;           // NG 1からA0への暗黙の型変換。
                         //    このような変換はセマンティクス的不整合につながる場合がある
    // A1 a1 = 1;        // OK explicitの効果で、意図通りコンパイルエラー

    f_A0(1);             // NG 1からA0への暗黙の型変換のためf_A0が呼び出せてしまう
    // f_A1(1);          // OK explicitの効果で、意図通り以下のようなコンパイルエラー
                         //    error: could not convert ‘1’ from ‘int’ to ‘A1’
    f_A1(A1{1});         // OK f_A1の呼び出し

    auto i = 3;
    A2  a2 = {i, &i};    // NG 代入演算子でのリスト初期化をしている

    // A3 a3 = { i, &i };// OK explicitの効果で、意図通りコンパイルエラー
    A3 a3{i, &i};        // OK リスト初期化
    auto a4 = A3{i, &i}; // OK AAA

    f_A2({i, &i});       // NG { i, &i }からA2への暗黙の型変換のためf_A2が呼び出せてしまう
    // f_A3({i, &i});    // OK explicitの効果で、意図通り以下のようなコンパイルエラー
                         //    error: converting to A3 from initializer list would use explicit 
                         //           constructor A3::A3(int32_t, int32_t*)’
    f_A3(A3{i, &i});     // OK f_A3の呼び出し
```

* 派生クラスが基底クラスの全コンストラクタを必要とする場合、
  [継承コンストラクタ](core_lang_spec.md#SS_19_6_1_2)を使用する。

* デフォルト引数はインターフェース関数の呼び出しを簡略化する目的で使用するべきであるため、
  private関数にデフォルト引数を持たせない。

* [演習-委譲コンストラクタ](exercise_q.md#SS_22_3_4)

#### copyコンストラクタ、copy代入演算子 <a id="SS_3_2_4_3"></a>
* copyコンストラクタ、copy代入演算子は[copyセマンティクス](cpp_idioms.md#SS_21_5_2)に従わせる。
* copyコンストラクタ、copy代入演算子の引数はconstリファレンスにする。
* [RVO(Return Value Optimization)](core_lang_spec.md#SS_19_15_1)により、
  copyコンストラクタの呼び出しは省略されることがあるため、
  copyコンストラクタ、copy代入演算子はコピー以外のことをしない。
* copy代入演算子は[lvalue修飾](core_lang_spec.md#SS_19_8_7_2)をする。

```cpp
    //  example/programming_convention/member_func_ut.cpp 233

    class Widget {
    public:
        Widget& operator=(Widget const& rhs)  // NG lvalue修飾無し
        {
            // 何らかの処理
            return *this;
        }

        Widget& operator=(Widget&& rhs) noexcept  // NG lvalue修飾無し
        {
            // 何らかの処理
            return *this;
        }
        // ...
    };
```
```cpp
    //  example/programming_convention/member_func_ut.cpp 262

    Widget w0{1};
    Widget w1{2};

    w0 = w1;         // これには問題ない
    w1 = Widget{3};  // これにも問題ない

    Widget{2} = w0;         // NG lvalue修飾無しのcopy代入演算子であるため、コンパイルできる
    Widget{3} = Widget{4};  // NG lvalue修飾無しのmove代入演算子であるため、コンパイルできる
```
```cpp
    //  example/programming_convention/member_func_ut.cpp 281

    class Widget {  // 上記の修正
    public:
        Widget& operator=(Widget const& rhs) &  // OK lvalue修飾
        {
            // 何らかの処理
            return *this;
        }

        Widget& operator=(Widget&& rhs) & noexcept  // OK lvalue修飾
        {
            // 何らかの処理
            return *this;
        }
        // ...
    };
```
```cpp
    //  example/programming_convention/member_func_ut.cpp 310

    Widget w0{1};
    Widget w1{2};

    // Widget{2} = w0;          lvalue修飾の効果でコンパイルエラー
    // Widget{3} = Widget{4};   lvalue修飾の効果でコンパイルエラー
```

* [演習-copyコンストラクタ](exercise_q.md#SS_22_3_5)

#### moveコンストラクタ、move代入演算子 <a id="SS_3_2_4_4"></a>
* moveコンストラクタ、move代入演算子は[moveセマンティクス](cpp_idioms.md#SS_21_5_3)に従わせる。
* moveコンストラクタ、move代入演算子はnoexceptをつけて宣言し、エクセプションを発生させない。
  noexceptでないmoveコンストラクタ、
  move代入演算子を持つクラスを標準ライブラリのコンテナのtemplate引数として使用した場合、
  moveの代わりにcopyが使用され、パフォーマンス問題を引き起こす場合がある。
* move代入演算子はlvalue修飾(「[copyコンストラクタ、copy代入演算子](programming_convention.md#SS_3_2_4_3)」参照)をする。


* [演習-moveコンストラクタ](exercise_q.md#SS_22_3_6)  

#### 初期化子リストコンストラクタ <a id="SS_3_2_4_5"></a>
* [初期化子リストコンストラクタ](core_lang_spec.md#SS_19_6_1_1)は、コンテナクラスの初期化のためのみに定義する。
* 初期化子リストコンストラクタと同じ仮引数を取り得るコンストラクタを定義しない。

#### デストラクタ <a id="SS_3_2_4_6"></a>
* デストラクタの中で[RTTI](programming_convention.md#SS_3_5_9)機能を使わない(「[コンストラクタ](programming_convention.md#SS_3_2_4_2)」参照)。
* デストラクタはnoexceptであり、throwするとプログラムが終了するため、デストラクタでthrowしない。

#### オーバーライド <a id="SS_3_2_4_7"></a>
* [オーバーライドとオーバーロードの違い](cpp_idioms.md#SS_21_13_1)に注意する。
* オーバーライドしたメンバ関数には、オーバーライドされたメンバ関数の機能の意味を踏襲させる。
* オーバーライドする/される一連の仮想関数(デストラクタを含む)について、
    * 全ての宣言にはvirtualを付ける。
    * 一連の仮想関数の最初でも最後でもないものの宣言には、overrideを付ける。
    * 一連の仮想関数の最後のものの宣言には、overrideを付けず、finalを付ける。

```cpp
    //  example/programming_convention/member_func_ut.cpp 327

    class Base {
    public:
        virtual ~Base();                   // OK
        virtual void f(int32_t) noexcept;  // OK
        virtual void g() noexcept;         // OK
    };

    // Derived_0::fは、Base::fのオーバーライドのつもりであったが、タイポのため新たな関数の宣言、
    // 定義になってしまった。この手のミスは、自分で気づくのは難しい
    class Derived_0 : public Base {
    public:
        virtual ~Derived_0();                // NG overrideが必要
        void f(uint32_t) noexcept;           // NG Derived_0:fはBase:fのオーバーライドではない
                                             //    virtualとoverrideやfinalがない
        virtual void g() noexcept override;  // OK
    };

    class Derived_1 : public Base {
    public:
        // NG 下記が必要
        // virtual ~Derived_1() override;

        virtual void f(uint32_t) override;  // OK overrideと書いたことで、
                                            //    コンパイルエラーになりタイポに気づく
        virtual void f(uint32_t) final;     // OK finalと書いたことで、
                                            //    コンパイルエラーになりタイポに気づく
    };

    class Derived_2 : public Base {
    public:
        virtual ~Derived_2() override;                    // OK Derived_2はfinalではない
        virtual void f(int32_t) noexcept override final;  // NG overrideは不要
        virtual void g() noexcept final;                  // OK これ以上オーバーライドしない
    };
```

* オーバーライド元の関数とそのオーバーライド関数のデフォルト引数の値は一致させる。
  オーバーライド元の関数にデフォルト引数を持たせないのであれば、
  そのオーバーライド関数にもデフォルト引数を持たせない。

```cpp
    //  example/programming_convention/member_func_ut.cpp 372

    class Base {
    public:
        virtual int32_t GetArg(int32_t a = 0) const noexcept { return a; }
        // ...
    };

    class Derived : public Base {
    public:
        // NG Base::GetArgのデフォルト引数と違う
        virtual int32_t GetArg(int32_t a = 1) const noexcept override { return a; }

        // ...
    };
```

```cpp
    //  example/programming_convention/member_func_ut.cpp 396

    auto  d = Derived{};
    Base& b{d};

    // 同じオブジェクトであるにもかかわらず、その表層型でデフォルト引数の値が変わってしまう。
    ASSERT_EQ(0, b.GetArg());
    ASSERT_EQ(1, d.GetArg());
```

* privateやprotectedなオーバーライド関数にはデフォルト引数を持たさない
  (「[実引数/仮引数](programming_convention.md#SS_3_3_4)」参照)。
  さらに[NVI(non virtual interface)](cpp_idioms.md#SS_21_1_8)にも従うことにより、
  上の条項の示した一連のオーバーライド関数のデフォルト引数の一致について考慮の必要がなくなり、
  且つこのクラスのユーザはデフォルト引数が使用できるようになる。

* [演習-オーバーライド関数の修飾](exercise_q.md#SS_22_3_8)  


### メンバ変数 <a id="SS_3_2_5"></a>
#### メンバ変数の数  <a id="SS_3_2_5_1"></a>
* constexprでなく、publicやprotectedなメンバ変数を宣言しない。
* クラスの可変な状態を表すメンバ変数(non-const, non-static)は4個以内に留める(「[クラス凝集性のクライテリア](cpp_idioms.md#SS_21_7_3)」参考)。

#### 非静的なメンバ変数 <a id="SS_3_2_5_2"></a>
* すべての非静的なメンバ変数は、コンストラクタ終了時までに明示的に初期化する。
* 多くのコンパイラや静的解析ツールはインスペクタは、
  [NSDMI](core_lang_spec.md#SS_19_6_7_1)、[初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)による初期化の漏れについては容易に発見、
  指摘できることが多い。
* constメンバ変数は、[NSDMI](core_lang_spec.md#SS_19_6_7_1)、
  [初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)でなければ初期化できないため、それ以外に方法がない場合を除き、
  [コンストラクタ内での非静的なメンバ変数の初期値の代入](core_lang_spec.md#SS_19_6_7_3)の使用を避ける。
* 非静的なメンバ変数はクラス内で定義された順序に従い初期化されるため、
  [初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)の順序を定義順序と同じにすることで可読性を向上させる。
* クラスがただ一つのコンストラクタを持つ場合、
  [NSDMI](core_lang_spec.md#SS_19_6_7_1)と[初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)を混在させない。
  従って、[初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)を必要とするメンバ変数が一つでもある場合は、
  すべての変数の初期化を[初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)で行う。

```cpp
    //  example/programming_convention/class_ut.cpp 259

    class A1 {
    public:
        A1() noexcept {}  // OK NSDMIに統一

    private:
        int32_t const a_{1};  // OK NSDMIによる初期化。
                              //    ただし、static constexprにすべき。
        int32_t b_[2]{0, 1};  // OK NSDMIによる初期化
        int32_t c_{5};        // OK NSDMIによる初期化
    };

    class A2 {
    public:
        explicit A2(int a) noexcept   // OK 初期化子リストに統一
            : a_{a}, b_{0, 1}, c_{5}  // OK 初期化子リストによる初期化
        {
        }

    private:
        int32_t const a_;
        int32_t       b_[2];
        int32_t       c_;
    };

    class A3 {
    public:
        explicit A3(int a) noexcept : a_{a}  // NG 初期化方法の混在
        {
            c_ = 5;  // NG NSDMIか初期化子リストを使用するべき
        }

    private:
        int32_t const a_;
        int32_t       b_[2]{0, 1};  // NG 初期化方法の混在
        int32_t       c_;
    };
```

* クラスが複数のコンストラクタを持つ場合、
  すべてのメンバ変数に対して[NSDMI](core_lang_spec.md#SS_19_6_7_1)を行い(デフォルト値の設定)、
  デフォルト値とは異なる初期値を持つ変数に対してのみ、
  コンストラクタ毎に[初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)を行う。

```cpp
    //  example/programming_convention/class_ut.cpp 299

    class A4 {
    public:
        A4() noexcept {}  // OK

        A4(int32_t e) noexcept : e_{e} {}  // OK 初期化子リストによるe_の上書き
        // 注) A4()とA4(int32_t)はデフォルト引数を使用すれば統一できるが、
        // 例の単純化のためにあえてそれぞれを定義している。

    private:
        int32_t d_{5};  // OK NSDMIによる初期化
        int32_t e_{0};  // OK NSDMIによる初期化
    };
```

* [演習-メンバ変数の初期化方法の選択](exercise_q.md#SS_22_2_3)
* [演習-メンバの型](exercise_q.md#SS_22_2_4)
* [演習-メンバ変数の初期化](exercise_q.md#SS_22_2_5)

#### 静的なメンバ変数/定数の初期化 <a id="SS_3_2_5_3"></a>
* 静的な(且つconstexprでない)メンバ変数は、ヘッダファイルで宣言し、.cppで定義、初期化する。
* クラス宣言内で初期化される基本型のstatic constメンバ定数を定義しない。
  代わりに、static constexprメンバ定数として定義、初期化する
  (クラス宣言外で初期化されるメンバ定数はstatic constにする)。
* privateなstatic constexprメンバ定数は、
  そのクラスが宣言されているヘッダファイル内で依存されている場合のみ使用する。
* privateなstatic constexprメンバ定数がヘッダファイル内で依存されていない場合は、
  .cppの無名名前空間内で定義、初期化する
  (つまり、クラスのメンバとして定義しない。こうすることで不要なコンパイルが防げる)。

```cpp
    //  example/programming_convention/class.h 5

    class StaticConstexprVar {
    public:
        StaticConstexprVar() = default;

        uint32_t MultiplyBy2(uint32_t a) noexcept;
        uint32_t MultiplyBy3(uint32_t a) noexcept { return static_constexpr_var_3 * a; }
        uint32_t MultiplyBy4(uint32_t a) noexcept;

    private:
        static constexpr uint32_t static_constexpr_var_2{2};  // NG クラス内で定義する必要なし
        static constexpr uint32_t static_constexpr_var_3{3};  // OK クラス内で定義する必要あり
    };
```

```cpp
    //  example/programming_convention/class_ut.cpp 319
    //
    uint32_t StaticConstexprVar::MultiplyBy2(uint32_t a) noexcept { return static_constexpr_var_2 * a; }

    namespace {
    constexpr uint32_t static_constexpr_var_4{4};  // OK クラス内で定義する必要なし
    }

    uint32_t StaticConstexprVar::MultiplyBy4(uint32_t a) noexcept { return static_constexpr_var_4 * a; }
```

#### mutableなメンバ変数 <a id="SS_3_2_5_4"></a>
* 排他制御用(std::mutex等)や計算データのキャッシュ用等のメンバ変数を除き、
  メンバ変数をmutableと宣言しない。

```cpp
    //  example/programming_convention/class_ut.cpp 333

    class A {
    public:
        A() = default;

        uint32_t GetValue() const  // OK GetValue()をconstにするためにmutex_はmutable
        {
            auto lock = std::lock_guard{mutex_};  // constでない関数std::mutex::lock()の呼び出し

            return v_;
        }

        void AddValue(uint32_t v) noexcept
        {
            auto lock = std::lock_guard{mutex_};

            v_ += v;
        }

    private:
        mutable std::mutex mutex_;  // OK
        uint32_t           v_{0};
    };
```

### 継承/派生 <a id="SS_3_2_6"></a>
* 派生は最大2回程度までに留める。やむを得ず階層が深くなる場合、
  コードの静的解析等を使用し派生関係を明確にする(「[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)」参照)。
* 実装の継承よりも、包含、委譲を優先的に使用する。やむを得ず実装の継承を行う場合は、
  private継承を使用する。 実装の継承をしたクラスがfinalでないならば、protected継承を使用する
  ([CRTP(curiously recurring template pattern)](cpp_idioms.md#SS_21_1_5)等は例外的に認められる)。

```cpp
    //  example/programming_convention/class_ut.cpp 124

    // private継承。非推奨
    class StringWrapper0 final : private std::string {
    public:
        explicit StringWrapper0(char const* str) : std::string{str} {}

        void AddStr(char const* str) { *this += str; }

        using std::string::c_str;
    };

    // 移譲。こちらを優先する
    class StringWrapper1 final {
    public:
        explicit StringWrapper1(char const* str) : str_{str} {}

        void AddStr(char const* str) { str_ += str; }

        char const* c_str() const noexcept { return str_.c_str(); }

    private:
        std::string str_;
    };
```

* 派生させないクラスは、finalと宣言する。ほとんどのクラスは派生しないはずなので、
  ほとんどのクラスはfinalになる。
* リソースリークの原因になり得るため、非virtualなデストラクタをもつクラスを継承しない。
  ただし、継承したクラスが基底クラスのメンバ変数以外のメンバ変数を持たないならば、継承しても良い。

```cpp
    //  example/programming_convention/class_ut.cpp 149

    class A {  // デストラクタの呼び出しチェック用のクラス
    public:
        A(bool& destructed) noexcept : destructed_{destructed} { destructed_ = false; }
        ~A() { destructed_ = true; }

    private:
        bool& destructed_;
    };

    class BaseNG {  // NG デストラクタが非virtual
    public:
        BaseNG() = default;
    };

    class DerivedNG : public BaseNG {
    public:
        DerivedNG(bool& destructed) : a_{std::make_unique<A>(destructed)} {}

    private:
        std::unique_ptr<A> a_;
    };
```
```cpp
    //  example/programming_convention/class_ut.cpp 183

    auto a_destructed = false;
    {
        std::unique_ptr<DerivedNG> d{std::make_unique<DerivedNG>(a_destructed)};
        ASSERT_FALSE(a_destructed);
    }
    ASSERT_TRUE(a_destructed);  // OK A::~A()が呼ばれたため問題ないが、、、

    {
        a_destructed = false;
        std::unique_ptr<BaseNG> d{std::make_unique<DerivedNG>(a_destructed)};
        ASSERT_FALSE(a_destructed);
    }
    ASSERT_FALSE(a_destructed);  // NG A::~A()が呼ばれないため、メモリリークする
```
```cpp
    //  example/programming_convention/class_ut.cpp 202

    class BaseOK {  // OK デストラクタがvirtual
    public:
        BaseOK()          = default;
        virtual ~BaseOK() = default;
    };

    class DerivedOK : public BaseOK {
    public:
        DerivedOK(bool& destructed) : a_{std::make_unique<A>(destructed)} {}

    private:
        std::unique_ptr<A> a_;
    };
```
```cpp
    //  example/programming_convention/class_ut.cpp 222

    auto a_destructed = false;
    {
        std::unique_ptr<DerivedOK> d{std::make_unique<DerivedOK>(a_destructed)};
        ASSERT_FALSE(a_destructed);
    }
    ASSERT_TRUE(a_destructed);  // OK A::~A()が呼ばれたため問題ない

    {
        a_destructed = false;
        std::unique_ptr<BaseOK> d{std::make_unique<DerivedOK>(a_destructed)};
        ASSERT_FALSE(a_destructed);
    }
    ASSERT_TRUE(a_destructed);  // OK A::~A()が呼ばれたため問題ない
```

#### インターフェースの継承 <a id="SS_3_2_6_1"></a>
* クラス間に「Is-a」の関係が成り立つときに限りpublic継承を行う。
    * public継承を行う場合、[リスコフの置換原則(LSP)](solid.md#SS_8_3)を守る。
    * インターフェースを継承しない場合、public継承をしない。
* C#やJavaのinterfaceが必要ならば(インタフェースと実装の完全分離をしたい場合等)、
  pure-virtualなメンバ関数のみを宣言したクラス
  (もしくはそのクラスに[NVI(non virtual interface)](cpp_idioms.md#SS_21_1_8)を適用したクラス)
  を定義する。

#### 多重継承 <a id="SS_3_2_6_2"></a>
* 多重継承が不可避でない限り、多重継承は使用しない。
    * 多重継承が必要な場合、その継承の基底クラスは1つを除き、
      他の基底クラスは[インターフェースクラス](core_lang_spec.md#SS_19_4_11)にしなければならない。
* 多重継承を使用する場合、複数個の基底クラスのうち、一つを除きメンバ変数を持ってはならない。
* 多重継承を使用する場合、継承階層内に同じ基底クラスが複数回出てきてはならない
  ([ダイヤモンド継承](core_lang_spec.md#SS_19_12_10)をしない)。
* やむを得ずダイヤモンド継承をせざるを得ない場合、
  継承階層内に複数回出現する基底クラスにはvirtual継承を行う。
* virtual継承を行ったクラスのコンストラクタからは、
  virtual基底クラスのコンストラクタを呼び出すようにする
  (こうしないとvirtual基底クラスは初期化されない)。

### オブジェクト <a id="SS_3_2_7"></a>
#### スライシング <a id="SS_3_2_7_1"></a>
* オブジェクトの[スライシング](cpp_idioms.md#SS_21_12_3)には以下のいずれかで対処する。
    * [Clone(仮想コンストラクタ)](design_pattern.md#SS_9_1_3)を使用する。
    * copy代入演算子を= deleteする。

* [スライシング](cpp_idioms.md#SS_21_12_3)と類似の問題が起こるため、
  オブジェクトの配列をそのオブジェクトの基底クラスへのポインタに代入しない。

* [演習-スライシング](exercise_q.md#SS_22_2_6)

#### オブジェクトの所有権 <a id="SS_3_2_7_2"></a>
* オブジェクトaの所有権
  (「[オブジェクトの所有権](cpp_idioms.md#SS_21_4)」参照)を持つオブジェクトもしくは関数は、
  オブジェクトaの解放責務を持つ。
* オブジェクトaの所有権を持たないオブジェクトは、
  オブジェクトaの[ハンドル](cpp_idioms.md#SS_21_14_8)をメンバ変数で保持することを出来る限り避ける
  ([Observer](design_pattern.md#SS_9_2_4)パターン等、このルール順守が困難な場合は多い)。
* クラスAのオブジェクトaが、オブジェクトbにダイナミックに生成されたとすると、  
    * オブジェクトaのポインタは`std::unique_ptr<A>`(「[RAII(scoped guard)](cpp_idioms.md#SS_21_1_3)」参照)で保持する。
    * オブジェクトa(正確にはオブジェクトaを管理する`std::unique_ptr<A>`オブジェクト)の所有権は、
      オブジェクトbが保持する。
    * オブジェクトbはオブジェクトaの解放責務を持つ(`std::unique_ptr<A>`による自動解放)。
    * オブジェクトaの所有権を保持していないオブジェクトは、オブジェクトaを解放してはならない。
    * オブジェクトaの所有権を別のオブジェクトxへ移動させる場合、
      `std::unique_ptr<A>`とstd::move()を使用する(「[オブジェクトの排他所有](cpp_idioms.md#SS_21_4_1)」参照)。
    * このようなaに複数の所有者b0、b1が存在する場合、`std::shared_ptr<A>`を使用してaを管理する。
      従って、b0、
      b1は`std::shared_ptr<A>`型のメンバを持つことになる(「[オブジェクトの共有所有](cpp_idioms.md#SS_21_4_2)」参照)。
    * オブジェクトbが`std::shared_ptr<A>`でオブジェクトaを、
      オブジェクトaが`std::shared_ptr<B>`でオブジェクトbを所有する場合、
      [オブジェクトの循環所有](cpp_idioms.md#SS_21_4_3)よるメモリリークが発生するため、
      [std::weak_ptr](stdlib_and_concepts.md#SS_20_6_3)を適切に使用する。

* [演習-オブジェクトの所有権](exercise_q.md#SS_22_2_7)

#### オブジェクトのライフタイム <a id="SS_3_2_7_3"></a>
* [オブジェクトのライフタイム](core_lang_spec.md#SS_19_6_8)開始前、
  もしくは終了後のオブジェクトにアクセスしない。

```cpp
    //  example/programming_convention/class_ut.cpp 387

    // 初期化前にオブジェクトにアクセスしてしまう例
    B& getB() noexcept;

    // bが初期される前に(ライフタイム開始前)に、a.A::A()が呼び出される。
    // a.A::A()が呼び出される前に、getB()が呼び出される。
    // 従って、bが初期化される前にgetB()が未初期化のbのリファレンスを返してしまう。
    A a{getB()};

    B  b;
    B& getB() noexcept { return b; }
```

* オブジェクトaが所有権を持たないオブジェクトbへのハンドルをa自体のメンバ変数で保持する場合、
  オブジェクトbのライフタイムが終了する前に、
  オブジェクトaがオブジェクトbにアクセスできないようにする(Observerパターンのdetachメンバ関数等)。

```cpp
    //  example/programming_convention/class_ut.cpp 403

    // ライフタイムが終了したオブジェクトにアクセスしてしまう例
    auto a = A{};
    {
        auto b = B{};
        a.SetB(&b);  // NG aのメンバ変数へ&bを代入。
    }                //    この行でbのライフタイム終了。

    a.DoSomething();  // NG bのポインタを使用して何かすると不定動作。
```

* スタック上のオブジェクトのハンドルをその関数外部へ開示しない
  (そのハンドルは、ライフタイムが終了したオブジェクトを指している)。
* thread_localオブジェクトは、ログやデバッグ用途のみで使用する。
* [rvalue](core_lang_spec.md#SS_19_7_1_2)はライフタイム終了間際のオブジェクトであるため、
  関数の仮引数以外のリファレンスでrvalueをバインドしない
  (特にリファレンス型のメンバ変数でrvalueをバインドしないことは重要である)。
  rvalueをリファレンス型の引数で受け取る場合はconstリファレンス、
  もしくはrvalueリファレンス(T&&)を使用する(「[rvalue](programming_convention.md#SS_3_1_13)」参照)。

```cpp
    //  example/programming_convention/class_ut.cpp 436

    void f0(E&) noexcept;
    void f1(E const&) noexcept;
    void f2(E &&) noexcept;

    // f0(E{});  NG ほとんどのコンパイラではエラー
    f1(E{});  // OK rvalueはconstリファレンスにバインド可
    f2(E{});  // OK rvalueはrvalueリファレンス

    E const& e0 = E{"4"};  // NG rvalueを引数以外のconstリファレンスに代入
    E&&      e1 = E{"5"};  // NG rvalueを引数以外のrvalueリファレンスに代入
```

* [danglingリファレンス](cpp_idioms.md#SS_21_13_2)、 [danglingポインタ](cpp_idioms.md#SS_21_13_3)に気を付ける。


## 関数 <a id="SS_3_3"></a>
### 関数構造のクライテリア <a id="SS_3_3_1"></a>
* 関数の規模・複雑度に関しては、
    * [サイクロマティック複雑度のクライテリア](cpp_idioms.md#SS_21_6_2)に従う。
* [関数の行数のクライテリア](cpp_idioms.md#SS_21_6_3)に従い、
    * 7 行程度を理想とする。
    * 40行以下に留める。


* [演習-関数分割](exercise_q.md#SS_22_3_7)  

### オーバーロード <a id="SS_3_3_2"></a>
* [オーバーライドとオーバーロードの違い](cpp_idioms.md#SS_21_13_1)に注意する。
* オーバーロードされた関数は実行目的を同じにする。
  異なる目的のためには異なる名前の関数を用意する。
* [オーバーライド](programming_convention.md#SS_3_2_4_7)を除き、基底クラスのメンバ関数と同じ名前を持つメンバ関数を派生クラスで宣言、
  定義しない。
  これに反すると[name-hiding](core_lang_spec.md#SS_19_12_9)のため、基底クラスのメンバ関数の可視範囲を縮小させてしまう。

```cpp
    //  example/programming_convention/func_ut.cpp 17

    // NGな例
    class Base {
    public:
        virtual ~Base() = default;
        void f() noexcept
        {
            // ...
        }
    };

    class DerivedNG : public Base {
    public:
        void f(int32_t a) noexcept  // NG DerivedNG::f(int32_t)がBase::fを隠す(可視範囲の縮小)
        {
            // ...
        }
    };

    void f() noexcept
    {
        auto d = DerivedNG{};

        d.f(0);
    #if 0
        d.f(); // NG DerivedNG::f(int32_t)がBase::fを隠す(可視範囲の縮小)ためコンパイルエラー
    #endif
    }

    // DerivedNGの修正
    class DerivedOK : public Base {
    public:
        void f(int32_t a) noexcept
        {
            // ...
        }
        using Base::f;  // OK Base::fをDerivedOKに導入。
    };

    void g() noexcept
    {
        auto d = DerivedOK{};

        d.f(0);
        d.f();  // OK usingにより、Base::fが見える
    }
```

* 仮引数の型が互いに暗黙に変換できるオーバーロード関数の定義、使用には気を付ける。

```cpp
    //  example/programming_convention/func_ut.cpp 74

    int32_t f(int32_t) { return 0; }
    int32_t f(int16_t) { return 1; }
```
```cpp
    //  example/programming_convention/func_ut.cpp 82

    auto i16 = int16_t{1};

    ASSERT_EQ(1, f(i16));        // f(int16_t)が呼ばれる
    ASSERT_EQ(0, f(i16 + i16));  // f(int32_t)が呼ばれる
```

* 暗黙の型変換による関数の使用範囲の拡張を防ぐには、オーバーロード関数を= deleteする。

```cpp
    //  example/programming_convention/func_ut.cpp 94

    // 実引数がdoubleを認めないパターン
    int32_t f0(double) = delete;
    int32_t f0(int32_t a) noexcept { return a / 2; }

    // 実引数がint32_t以外を認めないパターン
    template <typename T>
    int32_t f1(T) = delete;
    int32_t f1(int32_t a) noexcept { return a / 2; }

    // 実引数がunsigned以外を認めないパターン
    template <typename T, std::enable_if_t<!std::is_unsigned_v<T>>* = nullptr>  // C++17スタイル
    uint64_t f2(T) = delete;

    template <typename T, std::enable_if_t<std::is_unsigned_v<T>>* = nullptr>  // C++17スタイル
    uint64_t f2(T t) noexcept
    {
        uint64_t f2_impl(uint64_t) noexcept;

        // Tがsignedで、tが-1のような値の場合、f2_impl(uint64_t)の呼び出しによる算術変換により、
        // tは巨大な値に変換されるが、
        // Tがunsignedならば、f2_impl(uint64_t)の呼び出しによる算術変換は安全

        return f2_impl(t);
    }

    template <typename T>
    uint64_t f3(T) = delete;

    template <std::unsigned_integral T>  // C++20スタイル
    uint64_t f3(T t) noexcept
    {
        uint64_t ret = t;
        // 何らかの処理

        return ret;
    }
```
```cpp
    //  example/programming_convention/func_ut.cpp 136

    char     c{'c'};
    int8_t   i8{1};
    int32_t  i32{1};
    uint32_t ui32{1};
    uint64_t ui64{1};
    double   d{1.0};

    f0(c);
    f0(i8);
    f0(i32);
    // f0(d);    呼び出そうとしたf0(double)はdeleteされているので意図通りエラー

    f1(i32);
    // f1(u32);  呼び出そうとしたf1<uint32_t>(uint32_t)はdeleteされているので意図通りエラー

    f2(ui32);
    f2(ui64);
    // f2(c);    呼び出そうとしたf2<char>(char)はdeleteされているので意図通りエラー
    // f2(i32);  呼び出そうとしたf2<int32_t>(int32_t)はdeleteされているので意図通りエラー
    // f3(i8);   呼び出そうとしたf3<int8_t>(int8_t)はdeleteされているので意図通りエラー
    f3(ui32);
```

* [演習-オーバーライド/オーバーロード](exercise_q.md#SS_22_3_9)  
* [演習-オーバーロードによる誤用防止](exercise_q.md#SS_22_3_10)  

### 演算子オーバーロード <a id="SS_3_3_3"></a>
* 演算子をオーバーロードする場合、
    * 単項演算子はメンバ関数で定義する。
    * 二項演算子は非メンバ関数で定義する。
* &&, ||, カンマ(,)をオーバーロードしない。
* 型変換オペレータの宣言、定義を多用しない。
* boolへの型変換オペレータは、explicit付きで定義する。

```cpp
    //  example/programming_convention/func_ut.cpp 167

    class A0 {
    public:
        operator bool() const noexcept  // NG intへの型変換が可能
        {
            return state_;
        }

    private:
        bool state_{true};
    };

    class A1 {
    public:
        explicit operator bool() const noexcept  // OK explicitすることで誤使用を避ける。
        {
            return state_;
        }

    private:
        bool state_{true};
    };

    void f()
    {
        auto a0 = A0{};
        auto a1 = A1{};

        std::cout << a0 + 1;  // NG コンパイルできてしまう。
    #if 0
        std::cout << a1 + 1;  // OK 意図通りコンパイルエラー
    #endif

        // ...
    }
```

* 演算子をオーバーロードする場合、それが自然に使えるようにする。
    * operator == を定義するならば、operator != も定義する（<, >等のその他の例も同様）。
    * operator+ を定義するならば、operator += も定義する(+以外も同様)。
    * copy(またはmove)代入演算子を定義する場合、copy(またはmove)コンストラクタも定義する
      (その際、コードクローンを作りがちなので注意する(「[Copy-And-Swap](cpp_idioms.md#SS_21_1_4)」参照))。

```cpp
    //  example/programming_convention/func_ut.cpp 206

    class Integer {
    public:
        Integer(int32_t integer) noexcept : integer_{integer} {}  // int32_tの暗黙の型変換が必要なのでexplicitしない

        // copyコンストラクタ、copy代入演算子の定義
        Integer(Integer const&)            = default;
        Integer& operator=(Integer const&) = default;

        friend bool operator==(Integer lhs, Integer rhs) noexcept { return lhs.integer_ == rhs.integer_; }

        Integer& operator+=(Integer rhs) noexcept
        {
            integer_ += rhs.integer_;
            return *this;
        }

    private:
        int32_t integer_;
    };

    inline bool operator!=(Integer lhs, Integer rhs) noexcept
    {
        return !(lhs == rhs);  // operator==の活用
    }

    inline Integer operator+(Integer lhs, Integer rhs) noexcept
    {
        lhs += rhs;  // operator+=の活用
        return lhs;
    }

```

* 比較演算子のオーバーロードする場合、
    * C++20であれば、[<=>演算子](core_lang_spec.md#SS_19_6_4_1)を定義する。
    * C++17以下であれば、`operator==`と`operator<`の2つの演算子がを定義し、
      [std::rel_ops](stdlib_and_concepts.md#SS_20_11_1)を使用する。

* [ユーザ定義リテラル演算子](core_lang_spec.md#SS_19_2_6_1)のサフィックスには、
  アンダーバーから始まる3文字以上の文字列を使用する。

```cpp
    //  example/programming_convention/func_ut.cpp 244

    constexpr int32_t one_km{1000};

    // ユーザ定義リテラル演算子の定義
    constexpr int32_t operator""_kilo_meter(unsigned long long num_by_mk)  // OK
    {
        return num_by_mk * one_km;
    }

    constexpr int32_t operator"" km(unsigned long long num_by_mk)  // NG STDでリザーブ
    {
        return num_by_mk * one_km;
    }

    constexpr int32_t operator""_meter(unsigned long long num_by_m)  // OK
    {
        return num_by_m;
    }

    constexpr int32_t operator""_m(unsigned long long num_by_m)  // NG 短すぎる
    {
        return num_by_m;
    }
```
```cpp
    //  example/programming_convention/func_ut.cpp 272

    auto km = int32_t{3_kilo_meter};  // ユーザ定義リテラル演算子の利用
    auto m  = int32_t{3000_meter};    // ユーザ定義リテラル演算子の利用

    ASSERT_EQ(m, km);
```

### 実引数/仮引数 <a id="SS_3_3_4"></a>
* 仮引数(「[実引数/仮引数](core_lang_spec.md#SS_19_14_7)」参照)の数は、4個程度を上限とする。
  引数が多くなりすぎる場合、その関数の引数用の構造体を定義し、それを使用して関数を呼び出す。
  この場合、[指示付き初期化](core_lang_spec.md#SS_19_10_4)を使用する。

* 「[関数設計のガイドライン](cpp_idioms.md#SS_21_6)」の「[関数の引数と戻り値の型](cpp_idioms.md#SS_21_6_1)」に従う。

* 仮引数を関数の戻り値として利用する場合、
    * 「関数が、仮引数がnullptrである場合の処理を行う」場合、ポインタ渡しにする。
    * 「関数が、仮引数がnullptrでないことを前提している」場合、リファレンス渡しにする。

* [forwardingリファレンス](core_lang_spec.md#SS_19_8_3)を仮引数とする関数テンプレートでは、仮引数は非constにする。

* 継承の都合等で、使用しないにもかかわらず定義しなければならない仮引数には名前を付けない。
  仮引数が使用されていない警告の抑止のために[属性構文](core_lang_spec.md#SS_19_9_1)を使わない。
  
* 関数f()の仮引数が2つ以上であり、f()に渡す引数をそれぞれに生成する関数があった場合、
  引数を生成する関数の戻り値を直接f()に渡さない。

```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 22

    class A {
    public:
        int32_t f0() noexcept { return a_++; }

        int32_t f1() noexcept { return a_--; }
        // ...
    };

    void f(int32_t a0, int32_t a1) noexcept
    {
        // ...
    }

    void g(A& a) noexcept
    {
        f(a.f0(), a.f1());  // NG f0()、f1()が呼ばれる順番は未定義。

        auto a0 = a.f0();
        auto a1 = a.f1();
        f(a0, a1);          // OK f0()はf1()よりも先に呼ばれる。
    }
```

* copyコンストラクタ、copy代入演算子、moveコンストラクタ、
  move代入演算子の仮引数名はrhs(「[略語リスト](naming_practice.md#SS_6_1_1)」参照)にする。
* 二項演算子の仮引数名は、左側をlhs、右側をrhsにする。

```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 55

    class B {
    public:
        B(A const& rhs);
        B& operator=(A const& rhs);

    private:
        int32_t b_{0};

        friend bool operator==(B const& lhs, B const& rhs) noexcept { return lhs.b_ == rhs.b_; }
    };
```

* 仮引数の意味を明示するために、関数宣言の仮引数の名前は省略しない。
* 仮引数がない関数の()の中には何も書かない。
  Cからリンクされる場合に限り、関数の()の中にはvoidと書く。

```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 71

    class C {
    public:
        void SetValue(int32_t number_of_peaple);  // OK
    //  void SetValue(int32_t);                   // NG 仮引数名を書く
        void SetValue(D const& d);                // OK
    //  void SetValue(D const&);                  // NG 仮引数名を書く
    //  int32_t GetValue(void) const;             // NG void不要
        int32_t GetValue() const;                 // OK
    };

    extern "C" int32_t XxxGetValue(void);  // OK Cからリンクされる
```

* 実引数として使用される配列がポインタ型へ暗黙に変換されることを前提に、
  仮引数をポインタ型にしない。また、仮引数を一見、配列に見えるポインタ型にしない
  (「[スライシング](cpp_idioms.md#SS_21_12_3)」で述べたように、
  特に基底クラスを配列にすることは危険である)。
  代わりに配列へのリファレンスもしくはstd::arrayを使用する。 

```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 94

    class Base {
    public:
        Base(char const* name) noexcept : name0_{name} {}
        char const* Name0() const noexcept { return name0_; }

        // ...
    private:
        char const* name0_;
    };

    class Derived final : public Base {
    public:
        Derived(char const* name0, char const* name1) noexcept : Base{name0}, name1_{name1} {}
        char const* Name1() const noexcept { return name1_; }

        // ...
    private:
        char const* name1_;
    };

    std::vector<std::string> f(Base const* array, uint32_t n)  // NG 誤用しやすいシグネチャ
    {
        auto ret = std::vector<std::string>{n};

        std::transform(array, array + n, ret.begin(), [](Base const& b) noexcept { return b.Name0(); });

        return ret;
    }

    std::vector<std::string> g(Base const array[10], uint32_t n)  // NG 誤用しやすいシグネチャ
    {
        // str_arrayは一見、配列に見えるが、実際はポインタであるため、
        // この関数のシグネチャはf(Base const* str_array, uint32_t n)と同じ。
        // 配列の長さに見える10はシンタックス上の意味を持たない。
        auto ret = std::vector<std::string>{n};

        std::transform(array, array + n, ret.begin(), [](Base const& b) noexcept { return b.Name0(); });

        return ret;
    }
```
```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 149

    Base    b[]{"0", "0"};
    Derived d[]{{"0", "1"}, {"2", "3"}};

    ASSERT_EQ((std::vector<std::string>{"0", "0"}), f(b, array_length(b)));  // OK これは良いが
    ASSERT_EQ((std::vector<std::string>{"0", "0"}), g(b, array_length(b)));  // OK これは良いが

    // 本来なら、下記のようになるべきだが、
    // ASSERT_EQ((std::vector<std::string>{"0", "2"}), f(d, array_length(d)));  // NG
    // ASSERT_EQ((std::vector<std::string>{"0", "2"}), g(d, array_length(d)));  // NG

    // レイアウトずれにより、下記のようになる
    ASSERT_EQ((std::vector<std::string>{"0", "1"}), f(d, array_length(d)));  // NG
    ASSERT_EQ((std::vector<std::string>{"0", "1"}), g(d, array_length(d)));  // NG
```

```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 169

    // ポインタではなく、配列へのリファレンスを使用することで、
    // 上記のようなバグを避けることができる

    std::vector<std::string> f_ref_2(Base const (&array)[2])  // OK 配列へのリファレンス
    {
        auto ret = std::vector<std::string>{array_length(array)};

        // arrayの型はポインタではなく、リファレンスなのでstd::endが使える
        std::transform(array, std::end(array), ret.begin(), [](Base const& b) noexcept { return b.Name0(); });

        return ret;
    }

    template <size_t N>                                       // 配列の長さの型はsize_t
    std::vector<std::string> f_ref_n(Base const (&array)[N])  // OK 配列へのリファレンス
    {
        auto ret = std::vector<std::string>{N};

        std::transform(array, std::end(array), ret.begin(), [](auto& b) noexcept { return b.Name0(); });

        return ret;
    }

    template <typename T, size_t N>                      // 配列の長さの型はsize_t
    std::vector<std::string> g_ref(T const (&array)[N])  // OK 配列へのリファレンス
    {
        auto ret = std::vector<std::string>{N};

        std::transform(array, std::end(array), ret.begin(), [](auto& b) noexcept { return b.Name0(); });

        return ret;
    }

    template <typename T, size_t N>                                // std::arrayの第2パラメータの型はsize_t
    std::vector<std::string> h_ref(std::array<T, N> const& array)  // OK std::arrayへのリファレンス
    {
        auto ret = std::vector<std::string>{N};

        std::transform(std::begin(array), std::end(array), ret.begin(), [](auto& b) noexcept { return b.Name0(); });

        return ret;
    }

    // NULLを渡す必要がある場合、配列へのリファレンスの代わりに、
    // 配列へのポインタを使うことができる
    template <typename T, uint32_t N>
    std::vector<std::string> g_ptr(T const (*array)[N])  // OK
    {
        if (array == nullptr) {
            return std::vector<std::string>{};
        }

        auto ret = std::vector<std::string>{N};

        std::transform(*array, std::end(*array), ret.begin(), [](auto& b) noexcept { return b.Name0(); });

        return ret;
    }
```
```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 235

    Base    b[]{"0", "0"};
    Derived d[]{{"0", "1"}, {"2", "3"}};
    auto    d2 = std::array<Derived, 2>{Derived{"0", "1"}, Derived{"2", "3"}};

    ASSERT_EQ((std::vector<std::string>{"0", "0"}), f_ref_2(b));  // OK
    ASSERT_EQ((std::vector<std::string>{"0", "0"}), f_ref_n(b));  // OK
    ASSERT_EQ((std::vector<std::string>{"0", "0"}), g_ref(b));    // OK

    // ASSERT_EQ((std::vector<std::string>{"0", "2"}), f_ref_2(d));  OK 誤用なのでコンパイルエラー
    ASSERT_EQ((std::vector<std::string>{"0", "2"}), g_ref(d));   // OK
    ASSERT_EQ((std::vector<std::string>{"0", "2"}), h_ref(d2));  // OK

    // 配列へのポインタを使う場合
    ASSERT_EQ((std::vector<std::string>{"0", "0"}), g_ptr(&b));  // OK

    Derived(*d_null)[3]{nullptr};
    ASSERT_EQ((std::vector<std::string>{}), g_ptr(d_null));  // OK
```

* デフォルト引数は関数のプロトタイプ宣言もしくはクラス宣言内のメンバ関数宣言のみに記述する
  (「[オーバーライド](programming_convention.md#SS_3_2_4_7)」参照)。
* メンバ関数のデフォルト引数は、
  そのクラス外部からのメンバ関数呼び出しを簡潔に記述するための記法であるため、
  非publicなメンバ関数にデフォルト引数を持たさない。
* デフォルト引数の初期化オブジェクトは定数、もしくは常に等価なオブジェクトにする。
  デフォルト引数の初期化オブジェクトは関数呼出し時に評価されるため、
  引数の初期化オブジェクトが等価でない場合、
  関数の処理が初期化オブジェクトの現在の状態に依存してしまう。

```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 257

    int32_t default_arg{0};
    int32_t get_default_arg(int32_t a = default_arg) noexcept { return a; }
```
```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 265

    ASSERT_EQ(0, get_default_arg());  // default_arg == 0

    default_arg = 2;

    ASSERT_EQ(2, get_default_arg());  // default_arg == 2
```

* `std::unique_ptr<T> const&`を引数とする関数は、
  その引数が指すオブジェクトが保持しているT型オブジェクトを書き換えることができるため、
  そのような記述をしない。
  関数がそのT型オブジェクトを書き換える必要があるのであれば引数をT&とする。
  書き換える必要がないのであれば引数をT const&とする。

```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 278

    void f0(std::unique_ptr<std::string> const& str)  // NG *strは書き換え可能
    {
        *str = "it can be changed";

    #if 0  // strはconstなので以下はできない
        str = std::make_unique<std::string>("haha");
    #endif
    }

    void f1(std::string& str)  // OK
    {
        str = "it can be changed";
    }

    void f2(std::string const& str)  // OK
    {
    #if 0  // strは変更できない
        str = "it can NOT be changed";
    #endif
    }
```
```cpp
    //  example/programming_convention/func_arg_type_ut.cpp 305

    auto s = std::make_unique<std::string>("hehe");

    f0(s);   // sは変更されないが、sが保持しているstd::stringオブジェクトは変更できる
    f1(*s);  // sは変更されないが、sが保持しているstd::stringオブジェクトは変更できる
    f2(*s);  // sも、sが指しているstd::stringオブジェクトも変更されない
```

* [演習-仮引数の修飾](exercise_q.md#SS_22_3_11)  

### 自動変数 <a id="SS_3_3_5"></a>
* 一つの文で複数の変数の宣言をしない。
* 自動変数は、それを使う直前に定義することでスコープを最小化する。
* 自動変数は、定義と同時に初期化する。

```cpp
    //  example/programming_convention/func_ut.cpp 313

    int32_t a, b;  // NG 一度に2つの変数定義
    int32_t index;

    // Do something
    // ...

    index = get_index();                    // NG 定義と使用箇所が離れている
    int32_t index2{get_index()};            // OK
    auto    index3 = get_index();           // OK AAA
    auto    index4 = int32_t{get_index()};  // OK 型を明示したAAA

    int32_t i;

    for (i = 0; i < max; ++i) {  // NG 定義と使用箇所が離れている
        // Do something
    }

    for (int32_t i{0}; i < max; ++i) {  // OK
        // Do something
        // ...
    }

    for (auto i = 0; i < max; ++i) {  // OK AAAスタイル
        // Do something
        // ...
    }

    // ...

    auto& w0 = Widget::Inst();  // if文後にはw0を使用しないならばNG
    if (w0.GetStatus() == Widget::Success) {
        w0.DoSomething();
    }
    else {
        w0.DoSomething(Widget::None);
    }
    // この後w0を使用しない

    // ...

    if (auto& w1 = Widget::Inst(); w1.GetStatus() == Widget::Success) {  // OK C++17より使用可能
        w1.DoSomething();
    }
    else {
        w1.DoSomething(Widget::None);
    }

    // ...

    auto const& w2 = Widget::InstConst();  // switch文後にw2を使用しないならばNG
    switch (w2.GetStatus()) {
    case Widget::Success:
        // Do something
        break;
        // ...
    default:
        // Do something
        break;
    }
    // この後w2を使用しない

    // ...

    switch (auto const& w3 = Widget::InstConst(); w3.GetStatus()) {  // OK C++17より使用可能
    case Widget::Success:
        // Do something
        break;
        // ...
    default:
        // Do something
        break;
    }
```

### 戻り値型 <a id="SS_3_3_6"></a>
* メモリアロケータ以外の関数の戻り値をvoid\*にしない。
* 避けがたい理由なしに以下のシンタックスを使用しない。
    * [戻り値型を後置する関数宣言](core_lang_spec.md#SS_19_11_17)
    * [関数の戻り値型auto](core_lang_spec.md#SS_19_11_18)
    * [後置戻り値型auto](core_lang_spec.md#SS_19_11_19)

```cpp
    //  example/programming_convention/func_return_ut.cpp 22

    auto f(int32_t a, int32_t b) noexcept -> decltype(a + b)  // NG
    {
        return a + b;
    }

    template <typename T>
    auto f(T a, T b) noexcept -> decltype(a + b)  // OK 後置構文以外に方法がない
    {
        return a + b;  // T = uint8_tとすると、a + bの型はint32_t
    }
```

* 戻り値型は「[関数の引数と戻り値の型](cpp_idioms.md#SS_21_6_1)」に従う。

* 関数が複数の値を返す場合、[std::optional](stdlib_and_concepts.md#SS_20_9)、std::pair、std::tupple、
  構造体オブジェクトを戻り値にして返す。パフォーマンスに著しい悪影響がない限り、
  リファレンス引数で戻り値を返さない(「[関数の戻り値オブジェクト](programming_convention.md#SS_3_9_3)」参照)。

```cpp
    //  example/programming_convention/func_return_ut.cpp 38

    // NG 関数の戻り値が不明確
    void f(int32_t a, int32_t b, int32_t& quotient, int32_t& remainder)
    {
        quotient  = a / b;
        remainder = a % b;
    }

    // NG 関数の戻り値が不明確
    int32_t f(int32_t a, int32_t b, int32_t& remainder)
    {
        remainder = a % b;
        return a / b;
    }

    // 場合によりNG  f_pairがprivate関数やファイル内関数であり、広域に使われないのであれば問題ない
    std::pair<int32_t, int32_t> f_pair(int32_t a, int32_t b) { return {a / b, a % b}; }

    // 場合によりNG  f_tupleがprivate関数やファイル内関数であり、広域に使われないのであれば問題ない
    //               f_tupleが広域に使われない場合でも、tupleの型引数の数が3個を大きく超える場合に可読性が劣化する
    std::tuple<int32_t, int32_t> f_tuple(int32_t a, int32_t b) { return {a / b, a % b}; }

    struct Result {
        int32_t quotient;
        int32_t remainder;
    };

    Result f_struct(int32_t a, int32_t b)  // OK
    {
        return {a / b, a % b};
    }
```
```cpp
    //  example/programming_convention/func_return_ut.cpp 75

    int32_t quotient0;
    int32_t remainder0;
    f(7, 3, quotient0, remainder0);             // NG quotient0、remainder0が戻り値かどうかわかりづらい
    ASSERT_EQ(2, quotient0);
    ASSERT_EQ(1, remainder0);

    int32_t remainder1;
    int32_t quotient1 = f(7, 3, remainder1);    // NG remainder1が戻り値かどうかわかりづらい
    ASSERT_EQ(2, quotient1);
    ASSERT_EQ(1, remainder1);

    auto ret0 = f_pair(7, 3);                   // 場合によりNG
    ASSERT_EQ(2, ret0.first);                   // ret0.firstが何を表しているかどうかわかりづらい
    ASSERT_EQ(1, ret0.second);                  // ret0.secondが何を表しているかどうかわかりづらい

    auto ret1 = f_tuple(7, 3);                  // 場合によりNG
    ASSERT_EQ(2, std::get<0>(ret1));            // std::get<0>(ret1)が何を表しているかどうかわかりづらい
    ASSERT_EQ(1, std::get<1>(ret1));            // std::get<1>(ret1)が何を表しているかどうかわかりづらい

    auto [quotient2, remainder2] = f_struct(7, 3); // OK C++17 構造化束縛の使いすぎには注意
    ASSERT_EQ(2, quotient2);
    ASSERT_EQ(1, remainder2);

    auto ret2 = f_struct(7, 3);                 // OK
    ASSERT_EQ(2, ret2.quotient);
    ASSERT_EQ(1, ret2.remainder);
```

* 処理の成否をbool等で通知し、成功時の戻り値をリファレンス引数で戻す関数や、
  処理の成功時の値と、失敗時の外れ値を戻り値で返す関数を作らない。
  代わりにC++17で導入された[std::optional](stdlib_and_concepts.md#SS_20_9)を使用する。

```cpp
    //  example/programming_convention/func_return_ut.cpp 108

    namespace {

    // NG 関数の戻り値が不明確
    bool f(int32_t a, int32_t b, int32_t& remainder)
    {
        if (b == 0) {
            return false;
        }

        remainder = a % b;

        return true;
    }

    // NG 余りが-1になる場合(外れ値)、エラー通知
    int32_t f(uint32_t a, uint32_t b)
    {
        if (b == 0) {
            return -1;
        }

        return a % b;
    }

    // NG ret.firstがエラーを表していることが不明確
    std::pair<bool, int32_t> f_pair(int32_t a, int32_t b)
    {
        if (b == 0) {
            return {false, 0};
        }

        return {true, a % b};
    }

    struct Result {
        bool    is_success;
        int32_t remainder;
    };

    // NG 悪くはないが、エラー時でもResult::remainderにアクセスできる
    Result f_struct(int32_t a, int32_t b)
    {
        if (b == 0) {
            return {false, 0};
        }

        return {true, a % b};
    }

    std::optional<int32_t> f_optional(int32_t a, int32_t b)  // OK
    {
        if (b == 0) {
            return std::nullopt;
        }

        return a % b;
    }
```
```cpp
    //  example/programming_convention/func_return_ut.cpp 171

    int32_t remainder0;

    auto result0 = f(7, 0, remainder0);             // NG エラー時にremainder0が有効か否かわからない
    ASSERT_FALSE(result0);

    auto remainder1 = f(7, 0);                      // NG エラー通知がわかりづらい
    ASSERT_EQ(-1, remainder1);

    auto ret = f_pair(7, 0);                        // NG ret.firstがエラーを表していることが不明確
    ASSERT_FALSE(ret.first);

    auto [result2, remainder2] = f_struct(7, 0);    // エラー時にremainder2が有効か否かわからない
    ASSERT_FALSE(result2);

    auto result1 = f_optional(7, 0);                // OK
    ASSERT_FALSE(result1);                          // エラーの判定  値は取り出すための*result1はエクセプション

    result1 = f_optional(7, 4);                     // OK
    ASSERT_TRUE(result1);                           // 成功の判定
    ASSERT_EQ(3, *result1);                         // 成功時の値取り出し
```


### constexpr関数 <a id="SS_3_3_7"></a>
* 引数が[constexpr](core_lang_spec.md#SS_19_5_1)の場合、コンパイル時に評価が確定する関数テンプレートもしくはinline関数は、
  [constexpr関数](core_lang_spec.md#SS_19_5_3)として宣言する。
* [constexpr関数](core_lang_spec.md#SS_19_5_3)がコンパイル時に評価される必要がある場合、
  [constexpr](core_lang_spec.md#SS_19_5_1)の代わりに[consteval](core_lang_spec.md#SS_19_5_7)を使用する。

* [演習-constexpr関数](exercise_q.md#SS_22_3_12)  

### スレッドセーフ性 <a id="SS_3_3_8"></a>
* 関数、メンバ関数はなるべく[スレッドセーフ](cpp_idioms.md#SS_21_14_3)に実装する。
* 複数のスレッドから呼び出される関数は必ずスレッドセーフにする。

```cpp
    //  example/programming_convention/func_ut.cpp 415

    int32_t var{0};

    int32_t f() noexcept  // スレッドセーフでない関数f()
    {
        return ++var;
    }

    int32_t f(int32_t& i) noexcept  // スレッドセーフな関数f()
    {
        return ++i;
    }
```

### エクセプション処理 <a id="SS_3_3_9"></a>
* 関数はそれが不可避でない限り、[no-fail保証](core_lang_spec.md#SS_19_13_7_1)をする。
  [no-fail保証](core_lang_spec.md#SS_19_13_7_1)関数は[noexcept](core_lang_spec.md#SS_19_13_6)を使用してそのことを明示する。
* throwをせざるを得ない場合、最低でも[基本的な安全性の保証](core_lang_spec.md#SS_19_13_7_3)をする。
* 標準ライブラリのコンテナ(std::string, std::vector等)が発生させるエクセプションはtry-catchせず
  (catchしてデバッグ情報を保存するような場合を除く)、
  プログラムをクラッシュさせる。try-catchしてもできることはない。
* 特別な理由がない限り、コンストラクタ呼び出しは[noexcept](core_lang_spec.md#SS_19_13_6)と宣言する。
  ネットワーク接続等、簡単にエラーすることをコンストラクタ内で行わない。
* [オープン・クローズドの原則(OCP)](solid.md#SS_8_2)、[リスコフの置換原則(LSP)](solid.md#SS_8_3)に違反する場合が多いため、
  「throwキーワードによるエクセプション仕様」を使用しない(C++17で廃止)。
* エクセプションをthrowしないことが確定している関数は、[noexcept](core_lang_spec.md#SS_19_13_6)と宣言する。
  move代入演算子を[noexcept](core_lang_spec.md#SS_19_13_6)と宣言することは特に重要である。

```cpp
    //  example/programming_convention/func_ut.cpp 446

    int32_t f() noexcept;  // OK fはno-fail保証

    class Derived : public Base {
        // ...
        // オブジェクトの状態を変えず(const)、エクセプションを発生させず(noexcept)
        // f()の最後(final)のoverride
        virtual int32_t f() const noexcept final
        {
            // ...
        }
    };
```

* try-catchが不可避である場合、以下の理由によりconstリファレンスで受け取る。
    * 実態で受け取るとオブジェクトの[スライシング](cpp_idioms.md#SS_21_12_3)が起こる場合がある。
    * 受け取ったエクセプションオブジェクトを書き換えるべきではない。

* エクセプションによるリソースリークを避けるため[RAII(scoped guard)](cpp_idioms.md#SS_21_1_3)でリソースを管理する。
* 一連のcatch節では、catchするエクセプションの型の最もマッチ率の高いcatch節で処理されるのではなく、
  マッチした最上位のcatch節で処理されるため、
  catchするエクセプションの型に継承関係があるのであれば、継承順位が低い順番にcatchする。
  また、catch(...)は一番最後に書く(関数tryブロックの場合も同様にする)。

```cpp
    //  example/programming_convention/func_ut.cpp 466

    struct ExceptionA : std::exception {};
    struct ExceptionB : ExceptionA {};
    struct ExceptionX : std::exception {};

    void order_of_catch() noexcept
    {
        try {
            // ...
        }
        catch (ExceptionB const& e) {  // ExceptionAの前に書く。
            // ...
        }
        catch (ExceptionA const& e) {  // std::exceptionの前に書く。
            // ...
        }
        catch (ExceptionX const& e) {  // std::exceptionの前に書く。
            // ...
        }
        catch (std::exception const& e) {  // catch(...)の前に書く。
            // ...
        }
        catch (...) {  // 必ず一番最後に書く。
            // ...
        }
    }

    void order_of_catch_with_try() noexcept
    try {  // 関数tryブロック
        // ...
    }
    catch (ExceptionB const& e) {  // ExceptionAの前に書く。
        // ...
    }
    catch (ExceptionA const& e) {  // std::exceptionの前に書く。
        // ...
    }
    catch (ExceptionX const& e) {  // std::exceptionの前に書く。
        // ...
    }
    catch (std::exception const& e) {  // catch(...)の前に書く。
        // ...
    }
    catch (...) {  // 必ず一番最後に書く。
        // ...
    }
```

* [exception-unfriendly](core_lang_spec.md#SS_19_13_8)な関数はエクセプションを発生させないようにする。
* エクセプションをthrowする場合、独自定義したオブジェクトを使用しない。
  代わりにstd::exceptionか、これから派生したクラスを使用する。
  また、throwされたオブジェクトのwhat()から、throwされたファイル位置が特定できるようにする
  (「[ファイル位置を静的に保持したエクセプションクラスの開発](template_meta_programming.md#SS_13_7_6_4)」参照)。


* noexceptと宣言された関数へのポインタへ、noexceptでない関数のポインタを代入しない
  (C++17では[ill-formed](core_lang_spec.md#SS_19_14_1)になる)。

```cpp
    //  example/programming_convention/func_ut.cpp 529

    int32_t f0()  // noexceptではないため、エクセプションを発生させることがある。
    {
        // ...
    }

    int32_t f1() noexcept
    {
        // ...
    }

    #if __cplusplus < 201703L            // 以下のコードはC++14以前ではコンパイルできるが、
                                         // C++17以降ではコンパイルエラー
    int32_t (*f_ptr0)() noexcept = &f0;  // NG f_ptr0()はnoexceptだが、
                                         //    f0はエクセプションを発生させる可能性がある。
    #endif
    int32_t (*f_ptr1)() noexcept = &f1;  // OK
    int32_t (*f_ptr2)()          = &f0;  // OK
    int32_t (*f_ptr3)()          = &f1;  // OK f1はエクセプションを発生させない。

    class A {
    public:
        int32_t f0()  // noexceptではないため、エクセプションを発生させることがある。
        {
            // ...
        }

        int32_t f1() noexcept
        {
            // ...
        }
    };

    #if __cplusplus < 201703L                   // 以下のコードはC++14以前ではコンパイルできるが、
                                                // C++17以降ではコンパイルエラー
    int32_t (A::*mf_ptr0)() noexcept = &A::f0;  // NG mf_ptr0()はnoexceptだが、
                                                //    f0はエクセプションを発生させる可能性がある。
    #endif
    int32_t (A::*mf_ptr1)() noexcept = &A::f1;  // OK
    int32_t (A::*mf_ptr2)()          = &A::f0;  // OK
    int32_t (A::*mf_ptr3)()          = &A::f1;  // OK f1はエクセプションを発生させない。

```

* [演習-エクセプションの型](exercise_q.md#SS_22_3_13)  

### ビジーループ <a id="SS_3_3_10"></a>
* ビジーループを使わない。[std::condition_variable](stdlib_and_concepts.md#SS_20_4_4)を使用してイベントドリブンにする。

```cpp
    //  example/programming_convention/func_ut.cpp 591

    // NG イベントドリブンにするべき
    void wait_busily() noexcept
    {
        while (1) {
            sleep(1);
            if (xxx_flag) {
                break;
            }
        }
        // ...
    }
```

### 非メンバ関数 <a id="SS_3_3_11"></a>
* 下記のような関数を除き、グローバル名前空間に非メンバ関数を定義しない。
    * C言語から呼び出される関数
    * アセンブラ関数

* .cppファイルから、そのファイルの外部で定義された関数を呼び出す場合、その.cppファイル内での局所的な関数宣言をしない。
  つまり、.cppファイルローカルなetern関数宣言を行ってはならない
  (関数が宣言、定義されているヘッダファイルをインクルードする)。
* コンパイル時に戻り値が確定する関数は[constexpr関数](core_lang_spec.md#SS_19_5_3)として宣言する。

* [演習-非メンバ関数の宣言](exercise_q.md#SS_22_3_1)

## 構文 <a id="SS_3_4"></a>

### 複合文 <a id="SS_3_4_1"></a>
* if, else, for, while, do後には複合文を使う。

```cpp
    //  example/programming_convention/syntax_ut.cpp 22

    if (a == 0) {
        b = 0;  // OK
    }

    if (a == 0)
        b = 0;                      // NG 複合文でない

    if (a == 0) {
        b = 0;                      // OK
    }
    else                            // NG 複合文でない
        b = 1;

    for (auto i = 0; i < a; ++i) {  // OK
        c[i] = i;
    }

    for (auto i = 0; i < a; ++i)    // NG
        c[i] = i;
```

* 空の複合文には、何もすることがないという意図を表現するため、";"だけの文を置き、
  空の複合文である事を明示する。

```cpp
    //  example/programming_convention/syntax_ut.cpp 53

    while (volatile_flag) {
    }  // NG ;が無い

    while (volatile_flag) {
        ;  // OK
    }

    while (volatile_flag)
        ;  // NG whileの文が複合文でない
```

### switch文 <a id="SS_3_4_2"></a>
* caseラベル、defaultラベルに関連付けられた一連の文はできだけフォールスルーさせない。
  実装がシンプルになる等の理由からフォールスルーさせる場合、
  [属性構文](core_lang_spec.md#SS_19_9_1)を使用しそれが意図的であることを明示するため以下のような記述する。

```cpp
    // fallthrough          // C++14以前

    [[fallthrough]];        // C++17以降
```

* defaultラベルは省略せず、switch文の末尾に書く。
    * defaultラベルに関連付けられた処理がない場合は、breakのみを記述する。
    * 論理的にdefaultラベルに到達しないのであれば、
      defaultラベルに続いてassert(false)を実行することで、
      そこを通過してはならないことを明示する(「[assertion](programming_convention.md#SS_3_11_1)」参照)。

```cpp
    //  example/programming_convention/syntax_ut.cpp 79

    switch (a) {
    case 0:
        b = 0;
        break;  // OK
    case 1:
        e = 2;  // NG break無しで抜けているのにコメントが無い
    case 2:
        c = 1;
        // fallthrough  C++14以前であればOK
    case 3:
        e += 2;
        [[fallthrough]];  // OK C++17
    case 4:
        d = 1;
        break;  // OK
    default:
        assert(false);  // OK 論理的にここには来ないのならば、defaultを省略せずにassert
    }
```

* switch文のオペランド変数を生成する場合、
  できるだけ[初期化付きswitch文](core_lang_spec.md#SS_19_9_4_4)を使用し、その変数のスコープを最小に留める。

### if文 <a id="SS_3_4_3"></a>
* if-else-ifと連続する場合は、else文で終了させる。
  最後のelseのブロックでやるべき処理がないのであれば、そのブロックに;のみを記述する。

```cpp
    //  example/programming_convention/syntax_ut.cpp 111

    if (a == 1) {
        // ...
    }
    else if (a == 2) {
        // ...
    }  // NG elseで終了していない

    if (a == 1) {
        // ...
    }
    else if (a == 2) {
        // ...
    }
    else {  // OK else文でやることがない場合は、;のみ記述
        ;
    }
```

* if-else-ifの最後のelseのブロックに論理的に到達しないのであれば、
  そのブロックでassert(false)を実行する(「[assertion](programming_convention.md#SS_3_11_1)」参照)。

```cpp
    //  example/programming_convention/syntax_ut.cpp 134

    if (a == 1) {
        // ...
    }
    else if (a == 2) {
        // ...
    }
    else {              // OK
        assert(false);  //    ここに来るのはバグの場合。
    }
```

* 条件が2つ以上且つ、switchで表現できる条件文には、ifではなくswitchを使用する。
* ifの条件式が、コンパイル時に定まるのであれば、[constexpr if文](core_lang_spec.md#SS_19_11_12)を使用する。

* if文のオペランド変数を生成する場合、
  できるだけ[初期化付きif文](core_lang_spec.md#SS_19_9_4_3)を使用し、その変数のスコープを最小に留める。

### while文 <a id="SS_3_4_4"></a>
* while文には、[初期化付きif文](core_lang_spec.md#SS_19_9_4_3)/[初期化付きswitch文](core_lang_spec.md#SS_19_9_4_4)のような構文は存在しないが、
  while文のオペランド変数を生成するする場合、
  [初期化付きfor文(従来のfor文)](core_lang_spec.md#SS_19_9_4_1)を使用し、その変数のスコープを最小に留める。

### 範囲for文 <a id="SS_3_4_5"></a>
* 配列やコンテナの全要素にアクセスするような繰り返し処理には、
  [off-by-oneエラー](https://ja.wikipedia.org/wiki/Off-by-one%E3%82%A8%E3%83%A9%E3%83%BC)
  が避けられ、従来よりもシンプルに記述できる[範囲for文](core_lang_spec.md#SS_19_9_2)を使用する。

```cpp
    //  example/programming_convention/syntax_ut.cpp 155

    auto vect = std::vector<uint32_t>{0, 1, 2, 3, 4};

    // NG oldスタイル
    for (auto i = 0U; i < vect.size(); ++i) {
        std::cout << vect[i] << " ";
    }
    // ...

    // NG C++03スタイル
    for (std::vector<uint32_t>::iterator it = vect.begin(); it != vect.end(); ++it) {
        *it = 3;
    }

    for (std::vector<uint32_t>::const_iterator it = vect.cbegin(); it != vect.cend(); ++it) {
        std::cout << *it << " ";
    }
    // ...

    // OK C++11スタイル
    for (auto const& a : vect) {
        std::cout << a << " ";
    }
    // ...
```

* 独自のコンテナクラスを定義する場合、標準ライブラリのコンテナと同様の要件を満たすbegin()、end()や、
  cbegin()、cend()も定義し、そのコンテナに[範囲for文](core_lang_spec.md#SS_19_9_2)を適用できるようにする。

* [演習-コンテナの範囲for文](exercise_q.md#SS_22_4_1)  

### 制御文のネスト <a id="SS_3_4_6"></a>
* breakとの関係がわかりづらい、ブロックが巨大になる等の問題があるため、
  if, for, while, do-while, switch文に付随するブロックの中にswitch文を書かない。

### return文 <a id="SS_3_4_7"></a>
* returnの後に括弧をつけない。

```cpp
    //  example/programming_convention/syntax_ut.cpp 194

    // ...

    if (xxx) {
        // decltype(retval)は、int32_t
        // decltype((retval))は、(retval)がlvalueであるためint32_t&
        // この違いは通常問題にはならないが、関数の戻り値を型推測させると問題になる。
        return (retval);  // NG ()は不要
    }
    else {
        return retval2;  // OK
    }
```

* 下記のようなreturnしない関数には、[[noreturn]]をつけて宣言、定義する。

```cpp
    //  example/programming_convention/syntax_ut.cpp 215

    // @brief メッセージを出力してプログラムを終了させる。
    // @param const char* message 上記メッセージ
    [[noreturn]] void terminate(char const* message)
    {
        auto const str = std::string{"unrecoverable error"} + message;

        // ...

        throw std::runtime_error{str};
    }
```

### goto文 <a id="SS_3_4_8"></a>
* 二重以上のループを抜ける目的以外でgotoを使用しない。
* 二重以上のループを抜ける目的でgotoを使用する場合、gotoのジャンプ先ラベルはそのループの直後に置く。

### ラムダ式 <a id="SS_3_4_9"></a>
* [ラムダ式](core_lang_spec.md#SS_19_10_3)を複雑にしない。
    * できるだけワンライナーにする。
    * 必ず10行以下にする。

```cpp
    //  example/programming_convention/syntax_ut.cpp 235

    // ラムダ式はワンライナーが基本
    auto itr = std::find_if(strs.begin(), strs.end(),
                            [](auto const& n) noexcept { return (n.at(0) == 'n') && (n.size() > 5); });
```

* デフォルトのキャプチャ方式は、ローカル変数を無限定にキャプチャしてしまうため使用しない。
    * C++11では、キャプチャする変数ごとに代入キャプチャか参照キャプチャを使用する。
    * C++14以降では、初期化キャプチャを使用する。

```cpp
    //  example/programming_convention/syntax_ut.cpp 259

    // NG デフォルトのキャプチャ方式
    class A {
    public:
        // ...
        std::vector<std::string> GetNameLessThan(uint32_t length) const
        {
            auto ret = std::vector<std::string>{};

    #if __cplusplus == 201703L  // =でのキャプチャは範囲は大きすぎるため、C++20から非推奨
            std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                         [=](auto const& str) noexcept { return (strs_.size() < length); });

    #elif __cplusplus == 202002L
            std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                         [&strs = strs_, length = length](auto const& str) noexcept { return (strs.size() < length); });
    #else
            static_assert(false, "C++ version not supported!");
    #endif

            return ret;
        }

    private:
        std::vector<std::string> strs_;
    };
```

```cpp
    //  example/programming_convention/syntax_ut.cpp 294

    // OK 限定したキャプチャにより、ラムダ式から可視である変数が限定された
    class A {
    public:
        // ...
        std::vector<std::string> GetNameLessThan(uint32_t length) const
        {
            auto ret = std::vector<std::string>{};

    #if __cplusplus == 201103L  // c++11
                                // [length]を代入キャプチャと呼ぶ。

            std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                         [length](std::string const& str) noexcept { return (str.size() < length); });

    #elif __cplusplus >= 201402L  // c++14以降
            // [length = length]を初期化キャプチャと呼ぶ。
            // 左のlengthのスコープはラムダ式内。右のlengthのスコープはGetNameLessThan内。

            std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                         [length = length](auto const& str) noexcept { return (str.size() < length); });
    #else
            static_assert(false, "CPP_VER should be 11 or 14");
    #endif
            return ret;
        }
        // ...
    };
```

* 外部のオブジェクトを参照キャプチャしたクロージャを、
  その外部オブジェクトのライフタイムを超えて使用しない。
    * 関数で作られたクロージャがその関数のローカル変数のハンドルを使用するのであれば、
      そのクロージャをその関数外で使用しない。
    * オブジェクトで作られたクロージャがそのメンバ変数のハンドルを使用するのであれば、
      そのオブジェクトの終了後にそのクロージャを使用しない。

```cpp
    //  example/programming_convention/syntax_ut.cpp 330

    class B {
    public:
        // ...
        std::function<bool(int)> GenLambda(int max)
        {
            // NG
            // この関数が返すはクロージャがリファレンスしているmaxはこの関数が終了すると無効になる。
            return [&max](int n) noexcept { return n < max; };
        }

        std::function<bool(int)> GenLambda()
        {
            // NG
            // この関数が返すクロージャがリファレンスしているmin_はBオブジェクトが終了すると無効になる。
            return [&min = min_](int n) noexcept { return n > min; };
        }

    private:
        int min_;
    };
```

* C++17以降では、 コンパイル時に戻り値が確定するラムダ式の呼び出し式は定数にできるため、
  そのようなラムダ式は[constexprラムダ](core_lang_spec.md#SS_19_5_9)として宣言する。

```cpp
    //  example/programming_convention/syntax_ut.cpp 368

    auto square1 = [](int32_t n) { return n * n; };

    static_assert(square1(2) == 4);  // C++17以降、square1(2)はリテラル

    auto i = 2;
    // static_assert(square1(i) == 2);  // iはconstexprではないので、コンパイルエラー

    constexpr auto j       = 2;
    constexpr auto square2 = [n = j]() { return n * n; };  // constexprの宣言が必要

    static_assert(square2() == 4);  // C++17以降、square2()はリテラル

    auto square3 = [n = j]() { return n * n; };

    // static_assert(square3() == 4);  // square3()はリテラルではないので、コンパイルエラー
```
```cpp
    //  example/programming_convention/syntax_ut.cpp 389

    constexpr int32_t square4(int32_t n)  // OK nがconstexprであれば、ラムダはconstexpr
    {
        return [n] { return n * n; }();
    }

    static_assert(square4(2) == 4);  // C++17以降、square4(2)はリテラル

    constexpr auto square5(int32_t n)  //  OK nがconstexprであれば、ラムダはconstexpr
    {
        // nがconstexprならば、ラムダ式はリテラル
        auto f = [n] { return n * n; };

        // fの戻り値がリテラルならば、gもリテラル
        auto g = [f] { return f(); };
        return g;
    }

    static_assert(square5(2)() == 4);  // C++17以降、square5(2)はリテラル
```

* [演習-ラムダ式](exercise_q.md#SS_22_4_2)  
* [演習-ラムダ式のキャプチャ](exercise_q.md#SS_22_4_3)  

### マクロの中の文 <a id="SS_3_4_10"></a>
* マクロの中に文がある場合、do-while(0)イデオムを使用する(「[関数型マクロ](programming_convention.md#SS_3_6_1)」参照)。

```cpp
    //  example/programming_convention/syntax_ut.cpp 417

    // do-while(0)イデオムによる関数型マクロ
    #define INIT_ARRAY(array_, x_)      \
        do {                            \
            for (auto& a_ : (array_)) { \
                a_ = (x_);              \
            }                           \
        } while (0)

    void f(uint32_t (&a)[10])
    {
        // INIT_ARRAYがdo-whileではなく、単なるブロックで囲むと、";"が余計になる。
        INIT_ARRAY(a, 3);
    }
```

## 演算子 <a id="SS_3_5"></a>

### 優先順位 <a id="SS_3_5_1"></a>
* 規格上で[演算子のオペランドの評価順位](core_lang_spec.md#SS_19_14_12)が決まっていても、一見優先順位が分かりづらい式では、
  順序を明示するために丸括弧を使う。

```cpp
    //  example/programming_convention/operator_ut.cpp 18

    // 論理演算子例
    if (a < b && c < d || e < f)  // NG 優先順位がわからない
    {
        // ...
    }

    if (((a < b) && (c < d)) || (e < f))  // OK
    {
        // ...
    }

    // シフト演算子例
    auto a0 = b << 16 + 1;    // NG
    auto a1 = b << (16 + 1);  // OK
    auto a2 = (b << 16) + 1;  // OK

    // ビット演算ではないが
    std::cout << a0 + 1;    // NG
    std::cout << (a1 + 1);  // OK

    // 三項演算子例
    auto e0 = a ? b : c = d;      // NG
    auto e1 = ((a ? b : c) = d);  // OK
    auto e2 = (a ? b : (c = d));  // OK 上記NG式と同じ意味
```

* 複合代入式とそれと等価に見える式での演算順序の違いに気を付ける。

```cpp
    //  example/programming_convention/operator_ut.cpp 60
    {
        auto a = 4;

        a = a * 3 / 2;
        ASSERT_EQ(6, a);
    }
    {
        auto a = 4;

        a *= 3 / 2;  // この式は、a = a * 3 / 2と等価ではない
        ASSERT_EQ(4, a);
    }
```

### 代入演算 <a id="SS_3_5_2"></a>
* [単純代入](core_lang_spec.md#SS_19_14_8)のみからなる文を除き、1つの文で複数の代入を行わない。

```cpp
    //  example/programming_convention/operator_ut.cpp 87

    a = b = 0;              // OK
    b     = (a += 1) + 2;   // NG
    b     = (a++) + (c++);  // NG

    b = b++;  // NG unary operators assign itself.

    ++a;         // OK
    auto i = a;  // OK

    a = 0;                 // OK
```

* 一部の例外を除き、ifの条件文の中で代入しない。

```cpp
    //  example/programming_convention/operator_ut.cpp 104

    if (c = b) {  // NG ifの条件文の中で代入
        return 0;
    }

    if ((fd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  // OK このような場合は代入していることが明確
        return false;
    }

    if (auto fd2 = socket(AF_INET, SOCK_STREAM, 0); fd2 < 0) {  // OK C++17
        return false;
    }
    else {
        // fd2を使った処理
        // ...
    }
```

### ビット演算 <a id="SS_3_5_3"></a>
* 「[ビットシフトにおける未定義動作](core_lang_spec.md#SS_19_1_5_1)」を回避することは困難であるため、
  特別な理由がない限り、 可読性と安全性を優先して、ビット演算にはstd::bitsetや[BitmaskType](cpp_idioms.md#SS_21_2_3)を使用する。

### 論理演算 <a id="SS_3_5_4"></a>
* &&や||の論理演算子の右オペランドで[副作用](cpp_idioms.md#SS_21_14_16)のある処理をしない。

```cpp
    //  example/programming_convention/operator_ut.cpp 138

    if (a == 0 && ++b > 3) {  // NG ++bが上記の副作用
        // ...
    }

    // ↑のような記述は、↓とは意味が違う
    ++b;
    if (a == 0 && b > 3) {  // OK
        // ...
    }

    if (a == 0) {  // OK 上記NGのif文と同じ意味
        ++b;
        if (b > 3) {
            // ...
        }
    }
```

### 条件演算子 <a id="SS_3_5_5"></a>
* 単純なif文よりも、条件演算子を優先して使用する
  (const変数の条件付き初期化は条件演算子でのみ可能である)。

```cpp
    //  example/programming_convention/operator_ut.cpp 170

    int const a0{xxx ? 3 : 4};  // OK constで定義、初期化

    int a1;  // NG a1をconstにできない
             //    定義と初期が分離してしまう
    if (xxx) {
        a1 = 3;
    }
    else {
        a1 = 4;
    }
```

* [演習-条件演算子](exercise_q.md#SS_22_5_1)  

### メモリアロケーション <a id="SS_3_5_6"></a>
#### new <a id="SS_3_5_6_1"></a>
* オブジェクトのダイナミックな生成には、特別な理由がない限りnewを使用せず、
  [std::make_unique](stdlib_and_concepts.md#SS_20_6_1_1)や[std::make_shared](stdlib_and_concepts.md#SS_20_6_2_1)を使用する。
  また、特別な理由でnewした場合、そのポインタは[スマートポインタ](stdlib_and_concepts.md#SS_20_6)で管理する。
* [std::shared_ptr](stdlib_and_concepts.md#SS_20_6_2)でダイナミックに生成したオブジェクトを管理する場合、
  [オブジェクトの循環所有](cpp_idioms.md#SS_21_4_3)が発生しないように気を付ける(適切に[std::weak_ptr](stdlib_and_concepts.md#SS_20_6_3)を使う)。
* [プレースメントnew](core_lang_spec.md#SS_19_6_9)を使用しない。
* `new T[N]`を使用しない。代わりにstd::arrayをダイナミックに生成するか、std::vectorを使用する。
* [new (std::nothrow)](core_lang_spec.md#SS_19_6_10)を使わない限り、
  newの戻り値がnullptrであることはないため、new演算子の返り値をnullptrと比較しない。
* スタック上で生成しても差し支えないオブジェクトをダイナミックに生成しない。
* newを禁止したいクラスには、privateなoperator new()を宣言する(定義は不要)か、= deleteする。

#### delete <a id="SS_3_5_6_2"></a>
* [不完全型](core_lang_spec.md#SS_19_4_6)のオブジェクトへのポインタをdeleteしない。
  特に「[Pimpl](cpp_idioms.md#SS_21_2_1)」を使用する場合には注意が必要である。

```cpp
    //  example/programming_convention/operator_ut.cpp 204

    void deleteA(A* a_ptr) noexcept
    {
        // Aが不完全型だった場合、deleteAは、A::~A()にアクセスできないため、A::~A()は呼び出されない
        // これはリソースリークにつながる
        delete a_ptr;
    }

    // やむを得ず、deleteAのような関数を作る場合、下記のようにstatic_assertをdelete行の直前に書く
    // こうすることによりAが不完全型であった場合、コンパイルエラーとなる
    void deleteA2(A* a_ptr) noexcept
    {
        static_assert(sizeof(*a_ptr) != 0, "incomplete type");
        delete a_ptr;
    }

    // やむを得ず、deleteAのような関数を作る場合、std::unique_ptr<>を使用することもできる
    // こうすることによりAが不完全型であった場合、コンパイルエラーとなる
    void deleteA3(A* a_ptr) noexcept { std::unique_ptr<A> a(a_ptr); }
```

* 不完全型と同じような不具合が起こるためvoid\*をdeleteしない。

```cpp
    //  example/programming_convention/operator_ut.cpp 226

    void delete_ptr(void* v_ptr) noexcept
    {
        // NG
        // 任意の型のポインタは、キャストすること無しでこの関数に渡すことができる
        // そのポインタがクラス型であった場合でも、void*として扱われるため、
        // そのクラスのデストラクタは呼び出されない
        delete v_ptr;
    }

    void deleteA4(A* ptr) noexcept
    {
        delete_ptr(ptr);  // NG ptrはvoid*へ暗黙のキャストが行われる
                          //    delete_ptrでは、A::~A()は呼び出されない
    }
```

* deleteはオペランドがnullptrであった場合、何もしないため、delete対象ポインタをnullptrと比較しない。

```cpp
    //  example/programming_convention/operator_ut.cpp 246

    if (ptr != nullptr) {  // NG nullptrとの比較は不要
        delete ptr;
    }

    // ...

    delete ptr;  // OK ptrがnullptrでも問題ない
```

* [演習-delete](exercise_q.md#SS_22_5_2)  

### sizeof <a id="SS_3_5_7"></a>
* sizeof(型名)とsizeof(インスタンス名)の両方が使える場合、sizeof(インスタンス名)を優先的に使用する。
* ポインタ型変数に関して、それが指しているインスタンスのサイズを獲得する場合は、
  sizeof(\*ポインタ型変数名)を使用する
  (そのポインタがnullptrであってもデリファレンスされないので問題ない)。

```cpp
    //  example/programming_convention/operator_ut.cpp 272

    uint8_t  a = 0;
    uint8_t* b = &a;

    auto s_0 = sizeof(uint8_t);  // NG aのサイズをs_0に代入したい場合
    auto s_1 = sizeof(a);        // OK aのサイズをs_1に代入したい場合
    auto s_2 = sizeof(*b);       // OK *bのサイズをs_2に代入したい場合
```

* 上記例を除き、sizeof演算子のオペランドは一見[副作用](cpp_idioms.md#SS_21_14_16)を持っているような式を含んではならない。

```cpp
    //  example/programming_convention/operator_ut.cpp 284

    a = 0;

    auto size_3 = sizeof(++a);  // NG  おそらく意図通りには動かない
                                // この行でもa == 0(++aは効果がない)
```

* C++03のテンプレートの実装でよく使われたsizeofによるディスパッチを行わない。

```cpp
    //  example/programming_convention/operator_ut.cpp 297

    // 下記のようなsizeofディスパッチはC++03ではよく使われたが、
    // C++11ではtype_traitsを使えば、もっとスマートに実装できる
    struct True {
        uint8_t temp[2];
    };
    struct False {
        uint8_t temp[1];
    };

    constexpr True  sizeof_dispatch(int32_t);
    constexpr False sizeof_dispatch(...);
```
```cpp
    //  example/programming_convention/operator_ut.cpp 314

    static_assert(sizeof(sizeof_dispatch(int{})) == sizeof(True), "int32_t is int");
    static_assert(sizeof(sizeof_dispatch(std::string{})) != sizeof(True), "int32_t is not string");

    // 上記はC++11では下記のように実装すべき
    static_assert(std::is_same_v<int, int32_t>, "int32_t is int");
    static_assert(!std::is_same_v<std::string, int32_t>, "int32_t is not string");

```

* 一見、配列に見えるポインタをsizeofのオペランドにしない。
  (「[実引数/仮引数](programming_convention.md#SS_3_3_4)」参照)。

```cpp
    //  example/programming_convention/operator_ut.cpp 329

    void f(int8_t arg_array0[5], int8_t arg_array1[], int8_t (&arg_array2)[5]) noexcept
    {
        int8_t* ptr;
        int8_t  array[5];

        // arg_array0、arg_array1の型は、int8_t*
        // 従って、sizeof(arg_array0)の値は、sizeof(int8_t) * 5ではなく、sizeof(int8_t*)である

        // 64bit環境でコンパイルポインタサイズは8バイト
        static_assert(8 == sizeof(arg_array0), "arg_array0 is a pointer but an array");
        static_assert(8 == sizeof(arg_array1), "arg_array1 is a pointer but an array");
        static_assert(5 == sizeof(arg_array2), "arg_array2 is an array");
        static_assert(8 == sizeof(ptr), "ptr must be 8 bytes on 64bit environment");
        static_assert(5 == sizeof(array), "int8_t[5] is 5 bytes");
    }
```

* [演習-sizeof](exercise_q.md#SS_22_5_3)  

### ポインタ間の演算 <a id="SS_3_5_8"></a>
* 同一オブジェクト(配列等)の要素を指さないポインタ間の除算や比較をしない。

```cpp
    //  example/programming_convention/operator_ut.cpp 365

    int8_t  a0[5];
    int8_t  a1[5];
    int8_t* end0{&a0[5]};
    int8_t* end1{&a1[5]};

    for (int8_t* curr{a0}; curr < end0;  // OK currもend0もa0のどこかを指している
         ++curr) {
        *curr = 0;
    }

    for (int8_t* curr{a0}; curr < end1;  // NG currとend1は別々のオブジェクトを指している
         ++curr) {
        *curr = 0;
    }
```

### RTTI <a id="SS_3_5_9"></a>
* [Run-time Type Information](core_lang_spec.md#SS_19_4_10)を使用したラインタイム時の型による場合分けは、
  それ以外に解決方法がない場合や、実装が大幅にシンプルになる場合を除き行わない
  (「[等価性のセマンティクス](cpp_idioms.md#SS_21_5_1)」参照)。
    * 単体テストやロギングのでtypeidの使用は問題ない。
    * 派生クラスの型によって異なる動作にしたい場合には、仮想関数を使うか、
      [Visitor](design_pattern.md#SS_9_2_5)パターン等により実現できる。

```cpp
    //  example/programming_convention/operator_ut.cpp 385

    class Base {
    public:
        virtual ~Base() = default;
        // ...
    };

    class Derived_0 : public Base {
        // ...
    };

    class Derived_1 : public Base {
        // ...
    };

    // ...

    // NGの例
    void b_do_something(Base const& b) noexcept
    {
        auto name = std::string_view{typeid(b).name()};

        // bの実際の型を使った場合分けによる最悪のコード
        // dynamic_castによる場合分けも、下記のコードより大きく改善するわけではない
        if (name == "4Base") {  // マングリングされたBase
            // ...
        }
        else if (name == "9Derived_0") {  // マングリングされたDerived_0
            // ...
        }
        else if (name == "9Derived_1") {  // マングリングされたDerived_1
            // ...
        }
        else {
            assert(false);
        }
    }
```

```cpp
    //  example/programming_convention/operator_ut.cpp 473

    // OKの例
    // 上記のb_do_somethingにポリモーフィズムを適用しリファクタリング
    class Base {
    public:
        void DoSomething() noexcept { do_something(); }
        // ...
    private:
        virtual void do_something() noexcept
        {
            // ...
        }
    };

    class Derived_0 : public Base {
    private:
        virtual void do_something() noexcept override
        {
            // ...
        }
        // ...
    };

    class Derived_1 : public Base {
    public:
        virtual void do_something() noexcept override
        {
            // ...
        }
        // ...
    };

    // virtual Base::do_something()により醜悪なswitchが消えた
    void b_do_something(Base& b) noexcept { b.DoSomething(); }
```

* コンストラクタやデストラクタ内でRTTIの機能を使わない
  (「[コンストラクタ](programming_convention.md#SS_3_2_4_2)」、「[デストラクタ](programming_convention.md#SS_3_2_4_6)」参照)

* [演習-dynamic_castの削除](exercise_q.md#SS_22_5_4)  

### キャスト、暗黙の型変換 <a id="SS_3_5_10"></a>
* キャストが必要な式等は、設計レベルの問題を内包していることがほとんどであるため、設計を見直す。
* Cタイプキャストは使用しない。
* const_cast、 dynamic_castはそれ以外に解決方法がない場合や、
  実装が大幅にシンプルになる場合を除き使用しない。
* reinterpret_castはハードウエアレジスタ等のアドレスを表す目的以外で使用しない。
* ダウンキャストを行う目的でstatic_castを使用しない。

```cpp
    //  example/programming_convention/operator_ut.cpp 526
    class Base {
        // ...
    };

    class Derived : public Base {
        // ...
    };

    void f() noexcept
    {
        auto  d     = Derived{};
        Base* b_ptr = &d;  // ここまでは良い

        auto d_ptr = static_cast<Derived*>(b_ptr);  // ダウンキャスト、動作保証はない

    }
```

* strnlenや、memcpyのような例を除き、void\*への暗黙の型変換を行わない
  (これをすると、後にダウンキャストが必要になる)。

```cpp
    //  example/programming_convention/operator_ut.cpp 550

    class A {
    public:
        A() : str_{std::make_unique<std::string>("sample")}
        {
            // ...
        }

        ~A()
        {
            // ...
        }

    private:
        std::unique_ptr<std::string> str_;  // ~unique_ptr()は~A()から呼ばれる
    };

    class B;
```

```cpp
    //  example/programming_convention/operator_ut.cpp 578

    void* v = new A;  // 暗黙の型変換
                      // これ自体は問題ないが、vをdeleteすると
                      // A::~A()が呼び出されないためメモリリークする

    B* b = static_cast<B*>(v);  // ダウンキャストの一種で、極めて悪質なことが多い
                                // 実際、このコードの中にクラスBの定義はないが
                                // このようなことができてしまう

    delete v;          // このdeleleは、A::~A()を呼び出さない
```

* strnlenや、memcpyのような例を除き、配列からポインタへの暗黙の型変換をしない。
  配列を関数の仮引数にしたい場合は、配列へのリファレンスを使う。
  これにより、その関数内でも配列の長さが使用できる
  (「[実引数/仮引数](programming_convention.md#SS_3_3_4)」、
  「[sizeof](programming_convention.md#SS_3_5_7)」、「[関数型マクロ](programming_convention.md#SS_3_6_1)」参照)。

* [演習-キャスト](exercise_q.md#SS_22_5_5)  

## プリプロセッサ命令 <a id="SS_3_6"></a>
* `#include`を除き、プリプロセッサ命令を使用しない。
  特に関数内、クラス宣言内での#if/#ifdef等の使用は可読性を著しく低下させるため、
  それ以外の解決方法がない場合を除く使用しない。

```cpp
    //  example/programming_convention/preprocessor_ut.cpp 14

    bool f() noexcept
    {
    #ifdef DEBUG  // NG
        std::cout << __func__ << ":" << __LINE__ << std::endl;
    #endif

        // ...

    #if 0  // NG
        return true;
    #else  // NG
        return false;
    #endif
    }

    // やむを得ず条件付きコンパイルが必要な場合、下記のように書き、関数ブロックの中に
    // #ifdefは書かない。

    #ifdef DEBUG
    #define DEBUG_COUT() std::cout << __func__ << ":" << __LINE__ << std::endl
    #else
    #define DEBUG_COUT()
    #endif

    bool g() noexcept
    {
        DEBUG_COUT();

        // ...

        return false;
    }

```

* ヘッダファイル内での#if/#ifdef/#ifndefに関しては、以下の用途以外では使わない。
    * 二重インクルードガード(「[二重読み込みの防御](programming_convention.md#SS_3_7_3)」参照)
    * Cとシェアするヘッダファイルでの下記例


```cpp
    //  example/programming_convention/preprocessor.h 3

    #ifdef __cplusplus
    extern "C" {
    #endif  // __cplusplus

    extern bool func_shared_c();

    #ifdef __cplusplus
    }
    #endif  // __cplusplus
```

* ##によるシンボルの生成を使用しない。

```cpp
    //  example/programming_convention/preprocessor_ut.cpp 53

    #define GEN_SYMBOL(x_, y_) x_##y_

    int32_t h() noexcept
    {
        int32_t GEN_SYMBOL(a, b);  // int ab;と同じ

        ab = 3;

        return ab;
    }
```

* 出荷仕向け等の理由から、やむを得ずプリプロセッサ命令を使わざるを得ない場合、
  #if等で囲まれた区間をなるべく短くする。
  これによりより多くのコードがコンパイルされるようにできる
  (「[using宣言/usingディレクティブ](programming_convention.md#SS_3_8_3)」参照)。

```cpp
    //  example/programming_convention/preprocessor_ut.cpp 72
    //
    // ヘッダファイルでの宣言(NGのパターン)
    //

    enum class ShippingRegions { Japan, US, EU };

    struct ShippingData {
        // 何らかの宣言
    };

    void ShippingDoSomething(ShippingData const& region_data);

    #if defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // NG

    constexpr ShippingRegions shipping_region = ShippingRegions::Japan;

    ShippingData const region_data{
        // 何らかのデータ
    };

    #elif !defined(SHIP_TO_JAPAN) && defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // NG

    constexpr ShippingRegions shipping_region = ShippingRegions::US;
    ShippingData const region_data{
        // 何らかのデータ
    };

    #elif !defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && defined(SHIP_TO_EU)  // NG

    constexpr ShippingRegions shipping_region = ShippingRegions::EU;
    ShippingData const        region_data{
        // 何らかのデータ
    };

    #else
    static_assert(false, "SHIP_TO_JAPAN/US/EU must be defined");
    #endif

    //
    // .cppファイルでの定義(NGのパターン)
    //
    void ShippingDoSomething(ShippingData const& region_data)
    {
    #if defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // NG
        // 何らかの処理
    #elif !defined(SHIP_TO_JAPAN) && defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // NG
        // 何らかの処理
    #elif !defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && defined(SHIP_TO_EU)  // NG
        // 何らかの処理
    #else
        static_assert(false, "SHIP_TO_JAPAN/US/EU must be defined");
    #endif
    }
```
```cpp
    //  example/programming_convention/preprocessor_ut.cpp 140
    //
    // ヘッダファイルでの宣言(OKのパターン)
    //

    enum class ShippingRegions { Japan, US, EU };

    struct ShippingData {
        // 何らかの宣言
    };
    void ShippingDoSomething(ShippingData const& region_data);

    extern ShippingData const& region_data;

    #if defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // OK

    constexpr ShippingRegions shipping_region = ShippingRegions::Japan;

    #elif !defined(SHIP_TO_JAPAN) && defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // OK

    constexpr ShippingRegions shipping_region = ShippingRegions::US;

    #elif !defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && defined(SHIP_TO_EU)  // OK

    constexpr ShippingRegions shipping_region = ShippingRegions::EU;

    #else
    static_assert(false, "SHIP_TO_JAPAN/US/EU must be defined");
    #endif

    //
    // .cppファイルでの定義(OKのパターン、以下にはプリプロセッサ命令は出てこない)
    //

    void ShippingDoSomething(ShippingData const& region_data)
    {
        if constexpr (shipping_region == ShippingRegions::Japan) {
            // 何らかの処理
        }
        else if constexpr (shipping_region == ShippingRegions::US) {
            // 何らかの処理
        }
        else if constexpr (shipping_region == ShippingRegions::EU) {
            // 何らかの処理
        }
        else {
            static_assert(shipping_region == ShippingRegions::Japan || shipping_region == ShippingRegions::US
                          || shipping_region == ShippingRegions::EU);
        }
    }

    template <ShippingRegions sr>
    ShippingData const& gen_shipping_data()
    {
        if constexpr (sr == ShippingRegions::Japan) {
            static ShippingData const region_data{
                // 何らかのデータ
            };
            return region_data;
        }
        else if constexpr (sr == ShippingRegions::US) {
            static ShippingData const region_data{
                // 何らかのデータ
            };
            return region_data;
        }
        else if constexpr (sr == ShippingRegions::EU) {
            static ShippingData const region_data{
                // 何らかのデータ
            };
            return region_data;
        }
        else {
            static_assert(sr == ShippingRegions::Japan || sr == ShippingRegions::US || sr == ShippingRegions::EU);
        }
    }

    ShippingData const& region_data = gen_shipping_data<shipping_region>();
```

### 関数型マクロ <a id="SS_3_6_1"></a>
* 関数型マクロ以外に方法がない場合を除き、関数型マクロを定義しない。
  その代わりに関数テンプレートを定義する。こうすることで下記のような誤用を防ぐことができる。

```cpp
    //  example/programming_convention/preprocessor_ut.cpp 240

    #define ARRAY_LENGTH(array_) (sizeof(array_) / sizeof(array_[0]))  // NG

    template <typename T, size_t N>  // OK
    constexpr size_t array_length(T const (&)[N]) noexcept
    {
        return N;
    }

    // arrayは配列へのリファレンスだが関数中では配列
    size_t f0(bool use_macro, int32_t (&array)[5]) noexcept
    {
        if (use_macro) {
            return ARRAY_LENGTH(array);  // この場合は、関数型マクロでも正しく処理できるが好ましくない
        }
        else {
            return array_length(array);  // OK
        }
    }

    // fake_arrayは配列に見えるが実際にはポインタ
    size_t f1(bool use_macro, int32_t fake_array[5]) noexcept
    {
        if (use_macro) {
            return ARRAY_LENGTH(fake_array);  // NG 誤用でもコンパイルできてしまい不正値を返す
        }
        else {
            // return  array_length(fake_array); // OK 誤用のためコンパイルエラー
            auto array = reinterpret_cast<int32_t(*)[5]>(fake_array);  // 無理やりコンパイル
            return array_length(*array);
        }
    }
```

* 関数型マクロの中に文がある場合、do-while(0)イデオムを使用する
  (「[マクロの中の文](programming_convention.md#SS_3_4_10)」参照)。

### マクロ定数 <a id="SS_3_6_2"></a>
* マクロ定数以外に方法がない場合を除き、マクロ定数を定義しない。
  その代わりにconstexpr uint32\_t等や、enumを定義する。

```cpp
    //  example/programming_convention/preprocessor_ut.cpp 291

    #define XXX_LENGHT 5  // NG

    constexpr uint32_t YyyLenght{5};  // OK

    #define XXX_TYPE_A 0  // NG
    #define XXX_TYPE_B 1  // NG
    #define XXX_TYPE_C 2  // NG

    enum class XxxType {  // OK
        A = 0,            //      Aの値が必要だと前提
        B,
        C
    };
```

## ソースコードファイルとディレクトリ <a id="SS_3_7"></a>

- ソースコードファイル全体は、適切に[パッケージ](cpp_idioms.md#SS_21_9_2)に分割する。
- ソースコードファイルの最小構成は[ファイルペア](cpp_idioms.md#SS_21_9_1)を形成しなければならない。

<!-- pu:practical/plant_uml/package.pu--><p><img src="data:image/png;base64,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" /></p>


### 識別子の宣言、定義 <a id="SS_3_7_1"></a>
* [ODR](https://en.cppreference.com/w/cpp/language/definition)を守る。
  つまり、一つの識別子は全ソースコード内にただ一つの定義を持つようにする。
* 一つの.cppファイル内のみで使用される識別子は、
  その.cppファイル内の無名名前空間にその定義や宣言を持つ。
* [ファイルペア](cpp_idioms.md#SS_21_9_1)の実装ファイルは、対応するヘッダファイルをインクルードしなければならない。

### 依存関係 <a id="SS_3_7_2"></a>
* 不要/不適切な依存関係(「[インターフェース分離の原則(ISP)](solid.md#SS_8_4)」や
  「[依存関係逆転の原則(DIP)](solid.md#SS_8_5)」への違反)を作らない。

    * SOLIDの原則やデザインパターン、イデオム等を適切に使用することにより、依存関係を適切に保つ。
        * 依存関係の伝搬を回避したい場合、[Pimpl](cpp_idioms.md#SS_21_2_1)イデオムを使い実装の詳細を隠蔽する。
        * 上位概念が下位概念に依存することを避ける場合、
          「[依存関係逆転の原則(DIP)](solid.md#SS_8_5)」での例や[Observer](design_pattern.md#SS_9_2_4)等を適用する。
    * パッケージ間の依存関係は、[非循環依存の原則(ADP)](cpp_idioms.md#SS_21_8_4)を守る。

<!-- pu:practical/plant_uml/package_ng.pu--><p><img src="data:image/png;base64,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" /></p>

* ヘッダファイル間の依存関係を最小にとどめるために、
  前方宣言や[前方宣言ヘッダ(`_fwd.h`)](cpp_idioms.md#SS_21_1_2)イディオムやを適切に使用する。

* 標準ライブラリのクラス(class, struct, enum, enum class)の前方宣言をしない
  (例えば、「std::stringをクラス宣言することでstringヘッダファイルへの依存関係を作らない」
  といった方法は、std::stringはstd::basic_stringのエイリアスであり、その実装は規格で規定されていない。
  このような前方宣言を行うと[ODR](core_lang_spec.md#SS_19_14_10)違反による[未定義動作](core_lang_spec.md#SS_19_14_3)につながる可能性がある)。
  `<ios>`で宣言される型は`<iosfwd>`で前方宣言されている)。


### 二重読み込みの防御 <a id="SS_3_7_3"></a>
* 二重インクルードを防ぐため、 ヘッダファイルには#includeガードを付ける。
  ガード用のマクロは、<パス名>\_<ファイル名>\_H\_とする。

```cpp
    //  example/programming_convention/lib/inc/xxx.h 1

    // lib/inc/xxx.hでの#includeガード

    #ifndef LIB_INC_XXX_H_
    #define LIB_INC_XXX_H_

    extern void XxxInitialize();

    // ...

    #endif  // LIB_INC_XXX_H_
```

* コンパイラが#pragma onceをサポートしている場合は、
  上記方法ではなく下記をヘッダファイル先頭に記述する。

```cpp
    //  example/programming_convention/lib/inc/xxx.h 16

    #pragma once
```

### ヘッダファイル内の#include <a id="SS_3_7_4"></a>
* 不要な依存関係を作らないようにするため、ヘッダファイルは、そのコンパイルに不要なヘッダファイルをインクルードしない。
* ヘッダファイルは、それがインクルードするヘッダファイルを含めて、単体でコンパイルできなければならない。
* ヘッダファイルが外部からインポートする型(class、struct、enum)
  のデリファレンスがそのヘッダファイル内で不要な場合、
  前方宣言や[前方宣言ヘッダ(`_fwd.h`)](cpp_idioms.md#SS_21_1_2)を使い依存関係を小さくする。 

```cpp
    //  example/programming_convention/header.h 3

    // Pod0, Pod1の定義は別ファイルでされていると前提。
    struct Pod0;
    struct Pod1;

    // 下記関数宣言のコンパイルには、Pod0、Pod1の完全な定義は必要ない。
    extern void forward_decl(Pod0 const* pod_0, Pod1* pod_1) noexcept;
    extern Pod1 forward_decl(Pod0 const* pod_0) noexcept;
    extern void forward_decl(Pod0 pod_0) noexcept;
```

```cpp
    //  example/programming_convention/header_ut.cpp 12

    // Pod0, Pod1の定義がなくても宣言があるためコンパイルできる
    forward_decl(nullptr, nullptr);

    // 下記のソースコードのコンパイルには、Pod0の定義が必要なのでコンパイルできない
    // forward_decl(nullptr);
```

### #includeするファイルの順番 <a id="SS_3_7_5"></a>
* ユーザ定義ヘッダファイルより、システムヘッダファイルの#includeを先に行う。
* システムヘッダファイルは、アルファベット順に#includeを行う。
* ユーザ定義ヘッダファイルは、アルファベット順に#includeを行う。

### #includeで指定するパス名 <a id="SS_3_7_6"></a>
* ユーザ定義のヘッダファイルは""で囲み、システムヘッダファイルは、`<>`で囲む。
* 他のパッケージの外部非公開ヘッダファイルを読み込まないようにするために、
  #includeのパス指定に"../"(ディレクトリ上方向への移動)を使用しない。

```cpp
    //  example/programming_convention/lib/header.cpp 1

    #include <string>  // OK

    #include "../h/suppress_warning.h"  // NG   上方向へのファイルパスは禁止

    #include "../header.h"  // NG   上方向へのファイルパスは禁止
    #include "inc/xxx.h"    // OK
```

* ヘッダファイル以外のファイル(.cppファイル等)をインクルードしない。

## スコープ <a id="SS_3_8"></a>
### スコープの定義と原則 <a id="SS_3_8_1"></a>
この章で扱うスコープを下記のように定義する(「[ソースコードファイルとディレクトリ](programming_convention.md#SS_3_7)」参照)。

1. グローバル
2. [パッケージ](cpp_idioms.md#SS_21_9_2)外部公開名前空間
3. [パッケージ](cpp_idioms.md#SS_21_9_2)外部非公開名前空間
4. ファイル(無名名前空間と関数外static)
5. クラス内
6. 関数内
7. ブロック内

リンクの観点からは、2と3の識別子は同じスコープを持つが、
その識別子は[パッケージ](cpp_idioms.md#SS_21_9_2)外部非公開なヘッダファイルに宣言、定義されているため、
パッケージ外から(まともな方法では)アクセスできない。

* 識別子のスコープは最小になるように宣言する。
    * 1のスコープを持つ識別子を宣言しない(特にグローバルなスコープ内のオブジェクトを宣言・定義しない)。
    * 2、3のスコープを持つ静的な変数を宣言しない。
    * パッケージ外部公開ヘッダファイルでの識別子の宣言、定義を最小にする。
    * クラス内部でのみ使用される識別子は、privateもしくはprotectedで宣言する。
    * 一つの.cppファイルのみで使用する識別子は、
      その.cppファイル内の無名名前空間で宣言、定義する(staticを使用しない)。
    * 単一関数のみで使用する変数は、その関数内で定義する。
    * 自動変数は、使用直前に定義する。

* このドキュメント執筆時のコンパイラ/ビルダのC++20での[モジュール](core_lang_spec.md#SS_19_10_2)のサポート状況が
  万全ではないため、
    * モジュールを定義するためのmoduleを使用しない。
    * モジュール外に公開する識別子を定義するexport使用しない。
    * exportされた識別子を使用するためにimportを使用しない。

* [name-hiding](core_lang_spec.md#SS_19_12_9)を起こすとコードの可読性が著しく低下するため、
  スコープが重複する「名前のない名前空間内」(例えば、ブロックとそれを内包するブロック)
  にある「同一名を持つ識別子」を宣言、定義しない。

```cpp
    //  example/programming_convention/scope.h 7

    extern uint32_t xxx;  // NG 外部から参照可能な静的変数
    extern uint64_t yyy;  // NG 同上
```

```cpp
    //  example/programming_convention/scope_ut.cpp 18

    uint32_t xxx;  // NG 外部から参照可能な静的変数
    uint32_t yyy;  // NG 同上

    uint32_t f(uint32_t yyy) noexcept
    {
        auto xxx = 0;  // NG 関数外xxxと関数内xxxのスコープが重なっており区別が付きづらい

        return xxx + yyy;
    }
    // なお、
    //  scope.h内では、  uint64_t yyy;
    //  scope.cpp内では、uint32_t yyy;
    //  となっており、宣言と定義が矛盾している。
    //  この問題は、このファイルからscope.hをインクルードすれば防げる。
```

### 名前空間 <a id="SS_3_8_2"></a>
* グローバル名前空間には下記以外の識別子を定義、宣言しない。
    * main関数
    * グローバルnewのオーバーロード
    * Cとシェアする識別子
* [パッケージ](cpp_idioms.md#SS_21_9_2)毎に名前空間を定義する
  (「[ソースコードファイルとディレクトリ](programming_convention.md#SS_3_7)」、[名前空間名](naming_practice.md#SS_6_2_11)」参照)。
* 外部リンケージの不要な識別子は.cpp内の無名名前空間で宣言、定義する。
* 名前空間Xxx内で定義されたテンプレートやinline関数から参照されるため、
  外部公開用ではないにもかかわらずヘッダファイル内に定義が必要な識別子は、
  名前空間Xxx::Inner\_内で定義する。
  名前空間Xxx::Inner\_内の識別子は、単体テストを除き他のファイルから参照しない。

```cpp
    //  example/programming_convention/scope2.h 9

    template <size_t N>
    class StaticString {  // StaticStringは外部公開
        // ...
    };

    namespace Inner_ {  // equal_nは外部非公開
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

    template <size_t N1, size_t N2>  // operator==は外部公開
    constexpr bool operator==(StaticString<N1> const&, StaticString<N2> const&) noexcept
    {
        return false;
    }

    template <size_t N>  // operator==は外部公開
    constexpr bool operator==(StaticString<N> const& lhs, StaticString<N> const& rhs) noexcept
    {
        return Inner_::equal_n(0, lhs, rhs);
    }
```

### using宣言/usingディレクティブ <a id="SS_3_8_3"></a>
* 識別子のインポートのための[using宣言](core_lang_spec.md#SS_19_12_14)は下記のような場合のみに使用する
  (「[継承コンストラクタ](core_lang_spec.md#SS_19_6_1_2)」、「[オーバーライドとオーバーロードの違い](cpp_idioms.md#SS_21_13_1)」参照)。

```cpp
    //  example/programming_convention/scope_ut.cpp 55

    using std::string;         // NG この関数内でのstd::stringの使用箇所が少ないのであれば、
                               //    using宣言ではなく、名前修飾する
    auto s_0 = string{"str"};  // NG
    auto s_1 = std::string{"str"};  // OK

    // 大量のstd::stringリテラルを使用する場合
    using std::literals::string_literals::operator""s;  // OK

    auto s_2 = "str"s;  // OK
    // ...
    auto s_N = "str"s;  // OK

    // クラス内でのusing宣言
    struct Base {
        void f(){};
    };

    struct Derived : Base {
        using Base::Base;  // OK 継承コンストラクタ
        using Base::f;     // OK B::fのインポート
        void f(int){};
    };
```

* 下記のような場合を除き、[usingディレクティブ](core_lang_spec.md#SS_19_12_15)は使用しない。
  使用する場合でもその効果をブロックスコープ内のみに留める。

```cpp
    //  example/programming_convention/scope_ut.cpp 84

    using namespace std;  // NG

    auto s0 = string{"str"};

    auto s1 = std::literals::string_literals::operator""s("str", 3);  // NG
    static_assert(std::is_same_v<std::string, decltype(s1)>);

    using namespace std::literals::string_literals;  // OK 例外的にOK

    auto s2 = "str"s;
    static_assert(std::is_same_v<std::string, decltype(s2)>);
```

* 出荷仕向け等の理由を除き、inline namespaceを使用しない(「[プリプロセッサ命令](programming_convention.md#SS_3_6)」参照)。

```cpp
    //  example/programming_convention/scope_ut.cpp 106

    namespace XxxLib {
    namespace OldVersion {
    int32_t f() noexcept
    {
        // ...
    }
    }  // namespace OldVersion

    inline namespace NewVersion {  // NG inline
    int32_t f() noexcept
    {
        // ...
    }
    }  // namespace NewVersion

    int32_t g() noexcept
    {
        return f();  // NG NewVersion::f()が呼ばれる。
    }
```
```cpp
    //  example/programming_convention/scope_ut.cpp 141
    // 例外的にOKな例

    #if defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // OK
    #define INLINE_JAPAN inline                                                 // OK
    #define INLINE_US
    #define INLINE_EU

    #elif !defined(SHIP_TO_JAPAN) && defined(SHIP_TO_US) && !defined(SHIP_TO_EU)  // OK
    #define INLINE_JAPAN
    #define INLINE_US inline  // OK
    #define INLINE_EU

    #elif !defined(SHIP_TO_JAPAN) && !defined(SHIP_TO_US) && defined(SHIP_TO_EU)  // OK
    #define INLINE_JAPAN
    #define INLINE_US
    #define INLINE_EU inline  // OK

    #else
    static_assert(false, "SHIP_TO_JAPAN/US/EU must be defined");
    #endif

    namespace Shipping {
    INLINE_JAPAN namespace Japan  // OK
    {
        int32_t DoSomething() { return 0; }
    }

    INLINE_US namespace US  // OK
    {
        int32_t DoSomething() { return 1; }
    }

    INLINE_EU namespace EU  // OK
    {
        int32_t DoSomething() { return 2; }
    }
    }  // namespace Shipping
```
```cpp
    //  example/programming_convention/scope_ut.cpp 183

    // SHIP_TO_JAPAN/US/EUを切り替えることで、対応したDoSomethingが呼ばれる
    // この例ではSHIP_TO_JAPANが定義されているため、Shipping::Japan::DoSomethingが呼ばれる
    ASSERT_EQ(0, Shipping::DoSomething());

    // 名前修飾することで、すべてのDoSomethingにアクセスできるため、単体テストも容易
    ASSERT_EQ(0, Shipping::Japan::DoSomething());
    ASSERT_EQ(1, Shipping::US::DoSomething());
    ASSERT_EQ(2, Shipping::EU::DoSomething());
```

* [演習-usingディレクティブ](exercise_q.md#SS_22_6_1)  

### ADLと名前空間による修飾の省略 <a id="SS_3_8_4"></a>
* 名前空間の修飾を省略した識別子のアクセスには、
  下記のような副作用があるため、[ADL](core_lang_spec.md#SS_19_12_5)を使用する目的以外で使用しない
  (「[識別子の命名](naming_practice.md#SS_6_2)」を順守することで、識別子の偶然の一致を避けることも必要)。

```cpp
    //  example/programming_convention/scope_ut.cpp 200

    namespace NS_0 {
    class X {};

    std::string f(X, int32_t)  // 第2引数int32_t
    {
        return "in NS_0";
    }
    }  // namespace NS_0

    namespace NS_1 {

    std::string f(NS_0::X, uint32_t)  // 第2引数uint32_t
    {
        return "in NS_1";
    }
    }  // namespace NS_1
```
```cpp
    //  example/programming_convention/scope_ut.cpp 222

    // 関数fの探索名前空間には、
    //  * 第1引数の名前空間がNS_0であるため、ADLにより、
    //  * この関数の宣言がNS_1で行われているため、
    // NS_0、NS_1が含まれる。
    // これにより、下記fの候補は、NS_0::f、NS_1::fになるが、第2引数1がint32_t型であるため、
    // 名前修飾なしでのfの呼び出しは、NS_0::fが選択される。

    using namespace NS_1;  // この宣言があるにもかかわらず、f(NS_0::X(), 1)のNS_0::fではない

    ASSERT_EQ("in NS_0", f(NS_0::X(), 1));        // NS_0::fが呼ばれる。
    ASSERT_EQ("in NS_1", NS_1::f(NS_0::X(), 1));  // NS_1::fの呼び出しには名前修飾が必要
```

### 名前空間のエイリアス <a id="SS_3_8_5"></a>
* ネストされた長い名前空間を短く簡潔に書くための名前空間エイリアスは、
  その効果をブロックスコープ内のみに留める。
* 名前空間のエイリアスを[using宣言/usingディレクティブ](programming_convention.md#SS_3_8_3)で使用しない。

```cpp
    //  example/programming_convention/scope_ut.cpp 241

    std::vector<std::string> find_files_recursively(std::string const&                                path,
                                                    std::function<bool(std::filesystem::path const&)> condition)
    {
        namespace fs = std::filesystem;  // OK 長い名前を短く

        auto files  = std::vector<std::string>{};
        auto parent = fs::path{path.c_str()};

        using namespace fs;  // NG エイリアスをusing namespaceで使用しない

        std::for_each(fs::recursive_directory_iterator{parent},  // OK namespaceエイリアス
                      fs::recursive_directory_iterator{},        // OK namespaceエイリアス
                      // ...
        );

        using fs::recursive_directory_iterator;  // NG エイリアスをusing宣言で使用しない

        std::for_each(recursive_directory_iterator{parent},  // NG
                      recursive_directory_iterator{},        // NG
                      // ...
        );

        return files;
    }
```

## ランタイムの効率 <a id="SS_3_9"></a>
* ランタイム効率と、可読性のトレードオフが発生する場合、可読性を優先させる。
* やむを得ず可読性を落とすコードオプティマイゼーションを行う場合は、
  プロファイリング等を行い、ボトルネックを確定させ、必要最低限に留める。
  また、開発早期での可読性を落とすコードオプティマイゼーションは行わない。

### 前置/後置演算子の選択 <a id="SS_3_9_1"></a>
* 後置演算子の一般的な動作は、下記のようになるため前置演算子の実行に比べて処理が多い。
  どちらを使用してもよい場合は前置演算子を使う。
    1. 自分(オブジェクト)をコピーする。
    2. 自分に前置演算子を実行する。
    3. コピーされたオブジェクトを返す。

```cpp
    //  example/programming_convention/runtime_ut.cpp 11

    class A {
    public:
        A& operator++() noexcept  // 前置++
        {
            ++a_;  // メンバ変数のインクリメント
            return *this;
        }

        A operator++(int) noexcept  // 後置++
        {
            A old{*this};  // リターンするためのオブジェクト
            ++(*this);     // 前置++
            return old;    // oldオブジェクトのリターン(オブジェクトのコピー)
        }

        operator int() const noexcept { return a_; }

    private:
        int32_t a_{0};
    };
```
```cpp
    //  example/h/measure_performance.h 4

    // パフォーマンス測定用
    template <typename FUNC>
    std::chrono::milliseconds MeasurePerformance(uint32_t count, FUNC f)
    {
        auto const start = std::chrono::system_clock::now();

        for (auto i = 0U; i < count; ++i) {
            f();
        }

        auto const stop = std::chrono::system_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    }
```
```cpp
    //  example/programming_convention/runtime_ut.cpp 37

    constexpr auto count = 10000000U;

    auto a_post = A{};
    auto post   = MeasurePerformance(count, [&a_post] {
        a_post++;  // NG 効率が悪い
    });

    auto a_pre = A{};
    auto pre   = MeasurePerformance(count, [&a_pre] {
        ++a_pre;  // OK 上記に比べると効率が良い
    });

    ASSERT_GT(post, pre);  // 前置++の処理は後置++より効率が良い

    std::cout << "pre :" << pre.count() << " msec" << std::endl;
    std::cout << "post:" << post.count() << " msec" << std::endl;

    // 私の環境では以下のような出力が得られた
    // pre :24 msec
    // post:37 msec
```

* ソースコードの統一性のため、このオーバーヘッドがない基本型についても、同じルールを適用する。

### operator X、operator x=の選択 <a id="SS_3_9_2"></a>
* 前置/後置演算子と同じような問題が発生するため、どちらを使っても問題ない場合は、
  operator Xではなく、operator X=を使う。

```cpp
    //  example/programming_convention/runtime_ut.cpp 70

    class A {
    public:
        explicit A(int32_t a) noexcept : a_{a} {}

        A& operator+=(A const& rhs) noexcept
        {
            a_ += rhs.a_;
            return *this;
        }
        // ...
        friend A operator+(A const& lhs, A const& rhs) noexcept  // メンバ関数に見えるが、非メンバ関数
        {
            A tmp{lhs};  // operator +=に対して、
            tmp += rhs;  // 「tmpを作り、それを返す]をしなければならない。
            return tmp;
        }
    };

```
```cpp
    //  example/programming_convention/runtime_ut.cpp 101

    auto a = A{1};
    auto b = A{2};

    a = a + b;  // NG 無駄なコピーが発生する
    ASSERT_EQ(a.Value(), 3);

    a += b;  // OK 無駄なコピーが発生しない
    ASSERT_EQ(a.Value(), 5);
```

* ソースコードの統一性のため、このオーバーヘッドがない基本型についても、同じルー ルを適用する。

### 関数の戻り値オブジェクト <a id="SS_3_9_3"></a>
* 戻り値型は「[関数の引数と戻り値の型](cpp_idioms.md#SS_21_6_1)」に従う。


### move処理 <a id="SS_3_9_4"></a>
* [ディープコピー](cpp_idioms.md#SS_21_12_2)の実装を持つクラスへのcopy代入の多くがrvalueから行われるのであれば、
  moveコンストラクタや、move代入演算子も実装する。
* 関数の戻り値にローカルオブジェクトを使用する場合、
  [RVO(Return Value Optimization)](core_lang_spec.md#SS_19_15_1)の阻害になるため、そのオブジェクトをstd::moveしない。

```cpp
    //  example/programming_convention/runtime_ut.cpp 119

    std::string MakeString(int a, int b)
    {
        auto ret = std::string{};

        // ...
        // 文字列操作
        // ...

    #if 0
        // NG
        // std::moveのため、RVOが抑止される。
        // -Wpessimizing-moveを指定してg++/clang++でコンパイルすれば、
        // "moving a local object in a return statement prevents copy elision"
        // という警告が出る。

        return std::move(ret);
    #else
        // OK
        // ローカルオブジェクトには通常RVOが行われるため、std::moveするよりも無駄が少ない。

        return ret;
    #endif
    }
```

### std::string vs std::string const& vs std::string_view <a id="SS_3_9_5"></a>
* 文字列を受け取る関数の仮引数の型に関しては下記のような観点に気を付ける。
  以下に示す通り、このような仮引数の型をstd::string const&にすることが最適であるとは限らない。

```cpp
    //  example/programming_convention/runtime_ut.cpp 156
    // テスト０用関数

    void f0(std::string const& str) { /* strを使用した何らかの処理 */ }
    void f1(std::string str)        { /* strを使用した何らかの処理 */ }
    void f2(std::string_view str)   { /* strを使用した何らかの処理 */ }
```
```cpp
    //  example/programming_convention/runtime_ut.cpp 169
    // テスト０―０

    auto str     = std::string{__func__};
    auto f0_msec = MeasurePerformance(10000000, [&str] { f0(str); });
    auto f1_msec = MeasurePerformance(10000000, [&str] { f1(str); });
    auto f2_msec = MeasurePerformance(10000000, [&str] { f2(str); });

    // このドキュメントを開発しているPCでは上記の結果は以下の様になる。
    // f0 : 50 msec
    // f1 :222 msec
    // f2 : 55 msec
    // つまり、f0 < f2 < f1であり、f0とf2は大差がなく、f1は極めて非効率である。
    // 従って、文字列リテラルを関数に渡す場合の引数の型は、
    // std::string const&か、std::string_viewとするのが効率的である。
```
```cpp
    //  example/programming_convention/runtime_ut.cpp 193
    // テスト０―１

    auto f0_msec = MeasurePerformance(10000000, [] { f0(__func__); });
    auto f1_msec = MeasurePerformance(10000000, [] { f1(__func__); });
    auto f2_msec = MeasurePerformance(10000000, [] { f2(__func__); });

    // このドキュメントを開発しているPCでは上記の結果は以下の様になる。
    // f0 :674 msec
    // f1 :662 msec
    // f2 :115 msec
    // つまり、f2 < f1 < f0であり、f0、f1は極めて非効率である。
    // 従って、文字列を関数に渡す場合の引数の型は、std::string_viewとするのが効率的である。
    //
    // テスト０―０、テスト０―１の結果から、
    //   * 文字列リテラルからstd::string型テンポラリオブジェクトを作るような呼び出しが多い場合、
    //     std::string_view
    //   * 上記のような呼び出しがほとんどない場合、std::string const&
    // を引数型とすべきである。
    // 使用方法が想定できない場合、極めて非効率なテスト０－１のf0のパターンを避けるため、
    // std::string_viewを選択すべきだろう。
```
```cpp
    //  example/programming_convention/runtime_ut.cpp 222
    // テスト１用クラス

    class A0 {
    public:
        A0(std::string const& str) : str_{str} {}

    private:
        std::string str_;
    };

    class A1 {
    public:
        A1(std::string str) : str_{std::move(str)} {}  // strの一時オブジェクトをmoveで利用

    private:
        std::string str_;
    };

    class A2 {
    public:
        A2(std::string_view str) : str_{str} {}

    private:
        std::string str_;
    };
```
```cpp
    //  example/programming_convention/runtime_ut.cpp 253
    // テスト１―０

    auto str     = std::string{__func__};
    auto a0_msec = MeasurePerformance(10000000, [&str] { A0 a{str}; });
    auto a1_msec = MeasurePerformance(10000000, [&str] { A1 a{str}; });
    auto a2_msec = MeasurePerformance(10000000, [&str] { A2 a{str}; });

    // このドキュメントを開発しているPCでは上記の結果は以下の様になる。
    // A0 :258 msec
    // A1 :314 msec
    // A2 :683 msec
    // つまり、A0 < A1 < A2であり、A0とA1は大差がなく、A2は極めて非効率である。
    // 従って、stringオブジェクトを関数に渡す場合の引数の型は、
    // std::string const&か、std::stringとするのが効率的である。
```
```cpp
    //  example/programming_convention/runtime_ut.cpp 277
    // テスト１―１

    auto a0_msec = MeasurePerformance(10000000, [] { A0 a{__func__}; });
    auto a1_msec = MeasurePerformance(10000000, [] { A1 a{__func__}; });
    auto a2_msec = MeasurePerformance(10000000, [] { A2 a{__func__}; });

    // このドキュメントを開発しているPCでは上記の結果は以下の様になる。
    // A0 :834 msec
    // A1 :774 msec
    // A2 :704 msec
    // つまり、A2 < A1 < A0であり、A0の効率がやや悪い。
    // 従って、文字列リテラルを関数に渡す場合の引数の型は、
    // std::stringか、std::string_viewとするのが効率的である。
    //
    // コンストラクタのインターフェースとしては、
    // 実引数オブジェクトのライフタイムを考慮しなくて良いため、A0よりもA1の方が優れている。
    // この観点と、テスト１－０、テスト１－１の結果を総合的に考えれば、
    // このような場合の引数の型は、std::stringを選択すべきだろう。
```

### extern template <a id="SS_3_9_6"></a>
* 何度もインスタンス化が行われ、
  それによりROMの肥大化やビルドの長時間化を引き起こすようなクラステンプレートに対しては、
  extern templateを使う。

```cpp
    //  example/programming_convention/string_vector.h 4

    // このファイルをインクルードすると、
    // そのファイルでのstd::vector<std::string>のインスタンス化は抑止される。
    extern template class std::vector<std::string>;
```
```cpp
    //  example/programming_convention/string_vector.cpp 3

    // std::vector<std::string>はこのファイルでインスタンス化される。
    template class std::vector<std::string>;
```

## 標準クラス、関数の使用制限 <a id="SS_3_10"></a>
### 標準ライブラリ <a id="SS_3_10_1"></a>
* C++のバージョン毎に定められた非推奨の機能、関数、クラスを使わない。
  これらについては、[C++日本語リファレンス](https://cpprefjp.github.io/)の
  * [C++11の機能変更](https://cpprefjp.github.io/lang/cpp11.html)
  * [C++14の機能変更](https://cpprefjp.github.io/lang/cpp14.html)
  * [C++17の機能変更](https://cpprefjp.github.io/lang/cpp17.html)
  に詳細が書かれている。

* [g++](cpp_idioms.md#SS_21_15_1)/[clang++](cpp_idioms.md#SS_21_15_2)等の優れたコンパイラを適切なオプションで使用することで、
  非推奨の機能、関数、クラスの使用を防ぐ。

#### スマートポインタの使用制限 <a id="SS_3_10_1_1"></a>
* std::auto_ptrを使用しない(C++17で廃止)。
* ダイナミックに生成した[オブジェクトの排他所有](cpp_idioms.md#SS_21_4_1)を行う場合、`std::unique_ptr<>`を使用する。
* ダイナミックに生成した[オブジェクトの共有所有](cpp_idioms.md#SS_21_4_2)を行う場合、`std::shared_ptr<>`を使用する。
* `std::shared_ptr<>`を使用する場合、[オブジェクトの循環所有](cpp_idioms.md#SS_21_4_3)が発生しないように気を付ける。

#### 配列系コンテナクラスの使用制限 <a id="SS_3_10_1_2"></a>
* 配列系のコンテナを使用する場合、コンパイル時に要素数の上限が
    * 定まるのであれば、std::arrayを使用する。
    * 未定ならば、std::vectorを使用する。
* `std::vector<bool>`は、std::vectorの特殊化であり、通常のstd::vectorと同じようには扱えない。
  `std::vector<bool>`を使用する場合、その要素へのハンドルがbool&やbool\*でないことに注意する。
* std::arrayを除くコンテナクラスは、
  それ自体でメモリリソースの[RAII(scoped guard)](cpp_idioms.md#SS_21_1_3)を実現しているため、newしない。

#### std::stringの使用制限 <a id="SS_3_10_1_3"></a>
* std::stringは、
  それ自体でメモリリソースの[RAII(scoped guard)](cpp_idioms.md#SS_21_1_3)を実現しているため、newしない。
* std::stringの添字演算子[]は領域外アクセスを通知しない
  ([std::out_of_range](https://cpprefjp.github.io/reference/stdexcept.html)
  エクセプションを発生させない)ため、std::string::at() を使用する
  (「[安全な配列型コンテナ](template_meta_programming.md#SS_13_2_3)」参照)。
* std::string.data()は、C++のバージョンによってはNULLターミネイトが保証されていないため、
  std::string.c_str() を使用する。

#### std::string_viewの使用制限 <a id="SS_3_10_1_4"></a>
* std::string_viewが保持するポインタが指す文字列の所有権は、他のオブジェクトが保持しているため、
  std::string_viewの初期化や、copy代入の右辺にrvalueを使用しない。

```cpp
    //  example/programming_convention/string_view_ut.cpp 11

    auto str = std::string{"abc"};
    auto sv  = std::string_view{str};  // OK lvalueからの初期化

    ASSERT_EQ(sv, std::string_view{"abc"});
```
```cpp
    //  example/programming_convention/string_view_ut.cpp 31

    std::string_view sv = std::string{"abc"};  // NG rvalueからの初期化
                                               //    この行でstd::string{"abc"}が解放
    ASSERT_EQ(sv, std::string_view{"abc"});    //    svは無効なポインタを保持
```

* 文字列リテラルで初期化されたstd::string_viewと文字列リテラルとの微妙な違いに気を付ける。

```cpp
    //  example/programming_convention/string_view_ut.cpp 43

    {  // 文字列リテラルを範囲として使用すると、ヌル文字が要素に含まれる
        auto oss = std::ostringstream{};

        for (char c : "abc") {
            oss << c;
        }

        ASSERT_EQ((std::string{'a', 'b', 'c', '\0'}), oss.str());  // ヌル文字が入る
    }
    {  // string_viewを使用すると、ヌル文字が要素に含まれない
        auto oss = std::ostringstream{};

        for (char c : std::string_view{"abc"}) {
            oss << c;
        }

        ASSERT_EQ((std::string{'a', 'b', 'c'}), oss.str());  // ヌル文字は入らない
    }
```
```cpp
    //  example/programming_convention/string_view_ut.cpp 65

    char const a[]{"123"};
    auto       b = std::string_view{"01234"}.substr(1, 3);  // インデックス1 - 3

    ASSERT_EQ(a, b);  // a == bが成り立つ

    auto oss_a = std::ostringstream{};
    oss_a << a;

    auto oss_b = std::ostringstream{};
    oss_b << b;

    ASSERT_EQ(oss_a.str(), oss_b.str());  // ここまでは予想通り

    // bをインデックスアクセスすると以下のようになる。
    ASSERT_EQ('0', b[-1]); ASSERT_EQ('1', b[0]); ASSERT_EQ('2',  b[1]);
    ASSERT_EQ('3',  b[2]); ASSERT_EQ('4', b[3]); ASSERT_EQ('\0', b[4]);

    // 上記の結果から、以下の結果になることには注意が必要
    auto oss_b_cstr = std::ostringstream{};
    oss_b_cstr << b.data();  // data()は文字列リテラルへのポインタを指す。

    ASSERT_NE(oss_a.str(), oss_b_cstr.str());
    ASSERT_EQ("123", oss_a.str());
    ASSERT_EQ("1234", oss_b_cstr.str());
```


### POSIX系関数 <a id="SS_3_10_2"></a>
#### 使用禁止関数一覧 <a id="SS_3_10_2_1"></a>

| 禁止関数                                      | 代替え                                        |
|:----------------------------------------------|:----------------------------------------------|
| alloca()                                      | コンテナ                                      |
| asctime()                                     | strftime()                                    |
| asctime_r()                                   | strftime()                                    |
| bcmp()                                        |                                               |
| bcopy()                                       |                                               |
| brk()                                         |                                               |
| bzero()                                       |                                               |
| ctermid()                                     |                                               |
| ctime()                                       | strftime()                                    |
| ctime\_r()                                    | strftime()                                    |
| cuserid()                                     |                                               |
| ecvt()                                        |                                               |
| execl()                                       | execle(), execve()                            |
| execlp()                                      | execle(), execve()                            |
| execv()                                       | execle(), execve()                            |
| execvp()                                      | execle(), execve()                            |
| fattach()                                     |                                               |
| fcvt()                                        |                                               |
| fdetach()                                     |                                               |
| ftw()                                         |                                               |
| gcvt()                                        |                                               |
| getc()                                        |                                               |
| getchar()                                     |                                               |
| getgrgid()                                    | getgrgir\_r()                                 |
| getgrnam()                                    | getgrnam\_r()                                 |
| getitimer()                                   |                                               |
| getlogin()                                    | getlogin\_r()                                 |
| getmsg()                                      |                                               |
| getopt()                                      |                                               |
| getpmsg()                                     |                                               |
| getpwuid()                                    | getpwuid\_r()                                 |
| getpwnam()                                    | getpwnam\_r()                                 |
| gets()                                        | fgets()                                       |
| getitimer()                                   | timer\_gettime()                              |
| gettimeofday()                                | clock\_gettime()（戻り値を確認すること）      |
| getw()                                        |                                               |
| getwd()                                       |                                               |
| gmtime()                                      | gmtime\_r()                                   |
| index()                                       |                                               |
| ioctl() （stropts.hに定義されているもの）     |                                               |
| isascii()                                     |                                               |
| isastream()                                   |                                               |
| localtime()                                   | localtime\_r()                                |
| \_longjmp()                                   |                                               |
| mktemp()                                      |                                               |
| popen()                                       | execle(), execve()                            |
| pthread\_getconsurrency()                     |                                               |
| pthread\_setconcurrency()                     |                                               |
| putc()                                        |                                               |
| putchar()                                     |                                               |
| putenv() に autoな変数のポインタ              | setenv()                                      |
| putmsg()                                      |                                               |
| putpmsg()                                     |                                               |
| rand()                                        | srand()                                       |
| rand\_r()                                     | srand()                                       |
| readdir()                                     | readdir\_r()                                  |
| rindex()                                      |                                               |
| sbrk()                                        |                                               |
| scanf()                                       | sscanf()                                      |
| \_setjmp()                                    |                                               |
| setpgrp()                                     |                                               |
| settimer()                                    | timer\_settimer()                             |
| sighold()                                     | pthread\_sigmask() または sigprocmask()       |
| sigignore()                                   |                                               |
| siginterrupt()                                |                                               |
| signal()                                      | signalfd()                                    |
| sigpause()                                    | sigsuspend()                                  |
| sigrelse()                                    | pthread\_sigmask() または sigprocmask()       |
| sigset()                                      | sigaction()                                   |
| sigstack()                                    |                                               |
| strcpy()                                      | strncpy()                                     |
| strcat()                                      | strncat()                                     |
| strlen()                                      | strnlen()                                     |
| strtok()                                      |                                               |
| sprintf()                                     | snprintf()                                    |
| system()                                      | execle(), execve()                            |
| tempnam()                                     | tmpfile(), mkdtemp(), mkstemp()               |
| tmpnam()                                      | tmpfile(), mkdtemp(), mkstemp()               |
| toascii()                                     |                                               |
| \_tolower()                                   | tolower()                                     |
| \_toupper()                                   | toupper()                                     |
| ttyname()                                     | ttyname\_r()                                  |
| ttyslot()                                     |                                               |
| ulimit()                                      | getrlimit(), setrlimit()                      |
| utime()                                       | utimensat()                                   |
| utimes()                                      |                                               |
| valloc()                                      |                                               |
| vfork()                                       | fork()                                        |
| vsprintf()                                    | vsnprintf()                                   |
| wcscat()                                      | wcsncat()                                     |
| wcscpy()                                      | wcsncpy()                                     |

#### 使用禁止関数の理由や注意点 <a id="SS_3_10_2_2"></a>
##### バッファオーバーランを引き起こしやすい関数 <a id="SS_3_10_2_2_1"></a>
* 以下の関数は、バッファオーバーフロー等のバグを引き起こしやすい。

```
    gets(), scanf(), strcpy(), strcat(), sprintf(), vsprintf(), wcscat(), wcscpy()
```

##### コマンドインジェクション防止 <a id="SS_3_10_2_2_2"></a>
* 以下の関数は、外部コマンドの実行時に環境変数に依存してしまう。

```
    execl(), execlp(), execv(), execvp(), popen(), system()
```

##### obsolete関数 <a id="SS_3_10_2_2_3"></a>
* 以下の関数は、すでにメンテナンスがされなくなった(obsolete)。

```
    asc_time(), asctime_r(), ctime(), ctime_r(), fattach(), fdetach(), ftw(), getitimer(),
    getmsg(), getpmsg(), gets(), settimer(), gettimeofday(), ioctl() in stropts.h for stream,
    isascii(), isastream(), _longjmp(),
    pthread_getconsurrency(), pthread_setconcurrency(), putmsg(), putpmsg(), rand_r(),
    _setjmp(), settimer(),
    setpgrp(), sighold(), sigignore(), siginterrupt(), sigpause(), sigrelse(), sigset(),
    strlen(), _tolower(), _toupper(), tempnam(), tmpnam(), toascii(), ulimit(), utime()
```

##### LEGACY関数 <a id="SS_3_10_2_2_4"></a>
* 以下の関数は、すでに役目を終えた。

```
    sigstack(), cuserid(), getopt(), getw(), ttyslot(), valloc(), ecvt(), fcvt(), 
    gcvt(), mktemp(), bcmp(), bcopy(), bzero(), index(), rindex(), utimes(), getwd(),
    brk(), sbrk(), rand()
```

##### スレッドセーフでない関数 <a id="SS_3_10_2_2_5"></a>
* 以下の関数は、スレッドセーフでない。

```
    asctime(), ctime(), getgrgid(), getgrnam(), getlogin(), getpwuid(), getpwnam(), gmtime(),
    localtime(), ttyname(), 
    ctermid(), tmpnam() (引数がNULLのとき、非[リエントラント](cpp_idioms.md#SS_21_14_4)になる)
```

##### 標準外関数等 <a id="SS_3_10_2_2_6"></a>
* 可変長配列や、alloca()は、標準外である。

##### 扱いが難しい関数 <a id="SS_3_10_2_2_7"></a>
* signalの扱いは極めて難しく、安定動作をさせるのは困難である。
  「シグナルの[リエントラント](cpp_idioms.md#SS_21_14_4)問題を解決でき、使用できる関数に制限がない」という利点があるため、
   signal()の代わりに、 signalfd() を使用する。 
* 排他的にファイルをオープンできないため、tmpfile()を使用しない。代わりにmkstemp()を使用する。

#### 典型的な注意点 <a id="SS_3_10_2_3"></a>
##### リソースリークを引き起こしやすい関数 <a id="SS_3_10_2_3_1"></a>
* open()/close()、fopen()/fclose()はリソースリークを引き起こしやすい。
  「[RAII(scoped guard)](#8.9)」で例示したコードやstd::fstreamを使うことでその問題を回避する。

##### シンボリックリンクの検査 <a id="SS_3_10_2_3_2"></a>
* シンボリックリンクはlstat()のみで検査せず、以下のように検査する。

    1.	ファイル名をlstat()
    2.	ファイルをopen()
    3.	2で取得したファイル記述子に対してfstat()
    4.	1, 3の情報を照合して同一ファイルであることを確認

##### strncpy(), strncat()の終端 <a id="SS_3_10_2_3_3"></a>
* 下記のような問題を回避するために文字列操作にはstd::stringを使用する。
    * sizeof(dst) <= strlen(src) の場合、strncpy(dst, src, sizeof(dst) - 1)の呼び出しは、
      dstの文字列を'\0'終端しない。
    * コピーすべきデータが無くなると、dstの残りを'\0'で埋めるので性能上の問題がある。
    * strncpy(), strncat()ともに、
      sizeof(dst) < strlen(src) のときにsrcの文字列が切り捨てられたことを判別できない。

##### TOCTOU (Time Of Check, Time Of Use) <a id="SS_3_10_2_3_4"></a>
* open()前にaccess()でファイルの存在を確認する等、チェックして使用するパターンでは、
  この動作がアトミックに行われないため問題が発生する。
  この問題回避の一般解はないが「ファイルの存在確認後、read-open」のような場合では、
  「いきなりread-openし、エラーした場合に対処」することでアトミックな処理にできる。

##### メモリアロケーション <a id="SS_3_10_2_3_5"></a>
* new/deleteとmalloc/freeの混在を避けるため下記の使用をしない。
  newしたオブジェクトのポインタをfreeした場合、そのオブジェクトのデストラクタが呼び出されず、
  リソースリークしてしまうことがある。

```
    malloc(), realloc(), free()
```

##### 非同期シグナル <a id="SS_3_10_2_3_6"></a>
* プロセス監視のSIGCHLDや、accept()でのブロッキングの中断等、シグナルでしか処理できない場合を除き、
  非同期シグナルを使用しない。
* 使用してもよいシグナルは、以下に限られる。
    * SIGHUP : デーモン制御
    * SIGINT : 端末の割り込みキー
    * SIGILL : 不正なハードウェア命令
    * SIGBUS : ハードウェアフォルト
    * SIGFPE : 算術演算例外
    * SIGSEGV : 不正なメモリ参照
    * SIGALRM : タイムアウト検知
    * SIGTERM : killで送られるデフォルト終了シグナル
    * SIGCHLD : プロセス監視

* 上記シグナルを扱う場合であっても、シグナル処理専用スレッドでsigwait()を用いることで、
  非同期シグナルを同期的に扱うようにする。

## その他 <a id="SS_3_11"></a>
### assertion <a id="SS_3_11_1"></a>
* 論理的にありえない状態(特に論理的に到達しないはずの条件文への到達)を検出するために、
  assert()を使用する(「[switch文](programming_convention.md#SS_3_4_2)」、「[if文](programming_convention.md#SS_3_4_3)」参照)。
* assert()はコンパイルオプションにより無効化されることがあるため、
  assert()の引数に[副作用](cpp_idioms.md#SS_21_14_16)のある式を入れない。
* ランタイムでなく、コンパイル時に判断できる論理矛盾や使用制限には、static\_assertを使用する。

```cpp
    //  example/programming_convention/etc.cpp 12

    template <uint32_t SIZE>
    struct POD {
        POD() noexcept
        {  // 何らかの理由で、10を超えるSIZEをサポートしたくない。
            static_assert(SIZE < 10, "too big");
        }

        uint32_t mem[SIZE];
    };

    void f() noexcept
    {
        POD<3> p3;             // コンパイル可能
        auto   p4 = POD<4>{};  // コンパイル可能
        // POD<10> p10;        // static assertion failed: too big でコンパイルエラー
        // POD<11> p11;        // static assertion failed: too big でコンパイルエラー
    }
```

* static\_assert、assert両方が使える場合には、static\_assertを優先して使用する。

* [演習-アサーションの選択](exercise_q.md#SS_22_7_1)  
* [演習-assert/static_assert](exercise_q.md#SS_22_7_2)  

### アセンブラ <a id="SS_3_11_2"></a>
* アセンブラ関数は、.asm等で定義し、ヘッダファイルでCの関数として宣言する。
* アセンブラ関数も、関数/メンバ関数のルールに従う(「[関数](programming_convention.md#SS_3_3)」参照)。
* インラインアセンブラや、それを含む[関数型マクロ](programming_convention.md#SS_3_6_1)がソースコード全域に広がらないようにする。

### 言語拡張機能 <a id="SS_3_11_3"></a>
* #pragma once以外で、且つそれ以外に実装方法がない場合を除き、
  コンパイラ独自の言語拡張機能を使用しない。
* オブジェクトのアライメントが必要な場合、
    * alignas、alignofを使用する(「[プレースメントnew](core_lang_spec.md#SS_19_6_9)」参照)。
    * コンパイラ独自のアライメント機能(#pragma等)の使用を避ける。
* 繰り返し使用する#pragmaに関しては、\_Pragma演算子とマクロを組み合わせて使用する。
  コンパイラの警告には従うべきであるが、ごく稀に無視せざるを得ない場合がある。
  そういった場合、その警告は下記例のような方法で抑止する。

```cpp
    //  example/programming_convention/etc.cpp 38

    #if defined(__clang__)
    #define SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD _Pragma("clang diagnostic ignored \"-Wunused-private-field\"")
    #else
    #define SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD
    #endif

    #define SUPPRESS_WARN_GCC_BEGIN _Pragma("GCC diagnostic push")
    #define SUPPRESS_WARN_GCC_END _Pragma("GCC diagnostic pop")
    #define SUPPRESS_WARN_GCC_NOT_EFF_CPP _Pragma("GCC diagnostic ignored \"-Weffc++\"")
    #define SUPPRESS_WARN_GCC_UNUSED_VAR _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")

    //
    // ...
    //

    SUPPRESS_WARN_GCC_BEGIN;
    SUPPRESS_WARN_GCC_UNUSED_VAR;
    SUPPRESS_WARN_GCC_NOT_EFF_CPP;
    SUPPRESS_WARN_CLANG_UNUSED_PRIVATE_FIELD;

    class A {
    public:
        A() noexcept
        {
            // 警告: 'PragmaSample::A::b_' should be initialized in
            //       the member initialization list [-Weffc++]
            // 警告: unused variable 'c' [-Wunused-variable]
            // のようなワーニングが出力される。

            int32_t c;
            b_ = 0;
        }

    private:
        int32_t a_{0};
        int32_t b_;
    };

    SUPPRESS_WARN_GCC_END;
```

## 特に重要なプログラミング規約 <a id="SS_3_12"></a>
本章で取り上げた規約は、重要度という観点で様々なレベルのものが混在するため量も多く、
すぐに実践することが難しいかもしれない。
そういった場合には、まずは特に重要な下記リストを守ることから始めるのが良いだろう。

* 浮動小数点型をなるべく使わない([浮動小数点型](core_lang_spec.md#SS_19_1_12))。
* const/constexprを積極的に使用する([const/constexprインスタンス](programming_convention.md#SS_3_1_9), [メンバ関数](programming_convention.md#SS_3_2_4))。
* すべてのインスタンスは定義と同時に初期化する([インスタンスの初期化](programming_convention.md#SS_3_1_12))。
* クラスのpublicメンバ関数は最大7個([メンバの数](programming_convention.md#SS_3_2_2_2))。
* クラスのメンバ変数は最大4個([メンバの数](programming_convention.md#SS_3_2_2_2))。
* クラスのメンバ変数はprivateのみ([アクセスレベルと隠蔽化](programming_convention.md#SS_3_2_3))。
* クラスのメンバ変数はコンストラクタ終了時までに初期化する([非静的なメンバ変数](programming_convention.md#SS_3_2_5_2))。
* friendは使用しない([アクセスレベルと隠蔽化](programming_convention.md#SS_3_2_3))。
* 派生は最大2回([継承/派生](programming_convention.md#SS_3_2_6))。
* 関数は小さくする([サイクロマティック複雑度のクライテリア](cpp_idioms.md#SS_21_6_2))。
* 関数の仮引数は最大4個([実引数/仮引数](programming_convention.md#SS_3_3_4))。
* グローバルなインスタンスは使わない([スコープ](programming_convention.md#SS_3_8))。
* throw, try-catchは控えめに使用する([エクセプション処理](programming_convention.md#SS_3_3_9))。
* 構文に関しては以下に気を付ける。
    * if, else, for, while, do後には{}を使う([複合文](programming_convention.md#SS_3_4_1))。
    * switchでのフォールスルーをしない([switch文](programming_convention.md#SS_3_4_2))。
    * switchにはdefaultラベルを入れる([switch文](programming_convention.md#SS_3_4_2))。
    * 範囲for文を積極的に使う([範囲for文](core_lang_spec.md#SS_19_9_2))。
    * gotoを使用しない([goto文](programming_convention.md#SS_3_4_8))。
* オブジェクトのダイナミックな生成には`std::make_unique<>`や`std::make_shared<>`を使用する
  ([メモリアロケーション](programming_convention.md#SS_3_5_6))。
* Cタイプのキャストは使用しない([キャスト、暗黙の型変換](programming_convention.md#SS_3_5_10))。


