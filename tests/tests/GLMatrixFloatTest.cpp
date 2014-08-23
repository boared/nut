#include "gtest/gtest.h"
#include "GLMatrix.h"
#include "Vector3D.h"
#include "Vector4D.h"

#undef FLOAT
#define FLOAT float

using namespace nut;

class GLMatrixFloatTest : public ::testing::Test
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

TEST_F(GLMatrixFloatTest, constructors)
{
    // Default constructor
    GLMatrix<FLOAT> m1;
    
    for (int i = 0; i < 16; ++i)
    {
        if (i == 0 || i == 5 || i == 10 || i == 15)
        {
            EXPECT_FLOAT_EQ(1.0f, m1[i]);
        }
        else
        {
            EXPECT_FLOAT_EQ(0.0f, m1[i]);
        }
    }

    // Constructor
    GLMatrix<FLOAT> m2(11, 12, 13, 14,
                       21, 22, 23, 24,
                       31, 32, 33, 34,
                       41, 42, 43, 44);

    EXPECT_FLOAT_EQ(11, m2[ 0]);
    EXPECT_FLOAT_EQ(21, m2[ 1]);
    EXPECT_FLOAT_EQ(31, m2[ 2]);
    EXPECT_FLOAT_EQ(41, m2[ 3]);
    EXPECT_FLOAT_EQ(12, m2[ 4]);
    EXPECT_FLOAT_EQ(22, m2[ 5]);
    EXPECT_FLOAT_EQ(32, m2[ 6]);
    EXPECT_FLOAT_EQ(42, m2[ 7]);
    EXPECT_FLOAT_EQ(13, m2[ 8]);
    EXPECT_FLOAT_EQ(23, m2[ 9]);
    EXPECT_FLOAT_EQ(33, m2[10]);
    EXPECT_FLOAT_EQ(43, m2[11]);
    EXPECT_FLOAT_EQ(14, m2[12]);
    EXPECT_FLOAT_EQ(24, m2[13]);
    EXPECT_FLOAT_EQ(34, m2[14]);
    EXPECT_FLOAT_EQ(44, m2[15]);

    // Copy constructor
    m1 = m2;

    EXPECT_FLOAT_EQ(11, m1[ 0]);
    EXPECT_FLOAT_EQ(21, m1[ 1]);
    EXPECT_FLOAT_EQ(31, m1[ 2]);
    EXPECT_FLOAT_EQ(41, m1[ 3]);
    EXPECT_FLOAT_EQ(12, m1[ 4]);
    EXPECT_FLOAT_EQ(22, m1[ 5]);
    EXPECT_FLOAT_EQ(32, m1[ 6]);
    EXPECT_FLOAT_EQ(42, m1[ 7]);
    EXPECT_FLOAT_EQ(13, m1[ 8]);
    EXPECT_FLOAT_EQ(23, m1[ 9]);
    EXPECT_FLOAT_EQ(33, m1[10]);
    EXPECT_FLOAT_EQ(43, m1[11]);
    EXPECT_FLOAT_EQ(14, m1[12]);
    EXPECT_FLOAT_EQ(24, m1[13]);
    EXPECT_FLOAT_EQ(34, m1[14]);
    EXPECT_FLOAT_EQ(44, m1[15]);
}



// Methods

TEST_F(GLMatrixFloatTest, clear)
{
    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    m.clear();

    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(GLMatrix<FLOAT>::ZERO[i], m[i]);
    }
}



TEST_F(GLMatrixFloatTest, setIdentity)
{
    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    m.setIdentity();

    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(GLMatrix<FLOAT>::IDENTITY[i], m[i]);
    }
}



TEST_F(GLMatrixFloatTest, isAffine)
{
    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    EXPECT_TRUE(!m.isAffine());

    GLMatrix<FLOAT> n(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                       0,  0,  0,  1);

    EXPECT_TRUE(n.isAffine());

    GLMatrix<FLOAT> o( 0, 12, 13, 14,
                       0, 22, 23, 24,
                       0, 32, 33, 34,
                       1, 42, 43, 44);

    EXPECT_TRUE(!o.isAffine());

    GLMatrix<FLOAT> p(11, 12, 13,  0,
                      21, 22, 23,  0,
                      31, 32, 33,  0,
                      41, 42, 43,  1);

    EXPECT_TRUE(!p.isAffine());
}



