#include "gtest/gtest.h"
#include "Matrix4x4.h"
#include "Vector4D.h"

#undef FLOAT
#define FLOAT double

using namespace nut;

class Matrix4x4DoubleTest : public ::testing::Test
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

TEST_F(Matrix4x4DoubleTest, constructors)
{
    // Default constructor
    Matrix4x4<FLOAT> m1;
    
    for (int i = 0; i < 16; ++i)
    {
        if (i == 0 || i == 5 || i == 10 || i == 15)
        {
            EXPECT_DOUBLE_EQ(1.0, m1[i]);
        }
        else
        {
            EXPECT_DOUBLE_EQ(0.0, m1[i]);
        }
    }

    // Constructor
    Matrix4x4<FLOAT> m2(11, 12, 13, 14,
                       21, 22, 23, 24,
                       31, 32, 33, 34,
                       41, 42, 43, 44);

    EXPECT_DOUBLE_EQ(11, m2[ 0]);
    EXPECT_DOUBLE_EQ(21, m2[ 1]);
    EXPECT_DOUBLE_EQ(31, m2[ 2]);
    EXPECT_DOUBLE_EQ(41, m2[ 3]);
    EXPECT_DOUBLE_EQ(12, m2[ 4]);
    EXPECT_DOUBLE_EQ(22, m2[ 5]);
    EXPECT_DOUBLE_EQ(32, m2[ 6]);
    EXPECT_DOUBLE_EQ(42, m2[ 7]);
    EXPECT_DOUBLE_EQ(13, m2[ 8]);
    EXPECT_DOUBLE_EQ(23, m2[ 9]);
    EXPECT_DOUBLE_EQ(33, m2[10]);
    EXPECT_DOUBLE_EQ(43, m2[11]);
    EXPECT_DOUBLE_EQ(14, m2[12]);
    EXPECT_DOUBLE_EQ(24, m2[13]);
    EXPECT_DOUBLE_EQ(34, m2[14]);
    EXPECT_DOUBLE_EQ(44, m2[15]);

    // Copy constructor
    m1 = m2;

    EXPECT_DOUBLE_EQ(11, m1[ 0]);
    EXPECT_DOUBLE_EQ(21, m1[ 1]);
    EXPECT_DOUBLE_EQ(31, m1[ 2]);
    EXPECT_DOUBLE_EQ(41, m1[ 3]);
    EXPECT_DOUBLE_EQ(12, m1[ 4]);
    EXPECT_DOUBLE_EQ(22, m1[ 5]);
    EXPECT_DOUBLE_EQ(32, m1[ 6]);
    EXPECT_DOUBLE_EQ(42, m1[ 7]);
    EXPECT_DOUBLE_EQ(13, m1[ 8]);
    EXPECT_DOUBLE_EQ(23, m1[ 9]);
    EXPECT_DOUBLE_EQ(33, m1[10]);
    EXPECT_DOUBLE_EQ(43, m1[11]);
    EXPECT_DOUBLE_EQ(14, m1[12]);
    EXPECT_DOUBLE_EQ(24, m1[13]);
    EXPECT_DOUBLE_EQ(34, m1[14]);
    EXPECT_DOUBLE_EQ(44, m1[15]);
}



// Methods

TEST_F(Matrix4x4DoubleTest, clear)
{
    Matrix4x4<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    m.clear();

    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(Matrix4x4<FLOAT>::ZERO[i], m[i]);
    }
}



TEST_F(Matrix4x4DoubleTest, setIdentity)
{
    Matrix4x4<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    m.setIdentity();

    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(Matrix4x4<FLOAT>::IDENTITY[i], m[i]);
    }
}



