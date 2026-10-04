<!-- practical/md/coding_style.md -->
# コーディングスタイル <a id="SS_5"></a>
スタイルが統一されていないソースコードは、それだけで可読性に劣るため、
スタイルの統一は重要であるが、それにこだわりすぎれば、不毛な宗教論争が発生してしまう。
そのようなロスを避けスタイルを定めたとしても、その遵守が目視、手作業によって行われるならば、
これもまた新たなロスになる。

こういった状況に陥ることなくソースコードの記述スタイルを統一するために、
本ドキュメントでは「clang-formatを使い、デフォルトのスタイルを適切に定め、
必要なら多少のカスタマイズを行い、それに従う」ことを推奨する。

このドキュメントのコード例は、以下に示したスタイルを採用している。

- [コード全体のスタイル](coding_style.md#SS_5_1)
- [AAAスタイル](coding_style.md#SS_5_2_1)(すべてではないが、このスタイルが自然な場合)    
- [east-const](coding_style.md#SS_5_2_2)
- [Trailing Underscore(末尾アンダースコア)](coding_style.md#SS_5_2_4)

___

__この章の構成__

[コード全体のスタイル](coding_style.md#SS_5_1)  
&emsp;[インデント](coding_style.md#SS_5_1_1)  
&emsp;[ブロック(波括弧({}))](coding_style.md#SS_5_1_2)  
&emsp;[関数シグネチャ内の'()'](coding_style.md#SS_5_1_3)  
&emsp;[クラスのアクセスレベル](coding_style.md#SS_5_1_4)  
&emsp;[スペース](coding_style.md#SS_5_1_5)  
&emsp;[三項演算子のスタイル](coding_style.md#SS_5_1_6)  
&emsp;[ポインタ型やリファレンス型インスタンスの宣言、定義の\*や&の場所](coding_style.md#SS_5_1_7)  
&emsp;[行数・桁数](coding_style.md#SS_5_1_8)  
&emsp;[ブロックの論理レベル](coding_style.md#SS_5_1_9)  
&emsp;[名前空間](coding_style.md#SS_5_1_10)  
&emsp;[clang-format](coding_style.md#SS_5_1_11)  

[局所スタイル](coding_style.md#SS_5_2)  
&emsp;[AAAスタイル](coding_style.md#SS_5_2_1)  
&emsp;[east-const](coding_style.md#SS_5_2_2)  
&emsp;[west-const](coding_style.md#SS_5_2_3)  
&emsp;[Trailing Underscore(末尾アンダースコア)](coding_style.md#SS_5_2_4)  

[ケース記法](coding_style.md#SS_5_3)  
&emsp;[スネークケース(snake_case)](coding_style.md#SS_5_3_1)  
&emsp;[アッパースネークケース(UPPER_SNAKE_CASE)](coding_style.md#SS_5_3_2)  
&emsp;[アッパーキャメルケース(UpperCamelCase)](coding_style.md#SS_5_3_3)  
&emsp;[ロワーキャメルケース(lowerCamelCase)](coding_style.md#SS_5_3_4)  
&emsp;[ケバブケース(kebab-case)](coding_style.md#SS_5_3_5)  
  
  

[インデックス](comprehensive_intro.md#SS_1_3)に戻る。  

___

## コード全体のスタイル <a id="SS_5_1"></a>
以下は、clang-formatを使えない場合のスタイルの指針である。

### インデント <a id="SS_5_1_1"></a>
#### インデント用文字 <a id="SS_5_1_1_1"></a>
* 1インデントは、4つのスペース文字で表す
  (ハードタブはビューアにより見え方が変わるため使用しない)。

```cpp
    //  example/etc/coding_style.cpp 13

    int32_t f0() noexcept
    {
      auto var_x = 0;          // NG インデントが2スペース
      return var_x;
    }

    int32_t f1() noexcept
    {
            auto var_x = 0;    // NG インデントが8スペース
            return var_x;
    }

    int32_t f2() noexcept
    {
    	int32_t var_x{0};        // NG  インデントがハードタブ
    	return var_x;
    }

    int32_t f3() noexcept
    {
        auto var_x = 0;        // OK
        return var_x;
    }
```

#### if、for、while、do-whileのインデント <a id="SS_5_1_1_2"></a>
* if、for、while、do-whileに付随する文は、
  if、for、while、do-whileより1インデント下げる(「[ブロック(波括弧({}))](coding_style.md#SS_5_1_2)」等を参照)。

#### ブロックのインデント <a id="SS_5_1_1_3"></a>
* ブロック内部の文はブロック開始の'{'より1インデント下げる。

#### case、defaultのインデント <a id="SS_5_1_1_4"></a>
* case、defaultのインデントはswitchと合わせる。
* case、defaultに続く文のインデントは一つ下げる。 
* case、defaultの次の文は改行後に書く。
* case内をブロック化するために { ... } で囲む場合、'{'は:の後に1スペースを置き、
  その直後に配置する。'}'はcaseと同じカラムに置く。

```cpp
    //  example/etc/coding_style.cpp 47

    switch (var_a) {
    case 1: {                   // OK
        var_b = 1;
        break;
    }
        case 2:                 // NG caseのインデントはswitchと同じカラム
            {                   // NG {は"case 2: "の直後
                var_b = 2;
                break;
            }                   // NG caseと同じカラム
    case 3:
    var_b = 3;                  // NG caseから1インデント下げる
    break;
    case 4: var_b = 4;          // NG caseの行にそのまま処理を続けない
        break;
    default:                    // OK
        break;
    }
```

### ブロック(波括弧({})) <a id="SS_5_1_2"></a>
* 文に続く'{'は、文の後に1スペースを置き、その直後に配置する。
* '}'の後に続く文は'}'の直後に改行を入れ、同じカラムから書き始める。
* 関数宣言に続く'{'は、関数宣言の直後に改行し、直前の行の先頭と同じカラムに '{' を配置する。

```cpp
    //  example/etc/coding_style.cpp 76

    void f0(int32_t var_x, int32_t* var_y) noexcept { // NG {の前に改行
        if (var_x == 0)
        {                                   // NG
            *var_y = 0;
        }
        else
        {                                   // NG
            *var_y = 10;
        }
        return;
    }

    void f1(int32_t var_x, int32_t* var_y) noexcept
    {                                       // OK
        if (var_x == 0) {                   // OK
            *var_y = 0;
        }
        else {                              // OK
            *var_y = 1;
        }
        return;
    }

    void f2(int32_t var_x, int32_t* var_y) noexcept
    {                                       // OK
        if (var_x > 0)                      // NG )の後の改行不要
        {
            *var_y = 0;
        }

        if (var_x == 0)                     // NG )の後の改行不要
        {
            *var_y = 0;
        }
        else {                              // OK
            var_x = 3;
        }

        if (var_x == 0)                     // NG
        {
            *var_y = 0;
        } else                              // NG else前に改行。後ろは1スペース開けて{
        {                                   //    
            var_x = 3;
        }

        if (var_x == 0)                     // NG if文と同じ行に{
        {
            *var_y = 0;
        }
        else                                // NG 
        {
            *var_y = 3;
        }

        return;
    }
```

### 関数シグネチャ内の'()' <a id="SS_5_1_3"></a>
* 関数シグネチャ内の'('は関数名の直後に置く。
* 行が長すぎる等より関数を複数行で宣言する場合、')'は最後の仮引数の直後か、独立の行に置く。
* 全体が一行に収まるときは、そのまま一行に書く。

```cpp
    //  example/etc/coding_style.cpp 140

    void function();            // OK
    void function(int32_t foo,  // OK
                  int32_t bar);
    void funcction(             // OK 
            int32_t foo,
            int32_t bar
            );
    void function(int32_t hoge
                  );            // NG
    void function               // NG (は関数の直後
            (
             int32_t hoge,
             char  foo
             );
```

### クラスのアクセスレベル <a id="SS_5_1_4"></a>
* メンバ関数等のネストが深くなりすぎるため、クラスのアクセスレベルはインデントしない。

```cpp
    //  example/etc/coding_style.cpp 161

    class A {
        public:         // NG
            void B();
    private:            // OK
        void C();
    };
```

### スペース <a id="SS_5_1_5"></a>
#### 文の後 <a id="SS_5_1_5_1"></a>
* [定義] ステートメントキーワードとは、for、while、do-while、switch、try、if、else等を指す。
* ステートメントキーワードの後には1スペースを入れる。
* 関数名の直後にはスペースを入れない。

```cpp
    //  example/etc/coding_style.cpp 177

    for (;;) {                          // OK forの後ろにはスペース
        // ...
    }

    for(;;){                            // NG forの後ろにはスペース
        // ...
    }

    try {                               // OK tryの後ろにはスペース
        // ...
    }
    catch (std::exception const& e) {   // OK catchの後ろと{の前にはスペース
        // ...
    }

    try{                                // NG tryの後ろにはスペース
        // ...
    }
    catch(std::exception const& e){     // NG catchの後ろと{の前にはスペース
        // ...
    }

    g();                                // OK 関数の後ろにはスペース無し

    g ();                               // NG
```

#### コンマの後   <a id="SS_5_1_5_2"></a>
* 行最後の文字でないコンマ(,)の後には1スペースを入れる。

```cpp
    //  example/etc/coding_style.cpp 220

    for (int32_t i{0}, j{0}; i + j < 10; ++i, ++j) {  // OK
        // ...
    }

    for (int32_t i{0},j{0}; i + j < 10; ++i,++j) {    // NG ,の後ろにはスペース
        // ...
    }

    g("%d print tooooooooooooooooooooooooooooooooo many characters.",
      a);                                // OK ,の直後、スペース無し ↑
```

#### 単項演算子、二項演算子、三項演算子の前後 <a id="SS_5_1_5_3"></a>
* 単項演算子とオペランドの間にはスペースを入れない。
* []、->、ピリオド(.)、コンマ(,)は除き、 二項演算子、三項演算子の前後には1スペースを入れる。

```cpp
    //  example/etc/coding_style.cpp 241

    var_a=0;                        // NG
    var_a = 0;                      // OK

    var_b[ 1 ] = 1;                 // NG
    var_b[2] = 1;                   // OK

    var_c+=3;                       // NG
    var_c += 3;                     // OK

    if(var_a == *var_b) {           // OK
        return var_d .c_str();      // NG
    }
    else {
        return var_d.c_str() + 1;   // OK
    }
```

#### 不要なブランク文字 <a id="SS_5_1_5_4"></a>
* スペース文字は、セパレータとして適切に使用するためのものである。
  従って、行末に不要なブランクキャラクタを置かない。
* ファイル末に不要な改行を入れない。

### 三項演算子のスタイル <a id="SS_5_1_6"></a>
* 三項演算子は以下のように書く。

```cpp
    //  example/etc/coding_style.cpp 265

    auto ret = condition ? x : y;  // ワンライナーが基本

    auto ret2 = (a > b) ? x        // 行が長すぎる場合
                        : y;
```

* 以下のような表記方法も認められる。この表記は、switch文やif-else-if文と同様に使える。

```cpp
    //  example/etc/coding_style.cpp 278

    auto max = (a > b) ? a :
               (b > c) ? b : 
               (c > d) ? c : 
               // ...
                         x;
```

### ポインタ型やリファレンス型インスタンスの宣言、定義の\*や&の場所 <a id="SS_5_1_7"></a>
* ポインタ型やリファレンス型インスタンスの宣言、定義の\*や&は型の直後に配置する。

```cpp
    //  example/etc/coding_style.cpp 299

    char* a;  // OK
    char *b;  // NG 型の直後に*

    int32_t& j{i};  // OK
```

* 一つの文で複数の変数の定義をしない。

```cpp
    //  example/etc/coding_style.cpp 306

    char*   c, d;  // NG dはchar*ではない
    int32_t e, f;  // NG
```

### 行数・桁数 <a id="SS_5_1_8"></a>
#### 関数の行数 <a id="SS_5_1_8_1"></a>

* 関数の行数({から}の間)は30行までに収める。
* 「テストシーケンスを一つの関数に押し込める」という方法は一般的なため、
  単体テストのための関数に対しては、この制限を適用しない。

#### 行のカラム数 <a id="SS_5_1_8_2"></a>
* 1行の最長は コメントを含めて100カラムとする。100カラムを超える行は、適切な位置に改行を入れる。
* 以下に100カラムを超える行のスタイルを例示する(縦にそろえることを重要視する)。

    * 関数の宣言

    ```.cpp
            //  example/etc/coding_style.cpp 317

            int32_t f(int32_t arg1,  // OK
                      int32_t arg2,
                      int32_t arg3) noexcept;

            int32_t g(  // OK
                int32_t arg1,
                int32_t arg2,
                int32_t arg3) noexcept;
    ```

    * 定義を伴う関数の宣言

    ```.cpp
            //  example/etc/coding_style.cpp 328

            int32_t f(int32_t arg1,  // OK
                      int32_t arg2,
                      int32_t arg3) noexcept
            {
                return arg1 + arg2 + arg3;
            }

            int32_t g(  // OK
                int32_t arg1,
                int32_t arg2,
                int32_t arg3) noexcept
            {
                return arg1 + arg2 + arg3;
            }
    ```

    * 関数呼び出し

    ```.cpp
            //  example/etc/coding_style.cpp 348

            int32_t ret{f(arg1,
                          arg2,
                          arg3)};
    ```

    * 論理演算子は行末ではなく、行頭に配置(行中にあってもよい)

    ```.cpp
            //  example/etc/coding_style.cpp 354

            if (((arg1 == arg2) && (arg2 == arg3))
              || (arg3 == 3)) {
                ret = 0;
            }
    ```

    * 代入の'='の前で改行し、'='を行頭に持ってくる。 

    ```.cpp
            //  example/etc/coding_style.cpp 362

            auto some_looooooooooooooooooooog_variable  // 式の最後までが100カラムに入らない場合
                 = arg1 + 1;
    ```

    * 長い文字列

    ```.cpp
            //  example/etc/coding_style.cpp 368

            std::cout << "foobarfubarhoge"
                         "hugahogehoge"
                         "1234567890";  // 長い文字列は分割
    ```

### ブロックの論理レベル <a id="SS_5_1_9"></a>
* 各ブロックの抽象度を揃える。

```cpp
    //  example/etc/coding_style.cpp 394

    void DoSomethingNG() noexcept  // NG
    {
        Buffer_t* buff{new Buffer_t};           // NG 抽象度が低すぎる
                                                //
        buff->len  = 1024;                      //
        buff->buff = new uint8_t[buff->len];    //
        std::memset(buff->buff, 0, buff->len);  //

        ReadFromStream(*buff);
        WriteToStorage(*buff);

        DestroyBuffer(buff);
    }

    void DoSomethingOK() noexcept  // OK
    {
        Buffer_t* buff = PrepareBuffer();

        ReadFromStream(*buff);
        WriteToStorage(*buff);

        DestroyBuffer(buff);
    }
```

### 名前空間 <a id="SS_5_1_10"></a>
* 一般に名前空間定義の区間は縦に長いため、
  最後に必ず名前空間の終わりであることを示すためのコメントを記述する。
* ネストが深くなりすぎるため、名前空間用のインデントはしない。

```cpp
    //  example/etc/coding_style.cpp 423
    namespace event {

    class A {  // インデントなし
        // ...
    };

    // ...

    namespace {

    void f() noexcept;  // インデントなし
    // ...

    }  // namespace

    // ...
    }  // namespace event
```

### clang-format <a id="SS_5_1_11"></a>
参考のために、サンプルソースコードに適用している.clang-formatを例示する。

```
    //  example/.clang-format 1

    # default
    BasedOnStyle: Google

    # indents
    AccessModifierOffset: -4
    IndentCaseLabels: false
    IndentWidth: 4
    NamespaceIndentation: None

    # alignment
    AlignConsecutiveAssignments: true
    AlignConsecutiveDeclarations: true
    AlignOperands: true
    AlignTrailingComments: true

    #IncludeBlocks: Regroup
    IncludeCategories:
      - Regex:           '^<.*\.h>'
        Priority:        -10
      - Regex:           '^<'
        Priority:        -9
      - Regex:           'gtest_wrapper\.h'
        Priority:        -8
      - Regex:           'h/.*'
        Priority:        -7 
      - Regex:           '.*'
        Priority:        -6 
    SortIncludes: true

    # new line
    AllowShortCaseLabelsOnASingleLine: false
    AllowShortFunctionsOnASingleLine: All
    AllowShortBlocksOnASingleLine: false
    BreakBeforeBinaryOperators: All
    BreakBeforeBraces: Custom
    BraceWrapping:
        AfterClass: false
        AfterControlStatement: false
        AfterEnum: false
        AfterFunction: true
        AfterNamespace: false
        AfterObjCDeclaration: false
        AfterStruct: false
        AfterUnion: false
        AfterExternBlock: false
        BeforeCatch: true
        BeforeElse: true
    ColumnLimit: 120

    # space
    DerivePointerAlignment: false
    PointerAlignment: Left
    QualifierAlignment: Right # east-const style

```

---

## 局所スタイル <a id="SS_5_2"></a>

### AAAスタイル <a id="SS_5_2_1"></a>
このドキュメントでのAAAとは、単体テストのパターンarrange-act-assertではなく、
almost always autoを指し、
AAAスタイルとは、「可能な場合、型を左辺に明示して変数を宣言する代わりに、autoを使用する」
というコーディングスタイルである。
この用語は、Andrei Alexandrescuによって造られ、Herb Sutterによって広く推奨されている。

特定の型を明示して使用する必要がない場合、下記のように書く。

```cpp
    //  example/etc/aaa.cpp 11

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
    //  example/etc/aaa.cpp 51

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
    //  example/etc/aaa.cpp 94

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
    //  example/etc/aaa.cpp 118

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
    //  example/etc/aaa.cpp 145

    template <typename F, typename T>
    auto apply_0(F&& f, T value)
    {
        return f(value);
    }
```

ただし、インライン関数や関数テンプレートが複雑な下記のような場合、
AAAスタイルは出来る限り避けるべきである。

```cpp
    //  example/etc/aaa.cpp 153

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
    //  example/etc/aaa.cpp 180

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
    //  example/etc/aaa.cpp 194

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

---

### east-const <a id="SS_5_2_2"></a>
east-constとは、`const`修飾子を修飾する型要素の右側(east＝右)に置くコーディングスタイルのこと。
つまり「`const`はどの対象を修飾するか」を明確にするため、被修飾対象の直後に const を書くのが特徴である。

このスタイルは、C言語由来の「`const`を左に置く」スタイル([west-const](coding_style.md#SS_5_2_3))に比べ、
テンプレート展開や型推論の際に一貫性があり、C++コミュニティではしばしば論理的・直感的と評価されている。

```cpp
    //  example/etc/east_west_const.cpp 12

    char              str[] = "hehe";  // 配列strに書き込み可能
    char const*       str0  = str;     // str0が指すオブジェクトはconstなので、*str0への書き込み不可
    char* const       str1  = str;     // str1がconstなので、str1への代入不可
    char const* const str2  = str;     // *str2への書き込み不可、str2への代入不可

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

なお、このドキュメントでは、このスタイルを採用している。

---

### west-const <a id="SS_5_2_3"></a>
west-constとは、`const`修飾子を型の左側(west＝左)に置くコーディングスタイルのこと。
C言語からの伝統的な表記法であり、多くの標準ライブラリや教科書でも依然としてこの書き方が用いられている。

可読性は慣れに依存するが、`const`の位置が一貫しないケース(`T* const`など)では理解しづらくなることもある。

```cpp
    //  example/etc/east_west_const.cpp 37

    char              str[] = "hehe";  // 配列strに書き込み可能
    char const*       str0  = str;     // str0が指すオブジェクトはconstなので、*str0への書き込み不可
    char* const       str1  = str;     // str1がconstなので、str1への代入不可
    char const* const str2  = str;     // *str2への書き込み不可、str2への代入不可

    auto lamda = [](char const(&str_ref)[5]) {  // str_refは配列へのconstリファレンス
        int ret = 0;

        for (const char& a : str_ref) {  // aはchar constリファレンス
            ret += a;
        }
        return ret;
    };
```

このスタイルは「west constスタイル」または「左側const」と呼ばれ、
C言語文化圏での可読性・慣習を重視する場合に採用されることが多い。

---

### Trailing Underscore(末尾アンダースコア) <a id="SS_5_2_4"></a>
Trailing underscoreとは、C++においてメンバー変数名の末尾にアンダースコア
(\_)を付ける命名規約である。例えば、data_、count_、name_ のように記述する。

__採用の背景__  
この規約が広まった主な理由は以下の通りである：  

* 予約識別子との衝突回避 - 先頭のアンダースコアは標準で予約されている(\_+大文字、\_\_など)ため使用できない
* 可読性の向上 - プレフィックス方式(m_dataなど)と比べて、自然な語順を保てる
* コンストラクタでの利便性 - 初期化リストで `data_{data}` のようにパラメータ名と区別しやすい

__主要な採用例__

* Google C++ Style Guide
* Scott Meyers著「Effective C++」シリーズ
* 多くのオープンソースプロジェクト
* このドキュメント

この規約により、メンバー変数とローカル変数を明確に区別でき、コードの保守性が期待できる。


---

## ケース記法 <a id="SS_5_3"></a>
C++の識別子の命名規則(Naming convention)を以下のようにリストアップする。
筆者の好みから、このドキュメントのコード例では、アッパーキャメルケースを採用している。

プロジェクトのルールで記法をで統一しなければ、ファイルごとにバラバラになってしまうことがある。
言うまでもなく、これは好ましいことではないため、コーディングを始める前に記法を定めるべきである。

* [スネークケース(snake_case)](coding_style.md#SS_5_3_1)
* [アッパースネークケース(UPPER_SNAKE_CASE)](coding_style.md#SS_5_3_2)
* [アッパーキャメルケース(UpperCamelCase)](coding_style.md#SS_5_3_3)
* [ロワーキャメルケース(lowerCamelCase)](coding_style.md#SS_5_3_4)
* [ケバブケース(kebab-case)](coding_style.md#SS_5_3_5)

### スネークケース(snake_case) <a id="SS_5_3_1"></a>
識別子はすべて小文字のアルファベットおよび数字で構成し、単語の区切りにはアンダースコア（`_`）を用いる。
先頭文字は小文字のアルファベットでなければならない。  

この記法では、識別子を形成する文字列は、以下の正規表現に適合する。

```
    [a-z][a-z0-9]*(_[a-z0-9]+)*
```

この記法は、マクロを除いた標準ライブラリの識別子に使用されている。

識別子例：  

* sensor_value
* max_retry_count
* uart_tx_buffer

なお、この記法は、[cpprefjp - C++日本語リファレンス](https://cpprefjp.github.io/)に採用されている。

### アッパースネークケース(UPPER_SNAKE_CASE) <a id="SS_5_3_2"></a>
識別子はすべて大文字のアルファベットおよび数字で構成し、単語の区切りにはアンダースコア（`_`）を用いる。
先頭文字は大文字のアルファベットでなければならない。  

この記法では、識別子を形成する文字列は、以下の正規表現に適合する。

```
    [A-Z][A-Z0-9]*(_[A-Z0-9]+)*
```

この記法は、標準ライブラリのマクロに使用されている。

識別子例：  

* MAX_BUFFER_SIZE
* DEFAULT_TIMEOUT_MS
* CAN_TX_QUEUE_DEPTH

### アッパーキャメルケース(UpperCamelCase) <a id="SS_5_3_3"></a>
識別子を構成する各単語の先頭文字を大文字とし、残りの文字は小文字とする。単語の区切りを示す区切り文字は使用しない。
先頭文字は大文字のアルファベットでなければならない。  

この記法では、識別子を形成する文字列は、以下の正規表現に適合する。

```
    [A-Z][a-z0-9]*([A-Z][a-z0-9]*)*
```

プログラミング言語 Pascal で広く採用されていたことから、パスカルケース（PascalCase）と呼ばれることがある。
このドキュメントでは、この記法を採用して、 コードの例示を行っている。

識別子例：

* MotorController
* SensorDataParser
* UartTransmitBuffer

### ロワーキャメルケース(lowerCamelCase) <a id="SS_5_3_4"></a>

識別子を構成する最初の単語はすべて小文字とし、以降の各単語の先頭文字のみを大文字とする。
単語の区切りを示す区切り文字は使用しない。先頭文字は小文字のアルファベットでなければならない。  

この記法では、識別子を形成する文字列は、以下の正規表現に適合する。

```
    [a-z][a-z0-9]*([A-Z][a-z0-9]*)*
```

識別子例：  

* motorSpeed
* retryCount
* uartTxBufferSize


### ケバブケース(kebab-case) <a id="SS_5_3_5"></a>

識別子はすべて小文字のアルファベットおよび数字で構成し、単語の区切りにはハイフン（`-`）を用いる。
先頭文字は小文字のアルファベットでなければならない。  

この記法では、識別子を形成する文字列は、以下の正規表現に適合する。

```
    [a-z][a-z0-9]*(-[a-z0-9]+)*
```

C++ ではハイフンが減算演算子と衝突するため、識別子の宣言・定義には使用できない。
ファイル名や CMake ターゲット名で用いられることがある。


識別子例：  

* motor-controller
* sensor-data-parser
* uart-tx-buffer



