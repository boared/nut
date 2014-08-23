#include "gtest/gtest.h"
#include "Vector4D.h"

#undef FLOAT
#define FLOAT double

using namespace nut;

class Vector4DDoubleTest : public ::testing::Test
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

TEST_F(Vector4DDoubleTest, constructors)
{
    // Default constructor
    Vector4D<FLOAT> v;
    EXPECT_FLOAT_EQ(v.x, 0.0);
    EXPECT_FLOAT_EQ(v.y, 0.0);
    EXPECT_FLOAT_EQ(v.z, 0.0);
    EXPECT_FLOAT_EQ(v.w, 0.0);

    // Constructor
    Vector4D<FLOAT> u( 3.1459f, -2.0, 5.0, 12);
    EXPECT_FLOAT_EQ(u.x, 3.1459f);
    EXPECT_FLOAT_EQ(u.y, -2.0);
    EXPECT_FLOAT_EQ(u.z, 5.0);
    EXPECT_FLOAT_EQ(u.w, 12.0);

    // Copy constructor
    v = u;
    EXPECT_FLOAT_EQ(v.x, 3.1459f);
    EXPECT_FLOAT_EQ(v.y, -2.0);
    EXPECT_FLOAT_EQ(v.z, 5.0);
    EXPECT_FLOAT_EQ(v.w, 12.0);
}



// Methods

TEST_F(Vector4DDoubleTest, length)
{
    // v = (0, 0, 0, 0)
    Vector4D<FLOAT> v;
    EXPECT_FLOAT_EQ(0.0, v.length());

    // u = (1, 1, 1, 1)
    Vector4D<FLOAT> u(1.0, 1.0, 1.0, 1.0);
    EXPECT_NEAR(sqrt(4.0), u.length(), 1e-20);

    // w = (1, 0, 0, 0)
    Vector4D<FLOAT> w(1.0, 0.0, 0.0, 0.0);
    EXPECT_FLOAT_EQ(1.0, w.length());

    // x = (0, 1, 0, 0)
    Vector4D<FLOAT> x(0.0, 1.0, 0.0, 0.0);
    EXPECT_FLOAT_EQ(1.0, x.length());

    // z = (0, 0, 1, 0)
    Vector4D<FLOAT> z(0.0, 0.0, 1.0, 0.0);
    EXPECT_FLOAT_EQ(1.0, z.length());

    // s = (0, 0, 0, 1)
    Vector4D<FLOAT> s(0.0, 0.0, 0.0, 1.0);
    EXPECT_FLOAT_EQ(1.0, s.length());

    // y = (7.98, -2.5, 3.1415)
    Vector4D<FLOAT> y(7.98f, -2.5, 3.1415, 10);
    EXPECT_NEAR(13.408930701380063, (double)y.length(), 1e-20);
}



TEST_F(Vector4DDoubleTest, slength)
{
    // v = (0, 0, 0, 0)
    Vector4D<FLOAT> v;
    EXPECT_FLOAT_EQ(0.0, v.slength());
        
    // u = (1, 1, 1, 1)
    Vector4D<FLOAT> u(1.0, 1.0, 1.0, 1.0);
    EXPECT_NEAR(4.0, u.slength(), 1e-20);
        
    // w = (1, 0, 0, 0)
    Vector4D<FLOAT> w(1.0, 0.0, 0.0, 0.0);
    EXPECT_FLOAT_EQ(1.0, w.slength());
        
    // x = (0, 1, 0, 0)
    Vector4D<FLOAT> x(0.0, 1.0, 0.0, 0.0);
    EXPECT_FLOAT_EQ(1.0, x.slength());
    
    // z = (0, 0, 1, 0)
    Vector4D<FLOAT> z(0.0, 0.0, 1.0, 0.0);
    EXPECT_FLOAT_EQ(1.0, z.slength());

    // s = (0, 0, 1, 0)
    Vector4D<FLOAT> s(0.0, 0.0, 1.0, 0.0);
    EXPECT_FLOAT_EQ(1.0, s.slength());

    // y = (7.98, -2.5, 3.1415)
    Vector4D<FLOAT> y(7.98, -2.5, 3.1415, 12);
    EXPECT_NEAR(7.98*7.98 + (-2.5)*(-2.5) + (3.1415)*(3.1415) + 12.0*12.0, y.slength(), 1e-10);
}



