<!-- deep/md/cpp_idiom.md -->
# C++慣用語 <a id="SS_20"></a>
この章では、C++慣用言句ついて解説を行う。

___

__この章の構成__

&emsp;&emsp; [ソフトウェア一般](cpp_idiom.md#SS_20_1)  
&emsp;&emsp;&emsp; [ハンドル](cpp_idiom.md#SS_20_1_1)  
&emsp;&emsp;&emsp; [フリースタンディング環境](cpp_idiom.md#SS_20_1_2)  
&emsp;&emsp;&emsp; [サイクロマティック複雑度](cpp_idiom.md#SS_20_1_3)  
&emsp;&emsp;&emsp; [凝集度](cpp_idiom.md#SS_20_1_4)  
&emsp;&emsp;&emsp;&emsp; [凝集度の欠如](cpp_idiom.md#SS_20_1_4_1)  
&emsp;&emsp;&emsp;&emsp; [LCOMの評価基準](cpp_idiom.md#SS_20_1_4_2)  

&emsp;&emsp;&emsp; [Spurious Wakeup](cpp_idiom.md#SS_20_1_5)  
&emsp;&emsp;&emsp; [副作用](cpp_idiom.md#SS_20_1_6)  

&emsp;&emsp; [オブジェクト指向](cpp_idiom.md#SS_20_2)  
&emsp;&emsp;&emsp; [is-a](cpp_idiom.md#SS_20_2_1)  
&emsp;&emsp;&emsp; [has-a](cpp_idiom.md#SS_20_2_2)  
&emsp;&emsp;&emsp; [is-implemented-in-terms-of](cpp_idiom.md#SS_20_2_3)  
&emsp;&emsp;&emsp;&emsp; [public継承によるis-implemented-in-terms-of](cpp_idiom.md#SS_20_2_3_1)  
&emsp;&emsp;&emsp;&emsp; [private継承によるis-implemented-in-terms-of](cpp_idiom.md#SS_20_2_3_2)  
&emsp;&emsp;&emsp;&emsp; [コンポジションによる(has-a)is-implemented-in-terms-of](cpp_idiom.md#SS_20_2_3_3)  

&emsp;&emsp; [C++注意点](cpp_idiom.md#SS_20_3)  
&emsp;&emsp;&emsp; [オーバーライドとオーバーロードの違い](cpp_idiom.md#SS_20_3_1)  
&emsp;&emsp;&emsp; [Most Vexing Parse](cpp_idiom.md#SS_20_3_2)  

&emsp;&emsp; [C++コンパイラ](cpp_idiom.md#SS_20_4)  
&emsp;&emsp;&emsp; [g++](cpp_idiom.md#SS_20_4_1)  
&emsp;&emsp;&emsp; [clang++](cpp_idiom.md#SS_20_4_2)  
  
  

[このドキュメントの構成](introduction.md#SS_1_7)に戻る。  

___

## ソフトウェア一般 <a id="SS_20_1"></a>
### ハンドル <a id="SS_20_1_1"></a>
CやC++の文脈でのハンドルとは、ポインタかリファレンスを指す。

### フリースタンディング環境 <a id="SS_20_1_2"></a>
[フリースタンディング環境](https://ja.wikipedia.org/wiki/%E3%83%95%E3%83%AA%E3%83%BC%E3%82%B9%E3%82%BF%E3%83%B3%E3%83%87%E3%82%A3%E3%83%B3%E3%82%B0%E7%92%B0%E5%A2%83)
とは、組み込みソフトウェアやOSのように、その実行にOSの補助を受けられないソフトウエアを指す。

### サイクロマティック複雑度 <a id="SS_20_1_3"></a>
[サイクロマティック複雑度](https://ja.wikipedia.org/wiki/%E5%BE%AA%E7%92%B0%E7%9A%84%E8%A4%87%E9%9B%91%E5%BA%A6)
とは関数の複雑さを表すメトリクスである。
このメトリクスの解釈は諸説あるものの、概ね以下のテーブルのようなものである。

|サイクロマティック複雑度(CC)|複雑さの状態                              |
|:--------------------------:|:-----------------------------------------|
|           CC <= 10         |非常に良い構造                            |
|      11 < CC <  30         |やや複雑                                  |
|      31 < CC <  50         |構造的なリスクあり                        |
|      51 < CC               |テスト不可能、デグレードリスクが非常に高い|

### 凝集度 <a id="SS_20_1_4"></a>
[凝集度](https://ja.wikipedia.org/wiki/%E5%87%9D%E9%9B%86%E5%BA%A6)
とはクラス設計の妥当性を表す尺度の一種であり、
「[凝集度の欠如](cpp_idiom.md#SS_20_1_4_1)(LCOM)」というメトリクスで計測される。

* [凝集度の欠如](cpp_idiom.md#SS_20_1_4_1)メトリクスの値が1に近ければ凝集度は低く、この値が0に近ければ凝集度は高い。
* メンバ変数やメンバ関数が多くなれば、凝集度は低くなりやすい。
* 凝集度は、クラスのメンバがどれだけ一貫した責任を持つかを示す。
* 「[単一責任の原則(SRP)](solid.md#SS_8_1)」を守ると凝集度は高くなりやすい。
* 「[Accessor](design_pattern.md#SS_9_5)」を多用すれば、振る舞いが分散しがちになるため、通常、凝集度は低くなる。
   従って、下記のようなクラスは凝集度が低い。言い換えれば、凝集度を下げることなく、
   より小さいクラスに分割できる。
   なお、以下のクラスでは、```LCOM == 9```となっており、凝集性が欠如していることがわかる。

```cpp
    //  example/cpp_idiom/lack_of_cohesion_ut.cpp 7

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

良く設計されたクラスは、下記のようにメンバが結合しあっているため凝集度が高い
(ただし、「[Immutable](design_pattern.md#SS_9_7)」の観点からは、QuadraticEquation::Set()がない方が良い)。
言い換えれば、凝集度を落とさずにクラスを分割することは難しい。
なお、上記の```LCOM == 9```なっているクラスを凝集性を高く、修正した例を以下に示す。

```cpp
    //  example/cpp_idiom/lack_of_cohesion_ut.cpp 26

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

#### 凝集度の欠如 <a id="SS_20_1_4_1"></a>
[凝集度](cpp_idiom.md#SS_20_1_4)の欠如(Lack of Cohesion in Methods/LCOM)とは、
クラス設計の妥当性を表す尺度の一種であり、`0 ～ 1`の値で表すメトリクスである。

LCOMの値が大きい(1か1に近い値)場合、「クラス内のメソッドが互いに関連性を持たず、
それぞれが独立した責務やデータに依存するため、クラス全体の統一性が欠けている」ことを表す。

クラスデザイン見直しの基準値としてLCOMを活用する場合、
[LCOMの評価基準](cpp_idiom.md#SS_20_1_4_2)に具体的な推奨値を示す。

#### LCOMの評価基準 <a id="SS_20_1_4_2"></a>
クラスデザイン良し悪しの基準値としてLCOMを活用する場合の推奨値を以下に示す。

| 凝集度の欠如(LCOM)  | クラスの状態 |
|:-------------------:|:------------:|
|       `LCOM <= 0.4` | 理想的な状態 |
|`0.4 <  LCOM <  0.6` | 要注意状態   |
|`0.6 <= LCOM`        | 改善必須状態 |


* `LCOM <= 0.4`  
  クラスが非常に凝集しており、[単一責任の原則(SRP)](solid.md#SS_8_1)を強く遵守している状態であるため、
  通常、デザインの見直しは不要である。

* `0.4 < LCOM < 0.6`  
  クラスの凝集度がやや弱くなり始めている。
  デザイン見直しの必要な時期が迫りつつあると考えるべきだろう。
  このタイミングであればリファクタリングは低コストで完了できるだろう。

* `0.6 <= LCOM`  
  クラス内のメソッド間の関連性が低く、凝集度が不十分である。
  メソッドが異なる責務にまたがっている可能性が高いため、
  一刻も早くデザインの見直しを行うべきだろう。


### Spurious Wakeup <a id="SS_20_1_5"></a>
[Spurious Wakeup](https://en.wikipedia.org/wiki/Spurious_wakeup)とは、
条件変数に対する通知待ちの状態であるスレッドが、その通知がされていないにもかかわらず、
起き上がってしまう現象のことを指す。

下記のようなstd::condition_variableの使用で起こり得る。

```cpp
    //  example/cpp_idiom/spurious_wakeup_ut.cpp 8

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
    //  example/cpp_idiom/spurious_wakeup_ut.cpp 34

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

### 副作用 <a id="SS_20_1_6"></a>
プログラミングにおいて、式の評価による作用には、
主たる作用とそれ以外の
[副作用](https://ja.wikipedia.org/wiki/%E5%89%AF%E4%BD%9C%E7%94%A8_(%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0))
(side effect)とがある。
式は、評価値を得ること(関数では「引数を受け取り値を返す」と表現する)が主たる作用とされ、
それ以外のコンピュータの論理的状態(ローカル環境以外の状態変数の値)を変化させる作用を副作用という。
副作用の例としては、グローバル変数や静的ローカル変数の変更、
ファイルの読み書き等のI/O実行、等がある。

## オブジェクト指向 <a id="SS_20_2"></a>
### is-a <a id="SS_20_2_1"></a>
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
    //  example/cpp_idiom/class_relation_ut.cpp 11

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
    //  example/cpp_idiom/class_relation_ut.cpp 50

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
    //  example/cpp_idiom/class_relation_ut.cpp 91

    class q_chan : public kyukancho {
    public:
        std::string get_name() const override { return "キューちゃん"; }
    };
```

この誤用を改めた例を以下に示す。

```cpp
    //  example/cpp_idiom/class_relation_ut.cpp 113

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
kyukanchoとstd::stringの関係を[has-a](cpp_idiom.md#SS_20_2_2)の関係と呼ぶ。


### has-a <a id="SS_20_2_2"></a>
「has-a」の関係は、
あるクラスのインスタンスが別のクラスのインスタンスを構成要素として含む関係を指す。
つまり、あるクラスのオブジェクトが別のクラスのオブジェクトを保持している関係である。

例えば、CarクラスとEngineクラスがあるとする。CarクラスはEngineクラスのインスタンスを含むので、
CarはEngineを「has-a」の関係にあると言える。
通常、has-aの関係はクラス内でメンバ変数またはメンバオブジェクトとして実装される。
Carクラスの例ではCarクラスにはEngine型のメンバ変数が存在する。

```cpp
    //  example/cpp_idiom/class_relation_ut.cpp 144

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

### is-implemented-in-terms-of <a id="SS_20_2_3"></a>
「is-implemented-in-terms-of」の関係は、
オブジェクト指向プログラミング（OOP）において、
あるクラスが別のクラスの機能を内部的に利用して実装されていることを示す概念である。
これは、あるクラスが他のクラスのインターフェースやメソッドを用いて、
自身の機能を提供する場合に使われる。
[has-a](cpp_idiom.md#SS_20_2_2)の関係は、is-implemented-in-terms-of の関係の一種である。

is-implemented-in-terms-ofは下記の手段1-3に示した方法がある。

*手段1.* [public継承によるis-implemented-in-terms-of](cpp_idiom.md#SS_20_2_3_1)  
*手段2.* [private継承によるis-implemented-in-terms-of](cpp_idiom.md#SS_20_2_3_2)  
*手段3.* [コンポジションによる(has-a)is-implemented-in-terms-of](cpp_idiom.md#SS_20_2_3_3)  

手段1-3にはそれぞれ、長所、短所があるため、必要に応じて手段を選択する必要がある。
以下の議論を単純にするため、下記のようにクラスS、C、CCを定める。

* S(サーバー): 実装を提供するクラス
* C(クライアント): Sの実装を利用するクラス
* CC(クライアントのクライアント): Cのメンバを使用するクラス

コード量の観点から考えた場合、手段1が最も優れていることが多い。
依存関係の複雑さから考えた場合、CはSに強く依存する。
場合によっては、この依存はCCからSへの依存間にも影響をあたえる。
従って、手段3が依存関係を単純にしやすい。
手段1は[is-a](cpp_idiom.md#SS_20_2_1)に見え、以下に示すような問題も考慮する必要があるため、
可読性、保守性を劣化させる可能性がある。

```cpp
    //  example/cpp_idiom/class_relation_ut.cpp 260

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


#### public継承によるis-implemented-in-terms-of <a id="SS_20_2_3_1"></a>
public継承によるis-implemented-in-terms-ofの実装例を以下に示す。

```cpp
    //  example/cpp_idiom/class_relation_ut.cpp 282

    class MyString : public std::string {};

    // ...
    MyString str{"str"};

    ASSERT_EQ(str[0], 's');
    ASSERT_STREQ(str.c_str(), "str");

    str.clear();
    ASSERT_EQ(str.size(), 0);
```

すでに述べたようにこの方法は、
[private継承によるis-implemented-in-terms-of](cpp_idiom.md#SS_20_2_3_2)や、
[コンポジションによる(has-a)is-implemented-in-terms-of](cpp_idiom.md#SS_20_2_3_3)
と比べコードがシンプルになる。 

#### private継承によるis-implemented-in-terms-of <a id="SS_20_2_3_2"></a>
private継承によるis-implemented-in-terms-ofの実装例を以下に示す。

```cpp
    //  example/cpp_idiom/class_relation_ut.cpp 179

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

この方法は、[public継承によるis-implemented-in-terms-of](cpp_idiom.md#SS_20_2_3_1)が持つデストラクタ問題は発生せす、
[is-a](cpp_idiom.md#SS_20_2_1)と誤解してしまう問題も発生しない。


#### コンポジションによる(has-a)is-implemented-in-terms-of <a id="SS_20_2_3_3"></a>
コンポジションによる(has-a)is-implemented-in-terms-ofの実装例を示す。

```cpp
    //  example/cpp_idiom/class_relation_ut.cpp 207

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


## C++注意点 <a id="SS_20_3"></a>
### オーバーライドとオーバーロードの違い <a id="SS_20_3_1"></a>
下記例では、Base::g()がオーバーロードで、Derived::f()がオーバーライドである
(Derived::g()はオーバーロードでもオーバーライドでもない(「[name-hiding](cpp_standard.md#SS_19_12_9)」参照))。


```cpp
    //  example/cpp_idiom/override_overload_ut.cpp 5

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

<!-- pu:deep/plant_uml/vtbl.pu--><p><img src="data:image/png;base64,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" /></p>

vtblとは仮想関数テーブルとも呼ばれる、仮想関数ポインタを保持するための上記のようなテーブルである
(「[ポリモーフィックなクラス](cpp_standard.md#SS_19_4_8)」参照)。

Base::f()、Derived::f()の呼び出し選択は、オブジェクトの表層の型ではなく、実際の型により決定される。
Base::g()、Derived::g()の呼び出し選択は、オブジェクトの表層の型により決定される。

```cpp
    //  example/cpp_idiom/override_overload_ut.cpp 29

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

### Most Vexing Parse <a id="SS_20_3_2"></a>
Most Vexing Parse(最も困惑させる構文解析)とは、C++の文法に関連する問題で、
Scott Meyersが彼の著書"Effective STL"の中でこの現象に名前をつけたことに由来する。

この問題はC++の文法が関数の宣言と変数の定義とを曖昧に扱うことによって生じる。
特にオブジェクトの初期化の文脈で発生し、意図に反して、その行は関数宣言になってしまう。

```cpp
    //  example/cpp_idiom/most_vexing_parse_ut.cpp 6

    class Vexing {
    public:
        Vexing(int) {}
        Vexing() {}
    };

    //  example/cpp_idiom/most_vexing_parse_ut.cpp 21

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

[初期化子リストコンストラクタ](cpp_standard.md#SS_19_6_1_1)の呼び出しでオブジェクトの初期化を行うことで、
このような問題を回避できる。


## C++コンパイラ <a id="SS_20_4"></a>
本ドキュメントで使用するg++/clang++のバージョンは以下のとおりである。

### g++ <a id="SS_20_4_1"></a>
```
    g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
    Copyright (C) 2021 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### clang++ <a id="SS_20_4_2"></a>
```
    Ubuntu clang version 14.0.0-1ubuntu1
    Target: x86_64-pc-linux-gnu
    Thread model: posix
    InstalledDir: /usr/bin
```


