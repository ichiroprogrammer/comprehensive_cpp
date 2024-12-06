# 解答

__この章の構成__

<!-- index 1-2 -->
  
[このドキュメントの構成](---)に戻る。  

___

## プログラミング規約(型)

### 解答-汎整数型の選択
* 選択肢3
* 参照 [プログラミング規約|型とインスタンス|算術型](---)
* 解説  
  代入する小さい整数に合わせて8ビット型や16ビット型を使うと、
  それら同士の演算時にint昇格が起こり、わかりづらいバグを生むことがある。  
  int32_tを使うことは、
  ほとんどのコンパイラでint32_tの実際の型がintであることを利用しているため、
  その前提を避けるべきと考えるのであれば、int32_tの代わりにint、
  uint32_tの代わりにunsigned intを使用すればよい。

* [演習-汎整数型の選択](---)へ戻る。


### 解答例-汎整数型の演算
```cpp
    // @@@ exercise/programming_convention_a/type.cpp #0:0 begin
```

* [演習-汎整数型の演算](---)へ戻る。


### 解答例-浮動小数点型
```cpp
    // @@@ exercise/programming_convention_a/type.cpp #1:0 begin
```

* [演習-浮動小数点型](---)へ戻る。


### 解答-定数列挙
* 選択肢4
* 参照 [用語解説|enum](---)
* [演習-定数列挙](---)へ戻る。


### 解答例-enum
```cpp
    // @@@ exercise/programming_convention_a/type.cpp #2:0 begin
```

* [演習-enum](---)へ戻る。


### 解答例-配列の範囲for文
```cpp
    // @@@ exercise/programming_convention_a/type.cpp #3:0 begin
```

* [演習-配列の範囲for文](---)へ戻る。


### 解答例-エイリアス
```cpp
    // @@@ exercise/programming_convention_a/type.cpp #4:0 begin
```

* [演習-エイリアス](---)へ戻る。


### 解答-constの意味
* 選択肢1
* 参照 [const/constexprインスタンス](---)
* [演習-constの意味](---)へ戻る。


### 解答例-const/constexpr
```cpp
    // @@@ exercise/programming_convention_a/type.cpp #5:0 begin
```

* [演習-const/constexpr](---)へ戻る。


### 解答例-危険なconst_cast
```cpp
    // @@@ exercise/programming_convention_a/type.cpp #6:0 begin
```

* [演習-危険なconst_cast](---)へ戻る。


### 解答例-リテラル
```cpp
    // @@@ exercise/programming_convention_a/type.cpp #7:0 begin
```

* [演習-リテラル](---)へ戻る。


### 解答-適切なautoの使い方
* 選択肢4
* 参照 [auto](---)
* [演習-適切なautoの使い方](---)へ戻る。


### 解答-ポインタの初期化
* 選択肢3
* 参照 [用語解説|リテラル](---)
* [演習-ポインタの初期化](---)へ戻る。


### 解答-vector初期化
* 選択肢1
* 参照 [インスタンスの初期化](---)
* [演習-vector初期化](---)へ戻る。


### 解答例-インスタンスの初期化
```cpp
    // @@@ exercise/programming_convention_a/type.cpp #8:0 begin
```

* [演習-インスタンスの初期化](---)へ戻る。


## プログラミング規約(クラス)

### 解答-凝集度の意味
* 選択肢4
* 参照 [クラスの規模|凝集度](---)
* [演習-凝集度の意味](---)へ戻る。


### 解答例-凝集度の向上
```cpp
    // @@@ exercise/programming_convention_a/class.cpp #0:0 begin
```

* [演習-凝集度の向上](---)へ戻る。


### 解答-メンバ変数の初期化方法の選択
* 選択肢2
* 参照 [非静的なメンバ変数](---)
* [演習-メンバ変数の初期化方法の選択](---)へ戻る。


### 解答-メンバの型
* 選択肢3
* 参照 [インスタンスの初期化](---)
* 解説  
  関数の宣言と、クラスのデフォルトコンストラクタ呼び出しによるオブジェクトの生成は、
  プログラマを混乱させることがあるので注意が必要である。
* [演習-メンバの型](---)へ戻る。


