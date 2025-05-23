# 開発プロセスとインフラ
ソフトウェア開発を効率よく行うためには、以下の三要素をレベル高く保つことが重要である。

* プログラマ
* 開発プロセス(以下、単にプロセスと呼ぶ)
* 開発をサポートするためのインフラ(以下、単にインフラと呼ぶ)

この章では後ろ２つの要素(プロセスとそれを支えるインフラ)について、
アジャイル、CIに軸足を置いて説明する。

___

__この章の構成__

<!-- index 1-3 -->

[このドキュメントの構成](---)に戻る。  

___

## プロセス
本ドキュメントでは、プロセスを下記の3つに分類する。

* [ウォーターフォールモデル、V字モデル](---)
* 反復型
* [アジャイル系プロセス](---)

上から順に初期計画順守的であり、逆に下から順に状況適応的である。
状況適応的であることは、無計画であることを意味しない。
ただ単にプライオリティの問題として、
計画に従うことより状況に適応・対処することを選択するということである。

ほとんどのアジャイル系のプロセスは、繰り返し構造を持つため、
「アジャイル ⊆ 反復型」と分類されることもある(が、本ドキュメントではそうしない)。

### ウォーターフォールモデル、V字モデル
ウォーターフォールモデルもしくはV字モデルと呼ばれるプロセスでは、
「要件分析」→「基本設計」→「機能設計」→「詳細設計」→「プログラミング」
といった工程でソフトウェアを作り、その後
「単体テスト(UT)」→「結合テスト(IT)」→「システムテスト」→「受入テスト(運用テスト)」
といった工程でテストを行う。

![v-model](plant_uml/v_model.png)

設計・開発の各フェーズ(上図の左側)は、同じ高さにあるテストの各フェーズ
(上図の右側)にそれぞれ対応する。
ソフトウェアの機能はそれが定義された設計・開発フェーズに対応するテストフェーズで評価される。

設計・開発フェーズではトップダウンで作業を行うことで実装漏れや手戻りを防ぎ、
テストフェーズではその逆にボトムアップで作業を行うことにより、
細かいバグによる全体進捗の妨げを防ぐことを意図している。

長い歴史を持った手法であるため、安定したプロセスであるが、下記するような問題を持っている。

* プロダクトへの学習が進んでないプロジェクト初期に、
  下記のようなリスクの高い意思決定をせざるを得ない。
    * プロジェクトの計画
    * [アーキテクチャの設計](---)

* 設計・開発フェーズでの手戻りを無くすために多くのレビューを繰り返すが、
  多くの仕様上のバグは実装時に発見される(実装することで仕様バグは発見しやすくなる)。
* 設計・開発の各フェーズで一定以上のバグが見つかった場合、
  そのフェーズを中止し、前のフェーズに戻らなければならい。
  これにはコストがかかりすぎるため、このルールの順守は容易ではない。
* 自然言語やコンピュータ言語、数式等を使って以下のようなソフトウェアを仕様化することや、
  その仕様書をレビューすることは困難である。
    * ルック&フィールが重要なリッチなGUI
    * トライ&エラーを繰り返しながら開発するアルゴリズム  

* ソフトウェア開発は短くても数か月必要であるため、その間に要求仕様が不変であることは稀であり、
  開発途中での仕様変更は避けがたいが、このプロセスに従った要求仕様の変更、
  追加はコストがかかりすぎるため現実的には不可能である。
* 要求仕様の変更、追加が困難であるため、プロジェクトの初期に必要性の不確かな機能が大量に要求される。
* 実装が終わるのは通常全体日程の7割～8割を消化した頃である。
  その時期まで開発の進捗や品質はわからない。
  わかるのは「消費した工数」と、「希望的観測により作られた進捗率」である。

### アジャイル系プロセス
アジャイル系プロセスとは、
敏捷(==agile)かつ適応的にソフトウェア開発を行う軽量な開発手法群の総称である。

以前、アジャイルが意味するものは誤用・乱用され、今もってその状態が解消されたとは言い難いため、
あえて下記の通り注意喚起する。

