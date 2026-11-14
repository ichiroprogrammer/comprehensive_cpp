# リファクタリングの例
ソースコードに多くの問題があった場合でも、一度に多くの視点からの修正をしてはならない。
ステップバイステップで少しずつ改善させることを心掛けるべきである。

例えば大きすぎる関数を分割するリファクタリングを行う場合は、その分割のみに集中すべきで、
その最中に別の問題を見つけても、その修正を行ってはならない。
まずは、仕掛中のリファクタリングを終了させ、その後(コミットした後)、次の問題点に取り掛かるべきである。

以下では、そういったステップバイステップのリファクタリングを例示する。

___

__この章の構成__

<!-- index 1-4 -->

___


[インデックス](---) <!-- ss_end / -->

___


## オリジナルのソースコード
まずはリファクタリング前のオリジナルのソースコードを示す。

```cpp
    // @@@ example/ref_org/main.cpp #0:0 begin
```

上記プログラムは、

1. 標準入力から文字列を受け取り、
2. 文字列をパースし、コマンドと引数文字列に分離し、
3. 引数文字列を、時間のかかるアルゴリズムで別の文字列に変換し、
4. 変換文字列を保存し、
5. 保存した全ての変換文字列をstd::coutに出力する。

ソースコードの品質は高くないので、
すくなくとも機能追加するタイミングではリファクタリングが必要になる。

## 機能追加によるソースコード品質劣化
時間のかかるアルゴリズムがプログラムをブロックしてしまうので、
下記のように、この処理を(不十分ながら)非同期化した。

```cpp
    // @@@ example/ref_async_org/main.cpp #0:0 begin
```

一般に、同期処理をそのまま非同期に変更するとソースコードは腐敗を始める。
上記ソースコードもその例に漏れず、かなり醜悪になった。

## 小規模なリファクタリング
Null ObjectパターンやRAIIの導入で肥大化したmain関数を改善する小規模なリファクタリングを行う。

```cpp
    // @@@ example/ref_async_r0/main.cpp #0:0 begin
```

上記例のScopedGuardは、汎用性が高くプロジェクト全体で使用できるため、別のファイルとして、
下記のように宣言、定義する(汎用性が高いクラスや関数をプロジェクト全体で共有することは良い習慣である)。

```cpp
    // @@@ essential/h/scoped_guard.h #0:0 begin
    // @@@ essential/h/scoped_guard.h #0:1 begin
    // @@@ essential/h/scoped_guard.h #0:2 begin
```

## 構造のリファクタリング
前記レベルでは不十分であるため、ブロックを関数化するリファクタリングを行う。

```cpp
    // @@@ example/ref_async_r1/main.cpp #0:0 begin
```

メインループ関数は、main()と同じファイルに残すが、他の関数は下記のように他のファイルで定義する。
これにより、部分的だが単体テストが導入できる。

```cpp
    // @@@ example/ref_async_r1/lib.cpp #0:0 begin
```

## 単体テストの開発
前述したように、関数やファイルを分割したことにより、
不十分なレベルではあるが単体テストを開発、実行できるようになった。

```cpp
    // @@@ example/ref_async_r1/lib_ut.cpp #0:0 begin
```