### 解答例-メンバ変数の初期化
```cpp
    // @@@ exercise/programming_convention_a/class.cpp #1:0 begin
```

* [演習-メンバ変数の初期化](---)へ戻る。


### 解答例-スライシング
```cpp
    // @@@ exercise/programming_convention_a/class.cpp #2:0 begin
```

* [演習-スライシング](---)へ戻る。


### 解答例-オブジェクトの所有権
```cpp
    // @@@ exercise/programming_convention_a/class.cpp #3:0 begin
```

* [演習-オブジェクトの所有権](---)へ戻る。


## プログラミング規約(関数)
### 解答例-非メンバ関数の宣言
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #0:0 begin
```

* [演習-非メンバ関数の宣言](---)へ戻る。


### 解答例-メンバ関数の修飾
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #1:0 begin
```

* [演習-メンバ関数の修飾](---)へ戻る。


### 解答例-特殊メンバ関数の削除
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #2:0 begin
```

* [演習-特殊メンバ関数の削除](---)へ戻る。


### 解答例-委譲コンストラクタ
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #3:0 begin
```

* [演習-委譲コンストラクタ](---)へ戻る。


### 解答例-copyコンストラクタ
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #4:0 begin
```

* [演習-copyコンストラクタ](---)へ戻る。


### 解答例-moveコンストラクタ
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #5:0 begin
```

* [演習-moveコンストラクタ](---)へ戻る。


### 解答例-関数分割
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #6:0 begin
```

* [演習-関数分割](---)へ戻る。


### 解答-オーバーライド関数の修飾
* 選択肢2
* 参照 [オーバーライド](---)
* [演習-オーバーライド関数の修飾](---)へ戻る。


### 解答例-オーバーライド/オーバーロード
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #7:0 begin
```

* [演習-オーバーライド/オーバーロード](---)へ戻る。


### 解答例-オーバーロードによる誤用防止
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #8:0 begin
```

* [演習-オーバーロードによる誤用防止](---)へ戻る。


### 解答例-仮引数の修飾
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #9:0 begin
```

* [演習-仮引数の修飾](---)へ戻る。


### 解答例-constexpr関数
```cpp
    // @@@ exercise/programming_convention_a/func.cpp #10:0 begin
```

* [演習-constexpr関数](---)へ戻る。


### 解答-エクセプションの型
* 選択肢2
* 参照 [エクセプション処理](---)
* 解説  
  下記3つを統合して考えれば、必然的に「選択肢2」であることがわかる。
    * エクセプションでthrowされるオブジェクトのポインタがnullptrになることはない。
    * throwされたオブジェクトのスライスは当然避けるべきである。
    * throwされたオブジェクトを直接修正すべきでない。
* [演習-エクセプションの型](---)へ戻る。


## プログラミング規約(構文)

### 解答例-コンテナの範囲for文
```cpp
    // @@@ exercise/programming_convention_a/syntax.cpp #0:0 begin
```

* [演習-コンテナの範囲for文](---)へ戻る。


### 解答例-ラムダ式
```cpp
    // @@@ exercise/programming_convention_a/syntax.cpp #1:0 begin
```

* [演習-ラムダ式](---)へ戻る。


### 解答例-ラムダ式のキャプチャ
```cpp
    // @@@ exercise/programming_convention_a/syntax.cpp #2:0 begin
```

* [演習-ラムダ式のキャプチャ](---)へ戻る。


## プログラミング規約(演算子)

### 解答例-条件演算子
```cpp
    // @@@ exercise/programming_convention_a/operator.cpp #0:0 begin
```

* [演習-条件演算子](---)へ戻る。

### 解答例-delete
```cpp
    // @@@ exercise/programming_convention_a/operator.cpp #1:0 begin
```

* [演習-delete](---)へ戻る。

### 解答例-sizeof
```cpp
    // @@@ exercise/programming_convention_a/operator.cpp #2:0 begin
```

* [演習-sizeof](---)へ戻る。


### 解答例-dynamic_castの削除
```cpp
    // @@@ exercise/programming_convention_a/operator.cpp #3:0 begin
```

* [演習-dynamic_castの削除](---)へ戻る。