TEST_F(GLMatrixFloatTest, inverse)
{
    GLMatrix<FLOAT> inv;

    // Identity inverse
    GLMatrix<FLOAT> m;

    inv = m.inverse();

    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(GLMatrix<FLOAT>::IDENTITY[i], m[i]);
    }

    // General inverse
    GLMatrix<FLOAT> n(10,  -9, -12,  2.5,
                       7, -12,  11,  7,
                     -10,  10,   3, 32,
                      -1,   1,   3,  2);

    inv = n.inverse();

    GLMatrix<FLOAT> res(0.276413, -0.144717, -0.0983526, 1.73464,
                        0.187629, -0.162474, -0.0674756, 1.41373,
                        0.0118378, 0.00236756, -0.0263392, 0.398343,
                        0.0266351, 0.00532702, 0.0240702, 0.0629378);

    EXPECT_NEAR(res[ 0], inv[ 0], 1e-6);
    EXPECT_NEAR(res[ 1], inv[ 1], 1e-6);
    EXPECT_NEAR(res[ 2], inv[ 2], 1e-7);
    EXPECT_NEAR(res[ 3], inv[ 3], 1e-7);
    EXPECT_NEAR(res[ 4], inv[ 4], 1e-6);
    EXPECT_NEAR(res[ 5], inv[ 5], 1e-6);
    EXPECT_NEAR(res[ 6], inv[ 6], 1e-7);
    EXPECT_NEAR(res[ 7], inv[ 7], 1e-7);
    EXPECT_NEAR(res[ 8], inv[ 8], 1e-7);
    EXPECT_NEAR(res[ 9], inv[ 9], 1e-7);
    EXPECT_NEAR(res[10], inv[10], 1e-7);
    EXPECT_NEAR(res[11], inv[11], 1e-7);
    EXPECT_NEAR(res[12], inv[12], 1e-5);
    EXPECT_NEAR(res[13], inv[13], 1e-5);
    EXPECT_NEAR(res[14], inv[14], 1e-6);
    EXPECT_NEAR(res[15], inv[15], 1e-7);

    // Affine inverse
    GLMatrix<FLOAT> o(10,  -9, -12,  2.5,
                       7, -12,  11,  7,
                     -10,  10,   3, 32,
                       0,   0,   0,  1);

    inv = o.inverse();

    GLMatrix<FLOAT> resaff(-0.45768, -0.291536, -0.761755, 27.5611,
                           -0.410658, -0.282132, -0.60815, 22.4624,
                           -0.15674, -0.031348, -0.178683, 6.32915,
                            0,        0,         0,        1);

    EXPECT_NEAR(resaff[ 0], inv[ 0], 1e-6);
    EXPECT_NEAR(resaff[ 1], inv[ 1], 1e-6);
    EXPECT_NEAR(resaff[ 2], inv[ 2], 1e-6);
    EXPECT_NEAR(resaff[ 3], inv[ 3], 1e-7);
    EXPECT_NEAR(resaff[ 4], inv[ 4], 1e-7);
    EXPECT_NEAR(resaff[ 5], inv[ 5], 1e-6);
    EXPECT_NEAR(resaff[ 6], inv[ 6], 1e-7);
    EXPECT_NEAR(resaff[ 7], inv[ 7], 1e-7);
    EXPECT_NEAR(resaff[ 8], inv[ 8], 1e-6);
    EXPECT_NEAR(resaff[ 9], inv[ 9], 1e-6);
    EXPECT_NEAR(resaff[10], inv[10], 1e-6);
    EXPECT_NEAR(resaff[11], inv[11], 1e-7);
    EXPECT_NEAR(resaff[12], inv[12], 1e-4);
    EXPECT_NEAR(resaff[13], inv[13], 1e-4);
    EXPECT_NEAR(resaff[14], inv[14], 1e-5);
    EXPECT_NEAR(resaff[15], inv[15], 1e-7);
}



TEST_F(GLMatrixFloatTest, determinant)
{
    // Identity determinant
    GLMatrix<FLOAT> m;

    EXPECT_FLOAT_EQ(1, m.determinant());

    // General determinant
    GLMatrix<FLOAT> n(10,  -9, -12,  2.5,
                       7, -12,  11,  7,
                     -10,  10,   3, 32,
                      -1,   1,   3,  2);

    EXPECT_NEAR(5068.5, n.determinant(), 1e-10);

    // Affine determinant
    GLMatrix<FLOAT> o(10,  -9, -12,  2.5,
                       7, -12,  11,  7,
                     -10,  10,   3, 32,
                       0,   0,   0,  1);

    EXPECT_NEAR(319, o.determinant(), 1e-10);
}



TEST_F(GLMatrixFloatTest, transpose)
{
    // Identity determinant
    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    GLMatrix<FLOAT> t = m.transpose();
    
    GLMatrix<FLOAT> n(11, 21, 31, 41,
                      12, 22, 32, 42,
                      13, 23, 33, 43,
                      14, 24, 34, 44);

    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(n[i], t[i]);
    }
}