scoped_guard.hに関しても単体テストを追加するべきである。
このような単純なクラスに対して単体テストを行うことは一見無駄なように思えるかもしれないが、
単体テストカバレッジの管理、
「[割れ窓理論](https://ja.wikipedia.org/wiki/%E5%89%B2%E3%82%8C%E7%AA%93%E7%90%86%E8%AB%96)」
等の観点から重要である。

```cpp
    // @@@ example/ref_async_r1/scoped_guard_ut.cpp #0:0 begin
```

## クラスの導入
このプログラムは非同期処理が必要であるため、
そういったアプリケーションとの相性が良い[MVC](---)の導入によるリファクタリングを行う
(この程度の規模のソフトウェアにMVCを導入する必要はないが、
その導入を例示するためリファクタリングを行う)。

まずは、コマンドの非同期処理を行うクラス(== ビジネスロジック == Model)を導入する
(例としての分かりやすさを優先するためにクラス名もModelとする)。

```cpp
    // @@@ example/ref_async_r2/main.cpp #0:0 begin
```

以下のファイルで、Modelの宣言、定義を行う。

```cpp
    // @@@ example/ref_async_r2/lib.h #0:0 begin
```

```cpp
    // @@@ example/ref_async_r2/lib.cpp #0:0 begin
```

## 単体テストの変更
このリファクタリングにより単体テストは以下のようになる
(以下のModelのデザインは不十分であるため、妥当な単体テストはできない)。

```cpp
    // @@@ example/ref_async_r2/lib_ut.cpp #0:0 begin
```

## MVCの導入
非同期関数であるModel::ConvertStoreAsync()の完了がクラス外から捕捉できないことを一因として、
上記例のModelへの十分な単体テストができなかった。
この問題を解決し、単体テストのカバレッジを上げるために「[MVC](---)」の構造を導入する。

```cpp
    // @@@ example/ref_async_r3/main.cpp #0:0 begin
```

以下のファイルで、Modelの宣言、定義を行う。

```cpp
    // @@@ example/ref_async_r3/model.h #0:0 begin
```

```cpp
    // @@@ example/ref_async_r3/model.cpp #0:0 begin
```

以下のファイルで、Viewの宣言、定義を行う。

```cpp
    // @@@ example/ref_async_r3/view.h #0:0 begin
```

```cpp
    // @@@ example/ref_async_r3/view.cpp #0:0 begin
```

以下のファイルで、Controllerの宣言、定義を行う。

```cpp
    // @@@ example/ref_async_r3/controller.h #0:0 begin
```

```cpp
    // @@@ example/ref_async_r3/controller.cpp #0:0 begin
```

## 単体テストの変更(単体テスト用クラス導入)
Observerから派生した下記のテスト用クラスViewTestを使うことにより、
ConvertStoreAsync()の完了が捕捉できるようになった。

```cpp
    // @@@ example/h/ref_async_mock.h #0:0 begin
```

これにより、Modelの単体テストは十分なレベルになったが、
下記の通り、ControllerやViewがstd::coutやstd::cinに依存しているために、
これらの単体テストの開発は困難である。

```cpp
    // @@@ example/ref_async_r3/model_ut.cpp #0:0 begin
```

```cpp
    // @@@ example/ref_async_r3/view_ut.cpp #0:0 begin
```

```cpp
    // @@@ example/ref_async_r3/controller_ut.cpp #0:0 begin
```

## DIの導入
[DI(dependency injection)](---)を導入することで、
Controller、Viewのstd::coutやstd::cinへの直接の依存を回避する。

下図は、DI導入前後でControllerによる「std::cinからの文字列読み込み」がどのように変更されたかを示す。

![シーケンス図](plant_uml/refactoring_with_di.png)

DIの導入によりmain()は以下のようになる。

```cpp
    // @@@ example/ref_async_r4/main.cpp #0:0 begin
```

Modelについては、std::cout、std::cinへの依存はないので変更しない。
Viewについては、以下のようにstd::coutへの依存を削除する。

```cpp
    // @@@ example/ref_async_r4/view.h #0:0 begin
```

```cpp
    // @@@ example/ref_async_r4/view.cpp #0:0 begin
```

Controllerについても、以下のようにstd::cinへの依存を削除する。

```cpp
    // @@@ example/ref_async_r4/controller.h #0:0 begin
```

```cpp
    // @@@ example/ref_async_r4/controller.cpp #0:0 begin
```

以上のように、

* Controllerは、インスタンスstd::cinへの依存から、std::istream型への依存へ
* Viewは、インスタンスstd::coutへの依存から、std::ostream型への依存へ

と改善された(一般にグローバルオブジェクトへの依存よりも型への依存の方が柔軟性に勝る)。
なお、std::cin、std::cout、std::istream、std::ostream等の継承関係は以下の通りであるため、
このような変更が可能となった。

![basic ios クラス図](plant_uml/basic_ios.png)

## 全クラスの単体テスト
これまでの改善によりModel、View、Controllerすべてに妥当な単体テストをすることが可能となった。

```cpp
    // @@@ example/ref_async_r4/model_ut.cpp #0:0 begin
```

```cpp
    // @@@ example/ref_async_r4/view_ut.cpp #0:0 begin
```

```cpp
    // @@@ example/ref_async_r4/controller_ut.cpp #0:0 begin
```

## 自動統合テストのための仕様追加
リファクタリングの説明に使用したソースコード(「[リファクタリング](---)」参照)は、

* 複数の小さなファイルに分割され、
* MVC構造を導入され、
* すべてのクラスは十分にコンパクトで、
* すべてのクラスは単体テストを実行できる

ように改善された。
単体テストのラインカバレッジは100％に近く、動作品質という観点からも改善したが、
未だに統合テストは手作業で行わなければならない(現在の仕様では統合テストを自動化することは難しい)。

このプログラムの統合テストの自動化を難しくさせている原因は、
「標準入出力を利用し、ユーザとインタラクティブなやり取りを行う」
からである。この問題を解決するために、
「コマンド引数によりダイナミックに、標準入出力をファイル入出力へ切り替えられる」ように変更を行う
(このようなテスト機能の実現のために、#if/#endif等のプリプロセッサ命令を利用することは誤りである)。

コマンド引数の仕様(このプログラム名はref_async_r5)は下記のとおりである。

```
    ref_async_r5 [OPTIONS]
       -i <input-file>      std::cinの代わりに、<input-file>を使用する。
       -o <output-file>     std::coutの代わりに、<output-file>を使用する。
```

## 自動統合テストのためのソースコード変更
前述したオプションを備えた実装は、以下のようになる。

```cpp
    // @@@ example/ref_async_r5/main.cpp #0:0 begin
```
```cpp
    // @@@ example/ref_async_r5/arg.h #0:0 begin
```
```cpp
    // @@@ example/ref_async_r5/arg.cpp #0:0 begin
```

IOStreamSelectorと単体テスト用に導入した「[DI(dependency injection)](---)」構造により、
std::istream、std::ostreamのインスタンスを選択できるようになった。

IOStreamSelectorは以下のようになる。

```cpp
    // @@@ example/ref_async_r5/arg.h #0:1 begin
```
```cpp
    // @@@ example/ref_async_r5/arg.cpp #0:1 begin
```

## 自動統合テスト用ソースコード変更のための単体テスト
追加機能に対する単体テストを以下に示す。
なお、新規単体テストはファイルの生成、書き込み、読み込みを行うため、

* 単体テストの実行前に、結果に影響を与えるファイルを削除する
* 単体テストの実行後に、単体テストで生成したファイルを削除する

を行う必要がある。

* 前者を行うのがSetUp()
* 後者を行うのがTearDown()

である。

```cpp
    // @@@ example/ref_async_r5/arg_ut.cpp #0:0 begin
```

## 自動統合テストの実装
ref_async_r5に追加された機能をスクリプト言語(下記例ではbash)等から利用することで、
下記のような自動統合テスト(非手作業統合テスト)を開発することができる。
入力文字列や入力タイミングのバリエーションを増やすこと等によってこの方法を発展させれば、
堅固な自動統合テストにすることも可能である。

```sh
    // @@@ example/ref_it/it.sh #0:0 begin
```

---

[インデックス](---) <!-- ss_top / -->

---



