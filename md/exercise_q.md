# 演習

本章では、これまで解説した内容の復習やより深い理解のために、
解選択問題とプログラミング記述問題を提供する。

多くのプログラミング記述問題は、
google testを含むC++のソースコードと以下のようなコードコメントで与えれらる。

```cpp
    // [Q]
    // 以下のXXXをせよ。
```

___

__この章の構成__

<!-- index 1-2 -->
  
[このドキュメントの構成](---)に戻る。  

___

## プログラミング規約(型)

### 演習-汎整数型の選択
* 問題  
  汎整数型には、特に理由がない限りに、int32\_tを使用するべきであるが、
  値が負にならない場合は、(A)を使用するべきである。  
  (A)に相応しいものを下記より選べ。  

* 選択肢  
    1. int32_t
    2. unsigned long
    3. uint32_t
    4. uint16_t

* [解答-汎整数型の選択](---)


### 演習-汎整数型の演算
* 問題
```cpp
    // @@@ exercise/programming_convention_q/type.cpp #0:0 begin
```

* 参照 [プログラミング規約|型とインスタンス|算術型](---)
* [解答例-汎整数型の演算](---)


### 演習-浮動小数点型
* 問題
```cpp
    // @@@ exercise/programming_convention_q/type.cpp #1:0 begin
```

* 参照 [算術型|浮動小数点型](---)
* [解答例-浮動小数点型](---)


### 演習-定数列挙
* 問題  
  特に理由がない限り、一連の定数の列挙には(A)を定義して使用する。  
  (A)に相応しいものを下記より選べ。

* 選択肢  
    1. マクロ定数
    2. static const定数
    3. 非スコープドenum
    4. スコープドenum

* [解答-定数列挙](---)


### 演習-enum
* 問題
```cpp
    // @@@ exercise/programming_convention_q/type.cpp #2:0 begin
```

* 参照 [列挙型とバイト表現|enum](---)
* [解答例-enum](---)


### 演習-配列の範囲for文
* 問題
```cpp
    // @@@ exercise/programming_convention_q/type.cpp #3:0 begin
```

* 参照 [配列](---)
* [解答例-配列の範囲for文](---)


### 演習-エイリアス
* 問題

```cpp
    // @@@ exercise/programming_convention_q/type.cpp #4:0 begin
```

* 参照 [型エイリアス](---)
* [解答例-エイリアス](---)


### 演習-constの意味
* 問題  
  初期化後に変更されない変数はconstと宣言すべきであるが、
  以下のコードの2つのconstの意味にふさわしいものを選択せよ。

```cpp
    char const* const country = "japan";
```

* 選択肢  
    1. 左側のconstはcountryが指す先が不変。右側のconstは、country自体が不変。
    2. 左側のconstはcountry自体が不変。右側のconstは、countryが指す先が不変。
    3. 左右ともconstはcountry自体が不変。
    4. 上記のどれでもない。

* [解答-constの意味](---)


### 演習-const/constexpr
* 問題
```cpp
    // @@@ exercise/programming_convention_q/type.cpp #5:0 begin
```

* 参照 [const/constexprインスタンス](---)
* [解答例-const/constexpr](---)


### 演習-危険なconst_cast
* 問題
```cpp
    // @@@ exercise/programming_convention_q/type.cpp #6:0 begin
```

* 参照 [const/constexprインスタンス](---)
* [解答例-危険なconst_cast](---)


### 演習-リテラル
* 問題
```cpp
    // @@@ exercise/programming_convention_q/type.cpp #7:0 begin
```

* 参照 [C++標準|リテラル](---)

* [解答例-リテラル](---)


### 演習-適切なautoの使い方
* 問題  
  以下のコードのautoの中で、使い方が好ましくないものを選べ。

* 選択肢  
    1. auto s0 = std::string("xxx");
    2. auto s1(std::string("xxx"));
    3. auto s2 = s0;                   // s0は上記に定義されたもの
    4. auto s3 = get_name();           // get_name()は離れた場所に宣言