TEST_F(Vector4DDoubleTest, normalize)
{
    Vector4D<FLOAT> u1(0, 0, 0, 0), u2(1, 1, 1, 1), u3(1, 0, 0, 0), u4(0, 1, 0, 0), u5(7.98f, -2.5, 3.1415, 4);

    // u1 = (0, 0, 0, 0)
    u1.normalize();
    EXPECT_NEAR(0.0, u1.length(), 1e-20);

    // u2 = (1, 1, 1, 1)
    u2.normalize();
    EXPECT_NEAR(1.0, u2.length(), 1e-20);

    // u3 = (1, 0, 0, 0)
    u3.normalize();
    EXPECT_NEAR(1.0, u3.length(), 1e-20);

    // u4 = (0, 1, 0, 0)
    u4.normalize();
    EXPECT_NEAR(1.0, u4.length(), 1e-20);

    // u5 = (7.98, -2.5, 3.1415, 4)
    u5.normalize();
    EXPECT_NEAR(1.0, u5.length(), 1e-20);

    Vector4D<FLOAT> w1(3.1415f, -45.567f, 3.1415f, 0), w2(3458.0, -10000.0, 0.0, 1), w3(-98.234f, -4457.0, 1.0, 9), w4(0, 1.3344f, 0.0, 2), w5(7.98f, 0, 7, 8);

    w1.normalize();
    EXPECT_NEAR(1.0, w1.length(), 1e-20);

    w2.normalize();
    EXPECT_NEAR(1.0, w2.length(), 1e-20);

    w3.normalize();
    EXPECT_NEAR(1.0, w3.length(), 1e-15);

    w4.normalize();
    EXPECT_NEAR(1.0, w4.length(), 1e-20);

    w5.normalize();
    EXPECT_NEAR(1.0, w5.length(), 1e-20);
}



TEST_F(Vector4DDoubleTest, scale)
{
    Vector4D<FLOAT> u1(0, 0, 0, 0), u2(1, 1, 1, 1), u3(1, 0, 0, 0), u4(0, 1, 0, 0), u5(1, 1, 1, 1);

    // u1 = (0, 0, 0, 0)
    u1.scale(4.0, 3.5, 3.0, 4.0);
    EXPECT_NEAR(0.0, u1.length(), 1e-20);

    // u2 = (1, 1, 1, 1)
    u2.scale(5, 3, 2, 2);
    EXPECT_NEAR(std::sqrt(42.0), u2.length(), 1e-20);

    // u3 = (1, 0, 0, 0)
    u3.scale(5.0, 3.0, 3.1415, 13);
    EXPECT_NEAR(5.0, u3.length(), 1e-20);

    // u4 = (0, 1, 0, 0)
    u4.scale(5.0, 23.0, 5.0, 12);
    EXPECT_NEAR(23.0, u4.length(), 1e-20);
}



TEST_F(Vector4DDoubleTest, project)
{
    Vector4D<FLOAT> r;
    Vector4D<FLOAT> v1(1, 1, 1, 1), v2(1, 0, 0, 0), v3(0, 1, 0, 0), v4(2, 1, 3, 7), v5(1, 3, 4, 12);

    r = v2.project(v1);

    EXPECT_NEAR(1.0, r.x, 1e-20);
    EXPECT_NEAR(0.0, r.y, 1e-20);
    EXPECT_NEAR(0.0, r.z, 1e-20);
    EXPECT_NEAR(0.0, r.w, 1e-20);

    r = v3.project(v1);

    EXPECT_NEAR(0.0, r.x, 1e-20);
    EXPECT_NEAR(1.0, r.y, 1e-20);
    EXPECT_NEAR(0.0, r.z, 1e-20);
    EXPECT_NEAR(0.0, r.w, 1e-20);

    r = v5.project(v4);

    EXPECT_NEAR(101.0 / 170.0, r.x, 1e-20);
    EXPECT_NEAR(303.0 / 170.0, r.y, 1e-15);
    EXPECT_NEAR(202.0 /  85.0, r.z, 1e-20);
    EXPECT_NEAR(606.0 /  85.0, r.w, 1e-15);
}



TEST_F(Vector4DDoubleTest, dotProduct)
{
    Vector4D<FLOAT> u1(0, 0, 0, 0), u2(1, 1, 1, 1), u3(2.23876f, 4.4444f, 3, 5), u4(234.9898f, -1.22343f, -6, -9), u5(-2345.777f, -7878.887f, 13.777, 1.14f);

    EXPECT_NEAR(u1.x * u2.x + u1.y * u2.y + u1.z * u2.z + u1.w * u2.w, u1 * u2, 1e-20);
        
    EXPECT_NEAR(u3.x * u4.x + u3.y * u4.y + u3.z * u4.z + u3.w * u4.w, u3 * u4, 1e-20);
        
    EXPECT_NEAR(u4.x * u5.x + u4.y * u5.y + u4.z * u5.z + u4.w * u5.w, u4 * u5, 1e-20);
        
    EXPECT_NEAR(u5.x * u1.x + u5.y * u1.y + u5.z * u1.z + u5.w * u1.w, u5 * u1, 1e-20);
        
    EXPECT_NEAR(u5.x * u3.x + u5.y * u3.y + u5.z * u3.z + u5.w * u3.w, u5 * u3, 1e-20);
}



