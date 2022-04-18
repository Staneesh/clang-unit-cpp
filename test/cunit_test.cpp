#include <gtest/gtest.h> //clang-unit: System library
#include "/media/blk/HDD/llvm-project/clang-tools-extra/clang-unit/test/test.cpp" //clang-unit: User library

TEST(STUB_SUITE, get_lengthSTUB_TEST0)
{
	Outer::Inner::NiceStruct instance;
	unsigned int result = instance.get_length();
	ASSERT_EQ(result, /*Fill me!*/);

}
TEST(STUB_SUITE, methodSTUB_TEST1)
{
	StandaloneStruct instance;
	instance.method((int)(-89383), (long long)(-6930886), (long)(-1692777), (short)(-915), (unsigned int)(47793), (float)(-0.592654), (double)(-1.005668), (float)(-2.304689), (bool)(1));
	ASSERT_EQ(/*Fill me!*/, /*Fill me!*/);

}
TEST(STUB_SUITE, return_structSTUB_TEST2)
{
	StandaloneStruct instance;
	Outer::Inner::NiceStruct result = instance.return_struct((Outer::Inner::NiceStruct &)(Outer::Inner::NiceStruct &));
	ASSERT_EQ(result, /*Fill me!*/);

}
TEST(STUB_SUITE, free_functionSTUB_TEST3)
{
	int result = free_function((int)(-41421), (int)(-2362));
	ASSERT_EQ(result, /*Fill me!*/);

}
TEST(STUB_SUITE, get_lengthSTUB_TEST_CHILD7)
{
	Outer::Inner::NiceStruct instance;
	unsigned int result = instance.get_length();
	ASSERT_EQ(result, /*Fill me!*/);

}
TEST(STUB_SUITE, methodSTUB_TEST_CHILD8)
{
	StandaloneStruct instance;
	instance.method((int)(-5211), (long long)(-1595368), (long)(-4702567), (short)(-429), (unsigned int)(65782), (float)(-1.202833), (double)(-0.389371), (float)(-0.326426), (bool)(1));
	ASSERT_EQ(/*Fill me!*/, /*Fill me!*/);

}
TEST(STUB_SUITE, return_structSTUB_TEST_CHILD9)
{
	StandaloneStruct instance;
	Outer::Inner::NiceStruct result = instance.return_struct((Outer::Inner::NiceStruct &)(Outer::Inner::NiceStruct &));
	ASSERT_EQ(result, /*Fill me!*/);

}
TEST(STUB_SUITE, free_functionSTUB_TEST_CHILD10)
{
	ASSERT_EQ(free_function((int)(-3135), (int)(-13929)), free_function((int)(-79802), (int)(-34022)));

}
