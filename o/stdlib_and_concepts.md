<!-- essential/md/stdlib_and_concepts.md -->
# 標準ライブラリとプログラミングの概念 <a id="SS_20"></a>
この章では、C++標準ライブラリやそれによって導入されたプログラミングの概念等の紹介を行う。

___

__この章の構成__

&emsp;&emsp; [ユーティリティ](stdlib_and_concepts.md#SS_20_1)  
&emsp;&emsp;&emsp; [std::move](stdlib_and_concepts.md#SS_20_1_1)  
&emsp;&emsp;&emsp; [std::forward](stdlib_and_concepts.md#SS_20_1_2)  

&emsp;&emsp; [type_traits](stdlib_and_concepts.md#SS_20_2)  
&emsp;&emsp;&emsp; [std::integral_constant](stdlib_and_concepts.md#SS_20_2_1)  
&emsp;&emsp;&emsp; [std::true_type](stdlib_and_concepts.md#SS_20_2_2)  
&emsp;&emsp;&emsp; [std::false_type](stdlib_and_concepts.md#SS_20_2_3)  
&emsp;&emsp;&emsp; [std::is_same](stdlib_and_concepts.md#SS_20_2_4)  
&emsp;&emsp;&emsp; [std::enable_if](stdlib_and_concepts.md#SS_20_2_5)  
&emsp;&emsp;&emsp; [std::conditional](stdlib_and_concepts.md#SS_20_2_6)  
&emsp;&emsp;&emsp; [std::is_void](stdlib_and_concepts.md#SS_20_2_7)  
&emsp;&emsp;&emsp; [std::is_copy_assignable](stdlib_and_concepts.md#SS_20_2_8)  
&emsp;&emsp;&emsp; [std::is_move_assignable](stdlib_and_concepts.md#SS_20_2_9)  

&emsp;&emsp; [並列処理](stdlib_and_concepts.md#SS_20_3)  
&emsp;&emsp;&emsp; [std::thread](stdlib_and_concepts.md#SS_20_3_1)  
&emsp;&emsp;&emsp; [std::mutex](stdlib_and_concepts.md#SS_20_3_2)  
&emsp;&emsp;&emsp; [std::atomic](stdlib_and_concepts.md#SS_20_3_3)  
&emsp;&emsp;&emsp; [std::condition_variable](stdlib_and_concepts.md#SS_20_3_4)  

&emsp;&emsp; [ロック所有ラッパー](stdlib_and_concepts.md#SS_20_4)  
&emsp;&emsp;&emsp; [std::lock_guard](stdlib_and_concepts.md#SS_20_4_1)  
&emsp;&emsp;&emsp; [std::unique_lock](stdlib_and_concepts.md#SS_20_4_2)  
&emsp;&emsp;&emsp; [std::scoped_lock](stdlib_and_concepts.md#SS_20_4_3)  

&emsp;&emsp; [スマートポインタ](stdlib_and_concepts.md#SS_20_5)  
&emsp;&emsp;&emsp; [std::unique_ptr](stdlib_and_concepts.md#SS_20_5_1)  
&emsp;&emsp;&emsp;&emsp; [std::make_unique](stdlib_and_concepts.md#SS_20_5_1_1)  

&emsp;&emsp;&emsp; [std::shared_ptr](stdlib_and_concepts.md#SS_20_5_2)  
&emsp;&emsp;&emsp;&emsp; [std::make_shared](stdlib_and_concepts.md#SS_20_5_2_1)  
&emsp;&emsp;&emsp;&emsp; [std::enable_shared_from_this](stdlib_and_concepts.md#SS_20_5_2_2)  

&emsp;&emsp;&emsp; [std::weak_ptr](stdlib_and_concepts.md#SS_20_5_3)  
&emsp;&emsp;&emsp; [std::auto_ptr](stdlib_and_concepts.md#SS_20_5_4)  

&emsp;&emsp; [Polymorphic Memory Resource(pmr)](stdlib_and_concepts.md#SS_20_6)  
&emsp;&emsp;&emsp; [std::pmr::memory_resource](stdlib_and_concepts.md#SS_20_6_1)  
&emsp;&emsp;&emsp; [std::pmr::polymorphic_allocator](stdlib_and_concepts.md#SS_20_6_2)  
&emsp;&emsp;&emsp; [pool_resource](stdlib_and_concepts.md#SS_20_6_3)  

&emsp;&emsp; [コンテナ](stdlib_and_concepts.md#SS_20_7)  
&emsp;&emsp;&emsp; [シーケンスコンテナ(Sequence Containers)](stdlib_and_concepts.md#SS_20_7_1)  
&emsp;&emsp;&emsp;&emsp; [std::forward_list](stdlib_and_concepts.md#SS_20_7_1_1)  

&emsp;&emsp;&emsp; [連想コンテナ(Associative Containers)](stdlib_and_concepts.md#SS_20_7_2)  
&emsp;&emsp;&emsp; [無順序連想コンテナ(Unordered Associative Containers)](stdlib_and_concepts.md#SS_20_7_3)  
&emsp;&emsp;&emsp;&emsp; [std::unordered_set](stdlib_and_concepts.md#SS_20_7_3_1)  
&emsp;&emsp;&emsp;&emsp; [std::unordered_map](stdlib_and_concepts.md#SS_20_7_3_2)  
&emsp;&emsp;&emsp;&emsp; [std::type_index](stdlib_and_concepts.md#SS_20_7_3_3)  

&emsp;&emsp;&emsp; [コンテナアダプタ(Container Adapters)](stdlib_and_concepts.md#SS_20_7_4)  
&emsp;&emsp;&emsp; [特殊なコンテナ](stdlib_and_concepts.md#SS_20_7_5)  

&emsp;&emsp; [std::optional](stdlib_and_concepts.md#SS_20_8)  
&emsp;&emsp;&emsp; [戻り値の無効表現](stdlib_and_concepts.md#SS_20_8_1)  
&emsp;&emsp;&emsp; [オブジェクトの遅延初期化](stdlib_and_concepts.md#SS_20_8_2)  

&emsp;&emsp; [std::variant](stdlib_and_concepts.md#SS_20_9)  
&emsp;&emsp; [オブジェクトの比較](stdlib_and_concepts.md#SS_20_10)  
&emsp;&emsp;&emsp; [std::rel_ops](stdlib_and_concepts.md#SS_20_10_1)  
&emsp;&emsp;&emsp; [std::tuppleを使用した比較演算子の実装方法](stdlib_and_concepts.md#SS_20_10_2)  

&emsp;&emsp; [その他](stdlib_and_concepts.md#SS_20_11)  
&emsp;&emsp;&emsp; [SSO(Small String Optimization)](stdlib_and_concepts.md#SS_20_11_1)  
&emsp;&emsp;&emsp; [heap allocation elision](stdlib_and_concepts.md#SS_20_11_2)  
  
  

[インデックス](introduction.md#SS_1_4)に戻る。  

___


## ユーティリティ <a id="SS_20_1"></a>
### std::move <a id="SS_20_1_1"></a>
std::moveは引数を[rvalueリファレンス](core_lang_spec.md#SS_19_8_2)に変換する関数テンプレートである。

|引数                 |std::moveの動作                                    |
|---------------------|---------------------------------------------------|
|非const [lvalue](core_lang_spec.md#SS_19_7_1_1)|引数を[rvalueリファレンス](core_lang_spec.md#SS_19_8_2)にキャストする      |
|const [lvalue](core_lang_spec.md#SS_19_7_1_1)  |引数をconst [rvalueリファレンス](core_lang_spec.md#SS_19_8_2)にキャストする|

この表の動作仕様を下記ののコードで示す。

```cpp
    //  example/stdlib_and_concepts/utility_ut.cpp 10

    uint32_t f(std::string&) { return 0; }         // f-0
    uint32_t f(std::string&&) { return 1; }        // f-1
    uint32_t f(std::string const&) { return 2; }   // f-2
    uint32_t f(std::string const&&) { return 3; }  // f-3
```
```cpp
    //  example/stdlib_and_concepts/utility_ut.cpp 21

    std::string       str{};
    std::string const cstr{};

    ASSERT_EQ(0, f(str));               // strはlvalue → f(std::string&)
    ASSERT_EQ(1, f(std::string{}));     // 一時オブジェクトはrvalue → f(std::string&&)
    ASSERT_EQ(1, f(std::move(str)));    // std::moveでrvalueに変換 → f(std::string&&)
    ASSERT_EQ(2, f(cstr));              // cstrはconst lvalue → f(std::string const&)
    ASSERT_EQ(3, f(std::move(cstr)));   // std::moveでconst rvalueに変換 → f(std::string const&&)
```

std::moveは以下の２つの概念ときわめて密接に関連しており、

* [rvalueリファレンス](core_lang_spec.md#SS_19_8_2)
* [moveセマンティクス](cpp_idioms.md#SS_21_5_3)

これら3つが組み合わさることで、不要なコピーを避けた高効率なリソース管理が実現される。

### std::forward <a id="SS_20_1_2"></a>
std::forwardは、下記の２つの概念を実現するための関数テンプレートである。

* [forwardingリファレンス](core_lang_spec.md#SS_19_8_3)
* [perfect forwarding](core_lang_spec.md#SS_19_8_5)

std::forwardを適切に使用することで、引数の値カテゴリを保持したまま転送でき、
move可能なオブジェクトの不要なコピーを避けることができる。

## type_traits <a id="SS_20_2"></a>
type_traitsは、型に関する情報をコンパイル時に取得・変換するためのメタ関数群で、
型特性の判定や型操作を静的に行うために用いられる。

以下に代表的なものをいくつか説明する。

- [std::integral_constant](stdlib_and_concepts.md#SS_20_2_1)
- [std::true_type](stdlib_and_concepts.md#SS_20_2_2)/[std::false_type](stdlib_and_concepts.md#SS_20_2_3)
- [std::is_same](stdlib_and_concepts.md#SS_20_2_4)
- [std::enable_if](stdlib_and_concepts.md#SS_20_2_5)
- [std::conditional](stdlib_and_concepts.md#SS_20_2_6)
- [std::is_void](stdlib_and_concepts.md#SS_20_2_7)
- [std::is_copy_assignable](stdlib_and_concepts.md#SS_20_2_8)
- [std::is_move_assignable](stdlib_and_concepts.md#SS_20_2_9)

### std::integral_constant <a id="SS_20_2_1"></a>
std::integral_constantは「テンプレートパラメータとして与えられた型とその定数から新たな型を定義する」
クラステンプレートである。

以下に簡単な使用例を示す。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 13

    using int3 = std::integral_constant<int, 3>;

    // std::is_same_vの2パラメータが同一であれば、std::is_same_v<> == true
    static_assert(std::is_same_v<int, int3::value_type>);
    static_assert(std::is_same_v<std::integral_constant<int, 3>, int3::type>);
    static_assert(int3::value == 3);

    using bool_true = std::integral_constant<bool, true>;

    static_assert(std::is_same_v<bool, bool_true::value_type>);
    static_assert(std::is_same_v<std::integral_constant<bool, true>, bool_true::type>);
    static_assert(bool_true::value == true);
```

また、すでに示したようにstd::true_type/std::false_typeを実装するためのクラステンプレートでもある。


### std::true_type <a id="SS_20_2_2"></a>
`std::true_type`(と`std::false_type`)は真/偽を返す標準ライブラリの[メタ関数](core_lang_spec.md#SS_19_11_2)群の戻り型となる型エイリアスであるため、
最も使われるテンプレートの一つである。

これらは、下記で確かめられる通り、後述する[std::integral_constant](stdlib_and_concepts.md#SS_20_2_1)を使い定義されている。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 32

    // std::is_same_vの2パラメータが同一であれば、std::is_same_v<> == true
    static_assert(std::is_same_v<std::integral_constant<bool, true>, std::true_type>);
    static_assert(std::is_same_v<std::integral_constant<bool, false>, std::false_type>);
```

それぞれの型が持つvalue定数は、下記のように定義されている。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 39

    static_assert(std::true_type::value, "must be true");
    static_assert(!std::false_type::value, "must be false");
```

これらが何の役に立つのか直ちに理解することは難しいが、
true/falseのメタ関数版と考えれば、追々理解できるだろう。

以下に簡単な使用例を示す。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 48

    // 引数の型がintに変換できるかどうかを判定する関数
    // decltypeの中でのみ使用されるため、定義は不要
    constexpr std::true_type  IsCovertibleToInt(int);  // intに変換できる型はこちら
    constexpr std::false_type IsCovertibleToInt(...);  // それ以外はこちら
```

上記の単体テストは下記のようになる。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 59

    static_assert(decltype(IsCovertibleToInt(1))::value);
    static_assert(decltype(IsCovertibleToInt(1u))::value);
    static_assert(!decltype(IsCovertibleToInt(""))::value);  // ポインタはintに変換不可

    struct ConvertibleToInt {
        operator int();
    };

    struct NotConvertibleToInt {};

    static_assert(decltype(IsCovertibleToInt(ConvertibleToInt{}))::value);
    static_assert(!decltype(IsCovertibleToInt(NotConvertibleToInt{}))::value);

    // なお、IsCovertibleToInt()やConvertibleToInt::operator int()は実際に呼び出されるわけでは
    // ないため、定義は必要なく宣言のみがあれば良い。
```

IsCovertibleToIntの呼び出しをdecltypeのオペランドにすることで、
std::true_typeかstd::false_typeを受け取ることができる。

### std::false_type <a id="SS_20_2_3"></a>
[std::true_type](stdlib_and_concepts.md#SS_20_2_2)を参照せよ。

### std::is_same <a id="SS_20_2_4"></a>

すでに上記の例でも使用したが、std::is_sameは2つのテンプレートパラメータが

* 同じ型である場合、std::true_type
* 違う型である場合、std::false_type

から派生した型となる。

以下に簡単な使用例を示す。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 99

    static_assert(std::is_same<int, int>::value);
    static_assert(std::is_same<int, int32_t>::value);   // 64ビットg++/clang++
    static_assert(!std::is_same<int, int64_t>::value);  // 64ビットg++/clang++
    static_assert(std::is_same<std::string, std::basic_string<char>>::value);
    static_assert(std::is_same<typename std::vector<int>::reference, int&>::value);
```

また、 C++17で導入されたstd::is_same_vは、定数テンプレートを使用し、
下記のように定義されている。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 90

    template <typename T, typename U>
    constexpr bool is_same_v{std::is_same<T, U>::value};
```

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 108

    static_assert(is_same_v<int, int>);
    static_assert(is_same_v<int, int32_t>);   // 64ビットg++/clang++
    static_assert(!is_same_v<int, int64_t>);  // 64ビットg++/clang++
    static_assert(is_same_v<std::string, std::basic_string<char>>);
    static_assert(is_same_v<typename std::vector<int>::reference, int&>);
```

このような簡潔な記述の一般形式は、

```
   T::value  -> T_v
   T::type   -> T_t
```

のように定義されている(このドキュメントのほとんど場所では、簡潔な形式を用いる)。

第1テンプレートパラメータが第2テンプレートパラメータの基底クラスかどうかを判断する
std::is_base_ofを使うことで下記のようにstd::is_sameの基底クラス確認することもできる。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 117

    static_assert(std::is_base_of_v<std::true_type, std::is_same<int, int>>);
    static_assert(std::is_base_of_v<std::false_type, std::is_same<int, char>>);
```

### std::enable_if <a id="SS_20_2_5"></a>
std::enable_ifは、bool値である第1テンプレートパラメータが

* trueである場合、型である第2テンプレートパラメータをメンバ型typeとして宣言する。
* falseである場合、メンバ型typeを持たない。

下記のコードはクラステンプレートの特殊化を用いたstd::enable_ifの実装例である。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 124

    template <bool T_F, typename T = void>
    struct enable_if;

    template <typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    template <typename T>
    struct enable_if<false, T> {  // メンバエイリアスtypeを持たない
    };

    template <bool COND, typename T = void>
    using enable_if_t = typename enable_if<COND, T>::type;
```

std::enable_ifの使用例を下記に示す。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 148

    static_assert(std::is_same_v<void, std::enable_if_t<true>>);
    static_assert(std::is_same_v<int, std::enable_if_t<true, int>>);
```

実装例から明らかなように

* std::enable_if\<true>::typeは[well-formed](core_lang_spec.md#SS_19_14_2)
* std::enable_if\<false>::typeは[ill-formed](core_lang_spec.md#SS_19_14_1)

となるため、下記のコードはコンパイルできない。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 155

    // 下記はill-formedとなるため、コンパイルできない。
    static_assert(std::is_same_v<void, std::enable_if_t<false>>);
    static_assert(std::is_same_v<int, std::enable_if_t<false, int>>);
```

std::enable_ifのこの特性と後述する[SFINAE](core_lang_spec.md#SS_19_11_1)により、
様々な静的ディスパッチを行うことができる。


### std::conditional <a id="SS_20_2_6"></a>

std::conditionalは、bool値である第1テンプレートパラメータが

* trueである場合、第2テンプレートパラメータ
* falseである場合、第3テンプレートパラメータ

をメンバ型typeとして宣言する。

下記のコードはクラステンプレートの特殊化を用いたstd::conditionalの実装例である。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 164

    template <bool T_F, typename, typename>
    struct conditional;

    template <typename T, typename U>
    struct conditional<true, T, U> {
        using type = T;
    };

    template <typename T, typename U>
    struct conditional<false, T, U> {
        using type = U;
    };

    template <bool COND, typename T, typename U>
    using conditional_t = typename conditional<COND, T, U>::type;
```

std::conditionalの使用例を下記に示す。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 189

    static_assert(std::is_same_v<int, std::conditional_t<true, int, char>>);
    static_assert(std::is_same_v<char, std::conditional_t<false, int, char>>);
```

### std::is_void <a id="SS_20_2_7"></a>
std::is_voidはテンプレートパラメータの型が

* voidである場合、std::true_type
* voidでない場合、std::false_type

から派生した型となる。

以下に簡単な使用例を示す。

```cpp
    //  example/stdlib_and_concepts/type_traits_ut.cpp 82

    static_assert(std::is_void<void>::value);
    static_assert(!std::is_void<int>::value);
    static_assert(!std::is_void<std::string>::value);
```

### std::is_copy_assignable <a id="SS_20_2_8"></a>
std::is_copy_assignableはテンプレートパラメータの型(T)がcopy代入可能かを調べる。
Tが[CopyAssignable要件](cpp_idioms.md#SS_21_5_5)を満たすためには`std::is_copy_assignable<T>`がtrueでなければならないが、
その逆が成立するとは限らない。


### std::is_move_assignable <a id="SS_20_2_9"></a>
std::is_move_assignableはテンプレートパラメータの型(T)がmove代入可能かを調べる。
Tが[MoveAssignable要件](cpp_idioms.md#SS_21_5_4)を満たすためには`std::is_move_assignable<T>`がtrueでなければならないが、
その逆が成立するとは限らない。


## 並列処理 <a id="SS_20_3"></a>

### std::thread <a id="SS_20_3_1"></a>
クラスthread は、新しい実行のスレッドの作成/待機/その他を行う機構を提供する。

```cpp
    //  example/stdlib_and_concepts/thread_ut.cpp 9

    struct Conflict {
        void     increment() { ++count_; }  // 非アトミック（データレースの原因）
        uint32_t count_ = 0;
    };
```
```cpp
    //  example/stdlib_and_concepts/thread_ut.cpp 19

    Conflict c;

    constexpr uint32_t inc_per_thread = 5'000'000;
    constexpr uint32_t expected       = 2 * inc_per_thread;

    auto worker = [&c] {  // スレッドのボディとなるラムダの定義
        for (uint32_t i = 0; i < inc_per_thread; ++i) {
            c.increment();
        }
    };

    std::thread t1{worker};  // ラムダworker関数を使用したスレッドの起動
    std::thread t2{worker};

    t1.join();  // スレッドの終了待ち
    t2.join();  // スレッドの終了待ち
                // 注意: join()もdetach()も呼ばずにスレッドオブジェクトが
                // デストラクトされると、std::terminateが呼ばれる

    // ASSERT_EQ(c.count_, expected);  t1とt2が++count_が競合するためこのテストは成立しないため、
    //                                 一例では次のようになる  c.count_: 6825610 expected: 10000000
    ASSERT_NE(c.count_, expected);
```

### std::mutex <a id="SS_20_3_2"></a>
mutex は、スレッド間で使用する共有リソースを排他制御するためのクラスである。 

| メンバ関数 | 動作説明                                                                                    |
|:-----------|---------------------------------------------------------------------------------------------|
| lock()     | lock()が即時リターンするスレッドはただ一つ。そうでない場合、unlock()が呼ばれるまでブロック  |
| unlock()   | lock()でブロックされていたスレッドの中から一つが動き出す                                    |


以下のコード例では、メンバ変数のインクリメントがスレッド間の競合を引き起こす(こういったコード領域を
[クリティカルセクション](cpp_idioms.md#SS_21_12_4)と呼ぶ)が、std::mutexによりこの問題を回避している。

```cpp
    //  example/stdlib_and_concepts/thread_ut.cpp 48

    struct Conflict {
        void increment()
        {
            mtx_.lock();  // クリティカルセクションの保護開始

            ++count_;

            mtx_.unlock();  // クリティカルセクションの保護終了
        }
        uint32_t   count_ = 0;
        std::mutex mtx_{};
    };
```
```cpp
    //  example/stdlib_and_concepts/thread_ut.cpp 66

    Conflict c;

    constexpr uint32_t inc_per_thread = 5'000'000;
    constexpr uint32_t expected       = 2 * inc_per_thread;

    auto worker = [&c] {  // スレッドのボディとなるラムダの定義
        for (uint32_t i = 0; i < inc_per_thread; ++i) {
            c.increment();
        }
    };

    std::thread t1{worker};  // ラムダworker関数を使用したスレッドの起動
    std::thread t2{worker};

    t1.join();  // スレッドの終了待ち
    t2.join();  // スレッドの終了待ち
                // 注意: join()もdetach()も呼ばずにスレッドオブジェクトが
                // デストラクトされると、std::terminateが呼ばれる

    ASSERT_EQ(c.count_, expected);
```

lock()を呼び出した状態で、unlock()を呼び出さなかった場合、デッドロックを引き起こしてしまうため、
永久に処理が完了しないバグの元となり得る。このような問題を避けるために、
mutexは通常、[std::lock_guard](stdlib_and_concepts.md#SS_20_4_1)と組み合わせて使われる。

### std::atomic <a id="SS_20_3_3"></a>
atomicクラステンプレートは、型Tをアトミック操作するためのものである。
[組み込み型](core_lang_spec.md#SS_19_1_2)に対する特殊化が提供されており、それぞれに特化した演算が用意されている。
[std::mutex](stdlib_and_concepts.md#SS_20_3_2)で示したような単純なコードではstd::atomicを使用して下記のように書く方が一般的である。

```cpp
    //  example/stdlib_and_concepts/thread_ut.cpp 92

    struct Conflict {
        void increment()
        {
            ++count_;  // ++count_は「count_の値の呼び出し -> その値のインクリメント、その値のcount_への書き戻し」である
                       // この一連の操作は排他的(アトミック)に行われる

        }  // lockオブジェクトのデストラクタでmtx_.unlock()が呼ばれる
        std::atomic<uint32_t> count_ = 0;
    };
```
```cpp
    //  example/stdlib_and_concepts/thread_ut.cpp 107

    Conflict c;

    constexpr uint32_t inc_per_thread = 5'000'000;
    constexpr uint32_t expected       = 2 * inc_per_thread;

    auto worker = [&c] {  // スレッドのボディとなるラムダの定義
        for (uint32_t i = 0; i < inc_per_thread; ++i) {
            c.increment();
        }
    };

    std::thread t1{worker};  // ラムダworker関数を使用したスレッドの起動
    std::thread t2{worker};

    t1.join();  // スレッドの終了待ち
    t2.join();  // スレッドの終了待ち
                // 注意: join()もdetach()も呼ばずにスレッドオブジェクトが
                // デストラクトされると、std::terminateが呼ばれる

    ASSERT_EQ(c.count_, expected);
```

### std::condition_variable <a id="SS_20_3_4"></a>
condition_variable は、特定のイベントが発生するまでスレッドの待ち合わせを行うためのクラスである。
最も単純な使用例を以下に示す(「[Spurious Wakeup](cpp_idioms.md#SS_21_12_11)」参照)。
```cpp
    //  example/stdlib_and_concepts/thread_ut.cpp 135

    std::mutex              mutex;
    std::condition_variable cond_var;
    bool                    event_occured = false;

    void notify()  // 通知を行うスレッドが呼び出す関数
    {
        auto lock = std::lock_guard{mutex};

        event_occured = true;

        cond_var.notify_all();  // wait()で待ち状態のすべてのスレッドを起こす
    }

    void wait()
    {
        auto lock = std::unique_lock{mutex};

        // notifyされるのを待つ。
        cond_var.wait(lock, []() noexcept { return event_occured; });  // Spurious Wakeup対策
    }
```
```cpp
    //  example/stdlib_and_concepts/thread_ut.cpp 162

    std::thread t1{[]() { wait(); /* 通知待ち */ }};
    std::thread t2{[]() { wait(); /* 通知待ち */ }};

    notify();  // 通知待ちのスレッドに通知

    t1.join();
    t2.join();
```

## ロック所有ラッパー <a id="SS_20_4"></a>
ロック所有ラッパーとはミューテックスのロックおよびアンロックを管理するための以下のクラスを指す。

- [std::lock_guard](stdlib_and_concepts.md#SS_20_4_1)
- [std::unique_lock](stdlib_and_concepts.md#SS_20_4_2)
- [std::scoped_lock](stdlib_and_concepts.md#SS_20_4_3)


### std::lock_guard <a id="SS_20_4_1"></a>
std::lock_guardを使わない問題のあるコードを以下に示す。

```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 14

    struct Conflict {
        void increment()
        {
            mtx_.lock();  // ++count_の排他のためのロック

            ++count_;

            mtx_.unlock();  // 上記のアンロック
        }

        uint32_t   count_ = 0;
        std::mutex mtx_{};
    };
```

上記で示したConflict::increment()には以下のようなリスクが存在する。

1. 関数が複雑化してエクセプションを投げる可能性がある場合、
    - エクセプションをこの関数内で捕捉し、ロック解除 (mtx_.unlock()) を行った上で再スローしなければならない。
    - ロック解除を忘れるとデッドロックにつながる。

2. 複数の return 文を持つように関数が拡張された場合、
    - すべての return の前で mtx_.unlock() を呼び出さなければならない。

これらを正しく管理するためには、重複コードが増え、関数の保守性が著しく低下する。

std::lock_guardを使用して、このような問題に対処したコードを以下に示す。

```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 63

    struct Conflict {
        void increment()
        {
            std::lock_guard<std::mutex> lock{mtx_};  // lockオブジェクトのコンストラクタでmtx_.lock()が呼ばれる
                                                     // ++count_の排他
            ++count_;

        }  // lockオブジェクトのデストラクタでmtx_.unlock()が呼ばれる
        uint32_t   count_ = 0;
        std::mutex mtx_{};
    };
```

オリジナルの単純な以下のincrement()と改善版を比較すると、大差ないように見えるが、

```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 19
    {
        mtx_.lock();  // ++count_の排他のためのロック

        ++count_;

        mtx_.unlock();  // 上記のアンロック
    }
```

オリジナルのコードで指摘したすべてのリスクが、わずか一行の変更で解決されている。

```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 68
    {
        std::lock_guard<std::mutex> lock{mtx_};  // lockオブジェクトのコンストラクタでmtx_.lock()が呼ばれる
                                                 // ++count_の排他
        ++count_;

    }  // lockオブジェクトのデストラクタでmtx_.unlock()が呼ばれる
```

### std::unique_lock <a id="SS_20_4_2"></a>
std::unique_lockとは、ミューテックスのロック管理を柔軟に行えるロックオブジェクトである。
std::lock_guardと異なり、ロックの手動解放や再取得が可能であり、特にcondition_variable::wait()と組み合わせて使用される。
wait()は内部でロックを一時的に解放し、通知受信後に再取得する。

下記の例では、IntQueue::push()、 IntQueue::pop_ng()、
IntQueue::pop_ok()の中で行われるIntQueue::q_へのアクセスで発生する競合を回避するためにIntQueue::mtx_を使用する。

下記のコード例では、[std::lock_guard](stdlib_and_concepts.md#SS_20_4_1)の説明で述べたようにmutex::lock()、mutex::unlock()を直接呼び出すのではなく、
std::unique_lockやstd::lock_guardによりmutexを使用する。

```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 112

    class IntQueue {
    public:
        void push(int v)
        {
            {
                std::lock_guard<std::mutex> lg{mtx_};  // ロック取得
                q_.push(v);
            }  // ロック解放

            cv_.notify_one();  // 待機中のスレッドを1つ起床
                               // 注: ロック解放後に呼び出すことで、起床したスレッドがすぐにロックを取得できる
        }

        int pop_ng()
        {
            std::unique_lock<std::mutex> lock{mtx_};
            cv_.wait(lock);  // NG: Spurious Wakeup対策なし
                             // 起床時に条件を再確認しないため、
                             // q_.empty() が true のまま起床する可能性がある
            int v = q_.front();
            q_.pop();  // 条件未確認アクセス（危険）

            return v;
        }

        int pop_ok()
        {
            std::unique_lock<std::mutex> lock{mtx_};
            cv_.wait(lock, [&q_ = q_] { return !q_.empty(); });  // waitの述語が true になるまで待機(Spurious Wakeup対策)
            // wait()の動作:
            // 1. 述語を評価してtrueならすぐreturn
            // 2. falseなら: unlock() → 通知待機 → 通知受信 → lock() → 述語再評価
            // 3. 述語がtrueになるまで2を繰り返す

            int v = q_.front();
            q_.pop();  // ここでは、q_.empty()は必ずfalse
            return v;
        }
    private:
        std::mutex              mtx_{};
        std::condition_variable cv_{};
        std::queue<int>         q_{};
    };
```
```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 168

    IntQueue           iq;
    constexpr int      end_data       = -1;
    constexpr uint32_t push_count_max = 10;

    // Producer
    std::thread t1([&iq] {
        for (uint32_t i = 0; i < push_count_max; ++i) {
            iq.push(100 + i);
        }

        iq.push(end_data);  // t2が-1を受信したらt2のループ終了
    });

    uint32_t pop_count = 0;

    std::thread t2([&iq, &pop_count] {
        for (;;) {
            if (int v = iq.pop_ok(); v == -1) {
                break;
            }
            else {
                ++pop_count;
            }
        }
    });

    t1.join();  // スレッドの終了待ち
    t2.join();  // スレッドの終了待ち

    ASSERT_EQ(push_count_max, pop_count);
```

一般に条件変数には、[Spurious Wakeup](cpp_idioms.md#SS_21_12_11)という問題があり、std::condition_variableも同様である。

上記の抜粋である下記のコード例では[Spurious Wakeup](cpp_idioms.md#SS_21_12_11)の対策が行われていないため、
意図通り動作しない可能性がある。

```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 127

    int pop_ng()
    {
        std::unique_lock<std::mutex> lock{mtx_};
        cv_.wait(lock);  // NG: Spurious Wakeup対策なし
                         // 起床時に条件を再確認しないため、
                         // q_.empty() が true のまま起床する可能性がある
        int v = q_.front();
        q_.pop();  // 条件未確認アクセス（危険）

        return v;
    }
```

下記のIntQueue::pop_ok()は、pop_ng()にSpurious Wakeupの対策を施したものである。

```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 141

    int pop_ok()
    {
        std::unique_lock<std::mutex> lock{mtx_};
        cv_.wait(lock, [&q_ = q_] { return !q_.empty(); });  // waitの述語が true になるまで待機(Spurious Wakeup対策)
        // wait()の動作:
        // 1. 述語を評価してtrueならすぐreturn
        // 2. falseなら: unlock() → 通知待機 → 通知受信 → lock() → 述語再評価
        // 3. 述語がtrueになるまで2を繰り返す

        int v = q_.front();
        q_.pop();  // ここでは、q_.empty()は必ずfalse
        return v;
    }
```

### std::scoped_lock <a id="SS_20_4_3"></a>
std::scoped_lockとは、複数のミューテックスを同時にロックするためのロックオブジェクトである。
C++17で導入され、デッドロックを回避しながら複数のミューテックスを安全にロックできる。

複数のミューテックスを扱う際、異なるスレッドが異なる順序でロックを取得しようとすると、
デッドロックが発生する可能性がある。下記の例では、2つの銀行口座間で送金を行う際に、
両方の口座を同時にロックする必要がある。

```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 205

    class BankAccount {
    public:
        explicit BankAccount(int balance) : balance_{balance} {}

        void transfer_ng(BankAccount& to, int amount)
        {
            std::lock_guard<std::mutex> lock1{mtx_};     // 自分のアカウントをロック
            std::lock_guard<std::mutex> lock2{to.mtx_};  // 相手のアカウントをロック
            // NG: 異なるスレッドが異なる順序でロックを取得するとデッドロックの可能性

            if (balance_ >= amount) {
                balance_ -= amount;
                to.balance_ += amount;
            }
        }

        void transfer_ok(BankAccount& to, int amount)
        {
            std::scoped_lock lock{mtx_, to.mtx_};  // 複数のmutexを安全にロック
            // デッドロック回避アルゴリズムにより、常に同じ順序でロックを取得

            if (balance_ >= amount) {
                balance_ -= amount;
                to.balance_ += amount;
            }
        }

        int balance() const
        {
            std::lock_guard<std::mutex> lock{mtx_};
            return balance_;
        }

    private:
        mutable std::mutex mtx_{};
        int                balance_;
    };
```
下記の例では、2つのスレッドがそれぞれ逆方向の送金を同時に行う。
transfer_ok()の代わりにtransfer_ng()を使用した場合、デッドロックが発生する可能性がある。

```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 254

    BankAccount acc1{1000};
    BankAccount acc2{1000};

    constexpr int transfer_amount = 100;
    constexpr int transfer_count  = 10;

    // スレッド1: acc1 → acc2 へ送金
    std::thread t1([&acc1, &acc2] {
        for (int i = 0; i < transfer_count; ++i) {
            acc1.transfer_ok(acc2, transfer_amount);
        }
    });

    // スレッド2: acc2 → acc1 へ送金
    std::thread t2([&acc2, &acc1] {
        for (int i = 0; i < transfer_count; ++i) {
            acc2.transfer_ok(acc1, transfer_amount);
        }
    });

    t1.join();
    t2.join();

    // 総額は変わらない
    ASSERT_EQ(acc1.balance() + acc2.balance(), 2000);
```

transfer_ng()がデッドロックを引き起こすシナリオは、以下のようなものである。

1. スレッド1が acc1.transfer_ng(acc2, 100) を呼び出し、acc1.mtx_ をロック
2. スレッド2が acc2.transfer_ng(acc1, 100) を呼び出し、acc2.mtx_ をロック
3. スレッド1が acc2.mtx_ のロックを試みるが、スレッド2が保持しているため待機
4. スレッド2が acc1.mtx_ のロックを試みるが、スレッド1が保持しているため待機
5. 互いに相手のロック解放を待ち続け、永遠に進まない（デッドロック）

<!-- pu:essential/plant_uml/mutex_deadlock.pu--><p><img src="data:image/png;base64,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" /></p>


下記のBankAccount::transfer_ok()は、std::scoped_lockを使用して前述したデッドロックを回避したものである。

```cpp
    //  example/stdlib_and_concepts/lock_ownership_wrapper_ut.cpp 225

    void transfer_ok(BankAccount& to, int amount)
    {
        std::scoped_lock lock{mtx_, to.mtx_};  // 複数のmutexを安全にロック
        // デッドロック回避アルゴリズムにより、常に同じ順序でロックを取得

        if (balance_ >= amount) {
            balance_ -= amount;
            to.balance_ += amount;
        }
    }
```

## スマートポインタ <a id="SS_20_5"></a>
スマートポインタは、C++標準ライブラリが提供するメモリ管理クラス群を指す。
生のポインタの代わりに使用され、リソース管理を容易にし、
メモリリークや二重解放といった問題を防ぐことを目的としている。

スマートポインタは通常、所有権とスコープに基づいてメモリの解放を自動的に行う。
C++標準ライブラリでは、主に以下の3種類のスマートポインタが提供されている。

* [std::unique_ptr](stdlib_and_concepts.md#SS_20_5_1)
    - [std::make_unique](stdlib_and_concepts.md#SS_20_5_1_1)
* [std::shared_ptr](stdlib_and_concepts.md#SS_20_5_2)
    - [std::make_shared](stdlib_and_concepts.md#SS_20_5_2_1)
    - [std::enable_shared_from_this](stdlib_and_concepts.md#SS_20_5_2_2)
    - [std::weak_ptr](stdlib_and_concepts.md#SS_20_5_3)
* [std::auto_ptr](stdlib_and_concepts.md#SS_20_5_4)

### std::unique_ptr <a id="SS_20_5_1"></a>
std::unique_ptrは、C++11で導入されたスマートポインタの一種であり、std::shared_ptrとは異なり、
[オブジェクトの排他所有](cpp_idioms.md#SS_21_4_1)を表すために用いられる。所有権は一つのunique_ptrインスタンスに限定され、
他のポインタと共有することはできない。ムーブ操作によってのみ所有権を移譲でき、
スコープを抜けると自動的にリソースが解放されるため、メモリ管理の安全性と効率性が向上する。

#### std::make_unique <a id="SS_20_5_1_1"></a>
[std::make_unique\<T\>(Args...)](https://cpprefjp.github.io/reference/memory/make_unique.html)は、
クラスTをダイナミックに生成し、そのポインタを保持するshared_ptrオブジェクトを生成する。

使用例については、「[オブジェクトの排他所有](cpp_idioms.md#SS_21_4_1)」を参照せよ。

### std::shared_ptr <a id="SS_20_5_2"></a>
std::shared_ptrは、同じくC++11で導入されたスマートポインタであり、[オブジェクトの共有所有](cpp_idioms.md#SS_21_4_2)を表すために用いられる。
複数のshared_ptrインスタンスが同じリソースを参照でき、
内部の参照カウントによって最後の所有者が破棄された時点でリソースが解放される。
[std::weak_ptr](stdlib_and_concepts.md#SS_20_5_3)は、shared_ptrと連携して使用されるスマートポインタであり、オブジェクトの非所有参照を表す。
参照カウントには影響せず、循環参照を防ぐために用いられる。weak_ptrから一時的にshared_ptrを取得するにはlock()を使用する。

#### std::make_shared <a id="SS_20_5_2_1"></a>
[std::make_shared\<T\>(Args...)](https://cpprefjp.github.io/reference/memory/make_shared.html)は、
クラスTをダイナミックに生成し、そのポインタを保持するshared_ptrオブジェクトを生成する。

使用例については、「[オブジェクトの共有所有](cpp_idioms.md#SS_21_4_2)」を参照せよ。

#### std::enable_shared_from_this <a id="SS_20_5_2_2"></a>
`std::enable_shared_from_this`は、`shared_ptr`で管理されているオブジェクトが、
自分自身への`shared_ptr`を安全に取得するための仕組みである。

この`std::enable_shared_from_this`が存在しない場合に発生するであろう問題のあるコードを以下に示す。

```cpp
    //  example/stdlib_and_concepts/enable_shared_from_this_ut.cpp 7

    class A {
    public:
        void register_self(std::vector<std::shared_ptr<A>>& vec) { vec.push_back(std::shared_ptr<A>{this}); }
    };
```
```cpp
    //  example/stdlib_and_concepts/enable_shared_from_this_ut.cpp 17

    auto sp1 = std::make_shared<A>();  // Aのポインタを管理するshared_ptr(sp1)が作られる
                                       // sp1が管理するポインタを便宜上、sp1_pointerと呼ぶことにする

    std::vector<std::shared_ptr<A>> vec;

    sp1->register_self(vec);  // vecに登録されるのはsp1_pointerを管理するshared_ptrであるが、
                              // vecに保持された「sp1_pointerを管理するshared_ptr」は、
                              // sp1と個別に生成されたため、sp1とuseカウンタを共有しない

    // ここまで来ると、
    // * sp1がスコープアウトするため、sp1がsp1_pointerを解放する。
    // * vecがスコープアウトするため、vecが保持するshared_ptrが、sp1_pointerを解放する。

    // 以上によりsp1_pointer二重解放されるため、未定義動作につながる
```

std::enable_shared_from_thisを継承し、`shared_from_this()`メソッドを使用し、この問題を解決したコード例を以下に示す。

std::enable_shared_from_thisは、内部にweak_ptrメンバを持っている。shared_ptrでオブジェクトが初めて管理される際、
shared_ptrのコンストラクタがenable_shared_from_thisの存在を検出し、内部のweak_ptrに制御ブロックへの参照を設定する。

`shared_from_this()`メソッドはこの内部のweak_ptrをlock()することで、
元のshared_ptrと制御ブロックを共有する新しいshared_ptrを生成する。
これにより、同一オブジェクトへの複数のshared_ptrが正しく参照カウントを共有できる。

```cpp
    //  example/stdlib_and_concepts/enable_shared_from_this_ut.cpp 38

    class A : public std::enable_shared_from_this<A> {
    public:
        void register_self(std::vector<std::shared_ptr<A>>& vec) { vec.push_back(shared_from_this()); }
    };
```
```cpp
    //  example/stdlib_and_concepts/enable_shared_from_this_ut.cpp 48

    auto sp1 = std::make_shared<A>();  // Aのポインタを管理するstd::shread_ptr(sp1)が作られる
                                       // sp1が管理するポインタを便宜上、sp1_pointerと呼ぶことにする

    std::vector<std::shared_ptr<A>> vec;

    sp1->register_self(vec);  // shared_from_this()により、
                              // sp1と同じuseカウンタを共有する新しいshared_ptrが生成されvecに格納される。

    // スコープアウト時には参照カウントが正しく管理されているため、
    // 最後のshared_ptrが破棄されるまでオブジェクトは解放されない
```

**[使用上の注意点]**

1. コンストラクタ内での使用禁止  
   コンストラクタ内でshared_from_this()を呼び出してはならない。なぜなら、コンストラクタ実行時点ではまだshared_ptrによる管理が完了しておらず、内部のweak_ptrが初期化されていないためである。この場合、std::bad_weak_ptr例外がスローされる。
2. shared_ptrでの管理が必須  
   オブジェクトがshared_ptrで管理されていない状態(例えばスタック上のオブジェクトや生のnew)でshared_from_this()を呼び出すと、std::bad_weak_ptr例外がスローされるか、未定義動作となる。
3. make_sharedの使用推奨  
   std::enable_shared_from_thisを継承したクラスのインスタンスは、必ずstd::make_sharedまたはshared_ptrのコンストラクタで生成する必要がある。

C++17以降では、`weak_from_this()`メソッドも提供されている。これはshared_from_this()と同様の仕組みだが、
weak_ptrを返すため[オブジェクトの循環所有](cpp_idioms.md#SS_21_4_3)を避けたい場合に有用である。

### std::weak_ptr <a id="SS_20_5_3"></a>
std::weak_ptrは、スマートポインタの一種である。

std::weak_ptrは参照カウントに影響を与えず、[std::shared_ptr](stdlib_and_concepts.md#SS_20_5_2)とオブジェクトを共有所有するのではなく、
その`shared_ptr`インスタンスとの関連のみを保持するのため、[オブジェクトの循環所有](cpp_idioms.md#SS_21_4_3)の問題を解決できる。

[オブジェクトの循環所有](cpp_idioms.md#SS_21_4_3)で示した問題のあるクラスの修正版を以下に示す
(以下の例では、Xは前のままで、Yのみ修正した)。

```cpp
    //  example/stdlib_and_concepts/weak_ptr_ut.cpp 9

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

        std::weak_ptr<X> const& ref_x() const noexcept { return x_; }

        // 自身の状態を返す ("Y alone" または "Y with X")
        std::string WhoYouAre() const;

        // x_が保持するオブジェクトの状態を返す ("None" またはY::WhoYouAre()に委譲)
        std::string WhoIsWith() const;

        static uint32_t constructed_counter;

    private:
        std::weak_ptr<X> x_{};
    };

    // Xのメンバ定義
    std::string X::WhoYouAre() const { return y_ ? "X with Y" : "X alone"; }
    std::string X::WhoIsWith() const { return y_ ? y_->WhoYouAre() : std::string{"None"}; }
    uint32_t    X::constructed_counter;

    // Yのメンバ定義
    std::string Y::WhoYouAre() const { return x_.use_count() != 0 ? "Y with X" : "Y alone"; }
    // 注: weak_ptrはbool変換をサポートしないため、use_count() != 0 で有効性を判定
    std::string Y::WhoIsWith() const  // 修正版Y::WhoIsWithの定義
    {
        if (auto x = x_.lock(); x) {  // Xオブジェクトが解放されていた場合、xはstd::shared_ptr<X>{}となり、falseと評価される
            return x->WhoYouAre();
        }
        else {
            return "None";
        }
    }
    uint32_t Y::constructed_counter;
```

このコードからわかるように修正版YはXオブジェクトを参照するために、
`std::shared_ptr<X>`の代わりに`std::weak_ptr<X>`を使用する。
Xオブジェクトにアクセスする必要があるときに、
下記のY::WhoIsWith()関数の内部処理のようにすることで、`std::weak_ptr<X>`オブジェクトから、
それと紐づいた`std::shared_ptr<X>`オブジェクトを生成できる。

なお、上記コードは[初期化付きif文](core_lang_spec.md#SS_19_9_5_3)を使うことで、
生成した`std::shared_ptr<X>`オブジェクトのスコープを最小に留めている。

```cpp
    //  example/stdlib_and_concepts/weak_ptr_ut.cpp 63
    std::string Y::WhoIsWith() const  // 修正版Y::WhoIsWithの定義
    {
        if (auto x = x_.lock(); x) {  // Xオブジェクトが解放されていた場合、xはstd::shared_ptr<X>{}となり、falseと評価される
            return x->WhoYouAre();
        }
        else {
            return "None";
        }
    }
```

Xと修正版Yの単体テストによりメモリーリークが修正されたことを以下に示す。

```cpp
    //  example/stdlib_and_concepts/weak_ptr_ut.cpp 82

    {
        ASSERT_EQ(X::constructed_counter, 0);
        ASSERT_EQ(Y::constructed_counter, 0);

        auto x0 = std::make_shared<X>();       // Xオブジェクトを持つshared_ptrの生成
        ASSERT_EQ(X::constructed_counter, 1);  // Xオブジェクトは1つ生成された

        ASSERT_EQ(x0.use_count(), 1);
        ASSERT_EQ(x0->WhoYouAre(), "X alone");  // x0.y_は何も保持していないので、"X alone"
        ASSERT_EQ(x0->ref_y().use_count(), 0);  // X::y_は何も持っていない

        {
            auto y0 = std::make_shared<Y>();

            ASSERT_EQ(Y::constructed_counter, 1);       // Yオブジェクトは1つ生成された
            ASSERT_EQ(y0.use_count(), 1);
            ASSERT_EQ(y0->ref_x().use_count(), 0);      // y0.x_は何も持っていない
            ASSERT_EQ(y0->WhoYouAre(), "Y alone");      // y0.x_は何も持っていないので、"Y alone"

            x0->Register(y0);                           // これによりx0.y_はy0と同じオブジェクトを持つ
            ASSERT_EQ(x0->WhoYouAre(), "X with Y");     // x0.y_はYオブジェクトを持っている

            y0->Register(x0);  // これによりy0.x_はx0と同じXオブジェクトを持つことができる
            ASSERT_EQ(y0->WhoIsWith(), "X with Y");     // y0.x_が持っているXオブジェクトはYを持っている
            
            // x0->Register(y0), y0->Register(x0)により Xオブジェクト、Yオブジェクトは相互参照できる状態となった
            ASSERT_EQ(X::constructed_counter, 1);       // 新しいオブジェクトが生成されるわけではない
            ASSERT_EQ(Y::constructed_counter, 1);       // 新しいオブジェクトが生成されるわけではない

            ASSERT_EQ(y0->WhoYouAre(), "Y with X");     // y0.x_はXオブジェクトを持っている
            ASSERT_EQ(x0->WhoYouAre(), "X with Y");     // x0.y_はYオブジェクトを持っている(再確認)
            ASSERT_EQ(y0->WhoIsWith(), "X with Y");     // y0が参照するXオブジェクトはYを持っている
            // 現時点で、x0とy0がお互いを相互参照できることが確認できた

            // weak_ptrを使用した効果によりXオブジェクトの参照カウントは増加しない
            ASSERT_EQ(x0.use_count(), 1);               // y0.x_はweak_ptrなので参照カウントに影響しない
            ASSERT_EQ(y0.use_count(), 2);               // x0.y_はshared_ptrなので参照カウントが2
            ASSERT_EQ(y0->ref_x().use_count(), 1);      // y0.x_の参照カウントは1
            ASSERT_EQ(x0->ref_y().use_count(), 2);      // x0.y_の参照カウントは2
        }  //ここでy0がスコープアウトするため、y0にはアクセスできないが、
           // x0を介して、y0が持っていたYオブジェクトにはアクセスできる

        ASSERT_EQ(x0->ref_y().use_count(), 1);  // y0がスコープアウトしたため、Yオブジェクトの参照カウントが減った
        ASSERT_EQ(x0->ref_y()->WhoYouAre(), "Y with X");  // x0.y_はXオブジェクトを持っている
    }  // この次の行で、x0はスコープアウトし、以下の処理が実行される:
       //   1. x0のデストラクタが呼ばれ、x0.y_の参照カウントがデクリメント
       //   2. x0.y_の参照カウントが1→0になり、保持していたYオブジェクトを解放する
       //   3. Yオブジェクトのデストラクタ内でy_.x_(weak_ptr)が破棄されるが、weak_ptrなのでXオブジェクトの参照カウントには影響しない
       //   4. x0本体のデストラクタが完了し、Xオブジェクトの参照カウントが1→0になり、Xオブジェクトも解放される

    // 上記1-4によりダイナミックに生成されたオブジェクトは解放されたため、下記のテストが成立する
    ASSERT_EQ(X::constructed_counter, 0);
    ASSERT_EQ(Y::constructed_counter, 0);
```

上記コード例で見てきたように`std::weak_ptr`を使用することで:

- 循環参照によるメモリリークを防ぐことができる
- 必要に応じて`lock()`でオブジェクトにアクセスできる
- オブジェクトが既に解放されている場合は`lock()`が空の`shared_ptr`を返すため、安全に処理できる

### std::auto_ptr <a id="SS_20_5_4"></a>
`std::auto_ptr`はC++11以前に導入された初期のスマートポインタであるが、異常な[copyセマンティクス](cpp_idioms.md#SS_21_5_2)を持つため、
多くの誤用を生み出し、C++11から非推奨とされ、C++17から規格から排除された。


## Polymorphic Memory Resource(pmr) <a id="SS_20_6"></a>
Polymorphic Memory Resource(pmr)は、
動的メモリ管理の柔軟性と効率性を向上させるための、C++17から導入された仕組みである。

[std::pmr::polymorphic_allocator](stdlib_and_concepts.md#SS_20_6_2)はC++17で導入された標準ライブラリのクラスで、
C++のメモリリソース管理を抽象化するための機能を提供する。

例えば、std::vectorは以下のように宣言されていた。

```cpp
namespace std {
  template <class T, class Allocator = allocator<T>>
  class vector;
}
```

C++17では以下のエイリアスが追加された。

```cpp
namespace std::pmr {
  template <class T>
  using vector = std::vector<T, polymorphic_allocator<T>>;
}
```

他のコンテナに関してもほぼ同様のエイリアスが追加された。

C++17で導入されたstd::pmr名前空間は、カスタマイズ可能なメモリ管理を提供し、
特に標準ライブラリのコンテナと連携して効率化を図るための統一フレームワークを提供する。
std::pmrは、
カスタマイズ可能なメモリ管理を標準ライブラリのデータ構造に統合するための統一的なフレームワークであり、
特に標準ライブラリのコンテナと連携して、動的メモリ管理を効率化することができる。

std::pmrは以下のようなメモリ管理のカスタマイズを可能にする。

* メモリアロケータをポリモーフィック(動的に選択可能)にする。
* メモリ管理ポリシーをstd::pmr::memory_resourceで定義する。
* メモリリソースを再利用して効率的な動的メモリ管理を実現する。

std::pmrの主要なコンポーネントは以下の通りである。

* [std::pmr::memory_resource](stdlib_and_concepts.md#SS_20_6_1)  
* [std::pmr::polymorphic_allocator](stdlib_and_concepts.md#SS_20_6_2)  
* [pool_resource](stdlib_and_concepts.md#SS_20_6_3)

### std::pmr::memory_resource <a id="SS_20_6_1"></a>
std::pmr::memory_resourceは、
ユーザー定義のメモリリソースをカスタマイズし、
[std::pmr::polymorphic_allocator](stdlib_and_concepts.md#SS_20_6_2)を通じて利用可能にする[インターフェースクラス](core_lang_spec.md#SS_19_4_11)である。

std::pmr::memory_resourceから派生した具象クラスの実装を以下に示す。

```cpp
    //  example/stdlib_and_concepts/pmr_memory_resource_ut.cpp 64

    template <uint32_t MEM_SIZE>
    class memory_resource_variable final : public std::pmr::memory_resource {
    public:
        memory_resource_variable() noexcept
        {
            header_->next    = nullptr;
            header_->n_units = sizeof(buff_) / Inner_::unit_size;
        }

        size_t get_count() const noexcept { return unit_count_ * Inner_::unit_size; }
        bool   is_valid(void const* mem) const noexcept
        {
            return (&buff_ < mem) && (mem < &buff_.buffer[ArrayLength(buff_.buffer)]);
        }

        // ...

    private:
        using header_t = Inner_::header_t;

        Inner_::buffer_t<MEM_SIZE> buff_{};
        header_t*                  header_{reinterpret_cast<header_t*>(buff_.buffer)};
        mutable SpinLock           spin_lock_{};
        size_t                     unit_count_{sizeof(buff_) / Inner_::unit_size};
        size_t                     unit_count_min_{sizeof(buff_) / Inner_::unit_size};

        void* do_allocate(size_t size, size_t) override
        {
            auto n_units = (Roundup(Inner_::unit_size, size) / Inner_::unit_size) + 1;

            auto lock = std::lock_guard{spin_lock_};

            auto curr = header_;

            for (header_t* prev{nullptr}; curr != nullptr; prev = curr, curr = curr->next) {
                auto opt_next = std::optional<header_t*>{sprit(curr, n_units)};

                if (!opt_next) {
                    continue;
                }

                auto next = *opt_next;
                if (prev == nullptr) {
                    header_ = next;
                }
                else {
                    prev->next = next;
                }
                break;
            }

            if (curr != nullptr) {
                unit_count_ -= curr->n_units;
                unit_count_min_ = std::min(unit_count_, unit_count_min_);
                ++curr;
            }

            if (curr == nullptr) {
                throw std::bad_alloc{};
            }

            return curr;
        }

        void do_deallocate(void* mem, size_t, size_t) noexcept override
        {
            header_t* to_free = Inner_::set_back(mem);

            to_free->next = nullptr;

            auto lock = std::lock_guard{spin_lock_};

            unit_count_ += to_free->n_units;
            unit_count_min_ = std::min(unit_count_, unit_count_min_);

            if (header_ == nullptr) {
                header_ = to_free;
                return;
            }

            if (to_free < header_) {
                concat(to_free, header_);
                header_ = to_free;
                return;
            }

            header_t* curr = header_;

            for (; curr->next != nullptr; curr = curr->next) {
                if (to_free < curr->next) {  // 常に curr < to_free
                    concat(to_free, curr->next);
                    concat(curr, to_free);
                    return;
                }
            }

            concat(curr, to_free);
        }

        bool do_is_equal(const memory_resource& other) const noexcept override { return this == &other; }
    };
```

### std::pmr::polymorphic_allocator <a id="SS_20_6_2"></a>
std::pmr::polymorphic_allocatorはC++17で導入された標準ライブラリのクラスで、
C++のメモリリソース管理を抽象化するための機能を提供する。
[std::pmr::memory_resource](stdlib_and_concepts.md#SS_20_6_1)を基盤とし、
コンテナやアルゴリズムにカスタムメモリアロケーション戦略を容易に適用可能にする。
std::allocatorと異なり、型に依存せず、
ポリモーフィズムを活用してメモリリソースを切り替えられる点が特徴である。

すでに示したmemory_resource_variable([std::pmr::memory_resource](stdlib_and_concepts.md#SS_20_6_1))の単体テストを以下に示すことにより、
polymorphic_allocatorの使用例とする。

```cpp
    //  example/stdlib_and_concepts/pmr_memory_resource_ut.cpp 208

    constexpr uint32_t            max = 1024;
    memory_resource_variable<max> mrv;
    memory_resource_variable<max> mrv2;

    ASSERT_EQ(mrv, mrv);
    ASSERT_NE(mrv, mrv2);

    {
        auto remaings1 = mrv.get_count();

        ASSERT_GE(max, remaings1);

        // std::basic_stringにカスタムアロケータを適用
        using pmr_string = std::basic_string<char, std::char_traits<char>, std::pmr::polymorphic_allocator<char>>;
        std::pmr::polymorphic_allocator<char> allocator(&mrv);

        // カスタムアロケータを使って文字列を作成
        pmr_string str("custom allocator!", allocator);
        auto       remaings2 = mrv.get_count();
        // アサーション: 文字列の内容を確認

        ASSERT_GT(remaings1, remaings2);
        ASSERT_EQ("custom allocator!", str);

        ASSERT_TRUE(mrv.is_valid(str.c_str()));  // strの内部メモリがmrvの内部であることの確認

        auto str3 = str + str + str;
        ASSERT_EQ(str.size() * 3 + 1, str3.size() + 1);
        ASSERT_THROW(str3 = pmr_string(2000, 'a'), std::bad_alloc);  // メモリの枯渇テスト
    }

    ASSERT_GE(max, mrv.get_count());  // 解放後のメモリの回復のテスト
```

### pool_resource <a id="SS_20_6_3"></a>
pool_resourceは[std::pmr::memory_resource](stdlib_and_concepts.md#SS_20_6_1)を基底とする下記の2つの具象クラスである。

* std::pmr::synchronized_pool_resourceは下記のような特徴を持つメモリプールである。
    * 非同期のメモリプールリソース
    * シングルスレッド環境での高速なメモリ割り当てに適する
    * 排他制御のオーバーヘッドがない
    * 以下に使用例を示す。

```cpp
    //  example/stdlib_and_concepts/pool_resource_ut.cpp 10

    std::pmr::unsynchronized_pool_resource pool_resource(
        std::pmr::pool_options{
            .max_blocks_per_chunk        = 10,   // チャンクあたりの最大ブロック数
            .largest_required_pool_block = 1024  // 最大ブロックサイズ
        },
        std::pmr::new_delete_resource()  // フォールバックリソース
    );

    // vectorを使用したメモリ割り当てのテスト
    {
        std::pmr::vector<int> vec{&pool_resource};

        // ベクターへの要素追加
        vec.push_back(42);
        vec.push_back(100);

        // メモリ割り当てと要素の検証
        ASSERT_EQ(vec.size(), 2);
        ASSERT_EQ(vec[0], 42);
        ASSERT_EQ(vec[1], 100);
    }
```

* std::pmr::unsynchronized_pool_resource は下記のような特徴を持つメモリプールである。
    * スレッドセーフなメモリプールリソース
    * 複数のスレッドから同時にアクセス可能
    * 内部で排他制御を行う
    * 以下に使用例を示す。

```cpp
    //  example/stdlib_and_concepts/pool_resource_ut.cpp 38

    std::pmr::synchronized_pool_resource shared_pool;

    auto thread_func = [&shared_pool](int thread_id) {
        std::pmr::vector<int> local_vec{&shared_pool};

        // スレッドごとに異なる要素を追加
        local_vec.push_back(thread_id * 10);
        local_vec.push_back(thread_id * 20);

        ASSERT_EQ(local_vec.size(), 2);
    };

    // 複数スレッドでの同時使用
    std::thread t1(thread_func, 1);
    std::thread t2(thread_func, 2);

    t1.join();
    t2.join();
```


## コンテナ <a id="SS_20_7"></a>
データを格納し、
効率的に操作するための汎用的なデータ構造を提供するC++標準ライブラリの下記のようなクラス群である。

* [シーケンスコンテナ(Sequence Containers)](stdlib_and_concepts.md#SS_20_7_1)
* [連想コンテナ(Associative Containers)(---)
* [無順序連想コンテナ(Unordered Associative Containers)](stdlib_and_concepts.md#SS_20_7_3)
* [コンテナアダプタ(Container Adapters)](stdlib_and_concepts.md#SS_20_7_4)
* [特殊なコンテナ](stdlib_and_concepts.md#SS_20_7_5)

### シーケンスコンテナ(Sequence Containers) <a id="SS_20_7_1"></a>
データが挿入順に保持され、順序が重要な場合に使用する。

| コンテナ                 | 説明                                                                |
|--------------------------|---------------------------------------------------------------------|
| `std::vector`            | 動的な配列で、ランダムアクセスが高速。末尾への挿入/削除が効率的     |
| `std::deque`             | 両端に効率的な挿入/削除が可能な動的配列                             |
| `std::list`              | 双方向リスト。要素の順序を維持し、中間の挿入/削除が効率的           |
| [std::forward_list](stdlib_and_concepts.md#SS_20_7_1_1) | 単方向リスト。軽量だが、双方向の操作はできない                      |
| `std::array`             | 固定長配列で、サイズがコンパイル時に決まる                          |
| `std::string`            | 可変長の文字列を管理するクラス(厳密には`std::basic_string`の特殊化) |

#### std::forward_list <a id="SS_20_7_1_1"></a>

```cpp
    //  example/stdlib_and_concepts/container_ut.cpp 14

    std::forward_list<int> fl{1, 2, 3};

    // 要素の挿入
    EXPECT_EQ(fl.front(), 1);
    fl.push_front(0);
    EXPECT_EQ(fl.front(), 0);

    auto it = fl.begin();
    EXPECT_EQ(*++it, 1);
    EXPECT_EQ(*++it, 2);
    EXPECT_EQ(*++it, 3);
```

### 連想コンテナ(Associative Containers) <a id="SS_20_7_2"></a>
データがキーに基づいて自動的にソートされ、検索が高速である。

| コンテナ           | 説明                                             |
|--------------------|--------------------------------------------------|
| `std::set`         | 要素がソートされ、重複が許されない集合           |
| `std::multiset`    | ソートされるが、重複が許される集合               |
| `std::map`         | ソートされたキーと値のペアを保持。キーは一意     |
| `std::multimap`    | ソートされたキーと値のペアを保持。キーは重複可能 |

### 無順序連想コンテナ(Unordered Associative Containers) <a id="SS_20_7_3"></a>
ハッシュテーブルを基盤としたコンテナで、順序を保証しないが高速な検索を提供する。

| コンテナ                  | 説明                                                   |
|---------------------------|--------------------------------------------------------|
| [std::unordered_set](stdlib_and_concepts.md#SS_20_7_3_1) | ハッシュテーブルベースの集合。重複は許されない         |
| `std::unordered_multiset` | ハッシュテーブルベースの集合。重複が許される           |
| [std::unordered_map](stdlib_and_concepts.md#SS_20_7_3_2) | ハッシュテーブルベースのキーと値のペア。キーは一意     |
| `std::unordered_multimap` | ハッシュテーブルベースのキーと値のペア。キーは重複可能 |
| [std::type_index](stdlib_and_concepts.md#SS_20_7_3_3)    | 型情報型を連想コンテナのキーとして使用するためのクラス |

#### std::unordered_set <a id="SS_20_7_3_1"></a>

```cpp
    //  example/stdlib_and_concepts/container_ut.cpp 32

    std::unordered_set<int> uset{1, 2, 3};

    // 要素の挿入
    uset.insert(4);
    uset.insert(5);

    // 存在確認
    EXPECT_NE(uset.find(1), uset.end());
    EXPECT_NE(uset.find(4), uset.end());
    EXPECT_EQ(uset.find(6), uset.end());

    // サイズの確認
    EXPECT_EQ(uset.size(), 5);
```

#### std::unordered_map <a id="SS_20_7_3_2"></a>

```cpp
    //  example/stdlib_and_concepts/container_ut.cpp 52

    std::unordered_map<int, std::string> umap;

    // 要素の挿入
    umap[1] = "one";
    umap[2] = "two";
    umap[3] = "three";

    // 要素の確認
    EXPECT_EQ(umap[1], "one");
    EXPECT_EQ(umap[2], "two");
    EXPECT_EQ(umap[3], "three");

    // 存在確認
    EXPECT_NE(umap.find(1), umap.end());
    EXPECT_EQ(umap.find(4), umap.end());
```

#### std::type_index <a id="SS_20_7_3_3"></a>
std::type_indexはコンテナではないが、
型情報型を連想コンテナのキーとして使用するためのクラスであるため、この場所に掲載する。

```cpp
    //  example/stdlib_and_concepts/container_ut.cpp 74

    std::unordered_map<std::type_index, std::string> type_map;

    // std::type_indexを使って型をキーとしてマッピング
    type_map[typeid(int)]         = "int";
    type_map[typeid(double)]      = "double";
    type_map[typeid(std::string)] = "string";

    // マッピングの確認
    EXPECT_EQ(type_map[typeid(int)], "int");
    EXPECT_EQ(type_map[typeid(double)], "double");
    EXPECT_EQ(type_map[typeid(std::string)], "string");

    // 存在しない型の確認
    EXPECT_EQ(type_map.find(typeid(float)), type_map.end());
```


### コンテナアダプタ(Container Adapters) <a id="SS_20_7_4"></a>
特定の操作のみを公開するためのラッパーコンテナ。

| コンテナ              | 説明                                     |
|-----------------------|------------------------------------------|
| `std::stack`          | LIFO(後入れ先出し)操作を提供するアダプタ |
| `std::queue`          | FIFO(先入れ先出し)操作を提供するアダプタ |
| `std::priority_queue` | 優先度に基づく操作を提供するアダプタ     |

### 特殊なコンテナ <a id="SS_20_7_5"></a>
上記したようなコンテナとは一線を画すが、特定の用途や目的のために設計された一種のコンテナ。

| コンテナ             | 説明                                                       |
|----------------------|------------------------------------------------------------|
| `std::span`          | 生ポインタや配列を抽象化し、安全に操作するための軽量ビュー |
| `std::bitset`        | 固定長のビット集合を管理するクラス                         |
| `std::basic_string`  | カスタム文字型をサポートする文字列コンテナ                 |

## std::optional <a id="SS_20_8"></a>
C++17から導入されたstd::optionalには、以下のような2つの用途がある。
以下の用途2から、
このクラスがオブジェクトのダイナミックなメモリアロケーションを行うような印象を受けるが、
そのようなことは行わない。
このクラスがオブジェクトのダイナミックな生成が必要になった場合、プレースメントnewを実行する。
ただし、std::optionalが保持する型自身がnewを実行する場合は、この限りではない。

1. 関数の任意の型の[戻り値の無効表現](stdlib_and_concepts.md#SS_20_8_1)を持たせる
2. [オブジェクトの遅延初期化](stdlib_and_concepts.md#SS_20_8_2)する(初期化処理が重く、
   条件によってはそれが無駄になる場合にこの機能を使う)

### 戻り値の無効表現 <a id="SS_20_8_1"></a>
```cpp
    //  example/stdlib_and_concepts/optional_ut.cpp 11

    /// @brief 指定されたファイル名から拡張子を取得する。
    /// @param filename ファイル名（パスを含む場合も可）
    /// @return 拡張子を文字列として返す。拡張子がない場合は std::nullopt を返す。
    std::optional<std::string> file_extension(std::string const& filename)
    {
        size_t pos = filename.rfind('.');
        if (pos == std::string::npos || pos == filename.length() - 1) {
            return std::nullopt;  // 値が存在しない
        }
        return filename.substr(pos + 1);
    }
```
```cpp
    //  example/stdlib_and_concepts/optional_ut.cpp 28

    auto ret0 = file_extension("xxx.yyy");

    ASSERT_TRUE(ret0);  // 値を保持している
    ASSERT_EQ("yyy", *ret0);

    auto ret1 = file_extension("xxx");

    ASSERT_FALSE(ret1);  // 値を保持していない
    // ASSERT_THROW(*ret1, std::exception);  // 未定義動作(エクセプションは発生しない)
    ASSERT_THROW(ret1.value(), std::bad_optional_access);  // 値非保持の場合、エクセプション発生
```

### オブジェクトの遅延初期化 <a id="SS_20_8_2"></a>
```cpp
    //  example/stdlib_and_concepts/optional_ut.cpp 43

    class HeavyResource {
    public:
        HeavyResource() : large_erea_{0xdeadbeaf}
        {  // large_erea_[0]を44にする
            initialied = true;
        }
        bool     is_ready() const noexcept { return large_erea_[0] == 0xdeadbeaf; }
        uint32_t operator[](size_t index) const noexcept { return large_erea_[index]; }

        static bool initialied;

    private:
        uint32_t large_erea_[1024];
    };
    bool HeavyResource::initialied;
```
```cpp
    //  example/stdlib_and_concepts/optional_ut.cpp 64

    std::optional<HeavyResource> resource;

    // resourceの内部のHeavyResourceは未初期化
    ASSERT_FALSE(resource.has_value());
    ASSERT_FALSE(HeavyResource::initialied);
    ASSERT_NE(0xdeadbeaf, (*resource)[0]);  // 未定義動作

    // resourceの内部のHeavyResourceの遅延初期化
    resource.emplace();  // std::optionalの内部でplacement newが実行される

    // ここから下は定義動作
    ASSERT_TRUE(HeavyResource::initialied);  // resourceの内部のHeavyResourceは初期化済み
    ASSERT_TRUE(resource.has_value());

    ASSERT_TRUE(resource->is_ready());
    ASSERT_EQ(0xdeadbeaf, (*resource)[0]);
```

## std::variant <a id="SS_20_9"></a>
std::variantは、C++17で導入された型安全なunionである。
このクラスは複数の型のうち1つの値を保持することができ、
従来のunionに伴う低レベルな操作の安全性の問題を解消するために設計された。

std::variant自身では、オブジェクトのダイナミックな生成が必要な場合でも通常のnewを実行せず、
代わりにプレースメントnewを用いる
(以下のコード例のようにstd::variantが保持する型自身がnewを実行する場合は、この限りではない)。

以下にstd::variantの典型的な使用例を示す。

```cpp
    //  example/stdlib_and_concepts/variant_ut.cpp 13

    std::variant<int, std::string, double> var  = 10;
    auto                                   var2 = var;  // コピーコンストラクタの呼び出し

    ASSERT_EQ(std::get<int>(var), 10);  // 型intの値を取り出す

    // 型std::stringの値を取り出すが、その値は持っていないのでエクセプション発生
    ASSERT_THROW(std::get<std::string>(var), std::bad_variant_access);

    var = "variant";  // "variant"はstd::stringに変更され、varにムーブされる
    ASSERT_EQ(std::get<std::string>(var), "variant");

    ASSERT_NE(var, var2);  // 保持している値の型が違う

    var2.emplace<std::string>("variant");  // "variant"からvar2の値を直接生成するため、
                                           // 文字列代入より若干効率的
    ASSERT_EQ(var, var2);

    var = 1.0;
    ASSERT_FLOAT_EQ(std::get<2>(var), 1.0);  // 2番目の型の値を取得
```

std::variantとstd::visit([Visitor](design_pattern.md#SS_9_2_5)パターンの実装の一種)を組み合わせた場合の使用例を以下に示す。

```cpp
    //  example/stdlib_and_concepts/variant_ut.cpp 37

    void output_from_variant(std::variant<int, double, std::string> const& var, std::ostringstream& oss)
    {
        std::visit([&oss](auto&& arg) { oss.str().empty() ? oss << arg : oss << "|" << arg; }, var);
    }
```
```cpp
    //  example/stdlib_and_concepts/variant_ut.cpp 47

    std::ostringstream                     oss;
    std::variant<int, double, std::string> var = 42;

    output_from_variant(var, oss);
    ASSERT_EQ("42", oss.str());

    var = 3.14;
    output_from_variant(var, oss);
    ASSERT_EQ("42|3.14", oss.str());

    var = "Hello, world!";
    output_from_variant(var, oss);
    ASSERT_EQ("42|3.14|Hello, world!", oss.str());
```

## オブジェクトの比較 <a id="SS_20_10"></a>
### std::rel_ops <a id="SS_20_10_1"></a>
クラスに`operator==`と`operator<`の2つの演算子が定義されていれば、
それがメンバか否かにかかわらず、他の比較演算子 !=、<=、>、>= はこれらを基に自動的に導出できる。
std::rel_opsでは`operator==`と`operator<=` を基に他の比較演算子を機械的に生成する仕組みが提供されている。

次の例では、std::rel_opsを利用して、少ないコードで全ての比較演算子をサポートする例を示す。

```cpp
    //  example/stdlib_and_concepts/comparison_stdlib_ut.cpp 12

    class Integer {
    public:
        Integer(int x) noexcept : x_{x} {}

        // operator==とoperator<だけを定義
        int get() const noexcept { return x_; }

        // メンバ関数の比較演算子
        bool operator==(const Integer& other) const noexcept { return x_ == other.x_; }
        bool operator<(const Integer& other) const noexcept { return x_ < other.x_; }

    private:
        int x_;
    };
```

```cpp
    //  example/stdlib_and_concepts/comparison_stdlib_ut.cpp 32

    using namespace std::rel_ops;  // std::rel_opsを使うために名前空間を追加

    auto a = Integer{5};
    auto b = Integer{10};
    auto c = Integer{5};

    // std::rel_opsとは無関係に直接定義
    ASSERT_TRUE(a == c);   // a == c
    ASSERT_FALSE(a == b);  // !(a == b)
    ASSERT_TRUE(a < b);    // aはbより小さい
    ASSERT_FALSE(b < a);   // bはaより小さくない

    // std::rel_ops による!=, <=, >, >=の定義
    ASSERT_TRUE(a != b);   // aとbは異なる
    ASSERT_TRUE(a <= b);   // aはb以下
    ASSERT_TRUE(b > a);    // bはaより大きい
    ASSERT_FALSE(a >= b);  // aはb以上ではない
```

なお、std::rel_opsはC++20から導入された[<=>演算子](core_lang_spec.md#SS_19_6_4_1)により不要になったため、
非推奨とされた。

### std::tuppleを使用した比較演算子の実装方法 <a id="SS_20_10_2"></a>
クラスのメンバが多い場合、[==演算子](core_lang_spec.md#SS_19_6_3)で示したような方法は、
可読性、保守性の問題が発生する場合が多い。下記に示す方法はこの問題を幾分緩和する。

```cpp
    //  example/stdlib_and_concepts/comparison_stdlib_ut.cpp 56

    struct Point {
        int x;
        int y;

        bool operator==(const Point& other) const noexcept { return std::tie(x, y) == std::tie(other.x, other.y); }

        bool operator<(const Point& other) const noexcept { return std::tie(x, y) < std::tie(other.x, other.y); }
    };
```
```cpp
    //  example/stdlib_and_concepts/comparison_stdlib_ut.cpp 70

    auto a = Point{1, 2};
    auto b = Point{1, 3};
    auto c = Point{1, 2};

    using namespace std::rel_ops;  // std::rel_opsを使うために名前空間を追加

    ASSERT_TRUE(a == c);
    ASSERT_TRUE(a != b);
    ASSERT_TRUE(a < b);
    ASSERT_FALSE(a > b);
```

## その他 <a id="SS_20_11"></a>
### SSO(Small String Optimization) <a id="SS_20_11_1"></a>
一般にstd::stringで文字列を保持する場合、newしたメモリが使用される。
64ビット環境であれば、newしたメモリのアドレスを保持する領域は8バイトになる。
std::stringで保持する文字列が終端の'\0'も含め8バイト以下である場合、
アドレスを保持する領域をその文字列の格納に使用すれば、newする必要がない(当然deleteも不要)。
こうすることで、短い文字列を保持するstd::stringオブジェクトは効率的に動作できる。

SOOとはこのような最適化を指す。

### heap allocation elision <a id="SS_20_11_2"></a>
C++11までの仕様では、new式によるダイナミックメモリアロケーションはコードに書かれた通りに、
実行されなければならず、ひとまとめにしたり省略したりすることはできなかった。
つまり、ヒープ割り当てに対する最適化は認められなかった。
ダイナミックメモリアロケーションの最適化のため、この制限は緩和され、
new/deleteの呼び出しをまとめたり省略したりすることができるようになった。

```cpp
    //  example/stdlib_and_concepts/heap_allocation_elision_ut.cpp 4

    void lump()  // 実装によっては、ダイナミックメモリアロケーションをまとめらる場合がある
    {
        int* p1 = new int{1};
        int* p2 = new int{2};
        int* p3 = new int{3};

        // 何らかの処理

        delete p1;
        delete p2;
        delete p3;

        // 上記のメモリアロケーションは、実装によっては下記のように最適化される場合がある

        int* p = new int[3]{1, 2, 3};
        // 何らかの処理

        delete[] p;
    }

    int emit()  // ダイナミックメモリアロケーションの省略
    {
        int* p = new int{10};
        delete p;

        // 上記のメモリアロケーションは、下記の用にスタックの変数に置き換える最適化が許される

        int n = 10;

        return n;
    }
```

この最適化により、std::make_sharedのようにstd::shared_ptrの参照カウントを管理するメモリブロックと、
オブジェクトの実体を1つのヒープ領域に割り当てることができ、
ダイナミックメモリアロケーションが1回に抑えられるため、メモリアクセスが高速化される。