* 無計画なソフトウェア開発はアジャイルではない。
* [カウボーイコーディング](https://ja.wikipedia.org/wiki/%E3%82%A2%E3%82%B8%E3%83%A3%E3%82%A4%E3%83%AB%E3%82%BD%E3%83%95%E3%83%88%E3%82%A6%E3%82%A7%E3%82%A2%E9%96%8B%E7%99%BA#%E3%82%AB%E3%82%A6%E3%83%9C%E3%83%BC%E3%82%A4%E3%82%B3%E3%83%BC%E3%83%87%E3%82%A3%E3%83%B3%E3%82%B0)
  はアジャイルでない。
* 要求変更を受け入れるだけではアジャイルではない。
* アジャイルは、フレデリック・ブルックスがいうところの「銀の弾」ではない。

英単語の「agile(アジャイル)」には「繰り返し」という意味は含まれていないが、
実際には、その代表格であるスクラムやXPを含め、ほとんどのアジャイル系プロセスは、
下記のような繰り返し(イテレーション)構造を持つ。

![アジャイルプロセス例](plant_uml/agile.png)

こういったプロセスは、ウォーターフォールが持つ欠点への反省と克服のために作られた(と言って良い)ため、
多くのウォーターフォールの欠点を軽減、回避しているが、
一方でウォーターフォールが持っていない下記のような欠点を持っている。

* 比較的小さいプロジェクトに向いている(大規模プロジェクトでは難しい)。
* 要求仕様の全項目の完了時期を約束しない
  (ウォーターフォールでは約束するが、約束が守られるとは限らない。
  また、無理に守ろうとするため、しばしばデスマーチが発生し、返って完成が遅れる)。
* ほとんどのアジャイル系プロセスは、
  チームが様々なサブプロセスやプラクティスを実行することを前提としている。
* プログラマが多能工であることを前提している。
    * 要求分析→設計→コーディング→単体テスト(UT)→統合テスト(IT)を各人ができなければならない。
    * 各人は、プロダクト開発言語のみではなく、
      単体テストフレームワークや各種自動化用言語を理解する必要がある。

### ウォーターフォール vs アジャイル
ウォーターフォールとアジャイルの対比を下記する。

|                |ウォーターフォール          |アジャイル                        |
|:---------------|:--------------------------:|:--------------------------------:|
|計画            |無謬が前提なので硬直的に従う|誤りが前提なので修正しながら進める|
|進捗計測        |ほぼ不可能                  |実測ベース                        |
|要求技能        |OOD/C++                     |OOD/C++/TDD etc                   |
|自動化          |通常は未実施                |自動化前提                        |
|プロジェクト規模|規模とは関係小              |大規模は難しい                    |

アジャイル系プロセスは開発チーム全員による議論を要求するので、
１チーム１０人程度以下でなければ運営が効率的ではない。
それ以上の人数が必要な場合、１０人以下のチームを複数個作り、
「各チームのリーダーが参加するイテレーション毎の計画ミーティング」
でソフトウェア開発全体の計画作りと各チームへのタスクの割り振りを行うことになる。
先に述べた理由から、このミーティングの参加者も１０人程度以下が望ましい。
以上のような考察から、
１００人を超えるような大規模開発にはアジャイル系プロセスは不向きであるというのが常識的な結論である。
逆にそれほどの規模でないプロジェクトでウォーターフォールを選ぶ理由はないと思われる。

## アジャイル系プロセスのプラクティスとインフラ
多くのアジャイル系プロセスは、下記のようなサブプロセスやプラクティスの実施を前提とする。

* [自動単体テスト](---)
* [リファクタリング](---)
* [自動統合テスト](---)
* [TDD](---)
* [CI(継続的インテグレーション)](---)
* [コードインスペクション](---)

このプロセスでは前イテレーションまでに作られたテスト済のソースコードを何度も修正することになる。
これにより、

* ソースコードを修正すると再帰テストが必要になるが、
  これを手作業で行えば、プロジェクトの工数が圧迫されるため、
  テストの自動化はアジャイル系プロセスにとって必須である
* 汚いソースコードへの機能追加は困難・非効率であるため、リファクタリングが必要であり、
  リファクタリングには単体テストが必須である

という理由から、自動単体テストとリファクタリングは特に重要なプラクティスである。

### 自動単体テスト

#### 自動単体テストとは？
一般に、単体テスト(UT)とは、個々のクラスや関数といったソフトウェア構成要素の機能が正確に
動作することを検証するためのテストを指す。
原理的には、デバッガ等を利用して手作業で単体テストを実行することは可能であるが、

* 工数が膨大になる
* テストの再現性が低い
* 高速な操作のテストが困難である

等の問題がある(V字モデルであれば可能かもしれないが)ため、現実的ではない。

自動単体テスト(以下単に単体テストやUTと呼ぶこともある)とは、この問題に対処するためのもので、
ワンコマンド(もしくはワンクリック)でクラスや関数の単体テストを行うプログラムである。

下記にstd::vectorの単体テストを例示する。

```cpp
    // @@@ example/etc/ut.cpp #0:0 begin
```

このようなプログラムを書くことを「単体テストを書く(を作る)」、
このようなプログラムを実行する(実行してバグを取り除く)ことを「単体テストを行う(をする)」という。
通常、単体テストソースコードのビルドや単体テストの実行は、
その対象ソースコードと同じビルドシステム(makeやVisual Studioのソリューション等)に組み込まれる。
単体テストを書き、それをビルドシステムから実行できるようにすることで、
ほとんど工数をかけることなく何度でも単体テストを繰り返し実行できる
(つまり単体テストを持つクラスの回帰テストのコストをほぼ0にできる)。

#### 単体テストのメリット
単体テストを行うメリットは、

* バグが単体テストで検出可能である場合、
  そのバグを統合テストで検出・デバッグするよりも、単体テストで検出・デバッグする方が効率的である。
* 自動単体テストは工数をほとんどロスすることなしに何度でも実行できるため、
  機能追加、バグ修正、リファクタリング等のソースコード修正後の回帰テストが容易になる。
* ソースコードカバレッジを計測できるため、テストの網羅性を定量化できる。
* 統合テスト以降では実施が難しいテスト(エラーハンドリング等)であっても、
  単体テストであれば比較的容易に実施できる。

一方で単体テストを行うデメリットは、

* 単体テストが可能なクラス設計には、人員のスキルの向上が必要(OOD、デザインパターン等)である。
* 単体テストのコーディングに時間がかかる(一見そう見えるが、
  単体テストにより統合テストやシステムテストの時間が短縮されるので、
  期間トータルでは問題ないことが多い)。

単体テストのメリット、デメリットを比べれば明らかな通り、単体テストを行わない合理的理由はない
(そもそも一般的な意味での単体テストを行わないプロセスはおそらく存在しない)。

#### アーキテクチャと単体テスト
プログラムとその単体テストのパッケージの構造(「[アーキテクチャ](---)」参照)を説明するために、
以下のような特徴を持つAppliというプログラムを想定する。

* 「[パッケージとその構成ファイル](---)」で定めたルールに従っている。
* 各パッケージはライブラリとして実装され、それらをリンクすることによりAppliが生成される。
* 下記パッケージ図のような構造を持つ。

![パッケージ図](plant_uml/arch_and_lib.png)

この場合、下記図のように各パッケージ(ライブラリ)毎に単体テスト実行プログラムを作るのが一般的である
(「[ファイル名](---)」で述べたように、\*.cppに対しては\*\_ut.cppとする)。

![パッケージ図](plant_uml/arch_and_lib_ut.png)

パッケージ間に無駄な依存関係や相互依存、循環依存があると、
単体テスト用のモックやスタブを大量に作らざるを得なくなる場合が多く、
最悪の場合、単体テスト用のリンクができないこともある。

単体テストの開発を行うかどうかに関係なく、
効率の良いソフトウェア開発を行うためにはこのように整理されたパッケージ構造を持つことが好ましいが、
単体テストの開発を行う場合、このような構造は特に重要となる
(「[アーキテクチャとファイル構造](---)」参照)。

#### 単体テストのサポートツール
C++をサポートする単体テストフレームワークとしては、

* cUnit
* [google test(gtest)](http://opencv.jp/googletestdocs/primer.html)
* MSTest
* C++Test

等がある。

単体テスト用の実行形式バイナリはビルドを行うOS上で実行するため、
組み込みソフトウェア開発のようにクロスコンパイラを使用している場合、
単体テストのビルドにそのクロスコンパイラを使用することはできない。
そのような場合、単体テスト用にはg++やclang++を使用することが一般的である。
ネイティブなコンパイラを使用しているプロジェクトでは、
単体テストのビルドにもそのコンパイラを使用する。

多くのビルド環境では下記のようなテストカバレッジ(g++/clang++とlcov)を出力できる。
単体テストが十分かどうかは、それを見て判断できる。

![カバレッジリスト](image/coverage_list.png)
![ファイルカバレッジ](image/file_coverage.png)

### リファクタリング
リファクタリングとは、ソフトウェア(や、その構成物であるクラスや関数等)
の外部に対する振る舞いを変えることなしに、その内部構造を改善することである。
従って、リファクタリングには、

* リファクタリングの前後で動作の違いがないことを確認できる
* ソースコードの問題点に気づき、それをより良いソースコードに改善できる

ことが必要である。

通常、リファクタリングは下図に示すようなワークフローとしてプロセスに組み込まれ、
日々の開発業務の一環として行われる。

![リファクタリングワークフロー](plant_uml/refactoring.png)

#### リファクタリングのための回帰テスト
すでに述べたように、リファクタリング後には回帰テストが必要である。
通常、この回帰テストは、改善したソースコードをカバーする自動実行可能な単体テストや統合テスト等の、
エンジニアの工数をほとんどロスしない方法で行われる。
もし、多くの回帰テストが手作業で行われるならば、
プロジェクトがその工数負担に耐えられなくなり、以下のいずれかが発生する。

1. リファクタリングがほとんど行われなくなる。
2. ソースコード改善後、十分な回帰テストが行われなくなる。
3. 一度に大量のソースコード改善を行うようになる(回帰テストの回数を減らす)。

ソースコードの構造を改善し、自動テストを組み込めるようにするために、
上記3の方法は効果的である場合もある
(すなわち、方法3はそのソースコードのライフサイクルの中で一度だけ施行が許される)。
他の方法ではリファクタリングをプロセスに組み込むことはできない。

以上の考察から、リファクタリングのための回帰テストは、自動単体テストか自動統合テストのいずれか、
もしくは両方にならざるを得ない。
プロジェクトの進捗とともに自動統合テストは数時間～数日を要するようになるので、
実践的に考えると、自動統合テストはリファクタリングのための回帰テストには不向きである。
その結果、リファクタリング後の回帰テストには、
「修正したソースコードやその周辺をカバーする自動単体テスト」以外の選択肢はないと考えられる。

![リファクタリングワークフローと単体テスト](plant_uml/refactoring_ut.png)

#### ソースコードの改善
良いプログラマが書いたソースコードは、無駄がなく機能的である。
それが機能美として目に映ることもあるため、
自分や自分のチームにはそのようなソースコードは書けないと思う人がいる。
他方で、良いソースコードとはどのようなものかも知らずに、
自信満々にリファクタリングをやりたいという人もいる。

どちらの考え方も間違っている。
「[コードインスペクション](---)」で述べた観点に沿ってソースコードを読み、
その違反を確実に修正できることが、ソースコード改善の第一歩である。

これは前者が思うほど難しくもなく、後者が思うほど簡単でもない。

#### リファクタリングの例
ソースコードに多くの問題があった場合でも、一度に多くの視点からの修正をしてはならない。
ステップバイステップで少しずつ改善させることを心掛けるべきである。

例えば大きすぎる関数を分割するリファクタリングを行う場合は、その分割のみに集中すべきで、
その最中に別の問題を見つけても、その修正を行ってはならない。
まずは、仕掛中のリファクタリングを終了させ、その後(コミットした後)、次の問題点に取り掛かるべきである。

以下では、そういったステップバイステップのリファクタリングを例示する。

##### オリジナルのソースコード
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

##### 機能追加によるソースコード品質劣化
時間のかかるアルゴリズムがプログラムをブロックしてしまうので、
下記のように、この処理を(不十分ながら)非同期化した。

```cpp
    // @@@ example/ref_async_org/main.cpp #0:0 begin
```

一般に、同期処理をそのまま非同期に変更するとソースコードは腐敗を始める。
上記ソースコードもその例に漏れず、かなり醜悪になった。

##### 小規模なリファクタリング
Null ObjectパターンやRAIIの導入で肥大化したmain関数を改善する小規模なリファクタリングを行う。

```cpp
    // @@@ example/ref_async_r0/main.cpp #0:0 begin
```

上記例のScopedGuardは、汎用性が高くプロジェクト全体で使用できるため、別のファイルとして、
下記のように宣言、定義する(汎用性が高いクラスや関数をプロジェクト全体で共有することは良い習慣である)。

```cpp
    // @@@ deep/h/scoped_guard.h #0:0 begin
    // @@@ deep/h/scoped_guard.h #0:1 begin
    // @@@ deep/h/scoped_guard.h #0:2 begin
```

##### 構造のリファクタリング
前記レベルでは不十分であるため、ブロックを関数化するリファクタリングを行う。

```cpp
    // @@@ example/ref_async_r1/main.cpp #0:0 begin
```

メインループ関数は、main()と同じファイルに残すが、他の関数は下記のように他のファイルで定義する。
これにより、部分的だが単体テストが導入できる。

```cpp
    // @@@ example/ref_async_r1/lib.cpp #0:0 begin
```

##### 単体テストの開発
前述したように、関数やファイルを分割したことにより、
不十分なレベルではあるが単体テストを開発、実行できるようになった。

```cpp
    // @@@ example/ref_async_r1/lib_ut.cpp #0:0 begin
```

scoped_guard.hに関しても、以下のように単体テストを追加する。
バグが発生しそうにないこのようなクラスに対しても単体テストを行うことは一見無駄なように見えるが、
単体テストカバレッジの管理、コードクローンの撲滅、
「[割れ窓理論](https://ja.wikipedia.org/wiki/%E5%89%B2%E3%82%8C%E7%AA%93%E7%90%86%E8%AB%96)」
等の観点から重要である。

```cpp
    // @@@ example/programming_convention/scoped_guard_ut.cpp #0:0 begin
```

##### クラスの導入
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

##### 単体テストの変更
このリファクタリングにより単体テストは以下のようになる
(以下のModelのデザインは不十分であるため、妥当な単体テストはできない)。

```cpp
    // @@@ example/ref_async_r2/lib_ut.cpp #0:0 begin
```

##### MVCの導入
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

##### 単体テストの変更(単体テスト用クラス導入)
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

##### DIの導入
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

##### 全クラスの単体テスト
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

### 自動統合テスト

#### 自動統合テストとは？
一般に、統合テスト(IT)とは、クラスや関数、
ライブラリ等のソフトウェア構成要素すべてを結合したプログラムの動作が、
要求仕様に沿っていることを検証するためのテストである。
統合テストはテストエンジニアやプログラマの手作業で行われることが慣例になっているが、
プログラムに少しの工夫を加えることで、その多くを自動化することができる
(プログラムにもよるが100%自動化は困難である)。
この自動化された統合テストを本ドキュメントでは自動統合テストと呼ぶ。

以下のようなテストを手作業で行うことはほぼ不可能であるが、
これらの項目を統合テストから外すこともできないため、
すべてのソフトウェア開発において自動統合テストは必須である。

* 長時間オペレーションで不具合(メモリリーク等)が出ないことの検証
* 手作業では難しい高速入力

#### 自動統合テストのための仕様追加
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

#### 自動統合テストのためのソースコード変更
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

#### 自動統合テスト用ソースコード変更のための単体テスト
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

#### 自動統合テストの実装
ref_async_r5に追加された機能をスクリプト言語(下記例ではbash)等から利用することで、
下記のような自動統合テスト(非手作業統合テスト)を開発することができる。
入力文字列や入力タイミングのバリエーションを増やすこと等によってこの方法を発展させれば、
堅固な自動統合テストにすることも可能である。

```sh
    // @@@ example/ref_it/it.sh #0:0 begin
```

### TDD
この章の考察に従って、単体テストをプロセスに組み込むのであれば、
ほとんどのクラス、関数は統合テスト前までに単体テストを実施されデバッグされることになる。
もしそうであるならば、この作業の流れ(クラスや関数の開発→単体テスト)
はTest driven development(TDD)を使うことでさらに効率的になる。

TDDとは、下図に示すようなプログラマのワークフローである。

![TDDワークフロー](plant_uml/tdd.png)

これは極めて強力なプラクティスであり、TDDを習慣化することで生産性の大幅な向上が見込める。

### CI(継続的インテグレーション)
CI(continuous integration == 継続的インテグレーション)は、バージョン管理システムやそのウェブサービス、
ブランチ運用等と密接な関係を持つため、まずはこれらの説明を行う。

#### バージョン管理システム
バージョン管理システムは、ソフトウェア開発にとって最も重要なインフラの一つである。
従って、多彩なバージョン管理システムから何を選ぶかは、
プロジェクトの成否に大きく影響する重大な意思決定である。

機能、性能、今後の発展、情報入手の容易さ等を総合的に考えると、

* バージョン管理システムにはgit
* そのウェブサービスにはGitHub

がベストな選択であると思われる。
社内ルール等によりでGitHubが使えない場合、
GitHubと同等なgitウェブサービスをイントラネット内に構築することを推奨する。

##### gitのブランチモデル
gitは極めて自由度の高いバージョン管理システムであるため、
ブランチ運用については細心の注意が必要である。
特別な理由がない限り
[git-flow](https://nvie.com/posts/a-successful-git-branching-model/)
(A successful Git branching model)
等の世界的に評価の高い運用モデルを使用すべきである。

単純化したgit-flowを下記する。
![単純化したブランチモデル](plant_uml/git_branching.png)

このモデルにおける特に大切なポイントは、プロジェクト全体でシェアされる開発用ブランチdevelopと、
個別の機能開発用ブランチ(features/xxx, yyy等)を分けたことである。これにより、

* 中途半端な機能の追加によりdevelopブランチの動作が不安定になることを軽減できる。
* 上記の問題回避のために、プログラマのローカルブランチにソースコードが滞留し続けることを回避できる。
* featureブランチからdevelopブランチへのマージ前にpull-requestすることで、
  コードインスペクションの実施やその履歴管理が容易になる。

等のメリットを享受できる。

##### コードインスペクション
GitHubのようなシステムを前提とするプロセスでは、
コードインスペクションはpull-requestをトリガーとして行われる。
pull-requestとは、featureブランチをdevelopブランチへマージする直前に行われる、
ブランチ開発者からインスペクタへの依頼である。
インスペクタはこの依頼を受けると、対象コミットのコードインスペクションを行い、

* 問題ない品質であると判断した場合、pull-requestを承認する。
* 問題がある場合は、その部分を指摘し、pull-requestを却下する。

pull-requestが承認されれば、ブランチ開発者はfeatrueブランチをdevelopブランチにマージする。

ブランチ開発者は、pull-request前にその対象のコミットが、
以下のコミットクライテリアを満たしていることを保証しなければならない。

* 最新のdevelopブランチはそのfeatureブランチにマージされている
  (マージされてないと、
  この後のfeatureブランチからdevelopブランチへのマージで多くのコンフリクションが発生し、
  インスペクションが無駄になることがある)。
* 新規のクラスや関数の単体テスト、新規機能の統合テストは作られていて、パスしている。
* コミットは十分に小さい
  (様々な目的のソースコードを一度のコミットに混在させるべきではない)。

コードインスペクションは、以下のような観点で行われる。

* コミットクライテリアをクリアしているか(単体テストや自動統合テストが作られているかどうかの確認)？
* 設計上の問題点はないか？
    * [|SOLID](---)等の原則に従っているか？
    * デザインパターンの使用は適切か([Accessor](---)や[Singleton](---)の多用は認められない等)？
* [プログラミング規約](---)に従っているか？
    * 不要な依存関係はないか？ 依存関係の方向は問題ないか？
    * クラス、関数は大きすぎないか？
    * コードクローンや同型のcase文はないか？
    * 識別子やファイル名等の名前は適切か？

#### CIとは？
内容を具体化、単純化するためこれまで述べてきたように、今後の説明も下記項目を前提とする
(この前提でなければCIができないという意味ではない。当然ながらsubversion等でもCIの運用は可能である)。

* バージョン管理システムにgitを使用する。
* gitウェブサービスにはGitHubか、それと同等のものを使用する。
* gitの運用は、git-flowに従う (「[gitのブランチモデル](---)」参照)。

[CI](https://ja.wikipedia.org/wiki/%E7%B6%99%E7%B6%9A%E7%9A%84%E3%82%A4%E3%83%B3%E3%83%86%E3%82%B0%E3%83%AC%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3)
とは、「すべてのプログラマは、
1日1回以上の頻度で、featrueブランチをdevelopブランチへマージしなければならない」
というプラクティスである。
developブランチが更新され次第、ビルド、単体テスト、
統合テスト等を自動で行うシステムとの併用が前提となるため、
本ドキュメントのCIとは、本来の意味に加えてこの自動システムの運用も含めた概念であると定義する
(一般にも、そのように定義していると思われる)。
また、そのシステムをCIサーバ、CIサーバが実行するジョブ項目を単にCI項目と呼ぶ。
CIサーバにはクラウドサービスを含めて様々なものがあるが、代表的なものはJenkinsである。

CIの技術的優位性は、「枝分かれしてから長時間が経過したブランチは統合(マージ)が困難である」
という前提から発生している。この前提は明らかに正しいが、
こうしないプロジェクトにはこうしない理由がある。
マージするとdevelopブランチの動作品質が下がり、チーム全体の作業が滞るからである。
この問題の対抗策がビルド、単体テスト、統合テスト等の自動実行であるため、
これらの自動化ができていないチームが、
featureブランチからdevelopブランチへのマージを頻繁に行うと悲惨な結果になる。
一方で、developブランチへのマージを頻繁に行わないチームは、いずれ困難なマージを行わざるを得なくなる。
この作業は多くのデグレードを引き起こすため、これも悲惨な結果となる。

以上をまとめると、

* developブランチへのマージを頻繁に行った方が、効率よくソフトウェア開発ができる
* そのためには、ビルド、単体テスト、統合テストの自動化ができていなければならない

ということになる。従って、

* CIは効率よいソフトウェア開発を行うための重要なファクターである

というのが結論である。

#### CIとワークフロー
アジャイル系プロセスに下記プラクティス

* TDD
* git-flow
* コードインスペクション(pull-request)
* CI

を組み込んだ場合、プログラマの典型的なワークフローは下図のようになる。

![agileワークフロー](plant_uml/agile_workflow.png)

多くのアジャイル系プロセスは、このように洗練されたワークフローを前提としている。
逆にこのようなワークフローを行えないチームのアジャイル系プロセスは機能しない。
アジャイル導入の失敗例のほとんどは、こう言った問題が原因となっている。

このようなプラクティス、特に自動単体テストや自動統合テストを実践できていないチームが、
いきなりこのワークフローを身に着けることは極めて困難である。
イテレーション毎に決定される開発項目、改善項目の中にワークフローの向上に必要な項目を入れ、
ステップバイステップで改善し続けることが重要である。

#### CI項目実行の長時間化と分割
CI項目には前述した

* ビルド
* 単体テスト
* 統合テスト

に加えて、

* ソースコードの静的解析(「[コード解析](---)」参照)
* リリースパッケージの作成

等がある。

developブランチの更新をトリガーとして行われるCI項目は、
長くても30分程度で完了できるようにするのが理想的である。
一方で、機能開発の進捗とともに、この時間制限を超えてしまう項目が出てくる
(フルビルドですら30分を超えることはめずらしくない)。

こういった場合に行われるのが、CI項目の分割である。
以下のテーブルのように、実行タイミング毎にCI項目を分けることで効率の良い運用ができる。

|実行タイミング  |develop更新後           |深夜              |週末                 |
|:---------------|:----------------------:|:----------------:|:-------------------:|
|実行時間        |30分程度                |深夜～翌朝        |金曜日深夜～月曜日朝 |
|ビルド          |差分                    |フル              |同左                 |
|単体テスト      |差分                    |あり              |同左                 |
|統合テスト      |なし/20分以内程度       |あり              |あり(長期動作系)     |
|静的解析        |なし/20分以内程度       |あり              |同左                 |
|pgk作成         |なし          　　　　　|あり              |同左                 |

#### CI項目の例
CIの環境として、

* CIサーバとしてJenkins
* Jenkinsのジョブ記述にbash
* コンパイラに[g++](---)
* ビルドツールにmake

を使用すると前提とする。この場合、

* 差分ビルド

```
    > make -j
```

* フルビルド

```
    > make clean
    > make -j
```

* 単体テスト

```
    > make ut           # sanitizerをオンにしてビルドするとより効果的
```

* 統合テスト

```
    > make it           # sanitizerをオンにしてビルドするとより効果的
```

* 静的解析

```
    > make clang        # gccの他にclangでコンパイルすることで、clangの警告機能を使う
    > scan-build make   # clangベースの静的解析ツール
```

をJenkinsジョブ記述用テキストボックスに記述すればよい(「[コード解析](---)」参照)。
つまり、CIで重要なことはテスト等の項目をコマンド化することである
(従って、ビルドや単体テストをコマンドによって駆動できないIDEを使用してはならない)。

## まとめ
産業は、労働集約型と知識集約型に二分できる。
一般に労働集約型産業の就労者の生産性には大差がなく、
知識集約型産業の就労者の生産性には大きな差がある。
ソフトウェア産業は知識集約型であるにもかかわらず、
プログラマの月単価のような労働集約的な基準で生産性が語られることが慣行となっているが、
これはプログラマの生産性に大差がないという考えから発した誤りである。

ただし、以下のように前提することで、この誤りにも、ある程度の正当性が与えられる。

* プログラマの生産性の違いが発揮されるフェーズはプログラミングのみである。
* V字モデルでは、このフェーズの工数は全工数から見れば少ない。
* テストは、マウスをひたすらクリックするような手作業で行われるため、
  これは労働集約的な作業である。
* V字モデルでのこのフェーズの工数は、プログラミングの工数と同程度になる。

この章で解説した「ほとんどのテストはプログラミングにより自動化できる」ことを理解すれば、
この前提が成り立たないことは明らかだろう。

このことに気づいている組織は知識集約型のアプローチで、
気づかない組織は労働集約型のアプローチでソフトウェア開発を行うことになる。
どちらの生産性が高いかを議論する余地はない。

こういったことをマネージャ、リーダはよく理解するべきだろう。

[演習-プロセス分類](---)  
[演習-V字モデル](---)  
[演習-アジャイル](---)  
[演習-自動化](---)  
[演習-単体テスト](---)  
[演習-リファクタリングに付随する活動](---)  
[演習-リファクタリング対象コード](---)  
[演習-CI](---)  