* [解答-適切なautoの使い方](---)


### 演習-ポインタの初期化
* 問題  
  初期値が定まらないポインタ変数の初期化方法にふさわしいものを選べ。

* 選択肢  
    1. 0を代入する。
    2. NULLを代入する。
    3. nullptrを代入する。
    4. 何もしない。

* [解答-ポインタの初期化](---)


### 演習-vector初期化
* 問題  
  以下のコード実行後のvecの状態を選べ。

```cpp
    vector<int32_t> vec{10};
```

* 選択肢  
    1. vec.size()が1で、vec[0]は10
    2. vec.size()が10で、vec[0] ～ vec[9]は不定
    3. vec.size()が1で、vec[0]は不定
    4. vec.size()が10で、vec[0] ～ vec[9]は0

* [解答-vector初期化](---)


### 演習-インスタンスの初期化
* 問題
```cpp
    // @@@ exercise/programming_convention_q/type.cpp #8:0 begin
```

* 参照 [インスタンスの初期化](---)、[一様初期化](---)
* [解答例-インスタンスの初期化](---)


## プログラミング規約(クラス)

### 演習-凝集度の意味
* 問題  
  クラスの凝集度とはLack of Cohesion in Methodsというメトリクスで計測される。
  この凝集度やメトリクスの説明として正しくないものを選べ。

* 選択肢  
    1. クラスは凝集度を高くするように設計すべきである。
    2. このメトリクス値が1に近ければ凝集度は低く、この値が0に近ければ凝集度は高い。
    3. メンバ変数やメンバ関数が多くなれば、凝集度は低くなりやすい。
    4. setterやgetterを使用することで、凝集度を高く保つことができる。

* [解答-凝集度の意味](---)


### 演習-凝集度の向上
* 問題
```cpp
    // @@@ exercise/programming_convention_q/class.cpp #0:0 begin
```

* 参照 [クラスの規模|凝集度](---)
* [解答例-凝集度の向上](---)


### 演習-メンバ変数の初期化方法の選択
* 問題  
  非静的なメンバ変数の初期化には下記の3つの方法がある。
  これらの説明として誤っているものを下記選択肢より選べ。

    * 初期化方法０: 非静的メンバ変数の初期化子による初期化
    * 初期化方法１: コンストラクタの非静的メンバ初期化子による初期化
    * 初期化方法２: コンストラクタ内での非静的なメンバ変数の初期化

* 選択肢  
    1. 初期化方法０を優先して使う。
    2. どの方法も優劣はないので、任意に選択してよい。
    3. 初期化方法０が使えない場合は、なるべく初期化方法１を使う。
    4. 初期化方法０、１が使えない場合のみ初期化方法２を使う。

* [解答-メンバ変数の初期化方法の選択](---)


### 演習-メンバの型
* 問題  
  以下のA::strの意味を表すものを選べ。

```cpp
    class A {
        ...
    private:
        std::string str();     // <- この意味
    };
```

* 選択肢  
    1. デフォルト初期化されたstd::stringオブジェクト
    2. 初期化されていないstd::stringオブジェクト
    3. std::stringオブジェクトを返す関数
    4. 以上のいずれでもない

* [解答-メンバの型](---)


### 演習-メンバ変数の初期化
* 問題
```cpp
    // @@@ exercise/programming_convention_q/class.cpp #1:0 begin
```

* 参照 [非静的なメンバ変数](---)
* [解答例-メンバ変数の初期化](---)


### 演習-スライシング
* 問題
```cpp
    // @@@ exercise/programming_convention_q/class.cpp #2:0 begin
```

* 参照 [クラスとインスタンス|スライシング](---)
* [解答例-スライシング](---)

### 演習-オブジェクトの所有権
* 問題
```cpp
    // @@@ exercise/programming_convention_q/class.cpp #3:0 begin
```

* 参照 [クラスとインスタンス|オブジェクトの所有権](---)
* [解答例-オブジェクトの所有権](---)


## プログラミング規約(関数)