TEST_F(GLMatrixFloatTest, setRotation)
{
    Vector3D<FLOAT> v, v1(1, 0, 0), v2(1, 1, 1), v3(-3.14, 5.4, -2.3);
    Vector4D<FLOAT> u, u1(1, 0, 0, 1), u2(1, 1, 1, 1), u3(-3.14, 5.4, -2.3, 1);

    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    // 30 degrees, 120 degrees, 15 degrees
    m.setRotation(0.523598776, 2.0943951, 0.261799388);

    // v1
    v = m * v1;
    EXPECT_NEAR(-0.4829629, v.x, 1e-7);
    EXPECT_NEAR(-0.1294095, v.y, 1e-7);
    EXPECT_NEAR(-0.8660253, v.z, 1e-7);

    // v2
    v = m * v2;
    EXPECT_NEAR(0.56500512, v.x, 1e-7);
    EXPECT_NEAR(0.53033, v.y, 1e-7);
    EXPECT_NEAR(-1.5490381, v.z, 1e-7);
    
    // v3
    v = m * v3;
    EXPECT_NEAR(0.60085713, v.x, 1e-7);
    EXPECT_NEAR(6.19307422, v.y, 1e-7);
    EXPECT_NEAR(2.365249, v.z, 1e-7);
    
    // u1
    u = m * u1;
    EXPECT_NEAR(-0.4829629, u.x, 1e-7);
    EXPECT_NEAR(-0.1294095, u.y, 1e-7);
    EXPECT_NEAR(-0.8660253, u.z, 1e-7);
    EXPECT_NEAR(1.00000000, u.w, 1e-7);

    // u2
    u = m * u2;
    EXPECT_NEAR(0.56500512, u.x, 1e-7);
    EXPECT_NEAR(0.53033, u.y, 1e-7);
    EXPECT_NEAR(-1.5490381, u.z, 1e-7);
    EXPECT_NEAR(1.00000000, u.w, 1e-7);
    
    // u3
    u = m * u3;
    EXPECT_NEAR(0.60085713, u.x, 1e-7);
    EXPECT_NEAR(6.19307422, u.y, 1e-7);
    EXPECT_NEAR(2.365249, u.z, 1e-7);
    EXPECT_NEAR(1.000000, u.w, 1e-7);
}



TEST_F(GLMatrixFloatTest, setScale)
{
    Vector3D<FLOAT> v, v1(1, 0, 0), v2(0, 1, 0), v3(0, 0, 1), v4(1, 1, 1);
    Vector4D<FLOAT> u, u1(1, 0, 0, 1), u2(0, 1, 0, 1), u3(0, 0, 1, 1), u4(1, 1, 1, 1);

    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    m.setScale(5, 3, 2);

    // v1
    v = m * v1;
    EXPECT_NEAR(5, v.x, 1e-7);
    EXPECT_NEAR(0, v.y, 1e-7);
    EXPECT_NEAR(0, v.z, 1e-7);

    // v2
    v = m * v2;
    EXPECT_NEAR(0, v.x, 1e-7);
    EXPECT_NEAR(3, v.y, 1e-7);
    EXPECT_NEAR(0, v.z, 1e-7);
    
    // v3
    v = m * v3;
    EXPECT_NEAR(0, v.x, 1e-7);
    EXPECT_NEAR(0, v.y, 1e-7);
    EXPECT_NEAR(2, v.z, 1e-7);
    
    // v4
    v = m * v4;
    EXPECT_NEAR(5, v.x, 1e-7);
    EXPECT_NEAR(3, v.y, 1e-7);
    EXPECT_NEAR(2, v.z, 1e-7);
    
    // u1
    u = m * u1;
    EXPECT_NEAR(5, u.x, 1e-7);
    EXPECT_NEAR(0, u.y, 1e-7);
    EXPECT_NEAR(0, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);

    // u2
    u = m * u2;
    EXPECT_NEAR(0, u.x, 1e-7);
    EXPECT_NEAR(3, u.y, 1e-7);
    EXPECT_NEAR(0, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);
    
    // u3
    u = m * u3;
    EXPECT_NEAR(0, u.x, 1e-7);
    EXPECT_NEAR(0, u.y, 1e-7);
    EXPECT_NEAR(2, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);

    // u4
    u = m * u4;
    EXPECT_NEAR(5, u.x, 1e-7);
    EXPECT_NEAR(3, u.y, 1e-7);
    EXPECT_NEAR(2, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);
}



