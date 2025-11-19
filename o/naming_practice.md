<!-- practical/md/naming_practice.md -->
# 命名規則 <a id="SS_6"></a>
平凡なプログラマでもソースコードを介してコンパイラにその意図を伝えることはできる。
優れたプログラマはそれに加えて、
ソースコードを「他のプログラマに自分の意図を伝えるためのコミュニケーション手段」と位置づけ、
「ソフトウェア構成物(識別子、ファイル等)への適切な命名」
を重要なプログラミング技法の一つであると考える。

適切な命名とは、少なくとも下記のようなものである。

* ソフトウェア構成物の意味や責務、性質を容易に想起できる。
    * 一般に使用されている、もしくはプロジェクトで定義(「[略語リスト](naming_practice.md#SS_6_1_1)」参照)
      されている略語以外の略語は使用しない(特に母音の省略は悪習慣である)。
    * 対称的な概念には、対称的な名前を付ける(「[言葉の対称性](naming_practice.md#SS_6_1_2)」参照)。
    * 変数名、クラス名等は「人(er)」や「もの」にする(と適切な場合が多い)。
      また、単数、複数形に気をつける。
    * メンバ関数名は動詞から始める(と適切な場合が多い)。
* 非常識、時代遅れのルールに従っていない(ハンガリアン記法による命名は時代遅れ)。
* 違う概念の構成物に同じような(紛らわしい)名前を付けない。

このような技法は、簡単に習得できることではないが、
すべてのプログラマは、このことに細心の注意を払い、
可読性の高いソースコードを作り出すための努力を怠ってはならない。

なお、これ以降この章では、主に名前の形式についてのルールを定める。

___

__この章の構成__

&emsp;&emsp; [禁止事項](naming_practice.md#SS_6_1)  
&emsp;&emsp;&emsp; [略語リスト](naming_practice.md#SS_6_1_1)  
&emsp;&emsp;&emsp; [言葉の対称性](naming_practice.md#SS_6_1_2)  

&emsp;&emsp; [識別子の命名](naming_practice.md#SS_6_2)  
&emsp;&emsp;&emsp; [ファイル、ディレクトリの命名](naming_practice.md#SS_6_2_1)  
&emsp;&emsp;&emsp; [ファイル名](naming_practice.md#SS_6_2_2)  
&emsp;&emsp;&emsp; [ディレクトリ名](naming_practice.md#SS_6_2_3)  
&emsp;&emsp;&emsp; [型名](naming_practice.md#SS_6_2_4)  
&emsp;&emsp;&emsp; [定数名](naming_practice.md#SS_6_2_5)  
&emsp;&emsp;&emsp; [ローカル変数名(自動変数名、仮引数名、関数内static変数名)](naming_practice.md#SS_6_2_6)  
&emsp;&emsp;&emsp; [メンバ変数名](naming_practice.md#SS_6_2_7)  
&emsp;&emsp;&emsp; [メンバ関数名](naming_practice.md#SS_6_2_8)  
&emsp;&emsp;&emsp; [Accessorメンバ関数名](naming_practice.md#SS_6_2_9)  
&emsp;&emsp;&emsp; [関数名](naming_practice.md#SS_6_2_10)  
&emsp;&emsp;&emsp; [名前空間名](naming_practice.md#SS_6_2_11)  
&emsp;&emsp;&emsp; [テンプレート名](naming_practice.md#SS_6_2_12)  
&emsp;&emsp;&emsp; [テンプレートの仮引数名](naming_practice.md#SS_6_2_13)  
&emsp;&emsp;&emsp; [マクロ名](naming_practice.md#SS_6_2_14)  
&emsp;&emsp;&emsp; [その他の命名則](naming_practice.md#SS_6_2_15)  
  
  

[インデックス](introduction.md#SS_1_4)に戻る。  

___

## 禁止事項 <a id="SS_6_1"></a>
* [定義] 以下のような識別子は、C++の予約語であるため使用しない。
    * グローバルスコープを持ち、'\_'で始まる識別子
    * '\_'で始まり、その次が大文字の識別子
    * '\_\_'を**含む**識別子(Cでは、'\_\_'で**始まる**識別子)

* C++の予約語と紛らわしいため、'\_'で始まる名前は使用しない。  

```cpp
    //  example/etc/naming.cpp 12

    int32_t     _max;           // NG
    int32_t     max;            // OK
    void        _func();        // NG
    void        func();         // OK

    #define     _FOO_BAR_H_     // NG
    #define     FOO_BAR_H_      // OK
```

* システムハンガリアン的な命名は、不要な変更を発生させるため使用しない。  

```cpp
    //  example/etc/naming.cpp 25

    int32_t s32_read_counter;  // NG
    int32_t read_counter;      // OK
```

* エイリアス(typedef)を除き、同じ物に複数の名前をつけない。
  特に、同じ構造の型を複数定義することは不要な混乱を招くだけでなく、
  コードクローンの原因になる
  (こういったソースコードを意図的に書くプログラマは、「型とインスタンスを明確に区別する」、
  「委譲や継承を使う」といった基本的スキルへの理解が足りていない可能性が高い)。
* 名前に列挙のための数字をつけない。  

```cpp
    //  example/etc/naming.cpp 32

    int32_t name1;         // NG
    int32_t name2;         // NG
    int32_t utf16code;     // OK
    int32_t storage1K;     // OK
    bool    image1_onoff;  // image1が正式な名前ならOK
```

* 母音等を省略しない。

```cpp
    //  example/etc/naming.cpp 42

    int32_t acnt;            // NG
    int32_t account;         // OK
    int32_t sig_handler;     // NG
    int32_t signal_handler;  // OK

    // その他やってしまいがちな例
    // ctrl     ->  control
    // no       -> number
    // ttl      -> total
    // cb       -> callback
    // fn       -> function, func
```

* 英文字の大小で識別子を区別しない。
  ただし、「[NVI(non virtual interface)](cpp_idioms.md#SS_21_1_7)」を使用するメンバ関数名は例外とする。

```cpp
    //  example/etc/naming.cpp 59

    // NGの例 一見同じに見える
    class XxxCallBack {
        // ...
    };

    class XxxCallback {
        // ...
    };
```

* 一般的でない略語を使わない。
  一般的でない略語をプロジェクト横断的に定義したい場合には、略語リストを作り、それに定義する
  (「[略語リスト](naming_practice.md#SS_6_1_1)」参照)。
* 対照的概念に非対称な名前(startとend、topとdown等)を付けない
  (「[言葉の対称性](naming_practice.md#SS_6_1_2)」参照)。

### 略語リスト <a id="SS_6_1_1"></a>
プロジェクト独自の略語については下記のようなテーブルを作り、
ソースコードと同じリポジトリで管理する。

| 略語                      | 正式名称                                                          |
|:--------------------------|:------------------------------------------------------------------|
| cmd                       | command                                                           |
| fd                        | file descriptor                                                   |
| lhs                       | left-hand side                                                    |
| num                       | number                                                            |
| prev                      | previous                                                          |
| proc                      | process                                                           |
| ptr                       | pointer                                                           |
| rhs                       | right-hand side                                                   |
| str                       | std::stringのオブジェクト名                                       |
| thd                       | std::threadのオブジェクト名                                       |
| uniq                      | unique                                                            |

### 言葉の対称性 <a id="SS_6_1_2"></a>
「始まり」に対しては「終わり」であり、「開始」に対しては「終了」である。
これと同様に対称的な意味をもつ識別子に対して、 
正確な対義語を使うことは重要であり、良い命名をするための一つの方法である。

プログラミングにおいてよく使われる対義語リストを下記する。

| 対応語                            |意味                   |
|:----------------------------------|:----------------------|
| add/subtract                      |加減算                 |
| add/delete                        |追加／削除             |
| attach/detach                     |オブサーバ登録／解除   |
| begin/end                         |位置                   |
| first/last                        |順番                   |
| front/back                        |位置                   |
| get/set                           |Accessor               |
| lock/unlock                       |                       |
| new/old                           |                       |
| open/close                        |                       |
| previous(prev)/next               |                       |
| push/pop                          |スタック処理           |
| send/receive(recv)                |                       |
| set up/tear down                  |　　　                 |
| source/destination(src/dst)       |「先」と「元」         |
| start/stop                        |開始／停止             |
| under/over                        |                       |
| up/down                           |                       |
| upper/lower                       |                       |
| lhs/rhs                           |左右                   |

## 識別子の命名 <a id="SS_6_2"></a>
コードの可読性に大きな影響を与える識別子名はパッケージ外部(「パッケージの実装と公開」参照)
に公開されるクラス名、関数名、名前空間名である。

クラス名、関数名、名前空間名に良い名前を与えるためにこの章が存在するのだが、
執筆中にchatgptが公開されため、
識別子名の体裁(キャメルスタイル等)を決めること以外に説明することがほとんどなくなった。

筆者がよく使う「識別子の命名をするためのchatgptでのプロンプト」を紹介する。

* クラスの説明
    * 責務を２，３個挙げる
    * 主なメンバ関数のやることを２，３個挙げる。名前以外のシグネチャを決める
* 非メンバ関数
    * その非メンバ関数のやることを２，３個挙げる
    * その非メンバ関数の名前以外のシグネチャを決める

[依頼1]上記の説明にふさわしいクラス名、関数名をそれぞれ２，３個づつ挙げよ。

納得できる名前を挙げるまで繰り返すことになるが、通常２，３回の施行で良い名前が決められる。
トライ&エラーに備えて、できればcopiloteでなくchatgptを使うべきだろう。

[依頼2]「上記で定めたクラス名、関数名」を宣言するための名前空間名を考えよ。

以下は命名についての議論ではないが、AIの使い方に触れたので、コード生成についても少し言及する。

クラス名、関数名まで決められれば、セッションをそのまま使用しコードの生成をさせることができる。
この際、[クラスのコメント](comment.md#SS_7_2_1)、[関数のコメント](comment.md#SS_7_2_2)のフォーマットをchapgptに伝えれば、
より良いコードが作られる。問題点を修正し、それをchatgptにに張り付け、
単体テストをgtestで書くように依頼すれば、単体テスト付きのコードが入手できる。


### ファイル、ディレクトリの命名 <a id="SS_6_2_1"></a>
ファイル名、ディレクトリ名は、ソフトウェアを構成するパッケージや、
それらの構造から強い影響を受けるため、「[パッケージとその構成ファイル](programming_convention.md#SS_3_7)」
で定めたルールが守られていなければ、ファイル、ディレクトリへの適切な命名は困難である。
従って、ここで定める命名ルールに従っていないソースコードをベースとした開発、
保守を行っているプログラマが、そのソースコードをここでの名称ルールに従わせる場合、
まずは「[パッケージとその構成ファイル](programming_convention.md#SS_3_7)」の順守から始めなければならない。

[注意] ほとんどのバージョン管理システムはファイル名、ディレクトリ名の大文字小文字を区別するが、
OSによっては、その区別がないものがあるため、この違いがトラブルを発生させることがある。
それを避けるために、ファイル名、ディレクトリ名には大文字を使わない方が良い。

### ファイル名 <a id="SS_6_2_2"></a>
* ファイル名は、以下のような形式の文字列にするか、それらを'\_'によって連結した文字列にする。
    * 正規表現[a-z][a-z0-9]+で表される文字列

* ファイル名は、下記のようにクラス名から生成する「[ファイルの使用方法](programming_convention.md#SS_3_2_1)」参照)。
* 単体テストのソースコードのファイル名はテスト対象のファイル名(.cpp)
  のベース名末尾に"\_ut"を挿入することで生成する。

```cpp
    // クラス名
    class XxxController;

    // ファイル名
    xxx_controller.cpp       // OK XxxControllerの定義
    xxx_controller.h         // OK XxxControllerの宣言、定義
    XxxController.cpp        // NG
    XxxController.h          // NG

    xxx_controller_ut.cpp    // OK xxx_controller.cppの単体テストのソースコードのファイル名
```

### ディレクトリ名 <a id="SS_6_2_3"></a>
* クラス名からファイル名を生成する方法と同様に、
  パッケージ名(== 名前空間名)からディレクトリ名を生成する
  (パッケージ名がXxxYyyであれば、そのディレクトリ名はxxx_yyyである)。

### 型名 <a id="SS_6_2_4"></a>
* 型(class、struct、enum、それらのエイリアス)の名前は、以下のような形式の文字列にするか、
  それらを連結した文字列にする。
  ただし、文字列の連結部が大文字の連続になる場合はそれらを'\_'によって区切る。
    * 正規表現[A-Z][a-z0-9]+で表される文字列
    * 正規表現[A-Z][A-Z0-9]+で表される文字列(慣習的に小文字を使わない文字列のみ。TCP等)

```cpp
    //  example/etc/naming.cpp 73

    class XxxController;                     // OK
    class xxx_control;                       // NG
    struct SomeStruct;                       // OK
    enum class SomeEnumeration;              // OK
    enum class some_enumeration;             // OK
    using Container = std::vector<int32_t>;  // OK
    class TCP_IP;                            // OK
```

* 責務がわかる名前をつける。
  クラスには「xxxする人」、「yyyするもの」のような命名が適している場合が多い。

### 定数名 <a id="SS_6_2_5"></a>
* クラスや構造体のpublicな定数や、外部リンケージを持つ定数、定数テンプレートの名前は、
  型名と同じルールで生成する。

```cpp
    //  example/etc/naming.cpp 86

    constexpr int SOME_CONSTANT{0};  // NG  定数
    constexpr int SomeConstant{0};   // OK  定数

    struct Xxx {
        static constexpr int SOME_CONSTANT{0};  // NG  定数
        static constexpr int SomeConstant{0};   // OK  定数
    };

    template <typename T>
    constexpr bool IsSameAsXxxV = std::is_same_v<Xxx, T>;  // OK 定数テンプレート
```

### ローカル変数名(自動変数名、仮引数名、関数内static変数名) <a id="SS_6_2_6"></a>
* ローカル変数名は、以下のような形式の文字列にするか、
  それらを'\_'によって連結した文字列にする。
    * 正規表現[a-z][a-z0-9]+で表される文字列
    * 正規表現[a-z]で表される1文字
      (デカルト座標でのxやy、ループ変数iやj、std::string::c_str()のc等のみ)
    * 正規表現[A-Z][A-Z0-9]+で表される文字列(慣習的に小文字を使わない文字列のみ。TCP等)

* 数字と見分けが難しい文字は単独では使用しない(o、l、\_o、\_l等は0や1と区別が困難)。

### メンバ変数名 <a id="SS_6_2_7"></a>
* クラスのメンバ変数(static const、static constexprメンバ定数を含む)の名前は、
  ローカル変数名と同じルールで生成した文字列の末尾に'\_'を加えることにより生成する
  (visual studioで開発を行うプロジェクトを除きメンバ変数をm'\_'で始めことはしない)。
* 構造体のメンバ変数の名前は、ローカル変数名と同じルールで生成する(末尾に'\_'はつけない)。

```cpp
    //  example/etc/naming.cpp 102

    class Foo {
    private:
        int32_t read_counter;   // NG
        int32_t read_counter_;  // OK
        int32_t m_ReadCounter;  // NG
    };

    struct Hoo {
        int32_t bar;   // OK
        int32_t bar_;  // NG
    };
```

* enumのメンバ名は、型名と同じルールで生成する。

```cpp
    //  example/etc/naming.cpp 117

    enum class SignalType {
        RED,    // NG
        Green,  // OK
        yellow  // NG
    };
```

### メンバ関数名 <a id="SS_6_2_8"></a>
* メンバ関数はオブジェクトの振る舞いを定義するためのものであるため、
  名前は動詞から始める(と良い場合が多いが、std::string::c_str()のように例外も多い)。
* 非同期なサービスを駆動するためのメンバ関数の名前には末尾にasyncをつける。
* publicメンバ関数の名前は、型名と同じルールで生成する。
* private、protectedメンバ関数の名前は、ローカル変数名と同じルールで生成する。

```cpp
    //  example/etc/naming.cpp 125

    class Fee {
    public:
        void PrintMessage();   // OK
        void Print_Message();  // NG _は不要
        bool WatchdogExit();   // NG ExitByWatchdog等の方が良い
        bool DoSomething();    // OK
        bool doSomething();    // NG

    private:
        bool print_system_message_async();  // OK privateで非同期
        void do_something();                // OK
    };
```

### Accessorメンバ関数名 <a id="SS_6_2_9"></a>
* 慣習に従うと機能が類推しやすいため、 
  一般的な[Accessor](cpp_idioms.md#SS_21_1_5)メンバ関数には、以下のような接頭語をつける。

| 接頭語| 意味                  | 例                                        | 
|:------|:----------------------|:------------------------------------------| 
| is    | xxxか？               | signal.IsRed()                            | 
| get   | xxxを返せ             | signal.GetSignal()                        | 
| set   | xxxを設定せよ         | signal.SetSignal(signal\_color)           | 
| can   | xxxはできるか？       | signal.CanTurnOn()                        | 
| has   | xxxを持っているか？   | signal.HasLed()                           | 

* IsXXX(), CanXXX(), HasXXX()等は、戻り型boolのconstメンバ関数と宣言、定義する。
* 戻り値の意味を明示できないため、bool CheckXxx()のような名前は使用しない。
* 変更対象であるメンバ変数を明示するためにsetterメンバ関数の仮引数は、
  変更対象の変数名の末尾から'\_'を除いた名前にする。

```cpp
    //  example/etc/naming.cpp 140

    class Fii {
    public:
        int32_t GetFoo() const noexcept;      // OK 変数の値の取得
        void    SetFoo(int32_t foo) noexcept  // OK 変数に値を設定
        {
            foo_ = foo;  // OK setterの仮引数はメンバ名から'\_'を除いたもの
        }

        bool IsCurrency() const noexcept;        // OK bool値の問い合わせ
        bool IsGettableMemory() const noexcept;  // OK
        bool HasHoge() const noexcept;           // OK
        bool CanGet() const noexcept;            // OK
        bool CheckHoge() const noexcept;         // NG true/falseの意味が明確でない

    private:
        int32_t foo_;
    };
```

### 関数名 <a id="SS_6_2_10"></a>
* 非メンバ関数の名前は、型名と同じルールで生成する。

### 名前空間名 <a id="SS_6_2_11"></a>
* 名前空間名は、型名と同じルールで生成する。
* ディレクトリが階層を持つならば、名前空間もそれと同相にする。
  パッケージXxx(パッケージを構成するディレクトリ名はxxx)が、
  サブパッケージYyy(ディレクトリ名はyyy、相対パスはxxx/yyy)を内包するのであれば、
  それらパッケージの名前空間名は、それぞれXxx、Xxx::Yyyである。

### テンプレート名 <a id="SS_6_2_12"></a>
* ファイル外部から参照されるテンプレートの名前は、型名と同じルールで生成する。
* ファイル外部から参照されないテンプレート(「[名前空間](programming_convention.md#SS_3_8_2)」参照)の名前は、
  ローカル変数名と同じルールで生成する。

### テンプレートの仮引数名 <a id="SS_6_2_13"></a>
* templateの仮引数名は、以下のような形式の文字列にするか、定数名と同じルールで生成する。
    * 正規表現[A-Z][0-9]?で表される文字列(慣習的にはTやその周辺の大文字SやU等)

### マクロ名 <a id="SS_6_2_14"></a>
* 二重読み込みの防御用以外のマクロの名前は、定数名と同じルールで生成する。
* 二重読み込みの防御用のマクロの名前は、「[二重読み込みの防御](programming_convention.md#SS_3_7_4)」で定めたルールで生成する。

### その他の命名則 <a id="SS_6_2_15"></a>
* コレクションクラスやコンテナクラス、それらのインスタンスに対しては、
  その名前に以下のような工夫をすることにより、物の集まりであることを示す。
    * 複数形にする。
    * 集合、群等を名前に取り入れる。

```cpp
    //  example/etc/naming.cpp 160

    class StringCollector {  // OK 文字列の集合を扱うことを示す
    public:
        std::vector<std::string> const& GetStrings() const;  // OK 戻り値が集合であることを示す
        std::vector<std::string> const& GetString() const;   // NG 複数形にしてvectorであることを
                                                             //    示すべき
    private:
        std::vector<std::string> strings_;  // OK インスタンスが集合であることを示す
        std::vector<std::string> string_;   // NG
    };
```

* 名前を構成する単語は、概念が大きい順番に左から並べる。

```cpp
    //  example/etc/naming.cpp 175

    // 下記例のXXX_YYY_R0は、XXX回路のYYYサブ回路のR0レジスタを表す。
    volatile auto& XXX_YYY_R0 = *reinterpret_cast<uint32_t*>(0x1300'0000);
    volatile auto& XXX_YYY_R1 = *reinterpret_cast<uint32_t*>(0x1300'0100);
    volatile auto& XXX_YYY_Q0 = *reinterpret_cast<uint32_t*>(0x1300'0200);
    volatile auto& XXX_ZZZ_R0 = *reinterpret_cast<uint32_t*>(0x1400'0200);
```

```cpp
    //  example/etc/naming.cpp 183

    // OK DataFormatterという概念のインターフェース クラス
    class DataFormatterIF {
        // ...
    };

    // OK DataFormatterという概念の具象クラスDataFormatterXml。XmlDataFormatterとしない。
    class DataFormatterXml final : public DataFormatterIF {
        // ...
    };

    // OK DataFormatterという概念の具象クラスDataFormatterCsv。CsvDataFormatterとしない。
    class DataFormatterCsv final : public DataFormatterIF {
        // ...
    };
```


