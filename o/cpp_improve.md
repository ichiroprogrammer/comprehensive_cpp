<!-- ./md/cpp_improve.md -->
# C++の進化と主な変更点 <a id="SS_18"></a>
C++は、時代と共に進化を続け、その表現力と効率性が大きく向上してきた。
この章では、C++11以降にて導入された主要な機能や変更点を概観し、各バージョンがもたらした技術的な進展を示す。

___

__この章の構成__

&emsp;&emsp; [C++11の主な新規機能](cpp_improve.md#SS_18_1)  
&emsp;&emsp;&emsp; [一般機能](cpp_improve.md#SS_18_1_1)  
&emsp;&emsp;&emsp; [型に対する機能](cpp_improve.md#SS_18_1_2)  
&emsp;&emsp;&emsp; [テンプレートに対する機能](cpp_improve.md#SS_18_1_3)  
&emsp;&emsp;&emsp; [スレッドに関する機能](cpp_improve.md#SS_18_1_4)  
&emsp;&emsp;&emsp; [その他のユーティリティ](cpp_improve.md#SS_18_1_5)  
&emsp;&emsp;&emsp; [stdの変更、追加](cpp_improve.md#SS_18_1_6)  

&emsp;&emsp; [C++14の主な新規機能](cpp_improve.md#SS_18_2)  
&emsp;&emsp;&emsp; [stdの変更、追加](cpp_improve.md#SS_18_2_1)  

&emsp;&emsp; [C++17の主な新規機能](cpp_improve.md#SS_18_3)  
&emsp;&emsp;&emsp; [新機能、規制緩和](cpp_improve.md#SS_18_3_1)  

&emsp;&emsp; [C++20の主な新規機能](cpp_improve.md#SS_18_4)  
&emsp;&emsp;&emsp; [構文の新機能、規制緩和](cpp_improve.md#SS_18_4_1)  
&emsp;&emsp;&emsp; [構文の新機能、規制緩和の例](cpp_improve.md#SS_18_4_2)  
&emsp;&emsp;&emsp; [template関連](cpp_improve.md#SS_18_4_3)  
&emsp;&emsp;&emsp; [template関連の新機能、規制緩和の例](cpp_improve.md#SS_18_4_4)  

&emsp;&emsp; [C++23の主な新規機能](cpp_improve.md#SS_18_5)  
  
  

[インデックス](introduction.md#SS_1_4)に戻る。  

___

## C++11の主な新規機能 <a id="SS_18_1"></a>
### 一般機能 <a id="SS_18_1_1"></a>

|機能                                                     |説明                                                                        |
|:--------------------------------------------------------|:---------------------------------------------------------------------------|
| 型推論([auto](core_lang_spec.md#SS_19_11_14))                |変数や、式の型の推論                                                        |
| [decltype](core_lang_spec.md#SS_19_11_15)                                         |式の型を取得                                                                |
| [範囲for文](core_lang_spec.md#SS_19_9_3)                         |インデックス変数なしのfor文                                                 |
| [初期化子リストコンストラクタ](core_lang_spec.md#SS_19_6_1_1)      |`vector<int>` v = {1, 2, 3}; など。                                         |
| [一様初期化](core_lang_spec.md#SS_19_6_6)                                       |コンストラクタの呼び出しを、波カッコで行う。|vector<int> v{1, 2, 3};        |
| [rvalue](core_lang_spec.md#SS_19_7_1_2)/[moveセマンティクス](cpp_idioms.md#SS_21_3_3)      |[オブジェクトの所有権](cpp_idioms.md#SS_21_2)の移転、高速化。                     |
| [rvalueリファレンス](core_lang_spec.md#SS_19_8_2)                               |テンポラリオブジェクトをバインドできる`T&&`形式のリファレンス               |
| [ラムダ式](core_lang_spec.md#SS_19_10_3)                            |関数オブジェクトをその場に書く                                              |
| [noexcept](core_lang_spec.md#SS_19_13_4)                                         |関数の例外指定、例外を投げる可能性のある式かbool値を返す演算子              |
| [constexpr](core_lang_spec.md#SS_19_5_1)                                        |定数式やconstexpr関数の定義                                                 |
| nullptr                                                 |ヌルポインタを表すポインタ[リテラル](core_lang_spec.md#SS_19_2)                   |
| インライン名前空間                                      |ネストした名前空間に透過的にアクセスする。「[名前空間](programming_convention.md#SS_3_8_2)」参照  |
| [ユーザー定義リテラル](core_lang_spec.md#SS_19_2_6)                             |ユーザにより定義されたリテラル。標準ライブラリでは\_sや\_svなど             |


### 型に対する機能 <a id="SS_18_1_2"></a>

|機能                                                               |説明                                                          |
|:------------------------------------------------------------------|:-------------------------------------------------------------|
|[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)のdefault/delete 宣言|自動定義される特殊関数の制御                                  |
|[委譲コンストラクタ](core_lang_spec.md#SS_19_6_1_3)                                          |コンストラクタから他のコンストラクタに処理を委譲する          |
|[NSDMI](core_lang_spec.md#SS_19_6_7_1)                                                       |非staticメンバ変数の宣言と同時に初期値指定する                |
|[継承コンストラクタ](core_lang_spec.md#SS_19_6_1_2)                                          |基底クラスのコンストラクタの継承                              |
|virtual関数のoverride/final宣言                                    |「[オーバーライド](programming_convention.md#SS_3_2_4_7)」参照                                 |
|変換演算子のオーバーロードの[explicit](core_lang_spec.md#SS_19_6_2_1)宣言                    |「 [演算子オーバーロード](programming_convention.md#SS_3_3_3)」参照                          |
|friend 宣言の対象を拡張                                            |テンプレートパラメータ、エイリアスfriend 宣言できるように     |
|メンバ関数の[rvalue修飾](core_lang_spec.md#SS_19_8_7_1)/[lvalue修飾](core_lang_spec.md#SS_19_8_7_2)                    |オブジェクトのと値カテゴリでの呼び出し可能であることの指定    |
|[スコープドenum](core_lang_spec.md#SS_19_3_3)                           |スコープを持ち、型付の強いenum                                |
|unionの保持できるオブジェクトの拡張                                |unionでクラスオブジェクトをもつことを許可                     |

### テンプレートに対する機能 <a id="SS_18_1_3"></a>

|機能                                |説明                                                                                       |
|:-----------------------------------|:------------------------------------------------------------------------------------------|
|テンプレート引数の指定に>>の許可    |vector<list<int>> のような記述の許可。「[テンプレートメタプログラミング](template_meta_programming.md#SS_13)」参照       |
|[extern template](programming_convention.md#SS_3_9_6)              |テンプレートのインスタンス化の抑止                                                         |
|[エイリアステンプレート](core_lang_spec.md#SS_19_11_11)       |エイリアスをテンプレート化できる                                                           |
|[パラメータパック](core_lang_spec.md#SS_19_11_4)             |任意の数のテンプレートパラメータを受け取れるようにする                                     |
|テンプレートパラメータ型の制限の緩和|ローカル型と無名型を、テンプレート引数として使用することを許可                             |
|任意の式による[SFINAE](core_lang_spec.md#SS_19_11_1)         |特定の式が[ill-formed](core_lang_spec.md#SS_19_14_1)か否かで、その関数をオーバーロード解決に含めるかどうかを決定する|
|テンプレートのエクスポート機能      |削除                                                                                       |


### スレッドに関する機能 <a id="SS_18_1_4"></a>

|機能                                                    |説明                                                                                |
|:-------------------------------------------------------|:-----------------------------------------------------------------------------------|
|スレッドローカルストレージ                              |スレッドごとに異なる静的記憶域に保持される変数                                      |
|ブロックスコープのstatic変数初期化のスレッドセーフ化    |関数ローカルで定義したstatic変数の初期化をスレッドセーフに。「[Singleton](design_pattern.md#SS_9_13)」参照|


### その他のユーティリティ <a id="SS_18_1_5"></a>

| 機能                                             |説明                                                                             |
|:-------------------------------------------------|:--------------------------------------------------------------------------------|
| 戻り値の型を後置する関数宣言構文                 |「[戻り値型](programming_convention.md#SS_3_3_6)」参照                                                          |
| コンパイル時アサート                             |コンパイル時に条件式が真であることをassertする。「[assertion](programming_convention.md#SS_3_11_1)」参照         |
| [生文字列リテラル](core_lang_spec.md#SS_19_2_1) |文字列リテラルにRプレフィックスを付けることで、エスケープシーケンスを無視する。  |
| char16_tとchar32_t                               |UTF-16とUTF-32の文字型                                                           |
| UTF-8文字列リテラル                              |char の文字列をUTF-8エンコーディングするプレフィックス                           |
| [属性構文](core_lang_spec.md#SS_19_9_1)                                  |[[attr]]構文による属性指定。[[noreturn]]など。「[return文](programming_convention.md#SS_3_4_7)」参照            |
| alignas                                          |アライメントを指定する。「[固定長メモリプール](dynamic_memory_allocation.md#SS_14_2_1)」参照                        |
| alignof                                          |アライメントを取得する。「[固定長メモリプール](dynamic_memory_allocation.md#SS_14_2_1)」参照                        |


### stdの変更、追加 <a id="SS_18_1_6"></a>
#### ユーティリティ <a id="SS_18_1_6_1"></a>
|機能                |説明                                 |
|:-------------------|:------------------------------------|
|[std::move](stdlib_and_concepts.md#SS_20_1_1)    |[moveセマンティクス](cpp_idioms.md#SS_21_3_3)の利用      |
|[std::forward](stdlib_and_concepts.md#SS_20_1_2) |[perfect forwarding](core_lang_spec.md#SS_19_8_5)の実装、利用|

#### stdコンテナ <a id="SS_18_1_6_2"></a>
[コンテナ](stdlib_and_concepts.md#SS_20_7)全般が[moveセマンティクス](cpp_idioms.md#SS_21_3_3)に対応したため、
テンプレートのパラメータTが、コピー構築可能(`is_copy_constructible<T> == true`)な型だけでなく、
ムーブ構築(is_move_constructible)のみ可能な型も受け付けるられるようになった。
push_back()やinsert()等の要素追加のためのメンバ関数が、
新たな要素のコピーだけでなく、emplace() 、emplace_back() 、emplace_front()のような名称のメンバ関数は、
[rvalue](core_lang_spec.md#SS_19_7_1_2)オブジェクトも受け取れて、
move挿入ができるようになった(「[その他のテンプレートテクニック](template_meta_programming.md#SS_13_7)」参照)。

|機能                            |説明                                                                                |
|:-------------------------------|:-----------------------------------------------------------------------------------|
|std::array                      |このコンテナは固定長配列クラスを表す「[配列](programming_convention.md#SS_3_1_7)」参照)。         |
|[std::forward_list](stdlib_and_concepts.md#SS_20_7_1_1)        |このは単方向リンクリストの実装である。                                              |
|[std::unordered_map](stdlib_and_concepts.md#SS_20_7_3_2)       |同一キーの要素を複数格納しない、格納順が規定されていない連想配列の実装であるである。|
|[std::unordered_set](stdlib_and_concepts.md#SS_20_7_3_1)       |同一キーの要素を複数格納できず、格納順が規定されていないコンテナである。            |
|[std::type_index](stdlib_and_concepts.md#SS_20_7_3_3)          |型情報型を連想コンテナのキーとして使用するためのクラス。                            |

#### 並列処理 <a id="SS_18_1_6_3"></a>
|機能                          | 説明                                                    |
|:----------------------------:|:--------------------------------------------------------|
| [std::thread](stdlib_and_concepts.md#SS_20_3_1)           | スレッドの生成                                          |
| [std::atomic](stdlib_and_concepts.md#SS_20_3_3)           | 単純なオブジェクトのアトミック処理                      |
| [std::mutex](stdlib_and_concepts.md#SS_20_3_2)            | スレッド間の競合の回避                                  |
| [std::lock_guard](stdlib_and_concepts.md#SS_20_4_1)       | ミューテックスのロック/アンロックを管理するためクラス   |
| [std::unique_lock](stdlib_and_concepts.md#SS_20_4_2)      | ミューテックスのロック/アンロックを管理するためクラス   |
| [std::scoped_lock](stdlib_and_concepts.md#SS_20_4_3)      | ミューテックスのロック/アンロックを管理するためクラス   |


## C++14の主な新規機能 <a id="SS_18_2"></a>

|機能                                                  |説明                                                                             |
|:-----------------------------------------------------|:--------------------------------------------------------------------------------|
|[2進数リテラル](core_lang_spec.md#SS_19_2_2)                                  |2進数を表す0bもしくは0Bプレフィックスを付けた数値リテラルの記述を可能に          |
|[関数の戻り値型auto](core_lang_spec.md#SS_19_11_18)                             |戻り値の型を後置する関羽鵜テンプレート/関数定義とラムダ式の戻り値型にautoに      |
|[decltype(auto)](core_lang_spec.md#SS_19_11_16)                                 |decltypeの規則による変数の型推論                                                 |
|[ラムダ式](core_lang_spec.md#SS_19_10_3)の初期化キャプチャ        |キャプチャに代入構文を導入し、一つの変数に複数のキャプチャ方法を指定可能にする   |
|[ジェネリックラムダ](core_lang_spec.md#SS_19_11_6)                             |ラムダ式のパラメータを auto にすることで、ジェネリックな関数呼び出しに           |
|[変数テンプレート](core_lang_spec.md#SS_19_11_10)          |変数定義時のテンプレート指定を可能に                                             |
|constexpr関数内での条件分岐とループの文を許可         |[constexpr if文](core_lang_spec.md#SS_19_11_12)                                                            |
|structの[NSDMI](core_lang_spec.md#SS_19_6_7_1)の対応                            |                                                                                 |
|structのネストする初期化における波カッコ省略を許可    |一様初期化と初期化子リストを組み合わせた際、二重に波カッコが不要に               |
|[[deprecated]]属性                                    |「[属性構文](core_lang_spec.md#SS_19_9_1)」参照                                                          |
|[数値リテラル](core_lang_spec.md#SS_19_2_3)の桁区切り文字                     |シングルクォーテーションで数値リテラルを桁区切りする                             |
|サイズ付きデアロケーション                            |[グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_1)                                      |
|[heap allocation elision](stdlib_and_concepts.md#SS_20_11_2)                        |動的メモリ確保の省略(heap allocation elision)の許可                              |

### stdの変更、追加 <a id="SS_18_2_1"></a>

|機能                                              |説明                                                      |
|:-------------------------------------------------|:---------------------------------------------------------|
|std::make_unique<>()                              |「[メモリアロケーション](programming_convention.md#SS_3_5_6)」参照                |
|std::exchange()                                   |二つの値を入れ替える。「[Copy-And-Swap](design_pattern.md#SS_9_6)」参照        |
|[std::integer_sequence](cpp_improve.md#SS_18_2_1_1_1)                      |コンパイル時整数シーケンス                                |
|[std::get()のオーバーロード](cpp_improve.md#SS_18_2_1_1_2)を追加           |タプルを型の集合と見なし、型を指定して対応する値を取得する|
|`<type_traits>`                                   |xxx_t、xxx_vなどのエイリアステンプレート、定数テンプレート|
|[std::string型リテラル](core_lang_spec.md#SS_19_2_6_2)                      |                                                          |
|[std::chronoのリテラル](core_lang_spec.md#SS_19_2_6_3) |                                                          |
|[std::complexリテラル](core_lang_spec.md#SS_19_2_6_4)  |                                                          |

#### C++14/stdの追加使用例 <a id="SS_18_2_1_1"></a>
##### std::integer_sequence <a id="SS_18_2_1_1_1"></a>

```cpp
    //  example/cpp_improve/cpp14_ut.cpp 11

    template <typename Tuple, std::size_t... I>
    std::string tuple2string(const Tuple& t, std::index_sequence<I...>)
    {
        std::ostringstream os;

        ((os << std::get<I>(t) << " "), ...);  // Tupleの各要素を出力

        return os.str();
    }

    template <typename... Args>
    std::string process_tuple(const std::tuple<Args...>& t)
    {
        return tuple2string(t, std::index_sequence_for<Args...>{});
    }
```
```cpp
    //  example/cpp_improve/cpp14_ut.cpp 32

    std::tuple<int, double, const char*> t(1, 2.5, "test");

    auto ret = process_tuple(t);  // タプルの要素を出力 (1, 2.5, test)
    ASSERT_EQ("1 2.5 test ", ret);
    ASSERT_EQ(1, std::get<0>(t));
    ASSERT_EQ(2.5, std::get<1>(t));
    ASSERT_STREQ("test", std::get<2>(t));
```

##### std::get()のオーバーロード <a id="SS_18_2_1_1_2"></a>

```cpp
    //  example/cpp_improve/cpp14_ut.cpp 46

    std::tuple<int, float, std::string> my_tuple(1, 3.14f, "hello");

    // 異なる型のオーバーロードされた std::get を使用
    ASSERT_EQ(std::get<int>(my_tuple), 1);
    ASSERT_FLOAT_EQ(std::get<float>(my_tuple), 3.14f);
    ASSERT_EQ(std::get<std::string>(my_tuple), "hello");
```

## C++17の主な新規機能 <a id="SS_18_3"></a>
### 新機能、規制緩和 <a id="SS_18_3_1"></a>

|機能                                            |説明                                                                             |
|:-----------------------------------------------|:--------------------------------------------------------------------------------|
|[16進浮動小数点数リテラル](core_lang_spec.md#SS_19_2_5)                 |16進数表記で浮動小数点数リテラルを記述できるようにする                           |
|インライン変数                                  |inline 指定をすることで翻訳単位を跨いでひとつのオブジェクトになる変数を定義する  |
|構造化束縛                                      |「[戻り値型](programming_convention.md#SS_3_3_6)」参照                                                          |
|[単一要素の波カッコ初期化を非配列とする](cpp_improve.md#SS_18_3_1_1)   |リストによる直接初期化の型推論の規則が変更された                                 |
|[[maybe_unused]]属性                            |「[属性構文](core_lang_spec.md#SS_19_9_1)」参照                                                          | 
|[[nodiscard]]属性                               |「[属性構文](core_lang_spec.md#SS_19_9_1)」、[グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_1)」参照           |
|[RVO(Return Value Optimization)](core_lang_spec.md#SS_19_15_1)           |右辺値を変数の初期化のために使用する場合、コピーもムーブも省略することを保証     |
|[演算子のオペランドの評価順位](core_lang_spec.md#SS_19_14_12)             |C++14まで未規定であった部分式の評価順序を規定                                    |
|enum class変数の初期値のルール変更              |「[スコープドenum](core_lang_spec.md#SS_19_3_3)」、 「[underlying type](core_lang_spec.md#SS_19_3_4)」参照                       |
|[newのアライメント指定](cpp_improve.md#SS_18_3_1_2)                    |                                                                                 |
|[初期化付きif/switch文](core_lang_spec.md#SS_19_9_5)                    |if文とswitch文の条件式と初期化を分離する構文                                     |
|[[fallthrough]]属性                             |「[属性構文](core_lang_spec.md#SS_19_9_1)」参照                                                          |
|[constexpr if文](core_lang_spec.md#SS_19_11_12)                           |if constexpr(cond) とすることで、その if 文はコンパイル時に処理                  |
|[範囲for文のイテレータ型の不一致の許可](cpp_improve.md#SS_18_3_1_3)    |std::istream_iteratorとstd::istreamに利用                                        |
|[ラムダ式での\*thisのコピーキャプチャ](cpp_improve.md#SS_18_3_1_4)     |キャプチャリストに\*this を指定することで、\*thisをコピーキャプチャする          |
|[constexprラムダ](core_lang_spec.md#SS_19_5_9) |ラムダ式の関数オブジェクトのconstexpr指定を可能に                                |
|[std::optional](stdlib_and_concepts.md#SS_20_8)                            |関数の戻り値の無効表現を行うためのクラステンプレート                             |
|[std::variant](stdlib_and_concepts.md#SS_20_9)                             |型安全なunion機能を提供するクラステンプレート                                    |


#### 単一要素の波カッコ初期化を非配列とする <a id="SS_18_3_1_1"></a>

```cpp
    //  example/cpp_improve/cpp17_ut.cpp 16

    #if 1  // C++17からリストによる直接初期化の型推論の規則が変更された
        auto a0 = {0};
        auto a1 = {0, 1};
        auto a2{0};

        static_assert(std::is_same_v<decltype(a0), std::initializer_list<int>>);
        static_assert(std::is_same_v<decltype(a1), std::initializer_list<int>>);
        static_assert(std::is_same_v<decltype(a2), int>);
    #else
        auto ill_formd0 = {0, 1.0};  // ill-formed: int と double からは推論できない
        auto ill_formd0{0, 1};       // C++17からill-formd
    #endif
```

#### newのアライメント指定 <a id="SS_18_3_1_2"></a>

```cpp
    //  example/cpp_improve/cpp17_ut.cpp 34

    struct alignas(64) AlignedStruct {  // C++17 newのアライメント指定
        int x;
    };

```
```cpp
    //  example/cpp_improve/cpp17_ut.cpp 44

    AlignedStruct* ptr = new AlignedStruct;

    ASSERT_EQ(reinterpret_cast<std::uintptr_t>(ptr) % 64, 0);  // アライメントの確認

    delete ptr;
```

#### 範囲for文のイテレータ型の不一致の許可 <a id="SS_18_3_1_3"></a>
```cpp
    //  example/cpp_improve/cpp17_ut.cpp 57

    namespace org {
    struct custom_iterator {  // カスタムイテレータの定義
        const int* ptr;

        custom_iterator(const int* p) : ptr(p) {}
        bool             operator!=(const custom_iterator& other) const { return ptr != other.ptr; }
        const int&       operator*() const { return *ptr; }
        custom_iterator& operator++()
        {
            ++ptr;
            return *this;
        }
    };

    const int* begin(const std::vector<int>& vec)
    {
        return vec.data();  // 通常のポインタを返す
    }

    // 配列の終端はカスタムイテレータを返すend関数
    custom_iterator end(const std::vector<int>& vec)
    {
        return custom_iterator(vec.data() + vec.size());  // カスタムイテレータを返す
    }

    struct vec_int : std::vector<int> {};
    }  // namespace org
```
```cpp
    //  example/cpp_improve/cpp17_ut.cpp 91

    org::vec_int       nums{{1, 2, 3, 4, 5}};
    std::ostringstream os;

    // std::begin<T>, std::end<T>の戻り型が異なることの証明
    static_assert(!std::is_same_v<decltype(org::begin(nums)), decltype(org::end(nums))>);

    for (int num : nums) {  // 範囲for文でポインタとカスタムイテレータの不一致を許容
        os << num << " ";
    }

    ASSERT_EQ("1 2 3 4 5 ", os.str());
```

#### ラムダ式での\*thisのコピーキャプチャ <a id="SS_18_3_1_4"></a>

```cpp
    //  example/cpp_improve/cpp17_ut.cpp 107

    struct MyStruct {
        int value = 42;

        auto getValue()
        {
            return [*this]() { return value; };  // *thisをコピーキャプチャ
        }
    };
```
```cpp
    //  example/cpp_improve/cpp17_ut.cpp 121

        MyStruct obj;
        auto     lambda = obj.getValue();
        obj.value       = 0;  // コピーキャプチャされたため、影響を受けない

        ASSERT_EQ(lambda(), 42);  // コピーキャプチャの影響で元の値が保持される
```

## C++20の主な新規機能 <a id="SS_18_4"></a>
### 構文の新機能、規制緩和 <a id="SS_18_4_1"></a>

|機能                                           |説明                                                                                                |
|:----------------------------------------------|:---------------------------------------------------------------------------------------------------|
|[三方比較演算子](core_lang_spec.md#SS_19_6_4_2)                          |`<=>`/`==`による比較演算子の自動定義                                                                |
|ビットフィールドのメンバ変数初期化             |ビットフィールドメンバ変数のデフォルト値を設定する構文を追加                                        |
|[explicit(COND)](core_lang_spec.md#SS_19_6_2_4)                          |explicit(true/false) のように explicit にboolパラメータを指定できるようにする                       |
|const修飾されたメンバポインタの制限を修正      |`.*`演算子での[lvalue](core_lang_spec.md#SS_19_7_1_1)のconstメンバ関数呼び出しを許可                                          |
|デフォルトコピーコンストラクタの規約のバグ修正 |デフォルトのコピーコンストラクタと引数が非constなコンストラクタが衝突する問題を修正                 |
|特殊化のアクセスチェック                       |                                                                                                    |
|[[no_unique_address]]属性追加                  |空の型のオブジェクトをほかのオブジェクトと共有する最適化を許可。「[属性構文](core_lang_spec.md#SS_19_9_1)」参照             |
|[friend指定された関数内から構造化束縛](cpp_improve.md#SS_18_4_2_1)    |構造化束縛でのメンバ変数へアクセスルールの変更                                                      |
|[構造化束縛カスタマイゼーションルール変更](cpp_improve.md#SS_18_4_2_2)|構造化束縛がカスタマイゼーションポイントを見つけるルールを緩和                                      |
|関数の戻り値型の抽象型のチェック               |関数の宣言段階では、パラメータや戻り値型が抽象型かどうかをチェックしない                            |
|可変長データを扱うクラスの効率的なdelete       |クラスのdelete演算子が呼び出される前にデストラクタが呼ばれないようにするオプションを追加            |
|条件付きで特殊メンバ関数をトリビアルに定義     |制約によってトリビアルな特殊メンバ関数と非トリビアルな特殊メンバ関数をオーバーロード可に            |
|未初期化領域への暗黙的なオブジェクト構築       |未初期化領域の利用時に自動的にトリビアルな型のオブジェクトを構築する                                |

### 構文の新機能、規制緩和の例 <a id="SS_18_4_2"></a>
#### friend指定された関数内から構造化束縛 <a id="SS_18_4_2_1"></a>
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 9

    class A {
    public:
        A(int a0, int b0) : a0_{a0}, b0_{b0} {}

    private:
        int a0_;
        int b0_;

        friend std::pair<int, int> f(A const& a)
        {
            auto [a_a, a_b] = a;  // fがfriendであるため、構造化束縛可能

            return {a_a, a_b};
        }
    };
```
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 30

    auto a = A{1, 2};

    auto [a0, a1] = f(a);  // fはA::a0_、a1_にアクセスできる

    ASSERT_EQ(a0, 1);
    ASSERT_EQ(a1, 2);
```

#### 構造化束縛カスタマイゼーションルール変更 <a id="SS_18_4_2_2"></a>
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 42

    struct Point2D {  // C++17でも動作する例
        int x, y;
    };

    class Point3D {  // C++20で改善された例
    public:
        Point3D(int x, int y, int z) : x_{x}, y_{y}, z_{z} {}

        template <std::size_t I>  // 構造化束縛カスタマイゼーションポイント
        auto get() const
        {
            if constexpr (I == 0)
                return x_;
            else if constexpr (I == 1)
                return y_;
            else if constexpr (I == 2)
                return z_;
        }

    private:
        int x_, y_, z_;
    };

    namespace std {  // 例外的にstdへの追加が認められている
    template <>      // 構造化束縛のためのカスタマイゼーションポイント
    struct tuple_size<Point3D> : std::integral_constant<std::size_t, 3> {
    };

    template <std::size_t I>
    struct tuple_element<I, Point3D> {
        using type = int;
    };
    }  // namespace std
```
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 82

    // C++17までのスタイル
    Point2D p2d{10, 20};

    auto [x2d, y2d] = p2d;
    ASSERT_EQ(x2d, 10);
    ASSERT_EQ(y2d, 20);

    // C++20から
    Point3D p3d{1, 2, 3};

    auto [p3d_x, p3d_y, p3d_z] = p3d;
    ASSERT_EQ(p3d_x, 1);
    ASSERT_EQ(p3d_y, 2);
    ASSERT_EQ(p3d_z, 3);
```

### template関連 <a id="SS_18_4_3"></a>

|機能                                                   |説明                                                                            |
|:------------------------------------------------------|:-------------------------------------------------------------------------------|
|[コンセプト](core_lang_spec.md#SS_19_11_3)                                      |キーワードconcept、requiresの導入。テンプレートパラメータの制約。               |
|[autoパラメータによる関数テンプレートの簡易定義](core_lang_spec.md#SS_19_11_13)  |[ジェネリックラムダ](core_lang_spec.md#SS_19_11_6)と同様に関数パラメータをの型をautoにできる。           |
|[型の文脈でtypenameの省略を許可](cpp_improve.md#SS_18_4_4_1)                  |型しか現れない文脈では、typenameの省略を可能に                                  |
|[非型テンプレートパラメータとしてクラス型を許可](cpp_improve.md#SS_18_4_4_2)  |                                                                                |
|ADLのバグ修正                                          |[関数テンプレートに明示的に型指定した場合にADLで見つからない問題を修正](cpp_improve.md#SS_18_4_4_3)    |
|[structテンプレートのテンプレート引数推論](cpp_improve.md#SS_18_4_4_5)        |                                                                                |
|テンプレート引数推論の改善                             |[エイリアステンプレート経由でのクラステンプレートのテンプレート引数推論](cpp_improve.md#SS_18_4_4_4)   |


### template関連の新機能、規制緩和の例 <a id="SS_18_4_4"></a>
#### 型の文脈でtypenameの省略を許可 <a id="SS_18_4_4_1"></a>

```cpp
    //  example/cpp_improve/cpp20_ut.cpp 102

    template <typename T>

    struct Ommit {
        using value_type = T::value_type;  // C++20では typename を省略できる

        value_type get_first_element(const T& container) const { return container[0]; }
    };
```

#### 非型テンプレートパラメータとしてクラス型を許可 <a id="SS_18_4_4_2"></a>
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 123

    struct X1 {
        int   i;
        float f;

        friend bool operator==(const X1&, const X1&) = default;
    };

    struct X2 {
        int   i;
        float f;

        constexpr X2(int i, float f) : i{i}, f{f} {}

        friend bool operator==(const X2&, const X2&) = default;
    };

    template <int N>
    struct C1 {
        static constexpr int value = N;
    };

    template <float N>
    struct C2 {
        static constexpr float value = N;  // N を保持
    };

    template <X1 x1, X2 x2>
    struct C3 {
        static constexpr X1 value1 = x1;  // X1 の値を保持
        static constexpr X2 value2 = x2;  // X2 の値を保持
    };

    template <auto V>
    struct C4 {
        static constexpr decltype(V) value = V;  // V の型を推論し、その値を保持
    };
```
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 162

    static_assert(C1<42>::value == 42);  // テンプレートパラメータ N = 42 の動作を確認

    static_assert(C2<3.14f>::value == 3.14f);  // テンプレートパラメータ N = 3.14f の動作を確認

    constexpr X1 x1{1, 2.5f};  // X1 のオブジェクトを constexpr で作成
    constexpr X2 x2{2, 3.5f};  // X2 のオブジェクトを constexpr で作成

    static_assert(C3<x1, x2>::value1 == x1);  // X1 の比較
    static_assert(C3<x1, x2>::value2 == x2);  // X2 の比較

    static_assert(C4<100>::value == 100);  // 整数の動作確認
    static_assert(C4<x1>::value == x1);    // X1 オブジェクトの動作確認
```

#### 関数テンプレートに明示的に型指定した場合にADLで見つからない問題を修正 <a id="SS_18_4_4_3"></a>
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 179
    namespace adl_NS {
    struct X {};

    // X に対する関数テンプレート
    template <typename T>
    void func(T)
    {
        std::cout << "Called func(T) from my_namespace" << std::endl;
    }
    }  // namespace adl_NS
```
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 194

    adl_NS::X obj;

    // 型を明示的に指定して呼び出す（C++20以前では ADL が効かない）
    func<adl_NS::X>(obj);  // エラー: ADL が働かず、関数が見つからない

    // 型を明示的に指定せずに呼び出す（ADLが働く）
    func(obj);  // OK: adl_NS から func が見つかる
```

#### エイリアステンプレート経由でのクラステンプレートのテンプレート引数推論 <a id="SS_18_4_4_4"></a>
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 207

    template <typename T>
    class X {
    public:
        X(T value) : value_{value} {}
        T getValue() const { return value_; }

    private:
        T value_;
    };
    template <typename T>
    using XAlias = X<T>;
```
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 224

    XAlias obj1{42};  // 推論される型はint
    static_assert(std::is_same_v<decltype(obj1), X<int>>);

    XAlias obj2{3.14};  // 推論される型はdouble
    static_assert(std::is_same_v<decltype(obj2), X<double>>);

    EXPECT_EQ(obj1.getValue(), 42);
    EXPECT_DOUBLE_EQ(obj2.getValue(), 3.14);
```

#### structテンプレートのテンプレート引数推論 <a id="SS_18_4_4_5"></a>
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 236

    template <class T>
    struct Point {
        T x;
        T y;
    };
```
```cpp
    //  example/cpp_improve/cpp20_ut.cpp 247

    Point p{3.0, 4.0};  // C++17:NG C++20:OK

    ASSERT_DOUBLE_EQ(p.x, 3.0);
    ASSERT_DOUBLE_EQ(p.y, 4.0);
```


## C++23の主な新規機能 <a id="SS_18_5"></a>
not yet.