### 演習-非メンバ関数の宣言
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #0:0 begin
```

* 参照 [非メンバ関数](---)
* [解答例-非メンバ関数の宣言](---)


### 演習-メンバ関数の修飾
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #1:0 begin
```

* 参照 [メンバ関数](---)
* [解答例-メンバ関数の修飾](---)


### 演習-特殊メンバ関数の削除
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #2:0 begin
```

* 参照 [メンバ関数|特殊メンバ関数](---)
* [解答例-特殊メンバ関数の削除](---)


### 演習-委譲コンストラクタ
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #3:0 begin
```

* 参照 [コンストラクタ](---)
* [解答例-委譲コンストラクタ](---)


### 演習-copyコンストラクタ
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #4:0 begin
```

* 参照 [コンストラクタ](---)
* [解答例-copyコンストラクタ](---)


### 演習-moveコンストラクタ
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #5:0 begin
```

* 参照 [moveコンストラクタ、move代入演算子](---)
* [解答例-moveコンストラクタ](---)


### 演習-関数分割
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #6:0 begin
```

* 参照 [非メンバ関数/メンバ関数共通|行数](---)
* [解答例-関数分割](---)


### 演習-オーバーライド関数の修飾
* 問題  
  オーバーライドしたメンバ関数は、virtualと(A)を使用して宣言する。  
  (A)に相応しいものを下記より選べ。

* 選択肢  
    1. final
    2. override
    3. overload
    4. const

* [解答-オーバーライド関数の修飾](---)


### 演習-オーバーライド/オーバーロード
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #7:0 begin
```

* 参照 [オーバーライド](---)
* [解答例-オーバーライド/オーバーロード](---)


### 演習-オーバーロードによる誤用防止
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #8:0 begin
```

* 参照 [オーバーロード](---)
* [解答例-オーバーロードによる誤用防止](---)


### 演習-仮引数の修飾
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #9:0 begin
```

* 参照 [非メンバ関数/メンバ関数共通|実引数/仮引数](---)
* [解答例-仮引数の修飾](---)


### 演習-constexpr関数
* 問題
```cpp
    // @@@ exercise/programming_convention_q/func.cpp #10:0 begin
```

* 参照 [定数式とコンパイル時評価|constexpr関数](---)
* [解答例-constexpr関数](---)


### 演習-エクセプションの型
* 問題  
  try-catchでエクセプションを捕捉する場合、
  catchの中で宣言するエクセプション補足用の変数は(A)として定義する。  
  (A)に相応しいものを下記より選べ。

* 選択肢  
    1. constポインタ
    2. constリファレンス
    3. 非constオブジェクト
    4. constオブジェクト

* [解答-エクセプションの型](---)


## プログラミング規約(構文)

### 演習-コンテナの範囲for文
* 問題
```cpp
    // @@@ exercise/programming_convention_q/syntax.cpp #0:0 begin
```

* 参照 [構文と制御構造|範囲for文](---)
* [解答例-コンテナの範囲for文](---)


### 演習-ラムダ式
* 問題
```cpp
    // @@@ exercise/programming_convention_q/syntax.cpp #1:0 begin
```

* 参照 [構文|ラムダ式](---)
* [解答例-ラムダ式](---)


### 演習-ラムダ式のキャプチャ
* 問題
```cpp
    // @@@ exercise/programming_convention_q/syntax.cpp #2:0 begin
```

* 参照 [構文|ラムダ式](---)
* [解答例-ラムダ式のキャプチャ](---)

## プログラミング規約(演算子)

### 演習-条件演算子
* 問題
```cpp
    // @@@ exercise/programming_convention_q/operator.cpp #0:0 begin
```

* 参照 [条件演算子](---)
* [解答例-条件演算子](---)


### 演習-delete
* 問題
```cpp
    // @@@ exercise/programming_convention_q/operator.cpp #1:0 begin
```

* 参照 [delete](---)
* [解答例-delete](---)


