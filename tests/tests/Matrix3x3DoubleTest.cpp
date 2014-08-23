#include "gtest/gtest.h"
#include "Matrix3x3.h"
#include "Vector3D.h"
#include "GLMatrix.h"

#undef FLOAT
#define FLOAT double

using namespace nut;

class Matrix3x3DoubleTest : public ::testing::Test
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



// Constructors

TEST_F(Matrix3x3DoubleTest, constructors)
{
    // Default constructor
    Matrix3x3<FLOAT> m1;
    
    for (int i = 0; i < 9; ++i)
    {
        if (i == 0 || i == 4 || i == 8)
        {
            EXPECT_FLOAT_EQ(1.0, m1[i]);
        }
        else
        {
            EXPECT_FLOAT_EQ(0.0, m1[i]);
        }
    }

    // Constructor
    Matrix3x3<FLOAT> m2(11, 12, 13,
                        21, 22, 23,
                        31, 32, 33);

    EXPECT_FLOAT_EQ(11, m2[0]);
    EXPECT_FLOAT_EQ(21, m2[1]);
    EXPECT_FLOAT_EQ(31, m2[2]);
    EXPECT_FLOAT_EQ(12, m2[3]);
    EXPECT_FLOAT_EQ(22, m2[4]);
    EXPECT_FLOAT_EQ(32, m2[5]);
    EXPECT_FLOAT_EQ(13, m2[6]);
    EXPECT_FLOAT_EQ(23, m2[7]);
    EXPECT_FLOAT_EQ(33, m2[8]);

    // Copy constructor
    m1 = m2;

    EXPECT_FLOAT_EQ(11, m1[0]);
    EXPECT_FLOAT_EQ(21, m1[1]);
    EXPECT_FLOAT_EQ(31, m1[2]);
    EXPECT_FLOAT_EQ(12, m1[3]);
    EXPECT_FLOAT_EQ(22, m1[4]);
    EXPECT_FLOAT_EQ(32, m1[5]);
    EXPECT_FLOAT_EQ(13, m1[6]);
    EXPECT_FLOAT_EQ(23, m1[7]);
    EXPECT_FLOAT_EQ(33, m1[8]);
}



// Methods

TEST_F(Matrix3x3DoubleTest, clear)
{
    Matrix3x3<FLOAT> m(11, 12, 13,
                       21, 22, 23,
                       31, 32, 33);

    m.clear();

    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(Matrix3x3<FLOAT>::ZERO[i], m[i]);
    }
}



TEST_F(Matrix3x3DoubleTest, setIdentity)
{
    Matrix3x3<FLOAT> m(11, 12, 13,
                       21, 22, 23,
                       31, 32, 33);

    m.setIdentity();

    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(Matrix3x3<FLOAT>::IDENTITY[i], m[i]);
    }
}



TEST_F(Matrix3x3DoubleTest, inverse)
{
    Matrix3x3<FLOAT> inv;

    // Identity inverse
    Matrix3x3<FLOAT> m;

    inv = m.inverse();

    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(Matrix3x3<FLOAT>::IDENTITY[i], m[i]);
    }

    // General inverse
    Matrix3x3<FLOAT> n(10,  -9, -12,
                        7, -12,  11,
                      -10,  10,   3);

    inv = n.inverse();

    Matrix3x3<FLOAT> res(-146.0 / 319.0, -93.0 / 319.0, -243.0 / 319.0,
                         -131.0 / 319.0, -90.0 / 319.0, -194.0 / 319.0,
                          -50.0 / 319.0, -10.0 / 319.0,  -57.0 / 319.0);

    EXPECT_NEAR(res[ 0], inv[ 0], 1e-20);
    EXPECT_NEAR(res[ 1], inv[ 1], 1e-20);
    EXPECT_NEAR(res[ 2], inv[ 2], 1e-16);
    EXPECT_NEAR(res[ 3], inv[ 3], 1e-16);
    EXPECT_NEAR(res[ 4], inv[ 4], 1e-20);
    EXPECT_NEAR(res[ 5], inv[ 5], 1e-20);
    EXPECT_NEAR(res[ 6], inv[ 6], 1e-20);
    EXPECT_NEAR(res[ 7], inv[ 7], 1e-20);
    EXPECT_NEAR(res[ 8], inv[ 8], 1e-20);

    // Linearly dependant inverse
    Matrix3x3<FLOAT> o(10,  -9, -12,
                        7, -12,  11,
                      -20,  18,  24);

    inv = o.inverse();

    EXPECT_NEAR(0.0, inv[ 0], 1e-20);
    EXPECT_NEAR(0.0, inv[ 1], 1e-20);
    EXPECT_NEAR(0.0, inv[ 2], 1e-20);
    EXPECT_NEAR(0.0, inv[ 3], 1e-20);
    EXPECT_NEAR(0.0, inv[ 4], 1e-20);
    EXPECT_NEAR(0.0, inv[ 5], 1e-20);
    EXPECT_NEAR(0.0, inv[ 6], 1e-20);
    EXPECT_NEAR(0.0, inv[ 7], 1e-20);
    EXPECT_NEAR(0.0, inv[ 8], 1e-20);
}



TEST_F(Matrix3x3DoubleTest, determinant)
{
    // Identity determinant
    Matrix3x3<FLOAT> m;

    EXPECT_FLOAT_EQ(1, m.determinant());

    // General determinant
    Matrix3x3<FLOAT> n(10,  -9, -12,
                        7, -12,  11,
                      -10,  10,   3);

    EXPECT_NEAR(319.0, n.determinant(), 1e-20);

    // Linearly dependent matrix
    Matrix3x3<FLOAT> o(10,  -9, -12,
                        7, -12,  11,
                      -20,  18,  24);

    EXPECT_NEAR(0.0, o.determinant(), 1e-20);
}



