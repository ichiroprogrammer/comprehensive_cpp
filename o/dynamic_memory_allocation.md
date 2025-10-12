<!-- deep/md/dynamic_memory_allocation.md -->
# ダイナミックメモリアロケーション <a id="SS_14"></a>
本章で扱うダイナミックメモリアロケーションとは、new/delete、malloc/free
によるメモリ確保/解放のことである。

malloc/freeは、

* 最長処理時間を規定できない(リアルタイム性の欠如)
* メモリのフラグメントを起こす

等の問題(「[malloc/freeの問題点](dynamic_memory_allocation.md#SS_14_1)」参照)を持っている。
new/deleteは通常malloc/freeを使って実装されているため同じ問題を持っているが、
これらが汎用OS上でのアプリケーションで実際の不具合につながることはほとんどない。一方で、 

* リアルタイムな応答が要求される
* メモリの使用制限が厳しい(ページングと2次記憶がない)

ような組み込みソフトでは、上記の2点は致命的な不具合につながる。

本章では、この問題を回避するための技法を紹介する。

___

__この章の構成__

&emsp;&emsp; [malloc/freeの問題点](dynamic_memory_allocation.md#SS_14_1)  
&emsp;&emsp; [グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_2)  
&emsp;&emsp;&emsp; [固定長メモリプール](dynamic_memory_allocation.md#SS_14_2_1)  
&emsp;&emsp;&emsp; [グローバルnew/deleteのオーバーロードの実装](dynamic_memory_allocation.md#SS_14_2_2)  
&emsp;&emsp;&emsp; [プレースメントnew](dynamic_memory_allocation.md#SS_14_2_3)  
&emsp;&emsp;&emsp; [デバッグ用イテレータ](dynamic_memory_allocation.md#SS_14_2_4)  

&emsp;&emsp; [クラスnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_3)  
&emsp;&emsp; [STLコンテナのアロケーター](dynamic_memory_allocation.md#SS_14_4)  
&emsp;&emsp;&emsp; [STLコンテナ用アロケータ](dynamic_memory_allocation.md#SS_14_4_1)  
&emsp;&emsp;&emsp; [可変長メモリプール](dynamic_memory_allocation.md#SS_14_4_2)  
&emsp;&emsp;&emsp; [デバッグ用イテレータ](dynamic_memory_allocation.md#SS_14_4_3)  
&emsp;&emsp;&emsp; [エクセプション処理機構の変更](dynamic_memory_allocation.md#SS_14_4_4)  

&emsp;&emsp; [Polymorphic Memory Resource(pmr)](dynamic_memory_allocation.md#SS_14_5)  
&emsp;&emsp;&emsp; [std::pmr::memory_resource](dynamic_memory_allocation.md#SS_14_5_1)  
&emsp;&emsp;&emsp; [std::pmr::polymorphic_allocator](dynamic_memory_allocation.md#SS_14_5_2)  
&emsp;&emsp;&emsp; [pool_resource](dynamic_memory_allocation.md#SS_14_5_3)  
  
  

[このドキュメントの構成](introduction.md#SS_1_7)に戻る。  

___

## malloc/freeの問題点 <a id="SS_14_1"></a>
UNIX系のOSでの典型的なmalloc/freeの実装例の一部を以下に示す
(この実装は長いため、
全体は巻末の「[example/dynamic_memory_allocation/malloc_ut.cpp](sample_code.md#SS_24_2_35)」に掲載する)。

```cpp
    //  example/dynamic_memory_allocation/malloc_ut.cpp 19

    namespace {

    struct header_t {
        header_t* next;
        size_t    n_nuits;  // header_tが何個あるか
    };

    header_t*        header{nullptr};
    SpinLock         spin_lock{};
    constexpr size_t unit_size{sizeof(header_t)};

    inline bool sprit(header_t* header, size_t n_nuits, header_t*& next) noexcept
    {
        // ...
    }

    inline void concat(header_t* front, header_t* rear) noexcept
    {
        // ...
    }

    header_t* set_back(void* mem) noexcept { return static_cast<header_t*>(mem) - 1; }

    static_assert(sizeof(header_t) == alignof(std::max_align_t));

    void* malloc_inner(size_t size) noexcept
    {
        // ...
    }
    }  // namespace
```
```cpp
    //  example/dynamic_memory_allocation/malloc_ut.cpp 105

    void free(void* mem) noexcept
    {
        header_t* mem_to_free = set_back(mem);

        mem_to_free->next = nullptr;

        auto lock = std::lock_guard{spin_lock};

        if (header == nullptr) {
            header = mem_to_free;
            return;
        }

        if (mem_to_free < header) {
            concat(mem_to_free, header);
            header = mem_to_free;
            return;
        }

        auto curr = header;
        for (; curr->next != nullptr; curr = curr->next) {
            if (mem_to_free < curr->next) {  // 常に curr < mem_to_free
                concat(mem_to_free, curr->next);
                concat(curr, mem_to_free);
                return;
            }
        }

        concat(curr, mem_to_free);
    }

    void* malloc(size_t size) noexcept
    {
        void* mem = malloc_inner(size);

        if (mem == nullptr) {
            auto const add_size = Roundup(unit_size, 1024 * 1024 + size);  // 1MB追加

            header_t* add = static_cast<header_t*>(sbrk(add_size));
            add->n_nuits  = add_size / unit_size;
            free(++add);
            mem = malloc_inner(size);
        }

        return mem;
    }
```

上記で示したようにmalloc/freeで使用されるメモリはHeader_t型のheaderで管理され、
このアクセスの競合はspin_lockによって回避される。
headerが管理するメモリ用域からのメモリの切り出しはmalloc_innerによって行われるが、
下のフラグメントの説明でも示す通り、
headerで管理されたメモリは長さの上限が単純には決まらないリスト構造になるため、
このリストをなぞるmalloc/freeにリアルタイム性の保証をすることは困難である。

アプリケーションが実行する最初のmallocから呼び出されるmalloc_innerは、
headerがnullptrであるため必ずnullptrを返すことになる。

上記の抜粋である下記のコードによりmalloc_innerの戻りがnullptrであった場合、sbrkが呼び出される。

```cpp
    //  example/dynamic_memory_allocation/malloc_ut.cpp 148

    if (mem == nullptr) {
        auto const add_size = Roundup(unit_size, 1024 * 1024 + size);  // 1MB追加

        header_t* add = static_cast<header_t*>(sbrk(add_size));
        add->n_nuits  = add_size / unit_size;
        free(++add);
        mem = malloc_inner(size);
    }
```

sbrkとはOSからメモリを新たに取得するための下記のようなシステムコールである。

```cpp
    //  example/dynamic_memory_allocation/malloc_ut.cpp 13

    extern "C" void* sbrk(ptrdiff_t __incr);
```

OSがアプリケーションに割り当てるための十分なメモリを持っていない場合、
sbrkは
[ページング](https://ja.wikipedia.org/wiki/%E3%83%9A%E3%83%BC%E3%82%B8%E3%83%B3%E3%82%B0%E6%96%B9%E5%BC%8F)
によるメモリ確保のトリガーとなる。
これはOSのファイルシステムの動作を含む処理であるため、やはりリアルタイム性の保証は困難である。

[フリースタンディング環境](term_explanation.md#SS_19_21_2)では、sbrkのようなシステムコールは存在しないため、
アプリケーションの未使用領域や静的に確保した領域を上記コードで示したようなリスト構造で管理し、
mallocで使用することになる。
このような環境では、sbrkによるリアルタイム性の阻害は発生しないものの、
メモリ管理ためのリスト構造があるため、やはりリアルタイム性の保証は難しい。

次にもう一つの問題である「メモリのフラグメントを起こす」ことについて見て行く。

```cpp
    //  example/dynamic_memory_allocation/malloc_ut.cpp 190

    void* mem[1024];

    for (auto& m : mem) {  // 32バイト x 1024個のメモリ確保
        m = malloc(32);
    }

    // memを使用した何らかの処理
    // ...

    for (auto i = 0U; i < ArrayLength(mem); i += 2) {  // 512個のメモリを解放
        free(mem[i]);
    }
```

上記のような処理の後、解放されたメモリは、32バイト
(メモリヘッダがあるため、実際はもう少し大きい)の断片が512個ある状態になるため、
このサイズを超える新たなmallocの呼び出しには使えない。
このため、ページングが行えないようなOS上のアプリケーションでは、
メモリは十分にあるにもかかわらずmallocが失敗してしまうことが起こり得る。

また、上記freeの実装例の抜粋である下記のコードからわかるように、
このように断片化されたメモリは、そのアドレス順にソートされた単方向リストによって管理される。

```cpp
    //  example/dynamic_memory_allocation/malloc_ut.cpp 120

    if (mem_to_free < header) {
        concat(mem_to_free, header);
        header = mem_to_free;
        return;
    }

    auto curr = header;
    for (; curr->next != nullptr; curr = curr->next) {
        if (mem_to_free < curr->next) {  // 常に curr < mem_to_free
            concat(mem_to_free, curr->next);
            concat(curr, mem_to_free);
            return;
        }
    }

    concat(curr, mem_to_free);
```

この状態でさらにメモリ解放が行われた場合、
freeはこのリストを辿りメモリを最適な場所に戻す必要がある。
戻したメモリがリスト前後のメモリと隣接していれば、それらは結合される。
この処理は断片化への対策であるが、
ページングの無いOS上のアプリケーションにとっては不十分であるばかりでなく、

* freeの排他ロックする期間が長い
* freeの処理が遅い

といったリアルタイム処理を阻害する別の問題も発生させる
(繰り返しになるが、windows/linuxのような通常のOS上のアプリケーションでは、
このような仕様が問題になることはほとんどない)。


## グローバルnew/deleteのオーバーロード <a id="SS_14_2"></a>
すでに述べたように、組み込みソフトにはmalloc/freeを使用したnew/deleteは使えない可能性が高い。
そのような場合に備えC++11ではグローバルなnew/deleteのオーバーロードをサポートする。
ここでは、そのようなnew/deleteの実装例を示すが、
その前にnew/deleteの内部実装用メモリ管理用ライブラリを実装する。


### 固定長メモリプール <a id="SS_14_2_1"></a>
malloc/freeにリアルタイム性がない原因は、

* リアルタイム性がないOSのシステムコールを使用している
* メモリを可変長で管理しているため処理が重いにもかかわらず、この処理中にグローバルロックを行う。

ためである。従って、この問題に対処するためのメモリ管理システムは、

* 初期に静的なメモリを確保
* メモリを固定長で管理

する必要がある。これを含めこの章で開発するメモリ管理システムをメモリプールと呼ぶことにする。

「[グローバルnew/deleteのオーバーロードの実装](dynamic_memory_allocation.md#SS_14_2_2)」で示すように、
このメモリプールは管理する固定長のメモリブロックのサイズごとに複数必要になる一方で、
これらを統合的に扱う必要も出てくる。

そのため、固定長のメモリプールは、

* 複数個のメモリプールを統合的に扱う[インターフェースクラス](term_explanation.md#SS_19_3_13)MPool
* MPoolを基底クラスとし、固定長メモリブロックを管理するクラステンプレートMPoolFixed

によって実装することにする。

まずは、MPoolを下記に示す
(「[ファイル位置を静的に保持したエクセプションクラスの開発](template_meta_programming.md#SS_13_7_6_4)」参照)。

```cpp
    //  example/dynamic_memory_allocation/mpool.h 12

    class MPool {
    public:
        explicit MPool(size_t max_size) : max_size_{max_size} {}

        void* Alloc(size_t size)
        {
            if (size > max_size_) {
                throw MAKE_EXCEPTION(MPoolBadAlloc, "MPF : memory size too big");
            }

            void* mem = alloc(size);

            if (mem == nullptr) {
                throw MAKE_EXCEPTION(MPoolBadAlloc, "MPF : out of memory");
            }

            return mem;
        }

        void* AllocNoExcept(size_t size) noexcept { return alloc(size); }

        void   Free(void* area) noexcept { free(area); }
        size_t GetSize() const noexcept { return get_size(); }           // メモリ最小単位
        size_t GetCount() const noexcept { return get_count(); }         // メモリ最小単位が何個取れるか
        size_t GetCountMin() const noexcept { return get_count_min(); }  // GetCount()の最小値
        bool   IsValid(void const* area) const noexcept { return is_valid(area); }

    protected:
        ~MPool() = default;

    private:
        size_t const max_size_;

        virtual void*  alloc(size_t size) noexcept               = 0;
        virtual void   free(void* area) noexcept                 = 0;
        virtual size_t get_size() const noexcept                 = 0;
        virtual size_t get_count() const noexcept                = 0;
        virtual size_t get_count_min() const noexcept            = 0;
        virtual bool   is_valid(void const* area) const noexcept = 0;
    };
```

次に、MPoolFixedを下記に示す。

```cpp
    //  example/dynamic_memory_allocation/mpool_fixed.h 25

    template <uint32_t MEM_SIZE, uint32_t MEM_COUNT>
    class MPoolFixed final : public MPool {
    public:
        MPoolFixed() noexcept : MPool{mem_chunk_size_} {}

    private:
        using chunk_t = Inner_::mem_chunk<MEM_SIZE>;
        static constexpr size_t mem_chunk_size_{sizeof(chunk_t)};

        size_t           mem_count_{MEM_COUNT};
        size_t           mem_count_min_{MEM_COUNT};
        chunk_t          mem_chunk_[MEM_COUNT]{};
        chunk_t*         mem_head_{setup_mem()};
        mutable SpinLock spin_lock_{};

        chunk_t* setup_mem() noexcept
        {
            for (auto i = 0U; i < MEM_COUNT - 1; ++i) {
                mem_chunk_[i].next = &mem_chunk_[i + 1];
            }

            mem_chunk_[MEM_COUNT - 1].next = nullptr;

            return mem_chunk_;
        }

        virtual void* alloc(size_t size) noexcept override
        {
            assert(size <= mem_chunk_size_);

            auto lock = std::lock_guard{spin_lock_};

            auto mem = mem_head_;

            if (mem != nullptr) {
                mem_head_      = mem_head_->next;
                mem_count_min_ = std::min(--mem_count_, mem_count_min_);
            }

            return mem;
        }

        virtual void free(void* mem) noexcept override
        {
            assert(is_valid(mem));

            auto lock = std::lock_guard{spin_lock_};

            chunk_t* curr_head = static_cast<chunk_t*>(mem);
            curr_head->next    = mem_head_;
            mem_head_          = curr_head;

            mem_count_min_ = std::min(++mem_count_, mem_count_min_);
        }

        virtual size_t get_size() const noexcept override { return mem_chunk_size_; }
        virtual size_t get_count() const noexcept override { return mem_count_; }
        virtual size_t get_count_min() const noexcept override { return mem_count_min_; }

        virtual bool is_valid(void const* mem) const noexcept override
        {
            return (&mem_chunk_[0] <= mem) && (mem <= &mem_chunk_[MEM_COUNT - 1]);
        }
    };
```

上記コードからわかる通り、MPoolFixedは初期化直後、
サイズMEM_SIZのメモリブロックをMEM_COUNT個、保持する。
個々のメモリブロックは、下記のコードのalignas/alignofでアライメントされた領域となる。

```cpp
    //  example/dynamic_memory_allocation/mpool_fixed.h 11

    constexpr size_t MPoolFixed_MinSize{32};

    namespace Inner_ {
    template <uint32_t MEM_SIZE>
    union mem_chunk {
        mem_chunk* next;

        // MPoolFixed_MinSizeの整数倍のエリアを、最大アラインメントが必要な基本型にアライン
        alignas(alignof(std::max_align_t)) uint8_t mem[Roundup(MPoolFixed_MinSize, MEM_SIZE)];
    };
    }  // namespace Inner_
```

MPoolFixedに限らずメモリアロケータが返すメモリは、
どのようなアライメントにも対応できなければならないため、このようにする必要がある。

MPoolFixed::alloc/MPoolFixed::freeを見ればわかる通り、malloc/freeの実装に比べ格段にシンプルであり、
これによりリアルタイム性の保障は容易である。

なお、この実装ではmalloc/freeと同様に下記のSpinLockを使用したが、
このロックは、ラウンドロビンでスケジューリングされるスレッドの競合を防ぐためのものであり、
固定プライオリティでのスケジューリングが前提となるような組み込みソフトで使用した場合、
デッドロックを引き起こす可能性がある。
組み込みソフトでは、割り込みディセーブル/イネーブルを使ってロックすることを推奨する。

```cpp
    //  example/dynamic_memory_allocation/spin_lock.h 3

    #include <atomic>

    class SpinLock {
    public:
        void lock() noexcept
        {
            while (state_.exchange(state::locked, std::memory_order_acquire) == state::locked) {
                ;  // busy wait
            }
        }

        void unlock() noexcept { state_.store(state::unlocked, std::memory_order_release); }

    private:
        enum class state { locked, unlocked };
        std::atomic<state> state_{state::unlocked};
    };
```

MPoolFixedの単体テストは、下記のようになる。

```cpp
    //  example/dynamic_memory_allocation/mpool_fixed_ut.cpp 10

    Inner_::mem_chunk<5> mc5[3];
    static_assert(32 == sizeof(mc5[0]));
    static_assert(96 == sizeof(mc5));

    auto mc33 = Inner_::mem_chunk<33>{};
    static_assert(64 == sizeof(mc33));
```
```cpp
    //  example/dynamic_memory_allocation/mpool_fixed_ut.cpp 106

    auto mpf = MPoolFixed<33, 2>{};

    ASSERT_EQ(64, mpf.GetSize());
    ASSERT_EQ(2, mpf.GetCount());
    ASSERT_EQ(2, mpf.GetCountMin());
    ASSERT_FALSE(mpf.IsValid(&mpf));  // mpfの管理外のアドレス

    auto m0 = mpf.Alloc(1);
    ASSERT_TRUE(mpf.IsValid(m0));  // mpfの管理のアドレス
    ASSERT_NE(nullptr, m0);
    ASSERT_EQ(1, mpf.GetCount());
    ASSERT_EQ(1, mpf.GetCountMin());

    auto m1 = mpf.Alloc(1);
    ASSERT_TRUE(mpf.IsValid(m1));  // mpfの管理のアドレス
    ASSERT_NE(nullptr, m1);
    ASSERT_EQ(0, mpf.GetCount());
    ASSERT_EQ(0, mpf.GetCountMin());

    // mpfが空の場合のテスト
    ASSERT_THROW(mpf.Alloc(1), MPoolBadAlloc);  // MPoolBadAlloc例外が発生するはず
    auto m2 = mpf.AllocNoExcept(1);
    ASSERT_EQ(nullptr, m2);
    ASSERT_EQ(0, mpf.GetCount());

    mpf.Free(m0);
    ASSERT_EQ(1, mpf.GetCount());
    ASSERT_EQ(0, mpf.GetCountMin());

    mpf.Free(m1);
    ASSERT_EQ(2, mpf.GetCount());
    ASSERT_EQ(0, mpf.GetCountMin());

    ASSERT_THROW(mpf.Alloc(65), MPoolBadAlloc);  // MPoolBadAlloc例外が発生するはず
```

上記テストで使用したMPoolBadAllocは下記のように定義されたクラスであり
(「[ファイル位置を静的に保持したエクセプションクラスの開発](template_meta_programming.md#SS_13_7_6_4)」参照)、

```cpp
    //  example/h/nstd_exception.h 11

    /// @class Exception
    /// @brief StaticString<>を使ったエクセプションクラス
    ///        下記のMAKE_EXCEPTIONを使い生成
    /// @tparam E   std::exceptionから派生したエクセプションクラス
    /// @tparam N   StaticString<N>
    template <typename E, size_t N>
    #if __cplusplus >= 202002L  // c++20
    requires std::derived_from<E, std::exception>
    #endif
    class Exception : public E {
    public:
        static_assert(std::is_base_of_v<std::exception, E>);

        Exception(StaticString<N> const& what_str) noexcept : what_str_{what_str} {}
        char const* what() const noexcept override { return what_str_.String(); }

    private:
        StaticString<N> const what_str_;
    };

    #define MAKE_EXCEPTION(E__, msg__) Nstd::MakeException<E__, __LINE__>(__FILE__, msg__)
```
```cpp
    //  example/dynamic_memory_allocation/mpool.h 7

    class MPoolBadAlloc : public std::bad_alloc {  // Nstd::Exceptionの基底クラス
    };
```

MPoolから派生したクラスが、

* メモリブロックを保持していない状態でのMPool::alloc(size, true)の呼び出し
* MEM_SIZEを超えたsizeでのMPool::alloc(size, true)の呼び出し

のような処理の継続ができない場合に用いるエクセプション用クラスである。


### グローバルnew/deleteのオーバーロードの実装 <a id="SS_14_2_2"></a>
[固定長メモリプール](dynamic_memory_allocation.md#SS_14_2_1)を使用したoperator newのオーバーロードの実装例を以下に示す。

```cpp
    //  example/dynamic_memory_allocation/global_new_delete.cpp 31

    namespace {
    MPool* mpool_table[32];

    // mainの前に呼ばれるため、mpool_tableを初期化するには下記のような方法が必要
    bool is_setup{false};

    void setup() noexcept
    {
        is_setup = true;

        mpool_table[0] = gen_mpool<1, 128>();  //   32
        mpool_table[1] = gen_mpool<2, 128>();  //   64
        mpool_table[2] = gen_mpool<3, 128>();  //   96

        // ...

        mpool_table[29] = gen_mpool<30, 128>();  //  960
        mpool_table[30] = gen_mpool<31, 128>();  //  992
        mpool_table[31] = gen_mpool<32, 128>();  // 1024
    }

    size_t size2index(size_t v) noexcept { return (((v + (min_unit - 1)) & ~(min_unit - 1)) / min_unit) - 1; }
    }  // namespace

    [[nodiscard]] void* operator new(std::size_t size)
    {
        if (!is_setup) {
            setup();
        }

        for (auto i = size2index(size); i < ArrayLength(mpool_table); ++i) {
            void* mem = mpool_table[i]->AllocNoExcept(size);
            if (mem != nullptr) {
                return mem;
            }
        }

        throw std::bad_alloc{};

        static char fake[0];

        return fake;
    }
```

上記で定義されたoperator newは、

* 32の整数倍のサイズを持つ32個のメモリプールを持つ
* 各メモリープールは128個のメモリブロックを持つ
* メモリブロックの最大長は1024バイト

のような仕様を持つため、実際に使う場合は、メモリのサイズや個数の調整が必要だろうが、
後で詳しく見るようにリアルタイム性の阻害となるようなコードはないため、
リアルタイム性が必要なソフトウェアでも使用可能である。

静的オブジェクトを含まないアプリケーションでは、
上記のコードのsetupで行っているmpool_tableの初期化は
[一様初期化](term_explanation.md#SS_19_5_2)で行った方が良いが、
例で用いたアプリケーションにはnewを行う静的オブジェクトが存在するため
(google testは静的オブジェクトを利用する)、
setupで行っているような方法以外では、
最初のoperator newの呼び出しより前にmpool_tableの初期化をすることはできない。

mpool_tableはMPoolポインタを保持するが、そのポインタが指すオブジェクトの実態は、
gen_mpool<>が生成したMPoolFixed<>オブジェクトである。
gen_mpool<>については、「[プレースメントnew](dynamic_memory_allocation.md#SS_14_2_3)」で説明する。

size2indexは、要求されたサイズから、
それに対応するMPoolポインタを保持するmpool_tableのインデックスを導出する関数である。

この実装では対応するMPoolが空であった場合、
それよりも大きいメモリブロックを持つMPoolからメモリを返す仕様としたが、
その時点でアサーションフェールさせ
(つまり、対応するMPoolが空である状態でのAllocの呼び出しをバグとして扱う)、
MEM_COUNTの値を見直した方が、
より少ないメモリで動作する組み込みソフトを作りやすいだろう。

operator deleteについては、下記の2種類が必要となる。

```cpp
    //  example/dynamic_memory_allocation/global_new_delete.cpp 106

    void operator delete(void* mem) noexcept
    {
        for (MPool* mp : mpool_table) {
            if (mp->IsValid(mem)) {
                mp->Free(mem);
                return;
            }
        }
        assert(false);
    }

    void operator delete(void* mem, std::size_t size) noexcept
    {
        for (auto i = size2index(size); i < ArrayLength(mpool_table); ++i) {
            if (mpool_table[i]->IsValid(mem)) {
                mpool_table[i]->Free(mem);
                return;
            }
        }
        assert(false);
    }
```

operator delete(void\* mem, std::size_t size)は、完全型のオブジェクトのメモリ解放に使用され、
operator delete(void\* mem)は、それ以外のメモリ解放に使用される。

コードから明らかな通り、size付きのoperator deleteの方がループの回転数が少なくなるため、
高速に動作するが、malloc/freeの実装(「[malloc/freeの問題点](dynamic_memory_allocation.md#SS_14_1)」参照)で使用したHeader_t
を導入することでこの実行コストはほとんど排除できる。
そのトレードオフとしてメモリコストが増えるため、ここでは例示した仕様にした。


### プレースメントnew <a id="SS_14_2_3"></a>
「[グローバルnew/deleteのオーバーロードの実装](dynamic_memory_allocation.md#SS_14_2_2)」で使用したgen_mpool<>は、
下記のように定義されている。

```cpp
    //  example/dynamic_memory_allocation/global_new_delete.cpp 8

    namespace {

    constexpr size_t min_unit{MPoolFixed_MinSize};

    template <uint32_t N_UNITS, uint32_t MEM_COUNT>
    [[nodiscard]] MPool* gen_mpool() noexcept
    {
        using mp_t = MPoolFixed<min_unit * N_UNITS, MEM_COUNT>;

        static union {
            std::max_align_t max_align;
            uint8_t          mem[sizeof(mp_t)];
        } mem;

        static_assert(static_cast<void*>(&mem.max_align) == static_cast<void*>(mem.mem));
        static_assert(sizeof(mem) >= sizeof(mp_t));

        return new (mem.mem) mp_t;  // プレースメントnew
    }
    }  // namespace
```

この関数テンプレートは、MPoolFixed<>オブジェクトを生成し、それをMPool型のポインタとして返す。
MPoolFixedの生成は、上記で示したようにプレースメントnewを使用して行っている。

gen_mpool<>内でMPoolFixedのstaticなインスタンスを定義した方がシンプルに実装できるが、
その場合、main()終了後、そのインスタンスは解放され(デストラクタが呼び出され)、その後、
他の静的オブジェクトの解放が行われると、その延長でoperator deleteが呼び出され、
ライフタイム終了後のMPoolFixedのstaticなインスタンスが使われてしまう。

現在のMPoolFixedの実装ではこの操作で不具合は発生しないが、
解放済のオブジェクトを操作することは避けるべきであるため、
MPoolFixedの生成にプレースメントnewを用いている。

プレースメントnewで生成したオブジェクトをdeleteすることはできず、
デストラクタはユーザが明示的に呼び出さない限り、呼び出されない。
ここでは、プレースメントnewのこの特性を利用したが、
逆に、この特性があるため、
ここでの実装のような特殊な事情がある場合を除き、プレースメントnewを使うべきではない
(デストラクタの明示的な呼び出しを忘れるとリソースリークしてしまう)。


### デバッグ用イテレータ <a id="SS_14_2_4"></a>
この章で例示したグローバルnew/deleteは、すでに述べたように適切なメモリの量を調整する必要がある。
そのためには、これを使用するアプリケーションをある程度動作させた後、
グローバルnew/deleteのメモリの消費量を計測しなければならない。

下記のコードは、そのためのインターフェースを提供する。

```cpp
    //  example/dynamic_memory_allocation/global_new_delete.h 4

    class GlobalNewDeleteMonitor {
    public:
        MPool const* const* cbegin() const noexcept;
        MPool const* const* cend() const noexcept;
        MPool const* const* begin() const noexcept;
        MPool const* const* end() const noexcept;
    };
```
```cpp
    //  example/dynamic_memory_allocation/global_new_delete.cpp 132

    MPool const* const* GlobalNewDeleteMonitor::begin() const noexcept { return &mpool_table[0]; }
    MPool const* const* GlobalNewDeleteMonitor::end() const noexcept { return &mpool_table[ArrayLength(mpool_table)]; }

    MPool const* const* GlobalNewDeleteMonitor::cbegin() const noexcept { return begin(); }
    MPool const* const* GlobalNewDeleteMonitor::cend() const noexcept { return end(); }
```

このインターフェースを下記のように使用することで、

```cpp
    //  example/dynamic_memory_allocation/global_new_delete_ut.cpp 119

    auto gm = GlobalNewDeleteMonitor{};

    std::cout << "  size current   min" << std::endl;
    std::cout << "  ------------------" << std::endl;

    for (MPool const* mp : gm) {
        std::cout << std::setw(6) << mp->GetSize() << std::setw(8) << mp->GetCount() << std::setw(6)
                  << mp->GetCountMin() << std::endl;
    }
```

下記のようにメモリの現在の状態や使用履歴を見ることができる。

```
          size current   min
          ------------------
            32      90     0
            64      78    74
            96     127   125

           ...

           992     128   128
          1024     128     0
```

実際の組み込みソフトの開発では、
デバッグ用入出力機能からこのようなコードを実行できるようにすることで、
グローバルnew/deleteが使用するそれぞれのMPoolFixedインスタンスのメモリの調整ができるだろう。


## クラスnew/deleteのオーバーロード <a id="SS_14_3"></a>
「[グローバルnew/deleteのオーバーロードの実装](dynamic_memory_allocation.md#SS_14_2_2)」で示したコードのロックを、
「割り込みディセーブル/イネーブル」に置き換えることで、リアルタイム性を保障することができるが、
この機構はある程度多くのメモリを必要とするため、
極めてメモリ制限の厳しいシステムでは使用が困難である場合もあるだろう。

そのような場合、非スタック上でのオブジェクト生成には、

* 限定的なクラスのみ、newによる動的な方法を用いる
* その他のクラスに対しては、[Singleton](design_pattern.md#SS_9_13)や[Named Constructor](design_pattern.md#SS_9_18)と同様な静的な方法を用いる

とし、グローバルnewを使用しないことが、より良いメモリ使用方法となり得る。

グローバルnewを使わずに動的にオブジェクトを生成するためには、

* プレースメントnewを使う
* クラス毎にnew/deleteをオーバーロードする

という2つの選択肢が考えられるが、すでに述べた理由によりプレースメントnewの使用は避けるべきである。
従って、その方法はクラス毎のnew/deleteのオーバーロードになる。

メモリ管理に「[固定長メモリプール](dynamic_memory_allocation.md#SS_14_2_1)」で示したMPoolFixedを利用した実装例を以下に示す。

```cpp
    //  example/dynamic_memory_allocation/class_new_delete_ut.cpp 14

    struct A {
        A() noexcept : name0{"A"} {}
        char const* name0;

        [[nodiscard]] static void* operator new(size_t size);
        static void                operator delete(void* mem) noexcept;
        static void                operator delete(void* mem, std::size_t size) noexcept;

        [[nodiscard]] static void* operator new[](size_t size)                             = delete;
        static void                operator delete[](void* mem) noexcept                   = delete;
        static void                operator delete[](void* mem, std::size_t size) noexcept = delete;
    };

    MPoolFixed<sizeof(A), 3> mpf_A;

    void* A::operator new(size_t size) { return mpf_A.Alloc(size); }
    void A::operator delete(void* mem) noexcept { mpf_A.Free(mem); }
    void A::operator delete(void* mem, std::size_t) noexcept { mpf_A.Free(mem); }
```

以下の単体テストが示す通り、
静的に定義したMPoolFixedインスタンスがオーバーロードしたnew/deleteから使われていることがわかる
(従ってグローバルnew/deleteは使われていないこともわかる)。

```cpp
    //  example/dynamic_memory_allocation/class_new_delete_ut.cpp 43

    ASSERT_EQ(3, mpf_A.GetCount());

    {
        auto a = std::make_unique<A>();
        ASSERT_STREQ("A", a->name0);
        ASSERT_EQ(2, mpf_A.GetCount());
    }
    ASSERT_EQ(3, mpf_A.GetCount());

    {
        auto a = std::make_unique<A>();
        ASSERT_STREQ("A", a->name0);
        ASSERT_EQ(2, mpf_A.GetCount());

        auto b = std::make_unique<A>();
        ASSERT_STREQ("A", b->name0);
        ASSERT_EQ(1, mpf_A.GetCount());

        auto c = std::make_unique<A>();
        ASSERT_STREQ("A", c->name0);
        ASSERT_EQ(0, mpf_A.GetCount());

        ASSERT_THROW(std::make_unique<A>(), MPoolBadAlloc);
    }
    ASSERT_EQ(3, mpf_A.GetCount());
```

しかし、この方法ではnewのオーバーロードを行うクラス毎に、

```cpp
    //  example/dynamic_memory_allocation/class_new_delete_ut.cpp 20

    [[nodiscard]] static void* operator new(size_t size);
    static void                operator delete(void* mem) noexcept;
    static void                operator delete(void* mem, std::size_t size) noexcept;

    [[nodiscard]] static void* operator new[](size_t size)                             = delete;
    static void                operator delete[](void* mem) noexcept                   = delete;
    static void                operator delete[](void* mem, std::size_t size) noexcept = delete;
```

を記述しなければならず、コードクローンの温床となってしまう。
これを避けるためには、
[CRTP(curiously recurring template pattern)](design_pattern.md#SS_9_22)
を利用した下記のようなクラステンプレートを導入すれば良い。

```cpp
    //  example/dynamic_memory_allocation/op_new.h 5

    template <typename T>
    class OpNew {
    public:
        [[nodiscard]] static void* operator new(size_t size) { return mpool_.Alloc(size); }
        static void                operator delete(void* mem) noexcept { mpool_.Free(mem); }
        static void                operator delete(void* mem, std::size_t) noexcept { mpool_.Free(mem); }

        [[nodiscard]] static void* operator new[](size_t size)                             = delete;
        static void                operator delete[](void* mem) noexcept                   = delete;
        static void                operator delete[](void* mem, std::size_t size) noexcept = delete;

    private:
        static MPool& mpool_;
    };
```

このOpeNewを使用した「new/deleteのオーバーロードを持つ基底クラスとその一連の派生クラス」
の実装例を以下に示す。

```cpp
    //  example/dynamic_memory_allocation/class_new_delete_ut.cpp 77

    struct A : public OpNew<A> {
        A() noexcept : name0{"A"} {}
        char const* name0;
    };

    struct B : A {
        B() noexcept : name1{"B"} {}
        char const* name1;
    };

    struct C : A {
        C() noexcept : name1{"C"} {}
        char const* name1;
    };

    struct D : C {
        D() noexcept : name2{"D"} {}
        char const* name2;
    };

    MPoolFixed<MaxSizeof<A, B, C, D>(), 10> mpf_ABCD;

    template <>
    MPool& OpNew<A>::mpool_ = mpf_ABCD;
```

OpNewをクラステンプレートとし、内部で利用しないテンプレートパラメータを宣言した理由は、
別のクラスからはOpNewの別インスタンスを使用できるようにするためである。

この方法は、コードが若干複雑にることを除けば、
「[グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_2)」に比べ、優れているように見えてしまうかもしれないが、
下記のように、さらに派生クラスを定義してしまうとnewが失敗してしまうことがあるので注意が必要である。

```cpp
    //  example/dynamic_memory_allocation/class_new_delete_ut.cpp 135

    struct Large : A {
        uint8_t buff[1024];  // mpf_ABCDのメモリブロックのサイズを超える
    };

    TEST(NewDelete_Opt, class_new_delete_fixed_derived_large)
    {
        ASSERT_EQ(10, mpf_ABCD.GetCount());
        ASSERT_THROW(auto large = std::make_unique<Large>(), MPoolBadAlloc);  // サイズが大きすぎる
    }
```

なお、 下記のようなクラスをnew/deleteをオーバーロードしないすべのクラスの基底クラスとすることで、
偶発的にグローバルnewを使ってしまわないようにすることもできる。

```cpp
    //  example/dynamic_memory_allocation/op_new_deleted.h 3

    class OpNewDeleted {
        static void* operator new(size_t size)                             = delete;
        static void  operator delete(void* mem) noexcept                   = delete;
        static void  operator delete(void* mem, std::size_t size) noexcept = delete;
    };
```
```cpp
    //  example/dynamic_memory_allocation/class_new_delete_ut.cpp 150

    class DeletedNew : OpNewDeleted {  // プライベート継承
    };

    class DelivedDeletedNew : DeletedNew {  // プライベート継承
    };

    // DeletedNew* ptr0 { new DeletedNew };                // OpNewDeletedの効果でコンパイルエラー
    // DelivedDeletedNew* ptr1 { new DelivedDeletedNew };  // 同上
```

この記述方法は、コードインスペクションの省力化にも繋がるため、
OpNewを使うプロジェクトには導入するべきだろう。


## STLコンテナのアロケーター <a id="SS_14_4"></a>
ここまで前提として来たような組み込みソフトにおいても、
その大部分のコードにリアルタイム性は不要であり、このような部分のコードにSTLコンテナが使用できれば、

* 開発効率が向上する
* 開発コード量が少なくなる

等のポジティブな影響を期待できることは多い。
STLコンテナはこういった状況に備えて、ユーザ定義のアロケータを使用できるように定義されている。
ここでは、アロケータの定義例や、その使い方を示す。

### STLコンテナ用アロケータ <a id="SS_14_4_1"></a>
アロケータの定義例を以下に示す。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator.h 7

    template <typename T>
    class MPoolBasedAllocator {
    public:
        using pointer                                = T*;
        using const_pointer                          = T const*;
        using value_type                             = T;
        using propagate_on_container_move_assignment = std::true_type;
        using is_always_equal                        = std::true_type;
        using size_type                              = size_t;
        using difference_type                        = size_t;

        template <class U>
        struct rebind {
            using other = MPoolBasedAllocator<U>;
        };

        T*   allocate(size_type count) { return static_cast<pointer>(mpool_.Alloc(count * sizeof(T))); }
        void deallocate(T* mem, size_type) noexcept { mpool_.Free(mem); }

    private:
        static MPool& mpool_;
    };

    template <class T>  // T型のMPoolBasedAllocatorはシステムに唯一
    bool operator==(MPoolBasedAllocator<T> const&, MPoolBasedAllocator<T> const&) noexcept
    {
        return true;
    }

    template <class T, class U>
    bool operator==(MPoolBasedAllocator<T> const&, MPoolBasedAllocator<U> const&) noexcept
    {
        return false;
    }

    template <class T, class U>
    bool operator!=(MPoolBasedAllocator<T> const& lhs, MPoolBasedAllocator<U> const& rhs) noexcept
    {
        return !(lhs == rhs);
    }
```

アロケータのパブリックなメンバやoperator ==、operator !=は、STLに従い定義している
([STL allocator](https://cpprefjp.github.io/reference/memory/allocator.html)参照)。

上記コードからわかるようにメモリの実際のアロケーションには、
これまでと同様にMPoolから派生したクラスを使用するが、
リアルタイム性は不要であるためメモリ効率が悪いMPoolFixedは使わない。
代わりに、可変長メモリを扱うためメモリ効率がよいMPoolVariabl
(「[可変長メモリプール](dynamic_memory_allocation.md#SS_14_4_2)」参照)を使う。

### 可変長メモリプール <a id="SS_14_4_2"></a>
可変長メモリプールを生成するMPoolVariableの実装は下記のようになる
(全体は巻末の「[example/dynamic_memory_allocation/mpool_variable.h](sample_code.md#SS_24_2_36)」に掲載する)。

```cpp
    //  example/dynamic_memory_allocation/mpool_variable.h 59

    template <uint32_t MEM_SIZE>
    class MPoolVariable final : public MPool {
    public:
        MPoolVariable() noexcept : MPool{MEM_SIZE}
        {
            header_->next    = nullptr;
            header_->n_nuits = sizeof(buff_) / Inner_::unit_size;
        }

        // 中略
        ...

    private:
        using header_t = Inner_::header_t;

        Inner_::buffer_t<MEM_SIZE> buff_{};
        header_t*                  header_{reinterpret_cast<header_t*>(buff_.buffer)};
        mutable SpinLock           spin_lock_{};
        size_t                     unit_count_{sizeof(buff_) / Inner_::unit_size};
        size_t                     unit_count_min_{sizeof(buff_) / Inner_::unit_size};

        virtual void* alloc(size_t size) noexcept override
        {
            // ...
        }

        virtual void free(void* mem) noexcept override
        {
            // ...
        }

        virtual size_t get_size() const noexcept override { return 1; }
        virtual size_t get_count() const noexcept override { return unit_count_ * Inner_::unit_size; }
        virtual size_t get_count_min() const noexcept override { return unit_count_min_ * Inner_::unit_size; }

        virtual bool is_valid(void const* mem) const noexcept override
        {
            return (&buff_ < mem) && (mem < &buff_.buffer[ArrayLength(buff_.buffer)]);
        }
    };
```

下記のようにMPoolVariable、
MPoolBasedAllocatorを使うことでnew char[]に対応するアロケータが定義できる。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 11

    namespace {
    MPoolVariable<1024 * 64> mpv_allocator;
    }

    template <>
    MPool& MPoolBasedAllocator<char>::mpool_ = mpv_allocator;
```

下記の単体テストは、このアロケータを使うstd::stringオブジェクトの宣言方法と、
その振る舞いを示している。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 24

    auto rest = mpv_allocator.GetCount();
    auto str  = std::basic_string<char, std::char_traits<char>, MPoolBasedAllocator<char>>{"hehe"};

    ASSERT_TRUE(mpv_allocator.IsValid(str.c_str()));  // mpv_allocatorを使用してメモリ確保
    ASSERT_GT(rest, mpv_allocator.GetCount());        // mpv_allocatorのメモリが減っていることの確認
```

この長い宣言は、下記のようにすることで簡潔に記述できるようになる。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 34

    using mpv_string = std::basic_string<char, std::char_traits<char>, MPoolBasedAllocator<char>>;
```

下記のように宣言、定義することで、

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 50

    template <>
    MPool& MPoolBasedAllocator<int>::mpool_ = mpv_allocator;

    using mpv_vector_int = std::vector<int, MPoolBasedAllocator<int>>;
```

下記の単体テストが示す通り、std::vector\<int>にこのアロケータを使わせることもできる。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 61

    auto rest = mpv_allocator.GetCount();
    auto ints = mpv_vector_int{1, 2, 3};

    ASSERT_TRUE(mpv_allocator.IsValid(&ints[0]));  // mpv_allocatorのメモリであることの確認
    ASSERT_GT(rest, mpv_allocator.GetCount());     // mpv_allocatorのメモリが減っていることの確認
```

これまでの手法を組み合わせ下記のようにすることで、
std::stringと同等のオブジェクトを保持するstd::vectorを宣言することもできる。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 72

    using mpv_vector_str = std::vector<mpv_string, MPoolBasedAllocator<mpv_string>>;

    template <>
    MPool& MPoolBasedAllocator<mpv_string>::mpool_ = mpv_allocator;
```
```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 94

    auto strs = mpv_vector_str{"1", "2", "3"};

    ASSERT_GT(rest, mpv_allocator.GetCount());

    for (auto const& s : strs) {
        ASSERT_TRUE(mpv_allocator.IsValid(&s));         // mpv_allocatorのメモリであることの確認
        ASSERT_TRUE(mpv_allocator.IsValid(s.c_str()));  // mpv_allocatorのメモリであることの確認
    }
```

しかし、下記に示すように、これまでの定義、
宣言のみではmpv_stringのnewにこのアロケータを使わせることはできない。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 121

    auto rest = mpv_allocator.GetCount();

    auto str0 = std::make_unique<mpv_string>();  // グローバルnewが使われる

    // mpv_stringのnewにはmpv_allocatorは使われない
    ASSERT_FALSE(mpv_allocator.IsValid(str0.get()));
    ASSERT_EQ(rest, mpv_allocator.GetCount());
```

そうするためには、さらに下記のような定義が必要になる。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 108

    struct mpv_string_op_new : OpNew<mpv_string_op_new>, mpv_string {
        using mpv_string::basic_string;
    };

    template <>
    MPool& OpNew<mpv_string_op_new>::mpool_ = mpv_allocator;
```

このようにすることで、下記に示すように期待した動きになる。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 133

    rest = mpv_allocator.GetCount();

    auto str1 = std::make_unique<mpv_string_op_new>();

    // mpv_string_op_newのnewにmpv_allocatorが使われる
    ASSERT_TRUE(mpv_allocator.IsValid(str1.get()));
    ASSERT_GT(rest, mpv_allocator.GetCount());
```

ただし、std::make_sharedを使用した場合、この関数のメモリアロケーションの最適化により、
下記に示すように期待した結果にならないため、注意が必要である。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 145

    rest = mpv_allocator.GetCount();

    auto str2 = std::make_shared<mpv_string_op_new>();

    // mpv_string_op_newのnewにmpv_allocatorが使われない!!!
    ASSERT_FALSE(mpv_allocator.IsValid(str2.get()));
    ASSERT_EQ(rest, mpv_allocator.GetCount());
```

newをオーバーロードしたクラスをstd::shared_ptrで管理する場合、下記のようにしなければならない。

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 157

    rest = mpv_allocator.GetCount();

    auto str3 = std::shared_ptr<mpv_string_op_new>{new mpv_string_op_new};

    // mpv_string_op_newのnewにmpv_allocatorが使われる
    ASSERT_TRUE(mpv_allocator.IsValid(str3.get()));
    ASSERT_GT(rest, mpv_allocator.GetCount());
```

### デバッグ用イテレータ <a id="SS_14_4_3"></a>
[可変長メモリプール](dynamic_memory_allocation.md#SS_14_4_2)を使用すると、
メモリのフラグメントによりアロケーションが失敗することがあり得る。
このような事態が発生している可能性がある場合、
アロケータが保持しているメモリの状態を表示させることがデバッグの第一歩となる。

下記のコードは、そのためのインターフェースを提供する。


```cpp
    //  example/dynamic_memory_allocation/mpool_variable.h 59

    template <uint32_t MEM_SIZE>
    class MPoolVariable final : public MPool {
    public:

        // 中略
        ...

        class const_iterator {
        public:
            explicit const_iterator(Inner_::header_t const* header) noexcept : header_{header} {}
            const_iterator(const_iterator const&) = default;
            const_iterator(const_iterator&&)      = default;

            const_iterator& operator++() noexcept  // 前置++のみ実装
            {
                assert(header_ != nullptr);
                header_ = header_->next;

                return *this;
            }

            Inner_::header_t const* operator*() noexcept { return header_; }


        #if __cplusplus <= 201703L  // c++17
            bool operator==(const_iterator const& rhs) noexcept { return header_ == rhs.header_; }
            bool operator!=(const_iterator const& rhs) noexcept { return !(*this == rhs); }
        #else  // c++20

            auto operator<=>(const const_iterator&) const = default;
        #endif

        private:
            Inner_::header_t const* header_;
        };

        const_iterator begin() const noexcept { return const_iterator{header_}; }
        const_iterator end() const noexcept { return const_iterator{nullptr}; }
        const_iterator cbegin() const noexcept { return const_iterator{header_}; }
        const_iterator cend() const noexcept { return const_iterator{nullptr}; }

        // 中略
        ...
    };
```

このインターフェースを下記のように使用することで、

```cpp
    //  example/dynamic_memory_allocation/mpool_allocator_ut.cpp 213

    for (auto mem : mpv_allocator) {
        std::cout << std::setw(16) << mem->next << ":" << mem->n_nuits << std::endl;
    }
```

下記のようにmpv_allocator.header\_が保持するメモリの現在の状態を見ることができる
(これによるとmpv_allocatorが保持するメモリの先頭付近では多少フラグメントを起こしているが、
最後に大きなメモリブロックがあるため、全体としては問題ないレベルである)。

```
        0x7f073afe59d0:3
        0x7f073afe5a60:3
        0x7f073afe5ac0:3
        0x7f073afe5b70:3
        0x7f073afe5c50:11
        0x7f073afe5cb0:3
        0x7f073afe5e50:13
                     0:4018
```

「[グローバルnew/deleteのオーバーロードの実装](dynamic_memory_allocation.md#SS_14_2_2)」でも述べたように、
デバッグ用入出力機能からこのような出力を得られるようにしておくべきである。


### エクセプション処理機構の変更 <a id="SS_14_4_4"></a>
多くのコンパイラのエクセプション処理機構にはnew/deleteやmalloc/freeが使われているため、
リアルタイム性が必要な個所でエクセプション処理を行ってはならない。
そういった規制でプログラミングを行っていると、
リアルタイム性が不要な処理であるため使用しているSTLコンテナにすら、
既存のエクセプション処理機構を使わせたく無くなるものである。

コンパイラに[g++](term_explanation.md#SS_19_20_1)や[clang++](term_explanation.md#SS_19_20_2)を使っている場合、
下記関数を置き換えることでそういった要望を叶えることができる。

|関数                                           |機能                            |
|-----------------------------------------------|--------------------------------|
|`__cxa_allocate_exception(size_t thrown_size)` |エクセプション処理用のメモリ確保|
|`__cxa_free_exception(void\* thrown_exception)`|上記で確保したメモリの解放      |

オープンソースである[static exception](https://github.com/ApexAI/static_exception)を使うことで、
上記2関数を置き換えることもできるが、この実装が複雑すぎると思うのであれば、
下記に示すような、これまで使用したMPoolFixedによる単純な実装を使うこともできる。

```cpp
    //  example/dynamic_memory_allocation/exception_allocator_ut.cpp 15

    // https://github.com/hjl-tools/gcc/blob/master/libstdc%2B%2B-v3/libsupc%2B%2B/unwind-cxx.h
    // の抜粋
    namespace __cxxabiv1 {
    struct __cxa_exception {
        // ...
    };
    SUPPRESS_WARN_END;
    }  // namespace __cxxabiv1

    namespace {

    constexpr size_t             offset{sizeof(__cxxabiv1::__cxa_exception)};
    MPoolFixed<offset + 128, 50> mpf_exception;
    }  // namespace

    extern "C" {

    void* __cxa_allocate_exception(size_t thrown_size)
    {
        auto alloc_size = thrown_size + offset;  // メモリの実際の必要量はthrown_size+offset
        auto mem        = mpf_exception.AllocNoExcept(alloc_size);

        assert(mem != nullptr);

        memset(mem, 0, alloc_size);
        auto* ret = static_cast<uint8_t*>(mem);

        ret += offset;

        return ret;
    }

    void __cxa_free_exception(void* thrown_exception)
    {
        auto* ret = static_cast<uint8_t*>(thrown_exception);

        ret -= offset;
        mpf_exception.Free(ret);
    }
```

以下に単体テストを示す。

```cpp
    //  example/dynamic_memory_allocation/exception_allocator_ut.cpp 104

    auto count             = mpf_exception.GetCount();
    auto exception_occured = false;

    try {
        throw std::exception{};
    }
    catch (std::exception const& e) {
        ASSERT_EQ(count - 1, mpf_exception.GetCount());  // 1個消費
        exception_occured = true;
    }

    ASSERT_TRUE(exception_occured);
    ASSERT_EQ(count, mpf_exception.GetCount());  // 1個解放
```

すでに述べたが、残念なことに、この方法はC++の標準外であるため、
これを適用できるコンパイラは限られている。
しかし、多くのコンパイラはこれと同様の拡張方法を備えているため、
安易にエクセプションやSTLコンテナを使用禁止することなく、安全に使用する方法を探るべきだろう。

## Polymorphic Memory Resource(pmr) <a id="SS_14_5"></a>
Polymorphic Memory Resource(pmr)は、
動的メモリ管理の柔軟性と効率性を向上させるための、C++17から導入された仕組みである。

C++17で導入されたstd::pmr名前空間は、カスタマイズ可能なメモリ管理を提供し、
特にSTLコンテナと連携して効率化を図るための統一フレームワークを提供する。
std::pmrは、
カスタマイズ可能なメモリ管理を標準ライブラリのデータ構造に統合するための統一的なフレームワークであり、
特にSTLコンテナと連携して、動的メモリ管理を効率化することができる。

std::pmrは以下のようなメモリ管理のカスタマイズを可能にする。

* メモリアロケータをポリモーフィック(動的に選択可能)にする。
* メモリ管理ポリシーをstd::pmr::memory_resourceで定義する。
* メモリリソースを再利用して効率的な動的メモリ管理を実現する。

std::pmrの主要なコンポーネントは以下の通りである。

* [std::pmr::memory_resource](dynamic_memory_allocation.md#SS_14_5_1)  
* [std::pmr::polymorphic_allocator](dynamic_memory_allocation.md#SS_14_5_2)  
* [pool_resource](dynamic_memory_allocation.md#SS_14_5_3)

### std::pmr::memory_resource <a id="SS_14_5_1"></a>
std::pmr::memory_resourceは、
ユーザー定義のメモリリソースをカスタマイズし、
[std::pmr::polymorphic_allocator](dynamic_memory_allocation.md#SS_14_5_2)を通じて利用可能にする[インターフェースクラス](term_explanation.md#SS_19_3_13)である。

[可変長メモリプール](dynamic_memory_allocation.md#SS_14_4_2)の実装で示したコードとほぼ同様の、
std::pmr::memory_resourceから派生した具象クラスの実装を以下に示す。

```cpp
    //  example/dynamic_memory_allocation/pmr_memory_resource_ut.cpp 64

    template <uint32_t MEM_SIZE>
    class memory_resource_variable final : public std::pmr::memory_resource {
    public:
        memory_resource_variable() noexcept
        {
            header_->next    = nullptr;
            header_->n_nuits = sizeof(buff_) / Inner_::unit_size;
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
            // MPoolVariable::allocとほぼ同じ
            // ...
        }

        void do_deallocate(void* mem, size_t, size_t) noexcept override
        {
            // MPoolVariable::freeとほぼ同じ
            // ...
        }

        bool do_is_equal(const memory_resource& other) const noexcept override { return this == &other; }
    };
```

### std::pmr::polymorphic_allocator <a id="SS_14_5_2"></a>
std::pmr::polymorphic_allocatorはC++17で導入された標準ライブラリのクラスで、
C++のメモリリソース管理を抽象化するための機能を提供する。
[std::pmr::memory_resource](dynamic_memory_allocation.md#SS_14_5_1)を基盤とし、
コンテナやアルゴリズムにカスタムメモリアロケーション戦略を容易に適用可能にする。
std::allocatorと異なり、型に依存せず、
ポリモーフィズムを活用してメモリリソースを切り替えられる点が特徴である。

すでに示したmemory_resource_variable([std::pmr::memory_resource](dynamic_memory_allocation.md#SS_14_5_1))の単体テストを以下に示すことにより、
polymorphic_allocatorの使用例とする。

```cpp
    //  example/dynamic_memory_allocation/pmr_memory_resource_ut.cpp 214

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

### pool_resource <a id="SS_14_5_3"></a>
pool_resourceは[std::pmr::memory_resource](dynamic_memory_allocation.md#SS_14_5_1)を基底とする下記の2つの具象クラスである。

* std::pmr::synchronized_pool_resourceは下記のような特徴を持つメモリプールである。
    * 非同期のメモリプールリソース
    * シングルスレッド環境での高速なメモリ割り当てに適する
    * 排他制御のオーバーヘッドがない
    * 以下に使用例を示す。

```cpp
    //  example/dynamic_memory_allocation/pool_resource_ut.cpp 10

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
    //  example/dynamic_memory_allocation/pool_resource_ut.cpp 38

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




