# プログラミング規約
組織に秩序を与える法、道徳、慣習等をここではルールと呼ぶことにする。
当然ながら、秩序ある組織には良いルールがあり、混沌とした組織には悪いルールがあるか、
ルールはあっても守られていないか、そもそもルールが存在しない。

秩序あるソースコードとは、

* 可読性が高い。
    * 簡潔に記述されている。
    * 記述スタイルが統一されている(「[コーディングスタイル](---)」参照)。
    * ファイルや識別子の名前に規則性があり、適切に命名されている
      (「[Name and Conquer](---)」、「[命名規則](---)」参照)。 
    * コメントの記法が統一されており、内容が適切である(「[コメント](---)」参照)。 
* 保守、テスト、移植等が容易である。
* 型安全性が配慮されている。
* コンパイル警告レベルが高く、かつ指摘がない(「[g++の警告機能](---)」参照)。

のような特性を満たすものであるが、そうあるためには秩序ある組織と同様に良いルールが必要である。
本章の目的は、C++プログラミングにおけるそのようなルール(=プログラミング規約)を示すことである。

なお、型安全性とは、「正しく型付けされたソースコードは未定義動作をしない」
ことが保証されるという言語の特性である。
配列のオーバランが未定義動作を引き起こすことを考えれば明らかである通り、
C++は型安全性を保証しない。このことは、C++の劣等性を意味しないが、
それに配慮したプログラミング(型システムの最大限の利用等)が必要となることは事実である。

___

__この章の構成__

<!-- index 1-4 -->

[このドキュメントの構成](---)に戻る。  

___

## 型とインスタンス

### 算術型