TEST_F(Matrix3x3DoubleTest, transpose)
{
    // Identity determinant
    Matrix3x3<FLOAT> m(11, 12, 13,
                       21, 22, 23,
                       31, 32, 33);

    Matrix3x3<FLOAT> t = m.transpose();
    
    Matrix3x3<FLOAT> n(11, 21, 31,
                       12, 22, 32,
                       13, 23, 33);

    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(n[i], t[i]);
    }
}



TEST_F(Matrix3x3DoubleTest, constants)
{
    // Identity matrix
    for (int i = 0; i < 9; ++i)
    {
        if (i == 0 || i == 4 || i == 8)
        {
            EXPECT_FLOAT_EQ(1.0, Matrix3x3<FLOAT>::IDENTITY[i]);
        }
        else
        {
            EXPECT_FLOAT_EQ(0.0, Matrix3x3<FLOAT>::IDENTITY[i]);
        }
    }

    // Zero matrix
    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(0.0, Matrix3x3<FLOAT>::ZERO[i]);
    }
}



TEST_F(Matrix3x3DoubleTest, operators)
{
    Matrix3x3<FLOAT> m(11, 12, 13,
                       21, 22, 23,
                       31, 32, 33);

    // Operator []
    m[0] = m[8];
    EXPECT_FLOAT_EQ(33, m[0]);


    // Operator *
    m[0] = 11;
    Vector3D<FLOAT> u(1, 1, 1);

    u = m * u;

    EXPECT_FLOAT_EQ(11 + 12 + 13, u.x);
    EXPECT_FLOAT_EQ(21 + 22 + 23, u.y);
    EXPECT_FLOAT_EQ(31 + 32 + 33, u.z);

    Matrix3x3<FLOAT> n = 2 * m;
    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(2 * m[i], n[i]);
    }

    n = m * 2;
    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(2 * m[i], n[i]);
    }

    n *= 2;
    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(2 * 2 * m[i], n[i]);
    }

    Matrix3x3<FLOAT> m1( 1,  2,  3,
                         5,  6,  7,
                         9, 10, 11);
    
    Matrix3x3<FLOAT> m2( 2,  4,  6,
                        10, 12, 14,
                        18, 20, 22);
    
    n = m1 * m2;

    EXPECT_FLOAT_EQ(4 *  19, n[0]);
    EXPECT_FLOAT_EQ(4 *  22, n[3]);
    EXPECT_FLOAT_EQ(4 *  25, n[6]);

    EXPECT_FLOAT_EQ(4 *  49, n[1]);
    EXPECT_FLOAT_EQ(4 *  58, n[4]);
    EXPECT_FLOAT_EQ(4 *  67, n[7]);
    
    EXPECT_FLOAT_EQ(4 *  79, n[2]);
    EXPECT_FLOAT_EQ(4 *  94, n[5]);
    EXPECT_FLOAT_EQ(4 * 109, n[8]);

    m1 *= m2;

    EXPECT_FLOAT_EQ(4 *  19, n[0]);
    EXPECT_FLOAT_EQ(4 *  22, n[3]);
    EXPECT_FLOAT_EQ(4 *  25, n[6]);

    EXPECT_FLOAT_EQ(4 *  49, n[1]);
    EXPECT_FLOAT_EQ(4 *  58, n[4]);
    EXPECT_FLOAT_EQ(4 *  67, n[7]);
    
    EXPECT_FLOAT_EQ(4 *  79, n[2]);
    EXPECT_FLOAT_EQ(4 *  94, n[5]);
    EXPECT_FLOAT_EQ(4 * 109, n[8]);
  
    // Operator /

    m1 = m2 / 2.0;

    EXPECT_FLOAT_EQ( 1, m1[0]);
    EXPECT_FLOAT_EQ( 2, m1[3]);
    EXPECT_FLOAT_EQ( 3, m1[6]);

    EXPECT_FLOAT_EQ( 5, m1[1]);
    EXPECT_FLOAT_EQ( 6, m1[4]);
    EXPECT_FLOAT_EQ( 7, m1[7]);

    EXPECT_FLOAT_EQ( 9, m1[2]);
    EXPECT_FLOAT_EQ(10, m1[5]);
    EXPECT_FLOAT_EQ(11, m1[8]);

    m2 /= 2;

    EXPECT_FLOAT_EQ( 1, m1[0]);
    EXPECT_FLOAT_EQ( 2, m1[3]);
    EXPECT_FLOAT_EQ( 3, m1[6]);

    EXPECT_FLOAT_EQ( 5, m1[1]);
    EXPECT_FLOAT_EQ( 6, m1[4]);
    EXPECT_FLOAT_EQ( 7, m1[7]);

    EXPECT_FLOAT_EQ( 9, m1[2]);
    EXPECT_FLOAT_EQ(10, m1[5]);
    EXPECT_FLOAT_EQ(11, m1[8]);

    // Operator +
    Matrix3x3<FLOAT> m3( 1,  2,  3,
                         5,  6,  7,
                         9, 10, 11);

    Matrix3x3<FLOAT> m4( 2,  4,  6,
                        10, 12, 14,
                        18, 20, 22);

    m = m3 + m3;
    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(m4[i], m[i]);
    }

    m3 += m3;
    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(m4[i], m3[i]);
    }


    // Operator -
    m = m3 - m3;
    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(0, m[i]);
    }

    m3 -= m3;
    for (int i = 0; i < 9; ++i)
    {
        EXPECT_FLOAT_EQ(0, m3[i]);
    }


    // Operator ==
    EXPECT_TRUE(m3 == Matrix3x3<FLOAT>::ZERO);
    EXPECT_TRUE(m3 != Matrix3x3<FLOAT>::IDENTITY);
}