### 解答-キャスト
* 選択肢3  
* 参照 [キャスト、暗黙の型変換](---)
* 解説  
  reinterpret_castも避けるべきであるが、組み込みソフト等でのハードウエアアドレスの記述等には、
  使わざるを得ない。
* [演習-キャスト](---)へ戻る。


## プログラミング規約(スコープ)

### 解答-usingディレクティブ
* 選択肢1
* 参照 [using宣言/usingディレクティブ](---)
* [演習-usingディレクティブ](---)へ戻る。


## プログラミング規約(その他)

### 解答-アサーションの選択
* 選択肢1
* 参照 [assertion](---)
* [演習-アサーションの選択](---)へ戻る。


### 解答例-assert/static_assert
```cpp
    // @@@ exercise/programming_convention_a/etc.cpp #0:0 begin
```

* [演習-assert/static_assert](---)へ戻る。


## SOLID
### 解答例-SRP
```cpp
    // @@@ exercise/solid_a/srp_test_score.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/srp_test_score.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/srp_test_score_ut.cpp #0:0 begin
```

* [演習-SRP](---)へ戻る。


### 解答例-OCP
```cpp
    // @@@ exercise/solid_a/ocp_test_score.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/ocp_test_score.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/ocp_test_score_ut.cpp #0:0 begin
```

* [演習-OCP](---)へ戻る。


### 解答例-LSP
```cpp
    // @@@ exercise/solid_a/lsp_test_score.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/lsp_test_score.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/lsp_test_score_ut.cpp #0:0 begin
```

* [演習-LSP](---)へ戻る。


### 解答例-ISP
```cpp
    // @@@ exercise/solid_a/isp_test_score_average.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/isp_test_score.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/isp_test_score_average.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/isp_test_score.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/isp_test_score_average_ut.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/isp_test_score_ut.cpp #0:0 begin
```

* [演習-ISP](---)へ戻る。


### 解答例-DIP
```cpp
    // @@@ exercise/solid_a/dip_test_score.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/dip_test_score.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/dip_test_score_ut.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/dip_test_score_client.h #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/dip_test_score_client.cpp #0:0 begin
```
```cpp
    // @@@ exercise/solid_a/dip_test_score_client_ut.cpp #0:0 begin
```

* [演習-DIP](---)へ戻る。


### 解答-SOLIDの定義
* 選択肢対応
    * SRP - 1
    * OCP - 2
    * LIP - 3
    * ISP - 4
    * DIP - 5

* 参照 [|SOLID](---)
* [演習-SOLIDの定義](---)へ戻る。


## デザインパターン
### 解答例-ガード節
```cpp
    // @@@ exercise/design_pattern_a/guard.cpp #0:0 begin
```

* [演習-ガード節](---)へ戻る。


### 解答例-BitmaskType
```cpp
    // @@@ exercise/design_pattern_a/enum_bitmask.cpp #0:0 begin
```

* [演習-BitmaskType](---)へ戻る。


### 解答例-Pimpl
```cpp
    // @@@ exercise/design_pattern_a/pimpl.cpp #0:0 begin
```

* [演習-Pimpl](---)へ戻る。


### 解答-Accessorの副作用
* 選択肢1
* 参照 [Accessor](---)
* [演習-Accessorの副作用](---)へ戻る。


### 解答例-Accessor
```cpp
    // @@@ exercise/design_pattern_a/accessor.cpp #0:0 begin
```

* [演習-Accessor](---)へ戻る。


### 解答例-Copy-And-Swap
```cpp
    // @@@ exercise/design_pattern_a/copy_and_swap.cpp #0:0 begin
```

* [演習-Copy-And-Swap](---)へ戻る。


### 解答例-Immutable
```cpp
    // @@@ exercise/design_pattern_a/immutable.cpp #0:0 begin
```

* [演習-Immutable](---)へ戻る。


### 解答例-Clone
```cpp
    // @@@ exercise/design_pattern_a/clone.cpp #0:0 begin
```

* [演習-Clone](---)へ戻る。


### 解答例-NVI
```cpp
    // @@@ exercise/design_pattern_a/nvi.cpp #0:0 begin
```

* [演習-NVI](---)へ戻る。


### 解答-RAIIの効果
* 選択肢1
* 参照 [RAII(scoped guard)](---)
* [演習-RAIIの効果](---)へ戻る。


