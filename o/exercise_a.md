<!-- ./md/exercise_a.md -->
# 解答 <a id="SS_23"></a>

__この章の構成__

&emsp;&emsp; [プログラミング規約(型)](exercise_a.md#SS_23_1)  
&emsp;&emsp; [プログラミング規約(クラス)](exercise_a.md#SS_23_2)  
&emsp;&emsp; [プログラミング規約(関数)](exercise_a.md#SS_23_3)  
&emsp;&emsp; [プログラミング規約(構文)](exercise_a.md#SS_23_4)  
&emsp;&emsp; [プログラミング規約(演算子)](exercise_a.md#SS_23_5)  
&emsp;&emsp; [プログラミング規約(スコープ)](exercise_a.md#SS_23_6)  
&emsp;&emsp; [プログラミング規約(その他)](exercise_a.md#SS_23_7)  
&emsp;&emsp; [SOLID](exercise_a.md#SS_23_8)  
&emsp;&emsp; [デザインパターン](exercise_a.md#SS_23_9)  
&emsp;&emsp; [開発プロセスとインフラ(全般)](exercise_a.md#SS_23_10)  
&emsp;&emsp; [テンプレートメタプログラミング](exercise_a.md#SS_23_11)  
  
  
  
[インデックス](introduction.md#SS_1_4)に戻る。  

___

## プログラミング規約(型) <a id="SS_23_1"></a>

### 解答-汎整数型の選択 <a id="SS_23_1_1"></a>
* 選択肢3
* 参照 [算術型](programming_convention.md#SS_3_1_1)
* 解説  
  代入する小さい整数に合わせて8ビット型や16ビット型を使うと、
  それら同士の演算時にint昇格が起こり、わかりづらいバグを生むことがある。  
  int32_tを使うことは、
  ほとんどのコンパイラでint32_tの実際の型がintであることを利用しているため、
  その前提を避けるべきと考えるのであれば、int32_tの代わりにint、
  uint32_tの代わりにunsigned intを使用すればよい。

* [演習-汎整数型の選択](exercise_q.md#SS_22_1_1)へ戻る。


### 解答例-汎整数型の演算 <a id="SS_23_1_2"></a>
```cpp
    //  exercise/programming_convention_a/type.cpp 14
    TEST(ProgrammingConventionTypeA, GeneralInteger)
    {
        // [A]
        // 以下の組み込み型の使用方法は、その下のテストコードを(環境依存で)パスするが、
        // 適切であるとは言えない。適切な型に修正せよ。
        int32_t b{1};
        int32_t i{b};
        int32_t c{-1};

        ASSERT_EQ(i * c, -1);
    }
```

* [演習-汎整数型の演算](exercise_q.md#SS_22_1_2)へ戻る。


### 解答例-浮動小数点型 <a id="SS_23_1_3"></a>
```cpp
    //  exercise/programming_convention_a/type.cpp 28
    double f(double a) noexcept { return 1 / a; }

    template <typename FLOAT_0, typename FLOAT_1>
    bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs)
    {
        static_assert(std::is_floating_point_v<FLOAT_0>, "FLOAT_0 shoud be float or double.");
        static_assert(std::is_same_v<FLOAT_0, FLOAT_1>, "FLOAT_0 and FLOAT_1 shoud be a same type.");

        return std::abs(lhs - rhs) <= std::numeric_limits<FLOAT_0>::epsilon();
    }

    TEST(ProgrammingConventionTypeA, Float)
    {
        // [A]
        // 以下の両辺を同一と判定するための関数を作り、その関数の単体テストを行え。
        ASSERT_TRUE(is_equal(1.0, 1 + 0.001 - 0.001));

        // [A]
        // 以下の0除算を捕捉するためのコードを書け。
        std::feclearexcept(FE_ALL_EXCEPT);  // エラーをクリア
        f(0.0);
        ASSERT_TRUE(std::fetestexcept(FE_ALL_EXCEPT) & FE_DIVBYZERO);
        std::feclearexcept(FE_ALL_EXCEPT);  // エラーをクリア
    }
```

* [演習-浮動小数点型](exercise_q.md#SS_22_1_3)へ戻る。


### 解答-定数列挙 <a id="SS_23_1_4"></a>
* 選択肢4
* 参照 [enum](core_lang_spec.md#SS_19_3_1)
* [演習-定数列挙](exercise_q.md#SS_22_1_4)へ戻る。


### 解答例-enum <a id="SS_23_1_5"></a>
```cpp
    //  exercise/programming_convention_a/type.cpp 55
    // [A]
    // 以下のマクロ引数を型安全なenumに修正せよ

    enum class Color { Red, Green, Blue };

    std::string GetString(Color color)
    {
        switch (color) {
        case Color::Red:
            return "Red";
        case Color::Green:
            return "Green";
        case Color::Blue:
            return "Blue";
        default:
            assert(false);
            return "";
        }
    }

    TEST(ProgrammingConventionTypeA, Enum)
    {
        ASSERT_EQ(std::string{"Red"}, GetString(Color::Red));
        ASSERT_EQ(std::string{"Green"}, GetString(Color::Green));
        ASSERT_EQ(std::string{"Blue"}, GetString(Color::Blue));
    }
```

* [演習-enum](exercise_q.md#SS_22_1_5)へ戻る。


### 解答例-配列の範囲for文 <a id="SS_23_1_6"></a>
```cpp
    //  exercise/programming_convention_a/type.cpp 84
    int32_t array_value() noexcept
    {
        static int32_t i;

        return i++;
    }

    TEST(ProgrammingConventionTypeA, Array)
    {
        // [A]
        // 以下の配列の値の設定を範囲for文を使って書き直せ
        int32_t array[10];

        for (auto& a : array) {
            a = array_value();
        }

        ASSERT_EQ(0, array[0]);
        ASSERT_EQ(3, array[3]);
        ASSERT_EQ(9, array[9]);
    }
```

* [演習-配列の範囲for文](exercise_q.md#SS_22_1_6)へ戻る。


### 解答例-エイリアス <a id="SS_23_1_7"></a>
```cpp
    //  exercise/programming_convention_a/type.cpp 108
    // [A]
    // 以下のtypedefをC++11から導入された新しい形式のエイリアスに直せ。
    using uchar     = unsigned char;
    using func_type = bool (*)(int32_t);

    // [A]
    // template引数で与えられた型のオブジェクトをstd::vectorで保持するエイリアスtemplateを
    // 定義し、その単体テストを行え。
    template <class T>
    using TypeVector = std::vector<T>;

    TEST(ProgrammingConventionTypeA, Alias)
    {
        auto a = TypeVector<std::string>{"abc", "de", "f"};

        ASSERT_EQ((std::vector<std::string>{"abc", "de", "f"}), a);
        ASSERT_EQ(3, a.size());
    }
```

* [演習-エイリアス](exercise_q.md#SS_22_1_7)へ戻る。


### 解答-constの意味 <a id="SS_23_1_8"></a>
* 選択肢1
* 参照 [const/constexprインスタンス](programming_convention.md#SS_3_1_9)
* [演習-constの意味](exercise_q.md#SS_22_1_8)へ戻る。


### 解答例-const/constexpr <a id="SS_23_1_9"></a>
```cpp
    //  exercise/programming_convention_a/type.cpp 129
    // [A]
    // 下記のStringHolderに「const/constexprを付加する」等を行い、より良いコードに修正せよ。

    class StringHolder {
    public:
        StringHolder() = default;
        void Add(std::string const& str)
        {
            if (vector_len_max_ > strings_.size()) {
                strings_.push_back(str);
            }
        }

        std::vector<std::string> const& GetStrings() const noexcept { return strings_; }

    private:
        static constexpr size_t  vector_len_max_{3};
        std::vector<std::string> strings_{};
    };

    TEST(ProgrammingConventionTypeA, ConstConstexpr)
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

* [演習-const/constexpr](exercise_q.md#SS_22_1_9)へ戻る。


### 解答例-危険なconst_cast <a id="SS_23_1_10"></a>
```cpp
    //  exercise/programming_convention_a/type.cpp 166
    // [A]
    // 下記の"DISABLED_"を削除し、何が起こるのか、なぜそうなるのかを確かめた上で、
    // nameの型やその初期化を行っているコードを修正せよ。
    TEST(ProgrammingConventionTypeA, ConstConstexpr2)
    {
        char name[] = "abcdef";

        for (auto& n : name) {
            n = std::toupper(n);
        }

        ASSERT_STREQ("ABCDEF", name);
        ASSERT_EQ("ABCDEF", std::string{name});
    }
```

* [演習-危険なconst_cast](exercise_q.md#SS_22_1_10)へ戻る。


### 解答例-リテラル <a id="SS_23_1_11"></a>
```cpp
    //  exercise/programming_convention_a/type.cpp 186
    int32_t literal_test(int64_t) noexcept { return 0; }
    int32_t literal_test(int32_t*) noexcept { return 1; }

    // [A]
    // 下記変数の初期化コードをコメントに基づき適切に修正せよ。
    TEST(ProgrammingConventionTypeA, Literal)
    {
        int32_t* p{nullptr};                // NULLは使用不可
        uint64_t a{0x1234'5678'90ab'cdef};  // 適切なセパレータを挿入
        int32_t  b{0b0111'0001'0101};       // ビット表現に修正

        // [A]
        // 下記resultはfalseになるが、その理由を述べ、trueになるようにコードを修正せよ。
        bool const result{(literal_test(nullptr) == literal_test(p))};
        ASSERT_TRUE(result);

        ASSERT_EQ(0x1234567890abcdef, a);
        ASSERT_EQ(b, 0x715);
    }
```

* [演習-リテラル](exercise_q.md#SS_22_1_11)へ戻る。


### 解答-適切なautoの使い方 <a id="SS_23_1_12"></a>
* 選択肢4
* 参照 [auto](core_lang_spec.md#SS_19_11_14)
* [演習-適切なautoの使い方](exercise_q.md#SS_22_1_12)へ戻る。


### 解答-ポインタの初期化 <a id="SS_23_1_13"></a>
* 選択肢3
* 参照 [リテラル](core_lang_spec.md#SS_19_2)
* [演習-ポインタの初期化](exercise_q.md#SS_22_1_13)へ戻る。


### 解答-vector初期化 <a id="SS_23_1_14"></a>
* 選択肢1
* 参照 [インスタンスの初期化](programming_convention.md#SS_3_1_12)
* [演習-vector初期化](exercise_q.md#SS_22_1_14)へ戻る。


### 解答例-インスタンスの初期化 <a id="SS_23_1_15"></a>
```cpp
    //  exercise/programming_convention_a/type.cpp 209
    TEST(ProgrammingConventionTypeA, Initialization)
    {
        // [A]
        // 変数a、b、v、wの定義と初期化を1文で行え。
        {
            int32_t a[3]{1, 1, 1};

            ASSERT_EQ(1, a[0]);
            ASSERT_EQ(1, a[1]);
            ASSERT_EQ(1, a[2]);
        }
        {
            int32_t b[3]{};

            ASSERT_EQ(0, b[0]);
            ASSERT_EQ(0, b[1]);
            ASSERT_EQ(0, b[2]);
        }
        {
            auto v = std::vector<std::string>{3, std::string{"1"}};

            ASSERT_EQ("1", v[0]);
            ASSERT_EQ("1", v[1]);
            ASSERT_EQ("1", v[2]);
        }
        {
            auto w = std::vector<std::string>{"0", "1", "2"};

            ASSERT_EQ("0", w[0]);
            ASSERT_EQ("1", w[1]);
            ASSERT_EQ("2", w[2]);
        }
    }
```

* [演習-インスタンスの初期化](exercise_q.md#SS_22_1_15)へ戻る。


## プログラミング規約(クラス) <a id="SS_23_2"></a>

### 解答-凝集性の意味 <a id="SS_23_2_1"></a>
* 選択肢4
* 参照 [凝集性](programming_convention.md#SS_3_2_2_3)
* [演習-凝集性の意味](exercise_q.md#SS_22_2_1)へ戻る。


### 解答例-凝集性の向上 <a id="SS_23_2_2"></a>
```cpp
    //  exercise/programming_convention_a/class.cpp 7
    // [A]
    // 以下のクラスABCの凝集度が高くなるように、ABC、HasRealNumberSolutionをリファクタリングせよ。
    // その時に、他の問題があればそれも併せて修正せよ。

    class ABC {  // 2次方程式のパラメータ保持
    public:
        explicit ABC(int32_t a, int32_t b, int32_t c) noexcept : a_{a}, b_{b}, c_{c} {}

        bool HasRealNumberSolution() const noexcept { return 0 <= discriminant(); }

    private:
        int32_t const a_;
        int32_t const b_;
        int32_t const c_;

        int32_t discriminant() const noexcept  // 判定式
        {
            return b_ * b_ - 4 * a_ * c_;
        }
    };

    bool HasRealNumberSolution(ABC const& abc) noexcept { return abc.HasRealNumberSolution(); }

    TEST(ProgrammingConventionClassA, Cohision)
    {
        {
            auto const abc = ABC{1, 2, 1};

            ASSERT_TRUE(HasRealNumberSolution(abc));
        }
        {
            auto const abc = ABC{2, 0, 1};

            ASSERT_FALSE(HasRealNumberSolution(abc));
        }
    }
```

* [演習-凝集性の向上](exercise_q.md#SS_22_2_2)へ戻る。


### 解答-メンバ変数の初期化方法の選択 <a id="SS_23_2_3"></a>
* 選択肢2
* 参照 [非静的なメンバ変数](programming_convention.md#SS_3_2_5_2)
* [演習-メンバ変数の初期化方法の選択](exercise_q.md#SS_22_2_3)へ戻る。


### 解答-メンバの型 <a id="SS_23_2_4"></a>
* 選択肢3
* 参照 [インスタンスの初期化](programming_convention.md#SS_3_1_12)
* 解説  
  関数の宣言と、クラスのデフォルトコンストラクタ呼び出しによるオブジェクトの生成は、
  プログラマを混乱させることがあるので注意が必要である。
* [演習-メンバの型](exercise_q.md#SS_22_2_4)へ戻る。


### 解答例-メンバ変数の初期化 <a id="SS_23_2_5"></a>
```cpp
    //  exercise/programming_convention_a/class.cpp 46
    // [A]
    // 以下のMemberInitのメンバ変数を適切な方法で初期化せよ。

    class MemberInit {
    public:
        MemberInit() noexcept {}

        explicit MemberInit(int a) noexcept : a_{a}, b_{a, 99} {}

        int32_t GetA() const noexcept { return a_; }

        static constexpr size_t b_len{2};
        int32_t const (&GetB() const noexcept)[b_len] { return b_; }
        int32_t GetC() const noexcept { return c_; }

    private:
        int32_t const a_{0};
        int32_t const b_[b_len]{1, 1};
        int32_t const c_{2};
    };

    TEST(ProgrammingConventionClassA, MemberInit)
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

* [演習-メンバ変数の初期化](exercise_q.md#SS_22_2_5)へ戻る。


### 解答例-スライシング <a id="SS_23_2_6"></a>
```cpp
    //  exercise/programming_convention_a/class.cpp 89
    // [A]
    // 以下のクラスBaseはオブジェクトのスライシングを引き起こす。
    // このような誤用を起こさないようにするために、Baseオブジェクトのコピーを禁止せよ。
    // 合わせてクラスDerivedも含め、不十分な記述を修正せよ。

    class Base {
    public:
        explicit Base(char const* name = nullptr) noexcept : name_{name == nullptr ? "Base" : name} {}
        virtual ~Base() = default;

        virtual char const* Name0() const noexcept { return "Base"; }
        char const*         Name1() const noexcept { return name_; }

        Base& operator=(Base const& rhs) = delete;
        Base(Base const&)                = delete;

    private:
        char const* name_;
    };

    class Derived final : public Base {
    public:
        Derived() noexcept : Base{"Derived"} {}

        virtual char const* Name0() const noexcept override { return "Derived"; }
    };

    TEST(ProgrammingConventionClassA, Slicing)
    {
        auto  b     = Base{};
        auto  d     = Derived{};
        Base& d_ref = d;

        // 以下はBase、Derivedの単純なテスト
        ASSERT_STREQ("Base", b.Name0());
        ASSERT_STREQ("Base", b.Name1());
        ASSERT_STREQ("Derived", d_ref.Name0());
        ASSERT_STREQ("Derived", d_ref.Name1());

    #if 0
        // Base::operator=(Base const& rhs)をdeleteしたためにこのような誤用はコンパイルエラーになる。

        // 以下はbがスライスされたオブジェクトであることのテスト
        // こういった誤用を防ぐためにBaseのコピーを禁止せよ。
        b = d_ref;
        ASSERT_STREQ("Base", b.Name0());     // vtblはBaseになるから
        ASSERT_STREQ("Derived", b.Name1());  // name_はコピーされるから
    #else
        // 意図的に上記のようなことがしたい場合、下記のようにするべき。
        auto b_copy = Base{d_ref.Name0()};
        ASSERT_STREQ("Base", b_copy.Name0());     // vtblはBaseになるから
        ASSERT_STREQ("Derived", b_copy.Name1());  // name_はコピーされるから
    #endif
    }
```

* [演習-スライシング](exercise_q.md#SS_22_2_6)へ戻る。


### 解答例-オブジェクトの所有権 <a id="SS_23_2_7"></a>
```cpp
    //  exercise/programming_convention_a/class.cpp 146
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

    TEST(ProgrammingConventionClassA, Ownership)
    {
        // [A]
        // 以下の単体テストを完成させよ。

        ASSERT_EQ(-1, A::LastConstructedNum());     // まだ、A::A()は呼ばれてない
        ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない

        auto a0 = std::make_unique<A>(0);           // a0はA(0)を所有
        auto a1 = std::make_unique<A>(1);           // a1はA(1)を所有
        auto x = X {};

        ASSERT_EQ(1,  A::LastConstructedNum());     // A(1)は生成された
        ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない
        ASSERT_EQ(0, a0->GetNum());                 // a0はA(0)を所有
        x.Move(std::move(a0));                      // a0からxへA(0)の所有権の移動
        ASSERT_FALSE(a0);                           // a0は何も所有していない

        ASSERT_EQ(1, a1->GetNum());                 // a1はA(1)を所有
        x.Move(std::move(a1));                      // xによるA(0)の解放
                                                    // a1からxへA(1)の所有権の移動
        ASSERT_EQ(0, A::LastDestructedNum());       // A(0)は解放された
        ASSERT_FALSE(a1);                           // a1は何も所有していない
        ASSERT_EQ(1, x.GetA()->GetNum());           // xはA(1)を所有

        std::unique_ptr<A> a2{x.Release()};         // xからa2へA(1)の所有権の移動
        ASSERT_EQ(nullptr, x.GetA());               // xは何も所有していない
        ASSERT_EQ(1, a2->GetNum());                 // a2はA(1)を所有
        {
            std::unique_ptr<A> a3{std::move(a2)};
            ASSERT_FALSE(a2);                       // a2は何も所有していない
            ASSERT_EQ(1, a3->GetNum());             // a3はA(1)を所有
        }                                           // a3によるA(1)の解放
        ASSERT_EQ(1, A::LastDestructedNum());
    }
```

* [演習-オブジェクトの所有権](exercise_q.md#SS_22_2_7)へ戻る。


## プログラミング規約(関数) <a id="SS_23_3"></a>
### 解答例-非メンバ関数の宣言 <a id="SS_23_3_1"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 11
    TEST(ProgrammingConventionFuncA, NonMemberFunc)
    {
        // [A]
        // 適切な#includeを追加し、上記のextern宣言がなくとも下記がコンパイルできるようにせよ。

        // このファイルの先頭付近に
        // #include <cmath>
        // を追加した。

        ASSERT_EQ(1, cos(0));
    }
```

* [演習-非メンバ関数の宣言](exercise_q.md#SS_22_3_1)へ戻る。


### 解答例-メンバ関数の修飾 <a id="SS_23_3_2"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 25
    // [A]
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

        std::vector<std::string>&       GetStrings() noexcept { return strings_; }
        std::vector<std::string> const& GetStrings() const noexcept { return strings_; }
        constexpr size_t                MaxLen() const noexcept { return max_len; }

        static std::vector<std::string> const& GetStringsDefault()
        {
            static const std::vector<std::string> strings_default{max_len, ""};
            return strings_default;
        }

    private:
        std::vector<std::string> strings_;
        static constexpr size_t  max_len{3};
    };

    TEST(ProgrammingConventionFuncA, MemberFunc)
    {
        auto a = A{};

        auto const& strings_default = a.GetStringsDefault();
        ASSERT_EQ((std::vector<std::string>{a.MaxLen(), ""}), strings_default);

        auto const& strings = a.GetStrings();

        ASSERT_EQ((std::vector<std::string>{a.MaxLen(), ""}), strings);

        a.SetStrings(1, "TEST");
        ASSERT_EQ("", strings[0]);

        // [A]
        // このテストをASSERT_EQでパスできるようにせよ
        ASSERT_EQ("TEST", strings[1]);

        ASSERT_EQ("", strings[2]);

        // 上記は下記のように書くべき
        ASSERT_EQ((std::vector<std::string>{"", "TEST", ""}), strings);
    }
```

* [演習-メンバ関数の修飾](exercise_q.md#SS_22_3_2)へ戻る。


### 解答例-特殊メンバ関数の削除 <a id="SS_23_3_3"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 81
    // [A]
    // 下記クラスAutoGenのコンパイラが自動生成するメンバ関数を生成しないようにせよ。

    class AutoGen {
    public:
        AutoGen()  = delete;
        ~AutoGen() = delete;

        AutoGen(AutoGen const&)                = delete;
        AutoGen& operator=(AutoGen const&)     = delete;
        AutoGen(AutoGen&&) noexcept            = delete;
        AutoGen& operator=(AutoGen&&) noexcept = delete;
    };
```

* [演習-特殊メンバ関数の削除](exercise_q.md#SS_22_3_3)へ戻る。


### 解答例-委譲コンストラクタ <a id="SS_23_3_4"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 97
    // [A]
    // 下記クラスDelConstructorの2つのコンストラクタのコードクローンをできるだけ排除せよ。

    class DelConstructor {
    public:
        explicit DelConstructor(std::string const& str) : str0_{str + "0"}, str1_{str + "1"}, str2_{str + "2"} {}

        explicit DelConstructor(int32_t num) : DelConstructor{std::to_string(num) + "_"} {}

        std::string const& GetString0() const { return str0_; }
        std::string const& GetString1() const { return str1_; }
        std::string const& GetString2() const { return str2_; }

    private:
        std::string const str0_;
        std::string const str1_;
        std::string const str2_;
    };

    TEST(ProgrammingConventionFuncA, Constructor)
    {
        {
            auto const dc = DelConstructor{"hehe"};

            ASSERT_EQ("hehe0", dc.GetString0());
            ASSERT_EQ("hehe1", dc.GetString1());
            ASSERT_EQ("hehe2", dc.GetString2());
        }
        {
            auto const dc = DelConstructor{123};

            ASSERT_EQ("123_0", dc.GetString0());
            ASSERT_EQ("123_1", dc.GetString1());
            ASSERT_EQ("123_2", dc.GetString2());
        }
    }
```

* [演習-委譲コンストラクタ](exercise_q.md#SS_22_3_4)へ戻る。


### 解答例-copyコンストラクタ <a id="SS_23_3_5"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 136
    // [A]
    // 下記クラスIngeter、IntegerHolderに適切にcopyコンストラクタ、copy代入演算子を追加して、
    // 単体テストを行え。
    class Integer {
    public:
        explicit Integer(int32_t i) noexcept : i_{i} {}

        Integer(Integer const& rhs) noexcept = default;

        Integer& operator=(Integer const& rhs) noexcept = default;

        int32_t GetValue() const noexcept { return i_; }

    private:
        int32_t i_;
    };

    class IntegerHolder {
    public:
        explicit IntegerHolder(int32_t i) : integer_{std::make_unique<Integer>(i)} {}

        IntegerHolder(IntegerHolder const& rhs) : integer_{std::make_unique<Integer>(*rhs.integer_)} {}

        IntegerHolder& operator=(IntegerHolder const& rhs)
        {
            *integer_ = *(rhs.integer_);
            return *this;
        }

        int32_t GetValue() const noexcept { return integer_->GetValue(); }

    private:
        std::unique_ptr<Integer> integer_;
    };

    TEST(ProgrammingConventionFuncA, Constructor2)
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
```

* [演習-copyコンストラクタ](exercise_q.md#SS_22_3_5)へ戻る。


### 解答例-moveコンストラクタ <a id="SS_23_3_6"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 203
    // [A]
    // 上記問題を解決したIntegerHolderにmoveコンストラクタ、move演算子を追加した
    // クラスIntegerHolder2を作成し、単体テストを行え。

    class IntegerHolder2 {
    public:
        explicit IntegerHolder2(int32_t i) : integer_{std::make_unique<Integer>(i)} {}

        IntegerHolder2(IntegerHolder2 const& rhs) : integer_{std::make_unique<Integer>(*rhs.integer_)} {}

        IntegerHolder2(IntegerHolder2&& rhs) noexcept : integer_{std::move(rhs.integer_)} {}

        IntegerHolder2& operator=(IntegerHolder2 const& rhs) noexcept
        {
            *integer_ = *(rhs.integer_);
            return *this;
        }

        IntegerHolder2& operator=(IntegerHolder2&& rhs) noexcept
        {
            integer_ = std::move(rhs.integer_);
            return *this;
        }

        int32_t GetValue() const
        {
            if (!integer_) {
                throw std::bad_exception{};
            }
            return integer_->GetValue();
        }

    private:
        std::unique_ptr<Integer> integer_;
    };

    #ifndef __clang_analyzer__
    TEST(ProgrammingConventionFuncA, Move)
    {
        {
            auto i = IntegerHolder2{3};
            auto j = IntegerHolder2{std::move(i)};

            ASSERT_EQ(3, j.GetValue());

            ASSERT_THROW(i.GetValue(), std::bad_exception);
        }
        {
            auto i = IntegerHolder2{30};
            auto j = IntegerHolder2{0};

            ASSERT_EQ(0, j.GetValue());

            j = std::move(i);

            ASSERT_EQ(30, j.GetValue());

            ASSERT_THROW(i.GetValue(), std::bad_exception);
        }
    }
    #endif
```

* [演習-moveコンストラクタ](exercise_q.md#SS_22_3_6)へ戻る。


### 解答例-関数分割 <a id="SS_23_3_7"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 267
    // [A]
    // 下記PrimeNumbersは引数で与えられた整数以下の素数を返す関数である。
    // PrimeNumbersの単体テストを作成し、その後、行数を短くする等のリファクタリングを行え。

    namespace {
    uint32_t next_prime_num(uint32_t curr_prime_num, std::vector<bool>& is_num_prime) noexcept
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
    }  // namespace

    std::vector<uint32_t> PrimeNumbers(uint32_t max_number)
    {
        auto result = std::vector<uint32_t>{};

        if (max_number < 2) {  // ガード節。2未満の素数はない。
            return result;
        }

        auto prime_num    = 2U;                                       // 最初の素数
        auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない。
        is_num_prime[0] = is_num_prime[1] = false;

        do {
            result.emplace_back(prime_num);
            prime_num = next_prime_num(prime_num, is_num_prime);
        } while (prime_num < is_num_prime.size());

        return result;
    }

    TEST(ProgrammingConventionFuncA, Lines)
    {
        ASSERT_EQ((std::vector<uint32_t>{}), PrimeNumbers(0));
        ASSERT_EQ((std::vector<uint32_t>{}), PrimeNumbers(1));
        ASSERT_EQ((std::vector<uint32_t>{2}), PrimeNumbers(2));
        ASSERT_EQ((std::vector<uint32_t>{2, 3}), PrimeNumbers(3));
        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7}), PrimeNumbers(8));
        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), PrimeNumbers(30));
    }
```

* [演習-関数分割](exercise_q.md#SS_22_3_7)へ戻る。


### 解答-オーバーライド関数の修飾 <a id="SS_23_3_8"></a>
* 選択肢2
* 参照 [オーバーライド](programming_convention.md#SS_3_2_4_7)
* [演習-オーバーライド関数の修飾](exercise_q.md#SS_22_3_8)へ戻る。


### 解答例-オーバーライド/オーバーロード <a id="SS_23_3_9"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 320
    // [A]
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

    TEST(ProgrammingConventionFuncA, Overload)
    {
        auto  b     = Base{};
        auto  d     = Derived{};
        Base& d_ref = d;

        ASSERT_EQ(0, b.f());
        ASSERT_EQ(0, b.g());

        ASSERT_EQ(1, d.f());
        ASSERT_EQ(1, d.g());

        ASSERT_EQ(0, d_ref.f());
        ASSERT_EQ(1, d_ref.g());
    }
```

* [演習-オーバーライド/オーバーロード](exercise_q.md#SS_22_3_9)へ戻る。


### 解答例-オーバーロードによる誤用防止 <a id="SS_23_3_10"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 356
    // [A]
    // 下記関数Squareは、引数が浮動小数点となることを想定していない。
    // 誤用を防ぐために、引数に浮動小数点を指定された場合、コンパイルできないようにせよ。
    int32_t Square(int32_t a) noexcept { return a * a; }
    int32_t Square(double a) noexcept = delete;

    TEST(ProgrammingConventionFuncA, Overload2)
    {
        ASSERT_EQ(9, Square(3));
    #if 0  // int32_t Square(double a) = delete;により下記はコンパイルできない。
        ASSERT_EQ(4, Square(2.5));
    #endif
    }
```

* [演習-オーバーロードによる誤用防止](exercise_q.md#SS_22_3_10)へ戻る。


### 解答例-仮引数の修飾 <a id="SS_23_3_11"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 372
    // [A]
    // 下記AddStringsの仮引数等を適切に修正せよ。
    using Strings = std::list<std::string>;
    Strings AddStrings(Strings const& a, Strings const* b)
    {
        auto ret = a;

        if (b == nullptr) {
            return ret;
        }

        ret.insert(ret.end(), b->begin(), b->end());

        return ret;
    }

    TEST(ProgrammingConventionFuncA, Parameter)
    {
        auto a = Strings{"abc", "d"};
        auto b = Strings{"e", "fgh", "i"};

        auto ret = AddStrings(a, nullptr);
        ASSERT_EQ(ret, (Strings{"abc", "d"}));

        ret = AddStrings(a, &b);
        ASSERT_EQ(ret, (Strings{"abc", "d", "e", "fgh", "i"}));

        ASSERT_EQ(AddStrings(a, nullptr), (Strings{"abc", "d"}));

        ASSERT_EQ(AddStrings(a, &b), (Strings{"abc", "d", "e", "fgh", "i"}));
    }
```

* [演習-仮引数の修飾](exercise_q.md#SS_22_3_11)へ戻る。


### 解答例-constexpr関数 <a id="SS_23_3_12"></a>
```cpp
    //  exercise/programming_convention_a/func.cpp 406
    // [A]
    // 下記Factorialをconstexpr関数にせよ。
    constexpr uint32_t Factorial(uint32_t a) noexcept
    {
        if (a == 0 || a == 1) {
            return 1;
        }

        return Factorial(a - 1) * a;
    }

    TEST(ProgrammingConventionFuncA, ConstexprFunc)
    {
        static_assert(1 == Factorial(0), "Factorial fail");
        ASSERT_EQ(1, Factorial(0));
        ASSERT_EQ(6, Factorial(3));
        ASSERT_EQ(120, Factorial(5));
        ASSERT_EQ(3628800, Factorial(10));
    }
```

* [演習-constexpr関数](exercise_q.md#SS_22_3_12)へ戻る。


### 解答-エクセプションの型 <a id="SS_23_3_13"></a>
* 選択肢2
* 参照 [エクセプション処理](programming_convention.md#SS_3_3_9)
* 解説  
  下記3つを統合して考えれば、必然的に「選択肢2」であることがわかる。
    * エクセプションでthrowされるオブジェクトのポインタがnullptrになることはない。
    * throwされたオブジェクトのスライスは当然避けるべきである。
    * throwされたオブジェクトを直接修正すべきでない。
* [演習-エクセプションの型](exercise_q.md#SS_22_3_13)へ戻る。


## プログラミング規約(構文) <a id="SS_23_4"></a>

### 解答例-コンテナの範囲for文 <a id="SS_23_4_1"></a>
```cpp
    //  exercise/programming_convention_a/syntax.cpp 8
    // [A]
    // 下記Accumlateのfor文を
    //  * イテレータを使ったfor文を使用したAccumlate2
    //  * 範囲for文を使用したAccumlate3
    // を作り、それらの単体テストを行え。また、その時にその他の不具合があれば合わせて修正せよ。

    std::string Accumlate(std::vector<std::string> const& strings) noexcept
    {
        auto ret = std::string{};

        for (auto i = 0U; i < strings.size(); ++i) {
            ret += strings[i];
        }

        return ret;
    }

    std::string Accumlate2(std::vector<std::string> const& strings) noexcept
    {
        auto ret = std::string{};

    #if 0  // old style
        for (std::vector<std::string>::const_iterator it = strings.cbegin(); it != strings.cend(); ++it) {
            ret += *it;
        }
    #else
        for (auto it = strings.cbegin(); it != strings.cend(); ++it) {
            ret += *it;
        }
    #endif

        return ret;
    }

    std::string Accumlate3(std::vector<std::string> const& strings) noexcept
    {
        auto ret = std::string{};

        for (auto const& s : strings) {
            ret += s;
        }

        return ret;
    }

    TEST(ProgrammingConventionSyntaxA, RangeFor)
    {
        ASSERT_EQ("abcd", Accumlate(std::vector<std::string>{"a", "b", "cd"}));
        ASSERT_EQ("ABCD", Accumlate2(std::vector<std::string>{"A", "B", "CD"}));
        ASSERT_EQ("AbCd", Accumlate3(std::vector<std::string>{"A", "b", "Cd"}));
    }
```

* [演習-コンテナの範囲for文](exercise_q.md#SS_22_4_1)へ戻る。


### 解答例-ラムダ式 <a id="SS_23_4_2"></a>
```cpp
    //  exercise/programming_convention_a/syntax.cpp 62
    // [A]
    // 下記のcopy_ifの第4引数をラムダ式を使って書き直せ。

    TEST(ProgrammingConventionSyntaxA, Lambda)
    {
        auto data = std::vector<std::string>{"", "abc", "", "d"};

        auto ret = std::vector<std::string>{};

        std::copy_if(data.cbegin(), data.cend(), std::back_inserter(ret),
                     [](auto const& s) noexcept { return s.size() != 0; });
        ASSERT_EQ((std::vector<std::string>{"abc", "d"}), ret);
    }
```

* [演習-ラムダ式](exercise_q.md#SS_22_4_2)へ戻る。


### 解答例-ラムダ式のキャプチャ <a id="SS_23_4_3"></a>
```cpp
    //  exercise/programming_convention_a/syntax.cpp 78
    // [A]
    // 下記Lambda::GetNameLessThan()のラムダ式の問題点を修正し、単体テストを行え。
    class Lambda {
    public:
        explicit Lambda(std::vector<std::string>&& strs) : strs_{std::move(strs)} {}
        std::vector<std::string> GetNameLessThan(uint32_t length) const
        {
            auto ret = std::vector<std::string>{};

            std::copy_if(strs_.cbegin(), strs_.cend(), std::back_inserter(ret),
                         [length = length](auto const& str) noexcept { return (str.size() < length); });

            return ret;
        }

    private:
        std::vector<std::string> strs_;
    };

    TEST(ProgrammingConventionSyntaxA, Lambda2)
    {
        auto lambda = Lambda{{"abc", "abcdef", "a"}};

        ASSERT_EQ(lambda.GetNameLessThan(4), (std::vector<std::string>{"abc", "a"}));
        ASSERT_EQ(lambda.GetNameLessThan(2), (std::vector<std::string>{"a"}));
        ASSERT_EQ(lambda.GetNameLessThan(1), (std::vector<std::string>{}));
    }
```

* [演習-ラムダ式のキャプチャ](exercise_q.md#SS_22_4_3)へ戻る。


## プログラミング規約(演算子) <a id="SS_23_5"></a>

### 解答例-条件演算子 <a id="SS_23_5_1"></a>
```cpp
    //  exercise/programming_convention_a/operator.cpp 8
    // [A]
    // 下記whichのif文を三項演算子を使用して書き直せ。
    int32_t which(bool left, int32_t lhs, int32_t rhs) noexcept { return left ? lhs : rhs; }

    TEST(ProgrammingConventionOperatorA, OoOperator)
    {
        ASSERT_EQ(3, which(true, 3, 4));
        ASSERT_EQ(4, which(false, 3, 4));
    }
```

* [演習-条件演算子](exercise_q.md#SS_22_5_1)へ戻る。

### 解答例-delete <a id="SS_23_5_2"></a>
```cpp
    //  exercise/programming_convention_a/operator.cpp 20
    // [A]
    // 下記DeleteProblemのメモリ管理の問題を修正せよ。
    // また、他の問題があれば、合わせて修正せよ。
    class DeleteProblem {
    public:
        DeleteProblem(char const* str0 = nullptr, char const* str1 = nullptr)
            : str0_{(str0 == nullptr) ? std::unique_ptr<std::string>{} : std::make_unique<std::string>(str0)},
              str1_{(str1 == nullptr) ? std::unique_ptr<std::string>{} : std::make_unique<std::string>(str1)}
        {
        }

        DeleteProblem(DeleteProblem const&)            = delete;
        DeleteProblem& operator=(DeleteProblem const&) = delete;

        std::string const* GetStr0() const noexcept { return str0_.get(); }
        std::string const* GetStr1() const noexcept { return str1_.get(); }

    private:
        std::unique_ptr<std::string> str0_;
        std::unique_ptr<std::string> str1_;
    };

    TEST(ProgrammingConventionOperatorA, Delete)
    {
        {
            auto const dp = DeleteProblem{};

            ASSERT_EQ(nullptr, dp.GetStr0());
            ASSERT_EQ(nullptr, dp.GetStr1());
        }
        {
            auto const dp = DeleteProblem{"abc"};

            ASSERT_EQ("abc", *dp.GetStr0());
            ASSERT_EQ(nullptr, dp.GetStr1());
        }
        {
            auto const dp = DeleteProblem{"abc", "de"};

            ASSERT_EQ("abc", *dp.GetStr0());
            ASSERT_EQ("de", *dp.GetStr1());
        }
    }
```

* [演習-delete](exercise_q.md#SS_22_5_2)へ戻る。

### 解答例-sizeof <a id="SS_23_5_3"></a>
```cpp
    //  exercise/programming_convention_a/operator.cpp 69
    // [A]
    // 下記Size1() - Size4()の単体テストを作れ。
    size_t Size0(int32_t a) noexcept { return sizeof(a); }

    size_t Size1(int32_t a[10]) noexcept { return sizeof(a); }

    size_t Size2(int32_t a[]) noexcept { return sizeof(a); }

    size_t Size3(int32_t* a) noexcept { return sizeof(a); }

    size_t Size4(int32_t (&a)[10]) noexcept { return sizeof(a); }

    TEST(ProgrammingConventionOperatorA, Sizeof)
    {
        int32_t array[10]{};

        ASSERT_EQ(4, Size0(array[0]));
        ASSERT_EQ(sizeof(void*), Size1(array));
        ASSERT_EQ(sizeof(void*), Size2(array));
        ASSERT_EQ(sizeof(void*), Size3(array));
        ASSERT_EQ(sizeof(int32_t) * 10, Size4(array));
    }
```

* [演習-sizeof](exercise_q.md#SS_22_5_3)へ戻る。


### 解答例-dynamic_castの削除 <a id="SS_23_5_4"></a>
```cpp
    //  exercise/programming_convention_a/operator.cpp 95
    // [A]
    // 下記クラスX、Y、ZとGetNameをdynamic_castを使わずに書き直せ。

    class X {
    public:
        virtual std::string GetName() const { return "X"; }

        virtual ~X() = default;
    };

    class Y : public X {
    public:
        virtual std::string GetName() const override { return "Y"; }
    };

    class Z : public X {
    public:
        virtual std::string GetName() const override { return "Z"; }
    };

    std::string GetName(X const& x) { return x.GetName(); }

    TEST(ProgrammingConventionOperatorA, Cast)
    {
        auto x = X{};
        auto y = Y{};
        auto z = Z{};

        ASSERT_EQ("X", GetName(x));
        ASSERT_EQ("Y", GetName(y));
        ASSERT_EQ("Z", GetName(z));
    }
```

* [演習-dynamic_castの削除](exercise_q.md#SS_22_5_4)へ戻る。


### 解答-キャスト <a id="SS_23_5_5"></a>
* 選択肢3  
* 参照 [キャスト、暗黙の型変換](programming_convention.md#SS_3_5_10)
* 解説  
  reinterpret_castも避けるべきであるが、組み込みソフト等でのハードウエアアドレスの記述等には、
  使わざるを得ない。
* [演習-キャスト](exercise_q.md#SS_22_5_5)へ戻る。


## プログラミング規約(スコープ) <a id="SS_23_6"></a>

### 解答-usingディレクティブ <a id="SS_23_6_1"></a>
* 選択肢1
* 参照 [using宣言/usingディレクティブ](programming_convention.md#SS_3_8_3)
* [演習-usingディレクティブ](exercise_q.md#SS_22_6_1)へ戻る。


## プログラミング規約(その他) <a id="SS_23_7"></a>

### 解答-アサーションの選択 <a id="SS_23_7_1"></a>
* 選択肢1
* 参照 [assertion](programming_convention.md#SS_3_11_1)
* [演習-アサーションの選択](exercise_q.md#SS_22_7_1)へ戻る。


### 解答例-assert/static_assert <a id="SS_23_7_2"></a>
```cpp
    //  exercise/programming_convention_a/etc.cpp 10
    // [A]
    // 下記FloatingPointは、Tが浮動小数点型、Tのインスタンスは非０であることを前提としている。
    // 適切にアサーションを挿入して誤用を防げ。

    template <typename T>
    class FloatingPoint {
    public:
        static_assert(std::is_floating_point_v<T>, "T must be floating point type");
        FloatingPoint(T num) noexcept : num_{num} { assert(num != 0); }

        T Get() const noexcept { return num_; }
        T Reciprocal() const noexcept { return 1 / num_; }

    private:
        T const num_;
    };

    TEST(ProgrammingConventionFuncA_Opt, Assertion)
    {
        auto f1 = FloatingPoint<float>{1.0F};
        auto d1 = FloatingPoint<double>{1.0};

        ASSERT_EQ(f1.Get(), 1.0F);
        ASSERT_EQ(d1.Get(), 1.0);
        ASSERT_DEATH(FloatingPoint<float>{0}, "num != 0");
        ASSERT_DEATH(FloatingPoint<double>{0}, "num != 0");

    #if 0  // コンパイルできない。
        auto i = FloatingPoint<int32_t>{1};
    #endif
    }
```

* [演習-assert/static_assert](exercise_q.md#SS_22_7_2)へ戻る。


## SOLID <a id="SS_23_8"></a>
### 解答例-SRP <a id="SS_23_8_1"></a>
```cpp
    //  exercise/solid_a/srp_test_score.h 8
    // [A]
    // 下記クラスTestScoreはメンバにする必要のない関数までメンバにしてるため、
    // インターフェースが肥大化してしまい、少なくともSRPに反している。
    // メンバにする必要のないStoreCSVを外部関数にせよ。
    // また、受験者の平均点を求める
    //      TestScore::ScoreOne_t Average(TestScore const& test_score);
    // を同様の方法で作り、単体テストを行え。

    class TestScore {
    public:
        // ...

        // void StoreCSV(std::string const& filename) const;
        // は外部関数にした。
        void LoadCSV(std::string const& filename);

        // ...
    };

    std::string           ToString(TestScore const& ts);
    void                  StoreCSV(TestScore const& test_score, std::string const& filename);
    TestScore::ScoreOne_t Average(TestScore const& test_score);
```
```cpp
    //  exercise/solid_a/srp_test_score.cpp 10

    namespace {

    // ...

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

    // ...

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
    //  exercise/solid_a/srp_test_score_ut.cpp 13

    namespace {

    // ...

    TEST_F(SolidSRP_A, TestScore_StoreCSV)
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

    TEST_F(SolidSRP_A, TestScore_Average)
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

* [演習-SRP](exercise_q.md#SS_22_8_1)へ戻る。


### 解答例-OCP <a id="SS_23_8_2"></a>
```cpp
    //  exercise/solid_a/ocp_test_score.h 8
    // [A]
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
        TestScore& operator=(TestScore&&)      = default;  // moveが必要になった

        // ...

        // void LoadCSV(std::string const& filename);
        // は外部関数にした。

        ScoreAll_t::const_iterator begin() const noexcept { return test_score_row_.begin(); }
        ScoreAll_t::const_iterator end() const noexcept { return test_score_row_.end(); }

    private:
        // int32_t score: 0～100はスコア、-1は未受験、それ以外は不正データ
        void       validate_score(int32_t score) const;
        ScoreAll_t test_score_row_{};
    };

    std::string           ToString(TestScore const& ts);
    void                  LoadCSV(std::string const& filename, TestScore& test_score);
    void                  StoreCSV(TestScore const& test_score, std::string const& filename);
    TestScore::ScoreOne_t Average(TestScore const& test_score);
```
```cpp
    //  exercise/solid_a/ocp_test_score.cpp 10

    // ...

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
    //  exercise/solid_a/ocp_test_score_ut.cpp 13

    namespace {

    TEST_F(SolidOCP_A, TestScore_LoadCSV)
    {
        auto ts = TestScore{};
        LoadCSV(test_score_org_, ts);

        // ...
    }

    // ...

    TEST_F(SolidOCP_A, TestScore_AddScore)
    {
        auto ts = TestScore{};
        LoadCSV(test_score_org_, ts);

        // ...
    }

    TEST_F(SolidOCP_A, TestScore_GetScore)
    {
        auto ts = TestScore{};
        LoadCSV(test_score_org_, ts);

        // ...
    }

    TEST_F(SolidOCP_A, TestScore_StoreCSV)
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

    TEST_F(SolidOCP_A, TestScore_Average)
    {
        auto ts = TestScore{};
        LoadCSV(test_score_org_, ts);

        // ...
    }
    }  // namespace
```

* [演習-OCP](exercise_q.md#SS_22_8_2)へ戻る。


### 解答例-LSP <a id="SS_23_8_3"></a>
```cpp
    //  exercise/solid_a/lsp_test_score.h 8
    // [A]
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
    // [A]
    // 上記問題を解決するため、クラスTestScoreForceFixedを作り単体テストを行え。
    //
    // [解説]
    // TestScoreForceFixedをTestScoreからprivate継承することで、
    // TestScoreForceFixedとTestScorの関係がis-aの関係ではなくなるためLSPに適合する。
    // 一方で、private継承の影響で、TestScoreForceFixedは、
    //      * void LoadCSV(std::string const& filename, TestScore& test_score);
    //      * void StoreCSV(TestScore const& test_score, std::string const& filename);
    // 等TestScoreオブジェクトのリファレンスやポインタを受け取る関数が使えなくなる
    // (そもそもそれが目的でprivate継承にした)。
    // これに対処するために、オリジナルのコードをほとんどクローンした
    //      * void LoadCSV(std::string const& filename, TestScoreForceFixed& test_score);
    //      * void StoreCSV(TestScoreForceFixed const& test_score, std::string const& filename);
    // を作ることは当然、誤りである。
    // クローンを作らずに対処するためのコードを単体テストに記述したので参照してほしい。
    // また、TestScoreForceを作ったことが根本的な誤りであった可能性もある。
    // 「未受講データ-1を入力された場合、それをテストスコア0と解釈する」ようなオプションを
    // TestScoreに持たせることも考慮すべきであった。

    class TestScore {
        // ...
    };

    class TestScoreForce : public TestScore {
        // ...
    };

    class TestScoreForceFixed : TestScore {
    public:
        TestScoreForceFixed()                                      = default;
        virtual ~TestScoreForceFixed()                             = default;
        TestScoreForceFixed(TestScoreForceFixed const&)            = default;
        TestScoreForceFixed& operator=(TestScoreForceFixed const&) = delete;
        TestScoreForceFixed& operator=(TestScoreForceFixed&&)      = default;

        using ScoreAll_t = TestScore::ScoreAll_t;
        using ScoreOne_t = TestScore::ScoreOne_t;

        using TestScore::AddScore;
        using TestScore::GetScore;

        using TestScore::begin;
        using TestScore::end;

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
    //  exercise/solid_a/lsp_test_score.cpp 10

    // ...

    void TestScoreForceFixed::validate_score(int32_t score) const
    {
        if (is_valid_score(score)) {
            return;
        }

        throw std::out_of_range{"Invalid Score"};
    }

    // ...
```
```cpp
    //  exercise/solid_a/lsp_test_score_ut.cpp 15

    namespace {

    // ...

    // [A]
    // ファイルtest_score_org_には、TestScoreForceの不正値が含まれているため、
    // 下記の単体テストでの、
    //      LoadCSV(test_score_org_, ts_f);
    // はエクセプションが発生するべきだが、実際にはパスしてしまう。
    // 一方で、エクセプションが発生するようにLoadCSVを変更するには、LoadCVSの第2引数の
    // ランタイム時の実際の型が必要になってしまうため、この解決手段にも問題がある。

    TEST_F(SolidLSP_A, TestScoreForce_LoadCSV)
    {
        auto ts_f = TestScoreForce{};
        LoadCSV(test_score_org_, ts_f);  // 本来はエクセプションが発生すべき。

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {-1, 50, 80}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
        };

        ASSERT_TRUE(std::equal(ts_f.begin(), ts_f.end(), exp.begin()));

        auto const one_score = TestScore::ScoreOne_t{
            TestScore::ScoreOne_t::value_type("堂林", 50),  TestScore::ScoreOne_t::value_type("広輔", 40),
            TestScore::ScoreOne_t::value_type("會澤", 70),  TestScore::ScoreOne_t::value_type("松山", 1),
            TestScore::ScoreOne_t::value_type("菊池", -1),  TestScore::ScoreOne_t::value_type("鈴木", 5),
            TestScore::ScoreOne_t::value_type("田中", 100), TestScore::ScoreOne_t::value_type("西川", 90),
        };
    }

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

    template <typename TEST_SCORE>
    TEST_SCORE LoadCSV(std::string const& filename)
    {
        static_assert(std::is_same_v<TEST_SCORE, TestScore> || std::is_same_v<TEST_SCORE, TestScoreForceFixed>);

        auto data = std::ifstream{filename};

        typename TEST_SCORE::ScoreAll_t test_score_raw;
        auto                            line = std::string{};
        while (std::getline(data, line)) {
            // std::pair<TestScore::ScoreAll_t::iterator, bool>
            auto ret = test_score_raw.insert(parse_line(line));
            assert(ret.second);
        }

        typename TEST_SCORE::ScoreOne_t one_test;
        for (auto const& pair : test_score_raw) {
            one_test.emplace_back(std::make_pair(pair.first, 0));
        }

        auto const score_count = test_score_raw.begin()->second.size();
        auto       ts          = TEST_SCORE{};

        for (auto i = 0U; i < score_count; ++i) {
            for (auto& pair : one_test) {
                pair.second = test_score_raw[pair.first][i];
            }
            ts.AddScore(one_test);
        }

        return ts;
    }

    TEST_F(SolidLSP_A, TestScoreForceFixed_LoadCSV)
    {
        // 下で使用しているLoadCSVはtemplateで実装し直したもの(上記templace <>LoadCSV)。
        // 従来のLoadCSVでは型違いでコンパイルできない。
        // また、従来のLoadCSVは第2引数をTestScore&をしたため、
        // ここで指摘したような問題を引き起こしやすい。この問題を解決するため、
        // templace <>LoadCSVは引数での値戻しをやめ、リターンでの値戻しに改めた。
        ASSERT_THROW(LoadCSV<TestScoreForceFixed>(test_score_org_), std::out_of_range);

        TestScoreForceFixed ts_f_f = LoadCSV<TestScoreForceFixed>(test_score_org_f_);

        auto const exp = TestScore::ScoreAll_t{
            TestScore::ScoreAll_t::value_type("堂林", {0, 50, 80}),
            TestScore::ScoreAll_t::value_type("広輔", {40, 30, 10}),
            TestScore::ScoreAll_t::value_type("會澤", {30, 60, 70}),
            TestScore::ScoreAll_t::value_type("松山", {80, 90, 50}),
            TestScore::ScoreAll_t::value_type("菊池", {50, 20, 80}),
            TestScore::ScoreAll_t::value_type("鈴木", {0, 80, 100}),
        };

        ASSERT_TRUE(std::equal(ts_f_f.begin(), ts_f_f.end(), exp.begin()));
    }
    }  // namespace
```

* [演習-LSP](exercise_q.md#SS_22_8_3)へ戻る。


### 解答例-ISP <a id="SS_23_8_4"></a>
```cpp
    //  exercise/solid_a/isp_test_score_average.h 8
    // [A]
    // 下記クラスTestScoreの管理データの内、受験者とその平均スコア、
    // 平均スコアの高い順でソートされた受験者リストを扱うクラスが必要になったため、
    // 下記のようにイミュータブルなクラスTestScoreAverageを作成した。
    //
    // 現在のファイル構成では、TestScoreAverageのみを使うクラスや関数にも、
    // このファイル全体への依存を強いる(つまり、TestScoreやLoadCSV等に依存させる)ため、
    // ISPに反する。
    // TestScoreAverageを使うクラスや関数に余計な依存関係が発生しないようにリファクタリングを
    // 行え。

    // [解説]
    // TestScoreAverageの宣言・定義をsolid_isp_test_score_a.hからこのファイルに移動し、
    // TestScoreAverageのTestScore依存部分をTestScoreAverageDataで隠蔽することで、
    // このファイルからのsolid_isp_test_score_a.hの依存を消した。
    // また、TestScoreAverageのTestScore依存部はすべてsolid_isp_test_score_average_a.cppに移動した。
    // これにより、TestScoreAverageの利用者はTestScoreに依存しなくなった。
    //

    class TestScoreAverage {
    public:
        explicit TestScoreAverage(std::string const& filename);
        ~TestScoreAverage();
        uint32_t                        GetAverage(std::string const& name) const;
        std::vector<std::string> const& DescendingOrder() const;

    private:
        struct TestScoreAverageData;
        std::unique_ptr<TestScoreAverageData> const data_;
    };
```
```cpp
    //  exercise/solid_a/isp_test_score.h 8

    class TestScore {
        // ...
    };

    std::string           ToString(TestScore const& ts);
    TestScore             LoadCSV(std::string const& filename);
    void                  StoreCSV(TestScore const& test_score, std::string const& filename);
    TestScore::ScoreOne_t Average(TestScore const& test_score);
```
```cpp
    //  exercise/solid_a/isp_test_score_average.cpp 10

    namespace {

    TestScore::ScoreOne_t get_average(std::string const& filename)
    {
        TestScore ts = LoadCSV(filename);

        return Average(ts);
    }
    }  // namespace

    struct TestScoreAverage::TestScoreAverageData {
        TestScoreAverageData(TestScore::ScoreOne_t&& average) : average{std::move(average)} {}

        TestScore::ScoreOne_t const average;
        std::vector<std::string>    desending_order{};
    };

    TestScoreAverage::TestScoreAverage(std::string const& filename)
        : data_{std::make_unique<TestScoreAverage::TestScoreAverageData>(get_average(filename))}
    {
    }

    TestScoreAverage::~TestScoreAverage() = default;  // これはヘッダには書けない

    uint32_t TestScoreAverage::GetAverage(std::string const& name) const
    {
        auto pos
            = std::find_if(data_->average.cbegin(), data_->average.cend(),
                           [&name](std::pair<std::string, int32_t> const& pair) noexcept { return name == pair.first; });

        if (pos == data_->average.cend()) {
            throw std::out_of_range{"no member"};
        }

        return pos->second;
    }

    std::vector<std::string> const& TestScoreAverage::DescendingOrder() const
    {
        if (data_->desending_order.size() != 0) {
            return data_->desending_order;
        }

        auto ave = data_->average;
        std::sort(ave.begin(), ave.end(), [](std::pair<std::string, int32_t> const& lhs, auto const& rhs) noexcept {
            return lhs.second > rhs.second;
        });

        for (auto& pair : ave) {
            data_->desending_order.emplace_back(std::move(pair.first));
        }

        return data_->desending_order;
    }
```
```cpp
    //  exercise/solid_a/isp_test_score.cpp 10

    // 演習コードと同一であるため省略
    // ...

```
```cpp
    //  exercise/solid_a/isp_test_score_average_ut.cpp 13

    namespace {

    TEST_F(SolidISP_A, TestScoreAverage)
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
```cpp
    //  exercise/solid_a/isp_test_score_ut.cpp 13

    // 演習コードと同一であるため省略
    // ...

```

* [演習-ISP](exercise_q.md#SS_22_8_4)へ戻る。


### 解答例-DIP <a id="SS_23_8_5"></a>
```cpp
    //  exercise/solid_a/dip_test_score.h 9
    // [A]
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

    // [解説]
    // TestScoreLoaderを「TestScoreClientへの依存」から「TestScoreClientIFへの依存」に変更し、
    // TestScoreClientIFをTestScoreLoaderと同じファイル(このファイル)で宣言・定義したことにより、
    //      * TestScoreLoader -> TestScoreClient
    // の依存関係は解消された。
    // TestScoreClientは、TestScoreClientIFを継承することでTestScoreLoaderのサービスを使用できる。
    // この依存関係は、
    //      * TestScoreClient -> TestScoreClientIF
    // であり、クライアントからサーバへの依存であるため問題にならない。

    class TestScore {
        // ...
    };

    // ...

    class TestScoreClientIF {
    public:
        TestScoreClientIF()          = default;
        virtual ~TestScoreClientIF() = default;
        virtual void Done()          = 0;
    };

    class TestScoreLoader {
    public:
        TestScoreLoader() {}
        ~TestScoreLoader();
        void      LoadCSV_Async(std::string&& filename, TestScoreClientIF& client);
        TestScore LoadCSV_Get() { return future_.get(); }

    private:
        std::future<TestScore> future_{};
    };
```
```cpp
    //  exercise/solid_a/dip_test_score.cpp 10

    // ...

    void TestScoreLoader::LoadCSV_Async(std::string&& filename, TestScoreClientIF& client)
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
    //  exercise/solid_a/dip_test_score_ut.cpp 13

    // 演習コードと同一であるため省略
    // ...

```
```cpp
    //  exercise/solid_a/dip_test_score_client.h 11

    class TestScoreClient : public TestScoreClientIF {
    public:
        void             LoadAsync(std::string&& filename);
        virtual void     Done() override;
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
    //  exercise/solid_a/dip_test_score_client.cpp 5

    // 演習コードと同一であるため省略
    // ...

```
```cpp
    //  exercise/solid_a/dip_test_score_client_ut.cpp 9

    // 演習コードと同一であるため省略
    // ...

```

* [演習-DIP](exercise_q.md#SS_22_8_5)へ戻る。


### 解答-SOLIDの定義 <a id="SS_23_8_6"></a>
* 選択肢対応
    * SRP - 1
    * OCP - 2
    * LIP - 3
    * ISP - 4
    * DIP - 5

* 参照 [SOLID](solid.md#SS_8)
* [演習-SOLIDの定義](exercise_q.md#SS_22_8_6)へ戻る。


## デザインパターン <a id="SS_23_9"></a>
### 解答例-ガード節 <a id="SS_23_9_1"></a>
```cpp
    //  exercise/design_pattern_a/guard.cpp 7
    // [A]
    // 以下の関数PrimeNumbersをガード節や、関数の括りだし等によってリファクタリングせよ。

    inline uint32_t next_prime_num(uint32_t curr_prime_num, std::vector<bool>& is_num_prime) noexcept
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

    inline std::vector<uint32_t> prime_numbers(uint32_t max_number)
    {
        auto result       = std::vector<uint32_t>{};
        auto prime_num    = 2U;                                       // 最初の素数
        auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない
        is_num_prime[0] = is_num_prime[1] = false;

        do {
            result.emplace_back(prime_num);
            prime_num = next_prime_num(prime_num, is_num_prime);
        } while (prime_num < is_num_prime.size());

        return result;
    }

    std::optional<std::vector<uint32_t>> PrimeNumbers(uint32_t max_number)
    {
        if (max_number >= 65536) {  // ガード節。演算コストが高いためエラーにする
            return std::nullopt;
        }

        if (max_number < 2) {  // ガード節。2未満の素数はない
            return std::vector<uint32_t>{};
        }

        return prime_numbers(max_number);
    }

    TEST(DesignPatternA, Guard)
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

* [演習-ガード節](exercise_q.md#SS_22_9_1)へ戻る。


### 解答例-BitmaskType <a id="SS_23_9_2"></a>
```cpp
    //  exercise/design_pattern_a/enum_bitmask.cpp 5
    // [A]
    // 下記関数ColorMask2Strはuint32_t型のビットマスクを引数に取る。
    // これはユーザが使用間違いを起こしやすい脆弱なインターフェースである。
    // enumによるビットマスク表現を使用しこの問題に対処せよ。

    enum class Color : uint32_t {
        RED    = 0b0001,
        YELLOW = 0b0010,
        GREEN  = 0b0100,
        BLUE   = 0b1000,
    };

    constexpr Color operator&(Color x, Color y) noexcept
    {
        return static_cast<Color>(static_cast<uint32_t>(x) & static_cast<uint32_t>(y));
    }

    constexpr Color operator|(Color x, Color y) noexcept
    {
        return static_cast<Color>(static_cast<uint32_t>(x) | static_cast<uint32_t>(y));
    }

    Color& operator&=(Color& x, Color y) noexcept { return x = x & y; }
    Color& operator|=(Color& x, Color y) noexcept { return x = x | y; }

    constexpr bool IsTrue(Color x) noexcept { return static_cast<bool>(x); }

    std::string ColorMask2Str(Color color)
    {
        auto ret = std::string{};

        if (IsTrue(Color::RED & color)) {
            ret += "RED";
        }
        if (IsTrue(Color::YELLOW & color)) {
            if (ret.size() != 0) {
                ret += ',';
            }
            ret += "YELLOW";
        }
        if (IsTrue(Color::GREEN & color)) {
            if (ret.size() != 0) {
                ret += ',';
            }
            ret += "GREEN";
        }
        if (IsTrue(Color::BLUE & color)) {
            if (ret.size() != 0) {
                ret += ',';
            }
            ret += "BLUE";
        }

        return ret;
    }

    TEST(DesignPatternA, EnumBitmask)
    {
        ASSERT_EQ("RED", ColorMask2Str(Color::RED));
        ASSERT_EQ("RED,YELLOW", ColorMask2Str(Color::RED | Color::YELLOW));
        ASSERT_EQ("YELLOW", ColorMask2Str(Color::YELLOW));
        ASSERT_EQ("YELLOW,GREEN,BLUE", ColorMask2Str(Color::YELLOW | Color::GREEN | Color::BLUE));

        auto c = Color::GREEN;
        ASSERT_EQ("GREEN", ColorMask2Str(c));

        c |= Color::RED;
        ASSERT_EQ("RED,GREEN", ColorMask2Str(c));

        c &= Color::RED;
        ASSERT_EQ("RED", ColorMask2Str(c));

    #if 0  // 間違った使い方はコンパイルさせない
        ASSERT_EQ("", ColorMask2Str(0b10000)); // 想定していない使用法
    #endif
    }
```

* [演習-BitmaskType](exercise_q.md#SS_22_9_2)へ戻る。


### 解答例-Pimpl <a id="SS_23_9_3"></a>
```cpp
    //  exercise/design_pattern_a/pimpl.cpp 5
    // [A] 下記クラスCollectionの宣言はクラスWidgetの宣言に依存している。
    // Pimplパターンを使用し、Collectionの宣言がWidgetの宣言に依存しないようにせよ。

    class Widget;
    class Collection {
    public:
        Collection();
        char const* Name(size_t i) const;
        void        AddName(char const* name);
        size_t      Count() const noexcept;

    private:
        class Pimpl;
        std::unique_ptr<Pimpl> pimpl_{};
    };

    TEST(DesignPatternA, Pimpl)
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

    class Widget {
    public:
        explicit Widget(char const* name) : name_{name} {}
        char const* Name() const noexcept { return name_; }

    private:
        char const* name_;
    };

    class Collection::Pimpl {
    public:
        char const* Name(size_t i) const { return widgets_.at(i).Name(); }
        void        AddName(char const* name) { widgets_.emplace_back(name); }

        size_t Count() const noexcept { return widgets_.size(); }

    private:
        std::vector<Widget> widgets_{};
    };

    Collection::Collection() : pimpl_{std::make_unique<Collection::Pimpl>()} {}
    char const* Collection::Name(size_t i) const { return pimpl_->Name(i); }
    void        Collection::AddName(char const* name) { pimpl_->AddName(name); }
    size_t      Collection::Count() const noexcept { return pimpl_->Count(); }
```

* [演習-Pimpl](exercise_q.md#SS_22_9_3)へ戻る。


### 解答-Accessorの副作用 <a id="SS_23_9_4"></a>
* 選択肢1
* 参照 [Accessor](design_pattern.md#SS_9_5)
* [演習-Accessorの副作用](exercise_q.md#SS_22_9_4)へ戻る。


### 解答例-Accessor <a id="SS_23_9_5"></a>
```cpp
    //  exercise/design_pattern_a/accessor.cpp 5
    // [A]
    // 下記クラスPrimeNumbersはAccessorの多用により、クラスのカプセル化が破壊されている例である。
    // これにより、このクラスは凝集性が低く、誤用を誘発しやすい。
    // この問題を解決するため、クラスPrimeNumbersや関数GetPrimeNumbersを修正せよ。
    // また、別の問題があれば合わせて修正せよ。

    // [解説]
    // * Accessorについて
    //      * HasCache、Cashedを廃止。
    //        値(この場合は素数列prime_numbers_)をキャッシュしているかどうかの判断は、
    //        クラスに考えさせるべき。
    //      * SetMaxNumberの変更。
    //        SetMaxNumberで素数列を作っても良いが、一般に重い計算はなるべく遅延実行させた方が良い。
    // * その他の変更について
    //      * GetPrimeNumbersのGeneratePrimeNumbersへの名前変更。
    //        GetXXXはconstメンバ関数にすべきなので。
    //      * コンストラクタやcopy代入演算子等の自動生成関数は、何らかの定義・宣言をした方が良い。
    //      * メンバ変数は必ず初期化する。

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

    inline std::vector<uint32_t> PrimeNumbers::get_prime_numbers(uint32_t max_number)
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

    TEST(DesignPatternA, Accessor)
    {
        auto pm = PrimeNumbers{};

        pm.SetMaxNumber(1);
        ASSERT_EQ((std::vector<uint32_t>{}), pm.GeneratePrimeNumbers());

        pm.SetMaxNumber(3);
        ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm.GeneratePrimeNumbers());

        pm.SetMaxNumber(30);
        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm.GeneratePrimeNumbers());

    #if 0  // このテストパターンは廃止した
        pm.SetMaxNumber(3);
        GeneratePrimeNumbers(pm);  // pm.Cashed(false);しないので前のまま。
                                   // このような用途は考えづらいので、おそらく仕様のバグ。

        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm.GeneratePrimeNumbers());
    #else
        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm.GeneratePrimeNumbers());
    #endif

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

* [演習-Accessor](exercise_q.md#SS_22_9_5)へ戻る。


### 解答例-Copy-And-Swap <a id="SS_23_9_6"></a>
```cpp
    //  exercise/design_pattern_a/copy_and_swap.cpp 5
    // [A]
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

        CopyAndSwap(CopyAndSwap const& rhs) : name0_{rhs.name0_}, name1_{rhs.name1_} {}

        CopyAndSwap(CopyAndSwap&& rhs) noexcept : name0_{std::exchange(rhs.name0_, nullptr)}, name1_{std::move(rhs.name1_)}
        {
        }

        CopyAndSwap& operator=(CopyAndSwap const& rhs)
        {
            if (this == &rhs) {
                return *this;
            }

            // copyコンストラクタの使用
            auto tmp = CopyAndSwap{rhs};  // ここでエクセプションが発生しても、tmp以外、壊れない

            Swap(tmp);

            return *this;
        }

        CopyAndSwap& operator=(CopyAndSwap&& rhs) noexcept
        {
            if (this == &rhs) {
                return *this;
            }

            auto tmp = CopyAndSwap{std::move(rhs)};  // moveコンストラクタ

            Swap(tmp);

            return *this;
        }

        void Swap(CopyAndSwap& rhs) noexcept
        {
            std::swap(name0_, rhs.name0_);
            std::swap(name1_, rhs.name1_);
        }

        char const* GetName0() const noexcept { return name0_; }

        std::string const& GetName1() const noexcept { return name1_; }

        ~CopyAndSwap() = default;

    private:
        char const* name0_;
        std::string name1_;
    };

    #if defined(__clang__)  // clangコンパイルでの警告抑止
    #define SUPPRESS_WARN_CLANG_BEGIN _Pragma("clang diagnostic push")
    #define SUPPRESS_WARN_CLANG_SELF_ASSIGN_OVERLOADED _Pragma("clang diagnostic ignored \"-Wself-assign-overloaded\"")
    #define SUPPRESS_WARN_CLANG_SELF_MOVE _Pragma("clang diagnostic ignored \"-Wself-move\"")
    #define SUPPRESS_WARN_CLANG_END _Pragma("clang diagnostic pop")
    #else
    #define SUPPRESS_WARN_CLANG_BEGIN
    #define SUPPRESS_WARN_CLANG_SELF_ASSIGN_OVERLOADED
    #define SUPPRESS_WARN_CLANG_SELF_MOVE
    #define SUPPRESS_WARN_CLANG_END
    #endif

    // 本来は下記単体テストは分割すべきだが、紙面の都合上一つにまとめる。
    TEST(DesignPatternA, CopyAndSwap)
    {
        // test for explicit CopyAndSwap(char const* name0, char const* name1)
        auto n = CopyAndSwap{nullptr, nullptr};
        ASSERT_STREQ("", n.GetName0());
        ASSERT_EQ("", n.GetName1());

        auto a = CopyAndSwap{"a0", "a1"};
        ASSERT_STREQ("a0", a.GetName0());
        ASSERT_EQ("a1", a.GetName1());

        // test for void Swap(CopyAndSwap& rhs) noexcept
        auto b = CopyAndSwap{"b0", "b1"};

        a.Swap(b);
        ASSERT_STREQ("b0", a.GetName0());
        ASSERT_EQ("b1", a.GetName1());
        ASSERT_STREQ("a0", b.GetName0());
        ASSERT_EQ("a1", b.GetName1());

        a.Swap(a);
        ASSERT_STREQ("b0", a.GetName0());
        ASSERT_EQ("b1", a.GetName1());

        // test for CopyAndSwap(CopyAndSwap const& rhs)
        auto const const_a = CopyAndSwap{"const_a0", "const_a1"};

        auto b_copy = CopyAndSwap{const_a};

        ASSERT_STREQ("const_a0", b_copy.GetName0());
        ASSERT_EQ("const_a1", b_copy.GetName1());

        // test for CopyAndSwap& operator=(CopyAndSwap const& rhs)
        auto const c = CopyAndSwap{"c0", "c1"};

        b_copy = c;
        ASSERT_STREQ("c0", b_copy.GetName0());
        ASSERT_EQ("c1", b_copy.GetName1());

        SUPPRESS_WARN_CLANG_BEGIN;
        SUPPRESS_WARN_CLANG_SELF_ASSIGN_OVERLOADED;

        b_copy = b_copy;

        SUPPRESS_WARN_CLANG_END;

        ASSERT_STREQ("c0", b_copy.GetName0());
        ASSERT_EQ("c1", b_copy.GetName1());

        // test for CopyAndSwap(CopyAndSwap&& rhs) noexcept
        auto b_move = CopyAndSwap{std::move(b)};

        ASSERT_STREQ("a0", b_move.GetName0());
        ASSERT_EQ("a1", b_move.GetName1());

    #if !defined(__clang_analyzer__)  // move後のオブジェクトにリードアクセスするとscan-buildでエラー
        ASSERT_EQ(nullptr, b.GetName0());
        ASSERT_EQ("", b.GetName1());
    #endif

        auto c_move = CopyAndSwap{std::move(const_a)};  // moveに見えるが実はコピー

        ASSERT_STREQ("const_a0", const_a.GetName0());
        ASSERT_EQ("const_a1", const_a.GetName1());

        ASSERT_STREQ("const_a0", c_move.GetName0());
        ASSERT_EQ("const_a1", c_move.GetName1());

        // test for CopyAndSwap& operator=(CopyAndSwap&& rhs) noexcept
        c_move = std::move(b_move);
        ASSERT_STREQ("a0", c_move.GetName0());
        ASSERT_EQ("a1", c_move.GetName1());

    #if !defined(__clang_analyzer__)  // move後のオブジェクトにリードアクセスするとscan-buildでエラー
        ASSERT_EQ(nullptr, b_move.GetName0());
        ASSERT_EQ("", b_move.GetName1());
    #endif

        SUPPRESS_WARN_CLANG_BEGIN;
        SUPPRESS_WARN_CLANG_SELF_MOVE;

        c_move = std::move(c_move);

        SUPPRESS_WARN_CLANG_END;

        ASSERT_STREQ("a0", c_move.GetName0());
        ASSERT_EQ("a1", c_move.GetName1());
    }
```

* [演習-Copy-And-Swap](exercise_q.md#SS_22_9_6)へ戻る。


### 解答例-Immutable <a id="SS_23_9_7"></a>
```cpp
    //  exercise/design_pattern_a/immutable.cpp 5
    // [A]
    // 下記クラスPrimeNumbersはSetMaxNumberにより状態が変わってしまうことがある。
    // 状態変更が必要ない場合、こういった仕様はない方が良い。
    // PrimeNumbersからSetMaxNumberを削除し、このクラスをimmutableにせよ。

    // [解説]
    // * Immutableなクラスとは、生成後状態が変えられないクラスである。
    // * PrimeNumbersをImmutableにするには
    //      * SetMaxNumberを廃止し、メンバ変数をconstにする。
    //      * GeneratePrimeNumbersをconstメンバ関数にして、GetPrimeNumbersに変更する。
    //      * copy代入演算子を =deleteする(これがなくてもconstメンバならばコピーはできないが)

    class PrimeNumbers {
    public:
        explicit PrimeNumbers(uint32_t max_number = 2);

        PrimeNumbers(PrimeNumbers const&)            = default;
        PrimeNumbers& operator=(PrimeNumbers const&) = delete;  // constメンバはコピーできない。

        uint32_t                     GetMaxNumber() const noexcept { return max_number_; }
        std::vector<uint32_t> const& GetPrimeNumbers() const noexcept { return prime_numbers_; }

    private:
        uint32_t const              max_number_;
        std::vector<uint32_t> const prime_numbers_{};

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
        auto result = std::vector<uint32_t>{};

        if (max_number < 2) {  // ガード節。2未満の素数はない。
            return result;
        }

        auto prime_num    = 2U;                                       // 最初の素数
        auto is_num_prime = std::vector<bool>(max_number + 1, true);  // falseなら素数でない。
        is_num_prime[0] = is_num_prime[1] = false;

        do {
            result.emplace_back(prime_num);
            prime_num = next_prime_num(prime_num, is_num_prime);
        } while (prime_num < is_num_prime.size());

        return result;
    }

    PrimeNumbers::PrimeNumbers(uint32_t max_number) : max_number_{max_number}, prime_numbers_{get_prime_numbers(max_number)}
    {
    }

    TEST(DesignPatternA, Immutable)
    {
        auto pm1 = PrimeNumbers{1};
        ASSERT_EQ((std::vector<uint32_t>{}), pm1.GetPrimeNumbers());

        auto pm3 = PrimeNumbers{3};
        ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm3.GetPrimeNumbers());

        auto pm30 = PrimeNumbers{30};
        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm30.GetPrimeNumbers());

        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), pm30.GetPrimeNumbers());

        auto pm3_copy = PrimeNumbers{pm3};
        ASSERT_EQ((std::vector<uint32_t>{2, 3}), pm3_copy.GetPrimeNumbers());

    #if 0  // immutableなのでコピーはできない。
        auto pm  = PrimeNumbers{1};
        auto pm5 = PrimeNumbers{5};
        pm       = pm5;
        ASSERT_EQ((std::vector<uint32_t>{2, 3, 5}), pm.GetPrimeNumbers());
    #endif
    }
```

* [演習-Immutable](exercise_q.md#SS_22_9_7)へ戻る。


### 解答例-Clone <a id="SS_23_9_8"></a>
```cpp
    //  exercise/design_pattern_a/clone.cpp 7
    // [A]
    // TEST(DesignPatternQ, Clone)に記述したように、オブジェクトのスライシングによる影響で、
    // Base型ポインタに代入されたDerivedインスタンスへのコピーは部分的にしか行われない。
    // Cloneパターンを使用してこの問題を修正せよ。
    // また、その他の問題があれば合わせて修正せよ。

    class Base {
    public:
        explicit Base(std::string name) : name1_{std::move(name)} {}
        virtual ~Base() = default;
        virtual std::string const& GetName() const noexcept { return name1_; }

        virtual std::unique_ptr<Base> Clone() const { return std::make_unique<Base>(name1_); }

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

        virtual std::unique_ptr<Base> Clone() const override { return CloneOwn(); }

        std::unique_ptr<Derived> CloneOwn() const { return std::make_unique<Derived>(Base::GetName(), name2_); }

    private:
        std::string name2_;
    };

    TEST(DesignPatternA, Clone)
    {
        Derived d1{"name1", "name2"};

        ASSERT_EQ("name1", d1.Base::GetName());
        ASSERT_EQ("name2", d1.GetName());

        std::unique_ptr<Derived> d2 = d1.CloneOwn();
        ASSERT_EQ("name1", d2->Base::GetName());
        ASSERT_EQ("name2", d2->GetName());

        std::unique_ptr<Base> b3 = d1.Clone();  // コピーの代わりにクローン

        ASSERT_EQ("name1", b3->Base::GetName());
        ASSERT_EQ("name2", b3->GetName());  // ちゃんとコピーされた。
    }
```

* [演習-Clone](exercise_q.md#SS_22_9_8)へ戻る。


### 解答例-NVI <a id="SS_23_9_9"></a>
```cpp
    //  exercise/design_pattern_a/nvi.cpp 7
    // [A]
    // 下記クラスBase、Derived、DerivedDerivedの前処理はクローンコードになっている。
    // NVIを用いて、この問題に対処せよ。

    class Base {
    public:
        explicit Base(std::string name) : name1_{name} {}
        virtual ~Base() = default;
        std::string const& GetName1() const noexcept { return name1_; }

        bool IsEqual(Base const& rhs) const noexcept
        {
            if (this == &rhs) {
                return true;
            }

            if (typeid(*this) != typeid(rhs)) {
                return false;
            }

            return is_equal(rhs);
        }

    protected:
        virtual bool is_equal(Base const& rhs) const noexcept { return name1_ == rhs.name1_; }

    private:
        std::string name1_;
    };

    class Derived : public Base {
    public:
        explicit Derived(std::string name1 = "", std::string name2 = "") : Base{name1}, name2_{name2} {}
        virtual ~Derived() override = default;
        std::string const& GetName2() const noexcept { return name2_; }

    protected:
        virtual bool is_equal(Base const& rhs) const noexcept override
        {
            if (!Base::is_equal(rhs)) {
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

    protected:
        virtual bool is_equal(Base const& rhs) const noexcept override
        {
            if (!Derived::is_equal(rhs)) {
                return false;
            }

            auto rhs_d = dynamic_cast<DerivedDerived const*>(&rhs);

            return (rhs_d != nullptr) && (name3_ == rhs_d->name3_);
        }

    private:
        std::string name3_;
    };

    TEST(DesignPatternA, NVI)
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

* [演習-NVI](exercise_q.md#SS_22_9_9)へ戻る。


### 解答-RAIIの効果 <a id="SS_23_9_10"></a>
* 選択肢1
* 参照 [RAII(scoped guard)](design_pattern.md#SS_9_10)
* [演習-RAIIの効果](exercise_q.md#SS_22_9_10)へ戻る。


### 解答例-RAII <a id="SS_23_9_11"></a>
```cpp
    //  exercise/design_pattern_a/raii.cpp 5
    // [A]
    // 下記クラスBase、Derivedはクローンパターンをしているが、Clone関数はnewしたオブジェクトであるため、
    // メモリーリークを起こしやすい。std::unique_ptrを使用してこの問題に対処せよ。

    class Base {
    public:
        explicit Base(std::string name) : name1_{std::move(name)} {}
        virtual ~Base() = default;
        virtual std::string const& GetName() const noexcept { return name1_; }

        virtual std::unique_ptr<Base> Clone() const { return std::make_unique<Base>(name1_); }

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

        virtual std::unique_ptr<Base> Clone() const override { return CloneOwn(); }

        std::unique_ptr<Derived> CloneOwn() const { return std::make_unique<Derived>(Base::GetName(), name2_); }

    private:
        std::string name2_;
    };

    TEST(DesignPatternA, RAII)
    {
        Derived                  d1{"name1", "name2"};
        std::unique_ptr<Derived> d2{d1.CloneOwn()};

        ASSERT_EQ("name1", d2->Base::GetName());
        ASSERT_EQ("name2", d2->GetName());

        std::unique_ptr<Base> b3 = d1.Clone();

        ASSERT_EQ("name1", b3->Base::GetName());
        ASSERT_EQ("name2", b3->GetName());
    }
```

* [演習-RAII](exercise_q.md#SS_22_9_11)へ戻る。


### 解答例-Future <a id="SS_23_9_12"></a>
```cpp
    //  exercise/design_pattern_a/future.cpp 24
    // [A]
    // 下記のfind_files_concurrentlyはスレッドの出力の結果をキャプチャリファレンスで受け取るため、
    // 入出力の関係が明確でない。Futureパターンを使用しそれを明確にするリファクタリングを行え。

    std::vector<std::string> find_files_concurrently()
    {
        std::future<std::vector<std::string>> result0
            = std::async(std::launch::async, [] { return find_files("../programming_convention_a/"); });

        std::future<std::vector<std::string>> result1
            = std::async(std::launch::async, [] { return find_files("../programming_convention_q/"); });

        auto pca = result0.get();
        auto pcq = result1.get();

        pca.insert(pca.end(), pcq.begin(), pcq.end());

        return pca;
    }

    TEST(DesignPatternA, Future)
    {
        auto files = find_files_concurrently();

        ASSERT_GT(files.size(), 10);
    }
```

* [演習-Future](exercise_q.md#SS_22_9_12)へ戻る。


### 解答例-DI <a id="SS_23_9_13"></a>
```cpp
    //  exercise/design_pattern_a/di.cpp 10
    // [A]
    // CppFilesはLsCppを直に生成するため、LsCpp::FileList()がエラーした場合の単体テスト実施が
    // 困難である。CppFilesにDIパターンを適用するとともに、LsCppを適切に変更することによって、
    // LsCpp::FileList()がエラーした場合のCppFilesの単体テストを行え。

    class LsCpp {
    public:
        virtual ~LsCpp() {}

        std::string const& FileList() { return file_list(); }

    private:
        std::string files_{};

        virtual std::string const& file_list()  // 単体テストのためにvirtual
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
    };

    class CppFiles {
    public:
        explicit CppFiles(std::unique_ptr<LsCpp>&& ls_cpp = std::make_unique<LsCpp>()) : ls_cpp_{std::move(ls_cpp)} {}

        std::vector<std::string> FileList() const
        {
            auto files = std::string{};

            try {
                files = ls_cpp_->FileList();
            }
            catch (...) {
                ;  // 例外発生時には空のベクタを返すので何もしない。
            }

            return split_cr(files);
        }

    private:
        std::unique_ptr<LsCpp> ls_cpp_;

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

    class LsCppError : public LsCpp {
    public:
        LsCppError() noexcept {}
        virtual ~LsCppError() override {}

    private:
        [[noreturn]] virtual std::string const& file_list() override { throw std::exception{}; }
    };

    TEST(DesignPatternA, DI)
    {
        auto        files = CppFiles{};
        auto const& act   = files.FileList();
        auto        exp   = std::vector<std::string>{"../ut_data/a.cpp", "../ut_data/abc.cpp", "../ut_data/efghij.cpp"};

        ASSERT_EQ(exp, act);

        // エラー系のテスト
        auto files2 = CppFiles{std::make_unique<LsCppError>()};

        ASSERT_EQ(0, files2.FileList().size());
    }
```

* [演習-DI](exercise_q.md#SS_22_9_13)へ戻る。


### 解答例-Singleton <a id="SS_23_9_14"></a>
```cpp
    //  exercise/design_pattern_a/singleton.cpp 5
    // [A]
    // 下記AppConfigはアプリケーション全体の設定を管理するためのクラスである。
    // 目的上、そのインスタンスAppConfigは広域のアクセスが必要であり、
    // グローバルインスタンスとして実装している。
    // グローバルインスタンスは、初期化の順番が標準化されておらず、
    // 多くの処理系ではリンクの順番に依存しているため、
    // アプリケーション立ち上げ時に様々な問題を起こすことがある。
    // こういった問題を回避するため、AppConfigをSingleton化せよ。
    // また他の問題があれば合わせて修正せよ。

    // [解説]
    // * AppConfigをSingletonにした。
    //      * インスタンスを返すInst()と同じインスタンスをconst修飾したものを返すInstConst()を追加。
    //      * コンストラクタをprivateにした。
    //      * copyコンストラクタを= deleteした(こうすればmoveコンストラクタも= deleteされる)。
    // * リファクタリング
    //      * BaseColorをスコープドenumにした。
    //      * GetXxxをconst関数にした。
    //      * GetUserNameの戻りをconstリファレンスにした。
    //      * コピー演算子を使用しSetDefaultをシンプルにした。

    class AppConfig {
    public:
        static AppConfig& Inst()
        {
            static auto inst = AppConfig{};

            return inst;
        }

        static AppConfig const& InstConst() { return Inst(); }

        enum class BaseColor { Red, Green, Black };

        void      SetBaseColor(BaseColor color) noexcept { color_ = color; }
        BaseColor GetBaseColor() const noexcept { return color_; }

        void               SetUserName(std::string_view username) { username_ = username; }
        std::string const& GetUserName() const noexcept { return username_; }

        void Logging(bool is_logging) noexcept { is_logging_ = is_logging; }
        bool IsLoggin() const noexcept { return is_logging_; }

        // 他の設定値は省略

        void SetDefault() { *this = AppConfig{}; }

        // これがないとcopyコンストラクタやmoveコンストラクタで別のインスタンスが作れる。
        //    AppConfig app{AppConfig::Inst()};
        //    AppConfig app{std::move(AppConfig::Inst())};
        AppConfig(AppConfig const&) = delete;

    private:
        BaseColor   color_{BaseColor::Red};
        std::string username_{"No Name"};
        bool        is_logging_{false};

        AppConfig()                            = default;
        AppConfig& operator=(AppConfig const&) = default;
    };

    class DesignPatternA_F : public ::testing::Test {
    protected:
        virtual void SetUp() override { AppConfig::Inst().SetDefault(); }

        virtual void TearDown() override { AppConfig::Inst().SetDefault(); }
    };

    TEST_F(DesignPatternA_F, Singleton)
    {
        ASSERT_EQ(AppConfig::BaseColor::Red, AppConfig::InstConst().GetBaseColor());
        ASSERT_EQ("No Name", AppConfig::InstConst().GetUserName());
        ASSERT_FALSE(AppConfig::InstConst().IsLoggin());

        AppConfig::Inst().SetBaseColor(AppConfig::BaseColor::Green);
        ASSERT_EQ(AppConfig::BaseColor::Green, AppConfig::InstConst().GetBaseColor());

        AppConfig::Inst().SetUserName("Stroustrup");
        ASSERT_EQ("Stroustrup", AppConfig::InstConst().GetUserName());

        AppConfig::Inst().Logging(true);
        ASSERT_TRUE(AppConfig::InstConst().IsLoggin());

        AppConfig::Inst().SetDefault();
        ASSERT_EQ(AppConfig::BaseColor::Red, AppConfig::InstConst().GetBaseColor());
        ASSERT_EQ("No Name", AppConfig::InstConst().GetUserName());
        ASSERT_FALSE(AppConfig::InstConst().IsLoggin());
    }
```

* [演習-Singleton](exercise_q.md#SS_22_9_14)へ戻る。


### 解答例-State <a id="SS_23_9_15"></a>
```cpp
    //  exercise/design_pattern_a/state.cpp 5
    // [A]
    // 下記クラスGreetingにはlang_に対する同型のswitch文が3個ある。
    // これは機能追加時にバグが混入しやすいアンチパターンであるため、
    // Stateパターンを用いリファクタリングせよ。
    // また、他の問題があれば合わせて修正せよ。

    enum class Language { English, Japanese, French };

    class GreetingState {
    public:
        virtual ~GreetingState() = default;
        std::string GoodMorning() { return good_morning(); }
        std::string Hello() { return hello(); }
        std::string GoodEvening() { return good_evening(); }

    private:
        virtual std::string good_morning() const = 0;
        virtual std::string hello() const        = 0;
        virtual std::string good_evening() const = 0;
    };

    class GreetingState_English : public GreetingState {
        virtual std::string good_morning() const override { return "good morning"; }
        virtual std::string hello() const override { return "hello"; }
        virtual std::string good_evening() const override { return "good evening"; }
    };

    class GreetingState_Japanese : public GreetingState {
        virtual std::string good_morning() const override { return "おはよう"; }
        virtual std::string hello() const override { return "こんにちは"; }
        virtual std::string good_evening() const override { return "こんばんは"; }
    };

    class GreetingState_French : public GreetingState {
        virtual std::string good_morning() const override { return "Bonjour"; }
        virtual std::string hello() const override { return "Bonjour"; }
        virtual std::string good_evening() const override { return "bonne soirée"; }
    };

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

    TEST(DesignPatternA, State)
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

* [演習-State](exercise_q.md#SS_22_9_15)へ戻る。


### 解答例-Null Object <a id="SS_23_9_16"></a>
```cpp
    //  exercise/design_pattern_a/null_object.cpp 38
    // [A]
    // 下記クラスPersonにはgreeting_のヌルチェックを行う三項演算子が3つある。
    // これはヌルポインタアクセスを起こしやすいアンチパターンであるため、
    // Null Objectパターンを用いリファクタリングせよ。
    // また、他の問題があれば合わせて修正せよ。

    // [解説]
    // * 通常Null Objectパターンは
    //      if(object_ptr != nullptr) { ... }
    //   のようなコードが頻繁に存在する場合にそのコードの繰り返しを無くすためのものであるが、
    //   本例では対象が生のポインタでなくスマートポインタに適用した。
    // * 本例では、GoodMorning等が単純であるためGreetingにNVIを適用していないが、NVIを適用しても良い。
    // * 本例では、ヌルかどうかの同型条件分岐が3個しかないコードにNull Objectパターンを適用した。
    //   例題のためそうしたが、この程度の単純なコードにこのパターンを適用するのはやりすぎである。
    //   この程度のコードクローンであれば一つのヘルパー関数にまとめた方が実践的である。

    class Greeting {
    public:
        explicit Greeting(Language lang = Language::English) : state_{new_state(lang)} {}
        virtual ~Greeting() = default;
        void SetLanguage(Language lang) { state_ = new_state(lang); }

        virtual std::string GoodMorning() const { return state_->GoodMorning(); }
        virtual std::string Hello() const { return state_->Hello(); }
        virtual std::string GoodEvening() const { return state_->GoodEvening(); }

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

    class GreetingSilent : public Greeting {
    public:
        explicit GreetingSilent()          = default;
        virtual ~GreetingSilent() override = default;

        virtual std::string GoodMorning() const override { return ""; }
        virtual std::string Hello() const override { return ""; }
        virtual std::string GoodEvening() const override { return ""; }
    };

    class Person {
    public:
        explicit Person(Language lang, bool silent = false)
            : greeting_{silent ? std::make_unique<GreetingSilent>() : std::make_unique<Greeting>(lang)}
        {
        }

        std::string GoodMorning() const { return greeting_->GoodMorning(); }
        std::string Hello() const { return greeting_->Hello(); }
        std::string GoodEvening() const { return greeting_->GoodEvening(); }

    private:
        std::unique_ptr<Greeting> greeting_;
    };

    TEST(DesignPatternA, NullObject)
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

* [演習-Null Object](exercise_q.md#SS_22_9_16)へ戻る。


### 解答例-Templateメソッド <a id="SS_23_9_17"></a>
```cpp
    //  exercise/design_pattern_a/template_method.cpp 5
    // [A]
    // 下記クラスXxxDataFormatterXml、XxxDataFormatterCsvは同様の処理を行い、
    // それぞれのフォーマットで文字列を出力する。このような処理のクローンはTemplate Method
    // パターンにより排除できる。
    // このパターンを用い、下記2クラスをリファクタリングせよ。
    // また、他の問題があれば合わせて修正せよ。

    // [解説]
    // * Template Methodのインターフェースクラスとして、XxxDataFormatterIFを定義した。
    //      * header()、footer()はstd::stringのリファレンスを返すが、
    //        body()は返すstd::stringが引数に依存して変わるため、実態を返す。
    // * その他の修正
    //      * header_やfooter_はそれぞれのクラスで同じオブジェクトであるため、
    //        static constインスタンスとして、それぞれheader()、footer()の内部で定義した。
    //      * XxxDataFormatterXml、XxxDataFormatterCsvはそれ以上派生する必要がないためfinalとした。

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
            auto ret = std::string{header()};

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
        virtual std::string const& header() const override
        {
            static auto const header = std::string{"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<XxxDataFormatterXml>\n"};

            return header;
        }

        virtual std::string const& footer() const override
        {
            static auto const footer = std::string{"</XxxDataFormatterXml>\n"};

            return footer;
        }

        virtual std::string body(XxxData const& xxx_data) const override
        {
            auto content = std::string{"<Item>\n"};

            content += "    <XxxData a=\"" + std::to_string(xxx_data.a) + "\">\n";
            content += "    <XxxData b=\"" + std::to_string(xxx_data.b) + "\">\n";
            content += "    <XxxData c=\"" + std::to_string(xxx_data.c) + "\">\n";

            return content + "</Itemp>\n";
        }
    };

    class XxxDataFormatterCsv final : public XxxDataFormatterIF {
    public:
        XxxDataFormatterCsv()                   = default;
        virtual ~XxxDataFormatterCsv() override = default;

    private:
        virtual std::string const& header() const override
        {
            static auto const header = std::string{"a, b, c\n"};

            return header;
        }

        virtual std::string const& footer() const override
        {
            static auto const footer = std::string{};

            return footer;
        }

        virtual std::string body(XxxData const& xxx_data) const override
        {
            return std::string{std::to_string(xxx_data.a) + ", " + std::to_string(xxx_data.b) + ", "
                               + std::to_string(xxx_data.b) + "\n"};
        }
    };

    TEST(DesignPatternA, TemplateMethod)
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

* [演習-Templateメソッド](exercise_q.md#SS_22_9_17)へ戻る。


### 解答例-Factory <a id="SS_23_9_18"></a>
```cpp
    //  exercise/design_pattern_a/factory_lib.h 40
    // [A]
    // 下記クラスXxxDataFormatterXml、XxxDataFormatterCsvはヘッダファイルで宣言・定義を行ったために
    // 他の.cppファイルから直接アクセスできてしまう。
    // Factoryパターンを用いて、XxxDataFormatterXml、XxxDataFormatterCsvを他の.cppファイルから
    // 直接アクセスできないようにせよ。

    // [解説]
    // 一般的には、Factory関数は
    //      std::unique_ptr<XxxDataFormatterIF> XxxDataFormatterFactory(XxxDataFormatterType type);
    // のような形状になるが、今回の例では生成オブジェクトの提供するサービスがconst関数のみであるため、
    // constなunique_ptrを返している。
    // また、さらにこの考え方を進め、newしてオブジェクトの生成をする必要はないことに気づけば、
    // XxxDataFormatterFactory2のようにconstリファレンスを返すこともできる。

    enum class XxxDataFormatterType { Xml, Csv };

    std::unique_ptr<XxxDataFormatterIF const> XxxDataFormatterFactory(XxxDataFormatterType type);
    XxxDataFormatterIF const&                 XxxDataFormatterFactory2(XxxDataFormatterType type) noexcept;
```
```cpp
    //  exercise/design_pattern_a/factory_lib.cpp 76

    std::unique_ptr<XxxDataFormatterIF const> XxxDataFormatterFactory(XxxDataFormatterType type)
    {
        switch (type) {
        case XxxDataFormatterType::Xml:
            return std::make_unique<XxxDataFormatterXml>();
        case XxxDataFormatterType::Csv:
            return std::make_unique<XxxDataFormatterCsv>();
        default:
            assert("unknown type");
            return std::unique_ptr<XxxDataFormatterIF const>{};
        }
    }

    XxxDataFormatterIF const& XxxDataFormatterFactory2(XxxDataFormatterType type) noexcept
    {
        static auto const xml = XxxDataFormatterXml{};
        static auto const csv = XxxDataFormatterCsv{};

        switch (type) {
        case XxxDataFormatterType::Xml:
            return xml;
        case XxxDataFormatterType::Csv:
            return csv;
        default:
            assert("unknown type");
            return csv;
        }
    }
```
```cpp
    //  exercise/design_pattern_a/factory.cpp 9

    TEST(DesignPatternA, Factory)
    {
        auto xml = XxxDataFormatterFactory(XxxDataFormatterType::Xml);
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
            auto const actual_scalar = xml->ToString({1, 100, 10});

            ASSERT_EQ(expect_scalar, actual_scalar);
        }

        auto csv = XxxDataFormatterFactory(XxxDataFormatterType::Csv);
        {
            auto const expect_array = std::string{
                "a, b, c\n"
                "1, 100, 100\n"
                "2, 200, 200\n"};
            auto const actual_array = csv->ToString({{1, 100, 10}, {2, 200, 20}});

            ASSERT_EQ(expect_array, actual_array);
        }
    }

    TEST(DesignPatternA, Factory2)
    {
        auto const& xml = XxxDataFormatterFactory2(XxxDataFormatterType::Xml);
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

        auto const& csv = XxxDataFormatterFactory2(XxxDataFormatterType::Csv);
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

* [演習-Factory](exercise_q.md#SS_22_9_18)へ戻る。


### 解答例-Named Constructor <a id="SS_23_9_19"></a>
```cpp
    //  exercise/design_pattern_a/named_constructor_lib.h 14
    // [A]
    // 下記関数XxxDataFormatterFactoryはインターフェースクラスXxxDataFormatterIFのファクトリ関数
    // である。これをnamed constructorパターンで実装しなおせ。

    // [解説]
    // * XxxDataFormatterIFの特性から、Named ConstructorはXxxDataFormatterIFのconstリファレンスを返す
    //   仕様としたが、戻すオブジェクトの特性より戻り値型は以下のようにすべき。
    //
    //      const/非const | 静的/動的 | 戻す型
    //      --------------+-----------+-----------------------------------
    //      const         | 静的      | XxxDataFormatterIFのconstリファレンス
    //                    | 動的      | std::unique_ptr<const XxxDataFormatterIF>
    //      非const       | 静的      | XxxDataFormatterIFのリファレンス
    //                    | 動的      | std::unique_ptr<XxxDataFormatterIF>
    //
    // * FactoryとNamed Constructorはほぼ等価であり、どちらを使っても派生型の隠蔽という効果は等しい。
    // * 筆者は、今回の例のように静的オブジェクトを返す場合、Named Constructor、
    //   動的オブジェクトを返す場合、Factoryを使用している。

    class XxxDataFormatterIF {
    public:
        XxxDataFormatterIF() = default;
        static XxxDataFormatterIF const& Xml() noexcept;
        static XxxDataFormatterIF const& Csv() noexcept;
        static XxxDataFormatterIF const& Table() noexcept;

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
```
```cpp
    //  exercise/design_pattern_a/named_constructor_lib.cpp 112

    XxxDataFormatterIF const& XxxDataFormatterIF::Xml() noexcept
    {
        static auto const inst = XxxDataFormatterXml{};
        return inst;
    }

    XxxDataFormatterIF const& XxxDataFormatterIF::Csv() noexcept
    {
        static auto const inst = XxxDataFormatterCsv{};
        return inst;
    }

    XxxDataFormatterIF const& XxxDataFormatterIF::Table() noexcept
    {
        static auto const inst = XxxDataFormatterTable{};
        return inst;
    }
```
```cpp
    //  exercise/design_pattern_a/named_constructor.cpp 9

    TEST(DesignPatternA, NamedConstructor)
    {
        auto const& xml = XxxDataFormatterIF::Xml();
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

        auto const& csv = XxxDataFormatterIF::Csv();
        {
            auto const expect_array = std::string{
                "a, b, c\n"
                "1, 100, 100\n"
                "2, 200, 200\n"};
            auto const actual_array = csv.ToString({{1, 100, 10}, {2, 200, 20}});

            ASSERT_EQ(expect_array, actual_array);
        }

        auto const& table = XxxDataFormatterIF::Table();
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

* [演習-Named Constructor](exercise_q.md#SS_22_9_19)へ戻る。


### 解答例-Proxy <a id="SS_23_9_20"></a>
```cpp
    //  exercise/design_pattern_a/proxy.cpp 8
    // [A]
    // 下記クラスLsDirのFileListはlsコマンドをpopenにより実行し、その戻り値をstd::stringで返す。
    // popenはコストの高いコールなので、パフォーマンスを上げるためにlsの戻り値をキャッシュしたいが、
    // 現行のLsDirも必要である。
    // Proxyパターンを使い、この問題に対処するためのLsDirCachedを作れ。

    #define USE_ACCURATE_PROXY
    #ifdef USE_ACCURATE_PROXY  // 本来#ifdefは問題を発生させるため使うべきではないが、例なので。
    class LsDirIF {
    public:
        LsDirIF()          = default;
        virtual ~LsDirIF() = default;

        void               SetArgs(std::string_view args) { args_ = args; }
        std::string const& GetArgs() const noexcept { return args_; }
        std::string const  FileList() const { return file_list(); }

    private:
        std::string         args_{};
        virtual std::string file_list() const = 0;
    };

    class LsDir : public LsDirIF {
    public:
        LsDir()          = default;
        virtual ~LsDir() = default;

    private:
        virtual std::string file_list() const override
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
    };

    class LsDirCached : public LsDirIF {
    public:
        LsDirCached()                   = default;
        virtual ~LsDirCached() override = default;

    private:
        mutable std::string latest_ls_{};
        mutable LsDir       ld_no_cache_{};

        virtual std::string file_list() const override
        {
            if (GetArgs() == ld_no_cache_.GetArgs()) {
                return latest_ls_;
            }

            ld_no_cache_.SetArgs(GetArgs());
            latest_ls_ = ld_no_cache_.FileList();

            return latest_ls_;
        }
    };
    #else  // not USE_ACCURATE_PROXY
    class LsDir {
    public:
        LsDir()          = default;
        virtual ~LsDir() = default;

        void               SetArgs(std::string_view args) { args_ = args; }
        std::string const& GetArgs() const { return args_; }
        std::string const  FileList() const { return file_list(); }

    protected:
        virtual std::string file_list() const
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

    class LsDirCached : public LsDir {
    public:
        LsDirCached()                   = default;
        virtual ~LsDirCached() override = default;

    protected:
        virtual std::string file_list() const override
        {
            if (GetArgs() == latest_args_) {
                return latest_ls_;
            }

            latest_args_ = GetArgs();
            latest_ls_   = LsDir::file_list();

            return latest_ls_;
        }

    private:
        mutable std::string latest_ls_{};
        mutable std::string latest_args_{};
    };
    #endif

    TEST(DesignPatternA, Proxy)
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

    TEST(DesignPatternA, Proxy2)
    {
        auto ld = LsDirCached{};

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

    template <typename LSDIR>
    uint32_t measure_performance(LSDIR const& ls_dir, uint32_t count) noexcept
    {
        auto const start = std::chrono::system_clock::now();
        {
            for (decltype(count) i = 0; i < count; ++i) {
                volatile auto const list = ls_dir.FileList();
            }
        }

        auto const stop = std::chrono::system_clock::now();

        return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    }

    TEST(DesignPatternA, ProxyPerformance)
    {
        auto ld               = LsDir{};
        auto elapsed_no_cache = uint32_t{measure_performance(ld, 10)};
        std::cout << "No Cache Elapse:" << elapsed_no_cache << " usec" << std::endl;

        auto ldc           = LsDirCached{};
        auto elapsed_cache = uint32_t{measure_performance(ldc, 10)};
        std::cout << "Cached Elapse:" << elapsed_cache << " usec" << std::endl;

        ASSERT_LT(30 * elapsed_cache, elapsed_no_cache);  // 30倍に理由はない。
    }
```

* [演習-Proxy](exercise_q.md#SS_22_9_20)へ戻る。


### 解答例-Strategy <a id="SS_23_9_21"></a>
```cpp
    //  exercise/design_pattern_a/strategy.cpp 12
    // [A]
    // 下記find_filesは醜悪であるだけでなく、拡張性もない。
    // Strategyパターンを用い、この問題に対処せよ。

    using FindCondition = std::function<bool(std::filesystem::path const&)>;

    std::vector<std::string> find_files(std::string const& path, FindCondition condition)
    {
        auto files = std::vector<fs::path>{};

        // recursive_directory_iteratorはファイルシステム依存するため、その依存を排除する他の処理
        std::copy(fs::recursive_directory_iterator{path}, fs::recursive_directory_iterator{}, std::back_inserter(files));

        std::sort(files.begin(), files.end());

        auto ret = std::vector<std::string>{};

        std::for_each(files.cbegin(), files.cend(), [&](fs::path const& p) {
            if (condition(p)) {
                ret.emplace_back(p.generic_string());
            }
        });

        return ret;
    }

    bool is_cpp_file(std::filesystem::path const& path)
    {
        auto const        filename = path.filename().generic_string();
        static auto const cpp_file = std::string{".cpp"};

        return (filename.length() > cpp_file.length())
               && (filename.substr(filename.length() - cpp_file.length()) == cpp_file);
    }

    TEST(DesignPatternA, Strategy)
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
            auto act = find_files("../ut_data", [](fs::path const& p) noexcept { return fs::is_regular_file(p); });

            ASSERT_EQ(exp, act);
        }
        {
            auto exp = sort(std::vector<std::string>{"../ut_data/d", "../ut_data/lib", "../ut_data/o"});
            auto act = find_files("../ut_data", [](fs::path const& p) noexcept { return fs::is_directory(p); });

            ASSERT_EQ(exp, act);
        }
        {
            auto exp = sort(std::vector<std::string>{"../ut_data/a.cpp", "../ut_data/abc.cpp", "../ut_data/efghij.cpp",
                                                     "../ut_data/lib/lib.cpp"});
            auto act = find_files("../ut_data", is_cpp_file);

            ASSERT_EQ(exp, act);
        }
    }
```

* [演習-Strategy](exercise_q.md#SS_22_9_21)へ戻る。


### 解答例-Visitor <a id="SS_23_9_22"></a>
```cpp
    //  exercise/design_pattern_a/visitor.cpp 9
    // [A]
    // 下記クラスFile、Dir、OtherEntityはクラスFileEntityから派生し、
    // それぞれが自身をstd::stringに変換するアルゴリズム関数
    //      * to_string_normal()
    //      * to_string_with_char()
    //      * to_string_with_children()
    // をオーバーライドしている。これはポリモーフィズムの使用方法としては正しいが、
    // to_string_xxx系統のインターフェースがが大量に増えた場合に、
    // FileEntityのインターフェースがそれに比例して増えてしまう問題を持っている。
    // Visitorパターンを使用しこれに対処せよ。

    // [解説]
    // * 通常の例では、Visitor::Visit()の戻り値はvoidになっていることが多いが、この例では
    //   std::stringにした。Visitorパターンは戻り値が同じでなければ適用できない。
    // * Visitorパターンは静的型付け言語のダブルディスパッチと呼ばれるテクニックを使っている。
    //      * 1つ目のディスパッチは、Visitor::Visitのオーバーロードによって行われる。
    //      * 2つ目のディスパッチは、Visitorの派生クラスのオーバーライドによって行われる。
    // * デザインパターンとはそういうものであるが、この例でもVisitorの導入によって返って複雑になった。
    //   しかし、to_string_xxxのようなアルゴリズムが10個、20個とあるような場合等には、
    //   クラスの肥大化を防ぐ有用な手段となる。

    class Visitor;

    class FileEntity {
    public:
        explicit FileEntity(std::string const& pathname) : pathname_{strip(pathname)} {}
        virtual ~FileEntity() = default;
        std::string const& Pathname() const noexcept { return pathname_; }
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

    TEST(DesignPatternA, Visitor)
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

* [演習-Visitor](exercise_q.md#SS_22_9_22)へ戻る。


### 解答例-CRTP <a id="SS_23_9_23"></a>
```cpp
    //  exercise/design_pattern_a/crtp.cpp 9
    // [A]
    // 下記クラスFileEntityから派生しクラスFile、Dir、OtherEntityは、
    // Visitorパターンを利用しているため、そのすべてで下記のコードクローンを持つ。
    //
    //    virtual std::string to_string(Visitor const& to_s) const { return to_s.Visit(*this); }
    //
    // このコードクローンのthisの型は、それぞれFile、Dir、OtherEntityとなるため、
    // この関数をFileEntityで定義すると動作が変わってしまい、単純には統一できない。
    // CRTPを用い、このクローンを削除せよ。

    // [解説]
    // 下記のクラステンプレートAcceptableFileEntityと、
    // それから派生したFile、Dir、OtherEntityがCRTPを実装し、コードクローンを排除した。

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

    template <typename T>
    class AcceptableFileEntity : public FileEntity {  // CRTP
    private:
        virtual std::string to_string(Visitor const& to_s) const { return to_s.Visit(*static_cast<T const*>(this)); }

        // T : public AcceptableFileEntity<T> { ... };
        // 以外の使い方をコンパイルエラーにする
        AcceptableFileEntity(std::string const& pathname) : FileEntity{pathname} {}
        friend T;
    };

    class File final : public AcceptableFileEntity<File> {
    public:
        File(std::string const& pathname) : AcceptableFileEntity{pathname} {}
    };

    class Dir final : public AcceptableFileEntity<Dir> {
    public:
        Dir(std::string const& pathname) : AcceptableFileEntity{pathname} {}
    };

    class OtherEntity final : public AcceptableFileEntity<OtherEntity> {
    public:
        OtherEntity(std::string const& pathname) : AcceptableFileEntity{pathname} {}
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

    TEST(DesignPatternA, CRTP)
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

* [演習-CRTP](exercise_q.md#SS_22_9_23)へ戻る。


### 解答例-Observer <a id="SS_23_9_24"></a>
```cpp
    //  exercise/design_pattern_a/observer.cpp 9
    // [A]
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

    // [解説]
    // * Observerパターンの使用について
    //      * ObserverIFはModelを宣言、定義しているヘッダファイルに定義する。
    //      * 何らかの理由でそうしない場合は、ObserverIFはModelを含むパッケージ内に定義する。
    // * Observerパターンの導入により、
    //      * ModelはViewX、ViewYに依存しなくなったが、代わりにObserverIFに依存する。
    //      * この依存関係はObserverIFがModelヘッダに含まれることで問題にならない。
    // * その他
    //      * 通常は、Attachに対してDetachも定義するが、AttachされたオブジェクトをDetachしない
    //        場合は、今回の例のようにAttachされたオブジェクトの廃棄をModelにさせた方が良い。
    //      * こういった動作の確認にもForTestクラスを使用した。

    class ObserverIF {
    public:
        void DisplaySomething(std::string const& result) { display_something(result); }
        virtual ~ObserverIF() = default;

    private:
        virtual void display_something(std::string const&) = 0;
    };

    class Model {
    public:
        Model() = default;
        ~Model() { wait_future(); }

        // Detachできない仕様にする。その代わりにobserverの廃棄もModelに任せることができる。
        void Attach(std::unique_ptr<ObserverIF> observer) { observers_.emplace_back(std::move(observer)); }

        void DoSomething()
        {
            wait_future();

            future_ = std::async(std::launch::async, [this] {
                // 本来は非同期処理が必要な重い処理
                auto result = std::string{"result of doing something"};

                notify(result);
            });
        }

    private:
        std::future<void>                        future_{};
        std::vector<std::unique_ptr<ObserverIF>> observers_{};

        void notify(std::string const& result) const
        {
            for (auto& observer : observers_) {
                observer->DisplaySomething(result);
            }
        }

        void wait_future()
        {
            if (future_.valid()) {
                future_.wait();
            }
        }
    };

    class ViewX : public ObserverIF {
    private:
        virtual void display_something(std::string const&) override {}
    };

    class ViewY : public ObserverIF {
    private:
        virtual void display_something(std::string const&) override {}
    };

    class Controller {
    public:
        Controller(Model& model) : model_{model} {}
        void OK_Clicked() { model_.DoSomething(); }

        Model& model_;
    };

    class ForTest : public ObserverIF {
    public:
        explicit ForTest(std::string& result, uint32_t& called, bool& destructed)
            : result_{result}, called_{called}, destructed_{destructed}
        {
        }
        virtual ~ForTest() override { destructed_ = true; }

    private:
        virtual void display_something(std::string const& result) noexcept override
        {
            result_ = result;
            ++called_;
        }

        std::string& result_;
        uint32_t&    called_;
        bool&        destructed_;
    };

    TEST(DesignPatternA, Observer)
    {
        auto result     = std::string{};
        auto called     = 0U;
        auto destructed = false;

        {
            auto model      = Model{};
            auto controller = Controller{model};

            model.Attach(std::make_unique<ViewX>());
            model.Attach(std::make_unique<ViewY>());
            model.Attach(std::make_unique<ForTest>(result, called, destructed));

            controller.OK_Clicked();
            controller.OK_Clicked();
            controller.OK_Clicked();
        }

        ASSERT_EQ("result of doing something", result);
        ASSERT_EQ(3, called);
        ASSERT_TRUE(destructed);
    }
```

* [演習-Observer](exercise_q.md#SS_22_9_24)へ戻る。


### 解答-デザインパターン選択1 <a id="SS_23_9_25"></a>
* 選択肢2
* 参照 [State](design_pattern.md#SS_9_14)
* [演習-デザインパターン選択1](exercise_q.md#SS_22_9_25)へ戻る。


### 解答-デザインパターン選択2 <a id="SS_23_9_26"></a>
* 選択肢4
* 参照 [Null Object](design_pattern.md#SS_9_15)
* [演習-デザインパターン選択2](exercise_q.md#SS_22_9_26)へ戻る。


### 解答-デザインパターン選択3 <a id="SS_23_9_27"></a>
* 選択肢3
* 参照 [Observer](design_pattern.md#SS_9_23)
* [演習-デザインパターン選択3](exercise_q.md#SS_22_9_27)へ戻る。


## 開発プロセスとインフラ(全般) <a id="SS_23_10"></a>

### 解答-プロセス分類 <a id="SS_23_10_1"></a>
* 選択肢対応
    * A - 1
    * B - 2
    * C - 3

* 参照 [プロセス](process_and_infra.md#SS_11_1)
* [演習-プロセス分類](exercise_q.md#SS_22_10_1)へ戻る。


### 解答-V字モデル <a id="SS_23_10_2"></a>
* 選択肢対応
    * フェーズA - 4
    * フェーズB - 2
    * フェーズC - 3
    * フェーズD - 1

* 参照 [ウォーターフォールモデル、V字モデル](process_and_infra.md#SS_11_1_1)
* [演習-V字モデル](exercise_q.md#SS_22_10_2)へ戻る。


### 解答-アジャイル <a id="SS_23_10_3"></a>
* 選択肢2
* 参照 [アジャイル系プロセス](process_and_infra.md#SS_11_1_2)
* [演習-アジャイル](exercise_q.md#SS_22_10_3)へ戻る。


### 解答-自動化 <a id="SS_23_10_4"></a>
* 選択肢対応
    * A - 1
    * B - 4
    * C - 5

* 参照 [自動単体テスト](process_and_infra.md#SS_11_2_1)
* [演習-自動化](exercise_q.md#SS_22_10_4)へ戻る。


### 解答-単体テスト <a id="SS_23_10_5"></a>
* 選択肢4
* 参照 [自動単体テスト](process_and_infra.md#SS_11_2_1)
* [演習-単体テスト](exercise_q.md#SS_22_10_5)へ戻る。


### 解答-リファクタリングに付随する活動 <a id="SS_23_10_6"></a>
* 選択肢2
* 参照 [リファクタリング](process_and_infra.md#SS_11_2_2)
* [演習-リファクタリングに付随する活動](exercise_q.md#SS_22_10_6)へ戻る。


### 解答-リファクタリング対象コード <a id="SS_23_10_7"></a>
* 選択肢3
* 参照 [リファクタリング](process_and_infra.md#SS_11_2_2)
* [演習-リファクタリング対象コード](exercise_q.md#SS_22_10_7)へ戻る。


### 解答-CI <a id="SS_23_10_8"></a>
* 選択肢2, 4
* 参照 [CI(継続的インテグレーション)](process_and_infra.md#SS_11_2_5)
* [演習-CI](exercise_q.md#SS_22_10_8)へ戻る。


## テンプレートメタプログラミング <a id="SS_23_11"></a>
### 解答例-パラメータパック <a id="SS_23_11_1"></a>
```cpp
    //  exercise/template_a/parameter_pack.cpp 7
    // [A]
    // 下記の関数Maxは、単体テストが示す通り、2つのパラメータの大きい方を返す。
    // 任意の個数の引数を取れるようにMaxを修正せよ。

    // 解答例1
    // パラメータパックを使用しMaxを修正した例
    template <typename T>
    T Max(T const& t0, T const& t1) noexcept
    {
        return t0 > t1 ? t0 : t1;
    }

    template <typename HEAD, typename... ARGS>
    auto Max(HEAD const& head, ARGS const&... args) noexcept
    {
        auto args_max = Max(args...);

        return head > args_max ? head : args_max;
    }

    TEST(TemplateMetaProgrammingA, parameter_pack)
    {
        ASSERT_EQ(2, Max(1, 2));
        ASSERT_EQ("bcd", Max(std::string{"abc"}, std::string{"bcd"}));

        ASSERT_EQ(3, Max(1, 2, 3));
        ASSERT_EQ("efg", Max(std::string{"abc"}, std::string{"bcd"}, std::string{"efg"}));
    }

    // 解答例2
    // std::initializer_listを使用しMaxを修正した例
    template <typename T>
    T Max(std::initializer_list<T> t_list) noexcept
    {
        auto ret   = T{};
        auto first = true;

        for (auto const& t : t_list) {
            if (std::exchange(first, false)) {
                ret = t;
            }
            else {
                ret = Max(ret, t);
            }
        }

        return ret;
    }

    TEST(TemplateMetaProgrammingA, initializer_list)
    {
        ASSERT_EQ(2, Max({1, 2}));
        ASSERT_EQ("bcd", Max({std::string{"abc"}, std::string{"bcd"}}));

        ASSERT_EQ(3, Max({1, 2, 3}));
        ASSERT_EQ("efg", Max({std::string{"abc"}, std::string{"bcd"}, std::string{"efg"}}));
    }
```

* [演習-パラメータパック](exercise_q.md#SS_22_11_1)へ戻る。


### 解答例-エイリアステンプレート <a id="SS_23_11_2"></a>
```cpp
    //  exercise/template_a/template_alias.cpp 5
    // [A]
    // 下記の単体テストでしているstd::vector<std::vector<XXX>>を、
    // テンプレートエイリアスによって簡潔に記述せよ。

    // 解説
    // 下記のVect1Dはstd::vectorに対して簡潔な記述方法を提供しているとは言えないが、
    // Vect2Dと同じような場面で使用することが明示されるため、ソースコードに一貫性を与える。

    template <typename T>
    using Vect2D = std::vector<std::vector<T>>;

    template <typename T>
    using Vect1D = std::vector<T>;

    TEST(TemplateMetaProgrammingA, template_alias)
    {
        {
            auto vv = Vect2D<int>{{1, 2, 3}, {3, 4, 5}};
            ASSERT_EQ(2, vv.size());
            ASSERT_EQ((Vect1D<int>{1, 2, 3}), vv[0]);
            ASSERT_EQ((Vect1D<int>{3, 4, 5}), vv[1]);
            ASSERT_EQ(5, vv[1][2]);
        }
        {
            auto vv = Vect2D<float>{{1, 2, 3}, {3, 4, 5}};
            ASSERT_EQ(2, vv.size());
            ASSERT_EQ((Vect1D<float>{1, 2, 3}), vv[0]);
            ASSERT_EQ((Vect1D<float>{3, 4, 5}), vv[1]);
            ASSERT_EQ(5, vv[1][2]);
        }
        {
            auto vv = Vect2D<std::string>{{"1", "2", "3"}, {"3", "4", "5"}};
            ASSERT_EQ(2, vv.size());
            ASSERT_EQ((Vect1D<std::string>{"1", "2", "3"}), vv[0]);
            ASSERT_EQ((Vect1D<std::string>{"3", "4", "5"}), vv[1]);
            ASSERT_EQ("5", vv[1][2]);
        }
    }
```

* [演習-エイリアステンプレート](exercise_q.md#SS_22_11_2)へ戻る。


### 解答例-名前空間による修飾不要な`operator<<` <a id="SS_23_11_3"></a>
```cpp
    //  exercise/template_a/put_to.cpp 3
    // [A]
    // 下記のように名前空間TemplateMP、エイリアスInts_tとそのoperator<<が定義されている場合、
    // 単体テストで示した通り、Ints_tのoperator<<を使用するためには、
    // 名前空間による修飾やusing宣言/ディレクティブの記述が必要になる。
    // Ints_tをstd::vectorから継承したクラスとして定義することにより、このような記述を不要にせよ。

    namespace TemplateMP {

    struct Ints_t : std::vector<int> {
        using std::vector<int>::vector;  // 継承コンストラクタ
    };

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
    TEST(TemplateMetaProgrammingA, put_to)
    {
        {
            auto oss  = std::ostringstream{};
            auto ints = TemplateMP::Ints_t{1, 2, 3};

            oss << ints;  // ADLによるname lookup

            ASSERT_EQ("1 : 2 : 3", oss.str());
        }
    }
    }  // namespace
```

* [演習-名前空間による修飾不要な`operator<<`](exercise_q.md#SS_22_11_3)へ戻る。


### 解答例-std::arrayの継承 <a id="SS_23_11_4"></a>
```cpp
    //  exercise/template_a/safe_array.cpp 5
    // [A]
    // std::array、std::vector、std::string等のSTLの配列型コンテナはインデックスアクセスに対して、
    // レンジのチェックをしないため、不正なメモリアクセスをしてしまうことがある。
    // std::arrayを使用して、このような問題のないSafeArrayを作り、単体テストを行え。

    template <typename T, std::size_t N>
    struct SafeArray : std::array<T, N> {
        using std::array<T, N>::array;  // 継承コンストラクタ

        template <typename... ARGS>  // コンストラクタを定義
        SafeArray(ARGS... args) noexcept(std::is_nothrow_constructible_v<T, ARGS...>) : base_type{args...}
        {
        }

        using base_type = std::array<T, N>;
        using size_type = typename base_type::size_type;

        typename base_type::reference       operator[](size_type i) { return this->at(i); }
        typename base_type::const_reference operator[](size_type i) const { return this->at(i); }
    };

    namespace {
    TEST(TemplateMetaProgrammingA, safe_array)
    {
        auto sa = SafeArray<int, 3>{1, 2, 3};

        static_assert(std::is_nothrow_constructible_v<decltype(sa), int>);
        ASSERT_EQ(3, sa.size());
        ASSERT_EQ(1, sa[0]);
        ASSERT_EQ(2, sa[1]);
        ASSERT_EQ(3, sa[2]);
        ASSERT_THROW(sa[3], std::out_of_range);

        auto sa2 = SafeArray<std::string, 2>{"1", "2"};

        static_assert(!std::is_nothrow_constructible_v<decltype(sa2), char const*>);
        ASSERT_EQ(2, sa2.size());
        ASSERT_EQ("1", sa2[0]);
        ASSERT_EQ("2", sa2[1]);
        ASSERT_THROW(sa2[2], std::out_of_range);
    }
    }  // namespace
```

* [演習-std::arrayの継承](exercise_q.md#SS_22_11_4)へ戻る。


### 解答例-SFINAEを利用しない関数テンプレートの特殊化によるis_void <a id="SS_23_11_5"></a>
```cpp
    //  exercise/template_a/is_void.cpp 3
    // [A]
    // 下記の仕様を満たす関数テンプレートis_void_f<T>と定数テンプレートis_void_f_v<T>を作れ。
    //    * 与えられたテンプレートパラメータがvoidの場合、trueを返す
    //    * 与えられたテンプレートパラメータがvoidでない場合、falseを返す
    //    * std::is_sameを使わない
    //    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

    template <typename T>
    constexpr bool is_void_f() noexcept
    {
        return false;
    }

    template <>
    constexpr bool is_void_f<void>() noexcept
    {
        return true;
    }

    template <typename T>
    constexpr bool is_void_f_v{is_void_f<T>()};

    namespace IsVoidTest {
    void        test_func_0() noexcept {};
    std::string test_func_1() { return "test"; };
    }  // namespace IsVoidTest

    namespace {

    TEST(TemplateMetaProgrammingA, is_void_f)
    {
        static_assert(!is_void_f_v<int>);
        static_assert(is_void_f_v<void>);
        static_assert(is_void_f_v<decltype(IsVoidTest::test_func_0())>);
        static_assert(!is_void_f_v<decltype(IsVoidTest::test_func_1())>);
    }
    }  // namespace
```

* [演習-SFINAEを利用しない関数テンプレートの特殊化によるis_void](exercise_q.md#SS_22_11_5)へ戻る。


### 解答例-SFINAEを利用しないクラステンプレートの特殊化によるis_void <a id="SS_23_11_6"></a>
```cpp
    //  exercise/template_a/is_void.cpp 43
    // [A]
    // 下記の仕様を満たすクラステンプレートis_void_s<T>と定数テンプレートis_void_s_v<T>を作れ。
    //    * 与えられたテンプレートパラメータがvoidの場合、メンバvalueがtrueになる
    //    * 与えられたテンプレートパラメータがvoidでない場合、メンバvalueがtrueになる
    //    * std::is_sameを使わない
    //    * std::true_type/std::false_typeを利用する
    //    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

    template <typename T>
    struct is_void_s : std::false_type {
    };

    template <>
    struct is_void_s<void> : std::true_type {
    };

    template <typename T>
    constexpr bool is_void_s_v{is_void_s<T>::value};

    namespace {

    TEST(TemplateMetaProgrammingA, is_void_s)
    {
        static_assert(!is_void_s_v<int>);
        static_assert(is_void_s_v<void>);
        static_assert(is_void_s_v<decltype(IsVoidTest::test_func_0())>);
        static_assert(!is_void_s_v<decltype(IsVoidTest::test_func_1())>);
    }
    }  // namespace
```

* [演習-SFINAEを利用しないクラステンプレートの特殊化によるis_void](exercise_q.md#SS_22_11_6)へ戻る。


### 解答例-SFINAEを利用した関数テンプレートの特殊化によるis_void <a id="SS_23_11_7"></a>
```cpp
    //  exercise/template_a/is_void.cpp 75
    // [A]
    // 下記の仕様を満たす関数テンプレートis_void_sfinae_f<T>と
    // 定数テンプレートis_void_sfinae_f<T>を作れ。
    //    * 与えられたテンプレートパラメータがvoidの場合、trueを返す
    //    * 与えられたテンプレートパラメータがvoidでない場合、falseを返す
    //    * std::is_sameを使わない
    //    * SFINAEを利用する
    //    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

    namespace Inner_ {

    // T == void
    template <typename T>
    constexpr auto is_void_sfinae_f_detector(void const* v, T const* t) noexcept
        -> decltype(t = v, bool{})  // T != voidの場合、t = vはill-formed
                                    // T == voidの場合、well-formedでbool型生成
    {
        return true;
    }

    constexpr auto is_void_sfinae_f_detector(...) noexcept  // name lookupの順位は最低
    {
        return false;
    }
    }  // namespace Inner_

    template <typename T>
    constexpr bool is_void_sfinae_f() noexcept
    {
        return Inner_::is_void_sfinae_f_detector(nullptr, static_cast<T*>(nullptr));
    }

    template <typename T>
    constexpr bool is_void_sfinae_f_v{is_void_sfinae_f<T>()};

    namespace {

    TEST(TemplateMetaProgrammingA, is_void_sfinae_f)
    {
        static_assert(!is_void_sfinae_f_v<int>);
        static_assert(is_void_sfinae_f_v<void>);
        static_assert(is_void_sfinae_f_v<decltype(IsVoidTest::test_func_0())>);
        static_assert(!is_void_sfinae_f_v<decltype(IsVoidTest::test_func_1())>);
    }
    }  // namespace
```

* [演習-SFINAEを利用した関数テンプレートの特殊化によるis_void](exercise_q.md#SS_22_11_7)へ戻る。


### 解答例-SFINAEを利用したクラステンプレートの特殊化によるis_void <a id="SS_23_11_8"></a>
```cpp
    //  exercise/template_a/is_void.cpp 123
    // [A]
    // 下記の仕様を満たすクラステンプレートis_void_sfinae_s<T>と
    // 定数テンプレートis_void_sfinae_s_v<T>を作れ。
    //    * 与えられたテンプレートパラメータがvoidの場合、メンバvalueがtrueになる
    //    * 与えられたテンプレートパラメータがvoidでない場合、メンバvalueがtrueになる
    //    * std::is_sameを使わない
    //    * std::true_type/std::false_typeを利用する
    //    * SFINAEを利用する
    //    * 下記の単体テストをパスする(#if 0を削除してもコンパイルできる)

    namespace Inner_ {

    template <typename T>
    T*& t2ptr();

    }  // namespace Inner_

    template <typename T, typename = void*&>
    struct is_void_sfinae_s : std::false_type {
    };

    template <typename T>
    struct is_void_sfinae_s<T, decltype(Inner_::t2ptr<T>() = Inner_::t2ptr<void>())> : std::true_type {
    };

    template <typename T>
    constexpr bool is_void_sfinae_s_v{is_void_sfinae_s<T>::value};

    namespace {

    TEST(TemplateMetaProgrammingA, is_void_sfinae_s)
    {
        static_assert(!is_void_sfinae_s_v<int>);
        static_assert(is_void_sfinae_s_v<void>);
        static_assert(is_void_sfinae_s_v<decltype(IsVoidTest::test_func_0())>);
        static_assert(!is_void_sfinae_s_v<decltype(IsVoidTest::test_func_1())>);
    }
    }  // namespace
```

* [演習-SFINAEを利用したクラステンプレートの特殊化によるis_void](exercise_q.md#SS_22_11_8)へ戻る。


### 解答例-テンプレートテンプレートパラメータ <a id="SS_23_11_9"></a>
```cpp
    //  exercise/template_a/template_template.cpp 5
    // [A]
    // 以下の仕様を満たすクラステンプレートを作れ。
    //  * 任意のSTLコンテナを唯一のテンプレートパラメータとする
    //  * そのコンテナを使用しint型のデータを格納する

    template <template <class...> class STL_CONTAINER>
    struct IntContainer : STL_CONTAINER<int> {
        using STL_CONTAINER<int>::STL_CONTAINER;
    };

    namespace {

    TEST(TemplateMetaProgrammingA, template_template)
    {
        auto vi = IntContainer<std::vector>{1, 2, 3};
        auto vl = IntContainer<std::list>{1, 2, 3};
        auto vs = IntContainer<std::basic_string>{1, 2, 3};  // 意味は不明だがこれも可能

        ASSERT_EQ((std::vector<int>{1, 2, 3}), vi);
        ASSERT_EQ((std::list<int>{1, 2, 3}), vl);
        ASSERT_EQ((std::basic_string<int>{1, 2, 3}), vs);
    }
    }  // namespace
```

* [演習-テンプレートテンプレートパラメータ](exercise_q.md#SS_22_11_9)へ戻る。


### 解答例-テンプレートパラメータを可変長にしたstd::is_same <a id="SS_23_11_10"></a>
```cpp
    //  exercise/template_a/is_same.cpp 3
    // [A]
    // 以下の仕様を満たすクラステンプレートis_same_some_of<T, U...>と
    // 定数テンプレートis_same_some_of_v<T, U...>を作れ。
    //  * 2個以上のテンプレートパラメータを持つ
    //  * 第1パラメータと他のパラメータの何れかが同一の型であった場合、メンバvalueがtrueになる
    //  * 前行の条件が成立しなかった場合、メンバvalueがfalseになる
    //  * 型の同一性はstd::is_sameを使って判定する

    template <typename T, typename U, typename... Us>
    struct is_same_some_of {
        static constexpr bool value{std::is_same_v<T, U> ? true : is_same_some_of<T, Us...>::value};
    };

    template <typename T, typename U>
    struct is_same_some_of<T, U> {
        static constexpr bool value{std::is_same_v<T, U>};
    };

    template <typename T, typename U, typename... Us>
    constexpr bool is_same_some_of_v{is_same_some_of<T, U, Us...>::value};

    namespace {

    TEST(TemplateMetaProgrammingA, is_same_some_of)
    {
        static_assert(!is_same_some_of_v<int, int8_t, int16_t, uint16_t>);
        static_assert(is_same_some_of_v<int, int8_t, int16_t, uint16_t, int32_t>);
        static_assert(is_same_some_of_v<int&, int8_t, int16_t, int32_t&, int32_t>);
        static_assert(!is_same_some_of_v<int&, int8_t, int16_t, uint32_t&, int32_t>);
        static_assert(is_same_some_of_v<std::string, int, char*, std::string>);
        static_assert(!is_same_some_of_v<std::string, int, char*>);
    }
    }  // namespace
```

* [演習-テンプレートパラメータを可変長にしたstd::is_same](exercise_q.md#SS_22_11_10)へ戻る。


### 解答例-メンバ関数の存在の診断 <a id="SS_23_11_11"></a>
```cpp
    //  exercise/template_a/exists_func.cpp 5
    // [A]
    // テンプレートパラメータの型がメンバ関数c_str()を持つか否かを判定する
    // クラステンプレートhas_c_str<T>と定数テンプレートhas_c_str_v<T>を作れ。

    template <typename T, typename U = bool>
    struct has_c_str : std::false_type {
    };

    template <typename T>
    struct has_c_str<T, decltype(std::declval<T>().c_str(), bool{})> : std::true_type {
    };

    template <typename T>
    constexpr bool has_c_str_v{has_c_str<T>::value};

    namespace {

    TEST(TemplateMetaProgrammingA, has_c_str)
    {
        static_assert(has_c_str_v<std::string>);
        static_assert(!has_c_str_v<std::vector<int>>);
    }
    }  // namespace
```

* [演習-メンバ関数の存在の診断](exercise_q.md#SS_22_11_11)へ戻る。


### 解答例-範囲for文のオペランドになれるかどうかの診断 <a id="SS_23_11_12"></a>
```cpp
    //  exercise/template_a/exists_func.cpp 31
    // [A]
    // 範囲for文は、
    //      for(auto a : obj ) { ... }
    // のような形式で表現される。
    // テンプレートパラメータから生成されたオブジェクトが、
    // このobjに指定できるか否かを判定するクラステンプレートis_range<T>
    // と定数テンプレートis_range_v<T>を作れ。

    // 解説
    // 上記objに指定できるための条件は、std::begin()、std::end()の引数になれることとした。
    // セマンティクス的に正しいstd::begin()、std::end()は、それぞれが最初と最後を表す
    // イテレータ(もしくはポインタ)でなければならないが、それはテンプレートでの判定の範囲外である。

    template <typename, typename = bool>
    struct exists_begin : std::false_type {
    };

    template <typename T>
    struct exists_begin<T, decltype(std::begin(std::declval<T&>()), bool{})> : std::true_type {
    };

    template <typename T>
    constexpr bool exists_begin_v{exists_begin<T>::value};

    template <typename, typename = bool>
    struct exists_end : std::false_type {
    };

    template <typename T>
    struct exists_end<T, decltype(std::end(std::declval<T&>()), bool{})> : std::true_type {
    };

    template <typename T>
    constexpr bool exists_end_v{exists_end<T>::value};

    template <typename T>
    struct is_range : std::conditional_t<exists_begin_v<T> && exists_end_v<T>, std::true_type, std::false_type> {
    };

    template <typename T>
    constexpr bool is_range_v{is_range<T>::value};

    namespace {

    TEST(TemplateMetaProgrammingA, is_range)
    {
        static_assert(is_range_v<std::string>);
        static_assert(is_range_v<std::vector<int>>);
        static_assert(!is_range_v<std::mutex>);
        static_assert(!is_range_v<std::lock_guard<std::mutex>>);
    }
    }  // namespace
```

* [演習-範囲for文のオペランドになれるかどうかの診断](exercise_q.md#SS_22_11_12)へ戻る。


### 解答例-配列の長さの取り出し <a id="SS_23_11_13"></a>
```cpp
    //  exercise/template_a/array_op.cpp 3
    // [A]
    // 配列を引数に取り、その長さを返す関数テンプレートarray_lengthを作れ。

    template <typename T, size_t N>
    constexpr size_t array_length(T const (&)[N]) noexcept
    {
        return N;
    }

    namespace {

    TEST(TemplateMetaProgrammingA, array_length)
    {
        int         i[5];
        std::string str[]{"a", "b", "c"};

        static_assert(array_length(i) == 5);
        static_assert(array_length(str) == 3);
    }
    }  // namespace
```

* [演習-配列の長さの取り出し](exercise_q.md#SS_22_11_13)へ戻る。


### 解答例-配列の次元の取り出し <a id="SS_23_11_14"></a>
```cpp
    //  exercise/template_a/array_op.cpp 26
    // [A]
    // 配列を引数に取り、その次元を返す関数テンプレートarray_dimensionを作れ。

    constexpr size_t array_dimension(...) noexcept { return 0; }

    template <typename T, size_t N>
    constexpr size_t array_dimension(T const (&t)[N]) noexcept
    {
        return 1 + array_dimension(t[0]);
    }

    namespace {

    TEST(TemplateMetaProgrammingA, array_dimension)
    {
        constexpr int i1[5]{};
        constexpr int i2[5][2]{};
        constexpr int i3[5][2][3]{};

        static_assert(array_dimension(i1) == 1);
        static_assert(array_dimension(i2) == 2);
        static_assert(array_dimension(i3) == 3);
    }
    }  // namespace
```

* [演習-配列の次元の取り出し](exercise_q.md#SS_22_11_14)へ戻る。


### 解答例-関数型のテンプレートパラメータを持つクラステンプレート <a id="SS_23_11_15"></a>
```cpp
    //  exercise/template_a/scoped_guard.cpp 8
    // [A]
    // RAIIを行うための下記クラスscoped_guardをstd::functionを使わずに再実装せよ。

    template <typename FUNC>
    class scoped_guard {
    public:
        explicit scoped_guard(FUNC&& f) noexcept : f_{f}
        {
            static_assert(std::is_nothrow_invocable_r_v<void, FUNC>, "FUNC()() must return void");
        }
        ~scoped_guard() { f_(); }

        scoped_guard(scoped_guard const&)   = delete;   // copy禁止
        scoped_guard(scoped_guard&&)        = default;  // move
        void operator=(scoped_guard const&) = delete;   // copy代入禁止
        void operator=(scoped_guard&&)      = delete;   // move代入禁止

    private:
        FUNC f_;
    };

    namespace {

    TEST(TemplateMetaProgrammingA, scoped_guard)
    {
        {
            auto demangled = abi::__cxa_demangle(typeid(std::vector<int>).name(), 0, 0, nullptr);
            auto f         = [demangled]() noexcept { free(demangled); };
            auto sg        = scoped_guard<decltype(f)>{std::move(f)};  // C++14までの記法

            ASSERT_STREQ("std::vector<int, std::allocator<int> >", demangled);
        }
        {
            auto demangled = abi::__cxa_demangle(typeid(std::vector<int>).name(), 0, 0, nullptr);
            auto gs        = scoped_guard{[demangled]() noexcept { free(demangled); }};  // C++17からの記法

            ASSERT_STREQ("std::vector<int, std::allocator<int> >", demangled);
        }
        {
            auto stream = popen("ls " __FILE__, "r");
            auto f      = [stream]() noexcept { fclose(stream); };
            auto sg     = scoped_guard<decltype(f)>{std::move(f)};  // C++14までの記法

            char buff[256]{};
            fgets(buff, sizeof(buff) - 1, stream);

            ASSERT_STREQ("scoped_guard.cpp\n", buff);
        }
        {
            auto stream = popen("ls " __FILE__, "r");
            auto gs     = scoped_guard{[stream]() noexcept { fclose(stream); }};  // C++17からの記法

            char buff[256]{};
            fgets(buff, sizeof(buff) - 1, stream);

            ASSERT_STREQ("scoped_guard.cpp\n", buff);
        }
    }
    }  // namespace
```

* [演習-関数型のテンプレートパラメータを持つクラステンプレート](exercise_q.md#SS_22_11_15)へ戻る。


