<!-- ./md/refactring_expamples.md -->
# 11 リファクタリングの例 <a id="SS_11"></a>
ソースコードに多くの問題があった場合でも、一度に多くの視点からの修正をしてはならない。
ステップバイステップで少しずつ改善させることを心掛けるべきである。

例えば大きすぎる関数を分割するリファクタリングを行う場合は、その分割のみに集中すべきで、
その最中に別の問題を見つけても、その修正を行ってはならない。
まずは、仕掛中のリファクタリングを終了させ、その後(コミットした後)、次の問題点に取り掛かるべきである。

以下では、そういったステップバイステップのリファクタリングを例示する。

___

__この章の構成__

11.1 [オリジナルのソースコード](refactring_expamples.md#SS_11_1)  
11.2 [機能追加によるソースコード品質劣化](refactring_expamples.md#SS_11_2)  
11.3 [小規模なリファクタリング](refactring_expamples.md#SS_11_3)  
11.4 [構造のリファクタリング](refactring_expamples.md#SS_11_4)  
11.5 [単体テストの開発](refactring_expamples.md#SS_11_5)  
11.6 [クラスの導入](refactring_expamples.md#SS_11_6)  
11.7 [単体テストの変更](refactring_expamples.md#SS_11_7)  
11.8 [MVCの導入](refactring_expamples.md#SS_11_8)  
11.9 [単体テストの変更(単体テスト用クラス導入)](refactring_expamples.md#SS_11_9)  
11.10 [DIの導入](refactring_expamples.md#SS_11_10)  
11.11 [全クラスの単体テスト](refactring_expamples.md#SS_11_11)  
11.12 [自動統合テストのための仕様追加](refactring_expamples.md#SS_11_12)  
11.13 [自動統合テストのためのソースコード変更](refactring_expamples.md#SS_11_13)  
11.14 [自動統合テスト用ソースコード変更のための単体テスト](refactring_expamples.md#SS_11_14)  
11.15 [自動統合テストの実装](refactring_expamples.md#SS_11_15)  
  
  

___


[インデックス](seminer_intro.md#SS_1_2)/[章の最後](refactring_expamples.md#SS_11_999)/[次の章](concurrency.md#SS_12)

___


## 11.1 オリジナルのソースコード <a id="SS_11_1"></a>
まずはリファクタリング前のオリジナルのソースコードを示す。

```cpp
    //  example/ref_org/main.cpp 8

    int main(int, char**)
    {
        auto strings = std::vector<std::string>{};

        for (;;) {
            auto buffer = std::string{};

            if (std::getline(std::cin, buffer)) {
                switch (buffer.at(0)) {
                case '+': {
                    auto result = std::string{do_heavy_algorithm(buffer.substr(1))};
                    strings.emplace_back(result);
                    for (auto i = 0U; i < strings.size(); i++) {
                        std::cout << strings[i] << std::endl;
                    }
                    break;
                }
                case '.':
                    // do nothing
                    break;
                case '=':
                    return 0;
                default:
                    return 1;  // error exit
                }
            }
        }

        return 0;
    }
```

上記プログラムは、

1. 標準入力から文字列を受け取り、
2. 文字列をパースし、コマンドと引数文字列に分離し、
3. 引数文字列を、時間のかかるアルゴリズムで別の文字列に変換し、
4. 変換文字列を保存し、
5. 保存した全ての変換文字列をstd::coutに出力する。

ソースコードの品質は高くないので、
すくなくとも機能追加するタイミングではリファクタリングが必要になる。

## 11.2 機能追加によるソースコード品質劣化 <a id="SS_11_2"></a>
時間のかかるアルゴリズムがプログラムをブロックしてしまうので、
下記のように、この処理を(不十分ながら)非同期化した。

```cpp
    //  example/ref_async_org/main.cpp 15

    int main(int, char**)
    {
        auto         strings = std::vector<std::string>{};
        std::thread* thd     = nullptr;

        for (;;) {
            auto buffer = std::string{};

            if (std::getline(std::cin, buffer)) {
                switch (buffer.at(0)) {
                case '+': {
                    if (thd != nullptr) {
                        thd->join();
                        delete thd;
                    }

                    thd = new std::thread{[&strings, input = buffer.substr(1)] {
                        auto result = std::string{do_heavy_algorithm(input)};
                        strings.emplace_back(result);

                        for (auto i = 0U; i < strings.size(); i++) {
                            std::cout << strings[i] << std::endl;
                        }
                    }};
                    break;
                }
                case '.':
                    // ...
                }
            }
        }

        return 0;
    }
```

一般に、同期処理をそのまま非同期に変更するとソースコードは腐敗を始める。
上記ソースコードもその例に漏れず、かなり醜悪になった。

## 11.3 小規模なリファクタリング <a id="SS_11_3"></a>
Null ObjectパターンやRAIIの導入で肥大化したmain関数を改善する小規模なリファクタリングを行う。

```cpp
    //  example/ref_async_r0/main.cpp 13

    int main(int, char**)
    {
        auto strings = std::vector<std::string>{};
        auto thd     = std::make_unique<std::thread>([] {});        // Null Object & RAII
        auto sg      = Nstd::ScopedGuard{[&thd] { thd->join(); }};  // RAII

        for (;;) {
            auto buffer = std::string{};

            if (std::getline(std::cin, buffer)) {
                switch (buffer[0]) {
                case '+': {
                    thd->join();
                    thd = std::make_unique<std::thread>([&strings, input = buffer.substr(1)] {
                        auto result = std::string{do_heavy_algorithm(input)};
                        strings.emplace_back(result);
                        for (auto const& str : strings) {  // 範囲for文
                            std::cout << str << std::endl;
                        }
                    });
                    break;
                }
                case '.':
                    // ...
                }
            }
        }

        return 0;
    }
```

上記例のScopedGuardは、汎用性が高くプロジェクト全体で使用できるため、別のファイルとして、
下記のように宣言、定義する(汎用性が高いクラスや関数をプロジェクト全体で共有することは良い習慣である)。

```cpp
    //  essential/h/scoped_guard.h 7

    /// @brief RAIIのためのクラス。コンストラクタ引数の関数オブジェクトをデストラクタから呼び出す
    ///
    #if __cplusplus >= 202002L   // c++20

    template <std::invocable F>  // Fが呼び出し可能であることを制約
    #else  // c++17

    template <typename F>
    #endif
    class ScopedGuard {
    public:
        explicit ScopedGuard(F&& f) noexcept : f_{f}
        {
        }

        ~ScopedGuard() { f_(); }
        ScopedGuard(ScopedGuard const&)            = delete;  // copyは禁止
        ScopedGuard& operator=(ScopedGuard const&) = delete;  // copyは禁止

    private:
        F f_;
    };
```

## 11.4 構造のリファクタリング <a id="SS_11_4"></a>
前記レベルでは不十分であるため、ブロックを関数化するリファクタリングを行う。

```cpp
    //  example/ref_async_r1/main.cpp 9

    namespace {
    int main_loop()
    {
        auto strings = std::vector<std::string>{};
        auto thd     = std::thread{[] {}};                         // NullObject & RAII
        auto sg      = Nstd::ScopedGuard{[&thd] { thd.join(); }};  // RAII

        for (;;) {
            auto buffer = std::string{};

            if (std::getline(std::cin, buffer)) {
                if (auto exit_code = dispatch(thd, strings, buffer)) {
                    return *exit_code;
                }
            }
        }

        assert(false);
        return 0;
    }
    }  // namespace

    int main(int, char**) { return main_loop(); }
```

メインループ関数は、main()と同じファイルに残すが、他の関数は下記のように他のファイルで定義する。
これにより、部分的だが単体テストが導入できる。

```cpp
    //  example/ref_async_r1/lib.cpp 6

    namespace {
    void convert_store_async(std::thread& thd, std::vector<std::string>& strings, std::string const& input)
    {
        thd.join();

        thd = std::thread{[&strings, input = input] {
            auto result = std::string{do_heavy_algorithm(input)};
            strings.emplace_back(result);
            for (auto const& str : strings) {
                std::cout << str << std::endl;
            }
        }};
    }
    }  // namespace

    std::optional<int> dispatch(std::thread& thd, std::vector<std::string>& strings, std::string const& command)
    {
        switch (command[0]) {
        case '+':
            convert_store_async(thd, strings, command.substr(1));
            return std::nullopt;
        case '.':
            // do nothing
            return std::nullopt;
        case '=':
            return 0;
        default:
            return 1;
        }
    }
```

## 11.5 単体テストの開発 <a id="SS_11_5"></a>
前述したように、関数やファイルを分割したことにより、
不十分なレベルではあるが単体テストを開発、実行できるようになった。

```cpp
    //  example/ref_async_r1/lib_ut.cpp 10

    TEST(RefAsyncR1, dispatch)
    {
        auto actual = std::vector<std::string>{};

        {
            auto thd = std::thread{[] {}};                   // NullObject & RAII
            auto sg  = ScopedGuard{[&thd] { thd.join(); }};  // RAII

            {
                auto exit_code = dispatch(thd, actual, "+abc");
                ASSERT_FALSE(exit_code);
            }
            {
                auto exit_code = dispatch(thd, actual, "+defg");
                ASSERT_FALSE(exit_code);
            }
            {
                auto exit_code = dispatch(thd, actual, ".");
                ASSERT_FALSE(exit_code);
            }
            {
                auto exit_code = dispatch(thd, actual, "+hijkl");
                ASSERT_FALSE(exit_code);
            }
            {
                auto exit_code = dispatch(thd, actual, "=");
                ASSERT_TRUE(exit_code);
                ASSERT_EQ(0, *exit_code);
            }
            {
                auto exit_code = dispatch(thd, actual, "?");
                ASSERT_TRUE(exit_code);
                ASSERT_NE(0, *exit_code);
            }
        }

        ASSERT_EQ((std::vector<std::string>{"ABC", "DEFG", "HIJKL"}), actual);
    }
```

scoped_guard.hに関しても単体テストを追加するべきである。
このような単純なクラスに対して単体テストを行うことは一見無駄なように思えるかもしれないが、
単体テストカバレッジの管理、
「[割れ窓理論](https://ja.wikipedia.org/wiki/%E5%89%B2%E3%82%8C%E7%AA%93%E7%90%86%E8%AB%96)」
等の観点から重要である。

```cpp
    //  example/ref_async_r1/scoped_guard_ut.cpp 8

    TEST(ScopedGuard, scoped_guard)
    {
        auto a = 0;

        {
            auto sg = ScopedGuard{[&a]() noexcept { a = 99; }};
            ASSERT_NE(99, a);  // ~ScopedGuardは呼ばれていない
        }
        ASSERT_EQ(99, a);  // ~ScopedGuardは呼ばれた
    }
```

## 11.6 クラスの導入 <a id="SS_11_6"></a>
このプログラムは非同期処理が必要であるため、
そういったアプリケーションとの相性が良い[MVC](design_pattern.md#SS_9_5_2)の導入によるリファクタリングを行う
(この程度の規模のソフトウェアにMVCを導入する必要はないが、
その導入を例示するためリファクタリングを行う)。

まずは、コマンドの非同期処理を行うクラス(== ビジネスロジック == Model)を導入する
(例としての分かりやすさを優先するためにクラス名もModelとする)。

```cpp
    //  example/ref_async_r2/main.cpp 6

    namespace {
    int main_loop()
    {
        auto model = Model{};

        for (;;) {
            auto buffer = std::string{};

            if (std::getline(std::cin, buffer)) {
                if (auto exit_code = dispatch(model, buffer)) {
                    return *exit_code;
                }
            }
        }

        assert(false);
        return 0;
    }
    }  // namespace

    int main(int, char**) { return main_loop(); }
```

以下のファイルで、Modelの宣言、定義を行う。

```cpp
    //  example/ref_async_r2/lib.h 8

    class Model {
    public:
        Model() : thd_{[] {}}, strings_{} {}
        ~Model() { thd_.join(); }
        void ConvertStoreAsync(std::string const& input);

    private:
        std::thread              thd_;
        std::vector<std::string> strings_;
    };
```

```cpp
    //  example/ref_async_r2/lib.cpp 6

    void Model::ConvertStoreAsync(std::string const& input)
    {
        thd_.join();

        thd_ = std::thread{[&sv = strings_, input = input] {
            sv.emplace_back(do_heavy_algorithm(input));

            for (auto const& str : sv) {
                std::cout << str << std::endl;
            }
        }};
    }

    std::optional<int> dispatch(Model& model, std::string const& command)
    {
        // ...
    }
```

## 11.7 単体テストの変更 <a id="SS_11_7"></a>
このリファクタリングにより単体テストは以下のようになる
(以下のModelのデザインは不十分であるため、妥当な単体テストはできない)。

```cpp
    //  example/ref_async_r2/lib_ut.cpp 7

    TEST(RefAsyncR2, Model)
    {
        auto model = Model{};  // Modelのデザインが悪いために適切な単体テストは書けない

        model.ConvertStoreAsync("hehe");
    }

    TEST(RefAsyncR2, dispatch)
    {
        auto model = Model{};

        {
            auto exit_code = dispatch(model, "+abc");
            ASSERT_FALSE(exit_code);
        }
        {
            auto exit_code = dispatch(model, "+defg");
            ASSERT_FALSE(exit_code);
        }
        {
            auto exit_code = dispatch(model, ".");
            ASSERT_FALSE(exit_code);
        }
        {
            auto exit_code = dispatch(model, "+hijkl");
            ASSERT_FALSE(exit_code);
        }
        {
            auto exit_code = dispatch(model, "=");
            ASSERT_TRUE(exit_code);
            ASSERT_EQ(0, *exit_code);
        }
        {
            auto exit_code = dispatch(model, "?");
            ASSERT_TRUE(exit_code);
            ASSERT_NE(0, *exit_code);
        }
    }
```

## 11.8 MVCの導入 <a id="SS_11_8"></a>
非同期関数であるModel::ConvertStoreAsync()の完了がクラス外から捕捉できないことを一因として、
上記例のModelへの十分な単体テストができなかった。
この問題を解決し、単体テストのカバレッジを上げるために「[MVC](design_pattern.md#SS_9_5_2)」の構造を導入する。

```cpp
    //  example/ref_async_r3/main.cpp 5

    int main(int, char**)
    {
        auto view  = View{};
        auto model = Model{};
        model.Attach(view);
        auto controller = Controller{model};

        return controller.WatchInput();
    }
```

以下のファイルで、Modelの宣言、定義を行う。

```cpp
    //  example/ref_async_r3/model.h 10

    class Observer {
    public:
        Observer() = default;
        void Update(Model const& model) { update(model); }
        virtual ~Observer() = default;

    private:
        virtual void update(Model const& model) = 0;
    };

    class Model {
    public:
        Model() : thd_{[] {}}, strings_{}, observers_{} {}
        ~Model() { thd_.join(); }
        void                            ConvertStoreAsync(std::string const& input);
        void                            Attach(Observer& observer);
        void                            Detach(Observer& observer);
        std::vector<std::string> const& GetStrings() const { return strings_; }

    private:
        void notify() const;

        std::thread              thd_;
        std::vector<std::string> strings_;
        std::list<Observer*>     observers_;
    };
```

```cpp
    //  example/ref_async_r3/model.cpp 4

    void Model::ConvertStoreAsync(std::string const& input)
    {
        thd_.join();

        thd_ = std::thread{[this, input = input] {
            strings_.emplace_back(do_heavy_algorithm(input));
            notify();
        }};
    }

    void Model::Attach(Observer& observer) { observers_.emplace_back(&observer); }
    void Model::Detach(Observer& detach)
    {
        observers_.remove_if([&detach](Observer* observer) { return &detach == observer; });
    }

    void Model::notify() const
    {
        for (auto* observer : observers_) {
            observer->Update(*this);
        }
    }
```

以下のファイルで、Viewの宣言、定義を行う。

```cpp
    //  example/ref_async_r3/view.h 7

    class View : public Observer {
    private:
        virtual void update(Model const& model) override;
    };
```

```cpp
    //  example/ref_async_r3/view.cpp 3

    void View::update(Model const& model)
    {
        for (auto const& str : model.GetStrings()) {
            std::cout << str << std::endl;
        }
    }
```

以下のファイルで、Controllerの宣言、定義を行う。

```cpp
    //  example/ref_async_r3/controller.h 7

    class Controller {
    public:
        explicit Controller(Model& model) : model_{model} {}

        int WatchInput();

    private:
        std::optional<int> dispatch(std::string const& command);

        Model& model_;
    };
```

```cpp
    //  example/ref_async_r3/controller.cpp 6

    int Controller::WatchInput()
    {
        for (;;) {
            auto buffer = std::string{};

            if (std::getline(std::cin, buffer)) {
                if (auto exit_code = dispatch(buffer)) {
                    return *exit_code;
                }
            }
        }

        assert(false);
        return 0;
    }

    std::optional<int> Controller::dispatch(std::string const& command)
    {
        // ...
    }
```

## 11.9 単体テストの変更(単体テスト用クラス導入) <a id="SS_11_9"></a>
Observerから派生した下記のテスト用クラスViewTestを使うことにより、
ConvertStoreAsync()の完了が捕捉できるようになった。

```cpp
    //  example/h/ref_async_mock.h 10

    class ViewTest : public Observer {
    public:
        void WaitUpdate(uint32_t num) noexcept  // num回、updateが呼び出されるまでブロック
        {
            while (update_counter_ != num) {  // ポーリングは避けるべきだが、単体テストなら問題ない
                org_msec_sleep(100);
            }
        }

        uint32_t GetCount() const noexcept { return update_counter_; }

    private:
        virtual void update(Model const&) noexcept override { ++update_counter_; }

        std::atomic<uint32_t> update_counter_{0};
    };
```

これにより、Modelの単体テストは十分なレベルになったが、
下記の通り、ControllerやViewがstd::coutやstd::cinに依存しているために、
これらの単体テストの開発は困難である。

```cpp
    //  example/ref_async_r3/model_ut.cpp 10

    TEST(RefAsyncR3, Model)
    {
        auto view_test = ViewTest{};

        auto model = Model{};
        model.Attach(view_test);

        auto const input_model = std::vector<std::string>{"abc", "defg", "hijkl"};

        for (auto const& s : input_model) {
            model.ConvertStoreAsync(s);
        }

        view_test.WaitUpdate(input_model.size());

        ASSERT_EQ((std::vector<std::string>{"ABC", "DEFG", "HIJKL"}), model.GetStrings());
    }
```

```cpp
    //  example/ref_async_r3/view_ut.cpp 6

    TEST(RefAsyncR3, View)
    {
        auto view = View{};  // オブジェクト生成程度の単体テストしかできない
    }
```

```cpp
    //  example/ref_async_r3/controller_ut.cpp 8

    TEST(RefAsyncR3, Controller)
    {
        auto model      = Model{};
        auto controller = Controller{model};  // オブジェクト生成程度の単体テストしかできない
    }
```

## 11.10 DIの導入 <a id="SS_11_10"></a>
[DI(dependency injection)](design_pattern.md#SS_9_5_1)を導入することで、
Controller、Viewのstd::coutやstd::cinへの直接の依存を回避する。

下図は、DI導入前後でControllerによる「std::cinからの文字列読み込み」がどのように変更されたかを示す。

<!-- pu:plant_uml/refactoring_with_di.pu--><p><img src="data:image/png;base64,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" /></p>

DIの導入によりmain()は以下のようになる。

```cpp
    //  example/ref_async_r4/main.cpp 5

    int main(int, char**)
    {                                                   //   修正前のソースコード
        auto view  = View{std::cout};                   // > auto view  = View{};
        auto model = Model{};                           //   auto model = Model{};
        model.Attach(view);                             //   model.Attach(view);
        auto controller = Controller{model, std::cin};  // > auto controller = Controller{model};

        return controller.WatchInput();
    }
```

Modelについては、std::cout、std::cinへの依存はないので変更しない。
Viewについては、以下のようにstd::coutへの依存を削除する。

```cpp
    //  example/ref_async_r4/view.h 7

    class View : public Observer {
    public:
        explicit View(std::ostream& os) : Observer{}, os_{os} {}

    private:
        virtual void update(Model const& model) override;

        std::ostream& os_;
    };
```

```cpp
    //  example/ref_async_r4/view.cpp 3

    void View::update(Model const& model)
    {                                                 //   修正前のソースコード
        for (auto const& str : model.GetStrings()) {  //   for (auto const& str : model.GetStrings()) {
            os_ << str << std::endl;                  // >     std::cout << str << std::endl;
        }                                             //   }
    }
```

Controllerについても、以下のようにstd::cinへの依存を削除する。

```cpp
    //  example/ref_async_r4/controller.h 7

    class Controller {
    public:
        explicit Controller(Model& model, std::istream& is) : model_{model}, is_{is} {}

        int WatchInput();

    private:
        std::optional<int> dispatch(std::string const& command);

        Model&        model_;
        std::istream& is_;
    };
```

```cpp
    //  example/ref_async_r4/controller.cpp 6

    int Controller::WatchInput()
    {
        for (;;) {
            auto buffer = std::string{};

            //                                //  修正前のソースコード
            if (std::getline(is_, buffer)) {  //  if (std::getline(std::cin, buffer)) {
                if (auto exit_code = dispatch(buffer)) {
                    return *exit_code;
                }
            }
        }

        assert(false);
        return 0;
    }

    std::optional<int> Controller::dispatch(std::string const& command)
    {
        // ...
    }
```

以上のように、

* Controllerは、インスタンスstd::cinへの依存から、std::istream型への依存へ
* Viewは、インスタンスstd::coutへの依存から、std::ostream型への依存へ

と改善された(一般にグローバルオブジェクトへの依存よりも型への依存の方が柔軟性に勝る)。
なお、std::cin、std::cout、std::istream、std::ostream等の継承関係は以下の通りであるため、
このような変更が可能となった。

<!-- pu:plant_uml/basic_ios.pu--><p><img src="data:image/png;base64,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N2jQIDg4ePr06e7u7uPGjaPCK1euTJw4kcrt7e3PnDnDteQTNykp6bXXXnu2sioIl6IBtLBqyJAhfn5+3LzaLSKnAWQLOQ1KJMxpN0838evTsduXU043/KARXzJ96RdjIyasObSeafltahzz+vSYMWP4fyMiIpo0aUIzOTk5tEI+F3v37s3lNKe4uDgwMNDf35/7l0/crKwsWur48eN8y4KCAn6ewS917NgxWurEiRN8lZub27Bhw/5qKtoichpAtpDToETCnB4dMkb8fu/EE5v//tLfX3nt1eSTW7mSfzX5N4Xfij2rmZaffzGFeb/3G2+8sW3bNpo/derUu+++yw2vf/rpp1q1anHPNm/evJnaDBo06OzZszTS5Z7WppV06tSJW4nwHWHe3t5t2rShlmVlZYsXL27UqBH36rKYcClPT08PDw/u5ef58+e/+uqrFN40X9kWkdMAsoWcBiUS5vSuPbsc3dow6UuTlYM1BfPMlXNofsXeuBdrvfj2O28zbbae2UGJKPz8dLdu3ZYuXerl5fXOO++89dZboaGhpaWlXFV0dPSbb75Zp06djh07bty4sXv37oWFhcHBwbVr16bGVlZW/Li5X79+8+bN4+ZpAP2f//znH//4xyuvvNK6detDhw5x5WLMUkFBQXUq0FL8Laxsi8hpANlCToMSCXOaxqnu7dzF30cWEh1KOf1/jRoMmzbSws6S5rsN6M60WbxmCY131f4itdpRL7UUl1OQ37x5kykU4xe8qs7zbf9SXFzMFqnbInIaQLaQ06BEwpwmaTvSbO3txN/v7d2t/QvPNLF4P/7Icx+e3no8zcnJifl+byPopQ7bqJqQ0wCyhZwGJWJymoRMmujb9SPx72V9sSpiwKRBE2PCErI2CctTT+8I7BkYFhbGrMdEIacBZAs5DUokzumSkpJevT/p4N9Rm9+fTs16GtJ9+vTB708DgKEhp0GJxDmtqojq0NBQe0f7GUtmibOZm7ae2bF4zRInJycaSZtNSKuQ0wAyhpwGJVKb05z09HQvLy83D/exU8fHbloatz9+y+m09QcTVqeu+XzmFE9PT6o1/mvShoacBpAt5DQokYacVlW8K3vv3r3h4eG+vr62trb169envzRPJVSu9t3dpg45DSBbyGlQIs05rUDIaQDZQk6DEiGnGchpANlCToMSIacZyGkA2UJOgxIh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" /></p>

## 11.11 全クラスの単体テスト <a id="SS_11_11"></a>
これまでの改善によりModel、View、Controllerすべてに妥当な単体テストをすることが可能となった。

```cpp
    //  example/ref_async_r4/model_ut.cpp 11

    TEST(RefAsyncR4, Model)
    {
        auto view_test   = ViewTest{};
        auto ss_view     = std::ostringstream{};
        auto view_normal = View{ss_view};
        auto model       = Model{};

        model.Attach(view_normal);
        model.Attach(view_test);

        auto const input_model = std::vector<std::string>{"abc", "defg", "hijkl"};

        for (auto const& s : input_model) {
            model.ConvertStoreAsync(s);
        }

        view_test.WaitUpdate(input_model.size());

        ASSERT_EQ((std::vector<std::string>{"ABC", "DEFG", "HIJKL"}), model.GetStrings());

        auto ss_expect = std::ostringstream{};  // viewのテスト
        ss_expect << "ABC" << std::endl;
        ss_expect << "ABC" << std::endl << "DEFG" << std::endl;
        ss_expect << "ABC" << std::endl << "DEFG" << std::endl << "HIJKL" << std::endl;

        ASSERT_EQ(ss_expect.str(), ss_view.str());
    }
```

```cpp
    //  example/ref_async_r4/view_ut.cpp 4

    TEST(RefAsyncR4, View)
    {
        // model/controllerの単体テストで代用
    }
```

```cpp
    //  example/ref_async_r4/controller_ut.cpp 11

    TEST(RefAsyncR4, Controller)
    {
        auto view_test   = ViewTest{};
        auto ss_view     = std::ostringstream{};
        auto view_normal = View{ss_view};
        auto model       = Model{};

        model.Attach(view_test);
        model.Attach(view_normal);

        auto ss = std::stringstream{};

        ss << "+abc" << std::endl;
        ss << "+defg" << std::endl;
        ss << "." << std::endl;
        ss << "+hijkl" << std::endl;
        ss << "=" << std::endl;

        auto controller = Controller{model, ss};

        ASSERT_EQ(0, controller.WatchInput());

        auto const exp_model = std::vector<std::string>{"ABC", "DEFG", "HIJKL"};
        view_test.WaitUpdate(exp_model.size());

        ASSERT_EQ(exp_model, model.GetStrings());

        auto ss_expect = std::ostringstream{};
        ss_expect << "ABC" << std::endl;
        ss_expect << "ABC" << std::endl << "DEFG" << std::endl;
        ss_expect << "ABC" << std::endl << "DEFG" << std::endl << "HIJKL" << std::endl;

        ASSERT_EQ(ss_expect.str(), ss_view.str());

        // エラー入力テスト
        ss << "?" << std::endl;
        ASSERT_NE(0, controller.WatchInput());
    }
```

## 11.12 自動統合テストのための仕様追加 <a id="SS_11_12"></a>
リファクタリングの説明に使用したソースコード(「[リファクタリング](process_and_infra.md#SS_10_2_2)」参照)は、

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

## 11.13 自動統合テストのためのソースコード変更 <a id="SS_11_13"></a>
前述したオプションを備えた実装は、以下のようになる。

```cpp
    //  example/ref_async_r5/main.cpp 10

    namespace {

    void how_to_use(std::string_view program)
    {
        std::cerr << program << " [OPTIONS]" << std::endl;
        std::cerr << "   -i <input-file>" << std::endl;
        std::cerr << "   -o <output-file>" << std::endl;
    }
    }  // namespace

    int main(int argc, char** argv)
    {
        auto ret = getopt(argc, argv);
        if (!ret) {
            how_to_use(argv[0]);
            return __LINE__;
        }

        auto ios = IOStreamSelector{std::move(ret->ifile), std::move(ret->ofile)};

        if (!ios.Open()) {
            how_to_use(argv[0]);
            return __LINE__;
        }
        //                                                      //   修正前のソースコード
        auto view  = View{ios.GetOStream()};                    // > auto view  = View{std::cout};
        auto model = Model{};                                   //   auto model = {};
        model.Attach(view);                                     //   model.Attach(view);
        auto controller = Controller{model, ios.GetIStream()};  // > auto controller
                                                                //       = Controller{model, std::cin};

        return controller.WatchInput();
    }
```
```cpp
    //  example/ref_async_r5/arg.h 5

    struct opt_result {
        std::string ifile;
        std::string ofile;
    };

    std::optional<opt_result> getopt(int argc, char* const* argv);
```
```cpp
    //  example/ref_async_r5/arg.cpp 7

    std::optional<opt_result> getopt(int argc, char* const* argv)
    {
        auto opt   = int{};
        auto ifile = std::string{};
        auto ofile = std::string{};

        // ...
        return opt_result{std::move(ifile), std::move(ofile)};
    }
```

IOStreamSelectorと単体テスト用に導入した「[DI(dependency injection)](design_pattern.md#SS_9_5_1)」構造により、
std::istream、std::ostreamのインスタンスを選択できるようになった。

IOStreamSelectorは以下のようになる。

```cpp
    //  example/ref_async_r5/arg.h 14

    class IOStreamSelector {
    public:
        IOStreamSelector(std::string ifile, std::string ofile)
            : ifile_{std::move(ifile)}, ifs_{}, is_{nullptr}, ofile_{std::move(ofile)}, ofs_{}, os_{nullptr}
        {
        }

        bool          Open();
        std::istream& GetIStream();
        std::ostream& GetOStream();

    private:
        // ...
    };
```
```cpp
    //  example/ref_async_r5/arg.cpp 36

    namespace {
    template <typename FSTREAM, typename IOSTREAM>
    bool select_iostream(std::string const& filename, FSTREAM& fs, IOSTREAM& cin_cout, IOSTREAM*& output)
    {
        output = &cin_cout;

        if (filename.size() != 0) {
            fs.open(filename);
            if (!fs) {
                return false;
            }
            output = &fs;
        }

        return true;
    }
    }  // namespace

    bool IOStreamSelector::Open()
    {
        if (!select_iostream(ifile_, ifs_, std::cin, is_)) {
            return false;
        }

        return select_iostream(ofile_, ofs_, std::cout, os_);
    }

    std::istream& IOStreamSelector::GetIStream()
    {
        assert(is_ != nullptr);

        return *is_;
    }

    std::ostream& IOStreamSelector::GetOStream()
    {
        assert(os_ != nullptr);

        return *os_;
    }
```

## 11.14 自動統合テスト用ソースコード変更のための単体テスト <a id="SS_11_14"></a>
追加機能に対する単体テストを以下に示す。
なお、新規単体テストはファイルの生成、書き込み、読み込みを行うため、

* 単体テストの実行前に、結果に影響を与えるファイルを削除する
* 単体テストの実行後に、単体テストで生成したファイルを削除する

を行う必要がある。

* 前者を行うのがSetUp()
* 後者を行うのがTearDown()

である。

```cpp
    //  example/ref_async_r5/arg_ut.cpp 18

    class Refactorin_5 : public ::testing::Test {  // google testクラス
    protected:
        virtual void SetUp() noexcept override
        {
            remove_file(ofilename);  // ファイルがあると、テストがエラーするので。
            remove_file(ifilename);
        }

        virtual void TearDown() noexcept override
        {
            remove_file(ofilename);  // ローカルリポジトリにゴミを残さない。
            remove_file(ifilename);
        }

        static void remove_file(std::string const& filename) noexcept
        {
            if (std::filesystem::exists(filename)) {
                std::filesystem::remove(filename);
            }
        }
    };

    TEST_F(Refactorin_5, IOStreamSelector)
    {
        {
            auto ios = IOStreamSelector{"", ofilename};

            ASSERT_TRUE(ios.Open());
            ASSERT_TRUE(&std::cin == &ios.GetIStream());
        }
        ASSERT_TRUE(std::filesystem::exists(ofilename));

        {
            {  // テスト用ファイルの作成
                auto ofs = std::ofstream{};

                ofs.open(ifilename);
                ASSERT_TRUE(ofs);

                ofs << "test";
            }
            ASSERT_TRUE(std::filesystem::exists(ifilename));

            auto ios = IOStreamSelector{ifilename, ""};

            ASSERT_TRUE(ios.Open());
            ASSERT_TRUE(&std::cout == &ios.GetOStream());

            auto file_contents = std::string{};

            ios.GetIStream() >> file_contents;
            ASSERT_EQ("test", file_contents);
        }
    }

    TEST_F(Refactorin_5, getopt)
    {
        {
            char        p[]    = "p";
            char* const argv[] = {p};

            auto ret = getopt(array_length(argv), argv);

            ASSERT_TRUE(ret);
            ASSERT_EQ("", ret.value().ifile);
            ASSERT_EQ("", ret.value().ofile);
        }
        // ...
    }
```

## 11.15 自動統合テストの実装 <a id="SS_11_15"></a>
ref_async_r5に追加された機能をスクリプト言語(下記例ではbash)等から利用することで、
下記のような自動統合テスト(非手作業統合テスト)を開発することができる。
入力文字列や入力タイミングのバリエーションを増やすこと等によってこの方法を発展させれば、
堅固な自動統合テストにすることも可能である。

```sh
    //  example/ref_it/it.sh 45

    # $IFILEの作成
    cat << IFILE_END > $IFILE
    +abcdef
    +ddd
    +ffff
    =
    IFILE_END

    # expectの生成
    gen_expect "ABCDEF" "DDD" "FFFF" > $OFILE_EXP

    $TARGET -i $IFILE -o $OFILE_ACT

    declare -r diff_result1=$(diff $OFILE_EXP $OFILE_ACT)

    # $TARGETが正常動作すれば、文字列diff_result1の長さは0
    [[ -n "$diff_result1" ]] && exit $LINENO
```

---

[インデックス](seminer_intro.md#SS_1_2)/[章の先頭](refactring_expamples.md#SS_11)/[次の章](concurrency.md#SS_12)

---



<a id="SS_11_999"></a>

