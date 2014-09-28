#include "gtest/gtest.h"
#include "Vector2D.h"

#undef FLOAT
#define FLOAT double

using namespace nut;

class Vector2DDoubleTest : public ::testing::Test
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

TEST_F(Vector2DDoubleTest, constructors)
{
    // Default constructor
    Vector2D<FLOAT> v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    
    // Constructor
    Vector2D<FLOAT> u( 3.1459f, -2.0f);
    EXPECT_FLOAT_EQ(u.x, 3.1459f);
    EXPECT_FLOAT_EQ(u.y, -2.0f);
    
    // Copy constructor
    v = u;
    EXPECT_FLOAT_EQ(v.x, 3.1459f);
    EXPECT_FLOAT_EQ(v.y, -2.0f);
}



// Methods

TEST_F(Vector2DDoubleTest, length)
{
    // v = (0, 0)
    Vector2D<FLOAT> v;
    EXPECT_FLOAT_EQ(0.0f, v.length());
        
    // u = (1, 1)
    Vector2D<FLOAT> u(1.0f, 1.0f);
    EXPECT_NEAR(sqrt(2.0f), u.length(), 1e-20);
        
    // w = (1, 0)
    Vector2D<FLOAT> w(1.0f, 0.0f);
    EXPECT_FLOAT_EQ(1.0f, w.length());
        
    // x = (0, 1)
    Vector2D<FLOAT> x(0.0f, 1.0f);
    EXPECT_FLOAT_EQ(1.0f, x.length());
        
    // y = (7.98, -2.5)
    Vector2D<FLOAT> y(7.98f, -2.5f);
    EXPECT_NEAR(8.362439835359056, (double)y.length(), 1e-7);
}



TEST_F(Vector2DDoubleTest, slength)
{
    // v = (0, 0)
    Vector2D<FLOAT> v;
    EXPECT_FLOAT_EQ(0.0f, v.slength());

    // u = (1, 1)
    Vector2D<FLOAT> u(1.0f, 1.0f);
    EXPECT_NEAR(2.0f, u.slength(), 1e-20);
        
    // w = (1, 0)
    Vector2D<FLOAT> w(1.0f, 0.0f);
    EXPECT_FLOAT_EQ(1.0f, w.slength());
        
    // x = (0, 1)
    Vector2D<FLOAT> x(0.0f, 1.0f);
    EXPECT_FLOAT_EQ(1.0f, x.slength());
        
    // y = (7.98, -2.5)
    Vector2D<FLOAT> y(7.98f, -2.5f);
    EXPECT_NEAR(69.9304, y.slength(), 1e-6);
}



TEST_F(Vector2DDoubleTest, normalize)
{
    Vector2D<FLOAT> u1(0, 0), u2(1, 1), u3(1, 0), u4(0, 1), u5(7.98f, -2.5f);

    // u1 = (0, 0)
    u1.normalize();
    EXPECT_NEAR(0.0f, u1.length(), 1e-20);

    // u2 = (1, 1)
    u2.normalize();
    EXPECT_NEAR(1.0f, u2.length(), 1e-15);

    // u3 = (1, 0)
    u3.normalize();
    EXPECT_NEAR(1.0f, u3.length(), 1e-20);

    // u4 = (0, 1)
    u4.normalize();
    EXPECT_NEAR(1.0f, u4.length(), 1e-20);

    // u5 = (7.98, -2.5)
    u5.normalize();
    EXPECT_NEAR(1.0f, u5.length(), 1e-20);



    Vector2D<FLOAT> w1(3.1415f, -45.567f), w2(3458.0f, -10000.f), w3(-98.234f, -4457.f), w4(0, 1.3344f), w5(7.98f, 0);

    w1.normalize();
    EXPECT_NEAR(1.0f, w1.length(), 1e-20);

    w2.normalize();
    EXPECT_NEAR(1.0f, w2.length(), 1e-20);

    w3.normalize();
    EXPECT_NEAR(1.0f, w3.length(), 1e-15);

    w4.normalize();
    EXPECT_NEAR(1.0f, w4.length(), 1e-20);

    w5.normalize();
    EXPECT_NEAR(1.0f, w5.length(), 1e-20);
}



