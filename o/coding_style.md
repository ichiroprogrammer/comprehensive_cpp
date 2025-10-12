<!-- ./md/coding_style.md -->
# コーディングスタイル <a id="SS_5"></a>
スタイルが統一されていないソースコードは、それだけで可読性に劣るため、
スタイルの統一は重要であるが、それにこだわりすぎれば、不毛な宗教論争が発生してしまう。
そのようなロスを避けスタイルを定めたとしても、その遵守が目視、手作業によって行われるならば、
これもまた新たなロスになる。

こういった状況に陥ることなくソースコードの記述スタイルを統一するために、
本ドキュメントでは「clang-formatを使い、デフォルトのスタイルを適切に定め、
必要なら多少のカスタマイズを行い、それに従う」ことを推奨する。

以下は、clang-formatを使えない場合のスタイルの指針である。

___

__この章の構成__

&emsp;&emsp; [インデント](coding_style.md#SS_5_1)  
&emsp;&emsp;&emsp; [インデント用文字](coding_style.md#SS_5_1_1)  
&emsp;&emsp;&emsp; [if、for、while、do-whileのインデント](coding_style.md#SS_5_1_2)  
&emsp;&emsp;&emsp; [ブロックのインデント](coding_style.md#SS_5_1_3)  
&emsp;&emsp;&emsp; [case、defaultのインデント](coding_style.md#SS_5_1_4)  

&emsp;&emsp; [ブロック(波括弧({}))](coding_style.md#SS_5_2)  
&emsp;&emsp; [関数シグネチャ内の'()'](coding_style.md#SS_5_3)  
&emsp;&emsp; [クラスのアクセスレベル](coding_style.md#SS_5_4)  
&emsp;&emsp; [スペース](coding_style.md#SS_5_5)  
&emsp;&emsp;&emsp; [文の後](coding_style.md#SS_5_5_1)  
&emsp;&emsp;&emsp; [コンマの後  ](coding_style.md#SS_5_5_2)  
&emsp;&emsp;&emsp; [単項演算子、二項演算子、三項演算子の前後](coding_style.md#SS_5_5_3)  
&emsp;&emsp;&emsp; [不要なブランク文字](coding_style.md#SS_5_5_4)  

&emsp;&emsp; [三項演算子のスタイル](coding_style.md#SS_5_6)  
&emsp;&emsp; [ポインタ型やリファレンス型インスタンスの宣言、定義の\*や&の場所](coding_style.md#SS_5_7)  
&emsp;&emsp; [行数・桁数](coding_style.md#SS_5_8)  
&emsp;&emsp;&emsp; [関数の行数](coding_style.md#SS_5_8_1)  
&emsp;&emsp;&emsp; [行のカラム数](coding_style.md#SS_5_8_2)  

&emsp;&emsp; [ブロックの論理レベル](coding_style.md#SS_5_9)  
&emsp;&emsp; [名前空間](coding_style.md#SS_5_10)  
&emsp;&emsp; [clang-format](coding_style.md#SS_5_11)  
  
  

[このドキュメントの構成](introduction.md#SS_1_7)に戻る。  

___

## インデント <a id="SS_5_1"></a>
### インデント用文字 <a id="SS_5_1_1"></a>
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

### if、for、while、do-whileのインデント <a id="SS_5_1_2"></a>
* if、for、while、do-whileに付随する文は、
  if、for、while、do-whileより1インデント下げる(「[ブロック(波括弧({}))](coding_style.md#SS_5_2)」等を参照)。

### ブロックのインデント <a id="SS_5_1_3"></a>
* ブロック内部の文はブロック開始の'{'より1インデント下げる。

### case、defaultのインデント <a id="SS_5_1_4"></a>
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

## ブロック(波括弧({})) <a id="SS_5_2"></a>
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

## 関数シグネチャ内の'()' <a id="SS_5_3"></a>
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

## クラスのアクセスレベル <a id="SS_5_4"></a>
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

## スペース <a id="SS_5_5"></a>
### 文の後 <a id="SS_5_5_1"></a>
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

### コンマの後   <a id="SS_5_5_2"></a>
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

### 単項演算子、二項演算子、三項演算子の前後 <a id="SS_5_5_3"></a>
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

### 不要なブランク文字 <a id="SS_5_5_4"></a>
* スペース文字は、セパレータとして適切に使用するためのものである。
  従って、行末に不要なブランクキャラクタを置かない。
* ファイル末に不要な改行を入れない。

## 三項演算子のスタイル <a id="SS_5_6"></a>
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

## ポインタ型やリファレンス型インスタンスの宣言、定義の\*や&の場所 <a id="SS_5_7"></a>
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

## 行数・桁数 <a id="SS_5_8"></a>
### 関数の行数 <a id="SS_5_8_1"></a>

* 関数の行数({から}の間)は30行までに収める。
* 「テストシーケンスを一つの関数に押し込める」という方法は一般的なため、
  単体テストのための関数に対しては、この制限を適用しない。

### 行のカラム数 <a id="SS_5_8_2"></a>
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

## ブロックの論理レベル <a id="SS_5_9"></a>
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

## 名前空間 <a id="SS_5_10"></a>
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

## clang-format <a id="SS_5_11"></a>
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

```


