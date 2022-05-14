#include <gtest/gtest.h>														  //clang-unit: System library
#include "/media/blk/HDD/llvm-project/clang-tools-extra/clang-unit/test/test.cpp" //clang-unit: User library

TEST(SetterTesting, setSideSetterTest0)
{
	Square instance = Square();
	float value = -2.520563;
	instance.setSide(value);
	ASSERT_EQ(instance.getSide(), value);
}
TEST(ConstructorTesting, SquareConstructorTest1)
{
	Square instance = Square();
	ASSERT_EQ(instance.getSide(), float());
	ASSERT_EQ(instance.getArea(), float());
}
TEST(ConstructorTesting, SquareConstructorTest2)
{
	Square instance = Square((float)(-1.183149));
	ASSERT_EQ(instance.getSide(), (float)(-1.183149));
	ASSERT_EQ(instance.getArea(), (float)(-1.183149) * (float)(-1.183149));
}