TEST_F(Matrix4x4DoubleTest, inverse)
{
    Matrix4x4<FLOAT> inv;

    // Identity inverse
    Matrix4x4<FLOAT> m;

    inv = m.inverse();

    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(Matrix4x4<FLOAT>::IDENTITY[i], m[i]);
    }

    // General inverse
    Matrix4x4<FLOAT> n(10,  -9, -12,  2.5,
                       7, -12,  11,  7,
                     -10,  10,   3, 32,
                      -1,   1,   3,  2);

    inv = n.inverse();

    Matrix4x4<FLOAT> res(0.276413, -0.144717, -0.0983526, 1.73464,
                         0.187629, -0.162474, -0.0674756, 1.41373,
                         0.0118378, 0.00236756, -0.0263392, 0.398343,
                         0.0266351, 0.00532702, 0.0240702, 0.0629378);

    EXPECT_NEAR(res[ 0], inv[ 0], 1e-6);
    EXPECT_NEAR(res[ 1], inv[ 1], 1e-6);
    EXPECT_NEAR(res[ 2], inv[ 2], 1e-7);
    EXPECT_NEAR(res[ 3], inv[ 3], 1e-9);
    EXPECT_NEAR(res[ 4], inv[ 4], 1e-6);
    EXPECT_NEAR(res[ 5], inv[ 5], 1e-6);
    EXPECT_NEAR(res[ 6], inv[ 6], 1e-8);
    EXPECT_NEAR(res[ 7], inv[ 7], 1e-9);
    EXPECT_NEAR(res[ 8], inv[ 8], 1e-7);
    EXPECT_NEAR(res[ 9], inv[ 9], 1e-7);
    EXPECT_NEAR(res[10], inv[10], 1e-7);
    EXPECT_NEAR(res[11], inv[11], 1e-7);
    EXPECT_NEAR(res[12], inv[12], 1e-5);
    EXPECT_NEAR(res[13], inv[13], 1e-5);
    EXPECT_NEAR(res[14], inv[14], 1e-6);
    EXPECT_NEAR(res[15], inv[15], 1e-7);

    // Affine inverse
    Matrix4x4<FLOAT> o(10,  -9, -12,  2.5,
                       7, -12,  11,  7,
                     -10,  10,   3, 32,
                       0,   0,   0,  1);

    inv = o.inverse();

    Matrix4x4<FLOAT> resaff(-0.45768, -0.291536, -0.761755, 27.5611,
                            -0.410658, -0.282132, -0.60815, 22.4624,
                            -0.15674, -0.031348, -0.178683, 6.32915,
                             0,        0,         0,        1);

    EXPECT_NEAR(resaff[ 0], inv[ 0], 1e-6);
    EXPECT_NEAR(resaff[ 1], inv[ 1], 1e-6);
    EXPECT_NEAR(resaff[ 2], inv[ 2], 1e-6);
    EXPECT_NEAR(resaff[ 3], inv[ 3], 1e-20);
    EXPECT_NEAR(resaff[ 4], inv[ 4], 1e-7);
    EXPECT_NEAR(resaff[ 5], inv[ 5], 1e-6);
    EXPECT_NEAR(resaff[ 6], inv[ 6], 1e-7);
    EXPECT_NEAR(resaff[ 7], inv[ 7], 1e-20);
    EXPECT_NEAR(resaff[ 8], inv[ 8], 1e-6);
    EXPECT_NEAR(resaff[ 9], inv[ 9], 1e-6);
    EXPECT_NEAR(resaff[10], inv[10], 1e-6);
    EXPECT_NEAR(resaff[11], inv[11], 1e-20);
    EXPECT_NEAR(resaff[12], inv[12], 1e-4);
    EXPECT_NEAR(resaff[13], inv[13], 1e-4);
    EXPECT_NEAR(resaff[14], inv[14], 1e-5);
    EXPECT_NEAR(resaff[15], inv[15], 1e-20);
}



TEST_F(Matrix4x4DoubleTest, determinant)
{
    // Identity determinant
    Matrix4x4<FLOAT> m;

    EXPECT_DOUBLE_EQ(1, m.determinant());

    // General determinant
    Matrix4x4<FLOAT> n(10,  -9, -12,  2.5,
                       7, -12,  11,  7,
                     -10,  10,   3, 32,
                      -1,   1,   3,  2);

    EXPECT_NEAR(5068.5, n.determinant(), 1e-20);

    // Affine determinant
    Matrix4x4<FLOAT> o(10,  -9, -12,  2.5,
                       7, -12,  11,  7,
                     -10,  10,   3, 32,
                       0,   0,   0,  1);

    EXPECT_NEAR(319, o.determinant(), 1e-20);
}



