#include "gtest/gtest.h"
#include "Math.h"

using namespace nut;

class MathTest : public ::testing::Test
{
    protected:
    
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp()
    {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown()
    // {
    // }
};



TEST_F(MathTest, abs)
{
    float f = 3.0f;
    double d = 3.0;
    int i = 3;
    char c = 3;
    unsigned int ui = 3;
    unsigned char uc = 3;

    EXPECT_TRUE(3.0f == Math<float>::abs(f));
    EXPECT_TRUE(3.0f == Math<float>::abs(-f));

    EXPECT_TRUE(3.0 == Math<double>::abs(d));
    EXPECT_TRUE(3.0 == Math<double>::abs(-d));

    EXPECT_TRUE(3 == Math<int>::abs(i));
    EXPECT_TRUE(3 == Math<int>::abs(-i));

    EXPECT_TRUE(3 == Math<char>::abs(c));
    EXPECT_TRUE(3 == Math<char>::abs(-c));

    // Standard 5.3.1/7
    // The operand of the unary - operator shall have arithmetic or enumeration
    // type and the result is the negation of its operand. Integral promotion is
    // performed on integral or enumeration operands. The negative of an unsigned
    // quantity is computed by subtracting its value from 2n, where n is the
    // number of bits in the promoted operand. The type of the result is the type
    // of the promoted operand.
    // 
    // And the paragraph on Integral Promotion 4.5/1
    // An rvalue of type char, signed char, unsigned char, short int, or unsigned
    // short int can be converted to an rvalue of type int if int can represent
    // all the values of the source type; otherwise, the source rvalue can be
    // converted to an rvalue of type unsigned int.
    // 
    // i.e. an unsigned int will not be promoted to an int. And this function will
    // work with U8 and U16 but not with U32 in x86 and with U32 also in x64.
    // Actually it doesn't make any sense using this function with unsigned integers =)

    EXPECT_TRUE(3 == Math<unsigned int>::abs(ui));

    EXPECT_TRUE(3 == Math<unsigned char>::abs(uc));
}



TEST_F(MathTest, isZero)
{
    float f;
    double d;

    // Single precision
    f = 0.0f;
    EXPECT_TRUE(Math<float>::isZero(f));

    f = 0.00000001f;
    EXPECT_TRUE(Math<float>::isZero(f));

    f = -0.00000001f;
    EXPECT_TRUE(Math<float>::isZero(f));

    f = 1.00000001f;
    EXPECT_TRUE(!Math<float>::isZero(f));

    // Double precision
    d = 0.0;
    EXPECT_TRUE(Math<double>::isZero(d));

    d = 0.00000001;
    EXPECT_TRUE(Math<double>::isZero(d));

    d = -0.00000001;
    EXPECT_TRUE(Math<double>::isZero(d));

    d = 1.00000001;
    EXPECT_TRUE(!Math<double>::isZero(d));
}



TEST_F(MathTest, rad2deg)
{
    float rad, deg;

    rad = 0.0f;

    deg = Math<float>::rad2deg(rad);

    EXPECT_NEAR(0.0f, deg, Math<float>::EPSILON);

    rad = 0.523598776f;

    deg = Math<float>::rad2deg(rad);

    EXPECT_NEAR(30.0f, deg, 1e-5f);

    rad = 0.785398163f;

    deg = Math<float>::rad2deg(rad);

    EXPECT_NEAR(45.0f, deg, Math<float>::EPSILON);

    rad = 1.04719755f;

    deg = Math<float>::rad2deg(rad);

    EXPECT_NEAR(60.0f, deg, 1e-5f);

    rad = 1.57079633f;

    deg = Math<float>::rad2deg(rad);

    EXPECT_NEAR(90.0f, deg, Math<float>::EPSILON);

    rad = 3.14159265f;

    deg = Math<float>::rad2deg(rad);

    EXPECT_NEAR(180.0f, deg, Math<float>::EPSILON);

    rad = 3.4906585f;

    deg = Math<float>::rad2deg(rad);

    EXPECT_NEAR(200.0f, deg, Math<float>::EPSILON);

    rad = 5.23598776f;

    deg = Math<float>::rad2deg(rad);

    EXPECT_NEAR(300.0f, deg, Math<float>::EPSILON);

    rad = 6.28318531f;

    deg = Math<float>::rad2deg(rad);

    EXPECT_NEAR(360.0f, deg, Math<float>::EPSILON);

    rad = 7.33038286f;

    deg = Math<float>::rad2deg(rad);

    EXPECT_NEAR(420.0f, deg, Math<float>::EPSILON);
}



TEST_F(MathTest, deg2rad)
{
    float rad, deg;

    deg = 0.0f;

    rad = Math<float>::deg2rad(deg);

    EXPECT_NEAR(0.0f, rad, Math<float>::EPSILON);

    deg = 30.0f;

    rad = Math<float>::deg2rad(deg);

    EXPECT_NEAR(0.523598776f, rad, Math<float>::EPSILON);

    deg = 45.0f;

    rad = Math<float>::deg2rad(deg);

    EXPECT_NEAR(0.785398163f, rad, Math<float>::EPSILON);

    deg = 60.0f;

    rad = Math<float>::deg2rad(deg);

    EXPECT_NEAR(1.04719755f, rad, Math<float>::EPSILON);

    deg = 90.0f;

    rad = Math<float>::deg2rad(deg);

    EXPECT_NEAR(1.57079633f, rad, Math<float>::EPSILON);

    deg = 180.0f;

    rad = Math<float>::deg2rad(deg);

    EXPECT_NEAR(3.14159265f, rad, Math<float>::EPSILON);

    deg = 200.0f;

    rad = Math<float>::deg2rad(deg);

    EXPECT_NEAR(3.4906585f, rad, Math<float>::EPSILON);

    deg = 300.0f;

    rad = Math<float>::deg2rad(deg);

    EXPECT_NEAR(5.23598776f, rad, Math<float>::EPSILON);

    deg = 360.0f;

    rad = Math<float>::deg2rad(deg);

    EXPECT_NEAR(6.28318531f, rad, Math<float>::EPSILON);

    deg = 420.0f;

    rad = Math<float>::deg2rad(deg);

    EXPECT_NEAR(7.33038286f, rad, Math<float>::EPSILON);
}



TEST_F(MathTest, isPowerOf2)
{
    int i;
    unsigned int ui;
    char c;
    unsigned char uc;

    i = 8;
    EXPECT_TRUE(Math<int>::isPowerOf2(i));
    i = 7;
    EXPECT_TRUE(!Math<int>::isPowerOf2(i));

    ui = 8;
    EXPECT_TRUE(Math<unsigned int>::isPowerOf2(ui));
    ui = 7;
    EXPECT_TRUE(!Math<unsigned int>::isPowerOf2(ui));

    c = 8;
    EXPECT_TRUE(Math<char>::isPowerOf2(c));
    c = 7;
    EXPECT_TRUE(!Math<char>::isPowerOf2(c));

    uc = 8;
    EXPECT_TRUE(Math<unsigned char>::isPowerOf2(uc));
    uc = 7;
    EXPECT_TRUE(!Math<unsigned char>::isPowerOf2(uc));
}



TEST_F(MathTest, constants)
{
    EXPECT_NEAR(1e-7, Math<float>::EPSILON, 1e-10);
    EXPECT_NEAR(1e-7, Math<double>::EPSILON, 1e-20);
    
    EXPECT_NEAR(3.1415926535897932384626433832795028841971693993751058209749445923078164062, Math<float>::PI, 1e-7);
    EXPECT_NEAR(3.1415926535897932384626433832795028841971693993751058209749445923078164062, Math<double>::PI, 1e-20);

    EXPECT_NEAR(1.5707963267948966192313216916398, Math<float>::HALF_PI, 1e-7);
    EXPECT_NEAR(1.5707963267948966192313216916398, Math<double>::HALF_PI, 1e-20);
    
    EXPECT_NEAR(57.295779513082320876798154814105, Math<float>::_180_OVER_PI, 1e-6);
    EXPECT_NEAR(57.295779513082320876798154814105, Math<double>::_180_OVER_PI, 1e-20);
    
    EXPECT_NEAR(0.01745329251994329576923690768489, Math<float>::PI_OVER_180, 1e-9);
    EXPECT_NEAR(0.01745329251994329576923690768489, Math<double>::PI_OVER_180, 1e-20);
}
