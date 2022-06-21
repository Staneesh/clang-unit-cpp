#include <gtest/gtest.h>														   //clang-unit: System library
#include "/media/blk/HDD/llvm-project/clang-tools-extra/clang-unit/test/demo4.cpp" //clang-unit: User library

TEST(STUB_SUITE, aSTUB_TEST0)
{
	int result = a((int)(-89383));
	ASSERT_EQ(result, (int)(-89383) + 10);
}
TEST(STUB_SUITE, cSTUB_TEST1)
{
	c((int)(-30886));
}
