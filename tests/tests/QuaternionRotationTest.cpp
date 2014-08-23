#include "gtest/gtest.h"
#include "DataType.h"
#include "QuaternionRotation.h"

using namespace nut;

class QuaternionRotationTest : public ::testing::Test
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
    //virtual void TearDown()
    //{
    //}
};


TEST_F(QuaternionRotationTest, getAndSetRotationFromEulersAngle)
{
    // Float test
    QuaternionRotation<float> f1, f2, f3;

    f1.setRotation(0.0f, 0.523598776f, 0.0f); // 30 degrees
    f2.setRotation(0.0f, 1.04719755f, 0.0f);  // 60 degrees

    f3 = f1 * f2; // 90 degrees

    EXPECT_NEAR(0.523598776f, f1.getRotationAngle(), 1e-5);
    EXPECT_NEAR(1.04719755f,  f2.getRotationAngle(), 1e-5);
    EXPECT_NEAR(1.57079633f,  f3.getRotationAngle(), 1e-5);

    // Double test
    QuaternionRotation<double> d1, d2, d3;

    d1.setRotation(0.0, 0.523598776, 0.0); // 30 degrees
    d2.setRotation(0.0, 1.04719755, 0.0);  // 60 degrees

    d3 = d1 * d2; // 90 degrees

    EXPECT_NEAR(0.523598776, d1.getRotationAngle(), 1e-10);
    EXPECT_NEAR(1.04719755, d2.getRotationAngle(), 1e-10);
    EXPECT_NEAR(1.57079633, d3.getRotationAngle(), 1e-7);
}

TEST_F(QuaternionRotationTest, getAndSetRotationFromAxis)
{
    // Float test
    QuaternionRotation<float> f1, f2, f3;

    f1.setRotation(0.0f, 0.0f, 1.0f, 0.523598776f); // 30 degrees
    f2.setRotation(0.0f, 0.0f, 1.0f, 1.04719755f);  // 60 degrees

    f3 = f1 * f2; // 90 degrees

    EXPECT_NEAR(0.523598776f, f1.getRotationAngle(), 1e-5);
    EXPECT_NEAR(1.04719755f,  f2.getRotationAngle(), 1e-5);
    EXPECT_NEAR(1.57079633f,  f3.getRotationAngle(), 1e-5);

    // Double test
    QuaternionRotation<double> d1, d2, d3;

    d1.setRotation(0.0, 0.0, 1.0, 0.523598776); // 30 degrees
    d2.setRotation(0.0, 0.0, 1.0, 1.04719755);  // 60 degrees

    d3 = d1 * d2; // 90 degrees

    EXPECT_NEAR(0.523598776, d1.getRotationAngle(), 1e-10);
    EXPECT_NEAR(1.04719755, d2.getRotationAngle(), 1e-10);
    EXPECT_NEAR(1.57079633, d3.getRotationAngle(), 1e-7);
}