### 解答例-RAII
```cpp
    // @@@ exercise/design_pattern_a/raii.cpp #0:0 begin
```

* [演習-RAII](---)へ戻る。


### 解答例-Future
```cpp
    // @@@ exercise/design_pattern_a/future.cpp #0:0 begin
```

* [演習-Future](---)へ戻る。


### 解答例-DI
```cpp
    // @@@ exercise/design_pattern_a/di.cpp #0:0 begin
```

* [演習-DI](---)へ戻る。


### 解答例-Singleton
```cpp
    // @@@ exercise/design_pattern_a/singleton.cpp #0:0 begin
```

* [演習-Singleton](---)へ戻る。


### 解答例-State
```cpp
    // @@@ exercise/design_pattern_a/state.cpp #0:0 begin
```

* [演習-State](---)へ戻る。


### 解答例-Null Object
```cpp
    // @@@ exercise/design_pattern_a/null_object.cpp #0:0 begin
```

* [演習-Null Object](---)へ戻る。


### 解答例-Templateメソッド
```cpp
    // @@@ exercise/design_pattern_a/template_method.cpp #0:0 begin
```

* [演習-Templateメソッド](---)へ戻る。


### 解答例-Factory
```cpp
    // @@@ exercise/design_pattern_a/factory_lib.h #0:0 begin
```
```cpp
    // @@@ exercise/design_pattern_a/factory_lib.cpp #0:0 begin
```
```cpp
    // @@@ exercise/design_pattern_a/factory.cpp #0:0 begin
```

* [演習-Factory](---)へ戻る。


### 解答例-Named Constructor
```cpp
    // @@@ exercise/design_pattern_a/named_constructor_lib.h #0:0 begin
```
```cpp
    // @@@ exercise/design_pattern_a/named_constructor_lib.cpp #0:0 begin
```
```cpp
    // @@@ exercise/design_pattern_a/named_constructor.cpp #0:0 begin
```

* [演習-Named Constructor](---)へ戻る。


### 解答例-Proxy
```cpp
    // @@@ exercise/design_pattern_a/proxy.cpp #0:0 begin
```

* [演習-Proxy](---)へ戻る。


### 解答例-Strategy
```cpp
    // @@@ exercise/design_pattern_a/strategy.cpp #0:0 begin
```

* [演習-Strategy](---)へ戻る。


### 解答例-Visitor
```cpp
    // @@@ exercise/design_pattern_a/visitor.cpp #0:0 begin
```

* [演習-Visitor](---)へ戻る。


### 解答例-CRTP
```cpp
    // @@@ exercise/design_pattern_a/crtp.cpp #0:0 begin
```

* [演習-CRTP](---)へ戻る。


### 解答例-Observer
```cpp
    // @@@ exercise/design_pattern_a/observer.cpp #0:0 begin
```

* [演習-Observer](---)へ戻る。


### 解答-デザインパターン選択1
* 選択肢2
* 参照 [State](---)
* [演習-デザインパターン選択1](---)へ戻る。


### 解答-デザインパターン選択2
* 選択肢4
* 参照 [Null Object](---)
* [演習-デザインパターン選択2](---)へ戻る。


### 解答-デザインパターン選択3
* 選択肢3
* 参照 [Observer](---)
* [演習-デザインパターン選択3](---)へ戻る。


## 開発プロセスとインフラ(全般)

### 解答-プロセス分類
* 選択肢対応
    * A - 1
    * B - 2
    * C - 3

* 参照 [開発プロセスとインフラ|プロセス](---)
* [演習-プロセス分類](---)へ戻る。


### 解答-V字モデル
* 選択肢対応
    * フェーズA - 4
    * フェーズB - 2
    * フェーズC - 3
    * フェーズD - 1

* 参照 [ウォーターフォールモデル、V字モデル](---)
* [演習-V字モデル](---)へ戻る。


### 解答-アジャイル
* 選択肢2
* 参照 [アジャイル系プロセス](---)
* [演習-アジャイル](---)へ戻る。


### 解答-自動化
* 選択肢対応
    * A - 1
    * B - 4
    * C - 5

* 参照 [自動単体テスト](---)
* [演習-自動化](---)へ戻る。