TEST_F(Matrix4x4DoubleTest, transpose)
{
    // Identity determinant
    Matrix4x4<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    Matrix4x4<FLOAT> t = m.transpose();
    
    Matrix4x4<FLOAT> n(11, 21, 31, 41,
                      12, 22, 32, 42,
                      13, 23, 33, 43,
                      14, 24, 34, 44);

    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(n[i], t[i]);
    }
}



TEST_F(Matrix4x4DoubleTest, constants)
{
    // Identity matrix
    for (int i = 0; i < 16; ++i)
    {
        if (i == 0 || i == 5 || i == 10 || i == 15)
        {
            EXPECT_DOUBLE_EQ(1.0, Matrix4x4<FLOAT>::IDENTITY[i]);
        }
        else
        {
            EXPECT_DOUBLE_EQ(0.0, Matrix4x4<FLOAT>::IDENTITY[i]);
        }
    }

    // Zero matrix
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(0.0, Matrix4x4<FLOAT>::ZERO[i]);
    }
}



TEST_F(Matrix4x4DoubleTest, operators)
{
    Matrix4x4<FLOAT> m(11, 12, 13, 14,
                       21, 22, 23, 24,
                       31, 32, 33, 34,
                       41, 42, 43, 44);

    // Operator []
    m[0] = m[15];
    EXPECT_DOUBLE_EQ(44, m[0]);


    // Operator *
    m[0] = 11;
    Vector4D<FLOAT> u(1, 1, 1, 1);
    
    u = m * u;
    
    EXPECT_DOUBLE_EQ(11 + 12 + 13 + 14, u.x);
    EXPECT_DOUBLE_EQ(21 + 22 + 23 + 24, u.y);
    EXPECT_DOUBLE_EQ(31 + 32 + 33 + 34, u.z);
    EXPECT_DOUBLE_EQ(41 + 42 + 43 + 44, u.w);

    Matrix4x4<FLOAT> n = 2 * m;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(2 * m[i], n[i]);
    }

    n = m * 2;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(2 * m[i], n[i]);
    }
    
    n *= 2;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(2 * 2 * m[i], n[i]);
    }
    
    Matrix4x4<FLOAT> m1( 1,  2,  3,  4,
                         5,  6,  7,  8,
                         9, 10, 11, 12,
                        13, 14, 15, 16);
    
    Matrix4x4<FLOAT> m2( 2,  4,  6,  8,
                       10, 12, 14, 16,
                       18, 20, 22, 24,
                       26, 28, 30, 32);
    
    n = m1 * m2;

    EXPECT_DOUBLE_EQ(180, n[ 0]);
    EXPECT_DOUBLE_EQ(200, n[ 4]);
    EXPECT_DOUBLE_EQ(220, n[ 8]);
    EXPECT_DOUBLE_EQ(240, n[12]);
    
    EXPECT_DOUBLE_EQ(404, n[ 1]);
    EXPECT_DOUBLE_EQ(456, n[ 5]);
    EXPECT_DOUBLE_EQ(508, n[ 9]);
    EXPECT_DOUBLE_EQ(560, n[13]);
    
    EXPECT_DOUBLE_EQ(628, n[ 2]);
    EXPECT_DOUBLE_EQ(712, n[ 6]);
    EXPECT_DOUBLE_EQ(796, n[10]);
    EXPECT_DOUBLE_EQ(880, n[14]);
    
    EXPECT_DOUBLE_EQ(852, n[ 3]);
    EXPECT_DOUBLE_EQ(968, n[ 7]);
    EXPECT_DOUBLE_EQ(1084, n[11]);
    EXPECT_DOUBLE_EQ(1200, n[15]);

    m1 *= m2;

    EXPECT_DOUBLE_EQ(180, m1[ 0]);
    EXPECT_DOUBLE_EQ(200, m1[ 4]);
    EXPECT_DOUBLE_EQ(220, m1[ 8]);
    EXPECT_DOUBLE_EQ(240, m1[12]);
    
    EXPECT_DOUBLE_EQ(404, m1[ 1]);
    EXPECT_DOUBLE_EQ(456, m1[ 5]);
    EXPECT_DOUBLE_EQ(508, m1[ 9]);
    EXPECT_DOUBLE_EQ(560, m1[13]);
    
    EXPECT_DOUBLE_EQ(628, m1[ 2]);
    EXPECT_DOUBLE_EQ(712, m1[ 6]);
    EXPECT_DOUBLE_EQ(796, m1[10]);
    EXPECT_DOUBLE_EQ(880, m1[14]);
    
    EXPECT_DOUBLE_EQ(852, m1[ 3]);
    EXPECT_DOUBLE_EQ(968, m1[ 7]);
    EXPECT_DOUBLE_EQ(1084, m1[11]);
    EXPECT_DOUBLE_EQ(1200, m1[15]);
    
    // Operator /
    
    m1 = m2 / 2.0;
    
    EXPECT_DOUBLE_EQ( 1, m1[ 0]);
    EXPECT_DOUBLE_EQ( 2, m1[ 4]);
    EXPECT_DOUBLE_EQ( 3, m1[ 8]);
    EXPECT_DOUBLE_EQ( 4, m1[12]);
    
    EXPECT_DOUBLE_EQ( 5, m1[ 1]);
    EXPECT_DOUBLE_EQ( 6, m1[ 5]);
    EXPECT_DOUBLE_EQ( 7, m1[ 9]);
    EXPECT_DOUBLE_EQ( 8, m1[13]);
    
    EXPECT_DOUBLE_EQ( 9, m1[ 2]);
    EXPECT_DOUBLE_EQ(10, m1[ 6]);
    EXPECT_DOUBLE_EQ(11, m1[10]);
    EXPECT_DOUBLE_EQ(12, m1[14]);
    
    EXPECT_DOUBLE_EQ(13, m1[ 3]);
    EXPECT_DOUBLE_EQ(14, m1[ 7]);
    EXPECT_DOUBLE_EQ(15, m1[11]);
    EXPECT_DOUBLE_EQ(16, m1[15]);
    
    m2 /= 2;
    
    EXPECT_DOUBLE_EQ( 1, m2[ 0]);
    EXPECT_DOUBLE_EQ( 2, m2[ 4]);
    EXPECT_DOUBLE_EQ( 3, m2[ 8]);
    EXPECT_DOUBLE_EQ( 4, m2[12]);
    
    EXPECT_DOUBLE_EQ( 5, m2[ 1]);
    EXPECT_DOUBLE_EQ( 6, m2[ 5]);
    EXPECT_DOUBLE_EQ( 7, m2[ 9]);
    EXPECT_DOUBLE_EQ( 8, m2[13]);
    
    EXPECT_DOUBLE_EQ( 9, m2[ 2]);
    EXPECT_DOUBLE_EQ(10, m2[ 6]);
    EXPECT_DOUBLE_EQ(11, m2[10]);
    EXPECT_DOUBLE_EQ(12, m2[14]);
    
    EXPECT_DOUBLE_EQ(13, m2[ 3]);
    EXPECT_DOUBLE_EQ(14, m2[ 7]);
    EXPECT_DOUBLE_EQ(15, m2[11]);
    EXPECT_DOUBLE_EQ(16, m2[15]);
    
    // Operator +
    Matrix4x4<FLOAT> m3( 1,  2,  3,  4,
                         5,  6,  7,  8,
                         9, 10, 11, 12,
                        13, 14, 15, 16);
    
    Matrix4x4<FLOAT> m4( 2,  4,  6,  8,
                        10, 12, 14, 16,
                        18, 20, 22, 24,
                        26, 28, 30, 32);
    
    m = m3 + m3;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(m4[i], m[i]);
    }

    m3 += m3;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(m4[i], m3[i]);
    }

    
    // Operator -
    m = m3 - m3;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(0, m[i]);
    }

    m3 -= m3;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_DOUBLE_EQ(0, m3[i]);
    }

    
    // Operator ==
    EXPECT_TRUE(m3 == Matrix4x4<FLOAT>::ZERO);
    EXPECT_TRUE(m3 != Matrix4x4<FLOAT>::IDENTITY);
}
