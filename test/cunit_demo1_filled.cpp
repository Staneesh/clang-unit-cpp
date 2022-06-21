#include <gtest/gtest.h>														   //clang-unit: System library
#include "/media/blk/HDD/llvm-project/clang-tools-extra/clang-unit/test/demo1.cpp" //clang-unit: User library

TEST(STUB_SUITE, SquareSTUB_TEST0)
{
	auto instance = Square();
	// side;
	ASSERT_EQ(instance.getSide(), 0);
	// area;
	ASSERT_EQ(instance.getArea(), 0);
}
TEST(STUB_SUITE, SquareSTUB_TEST1)
{
	auto instance = Square((int)(-89383));
	// side;
	ASSERT_EQ(instance.getSide(), (int)(-89383));
	// area;
	ASSERT_EQ(instance.getArea(), (int)(-89383) * (int)(-89383));
}
TEST(STUB_SUITE, setSideSTUB_TEST2)
{
	Square instance;
	instance.setSide((int)(-30886));
	ASSERT_EQ(instance.getSide(), (int)(-30886));
}
TEST(STUB_SUITE, getAreaSTUB_TEST3)
{
	Square instance;
	int result = instance.getArea();
	ASSERT_EQ(result, 0);
}
TEST(STUB_SUITE, getSideSTUB_TEST4)
{
	Square instance;
	int result = instance.getSide();
	ASSERT_EQ(result, 0);
}
