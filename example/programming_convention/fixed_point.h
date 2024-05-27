#pragma once

#include <cstdint>
#include <type_traits>

// @@@ sample begin 0:0

/// @class FixedPoint
/// @brief BASIC_TYPEで指定する基本型のビット長を持つ固定小数点を扱うためのクラス
/// @tparam BASIC_TYPE       全体のビット長や、符号を指定するための整数型
/// @tparam FRACTION_BIT_NUM 小数点保持のためのビット長
template <typename BASIC_TYPE, uint32_t FRACTION_BIT_NUM>
class FixedPoint {
public:
    FixedPoint(BASIC_TYPE                                integer  = 0,
               typename std::make_unsigned_t<BASIC_TYPE> fraction = 0) noexcept
        : value_{get_init_value(integer, fraction)}
    {
        // @@@ ignore begin
        // signedに対する右ビットシフトの仕様が、算術右ビットシフトでないと
        // このクラスは成立しない。下記のstatic_assertはその確認。
        static_assert(IsSigned() ? (-1 >> 1 == -1) : true, "need logical right bit sift");

        // BASIC_TYPEをcharにすることは認めない。
        static_assert(!std::is_same_v<BASIC_TYPE, char>, "BASIC_TYPE should not be char");
        // @@@ ignore end
    }
    // @@@ sample end
    // @@@ sample begin 0:1

    // @@@ ignore begin
    ~FixedPoint()                                = default;
    FixedPoint(FixedPoint const&)                = default;
    FixedPoint& operator=(FixedPoint const&)     = default;
    FixedPoint(FixedPoint&&) noexcept            = default;
    FixedPoint& operator=(FixedPoint&&) noexcept = default;

    BASIC_TYPE GetValue() const noexcept { return value_; }

    BASIC_TYPE GetInteger() const noexcept { return value_ >> fraction_bit_num_; }

    BASIC_TYPE GetFraction() const noexcept { return value_ & fraction_bit_mask_; }

    double ToFloatPoint() const noexcept
    {
        return GetInteger() + (static_cast<double>(GetFraction()) / (fraction_bit_mask_ + 1));
    }

    constexpr typename std::make_unsigned_t<BASIC_TYPE> GetFractionMask() const noexcept
    {
        return fraction_bit_mask_;
    }

    constexpr typename std::make_unsigned_t<BASIC_TYPE> GetIntegerMask() const noexcept
    {
        return integer_bit_mask_;
    }

    static constexpr bool IsSigned() noexcept { return std::is_signed_v<BASIC_TYPE>; }

    static constexpr bool IsUnsigned() noexcept { return std::is_unsigned_v<BASIC_TYPE>; }

    // @@@ ignore end
    FixedPoint& operator+=(FixedPoint rhs) noexcept
    // @@@ ignore begin
    {
        value_ += rhs.value_;
        return *this;
    }

    // @@@ ignore end
    FixedPoint& operator-=(FixedPoint rhs) noexcept
    // @@@ ignore begin
    {
        value_ -= rhs.value_;
        return *this;
    }

    // @@@ ignore end
    FixedPoint& operator*=(FixedPoint rhs) noexcept
    // @@@ ignore begin
    {
        value_ *= rhs.value_ >> fraction_bit_num_;
        return *this;
    }

    // @@@ ignore end
    FixedPoint& operator/=(FixedPoint rhs) noexcept
    // @@@ ignore begin
    {
        using T = std::conditional_t<IsSigned(), int64_t, uint64_t>;

        value_ = (static_cast<T>(value_) << fraction_bit_num_) / rhs.value_;

        return *this;
    }

    // @@@ ignore end
private:
    BASIC_TYPE value_;
    // @@@ ignore begin

    static constexpr uint32_t bit_mask(uint32_t bit_len) noexcept
    {
        if (bit_len == 0) {
            return 0x0;
        }

        return bit_mask(bit_len - 1) | (0x01 << (bit_len - 1));
    }

    static constexpr uint32_t fraction_bit_num_{FRACTION_BIT_NUM};
    static constexpr uint32_t fraction_bit_mask_{bit_mask(fraction_bit_num_)};
    static constexpr uint32_t integer_bit_num_{sizeof(BASIC_TYPE) * 8 - FRACTION_BIT_NUM};
    static constexpr uint32_t integer_bit_mask_{bit_mask(integer_bit_num_) << fraction_bit_num_};

    static constexpr BASIC_TYPE get_init_value(BASIC_TYPE integer, BASIC_TYPE fraction) noexcept
    {
#if 0  // 本来は左シフト<<を使いたいが、signedに対しての<<は良くないので
        return (integer << fraction_bit_num_) | fraction;
#else
        return (integer * (fraction_bit_mask_ + 1)) | fraction;
#endif
    }
    // @@@ ignore end

    friend bool operator==(FixedPoint lhs, FixedPoint rhs) noexcept
    // @@@ ignore begin
    {
        return lhs.value_ == rhs.value_;
    }

    friend bool operator!=(FixedPoint lhs, FixedPoint rhs) noexcept { return !(lhs == rhs); }

    friend bool operator>(FixedPoint lhs, FixedPoint rhs) noexcept
    {
        return lhs.value_ > rhs.value_;
    }

    friend bool operator>=(FixedPoint lhs, FixedPoint rhs) noexcept
    {
        return (lhs > rhs) || (lhs == rhs);
    }

    friend bool operator<(FixedPoint lhs, FixedPoint rhs) noexcept { return (rhs > lhs); }

    friend bool operator<=(FixedPoint lhs, FixedPoint rhs) noexcept
    {
        return (lhs < rhs) || (lhs == rhs);
    }
    // @@@ ignore end

    // FixedPoint() + intのようなオーバーロードを作るためにあえてfriend
    friend FixedPoint operator+(FixedPoint lhs, FixedPoint rhs) noexcept
    // @@@ ignore begin
    {
        lhs += rhs;
        return lhs;
    }

    friend FixedPoint operator-(FixedPoint lhs, FixedPoint rhs) noexcept
    {
        lhs -= rhs;
        return lhs;
    }

    friend FixedPoint operator*(FixedPoint lhs, FixedPoint rhs) noexcept
    {
        lhs *= rhs;
        return lhs;
    }

    friend FixedPoint operator/(FixedPoint lhs, FixedPoint rhs) noexcept
    {
        lhs /= rhs;
        return lhs;
    }
    // @@@ ignore end
};
// @@@ sample end
