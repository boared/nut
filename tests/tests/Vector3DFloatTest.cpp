#include "gtest/gtest.h"
#include "Vector3D.h"

#undef FLOAT
#define FLOAT float

using namespace nut;

class Vector3DFloatTest : public ::testing::Test
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

TEST_F(Vector3DFloatTest, constructors)
{
    // Default constructor
    Vector3D<FLOAT> v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
    
    // Constructor
    Vector3D<FLOAT> u( 3.1459f, -2.0f, 5.0f);
    EXPECT_FLOAT_EQ(u.x, 3.1459f);
    EXPECT_FLOAT_EQ(u.y, -2.0f);
    EXPECT_FLOAT_EQ(u.z, 5.0f);
    
    // Copy constructor
    v = u;
    EXPECT_FLOAT_EQ(v.x, 3.1459f);
    EXPECT_FLOAT_EQ(v.y, -2.0f);
    EXPECT_FLOAT_EQ(v.z, 5.0f);
}



// Methods

TEST_F(Vector3DFloatTest, length)
{
    // v = (0, 0, 0)
    Vector3D<FLOAT> v;
    EXPECT_FLOAT_EQ(0.0f, v.length());

    // u = (1, 1, 1)
    Vector3D<FLOAT> u(1.0f, 1.0f, 1.0f);
    EXPECT_NEAR(sqrt(3.0f), u.length(), 1e-7);

    // w = (1, 0, 0)
    Vector3D<FLOAT> w(1.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(1.0f, w.length());

    // x = (0, 1, 0)
    Vector3D<FLOAT> x(0.0f, 1.0f, 0.0f);
    EXPECT_FLOAT_EQ(1.0f, x.length());

    // z = (0, 0, 1)
    Vector3D<FLOAT> z(0.0f, 0.0f, 1.0f);
    EXPECT_FLOAT_EQ(1.0f, z.length());

    // y = (7.98, -2.5, 3.1415)
    Vector3D<FLOAT> y(7.98f, -2.5f, 3.1415);
    EXPECT_NEAR(8.933052235938173444707, (double)y.length(), 1e-6);
}



TEST_F(Vector3DFloatTest, slength)
{
    // v = (0, 0, 0)
    Vector3D<FLOAT> v;
    EXPECT_FLOAT_EQ(0.0f, v.slength());
        
    // u = (1, 1, 1)
    Vector3D<FLOAT> u(1.0f, 1.0f, 1.0f);
    EXPECT_NEAR(3.0f, u.slength(), 1e-10);
        
    // w = (1, 0, 0)
    Vector3D<FLOAT> w(1.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(1.0f, w.slength());
        
    // x = (0, 1, 0)
    Vector3D<FLOAT> x(0.0f, 1.0f, 0.0f);
    EXPECT_FLOAT_EQ(1.0f, x.slength());
    
    // z = (0, 0, 1)
    Vector3D<FLOAT> z(0.0f, 0.0f, 1.0f);
    EXPECT_FLOAT_EQ(1.0f, z.slength());
        
    // y = (7.98, -2.5, 3.1415)
    Vector3D<FLOAT> y(7.98f, -2.5f, 3.1415f);
    EXPECT_NEAR(7.98f*7.98f + (-2.5f)*(-2.5f) + (3.1415f)*(3.1415f), y.slength(), 1e-5);
}



TEST_F(Vector3DFloatTest, normalize)
{
    Vector3D<FLOAT> u1(0, 0, 0), u2(1, 1, 1), u3(1, 0, 0), u4(0, 1, 0), u5(7.98f, -2.5f, 3.1415);

    // u1 = (0, 0, 0)
    u1.normalize();
    EXPECT_NEAR(0.0f, u1.length(), 1e-10);

    // u2 = (1, 1, 1)
    u2.normalize();
    EXPECT_NEAR(1.0f, u2.length(), 1e-7);

    // u3 = (1, 0, 0)
    u3.normalize();
    EXPECT_NEAR(1.0f, u3.length(), 1e-10);

    // u4 = (0, 1, 0)
    u4.normalize();
    EXPECT_NEAR(1.0f, u4.length(), 1e-10);

    // u5 = (7.98, -2.5, 3.1415)
    u5.normalize();
    EXPECT_NEAR(1.0f, u5.length(), 1e-7);

    Vector3D<FLOAT> w1(3.1415f, -45.567f, 3.1415f), w2(3458.0f, -10000.f, 0.0f), w3(-98.234f, -4457.f, 1.0f), w4(0, 1.3344f, 0.0f), w5(7.98f, 0, 7);

    w1.normalize();
    EXPECT_NEAR(1.0f, w1.length(), 1e-7);

    w2.normalize();
    EXPECT_NEAR(1.0f, w2.length(), 1e-10);

    w3.normalize();
    EXPECT_NEAR(1.0f, w3.length(), 1e-10);

    w4.normalize();
    EXPECT_NEAR(1.0f, w4.length(), 1e-10);

    w5.normalize();
    EXPECT_NEAR(1.0f, w5.length(), 1e-10);
}



TEST_F(Vector3DFloatTest, scale)
{
    Vector3D<FLOAT> u1(0, 0, 0), u2(1, 1, 1), u3(1, 0, 0), u4(0, 1, 0), u5(1, 1, 1);

    // u1 = (0, 0, 0)
    u1.scale(4.0f, 3.5f, 3.0f);
    EXPECT_NEAR(0.0f, u1.length(), 1e-10);

    // u2 = (1, 1, 1)
    u2.scale(5, 3, 2);
    EXPECT_NEAR(std::sqrt(38.0f), u2.length(), 1e-8);

    // u3 = (1, 0, 0)
    u3.scale(5.f, 5.f, 3.1415);
    EXPECT_NEAR(5.0f, u3.length(), 1e-10);

    // u4 = (0, 1, 0)
    u4.scale(5.f, 5.f, 5.0f);
    EXPECT_NEAR(5.0f, u4.length(), 1e-10);
}



TEST_F(Vector3DFloatTest, crossProduct)
{
    Vector3D<FLOAT> u1(0, 0, 0), u2(1, 0, 0), u3(0, 1.0f, 0),
                    u4(3.5f, -1.22343f, -2), u5(-2345.777f, -7878.887f, 12);
    
    Vector3D<FLOAT> r;

    // u1 x u2
    r = u1.cross(u2);
    EXPECT_NEAR(0.0f, r.x, 1e-10);
    EXPECT_NEAR(0.0f, r.y, 1e-10);
    EXPECT_NEAR(0.0f, r.z, 1e-10);

    // u2 x u3
    r = u2.cross(u3);
    EXPECT_NEAR(0.0f, r.x, 1e-10);
    EXPECT_NEAR(0.0f, r.y, 1e-10);
    EXPECT_NEAR(1.0f, r.z, 1e-10);

    // u3 x u4
    r = u3.cross(u4);
    EXPECT_NEAR(-2.0f, r.x, 1e-10);
    EXPECT_NEAR( 0.0f, r.y, 1e-10);
    EXPECT_NEAR(-3.5f, r.z, 1e-10);
    
    // u4 x u3
    r = u4.cross(u3);
    EXPECT_NEAR(2.0f, r.x, 1e-10);
    EXPECT_NEAR( 0.0f, r.y, 1e-10);
    EXPECT_NEAR(3.5f, r.z, 1e-10);
    
    // u4 x u5
    r = u4.cross(u5);
    EXPECT_NEAR(-15772.4560546875f, r.x, 1e-10);
    EXPECT_NEAR( 4649.55419f, r.y, 1e-10);
    EXPECT_NEAR(-30446.0f, r.z, 1e-10);
}



TEST_F(Vector3DFloatTest, project)
{
    Vector3D<FLOAT> r;
    Vector3D<FLOAT> v1(1, 1, 1), v2(1, 0, 0), v3(0, 1, 0), v4(2, 1, 3), v5(1, 3, 4);

    r = v2.project(v1);

    EXPECT_NEAR(1.0f, r.x, 1e-10);
    EXPECT_NEAR(0.0f, r.y, 1e-10);
    EXPECT_NEAR(0.0f, r.z, 1e-10);

    r = v3.project(v1);

    EXPECT_NEAR(0.0f, r.x, 1e-10);
    EXPECT_NEAR(1.0f, r.y, 1e-10);
    EXPECT_NEAR(0.0f, r.z, 1e-10);

    r = v5.project(v4);

    EXPECT_NEAR(17.0f / 26.0f, r.x, 1e-10);
    EXPECT_NEAR(51.0f / 26.0f, r.y, 1e-10);
    EXPECT_NEAR(34.0f / 13.0f, r.z, 1e-10);
}



TEST_F(Vector3DFloatTest, dotProduct)
{
    Vector3D<FLOAT> u1(0, 0, 0), u2(1, 1, 1), u3(2.23876f, 4.4444f, 3), u4(234.9898f, -1.22343f, -6), u5(-2345.777f, -7878.887f, 13.777);

    EXPECT_NEAR(u1.x * u2.x + u1.y * u2.y + u1.z * u2.z, u1 * u2, 1e-10);
        
    EXPECT_NEAR(u3.x * u4.x + u3.y * u4.y + u3.z * u4.z, u3 * u4, 1e-10);
        
    EXPECT_NEAR(u4.x * u5.x + u4.y * u5.y + u4.z * u5.z, u4 * u5, 1e-10);
        
    EXPECT_NEAR(u5.x * u1.x + u5.y * u1.y + u5.z * u1.z, u5 * u1, 1e-10);
        
    EXPECT_NEAR(u5.x * u3.x + u5.y * u3.y + u5.z * u3.z, u5 * u3, 1e-10);
}



TEST_F(Vector3DFloatTest, operators)
{
    Vector3D<FLOAT> r;
    Vector3D<FLOAT> v1(1, 1, 1), v2(0.5f, -3.14f, 2);

    // Multiplication by a scalar
    r = v1 * 5;
    EXPECT_FLOAT_EQ(5, r.x);
    EXPECT_FLOAT_EQ(5, r.y);
    EXPECT_FLOAT_EQ(5, r.z);

    r = 5 * v1;
    EXPECT_FLOAT_EQ(5, r.x);
    EXPECT_FLOAT_EQ(5, r.y);
    EXPECT_FLOAT_EQ(5, r.z);

    r = 5 * v2;
    EXPECT_FLOAT_EQ(5 * 0.5f, r.x);
    EXPECT_FLOAT_EQ(5 * (-3.14f), r.y);
    EXPECT_FLOAT_EQ(10.0f, r.z);

    r = v2 * 5;
    EXPECT_FLOAT_EQ(5 * 0.5f, r.x);
    EXPECT_FLOAT_EQ(5 * (-3.14f), r.y);
    EXPECT_FLOAT_EQ(10.0f, r.z);

    v2 *= 5;
    EXPECT_FLOAT_EQ(5 * 0.5f, v2.x);
    EXPECT_FLOAT_EQ(5 * (-3.14f), v2.y);
    EXPECT_FLOAT_EQ(10.0f, v2.z);
    


    // Division by a scalar    
    r = v1 / 5.0f;
    EXPECT_FLOAT_EQ(1.0f / 5.0f, r.x);
    EXPECT_FLOAT_EQ(1.0f / 5.0f, r.y);
    EXPECT_FLOAT_EQ(1.0f / 5.0f, r.z);

    v1 /= 5.0f;
    EXPECT_FLOAT_EQ(1.0f / 5.0f, v1.x);
    EXPECT_FLOAT_EQ(1.0f / 5.0f, v1.y);
    EXPECT_FLOAT_EQ(1.0f / 5.0f, v1.z);


    // Vector addition
    v1.y = v1.x = v1.z = 1.0f;
    v2.x = 0.5f; v2.y = -3.14f; v2.z = 2;
    
    r = v1 + v2;
    EXPECT_FLOAT_EQ(1.0f + 0.5f, r.x);
    EXPECT_FLOAT_EQ(1.0f - 3.14f, r.y);
    EXPECT_FLOAT_EQ(3.0f, r.z);

    v1 += v2;
    EXPECT_FLOAT_EQ(1.0f + 0.5f, v1.x);
    EXPECT_FLOAT_EQ(1.0f - 3.14f, v1.y);
    EXPECT_FLOAT_EQ(3.0f, v1.z);


    // Vector subtraction
    v1.y = v1.x = v1.z = 1.0f;
    v2.x = 0.5f; v2.y = -3.14f; v2.z = 2;
    
    r = v1 - v2;
    EXPECT_FLOAT_EQ(1.0f - 0.5f, r.x);
    EXPECT_FLOAT_EQ(1.0f + 3.14f, r.y);
    EXPECT_FLOAT_EQ(-1.0f, r.z);

    v1 -= v2;
    EXPECT_FLOAT_EQ(1.0f - 0.5f, v1.x);
    EXPECT_FLOAT_EQ(1.0f + 3.14f, v1.y);
    EXPECT_FLOAT_EQ(-1.0f, r.z);


    // Additive inverse
    v1.y = v1.x = v1.z = 1.0f;
    v2.x = 0.5f; v2.y = -3.14f; v2.z = 2;
    
    r = -v1;
    EXPECT_FLOAT_EQ(-1.0f, r.x);
    EXPECT_FLOAT_EQ(-1.0f, r.y);
    EXPECT_FLOAT_EQ(-1.0f, r.z);

    r = -v2;
    EXPECT_FLOAT_EQ(-0.5f, r.x);
    EXPECT_FLOAT_EQ(3.14f, r.y);
    EXPECT_FLOAT_EQ(-2, r.z);


    // Attribution
    v1.y = v1.x = v1.z = 1.0f;
    v2.x = 0.5f; v2.y = -3.14f; v2.z = 2;
    
    r = v1;
    EXPECT_FLOAT_EQ(1.0f, r.x);
    EXPECT_FLOAT_EQ(1.0f, r.y);
    EXPECT_FLOAT_EQ(1.0f, r.z);

    r = v2;
    EXPECT_FLOAT_EQ(0.5f, r.x);
    EXPECT_FLOAT_EQ(-3.14f, r.y);
    EXPECT_FLOAT_EQ(2.0f, r.z);


    // Comparison
    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v2 == v2);
}



TEST_F(Vector3DFloatTest, constants)
{
    Vector3D<FLOAT> v = Vector3D<FLOAT>(0.0f, 0.0f, 0.0f);

    // Zero vector
    EXPECT_FLOAT_EQ(v.x, Vector3D<FLOAT>::ZERO.x);
    EXPECT_FLOAT_EQ(v.y, Vector3D<FLOAT>::ZERO.y);
    EXPECT_FLOAT_EQ(v.z, Vector3D<FLOAT>::ZERO.z);

    // Unit vector
    v.x = v.y = v.z = 1.0f;
    EXPECT_FLOAT_EQ(v.x, Vector3D<FLOAT>::UNIT.x);
    EXPECT_FLOAT_EQ(v.y, Vector3D<FLOAT>::UNIT.y);
    EXPECT_FLOAT_EQ(v.z, Vector3D<FLOAT>::UNIT.z);
	
    // X-axis
	v.x = 1.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    EXPECT_FLOAT_EQ(v.x, Vector3D<FLOAT>::X_AXIS.x);
    EXPECT_FLOAT_EQ(v.y, Vector3D<FLOAT>::X_AXIS.y);
    EXPECT_FLOAT_EQ(v.z, Vector3D<FLOAT>::X_AXIS.z);

    // Y-axis
	v.x = 0.0f;
    v.y = 1.0f;
    v.z = 0.0f;
    EXPECT_FLOAT_EQ(v.x, Vector3D<FLOAT>::Y_AXIS.x);
    EXPECT_FLOAT_EQ(v.y, Vector3D<FLOAT>::Y_AXIS.y);
    EXPECT_FLOAT_EQ(v.z, Vector3D<FLOAT>::Y_AXIS.z);
    
    // Z-axis
	v.x = 0.0f;
    v.y = 0.0f;
    v.z = 1.0f;
    EXPECT_FLOAT_EQ(v.x, Vector3D<FLOAT>::Z_AXIS.x);
    EXPECT_FLOAT_EQ(v.y, Vector3D<FLOAT>::Z_AXIS.y);
    EXPECT_FLOAT_EQ(v.z, Vector3D<FLOAT>::Z_AXIS.z);
}