### 演習-sizeof
* 問題
```cpp
    // @@@ exercise/programming_convention_q/operator.cpp #2:0 begin
```

* 参照 [sizeof](---)
* [解答例-sizeof](---)


### 演習-dynamic_castの削除
* 問題
```cpp
    // @@@ exercise/programming_convention_q/operator.cpp #3:0 begin
```

* 参照 [キャスト、暗黙の型変換](---)
* [解答例-dynamic_castの削除](---)


### 演習-キャスト
* 問題  
  キャストは避けるべきだが、やむを得ず使用する場合であっても、
  Cタイプキャスト、(A)、 dynamic_castは使用しない。  
  (A)に相応しいものを下記より選べ。

* 選択肢  
    1. static_cast
    2. reinterpret_cast
    3. const_cast
    4. 該当なし

* [解答-キャスト](---)


## プログラミング規約(スコープ)

### 演習-usingディレクティブ
* 問題  
  usingディレクティブ(using namespace NS)の使用上の注意として相応しいものを選べ。

* 選択肢  
    1. usingディレクティブは、関数先頭でのみ使用してよい。
    2. ヘッダファイルでusingディレクティブをすると便利である。
    3. ファイルスコープでusingディレクティブをすると便利である。
    4. using宣言よりusingディレクティブを優先するべきである。

* [解答-usingディレクティブ](---)


## プログラミング規約(その他)

### 演習-アサーションの選択
* 問題  
  論理的にありえない(switchでそのcaseやdefaultを通過することはあり得ない等)
  状態を検知するために積極的に(A)を使用する。  
  (A)に相応しいものを下記より選べ。

* 選択肢  
    1. assert()
    2. static_assert
    3. while(1);
    4. abort()

* [解答-アサーションの選択](---)


### 演習-assert/static_assert
* 問題
```cpp
    // @@@ exercise/programming_convention_q/etc.cpp #0:0 begin
```

* 参照 [assertion](---)
* [解答例-assert/static_assert](---)


## SOLID
以下の演習問題の単体テストで使用される

```cpp
    TEST_F(Xxx, Yyy)
```

のような記述のXxyは、以下のように宣言・定義されている。

```cpp
    // @@@ exercise/h/solid_ut.h #0:0 begin
```

### 演習-SRP
* 問題
```cpp
    // @@@ exercise/solid_q/srp_test_score.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/srp_test_score.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/srp_test_score_ut.cpp #0:0 begin
```

* 参照 [単一責任の原則(SRP)](---)
* [解答例-SRP](---)


### 演習-OCP
* 問題
```cpp
    // @@@ exercise/solid_q/ocp_test_score.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/ocp_test_score.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/ocp_test_score_ut.cpp #0:0 begin
```

* 参照 [オープン・クローズドの原則(OCP)](---)
* [解答例-OCP](---)


### 演習-LSP
* 問題
```cpp
    // @@@ exercise/solid_q/lsp_test_score.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/lsp_test_score.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/lsp_test_score_ut.cpp #0:0 begin
```

* 参照 [リスコフの置換原則(LSP)](---)
* [解答例-LSP](---)


### 演習-ISP
* 問題
```cpp
    // @@@ exercise/solid_q/isp_test_score.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/isp_test_score.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/isp_test_score_ut.cpp #0:0 begin
```

* 参照 [インターフェース分離の原則(ISP)](---)
* [解答例-ISP](---)


### 演習-DIP
* 問題
```cpp
    // @@@ exercise/solid_q/dip_test_score.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/dip_test_score.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/dip_test_score_ut.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/dip_test_score_client.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/dip_test_score_client.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_q/dip_test_score_client_ut.cpp #0:0 begin
```

* 参照 [依存関係逆転の原則(DIP)](---)
* [解答例-DIP](---)


### 演習-SOLIDの定義
* 問題  
  下記原則群と説明群を結びつけよ。

* 原則群
    * SRP
    * OCP
    * LIP
    * ISP
    * DIP