TEST_F(Vector2DDoubleTest, scale)
{
    Vector2D<FLOAT> u1(0, 0), u2(1, 1), u3(1, 0), u4(0, 1), u5(1, 1);

    // u1 = (0, 0)
    u1.scale(4.0f, 3.5f);
    EXPECT_NEAR(0.0f, u1.length(), 1e-20);

    // u2 = (1, 1)
    u2.scale(5.f, 5.f);
    EXPECT_NEAR(7.0710678118654752440084436210484903928483593768847403, u2.length(), 1e-20);

    // u3 = (1, 0)
    u3.scale(5.f, 5.f);
    EXPECT_NEAR(5.0f, u3.length(), 1e-20);

    // u4 = (0, 1)
    u4.scale(5.f, 5.f);
    EXPECT_NEAR(5.0f, u4.length(), 1e-20);

    // u5 = (1, 1)
    u5.scale(5, 3);
    EXPECT_NEAR(std::sqrt(34.0), u5.length(), 1e-20);
}



TEST_F(Vector2DDoubleTest, orientedArea)
{
    Vector2D<FLOAT> u1(0, 0), u2(1, 1), u3(-1.0f, 0.0f), u4(234.9898f, -1.22343f),
                    u5(-2345.777f, -7878.887f), u6(1, 0), u7(0, 1);

    EXPECT_NEAR(0.0f, u1.orientedArea(u2), 1e-20);
    EXPECT_NEAR(0.0f, u2.orientedArea(u1), 1e-20);

    EXPECT_NEAR(0.0f, u3.orientedArea(u6), 1e-20);
    EXPECT_NEAR(0.0f, u6.orientedArea(u3), 1e-20);

    EXPECT_NEAR(-1.0f, u3.orientedArea(u7), 1e-20);
    EXPECT_NEAR(1.0f, u7.orientedArea(u3), 1e-20);

    EXPECT_NEAR(1.0f, u6.orientedArea(u7), 1e-20);
    EXPECT_NEAR(-1.0f, u7.orientedArea(u6), 1e-20);
}



TEST_F(Vector2DDoubleTest, project)
{
    Vector2D<FLOAT> r;
    Vector2D<FLOAT> v1(1, 1), v2(1, 0), v3(0, 1), v4(2, 1), v5(1, 3);
    
    r = v2.project(v1);

    EXPECT_NEAR(1.0f, r.x, 1e-20);
    EXPECT_NEAR(0.0f, r.y, 1e-20);

    r = v3.project(v1);

    EXPECT_NEAR(0.0f, r.x, 1e-20);
    EXPECT_NEAR(1.0f, r.y, 1e-20);

    r = v5.project(v4);

    EXPECT_NEAR(0.5f, r.x, 1e-20);
    EXPECT_NEAR(1.5f, r.y, 1e-20);
}



TEST_F(Vector2DDoubleTest, dotProduct)
{
    Vector2D<FLOAT> u1(0, 0), u2(1, 1), u3(2.23876f, 4.4444f), u4(234.9898f, -1.22343f), u5(-2345.777f, -7878.887f);

    EXPECT_NEAR(u1.x * u2.x + u1.y * u2.y, u1 * u2, 1e-20);
        
    EXPECT_NEAR(u3.x * u4.x + u3.y * u4.y, u3 * u4, 1e-20);
        
    EXPECT_NEAR(u4.x * u5.x + u4.y * u5.y, u4 * u5, 1e-20);
        
    EXPECT_NEAR(u5.x * u1.x + u5.y * u1.y, u5 * u1, 1e-20);
        
    EXPECT_NEAR(u5.x * u3.x + u5.y * u3.y, u5 * u3, 1e-20);
}