TEST_F(GLMatrixFloatTest, setTranslation)
{
    Vector3D<FLOAT> v, v1(1, 0, 0), v2(0, 1, 0), v3(0, 0, 1), v4(1, 1, 1);
    Vector4D<FLOAT> u, u1(1, 0, 0, 1), u2(0, 1, 0, 1), u3(0, 0, 1, 1), u4(1, 1, 1, 1);

    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    m.setTranslation(5, 3, 2);

    // v1
    v = m * v1;
    EXPECT_NEAR(v1.x + 5, v.x, 1e-7);
    EXPECT_NEAR(v1.y + 3, v.y, 1e-7);
    EXPECT_NEAR(v1.z + 2, v.z, 1e-7);

    // v2
    v = m * v2;
    EXPECT_NEAR(v2.x + 5, v.x, 1e-7);
    EXPECT_NEAR(v2.y + 3, v.y, 1e-7);
    EXPECT_NEAR(v2.z + 2, v.z, 1e-7);
    
    // v3
    v = m * v3;
    EXPECT_NEAR(v3.x + 5, v.x, 1e-7);
    EXPECT_NEAR(v3.y + 3, v.y, 1e-7);
    EXPECT_NEAR(v3.z + 2, v.z, 1e-7);
    
    // v4
    v = m * v4;
    EXPECT_NEAR(v4.x + 5, v.x, 1e-7);
    EXPECT_NEAR(v4.y + 3, v.y, 1e-7);
    EXPECT_NEAR(v4.z + 2, v.z, 1e-7);
    
    // u1
    u = m * u1;
    EXPECT_NEAR(u1.x + 5, u.x, 1e-7);
    EXPECT_NEAR(u1.y + 3, u.y, 1e-7);
    EXPECT_NEAR(u1.z + 2, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);

    // u2
    u = m * u2;
    EXPECT_NEAR(u2.x + 5, u.x, 1e-7);
    EXPECT_NEAR(u2.y + 3, u.y, 1e-7);
    EXPECT_NEAR(u2.z + 2, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);
    
    // u3
    u = m * u3;
    EXPECT_NEAR(u3.x + 5, u.x, 1e-7);
    EXPECT_NEAR(u3.y + 3, u.y, 1e-7);
    EXPECT_NEAR(u3.z + 2, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);

    // u4
    u = m * u4;
    EXPECT_NEAR(u4.x + 5, u.x, 1e-7);
    EXPECT_NEAR(u4.y + 3, u.y, 1e-7);
    EXPECT_NEAR(u4.z + 2, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);
}



TEST_F(GLMatrixFloatTest, rotate)
{
    Vector3D<FLOAT> v, v1(-3.14, 5.4, -2.3);
    Vector4D<FLOAT> u, u1(-3.14, 5.4, -2.3, 1);

    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    // 30 degrees, 120 degrees, 15 degrees
    m.setRotation(0.523598776, 2.0943951, 0.261799388);

    // 10 degrees, 5 degrees, 60 degrees
    m.rotate(0.174532925, 0.0872664626, 1.04719755);

    // v1
    v = m * v1;
    EXPECT_NEAR(-4.47852706, v.x, 1e-7);
    EXPECT_NEAR(3.619496107, v.y, 1e-7);
    EXPECT_NEAR(3.339407205, v.z, 1e-7);
    
    // u1
    u = m * u1;
    EXPECT_NEAR(-4.47852706, u.x, 1e-7);
    EXPECT_NEAR(3.619496107, u.y, 1e-7);
    EXPECT_NEAR(3.339407205, u.z, 1e-7);
    EXPECT_NEAR(1.000000, u.w, 1e-7);
}