TEST_F(QuaternionRotationTest, rotate)
{
    // Float test
    QuaternionRotation<float> f1, f2, f3;

    f1.setRotation(0.0f, 0.0f, 1.0f, 0.523598776f); // 30 degrees
    f2.setRotation(0.0f, 0.0f, 1.0f, 1.04719755f);  // 60 degrees
    f3.setRotation(0.0f, 0.0f, 1.0f, 1.57079633f);  // 90 degrees

    float x = 1.0f, y = 0.0f, z = 0.0f;

    f1.rotate(x, y, z);
    EXPECT_NEAR(0.866025f, x, 1e-5);
    EXPECT_NEAR(0.5f, y, 1e-5);
    EXPECT_NEAR(0.0f, z, 1e-5);

    x = 1.0f; y = 0.0f; z = 0.0f;
    f2.rotate(x, y, z);
    EXPECT_NEAR(0.5f, x, 1e-5);
    EXPECT_NEAR(0.866025f, y, 1e-5);
    EXPECT_NEAR(0.0f, z, 1e-5);

    x = 1.0f; y = 0.0f; z = 0.0f;
    f3.rotate(x, y, z);
    EXPECT_NEAR(0.0f, x, 1e-5);
    EXPECT_NEAR(1.0f, y, 1e-5);
    EXPECT_NEAR(0.0f, z, 1e-5);


    // Double test
    QuaternionRotation<double> d1, d2, d3;
    
    d1.setRotation(0.0, 0.0, 1.0, 0.523598776); // 30 degrees
    d2.setRotation(0.0, 0.0, 1.0, 1.04719755);  // 60 degrees
    d3.setRotation(0.0, 0.0, 1.0, 1.57079633);  // 90 degrees

    double xd = 1.0, yd = 0.0, zd = 0.0;

    d1.rotate(xd, yd, zd);
    EXPECT_NEAR(0.866025, xd, 1e-6);
    EXPECT_NEAR(0.5, yd, 1e-9);
    EXPECT_NEAR(0.0, zd, 1e-10);

    xd = 1.0; yd = 0.0; zd = 0.0;
    d2.rotate(xd, yd, zd);
    EXPECT_NEAR(0.5, xd, 1e-6);
    EXPECT_NEAR(0.866025, yd, 1e-6);
    EXPECT_NEAR(0.0, zd, 1e-10);

    xd = 1.0; yd = 0.0; zd = 0.0;
    d3.rotate(xd, yd, zd);
    EXPECT_NEAR(0.0, xd, 1e-8);
    EXPECT_NEAR(1.0, yd, 1e-10);
    EXPECT_NEAR(0.0, zd, 1e-10);
}

TEST_F(QuaternionRotationTest, inverse)
{
    // Float test
    QuaternionRotation<float> f1, f2, f3;

    f1.setRotation(0.0f, 0.0f, 1.0f, 0.523598776f); // 30 degrees
    f2.setRotation(0.0f, 0.0f, 1.0f, 1.04719755f);  // 60 degrees
    f3.setRotation(0.0f, 0.0f, 1.0f, 1.57079633f);  // 90 degrees

    float x = 1.0f, y = 0.0f, z = 0.0f;

    f1.rotate(x, y, z);
    f1 = f1.inverse();
    f1.rotate(x, y, z);
    EXPECT_NEAR(1.0f, x, 1e-7);
    EXPECT_NEAR(0.0f, y, 1e-7);
    EXPECT_NEAR(0.0f, z, 1e-7);

    x = 1.0f; y = 0.0f; z = 0.0f;
    f2.rotate(x, y, z);
    f2 = f2.inverse();
    f2.rotate(x, y, z);
    EXPECT_NEAR(1.0f, x, 1e-7);
    EXPECT_NEAR(0.0f, y, 1e-7);
    EXPECT_NEAR(0.0f, z, 1e-7);

    x = 1.0f; y = 0.0f; z = 0.0f;
    f3.rotate(x, y, z);
    f3 = f3.inverse();
    f3.rotate(x, y, z);
    EXPECT_NEAR(1.0f, x, 1e-6);
    EXPECT_NEAR(0.0f, y, 1e-7);
    EXPECT_NEAR(0.0f, z, 1e-7);


    // Double test
    QuaternionRotation<double> d1, d2, d3;
    
    d1.setRotation(0.0, 0.0, 1.0, 0.523598776); // 30 degrees
    d2.setRotation(0.0, 0.0, 1.0, 1.04719755);  // 60 degrees
    d3.setRotation(0.0, 0.0, 1.0, 1.57079633);  // 90 degrees

    double xd = 1.0, yd = 0.0, zd = 0.0;

    d1.rotate(xd, yd, zd);
    d1 = d1.inverse();
    d1.rotate(xd, yd, zd);
    EXPECT_NEAR(1.0, xd, 1e-10);
    EXPECT_NEAR(0.0, yd, 1e-10);
    EXPECT_NEAR(0.0, zd, 1e-10);

    xd = 1.0; yd = 0.0; zd = 0.0;
    d2.rotate(xd, yd, zd);
    d2 = d2.inverse();
    d2.rotate(xd, yd, zd);
    EXPECT_NEAR(1.0, xd, 1e-10);
    EXPECT_NEAR(0.0, yd, 1e-10);
    EXPECT_NEAR(0.0, zd, 1e-10);

    xd = 1.0; yd = 0.0; zd = 0.0;
    d3.rotate(xd, yd, zd);
    d3 = d3.inverse();
    d3.rotate(xd, yd, zd);
    EXPECT_NEAR(1.0, xd, 1e-10);
    EXPECT_NEAR(0.0, yd, 1e-10);
    EXPECT_NEAR(0.0, zd, 1e-10);
}