### 解答-単体テスト
* 選択肢4
* 参照 [自動単体テスト](---)
* [演習-単体テスト](---)へ戻る。


### 解答-リファクタリングに付随する活動
* 選択肢2
* 参照 [リファクタリング](---)
* [演習-リファクタリングに付随する活動](---)へ戻る。


### 解答-リファクタリング対象コード
* 選択肢3
* 参照 [リファクタリング](---)
* [演習-リファクタリング対象コード](---)へ戻る。


### 解答-CI
* 選択肢2, 4
* 参照 [CI(継続的インテグレーション)](---)
* [演習-CI](---)へ戻る。


## テンプレートメタプログラミング
### 解答例-パラメータパック
```cpp
    // @@@ exercise/template_a/parameter_pack.cpp #0:0 begin
```

* [演習-パラメータパック](---)へ戻る。


### 解答例-エイリアステンプレート
```cpp
    // @@@ exercise/template_a/template_alias.cpp #0:0 begin
```

* [演習-エイリアステンプレート](---)へ戻る。


### 解答例-名前空間による修飾不要な`operator<<`
```cpp
    // @@@ exercise/template_a/put_to.cpp #0:0 begin
```

* [演習-名前空間による修飾不要な`operator<<`](---)へ戻る。


### 解答例-std::arrayの継承
```cpp
    // @@@ exercise/template_a/safe_array.cpp #0:0 begin
```

* [演習-std::arrayの継承](---)へ戻る。


### 解答例-SFINAEを利用しない関数テンプレートの特殊化によるis_void
```cpp
    // @@@ exercise/template_a/is_void.cpp #0:0 begin
```

* [演習-SFINAEを利用しない関数テンプレートの特殊化によるis_void](---)へ戻る。


### 解答例-SFINAEを利用しないクラステンプレートの特殊化によるis_void
```cpp
    // @@@ exercise/template_a/is_void.cpp #1:0 begin
```

* [演習-SFINAEを利用しないクラステンプレートの特殊化によるis_void](---)へ戻る。


### 解答例-SFINAEを利用した関数テンプレートの特殊化によるis_void
```cpp
    // @@@ exercise/template_a/is_void.cpp #2:0 begin
```

* [演習-SFINAEを利用した関数テンプレートの特殊化によるis_void](---)へ戻る。


### 解答例-SFINAEを利用したクラステンプレートの特殊化によるis_void
```cpp
    // @@@ exercise/template_a/is_void.cpp #3:0 begin
```

* [演習-SFINAEを利用したクラステンプレートの特殊化によるis_void](---)へ戻る。


### 解答例-テンプレートテンプレートパラメータ
```cpp
    // @@@ exercise/template_a/template_template.cpp #0:0 begin
```

* [演習-テンプレートテンプレートパラメータ](---)へ戻る。


### 解答例-テンプレートパラメータを可変長にしたstd::is_same
```cpp
    // @@@ exercise/template_a/is_same.cpp #0:0 begin
```

* [演習-テンプレートパラメータを可変長にしたstd::is_same](---)へ戻る。


### 解答例-メンバ関数の存在の診断
```cpp
    // @@@ exercise/template_a/exists_func.cpp #0:0 begin
```

* [演習-メンバ関数の存在の診断](---)へ戻る。


### 解答例-範囲for文のオペランドになれるかどうかの診断
```cpp
    // @@@ exercise/template_a/exists_func.cpp #1:0 begin
```

* [演習-範囲for文のオペランドになれるかどうかの診断](---)へ戻る。


### 解答例-配列の長さの取り出し
```cpp
    // @@@ exercise/template_a/array_op.cpp #0:0 begin
```

* [演習-配列の長さの取り出し](---)へ戻る。


### 解答例-配列の次元の取り出し
```cpp
    // @@@ exercise/template_a/array_op.cpp #1:0 begin
```

* [演習-配列の次元の取り出し](---)へ戻る。


### 解答例-関数型のテンプレートパラメータを持つクラステンプレート
```cpp
    // @@@ exercise/template_a/scoped_guard.cpp #0:0 begin
```

* [演習-関数型のテンプレートパラメータを持つクラステンプレート](---)へ戻る。