* 説明群
    1. 一つのクラスは、ただ一つの責任(機能)を持つようにしなければならない。
    2. クラスは拡張に対して開いていて、 クラスは修正に対して閉じていなければならない。
    3. 事前条件を派生クラスで強めることはできず、事後条件を派生クラスで弱めることはできない。
    4. クラスは、そのクライアントが使用しないメソッドへの依存をそのクライアントに強制するべきではない。
    5. 上位レベルのモジュールは下位レベルのモジュールに依存すべきではない。

* [解答-SOLIDの定義](---)


## デザインパターン
### 演習-ガード節
* 問題
```cpp
    // @@@ exercise/design_pattern_q/guard.cpp #0:0 begin
```

* 参照 [ガード節](---)
* [解答例-ガード節](---)


### 演習-BitmaskType
* 問題
```cpp
    // @@@ exercise/design_pattern_q/enum_bitmask.cpp #0:0 begin
```

* 参照 [BitmaskType](---)
* [解答例-BitmaskType](---)


### 演習-Pimpl
* 問題
```cpp
    // @@@ exercise/design_pattern_q/pimpl.cpp #0:0 begin
```

* 参照 [Pimpl](---)
* [解答例-Pimpl](---)


### 演習-Accessorの副作用
* 問題  
  Accessor(特にセッター)には重大な副作用がある。その副作用を下記から選択せよ。

* 選択肢  
    1. クラスのカプセル化の破壊
    2. SRPへの違反
    3. 関数の巨大化
    4. クラスの巨大化

* [解答-Accessorの副作用](---)


### 演習-Accessor
* 問題
```cpp
    // @@@ exercise/design_pattern_q/accessor.cpp #0:0 begin
```

* 参照 [Accessor](---)
* [解答例-Accessor](---)


### 演習-Copy-And-Swap
* 問題
```cpp
    // @@@ exercise/design_pattern_q/copy_and_swap.cpp #0:0 begin
```

* 参照 [Copy-And-Swap](---)
* [解答例-Copy-And-Swap](---)


### 演習-Immutable
* 問題
```cpp
    // @@@ exercise/design_pattern_q/immutable.cpp #0:0 begin
```

* 参照 [Immutable](---)
* [解答例-Immutable](---)


### 演習-Clone
* 問題
```cpp
    // @@@ exercise/design_pattern_q/clone.cpp #0:0 begin
```

* 参照 [Clone(仮想コンストラクタ)](---)
* [解答例-Clone](---)


### 演習-NVI
* 問題
```cpp
    // @@@ exercise/design_pattern_q/nvi.cpp #0:0 begin
```

* 参照 [NVI(non virtual interface)](---)
* [解答例-NVI](---)


### 演習-RAIIの効果
* 問題  
  RAIIにはどのような効果があるか？　下記より相応しいものを選択せよ。

* 選択肢  
    1. リソースリークの防止
    2. 使用リソースの削減
    3. クラスの実装を隠ぺい
    4. LIPの順守

* [解答-RAIIの効果](---)


### 演習-RAII
* 問題
```cpp
    // @@@ exercise/design_pattern_q/raii.cpp #0:0 begin
```

* 参照 [RAII(scoped guard)](---)
* [解答例-RAII](---)


### 演習-Future
* 問題
```cpp
    // @@@ exercise/design_pattern_q/future.cpp #0:0 begin
```

* 参照 [Future](---)
* [解答例-Future](---)


### 演習-DI
* 問題
```cpp
    // @@@ exercise/design_pattern_q/di.cpp #0:0 begin
```

* 参照 [DI(dependency injection)](---)
* [解答例-DI](---)


### 演習-Singleton
* 問題
```cpp
    // @@@ exercise/design_pattern_q/singleton.cpp #0:0 begin
```

* 参照 [Singleton](---)
* [解答例-Singleton](---)


### 演習-State
* 問題
```cpp
    // @@@ exercise/design_pattern_q/state.cpp #0:0 begin
```

* 参照 [State](---)
* [解答例-State](---)


### 演習-Null Object
* 問題
```cpp
    // @@@ exercise/design_pattern_q/null_object.cpp #0:0 begin
```

