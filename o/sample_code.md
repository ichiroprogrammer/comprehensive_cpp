<!-- ./md/sample_code.md -->
# 21 Sample Code <a id="SS_21"></a>
## 21.1 C++ <a id="SS_21_1"></a>
### 21.1.1 example/dynamic_memory_allocation/malloc_ut.cpp <a id="SS_21_1_1"></a>


```cpp
          1 #include <sys/unistd.h>
          2 
          3 #include <cassert>
          4 #include <cstdint>
          5 #include <mutex>
          6 
          7 #include "gtest_wrapper.h"
          8 
          9 #include "dynamic_memory_allocation_ut.h"
         10 #include "spin_lock.h"
         11 #include "utils.h"
         12 
         13 // @@@ sample begin 0:0
         14 
         15 extern "C" void* sbrk(ptrdiff_t __incr);
         16 // @@@ sample end
         17 
         18 namespace MallocFree {
         19 // @@@ sample begin 1:0
         20 
         21 namespace {
         22 
         23 struct header_t {
         24     header_t* next;
         25     size_t    n_units;  // header_tが何個あるか
         26 };
         27 
         28 header_t*        header{nullptr};
         29 SpinLock         spin_lock{};
         30 constexpr size_t unit_size{sizeof(header_t)};
         31 
         32 inline bool sprit(header_t* header, size_t n_units, header_t*& next) noexcept
         33 {
         34     // @@@ ignore begin
         35     assert(n_units > 1);  // ヘッダとバッファなので最低でも2
         36 
         37     next = nullptr;
         38 
         39     if (header->n_units == n_units || header->n_units == n_units + 1) {
         40         next = header->next;
         41         return true;
         42     }
         43     else if (header->n_units > n_units) {
         44         next            = header + n_units;
         45         next->n_units   = header->n_units - n_units;
         46         next->next      = header->next;
         47         header->n_units = n_units;
         48         return true;
         49     }
         50 
         51     return false;
         52     // @@@ ignore end
         53 }
         54 
         55 inline void concat(header_t* front, header_t* rear) noexcept
         56 {
         57     // @@@ ignore begin
         58     if (front + front->n_units == rear) {  // 1枚のメモリになる
         59         front->n_units += rear->n_units;
         60         front->next = rear->next;
         61     }
         62     else {
         63         front->next = rear;
         64     }
         65     // @@@ ignore end
         66 }
         67 
         68 header_t* set_back(void* mem) noexcept { return static_cast<header_t*>(mem) - 1; }
         69 
         70 static_assert(sizeof(header_t) == alignof(std::max_align_t));
         71 
         72 void* malloc_inner(size_t size) noexcept
         73 {
         74     // @@@ ignore begin
         75     // size分のメモリとヘッダ
         76     auto n_units = (Roundup(unit_size, size) / unit_size) + 1;
         77     auto lock    = std::lock_guard{spin_lock};
         78 
         79     auto curr = header;
         80     for (header_t* prev = nullptr; curr != nullptr; prev = curr, curr = curr->next) {
         81         header_t* next;
         82 
         83         if (!sprit(curr, n_units, next)) {
         84             continue;
         85         }
         86 
         87         if (prev == nullptr) {
         88             header = next;
         89         }
         90         else {
         91             prev->next = next;
         92         }
         93         break;
         94     }
         95 
         96     if (curr != nullptr) {
         97         ++curr;
         98     }
         99 
        100     return curr;
        101     // @@@ ignore end
        102 }
        103 }  // namespace
        104 // @@@ sample end
        105 // @@@ sample begin 2:0
        106 
        107 void free(void* mem) noexcept
        108 {
        109     header_t* mem_to_free = set_back(mem);
        110 
        111     mem_to_free->next = nullptr;
        112 
        113     auto lock = std::lock_guard{spin_lock};
        114 
        115     if (header == nullptr) {
        116         header = mem_to_free;
        117         return;
        118     }
        119     // @@@ sample end
        120     // @@@ sample begin 2:1
        121 
        122     if (mem_to_free < header) {
        123         concat(mem_to_free, header);
        124         header = mem_to_free;
        125         return;
        126     }
        127 
        128     auto curr = header;
        129     for (; curr->next != nullptr; curr = curr->next) {
        130         if (mem_to_free < curr->next) {  // 常に curr < mem_to_free
        131             concat(mem_to_free, curr->next);
        132             concat(curr, mem_to_free);
        133             return;
        134         }
        135     }
        136 
        137     concat(curr, mem_to_free);
        138     // @@@ sample end
        139     // @@@ sample begin 2:2
        140 }
        141 // @@@ sample end
        142 // @@@ sample begin 3:0
        143 
        144 void* malloc(size_t size) noexcept
        145 {
        146     void* mem = malloc_inner(size);
        147     // @@@ sample end
        148     // @@@ sample begin 3:1
        149 
        150     if (mem == nullptr) {
        151         auto const add_size = Roundup(unit_size, 1024 * 1024 + size);  // 1MB追加
        152 
        153         header_t* add = static_cast<header_t*>(sbrk(add_size));
        154         add->n_units  = add_size / unit_size;
        155         free(++add);
        156         mem = malloc_inner(size);
        157     }
        158     // @@@ sample end
        159     // @@@ sample begin 3:2
        160 
        161     return mem;
        162 }
        163 // @@@ sample end
        164 
        165 namespace {
        166 TEST(NewDelete_Opt, malloc)
        167 {
        168     {
        169         void* mem = malloc(1024);
        170 
        171         ASSERT_NE(nullptr, mem);
        172         free(mem);
        173 
        174         void* ints[8]{};
        175 
        176         constexpr auto n_units = Roundup(unit_size, unit_size + sizeof(int)) / unit_size;
        177 
        178         for (auto& i : ints) {
        179             i = malloc(sizeof(int));
        180 
        181             header_t* h = set_back(i);
        182             ASSERT_EQ(h->n_units, n_units);
        183         }
        184 
        185         for (auto& i : ints) {
        186             free(i);
        187         }
        188     }
        189 
        190     // @@@ sample begin 4:0
        191 
        192     void* mem[1024];
        193 
        194     for (auto& m : mem) {  // 32バイト x 1024個のメモリ確保
        195         m = malloc(32);
        196     }
        197 
        198     // memを使用した何らかの処理
        199     // @@@ ignore begin
        200     // @@@ ignore end
        201 
        202     for (auto i = 0U; i < ArrayLength(mem); i += 2) {  // 512個のメモリを解放
        203         free(mem[i]);
        204     }
        205     // @@@ sample end
        206 
        207     for (auto i = 1U; i < ArrayLength(mem); i += 2) {
        208         free(mem[i]);
        209     }
        210 }
        211 }  // namespace
        212 }  // namespace MallocFree
```