#### 整数型
* [組み込み型とインスタンス|整数型](---)には、整数の基本型(intやlong等)を直接使わずに、
  [cstdint](https://cpprefjp.github.io/reference/cstdint.html)
  で定義されている型エイリアスを使用する。
    * STLやPOSIX等の標準クラスや関数のインターフェースが基本型を直接使用している場合は、
      その型に合わせるために基本型を直接使用する。
* 整数型には、特に理由がない限りに、int32\_tを使用する。
* 整数型の変数が負にならないのであれば、uint32\_tを使用する。
    * 符号あり型との演算がある場合は、その変数が負にならなくともint32\_tを使用する。
    * 符号あり型と符号なし型との比較をしない。
* sizeofの値や配列の長さの保持等には、size\_tを使用する。
* int32_tからint16_tや、int32_tからuint32_t等の値が変わる可能性がある代入を避ける。
  やむを得ずそのような代入をする場合、下記のようなnarrow_castを使いこのような問題を緩和する。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #0:0 begin
```

```cpp
    // @@@ example/programming_convention/type_ut.cpp #0:1 begin -1
```

* [演習-汎整数型の選択](---)

#### char型
* charはascii文字の保持のみに使用する。
* char\*をvoid\*の代わりに使わない。
* charがsingedかunsignedかは処理系に依存するため、char型を[汎整数型](---)として扱わない。
  8ビット整数には、int8\_tまたは、uint8\_tを使用する。
    * バイトストリームを表現する場合、int8_t\*、int8_t[]、uint8_t\*、uint8_t[]のいずれかを使う。

* [演習-汎整数型の演算](---)

#### std::byte型
* intよりもビット幅の小さい組み込み型の演算の結果は[汎整数型拡張](---)によりint型になるため、
  uint8_tのビット演算の型もintとなる。
  intへの拡張が意図したものかどうかの判別は困難であるため、
  uint8_tインスタンスにビット演算が必要な場合、
  uint8_tの代わりに下記のようにstd::byte(「[BitmaskType](---)」参照)を用いる。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #1:0 begin -2
```

```cpp
    // @@@ example/programming_convention/type_ut.cpp #1:1 begin -2
```

* std::byteの初期化には{}を用いる(static_castを使用しない)。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #1:2 begin -2
```

#### bool型
* bool型は、bool型リテラル(true/false)やbool型オブジェクトの保持のみに使用する。
* bool型を[汎整数型](---)として扱わない。bool型に++を使用しない(--はコンパイルできない)。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #2:0 begin
```

* ポインタ型やboolを除く汎整数型のインスタンスをbool値として使用しない。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #2:1 begin
```

#### 浮動小数点型
* 小数演算に安易に[組み込み型とインスタンス|浮動小数点型](---)を使用せず、
  [浮動小数点型のダイナミックレンジ](---)が必要な場合のみにこれらの型を使用する。
  ちなみに銀河系の直径は1e+21メートル程度、プランク長は1.616229e-35メートルであるため、
  銀河から素粒子までのサイズを一つの基本型で表す場合においても、
  floatのダイナミックレンジに収まる。
  従って、floatやdoubleが必要になる場合は極めて限られる。

* [浮動小数点の誤差](---)は避けられないため、浮動小数点型のインスタンスを==、!=で比較しない。
  代わりに[浮動小数点の比較](---)で定義した関数テンプレートを使用する。

```cpp
    // @@@ example/programming_convention/float_ut.cpp #0:0 begin -1
```
```cpp
    // @@@ example/programming_convention/float_ut.cpp #0:1 begin
```
```cpp
    // @@@ example/programming_convention/float_ut.cpp #0:2 begin -1
```

* 一つの式にfloatとdoubleを混在してしまうと、
  [イプシロン](---)を使用した比較の定義ができなくなるので、
  一つの式に複数の浮動小数型のインスタンスを混在させない。

```cpp
    // @@@ example/programming_convention/float_ut.cpp #0:3 begin
```
```cpp
    // @@@ example/programming_convention/float_ut.cpp #0:4 begin -1
```
```cpp
    // @@@ example/programming_convention/float_ut.cpp #0:5 begin
```
```cpp
    // @@@ example/programming_convention/float_ut.cpp #0:6 begin -1
```

* INFや、NANを演算で使用しない(「[浮動小数点の演算エラー](---)」参照)。
* [汎整数型](---)の演算とは違い、0除算等の[浮動小数点の演算エラー](---)は、
  通常、プログラム終了シグナルを発生させないため、
  浮動小数点演算のエラーを捕捉する必要がある場合(ほとんどの場合、そうなる)は、
  `std::fetestexcept()`、`std::isnan()`、`std::isinf()`等を使用してエラーを捕捉する。

* 扱うダイナミックレンジに収まる限り、安易に浮動小数点を使わず、
  代わりに[固定小数点クラス](---)や[有理数クラス](---)を使用する。

* [演習-浮動小数点型](---)

### enum
* C++の強力な型システムや、コンパイラの静的解析機能(switchでのcase抜け)を効果的に使用するために、
  一連の定数の列挙にはenumを使用する。
* 使用範囲や方法が明示しづらく、且つ整数型への[算術変換](---)が行われてしまう旧来のenum
  (非スコープドenum)は、一部の例外を除き定義しない。
  代わりに、より型安全なスコープドenumを使用する。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #3:0 begin
```

* 列挙子に値を設定する必要がない場合（具体的な値に意味を持たない場合）には、値を設定しない。
  値を設定する場合にはそれらを最初に書き、同じ値を設定しない。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #3:1 begin
```

* enumを配列のインデックスとして使う場合は以下のようにする。
    * スコープドenumの代わりに、旧来のenumをstruct内で定義する。
    * 最初に定義されるenumメンバは0で初期化する。
    * 最後の要素のシンボル名はMaxで終わることにより、
      その要素が最大値であることを示す。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #3:2 begin
```

* enumはC++11から前方宣言できるようになったため、
  この機能を使用して、不要なヘッダファイルの依存関係を作らないようにする。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #3:3 begin
```

* アプリケーションの設定ファイルに保存された情報を復元させるような場合や、
  「[BitmaskType](---)」を使用する場合を除き、enumへのキャストをしない。
* クラスのstatic constの整数定数の代わりにenumを使うことは、
  C++言語仕様やコンパイラの機能が不十分だった頃のテクニックであり、もはや不要である。
  代わりにstatic constexprインスタンス(「[constexpr|constexpr関数](---)」参照)を使用する。
  こうすることで定数の型を明示できる。

* [演習-定数列挙](---)
* [演習-enum](---)

### bit field
* ハードウエアレジスタにアクセスをする目的でのみ使用する。
* bit fieldの型は、unsigned intにする。

### class
* 「[クラスとインスタンス](---)」を参照せよ。

### struct
* メンバ変数を持つ構造体は、[POD](---)としてのみ使用する。
* メンバ変数を持つ構造体を基底クラスとした継承をしない。
  従ってそのような構造体は常にfinalであるが、finalの明示はしない。
* メンバ変数(static constやstatic constexprメンバは定数とする)を持たない構造体は、
  templateや非スコープドenumのスコーピング(「[用語解説|enum](---)」参照)等に使用しても良い。
* コンストラクタ以外のメンバ関数を定義しない。
    * [ディープコピー](---)(「[コンストラクタ](---)」参照)が必要な型は、structでなくclassで表す。
    * デフォルトコンストラクタを除く[用語解説|型とインスタンス|特殊メンバ関数](---)に対して、
      = defaultの明示をしない。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #4:0 begin
```

* Cとシェアしない構造体を無名構造体とそのtypedefで定義しない。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #4:1 begin
```

### union
* ハードウエアレジスタにアクセスをする目的以外で使用しない(以下のような使い方のみ認められる)。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #5:0 begin
```

* 上記のようなunionはランタイム依存性が強いため、それへの依存を最小にする。
  従って、unionの定義を外部パッケージに公開(「[パッケージの実装と公開](---)」参照)しない。

* 上記以外でunionのような機能が必要な場合、
  [std::variant](---)(「[std::variantとジェネリックラムダ](---)」参照)を使用する
  (std::anyはunionの代替えにはならないので、このような場合には使用しない)。

### 配列
* 配列型オブジェクトは[AAAスタイル](---)で生成できないため、使用が不可避できない場合を除き、
  使用しない。代わりに`std::array`を使う。
* 配列をnew[]により生成しない。
  可変長配列が必要な場合は、std::vectorを使用する(「[new](---)」参照)。
  固定長配列を動的に確保する場合は、std::arrayをnewする。
* 配列からポインタへの暗黙の型変換をしない(「[キャスト、暗黙の型変換](---)」参照)。
  特に、オブジェクトの配列をそのオブジェクトの基底クラスへのポインタに代入しないことは重要である
  (「[クラスとインスタンス|スライシング](---)」参照)。
* 関数の仮引数を一見、配列に見える型にしない
  (「[非メンバ関数/メンバ関数共通|実引数/仮引数](---)」参照)。
* char型の配列を文字列リテラルで初期化する場合、配列の長さを指定しない。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #6:0 begin
```

* 配列の全要素にアクセスするような繰り返し処理には[用語解説|構文|範囲for文](---)を使用する。

* [演習-配列の範囲for文](---)

### 型エイリアス
* Cとシェアされる型エイリアスを除き、typedefではなくusingを使用する。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #7:0 begin
```

* 型へのポインタのエイリアスは、それを使用してconstポインタが定義できないため、
  型へのポインタ(関数ポインタを除く)のエイリアスを作らない。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #7:1 begin -1
```

* [演習-エイリアス](---)

### const/constexprインスタンス
* インスタンス、インスタンスへのポインタ、インスタンスへのリファレンス等に対して、
    * [constexpr定数](---)をパラメータにした場合、コンパイル時に定数として評価できる関数は、
      [constexpr|constexpr関数](---)として宣言する。
    * コンパイル時に必ず定数として評価したい[constexpr|constexpr関数](---)には[consteval](---)を使用する。
    * constexprにはできないが、const(「[constインスタンス](---)」にはできるインスタンスは、
      constとして定義する。関数の仮引数になっているリファレンスやポインタをconstにすることは特に重要である
    * 文字列リテラルのアドレスを非constポインタ型変数に代入しない(「[用語解説|リテラル](---)」参照)。
    * イテレータにおいても、可能な場合は、イテレータをconstするか、const_iteratorを使う。

```cpp
    // @@@ example/programming_convention/type_const_ut.cpp #0:0 begin
```

* constは、意味が変わらない範囲で出来るだけ右側に書く。

```cpp
    // @@@ example/programming_convention/type_const_ut.cpp #0:1 begin
```

* [演習-constの意味](---)
* [演習-const/constexpr](---)

### リテラル
* ヌルポインタを表すポインタリテラルとして、nullptrを使用する(0やNULLを使用しない)。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #8:0 begin -1
```
```cpp
    // @@@ example/programming_convention/type_ut.cpp #8:1 begin -1
```

* 文字列リテラル("xxx")はconstオブジェクトとして扱う
  (「[const/constexprインスタンス](---)」、「[std::string型リテラル](---)」参照)。
* 長い[汎整数型](---)リテラルを使用する場合は、適切に区切りを入れる(C++14)。
* ビットマスク等2進数を使用した方が直感的な場合には2進数リテラルを使用する(C++14)。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #8:2 begin -2
```

* bool型を表すリテラルにはtrue、falseを使用する。代わりに0、1、!0等を使わない。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #8:3 begin -2
```

* long値リテラルを表す文字には"l"ではなく、"L"を使う。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #8:4 begin -2
```

#### 生文字列リテラル
* 正規表現を表す文字列リテラルを使用する場合、文字列内のエスケープシーケンスをエスケープするのでなく、
  には[用語解説|リテラル|生文字列リテラル](---)を使用する。これにより正規表現の可読性が向上する。

```cpp
    // @@@ example/programming_convention/raw_literal_ut.cpp #0:0 begin 

    // @@@ example/programming_convention/raw_literal_ut.cpp #0:1 begin -1
```

* [演習-危険なconst_cast](---)
* [演習-リテラル](---)

### 型推論
#### auto
* [AAAスタイル](---)に従い適切にautoを使用する。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #9:0 begin
```

* autoを使用する場合、&、\*、const等の付け忘れに注意する。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #9:1 begin
```

* autoと= {}を使用した変数の宣言には以下のような紛らわしさがあるため、
  そのような記述を行わない(「[インスタンスの初期化](---)」参照)。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #9:2 begin -1
```

* auto、[decltype](---), decltype(auto)の微妙な違いに気を付ける。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #9:3 begin -1
```

* 通常の関数の定義に「[autoパラメータによる関数テンプレートの簡易定義](---)」の使用を避ける。
  [autoパラメータによる関数テンプレートの簡易定義](---)を使ったインライン関数は柔軟すぎる。

* [演習-適切なautoの使い方](---)

### インスタンスの初期化
* 関数内のオブジェクトは、出来る限り[AAAスタイル](---)を用いて宣言し、同時に初期化する。
* [用語解説|組み込み型とインスタンス|算術型](---)の宣言に[AAAスタイル](---)が使えない場合、
  「代入演算子を伴わない[オブジェクトと生成|一様初期化](---)」を使用する。
  「代入演算子を伴う一様初期化」、「()、=による初期化」を使用しない。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #11:0 begin -1
```

* リファレンスやポインタの宣言に[AAAスタイル](---)が使えない場合、
  「代入演算子を伴わない[オブジェクトと生成|一様初期化](---)」か「=による初期化」を使用する。
  「代入演算子を伴う一様初期化」、「()による初期化」を使用しない。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #11:1 begin -1
```

* 構造体やクラス型オブジェクトの宣言に[AAAスタイル](---)が使えない場合、
    * 「代入演算子を伴わない[オブジェクトと生成|一様初期化](---)」を使用する。
    * 上記では意図したコンストラクタが呼び出せない場合にのみ「()による初期化」を使用する。
  ただし、std::string、std::string_viewに関しては「 = "xxx"」を使用しても良い。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #11:2 begin -1
```

* decltypeによるオブジェクトの宣言は、[AAAスタイル](---)と同様に行う。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #11:3 begin -1
```

* 配列の宣言には、「代入演算子を伴わない[オブジェクトと生成|一様初期化](---)」を使用する。
  char[]に関しては、「代入演算子を伴わない一様初期化」か「 = "xxx"」を使用する。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #11:4 begin -1
```

* 宣言時にポインタ変数の初期値が決まらない場合、nullptrで初期化する(「[用語解説|リテラル](---)」参照)。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #11:5 begin -1
```

* 初期化順序が不定になるため、
  別のコンパイル単位で定義された静的なオブジェクトに依存した静的オブジェクトの初期化を行わない
  (同じファイルの上方にある静的なオブジェクトや、
  [Singleton](---)に依存した初期化を行うことには問題はない)。
* コンパイル時に値が確定する「基本型」や「コンストラクタがconstexprであるクラス」のインスタンスは、
  constexpr(「[const/constexprインスタンス](---)」参照)と宣言する。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #11:6 begin
```
```cpp
    // @@@ example/programming_convention/type_ut.cpp #11:7 begin -1
```

* constなオブジェクトが複雑な初期化を必要とする場合、その初期化にはラムダ式を使用する。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #11:8 begin -1
```


* [演習-インスタンスの初期化](---)
* [演習-vector初期化](---)
* [演習-ポインタの初期化](---)


### rvalue
* 関数の仮引数以外のリファレンスで[expressionと値カテゴリ|rvalue](---)をバインドしない
  (「[クラスとインスタンス|オブジェクトのライフタイム](---)」参照)。
* rvalueの内部ハンドルを使用しない(「[std::string_viewの使用制限](---)」参照)。

```cpp
    // @@@ example/programming_convention/type_ut.cpp #12:0 begin -1
```

* 非constなリファレンスでrvalueをバインドしない。


## クラスとインスタンス
### ファイルの使用方法
* 下記の例外を除き、一つのクラスはそれを宣言、定義する1つのヘッダファイルと、
  一つの.cppファイルによって構成する。
    * ファイル外部から使用されないクラスは、一つの.cppファイルの無名名前空間で宣言、定義する。
    * ファイル外部から使用されるインラインクラス(クラステンプレート等)は、
      一つのヘッダファイルで宣言、定義する。
    * 「一つのヘッダファイル(a.h)と、一つの.cpp(a.cpp)で構成されたクラスA」のみをサポートするクラス
      (Aのインターフェースや実装専用に定義されたクラス(「[Pimpl](---)」参照))は、
      a.h、a.cppで宣言、定義する。

### クラスの規模
#### 行数
* それ以外に方法がない場合を除き、ヘッダファイル内のクラスの定義、
  宣言はコメントを含め200行程度に収める。
* クラス内定義関数が大きくなると下記のような問題が発生しやすくなるため、
  10行を超える関数はクラス内で定義しない。
    * 関数のインポートする外部シンボルが多くなり、
      このクラスを使用する別のクラスに不要な依存関係を作ってしまう
      (「[インターフェース分離の原則(ISP)](---)」参照)。
    * クラスの定義が間延びして、クラスの全体構造を把握することが困難になる。

#### メンバの数
* それ以外に方法がない場合を除き、publicメンバ関数の数は、最大7個程度に収める
  (ただし、オーバーロードにより同じ名前を持つ関数群は、全部で1個とカウントする)。
* オブジェクトの状態を保持するメンバ変数の数は、最大4個程度に留める。
  constやconstexprメンバ・インスタンスは定数(状態を保持するメンバ変数ではない)であるため、
  この数に含めない。

#### 凝集度
* 単なるデータホルダー(アプリケーションの設定データを保持するようなクラス等)や、
  ほとんどの振る舞いを他のクラスに委譲するようなクラスを除き、
  [ソフトウェア一般|凝集度](---)が高くなるように設計する。
* [LCOMの評価基準](---)に従い、凝集度を判断し、凝集度が著しく低いクラスを作らないようにする。

* [演習-凝集度の意味](---)
* [演習-凝集度の向上](---)


### アクセスレベルと隠蔽化
* アクセスレベルは、特別な理由がない限り、上からpublic、protected、privateの順番で明示する。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #0:0 begin
```

* 全てのメンバ変数はprivateにする。
    * メンバ変数にアクセスしたい場合は、Accessorメンバ関数を経由させる
      (「[Accessor](---)」参照)。その場合でもsetterは控えめに使用する。
    * 派生クラスから基底クラスの変数の値が必要になる場合は、protectedなAccessorを定義する。
    * 単体テスト用クラスでは、protectedメンバ変数を定義してよい。
* アクセスレベルによるカプセル化が破壊されるため、
  メンバ変数のハンドル(リファレンスやポインタ)を返さない。
  それが避けがたい場合においては、constハンドルを返す。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #0:1 begin
```

* 以下のような場合を除き、friendを使用しない。
    * 単体テスト用クラス
    * 二項演算子をオーバーロードした関数

```cpp
    // @@@ example/programming_convention/class_ut.cpp #0:2 begin
```

* [NVI(non virtual interface)](---)に従う。従って、
  virtualな関数はprivateかprotectedと宣言し、それをpublicな非仮想メンバ関数から呼び出す。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #0:3 begin
```

### 継承/派生
* 派生は最大2回程度までに留める。やむを得ず階層が深くなる場合、
  コードの静的解析等を使用し派生関係を明確にする(「[ポリモーフィックなクラス](---)」参照)。
* 実装の継承よりも、包含、委譲を優先的に使用する。やむを得ず実装の継承を行う場合は、
  private継承を使用する。 実装の継承をしたクラスがfinalでないならば、protected継承を使用する
  ([CRTP(curiously recurring template pattern)](---)等は例外的に認められる)。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #1:0 begin
```

* 派生させないクラスは、finalと宣言する。ほとんどのクラスは派生しないはずなので、
  ほとんどのクラスはfinalになる。
* リソースリークの原因になり得るため、非virtualなデストラクタをもつクラスを継承しない。
  ただし、継承したクラスが基底クラスのメンバ変数以外のメンバ変数を持たないならば、継承しても良い。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #1:1 begin
```
```cpp
    // @@@ example/programming_convention/class_ut.cpp #1:2 begin -1
```
```cpp
    // @@@ example/programming_convention/class_ut.cpp #1:3 begin
```
```cpp
    // @@@ example/programming_convention/class_ut.cpp #1:4 begin -1
```

#### インターフェースの継承
* クラス間に「Is-a」の関係が成り立つときに限りpublic継承を行う。
    * public継承を行う場合、[リスコフの置換原則(LSP)](---)を守る。
    * インターフェースを継承しない場合、public継承をしない。
* C#やJavaのinterfaceが必要ならば(インタフェースと実装の完全分離をしたい場合等)、
  pure-virtualなメンバ関数のみを宣言したクラス
  (もしくはそのクラスに[NVI(non virtual interface)](---)を適用したクラス)
  を定義する。

#### 多重継承
* それが不可避でない限り、多重継承は使用しない。
* 多重継承を使用する場合、複数個の基底クラスのうち、一つを除きメンバ変数を持ってはならない。
* 多重継承を使用する場合、継承階層内に同じ基底クラスが複数回出てきてはならない
  ([ダイヤモンド継承](---)をしない)。
* やむを得ずダイヤモンド継承をせざるを得ない場合、
  継承階層内に複数回出現する基底クラスにはvirtual継承を行う。
* virtual継承を行ったクラスのコンストラクタからは、
  virtual基底クラスのコンストラクタを呼び出すようにする
  (こうしないとvirtual基底クラスは初期化されない)。

### 非静的なメンバ変数
* すべての非静的なメンバ変数は、コンストラクタ終了時までに明示的に初期化する。
* 多くのコンパイラや静的解析ツールはインスペクタは、
  [NSDMI](---)、[初期化子リストでの初期化](---)による初期化の漏れについては容易に発見、
  指摘できることが多い。
* constメンバ変数は、[NSDMI](---)、
  [初期化子リストでの初期化](---)でなければ初期化できないため、それ以外に方法がない場合を除き、
  [コンストラクタ内での非静的なメンバ変数の初期値の代入](---)の使用を避ける。
* 非静的なメンバ変数はクラス内で定義された順序に従い初期化されるため、
  [初期化子リストでの初期化](---)の順序を定義順序と同じにすることで可読性を向上させる。
* クラスがただ一つのコンストラクタを持つ場合、
  [NSDMI](---)と[初期化子リストでの初期化](---)を混在させない。
  従って、[初期化子リストでの初期化](---)を必要とするメンバ変数が一つでもある場合は、
  すべての変数の初期化を[初期化子リストでの初期化](---)で行う。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #2:0 begin
```

* クラスが複数のコンストラクタを持つ場合、
  すべてのメンバ変数に対して[NSDMI](---)を行い(デフォルト値の設定)、
  デフォルト値とは異なる初期値を持つ変数に対してのみ、
  コンストラクタ毎に[初期化子リストでの初期化](---)を行う。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #2:1 begin
```

* [演習-メンバ変数の初期化方法の選択](---)
* [演習-メンバの型](---)
* [演習-メンバ変数の初期化](---)

### 静的なメンバ変数/定数の初期化
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
    // @@@ example/programming_convention/class.h #0:0 begin
```

```cpp
    // @@@ example/programming_convention/class_ut.cpp #3:0 begin
```

### mutableなメンバ変数
* 排他制御用(std::mutex等)や計算データのキャッシュ用等のメンバ変数を除き、
  メンバ変数をmutableと宣言しない。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #4:0 begin
```

### スライシング
* オブジェクトの[オブジェクトのコピー|スライシング](---)には以下のいずれかで対処する。
    * [Clone(仮想コンストラクタ)](---)を使用する。
    * copy代入演算子を= deleteする。

* [オブジェクトのコピー|スライシング](---)と類似の問題が起こるため、
  オブジェクトの配列をそのオブジェクトの基底クラスへのポインタに代入しない。

* [演習-スライシング](---)

### オブジェクトの所有権
* オブジェクトaの所有権
  (「[オブジェクトと生成|オブジェクトの所有権](---)」参照)を持つオブジェクトもしくは関数は、
  オブジェクトaの解放責務を持つ。
* オブジェクトaの所有権を持たないオブジェクトは、
  オブジェクトaのハンドルをメンバ変数で保持することを出来る限り避ける
  ([Observer](---)パターン等、このルール順守が困難な場合は多い)。
* クラスAのオブジェクトaが、オブジェクトbにダイナミックに生成されたとすると、  
    * オブジェクトaのポインタは`std::unique_ptr<A>`(「[RAII(scoped guard)](---)」参照)で保持する。
    * オブジェクトa(正確にはオブジェクトaを管理する`std::unique_ptr<A>`オブジェクト)の所有権は、
      オブジェクトbが保持する。
    * オブジェクトbはオブジェクトaの解放責務を持つ(`std::unique_ptr<A>`による自動解放)。
    * オブジェクトaの所有権を保持していないオブジェクトは、オブジェクトaを解放してはならない。
    * オブジェクトaの所有権を別のオブジェクトxへ移動させる場合、
      `std::unique_ptr<A>`とstd::move()を使用する(「[オブジェクトの排他所有](---)」参照)。
    * このようなaに複数の所有者b0、b1が存在する場合、`std::shared_ptr<A>`を使用してaを管理する。
      従って、b0、
      b1は`std::shared_ptr<A>`型のメンバを持つことになる(「[オブジェクトの共有所有](---)」参照)。
    * オブジェクトbが`std::shared_ptr<A>`でオブジェクトaを、
      オブジェクトaが`std::shared_ptr<B>`でオブジェクトbを所有する場合、
      [オブジェクトの循環所有](---)よるメモリリークが発生するため、
      [std::weak_ptr](---)を適切に使用する。

* [演習-オブジェクトの所有権](---)

### オブジェクトのライフタイム
* [オブジェクトと生成|オブジェクトのライフタイム](---)開始前、
  もしくは終了後のオブジェクトにアクセスしない。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #5:0 begin
```

* オブジェクトaが所有権を持たないオブジェクトbへのハンドルをa自体のメンバ変数で保持する場合、
  オブジェクトbのライフタイムが終了する前に、
  オブジェクトaがオブジェクトbにアクセスできないようにする(Observerパターンのdetachメンバ関数等)。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #5:1 begin -1
```

* スタック上のオブジェクトのハンドルをその関数外部へ開示しない
  (そのハンドルは、ライフタイムが終了したオブジェクトを指している)。
* thread_localオブジェクトは、ログやデバッグ用途のみで使用する。
* [expressionと値カテゴリ|rvalue](---)はライフタイム終了間際のオブジェクトであるため、
  関数の仮引数以外のリファレンスでrvalueをバインドしない
  (特にリファレンス型のメンバ変数でrvalueをバインドしないことは重要である)。
  rvalueをリファレンス型の引数で受け取る場合はconstリファレンス、
  もしくはrvalueリファレンス(T&&)を使用する(「[型とインスタンス|rvalue](---)」参照)。

```cpp
    // @@@ example/programming_convention/class_ut.cpp #5:2 begin -1
```

* [danglingリファレンス](---)、 [danglingポインタ](---)に気を付ける。


## 非メンバ関数/メンバ関数

### 非メンバ関数
* 下記のような関数を除き、グローバル名前空間に非メンバ関数を定義しない。
    * C言語から呼び出される関数
    * アセンブラ関数

* .cppファイルから、そのファイルの外部で定義された関数を呼び出す場合、
  その.cppファイル内での局所的な関数宣言をしない
  (関数が宣言、定義されているヘッダファイルをインクルードする)。
* コンパイル時に戻り値が確定する関数は[constexpr|constexpr関数](---)として宣言する。

* [演習-非メンバ関数の宣言](---)

### メンバ関数
* 可能な場合(メンバに直接アクセスしない場合)、メンバ関数をstaticにする。
* コンパイル時に戻り値が確定するメンバ関数は[constexpr|constexpr関数](---)と宣言する。
* オブジェクトの状態を変えないメンバ関数は、constと宣言する。
    * getter(下記の例ではGetString)はconstと宣言する。
    * 下記のSetPtrのような関数はconstにしない。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #0:0 begin
```

* クラス内部のハンドル（ポインタやリファレンス）を戻り値に使用しない。
    * それが避けがたい場合は、戻り値のハンドルをconstにする。
    * ハンドルがconstにできない場合(関数が非constなハンドルを返す場合)、
      そのハンドル経由でクラスの状態を変更できるため、その関数をconstにしない。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #0:1 begin
```

* 非静的メンバのハンドルを返すメンバ関数を持つオブジェクトが
  [expressionと値カテゴリ|rvalue](---)である場合、
  そのオブジェクトからその関数を呼び出した戻り値(メンバへのハンドル)を変数で保持しない
  (そのハンドルは[danglingリファレンス](---)/[danglingポインタ](---)になっている)。
  そういった使用方法が必要ならばlvalue修飾、[rvalue修飾](---)を用いたオーバーロード関数を定義する。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #0:2 begin -1
```

* [演習-メンバ関数の修飾](---)

#### 特殊メンバ関数
* [用語解説|型とインスタンス|特殊メンバ関数](---)
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
    // @@@ example/programming_convention/class_ut.cpp #6:0 begin
```

* リソース管理等の都合からコンパイラが生成するデストラクタでは機能が不十分な場合、
  プログラマがそのクラスのデストラクタを定義する。
  この場合、コンパイラが生成するcopyコンストラクタ、copy代入演算子、moveコンストラクタ、
  move代入演算子では機能が不十分であることが予測されるため、
  これらを使用しない(「[Copy-And-Swap](---)」参照)。

* [演習-特殊メンバ関数の削除](---)

#### コンストラクタ
* クラスが複数の初期化方法を提供する場合でも、
  デフォルト引数を使用し、できる限りコンストラクタを一つに集約する。
* 一つのコンストラクタに集約できない場合、[委譲コンストラクタ](---)等により処理の重複を防ぐ。
  [非静的なメンバ変数](---)処理の重複を避けることは特に重要である。
* オブジェクトの初期化が完了するまでは派生クラスの仮想関数呼び出し等の
  [演算子|RTTI](---)機能を使うことはできないため(「[ポリモーフィックなクラス](---)」参照)、
  コンストラクタの中でRTTI機能を使わない(デストラクタでも同様)。
  以下のコードはコンストラクタ内で仮想関数呼び出しを行ったため、想定通りの動作にならない例である。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #1:1 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #1:2 begin -1
```

* コンストラクタからのエクセプションを発生をできるだけ避ける([エクセプション処理](---))。
* クラスが解放責務を持つポインタ型メンバ変数を持つならば、copyコンストラクタ、
  copy代入演算子に対して以下のいずれかを行い、[シャローコピー](---)が行われないようにする
  (このルールはファイルディスクリプタ等のリソース管理をするクラス全般に当てはまる)。
    * [ディープコピー](---)をさせる。
    * = deleteする(「[用語解説|型とインスタンス|特殊メンバ関数](---)」参照)。

  またこの場合、moveコンストラクタ、move代入演算子の定義を検討する(「[Copy-And-Swap](---)」参照)。

* 非explicitなコンストラクタによる[暗黙の型変換](---)
  が不要なクラスのコンストラクタに関しては、下記の目的のためにexplicitと宣言する。

    * 仮引数一つのコンストラクタに関しては、[暗黙の型変換抑止](---)する。
    * 仮引数二つ以上のコンストラクタに関しては、
      代入演算子での[一様初期化](---)ができないようにする。  

```cpp
    // @@@ example/programming_convention/func_ut.cpp #1:3 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #1:4 begin -1
```

* 派生クラスが基底クラスの全コンストラクタを必要とする場合、
  [オブジェクトと生成|継承コンストラクタ](---)を使用する。

* デフォルト引数はインターフェース関数の呼び出しを簡略化する目的で使用するべきであるため、
  private関数にデフォルト引数を持たせない。

* [演習-委譲コンストラクタ](---)

#### copyコンストラクタ、copy代入演算子
* copyコンストラクタ、copy代入演算子は[copyセマンティクス](---)に従わせる。
* copyコンストラクタ、copy代入演算子の引数はconstリファレンスにする。
* [RVO(Return Value Optimization)](---)により、
  copyコンストラクタの呼び出しは省略されることがあるため、
  copyコンストラクタ、copy代入演算子はコピー以外のことをしない。
* copy代入演算子は[lvalue修飾](---)をする。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #2:0 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #2:1 begin -1
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #2:2 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #2:3 begin -1
```

* [演習-copyコンストラクタ](---)

#### moveコンストラクタ、move代入演算子
* moveコンストラクタ、move代入演算子は[moveセマンティクス](---)に従わせる。
* moveコンストラクタ、move代入演算子はnoexceptをつけて宣言し、エクセプションを発生させない。
  noexceptでないmoveコンストラクタ、
  move代入演算子を持つクラスをSTLコンテナのtemplate引数として使用した場合、
  moveの代わりにcopyが使用され、パフォーマンス問題を引き起こす場合がある。
* move代入演算子はlvalue修飾(「[copyコンストラクタ、copy代入演算子](---)」参照)をする。


* [演習-moveコンストラクタ](---)  

#### 初期化子リストコンストラクタ
* [オブジェクトと生成|初期化子リストコンストラクタ](---)は、コンテナクラスの初期化のためのみに定義する。
* 初期化子リストコンストラクタと同じ仮引数を取り得るコンストラクタを定義しない。

#### デストラクタ
* デストラクタの中で[演算子|RTTI](---)機能を使わない(「[コンストラクタ](---)」参照)。
* デストラクタはnoexceptであり、throwするとプログラムが終了するため、デストラクタでthrowしない。

#### オーバーライド
* [オーバーライドとオーバーロードの違い](---)に注意する。
* オーバーライドしたメンバ関数には、オーバーライドされたメンバ関数の機能の意味を踏襲させる。
* オーバーライドする/される一連の仮想関数(デストラクタを含む)について、
    * 全ての宣言にはvirtualを付ける。
    * 一連の仮想関数の最初でも最後でもないものの宣言には、overrideを付ける。
    * 一連の仮想関数の最後のものの宣言には、overrideを付けず、finalを付ける。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #3:0 begin
```

* オーバーライド元の関数とそのオーバーライド関数のデフォルト引数の値は一致させる。
  オーバーライド元の関数にデフォルト引数を持たせないのであれば、
  そのオーバーライド関数にもデフォルト引数を持たせない。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #3:2 begin
```

```cpp
    // @@@ example/programming_convention/func_ut.cpp #3:3 begin -1
```

* privateやprotectedなオーバーライド関数にはデフォルト引数を持たさない
  (「[非メンバ関数/メンバ関数共通|実引数/仮引数](---)」参照)。
  さらに[NVI(non virtual interface)](---)にも従うことにより、
  上の条項の示した一連のオーバーライド関数のデフォルト引数の一致について考慮の必要がなくなり、
  且つこのクラスのユーザはデフォルト引数が使用できるようになる。

* [演習-オーバーライド関数の修飾](---)  

### 非メンバ関数/メンバ関数共通

#### サイクロマティック複雑度
* [ソフトウェア一般|サイクロマティック複雑度](---)は15以下が好ましい。
* 特別な理由がない限り、サイクロマティック複雑度は20以下にする。

#### 行数
* 10行程度が好ましい。
* 特別な理由がない限り、40行以下で記述する。
* [注意] C++の創始者であるビャーネ・ストラウストラップ氏は、
  [プログラミング言語C++ 第4版](https://www.amazon.co.jp/%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0%E8%A8%80%E8%AA%9EC-%E7%AC%AC4%E7%89%88-%E3%83%93%E3%83%A3%E3%83%BC%E3%83%8D%E3%83%BB%E3%82%B9%E3%83%88%E3%83%A9%E3%82%A6%E3%82%B9%E3%83%88%E3%83%A9%E3%83%83%E3%83%97-ebook/dp/B01BGEO9MS)
  の中で、下記のように述べている。

```
    約 40 行を関数の上限にすればよい。 
    私自身は、もっと小さい平均 7 行程度を理想としている。 
```

* [演習-関数分割](---)  

#### オーバーロード
* [オーバーライドとオーバーロードの違い](---)に注意する。
* オーバーロードされた関数は実行目的を同じにする。
  異なる目的のためには異なる名前の関数を用意する。
* [オーバーライド](---)を除き、基底クラスのメンバ関数と同じ名前を持つメンバ関数を派生クラスで宣言、
  定義しない。
  これに反すると[name-hiding](---)のため、基底クラスのメンバ関数の可視範囲を縮小させてしまう。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #4:0 begin
```

* 仮引数の型が互いに暗黙に変換できるオーバーロード関数の定義、使用には気を付ける。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #4:1 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #4:2 begin -1
```

* 暗黙の型変換による関数の使用範囲の拡張を防ぐには、オーバーロード関数を= deleteする。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #4:3 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #4:4 begin -1
```

* [演習-オーバーライド/オーバーロード](---)  
* [演習-オーバーロードによる誤用防止](---)  

#### 演算子オーバーロード
* 演算子をオーバーロードする場合、
    * 単項演算子はメンバ関数で定義する。
    * 二項演算子は非メンバ関数で定義する。
* &&, ||, カンマ(,)をオーバーロードしない。
* 型変換オペレータの宣言、定義を多用しない。
* boolへの型変換オペレータは、explicit付きで定義する。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #5:0 begin
```

* 演算子をオーバーロードする場合、それが自然に使えるようにする。
    * operator == を定義するならば、operator != も定義する（<, >等のその他の例も同様）。
    * operator+ を定義するならば、operator += も定義する(+以外も同様)。
    * copy(またはmove)代入演算子を定義する場合、copy(またはmove)コンストラクタも定義する
      (その際、コードクローンを作りがちなので注意する(「[Copy-And-Swap](---)」参照))。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #5:1 begin
```

* 比較演算子のオーバーロードする場合、
    * C++20であれば、[<=>演算子](---)を定義する。
    * C++17以下であれば、`operator==`と`operator<`の2つの演算子がを定義し、
      [std::rel_ops](---)を使用する。

* [ユーザ定義リテラル演算子](---)のサフィックスには、
  アンダーバーから始まる3文字以上の文字列を使用する。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #5:2 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #5:3 begin -1
```

#### 実引数/仮引数
* 仮引数(「[C++その他|実引数/仮引数](---)」参照)の数は、4個程度を上限とする。
  引数が多くなりすぎる場合、その関数の引数用の構造体を定義し、それを使用して関数を呼び出す。
  この場合、[指示付き初期化](---)を使用する。

* 仮引数を関数の戻り値として利用しない場合
  (且つ仮引数が関数テンプレートの[ユニバーサルリファレンス](---)でない場合)、
    * 基本型やその型のエイリアス、enumは値渡しにする。
    * それ以外のオブジェクトはconstリファレンス渡しにする
      (「[const/constexprインスタンス](---)」参照)。
      ただし、数バイトの小さいオブジェクトは値渡ししても良い。
    * 「引数がnullptrである場合の処理をその関数が行う」場合、constポインタ渡しにする。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:0 begin
```

* [注意] 仮引数をconstリファレンス渡しやconstポインタ渡しにすることで、
    * 値渡しに比べて、ランタイムでの処理が速くなる。
    * リファレンスやポインタ経由で引数に使用されたオブジェクトが変更されるのを防ぐ
      (値渡しであれば引数に使用されたオブジェクトが変更されることはない)。

* 仮引数を関数の戻り値として利用する場合、
    * 「関数が、仮引数がnullptrである場合の処理を行う」場合、ポインタ渡しにする。
    * 「関数が、仮引数がnullptrでないことを前提している」場合、リファレンス渡しにする。

* [ユニバーサルリファレンス](---)を仮引数とする関数テンプレートでは、仮引数は非constにする。

* 継承の都合等で、使用しないにもかかわらず定義しなければならない仮引数には名前を付けない。
  仮引数が使用されていない警告の抑止のために[属性構文](---)を使わない。
  
* 関数f()の仮引数が2つ以上であり、f()に渡す引数をそれぞれに生成する関数があった場合、
  引数を生成する関数の戻り値を直接f()に渡さない。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:1 begin
```

* copyコンストラクタ、copy代入演算子、moveコンストラクタ、
  move代入演算子の仮引数名はrhs(「[略語リスト](---)」参照)にする。
* 二項演算子の仮引数名は、左側をlhs、右側をrhsにする。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:2 begin
```

* 仮引数の意味を明示するために、関数宣言の仮引数の名前は省略しない。
* 仮引数がない関数の()の中には何も書かない。
  Cからリンクされる場合に限り、関数の()の中にはvoidと書く。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:3 begin
```

* 実引数として使用される配列がポインタ型へ暗黙に変換されることを前提に、
  仮引数をポインタ型にしない。また、仮引数を一見、配列に見えるポインタ型にしない
  (「[オブジェクトのコピー|スライシング](---)」で述べたように、
  特に基底クラスを配列にすることは危険である)。
  代わりに配列へのリファレンスもしくはstd::arrayを使用する。 

```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:4 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:5 begin -1
```

```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:6 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:7 begin -1
```

* デフォルト引数は関数のプロトタイプ宣言もしくはクラス宣言内のメンバ関数宣言のみに記述する
  (「[オーバーライド](---)」参照)。
* メンバ関数のデフォルト引数は、
  そのクラス外部からのメンバ関数呼び出しを簡潔に記述するための記法であるため、
  非publicなメンバ関数にデフォルト引数を持たさない。
* デフォルト引数の初期化オブジェクトは定数、もしくは常に等価なオブジェクトにする。
  デフォルト引数の初期化オブジェクトは関数呼出し時に評価されるため、
  引数の初期化オブジェクトが等価でない場合、
  関数の処理が初期化オブジェクトの現在の状態に依存してしまう。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:8 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:9 begin -1
```

* `std::unique_ptr<T>` const&を引数とする関数は、
  その引数が指すオブジェクトが保持しているT型オブジェクトを書き換えることができるため、
  そのような記述をしない。
  関数がそのT型オブジェクトを書き換える必要があるのであれば引数をT&とする。
  書き換える必要がないのであれば引数をT const&とする。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #6:10 begin
```

* [演習-仮引数の修飾](---)  

#### 自動変数
* 一つの文で複数の変数の宣言をしない。
* 自動変数は、それを使う直前に定義することでスコープを最小化する。
* 自動変数は、定義と同時に初期化する。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #7:0 begin -1
```

#### 戻り値型
* メモリアロケータ以外の関数の戻り値をvoid\*にしない。
* 避けがたい理由なしに以下のシンタックスを使用しない。
    * [戻り値型を後置する関数宣言](---)
    * [関数の戻り値型auto](---)
    * [後置戻り値型auto](---)

```cpp
    // @@@ example/programming_convention/func_ut.cpp #8:0 begin
```

* 戻り値を比較的大きなオブジェクトにする場合、パフォーマンスに注意する
  (「[関数の戻り値オブジェクト](---)」参照)。

* 関数が複数の値を返す場合、[std::optional](---)、std::pair、std::tupple、
  構造体オブジェクトを戻り値にして返す。パフォーマンスに著しい悪影響がない限り、
  リファレンス引数で戻り値を返さない(「[関数の戻り値オブジェクト](---)」参照)。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #8:1 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #8:2 begin -1
```

* 処理の成否をbool等で通知し、成功時の戻り値をリファレンス引数で戻す関数や、
  処理の成功時の値と、失敗時の外れ値を戻り値で返す関数を作らない。
  代わりにC++17で導入されたstd::optionalを使用する。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #8:3 begin
```
```cpp
    // @@@ example/programming_convention/func_ut.cpp #8:4 begin -1
```


#### constexpr関数
* 引数が[constexpr](---)の場合、コンパイル時に評価が確定する関数テンプレートもしくはinline関数は、
  [constexpr|constexpr関数](---)として宣言する。
* [constexpr|constexpr関数](---)がコンパイル時に評価される必要がある場合、
  [constexpr](---)の代わりに[constexpr|consteval](---)を使用する。

* [演習-constexpr関数](---)  

#### リエントラント性
* 関数、メンバ関数はなるべくリエントラントに実装する。
* 複数のスレッドから呼び出される関数は必ずリエントラントにする。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #9:0 begin
```

#### エクセプション処理
* 関数はそれが不可避でない限り、[no-fail保証](---)をする。
  [no-fail保証](---)関数は[noexcept](---)を使用してそのことを明示する。
* throwをせざるを得ない場合、最低でも[基本的な安全性の保証](---)をする。
* STLコンテナ(std::string, std::vector等)が発生させるエクセプションはtry-catchせず
  (catchしてデバッグ情報を保存するような場合を除く)、
  プログラムをクラッシュさせる。try-catchしてもできることはない。
* 特別な理由がない限り、コンストラクタ呼び出しは[noexcept](---)と宣言する。
  ネットワーク接続等、簡単にエラーすることをコンストラクタ内で行わない。
* [オープン・クローズドの原則(OCP)](---)、[リスコフの置換原則(LSP)](---)に違反する場合が多いため、
  「throwキーワードによるエクセプション仕様」を使用しない(C++17で廃止)。
* エクセプションをthrowしないことが確定している関数は、[noexcept](---)と宣言する。
  move代入演算子を[noexcept](---)と宣言することは特に重要である。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #10:0 begin
```

* try-catchが不可避である場合、以下の理由によりconstリファレンスで受け取る。
    * 実態で受け取るとオブジェクトの[オブジェクトのコピー|スライシング](---)が起こる場合がある。
    * 受け取ったエクセプションオブジェクトを書き換えるべきではない。

* エクセプションによるリソースリークを避けるため[RAII(scoped guard)](---)でリソースを管理する。
* 一連のcatch節では、catchするエクセプションの型の最もマッチ率の高いcatch節で処理されるのではなく、
  マッチした最上位のcatch節で処理されるため、
  catchするエクセプションの型に継承関係があるのであれば、継承順位が低い順番にcatchする。
  また、catch(...)は一番最後に書く(関数tryブロックの場合も同様にする)。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #10:1 begin
```

* [exception-unfriendly](---)な関数はエクセプションを発生させないようにする。
* エクセプションをthrowする場合、独自定義したオブジェクトを使用しない。
  代わりにstd::exceptionか、これから派生したクラスを使用する。
  また、throwされたオブジェクトのwhat()から、throwされたファイル位置が特定できるようにする
  (「[ファイル位置を静的に保持したエクセプションクラスの開発](---)」参照)。


* noexceptと宣言された関数へのポインタへ、noexceptでない関数のポインタを代入しない
  (C++17では[ill-formed](---)になる)。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #10:2 begin
```

* [演習-エクセプションの型](---)  

#### ビジーループ
* 待ち合わせにビジーループを使わない。イベントドリブンにする。

```cpp
    // @@@ example/programming_convention/func_ut.cpp #11:0 begin
```

* [注意] C++11からイベント通知のためにstd::condition_variable
  (「[並行処理](---)」参照)が導入された。

## 構文

### 複合文
* if, else, for, while, do後には複合文を使う。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #0:0 begin -1
```

* 空の複合文には、何もすることがないという意図を表現するため、";"だけの文を置き、
  空の複合文である事を明示する。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #0:1 begin -1
```

### switch文
* caseラベル、defaultラベルに関連付けられた一連の文はできだけフォールスルーさせない。
  実装がシンプルになる等の理由からフォールスルーさせる場合、
  [属性構文](---)を使用しそれが意図的であることを明示するため以下のような記述する。

```cpp
    // fallthrough          // C++14以前

    [[fallthrough]];        // C++17以降
```

* defaultラベルは省略せず、switch文の末尾に書く。
    * defaultラベルに関連付けられた処理がない場合は、breakのみを記述する。
    * 論理的にdefaultラベルに到達しないのであれば、
      defaultラベルに続いてassert(false)を実行することで、
      そこを通過してはならないことを明示する(「[assertion](---)」参照)。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #1:0 begin -1
```

* switch文のオペランド変数を生成する場合、
  できるだけ[初期化付きswitch文](---)を使用し、その変数のスコープを最小に留める。

### if文
* if-else-ifと連続する場合は、else文で終了させる。
  最後のelseのブロックでやるべき処理がないのであれば、そのブロックに;のみを記述する。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #2:0 begin -1
```

* if-else-ifの最後のelseのブロックに論理的に到達しないのであれば、
  そのブロックでassert(false)を実行する(「[assertion](---)」参照)。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #2:1 begin -1
```

* 条件が2つ以上且つ、switchで表現できる条件文には、ifではなくswitchを使用する。
* ifの条件式が、コンパイル時に定まるのであれば、[constexpr if文](---)を使用する。

* if文のオペランド変数を生成する場合、
  できるだけ[初期化付きif文](---)を使用し、その変数のスコープを最小に留める。

### while文
* while文には、[初期化付きif文](---)/[初期化付きswitch文](---)のような構文は存在しないが、
  while文のオペランド変数を生成するする場合、
  [初期化付きfor文(従来のfor文)](---)を使用し、その変数のスコープを最小に留める。

### 範囲for文
* 配列やコンテナの全要素にアクセスするような繰り返し処理には、
  [off-by-oneエラー](https://ja.wikipedia.org/wiki/Off-by-one%E3%82%A8%E3%83%A9%E3%83%BC)
  が避けられ、従来よりもシンプルに記述できる[用語解説|構文|範囲for文](---)を使用する。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #3:0 begin -1
```

* 独自のコンテナクラスを定義する場合、STLコンテナと同様の要件を満たすbegin()、end()や、
  cbegin()、cend()も定義し、そのコンテナに[用語解説|構文|範囲for文](---)を適用できるようにする
  (「[グローバルnew/deleteのオーバーロード|デバッグ用イテレータ](---)」参照)。

* [演習-コンテナの範囲for文](---)  

### 制御文のネスト
* breakとの関係がわかりづらい、ブロックが巨大になる等の問題があるため、
  if, for, while, do-while, switch文に付随するブロックの中にswitch文を書かない。

### return文
* returnの後に括弧をつけない。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #4:0 begin -1
```

* 下記のようなreturnしない関数には、[[noreturn]]をつけて宣言、定義する。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #4:1 begin
```

### goto文
* 二重以上のループを抜ける目的以外でgotoを使用しない。
* 二重以上のループを抜ける目的でgotoを使用する場合、gotoのジャンプ先ラベルはそのループの直後に置く。

### ラムダ式
* [言語機能|ラムダ式](---)を複雑にしない。
    * できるだけワンライナーにする。
    * 必ず10行以下にする。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #5:0 begin -1
```

* デフォルトのキャプチャ方式は、ローカル変数を無限定にキャプチャしてしまうため使用しない。
    * C++11では、キャプチャする変数ごとに代入キャプチャか参照キャプチャを使用する。
    * C++14以降では、初期化キャプチャを使用する。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #5:1 begin
```

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #5:2 begin
```

* 外部のオブジェクトを参照キャプチャしたクロージャを、
  その外部オブジェクトのライフタイムを超えて使用しない。
    * 関数で作られたクロージャがその関数のローカル変数のハンドルを使用するのであれば、
      そのクロージャをその関数外で使用しない。
    * オブジェクトで作られたクロージャがそのメンバ変数のハンドルを使用するのであれば、
      そのオブジェクトの終了後にそのクロージャを使用しない。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #5:3 begin
```

* C++17以降では、 コンパイル時に戻り値が確定するラムダ式の呼び出し式は定数にできるため、
  そのようなラムダ式は[constexprラムダ](---)として宣言する。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #5:4 begin -1
```
```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #5:5 begin
```

* [演習-ラムダ式](---)  
* [演習-ラムダ式のキャプチャ](---)  

### マクロの中の文
* マクロの中に文がある場合、do-while(0)イデオムを使用する(「[関数型マクロ](---)」参照)。

```cpp
    // @@@ example/programming_convention/syntax_ut.cpp #6:0 begin
```

## 演算子

### 優先順位
* 規格上で[演算子のオペランドの評価順位](---)が決まっていても、一見優先順位が分かりづらい式では、
  順序を明示するために丸括弧を使う。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #0:0 begin -1
```

* [注意] 複合代入式と、それと等価に見える式での演算順序の違いに気を付ける。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #1:0 begin -1
```

### 代入演算
* [単純代入](---)のみからなる文を除き、1つの文で複数の代入を行わない。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #2:0 begin -1
```

* 一部の例外を除き、ifの条件文の中で代入しない。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #2:1 begin -1
```

### ビット演算
* オーバーフロー、アンダーフローしたときの符号の扱い方が未定義であるため、
  signed変数へのビット演算を使用しない。
  (「2の階乗での除算は、ビット演算に置き換えることで実行速度が速くなる」というのは都市伝説である)。
* [注意] ビット演算にはstd::bitsetや[BitmaskType](---)を使用することもできる。

### 論理演算
* &&や||の論理演算子の右オペランドで[副作用](---)のある処理をしない。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #3:0 begin -1
```

### 条件演算子
* 単純なif文よりも、条件演算子を優先して使用する
  (const変数の条件付き初期化は条件演算子でのみ可能である)。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #4:0 begin -1
```

* [演習-条件演算子](---)  

### メモリアロケーション
#### new
* オブジェクトのダイナミックな生成には、特別な理由がない限りnewを使用せず、
  `std::make_unique<>`や`std::make_shared<>`を使用する。
  また、特別な理由でnewした場合、そのポインタは[スマートポインタ](---)で管理する。
* `std::shared_ptr<>`でダイナミックに生成したオブジェクトを管理する場合、
  [オブジェクトの循環所有](---)が発生しないように気を付ける(適切に[std::weak_ptr](---)を使う)。
* new(nothrow)、プレースメントnewは使用しない。
* 配列型オブジェクトのダイナミックな生成を避け、
  代わりにstd::arrayをダイナミックに生成するか、std::vectorを使用する。
* newの戻り値がnullptrであることはない、
  もしくはnewがnullptrを返してきた場合、リカバリーすることはできないため、
  new演算子の返り値をnullptrと比較しない。
    * operator newを独自に実装した場合でも、newはnullptrを返してはならない。
      メモリが不足した場合、assert(false)させるかstd::bad_allocをthrowする。
* スタック上で生成しても差し支えないオブジェクトをダイナミックに生成しない。
* newを禁止したいクラスには、privateなoperator new()を宣言する(定義は不要)か、= deleteする。

#### delete
* [不完全型](---)のオブジェクトへのポインタをdeleteしない。
  特に「[Pimpl](---)」を使用する場合には注意が必要である。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #5:0 begin
```

* 不完全型と同じような不具合が起こるためvoid\*をdeleteしない。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #5:1 begin
```

* deleteはオペランドがnullptrであった場合、何もしないため、delete対象ポインタをnullptrと比較しない。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #5:2 begin -1
```

* [演習-delete](---)  

#### メモリ制約が強いシステムでの::operator new
* [注意]このルールは以下のようなソフトウェアを対象とする。  
    * 使用できるメモリが少なく、且つほとんど再起動されない。
    * メモリリークの可能性を否定できない3rdパーティライブラリを使っている。
    * MISRA/AUTOSAR C++等のヒープの使用制限が強い規約を守る必要がある
      (ヒープを使った場合の最長処理時間の決定が難しいためリアルタイム性に問題がある)。

  このようなソフトウェア開発においてはこのルールは重要であるが、
  逆にそのような制限のないソフトウェア開発においては不要である。

* デフォルトのグローバルnewを使用しない。
    * リアルタイム性に制約のあるシステムでは、
      「[グローバルnew/deleteのオーバーロード](---)」で述べたようなnewを実装する。
    * メモリ制限が強いシステムでは、ダイナミックなオブジェクト生成を避け、
      やむを得ない場合、「[クラスnew/deleteのオーバーロード](---)」
      で述べたようなクラス毎のnewを実装する。

* エクセプションの送出にダイナミックなメモリアロケーションを使用している場合
  (多くのコンパイラはmalloc/newを用いてエクセプション送出を行っている)、
  エクセプションの送出をしない(「[エクセプション処理機構の変更](---)」参照)。


### sizeof
* sizeof(型名)とsizeof(インスタンス名)の両方が使える場合、sizeof(インスタンス名)を優先的に使用する。
* ポインタ型変数に関して、それが指しているインスタンスのサイズを獲得する場合は、
  sizeof(\*ポインタ型変数名)を使用する
  (そのポインタがnullptrであってもデリファレンスされないので問題ない)。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #6:0 begin -1
```

* 上記例を除き、sizeof演算子のオペランドは一見[副作用](---)を持っているような式を含んではならない。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #6:1 begin -1
```

* C++03のテンプレートの実装でよく使われたsizeofによるディスパッチを行わない。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #6:2 begin
```
```cpp
    // @@@ example/programming_convention/operator_ut.cpp #6:3 begin -1
```

* 一見、配列に見えるポインタをsizeofのオペランドにしない。
  (「[非メンバ関数/メンバ関数共通|実引数/仮引数](---)」参照)。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #6:4 begin
```

* [演習-sizeof](---)  

### ポインタ間の演算
* 同一オブジェクト(配列等)の要素を指さないポインタ間の除算や比較をしない。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #7:0 begin -1
```

### RTTI
* [注意] [RAII(scoped guard)](---)との混乱に気を付ける。
* [Run-time Type Information](---)を使用したラインタイム時の型による場合分けは、
  それ以外に解決方法がない場合や、実装が大幅にシンプルになる場合を除き行わない
  (「[等価性のセマンティクス](---)」参照)。
    * 単体テストやロギングのでtypeidの使用は問題ない。
    * 派生クラスの型によって異なる動作にしたい場合には、仮想関数を使うか、
      [Visitor](---)パターン等により実現できる。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #8:0 begin
```

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #8:1 begin
```

* コンストラクタやデストラクタ内でRTTIの機能を使わない
  (「[コンストラクタ](---)」、「[デストラクタ](---)」参照)

* [演習-dynamic_castの削除](---)  

### キャスト、暗黙の型変換
* キャストが必要な式等は、設計レベルの問題を内包していることがほとんどであるため、設計を見直す。
* Cタイプキャストは使用しない。
* const_cast、 dynamic_castはそれ以外に解決方法がない場合や、
  実装が大幅にシンプルになる場合を除き使用しない。
* reinterpret_castはハードウエアレジスタ等のアドレスを表す目的以外で使用しない。
* ダウンキャストを行う目的でstatic_castを使用しない。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #9:0 begin
```

* strnlenや、memcpyのような例を除き、void\*への暗黙の型変換を行わない
  (これをすると、後にダウンキャストが必要になる)。

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #9:1 begin
```

```cpp
    // @@@ example/programming_convention/operator_ut.cpp #9:2 begin -1
```

* strnlenや、memcpyのような例を除き、配列からポインタへの暗黙の型変換をしない。
  配列を関数の仮引数にしたい場合は、配列へのリファレンスを使う。
  これにより、その関数内でも配列の長さが使用できる
  (「[非メンバ関数/メンバ関数共通|実引数/仮引数](---)」、
  「[sizeof](---)」、「[関数型マクロ](---)」参照)。

* [演習-キャスト](---)  

## プリプロセッサ命令
* `#include`を除き、プリプロセッサ命令を使用しない。
  特に関数内、クラス宣言内での#if/#ifdef等の使用は可読性を著しく低下させるため、
  それ以外の解決方法がない場合を除く使用しない。

```cpp
    // @@@ example/programming_convention/preprocessor_ut.cpp #0:0 begin
```

* ヘッダファイル内での#if/#ifdef/#ifndefに関しては、以下の用途以外では使わない。
    * 二重インクルードガード(「[二重読み込みの防御](---)」参照)
    * Cとシェアするヘッダファイルでの下記例


```cpp
    // @@@ example/programming_convention/preprocessor.h #0:0 begin
```

* ##によるシンボルの生成を使用しない。

```cpp
    // @@@ example/programming_convention/preprocessor_ut.cpp #0:1 begin
```

* 出荷仕向け等の理由から、やむを得ずプリプロセッサ命令を使わざるを得ない場合、
  #if等で囲まれた区間をなるべく短くする。
  これによりより多くのコードがコンパイルされるようにできる
  (「[using宣言/usingディレクティブ](---)」参照)。

```cpp
    // @@@ example/programming_convention/preprocessor_ut.cpp #0:2 begin
```
```cpp
    // @@@ example/programming_convention/preprocessor_ut.cpp #0:3 begin
```

### 関数型マクロ
* 関数型マクロ以外に方法がない場合を除き、関数型マクロを定義しない。
  その代わりに関数テンプレートを定義する。こうすることで下記のような誤用を防ぐことができる。

```cpp
    // @@@ example/programming_convention/preprocessor_ut.cpp #1:0 begin
```

* 関数型マクロの中に文がある場合、do-while(0)イデオムを使用する
  (「[マクロの中の文](---)」参照)。

### マクロ定数
* マクロ定数以外に方法がない場合を除き、マクロ定数を定義しない。
  その代わりにconstexpr uint32\_t等や、enumを定義する。

```cpp
    // @@@ example/programming_convention/preprocessor_ut.cpp #2:0 begin
```

## パッケージとその構成ファイル

### パッケージの実装と公開
* パッケージに関して、以下の構造を持つようにソースコードを構成する
  (「[アーキテクチャとファイル構造](---)」参照)。
    * ソフトウェアはパッケージに分割される。
    * パッケージは、複数のヘッダファイルと複数の.cppファイルから作られる。
    * パッケージを構成するファイルは、このパッケージ専用ディレクトリに保存される。
    * パッケージは他のパッケージとは排他的な[スコープ|名前空間](---)を持ち、
      パッケージ内で宣言、定義され、外部パッケージに公開される識別子はその名前空間に包含される。
      外部パッケージに公開されない識別子は、そのパッケージでのみ使用される名前空間か、
      無名名前空間に包含されるようにする。
    * パッケージは、サブパッケージを内包する場合がある。
      サブパッケージは、パッケージの要件を満たす。

* 上記前提のもと、パッケージが外部にサービスを提供する場合、
  そのパッケージで定義されるヘッダファイルは以下のどちらかのみを行うように構成する。
    * 外部へ提供するクラス等を公開する(外部公開ヘッダファイル)。
    * パッケージ内部のみで使用するクラス等の宣言、定義を行う(外部非公開ヘッダファイル)。

![パッケージの構造](plant_uml/package.png)

* h/PackageBのディレクトリPackageBは冗長に見えるが、
  h配下にそれを保持するディレクトリ名と同じ名前のディレクトリを持つことは、
  可読性の観点から重要である。
  このディレクトリため、他のパッケージから識別子をインポートするためのインクルードディレクティブは
  以下のように記述されることになる。
  このような記述を可能とするために、
  PackageBがエクスポートするヘッダを使用するコードのコンパイルに
 「インクルールパスにPackageB/hを指定する」オプションを使用する。

```cpp
    // @@@ example/programming_convention/pkg.cpp #0:0 begin
```

* 外部公開ヘッダファイルは、ビルド時に他のパッケージから参照できるディレクトリに配置する。
    * 外部公開ヘッダファイルは、外部非公開ヘッダファイルをインクルードしない。
    * 外部非公開ヘッダファイルは、ビルド時に他のパッケージから参照できるディレクトリに配置しない。

### 識別子の宣言、定義
* [ODR](https://en.cppreference.com/w/cpp/language/definition)を守る。
  つまり、一つの識別子は全ソースコード内にただ一つの定義を持つようにする。
* 一つの.cppファイル内のみで使用される識別子は、
  その.cppファイル内の無名名前空間にその定義や宣言を持つ。
* ヘッダファイルで宣言された識別子が.cppファイル内に定義をもつ場合、
  その.cppファイルにそのヘッダファイルをインクルードさせる。
  特に、非メンバ関数や変数の宣言と定義を矛盾させないために、このルールは特に重要である
  (「[非メンバ関数](---)」参照)。

### 依存関係
* 不要/不適切な依存関係(「[インターフェース分離の原則(ISP)](---)」や
  「[依存関係逆転の原則(DIP)](---)」への違反)を作らない。
    * 依存関係を最小にとどめるために、前方宣言を適切に使用する。
        * STLクラス(やクラスのエイリアス)の前方宣言をしない
          (例えば、「std::stringをクラス宣言することでstringヘッダファイルへの依存関係を作らない」
          といった方法は、std::stringがクラスでないため想定通りに働かない)。
    * SOLIDの原則やデザインパターン、イデオム等を適切に使用することにより、依存関係を適切に保つ。
        * 依存関係の伝搬を回避したい場合、[Pimpl](---)イデオムを使い実装の詳細を隠蔽する。
        * 上位概念が下位概念に依存することを避ける場合、
          「[依存関係逆転の原則(DIP)](---)」での例や[Observer](---)等を適用する。
    * パッケージ間の相互、循環依存関係を作らない。

![パッケージの構造(NG)](plant_uml/package_ng.png)

### 二重読み込みの防御
* 二重インクルードを防ぐため、 ヘッダファイルには#includeガードを付ける。
  ガード用のマクロは、<パス名>\_<ファイル名>\_H\_とする。

```cpp
    // @@@ example/programming_convention/lib/inc/xxx.h #0:0 begin
```

* コンパイラが#pragma onceをサポートしている場合は、
  上記方法ではなく下記をヘッダファイル先頭に記述する。

```cpp
    // @@@ example/programming_convention/lib/inc/xxx.h #0:1 begin
```

### ヘッダファイル内の#include
* 不要な依存関係を作らないようにするため、
  ヘッダファイルは、そのコンパイルに不要なヘッダファイルをインクルードしない。
* ヘッダファイルが外部からインポートする型(class、struct、enum)
  のデリファレンスがそのヘッダファイル内で不要な場合、前方宣言を使い依存関係を小さくする。 

```cpp
    // @@@ example/programming_convention/header.h #0:0 begin
```

```cpp
    // @@@ example/programming_convention/header_ut.cpp #0:0 begin -1
```

### #includeするファイルの順番
* ユーザ定義ヘッダファイルより、システムヘッダファイルの#includeを先に行う。
* システムヘッダファイルは、アルファベット順に#includeを行う。
* ユーザ定義ヘッダファイルは、アルファベット順に#includeを行う。

### #includeで指定するパス名
* ユーザ定義のヘッダファイルは""で囲み、システムヘッダファイルは、`<>`で囲む。
* 他のパッケージの外部非公開ヘッダファイルを読み込まないようにするために、
  #includeのパス指定に"../"(ディレクトリ上方向への移動)を使用しない。

```cpp
    // @@@ example/programming_convention/lib/header.cpp #0:0 begin
```

* ヘッダファイル以外のファイル(.cppファイル等)をインクルードしない。

## スコープ
### スコープの定義と原則
この章で扱うスコープを下記のように定義する(「[パッケージの実装と公開](---)」参照)。

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

* このドキュメント執筆時のコンパイラ/ビルダのC++20での[モジュール](---)のサポート状況が
  万全ではないため、
    * モジュールを定義するためのmoduleを使用しない。
    * モジュール外に公開する識別子を定義するexport使用しない。
    * exportされた識別子を使用するためにimportを使用しない。

* [name-hiding](---)を起こすとコードの可読性が著しく低下するため、
  スコープが重複する「名前のない名前空間内」(例えば、ブロックとそれを内包するブロック)
  にある「同一名を持つ識別子」を宣言、定義しない。

```cpp
    // @@@ example/programming_convention/scope.h #0:0 begin
```

```cpp
    // @@@ example/programming_convention/scope_ut.cpp #0:0 begin
```

### 名前空間
* グローバル名前空間には下記以外の識別子を定義、宣言しない。
    * main関数
    * グローバルnewのオーバーロード
    * Cとシェアする識別子
* パッケージ毎に名前空間を定義する
  (「[パッケージの実装と公開](---)」、[名前空間名](---)」参照)。
* 外部リンケージの不要な識別子は.cpp内の無名名前空間で宣言、定義する。
* 名前空間Xxx内で定義されたテンプレートやinline関数から参照されるため、
  外部公開用ではないにもかかわらずヘッダファイル内に定義が必要な識別子は、
  名前空間Xxx::Inner\_内で定義する。
  名前空間Xxx::Inner\_内の識別子は、単体テストを除き他のファイルから参照しない。

```cpp
    // @@@ example/programming_convention/scope2.h #0:0 begin
```

### using宣言/usingディレクティブ
* 識別子のインポートのための[using宣言](---)は下記のような場合のみに使用する
  (「[継承コンストラクタ](---)」、「[オーバーライドとオーバーロードの違い](---)」参照)。

```cpp
    // @@@ example/programming_convention/scope_ut.cpp #1:0 begin -2
```

* 下記のような場合を除き、[usingディレクティブ](---)は使用しない。
  使用する場合でもその効果をブロックスコープ内のみに留める。

```cpp
    // @@@ example/programming_convention/scope_ut.cpp #1:1 begin -2
```

* 出荷仕向け等の理由を除き、inline namespaceを使用しない(「[プリプロセッサ命令](---)」参照)。

```cpp
    // @@@ example/programming_convention/scope_ut.cpp #1:2 begin
```
```cpp
    // @@@ example/programming_convention/scope_ut.cpp #1:3 begin
```
```cpp
    // @@@ example/programming_convention/scope_ut.cpp #1:4 begin -1
```

* [演習-usingディレクティブ](---)  

### ADLと名前空間による修飾の省略
* 名前空間の修飾を省略した識別子のアクセスには、
  下記のような副作用があるため、[ADL](---)を使用する目的以外で使用しない
  (「[識別子の命名](---)」を順守することで、識別子の偶然の一致を避けることも必要)。

```cpp
    // @@@ example/programming_convention/scope_ut.cpp #2:0 begin
```


### 名前空間のエイリアス
* ネストされた長い名前空間を短く簡潔に書くための名前空間エイリアスは、
  その効果をブロックスコープ内のみに留める。
* 名前空間のエイリアスを[using宣言/usingディレクティブ](---)で使用しない。

```cpp
    // @@@ example/programming_convention/scope_ut.cpp #3:0 begin
```

## ランタイムの効率
* ランタイム効率と、可読性のトレードオフが発生する場合、可読性を優先させる。
* やむを得ず可読性を落とすコードオプティマイゼーションを行う場合は、
  プロファイリング等を行い、ボトルネックを確定させ、必要最低限に留める。
  また、開発早期での可読性を落とすコードオプティマイゼーションは行わない。

### 前置/後置演算子の選択
* 後置演算子の一般的な動作は、下記のようになるため前置演算子の実行に比べて処理が多い。
  どちらを使用してもよい場合は前置演算子を使う。
    1. 自分(オブジェクト)をコピーする。
    2. 自分に前置演算子を実行する。
    3. コピーされたオブジェクトを返す。

```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #0:0 begin
```
```cpp
    // @@@ example/h/measure_performance.h #0:0 begin
```
```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #0:1 begin -1
```

* ソースコードの統一性のため、このオーバーヘッドがない基本型についても、同じルールを適用する。

### operator X、operator x=の選択
* 前置/後置演算子と同じような問題が発生するため、どちらを使っても問題ない場合は、
  operator Xではなく、operator X=を使う。

```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #1:0 begin
```
```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #1:1 begin -1
```

* ソースコードの統一性のため、このオーバーヘッドがない基本型についても、同じルー ルを適用する。

### 関数の戻り値オブジェクト
* 基本型やenum、`std::unique_ptr<>`、
  `std::optional<>`等のサイズの小さいクラス以外のオブジェクトを関数の戻り値にしない。
* [注意] ローカルオブジェクトに対して[RVO(Return Value Optimization)](---)が有効であれば、
  そのオブジェクトを戻り値にしても良い。
* [注意] stdのコンテナは、RVOが有効でなくてもmoveが行われるため、関数の戻り値として使用しても良い。
* [注意] std::stringについては、RVOに加えて、
  [SSO(Small String Optimization)](---)が使用されていることが多い。
  そのようなコンパイラを使用している場合、std::stringは小さいオブジェクトとして扱って良い。

```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #2:0 begin
```

### move処理
* [ディープコピー](---)の実装を持つクラスへのcopy代入の多くがrvalueから行われるのであれば、
  moveコンストラクタや、move代入演算子も実装する。
* 関数の戻り値にローカルオブジェクトを使用する場合、
  [RVO(Return Value Optimization)](---)の阻害になるため、そのオブジェクトをstd::moveしない。

```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #3:0 begin
```

### std::string vs std::string const& vs std::string_view
* 文字列を受け取る関数の仮引数の型に関しては下記のような観点に気を付ける。
  以下に示す通り、このような仮引数の型をstd::string const&にすることが最適であるとは限らない。

```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #4:0 begin
```
```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #4:1 begin -1
```
```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #4:2 begin -1
```
```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #4:3 begin
```
```cpp
    // @@@ example/programming_convention/runtime_ut.cpp #4:4 begin -1
```

### extern template
* 何度もインスタンス化が行われ、
  それによりROMの肥大化やビルドの長時間化を引き起こすようなクラステンプレートに対しては、
  extern templateを使う。

```cpp
    // @@@ example/programming_convention/string_vector.h #0:0 begin
```
```cpp
    // @@@ example/programming_convention/string_vector.cpp #0:0 begin
```

## 標準クラス、関数の使用制限
### STL
* C++のバージョン毎に定められた非推奨の機能、関数、クラスを使わない。
  これらについては、[C++日本語リファレンス](https://cpprefjp.github.io/)の
  * [C++11の機能変更](https://cpprefjp.github.io/lang/cpp11.html)
  * [C++14の機能変更](https://cpprefjp.github.io/lang/cpp14.html)
  * [C++17の機能変更](https://cpprefjp.github.io/lang/cpp17.html)
  に詳細が書かれている。

* [g++](---)/[clang++](---)等の優れたコンパイラを適切なオプションで使用することで、
  非推奨の機能、関数、クラスの使用を防ぐ。

#### スマートポインタの使用制限
* std::auto_ptrを使用しない(C++17で廃止)。
* ダイナミックに生成した[オブジェクトの排他所有](---)を行う場合、`std::unique_ptr<>`を使用する。
* ダイナミックに生成した[オブジェクトの共有所有](---)を行う場合、`std::shared_ptr<>`を使用する。
* `std::shared_ptr<>`を使用する場合、[オブジェクトの循環所有](---)が発生しないように気を付ける。

#### 配列系コンテナクラスの使用制限
* 配列系のコンテナを使用する場合、コンパイル時に要素数の上限が
    * 定まるのであれば、std::arrayを使用する。
    * 未定ならば、std::vectorを使用する。
* `std::vector<bool>`は、std::vectorの特殊化であり、通常のstd::vectorと同じようには扱えない。
  `std::vector<bool>`を使用する場合、その要素へのハンドルがbool&やbool\*でないことに注意する。
* std::arrayを除くコンテナクラスは、
  それ自体でメモリリソースの[RAII(scoped guard)](---)を実現しているため、newしない。

#### std::stringの使用制限
* std::stringは、
  それ自体でメモリリソースの[RAII(scoped guard)](---)を実現しているため、newしない。
* std::stringの添字演算子[]は領域外アクセスを通知しない
  ([std::out_of_range](https://cpprefjp.github.io/reference/stdexcept.html)
  エクセプションを発生させない)ため、std::string::at() を使用する
  (「[安全な配列型コンテナ](---)」参照)。
* std::string.data()は、C++のバージョンによってはNULLターミネイトが保証されていないため、
  std::string.c_str() を使用する。

#### std::string_viewの使用制限
* std::string_viewが保持するポインタが指す文字列の所有権は、他のオブジェクトが保持しているため、
  std::string_viewの初期化や、copy代入の右辺にrvalueを使用しない。

```cpp
    // @@@ example/programming_convention/string_view_ut.cpp #0:0 begin -1
```
```cpp
    // @@@ example/programming_convention/string_view_ut.cpp #0:1 begin -1
```

* 文字列リテラルで初期化されたstd::string_viewと文字列リテラルとの微妙な違いに気を付ける。

```cpp
    // @@@ example/programming_convention/string_view_ut.cpp #1:0 begin -1
```
```cpp
    // @@@ example/programming_convention/string_view_ut.cpp #2:0 begin -2
```


### POSIX系関数
#### 使用禁止関数一覧

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

#### 使用禁止関数の理由や注意点
##### バッファオーバーランを引き起こしやすい関数
* 以下の関数は、バッファオーバーフロー等のバグを引き起こしやすい。

```
    gets(), scanf(), strcpy(), strcat(), sprintf(), vsprintf(), wcscat(), wcscpy()
```

##### コマンドインジェクション防止
* 以下の関数は、外部コマンドの実行時に環境変数に依存してしまう。

```
    execl(), execlp(), execv(), execvp(), popen(), system()
```

##### obsolete関数
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

##### LEGACY関数
* 以下の関数は、すでに役目を終えた。

```
    sigstack(), cuserid(), getopt(), getw(), ttyslot(), valloc(), ecvt(), fcvt(), 
    gcvt(), mktemp(), bcmp(), bcopy(), bzero(), index(), rindex(), utimes(), getwd(),
    brk(), sbrk(), rand()
```

##### スレッドセーフでない関数
* 以下の関数は、スレッドセーフでない。

```
    asctime(), ctime(), getgrgid(), getgrnam(), getlogin(), getpwuid(), getpwnam(), gmtime(),
    localtime(), ttyname(), 
    ctermid(), tmpnam() (引数がNULLのとき、非リエントラントになる)
```

##### 標準外関数等
* 可変長配列や、alloca()は、標準外である。

##### 扱いが難しい関数
* signalの扱いは極めて難しく、安定動作をさせるのは困難である。
  「シグナルのリエントラント問題を解決でき、使用できる関数に制限がない」という利点があるため、
   signal()の代わりに、 signalfd() を使用する。 
* 排他的にファイルをオープンできないため、tmpfile()を使用しない。代わりにmkstemp()を使用する。

#### 典型的な注意点
##### リソースリークを引き起こしやすい関数
* open()/close()、fopen()/fclose()はリソースリークを引き起こしやすい。
  「[RAII(scoped guard)](#8.9)」で例示したコードやstd::fstreamを使うことでその問題を回避する。

##### シンボリックリンクの検査
* シンボリックリンクはlstat()のみで検査せず、以下のように検査する。

    1.	ファイル名をlstat()
    2.	ファイルをopen()
    3.	2で取得したファイル記述子に対してfstat()
    4.	1, 3の情報を照合して同一ファイルであることを確認

##### strncpy(), strncat()の終端
* 下記のような問題を回避するために文字列操作にはstd::stringを使用する。
    * sizeof(dst) <= strlen(src) の場合、strncpy(dst, src, sizeof(dst) - 1)の呼び出しは、
      dstの文字列を'\0'終端しない。
    * コピーすべきデータが無くなると、dstの残りを'\0'で埋めるので性能上の問題がある。
    * strncpy(), strncat()ともに、
      sizeof(dst) < strlen(src) のときにsrcの文字列が切り捨てられたことを判別できない。

##### TOCTOU (Time Of Check, Time Of Use)
* open()前にaccess()でファイルの存在を確認する等、チェックして使用するパターンでは、
  この動作がアトミックに行われないため問題が発生する。
  この問題回避の一般解はないが「ファイルの存在確認後、read-open」のような場合では、
  「いきなりread-openし、エラーした場合に対処」することでアトミックな処理にできる。

##### メモリアロケーション
* new/deleteとmalloc/freeの混在を避けるため下記の使用をしない。
  newしたオブジェクトのポインタをfreeした場合、そのオブジェクトのデストラクタが呼び出されず、
  リソースリークしてしまうことがある。

```
    malloc(), realloc(), free()
```

##### 非同期シグナル
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

## その他
### assertion
* 論理的にありえない状態(特に論理的に到達しないはずの条件文への到達)を検出するために、
  assert()を使用する(「[switch文](---)」、「[if文](---)」参照)。
* assert()はコンパイルオプションにより無効化されることがあるため、
  assert()の引数に[副作用](---)のある式を入れない。
* ランタイムでなく、コンパイル時に判断できる論理矛盾や使用制限には、static\_assertを使用する。

```cpp
    // @@@ example/programming_convention/etc.cpp #0:0 begin
```

* static\_assert、assert両方が使える場合には、static\_assertを優先して使用する。

* [演習-アサーションの選択](---)  
* [演習-assert/static_assert](---)  

### アセンブラ
* アセンブラ関数は、.asm等で定義し、ヘッダファイルでCの関数として宣言する。
* アセンブラ関数も、関数/メンバ関数のルールに従う(「[非メンバ関数/メンバ関数](---)」参照)。
* インラインアセンブラや、それを含む[関数型マクロ](---)がソースコード全域に広がらないようにする。

### 言語拡張機能
* #pragma once以外で、且つそれ以外に実装方法がない場合を除き、
  コンパイラ独自の言語拡張機能を使用しない。
* オブジェクトのアライメントが必要な場合、
    * alignas、alignofを使用する(「[固定長メモリプール](---)」参照)。
    * コンパイラ独自のアライメント機能(#pragma等)の使用を避ける。
* 繰り返し使用する#pragmaに関しては、\_Pragma演算子とマクロを組み合わせて使用する。
  コンパイラの警告には従うべきであるが、ごく稀に無視せざるを得ない場合がある。
  そういった場合、その警告は下記例のような方法で抑止する。

```cpp
    // @@@ example/programming_convention/etc.cpp #1:0 begin
```

## 特に重要なプログラミング規約
本章で取り上げた規約は、重要度という観点で様々なレベルのものが混在するため量も多く、
すぐに実践することが難しいかもしれない。
そういった場合には、まずは特に重要な下記リストを守ることから始めるのが良いだろう。

* 浮動小数点型をなるべく使わない([型とインスタンス|算術型|浮動小数点型](---))。
* const/constexprを積極的に使用する([const/constexprインスタンス](---), [メンバ関数](---))。
* すべてのインスタンスは定義と同時に初期化する([インスタンスの初期化](---))。
* クラスのpublicメンバ関数は最大7個([メンバの数](---))。
* クラスのメンバ変数は最大4個([メンバの数](---))。
* クラスのメンバ変数はprivateのみ([アクセスレベルと隠蔽化](---))。
* クラスのメンバ変数はコンストラクタ終了時までに初期化する([非静的なメンバ変数](---))。
* friendは使用しない([アクセスレベルと隠蔽化](---))。
* 派生は最大2回([継承/派生](---))。
* 関数は小さくする([非メンバ関数/メンバ関数共通|サイクロマティック複雑度](---))。
* 関数の仮引数は最大4個([非メンバ関数/メンバ関数共通|実引数/仮引数](---))。
* グローバルなインスタンスは使わない([スコープ](---))。
* throw, try-catchは控えめに使用する([エクセプション処理](---))。
* 構文に関しては以下に気を付ける。
    * if, else, for, while, do後には{}を使う([複合文](---))。
    * switchでのフォールスルーをしない([switch文](---))。
    * switchにはdefaultラベルを入れる([switch文](---))。
    * 範囲for文を積極的に使う([用語解説|構文|範囲for文](---))。
    * gotoを使用しない([goto文](---))。
* オブジェクトのダイナミックな生成には`std::make_unique<>`や`std::make_shared<>`を使用する
  ([演算子|メモリアロケーション](---))。
* Cタイプのキャストは使用しない([キャスト、暗黙の型変換](---))。