* 参照 [Null Object](---)
* [解答例-Null Object](---)


### 演習-Templateメソッド
* 問題
```cpp
    // @@@ exercise/design_pattern_q/template_method.cpp #0:0 begin
```

* 参照 [Templateメソッド](---)
* [解答例-Templateメソッド](---)


### 演習-Factory
* 問題
```cpp
    // @@@ exercise/design_pattern_q/factory_lib.h #0:0 begin
```
```cpp
    // @@@ exercise/design_pattern_q/factory_lib.cpp #0:0 begin
```
```cpp
    // @@@ exercise/design_pattern_q/factory.cpp #0:0 begin
```

* 参照 [Factory](---)
* [解答例-Factory](---)


### 演習-Named Constructor
* 問題
```cpp
    // @@@ exercise/design_pattern_q/named_constructor_lib.h #0:0 begin
```
```cpp
    // @@@ exercise/design_pattern_q/named_constructor_lib.cpp #0:0 begin
```
```cpp
    // @@@ exercise/design_pattern_q/named_constructor.cpp #0:0 begin
```

* 参照 [Named Constructor](---)
* [解答例-Named Constructor](---)


### 演習-Proxy
* 問題
```cpp
    // @@@ exercise/design_pattern_q/proxy.cpp #0:0 begin
```

* 参照 [Proxy](---)
* [解答例-Proxy](---)


### 演習-Strategy
* 問題
```cpp
    // @@@ exercise/design_pattern_q/strategy.cpp #0:0 begin
```

* 参照 [Strategy](---)
* [解答例-Strategy](---)


### 演習-Visitor
* 問題
```cpp
    // @@@ exercise/design_pattern_q/visitor.cpp #0:0 begin
```

* 参照 [Visitor](---)
* [解答例-Visitor](---)


### 演習-CRTP
* 問題
```cpp
    // @@@ exercise/design_pattern_q/crtp.cpp #0:0 begin
```

* 参照 [CRTP(curiously recurring template pattern)](---)
* [解答例-CRTP](---)


### 演習-Observer
* 問題
```cpp
    // @@@ exercise/design_pattern_q/observer.cpp #0:0 begin
```

* 参照 [Observer](---)
* [解答例-Observer](---)


### 演習-デザインパターン選択1
* 問題  
  オブジェクトの状態と、
  それに伴う振る舞いを分離して記述する場合に使用されるデザインパターンとは何か？
  下記から選択せよ。

* 選択肢  
    1. Singleton
    2. State
    3. Observer
    4. Null Object

* [解答-デザインパターン選択1](---)


### 演習-デザインパターン選択2
* 問題  
  オブジェクトへのポインタがヌルかどうかを確かめるif文が頻繁に出てくる場合、
  そのif文を無くすために使われるデザインパターンは何か？
  下記から選択せよ。

* 選択肢  
    1. Singleton
    2. State
    3. Observer
    4. Null Object

* [解答-デザインパターン選択2](---)


### 演習-デザインパターン選択3
* 問題  
  MVCアーキテクチャの実現のためによく使われるデザインパターンは何か？
  以下から選択せよ。

* 選択肢  
    1. Singleton
    2. State
    3. Observer
    4. Null Object

* [解答-デザインパターン選択3](---)


## 開発プロセスとインフラ(全般)

### 演習-プロセス分類
* 問題  
  ソフトウェア開発プロセスは(A)、(B)、(C)の3つに分類できる。
  (A)から順に初期計画順守的であり、(C)から逆順に状況適応的である。 
  状況適応的であることは、無計画であることを意味しない。 
  ただ単にプライオリティの問題として、 計画に従うことより状況に適応、
  対処することを選択するということである。  
  (A)、(B)、(C)それぞれにふさわしいものを下記から選べ。

* 選択肢  
    1. ウォーターフォール
    2. 反復型
    3. アジャイル
    4. 無手順

* [解答-プロセス分類](---)


