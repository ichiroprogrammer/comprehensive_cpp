<!-- ./md/code_analysis.md -->
# コード解析 <a id="SS_4"></a>
本ドキュメントでは、ソースコードの品質を向上するために下記のような様々な方法を推奨する。

* [自動単体テスト](process_and_infra.md#SS_10_2_1) 
* [自動統合テスト](process_and_infra.md#SS_10_2_3)
* [コードインスペクション](process_and_infra.md#SS_10_2_5_1_2)
* ツールによるコード解析

ツールによるコード解析(以下、単にコード解析と呼ぶ)とは、
開発対象のソフトウェアの仕様とは無関係に発見できるバグやその類、セキュリティホール、
コーディングルール不順守、その他のソースコード記述の問題を発見するための検出手段であり、
動的、静的に分類される。
静的コード解析には、以下のようなものがある。

1. ソースコードの記述自体の解析
2. 実行形式バイナリコードの解析
3. 各種メトリクスやリバースエンジニアリングツールを用いた解析

本章では、無償のオープンソースで実施できる静的解析1と動的解析について解説を行う。

___

__この章の構成__

&emsp;&emsp; [コンパイラによる静的解析](code_analysis.md#SS_4_1)  
&emsp;&emsp; [scan-buildによる静的解析](code_analysis.md#SS_4_2)  
&emsp;&emsp; [cppcheck静的解析](code_analysis.md#SS_4_3)  
&emsp;&emsp; [sanitizerによる動的解析](code_analysis.md#SS_4_4)  
&emsp;&emsp; [まとめ](code_analysis.md#SS_4_5)  
  
  

[インデックス](introduction.md#SS_1_4)に戻る。  

___

## コンパイラによる静的解析 <a id="SS_4_1"></a>
コンパイラによる静的解析とは、コンパイラの警告出力を使用する解析である。
静的解析の中で最も手軽に実施することができるが、
意外なほど多くのソフトウェア開発でおざなりにされている。

多くのコンパイラでは警告をエラーとして扱うオプションが用意されているため、
それをオンにしたビルドをすることで、多くのバグやバグの元となり得るコードを排除できる。

### g++の警告機能 <a id="SS_4_1_1"></a>
本ドキュメントのサンプルコードは、
以下のような[g++](cpp_idioms.md#SS_20_12_1)/[clang++](cpp_idioms.md#SS_20_12_2)の警告機能を使用してビルドを行っている。

```Makefile
    -Werror -Wall -Wextra -Weffc++
```

また、[演習](exercise_q.md#SS_21)で使用するコードに関しては、あえて問題のあるコードを記述するため、
下記のようなオプションを使用し一部の警告を抑止している。

```Makefile
    //  exercise/programming_convention_q/Makefile 4
     
    SUPPRESS_WARN=-Wno-effc++ -Wno-unused-variable -Wno-delete-incomplete -Wno-unused-function \
                  -Wno-sizeof-array-argument -Wno-unused-parameter -Wno-conversion-null \
                  -Wno-literal-conversion
```

実際のコードによりこの効果を例示する。

```cpp
    //  example/code_analysis/code_analysis.cpp 24

    int32_t  x{-1};
    uint32_t y{1};

    bool b0{x < y};
    ASSERT_FALSE(b0);  // 数学では成立する x < y が成立しない

    ++x, ++y;
    bool b1{x < y};
    ASSERT_TRUE(b1);  // x、yが正になれば x < y が成立する
```

上記コードでは、int32_tであるxとuint32_tであるyを比較することにより、xがuin32_tに型変換されるため、
数学的には自明な x < y が成立しない。
「[整数型](programming_convention.md#SS_3_1_1_1)」で述べたルールに違反したために発生する問題であるが、
その検出はg++により下記のように行うことができる。

```cpp
    //  example/code_analysis/warnings/GCC.txt 2

    code_analysis.cpp:29:15: warning: comparison of integer expressions of different signedness: ‘int32_t’ {aka ‘int’} and ‘uint32_t’ {aka ‘unsigned int’} [-Wsign-compare]
       29 |     bool b0{x < y};
          |             ~~^~~
    code_analysis.cpp:33:15: warning: comparison of integer expressions of different signedness: ‘int32_t’ {aka ‘int’} and ‘uint32_t’ {aka ‘unsigned int’} [-Wsign-compare]
       33 |     bool b1{x < y};
          |             ~~^~~
```

次のコードは、[Pimpl](cpp_idioms.md#SS_20_2_1)パターンの誤った実装よってメモリリークを引き起こす
(「[delete](programming_convention.md#SS_3_5_6_2)」参照)。

```cpp
    //  example/code_analysis/code_analysis.cpp 46

    class Pimpl {
    public:
        Pimpl();
        ~Pimpl() { delete core_; }  // 不完全型のdelete
    private:
        class PimplCore;
        PimplCore* core_;
    };

    class Pimpl::PimplCore {
    public:
        PimplCore() : x_{new X} {}
        ~PimplCore() { delete x_; }  // ~PimplCore()から呼び出されない

    private:
        X* x_;
    };

    Pimpl::Pimpl() : core_{new PimplCore} {}

    void incomplete_class()
    {
        // ~Pimpl()では、クラスPimplCoreが不完全型なので~PimplCore()が呼び出されないため、
        // x_の解放がされずメモリリークする
        auto pimpl = Pimpl{};
    }
```

このように連続的に記述されている場合は、コードインスペクションで発見できるかもしれないが、
クラスの規模がある程度大きくなれば、このような問題を目視で発見することは容易ではない。
一方でg++は下記のように、いとも簡単にそれを指摘する。

```cpp
    //  example/code_analysis/warnings/GCC.txt 20

    code_analysis.cpp: In destructor ‘Pimpl::~Pimpl()’:
    code_analysis.cpp:51:16: warning: possible problem detected in invocation of ‘operator delete’ [-Wdelete-incomplete]
       51 |     ~Pimpl() { delete core_; }  // 不完全型のdelete
          |                ^~~~~~~~~~~~
    code_analysis.cpp:51:23: warning: invalid use of incomplete type ‘class Pimpl::PimplCore’
       51 |     ~Pimpl() { delete core_; }  // 不完全型のdelete
          |                       ^~~~~
    code_analysis.cpp:53:11: note: forward declaration of ‘class Pimpl::PimplCore’
       53 |     class PimplCore;
          |           ^~~~~~~~~
```

また、「[move処理](programming_convention.md#SS_3_9_4)」
で触れたようなパフォーマンスに悪影響のある下記のようなコードに対しても、
g++は適切な指摘をすることができる。

```cpp
    //  example/code_analysis/code_analysis.cpp 76

    std::string prevent_copy_elision()
    {
        auto ret = std::string{"prevent copy elision"};

        return std::move(ret);  // std::moveのためにRVOが阻害される
    }

    void rvo_inhibition()
    {
        // RVOが機能すればstd::stringのコンストラクタは一度だけ呼び出される
        std::string a = prevent_copy_elision();
    }
```

```cpp
    //  example/code_analysis/warnings/GCC.txt 45

    code_analysis.cpp: In function ‘std::string prevent_copy_elision()’:
    code_analysis.cpp:82:21: warning: moving a local object in a return statement prevents copy elision [-Wpessimizing-move]
       82 |     return std::move(ret);  // std::moveのためにRVOが阻害される
          |            ~~~~~~~~~^~~~~
    code_analysis.cpp:82:21: note: remove ‘std::move’ call
```

### clang++の警告機能 <a id="SS_4_1_2"></a>
clang++にもg++と同様の優れた警告機能が備わっているが、それらは実装が異なるため、
下記のような混乱を引き起こすコードに対して(「[オーバーライド](programming_convention.md#SS_3_2_4_7)」参照)、
clang++は、g++ができない問題点の指摘を行うことができる。

```cpp
    //  example/code_analysis/code_analysis.cpp 92

    class OverloadVirtualBase {
    public:
        OverloadVirtualBase()          = default;
        virtual ~OverloadVirtualBase() = default;
        virtual void DoSomething(int32_t) noexcept  // 派生クラスがオーバーライドできる。
        {
            // ...
        }
    };

    class OverloadVirtualDerived : public OverloadVirtualBase {
    public:
        // シグネチャが異なるためOverloadVirtualBase::DoSomethingのオーバーライドではない。
        virtual void DoSomething(uint32_t) noexcept
        {
            // ...
        }
    };
```

```cpp
    //  example/code_analysis/warnings/CLANG.txt 19

    code_analysis.cpp:108:18: warning: 'OverloadVirtualDerived::DoSomething' hides overloaded virtual function [-Woverloaded-virtual]
        virtual void DoSomething(uint32_t) noexcept
                     ^
    code_analysis.cpp:98:18: note: hidden overloaded virtual function 'OverloadVirtualBase::DoSomething' declared here: type mismatch at 1st parameter ('int32_t' (aka 'int') vs 'uint32_t' (aka 'unsigned int'))
        virtual void DoSomething(int32_t) noexcept  // 派生クラスがオーバーライドできる。
```

こういった問題があるため、両コンパイラによるコンパイルを薦める。

## scan-buildによる静的解析 <a id="SS_4_2"></a>
scan-buildはclang++をベースにした静的解析ツールであり、
コンパイラの警告機能では指摘できないバグやバグの元となり得るコードを指摘できる。

まずは、問題のあるコードを以下に示す。

```cpp
    //  example/code_analysis/code_analysis.cpp 115

    class IllegalShallowCopy {
    public:
        IllegalShallowCopy() : x_{new X} {}
        ~IllegalShallowCopy() { delete x_; }

    private:
        X* x_;
    };

    void illegal_shallow_copy()
    {
        auto a = IllegalShallowCopy{};
        auto b = IllegalShallowCopy{};

        a = b;  // a.x_ = b.x_が行われるため、代入前のa.x_は解放されず、
                // 代入後のb.x_は2度deleteされる
    }
```

上記クラスIllegalShallowCopyは、オブジェクトをnewにより生成し、そのポインタをメンバ変数として持つ。
このようなクラスに対しては[ディープコピー](cpp_idioms.md#SS_20_9_2)を実装するか、
オブジェクトのコピーを禁止すべきであることは、「[コンストラクタ](programming_convention.md#SS_3_2_4_2)」で述べた通りである。

こういったコードに対して、g++/clang++はその問題を発見できないが、
scan-buildは下記のように適切な指摘を行うことができる。

```cpp
    //  example/code_analysis/warnings/scan-build.txt 1

    code_analysis.cpp:120:29: warning: Attempt to free released memory [cplusplus.NewDelete]
        ~IllegalShallowCopy() { delete x_; }
                                ^~~~~~~~~
```

次に示すのは、
「[RAII(scoped guard)](cpp_idioms.md#SS_20_1_2)」に従わなかったために発生した潜在的バグを含んだコードである。

```cpp
    //  example/code_analysis/code_analysis.cpp 138

    void potential_leak()
    {
        X* x{new X};

        if (global == 2) {  // globalが2ならメモリリーク
            return;
        }

        delete x;
    }
```

こういったコードに対しても以下に示す通り適切なメッセージを出力する。

```cpp
    //  example/code_analysis/warnings/scan-build.txt 7

    code_analysis.cpp:145:9: warning: Potential leak of memory pointed to by 'x' [cplusplus.NewDeleteLeaks]
            return;
            ^~~~~~
```

scan-buildは以下のような方法で簡単に使用できるため、
C++でのソフトウェア開発における必須アイテムの一つであるといえる。

	    > scan-build make

## cppcheck静的解析 <a id="SS_4_3"></a>
cppcheckはscan-buildと同様な静的解析ツールであり、
コンパイラの警告機能では指摘できないバグやバグの元となり得るコードを指摘できる。

まずは、問題のあるコードを以下に示す。

```cpp
    //  example/code_analysis/code_analysis.cpp 152

    int32_t array_access(int32_t index)
    {
        uint32_t array[8]{};

        return array[index];
    }

    void array_stask_read_overflow()
    {
        array_access(8);  // off-by-1 このようなコードは意外なほど多い
    }
```

問題は、配列への不正アクセスであり、これは未定義動作につながる典型的なバグであるが、
scan-buildでは発見できない。

cppcheckはこういったコードに対して以下に示す通り適切なメッセージを出力する。

```cpp
    //  example/code_analysis/warnings/cppcheck.txt 1

    [1mcode_analysis.cpp:158:17: [31merror:[39m Array 'array[8]' accessed at index 8, which is out of bounds. [arrayIndexOutOfBounds][0m
        return array[index];
                    ^
    [1mcode_analysis.cpp:163:18: [2mnote:[0m Calling function 'array_access', 1st argument '8' value is 8
        array_access(8);  // off-by-1 このようなコードは意外なほど多い
                     ^
    [1mcode_analysis.cpp:158:17: [2mnote:[0m Array index out of bounds
        return array[index];
                    ^
```

このバグは、後述するsanitizerで発見できるものの、静的解析で発見できた方が当然ながら好ましい。

cppcheckは以下のような方法で簡単に使用できるため、
C++でのソフトウェア開発における必須アイテムの一つであるといえる。

        > bear make --always-make       # compile_commands.jsonの生成
        > cppcheck --project=compile_commands.json 2> cppcheck_bugs.txt

## sanitizerによる動的解析 <a id="SS_4_4"></a>
本ドキュメントで扱うsanitizerとは、無償で利用できるC/C++動的解析ツールである。
sanitizerオプションをオンにしたg++/clang++でテスト対象をビルドし、
生成された実行形式バイナリを駆動することで使用することができる。

サンプルコードをsanitizerで解析するために使用したg++/clang++のコンパイルオプションを以下に示す。

```
    -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow
```

これらのオプションは、g++/clang++共通である。

このオプションを使用した実行形式コードがどのように動作するのかを例示するために、
まずは、動的解析対象のコードを下記する。

```cpp
    //  example/code_analysis/code_analysis.cpp 167

    class NonVirtualDestructorBase {
    public:
        NonVirtualDestructorBase() noexcept {}
        ~NonVirtualDestructorBase() { std::cout << __func__ << std::endl; }
    };

    class NonVirtualDestructorDerived : public NonVirtualDestructorBase {
    public:
        NonVirtualDestructorDerived(char const* str) : str_{std::make_unique<std::string>(str)} {}
        ~NonVirtualDestructorDerived() { std::cout << __func__ << std::endl; }
        std::string const& Get() const noexcept { return *str_; }

    private:
        std::unique_ptr<std::string> str_;
    };

    void non_virtual_destructor()
    {
        // ~NonVirtualDestructorBase()が非virtualであるため、aの解放時に~NonVirtualDestructorDerived()
        // が呼び出されないことによってNonVirtualDestructorDerived::str_はリークする。
        std::unique_ptr<NonVirtualDestructorBase> a{std::make_unique<NonVirtualDestructorDerived>("D")};
    }
```

上記コードは、「[継承/派生](programming_convention.md#SS_3_2_6)」で説明した内容(基底クラスのデストラクタはvirtual)に反するため、
メモリ管理にstd::unique_ptr<>を使用しているにもかかわらずメモリリークを引き起こす。
g++/clang++/scan-build/cppcheckはこの問題を指摘できないが、
sanitizerは以下のような出力によりメモリリークを指摘することができる。

```cpp
    //  example/code_analysis/warnings/sanitizer.txt 4

    ==4691==ERROR: AddressSanitizer: new-delete-type-mismatch on 0x602000000410 in thread T0:
      object passed to delete has wrong type:
      size of the allocated type:   8 bytes;
      size of the deallocated type: 1 bytes.
        #0 0x7f79c7b5422f in operator delete(void*, unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:172
        #1 0x55aae7e44f4f in std::default_delete<NonVirtualDestructorBase>::operator()(NonVirtualDestructorBase*) const /usr/include/c++/11/bits/unique_ptr.h:85
        #2 0x55aae7e42954 in std::unique_ptr<NonVirtualDestructorBase, std::default_delete<NonVirtualDestructorBase> >::~unique_ptr() /usr/include/c++/11/bits/unique_ptr.h:361
        #3 0x55aae7e37129 in non_virtual_destructor() /home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/code_analysis.cpp:190
        #4 0x55aae7e3b7fd in exec_background(void (*)()) /home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/code_analysis.cpp:366
        #5 0x55aae7e3ba66 in all() /home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/code_analysis.cpp:378
        #6 0x55aae7e3baf0 in CodeAnalysis_others_Test::TestBody() /home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/code_analysis.cpp:382
        #7 0x55aae7e919e0 in void testing::internal::HandleSehExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void (testing::Test::*)(), char const*) (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0x969e0)
        #8 0x55aae7e8986c in void testing::internal::HandleExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void (testing::Test::*)(), char const*) (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0x8e86c)
        #9 0x55aae7e63623 in testing::Test::Run() (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0x68623)
        #10 0x55aae7e64050 in testing::TestInfo::Run() (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0x69050)
        #11 0x55aae7e649af in testing::TestSuite::Run() (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0x699af)
        #12 0x55aae7e74162 in testing::internal::UnitTestImpl::RunAllTests() (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0x79162)
        #13 0x55aae7e92b03 in bool testing::internal::HandleSehExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*) (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0x97b03)
        #14 0x55aae7e8ab12 in bool testing::internal::HandleExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*) (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0x8fb12)
        #15 0x55aae7e72859 in testing::UnitTest::Run() (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0x77859)
        #16 0x55aae7ea90aa in RUN_ALL_TESTS() (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0xae0aa)
        #17 0x55aae7ea9023 in main (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0xae023)
        #18 0x7f79c6f38d8f  (/lib/x86_64-linux-gnu/libc.so.6+0x29d8f)
        #19 0x7f79c6f38e3f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x29e3f)
        #20 0x55aae7e35204 in _start (/home/ichiro/ichiroprogrammer/comprehensive_cpp/example/code_analysis/sanitizer/example.exe+0x3a204)

    // ...

    SUMMARY: AddressSanitizer: new-delete-type-mismatch ../../../../src/libsanitizer/asan/asan_new_delete.cpp:172 in operator delete(void*, unsigned long)
```

次に示すコードは、型が違うインスタンスへの代入によりオーバーフローを起こしてしまう例である。
先に示したコード同様、
g++/clang++/scan-build/cppcheckでは指摘されない問題がsanitizerにより指摘される。

```cpp
    //  example/code_analysis/code_analysis.cpp 386

    float x{0x1'0000'0000};
    // int32_t y{x};  // yのレンジを超えるため、コンパイルエラー
    int32_t y = x;
```

```cpp
    //  example/code_analysis/warnings/sanitizer.txt 585

    code_analysis.cpp:390:17: runtime error: 4.29497e+09 is outside the range of representable values of type 'int'
```

sanitizerは以上に示した通り極めて優れたバグ検出能力を持つが、
動的解析の特性からソースコードに上記のようなバグがあってもそれが実行されなければ、
そのバグは指摘されない。

また、このような指摘をするためのコードは実行形式バイナリの中にコンパイル時に組み込まれるため、
以下のような問題が発生する。

* ランタイム動作が遅くなる。
* ビルド時間が延びる。
* 実行形式バイナリのファイルサイズが巨大になる。

このためプログラミングの最中に行われる動作確認や手作業でのシステムテスト(特に組み込みソフトウェア)
に用いる実行形式バイナリにsanitizerを適用することは難しい。

従って、[CI(継続的インテグレーション)](process_and_infra.md#SS_10_2_5)の一環で行われる
[自動単体テスト](process_and_infra.md#SS_10_2_1)や[自動統合テスト](process_and_infra.md#SS_10_2_3)でのsanitizerの使用を薦める。


## まとめ <a id="SS_4_5"></a>
以上で述べてきたようにコード解析ツールにはそれぞれ得手不得手があり、完璧なものは存在しないため、
これらを組み合わせてコード品質の向上に努める必要があるが、
これらの実施が各プログラマによって個別に行われるのであれば、
コンパイル時間の増大等による新たなロスが発生する。

上記や「[CI項目の例](process_and_infra.md#SS_10_2_5_5)」で述べたように自動化によって、こういったロスを回避しつつ、
様々なコード解析ツールを組み合わせて使用することが効率的なプロセスの要件となる。


