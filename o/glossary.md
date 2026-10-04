<!-- essential/md/glossary.md -->
# 用語集 <a id="SS_21"></a>
この章では、C++慣用言句ついて解説を行う。

___

__この章の構成__

[オブジェクト指向](glossary.md#SS_21_1)  
&emsp;[is-a](glossary.md#SS_21_1_1)  
&emsp;[has-a](glossary.md#SS_21_1_2)  
&emsp;[is-implemented-in-terms-of](glossary.md#SS_21_1_3)  
&emsp;&emsp;[public継承によるis-implemented-in-terms-of](glossary.md#SS_21_1_3_1)  
&emsp;&emsp;[private継承によるis-implemented-in-terms-of](glossary.md#SS_21_1_3_2)  
&emsp;&emsp;[コンポジションによる(has-a)is-implemented-in-terms-of](glossary.md#SS_21_1_3_3)  

[Robert C. Martinのコンポーネント原則](glossary.md#SS_21_2)  
&emsp;[リリース等価の原則(REP)](glossary.md#SS_21_2_1)  
&emsp;[共通閉鎖の原則(CCP)](glossary.md#SS_21_2_2)  
&emsp;[共通再利用の原則(CRP)](glossary.md#SS_21_2_3)  
&emsp;[非循環依存の原則(ADP)](glossary.md#SS_21_2_4)  

[コード・ユニット](glossary.md#SS_21_3)  
&emsp;[ファイルペア](glossary.md#SS_21_3_1)  
&emsp;&emsp;[パッケージ内のファイルペアの配置](glossary.md#SS_21_3_1_1)  

&emsp;[パッケージ](glossary.md#SS_21_3_2)  
&emsp;[モジュール](glossary.md#SS_21_3_3)  

[Modern CMake project layout](glossary.md#SS_21_4)  
&emsp;[Modern CMake project layoutのカスタマイズ](glossary.md#SS_21_4_1)  

[ソフトウェア一般](glossary.md#SS_21_5)  
&emsp;[ヒープ](glossary.md#SS_21_5_1)  
&emsp;[プライオリティインバージョン](glossary.md#SS_21_5_2)  
&emsp;[スレッドセーフ](glossary.md#SS_21_5_3)  
&emsp;[リエントラント](glossary.md#SS_21_5_4)  
&emsp;[クリティカルセクション](glossary.md#SS_21_5_5)  
&emsp;[スピンロック](glossary.md#SS_21_5_6)  
&emsp;[ミックスイン](glossary.md#SS_21_5_7)  
&emsp;[ハンドル](glossary.md#SS_21_5_8)  
&emsp;[フリースタンディング環境](glossary.md#SS_21_5_9)  
&emsp;[メモリ保護機構](glossary.md#SS_21_5_10)  
&emsp;[CPU例外](glossary.md#SS_21_5_11)  
&emsp;[Fluent Interface](glossary.md#SS_21_5_12)  
&emsp;[Unbounded Functions](glossary.md#SS_21_5_13)  
&emsp;[サイクロマティック複雑度](glossary.md#SS_21_5_14)  
&emsp;[凝集性](glossary.md#SS_21_5_15)  
&emsp;&emsp;[凝集性の欠如](glossary.md#SS_21_5_15_1)  
&emsp;&emsp;[LCOM](glossary.md#SS_21_5_15_2)  
&emsp;&emsp;[PercentLackOfCohesion](glossary.md#SS_21_5_15_3)  

&emsp;[Spurious Wakeup](glossary.md#SS_21_5_16)  
&emsp;[副作用](glossary.md#SS_21_5_17)  
&emsp;[Itanium C++ ABI](glossary.md#SS_21_5_18)  

[C++コンパイラ](glossary.md#SS_21_6)  
&emsp;[g++](glossary.md#SS_21_6_1)  
&emsp;[clang++](glossary.md#SS_21_6_2)  

[非ソフトウェア用語](glossary.md#SS_21_7)  
&emsp;[セマンティクス](glossary.md#SS_21_7_1)  
&emsp;[割れ窓理論](glossary.md#SS_21_7_2)  
&emsp;[車輪の再発明](glossary.md#SS_21_7_3)  

[DAG(有向非循環グラフ)](glossary.md#SS_21_8)  
  
  

[インデックス](comprehensive_intro.md#SS_1_3)に戻る。  

___


## オブジェクト指向 <a id="SS_21_1"></a>
### is-a <a id="SS_21_1_1"></a>
「is-a」の関係は、オブジェクト指向プログラミング（OOP）
においてクラス間の継承関係を説明する際に使われる概念である。
クラスDerivedとBaseが「is-a」の関係である場合、
DerivedがBaseの派生クラスであり、Baseの特性をDerivedが引き継いでいることを意味する。
C++でのOOPでは、DerivedはBaseのpublic継承として定義される。
通常DerivedやBaseは以下の条件を満たす必要がある。

* Baseはvirtualメンバ関数(Base::f)を持つ。
* DerivedはBase::fのオーバーライド関数を持つ。
* DerivedはBaseに対して
  [リスコフの置換原則](https://ja.wikipedia.org/wiki/%E3%83%AA%E3%82%B9%E3%82%B3%E3%83%95%E3%81%AE%E7%BD%AE%E6%8F%9B%E5%8E%9F%E5%89%87)
  を守る必要がある。
  この原則を簡単に説明すると、
  「派生クラスのオブジェクトは、
  いつでもその基底クラスのオブジェクトと置き換えても、
  プログラムの動作に悪影響を与えずに問題が発生してはならない」という設計の制約である。

 「is-a」の関係とは「一種の～」と言い換えることができることが多い.
ペンギンや九官鳥 は一種の鳥であるため、この関係を使用したコード例を次に示す。

```cpp
    //  example/glossary/class_relation_ut.cpp 11

    class bird {
    public:
        //  事前条件: altitude  > 0 でなければならない
        //  事後条件: 呼び出しが成功した場合、is_flyingがtrueを返すことである
        virtual void fly(int altitude)
        {
            if (not(altitude > 0)) {  // 高度(altitude)は0より大きくなければ、飛べない
                throw std::invalid_argument{"altitude error"};
            }
            altitude_ = altitude;
        }

        bool is_flying() const noexcept
        {
            return altitude_ != 0;  // 高度が0でなければ、飛んでいると判断
        }

        virtual ~bird() = default;

    private:
        int altitude_ = 0;
    };

    class kyukancho : public bird {
    public:
        void speak()
        {
            // しゃべるため処理
        }

        // このクラスにget_nameを追加した理由はこの後を読めばわかる
        virtual std::string get_name() const  // その個体の名前を返す
        {
            return "no name";
        }
    };
```

bird::flyのオーバーライド関数(penguin::fly)について、[リスコフの置換原則(LSP)](class_design.md#SS_8_1_3)に反した例を下記する。

```cpp
    //  example/glossary/class_relation_ut.cpp 50

    class penguin : public bird {
    public:
        void fly(int altitude) override
        {
            if (altitude != 0) {
                throw std::invalid_argument{"altitude error"};
            }
        }
    };

    // 単体テストを行うためのラムダ
    auto let_it_fly = [](bird& b, int altitude) {
        try {
            b.fly(altitude);
        }
        catch (std::exception const&) {
            return 0;  // エクセプションが発生した
        }

        return b.is_flying() ? 2 : 1;  // is_flyingがfalseなら1を返す
    };

    bird    b;
    penguin p;
    ASSERT_EQ(let_it_fly(p, 0), 1);  // パスする
    // リスコフ置換原則が満たされていれば、派生クラス(penguin)
    // を基底クラス(bird)で置き換えても同じ結果になるはずだが、
    // 実際には逆に下記テストがパスしてしまう
    ASSERT_NE(let_it_fly(b, 0), 1);  // let_it_fly(b, 0) != 1　であることに注意
    // このことからpenguinへの派生はリスコフ置換の原則を満たさない

```

birdからpenguinへの派生がリスコフ置換の原則に反してしまった原因は以下のように考えることができる。

* bird::flyの事前条件penguin::flyが強めた
* bird::flyの事後条件をpenguin::flyが弱めた

penguinとbirdの関係はis-aの関係ではあるが、
上記コードの問題によって不適切なis-aの関係と言わざるを得ない。

上記の例では鳥全般と鳥の種類のis-a関係をpublic継承を使用して表した(一部不適切であるもの)。
さらにis-aの誤った適用例を示す。
自身が飼っている九官鳥に"キューちゃん"と名付けることはよくあることである。
キューちゃんという名前の九官鳥は一種の九官鳥であることは間違いのないことであるが、
このis-aの関係を表すためにpublic継承を使用するのは、is-aの関係の誤用になることが多い。
実際のコード例を以下に示す。この場合、型とインスタンスの概念の混乱が原因だと思われる。

```cpp
    //  example/glossary/class_relation_ut.cpp 91

    class q_chan : public kyukancho {
    public:
        std::string get_name() const override { return "キューちゃん"; }
    };
```

この誤用を改めた例を以下に示す。

```cpp
    //  example/glossary/class_relation_ut.cpp 113

    class kyukancho {
    public:
        kyukancho(std::string name) : name_{std::move(name)} {}

        std::string const& get_name() const  // 名称をメンバ変数で保持するため、virtualである必要はない
        {
            return name_;
        }

        virtual ~kyukancho() = default;

    private:
        std::string const name_;  // 名称の保持
    };

    // ...

    kyukancho q{"キューちゃん"};

    ASSERT_EQ("キューちゃん", q.get_name());
```

修正されたKyukancho はstd::string インスタンスをメンバ変数として持ち、
kyukanchoとstd::stringの関係を[has-a](glossary.md#SS_21_1_2)の関係と呼ぶ。

---

### has-a <a id="SS_21_1_2"></a>
「has-a」の関係は、
あるクラスのインスタンスが別のクラスのインスタンスを構成要素として含む関係を指す。
つまり、あるクラスのオブジェクトが別のクラスのオブジェクトを保持している関係である。

例えば、CarクラスとEngineクラスがあるとする。CarクラスはEngineクラスのインスタンスを含むので、
CarはEngineを「has-a」の関係にあると言える。
通常、has-aの関係はクラス内でメンバ変数またはメンバオブジェクトとして実装される。
Carクラスの例ではCarクラスにはEngine型のメンバ変数が存在する。

```cpp
    //  example/glossary/class_relation_ut.cpp 144

    class Engine {
    public:
        void start() {}  // エンジンを始動するための処理
        void stop() {}   // エンジンを停止するための処理

    private:
        // ...
    };

    class Car {
    public:
        Car() : engine_{} {}
        void start() { engine_.start(); }
        void stop() { engine_.stop(); }

    private:
        Engine engine_;  // Car は Engine を持っている（has-a）
    };
```

---

### is-implemented-in-terms-of <a id="SS_21_1_3"></a>
「is-implemented-in-terms-of」の関係は、
オブジェクト指向プログラミング（OOP）において、
あるクラスが別のクラスの機能を内部的に利用して実装されていることを示す概念である。
これは、あるクラスが他のクラスのインターフェースやメンバ関数を用いて、
自身の機能を提供する場合に使われる。
[has-a](glossary.md#SS_21_1_2)の関係は、is-implemented-in-terms-of の関係の一種である。

is-implemented-in-terms-ofは下記の手段1-3に示した方法がある。

* 手段1.[public継承によるis-implemented-in-terms-of](glossary.md#SS_21_1_3_1)  
* 手段2.[private継承によるis-implemented-in-terms-of](glossary.md#SS_21_1_3_2)  
* 手段3.[コンポジションによる(has-a)is-implemented-in-terms-of](glossary.md#SS_21_1_3_3)  

手段1-3にはそれぞれ、長所、短所があるため、必要に応じて手段を選択する必要がある。
以下の議論を単純にするため、下記のようにクラスS、C、CCを定める。

* S(サーバー): 実装を提供するクラス
* C(クライアント): Sの実装を利用するクラス
* CC(クライアントのクライアント): Cのメンバを使用するクラス

コード量の観点から考えた場合、手段1が最も優れていることが多い。
依存関係の複雑さから考えた場合、CはSに強く依存する。
場合によっては、この依存はCCからSへの依存間にも影響をあたえる。
従って、手段3が依存関係を単純にしやすい。
手段1は[is-a](glossary.md#SS_21_1_1)に見え、以下に示すような問題も考慮する必要があるため、
可読性、保守性を劣化させる可能性がある。

```cpp
    //  example/glossary/class_relation_ut.cpp 260

    class MyString : public std::string {  // 手段1
    };

    // ...
    std::string* m_str = new MyString{"str"};

    // このようなpublic継承を行う場合、基底クラスのデストラクタは非virtualであるため、
    // 以下のコードではｈmy_stringのデストラクタは呼び出されない。
    // この問題はリソースリークを発生させる場合がある。
    delete m_str;
```

以上述べたように問題の多い手段1であるが、実践的には有用なパターンであり、
[CRTP(curiously recurring template pattern)](https://ja.wikibooks.org/wiki/More_C%2B%2B_Idioms/%E5%A5%87%E5%A6%99%E3%81%AB%E5%86%8D%E5%B8%B0%E3%81%97%E3%81%9F%E3%83%86%E3%83%B3%E3%83%97%E3%83%AC%E3%83%BC%E3%83%88%E3%83%91%E3%82%BF%E3%83%BC%E3%83%B3(Curiously_Recurring_Template_Pattern))
の実現手段でもあるため、一概にコーディング規約などで排除することもできない。


#### public継承によるis-implemented-in-terms-of <a id="SS_21_1_3_1"></a>
public継承によるis-implemented-in-terms-ofの実装例を以下に示す。

```cpp
    //  example/glossary/class_relation_ut.cpp 282

    class MyString : public std::string {};

    // ...
    MyString str{"str"};

    ASSERT_EQ(str[0], 's');
    ASSERT_STREQ(str.c_str(), "str");

    str.clear();
    ASSERT_EQ(str.size(), 0);
```

すでに述べたようにこの方法は、
[private継承によるis-implemented-in-terms-of](glossary.md#SS_21_1_3_2)や、
[コンポジションによる(has-a)is-implemented-in-terms-of](glossary.md#SS_21_1_3_3)
と比べコードがシンプルになる。 

#### private継承によるis-implemented-in-terms-of <a id="SS_21_1_3_2"></a>
private継承によるis-implemented-in-terms-ofの実装例を以下に示す。

```cpp
    //  example/glossary/class_relation_ut.cpp 179

    class MyString : std::string {
    public:
        using std::string::string;
        using std::string::operator[];
        using std::string::c_str;
        using std::string::clear;
        using std::string::size;
    };

    // ...
    MyString str{"str"};

    ASSERT_EQ(str[0], 's');
    ASSERT_STREQ(str.c_str(), "str");

    str.clear();
    ASSERT_EQ(str.size(), 0);
```

この方法は、[public継承によるis-implemented-in-terms-of](glossary.md#SS_21_1_3_1)が持つデストラクタ問題は発生せす、
[is-a](glossary.md#SS_21_1_1)と誤解してしまう問題も発生しない。


#### コンポジションによる(has-a)is-implemented-in-terms-of <a id="SS_21_1_3_3"></a>
コンポジションによる(has-a)is-implemented-in-terms-ofの実装例を示す。

```cpp
    //  example/glossary/class_relation_ut.cpp 207

    namespace is_implemented_in_terms_of_1 {
    class MyString {
    public:
        // コンストラクタ
        MyString() = default;
        MyString(std::string const& str) : str_(str) {}
        MyString(char const* cstr) : str_(cstr) {}

        // 文字列へのアクセス
        char const* c_str() const { return str_.c_str(); }

        using reference = std::string::reference;
        using size_type = std::string::size_type;

        reference operator[](size_type pos) { return str_[pos]; }

        // その他のメソッドも必要に応じて追加する
        // 以下は例
        std::size_t size() const { return str_.size(); }

        void clear() { str_.clear(); }

        MyString& operator+=(MyString const& rhs)
        {
            str_ += rhs.str_;
            return *this;
        }

    private:
        std::string str_;
    };

    // ...
    MyString str{"str"};

    ASSERT_EQ(str[0], 's');
    ASSERT_STREQ(str.c_str(), "str");

    str.clear();
    ASSERT_EQ(str.size(), 0);
```

この方は実装を利用するクラストの依存関係を他の2つに比べるとシンプルにできるが、
逆に実装例から昭なとおり、コード量が増えてしまう。

---

## Robert C. Martinのコンポーネント原則 <a id="SS_21_2"></a>
Robert C. Martin が提唱した、クラスや関数より粒度の大きい「コンポーネント」
（このドキュメントではパッケージに相当する）の設計原則群。
本ドキュメントでは、**凝集性**＝何を一つのライブラリにまとめるかを扱う3原則（REP/CCP/CRP）と、
それと一体で判断すべき依存構造の原則 [非循環依存の原則(ADP)](glossary.md#SS_21_2_4)を用いる。

| 原則                           | 一文での定義                             | 視点   | 力の向き／作用   |
|:------------------------------ |:-----------------------------------------|:-------|:-----------------|
| [リリース等価の原則(REP)](glossary.md#SS_21_2_1) | リリースノートが一本の筋として書けるか   | 提供側 | 凝集（まとめる） |
| [共通閉鎖の原則(CCP)](glossary.md#SS_21_2_2)     | 変更される理由が一つか                   | 提供側 | 凝集（まとめる） |
| [共通再利用の原則(CRP)](glossary.md#SS_21_2_3)   | 利用者に不要な依存まで抱えさせていないか | 利用側 | 分割（割る）     |
 
### リリース等価の原則(REP) <a id="SS_21_2_1"></a>
REPとは、Reuse-Release Equivalence Principle(再利用・リリース等価の原則)の略称であり、
再利用の単位はリリースの単位に等しい、という原則である。
ライブラリとして再利用させるなら、
バージョン番号を付与し一本のリリースノートを伴って一体でリリースできる単位にまとめよ、ということ。
一つのリリースとして筋の通らない寄せ集めは再利用単位として不適切である。
REPは「まとめる方向性の根拠」になり得る。

### 共通閉鎖の原則(CCP) <a id="SS_21_2_2"></a>
CCPとは、Common Closure Principle(共通閉鎖の原則)の略称であり、
同じ理由・同じタイミングで変更されるものを一つのライブラリに集める原則である。
[単一責任の原則(SRP)](class_design.md#SS_8_1_1)をライブラリ粒度へ拡大したもので、
「このライブラリが変更される理由は一つである」と言える状態を目指す。
ある仕様変更の影響が単一ライブラリの中に閉じる（closure）ことを狙う。
CCPは、[リリース等価の原則(REP)](glossary.md#SS_21_2_1)と同様に「パッケージをまとめることの根拠」になり得る。

### 共通再利用の原則(CRP) <a id="SS_21_2_3"></a>
CRPとは、Common Reuse Principle(共通再利用の原則)の略称であり、
一緒に再利用されないものを同じライブラリに入れない原則である。利用側が一部の機能のためにリンクしたとき、
使わない機能や、それが連れてくる依存まで巻き込まれないようにする。
[インターフェース分離の原則(ISP)](class_design.md#SS_8_1_4)をライブラリ粒度へ適用したものに相当する。
[リリース等価の原則(REP)](glossary.md#SS_21_2_1)/[共通閉鎖の原則(CCP)](glossary.md#SS_21_2_2)とは逆に、「パッケージを分割することの根拠」になり得る。


### 非循環依存の原則(ADP) <a id="SS_21_2_4"></a>
ADPとは、Acyclic Dependencies Principle(非循環依存の原則)の略称であり、
ライブラリ間の依存関係に循環を作ってはならない、という原則である。
依存グラフは後述の[DAG(有向非循環グラフ)](glossary.md#SS_21_8)でなければならない。
循環があると、ライブラリを独立してビルド・テスト・リリースすることが困難になる。

---

## コード・ユニット <a id="SS_21_3"></a>

このドキュメントでは、以下のような概念をコード・ユニットと呼ぶ。
これらの概念は、コード全体の構成単位となることを前提とする。

| 名前         | 説明                                                                                           |
|:-------------|:-----------------------------------------------------------------------------------------------|
|ヘッダファイル|`*.h` `*.hpp` `*.hxx`                                                                           |
|実装ファイル  |`*.c` `*.cpp` `*.cxx`                                                                           |
|ファイルペア  |`name.h`と`name.c`の組み合わせ /「[ファイルペア](glossary.md#SS_21_3_1)」で解説                                   |
|モジュール    |モジュール ≒  パッケージ / 「[モジュール](glossary.md#SS_21_3_3)」で解説                                          |
|パッケージ    |「[パッケージ](glossary.md#SS_21_3_2)」で解説 / CMake([Modern CMake project layout](glossary.md#SS_21_4))のビルド単位(ライブラリ) |

ここでは、これらの概念に意味と定義を与える。

- ファイルペア ＝ １つの実装ファイルとヘッダファイル(稀に、実装ファイルやヘッダファイルのみ)
- パッケージ(CMakeのビルド単位) ≒  [Robert C. Martinのコンポーネント原則](glossary.md#SS_21_2)における「コンポーネント」
- パッケージ(CMakeのビルド単位) ∋  (複数の似た機能を持つ)ファイルペア


### ファイルペア <a id="SS_21_3_1"></a>
- このドキュメントでは、実装ファイルとそれに対応するヘッダファイルのペアを単にファイルペアと呼ぶ。
  - ファイルペアは、ソースコードの静的構造上の最小単位である。
  - ヘッダファイルのみでインライン関数や型の宣言・定義を完結させる場合、実装ファイルを持たないファイルペアが例外的に存在する
    （厳密には「ペア」ではないが、本ドキュメントではこれもファイルペアと呼ぶ）。
- ヘッダファイル一つに対し実装ファイルは原則一つとし、逆に一つの実装ファイルが複数のヘッダを持ってはならない。
  これによりファイルペアの境界を機械的かつ一意に判定可能にする。
- ファイルペアのファイルの配置は、「[パッケージ内のファイルペアの配置](glossary.md#SS_21_3_1_1)」で示す。 


#### パッケージ内のファイルペアの配置 <a id="SS_21_3_1_1"></a>
パッケージ内でのファイルペアのヘッダの配置は以下の２パターンのみでなければならない。

- [ファイルペアの機能をパッケージ内部でのみ使用する場合](glossary.md#SS_21_3_1_1_1)
- [ファイルペアの機能をパッケージが外部公開する場合](glossary.md#SS_21_3_1_1_2)

##### ファイルペアの機能をパッケージ内部でのみ使用する場合 <a id="SS_21_3_1_1_1"></a>

```sh
package/
└── src/             # パッケージ内部実装
    ├── fp_name.h    # fp_nameをpackage/src内に公開するためのヘッダ
    └── fp_name.cpp  # fp_nameの実装ファイル
```

##### ファイルペアの機能をパッケージが外部公開する場合 <a id="SS_21_3_1_1_2"></a>

```sh
package/
├── include/
│   └── package/       # パッケージ利用者向け公開ヘッダ
│       └── fp_name.h  # ファイルペアfp_nameのpackage外部公開ヘッダ
└── src/
    └── fp_name.cpp    # fp_nameの実装ファイル
```

### パッケージ <a id="SS_21_3_2"></a>
このドキュメントでのパッケージとは、以下の特徴を持つソースコードツリーである。 

- **類似した機能**を持つ複数の[ファイルペア](glossary.md#SS_21_3_1)の集合体
- パッケージのソースコードは、専用のディレクトリの配下に配置され、[Modern CMake project layout](glossary.md#SS_21_4)と同等の形状を持つ。
- パッケージは専用の名前空間を持つ。
- パッケージのビルド生成物はライブラリである。
- ライブラリ粒度の凝集性は、関数レベル/クラスの古典的凝集度分類ではなく、[Robert C. Martinのコンポーネント原則](glossary.md#SS_21_2)
  (「[Robert C. Martinのコンポーネント原則](glossary.md#SS_21_2)」のコンポーネントとはこのドキュメントではパッケージを指す)で判断する。
  中核は次の三原則のパワーバランスである。
    - [リリース等価の原則(REP)](glossary.md#SS_21_2_1)
    - [共通閉鎖の原則(CCP)](glossary.md#SS_21_2_2)
    - [共通再利用の原則(CRP)](glossary.md#SS_21_2_3)

さらに以下に注意する必要がある。特にREPとCRPは、両者とも凝集性の話であるため混同しやすいが、
問いの視点が異なる(CCPは「変更理由の単一性」という別の軸の指標である)。

- **REP は提供側の問い**: 「これらを一つの製品として、一つのバージョン番号・一本のリリースノートで出して筋が通るか？」。  
  関心事はバージョン管理とリリース工程。  
- **CRP は利用側の問い**: 「利用者はこれを丸ごと使うか。使わない物まで巻き込ませていないか？」。  
  パッケージ版の[インターフェース分離の原則(ISP)](class_design.md#SS_8_1_4)と考えて差し支えない。

判別のコツは**片方のルールだけをやぶる例**で考えることである。  
[例]:  
`libnet` に TCPソケット層とHTTPクライアントを同居させる。製品テーマは一貫し REP は満たすが、
TCP層だけ欲しい利用者まで HTTP側の更新で再ビルド・再検証を強いられる（CRP違反）。
修正は `libnet-tcp` と `libnet-http` への分割である。


### モジュール <a id="SS_21_3_3"></a>
明確に定義された公開インターフェースを通じて他の要素と協調する、論理的または物理的な構成単位、
と捉えるのが一般的だろう。

このような一般的な捉え方で概ね問題ないことが多いが、一般の文脈では、
粒度（ソースコードツリー、ライブラリ、クラスや関数、ヘッダファイル等）が大きく異なることがあるため、
このドキュメントでは、

> 上記定義のモジュール ≒  パッケージ

とし、[パッケージ](glossary.md#SS_21_3_2)としてその粒度を詳細に定義付けている。

__[注]__:
ここでのモジュールとC++20で導入された[モジュール](core_lang_spec.md#SS_19_10_2)は似た概念であるが、異なるものである。

--- 

## Modern CMake project layout <a id="SS_21_4"></a>
[Modern CMake project layout](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html)
はパッケージ単位でディレクトリを分割し、各パッケージが独立したビルド単位となる構造である。
このような構造はビルドツールに[CMake](https://cliutils.gitlab.io/modern-cmake/)を使用する場合は特に有効であるが、
makeプロジェクトにおいても有効である。  

[注]
この節でのパッケージとはUMLでのパッケージとは同じソフトウェアの構造の単位であるが、
CMakeでの`find_package`でのパッケージとは意味が異なる。


__[主な特徴]__  

* 公開ヘッダと実装ファイルの明確な分離
* 各パッケージに独自のCMakeLists.txtを配置
* テストコードを各パッケージに併置
* target_include_directories()のPUBLIC/PRIVATEでAPI境界を制御

この構造により、パッケージ間の依存関係が明示化され、モジュール性とテスタビリティが向上する。

__[ディレクトリ構造例]__  

```
    project/
    ├── CMakeLists.txt
    ├── app/
    │   └── main.cpp
    ├── core/
    │   ├── CMakeLists.txt
    │   ├── include/                # 公開ヘッダ
    │   │   └── core/
    │   │     ├── engine.h
    │   │     └── logger.h 
    │   ├── src/                    # 実装ファイル
    │   │   ├── engine.cpp
    │   │   └── internal.h          # 内部ヘッダ
    │   └── tests/                  # 単体テスト
    │       └── engine_test.cpp
    └── logger/
        ├── CMakeLists.txt
        ├── include/
        │   └── logger/
        │       └── logger.h
        ├── src/
        │   └── logger.cpp
        └── tests/
            └── logger_test.cpp
```

ディレクトリ構造例のcore/include/coreの構造は一見冗長に見えるが、
コンパイラに指定するインクルードパスを各パッケージのincludeディレクトリを指定することにより、
パッケージ外部の実装ファイルのインクルードセクションは以下のように記述される。

```cpp
  // インクルードセクション
  #include "core/logger.h"          // パッケージcoreからのインポート
  #include "logger/logger.h"        // パッケージloggerからのインポート
```

このような記述には以下のようなメリットがある。

- ヘッダ名の衝突を避けることができる
- main.cppのインクルードセクションの可読性が向上する

  
__[core/CMakeLists.txt例]__  

```
    # coreライブラリの定義
    add_library(core STATIC
        src/engine.cpp
    )

    # インクルードディレクトリの設定
    # PUBLIC: このライブラリを使う側にも公開されるヘッダパス
    # PRIVATE: このライブラリ内部でのみ使用するヘッダパス
    target_include_directories(core
        PUBLIC 
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

    # 単体テストの定義
    add_executable(core_test tests/engine_test.cpp)

    # テストがcoreライブラリに依存することを宣言
    target_link_libraries(core_test PRIVATE core)
```

__[トップレベルCMakeLists.txt例]__  

```
    cmake_minimum_required(VERSION 3.15)
    project(MyProject)

    # 各コンポーネントをサブディレクトリとして追加
    add_subdirectory(core)
    add_subdirectory(logger)

    # アプリケーション実行ファイルの定義
    add_executable(app app/main.cpp)

    # アプリケーションが依存するライブラリを指定
    # PRIVATE: appの実装内部でのみ使用（他のターゲットにはヘッダパスを公開しない）
    target_link_libraries(app PRIVATE core logger)
```

---

### Modern CMake project layoutのカスタマイズ <a id="SS_21_4_1"></a>
このドキュメントでは、以下の方針に基づいて[Modern CMake project layout](glossary.md#SS_21_4)の構成をカスタマイズすることを推奨する。

- パス名が過度に長くなることを避ける。
- `tests`（または `test`）という語は統合テストを指す場合もあるため、
  曖昧さを避ける目的で、単体テストには `ut`（unit test）という語を使用する。

そのため、以下のような置き換えを推奨する。

| オリジナル       | カスタマイズ |
|------------------|--------------|
| include/         | h/           |
| tests/           | ut/          |
| xxx_test.cpp     | xxx_ut.cpp   |


__[置き換え後のディレクトリ構造例]__  

```
    project/
    ├── CMakeLists.txt
    ├── app/
    │   └── main.cpp
    ├── core/
    │   ├── CMakeLists.txt
    │   ├── h/                      # 公開ヘッダ
    │   │   └── core/
    │   │     ├── engine.h
    │   │     └── logger.h 
    │   ├── src/                    # 実装ファイル
    │   │   ├── engine.cpp
    │   │   └── internal.h          # 内部ヘッダ
    │   └── ut/                     # 単体テスト
    │       └── engine_ut.cpp
    └── logger/
        ├── CMakeLists.txt
        ├── h/
        │   └── logger/
        │       └── logger.h
        ├── src/
        │   └── logger.cpp
        └── ut/
            └── logger_ut.cpp
```

---


## ソフトウェア一般 <a id="SS_21_5"></a>
### ヒープ <a id="SS_21_5_1"></a>
ヒープとは、プログラム実行時に動的メモリ割り当てを行うためのメモリ領域である。
malloc、calloc、reallocといった関数を使用して必要なサイズのメモリを確保し、freeで解放する。
スタックとは異なり、プログラマが明示的にメモリ管理を行う必要があり、解放漏れはメモリリークを引き起こす。
ヒープ領域はスタックよりも大きく、動的なサイズのデータ構造や長寿命のオブジェクトに適しているが、
アクセス速度はスタックより遅い。また、断片化（フラグメンテーション）が発生しやすく、
連続的な割り当てと解放により利用可能なメモリが分散する課題がある。適切なヒープ管理は、
C/C++プログラミングにおける重要なスキルの一つである。

### プライオリティインバージョン <a id="SS_21_5_2"></a>
プライオリティインバージョン（優先度逆転）とは、
低優先度スレッドが保持するミューテックスを高優先度スレッドが待機している間に、
無関係な中優先度スレッドが割り込んで実行される現象である。典型的なシナリオを以下に示す。

0. 低優先度スレッド L がミューテックスを獲得し、クリティカルセクションに入る。
0. 高優先度スレッド H が起床し、同じミューテックスを取ろうとするがブロックされる。
0. 中優先度スレッド M が起床し、L をプリエンプトして実行を開始する。

この結果、H は M より優先度が高いにもかかわらず、M の実行が完了するまで待たされる。
H から見れば、本来無関係な M に実行権を奪われている状態となる。


なお、プライオリティインバージョンはミューテックス固有の問題ではない。
セマフォ、メッセージキューの受信待ち、read()/write() などのブロッキング I/O といった、
スレッドのブロックを引き起こすあらゆるシステムコールで同様の構造が生じ得る。
共通の本質は「低優先度スレッドがブロックの原因を保持しており、それを解放できない状態が続く」点にある。

---

### スレッドセーフ <a id="SS_21_5_3"></a>
スレッドセーフとは「複数のスレッドから同時にアクセスされても、
排他制御などの機構([std::mutex](stdlib_and_concepts.md#SS_20_4_2))により共有データの整合性が保たれ、正しく動作する性質」である。

---

### リエントラント <a id="SS_21_5_4"></a>
リエントラントとは「実行中に同じ関数が再度呼び出されても、グローバル変数や静的変数に依存せず、
ローカル変数のみで動作するため正しく動作する性質」である。

一般に、リエントラントな関数は[スレッドセーフ](glossary.md#SS_21_5_3)であるが、逆は成り立たない。

---

### クリティカルセクション <a id="SS_21_5_5"></a>
複数のスレッドから同時にアクセスされると競合状態を引き起こす可能性があるコード領域をクリティカルセクションと呼ぶ。
典型的には、共有変数や共有データ構造を読み書きするコード部分がこれに該当する。
クリティカルセクションは、[std::mutex](stdlib_and_concepts.md#SS_20_4_2)等の排他制御機構によって保護し、
一度に一つのスレッドのみが実行できるようにする必要がある。

---

### スピンロック <a id="SS_21_5_6"></a>
スピンロックとは、
スレッドがロックを取得できるまでCPUを占有したままビジーループで待機する排他制御方式である。
スリープを伴わずカーネルを呼び出さないため、短時間の競合では高速に動作するが、
長時間の待機ではCPUを浪費しやすい。リアルタイム処理や割り込み制御に適する。

C++11では、スピンロックは[std::atomic](stdlib_and_concepts.md#SS_20_4_3)を使用して以下のように定義できる。

```cpp
    //  h/spin_lock.h 3

    #include <atomic>

    class SpinLock {
    public:
        void lock() noexcept
        {
            while (state_.exchange(state::locked, std::memory_order_acquire) == state::locked) {
                ;  // busy wait
            }
        }

        void unlock() noexcept { state_.store(state::unlocked, std::memory_order_release); }

    private:
        enum class state { locked, unlocked };
        std::atomic<state> state_{state::unlocked};
    };
```

以下の単体テスト(「[std::mutex](stdlib_and_concepts.md#SS_20_4_2)」の単体テストを参照)
に示したように[std::scoped_lock](stdlib_and_concepts.md#SS_20_5_3)のテンプレートパラメータとして使用できる。

```cpp
    //  example/glossary/spin_lock_ut.cpp 11

    struct Conflict {
        void increment()
        {
            std::lock_guard<SpinLock> lock{spin_lock_};  // スピンロックのロックガードオブジェクト生成
            ++count_;
        }

        SpinLock spin_lock_{};
        uint32_t count_ = 0;
    };
```
```cpp
    //  example/glossary/spin_lock_ut.cpp 27

    Conflict c{};

    constexpr uint32_t inc_per_thread = 5'000'000;
    constexpr uint32_t expected       = 2 * inc_per_thread;
    auto               thread_body    = [&c] {
        for (uint32_t i = 0; i < inc_per_thread; ++i) {
            c.increment();
        }
    };

    std::thread t1{thread_body};
    std::thread t2{thread_body};

    t1.join();  // スレッドの終了待ち
    t2.join();  // スレッドの終了待ち
                // 注意: join()もdetach()も呼ばずにスレッドオブジェクトが
                // デストラクトされると、std::terminateが呼ばれる

    ASSERT_EQ(c.count_, expected);
```

---

### ミックスイン <a id="SS_21_5_7"></a>
ミックスインとは、オブジェクト指向プログラミングにおいて、
複数のクラスに対して特定の機能やメソッドを提供するための設計パターンである。
「混ぜ込む（mix in）」という名称が示すとおり、既存のクラスに機能を追加する目的で使用される。

C++では[CRTP(curiously recurring template pattern)](design_pattern.md#SS_9_1_5)や通常の継承によってミックスインを実現する。

---

### ハンドル <a id="SS_21_5_8"></a>
CやC++の文脈でのハンドルとは、ポインタかリファレンスを指す。

---

### フリースタンディング環境 <a id="SS_21_5_9"></a>
[フリースタンディング環境](https://ja.wikipedia.org/wiki/%E3%83%95%E3%83%AA%E3%83%BC%E3%82%B9%E3%82%BF%E3%83%B3%E3%83%87%E3%82%A3%E3%83%B3%E3%82%B0%E7%92%B0%E5%A2%83)とは、
組み込みソフトウェアやOSのように、その実行にOSの補助を受けられないソフトウエアを指す。


### メモリ保護機構 <a id="SS_21_5_10"></a>
メモリ保護機構とは、MMU(Memory Management Unit)やMPU(Memory Protection Unit)と呼ばれることが多い。
メモリ保護機構は以下のような機能を持つ。

- メモリの用途の設定:  
    メモリ領域ごとに読み取り専用、書き込み可能、実行可能といったアクセス権を設定できる。
    これにより、コード領域への書き込みやデータ領域からの実行を防止する。  
- 不正なアライメントでのメモリアクセスの検出:  
    プロセッサのアーキテクチャが要求するアライメント境界に違反したメモリアクセスを検出し、
    例外を発生させる。これにより、バス幅に合わない不正なアクセスを早期に発見できる。  

メモリ保護機構を有効化することで、メモリ関連のバグが発生した際に、即座に例外が発生し、
問題箇所を特定しやすくなる。特に組み込みシステムでは、デバッガが常時利用できない環境において、
このような検出機能が重要となる。

### CPU例外 <a id="SS_21_5_11"></a>
CPU例外とは、プログラム実行中にCPUが検出する異常事象であり、以下のようなものを指す。

- 0除算例外:  
    整数の除算命令で除数が0の場合に発生する。ただし、ハードウェア除算を行わない処理系では、
    0除算例外はソフトウェア割り込みとして実装されることが多い。
- 不正インストラクション例外:   
    未定義の命令コードや、現在のCPUモードでは実行できない命令を実行しようとした場合に発生する。
- メモリ保護違反例外:
    [メモリ保護機構](glossary.md#SS_21_5_10)の設定に反した命令を実行した場合に発生する。例えば、リードオンリー領域への書き込み、
    実行禁止領域からの命令フェッチ、アクセス権のない領域への参照などが該当する。
- アライメント例外:
    プロセッサが要求するアライメント境界に違反したメモリアクセスを行った場合に発生する。

これらのCPU例外が発生すると、通常はプログラムの実行が中断され、例外ハンドラが呼び出される。
適切な例外ハンドラを実装することで、バグの発生箇所や原因を特定しやすくなる。
特に組み込みシステムでは、例外発生時のレジスタ状態やスタックトレースを記録する機構を用意しておくことが、
効果的なデバッグ手法となる。

### Fluent Interface <a id="SS_21_5_12"></a>
メソッドや演算子の連鎖によって一連の操作を一文で表現できるように設計する手法であり、
C++ においては古くから`std::ostream`の`operator<<`がその代表例である。
`std::cout << "value=" << x << std::endl;` はまさに Fluent Interfaceであり、
各`operator<<`が`std::ostream&`を返すことでチェーンを実現している。
C++20では`std::ranges::views`においてパイプ演算子`|` によるビュー合成が標準化され、
`vec | views::filter(...) | views::transform(...)` のような宣言的な記述が可能になった。
これはFluent Interfaceの思想をアルゴリズム合成の領域に持ち込んだものであり、
標準ライブラリにおける同パターンの本格的な拡張といえる。
可読性の向上という恩恵は大きい一方、デバッガでのステップ実行がしにくくなる点は従来から変わらぬ注意点である。

__補足：__
`operator<<`によるチェーンと`|`によるパイプ合成は、どちらも「前の式の結果を次の操作に渡す」という同じ思想を持つ。
前者は C++98 から存在する枯れた実績であり、後者はC++20 で標準化された現代的なスタイルである。

---


### Unbounded Functions <a id="SS_21_5_13"></a>
unbounded function とは操作対象のバッファサイズを引数として受け取らない関数を指す。
strcpy や gets のように書き込み先のサイズ検証を行わないため、
入力データ次第でバッファの境界を超えて書き込みが発生するリスクがある。
サイズ引数を持つstrncpyやsnprintfのようなbounded functionと対をなす概念であり、
MISRA-CやAUTOSAR等のコーディング標準ではunbounded functionの使用を禁止または制限するルールが設けられている。

---

### サイクロマティック複雑度 <a id="SS_21_5_14"></a>
[サイクロマティック複雑度](https://ja.wikipedia.org/wiki/%E5%BE%AA%E7%92%B0%E7%9A%84%E8%A4%87%E9%9B%91%E5%BA%A6)
とは関数の複雑さを表すメトリクスである。

---

### 凝集性 <a id="SS_21_5_15"></a>
[凝集性(凝集度)](https://ja.wikipedia.org/wiki/%E5%87%9D%E9%9B%86%E5%BA%A6)
とはクラス設計の妥当性を表す尺度の一種であり、「[PercentLackOfCohesion](glossary.md#SS_21_5_15_3)」というメトリクスで計測される。

* [凝集性の欠如](glossary.md#SS_21_5_15_1)メトリクスの値が100に近ければ凝集性は低く、この値が0に近ければ凝集性は高い。
* メンバ変数やメンバ関数が多くなれば、凝集性は低くなりやすい。
* 凝集性は、クラスのメンバがどれだけ一貫した責任を持つかを示す。
* 「[単一責任の原則(SRP)](class_design.md#SS_8_1_1)」を守ると凝集性は高くなりやすい。
* 「[Accessor](design_pattern.md#SS_9_1_6)」を多用すれば、振る舞いが分散しがちになるため、通常、凝集性は低くなる。
   従って、下記のようなクラスは凝集性が低い。言い換えれば、凝集性を下げることなく、
   より小さいクラスに分割できる。
   なお、以下のクラスでは、実際に計測すると、[PercentLackOfCohesion](glossary.md#SS_21_5_15_3)が100に近い値となっている。

```cpp
    //  example/glossary/lack_of_cohesion_ut.cpp 7

    class ABC {
    public:
        explicit ABC(int32_t a, int32_t b, int32_t c) noexcept : a_{a}, b_{b}, c_{c} {}

        int32_t GetA() const noexcept { return a_; }
        int32_t GetB() const noexcept { return b_; }
        int32_t GetC() const noexcept { return c_; }
        void    SetA(int32_t a) noexcept { a_ = a; }
        void    SetB(int32_t b) noexcept { b_ = b; }
        void    SetC(int32_t c) noexcept { c_ = c; }

    private:
        int32_t a_;
        int32_t b_;
        int32_t c_;
    };
```

良く設計されたクラスは、下記のようにメンバが結合しあっているため凝集性が高い
(ただし、「[Immutable](design_pattern.md#SS_9_1_7)」の観点からは、QuadraticEquation::Set()がない方が良い)。
言い換えれば、凝集性を落とさずにクラスを分割することは難しい。
なお、上記の凝集性を欠くクラスを凝集性が高くなるように修正した例を以下に示す。

```cpp
    //  example/glossary/lack_of_cohesion_ut.cpp 26

    class QuadraticEquation {  // 2次方程式
    public:
        explicit QuadraticEquation(int32_t a, int32_t b, int32_t c) noexcept : a_{a}, b_{b}, c_{c} {}

        void Set(int32_t a, int32_t b, int32_t c) noexcept
        {
            a_ = a;
            b_ = b;
            c_ = c;
        }

        int32_t Discriminant() const noexcept  // 判定式
        {
            return b_ * b_ - 4 * a_ * c_;
        }

        bool HasRealNumberSolution() const noexcept { return 0 <= Discriminant(); }

        std::pair<int32_t, int32_t> Solution() const;

    private:
        int32_t a_;
        int32_t b_;
        int32_t c_;
    };

    std::pair<int32_t, int32_t> QuadraticEquation::Solution() const
    {
        if (!HasRealNumberSolution()) {
            throw std::invalid_argument{"solution is an imaginary number"};
        }

        auto a0 = static_cast<int32_t>((-b_ - std::sqrt(Discriminant())) / 2);
        auto a1 = static_cast<int32_t>((-b_ + std::sqrt(Discriminant())) / 2);

        return {a0, a1};
    }
```

#### 凝集性の欠如 <a id="SS_21_5_15_1"></a>
[凝集性の欠如](glossary.md#SS_21_5_15_1)とはLack of Cohesion in Methodsの和訳であり、[LCOM](glossary.md#SS_21_5_15_2)と呼ばれる。

LCOMはメソッドペアの数に基づく非正規化の整数値であるため、
メソッド数が多いクラスほど値が大きくなりやすく、クラス間で単純に値の大小を比較することはできない。
この弱点を補う指標として実務上広く用いられるのが、[PercentLackOfCohesion](glossary.md#SS_21_5_15_3)である。
PercentLackOfCohesionはLCOMと同じ「メンバの共有度合い」という概念を扱うが、
クラス規模に依存しないよう0〜100%に正規化して算出される点が異なる。すなわち両者は
同一の計算式ではなく、後者はクラス規模の影響を除去した実務向けの指標と位置付けられる。

#### LCOM <a id="SS_21_5_15_2"></a>
LCOMの定義 (Chidamber & Kemerer版)を以下に述べる。  

あるクラス `C` が、メソッド集合 `{M1, M2, ..., Mn}` を持つとする（本文書中では数式番号ではなく記号のみで表現する）。

各メソッド `Mi` に対して、そのメソッドが参照（読み取りまたは書き込み）するインスタンス変数の集合を `Ii` と定義する。

```
Ii = メソッド Mi が直接アクセスするインスタンス変数の集合
```

__[P と Q の定義]__  
すべてのメソッドペア（`i ≠ j`）について、以下の2つの集合を定義する。

```
P = { (Mi, Mj) | i ≠ j, Ii ∩ Ij = ∅ }   … 共有するインスタンス変数が存在しないメソッド対の集合
Q = { (Mi, Mj) | i ≠ j, Ii ∩ Ij ≠ ∅ }   … 共有するインスタンス変数が存在するメソッド対の集合
```

ここで、メソッド数を `n` とすると、順不同のペアの総数は次の関係を満たす。

```
|P| + |Q| = n(n-1) / 2
```


__[LCOM算出式（CK原式]__  

```
LCOM = |P| - |Q|   （|P| > |Q| の場合）
LCOM = 0           （|P| ≤ |Q| の場合）
```

すなわち、「共有変数を持たないペアの数」が「共有変数を持つペアの数」を上回った超過分がLCOMの値となる。
この定義は非負値を取り、下限は0である。


#### PercentLackOfCohesion <a id="SS_21_5_15_3"></a>
厳密性を欠くが、クラスの凝集性を測定するためには、
テクマトリックス社製のUnderstandのメトリクスPercentLackOfCohesionを使用するのが実践的である。

PercentLackOfCohesionは、[LCOM](glossary.md#SS_21_5_15_2)と同様に使用できるメトリクスであり、0〜100に正規化された値である。

---

### Spurious Wakeup <a id="SS_21_5_16"></a>
[Spurious Wakeup](https://en.wikipedia.org/wiki/Spurious_wakeup)とは、
条件変数に対する通知待ちの状態であるスレッドが、その通知がされていないにもかかわらず、
起き上がってしまう現象のことを指す。

下記のようなstd::condition_variableの使用で起こり得る。

```cpp
    //  example/glossary/spurious_wakeup_ut.cpp 8

    namespace {
    std::mutex              mutex;
    std::condition_variable cond_var;
    }  // namespace

    void notify_wrong()  // 通知を行うスレッドが呼び出す関数
    {
        auto lock = std::lock_guard{mutex};

        cond_var.notify_all();  // wait()で待ち状態のスレッドを起こす。
    }

    void wait_wrong()  // 通知待ちスレッドが呼び出す関数
    {
        auto lock = std::unique_lock{mutex};

        // notifyされるのを待つ。
        cond_var.wait(lock);  // notify_allされなくても起き上がってしまうことがある。

        // do something
    }
```

std::condition_variable::wait()の第2引数を下記のようにすることでこの現象を回避できる。

```cpp
    //  example/glossary/spurious_wakeup_ut.cpp 34

    namespace {
    bool                    event_occured{false};
    std::mutex              mutex;
    std::condition_variable cond_var;
    }  // namespace

    void notify_right()  // 通知を行うスレッドが呼び出す関数
    {
        auto lock = std::lock_guard{mutex};

        event_occured = true;

        cond_var.notify_all();  // wait()で待ち状態のスレッドを起こす。
    }

    void wait_right()  // 通知待ちスレッドが呼び出す関数
    {
        auto lock = std::unique_lock{mutex};

        // notifyされるのを待つ。
        cond_var.wait(lock, []() noexcept { return event_occured; });  // Spurious Wakeup対策

        event_occured = false;

        // do something
    }
```

---

### 副作用 <a id="SS_21_5_17"></a>
プログラミングにおいて、式の評価による作用には、
主たる作用とそれ以外の
[副作用](https://ja.wikipedia.org/wiki/%E5%89%AF%E4%BD%9C%E7%94%A8_(%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0))
(side effect)とがある。
式は、評価値を得ること(関数では「引数を受け取り値を返す」と表現する)が主たる作用とされ、
それ以外のコンピュータの論理的状態(ローカル環境以外の状態変数の値)を変化させる作用を副作用という。
副作用の例としては、グローバル変数や静的ローカル変数の変更、
ファイルの読み書き等のI/O実行、等がある。


---

### Itanium C++ ABI <a id="SS_21_5_18"></a>
ItaniumC++ABIとは、C++コンパイラ間でバイナリ互換性を確保するための規約である。
関数呼び出し規約、クラスレイアウト、仮想関数テーブル、例外処理、
名前修飾(マングリング)などC++のオブジェクト表現と呼び出し方法に関する標準ルールを定めている。

もともとはIntelItanium(IA-64)プロセッサ向けに策定されたが、
[g++](glossary.md#SS_21_6_1)や[clang++](glossary.md#SS_21_6_2)はx86/x86-64やARM64など多くのプラットフォームでもItaniumC++ABI準拠の規約を採用している。
そのため異なるコンパイラ間でもオブジェクトファイルやライブラリのリンクが可能である。
また、typeid(...).name()をデマングルした場合、
constがeast-const形式(T const)で表示されるのもこのABIの規約によるものである。

| ABI               | 主な対象プラットフォーム  | マングリング規則    | クラスレイアウト  | 例外処理    |
| ----------------- | ------------------------- | ------------------- | ----------------- | ----------- |
| **ItaniumC++ABI** | IA-64, x86, x86-64, ARM64 | east-const形式      | Itanium規則       | Itanium規則 |
| **MSVC C++ABI**   | Windows x86/x64           | 独自形式            | 独自規則          | 独自規則    |
| **ARM C++ABI**    | AArch32, AArch64          | 基本的にItanium準拠だが例外あり         | ARM規則     |

---

## C++コンパイラ <a id="SS_21_6"></a>
本ドキュメントで使用するg++/clang++のバージョンは以下のとおりである。

### g++ <a id="SS_21_6_1"></a>

```
    g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
    Copyright (C) 2021 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### clang++ <a id="SS_21_6_2"></a>

```
    Ubuntu clang version 14.0.0-1ubuntu1
    Target: x86_64-pc-linux-gnu
    Thread model: posix
    InstalledDir: /usr/bin
```

## 非ソフトウェア用語 <a id="SS_21_7"></a>
### セマンティクス <a id="SS_21_7_1"></a>
シンタックスとは構文論のことであり、セマンティクスとは意味論のことである。
セマンティクス、シンタックスの違いをはっきりと際立たせる以下の有名な例文により、
セマンティクスの意味を直感的に理解することができる。

```
    Colorless green ideas sleep furiously(直訳:無色の緑の考えが猛烈に眠る)
```

この文は文法的には正しい(シンタックス的に成立している)が、意味的には不自然で理解不能である
(セマンティクス的には破綻している)。ノーム・チョムスキーによって提示されたこの例文は、
構文が正しくても意味が成立しないことがあるという事実を示しており、構文と意味の違いを鮮やかに浮かび上がらせる。


---

### 割れ窓理論 <a id="SS_21_7_2"></a>
[割れ窓理論](https://ja.wikipedia.org/wiki/%E5%89%B2%E3%82%8C%E7%AA%93%E7%90%86%E8%AB%96)とは、
軽微な犯罪も徹底的に取り締まることで、凶悪犯罪を含めた犯罪を抑止できるとする環境犯罪学上の理論。
アメリカの犯罪学者ジョージ・ケリングが考案した。
「建物の窓が壊れているのを放置すると、誰も注意を払っていないという象徴になり、
やがて他の窓もまもなく全て壊される」との考え方からこの名がある。

ソフトウェア開発での割れ窓とは、「朝会に数分遅刻する」、「プログラミング規約を守らない」
等の軽微なルール違反を指し、この理論の実践には、このような問題を放置しないことによって、

* チームのモラルハザードを防ぐ
* コードの品質を高く保つ

等の重要な狙いがある。


---

### 車輪の再発明 <a id="SS_21_7_3"></a>
[車輪の再発明](https://ja.wikipedia.org/wiki/%E8%BB%8A%E8%BC%AA%E3%81%AE%E5%86%8D%E7%99%BA%E6%98%8E)
とは、広く受け入れられ確立されている技術や解決法を（知らずに、または意図的に無視して）
再び一から作ること」を指すための慣用句である。
ソフトウェア開発では、STLのような優れたライブラリを使わずに、
それと同様なライブラリを自分たちで実装するような非効率な様を指すことが多い。

## DAG(有向非循環グラフ) <a id="SS_21_8"></a>
DAGとは、Directed Acyclic Graph([有向非循環グラフ](https://ja.wikipedia.org/wiki/%E6%9C%89%E5%90%91%E9%9D%9E%E5%B7%A1%E5%9B%9E%E3%82%B0%E3%83%A9%E3%83%95))の略称である。

---