TEST_F(Vector2DDoubleTest, operators)
{
    Vector2D<FLOAT> r;
    Vector2D<FLOAT> v1(1, 1), v2(0.5f, -3.14f);

    // Multiplication by a scalar
    r = v1 * 5;
    EXPECT_FLOAT_EQ(5, r.x);
    EXPECT_FLOAT_EQ(5, r.y);

    r = 5 * v1;
    EXPECT_FLOAT_EQ(5, r.x);
    EXPECT_FLOAT_EQ(5, r.y);

    r = 5 * v2;
    EXPECT_FLOAT_EQ(5 * 0.5f, r.x);
    EXPECT_FLOAT_EQ(5 * (-3.14f), r.y);

    r = v2 * 5;
    EXPECT_FLOAT_EQ(5 * 0.5f, r.x);
    EXPECT_FLOAT_EQ(5 * (-3.14f), r.y);

    v2 *= 5;
    EXPECT_FLOAT_EQ(5 * 0.5f, v2.x);
    EXPECT_FLOAT_EQ(5 * (-3.14f), v2.y);
    


    // Division by a scalar    
    r = v1 / 5.0f;
    EXPECT_FLOAT_EQ(1.0f / 5.0f, r.x);
    EXPECT_FLOAT_EQ(1.0f / 5.0f, r.y);

    v1 /= 5.0f;
    EXPECT_FLOAT_EQ(1.0f / 5.0f, v1.x);
    EXPECT_FLOAT_EQ(1.0f / 5.0f, v1.y);


    // Vector addition
    v1.y = v1.x = 1.0f;
    v2.x = 0.5f; v2.y = -3.14f;
    
    r = v1 + v2;
    EXPECT_FLOAT_EQ(1.0f + 0.5f, r.x);
    EXPECT_FLOAT_EQ(1.0f - 3.14f, r.y);

    v1 += v2;
    EXPECT_FLOAT_EQ(1.0f + 0.5f, v1.x);
    EXPECT_FLOAT_EQ(1.0f - 3.14f, v1.y);


    // Vector subtraction
    v1.y = v1.x = 1.0f;
    v2.x = 0.5f; v2.y = -3.14f;
    
    r = v1 - v2;
    EXPECT_FLOAT_EQ(1.0f - 0.5f, r.x);
    EXPECT_FLOAT_EQ(1.0f + 3.14f, r.y);

    v1 -= v2;
    EXPECT_FLOAT_EQ(1.0f - 0.5f, v1.x);
    EXPECT_FLOAT_EQ(1.0f + 3.14f, v1.y);


    // Additive inverse
    v1.y = v1.x = 1.0f;
    v2.x = 0.5f; v2.y = -3.14f;
    
    r = -v1;
    EXPECT_FLOAT_EQ(-1.0f, r.x);
    EXPECT_FLOAT_EQ(-1.0f, r.y);

    r = -v2;
    EXPECT_FLOAT_EQ(-0.5f, r.x);
    EXPECT_FLOAT_EQ(3.14f, r.y);


    // Attribution
    v1.y = v1.x = 1.0f;
    v2.x = 0.5f; v2.y = -3.14f;
    
    r = v1;
    EXPECT_FLOAT_EQ(1.0f, r.x);
    EXPECT_FLOAT_EQ(1.0f, r.y);

    r = v2;
    EXPECT_FLOAT_EQ(0.5f, r.x);
    EXPECT_FLOAT_EQ(-3.14f, r.y);
    

    // Comparison
    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v2 == v2);
}



TEST_F(Vector2DDoubleTest, constants)
{
    Vector2D<FLOAT> v = Vector2D<FLOAT>(0.0f, 0.0f);

    // Zero vector
    EXPECT_FLOAT_EQ(v.x, Vector2D<FLOAT>::ZERO.x);
    EXPECT_FLOAT_EQ(v.y, Vector2D<FLOAT>::ZERO.y);

    // Unit vector
    v.x = v.y = 1.0f;
    EXPECT_FLOAT_EQ(v.x, Vector2D<FLOAT>::UNIT.x);
    EXPECT_FLOAT_EQ(v.y, Vector2D<FLOAT>::UNIT.y);
	
    // X-axis
	v.x = 1.0f;
    v.y = 0.0f;
    EXPECT_FLOAT_EQ(v.x, Vector2D<FLOAT>::X_AXIS.x);
    EXPECT_FLOAT_EQ(v.y, Vector2D<FLOAT>::X_AXIS.y);

    // Y-axis
	v.x = 0.0f;
    v.y = 1.0f;
    EXPECT_FLOAT_EQ(v.x, Vector2D<FLOAT>::Y_AXIS.x);
    EXPECT_FLOAT_EQ(v.y, Vector2D<FLOAT>::Y_AXIS.y);
}
