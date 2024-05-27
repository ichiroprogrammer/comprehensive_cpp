#include <iostream>

#include "gtest_wrapper.h"

#include "fixed_point.h"

namespace {

template <typename FLOAT_0, typename FLOAT_1>
bool is_equal(FLOAT_0 lhs, FLOAT_1 rhs) noexcept
{
    static_assert(std::is_floating_point_v<FLOAT_0>, "FLOAT_0 shoud be float or double.");
    static_assert(std::is_same_v<FLOAT_0, FLOAT_1>, "FLOAT_0 and FLOAT_1 shoud be a same type.");

    return std::abs(lhs - rhs) <= std::numeric_limits<FLOAT_0>::epsilon();
}

TEST(FixedPoint, uchar_4)
// @@@ sample begin 0:0

// 以下は、FixedPoint<>の使用例である。
{
    using FP4 = FixedPoint<uint8_t, 4>;  // 基本型uint8_t、小数点4ビット
    auto fp0  = FP4{};

    // @@@ ignore begin

    ASSERT_FALSE(fp0.IsSigned());
    ASSERT_TRUE(fp0.IsUnsigned());

    // @@@ ignore end
    // clang-format off
    fp0 = 7;    ASSERT_EQ(7, fp0);
    fp0 = 7;    ASSERT_NE(6, fp0);
    fp0 += 2;   ASSERT_EQ(FP4{9}, fp0);         
                ASSERT_TRUE(is_equal(9.0, fp0.ToFloatPoint()));
    fp0 /= 2;   ASSERT_EQ((FP4{4, 8}), fp0);    
                ASSERT_TRUE(is_equal(4.5, fp0.ToFloatPoint()));
    fp0 /= 2;   ASSERT_EQ((FP4{2, 4}), fp0);    
                ASSERT_TRUE(is_equal(2.25, fp0.ToFloatPoint()));
    fp0 *= 4;   ASSERT_EQ(FP4{9}, fp0);
    fp0 += 7;   ASSERT_EQ(FP4{0}, fp0);
    // clang-format on
}
// @@@ ignore begin

TEST(FixedPoint, int_7)
{
    auto fp0 = FixedPoint<int, 7>{0xff, 0x7f};

    ASSERT_TRUE(fp0.IsSigned());

    ASSERT_EQ(0x7fff, fp0.GetValue());

    ASSERT_EQ(0xff, fp0.GetInteger());
    ASSERT_EQ(0x7f, fp0.GetFraction());
    ASSERT_EQ(0xffffff80, fp0.GetIntegerMask());
    ASSERT_EQ(0x7f, fp0.GetFractionMask());
}

TEST(FixedPoint, int_8_op_comp)
{
    using FP8 = FixedPoint<int16_t, 8>;

    ASSERT_LT(FP8{0}, FP8{3});
    ASSERT_LE(FP8{0}, FP8{3});
    ASSERT_GT(FP8{3}, FP8{0});
    ASSERT_GE(FP8{3}, FP8{0});

    ASSERT_GT(FP8{0}, -3);
    ASSERT_GE(FP8{0}, -3);
    ASSERT_GE(FP8{0}, 0);
    ASSERT_LT(FP8{-3}, 0);
    ASSERT_LE(FP8{-3}, 0);
    ASSERT_LE(FP8{-3}, -3);

    ASSERT_EQ(FP8{0x81}, FP8{-127});  // overflow
    ASSERT_LT(FP8{0x81}, FP8{0});     // overflow
}

TEST(FixedPoint, int_8_op_fourlaw)
// @@@ ignore end
{
    using FP8 = FixedPoint<int32_t, 8>;  // 基本型int32_t、小数点8ビット

    auto fp0 = FP8{};
    // @@@ ignore begin
    ASSERT_EQ(0, fp0.GetInteger());
    ASSERT_EQ(0, fp0.GetFraction());

    // + - test
    // @@@ ignore end
    // clang-format off
    fp0 = 3;            ASSERT_EQ((FP8{3, 0}), fp0);
    fp0 += 3;           ASSERT_EQ((FP8{6, 0}), fp0);
    fp0 -= 3;           ASSERT_EQ((FP8{3, 0}), fp0);
    // @@@ ignore begin
    fp0 = FP8{0} + 3;   ASSERT_EQ((FP8{3, 0}), fp0);
    fp0 = 3 + fp0;      ASSERT_EQ((FP8{6, 0}), fp0);

    fp0 = FP8{0} - 3;   ASSERT_EQ((FP8{-3, 0}), fp0);

    fp0 = 3 - fp0;      ASSERT_EQ((FP8{6, 0}), fp0);

    // * / test
    // @@@ ignore end
    fp0 = 3;
    fp0 *= 5;           ASSERT_EQ((FP8{15, 0}), fp0);
    fp0 /= 5;           ASSERT_EQ((FP8{3, 0}), fp0);
    fp0 = fp0 / 2;      ASSERT_EQ((FP8{1, 0x80}), fp0);
    // @@@ ignore begin
    fp0 = fp0 * 2;      ASSERT_EQ((FP8{3, 0}), fp0);
    fp0 = 3 * fp0;      ASSERT_EQ((FP8{9, 0}), fp0);
    fp0 = 18 / fp0;     ASSERT_EQ((FP8{2, 0}), fp0);
    // clang-format on
    // @@@ ignore end
}
// @@@ sample end

TEST(FixedPoint, int_8_op_big)
{
    using FP8 = FixedPoint<int32_t, 8>;
    auto fp0  = FP8{};

    // clang-format off
    fp0 =  0x7fffff; ASSERT_EQ((FP8{ 0x7fffff, 0}), fp0);
    fp0 +=      0x1; ASSERT_EQ((FP8{-0x800000, 0}), fp0);   // overflow
    fp0 += 0x100000; ASSERT_EQ((FP8{-0x700000, 0}), fp0);

    fp0 = 1;

    fp0 -= 0x800001; ASSERT_EQ((FP8{-0x800000, 0}), fp0);
    fp0 =  0x800000; ASSERT_EQ((FP8{0x800000, 0}), fp0);    // overflow
    fp0 += 0x7fffff; ASSERT_EQ((FP8{ -0x1, 0}), fp0);

    fp0 =  0x700000;  
    fp0 *= 2;        ASSERT_EQ((FP8{ -0x200000, 0}), fp0);  // overflow
    // clang-format on
}

TEST(FixedPoint, int_8)
{
    using FP8 = FixedPoint<int32_t, 8>;
    auto fp0  = FP8{0x0000ff, 0x7f};

    ASSERT_TRUE(fp0.IsSigned());
    ASSERT_EQ(0xffffff00, fp0.GetIntegerMask());
    ASSERT_EQ(0xff, fp0.GetFractionMask());

    // clang-format off
    auto fp1 = FixedPoint<int, 8>{0, 1};
    auto fp2 = fp0 + fp1;                     ASSERT_EQ((FP8{0xff, 0x80}), fp2);

    fp2 += FixedPoint<int, 8>{0, 0x80};       ASSERT_EQ((FP8{0x100, 0}), fp2);
    fp2 += FixedPoint<int, 8>{0xffff01, 0x0}; ASSERT_EQ(1, fp2); // overflow
    fp2 += FixedPoint<int, 8>{-1, 0x0};       ASSERT_EQ(0, fp2);

    fp2 += FixedPoint<int, 8>{-1, 0x0};       ASSERT_EQ(-1, fp2);

    auto fp3 = fp2 - -2;                      ASSERT_EQ(1, fp3);
    auto fp4 = fp2;
    
    fp4 -= -2;                                ASSERT_EQ(fp3, fp4);
    // clang-format on
}

TEST(FixedPoint, uint_8)
{
    auto fp0 = FixedPoint<uint32_t, 8>{};

    ASSERT_FALSE(fp0.IsSigned());
    ASSERT_EQ(0, fp0.GetValue());
    ASSERT_EQ(0, fp0.GetInteger());
    ASSERT_EQ(0, fp0.GetFraction());
    ASSERT_EQ(0xffffff00, fp0.GetIntegerMask());
    ASSERT_EQ(0xff, fp0.GetFractionMask());
}
}  // namespace