TEST_F(Vector4DDoubleTest, operators)
{
    Vector4D<FLOAT> r;
    Vector4D<FLOAT> v1(1, 1, 1, 1), v2(0.5, -3.14f, 2, 5);

    // Multiplication by a scalar
    r = v1 * 5;
    EXPECT_FLOAT_EQ(5, r.x);
    EXPECT_FLOAT_EQ(5, r.y);
    EXPECT_FLOAT_EQ(5, r.z);
    EXPECT_FLOAT_EQ(5, r.w);

    r = 5 * v1;
    EXPECT_FLOAT_EQ(5, r.x);
    EXPECT_FLOAT_EQ(5, r.y);
    EXPECT_FLOAT_EQ(5, r.z);
    EXPECT_FLOAT_EQ(5, r.w);

    r = 5 * v2;
    EXPECT_FLOAT_EQ(5 * 0.5, r.x);
    EXPECT_FLOAT_EQ(5 * (-3.14f), r.y);
    EXPECT_FLOAT_EQ(10.0, r.z);
    EXPECT_FLOAT_EQ(25.0, r.w);

    r = v2 * 5;
    EXPECT_FLOAT_EQ(5 * 0.5, r.x);
    EXPECT_FLOAT_EQ(5 * (-3.14f), r.y);
    EXPECT_FLOAT_EQ(10.0, r.z);
    EXPECT_FLOAT_EQ(25.0, r.w);

    v2 *= 5;
    EXPECT_FLOAT_EQ(5 * 0.5, v2.x);
    EXPECT_FLOAT_EQ(5 * (-3.14f), v2.y);
    EXPECT_FLOAT_EQ(10.0, v2.z);
    EXPECT_FLOAT_EQ(25.0, v2.w);


    // Division by a scalar    
    r = v1 / 5.0;
    EXPECT_FLOAT_EQ(1.0 / 5.0, r.x);
    EXPECT_FLOAT_EQ(1.0 / 5.0, r.y);
    EXPECT_FLOAT_EQ(1.0 / 5.0, r.z);
    EXPECT_FLOAT_EQ(1.0 / 5.0, r.w);

    v1 /= 5.0;
    EXPECT_FLOAT_EQ(1.0 / 5.0, v1.x);
    EXPECT_FLOAT_EQ(1.0 / 5.0, v1.y);
    EXPECT_FLOAT_EQ(1.0 / 5.0, v1.z);
    EXPECT_FLOAT_EQ(1.0 / 5.0, v1.w);


    // Vector addition
    v1.y = v1.x = v1.z = v1.w = 1.0;
    v2.x = 0.5; v2.y = -3.14f; v2.z = 2; v2.w = 5;
    
    r = v1 + v2;
    EXPECT_FLOAT_EQ(1.0 + 0.5, r.x);
    EXPECT_FLOAT_EQ(1.0 - 3.14f, r.y);
    EXPECT_FLOAT_EQ(3.0, r.z);
    EXPECT_FLOAT_EQ(6.0, r.w);

    v1 += v2;
    EXPECT_FLOAT_EQ(1.0 + 0.5, v1.x);
    EXPECT_FLOAT_EQ(1.0 - 3.14f, v1.y);
    EXPECT_FLOAT_EQ(3.0, v1.z);
    EXPECT_FLOAT_EQ(6.0, v1.w);


    // Vector subtraction
    v1.y = v1.x = v1.z = v1.w = 1.0;
    v2.x = 0.5; v2.y = -3.14f; v2.z = 2; v2.w = 5;

    r = v1 - v2;
    EXPECT_FLOAT_EQ(1.0 - 0.5, r.x);
    EXPECT_FLOAT_EQ(1.0 + 3.14f, r.y);
    EXPECT_FLOAT_EQ(-1.0, r.z);
    EXPECT_FLOAT_EQ(-4.0, r.w);

    v1 -= v2;
    EXPECT_FLOAT_EQ(1.0 - 0.5, v1.x);
    EXPECT_FLOAT_EQ(1.0 + 3.14f, v1.y);
    EXPECT_FLOAT_EQ(-1.0, r.z);
    EXPECT_FLOAT_EQ(-4.0, r.w);


    // Additive inverse
    v1.y = v1.x = v1.z = v1.w = 1.0;
    v2.x = 0.5; v2.y = -3.14f; v2.z = 2; v2.w = 5;
    
    r = -v1;
    EXPECT_FLOAT_EQ(-1.0, r.x);
    EXPECT_FLOAT_EQ(-1.0, r.y);
    EXPECT_FLOAT_EQ(-1.0, r.z);
    EXPECT_FLOAT_EQ(-1.0, r.w);

    r = -v2;
    EXPECT_FLOAT_EQ(-0.5, r.x);
    EXPECT_FLOAT_EQ(3.14f, r.y);
    EXPECT_FLOAT_EQ(-2, r.z);
    EXPECT_FLOAT_EQ(-5, r.w);


    // Attribution
    v1.y = v1.x = v1.z = v1.w = 1.0;
    v2.x = 0.5; v2.y = -3.14f; v2.z = 2; v2.w = 5;

    r = v1;
    EXPECT_FLOAT_EQ(1.0, r.x);
    EXPECT_FLOAT_EQ(1.0, r.y);
    EXPECT_FLOAT_EQ(1.0, r.z);
    EXPECT_FLOAT_EQ(1.0, r.w);

    r = v2;
    EXPECT_FLOAT_EQ(0.5, r.x);
    EXPECT_FLOAT_EQ(-3.14f, r.y);
    EXPECT_FLOAT_EQ(2.0, r.z);
    EXPECT_FLOAT_EQ(5.0, r.w);


    // Comparison
    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v2 == v2);
}



