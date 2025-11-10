<!-- essential/md/cpp_idioms.md -->
# C++慣用語句 <a id="SS_21"></a>
この章では、C++慣用言句ついて解説を行う。

___

__この章の構成__

&emsp;&emsp; [オブジェクト指向](cpp_idioms.md#SS_21_1)  
&emsp;&emsp;&emsp; [is-a](cpp_idioms.md#SS_21_1_1)  
&emsp;&emsp;&emsp; [has-a](cpp_idioms.md#SS_21_1_2)  
&emsp;&emsp;&emsp; [is-implemented-in-terms-of](cpp_idioms.md#SS_21_1_3)  
&emsp;&emsp;&emsp;&emsp; [public継承によるis-implemented-in-terms-of](cpp_idioms.md#SS_21_1_3_1)  
&emsp;&emsp;&emsp;&emsp; [private継承によるis-implemented-in-terms-of](cpp_idioms.md#SS_21_1_3_2)  
&emsp;&emsp;&emsp;&emsp; [コンポジションによる(has-a)is-implemented-in-terms-of](cpp_idioms.md#SS_21_1_3_3)  

&emsp;&emsp; [オブジェクトの所有権](cpp_idioms.md#SS_21_2)  
&emsp;&emsp;&emsp; [オブジェクトの排他所有](cpp_idioms.md#SS_21_2_1)  
&emsp;&emsp;&emsp; [オブジェクトの共有所有](cpp_idioms.md#SS_21_2_2)  
&emsp;&emsp;&emsp; [オブジェクトの循環所有](cpp_idioms.md#SS_21_2_3)  

&emsp;&emsp; [copy/moveと等価性のセマンティクス](cpp_idioms.md#SS_21_3)  
&emsp;&emsp;&emsp; [等価性のセマンティクス](cpp_idioms.md#SS_21_3_1)  
&emsp;&emsp;&emsp; [copyセマンティクス](cpp_idioms.md#SS_21_3_2)  
&emsp;&emsp;&emsp; [moveセマンティクス](cpp_idioms.md#SS_21_3_3)  
&emsp;&emsp;&emsp; [MoveAssignable要件](cpp_idioms.md#SS_21_3_4)  
&emsp;&emsp;&emsp; [CopyAssignable要件](cpp_idioms.md#SS_21_3_5)  

&emsp;&emsp; [関数設計のガイドライン](cpp_idioms.md#SS_21_4)  
&emsp;&emsp;&emsp; [関数の引数と戻り値の型](cpp_idioms.md#SS_21_4_1)  
&emsp;&emsp;&emsp; [サイクロマティック複雑度のクライテリア](cpp_idioms.md#SS_21_4_2)  
&emsp;&emsp;&emsp; [関数の行数のクライテリア](cpp_idioms.md#SS_21_4_3)  

&emsp;&emsp; [クラス設計のガイドライン](cpp_idioms.md#SS_21_5)  
&emsp;&emsp;&emsp; [ゼロの原則(Rule of Zero)](cpp_idioms.md#SS_21_5_1)  
&emsp;&emsp;&emsp; [五の原則(Rule of Five)](cpp_idioms.md#SS_21_5_2)  
&emsp;&emsp;&emsp; [クラス凝集性のクライテリア](cpp_idioms.md#SS_21_5_3)  

&emsp;&emsp; [コーディングスタイル](cpp_idioms.md#SS_21_6)  
&emsp;&emsp;&emsp; [AAAスタイル](cpp_idioms.md#SS_21_6_1)  
&emsp;&emsp;&emsp; [east-const](cpp_idioms.md#SS_21_6_2)  
&emsp;&emsp;&emsp; [west-const](cpp_idioms.md#SS_21_6_3)  

&emsp;&emsp; [オブジェクトのコピー](cpp_idioms.md#SS_21_7)  
&emsp;&emsp;&emsp; [シャローコピー](cpp_idioms.md#SS_21_7_1)  
&emsp;&emsp;&emsp; [ディープコピー](cpp_idioms.md#SS_21_7_2)  
&emsp;&emsp;&emsp; [スライシング](cpp_idioms.md#SS_21_7_3)  

&emsp;&emsp; [C++注意点](cpp_idioms.md#SS_21_8)  
&emsp;&emsp;&emsp; [オーバーライドとオーバーロードの違い](cpp_idioms.md#SS_21_8_1)  
&emsp;&emsp;&emsp; [danglingリファレンス](cpp_idioms.md#SS_21_8_2)  
&emsp;&emsp;&emsp; [danglingポインタ](cpp_idioms.md#SS_21_8_3)  
&emsp;&emsp;&emsp; [Most Vexing Parse](cpp_idioms.md#SS_21_8_4)  

&emsp;&emsp; [ソフトウェア一般](cpp_idioms.md#SS_21_9)  
&emsp;&emsp;&emsp; [ヒープ](cpp_idioms.md#SS_21_9_1)  
&emsp;&emsp;&emsp; [スレッドセーフ](cpp_idioms.md#SS_21_9_2)  
&emsp;&emsp;&emsp; [リエントラント](cpp_idioms.md#SS_21_9_3)  
&emsp;&emsp;&emsp; [クリティカルセクション](cpp_idioms.md#SS_21_9_4)  
&emsp;&emsp;&emsp; [スピンロック](cpp_idioms.md#SS_21_9_5)  
&emsp;&emsp;&emsp; [ハンドル](cpp_idioms.md#SS_21_9_6)  
&emsp;&emsp;&emsp; [フリースタンディング環境](cpp_idioms.md#SS_21_9_7)  
&emsp;&emsp;&emsp; [サイクロマティック複雑度](cpp_idioms.md#SS_21_9_8)  
&emsp;&emsp;&emsp; [凝集性](cpp_idioms.md#SS_21_9_9)  
&emsp;&emsp;&emsp;&emsp; [凝集性の欠如](cpp_idioms.md#SS_21_9_9_1)  
&emsp;&emsp;&emsp;&emsp; [LCOM](cpp_idioms.md#SS_21_9_9_2)  

&emsp;&emsp;&emsp; [Spurious Wakeup](cpp_idioms.md#SS_21_9_10)  
&emsp;&emsp;&emsp; [Static Initialization Order Fiasco(静的初期化順序問題)](cpp_idioms.md#SS_21_9_11)  
&emsp;&emsp;&emsp; [副作用](cpp_idioms.md#SS_21_9_12)  
&emsp;&emsp;&emsp; [Itanium C++ ABI](cpp_idioms.md#SS_21_9_13)  

&emsp;&emsp; [C++コンパイラ](cpp_idioms.md#SS_21_10)  
&emsp;&emsp;&emsp; [g++](cpp_idioms.md#SS_21_10_1)  
&emsp;&emsp;&emsp; [clang++](cpp_idioms.md#SS_21_10_2)  

&emsp;&emsp; [非ソフトウェア用語](cpp_idioms.md#SS_21_11)  
&emsp;&emsp;&emsp; [セマンティクス](cpp_idioms.md#SS_21_11_1)  
&emsp;&emsp;&emsp; [割れ窓理論](cpp_idioms.md#SS_21_11_2)  
&emsp;&emsp;&emsp; [車輪の再発明](cpp_idioms.md#SS_21_11_3)  
  
  

[インデックス](introduction.md#SS_1_4)に戻る。  

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
    //  example/cpp_idioms/class_relation_ut.cpp 11

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

bird::flyのオーバーライド関数(penguin::fly)について、[リスコフの置換原則(LSP)](solid.md#SS_8_3)に反した例を下記する。

```cpp
    //  example/cpp_idioms/class_relation_ut.cpp 50

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
    //  example/cpp_idioms/class_relation_ut.cpp 91

    class q_chan : public kyukancho {
    public:
        std::string get_name() const override { return "キューちゃん"; }
    };
```

この誤用を改めた例を以下に示す。

```cpp
    //  example/cpp_idioms/class_relation_ut.cpp 113

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
kyukanchoとstd::stringの関係を[has-a](cpp_idioms.md#SS_21_1_2)の関係と呼ぶ。


### has-a <a id="SS_21_1_2"></a>
「has-a」の関係は、
あるクラスのインスタンスが別のクラスのインスタンスを構成要素として含む関係を指す。
つまり、あるクラスのオブジェクトが別のクラスのオブジェクトを保持している関係である。

例えば、CarクラスとEngineクラスがあるとする。CarクラスはEngineクラスのインスタンスを含むので、
CarはEngineを「has-a」の関係にあると言える。
通常、has-aの関係はクラス内でメンバ変数またはメンバオブジェクトとして実装される。
Carクラスの例ではCarクラスにはEngine型のメンバ変数が存在する。

```cpp
    //  example/cpp_idioms/class_relation_ut.cpp 144

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

### is-implemented-in-terms-of <a id="SS_21_1_3"></a>
「is-implemented-in-terms-of」の関係は、
オブジェクト指向プログラミング（OOP）において、
あるクラスが別のクラスの機能を内部的に利用して実装されていることを示す概念である。
これは、あるクラスが他のクラスのインターフェースやメンバ関数を用いて、
自身の機能を提供する場合に使われる。
[has-a](cpp_idioms.md#SS_21_1_2)の関係は、is-implemented-in-terms-of の関係の一種である。

is-implemented-in-terms-ofは下記の手段1-3に示した方法がある。

* 手段1.[public継承によるis-implemented-in-terms-of](cpp_idioms.md#SS_21_1_3_1)  
* 手段2.[private継承によるis-implemented-in-terms-of](cpp_idioms.md#SS_21_1_3_2)  
* 手段3.[コンポジションによる(has-a)is-implemented-in-terms-of](cpp_idioms.md#SS_21_1_3_3)  

手段1-3にはそれぞれ、長所、短所があるため、必要に応じて手段を選択する必要がある。
以下の議論を単純にするため、下記のようにクラスS、C、CCを定める。

* S(サーバー): 実装を提供するクラス
* C(クライアント): Sの実装を利用するクラス
* CC(クライアントのクライアント): Cのメンバを使用するクラス

コード量の観点から考えた場合、手段1が最も優れていることが多い。
依存関係の複雑さから考えた場合、CはSに強く依存する。
場合によっては、この依存はCCからSへの依存間にも影響をあたえる。
従って、手段3が依存関係を単純にしやすい。
手段1は[is-a](cpp_idioms.md#SS_21_1_1)に見え、以下に示すような問題も考慮する必要があるため、
可読性、保守性を劣化させる可能性がある。

```cpp
    //  example/cpp_idioms/class_relation_ut.cpp 260

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
    //  example/cpp_idioms/class_relation_ut.cpp 282

    class MyString : public std::string {};

    // ...
    MyString str{"str"};

    ASSERT_EQ(str[0], 's');
    ASSERT_STREQ(str.c_str(), "str");

    str.clear();
    ASSERT_EQ(str.size(), 0);
```

すでに述べたようにこの方法は、
[private継承によるis-implemented-in-terms-of](cpp_idioms.md#SS_21_1_3_2)や、
[コンポジションによる(has-a)is-implemented-in-terms-of](cpp_idioms.md#SS_21_1_3_3)
と比べコードがシンプルになる。 

#### private継承によるis-implemented-in-terms-of <a id="SS_21_1_3_2"></a>
private継承によるis-implemented-in-terms-ofの実装例を以下に示す。

```cpp
    //  example/cpp_idioms/class_relation_ut.cpp 179

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

この方法は、[public継承によるis-implemented-in-terms-of](cpp_idioms.md#SS_21_1_3_1)が持つデストラクタ問題は発生せす、
[is-a](cpp_idioms.md#SS_21_1_1)と誤解してしまう問題も発生しない。


#### コンポジションによる(has-a)is-implemented-in-terms-of <a id="SS_21_1_3_3"></a>
コンポジションによる(has-a)is-implemented-in-terms-ofの実装例を示す。

```cpp
    //  example/cpp_idioms/class_relation_ut.cpp 207

    namespace is_implemented_in_terms_of_1 {
    class MyString {
    public:
        // コンストラクタ
        MyString() = default;
        MyString(const std::string& str) : str_(str) {}
        MyString(const char* cstr) : str_(cstr) {}

        // 文字列へのアクセス
        const char* c_str() const { return str_.c_str(); }

        using reference = std::string::reference;
        using size_type = std::string::size_type;

        reference operator[](size_type pos) { return str_[pos]; }

        // その他のメソッドも必要に応じて追加する
        // 以下は例
        std::size_t size() const { return str_.size(); }

        void clear() { str_.clear(); }

        MyString& operator+=(const MyString& rhs)
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

## オブジェクトの所有権 <a id="SS_21_2"></a>
### オブジェクトの排他所有 <a id="SS_21_2_1"></a>
オブジェクトの排他所有や、それを容易に実現するための
[std::unique_ptr](https://cpprefjp.github.io/reference/memory/unique_ptr.html)
の仕様を説明するために、下記のようにクラスA、Xを定義する。

```cpp
    //  example/cpp_idioms/unique_ptr_ownership_ut.cpp 7

    class A final {
    public:
        explicit A(int32_t n) noexcept : num_{n} { last_constructed_num_ = num_; }
        ~A() { last_destructed_num_ = num_; }

        int32_t GetNum() const noexcept { return num_; }

        static int32_t LastConstructedNum() noexcept { return last_constructed_num_; }
        static int32_t LastDestructedNum() noexcept { return last_destructed_num_; }

    private:
        int32_t const  num_;
        static int32_t last_constructed_num_;
        static int32_t last_destructed_num_;
    };

    int32_t A::last_constructed_num_ = -1;
    int32_t A::last_destructed_num_  = -1;

    class X final {
    public:
        // Xオブジェクトの生成と、ptrからptr_へ所有権の移動
        explicit X(std::unique_ptr<A>&& ptr) : ptr_{std::move(ptr)} {}

        // ptrからptr_へ所有権の移動
        void MoveFrom(std::unique_ptr<A>&& ptr) noexcept { ptr_ = std::move(ptr); }

        // ptr_から外部への所有権の移動
        std::unique_ptr<A> Release() noexcept { return std::move(ptr_); }

        A const* GetA() const noexcept { return ptr_ ? ptr_.get() : nullptr; }

    private:
        std::unique_ptr<A> ptr_{};
    };
```

下記に示した上記クラスの単体テストにより、
オブジェクトの所有権やその移動、
std::unique_ptr、std::move()、[rvalue](core_lang_spec.md#SS_19_7_1_2)の関係を解説する。

```cpp
    //  example/cpp_idioms/unique_ptr_ownership_ut.cpp 48

    // ステップ0
    // まだ、クラスAオブジェクトは生成されていないため、
    // A::LastConstructedNum()、A::LastDestructedNum()は初期値である-1である。
    ASSERT_EQ(-1, A::LastConstructedNum());     // まだ、A::A()は呼ばれてない
    ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない
```

```cpp
    //  example/cpp_idioms/unique_ptr_ownership_ut.cpp 57

    // ステップ1
    // a0、a1がそれぞれ初期化される。
    auto a0 = std::make_unique<A>(0);           // a0はA{0}を所有
    auto a1 = std::make_unique<A>(1);           // a1はA{1}を所有

    ASSERT_EQ(1,  A::LastConstructedNum());     // A{1}は生成された
    ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない
```

<!-- pu:essential/plant_uml/unique_ownership_1.pu--><p><img src="data:image/png;base64,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EEhMTHSV/wTMVY6M63fF9zEEa9asEfHOnTt36dLl7bffRiMoKGjmzJlbtmxp1qxZTEzMuHHjcNQXX3whMrFc7du37xtvvCE/DhYD4ljxOTKQv/mydOlSLLEnTpyYkJDQu3fvFi1aXLp0yevIyrBiZG2NPfDAAzgcjokDkSx7P/zwQ7SHDh2KrtatW+P6xZ1DGdDrlZSWfxsBhw8fPjwuLg5XLodVzo5Hinr16mmDvq5Hm+O1HRsb2759exEE7733Xv369bUf+9QuLto37dtpmCl02BOM46GHHtIGT58+DduFlbjKkXGvuxKsSUUchtupUyesKEeMGAHXGzhwoNvtfv7555s2bYqF+aRJk+QI06ZNQ9pdd90lvicnh0Jm165dsYTPzs6WyaXlX6Tr2LEjHCo6Ojo9Pb20/IvP+pGVYUt1Bnrq1KmHH364UaNGUVFR8fHx4eHhsnfBggUdOnTA4Y888oj87qB+QP2VCHDna9WqFbx71KhR8uMR5eyl5b8nqQ36uh5tjtf2kSNHcOvduHGjiGOQIUOGiHYg4KJ9076dhi2F7mTS0tLknUACz9UH/WDs2LG4heA2fODAgZCQkH379qkZtYft7dsrtO/rqCnOwDlCJ8a5cuVKv3799u/fjzXg1KlT1e5ahfZN+3YczhE6sTe0b9q343CO0Im9oX3Tvh2Hc4RO7A3tm/btOJwjdGJvaN+0b8fhHKETe0P7pn07DucIndgb2jft23E4R+jE3tC+ad+OIzIy0kWI9QkLC5NGFhERoXbbFO2sad9OxO12Z2VlZWZmbt26NTU1dRUh1kT7N9cFTlA1/9K8o+07Ly8vJycHt+6MjAzoYD0h1gTqhYah5JwbOEHV2lmjltXytiO0bw/5+fl45srOzoYCcA/fTYg1gXqhYSj5wg2coGrtrFHLannbEdq3h8LCQty08d7j7o3nr2OEWBOoFxqGkvNu4ARVa2eNWlbL247Qvj0UFRXhXcd9G2+/2+2WKxdCrAXUCw1DyYU3cIKqtbNGLavlbUdo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYkm82DchhBALQfsmhBBLQvsmhBBL8v8Bd8qC/hsMX6MAAAAASUVORK5CYII=" /></p>

```cpp
    //  example/cpp_idioms/unique_ptr_ownership_ut.cpp 67

    // ステップ2
    // xが生成され、オブジェクトA{0}の所有がa0からxへ移動する。
    ASSERT_EQ(0, a0->GetNum());                 // a0はA{0}を所有
    auto x = X{std::move(a0)};                  // xの生成と、a0からxへA{0}の所有権の移動
    ASSERT_FALSE(a0);                           // a0は何も所有していない
```

<!-- pu:essential/plant_uml/unique_ownership_2.pu--><p><img src="data:image/png;base64,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" /></p>

```cpp
    //  example/cpp_idioms/unique_ptr_ownership_ut.cpp 75

    // ステップ3
    // オブジェクトA{1}の所有がa1からxへ移動する。
    // xは以前保持していたA{0}オブジェクトへのポインタをdeleteするため
    // (std::unique_ptrによる自動delete)、A::LastDestructedNum()の値が0になる。
    ASSERT_EQ(1, a1->GetNum());                 // a1はA{1}を所有
    x.MoveFrom(std::move(a1));                  // xによるA{0}の解放
                                                // a1からxへA{1}の所有権の移動
                                                // MoveFromの処理は ptr_ = std::move(a1)
    ASSERT_EQ(0, A::LastDestructedNum());       // A{0}は解放された
    ASSERT_FALSE(a1);                           // a1は何も所有していない
    ASSERT_EQ(1, x.GetA()->GetNum());           // xはA{1}を所有
```
<!-- pu:essential/plant_uml/unique_ownership_3.pu--><p><img src="data:image/png;base64,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" /></p>

```cpp
    //  example/cpp_idioms/unique_ptr_ownership_ut.cpp 89

    // ステップ4
    // x.ptr_はstd::unique_ptr<A>であるため、ステップ3の状態では、
    // x.ptr_はA{1}オブジェクトのポインタを保持しているが、
    // x.Release()はそれをrvalueに変換し戻り値にする。
    // その戻り値をa2で受け取るため、A{1}の所有はxからa2に移動する。
    std::unique_ptr<A> a2{x.Release()};         // xからa2へA{1}の所有権の移動
    ASSERT_EQ(nullptr, x.GetA());               // xは何も所有していない
    ASSERT_EQ(1, a2->GetNum());                 // a2はA{1}を所有
```

<!-- pu:essential/plant_uml/unique_ownership_4.pu--><p><img src="data:image/png;base64,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" /></p>

```cpp
    //  example/cpp_idioms/unique_ptr_ownership_ut.cpp 100

    // ステップ5
    // a2をstd::move()によりrvalueに変換し、ブロック内のa3に渡すことで、
    // A{1}の所有はa2からa3に移動する。
    {
        std::unique_ptr<A> a3{std::move(a2)};
        ASSERT_FALSE(a2);                       // a2は何も所有していない
        ASSERT_EQ(1, a3->GetNum());             // a3はA{1}を所有
```

<!-- pu:essential/plant_uml/unique_ownership_5.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAeoAAAEmCAIAAAAiJUSiAAA0NklEQVR4Xu2dCXQUVdr3KwESSEIIYNiRRQcmGT4QPpj4os6L4AFkc+HwDiO8AorAmWExGs13BtkNBmSTHRTZFYRhBnkJywgOi7KKIUFQ1jcYiYBAYyAkEJLvP33hdnGrO4TupDtV9f+dHM69z33qqbrN8/zrVnV3tVZICCHEhGiqgRBCiBmgfBNCiClxyXcBIYSQMg/lmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnlmxBCTAnl2xtOnz7dpk2bkSNHqgOEEOIvLCLfubm563SsXbt2z549cjQzM3OMgePHj+sCFMUvv/xy9OjRI0eOpKenp6WlpaamYvPOnTvXrVsXowcPHpT7PXDggLoxIYSUDhaRbyhslSpVoqKioqOj69WrV7ly5Tp16ty+fVuMQqm7GoDs3hvj3+A0oJoKCiZOnKgZiIyMTElJwWi3bt2ksU+fPurGhBBSOlhEvvXcunXrkUceeffdd6XlqAeuXr0qffbu3bt//35IP84E6P7xj3+cPHmyGLp8+fKpU6cyMjKwis/Kyrp48eJTTz01ePBgMdqiRYsNGzbIOIQQ4h8sKN8LFiwIDw8XKgxu3rypWzTfwyeffCJ8Tpw4UaFChXXr1jVs2DAhIQGWBg0aJCcny5h6srOzw8LCVqxYIbrVqlXbsmXLxo0bDx8+fK8jIYSUIlaT72+//RbaKiRYcu4uEyZMqFWrluzm5ORIn+HDhz/22GOLFi16+eWXsSoPCgr6/PPPdTFczJ49OyIiQqzcr1+/rj8fvPDCC1j7qxsQQkgpYCn5PnjwYJ06dRo1aoTV96ZNm9ThgoLXX3+9devWqtXJmTNn5syZI8T3vffeCwkJuXTpkupUUHDkyJGoqKgxY8ZIC9yuXbuWl5e3detWKPjOnTt17oQQUlpYRL7z8/MXLlyIdXfnzp2xIsYqu0KFCoqCHzp0qHr16hjSGxVu3LgB7Q4ODh47dqwyBI2ePn16lSpVunTpcvPmTWH8+eef//u//3vatGmrVq0aMmRIuXLlTpw4ce92hBBSKlhBvi9fvtyqVavy5cuPHj1a3rtISEjAGnz//v0FTuV97rnnIMo9evSAuN+zsY4333wzOjq6UqVKSUlJejvEul+/fhDuypUrQ/2ldgsmT56M9X5oaGhMTMzq1av1Q4QQUnpYQb7BrFmzvvvuO73l9u3bUPNz586JLtbmW7du1TsYWbFixYwZM86fP68OFBRMmTIFERwOhzpACCEBwiLyTQghdoPyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpsRS8l29enX98/8IKSbIHDWZig2zjniHL1knsJR84xWRsyCk+CBzHA5HdnZ2Tk5OXl5efn6+mlueYdYR7/Al6wSuULKlupgHFhLxDmRORkZGVlbWpUuXUE6oJTW3PMOsI97hS9YJXKFkS3UxDywk4h3InPT09BMnTmRmZqKW9L/jcV+YdcQ7fMk6gSuUbKku5oGFRLwDmbN79+7U1FTUElZDWAqpueUZZh3xDl+yTuAKJVuqi3lgIRHvQOakpKSglrAawvXsAz0ZmFlHvMOXrBO4QsmW6mIeWEjEO5A5n3766ebNm/fv34+lkNvfyfMEs454hy9ZJ3CFki3VxTywkIh3+FJIzDriHb5kncAVSrZUF/NQRgopMTFx7969qpV4IC8v7/z586rVv/hSSMw6M2L2rBO4QsmW6mIe/FNIP//885EjR1SrDhzGvHnzVGtJgLDfffedavUv953+gzJu3Di8YkePHlUH/IgvhcSs8wP3nf6DYvasE7hCyZbqYh78U0jh4eFF10npFVLpRS4+952+J7755hvV5Ey2Ro0alS9f/u2331aGfvjhh+zsbMVYSvhSSMw6P3Df6XvCqlkncIWSLdXFPJRSIX355ZdLliwRJ+oVK1ZgLy+99BKS6cKFC9Ln+vXrGzZsWL16dVZWVjHTXVnU6Ltonzx58tChQ8uXL09JSbl586Z005Obm4v/+08++eT06dOrVq1KTU0V9iIii01wnFjOSAe3YKvjx49v37595cqVp06dEka300cbB3DgwIFZs2a5ttexa9eu//zP/3zkkUfUgcJCxEfAnj171qlTJz8/Xz80ffr0hx56aMqUKTk5OXp7aeBLITHrhL2IyMw6t/iSdQJXKNlSXcxDaRTSsGHDNCdBQUGTJ09u0KCB6AKkjvA5d+5ckyZNhDEyMlK7W0jCIkMZu/p603fRjo2NFf6gTZs2t27dUnzwn92iRQvhEBoaGhERod/cbWSkfvPmzcUmOM49e/ZIHyPwqVu3rnAOCQlBucLodvpox8fH4/Xp1q3bPSEKC+HTqVMnODz77LMHDx5URkHfvn0x0507d2rOD1Hph65evTp27NgqVarUrl179uzZeXl5+tGSRfOhkDRmnSGUvsus84TmQ9YJXKFkS3UxD1opFBISdOjQoVeuXJk/f/7FixcLDWkKBgwYUK1aNSQK3EaMGCEdRMJJN2PXbbqLduXKldevX48lAJZC6G7ZskXxGTJkSNWqVbHE+OWXX1577TVlc7eRsQlqD2uW9PT0evXqPfHEE9LHCLbCMmTHjh0OhwPxo6KikF7CrkwfFuQ6ikGf61jHPf/88xhq3779V199pXN3gVIJCwtLTk7G/13jxo179eqlehQWXr58+a9//Sv+F1DDy5YtU4dLCM2HQtL/n5YUzDpmXXFwhZIt1cU86NO0pGjXrl39+vWxCpAXWcZMgkNiYqJo45LT6OAWT+ku2hMmTBBtrIDQXbhwoeLTsGHDt956S+9z30LCJq+++uo8J127dg0ODi5icYGtkOKi/eOPP6KLPBN2YyENHjxYbyl0XvBiZRQTE4OLcWVIsmDBAmw7atQoBHz66aexmkPZqE6Fhb/++ivWWfD8j//4D3WshNB8KCSNWefEU2RmnSc0H7JO4AolW6qLedBKoZDwXzt8+PBKlSrFxcXduHGj0F0mhYeHT506VXaNDm7xlO5FDOntRezU0+ZYdGj3gtWKdFPQB7l27Rq6WJEpduk5d+5cvUWAEkK5opyee+45t+8gPf744/cejjZnzhy9A0ooKSkJa0ys2rBTT3djfUfzoZA0Zp2hre8y6zyh+ZB1Alco2VJdzINWCoUkVgppaWkI/tlnnxW6y6SWLVt2795dtHExa3RwC9J60qRJor1p0yb9VkoE2dXb9Ts9fPiwfshTZFzDLl26VNhv376tfxPMCLZ6/fXXRTslJQVd8bFi4+yMFj179uzBlSx8+vXrp7cfO3ZM2bBVq1atW7eW3a1bt6KEatasOX369NzcXGkvDTQfCklj1jnxFJlZ5wnNh6wTuELJlupiHrSSLqRdu3ZFR0cnJCQMHTpUu3srEAuQTp06jR8/XryxA5CdIlHGjh2L/3t93usPSekivWrVqoWMR3zE1GeVkmH6gNIudzpu3DgcpH7IU+TFixdjQTdixAhcn7Zt2xY+WGjc3YmK5nzfbNCgQe+99x48f//73xc408U4feVo3fLll1++/PLLeguuwcuVK6cv5smTJyOU/HgvJjhx4kQswaRD6aH5UEj6/9MSgVnHrCsmrlCypbqYB32alggOhwOZVLVq1SpVqsTHxwvj6NGjsdBo2rSp/mNSSIK6deuiil555RU4F6eQzpw507Fjx4iIiEaNGiFjIiMjH6iQCp07xfUddte7d2/9UBGR0WjSpEnFihVxVb5z504ZyggComAQAXG6dOny448/Crtx+spRFYf8/HwU5zPPPKM3nj17FqWL4tcb/YMvhcSsE/YiIjPr3OJL1glcoWRLdTEPJV5IJsKLbBbMMyAudb0OaEZ8KSRmnWotBmrOMeseMOsErlCypbqYBxaSai0GmoGaNWsKu3cBzYjmQyFpzLoH596M+zfMugfKOoErlGypLuZBs3EhDR48uOjL0gelxAOWZXwpJGadavWBEg9YlvEl6wSuULKlupgHOxcS8QVfColZR7zDl6wTuELJlupiHlhI9yU7O/vzzz9funQpHy6qx5dCYtbdF7yea9euXbFiRVpamjpmY3zJOoErlGypLuaBhVQ027dvj4qK0u7SvXt35Xk9tsWXQmLWFQ1eWPHNnWAnffr0uX37tupkS3zJOoErlGypLuaBhaTn5MmTy5Yt0z867sknn4yLizt27FhOTs6MGTPwcm3YsOHejWyKL4XErNOjZB0yrVmzZi+++KL4CKB4StRm5/fgiS9ZJ3CFki3VxTywkCRTp07FSkessiHZUsHlF8kcDgeG1q1b59rGxvhSSMw6idusw1pbpt8333yjcdFwF1+yTuAKJVuqi3lgIQlQLX379u3fv/+FCxfWrl1rLJgbN27gGrZ+/friaXbEl0Ji1gmKyLozZ87Ex8f/8Y9/jIiIeP7550vvKSLmwpesE7hCyZbqYh5YSBK8Gps2bUpMTBRfjZs/f74cOnjwYGxs7FNPPZWZmanbwtb4UkjMOkmBh6xLS0tDvjVo0KBmzZr2+Vj3ffEl6wSuULKlupgHFpJk+PDh5cqV69Chw8CBAzXdVyE+/vjj8PDwSZMm8e0jPb4UErNO4inrJIsWLYK96F9ssA++ZJ3AFUq2VBfzwEKSVKlSZeTIkWicOnVKFtLf/va3kJAQ5edFSKFvhcSskxizLi8v76OPPpLPqLpw4QLsK1euvGczu+JL1glcoWRLdTEPLCRJbGxss2bN3n//fTSCgoKSkpJycnKio6PbtGlz5xkTTlatWqVuaUt8KSRmncSYdQcOHAgNDf3Nb34zYcIE2Fu1aoWLv7Nnz6pb2hJfsk7gCiVbqot5YCFJ9u7dGxMTExYW1r9//06dOnXr1k38mq1C06ZN1S1tieZDIWnMursYs67Q+V7Ls88+G+nkqaee2rFjh7qZXfEl6wSuULKlupgHFhLxDl8KiVlHvMOXrBO4QsmW6mIeWEjEO3wpJGYd8Q5fsk7gCiVbqot5YCER7/ClkJh1xDt8yTqBK5RsqS7mgYVEvMOXQmLWEe/wJesErlCypbqYBxYS8Q5fColZR7zDl6wTuELJlupiHlhIxDt8KSRmHfEOX7JO4AolW6qLeWAhEe/wpZCYdcQ7fMk6gSuUbKku5oGFRLzDl0Ji1hHv8CXrBK5QsqW6mAcWEvEOXwqJWUe8w5esE7hCyZbqYh6qV6+uEfLghIeHe11IzDriHb5kncBS8g0cDkdGRkZ6evru3btTUlI+tTGa89xOigmyBTmDzEH+IIvUxCoSZp2EWfdA+JJ1BdaT7+zs7KysLJzKUlNT8bpstjGa81epSDFBtiBnkDnIH2SRmlhFwqyTMOseCF+yrsB68p2Tk4NrkMzMTLwiOKfttzEoJNVEPINsQc4gc5A/yCI1sYqEWSdh1j0QvmRdgfXkOy8vDycxvBY4m+F65ISNQSGpJuIZZAtyBpmD/EEWqYlVJMw6CbPugfAl6wqsJ9/5+fl4FXAew8vhcDgu2RgUkmoinkG2IGeQOcgfZJGaWEXCrJMw6x4IX7KuwHryTSQoJNVESCnDrPMnlG/LwkIi/odZ508o35aFhUT8D7POn1C+LQsLifgfZp0/oXxbFhYS8T/MOn9C+bYsLCTif5h1/oTybVlYSMT/MOv8CeXbsrCQiP9h1vkTyrdlYSER/8Os8yeUb8vCQiL+h1nnTyjfloWFRPwPs86fUL4tCwuJ+B9mnT+hfFsWFhLxP8w6f0L5tiwsJOJ/mHX+hPJtWVhIxP8w6/wJ5ds6NG/eXPMAhlRvQkoCZl0AoXxbh+TkZLWA7oIh1ZuQkoBZF0Ao39YhIyMjODhYrSFNgxFDqjchJQGzLoBQvi1Fu3bt1DLSNBhVP0JKDmZdoKB8W4qFCxeqZaRpMKp+hJQczLpAQfm2FJcvXw4NDdVXEbowqn6ElBzMukBB+bYaL774or6Q0FU9CClpmHUBgfJtNdauXasvJHRVD0JKGmZdQKB8W40bN25UrVpVVBEa6KoehJQ0zLqAQPm2IAMHDhSFhIY6RkjpwKzzP5RvC7J9+3ZRSGioY4SUDsw6/0P5tiC3b9+u7wQNdYyQ0oFZ538o39Yk0YlqJaQ0Ydb5Gcq3NTnsRLUSUpow6/wM5ZsQQkwJ5ZsUi5s3b8p7mvo2ISRQUL5JsdA0be7cucZ2EWRlZaWnp6tWQkgJQfkmxcIL+Q4PDy+OGyHEOyjfdgSqeuLEiW+++WbZsmUbN27My8uT9iNHjujdZLcI+Ub7hx9+2LZt24oVK06ePCmMy5cvh9tLL72E0fPnzwu3U6dO7d+/f+bMmXJbQojXUL7tCIQ1NjZWfMkCtGnT5ubNm8Ku12VPkm10q1u3rggVEhKycuVKGBs0aCDjQ7KFW3x8fFBQULdu3eS2hBCvoXzbEShp5cqV//GPf1y/fh0LcHQ3b94s7N7J90MPPfSvf/3rypUrr732WlRU1C+//OLWrXbt2jt27MjNzZVGQojXUL7tCJR0/Pjxoo11N7oLFiwQdu/k+7333hPts2fPortp0ya3boMHD5ZdYknCo8I1a1G9enV1kmUGyrcd0QzCKrqe7EW0lW52dja6WNG7dZszZ47sEkuC/+UFpxZY6Q8zcjgcSOycnJy8vLz8/Hx1zoGD8m1HjMIqumFhYfLXwVNSUjxJtnHz119/XbQ3btyI7p49e9y66bvEklhSvjMyMrKysi5dugQRl+/zlwUo33bEk7C2b9++Vq1aUPCEhITw8H9fBbuVbOPmQUFBgwYNmjhxIjb//e9/L77UgwidOnUaN26c2/dFiSWxpHynp6efOHEiMzMTCo41uDrnwEH5tiNG/RXd06dPd+zYMSIiolGjRklJSZGRkW4l27g5ZBqbYMMuXbqcPXtW2EePHo3lfNOmTcWnDynfdsCS8r179+7U1FQoONbgWICrcw4clG/iK9RlIrGkfKekpEDBsQbPyMhwOBzqnAMH5Zv4CuWbSCwp359++unmzZv379+PBfilS5fUOQcOyjfxlcGDB+/YsUO1EvPwpz/96fLly6rVKyjf/oTyTYjdgULVr19/27Zt6sCDU7LyPef7OVP2TzHa55+YPzN9ptEut5r93Wyj3bs/yjchpOyiOQkODn7zzTd9/JH4kpXv7q93R8CxW8bqjb3+2qt8SPnGLRtLy/RD0wdMGSDd0A4uFwyHIiS++H+Ub0JI2UXIt6B58+a+/GJOCcr3/JPzH6r/EIS406BOentYZFinwXcsf/nwL83aNasQWgH77TOhj/SZuGMiLK/NfM0Y9kH/KN+EkLKLXr5BaGjolClTvPtFDq3k5PuNlW8gWqvOraJqRs07Pk/aNZ1SY6Ed91zcc288pzca3Xz50yjfhJAyi167Je3bt8/IyFBd74dWcvId93xc7UdrJ6xKQMxhHw+Tds2gyxO2TzAajRbv/jTKNyGkzKJXbT1RUVHi8b/FRysh+f7g8AchlUJefPtFcQvl/3b5v8I+68gs7AKLbr2zW/muULFCr7/2MkZ+0D+N8k1MzZgxY/RVjS5HrTSqH9ITQPnum9QXoboO7QpRbvp40/Ih5acfmg77H/70h7DIsIk7J+qd3cp33HNxUTWjJn09yRj8gf40yjchpMxyr2jfIbA3Txq3bKwcz5/G/Qn2HvE9ypUvNzpltN7ZrXxD9Ov9tt60b6YZgz/Qn0b5JoSUWRShDPhbl+O2jlPk+OHfPdzg/zRAY+4PczH0cvLLen+38g2V7z2mt97i3Z9G+SaElFn02l0WPjjY8bWOweWCpxxwfWGn5//richjNo9Z4O49SbfybbR490f5JoSUXYRwl5Gv7cw7Pi8yOjLmiRi9MXl3clBQEGR9gTtdpnxTvgmxKVpZ/dK827/wqPCnX356zrE5xiHxhxPAqI2jcCSDZw82jj7oH+WbEFJ2Mdcjq/q82ycsMqxBs3/fCnf7129yv+BywTFPxsw+WgJPPqF8E0JsgR/kW/zpv4ep/M0/OR9/Rrt3f5RvQkqYxMRE8YuaZYcPPvjgQT9pt3379i1btqhWM+M3+fbbH+WbkAcjKysrPT1dterQythvRMyfP79GjRoXLlxQB3T8+uuv69evX7JkiTzxfPbZZ9HR0UVvZS4o3/6E8k3KIuHh4UWrc5mS7ytXrlStWnXBggXqgI5t27ZFRUVpd+nevfutW7dgj4mJGTlypOptWijf/oTyTcoE27dvX7x48XfffYf28uXLUTMvvfQSBPr8+fPS59q1a59//vmqVavOnTtXTPmGz969e1esWLF06VJshfUvNv/HP/5x/fp1vVtubu4///lPDGVmZgrLwoULU1JSpAM2/5//+R80bty4sWnTJnji+kCOTp06FfItf4McRQ7/jRs35uXlSZ8nn3wyLi7u6NGj2PX06dNx/JgL7ElJSVi2SzezQ/n2J5RvEniGDRsm1qRBQUGTJk1q0KDBnTWqpqFmhM9PP/3UpEkTYYyMjNTuyrewyFDGbvny5YWxVq1azZs3F+02bdrcvHlT+Fy8eLF169bCjlX/3/72Nxh79OhRvXp1ob/Hjx/H0LRp03AukRFwDF9//bWI0KFDh549e4r2lClTgoODhQ/0Wq/g8iPVWK1jVOxo586daBd9p8hEaJRvP0L5JoEnIiJi6NChly9fnjdvnrgRrBkW1wMGDKhWrdqBAwfgNmLECOkghFK6GbuPPvoo9HfLli1o4wTwv//7v1gXo41FtPD585//DC3evXs3dLx79+5Qbcjr+vXr4SNW3OPHjw8NDcXokCFDWrRocerUqbS0tHr16j3xxBMiQu3atceOHYsGxLpv3779+/eH0K9Zs0a7u8TWg0V6nz596tevL2aKf+G2bt06xc2kaJRvP0L5JoGnXbt2kLOVK1eK28EF7uQbDomJiaINlTQ6uAVu06dPRyM/P19zrqBlW96qfvjhhxMSEkRbLLSh7DiSunXrQmdh/N3vfte7d280GjZs+Oqrr8510rVrV6yyc3NzYa9QocIHH3wgIty+fTslJQWHik0QCickYRfg9BMbG/vUU0/9+OOPwiLm8tFHH+ndzAvl259QvkngQUkMHz68UqVKcXFx4g6yUZ3Dw8OnTJkiu0YHt+jdPLX1kbOzszG0bNkytEeOHInLgn379sHyz3/+E5awsDDtXlDPsOOyICkpSUTARMqVK9ehQ4eBAwfq9wIWLVqEfSUnJ+P8IY24mIDbqlWrpMXUaJRvP0L5JoFHrGEPHz6MUlm9enWBO3Vu2bJl9+7dRRtrWKODW/RuntqPPfbYCy+8INrivor4YN+pU6eCgoLatGnTuHFj8fi9Fi1aLFmyRHhCguXbqq1atYJYi3aVKlXEJ0lOnjyp38vatWtDQkIQX3QlaWlpcNu9e7diNymUb39C+SYBZufOndHR0QkJCUOHDkWpoE4KnCviTp06jRs3Tr7BCN3EaL9+/caMGYPVrlRGzYmMZuy6lWx9G4tidAcMGPDuu+/WqFGjbdu28lmpzzzzDIZgF92PP/4YlwgjRox477334FarVq2rV68WOL9DBIkXPrGxsc2aNZs8eTIaUH+x7fXr1zFHnAnm6oAoYOjDDz+sWLGijw+KKjtolG8/QvkmAebKlSuDBg2qWrUq1q3x8fHCOHr06LCwsKZNmx45ckR6Tpo0qW7dutDuV155Bc4lJd9g+vTp0N+oqKhevXrpP6q4atWqcuXKyU8TFjg/idikSRMIblxc3I4dO4Tx2LFjcBM3WLByj4mJwcH3798fZ6Bu3brBKD7pqIDZYahjx47ixro10CjffoTyTUgJMGTIEAi6fOu1mBw+fLhChQqHDh1SB0wL5dufUL4JKQFycnI6d+6cmpqqDhQJ1vKjRo1SrWaG8u1PKN+EkBKD8u1PKN+ElAw3b9707vchrQTl259Qvon5uO/zCAOCVrzPMlobyrc/oXwT83Hf5xEGBMp3AeXbv1C+SRkC8nfq1CnUycyZM4XF+IQ/4/MI0dB/vlDfVQKiiwr85ptvli1bpjwR0K2/p+cOnnD3TEG9fBdxSMYZWQnKtz+hfJMyBEolPj4+KChIfFza7RP+jM8j1Oum0lUCohsbGys31z930K2/2+cOenqmoLJft4fkdkZWQqN8+xHKNylDoFRq1669Y8cO8TV6T0/48ySOxq4SEN3KlSuL531jAa7d/ZKnflu9v/G5g+fOnfP0TEFlv24PydOMLAPl259QvkkZAqUyePBg2fX0hD9P4mjsKgHRhQqLNtbd/9aae38iR/F3+9xBT88ULI58e5qRZcDFimYtwsPDKd+E3B9Uy5w5c2TX0xP+NA/iaOxq9wYswlNa9P4F7p476OmZgp7a+q6nGVkJh8ORkZGRnp6+e/dunOc+NT+YBeaCGWFemJ064cBB+SZlCEX1PD3hT3GDJiYnJ4s2Kk0/qngW3XVrMT530NMzBfVtT4fkaUZWIjs7OysrC6el1NRUqN5m84NZYC6YEeaF2akTDhyUb1KGUNTT0xP+lOcRtm/fHkOQy4SEBAx5ktT7dt1aCgzPHXT7TMGCe7f1dEieZmQlcnJyLl26lJmZCb3DinW/+cEsMBfMCPOSv2haFqB8kzKEUT3nunvCn/I8wtOnT3fs2DEiIqJRo0ZJSUmRkZElK9/KcwfdPlOw4N5tizgktzOyEnl5eViiQumwVs3IyDhhfjALzAUzwryMHzYNIJRvQkhJkp+fD43DKhVi53A4LpkfzAJzwYwwL/0vJQUcyjchhJgSyjchhJgSyjchhJgSyjchhJgSyjchhJgSyjchhJgSyjchhJgSyjchhJgSS8n3mDFjNB3ocpSjHOVo0aPmxVLyTQgh9oHyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyfYfq1avrn0lGiElBJtswq/Wztg+U7zsgA+QrQIh5QSY7HI7s7OycnBz7ZLV+1nl5efn5+WqFWxHX9GVLdbEH9kl0Ym2QyRkZGVlZWZcuXbJPVutnDRGHgqsVbkVc05ct1cUe2CfRibVBJqenp584cSIzM9M+Wa2fNRQca3C1wq2Ia/qypbrYA/skOrE2yOTdu3enpqZCy+yT1fpZYw2OBbha4VbENX3ZUl3sgX0SnVgbZHJKSgq0DKtR+2S1ftYZGRkOh0OtcCvimr5sqS72wD6JTqwNMvnTTz/dvHnz/v377ZPV+lljAX7p0iW1wq2Ia/qypbrYA/skOrE2lG/Kt+0IYKLn5eWdP39etZKSJjExce/evaq1dJg5c+bq1au3bt2qDpQ+lG/Kt+0IYKKPGzcOez969Kg64IGePXv6qAs///zzkSNHFOP169dTUlI+/vjjjRs3ZmdnK6M+4naPXuNdNLzI8+bNE200Fi9eXKArAGH87rvv9BbvWLBgQY0aNfBKRkdHX7x4UR0uZSwv35cvX166dKnyP0X5voPqYg8ClejYdaNGjcqXL//222+rYx7Qy5B3hIeHKxEg2VAc7S4RERFQN72Djxj36AveRdO/bmKaEydO9OTgNQ6Ho2rVqgsXLkQ7JiZm5MiRqkcpoxeyQGV1KbFhw4YuXbpUrFjR+D+lnzXl23YEKtG3b9+OXWNBXadOnfz8fHXYHcbclZw8eXLZsmVYRN+8eVMav/zyyyVLlsjV/YoVKxDhpZdeQpALFy7A8u2334aGhnbu3DktLQ3r7oMHD3bq1OmJJ57AMqfQeW/niy++WL169U8//SRjFjrXqtjdoUOHli9f/qB7ROP06dMHDhyYNWuW6OoXU0oXB4CrDQQ5e/ZsobtogtzcXFQvjhNrc2nEJQVqHsasrCxFvuvVq1euXLlt27ZJZ+ng6XjQ2Ldv38qVK/Eii0+nIfL69etzcnKk87Rp0yDfN27cQBunB5wU5ZB/sLB8Y9Hdp0+fCRMmGEuA8n0H1cUeBCrR+/btGxsbu3PnTs35ySdh1JxIH2PXrXxPnTo1ODhYOMfFxQk9HTZsmLAEBQVNnjwZlgYNGggLgIDC8uKLLzZu3FgojsIvv/zSunVr4Yw177p16+QQLDhyGapNmza3bt0qLN4e0YiPj4dDt27dRFc/I3334sWLLVu2FNuGhITgAIzRAHS8efPmwhgZGblnzx4Yz50716RJE2nU7pVv6Gzt2rVr1qwpT0vSQe+p2HGdJALWqlVL7lHOHXTo0AEnY9HetWsXRr24z+MLmnXlWyA+z075LqB8SwKS6FevXg0LC0tOTsYBQEB79eol7EIUpJuxa5RviDXOBP3794eQrV27Fj5YdcIeERExdOjQK1euzJ8/X96HVSJUr17d062bP//5zxC+r776CjrevXt3eDocDjGEIJUrVxZrTyzA0d2yZUth8faILqQTJy2srN2Oyu6QIUOioqJQk5gXlBGLbqO/cGvRogVW9Onp6VhW49IBxgEDBlSrVg0XEziYESNG6LdCe+HChbj0wQL8ySefFOIrHTwdDxqPPvoo1AFXA2jj3JCRkYGTLtoQDuGMeY0bN060MX0M/f3vf5eh/IBG+aZ8242AJPqCBQuw31GjRiEXn3766dDQUHG/omiMuSvALDZt2pSYmNi7d2/4QD1hbNeuXf369T/55BP9nRklQoUKFbByl109Dz/8cEJCgmiLspE6hTYuY0Ub8qc5BbGweHtEd/DgwUWMyq7+AHJzc40OgoYNG7766qvznHTt2hVXITgx4DDwaggHnN70W8nX591330X7zTffRBtSfl/5njFjBhq3b99Ge/r06bIt5l7ofDFnzpwp2mKnixYtuhPIL2iUb8q33QhIoj/++OPavcyZM0d1MmDMXcHw4cMhQFiiDhw4UPrgfAB7pUqV4uLi5O0RJQIW/tA+2S105oAQ3/DwcKns165dw4ZYaIuuEuSB9oju3Llz9V23oQrvPQCJ8RXARcydV/AuJ0+eVLbVbyXbmGmXLl3QxZmvSpUq95VvYwSljfW+fEcUq34MrV69WnT9g0b5pnzbDf8n+rFjx5QsbNWqVevWrXUu7jHmrgDqIz7ncOrUKekj7k6kpaXB8tlnnwlPJcJbb70VEhICH2mZPHnyb37zm8zMzMcee+yFF14QRnGXQH50WgnyQHtUuhDfSZMmiTZkVD+K16RHjx6iffTo0a+//rrQsDlo0aLF0qVLRRvLYfGWZsuWLbt37y6MBw8e1G+lb6PUH3aCJbwwejoeTxGUA8bpU7TF19a/+uor0fUPGuWb8m03/J/oEE0slvWfnYBoas53ujQn0m7sis9dCNasWSPssbGxzZo1e//999EICgpKSkratWtXdHR0QkLC0KFDtbv3pgudS9pOnTqNHz9e3PO9evUqNqxcuXJ8fPyMGTP+67/+C85C+D7++GO0BwwYgGg1atRo27Ztwd2kUUpIdIu5R2Xb9u3b16pVC4qJDeGpHxV31fv06YPRevXqYWq4LFCigcWLF2O9P2LEiOTkZBwkov36668QdGzbr1+/sWPHYlGsD6scwL59+3ACk0ZPx+Mpgr6dmJiIqxnR/uijjypWrCjv+fgHjfJN+bYbfk50aBAE4plnntEbz549C9mFZGhOpN1tV4KFp7BjXRwTE4OVY//+/aFu3bp1czgcgwYNqlq1KhbmkGYZYfTo0XBr2rSp/HgcPN9444369euHhob+9re/hXKJRTSAoEOPoqKievXqpT/ZaO7ku5h7VLY9c+ZMx44dIyIiGjVqNHHixMjISP3o7NmzH3nkEWz+7LPPis8OGo+/0PmpviZNmkAu4+Lidu7cKYw4I9atWxfa/corr8h7I4WGAyh0fk9SGj0dj34rT+3vv/8eZ+UvvvgCbQTp3bu3sPsNjfJN+bYblkx04olNmzaJM4EeaK7R6AVDhgzBKSQ1NbVChQrffvutOlzKWF6+3UL5voPqYg/sk+iktLlx40bnzp3feeedUaNGqWOlD+Wb8m077JPoxNpQvinftsM+iU6sDeWb8m077JPoxNpQvinftsM+iU6sDeWb8m077JPoxNpQvinftqN69eoaIeYnPDxcCllUVJQ6bFH0s6Z82xGHw5GRkZGenr579+6UlJRPCTEn+t9cF9ghq/lL87aW7+zs7KysLJy6U1NTkQebCTEnyF7kMDI56y52yGr9rFHLanlbEcq3i5ycHFxzZWZmIgNwDt9PiDlB9iKHkcmX7mKHrNbPGrWslrcVoXzfgfe+iTWIiorKyMjAChQqZp+s1s8aS++8vDy1wq0I5fsOmm3eoyfWBpkshcw+Wa2fNeXbdtgn0Ym1oXxTvm2HfRKdWBtksrwLbJ+s1s+a975th30SnVgbZLL8DIZ9slo/a37yxHbYJ9GJtUEmy09A2yer9bPm575tR6ASPS8v7/z586qVeEtiYqL8Nc5SZebMmWfPnv3yyy+3bt2qjgUUjV+a57cu7UagEn3cuHHY9dGjR9UBD/Ts2dNHvfj555+PHDkiu/OczJ8/f9myZTt27MjJydH5PgBKWN/xLqB292e08O/ixYsLdCkujPrfV/OaBQsW1KhR4+LFi2vWrImOjkZD9Qgclpdv/A+uWLFiw4YNN27ckEbK9x1UF3sQkETHfhs1alS+fPm3335bHfOAlCevCQ8P10fQ7iUqKmry5Mk69+KihPUd7wLK10dMZ+LEiW5HfQEX5lWrVl24cKHoxsTEjBw58l6XQKJZV75RL0OGDJG5itqBUosh/awp37YjIIm+fft27BcL6jp16uTn56vD7ihCgE6ePIkVdEpKys2bN6URV/dLliyRq3ssW7S7P1QvfndYBszOzj5w4MBf/vKXoKCgd955R0bIzc1FVaxevRrLYWksvDeyMWyhc6l7+vRpxJw1a5boKr8sLLt5eXm4pEAQ+VOTbgN6OpLr169jLQZ7VlaWnA4a9erVK1eu3LZt26Sn/tXzdDxo7Nu3b+XKlXgxxZtgiLx+/Xp5XTJt2jTIt1z64QyBlbiME3D0QhaQrC49PvzwQ8xo0qRJly9f/vrrrxs0aPCHP/xBDFG+76C62IOAJHrfvn1jY2N37typOd94EUbNifQxdt3K99SpU4ODg4VzXFycUPBhw4YJCxRZrKmR8cICIKyF7gKOGzcOFwRQLrQhnc2bNxf+kZGRe/bsET5KZGPYQmfk+Ph4OHTr1k109TuS3YsXL7Zs2VJsGxISsm7dukJ3x+npSM6dO9ekSRNp13TyDZ2tXbt2zZo1f/rpJ2WnSlvfRQPTFwFr1aold9qmTZtbt27BoUOHDjjjyg137dqFUS/u85QSmnXlu23btu3atZPdNWvWYILff/99IeVbtlQXe+D/RL969WpYWFhycjL23rhx4169egm7EAvpZuwa5RtijTNB//79oXFr166FD1ajsEdERAwdOvTKlSvz58+X92eVCMaAEEQYEafQ+aPpLVq0wCI6PT0di9knnnhC+BgjG+PAAvXEyQmLa6OD7GIXUVFRqDocPJQRK27FQeDpSAYMGFCtWrWDBw/iYEaMGCG3QmPhwoW4vsEC/MknnxTKq4/p6XjQePTRRyEBuCBAG+eGjIwMnFzRhjrAAZPCGU5uiOlj6O9//7u0BBbNuvKN0/PYsWNl9/z58/KV18+a8m07/J/oCxYswE5HjRoF1Xj66adDQ0NxSag6GVBER4IpbNq0KTExsXfv3vCBqsKIpUr9+vU/+eQT/Z0ZT7Ilyc3NhXHJkiVoN2zY8NVXX53npGvXrljgCy02RjbGgWXw4MH6rtv9PvzwwwkJCcKIXRsdBJ6OBIeBWQsfnMbkVvJFePfdd9F+88030YaUy5iejgeNGTNmoHH79m20p0+fLtvifneFChVmzpwpNxQ7XbRokbQEFs268o0aEf81An2i6mdN+bYd/k/0xx9/XLuXOXPmqE4GNINKCoYPHw5twup14MCB0gfnA9grVaoUFxcn79UqEYwB9+3bB+O//vUvtHF9cM8hatrJkycL3UU2xoFl7ty5+q7b/YaHh0+dOlXaJYq/pyNRNpdbyQb+c7t06YIuTm9VqlQpjny79ZFtLPb174hi1Y+h1atXS0tg0awr340aNXrjjTdk9/jx45ig+CCWftaUb9vh50Q/duyYIh+tWrVq3bq1zsU9ylYSCJP4/MOpU6ekj1ifpqWlwfLZZ58JT0+yJYAu47yCpa5YVrdo0WLp0qViCCtQ+S6iMbLxwBQL9HfSpEmiDSWVo5h4jx49hP3o0aNff/21aCubezqSli1bdu/eXbQPHjwot9JvjmJ+2AnmJY2ejke/ods2DhjnSGEE4tsxX331lbQEFs268v3KK6/UrVv32rVrovvOO+/gP9HhcBRSvmVLdbEHfk70t956C4tlqUFg8uTJmvMdMM2JtBu74vMYgjVr1gh7bGxss2bN3n//fTSCgoKSkpJ27doVHR2dkJAwdOhQbLVlyxbhieVqp06dxo8fL28Hi4DYVtxHBvKbL4sXL8YSe8SIEcnJyW3btq1Vq9avv/7qNrISVkTW62/79u2xORQTG8JZji5fvhztPn36YKhevXo4fnHmUAK6PRLYoenYvF+/fmPHjsWRy7DK3nFJERISojd6Oh69j9t2YmJi48aNhRF89NFHFStW1N/2CSyadeUbZ0q81DiRIweGDBkSHBwsb7vpZ035th3+THTIE4TjmWee0RvPnj0L2UU6ak6k3W1XglQWdghuTEwMFiP9+/eH6nXr1g2rkkGDBlWtWhUL8/j4eBlh9OjRcGvatKn4nJwMBc/mzZtjCZ+ZmSmdC50fpGvSpAnKJi4ubufOnYXODz4bIythCw0CeubMmY4dO0ZEROASeOLEiZGRkXJ09uzZjzzyCDZ/9tln5WcHjQGNRyLAmQ+LMmg3Vmfy9oiy90Ln9yT1Rk/Ho/dx2/7+++9x6v3iiy+EHUF69+4t2mUBzbryXej8uGqbNm1CQ0Pr1KmD1bd+rUD5/jeqiz2wXqLbnE2bNskzgQSaazR6AZZ+OIXgNJyWllahQoVvv/1W9Qgc1pZvT1C+76C62AP7JDrxnRs3bnTu3Pnw4cNYj48aNUodDiiUb8q37bBPohNrQ/mmfNsO+yQ6sTaUb8q37bBPohNrQ/mmfNsO+yQ6sTaUb8q37bBPohNrQ/mmfNsO+yQ6sTaUb8q37bBPohNrQ/mmfNuO6tWra4SYn/DwcClkUVFR6rBF0c+a8m1HHA5HRkZGenr67t27U1JSPiXEnOh/c11gh6zmL83bWr6zs7OzsrJw6k5NTUUebCbEnCB7kcPI5Ky72CGr9bNGLavlbUUo3y5ycnJwzZWZmYkMwDl8PyHmBNmLHEYmX7qLHbJaP2vUslreVoTy7SIvLw8nbfzf4+yN668ThJgTZC9yGJmcfRc7ZLV+1qhltbytCOXbRX5+Pv7Xcd7Gf7/D4ZArF0LMBbIXOYxMzruLHbJaP2vUslreVoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpoTyTQghpsSNfBNCCDERlG9CCDEllG9CCDEl/x8FFFUy9f2/VgAAAABJRU5ErkJggg==" /></p>

```cpp
    //  example/cpp_idioms/unique_ptr_ownership_ut.cpp 110

        // ステップ6
        // このブロックが終了することで、std::unique_ptrであるa3のデストラクタが呼び出される。
        // これはA{1}オブジェクトへのポインタをdeleteする。
    }                                      // a3によるA{1}の解放
    ASSERT_EQ(1, A::LastDestructedNum());  // A{1}が解放されたことの確認
```

<!-- pu:essential/plant_uml/unique_ownership_6.pu--><p><img src="data:image/png;base64,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sqWHuAPLBjkDywbLRrCZySZbeog7sGyQM7BssGwEm5lssqWHuAPLBjkDywbLRrCZySZbeog7sGyQM7BssGwEm5lssqWHuAPLBjkDywbLRrCZySZbeog7sGyQM7BssGwEm5lssqWHuENcXJxBFP6ioqLkAhobG6vvdij1qlk2go1lw+TxeDIzMzMyMvbs2ZOamvo+UXhC9iKHkcmZt7ghq9WrxlzWpzcFDsuGKTc3Nzs7G7cq6enpyL8tROEJ2YscRiZn3+KGrFavGnNZn94UOCwbpry8PDzbZmVlIfNwz7KfKDwhe5HDyOSLt7ghq9WrxlzWpzcFDsuGqbCwEDcpyDncreA59wRReEL2IoeRybm3uCGr1avGXNanNwUOy4apuLgY2Yb7FKSdx+ORd2pE4QXZixxGJhfe4oasVq8ac1mf3hQ4LBtERGQDywYREdnAskFERDawbBARkQ0sG0REZAPLBhER2cCyQURENrBsEBGRDSwbRERkA8sGERHZwLJBREQ2sGwQEZENLBtERGQDywYREdnAskFERDawbBARkQ0sG0REZAPLBhER2cCyQURENrBsEBGRDSwbRERkA8sGERHZwLJBREQ2sGwQEZENLBtERGQDywYREdngo2wQERHdFssGERHZwLJBREQ2/D/ufLX/rhjd6wAAAABJRU5ErkJggg==" /></p>


また、以下に見るようにstd::unique_ptrはcopy生成やcopy代入を許可しない。

```cpp
    //  example/cpp_idioms/unique_ptr_ownership_ut.cpp 124

    auto a0 = std::make_unique<A>(0);

    // auto a1 = a0;                            // 下記のようなメッセージでコンパイルエラー
    //      unique_ptr_ownership_ut.cpp:125:15: error: use of deleted function ‘std::unique_ptr ...

    auto a1 = std::move(a0);                    // すでに示したようにmove生成は可能
    
    auto a2 = std::unique_ptr<A>{};

    // a2 = a1;                                 // 下記のようなメッセージでコンパイルエラー
    //      unique_ptr_ownership_ut.cpp:131:10: error: use of deleted function ‘std::unique_ptr ...

    a2 = std::move(a1);                         // すでに示したようにmove代入は可能

    //
    auto x0 = X{std::make_unique<A>(0)};

    // auto x1 = x0;                            // Xはstd::unique_ptrをメンバとするため、
                                                // デフォルトのcopyコンストラクタによる生成は
                                                // コンパイルエラー
    auto x1 = std::move(x0);                    // デフォルトのmove生成は可能

    auto x2 = X{std::make_unique<A>(0)};

    // x2 = x1;                                 // Xはstd::unique_ptrをメンバとするため、
                                                // デフォルトのcopy代入子の呼び出しは
                                                // コンパイルエラー
    x2 = std::move(x1);                         // デフォルトのmove代入は可能
```

以上で示したstd::unique_ptrの仕様の要点をまとめると、以下のようになる。

* std::unique_ptrはダイナミックに生成されたオブジェクトを保持する。
* ダイナミックに生成されたオブジェクトを保持するstd::unique_ptrがスコープアウトすると、
  保持中のオブジェクトは自動的にdeleteされる。
* 保持中のオブジェクトを他のstd::unique_ptrにmoveすることはできるが、
  copyすることはできない。このため、下記に示すような不正な方法以外で、
  複数のstd::unique_ptrが1つのオブジェクトを共有することはできない。

```cpp
    //  example/cpp_idioms/unique_ptr_ownership_ut.cpp 162

    // 以下のようなコードを書いてはならない

    auto a0 = std::make_unique<A>(0);
    auto a1 = std::unique_ptr<A>{a0.get()};  // a1もa0が保持するオブジェクトを保持するが、
                                             // 保持されたオブジェクトは二重解放される

    auto a_ptr = new A{0};

    auto a2 = std::unique_ptr<A>{a_ptr};
    auto a3 = std::unique_ptr<A>{a_ptr};  // a3もa2が保持するオブジェクトを保持するが、
                                          // 保持されたオブジェクトは二重解放される
```

こういった機能によりstd::unique_ptrはオブジェクトの排他所有を実現している。

### オブジェクトの共有所有 <a id="SS_21_2_2"></a>
オブジェクトの共有所有や、それを容易に実現するための
[std::shared_ptr](https://cpprefjp.github.io/reference/memory/shared_ptr.html)
の仕様を説明するために、下記のようにクラスA、Xを定義する。

```cpp
    //  example/cpp_idioms/shared_ptr_ownership_ut.cpp 7

    class A final {
    public:
        explicit A(int32_t n) noexcept : num_{n} { last_constructed_num_ = num_; }
        ~A() { last_destructed_num_ = num_; }

        int32_t GetNum() const noexcept { return num_; }

        static int32_t LastConstructedNum() noexcept { return last_constructed_num_; }
        static int32_t LastDestructedNum() noexcept { return last_destructed_num_; }

    private:
        int32_t const  num_;
        static int32_t last_constructed_num_;
        static int32_t last_destructed_num_;
    };

    int32_t A::last_constructed_num_ = -1;
    int32_t A::last_destructed_num_  = -1;

    class X final {
    public:
        // Xオブジェクトの生成と、ptrからptr_へ所有権の移動もしくは共有
        explicit X(std::shared_ptr<A> ptr) : ptr_{std::move(ptr)} {}

        // ptrからptr_へ所有権の移動
        void Move(std::shared_ptr<A>&& ptr) noexcept { ptr_ = std::move(ptr); }

        int32_t UseCount() const noexcept { return ptr_.use_count(); }

        A const* GetA() const noexcept { return ptr_ ? ptr_.get() : nullptr; }

    private:
        std::shared_ptr<A> ptr_{};
    };
```

下記に示した上記クラスの単体テストにより、
オブジェクトの所有権やその移動、共有、
std::shared_ptr、std::move()、[rvalue](core_lang_spec.md#SS_19_7_1_2)の関係を解説する。

```cpp
    //  example/cpp_idioms/shared_ptr_ownership_ut.cpp 47

    // ステップ0
    // まだ、クラスAオブジェクトは生成されていないため、
    // A::LastConstructedNum()、A::LastDestructedNum()は初期値である-1である。
    ASSERT_EQ(-1, A::LastConstructedNum());     // まだ、A::A()は呼ばれてない
    ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない
```

```cpp
    //  example/cpp_idioms/shared_ptr_ownership_ut.cpp 56

    // ステップ1
    // a0、a1がそれぞれ初期化される。
    auto a0 = std::make_shared<A>(0);           // a0はA{0}を所有
    auto a1 = std::make_shared<A>(1);           // a1はA{1}を所有
    ASSERT_EQ(1, a0.use_count());               // A{0}の共有所有カウント数は1
    ASSERT_EQ(1, a1.use_count());               // A{1}の共有所有カウント数は1

    ASSERT_EQ(1,  A::LastConstructedNum());     // A{1}は生成された
    ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない
```

<!-- pu:essential/plant_uml/shared_ownership_1.pu--><p><img src="data:image/png;base64,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" /></p>


```cpp
    //  example/cpp_idioms/shared_ptr_ownership_ut.cpp 68

    // ステップ2
    // x0が生成され、オブジェクトA{0}がa0とx0に共同所有される。
    ASSERT_EQ(0, a0->GetNum());                 // a0はA{0}を所有
    ASSERT_EQ(1, a0.use_count());               // A{0}の共有所有カウントは1
    auto x0 = X{a0};                            // x0の生成と、a0とx0によるA{0}の共有所有
    ASSERT_EQ(2, a0.use_count());               // A{0}の共有所有カウント数は2
    ASSERT_EQ(2, x0.UseCount());
    ASSERT_EQ(x0.GetA(), a0.get());
```

<!-- pu:essential/plant_uml/shared_ownership_2.pu--><p><img src="data:image/png;base64,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DrEHh+mFfuuttyolu2DBAnWQD9/CFUaPHo1swu512LBhcgzeD9DfoEGD5ORk+V2tMoPvhF988QU6//GPf6CNzwdXnKLDkZOTU+FvZt950LNw4ULjXb/PGxcXN2vWLNkvKeMDnYnycPko2cAfbt++fXEXb29NmjQJJr79jpFtbPaNfyOKXT8OrVq1SvZElkOf+A4N41vyLl+21CH2YHKhf/3110oJ3nLLLd27dzcM8c+3cAUEk/j5h6NHj8oxYn+6b98+9KxevVqMDBRbAnIZ7yvY6optddeuXVesWCEOYQcq/xbRd2bfE1N6kL+vvvqqaCNJ5VEs/MEHHxT9Bw8e3LFjh2grDw90Jt26dXvggQdEe/fu3fJRxofjYr7eA+uSnYHOx/hAv22cMN4jRSeIfx2zfft22RNZDsY349tuTC705557DptlmUEwY8YMh+dvwBwest/3rvh5DGHNmjWiv1OnTp07d37ttdfQqFWr1rRp07Zt29a8efPx48ePHDkSj/roo4/ESGxXe/fu/dJLL8mvg8WEeKz4Hhnkv3xZtmwZtthjxoxJTU3t2bNnixYtfvzxR78zK9OKmY3X2F133YWHIzHxQAyWR99++220Bw4ciEOtW7fG+Yt3DmVCv2dS4flpBDx88ODBkydPxpnLaZVnx0eKevXqGTsDnY9xjN92SkpKu3btRCe88cYb9evXN37tE1kOxjfj227MLHTEE4LjnnvuMXYeP34csYsocXjIfr93JexJRT8Ct2PHjthRDhkyBKnXr18/l8v19NNPN23aFBvzsWPHyhkmTZqEYTfddJP4OTk5FUZ26dIFW/jc3Fw5uMLzg3QdOnRAQiUnJ2/durXC84PPvjMr01b4BOi333577733NmrUKCkpafr06fHx8fLo/Pnz27dvj4ffd9998mcHfSf0PRMB73ytWrVCdg8dOlR+PaI8e4Xn30kaOwOdj3GM3/ahQ4fw1vvJJ5+IfkwyYMAA0Y4GDsY349tuLFnodrZhwwb5TiAhc307QzBixAi8heBteN++fXXr1t27d686InIsH99+Mb4vUYfYg30KncJXXFzcp0+fr776CnvAiRMnqocjivHN+LYd+xQ6WRvjm/FtO/YpdLI2xjfj23bsU+hkbYxvxrft2KfQydoY34xv27FPoZO1Mb4Z37Zjn0Ina2N8M75txz6FTtbG+GZ8205iYqKDSH9xcXEyyBISEtTDFmVcNePbjlwul9PpzM7OzszMzMjIWEmkJ+P/c12wQ1Xz/zRv6/guLCzMy8vDW3dWVhbqYCORnlC9qGFUct5ldqhq46pxLauXtxUxvr2KiorwmSs3NxcVgPfwXUR6QvWihlHJ+ZfZoaqNq8a1rF7eVsT49nK73XjTxp893r3x+esIkZ5QvahhVHLhZXaoauOqcS2rl7cVMb69SktL8aeO92388btcLrlzIdILqhc1jEp2X2aHqjauGteyenlbEeObiEhLjG8iIi0xvomItMT4JiLSEuObiEhLjG8iIi0xvomItMT4JiLSEuObiEhLjG8iIi0xvomItMT4JiLSEuObiEhLjG8iIi0xvomItMT4JiLSEuObiEhLjG8iIi0xvomItMT4JiLSEuObiEhLjG8iIi0xvomItMT4JiLSEuObiEhLjG8iIi35iW8iItII45uISEuMbyIiLf1/efGDsCzmC2kAAAAASUVORK5CYII=" /></p>

```cpp
    //  example/cpp_idioms/shared_ptr_ownership_ut.cpp 79

    // ステップ３
    // x1が生成され、オブジェクトA{0}の所有がa0からx1へ移動する。
    auto x1 = X{std::move(a0)};                 // x1の生成と、a0からx1へA{0}の所有権の移動
    ASSERT_EQ(x1.GetA(), x1.GetA());            // x0、x1がA{0}を共有所有
    ASSERT_EQ(2, x0.UseCount());                // A{0}の共有所有カウント数は2
    ASSERT_EQ(2, x1.UseCount());
    ASSERT_FALSE(a0);                           // a0は何も所有していない
```

<!-- pu:essential/plant_uml/shared_ownership_3.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAeoAAAHACAIAAADiOLw9AABBnElEQVR4Xu3dCXhTVd4/8FCWFgql2EFZxaLCwPgHQZg6OK8iLiCCOvrggPDKqvA4IIJV3hkEQQQLgjDsoLIIiCzjMowFUUGggBZGC2VRNg1WCmJLsNAFuvy/5sDJ5WQhTdKb3Hu/n6ePz7nnntzcm/zONydpLLYyIiIyIJvaQURERsD4JiIyJFd8lxIRUcRjfBMRGRLjm4jIkBjfRESGxPgmIjIkxjcRkSExvomIDInxTURkSIxvIiJDYnwTERkS45uIyJAY30REhsT4JiIyJMY3EZEhMb6JiAyJ8U1EZEiMbyIiQ2J8ExEZEuObiMiQGN9ERIbE+CYiMiTGNxGRITG+iYgMifFNRGRIjG8iIkNifBMRGRLjm4jIkBjfgTh27Fj79u1Hjx6t7iAi0otJ4ruwsPB9jbVr1+7cuVPuzcrKetnNoUOHNAfw5Zdffjlw4MC+ffsyMzP37t2bkZGBm3fp0qVhw4bYe/Hixa1bt37xxRdFRUXqLYmIKoxJ4hsJW7t27fj4+Lp16zZq1KhWrVoNGjQoKSkRe5HUD7rZvXv3lcf4DV4G1K7S0kmTJtncxMXFpaamnj179rbbbsNmjRo1WrVqlZeXp96YiKhimCS+tbAcvvHGG1999VXZc8ALhK8c8+WXX6anpyP68UqAzb/+9a9TpkwRu3Jzc48ePWq327GKz87OPn369P/8z/8MHjwYu06cOIGV+OHDh7H0Roh/9tln8oBERBXKhPG9YMGC2NhYkcJw4cIFdeV82bvvvivGIH+rVq36/vvv33DDDcnJyehp0qRJSkqKPKYWlthYay9fvlz2rF+/fvjw4ViPI9w1A4mIKpDZ4vubb75BtooIlk5cNmHChHr16snN/Px8OebZZ5+99dZb33777SeffBKr8kqVKv373//WHMNl9uzZNWvW1K7c+/fvj2X7448/XlxcrBlIRFSBTBXfu3fvbtCgQWJiIlbfWBGru0tLn3vuuXbt2qm9Tt9///2cOXMuXryI9muvvVatWrWcnBx1UGnpvn374uPjX375ZaUf624s57/44guln4iogpgkvrHsXbhwIdbdXbp0OX/+PFbZVatWVRL866+/TkhIwC5tp6KgoADZHRUVNW7cOGXXuXPnpk+fXrt27a5du164cEF0fvTRR7fddtubb775f//3f4hv3MWVNyIiqihmiO/c3Ny2bdtWqVJl7NixYvkMycnJWIOnp6eXOpP34YcfRig/9NBDCPcrbqzx/PPP161bt3r16hMnTtT2I6z79u2L4K5VqxbSX2Z3qfPIAwcORD9uOH78eM2NiIgqlhniG2bNmrV//35tT0lJCdL8xIkTYhNr840bN2oHuFu+fPmMGTNOnTql7igtnTp1Ko7gcDjUHUREYWKS+CYishrGNxGRITG+iYgMifFNRGRIjG8iIkNifBMRGRLjm4jIkBjfRESGxPgmIjIkU8V3QkKC+jdhifyAylGLyW+sOgpMMFUnmCq+8YjIqyDyHyrH4XDk5eXl5+cXFRWV6w//suooMMFUneA6lGypQ4yDE4kCg8qx2+3Z2dk5OTmYTuX6Z0tZdRSYYKpOcB1KttQhxsGJRIFB5WRmZh4+fDgrKwtzSfvveFwVq44CE0zVCa5DyZY6xDg4kSgwqJy0tLSMjAzMJayGyvVPTrPqKDDBVJ3gOpRsqUOMgxOJAoPKSU1NxVzCagjvZ8v1l4FZdRSYYKpOcB1KttQhxsGJRIFB5axcuXLDhg3p6elYCnn8d/K8YdVRYIKpOsF1KNlShxgHJxIFJpiJxKqjwARTdYLrULKlDjGOyJlIo0aN+vLLL9Ve/wRzWz/pcBd+KioqOnXqlNqru2AmEqvOTzrchZ9MUHWC61CypQ4xDt0m0smTJ/ft26f2auBM5s2bp/b6J5jb+ingu7jqhZfX+PHjcTIHDhxQd+grmInEqvNTwHdx1QsvLxNUneA6lGypQ4xDt4kUGxvruxADrtSy4G7rp4Dv4qoX7s1///tftctZaYmJiVWqVHnxxReVXd99911eXp7SWXGCmUisOj8FfBdXvXBvTFx1gutQsqUOMY6Km0ibN29esmSJeLlevnw57uiJJ55ASf38889yzPnz59etW7dq1ars7Gz/K1V7ZEHc9uuvv162bFlqauqFCxfkriNHjrzzzjvaTow8duzYrl27Zs2aJYcVFhaiJnAmWLbIznKdHvYeOnRo06ZNK1asOHr0qOj0eOEeT0Br27Ztd91114033qjuKCvD8XHAxx57rEGDBsXFxdpd06dP/93vfjd16tT8/HxtfwUJZiKx6gRWXXkFU3WC61CypQ4xjgqaSMOGDbM5VapUacqUKU2aNBGbgAISY06cONGsWTPRGRcXZ7tcqaJHHkrZVI4sx6DsRD+0b9/+4sWL6J82bVpUVJToTEpKEnMJ7REjRuDm3bp1EzdHibdq1UoMw5ns3LmzzPvpeYMBDRs2FOOrVav27rvvotPjhdvcTkDCmM6dO2PAAw88sHv3bmUv9OnTp2XLllu3brU5v0Gl3XX27Nlx48bVrl27fv36s2fPLioq0u4NOVsQE8nGqmPVBcQWRNUJrkPJljrEOGwVM5Fq1qw5dOjQM2fOzJ8///Tp02XOx10pxP79+19zzTUoFwwbPny4HCDKTg5TNt2PLMbUqlXrww8/xBIASyFsfvLJJ5g2KLt+/fphnqxduxadWNSIwSg11KIstSFDhrRu3Rprk8zMzEaNGt1xxx1l3k/PGwzAMmTLli0Oh+Opp56Kj49HbYl+5YbuJ1DmXK898sgj2NWpU6ft27drhrtgqtSoUSMlJQVPXNOmTXv06KGOKCvLzc39xz/+gUcJcxgLQHV36NiCmEjaJzSE3GvD/cH39rQ6q4xV54Fpqk5wHUq21CHGoa3REOrYsWPjxo2xFpBvtdzrCQNGjRol2ih69wEeuR+5zHnwCRMmiDZWQNhcuHBhmfN5Wb9+Pe6lZ8+e6MTcE4MHDx4sbws33HDDwIED5zk9+OCDWDqhxMt7ehiAEhftH3/8EZsoMtHvPpGUEyhzvuHFyqhFixZ4M67skhYsWIDbjhkzBge8++67o6OjMW3UQWVlv/76K9ZZGPmnP/1J3Rc6wUwkVl0Zqy4gwVSd4DqUbKlDjKOCJhKe4GeffbZ69ep481hQUFDmqZ5iY2PxNlNuug/wyP3IZW63lZsYWbly5XvuuWfQoEGyE425c+fKwYDFhe1KWJWU9/S0A86dO4dNrMiUfjlSOQEBUwjTGNPp4Ycf9vgbpNtvv/2Ks7TZ5syZox2AKTRx4kQs37Caw51qP40NOVsQE8nGqmPVBcQWRNUJrkPJljrEOGwVM5HEG7S9e/fi+KtXry7zVE9t2rTp3r27aOPdovsAj9yPXOZ2cLlZu3bt0aNHo3H06FHZ6X5HeA+7dOlS0S4pKRG/7Snv6WHAc889J9qpqanYFN/Ydb+he4/Wzp078U4WY/r27avtP3jwoHLDtm3btmvXTm5u3LgRU+i6666bPn16YWGh7K8gtiAmko1Vx6oLiC2IqhNch5ItdYhx2CpgIm3btq1u3brJyclDhw61OT8QLHOuejp37vzKK6+IX+8AaleUy7hx41AB2kLXnpV20+ORxRiPE6lly5a33HLL66+/jgbWF1gjuA+GxYsXY2E1fPhwvA/t0KFDvXr1sKDwdnre2Jy/13r66adfe+01HOGPf/xjqbNW3C/8qocqc37P4cknn9T2vPDCC1jTab9BMWXKFBxKfr0XJzxp0iQsweSACmULYiJpn99Q8Vgb7g++t6f1tyJj1Zm66gTXoWRLHWIc2pINFYfDgXqqU6cOliEjRowQnWPHjsW7xebNm+/fv1+ORCk0bNgQZTpgwAAMvupE8nhkMcbjRMJKpEWLFrjffv36oZrF79w91jF6mjVrFhMTg3fHW7duFZ0eT88bHBZ3kZiYWLNmza5du/7444+i3/3CPZ6Ab8XFxZic9957r7bz+PHjmLqIFW2nboKZSKw6gVVXXsFUneA6lGypQ4yjIiaSuc1zI94CBzA9DC2YicSqKy+15lh15a86wXUo2VKHGAcnUnk5l2VXuO6660Q/J5KfbKy6clJKzsaqK3/VCa5DyZY6xDhsnEghMnjwYPn+1wqCmUisulBh1am1dTWuQ8mWOsQ4OJEoMMFMJFYdBSaYqhNch5ItdYhxcCL5Y//+/cuXL1+3bp38zi8FM5FYdf7Izc1dunSp9peuFEzVCa5DyZY6xDg4kXzDQzRkyBDbZYmJiSgadZAlBTORWHW+YaHQtWvXmJgYm8U+2r6qYKpOcB1KttQhxsGJpOX+h+LefPNNPESTJ0/GUmjHjh1NmjS58847r7yRRQUzkVh1Wu5Vh0V37969J0yYwPhWBFN1gutQsqUOMQ5OJMnjH4rr0KFDx44d5Zg1a9Zg77fffuu6mVUFM5FYdZLHqhPwqDK+FcFUneA6lGypQ4yDE0nw9ofi4uLixo0bJ4edOnUKuz744APXLa0qmInEqhO8VZ3A+HYXTNUJrkPJljrEODiRpFJPfyguOjp6xowZckxhYSF2LVmyxHUzqwpmIrHqpFJPVScwvt0FU3WC61CypQ4xDk4kyeMfiktMTBw5cqQcc+jQIezauHGj62ZWFcxEYtVJHqtOYHy7C6bqBNehZEsdYhycSJLHPxQ3YMCAhg0byr/I89JLL9WoUcPhcGhvaE3BTCRWneSx6gTGt7tgqk5wHUq21CHGwYkkefxDcZmZmTExMa1bt05JSRkyZEhUVFS4/lhPpAlmIrHqJI9VJzC+3QVTdYLrULKlDjEOTiTJ4x+KK3P+Fc327dtHR0c3aNAAq2/5FzgtLpiJxKqTvFVdGePbk2CqTnAdSrbUIcbBiUSBCWYiseooMMFUneA6lGypQ4yDE4kCE8xEYtVRYIKpOsF1KNlShxgHJxIFJpiJxKqjwARTdYLrULKlDjEOTiQKTDATiVVHgQmm6gTXoWRLHWIcnEgUmGAmEquOAhNM1QmuQ8mWOsQ4OJEoMMFMJFYdBSaYqhNch5ItdYhxcCJRYIKZSKw6CkwwVSe4DiVb6hDj4ESiwAQzkVh1FJhgqk5wHUq21CHGwYlEgQlmIrHqKDDBVJ3gOpRsqUOMIyEhwUZUfrGxsQFPJFYdBSaYqhNMFd/gcDjsdntmZmZaWlpqaupKC7M5X9vJT6gW1AwqB/WDKlILyydWncSqK5dgqq7UfPGdl5eXnZ2Nl7KMjAw8LhssDBNJ7SLvUC2oGVQO6gdVpBaWT6w6iVVXLsFUXan54js/Px/vQbKysvCI4DUt3cIwkdQu8g7VgppB5aB+UEVqYfnEqpNYdeUSTNWVmi++i4qK8CKGxwKvZng/ctjCMJHULvIO1YKaQeWgflBFamH5xKqTWHXlEkzVlZovvouLi/Eo4HUMD4fD4cixMEwktYu8Q7WgZlA5qB9UkVpYPrHqJFZduQRTdaXmi2+SMJHULqIKxqrTE+PbtDiRSH+sOj0xvk2LE4n0x6rTE+PbtDiRSH+sOj0xvk2LE4n0x6rTE+PbtDiRSH+sOj0xvk2LE4n0x6rTE+PbtDiRSH+sOj0xvk2LE4n0x6rTE+PbtDiRSH+sOj0xvk2LE4n0x6rTE+PbtDiRSH+sOj0xvk2LE4n0x6rTE+PbtDiRSH+sOj0xvk2LE4n0x6rTE+PbPFq1amXzArvU0UShwKoLI8a3eaSkpKgT6DLsUkcThQKrLowY3+Zht9ujoqLUOWSzoRO71NFEocCqCyPGt6l07NhRnUY2GzrVcUShw6oLF8a3qSxcuFCdRjYbOtVxRKHDqgsXxrep5ObmRkdHa2cRNtGpjiMKHVZduDC+zebRRx/VTiRsqiOIQo1VFxaMb7NZu3atdiJhUx1BFGqsurBgfJtNQUFBnTp1xCxCA5vqCKJQY9WFBePbhAYNGiQmEhrqPqKKwarTH+PbhDZt2iQmEhrqPqKKwarTH+PbhEpKSho7oaHuI6oYrDr9Mb7NaZST2ktUkVh1OmN8m9MeJ7WXqCKx6nTG+CYiMiTGN/nlwoUL8jNNbZuIwoXxTX6x2Wxz5851b/uQnZ2dmZmp9hJRiDC+yS8BxHdsbKw/w4goMIxvK0KqHj58+L///e8777zz8ccfFxUVyf59+/Zph8lNH/GN9nfffff5558vX778yJEjonPZsmUY9sQTT2DvqVOnxLCjR4+mp6fPnDlT3paIAsb4tiIEa8uWLcX/ZAHt27e/cOGC6NfmsrfIdh/WsGFDcahq1aqtWLECnU2aNJHHR2SLYSNGjKhUqVK3bt3kbYkoYIxvK0KS1qpV68MPPzx//jwW4NjcsGGD6A8svn/3u9998cUXZ86ceeqpp+Lj43/55RePw+rXr79ly5bCwkLZSUQBY3xbEZL0lVdeEW2su7G5YMEC0R9YfL/22muiffz4cWyuX7/e47DBgwfLTTKl2PhYm7kkJCSoFxkxGN9WZHMLVrHprd9HW9nMy8vDJlb0HofNmTNHbpIp4VlecHSBmX5wRQ6HA4Wdn59fVFRUXFysXnP4ML6tyD1YxWaNGjXkvw6emprqLbLdb/7cc8+J9scff4zNnTt3ehym3SRTMmV82+327OzsnJwchLj8PX8kYHxbkbdg7dSpU7169ZDgycnJsbG/vQv2GNnuN69UqdLTTz89adIk3PyPf/yj+J96cITOnTuPHz/e4+9FyZRMGd+ZmZmHDx/OyspCgmMNrl5z+DC+rcg9f8XmsWPH7r///po1ayYmJk6cODEuLs5jZLvfHDGNm+CGXbt2PX78uOgfO3YslvPNmzcX3z5kfFuBKeM7LS0tIyMDCY41OBbg6jWHD+ObgsVcJsmU8Z2amooExxrcbrc7HA71msOH8U3BYnyTZMr4Xrly5YYNG9LT07EAz8nJUa85fBjfFKzBgwdv2bJF7SVLYnzrifFNRCET2vie8+2cqelT3fvnH54/M3Ome7+81ez9s937A/thfBORJYQ2vrs/1x0HHPfJOG1nj3/0qFKtStM2TWXP9K+n95/aXw5DO6pyFAb4iHj/fxjfRGQJIYzv+Ufm/67x7xDEnZ/urO2vEVej8+BLPX9782+3dLylanRV3G/vCb3lmElbJqHnqZlPuR+2vD+MbyKyhBDG98gVI3G0tl3axl8XP+/QPNmvTWostJMeTnp45MNKfCvDgvlhfBORJYQwvpMeSap/U/3k95JxzGGLhsl+91yesGmCe6d7T2A/jG8isoRQxfc/9/yzWvVqj774qPgI5baut4n+Wftm4S6w6NYO9hjfVWOq9vhHD/cjl/eH8U1h8PLLL6tdRBUsVPHdZ2IfHOrBoQ8ilJvf3rxKtSrTv56O/jt73VkjrsakrZO0gz3Gd9LDSfHXxU/eMdn94OX6YXxTGKDs1C6iChaq+G7apqntSr3G90L/QyMeqlyl8tjUsdrBHuMbod/o943e+O8b7gcv14+N8U36szG+SXe2UMT3+I3jlTi+/g/XN/l/TdCY+91c7Hoy5UnteI/xjZTv+XJPbU9gP4xvCgPGN+kvJPF9/1P3R1WOmrrL9T/sPPZ/j+HIL294eYGn30l6jG/3nsB+GN8UBoxv0l/w8T3v0Ly4unEt7mih7UxJS6lUqRJifYGnXGZ8M77Nhr+6JP0FH99X/YmNj737ybvnHJzjvkv84AVgzMdjcCaDZw9231veH8Y3EVmCDvHd+9XeNeJqNLnlt4/CPf70ndI3qnJUiz+3mH0gBH/5hPFNRJagQ3yLH+3/h6n8zD8yHz/u/YH9ML6JyBJ0i2/dfhjfRGQJjG89Mb5Ni7+6JP0xvvXE+DYtG784SLpjfOuJ8W1ajG/SH+NbT4xv02J8k/4Y33pifJsW45v0x/jWE+PbtPirS9If41tPjG8iChnGt54Y30QUMoxvPTG+iShkGN96YnwTUcgwvvXE+DYt/uqS9Mf41hPj27T4xUHSH+NbT4xv02J8k/4Y33pifJsW45v0x/jWE+PbtBjfpD/Gt54Y36bFX12S/hjfemJ8E1HIML71xPgmopBhfOuJ8U1EIZOQkGAzl9jYWMY3EVmCw+Gw2+2ZmZlpaWmpqakrjQ9XgWvBFeG6cHXqBYcP49u0+KtLCou8vLzs7GwsVDMyMpB6G4wPV4FrwRXhunB16gWHD+PbtGz84iCFQ35+fk5OTlZWFvIOK9Z048NV4FpwRbguXJ16weHD+DYtxjeFRVFREZaoSDqsVe12+2Hjw1XgWnBFuC5cnXrB4cP4Ni3GN4VFcXExMg6rVISdw+HIMT5cBa4FV4TrwtWpFxw+jG/TYnwTmRvj27T4q0sic2N8ExEZEuObiMiQGN9ERIbE+CYiMiTGt2nxV5dE5sb4Ni1+cZDI3BjfpsX4JjI3xrdpMb6JzI3xbVqMbyJzY3ybFn91SWRujG8iIkNifBMRGRLjm4jIkBjfRESGxPg2Lf7q8qqKi4t//fVXtdcPo0aN2rlzp9obVv/85z/tdrva69OmTZs++eQTuVlYWHj+/HnNfop0jG/TMtwXB3NycpYsWbJv3z51R/l9+umnc+fOPXr0qOwpKipasGDB4sWLS0pKRM/UqVOjo6P/9Kc/yTFSdnZ2Zmam2quBxxbHV3vDZ/78+ddee+3PP/+s7rgSHttly5b9+9//Fv9g4+rVq+vWrStvtXTp0sqVK+MBCewljfTH+DYtA8U3AqVr164xMTGhikXkVI0aNdq1a3fhwgXR8/e//x0HR8zJMfHx8VhEy02t2NhY36cRqvMMiTNnztSpUwcvTuoODbxoDRkyxHZZYmLioUOH0N+iRYvRo0fLYceOHcPelStXum5JEYzxbVqRGd+rVq16++23xRL47NmzCMG0tDQsunv37v3KK6+EMBbffPNNHG3s2LFo4y6wruzVq5d2gPa+Nm3ahIX5/v370cb6FLueeOIJ7D116pQcf+7cObzMvPfeeydOnPDzPDHmyy+/XL58ORa2uBVWtbj5hx9+qHxGUVhYiLcL2JWVlSV6Fi5cmJqaKgfg5v/5z3/QKCgoWL9+PUbi/YHcO23aNMS3/BfQDx8+jPEff/yx9h/VxQFxzikpKXiLs3379iZNmtx5553onzhxIpbtclhphL0ykW+Mb9OKzPhGluHEkCZoDxs2DOtcxI3YhfXgVbMD7/fvuhJyVh10GV4SqlSpgmRs2rRps2bN8Gqh3SvvC6fhXJLaKlWqNHnyZESb2IT09HQx+KeffsIRRGdcXJy8rejRHlPZxAmIznr16rVq1Uq027dvL98WnD59Gu8SRD8ejX/961/ofOihhxISEkT+iofljTfewGuJPALOYceOHeII99xzz2OPPSbaU6dOjYqKEmOSkpJkgnfo0KFjx46iXep8GDHg4MGDW7duRUP7SZHtak8BRQ7Gt2lF7K8uH3nkkWuuuWbdunUImpkzZ8p+f+J78+bNw680YcIEddBlWO3efPPNWHfHxMR888032l1YSuO+sOpHu2bNmkOHDs3NzZ03b574INj9NPr3749z3rVrF4bhTuUAEZRymPvmTTfdhOv65JNP0MYLwA8//IB1MdpYRIsxzzzzDLIY7w+Q4927d0dqnzlz5qOPPsIYseLGm5Lo6GjsHTJkSOvWrY8ePbp3795GjRrdcccd4gj169cfN25cqfPz/T59+vTr1w9Bv2bNGhwBbxfEGNyFth5OnjyJve+//z6uVzTkrurVq+M1QG5SJGN8k97wxh8hhezG2ln+IrHUv/hGiu290nfffacO0kAu45i33nrrxYsXtf2DBw+Oj4///vvv0caytHHjxitWrJBj3E8DA+QH5UhJ9wEeYdj06dNLnV9xsTlX0LItP6q+/vrrk5OTRVs8Akh2nEnDhg3x7gGdf/jDH3r27InGDTfcMHDgwLlODz74IB7AwsJC9FetWvWf//ynOAIez9TUVJwqboJD4QVJ9OMFQJyJUFBQgL2LFy8W1/LWW2/JXbhT3PWPP/4oeyhiMb4pDO677z6kxquvvqrt9Ce+kYC2K914443qoMuQg5UqVerUqROG/f3vf9fuGj9+PFJvz549pc5vvDz77LNYdSYlJYlPkN1PIzY2VrsmdR/gkXaYt7b2yHl5edj1zjvvoD169Gi8Lfjqq6/Q8+mnn6KnRo0arst2Ep874W3BxIkTxRFwIXi3cc899wwaNEh7L4mJiSNHjhRtwGse9uI9Ad5MoPHee+/JXXfffXerVq3wMil7KGIxvklvWPQhMvDeH4mpXTv7E994159+JSzA1UFOP/30U926ddu0aYMFZt++fZHj8vOK0ssraLHqFGtYRDl6Vq1aVeopnXGc7t27i/auXbvcB3ikHeatjXcGf/nLX0RbfK4ivlF+9OhRnHP79u2bNm0q3qO0bt1afNpT6lzCy1+rtm3bFmEt2rVr1xbfJDly5Ij2XgYMGIA1NV4exOZLL72EF4MzZ87g0cOwtLQ00V965VqeIhzjm3Rlt9sRMb169XI4HA0aNECII4nELn/i2084ZseOHaOjo8Uv5c6ePYsQRJrLr3aUXs7QrVu3oj85OVl8zLJhw4ZS54q4c+fOWKHLXzAiN7EXLwMvv/wyVrvyPG1O2mMqmx4jW9t+++23sdm/f3+8F7n22ms7dOggP1C69957bZr3KIsWLcIL3vDhw1977TUMq1evnvhl7KhRo3B1YkzLli1vueWWKVOmoIH0l7dFTMfExOAFALcdMmRIVFSU+MTmzTffRH9BQYEYVurppYsiFuPbtCLwV5cIJkRSfHy8+N7bv/71L4SF/OgghPE9duxYHAopJnvEdwfvuusu5QNurECffvrpOnXq4EVlxIgR8uZYnDZv3lz7/xBNnjwZC1hkN1ayGByq+Ibp06cjf/Gw9OjRQ/tVxffeew/nrH3Jwa2aNWuGwE1KStqyZYvoPHjwIIaJD1iwcm/RogVOvl+/fngF6tatm7ztpk2bsJbHSxpeNbH6Fq9M999/v/hgXQrVU0A6YHybljZHyB2CeNiwYdqFp3FhQY1AV349e1V79uypWrXq119/LTZx84yMDJTN6tWrrxxIEYrxbVqMb9/mzZuHBe9tt92m7jCg/Pz8Ll26IHzVHT5hlT1mzBi5uWjRoipVqtx3333y/wCiCMf4Ni3Gtz/Ku2I1sRIntZciGOPbtBjfRObG+DatCPzVJRGFEOObiMiQGN9ERIbE+CYiMiTGNxGRIZkqvhMSEsT/9mYauCL1Iv3GX13qg1VH4WKq+EblyaswB1yRw+HIy8vLz88vKiqSfx7EHzZ+cVAXrDoKF9dTJlvqEOMw5USy2+3Z2dk5OTmYTtp//uqqGN/6YNVRuLieMtlShxiHKSdSZmbm4cOHs7KyMJfK9X8zM771waqjcHE9ZbKlDjEOU06ktLS0jIwMzCWshuTfa/YH41sfrDoKF9dTJlvqEOMw5URKTU3FXMJqCO9nHQ6Hes3e8VeX+mDVUbi4njLZUocYhykn0sqVKzds2JCeno6lEN7JqtdM4caqo3BxPWWypQ4xDk4k0h+rjsLF9ZTJljrEODiRSH+sOgoX11MmW+oQ49B5Iu3fv3/58uXr1q0rKChQ94UIJ1Lk07nqcnNzly5ditpTd4QOq84oXE+ZbKlDjEO3iVTq/OepbJclJiaiytVBoRDMROKvLvWhW9VhodC1a9eYmBjc47x589TdoRNM1ZGeXE+ZbKlDjKMiJtLq1asXLVpU6nykfv31V0yb7du3v/nmm7ivyZMnYym0Y8eOJk2a3HnnneotQyGYiWTjFwd1oVvVYdHdu3fvCRMmML5JcD1lsqUOMY6KmEgrVqzAYZHXaA8bNiw2NvbIkSMdOnTo2LGjHLNmzRqM+fbbb103C5FgJhLjWx+6VZ3YhTJgfJPgespkSx1iHBUxkeCRRx655ppr/vOf/0RFRc2aNQs9cXFx48aNkwNOnTqFu/7ggw9ctwmRYCYS41sfulWdwPgmyfWUyZY6xDgqaCKdPHkyISEBs+iuu+4qdT5k0dHRM2bMkAMKCwtx10uWLHHdJkSCmUiMb33oVnUC45sk11MmW+oQ46igiQT33XcfDj5x4kSxmZiYOHLkSLn30KFD2Ltx40bZEyrBTCT+6lIfulWdwPgmyfWUyZY6xDgqaCJhWY0j33HHHdWrV0dSo2fAgAENGzY8d+6cGPDSSy/VqFHD4XBccbNQ4ESKfLpVncD4Jsn1lMmWOsQ4KmIiHT9+vHbt2r169Tp79myDBg0wnUpKSjIzM2NiYlq3bp2SkjJkyBC8w01OTlZvGQqcSJFPt6oTuxjfJLmeMtlShxhHyCcSjnnvvffGx8efPHkSm++//z7uYtq0aWhv3ry5ffv20dHRmF1YfV+8eFG9cShwIkU+PauujPFNGq6nTLbUIcYR8okUdpxIkY9VR+HiespkSx1iHJxIWvzVpT5YdRQurqdMttQhxsGJpGXjFwd1waqjcHE9ZbKlDjEOTiQtxrc+WHUULq6nTLbUIcbBiaTF+NYHq47CxfWUyZY6xDg4kbQY3/pg1VG4uJ4y2VKHGAcnkhZ/dakPVh2Fi+spky11iHFwIpH+WHUULq6nTLbUIcbBiUT6Y9VRuLieMtlShxhHQkKCzVxiY2M5kSIcq47CxVTxDQ6Hw263Z2ZmpqWlpaamrgwRm3M9Eha4ClwLrgjXhatTL5giAKuOwsJs8Z2Xl5ednY0lQ0ZGBupvQ4hgIqldesFV4FpwRbguXJ16wd7xV5e6YdVRWJgtvvPz8/FeLysrC5WHtUN6iGAiqV16wVXgWnBFuC5cnXrB3tn4xUG9sOooLMwW30VFRVgsoOawasD7vsMhgomkdukFV4FrwRXhunB16gV7x/jWDauOwsJs8V1cXIxqw3oBZedwOHJCBBNJ7dILrgLXgivCdeHq1Av2jvGtG1YdhYXZ4ruCGDEKjXjOpMVnkHxjfPvFiBOJv7o0OiNWHemJ8e0XTiTSH6uOfGN8+4UTifTHqiPfGN9+4UQi/bHqyDfGt184kUh/rDryjfHtFyNOJP7q0uiMWHWkJ8a3X4w4kYx4zqTFZ5B8Y3z7xYgTyYjnTFp8Bsk3xrdfjDiRjHjOpMVnkHxjfPvFiBPJiOdMWnwGyTfGt1+MOJH4q0ujM2LVkZ4Y337hRCL9serIN8a3XziRSH+sOvKN8e0XTiTSH6uOfGN8e9aqVSubF9iljo4MRjxn8sHG+CafGN+epaSkqBF4GXapoyODEc+ZfLAxvsknxrdndrs9KipKTUGbDZ3YpY6ODEY8Z/LBxvgmnxjfXnXs2FENQpsNneq4SGLEcyZvbIxv8onx7dXChQvVILTZ0KmOiyRGPGfyxsb4Jp8Y317l5uZGR0drcxCb6FTHRRIjnjN5Y2N8k0+Mb18effRRbRRiUx0ReYx4zuSRjfFNPjG+fVm7dq02CrGpjog8Rjxn8sjG+CafGN++FBQU1KlTR+QgGthUR0QeI54zecT4Jt8Y31cxaNAgEYVoqPsilRHPmdwxvsk3xvdVbNq0SUQhGuq+SGXEcyZ3jG/yjfF9FSUlJY2d0FD3RSojnjO5Y3yTb4zvqxvlpPZGNiOeMykY3+Qb4/vq9jipvZHNiOdMCsY3+cb4Jl9yc3N79eql9pIuGN/kG+ObvPr8888bN27MEAkXPvLkG+ObPCgoKHj++efl3y9Ud5Mu+MiTb4xvUu3Zs0f5lx/UEaQLPvLkG+ObXEpKSqZOnar80SuGSLjwkSffGN90id1u79SpkxLcgjqUdMFHnnxjfNNvVqxYER8fr8b2Zepo0gUfefKN8e2XatXi1EgzuISEBO0F+o5vCgvlOSJSML79grnUo8enZvrBFTkcjry8vPz8/KKiouLiYn54QmQsjG+/2MwY38jr7OzsnJwchDgSvJS/uiQyFMa3X0wZ35mZmYcPH87KykKCYw0uL5ZfHCQyBMa3X0wZ32lpaRkZGUhwrMGxANdeL/+3HaLIx/j2iynjOzU1FQmONbjdbnc4HOo183+aJ4psjG+/mDK+V65cuWHDhvT0dCzAc3Jy1Gt24p+sIopYjG+/WDa+iShiMb79Etr47tXr80GDtrj3P/74Z//7v5vc++Wtevf+3L0/sB/GN5HRMb79Etr4XrXqKB7n557boe1cuvS7CxdKvvvOIXtGjNgxc2ZmSso3TzzxW2rPmrWvpKQUA3xEvP8/jG8io2N8+yWE8f3445+eOpVfXFz64Yc/aPvPnbv44YffyzEbN/4onxGMHzZsO/qfeSYNm9On73U/bHl/GN9ERicjgvHtSwjje9y43XiQv/zyVG5u4V//+pnsR+fChQdFe/78A9hcvvxQv35fjB6d/vPPBQcO5LoPC+aH8U1kdDK0Gd++hDC+t2498eOP58aO3YWHetKkr2W/Npe//daxb9+lvMbPtGl7sHf48N8W4NphwfwwvomMToY249uXUMX3k09uLiwsXr788OOPf3ryZP6OHSdFf58+m/DIz569T2zm519cvfqovNWgQVuwd8qUDLSLikqWLv3O/cjl/WF8Exkd49svoYrvBQt++1Rk7dpjWEFjfX3hQkm/fl+gf+PGrHPnLj7zzDYxDP2LF7sy+oknPi+7HO5bt2bn5BQOHrzV/eDl+mF8Exkd49svoYrvQ4cc8nEW3nrrt09C3nvvSHFx6fPP7xTDTp3KX7fOLm/17LPbMXLChP+ijdD/4Ye8AQN+C/1gfhjfREYnY4Tx7UtI4vu553aUXfnJ9bFjvx45chaNnj0/w665c/eL/k2bfsISu0+fS18QxGq9sLC4b9/NaCPlFy361v3g5f1hfBMZHePbLyGJ748++qGkpHTgQNf/sLNs2SE84CNH/vYF8DJNso8cufPChZIffvh1+fLDGzf+iBP4978vfctQOyyYH8Y3kdHJ0GZ8+xJ8fP/1r5+dOVO0d2+OtnPIkG14CkQ0K7k8btxuLMwR4rm5hVh9Y3ku+hnfRCQwvv0SfHxf9Scv70Jq6nHxP1h6/MELQHLyTjxB06btcd9b3h/GN5HRMb79okN8L1x44Ny5i0eP/vZRuMefOXP2FxeX7tmT4yPi/f9hfBMZHePbLzrEt/jR/n+Yys/jj//2494f2A/jm8joGN9+0S2+dfthfBMZHePbL4xvIoo0jG+/ML6JKNIwvv3C+CaiSMP49gvjm4giDePbL4xvIoo0jG+/ML6JKNIwvv3C+CaiSMP49gvjm4giDePbL4xvIoo0jG+/ML6JKNIwvv3C+CaiSMP49gvjm4giDePbL4xvIoo0jG+/ML6JKNIwvv3C+CaiSMP49gvjm4giDePbL4xvIoo0jG+/ML6JKNIwvv3C+CaiSMP49ktCQoLNXGJjYxnfRIbG+PaXw+Gw2+2ZmZlpaWmpqakrjQ9XgWvBFeG6cHXqBRNRZGN8+ysvLy87OxsL1YyMDKTeBuPDVeBacEW4LlydesFEFNkY3/7Kz8/PycnJyspC3mHFmm58uApcC64I14WrUy+YiCIb49tfRUVFWKIi6bBWtdvth40PV4FrwRXhunB16gUTUWRjfPuruLgYGYdVKsLO4XDkGB+uAteCK8J14erUCyaiyMb4JiIyJMY3EZEhMb6JiAyJ8U1EZEiMbyIiQ2J8ExEZEuObiMiQGN9ERIZkqvh++eWXtX9UD5vcy73cy72+9xqXqeKbiMg6GN9ERIbE+CYiMiTGNxGRITG+iYgMifFNRGRIjG8iIkNifBMRGRLjm4jIkBjfRESGxPgmIjIkxjcRkSExvomIDInxfUlCQoL2b5IRGRQq2YJVrb1q62B8X4IKkI8AkXGhkh0OR15eXn5+vnWqWnvVRUVFxcXF6gw3I9fly5Y6xBqsU+hkbqhku92enZ2dk5NjnarWXjVCHAmuznAzcl2+bKlDrME6hU7mhkrOzMw8fPhwVlaWdapae9VIcKzB1RluRq7Lly11iDVYp9DJ3FDJaWlpGRkZyDLrVLX2qrEGxwJcneFm5Lp82VKHWIN1Cp3MDZWcmpqKLMNq1DpVrb1qu93ucDjUGW5GrsuXLXWINVin0MncUMkrV67csGFDenq6dapae9VYgOfk5Kgz3Ixcly9b6hBrsE6hk7kxvhnflhPGQi8qKjp16pTaS6E2atSoL7/8Uu2tGDNnzly1atXGjRvVHRWP8c34tpwwFvr48eNx7wcOHFB3ePHYY48FmQsnT57ct2+f0nn+/PnU1NRFixZ9/PHHeXl5yt4gebzHgAV2NDzI8+bNE200Fi9eXKqZAKJz//792p7ALFiw4Nprr8UjWbdu3dOnT6u7K5jp4zs3N3fp0qXKM8X4vkQdYg3hKnTcdWJiYpUqVV588UV1nxfaGApMbGyscgRENhLHdlnNmjWRbtoBQXK/x2AEdjTt4yYuc9KkSd4GBMzhcNSpU2fhwoVot2jRYvTo0eqICqYNsnBVdQVZt25d165dY2Ji3J8p7VUzvi0nXIW+adMm3DUW1A0aNCguLlZ3e+Jeu9KRI0feeecdLKIvXLggOzdv3rxkyRK5ul++fDmO8MQTT+AgP//8M3q++eab6OjoLl267N27F+vu3bt3d+7c+Y477sAyp8z52c5nn322atWqn376SR6zzLlWxd19/fXXy5YtK+89onHs2LFdu3bNmjVLbGoXU8omTgDvNnCQ48ePl3k6mlBYWIjZi/PE2lx24i0F5jw6s7Ozlfhu1KhR5cqVP//8czlYDvB2Pmh89dVXK1aswIMsvp2GI3/00Uf5+fly8BtvvIH4LigoQBsvD3hRlLv0YeL4xqK7d+/eEyZMcJ8CjO9L1CHWEK5C79OnT8uWLbdu3WpzfvNJdNqc5Bj3TY/xPW3atKioKDE4KSlJ5OmwYcNET6VKlaZMmYKeJk2aiB5AgKLn0Ucfbdq0qUgcxS+//NKuXTsxGGve999/X+5CD85cHqp9+/YXL14s8+8e0RgxYgQGdOvWTWxqr0i7efr06TZt2ojbVqtWDSfgfjRAjrdq1Up0xsXF7dy5E50nTpxo1qyZ7LRdGd/I2fr161933XXyZUkO0I5U+vE+SRywXr168h7ltcM999yDF2PR3rZtG/YG8DlPMGzmjW9BfJ+d8V3K+JbCUuhnz56tUaNGSkoKTgAB2qNHD9EvQkEOc990j2+ENV4J+vXrhyBbu3YtxmDVif6aNWsOHTr0zJkz8+fPl5/DKkdISEjw9tHNM888g+Dbvn07crx79+4Y6XA4xC4cpFatWmLtiQU4Nj/55JMy/+4Rm4hOvGhhZe1xr9wcMmRIfHw85iSuC8mIRbf7eDGsdevWWNFnZmZiWY23Dujs37//NddcgzcTOJnhw4drb4X2woUL8dYHC/A///nPInzlAG/ng8ZNN92EdMC7AbTx2mC32/GiizaCQwzGdY0fP160cfnY9cEHH8hD6cDG+GZ8W01YCn3BggW43zFjxqAW77777ujoaPF5hW/utSvgKtavXz9q1KiePXtiDNITnR07dmzcuPG7776r/WRGOULVqlWxcpebWtdff31ycrJoi2kjcwptvI0VbcSfzRmIZf7dIzYHDx7sY6/c1J5AYWGh+wDhhhtuGDhw4DynBx98EO9C8MKA08CjIQbg5U17K/n4vPrqq2g///zzaCPKrxrfM2bMQKOkpATt6dOny7a49jLngzlz5kzRFnf69ttvXzqQLmyMb8a31YSl0G+//XbblebMmaMOcuNeu8Kzzz6LAMISddCgQXIMXg/QX7169aSkJPnxiHIELPyRfXKzzFkDInxjY2Nlsp87dw43xEJbbCoHKdc9YnPu3LnaTY+HKrvyBCT3RwBvYi49gpcdOXJEua32VrKNK+3atSs28cpXu3btq8a3+xGUNtb78jeiWPVj16pVq8SmPmyMb8a31ehf6AcPHlSqsG3btu3atdMM8cy9dgWkj/iew9GjR+UY8enE3r170bN69WoxUjnCCy+8UK1aNYyRPVOmTLn55puzsrJuvfXWv/zlL6JTfEogvzqtHKRc96hsInwnT54s2ohR7V48Jg899JBoHzhwYMeOHWVuN4fWrVsvXbpUtLEcFr/SbNOmTffu3UXn7t27tbfStjHVr3fCEl50ejsfb0dQThgvn6It/rf17du3i0192BjfjG+r0b/QEZpYLGu/O4HQtDl/02Vzkv3um+J7F8KaNWtEf8uWLW+55ZbXX38djUqVKk2cOHHbtm1169ZNTk4eOnSo7fJn02XOJW3nzp1feeUV8Znv2bNnccNatWqNGDFixowZjz/+OAaL4Fu0aBHa/fv3x9GuvfbaDh06lF4uGmUKiU0/71G5badOnerVq4fExA0xUrtXfKreu3dv7G3UqBEuDW8LlKPB4sWLsd4fPnx4SkoKThJH+/XXXxHouG3fvn3HjRuHRbH2sMoJfPXVV3gBk53ezsfbEbTtUaNG4d2MaL/11lsxMTHyMx992BjfjG+r0bnQkUEIiHvvvVfbefz4ccQuIsPmJPs9bkpYeIp+rItbtGiBlWO/fv2Qbt26dXM4HE8//XSdOnWwMEc0yyOMHTsWw5o3by6/HoeRI0eObNy4cXR09O9//3skl1hEAwIdeRQfH9+jRw/ti43NU3z7eY/Kbb///vv777+/Zs2aiYmJkyZNiouL0+6dPXv2jTfeiJs/8MAD4ruD7udf5vxWX7NmzRCXSUlJW7duFZ14RWzYsCGye8CAAfKzkTK3Eyhz/n+SstPb+Whv5a397bff4lX5s88+QxsH6dmzp+jXjY3xzfi2GlMWOnmzfv168Uqghcx17wzAkCFD8BKSkZFRtWrVb775Rt1dwUwf3x4xvi9Rh1iDdQqdKlpBQUGXLl1eeumlMWPGqPsqHuOb8W051il0MjfGN+PbcqxT6GRujG/Gt+VYp9DJ3BjfjG/LsU6hk7kxvhnflmOdQidzY3wzvi0nISHBRmR8sbGxMsji4+PV3SalvWrGtxU5HA673Z6ZmZmWlpaamrqSyJi0/+a6YIWq5r80b+n4zsvLy87Oxkt3RkYG6mADkTGhelHDqOTsy6xQ1dqrxlxWp7cZMb5d8vPz8Z4rKysLFYDX8HQiY0L1ooZRyTmXWaGqtVeNuaxObzNifF/Cz77JHOLj4+12O1agSDHrVLX2qrH0LioqUme4GTG+L7FZ5nf0ZG6oZBlk1qlq7VUzvi3HOoVO5sb4ZnxbjnUKncwNlSw/BbZOVWuvmp99W451Cp3MDZUsv4NhnarWXjW/eWI51il0MjdUsvwGtHWqWnvV/N635YSr0IuKik6dOqX2UqBGjRol/zXOCjVz5szjx49v3rx548aN6r6wsvF/muf/dWk14Sr08ePH464PHDig7vDiscceCzIvTp48uW/fPrk5z2n+/PnvvPPOli1b8vPzNWPLQTls8AI7oO3yP6OF/y5evLhUU+KiU/vvqwVswYIF11577enTp9esWVO3bl001BHhY/r4zs3NXbp0qfI8Mr4vUYdYQ1gKHfebmJhYpUqVF198Ud3nhYyngMXGxmqPYLtSfHz8lClTNMP9pRw2eIEdUD4+4nImTZrkcW8w8Ma8Tp06CxcuFJstWrQYPXr0lUPCyWbe+F63bl3Xrl1jYmLcn0ftVTO+LScshb5p0ybcLxbUDRo0KC4uVnd74l640pEjR7CCTk1NvXDhguzEu/slS5bI1f3y5cttl/+hevHvDssD5uXl7dq1629/+1ulSpVeeukleYTCwkLMilWrVmE5LDvLrjyy+2HLnEvdY8eO4ZizZs0Sm8q/LCw3i4qK8JYCB5H/1KTHA3o7k/Pnz2Nioz87O1teDhqNGjWqXLny559/LkdqHz1v54PGV199tWLFCjyY4pdgOPJHH30k35e88cYbiO+CggKxiVcIrMTlccLOxPGNRXfv3r0nTJjgPgsY35eoQ6whLIXep0+fli1bbt261eb8xYvotDnJMe6bHuN72rRpUVFRYnBSUpJI8GHDhokeJLJYUzdp0kT0AIK1zNMBx48fjzcESC60EZ2tWrUS4+Pi4nbu3CnGKEd2P2yZ88gjRozAgG7duolN7R3JzdOnT7dp00bctlq1au+//36Zp/P0diYnTpxo1qyZ7Ldp4hs5W79+/euuu+6nn35S7lRpazfRwOWLA9arV0/eafv27S9evIgB99xzD15x5Q23bduGvQF8zlNBbOaNb0F8o4bxXcr4lvQv9LNnz9aoUSMlJQX33rRp0x49eoh+ERZymPume3wjrPFK0K9fP2Tc2rVrMQarUfTXrFlz6NChZ86cmT9/vvx8VjmC+wERiOjEccqc/2h669atsYjOzMzEYvaOO+4QY9yP7H4c9CA98eKExbX7ALmJu4iPj8esw8kjGbHiVgYI3s6kf//+11xzze7du3Eyw4cPl7dCY+HChXh/gwX4n//8Z5G82mN6Ox80brrpJkQA3hCgjdcGu92OF1e0kQ4YgIvCK5y8IS4fuz744APZE142xjfj22r0L/QFCxbgTseMGYNCvPvuu6Ojo3Nzc9VBbtwLV8AlrF+/ftSoUT179sQYpCo6O3bs2Lhx43fffVf7yYy32JIKCwvRuWTJErRvuOGGgQMHznN68MEHscAXWex+ZPfjoGfw4MHaTY/3e/311ycnJ4tO3LX7AMHbmeA0cNViDF7G5K3kg/Dqq6+i/fzzz6ONKJfH9HY+aMyYMQONkpIStKdPny7b4vPuqlWrzpw5U95Q3Onbb78te8LLZpz4vvnmm21eYJc6+jLGt+S6fNlSh1iDTfdCv/3225WSnTNnjjrIjXvhCs8++yyyCavXQYMGyTF4PUB/9erVk5KS5Ge1yhHcD/jVV1+h84svvkAb7w+uOEWb7ciRI2Wejux+HPTMnTtXu+nxfmNjY6dNmyb7JWW8tzNRbi5vJRt4crt27YpNvLzVrl3bn/j2OEa2sdjX/kYUq37sWrVqlewJL5tx4jswjG/JdfmypQ6xBp0L/eDBg0oJtm3btl27dpohnrkXroBgEt9/OHr0qBwj1qd79+5Fz+rVq8VIb7ElIJfxuoKlrlhWt27deunSpWIXVqDyt4juR3Y/MaUH+Tt58mTRRpLKvbjwhx56SPQfOHBgx44doq3c3NuZtGnTpnv37qK9e/dueSvtzTGZr3fCdclOb+ejvaHHNk4Yr5GiE8T/HbN9+3bZE142xjfj22p0LvQXXngBi2WZQTBlyhSb8zdgNifZ774pvo8hrFmzRvS3bNnylltuef3119GoVKnSxIkTt23bVrdu3eTk5KFDh+JWn3zyiRiJ5Wrnzp1feeUV+XGwOCBuKz5HBvl/vixevBhL7OHDh6ekpHTo0KFevXq//vqrxyMrhxVH1s6xTp064eZITNwQg+XeZcuWod27d2/satSoEc5fvHIoB/R4JmXObyPg5n379h03bhzOXB5WuXe8pahWrZq209v5aMd4bI8aNapp06aiE956662YmBjtxz7hZWN8M76tRs9CRzwhOO69915t5/HjxxG7iBKbk+z3uClhTSr6EbgtWrTAirJfv35IvW7dujkcjqeffrpOnTpYmI8YMUIeYezYsRjWvHlz8T05eSiMbNWqFZbwWVlZcnCZ84t0zZo1Q0IlJSVt3bq1zPnFZ/cjK4ctcwvQ77///v77769Zs2ZiYuKkSZPi4uLk3tmzZ9944424+QMPPCC/O+h+QPczEfDK17BhQ2T3gAED5Mcjyr2XOf8/SW2nt/PRjvHY/vbbb/HS+9lnn4l+HKRnz56iHQlsjG/Gt9WYstCtbP369fKVQELmuncGYMiQIXgJwcvw3r17q1at+s0336gjwsf08e0R4/sSdYg1WKfQKXgFBQVdunTZs2cP1oBjxoxRd4cV45vxbTnWKXQyN8Y349tyrFPoZG6Mb8a35Vin0MncGN+Mb8uxTqGTuTG+Gd+WY51CJ3NjfDO+Lcc6hU7mxvhmfFuOdQqdzI3xzfi2nISEBBuR8cXGxsogi4+PV3eblPaqGd9W5HA47HZ7ZmZmWlpaamrqSiJj0v6b64IVqpr/0ryl4zsvLy87Oxsv3RkZGaiDDUTGhOpFDaOSsy+zQlVrrxpzWZ3eZsT4dsnPz8d7rqysLFQAXsPTiYwJ1YsaRiXnXGaFqtZeNeayOr3NiPHtUlRUhBdtPPd49cb7r8NExoTqRQ2jkvMus0JVa68ac1md3mbE+HYpLi7Gs47XbTz9DodDrlyIjAXVixpGJRddZoWq1l415rI6vc2I8U1EZEiMbyIiQ2J8ExEZEuObiMiQGN9ERIbE+CYiMiTGNxGRITG+iYgMifFNRGRIjG8iIkNifBMRGRLjm4jIkBjfRESGxPgmIjIkxjcRkSExvomIDInxTURkSIxvIiJDYnwTERkS45uIyJAY30REhsT4JiIyJMY3EZEhMb6JiAyJ8U1EZEiMbyIiQ/IQ30REZCCMbyIiQ2J8ExEZ0v8H8XZYTGAPLv0AAAAASUVORK5CYII=" /></p>

```cpp
    //  example/cpp_idioms/shared_ptr_ownership_ut.cpp 89

    // ステップ４
    // オブジェクトA{1}の所有がa1からx1へ移動する。
    // この時、x1::ptr_は下記のような手順で以前保持していたA{0}オブジェクトへの所有を放棄する。
    //  1. x1::ptr_の共有所有カウント(ptr_.use_count()の戻り値)をデクリメント
    //  2. 共有所有カウントが0ならば、ptr_で保持しているオブジェクト(この場合、A{0})をdelete
    //  3. x1::ptr_の管理対象をに新規オブジェクト(この場合、A{1})に変更
    //
    // ここでは、x0::ptr_がA{0}を所有しているため、共有所有カウントは1であり、
    // 従って、A{0}はdeleteされず、A::LastDestructedNum()の値は-1のまま。
    ASSERT_EQ(1, a1->GetNum());                 // a1はA{1}を所有
    ASSERT_EQ(0, x1.GetA()->GetNum());          // x1はA{0}を所有
    ASSERT_EQ(2, x1.UseCount());                // A{0}の共有所有カウント数は２
    x1.Move(std::move(a1));                     // x1はA{0}の代わりに、A{1}を所有
                                                // a1からx1へA{1}の所有権の移動
    ASSERT_EQ(-1, A::LastDestructedNum());      // x0がA{0}を所有するため、A{0}は未解放
    ASSERT_FALSE(a1);                           // a1は何も所有していない
    ASSERT_EQ(1, x1.GetA()->GetNum());          // x1はA{1}を所有
    ASSERT_EQ(1, x1.UseCount());                // A{1}の共有所有カウント数は1
```

<!-- pu:essential/plant_uml/shared_ownership_4.pu--><p><img src="data:image/png;base64,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" /></p>

```cpp
    //  example/cpp_idioms/shared_ptr_ownership_ut.cpp 110

    // ステップ５
    // 現時点でx1はA{1}オブジェクトを保持している。
    // x1::Moveに空のstd::shared_ptrを渡すことにより、A{1}を解放する。
    x1.Move(std::shared_ptr<A>{});              // x1に空のstd::shared_ptr<A>を代入することで、
                                                // A{1}を解放
    ASSERT_EQ(nullptr, x1.GetA());              // x1は何も保持していない
    ASSERT_EQ(1, A::LastDestructedNum());       // A{1}が解放された
```

<!-- pu:essential/plant_uml/shared_ownership_5.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAnYAAAGkCAIAAAAzKP8XAABHoElEQVR4Xu3deXQUVd4+8GZNSFgCkTUgBH1x4PWQgR8YhZkRcUEjuL4oA4wsIslxQECjnDMIsggEFFF2UFkkiCzjxhAWBWQRFFAjAZTV6RgJCAkNgWxk+T30ldvF7e5Q6U53uqqfz8kft27dqu5Kf+s+fbNaSomIiMgHLGoHERERVQRGLBERkU84IraEiIiIvMaIJSIi8glGLBERkU8wYomIiHyCEUtEROQTjFgiIiKfYMQSERH5BCOWiIjIJxixREREPsGIJSIi8glGLBERkU8wYomIiHyCEUtEROQTjFgiIiKfYMQSERH5BCOWiIjIJxixREREPsGIJSIi8glGLBERkU8wYomIiHyCEUtEROQTjFgiIiKfYMQSERH5BCOWiIjIJxixREREPsGIJSIi8glGLBERkU8wYj1x8uTJzp07jxkzRt1BRER0jUkiNj8//2ONtWvX7tmzR+7NyMh4zcnRo0c1JyjLuXPnDh8+fPDgwbS0tAMHDqSmpuLwBx98MCoqCnv3798vH3ffvn3qwUREFKxMErFIwXr16kVERDRs2LB58+Z16tRp1qxZcXGx2Is0fdgJovH6c1yFqFa7SkqmTJlicVK3bt2UlBTs7dmzp+zs16+fejAREQUrk0Ss1pUrV2655ZbXX39d9hx248KFC3LMN998s3fvXsQz0hqbTz/99PTp08Wu7OzsEydOWK1WrIYzMzPPnj3717/+NT4+XuyNiYlZt26dPA8REZFgwohduHBheHi4SEooLCzULD6v8+GHH4oxx44dq1Gjxscff9yqVavExET0tGzZMikpSZ5TKycnJywsLDk5WWw2aNBg06ZN69ev//HHH68fSEREQc1sEfvDDz8g/0RMSqeumTRpUpMmTeRmbm6uHPPCCy/8+c9/fv/995955hmsbqtUqfL5559rzuEwZ86c2rVrixXw5cuXtZn9+OOPYw2tHkBEREHJVBG7f//+Zs2aRUdHYxW7YcMGdXdJyciRIzt16qT22v3yyy9z584VATl16tSaNWtmZWWpg0pKDh48GBER8dprr8keDLt06VJBQcHmzZuRsjt27NAMJyKi4GWSiC0qKlq0aBHWrw8++CBWllit1qhRQ0nZ77//PjIyEru0nYq8vDzka9WqVcePH6/s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" /></p>


```cpp
    //  example/cpp_idioms/shared_ptr_ownership_ut.cpp 120

    // ステップ６
    // 現時点でx0はA{0}オブジェクトを保持している。
    //
    // ここでは、x0からx2、x3をそれぞれcopy、move生成し、
    // この次のステップ７では、x2、x3がスコープアウトすることでA{0}を解放する。
    {
        ASSERT_EQ(0, x0.GetA()->GetNum());      // x0はA{0}を所有
        ASSERT_EQ(1, x0.UseCount());            // A{0}の共有所有カウント数は1
        auto x2 = x0;                           // x0からx2をcopy生成
        ASSERT_EQ(x0.GetA(), x2.GetA());
        ASSERT_EQ(2, x0.UseCount());            // A{0}の共有所有カウント数は２

        auto x3 = std::move(x0);                // x0からx2をmove生成、x0はA{0}の所有を放棄
        ASSERT_EQ(nullptr, x0.GetA());
        ASSERT_EQ(0, x2.GetA()->GetNum());      // x2はA{0}を保有
        ASSERT_EQ(x2.GetA(), x3.GetA());        // x2、x3はA{0}を共有保有
        ASSERT_EQ(2, x2.UseCount());            // A{1}の共有所有カウント数は２
```

<!-- pu:essential/plant_uml/shared_ownership_6.pu--><p><img src="data:image/png;base64,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keEwgr2FNKxXr96nn356/fp1LISxuX37dlFftQj+j//4jz179ly+fPkf//hHRETEb7/95rLZ3XffvXfv3sLCQllJRIbDCPYW0nDatGmijPUvNpcsWSLqqxbBb7/9tiifO3cOm9u2bXPZbOTIkXKTiAyKEewt53AUm+7qKykrm3l5edjEytplswULFshNIjIoRrC3nMNRbNapU0f+reXExER3set8+KuvvirKX3zxBTYPHjzospl2k4gMihHsLXfh+OijjzZt2hQpPGHChPDwcHex63x4tWrVXn755bfeeguH//d//7f4xQ2coVevXlOnTnX5WR8RGRQj2FvOGSo2z5w588QTT9StWzcqKmrGjBn169d3GbvOhyNqcQgO7NOnz7lz50T95MmTsaxu06aN+GYbI5jIHBjBwYXZShRSGMHBhRFMFFIYwcFl5MiRe/fuVWuJyKQYwUREumEEExHphhFMRKQbRjARkW4YwUREumEEExHphhFMRKQbRjARkW4YwUREumEEm9Ybb7yhVhFRkGEEm5bFYlGriCjIMIJNixFMFPwYwabFCCYKfoxg02IEEwU/RrBp8eM4ouDHCCYi0g0jmIhIN4xgIiLdMIKJiHTDCDYtfhxHFPwYwabFL6URBT9GsGkxgomCHyPYtBjBRMGPEWxajGCi4McINi1+HEcU/BjBRES6YQQTEemGEUxEpBtGMBHdWmxs7MGDB9VaXf373/+2Wq1qrXu7du368ssv1Vq9hWgEX716dcuWLStXrgzAqDp69Ojq1as/++yz/Px8dZ8/8eM40/jtt982btyIUXTkyBF1n+9kZ2dnZGSotTdZLJaFCxeqtfpZvHhxkyZNfv31V3WHhjL1NmzY0Lhx48oPCbxQjOCdO3dGRERYburXr9+NGzfURr5QWlo6atQoeUNRUVEnT55UG/kNv5RmDh999FGdOnXwaFa3Gzx4cElJidrIF8LDwysJWUswRfDly5cbNmy4ZMkSdcdN7qZe27ZtJ06cqLbWlckjeP369cuWLcPjgfKVK1cwhpKTkx955JHo6Ojjx49fv359zpw5eITwPKkeeTtc3grK8fHxOHlcXFxOTs7+/ftbtWr15z//WTnWfxjBhuM8kLBceOihh/r373/u3DlU7t27Fw/rtm3b1CNvH16Vr1ix4tixY2ITq0Wc+YUXXsCNXrx4UVReu3YN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" /></p>


```cpp
    //  example/cpp_idioms/shared_ptr_ownership_ut.cpp 142

        // ステップ７
        // このブロックが終了することで、x2、x3はスコープアウトする。
        // デストラクタ呼び出しの順序はコンストラクタ呼び出しの逆になるため、
        // 最初にx3::~X()が呼び出され、この延長でx3::ptr_のデストラクタが呼び出される。
        // これによりA{0}のの共有所有カウントは1になる。
        // 次にx2::~X()が呼び出され、この延長でx2::ptr_のデストラクタが呼び出される。
        // これによりA{0}のの共有所有カウントは0になり、A{0}はdeleteされる。
        // 
    }   // x2、x3のスコープアウト
    ASSERT_EQ(0, A::LastDestructedNum());  // A{0}が解放された
    
```

<!-- pu:essential/plant_uml/shared_ownership_7.pu--><p><img src="data:image/png;base64,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N2+e6C9ajE6cOFG0U1JSsLhx40a7wwYMGCAXiciDGKN62QacWHTUf4e2spiRkYFFzHDtDps1a5ZcJCIPYozqZRtwYjEoKEh+h2h8fLyj6LTd/O233xbtDRs2YHHPnj12h2kXiciDGKN6OQq4tm3bVqtWDUkaHR0dHBzsKDptNw8ICOjfv/+ECROw+aOPPio+nI89dOzYccyYMXZ/f0VEHsQY1cs2B8Xi6dOnO3ToUL58+aioqPHjx4eEhNiNTtvNEZfYBBt27tw5JSVF9I8aNQrT2/r164tPTTFGibwHY9S7MB+JfA5j1LswRol8DmPUuwwYMGDbtm1qLxF5McaoEdy8efP333/Py8tTV9i4cePG5cuXCywfcVXXEd0jFp5g8BjNz8/fvn376tWr8cNW11lMmTLlX//6l9qrgW3XrFlz7NgxL/xzdmfPnu3fv//58+d//vlnk8l0+vRpdYSNCRMm1KxZMyYm5vHHHzdkQXuWsetNYuEpjByj2dnZHTp0MFmEhITs3r1bHVFQ0KhRo27duon2okWLRowYcfv6gqeeekrsoVq1aq+//vqvv/6qDBDOnDkTHR39t7/9rUGDBm3bto2NjTWbzeogVxs7dmzlypWzsrLuUM0nT578WmPAgAEVK1acN28exn/wwQcZGRnqBlRUhq83iYWnMHKMTpo0KTAwcOPGjampqS1atEAFy1XXrl07evToV199hR/qP/7xD/yYcQ6MHj26dOnS2sJFaY4cOXL//v3ffPMNajo8PNxuWa9atapcuXKokocffvj+++9/9dVXg4KCIiMjjxw5og51nZycnNq1az/44IPvvPPOP//5TxwInuE7t8hPSk2ePLlkyZJht1SoUAEj5eLx48dv3ysVnbHrTWLh2TJIjK5bt+7LL78UbVwhFy9enJmZ2axZs5deekl0fvvtt/gpopTFopw1mCx/SAn/x4X96tWrERERqHIxBjChwKr/+7//E4t23wPas2cPTobevXtj80GDBmFqUGC5FNeqVatevXryT4dcuXIFJ098fLz2j4mgvWXLFjx53CXJTkxScHnfunUr7u9OnTqFnri4uB07doi1OEUx4Ny5c2PGjClbtmxHi5YtW+J5Pvnkk2IR5OmHam7cuLHcufj3VHjcgwcPXrx4UfbTPfHyekOF4Oe7du3azz77DKWC6vr888+1NWZbeMuW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" /></p>

以上で示したstd::shared_ptrの仕様の要点をまとめると、以下のようになる。

* std::shared_ptrはダイナミックに生成されたオブジェクトを保持する。
* ダイナミックに生成されたオブジェクトを保持するstd::shared_ptrがスコープアウトすると、
  共有所有カウントはデクリメントされ、その値が0ならば保持しているオブジェクトはdeleteされる。
* std::shared_ptrを他のstd::shared_ptrに、
    * moveすることことで、保持中のオブジェクトの所有権を移動できる。
    * copyすることことで、保持中のオブジェクトの所有権を共有できる。
* 下記のようなコードはstd::shared_ptrの仕様が想定する[セマンティクス](cpp_idioms.md#SS_21_11_1)に沿っておらず、
  [未定義動作](core_lang_spec.md#SS_19_14_3)に繋がる。

```cpp
    //  example/cpp_idioms/shared_ptr_ownership_ut.cpp 162

    // 以下のようなコードを書いてはならない

    auto a0 = std::make_shared<A>(0);
    auto a1 = std::shared_ptr<A>{a0.get()};  // a1もa0が保持するオブジェクトを保持するが、
                                             // 保持されたオブジェクトは二重解放される

    auto a_ptr = new A{0};

    auto a2 = std::shared_ptr<A>{a_ptr};
    auto a3 = std::shared_ptr<A>{a_ptr};  // a3もa2が保持するオブジェクトを保持するが、
                                          // 保持されたオブジェクトは二重解放される
```

こういった機能によりstd::shared_ptrはオブジェクトの共有所有を実現している。


### オブジェクトの循環所有 <a id="SS_21_2_3"></a>
[std::shared_ptr](https://cpprefjp.github.io/reference/memory/shared_ptr.html)の使い方を誤ると、
以下のコード例が示すようにメモリーリークが発生する。

なお、この節の題名である「オブジェクトの循環所有」という用語は、
この前後の節がダイナミックに確保されたオブジェクトの所有の概念についての解説しているため、
この用語を選択したが、文脈によっては、「オブジェクトの循環参照」といった方がふさわしい場合もある。

---

まずは、**メモリリークが発生しない**`std::shared_ptr`の正しい使用例を示す。

```cpp
    //  example/cpp_idioms/shared_ptr_cycle_ut.cpp 8

    class Y;
    class X final {
    public:
        explicit X() noexcept { ++constructed_counter; }
        ~X() { --constructed_counter; }

        static uint32_t constructed_counter;

    private:
        std::shared_ptr<Y> y_{};  // 初期化状態では、y_はオブジェクトの所有しない(use_count()==0)
    };
    uint32_t X::constructed_counter;

    class Y final {
    public:
        explicit Y() noexcept { ++constructed_counter; }
        ~Y() { --constructed_counter; }

        static uint32_t constructed_counter;

    private:
        std::shared_ptr<X> x_{};  // 初期化状態では、x_はオブジェクトの所有しない(use_count()==0)
    };
    uint32_t Y::constructed_counter;
```

上記のクラスの使用例を示す。下記をステップ1とする。

```cpp
    //  example/cpp_idioms/shared_ptr_cycle_ut.cpp 39

    {  // ステップ1
        ASSERT_EQ(X::constructed_counter, 0);
        ASSERT_EQ(Y::constructed_counter, 0);

        auto x0 = std::make_shared<X>();
        auto y0 = std::make_shared<Y>();

        ASSERT_EQ(x0.use_count(), 1);

        ASSERT_EQ(y0.use_count(), 1);

        ASSERT_EQ(X::constructed_counter, 1);
        ASSERT_EQ(Y::constructed_counter, 1);
```

<!-- pu:essential/plant_uml/shared_each_1.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAbgAAAFCCAIAAAAMoV+bAAA1m0lEQVR4Xu2dC5xVU///j0QxpZJC6lFukVv15PLwRC7RQ0SU3EpJpageXSWVIkVRuqjcQsollwdNCSGj0oVhKl0kwzDR5ZlMJsN0/v+3s36ts2edmTk7zwydsz/v1371Wmfttfdea+293uu7zjmdCf0/IYQQJRJyM4QQQhRGohRCiDhERRkWQgjhQaIUQog4SJRCCBEHiVIIIeIgUQohRBwkSiGEiINEKYQQcZAohRAiDhKlEELEQaIUQog4SJRCCBEHiVIIIeIgUQohRBwkSiGEiINEKYQQcZAohRAiDhKlEELEQaIUQog4SJRCCBEHiVIIIeIgUQohRBwkSiGEiINEKYQQcZAohRAiDhKlEELEQaIUQog4SJRCCBEHifKP8NVXX5122ml33XWXu0MIkYwkiSh/+eWXVzzMnj178eLFdm9WVtbQGNatW+c5QUls2bJl9erVK1euzMjI+Pzzz9PT0zm8RYsWRxxxhCnA1efNm/fTTz8VPk4IkSQkiShxWZUqVapWrVqjRo3atWtXrly5Vq1au3btMntx4qUxLF++vPA5fgfluVnh8MiRI0MxHHTQQampqezt2rVr9erVyUGm7pFCiKQgSUTp5bfffjv66KPvvfdem7O6GLZv327LLFmyZOnSpUgW5/LymmuueeCBB8yubdu2bdiwITMzk8g0Ozt78+bNTZs2xY9m79y5c4k0JUohkpgkFOXUqVNTUlKM7+DXX391o8HdzJw505RZv379fvvtx5q9bt26ffv2JefII48cNWqUPaeX3NzcAw88cMaMGTYnLy8vJFEKkbwkmyg//fRTLGZkZ/l+NyNGjDjssMPsSwRny/Ts2bNhw4ZPPPFE+/btiTT32Wef119/3XOOKBMnTqxUqZI3GpUohUhukkqUy5cvr1WrVr169YgoWRG7u8Ph3r17N2nSxM2NsHHjxkmTJrFsJ33//ffvv//+W7dudQuFwytXrqxaterQoUO9mRKlEMlNkoiyoKBg2rRpxJItWrT4+eefiRxZSjuu/OSTT6pXr84ub6bDzp07sWS5cuWGDRvm7NqxY8fDDz9cpUqVSy65hOW8d5dEKURykwyi3LZtW+PGjcuXLz9kyBATEgKrb+LKpUuXhiOOa9WqFfq7/PLL0Wihgz306dOnRo0aBxxwwH333efNR4sdOnRAkZUrV8azjiXDEqUQyU4yiBImTJiwatUqb86uXbvw5vfff29eEm/Onz/fWyCWGTNmjBs37ocffnB3hMNjxozhDDk5Oe4OIUQASBJRCiFE2SFRCiFEHCRKIYSIg0QphBBxkCiFECIOEqUQQsRBohRCiDhIlEIIEQeJUggh4pBUojQ/oJtYUGe3GUKIvYykEiXesa1IFKhzTk5Obm5uXl5efn5+QUGB2yohxF9NdMDalFskcUhQUWZmZmZnZ2/duhVd4kq3VUKIv5rogLUpt0jikKCizMjIWL9+fVZWFq70/pawEGIvITpgbcotkjgkqCjT0tLS09NxJXElQaXbKiHEX010wNqUWyRxSFBRpqam4kriStbg+iU3IfZCogPWptwiiUOCinLWrFnz5s1bunQpQWWRf39CCPHXEh2wNuUWSRwkSiFEWRAdsDblFkkcJMqAs27dum3btrm5gWfkyJFz5sxxc3ezY8eO4v7gaMmU6Tc0dkVYtmzZL7/8UlBQkJeX980337iF/kSiA9am3CKJw58sylWrVs2YMeONN97YuXOnu883wRRl7N8dsqSlpS1fvtzN3Q2DZ8WKFWvXrnV3hMOvvPLKAQcc8Mwzz2zZsqVly5aLFi2yu3r37n19hEmTJh1dGOuIjRs3HnHEEeaPLPmHW79p06affvqJ9MKFC7/++munwKeffuo0ds2aNVT1xRdfnDlz5tNPP23/uDx88MEHL730kn2JHXg20tPTbY5lzJgxjRo1cnOL4sknnwxF+Oqrr3g5fvz4BQsW2L1PPfXUMcccc/DBB0+ZMsVm+iEzM7NKlSol/HmVt99+m/4s+XnGgOaLce6OcLhNmzbPP//8vvvuO2TIkH/+859z586tWLEi0vSW2bx5M/frz5kaowPWptwiicOfJkqu1a1bN/P8Qb169XCcW8gfARTleeedR5Pd3HB49OjR9evXp0N69Ojh7ouQk5PTokWL008/3Yx5C7HG1VdfzYENGza85557OJwxzLhCRqbAkUce2bVr17///e/9+vXDRAy/iRMnMsirV68+e/ZsU2blypWcoThHI+iOHTteeeWV559/Puc59thja9asWaFCBfMAMKQpc+GFF1577bXeo6gne71iAvMnQqnhcccdd+CBB5YrV87qFdVSt6lTp5qXffr0qVq1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ztZkhzbSUtpLq2m72x1CBAmJUggh4iBRCiFEHCRKIYSIg0QphBBxkCiFECIOEqUQQsRBohRCiDhIlEIIEYekEmUi/sYPdXabIYTYy0gqUeId24pEgTrr/8AIsZcTHbA25RZJHBJUlPpf1ULs5UQHrE25RRKHBBWlfqdHiL2c6IC1KbdI4pCgotQvPwqxlxMdsDblFkkcElSU+i1xIfZyogPWptwiiUOCinKW/jqNEHs30QFrU26RxEGiFEKUBdEBa1NukcRBogwau3bt+umnn9xcURRTpkxZt26dm1uYnTt3rlq1ys3dy8jPz//1119NmgoX3llWRAesTblFEoc/WZQ8UjNmzHjjjTe4W+4+3wRZlBs2bHjqqafcXN/Q7W3atKldu3ZOTs4XX3wxYsSI3377zVvgxRdffCTCY489Nm7cuGsK88knn9iSN99880MPPeQ59I9Q3L1zasXL//73vz/++ON3332XmZm5Zs2aTZs2mV1kPvnkk0uWLLGFmQbIef/9922Ol+uvv95ntQcMGMCTduihh2ZnZ5uc9PT0L7/80lvmtttua9Wq1UEHHfTxxx978/3Qo0ePvn37urkxXHnllf/LHR87duzkyZMvvvjiQYMGXXXVVYyaTp06cSvdcmVAdMDalFskcfjTRMm1unXrFtpNvXr1cJxbyB9JLEqm/R9++MHNjfD8889fcMEF5cqVo/nuvsIwsC+55JJTTz01IyPDm//OO+80atRo//33f+aZZ9LS0vr06cOpKOkNMM8444y6deuecMIJ1atXnz59+rnnnnvAAQf06tWre/fuFH7rrbdsySOOOIIbal86pKamcpUJEybce++9/fv379q1a7t27bjW2WeffdJJJ7333numGIP2xBNPLHxo+IknnjjkkEO83/riuvbJMTRp0sTsIkCmW6gtxjQ5PXv2pI1ep3upVatWhw4dvDnIF2fdeuutVLJLly6dO3emVh07djz22GO50PHHH4+jTclzzjlnn332+de//vXhhx+aHJ5DrnX66ac3b948ekYfcJcrVKiAubhH+HfFihXcHbdQBIqhbDfXw8aNGxHuP/7xD+7a+eefP2rUKPvxZkFBAS+POuoouoga0quInnbR0m8ieD8IpcO5oX/729/mzp1rM/8XogPWptwiiUOoDETJfP7aa6/Zl8899xwviVC41ujRo7dt27Zo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" /></p>


上記の続きを以下に示し、ステップ2とする。

```cpp
    //  example/cpp_idioms/shared_ptr_cycle_ut.cpp 55
        // ステップ2

        auto x1 = x0;  // x0が保有するオブジェクトをx1にも所有させる
        auto y1 = y0;  // y0が保有するオブジェクトをy1にも所有させる

        ASSERT_EQ(X::constructed_counter, 1);  // 新しいオブジェクトが生成されるわけではない
        ASSERT_EQ(Y::constructed_counter, 1);  // 新しいオブジェクトが生成されるわけではない

        ASSERT_EQ(x1.use_count(), 2);  // コピーしたため、参照カウントが増えた
        ASSERT_EQ(y1.use_count(), 2);  // コピーしたため、参照カウントが増えた
```

<!-- pu:essential/plant_uml/shared_each_2.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAjAAAAF6CAIAAACIuPWvAAA8g0lEQVR4Xu3dC5xU8//H8SkRKsq6pqjc5VL9hB8il0giopRLkRCRfhUlVESKULqo3Emh3KItIcpSKlltJV0wWla/bDabzarm93+b77/vnL6zUwdnptnt9XzMw+PMOd85M+c7cz7v73fmtEL/AwAgDYTcFQAAbA8EEgAgLcQCKQIAQMoRSACAtEAgAQDSAoEEAEgLBBIAIC0QSACAtEAgAQDSAoEEAEgLBBIAIC0QSACAtEAgAQDSAoEEAEgLBBIAIC0QSACAtEAgAQDSAoEEAEgLBBIAIC0QSACAtEAgAQDSAoEEAEgLBBIAIC0QSACAtEAgAQDSAoEEAEgLBBIAIC0QSACAtEAgAQDSAoH0d3zzzTcNGza866673A0AgL+rjATS77///rrHxIkTZ82aZbfm5ub2jbN06VLPDrbm559/Xrx48cKFC3NychYsWJCdna2HN23a9MADDzQNVq5cOXXq1Pnz52/5OADAX1BGAkmZseeee1atWnWfffapUaNGlSpVqlevvmnTJrNV2XNBnHnz5m25jz8p2NxVkciAAQNCcfbYY4/MzEyzdaeddjIrzz333D/++MN9PADAhzISSF4bNmw45JBD7r//frtmcQJr1661bWbPnj1nzhyFmbJNdy+//PKHHnrIbFqzZs2KFSvC4bBmWnl5eatXr27UqNGNN96oTatWrdprr700ISsqKpo8ebIyacaMGXafAAD/ymAgjR49ulKlSiZXRFOWLaY2HuPGjTNtli1btvPOO7/++uu1atXq0aOH1hx88MEDBw60+/QqLCzcfffdx44da+4WFxebBT382GOPVXrFmgIAfCtrgfTFF18oLUyoWD9u1r9///3339/e1bTGtunSpUu9evWefvrpdu3aaeZUrly5SZMmefYRM3z48MqVK3tnVytXrtSMqnXr1r/88ounIQDgLyhTgTRv3rzq1avXrl1bM6QpU6a4myORrl27nnDCCe7aqG+//XbEiBEbNmzQ8oMPPrjLLrvk5+e7jSKRhQsXVq1atW/fvnbNtGnTjjnmmBKfDgDgXxkJpI0bN44ZM0Zzo6ZNm/7222+aCe28885OSMyfPz8jI0ObvCsd69evVxqVL1++X79+zqZ169Y99thje+65Z7NmzeyVC8uXL1f4ab29wE+vZMvHAQB8KQuBtGbNmgYNGlSoUKFPnz5miiM9evRQVMyZMycSzZIWLVooZi666CLF1RYP9ujevfs+++yz2267PfDAA971ip/27dsriqpUqaI8815HN2nSJOd3Ke/XgAAA/8pCIMmwYcMWLVrkXbNp0ybl048//mjuav40bdo0b4N4Y8eOHTJkyKpVq9wNkcjgwYO1h4KCAncDACAgZSSQAAClHYEEAEgLBBIAIC0QSACAtEAgAQDSAoEEAEgLBBIAIC0QSACAtEAgAQDSQpkKpIyMDOcP+ZR2OiL3IFOCngSQemUqkFR37FGUDTqigoKCwsLCoqKi4uLilP3lVnoSQOrFTli75DYpPcpkGQ2Hw3l5efn5+Sqm9n8GmGz0JIDUi52wdsltUnqUyTKak5OzbNmy3NxcVdKU/SlxehJA6sVOWLvkNik9ymQZzcrKys7OViXV6F5De/eYk4OeBJB6sRPWLrlNSo8yWUYzMzNVSTW6D4fDKfv/X9CTAFIvdsLaJbdJ6VEmy+j48eOnTp06Z84cDe1L/L+qJwM9CSD1YiesXXKblB6U0aDQkwBSL3bC2iW3SelBGQ0KPYmtWLp06Zo1a9y1O7wBAwZMnjzZXbvZunXrJk2a5K71IalXhG6Kmjt37u+//75x48aioqLvv//ebZRCsRPWLrlNSo8Ul9FFixaNHTv27bffXr9+vbstINurjKa4J1Xdnn/+efWnuyE426snt68//vjDXRUVDoffeuutWbNmqRi526K0/vPPP//666/dDZHI66+/vttuu73wwgs///xz8+bNP/30U7upa9euV0aNGDHikC3ZWvztt98eeOCBehfso/zQKfbTTz/9+uuvWp45c+Z3333nNPjiiy+cg12yZIle6quvvjpu3Dh9uvRfu2nGjBkTJkywd1WF9dnIzs62a6zBgwfXr1/fXVuSZ555JhT1zTff6O7QoUOnT59utz777LOHHnroXnvtNWrUKLvSD71Te+6557Rp09wNm7333nvqz61/npU05h88uBsikVatWr388ss77bRTnz59TjvttClTpuy6664KJ2+b1atX6/1KzRAkdsLaJbdJ6ZGyMqrn6tSpk/n8Se3atVXj3EZB2F5lNGU9qThv1qyZzgE94xNPPOFuDs726snt6Mwzz9Qhu2sjkSFDhqgAmY/uOeecEx9aBQUF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UWqmaHTXenz77bcKtn//+996184666yBAwfay3w2btyou3Xq1FEX6RWqVxWoOi4d6fdR3guC1OF6Qw866KApU6bYlf9E7IS1S26T0iOUhDKqcdObb75p77700ku6q5GgnmvQoEEa2n/66acHH3ywPnaeBwUmtJ3KaMp6UhMjDT816A4RSH+XPn7qW3dtVNu2bffZZx+VwsLCQlUZVcYSvylau3ataqiCx7n4UB3lqechjRsUPKeccsq+++57xRVX2GYKpPvuu2/cuHEq8SpYqnEKEq1fsWKFHuWdB6i6devWzd51aOdqr6nDEUccceaZZ1apUmXnnXdu3ry5wuD666/XFMc001Bdr3bLh0YUlnqsxjd2jcq3XtJrr702ffr0yy67TDX6qaeesls1Z9pzzz2vvvpqLesVKq3VP2bTY489pmdXrDZq1EhZqKqt/NArV54psM0sauHChQpdvcKqVavqqDUlUmjtv//+eg1qb7/pkpUrV/bp00cP93aFSseMGTNsHPrUtWtX79shekO1H7fdtgLplVde0YvX4SvmlSWatu6+++76FC1evFhb9V/nWdTb3rvxe9ZARx0YSCbFTli75DYpPUJJKKPt2rXTu6v6pWWNFPQUDz74oM7Jxo0b2zYTJkzQep0wsYcFJLSdymjKetJsMoUvrQJJJd7+EmCXN2zYoLPunXfe0UDE21h333rrrcmTJ2/z39tq4Dxp0iRNBX7//Xe7Ussqmq+//rrG3WZNic9ultV106ZNU539+eeftUahrkNTTdEmvTxTMkxj3VXFGTFihLmrp9amiRMnmrteGvyqsObm5npXKroGDBjQokULjRg0TdFjVRAHRKmOa0rx8ssvm5YKJJXvSy65pHLlyjVr1jz66KN//PHH0047TVmokq20s/vU3bvvvtvedah2r1u3zizfcsstSqZZs2Zt2eRPF1xwwcknn+ys1MGqqsbXSh21XrzG+/GzH83GQtF/DKCY0eu3f01q9OjRmtAoCC+66KKLL75YR6RmqteXRs2dO3fL3cSob9XSW5cVe+aTpk549dVX7fq77rqrQYMG9ocZhYrpWC/nO7cFCxbo9GndurVesCZGM2fO1NuhGChxcqyWmq799ttv7oZIRF2qmNd7qpekTtb0SCv1odJhHn744fooKk11gihWdSyaGOltVd5oLPLll18+8MADlSpV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" /></p>


上記の続きを以下に示し、ステップ3とする。

```cpp
    //  example/cpp_idioms/shared_ptr_cycle_ut.cpp 67
        // ステップ3

        auto x2 = std::move(x1);  // x1が保持する所有権をx2に移動(この後x1はオブジェクトを所有しない)
        auto y2 = std::move(y1);  // y1が保持する所有権をy2に移動(この後y1はオブジェクトを所有しない)

        ASSERT_EQ(x1.use_count(), 0);  // ムーブしたため、参照カウントが0に
        ASSERT_EQ(y1.use_count(), 0);  // ムーブしたため、参照カウントが0に

        ASSERT_EQ(x0.use_count(), 2);  // x0からムーブしていないので参照カウントは不変
        ASSERT_EQ(y0.use_count(), 2);  // y0からムーブしていないので参照カウントは不変
```

<!-- pu:essential/plant_uml/shared_each_3.pu--><p><img src="data:image/png;base64,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" /></p>


上記の続きを以下に示し、ステップ4とする。

```cpp
    //  example/cpp_idioms/shared_ptr_cycle_ut.cpp 79

    }  // この次の行で、x0、x2、y0、y2はスコープアウトし、X、Yオブジェクトは解放される

    ASSERT_EQ(X::constructed_counter, 0);  // Xオブジェクトの解放の確認
    ASSERT_EQ(Y::constructed_counter, 0);  // Yオブジェクトの解放の確認
```

<!-- pu:essential/plant_uml/shared_each_4.pu--><p><img src="data:image/png;base64,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jDFjcEH2MGfOnH37dcCTddttt1155ZUNGzZkP5UrVz722GMLFSpkbg+kkzGNGjW6/vrrnVtxnvQ6DQB69+59+OGHc4annHJK4cKF8+fPb20MS+Pchg0bZla7du3KTWh6Ue1ff/2VmWKcK1euvPfee0uWLIkxL1myBBc34ydOnHjiiSdWrFiR+R5//PH4QZkyZdLS0jiHhx56KBiqac444wxWa9So8cEHHwRDnle/fn3OvG3btmYnMXL//fezH+LJI4lnEN7169c7B+D0DPjjjz+cjRbO+e677z7qqKNMAMkMXnjhBdvLrurUqVOrVi2Cc/rpp1977bXt27cvX778syFsPJkOIWKaX3/9td02QciQcuCdd9555ZVXeE5Y/uuvv4YOHfrVV18NHz6cq9uvXz9uXy4S9+WFF17o3vJgJpCA364iRpKk7JxzzuFp37Zt23PPPcdx8/ZaI0fibrFk3Fbg7DJJ+uTJk7/99lszTQOpPeXIL7/8YlvCQVA++uijH374wdlICYL2kenblogHZYGdf/nllwwmsKb3888/J5idOnVit3Zzw6233oowIbuoD1YRXkVdfvnlyBO25GqnhuBiNW7cuECBAsgx+shFfPTRR7EQM4AHgXOgQmrZsiUjUTpCgV0xnmttxnz33XecGFd8336zc91117Vp0+aRRx4ZNGhQ3bp1qSpeeuklappZs2YZSzj33HM5c9dWp556ardu3VyNwVBx8OCDDx533HGuIgPnKFasGPUHFR5ybOsn5m60OxyKQjPm+++/v++++9gtJ8l9hTdjfswRt9h3gFCyxe398MMPm9XFixdTODoH5Mhvv/2GlZI9VK1alUKNeHIaTkcJRjUk7h825EpxXPIG5tirVy/cvXPnzmYAt1aLFi0IDnvAtql3cdZq1aoRdlqef/55596YL95MxJyNccdXhhR30YFRo0ZxbXAglsk1yIOWL19+/vnnk+/YMTxyjHGpyUFNIAGGFDGSwdDbGDMAuWHA+++/79wqXsR9RuzQqphdpsIz4kX1YLoyMzNNCch8vRJMxpgclpLFpu3z5s0rVaqUaezfv79pjHhQFshezXFxGqydxnr16tkWMyaQFQGSevOkoEc0IvSm3YCM0jh79mxnI7zxxhvFs6C8MMWH5dJLLw2GDIl29J0SB4fAnBBuBlMo2NfaM2fOZP/h79zCGTBg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zZFLNmHDZs2arVmzxrT36NGDQqFKlSrmi2dfymh4KBRJIUSMyJDij/QxXiiSQhxSyJDij2Q0XiiSQhxSyJDiT3p6+vTp092tIvcokkIcUsiQhBBCpAQyJCGEECmBDEkIIURKIEMSQgiREsiQhBBCpAQyJCGEECmBrwzpsRABB6y6Bhx0vUkn+ukdLL2uAUKIFMRXhoT0uJsOcpIlo8k6buLw370hhP+QIaU0yZpRso6bOPw3IyH8hwwppUnWjJJ13MThvxkJ4T9kSClNsmaUrOMmDv/NSAj/4StD0i8f8SJZx00c/rs3hPAfvjIk/5EsGU3WcYUQhzIyJCGEECmBDEkIkQN79uz5+++/3a0iEi+++OKyZcvcrdnZvn374sWL3a0pxs6dO3ft2mWWOeHsnYlChpR3Fi1aNHLkyPHjx//777/uPhEzKN2HH374+uuvz5w5090n9hu8ZMaMGe++++4ff/zh7osNxKhVq1bly5f/888/f/jhh969e+/evds5gJ0PDPHSSy89//zz12bnu+++syPvuOOOZ5991rFpXti0aZO7KYTrrFjdsmULs/7tt99Wr179448//v7776aLxldffXXWrFl2MDchLdOmTbMtTm688cYYT/v+++8PBALHHXfcunXrTMv8+fNXrFjhHNOxY8cWLVoUK1bs22+/dbbHQocOHbp16+ZuDePKK6987bXX3K0x88wzzwwdOvTiiy9+6KGHrrrqqsmTJ99+++1cSve4BOArQzpgv3zwkLdr1y6QRaVKlXLMiUREpkyZUqJECRvJyy67zCUr8eKA3RsHHtLY9evXu1tD7Nixo0mTJia2KOA333zjHpEFAtqsWbMzzjhj4cKFzvbPP//8zDPPLFiw4IgRI7766quuXbuyK0Y6C6ZzzjmnYsWKp5122jHHHENiUa9evSOPPLJz58533XUXgz/55BM7sly5cjw4dtXFxIkTOcqgQYOeeOKJ++67Lz09/brrruNYderUqV69+hdffGGGIY7VqlXLvmnwlVdeKVmypDM15Lj2vjKcffbZpovn96KLLuJsrUl36tSJOTq900nZsmVvueUWZwsmhze0b9+ek2zbtm2bNm04q9tuu61y5coc6NRTT8ULzcgLL7wwX758l1xyyZdffmla3nrrLY5Vu3btxo0b79tjDHCVCxUqhENwjfC5uXPncnXcg0IwDGt0tzr46aefMLbzzjuPq9awYcN+/fqRbZiu//77j9UTTzyREHGGRBVDZV7MdE0IOxIIOBf0hBNOmDRpkm3cH3xlSIEEfBvGjf7BBx/Y1VGjRrE6fPhwjsVlI1n7+uuvK1SowG23b5v4kSwZTcRxI0byggsuQM6WLFmybdu25557jqhScTo2ihuJuDdSBG4/snt3a4gnn3wSbUIsfv31V+Jco0YN94gQf/31FxqK8Ti1BpYvX+4U9COOOALjOf/884899tgbbrjBDmPPvXr1Gj16NBKPYKFxGAntK1euZCtnHYC63XvvvXbVBTsPhIyzSpUqDRo0KFq06OGHH968eXPM4M4776TEMcNI1Tnb7JsGMUu2/eijj2wL8s0pvf/++1OnTr366quJw8svv2x7qZmKFy9+8803s8wZ5s+fn8fZdHEfcnRstW7dunghqo1/cOb4GYZtqqhFixZhupwh6RSzpiTCtEqXLs05MN6+6YJffvmlR48ebO4MBddl+vTpua1Zu3Tp4rwcgNVF/F8qRzekd955h5Nn+tg8XkLZWrhwYe4iHkN6+a/rKETbuRq+5549exLAuHiSDCkHWrduzdXduHFjMOv5zMjI4JmsX7++HfPuu+/S/sMPP+zbLE4kYkaxkIjjRoxk0PF6mqSSRhTEuVW8yO2MkHhb9dplqjeeuo8//njz5s3Owax++OGHEyZMyPHlLXPEcSkFqF1sI8uI5tixY8m7TUvEo5tl0tVPP/2UKJlIjhs3jqmhKXRxekYyzGBAQ6+//nqzbCqGiHcpyS/Cimk5GxcvXswFatGixY033kiZwrYIYkYIdJyS4u233zYjMSTk+8orryxSpMjxxx9ftWrVtWvXkmqUKlUKycbt7D5ZfeSRR+yqC7T7n3/+McsdO3bEmSK+xb300kvPPfdcVyNzR1XDtZKAc/Lk++HVD9UYk+JaYDOcP5WBaR82bBgFDUZ4+eWXX3HFFcyIYej1VSFmz56dfTf7GDNmDCOduoztmReMBAGVsO0PP/zwWWedZe98TMUE1onrnduCBQt4fK655hpOmMJoxowZXA5sIGJxzEjKNZI8d0cwSEixea4pp0SQKY9o5KZimqeccgq3Im7K44mtMhcKIy4rfkMu8v333/fp0yctLS3iEVu1aoUxb9261d2RS2RIOcB9zG6ff/55lnmWuNJcDx4VZw3x+++/MwZB2bdZnEjEjGIhEceNGEnbi5TzkPBU5DZtjJHczojxtuywy8hTIAQZMZprehcuXGhSYzjppJOi/PjPyDJlypiR1apVM1L1888/U1KYRvLWN954I+hxdLPMY28GlytXjoIGMTWrQAzNghkcDBlA//79zfKGDRsC2WsIA8aG3Dz44IOu9smTJ/8vBHc7G3KSLFMrsIxysXz33XebkRjS6aefjoRxbn379sUwEG4UvECBAqRuzn2yOaLmbImIyfC8UhPMo2nTpu7WYBCXuuiii5wtFFVk90cffTQ6Tl1FDeR0RzCVE7UCV8HZbsHFkW9O5qabbnL3hdGuXTsm6KwyScIOO+wwvJnLau0HpyfgLVu2tMN69+5dPASbU/SYZWfKy2kTYW4eZyZUu3Zt9mxXnTApzpm9UeGhVM4spEmTJhRGxn3ZA7mIaUe+2ISkCjXjWpcvX54jUphS2xUOwY3dvXv38JelBibFmQ8ZMsTdkUtkSDnDnVGjRo09e/bwjCGawdD1pq63A7jVOPT+/IroRYJmlCMJOm54JA1knaTVdevWJUd2DI8nuZ1RIJIloO88kyTd8+bNsyN5wi+++OJBgwa1bduWjHXAgAG2y0Xjxo3RgjVr1sydO5eMkjyURkoQ8vdFixaxW55/PAmri3h0s4yIEKVZs2axTFnmGuACSXrxxRfNMskvI0ePHp19yF7joT38zQ9++dZbb3F6SOq9996LPSB/aCJXkP9SRthy0PnKbuDAgUTJ/PPqFGc8Kc59olkmI7EQBDJ9V9LdqFGjWrVqOVuc4Hyk7e7W0G9LJDR2lUrC/Dx5wgknEHmkmYkwgPjbMcakn376advi5J133uH88VS2yvEnfTzjqKOOoqhyNuKIxAH/DmT9lkYJWLNmTTw+ogV27tyZPMPdGgw+9NBD3BjOevHrr79mny+99JJj1D44bZIn0j6eKdICRnK/BUO/D+GvVDzB0HccdNk9EBaGDR48mPuE0zA5AT762WefETe24opzA0Qx5kqVKjlf5OYNXxlSIn75CGa9FeFJ47/ml0lC73wVvnTpUnvDxZdALmU0XiTouOGRDIZ+W0pLSyN7te9MEkFu741AJEvgVEuVKoWVzpkzx44kmQ04aN++ve1ygQw58xgDovnMM8+YZTyAPZgohR/dLHMOdtnkQM4BLlA3rMIsr169mpHoS/YhQXZC+8qVK13tM2bMIC9GB9FTpBZvo55A4zAD0moUqlmzZmYkhkTB1KBBA2NIhGhGCK6p05CMIw4fPty2QEZGBnrn+nAOA+jQoYOzxQkHMl9VdOzYkUnZ9kcffZRdmY9ilixZwjLmbW8z4KoxC9TWtgQ9osep8oBjn1gjFQ/ZEjWfa4wLxgci+Xow9A0Frs+Jbdu27ZJLLmG3WJ17UAgvQyLlxYHsKqfHKZUtW9brFbHzNyRMF9d57733gqENyZlMTjB+/HhO2P4yx5mzyollZmaGbuR9fPPNN/fddx8XhW1HjhyZdRA3F154obOqyxu+MqQEwf1UuXLlY4891v4mTC7GfWNfmPKU8uja72riSG5lNF4k6LjhkRwzZgwaMWHChOwDkw/PnkkezftYq1lkuPgHcmz/jgRdsL9PuD4KcMEjbd+MIRNmgfzdfsj7/fffc6ypU6d6HT3isrPRRcuWLe3PLZRKnLb55cnJpEmTAo78wAk6+PHHH2PAt956a+vWrY877jj2cMsttzALijOqOjPs2Wef7Rzi4YcfJo82b5wMbGL3tnPnTrTYaUibN28uXbr0ZZddZlsMqC1Fp6vRQrFy1llnGdum1rTtFKm02Fe+lHddu3Yl1zn55JNHjBhhGinNXVl8ePSQ5mrVqnGqbG4+TzjjjDNcpY8T7uonn3yS8a4v8VzMnz//zDPP5HA2/wjHy5CccEpcEfbDBN19WUT5qKFKlSqm2qMcJ7G27TileYtOXkiOgp3Pnj0bPzafAq5bt47nlCfX/sgXDoW+/cEyz8iQYmLAgAHcAS+88IJZXbBgwRFHHMFt2rdv33bt2iEfsfxxgAhmjyQJI9l0rVq1hjqI8pgdSHhuya+HDBliRATN4qJfccUVqAlyHHD8GENqjIggST179ixZsiRTyL6nfZBmUnD06NGDDIb7x3xPyCoqTxd5K2596qmnkvaGH93sIeKy+Y36008/NY0BR3VrXsfRy+lRikV8o4KCo0QPPfSQuyNEq1atOFXUlstERdKpU6eKFSsyTecPPEuXLkW72Q+et3z58mXLlpkvF/BpW88ZmCBJtEnd2KpOnTo8O+F/jsNjxWmj7/hN+J8B9O7dm1O69NJLq1ev7mx/+eWX2cr5Kgw3Yth1111nbjkuUCD0GsqxUQRDQq+Zo3nhYY5+9tln23LQCb0ffPABBSI7ad68ecSPCLCradOmcQ7MlEtgvwRxwr00NgQ7oco0y86PXCzEtm7duhyue/furi4nUQyJhICr+cADD5BDk3eSc5AAcVHYpy2mSSy4qcqUKcMY80GNeWxpnDhxYrbdZUFJym4HDx7s7sglMqSYQC+KFSvm/L2aq8gjyoUnQebxc37oKaLgjKT5scQFWuzeJhlMmTKFzJpTRZ7QNTRr9erVKDspP41t27Yl3zcjkSFkmuSRgoB2UshXwzBPNU5z9913o+aIDopgxI79cP9QPLFbagXz6iz86OZYgUiG1KFDBwQadTafKQayv27F1fBLlIVdeRXxd9xxByfvfP1lYGrY5JVXXnnNNddQtbDn8uXLo2LOMov58iDgo1u3biVHppaizkN8US4qJ0TKKWGUNVhygQIFzK87LL/++uu210KSTnzMBxRGGZ1aTzDp4hCuwhpj69Kli/OjGMoaMn3KKQ5kdkXiiEM4NtobPde3fBzLvvxgD0SGEw6vfkhNzMfcJFUDBw6M+MIZe0YfGMNF5NLbv8x14Xrra3F9J4VPIDhca9fvcOFEMSSmj5mZ7x3++usvbjkOxAnY3z6RMgJbs2bNIkWKBEJ/c8btTbRJR7gTCmX/et5C19FHHx3li54YkSHlAE8piQPXj3vd3Sdyw6ETSbeuhOXgqQZGhaNUq1bN9YnjqFGjAiHBrVev3qOPPkqmH16vzJkzB5M2VQ4iaL7Catq0KTVTMPTFh0vKf/nllxEjRvTv35+dR/+icsOGDaNHj34khKuLyikzM9PVGA7pPwU3Z84eqAwifkcQHapYkoz09PRVq1a5umbPnt2yZUvm4vVDjqF9+/YUjl6pgIEsZFkkXF9RMxcKVipLZ2NEcvyXGux1ZBZvvvmm00gWLFiAFTFr7BNnYlfkRgQQJ2OmLVq0wBftYANZJsavv0Nyk4hfPrhXyPIaN27s+tMTkVuSG8lE3Bt+Yv369ddff/3555/v+pcavP6dHif2dwX7ZbP9K6v9T5nFgcdlhM7yFCdz1oJYFCXmmWeeOXXqVNu4P/jKkAKJ+TbM+TeMB5hkyWiCjpvESCbo3hBCxBEZUkqTrBkl67iJw38zEsJ/yJBSmmTNKFnHTRz+m5EQ/kOGlNIka0bJOm7i8N+MhPAfvjKkBP3ykUSSJaPJOm7i8N+9IYT/8JUh+Y9kyWiyjiuEOJSRIQkhhEgJfGhIZPcBB65kP2+9lStXjtIbfdv9700i0U8sD70mkl690beNS68QImXxoSElgoDvflNJFoqkEMILGVJMSEbjhSIphPBChhQTktF4oUgKIbyQIcWEZDReKJJCCC9kSDEhGY0XiqQQwgsZUkxIRuOFIimE8EKGFBOS0XihSAohvJAhxYRkNF4okkIIL2RIMSEZjReKpBDCCxlSTEhG44UiKYTwQoYUE5LReKFICiG8kCHFhGQ0XiiSQggvZEgxIRmNF4qkEMILGVJMSEbjhSIphPBChhQTktF4oUgKIbyQIcWEZDReKJJCCC9kSDEhGY0XiqQQwgsZUkxIRuOFIimE8EKGFBOS0XihSAohvJAhxYRkNF4okkIIL2RIkalRo0bAA7rco4U3iqQQIkZkSJHp16+fWz6zoMs9WnijSAohYkSGFJnVq1fnz5/fraCBAI10uUcLbxRJIUSMyJA8qV+/vltEAwEa3eNETiiSQohYkCF5Mnz4cLeIBgI0useJnFAkhRCxIEPyZPPmzYUKFXJqKKs0useJnFAkhRCxIEOKRsuWLZ0yyqp7hIgNRVIIkSMypGiMGTPGKaOsukeI2FAkhRA5IkOKxvbt24866iijoSyw6h4hYkORFELkiAwpB9q0aWNklAV3n8gNiqQQIjoypByYOnWqkVEW3H0iNyiSQojoyJByYM+ePceHYMHdJ3KDIimEiI4MKWfuD+FuFblHkRRCREGGlDPfh3C3ityjSAohoiBDEkIIkRLIkPLIrl277G8hzmWRWxRJIYRBhpRHAoHA0KFDw5ejsG7duoULF7pbD3kUSSGEQYaUR/Igo2lpabEMO9RQJIUQBhnSXlC35cuXz507d8SIERMmTNi5c6dtX7RokXOYXY0ioywvXbp0ypQpo0aNWrFihWkcOXIkw2644QZ6169fb4atXLkyMzNz4MCBdtuDHUVSCJFnZEh7QeCqVq0ayKJWrVq7du0y7U599JLO8GHlypUzuypYsOCbb75JY4UKFez+kU4z7J577smXL1/z5s3ttgc7AUVSCJFXZEh7QdGKFi06bty4bdu2kdqzOnnyZNOeNxktWbLktGnTtmzZcuedd5YoUWLjxo0Rh5UpU2b69Ok7duywjQc7iqQQIs/IkPaCovXq1cssk9GzOmzYMNOeNxnt27evWV6zZg2rkyZNijgsPT3drvoDRVIIkWdkSHsJFziz6tUeZdm1unXrVlapFSIOGzJkiF31B+FzVCSFEDEiQ9pLuMCZ1cKFC/fr1880Tpw40Us6wzfv0qWLWZ4wYQKrM2fOjDjMueoPvOaoSAohckSGtBcvgWvYsGHp0qVR0m7duqWlpXlJZ/jm+fLla9u2bUZGBpvXrl3b/LEne7j44osff/zxiL/z+4PwUCiSQogYkSHtJVwHzeqqVauaNGlSpEiRSpUq9enTp1ixYhGlM3xz5JJN2LBZs2Zr1qwx7T169KBQqFKlivni2ZcyGh4KRVIIESMypPgjfYwXiqQQhxQypPgjGY0XiqQQhxQypPiTnp4+ffp0d6vIPYqkEIcUMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEEQxJCCGESCIyJCGEECmBDEkIIURK8P+SDLRScZ1/DQAAAABJRU5ErkJggg==" /></p>


このような動作により、`std::make_shared<>`で生成されたX、Yオブジェクトは解放される。

---

次は**メモリリークが発生する**`std::shared_ptr`の誤用を示す。まずはクラスの定義から。

```cpp
    //  example/cpp_idioms/shared_ptr_cycle_ut.cpp 91

    class Y;
    class X final {
    public:
        explicit X() noexcept { ++constructed_counter; }
        ~X() { --constructed_counter; }

        void Register(std::shared_ptr<Y> y) { y_ = y; }

        std::shared_ptr<Y> const& ref_y() const noexcept { return y_; }

        // 自身の状態を返す ("X alone" または "X with Y")
        std::string WhoYouAre() const;

        // y_が保持するオブジェクトの状態を返す ("None" またはY::WhoYouAre()に委譲)
        std::string WhoIsWith() const;

        static uint32_t constructed_counter;

    private:
        std::shared_ptr<Y> y_{};  // 初期化状態では、y_はオブジェクトを所有しない(use_count()==0)
    };

    class Y final {
    public:
        explicit Y() noexcept { ++constructed_counter; }
        ~Y() { --constructed_counter; }

        void Register(std::shared_ptr<X> x) { x_ = x; }

        std::shared_ptr<X> const& ref_x() const noexcept { return x_; }

        // 自身の状態を返す ("Y alone" または "Y with X")
        std::string WhoYouAre() const;

        // x_が保持するオブジェクトの状態を返す ("None" またはY::WhoYouAre()に委譲)
        std::string WhoIsWith() const;

        static uint32_t constructed_counter;

    private:
        std::shared_ptr<X> x_{};  // 初期化状態では、x_はオブジェクトを所有しない(use_count()==0)
    };

    // Xのメンバ定義
    std::string X::WhoYouAre() const { return y_ ? "X with Y" : "X alone"; }
    std::string X::WhoIsWith() const { return y_ ? y_->WhoYouAre() : std::string{"None"}; }
    uint32_t    X::constructed_counter;

    // Yのメンバ定義
    std::string Y::WhoYouAre() const { return x_ ? "Y with X" : "Y alone"; }
    std::string Y::WhoIsWith() const { return x_ ? x_->WhoYouAre() : std::string{"None"}; }
    uint32_t    Y::constructed_counter;
```

上記のクラスの動作を以下に示したコードで示す。

```cpp
    //  example/cpp_idioms/shared_ptr_cycle_ut.cpp 151

    {
        ASSERT_EQ(X::constructed_counter, 0);
        ASSERT_EQ(Y::constructed_counter, 0);

        auto x0 = std::make_shared<X>();       // Xオブジェクトを持つshared_ptrの生成
        ASSERT_EQ(X::constructed_counter, 1);  // Xオブジェクトは1つ生成された

        ASSERT_EQ(x0.use_count(), 1);
        ASSERT_EQ(x0->WhoIsWith(), "None");     // x0.y_は何も保持していないので、"None"
        ASSERT_EQ(x0->ref_y().use_count(), 0);  // X::y_は何も持っていない

```

x0のライフタイムに差を作るために新しいスコープを導入し、そのスコープ内で、y0を生成し、
`X::Register`、`Y::Register`を用いて、循環を作ってしまう例(メモリーリークを起こすバグ)を示す。

```cpp
    //  example/cpp_idioms/shared_ptr_cycle_ut.cpp 165

        {
            auto y0 = std::make_shared<Y>();

            ASSERT_EQ(Y::constructed_counter, 1);   // Yオブジェクトは1つ生成された
            ASSERT_EQ(y0.use_count(), 1);
            ASSERT_EQ(y0->ref_x().use_count(), 0);  // y0.x_は何も持っていない
            ASSERT_EQ(y0->WhoYouAre(), "Y alone");  // y0.x_は何も持っていないので、"Y alone"

            x0->Register(y0);                       // これによりx0.y_はy0と同じYオブジェクトを持つ
            ASSERT_EQ(x0->WhoIsWith(), "Y alone");  // x0が持つYオブジェクトはまだXを持っていない状態

            y0->Register(x0);                       // これによりy0.y_はx0と同じオブジェクトを持つ
            // 上記で生成されたXオブジェクト、Yオブジェクトは、x0->Register(y0), y0->Register(x0)により
            // 相互に参照しあう状態になる
            ASSERT_EQ(X::constructed_counter, 1);   // 新しいオブジェクトが生成されるわけではない
            ASSERT_EQ(Y::constructed_counter, 1);   // 新しいオブジェクトが生成されるわけではない

            ASSERT_EQ(y0->WhoYouAre(), "Y with X"); // y0.x_はXオブジェクトを持っている
            ASSERT_EQ(x0->WhoYouAre(), "X with Y"); // x0.y_はYオブジェクトを持っている

            ASSERT_EQ(y0->WhoIsWith(), "X with Y"); // y0.x_はXオブジェクトを持っている
            ASSERT_EQ(x0->WhoIsWith(), "Y with X"); // x0.y_はYオブジェクトを持っている

            // 現時点で、x0とy0がお互いを持ち合う状態であることが確認できた
```

<!-- pu:essential/plant_uml/shared_cyclic.pu--><p><img src="data:image/png;base64,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" /></p>

下記のコードでは、y0がスコープアウトするが、そのタイミングでは、x0はまだ健在であるため、
Yオブジェクトの参照カウントは1になる(x0::y_が存在するため0にならない)。

```cpp
    //  example/cpp_idioms/shared_ptr_cycle_ut.cpp 192

            ASSERT_EQ(x0.use_count(), 2);           // x0、y0が相互に参照するので参照カウントが2に
            ASSERT_EQ(y0.use_count(), 2);           // x0、y0が相互に参照するので参照カウントが2に
            ASSERT_EQ(y0->ref_x().use_count(), 2);  // y0.x_の参照カウントは2
            ASSERT_EQ(x0->ref_y().use_count(), 2);  // x0.y_の参照カウントは2
        }  //ここでy0がスコープアウトするため、y0にはアクセスできないが、
           //x0を介して、y0が持っていたYオブジェクトにはアクセスできる

        ASSERT_EQ(x0->ref_y().use_count(), 1);  // y0がスコープアウトしたため、Yオブジェクトの参照カウントが減った
        ASSERT_EQ(x0->ref_y()->WhoYouAre(), "Y with X");  // x0.y_はXオブジェクトを持っている
```

<!-- pu:essential/plant_uml/shared_cyclic_2.pu--><p><img src="data:image/png;base64,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2bzkkkuciZGSXvMSzVrcAwuLEv32228PFL1qXb9+/ffffz98bymMmNTdP89bKZ+e/fzzzxUPeq4T/jTFoMm9Huvf//535Bcq1LKunvOitEvB37x587p165b49CjyvUlNJY13pjWcLrvssvASadeunc7T3dR0ULGt3umHoqz1GmOFZat57bXXOl+GueCCC3R6Xbp0cXf169dPJZHPb6JBTForEM8xqXmk83clNaeM3FviEoj/mNTd84wzzmjQoIHmQ+a+8lDypaSkOOupqaluqDj3wfXr1wfCPqLZsmVL9xOYumOW8krv+eeff/311zvrmzZtcl/NO/fcc2+88UZn/c0331Tja9asKfQ+jcKIOHQ3jfISlR6TkddQUx/NF5XfzubQoUN1Yu7bdT179tSs0U0OZarzeqYuhfHxHI2oTp066aE7d+6sMdawYUO1s3z58vA6XirkvUk1ogfVzGnZsmXmvkOCweBxxx131llnmTu8OR/iDX8mES4yJiMpIy+++OLwkldffVVHPfDAA26JnnM4Uar41ET/l19+Ka59uLLUvOWWW0499VT9rDUg3c/xiiaRxx9/vFL/8OrRIiatFYjnmNTiTCWTRiZF7ipxCcR/TMrEiRMDYZMbL4EiXpsdO3Y88cQTFVGDBg3SVC9QFCqa+pxwwgkqcZ5uO+8Fiu7dml/eddddY8aMadOmjQ7ctWuX21Q4503EpKQktdy4cWPdjJwgcd4c6tWr18iRI5VPasR5razE03CaCl8P31S1K6+88qGHHnJmVEa/HKXHZGHENdywYUPNmjX1bEAdTE5OVsy4LxHrOYEmLjfddNP333+vR/zxxx81TezTp09xW0XUnWeffVZZGyj6pE9e0URct+bExMTatWt/+OGH4ZWVZHUjON3/fTGpR9eUV09E1ILOVoPcrHHIZ5995nyWqizfINRzpjfeeEM/I9XXUV4/9LLEpPPm7ty5c9WmUu3pp5/WZdFIcP8P6klVoOjDxlo/s4hK1C+Nnx07duhKuo9expovvvhioOiTX/r3kUceKSx6fqDH1c9IZ6LnZE5rFYWYtFYgzmPyytuvrFm75qT0SZG7SlwCVsTk4MGD69Sp4/UhRlegiNfmV199dcUVV+hWpbnRqFGj1KBCRfOn22+/vX79+rprG79cRnt1P1KWtG7d+r333gvfZXjiiSdOP/10zaKu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" /></p>

ここでの状態をまとめると、

- y0がもともと持っていたXオブジェクトは健在(このオブジェクトはx0が持っているものでもあるため、use_countは2のまま)
- x0が宣言されたスコープが残っているため、当然ながらx0は健在
- x0はYオブジェクトを持ったままではあるが、y0がスコープアウトしたため、Yオブジェクトのuse_countは1に減った

  
次のコードでは、x0がスコープアウトし、y0がもともと持っていたXオブジェクトは健在であるため、
Xオブジェクトの参照カウントも1になる。このため、x0、y0がスコープアウトした状態でも、
X、Yオブジェクトの参照カウントは0にならず、従ってこれらのオブジェクトは解放されない
(shared_ptrは参照カウントが1->0に変化するタイミングで保持するオブジェクトを解放する)。

```cpp
    //  example/cpp_idioms/shared_ptr_cycle_ut.cpp 204
    }  // この次の行で、x0はスコープアウトするため、x0にはアクセスできず、すでにy0にもアクセスできない
    // ここではx0、y0がもともと持っていたXオブジェクト、Yオブジェクトへのポインタを完全に失ってしまった状態

    ASSERT_EQ(X::constructed_counter, 1);  // Xオブジェクトは未開放であり、リークが発生
    ASSERT_EQ(Y::constructed_counter, 1);  // Yオブジェクトは未開放であり、リークが発生
```

<!-- pu:essential/plant_uml/shared_cyclic_3.pu--><p><img src="data:image/png;base64,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" /></p>

X、Yオブジェクトへの[ハンドル](cpp_idioms.md#SS_21_9_6)を完全に失った状態であり、X、Yオブジェクトを解放する手段はない。

## copy/moveと等価性のセマンティクス <a id="SS_21_3"></a>
### 等価性のセマンティクス <a id="SS_21_3_1"></a>
純粋数学での実数の等号(=)は、任意の実数x、y、zに対して、

| 律   |意味                     |
|------|-------------------------|
|反射律|x = x                    |
|対称律|x = yならばy = x         |
|推移律|x = y且つy = zならばx = z|

を満たしている。x = yが成立する場合、「xはyと等しい」もしくは「xはyと同一」であると言う。

C++における組み込みの==も純粋数学の等号と同じ性質を満たしている。
下記のコードは、その性質を表している。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 13

    auto  a = 0;
    auto& b = a;

    ASSERT_TRUE(a == b);
    ASSERT_TRUE(&a == &b);  // aとbは同一
```

しかし、下記のコード内のa、bは同じ値を持つが、
アドレスが異なるため同一のオブジェクトではないにもかかわらず、組み込みの==の値はtrueとなる。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 23

    auto a = 0;
    auto b = 0;

    ASSERT_TRUE(a == b);
    ASSERT_FALSE(&a == &b);  // aとbは同一ではない
```

このような場合、aとbは等価であるという。同一ならば等価であるが、等価であっても同一とは限らない。

ポインタや配列をオペランドとする場合を除き、C++における組み込みの==は、
数学の等号とは違い、等価を表していると考えられるが、
上記した3つの律を守っている。従ってオーバーロードoperator==も同じ性質を守る必要がある。

組み込みの==やオーバーロード[==演算子](core_lang_spec.md#SS_19_6_3)のこのような性質をここでは「等価性のセマンティクス」と呼ぶ。

クラスAを下記のように定義し、

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 34

    class A {
    public:
        explicit A(int num, char const* name) noexcept : num_{num}, name_{name} {}

        int         GetNum() const noexcept { return num_; }
        char const* GetName() const noexcept { return name_; }

    private:
        int const   num_;
        char const* name_;
    };
```

そのoperator==を下記のように定義した場合、

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 51

    inline bool operator==(A const& lhs, A const& rhs) noexcept
    {
        return std::tuple(lhs.GetNum(), lhs.GetName()) == std::tuple(rhs.GetNum(), rhs.GetName());
    }
```

単体テストは下記のように書けるだろう。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 62

    auto a0 = A{0, "a"};
    auto a1 = A{0, "a"};

    ASSERT_TRUE(a0 == a1);
```

これは、一応パスするが(処理系定義の動作を前提とするため、必ず動作する保証はない)、
下記のようにすると、パスしなくなる。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 72

    char a0_name[] = "a";
    auto a0        = A{0, a0_name};

    char a1_name[] = "a";
    auto a1        = A{0, a1_name};

    ASSERT_TRUE(a0 == a1);  // テストが失敗する
```

一般にポインタの等価性は、その値の同一性ではなく、
そのポインタが指すオブジェクトの等価性で判断されるべきであるが、
先に示したoperator==はその考慮をしていないため、このような結果になった。

次に、これを修正した例を示す。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 91

    inline bool operator==(A const& lhs, A const& rhs) noexcept
    {
        return std::tuple(lhs.GetNum(), std::string_view{lhs.GetName()})
               == std::tuple(rhs.GetNum(), std::string_view{rhs.GetName()});
    }
```

ポインタをメンバに持つクラスのoperator==については、上記したような処理が必要となる。

次に示す例は、基底クラスBaseとそのoperator==である。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 114

    class Base {
    public:
        explicit Base(int b) noexcept : b_{b} {}
        virtual ~Base() = default;
        int GetB() const noexcept { return b_; }

    private:
        int b_;
    };

    inline bool operator==(Base const& lhs, Base const& rhs) noexcept { return lhs.GetB() == rhs.GetB(); }
```

次の単体テストが示す通り、これ自体には問題がないように見える。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 131

    auto b0 = Base{0};
    auto b1 = Base{0};
    auto b2 = Base{1};

    ASSERT_TRUE(b0 == b0);
    ASSERT_TRUE(b0 == b1);
    ASSERT_FALSE(b0 == b2);
```

しかし、Baseから派生したクラスDerivedを

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 143

    class Derived : public Base {
    public:
        explicit Derived(int d) noexcept : Base{0}, d_{d} {}
        int GetD() const noexcept { return d_; }

    private:
        int d_;
    };
```

のように定義すると、下記の単体テストで示す通り、等価性のセマンティクスが破壊される。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 157

    {
        auto b = Base{0};
        auto d = Derived{1};

        ASSERT_TRUE(b == d);  // NG bとdは明らかに等価でない
    }
    {
        auto d0 = Derived{0};
        auto d1 = Derived{1};

        ASSERT_TRUE(d0 == d1);  // NG d0とd1は明らかに等価ではない
    }
```

Derived用のoperator==を

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 174

    bool operator==(Derived const& lhs, Derived const& rhs) noexcept
    {
        return std::tuple(lhs.GetB(), lhs.GetD()) == std::tuple(rhs.GetB(), rhs.GetD());
    }
```

と定義しても、下記に示す通り部分的な効果しかない。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 184

    auto d0 = Derived{0};
    auto d1 = Derived{1};

    ASSERT_FALSE(d0 == d1);  // OK operator==(Derived const&, Derived const&)の効果で正しい判定

    Base& d0_b_ref = d0;

    ASSERT_TRUE(d0_b_ref == d1);  // NG d0_b_refの実態はd0なのでd1と等価でない
```

この問題は、「[RTTI](core_lang_spec.md#SS_19_4_9)」使った下記のようなコードで対処できる。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 200

    class Base {
    public:
        explicit Base(int b) noexcept : b_{b} {}
        virtual ~Base() = default;
        int GetB() const noexcept { return b_; }

    protected:
        virtual bool is_equal(Base const& rhs) const noexcept { return b_ == rhs.b_; }

    private:
        int b_;

        friend inline bool operator==(Base const& lhs, Base const& rhs) noexcept
        {
            if (typeid(lhs) != typeid(rhs)) {
                return false;
            }

            return lhs.is_equal(rhs);
        }
    };

    class Derived : public Base {
    public:
        explicit Derived(int d) : Base{0}, d_{d} {}
        int GetD() const noexcept { return d_; }

    protected:
        virtual bool is_equal(Base const& rhs) const noexcept
        {
            // operator==によりrhsの型はDerivedであるため、下記のキャストは安全
            auto const& rhs_d = static_cast<Derived const&>(rhs);

            return Base::is_equal(rhs) && d_ == rhs_d.d_;
        }

    private:
        int d_;
    };
```

下記に示す通り、このコードは、
[オープン・クローズドの原則(OCP)](solid.md#SS_8_2)にも対応した柔軟な構造を実現している。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 267

    class DerivedDerived : public Derived {
    public:
        explicit DerivedDerived(int dd) noexcept : Derived{0}, dd_{dd} {}
        int GetDD() const noexcept { return dd_; }

    protected:
        virtual bool is_equal(Base const& rhs) const noexcept
        {
            // operator==によりrhsの型はDerivedDerivedであるため、下記のキャストは安全
            auto const& rhs_d = static_cast<DerivedDerived const&>(rhs);

            return Derived::is_equal(rhs) && dd_ == rhs_d.dd_;
        }

    private:
        int dd_;
    };
```

前例では「両辺の型が等しいこと」が「等価であること」の必要条件となるが、
この要件が、すべてのoperator==に求められるわけではない。

次に示すのは、一見すると両辺の型が違うにもかかわらず、
等価性のセマンティクスを満たしている例である。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 317

    auto abc = std::string{"abc"};

    ASSERT_TRUE("abc" == abc);
    ASSERT_TRUE(abc == "abc");
```

これは、文字列リテラルを第1引数に取るstd::stringのコンストラクタが非explicitであることによって、
文字列リテラルからstd::stringへの[暗黙の型変換](core_lang_spec.md#SS_19_6_2_2)が起こるために成立する。

以上で見てきたように、等価性のセマンティクスを守ったoperator==の実装には多くの観点が必要になる。

### copyセマンティクス <a id="SS_21_3_2"></a>
copyセマンティクスとは以下を満たすようなセマンティクスである。

* a = bが行われた後に、aとbが等価である。
* a = bが行われた前後でbの値が変わっていない。

従って、これらのオブジェクトに対して[等価性のセマンティクス](cpp_idioms.md#SS_21_3_1)
を満たすoperator==が定義されている場合、
以下を満たすようなセマンティクスであると言い換えることができる。

* a = bが行われた後に、a == bがtrueになる。
* b == b_preがtrueの時に、a = bが行われた後でもb == b_preがtrueとなる。

下記に示す通り、std::stringはcopyセマンティクスを満たしている。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 331

    auto c_str = "string";
    auto str   = std::string{};

    str = c_str;
    ASSERT_TRUE(c_str == str);      // = 後には == が成立している
    ASSERT_STREQ("string", c_str);  // c_strの値は変わっていない
```

一方で、std::auto_ptrはcopyセマンティクスを満たしていない。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 344

    std::auto_ptr<std::string> str0{new std::string{"string"}};
    std::auto_ptr<std::string> str0_pre{new std::string{"string"}};

    ASSERT_TRUE(*str0 == *str0_pre);  // 前提は成立

    std::auto_ptr<std::string> str1;

    str1 = str0;

    // ASSERT_TRUE(*str0 == *str0_pre);  // これをするとクラッシュする
    ASSERT_TRUE(str0.get() == nullptr);  // str0の値がoperator ==で変わってしまった

    ASSERT_TRUE(*str1 == *str0_pre);  // これは成立

```

この仕様は極めて不自然であり、std::auto_ptrはC++11で非推奨となり、C++17で規格から排除された。

下記の単体テストから明らかな通り、
「[等価性のセマンティクス](cpp_idioms.md#SS_21_3_1)」で示した最後の例も、copyセマンティクスを満たしていない。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 364

    auto b = Base{1};
    auto d = Derived{1};

    b = d;  // スライシングが起こる

    ASSERT_FALSE(b == d);  // copyセマンティクスを満たしていない
```

原因は、copy代入で[スライシング](cpp_idioms.md#SS_21_7_3)が起こるためである。


### moveセマンティクス <a id="SS_21_3_3"></a>
moveセマンティクスとは以下を満たすようなセマンティクスである(operator==が定義されていると前提)。

* パフォーマンス要件  
    move代入の実行コスト <= copy代入の実行コスト(通常はmove代入の方が高速)

* 意味的要件  
    a == b が true の時に、c = std::move(a) を実行すると、  
    * b == c が true になる（値が保存される）
    * a == c は true にならなくても良い（aはmove後に不定状態になり得る）

* リソース管理   
    必須ではないが、aがポインタ等のリソースを保有している場合、
     move代入後にはそのリソースはcに移動していることが一般的である(「[rvalue](core_lang_spec.md#SS_19_7_1_2)」参照)

* エクセプション安全性  
    [no-fail保証](core_lang_spec.md#SS_19_13_1)をする(noexceptと宣言し、エクセプションをthrowしない)

moveセマンティクスは、使用後に破棄されるオブジェクト(主にrvalue)からの代入処理の実行コストを削減するために導入された。

下記のクラスのmove代入の内部処理はcopy代入が行われており、
moveセマンティクスの目的である「パフォーマンスの向上」が達成されない。

そのため、このようなmove代入は避けるべきである。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 379

    class IneffcientMove {
    public:
        IneffcientMove(char const* name) : name_{name} {}
        std::string const& Name() const noexcept { return name_; }

        IneffcientMove& operator=(IneffcientMove&& rhs)  // move代入、noexceptなし(非推奨)
        {
            name_ = rhs.name_;  // NG: rhs.name_をcopy代入している
                                //     std::move(rhs.name_)を使うべき
            return *this;
        }

    private:
        std::string name_;
    };

    bool operator==(IneffcientMove const& lhs, IneffcientMove const& rhs) noexcept { return lhs.Name() == rhs.Name(); }

    TEST(Semantics, move1)
    {
        auto a = IneffcientMove{"a"};
        auto b = IneffcientMove{"a"};

        ASSERT_EQ("a", a.Name());
        ASSERT_TRUE(a == b);

        auto c = IneffcientMove{"c"};
        ASSERT_EQ("c", c.Name());

        c = std::move(a);
        ASSERT_TRUE(b == c);  // 意味的には正しいが、内部でcopyが発生している(非効率)
    }

```

下記のコードのようにメンバの代入もできる限りmove代入を使うことで、
パフォーマンスの良い代入ができる。

```cpp
    //  example/cpp_idioms/semantics_ut.cpp 415

    class EfficientMove {
    public:
        EfficientMove(char const* name) : name_{name} {}
        std::string const& Name() const noexcept { return name_; }

        EfficientMove& operator=(EfficientMove&& rhs) noexcept  // move代入、no-fail保証
        {
            name_ = std::move(rhs.name_);  // OK: rhs.name_からname_へのmove代入
                                           //     リソース(文字列バッファ)をmove
            return *this;
        }

    private:
        std::string name_;
    };

    bool operator==(EfficientMove const& lhs, EfficientMove const& rhs) noexcept { return lhs.Name() == rhs.Name(); }

    TEST(Semantics, move2)
    {
        auto a = EfficientMove{"a"};
        auto b = EfficientMove{"a"};

        ASSERT_EQ("a", a.Name());
        ASSERT_TRUE(a == b);

        auto c = EfficientMove{"c"};
        ASSERT_EQ("c", c.Name());

        c = std::move(a);     // これ以降aは使ってはならない（aは不定状態）
        ASSERT_TRUE(b == c);  // moveセマンティクスを正しく守り、かつ効率的
    }

```

### MoveAssignable要件 <a id="SS_21_3_4"></a>
MoveAssignable要件は、C++において型がmove代入をサポートするために満たすべき条件を指す。
move代入はリソースを効率的に転送する操作であり、以下の条件を満たす必要がある。

1. リソースの移動  
   move代入では、リソース(動的メモリ等)が代入元から代入先へ効率的に転送される。

2. 有効だが未定義の状態  
   move代入後、代入元のオブジェクトは有効ではあるが未定義の状態となる。
   未定義の状態とは、破棄や再代入が可能である状態を指し、それ以外の操作は保証されない。

3. 自己代入の安全性  
   同一のオブジェクトをmove代入する場合でも、未定義動作やリソースリークを引き起こしてはならない。

4. 効率性  
   move代入は通常、copy代入よりも効率的であることが求められる。
   これは、リソースの複製を避けることで達成される(「[moveセマンティクス](cpp_idioms.md#SS_21_3_3)」参照)。

5. デフォルト実装  
   move代入演算子が明示的に定義されていない場合でも、
   クラスが一定の条件(例: move不可能なメンバが存在しないこと)を満たしていれば、
   コンパイラがデフォルトの実装(「[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)」参照)を生成する。

### CopyAssignable要件 <a id="SS_21_3_5"></a>
CopyAssignable要件は、C++において型がcopy代入をサポートするために満たすべき条件を指す。

1. 動作が定義されていること  
   代入操作は未定義動作を引き起こしてはならない。自己代入（同じオブジェクトを代入する場合）においても正しく動作し、
   リソースリークを引き起こさないことが求められる。

2. 値の保持  
   代入後、代入先のオブジェクトの値は代入元のオブジェクトの値と一致していなければならない。

3. 正しいセマンティクス  
   copy代入によって代入元のオブジェクトが変更されてはならない(「[copyセマンティクス](cpp_idioms.md#SS_21_3_2)」参照)。
   代入先のオブジェクトが保持していたリソース(例: メモリ)は適切に解放される必要がある。

4. デフォルト実装  
   copy代入演算子が明示的に定義されていない場合でも、
   クラスが一定の条件(例: copy不可能なメンバが存在しないこと)を満たしていれば、
   コンパイラがデフォルトの実装(「[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)」参照)を生成する。

## 関数設計のガイドライン <a id="SS_21_4"></a>
### 関数の引数と戻り値の型 <a id="SS_21_4_1"></a>
関数の引数型および戻り値型に関するガイドラインを以下の表で表す。

<table>
  <tr bgcolor="#cccccc">
    <th style="text-align: center;"> </th>
    <th style="text-align: center;">copy/moveが低コスト</th>
    <th style="text-align: center;">copyが高コスト/moveが低コスト</th>
    <th style="text-align: center;">moveが高コスト</th>
    <th style="text-align: center;">fがヌルを扱う</th>
  </tr>
  <tr>
    <td style="text-align: center;">in</td>
    <td style="text-align: center;"><code>f(X)</code></td>
    <td colspan="2" style="text-align: center;"><code>f(X const&)</code></td>
    <td style="text-align: center;"><code>f(X const\*)</code></td>
  </tr>
  <tr>
    <td style="text-align: center;">in/out</td>
    <td colspan="3" style="text-align: center;"><code>f(X&)</code></td>
    <td style="text-align: center;"><code>f(X\*)</code></td>
  </tr>
  <tr>
    <td style="text-align: center;">out</td>
    <td colspan="2" style="text-align: center;"><code>X f()</code></td>
    <td style="text-align: center;"><code>f(X&)</code></td>
    <td style="text-align: center;"><code>f(X\*)</code></td>
  </tr>
  <tr>
    <td style="text-align: center;">move</td>
    <td colspan="3" style="text-align: center;"><code>f(X&&)</code></td>
    <td style="text-align: center;">-</td>
  </tr>
  <tr>
    <td style="text-align: center;">forward</td>
    <td colspan="3" style="text-align: center;"><code>template&lt;typename T&gt; f(T&&)</code></td>
    <td style="text-align: center;">-</td>
  </tr>
</table>

[注] Xは任意の型  

[注] `templat<typename T> f(T&&)`の`T&&`は[forwardingリファレンス](core_lang_spec.md#SS_19_8_3)である。  

[注] 以下のような引数型は避けるべきである。  

* `X const*`
* `X*`
* `X&`


### サイクロマティック複雑度のクライテリア <a id="SS_21_4_2"></a>
関数構造の適・不適については、[サイクロマティック複雑度](cpp_idioms.md#SS_21_9_8)によって下記テーブルのように定義する。

| サイクロマティック複雑度(CC) | 複雑さの状態                                     |
| :--------------------------: | :----------------------------------------------- |
|            CC <= 10          | 非常に良い構造(適)                               |
|       11 < CC <  30          | やや複雑(概ね適)                                 |
|       31 < CC <  50          | 構造的なリスクあり(場合により不適)               |
|       51 < CC                | テスト不可能、デグレードリスクが非常に高い(不適) |

### 関数の行数のクライテリア <a id="SS_21_4_3"></a>
C++の創始者であるビャーネ・ストラウストラップ氏は、
  [プログラミング言語C++ 第4版](https://www.amazon.co.jp/%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0%E8%A8%80%E8%AA%9EC-%E7%AC%AC4%E7%89%88-%E3%83%93%E3%83%A3%E3%83%BC%E3%83%8D%E3%83%BB%E3%82%B9%E3%83%88%E3%83%A9%E3%82%A6%E3%82%B9%E3%83%88%E3%83%A9%E3%83%83%E3%83%97-ebook/dp/B01BGEO9MS)
  の中で、下記のように述べている。

```
    約 40 行を関数の上限にすればよい。 
    私自身は、もっと小さい平均 7 行程度を理想としている。 
```

## クラス設計のガイドライン <a id="SS_21_5"></a>
### ゼロの原則(Rule of Zero) <a id="SS_21_5_1"></a>
「ゼロの原則」は、リソース管理を直接クラスで行わず、
リソース管理を専門とするクラス
(例: 標準ライブラリの[RAII(scoped guard)](design_pattern.md#SS_9_10)クラス)に任せる設計ガイドラインを指す。
この法則に従うと、自身で特殊メンバ関数を定義する必要がなくなる。

```cpp
    //  example/cpp_idioms/rule_of_zero_ut.cpp 9

    class RuleZero {
    public:
        RuleZero(std::list<std::string> const& strs, std::string const& s) : strs_{strs}, s_{s} {}
        std::list<std::string> const& GetStrs() const noexcept { return strs_; }
        std::string const&            GetStr() const noexcept { return s_; }

        // 特殊メンバ関数は、メンバの特殊メンバ関数に任せる
    private:
        std::list<std::string> strs_{};
        std::string            s_{};
    };
```
```cpp
    //  example/cpp_idioms/rule_of_zero_ut.cpp 26

    auto z = RuleZero(std::list<std::string>{"1", "2", "3"}, "str");

    auto copied = z;             // コピーは自動生成に任せる(ゼロの原則)
    auto moved  = std::move(z);  // ムーブも自動生成に任せる(ゼロの原則)

    ASSERT_EQ(copied.GetStr(), moved.GetStr());
    ASSERT_EQ(copied.GetStrs(), moved.GetStrs());
```

クラスがリソースを直接管理する場合、メモリリークや二重解放などのリスクを伴う。
上記のように信頼性の高いクラスに特殊メンバ関数の処理を任せることにより、
クラス自体にリソース管理の責任を持たせる必要がなくなる。

### 五の原則(Rule of Five) <a id="SS_21_5_2"></a>
「五の原則」は、
クラスがリソース(例: 動的メモリやファイルハンドルなど)を管理する場合、
デフォルトコンストラクタを除く[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)、
つまり以下の5つの関数をすべて適切に定義する必要があるという設計ガイドラインを指す。

* デストラクタ
* コピーコンストラクタ
* コピー代入演算子
* ムーブコンストラクタ
* ムーブ代入演算子

特殊メンバ関数の挙動を正しく定義しないと、
リソースの不適切な管理(例: メモリリーク、リソースの二重解放)を招く可能性がある。
自動生成されるメンバ関数では、
複雑なリソース管理の要件を満たせないことがある(「[シャローコピー](cpp_idioms.md#SS_21_7_1)」参照)。

なお、「五の原則」は、「六の原則」と呼ばれることもある。
その場合、この原則が対象とする関数は、
[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)のすべてとなる。

このガイドラインに従って、コピーやムーブを実装する場合、

* [等価性のセマンティクス](cpp_idioms.md#SS_21_3_1)
* [copyセマンティクス](cpp_idioms.md#SS_21_3_2)
* [moveセマンティクス](cpp_idioms.md#SS_21_3_3)

に従わなけならない。

### クラス凝集性のクライテリア <a id="SS_21_5_3"></a>
クラス構造の適・不適については、[LCOM](cpp_idioms.md#SS_21_9_9_2)によって下記テーブルのように定義する。

| 凝集性の欠如(LCOM)  |  クラスの状態              |
|:-------------------:|:--------------------------:|
|       `LCOM <= 0.4` | 理想的な状態(適)           |
|`0.4 <  LCOM <  0.6` | 要注意状態(場合により不適) |
|`0.6 <= LCOM`        | 改善必須状態(不適)         |


* `LCOM <= 0.4`  
  クラスが非常に凝集しており、[単一責任の原則(SRP)](solid.md#SS_8_1)を強く遵守している状態であるため、
  通常、デザインの見直しは不要である。

* `0.4 < LCOM < 0.6`  
  クラスの凝集性がやや弱くなり始めている。
  デザイン見直しの必要な時期が迫りつつあると考えるべきだろう。
  このタイミングであればリファクタリングは低コストで完了できるだろう。

* `0.6 <= LCOM`  
  クラス内のメンバ関数間の関連性が低く、凝集性が不十分である。
  メンバ関数が異なる責務にまたがっている可能性が高いため、
  一刻も早くデザインの見直しを行うべきだろう。


## コーディングスタイル <a id="SS_21_6"></a>
### AAAスタイル <a id="SS_21_6_1"></a>
このドキュメントでのAAAとは、単体テストのパターンarrange-act-assertではなく、
almost always autoを指し、
AAAスタイルとは、「可能な場合、型を左辺に明示して変数を宣言する代わりに、autoを使用する」
というコーディングスタイルである。
この用語は、Andrei Alexandrescuによって造られ、Herb Sutterによって広く推奨されている。

特定の型を明示して使用する必要がない場合、下記のように書く。

```cpp
    //  example/cpp_idioms/aaa.cpp 11

    auto i  = 1;
    auto ui = 1U;
    auto d  = 1.0;
    auto s  = "str";
    auto v  = {0, 1, 2};

    for (auto i : v) {
        // 何らかの処理
    }

    auto add = [](auto lhs, auto rhs) {  // -> return_typeのような記述は不要
        return lhs + rhs;                // addの型もautoで良い
    };

    // 上記変数の型の確認
    static_assert(std::is_same_v<decltype(i), int>);
    static_assert(std::is_same_v<decltype(ui), unsigned int>);
    static_assert(std::is_same_v<decltype(d), double>);
    static_assert(std::is_same_v<decltype(s), char const*>);
    static_assert(std::is_same_v<decltype(v), std::initializer_list<int>>);

    char s2[] = "str";  // 配列の宣言には、AAAは使えない
    static_assert(std::is_same_v<decltype(s2), char[4]>);

    int* p0 = nullptr;  // 初期値がnullptrであるポインタの初期化には、AAAは使うべきではない
    auto p1 = static_cast<int*>(nullptr);  // NG
    auto p2 = p0;                          // OK
    auto p3 = nullptr;                     // NG 通常、想定通りにならない
    static_assert(std::is_same_v<decltype(p3), std::nullptr_t>);
```

特定の型を明示して使用する必要がある場合、下記のように書く。

```cpp
    //  example/cpp_idioms/aaa.cpp 51

    auto b  = new char[10]{0};
    auto v  = std::vector<int>{0, 1, 2};
    auto s  = std::string{"str"};
    auto sv = std::string_view{"str"};

    static_assert(std::is_same_v<decltype(b), char*>);
    static_assert(std::is_same_v<decltype(v), std::vector<int>>);
    static_assert(std::is_same_v<decltype(s), std::string>);
    static_assert(std::is_same_v<decltype(sv), std::string_view>);

    // 大量のstd::stringオブジェクトを定義する場合
    using std::literals::string_literals::operator""s;

    auto s_0 = "222"s;  // OK
    // ...
    auto s_N = "222"s;  // OK

    static_assert(std::is_same_v<decltype(s_0), std::string>);
    static_assert(std::is_same_v<decltype(s_N), std::string>);

    // 大量のstd::string_viewオブジェクトを定義する場合
    using std::literals::string_view_literals::operator""sv;

    auto sv_0 = "222"sv;  // OK
    // ...
    auto sv_N = "222"sv;  // OK

    static_assert(std::is_same_v<decltype(sv_0), std::string_view>);
    static_assert(std::is_same_v<decltype(sv_N), std::string_view>);

    std::mutex mtx;  // std::mutexはmove出来ないので、AAAスタイル不可
    auto       lock = std::lock_guard{mtx};

    static_assert(std::is_same_v<decltype(lock), std::lock_guard<std::mutex>>);
```

関数の戻り値を受け取る変数を宣言する場合、下記のように書く。

```cpp
    //  example/cpp_idioms/aaa.cpp 94

    auto v = std::vector<int>{0, 1, 2};

    // AAAを使わない例
    std::vector<int>::size_type t0{v.size()};      // 正確に書くとこうなる
    std::vector<int>::iterator  itr0 = v.begin();  // 正確に書くとこうなる

    std::unique_ptr<int> p0 = std::make_unique<int>(3);

    // 上記をAAAにした例
    auto t1   = v.size();   // size()の戻りは算術型であると推測できる
    auto itr1 = v.begin();  // begin()の戻りはイテレータであると推測できる

    auto p1 = std::make_unique<int>(3);  // make_uniqueの戻りはstd::unique_ptrであると推測できる
```

ただし、関数の戻り値型が容易に推測しがたい下記のような場合、
型を明示しないAAAスタイルは使うべきではない。

```cpp
    //  example/cpp_idioms/aaa.cpp 118

    extern std::map<std::string, int> gen_map();

    // 上記のような複雑な型を戻す関数の場合、AAAを使うと可読性が落ちる
    auto map0 = gen_map();

    for (auto [str, i] : gen_map()) {
        // 何らかの処理
    }

    // 上記のような複雑な型を戻す関数の場合、AAAを使うと可読性が落ちるため、AAAにしない
    std::map<std::string, int> map1 = gen_map();  // 型がコメントとして役に立つ

    for (std::pair<std::string, int> str_i : gen_map()) {
        // 何らかの処理
    }

    // 型を明示したAAAスタイルでも良い
    auto map2 = std::map<std::string, int>{gen_map()};  // 型がコメントとして役に立つ
```

インライン関数や関数テンプレートの宣言は、下記のように書く。

```cpp
    //  example/cpp_idioms/aaa.cpp 145

    template <typename F, typename T>
    auto apply_0(F&& f, T value)
    {
        return f(value);
    }
```

ただし、インライン関数や関数テンプレートが複雑な下記のような場合、
AAAスタイルは出来る限り避けるべきである。

```cpp
    //  example/cpp_idioms/aaa.cpp 153

    template <typename F, typename T>
    auto apply_1(F&& f, T value) -> decltype(f(std::declval<T>()))  // autoを使用しているが、AAAではない
    {
        auto cond  = false;
        auto param = value;

        // 複雑な処理

        if (cond) {
            return f(param);
        }
        else {
            return f(value);
        }
    }
```

このスタイルには下記のような狙いがある。

* コードの安全性の向上  
  autoで宣言された変数は未初期化にすることができないため、未初期化変数によるバグを防げる。
  また、下記のように縮小型変換(下記では、unsignedからsignedの変換)を防ぐこともできる。

```cpp
    //  example/cpp_idioms/aaa.cpp 180

    auto v = std::vector<int>{0, 1, 2};

    int t0 = v.size();  // 縮小型変換されるため、バグが発生する可能性がある
    // int t1{v.size()};   縮小型変換のため、コンパイルエラー
    auto t2 = v.size();  // t2は正確な型
```

* コードの可読性の向上  
  冗長なコードを排除することで、可読性の向上が見込める。

* コードの保守性の向上  
  「変数宣言時での左辺と右辺を同一の型にする」非AAAスタイルは
  [DRYの原則](https://ja.wikipedia.org/wiki/Don%27t_repeat_yourself#:~:text=Don't%20repeat%20yourself%EF%BC%88DRY,%E3%81%A7%E3%81%AA%E3%81%84%E3%81%93%E3%81%A8%E3%82%92%E5%BC%B7%E8%AA%BF%E3%81%99%E3%82%8B%E3%80%82)
  に反するが、この観点において、AAAスタイルはDRYの原則に沿うため、
  コード修正時に型の変更があった場合でも、それに付随したコード修正を最小限に留められる。


AAAスタイルでは、以下のような場合に注意が必要である。

* 関数の戻り値をautoで宣言された変数で受ける場合  
  上記で述べた通り、AAAの過剰な仕様は、可読性を下げてしまう。

* autoで推論された型が直感に反する場合  
  下記のような型推論は、直感に反する場合があるため、autoの使い方に対する習熟が必要である。

```cpp
    //  example/cpp_idioms/aaa.cpp 194

    auto str0 = "str";
    static_assert(std::is_same_v<char const*, decltype(str0)>);  // str0はchar[4]ではない

    // char[]が必要ならば、AAAを使わずに下記のように書く
    char str1[] = "str";
    static_assert(std::is_same_v<char[4], decltype(str1)>);

    // &が必要になるパターン
    class X {
    public:
        explicit X(int32_t a) : a_{a} {}
        int32_t& Get() { return a_; }

    private:
        int32_t a_;
    };

    X x{3};

    auto a0 = x.Get();
    ASSERT_EQ(3, a0);

    a0 = 4;
    ASSERT_EQ(4, a0);
    ASSERT_EQ(3, x.Get());  // a0はリファレンスではないため、このような結果になる

    // X::a_のリファレンスが必要ならば、下記のように書く
    auto& a1 = x.Get();
    a1       = 4;
    ASSERT_EQ(4, a1);
    ASSERT_EQ(4, x.Get());  // a1はリファレンスであるため、このような結果になる

    // constが必要になるパターン
    class Y {
    public:
        std::string&       Name() { return name_; }
        std::string const& Name() const { return name_; }

    private:
        std::string name_{"str"};
    };

    auto const y = Y{};

    auto        name0 = y.Name();  // std::stringがコピーされる
    auto&       name1 = y.Name();  // name1はconstに見えない
    auto const& name2 = y.Name();  // このように書くべき

    static_assert(std::is_same_v<std::string, decltype(name0)>);
    static_assert(std::is_same_v<std::string const&, decltype(name1)>);
    static_assert(std::is_same_v<std::string const&, decltype(name2)>);

    // 範囲for文でのauto const&
    auto const v = std::vector<std::string>{"0", "1", "2"};

    for (auto s : v) {  // sはコピー生成される
        static_assert(std::is_same_v<std::string, decltype(s)>);
    }

    for (auto& s : v) {  // sはconstに見えない
        static_assert(std::is_same_v<std::string const&, decltype(s)>);
    }

    for (auto const& s : v) {  // このように書くべき
        static_assert(std::is_same_v<std::string const&, decltype(s)>);
    }
```
 
### east-const <a id="SS_21_6_2"></a>
east-constとは、`const`修飾子を修飾する型要素の右側(east＝右)に置くコーディングスタイルのこと。
つまり「`const`はどの対象を修飾するか」を明確にするため、被修飾対象の直後に const を書くのが特徴である。

このスタイルは、C言語由来の「`const`を左に置く」スタイル([west-const](cpp_idioms.md#SS_21_6_3))に比べ、
テンプレート展開や型推論の際に一貫性があり、C++コミュニティではしばしば論理的・直感的と評価されている。

```cpp
    //  example/cpp_idioms/east_west_const.cpp 11

    char              str[] = "hehe";  // 配列strに書き込み可能
    char const*       str0  = str;  // str0が指すオブジェクトはconstなので、*str0への書き込み不可
    char* const       str1  = str;  // str1がconstなので、str1への代入不可
    char const* const str2  = str;  // *str2への書き込み不可、str2への代入不可

    auto lamda = [](char const(&str_ref)[5]) {  // str_refは配列へのconstリファレンス
        int ret = 0;

        for (char const& a : str_ref) {  // aはchar constリファレンス
            ret += a;
        }
        return ret;
    };
```

このスタイルは 「east constスタイル」 または 「右側const」と呼ばれ、
typeid のデマングル結果や Itanium C++ ABI でもこの形式が採用されている。

### west-const <a id="SS_21_6_3"></a>
west-constとは、`const`修飾子を型の左側(west＝左)に置くコーディングスタイルのこと。
C言語からの伝統的な表記法であり、多くの標準ライブラリや教科書でも依然としてこの書き方が用いられている。

可読性は慣れに依存するが、`const`の位置が一貫しないケース(`T* const`など)では理解しづらくなることもある。

```cpp
    //  example/cpp_idioms/east_west_const.cpp 34

    char              str[] = "hehe";  // 配列strに書き込み可能
    const char*       str0  = str;  // str0が指すオブジェクトはconstなので、*str0への書き込み不可
    char* const       str1  = str;  // str1がconstなので、str1への代入不可
    const char* const str2  = str;  // *str2への書き込み不可、str2への代入不可

    auto lamda = [](const char(&str_ref)[5]) {  // str_refは配列へのconstリファレンス
        int ret = 0;

        for (const char& a : str_ref) {  // aはchar constリファレンス
            ret += a;
        }
        return ret;
    };
```

このスタイルは「west constスタイル」または「左側const」と呼ばれ、
C言語文化圏での可読性・慣習を重視する場合に採用されることが多い。

## オブジェクトのコピー <a id="SS_21_7"></a>
### シャローコピー <a id="SS_21_7_1"></a>
シャローコピー(浅いコピー)とは、暗黙的、
もしくは=defaultによってコンパイラが生成するようなcopyコンストラクタ、
copy代入演算子が行うコピーであり、[ディープコピー](cpp_idioms.md#SS_21_7_2)と対比的に使われる概念である。

以下のクラスShallowOKには、コンパイラが生成するcopyコンストラクタ、
copy代入演算子と同等なものを定義したが、これは問題のないシャローコピーである
(が、正しく自動生成される関数を実装すると、メンバ変数が増えた際にバグを生み出すことがあるため、
実践的にはこのようなことはすべきではない)。

```cpp
    //  example/cpp_idioms/deep_shallow_copy_ut.cpp 7

    class ShallowOK {
    public:
        explicit ShallowOK(char const* str = "") : str_{std::string{str}} {}
        std::string const& GetString() const noexcept { return str_; }

        // 下記2関数を定義しなければ、以下と同等なcopyコンストラクタ、copy代入演算子が定義される。
        ShallowOK(ShallowOK const& rhs) : str_{rhs.str_} {}

        ShallowOK& operator=(ShallowOK const& rhs)
        {
            str_ = rhs.str_;
            return *this;
        }

    private:
        std::string str_;
    };
```

コンストラクタでポインタのようなリソースを確保し、
デストラクタでそれらを解放するようなクラスの場合、シャローコピーは良く知られた問題を起こす。

下記のShallowNGはその例である。

```cpp
    //  example/cpp_idioms/deep_shallow_copy_ut.cpp 43

    class ShallowNG {
    public:
        explicit ShallowNG(char const* str = "") : str_{new std::string{str}} {}
        ~ShallowNG() { delete str_; }
        std::string const& GetString() const noexcept { return *str_; }

    private:
        std::string* str_;
    };
```

シャローコピーにより、メンバで保持していたポインタ(ポインタが指しているオブジェクトではない)
がコピーされてしまうため、下記のコード内のコメントで示した通り、
メモリリークや2重解放を起こしてしまう。

```cpp
    //  example/cpp_idioms/deep_shallow_copy_ut.cpp 60

    auto const s0 = ShallowNG{"s0"};

    // NG s0.str_とs1.str_は同じメモリを指すため~ShallowNG()に2重解放される。
    auto const s1 = ShallowNG{s0};

    auto s2 = ShallowNG{"s2"};

    // NG s2.str_が元々保持していたメモリは、解放できなくなる。
    s2 = s0;

    // NG s0.str_とs2.str_は同じメモリを指すため、
    //    s0、s2のスコープアウト時に、~ShallowNG()により、2重解放される。
```

### ディープコピー <a id="SS_21_7_2"></a>
ディープコピーとは、[シャローコピー](cpp_idioms.md#SS_21_7_1)が発生させる問題を回避したコピーである。

以下に例を示す。

```cpp
    //  example/cpp_idioms/deep_shallow_copy_ut.cpp 79

    class Deep {
    public:
        explicit Deep(char const* str = "") : str_{new std::string{str}} {}
        ~Deep() { delete str_; }
        std::string const& GetString() const noexcept { return *str_; }

        // copyコンストラクタの実装例
        Deep(Deep const& rhs) : str_{new std::string{*rhs.str_}} {}

        // copy代入演算子の実装例
        Deep& operator=(Deep const& rhs)
        {
            *str_ = *(rhs.str_);
            return *this;
        }

    private:
        std::string* str_;
    };

    class Deep2 {  // std::unique_ptrを使いDeepをリファクタリング
    public:
        explicit Deep2(char const* str = "") : str_{std::make_unique<std::string>(str)} {}
        std::string const& GetString() const { return *str_; }

        // copyコンストラクタの実装例
        Deep2(Deep2 const& rhs) : str_{std::make_unique<std::string>(*rhs.str_)} {}

        // copy代入演算子の実装例
        Deep2& operator=(Deep2 const& rhs)
        {
            *str_ = *(rhs.str_);
            return *this;
        }

    private:
        std::unique_ptr<std::string> str_;
    };
```

上記クラスのDeepは、copyコンストラクタ、copy代入演算子でポインタをコピーするのではなく、
ポインタが指しているオブジェクトを複製することにより、シャローコピーの問題を防ぐ。


### スライシング <a id="SS_21_7_3"></a>
オブジェクトのスライシングとは、

* クラスBaseとその派生クラスDerived
* クラスDerivedのインスタンスd1、d2(解説のために下記例ではd0も定義)
* d2により初期化されたBase&型のd2_ref(クラスBase型のリファレンス)

が宣言されたとした場合、 

```cpp
    d2_ref = d1;    // オブジェクトの代入
```

を実行した時に発生するようなオブジェクトの部分コピーのことである
(この問題はリファレンスをポインタに代えた場合にも起こる)。

以下のクラスと単体テストはこの現象を表している。

```cpp
    //  example/cpp_idioms/slice_ut.cpp 10

    class Base {
    public:
        explicit Base(char const* name) noexcept : name0_{name} {}
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
```

```cpp
    //  example/cpp_idioms/slice_ut.cpp 41

    auto const d0     = Derived{"d0", "d0"};
    auto const d1     = Derived{"d1", "d1"};
    auto       d2     = Derived{"d2", "d2"};
    Base&      d2_ref = d2;

    ASSERT_STREQ("d2", d2.Name0());  // OK
    ASSERT_STREQ("d2", d2.Name1());  // OK

    d2 = d0;
    ASSERT_STREQ("d0", d2.Name0());  // OK
    ASSERT_STREQ("d0", d2.Name1());  // OK

    d2_ref = d1;                     // d2_refはBase&型で、d2へのリファレンス
    ASSERT_STREQ("d1", d2.Name0());  // OK
    /*  本来なら↓が成立してほしいが.、、、
    ASSERT_STREQ("d1", d2.Name1()); */
    ASSERT_STREQ("d0", d2.Name1());  // スライシングの影響でDerived::name1_はコピーされない
```

copy代入演算子(=)によりコピーが行われた場合、=の両辺のオブジェクトは等価になるべきだが
(copy代入演算子をオーバーロードした場合も、そうなるように定義すべきである)、
スライシングが起こった場合、そうならないことが問題である(「[等価性のセマンティクス](cpp_idioms.md#SS_21_3_1)」参照)。

下記にこの現象の発生メカニズムについて解説する。

1. 上記クラスBase、Derivedのメモリ上のレイアウトは下記のようになる。

<!-- pu:essential/plant_uml/slicing_class.pu--><p><img src="data:image/png;base64,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" /></p>

2. 上記インスタンスd0、d1、d2、d2_refのメモリ上のレイアウトは下記のようになる。

<!-- pu:essential/plant_uml/slicing_init.pu--><p><img src="data:image/png;base64,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" /></p>

3. d2 = d0をした場合の状態は下記のようになる。

<!-- pu:essential/plant_uml/slicing_normal.pu--><p><img src="data:image/png;base64,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" /></p>

4. 上記の状態でd2_ref = d1をした場合の状態は下記のようになる。

<!-- pu:essential/plant_uml/slicing_slicing.pu--><p><img src="data:image/png;base64,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" /></p>

d2.name1\_の値が元のままであるが(これがスライシングである)、その理由は下記の疑似コードが示す通り、
「d2_refの表層型がクラスBaseであるためd1もクラスBase(正確にはBase型へのリファレンス)へ変換された後、
d2_refが指しているオブジェクト(d2)へコピーされた」からである。

```cpp
    d2_ref.Base::operator=(d1);   // Base::operator=(Base const&)が呼び出される
                                  // 関数Base::operator=(Base const&)の中では、
                                  // d1の型はBase型のリファレンスとなる
```

次に示すのは、
「オブジェクトの配列をその基底クラスへのポインタに代入し、
そのポインタを配列のように使用した場合に発生する」スライシングと類似の現象である。

```cpp
    //  example/cpp_idioms/slice_ut.cpp 64

    Derived d_array[]{{"0", "1"}, {"2", "3"}};
    Base*   b_ptr = d_array;  // この代入までは問題ないが、b_ptr[1]でのアクセスで問題が起こる

    ASSERT_STREQ("0", d_array[0].Name0());  // OK
    ASSERT_STREQ("0", b_ptr[0].Name0());    // OK

    ASSERT_STREQ("2", d_array[1].Name0());  // OK
    /* スライシングに類似した問題で、以下のテストは失敗する。
    ASSERT_STREQ("2", b_ptr[1].Name0());    NG */
    // こうすればテストは通るが、、、
    ASSERT_STREQ("1", b_ptr[1].Name0());  // NG
```

<!-- pu:essential/plant_uml/slicing_array.pu--><p><img src="data:image/png;base64,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" /></p>


## C++注意点 <a id="SS_21_8"></a>
### オーバーライドとオーバーロードの違い <a id="SS_21_8_1"></a>
下記例では、Base::g()がオーバーロードで、Derived::f()がオーバーライドである
(Derived::g()はオーバーロードでもオーバーライドでもない(「[name-hiding](core_lang_spec.md#SS_19_12_9)」参照))。


```cpp
    //  example/cpp_idioms/override_overload_ut.cpp 5

    class Base {
    public:
        virtual ~Base() = default;
        virtual std::string f() { return "Base::f"; }
        std::string         g() { return "Base::g"; }

        // g()のオーバーロード
        std::string g(int) { return "Base::g(int)"; }
    };

    class Derived : public Base {
    public:
        // Base::fのオーバーライド
        virtual std::string f() override { return "Derived::f"; }

        // Base::gのname-hiding
        std::string g() { return "Derived::g"; }
    };
```

下記図の通り、

* BaseのインスタンスはBase用のvtblへのポインタを内部に持ち、
  そのvtblでBase::f()のアドレスを保持する。
* DerivedのインスタンスはDerived用のvtblへのポインタを内部に持ち、
  そのvtblでDerived::f()のアドレスを保持する。
* Base::g()、Base::g(int)、
  Derived::g()のアドレスはBaseやDerivedのインスタンスから辿ることはできない。

<!-- pu:essential/plant_uml/vtbl.pu--><p><img src="data:image/png;base64,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" /></p>

vtblとは仮想関数テーブルとも呼ばれる、仮想関数ポインタを保持するための上記のようなテーブルである
(「[ポリモーフィックなクラス](core_lang_spec.md#SS_19_4_8)」参照)。

Base::f()、Derived::f()の呼び出し選択は、オブジェクトの表層の型ではなく、実際の型により決定される。
Base::g()、Derived::g()の呼び出し選択は、オブジェクトの表層の型により決定される。

```cpp
    //  example/cpp_idioms/override_overload_ut.cpp 29

    auto  ret   = std::string{};
    auto  b     = Base{};
    auto  d     = Derived{};
    Base& d_ref = d;

    ret = b.f();  // Base::f()呼び出し
    ASSERT_EQ("Base::f", ret);

    ret = d.f();  // Derived::f()呼び出し
    ASSERT_EQ("Derived::f", ret);

    ret = b.g();  // Base::g()呼び出し
    ASSERT_EQ("Base::g", ret);

    ret = d.g();  // Derived::g()呼び出し
    ASSERT_EQ("Derived::g", ret);
    // ret = d.g(int{});   // Derived::gによって、Base::gが隠されるのでコンパイルエラー

    ret = d_ref.f();  // Base::fはDerived::fによってオーバーライドされたので、Derived::f()呼び出し
    ASSERT_EQ("Derived::f", ret);

    ret = d_ref.g();  // d_refの表層型はBaseなので、Base::g()呼び出し
    ASSERT_EQ("Base::g", ret);

    ret = d_ref.g(int{});  // d_refの表層型はBaseなので、Base::g(int)呼び出し
    ASSERT_EQ("Base::g(int)", ret);
```

上記のメンバ関数呼び出し

```cpp
    d_ref.f() 
```

がどのように解釈され、Derived::f()が選択されるかを以下に疑似コードで例示する。

```cpp
    vtbl = d_ref.vtbl             // d_refの実態はDerivedなのでvtblはDerivedのvtbl

    member_func = vtbl->f         // vtbl->fはDerived::f()のアドレス

    (d_ref.*member_func)(&d_ref)  // member_func()の呼び出し
```

このようなメカニズムにより仮想関数呼び出しが行われる。

### danglingリファレンス <a id="SS_21_8_2"></a>
Dangling リファレンスとは、破棄後のオブジェクトを指しているリファレンスを指す。
このようなリファレンスにアクセスすると、[未定義動作](core_lang_spec.md#SS_19_14_3)に繋がるに繋がる。

```cpp
    //  example/cpp_idioms/dangling_ut.cpp 9

    bool X_destructed;
    class X {
    public:
        X() { X_destructed = false; }
        ~X() { X_destructed = true; }
    };

    bool A_destructed;
    class A {
    public:
        A() { A_destructed = false; }
        ~A() { A_destructed = true; }

        X const& GetX() const noexcept { return x_; }

    private:
        X x_;
    };

    //  example/cpp_idioms/dangling_ut.cpp 34

    auto a = A{};

    auto const& x_safe = a.GetX();  // x_safeはダングリングリファレンスではない
    ASSERT_FALSE(A_destructed || X_destructed);

    auto const& x_dangling = A{}.GetX();  // 次の行でxが指すオブジェクトは解放される
    // この行ではxはdangngling リファレンスになる。
    ASSERT_TRUE(A_destructed && X_destructed);

    auto const* x_ptr_dangling = &A{}.GetX();  // 次の行でxが指すオブジェクトは解放される
    // この行ではxはdangngling ポインタになる。
    ASSERT_TRUE(A_destructed && X_destructed);
```

### danglingポインタ <a id="SS_21_8_3"></a>
danglingポインタとは、[danglingリファレンス](cpp_idioms.md#SS_21_8_2)と同じような状態になったポインタを指す。


### Most Vexing Parse <a id="SS_21_8_4"></a>
Most Vexing Parse(最も困惑させる構文解析)とは、C++の文法に関連する問題で、
Scott Meyersが彼の著書"Effective STL"の中でこの現象に名前をつけたことに由来する。

この問題はC++の文法が関数の宣言と変数の定義とを曖昧に扱うことによって生じる。
特にオブジェクトの初期化の文脈で発生し、意図に反して、その行は関数宣言になってしまう。

```cpp
    //  example/cpp_idioms/most_vexing_parse_ut.cpp 6

    class Vexing {
    public:
        Vexing(int) {}
        Vexing() {}
    };

    //  example/cpp_idioms/most_vexing_parse_ut.cpp 21

    Vexing obj1();        // はローカルオブジェクトobj1の定義ではない
    Vexing obj2(Vexing);  // はローカルオブジェクトobj2の定義ではない
    Vexing(obj3);         // はローカルオブジェクトobj3の定義

    ASSERT_EQ("Vexing ()", Nstd::Type2Str<decltype(obj1)>());
    ASSERT_EQ("Vexing (Vexing)", Nstd::Type2Str<decltype(obj2)>());
    ASSERT_EQ("Vexing", Nstd::Type2Str<decltype(obj3)>());
    // 上記単体テストが示すように、
    //   * obj1はVexingを返す関数
    //   * obj2はVexingを引数に取りVexingを返す関数
    //   * obj3はVexing型のオブジェクト
    // となる。
```

[初期化子リストコンストラクタ](core_lang_spec.md#SS_19_6_1_1)の呼び出しでオブジェクトの初期化を行うことで、
このような問題を回避できる。

## ソフトウェア一般 <a id="SS_21_9"></a>
### ヒープ <a id="SS_21_9_1"></a>
ヒープとは、プログラム実行時に動的メモリ割り当てを行うためのメモリ領域である。
malloc、calloc、reallocといった関数を使用して必要なサイズのメモリを確保し、freeで解放する。
スタックとは異なり、プログラマが明示的にメモリ管理を行う必要があり、解放漏れはメモリリークを引き起こす。
ヒープ領域はスタックよりも大きく、動的なサイズのデータ構造や長寿命のオブジェクトに適しているが、
アクセス速度はスタックより遅い。また、断片化（フラグメンテーション）が発生しやすく、
連続的な割り当てと解放により利用可能なメモリが分散する課題がある。適切なヒープ管理は、
C/C++プログラミングにおける重要なスキルの一つである。

### スレッドセーフ <a id="SS_21_9_2"></a>
スレッドセーフとは「複数のスレッドから同時にアクセスされても、
排他制御などの機構([std::mutex](stdlib_and_concepts.md#SS_20_3_2))により共有データの整合性が保たれ、正しく動作する性質」である。

### リエントラント <a id="SS_21_9_3"></a>
リエントラントとは「実行中に同じ関数が再度呼び出されても、グローバル変数や静的変数に依存せず、
ローカル変数のみで動作するため正しく動作する性質」である。

一般に、リエントラントな関数は[スレッドセーフ](cpp_idioms.md#SS_21_9_2)であるが、逆は成り立たない。


### クリティカルセクション <a id="SS_21_9_4"></a>
複数のスレッドから同時にアクセスされると競合状態を引き起こす可能性があるコード領域をクリティカルセクションと呼ぶ。
典型的には、共有変数や共有データ構造を読み書きするコード部分がこれに該当する。
クリティカルセクションは、[std::mutex](stdlib_and_concepts.md#SS_20_3_2)等の排他制御機構によって保護し、
一度に一つのスレッドのみが実行できるようにする必要がある。

### スピンロック <a id="SS_21_9_5"></a>
スピンロックとは、
スレッドがロックを取得できるまでCPUを占有したままビジーループで待機する排他制御方式である。
スリープを伴わずカーネルを呼び出さないため、短時間の競合では高速に動作するが、
長時間の待機ではCPUを浪費しやすい。リアルタイム処理や割り込み制御に適する。

C++11では、スピンロックは[std::atomic](stdlib_and_concepts.md#SS_20_3_3)を使用して以下のように定義できる。

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

以下の単体テスト(「[std::mutex](stdlib_and_concepts.md#SS_20_3_2)」の単体テストを参照)
に示したように[std::scoped_lock](stdlib_and_concepts.md#SS_20_4_3)のテンプレートパラメータとして使用できる。

```cpp
    //  example/cpp_idioms/spin_lock_ut.cpp 11

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
    //  example/cpp_idioms/spin_lock_ut.cpp 27

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

### ハンドル <a id="SS_21_9_6"></a>
CやC++の文脈でのハンドルとは、ポインタかリファレンスを指す。

### フリースタンディング環境 <a id="SS_21_9_7"></a>
[フリースタンディング環境](https://ja.wikipedia.org/wiki/%E3%83%95%E3%83%AA%E3%83%BC%E3%82%B9%E3%82%BF%E3%83%B3%E3%83%87%E3%82%A3%E3%83%B3%E3%82%B0%E7%92%B0%E5%A2%83)
とは、組み込みソフトウェアやOSのように、その実行にOSの補助を受けられないソフトウエアを指す。

### サイクロマティック複雑度 <a id="SS_21_9_8"></a>
[サイクロマティック複雑度](https://ja.wikipedia.org/wiki/%E5%BE%AA%E7%92%B0%E7%9A%84%E8%A4%87%E9%9B%91%E5%BA%A6)
とは関数の複雑さを表すメトリクスである。


### 凝集性 <a id="SS_21_9_9"></a>
[凝集性(凝集度)](https://ja.wikipedia.org/wiki/%E5%87%9D%E9%9B%86%E5%BA%A6)
とはクラス設計の妥当性を表す尺度の一種であり、
「[凝集性の欠如](cpp_idioms.md#SS_21_9_9_1)(LCOM)」というメトリクスで計測される。

* [凝集性の欠如](cpp_idioms.md#SS_21_9_9_1)メトリクスの値が1に近ければ凝集性は低く、この値が0に近ければ凝集性は高い。
* メンバ変数やメンバ関数が多くなれば、凝集性は低くなりやすい。
* 凝集性は、クラスのメンバがどれだけ一貫した責任を持つかを示す。
* 「[単一責任の原則(SRP)](solid.md#SS_8_1)」を守ると凝集性は高くなりやすい。
* 「[Accessor](design_pattern.md#SS_9_5)」を多用すれば、振る舞いが分散しがちになるため、通常、凝集性は低くなる。
   従って、下記のようなクラスは凝集性が低い。言い換えれば、凝集性を下げることなく、
   より小さいクラスに分割できる。
   なお、以下のクラスでは、LCOMが位置にに近い値となっており、凝集性が欠如していることがわかる。

```cpp
    //  example/cpp_idioms/lack_of_cohesion_ut.cpp 7

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
(ただし、「[Immutable](design_pattern.md#SS_9_7)」の観点からは、QuadraticEquation::Set()がない方が良い)。
言い換えれば、凝集性を落とさずにクラスを分割することは難しい。
なお、上記の凝集性を欠くクラスを凝集性が高くなるように修正した例を以下に示す。

```cpp
    //  example/cpp_idioms/lack_of_cohesion_ut.cpp 26

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

#### 凝集性の欠如 <a id="SS_21_9_9_1"></a>
[凝集性](cpp_idioms.md#SS_21_9_9)の欠如(Lack of Cohesion in Methods/LCOM)とは、
クラス設計の妥当性を表す尺度の一種であり、`0 ～ 1`の値で表すメトリクスである。

LCOMの値が大きい(1か1に近い値)場合、「クラス内のメンバ関数が互いに関連性を持たず、
それぞれが独立した責務やデータに依存するため、クラス全体の統一性が欠けている」ことを表す。

クラスデザイン見直しの基準値としてLCOMを活用する場合、[クラス凝集性のクライテリア](cpp_idioms.md#SS_21_5_3)に具体的な推奨値を示す。

#### LCOM <a id="SS_21_9_9_2"></a>
[凝集性の欠如](cpp_idioms.md#SS_21_9_9_1)とはLack of Cohesion in Methodsの和訳であり、LCOMと呼ばれる。

### Spurious Wakeup <a id="SS_21_9_10"></a>
[Spurious Wakeup](https://en.wikipedia.org/wiki/Spurious_wakeup)とは、
条件変数に対する通知待ちの状態であるスレッドが、その通知がされていないにもかかわらず、
起き上がってしまう現象のことを指す。

下記のようなstd::condition_variableの使用で起こり得る。

```cpp
    //  example/cpp_idioms/spurious_wakeup_ut.cpp 8

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
    //  example/cpp_idioms/spurious_wakeup_ut.cpp 34

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

### Static Initialization Order Fiasco(静的初期化順序問題) <a id="SS_21_9_11"></a>
静的初期化順序問題とは、
グローバルや名前空間スコープの静的オブジェクトの初期化順序が翻訳単位間で未定義であることに起因する不具合である。
あるオブジェクトAが初期化時に別のオブジェクトBに依存していても、Bがまだ初期化されていない場合、
Aの初期化は未定義の状態となり、不正アクセスやクラッシュを引き起こす可能性がある。

原因は、C++標準が同じ翻訳単位内の静的オブジェクトの初期化順序は保証するが、
異なる翻訳単位間の順序は保証しないことにある。さらに、動的初期化を必要とするオブジェクトでは、
初期化順序の依存関係が問題を起こす。

C++20からこの問題の対策として、[constinit](core_lang_spec.md#SS_19_5_8)が導入された。

### 副作用 <a id="SS_21_9_12"></a>
プログラミングにおいて、式の評価による作用には、
主たる作用とそれ以外の
[副作用](https://ja.wikipedia.org/wiki/%E5%89%AF%E4%BD%9C%E7%94%A8_(%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0))
(side effect)とがある。
式は、評価値を得ること(関数では「引数を受け取り値を返す」と表現する)が主たる作用とされ、
それ以外のコンピュータの論理的状態(ローカル環境以外の状態変数の値)を変化させる作用を副作用という。
副作用の例としては、グローバル変数や静的ローカル変数の変更、
ファイルの読み書き等のI/O実行、等がある。


### Itanium C++ ABI <a id="SS_21_9_13"></a>
ItaniumC++ABIとは、C++コンパイラ間でバイナリ互換性を確保するための規約である。
関数呼び出し規約、クラスレイアウト、仮想関数テーブル、例外処理、
名前修飾(マングリング)などC++のオブジェクト表現と呼び出し方法に関する標準ルールを定めている。

もともとはIntelItanium(IA-64)プロセッサ向けに策定されたが、
[g++](cpp_idioms.md#SS_21_10_1)や[clang++](cpp_idioms.md#SS_21_10_2)はx86/x86-64やARM64など多くのプラットフォームでもItaniumC++ABI準拠の規約を採用している。
そのため異なるコンパイラ間でもオブジェクトファイルやライブラリのリンクが可能である。
また、typeid(...).name()をデマングルした場合、
constがeast-const形式(T const)で表示されるのもこのABIの規約によるものである。

| ABI               | 主な対象プラットフォーム  | マングリング規則    | クラスレイアウト  | 例外処理    |
| ----------------- | ------------------------- | ------------------- | ----------------- | ----------- |
| **ItaniumC++ABI** | IA-64, x86, x86-64, ARM64 | east-const形式      | Itanium規則       | Itanium規則 |
| **MSVC C++ABI**   | Windows x86/x64           | 独自形式            | 独自規則          | 独自規則    |
| **ARM C++ABI**    | AArch32, AArch64          | 基本的にItanium準拠だが例外あり         | ARM規則     |


## C++コンパイラ <a id="SS_21_10"></a>
本ドキュメントで使用するg++/clang++のバージョンは以下のとおりである。

### g++ <a id="SS_21_10_1"></a>
```
    g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
    Copyright (C) 2021 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### clang++ <a id="SS_21_10_2"></a>
```
    Ubuntu clang version 14.0.0-1ubuntu1
    Target: x86_64-pc-linux-gnu
    Thread model: posix
    InstalledDir: /usr/bin
```

## 非ソフトウェア用語 <a id="SS_21_11"></a>
### セマンティクス <a id="SS_21_11_1"></a>
シンタックスとは構文論のことであり、セマンティクスとは意味論のことである。
セマンティクス、シンタックスの違いをはっきりと際立たせる以下の有名な例文により、
セマンティクスの意味を直感的に理解することができる。

```
    Colorless green ideas sleep furiously(直訳:無色の緑の考えが猛烈に眠る)
```

この文は文法的には正しい(シンタックス的に成立している)が、意味的には不自然で理解不能である
(セマンティクス的には破綻している)。ノーム・チョムスキーによって提示されたこの例文は、
構文が正しくても意味が成立しないことがあるという事実を示しており、構文と意味の違いを鮮やかに浮かび上がらせる。


### 割れ窓理論 <a id="SS_21_11_2"></a>
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


### 車輪の再発明 <a id="SS_21_11_3"></a>
[車輪の再発明](https://ja.wikipedia.org/wiki/%E8%BB%8A%E8%BC%AA%E3%81%AE%E5%86%8D%E7%99%BA%E6%98%8E)
とは、広く受け入れられ確立されている技術や解決法を（知らずに、または意図的に無視して）
再び一から作ること」を指すための慣用句である。
ソフトウェア開発では、STLのような優れたライブラリを使わずに、
それと同様なライブラリを自分たちで実装するような非効率な様を指すことが多い。



