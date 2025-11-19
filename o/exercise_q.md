<!-- ./md/exercise_q.md -->
# 演習 <a id="SS_22"></a>

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

&emsp;&emsp; [プログラミング規約(型)](exercise_q.md#SS_22_1)  
&emsp;&emsp; [プログラミング規約(クラス)](exercise_q.md#SS_22_2)  
&emsp;&emsp; [プログラミング規約(関数)](exercise_q.md#SS_22_3)  
&emsp;&emsp; [プログラミング規約(構文)](exercise_q.md#SS_22_4)  
&emsp;&emsp; [プログラミング規約(演算子)](exercise_q.md#SS_22_5)  
&emsp;&emsp; [プログラミング規約(スコープ)](exercise_q.md#SS_22_6)  
&emsp;&emsp; [プログラミング規約(その他)](exercise_q.md#SS_22_7)  
&emsp;&emsp; [SOLID](exercise_q.md#SS_22_8)  
&emsp;&emsp; [デザインパターン](exercise_q.md#SS_22_9)  
&emsp;&emsp; [開発プロセスとインフラ(全般)](exercise_q.md#SS_22_10)  
&emsp;&emsp; [テンプレートメタプログラミング](exercise_q.md#SS_22_11)  
  
  
  
[インデックス](introduction.md#SS_1_4)に戻る。  

___

## プログラミング規約(型) <a id="SS_22_1"></a>

### 演習-汎整数型の選択 <a id="SS_22_1_1"></a>
* 問題  
  汎整数型には、特に理由がない限りに、int32\_tを使用するべきであるが、
  値が負にならない場合は、(A)を使用するべきである。  
  (A)に相応しいものを下記より選べ。  

* 選択肢  
    1. int32_t
    2. unsigned long
    3. uint32_t
    4. uint16_t

* [解答-汎整数型の選択](exercise_a.md#SS_23_1_1)


### 演習-汎整数型の演算 <a id="SS_22_1_2"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/type.cpp 7
    TEST(ProgrammingConventionTypeQ, GeneralInteger)
    {
        // [Q]
        // 以下の組み込み型の使用方法は、その下のテストコードを(環境依存で)パスするが、
        // 適切であるとは言えない。適切な型に修正せよ。
        auto b = true;
        int  i{b};
        char c{-1};

        ASSERT_EQ(i * c, -1);
    }
```

* 参照 [算術型](programming_convention.md#SS_3_1_1)
* [解答例-汎整数型の演算](exercise_a.md#SS_23_1_2)


### 演習-浮動小数点型 <a id="SS_22_1_3"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/type.cpp 21
    double f(double a) noexcept { return 1 / a; }

    TEST(ProgrammingConventionTypeQ, Float)
    {
        // [Q]
        // 以下の両辺を同一と判定するための関数を作り、その関数の単体テストを行え。
        ASSERT_FALSE(1.0 == 1 + 0.001 - 0.001);

        // [Q]
        // 以下の0除算を捕捉するためのコードを書け。
        f(0.0);
    }
```

* 参照 [浮動小数点型](programming_convention.md#SS_3_1_1_5)
* [解答例-浮動小数点型](exercise_a.md#SS_23_1_3)


### 演習-定数列挙 <a id="SS_22_1_4"></a>
* 問題  
  特に理由がない限り、一連の定数の列挙には(A)を定義して使用する。  
  (A)に相応しいものを下記より選べ。

* 選択肢  
    1. マクロ定数
    2. static const定数
    3. 非スコープドenum
    4. スコープドenum

* [解答-定数列挙](exercise_a.md#SS_23_1_4)


### 演習-enum <a id="SS_22_1_5"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/type.cpp 36
    // [Q]
    // 以下のマクロ引数を型安全なenumに修正せよ

    #define COLOR_RED 0
    #define COLOR_GREEN 1
    #define COLOR_BLUE 2

    std::string GetString(int color)
    {
        switch (color) {
        case COLOR_RED:
            return "Red";
        case COLOR_GREEN:
            return "Green";
        case COLOR_BLUE:
            return "Blue";
        default:
            assert(false);
            return "";
        }
    }

    TEST(ProgrammingConventionTypeQ, Enum)
    {
        ASSERT_EQ(std::string{"Red"}, GetString(COLOR_RED));
        ASSERT_EQ(std::string{"Green"}, GetString(COLOR_GREEN));
        ASSERT_EQ(std::string{"Blue"}, GetString(COLOR_BLUE));
    }
```

* 参照 [enum](core_lang_spec.md#SS_19_3_1)
* [解答例-enum](exercise_a.md#SS_23_1_5)


### 演習-配列の範囲for文 <a id="SS_22_1_6"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/type.cpp 67
    int32_t array_value() noexcept
    {
        static int32_t i;

        return i++;
    }

    TEST(ProgrammingConventionTypeQ, Array)
    {
        // [Q]
        // 以下の配列の値の設定を範囲for文を使って書き直せ
        int32_t array[10];

        for (auto i = 0U; i < sizeof(array) / sizeof(array[0]); ++i) {
            array[i] = array_value();
        }

        ASSERT_EQ(0, array[0]);
        ASSERT_EQ(3, array[3]);
        ASSERT_EQ(9, array[9]);
    }
```

* 参照 [配列](programming_convention.md#SS_3_1_7)
* [解答例-配列の範囲for文](exercise_a.md#SS_23_1_6)


### 演習-エイリアス <a id="SS_22_1_7"></a>
* 問題

```cpp
    //  exercise/programming_convention_q/type.cpp 91
    // [Q]
    // 以下のtypedefをC++11から導入された新しい形式のエイリアスに直せ。
    typedef unsigned char uchar;
    typedef bool (*func_type)(int32_t);

    // [Q]
    // template引数で与えられた型のオブジェクトをstd::vectorで保持するエイリアスtemplateを
    // 定義し、その単体テストを行え。

```

* 参照 [型エイリアス](programming_convention.md#SS_3_1_8)
* [解答例-エイリアス](exercise_a.md#SS_23_1_7)


### 演習-constの意味 <a id="SS_22_1_8"></a>
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

* [解答-constの意味](exercise_a.md#SS_23_1_8)


### 演習-const/constexpr <a id="SS_22_1_9"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/type.cpp 103
    // [Q]
    // 下記のStringHolderに「const/constexprを付加する」等を行い、より良いコードに修正せよ。

    class StringHolder {
    public:
        StringHolder() = default;
        void Add(std::string str)
        {
            if (vector_len_max_ > strings_.size()) {
                strings_.push_back(str);
            }
        }

        std::vector<std::string> GetStrings() const { return strings_; }

    private:
        size_t                   vector_len_max_{3};
        std::vector<std::string> strings_{};
    };

    TEST(ProgrammingConventionTypeQ, ConstConstexpr)
    {
        auto sh = StringHolder{};

        ASSERT_EQ(std::vector<std::string>{}, sh.GetStrings());

        sh.Add("a");
        sh.Add(std::string{"bc"});
        ASSERT_EQ((std::vector<std::string>{"a", "bc"}), sh.GetStrings());

        sh.Add("def");
        sh.Add(std::string{"g"});
        ASSERT_EQ((std::vector<std::string>{"a", "bc", "def"}), sh.GetStrings());
    }
```

* 参照 [const/constexprインスタンス](programming_convention.md#SS_3_1_9)
* [解答例-const/constexpr](exercise_a.md#SS_23_1_9)


### 演習-危険なconst_cast <a id="SS_22_1_10"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/type.cpp 140
    // [Q]
    // 下記の"DISABLED_"を削除し、何が起こるのか、なぜそうなるのかを確かめた上で、
    // nameの型やその初期化を行っているコードを修正せよ。
    TEST(DISABLED_ProgrammingConventionQ, ConstConstexpr2)
    {
        char* name = const_cast<char*>("abcdef");

        for (auto i = 0U; name[i] != '\0'; ++i) {
            name[i] = std::toupper(name[i]);
        }

        ASSERT_STREQ("ABCDEF", name);
        ASSERT_EQ("ABCDEF", std::string{name});
    }
```

* 参照 [const/constexprインスタンス](programming_convention.md#SS_3_1_9)
* [解答例-危険なconst_cast](exercise_a.md#SS_23_1_10)


### 演習-リテラル <a id="SS_22_1_11"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/type.cpp 157
    int32_t literal_test(int64_t) noexcept { return 0; }
    int32_t literal_test(int32_t*) noexcept { return 1; }

    // [Q]
    // 下記変数の初期化コードをコメントに基づき適切に修正せよ。
    TEST(ProgrammingConventionTypeQ, Literal)
    {
        int32_t* p{NULL};                // NULLは使用不可
        uint64_t a{0x1234567890abcdef};  // 適切なセパレータを挿入
        int32_t  b{0x715};               // ビット表現に修正

        // [Q]
        // 下記resultはfalseになるが、その理由を述べ、trueになるようにコードを修正せよ。
        bool const result{(literal_test(NULL) == literal_test(p))};
        ASSERT_FALSE(result);

        ASSERT_EQ(0x1234567890abcdef, a);
        ASSERT_EQ(b, 0x715);
    }
```

* 参照 [リテラル](core_lang_spec.md#SS_19_2)

* [解答例-リテラル](exercise_a.md#SS_23_1_11)


### 演習-適切なautoの使い方 <a id="SS_22_1_12"></a>
* 問題  
  以下のコードのautoの中で、使い方が好ましくないものを選べ。

* 選択肢  
    1. auto s0 = std::string("xxx");
    2. auto s1(std::string("xxx"));
    3. auto s2 = s0;                   // s0は上記に定義されたもの
    4. auto s3 = get_name();           // get_name()は離れた場所に宣言

* [解答-適切なautoの使い方](exercise_a.md#SS_23_1_12)


### 演習-ポインタの初期化 <a id="SS_22_1_13"></a>
* 問題  
  初期値が定まらないポインタ変数の初期化方法にふさわしいものを選べ。

* 選択肢  
    1. 0を代入する。
    2. NULLを代入する。
    3. nullptrを代入する。
    4. 何もしない。

* [解答-ポインタの初期化](exercise_a.md#SS_23_1_13)


### 演習-vector初期化 <a id="SS_22_1_14"></a>
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

* [解答-vector初期化](exercise_a.md#SS_23_1_14)


### 演習-インスタンスの初期化 <a id="SS_22_1_15"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/type.cpp 179
    TEST(ProgrammingConventionTypeQ, Initialization)
    {
        // [Q]
        // 変数a、b、v、wの定義と初期化を1文で行え。
        {
            int32_t a[3];

            for (auto& r : a) {
                r = 1;
            }

            ASSERT_EQ(1, a[0]);
            ASSERT_EQ(1, a[1]);
            ASSERT_EQ(1, a[2]);
        }
        {
            int32_t b[3];

            for (auto& r : b) {
                r = 0;
            }

            ASSERT_EQ(0, b[0]);
            ASSERT_EQ(0, b[1]);
            ASSERT_EQ(0, b[2]);
        }
        {
            auto v = std::vector<std::string>{3};

            for (auto& r : v) {
                r = "1";
            }

            ASSERT_EQ("1", v[0]);
            ASSERT_EQ("1", v[1]);
            ASSERT_EQ("1", v[2]);
        }
        {
            auto w = std::vector<std::string>{};

            for (auto i = 0; i < 3; ++i) {
                w.emplace_back(std::to_string(i));
            }

            ASSERT_EQ("0", w[0]);
            ASSERT_EQ("1", w[1]);
            ASSERT_EQ("2", w[2]);
        }
    }
```

* 参照 [インスタンスの初期化](programming_convention.md#SS_3_1_12)、[一様初期化](core_lang_spec.md#SS_19_6_6)
* [解答例-インスタンスの初期化](exercise_a.md#SS_23_1_15)


## プログラミング規約(クラス) <a id="SS_22_2"></a>

### 演習-凝集性の意味 <a id="SS_22_2_1"></a>
* 問題  
  クラスの凝集性とはLack of Cohesion in Methodsというメトリクスで計測される。
  この凝集性やメトリクスの説明として正しくないものを選べ。

* 選択肢  
    1. クラスは凝集性を高くするように設計すべきである。
    2. このメトリクス値が1に近ければ凝集性は低く、この値が0に近ければ凝集性は高い。
    3. メンバ変数やメンバ関数が多くなれば、凝集性は低くなりやすい。
    4. setterやgetterを使用することで、凝集性を高く保つことができる。

* [解答-凝集性の意味](exercise_a.md#SS_23_2_1)


### 演習-凝集性の向上 <a id="SS_22_2_2"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/class.cpp 7
    // [Q]
    // 以下のクラスABCの凝集度が高くなるように、ABC、HasRealNumberSolutionをリファクタリングせよ。
    // その時に、他の問題があればそれも併せて修正せよ。

    class ABC {  // 2次方程式のパラメータ保持
    public:
        ABC(int32_t a, int32_t b, int32_t c) noexcept : a_{a}, b_{b}, c_{c} {}

        int32_t GetA() const { return a_; }
        int32_t GetB() const { return b_; }
        int32_t GetC() const { return c_; }
        void    SetA(int32_t a) { a_ = a; }
        void    SetB(int32_t b) { b_ = b; }
        void    SetC(int32_t c) { c_ = c; }

    private:
        int32_t a_;
        int32_t b_;
        int32_t c_;
    };

    bool HasRealNumberSolution(ABC abc)
    {
        auto const discriminant = abc.GetB() * abc.GetB() - 4 * abc.GetA() * abc.GetC();  // 判定式

        return 0 <= discriminant;
    }

    TEST(ProgrammingConventionClassQ, Cohision)
    {
        {
            auto abc = ABC{1, 2, 1};

            ASSERT_TRUE(HasRealNumberSolution(abc));
        }
        {
            auto abc = ABC{2, 0, 1};

            ASSERT_FALSE(HasRealNumberSolution(abc));
        }
    }
```

* 参照 [凝集性](programming_convention.md#SS_3_2_2_3)
* [解答例-凝集性の向上](exercise_a.md#SS_23_2_2)


### 演習-メンバ変数の初期化方法の選択 <a id="SS_22_2_3"></a>
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

* [解答-メンバ変数の初期化方法の選択](exercise_a.md#SS_23_2_3)


### 演習-メンバの型 <a id="SS_22_2_4"></a>
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

* [解答-メンバの型](exercise_a.md#SS_23_2_4)


### 演習-メンバ変数の初期化 <a id="SS_22_2_5"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/class.cpp 51
    // [Q]
    // 以下のMemberInitのメンバ変数を適切な方法で初期化せよ。

    class MemberInit {
    public:
        MemberInit() noexcept
        {
            a_    = 0;
            b_[0] = 1;
            b_[1] = 1;
            c_    = 2;
        }

        explicit MemberInit(int a) noexcept
        {
            a_    = a;
            b_[0] = a;
            b_[1] = 99;
            c_    = 2;
        }

        int32_t       GetA() noexcept { return a_; }
        int32_t*      GetB() noexcept { return b_; }
        int32_t       GetC() noexcept { return c_; }
        static size_t b_len;

    private:
        int32_t a_;
        int32_t b_[2];
        int32_t c_;
    };
    size_t MemberInit::b_len = 2;

    TEST(ProgrammingConventionClassQ, MemberInit)
    {
        {
            auto mi = MemberInit{};

            ASSERT_EQ(0, mi.GetA());
            ASSERT_EQ(1, mi.GetB()[0]);
            ASSERT_EQ(1, mi.GetB()[1]);
            ASSERT_EQ(2, mi.GetC());
        }
        {
            auto mi = MemberInit{1};

            ASSERT_EQ(1, mi.GetA());
            ASSERT_EQ(1, mi.GetB()[0]);
            ASSERT_EQ(99, mi.GetB()[1]);
            ASSERT_EQ(2, mi.GetC());
        }
    }
```

* 参照 [非静的なメンバ変数](programming_convention.md#SS_3_2_5_2)
* [解答例-メンバ変数の初期化](exercise_a.md#SS_23_2_5)


### 演習-スライシング <a id="SS_22_2_6"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/class.cpp 106
    // [Q]
    // 以下のクラスBaseはオブジェクトのスライシングを引き起こす。
    // このような誤用を起こさないようにするために、Baseオブジェクトのコピーを禁止せよ。
    // 合わせてクラスDerivedも含め、不十分な記述を修正せよ。

    class Base {
    public:
        Base(char const* name = nullptr) noexcept : name_{name == nullptr ? "Base" : name} {}
        ~Base() = default;

        virtual char const* Name0() { return "Base"; }
        char const*         Name1() { return name_; }

    private:
        char const* name_;
    };

    class Derived final : public Base {
    public:
        Derived() noexcept : Base{"Derived"} {}

        char const* Name0() { return "Derived"; }
    };

    TEST(ProgrammingConventionClassQ, Slicing)
    {
        auto  b     = Base{};
        auto  d     = Derived{};
        Base& d_ref = d;

        // 以下はBase、Derivedの単純なテスト
        ASSERT_STREQ("Base", b.Name0());
        ASSERT_STREQ("Base", b.Name1());
        ASSERT_STREQ("Derived", d_ref.Name0());
        ASSERT_STREQ("Derived", d_ref.Name1());

        // 以下はbがスライスされたオブジェクトであることのテスト
        // こういった誤用を防ぐためにBaseのコピーを禁止せよ。
        b = d_ref;
        ASSERT_STREQ("Base", b.Name0());     // vtblはBaseになるから
        ASSERT_STREQ("Derived", b.Name1());  // name_はコピーされるから
    }
```

* 参照 [スライシング](cpp_idioms.md#SS_21_10_3)
* [解答例-スライシング](exercise_a.md#SS_23_2_6)

### 演習-オブジェクトの所有権 <a id="SS_22_2_7"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/class.cpp 151
    class A {
    public:
        explicit A(int32_t n) noexcept : num_{n} { last_constructed_num_ = num_; }
        ~A() { last_destructed_num_ = num_; }

        int32_t GetNum() const noexcept { return num_; }

        static int32_t LastConstructedNum() noexcept { return last_constructed_num_; }
        static int32_t LastDestructedNum() noexcept { return last_destructed_num_; }

    private:
        int32_t        num_;
        static int32_t last_constructed_num_;
        static int32_t last_destructed_num_;
    };

    int32_t A::last_constructed_num_ = -1;
    int32_t A::last_destructed_num_  = -1;

    class X final {
    public:
        void Move(std::unique_ptr<A>&& ptr) noexcept
        {
            ptr_ = std::move(ptr);  // ptr->ptr_へ所有権の移動
        }

        std::unique_ptr<A> Release() noexcept
        {
            return std::move(ptr_);  // ptr_から外部への所有権の移動
        }

        A const* GetA() const noexcept { return ptr_.get(); }
        X()  = default;
        ~X() = default;

    private:
        std::unique_ptr<A> ptr_{};
    };

    TEST(ProgrammingConventionClassQ, Ownership)
    {
        // [Q]
        // 以下の単体テストを完成させよ。
        // ?はインスタンスが入り、?????はTRUEかFALSEが入る。

        ASSERT_EQ(-1, A::LastConstructedNum());     // まだ、A::A()は呼ばれてない
        ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない

        auto a0 = std::make_unique<A>(0);           // a0はA(0)を所有
        auto a1 = std::make_unique<A>(1);           // a1はA(1)を所有
        auto x = X {};

    //  ASSERT_EQ(?, A::LastConstructedNum());      // A(1)は生成された
    //  ASSERT_EQ(?, A::LastDestructedNum());       // まだ、A::~A()は呼ばれてない
    //  ASSERT_EQ(?, a0->GetNum());                 // a0はA(0)を所有
        x.Move(std::move(a0));                      // a0からxへA(0)の所有権の移動
    //  ASSERT_?????(a0);                           // a0は何も所有していない

    //  ASSERT_EQ(?, a1->GetNum());                 // a1はA(1)を所有
        x.Move(std::move(a1));                      // xによるA(0)の解放
                                                    // a1からxへA(1)の所有権の移動
    //  ASSERT_EQ(?, A::LastDestructedNum());       // A(0)は解放された
    //  ASSERT_?????(a1);                           // a1は何も所有していない
    //  ASSERT_EQ(?, x.GetA()->GetNum());           // xはA(1)を所有

        std::unique_ptr<A> a2{x.Release()};         // xからa2へA(1)の所有権の移動
    //  ASSERT_EQ(?, x.GetA());                     // xは何も所有していない
    //  ASSERT_EQ(?, a2->GetNum());                 // a2はA(1)を所有
        {
            std::unique_ptr<A> a3{std::move(a2)};
    //      ASSERT_?????(a2);                       // a2は何も所有していない
    //      ASSERT_EQ(?, a3->GetNum());             // a3はA(1)を所有
        }                                           // a3によるA(1)の解放
    //  ASSERT_EQ(?, A::LastDestructedNum());
    }
```

* 参照 [オブジェクトの所有権](cpp_idioms.md#SS_21_4)
* [解答例-オブジェクトの所有権](exercise_a.md#SS_23_2_7)


## プログラミング規約(関数) <a id="SS_22_3"></a>

### 演習-非メンバ関数の宣言 <a id="SS_22_3_1"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 5
    extern "C" double cos(double x);

    TEST(ProgrammingConventionFuncQ, NonMemberFunc)
    {
        // [Q]
        // 適切な#includeを追加し、上記のextern宣言がなくとも下記がコンパイルできるようにせよ。
        ASSERT_EQ(1, cos(0));
    }
```

* 参照 [非メンバ関数](programming_convention.md#SS_3_3_11)
* [解答例-非メンバ関数の宣言](exercise_a.md#SS_23_3_1)


### 演習-メンバ関数の修飾 <a id="SS_22_3_2"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 17
    // [Q]
    // 下記のクラスAのメンバ関数の不正確な記述を修正せよ。
    // また、単体テストを同様に修正せよ。

    class A {
    public:
        A() : strings_{GetStringsDefault()} {}

        void SetStrings(size_t index, std::string str)
        {
            if (index < max_len) {
                strings_[index] = str;
            }
        }

        std::vector<std::string>& GetStrings() { return strings_; }
        std::vector<std::string>  GetStrings() const { return strings_; }
        size_t                    MaxLen() { return max_len; }

        std::vector<std::string>& GetStringsDefault()
        {
            static auto strings_default = std::vector<std::string>{max_len, ""};
            return strings_default;
        }

    private:
        std::vector<std::string> strings_;
        static constexpr size_t  max_len{3};
    };

    TEST(ProgrammingConventionFuncQ, MemberFunc)
    {
        auto a = A{};

        auto strings_default = a.GetStringsDefault();
        ASSERT_EQ("", strings_default[0]);
        ASSERT_EQ("", strings_default[1]);
        ASSERT_EQ("", strings_default[2]);
        ASSERT_EQ(3, a.MaxLen());

        auto strings = a.GetStrings();

        ASSERT_EQ("", strings[0]);
        ASSERT_EQ("", strings[1]);
        ASSERT_EQ("", strings[2]);

        a.SetStrings(1, "TEST");
        ASSERT_EQ("", strings[0]);

        // [Q]
        // このテストをASSERT_EQでパスできるようにせよ
        ASSERT_NE("TEST", strings[1]);

        ASSERT_EQ("", strings[2]);
    }
```

* 参照 [メンバ関数](programming_convention.md#SS_3_2_4)
* [解答例-メンバ関数の修飾](exercise_a.md#SS_23_3_2)


### 演習-特殊メンバ関数の削除 <a id="SS_22_3_3"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 75
    // [Q]
    // 下記クラスAutoGenのコンパイラが自動生成するメンバ関数を生成しないようにせよ。

    class AutoGen {};
```

* 参照 [特殊メンバ関数](programming_convention.md#SS_3_2_4_1)
* [解答例-特殊メンバ関数の削除](exercise_a.md#SS_23_3_3)


### 演習-委譲コンストラクタ <a id="SS_22_3_4"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 82
    // [Q]
    // 下記クラスDelConstructorの2つのコンストラクタのコードクローンをできるだけ排除せよ。
    // また、不正確な記述を修正せよ。

    class DelConstructor {
    public:
        DelConstructor(std::string const& str) : str0_{str + "0"}, str1_{str + "1"}, str2_{str + "2"} {}

        DelConstructor(int32_t num)
            : str0_{std::to_string(num) + "_0"}, str1_{std::to_string(num) + "_1"}, str2_{std::to_string(num) + "_2"}
        {
        }

        std::string& GetString0() { return str0_; }
        std::string& GetString1() { return str1_; }
        std::string& GetString2() { return str2_; }

    private:
        std::string str0_;
        std::string str1_;
        std::string str2_;
    };

    TEST(ProgrammingConventionFuncQ, Constructor)
    {
        {
            auto dc = DelConstructor{"hehe"};

            ASSERT_EQ("hehe0", dc.GetString0());
            ASSERT_EQ("hehe1", dc.GetString1());
            ASSERT_EQ("hehe2", dc.GetString2());
        }
        {
            auto dc = DelConstructor{123};

            ASSERT_EQ("123_0", dc.GetString0());
            ASSERT_EQ("123_1", dc.GetString1());
            ASSERT_EQ("123_2", dc.GetString2());
        }
    }
```

* 参照 [コンストラクタ](programming_convention.md#SS_3_2_4_2)
* [解答例-委譲コンストラクタ](exercise_a.md#SS_23_3_4)


### 演習-copyコンストラクタ <a id="SS_22_3_5"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 125
    // [Q]
    // 下記クラスIngeter、IntegerHolderに適切にcopyコンストラクタ、copy代入演算子を追加して、
    // 単体テストを行え(DISABLED_削除)。
    class Integer {
    public:
        explicit Integer(int32_t i) noexcept : i_{i} {}

        int32_t GetValue() const noexcept { return i_; }

    private:
        int32_t i_;
    };

    class IntegerHolder {
    public:
        explicit IntegerHolder(int32_t i) : integer_{new Integer{i}} {}

        int32_t GetValue() const noexcept { return integer_->GetValue(); }

        ~IntegerHolder() { delete integer_; }

    private:
        Integer* integer_;
    };

    #ifndef __clang_analyzer__
    TEST(DISABLED_ProgrammingConventionFuncQ, Constructor2)
    {
        {
            auto i = Integer{3};
            ASSERT_EQ(3, i.GetValue());

            auto j = Integer{i};
            ASSERT_EQ(3, j.GetValue());

            auto k = Integer{0};
            ASSERT_EQ(0, k.GetValue());

            k = i;
            ASSERT_EQ(3, k.GetValue());
        }
        {
            auto i = IntegerHolder{3};
            ASSERT_EQ(3, i.GetValue());

            auto j = IntegerHolder{i};
            ASSERT_EQ(3, j.GetValue());

            auto k = IntegerHolder{0};
            ASSERT_EQ(0, k.GetValue());

            k = i;
            ASSERT_EQ(3, k.GetValue());
        }
    }
    #endif
```

* 参照 [コンストラクタ](programming_convention.md#SS_3_2_4_2)
* [解答例-copyコンストラクタ](exercise_a.md#SS_23_3_5)


### 演習-moveコンストラクタ <a id="SS_22_3_6"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 184
    // [Q]
    // 上記問題を解決したIntegerHolderにmoveコンストラクタ、move演算子を追加した
    // クラスIntegerHolder2を作成し、単体テストを行え。
```

* 参照 [moveコンストラクタ、move代入演算子](programming_convention.md#SS_3_2_4_4)
* [解答例-moveコンストラクタ](exercise_a.md#SS_23_3_6)


### 演習-関数分割 <a id="SS_22_3_7"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 190
    // [Q]
    // 下記PrimeNumbersは引数で与えられた整数以下の素数を返す関数である。
    // PrimeNumbersの単体テストを作成し、その後、行数を短くする等のリファクタリングを行え。

    std::vector<uint32_t> PrimeNumbers(uint32_t max_number)
    {
        auto result = std::vector<uint32_t>{};

        if (max_number >= 2) {
            auto prime_num    = 2U;                                       // 最初の素数
            auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない。
            is_num_prime[0] = is_num_prime[1] = false;

            do {
                result.emplace_back(prime_num);

                for (auto i = 2 * prime_num; i < is_num_prime.size(); i += prime_num) {
                    is_num_prime[i] = false;
                }

                do {  // 次の素数の探索
                    ++prime_num;
                } while (!is_num_prime[prime_num] && (prime_num < is_num_prime.size()));

            } while (prime_num < is_num_prime.size());

            return result;
        }
        else {
            return result;
        }
    }

    TEST(ProgrammingConventionFuncQ, Lines)
    {
        ASSERT_EQ((std::vector<uint32_t>{}), PrimeNumbers(0));
        // 以下に単体テストを追加
    }
```

* 参照 [関数構造のクライテリア](programming_convention.md#SS_3_3_1)
* [解答例-関数分割](exercise_a.md#SS_23_3_7)


### 演習-オーバーライド関数の修飾 <a id="SS_22_3_8"></a>
* 問題  
  オーバーライドしたメンバ関数は、virtualと(A)を使用して宣言する。  
  (A)に相応しいものを下記より選べ。

* 選択肢  
    1. final
    2. override
    3. overload
    4. const

* [解答-オーバーライド関数の修飾](exercise_a.md#SS_23_3_8)


### 演習-オーバーライド/オーバーロード <a id="SS_22_3_9"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 231
    // [Q]
    // 下記クラスBase、Derivedの単体テストを完成せよ。

    class Base {
    public:
        virtual ~Base() = default;
        int32_t f() noexcept { return 0; }

        virtual int32_t g() noexcept { return 0; }
    };

    class Derived : public Base {
    public:
        int32_t f() noexcept { return 1; }

        virtual int32_t g() noexcept override { return 1; }
    };

    TEST(ProgrammingConventionFuncQ, Overload)
    {
        auto  b     = Base{};
        auto  d     = Derived{};
        Base& d_ref = d;

    #if 0
        // 下記?は0もしくは1が入る
        ASSERT_EQ(?, b.f());
        ASSERT_EQ(?, b.g());

        ASSERT_EQ(?, d.f());
        ASSERT_EQ(?, d.g());

        ASSERT_EQ(?, d_ref.f());
        ASSERT_EQ(?, d_ref.g());
    #endif
    }
```

* 参照 [オーバーライド](programming_convention.md#SS_3_2_4_7)
* [解答例-オーバーライド/オーバーロード](exercise_a.md#SS_23_3_9)


### 演習-オーバーロードによる誤用防止 <a id="SS_22_3_10"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 270
    // [Q]
    // 下記関数Squareは、引数が浮動小数点となることを想定していない。
    // 誤用を防ぐために、引数に浮動小数点を指定された場合、コンパイルできないようにせよ。
    int32_t Square(int32_t a) noexcept { return a * a; }

    TEST(ProgrammingConventionFuncQ, Overload2)
    {
        ASSERT_EQ(9, Square(3));
        ASSERT_EQ(4, Square(2.5));  // この誤用を防ぐためにコンパイルエラーにせよ。
    }
```

* 参照 [オーバーロード](programming_convention.md#SS_3_3_2)
* [解答例-オーバーロードによる誤用防止](exercise_a.md#SS_23_3_10)


### 演習-仮引数の修飾 <a id="SS_22_3_11"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 283
    // [Q]
    // 下記AddStringsの仮引数等を適切に修正せよ。
    using Strings = std::list<std::string>;
    void AddStrings(Strings a, Strings* b, Strings* ret)
    {
        *ret = a;

        if (b == nullptr) {
            return;
        }

        ret->insert(ret->end(), b->begin(), b->end());
    }

    TEST(ProgrammingConventionFuncQ, Parameter)
    {
        auto a = Strings{"abc", "d"};
        auto b = Strings{"e", "fgh", "i"};

        auto ret = Strings{};
        AddStrings(a, nullptr, &ret);
        ASSERT_EQ(ret, (Strings{"abc", "d"}));

        AddStrings(a, &b, &ret);
        ASSERT_EQ(ret, (Strings{"abc", "d", "e", "fgh", "i"}));
    }
```

* 参照 [実引数/仮引数](programming_convention.md#SS_3_3_4)
* [解答例-仮引数の修飾](exercise_a.md#SS_23_3_11)


### 演習-constexpr関数 <a id="SS_22_3_12"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/func.cpp 312
    // [Q]
    // 下記Factorialをconstexpr関数にせよ。
    uint32_t Factorial(uint32_t a) noexcept
    {
        if (a == 0 || a == 1) {
            return 1;
        }

        auto fact = 1U;

        for (auto i = 2U; i <= a; ++i) {
            fact *= i;
        }

        return fact;
    }

    TEST(ProgrammingConventionFuncQ, ConstexprFunc)
    {
    #if 0  // Factorialはconstexpr関数でないため、下記はコンパイルできない。
        static_assert(1 == Factorial(0), "Factorial fail");
    #endif
        ASSERT_EQ(1, Factorial(0));
        ASSERT_EQ(6, Factorial(3));
        ASSERT_EQ(120, Factorial(5));
        ASSERT_EQ(3628800, Factorial(10));
    }
```

* 参照 [constexpr関数](core_lang_spec.md#SS_19_5_3)
* [解答例-constexpr関数](exercise_a.md#SS_23_3_12)


### 演習-エクセプションの型 <a id="SS_22_3_13"></a>
* 問題  
  try-catchでエクセプションを捕捉する場合、
  catchの中で宣言するエクセプション補足用の変数は(A)として定義する。  
  (A)に相応しいものを下記より選べ。

* 選択肢  
    1. constポインタ
    2. constリファレンス
    3. 非constオブジェクト
    4. constオブジェクト

* [解答-エクセプションの型](exercise_a.md#SS_23_3_13)


## プログラミング規約(構文) <a id="SS_22_4"></a>

### 演習-コンテナの範囲for文 <a id="SS_22_4_1"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/syntax.cpp 12
    // [Q]
    // 下記Accumlateのfor文を
    //  * イテレータを使ったfor文を使用したAccumlate2
    //  * 範囲for文を使用したAccumlate3
    // を作り、それらの単体テストを行え。また、その時にその他の不具合があれば合わせて修正せよ。
    std::string Accumlate(std::vector<std::string> strings) noexcept
    {
        auto ret = std::string{};

        for (auto i = 0U; i < strings.size(); ++i) {
            ret += strings[i];
        }

        return ret;
    }

    TEST(ProgrammingConventionSyntaxQ, RangeFor) { ASSERT_EQ("abcd", Accumlate(std::vector<std::string>{"a", "b", "cd"})); }
```

* 参照 [範囲for文](core_lang_spec.md#SS_19_9_3)
* [解答例-コンテナの範囲for文](exercise_a.md#SS_23_4_1)


### 演習-ラムダ式 <a id="SS_22_4_2"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/syntax.cpp 32
    // [Q]
    // 下記のcopy_ifの第4引数をラムダ式を使って書き直せ。
    bool is_not_size0(std::string const& s) noexcept { return s.size() != 0; }

    TEST(ProgrammingConventionSyntaxQ, Lambda)
    {
        auto data = std::vector<std::string>{"", "abc", "", "d"};

        auto ret = std::vector<std::string>{};

        std::copy_if(data.cbegin(), data.cend(), std::back_inserter(ret), is_not_size0);
        ASSERT_EQ((std::vector<std::string>{"abc", "d"}), ret);
    }
```

* 参照 [ラムダ式](programming_convention.md#SS_3_4_9)
* [解答例-ラムダ式](exercise_a.md#SS_23_4_2)


### 演習-ラムダ式のキャプチャ <a id="SS_22_4_3"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/syntax.cpp 48
    // [Q]
    // 下記Lambda::GetNameLessThan()のラムダ式の問題点を修正し、単体テストを行え。
    class Lambda {
    public:
        explicit Lambda(std::vector<std::string>&& strs) : strs_{std::move(strs)} {}
        std::vector<std::string> GetNameLessThan(uint32_t length) const
        {
            auto ret = std::vector<std::string>{};

            std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                         [=](auto const& str) noexcept { return (strs_.size() < length); });

            return ret;
        }

    private:
        std::vector<std::string> strs_;
    };

    TEST(ProgrammingConventionSyntaxQ, Lambda2)
    {
        auto lambda = Lambda{{"abc", "abcdef", "a"}};

        // 以下に単体テストを追加。
    }
```

* 参照 [ラムダ式](programming_convention.md#SS_3_4_9)
* [解答例-ラムダ式のキャプチャ](exercise_a.md#SS_23_4_3)

## プログラミング規約(演算子) <a id="SS_22_5"></a>

### 演習-条件演算子 <a id="SS_22_5_1"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/operator.cpp 6
    // [Q]
    // 下記whichのif文を三項演算子を使用して書き直せ。
    int32_t which(bool left, int32_t lhs, int32_t rhs) noexcept
    {
        if (left) {
            return lhs;
        }
        else {
            return rhs;
        }
    }

    TEST(ProgrammingConventionOperatorQ, OoOperator)
    {
        ASSERT_EQ(3, which(true, 3, 4));
        ASSERT_EQ(4, which(false, 3, 4));
    }
```

* 参照 [条件演算子](programming_convention.md#SS_3_5_5)
* [解答例-条件演算子](exercise_a.md#SS_23_5_1)


### 演習-delete <a id="SS_22_5_2"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/operator.cpp 26
    // [Q]
    // 下記DeleteProblemのメモリ管理の問題を修正し、単体テストを行え(DISABLED_削除)。
    // また、他の問題があれば、合わせて修正せよ。
    class DeleteProblem {
    public:
        DeleteProblem(char const* str0 = nullptr, char const* str1 = nullptr)
        {
            if (str0 != nullptr) {
                str0_ = new std::string{str0};
            }
            if (str1 != nullptr) {
                str1_ = new std::string{str1};
            }
        }

        std::string const* GetStr0() { return str0_; }
        std::string const* GetStr1() { return str1_; }

        ~DeleteProblem()
        {
            delete_str(str0_);
            delete_str(str1_);
        }

    private:
        static void delete_str(void* str)
        {
            if (str != nullptr) {
                delete str;
            }
        }

        std::string* str0_ = nullptr;
        std::string* str1_ = nullptr;
    };

    TEST(DISABLED_ProgrammingConventionOperatorQ, Delete)
    {
        // この単体テストはメモリリークを起こす
        // このメモリリークはmake san-utで検出される
        {
            auto dp = DeleteProblem{};

            ASSERT_EQ(nullptr, dp.GetStr0());
            ASSERT_EQ(nullptr, dp.GetStr1());
        }
        {
            auto dp = DeleteProblem{"abc"};

            ASSERT_EQ("abc", *dp.GetStr0());
            ASSERT_EQ(nullptr, dp.GetStr1());
        }
        {
            auto dp = DeleteProblem{"abc", "de"};

            ASSERT_EQ("abc", *dp.GetStr0());
            ASSERT_EQ("de", *dp.GetStr1());
        }
    }
```

* 参照 [delete](programming_convention.md#SS_3_5_6_2)
* [解答例-delete](exercise_a.md#SS_23_5_2)


### 演習-sizeof <a id="SS_22_5_3"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/operator.cpp 88
    // [Q]
    // 下記Size1() - Size4()の単体テストを作れ。
    size_t Size0(int32_t a) noexcept { return sizeof(a); }

    size_t Size1(int32_t a[10]) noexcept { return sizeof(a); }

    size_t Size2(int32_t a[]) noexcept { return sizeof(a); }

    size_t Size3(int32_t* a) noexcept { return sizeof(a); }

    size_t Size4(int32_t (&a)[10]) noexcept { return sizeof(a); }

    TEST(ProgrammingConventionOperatorQ, Sizeof)
    {
        int32_t array[10]{};

        // Size1() - Size4()の単体テスト
        ASSERT_EQ(sizeof(void*), Size3(array));
    }
```

* 参照 [sizeof](programming_convention.md#SS_3_5_7)
* [解答例-sizeof](exercise_a.md#SS_23_5_3)


### 演習-dynamic_castの削除 <a id="SS_22_5_4"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/operator.cpp 110
    // [Q]
    // 下記クラスX、Y、ZとGetNameをdynamic_castを使わずに書き直せ。

    class X {
    public:
        virtual ~X() = default;
    };

    class Y : public X {};

    class Z : public X {};

    std::string GetName(X* x)
    {
        if (dynamic_cast<Y*>(x) != nullptr) {
            return "Y";
        }
        if (dynamic_cast<Z*>(x) != nullptr) {
            return "Z";
        }
        if (dynamic_cast<X*>(x) != nullptr) {
            return "X";
        }

        assert(false);
        return "UnKnown";
    }

    TEST(ProgrammingConventionOperatorQ, Cast)
    {
        auto x = X{};
        auto y = Y{};
        auto z = Z{};

        ASSERT_EQ("X", GetName(&x));
        ASSERT_EQ("Y", GetName(&y));
        ASSERT_EQ("Z", GetName(&z));
    }
```

* 参照 [キャスト、暗黙の型変換](programming_convention.md#SS_3_5_10)
* [解答例-dynamic_castの削除](exercise_a.md#SS_23_5_4)


### 演習-キャスト <a id="SS_22_5_5"></a>
* 問題  
  キャストは避けるべきだが、やむを得ず使用する場合であっても、
  Cタイプキャスト、(A)、 dynamic_castは使用しない。  
  (A)に相応しいものを下記より選べ。

* 選択肢  
    1. static_cast
    2. reinterpret_cast
    3. const_cast
    4. 該当なし

* [解答-キャスト](exercise_a.md#SS_23_5_5)


## プログラミング規約(スコープ) <a id="SS_22_6"></a>

### 演習-usingディレクティブ <a id="SS_22_6_1"></a>
* 問題  
  usingディレクティブ(using namespace NS)の使用上の注意として相応しいものを選べ。

* 選択肢  
    1. usingディレクティブは、関数先頭でのみ使用してよい。
    2. ヘッダファイルでusingディレクティブをすると便利である。
    3. ファイルスコープでusingディレクティブをすると便利である。
    4. using宣言よりusingディレクティブを優先するべきである。

* [解答-usingディレクティブ](exercise_a.md#SS_23_6_1)


## プログラミング規約(その他) <a id="SS_22_7"></a>

### 演習-アサーションの選択 <a id="SS_22_7_1"></a>
* 問題  
  論理的にありえない(switchでそのcaseやdefaultを通過することはあり得ない等)
  状態を検知するために積極的に(A)を使用する。  
  (A)に相応しいものを下記より選べ。

* 選択肢  
    1. assert()
    2. static_assert
    3. while(1);
    4. abort()

* [解答-アサーションの選択](exercise_a.md#SS_23_7_1)


### 演習-assert/static_assert <a id="SS_22_7_2"></a>
* 問題
```cpp
    //  exercise/programming_convention_q/etc.cpp 4
    // [Q]
    // 下記FloatingPointは、Tが浮動小数点型、Tのインスタンスは非０であることを前提としている。
    // 適切にアサーションを挿入して誤用を防げ。

    template <typename T>
    class FloatingPoint {
    public:
        FloatingPoint(T num) noexcept : num_{num} {}
        T Get() const noexcept { return num_; }
        T Reciprocal() const noexcept { return 1 / num_; }

    private:
        T num_;
    };
```

* 参照 [assertion](programming_convention.md#SS_3_11_1)
* [解答例-assert/static_assert](exercise_a.md#SS_23_7_2)


## SOLID <a id="SS_22_8"></a>
以下の演習問題の単体テストで使用される

```cpp
    TEST_F(Xxx, Yyy)
```

のような記述のXxyは、以下のように宣言・定義されている。

```cpp
    //  exercise/h/solid_ut.h 7

    class SolidFixture : public ::testing::Test {
    protected:
        std::string const test_score_org_     = "../ut_data2/test_score_org.csv";
        std::string const test_score_org_f_   = "../ut_data2/test_score_org_f.csv";
        std::string const test_score_act_     = "../ut_data2/test_score_act.csv";
        std::string const test_score_exp_     = "../ut_data2/test_score_exp.csv";
        std::string const test_score_exp_err_ = "../ut_data2/test_score_exp_err.csv";

        virtual void SetUp() noexcept override { remove_file(test_score_act_); }
        virtual void TearDown() noexcept override { remove_file(test_score_act_); }

        static void remove_file(std::string const& filename) noexcept
        {
            if (std::filesystem::exists(filename)) {
                std::filesystem::remove(filename);
            }
        }
    };

    class SolidSRP_Q : public SolidFixture {};
    class SolidOCP_Q : public SolidFixture {};
    class SolidLSP_Q : public SolidFixture {};
    class SolidISP_Q : public SolidFixture {};
    class SolidDIP_Q : public SolidFixture {};

    class SolidSRP_A : public SolidFixture {};
    class SolidOCP_A : public SolidFixture {};
    class SolidLSP_A : public SolidFixture {};
    class SolidISP_A : public SolidFixture {};
    class SolidDIP_A : public SolidFixture {};
```

### 演習-SRP <a id="SS_22_8_1"></a>
* 問題
```cpp
    //  exercise/solid_q/srp_test_score.h 8
    // [Q]
    // 下記クラスTestScoreはメンバにする必要のない関数までメンバにしてるため、
    // インターフェースが肥大化してしまい、少なくともSRPに反している。
    // メンバにする必要のないStoreCSVを外部関数にせよ。
    // また、受験者の平均点を求める
    //      TestScore::ScoreOne_t Average(TestScore const& test_score);
    // を同様の方法で作り、単体テストを行え。

    class TestScore {
    public:
        TestScore()                            = default;
        TestScore(TestScore const&)            = default;
        TestScore& operator=(TestScore const&) = delete;

        using ScoreAll_t = std::map<std::string, std::vector<int32_t>>;
        using ScoreOne_t = std::vector<std::pair<std::string, int32_t>>;

        void                        AddScore(ScoreOne_t const& one_test_score);
        std::vector<int32_t> const& GetScore(std::string const& name) const { return test_score_row_.at(name); }

        void StoreCSV(std::string const& filename) const;
        void LoadCSV(std::string const& filename);

        ScoreAll_t::const_iterator begin() const noexcept { return test_score_row_.begin(); }
        ScoreAll_t::const_iterator end() const noexcept { return test_score_row_.end(); }

    private:
        // int32_t score: 0～100はスコア、-1は未受験、それ以外は不正データ
        void       validate_score(int32_t score) const;
        ScoreAll_t test_score_row_{};
    };

    std::string ToString(TestScore const& ts);
```
```cpp
    //  exercise/solid_q/srp_test_score.cpp 10

    namespace {
    std::pair<std::string, std::vector<int32_t>> parse_line(std::string const& line)
    {
        auto const csv_sep = std::regex{R"( *, *)"};
        auto       name    = std::string{};
        auto       score   = std::vector<int32_t>{};

        auto end = std::sregex_token_iterator{};
        for (auto it = std::sregex_token_iterator{line.begin(), line.end(), csv_sep, -1}; it != end; ++it) {
            if (name.length() == 0) {
                name = *it;
            }
            else {
                auto s = std::stoi(*it);
                score.emplace_back(s);
            }
        }

        return {std::move(name), std::move(score)};
    }
    }  // namespace

    void TestScore::validate_score(int32_t score) const
    {
        auto highest = 100;
        auto lowest  = 0;
        auto invalid = -1;

        if (lowest <= score && score <= highest) {
            ;  // do notihng
        }
        else if (invalid == score) {
            ;  // do notihng
        }
        else {
            throw std::out_of_range{"Invalid Score"};
        }
    }

    void TestScore::AddScore(TestScore::ScoreOne_t const& one_test_score)
    {
        for (auto const& pair : one_test_score) {
            validate_score(pair.second);
        }

        if (test_score_row_.size() == 0) {
            test_score_row_[one_test_score[0].first] = std::vector<int32_t>{};
        }

        for (auto& pair : test_score_row_) {
            pair.second.push_back(-1);
        }

        auto curr_test_count = test_score_row_.begin()->second.size();

        for (auto const& pair : one_test_score) {
            if (test_score_row_.find(pair.first) == test_score_row_.end()) {
                test_score_row_[pair.first] = std::vector<int32_t>(curr_test_count, -1);
            }

            test_score_row_[pair.first].back() = pair.second;
        }
    }

    void TestScore::LoadCSV(std::string const& filename)
    {
        auto data = std::ifstream{filename};

        auto test_score_raw = ScoreAll_t{};
        auto line           = std::string{};
        while (std::getline(data, line)) {
            // std::pair<TestScore::ScoreAll_t::iterator, bool>
            auto ret = test_score_raw.insert(parse_line(line));
            assert(ret.second);
        }

        for (auto const& pair : test_score_raw) {
            for (auto const s : pair.second) {
                validate_score(s);
            }
        }

        test_score_row_.swap(test_score_raw);
    }

    void TestScore::StoreCSV(std::string const& filename) const
    {
        auto data = std::ofstream{filename};
        auto ss   = std::ostringstream{};

        for (auto const& pair : test_score_row_) {
            ss << pair.first;
            for (auto const s : pair.second) {
                ss << ", " << s;
            }
            ss << std::endl;
        }

        data << ss.str();
    }

    std::string ToString(TestScore const& ts)
    {
        auto ss = std::ostringstream{};

        for (auto const& pair : ts) {
            ss << pair.first << ':';
            for (auto const& s : pair.second) {
                ss << ' ' << s;
            }
            ss << std::endl;
        }

        return ss.str();
    }
```
```cpp
    //  exercise/solid_q/srp_test_score_ut.cpp 13

    namespace {

    TEST_F(SolidSRP_Q, TestScore_LoadCSV)
    {
        auto ts = TestScore{};
        ts.LoadCSV(test_score_org_);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
        };

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto const exp_str = std::string{
            "堂林: -1 50 80\n広輔: 40 30 10\n會澤: 30 60 70\n"
            "松山: 80 90 50\n菊池: 50 20 80\n鈴木: 0 80 100\n"};
        ASSERT_EQ(ToString(ts), exp_str);
    }

    std::string whole_file(std::string const& filename)
    {
        auto ifs = std::ifstream{filename};

        return std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    }

    TEST_F(SolidSRP_Q, TestScore_AddScore)
    {
        auto ts = TestScore{};
        ts.LoadCSV(test_score_org_);

        auto const one_score = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("堂林", 50),  TestScore::ScoreOne_t::value_type("広輔", 40),
            TestScore::ScoreOne_t::value_type("會澤", 70),  TestScore::ScoreOne_t::value_type("松山", 1),
            TestScore::ScoreOne_t::value_type("菊池", -1),  TestScore::ScoreOne_t::value_type("鈴木", 5),
            TestScore::ScoreOne_t::value_type("田中", 100), TestScore::ScoreOne_t::value_type("西川", 90),
        };

        ts.AddScore(one_score);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80, 50}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10, 40}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50, 1}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80, -1}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100, 5}),
            TestScore::ScoreAll_t::value_type("田中", {-1, -1, -1, 100}),
            TestScore::ScoreAll_t::value_type("西川", {-1, -1, -1, 90}),
        };

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto const one_score_err = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("野村", -2),
            TestScore::ScoreOne_t::value_type("衣笠", 40),
        };

        // 不正データロード
        auto ts2 = ts;
        ASSERT_THROW(ts.AddScore(one_score_err), std::out_of_range);

        // エクセプション 強い保証
        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
    }

    TEST_F(SolidSRP_Q, TestScore_GetScore)
    {
        auto ts = TestScore{};
        ts.LoadCSV(test_score_org_);

        auto const& score_0 = ts.GetScore("堂林");
        ASSERT_EQ((std::vector{-1, 50, 80}), score_0);

        auto const& score_1 = ts.GetScore("広輔");
        ASSERT_EQ((std::vector{40, 30, 10}), score_1);

        auto const& score_2 = ts.GetScore("會澤");
        ASSERT_EQ((std::vector{30, 60, 70}), score_2);

        auto const& score_3 = ts.GetScore("松山");
        ASSERT_EQ((std::vector{80, 90, 50}), score_3);

        auto const& score_4 = ts.GetScore("菊池");
        ASSERT_EQ((std::vector{50, 20, 80}), score_4);

        auto const& score_5 = ts.GetScore("鈴木");
        ASSERT_EQ((std::vector{0, 80, 100}), score_5);

        ASSERT_THROW(ts.GetScore("西川"), std::out_of_range);
    }

    TEST_F(SolidSRP_Q, TestScore_StoreCSV)
    {
        auto ts = TestScore{};
        ts.LoadCSV(test_score_org_);
        ts.StoreCSV(test_score_act_);

        auto content_act = whole_file(test_score_act_);
        auto content_exp = whole_file(test_score_exp_);

        ASSERT_EQ(content_exp, content_act);

        // 不正ファイルロード
        auto ts2 = ts;
        ASSERT_THROW(ts.LoadCSV(test_score_exp_err_), std::out_of_range);

        // エクセプション 強い保証
        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
    }
    }  // namespace
```

* 参照 [単一責任の原則(SRP)](solid.md#SS_8_1)
* [解答例-SRP](exercise_a.md#SS_23_8_1)


### 演習-OCP <a id="SS_22_8_2"></a>
* 問題
```cpp
    //  exercise/solid_q/ocp_test_score.h 8
    // [Q]
    // 下記クラスTestScoreは、
    //      * テスト受講者とその点数を保持/提供する。
    //      * テスト受講者とその点数をCSVファイルからロードする。
    // 責任を持つ。サポートするファイル形式が増えた場合、このクラスを修正せざるを得ないため、
    // 機能拡張に対して開いていない。つまり、OCPに反していると言える
    // (実際にはこの程度の違反が問題になることは稀である)。
    //
    // サポートしているファイル形式はCSVのみであったが、TSVを追加することになった。
    // 今後もサポートするファイル形式を増やす必要があるため、OCPに従った方が良いと判断し、
    // TestScoreの責務から「ファイルのロード」を外し、その機能を外部関数として定義することにした。
    // これに従い、下記クラスTestScoreを修正し、外部関数
    //      void LoadCSV(std::string const& filename, TestScore& test_score);
    // を作り、単体テストを行え。

    class TestScore {
    public:
        TestScore()                            = default;
        TestScore(TestScore const&)            = default;
        TestScore& operator=(TestScore const&) = delete;

        using ScoreAll_t = std::map<std::string, std::vector<int32_t>>;
        using ScoreOne_t = std::vector<std::pair<std::string, int32_t>>;

        void                        AddScore(ScoreOne_t const& one_test_score);
        std::vector<int32_t> const& GetScore(std::string const& name) const { return test_score_row_.at(name); }

        void LoadCSV(std::string const& filename);

        ScoreAll_t::const_iterator begin() const noexcept { return test_score_row_.begin(); }
        ScoreAll_t::const_iterator end() const noexcept { return test_score_row_.end(); }

    private:
        // int32_t score: 0～100はスコア、-1は未受験、それ以外は不正データ
        void       validate_score(int32_t score) const;
        ScoreAll_t test_score_row_{};
    };

    std::string           ToString(TestScore const& ts);
    void                  StoreCSV(TestScore const& test_score, std::string const& filename);
    TestScore::ScoreOne_t Average(TestScore const& test_score);
```
```cpp
    //  exercise/solid_q/ocp_test_score.cpp 10

    namespace {
    std::pair<std::string, std::vector<int32_t>> parse_line(std::string const& line)
    {
        auto const csv_sep = std::regex{R"( *, *)"};
        auto       name    = std::string{};
        auto       score   = std::vector<int32_t>{};

        auto end = std::sregex_token_iterator{};
        for (auto it = std::sregex_token_iterator{line.begin(), line.end(), csv_sep, -1}; it != end; ++it) {
            if (name.length() == 0) {
                name = *it;
            }
            else {
                auto s = std::stoi(*it);
                score.emplace_back(s);
            }
        }

        return {std::move(name), std::move(score)};
    }

    bool is_valid_score(int32_t score) noexcept { return 0 <= score && score <= 100; }

    bool not_score(int32_t score) noexcept { return score == -1; }
    }  // namespace

    void TestScore::validate_score(int32_t score) const
    {
        if (is_valid_score(score) || not_score(score)) {
            return;
        }

        throw std::out_of_range{"Invalid Score"};
    }

    void TestScore::AddScore(TestScore::ScoreOne_t const& one_test_score)
    {
        for (auto const& pair : one_test_score) {
            validate_score(pair.second);
        }

        if (test_score_row_.size() == 0) {
            test_score_row_[one_test_score[0].first] = std::vector<int32_t>{};
        }

        for (auto& pair : test_score_row_) {
            pair.second.push_back(-1);
        }

        auto curr_test_count = test_score_row_.begin()->second.size();

        for (auto const& pair : one_test_score) {
            if (test_score_row_.find(pair.first) == test_score_row_.end()) {
                test_score_row_[pair.first] = std::vector<int32_t>(curr_test_count, -1);
            }

            test_score_row_[pair.first].back() = pair.second;
        }
    }

    void TestScore::LoadCSV(std::string const& filename)
    {
        auto data = std::ifstream{filename};

        auto test_score_raw = TestScore::ScoreAll_t{};
        auto line           = std::string{};
        while (std::getline(data, line)) {
            // std::pair<TestScore::ScoreAll_t::iterator, bool>
            auto ret = test_score_raw.insert(parse_line(line));
            assert(ret.second);
        }

        for (auto const& pair : test_score_raw) {
            for (auto const s : pair.second) {
                validate_score(s);
            }
        }

        test_score_row_.swap(test_score_raw);
    }

    void StoreCSV(TestScore const& test_score, std::string const& filename)
    {
        auto data = std::ofstream{filename};
        auto ss   = std::ostringstream{};

        for (auto const& pair : test_score) {
            ss << pair.first;
            for (auto const s : pair.second) {
                ss << ", " << s;
            }
            ss << std::endl;
        }

        data << ss.str();
    }

    std::string ToString(TestScore const& ts)
    {
        auto ss = std::ostringstream{};

        for (auto const& pair : ts) {
            ss << pair.first << ':';
            for (auto const s : pair.second) {
                ss << ' ' << s;
            }
            ss << std::endl;
        }

        return ss.str();
    }

    TestScore::ScoreOne_t Average(TestScore const& test_score)
    {
        auto ret = TestScore::ScoreOne_t{};

        for (auto const& pair : test_score) {
            auto sum         = 0;
            auto valid_count = 0U;
            for (auto const s : pair.second) {
                if (is_valid_score(s)) {
                    sum += s;
                    ++valid_count;
                }
            }
            ret.emplace_back(std::make_pair(pair.first, valid_count == 0 ? -1 : sum / valid_count));
        }

        return ret;
    }
```
```cpp
    //  exercise/solid_q/ocp_test_score_ut.cpp 13

    namespace {

    TEST_F(SolidOCP_Q, TestScore_LoadCSV)
    {
        auto ts = TestScore{};
        ts.LoadCSV(test_score_org_);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
        };

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto const exp_str = std::string{
            "堂林: -1 50 80\n広輔: 40 30 10\n會澤: 30 60 70\n"
            "松山: 80 90 50\n菊池: 50 20 80\n鈴木: 0 80 100\n"};
        ASSERT_EQ(ToString(ts), exp_str);
    }

    std::string whole_file(std::string const& filename)
    {
        auto ifs = std::ifstream{filename};

        return std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    }

    TEST_F(SolidOCP_Q, TestScore_AddScore)
    {
        auto ts = TestScore{};
        ts.LoadCSV(test_score_org_);

        auto const one_score = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("堂林", 50),  TestScore::ScoreOne_t::value_type("広輔", 40),
            TestScore::ScoreOne_t::value_type("會澤", 70),  TestScore::ScoreOne_t::value_type("松山", 1),
            TestScore::ScoreOne_t::value_type("菊池", -1),  TestScore::ScoreOne_t::value_type("鈴木", 5),
            TestScore::ScoreOne_t::value_type("田中", 100), TestScore::ScoreOne_t::value_type("西川", 90),
        };

        ts.AddScore(one_score);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80, 50}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10, 40}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50, 1}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80, -1}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100, 5}),
            TestScore::ScoreAll_t::value_type("田中", {-1, -1, -1, 100}),
            TestScore::ScoreAll_t::value_type("西川", {-1, -1, -1, 90}),
        };

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto const one_score_err = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("野村", -2),
            TestScore::ScoreOne_t::value_type("衣笠", 40),
        };

        // 不正データロード
        auto ts2 = ts;
        ASSERT_THROW(ts.AddScore(one_score_err), std::out_of_range);

        // エクセプション 強い保証
        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
    }

    TEST_F(SolidOCP_Q, TestScore_GetScore)
    {
        auto ts = TestScore{};
        ts.LoadCSV(test_score_org_);

        auto const& score_0 = ts.GetScore("堂林");
        ASSERT_EQ((std::vector{-1, 50, 80}), score_0);

        auto const& score_1 = ts.GetScore("広輔");
        ASSERT_EQ((std::vector{40, 30, 10}), score_1);

        auto const& score_2 = ts.GetScore("會澤");
        ASSERT_EQ((std::vector{30, 60, 70}), score_2);

        auto const& score_3 = ts.GetScore("松山");
        ASSERT_EQ((std::vector{80, 90, 50}), score_3);

        auto const& score_4 = ts.GetScore("菊池");
        ASSERT_EQ((std::vector{50, 20, 80}), score_4);

        auto const& score_5 = ts.GetScore("鈴木");
        ASSERT_EQ((std::vector{0, 80, 100}), score_5);

        ASSERT_THROW(ts.GetScore("西川"), std::out_of_range);
    }

    TEST_F(SolidOCP_Q, TestScore_StoreCSV)
    {
        auto ts = TestScore{};
        ts.LoadCSV(test_score_org_);
        StoreCSV(ts, test_score_act_);

        auto content_act = whole_file(test_score_act_);
        auto content_exp = whole_file(test_score_exp_);

        ASSERT_EQ(content_exp, content_act);

        // 不正ファイルロード
        auto ts2 = ts;
        ASSERT_THROW(ts.LoadCSV(test_score_exp_err_), std::out_of_range);

        // エクセプション 強い保証
        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
    }

    TEST_F(SolidOCP_Q, TestScore_Average)
    {
        auto ts = TestScore{};
        ts.LoadCSV(test_score_org_);

        auto const exp = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("堂林", 65), TestScore::ScoreOne_t::value_type("広輔", 26),
            TestScore::ScoreOne_t::value_type("會澤", 53), TestScore::ScoreOne_t::value_type("松山", 73),
            TestScore::ScoreOne_t::value_type("菊池", 50), TestScore::ScoreOne_t::value_type("鈴木", 60),
        };
        auto act = Average(ts);

        ASSERT_EQ(act, exp);
    }
    }  // namespace
```

* 参照 [オープン・クローズドの原則(OCP)](solid.md#SS_8_2)
* [解答例-OCP](exercise_a.md#SS_23_8_2)


### 演習-LSP <a id="SS_22_8_3"></a>
* 問題
```cpp
    //  exercise/solid_q/lsp_test_score.h 8
    // [Q]
    // 下記クラスTestScoreが管理するテストのスコアの値は、
    //      * 0～100   テストのスコア
    //      *-1        未受験
    //      * それ以外 不正値であるため、このデータを入力すると
    //                 std::out_of_rangeエクセプションが発生する。
    // を表すが、未受講を許可しない仕様(受験できない場合のスコアは0点)の
    // TestScoreForceも必要になったため下記のように定義した。
    //      * TestScoreForceが管理するテストのスコアの値は
    //           * 0～100   テストのスコア
    //           * それ以外 不正値であるため、このデータを入力すると
    //                      std::out_of_rangeエクセプションが発生する。
    //      * それ以外の動作はTestScoreと同じ。
    //  これは、事前条件(「-1～100を受け入れる」から「0～100を受け入れる」)の強化であるため、
    //  LSPに反する。
    //  これにより起こる問題点を単体テストを用いて指摘せよ。
    //
    // [Q]
    // 上記問題を解決するため、クラスTestScoreForceFixedを作り単体テストを行え。

    class TestScore {
    public:
        TestScore()                            = default;
        virtual ~TestScore()                   = default;
        TestScore(TestScore const&)            = default;
        TestScore& operator=(TestScore const&) = delete;
        TestScore& operator=(TestScore&&)      = default;

        using ScoreAll_t = std::map<std::string, std::vector<int32_t>>;
        using ScoreOne_t = std::vector<std::pair<std::string, int32_t>>;

        void                        AddScore(ScoreOne_t const& one_test_score);
        std::vector<int32_t> const& GetScore(std::string const& name) const { return test_score_row_.at(name); }

        ScoreAll_t::const_iterator begin() const noexcept { return test_score_row_.begin(); }
        ScoreAll_t::const_iterator end() const noexcept { return test_score_row_.end(); }

    private:
        // int32_t score: 0～100はスコア、-1は未受験、それ以外は不正データ
        virtual void validate_score(int32_t score) const;
        ScoreAll_t   test_score_row_{};
    };

    class TestScoreForce : public TestScore {
    private:
        // int32_t score: 0～100はスコア、それ以外は不正データ
        virtual void validate_score(int32_t score) const override;
    };

    std::string           ToString(TestScore const& ts);
    void                  LoadCSV(std::string const& filename, TestScore& test_score);
    void                  StoreCSV(TestScore const& test_score, std::string const& filename);
    TestScore::ScoreOne_t Average(TestScore const& test_score);
```
```cpp
    //  exercise/solid_q/lsp_test_score.cpp 10

    namespace {
    std::pair<std::string, std::vector<int32_t>> parse_line(std::string const& line)
    {
        auto const csv_sep = std::regex{R"( *, *)"};
        auto       name    = std::string{};
        auto       score   = std::vector<int32_t>{};

        auto end = std::sregex_token_iterator{};
        for (auto it = std::sregex_token_iterator{line.begin(), line.end(), csv_sep, -1}; it != end; ++it) {
            if (name.length() == 0) {
                name = *it;
            }
            else {
                auto s = std::stoi(*it);
                score.emplace_back(s);
            }
        }

        return {std::move(name), std::move(score)};
    }

    bool is_valid_score(int32_t score) noexcept { return 0 <= score && score <= 100; }

    bool not_score(int32_t score) noexcept { return score == -1; }
    }  // namespace

    void TestScore::validate_score(int32_t score) const
    {
        if (is_valid_score(score) || not_score(score)) {
            return;
        }

        throw std::out_of_range{"Invalid Score"};
    }

    void TestScoreForce::validate_score(int32_t score) const
    {
        if (is_valid_score(score)) {
            return;
        }

        throw std::out_of_range{"Invalid Score"};
    }

    void TestScore::AddScore(TestScore::ScoreOne_t const& one_test_score)
    {
        for (auto const& pair : one_test_score) {
            validate_score(pair.second);
        }

        if (test_score_row_.size() == 0) {
            test_score_row_[one_test_score[0].first] = std::vector<int32_t>{};
        }

        for (auto& pair : test_score_row_) {
            pair.second.push_back(-1);
        }

        auto curr_test_count = test_score_row_.begin()->second.size();

        for (auto const& pair : one_test_score) {
            if (test_score_row_.find(pair.first) == test_score_row_.end()) {
                test_score_row_[pair.first] = std::vector<int32_t>(curr_test_count, -1);
            }

            test_score_row_[pair.first].back() = pair.second;
        }
    }

    void LoadCSV(std::string const& filename, TestScore& test_score)
    {
        auto data = std::ifstream{filename};

        auto test_score_raw = TestScore::ScoreAll_t{};
        auto line           = std::string{};
        while (std::getline(data, line)) {
            // std::pair<TestScore::ScoreAll_t::iterator, bool>
            auto ret = test_score_raw.insert(parse_line(line));
            assert(ret.second);
        }

        auto one_test = TestScore::ScoreOne_t{};
        for (auto const& pair : test_score_raw) {
            one_test.emplace_back(std::make_pair(pair.first, 0));
        }

        auto const score_count = test_score_raw.begin()->second.size();
        auto       ts          = TestScore{};

        for (auto i = 0U; i < score_count; ++i) {
            for (auto& pair : one_test) {
                pair.second = test_score_raw[pair.first][i];
            }
            ts.AddScore(one_test);
        }

        test_score = std::move(ts);
    }

    void StoreCSV(TestScore const& test_score, std::string const& filename)
    {
        auto data = std::ofstream{filename};
        auto ss   = std::ostringstream{};

        for (auto const& pair : test_score) {
            ss << pair.first;
            for (auto const s : pair.second) {
                ss << ", " << s;
            }
            ss << std::endl;
        }

        data << ss.str();
    }

    std::string ToString(TestScore const& ts)
    {
        auto ss = std::ostringstream{};

        for (auto const& pair : ts) {
            ss << pair.first << ':';
            for (auto const s : pair.second) {
                ss << ' ' << s;
            }
            ss << std::endl;
        }

        return ss.str();
    }

    TestScore::ScoreOne_t Average(TestScore const& test_score)
    {
        auto ret = TestScore::ScoreOne_t{};

        for (auto const& pair : test_score) {
            auto sum         = 0;
            auto valid_count = 0U;
            for (auto const s : pair.second) {
                if (is_valid_score(s)) {
                    sum += s;
                    ++valid_count;
                }
            }
            ret.emplace_back(std::make_pair(pair.first, valid_count == 0 ? -1 : sum / valid_count));
        }

        return ret;
    }
```
```cpp
    //  exercise/solid_q/lsp_test_score_ut.cpp 13

    namespace {

    TEST_F(SolidLSP_Q, TestScore_LoadCSV)
    {
        auto ts = TestScore{};
        LoadCSV(test_score_org_, ts);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
        };

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto exp_str = std::string{
            "堂林: -1 50 80\n広輔: 40 30 10\n會澤: 30 60 70\n"
            "松山: 80 90 50\n菊池: 50 20 80\n鈴木: 0 80 100\n"};
        ASSERT_EQ(ToString(ts), exp_str);
    }

    std::string whole_file(std::string const& filename)
    {
        auto ifs = std::ifstream{filename};

        return std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    }

    TEST_F(SolidLSP_Q, TestScore_AddScore)
    {
        auto ts = TestScore{};
        LoadCSV(test_score_org_, ts);

        auto const one_score = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("堂林", 50),  TestScore::ScoreOne_t::value_type("広輔", 40),
            TestScore::ScoreOne_t::value_type("會澤", 70),  TestScore::ScoreOne_t::value_type("松山", 1),
            TestScore::ScoreOne_t::value_type("菊池", -1),  TestScore::ScoreOne_t::value_type("鈴木", 5),
            TestScore::ScoreOne_t::value_type("田中", 100), TestScore::ScoreOne_t::value_type("西川", 90),
        };

        ts.AddScore(one_score);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80, 50}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10, 40}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50, 1}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80, -1}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100, 5}),
            TestScore::ScoreAll_t::value_type("田中", {-1, -1, -1, 100}),
            TestScore::ScoreAll_t::value_type("西川", {-1, -1, -1, 90}),
        };

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto const one_score_err = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("野村", -2),
            TestScore::ScoreOne_t::value_type("衣笠", 40),
        };

        // 不正データロード
        auto ts2 = ts;
        ASSERT_THROW(ts.AddScore(one_score_err), std::out_of_range);

        // エクセプション 強い保証
        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
    }

    TEST_F(SolidLSP_Q, TestScore_GetScore)
    {
        auto ts = TestScore{};
        LoadCSV(test_score_org_, ts);

        auto const& score_0 = ts.GetScore("堂林");
        ASSERT_EQ((std::vector{-1, 50, 80}), score_0);

        auto const& score_1 = ts.GetScore("広輔");
        ASSERT_EQ((std::vector{40, 30, 10}), score_1);

        auto const& score_2 = ts.GetScore("會澤");
        ASSERT_EQ((std::vector{30, 60, 70}), score_2);

        auto const& score_3 = ts.GetScore("松山");
        ASSERT_EQ((std::vector{80, 90, 50}), score_3);

        auto const& score_4 = ts.GetScore("菊池");
        ASSERT_EQ((std::vector{50, 20, 80}), score_4);

        auto const& score_5 = ts.GetScore("鈴木");
        ASSERT_EQ((std::vector{0, 80, 100}), score_5);

        ASSERT_THROW(ts.GetScore("西川"), std::out_of_range);
    }

    TEST_F(SolidLSP_Q, TestScore_StoreCSV)
    {
        auto ts = TestScore{};
        LoadCSV(test_score_org_, ts);
        StoreCSV(ts, test_score_act_);

        auto content_act = whole_file(test_score_act_);
        auto content_exp = whole_file(test_score_exp_);

        ASSERT_EQ(content_exp, content_act);

        // 不正ファイルロード
        auto ts2 = ts;
        ASSERT_THROW(LoadCSV(test_score_exp_err_, ts2), std::out_of_range);

        // エクセプション 強い保証
        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
    }

    TEST_F(SolidLSP_Q, TestScore_Average)
    {
        auto ts = TestScore{};
        LoadCSV(test_score_org_, ts);

        auto const exp = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("堂林", 65), TestScore::ScoreOne_t::value_type("広輔", 26),
            TestScore::ScoreOne_t::value_type("會澤", 53), TestScore::ScoreOne_t::value_type("松山", 73),
            TestScore::ScoreOne_t::value_type("菊池", 50), TestScore::ScoreOne_t::value_type("鈴木", 60),
        };
        auto act = Average(ts);

        ASSERT_EQ(act, exp);
    }
    }  // namespace
```

* 参照 [リスコフの置換原則(LSP)](solid.md#SS_8_3)
* [解答例-LSP](exercise_a.md#SS_23_8_3)


### 演習-ISP <a id="SS_22_8_4"></a>
* 問題
```cpp
    //  exercise/solid_q/isp_test_score.h 8
    // [Q]
    // 下記クラスTestScoreの管理データの内、受験者とその平均スコア、
    // 平均スコアの高い順でソートされた受験者リストを扱うクラスが必要になったため、
    // 下記のようにイミュータブルなクラスTestScoreAverageを作成した。
    //
    // 現在のファイル構成では、TestScoreAverageのみを使うクラスや関数にも、
    // このファイル全体への依存を強いる(つまり、TestScoreやLoadCSV等に依存させる)ため、
    // ISPに反する。
    // TestScoreAverageを使うクラスや関数に余計な依存関係が発生しないようにリファクタリングを
    // 行え。

    class TestScore {
    public:
        TestScore()                            = default;
        TestScore(TestScore const&)            = default;
        TestScore& operator=(TestScore const&) = delete;
        TestScore& operator=(TestScore&&)      = default;

        using ScoreAll_t = std::map<std::string, std::vector<int32_t>>;
        using ScoreOne_t = std::vector<std::pair<std::string, int32_t>>;

        void                        AddScore(ScoreOne_t const& one_test_score);
        std::vector<int32_t> const& GetScore(std::string const& name) const { return test_score_row_.at(name); }

        ScoreAll_t::const_iterator begin() const noexcept { return test_score_row_.begin(); }
        ScoreAll_t::const_iterator end() const noexcept { return test_score_row_.end(); }

    private:
        // int32_t score: 0～100はスコア、-1は未受験、それ以外は不正データ
        void       validate_score(int32_t score) const;
        ScoreAll_t test_score_row_{};
    };

    std::string           ToString(TestScore const& ts);
    TestScore             LoadCSV(std::string const& filename);
    void                  StoreCSV(TestScore const& test_score, std::string const& filename);
    TestScore::ScoreOne_t Average(TestScore const& test_score);

    class TestScoreAverage {
    public:
        explicit TestScoreAverage(std::string const& filename);
        uint32_t                        GetAverage(std::string const& name) const;
        std::vector<std::string> const& DescendingOrder() const;

    private:
        TestScore::ScoreOne_t const      average_;
        mutable std::vector<std::string> desending_order_{};
    };
```
```cpp
    //  exercise/solid_q/isp_test_score.cpp 10

    namespace {
    std::pair<std::string, std::vector<int32_t>> parse_line(std::string const& line)
    {
        auto const csv_sep = std::regex{R"( *, *)"};
        auto       name    = std::string{};
        auto       score   = std::vector<int32_t>{};

        auto end = std::sregex_token_iterator{};
        for (auto it = std::sregex_token_iterator{line.begin(), line.end(), csv_sep, -1}; it != end; ++it) {
            if (name.length() == 0) {
                name = *it;
            }
            else {
                auto s = std::stoi(*it);
                score.emplace_back(s);
            }
        }

        return {std::move(name), std::move(score)};
    }

    bool is_valid_score(int32_t score) noexcept { return 0 <= score && score <= 100; }

    bool not_score(int32_t score) noexcept { return score == -1; }
    }  // namespace

    void TestScore::validate_score(int32_t score) const
    {
        if (is_valid_score(score) || not_score(score)) {
            return;
        }

        throw std::out_of_range{"Invalid Score"};
    }

    void TestScore::AddScore(TestScore::ScoreOne_t const& one_test_score)
    {
        for (auto const& pair : one_test_score) {
            validate_score(pair.second);
        }

        if (test_score_row_.size() == 0) {
            test_score_row_[one_test_score[0].first] = std::vector<int32_t>{};
        }

        for (auto& pair : test_score_row_) {
            pair.second.push_back(-1);
        }

        auto curr_test_count = test_score_row_.begin()->second.size();

        for (auto const& pair : one_test_score) {
            if (test_score_row_.find(pair.first) == test_score_row_.end()) {
                test_score_row_[pair.first] = std::vector<int32_t>(curr_test_count, -1);
            }

            test_score_row_[pair.first].back() = pair.second;
        }
    }

    TestScore LoadCSV(std::string const& filename)
    {
        auto data = std::ifstream{filename};

        auto test_score_raw = TestScore::ScoreAll_t{};
        auto line           = std::string{};
        while (std::getline(data, line)) {
            // std::pair<TestScore::ScoreAll_t::iterator, bool>
            auto ret = test_score_raw.insert(parse_line(line));
            assert(ret.second);
        }

        auto one_test = TestScore::ScoreOne_t{};
        for (auto const& pair : test_score_raw) {
            one_test.emplace_back(std::make_pair(pair.first, 0));
        }

        auto const score_count = test_score_raw.begin()->second.size();
        auto       ts          = TestScore{};

        for (auto i = 0U; i < score_count; ++i) {
            for (auto& pair : one_test) {
                pair.second = test_score_raw[pair.first][i];
            }
            ts.AddScore(one_test);
        }

        return ts;
    }

    void StoreCSV(TestScore const& test_score, std::string const& filename)
    {
        auto data = std::ofstream{filename};
        auto ss   = std::ostringstream{};

        for (auto const& pair : test_score) {
            ss << pair.first;
            for (auto const s : pair.second) {
                ss << ", " << s;
            }
            ss << std::endl;
        }

        data << ss.str();
    }

    std::string ToString(TestScore const& ts)
    {
        auto ss = std::ostringstream{};

        for (auto const& pair : ts) {
            ss << pair.first << ':';
            for (auto const s : pair.second) {
                ss << ' ' << s;
            }
            ss << std::endl;
        }

        return ss.str();
    }

    TestScore::ScoreOne_t Average(TestScore const& test_score)
    {
        auto ret = TestScore::ScoreOne_t{};

        for (auto const& pair : test_score) {
            auto sum         = 0;
            auto valid_count = 0U;
            for (auto const s : pair.second) {
                if (is_valid_score(s)) {
                    sum += s;
                    ++valid_count;
                }
            }
            ret.emplace_back(std::make_pair(pair.first, valid_count == 0 ? -1 : sum / valid_count));
        }

        return ret;
    }

    namespace {
    TestScore::ScoreOne_t get_average(std::string const& filename)
    {
        TestScore ts = LoadCSV(filename);

        return Average(ts);
    }
    }  // namespace

    TestScoreAverage::TestScoreAverage(std::string const& filename) : average_{get_average(filename)} {}

    uint32_t TestScoreAverage::GetAverage(std::string const& name) const
    {
        auto pos
            = std::find_if(average_.cbegin(), average_.cend(),
                           [&name](std::pair<std::string, int32_t> const& pair) noexcept { return name == pair.first; });

        if (pos == average_.cend()) {
            throw std::out_of_range{"no member"};
        }

        return pos->second;
    }

    std::vector<std::string> const& TestScoreAverage::DescendingOrder() const
    {
        if (desending_order_.size() != 0) {
            return desending_order_;
        }

        auto ave = average_;
        std::sort(ave.begin(), ave.end(), [](std::pair<std::string, int32_t> const& lhs, auto const& rhs) noexcept {
            return lhs.second > rhs.second;
        });

        for (auto& pair : ave) {
            desending_order_.emplace_back(std::move(pair.first));
        }

        return desending_order_;
    }
```
```cpp
    //  exercise/solid_q/isp_test_score_ut.cpp 13

    namespace {

    TEST_F(SolidISP_Q, TestScore_LoadCSV)
    {
        TestScore ts = LoadCSV(test_score_org_);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
        };

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto exp_str = std::string{
            "堂林: -1 50 80\n広輔: 40 30 10\n會澤: 30 60 70\n"
            "松山: 80 90 50\n菊池: 50 20 80\n鈴木: 0 80 100\n"};
        ASSERT_EQ(ToString(ts), exp_str);
    }

    std::string whole_file(std::string const& filename)
    {
        auto ifs = std::ifstream{filename};

        return std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    }

    TEST_F(SolidISP_Q, TestScore_AddScore)
    {
        TestScore ts = LoadCSV(test_score_org_);

        auto const one_score = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("堂林", 50),  TestScore::ScoreOne_t::value_type("広輔", 40),
            TestScore::ScoreOne_t::value_type("會澤", 70),  TestScore::ScoreOne_t::value_type("松山", 1),
            TestScore::ScoreOne_t::value_type("菊池", -1),  TestScore::ScoreOne_t::value_type("鈴木", 5),
            TestScore::ScoreOne_t::value_type("田中", 100), TestScore::ScoreOne_t::value_type("西川", 90),
        };

        ts.AddScore(one_score);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80, 50}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10, 40}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50, 1}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80, -1}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100, 5}),
            TestScore::ScoreAll_t::value_type("田中", {-1, -1, -1, 100}),
            TestScore::ScoreAll_t::value_type("西川", {-1, -1, -1, 90}),
        };

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto const one_score_err = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("野村", -2),
            TestScore::ScoreOne_t::value_type("衣笠", 40),
        };

        // 不正データロード
        auto ts2 = ts;
        ASSERT_THROW(ts.AddScore(one_score_err), std::out_of_range);

        // エクセプション 強い保証
        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
    }

    TEST_F(SolidISP_Q, TestScore_GetScore)
    {
        TestScore ts = LoadCSV(test_score_org_);

        auto const& score_0 = ts.GetScore("堂林");
        ASSERT_EQ((std::vector{-1, 50, 80}), score_0);

        auto const& score_1 = ts.GetScore("広輔");
        ASSERT_EQ((std::vector{40, 30, 10}), score_1);

        auto const& score_2 = ts.GetScore("會澤");
        ASSERT_EQ((std::vector{30, 60, 70}), score_2);

        auto const& score_3 = ts.GetScore("松山");
        ASSERT_EQ((std::vector{80, 90, 50}), score_3);

        auto const& score_4 = ts.GetScore("菊池");
        ASSERT_EQ((std::vector{50, 20, 80}), score_4);

        auto const& score_5 = ts.GetScore("鈴木");
        ASSERT_EQ((std::vector{0, 80, 100}), score_5);

        ASSERT_THROW(ts.GetScore("西川"), std::out_of_range);
    }

    TEST_F(SolidISP_Q, TestScore_StoreCSV)
    {
        TestScore ts = LoadCSV(test_score_org_);
        StoreCSV(ts, test_score_act_);

        auto content_act = whole_file(test_score_act_);
        auto content_exp = whole_file(test_score_exp_);

        ASSERT_EQ(content_exp, content_act);

        // 不正ファイルロード
        auto ts2 = ts;
        ASSERT_THROW(ts2 = LoadCSV(test_score_exp_err_), std::out_of_range);

        // エクセプション 強い保証
        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
    }

    TEST_F(SolidISP_Q, TestScore_Average)
    {
        TestScore ts = LoadCSV(test_score_org_);

        auto const exp = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("堂林", 65), TestScore::ScoreOne_t::value_type("広輔", 26),
            TestScore::ScoreOne_t::value_type("會澤", 53), TestScore::ScoreOne_t::value_type("松山", 73),
            TestScore::ScoreOne_t::value_type("菊池", 50), TestScore::ScoreOne_t::value_type("鈴木", 60),
        };
        auto act = Average(ts);

        ASSERT_EQ(act, exp);
    }

    TEST_F(SolidISP_Q, TestScoreAverage)
    {
        auto tsa = TestScoreAverage{test_score_org_};

        ASSERT_EQ(tsa.GetAverage("堂林"), 65);
        ASSERT_EQ(tsa.GetAverage("広輔"), 26);
        ASSERT_EQ(tsa.GetAverage("會澤"), 53);
        ASSERT_EQ(tsa.GetAverage("松山"), 73);
        ASSERT_EQ(tsa.GetAverage("菊池"), 50);
        ASSERT_EQ(tsa.GetAverage("鈴木"), 60);

        ASSERT_THROW(tsa.GetAverage("野村"), std::out_of_range);

        auto const exp = std::vector<std::string>{
            "松山", "堂林", "鈴木", "會澤", "菊池", "広輔",
        };

        ASSERT_EQ(tsa.DescendingOrder(), exp);
        ASSERT_EQ(tsa.DescendingOrder(), exp);  // キャッシュのテスト
    }
    }  // namespace
```

* 参照 [インターフェース分離の原則(ISP)](solid.md#SS_8_4)
* [解答例-ISP](exercise_a.md#SS_23_8_4)


### 演習-DIP <a id="SS_22_8_5"></a>
* 問題
```cpp
    //  exercise/solid_q/dip_test_score.h 9
    // [Q]
    // クラスTestScoreClientは、
    //      * dip_test_score_client.h
    //      * dip_test_score_client.cpp
    // で宣言・定義され、
    // クラスTestScoreLoaderは、
    //      * dip_test_score.h(このファイル)
    //      * dip_test_score.cpp
    // で宣言・定義されされている。
    // TestScoreLoaderは宣言・定義の中にTestScoreClientを使用しているため、
    //      * dip_test_score.cpp -> dip_test_score_client.h
    // の依存関係が発生してる(dip_test_score.h -> dip_test_score_client.hの依存関係は、
    // dip_test_score.h内のTestScoreClientの前方宣言で回避)。
    // クラスの名前からもわかる通り、
    //      * TestScoreClientはTestScoreLoaderのクライアント
    //      * TestScoreLoaderはTestScoreClientのサーバ
    // であるため、この依存関係
    //      * TestScoreLoader -> TestScoreClient(逆の依存関係もあるため、双方向依存)
    //      * dip_test_score.cpp -> dip_test_score_client.h
    // はDIPに反し、機能拡張(や、場合よっては単体テスト可能なパッケージ構成維持)
    // に多大な悪影響がある(TestScoreLoaderを使うTestScoreClient2を新たに定義したときに
    // TestScoreLoaderがどのように修正されるかを考えればこの問題に気づくだろう)。
    // この問題に対処せよ。

    class TestScore {
    public:
        TestScore()                            = default;
        TestScore(TestScore const&)            = default;
        TestScore& operator=(TestScore const&) = delete;
        TestScore& operator=(TestScore&&)      = default;

        using ScoreAll_t = std::map<std::string, std::vector<int32_t>>;
        using ScoreOne_t = std::vector<std::pair<std::string, int32_t>>;

        void                        AddScore(ScoreOne_t const& one_test_score);
        std::vector<int32_t> const& GetScore(std::string const& name) const { return test_score_row_.at(name); }

        ScoreAll_t::const_iterator begin() const noexcept { return test_score_row_.begin(); }
        ScoreAll_t::const_iterator end() const noexcept { return test_score_row_.end(); }

    private:
        // int32_t score: 0～100はスコア、-1は未受験、それ以外は不正データ
        void       validate_score(int32_t score) const;
        ScoreAll_t test_score_row_{};
    };

    std::string           ToString(TestScore const& ts);
    TestScore             LoadCSV(std::string const& filename);
    void                  StoreCSV(TestScore const& test_score, std::string const& filename);
    TestScore::ScoreOne_t Average(TestScore const& test_score);

    class TestScoreClient;
    class TestScoreLoader {
    public:
        TestScoreLoader() {}
        ~TestScoreLoader();
        void      LoadCSV_Async(std::string&& filename, TestScoreClient& client);
        TestScore LoadCSV_Get() { return future_.get(); }

    private:
        std::future<TestScore> future_{};
    };
```
```cpp
    //  exercise/solid_q/dip_test_score.cpp 11

    namespace {
    std::pair<std::string, std::vector<int32_t>> parse_line(std::string const& line)
    {
        auto const csv_sep = std::regex{R"( *, *)"};
        auto       name    = std::string{};
        auto       score   = std::vector<int32_t>{};

        auto end = std::sregex_token_iterator{};
        for (auto it = std::sregex_token_iterator{line.begin(), line.end(), csv_sep, -1}; it != end; ++it) {
            if (name.length() == 0) {
                name = *it;
            }
            else {
                auto s = std::stoi(*it);
                score.emplace_back(s);
            }
        }

        return {std::move(name), std::move(score)};
    }

    bool is_valid_score(int32_t score) noexcept { return 0 <= score && score <= 100; }

    bool not_score(int32_t score) noexcept { return score == -1; }
    }  // namespace

    void TestScore::validate_score(int32_t score) const
    {
        if (is_valid_score(score) || not_score(score)) {
            return;
        }

        throw std::out_of_range{"Invalid Score"};
    }

    void TestScore::AddScore(TestScore::ScoreOne_t const& one_test_score)
    {
        for (auto const& pair : one_test_score) {
            validate_score(pair.second);
        }

        if (test_score_row_.size() == 0) {
            test_score_row_[one_test_score[0].first] = std::vector<int32_t>{};
        }

        for (auto& pair : test_score_row_) {
            pair.second.push_back(-1);
        }

        auto curr_test_count = test_score_row_.begin()->second.size();

        for (auto const& pair : one_test_score) {
            if (test_score_row_.find(pair.first) == test_score_row_.end()) {
                test_score_row_[pair.first] = std::vector<int32_t>(curr_test_count, -1);
            }

            test_score_row_[pair.first].back() = pair.second;
        }
    }

    TestScore LoadCSV(std::string const& filename)
    {
        auto data = std::ifstream{filename};

        auto test_score_raw = TestScore::ScoreAll_t{};
        auto line           = std::string{};
        while (std::getline(data, line)) {
            // std::pair<TestScore::ScoreAll_t::iterator, bool>
            auto ret = test_score_raw.insert(parse_line(line));
            assert(ret.second);
        }

        auto one_test = TestScore::ScoreOne_t{};
        for (auto const& pair : test_score_raw) {
            one_test.emplace_back(std::make_pair(pair.first, 0));
        }

        auto const score_count = test_score_raw.begin()->second.size();
        auto       ts          = TestScore{};

        for (auto i = 0U; i < score_count; ++i) {
            for (auto& pair : one_test) {
                pair.second = test_score_raw[pair.first][i];
            }
            ts.AddScore(one_test);
        }

        return ts;
    }

    void StoreCSV(TestScore const& test_score, std::string const& filename)
    {
        auto data = std::ofstream{filename};
        auto ss   = std::ostringstream{};

        for (auto const& pair : test_score) {
            ss << pair.first;
            for (auto const s : pair.second) {
                ss << ", " << s;
            }
            ss << std::endl;
        }

        data << ss.str();
    }

    std::string ToString(TestScore const& ts)
    {
        auto ss = std::ostringstream{};

        for (auto const& pair : ts) {
            ss << pair.first << ':';
            for (auto const s : pair.second) {
                ss << ' ' << s;
            }
            ss << std::endl;
        }

        return ss.str();
    }

    TestScore::ScoreOne_t Average(TestScore const& test_score)
    {
        auto ret = TestScore::ScoreOne_t{};

        for (auto const& pair : test_score) {
            auto sum         = 0;
            auto valid_count = 0U;
            for (auto const s : pair.second) {
                if (is_valid_score(s)) {
                    sum += s;
                    ++valid_count;
                }
            }
            ret.emplace_back(std::make_pair(pair.first, valid_count == 0 ? -1 : sum / valid_count));
        }

        return ret;
    }

    TestScoreLoader::~TestScoreLoader()
    {
        if (future_.valid()) {
            future_.get();
        }
    }

    void TestScoreLoader::LoadCSV_Async(std::string&& filename, TestScoreClient& client)
    {
        if (future_.valid()) {
            future_.get();
        }

        future_ = std::async(std::launch::async, [&client, filename = std::move(filename)]() {
            auto test_score = LoadCSV(filename);
            client.Done();
            return test_score;
        });
    }
```
```cpp
    //  exercise/solid_q/dip_test_score_ut.cpp 13

    namespace {

    TEST_F(SolidDIP_Q, TestScore_LoadCSV)
    {
        TestScore ts = LoadCSV(test_score_org_);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
        };

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto exp_str = std::string{
            "堂林: -1 50 80\n広輔: 40 30 10\n會澤: 30 60 70\n"
            "松山: 80 90 50\n菊池: 50 20 80\n鈴木: 0 80 100\n"};
        ASSERT_EQ(ToString(ts), exp_str);
    }

    std::string whole_file(std::string const& filename)
    {
        auto ifs = std::ifstream{filename};

        return std::string{std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
    }

    TEST_F(SolidDIP_Q, TestScore_AddScore)
    {
        TestScore ts = LoadCSV(test_score_org_);

        auto const one_score = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("堂林", 50),  TestScore::ScoreOne_t::value_type("広輔", 40),
            TestScore::ScoreOne_t::value_type("會澤", 70),  TestScore::ScoreOne_t::value_type("松山", 1),
            TestScore::ScoreOne_t::value_type("菊池", -1),  TestScore::ScoreOne_t::value_type("鈴木", 5),
            TestScore::ScoreOne_t::value_type("田中", 100), TestScore::ScoreOne_t::value_type("西川", 90),
        };

        ts.AddScore(one_score);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80, 50}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10, 40}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50, 1}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80, -1}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100, 5}),
            TestScore::ScoreAll_t::value_type("田中", {-1, -1, -1, 100}),
            TestScore::ScoreAll_t::value_type("西川", {-1, -1, -1, 90}),
        };

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto const one_score_err = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("野村", -2),
            TestScore::ScoreOne_t::value_type("衣笠", 40),
        };

        // 不正データロード
        auto ts2 = ts;
        ASSERT_THROW(ts.AddScore(one_score_err), std::out_of_range);

        // エクセプション 強い保証
        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
    }

    TEST_F(SolidDIP_Q, TestScore_GetScore)
    {
        TestScore ts = LoadCSV(test_score_org_);

        auto const& score_0 = ts.GetScore("堂林");
        ASSERT_EQ((std::vector{-1, 50, 80}), score_0);

        auto const& score_1 = ts.GetScore("広輔");
        ASSERT_EQ((std::vector{40, 30, 10}), score_1);

        auto const& score_2 = ts.GetScore("會澤");
        ASSERT_EQ((std::vector{30, 60, 70}), score_2);

        auto const& score_3 = ts.GetScore("松山");
        ASSERT_EQ((std::vector{80, 90, 50}), score_3);

        auto const& score_4 = ts.GetScore("菊池");
        ASSERT_EQ((std::vector{50, 20, 80}), score_4);

        auto const& score_5 = ts.GetScore("鈴木");
        ASSERT_EQ((std::vector{0, 80, 100}), score_5);

        ASSERT_THROW(ts.GetScore("西川"), std::out_of_range);
    }

    TEST_F(SolidDIP_Q, TestScore_StoreCSV)
    {
        TestScore ts = LoadCSV(test_score_org_);
        StoreCSV(ts, test_score_act_);

        auto content_act = whole_file(test_score_act_);
        auto content_exp = whole_file(test_score_exp_);

        ASSERT_EQ(content_exp, content_act);

        // 不正ファイルロード
        auto ts2 = ts;
        ASSERT_THROW(ts2 = LoadCSV(test_score_exp_err_), std::out_of_range);

        // エクセプション 強い保証
        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), ts2.begin()));
    }

    TEST_F(SolidDIP_Q, TestScore_Average)
    {
        TestScore ts = LoadCSV(test_score_org_);

        auto const exp = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("堂林", 65), TestScore::ScoreOne_t::value_type("広輔", 26),
            TestScore::ScoreOne_t::value_type("會澤", 53), TestScore::ScoreOne_t::value_type("松山", 73),
            TestScore::ScoreOne_t::value_type("菊池", 50), TestScore::ScoreOne_t::value_type("鈴木", 60),
        };
        auto act = Average(ts);

        ASSERT_EQ(act, exp);
    }
    }  // namespace
```
```cpp
    //  exercise/solid_q/dip_test_score_client.h 11

    class TestScoreClient {
    public:
        void             LoadAsync(std::string&& filename);
        void             Done();
        void             Wait();
        TestScore const& GetTestScore() const noexcept { return test_score_; }

    private:
        std::condition_variable condition_{};
        std::mutex              mutex_{};
        TestScore               test_score_{};
        TestScoreLoader         loader_{};
        bool                    loaded_{false};
    };
```
```cpp
    //  exercise/solid_q/dip_test_score_client.cpp 5

    void TestScoreClient::LoadAsync(std::string&& filename) { loader_.LoadCSV_Async(std::move(filename), *this); }

    void TestScoreClient::Done()
    {
        {
            auto lock = std::lock_guard{mutex_};
            loaded_   = true;
        }

        condition_.notify_all();
    }

    void TestScoreClient::Wait()
    {
        auto lock = std::unique_lock{mutex_};

        condition_.wait(lock, [&loaded = loaded_] { return loaded; });

        test_score_ = loader_.LoadCSV_Get();
    }
```
```cpp
    //  exercise/solid_q/dip_test_score_client_ut.cpp 9

    namespace {

    TEST_F(SolidDIP_Q, TestStoreClient_LoadAsync)
    {
        auto tsc = TestScoreClient{};

        tsc.LoadAsync("../ut_data2/test_score_org.csv");

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
        };

        // ここで何か別のことをして終わったら
        tsc.Wait();

        auto const& ts = tsc.GetTestScore();

        ASSERT_TRUE(std::equal(ts.begin(), ts.end(), exp.begin()));

        auto const exp_str = std::string{
            "堂林: -1 50 80\n広輔: 40 30 10\n會澤: 30 60 70\n"
            "松山: 80 90 50\n菊池: 50 20 80\n鈴木: 0 80 100\n"};
        ASSERT_EQ(ToString(ts), exp_str);
    }
    }  // namespace
```

* 参照 [依存関係逆転の原則(DIP)](solid.md#SS_8_5)
* [解答例-DIP](exercise_a.md#SS_23_8_5)


### 演習-SOLIDの定義 <a id="SS_22_8_6"></a>
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

* [解答-SOLIDの定義](exercise_a.md#SS_23_8_6)


## デザインパターン <a id="SS_22_9"></a>
### 演習-ガード節 <a id="SS_22_9_1"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/guard.cpp 7
    // [Q]
    // 以下の関数PrimeNumbersをガード節や、関数の括りだし等によってリファクタリングせよ。

    std::optional<std::vector<uint32_t>> PrimeNumbers(uint32_t max_number)
    {
        if (max_number < 65536) {  // 演算コストが高いためエラーにする
            auto result = std::vector<uint32_t>{};

            if (max_number >= 2) {
                auto prime_num    = 2U;                                       // 最初の素数
                auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない
                is_num_prime[0] = is_num_prime[1] = false;

                do {
                    result.emplace_back(prime_num);

                    for (auto i = 2 * prime_num; i < is_num_prime.size(); i += prime_num) {
                        is_num_prime[i] = false;  // 次の倍数は素数ではない
                    }

                    do {  // 次の素数の探索
                        ++prime_num;
                    } while (!is_num_prime[prime_num] && (prime_num < is_num_prime.size()));

                } while (prime_num < is_num_prime.size());
            }
            return result;
        }

        return std::nullopt;
    }

    TEST(DesignPatternQ, Guard)
    {
        auto result = PrimeNumbers(1);
        ASSERT_TRUE(result);
        ASSERT_EQ((std::vector<uint32_t>{}), *result);

        result = PrimeNumbers(2);
        ASSERT_TRUE(result);
        ASSERT_EQ((std::vector<uint32_t>{2}), *result);

        result = PrimeNumbers(30);
        ASSERT_TRUE(result);
        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), *result);

        ASSERT_FALSE(PrimeNumbers(65536));
    }
```

* 参照 [ガード節(Early Return)](cpp_idioms.md#SS_21_1_1)
* [解答例-ガード節](exercise_a.md#SS_23_9_1)


### 演習-BitmaskType <a id="SS_22_9_2"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/enum_bitmask.cpp 5
    // [Q]
    // 下記関数ColorMask2Strはuint32_t型のビットマスクを引数に取る。
    // これはユーザが使用間違いを起こしやすい脆弱なインターフェースである。
    // enumによるビットマスク表現を使用しこの問題に対処せよ。

    constexpr auto COLOR_RED    = 0b0001U;
    constexpr auto COLOR_YELLOW = 0b0010U;
    constexpr auto COLOR_GREEN  = 0b0100U;
    constexpr auto COLOR_BLUE   = 0b1000U;

    std::string ColorMask2Str(uint32_t color)
    {
        auto ret = std::string{};

        if (COLOR_RED & color) {
            ret += "RED";
        }
        if (COLOR_YELLOW & color) {
            if (ret.size() != 0) {
                ret += ',';
            }
            ret += "YELLOW";
        }
        if (COLOR_GREEN & color) {
            if (ret.size() != 0) {
                ret += ',';
            }
            ret += "GREEN";
        }
        if (COLOR_BLUE & color) {
            if (ret.size() != 0) {
                ret += ',';
            }
            ret += "BLUE";
        }

        return ret;
    }

    TEST(DesignPatternQ, EnumBitmask)
    {
        ASSERT_EQ("RED", ColorMask2Str(COLOR_RED));
        ASSERT_EQ("RED,YELLOW", ColorMask2Str(COLOR_RED | COLOR_YELLOW));
        ASSERT_EQ("YELLOW", ColorMask2Str(COLOR_YELLOW));
        ASSERT_EQ("YELLOW,GREEN,BLUE", ColorMask2Str(COLOR_YELLOW | COLOR_GREEN | COLOR_BLUE));

        ASSERT_EQ("", ColorMask2Str(0b10000));  // 想定していない使用法
    }
```

* 参照 [BitmaskType](cpp_idioms.md#SS_21_2_3)
* [解答例-BitmaskType](exercise_a.md#SS_23_9_2)


### 演習-Pimpl <a id="SS_22_9_3"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/pimpl.cpp 5
    // [Q] 下記クラスCollectionの宣言はクラスWidgetの宣言に依存している。
    // Pimplパターンを使用し、Collectionの宣言がWidgetの宣言に依存しないようにせよ。

    class Widget {
    public:
        explicit Widget(char const* name) : name_{name} {}
        char const* Name() const noexcept { return name_; }

    private:
        char const* name_;
    };

    class Collection {
    public:
        char const* Name(size_t i) const { return widgets_.at(i).Name(); }
        void        AddName(char const* name) { widgets_.emplace_back(name); }

        size_t Count() const noexcept { return widgets_.size(); }

    private:
        std::vector<Widget> widgets_{};
    };

    TEST(DesignPatternQ, Pimpl)
    {
        auto c = Collection{};

        ASSERT_EQ(0, c.Count());
        ASSERT_THROW(c.Name(0), std::out_of_range);

        c.AddName("n0");
        c.AddName("n1");
        c.AddName("n2");

        ASSERT_EQ(3, c.Count());
        ASSERT_STREQ("n0", c.Name(0));
        ASSERT_STREQ("n1", c.Name(1));
        ASSERT_STREQ("n2", c.Name(2));
        ASSERT_THROW(c.Name(4), std::out_of_range);
    }

```

* 参照 [Pimpl](cpp_idioms.md#SS_21_2_1)
* [解答例-Pimpl](exercise_a.md#SS_23_9_3)


### 演習-Accessorの副作用 <a id="SS_22_9_4"></a>
* 問題  
  Accessor(特にセッター)には重大な副作用がある。その副作用を下記から選択せよ。

* 選択肢  
    1. クラスのカプセル化の破壊
    2. SRPへの違反
    3. 関数の巨大化
    4. クラスの巨大化

* [解答-Accessorの副作用](exercise_a.md#SS_23_9_4)


### 演習-Accessor <a id="SS_22_9_5"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/accessor.cpp 5
    // [Q]
    // 下記クラスPrimeNumbersはAccessorの多用により、クラスのカプセル化が破壊されている例である。
    // これにより、このクラスは凝集性が低く、誤用を誘発しやすい。
    // この問題を解決するため、クラスPrimeNumbersや関数GetPrimeNumbersを修正せよ。
    // また、別の問題があれば合わせて修正せよ。

    class PrimeNumbers {
    public:
        uint32_t GetMaxNumber() const { return max_number_; }
        void     SetMaxNumber(uint32_t max_number) { max_number_ = max_number; }
        bool     HasCache() const { return cached_; }
        void     Cashed(bool cached) { cached_ = cached; }

        std::vector<uint32_t>& GetPrimeNumbers() { return prime_numbers_; }

    private:
        uint32_t              max_number_;
        bool                  cached_;
        std::vector<uint32_t> prime_numbers_;
    };

    inline uint32_t next_prime_num(uint32_t curr_prime_num, std::vector<bool>& is_num_prime)
    {
        for (auto i = 2 * curr_prime_num; i < is_num_prime.size(); i += curr_prime_num) {
            is_num_prime[i] = false;  // 次の倍数は素数ではない
        }

        auto prime_num = curr_prime_num;

        do {  // 次の素数の探索
            ++prime_num;
        } while (!is_num_prime[prime_num] && (prime_num < is_num_prime.size()));

        return prime_num;
    }

    inline std::vector<uint32_t> get_prime_numbers(uint32_t max_number)
    {
        auto result       = std::vector<uint32_t>{};
        auto prime_num    = 2U;                                       // 最初の素数
        auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない。
        is_num_prime[0] = is_num_prime[1] = false;

        do {
            result.emplace_back(prime_num);
            prime_num = next_prime_num(prime_num, is_num_prime);
        } while (prime_num < is_num_prime.size());

        return result;
    }

    void GetPrimeNumbers(PrimeNumbers& pm)
    {
        if (pm.HasCache()) {
            return;
        }

        if (pm.GetMaxNumber() < 2) {  // ガード節。2未満の素数はない。
            pm.GetPrimeNumbers().clear();
            return;
        }

        pm.GetPrimeNumbers() = get_prime_numbers(pm.GetMaxNumber());
    }

    TEST(DesignPatternQ, Accessor)
    {
        auto pm = PrimeNumbers{};

        pm.SetMaxNumber(1);
        pm.Cashed(false);
        GetPrimeNumbers(pm);
        pm.Cashed(true);

        ASSERT_EQ((std::vector<uint32_t>{}), pm.GetPrimeNumbers());

        pm.SetMaxNumber(3);
        pm.Cashed(false);
        GetPrimeNumbers(pm);
        pm.Cashed(true);

        ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm.GetPrimeNumbers());

        pm.SetMaxNumber(30);
        pm.Cashed(false);
        GetPrimeNumbers(pm);
        pm.Cashed(true);

        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm.GetPrimeNumbers());

        pm.SetMaxNumber(3);
        GetPrimeNumbers(pm);  // pm.Cashed(false);しないので前のまま。
                              // このような用途は考えづらいので、おそらく仕様のバグ。

        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm.GetPrimeNumbers());
    }
```

* 参照 [Accessor](cpp_idioms.md#SS_21_1_5)
* [解答例-Accessor](exercise_a.md#SS_23_9_5)


### 演習-Copy-And-Swap <a id="SS_22_9_6"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/copy_and_swap.cpp 5
    // [Q]
    // 以下のクラスCopyAndSwapの
    //  * copyコンストラクタ
    //  * copy代入演算子
    //  * moveコンストラクタ
    //  * move代入演算子
    // をCopy-And-Swapイデオムを使用して実装し、単体テストを行え。

    class CopyAndSwap final {
    public:
        explicit CopyAndSwap(char const* name0, char const* name1)
            : name0_{name0 == nullptr ? "" : name0}, name1_{name1 == nullptr ? "" : name1}
        {
        }

        CopyAndSwap(CopyAndSwap const& rhs)
        {
            // この関数の実装
        }

        CopyAndSwap(CopyAndSwap&& rhs) noexcept
        {
            // この関数の実装
        }

        CopyAndSwap& operator=(CopyAndSwap const& rhs)
        {
            // この関数の実装
            return *this;
        }

        CopyAndSwap& operator=(CopyAndSwap&& rhs) noexcept
        {
            // この関数の実装
            return *this;
        }

        void Swap(CopyAndSwap& rhs) noexcept
        {
            // この関数の実装
        }

        char const* GetName0() const noexcept { return name0_; }

        std::string const& GetName1() const noexcept { return name1_; }

        ~CopyAndSwap() = default;

    private:
        char const* name0_;
        std::string name1_;
    };

    TEST(DesignPatternQ, CopyAndSwap)
    {
        // test for explicit CopyAndSwap(char const* name0, char const* name1)
        auto n = CopyAndSwap{nullptr, nullptr};
        ASSERT_STREQ("", n.GetName0());
        ASSERT_EQ("", n.GetName1());

        auto a = CopyAndSwap{"a0", "a1"};
        ASSERT_STREQ("a0", a.GetName0());
        ASSERT_EQ("a1", a.GetName1());
    }
```

* 参照 [Copy-And-Swap](cpp_idioms.md#SS_21_1_3)
* [解答例-Copy-And-Swap](exercise_a.md#SS_23_9_6)


### 演習-Immutable <a id="SS_22_9_7"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/immutable.cpp 5
    // [Q]
    // 下記クラスPrimeNumbersはSetMaxNumberにより状態が変わってしまうことがある。
    // 状態変更が必要ない場合、こういった仕様はない方が良い。
    // PrimeNumbersからSetMaxNumberを削除し、このクラスをimmutableにせよ。

    class PrimeNumbers {
    public:
        PrimeNumbers() = default;

        PrimeNumbers(PrimeNumbers const&)            = default;
        PrimeNumbers& operator=(PrimeNumbers const&) = default;

        uint32_t GetMaxNumber() const noexcept { return max_number_; }
        void     SetMaxNumber(uint32_t max_number) noexcept
        {
            if (max_number != max_number_) {
                cached_     = false;
                max_number_ = max_number;
            }
        }

        std::vector<uint32_t> const& GeneratePrimeNumbers();

    private:
        uint32_t              max_number_{0};
        bool                  cached_{false};
        std::vector<uint32_t> prime_numbers_{};

        static uint32_t              next_prime_num(uint32_t curr_prime_num, std::vector<bool>& is_num_prime) noexcept;
        static std::vector<uint32_t> get_prime_numbers(uint32_t max_number);
    };

    uint32_t PrimeNumbers::next_prime_num(uint32_t curr_prime_num, std::vector<bool>& is_num_prime) noexcept
    {
        for (auto i = 2 * curr_prime_num; i < is_num_prime.size(); i += curr_prime_num) {
            is_num_prime[i] = false;  // 次の倍数は素数ではない
        }

        auto prime_num = curr_prime_num;

        do {  // 次の素数の探索
            ++prime_num;
        } while (!is_num_prime[prime_num] && (prime_num < is_num_prime.size()));

        return prime_num;
    }

    std::vector<uint32_t> PrimeNumbers::get_prime_numbers(uint32_t max_number)
    {
        auto result       = std::vector<uint32_t>{};
        auto prime_num    = 2U;                                       // 最初の素数
        auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない。
        is_num_prime[0] = is_num_prime[1] = false;

        do {
            result.emplace_back(prime_num);
            prime_num = next_prime_num(prime_num, is_num_prime);
        } while (prime_num < is_num_prime.size());

        return result;
    }

    std::vector<uint32_t> const& PrimeNumbers::GeneratePrimeNumbers()
    {
        if (cached_) {
            return prime_numbers_;
        }

        if (max_number_ < 2) {  // ガード節。2未満の素数はない。
            prime_numbers_.clear();
        }
        else {
            prime_numbers_ = get_prime_numbers(max_number_);
        }

        cached_ = true;
        return prime_numbers_;
    }

    TEST(DesignPatternQ, Immutable)
    {
        auto pm = PrimeNumbers{};

        pm.SetMaxNumber(1);
        ASSERT_EQ((std::vector<uint32_t>{}), pm.GeneratePrimeNumbers());

        pm.SetMaxNumber(3);
        ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm.GeneratePrimeNumbers());

        pm.SetMaxNumber(30);
        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm.GeneratePrimeNumbers());

        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm.GeneratePrimeNumbers());

        pm.SetMaxNumber(3);
        ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm.GeneratePrimeNumbers());

        auto pm3_copy = PrimeNumbers{pm};
        ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm3_copy.GeneratePrimeNumbers());

        auto pm5 = PrimeNumbers{};
        pm5.SetMaxNumber(5);
        pm = pm5;
        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5}), pm.GeneratePrimeNumbers());
    }
```

* 参照 [Immutable](cpp_idioms.md#SS_21_1_6)
* [解答例-Immutable](exercise_a.md#SS_23_9_7)


### 演習-Clone <a id="SS_22_9_8"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/clone.cpp 5
    // [Q]
    // TEST(DesignPatternQ, Clone)に記述したように、オブジェクトのスライシングによる影響で、
    // Base型ポインタに代入されたDerivedインスタンスへのコピーは部分的にしか行われない。
    // Cloneパターンを使用してこの問題を修正せよ。
    // また、その他の問題があれば合わせて修正せよ。

    class Base {
    public:
        explicit Base(std::string name) : name1_{name} {}
        virtual ~Base() = default;
        virtual std::string const& GetName() { return name1_; }

    private:
        std::string name1_;
    };

    class Derived final : public Base {
    public:
        explicit Derived(std::string name1 = "", std::string name2 = "") : Base{name1}, name2_{name2} {}
        virtual ~Derived() = default;
        virtual std::string const& GetName() { return name2_; }

    private:
        std::string name2_;
    };

    TEST(DesignPatternQ, Clone)
    {
        Derived d1{"name1", "name2"};

        ASSERT_EQ("name1", d1.Base::GetName());
        ASSERT_EQ("name2", d1.GetName());

        Derived d2{d1};
        ASSERT_EQ("name1", d2.Base::GetName());
        ASSERT_EQ("name2", d2.GetName());

        Derived d3;
        Base*   b3 = &d3;

        *b3 = d1;  // d1からd3へコピーしたつもりだが、スライスによりうまく行かない。

        ASSERT_EQ("name1", b3->Base::GetName());
    #if 0
        ASSERT_EQ("name2", b3->GetName());   // スライスの影響でname2_がコピーされていない。
    #else
        ASSERT_EQ("", d3.GetName());
    #endif
    }
```

* 参照 [Clone(仮想コンストラクタ)](design_pattern.md#SS_9_1_3)
* [解答例-Clone](exercise_a.md#SS_23_9_8)


### 演習-NVI <a id="SS_22_9_9"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/nvi.cpp 7
    // [Q]
    // 下記クラスBase、Derived、DerivedDerivedの前処理はクローンコードになっている。
    // NVIを用いて、この問題に対処せよ。

    class Base {
    public:
        explicit Base(std::string name) : name1_{name} {}
        virtual ~Base() = default;
        std::string const& GetName1() const noexcept { return name1_; }

        virtual bool IsEqual(Base const& rhs) const noexcept
        {
            if (this == &rhs) {
                return true;
            }

            if (typeid(*this) != typeid(rhs)) {
                return false;
            }

            return name1_ == rhs.name1_;
        }

    private:
        std::string name1_;
    };

    class Derived : public Base {
    public:
        explicit Derived(std::string name1 = "", std::string name2 = "") : Base{name1}, name2_{name2} {}
        virtual ~Derived() override = default;
        std::string const& GetName2() const noexcept { return name2_; }

        virtual bool IsEqual(Base const& rhs) const noexcept override
        {
            if (this == &rhs) {
                return true;
            }

            if (!Base::IsEqual(rhs)) {
                return false;
            }

            auto rhs_d = dynamic_cast<Derived const*>(&rhs);

            return (rhs_d != nullptr) && (name2_ == rhs_d->name2_);
        }

    private:
        std::string name2_;
    };

    class DerivedDerived : public Derived {
    public:
        explicit DerivedDerived(std::string name1 = "", std::string name2 = "", std::string name3 = "")
            : Derived{name1, name2}, name3_{name3}
        {
        }
        virtual ~DerivedDerived() override = default;
        std::string const& GetName3() const noexcept { return name3_; }

        virtual bool IsEqual(Base const& rhs) const noexcept override
        {
            if (this == &rhs) {
                return true;
            }

            if (!Derived::IsEqual(rhs)) {
                return false;
            }

            auto rhs_d = dynamic_cast<DerivedDerived const*>(&rhs);

            return (rhs_d != nullptr) && (name3_ == rhs_d->name3_);
        }

    private:
        std::string name3_;
    };

    TEST(DesignPatternQ, NVI)
    {
        auto b1 = Base{"b1"};

        ASSERT_TRUE(b1.IsEqual(Base{b1}));
        ASSERT_TRUE(b1.IsEqual(Base{"b1"}));
        ASSERT_FALSE(b1.IsEqual(Base{"b2"}));
        ASSERT_FALSE(b1.IsEqual(Derived{"b1", "d1"}));

        auto d1 = Derived{"b1", "d1"};

        ASSERT_FALSE(d1.IsEqual(Base{"b1"}));
        ASSERT_TRUE(d1.IsEqual(d1));
        ASSERT_TRUE(d1.IsEqual(Derived{"b1", "d1"}));
        ASSERT_FALSE(d1.IsEqual(Derived{"b1", "d2"}));
        ASSERT_FALSE(d1.IsEqual(DerivedDerived{"b1", "d1", "dd2"}));

        auto dd1 = DerivedDerived{"b1", "d1", "dd1"};

        ASSERT_FALSE(dd1.IsEqual(Base{"b1"}));
        ASSERT_FALSE(dd1.IsEqual(Derived{"b1", "d1"}));
        ASSERT_TRUE(dd1.IsEqual(dd1));
        ASSERT_TRUE(dd1.IsEqual(DerivedDerived{"b1", "d1", "dd1"}));
        ASSERT_FALSE(dd1.IsEqual(DerivedDerived{"b1", "d1", "dd2"}));
    }
```

* 参照 [NVI(non virtual interface)](cpp_idioms.md#SS_21_1_7)
* [解答例-NVI](exercise_a.md#SS_23_9_9)


### 演習-RAIIの効果 <a id="SS_22_9_10"></a>
* 問題  
  RAIIにはどのような効果があるか？　下記より相応しいものを選択せよ。

* 選択肢  
    1. リソースリークの防止
    2. 使用リソースの削減
    3. クラスの実装を隠ぺい
    4. LIPの順守

* [解答-RAIIの効果](exercise_a.md#SS_23_9_10)


### 演習-RAII <a id="SS_22_9_11"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/raii.cpp 5
    // [Q]
    // 下記クラスBase、Derivedはクローンパターンをしているが、Clone関数はnewしたオブジェクトであるため、
    // メモリーリークを起こしやすい。std::unique_ptrを使用してこの問題に対処せよ。

    class Base {
    public:
        explicit Base(std::string name) : name1_{std::move(name)} {}
        virtual ~Base() = default;
        virtual std::string const& GetName() const noexcept { return name1_; }

        virtual Base* Clone() const { return new Base(name1_); }

        Base(Base const&)            = delete;
        Base& operator=(Base const&) = delete;

    private:
        std::string name1_;
    };

    class Derived final : public Base {
    public:
        explicit Derived(std::string name1 = "", std::string name2 = "") : Base{std::move(name1)}, name2_{std::move(name2)}
        {
        }
        virtual ~Derived() override = default;
        virtual std::string const& GetName() const noexcept override { return name2_; }

        virtual Derived* Clone() const override { return new Derived{Base::GetName(), name2_}; }

    private:
        std::string name2_;
    };

    TEST(DesignPatternQ, RAII)
    {
        Derived  d1{"name1", "name2"};
        Derived* d2{d1.Clone()};

        ASSERT_EQ("name1", d2->Base::GetName());
        ASSERT_EQ("name2", d2->GetName());

        delete d2;

        Base* b3 = d1.Clone();

        ASSERT_EQ("name1", b3->Base::GetName());
        ASSERT_EQ("name2", b3->GetName());

        delete b3;
    }
```

* 参照 [RAII(scoped guard)](cpp_idioms.md#SS_21_1_2)
* [解答例-RAII](exercise_a.md#SS_23_9_11)


### 演習-Future <a id="SS_22_9_12"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/future.cpp 23
    // [Q]
    // 下記のfind_files_concurrentlyはスレッドの出力の結果をキャプチャリファレンスで受け取るため、
    // 入出力の関係が明確でない。Futureパターンを使用しそれを明確にするリファクタリングを行え。

    std::vector<std::string> find_files_concurrently()
    {
        auto pca = std::vector<std::string>{};
        auto pcq = std::vector<std::string>{};

        auto th0 = std::thread{[&pca] { pca = find_files("../programming_convention_a/"); }};
        auto th1 = std::thread{[&pcq] { pcq = find_files("../programming_convention_q/"); }};

        th0.join();
        th1.join();

        pca.insert(pca.end(), pcq.begin(), pcq.end());

        return pca;
    }

    TEST(DesignPatternQ, Future)
    {
        auto files = find_files_concurrently();

        ASSERT_GT(files.size(), 10);
    }
```

* 参照 [Future](cpp_idioms.md#SS_21_2_4)
* [解答例-Future](exercise_a.md#SS_23_9_12)


### 演習-DI <a id="SS_22_9_13"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/di.cpp 10
    // [Q]
    // CppFilesはLsCppを直に生成するため、LsCpp::FileList()がエラーした場合の単体テスト実施が
    // 困難である。CppFilesにDIパターンを適用するとともに、LsCppを適切に変更することによって、
    // LsCpp::FileList()がエラーした場合のCppFilesの単体テストを行え。

    class LsCpp {
    public:
        std::string const& FileList()
        {
            if (files_.size() != 0) {  // キャッシュを使う
                return files_;
            }

            auto stream = std::unique_ptr<FILE, decltype(&fclose)>{popen("ls ../ut_data/*.cpp", "r"), fclose};

            if (stream.get() == NULL) {
                throw std::exception{};
            }

            char buff[256];
            while (fgets(buff, sizeof(buff) - 1, stream.get()) != NULL) {
                files_ += buff;
            }

            return files_;
        }

    private:
        std::string files_{};
    };

    class CppFiles {
    public:
        std::vector<std::string> FileList() const
        {
            auto files  = std::string{};
            auto ls_cpp = LsCpp{};

            try {
                files = ls_cpp.FileList();
            }
            catch (...) {
                ;  // 例外発生時には空のベクタを返すので何もしない。
            }

            return split_cr(files);
        }

    private:
        static std::vector<std::string> split_cr(std::string const& str)
        {
            auto ss  = std::stringstream{str};
            auto ret = std::vector<std::string>{};

            for (std::string line; std::getline(ss, line);) {
                ret.emplace_back(line);
            }

            return ret;
        }
    };

    TEST(DesignPatternQ, DI)
    {
        auto        files = CppFiles{};
        auto const& act   = files.FileList();
        auto        exp   = std::vector<std::string>{"../ut_data/a.cpp", "../ut_data/abc.cpp", "../ut_data/efghij.cpp"};

        ASSERT_EQ(exp, act);
    }
```

* 参照 [DI(dependency injection)](design_pattern.md#SS_9_3_1)
* [解答例-DI](exercise_a.md#SS_23_9_13)


### 演習-Singleton <a id="SS_22_9_14"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/singleton.cpp 5
    // [Q]
    // 下記AppConfigはアプリケーション全体の設定を管理するためのクラスである。
    // 目的上、そのインスタンスAppConfigは広域のアクセスが必要であり、
    // グローバルインスタンスとして実装している。
    // グローバルインスタンスは、初期化の順番が標準化されておらず、
    // 多くの処理系ではリンクの順番に依存しているため、
    // アプリケーション立ち上げ時に様々な問題を起こすことがある。
    // こういった問題を回避するため、AppConfigをSingleton化せよ。
    // また他の問題があれば合わせて修正せよ。

    class AppConfig {
    public:
        enum BaseColor { Red, Green, Black };

        void      SetBaseColor(BaseColor color) noexcept { color_ = color; }
        BaseColor GetBaseColor() { return color_; }

        void         SetUserName(std::string_view username) { username_ = username; }
        std::string& GetUserName() { return username_; }

        void Logging(bool is_logging) { is_logging_ = is_logging; }
        bool IsLoggin() { return is_logging_; }

        // 他の設定値は省略

        void SetDefault()
        {
            SetBaseColor(Red);
            SetUserName("No Name");
            Logging(false);
        }

    private:
        BaseColor   color_{Red};
        std::string username_{"No Name"};
        bool        is_logging_{false};
    };

    AppConfig AppConfig;

    class DesignPatternQ_F : public ::testing::Test {
    protected:
        virtual void SetUp() override { AppConfig.SetDefault(); }

        virtual void TearDown() override { AppConfig.SetDefault(); }
    };

    TEST_F(DesignPatternQ_F, Singleton)
    {
        ASSERT_EQ(AppConfig::Red, AppConfig.GetBaseColor());
        ASSERT_EQ("No Name", AppConfig.GetUserName());
        ASSERT_FALSE(AppConfig.IsLoggin());

        AppConfig.SetBaseColor(AppConfig::Green);
        ASSERT_EQ(AppConfig::Green, AppConfig.GetBaseColor());

        AppConfig.SetUserName("Stroustrup");
        ASSERT_EQ("Stroustrup", AppConfig.GetUserName());

        AppConfig.Logging(true);
        ASSERT_TRUE(AppConfig.IsLoggin());

        AppConfig.SetDefault();
        ASSERT_EQ(AppConfig::Red, AppConfig.GetBaseColor());
        ASSERT_EQ("No Name", AppConfig.GetUserName());
        ASSERT_FALSE(AppConfig.IsLoggin());
    }
```

* 参照 [Singleton](design_pattern.md#SS_9_1_1)
* [解答例-Singleton](exercise_a.md#SS_23_9_14)


### 演習-State <a id="SS_22_9_15"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/state.cpp 5
    // [Q]
    // 下記クラスGreetingにはlang_に対する同型のswitch文が3個ある。
    // これは機能追加時にバグが混入しやすいアンチパターンであるため、
    // Stateパターンを用いリファクタリングせよ。
    // また、他の問題があれば合わせて修正せよ。

    enum class Language { English, Japanese, French };

    class Greeting {
    public:
        explicit Greeting(Language lang = Language::English) noexcept : lang_{lang} {}
        void SetLanguage(Language lang) noexcept { lang_ = lang; }

        std::string GoodMorning()
        {
            switch (lang_) {
            case Language::Japanese:
                return "おはよう";
            case Language::French:
                return "Bonjour";
            case Language::English:
            default:
                return "good morning";
            }
        }

        std::string Hello()
        {
            switch (lang_) {
            case Language::Japanese:
                return "こんにちは";
            case Language::French:
                return "Bonjour";
            case Language::English:
            default:
                return "hello";
            }
        }

        std::string GoodEvening()
        {
            switch (lang_) {
            case Language::Japanese:
                return "こんばんは";
            case Language::French:
                return "bonne soirée";
            case Language::English:
            default:
                return "good evening";
            }
        }

    private:
        Language lang_;
    };

    TEST(DesignPatternQ, State)
    {
        auto greeting = Greeting{};

        ASSERT_EQ("good morning", greeting.GoodMorning());
        ASSERT_EQ("hello", greeting.Hello());
        ASSERT_EQ("good evening", greeting.GoodEvening());

        greeting.SetLanguage(Language::Japanese);
        ASSERT_EQ("おはよう", greeting.GoodMorning());
        ASSERT_EQ("こんにちは", greeting.Hello());
        ASSERT_EQ("こんばんは", greeting.GoodEvening());

        greeting.SetLanguage(Language::French);
        ASSERT_EQ("Bonjour", greeting.GoodMorning());
        ASSERT_EQ("Bonjour", greeting.Hello());
        ASSERT_EQ("bonne soirée", greeting.GoodEvening());

        greeting.SetLanguage(Language::English);
        ASSERT_EQ("good morning", greeting.GoodMorning());
        ASSERT_EQ("hello", greeting.Hello());
        ASSERT_EQ("good evening", greeting.GoodEvening());
    }
```

* 参照 [State](design_pattern.md#SS_9_2_3)
* [解答例-State](exercise_a.md#SS_23_9_15)


### 演習-Null Object <a id="SS_22_9_16"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/null_object.cpp 38
    // [Q]
    // 下記クラスPersonにはgreeting_のヌルチェックを行う三項演算子が3つある。
    // これはヌルポインタアクセスを起こしやすいアンチパターンであるため、
    // Null Objectパターンを用いリファクタリングせよ。
    // また、他の問題があれば合わせて修正せよ。

    class Greeting {
    public:
        explicit Greeting(Language lang = Language::English) : state_{new_state(lang)} {}
        void SetLanguage(Language lang) { state_ = new_state(lang); }

        std::string GoodMorning() const { return state_->GoodMorning(); }
        std::string Hello() const { return state_->Hello(); }
        std::string GoodEvening() const { return state_->GoodEvening(); }

    private:
        std::unique_ptr<GreetingState> state_;

        static std::unique_ptr<GreetingState> new_state(Language lang)
        {
            switch (lang) {
            case Language::Japanese:
                return std::make_unique<GreetingState_Japanese>();
            case Language::French:
                return std::make_unique<GreetingState_French>();
            case Language::English:
            default:
                return std::make_unique<GreetingState_English>();
            }
        }
    };

    class Person {
    public:
        explicit Person(Language lang, bool silent = false)
            : greeting_{silent ? std::unique_ptr<Greeting>{} : std::make_unique<Greeting>(lang)}
        {
        }

        std::string GoodMorning() { return greeting_ ? greeting_->GoodMorning() : ""; }
        std::string Hello() { return greeting_ ? greeting_->Hello() : ""; }
        std::string GoodEvening() { return greeting_ ? greeting_->GoodEvening() : ""; }

    private:
        std::unique_ptr<Greeting> greeting_;
    };

    TEST(DesignPatternQ, NullObject)
    {
        auto e = Person{Language::English};

        ASSERT_EQ("good morning", e.GoodMorning());
        ASSERT_EQ("hello", e.Hello());
        ASSERT_EQ("good evening", e.GoodEvening());

        auto j = Person{Language::Japanese};
        ASSERT_EQ("おはよう", j.GoodMorning());
        ASSERT_EQ("こんにちは", j.Hello());
        ASSERT_EQ("こんばんは", j.GoodEvening());

        auto f = Person{Language::French};
        ASSERT_EQ("Bonjour", f.GoodMorning());
        ASSERT_EQ("Bonjour", f.Hello());
        ASSERT_EQ("bonne soirée", f.GoodEvening());

        auto e_s = Person{Language::English, true};

        ASSERT_EQ("", e_s.GoodMorning());
        ASSERT_EQ("", e_s.Hello());
        ASSERT_EQ("", e_s.GoodEvening());
    }
```

* 参照 [Null Object](cpp_idioms.md#SS_21_2_5)
* [解答例-Null Object](exercise_a.md#SS_23_9_16)


### 演習-Templateメソッド <a id="SS_22_9_17"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/template_method.cpp 5
    // [Q]
    // 下記クラスXxxDataFormatterXml、XxxDataFormatterCsvは同様の処理を行い、
    // それぞれのフォーマットで文字列を出力する。このような処理のクローンはTemplate Method
    // パターンにより排除できる。
    // このパターンを用い、下記2クラスをリファクタリングせよ。
    // また、他の問題があれば合わせて修正せよ。

    struct XxxData {
        int a;
        int b;
        int c;
    };

    class XxxDataFormatterXml {
    public:
        XxxDataFormatterXml() = default;

        std::string ToString(XxxData const& xxx_data) const
        {
            auto body = std::string{"<Item>\n"};

            body += "    <XxxData a=\"" + std::to_string(xxx_data.a) + "\">\n";
            body += "    <XxxData b=\"" + std::to_string(xxx_data.b) + "\">\n";
            body += "    <XxxData c=\"" + std::to_string(xxx_data.c) + "\">\n";
            body += "</Itemp>\n";

            return header_ + body + footer_;
        }

        std::string ToString(std::vector<XxxData> const& xxx_datas) const
        {
            auto ret = std::string{header_};

            for (auto const& xxx_data : xxx_datas) {
                ret += "<Item>\n";
                ret += "    <XxxData a=\"" + std::to_string(xxx_data.a) + "\">\n";
                ret += "    <XxxData b=\"" + std::to_string(xxx_data.b) + "\">\n";
                ret += "    <XxxData c=\"" + std::to_string(xxx_data.c) + "\">\n";
                ret += "</Itemp>\n";
            }

            return ret + footer_;
        }

    private:
        std::string header_ = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<XxxDataFormatterXml>\n";
        std::string footer_ = "</XxxDataFormatterXml>\n";
    };

    class XxxDataFormatterCsv {
    public:
        XxxDataFormatterCsv() = default;

        std::string ToString(XxxData const& xxx_data) const
        {
            auto body = std::string{std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
                                    + std::to_string(xxx_data.b) + "\n"};

            return header_ + body;
        }

        std::string ToString(std::vector<XxxData> const& xxx_datas) const
        {
            auto ret = std::string{header_};

            for (auto const& xxx_data : xxx_datas) {
                ret += std::string{std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
                                   + std::to_string(xxx_data.b) + "\n"};
            }

            return ret;
        }

    private:
        std::string const header_ = "a, b, c\n";
    };

    TEST(DesignPatternQ, TemplateMethod)
    {
        auto xml = XxxDataFormatterXml{};
        {
            auto const expect_scalar = std::string{
                "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
                "<XxxDataFormatterXml>\n"
                "<Item>\n"
                "    <XxxData a=\"1\">\n"
                "    <XxxData b=\"100\">\n"
                "    <XxxData c=\"10\">\n"
                "</Itemp>\n"
                "</XxxDataFormatterXml>\n"};
            auto const actual_scalar = xml.ToString({1, 100, 10});
            ASSERT_EQ(expect_scalar, actual_scalar);

            auto const expect_array = std::string{
                "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
                "<XxxDataFormatterXml>\n"
                "<Item>\n"
                "    <XxxData a=\"1\">\n"
                "    <XxxData b=\"100\">\n"
                "    <XxxData c=\"10\">\n"
                "</Itemp>\n"
                "<Item>\n"
                "    <XxxData a=\"2\">\n"
                "    <XxxData b=\"200\">\n"
                "    <XxxData c=\"20\">\n"
                "</Itemp>\n"
                "</XxxDataFormatterXml>\n"};
            auto const actual_array = xml.ToString({{1, 100, 10}, {2, 200, 20}});
            ASSERT_EQ(expect_array, actual_array);
        }

        auto csv = XxxDataFormatterCsv{};
        {
            auto expect_scalar = std::string{
                "a, b, c\n"
                "1, 100, 100\n"};
            auto const actual_scalar = csv.ToString({1, 100, 10});
            ASSERT_EQ(expect_scalar, actual_scalar);

            auto const expect_array = std::string{
                "a, b, c\n"
                "1, 100, 100\n"
                "2, 200, 200\n"};
            auto const actual_array = csv.ToString({{1, 100, 10}, {2, 200, 20}});
            ASSERT_EQ(expect_array, actual_array);
        }
    }
```

* 参照 [Templateメソッド](design_pattern.md#SS_9_2_1)
* [解答例-Templateメソッド](exercise_a.md#SS_23_9_17)


### 演習-Factory <a id="SS_22_9_18"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/factory_lib.h 6
    // [Q]
    // 下記クラスXxxDataFormatterXml、XxxDataFormatterCsvはヘッダファイルで宣言・定義を行ったために
    // 他の.cppファイルから直接アクセスできてしまう。
    // Factoryパターンを用いて、XxxDataFormatterXml、XxxDataFormatterCsvを他の.cppファイルから
    // 直接アクセスできないようにせよ。

    struct XxxData {
        int a;
        int b;
        int c;
    };

    class XxxDataFormatterIF {
    public:
        XxxDataFormatterIF() noexcept                            = default;
        virtual ~XxxDataFormatterIF()                            = default;
        XxxDataFormatterIF(XxxDataFormatterIF const&)            = delete;
        XxxDataFormatterIF& operator=(XxxDataFormatterIF const&) = delete;

        std::string ToString(XxxData const& xxx_data) const { return header() + body(xxx_data) + footer(); }

        std::string ToString(std::vector<XxxData> const& xxx_datas) const
        {
            auto ret = header();

            for (auto const& xxx_data : xxx_datas) {
                ret += body(xxx_data);
            }

            return ret + footer();
        }

    private:
        virtual std::string const& header() const                      = 0;
        virtual std::string const& footer() const                      = 0;
        virtual std::string        body(XxxData const& xxx_data) const = 0;
    };

    class XxxDataFormatterXml final : public XxxDataFormatterIF {
    public:
        XxxDataFormatterXml()                   = default;
        virtual ~XxxDataFormatterXml() override = default;

    private:
        virtual std::string const& header() const override;
        virtual std::string const& footer() const override;
        virtual std::string        body(XxxData const& xxx_data) const override;
    };

    class XxxDataFormatterCsv final : public XxxDataFormatterIF {
    public:
        XxxDataFormatterCsv()                   = default;
        virtual ~XxxDataFormatterCsv() override = default;

    private:
        virtual std::string const& header() const override;
        virtual std::string const& footer() const override;
        virtual std::string        body(XxxData const& xxx_data) const override;
    };
```
```cpp
    //  exercise/design_pattern_q/factory_lib.cpp 5

    std::string const& XxxDataFormatterXml::header() const
    {
        static auto const header = std::string{"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<XxxDataFormatterXml>\n"};

        return header;
    }

    std::string const& XxxDataFormatterXml::footer() const
    {
        static auto const footer = std::string{"</XxxDataFormatterXml>\n"};

        return footer;
    }

    std::string XxxDataFormatterXml::body(XxxData const& xxx_data) const
    {
        auto content = std::string{"<Item>\n"};

        content += "    <XxxData a=\"" + std::to_string(xxx_data.a) + "\">\n";
        content += "    <XxxData b=\"" + std::to_string(xxx_data.b) + "\">\n";
        content += "    <XxxData c=\"" + std::to_string(xxx_data.c) + "\">\n";

        return content + "</Itemp>\n";
    }

    std::string const& XxxDataFormatterCsv::header() const
    {
        static auto const header = std::string{"a, b, c\n"};

        return header;
    }

    std::string const& XxxDataFormatterCsv::footer() const
    {
        static auto const footer = std::string{};

        return footer;
    }

    std::string XxxDataFormatterCsv::body(XxxData const& xxx_data) const
    {
        return std::string{std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
                           + std::to_string(xxx_data.b) + "\n"};
    }
```
```cpp
    //  exercise/design_pattern_q/factory.cpp 9

    TEST(DesignPatternQ, Factory)
    {
        auto xml = XxxDataFormatterXml{};
        {
            auto const expect_scalar = std::string{
                "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
                "<XxxDataFormatterXml>\n"
                "<Item>\n"
                "    <XxxData a=\"1\">\n"
                "    <XxxData b=\"100\">\n"
                "    <XxxData c=\"10\">\n"
                "</Itemp>\n"
                "</XxxDataFormatterXml>\n"};
            auto const actual_scalar = xml.ToString({1, 100, 10});
            ASSERT_EQ(expect_scalar, actual_scalar);
        }

        auto csv = XxxDataFormatterCsv{};
        {
            auto const expect_array = std::string{
                "a, b, c\n"
                "1, 100, 100\n"
                "2, 200, 200\n"};
            auto const actual_array = csv.ToString({{1, 100, 10}, {2, 200, 20}});
            ASSERT_EQ(expect_array, actual_array);
        }
    }
```

* 参照 [Factory](design_pattern.md#SS_9_1_4)
* [解答例-Factory](exercise_a.md#SS_23_9_18)


### 演習-Named Constructor <a id="SS_22_9_19"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/named_constructor_lib.h 14
    // [Q]
    // 下記関数XxxDataFormatterFactoryはインターフェースクラスXxxDataFormatterIFのファクトリ関数
    // である。これをnamed constructorパターンで実装しなおせ。

    class XxxDataFormatterIF {
    public:
        XxxDataFormatterIF() noexcept                            = default;
        virtual ~XxxDataFormatterIF()                            = default;
        XxxDataFormatterIF(XxxDataFormatterIF const&)            = delete;
        XxxDataFormatterIF& operator=(XxxDataFormatterIF const&) = delete;

        std::string ToString(XxxData const& xxx_data) const { return header() + body(xxx_data) + footer(); }

        std::string ToString(std::vector<XxxData> const& xxx_datas) const
        {
            auto ret = header();

            for (auto const& xxx_data : xxx_datas) {
                ret += body(xxx_data);
            }

            return ret + footer();
        }

    private:
        virtual std::string const& header() const                      = 0;
        virtual std::string const& footer() const                      = 0;
        virtual std::string        body(XxxData const& xxx_data) const = 0;
    };

    enum class XxxDataFormatterType { Xml, Csv, Table };

    XxxDataFormatterIF const& XxxDataFormatterFactory(XxxDataFormatterType type) noexcept;
```
```cpp
    //  exercise/design_pattern_q/named_constructor_lib.cpp 112

    XxxDataFormatterIF const& XxxDataFormatterFactory(XxxDataFormatterType type) noexcept
    {
        static auto const xml   = XxxDataFormatterXml{};
        static auto const csv   = XxxDataFormatterCsv{};
        static auto const table = XxxDataFormatterTable{};

        switch (type) {
        case XxxDataFormatterType::Xml:
            return xml;
        case XxxDataFormatterType::Csv:
            return csv;
        case XxxDataFormatterType::Table:
            return table;
        default:
            assert("unknown type");
            return csv;
        }
    }
```
```cpp
    //  exercise/design_pattern_q/named_constructor.cpp 9

    TEST(DesignPatternQ, NamedConstructor)
    {
        auto const& xml = XxxDataFormatterFactory(XxxDataFormatterType::Xml);
        {
            auto const expect_scalar = std::string{
                "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
                "<XxxDataFormatterXml>\n"
                "<Item>\n"
                "    <XxxData a=\"1\">\n"
                "    <XxxData b=\"100\">\n"
                "    <XxxData c=\"10\">\n"
                "</Itemp>\n"
                "</XxxDataFormatterXml>\n"};
            auto const actual_scalar = xml.ToString({1, 100, 10});

            ASSERT_EQ(expect_scalar, actual_scalar);
        }

        auto const& csv = XxxDataFormatterFactory(XxxDataFormatterType::Csv);
        {
            auto const expect_array = std::string{
                "a, b, c\n"
                "1, 100, 100\n"
                "2, 200, 200\n"};
            auto const actual_array = csv.ToString({{1, 100, 10}, {2, 200, 20}});

            ASSERT_EQ(expect_array, actual_array);
        }

        auto const& table = XxxDataFormatterFactory(XxxDataFormatterType::Table);
        {
            auto const expect_array = std::string{
                "+--------|--------|--------+\n"
                "| a      | b      | c      |\n"
                "+--------|--------|--------+\n"
                "| 3      | 300    | 30     |\n"
                "+--------|--------|--------+\n"
                "| 4      | 400    | 40     |\n"
                "+--------|--------|--------+\n"};
            auto const actual_array = table.ToString({{3, 300, 30}, {4, 400, 40}});

            ASSERT_EQ(expect_array, actual_array);
        }
    }
```

* 参照 [Named Constructor](design_pattern.md#SS_9_1_2)
* [解答例-Named Constructor](exercise_a.md#SS_23_9_19)


### 演習-Proxy <a id="SS_22_9_20"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/proxy.cpp 7
    // [Q]
    // 下記クラスLsDirのFileListはlsコマンドをpopenにより実行し、その戻り値をstd::stringで返す。
    // popenはコストの高いコールなので、パフォーマンスを上げるためにlsの戻り値をキャッシュしたいが、
    // 現行のLsDirも必要である。
    // Proxyパターンを使い、この問題に対処するためのLsDirCachedを作れ。

    class LsDir {
    public:
        LsDir()  = default;
        ~LsDir() = default;

        void               SetArgs(std::string_view args) { args_ = args; }
        std::string const& GetArgs() const noexcept { return args_; }

        std::string FileList() const
        {
            auto cmd      = std::string{"ls "} + GetArgs();
            auto to_close = [](FILE* f) { fclose(f); };
            auto stream   = std::unique_ptr<FILE, decltype(to_close)>{popen(cmd.c_str(), "r"), to_close};

            auto files = std::string{};
            char buff[256];

            while (fgets(buff, sizeof(buff) - 1, stream.get()) != NULL) {
                files += buff;
            }

            return files;
        }

    private:
        std::string args_{};
    };

    TEST(DesignPatternQ, Proxy)
    {
        auto ld = LsDir{};

        {
            ld.SetArgs("../ut_data/");

            auto exp = std::string{"a.cpp\na.h\nabc.cpp\nabc.h\nd\nefghij.cpp\nefghij.h\nlib\no\n"};
            auto act = ld.FileList();

            ASSERT_EQ(exp, act);
            ASSERT_EQ(act, ld.FileList());
        }
        {
            ld.SetArgs("../ut_data/lib/");

            auto exp = std::string{"lib.cpp\nlib.h\n"};
            auto act = ld.FileList();

            ASSERT_EQ(exp, act);
            ASSERT_EQ(act, ld.FileList());
        }
    }
```

* 参照 [Proxy](design_pattern.md#SS_9_2_6)
* [解答例-Proxy](exercise_a.md#SS_23_9_20)


### 演習-Strategy <a id="SS_22_9_21"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/strategy.cpp 11
    // [Q]
    // 下記find_filesは醜悪であるだけでなく、拡張性もない。
    // Strategyパターンを用い、この問題に対処せよ。

    enum class FindCondition {
        File,
        Dir,
        FileCpp,
    };

    std::vector<std::string> find_files(std::string const& path, FindCondition condition)
    {
        namespace fs = std::filesystem;

        auto files = std::vector<fs::path>{};

        // recursive_directory_iteratorはファイルシステム依存するため、その依存を排除する他の処理
        std::copy(fs::recursive_directory_iterator{path}, fs::recursive_directory_iterator{}, std::back_inserter(files));

        std::sort(files.begin(), files.end());

        auto ret = std::vector<std::string>{};

        for (fs::path const& p : files) {
            auto is_match = false;

            switch (condition) {
            case FindCondition::File:
                if (fs::is_regular_file(p)) {
                    is_match = true;
                }
                break;
            case FindCondition::Dir:
                if (fs::is_directory(p)) {
                    is_match = true;
                }
                break;
            case FindCondition::FileCpp: {
                auto const filename = p.filename().generic_string();
                auto const cpp_file = std::string{".cpp"};

                if (filename.length() > cpp_file.length()
                    && (filename.substr(filename.length() - cpp_file.length()) == cpp_file)) {
                    is_match = true;
                }
                break;
            }
            default:
                assert(false);
            }

            if (is_match) {
                ret.emplace_back(p.generic_string());
            }
        }

        return ret;
    }

    TEST(DesignPatternQ, Strategy)
    {
        auto sort = [](auto&& v) {
            std::sort(v.begin(), v.end());
            return v;
        };

        {
            auto exp = sort(std::vector<std::string>{"../ut_data/a.cpp", "../ut_data/a.h", "../ut_data/abc.cpp",
                                                     "../ut_data/abc.h", "../ut_data/d/a.d", "../ut_data/efghij.cpp",
                                                     "../ut_data/efghij.h", "../ut_data/lib/lib.cpp",
                                                     "../ut_data/lib/lib.h", "../ut_data/o/a.o"});
            auto act = find_files("../ut_data", FindCondition::File);

            ASSERT_EQ(exp, act);
        }
        {
            auto exp = sort(std::vector<std::string>{"../ut_data/d", "../ut_data/lib", "../ut_data/o"});
            auto act = find_files("../ut_data", FindCondition::Dir);

            ASSERT_EQ(exp, act);
        }
        {
            auto exp = sort(std::vector<std::string>{"../ut_data/a.cpp", "../ut_data/abc.cpp", "../ut_data/efghij.cpp",
                                                     "../ut_data/lib/lib.cpp"});
            auto act = find_files("../ut_data", FindCondition::FileCpp);

            ASSERT_EQ(exp, act);
        }
    }
```

* 参照 [Strategy](design_pattern.md#SS_9_2_2)
* [解答例-Strategy](exercise_a.md#SS_23_9_21)


### 演習-Visitor <a id="SS_22_9_22"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/visitor.cpp 9
    // [Q]
    // 下記クラスFile、Dir、OtherEntityはクラスFileEntityから派生し、
    // それぞれが自身をstd::stringに変換するアルゴリズム関数
    //      * to_string_normal()
    //      * to_string_with_char()
    //      * to_string_with_children()
    // をオーバーライドしている。これはポリモーフィズムの使用方法としては正しいが、
    // to_string_xxx系統のインターフェースがが大量に増えた場合に、
    // FileEntityのインターフェースがそれに比例して増えてしまう問題を持っている。
    // Visitorパターンを使用しこれに対処せよ。

    class FileEntity {
    public:
        explicit FileEntity(std::string const& pathname) : pathname_{strip(pathname)} {}
        virtual ~FileEntity() = default;
        std::string const& Pathname() const noexcept { return pathname_; }

        std::string ToStringNormal() const { return to_string_normal(); }
        std::string ToStringWithChar() const { return to_string_with_char(); }
        std::string ToStringWithChildren() const { return to_string_with_children(); }

    private:
        std::string const pathname_;

        virtual std::string to_string_normal() const        = 0;
        virtual std::string to_string_with_char() const     = 0;
        virtual std::string to_string_with_children() const = 0;

        static std::string strip(std::string const& pathname)
        {
            return std::regex_replace(pathname, std::regex{R"(/+$)"}, "");
        }
    };

    class File final : public FileEntity {
    public:
        explicit File(std::string const& pathname) : FileEntity{pathname} {}

    private:
        virtual std::string to_string_normal() const override { return Pathname(); }
        virtual std::string to_string_with_char() const override { return Pathname(); };
        virtual std::string to_string_with_children() const override { return Pathname(); };
    };

    class Dir final : public FileEntity {
    public:
        explicit Dir(std::string const& pathname) : FileEntity{pathname} {}

    private:
        virtual std::string to_string_normal() const override { return Pathname() + '/'; }
        virtual std::string to_string_with_char() const override { return to_string_normal(); };
        virtual std::string to_string_with_children() const override { return find_files(Pathname()); };

        static std::string find_files(std::string const& dir)
        {
            namespace fs = std::filesystem;

            auto files = std::vector<std::string>{};

            std::for_each(fs::recursive_directory_iterator{dir}, fs::recursive_directory_iterator{},
                          [&files](fs::path const& p) { files.emplace_back(p.generic_string()); });

            std::sort(files.begin(), files.end());

            auto ret = std::string{dir};

            for (auto f : files) {
                ret += ' ' + f;
            }

            return ret;
        }
    };

    class OtherEntity final : public FileEntity {
    public:
        explicit OtherEntity(std::string const& pathname) : FileEntity{pathname} {}

    private:
        virtual std::string to_string_normal() const override { return Pathname(); }
        virtual std::string to_string_with_char() const override { return Pathname() + '+'; };
        virtual std::string to_string_with_children() const override { return Pathname(); };
    };

    TEST(DesignPatternQ, Visitor)
    {
        auto const f0 = File{"../ut_data/a.cpp"};
        auto const f1 = File{"../ut_data/a.cpp///"};

        ASSERT_EQ("../ut_data/a.cpp", f0.Pathname());
        ASSERT_EQ("../ut_data/a.cpp", f0.Pathname());
        ASSERT_EQ("../ut_data/a.cpp", f0.ToStringNormal());
        ASSERT_EQ("../ut_data/a.cpp", f0.ToStringWithChar());
        ASSERT_EQ("../ut_data/a.cpp", f0.ToStringWithChildren());

        auto const dir = Dir{"../ut_data/lib/"};

        ASSERT_EQ("../ut_data/lib", dir.Pathname());
        ASSERT_EQ("../ut_data/lib/", dir.ToStringNormal());
        ASSERT_EQ("../ut_data/lib/", dir.ToStringWithChar());
        ASSERT_EQ("../ut_data/lib ../ut_data/lib/lib.cpp ../ut_data/lib/lib.h", dir.ToStringWithChildren());

        auto const other = OtherEntity{"symbolic_link"};

        ASSERT_EQ("symbolic_link", other.Pathname());
        ASSERT_EQ("symbolic_link", other.ToStringNormal());
        ASSERT_EQ("symbolic_link+", other.ToStringWithChar());
        ASSERT_EQ("symbolic_link", other.ToStringWithChildren());
    }
```

* 参照 [Visitor](design_pattern.md#SS_9_2_5)
* [解答例-Visitor](exercise_a.md#SS_23_9_22)


### 演習-CRTP <a id="SS_22_9_23"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/crtp.cpp 9
    // [Q]
    // 下記クラスFileEntityから派生しクラスFile、Dir、OtherEntityは、
    // Visitorパターンを利用しているため、そのすべてで下記のコードクローンを持つ。
    //
    //    virtual std::string to_string(Visitor const& to_s) const { return to_s.Visit(*this); }
    //
    // このコードクローンのthisの型は、それぞれFile、Dir、OtherEntityとなるため、
    // この関数をFileEntityで定義すると動作が変わってしまい、単純には統一できない。
    // CRTPを用い、このクローンを削除せよ。

    class Visitor;

    class FileEntity {
    public:
        explicit FileEntity(std::string const& pathname) : pathname_{strip(pathname)} {}
        virtual ~FileEntity() = default;
        std::string const& Pathname() const { return pathname_; }
        std::string        ToString(Visitor const& to_s) const { return to_string(to_s); }

    private:
        std::string const pathname_;

        virtual std::string to_string(Visitor const& to_s) const = 0;
        static std::string  strip(std::string const& pathname)
        {
            return std::regex_replace(pathname, std::regex{R"(/+$)"}, "");
        }
    };

    class File;
    class Dir;
    class OtherEntity;

    class Visitor {
    public:
        virtual ~Visitor() = default;
        std::string Visit(File const& file) const { return visit(file); }
        std::string Visit(Dir const& dir) const { return visit(dir); }
        std::string Visit(OtherEntity const& other) const { return visit(other); }

    private:
        virtual std::string visit(File const& file) const     = 0;
        virtual std::string visit(Dir const& dir) const       = 0;
        virtual std::string visit(OtherEntity const& f) const = 0;
    };

    class File final : public FileEntity {
    public:
        explicit File(std::string const& pathname) : FileEntity{pathname} {}

    private:
        virtual std::string to_string(Visitor const& to_s) const { return to_s.Visit(*this); }
    };

    class Dir final : public FileEntity {
    public:
        explicit Dir(std::string const& pathname) : FileEntity{pathname} {}

    private:
        virtual std::string to_string(Visitor const& to_s) const { return to_s.Visit(*this); }
    };

    class OtherEntity final : public FileEntity {
    public:
        explicit OtherEntity(std::string const& pathname) : FileEntity{pathname} {}

    private:
        virtual std::string to_string(Visitor const& to_s) const { return to_s.Visit(*this); }
    };

    class ToStringNormal : public Visitor {
    private:
        virtual std::string visit(File const& file) const override { return file.Pathname(); }
        virtual std::string visit(Dir const& dir) const override { return dir.Pathname() + '/'; }
        virtual std::string visit(OtherEntity const& other) const override { return other.Pathname(); }
    };

    class ToStringWithChar : public Visitor {
    private:
        virtual std::string visit(File const& file) const override { return file.Pathname(); }
        virtual std::string visit(Dir const& dir) const override { return dir.Pathname() + '/'; }
        virtual std::string visit(OtherEntity const& other) const override { return other.Pathname() + '+'; }
    };

    class ToStringWithChildren : public Visitor {
    private:
        virtual std::string visit(File const& file) const override { return file.Pathname(); }
        virtual std::string visit(Dir const& dir) const override { return find_files(dir.Pathname()); }
        virtual std::string visit(OtherEntity const& other) const override { return other.Pathname(); }

        static std::string find_files(std::string const& dir)
        {
            namespace fs = std::filesystem;

            auto files = std::vector<std::string>{};

            std::for_each(fs::recursive_directory_iterator{dir}, fs::recursive_directory_iterator{},
                          [&files](fs::path const& p) { files.emplace_back(p.generic_string()); });

            std::sort(files.begin(), files.end());

            auto ret = std::string{dir};

            for (auto f : files) {
                ret += ' ' + f;
            }

            return ret;
        }
    };

    TEST(DesignPatternQ, CRTP)
    {
        auto ts_normal   = ToStringNormal{};
        auto ts_char     = ToStringWithChar{};
        auto ts_children = ToStringWithChildren{};

        auto const f0 = File{"../ut_data/a.cpp"};
        auto const f1 = File{"../ut_data/a.cpp///"};

        ASSERT_EQ("../ut_data/a.cpp", f0.Pathname());
        ASSERT_EQ("../ut_data/a.cpp", f0.Pathname());

        ASSERT_EQ("../ut_data/a.cpp", f0.ToString(ts_normal));
        ASSERT_EQ("../ut_data/a.cpp", f0.ToString(ts_char));
        ASSERT_EQ("../ut_data/a.cpp", f0.ToString(ts_children));

        auto const dir = Dir{"../ut_data/lib/"};

        ASSERT_EQ("../ut_data/lib", dir.Pathname());
        ASSERT_EQ("../ut_data/lib/", dir.ToString(ts_normal));
        ASSERT_EQ("../ut_data/lib/", dir.ToString(ts_char));
        ASSERT_EQ("../ut_data/lib ../ut_data/lib/lib.cpp ../ut_data/lib/lib.h", dir.ToString(ts_children));

        auto const other = OtherEntity{"symbolic_link"};

        ASSERT_EQ("symbolic_link", other.Pathname());
        ASSERT_EQ("symbolic_link", other.ToString(ts_normal));
        ASSERT_EQ("symbolic_link+", other.ToString(ts_char));
        ASSERT_EQ("symbolic_link", other.ToString(ts_children));
    }
```

* 参照 [CRTP(curiously recurring template pattern)](cpp_idioms.md#SS_21_1_4)
* [解答例-CRTP](exercise_a.md#SS_23_9_23)


### 演習-Observer <a id="SS_22_9_24"></a>
* 問題
```cpp
    //  exercise/design_pattern_q/observer.cpp 7
    // [Q]
    // 下記クラスはそれぞれが
    //      * ViewX、 ViewY : GUIへの出力(描画)
    //      * Model         : 何らかのビジネスロジックの演算
    //      * Controller    : OKボタンクリックイベントをModelへ通知
    // を行うことを模擬している。
    // 依存関係Model->ViewX、ViewYはMVCに逆行しているため下記のような問題を持つ。
    //      * ViewX、ViewYの変更がModelに伝搬してしまう。
    //      * この例は単純であるためViewX、ViewY->Modelへの依存関係は存在しないが、
    //        実際のアプリケーションではそのような依存関係が存在するため、依存関係が循環してしまう。
    //      * ModelがダイレクトにViewX、ViewYへ出力するため、単体テストの実施は困難である。
    //      * この依存関係が直接の原因ではないが、このような依存関係を持つアプリケーションのクラスは
    //        巨大になる。
    //  アプリケーションが小規模である時には、このような問題がバグや開発効率悪化の原因となることは稀
    //  であり放置されることが多いが、大規模化に伴いこのような潜在的問題が表出する。
    //  ModelにObserverパターンを適用する等をしてこの問題に対処するとともに、Modelの単体テストを行え。

    class ViewX {
    public:
        void DisplaySomething(std::string const&) noexcept {}
    };
    ViewX g_ViewX;

    class ViewY {
    public:
        void DisplaySomething(std::string const&) noexcept {}
    };
    ViewY g_ViewY;

    class Model {
    public:
        Model() = default;
        ~Model() { wait_future(); }

        void DoSomething()
        {
            wait_future();

            future_ = std::async(std::launch::async, [] {
                // 本来は非同期処理が必要な重い処理
                auto result = std::string{"result of doing something"};

                g_ViewX.DisplaySomething(result);
                g_ViewY.DisplaySomething(result);
            });
        }

    private:
        std::future<void> future_;

        void wait_future() noexcept
        {
            if (future_.valid()) {
                future_.wait();
            }
        }
    };

    class Controller {
    public:
        Controller(Model& model) noexcept : model_{model} {}
        void OK_Clicked() { model_.DoSomething(); }

        Model& model_;
    };

    TEST(DesignPatternQ, Observer)
    {
        auto model      = Model{};
        auto controller = Controller{model};

        controller.OK_Clicked();
        controller.OK_Clicked();
        controller.OK_Clicked();
    }
```

* 参照 [Observer](design_pattern.md#SS_9_2_4)
* [解答例-Observer](exercise_a.md#SS_23_9_24)


### 演習-デザインパターン選択1 <a id="SS_22_9_25"></a>
* 問題  
  オブジェクトの状態と、
  それに伴う振る舞いを分離して記述する場合に使用されるデザインパターンとは何か？
  下記から選択せよ。

* 選択肢  
    1. Singleton
    2. State
    3. Observer
    4. Null Object

* [解答-デザインパターン選択1](exercise_a.md#SS_23_9_25)


### 演習-デザインパターン選択2 <a id="SS_22_9_26"></a>
* 問題  
  オブジェクトへのポインタがヌルかどうかを確かめるif文が頻繁に出てくる場合、
  そのif文を無くすために使われるデザインパターンは何か？
  下記から選択せよ。

* 選択肢  
    1. Singleton
    2. State
    3. Observer
    4. Null Object

* [解答-デザインパターン選択2](exercise_a.md#SS_23_9_26)


### 演習-デザインパターン選択3 <a id="SS_22_9_27"></a>
* 問題  
  MVCアーキテクチャの実現のためによく使われるデザインパターンは何か？
  以下から選択せよ。

* 選択肢  
    1. Singleton
    2. State
    3. Observer
    4. Null Object

* [解答-デザインパターン選択3](exercise_a.md#SS_23_9_27)


## 開発プロセスとインフラ(全般) <a id="SS_22_10"></a>

### 演習-プロセス分類 <a id="SS_22_10_1"></a>
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

* [解答-プロセス分類](exercise_a.md#SS_23_10_1)


### 演習-V字モデル <a id="SS_22_10_2"></a>
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

* [解答-V字モデル](exercise_a.md#SS_23_10_2)


### 演習-アジャイル <a id="SS_22_10_3"></a>
* 問題  
  アジャイル系プロセスの説明にふさわしくないものを選べ。

* 選択肢  
    1. アジャイル系プロセスとは、敏捷かつ適応的にソフトウェア開発を行う軽量な開発手法群の総称である。
    2. アジャイル系プロセスには計画は必要ない。
    3. ほとんどのアジャイル系プロセスでは、イテレーションを繰り返すことにより開発を進める。
    4. アジャイル系プロセスにはスクラムやXPがある。

* [解答-アジャイル](exercise_a.md#SS_23_10_3)


### 演習-自動化 <a id="SS_22_10_4"></a>
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

* [解答-自動化](exercise_a.md#SS_23_10_4)


### 演習-単体テスト <a id="SS_22_10_5"></a>
* 問題  
  単体テストの説明としてふさわしくないものを選べ。

* 選択肢  
    1. 単体テストで検出可能なバグを、統合テストで検出・デバッグすることは非効率である。
    2. 単体テストが可能なクラス設計には、プログラマのスキルの向上が必要である。
    3. 自動単体テストは工数をほとんどロスすることなしに何度でも実行できるため、
       機能追加、バグ修正、リファクタリング等のソースコード修正後の回帰テストが容易になる。
    4. 単体テストはアジャイル系プロセスのみで使われるテスト手法である。

* [解答-単体テスト](exercise_a.md#SS_23_10_5)


### 演習-リファクタリングに付随する活動 <a id="SS_22_10_6"></a>
* 問題  
  リファクタリングに付随する活動ではないものを選べ。

* 選択肢  
    1. ソースコードインスペクション
    2. 受入テスト
    3. 回帰テスト
    4. クラス分割

* [解答-リファクタリングに付随する活動](exercise_a.md#SS_23_10_6)


### 演習-リファクタリング対象コード <a id="SS_22_10_7"></a>
* 問題  
  リファクタリングの対象とならないソースコードの問題点を下記から選べ。

* 選択肢  
    1. 巨大なクラス
    2. コードクローン
    3. メモリリーク
    4. 間違った依存関係

* [解答-リファクタリング対象コード](exercise_a.md#SS_23_10_7)


### 演習-CI <a id="SS_22_10_8"></a>
* 問題  
  CI(継続的インテグレーション)を前提とするプロセスに特徴的な活動すべてを下記から選べ。

* 選択肢  
    1. (svnやgitリポジトリへの)コミット前にコードインスペクションを行う。
    2. リポジトリの最新ソースコードを自動的にビルド、単体テストを行うプログラムの開発や設定を行う。
    3. コミット前に回帰テストを行う。
    4. 開発者全員に共有されているブランチになるべく頻繁にコミットする。

* [解答-CI](exercise_a.md#SS_23_10_8)


## テンプレートメタプログラミング <a id="SS_22_11"></a>

### 演習-パラメータパック <a id="SS_22_11_1"></a>
* 問題
```cpp
    //  exercise/template_q/parameter_pack.cpp 5
    // [Q]
    // 下記の関数Maxは、単体テストが示す通り、2つのパラメータの大きい方を返す。
    // 任意の個数の引数を取れるようにMaxを修正せよ。

    template <typename T>
    T Max(T const& t0, T const& t1) noexcept
    {
        return t0 > t1 ? t0 : t1;
    }

    TEST(TemplateMetaProgrammingQ, parameter_pack)
    {
        ASSERT_EQ(2, Max(1, 2));
        ASSERT_EQ("bcd", Max(std::string{"abc"}, std::string{"bcd"}));
    }
```

* 参照 [パラメータパック](core_lang_spec.md#SS_19_11_4)
* [解答例-パラメータパック](exercise_a.md#SS_23_11_1)


### 演習-エイリアステンプレート <a id="SS_22_11_2"></a>
* 問題
```cpp
    //  exercise/template_q/template_alias.cpp 5
    // [Q]
    // 下記の単体テストでしているstd::vector<std::vector<XXX>>を、
    // テンプレートエイリアスによって簡潔に記述せよ。

    TEST(TemplateMetaProgrammingQ, template_alias)
    {
        {
            auto vv = std::vector<std::vector<int>>{{1, 2, 3}, {3, 4, 5}};
            ASSERT_EQ(2, vv.size());
            ASSERT_EQ((std::vector<int>{1, 2, 3}), vv[0]);
            ASSERT_EQ((std::vector<int>{3, 4, 5}), vv[1]);
            ASSERT_EQ(5, vv[1][2]);
        }
        {
            auto vv = std::vector<std::vector<float>>{{1, 2, 3}, {3, 4, 5}};
            ASSERT_EQ(2, vv.size());
            ASSERT_EQ((std::vector<float>{1, 2, 3}), vv[0]);
            ASSERT_EQ((std::vector<float>{3, 4, 5}), vv[1]);
            ASSERT_EQ(5, vv[1][2]);
        }
        {
            auto vv = std::vector<std::vector<std::string>>{{"1", "2", "3"}, {"3", "4", "5"}};
            ASSERT_EQ(2, vv.size());
            ASSERT_EQ((std::vector<std::string>{"1", "2", "3"}), vv[0]);
            ASSERT_EQ((std::vector<std::string>{"3", "4", "5"}), vv[1]);
            ASSERT_EQ("5", vv[1][2]);
        }
    }
```

* [解答例-エイリアステンプレート](exercise_a.md#SS_23_11_2)


### 演習-名前空間による修飾不要な`operator<<` <a id="SS_22_11_3"></a>
* 問題
```cpp
    //  exercise/template_q/put_to.cpp 3
    // [Q]
    // 下記のように名前空間TemplateMP、エイリアスInts_tとそのoperator<<が定義されている場合、
    // 単体テストで示した通り、Ints_tのoperator<<を使用するためには、
    // 名前空間による修飾やusing宣言/ディレクティブの記述が必要になる。
    // Ints_tをstd::vectorから継承したクラスとして定義することにより、このような記述を不要にせよ。

    namespace TemplateMP {

    using Ints_t = std::vector<int>;

    std::ostream& operator<<(std::ostream& os, Ints_t const& ints)
    {
        auto first = true;
        for (auto i : ints) {
            if (!std::exchange(first, false)) {
                os << " : ";
            }
            os << i;
        }

        return os;
    }
    }  // namespace TemplateMP

    namespace {
    TEST(TemplateMetaProgrammingQ, put_to)
    {
        {
            auto oss  = std::ostringstream{};
            auto ints = TemplateMP::Ints_t{1, 2, 3};

            // oss << ints;
            TemplateMP::operator<<(oss, ints);  // 名前空間による飾

            ASSERT_EQ("1 : 2 : 3", oss.str());
        }
        {
            auto oss  = std::ostringstream{};
            auto ints = TemplateMP::Ints_t{1, 2, 3};

            using TemplateMP::operator<<;  // using宣言
            oss << ints;

            ASSERT_EQ("1 : 2 : 3", oss.str());
        }
        {
            auto oss  = std::ostringstream{};
            auto ints = TemplateMP::Ints_t{1, 2, 3};

            using namespace TemplateMP;  // usingディレクティブ
            oss << ints;

            ASSERT_EQ("1 : 2 : 3", oss.str());
        }
    }
    }  // namespace
```

* 参照 [Ints_tのログ登録](template_meta_programming.md#SS_13_1_6)、[Ints_tを構造体としてApp内に宣言する](template_meta_programming.md#SS_13_1_6_5)、
* [解答例-名前空間による修飾不要な`operator<<`](exercise_a.md#SS_23_11_3)


### 演習-std::arrayの継承 <a id="SS_22_11_4"></a>
* 問題
```cpp
    //  exercise/template_q/safe_array.cpp 3
    // [Q]
    // std::array、std::vector、std::string等のSTLの配列型コンテナはインデックスアクセスに対して、
    // レンジのチェックをしないため、不正なメモリアクセスをしてしまうことがある。
    // std::arrayを使用して、このような問題のないSafeArrayを作り、単体テストを行え。

    namespace {
    TEST(TemplateMetaProgrammingQ, safe_array)
    {
        // SafeArrayの単体テスト
    }
    }  // namespace
```

* 参照 [安全な配列型コンテナ](template_meta_programming.md#SS_13_2_3)
* [解答例-std::arrayの継承](exercise_a.md#SS_23_11_4)


### 演習-SFINAEを利用しない関数テンプレートの特殊化によるis_void <a id="SS_22_11_5"></a>
* 問題
```cpp
    //  exercise/template_q/is_void.cpp 3
    // [Q]
    // 下記の仕様を満たす関数テンプレートis_void_f<T>と定数テンプレートis_void_f_v<T>を作れ。
    //    * 与えられたテンプレートパラメータがvoidの場合、trueを返す
    //    * 与えられたテンプレートパラメータがvoidでない場合、falseを返す
    //    * std::is_sameを使わない
    //    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

    namespace IsVoidTest {
    void        test_func_0() noexcept {};
    std::string test_func_1() { return "test"; };
    }  // namespace IsVoidTest

    namespace {

    TEST(TemplateMetaProgrammingQ, is_void_f)
    {
    #if 0
        static_assert(!is_void_f_v<int>);
        static_assert(is_void_f_v<void>);
        static_assert(is_void_f_v<decltype(IsVoidTest::test_func_0())>);
        static_assert(!is_void_f_v<decltype(IsVoidTest::test_func_1())>);
    #endif
    }
    }  // namespace
```

* 参照 [is_void_f](template_meta_programming.md#SS_13_3_1_1)
* [解答例-SFINAEを利用しない関数テンプレートの特殊化によるis_void](exercise_a.md#SS_23_11_5)


### 演習-SFINAEを利用しないクラステンプレートの特殊化によるis_void <a id="SS_22_11_6"></a>
* 問題
    //  exercise/template_q/is_void.cpp 30
    // [Q]
    // 下記の仕様を満たすクラステンプレートis_void_s<T>と定数テンプレートis_void_s_v<T>を作れ。
    //    * 与えられたテンプレートパラメータがvoidの場合、メンバvalueがtrueになる
    //    * 与えられたテンプレートパラメータがvoidでない場合、メンバvalueがtrueになる
    //    * std::is_sameを使わない
    //    * std::true_type/std::false_typeを利用する
    //    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

    namespace {

    TEST(TemplateMetaProgrammingQ, is_void_s)
    {
    #if 0
        static_assert(!is_void_s_v<int>);
        static_assert(is_void_s_v<void>);
        static_assert(is_void_s_v<decltype(IsVoidTest::test_func_0())>);
        static_assert(!is_void_s_v<decltype(IsVoidTest::test_func_1())>);
    #endif
    }
    }  // namespace
```cpp
```

* 参照 [is_void_s](template_meta_programming.md#SS_13_3_1_2)
* [解答例-SFINAEを利用しないクラステンプレートの特殊化によるis_void](exercise_a.md#SS_23_11_6)


### 演習-SFINAEを利用した関数テンプレートの特殊化によるis_void <a id="SS_22_11_7"></a>
* 問題
```cpp
    //  exercise/template_q/is_void.cpp 53
    // [Q]
    // 下記の仕様を満たす関数テンプレートis_void_sfinae_f<T>と
    // 定数テンプレートis_void_sfinae_f<T>を作れ。
    //    * 与えられたテンプレートパラメータがvoidの場合、trueを返す
    //    * 与えられたテンプレートパラメータがvoidでない場合、falseを返す
    //    * std::is_sameを使わない
    //    * SFINAEを利用する
    //    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

    namespace {

    TEST(TemplateMetaProgrammingQ, is_void_sfinae_f)
    {
    #if 0
        static_assert(!is_void_sfinae_f_v<int>);
        static_assert(is_void_sfinae_f_v<void>);
        static_assert(is_void_sfinae_f_v<decltype(IsVoidTest::test_func_0())>);
        static_assert(!is_void_sfinae_f_v<decltype(IsVoidTest::test_func_1())>);
    #endif
    }
    }  // namespace
```

* 参照 [is_void_sfinae_f](template_meta_programming.md#SS_13_3_1_3)
* [解答例-SFINAEを利用した関数テンプレートの特殊化によるis_void](exercise_a.md#SS_23_11_7)


### 演習-SFINAEを利用したクラステンプレートの特殊化によるis_void <a id="SS_22_11_8"></a>
* 問題
```cpp
    //  exercise/template_q/is_void.cpp 77
    // [Q]
    // 下記の仕様を満たすクラステンプレートis_void_sfinae_s<T>と
    // 定数テンプレートis_void_sfinae_s_v<T>を作れ。
    //    * 与えられたテンプレートパラメータがvoidの場合、メンバvalueがtrueになる
    //    * 与えられたテンプレートパラメータがvoidでない場合、メンバvalueがtrueになる
    //    * std::is_sameを使わない
    //    * std::true_type/std::false_typeを利用する
    //    * SFINAEを利用する
    //    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

    namespace {

    TEST(TemplateMetaProgrammingQ, is_void_sfinae_s)
    {
    #if 0
        static_assert(!is_void_sfinae_s_v<int>);
        static_assert(is_void_sfinae_s_v<void>);
        static_assert(is_void_sfinae_s_v<decltype(IsVoidTest::test_func_0())>);
        static_assert(!is_void_sfinae_s_v<decltype(IsVoidTest::test_func_1())>);
    #endif
    }
    }  // namespace
```

* 参照 [is_void_sfinae_s](template_meta_programming.md#SS_13_3_1_4)
* [解答例-SFINAEを利用したクラステンプレートの特殊化によるis_void](exercise_a.md#SS_23_11_8)


### 演習-テンプレートテンプレートパラメータ <a id="SS_22_11_9"></a>
* 問題
```cpp
    //  exercise/template_q/template_template.cpp 3
    // [Q]
    // 以下の使用を満たすクラステンプレートを作れ。
    //  * 任意のSTLコンテナを唯一のテンプレートパラメータとする
    //  * そのコンテナを使用しint型のデータを格納する

    namespace {

    TEST(TemplateMetaProgrammingQ, template_template)
    {
        //
    }
    }  // namespace
```

* 参照 [is_same_templ](template_meta_programming.md#SS_13_3_2_7)
* [解答例-テンプレートテンプレートパラメータ](exercise_a.md#SS_23_11_9)


### 演習-テンプレートパラメータを可変長にしたstd::is_same <a id="SS_22_11_10"></a>
* 問題
```cpp
    //  exercise/template_q/is_same.cpp 3
    // [Q]
    // 以下の仕様を満たすクラステンプレートis_same_some_of<T, U...>と
    // 定数テンプレートis_same_some_of_v<T, U...>を作れ。
    //  * 2個以上のテンプレートパラメータを持つ
    //  * 第1パラメータと他のパラメータの何れかが同一の型であった場合、メンバvalueがtrueになる
    //  * 前行の条件が成立しなかった場合、メンバvalueがfalseになる
    //  * 型の同一性はstd::is_sameを使って判定する

    namespace {

    TEST(TemplateMetaProgrammingQ, is_same_some_of)
    {
    #if 0
        static_assert(!is_same_some_of_v<int, int8_t, int16_t, uint16_t>);
        static_assert(is_same_some_of_v<int, int8_t, int16_t, uint16_t, int32_t>);
        static_assert(is_same_some_of_v<int&, int8_t, int16_t, int32_t&, int32_t>);
        static_assert(!is_same_some_of_v<int&, int8_t, int16_t, uint32_t&, int32_t>);
        static_assert(is_same_some_of_v<std::string, int, char*, std::string>);
        static_assert(!is_same_some_of_v<std::string, int, char*>);
    #endif
    }
    }  // namespace
```

* 参照 [IsSameSomeOf](template_meta_programming.md#SS_13_3_2_8)
* [解答例-テンプレートパラメータを可変長にしたstd::is_same](exercise_a.md#SS_23_11_10)


### 演習-メンバ関数の存在の診断 <a id="SS_22_11_11"></a>
* 問題
```cpp
    //  exercise/template_q/exists_func.cpp 3
    // [Q]
    // テンプレートパラメータの型がメンバ関数c_str()を持つか否かを判定する
    // クラステンプレートhas_c_str<T>と定数テンプレートhas_c_str_v<T>を作れ。

    namespace {

    TEST(TemplateMetaProgrammingQ, has_c_str)
    {
    #if 0
        static_assert(has_c_str_v<std::string>);
        static_assert(!has_c_str_v<std::vector<int>>);
    #endif
    }
    }  // namespace
```

* 参照 [関数の存在の診断](template_meta_programming.md#SS_13_3_4)
* [解答例-メンバ関数の存在の診断](exercise_a.md#SS_23_11_11)


### 演習-範囲for文のオペランドになれるかどうかの診断 <a id="SS_22_11_12"></a>
* 問題
```cpp
    //  exercise/template_q/exists_func.cpp 20
    // [Q]
    // 範囲for文は、
    //      for(auto a : obj ) { ... }
    // のような形式で表現される。
    // テンプレートパラメータから生成されたオブジェクトが、
    // このobjに指定できるか否かを判定するクラステンプレートis_range<T>
    // と定数テンプレートis_range_v<T>を作れ。

    namespace {

    TEST(TemplateMetaProgrammingQ, is_range)
    {
    #if 0
        static_assert(is_range_v<std::string>);
        static_assert(is_range_v<std::vector<int>>);
        static_assert(!is_range_v<std::mutex>);
        static_assert(!is_range_v<std::lock_guard<std::mutex>>);
    #endif
    }
    }  // namespace
```

* 参照 [関数の存在の診断](template_meta_programming.md#SS_13_3_4)
* [解答例-範囲for文のオペランドになれるかどうかの診断](exercise_a.md#SS_23_11_12)


### 演習-配列の長さの取り出し <a id="SS_22_11_13"></a>
* 問題
```cpp
    //  exercise/template_q/array_op.cpp 3
    // [Q]
    // 配列を引数に取り、その長さを返す関数テンプレートarray_lengthを作れ。

    namespace {

    TEST(TemplateMetaProgrammingQ, array_length)
    {
    #if 0
        int         i[5];
        std::string str[]{"a", "b", "c"};

        static_assert(array_length(i) == 5);
        static_assert(array_length(str) == 3);
    #endif
    }
    }  // namespace
```

* 参照 [関数の存在の診断](template_meta_programming.md#SS_13_3_4)
* [解答例-配列の長さの取り出し](exercise_a.md#SS_23_11_13)


### 演習-配列の次元の取り出し <a id="SS_22_11_14"></a>
* 問題
```cpp
    //  exercise/template_q/array_op.cpp 22
    // [Q]
    // 配列を引数に取り、その次元を返す関数テンプレートarray_dimensionを作れ。

    namespace {

    TEST(TemplateMetaProgrammingQ, array_dimension)
    {
    #if 0
        constexpr int i1[5]{};
        constexpr int i2[5][2]{};
        constexpr int i3[5][2][3]{};

        static_assert(array_dimension(i1) == 1);
        static_assert(array_dimension(i2) == 2);
        static_assert(array_dimension(i3) == 3);
    #endif
    }
    }  // namespace
```

* 参照 [ValueTypeの実装](template_meta_programming.md#SS_13_3_4_15)
* [解答例-配列の次元の取り出し](exercise_a.md#SS_23_11_14)


### 演習-関数型のテンプレートパラメータを持つクラステンプレート <a id="SS_22_11_15"></a>
* 問題
```cpp
    //  exercise/template_q/scoped_guard.cpp 8
    // [Q]
    // RAIIを行うための下記クラスscoped_guardをstd::functionを使わずに再実装せよ。

    class scoped_guard {
    public:
        explicit scoped_guard(std::function<void()> f) noexcept : f_{f} {}
        ~scoped_guard() { f_(); }

        scoped_guard(scoped_guard const&)   = delete;
        void operator=(scoped_guard const&) = delete;

    private:
        std::function<void()> f_;
    };

    namespace {

    TEST(TemplateMetaProgrammingQ, scoped_guard)
    {
        {
            auto demangled = abi::__cxa_demangle(typeid(std::vector<int>).name(), 0, 0, nullptr);
            auto sg        = scoped_guard{[demangled]() noexcept { free(demangled); }};

            ASSERT_STREQ("std::vector<int, std::allocator<int> >", demangled);
        }
        {
            auto stream = popen("ls " __FILE__, "r");
            auto sg     = scoped_guard{[stream]() noexcept { fclose(stream); }};

            char buff[256]{};
            fgets(buff, sizeof(buff) - 1, stream);

            ASSERT_STREQ("scoped_guard.cpp\n", buff);
        }
    }
    }  // namespace
```

* 参照 [関数型をテンプレートパラメータで使う](template_meta_programming.md#SS_13_7_7)
* [解答例-関数型のテンプレートパラメータを持つクラステンプレート](exercise_a.md#SS_23_11_15)


