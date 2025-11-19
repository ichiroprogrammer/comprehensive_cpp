<!-- essential/md/core_lang_spec.md -->
# C++コア言語仕様 <a id="SS_19"></a>
この章では、C++コア言語仕様について説明する。

___

__この章の構成__

&emsp;&emsp; [型システムと算術の基礎](core_lang_spec.md#SS_19_1)  
&emsp;&emsp;&emsp; [基本型](core_lang_spec.md#SS_19_1_1)  
&emsp;&emsp;&emsp; [組み込み型](core_lang_spec.md#SS_19_1_2)  
&emsp;&emsp;&emsp; [算術型](core_lang_spec.md#SS_19_1_3)  
&emsp;&emsp;&emsp; [汎整数型](core_lang_spec.md#SS_19_1_4)  
&emsp;&emsp;&emsp; [整数型](core_lang_spec.md#SS_19_1_5)  
&emsp;&emsp;&emsp;&emsp; [ビットシフトにおける未定義動作](core_lang_spec.md#SS_19_1_5_1)  

&emsp;&emsp;&emsp; [算術変換](core_lang_spec.md#SS_19_1_6)  
&emsp;&emsp;&emsp; [汎整数型昇格](core_lang_spec.md#SS_19_1_7)  
&emsp;&emsp;&emsp; [汎整数型拡張](core_lang_spec.md#SS_19_1_8)  
&emsp;&emsp;&emsp; [浮動小数点型昇格](core_lang_spec.md#SS_19_1_9)  
&emsp;&emsp;&emsp; [デフォルト引数昇格](core_lang_spec.md#SS_19_1_10)  
&emsp;&emsp;&emsp; [縮小型変換](core_lang_spec.md#SS_19_1_11)  
&emsp;&emsp;&emsp; [浮動小数点型](core_lang_spec.md#SS_19_1_12)  
&emsp;&emsp;&emsp;&emsp; [浮動小数点型のダイナミックレンジ](core_lang_spec.md#SS_19_1_12_1)  
&emsp;&emsp;&emsp;&emsp; [浮動小数点の誤差](core_lang_spec.md#SS_19_1_12_2)  
&emsp;&emsp;&emsp;&emsp; [イプシロン](core_lang_spec.md#SS_19_1_12_3)  
&emsp;&emsp;&emsp;&emsp; [浮動小数点の演算エラー](core_lang_spec.md#SS_19_1_12_4)  

&emsp;&emsp; [リテラル](core_lang_spec.md#SS_19_2)  
&emsp;&emsp;&emsp; [生文字列リテラル](core_lang_spec.md#SS_19_2_1)  
&emsp;&emsp;&emsp; [2進数リテラル](core_lang_spec.md#SS_19_2_2)  
&emsp;&emsp;&emsp; [数値リテラル](core_lang_spec.md#SS_19_2_3)  
&emsp;&emsp;&emsp; [ワイド文字列](core_lang_spec.md#SS_19_2_4)  
&emsp;&emsp;&emsp; [16進浮動小数点数リテラル](core_lang_spec.md#SS_19_2_5)  
&emsp;&emsp;&emsp; [ユーザー定義リテラル](core_lang_spec.md#SS_19_2_6)  
&emsp;&emsp;&emsp;&emsp; [ユーザ定義リテラル演算子](core_lang_spec.md#SS_19_2_6_1)  
&emsp;&emsp;&emsp;&emsp; [std::string型リテラル](core_lang_spec.md#SS_19_2_6_2)  
&emsp;&emsp;&emsp;&emsp; [std::chronoのリテラル](core_lang_spec.md#SS_19_2_6_3)  
&emsp;&emsp;&emsp;&emsp; [std::complexリテラル](core_lang_spec.md#SS_19_2_6_4)  

&emsp;&emsp; [列挙型とバイト表現](core_lang_spec.md#SS_19_3)  
&emsp;&emsp;&emsp; [enum](core_lang_spec.md#SS_19_3_1)  
&emsp;&emsp;&emsp; [enum class](core_lang_spec.md#SS_19_3_2)  
&emsp;&emsp;&emsp; [スコープドenum](core_lang_spec.md#SS_19_3_3)  
&emsp;&emsp;&emsp; [underlying type](core_lang_spec.md#SS_19_3_4)  
&emsp;&emsp;&emsp; [std::byte](core_lang_spec.md#SS_19_3_5)  
&emsp;&emsp;&emsp; [using enum](core_lang_spec.md#SS_19_3_6)  

&emsp;&emsp; [型とインスタンス](core_lang_spec.md#SS_19_4)  
&emsp;&emsp;&emsp; [トリビアル型](core_lang_spec.md#SS_19_4_1)  
&emsp;&emsp;&emsp; [トリビアルに破壊可能な型](core_lang_spec.md#SS_19_4_2)  
&emsp;&emsp;&emsp; [標準レイアウト型](core_lang_spec.md#SS_19_4_3)  
&emsp;&emsp;&emsp; [集成体](core_lang_spec.md#SS_19_4_4)  
&emsp;&emsp;&emsp; [POD](core_lang_spec.md#SS_19_4_5)  
&emsp;&emsp;&emsp; [不完全型](core_lang_spec.md#SS_19_4_6)  
&emsp;&emsp;&emsp; [完全型](core_lang_spec.md#SS_19_4_7)  
&emsp;&emsp;&emsp; [ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)  
&emsp;&emsp;&emsp; [RTTI](core_lang_spec.md#SS_19_4_9)  
&emsp;&emsp;&emsp;&emsp; [dynamic_cast](core_lang_spec.md#SS_19_4_9_1)  
&emsp;&emsp;&emsp;&emsp; [typeid](core_lang_spec.md#SS_19_4_9_2)  
&emsp;&emsp;&emsp;&emsp; [std::type_info](core_lang_spec.md#SS_19_4_9_3)  

&emsp;&emsp;&emsp; [Run-time Type Information](core_lang_spec.md#SS_19_4_10)  
&emsp;&emsp;&emsp; [インターフェースクラス](core_lang_spec.md#SS_19_4_11)  
&emsp;&emsp;&emsp; [constインスタンス](core_lang_spec.md#SS_19_4_12)  

&emsp;&emsp; [定数式とコンパイル時評価](core_lang_spec.md#SS_19_5)  
&emsp;&emsp;&emsp; [constexpr](core_lang_spec.md#SS_19_5_1)  
&emsp;&emsp;&emsp; [constexpr定数](core_lang_spec.md#SS_19_5_2)  
&emsp;&emsp;&emsp; [constexpr関数](core_lang_spec.md#SS_19_5_3)  
&emsp;&emsp;&emsp; [コア定数式](core_lang_spec.md#SS_19_5_4)  
&emsp;&emsp;&emsp; [リテラル型](core_lang_spec.md#SS_19_5_5)  
&emsp;&emsp;&emsp; [constexprインスタンス](core_lang_spec.md#SS_19_5_6)  
&emsp;&emsp;&emsp; [consteval](core_lang_spec.md#SS_19_5_7)  
&emsp;&emsp;&emsp; [constinit](core_lang_spec.md#SS_19_5_8)  
&emsp;&emsp;&emsp; [constexprラムダ](core_lang_spec.md#SS_19_5_9)  

&emsp;&emsp; [オブジェクト生成と初期化](core_lang_spec.md#SS_19_6)  
&emsp;&emsp;&emsp; [特殊メンバ関数](core_lang_spec.md#SS_19_6_1)  
&emsp;&emsp;&emsp;&emsp; [初期化子リストコンストラクタ](core_lang_spec.md#SS_19_6_1_1)  
&emsp;&emsp;&emsp;&emsp; [継承コンストラクタ](core_lang_spec.md#SS_19_6_1_2)  
&emsp;&emsp;&emsp;&emsp; [委譲コンストラクタ](core_lang_spec.md#SS_19_6_1_3)  

&emsp;&emsp;&emsp; [explicit コンストラクタと型変換制御](core_lang_spec.md#SS_19_6_2)  
&emsp;&emsp;&emsp;&emsp; [explicit](core_lang_spec.md#SS_19_6_2_1)  
&emsp;&emsp;&emsp;&emsp; [暗黙の型変換](core_lang_spec.md#SS_19_6_2_2)  
&emsp;&emsp;&emsp;&emsp; [暗黙の型変換抑止](core_lang_spec.md#SS_19_6_2_3)  
&emsp;&emsp;&emsp;&emsp; [explicit(COND)](core_lang_spec.md#SS_19_6_2_4)  
&emsp;&emsp;&emsp;&emsp; [explicit type operator()](core_lang_spec.md#SS_19_6_2_5)  

&emsp;&emsp;&emsp; [==演算子](core_lang_spec.md#SS_19_6_3)  
&emsp;&emsp;&emsp;&emsp; [メンバ==演算子](core_lang_spec.md#SS_19_6_3_1)  
&emsp;&emsp;&emsp;&emsp; [非メンバ==演算子](core_lang_spec.md#SS_19_6_3_2)  

&emsp;&emsp;&emsp; [比較演算子](core_lang_spec.md#SS_19_6_4)  
&emsp;&emsp;&emsp;&emsp; [<=>演算子](core_lang_spec.md#SS_19_6_4_1)  
&emsp;&emsp;&emsp;&emsp; [三方比較演算子](core_lang_spec.md#SS_19_6_4_2)  
&emsp;&emsp;&emsp;&emsp; [spaceship operator](core_lang_spec.md#SS_19_6_4_3)  

&emsp;&emsp;&emsp; [リスト初期化](core_lang_spec.md#SS_19_6_5)  
&emsp;&emsp;&emsp; [一様初期化](core_lang_spec.md#SS_19_6_6)  
&emsp;&emsp;&emsp; [非静的なメンバ変数の初期化](core_lang_spec.md#SS_19_6_7)  
&emsp;&emsp;&emsp;&emsp; [NSDMI](core_lang_spec.md#SS_19_6_7_1)  
&emsp;&emsp;&emsp;&emsp; [初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)  
&emsp;&emsp;&emsp;&emsp; [コンストラクタ内での非静的なメンバ変数の初期値の代入](core_lang_spec.md#SS_19_6_7_3)  

&emsp;&emsp;&emsp; [オブジェクトのライフタイム](core_lang_spec.md#SS_19_6_8)  
&emsp;&emsp;&emsp; [プレースメントnew](core_lang_spec.md#SS_19_6_9)  
&emsp;&emsp;&emsp; [new (std::nothrow)](core_lang_spec.md#SS_19_6_10)  

&emsp;&emsp; [値カテゴリとリファレンス](core_lang_spec.md#SS_19_7)  
&emsp;&emsp;&emsp; [expression](core_lang_spec.md#SS_19_7_1)  
&emsp;&emsp;&emsp;&emsp; [lvalue](core_lang_spec.md#SS_19_7_1_1)  
&emsp;&emsp;&emsp;&emsp; [rvalue](core_lang_spec.md#SS_19_7_1_2)  
&emsp;&emsp;&emsp;&emsp; [xvalue](core_lang_spec.md#SS_19_7_1_3)  
&emsp;&emsp;&emsp;&emsp; [prvalue](core_lang_spec.md#SS_19_7_1_4)  
&emsp;&emsp;&emsp;&emsp; [glvalue](core_lang_spec.md#SS_19_7_1_5)  

&emsp;&emsp;&emsp; [decltypeとexpression](core_lang_spec.md#SS_19_7_2)  

&emsp;&emsp; [リファレンス](core_lang_spec.md#SS_19_8)  
&emsp;&emsp;&emsp; [lvalueリファレンス](core_lang_spec.md#SS_19_8_1)  
&emsp;&emsp;&emsp; [rvalueリファレンス](core_lang_spec.md#SS_19_8_2)  
&emsp;&emsp;&emsp;&emsp; [lvalueからの代入](core_lang_spec.md#SS_19_8_2_1)  
&emsp;&emsp;&emsp;&emsp; [rvalueからの代入](core_lang_spec.md#SS_19_8_2_2)  
&emsp;&emsp;&emsp;&emsp; [std::move(lvalue)からの代入](core_lang_spec.md#SS_19_8_2_3)  

&emsp;&emsp;&emsp; [forwardingリファレンス](core_lang_spec.md#SS_19_8_3)  
&emsp;&emsp;&emsp; [ユニバーサルリファレンス](core_lang_spec.md#SS_19_8_4)  
&emsp;&emsp;&emsp; [perfect forwarding](core_lang_spec.md#SS_19_8_5)  
&emsp;&emsp;&emsp; [リファレンスcollapsing](core_lang_spec.md#SS_19_8_6)  
&emsp;&emsp;&emsp; [リファレンス修飾](core_lang_spec.md#SS_19_8_7)  
&emsp;&emsp;&emsp;&emsp; [rvalue修飾](core_lang_spec.md#SS_19_8_7_1)  
&emsp;&emsp;&emsp;&emsp; [lvalue修飾](core_lang_spec.md#SS_19_8_7_2)  

&emsp;&emsp; [構文と制御構造](core_lang_spec.md#SS_19_9)  
&emsp;&emsp;&emsp; [属性構文](core_lang_spec.md#SS_19_9_1)  
&emsp;&emsp;&emsp; [関数tryブロック](core_lang_spec.md#SS_19_9_2)  
&emsp;&emsp;&emsp; [範囲for文](core_lang_spec.md#SS_19_9_3)  
&emsp;&emsp;&emsp; [構造化束縛](core_lang_spec.md#SS_19_9_4)  
&emsp;&emsp;&emsp; [初期化付きif/switch文](core_lang_spec.md#SS_19_9_5)  
&emsp;&emsp;&emsp;&emsp; [初期化付きfor文(従来のfor文)](core_lang_spec.md#SS_19_9_5_1)  
&emsp;&emsp;&emsp;&emsp; [初期化付きwhile文(従来のwhile文)](core_lang_spec.md#SS_19_9_5_2)  
&emsp;&emsp;&emsp;&emsp; [初期化付きif文](core_lang_spec.md#SS_19_9_5_3)  
&emsp;&emsp;&emsp;&emsp; [初期化付きswitch文](core_lang_spec.md#SS_19_9_5_4)  

&emsp;&emsp; [言語拡張機能](core_lang_spec.md#SS_19_10)  
&emsp;&emsp;&emsp; [コルーチン](core_lang_spec.md#SS_19_10_1)  
&emsp;&emsp;&emsp;&emsp; [co_await](core_lang_spec.md#SS_19_10_1_1)  
&emsp;&emsp;&emsp;&emsp; [co_return](core_lang_spec.md#SS_19_10_1_2)  
&emsp;&emsp;&emsp;&emsp; [co_yield](core_lang_spec.md#SS_19_10_1_3)  

&emsp;&emsp;&emsp; [モジュール](core_lang_spec.md#SS_19_10_2)  
&emsp;&emsp;&emsp; [ラムダ式](core_lang_spec.md#SS_19_10_3)  
&emsp;&emsp;&emsp;&emsp; [クロージャ](core_lang_spec.md#SS_19_10_3_1)  
&emsp;&emsp;&emsp;&emsp; [クロージャ型](core_lang_spec.md#SS_19_10_3_2)  
&emsp;&emsp;&emsp;&emsp; [一時的ラムダ](core_lang_spec.md#SS_19_10_3_3)  
&emsp;&emsp;&emsp;&emsp; [transient lambda](core_lang_spec.md#SS_19_10_3_4)  

&emsp;&emsp;&emsp; [指示付き初期化](core_lang_spec.md#SS_19_10_4)  

&emsp;&emsp; [テンプレートと型推論](core_lang_spec.md#SS_19_11)  
&emsp;&emsp;&emsp; [SFINAE](core_lang_spec.md#SS_19_11_1)  
&emsp;&emsp;&emsp; [メタ関数](core_lang_spec.md#SS_19_11_2)  
&emsp;&emsp;&emsp; [コンセプト](core_lang_spec.md#SS_19_11_3)  
&emsp;&emsp;&emsp; [パラメータパック](core_lang_spec.md#SS_19_11_4)  
&emsp;&emsp;&emsp; [畳み込み式](core_lang_spec.md#SS_19_11_5)  
&emsp;&emsp;&emsp; [ジェネリックラムダ](core_lang_spec.md#SS_19_11_6)  
&emsp;&emsp;&emsp; [クラステンプレートのテンプレート引数の型推論](core_lang_spec.md#SS_19_11_7)  
&emsp;&emsp;&emsp; [CTAD(Class Template Argument Deduction)](core_lang_spec.md#SS_19_11_8)  
&emsp;&emsp;&emsp; [テンプレートの型推論ガイド](core_lang_spec.md#SS_19_11_9)  
&emsp;&emsp;&emsp; [変数テンプレート](core_lang_spec.md#SS_19_11_10)  
&emsp;&emsp;&emsp; [エイリアステンプレート](core_lang_spec.md#SS_19_11_11)  
&emsp;&emsp;&emsp; [constexpr if文](core_lang_spec.md#SS_19_11_12)  
&emsp;&emsp;&emsp; [autoパラメータによる関数テンプレートの簡易定義](core_lang_spec.md#SS_19_11_13)  
&emsp;&emsp;&emsp; [auto](core_lang_spec.md#SS_19_11_14)  
&emsp;&emsp;&emsp; [decltype](core_lang_spec.md#SS_19_11_15)  
&emsp;&emsp;&emsp; [decltype(auto)](core_lang_spec.md#SS_19_11_16)  
&emsp;&emsp;&emsp; [戻り値型を後置する関数宣言](core_lang_spec.md#SS_19_11_17)  
&emsp;&emsp;&emsp; [関数の戻り値型auto](core_lang_spec.md#SS_19_11_18)  
&emsp;&emsp;&emsp; [後置戻り値型auto](core_lang_spec.md#SS_19_11_19)  

&emsp;&emsp; [name lookupと継承構造](core_lang_spec.md#SS_19_12)  
&emsp;&emsp;&emsp; [ルックアップ](core_lang_spec.md#SS_19_12_1)  
&emsp;&emsp;&emsp; [name lookup](core_lang_spec.md#SS_19_12_2)  
&emsp;&emsp;&emsp; [two phase name lookup](core_lang_spec.md#SS_19_12_3)  
&emsp;&emsp;&emsp; [実引数依存探索](core_lang_spec.md#SS_19_12_4)  
&emsp;&emsp;&emsp; [ADL](core_lang_spec.md#SS_19_12_5)  
&emsp;&emsp;&emsp; [関連名前空間](core_lang_spec.md#SS_19_12_6)  
&emsp;&emsp;&emsp; [修飾付き関数呼び出し](core_lang_spec.md#SS_19_12_7)  
&emsp;&emsp;&emsp; [hidden-friend関数](core_lang_spec.md#SS_19_12_8)  
&emsp;&emsp;&emsp; [name-hiding](core_lang_spec.md#SS_19_12_9)  
&emsp;&emsp;&emsp; [ダイヤモンド継承](core_lang_spec.md#SS_19_12_10)  
&emsp;&emsp;&emsp; [仮想継承](core_lang_spec.md#SS_19_12_11)  
&emsp;&emsp;&emsp; [仮想基底](core_lang_spec.md#SS_19_12_12)  
&emsp;&emsp;&emsp; [ドミナンス](core_lang_spec.md#SS_19_12_13)  
&emsp;&emsp;&emsp;&emsp; [ダイヤモンド継承を含まない場合](core_lang_spec.md#SS_19_12_13_1)  
&emsp;&emsp;&emsp;&emsp; [ダイヤモンド継承かつそれが仮想継承でない場合](core_lang_spec.md#SS_19_12_13_2)  
&emsp;&emsp;&emsp;&emsp; [ダイヤモンド継承かつそれが仮想継承である場合](core_lang_spec.md#SS_19_12_13_3)  

&emsp;&emsp;&emsp; [using宣言](core_lang_spec.md#SS_19_12_14)  
&emsp;&emsp;&emsp; [usingディレクティブ](core_lang_spec.md#SS_19_12_15)  

&emsp;&emsp; [エクセプション安全性の保証](core_lang_spec.md#SS_19_13)  
&emsp;&emsp;&emsp; [no-fail保証](core_lang_spec.md#SS_19_13_1)  
&emsp;&emsp;&emsp; [強い安全性の保証](core_lang_spec.md#SS_19_13_2)  
&emsp;&emsp;&emsp; [基本的な安全性の保証](core_lang_spec.md#SS_19_13_3)  
&emsp;&emsp;&emsp; [noexcept](core_lang_spec.md#SS_19_13_4)  
&emsp;&emsp;&emsp; [exception-unfriendly](core_lang_spec.md#SS_19_13_5)  

&emsp;&emsp; [言語仕様の定義要素](core_lang_spec.md#SS_19_14)  
&emsp;&emsp;&emsp; [ill-formed](core_lang_spec.md#SS_19_14_1)  
&emsp;&emsp;&emsp; [well-formed](core_lang_spec.md#SS_19_14_2)  
&emsp;&emsp;&emsp; [未定義動作](core_lang_spec.md#SS_19_14_3)  
&emsp;&emsp;&emsp; [未規定動作](core_lang_spec.md#SS_19_14_4)  
&emsp;&emsp;&emsp; [未定義動作と未規定動作](core_lang_spec.md#SS_19_14_5)  
&emsp;&emsp;&emsp; [被修飾型](core_lang_spec.md#SS_19_14_6)  
&emsp;&emsp;&emsp; [実引数/仮引数](core_lang_spec.md#SS_19_14_7)  
&emsp;&emsp;&emsp; [単純代入](core_lang_spec.md#SS_19_14_8)  
&emsp;&emsp;&emsp; [one-definition rule](core_lang_spec.md#SS_19_14_9)  
&emsp;&emsp;&emsp; [ODR](core_lang_spec.md#SS_19_14_10)  
&emsp;&emsp;&emsp; [型特性キーワード](core_lang_spec.md#SS_19_14_11)  
&emsp;&emsp;&emsp;&emsp; [alignof](core_lang_spec.md#SS_19_14_11_1)  
&emsp;&emsp;&emsp;&emsp; [alignas](core_lang_spec.md#SS_19_14_11_2)  
&emsp;&emsp;&emsp;&emsp; [addressof](core_lang_spec.md#SS_19_14_11_3)  

&emsp;&emsp;&emsp; [演算子のオペランドの評価順位](core_lang_spec.md#SS_19_14_12)  

&emsp;&emsp; [その他](core_lang_spec.md#SS_19_15)  
&emsp;&emsp;&emsp; [RVO(Return Value Optimization)](core_lang_spec.md#SS_19_15_1)  
&emsp;&emsp;&emsp; [トライグラフ](core_lang_spec.md#SS_19_15_2)  
  
  

[インデックス](introduction.md#SS_1_4)に戻る。  

___

## 型システムと算術の基礎 <a id="SS_19_1"></a>

### 基本型 <a id="SS_19_1_1"></a>
基本型(fundamental types)は、C++の標準で定義されている型で、
特別なキーワードを使用して直接宣言できる型の総称である。
[組み込み型](core_lang_spec.md#SS_19_1_2)とも呼ばれることもある。

基本型は以下のに示した型によって構成される。

* [算術型](core_lang_spec.md#SS_19_1_3)
* [汎整数型](core_lang_spec.md#SS_19_1_4)
* [浮動小数点型](core_lang_spec.md#SS_19_1_12)
* void
* 上記した型のポインタ型

注:  
リファレンスは基本型に含まれない。

### 組み込み型 <a id="SS_19_1_2"></a>
組み込み型(built-in types)は[基本型](core_lang_spec.md#SS_19_1_1)(fundamental types)の別称。

### 算術型 <a id="SS_19_1_3"></a>
算術型とは下記の型の総称である。

* [汎整数型](core_lang_spec.md#SS_19_1_4)(bool, char, int, unsigned int, long long等)
* [浮動小数点型](core_lang_spec.md#SS_19_1_12)(float、double、long double)

算術型のサイズは下記のように規定されている。

* 1 == sizeof(bool) == sizeof(char)
* sizeof(char) <= sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)
* 4 <= sizeof(long)
* 8 <= sizeof(long long)
* 4 == sizeof(float)
* 8 == sizeof(double) <= sizeof(long double)

### 汎整数型 <a id="SS_19_1_4"></a>
汎整数型とは下記の型の総称である。

* 論理型(bool)
* 文字型(char、wchar_t等)
* [整数型](core_lang_spec.md#SS_19_1_5)(int、unsigned int、long等)

### 整数型 <a id="SS_19_1_5"></a>
整数型とは下記の型の総称である。

* signed char
* unsigned char
* short
* unsigned short
* int
* unsigned int
* long
* unsigned long
* long long
* unsigned long long

#### ビットシフトにおける未定義動作 <a id="SS_19_1_5_1"></a>

__[動作の分類]__

| 条件                     | unsigned                   | signed (C++17以前) | signed (C++20以降)   |
|--------------------------|:---------------------------|--------------------|----------------------|
| シフト量が負             | 未定義動作                 | 未定義動作         | 未定義動作           |
| シフト量 ≥ ビット数      | 未定義動作                 | 未定義動作         | 未定義動作           |
| 負の値の左シフト         | N/A                        | 未定義動作         | 未定義動作           |
| 左シフトでオーバーフロー | 定義済み(ラップアラウンド) | 未定義動作         | 未定義動作           |
| 負の値の右シフト         | N/A                        | 実装定義           | 定義済み(算術シフト) |
| 正の値の右シフト         | 定義済み（論理シフト）     | 定義済み           | 定義済み             |

__[具体例]__

| コード例                        | 動作                       | 説明                                                 |
|---------------------------------|----------------------------|------------------------------------------------------|
| `x << -1`                       | 未定義動作                 | 負のシフト量(型に関わらず)                           |
| `x << 32`                       | 未定義動作                 | シフト量がビット数以上(intが32ビットの場合)          |
| `int x = -1; x << 1`            | 未定義動作                 | 負の値の左シフト                                     |
| `int x = INT_MAX; x << 1`       | 未定義動作                 | オーバーフロー                                       |
| `unsigned x = UINT_MAX; x << 1` | 定義済み                   | ラップアラウンド(結果は最大値の2倍を2^nで割った余り) |
| `int x = -8; x >> 1`            | 実装定義(上記テーブル参照) | 負の値の右シフト                                     |
| `unsigned x = 8; x >> 1`        | 定義済み                   | 論理シフト                                           |

__[安全なビットシフトのガイドライン]__

| 推奨事項                      | 理由                          |
|-------------------------------|-------------------------------|
| 符号なし整数型を使用(注)      | 未定義動作を回避しやすい      |
| シフト量の範囲チェック        | 0 ≤ シフト量 < ビット数を保証 |
| 負の値をシフトしない          | 未定義動作の原因              |
| オーバーフローの可能性を考慮  | 特にsigned型での左シフト      |
| 静的解析ツールを活用          | コンパイル時に検出可能        |
(注) 符号なし[整数型](core_lang_spec.md#SS_19_1_5)変数(us)をオペランドにした左ビットシフトがオーバーフローした場合、
     usが整数昇格によりintに変換されるため、未定義動作になる可能性がある。

### 算術変換 <a id="SS_19_1_6"></a>
C++における算術変換とは、算術演算の1つのオペランドが他のオペランドと同じ型でない場合、
1つのオペランドを他のオペランドと同じ型に変換するプロセスのことを指す。

算術変換は、[汎整数型昇格](core_lang_spec.md#SS_19_1_7)と通常算術変換に分けられる。

```cpp
    //  example/core_lang_spec/integral_promotion_ut.cpp 11

    bool           bval{};
    char           cval{};
    short          sval{};
    unsigned short usval{};
    int            ival{};
    unsigned int   uival{};
    long           lval{};
    unsigned long  ulval{};
    float          fval{};
    double         dval{};

    auto ret_0 = 3.14159 + 'a';  // 'a'は汎整数拡張でintになった後、さらに通常算術変換でdoubleに
    static_assert(std::is_same<decltype(ret_0), double>::value, "");

    auto ret_1 = dval + ival;  // ivalは通常算術変換でdoubleに
    static_assert(std::is_same<decltype(ret_1), double>::value, "");

    auto ret_2 = dval + fval;  // fvalは通常算術変換でdoubleに
    static_assert(std::is_same<decltype(ret_2), double>::value, "");

    auto ret_3 = ival = dval;  // dvalは通常算術変換でintに
    static_assert(std::is_same<decltype(ret_3), int>::value, "");

    bval = dval;  // dvalは通常算術変換でboolに
    ASSERT_FALSE(bval);

    auto ret_4 = cval + fval;  // cvalは汎整数拡張でintになった後、さらに通常算術変換でfloatに
    static_assert(std::is_same<decltype(ret_4), float>::value, "");

    auto ret_5 = sval + cval;  // svalとcvalは汎整数拡張でintに
    static_assert(std::is_same<decltype(ret_5), int>::value, "");

    auto ret_6 = cval + lval;  // cvalはは汎整数拡張でintになった後、通常算術変換でlongに
    static_assert(std::is_same<decltype(ret_6), long>::value, "");

    auto ret_7 = ival + ulval;  // ivalは通常算術変換でunsigned longに
    static_assert(std::is_same<decltype(ret_7), unsigned long>::value, "");

    auto ret_8 = usval + ival;  // usvalは汎整数拡張でintに
                                // ただし、この変換はunsigned shortとintのサイズに依存する
    static_assert(std::is_same<decltype(ret_8), int>::value, "");

    auto ret_9 = uival + lval;  // uivalは通常算術変換でlongに
                                // ただし、この変換はunsigned intとlongのサイズに依存する
    static_assert(std::is_same<decltype(ret_9), long>::value, "");
```

[一様初期化](core_lang_spec.md#SS_19_6_6)を使用することで、
変数定義時の算術変換による意図しない値の変換([縮小型変換](core_lang_spec.md#SS_19_1_11))を防ぐことができる。

```cpp
    //  example/core_lang_spec/integral_promotion_ut.cpp 62

    int i{-1};
    // int8_t i8 {i};  縮小型変換によりコンパイル不可
    int8_t i8 = i;  // intからint8_tへの型変換
    // これには問題ないが

    ASSERT_EQ(-1, i8);

    // uint8_t ui8 {i};  縮小型変換によりコンパイル不可
    uint8_t ui8 = i;  // intからuint8_tへの型変換
    // おそらく意図通りではない

    ASSERT_EQ(255, ui8);
```

以下に示すように、算術変換の結果は直感に反することがあるため、注意が必要である。

```cpp
    //  example/core_lang_spec/integral_promotion_ut.cpp 81

    int          i{-1};
    unsigned int ui{1};

    // ASSERT_TRUE(i < ui);
    ASSERT_TRUE(i > ui);  // 算術変換の影響で、-1 < 1が成立しない

    signed short   s{-1};
    unsigned short us{1};

    ASSERT_TRUE(s < us);  // 汎整数拡張により、-1 < 1が成立
```

### 汎整数型昇格 <a id="SS_19_1_7"></a>
bool、char、signed char、unsigned char、short、unsigned short型の変数が、
算術のオペランドとして使用される場合、

* その変数の型の取り得る値全てがintで表現できるのならば、int型に変換される。
* そうでなければ、その変数はunsigned int型に変換される。

この変換を汎整数型昇格(integral promotion)と呼ぶ。

従って、sizof(short) < sizeof(int)である処理系では、
bool、char、signed char、unsigned char、short、unsigned short型の変数は、
下記のようにintに変換される。

```cpp
    //  example/core_lang_spec/integral_promotion_ut.cpp 100

    bool bval;
    static_assert(std::is_same<int, decltype(bval + bval)>::value, "");

    char cval;
    static_assert(std::is_same<int, decltype(cval + cval)>::value, "");

    unsigned char ucval = 128;
    static_assert(std::is_same<int, decltype(ucval + ucval)>::value, "");
    ASSERT_EQ(256, ucval + ucval);  // 汎整数拡張により256になる

    static_assert(std::is_same<int, decltype(cval + ucval)>::value, "");

    short sval;
    static_assert(std::is_same<int, decltype(sval + sval)>::value, "");

    unsigned short usval;
    static_assert(std::is_same<int, decltype(usval + usval)>::value, "");

    static_assert(std::is_same<int, decltype(sval + usval)>::value, "");
```

### 汎整数型拡張 <a id="SS_19_1_8"></a>
汎整数型拡張とは[汎整数型昇格](core_lang_spec.md#SS_19_1_7)と同じ概念を指す。

### 浮動小数点型昇格 <a id="SS_19_1_9"></a>
浮動小数点型昇格とは、float型とdouble型の演算で、
float型オブジェクトがdoulbe型に変換されることを指す。

```cpp
    //  example/core_lang_spec/integral_promotion_ut.cpp 126

    double d = 0.05;  // 0.05は循環少数
    float  f = 0.05f;

    bool b1 = d == f;  // fはdoubleに昇格
    ASSERT_FALSE(b1);  // 0.05は循環少数であるため、0.5と0.5fは異なる。

    bool b2 = std::abs(d - f) <= std::numeric_limits<decltype(d - f)>::epsilon();
    ASSERT_FALSE(b2);  // dとfの差はdoubleのイプシロンには収まらない。
```

### デフォルト引数昇格 <a id="SS_19_1_10"></a>
デフォルト引数昇格(Default Argument Promotions)とは、可変長引数`(...)`や、
プロトタイプを持たない関数に[算術型](core_lang_spec.md#SS_19_1_3)引数を渡す際に適用される昇格ルールの総称である。

デフォルト引数昇格には以下が含まれる。

- [汎整数型昇格](core_lang_spec.md#SS_19_1_7)
- [浮動小数点型昇格](core_lang_spec.md#SS_19_1_9)

### 縮小型変換 <a id="SS_19_1_11"></a>
縮小型変換(Narrowing Conversion) とは、あるデータ型から別のデータ型に変換する際に、
変換先の型が元の型の表現範囲を完全にカバーしていない場合に発生する変換を指す。
主に[整数型](core_lang_spec.md#SS_19_1_5)や[浮動小数点型](core_lang_spec.md#SS_19_1_12)などの値を小さな範囲の型に変換する際に起こる。

```cpp
    //  example/core_lang_spec/etc_ut.cpp 19

    int32_t large  = 300;
    int8_t  small  = large;  // 縮小型変換
    bool    b      = large;
    double  d      = large;  // 単単なる型変換(縮小ではない)
    int32_t large2 = d;      // 縮小型変換

    // large = int32_t{d};   縮小型変換回避のためリスト初期化の使用。コンパイルエラー
```

[リスト初期化](core_lang_spec.md#SS_19_6_5)を使うことで、このような変換によるバグの発生を防ぐことができる。


### 浮動小数点型 <a id="SS_19_1_12"></a>
浮動小数点型は以下の型の総称である。

* `float`
* `double`
* `long double`

浮動小数点の仕様は、IEEE 754標準に準拠している。
この標準は、浮動小数点演算の表現方法、精度、丸め方法、および例外処理を規定しており、
広く使用されている。

#### 浮動小数点型のダイナミックレンジ <a id="SS_19_1_12_1"></a>

| 型                          | 正の最小値                    | 正の最大値                    |
|:----------------------------|:------------------------------|:------------------------------|
| `float`                     | 1.175494351 e-38              | 3.402823466 e+38              |
| `double`                    | 2.2250738585072014 e-308      | 1.7976931348623158 e+308      |
| `long double`               | 3.36210314311209350626 e-4932 | 1.18973149535723176502 e+4932 |
| `int32_t`                   | -2,147,483,648                | 2,147,483,647                 |
| `int64_t`                   | -9,223,372,036,854,775,808    | 9,223,372,036,854,775,807     |

ここで`long double`の最小値と最大値は、システムやコンパイラに依存して異なる場合がある点に留意する。

#### 浮動小数点の誤差 <a id="SS_19_1_12_2"></a>
浮動小数点変数の10進数の表現が2進数では循環小数となる場合があり、
正確に表現できないことがある。これにより、計算結果がわずかに異なる値を返す場合がある。
浮動小数点誤差は、特に計算の繰り返しや桁数の多い計算で顕著になる。

以下のコードにより誤差が容易に発生することを示す。

```cpp
    //  example/core_lang_spec/float_ut.cpp 12

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    //  ASSERT_EQ(0.05F, a + b);  // NG  a + b == 0.05Fは一般には成立しない。
    ASSERT_NE(0.05F, a + b);
```

#### イプシロン <a id="SS_19_1_12_3"></a>
イプシロン(epsilon)とは、ある浮動小数点数に対して「1」を加えた時に、
異なる値として識別できる最小の差分を指す。
つまり、イプシロンは浮動小数点数の精度を示す尺度である。

任意の浮動小数点変数a, bがあり、`|a - b| <= epsilon`であった場合、
浮動小数点の仕組みではa、bの差が無いものと考えて、aとbが同値であると考えることが一般的である。

イプシロンを使用した浮動小数点変数の同値判定のコード例を以下に示す。

```cpp
    //  example/core_lang_spec/float_ut.cpp 24

    // 下記の0.01は2進数では循環小数となるため、実数の0.01とは異なる。
    constexpr auto a = 0.01F;  // 0.0000001010001111...
    constexpr auto b = 0.04F;  // 0.0000101000111101...

    bool is_equal = 0.05F == (a + b);
    ASSERT_FALSE(is_equal);  // is_equalはtrueにはならない

    bool is_nearly_equal = std::abs(0.05F - (a + b)) <= std::numeric_limits<float>::epsilon();
    ASSERT_TRUE(is_nearly_equal);  // 浮動小数点の同値はこのように判定する
```

#### 浮動小数点の演算エラー <a id="SS_19_1_12_4"></a>
浮動小数点の演算は以下のようなエラーを生じることがある。

| エラーの種類   | 説明                                                                           | 例                           |
|:---------------|:-------------------------------------------------------------------------------|:-----------------------------|
| 丸め誤差       | 有限桁数による四捨五入の誤差が発生し、正確な値とわずかに異なる場合がある。     | `0.1 + 0.2 != 0.3`           |
| 桁落ち         | 非常に小さい数と大きい数の加算時に、小さい数が無視され、精度が低下する。       | `1e20 + 1 - 1e20 == 0`       |
| 累積誤差       | 繰り返し演算で小さな誤差が積み重なり、最終的に大きなズレが生じることがある。   | ループ内での浮動小数点の加算 |
| ゼロ除算       | 0での除算により計算が定義されず、例外が発生または±無限大が返される。           | `1.0 / 0.0`                  |
| オーバーフロー | 型が表現可能な最大値を超えると無限大（`inf`）として扱われる。                  | `std::pow(10.0, 308)`        |
| アンダーフロー | 型の最小値より小さい数値は0または非常に小さな値として表現され、精度が失われる。| `std::pow(10.0, -308)`       |
| NaN            | 実数では表現できない。                                                         | `std::sqrt(-1)`              |

浮動小数点の演算エラーの検出コード例を以下に示す。

```cpp
    //  example/core_lang_spec/float_ut.cpp 43

    std::feclearexcept(FE_ALL_EXCEPT);  // エラーをクリア

    div(1.0F, 0.0F);  // 関数の中で0除算するが、終了シグナルは発生しない
    ASSERT_TRUE(std::fetestexcept(FE_ALL_EXCEPT) & FE_DIVBYZERO);  // 0除算

    std::feclearexcept(FE_ALL_EXCEPT);  // エラーをクリア

    div(std::numeric_limits<double>::max(), 1);

    auto const excepts = std::fetestexcept(FE_ALL_EXCEPT);

    ASSERT_FALSE(excepts & FE_DIVBYZERO);  // 0除算
    ASSERT_TRUE(excepts & FE_INEXACT);     // 演算が不正確
    ASSERT_FALSE(excepts & FE_INVALID);    // 不正な操作
    ASSERT_TRUE(excepts & FE_OVERFLOW);    // 演算がオーバーフローを起こした
    ASSERT_FALSE(excepts & FE_UNDERFLOW);  // 演算がアンダーフローを起こした

    std::feclearexcept(FE_ALL_EXCEPT);  // エラーをクリア

    auto const a = 1.0F / global_zero;  // global_zero == 0
    ASSERT_TRUE(std::isinf(a));

    auto const b = std::sqrt(-1);
    auto const c = std::sqrt(-1);
    ASSERT_TRUE(std::isnan(b));
    ASSERT_FALSE(b == c);  // NaN == NaNは常にfalse
```

なお、上記のコードで使用した`std::fetestexcept`は一般にスレッドセーフである。
`std::fetestexcept`がスレッドセーフでない処理系では、浮動小数演算エラーの検出は、
実質的には不可能になってしまうため、
浮動小数演算を複数コンテキストで行うソフトウェアの開発する場合、
処理系の選択に注意が必要である。

## リテラル <a id="SS_19_2"></a>
プログラムに具体的な値を与えるための基本的な即値を指す。
例えば、1, 2, 1.0, true/false, nullptr, "literal string"など。

### 生文字列リテラル <a id="SS_19_2_1"></a>
下記の例にあるように正規表現をそのまま文字列リテラルとして表現するために、
C++11から導入された導入されたリテラル。

```cpp
    //  example/core_lang_spec/literal_ut.cpp 15

        std::regex raw_re{R"(\d+)"};     // 生文字リテラルで正規表現パターン。\のエスケープが不要
        std::regex normal_re{"(\\d+)"};  // 生文字リテラルで正規表現パターン。\のエスケープが必要

        std::string test_str = "The year is 2024";  // テスト対象の文字列

        {
            std::smatch match;
            ASSERT_TRUE(std::regex_search(test_str, match, raw_re));  // 正規表現で数字部分を検索
            ASSERT_EQ(match.str(), "2024");  // マッチした部分が "2024" であることをチェック
        }
        {
            std::smatch match;
            ASSERT_TRUE(std::regex_search(test_str, match, normal_re));  // 正規表現で数字部分を検索
            ASSERT_EQ(match.str(), "2024");  // マッチした部分が "2024" であることをチェック
        }
```

### 2進数リテラル <a id="SS_19_2_2"></a>
C++14以降では、0bまたは 0B をプレフィックスとして使うことで、2進数リテラルを表現できる。

```cpp
    //  example/core_lang_spec/literal_ut.cpp 36

    int bin_value = 0b1101;  // 2進数リテラル  2進数1101 は10進数で 13
    ASSERT_EQ(bin_value, 13);
```

### 数値リテラル <a id="SS_19_2_3"></a>
C++14では区切り文字'を使用し、数値リテラルを記述できるようになった。

```cpp
    //  example/core_lang_spec/literal_ut.cpp 42

    // 区切り文字を使った数値リテラル
    int large_number = 1'000'000;  // 10進数は3桁で区切るとわかりやすい
    ASSERT_EQ(large_number, 1000000);

    int bin_with_separator = 0b1011'0010;  // 10進数は4桁で区切るとわかりやすい
    ASSERT_EQ(bin_with_separator, 178);    // 2進数 1011 0010 は 10進数で 178

    int hex_with_separator = 0x00'00'ff'ff;  // 16進数は2桁で区切るとわかりやすい
    ASSERT_EQ(hex_with_separator, 65535);    // 16進数 0x00010011 == 65535
```

### ワイド文字列 <a id="SS_19_2_4"></a>
ワイド文字列リテラルを保持する型は下記のように定義された。

* char16_t: UTF-16エンコーディングのコード単位を扱う型。 u"..." というリテラルでUTF-16文字列を表す。
* char32_t: UTF-32エンコーディングのコード単位を扱う型。 U"..." というリテラルでUTF-32文字列を表す。
* char8_t: UTF-8エンコーディングのコード単位を扱う型。 u8"..." というリテラルでUTF-8文字列を表す。

```cpp
    //  example/core_lang_spec/literal_ut.cpp 59

        // UTF-16 文字列リテラル（uプレフィックスを使用）
        char16_t       utf16_str[]  = u"こんにちは";
        std::u16string utf16_string = u"こんにちは";  // UTF-16 std::u16string 型

        // UTF-32 文字列リテラル（Uプレフィックスを使用）
        char32_t       utf32_str[]  = U"こんにちは";
        std::u32string utf32_string = U"こんにちは";  // UTF-32 std::u32string 型

    #if __cplusplus >= 202002L  // c++20
        // UTF-8 文字列リテラル（u8プレフィックスを使用）
        const char8_t* utf8_str    = u8"こんにちは";
        std::u8string  utf8_string = u8"こんにちは";  // UTF-8 std::string 型

    #else // c++17
        // UTF-8 文字列リテラル（u8プレフィックスを使用）
        const char* utf8_str    = "こんにちは";
        std::string utf8_string = "こんにちは";  // UTF-8 std::string 型
    #endif
```

### 16進浮動小数点数リテラル <a id="SS_19_2_5"></a>
16進浮動小数点数リテラルは、
C++17から導入された浮動小数点数を16進数で表現する方法である。
特に、ハードウェアや低レベルのプログラミングで、
浮動小数点数の内部表現を直接扱う際に便利である

```
    一般的な形式:
        0x[数字].[数字]p[指数]
        0x: 16進数を表すプレフィックス
        [数字]: 16進数の数字 (0-9, a-f, A-F)
        .: 小数点
        p: 指数部を表す
        [指数]: 10進数の指数

    例:
        0x1.2p3は下記に解説する

    リテラルの構成:
        0x: 16進数の開始を示す。
        1.2: 仮数部を表す。この部分は16進数。
        p3: 指数部を表す。この場合、2の3乗を意味すため、つまり8。

        1.2(16進数) =  1 + 2 / 16 = 1.125(10進数)
        1.125 * 8 = 9.0
```

```cpp
    //  example/core_lang_spec/literal_ut.cpp 87

    // float型
    float hex_float = 0x1.2p3;
    EXPECT_FLOAT_EQ(hex_float, 9.0f);  // 正しい期待値は9.0f

    // double型
    double hex_double = 0x1.2p3;
    EXPECT_DOUBLE_EQ(hex_double, 9.0);  // 正しい期待値は9.0

    // 指数部が負の場合 (double型)
    double negative_exp = 0x1.2p-2;
    EXPECT_DOUBLE_EQ(negative_exp, 0.28125);  // 期待値は正しい

    // 小数点以下の部分がない場合 (double型)
    double integer_part = 0x1p3;
    EXPECT_DOUBLE_EQ(integer_part, 8.0);  // 期待値は正しい

    EXPECT_FLOAT_EQ(static_cast<float>(hex_double), hex_float);  // double型をfloatにキャスト
```

### ユーザー定義リテラル <a id="SS_19_2_6"></a>
[ユーザ定義リテラル演算子](core_lang_spec.md#SS_19_2_6_1)により定義されたリテラルを指す。

#### ユーザ定義リテラル演算子 <a id="SS_19_2_6_1"></a>
ユーザ定義リテラル演算子とは以下のようなものである。

```cpp
    //  example/core_lang_spec/user_defined_literal_ut.cpp 4

    constexpr int32_t one_km = 1000;

    // ユーザ定義リテラル演算子の定義
    constexpr int32_t operator""_kilo_meter(unsigned long long num_by_mk) { return num_by_mk * one_km; }
    constexpr int32_t operator""_meter(unsigned long long num_by_m) { return num_by_m; }
```
```cpp
    //  example/core_lang_spec/user_defined_literal_ut.cpp 15

    int32_t km = 3_kilo_meter;  // ユーザ定義リテラル演算子の利用
    int32_t m  = 3000_meter;    // ユーザ定義リテラル演算子の利用

    ASSERT_EQ(m, km);
```

#### std::string型リテラル <a id="SS_19_2_6_2"></a>
"xxx"sとすることで、std::string型のリテラルを作ることができる。

```cpp
    //  example/core_lang_spec/user_defined_literal_ut.cpp 26

    using namespace std::literals::string_literals;

    auto a = "str"s;  // aはstd::string
    auto b = "str";   // bはconst char*

    static_assert(std::is_same_v<decltype(a), std::string>);
    ASSERT_EQ(std::string{"str"}, a);

    static_assert(std::is_same_v<decltype(b), char const*>);
    ASSERT_STREQ("str", b);
```

#### std::chronoのリテラル <a id="SS_19_2_6_3"></a>
std::chronoのリテラルは以下のコードのように使用できる。

```cpp
    //  example/core_lang_spec/literal_ut.cpp 109

    using namespace std::chrono_literals;

    static_assert(1s == 1000ms);  // 1秒 (1s) は 1000 ミリ秒 (1000ms) と等しい

    static_assert(1min == 60s);  // 1分 (1min) は 60秒 (60s) と等しい

    static_assert(1h == 3600s);  // 1時間 (1h) は 3600秒 (3600s) と等しい

    static_assert(1.5s == 1500ms);  // 小数点を使った時間リテラル
```

#### std::complexリテラル <a id="SS_19_2_6_4"></a>
std::complexリテラル以下のコードのように使用できる。

```cpp
    //  example/core_lang_spec/literal_ut.cpp 124

    using namespace std::complex_literals;  // 複素数リテラルを使うための名前空間

    auto a = 1.0 + 2.0i;  // std::complex<double>
    auto b = 3.0 + 4.0i;  // std::complex<double>

    auto result = a + b;
    EXPECT_EQ(result.real(), 4.0);
    EXPECT_EQ(result.imag(), 6.0);
    EXPECT_EQ(result, 4.0 + 6.0i);
```

## 列挙型とバイト表現 <a id="SS_19_3"></a>
### enum <a id="SS_19_3_1"></a>
C++03までのenumは定数を分かりやすい名前で定義するための記法である。
このドキュメントでは、[スコープドenum](core_lang_spec.md#SS_19_3_3)に対して、C++03までのenumを非スコープドenum、
通常のenum、あるいは単にenumと呼ぶことがある。
C++03までのenumには、以下のような問題があった。

* スコープの制限: 名前付きスコープ内に定義するためには、クラスのメンバとして定義しなければならない。
* 型安全性: enumの値は整数型と暗黙の変換が行われてしまう。
* 名前空間の汚染: グローバルスコープに定義されたenumは、名前空間を汚染する。

```cpp
    //  example/core_lang_spec/enum_ut.cpp 14

    enum DayOfWeek { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

    ASSERT_TRUE(1 == Monday);  // intへの暗黙の変換

    enum Color { Red, Green, Blue };

    ASSERT_TRUE(Green == Monday);  // 別のenumが比較できてしまう
```

### enum class <a id="SS_19_3_2"></a>
enum classは通常の[enum](core_lang_spec.md#SS_19_3_1)の問題を解決するためにC++11から導入された。

```cpp
    //  example/core_lang_spec/enum_ut.cpp 29

    enum class DayOfWeek { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

    // ASSERT_TRUE(1 == Monday);  // intへの暗黙の変換できないため、コンパイルエラー
    ASSERT_TRUE(1 == static_cast<int>(DayOfWeek::Monday));

    enum class Color { Red, Green, Blue };

    // ASSERT_TRUE(Green == Monday);  // 別のenumが比較できないため、コンパイルエラー
    ASSERT_TRUE(static_cast<DayOfWeek>(Color::Green) == DayOfWeek::Monday);
```

```cpp
    //  example/core_lang_spec/enum_ut.cpp 41

    // DayOfWeek d0 {0}; intからの暗黙の型変換は許可されないため、コンパイルエラー
    DayOfWeek d0{static_cast<DayOfWeek>(0)};
    DayOfWeek d1{};  // デフォルト初期化
    ASSERT_EQ(d1, DayOfWeek::Sunday);

    DayOfWeek d2{DayOfWeek::Tuesday};  // 値あり初期化
```

### スコープドenum <a id="SS_19_3_3"></a>
[enum class](core_lang_spec.md#SS_19_3_2)はスコープドenum(scoped enum)と呼ばれることがある。


### underlying type <a id="SS_19_3_4"></a>
underlying typeとは、enumやenum classの[汎整数型](core_lang_spec.md#SS_19_1_4)を指定できるようにするために、
C++11で導入されたシンタックスである。enumのサイズをユーザが定義できるため、
特定のバイナリプロトコルとの互換性が必要な場合や、特定のハードウェアと連携する際に特に有効である。

```cpp
    //  example/core_lang_spec/enum_ut.cpp 54

    enum NormalEnum {  // underlying typeの指定しない従来のenum
    };

    enum NormalEnumUnderlyingType : int8_t {  // enum underlying typeがint8_tに指定された従来のenum
    };

    // enum class
    enum class EnumClass {  // underlying typeの指定しないenum class
    };

    enum class EnumClassUnderlyingType : int64_t {  // enum underlying typeがint64_tに指定されたenum
                                                    // class
    };

    static_assert(4 ==  sizeof(NormalEnum));  // 列挙子の値を表現するのに十分なサイズの整数型で処理系依存
    static_assert(4 ==  sizeof(EnumClass));   // 列挙子の値を表現するのに十分なサイズの整数型で処理系依存
    static_assert(sizeof(int8_t) == sizeof(NormalEnumUnderlyingType));
    static_assert(sizeof(int64_t) == sizeof(EnumClassUnderlyingType));
```

C++17までは、型安全の観点から、初期化においては、以下のコードコメントのような仕様であったが、
C++17から導入された[std::byte](core_lang_spec.md#SS_19_3_5)の利便性のため、
underlying typeを指定したenumやenum class変数のunderlying typeインスタンスによる初期化が認められるようになった。

```cpp
    //  example/core_lang_spec/enum_ut.cpp 80

    enum class Color : int { Red, Green, Blue };

    // Color red{0}; C++14まではコンパイルエラー

    Color red{0};  // underlying typeの効果でC++17からコンパイルできる。

    long a{1};
    // Color green{a};  // 縮小型変換が発生するため、コンパイルエラー

```

上記コードにもあるが、underlying typeインスタンスによる初期化を行う場合は、
意図しない縮小型変換によるバグの発生を防ぐためにも、
[一様初期化](core_lang_spec.md#SS_19_6_6)を使用するべきだろう。

一部の例外を除くとunderlying typeを指定しないenumやenum classはコンパイル時にサイズが確定できないため、
前方宣言できないが、underlying typeを指定したenum、enum classは前方宣言することができる。

```cpp
    //  example/core_lang_spec/enum_ut.cpp 97

    // in calender.h
    enum class DayOfWeek : int8_t;  // DayOfWeekの前方宣言

    bool calender(DayOfWeek);  // 前方宣言の効果でこのヘッダでの#include "day_of_week.h"が不要

    // in day_of_week.h
    enum class DayOfWeek : int8_t { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
```

### std::byte <a id="SS_19_3_5"></a>
C++17で導入されたstd::byte型は、バイト単位のデータ操作に使用され、
[整数型](core_lang_spec.md#SS_19_1_5)としての意味を持たないため、型安全性を確保する。
uint8_t型と似ているが、uint8_t型の演算による[汎整数型昇格](core_lang_spec.md#SS_19_1_7)を発生させないため、
可読性、保守性の向上が見込める。

```cpp
    //  example/core_lang_spec/enum_ut.cpp 113

    uint8_t u8_0     = 0x80;
    auto    result_0 = u8_0 << 1;  // 汎整数拡張のためresult_0の型はintになる

    static_assert(std::is_same_v<decltype(result_0), int>);
    ASSERT_EQ(0x100, result_0);  // これがわかりずらいバグにつながることがある

    auto u8_1     = std::byte{0x80};
    auto result_1 = u8_1 << 1;  // 汎整数拡張は発生せず、result_1の型はstd::byteになる

    static_assert(std::is_same_v<decltype(result_1), std::byte>);

    // 整数型を取り出すためには、暗黙の型変換ではなく、
    // 明示的なto_integerの呼び出しが必要になることもコードの安全性につながる
    ASSERT_EQ(0x00, std::to_integer<int>(result_1));  // 0x100はstd::byteでは0
```

### using enum <a id="SS_19_3_6"></a>
名前空間のように、

```cpp
    using enum EnumType;
```

もしくは

```cpp
    using EnumType::enumerator
```

とすることで、スコープによる修飾を省略するための記法である。

```cpp
    //  example/core_lang_spec/enum_ut.cpp 158

    enum class Color { Red, Green, Yellow };

    constexpr std::string_view to_str(Color color)
    {
    #if __cplusplus >= 202002L  // c++20
        using enum Color;       // 名前修飾の省略可能にする

        switch (color) {
        case Red:
            return "Red";
        case Green:
            return "Green";
        case Yellow:
            return "Yellow";
        }

    #else  // c++17
        switch (color) {
        case Color::Red:
            return "Red";
        case Color::Green:
            return "Green";
        case Color::Yellow:
            return "Yellow";
        }
    #endif
        assert(false);
        return "";
    }
```
```cpp
    //  example/core_lang_spec/enum_ut.cpp 194

    #if __cplusplus >= 202002L  // c++20
        using Color::Red;  // Redに関しては名前修飾なしで使用する

        ASSERT_EQ("Red", to_str(Red));
        ASSERT_EQ("Yellow", to_str(Color::Yellow));

    #else  // c++17
        ASSERT_EQ("Red", to_str(Color::Red));
        ASSERT_EQ("Yellow", to_str(Color::Yellow));
    #endif
```

```cpp
    //  example/core_lang_spec/enum_ut.cpp 213

    class Signal {
    public:
        enum class Color { Red, Green, Yellow };
        using enum Color;

        void Set(Color);

    private:
        // ...
    };
```
```cpp
    //  example/core_lang_spec/enum_ut.cpp 229

    Signal s{};

    s.Set(Signal::Color::Red);  // 名前修飾が長すぎる感じがする
    s.Set(Signal::Red);         // using enum colorがあるために、簡潔に書ける

    using Signal::Red;  // Redに関しては名前修飾なしで使用する
                        // この記述によりこの名前空間でのRed識別子が使えなくなる
    s.Set(Red);
```

この記法は、簡潔に記述できるものの、一方では過度な使用は、
C++03までのenumが持っていた問題を再発生させてしまうため、
ブロックスコープ以外での使用に関しては控え目に使用するべきだろう。

## 型とインスタンス <a id="SS_19_4"></a>
### トリビアル型 <a id="SS_19_4_1"></a>
トリビアル型とは、

* 全ての[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)がデフォルトである。
* バーチャル関数や仮想継承を持たない。
* 基底クラスがある場合、基底クラスもトリビアルである。

である。その結果、トリビアル型とは、[トリビアルに破壊可能な型](core_lang_spec.md#SS_19_4_2)となる。

「型Tがトリビアルであること」と「以下の行がコンパイルできること」は等価である。

```cpp
    static_assert(std::is_trivial_v<T>);
```

下記のコードはその使用例である。

```cpp
    //  example/core_lang_spec/trivial_ut.cpp 63

    static_assert(std::is_trivial_v<int>);
    static_assert(std::is_trivial_v<int*>);
    static_assert(std::is_trivial_v<int[1]>);
    static_assert(!std::is_trivial_v<int&>);

    enum class SizeUndefined { su_0, su_1 };

    struct Trivial {      // トリビアルだが標準レイアウトではない
        int&          a;  // リファレンスは標準レイアウトではない
        SizeUndefined b;
    };

    static_assert(!std::is_standard_layout_v<Trivial>);
    static_assert(std::is_trivial_v<Trivial>);
    static_assert(!is_pod_v<Trivial>);
```

### トリビアルに破壊可能な型 <a id="SS_19_4_2"></a>
「トリビアルに破壊可能な型(Trivially Destructible)」とは、以下の条件を満たす型を指す。

* デストラクタがユーザー定義されていない
  (つまりコンパイラが生成したデフォルトのデストラクタを使用している)。
* 型に含まれるすべてのメンバ変数や基底クラスも「トリビアルに破壊可能」である。

```cpp
    //  example/core_lang_spec/trivial_ut.cpp 84

    static_assert(std::is_trivially_destructible_v<int>);
    static_assert(std::is_trivially_destructible_v<int*>);
    static_assert(std::is_trivially_destructible_v<int[1]>);
    static_assert(std::is_trivially_destructible_v<int&>);

    enum class SizeUndefined { su_0, su_1 };

    struct Trivial {  // トリビアルに破壊可能でないため、トリビアル型ではない
        int           a;
        SizeUndefined b;
        ~Trivial() {}
    };

    static_assert(std::is_standard_layout_v<Trivial>);
    static_assert(!std::is_trivial_v<Trivial>);
    static_assert(!std::is_trivially_destructible_v<Trivial>);
```

### 標準レイアウト型 <a id="SS_19_4_3"></a>
「型Tが標準レイアウトであること」と「以下の行がコンパイルできること」は等価である。

```cpp
    static_assert(std::is_standard_layout_v<T>);
```

下記のコードはその使用例である。

```cpp
    //  example/core_lang_spec/trivial_ut.cpp 42

    static_assert(std::is_standard_layout_v<int>);
    static_assert(std::is_standard_layout_v<int*>);
    static_assert(std::is_standard_layout_v<int[1]>);
    static_assert(!std::is_standard_layout_v<int&>);

    enum class SizeUndefined { su_0, su_1 };

    struct StanderdLayout {  // 標準レイアウトだがトリビアルではない
        StanderdLayout() : a{0}, b{SizeUndefined::su_0} {}
        int           a;
        SizeUndefined b;
    };

    static_assert(std::is_standard_layout_v<StanderdLayout>);
    static_assert(!std::is_trivial_v<StanderdLayout>);
    static_assert(!is_pod_v<StanderdLayout>);
```

### 集成体 <a id="SS_19_4_4"></a>
型Tが集成体であるための条件を以下に示す。

* 型Tが`class`、`struct`、`union`であった場合、以下の条件を満たせばTは集成体である。
    * 以下に示したユーザ定義による特殊関数が存在しない。
        * ユーザー定義のコンストラクタ(デフォルトコンストラクタ、コピーコンストラクタ、ムーブコンストラクタ)
        * デストラクタ
        * コピー代入演算子
        * ムーブ代入演算子

    * すべての非静的メンバがpublicであるか、それらに外部からアクセスできる。
    * 仮想関数や仮想基底クラスを持たないこと
    * 仮想関数が定義されておらず、仮想基底クラス（仮想継承）を使用していない。
    * 基底クラスを持たない。

* 集成体の配列や、組み込み型の配列は集成体である。

### POD <a id="SS_19_4_5"></a>
PODとは、 Plain Old Dataの略語であり、
「型TがPODであること」と「以下の行がコンパイルできること」は等価である。

```cpp
    static_assert(std::is_pod_v<T>);  // is_podはC++20から非推奨
```

「型が[トリビアル型](core_lang_spec.md#SS_19_4_1)且つ[標準レイアウト型](core_lang_spec.md#SS_19_4_3)であること」と
「型が[POD](core_lang_spec.md#SS_19_4_5)であること」は等価であるため、C++20では、
[PODという用語は非推奨](https://cpprefjp.github.io/lang/cpp20/deprecate_pod.html)となった。
従って、std::is_pod_vは以下のように置き換えられるべきである。

```cpp
    //  example/core_lang_spec/trivial_ut.cpp 9

    template <typename T>  // std::is_povはC++20から非推奨
    constexpr bool is_pod_v = std::is_trivial_v<T>&& std::is_standard_layout_v<T>;
```

下記のコードは置き換えられたstd::is_pod_vの使用例である。

```cpp
    //  example/core_lang_spec/trivial_ut.cpp 18

    static_assert(is_pod_v<int>);
    static_assert(is_pod_v<int const>);
    static_assert(is_pod_v<int*>);
    static_assert(is_pod_v<int[3]>);
    static_assert(!is_pod_v<int&>);  // リファレンスはPODではない

    struct Pod {};

    static_assert(is_pod_v<Pod>);
    static_assert(is_pod_v<Pod const>);
    static_assert(is_pod_v<Pod*>);
    static_assert(is_pod_v<Pod[3]>);
    static_assert(!is_pod_v<Pod&>);

    struct NonPod {  // コンストラクタがあるためPODではない
        NonPod();
    };

    static_assert(!is_pod_v<NonPod>);
```

上記からわかる通り、POD型とは概ね、C言語と互換性のある型を指すと思って良い。


### 不完全型 <a id="SS_19_4_6"></a>
不完全型とは、型のサイズや構造が不明な型を指す。
以下のis_completeで示したテンプレート定数で、不完全型か否かを判定できる。

```cpp
    //  example/core_lang_spec/incomplete_type_ut.cpp 4

    template <typename T, typename = void>
    struct is_complete : std::false_type {
    };

    template <typename T>  // sizeof(T) が有効であれば、Tは完全型であると判定
    struct is_complete<T, std::void_t<decltype(sizeof(T))>> : std::true_type {
    };

    template <typename T>
    constexpr bool is_complete_v = is_complete<T>::value;
```
```cpp
    //  example/core_lang_spec/incomplete_type_ut.cpp 21

    class A;  // Aの前方宣言
              // これ以降、Aは不完全型となる

    // auto a = sizeof(A);  Aが不完全型であるため、コンパイルエラー
    static_assert(!is_complete_v<A>);
```
```cpp
    //  example/core_lang_spec/incomplete_type_ut.cpp 31

    class A {  // この宣言により、この行以降はAは完全型になる
    public:
        // 何らかの宣言
    };

    auto a = sizeof(A);  // Aが完全型であるため、コンパイル可能
    static_assert(is_complete_v<A>);
```

### 完全型 <a id="SS_19_4_7"></a>
[不完全型](core_lang_spec.md#SS_19_4_6)ではない型を指す。

### ポリモーフィックなクラス <a id="SS_19_4_8"></a>
ポリモーフィックなクラスとは仮想関数を持つクラスや、
ポリモーフィックなクラスから派生したクラスを指す。
なお、純粋仮想関数を持つクラスは、
仮想クラスと呼ばれれる(「[インターフェースクラス](core_lang_spec.md#SS_19_4_11)」参照)。
ポリモーフィックなクラスと、
非ポリモーフィックなクラスは[RTTI](core_lang_spec.md#SS_19_4_9)との組み合わせで動作の違いが顕著となる。

非ポリモーフィックなクラスは非静的なメンバ変数が定義された順にメモリ上に配置されたレイアウトを持つ
(CPUアーキテクチャに依存したパディング領域が変数間に挿入されることもある)。
このようなクラスは[POD](core_lang_spec.md#SS_19_4_5)
(C++20では、[PODという用語は非推奨](https://cpprefjp.github.io/lang/cpp20/deprecate_pod.html)
となり、[トリビアル型](core_lang_spec.md#SS_19_4_1)と[標準レイアウト型](core_lang_spec.md#SS_19_4_3)に用語が分割された)とも呼ばれ、
C言語の構造体のレイアウトと互換性を持つことが一般的である。

ポリモーフィックなクラスは、
仮想関数呼び出しを行う(「[オーバーライドとオーバーロードの違い](cpp_idioms.md#SS_21_11_1)」参照)
ためのメモリレイアウトが必要になる。
それを示すために、まずは下記のようにクラスX、Y、Zを定義する。

```cpp
    //  example/core_lang_spec/class_layout_ut.cpp 4

    class X {
    public:
        virtual int64_t GetX() { return x_; }
        virtual ~X() {}

    private:
        int64_t x_{1};
    };

    class Y : public X {
    public:
        virtual int64_t GetX() override { return X::GetX() + y_; }
        virtual int64_t GetY() { return y_; }
        virtual ~Y() override {}

    private:
        int64_t y_{2};
    };

    class Z : public Y {
    public:
        virtual int64_t GetX() override { return Y::GetX() + z_; }
        virtual int64_t GetY() override { return Y::GetY() + z_; }
        virtual int64_t GetZ() { return z_; }
        virtual ~Z() override {}

    private:
        int64_t z_{3};
    };
```

通常のC++コンパイラが作り出すX、Y、Zの概念的なメモリレイアウトは下記のようになる。

下図中のvtbl(virtual table または virtual function table)とは、
仮想関数ポインタを保持するための構造体であり、仮想関数呼び出しを解決するための仕組みである。

<!-- pu:essential/plant_uml/class_layout.pu--><p><img src="data:image/png;base64,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" /></p>

各クラスがvtblへのポインタを保持するため、このドキュメントで使用している[g++](cpp_idioms.md#SS_21_13_1)では、
sizeof(X)は8ではなく16、sizeof(Y)は16ではなく24、sizeof(Z)は24ではなく32となる。

g++の場合、以下のオプションを使用し、クラスのメモリレイアウトをファイルに出力することができる。

```cpp
    //  example/core_lang_spec/Makefile 23

    CCFLAGS_ADD:=-fdump-lang-class
```

X、Y、Zのメモリレイアウトは以下の様に出力される。

```
    Vtable for X
    X::_ZTV1X: 5 entries
    0     (int (*)(...))0
    8     (int (*)(...))(& _ZTI1X)
    16    (int (*)(...))X::GetX
    24    (int (*)(...))X::~X
    32    (int (*)(...))X::~X

    Class X
       size=16 align=8
       base size=16 base align=8
    X (0x0x7f54bbc23a80) 0
        vptr=((& X::_ZTV1X) + 16)

    Vtable for Y
    Y::_ZTV1Y: 6 entries
    0     (int (*)(...))0
    8     (int (*)(...))(& _ZTI1Y)
    16    (int (*)(...))Y::GetX
    24    (int (*)(...))Y::~Y
    32    (int (*)(...))Y::~Y
    40    (int (*)(...))Y::GetY

    Class Y
       size=24 align=8
       base size=24 base align=8
    Y (0x0x7f54bbc3f000) 0
        vptr=((& Y::_ZTV1Y) + 16)
      X (0x0x7f54bbc23d20) 0
          primary-for Y (0x0x7f54bbc3f000)

    Vtable for Z
    Z::_ZTV1Z: 7 entries
    0     (int (*)(...))0
    8     (int (*)(...))(& _ZTI1Z)
    16    (int (*)(...))Z::GetX
    24    (int (*)(...))Z::~Z
    32    (int (*)(...))Z::~Z
    40    (int (*)(...))Z::GetY
    48    (int (*)(...))Z::GetZ

    Class Z
       size=32 align=8
       base size=32 base align=8
    Z (0x0x7f54bbc3f068) 0
        vptr=((& Z::_ZTV1Z) + 16)
      Y (0x0x7f54bbc3f0d0) 0
          primary-for Z (0x0x7f54bbc3f068)
        X (0x0x7f54bbc43060) 0
            primary-for Y (0x0x7f54bbc3f0d0)
```

このようなメモリレイアウトは、

```cpp
    //  example/core_lang_spec/class_layout_ut.cpp 40

    auto z_ptr = new Z;
```

のようなオブジェクト生成に密接に関係する。その手順を下記の疑似コードにより示す。

```cpp
    // ステップ1  メモリアロケーション
    void* ptr = malloc(sizeof(Z));

    // ステップ2  ZオブジェクトのX部分の初期化
    X* x_ptr = (X*)ptr;
    x_ptr->vtbl = &vtbl_for_X       // Xのコンストラクタ呼び出し処理
    x_ptr->x_ = 1;                  // Xのコンストラクタ呼び出し処理

    // ステップ3  ZオブジェクトのY部分の初期化
    Y* y_ptr = (Y*)ptr;
    y_ptr->vtbl = &vtbl_for_Y       // Yのコンストラクタ呼び出し処理
    y_ptr->y_ = 2;                  // Yのコンストラクタ呼び出し処理

    // ステップ4  ZオブジェクトのZ部分の初期化
    Z* z_ptr = (Z*)ptr;
    z_ptr->vtbl = &vtbl_for_Z       // Zのコンストラクタ呼び出し処理
    z_ptr->z_ = 3;                  // Zのコンストラクタ呼び出し処理
```

オブジェクトの生成がこのように行われるため、Xのコンストラクタ内で仮想関数GetX()を呼び出した場合、
その時のvtblへのポインタはXのvtblを指しており(上記ステップ2)、X::GetX()の呼び出しとなる
(Z::GetX()の呼び出しとはならない)。

なお、オブジェクトの解放は生成とは逆の順番で行われる。

### RTTI <a id="SS_19_4_9"></a>
RTTI(Run-time Type Information)とは、プログラム実行中のオブジェクトの型を導出するための機能であり、
具体的には下記の3つの要素を指す。

* [dynamic_cast](core_lang_spec.md#SS_19_4_9_1)
* [typeid](core_lang_spec.md#SS_19_4_9_2)
* [std::type_info](core_lang_spec.md#SS_19_4_9_3)


#### dynamic_cast <a id="SS_19_4_9_1"></a>
dynamic_castは、実行時の型チェックと安全なダウンキャストを行うためのキャスト演算子であるため、
[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)とは密接な関係を持つ。


下記のような[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)に対しては、

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 8

    class Polymorphic_Base {  // ポリモーフィックな基底クラス
    public:
        virtual ~Polymorphic_Base() = default;
    };

    class Polymorphic_Derived : public Polymorphic_Base {  // ポリモーフィックな派生クラス
    };
```

dynamic_castは下記のように振舞う。

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 25

    auto b = Polymorphic_Base{};
    auto d = Polymorphic_Derived{};

    Polymorphic_Base& b_ref_d = d;
    Polymorphic_Base& b_ref_b = b;

    // ポインタへのdynamic_cast
    auto* d_ptr = dynamic_cast<Polymorphic_Derived*>(&b_ref_d);
    ASSERT_EQ(d_ptr, &d);

    auto* d_ptr2 = dynamic_cast<Polymorphic_Derived*>(&b_ref_b);
    ASSERT_EQ(d_ptr2, nullptr);  // キャストできない場合、nullptrが返る

    // リファレンスへのdynamic_cast
    auto& d_ref = dynamic_cast<Polymorphic_Derived&>(b_ref_d);
    ASSERT_EQ(&d_ref, &d);

    // キャストできない場合、エクセプションのが発生する
    ASSERT_THROW(dynamic_cast<Polymorphic_Derived&>(b_ref_b), std::bad_cast);
```


一方で、下記のような非[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)に対しては、

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 102

    class NonPolymorphic_Base {  // 非ポリモーフィックな基底クラス
    };

    class NonPolymorphic_Derived : public NonPolymorphic_Base {  // 非ポリモーフィックな派生クラス
    };
```

dynamic_castは下記のように振舞う。

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 115

    auto b = NonPolymorphic_Base{};
    auto d = NonPolymorphic_Derived{};

    NonPolymorphic_Base& b_ref_d = d;
    NonPolymorphic_Base& b_ref_b = b;

    #if 0  // 非ポリモーフィックなクラスへのdynamic_castはill-formedになる
    auto* d_ptr = dynamic_cast<NonPolymorphic_Derived*>(&b_ref_d);
    auto* d_ptr2 = dynamic_cast<NonPolymorphic_Derived*>(&b_ref_b);
    
    //virtual関数を持たないため、リファレンスへのdynamic_castはコンパイルできない
    auto& d_ref = dynamic_cast<NonPolymorphic_Derived&>(b_ref_d);
    ASSERT_THROW(dynamic_cast<NonPolymorphic_Derived&>(b_ref_b), std::bad_cast);
    #endif
```

#### typeid <a id="SS_19_4_9_2"></a>
typeidは[RTTI](core_lang_spec.md#SS_19_4_9)オブジェクトの型情報
([std::type_info](core_lang_spec.md#SS_19_4_9_3))を実行時に取得するための演算子である。
dynamic_castとは違い、
typeidのオペランドは[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)のインスタンスでなくても良い。
以下の例では[基本型](core_lang_spec.md#SS_19_1_1)に対するtypeidが返す[std::type_info](core_lang_spec.md#SS_19_4_9_3)の振る舞いを表す。

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 52

    int   i{};
    long  j{};
    auto& i_ref = i;

    auto const& type_info_i     = typeid(i);
    auto const& type_info_i_ref = typeid(i_ref);

    ASSERT_NE(typeid(i), typeid(j));
    ASSERT_EQ(type_info_i, type_info_i_ref);
    ASSERT_STREQ(type_info_i.name(), "i");  // 実装定義の型名(clang++/g++ではintはi)
```

下記のような[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)のインスタンスに関して、

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 8

class Polymorphic_Base {  // ポリモーフィックな基底クラス
public:
    virtual ~Polymorphic_Base() = default;
};

class Polymorphic_Derived : public Polymorphic_Base {  // ポリモーフィックな派生クラス
};
```

typeidが返す[std::type_info](core_lang_spec.md#SS_19_4_9_3)オブジェクトは下記のように振舞う。

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 65

    auto b = Polymorphic_Base{};
    auto d = Polymorphic_Derived{};

    Polymorphic_Base& b_ref_d = d;
    Polymorphic_Base& b_ref_b = b;

    // ポリモーフィックなクラスインスタンスに対するtypeidが返す
    // std::type_infoオブジェクトが示す型は、オペランドの実際の型である。
    // * b_ref_dの表層の型:Polymorphic_Base
    // * b_ref_dの実際の型:Polymorphic_Derived
    // 下記のアサーションはこのことを表す。
    ASSERT_EQ(typeid(b_ref_d), typeid(d));  // b_ref_dとdの実際の型が同じであることを示す
    ASSERT_EQ(typeid(b_ref_b), typeid(b));  // b_ref_bとbの表層の型が同じであることを示す
```

一方で、下記のような非[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)に対しては、

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 102

    class NonPolymorphic_Base {  // 非ポリモーフィックな基底クラス
    };

    class NonPolymorphic_Derived : public NonPolymorphic_Base {  // 非ポリモーフィックな派生クラス
    };
```

typeidが返す[std::type_info](core_lang_spec.md#SS_19_4_9_3)オブジェクトは下記のように振舞う。

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 139

    auto b = NonPolymorphic_Base{};
    auto d = NonPolymorphic_Derived{};

    NonPolymorphic_Base& b_ref_d = d;
    NonPolymorphic_Base& b_ref_b = b;

    // 非ポリモーフィックなクラスインスタンスに対するtypeidが返す
    // std::type_infoオブジェクトが示す型は、オペランドの表層の型である。
    // * b_ref_dの表層の型:Polymorphic_Base
    // * b_ref_dの実際の型:Polymorphic_Derived
    // 下記のアサーションはこのことを表す。
    ASSERT_EQ(typeid(b_ref_d), typeid(b));  // b_ref_dとdの表層の型が同じであることを示す
    ASSERT_EQ(typeid(b_ref_b), typeid(b));  // b_ref_bとbの表層の型が同じであることを示す
```

従って、このような場合のtypeidは静的な型(表層の型)に対しての情報を返すため、
コンパイル時にのみ評価され、ランタイム時に評価されない。

[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)のオブジェクトをオペランドとするtypeidの実行は、
そのオペランドの実際のオブジェクトの型を取得することはすでに示した。
このような場合、オペランド式は実行時に評価される。以下のコードはそのことを表している。

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 87

    Polymorphic_Base    base;
    Polymorphic_Derived derived;
    Polymorphic_Base*   base_ptr = &derived;

    ASSERT_EQ(typeid(Polymorphic_Derived), typeid(*base_ptr));
    ASSERT_EQ(typeid(Polymorphic_Base), typeid(*(base_ptr = &base)));  // 注意

    // ポリモーフィックなクラスは対しては、typeid内の式が実行される
    ASSERT_EQ(base_ptr, &base);  // base_ptr = &baseが実行される
```


一方、非[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)のオブジェクトをオペランドとするtypeidのオペランド式は、
コンパイル時に処理されるため、その式は実行されない。以下のコードはそのことを表している。

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 161

    NonPolymorphic_Base    base;
    NonPolymorphic_Derived derived;
    NonPolymorphic_Base*   base_ptr = &derived;

    ASSERT_NE(typeid(NonPolymorphic_Derived), typeid(*base_ptr));
    ASSERT_EQ(typeid(NonPolymorphic_Base), typeid(*(base_ptr = &base)));  // 注意

    // 非ポリモーフィックなクラスに対しては、typeid内の式は実行されない
    ASSERT_EQ(base_ptr, &derived);  // base_ptr = &baseは実行されない
```

#### std::type_info <a id="SS_19_4_9_3"></a>
type_infoクラスは、[typeid](----)演算子によって返される、型の情報が格納された型である。

std::type_infoはコンパイラの実装で定義された型名を含んでいる。
以下のコードで示したように`std::type_info::name()`によりその型名を取り出すことができる。

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 179

    auto s = std::string{"str"};
    auto v = std::string_view{"str"};
    auto b = std::byte{0b1001};

    ASSERT_STREQ(typeid(s).name(), "Ss");       // 実装定義の型名
    ASSERT_STREQ(typeid(b).name(), "St4byte");  // 実装定義の型名
    ASSERT_STREQ(typeid(v).name(), "St17basic_string_viewIcSt11char_traitsIcEE");
```

`std::type_info::name()`が返すCスタイルの文字列リテラルを、
「人間が認知できる元の型名に戻す関数」を通常のコンパイラは独自に提供する。
このドキュメントのコードのコンパイルに使用している[g++](cpp_idioms.md#SS_21_13_1)/[clang++](cpp_idioms.md#SS_21_13_2)では、
そのような関数は、`abi::__cxa_demangle`である。

`std::type_info::name()`と`abi::__cxa_demangle`を利用して、
オブジェクトの[被修飾型](core_lang_spec.md#SS_19_14_6)名をstd::stringオブジェクトとして取り出す関数とその使用例を以下に示す。

```cpp
    //  example/core_lang_spec/rtti_ut.cpp 191

    #include <cxxabi.h>  // g++/clang++実装依存ヘッダ abi::__cxa_demangleの宣言

    #include <memory>
    #include <string>

    template <typename T>
    std::string type2str(T&& obj)
    {
        int status;

        // objに基づく型情報を取得
        auto demangled = std::unique_ptr<char, decltype(&std::free)>{abi::__cxa_demangle(typeid(obj).name(), 0, 0, &status),
                                                                     &std::free};

        return demangled ? demangled.get() : "unknown";
    }
```
```cpp
    //  example/core_lang_spec/rtti_ut.cpp 213

    int   i{};
    auto  s     = std::string{"str"};
    auto& s_ref = s;
    auto  v     = std::string_view{"str"};

    ASSERT_EQ(type2str(i), "int");
    ASSERT_EQ(type2str(s), "std::string");
    ASSERT_EQ(type2str(s_ref), "std::string");
    ASSERT_EQ(type2str(v), "std::basic_string_view<char, std::char_traits<char> >");

    auto b = Polymorphic_Base{};
    auto d = Polymorphic_Derived{};

    Polymorphic_Base& b_ref_d = d;
    Polymorphic_Base& b_ref_b = b;

    ASSERT_EQ(type2str(b_ref_d), "Polymorphic_Derived");  // b_ref_dの実際の型はPolymorphic_Derived
    ASSERT_EQ(type2str(b_ref_b), "Polymorphic_Base");     // b_ref_bの実際の型はPolymorphic_Base
```

### Run-time Type Information <a id="SS_19_4_10"></a>
「[RTTI](core_lang_spec.md#SS_19_4_9)」を参照せよ。


### インターフェースクラス <a id="SS_19_4_11"></a>
インターフェースクラスとは、純粋仮想関数のみを持つ抽象クラスのことを指す。
インターフェースクラスは、クラスの実装を提供することなく、
クラスのインターフェースを定義するために使用される。
インターフェースクラスは、クラスの仕様を定義するために使用されるため、
多くの場合、抽象基底クラスとして使用される。

```cpp
    //  example/core_lang_spec/interface_class.cpp 8

    class InterfaceClass {  // インターフェースクラス
    public:
        virtual void DoSomething(int32_t) = 0;
        virtual bool IsXxx() const        = 0;
        virtual ~InterfaceClass()         = 0;
    };

    class NotInterfaceClass {  // メンバ変数があるためインターフェースクラスではない
    public:
        NotInterfaceClass();
        virtual void DoSomething(int32_t) = 0;
        virtual bool IsXxx() const        = 0;
        virtual ~NotInterfaceClass()      = 0;

    private:
        int32_t num_;
    };
```

### constインスタンス <a id="SS_19_4_12"></a>
constインスタンスは、ランタイムまたはコンパイル時に初期化され、
その後、状態が不変であるインスタンスである。
必ずしも以下に示すようにconstインスタンスがコンパイル時に値が定まっているわけではない。
[constexprインスタンス](core_lang_spec.md#SS_19_5_6)はconstインスタンスである。
C++03までのコンパイラに、
最適化の一環で`static const`インスタンスを[constexprインスタンス](core_lang_spec.md#SS_19_5_6)と扱うものもあった。


```cpp
    //  example/core_lang_spec/const_ut.cpp 12

    using namespace std;
    auto const str = string{"str"};  // strはプログラムがこの行を通過するときに初期化

    char const* c_str = str.c_str();

    static_assert(!is_const_v<decltype(c_str)>);
    c_str = nullptr;                                                  // c_strは変数としてconstではない
    static_assert(is_const_v<remove_reference_t<decltype(*c_str)>>);  // *cは_strはconst
    static_assert(is_same_v<char const&, decltype(*c_str)>);          // *c_strはconstリファレンス

    char const* const cc_str = c_str;

    static_assert(is_const_v<decltype(cc_str)>);
    // cc_str = nullptr;  // cc_strは変数としてconstであるためコンパイルエラー
    static_assert(is_const_v<remove_reference_t<decltype(*cc_str)>>);  // *cc_strはconst
    static_assert(is_same_v<char const&, decltype(*cc_str)>);          // *cc_strはconstリファレンス

    constexpr int c_int = 1;
    static_assert(is_const_v<decltype(c_int)>);  // c_intはcons
```

## 定数式とコンパイル時評価 <a id="SS_19_5"></a>

### constexpr <a id="SS_19_5_1"></a>
constexprはC++11で導入されたキーワードで、
関数や変数をコンパイル時に評価可能にする。
これにより、定数計算がコンパイル時に行われ、
実行時のパフォーマンスが向上し、コンパイル時にエラーを検出できることがある。

### constexpr定数 <a id="SS_19_5_2"></a>
C++11以前で定数を定義する方法は、

* マクロ定数
* [enum](core_lang_spec.md#SS_19_3_1)
* static const(定数となるか否かは、コンパイラの実装依存に依存する)

の方法があったが、それぞれの方法には下記のような問題がある。

* マクロにはスコープが無く、`#undef`できてしまう。
* enumには整数の定義に限られる。
* static constに関しては、コンパイラの実装依存に依存する。

こういった問題を解決できるのがconstexpr定数である。constexpr定数とは下記のような定数を指す。

```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 11

    template <int N>
    struct Templ {
        static constexpr auto value = N;  // valueは定数
    };
```
```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 20

    constexpr int a = 5;  // aは定数であるためかきのような使い方ができる
    static_assert(a == 5);

    constexpr int b = 5;  // bは定数でないため、下記のような使い方ができない
    // static_assert(b == 5);  // コンパイルエラー

    constexpr double PI{3.14159265358979323846};  // PIはconstexpr

    auto templ = Templ<a>{};  // aはconstexprなのでaの初期化が可能

    static_assert(templ.value == 5);
```

constexpr定数がif文のオカレンスになる場合、[constexpr if文](core_lang_spec.md#SS_19_11_12)することで、
[ill-formed](core_lang_spec.md#SS_19_14_1)を使用した場合分けが可能になる。


### constexpr関数 <a id="SS_19_5_3"></a>
関数に`constexpr`をつけて宣言することで定数を定義することができる。
constexpr関数の呼び出し式の値がコンパイル時に確定する場合、
その値はconstexpr定数となるため、関数呼び出しが発生しないため、実行効率が向上する。
一方で、constexpr関数の呼び出し式の値が、コンパイル時に確定しない場合、
通常の関数呼び出しと同じになる。

```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 39

    constexpr int f(int a) noexcept { return a * 3; }  // aがconstexprならばf(a)もconstexpr
    int g(int a) noexcept { return a * 3; }            // aがconstexprであってもg(a)は非constexpr
```
```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 49

    auto x = int{0};

    constexpr auto a = f(3);     // f(3)はconstexprなのでaの初期化が可能
    // constexpr auto b = f(x);  // xは非constexprなのでbの初期化はコンパイルエラー
    auto const c = f(3);         // cはconstexpr定数と定義とすべき
    // constexpr auto d = g(3);  // g(3)は非constexprなのでdの初期化はコンパイルエラー
    auto const e = g(x);         // eはここで初期化して、この後不変
```

C++11の規約では、constexpr関数の制約は厳しく、
for/if文や条件分岐のような処理を含むことができなかったため、
下記のコード例で示した通り、条件演算子とリカーシブコールをうことが多かった。

```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 64

    constexpr uint64_t bit_mask(uint32_t max) { return max == 0 ? 0 : (1ULL << (max - 1)) | bit_mask(max - 1); }
    constexpr uint64_t bit_mask_0 = bit_mask(4);  // C++11ではコンパイルエラー
    static_assert(0b1111 == bit_mask_0);
```
このため、可読性、保守性があったため、C++14で制約が緩和され、
さらにC++17では for/if文などの一般的な制御構文も使えるようになった。

```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 70

    constexpr uint64_t bit_mask_for(uint32_t max)
    {
        uint64_t ret = 0;

        for (auto i = 0u; i < max; ++i) {
            ret |= 1ULL << i;
        }

        return ret;
    }
    constexpr uint64_t bit_mask_1 = bit_mask_for(4);  // C++17からサポート
    static_assert(0b1111 == bit_mask_1);
```

### コア定数式 <a id="SS_19_5_4"></a>
コア定数式(core constant expression)とは以下の条件を満たす式である。

1. 以下のいずれかに該当する式であること  
   - リテラル
   - constexpr変数への参照
   - 定数式で初期化された参照
   - constexprサブオブジェクトへの参照
   - constexpr関数呼び出し
   - sizeof演算子の適用結果
   - typeid演算子の適用結果(式の値が[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)である場合を除く)

2. 以下のすべてを満たすこと:  
   - 浮動小数点の比較演算を含まない
   - インクリメント/デクリメント演算を含まない
   - 代入演算を含まない
   - 動的メモリ割り当てを含まない
   - 仮想関数の呼び出しを含まない
   - 未定義動作を引き起こさない
   - エクセプションを投げない
   - アドレス取得演算子の使用が定数式の評価に限定される

3. その式の評価において:  
   - すべてのサブ式も定数式である
   - 使用されるすべての変数は定数式で初期化されている
   - 呼び出されるすべての関数はconstexpr関数である

このドキュメントでは慣用的に[constexpr定数](core_lang_spec.md#SS_19_5_2)と呼んでいる概念が、コア定数式である。

### リテラル型 <a id="SS_19_5_5"></a>
constexpr導入後のC++11の標準では、下記の条件を満たすクラスは、

* constexprコンストラクタを持つ
* すべてのメンバ変数がリテラル型である
* 仮想関数や仮想基底クラスを持たない

constexpr定数もしくはconstexprインスタンスをコンストラクタに渡すことにより、
[constexprインスタンス](core_lang_spec.md#SS_19_5_6)を生成できる。

このようなクラスは慣習的にリテラル型(literal type)と呼ばれる。

以下にリテラル型を例示する。

```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 87

    class Integer {
    public:
        constexpr Integer(int32_t integer) noexcept : integer_{integer} {}
        constexpr operator int() const noexcept { return integer_; }  // constexprメンバ関数はconst
        constexpr int32_t Allways2() const noexcept { return 2; }     // constexprメンバ関数はconst
        static constexpr int32_t Allways3() noexcept { return 3; }    // static関数のconstexpr化

    private:
        int32_t integer_;
    };
```
```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 105

    constexpr auto i5 = 5;                // i5はconstexprインスタンス
    constexpr auto int_5 = Integer{i5};   // int_5はconstexprインスタンス
    static_assert(int_5 == 5);            // intへの暗黙の型変換

    auto i3  = 3;                         // i3はconstexpr定数ではない
    auto int_3 = Integer{i3};             // int_3はconstexprインスタンスではない
    // static_assert(int_3 == 5);         // int_3がconstexprではないため、コンパイルエラー
    static_assert(int_3.Allways2() == 2); // int_3はconstexprインスタンスではないが、
                                          // int_3.Allways2()はconstexprt定数
    static_assert(int_3.Allways3() == 3); // int_3はconstexprインスタンスではないが、
                                          // int_3.Allways3()はconstexprt定数
```

### constexprインスタンス <a id="SS_19_5_6"></a>
[constexpr定数](core_lang_spec.md#SS_19_5_2)を引数にして、[リテラル型](core_lang_spec.md#SS_19_5_5)のconstexprコンストラクタを呼び出せば、
constexprインスタンスを生成できる。このリテラル型を使用して下記のように[ユーザー定義リテラル](core_lang_spec.md#SS_19_2_6)
を定義することで、constexprインスタンスをより簡易に使用することができるようになる。

```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 122

    constexpr Integer operator"" _i(unsigned long long int value)  // ユーザ定義リテラルの定義
    {
        return Integer(static_cast<int32_t>(value));
    }
```
```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 132

    constexpr auto i = 123_i;
    static_assert(i == 123);
    static_assert(std::is_same_v<decltype(i), Integer const>);
```

### consteval <a id="SS_19_5_7"></a>
constevalはC++20から導入されたキーワードであり、
呼び出しが必ずコンパイル時に評価されなければならない関数を定義するために使用される。
この関数は、コンパイル時に評価できない引数や式が与えられるとコンパイルエラーとなる。
constexpr関数が「コンパイル時に評価されることもできる」のに対し、
consteval関数は「必ずコンパイル時に評価されなければならない」という点で異なる。

この特性により、ランタイム評価を完全に排除した定数生成専用関数を記述でき、
パフォーマンスの最適化や定数検証（static_assertなど）に利用できる。
consteval関数の呼び出しは、その結果が定数式でなければコンパイルエラーとなる。

```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 154

    #if __cplusplus >= 202002L  // c++20
    consteval uint64_t bit_mask(uint32_t max)  // コンパイル時、評価ができなければエラー

    #else // C++17
    constexpr uint64_t bit_mask(uint32_t max)  // コンパイル時、評価されるとは限らない
    #endif
    {
        if (max == 0) {
            return 0;
        }
        else {
            return (1ULL << (max - 1)) | bit_mask(max - 1);
        }
    }
```
```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 176

    static_assert(0b1111'1111 == bit_mask(8));

    // auto i = 8UL;         // bit_maskがconstevalであるため、コンパイルエラー
    constexpr auto i = 8UL;  // iがconstexprであるためbit_maskがコンパイル時評価されるため、
    auto bm = bit_mask(i);   // bit_mask(i)の呼び出しは効率的になる
                             // bmをconsexprにするとさらに効率的になる

    ASSERT_EQ(0b1111'1111, bm);
```

### constinit <a id="SS_19_5_8"></a>
constinitはC++20から導入されたキーワードであり、
静的記憶域期間（static、namespaceスコープ）またはthread_local変数が、
コンパイル時に初期化されることを保証するために使用される。
これにより、[Static Initialization Order Fiasco(静的初期化順序問題)](cpp_idioms.md#SS_21_12_12)を回避できる。

このキーワードを付与すると、初期化が動的である場合にはコンパイルエラーとなる。
ただし、constexprと異なり、変数自体がconstになるわけではないため、再代入は可能である。
また、constinitはローカル(自動変数)には意味を持たない。

```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 192

    #if __cplusplus >= 202002L  // c++20

    // constinit は静的・スレッドローカル変数の初期化が動的でないことを保証する。
    // この変数は const にはならず、後から変更可能である。
    constinit float pi = 3.14f;

    // C++17以前ではconstinitが存在しないため、constexprを使用する。
    // ただしconstexprでは変数がconstになり、再代入はできない点が異なる。
    constinit uint32_t mask = bit_mask(16);

    #else  // C++17

    // C++17ではconstinitが存在しないため、constexprを代用する。
    // ただしconstexprでは変数がconstとなり、再代入はできない。
    constexpr float    pi   = 3.14f;
    constexpr uint32_t mask = bit_mask(16);
    #endif
```

### constexprラムダ <a id="SS_19_5_9"></a>
constexprラムダはC++17から導入された機能であり、以下の条件を満たした[ラムダ式](core_lang_spec.md#SS_19_10_3)である。

* 引数やラムダ式内の処理がコンパイル時に評価可能である必要がある。
  すべての処理はconstexpr関数のようにコンパイル時に確定する必要があり、
  動的な処理やランタイムでしか決定できないものは含めることができない。

* ラムダ内で使用される関数や式もconstexprでなければならない。
  たとえば、関数の呼び出しや算術演算は、コンパイル時に評価可能なものであることが求められる。

* ラムダキャプチャはconstexprに適合している必要がある。
  キャプチャする変数もコンパイル時に確定できるものに限られる。
  動的な変数をキャプチャすると、コンパイルエラーとなる。

* エクセプション処理 (try/catch/throw) が禁止されている。
  constexprラムダでは、エクセプション処理を含むことはできない。

* 動的メモリの割り当て(new/delete) が禁止されている。
  これらの操作はコンパイル時には行えないため、constexprラムダでは使用できない。

```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 217

    constexpr auto factorial = [](int n) {  // constexpr ラムダの定義
        int result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    };

    constexpr int fact_5 = factorial(5);  // コンパイル時に計算される
    static_assert(fact_5 == 120);
```
```cpp
    //  example/core_lang_spec/constexpr_ut.cpp 234

    constexpr auto factorial = [](auto self, int n) -> int {  // リカーシブconstexprラムダ
        return (n <= 1) ? 1 : n * self(self, n - 1);
    };

    constexpr int fact_5 = factorial(factorial, 5);  // コンパイル時の評価
    static_assert(fact_5 == 120);
```

## オブジェクト生成と初期化 <a id="SS_19_6"></a>
### 特殊メンバ関数 <a id="SS_19_6_1"></a>
特殊メンバ関数とは下記の関数を指す。

* デフォルトコンストラクタ
* copyコンストラクタ
* copy代入演算子
* moveコンストラクタ
* move代入演算子
* デストラクタ

以下のメンバ関数は特殊関数ではないが、C++20から特殊関数と同様に`=default`とすることで自動生成される。

* [==演算子](core_lang_spec.md#SS_19_6_3)  
  クラス内のすべてのメンバが==をサポートしている場合、`= default`とすることで自動生成される。
* [<=>演算子](core_lang_spec.md#SS_19_6_4_1)  
  すべてのメンバが[<=>演算子](core_lang_spec.md#SS_19_6_4_1)での比較可能である場合、`= default`とすることで自動生成される。 

ユーザがこれらを一切定義しない場合、または一部のみを定義する場合、
コンパイラは、下記のテーブル等で示すルールに従い、特殊関数メンバの宣言、定義の状態を定める。

左1列目がユーザによる各関数の宣言を表し、2列目以降はユーザ宣言の影響による各関数の宣言の状態を表す。  
下記表において、

* 「`= default`」とは、「コンパイラによってその関数が`= default`と宣言された」状態であることを表す。
* 「~~= default~~」とは、`= default`と同じであるが、バグが発生しやすいので推奨されない。
* 「宣言無し」とは、「コンパイラによってその関数が`= default`と宣言された状態ではない」ことを表す。
    * 「moveコンストラクタが`= default`と宣言された状態ではない」且つ
      「copyコンストラクタが宣言されている」場合、
      rvalueを使用したオブジェクトの初期化には、
      moveコンストラクタの代わりにcopyコンストラクタが使われる。
    * 「move代入演算子が`= default`と宣言された状態ではない」且つ
      「copy代入演算子が宣言されている」場合、
      rvalueを使用したオブジェクトの代入には、
      move代入演算子の代わりにcopy代入演算子が使われる。
* 「= delete」とは「コンパイラによってその関数が= deleteと宣言された」状態であることを表す。

|  user-defined  |default ctor|   dtor  |  copy ctor  | copy assign |move ctor|move assign|   `==`   |   `<=>`  |
|:--------------:|:----------:|:-------:|:-----------:|:-----------:|:-------:|:---------:|:--------:|:--------:|
|   undeclared   |  = default |= default|  = default  |  = default  |= default| = default |undeclared|undeclared|
|non-default ctor| undeclared |= default|  = default  |  = default  |= default| = default |undeclared|undeclared|
|  default ctor  |      -     |= default|  = default  |  = default  |= default| = default |undeclared|undeclared|
|      dtor      |  = default |    -    |~~= default~~|~~= default~~|= default| = default |undeclared|undeclared|
|    copy ctor   |  = default |= default|      -      |~~= default~~|= default| = default |undeclared|undeclared|
|   copy assign  |  = default |= default|~~= default~~|      -      |= default| = default |undeclared|undeclared|
|    move ctor   |  = default |= default|   = delete  |   = delete  |    -    | = default |undeclared|undeclared|
|   move assign  |  = default |= default|   = delete  |   = delete  |= default|     -     |undeclared|undeclared|
|      `==`      |      -     |    -    |      -      |      -      |    -    |     -     |     -    |undeclared|
|      `<=>`     |      -     |    -    |      -      |      -      |    -    |     -     |undeclared|     -    |


**テーブル注**  

* C++14以前と、C++17以降での仕様の差は以下のようになる。
    * C++14以前では、コピーコンストラクタやコピー代入演算子をユーザ定義すると、
      ムーブコンストラクタ／ムーブ代入演算子は自動生成されず` = delete`となる。
    * C++17以降では、コピー系をユーザ定義していても、ムーブ系は自動生成される(` = default`と同等になる)ことがある。
      コンパイラは「コピー系の存在」だけではムーブ系を削除しない。
      ただし、ムーブ不可能なメンバや基底がある場合は、結果的に` = delete`になる。
    * C++17以降では、` = default`された特殊メンバ関数は明示的に`noexcept`推定され、ムーブセマンティクスの活用がしやすくなる。
    * C++20以降では、比較演算子(`==, <=>`)も`= default`によって自動生成可能だが、特殊メンバ関数とは分類が異なるが、
      上記テーブルでは同じように扱う。
* ctor: コンストラクタを指す。
* dtor: デストラクタを指す。
* assign: 代入演算子（assignment）を指す。
* user-defined: この列の関数がユーザによって定義されていることを指す。
  従って、non-default ctorは、デフォルトコンストラクタでないコンストラクタが定義されている行を指す。
* undeclared: 特定の特殊メンバ関数がユーザによって宣言されていないことを指し、
  コンパイラによる自動生成もされていないことを指す。
* 「~~= default~~」とは、`= default`と同様に自動生成されるが、
  場合によっては不適切な挙動を引き起こす可能性があるため、推奨されない。


上記表より、下記のようなことがわかる。

* ユーザが上記6メンバ関数を一切宣言しない場合、それらはコンパイラにより暗黙に宣言、定義される。
* ユーザがcopyコンストラクタを宣言した場合、デフォルトコンストラクタは暗黙に宣言、定義されない。
* moveコンストラクタ、move代入演算子は、
  以下のいずれもが明示的に宣言されていない場合にのみ暗黙に宣言、定義される。
    * copyコンストラクタ
    * copy代入演算子(operator =)
    * moveコンストラクタ
    * move代入演算子
    * デストラクタ

* ユーザがmoveコンストラクタまたはmove代入演算子を宣言した場合、
  copyコンストラクタ、copy代入演算子は`= delete`される。


これらの特殊メンバ関数に対しての設計のガイドラインには、以下のようなものがある。

* [ゼロの原則(Rule of Zero)](cpp_idioms.md#SS_21_7_1)
* [五の原則(Rule of Five)](cpp_idioms.md#SS_21_7_2)

この2つの原則(ガイドライン)の使い分けに関しては、

* リソース管理を外部([RAII(scoped guard)](cpp_idioms.md#SS_21_1_2)クラス)に任せられる場合: ゼロの法則を採用し、特殊メンバ関数を明示的に定義しない。
* リソースをクラス内で直接管理する場合: 五の法則を採用し、すべての特殊メンバ関数を適切に定義する。

とすることで安全で保守性性の高いコードを設計できる。

#### 初期化子リストコンストラクタ <a id="SS_19_6_1_1"></a>
初期化子リストコンストラクタ([リスト初期化](core_lang_spec.md#SS_19_6_5)用のコンストラクタ)とは、
{}による[リスト初期化](core_lang_spec.md#SS_19_6_5)をサポートするためのコンストラクタである。
下記コードでは、 E::E(std::initializer_list\<uint32_t>)が初期化子リストコンストラクタである。

```cpp
    //  example/core_lang_spec/constructor_ut.cpp 6

    class E {
    public:
        E() : str_{"default constructor"} {}

        // 初期化子リストコンストラクタ
        explicit E(std::initializer_list<uint32_t>) : str_{"initializer list constructor"} {}

        explicit E(uint32_t, uint32_t) : str_{"uint32_t uint32_t constructor"} {}

        std::string const& GetString() const { return str_; }

    private:
        std::string const str_;
    };

    TEST(Constructor, initializer_list_constructor)
    {
        E const e0;
        ASSERT_EQ("default constructor", e0.GetString());

        E const e1{};
        ASSERT_EQ("default constructor", e1.GetString());

        E const e2{3, 4};  // E::E(uint32_t, uint32_t)の呼び出しと区別が困難
        ASSERT_EQ("initializer list constructor", e2.GetString());

        E const e3(3, 4);  // E::E(std::initializer_list<uint32_t>)の呼び出しと区別が困難
        ASSERT_EQ("uint32_t uint32_t constructor", e3.GetString());
    }
```

デフォルトコンストラクタと初期化子リストコンストラクタが、
それぞれに定義されているクラスの初期化時に空の初期化子リストが渡された場合、
デフォルトコンストラクタが呼び出される。

初期化子リストコンストラクタと、
「その初期化子リストの要素型と同じ型の仮引数のみを受け取るコンストラクタ
(上記コードのE::E(uint32_t, uint32_t))」
の両方を持つクラスの初期化時にどちらでも呼び出せる初期化子リストが渡された場合({}を使った呼び出し)、
初期化子コンストラクタが呼び出される。

#### 継承コンストラクタ <a id="SS_19_6_1_2"></a>
継承コンストラクタとは、基底クラスで定義したコンストラクタ群を、
派生クラスのインターフェースとしても使用できるようにするための機能である。
下記コードのように、継承コンストラクタは派生クラス内でusingを用いて宣言される。

```cpp
    //  example/core_lang_spec/constructor_ut.cpp 40

    class Base {
    public:
        explicit Base(int32_t b) noexcept : b_{b} {}
        virtual ~Base() = default;
        // ...
    };

    class Derived : public Base {
    public:
        using Base::Base;  // 継承コンストラクタ
    #if 0
        Derived(int32_t b) : Base{b} {}  // オールドスタイル
    #endif
    };

    void f() noexcept
    {
        Derived d{1};  // Derived::Derived(int32_t)が使える
        // ...
    }
```

#### 委譲コンストラクタ <a id="SS_19_6_1_3"></a>
委譲コンストラクタとは、コンストラクタから同じクラスの他のコンストラクタに処理を委譲する機能である。
以下のコード中では、委譲コンストラクタを使い、
A::A(uint32_t)の処理をA::A(std::string const&)へ委譲している。

```cpp
    //  example/core_lang_spec/constructor_ut.cpp 72

    class A {
    public:
        explicit A(std::string str) : str_{std::move(str)}
        {
            // ...
        }

        explicit A(uint32_t num) : A{std::to_string(num)}  // 委譲コンストラクタ
        {
        }

    private:
        std::string str_;
    };
```

### explicit コンストラクタと型変換制御 <a id="SS_19_6_2"></a>

#### explicit <a id="SS_19_6_2_1"></a>
explicitは、コンストラクタに対して付与することで、
コンストラクタによる暗黙の型変換を禁止するためのキーワードである。
暗黙の型変換とは、ある型の値を別の型の値に自動的に変換する言語機能を指す。
explicitキーワードを付けることで、意図しない型変換を防ぎ、コードの堅牢性を高めることがでできる。

この節で説明するexplicitの機能は下記のような項目に渡って説明を行う。

- [暗黙の型変換](core_lang_spec.md#SS_19_6_2_2)
- [暗黙の型変換抑止](core_lang_spec.md#SS_19_6_2_3)
- [explicit(COND)](core_lang_spec.md#SS_19_6_2_4)
- [explicit type operator()](core_lang_spec.md#SS_19_6_2_5)

#### 暗黙の型変換 <a id="SS_19_6_2_2"></a>
この節で扱う暗黙の型変換とは、
以下に示したような「非explicitなコンストラクタを持つクラス」による暗黙の型変換を指し、
[汎整数型昇格](core_lang_spec.md#SS_19_1_7)や[算術変換](core_lang_spec.md#SS_19_1_6)等を指さない。

```cpp
    //  example/core_lang_spec/implicit_conversion_ut.cpp 8

    class Person {
    public:
        Person(char const* name, uint32_t age = 0) : name_{name}, age_{age} {}
        Person(Person const&)            = default;
        Person& operator=(Person const&) = default;

        std::string const& GetName() const noexcept { return name_; }
        uint32_t           GetAge() const noexcept { return age_; }

    private:
        std::string name_;  // コピーをするため非const
        uint32_t    age_;
    };

    #if __cplusplus <= 201703L  // c++17
    bool operator==(Person const& lhs, Person const& rhs) noexcept
    {
        return std::tuple(lhs.GetName(), lhs.GetAge()) == std::tuple(rhs.GetName(), rhs.GetAge());
    }

    #else  // c++20
    auto operator<=>(Person const& lhs, Person const& rhs) noexcept
    {
        return std::tuple(lhs.GetName(), lhs.GetAge()) <=> std::tuple(rhs.GetName(), rhs.GetAge());
    }

    // <=>から自動的に==が生成されないため、明示的に定義する必要がある
    bool operator==(Person const& lhs, Person const& rhs) noexcept { return (lhs <=> rhs) == 0; }
    #endif
```

上記のクラスPersonを使用して、下記のようなコードをコンパイルできるようにする機能である。

```cpp
    //  example/core_lang_spec/implicit_conversion_ut.cpp 40

    void f(Person const& person) noexcept
    {
        // ...
    }

    void using_implicit_coversion()
    {
        f("Ohtani");  // "Ohtani"はPerson型ではないが、コンパイル可能
    }
```

この記法は下記コードの短縮形であり、コードの見た目をシンプルに保つ効果がある。

```cpp
    //  example/core_lang_spec/implicit_conversion_ut.cpp 54

    void not_using_implicit_coversion()
    {
        f(Person{"Ohtani"});  // 本来は、fの引数はPerson型
    }
```

この記法は下記のようにstd::string等のSTLでも多用され、その効果は十分に発揮されているものの、

```cpp
    //  example/core_lang_spec/implicit_conversion_ut.cpp 66

    auto otani = std::string{"Ohtani"};

    // ...

    if (otani == "Ohtani") {  // 暗黙の型変換によりコンパイルできる
        // ...
    }
```

以下のようなコードがコンパイルできてしまうため、わかりづらいバグの元にもなる。

```cpp
    //  example/core_lang_spec/implicit_conversion_ut.cpp 80

    auto otani = Person{"Ohtani", 26};

    // ...

    if (otani == "Otani") {  // このコードがコンパイルされる。
        // ...
    }

    if (otani == Person{"Otani"}) {  // 暗黙の型変換を使わない記法
        // ...
    }
```

下記のようにコンストラクタにexplicitを付けて宣言することにより、この問題を防ぐことができる。

```cpp
    //  example/core_lang_spec/implicit_conversion_ut.cpp 112

    class Person {
    public:
        explicit Person(char const* name, uint32_t age = 0) : name_{name}, age_{age} {}
        Person(Person const&)            = default;
        Person& operator=(Person const&) = default;

        // ...
    };

    void prohibit_implicit_coversion()
    {
    #if 0  // explicit付きのコンストラクタを持つPersonと違い、コンパイルできない。
        f("Ohtani");
    #else
        f(Person{"Ohtani"});
    #endif

        auto otani = Person{"Ohtani", 26};

        // ...

    #if 0
        if (otani == "Otani") {  // このコードもコンパイルできない。
            // ...
        }
    #else
        if (otani == Person{"Otani", 26}) {  // この記述を強制できる。
            // ...
        }
    #endif
    }
```

std::stringは暗黙の型変換を許して良く、(多くの場合)Personには暗黙の型変換をしない方が良い理由は、

* std::stringの役割は文字列の管理と演算のみであるため、
  std::stringを文字列リテラルと等価なもののように扱っても違和感がない
* Personは、明らかに文字列リテラルと等価なものではない

といった[セマンティクス](cpp_idioms.md#SS_21_14_1)的観点によるものである。

クラスPersonと同様に、
ほとんどのユーザ定義クラスには非explicitなコンストラクタによる暗黙の型変換は必要ない。

#### 暗黙の型変換抑止 <a id="SS_19_6_2_3"></a>
explicit宣言されていないコンストラクタを持つクラスは、
下記のコードのように[暗黙の型変換](core_lang_spec.md#SS_19_6_2_2)が起こる。

```cpp
    //  example/core_lang_spec/explicit_ut.cpp 10

    struct A {
        A(int a) : x{a} {}
        int x;
    };

    A f(A a) { return a; };
```
```cpp
    //  example/core_lang_spec/explicit_ut.cpp 21

    A a = 1;  // A::Aがexplicitでないため、iはA{1}に変換される
    ASSERT_EQ(a.x, 1);

    auto b = f(2);  // A::Aがexplicitでないため、2はA{2}に変換される
    ASSERT_EQ(b.x, 2);
```

暗黙の型変換はわかりづらいバグを生み出してしまうことがあるため、
下記のように適切にexplicitを使うことで、このような変換を抑止することができる。

```cpp
    //  example/core_lang_spec/explicit_ut.cpp 34

    struct A {
        explicit A(int a) : x{a} {}  // 暗黙の型変換の抑止
        int x;
    };

    A f(A a) { return a; };
```
```cpp
    //  example/core_lang_spec/explicit_ut.cpp 45

    // A a = 1;    // A::Aがexplicitであるため、コンパイルエラー
    // auto b = f(2);  // A::Aがexplicitであるため、コンパイルエラー
```

C++03までは、[一様初期化](core_lang_spec.md#SS_19_6_6)がサポートされていなかったため、
explicitは単一引数のコンストラクタに使用されることが一般的であった。

C++11からサポートされた[一様初期化](core_lang_spec.md#SS_19_6_6)を下記のように使用することで、
暗黙の型変換を使用できる。

```cpp
    //  example/core_lang_spec/explicit_ut.cpp 56

    struct A {
        A(int a, int b) : x{a}, y{b} {}
        int x;
        int y;
    };

    A    f(A a) { return a; };
    bool operator==(A lhs, A rhs) { return std::tuple(lhs.x, lhs.x) == std::tuple(rhs.x, rhs.x); }
```
```cpp
    //  example/core_lang_spec/explicit_ut.cpp 70

    A a = {1, 2};  // A::Aがexplicitでないため、iはA{1, 2}に変換される
    ASSERT_EQ(a, (A{1, 2}));

    auto b = f({2, 1});  // A::Aがexplicitでないため、2はA{2,1}に変換される
    ASSERT_EQ(b, (A{2, 1}));
```

以下に示す通り、コンストラクタの引数の数によらず、
C++11からは暗黙の型変換を抑止したい型のコンストラクタにはexplicit宣言することが一般的となっている。

```cpp
    //  example/core_lang_spec/explicit_ut.cpp 82

    struct A {
        explicit A(int a, int b) : x{a}, y{b} {}
        int x;
        int y;
    };

    A    f(A a) { return a; };
    bool operator==(A lhs, A rhs) { return std::tuple(lhs.x, lhs.x) == std::tuple(rhs.x, rhs.x); }
```
```cpp
    //  example/core_lang_spec/explicit_ut.cpp 96

    // A a = {1, 2};  // A::Aがexplicitであるため、コンパイルエラー
    // auto b = f({2, 1});  // A::Aがexplicitであるため、コンパイルエラー
```

#### explicit(COND) <a id="SS_19_6_2_4"></a>
C++20から導入されたexplicit(COND)は、
コンストラクタや変換演算子に対して、
特定の条件下で暗黙の型変換を許可または禁止する機能である。
CONDには、型特性や定数式などの任意のconstexprな条件式を指定できる。
以下にこのシンタックスの単純な使用例を示す。

```cpp
    //  example/core_lang_spec/explicit_ut.cpp 162

    template <typename T>  // Tが整数型の場合、暗黙の型変換を許可
    struct S {
    #if __cplusplus >= 202002L  // c++20
        explicit(!std::is_integral_v<T>) S(T x) : value{x} {}

    #else  // c++17
        // T が整数型でない場合に有効なコンストラクタ
        template <typename U = T, std::enable_if_t<!std::is_integral_v<U>>* = nullptr>
        explicit S(U x) : value{x} { }

        // T が整数型の場合に有効な非explicitコンストラクタ
        // T が整数型の場合に有効な非explicitコンストラクタ
        template <typename U = T, std::enable_if_t<std::is_integral_v<U>>* = nullptr>
        S(U x) : value{x} { }
    #endif

        T value;
    };

    template <typename T>  // 推論ガイド
    S(T)->S<T>;
```
```cpp
    //  example/core_lang_spec/explicit_ut.cpp 190

    S s = 1;      // Tがintであるため、explicit宣言されていないため、暗黙の型変換は許可
    // S t = 1.0; // Tが整数型でないため暗黙の型変換は禁止であるため、コンパイルエラー
    S t{1.0};     // Tが整数型でないが、明示的な初期化は問題ない

    ASSERT_EQ(s.value, 1);
```

テンプレートのパラメータの型による暗黙の型変換の可否をコントロールする例を以下に示す。

```cpp
    //  example/core_lang_spec/explicit_ut.cpp 203

    template <typename T>
    struct Optional {
    #if __cplusplus >= 202002L  // c++20
        explicit(std::is_same_v<T, std::nullptr_t>) Optional(const T& value)
            : has_value_(!std::is_same_v<T, std::nullptr_t>), value_(value) { }

    #else  // c++17
        // Tがnullptr_tではない場合に有効なコンストラクタ
        template <typename U = T, std::enable_if_t<!std::is_same_v<U, std::nullptr_t>>* = nullptr>
        Optional(const U& value) : has_value_(true), value_(value) { }

        // Tがnullptr_tの場合に有効なexplicitコンストラクタ
        template <typename U = T, std::enable_if_t<std::is_same_v<U, std::nullptr_t>>* = nullptr>
        explicit Optional(const U& value) : has_value_(false), value_(value) { }
    #endif

        explicit operator bool() const noexcept { return has_value_; }  // bool型への変換
                 operator T() const noexcept { return value_; }         // T型への変換

    private:
        bool has_value_;
        T    value_;
    };
    template <typename T>  // 推論ガイド
    Optional(T)->Optional<T>;
```
```cpp
    //  example/core_lang_spec/explicit_ut.cpp 235

    Optional a = 2;   // T == intであるため、暗黙の型変換を許可
    ASSERT_TRUE(a);   // has_value_がtrueであるため
    ASSERT_EQ(a, 2);  // T型への暗黙的変換をチェック

    // Optional n = nullptr; // T == std::nullptr_tのため暗黙の型変換抑止により、コンパイルエラー
    Optional n{nullptr};  // 通常の初期化
    ASSERT_FALSE(n);
```

こういった工夫により、コードの過度な柔軟性を適度に保つことができ、
可読性の向上につながる。

#### explicit type operator() <a id="SS_19_6_2_5"></a>
型変換演算子のオーバーロードの戻り値をさらに別の型に変換すると、
きわめてわかりづらいバグを生み出してしまうことがあるため、
この機能を使用すると型変換演算子のオーバーロードの型変換の抑止することができる。

```cpp
    //  example/core_lang_spec/explicit_ut.cpp 110

    struct A {
        explicit A(int a) : x{a} {}  // 暗黙の型変換の抑止
        operator bool() const noexcept { return x; }
        int x;
    };
```
```cpp
    //  example/core_lang_spec/explicit_ut.cpp 123

    auto a = A{2};

    ASSERT_TRUE(a);
    ASSERT_EQ(1, a);  // aをboolに変換するとtrue、trueをintに変換すると1

    int b = a + 1;  // aをboolに変換するとtrue、trueをintに変換すると1であるため、bは2
    ASSERT_EQ(b, 2);

```

以下に示すようにexplicitを使うことで、このような暗黙の型変換を抑止できる。

```cpp
    //  example/core_lang_spec/explicit_ut.cpp 137

    struct A {
        explicit A(int a) : x{a} {}  // 暗黙の型変換の抑止
        explicit operator bool() const noexcept { return x; }// 暗黙の型変換の抑止
        int x;
    };
```
```cpp
    //  example/core_lang_spec/explicit_ut.cpp 150

    auto a = A{2};

    // ASSERT_EQ(1, a);  // operator boolがexplicitであるため、コンパイルエラー
    // int b = a + 1;  // operator boolがexplicitであるため、コンパイルエラー
```

### ==演算子 <a id="SS_19_6_3"></a>
クラスの==演算子の実装方法には、
[メンバ==演算子](core_lang_spec.md#SS_19_6_3_1)、[非メンバ==演算子](core_lang_spec.md#SS_19_6_3_2)の2つの方法がある。

#### メンバ==演算子 <a id="SS_19_6_3_1"></a>
メンバ==演算子には、[非メンバ==演算子](core_lang_spec.md#SS_19_6_3_2)に比べ、下記のようなメリットがある。

* メンバ変数へのアクセスが容易であるため、より実装が単純になりやすい。
* メンバ変数へのアクセスが容易であるため、パフォーマンスが向上する。
* インライン化し易い。

```cpp
    //  example/core_lang_spec/comparison_operator_old_ut.cpp 12

    class Integer {
    public:
        Integer(int x) noexcept : x_{x} {}

        // operator==とoperator<だけを定義
        int get() const noexcept { return x_; }

        // メンバ関数の比較演算子
        bool operator==(const Integer& other) const noexcept { return x_ == other.x_; }
        bool operator<(const Integer& other) const noexcept { return x_ < other.x_; }

    private:
        int x_;
    };
```

すべてのメンバ変数に==演算子が定義されている場合、
C++20以降より、`=default`により==演算子を自動生成させることができるようになった。

```cpp
    //  example/core_lang_spec20/comparison_operator_ut.cpp 11

    class Integer {
    public:
        Integer(int x) noexcept : x_{x} {}

        bool operator==(const Integer& other) const noexcept = default;  // 自動生成

    private:
        int x_;
    };
```

#### 非メンバ==演算子 <a id="SS_19_6_3_2"></a>
非メンバ==演算子には、[メンバ==演算子](core_lang_spec.md#SS_19_6_3_1)に比べ、下記のようなメリットがある。

* クラスをよりコンパクトに記述できるが、その副作用として、
  アクセッサやfriend宣言が必要になることがある。

```cpp
    //  example/core_lang_spec/comparison_operator_old_ut.cpp 53

    class Integer {
    public:
        Integer(int x) noexcept : x_{x} {}

        // operator==とoperator<だけを定義
        int get() const noexcept { return x_; }

        // メンバ関数の比較演算子に見えるが、非メンバ関数
        friend bool operator==(const Integer& lhs, const Integer& rhs) noexcept { return lhs.x_ == rhs.x_; }

        friend bool operator<(const Integer& lhs, const Integer& rhs) noexcept { return lhs.x_ < rhs.x_; }

    private:
        int x_;
    };
```

* [暗黙の型変換](core_lang_spec.md#SS_19_6_2_2)を利用した以下に示すようなシンプルな記述ができる場合がある。

```cpp
    //  example/core_lang_spec/comparison_operator_old_ut.cpp 75

    auto a = Integer{5};

    ASSERT_TRUE(5 == a);  // 5がInteger{5}に型型変換される
```

すべてのメンバ変数に==演算子が定義されている場合、
C++20以降より、`=default`により==演算子を自動生成させることができるようになった。

```cpp
    //  example/core_lang_spec20/comparison_operator_ut.cpp 35

    class Integer {
    public:
        Integer(int x) noexcept : x_{x} {}

        friend bool operator==(Integer const& lhs, Integer const& rhs) noexcept;

    private:
        int x_;
    };

    bool operator==(Integer const& lhs, Integer const& rhs) noexcept = default;  // 自動生成
```

### 比較演算子 <a id="SS_19_6_4"></a>
比較演算子とは、[==演算子](--)の他に、!=、 <=、>、>= <、>を指す。
C++20から導入された[<=>演算子](core_lang_spec.md#SS_19_6_4_1)の定義により、すべてが定義される。

#### <=>演算子 <a id="SS_19_6_4_1"></a>
「[std::tuppleを使用した比較演算子の実装方法](stdlib_and_concepts.md#SS_20_10_2)」
で示した定型のコードはコンパイラが自動生成するのがC++規格のセオリーである。
このためC++20から導入されたのが<=>演算子`<=>`である。

```cpp
    //  example/core_lang_spec20/comparison_operator_ut.cpp 61

    struct Point {
        int x;
        int y;

        auto operator<=>(const Point& other) const noexcept = default;  // 三方比較演算子 (C++20)
        // 通常autoとするが、実際の戻り型はstd::strong_ordering
    };
```
```cpp
    //  example/core_lang_spec20/comparison_operator_ut.cpp 74

    auto p1 = Point{1, 2};
    auto p2 = Point{1, 2};
    auto p3 = Point{2, 3};

    ASSERT_EQ(p1, p2);  // p1 == p2
    ASSERT_NE(p1, p3);  // p1 != p3
    ASSERT_TRUE(p1 < p3);
    ASSERT_FALSE(p1 > p3);

    auto cmp_1_2 = p1 <=> p2;
    auto cmp_1_3 = p1 <=> p3;
    auto cmp_3_1 = p3 <=> p1;
    static_assert(std::is_same_v<std::strong_ordering, decltype(cmp_1_2)>);

    ASSERT_EQ(std::strong_ordering::equal, cmp_1_2);    // 等しい
    ASSERT_EQ(std::strong_ordering::less, cmp_1_3);     // <=>の左オペランドが小さい
    ASSERT_EQ(std::strong_ordering::greater, cmp_3_1);  // <=>の左オペランドが大きい

    // std::strong_orderingの値
    // ASSERT_EQ(static_cast<int32_t>(cmp_1_2), 0); キャストできないのでコンパイルエラー
    ASSERT_TRUE(cmp_1_2 == 0);
    ASSERT_TRUE(cmp_1_3 < 0);  // cmp_1_3は実質的には-1
    ASSERT_TRUE(cmp_3_1 > 0);  // cmp_3_1は実質的には1

```

定型の比較演算子では不十分である場合、<=>演算子を実装する必要が出てくる。
そのような場合に備えて、上記の自動生成コードの内容を敢えて実装して、以下に示す。

```cpp
    //  example/core_lang_spec20/comparison_operator_ut.cpp 105

    struct Point {
        int x;
        int y;

        std::strong_ordering operator<=>(const Point& other) const noexcept
        {
            return std::tie(x, y) <=> std::tie(other.x, other.y);
        }

        bool operator==(const Point& other) const noexcept { return std::tie(x, y) == std::tie(other.x, other.y); }
    };
```

#### 三方比較演算子 <a id="SS_19_6_4_2"></a>
三方比較演算子とは[<=>演算子](core_lang_spec.md#SS_19_6_4_1)を指す。

#### spaceship operator <a id="SS_19_6_4_3"></a>
spaceship operatorとは[<=>演算子](core_lang_spec.md#SS_19_6_4_1)を指す。
この名前は`<=>`が宇宙船に見えることに由来としている。


### リスト初期化 <a id="SS_19_6_5"></a>
リスト初期化とは、C++11で導入された`{}`を使ったオブジェクトの初期化構文を指す。
以下にコード例を示す。

```cpp
    //  example/core_lang_spec/uniform_initialization_ut.cpp 12

    struct X {
        X(int) {}
    };

    X x0(0);   // 通常従来のコンストラクタ呼び出し
    X x1 = 0;  // 暗黙の型変換を使用した従来のコンストラクタ呼び出し

    X x2{0};     // リスト初期化
    X x3 = {0};  // 暗黙の型変換を使用したリスト初期化

    struct Y {
        Y(int, double, std::string) {}
    };

    auto lamda = [](int, double, std::string) -> Y {
        return {1, 3.14, "hello"};  // 暗黙の型変換を使用したリスト初期化でのYの生成
    };
```

変数による一様初期化が縮小型変換を起こす場合や、
リテラルによる一様初期化がその値を変更する場合、コンパイルエラーとなるため、
この機能を積極的に使用することで、縮小型変換による初期化のバグを未然に防ぐことができる。

```cpp
    //  example/core_lang_spec/uniform_initialization_ut.cpp 34

    int i{0};  // リスト初期化

    bool b0 = 7;  // 縮小型変換のため、b0の値はtrue(通常は1)となる
    ASSERT_EQ(b0, 1);

    // bool b1{7};  // 縮小型変換のため、コンパイルエラー
    // bool b2{i};  // 縮小型変換のため、コンパイルエラー

    uint8_t u8_0 = 256;  // 縮小型変換のためu8_0は0となる
    ASSERT_EQ(u8_0, 0);

    // uint8_t u8_1{256};  // 縮小型変換のため、コンパイルエラー
    // uint8_t u8_2{i};    // 縮小型変換のため、コンパイルエラー

    uint8_t array0[3]{1, 2, 255};  // リスト初期化
    // uint8_t array1[3] = {1, 2, 256};  // 縮小型変換のため、コンパイルエラー
    // uint8_t array2[3]{1, 2, 256};     // 縮小型変換のため、コンパイルエラー
    // uint8_t array2[3]{1, 2, i};       // 縮小型変換のため、コンパイルエラー

    int i0 = 1.0;  // 縮小型変換のため、i0の値は1
    ASSERT_EQ(i0, 1);

    // int i1{1.0};  // 縮小型変換のため、コンパイルエラー

    double d{1};  // 縮小型変換は起こらないのでコンパイル可能
    // int i2{d};  // 縮小型変換のため、コンパイルエラー
```

### 一様初期化 <a id="SS_19_6_6"></a>
一様初期化(Uniform Initialization)は 、
[リスト初期化](core_lang_spec.md#SS_19_6_5)による初期化方法がC++における初期化を統一的に扱えるように設計された概念を指さす。

### 非静的なメンバ変数の初期化 <a id="SS_19_6_7"></a>
非静的なメンバ変数の初期化には下記の3つの方法がある。

* [NSDMI](core_lang_spec.md#SS_19_6_7_1)
* [初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)
* [コンストラクタ内での非静的なメンバ変数の初期値の代入](core_lang_spec.md#SS_19_6_7_3)

同一変数に対して、
「[NSDMI](core_lang_spec.md#SS_19_6_7_1)」と「[初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)」
が行われた場合、その変数に対するNSDMIは行われない。


#### NSDMI <a id="SS_19_6_7_1"></a>
NSDMIとは、non-static data member initializerの略語であり、
下記のような非静的なメンバ変数の初期化子を指す。

```cpp
    //  example/core_lang_spec/nsdmi.cpp 11

    class A {
    public:
        A() : a_{1}  // NSDMIではなく、非静的なメンバ初期化子による初期化
        {
        }

    private:
        int32_t     a_;
        int32_t     b_ = 0;        // NSDMI
        std::string str_{"init"};  // NSDMI
    };
```

#### 初期化子リストでの初期化 <a id="SS_19_6_7_2"></a>
「非静的メンバ変数をコンストラクタの本体よりも前に初期化する」言語機能である。
メンバ変数は宣言された順序で初期化されるため、
初期化子リストでの順序は、実際の初期化の順序とは関係がない。

この機能を使うことで、メンバ変数の初期化処理が簡素に記述できる。
constメンバ変数は、初期化子リストでの初期化か[NSDMI](core_lang_spec.md#SS_19_6_7_1)でしか初期化できない。

```cpp
    //  example/core_lang_spec/nsdmi.cpp 27

    class A {
    public:
        A(int a, int b) : v_{a, b, 3}, a_{a}  // 非静的なメンバ初期化子による初期化
        //                 ^^^^^^^^^^^^^ メンバ変数の初期化は
        //                                  - 宣言順に行われる。
        //                                  - 初期化リストの順番と、初期化の順番には関係がない。
        {
        }

    private:
        int              a_;
        std::vector<int> v_;
    };
```

#### コンストラクタ内での非静的なメンバ変数の初期値の代入 <a id="SS_19_6_7_3"></a>
この方法は単なる代入でありメンバ変数の初期化ではない。

[NSDMI](core_lang_spec.md#SS_19_6_7_1)、
[初期化子リストでの初期化](core_lang_spec.md#SS_19_6_7_2)で初期化できない変数を未初期化でない状態にするための唯一の方法である。

```cpp
    //  example/core_lang_spec/nsdmi.cpp 45

    class A {
    public:
        A(int a, int b)
        {
            a_ = b;                     // 非静的なメンバのコンストラクタでの代入
            v_ = std::vector{a, b, 3};  // 非静的なメンバのコンストラクタでの代入
        }

    private:
        int              a_;
        std::vector<int> v_;
    };
```

### オブジェクトのライフタイム <a id="SS_19_6_8"></a>
オブジェクトは、以下のような種類のライフタイムを持つ。

* 静的に生成されたオブジェクトのライフタイム
* thread_localに生成されたオブジェクトのライフタイム
* newで生成されたオブジェクトのライフタイム
* スタック上に生成されたオブジェクトのライフタイム
* prvalue(「[rvalue](core_lang_spec.md#SS_19_7_1_2)」参照)のライフタイム

なお、リファレンスの初期化をrvalueで行った場合、
そのrvalueはリファレンスがスコープを抜けるまで存続し続ける。

rvalueをバインドするリファレンスが存在しない状態で、
そのrvalueがメンバ変数へのリファレンスを返す関数を呼び出し、
そのリファレンスをバインドするリファレンス変数を初期化した場合、
リファレンスが指すオブジェクトはすでにライフタイムを終了している。
このような状態のリファレンスを[danglingリファレンス](cpp_idioms.md#SS_21_11_2)と呼ぶ。
同様に、このような状態のポインタを[danglingポインタ](cpp_idioms.md#SS_21_11_3)と呼ぶ。

### プレースメントnew <a id="SS_19_6_9"></a>
プレースメントnewは、既に確保済みの生ストレージ上で、
オブジェクトを生成するための `new(raw_storage) T(args...)`のような構文である。
通常のnew演算子が「メモリ確保＋初期化」を同時に行うのに対し、プレースメントnewは「初期化のみ」を担当する。
これにより、メモリ確保の責務を呼び出し側に委ねることができ、
アロケーションコストの削減やメモリプールとの統合が可能となる。
また、リアルタイム処理や組込みソフトウェアなど、ヒープからの動的割り当てを避けたい場面でも有用である。

```cpp
    //  example/core_lang_spec/placement_new_ut.cpp 10

    class X {
    public:
        explicit X(int v) : str_{std::to_string(v)} {}
        std::string const& get_str() const noexcept { return str_; }

        ~X() {}

    private:
        std::string str_;
    };
```

上記クラスをプレースメントnewを使用して生成するコード例を以下に示す。

```cpp
    //  example/core_lang_spec/placement_new_ut.cpp 26

    alignas(X) uint8_t memory_[sizeof(X)];
    // alignas(X)はXのアライメント要件(通常4や8バイト境界)に合わせる
    // これがないと、memory_が不適切な境界(例:奇数アドレス)に配置され、
    // 一部のCPUアーキテクチャでクラッシュやパフォーマンス低下を引き起こす

    X* x = new (memory_) X{42};  // X型オブジェクトをmemory_上に生成

    ASSERT_EQ("42", x->get_str());  // 正しく生成されたかどうかの確認

    // ...
    // ... ここでエクセプションが発生して、
    // ... 以下のコードが実行できないとデストラクタが呼ばれないためメモリリークする可能性がある

    x->~X();  // プレースメントしたオブジェクトの解放にはdeleteを使ってはならないため、
              // このように直接デストラクタを呼び出す必要がある
```

このコードからわかる通り、プレースメントnewで生成したオブジェクトは手動でデストラクタを呼び出す必要があるため、
例外が発生した場合にリソースリークのリスクがある。
下記のようにstd::unique_ptrにカスタムデリータを指定することで、この問題を解決できる。

```cpp
    //  example/core_lang_spec/placement_new_ut.cpp 48

    alignas(X) uint8_t memory_[sizeof(X)];

    auto deleter = [](X* p) {  // カスタムデリータの定義
        if (p) {
            p->~X();  // デストラクタのみ呼び出し
        }
    };

    std::unique_ptr<X, decltype(deleter)> x{new (memory_) X{42}, deleter};

    ASSERT_EQ("42", x->get_str());
    // xがスコープアウトするタイミングでカスタムデリータdeleterが呼ばれるため、~X()の呼び出し漏れが回避できる
```

### new (std::nothrow) <a id="SS_19_6_10"></a>
`new (std::nothrow)`は、メモリ確保失敗時に例外を投げずnullptrを返すnewの形式である。
通常のnewはメモリ確保に失敗するとstd::bad_alloc例外を投げるが、
`new (std::nothrow)`はstd::nothrow_t型の引数を取ることで、失敗時にnullptrを返す動作に変更される。
この形式は例外を使わない環境(組み込みシステムなど)や、明示的なnullチェックによるエラー処理が望ましい場合に使用される。
解放方法は通常のnewと同じで、単一オブジェクトの場合はdelete、配列の場合はdelete[]を使用する。

## 値カテゴリとリファレンス <a id="SS_19_7"></a>
ここでは、expression(式)の値カテゴリや、それに付随した機能についての解説を行う。

### expression <a id="SS_19_7_1"></a>

[expression](https://ja.cppreference.com/w/cpp/language/expressions)(式)とは、
「演算子とそのオペランドの並び」である(オペランドのみの記述も式である)。
演算子とは以下のようなものである。

* 四則演算、代入(a = b、a += b ...)、インクリメント、比較、論理式
* 明示的キャストや型変換
* メンバアクセス(a.b、a->b、a[x]、 \*a、&a ...)
* 関数呼び出し演算子(f(...))、sizeof、decltype等


expressionは、

* [lvalue](core_lang_spec.md#SS_19_7_1_1)
* [rvalue](core_lang_spec.md#SS_19_7_1_2)
* [xvalue](core_lang_spec.md#SS_19_7_1_3)
* [glvalue](core_lang_spec.md#SS_19_7_1_5)
* [prvalue](core_lang_spec.md#SS_19_7_1_4)

に分類される。
<!-- pu:essential/plant_uml/rvalue.pu--><p><img src="data:image/png;base64,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" /></p>


expressionは、[lvalue](core_lang_spec.md#SS_19_7_1_1)か[rvalue](core_lang_spec.md#SS_19_7_1_2)である。


#### lvalue <a id="SS_19_7_1_1"></a>
lvalueとは、

* 名前を持つオブジェクト(識別子で参照可能)や関数を指す式
* 代入式の左辺になり得る式であるため、左辺値と呼ばれることがある。
* constなlvalueは代入式の左辺にはなり得ないが、lvalueである。
* [rvalue](core_lang_spec.md#SS_19_7_1_2)でない[expression](core_lang_spec.md#SS_19_7_1)がlvalueである。

`T const&`は代入式の左辺になりは得ないがlvalueである。[rvalueリファレンス](core_lang_spec.md#SS_19_8_2)もlvalueである。

#### rvalue <a id="SS_19_7_1_2"></a>
rvalueとは、

* テンポラリな値を表す式(代入式の右辺値として使われることが多い)
* [xvalue](core_lang_spec.md#SS_19_7_1_3)か[prvalue](core_lang_spec.md#SS_19_7_1_4)である。
* [lvalue](core_lang_spec.md#SS_19_7_1_1)でない[expression](core_lang_spec.md#SS_19_7_1)がrvalueである。

[rvalueリファレンス](core_lang_spec.md#SS_19_8_2)(`T&&`型の変数)はlvalueである。
一方、その初期化に使われる式(例えばstd::move(x))は[xvalue](core_lang_spec.md#SS_19_7_1_3)である。


#### xvalue <a id="SS_19_7_1_3"></a>
xvalueとは以下のようなものである。

* 戻り値の型がT&&(Tは任意の型)である関数の呼び出し式(std::move(x))
* オブジェクトへのT&&へのキャスト式(static_cast<char&&>(x))
* aを配列のxvalueとした場合のa[N]や、cをクラス型のrvalueとした場合のc.m(mはaの非staticメンバ)等

#### prvalue <a id="SS_19_7_1_4"></a>
prvalueとは、オブジェクトやビットフィールドを初期化する、
もしくはオペランドの値を計算する式であり、以下のようなものである。

* 文字列リテラルを除くリテラル
* 戻り値の型が非リファレンスである関数呼び出し式、
  または前置++と前置--を除くオーバーロードされた演算子式(`path.string()`、`str1 + str2`、`it++` ...)
* 組み込み型インスタンスaの`a++`、`a--`(`++a`や`--a`はlvalue)
* 組み込み型インスタンスa、bに対する
  `a + b`、 `a % b`、 `a & b`、 `a && b`、 `a || b`、 `!a`、 `a < b`、 `a == b`等
* prvalue(もしくはrvalue)は、
    * アドレス演算子(&)のオペランドになれない。
    * 非constな[lvalueリファレンス](core_lang_spec.md#SS_19_8_1)ではバインドできないが、
      constな[lvalueリファレンス](core_lang_spec.md#SS_19_8_1)や[rvalueリファレンス](core_lang_spec.md#SS_19_8_2)でバインドできる。
  

つまり、prvalueとはいわゆるテンポラリオブジェクトのことである(下記の`std::string{}`で作られるようなオブジェクト)。
多くの場合、prvalueはテンポラリオブジェクトを生成するが、
C++17以降は[RVO(Return Value Optimization)](core_lang_spec.md#SS_19_15_1)により、
テンポラリオブジェクトを生成せず、直接、初期化に使われる場合もある。  
また、正確にはprvalueと呼ぶべき場面でも単にrvalueと呼ばれることがある。
このドキュメントでも、そうなっていることもある。

```cpp
    //  example/core_lang_spec/rvalue_lvalue_ut.cpp 10
    // str0を初期化するためにstd::string{}により生成されるオブジェクトはprvalue、 str0はlvalue
    //   ↓lvalue
    auto str0 = std::string{};  // この式の左辺はテンポラリオブジェクト(つまりprvalue)

    /*
    auto* str0_ptr = &std::string{};  // prvalueのアドレスの取得はできない
    ↑は、メッセージは error: taking address of rvalue でコンパイルエラー */

    /*
    std::string& str1_ref = std::string{};  // prvalueを非constなlvalueリファレンスではバインドできない
    ↑は、コンパイルエラーで、エラーメッセージは error: taking address of rvalue */

    std::string const& str2_ref = std::string{};  // prvalueはconstなlvalueリファレンスでバインドできる
    // ↓のようにすればアドレスを取得できるが、このようなことはすべきではない。
    std::string const* str2_ptr = &str2_ref;  // str_ptrはprvalueのアドレスを指しているが、、、

    auto&& str3_ref = std::string{};  // prvalueはprvalueリファレンスでバインドできる
    // ↓のようにすればアドレスを取得できるが、このようなことはすべきではない。
    std::string* str3_ptr = &str3_ref;  // str_ptrはprvalueのアドレスを指しているが、、、
```

#### glvalue <a id="SS_19_7_1_5"></a>
glvalueは、

* [lvalue](core_lang_spec.md#SS_19_7_1_1)か[xvalue](core_lang_spec.md#SS_19_7_1_3)である。
* "generalized lvalue"の略称

オブジェクトや関数を参照する式を総称してglvalueと呼ぶ。
これにより、式が「場所を指す」か「一時的な値を表す」かを大きく分類できる。


### decltypeとexpression <a id="SS_19_7_2"></a>
エッセンシャルタイプがTであるlvalue、xvalue、prvalueに対して
(例えば、std::string const&のエッセンシャルタイプはstd::stringである)、
decltypeの算出結果は下表のようになる。

|decltype           |算出された型|
|:------------------|:-----------|
|decltype(lvalue)   |T           |
|decltype((lvalue)) |T&          |
|decltype(xvalue)   |T&&         |
|decltype((xvalue)) |T&&         |
|decltype(prvalue)  |T           |
|decltype((prvalue))|T           |

この表の結果を使用した下記の関数型マクロ群により式を分類できる。
定義から明らかな通り、これらは
[テンプレートメタプログラミング](https://ja.wikipedia.org/wiki/%E3%83%86%E3%83%B3%E3%83%97%E3%83%AC%E3%83%BC%E3%83%88%E3%83%A1%E3%82%BF%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0)
に有効に活用できる。

```cpp
    //  example/core_lang_spec/decltype_expression_ut.cpp 7

    #define IS_LVALUE(EXPR_) std::is_lvalue_reference_v<decltype((EXPR_))>
    #define IS_XVALUE(EXPR_) std::is_rvalue_reference_v<decltype((EXPR_))>
    #define IS_PRVALUE(EXPR_) !std::is_reference_v<decltype((EXPR_))>
    #define IS_RVALUE(EXPR_) (IS_PRVALUE(EXPR_) || IS_XVALUE(EXPR_))

    auto str = std::string{};

    static_assert(IS_LVALUE(str), "EXPR_ must be lvalue");
    static_assert(!IS_RVALUE(str), "EXPR_ must NOT be rvalue");

    static_assert(IS_XVALUE(std::move(str)), "EXPR_ must be xvalue");
    static_assert(!IS_PRVALUE(std::move(str)), "EXPR_ must NOT be prvalue");

    static_assert(IS_PRVALUE(std::string{}), "EXPR_ must be prvalue");
    static_assert(IS_RVALUE(std::string{}), "EXPR_ must be rvalue");
    static_assert(!IS_LVALUE(std::string{}), "EXPR_ must NOT be lvalue");
```

## リファレンス <a id="SS_19_8"></a>

リファレンス(参照)とは、以下のいずれか、もしくはすべてを指すが、
単にリファレンスと呼ぶ場合、lvalueリファレンスを指すことが多い。

* [lvalueリファレンス](core_lang_spec.md#SS_19_8_1)
* [rvalueリファレンス](core_lang_spec.md#SS_19_8_2)
* [forwardingリファレンス](core_lang_spec.md#SS_19_8_3)


これらの概念と関わり強い、[リファレンスcollapsing](core_lang_spec.md#SS_19_8_6)についても併せて解説を行う。

### lvalueリファレンス <a id="SS_19_8_1"></a>
lvalueリファレンスとは、

* C++98(もしくは03)から導入されたシンタックスであり、任意の型Tに対して`T&`という形式で宣言される。
* 既存のオブジェクトに対する別名(エイリアス)であり、宣言時に必ず初期化が必要で、
  一度初期化後は別のオブジェクトを参照することはできない。
* [rvalueリファレンス](core_lang_spec.md#SS_19_8_2)導入前のC++では、すべてのリファレンスはlvalueリファレンスであったため、
  lvalueリファレンスを単にリファレンスと呼んでいた。
* オブジェクトaのエイリアスとして、
   リファレンスa_refが宣言されることを「a_refはaをバインドする」という。
* 以下のコード例で示すように、
    * 非const lvalueリファレンスは[rvalue](core_lang_spec.md#SS_19_7_1_2)をバインドできないが、
    * const lvalueリファレンスは[rvalue](core_lang_spec.md#SS_19_7_1_2)をバインドできる。

```cpp
    //  example/core_lang_spec/rvalue_lvalue_ut.cpp 40

    int  a     = 0;
    int& a_ref = a;  // a_refはaのリファレンス
                     // a_refはaをバインドする

    ASSERT_EQ(&a, &a_ref);  // リファレンスは別名に過ぎないため、このテストが成立

    int b = 1;
    a_ref = b;  // 一見、a_refの再初期化に見えるが、実際は値の代入になるため、以下のテストが成立
    ASSERT_EQ(a, b);  // リファレンスは別名に過ぎないため、このテストが成立

    /*
    int& t_ref = int{99};  非const lvalueリファレンスはrvalueをバインドできない */
    int const& t_ref = int{99};  // 上記とは異なり、const lvalueリファレンスはrvalueをバインドできる
    ASSERT_EQ(t_ref, 99);
```

このようなリファレンスのバインドの可否はオーバーロードにも影響を与える。


```cpp
    //  example/core_lang_spec/rvalue_lvalue_ut.cpp 60

    int f(int& )        { return 1; }   // f-1
    int f(int const & ) { return 2; }   // f-2
```

```cpp
    //  example/core_lang_spec/rvalue_lvalue_ut.cpp 69

    int       a = 0;
    int const b = 0;

    ASSERT_EQ(1, f(a));  // f(a)は、f-2も呼び出せるが、デフォルトでは、f-1が呼ばれる
    ASSERT_EQ(2, f(static_cast<int const&>(a)));  // aをconstにキャストして、強制的にf-2の呼び出し
    ASSERT_EQ(2, f(b));                           // constオブジェクトのバインド
    ASSERT_EQ(2, f(int{}));                       // rvalueのバインド
```

### rvalueリファレンス <a id="SS_19_8_2"></a>
rvalueリファレンスは、

* C++11で導入されたシンタックスであり、任意の型Tに対して、`T&&`で宣言される。
* 「テンポラリオブジェクト([rvalue](core_lang_spec.md#SS_19_7_1_2))」をバインドできるリファレンス。
* C++11の[moveセマンティクス](cpp_idioms.md#SS_21_5_3)と[perfect forwarding](core_lang_spec.md#SS_19_8_5)を実現するために導入された。
* **注意1** 型が`T&&`である変数の値カテゴリは[lvalue](core_lang_spec.md#SS_19_7_1_1)である。
* **注意2** 型が`T&&`である変数は、`T&`でバインドできる。

```cpp
    //  example/core_lang_spec/rvalue_lvalue_ut.cpp 87

    int        a      = 0;
    int const& a_ref0 = a;        // const lvalueリファレンスはlvalueをバインドできる
    int const& a_ref1 = int{99};  // const lvalueリファレンスはrvalueもバインドできる
    int&& a_ref2 = int{99};       // rvalueリファレンスはテンポラリオブジェクトをバインドできる
    int& a_ref3 = a_ref2;         // rvalueリファレンス型の変数は、lvalueリファレンスでバインドできる
    /*
    int&& a_ref4 = a_ref2;       以下のメッセージでコンパイルエラー
                                 cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’ 
                                 rvalueリファレンス型の変数(lvalue)は、rvalueリファレンスでバインドできない */
```

このようなリファレンスのバインドの可否はオーバーロードにも影響を与える。


```cpp
    //  example/core_lang_spec/rvalue_lvalue_ut.cpp 118

    int f(int&)       { return 1; } // f-1
    int f(int const&) { return 2; } // f-2
    int f(int&&)      { return 3; } // f-3
```

```cpp
    //  example/core_lang_spec/rvalue_lvalue_ut.cpp 129

    int       a = 0;
    int const b = 0;

    ASSERT_EQ(1, f(a));                           // f-1の呼び出し
    ASSERT_EQ(2, f(b));                           // f-2の呼び出し、constなlvalueリファレンスのバインド
    ASSERT_EQ(3, f(int{}));                       // f-3の呼び出し(f-3が無ければ、f-2を呼ばれる)
    ASSERT_EQ(2, f(static_cast<int const&>(a)));  // aをconstリファレンスにキャストして、強制的にf-2の呼び出し
    ASSERT_EQ(3, f(static_cast<int&&>(a)));       // aをrvalueリファレンスにキャストして、強制的にf-3の呼び出し
    ASSERT_EQ(3, f(std::move(a)));                // f-3の呼び出し

    int&& ref_ref = int{};

    ASSERT_EQ(1, f(ref_ref));                     // f-3ではなくf-1を呼び出す。従って間違いなくこのテストはパスする
```

上記コードの最後の部分の抜粋である以下のコードについては、少々解説が必要だろう。

```cpp
    //  example/core_lang_spec/rvalue_lvalue_ut.cpp 141

    int&& ref_ref = int{};

    ASSERT_EQ(1, f(ref_ref));                     // f-3ではなくf-1を呼び出す。従って間違いなくこのテストはパスする
```

ref_refの型は`int &&`であるが、ref_refの値カテゴリは[rvalue](core_lang_spec.md#SS_19_7_1_2)ではなく、[lvalue](core_lang_spec.md#SS_19_7_1_1)である。
そのため、`f(ref_ref)`はlvalueリファレンスを引数とするf-1が選択される。

rvalueリファレンス型の仮引数（`T&&`）を持つ関数は、ムーブコンストラクタやムーブ代入演算子など頻繁に使用される。
しかし、関数内では仮引数は名前を持つため、常にlvalueとして扱われる。
この動作を理解することは、
[moveセマンティクス](cpp_idioms.md#SS_21_5_3)や[perfect forwarding](core_lang_spec.md#SS_19_8_5)を正しく実装/使用するために極めて重要である。

```cpp
    //  example/core_lang_spec/rvalue_lvalue_ut.cpp 150

    int g(int&& a) { return f(a); }            // g-1    仮引数aはlvalue -> f-1が呼ばれる
    int g(int& a) { return f(std::move(a)); }  // g-2    std::moveでrvalueに変換 -> f-3が呼ばれる
```
```cpp
    //  example/core_lang_spec/rvalue_lvalue_ut.cpp 158

    ASSERT_EQ(1, g(int{}));  // int{}はrvalue -> g-1が呼ばれ、内部でf-1が呼ばれる

    int a{};
    ASSERT_EQ(3, g(a));  // aはlvalue -> g-2が呼ばれ、内部でf-3が呼ばれる
```
---

C++11でrvalueの概念の整理やrvalueリファレンス、
std::move()の導入が行われた目的はプログラム実行速度の向上である。
以下のパターンの代入式の処理がどのように違うのかを見ることでrvalueやstd::moveの効果について説明する。

* [lvalueからの代入](core_lang_spec.md#SS_19_8_2_1)
* [rvalueからの代入](core_lang_spec.md#SS_19_8_2_2)
* [std::move(lvalue)からの代入](core_lang_spec.md#SS_19_8_2_3)



#### lvalueからの代入 <a id="SS_19_8_2_1"></a>
下記コードにより「[lvalue](core_lang_spec.md#SS_19_7_1_1)からの代入」を説明する。

```.cpp
    //  example/core_lang_spec/rvalue_move_ut.cpp 10

    auto str0 = std::string{};        // 行１   str0はlvalue
    auto str1 = std::string{"hehe"};  // 行２   str1もlvalue
    str0      = str1;                 // 行３   lvalueからの代入
```

* 行１、２  
  str0、str1がそれぞれ初期化される
  ("hehe"を保持するバッファが生成され、それをstr1オブジェクトが所有する)。

* 行３  
  str1が所有している文字列バッファと同じ内容を持つ新しいバッファが確保され、
  その内容がコピーされstr0がそれを所有する。従って、"hehe"を保持するバッファが2つできる。この代入をcopy代入と呼ぶ。

<!-- pu:essential/plant_uml/rvalue_from_lvalue.pu--><p><img src="data:image/png;base64,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" /></p>


#### rvalueからの代入 <a id="SS_19_8_2_2"></a>
下記コードにより「[rvalue](core_lang_spec.md#SS_19_7_1_2)からの代入」を説明する。

```.cpp
    //  example/core_lang_spec/rvalue_move_ut.cpp 23

    auto str0 = std::string{};        // 行１   str0はlvalue
    str0      = std::string{"hehe"};  // 行２   rvalueからの代入
                                      // 行３   行２で生成されたテンポラリオブジェクト(rvalue)は解放
```

* 行１  
  str0が「std::string()により作られたテンポラリオブジェクト」により初期化される。

* 行２の右辺  
 「"hehe"を保持するをstd::stringテンポラリオブジェクトが生成される。

* 行２の左辺  
  この例の場合、std::stringがmoveコンストラクタ／move代入演算子を提供しているため、
  下記図のようなバッファの所有が移し替えられるだけである(この代入をmove代入と呼ぶ)。

* 行３  
  テンポラリオブジェクトが解体されるが、heheバッファはstr0の所有になったためdeleteする必要がなく、
  実際には何もしない。move代入によって、文字列バッファの生成と破棄の回数がそれぞれ1回少なくなったため、
  実行速度は向上する(通常、new/deleteの処理コストは高い)。

<!-- pu:essential/plant_uml/rvalue_from_rvalue.pu--><p><img src="data:image/png;base64,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kMriGZOrVq3q27fvwoULP/zwQ/1crffee2/ChAkFBQXf//73586dG35qy5Ytp59++jXXXNO+ffsZM2b06tVr1KhRR44ckUtdffXVP/jBD0477bSrw8jbkle99NJL7777bk1NzR133DFv3jzZX0oGFxYWhl8ZOEXEJJDK4hmTlZWVb7/9tqTdnDlzBoYZMWKEVnndddeFx+Thw4fPOussydeDBw9mZmZK2pWVlXXr1k22j05Bbm5u5I8llN3kgw8+uHHjRumPHDly5cqV0rnkkkuKioq0SuBUEJNAKotnTH766aeyC/zlL38pIbe11i233HLjjTdqX0F85513unTpsm/fPjXy1ltvderUSfaOGzZsyMnJcQZvuummiRMnSueTTz5p3rz5v//7v48JEwqF8vLyfvSjHznxKW/X2cIOGDCgpKREXRk4dcQkkMriGZOy+ZO946RJk9SIZFj44dHazDvzzDNXr14dPvj666+fc845R2vrb731VmdwyJAhDz30UHV19f/7f/9P4nbp0qU/+9nPJCyX1pKdq9RMnz5dXrJq1SoVrrIHLS8vP3ZhIA6ISSCVxTMmxbx58+qJydLS0j59+ixZskT6sndU4wcOHGjfvv2aNWt69+6dn58vpx555JGWLVvu3r37iSee+Ld/+7fDhw87V5NcVK86WhuTd999d3Z29vr16++6665BgwadffbZ4QXAqSMmgVSWwJjcsGHD6NGjJb3U2WnTpqWnp7dq1app06Y/+MEP1Lh44YUXsrKyhg0btmnTpjPOOKNr167ON7tKZC5YsGBerR//+MdS4PRfeuklub7Eavfu3a+++uopU6aMHz/+qquukrcuyRp+ZeAUEZNAKotzTC5btkx9b86oUaMkC2Wfd3xJAw4dOvTaa68520fHrFmzJkX4y1/+smXLlqVLl37++eePP/74nXfeecsttzhftpT3Iex6wKkiJoFUFueYBOxDTAKpjJgEGkBMAqmMmAQaQEwCqYyYBBpATAKpjJgEGkBMAqmMmAQaQEwCqYyYBBpATAKpjJgEGkBMAqmMmAQaQEwCqYyYBBpATAKpzKqYzMrKCsBeMr/6lCdFwKOYbN+4kf4hgEW8ep4RK6tiUp48dRewj8xvKBSqqKiorKysrq6uqanRn4DECHgUk/J2y7/Xk2Zr8+p5RqzcJUj19BJzEJN2k/kNBoOl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" /></p>

#### std::move(lvalue)からの代入 <a id="SS_19_8_2_3"></a>
下記コードにより「std::move(lvalue)からの代入」を説明する。

```.cpp
    //  example/core_lang_spec/rvalue_move_ut.cpp 36

    auto str0 = std::string{};        // 行１   str0はlvalue
    auto str1 = std::string{"hehe"};  // 行２   str1もlvalue
    str0      = std::move(str1);      // 行３   str1への代入以外のアクセスは未規定である。
```

* 行１  
  「[lvalueからの代入](core_lang_spec.md#SS_19_8_2_1)」の行１と同じである。

* 行２  
  「[lvalueからの代入](core_lang_spec.md#SS_19_8_2_1)」の行２と同じである。

* 行３  
  std::moveは単にrvalueリファレンスへのキャストを行うだけであり、ランタイム時の処理コストは発生しない。
  この例の場合、std::stringがmoveコンストラクタ／move代入演算子を提供しているため、
  下記図のようなバッファの所有が移し替えられるだけである(この代入もmove代入と呼ぶ)。
  この動作は「[rvalueからの代入](core_lang_spec.md#SS_19_8_2_2)の行２の左辺」と同じであり、同様に速度が向上するが、その副作用として、
  str1への代入以外のアクセスは[未規定動作](core_lang_spec.md#SS_19_14_4)であるため、避けるべきである
  (多くの実装では、str1.size() == 0となることが多いがこの動作は約束されない)。

<!-- pu:essential/plant_uml/rvalue_from_move.pu--><p><img src="data:image/png;base64,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" /></p>


### forwardingリファレンス <a id="SS_19_8_3"></a>
関数テンプレートの型パラメータTに対して`T&&`として宣言された仮引数、
または型推論を伴うauto&&として宣言された変数を、forwardingリファレンスと呼ぶ
(この概念はC++14から存在し、慣用的にユニバーサルリファレンスと呼ばれていたが、
C++17から正式にforwardingリファレンスと命名された)。
forwardingリファレンスは一見rvalueリファレンスのように見えるが、
下記に示す通り、lvalueにもrvalueにもバインドできる
([リファレンスcollapsing](core_lang_spec.md#SS_19_8_6)により、このようなバインドが可能になる)。

```cpp
    //  example/core_lang_spec/universal_ref_ut.cpp 8

    template <typename T>
    void f(T&& t) noexcept  // tはforwardingリファレンス
    {
        // ...
    }

    template <typename T>
    void g(std::vector<T>&& t) noexcept  // tはrvalueリファレンス
    {
        // ...
    }
```
```cpp
    //  example/core_lang_spec/universal_ref_ut.cpp 29

    auto       vec  = std::vector<std::string>{"lvalue"};   // vecはlvalue
    auto const cvec = std::vector<std::string>{"clvalue"};  // cvecはconstなlvalue

    f(vec);                                 // 引数はlvalue
    f(cvec);                                // 引数はconstなlvalue
    f(std::vector<std::string>{"rvalue"});  // 引数はrvalue

    // g(vec);  // 引数がlvalueなのでコンパイルエラー
    // g(cvec); // 引数がconst lvalueなのでコンパイルエラー
    g(std::vector<std::string>{"rvalue"});  // 引数はrvalue
```

下記のコードは[ジェネリックラムダ](core_lang_spec.md#SS_19_11_6)の引数をforwardingリファレンスにした例である。

```cpp
    //  example/core_lang_spec/universal_ref_ut.cpp 47

    // sはforwardingリファレンス
    auto value_type = [](auto&& s) noexcept {
        if (std::is_same_v<std::string&, decltype(s)>) {
            return 0;
        }
        if (std::is_same_v<std::string const&, decltype(s)>) {
            return 1;
        }
        if (std::is_same_v<std::string&&, decltype(s)>) {
            return 2;
        }
        return 3;
    };

    auto       str  = std::string{"lvalue"};
    auto const cstr = std::string{"const lvalue"};

    ASSERT_EQ(0, value_type(str));
    ASSERT_EQ(1, value_type(cstr));
    ASSERT_EQ(2, value_type(std::string{"rvalue"}));
```

通常、forwardingリファレンスはstd::forwardと組み合わせて使用される。


### ユニバーサルリファレンス <a id="SS_19_8_4"></a>
ユニバーサルリファレンスとは、「[forwardingリファレンス](core_lang_spec.md#SS_19_8_3)」の通称、もしくは旧称である。

### perfect forwarding <a id="SS_19_8_5"></a>
perfect forwarding(完全転送)とは、引数の[rvalue](core_lang_spec.md#SS_19_7_1_2)性や
[lvalue](core_lang_spec.md#SS_19_7_1_1)性を損失することなく、
その引数を別の関数に転送する技術のことを指す。
通常は、[forwardingリファレンス](core_lang_spec.md#SS_19_8_3)である関数の仮引数をstd::forwardを用いて、
他の関数に渡すことで実現される。

perfect forwardingの使用例を以下に示す。

```cpp
    //  example/core_lang_spec/perfect_forwarding_ut.cpp 7

    class Widget {
    public:
        explicit Widget(std::string const& name) : name_{name} {}        // lvalueによるコンストラクタ
        explicit Widget(std::string&& name) : name_{std::move(name)} {}  // rvalueによるコンストラクタ
        std::string const& GetName() const { return name_; }

    private:
        std::string name_;  // コンストラクタの引数をcopy/move構築
    };

    template <typename T>
    Widget make_Widget(T&& str)
    {                                         // strはforwardingリファレンス
        return Widget(std::forward<T>(str));  // perfect forwarding
    }
```
```cpp
    //  example/core_lang_spec/perfect_forwarding_ut.cpp 28

    std::string       str{"lvalue ref"};
    std::string const cstr{"lvalue const ref"};

    Widget w0 = make_Widget(str);  // make_Widget -> Widget(std::string const&)
    ASSERT_EQ(w0.GetName(), str);

    Widget w1 = make_Widget(cstr);  // make_Widget -> Widget(std::string const&)
    ASSERT_EQ(w1.GetName(), cstr);

    Widget w2 = make_Widget(std::string{"rvalue ref"});  // make_Widget -> Widget(std::string &&)
    ASSERT_EQ(w2.GetName(), "rvalue ref");

    Widget w3 = make_Widget(std::move(str));  // make_Widget -> Widget(std::string &&)
    ASSERT_EQ(w3.GetName(), "lvalue ref");    // strはムーブされたのでアクセス不可
```

### リファレンスcollapsing <a id="SS_19_8_6"></a>
Tを任意の型とし、TRを下記のように宣言した場合、

```cpp
    using TR = T&;
```

下記のようなコードは、C++03ではコンパイルエラーとなったが、
C++11からはエラーとならず、TRRはT&となる。

```cpp
    using TRR = TR&;
```

2つの&を1つに折り畳む、このような機能をリファレンスcollapsingと呼ぶ。

下記はTをintとした場合のリファレンスcollapsingの動きを示している。

```cpp
    //  example/core_lang_spec/ref_collapsing_ut.cpp 7

    int i;

    using IR  = int&;
    using IRR = IR&;  // IRRはint& &となり、int&に変換される

    IR  ir  = i;
    IRR irr = ir;

    static_assert(std::is_same_v<int&, decltype(ir)>);   // lvalueリファレンス
    static_assert(std::is_same_v<int&, decltype(irr)>);  // lvalueリファレンス
```

リファレンスcollapsingは、型エイリアス、型であるテンプレートパラメータ、decltypeに対して行われる。
詳細な変換則は、下記のようになる。

```
    T& &   -> T&
    T& &&  -> T&
    T&& &  -> T&
    T&& && -> T&&
```

下記のようなクラステンプレートを定義した場合、

```cpp
    //  example/core_lang_spec/ref_collapsing_ut.cpp 26

    template <typename T>
    struct Ref {
        T&  t;
        T&& u;
    };
```

下記のコードにより、テンプレートパラメータに対するこの変換則を確かめることができる。

```cpp
    //  example/core_lang_spec/ref_collapsing_ut.cpp 38

    static_assert(std::is_same_v<int&, decltype(Ref<int>::t)>);    // lvalueリファレンス
    static_assert(std::is_same_v<int&&, decltype(Ref<int>::u)>);   // rvalueリファレンス

    static_assert(std::is_same_v<int&, decltype(Ref<int&>::t)>);   // lvalueリファレンス
    static_assert(std::is_same_v<int&, decltype(Ref<int&>::u)>);   // lvalueリファレンス

    static_assert(std::is_same_v<int&, decltype(Ref<int&&>::t)>);  // lvalueリファレンス
    static_assert(std::is_same_v<int&&, decltype(Ref<int&&>::u)>); // rvalueリファレンス
```

この機能がないC++03では、

```cpp
    //  example/core_lang_spec/ref_collapsing_ut.cpp 52

    template <typename T>
    struct AddRef {
        using type = T&;
    };
```

ようなクラステンプレートに下記コードのようにリファレンス型を渡すとコンパイルエラーとなる。

```cpp
    //  example/core_lang_spec/ref_collapsing_ut.cpp 69

    static_assert(std::is_same_v<int&, AddRef<int&>::type>);
```

この問題を回避するためには下記のようなテンプレートの特殊化が必要になる。

```cpp
    //  example/core_lang_spec/ref_collapsing_ut.cpp 59

    template <typename T>
    struct AddRef<T&> {
        using type = T&;
    };
```

上記したようなクラステンプレートでのメンバエイリアスの宣言は、
[テンプレートメタプログラミング](https://ja.wikipedia.org/wiki/%E3%83%86%E3%83%B3%E3%83%97%E3%83%AC%E3%83%BC%E3%83%88%E3%83%A1%E3%82%BF%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0)
で頻繁に使用されるため、
このようなテンプレートの特殊化を不要にするリファレンスcollapsingは、
有用な機能拡張であると言える。

### リファレンス修飾 <a id="SS_19_8_7"></a>
[rvalue修飾](core_lang_spec.md#SS_19_8_7_1)と[lvalue修飾](core_lang_spec.md#SS_19_8_7_2)とを併せて、リファレンス修飾と呼ぶ。

#### rvalue修飾 <a id="SS_19_8_7_1"></a>
下記GetString0()のような関数が返すオブジェクトの内部メンバに対する[ハンドル](cpp_idioms.md#SS_21_12_7)は、
オブジェクトのライフタイム終了後にもアクセスすることができるため、
そのハンドルを通じて、
ライフタイム終了後のオブジェクトのメンバオブジェクトにもアクセスできてしまう。

ライフタイム終了後のオブジェクトにアクセスすることは未定義動作であり、
特にそのオブジェクトがrvalueであった場合、さらにその危険性は高まる。

こういったコードに対処するためのシンタックスが、lvalue修飾、rvalue修飾である。

下記GetString1()、GetString3()、GetString4()のようにメンバ関数をlvalue修飾やrvalue修飾することで、
rvalueの内部ハンドルを返さないようにすることが可能となり、上記の危険性を緩和することができる。

```cpp
    //  example/core_lang_spec/ref_qualifiers_ut.cpp 8

    class C {
    public:
        explicit C(char const* str) : str_{str} {}

        // lvalue修飾なし、rvalue修飾なし
        std::string& GetString0() noexcept { return str_; }

        // lvalue修飾
        std::string const& GetString1() const& noexcept { return str_; }

        // rvalue修飾
        // *thisがrvalueの場合でのGetString1()の呼び出しは、この関数を呼び出すため、
        // class内部のハンドルを返してはならない。
        // また、それによりstd::stringを生成するため、noexcept指定してはならない。
        std::string GetString1() const&& { return str_; }

        // lvalue修飾だが、const関数はrvalueからでも呼び出せる。
        // rvalueに対しての呼び出しを禁止したい場合には、GetString4のようにする。
        std::string const& GetString2() const& noexcept { return str_; }

        // lvalue修飾
        // 非constなのでrvalueからは呼び出せない。
        std::string const& GetString3() & noexcept { return str_; }

        // lvalue修飾
        std::string const& GetString4() const& noexcept { return str_; }

        // rvalue修飾
        // rvalueからこの関数を呼び出されるとrvalueオブジェクトの内部ハンドルを返してしまい、
        // 危険なので=deleteすべき。
        std::string const& GetString4() const&& = delete;

    private:
        std::string str_;
    };
```
```cpp
    //  example/core_lang_spec/ref_qualifiers_ut.cpp 49

    auto        c    = C{"c0"};
    auto const& s0_0 = c.GetString0();        // OK cが解放されるまでs0_0は有効
    auto        s0_1 = C{"c1"}.GetString0();  // NG 危険なコード
    // s0_1が指すオブジェクトは、次の行で無効になる

    auto const& s1_0 = c.GetString1();        // OK GetString1()&が呼び出される
    auto const& s1_1 = C{"c1"}.GetString1();  // OK GetString1()&&が呼び出される
    // s1_0が指すrvalueはs1_0がスコープアウトするまで有効

    auto const& s2_0 = c.GetString2();        // OK GetString2()&が呼び出される
    auto const& s2_1 = C{"c1"}.GetString2();  // NG const関数はlvalue修飾しても呼び出し可能
    // s2_1が指すオブジェクトは、次の行で無効になる

    auto const& s3_0 = c.GetString3();  // OK GetString3()&が呼び出される
    // auto const& s3_1 = C{"c1"}.GetString3();  // 危険なのでコンパイルさせない

    auto const& s4_0 = c.GetString4();  // OK GetString4()&が呼び出される
    // auto const& s4_1 = C{"c1"}.GetString4();  // 危険なのでコンパイルさせない
```

#### lvalue修飾 <a id="SS_19_8_7_2"></a>
[rvalue修飾](core_lang_spec.md#SS_19_8_7_1)を参照せよ。


## 構文と制御構造 <a id="SS_19_9"></a>

### 属性構文 <a id="SS_19_9_1"></a>
C++14から導入されたの属性構文は、[[属性名]]の形式で記述され、
特定のコード要素に対する追加情報やコンパイラへの指示を与えるためのものである。

|属性                 |C++Ver|効果                                               |
|---------------------|------|---------------------------------------------------|
|[[noreturn]]         |C++11 |関数が決して返らないことを示す                     |
|[[deprecated]]       |C++14 |関数や変数が非推奨であることを示しめす             |
|[[maybe_unused]]     |C++17 |変数や関数が未使用である警告の抑止                 |
|[[nodiscard]]        |C++17 |戻り値が無視されると警告                           |
|[[fallthrough]]      |C++14 |switch文のfallthroughの警告抑止                    |
|[[no_unique_address]]|C++20 |クラスや構造体のメンバに対して、メモリの最適化促進 |

```cpp
    //  example/core_lang_spec/attr_ut.cpp 10

    // 非推奨の関数
    [[deprecated("この関数は非推奨です。代わりに newFunction を使用してください。")]]  // 
    void oldFunction();  // この関数を呼び出すと警告される
    void newFunction();
```
```cpp
    //  example/core_lang_spec/attr_ut.cpp 20
    void processValues()
    {
        [[maybe_unused]] int unusedValue = 42;  // 使用しない変数でも警告が出ない

        // do something
    }
```
```cpp
    //  example/core_lang_spec/attr_ut.cpp 28

    [[nodiscard]] int computeResult() { return 42; }

    //  example/core_lang_spec/attr_ut.cpp 38

    computeResult();               // 警告が出る：戻り値が無視されている
    int result = computeResult();  // これはOK
```
```cpp
    //  example/core_lang_spec/attr_ut.cpp 54

    switch (value) {
    case 1:
        // do something
        [[fallthrough]];  // 明示的に fallthrough を宣言することができる
    case 2:
        // do something
        break;
    default:
        break;
    }
```

### 関数tryブロック <a id="SS_19_9_2"></a>
関数tryブロックとはtry-catchを本体とした下記のような関数のブロックを指す。

```cpp
    //  example/core_lang_spec/func_try_block.cpp 8

    void function_try_block()
    try {  // 関数tryブロック
        // 何らかの処理
        // ...
    }
    catch (std::length_error const& e) {  // 関数tryブロックのエクセプションハンドラ
        // ...
    }
    catch (std::logic_error const& e) {  // 関数tryブロックのエクセプションハンドラ
        // ...
    }
```

### 範囲for文 <a id="SS_19_9_3"></a>
範囲for文は、

```cpp
    for ( for-range-declaration : for-range-initializer ) statement
```

このような形式で表され、C++17までは下記のような疑似コードに展開される。

```cpp
    {
        auto && __range = for-range-initializer;
        for ( auto __begin = begin-expr, __end = end-expr; __begin != __end; ++__begin ) {
        for-range-declaration = *__begin;
        statement
      }
    }
```

単純な範囲for文の使用例は下記の通りである。

```cpp
    //  example/core_lang_spec/range_for_ut.cpp 14

    auto list = std::list{1, 2, 3};
    auto oss  = std::stringstream{};

    for (auto a : list) {  // 範囲for文
        oss << a;
    }
    ASSERT_EQ(oss.str(), "123");
```

上記のコードは下記のように展開される。

```cpp
    //  example/core_lang_spec/range_for_ut.cpp 26

    auto list = std::list{1, 2, 3};
    auto oss  = std::stringstream{};

    // std::begin(list)、std::end(list)の戻り型が同一
    static_assert(std::is_same_v<decltype(std::begin(list)), decltype(std::end(list))>);

    // 上記の範囲for文は下記のように展開される
    for (auto it = std::begin(list); it != std::end(list); ++it) {
        oss << *it;
    }

    ASSERT_EQ(oss.str(), "123");
```


C++17以前は、上記のコードのコメントにある通り、`__begin`と`__end`が同一の型である前提であった。
C++17以降は、この規制が緩和されたため、以下のように展開されることになった。

```cpp
    {
        auto && __range = for-range-initializer;
        auto __begin = begin-expr;
        auto __end = end-expr;     // C++17までは、__begin と __endは同一である前提
        for ( ; __begin != __end; ++__begin ) {
            for-range-declaration = *__begin;
            statement
        }
    }
```

この規制緩和により、以下のようなコードが範囲for文で記述できるようになった。
下記のコードはこの緩和ルールの応用例である。

```cpp
    //  example/core_lang_spec/range_for_ut.cpp 73

    delimited_string<','> delimited_str{"Hello,World"};
    std::ostringstream    oss;

    // ',' を終了文字として "Hello" だけをループして出力
    for (auto c : delimited_str) {
        oss << c;
    }

    ASSERT_EQ("Hello", oss.str());  // 結果は "Hello" になるはず
```
上記のコードは下記のように展開される。

```cpp
    //  example/core_lang_spec/range_for_ut.cpp 87

    delimited_string<','> delimited_str{"Hello,World"};
    std::ostringstream    oss;

    // ',' を終了文字として"Hello" だけをループして出力
    for (auto it = delimited_str.begin(); it != delimited_str.end(); ++it) {
        oss << *it;
    }

    ASSERT_EQ("Hello", oss.str());  // 結果は "Hello" になるはず
```

### 構造化束縛 <a id="SS_19_9_4"></a>
構造化束縛はC++17 から導入されたもので、std::tuppleやstd::pair、std::arrayなど、
構造体のメンバーを個別の変数に分解して簡潔に扱うことをできるようにするための機能である。

```cpp
    //  example/core_lang_spec/structured_binding_ut.cpp 13

    // tupleでの構造化束縛の例
    std::tuple<int, double, std::string> tobj(1, 2.5, "Hello");

    auto [i, d, s] = tobj;  // 構造化束縛を使用してタプルを分解

    ASSERT_EQ(i, 1);
    ASSERT_DOUBLE_EQ(d, 2.5);
    ASSERT_EQ("Hello", s);
```
```cpp
    //  example/core_lang_spec/structured_binding_ut.cpp 28

    // pairでの構造化束縛の例
    std::pair<int, std::string> pobj(42, "example");

    auto [i, s] = pobj;  // 構造化束縛を使用してペアを分解

    ASSERT_EQ(i, 42);
    ASSERT_EQ("example", s);
```
```cpp
    //  example/core_lang_spec/structured_binding_ut.cpp 42

    struct Person {
        std::string name;
        int         age;
    };

    Person person{"Ichiro", 30};  // 構造体のインスタンス

    auto& [name, age] = person;  // 構造化束縛を使用して構造体のメンバーを分解

    static_assert(std::is_same_v<decltype(name), std::string>);  // これは正しい
    // static_assert(std::is_same_v<decltype(name), std::string&>); これはコンパイルエラー
    // 上記がコンパイルエラーになる理由は以下の通り。
    //
    // 変数宣言は、 autoを記述したあとに角カッコ内に変数名を列挙する。
    // それぞれの変数に対する型や修飾子の指定はできない。
    // autoの部分を const auto&のように、全体に対してCV修飾や参照を付加することはできる。
    // それぞれの変数の型は、各要素をdecltypeしたものとなる。
    //                        ^^^^^^^^^^^^^^ nameの型がstd::stringと評価された理由

    name = "Taro";  // nameはリファレンス
    age  = 56;      // ageはリファレンス
    ASSERT_EQ(person.name, "Taro");
    ASSERT_EQ(person.age, 56);
```
```cpp
    //  example/core_lang_spec/structured_binding_ut.cpp 72

    auto array = std::array<int, 3>{1, 2, 3};

    auto [x, y, z] = array;  // 構造化束縛を使って std::array の要素を分解

    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);
    ASSERT_EQ(z, 3);
```

### 初期化付きif/switch文 <a id="SS_19_9_5"></a>
C++17で、if文とswitc文に初期化を行う構文が導入された。
これにより、変数をそのスコープ内で初期化し、その変数を条件式の評価に使用できる。
初期化された変数は、if文やswitch文のスコープ内でのみ有効であり、他のスコープには影響を与えない。

この構文は、従来のfor文で使用されていた初期化ステートメントを、if/switch文に拡張したものである。
この類似性が理解しやすいように、本節では、 敢えて以下のコード例で同じ関数、同じクラスを使用し、
対比できるようにした。

- [初期化付きfor文(従来のfor文)](core_lang_spec.md#SS_19_9_5_1)
- [初期化付きwhile文(従来のwhile文)](core_lang_spec.md#SS_19_9_5_2)
- [初期化付きif文](core_lang_spec.md#SS_19_9_5_3)
- [初期化付きswitch文](core_lang_spec.md#SS_19_9_5_4)


#### 初期化付きfor文(従来のfor文) <a id="SS_19_9_5_1"></a>
下記の疑似コードは従来のfor文の構造を表す。

```cpp
    for (init-statement; condition; post-statement) {
        // ループ処理
    }
```
上記のと同様の実際のfor文のコードを以下に示す。

```cpp
    //  example/core_lang_spec/if_switch_init_ut.cpp 8

    class OperationResult {
    public:
        enum class ErrorCode { NoError, ErrorPattern1, ErrorPattern2, ErrorPattern3 };
        bool      IsError() const noexcept;
        ErrorCode Get() const noexcept;
                  operator bool() const noexcept { return IsError(); }

    private:
        // 何らかの定義
    };

    OperationResult DoOperation();                                 // 何らかの処理
    void            RecoverOperation(OperationResult::ErrorCode);  // リカバリ処理
```
```cpp
    //  example/core_lang_spec/if_switch_init_ut.cpp 33

    for (auto result = DoOperation(); result.IsError(); result = DoOperation()) {
        RecoverOperation(result.Get());  // エラー処理
    }

    // 以下、成功時の処理
    // ...
```

#### 初期化付きwhile文(従来のwhile文) <a id="SS_19_9_5_2"></a>
下記の疑似コードこの節で説明しようとしているwhile文の構造を表す(従来からのwhile文)。

```cpp
    while (type-specifier-seq declarator) {
        // 条件がtrueの場合の処理
    }
```

[初期化付きif文](core_lang_spec.md#SS_19_9_5_3)/[初期化付きswitch文](core_lang_spec.md#SS_19_9_5_4)はC++17から導入されたシンタックスであるが、
それと同様のシンタックスはwhileには存在しないが、
以下のコード例のように従来の記法は広く知られているため、念とため紹介する。

```cpp
    //  example/core_lang_spec/if_switch_init_ut.cpp 46

    while (auto result = DoOperation()) {  // resultはboolへの暗黙の型変換が行われる
        // エラー処理
    }
    // resultはスコープアウトする
```

#### 初期化付きif文 <a id="SS_19_9_5_3"></a>
下記の疑似コードこの節で説明しようとしているif文の構造を表す。

```cpp
    if (init-statement; condition) {
        // 条件がtrueの場合の処理
    }
```

上記と同様の構造を持つ実際のif文のコードを以下に示す。

```cpp
    //  example/core_lang_spec/if_switch_init_ut.cpp 8

    class OperationResult {
    public:
        enum class ErrorCode { NoError, ErrorPattern1, ErrorPattern2, ErrorPattern3 };
        bool      IsError() const noexcept;
        ErrorCode Get() const noexcept;
                  operator bool() const noexcept { return IsError(); }

    private:
        // 何らかの定義
    };

    OperationResult DoOperation();                                 // 何らかの処理
    void            RecoverOperation(OperationResult::ErrorCode);  // リカバリ処理
```
```cpp
    //  example/core_lang_spec/if_switch_init_ut.cpp 57

    if (auto result = DoOperation(); !result.IsError()) {
        // 成功処理
    }
    else {
        RecoverOperation(result.Get());  // エラー処理
    }
    // resultはスコープアウトする
```

クラスの独自の[<=>演算子](core_lang_spec.md#SS_19_6_4_1)を定義する場合、下記のように使用することができる。

```cpp
    //  example/core_lang_spec/if_switch_init_ut.cpp 70

    struct DoubleName {
        std::string name0;
        std::string name1;
        friend bool operator==(DoubleName const& lhs, DoubleName const& rhs) noexcept = default;
    };

    inline auto operator<=>(DoubleName const& lhs, DoubleName const& rhs) noexcept
    {
        // name0 を比較し、等しくなければその比較結果を返す
        if (auto cmp = lhs.name0 <=> rhs.name0; cmp != 0) {
            return cmp;
        }

        return lhs.name1 <=> rhs.name1;  // name0が等しければ name1を比較
    }
```

#### 初期化付きswitch文 <a id="SS_19_9_5_4"></a>
下記の疑似コードはこの節で説明しようとしているswitch文の構造を表す。

```cpp
    switch (init-statement; condition) {
        case value1:
            // 条件が value1 の場合の処理
            break;
        case value2:
            // 条件が value2 の場合の処理
            break;
        // その他のケース
    }

```
上記と同様の構造を持つ実際のswitch文のコードを以下に示す。

```cpp
    //  example/core_lang_spec/if_switch_init_ut.cpp 8

    class OperationResult {
    public:
        enum class ErrorCode { NoError, ErrorPattern1, ErrorPattern2, ErrorPattern3 };
        bool      IsError() const noexcept;
        ErrorCode Get() const noexcept;
                  operator bool() const noexcept { return IsError(); }

    private:
        // 何らかの定義
    };

    OperationResult DoOperation();                                 // 何らかの処理
    void            RecoverOperation(OperationResult::ErrorCode);  // リカバリ処理
```
```cpp
    //  example/core_lang_spec/if_switch_init_ut.cpp 101

    switch (auto result = DoOperation(); result.Get()) {
    case OperationResult::ErrorCode::ErrorPattern1:
        RecoverOperation(result.Get());  // エラー処理
        break;
        // エラー処理のいくつかのパターン
    case OperationResult::ErrorCode::NoError:
        // 成功処理
    default:
        assert(false);  // ここには来ないはず
    }
    // resultはスコープアウトする
```

## 言語拡張機能 <a id="SS_19_10"></a>
### コルーチン <a id="SS_19_10_1"></a>
コルーチンはC++20から導入された機能であり、以下の新しいキーワードによりサポートされる。

* [co_await](core_lang_spec.md#SS_19_10_1_1)
* [co_return](core_lang_spec.md#SS_19_10_1_2)
* [co_yield](core_lang_spec.md#SS_19_10_1_3)

#### co_await <a id="SS_19_10_1_1"></a>
co_awaitはコルーチンの非同期操作の一時停止と再開に使用される。
co_waitとco_returnを使用したコードを以下に示す。

```cpp
    //  example/core_lang_spec20/co_await_ut.cpp 12

    class Task {  // コルーチンが返す型
    public:
        /// @struct promise_type
        /// @brief コルーチンのライフサイクルを管理する構造体
        struct promise_type {
            /// @brief コルーチンから Task 型のオブジェクトを返す関数
            /// @return Taskオブジェクト
            Task get_return_object() { return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; }

            /// @brief コルーチンの最初のサスペンドポイント
            /// @return 常にサスペンドするオブジェクトを返す
            std::suspend_always initial_suspend() { return {}; }

            /// @brief コルーチンの最後のサスペンドポイント
            /// @return 常にサスペンドするオブジェクトを返す
            std::suspend_always final_suspend() noexcept { return {}; }

            /// @brief コルーチン内で例外が発生した場合に呼び出される
            /// @details コルーチン内で未処理の例外が発生した場合に、プロセスを終了する
            void unhandled_exception() { std::exit(1); }

            /// @brief コルーチンが終了した際に呼び出される
            /// @details co_return で値が返されない場合に呼び出されるが、何も行わない
            void return_void() {}
        };

        /// @brief Task のコンストラクタ
        /// @param h コルーチンハンドル
        Task(std::coroutine_handle<promise_type> h) : coro{h} {}

        /// @brief コルーチンの呼び出し回数に基づいた文字列を返す
        /// @return 呼び出し回数に応じた "call X" という文字列
        std::string get_value() { return "call " + std::to_string(called); }

        /// @brief コルーチンを再開する
        /// @details コルーチンが終了していなければ再開し、呼び出し回数をカウントする
        /// @return コルーチンが完了していなければ true、完了していれば false
        bool resume()
        {
            ++called;                 // コルーチンを呼び出した回数をカウント
            if (!coro.done()) {       // コルーチンが完了していなければ
                coro.resume();        // 再開
                return !coro.done();  // 再開後も完了していなければ true を返す
            }
            return false;  // すでに完了している場合は false を返す
        }

        /// @brief Task のデストラクタ
        /// @details コルーチンハンドルが有効であれば破棄する
        ~Task()
        {
            if (coro) coro.destroy();
        }

    private:
        std::coroutine_handle<promise_type> coro;        ///< コルーチンハンドル
        uint32_t                            called = 0;  ///< コルーチンが再開された回数
    };

    /// @brief コルーチンを生成する関数
    /// @return Taskオブジェクト
    Task gen_coroutine()
    {
        co_await std::suspend_always{};  // 最初のサスペンドポイント
        co_await std::suspend_always{};  // 2回目のサスペンドポイント
        co_return;                       // コルーチン終了
    }
```
以下単体テストコードによりに上記コルーチンの動作を示す。

```cpp
    //  example/core_lang_spec20/co_await_ut.cpp 85

    Task    task  = gen_coroutine();  // gen_coroutine から Task オブジェクトを生成
    int32_t calls = 0;

    /// @test コルーチンを resume() で再開し、完了するまでループする
    while (task.resume()) {  // コルーチンが完了していない間、再開
        switch (calls) {
        case 0:
            /// @test コルーチンが1回目の再開後、"call 1" が返されることを確認
            ASSERT_EQ("call 1", task.get_value());
            break;
        case 1:
            /// @test コルーチンが2回目の再開後、"call 2" が返されることを確認
            ASSERT_EQ("call 2", task.get_value());
            break;
        case 2:
            /// @test コルーチンが3回目の再開後、"call 3" が返されることを確認
            ASSERT_EQ("call 3", task.get_value());
            break;
        }
        ++calls;
    }

    /// @test コルーチンが 2 回 resume された後に終了していることを確認
    ASSERT_EQ(2, calls);
```

上記のコルーチンと同じ機能を持つクラスのco_await/co_returnを使わない実装を以下に示す。

```cpp
    //  example/core_lang_spec20/co_await_ut.cpp 115

    /// @enum CoroutineState
    /// @brief ManualCoroutine の状態を表す enum 型
    enum class CoroutineState {
        Start,             ///< コルーチンが開始された状態
        FirstSuspension,   ///< コルーチンが最初にサスペンドされた状態
        SecondSuspension,  ///< コルーチンが2回目にサスペンドされた状態
        Finished           ///< コルーチンが完了した状態
    };

    /// @brief コルーチンの状態を保持し、進行を管理するためのクラス
    class ManualCoroutine {
    public:
        /// @brief コルーチンの代わりに状態を進行させる関数
        /// @details コルーチンの状態に基づいて進行し、コルーチンのように振る舞う
        /// @return コルーチンが継続可能なら true、終了していれば false を返す
        bool resume()
        {
            ++called;  // コルーチンの再開回数をカウント
            switch (state) {
            case CoroutineState::Start:
                state = CoroutineState::FirstSuspension;
                return true;  // 継続可能

            case CoroutineState::FirstSuspension:
                state = CoroutineState::SecondSuspension;
                return true;  // 継続可能

            case CoroutineState::SecondSuspension:
                state = CoroutineState::Finished;
                return false;  // 終了

            case CoroutineState::Finished:
                return false;  // 既に終了している
            }
            assert(false);  // 不正な状態（理論的には到達しないはず）
            return false;
        }

        /// @brief 呼び出し回数に基づいた文字列を返す
        /// @return "call X" という形式の文字列（X は呼び出し回数）
        std::string get_value() { return "call " + std::to_string(called); }

    private:
        uint32_t       called = 0;                      ///< コルーチンが再開された回数
        CoroutineState state  = CoroutineState::Start;  ///< 現在のコルーチンの状態
    };
```

このクラスは当然ながら、前記のコルーチンの単体テストコードとほぼ同じになる。

```cpp
    //  example/core_lang_spec20/co_await_ut.cpp 167

    auto    manual_coroutine = ManualCoroutine{};
    int32_t calls            = 0;

    while (manual_coroutine.resume()) {  // コルーチンを再開する
        switch (calls) {
        case 0:
            /// @test 1回目の再開後に "call 1" が返されることを確認
            ASSERT_EQ("call 1", manual_coroutine.get_value());
            break;
        case 1:
            /// @test 2回目の再開後に "call 2" が返されることを確認
            ASSERT_EQ("call 2", manual_coroutine.get_value());
            break;
        case 2:
            /// @test 3回目の再開後に "call 3" が返されることを確認
            ASSERT_EQ("call 3", manual_coroutine.get_value());
            break;
        }
        ++calls;  ///< コルーチンの再開回数をインクリメント
    }

    /// @test コルーチンが2回 resume された後に終了していることを確認
    ASSERT_EQ(2, calls);
```

C++20から導入されたco_await、co_return、TaskとC++17以前の機能のみを使用したコードの対比によって、
コルーチンのサポート機能により実装が容易になることが理解できるだろう。

#### co_return <a id="SS_19_10_1_2"></a>
co_returnはコルーチンの終了時に値を返すために使用される。
co_returnは通常[co_await](core_lang_spec.md#SS_19_10_1_1)と同時に使われることが多い。

#### co_yield <a id="SS_19_10_1_3"></a>
co_yieldはコルーチンから値を返しつつ、
次の再開ポイントまで処理を中断する。これはジェネレーターの実装に便利である。

```cpp
    //  example/core_lang_spec20/co_yield_ut.cpp 12

    template <typename T>
    class Generator {
    public:
        Generator(Generator&& other) noexcept : coro{std::move(other.coro)} { other.coro = nullptr; }

        Generator& operator=(Generator&& other) noexcept
        {
            if (this != &other) {
                coro       = other.coro;
                other.coro = nullptr;
            }
            return *this;
        }

        /// @struct promise_type
        /// @brief コルーチンのライフサイクルを管理する構造体
        struct promise_type {
            T current_value;

            /// @brief コルーチンから Generator 型のオブジェクトを返す関数
            /// @return Generatorオブジェクト
            Generator get_return_object() { return Generator{std::coroutine_handle<promise_type>::from_promise(*this)}; }

            /// @brief コルーチンの最初のサスペンドポイント
            /// @return 常にサスペンドするオブジェクトを返す
            std::suspend_always initial_suspend() { return {}; }

            /// @brief コルーチンの最後のサスペンドポイント
            /// @return 常にサスペンドするオブジェクトを返す
            std::suspend_always final_suspend() noexcept { return {}; }

            /// @brief コルーチンで値を生成するためのサスペンドポイント
            /// @param value 生成された値
            /// @return 常にサスペンドするオブジェクトを返す
            std::suspend_always yield_value(T value)
            {
                current_value = value;
                return {};
            }

            /// @brief コルーチン内で例外が発生した場合に呼び出される
            void unhandled_exception() { std::exit(1); }

            /// @brief コルーチンの終了時に呼び出される
            void return_void() {}
        };

        /// @brief コルーチンを再開し、次の値を生成する
        /// @return 次の値が生成された場合は true、終了した場合は false
        bool move_next()
        {
            if (coro && !coro.done()) {
                coro.resume();
                return !coro.done();
            }
            return false;
        }

        /// @brief 現在の値を取得する
        /// @return 現在の値
        T current_value() const { return coro.promise().current_value; }

        /// @brief Generator のコンストラクタ
        /// @param h コルーチンハンドル
        Generator(std::coroutine_handle<promise_type> h) : coro(h) {}

        /// @brief Generator のデストラクタ
        /// @details コルーチンハンドルが有効であれば破棄する
        ~Generator()
        {
            if (coro) coro.destroy();
        }

    private:
        std::coroutine_handle<promise_type> coro;
    };

    /// @brief 偶数のみをフィルタリングする
    /// @param input フィルタ対象の Generator
    /// @return フィルタ後の Generator
    Generator<int> filter_even(Generator<int> input)
    {
        while (input.move_next()) {
            if (input.current_value() % 2 == 0) {
                co_yield input.current_value();
            }
        }
    }

    /// @brief 値を2倍に変換する
    /// @param input 変換対象の Generator
    /// @return 変換後の Generator
    Generator<int> double_values(Generator<int> input)
    {
        while (input.move_next()) {
            co_yield input.current_value() * 2;
        }
    }

    /// @brief 数値の範囲を生成する
    /// @param start 開始値
    /// @param end 終了値
    /// @return 範囲内の数値を生成する Generator
    Generator<int> generate_numbers(int start, int end)
    {
        for (int i = start; i <= end; ++i) {
            co_yield i;
        }
    }
```
このテストを以下に示す。

```cpp
    //  example/core_lang_spec20/co_yield_ut.cpp 127

    // 数値を生成し、それをパイプライン処理に通す
    auto numbers         = generate_numbers(1, 10);
    auto even_numbers    = filter_even(std::move(numbers));
    auto doubled_numbers = double_values(std::move(even_numbers));

    // 結果を検証するために期待される値の配列を準備
    std::vector<int> expected_values = {4, 8, 12, 16, 20};

    // 生成された値を順に取得し、期待される値と比較
    size_t index = 0;
    while (doubled_numbers.move_next()) {
        ASSERT_LT(index, expected_values.size());  // インデックスが範囲内か確認
        EXPECT_EQ(doubled_numbers.current_value(), expected_values[index]);
        ++index;
    }

    // 最終的にすべての期待される値が生成されたことを確認
    EXPECT_EQ(index, expected_values.size());
```

[co_await](core_lang_spec.md#SS_19_10_1_1)、co_returnの例でみたように、
co_yieldを使用したコルーチンと同じ機能を持つクラスのco_yieldを使わない実装を以下に示す。

```cpp
    //  example/core_lang_spec20/co_yield_ut.cpp 152

    /// @brief コルーチンを使わずにデータを逐次的に提供するジェネレータークラス
    template <typename T>
    class Generator {
    public:
        /// @brief コンストラクタ
        /// @param data 生成対象のデータ
        Generator(std::vector<T>&& data) : data_(std::move(data)), current_index_(0) {}

        /// @brief 次の値があるかを確認し、次の値に進む
        /// @return 次の値が存在する場合は true、存在しない場合は false
        bool move_next()
        {
            if (current_index_ < data_.size()) {
                ++current_index_;
                return true;
            }
            return false;
        }

        /// @brief 現在の値を取得する
        /// @return 現在の値
        T current_value() const
        {
            if (current_index_ > 0 && current_index_ <= data_.size()) {
                return data_[current_index_ - 1];
            }
            throw std::out_of_range("Invalid current value access");
        }

    private:
        std::vector<T> data_;           ///< データを保持
        size_t         current_index_;  ///< 現在のインデックス
    };

    /// @brief 偶数のみをフィルタリングする
    /// @param input フィルタ対象の Generator
    /// @return フィルタ後の Generator
    Generator<int> filter_even(const Generator<int>& input)
    {
        std::vector<int> filtered;
        auto             gen = input;

        while (gen.move_next()) {
            if (gen.current_value() % 2 == 0) {
                filtered.push_back(gen.current_value());
            }
        }
        return Generator<int>(std::move(filtered));
    }

    /// @brief 値を2倍に変換する
    /// @param input 変換対象の Generator
    /// @return 変換後の Generator
    Generator<int> double_values(const Generator<int>& input)
    {
        std::vector<int> doubled;
        auto             gen = input;

        while (gen.move_next()) {
            doubled.push_back(gen.current_value() * 2);
        }
        return Generator<int>(std::move(doubled));
    }

    /// @brief 数値の範囲を生成する
    /// @param start 開始値
    /// @param end 終了値
    /// @return 範囲内の数値を生成する Generator
    Generator<int> generate_numbers(int start, int end)
    {
        std::vector<int> numbers;
        for (int i = start; i <= end; ++i) {
            numbers.push_back(i);
        }
        return Generator<int>(std::move(numbers));
    }
```

このクラスは当然ながら、前記のコルーチンの単体テストコードとほぼ同じになる。

```cpp
    //  example/core_lang_spec20/co_yield_ut.cpp 234

    // 数値を生成し、それをパイプライン処理に通す
    auto numbers         = generate_numbers(1, 10);
    auto even_numbers    = filter_even(std::move(numbers));
    auto doubled_numbers = double_values(std::move(even_numbers));

    // 結果を検証するために期待される値の配列を準備
    std::vector<int> expected_values = {4, 8, 12, 16, 20};

    // 生成された値を順に取得し、期待される値と比較
    size_t index = 0;
    while (doubled_numbers.move_next()) {
        ASSERT_LT(index, expected_values.size());  // インデックスが範囲内か確認
        EXPECT_EQ(doubled_numbers.current_value(), expected_values[index]);
        ++index;
    }

    // 最終的にすべての期待される値が生成されたことを確認
    EXPECT_EQ(index, expected_values.size());
```

C++20から導入されたco_await、co_return、TaskとC++17以前の機能のみを使用したコードの対比によって、
コルーチンのサポート機能により実装が容易になることが理解できるだろう。

### モジュール <a id="SS_19_10_2"></a>
モジュールはC++20から導入された機能であり、以下の新しいキーワードによりサポートされる。

* module: モジュールを宣言する。独立した構造を持ち、名前の衝突を防ぐ。
* export: モジュール外部に公開する関数やクラスを指定する。公開しない要素はモジュール内に限定される。
* import: 他のモジュールをインポートして利用できる。従来の#includeと異なり、依存関係を最適化し、ビルド時間を短縮する。

以下にこれらのキーワードのコード例を示す。

まずは、同時に使われることが多い`module`と`export`の使用例を示す。

```cpp
    //  example/module_cmake/type_traits.cppm 1

    export module type_traits;  // モジュール宣言

    namespace type_traits {  // 通常の名前空間。モジュール名と同じにして良い
    namespace Inner_ {       // 内部実装であるためexportしない

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

    export
    {  // 纏めてexport
        template <typename T>
        constexpr bool is_void() noexcept
        {
            return Inner_::is_void_sfinae_f_detector(nullptr, static_cast<T*>(nullptr));
        }
        template <typename T>
        bool is_void_v = is_void<T>();
    }
    }  // namespace type_traits
```

最後に`import`の使用例を示す。

```cpp
    //  example/module_cmake/main.cpp 1

    import math;        // モジュールのインポート
    import type_traits; // モジュールのインポート

    #include <iostream>  // これまで同様のインクルード。stdのモジュール化はC++23から

    void f(int a, int b)
    {
        std::cout << "Add: " << math::add(a, b) << std::endl;
        std::cout << "Multiply: " << math::multiply(a, b) << std::endl;

        std::cout << std::boolalpha << type_traits::is_void<void>() << std::endl;
        std::cout << std::boolalpha << type_traits::is_void_v<decltype(a)> << std::endl;
    }
```

これらにより、モジュールは依存関係の管理、名前空間の分離、ビルド時間の短縮を実現し、
大規模プロジェクトでの保守性向上に貢献する。
が、一方ではC++のモジュールに対応してるビルドツールを使用することが望ましい。

### ラムダ式 <a id="SS_19_10_3"></a>
ラムダ式に関する言葉の定義と例を示す。

* ラムダ式とは、その場で関数オブジェクトを定義する式。
* クロージャ(オブジェクト)とは、ラムダ式から生成された関数オブジェクト。
* クロージャ型とは、クロージャオブジェクトの型。
* キャプチャとは、ラムダ式外部の変数をラムダ式内にコピーかリファレンスとして定義する機能。
* ラムダ式からキャプチャできるのは、ラムダ式から可視である自動変数と仮引数(thisを含む)。
* [constexprラムダ](core_lang_spec.md#SS_19_5_9)とはクロージャ型の[constexprインスタンス](core_lang_spec.md#SS_19_5_6)。
* [ジェネリックラムダ](core_lang_spec.md#SS_19_11_6)とは、C++11のラムダ式を拡張して、
  パラメータにautoを使用(型推測)できるようにした機能。

```cpp
    //  example/core_lang_spec/lambda.cpp 10

    auto a = 0;

    // closureがクロージャ。それを初期化する式がラムダ式
    // [a = a]がキャプチャ
    // [a = a]内の右辺aは上記で定義されたa
    // [a = a]内の左辺aは右辺aで初期化された変数。ラムダ式内で使用されるaは左辺a。
    auto closure = [a = a](int32_t b) noexcept { return a + b; };

    auto ret = closure(3);  // クロージャの実行

    // g_closureはジェネリックラムダ
    auto g_closure = [](auto t0, auto t1) { return t0 + t1; };

    auto i = g_closure(1, 2);                                // t0、t1はint
    auto s = g_closure(std::string{"1"}, std::string{"2"});  // t0、t1はstd::string
```

#### クロージャ <a id="SS_19_10_3_1"></a>
「[ラムダ式](core_lang_spec.md#SS_19_10_3)」を参照せよ。

#### クロージャ型 <a id="SS_19_10_3_2"></a>
「[ラムダ式](core_lang_spec.md#SS_19_10_3)」を参照せよ。

#### 一時的ラムダ <a id="SS_19_10_3_3"></a>
一時的ラムダ(transient lambda)とは下記のような使い方をするラムダ式指す慣用用語である。

複雑な初期化を必要とするconstオブジェクトの生成をするような場合に有用なテクニックである。

```cpp
    //  example/core_lang_spec/transient_lambda_ut.cpp 9

    std::vector<int> vec{1, 2, 3};

    // ラムダ式を即時実行するために () を追加
    auto const vec_act = [&vec = vec]() {
        using arg_type = std::remove_reference_t<decltype(vec)>;
        arg_type temp;
        for (auto val : vec) {
            temp.push_back(val * 2);
        }
        return temp;  // 変更後のベクターを返す
    }();

    std::vector<int> const vec_exp{2, 4, 6};

    ASSERT_EQ(vec_act, vec_exp);
```

#### transient lambda <a id="SS_19_10_3_4"></a>
「[一時的ラムダ](core_lang_spec.md#SS_19_10_3_3)」を参照せよ。


### 指示付き初期化 <a id="SS_19_10_4"></a>
指示付き初期化(designated initialization)とは、C++20から導入されたシンタックスであり、
構造体やクラスのメンバを明示的に指定して初期化できるようにする機能である。
この構文により、コードの可読性と安全性が向上し、初期化漏れや順序の誤りを防ぐことができる。

まずは、この機能を有効に使えるクラス例を以下に示す。

```cpp
    //  example/core_lang_spec20/designated_init_ut.cpp 11

    struct Point {
        int  x;
        int  y;
        bool operator==(Point const& rhs) const noexcept = default;
    };

    class Circl {
    public:
        Circl(Point center, uint32_t radius) : center_{center}, radius_{radius} {}

        std::string to_string()
        {
            std::ostringstream oss;

            oss << "center x:" << center_.x << " y:" << center_.y << " radius:" << radius_;
            return oss.str();
        }

        bool operator==(Circl const& rhs) const noexcept = default;

    private:
        Point const center_;
        uint32_t    radius_;
    };
```
```cpp
    //  example/core_lang_spec20/designated_init_ut.cpp 41

    struct Point p0 {
        10, 20
    };
    struct Point p1 {
        .x = 10, .y = 20
    };  // x、yを明示できるため、可読性向上が見込める

    ASSERT_EQ(p0, p1);

    Circl circl_0{p1, 2U};
    ASSERT_EQ("center x:10 y:20 radius:2", circl_0.to_string());

    Circl circl_1{{10, 20}, 2U};  // circl_2に比べると可読性に劣る
    ASSERT_EQ("center x:10 y:20 radius:2", circl_1.to_string());

    Circl circl_2{{.x = 10, .y = 20}, 2U};  // x、yを明示できるため、可読性向上が見込める
    ASSERT_EQ("center x:10 y:20 radius:2", circl_2.to_string());

    ASSERT_EQ(circl_1, circl_2);
```

下記に示すように、[Polymorphic Memory Resource(pmr)](stdlib_and_concepts.md#SS_20_6)のpool_resourceの初期化には、
この機能を使うと可読性の改善が期待できる。

```cpp
    //  example/core_lang_spec20/designated_init_ut.cpp 68

    std::pmr::unsynchronized_pool_resource pool_resource(
        std::pmr::pool_options{
            .max_blocks_per_chunk        = 10,   // チャンクあたりの最大ブロック数
            .largest_required_pool_block = 1024  // 最大ブロックサイズ
        },
        std::pmr::new_delete_resource()  // フォールバックリソース
    );

    std::pmr::vector<int> vec{&pool_resource};  // pmrを使用するベクタの定義
```

指示付き初期化を使わない以下のコード例と上記を比べれば可読性の改善に議論の余地はないだろう。

```cpp
    //  example/core_lang_spec20/designated_init_ut.cpp 83

    // 指示付き初期化を使わずにstd::pmr::unsynchronized_pool_resourceの初期化
    std::pmr::unsynchronized_pool_resource pool_resource(
        std::pmr::pool_options{
            10,   // チャンクあたりの最大ブロック数
            1024  // 最大ブロックサイズ
        },
        std::pmr::new_delete_resource()  // フォールバックリソース
    );

    std::pmr::vector<int> vec{&pool_resource};  // pmrを使用するベクタの定義
```

## テンプレートと型推論 <a id="SS_19_11"></a>
### SFINAE <a id="SS_19_11_1"></a>
[SFINAE](https://cpprefjp.github.io/lang/cpp11/sfinae_expressions.html)
(Substitution Failure Is Not An Errorの略称、スフィネェと読む)とは、
「テンプレートのパラメータ置き換えに失敗した([ill-formed](core_lang_spec.md#SS_19_14_1)になった)際に、
即時にコンパイルエラーとはせず、置き換えに失敗したテンプレートを
[name lookup](core_lang_spec.md#SS_19_12_2)の候補から除外する」
という言語機能である。

### メタ関数 <a id="SS_19_11_2"></a>
メタ関数とは、型を引数として型または値を返すテンプレートのことを指す。
通常の関数が実行時に値を返すのに対し、メタ関数はコンパイル時に型情報を生成または変換する。
主要なメタ関数は標準ライブラリの[type_traits](stdlib_and_concepts.md#SS_20_2)で定義されている。

### コンセプト <a id="SS_19_11_3"></a>
C++17までのテンプレートには以下のような問題があった。

* [SFINAE](core_lang_spec.md#SS_19_11_1)による制約が複雑  
  テンプレートの制約を行うために、
  std::enable_ifやの仕組みを使う必要があり、コードが非常に複雑で難読になりがちだった。
* エラーメッセージが不明瞭  
  テンプレートのパラメータが不適切な型だった場合に、
  コンパイルエラーのメッセージが非常にわかりにくく、問題の原因を特定するのが困難だった。
* テンプレートの適用範囲が不明確  
  テンプレートの使用可能な型の範囲がドキュメントやコメントでしか表現されず、
  明確な制約がコードに反映されていなかったため、コードの意図が伝わりづらい。
* 部分特殊化やオーバーロードによる冗長性  
  特定の型に対するテンプレートの処理を制限するために、
  部分特殊化やテンプレートオーバーロードを行うことが多く、コードが冗長になりがちだった。

C++20から導入された「コンセプト(concepts)」は、
テンプレートパラメータを制約する機能である。
この機能を使用することで、以下のようなプログラミングでのメリットが得られる。

* テンプレートの制約を明確に定義できる  
  コンセプトを使うことで、テンプレートパラメータが満たすべき条件を宣言的に記述できるため、
  コードの意図が明確にできる。
* コンパイルエラーがわかりやすくなる  
  コンセプトを使用すると、テンプレートの適用範囲外の型に対して、
  より具体的でわかりやすいエラーメッセージが表示される。
* コードの可読性が向上する  
  コンセプトを利用することで、
  テンプレート関数やクラスのインターフェースが明確になり、可読性が向上する。

```cpp
    //  example/core_lang_spec/concept_ut.cpp 12

    // SFINAEを使用したc++17スタイル
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    T add(T a, T b)
    {
        return a + b;
    }

    //  example/core_lang_spec/concept_ut.cpp 24

    ASSERT_EQ(add(10, 20), 30);     // int型
    ASSERT_EQ(add(1.5, 2.5), 4.0);  // double型

    auto str1 = std::string{"Hello, "};
    auto str2 = std::string{"World!"};
    // add(str1, str2);  // これを試すとコンパイルエラー
    // concept_ut.cpp:10:3: note: candidate: ‘template<class T, class> T
    // {anonymous}::old_style::add(T, T)’
    //    10 | T add(T a, T b) {
    //       |   ^~~
    // concept_ut.cpp:10:3: note:   template argument deduction/substitution failed:
    // concept_ut.cpp:9:22: error: no type named ‘type’ in ‘struct std::enable_if<false, void>’
    //     9 | template<typename T, typename = typename
    //     std::enable_if<std::is_arithmetic<T>::value>::type>
    //       |                      ^~~~~~~~
    // エラーメッセージがわかりずらい
```

```cpp
    //  example/core_lang_spec/concept_ut.cpp 49

    // コンセプトを使用したC++20スタイル
    template <typename T>
    concept Arithmetic = std::is_arithmetic_v<T>;

    template <Arithmetic T>
    T add(T a, T b)
    {
        return a + b;
    }

    //  example/core_lang_spec/concept_ut.cpp 64

    ASSERT_EQ(add(10, 20), 30);     // int型
    ASSERT_EQ(add(1.5, 2.5), 4.0);  // double型

    auto str1 = std::string{"Hello, "};
    auto str2 = std::string{"World!"};
    // add(str1, str2);  // これを試すとコンパイルエラー
    // concept_ut.cpp:36:27: note: the expression ‘is_arithmetic_v<T> [with T =
    // std::basic_string<char, std
    // ::char_traits<char>, std::allocator<char> >]’ evaluated to ‘false’
    //    36 | concept Arithmetic = std::is_arithmetic_v<T>;
    //       |                      ~~~~~^~~~~~~~~~~~~~~~~~
    // ↑  エラーメッセージがわかりよい。テンプレートTがコンセプトfalseとなる
```

以下はテンプレートパラメータの制約にstatic_assertを使用した例である。

```cpp
    //  example/core_lang_spec/concept_ut.cpp 85

    // 制約のためにstatic_assertを使用したC++17スタイル
    template <typename FLOAT_0, typename FLOAT_1>
    bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs) noexcept
    {
        static_assert(std::is_floating_point_v<FLOAT_0>, "FLOAT_0 shoud be float or double.");
        static_assert(std::is_same_v<FLOAT_0, FLOAT_1>, "FLOAT_0 and FLOAT_1 shoud be a same type.");

        return std::abs(lhs - rhs) <= std::numeric_limits<FLOAT_0>::epsilon();
    }
```

以上の関数テンプレートをコンセプトを使用して改善した例である。

```cpp
    //  example/core_lang_spec/concept_ut.cpp 113

    // 標準コンセプト std::floating_point と std::same_as を使用
    template <std::floating_point FLOAT_0, std::same_as<FLOAT_0> FLOAT_1>
    bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs) noexcept
    {
        return std::abs(lhs - rhs) <= std::numeric_limits<FLOAT_0>::epsilon();
    }
```

フレキシブルに制約を記述するためにrequiresを使用したコード例を下記する。

```cpp
    //  example/core_lang_spec/concept_ut.cpp 138

    #if __cplusplus >= 202002L  // c++20

    // requiresを使った関数テンプレートの制約
    template <typename FLOAT_0, typename FLOAT_1>
    requires std::floating_point<FLOAT_0> && std::same_as<FLOAT_0, FLOAT_1>
    bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs) noexcept
    {
        return std::abs(lhs - rhs) <= std::numeric_limits<FLOAT_0>::epsilon();
    }

    #else  // c++17
    template <typename FLOAT_0, typename FLOAT_1>
    bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs) noexcept
    {
        static_assert(std::is_same_v<FLOAT_0, FLOAT_1>);
        return std::abs(lhs - rhs) <= std::numeric_limits<FLOAT_0>::epsilon();
    }
    #endif

```

### パラメータパック <a id="SS_19_11_4"></a>
パラメータパック(parameter pack)は、可変長テンプレート引数を表現するためにC++11で導入されたシンタックスである。
テンプレートの定義時に、任意個数のテンプレート引数または関数引数をまとめて受け取ることができる。

パラメータパックのシンタックスは以下のようなものである。

* `typename... Args` - テンプレートパラメータパック
* `Args... args` - 関数パラメータパック
* `args...` - パック展開（pack expansion）
* `sizeof...(args)` - パック内の要素数を取得

パラメータパックを使用した関数テンプレートは以下のように定義する。

```cpp
    //  example/core_lang_spec/template_ut.cpp 70

    void print(std::ostream& os) { os << std::endl; }

    template <typename HEAD, typename... TAIL>
    int print(std::ostream& os, HEAD head, TAIL... tail)
    {
        os << head;
        print(os, tail...);  // 残りの引数を再帰的に処理

        return 1 + sizeof...(tail);  // headの1個 + tailの個数 = 全パラメータ数
                                     // sizeof...(tail)はパック内の要素数
    }
```

以下の単体テストは上記の関数の使い方を示している。

```cpp
    //  example/core_lang_spec/template_ut.cpp 87

    std::stringstream os;

    auto parameter_pack_count = print(os, 1, "-", "c_str-", std::string{"std::string"});

    ASSERT_EQ("1-c_str-std::string\n", os.str());
    ASSERT_EQ(4, parameter_pack_count);
```

### 畳み込み式 <a id="SS_19_11_5"></a>
畳み式(fold expression)とは、C++17から導入された新機能であり、
可変引数テンプレートのパラメータパックに対して二項演算を累積的に行うためのものである。

畳み込み式のシンタックスの使用は下記のようなものである。
```
( pack op ... )          // (1) 単項右畳み込み
( ... op pack )          // (2) 単項左畳み込み
( pack op ... op init )  // (3) 二項右畳み込み
( init op ... op pack )  // (4) 二項左畳み込み
```

1. 単項右畳み込み
```cpp
    //  example/core_lang_spec/flold_expression_ut.cpp 9

    namespace cpp14_style {  // c++14までのスタイル
    template <typename T>
    constexpr bool all_true(T arg)
    {
        return arg;
    }
    template <typename T, typename... Args>
    constexpr bool all_true(T arg, Args... args)
    {
        return arg && all_true(args...);
    }
    }  // namespace cpp14_style

    namespace cpp17_style {  // 畳み込み式を使用したスタイル
    template <typename... Ts>
    constexpr bool all_true(Ts... args)
    {
        return (args && ...);  // 単項右畳み込み
    }
    }  // namespace cpp17_style

    static_assert(cpp14_style::all_true(true, true, true));
    static_assert(cpp17_style::all_true(true, true, true));
```
2. 単項左畳み込み
```cpp
    //  example/core_lang_spec/flold_expression_ut.cpp 36
    namespace cpp14_style {  // c++14までのスタイル
    template <typename T>
    constexpr bool any_true(T arg)
    {
        return arg;
    }
    template <typename T, typename... Args>
    constexpr bool any_true(T arg, Args... args)
    {
        return arg || any_true(args...);
    }
    }  // namespace cpp14_style

    namespace cpp17_style {  // 畳み込み式を使用したスタイル
    template <typename... Ts>
    constexpr bool any_true(Ts... args)
    {
        return (... || args);  // 単項左畳み込み
    }
    }  // namespace cpp17_style
    static_assert(cpp14_style::any_true(false, false, true));
    static_assert(cpp17_style::any_true(false, false, true));
```
3. 二項右畳み込み
```cpp
    //  example/core_lang_spec/flold_expression_ut.cpp 61

    namespace cpp14_style {  // c++14までのスタイル
    template <typename T>
    constexpr int sum(T arg)
    {
        return arg;
    }
    template <typename T, typename... Args>
    constexpr int sum(T arg, Args... args)
    {
        return arg + sum(args...);
    }

    }  // namespace cpp14_style

    namespace cpp17_style {  // 畳み込み式を使用したスタイル
    template <typename... Ts>
    constexpr int sum(Ts... args)
    {
        return (args + ... + 0);  // 二項右畳み込み (初期値: 0)
    }
    }  // namespace cpp17_style

    static_assert(cpp14_style::sum(1, 2, 3));
    static_assert(cpp17_style::sum(1, 2, 3));
```
4. 二項左畳み込み
```cpp
    //  example/core_lang_spec/flold_expression_ut.cpp 89

    namespace cpp14_style {  // c++14までのスタイル
    template <typename T>
    constexpr int product(T arg)
    {
        return arg;
    }
    template <typename T, typename... Args>
    constexpr int product(T arg, Args... args)
    {
        return arg * product(args...);
    }
    }  // namespace cpp14_style

    namespace cpp17_style {  // 畳み込み式を使用したスタイル
    template <typename... Ts>
    constexpr int product(Ts... args)
    {
        return (1 * ... * args);  // 二項左畳み込み (初期値: 1)
    }
    }  // namespace cpp17_style

    static_assert(cpp14_style::product(2, 3, 4));
    static_assert(cpp17_style::product(2, 3, 4));
```

上記したような単純な例では、畳み込み式の効果はわかりづらいため、
もっと複雑なで読解が困難な再帰構造を持ったコードを以下に示す。

```cpp
    //  example/core_lang_spec/flold_expression_ut.cpp 117
    template <typename T, typename U, typename... Us>
    struct is_same_some_of {
        static constexpr bool value{std::is_same_v<T, U> ? true : is_same_some_of<T, Us...>::value};
    };

    template <typename T, typename U>
    struct is_same_some_of<T, U> {
        static constexpr bool value{std::is_same_v<T, U>};
    };
```
```cpp
    //  example/core_lang_spec/flold_expression_ut.cpp 128

    static_assert(is_same_some_of<int, int, double, char>::value);
    static_assert(!is_same_some_of<int, double, char>::value);
    static_assert(is_same_some_of<std::string, std::string, int>::value);
```

畳み込み式を使うことで、この問題をある程度緩和したコードを下記する。

```cpp
    //  example/core_lang_spec/flold_expression_ut.cpp 140
    template <typename T, typename U, typename... Us>
    struct is_same_some_of {
        static constexpr bool value = (std::is_same_v<T, U> || ... || std::is_same_v<T, Us>);
    };
```
```cpp
    //  example/core_lang_spec/flold_expression_ut.cpp 146

    static_assert(is_same_some_of<int, int, double, char>::value);
    static_assert(!is_same_some_of<int, double, char>::value);
    static_assert(is_same_some_of<std::string, std::string, int>::value);
```

### ジェネリックラムダ <a id="SS_19_11_6"></a>
ジェネリックラムダとは、C++11のラムダ式のパラメータの型にautoを指定できるようにした機能で、
C++14で導入された。

この機能により関数の中で関数テンプレートと同等のものが定義できるようになった。

ジェネリックラムダで定義されたクロージャは、通常のラムダと同様にオブジェクトであるため、
下記のように使用することもできる便利な記法である。

```cpp
    //  example/core_lang_spec/generic_lambda_ut.cpp 4

    template <typename PUTTO>
    void f(PUTTO&& p)
    {
        p(1);
        p(2.71);
        p("str");
    }

    TEST(Template, generic_lambda)
    {
        std::ostringstream oss;

        f([&oss](auto const& elem) { oss << elem << std::endl; });

        ASSERT_EQ("1\n2.71\nstr\n", oss.str());
    }
```

なお、上記のジェネリックラムダは下記クラスのインスタンスの動きと同じである。

```cpp
    //  example/core_lang_spec/generic_lambda_ut.cpp 23

    class Closure {
    public:
        Closure(std::ostream& os) : os_(os) {}

        template <typename T>
        void operator()(T&& t)
        {
            os_ << t << std::endl;
        }

    private:
        std::ostream& os_;
    };

    TEST(Template, generic_lambda_like)
    {
        std::ostringstream oss;

        Closure closure(oss);
        f(closure);

        ASSERT_EQ("1\n2.71\nstr\n", oss.str());
    }
```

### クラステンプレートのテンプレート引数の型推論 <a id="SS_19_11_7"></a>
C++17から、
「コンストラクタに渡される値によって、クラステンプレートのテンプレート引数を推論する」
機能が導入された。

この機能がないC++14までは以下のように記述する必要があった。

```cpp
    //  example/core_lang_spec/template_ut.cpp 14

    auto a = std::vector<int>{1, 2, 3};

    static_assert(std::is_same_v<decltype(a), std::vector<int>>);
```

これに対して、この機能により、以下のようにシンプルに記述できるようになった。

```cpp
    //  example/core_lang_spec/template_ut.cpp 25

    auto a = std::vector{1, 2, 3};

    static_assert(std::is_same_v<decltype(a), std::vector<int>>);  // テンプレート引数がintと推論
```

### CTAD(Class Template Argument Deduction) <a id="SS_19_11_8"></a>
CTAD（Class Template Argument Deduction、クラステンプレート実引数推論）は、C++17で導入された機能である。
この機能により、クラステンプレートのインスタンス化時にテンプレート引数を明示的に指定せず、
コンストラクタの引数から自動的に型を推論できるようになる。
クラステンプレートの型推論が不十分な場合、[テンプレートの型推論ガイド](core_lang_spec.md#SS_19_11_9)を追加することにより、
型推論を強化することができる。


### テンプレートの型推論ガイド <a id="SS_19_11_9"></a>
[CTAD(Class Template Argument Deduction)](core_lang_spec.md#SS_19_11_8)による型推論をカスタマイズするために、型推論ガイドを定義できる。
特にコンストラクタがテンプレートである場合など、暗黙の型推論では不十分な場合に有用である。

```cpp
    //  example/core_lang_spec/deduction_guide_ut.cpp 8

    template <typename T>  // Tが整数型の場合、暗黙の型変換を許可
    struct S {
        // T が整数型でない場合に有効なコンストラクタ
        template <typename U = T, std::enable_if_t<!std::is_integral_v<U>>* = nullptr>
        explicit S(U x) : value{x}
        {
        }

        // T が整数型の場合に有効な非explicitコンストラクタ
        template <typename U = T, std::enable_if_t<std::is_integral_v<U>>* = nullptr>
        S(U x) : value{x}
        {
        }

        T value;
    };

```

上記のクラステンプレートは、型推論ガイドがない場合、コンストラクタがテンプレートであるため、
[CTAD(Class Template Argument Deduction)](core_lang_spec.md#SS_19_11_8)による型推論ができない。
そのため、以下のように明示的にテンプレート引数を指定する必要がある。

```cpp
    //  example/core_lang_spec/deduction_guide_ut.cpp 31

    // 型推論ガイドがないため、下記はコンパイルできない
    // S s1{42};   // エラー: テンプレート引数を推論できない
    // S s2{1.0};  // エラー: テンプレート引数を推論できない

    // 上記の問題を回避するためには型推論ガイドを定義するか、テンプレート引数を指定しなければならない
    S<int>    s1{42};   // 明示的にテンプレート引数を指定
    S<double> s2{1.0};  // 明示的にテンプレート引数を指定
```

以上に示したクラステンプレートに以下の型推論ガイドを追加することにより、
テンプレート引数を型推論できるようになる。

```cpp
    //  example/core_lang_spec/deduction_guide_ut.cpp 44

    template <typename T>
    S(T) -> S<T>;
```
```cpp
    //  example/core_lang_spec/deduction_guide_ut.cpp 52

    S s1{42};   // 推論ガイドの効果
    S s2{1.0};  // 推論ガイドの効果
    S s3 = 42;  // OK: S<int>のコンストラクタが非explicitのため、暗黙の変換が可能
    // S    s4 = 1.0;  // S<double>のコンストラクタがexplicitであるため、暗黙の変換不可
```

多くの場合、コンパイラは暗黙の型推論ガイドを生成するため、明示的に型推論ガイドを書く必要はない。
明示的な型推論ガイドが必要なのは、 上記の例のようにコンストラクタがテンプレートである場合や、
特殊な推論ルールが必要な場合である。

### 変数テンプレート <a id="SS_19_11_10"></a>
変数テンプレートとは、下記のコード示したような機能である。

```cpp
    //  example/core_lang_spec/template_ut.cpp 33

    template <typename T>
    struct is_void {
        static constexpr bool value = false;
    };

    template <>
    struct is_void<void> {
        static constexpr bool value = true;
    };

    static_assert(is_void<void>::value);
    static_assert(!is_void<int>::value);
    // 以上はC++14以前のスタイル

    // 以下はC++17から導入された
    template <typename T>
    constexpr bool is_void_v = is_void<T>::value;

    static_assert(is_void_v<void>);
    static_assert(!is_void_v<int>);
```

なお、変数テンプレートはconstexprと定義されるが、
「定数テンプレート」ではなく変数テンプレートである。


### エイリアステンプレート <a id="SS_19_11_11"></a>
エイリアステンプレート(alias templates)とはC++11から導入され、
下記のコード例で示したようにテンプレートによって型の別名を定義する機能である。

```cpp
    //  example/core_lang_spec/template_ut.cpp 57

    using IntVector = std::vector<int>;  // std::vector<int> のエイリアスを定義

    template <typename T>  //エイリアステンプレートを定義
    using Vec = std::vector<T>;

    static_assert(std::is_same_v<IntVector, Vec<int>>);  // Vec<int> == std::vector<int>
```

### constexpr if文 <a id="SS_19_11_12"></a>
C++17で導入された[constexpr if文](https://cpprefjp.github.io/lang/cpp17/if_constexpr.html)とは、
文を条件付きコンパイルすることができるようにするための制御構文である。

まずは、この構文を使用しない例を示す。

```cpp
    //  example/core_lang_spec/constexpr_if_ut.cpp 9

    // 配列のサイズ
    template <typename T>
    auto Length(T const&) -> std::enable_if_t<std::is_array_v<T>, size_t>
    {
        return std::extent_v<T>;
    }

    // コンテナのサイズ
    template <typename T>
    auto Length(T const& t) -> decltype(t.size())
    {
        return t.size();
    }

    // その他のサイズ
    size_t Length(...) { return 0; }
```
```cpp
    //  example/core_lang_spec/constexpr_if_ut.cpp 31

    uint32_t a[5];
    auto     v = std::vector{0, 1, 2};
    struct SizeTest {
    } t;

    ASSERT_EQ(5, Length(a));
    ASSERT_EQ(3, Length(v));
    ASSERT_EQ(0, Length(t));

    // C++17で、Lengthと同様の機能の関数テンプレートがSTLに追加された
    ASSERT_EQ(std::size(a), Length(a));
    ASSERT_EQ(std::size(v), Length(v));
```

このような場合、[SFINAE](core_lang_spec.md#SS_19_11_1)によるオーバーロードが必須であったが、
この文を使用することで、下記のようにオーバーロードを使用せずに記述できるため、
条件分岐の可読性の向上が見込める。

```cpp
    //  example/core_lang_spec/constexpr_if_ut.cpp 52

    struct helper {
        template <typename T>
        auto operator()(T const& t) -> decltype(t.size());
    };

    template <typename T>
    size_t Length(T const& t)
    {
        if constexpr (std::is_array_v<T>) {  // Tが配列の場合
            // Tが配列でない場合、他の条件のブロックはコンパイル対象外
            return std::extent_v<T>;
        }
        else if constexpr (std::is_invocable_v<helper, T>) {  // T::Lengthが呼び出せる場合
            // T::Lengthが呼び出せない場合、他の条件のブロックはコンパイル対象外
            return t.size();
        }
        else {  // それ以外
            // Tが配列でなく且つ、T::Lengthが呼び出ない場合、他の条件のブロックはコンパイル対象外
            return 0;
        }
    }
```

この構文は[パラメータパック](core_lang_spec.md#SS_19_11_4)の展開においても有用な場合がある。

```cpp
    //  example/core_lang_spec/constexpr_if_ut.cpp 93

    // テンプレートパラメータで与えられた型のsizeofの値が最も大きな値を返す。
    template <typename HEAD>
    constexpr size_t MaxSizeof()
    {
        return sizeof(HEAD);
    }

    template <typename HEAD, typename T, typename... TAILS>
    constexpr size_t MaxSizeof()
    {
        return std::max(sizeof(HEAD), MaxSizeof<T, TAILS...>());
    }
```
```cpp
    //  example/core_lang_spec/constexpr_if_ut.cpp 111

    static_assert(4 == (MaxSizeof<int8_t, int16_t, int32_t>()));
    static_assert(4 == (MaxSizeof<int32_t, int16_t, int8_t>()));
    static_assert(sizeof(std::string) == MaxSizeof<int32_t, int16_t, int8_t, std::string>());
```

C++14までの構文を使用する場合、
上記のようなオーバーロードとリカーシブコールの組み合わせが必要であったが、
constexpr ifを使用することで、やや単純に記述できる。

```cpp
    //  example/core_lang_spec/constexpr_if_ut.cpp 123

    // テンプレートパラメータで与えられた型のsizeofの値が最も大きな値を返す。
    template <typename HEAD, typename... TAILS>
    constexpr size_t MaxSizeof()
    {
        if constexpr (sizeof...(TAILS) == 0) {  // TAILSが存在しない場合
            return sizeof(HEAD);
        }
        else {
            return std::max(sizeof(HEAD), MaxSizeof<TAILS...>());
        }
    }
```

### autoパラメータによる関数テンプレートの簡易定義 <a id="SS_19_11_13"></a>
この機能は、C++20から導入された。
下記のコードで示すように簡易的に関数テンプレートを定義するための機能である。

```cpp
    //  example/core_lang_spec20/abbreviated_func_template_ut.cpp 11

    auto add(auto lhs, auto rhs)  // c++20で導入された記法
    {
        return lhs + rhs;
    }
```
```cpp
    //  example/core_lang_spec20/abbreviated_func_template_ut.cpp 21

    ASSERT_EQ(add(1, 2), 3);

    ASSERT_DOUBLE_EQ(add(1.5, 2.5), 4.0);

    using namespace std::literals::string_literals;

    ASSERT_EQ(add("hello"s, "world"s), "helloworld"s);
```

### auto <a id="SS_19_11_14"></a>
autoは、C++11で導入された型推論キーワードである。変数宣言時に明示的な型指定を省略し、
初期化式からコンパイラが型を自動的に推定する。 これにより、複雑な型やテンプレート使用時の記述が簡潔になり、
可読性と保守性が向上する。
コード例については、[decltype](core_lang_spec.md#SS_19_11_15)を参照せよ。

### decltype <a id="SS_19_11_15"></a>
decltypeはオペランドに[expression](core_lang_spec.md#SS_19_7_1)を取り、その型を算出する機能である。
下記のコードにあるようなautoの機能との微妙な差に気を付ける必要がある。

```cpp
    //  example/core_lang_spec/decltype_ut.cpp 13

    int32_t  x{3};
    int32_t& r{x};

    auto        a = r;  // aの型はint32_t
    decltype(r) b = r;  // bの型はint32_t&

    // std::is_sameはオペランドの型が同じか否かを返すメタ関数
    static_assert(std::is_same_v<decltype(a), int>);
    static_assert(std::is_same_v<decltype(b), int&>);
```

decltypeは、テンプレートプログラミングに多用されるが、
クロージャ型(「[ラムダ式](core_lang_spec.md#SS_19_10_3)」参照)
のような記述不可能な型をオブジェクトから算出できるため、
下記例のような場合にも有用である。

```cpp
    //  example/core_lang_spec/decltype_ut.cpp 28

    //  本来ならばA::dataは、
    //      * A::Aでメモリ割り当て
    //      * A::~Aでメモリ解放
    //  すべきだが、何らかの理由でそれが出来ないとする
    struct A {
        size_t   len;
        uint8_t* data;
    };

    void do_something(size_t len)
    {
        auto deallocate = [](A* p) {
            delete[](p->data);
            delete p;
        };

        auto a_ptr = std::unique_ptr<A, decltype(deallocate)>{new A, deallocate};

        a_ptr->len  = len;
        a_ptr->data = new uint8_t[10];

        // ...
        // do something for a_ptr
        // ...

        // a_ptrによるメモリの自動解放
    }
```

### decltype(auto) <a id="SS_19_11_16"></a>
decltype(auto)はC++14から導入されたdecltypeの類似機能である。

auto、decltype、decltype(auto)では、以下に示す通りリファレンスの扱いが異なることに注意する必要がある。

```cpp
    //  example/core_lang_spec/decltype_ut.cpp 63

    int32_t  x{3};
    int32_t& r{x};

    auto           a = r;  // aの型はint32_t
    decltype(r)    b = r;  // bの型はint32_t&
    decltype(auto) c = r;  // cの型はint32_t&   C++14からサポート
                           // decltype(auto)は、decltypeに右辺の式を与えるための構文

    // std::is_sameはオペランドの型が同じか否かを返すメタ関数
    static_assert(std::is_same_v<decltype(a), int>);
    static_assert(std::is_same_v<decltype(b), int&>);
    static_assert(std::is_same_v<decltype(c), int&>);
```

### 戻り値型を後置する関数宣言 <a id="SS_19_11_17"></a>
関数の戻り値型後置構文は戻り値型をプレースホルダ(auto)にして、
実際の型を->で示して型推論させるシンタックスを指す。実際には関数テンプレートで使用されることが多い。
コード例を以下に示す。

```cpp
    //  example/core_lang_spec/decltype_ut.cpp 82

    template <typename T, typename U>
    auto add(T a, U b) -> decltype(a + b)
    {
        return a + b;
    }

    static_assert(std::is_same_v<decltype(add(1, 2)), int>);         // addの戻り値型はintに型推論
    static_assert(std::is_same_v<decltype(add(1u, 2u)), uint32_t>);  // addの戻り値型はintに型推論
    static_assert(std::is_same_v<decltype(add(std::string{"str"}, "2")),
                                 std::string>);  // addの戻り値型はstd::stringに型推論
```

この構文をC++11から導入された理由は以下のコードを見れば明らかだろう。

```cpp
    //  example/core_lang_spec/decltype_ut.cpp 97

    template <typename T, typename U>  // 戻り値型を後置する関数宣言
    decltype(std::declval<T>() + std::declval<T>()) add(T a, U b)
    {
        return a + b;
    }

    static_assert(std::is_same_v<decltype(add(1, 2)), int>);         // addの戻り値型はintに型推論
    static_assert(std::is_same_v<decltype(add(1u, 2u)), uint32_t>);  // addの戻り値型はintに型推論
    static_assert(std::is_same_v<decltype(add(std::string{"str"}, "2")),
                                 std::string>);  // addの戻り値型はstd::stringに型推論
```

### 関数の戻り値型auto <a id="SS_19_11_18"></a>
C++14から導入された機能で、関数の戻り値の型をautoキーワードで宣言することで、
コンパイラがreturn文から自動的に型を推論してくれる機能である。
これにより、複雑な型の戻り値を持つ関数でも、より簡潔に記述できるようになる
(「[autoパラメータによる関数テンプレートの簡易定義](core_lang_spec.md#SS_19_11_13)」を参照)。

```cpp
    //  example/core_lang_spec/decltype_ut.cpp 114

    // 戻り値型autoが使えないと下記のような宣言が必要
    // std::vector<std::string> split(std::string_view str, char delimiter)
    auto split(std::string_view str, char delimiter)
    {
        std::vector<std::string> result;
        std::string              token;

        for (char ch : str) {
            if (ch == delimiter) {
                if (!token.empty()) {
                    result.emplace_back(std::move(token));
                }
            }
            else {
                token += ch;
            }
        }

        if (!token.empty()) {
            result.emplace_back(std::move(token));
        }

        return result;
    }
```
```cpp
    //  example/core_lang_spec/decltype_ut.cpp 144

    auto result = split("hello,world", ',');

    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0], "hello");
    ASSERT_EQ(result[1], "world");
```

### 後置戻り値型auto <a id="SS_19_11_19"></a>
C++14から導入された[関数の戻り値型auto](core_lang_spec.md#SS_19_11_18)と似た、
関数の戻り値の型を関数本体の後に-> autoと書くことでができる機能である。
autoプレースホルダーとし、そのプレースホルダーを修飾することで、戻り値型の推論を補助できる。

```cpp
    //  example/core_lang_spec/decltype_ut.cpp 154

    int16_t gvalue = 1;

    auto getValue(int16_t a) -> auto& { return gvalue += a; }
```
```cpp
    //  example/core_lang_spec/decltype_ut.cpp 163

    auto           ret1 = getValue(10);
    decltype(auto) ret2 = getValue(0);

    ASSERT_EQ(ret1, 11);
    ASSERT_EQ(ret2, 11);

    ASSERT_EQ(gvalue, 11);
    ret1 += 1;
    ASSERT_EQ(gvalue, 11);

    ret2 += 1;
    ASSERT_EQ(gvalue, 12);
```

## name lookupと継承構造 <a id="SS_19_12"></a>
ここではname lookupとそれに影響を与える名前空間について解説する。

### ルックアップ <a id="SS_19_12_1"></a>
このドキュメントでのルックアップとは[name lookup](core_lang_spec.md#SS_19_12_2)を指す。

### name lookup <a id="SS_19_12_2"></a>
[name lookup](https://en.cppreference.com/w/cpp/language/lookup)
とはソースコードで名前が検出された時に、その名前をその宣言と関連付けることである。
以下、name lookupの例を上げる。

下記のようなコードがあった場合、

```cpp
    //  example/core_lang_spec/name_lookup_ut.cpp 5

    namespace NS_LU {
    int f() noexcept { return 0; }
    }  // namespace NS_LU
```

以下のコードでの関数呼び出しf()のname lookupは、


```cpp
    //  example/core_lang_spec/name_lookup_ut.cpp 29

    NS_LU::f();
```

1. NS_LUをその前方で宣言された名前空間と関連付けする
2. f()呼び出しをその前方の名前空間NS_LUで宣言された関数fと関連付ける

という手順で行われる。

下記のようなコードがあった場合、

```cpp
    //  example/core_lang_spec/name_lookup_ut.cpp 11

    namespace NS_LU {
    bool g(int i) noexcept { return i < 0; }

    char g(std::string_view str) noexcept { return str[0]; }

    template <typename T, size_t N>
    size_t g(T const (&)[N]) noexcept
    {
        return N;
    }
```

以下のコードでの関数呼び出しg()のname lookupは、


```cpp
    //  example/core_lang_spec/name_lookup_ut.cpp 37
    int a[3]{1, 2, 3};
    NS_LU::g(a);
```

1. NS_LUをその前方で宣言された名前空間と関連付けする
2. 名前空間NS_LU内で宣言された複数のgを見つける
3. g()呼び出しを、
   すでに見つけたgの中からベストマッチしたg(T const (&)[N])と関連付ける

という手順で行われる。

下記記のようなコードがあった場合、

```cpp
    //  example/core_lang_spec/name_lookup_ut.cpp 44

    // グローバル名前空間
    std::string ToString(int i) { return std::to_string(i) + " in Global"; }

    namespace NS_LU {
    struct X {
        int i;
    };

    std::string ToString(X const& x) { return std::to_string(x.i) + " in NS_LU"; }
    }  // namespace NS_LU

    namespace NS2 {
    std::string ToString(NS_LU::X const& x) { return std::to_string(x.i) + " in NS2"; }
    }  // namespace NS2
```

以下のコードでの関数呼び出しToString()のname lookupは、

```cpp
    //  example/core_lang_spec/name_lookup_ut.cpp 65

    auto x = NS_LU::X{1};

    ASSERT_EQ("1 in NS_LU", ToString(x));
```

1. ToString()呼び出しの引数xの型Xが名前空間NS_LUで定義されているため、
   ToStringを探索する名前空間にNS_LUを組み入れる(「[関連名前空間](core_lang_spec.md#SS_19_12_6)」参照)
2. ToString()呼び出しより前方で宣言されたグローバル名前空間とNS_LUの中から、
   複数のToStringの定義を見つける
3. ToString()呼び出しを、
   すでに見つけたToStringの中からベストマッチしたNS_LU::ToStringと関連付ける

という手順で行われる。


### two phase name lookup <a id="SS_19_12_3"></a>
[two phase name lookup](https://en.cppreference.com/w/cpp/language/two-phase_lookup)
とはテンプレートをインスタンス化するときに使用される、下記のような2段階でのname lookupである。

1. テンプレート定義内でname lookupを行う(通常のname lookupと同じ)。
   この時、テンプレートパラメータに依存した名前
   ([dependent_name](https://en.cppreference.com/w/cpp/language/dependent_name))は
   name lookupの対象外となる(name lookupの対象が確定しないため)。
2. 1の後、テンプレートパラメータを展開した関数内で、
   [関連名前空間](core_lang_spec.md#SS_19_12_6)の宣言も含めたname lookupを行う。

以下の議論では、

* 上記1のname lookupを1st name lookup
* 上記2のname lookupを2nd name lookup

と呼ぶことにする。

下記のようなコードがあった場合、

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 5

    namespace NS_TPLU {
    struct X {
        int i;
    };
    }  // namespace NS_TPLU

    // グローバル名前空間
    inline std::string ToType(NS_TPLU::X const&) { return "X in global"; }
    inline std::string ToType(int const&) { return "int in global"; }

    // 再びNS_TPLU
    namespace NS_TPLU {

    std::string Header(long) { return "type:"; }  //  下記にもオーバーロードあり

    template <typename T>
    std::string ToType(T const&)  //  下記にもオーバーロードあり
    {
        return "unknown";
    }

    template <typename T>
    std::string TypeName(T const& t)  // オーバーロードなし
    {
        return Header(int{}) + ToType(t);
    }

    std::string Header(int) { return "TYPE:"; }  // 上記にもオーバーロードあり

    std::string ToType(X const&) { return "X"; }      // 上記にもオーバーロードあり
    std::string ToType(int const&) { return "int"; }  // 上記にもオーバーロードあり
    }  // namespace NS_TPLU
```

以下のコードでのTypeNameのインスタンス化に伴うname lookupは、

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 44

    auto x = NS_TPLU::X{1};

    ASSERT_EQ("type:X", TypeName(x));
```

1. TypeName()呼び出しの引数xの型Xが名前空間NS_TPLUで宣言されているため、
   NS_TPLUをTypeNameを探索する[関連名前空間](core_lang_spec.md#SS_19_12_6)にする。
2. TypeName()呼び出しより前方で宣言されたグローバル名前空間とNS_TPLUの中からTypeNameを見つける。
3. TypeNameは関数テンプレートであるためtwo phase lookupが以下のように行われる。
    1. TypeName内でのHeader(int{})の呼び出しは、1st name lookupにより、
       Header(long)の宣言と関連付けられる。
       Header(int)はHeader(long)よりもマッチ率が高い、
       TypeNameの定義より後方で宣言されているため、name lookupの対象外となる。
    2. TypeName内でのToType(t)の呼び出しに対しては、2nd name lookupが行われる。
       このためTypeName定義より前方で宣言されたグローバル名前空間と、
       tの型がNS_TPLU::Xであるため[関連名前空間](core_lang_spec.md#SS_19_12_6)となったNS_TPLUがname lookupの対象となるが、
       グローバル名前空間内のToTypeは、
       NS_TPLU内でTypeNameより前に宣言されたtemplate<> ToTypeによって[name-hiding](core_lang_spec.md#SS_19_12_9)が起こり、
       TypeNameからは非可視となるためname lookupの対象から外れる。
       このため、ToType(t)の呼び出しは、NS_TPLU::ToType(X const&)の宣言と関連付けられる。

という手順で行われる。

上と同じ定義、宣言がある場合の以下のコードでのTypeNameのインスタンス化に伴うname lookupは、

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 50

    ASSERT_EQ("type:unknown", NS_TPLU::TypeName(int{}));
```

1. NS_TPLUを名前空間と関連付けする
   (引数の型がintなのでNS_TPLUは[関連名前空間](core_lang_spec.md#SS_19_12_6)とならず、NS_TPLUを明示する必要がある)。
2. TypeName()呼び出しより前方で宣言されたNS_TPLUの中からTypeNameを見つける。
3. TypeNameは関数テンプレートであるためtwo phase lookupが以下のように行われる。
    1. TypeName内でのHeader(int{})の呼び出しは、1st name lookupにより、
       前例と同じ理由で、Header(long)の宣言と関連付けられる。
    2. TypeName内でのToType(t)の呼び出しに対しては、2nd name lookupが行われる。
       tの型がintであるためNS_TPLUは[関連名前空間](core_lang_spec.md#SS_19_12_6)とならず、通常のname lookupと同様に
       ToType(t)の呼び出し前方のグローバル名前空間とNS_TPLUがname lookupの対象になるが、
       グローバル名前空間内のToTypeは、
       NS_TPLU内でTypeNameより前に宣言されたtemplate<> ToTypeによって[name-hiding](core_lang_spec.md#SS_19_12_9)が起こり、
       TypeNameからは非可視となるためname lookupの対象から外れる。
       また、ToType(int const&)は、TypeNameの定義より後方で宣言されているため、
       name lookupの対象外となり、
       その結果、ToType(t)の呼び出しは、NS_TPLU内のtemplate<> ToTypeの宣言と関連付けられる。

という手順で行われる。

以上の理由から、先に示した例でのToTypeの戻り値は"X"となり、
後に示した例でのToTypeの戻り値は"unknown"となる。
これはtwo phase lookupの結果であり、
two phase lookupが実装されていないコンパイラ(こういったコンパイラは存在する)では、
結果が異なるため注意が必要である
(本ドキュメントではこのような問題をできる限り避けるために、
サンプルコードを[g++](cpp_idioms.md#SS_21_13_1)と[clang++](cpp_idioms.md#SS_21_13_2)でコンパイルしている)。

以下に、two phase lookupにまつわるさらに驚くべきコード例を紹介する。
上と同じ定義、宣言がある場合の以下のコードの動作を考える。

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 54

    ASSERT_EQ("type:long", NS_TPLU::TypeName(long{}));
```

NS_TPLU::TypeName(int{})のintをlongにしただけなので、この単体テストはパスしないが、
この単体テストコードの後(実際にはこのファイルのコンパイル単位の中のNS_TPLU内で、
且つtemplate<> ToTypeの宣言の後方であればどこでもよい)
に以下のコードを追加するとパスしてしまう。

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 61

    namespace NS_TPLU {
    template <>
    std::string ToType<long>(long const&)
    {
        return "long";
    }
    }  // namespace NS_TPLU
```

この理由は、関数テンプレート内での2nd name lookupで選択された名前が関数テンプレートであった場合、
その特殊化の検索範囲はコンパイル単位内になることがあるからである
([template_specialization](https://en.cppreference.com/w/cpp/language/template_specialization)
によるとこの動作は未定義のようだが、
[g++](cpp_idioms.md#SS_21_13_1)/[clang++](cpp_idioms.md#SS_21_13_2)両方ともこのコードを警告なしでコンパイルする)。

TypeName(long{})内でのtwo phase name lookupは、TypeName(int{})とほぼ同様に進み、
template<> ToTypeの宣言を探し出すが、
さらに前述したようにこのコンパイル単位のNS_TPLU内からその特殊化も探し出す。
その結果、ToType(t)の呼び出しは、NS_TPLU内のtemplate<> ToType\<long>の定義と関連付けられる。

以上の議論からわかる通り、関数テンプレートとその特殊化の組み合わせは、
そのインスタンス化箇所(この場合単体テストコード内)の後方から、
name lookupでバインドされる関数を変更することができるため、
極めて分かりづらいコードを生み出す。ここから、

* 関数テンプレートとその特殊化はソースコード上なるべく近い位置で宣言するべきである
* STL関数テンプレートの特殊化は行うべきではない

という教訓が得られる。

なお、関数とその関数オーバーロードのname lookupの対象は、呼び出し箇所前方の宣言のみであるため、
関数テンプレートToType(T const& t)の代わりに、関数ToType(...)を使うことで、
上記問題は回避可能である。

次に示す例は、一見2nd name lookupで関連付けされるように見える関数ToType(NS_TPLU2::Y const&)が、
実際には関連付けされないコードである。

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 71

    namespace NS_TPLU2 {
    struct Y {
        int i;
    };
    }  // namespace NS_TPLU2
```
```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 79

    // global名前空間
    template <typename T>
    std::string ToType(T const&)
    {
        return "unknown";
    }

    template <typename T>
    std::string TypeName(T const& t)
    {
        return "type:" + ToType(t);
    }

    std::string ToType(NS_TPLU2::Y const&) { return "Y"; }
```

これは先に示したNS_TPLU::Xの例と極めて似ている。本質的な違いは、
TypeNameやToTypeがグローバル名前空間で宣言されていることのみである。
だが、下記の単体テストで示す通り、
TypeName内でのname lookupで関数オーバーライドToType(NS_TPLU2::Y const&)が選択されないのである。

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 100

    auto y = NS_TPLU2::Y{1};

    // ASSERT_EQ("type:Y", TypeName(y));
    ASSERT_EQ("type:unknown", TypeName(y));  // ToType(NS_TPLU2::Y const&)は使われない
```

ここまでの現象を正確に理解するには、
「two phase lookupの対象となる宣言」を下記のように、より厳密に認識する必要がある。

* TypeNameの中で行われる1st name lookupの対象となる宣言は下記の積集合である。
    * TypeNameと同じ名前空間内かグローバル名前空間内の宣言
    * TypeName定義位置より前方の宣言

* TypeNameの中で行われる2nd name lookupの対象となる宣言は下記の和集合である。
    * 1st name lookupで使われた宣言
    * TypeName呼び出しより前方にある[関連名前空間](core_lang_spec.md#SS_19_12_6)内の宣言

この認識に基づくNS_TPLU2::Yに対するグローバルなTypeName内でのtwo phase name lookupは、

1. TypeName内に1st name lookupの対象がないため何もしない。
2. TypeName内の2nd name lookupに使用される[関連名前空間](core_lang_spec.md#SS_19_12_6)NS_TPLU2は、
   ToType(NS_TPLU2::Y const&)の宣言を含まないため、この宣言は2nd name lookupの対象とならない。
   その結果、ToType(t)の呼び出しは関数テンプレートToType(T const&)と関連付けられる。

という手順で行われる。

以上が、TypeNameからToType(NS_TPLU2::Y const&)が使われない理由である。

ここまでで示したようにtwo phase name lookupは理解しがたく、
理解したとしてもその使いこなしはさらに難しい。

次のコードは、この難解さに翻弄されるのが現場のプログラマのみではないことを示す。

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 71

    namespace NS_TPLU2 {
    struct Y {
        int i;
    };
    }  // namespace NS_TPLU2
```
```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 110

    // global名前空間
    template <typename T>
    int operator+(T const&, int i)
    {
        return i;
    }

    template <typename T>
    int TypeNum(T const& t)
    {
        return t + 0;
    }

    int operator+(NS_TPLU2::Y const& y, int i) { return y.i + i; }
```

上記の宣言、定義があった場合、operator+の単体テストは以下のようになる。

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 132

    auto y = NS_TPLU2::Y{1};

    ASSERT_EQ(1, y + 0);  // 2つ目のoperator+が選択される
```

このテストは当然パスするが、次はどうだろう？

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 142

    auto y = NS_TPLU2::Y{1};

    ASSERT_EQ(1, TypeNum(y));  // g++ではoperator+(NS_TPLU2::Y const&, int i)がname lookupされる
```

これまでのtwo phase name lookupの説明では、
operator+(NS_TPLU2::Y const& y, int i)はTypeNum内でのname lookupの対象にはならないため、
このテストはエラーとならなければならないが、[g++](cpp_idioms.md#SS_21_13_1)ではパスしてしまう。
2nd name lookupのロジックにバグがあるようである。

有難いことに、[clang++](cpp_idioms.md#SS_21_13_2)では仕様通りこのテストはエラーとなり、
当然ながら以下のテストはパスする(つまり、g++ではエラーする)。

```cpp
    //  example/core_lang_spec/two_phase_name_lookup_ut.cpp 151

    auto y = NS_TPLU2::Y{1};

    ASSERT_EQ(0, TypeNum(y));  // clang++ではoperator+(T const&, int i)がname lookupされる
```

なお、TypeNum内のコードである

```cpp
    return t + 0;
```

を下記のように変更することで

```cpp
    return operator+(t, 0);
```

g++のname lookupはclang++と同じように動作するため、
記法に違和感があるものの、この方法はg++のバグのワークアランドとして使用できる。

また、operator+(NS_TPLU2::Y const& y, int i)をNS_TPLU2で宣言することで、
g++ではパスしたテストをclang++でもパスさせられるようになる(これは正しい動作)。
これにより、型とその2項演算子オーバーロードは同じ名前空間で宣言するべきである、
という教訓が得られる。

以上で見てきたようにtwo phase name lookupは、現場プログラマのみではなく、
コンパイラを開発するプログラマをも混乱させるほど難解ではあるが、
STLを含むテンプレートメタプログラミングを支える重要な機能であるため、
C++プログラマには、最低でもこれを理解し、出来れば使いこなせるようになってほしい。


### 実引数依存探索 <a id="SS_19_12_4"></a>
実引数依存探索とは、argument-dependent lookupの和訳語であり、
通常はその略語である[ADL](core_lang_spec.md#SS_19_12_5)と呼ばれる。

### ADL <a id="SS_19_12_5"></a>
ADLとは、関数の実引数の型が宣言されている名前空間(これを[関連名前空間](core_lang_spec.md#SS_19_12_6)と呼ぶ)内の宣言が、
その関数の[name lookup](core_lang_spec.md#SS_19_12_2)の対象になることである。

下記のようなコードがあった場合、

```cpp
    //  example/core_lang_spec/name_lookup_adl_ut.cpp 5
    namespace NS_ADL {
    struct A {
        int i;
    };

    std::string ToString(A const& a) { return std::string{"A:"} + std::to_string(a.i); }
    }  // namespace NS_ADL
```

以下のコードでのToStringの呼び出しに対するのname lookupは、

```cpp
    //  example/core_lang_spec/name_lookup_adl_ut.cpp 18

    auto a = NS_ADL::A{0};

    ASSERT_EQ("A:0", ToString(a));  // ADLの効果により、ToStringはNS_ADLを指定しなくても見つかる
```

* ToStringの呼び出しより前方で行われているグローバル名前空間内の宣言
* ToStringの呼び出しより前方で行われているNS_ADL内の宣言

の両方を対象として行われる。
NS_ADL内の宣言がToStringの呼び出しに対するのname lookupの対象になる理由は、
ToStringの呼び出しに使われている実引数aの型AがNS_ADLで宣言されているからである。
すでに述べたようにこれをADLと呼び、この場合のNS_ADLを[関連名前空間](core_lang_spec.md#SS_19_12_6)と呼ぶ。

ADLは思わぬname lookupによるバグを誘発することもあるが、
下記コードを見れば明らかなように、また、
多くのプログラマはそれと気づかずに使っていることからもわかる通り、
コードをより自然に、より簡潔に記述するための重要な機能となっている。

```cpp
    //  example/core_lang_spec/name_lookup_adl_ut.cpp 28

    // 下記operator <<は、std::operator<<(ostream&, string const&)であり、
    // namespace stdで定義されている。

    // ADLがあるため、operator <<は名前空間修飾無しで呼び出せる。
    std::cout << std::string{__func__};

    // ADLが無いと下記のような呼び出しになる。
    std::operator<<(std::cout, std::string{__func__});
```

### 関連名前空間 <a id="SS_19_12_6"></a>
関連名前空間(associated namespace)とは、
[ADL](core_lang_spec.md#SS_19_12_5)(実引数依存探索)によってname lookupの対象になった宣言を含む名前空間のことである。


### 修飾付き関数呼び出し <a id="SS_19_12_7"></a>
修飾付き関数呼び出し(Qualified Call)は、
C++で関数やメンバ関数を明示的にスコープやクラス名で修飾して呼び出す方法である。
名前の曖昧性を回避し、特定の関数やクラスメンバを明確に選択する際に利用される。
これにより、意図しない[name lookup](core_lang_spec.md#SS_19_12_2)を回避することができるため、可読性と安全性が向上する。
一方で、[ADL](core_lang_spec.md#SS_19_12_5)が働かなくなるため、フレキシブルな[name lookup](core_lang_spec.md#SS_19_12_2)ができなくなる。

```cpp
    //  example/core_lang_spec/etc_ut.cpp 40

    extern void func();  // グローバル名前空間での宣言

    struct Base {
        void func() const noexcept {}
    };

    A::func();  // 名前空間名による修飾

    struct Derived : Base {
        // void        func() { func(); /* funcの無限リカーシブコール */ }
        void        func() { Base::func(); /* クラス名での修飾 */ }
        void        func(int) { ::func(); /* グローバル修飾 */ }
        void        func(Base) { this->func(); /* thisによる修飾 */ }
        static void func(std::string) {}
    };

    Base b;
    b.func();        // 通常の関数呼び出し
    b.Base::func();  // クラス名での修飾による関数呼び出し

    Derived d;
    Derived::func("str");  // クラス名での修飾による関数呼び出し
    d.func("str");         // 通常の関数呼び出し
```

### hidden-friend関数 <a id="SS_19_12_8"></a>
hidden-friend関数(隠れたフレンド関数、あるいは単にhidden-friend)とは、

* クラスの内部で定義された、
* 名前空間スコープでの通常の[name lookup](core_lang_spec.md#SS_19_12_2)できず、[ADL](core_lang_spec.md#SS_19_12_5)のみでname lookupできる

friend関数のことを指す。このような性質から、non-namespace-visible friend関数と呼ばれることもある。

これにより、意図的に外部からのアクセスを制限し、
必要な場合にのみ利用されることを保証する設計が可能となる。

hidden-friend関数(隠れたフレンド関数)の目的は、

* カプセル化の強化：
  クラスの内部実装を外部から隠しつつ、特定の操作だけを許可する。
* 名前空間汚染の防止：
  関数が名前空間スコープに現れないため、他の名前と衝突しにくい。
* 最適化：
  コンパイラによる最適化を妨げることなく、特定の機能を提供する。

```cpp
    //  example/core_lang_spec/hidden_friend_ut.cpp 7

    namespace NS {
    class Person {
    public:
        Person(std::string name, uint32_t age) : name_{std::move(name)}, age_{age} {}

        // hidden-friend関数
        friend std::ostream& operator<<(std::ostream& os, const Person& person)
        {
            os << "Name:" << person.name_ << ", Age:" << person.age_;
            return os;
        }

    private:
        std::string const name_;
        uint32_t const    age_;
    };
    }  // namespace NS
```
```cpp
    //  example/core_lang_spec/hidden_friend_ut.cpp 31

    NS::Person         alice("Alice", 30);
    std::ostringstream oss;

    oss << alice;  // フレンド関数を呼び出す(ADLによって見つかる)
    ASSERT_EQ("Name:Alice, Age:30", oss.str());

    // 以下はエラー（operator<<がNS名前空間スコープで見えない）
    // NS::Person::operator<<(oss, alice);
    // 上記は以下のようなコンパイルエラーになる
    //  error: ‘operator<<’ is not a member of ‘NS::Person’
```


### name-hiding <a id="SS_19_12_9"></a>
name-hidingとは
「前方の識別子が、その後方に同一の名前をもつ識別子があるために、
[name lookup](core_lang_spec.md#SS_19_12_2)の対象外になる」現象一般を指す通称である
([namespace](https://en.cppreference.com/w/cpp/language/namespace)参照)。

まずは、クラスとその派生クラスでのname-hidingの例を示す。

```cpp
    //  example/core_lang_spec/name_hiding.cpp 4

    struct Base {
        void f() {}
    };

    struct Derived : Base {
        // void f(int) { f(); }     // f()では、Baseのf()をname lookupできないため、
        void f(int) { Base::f(); }  // Base::でf()を修飾した
    };
```

上記の関数fは一見オーバーロードに見えるが、そうではない。下記のコードで示したように、
Base::f()には、修飾しない形式でのDerivedクラス経由のアクセスはできない。

```cpp
    //  example/core_lang_spec/name_hiding.cpp 18

    {
        auto d = Derived{};
    #if 0 
        d.f(); // コンパイルできない
    #else
        d.Base::f();  // Base::での修飾が必要
    #endif
    }
```

これは前述したように、
Base::fがその後方にあるDerived::f(int)によりname-hidingされたために起こる現象である
(name lookupによる探索には識別子が使われるため、シグネチャの違いはname-hidingに影響しない)。

下記のように[using宣言](core_lang_spec.md#SS_19_12_14)を使用することで、
修飾しない形式でのDerivedクラス経由のBase::f()へのアクセスが可能となる。

```cpp
    //  example/core_lang_spec/name_hiding.cpp 34

    struct Derived : Base {
        using Base::f;        // using宣言によりDerivedにBase::fを導入
        void f(int) { f(); }  // using Base::fの効果でfの名前修飾が不要になった
    };
```
```cpp
    //  example/core_lang_spec/name_hiding.cpp 45

    auto d = Derived{};
    d.f();  // using宣言によりコンパイルできる
```

下記コードは、名前空間でも似たような現象が起こることを示している。

```cpp
    //  example/core_lang_spec/name_hiding.cpp 54

    // global名前空間
    void f() {}

    namespace NS_A {
    void f(int) {}

    void g()
    {
    #if 0
        f();  // NS_A::fによりname-hidingされたため、コンパイルできない
    #endif
    }
    }  // namespace NS_A
```

この問題に対しては、下記のようにf(int)の定義位置を後方に移動することで回避できる。

```cpp
    //  example/core_lang_spec/name_hiding.cpp 70

    namespace NS_A_fixed_0 {
    void g()
    {
        // グローバルなfの呼び出し
        f();  // NS_A::fは後方に移動されたためコンパイルできる
    }

    void f(int) {}
    }  // namespace NS_A_fixed_0
```

また、先述のクラスでの方法と同様にusing宣言を使い、下記のようにすることもできる。

```cpp
    //  example/core_lang_spec/name_hiding.cpp 82

    namespace NS_A_fixed_1 {
    void f(int) {}

    void g()
    {
        using ::f;

        // グローバルなfの呼び出し
        f();  // using宣言によりコンパイルできる
    }
    }  // namespace NS_A_fixed_1
```

当然ながら、下記のようにf()の呼び出しを::で修飾することもできる。

```cpp
    //  example/core_lang_spec/name_hiding.cpp 96

    namespace NS_A_fixed_2 {
    void f(int) {}

    void g()
    {
        // グローバルなfの呼び出し
        ::f();  // ::で修飾すればコンパイルできる
    }
    }  // namespace NS_A_fixed_2
```

修飾の副作用として「[two phase name lookup](core_lang_spec.md#SS_19_12_3)」の例で示したような
[ADL](core_lang_spec.md#SS_19_12_5)を利用した高度な静的ディスパッチが使用できなくなるが、
通常のソフトウェア開発では、ADLが必要な場面は限られているため、
デフォルトでは名前空間を使用して修飾を行うことにするのが、
無用の混乱をさけるための安全な記法であると言えるだろう。

次に、そういった混乱を引き起こすであろうコードを示す。

```cpp
    //  example/core_lang_spec/name_hiding.cpp 108

    namespace NS_B {
    struct S_in_B {};

    void f(S_in_B) {}
    void f(int) {}

    namespace NS_B_Inner {
    void g()
    {
        f(int{});  // コンパイルでき、NS_B::f(int)が呼ばれる
    }

    void f() {}

    void h()
    {
        // f(int{});     // コンパイルできない
        NS_B::f(int{});  // 名前空間で修飾することでコンパイルできる

        f(S_in_B{});  // ADLによりコンパイルできる
    }
    }  // namespace NS_B_Inner
    }  // namespace NS_B
```

NS_B_Inner::g()内のf(int)の呼び出しはコンパイルできるが、
name-hidingが原因で、NS_B_Inner::h()内のf(int)の呼び出しはコンパイルできず、
名前空間で修飾することが必要になる。
一方で、ADLの効果で名前空間での修飾をしていないf(S_in_B)の呼び出しはコンパイルできる。

全チームメンバがこういったname lookupを正しく扱えると確信できないのであれば、
前述の通り、デフォルトでは名前空間を使用して修飾を行うのが良いだろう。

### ダイヤモンド継承 <a id="SS_19_12_10"></a>
ダイヤモンド継承(Diamond Inheritance)とは、以下のような構造のクラス継承を指す。

* 基底クラス(Base)が一つ存在し、その基底クラスから二つのクラス(Derived_0、Derived_1)が派生する。
* Derived_0とDerived_1からさらに一つのクラス(DerivedDerived)が派生する。
  したがって、DerivedDerivedはBaseの孫クラスとなる。

この継承は、多重継承の一形態であり、クラス図で表すと下記のようになるため、
ダイヤモンド継承と呼ばれる。

<!-- pu:essential/plant_uml/diamond_inheritance.pu--><p><img src="data:image/png;base64,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" /></p>

ダイヤモンド継承は、
[仮想継承](core_lang_spec.md#SS_19_12_11)(virtual inheritance)を使ったものと、使わないものに分類できる。

[仮想継承](core_lang_spec.md#SS_19_12_11)を使わないダイヤモンド継承のコードを以下に示す。

```cpp
    //  example/core_lang_spec/diamond_inheritance_ut.cpp 6

    class Base {
    public:
        int32_t get() const noexcept { return x_; }
        void    set(int32_t x) noexcept { x_ = x; }

    private:
        int32_t x_ = 0;
    };

    class Derived_0 : public Base {};

    class Derived_1 : public Base {};

    class DerivedDerived : public Derived_0, public Derived_1 {};
```
```cpp
    //  example/core_lang_spec/diamond_inheritance_ut.cpp 26

    auto dd = DerivedDerived{};

    Base& b0 = static_cast<Derived_0&>(dd);  // Derived_0::Baseのリファレンス
    Base& b1 = static_cast<Derived_1&>(dd);  // Derived_1::Baseのリファレンス

    ASSERT_NE(&b0, &b1);  // ddの中には、Baseインスタンスが2つできる
```

これからわかるように、DerivedDerivedインスタンスの中に2つのBaseインスタンスが存在する。
この状態をオブジェクト図で表すと下記のようになる。

<!-- pu:essential/plant_uml/diamond_inheritance_obj.pu--><p><img src="data:image/png;base64,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" /></p>

下記コードは、それが原因で名前解決が曖昧になりコンパイルできない。

```cpp
    //  example/core_lang_spec/diamond_inheritance_ut.cpp 36

    Base& b = dd;  // Derived_0::Base or Derived_1::Base ?

    dd.get();  // Derived_0::get or  Derived_1::get ?

    // 下記のようなエラーが発生する
    //  diamond_inheritance_ut.cpp:37:15: error: ‘Base’ is an ambiguous base of ‘DerivedDerived’
    //     37 |     Base& b = dd;  // Derived_0::Base or Derived_1::Base ?
    //        |               ^~
    //  diamond_inheritance_ut.cpp:39:8: error: request for member ‘get’ is ambiguous
    //     39 |     dd.get();  // Derived_0::get or  Derived_1::get ?
    //        |        ^~~
```

この問題に対処するには、クラス名による修飾が必要になるが、
Baseインスタンスが2つ存在するため、下記に示すようなわかりづらいバグの温床となる。

```cpp
    //  example/core_lang_spec/diamond_inheritance_ut.cpp 53

    ASSERT_EQ(0, dd.Derived_0::get());  // クラス名による名前修飾
    ASSERT_EQ(0, dd.Derived_1::get());

    dd.Derived_0::set(1);
    ASSERT_EQ(1, dd.Derived_0::get());  // Derived_0::Base::x_は1に変更
    ASSERT_EQ(0, dd.Derived_1::get());  // Derived_1::Base::x_は0のまま

    dd.Derived_1::set(2);
    ASSERT_EQ(1, dd.Derived_0::get());  // Derived_0::Base::x_は1のまま
    ASSERT_EQ(2, dd.Derived_1::get());  // Derived_1::Base::x_は2に変更
```

次に示すのは、[仮想継承](core_lang_spec.md#SS_19_12_11)を使用したダイヤモンド継承の例である。

```cpp
    //  example/core_lang_spec/diamond_inheritance_ut.cpp 70

    class Base {
    public:
        int32_t get() const noexcept { return x_; }
        void    set(int32_t x) noexcept { x_ = x; }

    private:
        int32_t x_ = 0;
    };

    class Derived_0 : public virtual Base {};  // 仮想継承

    class Derived_1 : public virtual Base {};  // 仮想継承

    class DerivedDerived : public Derived_0, public Derived_1 {};
```
```cpp
    //  example/core_lang_spec/diamond_inheritance_ut.cpp 90

    auto dd = DerivedDerived{};

    Base& b0 = static_cast<Derived_0&>(dd);  // Derived_0::Baseのリファレンス
    Base& b1 = static_cast<Derived_1&>(dd);  // Derived_1::Baseのリファレンス

    ASSERT_EQ(&b0, &b1);  // ddの中には、Baseインスタンスが1つできる
```

仮想継承の効果で、DerivedDerivedインスタンスの中に存在するBaseインスタンスは1つになるため、
上で示した仮想継承を使わないダイヤモンド継承での問題は解消される
(が、[仮想継承](core_lang_spec.md#SS_19_12_11)による別の問題が発生する)。

```cpp
    //  example/core_lang_spec/diamond_inheritance_ut.cpp 99

    Base& b = dd;  // Baseインスタンスは1つであるため、コンパイルできる

    dd.get();  // Baseインスタンスは1つであるため、コンパイルできる

    dd.Derived_0::set(1);               // クラス名による修飾
    ASSERT_EQ(1, dd.Derived_1::get());  // Derived_1::BaseとDerived_1::Baseは同一であるため

    dd.set(2);
    ASSERT_EQ(2, dd.get());
```

この状態をオブジェクト図で表すと下記のようになる。

<!-- pu:essential/plant_uml/diamond_inheritance_virtual_obj.pu--><p><img src="data:image/png;base64,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" /></p>

### 仮想継承 <a id="SS_19_12_11"></a>
下記に示した継承方法を仮想継承、仮想継承の基底クラスを仮想基底クラスと呼ぶ。

```cpp
    //  example/core_lang_spec/virtual_inheritance_ut.cpp 9

    class Base {
    public:
        explicit Base(int32_t x = 0) noexcept : x_{x} {}
        int32_t get() const noexcept { return x_; }

    private:
        int32_t x_;
    };

    class DerivedVirtual : public virtual Base {  // 仮想継承
    public:
        explicit DerivedVirtual(int32_t x) noexcept : Base{x} {}
    };
```

仮想継承は、[ダイヤモンド継承](core_lang_spec.md#SS_19_12_10)の基底クラスのインスタンスを、
その継承ヒエラルキーの中で1つのみにするための言語機能である。

仮想継承の独特の動作を示すため、
上記コードに加え、仮想継承クラス、通常の継承クラス、
それぞれを通常の継承したクラスを下記のように定義する。

```cpp
    //  example/core_lang_spec/virtual_inheritance_ut.cpp 25

    class DerivedDerivedVirtual : public DerivedVirtual {  // 仮想継承を通常の継承
    public:
        // 注: DerivedDerivedVirtualのコンストラクタは、Baseのデフォルトコンストラクタを呼び出す
        explicit DerivedDerivedVirtual(int32_t x) noexcept : DerivedVirtual{x} {}
    };

    class DerivedNormal : public Base {  // 通常の継承
    public:
        explicit DerivedNormal(int32_t x) noexcept : Base{x} {}
    };

    class DerivedDerivedNormal : public DerivedNormal {  // 通常継承を通常の継承
    public:
        explicit DerivedDerivedNormal(int32_t x) noexcept : DerivedNormal{x} {}
    };
```

この場合、継承ヒエラルキーに仮想継承を含むクラスと、含まないクラスでは、
以下に示したような違いが発生する。

```cpp
    //  example/core_lang_spec/virtual_inheritance_ut.cpp 46

    auto dv = DerivedVirtual{1};  // 仮想継承クラス
    auto dn = DerivedNormal{1};   // 通常の継承クラス

    ASSERT_EQ(1, dv.get());  // これは非仮想継承と同じ動作
    ASSERT_EQ(1, dn.get());

    auto ddv = DerivedDerivedVirtual{1};  // 仮想継承クラスを継承したクラス Base::Base()が呼ばれる
    auto ddn = DerivedDerivedNormal{1};   // 通常継承クラスを継承したクラス Base::Base(1)が呼ばれる

    ASSERT_EQ(0, ddv.get());  // ddvのBaseインスタンスはのデフォルトコンストラクタで初期化されている
    ASSERT_EQ(1, ddn.get());
```

この動作は、下記の仕様に起因している
(引数なしで呼び出せる基底クラスのコンストラクタがない場合はコンパイルエラー)。

__「仮想継承クラスを継承したクラスが、仮想継承クラスの基底クラスのコンストラクタを明示的に呼び出さない場合、
引数なしで呼び出せる基底クラスのコンストラクタが呼ばれる」__  

以下では、これを「仮想継承のコンストラクタ呼び出し」仕様と呼ぶことにする。

仮想継承クラスが、基底クラスのコンストラクタを呼び出したとしても、この仕様が優先されるため、
上記コードのような動作となる。

これを通常の継承クラスと同様な動作にするには、下記のようにしなければならない。

```cpp
    //  example/core_lang_spec/virtual_inheritance_ut.cpp 62

    class DerivedDerivedVirtualFixed : public DerivedVirtual {  // DerivedDerivedNormalと同じように動作
    public:
        explicit DerivedDerivedVirtualFixed(int32_t x) noexcept : Base{x}, DerivedVirtual{x} {}
        //                     基底クラスのコンストラクタ呼び出し ^^^^^^^
    };
```
```cpp
    //  example/core_lang_spec/virtual_inheritance_ut.cpp 73

    DerivedDerivedVirtual      ddv{1};   // 仮想継承クラスを継承したクラス
    DerivedDerivedVirtualFixed ddvf{1};  // 上記クラスのコンストラクタを修正したクラス
    DerivedDerivedNormal       ddn{1};   // 通常の継承クラスを継承したクラス

    ASSERT_EQ(0, ddv.get());  // 仮想継承独特の動作
    ASSERT_EQ(1, ddvf.get());
    ASSERT_EQ(1, ddn.get());
```
「仮想継承のコンストラクタ呼び出し」仕様は、
[ダイヤモンド継承](core_lang_spec.md#SS_19_12_10)での基底クラスのコンストラクタ呼び出しを一度にするために存在する。

もし、この機能がなければ、下記のコードでの基底クラスのコンストラクタ呼び出しは2度になるため、
デバッグ困難なバグが発生してしまうことは容易に想像できるだろう。

```cpp
    //  example/core_lang_spec/virtual_inheritance_ut.cpp 88

    int32_t base_called;

    class Base {
    public:
        explicit Base(int32_t x = 0) noexcept : x_{x} { ++base_called; }
        int32_t get() const noexcept { return x_; }

    private:
        int32_t x_;
    };

    class Derived_0 : public virtual Base {  // 仮想継承
    public:
        explicit Derived_0(int32_t x) noexcept : Base{x} { assert(base_called == 1); }
    };

    class Derived_1 : public virtual Base {  // 仮想継承
    public:
        explicit Derived_1(int32_t x) noexcept : Base{x} { assert(base_called == 1); }
    };

    class DerivedDerived : public Derived_0, public Derived_1 {
    public:
        DerivedDerived(int32_t x0, int32_t x1) noexcept : Derived_0{x0}, Derived_1{x1} {}
        // 「仮想継承のコンストラクタ呼び出し」仕様がなければ、このコンストラクタは、
        //    Base::Base -> Derived_0::Derived_0 ->
        //      Base::Base -> Derived_0::Derived_0 ->
        //        DerivedDerived::DerivedDerived
        //  という呼び出しになるため、Base::Baseが2度呼び出されてしまう。
    };
```
```cpp
    //  example/core_lang_spec/virtual_inheritance_ut.cpp 124

    ASSERT_EQ(0, base_called);

    auto dd = DerivedDerived{2, 3};  // Base::Baseが最初に呼ばれないとassertion failする

    ASSERT_EQ(1, base_called);  // 「仮想継承のコンストラクタ呼び出し」仕様のため
    ASSERT_EQ(0, dd.get());     // Baseのデフォルトコンストラクタは、x_を0にする
```

基底クラスのコンストラクタ呼び出しは、下記のコードのようにした場合でも、
単体テストが示すように、一番最初に行われる。

```cpp
    //  example/core_lang_spec/virtual_inheritance_ut.cpp 139

    class DerivedDerived : public Derived_0, public Derived_1 {
    public:
        DerivedDerived(int32_t x0, int32_t x1) noexcept : Derived_0{x0}, Derived_1{x1}, Base{1} {}
    };
```
```cpp
    //  example/core_lang_spec/virtual_inheritance_ut.cpp 151

    ASSERT_EQ(0, base_called);

    auto dd = DerivedDerived{2, 3};  // Base::Baseが最初に呼ばれないとassertion failする

    ASSERT_EQ(1, base_called);  // 「仮想継承のコンストラクタ呼び出し」仕様のため
    ASSERT_EQ(1, dd.get());     // Base{1}呼び出しの効果
```

このため、基底クラスのコンストラクタ呼び出しは下記のような順番で行うべきである。

```cpp
    //  example/core_lang_spec/virtual_inheritance_ut.cpp 164

    class DerivedDerived : public Derived_0, public Derived_1 {
    public:
        DerivedDerived(int32_t x0, int32_t x1) noexcept : Base{1}, Derived_0{x0}, Derived_1{x1} {}
    };
```

### 仮想基底 <a id="SS_19_12_12"></a>
仮想基底(クラス)とは、[仮想継承](core_lang_spec.md#SS_19_12_11)の基底クラス指す。

### ドミナンス <a id="SS_19_12_13"></a>
[ドミナンス(Dominance、支配性)](https://en.wikipedia.org/wiki/Dominance_(C%2B%2B))とは、
「探索対称の名前が継承の中にも存在するような場合の[name lookup](core_lang_spec.md#SS_19_12_2)の仕様の一部」
を指す慣用句である。

以下に

* [ダイヤモンド継承を含まない場合](core_lang_spec.md#SS_19_12_13_1)
* [ダイヤモンド継承かつそれが仮想継承でない場合](core_lang_spec.md#SS_19_12_13_2)
* [ダイヤモンド継承かつそれが仮想継承である場合](core_lang_spec.md#SS_19_12_13_3)

のドミナンスについてのコードを例示する。

この例で示したように、[ダイヤモンド継承](core_lang_spec.md#SS_19_12_10)を通常の継承で行うか、
[仮想継承](core_lang_spec.md#SS_19_12_11)で行うかでは結果が全く異なるため、注意が必要である。

#### ダイヤモンド継承を含まない場合 <a id="SS_19_12_13_1"></a>

```cpp
    //  example/core_lang_spec/dominance_ut.cpp 9

    int32_t f(double) noexcept { return 0; }

    struct Base {
        int32_t f(int32_t) const noexcept { return 1; }
        int32_t f(double) const noexcept { return 2; }
    };

    struct Derived : Base {
        int32_t f(int32_t) const noexcept { return 3; }  // Base::fを隠蔽する(name-hiding)
    };

    struct DerivedDerived : Derived {
        int32_t g() const noexcept { return f(2.14); }
    };
```
```cpp
    //  example/core_lang_spec/dominance_ut.cpp 29

    Base b;

    ASSERT_EQ(2, b.f(2.14));  // オーバーロード解決により、B::f(double)が呼ばれる

    DerivedDerived dd;

    // Derivedのドミナンスにより、B::fは、DerivedDerived::gでのfのname lookupの対象にならず、
    // DerivedDerived::gはDerived::fを呼び出す。
    ASSERT_EQ(3, dd.g());
```

この[name lookup](core_lang_spec.md#SS_19_12_2)については、[name-hiding](core_lang_spec.md#SS_19_12_9)で説明した通りである。

#### ダイヤモンド継承かつそれが仮想継承でない場合 <a id="SS_19_12_13_2"></a>

```cpp
    //  example/core_lang_spec/dominance_ut.cpp 45

    struct Base {
        int32_t f(int32_t) const noexcept { return 1; }
        int32_t f(double) const noexcept { return 2; }
    };

    struct Derived_0 : Base {
        int32_t f(int32_t) const noexcept { return 3; }  // Base::fを隠蔽する(name-hiding)
    };

    struct Derived_1 : Base {};

    struct DerivedDerived : Derived_0, Derived_1 {
        int32_t g() const noexcept { return f(2.14); }  // Derived_0::f or Derived_1::f ?
    };

    // dominance_ut.cpp:58:41: error: reference to ‘f’ is ambiguous
    //    58 |     int32_t g() const noexcept { return f(2.14); }  // Derived_0::f or Derived_1::f ?
    //       |                                         ^
```

上記コードはコードブロック内のコメントのようなメッセージが原因でコンパイルできない。

Derived_0のドミナンスにより、DerivedDerived::gはDerived_0::fを呼び出すように見えるが、
もう一つの継承元であるDerived_1が導入したDerived_1::f(実際には、Derived_1::Base::f)があるため、
Derived_1によるドミナンスも働き、その結果として、呼び出しが曖昧(ambiguous)になることで、
このような結果となる。

#### ダイヤモンド継承かつそれが仮想継承である場合 <a id="SS_19_12_13_3"></a>

```cpp
    //  example/core_lang_spec/dominance_ut.cpp 71

    struct Base {
        int32_t f(int32_t) const noexcept { return 1; }
        int32_t f(double) const noexcept { return 2; }
    };

    struct Derived_0 : virtual Base {
        int32_t f(int32_t) const noexcept { return 3; }  // Base::fを隠蔽する(name-hiding)
    };

    struct Derived_1 : virtual Base {};

    struct DerivedDerived : Derived_0, Derived_1 {
        int32_t g() const noexcept { return f(2.14); }
    };
```
```cpp
    //  example/core_lang_spec/dominance_ut.cpp 92

    DerivedDerived dd;

    // Derived_0のドミナンスと仮想継承の効果により、
    // B::fは、DerivedDerived::gでのfのname lookupの対象にならず、
    // DerivedDerived::gはDerived_0::fを呼び出す。
    ASSERT_EQ(3, dd.g());
```

これまでと同様にDerived_0のドミナンスによりBase::fは[name-hiding](core_lang_spec.md#SS_19_12_9)されることになる。
この時、Derived_0、Derived_1がBaseから[仮想継承](core_lang_spec.md#SS_19_12_11)した効果により、
この継承ヒエラルキーの中でBaseは１つのみ存在することになるため、
Derived_1により導入されたBase::fも併せて[name-hiding](core_lang_spec.md#SS_19_12_9)される。
結果として、曖昧性は排除され、コンパイルエラーにはならず、このような結果となる。

### using宣言 <a id="SS_19_12_14"></a>
using宣言とは、"using XXX::func"のような記述である。
この記述が行われたスコープでは、この記述後の行から名前空間XXXでの修飾をすることなく、
funcが使用できる。

```cpp
    //  example/core_lang_spec/namespace_ut.cpp 6
    namespace XXX {
    void func() noexcept {}
    void gunc() noexcept {}
    }  // namespace XXX
```
```cpp
    //  example/core_lang_spec/namespace_ut.cpp 12

    // global namespace
    void using_declaration() noexcept
    {
        using XXX::func;  // using宣言

        func();       // XXX::不要
        XXX::gunc();  // XXX::必要
    }

```

### usingディレクティブ <a id="SS_19_12_15"></a>
usingディレクティブとは、"using namespace XXX"のような記述である。
この記述が行われたスコープでは、下記例のように、この記述後から名前空間XXXでの修飾をすることなく、
XXXの識別子が使用できる。

```cpp
    //  example/core_lang_spec/namespace_ut.cpp 6
    namespace XXX {
    void func() noexcept {}
    void gunc() noexcept {}
    }  // namespace XXX
```
```cpp
    //  example/core_lang_spec/namespace_ut.cpp 24

    // global namespace
    void using_directive() noexcept
    {
        using namespace XXX;  // usingディレクティブ

        func();  // XXX::不要
        gunc();  // XXX::不要
    }
```

より多くの識別子が名前空間の修飾無しで使えるようになる点において、
[using宣言](core_lang_spec.md#SS_19_12_14)よりも危険であり、また、
下記のように[name-hiding](core_lang_spec.md#SS_19_12_9)された識別子の導入には効果がない。

```cpp
    //  example/core_lang_spec/namespace_ut.cpp 6
    namespace XXX {
    void func() noexcept {}
    void gunc() noexcept {}
    }  // namespace XXX
```
```cpp
    //  example/core_lang_spec/namespace_ut.cpp 35

    namespace XXX_Inner {
    void func(int) noexcept {}
    void using_declaration() noexcept
    {
    #if 0
        using namespace XXX;  // name-hidingのため効果がない
    #else
        using XXX::func;  // using宣言
    #endif

        func();  // XXX::不要
    }
```

従って、usingディレクティブの使用は避けるべきである。


## エクセプション安全性の保証 <a id="SS_19_13"></a>
関数のエクセプション発生時の安全性の保証には以下の3つのレベルが規定されている。

* [no-fail保証](core_lang_spec.md#SS_19_13_1)
* [強い安全性の保証](core_lang_spec.md#SS_19_13_2)
* [基本的な安全性の保証](core_lang_spec.md#SS_19_13_3)

### no-fail保証 <a id="SS_19_13_1"></a>
「no-fail保証」を満たす関数はエクセプションをthrowしない。
no-failを保証する関数は、
[noexcept](core_lang_spec.md#SS_19_13_4)を使用してエクセプションを発生させないことを明示できる。

標準テンプレートクラスのパラメータとして使用するクラスのメンバ関数には、
正確にnoexceptの宣言をしないと、
テンプレートクラスのメンバ関数によってはパフォーマンスを起こしてしまう可能性がある。

### 強い安全性の保証 <a id="SS_19_13_2"></a>
「強い保証」を満たす関数は、この関数がエクセプションによりスコープから外れた場合でも、
この関数が呼ばれなかった状態と同じ(プログラムカウンタ以外の状態は同じ)であることを保証する。
従って、この関数呼び出しは成功したか、完全な無効だったかのどちらかになる。

### 基本的な安全性の保証 <a id="SS_19_13_3"></a>
「基本的な安全性の保証」を満たす関数は、この関数がエクセプションによりスコープから外れた場合でも、
メモリ等のリソースリークは起こさず、
オブジェクトは(変更されたかもしれないが)引き続き使えることを保証する。

### noexcept <a id="SS_19_13_4"></a>
C++11で導入されたnoexceptキーワードには、以下の2つの意味がある。

* C++03までのthrowキーワードによるエクセプション仕様の代替。
  関数がどのエクセプションを送出する可能性があるかを列挙するのではなく、
  エクセプションを送出する可能性があるかないかのみを指定する。

* sizeofと同じような形式で使用されるのような演算子としてのnoexceptは、
  noexcept(expression)の形式使用され、
  expressionがエクセプションを送出しないと宣言されている場合(noexceptと宣言された関数の呼び出し)、
  noexcept(expression)は静的にtrueとなる。

以下に上記のコード例を示す。

```cpp
    //  example/core_lang_spec/noexcept_ut.cpp 11

    std::string f_noexcept() noexcept  // エクセプションを発生させない
    {
        return "No exceptions here!";
    }

    std::string f_except() noexcept(false)  // エクセプションを発生させる
    {
        throw std::runtime_error{"always throw"};

        return "No exceptions here!";
    }

    // noexcept or noexcept(false)と宣言しない限りnoexceptでない
    std::string f_except2()  // エクセプションを発生させる
    {
        throw std::runtime_error{"always throw"};

        return "No exceptions here!";
    }
```
```cpp
    //  example/core_lang_spec/noexcept_ut.cpp 37

    static_assert(noexcept(f_noexcept()));  // エクセプションを発生させる可能性の確認
    static_assert(!noexcept(f_except()));   // エクセプションを発生させない可能性の確認
    static_assert(!noexcept(f_except2()));  // エクセプションを発生させない可能性の確認

    ASSERT_EQ(f_noexcept(), "No exceptions here!");  // 動作確認
    ASSERT_THROW(f_except(), std::runtime_error);    // エクセプションの発生確認
    ASSERT_THROW(f_except2(), std::runtime_error);   // エクセプションの発生確認
```

演算子としてのnoexceptはテンプレートで頻繁に使用されるため、以下にそのような例を示す。

```cpp
    //  example/core_lang_spec/noexcept_ut.cpp 50

    class PossiblyThrow {  // オブジェクト生成でエクセプションの発生可能性あり
    public:
        PossiblyThrow() {}
    };

    // テンプレート型Tがnoexceptで生成可能なら、関数もnoexceptにする
    template <typename T>
    void t_f(T const&) noexcept(std::is_nothrow_constructible_v<T>)
    {
        // Tを生成して、何らかの処理を行う
    }
```
```cpp
    //  example/core_lang_spec/noexcept_ut.cpp 67

    auto i = int{};
    auto p = PossiblyThrow{};

    static_assert(!std::is_nothrow_constructible_v<PossiblyThrow>);
    static_assert(std::is_nothrow_constructible_v<decltype(i)>);
    static_assert(noexcept(t_f(i)));
    static_assert(!noexcept(t_f(p)));
```

### exception-unfriendly <a id="SS_19_13_5"></a>
以下のような関数  

* 初期化に関連する関数やコンストラクタ
    * 静的または thread_local な変数を初期化する関数やコンストラクタ
* 特殊メンバ関数
    * すべてのデストラクタ
    * すべてのエクセプションオブジェクトのコピーコンストラクタ
    * すべてのムーブコンストラクタ
    * すべてのムーブ代入演算子
* 特定の名前を持つ関数
    * "swap" という名前のすべての関数
* C言語との互換性を持つ関数
    * Cとのリンケージを持つすべての関数

の呼び出しでエクセプションがthrowされると、[未定義動作](core_lang_spec.md#SS_19_14_3)や[未規定動作](core_lang_spec.md#SS_19_14_4)が発生するため、
exception-unfriendly(エクセプションに不向き)であるとされる。
従って上記の関数は暗黙的または明示的に`noexcept`であることが求められる。


## 言語仕様の定義要素 <a id="SS_19_14"></a>
### ill-formed <a id="SS_19_14_1"></a>
[標準規格と処理系](https://cpprefjp.github.io/implementation-compliance.html)に詳しい解説があるが、

* [well-formed](core_lang_spec.md#SS_19_14_2)(適格)とはプログラムが全ての構文規則・診断対象の意味規則・
  単一定義規則を満たすことである。
* ill-formed(不適格)とはプログラムが適格でないことである。

プログラムがwell-formedになった場合、そのプログラムはコンパイルできる。
プログラムがill-formedになった場合、通常はコンパイルエラーになるが、
対象がテンプレートの場合、事情は少々異なり、[SFINAE](core_lang_spec.md#SS_19_11_1)によりコンパイルできることもある。

### well-formed <a id="SS_19_14_2"></a>
「[ill-formed](core_lang_spec.md#SS_19_14_1)」を参照せよ。

### 未定義動作 <a id="SS_19_14_3"></a>
未定義動作(Undefined Behavior)とは、
C++標準が特定の操作や状況に対して一切の制約を設けないケースである。
未定義動作が発生すると、プログラムの実行結果が予測できなくなり、
何が起こるかはコンパイラや環境によって異なる。
未定義動作を含むコードは、クラッシュやセキュリティの問題を引き起こす可能性がある。

```cpp
    //  example/core_lang_spec/undefined_ut.cpp 14

    int a = 42;
    int b = 0;
    int c = a / b;  // 未定義動作 - ゼロ除算

    int arr[]{1, 2, 3};
    int x = arr[index];  // 未定義動作 - index>2の場合、配列範囲外アクセス

```

### 未規定動作 <a id="SS_19_14_4"></a>
未規定動作(Unspecified Behavior)とは、C++標準がある操作の動作を完全には決めておらず、
複数の許容可能な選択肢がある場合でのコードの動作を指す。
未規定動作は、実装ごとに異なる可能性があり、標準は少なくとも「何らかの合理的な結果」を保証する。
つまり、動作が特定の範囲で予測可能だが、正確な挙動が処理系の実装に依存することになる。

```cpp
    //  example/core_lang_spec/undefined_ut.cpp 35

    enum class MyEnum : int { Value1 = 1, Value2 = 256 };
    int value = static_cast<int8_t>(MyEnum::Value2);  // 未規定 - 256はint8_tとして表現できない

    auto a      = int{5};
    auto lambda = [](auto a0, auto a1) { return a0 / a1; };
    auto result = lambda(a++, a++);  // 未規定 - 引数評価の順序が決まっていない
```

### 未定義動作と未規定動作 <a id="SS_19_14_5"></a>
| 種類            |定義                                                               | 例                               | 結果                           |
|-----------------|-------------------------------------------------------------------|----------------------------------|--------------------------------|
|[未定義動作](core_lang_spec.md#SS_19_14_3)|C++標準が全く保証しない動作                                        | ゼロ除算、配列範囲外アクセス     | 予測不能(クラッシュなど)       |
|[未規定動作](core_lang_spec.md#SS_19_14_4)|C++標準が動作を定めていないが、いくつかの選択肢が許容されている動作| `int8_t` に収まらない値のキャスト| 実装依存(異なるが合理的な動作) |


### 被修飾型 <a id="SS_19_14_6"></a>
被修飾型(unqualified type)とは、変数の宣言において付加される修飾子(const、
volatile など)やポインタやリファレンスなどの間接指定子を除いた素の型を指す。

修飾子(const、volatile)に注視しい場合、cv-被修飾型(cv-unqualified type)という場合もある。

例えば: 

|定義         |被修飾型|
|-------------|:------:|
|const A& a   |A       |
|volatile B& b|B       |
|const T* C   |C       |
|const D d    |D       |

見た目が類似する[修飾付き関数呼び出し](core_lang_spec.md#SS_19_12_7)とは無関係である。

### 実引数/仮引数 <a id="SS_19_14_7"></a>
引数(もしくは実引数、argument)、仮引数(parameter)とは下記のように定義される。

```cpp
    //  example/core_lang_spec/argument.cpp 2

    int f0(int a, int& b) noexcept  // a, bは仮引数
    {
        // ...
    }

    void f1() noexcept
    {
        // ...

        f0(x, y);  // x, yは実引数
    }
```

### 単純代入 <a id="SS_19_14_8"></a>
代入は下記のように分類される。

* 単純代入(=)
* 複合代入(+=，++ 等)


### one-definition rule <a id="SS_19_14_9"></a>
「[ODR](core_lang_spec.md#SS_19_14_10)」を参照せよ。

### ODR <a id="SS_19_14_10"></a>
ODRとは、One Definition Ruleの略語であり、下記のようなことを定めている。

* どの翻訳単位でも、テンプレート、型、関数、またはオブジェクトは、複数の定義を持つことができない。
* プログラム全体で、オブジェクトまたは非インライン関数は複数の定義を持つことはできない。
* 型、テンプレート、外部インライン関数等、いくつかのものは複数の翻訳単位で定義することができる。

より詳しい内容がが知りたい場合は、
[https://en.cppreference.com/w/cpp/language/definition](https://en.cppreference.com/w/cpp/language/definition)
が参考になる。

### 型特性キーワード <a id="SS_19_14_11"></a>
アライメントとは、
データが効率的にアクセスされるために特定のメモリアドレス境界に配置される規則である。
C++03までの規約では、アライメントのコントロールは実装依存した#pragmaなどで行っていた。

[alignas](core_lang_spec.md#SS_19_14_11_2)、
[alignof](core_lang_spec.md#SS_19_14_11_1)によりコンパイラの標準的な方法でアライメントのコントロールできるようになった。

#### alignof <a id="SS_19_14_11_1"></a>
C++11で導入されたキーワードで、型のアライメント要求を取得するために使用する。

```cpp
    //  example/core_lang_spec/aliging_ut.cpp 12

    struct alignas(16) AlignedStruct {  // メモリ上で16バイト境界にアライメントされる
        char   a;
        double x;
        double y;
    };

    AlignedStruct a;

    uintptr_t address = reinterpret_cast<uintptr_t>(&a);  // aのアドレスを取得

    ASSERT_EQ(address % 16, 0);             // アドレスが16の倍数であることを確認
    ASSERT_EQ(alignof(AlignedStruct), 16);  // アライメントが正しいか確認
```

#### alignas <a id="SS_19_14_11_2"></a>
C++11で導入されたキーワードで、メモリのアライメントを指定するために使用する。

```cpp
    //  example/core_lang_spec/aliging_ut.cpp 27

    ASSERT_EQ(alignof(long double), 16);  // アライメントが正しいか確認
    ASSERT_EQ(alignof(long long), 8);     // アライメントが正しいか確認
    ASSERT_EQ(alignof(void*), 8);         // アライメントが正しいか確認
    ASSERT_EQ(alignof(int), 4);           // アライメントが正しいか確認
```

#### addressof <a id="SS_19_14_11_3"></a>
addressofは、オブジェクトの「実際の」
アドレスを取得するために使用されるC++標準ライブラリのユーティリティ関数である。
通常、オブジェクトのアドレスを取得するには&演算子を使うが、
operator& がオーバーロードされている場合には、
&演算子ではオブジェクトのメモリ上の実際のアドレスを取得できない場合があり得る。
そのような場合にstd::addressofすることにより、
オーバーロードを無視して元のアドレスを確実に取得できる。

```cpp
    //  example/core_lang_spec/aliging_ut.cpp 38

    class X {
    public:
        explicit X(int v) : v_{v} {}

        X* operator&()
        {                    // `operator&` をオーバーロードしてアドレス取得の挙動を変更
            return nullptr;  // 意図的に nullptr を返す
        }
        operator int() const noexcept { return v_; }

    private:
        int v_;
    };
```
```cpp
    //  example/core_lang_spec/aliging_ut.cpp 54

    X obj{42};

    X* p0 = &obj;  // &演算子で取得するアドレス(オーバーロードされているためnullptr が返る)
    ASSERT_EQ(p0, nullptr);

    // std::addressofとほぼ同じ実装であるラムダ
    auto addressof = [](auto& arg) noexcept {
        return reinterpret_cast<std::remove_reference_t<decltype(arg)>*>(
            &const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
    };

    // ラムダaddressofを使用して強引にobjのアドレスを取得
    X* p1 = addressof(obj);
    ASSERT_NE(p1, nullptr);

    int* i_ptr = reinterpret_cast<int*>(p1);  // 処理系依存だが、通常の32/64bit環境なら通る
    ASSERT_EQ(42, *i_ptr);

    X* p2 = std::addressof(obj);
    ASSERT_EQ(p1, p2);
```

### 演算子のオペランドの評価順位 <a id="SS_19_14_12"></a>

C++17で、演算子のオペランドに対する評価順序が明確に規定された。
それに対し、C++14までは、演算子のオペランド部分式の評価順序は[未規定動作](core_lang_spec.md#SS_19_14_4)であった。
以下の表で示す演算子に関しては、オペランドaがオペランドbよりも先に評価される。

| 演算子               |説明                                                                   |
|:---------------------|:----------------------------------------------------------------------|
| a.b                  |メンバアクセス演算子                                                   |
| a->b                 |ポインタメンバアクセス演算子                                           |
| a->\*b               |メンバポインタアクセス演算子                                           |
| a(b1,  b2, b3)       |関数呼び出し、引数リストの評価順序は規定外)                            |
| b @= a               |代入演算子 = や複合代入演算子。@は+,-,/,&,\|など                       |
| a[b]                 |配列アクセス                                                           |
| a << b               |ビットシフト左演算子                                                   |
| a >> b               |ビットシフト右演算子                                                   |

C++11以前では、以下のコードの評価順序は未規定であったが、上記の通り定義された。

```cpp
    //  example/core_lang_spec/etc_ut.cpp 74

    int i = 0;
    int y = (i = 1) * x + (i = 2);

    a(b1, b2, b3);  // b1, b2, b3の評価順序は規定外
```

関数呼び出しにおける引数の式の評価順序は、上記の例a(b1, b2, b3)での評価順序は、
不定順で序列化される。これは、b1, b2, b3 が特定の順序で評価される保証はなく、
例えば b3, b2, b1 の順に評価されたり、
b2, b3, b1 で評価される可能性があることを意味する。
一方で一度評価が開始された場合、部分式間でインターリーブ（交差実行されることはない。
つまり、b1 の評価が完全に終わる前に b2 や b3 の評価が開始されることはない。

条件演算子式`condition ? expr1 : expr2`については、
最初の部分であるconditionがまず評価される。
conditionの評価結果に基づき、expr1または expr2 のどちらかが選択され、選択された側だけが評価される。  

```cpp
    //  example/core_lang_spec/etc_ut.cpp 83

    int a      = 1;
    int b      = 2;
    int result = (a < b) ? func1() : func2();
```

なお、単項演算子のオペランドは1つであるため、優先順位の定義は不要である。

## その他 <a id="SS_19_15"></a>
### RVO(Return Value Optimization) <a id="SS_19_15_1"></a>
関数の戻り値がオブジェクトである場合、
戻り値オブジェクトは、その関数の呼び出し元のオブジェクトにcopyされた後、すぐに破棄される。
この「オブジェクトをcopyして、その後すぐにそのオブジェクトを破棄する」動作は、
「関数の戻り値オブジェクトをそのままその関数の呼び出し元で使用する」ことで効率的になる。
RVOとはこのような最適化を指す。

なお、このような最適化は、
[C++17から規格化](https://cpprefjp.github.io/lang/cpp17/guaranteed_copy_elision.html)された。


### トライグラフ <a id="SS_19_15_2"></a>
トライグラフとは、2つの疑問符とその後に続く1文字によって表される、下記の文字列である。

```
    ??=  ??/  ??'  ??(  ??)  ??!  ??<  ??>  ??-
```


