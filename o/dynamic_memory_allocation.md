<!-- deep/md/dynamic_memory_allocation.md -->
# ダイナミックメモリアロケーション <a id="SS_14"></a>
本章で扱うダイナミックメモリアロケーション([ヒープ](cpp_idioms.md#SS_21_9_1)の使用)とは、new/delete、malloc/free
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

__この章の構成__

&emsp;&emsp; [malloc/freeの問題点](dynamic_memory_allocation.md#SS_14_1)  
&emsp;&emsp; [メモリプール](dynamic_memory_allocation.md#SS_14_2)  
&emsp;&emsp;&emsp; [固定長メモリプール](dynamic_memory_allocation.md#SS_14_2_1)  
&emsp;&emsp;&emsp; [可変長メモリプール](dynamic_memory_allocation.md#SS_14_2_2)  

&emsp;&emsp; [メモリプールのエクセプション](dynamic_memory_allocation.md#SS_14_3)  
&emsp;&emsp;&emsp; [MPoolBadAlloc](dynamic_memory_allocation.md#SS_14_3_1)  
&emsp;&emsp;&emsp; [エクセプション処理機構の変更](dynamic_memory_allocation.md#SS_14_3_2)  

&emsp;&emsp; [new/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4)  
&emsp;&emsp;&emsp; [グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_1)  
&emsp;&emsp;&emsp; [デバッグ用イテレータ](dynamic_memory_allocation.md#SS_14_4_2)  
&emsp;&emsp;&emsp; [クラスnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_3)  
&emsp;&emsp;&emsp; [new/deleteのオーバーロードのまとめ](dynamic_memory_allocation.md#SS_14_4_4)  

&emsp;&emsp; [標準ライブラリのコンテナ用アロケータ](dynamic_memory_allocation.md#SS_14_5)  
&emsp;&emsp;&emsp; [デバッグ用イテレータ](dynamic_memory_allocation.md#SS_14_5_1)  
  
  

[インデックス](introduction.md#SS_1_4)に戻る。  

___

## malloc/freeの問題点 <a id="SS_14_1"></a>
UNIX系のOSでの典型的なmalloc/freeの実装例の一部を以下に示す
(この実装は長いため、
全体は巻末の「[example/dynamic_memory_allocation/malloc_ut.cpp](sample_code.md#SS_26_2_35)」に掲載する)。

```cpp
    //  example/dynamic_memory_allocation/malloc_ut.cpp 19

    namespace {

    struct header_t {
        header_t* next;
        size_t    n_units;  // header_tが何個あるか
    };

    header_t*        header{nullptr};
    SpinLock         spin_lock{};
    constexpr size_t unit_size{sizeof(header_t)};

    inline bool sprit(header_t* header, size_t n_units, header_t*& next) noexcept
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
            add->n_units  = add_size / unit_size;
            free(++add);
            mem = malloc_inner(size);
        }

        return mem;
    }
```

上記で示したようにmalloc/freeで使用されるメモリはHeader_t型のheaderで管理され、
このアクセスの競合は[スピンロック](cpp_idioms.md#SS_21_9_5)(SpinLock)によって回避される。
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
        add->n_units  = add_size / unit_size;
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

[フリースタンディング環境](cpp_idioms.md#SS_21_9_7)では、sbrkのようなシステムコールは存在しないため、
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

## メモリプール <a id="SS_14_2"></a>
このドキュメントでは、メモリの確保/解放をサポートするサブシステムをメモリプールと呼ぶ。

[malloc/freeの問題点](dynamic_memory_allocation.md#SS_14_1)の問題を回避するすために２種類のメモリプールの実装を示す。

* リアルタイム性が保証されれた[固定長メモリプール](dynamic_memory_allocation.md#SS_14_2_1)
* フラグメントの状態を確認することができる[可変長メモリプール](dynamic_memory_allocation.md#SS_14_2_2)


### 固定長メモリプール <a id="SS_14_2_1"></a>
malloc/freeにリアルタイム性がない原因は、

* リアルタイム性がないOSのシステムコールを使用している
* メモリを可変長で管理しているため処理が重いにもかかわらず、この処理中にグローバルロックを行う

ためである。従って、この問題に対処するためのメモリ管理システムは、

* 初期に静的なメモリを確保
* メモリを固定長で管理(リスト構造でメモリ管理できないため)

する必要がある。

このメモリプールは管理する固定長のメモリブロックのサイズごとに複数必要になる一方で、
これらを統合的に扱う必要も出てくる。

そのため、固定長のメモリプールは、

* 複数個のメモリプールを統合的に扱う[インターフェースクラス](core_lang_spec.md#SS_19_4_11)MPool
* MPoolを基底クラスとし、固定長メモリブロックを管理するクラステンプレートMPoolFixed

によって実装することにする。

まずは、MPoolを下記に示す。なお、throwするオブジェクトの型は[MPoolBadAlloc](dynamic_memory_allocation.md#SS_14_3_1)を使用している。

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
                mem_head_ = mem_head_->next;
                --mem_count_;
                mem_count_min_ = std::min(mem_count_, mem_count_min_);
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
個々のメモリブロックは、下記のコードのalignasでアライメントされた領域となる。

```cpp
    //  example/dynamic_memory_allocation/mpool_fixed.h 11

    constexpr size_t MPoolFixed_MinSize{32};

    namespace Inner_ {
    template <uint32_t MEM_SIZE>
    union mem_chunk {
        mem_chunk* next;

        // MPoolFixed_MinSizeの整数倍のエリアを、最大アラインメントが必要な基本型にアライン
        alignas(std::max_align_t) uint8_t mem[Roundup(MPoolFixed_MinSize, MEM_SIZE)];
    };
    }  // namespace Inner_
```

MPoolFixedに限らずメモリアロケータが返すメモリは、
どのようなアライメントにも対応できなければならないため、このようにする必要がある。

MPoolFixed::alloc/MPoolFixed::freeを見ればわかる通り、malloc/freeの実装に比べ格段にシンプルであり、
これによりリアルタイム性の保障は容易である。

なお、この実装ではmalloc/freeと同様に使用制限の少ない[スピンロック](cpp_idioms.md#SS_21_9_5)(SpinLock)を使用したが、
このロックは、ラウンドロビンでスケジューリングされるスレッドの競合を防ぐためのものであり、
固定プライオリティでのスケジューリングが前提となるような組み込みソフトで使用した場合、
デッドロックを引き起こす可能性がある。
組み込みソフトでは、割り込みディセーブル/イネーブルを使ってロックすることを推奨する。

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

### 可変長メモリプール <a id="SS_14_2_2"></a>
可変長メモリプールを生成するMPoolVariableの実装は下記のようになる
(全体は巻末の「[example/dynamic_memory_allocation/mpool_variable.h](sample_code.md#SS_26_2_36)」に掲載する)。

```cpp
    //  example/dynamic_memory_allocation/mpool_variable.h 59

    template <uint32_t MEM_SIZE>
    class MPoolVariable final : public MPool {
    public:
        MPoolVariable() noexcept : MPool{MEM_SIZE}
        {
            header_->next    = nullptr;
            header_->n_units = sizeof(buff_) / Inner_::unit_size;
        }

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

上記の抜粋である下記のイテレータにより、このメモリプールの状態を見ることができる。

```cpp
    //  example/dynamic_memory_allocation/mpool_variable.h 72

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
```

可変長メモリプールとイテレータの使用例を下記に示す。

```cpp
    //  example/dynamic_memory_allocation/mpool_variable_ut.cpp 322

    MPoolVariable<1024 * 64> mpv;  // 可変長メモリプール

    constexpr size_t alloc_cout = 100U;
    void*            mem[alloc_cout]{};

    for (size_t i = 0; i < alloc_cout; ++i) {
        mem[i] = mpv.Alloc(i + 100);
    }
```
上記のような使用ではフラグメントは発生しないが、下記によりそのことを見てみよう。

```cpp
    //  example/dynamic_memory_allocation/mpool_variable_ut.cpp 333

    std::cout << "mpv:" << __LINE__ << std::endl;
    for (auto itor = mpv.cbegin(); itor != mpv.cend(); ++itor) {
        std::cout << std::setw(16) << (*itor)->next << ":" << (*itor)->n_units << std::endl;
    }
```

この結果は、下記のように出力される(後に示すが、mpvが保持しているメモリが１つの塊のままであり、
フラグメントを起こしていないことを示している)。

```
mpv:238
               0:3014
```

敢えてフラグメントを起こすために、以下のようなコードを実行する。

```cpp
    //  example/dynamic_memory_allocation/mpool_variable_ut.cpp 340

    for (size_t i = 0; i < alloc_cout; ++i) {
        if (i % 2 == 0) {  // 偶数だけ解放
            mpv.Free(mem[i]);
        }
    }

    std::cout << "mpv:" << __LINE__ << std::endl;
    for (auto itor = mpv.cbegin(); itor != mpv.cend(); ++itor) {
        std::cout << std::setw(16) << (*itor)->next << ":" << (*itor)->n_units << std::endl;
    }
```

この結果、以下のような出力が得られる。これはmpvにはまだメモリが残されているものの、
mpvが保持しているメモリの先頭付近がフラグメントを起こしていることを示している。

```
mpv:249
  0x7ffdeca0b4a0:8            
  0x7ffdeca0b5a0:8
  0x7ffdeca0b6a0:8
  0x7ffdeca0b7a0:8
  0x7ffdeca0b8a0:8
  ... 省略
               0:3014     <- アロケーションされていないメモリの塊
```

## メモリプールのエクセプション <a id="SS_14_3"></a>
メモリプール内で回復不可能なエラーが発生した場合、
エクセプションの送出によりそのことを使用側にそれを伝えなければならない。

多くのコンパイラのエクセプション処理機構にはmalloc/freeが使われているため、
メモリプールの実装に通常の例外を使用した場合、メモリプールの開発趣旨に反する。


ここでは、

- エクセプション用の型[MPoolBadAlloc](dynamic_memory_allocation.md#SS_14_3_1)の開発
- [エクセプション処理機構の変更](dynamic_memory_allocation.md#SS_14_3_2)

を通じて、メモリプールのエクセプション機構を紹介する。

### MPoolBadAlloc <a id="SS_14_3_1"></a>
MPoolBadAllocは下記のように定義されたクラスであり、
「[ファイル位置を静的に保持したエクセプションクラスの開発](template_meta_programming.md#SS_13_7_6_4)」
で示したのクラスライブラリ基づいたメモリプール専用のエクセプション型である。

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

のような処理の継続ができない場合に用いるエクセプション専用クラスである。


### エクセプション処理機構の変更 <a id="SS_14_3_2"></a>
多くのコンパイラのエクセプション処理機構にはnew/deleteやmalloc/freeが使われているため、
リアルタイム性が必要な個所でエクセプション処理を行ってはならない。
そういった規制でプログラミングを行っていると、
リアルタイム性が不要な処理であるため使用しているstdコンテナにすら、
既存のエクセプション処理機構を使わせたく無くなるものである。

コンパイラに[g++](cpp_idioms.md#SS_21_10_1)や[clang++](cpp_idioms.md#SS_21_10_2)を使っている場合、
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
安易にエクセプションや標準ライブラリのコンテナを使用禁止することなく、安全に使用する方法を探るべきだろう。


## new/deleteのオーバーロード <a id="SS_14_4"></a>
前述したように、組み込みソフトにはmalloc/freeを使用したnew/deleteではシステムの制限を満たせないことが多い。
C++11では、以下のような方法により、このような問題を回避することができる。

* [グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_1)
* [クラスnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_3)



### グローバルnew/deleteのオーバーロード <a id="SS_14_4_1"></a>
[固定長メモリプール](dynamic_memory_allocation.md#SS_14_2_1)を使用した`operator new`のオーバーロードの実装例を以下に示す。

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

        static char fake;

        return &fake;
    }
```

上記で定義された`operator new`は、

* 32の整数倍のサイズを持つ32個のメモリプールを持つ
* 各メモリープールは128個のメモリブロックを持つ
* メモリブロックの最大長は1024バイト

のような仕様を持つため、実際に使う場合は、メモリのサイズや個数の調整が必要だろうが、
後で詳しく見るようにリアルタイム性の阻害となるようなコードはないため、
リアルタイム性が必要なソフトウェアでも使用可能である。

静的オブジェクトを含まないアプリケーションでは、
上記のコードのsetupで行っているmpool_tableの初期化は
[一様初期化](core_lang_spec.md#SS_19_6_6)で行った方が良いが、
例で用いたアプリケーションにはnewを行う静的オブジェクトが存在するため
(google testは静的オブジェクトを利用する)、
setupで行っているような方法以外では、
最初の`operator new`の呼び出しより前にmpool_tableの初期化をすることはできない。

mpool_tableはMPoolポインタを保持するが、そのポインタが指すオブジェクトの実態は、
gen_mpool<>が生成したMPoolFixed<>オブジェクトである。
gen_mpool<>については、その内部に静的に確保したメモリを使用して、
[プレースメントnew](core_lang_spec.md#SS_19_6_9)によりMPoolオブジェクトを生成する下記の関数テンプレートである。

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


この実装では対応するMPoolが空であった場合、
それよりも大きいメモリブロックを持つMPoolからメモリを返す仕様としたが、
その時点でアサーションフェールさせ
(つまり、対応するMPoolが空である状態でのAllocの呼び出しをバグとして扱う)、
MEM_COUNTの値を見直した方が、
より少ないメモリで動作する組み込みソフトを作りやすいだろう。

`operator delete`については、下記の2種類が必要となる。

size2indexは要求されたサイズから、
それに対応するMPoolポインタを保持するmpool_tableのインデックスを導出する関数である。

```cpp
    //  example/dynamic_memory_allocation/global_new_delete.cpp 111

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

`operator delete(void* mem, std::size_t size)`は、完全型のオブジェクトのメモリ解放に使用され、
`operator delete(void* mem)`は、それ以外のメモリ解放に使用される。

コードから明らかな通り、size付きの`operator delete`の方がループの回転数が少なくなるため、
高速に動作するが、malloc/freeの実装(「[malloc/freeの問題点](dynamic_memory_allocation.md#SS_14_1)」参照)で使用したHeader_t
を導入することでこの実行コストはほとんど排除できる。
そのトレードオフとしてメモリコストが増えるため、ここでは例示した仕様にした。

### デバッグ用イテレータ <a id="SS_14_4_2"></a>
[グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_1)で示したグローバルnew/deleteの実装は、適切なメモリの量を調整する必要がある。
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
    //  example/dynamic_memory_allocation/global_new_delete.cpp 35

    MPool* mpool_table[32];
```
```cpp
    //  example/dynamic_memory_allocation/global_new_delete.cpp 137

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



### クラスnew/deleteのオーバーロード <a id="SS_14_4_3"></a>
「[グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_1)」で示したコードのロックを、
「割り込みディセーブル/イネーブル」に置き換えることで、リアルタイム性を保障することができるが、
この機構はある程度多くのメモリを必要とするため、
極めてメモリ制限の厳しいシステムでは使用が困難である場合もあるだろう。

そのような場合、非スタック上でのオブジェクト生成には、

* 限定的なクラスのみ、newによる動的な方法を用いる
* その他のクラスに対しては、[Singleton](design_pattern.md#SS_9_13)や[Named Constructor](design_pattern.md#SS_9_18)と同様な静的な方法を用いる

とし、グローバルnewを使用しないことが、より良いメモリ使用方法となり得る。

グローバルnewを使わずに動的にオブジェクトを生成するためには、

* [プレースメントnew](core_lang_spec.md#SS_19_6_9)を使う
* クラス毎にnew/deleteをオーバーロードする

という2つの選択肢が考えられるが、プレースメントnewは見慣れないシンタックスを用いるため、これの使用は避けるべきである。
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
「[グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_1)」に比べ、優れているように見えてしまうかもしれないが、
下記のように、さらに派生クラスを定義してしまうとnewが失敗してしまうことがあるので注意が必要である。

```cpp
    //  example/dynamic_memory_allocation/class_new_delete_ut.cpp 135

    struct Large : A {
        uint8_t buff[1024];  // mpf_ABCDのメモリブロックのサイズを超える
    };
```
```cpp
    //  example/dynamic_memory_allocation/class_new_delete_ut.cpp 144

    ASSERT_EQ(10, mpf_ABCD.GetCount());
    ASSERT_THROW(auto large = std::make_unique<Large>(), MPoolBadAlloc);  // サイズが大きすぎる
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
    //  example/dynamic_memory_allocation/class_new_delete_ut.cpp 153

    class DeletedNew : OpNewDeleted {  // プライベート継承
    };

    class DelivedDeletedNew : DeletedNew {  // プライベート継承
    };

    // DeletedNew* ptr0 { new DeletedNew };                // OpNewDeletedの効果でコンパイルエラー
    // DelivedDeletedNew* ptr1 { new DelivedDeletedNew };  // 同上
```

この記述方法は、コードインスペクションの省力化にも繋がるため、
OpNewを使うプロジェクトには導入するべきだろう。


### new/deleteのオーバーロードのまとめ <a id="SS_14_4_4"></a>
ここまで、malloc/freeの問題の様々な回避方法を示したのでその組み合わせをまとめる。

1. リアルタイムパスでのオブジェクトの生成/解放を行う必要があるクラスのnew/deleteのオーバーロードを
  [固定長メモリプール](dynamic_memory_allocation.md#SS_14_2_1)により実装する。
2. グローバルnew/deleteのオーバーロードを[可変長メモリプール](dynamic_memory_allocation.md#SS_14_2_2)により実装する。

上記1によりリアルタイム性の問題は発生しない。
2により、フラグメントの状態を調査できるようになる。
ここではデバッグイテレータの実装を行っていないが、
[デバッグ用イテレータ](dynamic_memory_allocation.md#SS_14_5_1)の実装例が参考になるだろう。


## 標準ライブラリのコンテナ用アロケータ <a id="SS_14_5"></a>
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

アロケータのパブリックなメンバやoperator ==、operator !=は、標準ライブラリに従い定義している
([標準ライブラリのallocator](https://cpprefjp.github.io/reference/memory/allocator.html)参照)。

上記コードからわかるようにメモリの実際のアロケーションには、
これまでと同様にMPoolから派生したクラスを使用するが、
リアルタイム性は不要であるためメモリ効率が悪いMPoolFixedは使わない。
代わりに、可変長メモリを扱うためメモリ効率がよいMPoolVariabl
(「[可変長メモリプール](dynamic_memory_allocation.md#SS_14_2_2)」参照)を使う。

C++14の環境で標準ライブラリのアロケータを置き換える場合は、上記のような方法で実現できるが、
C++17以降では、[std::pmr::polymorphic_allocator](stdlib_and_concepts.md#SS_20_6_2)を使用するべきである。

### デバッグ用イテレータ <a id="SS_14_5_1"></a>
[可変長メモリプール](dynamic_memory_allocation.md#SS_14_2_2)を使用すると、
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
    //  example/dynamic_memory_allocation/mpool_variable_ut.cpp 322

    MPoolVariable<1024 * 64> mpv;  // 可変長メモリプール

    constexpr size_t alloc_cout = 100U;
    void*            mem[alloc_cout]{};

    for (size_t i = 0; i < alloc_cout; ++i) {
        mem[i] = mpv.Alloc(i + 100);
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

「[グローバルnew/deleteのオーバーロード](dynamic_memory_allocation.md#SS_14_4_1)」でも述べたように、
デバッグ用入出力機能からこのような出力を得られるようにしておくべきである。