TEST_F(GLMatrixFloatTest, scale)
{
    Vector3D<FLOAT> v, v1(1, 0, 0), v2(0, 1, 0), v3(0, 0, 1), v4(1, 1, 1);
    Vector4D<FLOAT> u, u1(1, 0, 0, 1), u2(0, 1, 0, 1), u3(0, 0, 1, 1), u4(1, 1, 1, 1);

    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    m.setScale(5, 3, 2);
    
    m.scale(-10, 1, 4);

    // v1
    v = m * v1;
    EXPECT_NEAR(v1.x * 5 * -10, v.x, 1e-7);
    EXPECT_NEAR(v1.y * 3 * 1, v.y, 1e-7);
    EXPECT_NEAR(v1.z * 2 * 4, v.z, 1e-7);

    // v2
    v = m * v2;
    EXPECT_NEAR(v2.x * 5 * -10, v.x, 1e-7);
    EXPECT_NEAR(v2.y * 3 * 1, v.y, 1e-7);
    EXPECT_NEAR(v2.z * 2 * 4, v.z, 1e-7);
    
    // v3
    v = m * v3;
    EXPECT_NEAR(v3.x * 5 * -10, v.x, 1e-7);
    EXPECT_NEAR(v3.y * 3 * 1, v.y, 1e-7);
    EXPECT_NEAR(v3.z * 2 * 4, v.z, 1e-7);
    
    // v4
    v = m * v4;
    EXPECT_NEAR(v4.x * 5 * -10, v.x, 1e-7);
    EXPECT_NEAR(v4.y * 3 * 1, v.y, 1e-7);
    EXPECT_NEAR(v4.z * 2 * 4, v.z, 1e-7);
    
    // u1
    u = m * u1;
    EXPECT_NEAR(u1.x * 5 * -10, u.x, 1e-7);
    EXPECT_NEAR(u1.y * 3 * 1, u.y, 1e-7);
    EXPECT_NEAR(u1.z * 2 * 4, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);

    // u2
    u = m * u2;
    EXPECT_NEAR(u2.x * 5 * -10, u.x, 1e-7);
    EXPECT_NEAR(u2.y * 3 * 1, u.y, 1e-7);
    EXPECT_NEAR(u2.z * 2 * 4, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);
    
    // u3
    u = m * u3;
    EXPECT_NEAR(u3.x * 5 * -10, u.x, 1e-7);
    EXPECT_NEAR(u3.y * 3 * 1, u.y, 1e-7);
    EXPECT_NEAR(u3.z * 2 * 4, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);

    // u4
    u = m * u4;
    EXPECT_NEAR(u4.x * 5 * -10, u.x, 1e-7);
    EXPECT_NEAR(u4.y * 3 * 1, u.y, 1e-7);
    EXPECT_NEAR(u4.z * 2 * 4, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);
}



TEST_F(GLMatrixFloatTest, translate)
{
    Vector3D<FLOAT> v, v1(1, 0, 0), v2(0, 1, 0), v3(0, 0, 1), v4(1, 1, 1);
    Vector4D<FLOAT> u, u1(1, 0, 0, 1), u2(0, 1, 0, 1), u3(0, 0, 1, 1), u4(1, 1, 1, 1);

    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    m.setTranslation(5, 3, 2);

    m.translate(-10, -4, -6);

    // v1
    v = m * v1;
    EXPECT_NEAR(v1.x + 5 - 10, v.x, 1e-7);
    EXPECT_NEAR(v1.y + 3 - 4, v.y, 1e-7);
    EXPECT_NEAR(v1.z + 2 - 6, v.z, 1e-7);

    // v2
    v = m * v2;
    EXPECT_NEAR(v2.x + 5 - 10, v.x, 1e-7);
    EXPECT_NEAR(v2.y + 3 - 4, v.y, 1e-7);
    EXPECT_NEAR(v2.z + 2 - 6, v.z, 1e-7);
    
    // v3
    v = m * v3;
    EXPECT_NEAR(v3.x + 5 - 10, v.x, 1e-7);
    EXPECT_NEAR(v3.y + 3 - 4, v.y, 1e-7);
    EXPECT_NEAR(v3.z + 2 - 6, v.z, 1e-7);
    
    // v4
    v = m * v4;
    EXPECT_NEAR(v4.x + 5 - 10, v.x, 1e-7);
    EXPECT_NEAR(v4.y + 3 - 4, v.y, 1e-7);
    EXPECT_NEAR(v4.z + 2 - 6, v.z, 1e-7);
    
    // u1
    u = m * u1;
    EXPECT_NEAR(u1.x + 5 - 10, u.x, 1e-7);
    EXPECT_NEAR(u1.y + 3 - 4, u.y, 1e-7);
    EXPECT_NEAR(u1.z + 2 - 6, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);

    // u2
    u = m * u2;
    EXPECT_NEAR(u2.x + 5 - 10, u.x, 1e-7);
    EXPECT_NEAR(u2.y + 3 - 4, u.y, 1e-7);
    EXPECT_NEAR(u2.z + 2 - 6, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);
    
    // u3
    u = m * u3;
    EXPECT_NEAR(u3.x + 5 - 10, u.x, 1e-7);
    EXPECT_NEAR(u3.y + 3 - 4, u.y, 1e-7);
    EXPECT_NEAR(u3.z + 2 - 6, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);

    // u4
    u = m * u4;
    EXPECT_NEAR(u4.x + 5 - 10, u.x, 1e-7);
    EXPECT_NEAR(u4.y + 3 - 4, u.y, 1e-7);
    EXPECT_NEAR(u4.z + 2 - 6, u.z, 1e-7);
    EXPECT_NEAR(1, u.w, 1e-7);
}



