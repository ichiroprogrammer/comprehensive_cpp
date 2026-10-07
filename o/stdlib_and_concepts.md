<!-- essential/md/stdlib_and_concepts.md -->
# 標準ライブラリとプログラミングの概念 <a id="SS_20"></a>
この章では、C++標準ライブラリやそれによって導入されたプログラミングの概念等の紹介を行う。

___

__この章の構成__

[ユーティリティ](stdlib_and_concepts.md#SS_20_1)  
&emsp;[std::move](stdlib_and_concepts.md#SS_20_1_1)  
&emsp;[std::forward](stdlib_and_concepts.md#SS_20_1_2)  

[type_traits](stdlib_and_concepts.md#SS_20_2)  
&emsp;[std::integral_constant](stdlib_and_concepts.md#SS_20_2_1)  
&emsp;[std::true_type](stdlib_and_concepts.md#SS_20_2_2)  
&emsp;[std::false_type](stdlib_and_concepts.md#SS_20_2_3)  
&emsp;[std::is_same](stdlib_and_concepts.md#SS_20_2_4)  
&emsp;[std::enable_if](stdlib_and_concepts.md#SS_20_2_5)  
&emsp;[std::conditional](stdlib_and_concepts.md#SS_20_2_6)  
&emsp;[std::is_void](stdlib_and_concepts.md#SS_20_2_7)  
&emsp;[std::is_copy_assignable](stdlib_and_concepts.md#SS_20_2_8)  
&emsp;&emsp;[CopyAssignable要件](stdlib_and_concepts.md#SS_20_2_8_1)  

&emsp;[std::is_move_assignable](stdlib_and_concepts.md#SS_20_2_9)  
&emsp;&emsp;[MoveAssignable要件](stdlib_and_concepts.md#SS_20_2_9_1)  

[標準エクセプションクラス](stdlib_and_concepts.md#SS_20_3)  
&emsp;[std::exception](stdlib_and_concepts.md#SS_20_3_1)  

[並列処理](stdlib_and_concepts.md#SS_20_4)  
&emsp;[std::thread](stdlib_and_concepts.md#SS_20_4_1)  
&emsp;[std::mutex](stdlib_and_concepts.md#SS_20_4_2)  
&emsp;[std::atomic](stdlib_and_concepts.md#SS_20_4_3)  
&emsp;[std::condition_variable](stdlib_and_concepts.md#SS_20_4_4)  

[ロック所有ラッパー](stdlib_and_concepts.md#SS_20_5)  
&emsp;[std::lock_guard](stdlib_and_concepts.md#SS_20_5_1)  
&emsp;[std::unique_lock](stdlib_and_concepts.md#SS_20_5_2)  
&emsp;[std::scoped_lock](stdlib_and_concepts.md#SS_20_5_3)  

[スマートポインタとオブジェクトの所有権](stdlib_and_concepts.md#SS_20_6)  
&emsp;[スマートポインタ](stdlib_and_concepts.md#SS_20_6_1)  
&emsp;&emsp;[std::unique_ptr](stdlib_and_concepts.md#SS_20_6_1_1)  
&emsp;&emsp;[std::make_unique](stdlib_and_concepts.md#SS_20_6_1_2)  
&emsp;&emsp;[std::shared_ptr](stdlib_and_concepts.md#SS_20_6_1_3)  
&emsp;&emsp;[std::weak_ptr](stdlib_and_concepts.md#SS_20_6_1_4)  
&emsp;&emsp;[std::auto_ptr](stdlib_and_concepts.md#SS_20_6_1_5)  

&emsp;[オブジェクトの所有権](stdlib_and_concepts.md#SS_20_6_2)  
&emsp;&emsp;[オブジェクトの排他所有](stdlib_and_concepts.md#SS_20_6_2_1)  
&emsp;&emsp;[オブジェクトの共有所有](stdlib_and_concepts.md#SS_20_6_2_2)  
&emsp;&emsp;[オブジェクトの循環所有](stdlib_and_concepts.md#SS_20_6_2_3)  

[Polymorphic Memory Resource(pmr)](stdlib_and_concepts.md#SS_20_7)  
&emsp;[std::pmr::memory_resource](stdlib_and_concepts.md#SS_20_7_1)  
&emsp;[std::pmr::polymorphic_allocator](stdlib_and_concepts.md#SS_20_7_2)  
&emsp;[pool_resource](stdlib_and_concepts.md#SS_20_7_3)  

[コンテナ](stdlib_and_concepts.md#SS_20_8)  
&emsp;[シーケンスコンテナ(Sequence Containers)](stdlib_and_concepts.md#SS_20_8_1)  
&emsp;&emsp;[std::forward_list](stdlib_and_concepts.md#SS_20_8_1_1)  

&emsp;[連想コンテナ(Associative Containers)](stdlib_and_concepts.md#SS_20_8_2)  
&emsp;[無順序連想コンテナ(Unordered Associative Containers)](stdlib_and_concepts.md#SS_20_8_3)  
&emsp;&emsp;[std::unordered_set](stdlib_and_concepts.md#SS_20_8_3_1)  
&emsp;&emsp;[std::unordered_map](stdlib_and_concepts.md#SS_20_8_3_2)  
&emsp;&emsp;[std::type_index](stdlib_and_concepts.md#SS_20_8_3_3)  

&emsp;[コンテナアダプタ(Container Adapters)](stdlib_and_concepts.md#SS_20_8_4)  
&emsp;[特殊なコンテナ](stdlib_and_concepts.md#SS_20_8_5)  

[std::optional](stdlib_and_concepts.md#SS_20_9)  
&emsp;[戻り値の無効表現](stdlib_and_concepts.md#SS_20_9_1)  
&emsp;[オブジェクトの遅延初期化](stdlib_and_concepts.md#SS_20_9_2)  

[std::variant](stdlib_and_concepts.md#SS_20_10)  
[オブジェクトの比較](stdlib_and_concepts.md#SS_20_11)  
&emsp;[std::rel_ops](stdlib_and_concepts.md#SS_20_11_1)  
&emsp;[std::tuppleを使用した比較演算子の実装方法](stdlib_and_concepts.md#SS_20_11_2)  

[その他](stdlib_and_concepts.md#SS_20_12)  
&emsp;[SSO(Small String Optimization)](stdlib_and_concepts.md#SS_20_12_1)  
&emsp;[heap allocation elision](stdlib_and_concepts.md#SS_20_12_2)  
  
  

[インデックス](comprehensive_intro.md#SS_1_3)に戻る。  

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
* [moveセマンティクス](class_design.md#SS_8_3_3)

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
Tが[CopyAssignable要件](stdlib_and_concepts.md#SS_20_2_8_1)を満たすためには`std::is_copy_assignable<T>`がtrueでなければならないが、
その逆が成立するとは限らない。

#### CopyAssignable要件 <a id="SS_20_2_8_1"></a>
CopyAssignable要件は、C++において型がcopy代入をサポートするために満たすべき条件を指す。

1. 動作が定義されていること  
   代入操作は未定義動作を引き起こしてはならない。自己代入（同じオブジェクトを代入する場合）においても正しく動作し、
   リソースリークを引き起こさないことが求められる。

2. 値の保持  
   代入後、代入先のオブジェクトの値は代入元のオブジェクトの値と一致していなければならない。

3. 正しいセマンティクス  
   copy代入によって代入元のオブジェクトが変更されてはならない(「[copyセマンティクス](class_design.md#SS_8_3_2)」に注意)。
   代入先のオブジェクトが保持していたリソース(例: メモリ)は適切に解放される必要がある。

4. デフォルト実装  
   copy代入演算子が明示的に定義されていない場合でも、
   クラスが一定の条件(例: copy不可能なメンバが存在しないこと)を満たしていれば、
   コンパイラがデフォルトの実装(「[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)」参照)を生成する。


### std::is_move_assignable <a id="SS_20_2_9"></a>
std::is_move_assignableはテンプレートパラメータの型(T)がmove代入可能かを調べる。
Tが[MoveAssignable要件](stdlib_and_concepts.md#SS_20_2_9_1)を満たすためには`std::is_move_assignable<T>`がtrueでなければならないが、
その逆が成立するとは限らない。

#### MoveAssignable要件 <a id="SS_20_2_9_1"></a>
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
   これは、リソースの複製を避けることで達成される(「[moveセマンティクス](class_design.md#SS_8_3_3)」参照)。

5. デフォルト実装  
   move代入演算子が明示的に定義されていない場合でも、
   クラスが一定の条件(例: move不可能なメンバが存在しないこと)を満たしていれば、
   コンパイラがデフォルトの実装(「[特殊メンバ関数](core_lang_spec.md#SS_19_6_1)」参照)を生成する。

---

## 標準エクセプションクラス <a id="SS_20_3"></a>
C++標準ライブラリは、`<exception>`と`<stdexcept>`定義される標準エクセプションクラスを提供する。

### std::exception <a id="SS_20_3_1"></a>
exceptionクラスは、標準ライブラリが提供する全てのエクセプションクラスの基底クラスである。
標準ライブラリによって送出されるエクセプションオブジェクトのクラスは全て、このクラスから派生する。
したがって、標準のエクセプションは全てこのクラスで捕捉できる。

標準ライブラリによって送出されるエクセプションオブジェクトの派生の系譜を以下に示す。


```cpp
    // 標準ライブラリによって送出されるエクセプションオブジェクトの派生の系譜

    std::exception                      // すべての標準エクセプションの基底クラス
    ├── std::bad_alloc                  // メモリ確保の失敗
    ├── std::bad_cast                   // 不正なキャスト
    ├── std::bad_typeid                 // 不正なtypeid
    ├── std::bad_exception              // 予期しないエクセプション
    └── std::logic_error                // 論理エラー
        ├── std::invalid_argument
        ├── std::domain_error
        ├── std::length_error
        ├── std::out_of_range
        └── std::runtime_error          // 実行時エラー
            ├── std::range_error
            ├── std::overflow_error
            └── std::underflow_error
```

## 並列処理 <a id="SS_20_4"></a>
### std::thread <a id="SS_20_4_1"></a>
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

### std::mutex <a id="SS_20_4_2"></a>
mutex は、スレッド間で使用する共有リソースを排他制御するためのクラスである。 

| メンバ関数 | 動作説明                                                                                    |
|:-----------|---------------------------------------------------------------------------------------------|
| lock()     | lock()が即時リターンするスレッドはただ一つ。そうでない場合、unlock()が呼ばれるまでブロック  |
| unlock()   | lock()でブロックされていたスレッドの中から一つが動き出す                                    |


以下のコード例では、メンバ変数のインクリメントがスレッド間の競合を引き起こす(こういったコード領域を
[クリティカルセクション](glossary.md#SS_21_5_5)と呼ぶ)が、std::mutexによりこの問題を回避している。

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
mutexは通常、[std::lock_guard](stdlib_and_concepts.md#SS_20_5_1)と組み合わせて使われる。

### std::atomic <a id="SS_20_4_3"></a>
atomicクラステンプレートは、型Tをアトミック操作するためのものである。
[組み込み型](core_lang_spec.md#SS_19_1_2)に対する特殊化が提供されており、それぞれに特化した演算が用意されている。
[std::mutex](stdlib_and_concepts.md#SS_20_4_2)で示したような単純なコードではstd::atomicを使用して下記のように書く方が一般的である。

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

### std::condition_variable <a id="SS_20_4_4"></a>
condition_variable は、特定のイベントが発生するまでスレッドの待ち合わせを行うためのクラスである。
最も単純な使用例を以下に示す(「[Spurious Wakeup](glossary.md#SS_21_5_16)」参照)。

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

## ロック所有ラッパー <a id="SS_20_5"></a>
ロック所有ラッパーとはミューテックスのロックおよびアンロックを管理するための以下のクラスを指す。

- [std::lock_guard](stdlib_and_concepts.md#SS_20_5_1)
- [std::unique_lock](stdlib_and_concepts.md#SS_20_5_2)
- [std::scoped_lock](stdlib_and_concepts.md#SS_20_5_3)


### std::lock_guard <a id="SS_20_5_1"></a>
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

### std::unique_lock <a id="SS_20_5_2"></a>
std::unique_lockとは、ミューテックスのロック管理を柔軟に行えるロックオブジェクトである。
std::lock_guardと異なり、ロックの手動解放や再取得が可能であり、特にcondition_variable::wait()と組み合わせて使用される。
wait()は内部でロックを一時的に解放し、通知受信後に再取得する。

下記の例では、IntQueue::push()、 IntQueue::pop_ng()、
IntQueue::pop_ok()の中で行われるIntQueue::q_へのアクセスで発生する競合を回避するためにIntQueue::mtx_を使用する。

下記のコード例では、[std::lock_guard](stdlib_and_concepts.md#SS_20_5_1)の説明で述べたようにmutex::lock()、mutex::unlock()を直接呼び出すのではなく、
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

一般に条件変数には、[Spurious Wakeup](glossary.md#SS_21_5_16)という問題があり、std::condition_variableも同様である。

上記の抜粋である下記のコード例では[Spurious Wakeup](glossary.md#SS_21_5_16)の対策が行われていないため、
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

### std::scoped_lock <a id="SS_20_5_3"></a>
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

## スマートポインタとオブジェクトの所有権 <a id="SS_20_6"></a>
この節では、スマートポインタとそれに密接な関係を持つオブジェクトの所有権について解説する。

### スマートポインタ <a id="SS_20_6_1"></a>
スマートポインタは、C++標準ライブラリが提供するメモリ管理クラス群を指す。
生のポインタの代わりに使用され、リソース管理を容易にし、
メモリリークや二重解放といった問題を防ぐことを目的としている。

スマートポインタは通常、所有権とスコープに基づいてメモリの解放を自動的に行う。
C++標準ライブラリでは、主に以下の3種類のスマートポインタが提供されている。

* [std::unique_ptr](stdlib_and_concepts.md#SS_20_6_1_1)
    - [std::make_unique](stdlib_and_concepts.md#SS_20_6_1_2)
* [std::shared_ptr](stdlib_and_concepts.md#SS_20_6_1_3)
    - [std::make_shared](stdlib_and_concepts.md#SS_20_6_1_3_1)
    - [std::enable_shared_from_this](stdlib_and_concepts.md#SS_20_6_1_3_2)
    - [std::weak_ptr](stdlib_and_concepts.md#SS_20_6_1_4)
* [std::auto_ptr](stdlib_and_concepts.md#SS_20_6_1_5)

#### std::unique_ptr <a id="SS_20_6_1_1"></a>
std::unique_ptrは、C++11で導入されたスマートポインタの一種であり、std::shared_ptrとは異なり、
[オブジェクトの排他所有](stdlib_and_concepts.md#SS_20_6_2_1)を表すために用いられる。所有権は一つのunique_ptrインスタンスに限定され、
他のポインタと共有することはできない。ムーブ操作によってのみ所有権を移譲でき、
スコープを抜けると自動的にリソースが解放されるため、メモリ管理の安全性と効率性が向上する。

#### std::make_unique <a id="SS_20_6_1_2"></a>
[std::make_unique\<T\>(Args...)](https://cpprefjp.github.io/reference/memory/make_unique.html)は、
クラスTをダイナミックに生成し、そのポインタを保持するshared_ptrオブジェクトを生成する。

使用例については、「[オブジェクトの排他所有](stdlib_and_concepts.md#SS_20_6_2_1)」を参照せよ。

#### std::shared_ptr <a id="SS_20_6_1_3"></a>
std::shared_ptrは、同じくC++11で導入されたスマートポインタであり、[オブジェクトの共有所有](stdlib_and_concepts.md#SS_20_6_2_2)を表すために用いられる。
複数のshared_ptrインスタンスが同じリソースを参照でき、
内部の参照カウントによって最後の所有者が破棄された時点でリソースが解放される。
[std::weak_ptr](stdlib_and_concepts.md#SS_20_6_1_4)は、shared_ptrと連携して使用されるスマートポインタであり、オブジェクトの非所有参照を表す。
参照カウントには影響せず、循環参照を防ぐために用いられる。weak_ptrから一時的にshared_ptrを取得するにはlock()を使用する。

##### std::make_shared <a id="SS_20_6_1_3_1"></a>
[std::make_shared\<T\>(Args...)](https://cpprefjp.github.io/reference/memory/make_shared.html)は、
クラスTをダイナミックに生成し、そのポインタを保持するshared_ptrオブジェクトを生成する。

使用例については、「[オブジェクトの共有所有](stdlib_and_concepts.md#SS_20_6_2_2)」を参照せよ。

##### std::enable_shared_from_this <a id="SS_20_6_1_3_2"></a>
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
   コンストラクタ内でshared_from_this()を呼び出してはならない。なぜなら、コンストラクタ実行時点ではまだshared_ptrによる管理が完了しておらず、内部のweak_ptrが初期化されていないためである。この場合、std::bad_weak_ptrエクセプションがスローされる。
2. shared_ptrでの管理が必須  
   オブジェクトがshared_ptrで管理されていない状態(例えばスタック上のオブジェクトや生のnew)でshared_from_this()を呼び出すと、std::bad_weak_ptr例外がスローされるか、未定義動作となる。
3. make_sharedの使用推奨  
   std::enable_shared_from_thisを継承したクラスのインスタンスは、必ずstd::make_sharedまたはshared_ptrのコンストラクタで生成する必要がある。

C++17以降では、`weak_from_this()`メソッドも提供されている。これはshared_from_this()と同様の仕組みだが、
weak_ptrを返すため[オブジェクトの循環所有](stdlib_and_concepts.md#SS_20_6_2_3)を避けたい場合に有用である。

#### std::weak_ptr <a id="SS_20_6_1_4"></a>
std::weak_ptrは、スマートポインタの一種である。

std::weak_ptrは参照カウントに影響を与えず、[std::shared_ptr](stdlib_and_concepts.md#SS_20_6_1_3)とオブジェクトを共有所有するのではなく、
その`shared_ptr`インスタンスとの関連のみを保持するのため、[オブジェクトの循環所有](stdlib_and_concepts.md#SS_20_6_2_3)の問題を解決できる。

[オブジェクトの循環所有](stdlib_and_concepts.md#SS_20_6_2_3)で示した問題のあるクラスの修正版を以下に示す
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

なお、上記コードは[初期化付きif文](core_lang_spec.md#SS_19_9_4_3)を使うことで、
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

#### std::auto_ptr <a id="SS_20_6_1_5"></a>
`std::auto_ptr`はC++11以前に導入された初期のスマートポインタであるが、異常な[copyセマンティクス](class_design.md#SS_8_3_2)を持つため、
多くの誤用を生み出し、C++11から非推奨とされ、C++17から規格から排除された。


---

### オブジェクトの所有権 <a id="SS_20_6_2"></a>

オブジェクトの所有権とは、
「誰がそのオブジェクトの寿命（生成から破棄まで）を管理し、解放する責任を持つか」という概念である。
例えば、以下のようなコードはオブジェクトの所有権が不明確である。

```cpp
    //  example/stdlib_and_concepts/ambiguous_ownership_ut.cpp 11

    class A {
        // 何らかの宣言
    };

    class X {
    public:
        explicit X(A* a) : a_{a} {}
        A* GetA() { return a_; }

    private:
        A* a_;
    };

    auto* a = new A;
    auto  x = X{a};
    // aがxに排他所有されているのか否かの判断は難しい

    auto x0 = X{new A};
    auto x1 = X{x0.GetA()};
    // x0生成時にnewされたオブジェクトがx0とx1に共有所有されているのか否かの判断は難しい
```

[スマートポインタ](stdlib_and_concepts.md#SS_20_6_1)を用いることで、所有権の明確化、メモリリークや二重解放の防止を実現できる。

オブジェクトの所有権のスタイルは、以下の3つに分類できる。

- [オブジェクトの排他所有](stdlib_and_concepts.md#SS_20_6_2_1)
- [オブジェクトの共有所有](stdlib_and_concepts.md#SS_20_6_2_2)
- [オブジェクトの循環所有](stdlib_and_concepts.md#SS_20_6_2_3)


#### オブジェクトの排他所有 <a id="SS_20_6_2_1"></a>
オブジェクトの排他所有や、それを容易に実現するための
[std::unique_ptr](https://cpprefjp.github.io/reference/memory/unique_ptr.html)
の仕様を説明するために、下記のようにクラスA、Xを定義する。

```cpp
    //  example/stdlib_and_concepts/unique_ptr_ownership_ut.cpp 7

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

以下に示した上記クラスの単体テストにより、オブジェクトの所有権やその移動、
std::unique_ptr、std::move()、[rvalue](core_lang_spec.md#SS_19_7_1_2)の関係を解説する。

```cpp
    //  example/stdlib_and_concepts/unique_ptr_ownership_ut.cpp 48

    // ステップ0
    // まだ、クラスAオブジェクトは生成されていないため、
    // A::LastConstructedNum()、A::LastDestructedNum()は初期値である-1である。
    ASSERT_EQ(-1, A::LastConstructedNum());     // まだ、A::A()は呼ばれてない
    ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない
```

```cpp
    //  example/stdlib_and_concepts/unique_ptr_ownership_ut.cpp 57

    // ステップ1
    // a0、a1がそれぞれ初期化される。
    auto a0 = std::make_unique<A>(0);           // a0はA{0}を所有
    auto a1 = std::make_unique<A>(1);           // a1はA{1}を所有

    ASSERT_EQ(1,  A::LastConstructedNum());     // A{1}は生成された
    ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない
```

<!-- pu:essential/plant_uml/unique_ownership_1.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAeoAAAEmCAIAAAAiJUSiAAAtwklEQVR4Xu2dCXQUVd72O4EQIBCCGQRZhIDiwMcHwgsTX3RmcDmCLDqjB2WEVxZROMoiGM13BsEgEkMU4WVPRmUxgghHx+FMggzCGHZkIBBAZDUYCYjEhmBIIMv3JBduF7e6Y9KVVLqqnt+pw7n1v/+6Vbf7+T91q9MhrlJCCCEWxKUGCCGEWAHaNyGEWBKPfZcQQggJeGjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjfhBBiSWjf/nDy5MlevXpNmTJF7SCEELOwiX0XFBR8qmHt2rU7duyQvdnZ2a/rOHr0qGaAivjpp58OHz588ODBzMzMAwcOZGRk4PB+/fq1atVKJODs69evv3Tp0s3HEUJIDWIT+4bDNmnSJCIiolmzZq1bt27cuHHLli2Li4tFL5x6gI49e/bcPEYZMGI1VFISHx/v0hEeHp6amoreMWPGREZGIgKLV48khJAawyb2reXatWsdOnR48803ZeSwDy5evChzdu7cuXv3blg/7gTYfeqppxITE0VXbm7uiRMnsrKysIrPyck5f/7873//e7i26E1LS8OqnPZNCDEZG9p3UlJSWFiYcGFw9epVdeV8g5UrV4qcY8eOhYSEfPrpp+3atYuJiUGkbdu2CQkJckwteXl5DRs2TElJkZH8/HwX7ZsQYi52s+99+/bBW4UFS87cYMaMGS1atJC7sF2ZM2HChLvvvvv9999/5plnsCoPCgr6xz/+oRnDw4IFCxo1aqRdudO+CSHmYyv73rNnT8uWLaOiorD6TktLU7tLSl566aWePXuq0XJOnTq1cOHCa9euof3WW2/Vq1fvwoULalJJycGDByMiIl5//XVtkPZNCDEfm9h3UVFRcnIy1t39+vX75ZdfsMoOCQlRHHzv3r2RkZHo0gYVrly5Au8ODg6Oi4tTui5fvjxnzpwmTZr079//6tWr2i7aNyHEfOxg37m5uT169Khbt+60adPE8hnExMRgDb579+6Scud97LHHYMqPPvoozP2mgzW8/PLLzZo1a9CgwcyZM7VxmPXw4cNh3I0bN4b7K95dQvsmhNQGdrBvMH/+/EOHDmkjxcXFcPMzZ86IXazNN2zYoE3Qk5KSMnfu3HPnzqkdJSXvvPMORnC73WoHIYTUEjaxb0IIcRq0b0IIsSS0b0IIsSS0b0IIsSS0b0IIsSS0b0IIsSS0b0IIsSS0b0IIsSS0b0IIsSS2sm/xZxMIqSpQjiqmSkPVEf8wojqBrewbr4icBSGVB8pxu915eXn5+fmFhYVFRUWqtnxD1RH/MKI6gWco2VJTrAMLifgHlJOVlZWTk3PhwgWUE2pJ1ZZvqDriH0ZUJ/AMJVtqinVgIRH/gHIyMzOPHTuWnZ2NWtL+HY9fhaoj/mFEdQLPULKlplgHFhLxDyhn69atGRkZqCWshrAUUrXlG6qO+IcR1Qk8Q8mWmmIdWEjEP6Cc1NRU1BJWQ3ierdL/DEzVEf8wojqBZyjZUlOsAwuJ+AeUs2rVqvXr1+/evRtLIa9/J88XVB3xDyOqE3iGki01xTqwkIh/GCkkqo74hxHVCTxDyZaaYh0CpJBiY2N37typRokPCgsLz507p0bNxUghUXVWxOqqE3iGki01xTqYU0hnz549ePCgGtWAy1i8eLEarQ4w7KFDh9Soufzq9KvK9OnTXeV/KVTtMBEjhUTVmcCvTr+qWF11As9QsqWmWAdzCiksLKziOqm5Qqq5kSvPr07fF//5z3/UULnYoqKi6tat++qrrypd3377bV5enhKsIYwUElVnAr86fV/YVXUCz1CypaZYhxoqpM2bNy9btkzcqFNSUnCWp59+GmL68ccfZc4vv/yybt261atX5+TkVFLuyqJGu4v28ePH9+7d++GHH6ampl69elWmaSkoKMB7v3LlypMnT3788ccZGRkiXsHI4hBcJ5YzMsErOOro0aObNm366KOPTpw4IYJep482LuDrr7+eP3++53gNW7Zs+eMf/9ihQwe1o7QU42PAJ554omXLlkVFRdquOXPm/OY3v3nnnXfy8/O18ZrASCFRdSJewchUnVeMqE7gGUq21BTrUBOFNH78eFc5QUFBiYmJbdu2FbsA0hE5Z86c6dixowiGh4e7bhSSiMih9LvaetPuot25c2eRD3r16nXt2jUlB292t27dREJoaGijRo20h3sdGdLv2rWrOATXuWPHDpmjBzmtWrUSyfXq1UO5Iuh1+mhPmjQJr8/AgQNvGqK0FDl9+/ZFwiOPPLJnzx6lFwwbNgwzTU9Pd5V/iUrbdfHixbi4uCZNmtx2220LFiwoLCzU9lYvLgOF5KLqdENpd6k6X7gMqE7gGUq21BTr4KqBQoJAx40b9/PPPy9ZsuT8+fOlOpmCkSNH3nLLLRAK0iZOnCgThOBkmn7Xq9xFu3Hjxp9//jmWAFgKYfeLL75QcsaOHdu0aVMsMX766afnnntOOdzryDgEtYc1S2ZmZuvWre+9916ZowdHYRny1Vdfud1ujB8REQF5ibgyfUSgdRSDVutYx/3pT39C1wMPPLBt2zZNugeUSsOGDRMSEvDetW/ffvDgwWpGaWlubu5f//pXvAuo4RUrVqjd1YTLQCFp39Pqgqqj6iqDZyjZUlOsg1am1UWfPn3atGmDVYB8yNIrCQmxsbGijUdOfYJXfMldtGfMmCHaWAFhNzk5Wclp167dK6+8os351ULCIc8+++zicgYMGBAcHFzB4gJHQeKi/f3332MXOhNxfSGNGTNGGyktf+DFyqhTp054GFe6JElJSTh26tSpGPD+++/Hag5loyaVll66dAnrLGT+93//t9pXTbgMFJKLqivH18hUnS9cBlQn8AwlW2qKdXDVQCHhrZ0wYUKDBg2io6OvXLlS6k1JYWFhs2fPlrv6BK/4knsFXdp4BSf1dTgWHa6bwWpFpiloB7l8+TJ2sSJT4jJz0aJF2ogAJYRyRTk99thjXn+CdM8999x8Oa6FCxdqE1BCM2fOxBoTqzac1NenscZxGSgkF1Wna2t3qTpfuAyoTuAZSrbUFOvgqoFCEiuFAwcOYPBPPvmk1JuSunfvPmjQINHGw6w+wSuQ9axZs0Q7LS1Ne5QygtzVxrUn3b9/v7bL18h4hl2+fLmIFxcXa38IpgdHvfTSS6KdmpqKXfG1Yv3s9BEtO3bswJMscoYPH66Nf/PNN8qBPXr06Nmzp9zdsGEDSqh58+Zz5swpKCiQ8ZrAZaCQXFRdOb5Gpup84TKgOoFnKNlSU6yDq7oLacuWLc2aNYuJiRk3bpzrxkeBWID07dv3jTfeED/YAVCnEEpcXBzee63utZek7EJeLVq0gOIxPsbUqkpRmHZAGZcnnT59Oi5S2+Vr5KVLl2JBN3HiRDyf9u7dGzlYaNw4iYqr/Odmzz///FtvvYXM3/3udyXlctFPX7lar2zevPmZZ57RRvAMXqdOHW0xJyYmYij59V5MMD4+HkswmVBzuAwUkvY9rRaoOqqukniGki01xTpoZVotuN1uKKlp06ZNmjSZNGmSCE6bNg0Ljbvuukv7NSmIoFWrVqiiUaNGIbkyhXTq1KmHH364UaNGUVFRUEx4eHiVCqm0/KR4vsPphgwZou2qYGQ0OnbsWL9+fTyVp6eny6H0YEAUDEbAOP379//+++9FXD995aoqQ1FREYrzoYce0gZPnz6N0kXxa4PmYKSQqDoRr2Bkqs4rRlQn8AwlW2qKdaj2QrIQfqhZsFiHeNT1e0ArYqSQqDo1WglUzVF1VVSdwDOUbKkp1oGFpEYrgUtH8+bNRdy/Aa2Iy0Ahuai6qnOz4sqg6qqkOoFnKNlSU6yDy8GFNGbMmIofS6tKtQ8YyBgpJKpOjRqg2gcMZIyoTuAZSrbUFOvg5EIiRjBSSFQd8Q8jqhN4hpItNcU6sJAqw6FDh1JSUtatWye+UExKjRUSVVcZcnNzly9fXuv/c2FAYUR1As9QsqWmWAcWUsXgJRo7dqzrBlFRURCNmuRIjBQSVVcxWCj079+/fv36Lid9rl0ZjKhO4BlKttQU68BC0nL8+PEVK1Zo/+u4v/3tb3iJZs2ahaXQ9u3b27Zt+4c//OHmgxyKkUKi6rToVYdF99ChQ2fMmEH7VjCiOoFnKNlSU6wDC0kye/bs4OBgscqOjo4WtdS7d+8+ffrInDVr1qD3yJEjnsOcipFCouokXlUnwKtK+1YwojqBZyjZUlOsAwtJgLIZNmzYiBEjfvzxx7Vr1+JlwQMs4uHh4XFxcTLt3Llz6Prss888RzoVI4VE1Ql8qU5A+9ZjRHUCz1CypaZYBxaSBK9GWlpabGys+NW4JUuWIBgaGjp37lyZU1BQgK5ly5Z5DnMqRgqJqpOUeFOdgPatx4jqBJ6hZEtNsQ4sJMmECRPq1Knz4IMPjh49WpZNVFTU5MmTZc7Ro0fRtWHDBs9hTsVIIVF1Eq+qE9C+9RhRncAzlGypKdaBhSRp0qTJlClT0Dhx4oQsm1GjRrVq1Ur+dzyvvfZaw4YN3W639kBnYqSQqDqJV9UJaN96jKhO4BlKttQU68BCknTu3LlLly5vv/02GkFBQTNnzkQwMzOzfv363bp1S0hIGDt2bHBwcK38Tz0BiJFCouokXlUnoH3rMaI6gWco2VJTrAMLSbJz585OnTphcT1ixIi+ffvKvwe4efPmXr16hYaGtmzZEqtv+d9vOhwjhUTVSXyprpT27Q0jqhN4hpItNcU6sJCIfxgpJKqO+IcR1Qk8Q8mWmmIdWEjEP4wUElVH/MOI6gSeoWRLTbEOLCTiH0YKiaoj/mFEdQLPULKlplgHFhLxDyOFRNUR/zCiOoFnKNlSU6wDC4n4h5FCouqIfxhRncAzlGypKdaBhUT8w0ghUXXEP4yoTuAZSrbUFOvAQiL+YaSQqDriH0ZUJ/AMJVtqinVgIRH/MFJIVB3xDyOqE3iGki01xTqwkIh/GCkkqo74hxHVCTxDyZaaYh0iIyNdhFSdsLAwvwuJqiP+YUR1AlvZN3C73VlZWZmZmVu3bk1NTV3lYFzl93ZSSaAWaAbKgX6gIlVYFULVSai6KmFEdSX2s++8vLycnBzcyjIyMvC6rHcwKCQ1RHwDtUAzUA70AxWpwqoQqk5C1VUJI6orsZ995+fn4xkkOzsbrwjuabsdDApJDRHfQC3QDJQD/UBFqrAqhKqTUHVVwojqSuxn34WFhbiJ4bXA3QzPI8ccDApJDRHfQC3QDJQD/UBFqrAqhKqTUHVVwojqSuxn30VFRXgVcB/Dy+F2uy84GBSSGiK+gVqgGSgH+oGKVGFVCFUnoeqqhBHVldjPvokEhaSGCKlhqDozoX3bFhYSMR+qzkxo37aFhUTMh6ozE9q3bWEhEfOh6syE9m1bWEjEfKg6M6F92xYWEjEfqs5MaN+2hYVEzIeqMxPat21hIRHzoerMhPZtW1hIxHyoOjOhfdsWFhIxH6rOTGjftoWFRMyHqjMT2rdtYSER86HqzIT2bVtYSMR8qDozoX3bFhYSMR+qzkxo37aFhUTMh6ozE9q3fejatavLB+hSswmpDqi6WoT2bR8SEhLUAroButRsQqoDqq4WoX3bh6ysrODgYLWGXC4E0aVmE1IdUHW1CO3bVvTp00ctI5cLQTWPkOqDqqstaN+2Ijk5WS0jlwtBNY+Q6oOqqy1o37YiNzc3NDRUW0XYRVDNI6T6oOpqC9q33Xj88ce1hYRdNYOQ6oaqqxVo33Zj7dq12kLCrppBSHVD1dUKtG+7ceXKlaZNm4oqQgO7agYh1Q1VVyvQvm3I6NGjRSGhofYRUjNQdeZD+7YhmzZtEoWEhtpHSM1A1ZkP7duGFBcXtykHDbWPkJqBqjMf2rc9iS1HjRJSk1B1JkP7tif7y1GjhNQkVJ3J0L4JIcSS0L4JIcSS0L4JIcSS0L4JIcSS0L4JIcSS0L4JIcSS0L4JIcSS0L5tS7164eKXmG1DZGSkOkkSYIRFhKlvm8UJZNXRvm0LlDd48L/stGFGbrc7Ly8vPz+/sLCwqKhInTOpbfAeJZ1IstMWyKqjfdsWW9p3VlZWTk7OhQsXUE6oJXXOpLaxpX0HrOpo37bFlvadmZl57Nix7Oxs1BJWQ+qcSW1jS/sOWNXRvm2LLe1769atGRkZqCWshrAUUudMahtb2nfAqo72bVtsad+pqamoJayG8DzrdrvVOZPaxpb2HbCqo33bFlva96pVq9avX797924shfAkq86Z1Da2tO+AVR3t27bQvon50L7NhPZtW6rXvv/yly9Hj/5KH3/yyY3/8z+b9HF51NChX+rj/m2BXEhEUL32vfDIwnd2v6OPLzm2ZF7mPH1cHrXg0AJ93L8tkFVH+7Yt1Wvfq1efgDZeemm7Nrh8+bdXrxZ/+61bRiZN2j5vXmZCwr6nny5z7fnzDxYXlyChAouv/BbIhUQE1Wvfg14ahAHjvojTBgf/dXDdenXbd28vI3P2zhn5zkiZhnZwnWAkVGDxld8CWXW0b9tSjfb95JP/Oncuv6io5O9//04bv3z52t//fkrmbNjwvVQR8seP34b4Cy9sxe6cOQf0w1Z1C+RCIoJqtO8lx5f8ps1vYMR9n++rjTcMb9h3zPXIi397sUufLiGhITjv0BlDZU78V/GIPDfvOf2wVd0CWXWy3GjfdqMa7Tsubg+EsXPnudzcgqee2ijjCCYnfyPaS5Ycxm5KytERI/49ZcruH3+8cvhwrj7NyBbIhUQE1Wjfkz+ajNF69OsR0Txi8dHFMq51aiy0ox+LfmzyY4p9K2lGtkBWnTRt2rfdqEb7Tk8/8/33l6dN+xryiI/fK+NaXz5yxH3w4HW/xjZ79n70TpxYtgDXphnZArmQiKAa7Tv6T9G33XFbzMcxGHP8B+NlXO/LMzbN0Af1Ef+2QFadNG3at92oLvt+5pnNBQVFKSnHnnzyX2fP5m/fflbEhw3bBLUsWHBQ7ObnX/vkkxPyqNGjv0JvYmIG2oWFxcuXf6sfuapbIBcSEVSXff/v/v+t16De468+Lj5C+a/+/yXi8w/Oxymw6NYme7XvkPohg/86WD9yVbdAVh3t27ZUl30nJZV9KrJ27UmsoLG+vnq1eMSIfyO+YUP25cvXXnhhi0hDfOlSj0c//fSXpTfMPT0958KFgjFj0vWDV2kL5EIiguqy72Ezh2GoAeMGwJTvuueuuvXqztk7B/E//OUPDcMbxqfHa5O92nf0Y9ERzSNmbZ+lH7xKWyCrjvZtW6rLvo8edUttCN57r+yTkI8/Pl5UVPLyyztE2rlz+evWZcmjJkzYhswZM/6DNkz/u+/yRo0qM30jWyAXEhFUl323797edTN/mf4XxB+d9GidunWmpU7TJnu1b5h+69+2fvc/7+oHr9IWyKqTJUn7thuu6rDvl17aXnrzJ9cnT146fvwiGkOGbETXokWHRHzTph+wxB427PoXBLFaLygoGj58M9pw+Q8+OKIfvKpbIBcSEbiqw76nb5iu2PHt/+f2tv+3LRqLvl2ErmcSntHme7VvuPyQ14doI/5tgaw62rdtqRb7/vzz74qLS5591vMLOx9+eBQimTy57AvgpRpnnzx5x9Wrxd99dykl5diGDd/jAv7xj+vfMtSmGdkCuZCIoFrs++HnHg6uE/zO155f2Hni/z2BkV9f/3qSt59JerVvfcS/LZBVJ02b9m03jNv3U09t/PnnwgMHLmiDY8dugWyENSu+HBe3BwtzmHhubgFW31ieizjt2zkYt+/FRxeHNwvvdG8nbTBha0JQUBBsPcmbL9O+ad92w7h9/+qWl3c1NfW0+AVLrxtuADExOyCq2bP363urugVyIRGBcfv+1S0sIuz+Z+5f+M1CfZfYcAOY+s+puJIxC8boe6u6BbLqaN+2xQT7Tk4+fPnytRMnyj4K97otXHioqKhk//4LFVh85bdALiQiMMG+h745tGF4w7Zdyj4K97oNTxweXCe4032dFhyuhv/5JJBVR/u2LSbYt9i0v4epbE8+Wbbp4/5tgVxIRGCCfYtN+3uYyrbk+BJs+rh/WyCrjvZtW0yzb9O2QC4kIjDNvk3bAll1tG/bQvsm5kP7NhPat22hfRPzoX2bCe3bttC+ifnQvs2E9m1baN/EfGjfZkL7ti20b2I+tG8zoX3bFto3MR/at5nQvm0L7ZuYD+3bTGjftoX2TcyH9m0mtG/bQvsm5kP7NhPat22hfRPzoX2bCe3bttC+ifnQvs2E9m1baN/EfGjfZkL7ti20b2I+tG8zoX3bFto3MR/at5nQvm0L7ZuYD+3bTGjftoX2TcyH9m0mtG/bQvsm5kP7NhPat22hfRPzoX2bCe3bttC+ifnQvs2E9m1bIiMjXfYiLCwsYAuJCKg6M6F92xm3252VlZWZmbl169bU1NRV1gezwFwwI8wLs1MnTAIAqs40aN92Ji8vLycnB0uGjIwM6G+99cEsMBfMCPPC7NQJkwCAqjMN2redyc/Px7NednY2lIe1w27rg1lgLpgR5oXZqRMmAQBVZxq0bztTWFiIxQI0h1UDnvuOWR/MAnPBjDAvzE6dMAkAqDrToH3bmaKiIqgN6wXIzu12X7A+mAXmghlhXpidOmESAFB1pkH7JoQQS0L7JoQQS0L7JoQQS0L7JoQQS0L7JoQQS0L7JoQQS0L7JoQQS0L7JoQQS2Ir+3799de1/1UYdtnLXvayt+Je62Ir+yaEEOdA+yaEEEtC+yaEEEtC+yaEEEtC+yaEEEtC+yaEEEtC+yaEEEtC+yaEEEtC+yaEEEtC+yaEEEtC+yaEEEtC+yaEEEtC+yaEEEtC+75OZGSk9v8kI8SiQMkeVTdurHbbFO2snQPt+zpQgHwFCLEuULLb7c7Ly8vPzy9T9SefOGHTzrqwsLCoqEitcDviedNlS01xBrRvYg+g5KysrJycnAsXLjjKvuWsYeJwcLXC7YjnTZctNcUZ0L6JPYCSMzMzjx07lp2d7Sj7lrOGg2MNrla4HfG86bKlpjgD2jexB1Dy1q1bMzIy4GWOsm85a6zBsQBXK9yOeN502VJTnAHtm9gDKDk1NRVehtWoo+xbzjorK8vtdqsVbkc8b7psqSnOgPZN7AGUvGrVqvXr1+/evdtR9i1njQX4hQsX1Aq3I543XbbUFGdA+yb2gPZN+3YctWjfhYWF586dU6OkuomNjd25c6carRnmzZu3evXqDRs2qB01D+2b9u04atG+p0+fjrMfPnxY7fDBE088YdAXzp49e/DgQSX4yy+/pKamfvDBB//85z/z8vKUXoN4PaPf+DcaXuTFixeLNhpLly4t0RSACB46dEgb8Y+kpKRbb70Vr2SzZs3Onz+vdtcwtrfv3KVLl7/44qF339UGad/XUVOcQW3ZN04dFRVVt27dV199Ve3zgdaG/CMsLEwZAZYNx3HdoFGjRnA3bYJB9Gc0gn+jaV83Mc34+HhfCX7jdrubNm2anJyMdqdOnaZMmaJm1DBaIytTtc7+rLuti43t3717/ZCQsnfquee0XdpZ074dR5nQa4NNmzbh1FhQt2zZsqioSO32RgUuc/z48RUrVmARffXqVRncvHnzsmXL5Oo+JSUFIzz99NMY5Mcff0Rk3759oaGh/fr1O3DgANbde/bs6du377333pubm1ta/tnOxo0bV69e/cMPP8gxS8vXqjjd3r17P/zww6qeEY2TJ09+/fXX8+fPF7vaZa+yiwvA0wYGOX36dKm30QQFBQWoXlwn1uYyiEeKdevWIZiTk6PYd+vWrevUqfPll1/KZJng63rQ2LVr10cffYQXWXw7DSN//vnn+fn5Mvndd9+FfV+5cgVt3B5wU5Rd5mBj+8aie+jvfz/jqado3wLPmy5baoozqC37HjZsWOfOndPT013l33wSQVc5Mke/69W+Z8+eHRwcLJKjo6OFn44fP15EgoKCEhMTEWnbtq2IABgoIo8//nj79u2F4yj89NNPPXv2FMlY83766aeyCxFcuRyqV69e165dK63cGdGYNGkSEgYOHCh2tTPS7p4/f7579+7i2Hr16uEC9KMB+HjXrl1FMDw8fMeOHQieOXOmY8eOMui62b7hs7fddlvz5s3lbUkmaDOVOJ6TxIAtWrSQZ5RzBw8++CBuxqK9ZcsW9PrxOY8RXPa1b7Edmzev7B2hfdO+JWVCN52LFy82bNgwISEBFwADHTx4sIgLU5Bp+l29fcOscScYMWIEjGzt2rXIwaoT8UaNGo0bN+7nn39esmSJ/BxWGSEyMtLXRzcvvPACjG/btm3w8UGDBiHT7XaLLgzSuHFjsfbEAhy7X3zxRWnlzohdWCduWlhZe+2Vu2PHjo2IiEBNYl5wRiy69fkirVu3bljRZ2ZmYlmNRwcER44cecstt+BhAhczceJE7VFoJycn49EHC/D77rtPmK9M8HU9aNxxxx1wBzwNoI17Q1ZWFm66aMM4RDLmNX36dNHG9NH12WefyaFMwEX7pn07jTKhm05SUhLOO3XqVLjD/fffHxoaKj6vqBi9eQkwi7S0tNjY2CFDhiAH7olgnz592rRps3LlSu0nM8oIISEhWLnLXS233357TEyMaIvf4pM+hfaMGTNEG/bnKjfE0sqdEbtjxoypoFfuai+goKBAnyBo167ds88+u7icAQMG4CkENwZcBl4NkYDbm/Yo+fq8+eabaL/88stow8p/1b7nzp2LRnFxMdpz5syRbTH30vIXc968eaItTvr+++9fH8gUXLRv2rfTKBO66dxzzz2um1m4cKGapKNMu97se8KECTAgLFFHjx4tc3A/QLxBgwbR0dHy4xFlBCz84X1yt7RcA8J8w8LCpLNfvnwZB2KhLXaVQap0RuwuWrRIu+t1qNKbL0CifwXwEHP9FbzB8ePHlWO1R8k2Ztq/f3/s4s7XpEmTX7Vv/QhKG+t9+RNRrPrRtXr1arFrDi7aN+3baZQJ3Vy++eYbxSZ69OjRs2dPTYp3lKMkcB/xPYcTJ07IHPHpxIEDBxD5BEIvRxnhlVdeqVevHnJkJDEx8c4778zOzr777rv//Oc/i6D4lEB+dVoZpEpnVHZhvrNmzRJt2Ki2F6/Jo48+KtqHDx/evn17qe5w0K1bt+XLl4s2lsPiR5rdu3cfNGiQCO7Zs0d7lLaNUr+9HCzhRdDX9fgaQblg3D5FW/za+rZt28SuObho37Rvp1EmdHOBaWKxrP3uBEzTVf6TLlc5Mq7fFd+7EKxZs0bEO3fu3KVLl7fffhuNoKCgmTNnbtmypVmzZjExMePGjXPd+Gy6tHxJ27dv3zfeeEN85nvx4kUc2Lhx40mTJs2dO/fJJ59EsjC+Dz74AO2RI0ditFtvvbV3794lN0RTVkI6R67kGZVjH3jggRYtWsAxcSAytb3iU/WhQ4eit3Xr1pgaHguU0cDSpUux3p84cWJCQgIuEqNdunQJho5jhw8fHhcXh0WxdljlAnbt2oUbmAz6uh5fI2jbsbGxeJoR7ffee69+/fryMx9zcNG+ad9Oo0zoJgIPgkE89NBD2uDp06dhu7AMVzky7nVXgoWniGNd3KlTJ6wcR4wYAXcbOHCg2+1+/vnnmzZtioU5rFmOMG3aNKTddddd8utxyJw8eXKbNm1CQ0N/+9vfwrnEIhrA0OFHERERgwcP1t5sXN7su5JnVI49derUww8/3KhRo6ioqPj4+PDwcG3vggULOnTogMMfeeQR8d1B/fWXln+rr2PHjrDL6Ojo9PR0EcQdsVWrVvDuUaNGyc9GSnUXUFr+e5Iy6Ot6tEf5ah85cgR35Y0bN6KNQYYMGSLipuGifdO+nUaZ0IljSEtLE3cCLfBcfdAPxo4di1tIRkZGSEjIvn371O4axvb27XWjfV9HTXEGtG9SXVy5cqVfv36vvfba1KlT1b6ah/ZN+3YctG9iD2jftG/HQfsm9oD2Tft2HLRvYg9o37Rvx0H7JvaA9k37dhy0b2IPaN+0b8cRGRnpIsT6hIWFSSOLiIhQu22Kdta0byfidruzsrIyMzO3bt2ampq6ihBrov2b6wInqJp/ad7R9p2Xl5eTk4Nbd0ZGBnSwnhBrAvVCw1Byzg2coGrtrFHLannbEdq3h/z8fDxzZWdnQwG4h+8mxJpAvdAwlHzhBk5QtXbWqGW1vO0I7fs6/Oyb2IOIiIisrCysQOFizlG1dtZYehcWFqoVbkdo39dx8ZsnxBZAydLInKNq7axp347DOUIn9ob2Tft2HM4ROrE3ULL8FNg5qtbOmp99Ow7nCJ3YGyhZfgfDOarWzprfPHEczhE6sTdQsvwGtHNUrZ01v/ftOGpL6IWFhefOnVOjxF9iY2PlX+OsUebNm3f69OnNmzdv2LBB7atVXMovzTsD7az5W5eOo7aEPn36dJz68OHDaocPnnjiCYN+cfbs2YMHD8rdxeUsWbJkxYoVX331VX5+via3CijDGse/AV03/m4Z/l26dGmJRuIiqP37an6TlJR06623nj9/fs2aNc2aNUNDzag9bG/fubm5y5cvV95H2vd11BRnUCtCx3mjoqLq1q376quvqn0+kPbkN2FhYdoRXDcTERGRmJioSa8syrDG8W9A+fqI6cTHx3vtNQIezJs2bZqcnCx2O3XqNGXKlJtTahOXfe173bp1/fv3r1+/vv591M6a9u04akXomzZtwnmxoG7ZsmVRUZHa7Q29cCXHjx/HCjo1NfXq1asyiKf7ZcuWydV9SkqK68Yfqhd/d1gOmJeX9/XXX7/44otBQUGvvfaaHKGgoABVsXr1aiyHZbD05pH1w5aWL3VPnjyJMefPny92lb8sLHcLCwvxSIFB5J+a9Dqgryv55ZdfUNiI5+TkyOmg0bp16zp16nz55ZcyU/vq+boeNHbt2vXRRx/hxRQ/BMPIn3/+uXwueffdd2HfV65cEbu4Q2AlLsepdWxs31h0Dx06dMaMGfoqoH1fR01xBrUi9GHDhnXu3Dk9Pd1V/oMXEXSVI3P0u17te/bs2cHBwSI5OjpaOPj48eNFBI4s1tRt27YVEQBjLfU24PTp0/FAAOdCG9bZtWtXkR8eHr5jxw6Ro4ysH7a0fORJkyYhYeDAgWJXeyK5e/78+e7du4tj69Wr9+mnn5Z6u05fV3LmzJmOHTvKuEtj3/DZ2267rXnz5j/88INyUqWt3UUD0xcDtmjRQp60V69e165dQ8KDDz6IO648cMuWLej143OeGsJlX/sWiG/U0L5LaN8S84V+8eLFhg0bJiQk4Ozt27cfPHiwiAuzkGn6Xb19w6xxJxgxYgQ8bu3atcjBahTxRo0ajRs37ueff16yZIn8fFYZQT8gDBFBjFNa/kfTu3XrhkV0ZmYmFrP33nuvyNGPrB8HEbgnbk5YXOsT5C5OERERgarDxcMZseJWEgS+rmTkyJG33HLLnj17cDETJ06UR6GRnJyM5xsswO+77z7hvNoxfV0PGnfccQcsAA8EaOPekJWVhZsr2nAHJGBSuMPJAzF9dH322WcyUru4aN+0b6dhvtCTkpJw0qlTp0KI999/f2hoaG5urpqkQy9cAaaQlpYWGxs7ZMgQ5MBVEezTp0+bNm1Wrlyp/WTGl21JCgoKEFy2bBna7dq1e/bZZxeXM2DAACzwhRfrR9aPg8iYMWO0u17Pe/vtt8fExIggTq1PEPi6ElwGZi1ycBuTR8kX4c0330T75ZdfRhtWLsf0dT1ozJ07F43i4mK058yZI9vi8+6QkJB58+bJA8VJ33//fRmpXVzWse8777zT5QN0qdk3oH1LPNOXLTXFGbhMF/o999yjSHbhwoVqkg69cAUTJkyAN2H1Onr0aJmD+wHiDRo0iI6Olp/VKiPoB9y1axeC//73v9HG88FNl+hyHT9+vNTbyPpxEFm0aJF21+t5w8LCZs+eLeMSJd/XlSiHy6NkA29u//79sYvbW5MmTSpj315zZBuLfe1PRLHqR9fq1atlpHZxWce+/YP2LfFMX7bUFGdgstC/+eYbRYI9evTo2bOnJsU7euEKYEzi+w8nTpyQOWJ9euDAAUQ++eQTkenLtgTwZdxXsNQVy+pu3botX75cdGEFKn+KqB9Zf2FKBP47a9Ys0YaTyl5M/NFHHxXxw4cPb9++XbSVw31dSffu3QcNGiTae/bskUdpD0cx314O5iWDvq5He6DXNi4Y90gRBOK3Y7Zt2yYjtYuL9k37dhomC/2VV17BYll6EEhMTHSV/wTMVY6M63fF9zEEa9asEfHOnTt36dLl7bffRiMoKGjmzJlbtmxp1qxZTEzMuHHjcNQXX3whMrFc7du37xtvvCE/DhYD4ljxOTKQv/mydOlSLLEnTpyYkJDQu3fvFi1aXLp0yevIyrBiZG2NPfDAAzgcjokDkSx7P/zwQ7SHDh2KrtatW+P6xZ1DGdDrlZSWfxsBhw8fPjwuLg5XLodVzo5Hinr16mmDvq5Hm+O1HRsb2759exEE7733Xv369bUf+9QuLto37dtpmCl02BOM46GHHtIGT58+DduFlbjKkXGvuxKsSUUchtupUyesKEeMGAHXGzhwoNvtfv7555s2bYqF+aRJk+QI06ZNQ9pdd90lvicnh0Jm165dsYTPzs6WyaXlX6Tr2LEjHCo6Ojo9Pb20/IvP+pGVYUt1Bnrq1KmHH364UaNGUVFR8fHx4eHhsnfBggUdOnTA4Y888oj87qB+QP2VCHDna9WqFbx71KhR8uMR5eyl5b8nqQ36uh5tjtf2kSNHcOvduHGjiGOQIUOGiHYg4KJ9076dhi2F7mTS0tLknUACz9UH/WDs2LG4heA2fODAgZCQkH379qkZtYft7dsrtO/rqCnOwDlCJ8a5cuVKv3799u/fjzXg1KlT1e5ahfZN+3YczhE6sTe0b9q343CO0Im9oX3Tvh2Hc4RO7A3tm/btOJwjdGJvaN+0b8fhHKETe0P7pn07DucIndgb2jft23E4R+jE3tC+ad+OIzIy0kWI9QkLC5NGFhERoXbbFO2sad9OxO12Z2VlZWZmbt26NTU1dRUh1kT7N9cFTlA1/9K8o+07Ly8vJycHt+6MjAzoYD0h1gTqhYah5JwbOEHV2lmjltXytiO0bw/5+fl45srOzoYCcA/fTYg1gXqhYSj5wg2coGrtrFHLannbEdq3h8LCQty08d7j7o3nr2OEWBOoFxqGkvNu4ARVa2eNWlbL247Qvj0UFRXhXcd9G2+/2+2WKxdCrAXUCw1DyYU3cIKqtbNGLavlbUdo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYklo34QQYkm82DchhBALQfsmhBBLQvsmhBBL8v8Bd8qC/hsMX6MAAAAASUVORK5CYII=" /></p>

```cpp
    //  example/stdlib_and_concepts/unique_ptr_ownership_ut.cpp 67

    // ステップ2
    // xが生成され、オブジェクトA{0}の所有がa0からxへ移動する。
    ASSERT_EQ(0, a0->GetNum());                 // a0はA{0}を所有
    auto x = X{std::move(a0)};                  // xの生成と、a0からxへA{0}の所有権の移動
    ASSERT_FALSE(a0);                           // a0は何も所有していない
```

<!-- pu:essential/plant_uml/unique_ownership_2.pu--><p><img src="data:image/png;base64,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" /></p>

```cpp
    //  example/stdlib_and_concepts/unique_ptr_ownership_ut.cpp 75

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
    //  example/stdlib_and_concepts/unique_ptr_ownership_ut.cpp 89

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
    //  example/stdlib_and_concepts/unique_ptr_ownership_ut.cpp 100

    // ステップ5
    // a2をstd::move()によりrvalueに変換し、ブロック内のa3に渡すことで、
    // A{1}の所有はa2からa3に移動する。
    {
        std::unique_ptr<A> a3{std::move(a2)};
        ASSERT_FALSE(a2);                       // a2は何も所有していない
        ASSERT_EQ(1, a3->GetNum());             // a3はA{1}を所有
```

<!-- pu:essential/plant_uml/unique_ownership_5.pu--><p><img src="data:image/png;base64,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" /></p>

```cpp
    //  example/stdlib_and_concepts/unique_ptr_ownership_ut.cpp 110

        // ステップ6
        // このブロックが終了することで、std::unique_ptrであるa3のデストラクタが呼び出される。
        // これはA{1}オブジェクトへのポインタをdeleteする。
    }                                      // a3によるA{1}の解放
    ASSERT_EQ(1, A::LastDestructedNum());  // A{1}が解放されたことの確認
```

<!-- pu:essential/plant_uml/unique_ownership_6.pu--><p><img src="data:image/png;base64,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sqWHuAPLBjkDywbLRrCZySZbeog7sGyQM7BssGwEm5lssqWHuAPLBjkDywbLRrCZySZbeog7sGyQM7BssGwEm5lssqWHuAPLBjkDywbLRrCZySZbeog7sGyQM7BssGwEm5lssqWHuENcXJxBFP6ioqLkAhobG6vvdij1qlk2go1lw+TxeDIzMzMyMvbs2ZOamvo+UXhC9iKHkcmZt7ghq9WrxlzWpzcFDsuGKTc3Nzs7G7cq6enpyL8tROEJ2YscRiZn3+KGrFavGnNZn94UOCwbpry8PDzbZmVlIfNwz7KfKDwhe5HDyOSLt7ghq9WrxlzWpzcFDsuGqbCwEDcpyDncreA59wRReEL2IoeRybm3uCGr1avGXNanNwUOy4apuLgY2Yb7FKSdx+ORd2pE4QXZixxGJhfe4oasVq8ac1mf3hQ4LBtERGQDywYREdnAskFERDawbBARkQ0sG0REZAPLBhER2cCyQURENrBsEBGRDSwbRERkA8sGERHZwLJBREQ2sGwQEZENLBtERGQDywYREdnAskFERDawbBARkQ0sG0REZAPLBhER2cCyQURENrBsEBGRDSwbRERkA8sGERHZwLJBREQ2sGwQEZENLBtERGQDywYREdngo2wQERHdFssGERHZwLJBREQ2/D/ufLX/rhjd6wAAAABJRU5ErkJggg==" /></p>


また、以下に見るようにstd::unique_ptrはcopy生成やcopy代入を許可しない。

```cpp
    //  example/stdlib_and_concepts/unique_ptr_ownership_ut.cpp 124

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
    //  example/stdlib_and_concepts/unique_ptr_ownership_ut.cpp 162

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

---

#### オブジェクトの共有所有 <a id="SS_20_6_2_2"></a>
オブジェクトの共有所有や、それを容易に実現するための
[std::shared_ptr](https://cpprefjp.github.io/reference/memory/shared_ptr.html)
の仕様を説明するために、下記のようにクラスA、Xを定義する。

```cpp
    //  example/stdlib_and_concepts/shared_ptr_ownership_ut.cpp 7

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
    //  example/stdlib_and_concepts/shared_ptr_ownership_ut.cpp 47

    // ステップ0
    // まだ、クラスAオブジェクトは生成されていないため、
    // A::LastConstructedNum()、A::LastDestructedNum()は初期値である-1である。
    ASSERT_EQ(-1, A::LastConstructedNum());     // まだ、A::A()は呼ばれてない
    ASSERT_EQ(-1, A::LastDestructedNum());      // まだ、A::~A()は呼ばれてない
```

```cpp
    //  example/stdlib_and_concepts/shared_ptr_ownership_ut.cpp 56

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
    //  example/stdlib_and_concepts/shared_ptr_ownership_ut.cpp 68

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
    //  example/stdlib_and_concepts/shared_ptr_ownership_ut.cpp 79

    // ステップ３
    // x1が生成され、オブジェクトA{0}の所有がa0からx1へ移動する。
    auto x1 = X{std::move(a0)};                 // x1の生成と、a0からx1へA{0}の所有権の移動
    ASSERT_EQ(x1.GetA(), x1.GetA());            // x0、x1がA{0}を共有所有
    ASSERT_EQ(2, x0.UseCount());                // A{0}の共有所有カウント数は2
    ASSERT_EQ(2, x1.UseCount());
    ASSERT_FALSE(a0);                           // a0は何も所有していない
```

<!-- pu:essential/plant_uml/shared_ownership_3.pu--><p><img src="data:image/png;base64,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" /></p>

```cpp
    //  example/stdlib_and_concepts/shared_ptr_ownership_ut.cpp 89

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
    //  example/stdlib_and_concepts/shared_ptr_ownership_ut.cpp 110

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
    //  example/stdlib_and_concepts/shared_ptr_ownership_ut.cpp 120

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
    //  example/stdlib_and_concepts/shared_ptr_ownership_ut.cpp 142

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
* 下記のようなコードはstd::shared_ptrの仕様が想定する[セマンティクス](glossary.md#SS_21_7_1)に沿っておらず、
  [未定義動作](core_lang_spec.md#SS_19_14_3)に繋がる。

```cpp
    //  example/stdlib_and_concepts/shared_ptr_ownership_ut.cpp 162

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

---

#### オブジェクトの循環所有 <a id="SS_20_6_2_3"></a>
[std::shared_ptr](https://cpprefjp.github.io/reference/memory/shared_ptr.html)の使い方を誤ると、
以下のコード例が示すようにメモリーリークが発生する。

なお、この節の題名である「オブジェクトの循環所有」という用語は、
この前後の節がダイナミックに確保されたオブジェクトの所有の概念についての解説しているため、
この用語を選択したが、文脈によっては、「オブジェクトの循環参照」といった方がふさわしい場合もある。

---

まずは、**メモリリークが発生しない**`std::shared_ptr`の正しい使用例を示す。

```cpp
    //  example/stdlib_and_concepts/shared_ptr_cycle_ut.cpp 8

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
    //  example/stdlib_and_concepts/shared_ptr_cycle_ut.cpp 39

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
    //  example/stdlib_and_concepts/shared_ptr_cycle_ut.cpp 55
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
    //  example/stdlib_and_concepts/shared_ptr_cycle_ut.cpp 67
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
    //  example/stdlib_and_concepts/shared_ptr_cycle_ut.cpp 79

    }  // この次の行で、x0、x2、y0、y2はスコープアウトし、X、Yオブジェクトは解放される

    ASSERT_EQ(X::constructed_counter, 0);  // Xオブジェクトの解放の確認
    ASSERT_EQ(Y::constructed_counter, 0);  // Yオブジェクトの解放の確認
```

<!-- pu:essential/plant_uml/shared_each_4.pu--><p><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAjAAAADuCAIAAACoOKpOAAAvUElEQVR4Xu2debxN1fvHD4lyTRVlKlRSSOobDZIhJCmlNKdJLhEKzUnkUmkwFs1IkyRlaCA00EVkKmNRkUyVZMr5/d7Oet1l333OPvfc6xzn2D7vP3rtvdbaw3r23p/P8+yzrwL/J4QQQqQAAXeDEEIIkQxkSEIIIVKCfYYUFEIIIQ44MiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDEkIIkRLIkIQQQqQEMiQhhBApgQxJCCFESiBDygurVq2qVavWww8/7O4QQgiRV3xiSDt27BjrYMyYMTNnzrS9v/7662NhLFu2zLGDaGzcuHHJkiWLFi1auHDhggUL5s+fz+ZNmzYtV66cHbNlyxaOu337dsd2QgghcoFPDAnPKF68eIkSJUqVKlW+fPmiRYuWLVt2z549phfvuTSMOXPmZN/HXjA2d1MwmJGREQijWLFiEydONAM4UIsWLQoWLLh27drsmwohhIgVnxiSk927d5900klPPPGEbVniwV9//WXHzJo1KzMzEzPD21i99tprn3rqKdO1efPmlStXrl69mkpr3bp1GzZsqFu3bnp6ut22d+/e7du3P/zww2VIQgiRZ3xoSMOGDUtLSzO+Art27XJXN1mMHj3ajFm+fDl2Mnbs2IoVK3br1o2WChUq9OvXz+7TydatWwsXLjxq1Ciz+tlnn1WrVm3Lli3sUIYkhBB5xm+GNG/ePNzCmIplbRaUMqVLl7ar//77rx3TqVOnmjVrvvLKK61bt6Zyypcv3/jx4x372MfgwYOLFCliqqtffvkF61qwYIGxPRmSEELkGV8Z0pw5c8qWLVupUiUqpEmTJrm7g8EuXbqcffbZ7tYQP/3005AhQ3bv3s1y3759CxYsuGnTJvegYHDRokUlSpR47LHHzOpNN92E/50UAkNq1KgRjph9CyGEEDHhE0P677//hg8fjjc0bdp027ZtVEKHH364y5O+++67Y445hi5no4vt27fjRvnz5+/Zs6er659//nnuueeKFy/erFkz6iHTOGPGjNEhRo0ahSG98MIL69aty76dEEKImPCDIW3evPmss84qUKBAjx49TIkD3bp1o07KzMwMhrykRYsW2Mzll1+OXWXb2EHXrl1LlSp15JFH9unTx9mO/dxyyy1YUdGiRfEz60auMXplJ4QQ+4MfDAkGDRq0ePFiZ8uePXvwJ+sQ1E+ffvqpc0A4VDnPP//8+vXr3R3BYP/+/dnDn3/+6e4QQggRJ3xiSEIIIQ52ZEhCCCFSAhmSEEKIlECGJIQQIiWQIQkhhEgJZEhCCCFSAhmSEEKIlECGJIQQIiWQIQkhhEgJ/GlIjz32mPN/M2H/LdSDt/cA81iIKOdzMPYKIVIcfxqS2E9Qc3fTQY7MSYjUx1eGJNGJF/4zJP/NSAj/4StD8p/oJMti/RdJ/81ICP8hQ0ppkjWjZB03cfhvRkL4DxlSSpOsGSWrMkscyYqkECJ2ZEgpjf9mlCz8Z7FC+A9fGZL/REeGJIQ4dPCVIfkP/1ms8AHLli3bvHmzu/WQJyMjY8KECe7WLP7555/x48e7W2Ng586d7qb4sSfE7Nmzd+zY8d9///37779r1qxxDzqAyJDyzqJFi0aOHMlNxlV094mY+fvvvz/88MPXX3995syZ7j6xf+zatcvdFGLLli0ff/wxN7C7IwtEau7cuUuXLnV3BINjx4498sgjR4wYsXHjxubNm3/zzTe2q0uXLjeGGDJkyEnZsVr8008/lStXLjMz024VC9u3b//999+5VVieMWPGzz//7Bowb94812R//PFHTvXdd98dPXr0G2+8wX9t1/Tp09977z27yvP71ltvzZ8/37ZY+vfvf+aZZ7pbI/Hqq68GQqxatYrVAQMGTJ061fa+9tprJ5988tFHH/3iiy/axlhYvXp18eLFP/30U3dHFp999hnx3LRpk7vDAU6zbt26iGNatWr19ttvH3bYYT169LjgggsmTZp0xBFHYE7OMRs2bOB6HZgURIaUF3hc27VrZ+4/qFSpEjmje9DBzAGrzKZMmVKiRAkbycsuu2z37t3uQSJPNGjQAJ11twaDKGbZsmWJdr58+V5++WV3dzD4559/Nm3atHbt2kZbLeTOV199NRvWrFnz8ccf79ChA1qJfiH6ZkCFChXS09P/97//de/eHcVH5gYPHoyYHnPMMWPGjDFjcEH2MGfOnH37dcCTddttt1155ZUNGzZkP5UrVz722GMLFSpkbg+kkzGNGjW6/vrrnVtxnvQ6DQB69+59+OGHc4annHJK4cKF8+fPb20MS+Pchg0bZla7du3KTWh6Ue1ff/2VmWKcK1euvPfee0uWLIkxL1myBBc34ydOnHjiiSdWrFiR+R5//PH4QZkyZdLS0jiHhx56KBiqac444wxWa9So8cEHHwRDnle/fn3OvG3btmYnMXL//fezH+LJI4lnEN7169c7B+D0DPjjjz+cjRbO+e677z7qqKNMAMkMXnjhBdvLrurUqVOrVi2Cc/rpp1977bXt27cvX778syFsPJkOIWKaX3/9td02QciQcuCdd9555ZVXeE5Y/uuvv4YOHfrVV18NHz6cq9uvXz9uXy4S9+WFF17o3vJgJpCA364iRpKk7JxzzuFp37Zt23PPPcdx8/ZaI0fibrFk3Fbg7DJJ+uTJk7/99lszTQOpPeXIL7/8YlvCQVA++uijH374wdlICYL2kenblogHZYGdf/nllwwmsKb3888/J5idOnVit3Zzw6233oowIbuoD1YRXkVdfvnlyBO25GqnhuBiNW7cuECBAsgx+shFfPTRR7EQM4AHgXOgQmrZsiUjUTpCgV0xnmttxnz33XecGFd8336zc91117Vp0+aRRx4ZNGhQ3bp1qSpeeuklappZs2YZSzj33HM5c9dWp556ardu3VyNwVBx8OCDDx533HGuIgPnKFasGPUHFR5ybOsn5m60OxyKQjPm+++/v++++9gtJ8l9hTdjfswRt9h3gFCyxe398MMPm9XFixdTODoH5Mhvv/2GlZI9VK1alUKNeHIaTkcJRjUk7h825EpxXPIG5tirVy/cvXPnzmYAt1aLFi0IDnvAtql3cdZq1aoRdlqef/55596YL95MxJyNccdXhhR30YFRo0ZxbXAglsk1yIOWL19+/vnnk+/YMTxyjHGpyUFNIAGGFDGSwdDbGDMAuWHA+++/79wqXsR9RuzQqphdpsIz4kX1YLoyMzNNCch8vRJMxpgclpLFpu3z5s0rVaqUaezfv79pjHhQFshezXFxGqydxnr16tkWMyaQFQGSevOkoEc0IvSm3YCM0jh79mxnI7zxxhvFs6C8MMWH5dJLLw2GDIl29J0SB4fAnBBuBlMo2NfaM2fOZP/h79zCGTBg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zZFLNmHDZs2arVmzxrT36NGDQqFKlSrmi2dfymh4KBRJIUSMyJDij/QxXiiSQhxSyJDij2Q0XiiSQhxSyJDiT3p6+vTp092tIvcokkIcUsiQhBBCpAQyJCGEECmBDEkIIURKIEMSQgiREsiQhBBCpAQyJCGEECmBrwzpsRABB6y6Bhx0vUkn+ukdLL2uAUKIFMRXhoT0uJsOcpIlo8k6buLw370hhP+QIaU0yZpRso6bOPw3IyH8hwwppUnWjJJ13MThvxkJ4T9kSClNsmaUrOMmDv/NSAj/4StD0i8f8SJZx00c/rs3hPAfvjIk/5EsGU3WcYUQhzIyJCGEECmBDEkIkQN79uz5+++/3a0iEi+++OKyZcvcrdnZvn374sWL3a0pxs6dO3ft2mWWOeHsnYlChpR3Fi1aNHLkyPHjx//777/uPhEzKN2HH374+uuvz5w5090n9hu8ZMaMGe++++4ff/zh7osNxKhVq1bly5f/888/f/jhh969e+/evds5gJ0PDPHSSy89//zz12bnu+++syPvuOOOZ5991rFpXti0aZO7KYTrrFjdsmULs/7tt99Wr179448//v7776aLxldffXXWrFl2MDchLdOmTbMtTm688cYYT/v+++8PBALHHXfcunXrTMv8+fNXrFjhHNOxY8cWLVoUK1bs22+/dbbHQocOHbp16+ZuDePKK6987bXX3K0x88wzzwwdOvTiiy9+6KGHrrrqqsmTJ99+++1cSve4BOArQzpgv3zwkLdr1y6QRaVKlXLMiUREpkyZUqJECRvJyy67zCUr8eKA3RsHHtLY9evXu1tD7Nixo0mTJia2KOA333zjHpEFAtqsWbMzzjhj4cKFzvbPP//8zDPPLFiw4IgRI7766quuXbuyK0Y6C6ZzzjmnYsWKp5122jHHHENiUa9evSOPPLJz58533XUXgz/55BM7sly5cjw4dtXFxIkTOcqgQYOeeOKJ++67Lz09/brrruNYderUqV69+hdffGGGIY7VqlXLvmnwlVdeKVmypDM15Lj2vjKcffbZpovn96KLLuJsrUl36tSJOTq900nZsmVvueUWZwsmhze0b9+ek2zbtm2bNm04q9tuu61y5coc6NRTT8ULzcgLL7wwX758l1xyyZdffmla3nrrLY5Vu3btxo0b79tjDHCVCxUqhENwjfC5uXPncnXcg0Iw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" /></p>


このような動作により、`std::make_shared<>`で生成されたX、Yオブジェクトは解放される。

---

次は**メモリリークが発生する**`std::shared_ptr`の誤用を示す。まずはクラスの定義から。

```cpp
    //  example/stdlib_and_concepts/shared_ptr_cycle_ut.cpp 91

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
    //  example/stdlib_and_concepts/shared_ptr_cycle_ut.cpp 151

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
    //  example/stdlib_and_concepts/shared_ptr_cycle_ut.cpp 165

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
    //  example/stdlib_and_concepts/shared_ptr_cycle_ut.cpp 192

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
    //  example/stdlib_and_concepts/shared_ptr_cycle_ut.cpp 204
    }  // この次の行で、x0はスコープアウトするため、x0にはアクセスできず、すでにy0にもアクセスできない
    // ここではx0、y0がもともと持っていたXオブジェクト、Yオブジェクトへのポインタを完全に失ってしまった状態

    ASSERT_EQ(X::constructed_counter, 1);  // Xオブジェクトは未開放であり、リークが発生
    ASSERT_EQ(Y::constructed_counter, 1);  // Yオブジェクトは未開放であり、リークが発生
```

<!-- pu:essential/plant_uml/shared_cyclic_3.pu--><p><img src="data:image/png;base64,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" /></p>

X、Yオブジェクトへの[ハンドル](glossary.md#SS_21_5_8)を完全に失った状態であり、X、Yオブジェクトを解放する手段はない。

---

## Polymorphic Memory Resource(pmr) <a id="SS_20_7"></a>
Polymorphic Memory Resource(pmr)は、
動的メモリ管理の柔軟性と効率性を向上させるための、C++17から導入された仕組みである。

[std::pmr::polymorphic_allocator](stdlib_and_concepts.md#SS_20_7_2)はC++17で導入された標準ライブラリのクラスで、
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

* [std::pmr::memory_resource](stdlib_and_concepts.md#SS_20_7_1)  
* [std::pmr::polymorphic_allocator](stdlib_and_concepts.md#SS_20_7_2)  
* [pool_resource](stdlib_and_concepts.md#SS_20_7_3)

### std::pmr::memory_resource <a id="SS_20_7_1"></a>
std::pmr::memory_resourceは、
ユーザー定義のメモリリソースをカスタマイズし、
[std::pmr::polymorphic_allocator](stdlib_and_concepts.md#SS_20_7_2)を通じて利用可能にする[インターフェースクラス](core_lang_spec.md#SS_19_4_11)である。

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

        bool do_is_equal(memory_resource const& other) const noexcept override { return this == &other; }
    };
```

### std::pmr::polymorphic_allocator <a id="SS_20_7_2"></a>
std::pmr::polymorphic_allocatorはC++17で導入された標準ライブラリのクラスで、
C++のメモリリソース管理を抽象化するための機能を提供する。
[std::pmr::memory_resource](stdlib_and_concepts.md#SS_20_7_1)を基盤とし、
コンテナやアルゴリズムにカスタムメモリアロケーション戦略を容易に適用可能にする。
std::allocatorと異なり、型に依存せず、
ポリモーフィズムを活用してメモリリソースを切り替えられる点が特徴である。

すでに示したmemory_resource_variable([std::pmr::memory_resource](stdlib_and_concepts.md#SS_20_7_1))の単体テストを以下に示すことにより、
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

### pool_resource <a id="SS_20_7_3"></a>
pool_resourceは[std::pmr::memory_resource](stdlib_and_concepts.md#SS_20_7_1)を基底とする下記の2つの具象クラスである。

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


## コンテナ <a id="SS_20_8"></a>
データを格納し、
効率的に操作するための汎用的なデータ構造を提供するC++標準ライブラリの下記のようなクラス群である。

* [シーケンスコンテナ(Sequence Containers)](stdlib_and_concepts.md#SS_20_8_1)
* [連想コンテナ(Associative Containers)(---)
* [無順序連想コンテナ(Unordered Associative Containers)](stdlib_and_concepts.md#SS_20_8_3)
* [コンテナアダプタ(Container Adapters)](stdlib_and_concepts.md#SS_20_8_4)
* [特殊なコンテナ](stdlib_and_concepts.md#SS_20_8_5)

### シーケンスコンテナ(Sequence Containers) <a id="SS_20_8_1"></a>
データが挿入順に保持され、順序が重要な場合に使用する。

| コンテナ                 | 説明                                                                |
|--------------------------|---------------------------------------------------------------------|
| `std::vector`            | 動的な配列で、ランダムアクセスが高速。末尾への挿入/削除が効率的     |
| `std::deque`             | 両端に効率的な挿入/削除が可能な動的配列                             |
| `std::list`              | 双方向リスト。要素の順序を維持し、中間の挿入/削除が効率的           |
| [std::forward_list](stdlib_and_concepts.md#SS_20_8_1_1) | 単方向リスト。軽量だが、双方向の操作はできない                      |
| `std::array`             | 固定長配列で、サイズがコンパイル時に決まる                          |
| `std::string`            | 可変長の文字列を管理するクラス(厳密には`std::basic_string`の特殊化) |

#### std::forward_list <a id="SS_20_8_1_1"></a>

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

### 連想コンテナ(Associative Containers) <a id="SS_20_8_2"></a>
データがキーに基づいて自動的にソートされ、検索が高速である。

| コンテナ           | 説明                                             |
|--------------------|--------------------------------------------------|
| `std::set`         | 要素がソートされ、重複が許されない集合           |
| `std::multiset`    | ソートされるが、重複が許される集合               |
| `std::map`         | ソートされたキーと値のペアを保持。キーは一意     |
| `std::multimap`    | ソートされたキーと値のペアを保持。キーは重複可能 |

### 無順序連想コンテナ(Unordered Associative Containers) <a id="SS_20_8_3"></a>
ハッシュテーブルを基盤としたコンテナで、順序を保証しないが高速な検索を提供する。

| コンテナ                  | 説明                                                   |
|---------------------------|--------------------------------------------------------|
| [std::unordered_set](stdlib_and_concepts.md#SS_20_8_3_1) | ハッシュテーブルベースの集合。重複は許されない         |
| `std::unordered_multiset` | ハッシュテーブルベースの集合。重複が許される           |
| [std::unordered_map](stdlib_and_concepts.md#SS_20_8_3_2) | ハッシュテーブルベースのキーと値のペア。キーは一意     |
| `std::unordered_multimap` | ハッシュテーブルベースのキーと値のペア。キーは重複可能 |
| [std::type_index](stdlib_and_concepts.md#SS_20_8_3_3)    | 型情報型を連想コンテナのキーとして使用するためのクラス |

#### std::unordered_set <a id="SS_20_8_3_1"></a>

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

#### std::unordered_map <a id="SS_20_8_3_2"></a>

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

#### std::type_index <a id="SS_20_8_3_3"></a>
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


### コンテナアダプタ(Container Adapters) <a id="SS_20_8_4"></a>
特定の操作のみを公開するためのラッパーコンテナ。

| コンテナ              | 説明                                     |
|-----------------------|------------------------------------------|
| `std::stack`          | LIFO(後入れ先出し)操作を提供するアダプタ |
| `std::queue`          | FIFO(先入れ先出し)操作を提供するアダプタ |
| `std::priority_queue` | 優先度に基づく操作を提供するアダプタ     |

### 特殊なコンテナ <a id="SS_20_8_5"></a>
上記したようなコンテナとは一線を画すが、特定の用途や目的のために設計された一種のコンテナ。

| コンテナ             | 説明                                                       |
|----------------------|------------------------------------------------------------|
| `std::span`          | 生ポインタや配列を抽象化し、安全に操作するための軽量ビュー |
| `std::bitset`        | 固定長のビット集合を管理するクラス                         |
| `std::basic_string`  | カスタム文字型をサポートする文字列コンテナ                 |

## std::optional <a id="SS_20_9"></a>
C++17から導入されたstd::optionalには、以下のような2つの用途がある。
以下の用途2から、
このクラスがオブジェクトのダイナミックなメモリアロケーションを行うような印象を受けるが、
そのようなことは行わない。
このクラスがオブジェクトのダイナミックな生成が必要になった場合、プレースメントnewを実行する。
ただし、std::optionalが保持する型自身がnewを実行する場合は、この限りではない。

1. 関数の任意の型の[戻り値の無効表現](stdlib_and_concepts.md#SS_20_9_1)を持たせる
2. [オブジェクトの遅延初期化](stdlib_and_concepts.md#SS_20_9_2)する(初期化処理が重く、
   条件によってはそれが無駄になる場合にこの機能を使う)

### 戻り値の無効表現 <a id="SS_20_9_1"></a>

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


### オブジェクトの遅延初期化 <a id="SS_20_9_2"></a>

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


## std::variant <a id="SS_20_10"></a>
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

std::variantとstd::visit([Visitor](design_pattern.md#SS_9_4_5)パターンの実装の一種)を組み合わせた場合の使用例を以下に示す。

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


## オブジェクトの比較 <a id="SS_20_11"></a>
### std::rel_ops <a id="SS_20_11_1"></a>
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
        bool operator==(Integer const& other) const noexcept { return x_ == other.x_; }
        bool operator<(Integer const& other) const noexcept { return x_ < other.x_; }

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

### std::tuppleを使用した比較演算子の実装方法 <a id="SS_20_11_2"></a>
クラスのメンバが多い場合、[==演算子](core_lang_spec.md#SS_19_6_3)で示したような方法は、
可読性、保守性の問題が発生する場合が多い。下記に示す方法はこの問題を幾分緩和する。

```cpp
    //  example/stdlib_and_concepts/comparison_stdlib_ut.cpp 56

    struct Point {
        int x;
        int y;

        bool operator==(Point const& other) const noexcept { return std::tie(x, y) == std::tie(other.x, other.y); }

        bool operator<(Point const& other) const noexcept { return std::tie(x, y) < std::tie(other.x, other.y); }
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

## その他 <a id="SS_20_12"></a>
### SSO(Small String Optimization) <a id="SS_20_12_1"></a>
一般にstd::stringで文字列を保持する場合、newしたメモリが使用される。
64ビット環境であれば、newしたメモリのアドレスを保持する領域は8バイトになる。
std::stringで保持する文字列が終端の'\0'も含め8バイト以下である場合、
アドレスを保持する領域をその文字列の格納に使用すれば、newする必要がない(当然deleteも不要)。
こうすることで、短い文字列を保持するstd::stringオブジェクトは効率的に動作できる。

SOOとはこのような最適化を指す。

### heap allocation elision <a id="SS_20_12_2"></a>
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