### 演習-V字モデル
* 問題  
  ウォーターフォールモデルもしくはV字モデルと呼ばれるプロセスでは、  
  「フェーズA」→「フェーズB」→「フェーズC」→「フェーズD」→「プログラミング」   
  といった工程でソフトウェアを作り、その後  
  「単体テスト(UT)」→「結合テスト(IT)」→「システムテスト」→「受入テスト(運用テスト)」  
  といった工程でテストを行う。  
  フェーズA、B、C、Dそれぞれにふさわしいものを下記から選べ。


* 選択肢  
    1. 詳細設計
    2. 基本設計
    3. 機能設計
    4. 要件分析

* [解答-V字モデル](---)


### 演習-アジャイル
* 問題  
  アジャイル系プロセスの説明にふさわしくないものを選べ。

* 選択肢  
    1. アジャイル系プロセスとは、敏捷かつ適応的にソフトウェア開発を行う軽量な開発手法群の総称である。
    2. アジャイル系プロセスには計画は必要ない。
    3. ほとんどのアジャイル系プロセスでは、イテレーションを繰り返すことにより開発を進める。
    4. アジャイル系プロセスにはスクラムやXPがある。

* [解答-アジャイル](---)


### 演習-自動化
* 問題  
  一般に、(A)とは、個々のクラスや関数といったソフトウェア構成要素の機能が正確に
  動作することを検証するためのテストを指す。
  原理的には、デバッガ等を利用して(B)で(A)を実行することは可能であるが、  
  「工数が膨大になる」、「テストの(C)が低い」  
  等の問題があるため、現実的ではない。
  自動(A)とは、この問題に対処するためのもので、
  ワンコマンドもしくはワンクリックで(A)を実行するように開発されるプログラムである。  
  (A)、(B)、(C)それぞれにふさわしいものを下記から選べ。

* 選択肢  
    1. 単体テスト
    2. 統合テスト
    3. 自動
    4. 手作業
    5. 再現性
    6. 可塑性

* [解答-自動化](---)


### 演習-単体テスト
* 問題  
  単体テストの説明としてふさわしくないものを選べ。

* 選択肢  
    1. 単体テストで検出可能なバグを、統合テストで検出・デバッグすることは非効率である。
    2. 単体テストが可能なクラス設計には、プログラマのスキルの向上が必要である。
    3. 自動単体テストは工数をほとんどロスすることなしに何度でも実行できるため、
       機能追加、バグ修正、リファクタリング等のソースコード修正後の回帰テストが容易になる。
    4. 単体テストはアジャイル系プロセスのみで使われるテスト手法である。

* [解答-単体テスト](---)


### 演習-リファクタリングに付随する活動
* 問題  
  リファクタリングに付随する活動ではないものを選べ。

* 選択肢  
    1. ソースコードインスペクション
    2. 受入テスト
    3. 回帰テスト
    4. クラス分割

* [解答-リファクタリングに付随する活動](---)


### 演習-リファクタリング対象コード
* 問題  
  リファクタリングの対象とならないソースコードの問題点を下記から選べ。

* 選択肢  
    1. 巨大なクラス
    2. コードクローン
    3. メモリリーク
    4. 間違った依存関係

* [解答-リファクタリング対象コード](---)


### 演習-CI
* 問題  
  CI(継続的インテグレーション)を前提とするプロセスに特徴的な活動すべてを下記から選べ。

* 選択肢  
    1. (svnやgitリポジトリへの)コミット前にコードインスペクションを行う。
    2. リポジトリの最新ソースコードを自動的にビルド、単体テストを行うプログラムの開発や設定を行う。
    3. コミット前に回帰テストを行う。
    4. 開発者全員に共有されているブランチになるべく頻繁にコミットする。

* [解答-CI](---)


## テンプレートメタプログラミング

### 演習-パラメータパック
* 問題
```cpp
    // @@@ exercise/template_q/parameter_pack.cpp #0:0 begin
```

* 参照 [パラメータパック](---)
* [解答例-パラメータパック](---)


