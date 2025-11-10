<!-- ./md/programming_convention.md -->
# プログラミング規約 <a id="SS_3"></a>
組織に秩序を与える法、道徳、慣習等をここではルールと呼ぶことにする。
当然ながら、秩序ある組織には良いルールがあり、混沌とした組織には悪いルールがあるか、
ルールはあっても守られていないか、そもそもルールが存在しない。

秩序あるソースコードとは、

* 可読性が高い。
    * 簡潔に記述されている。
    * 記述スタイルが統一されている(「[コーディングスタイル](coding_style.md#SS_5)」参照)。
    * ファイルや識別子の名前に規則性があり、適切に命名されている
      (「[Name and Conquer](software_practice.md#SS_2_6)」、「[命名規則](naming_practice.md#SS_6)」参照)。 
    * コメントの記法が統一されており、内容が適切である(「[コメント](comment.md#SS_7)」参照)。 
* 保守、テスト、移植等が容易である。
* 型安全性が配慮されている。
* コンパイル警告レベルが高く、かつ指摘がない(「[g++の警告機能](code_analysis.md#SS_4_1_1)」参照)。

のような特性を満たすものであるが、そうあるためには秩序ある組織と同様に良いルールが必要である。
本章の目的は、C++プログラミングにおけるそのようなルール(=プログラミング規約)を示すことである。

なお、型安全性とは、「正しく型付けされたソースコードは未定義動作をしない」
ことが保証されるという言語の特性である。
配列のオーバランが未定義動作を引き起こすことを考えれば明らかである通り、
C++は型安全性を保証しない。このことは、C++の劣等性を意味しないが、
それに配慮したプログラミング(型システムの最大限の利用等)が必要となることは事実である。

___

__この章の構成__

&emsp;&emsp; [型とインスタンス](programming_convention.md#SS_3_1)  
&emsp;&emsp;&emsp; [算術型](programming_convention.md#SS_3_1_1)  
&emsp;&emsp;&emsp;&emsp; [整数型](programming_convention.md#SS_3_1_1_1)  
&emsp;&emsp;&emsp;&emsp; [char型](programming_convention.md#SS_3_1_1_2)  
&emsp;&emsp;&emsp;&emsp; [std::byte型](programming_convention.md#SS_3_1_1_3)  
&emsp;&emsp;&emsp;&emsp; [bool型](programming_convention.md#SS_3_1_1_4)  
&emsp;&emsp;&emsp;&emsp; [浮動小数点型](programming_convention.md#SS_3_1_1_5)  

&emsp;&emsp;&emsp; [enum](programming_convention.md#SS_3_1_2)  
&emsp;&emsp;&emsp; [bit field](programming_convention.md#SS_3_1_3)  
&emsp;&emsp;&emsp; [class](programming_convention.md#SS_3_1_4)  
&emsp;&emsp;&emsp; [struct](programming_convention.md#SS_3_1_5)  
&emsp;&emsp;&emsp; [union](programming_convention.md#SS_3_1_6)  
&emsp;&emsp;&emsp; [配列](programming_convention.md#SS_3_1_7)  
&emsp;&emsp;&emsp; [型エイリアス](programming_convention.md#SS_3_1_8)  
&emsp;&emsp;&emsp; [const/constexprインスタンス](programming_convention.md#SS_3_1_9)  
&emsp;&emsp;&emsp; [リテラル](programming_convention.md#SS_3_1_10)  
&emsp;&emsp;&emsp;&emsp; [生文字列リテラル](programming_convention.md#SS_3_1_10_1)  

&emsp;&emsp;&emsp; [型推論](programming_convention.md#SS_3_1_11)  
&emsp;&emsp;&emsp;&emsp; [auto](programming_convention.md#SS_3_1_11_1)  

&emsp;&emsp;&emsp; [インスタンスの初期化](programming_convention.md#SS_3_1_12)  
&emsp;&emsp;&emsp; [rvalue](programming_convention.md#SS_3_1_13)  

&emsp;&emsp; [クラスとオブジェクト](programming_convention.md#SS_3_2)  
&emsp;&emsp;&emsp; [ファイルの使用方法](programming_convention.md#SS_3_2_1)  
&emsp;&emsp;&emsp; [クラスの規模](programming_convention.md#SS_3_2_2)  
&emsp;&emsp;&emsp;&emsp; [行数](programming_convention.md#SS_3_2_2_1)  
&emsp;&emsp;&emsp;&emsp; [メンバの数](programming_convention.md#SS_3_2_2_2)  
&emsp;&emsp;&emsp;&emsp; [凝集性](programming_convention.md#SS_3_2_2_3)  

&emsp;&emsp;&emsp; [アクセスレベルと隠蔽化](programming_convention.md#SS_3_2_3)  
&emsp;&emsp;&emsp; [メンバ関数](programming_convention.md#SS_3_2_4)  
&emsp;&emsp;&emsp;&emsp; [特殊メンバ関数](programming_convention.md#SS_3_2_4_1)  
&emsp;&emsp;&emsp;&emsp; [コンストラクタ](programming_convention.md#SS_3_2_4_2)  
&emsp;&emsp;&emsp;&emsp; [copyコンストラクタ、copy代入演算子](programming_convention.md#SS_3_2_4_3)  
&emsp;&emsp;&emsp;&emsp; [moveコンストラクタ、move代入演算子](programming_convention.md#SS_3_2_4_4)  
&emsp;&emsp;&emsp;&emsp; [初期化子リストコンストラクタ](programming_convention.md#SS_3_2_4_5)  
&emsp;&emsp;&emsp;&emsp; [デストラクタ](programming_convention.md#SS_3_2_4_6)  
&emsp;&emsp;&emsp;&emsp; [オーバーライド](programming_convention.md#SS_3_2_4_7)  

&emsp;&emsp;&emsp; [メンバ変数](programming_convention.md#SS_3_2_5)  
&emsp;&emsp;&emsp;&emsp; [メンバ変数の数 ](programming_convention.md#SS_3_2_5_1)  
&emsp;&emsp;&emsp;&emsp; [非静的なメンバ変数](programming_convention.md#SS_3_2_5_2)  
&emsp;&emsp;&emsp;&emsp; [静的なメンバ変数/定数の初期化](programming_convention.md#SS_3_2_5_3)  
&emsp;&emsp;&emsp;&emsp; [mutableなメンバ変数](programming_convention.md#SS_3_2_5_4)  

&emsp;&emsp;&emsp; [継承/派生](programming_convention.md#SS_3_2_6)  
&emsp;&emsp;&emsp;&emsp; [インターフェースの継承](programming_convention.md#SS_3_2_6_1)  
&emsp;&emsp;&emsp;&emsp; [多重継承](programming_convention.md#SS_3_2_6_2)  

&emsp;&emsp;&emsp; [オブジェクト](programming_convention.md#SS_3_2_7)  
&emsp;&emsp;&emsp;&emsp; [スライシング](programming_convention.md#SS_3_2_7_1)  
&emsp;&emsp;&emsp;&emsp; [オブジェクトの所有権](programming_convention.md#SS_3_2_7_2)  
&emsp;&emsp;&emsp;&emsp; [オブジェクトのライフタイム](programming_convention.md#SS_3_2_7_3)  

&emsp;&emsp; [関数](programming_convention.md#SS_3_3)  
&emsp;&emsp;&emsp; [関数構造のクライテリア](programming_convention.md#SS_3_3_1)  
&emsp;&emsp;&emsp; [オーバーロード](programming_convention.md#SS_3_3_2)  
&emsp;&emsp;&emsp; [演算子オーバーロード](programming_convention.md#SS_3_3_3)  
&emsp;&emsp;&emsp; [実引数/仮引数](programming_convention.md#SS_3_3_4)  
&emsp;&emsp;&emsp; [自動変数](programming_convention.md#SS_3_3_5)  
&emsp;&emsp;&emsp; [戻り値型](programming_convention.md#SS_3_3_6)  
&emsp;&emsp;&emsp; [constexpr関数](programming_convention.md#SS_3_3_7)  
&emsp;&emsp;&emsp; [スレッドセーフ性](programming_convention.md#SS_3_3_8)  
&emsp;&emsp;&emsp; [エクセプション処理](programming_convention.md#SS_3_3_9)  
&emsp;&emsp;&emsp; [ビジーループ](programming_convention.md#SS_3_3_10)  
&emsp;&emsp;&emsp; [非メンバ関数](programming_convention.md#SS_3_3_11)  

&emsp;&emsp; [構文](programming_convention.md#SS_3_4)  
&emsp;&emsp;&emsp; [複合文](programming_convention.md#SS_3_4_1)  
&emsp;&emsp;&emsp; [switch文](programming_convention.md#SS_3_4_2)  
&emsp;&emsp;&emsp; [if文](programming_convention.md#SS_3_4_3)  
&emsp;&emsp;&emsp; [while文](programming_convention.md#SS_3_4_4)  
&emsp;&emsp;&emsp; [範囲for文](programming_convention.md#SS_3_4_5)  
&emsp;&emsp;&emsp; [制御文のネスト](programming_convention.md#SS_3_4_6)  
&emsp;&emsp;&emsp; [return文](programming_convention.md#SS_3_4_7)  
&emsp;&emsp;&emsp; [goto文](programming_convention.md#SS_3_4_8)  
&emsp;&emsp;&emsp; [ラムダ式](programming_convention.md#SS_3_4_9)  
&emsp;&emsp;&emsp; [マクロの中の文](programming_convention.md#SS_3_4_10)  

&emsp;&emsp; [演算子](programming_convention.md#SS_3_5)  
&emsp;&emsp;&emsp; [優先順位](programming_convention.md#SS_3_5_1)  
&emsp;&emsp;&emsp; [代入演算](programming_convention.md#SS_3_5_2)  
&emsp;&emsp;&emsp; [ビット演算](programming_convention.md#SS_3_5_3)  
&emsp;&emsp;&emsp; [論理演算](programming_convention.md#SS_3_5_4)  
&emsp;&emsp;&emsp; [条件演算子](programming_convention.md#SS_3_5_5)  
&emsp;&emsp;&emsp; [メモリアロケーション](programming_convention.md#SS_3_5_6)  
&emsp;&emsp;&emsp;&emsp; [new](programming_convention.md#SS_3_5_6_1)  
&emsp;&emsp;&emsp;&emsp; [delete](programming_convention.md#SS_3_5_6_2)  
&emsp;&emsp;&emsp;&emsp; [ダイナミックメモリアロケーションの制約が強いシステム](programming_convention.md#SS_3_5_6_3)  

&emsp;&emsp;&emsp; [sizeof](programming_convention.md#SS_3_5_7)  
&emsp;&emsp;&emsp; [ポインタ間の演算](programming_convention.md#SS_3_5_8)  
&emsp;&emsp;&emsp; [RTTI](programming_convention.md#SS_3_5_9)  
&emsp;&emsp;&emsp; [キャスト、暗黙の型変換](programming_convention.md#SS_3_5_10)  

&emsp;&emsp; [プリプロセッサ命令](programming_convention.md#SS_3_6)  
&emsp;&emsp;&emsp; [関数型マクロ](programming_convention.md#SS_3_6_1)  
&emsp;&emsp;&emsp; [マクロ定数](programming_convention.md#SS_3_6_2)  

&emsp;&emsp; [パッケージとその構成ファイル](programming_convention.md#SS_3_7)  
&emsp;&emsp;&emsp; [パッケージの実装と公開](programming_convention.md#SS_3_7_1)  
&emsp;&emsp;&emsp; [識別子の宣言、定義](programming_convention.md#SS_3_7_2)  
&emsp;&emsp;&emsp; [依存関係](programming_convention.md#SS_3_7_3)  
&emsp;&emsp;&emsp; [二重読み込みの防御](programming_convention.md#SS_3_7_4)  
&emsp;&emsp;&emsp; [ヘッダファイル内の#include](programming_convention.md#SS_3_7_5)  
&emsp;&emsp;&emsp; [#includeするファイルの順番](programming_convention.md#SS_3_7_6)  
&emsp;&emsp;&emsp; [#includeで指定するパス名](programming_convention.md#SS_3_7_7)  

&emsp;&emsp; [スコープ](programming_convention.md#SS_3_8)  
&emsp;&emsp;&emsp; [スコープの定義と原則](programming_convention.md#SS_3_8_1)  
&emsp;&emsp;&emsp; [名前空間](programming_convention.md#SS_3_8_2)  
&emsp;&emsp;&emsp; [using宣言/usingディレクティブ](programming_convention.md#SS_3_8_3)  
&emsp;&emsp;&emsp; [ADLと名前空間による修飾の省略](programming_convention.md#SS_3_8_4)  
&emsp;&emsp;&emsp; [名前空間のエイリアス](programming_convention.md#SS_3_8_5)  

&emsp;&emsp; [ランタイムの効率](programming_convention.md#SS_3_9)  
&emsp;&emsp;&emsp; [前置/後置演算子の選択](programming_convention.md#SS_3_9_1)  
&emsp;&emsp;&emsp; [operator X、operator x=の選択](programming_convention.md#SS_3_9_2)  
&emsp;&emsp;&emsp; [関数の戻り値オブジェクト](programming_convention.md#SS_3_9_3)  
&emsp;&emsp;&emsp; [move処理](programming_convention.md#SS_3_9_4)  
&emsp;&emsp;&emsp; [std::string vs std::string const& vs std::string_view](programming_convention.md#SS_3_9_5)  
&emsp;&emsp;&emsp; [extern template](programming_convention.md#SS_3_9_6)  

&emsp;&emsp; [標準クラス、関数の使用制限](programming_convention.md#SS_3_10)  
&emsp;&emsp;&emsp; [標準ライブラリ](programming_convention.md#SS_3_10_1)  
&emsp;&emsp;&emsp;&emsp; [スマートポインタの使用制限](programming_convention.md#SS_3_10_1_1)  
&emsp;&emsp;&emsp;&emsp; [配列系コンテナクラスの使用制限](programming_convention.md#SS_3_10_1_2)  
&emsp;&emsp;&emsp;&emsp; [std::stringの使用制限](programming_convention.md#SS_3_10_1_3)  
&emsp;&emsp;&emsp;&emsp; [std::string_viewの使用制限](programming_convention.md#SS_3_10_1_4)  

&emsp;&emsp;&emsp; [POSIX系関数](programming_convention.md#SS_3_10_2)  
&emsp;&emsp;&emsp;&emsp; [使用禁止関数一覧](programming_convention.md#SS_3_10_2_1)  
&emsp;&emsp;&emsp;&emsp; [使用禁止関数の理由や注意点](programming_convention.md#SS_3_10_2_2)  
&emsp;&emsp;&emsp;&emsp; [典型的な注意点](programming_convention.md#SS_3_10_2_3)  

&emsp;&emsp; [その他](programming_convention.md#SS_3_11)  
&emsp;&emsp;&emsp; [assertion](programming_convention.md#SS_3_11_1)  
&emsp;&emsp;&emsp; [アセンブラ](programming_convention.md#SS_3_11_2)  
&emsp;&emsp;&emsp; [言語拡張機能](programming_convention.md#SS_3_11_3)  

&emsp;&emsp; [特に重要なプログラミング規約](programming_convention.md#SS_3_12)  
  
  

[インデックス](introduction.md#SS_1_4)に戻る。  

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
  uint8_tの代わりに下記のようにstd::byte(「[BitmaskType](design_pattern.md#SS_9_2)」参照)を用いる。

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
  「[BitmaskType](design_pattern.md#SS_9_2)」を使用する場合を除き、enumへのキャストをしない。
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
    * [ディープコピー](cpp_idioms.md#SS_21_7_2)(「[コンストラクタ](programming_convention.md#SS_3_2_4_2)」参照)が必要な型は、structでなくclassで表す。
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
  従って、unionの定義を外部パッケージに公開(「[パッケージの実装と公開](programming_convention.md#SS_3_7_1)」参照)しない。

* 上記以外でunionのような機能が必要な場合、
  [std::variant](stdlib_and_concepts.md#SS_20_9)(「[std::variantとジェネリックラムダ](template_meta_programming.md#SS_13_7_2_2)」参照)を使用する
  (std::anyはunionの代替えにはならないので、このような場合には使用しない)。

### 配列 <a id="SS_3_1_7"></a>
* 列型オブジェクトは以下で述べるような問題や、
  [AAAスタイル](cpp_idioms.md#SS_21_6_1)で生成できない等の様々な問題を起こしやすいため、
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

* 配列の全要素にアクセスするような繰り返し処理には[範囲for文](core_lang_spec.md#SS_19_9_3)を使用する。

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
    * [constexpr定数](core_lang_spec.md#SS_19_5_2)をパラメータにした場合、コンパイル時に定数として評価できる関数は、
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

* constは[west-const](cpp_idioms.md#SS_21_6_3)に従って記述する。

```cpp
    //  example/programming_convention/type_const_ut.cpp 52

    const std::string s;  // NG
    std::string const t;  // OK

    const std::string* s_ptr;  // NG
    std::string const* t_ptr;  // OK

    const std::string& f();  // NG 関数の宣言
    std::string const& g();  // OK 関数の宣言

    char        abc[]{"abc"};
    const char* a = abc;  // NG *aはconst
    char const* b = abc;  // OK *aはconst
    char* const c = abc;  // NG *aではなく、aがconstになり、意味が変わる

    const char* const d = abc;  // NG
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
* [AAAスタイル](cpp_idioms.md#SS_21_6_1)に従い適切にautoを使用する。

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
* 関数内のオブジェクトは、出来る限り[AAAスタイル](cpp_idioms.md#SS_21_6_1)を用いて宣言し、同時に初期化する。
* [算術型](core_lang_spec.md#SS_19_1_3)の宣言に[AAAスタイル](cpp_idioms.md#SS_21_6_1)が使えない場合、
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

* リファレンスやポインタの宣言に[AAAスタイル](cpp_idioms.md#SS_21_6_1)が使えない場合、
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

* 構造体やクラス型オブジェクトの宣言に[AAAスタイル](cpp_idioms.md#SS_21_6_1)が使えない場合、
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

* decltypeによるオブジェクトの宣言は、[AAAスタイル](cpp_idioms.md#SS_21_6_1)と同様に行う。

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
  [Singleton](design_pattern.md#SS_9_13)に依存した初期化を行うことには問題はない)。
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
      (Aのインターフェースや実装専用に定義されたクラス(「[Pimpl](design_pattern.md#SS_9_3)」参照))は、
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
  [凝集性](cpp_idioms.md#SS_21_9_9)が高くなるように設計する。
* [クラス凝集性のクライテリア](cpp_idioms.md#SS_21_5_3)に従い、凝集性を判断し、凝集性が著しく低いクラスを作らないようにする。

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
      (「[Accessor](design_pattern.md#SS_9_5)」参照)。その場合でもsetterは控えめに使用する。
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

* [NVI(non virtual interface)](design_pattern.md#SS_9_9)に従う。従って、
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

* 非静的メンバの[ハンドル](cpp_idioms.md#SS_21_9_6)を返すメンバ関数を持つオブジェクトが
  [rvalue](core_lang_spec.md#SS_19_7_1_2)である場合、
  そのオブジェクトからその関数を呼び出した戻り値(メンバへのハンドル)を変数で保持しない
  (そのハンドルは[danglingリファレンス](cpp_idioms.md#SS_21_8_2)/[danglingポインタ](cpp_idioms.md#SS_21_8_3)になっている)。
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
  これらを使用しない(「[Copy-And-Swap](design_pattern.md#SS_9_6)」参照)。

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
  copy代入演算子に対して以下のいずれかを行い、[シャローコピー](cpp_idioms.md#SS_21_7_1)が行われないようにする
  (このルールはファイルディスクリプタ等のリソース管理をするクラス全般に当てはまる)。
    * [ディープコピー](cpp_idioms.md#SS_21_7_2)をさせる。
    * = deleteする(「[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)」参照)。

  またこの場合、moveコンストラクタ、move代入演算子の定義を検討する(「[Copy-And-Swap](design_pattern.md#SS_9_6)」参照)。

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
* copyコンストラクタ、copy代入演算子は[copyセマンティクス](cpp_idioms.md#SS_21_3_2)に従わせる。
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
* moveコンストラクタ、move代入演算子は[moveセマンティクス](cpp_idioms.md#SS_21_3_3)に従わせる。
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
* [オーバーライドとオーバーロードの違い](cpp_idioms.md#SS_21_8_1)に注意する。
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
  さらに[NVI(non virtual interface)](design_pattern.md#SS_9_9)にも従うことにより、
  上の条項の示した一連のオーバーライド関数のデフォルト引数の一致について考慮の必要がなくなり、
  且つこのクラスのユーザはデフォルト引数が使用できるようになる。

* [演習-オーバーライド関数の修飾](exercise_q.md#SS_22_3_8)  


### メンバ変数 <a id="SS_3_2_5"></a>
#### メンバ変数の数  <a id="SS_3_2_5_1"></a>
* constexprでなく、publicやprotectedなメンバ変数を宣言しない。
* クラスの可変な状態を表すメンバ変数(non-const, non-static)は4個以内に留める(「[クラス凝集性のクライテリア](cpp_idioms.md#SS_21_5_3)」参考)。

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
  ([CRTP(curiously recurring template pattern)](design_pattern.md#SS_9_22)等は例外的に認められる)。

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
  (もしくはそのクラスに[NVI(non virtual interface)](design_pattern.md#SS_9_9)を適用したクラス)
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
* オブジェクトの[スライシング](cpp_idioms.md#SS_21_7_3)には以下のいずれかで対処する。
    * [Clone(仮想コンストラクタ)](design_pattern.md#SS_9_8)を使用する。
    * copy代入演算子を= deleteする。

* [スライシング](cpp_idioms.md#SS_21_7_3)と類似の問題が起こるため、
  オブジェクトの配列をそのオブジェクトの基底クラスへのポインタに代入しない。

* [演習-スライシング](exercise_q.md#SS_22_2_6)

#### オブジェクトの所有権 <a id="SS_3_2_7_2"></a>
* オブジェクトaの所有権
  (「[オブジェクトの所有権](cpp_idioms.md#SS_21_2)」参照)を持つオブジェクトもしくは関数は、
  オブジェクトaの解放責務を持つ。
* オブジェクトaの所有権を持たないオブジェクトは、
  オブジェクトaの[ハンドル](cpp_idioms.md#SS_21_9_6)をメンバ変数で保持することを出来る限り避ける
  ([Observer](design_pattern.md#SS_9_23)パターン等、このルール順守が困難な場合は多い)。
* クラスAのオブジェクトaが、オブジェクトbにダイナミックに生成されたとすると、  
    * オブジェクトaのポインタは`std::unique_ptr<A>`(「[RAII(scoped guard)](design_pattern.md#SS_9_10)」参照)で保持する。
    * オブジェクトa(正確にはオブジェクトaを管理する`std::unique_ptr<A>`オブジェクト)の所有権は、
      オブジェクトbが保持する。
    * オブジェクトbはオブジェクトaの解放責務を持つ(`std::unique_ptr<A>`による自動解放)。
    * オブジェクトaの所有権を保持していないオブジェクトは、オブジェクトaを解放してはならない。
    * オブジェクトaの所有権を別のオブジェクトxへ移動させる場合、
      `std::unique_ptr<A>`とstd::move()を使用する(「[オブジェクトの排他所有](cpp_idioms.md#SS_21_2_1)」参照)。
    * このようなaに複数の所有者b0、b1が存在する場合、`std::shared_ptr<A>`を使用してaを管理する。
      従って、b0、
      b1は`std::shared_ptr<A>`型のメンバを持つことになる(「[オブジェクトの共有所有](cpp_idioms.md#SS_21_2_2)」参照)。
    * オブジェクトbが`std::shared_ptr<A>`でオブジェクトaを、
      オブジェクトaが`std::shared_ptr<B>`でオブジェクトbを所有する場合、
      [オブジェクトの循環所有](cpp_idioms.md#SS_21_2_3)よるメモリリークが発生するため、
      [std::weak_ptr](stdlib_and_concepts.md#SS_20_5_3)を適切に使用する。

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

* [danglingリファレンス](cpp_idioms.md#SS_21_8_2)、 [danglingポインタ](cpp_idioms.md#SS_21_8_3)に気を付ける。


## 関数 <a id="SS_3_3"></a>
### 関数構造のクライテリア <a id="SS_3_3_1"></a>
* 関数の規模・複雑度に関しては、
    * [サイクロマティック複雑度のクライテリア](cpp_idioms.md#SS_21_4_2)に従う。
* [関数の行数のクライテリア](cpp_idioms.md#SS_21_4_3)に従い、
    * 7 行程度を理想とする。
    * 40行以下に留める。


* [演習-関数分割](exercise_q.md#SS_22_3_7)  

### オーバーロード <a id="SS_3_3_2"></a>
* [オーバーライドとオーバーロードの違い](cpp_idioms.md#SS_21_8_1)に注意する。
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
      (その際、コードクローンを作りがちなので注意する(「[Copy-And-Swap](design_pattern.md#SS_9_6)」参照))。

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
      [std::rel_ops](stdlib_and_concepts.md#SS_20_10_1)を使用する。

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

* 「[関数設計のガイドライン](cpp_idioms.md#SS_21_4)」の「[関数の引数と戻り値の型](cpp_idioms.md#SS_21_4_1)」に従う。

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
  (「[スライシング](cpp_idioms.md#SS_21_7_3)」で述べたように、
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

* 戻り値型は「[関数の引数と戻り値の型](cpp_idioms.md#SS_21_4_1)」に従う。

* 関数が複数の値を返す場合、[std::optional](stdlib_and_concepts.md#SS_20_8)、std::pair、std::tupple、
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
  代わりにC++17で導入された[std::optional](stdlib_and_concepts.md#SS_20_8)を使用する。

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
* 関数、メンバ関数はなるべく[スレッドセーフ](cpp_idioms.md#SS_21_9_2)に実装する。
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
* 関数はそれが不可避でない限り、[no-fail保証](core_lang_spec.md#SS_19_13_1)をする。
  [no-fail保証](core_lang_spec.md#SS_19_13_1)関数は[noexcept](core_lang_spec.md#SS_19_13_4)を使用してそのことを明示する。
* throwをせざるを得ない場合、最低でも[基本的な安全性の保証](core_lang_spec.md#SS_19_13_3)をする。
* 標準ライブラリのコンテナ(std::string, std::vector等)が発生させるエクセプションはtry-catchせず
  (catchしてデバッグ情報を保存するような場合を除く)、
  プログラムをクラッシュさせる。try-catchしてもできることはない。
* 特別な理由がない限り、コンストラクタ呼び出しは[noexcept](core_lang_spec.md#SS_19_13_4)と宣言する。
  ネットワーク接続等、簡単にエラーすることをコンストラクタ内で行わない。
* [オープン・クローズドの原則(OCP)](solid.md#SS_8_2)、[リスコフの置換原則(LSP)](solid.md#SS_8_3)に違反する場合が多いため、
  「throwキーワードによるエクセプション仕様」を使用しない(C++17で廃止)。
* エクセプションをthrowしないことが確定している関数は、[noexcept](core_lang_spec.md#SS_19_13_4)と宣言する。
  move代入演算子を[noexcept](core_lang_spec.md#SS_19_13_4)と宣言することは特に重要である。

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
    * 実態で受け取るとオブジェクトの[スライシング](cpp_idioms.md#SS_21_7_3)が起こる場合がある。
    * 受け取ったエクセプションオブジェクトを書き換えるべきではない。

* エクセプションによるリソースリークを避けるため[RAII(scoped guard)](design_pattern.md#SS_9_10)でリソースを管理する。
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

* [exception-unfriendly](core_lang_spec.md#SS_19_13_5)な関数はエクセプションを発生させないようにする。
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
* ビジーループを使わない。[std::condition_variable](stdlib_and_concepts.md#SS_20_3_4)を使用してイベントドリブンにする。

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
  できるだけ[初期化付きswitch文](core_lang_spec.md#SS_19_9_5_4)を使用し、その変数のスコープを最小に留める。

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
  できるだけ[初期化付きif文](core_lang_spec.md#SS_19_9_5_3)を使用し、その変数のスコープを最小に留める。

### while文 <a id="SS_3_4_4"></a>
* while文には、[初期化付きif文](core_lang_spec.md#SS_19_9_5_3)/[初期化付きswitch文](core_lang_spec.md#SS_19_9_5_4)のような構文は存在しないが、
  while文のオペランド変数を生成するする場合、
  [初期化付きfor文(従来のfor文)](core_lang_spec.md#SS_19_9_5_1)を使用し、その変数のスコープを最小に留める。

### 範囲for文 <a id="SS_3_4_5"></a>
* 配列やコンテナの全要素にアクセスするような繰り返し処理には、
  [off-by-oneエラー](https://ja.wikipedia.org/wiki/Off-by-one%E3%82%A8%E3%83%A9%E3%83%BC)
  が避けられ、従来よりもシンプルに記述できる[範囲for文](core_lang_spec.md#SS_19_9_3)を使用する。

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
  cbegin()、cend()も定義し、そのコンテナに[範囲for文](core_lang_spec.md#SS_19_9_3)を適用できるようにする。

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
  特別な理由がない限り、 可読性と安全性を優先して、ビット演算にはstd::bitsetや[BitmaskType](design_pattern.md#SS_9_2)を使用する。

### 論理演算 <a id="SS_3_5_4"></a>
* &&や||の論理演算子の右オペランドで[副作用](cpp_idioms.md#SS_21_9_12)のある処理をしない。

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
  `std::make_unique<>`や`std::make_shared<>`を使用する。
  また、特別な理由でnewした場合、そのポインタは[スマートポインタ](stdlib_and_concepts.md#SS_20_5)で管理する。
* `std::shared_ptr<>`でダイナミックに生成したオブジェクトを管理する場合、
  [オブジェクトの循環所有](cpp_idioms.md#SS_21_2_3)が発生しないように気を付ける(適切に[std::weak_ptr](stdlib_and_concepts.md#SS_20_5_3)を使う)。
* [プレースメントnew](core_lang_spec.md#SS_19_6_9)を使用しない。
* `new T[N]`を使用しない。代わりにstd::arrayをダイナミックに生成するか、std::vectorを使用する。
* [new (std::nothrow)](core_lang_spec.md#SS_19_6_10)を使わない限り、
  newの戻り値がnullptrであることはないため、new演算子の返り値をnullptrと比較しない。
* [new/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4)する場合、newはnullptrを返さないようにする。
  メモリ不足した場合、ソフト全体をエラー終了させる。
* スタック上で生成しても差し支えないオブジェクトをダイナミックに生成しない。
* newを禁止したいクラスには、privateなoperator new()を宣言する(定義は不要)か、= deleteする。

#### delete <a id="SS_3_5_6_2"></a>
* [不完全型](core_lang_spec.md#SS_19_4_6)のオブジェクトへのポインタをdeleteしない。
  特に「[Pimpl](design_pattern.md#SS_9_3)」を使用する場合には注意が必要である。

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

#### ダイナミックメモリアロケーションの制約が強いシステム <a id="SS_3_5_6_3"></a>
このルールは以下のようなやや特殊なソフトウェアを対象とする。  

* 使用できるメモリが少なく、且つほとんど再起動されない。
* メモリリークの可能性を否定できない3rdパーティライブラリを使っている。
* MISRA/AUTOSAR C++等のヒープの使用制限が強い制約(リアルタイム性の遵守)を守る必要がある
  (「[malloc/freeの問題点](dynamic_memory_allocation.md#SS_14_1)」参照)。


以上のようなシステム開発においては、  

* デフォルトのグローバルnewを使用しない。
    * リアルタイム性に制約のあるシステムでは、
      「[グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_1)」で述べたようなnewを実装する。
    * メモリ制限が強いシステムでは、ダイナミックなオブジェクト生成を避け、
      やむを得ない場合、「[クラスnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_3)」で述べたようなクラス毎のnewを実装する。
* malloc/newを用いてエクセプション送出を行っているツールチェーンを使用している場合、
 「[エクセプション処理機構の変更](dynamic_memory_allocation.md#SS_14_3_2)」で述べたような方法でリアルタイム制を確保するか、
  エクセプションを使用しない。


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

* 上記例を除き、sizeof演算子のオペランドは一見[副作用](cpp_idioms.md#SS_21_9_12)を持っているような式を含んではならない。

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
  (「[等価性のセマンティクス](cpp_idioms.md#SS_21_3_1)」参照)。
    * 単体テストやロギングのでtypeidの使用は問題ない。
    * 派生クラスの型によって異なる動作にしたい場合には、仮想関数を使うか、
      [Visitor](design_pattern.md#SS_9_21)パターン等により実現できる。

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
    * 二重インクルードガード(「[二重読み込みの防御](programming_convention.md#SS_3_7_4)」参照)
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

## パッケージとその構成ファイル <a id="SS_3_7"></a>

### パッケージの実装と公開 <a id="SS_3_7_1"></a>
* パッケージに関して、以下の構造を持つようにソースコードを構成する
  (「[アーキテクチャとファイル構造](architecture.md#SS_10_3)」参照)。
    * ソフトウェアはパッケージに分割される。
    * パッケージは、複数のヘッダファイルと複数の.cppファイルから作られる。
    * パッケージを構成するファイルは、このパッケージ専用ディレクトリに保存される。
    * パッケージは他のパッケージとは排他的な[名前空間](programming_convention.md#SS_3_8_2)を持ち、
      パッケージ内で宣言、定義され、外部パッケージに公開される識別子はその名前空間に包含される。
      外部パッケージに公開されない識別子は、そのパッケージでのみ使用される名前空間か、
      無名名前空間に包含されるようにする。
    * パッケージは、サブパッケージを内包する場合がある。
      サブパッケージは、パッケージの要件を満たす。

* 上記前提のもと、パッケージが外部にサービスを提供する場合、
  そのパッケージで定義されるヘッダファイルは以下のどちらかのみを行うように構成する。
    * 外部へ提供するクラス等を公開する(外部公開ヘッダファイル)。
    * パッケージ内部のみで使用するクラス等の宣言、定義を行う(外部非公開ヘッダファイル)。

<!-- pu:plant_uml/package.pu--><p><img src="data:image/png;base64,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" /></p>

* h/PackageBのディレクトリPackageBは冗長に見えるが、
  h配下にそれを保持するディレクトリ名と同じ名前のディレクトリを持つことは、
  可読性の観点から重要である。
  このディレクトリため、他のパッケージから識別子をインポートするためのインクルードディレクティブは
  以下のように記述されることになる。
  このような記述を可能とするために、
  PackageBがエクスポートするヘッダを使用するコードのコンパイルに
 「インクルールパスにPackageB/hを指定する」オプションを使用する。

```cpp
    //  example/programming_convention/pkg.cpp 1

    // PackageC内の*.cppファイルの内部とする
    #include <memory>  // システムヘッダ
    #include <mutex>   // システムヘッダ
    #include <string>  // システムヘッダ

    // PackageBがエクスポートするするヘッダを使用するために、
    // 以下のようなコンパイルオプションが必要になる
    //      -I<DIR>/PackageA/h
    // <DIR>はコンパイラが実行されるディレクトリ
    //
    #include "PackageA/xxx.h"  // PackageAのインクルード
    #include "PackageB/b0.h"   // PackageBのインクルード
    #include "PackageB/b3.h"   // PackageBのインクルード
    #include "internal.h"      // パッケージ外部非公開ヘッダのインクルード
```

* 外部公開ヘッダファイルは、ビルド時に他のパッケージから参照できるディレクトリに配置する。
    * 外部公開ヘッダファイルは、外部非公開ヘッダファイルをインクルードしない。
    * 外部非公開ヘッダファイルは、ビルド時に他のパッケージから参照できるディレクトリに配置しない。

### 識別子の宣言、定義 <a id="SS_3_7_2"></a>
* [ODR](https://en.cppreference.com/w/cpp/language/definition)を守る。
  つまり、一つの識別子は全ソースコード内にただ一つの定義を持つようにする。
* 一つの.cppファイル内のみで使用される識別子は、
  その.cppファイル内の無名名前空間にその定義や宣言を持つ。
* ヘッダファイルで宣言された識別子が.cppファイル内に定義をもつ場合、
  その.cppファイルにそのヘッダファイルをインクルードさせる。
  特に、非メンバ関数や変数の宣言と定義を矛盾させないために、このルールは特に重要である
  (「[非メンバ関数](programming_convention.md#SS_3_3_11)」参照)。

### 依存関係 <a id="SS_3_7_3"></a>
* 不要/不適切な依存関係(「[インターフェース分離の原則(ISP)](solid.md#SS_8_4)」や
  「[依存関係逆転の原則(DIP)](solid.md#SS_8_5)」への違反)を作らない。
    * 依存関係を最小にとどめるために、前方宣言を適切に使用する。
        * 標準ライブラリのクラス(やクラスのエイリアス)の前方宣言をしない
          (例えば、「std::stringをクラス宣言することでstringヘッダファイルへの依存関係を作らない」
          といった方法は、std::stringがクラスでないため想定通りに働かない)。
    * SOLIDの原則やデザインパターン、イデオム等を適切に使用することにより、依存関係を適切に保つ。
        * 依存関係の伝搬を回避したい場合、[Pimpl](design_pattern.md#SS_9_3)イデオムを使い実装の詳細を隠蔽する。
        * 上位概念が下位概念に依存することを避ける場合、
          「[依存関係逆転の原則(DIP)](solid.md#SS_8_5)」での例や[Observer](design_pattern.md#SS_9_23)等を適用する。
    * パッケージ間の相互、循環依存関係を作らない。

<!-- pu:plant_uml/package_ng.pu--><p><img src="data:image/png;base64,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" /></p>

### 二重読み込みの防御 <a id="SS_3_7_4"></a>
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

### ヘッダファイル内の#include <a id="SS_3_7_5"></a>
* 不要な依存関係を作らないようにするため、
  ヘッダファイルは、そのコンパイルに不要なヘッダファイルをインクルードしない。
* ヘッダファイルが外部からインポートする型(class、struct、enum)
  のデリファレンスがそのヘッダファイル内で不要な場合、前方宣言を使い依存関係を小さくする。 

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

### #includeするファイルの順番 <a id="SS_3_7_6"></a>
* ユーザ定義ヘッダファイルより、システムヘッダファイルの#includeを先に行う。
* システムヘッダファイルは、アルファベット順に#includeを行う。
* ユーザ定義ヘッダファイルは、アルファベット順に#includeを行う。

### #includeで指定するパス名 <a id="SS_3_7_7"></a>
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
この章で扱うスコープを下記のように定義する(「[パッケージの実装と公開](programming_convention.md#SS_3_7_1)」参照)。

1. グローバル
2. パッケージ外部公開名前空間
3. パッケージ外部非公開名前空間
4. ファイル(無名名前空間と関数外static)
5. クラス内
6. 関数内
7. ブロック内

リンクの観点からは、2と3の識別子は同じスコープを持つが、
その識別子はパッケージ外部非公開なヘッダファイルに宣言、定義されているため、
パッケージ外から(まともな方法では)アクセスできない。

* 識別子のスコープは最小になるように配置する。
    * 1のスコープを持つ識別子を宣言しない(特にグローバルなスコープ内のオブジェクトは定義しない)。
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
* パッケージ毎に名前空間を定義する
  (「[パッケージの実装と公開](programming_convention.md#SS_3_7_1)」、[名前空間名](naming_practice.md#SS_6_2_11)」参照)。
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
  (「[継承コンストラクタ](core_lang_spec.md#SS_19_6_1_2)」、「[オーバーライドとオーバーロードの違い](cpp_idioms.md#SS_21_8_1)」参照)。

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
* 戻り値型は「[関数の引数と戻り値の型](cpp_idioms.md#SS_21_4_1)」に従う。


### move処理 <a id="SS_3_9_4"></a>
* [ディープコピー](cpp_idioms.md#SS_21_7_2)の実装を持つクラスへのcopy代入の多くがrvalueから行われるのであれば、
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

* [g++](cpp_idioms.md#SS_21_10_1)/[clang++](cpp_idioms.md#SS_21_10_2)等の優れたコンパイラを適切なオプションで使用することで、
  非推奨の機能、関数、クラスの使用を防ぐ。

#### スマートポインタの使用制限 <a id="SS_3_10_1_1"></a>
* std::auto_ptrを使用しない(C++17で廃止)。
* ダイナミックに生成した[オブジェクトの排他所有](cpp_idioms.md#SS_21_2_1)を行う場合、`std::unique_ptr<>`を使用する。
* ダイナミックに生成した[オブジェクトの共有所有](cpp_idioms.md#SS_21_2_2)を行う場合、`std::shared_ptr<>`を使用する。
* `std::shared_ptr<>`を使用する場合、[オブジェクトの循環所有](cpp_idioms.md#SS_21_2_3)が発生しないように気を付ける。

#### 配列系コンテナクラスの使用制限 <a id="SS_3_10_1_2"></a>
* 配列系のコンテナを使用する場合、コンパイル時に要素数の上限が
    * 定まるのであれば、std::arrayを使用する。
    * 未定ならば、std::vectorを使用する。
* `std::vector<bool>`は、std::vectorの特殊化であり、通常のstd::vectorと同じようには扱えない。
  `std::vector<bool>`を使用する場合、その要素へのハンドルがbool&やbool\*でないことに注意する。
* std::arrayを除くコンテナクラスは、
  それ自体でメモリリソースの[RAII(scoped guard)](design_pattern.md#SS_9_10)を実現しているため、newしない。

#### std::stringの使用制限 <a id="SS_3_10_1_3"></a>
* std::stringは、
  それ自体でメモリリソースの[RAII(scoped guard)](design_pattern.md#SS_9_10)を実現しているため、newしない。
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
    ctermid(), tmpnam() (引数がNULLのとき、非[リエントラント](cpp_idioms.md#SS_21_9_3)になる)
```

##### 標準外関数等 <a id="SS_3_10_2_2_6"></a>
* 可変長配列や、alloca()は、標準外である。

##### 扱いが難しい関数 <a id="SS_3_10_2_2_7"></a>
* signalの扱いは極めて難しく、安定動作をさせるのは困難である。
  「シグナルの[リエントラント](cpp_idioms.md#SS_21_9_3)問題を解決でき、使用できる関数に制限がない」という利点があるため、
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
  assert()の引数に[副作用](cpp_idioms.md#SS_21_9_12)のある式を入れない。
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
    * alignas、alignofを使用する(「[固定長メモリプール](dynamic_memory_allocation.md#SS_14_2_1)」参照)。
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
* 関数は小さくする([サイクロマティック複雑度のクライテリア](cpp_idioms.md#SS_21_4_2))。
* 関数の仮引数は最大4個([実引数/仮引数](programming_convention.md#SS_3_3_4))。
* グローバルなインスタンスは使わない([スコープ](programming_convention.md#SS_3_8))。
* throw, try-catchは控えめに使用する([エクセプション処理](programming_convention.md#SS_3_3_9))。
* 構文に関しては以下に気を付ける。
    * if, else, for, while, do後には{}を使う([複合文](programming_convention.md#SS_3_4_1))。
    * switchでのフォールスルーをしない([switch文](programming_convention.md#SS_3_4_2))。
    * switchにはdefaultラベルを入れる([switch文](programming_convention.md#SS_3_4_2))。
    * 範囲for文を積極的に使う([範囲for文](core_lang_spec.md#SS_19_9_3))。
    * gotoを使用しない([goto文](programming_convention.md#SS_3_4_8))。
* オブジェクトのダイナミックな生成には`std::make_unique<>`や`std::make_shared<>`を使用する
  ([メモリアロケーション](programming_convention.md#SS_3_5_6))。
* Cタイプのキャストは使用しない([キャスト、暗黙の型変換](programming_convention.md#SS_3_5_10))。