### 21.1.2 example/dynamic_memory_allocation/mpool_variable.h <a id="SS_21_1_2"></a>


```cpp
          1 #pragma once
          2 #include <cassert>
          3 #include <cstdint>
          4 #include <mutex>
          5 #include <optional>
          6 
          7 #include "mpool.h"
          8 #include "spin_lock.h"
          9 #include "utils.h"
         10 
         11 namespace Inner_ {
         12 
         13 struct header_t {
         14     header_t* next;
         15     size_t    n_units;  // header_tが何個あるか
         16 };
         17 
         18 constexpr auto unit_size = sizeof(header_t);
         19 
         20 inline std::optional<header_t*> sprit(header_t* header, size_t n_units) noexcept
         21 {
         22     assert(n_units > 1);  // ヘッダとバッファなので最低でも2
         23 
         24     if (header->n_units == n_units || header->n_units == n_units + 1) {
         25         return header->next;
         26     }
         27     else if (header->n_units > n_units) {
         28         auto next       = header + n_units;
         29         next->n_units   = header->n_units - n_units;
         30         next->next      = header->next;
         31         header->n_units = n_units;
         32         return next;
         33     }
         34 
         35     return std::nullopt;
         36 }
         37 
         38 inline void concat(header_t* front, header_t* rear) noexcept
         39 {
         40     if (front + front->n_units == rear) {  // 1枚のメモリになる
         41         front->n_units += rear->n_units;
         42         front->next = rear->next;
         43     }
         44     else {
         45         front->next = rear;
         46     }
         47 }
         48 
         49 inline header_t* set_back(void* mem) noexcept { return static_cast<header_t*>(mem) - 1; }
         50 
         51 static_assert(sizeof(header_t) == alignof(std::max_align_t));
         52 
         53 template <uint32_t MEM_SIZE>
         54 struct buffer_t {
         55     alignas(std::max_align_t) uint8_t buffer[Roundup(sizeof(header_t), MEM_SIZE)];
         56 };
         57 }  // namespace Inner_
         58 
         59 // @@@ sample begin 0:0
         60 
         61 template <uint32_t MEM_SIZE>
         62 class MPoolVariable final : public MPool {
         63 public:
         64     // @@@ sample end
         65     // @@@ sample begin 0:1
         66     MPoolVariable() noexcept : MPool{MEM_SIZE}
         67     {
         68         header_->next    = nullptr;
         69         header_->n_units = sizeof(buff_) / Inner_::unit_size;
         70     }
         71     // @@@ sample end
         72     // @@@ sample begin 0:2
         73 
         74     class const_iterator {
         75     public:
         76         explicit const_iterator(Inner_::header_t const* header) noexcept : header_{header} {}
         77         const_iterator(const_iterator const&) = default;
         78         const_iterator(const_iterator&&)      = default;
         79 
         80         const_iterator& operator++() noexcept  // 前置++のみ実装
         81         {
         82             assert(header_ != nullptr);
         83             header_ = header_->next;
         84 
         85             return *this;
         86         }
         87 
         88         Inner_::header_t const* operator*() noexcept { return header_; }
         89 
         90         // clang-format off
         91 
         92     #if __cplusplus <= 201703L  // c++17
         93         bool operator==(const_iterator const& rhs) noexcept { return header_ == rhs.header_; }
         94         bool operator!=(const_iterator const& rhs) noexcept { return !(*this == rhs); }
         95     #else  // c++20
         96 
         97         auto operator<=>(const const_iterator&) const = default;
         98     #endif
         99         // clang-format on
        100 
        101     private:
        102         Inner_::header_t const* header_;
        103     };
        104 
        105     const_iterator begin() const noexcept { return const_iterator{header_}; }
        106     const_iterator end() const noexcept { return const_iterator{nullptr}; }
        107     const_iterator cbegin() const noexcept { return const_iterator{header_}; }
        108     const_iterator cend() const noexcept { return const_iterator{nullptr}; }
        109     // @@@ sample end
        110     // @@@ sample begin 0:3
        111 
        112 private:
        113     using header_t = Inner_::header_t;
        114 
        115     Inner_::buffer_t<MEM_SIZE> buff_{};
        116     header_t*                  header_{reinterpret_cast<header_t*>(buff_.buffer)};
        117     mutable SpinLock           spin_lock_{};
        118     size_t                     unit_count_{sizeof(buff_) / Inner_::unit_size};
        119     size_t                     unit_count_min_{sizeof(buff_) / Inner_::unit_size};
        120 
        121     virtual void* alloc(size_t size) noexcept override
        122     {
        123         // @@@ ignore begin
        124         // size分のメモリとヘッダ
        125         auto n_units = (Roundup(Inner_::unit_size, size) / Inner_::unit_size) + 1;
        126 
        127         auto lock = std::lock_guard{spin_lock_};
        128 
        129         auto curr = header_;
        130 
        131         for (header_t* prev{nullptr}; curr != nullptr; prev = curr, curr = curr->next) {
        132             auto opt_next = std::optional<header_t*>{sprit(curr, n_units)};
        133 
        134             if (!opt_next) {
        135                 continue;
        136             }
        137 
        138             auto next = *opt_next;
        139             if (prev == nullptr) {
        140                 header_ = next;
        141             }
        142             else {
        143                 prev->next = next;
        144             }
        145             break;
        146         }
        147 
        148         if (curr != nullptr) {
        149             unit_count_ -= curr->n_units;
        150             unit_count_min_ = std::min(unit_count_, unit_count_min_);
        151             ++curr;
        152         }
        153 
        154         return curr;
        155         // @@@ ignore end
        156     }
        157 
        158     virtual void free(void* mem) noexcept override
        159     {
        160         // @@@ ignore begin
        161         header_t* to_free = Inner_::set_back(mem);
        162 
        163         to_free->next = nullptr;
        164 
        165         auto lock = std::lock_guard{spin_lock_};
        166 
        167         unit_count_ += to_free->n_units;
        168         unit_count_min_ = std::min(unit_count_, unit_count_min_);
        169 
        170         if (header_ == nullptr) {
        171             header_ = to_free;
        172             return;
        173         }
        174 
        175         if (to_free < header_) {
        176             concat(to_free, header_);
        177             header_ = to_free;
        178             return;
        179         }
        180 
        181         header_t* curr = header_;
        182 
        183         for (; curr->next != nullptr; curr = curr->next) {
        184             if (to_free < curr->next) {  // 常に curr < to_free
        185                 concat(to_free, curr->next);
        186                 concat(curr, to_free);
        187                 return;
        188             }
        189         }
        190 
        191         concat(curr, to_free);
        192         // @@@ ignore end
        193     }
        194 
        195     virtual size_t get_size() const noexcept override { return 1; }
        196     virtual size_t get_count() const noexcept override { return unit_count_ * Inner_::unit_size; }
        197     virtual size_t get_count_min() const noexcept override { return unit_count_min_ * Inner_::unit_size; }
        198 
        199     virtual bool is_valid(void const* mem) const noexcept override
        200     {
        201         return (&buff_ < mem) && (mem < &buff_.buffer[ArrayLength(buff_.buffer)]);
        202     }
        203     // @@@ sample end
        204     // @@@ sample begin 0:4
        205 };
        206 // @@@ sample end
```



