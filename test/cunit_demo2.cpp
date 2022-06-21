#include <gtest/gtest.h> //clang-unit: System library
#include "/media/blk/HDD/llvm-project/clang-tools-extra/clang-unit/test/demo2.cpp" //clang-unit: User library

TEST(STUB_SUITE, SquareSTUB_TEST0)
{
	auto instance = Square();
	ASSERT_EQ(instance.side, /*Fill me!*/);
	ASSERT_EQ(instance.area, /*Fill me!*/);

}
TEST(STUB_SUITE, SquareSTUB_TEST1)
{
	auto instance = Square((int)(-89383));
	ASSERT_EQ(instance.side, /*Fill me!*/);
	ASSERT_EQ(instance.area, /*Fill me!*/);

}
TEST(STUB_SUITE, setSideSTUB_TEST2)
{
	Square instance ;
	instance.setSide((int)(-30886));
	ASSERT_EQ(/*Fill me!*/, /*Fill me!*/);

}