TEST_F(GLMatrixFloatTest, constants)
{
    // Identity matrix
    for (int i = 0; i < 16; ++i)
    {
        if (i == 0 || i == 5 || i == 10 || i == 15)
        {
            EXPECT_FLOAT_EQ(1.0f, GLMatrix<FLOAT>::IDENTITY[i]);
        }
        else
        {
            EXPECT_FLOAT_EQ(0.0f, GLMatrix<FLOAT>::IDENTITY[i]);
        }
    }

    // Zero matrix
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(0.0f, GLMatrix<FLOAT>::ZERO[i]);
    }

    // Zero affine matrix
    for (int i = 0; i < 16; ++i)
    {
        if (i == 15)
        {
            EXPECT_FLOAT_EQ(1.0f, GLMatrix<FLOAT>::ZEROAFFINE[i]);
        }
        else
        {
            EXPECT_FLOAT_EQ(0.0f, GLMatrix<FLOAT>::ZEROAFFINE[i]);
        }
    }
}



TEST_F(GLMatrixFloatTest, operators)
{
    GLMatrix<FLOAT> m(11, 12, 13, 14,
                      21, 22, 23, 24,
                      31, 32, 33, 34,
                      41, 42, 43, 44);

    // Operator []
    m[0] = m[15];
    EXPECT_FLOAT_EQ(44, m[0]);


    // Operator *
    m[0] = 11;
    Vector3D<FLOAT> v(1, 1, 1);
    Vector4D<FLOAT> u(1, 1, 1, 1);
    
    v = m * v;
    u = m * u;
    
    EXPECT_FLOAT_EQ(11 + 12 + 13 + 14, v.x);
    EXPECT_FLOAT_EQ(21 + 22 + 23 + 24, v.y);
    EXPECT_FLOAT_EQ(31 + 32 + 33 + 34, v.z);
    
    EXPECT_FLOAT_EQ(11 + 12 + 13 + 14, u.x);
    EXPECT_FLOAT_EQ(21 + 22 + 23 + 24, u.y);
    EXPECT_FLOAT_EQ(31 + 32 + 33 + 34, u.z);
    EXPECT_FLOAT_EQ(41 + 42 + 43 + 44, u.w);

    GLMatrix<FLOAT> n = 2 * m;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(2 * m[i], n[i]);
    }

    n = m * 2;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(2 * m[i], n[i]);
    }
    
    n *= 2;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(2 * 2 * m[i], n[i]);
    }
    
    GLMatrix<FLOAT> m1( 1,  2,  3,  4,
                        5,  6,  7,  8,
                        9, 10, 11, 12,
                       13, 14, 15, 16);
    
    GLMatrix<FLOAT> m2( 2,  4,  6,  8,
                       10, 12, 14, 16,
                       18, 20, 22, 24,
                       26, 28, 30, 32);
    
    n = m1 * m2;

    EXPECT_FLOAT_EQ(180, n[ 0]);
    EXPECT_FLOAT_EQ(200, n[ 4]);
    EXPECT_FLOAT_EQ(220, n[ 8]);
    EXPECT_FLOAT_EQ(240, n[12]);
    
    EXPECT_FLOAT_EQ(404, n[ 1]);
    EXPECT_FLOAT_EQ(456, n[ 5]);
    EXPECT_FLOAT_EQ(508, n[ 9]);
    EXPECT_FLOAT_EQ(560, n[13]);
    
    EXPECT_FLOAT_EQ(628, n[ 2]);
    EXPECT_FLOAT_EQ(712, n[ 6]);
    EXPECT_FLOAT_EQ(796, n[10]);
    EXPECT_FLOAT_EQ(880, n[14]);
    
    EXPECT_FLOAT_EQ(852, n[ 3]);
    EXPECT_FLOAT_EQ(968, n[ 7]);
    EXPECT_FLOAT_EQ(1084, n[11]);
    EXPECT_FLOAT_EQ(1200, n[15]);

    m1 *= m2;

    EXPECT_FLOAT_EQ(180, m1[ 0]);
    EXPECT_FLOAT_EQ(200, m1[ 4]);
    EXPECT_FLOAT_EQ(220, m1[ 8]);
    EXPECT_FLOAT_EQ(240, m1[12]);
    
    EXPECT_FLOAT_EQ(404, m1[ 1]);
    EXPECT_FLOAT_EQ(456, m1[ 5]);
    EXPECT_FLOAT_EQ(508, m1[ 9]);
    EXPECT_FLOAT_EQ(560, m1[13]);
    
    EXPECT_FLOAT_EQ(628, m1[ 2]);
    EXPECT_FLOAT_EQ(712, m1[ 6]);
    EXPECT_FLOAT_EQ(796, m1[10]);
    EXPECT_FLOAT_EQ(880, m1[14]);
    
    EXPECT_FLOAT_EQ(852, m1[ 3]);
    EXPECT_FLOAT_EQ(968, m1[ 7]);
    EXPECT_FLOAT_EQ(1084, m1[11]);
    EXPECT_FLOAT_EQ(1200, m1[15]);
    
    // Operator /
    
    m1 = m2 / 2.0f;
    
    EXPECT_FLOAT_EQ( 1, m1[ 0]);
    EXPECT_FLOAT_EQ( 2, m1[ 4]);
    EXPECT_FLOAT_EQ( 3, m1[ 8]);
    EXPECT_FLOAT_EQ( 4, m1[12]);
    
    EXPECT_FLOAT_EQ( 5, m1[ 1]);
    EXPECT_FLOAT_EQ( 6, m1[ 5]);
    EXPECT_FLOAT_EQ( 7, m1[ 9]);
    EXPECT_FLOAT_EQ( 8, m1[13]);
    
    EXPECT_FLOAT_EQ( 9, m1[ 2]);
    EXPECT_FLOAT_EQ(10, m1[ 6]);
    EXPECT_FLOAT_EQ(11, m1[10]);
    EXPECT_FLOAT_EQ(12, m1[14]);
    
    EXPECT_FLOAT_EQ(13, m1[ 3]);
    EXPECT_FLOAT_EQ(14, m1[ 7]);
    EXPECT_FLOAT_EQ(15, m1[11]);
    EXPECT_FLOAT_EQ(16, m1[15]);
    
    m2 /= 2;
    
    EXPECT_FLOAT_EQ( 1, m2[ 0]);
    EXPECT_FLOAT_EQ( 2, m2[ 4]);
    EXPECT_FLOAT_EQ( 3, m2[ 8]);
    EXPECT_FLOAT_EQ( 4, m2[12]);
    
    EXPECT_FLOAT_EQ( 5, m2[ 1]);
    EXPECT_FLOAT_EQ( 6, m2[ 5]);
    EXPECT_FLOAT_EQ( 7, m2[ 9]);
    EXPECT_FLOAT_EQ( 8, m2[13]);
    
    EXPECT_FLOAT_EQ( 9, m2[ 2]);
    EXPECT_FLOAT_EQ(10, m2[ 6]);
    EXPECT_FLOAT_EQ(11, m2[10]);
    EXPECT_FLOAT_EQ(12, m2[14]);
    
    EXPECT_FLOAT_EQ(13, m2[ 3]);
    EXPECT_FLOAT_EQ(14, m2[ 7]);
    EXPECT_FLOAT_EQ(15, m2[11]);
    EXPECT_FLOAT_EQ(16, m2[15]);
    
    // Operator +
    GLMatrix<FLOAT> m3( 1,  2,  3,  4,
                        5,  6,  7,  8,
                        9, 10, 11, 12,
                       13, 14, 15, 16);
    
    GLMatrix<FLOAT> m4( 2,  4,  6,  8,
                       10, 12, 14, 16,
                       18, 20, 22, 24,
                       26, 28, 30, 32);
    
    m = m3 + m3;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(m4[i], m[i]);
    }

    m3 += m3;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(m4[i], m3[i]);
    }

    
    // Operator -
    m = m3 - m3;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(0, m[i]);
    }

    m3 -= m3;
    for (int i = 0; i < 16; ++i)
    {
        EXPECT_FLOAT_EQ(0, m3[i]);
    }

    
    // Operator ==
    EXPECT_TRUE(m3 == GLMatrix<FLOAT>::ZERO);
    EXPECT_TRUE(m3 != GLMatrix<FLOAT>::ZEROAFFINE);
}