### 演習-エイリアステンプレート
* 問題
```cpp
    // @@@ exercise/template_q/template_alias.cpp #0:0 begin
```

* [解答例-エイリアステンプレート](---)


### 演習-名前空間による修飾不要な`operator<<`
* 問題
```cpp
    // @@@ exercise/template_q/put_to.cpp #0:0 begin
```

* 参照 [Ints_tのログ登録](---)、[Ints_tを構造体としてApp内に宣言する](---)、
* [解答例-名前空間による修飾不要な`operator<<`](---)


### 演習-std::arrayの継承
* 問題
```cpp
    // @@@ exercise/template_q/safe_array.cpp #0:0 begin
```

* 参照 [安全な配列型コンテナ](---)
* [解答例-std::arrayの継承](---)


### 演習-SFINAEを利用しない関数テンプレートの特殊化によるis_void
* 問題
```cpp
    // @@@ exercise/template_q/is_void.cpp #0:0 begin
```

* 参照 [is_void_f](---)
* [解答例-SFINAEを利用しない関数テンプレートの特殊化によるis_void](---)


### 演習-SFINAEを利用しないクラステンプレートの特殊化によるis_void
* 問題
    // @@@ exercise/template_q/is_void.cpp #1:0 begin
```cpp
```

* 参照 [is_void_s](---)
* [解答例-SFINAEを利用しないクラステンプレートの特殊化によるis_void](---)


### 演習-SFINAEを利用した関数テンプレートの特殊化によるis_void
* 問題
```cpp
    // @@@ exercise/template_q/is_void.cpp #2:0 begin
```

* 参照 [is_void_sfinae_f](---)
* [解答例-SFINAEを利用した関数テンプレートの特殊化によるis_void](---)


### 演習-SFINAEを利用したクラステンプレートの特殊化によるis_void
* 問題
```cpp
    // @@@ exercise/template_q/is_void.cpp #3:0 begin
```

* 参照 [is_void_sfinae_s](---)
* [解答例-SFINAEを利用したクラステンプレートの特殊化によるis_void](---)


### 演習-テンプレートテンプレートパラメータ
* 問題
```cpp
    // @@@ exercise/template_q/template_template.cpp #0:0 begin
```

* 参照 [is_same_templ](---)
* [解答例-テンプレートテンプレートパラメータ](---)


### 演習-テンプレートパラメータを可変長にしたstd::is_same
* 問題
```cpp
    // @@@ exercise/template_q/is_same.cpp #0:0 begin
```

* 参照 [IsSameSomeOf](---)
* [解答例-テンプレートパラメータを可変長にしたstd::is_same](---)


### 演習-メンバ関数の存在の診断
* 問題
```cpp
    // @@@ exercise/template_q/exists_func.cpp #0:0 begin
```

* 参照 [関数の存在の診断](---)
* [解答例-メンバ関数の存在の診断](---)


### 演習-範囲for文のオペランドになれるかどうかの診断
* 問題
```cpp
    // @@@ exercise/template_q/exists_func.cpp #1:0 begin
```

* 参照 [関数の存在の診断](---)
* [解答例-範囲for文のオペランドになれるかどうかの診断](---)


### 演習-配列の長さの取り出し
* 問題
```cpp
    // @@@ exercise/template_q/array_op.cpp #0:0 begin
```

* 参照 [関数の存在の診断](---)
* [解答例-配列の長さの取り出し](---)


### 演習-配列の次元の取り出し
* 問題
```cpp
    // @@@ exercise/template_q/array_op.cpp #1:0 begin
```

* 参照 [ValueTypeの実装](---)
* [解答例-配列の次元の取り出し](---)


### 演習-関数型のテンプレートパラメータを持つクラステンプレート
* 問題
```cpp
    // @@@ exercise/template_q/scoped_guard.cpp #0:0 begin
```

* 参照 [関数型をテンプレートパラメータで使う](---)
* [解答例-関数型のテンプレートパラメータを持つクラステンプレート](---)


