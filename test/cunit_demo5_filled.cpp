#include <gtest/gtest.h>														   //clang-unit: System library
#include "/media/blk/HDD/llvm-project/clang-tools-extra/clang-unit/test/demo5.cpp" //clang-unit: User library

TEST(STUB_SUITE, aSTUB_TEST0)
{
	auto result = a<int>((int)(-89383));
	ASSERT_EQ(result, (int)(-89383) + 10);
}
TEST(STUB_SUITE, aSTUB_TEST1)
{
	auto result = a<float>((float)(-1.183149));
	ASSERT_EQ(result, (float)(-1.183149) + 10);
}
TEST(STUB_SUITE, aSTUB_TEST2)
{
	auto result = a<double>((double)(-2.349298));
	ASSERT_EQ(result, (double)(-2.349298) + 10);
}
TEST(STUB_SUITE, aSTUB_TEST3)
{
	auto result = a<unsigned int>((unsigned int)(36915));
	ASSERT_EQ(result, (unsigned int)(36915) + 10);
}
TEST(STUB_SUITE, aSTUB_TEST4)
{
	auto result = a<long long>((long long)(-7747793));
	ASSERT_EQ(result, (long long)(-7747793) + 10);
}
TEST(STUB_SUITE, aSTUB_TEST5)
{
	auto result = a<char>((char)('i'));
	ASSERT_EQ(result, (char)('i') + 10);
}
TEST(STUB_SUITE, aSTUB_TEST6)
{
	auto result = a<unsigned char>((unsigned char)('0'));
	ASSERT_EQ(result, (unsigned char)('0') + 10);
}
TEST(STUB_SUITE, aSTUB_TEST7)
{
	auto result = a<short>((short)(-492));
	ASSERT_EQ(result, (short)(-492) + 10);
}