TEST_F(GLMatrixFloatTest, setLookAt)
{
    GLMatrix<FLOAT> m;
    
    Vector3D<FLOAT> eye(50, 45, -15), center(10, 20, 15), up(1, 1, 1);
    Vector3D<FLOAT> s, f, u;

    m.setLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);

    f = center - eye;
    f.normalize();
    up.normalize();
    s = f.cross(up);
    s.normalize();
    u = s.cross(f);
    
    GLMatrix<FLOAT> l(s.x, s.y, s.z, 0,
                      u.x, u.y, u.z, 0,
                     -f.x,-f.y,-f.z, 0,
                        0,   0,   0, 1);
    
    l.translate(-eye.x, -eye.y, -eye.z);

    // Row 1
    EXPECT_NEAR(l[ 0], m[ 0], 1e-10);
    EXPECT_NEAR(l[ 4], m[ 4], 1e-10);
    EXPECT_NEAR(l[ 8], m[ 8], 1e-10);
    EXPECT_NEAR(l[12], m[12], 1e-10);

    // Row 2
    EXPECT_NEAR(l[ 1], m[ 1], 1e-10);
    EXPECT_NEAR(l[ 5], m[ 5], 1e-10);
    EXPECT_NEAR(l[ 9], m[ 9], 1e-10);
    EXPECT_NEAR(l[13], m[13], 1e-10);
    
    // Row 3
    EXPECT_NEAR(l[ 2], m[ 2], 1e-10);
    EXPECT_NEAR(l[ 6], m[ 6], 1e-10);
    EXPECT_NEAR(l[10], m[10], 1e-10);
    EXPECT_NEAR(l[14], m[14], 1e-10);
    
    // Row 4
    EXPECT_NEAR(l[ 3], m[ 3], 1e-10);
    EXPECT_NEAR(l[ 7], m[ 7], 1e-10);
    EXPECT_NEAR(l[11], m[11], 1e-10);
    EXPECT_NEAR(l[15], m[15], 1e-10);
}



