#include "gtest/gtest.h"
#include "DataType.h"

using namespace nut;

class DataTypeTest : public ::testing::Test
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


TEST_F(DataTypeTest, typeSize)
{
    size_t size;

    size = sizeof(I8);
    EXPECT_TRUE(size == 1);

    size = sizeof(I16);
    EXPECT_TRUE(size == 2);

    size = sizeof(I32);
    EXPECT_TRUE(size == 4);

    size = sizeof(I64);
    EXPECT_TRUE(size == 8);

    size = sizeof(U8);
    EXPECT_TRUE(size == 1);

    size = sizeof(U16);
    EXPECT_TRUE(size == 2);

    size = sizeof(U32);
    EXPECT_TRUE(size == 4);

    size = sizeof(U64);
    EXPECT_TRUE(size == 8);

    size = sizeof(IPTR);
    EXPECT_TRUE(size == 8);
}



TEST_F(DataTypeTest, endianSwapU16)
{
    U16 value = 0x00C3;

    U16 swaped = DataType::endianSwapU16(value);

    EXPECT_TRUE(swaped == 0xC300);
}



TEST_F(DataTypeTest, endianSwapU32)
{
    U32 value = 0x0000AFC3;

    U32 swaped = DataType::endianSwapU32(value);

    EXPECT_TRUE(swaped == 0xC3AF0000);
}



TEST_F(DataTypeTest, endianSwapU64)
{
    U64 value = 0x00000000AFBECDDC;

    U64 swaped = DataType::endianSwapU64(value);

    EXPECT_TRUE(swaped == 0xDCCDBEAF00000000);
}



TEST_F(DataTypeTest, endianSwapI16)
{
    I16 value = 0x000A;

    I16 swaped = DataType::endianSwapI16(value);

    EXPECT_TRUE(swaped == 0x0A00);
}



TEST_F(DataTypeTest, endianSwapI32)
{
    I32 value = 0x0000AFC3;

    I32 swaped = DataType::endianSwapI32(value);

    EXPECT_TRUE(swaped == 0xC3AF0000);
}



TEST_F(DataTypeTest, endianSwapI64)
{
    I64 value = 0x00000000AFBECDDC;

    I64 swaped = DataType::endianSwapI64(value);
    
    EXPECT_TRUE(swaped == 0xDCCDBEAF00000000);
}



TEST_F(DataTypeTest, endianSwapFloat)
{
    IntFloat u;
    u.asInt = 0xAFBECDDC;
    u.asFloat = DataType::endianSwapFloat(u.asFloat);
    
    EXPECT_TRUE(u.asInt == 0xDCCDBEAF);
}



TEST_F(DataTypeTest, punning)
{
    float value = 7.0f;

    IntFloat u;
    u.asFloat = value;

    U32 cast = DataType::punning(value);

    // Because of the representation of float points,
    // the cast from F32 to U32 doesn't result in the
    // same value in decimal basis
    EXPECT_TRUE(cast == 0x40E00000);
}