TEST_F(Vector4DDoubleTest, constants)
{
    Vector4D<FLOAT> v = Vector4D<FLOAT>(0.0, 0.0, 0.0, 0.0);

    // Zero vector
    EXPECT_FLOAT_EQ(v.x, Vector4D<FLOAT>::ZERO.x);
    EXPECT_FLOAT_EQ(v.y, Vector4D<FLOAT>::ZERO.y);
    EXPECT_FLOAT_EQ(v.z, Vector4D<FLOAT>::ZERO.z);
    EXPECT_FLOAT_EQ(v.w, Vector4D<FLOAT>::ZERO.w);

    // Unit vector
    v.x = v.y = v.z = v.w = 1.0;
    EXPECT_FLOAT_EQ(v.x, Vector4D<FLOAT>::UNIT.x);
    EXPECT_FLOAT_EQ(v.y, Vector4D<FLOAT>::UNIT.y);
    EXPECT_FLOAT_EQ(v.z, Vector4D<FLOAT>::UNIT.z);
    EXPECT_FLOAT_EQ(v.w, Vector4D<FLOAT>::UNIT.w);
	
    // X-axis
	v.x = 1.0;
    v.y = 0.0;
    v.z = 0.0;
    v.w = 0.0;
    EXPECT_FLOAT_EQ(v.x, Vector4D<FLOAT>::X_AXIS.x);
    EXPECT_FLOAT_EQ(v.y, Vector4D<FLOAT>::X_AXIS.y);
    EXPECT_FLOAT_EQ(v.z, Vector4D<FLOAT>::X_AXIS.z);
    EXPECT_FLOAT_EQ(v.w, Vector4D<FLOAT>::X_AXIS.w);

    // Y-axis
	v.x = 0.0;
    v.y = 1.0;
    v.z = 0.0;
    v.w = 0.0;
    EXPECT_FLOAT_EQ(v.x, Vector4D<FLOAT>::Y_AXIS.x);
    EXPECT_FLOAT_EQ(v.y, Vector4D<FLOAT>::Y_AXIS.y);
    EXPECT_FLOAT_EQ(v.z, Vector4D<FLOAT>::Y_AXIS.z);
    EXPECT_FLOAT_EQ(v.w, Vector4D<FLOAT>::Y_AXIS.w);
    
    // Z-axis
	v.x = 0.0;
    v.y = 0.0;
    v.z = 1.0;
    v.w = 0.0;
    EXPECT_FLOAT_EQ(v.x, Vector4D<FLOAT>::Z_AXIS.x);
    EXPECT_FLOAT_EQ(v.y, Vector4D<FLOAT>::Z_AXIS.y);
    EXPECT_FLOAT_EQ(v.z, Vector4D<FLOAT>::Z_AXIS.z);
    EXPECT_FLOAT_EQ(v.w, Vector4D<FLOAT>::Z_AXIS.w);

    // W-axis
	v.x = 0.0;
    v.y = 0.0;
    v.z = 0.0;
    v.w = 1.0;
    EXPECT_FLOAT_EQ(v.x, Vector4D<FLOAT>::W_AXIS.x);
    EXPECT_FLOAT_EQ(v.y, Vector4D<FLOAT>::W_AXIS.y);
    EXPECT_FLOAT_EQ(v.z, Vector4D<FLOAT>::W_AXIS.z);
    EXPECT_FLOAT_EQ(v.w, Vector4D<FLOAT>::W_AXIS.w);
}