TEST_F(GLMatrixFloatTest, setFrustum)
{
    GLMatrix<FLOAT> m;
    
    FLOAT left = -10, right = 25, top = 25, bottom = -10, zNear = 1, zFar = 10;
    FLOAT width  = right - left;
    FLOAT height = top - bottom;

    m.setFrustum(left, right, bottom, top, zNear, zFar);

    // Row 1
    EXPECT_NEAR(2.0*zNear / width,        m[ 0], 1e-9);
    EXPECT_NEAR(0,                            m[ 4], 1e-10);
    EXPECT_NEAR((right + left) / width, m[ 8], 1e-8);
    EXPECT_NEAR(0,                            m[12], 1e-10);
    
    // Row 2
    EXPECT_NEAR(0,                               m[ 1], 1e-10);
    EXPECT_NEAR(2.0*zNear / height,          m[ 5], 1e-9);
    EXPECT_NEAR((top + bottom) / height, m[ 9], 1e-8);
    EXPECT_NEAR(0,                               m[13], 1e-10);
    
    // Row 3
    EXPECT_NEAR(0,                                    m[ 2], 1e-10);
    EXPECT_NEAR(0,                                    m[ 6], 1e-10);
    EXPECT_NEAR(-( (zFar + zNear) / (zFar - zNear) ), m[10], 1e-10);
    EXPECT_NEAR((-2.0*zFar*zNear) / (zFar - zNear),    m[14], 1e-6);
    
    // Row 4
    EXPECT_NEAR(0,  m[ 3], 1e-10);
    EXPECT_NEAR(0,  m[ 7], 1e-10);
    EXPECT_NEAR(-1, m[11], 1e-10);
    EXPECT_NEAR(0,  m[15], 1e-10);
}



TEST_F(GLMatrixFloatTest, setOrtho)
{
    GLMatrix<FLOAT> m;
    
    FLOAT left = -10, right = 25, top = 25, bottom = -10, zNear = 1, zFar = 10;
    FLOAT width  = right - left;
    FLOAT height = top - bottom;

    m.setOrtho(left, right, bottom, top, zNear, zFar);

    // Row 1
    EXPECT_NEAR(1.0 / (width / 2.0),     m[ 0], 1e-9);
    EXPECT_NEAR(0,                       m[ 4], 1e-10);
    EXPECT_NEAR(0,                       m[ 8], 1e-8);
    EXPECT_NEAR(-(right + left) / width, m[12], 1e-10);
    
    // Row 2
    EXPECT_NEAR(0,                        m[ 1], 1e-10);
    EXPECT_NEAR(1.0 / (height / 2.0),     m[ 5], 1e-9);
    EXPECT_NEAR(0,                        m[ 9], 1e-8);
    EXPECT_NEAR(-(top + bottom) / height, m[13], 1e-10);

    // Row 3
    EXPECT_NEAR(0,                                m[ 2], 1e-10);
    EXPECT_NEAR(0,                                m[ 6], 1e-10);
    EXPECT_NEAR(-1.0 / ((zFar - zNear) / 2.0),    m[10], 1e-8);
    EXPECT_NEAR(-(zFar + zNear) / (zFar - zNear), m[14], 1e-6);
    
    // Row 4
    EXPECT_NEAR(0, m[ 3], 1e-10);
    EXPECT_NEAR(0, m[ 7], 1e-10);
    EXPECT_NEAR(0, m[11], 1e-10);
    EXPECT_NEAR(1, m[15], 1e-10);
}