TEST_F(QuaternionRotationTest, lerp)
{
    QuaternionRotation<float> q1, q2;

    q1.setRotation(0.0f, 0.0f, 1.0f, 0.0f);
    q2.setRotation(0.0f, 0.0f, 1.0f, Math<float>::deg2rad(90.0f));
    
    QuaternionRotation<float> quat = QuaternionRotation<float>::lerp(q1, q2, 0.0f);
    
    EXPECT_NEAR(0.0f, quat.getRotationAngle(), 1e-5);
    
    quat = QuaternionRotation<float>::lerp(q1, q2, 0.5f);
    EXPECT_NEAR(0.785398163f, quat.getRotationAngle(), 1e-5);

    quat = QuaternionRotation<float>::lerp(q1, q2, 1.0f);
    EXPECT_NEAR(1.57079633f, quat.getRotationAngle(), 1e-5);
}

TEST_F(QuaternionRotationTest, slerp)
{
    QuaternionRotation<float> q1, q2;

    q1.setRotation(0.0f, 0.0f, 1.0f, 0.0f);
    q2.setRotation(0.0f, 0.0f, 1.0f, Math<double>::deg2rad(90.0f));
    
    QuaternionRotation<float> quat = QuaternionRotation<float>::slerp(q1, q2, 0.0f);
    
    EXPECT_NEAR(0.0f, quat.getRotationAngle(), 1e-5);
    
    quat = QuaternionRotation<float>::slerp(q1, q2, 0.5f);
    EXPECT_NEAR(0.785398163f, quat.getRotationAngle(), 1e-5);

    quat = QuaternionRotation<float>::slerp(q1, q2, 1.0f);
    EXPECT_NEAR(1.57079633f, quat.getRotationAngle(), 1e-5);
}

TEST_F(QuaternionRotationTest, operatorMultply)
{
    // Float test
    QuaternionRotation<float> f1, f2, rf;

    f1.setRotation(0.0f, 0.0f, 1.0f, 0.523598776f); // 30 degrees
    f2.setRotation(0.0f, 0.0f, 1.0f, 1.04719755f);  // 60 degrees

    rf = f1 * f2;

    float x = 1.0f, y = 0.0f, z = 0.0f;

    rf.rotate(x, y, z);

    EXPECT_NEAR(0.0f, x, 1e-5);
    EXPECT_NEAR(1.0f, y, 1e-5);
    EXPECT_NEAR(0.0f, z, 1e-5);


    // Double test
    QuaternionRotation<double> d1, d2, rd;
    
    d1.setRotation(0.0, 0.0, 1.0, 0.523598776); // 30 degrees
    d2.setRotation(0.0, 0.0, 1.0, 1.04719755);  // 60 degrees

    rd = d1 * d2; // 90 degrees

    double xd = 1.0, yd = 0.0, zd = 0.0;

    rd.rotate(xd, yd, zd);

    EXPECT_NEAR(0.0, xd, 1e-9);
    EXPECT_NEAR(1.0, yd, 1e-10);
    EXPECT_NEAR(0.0, zd, 1e-10);
}