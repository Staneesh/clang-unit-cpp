#include <gtest/gtest.h> //clang-unit: System library
#include "/media/blk/HDD/llvm-project/clang-tools-extra/clang-unit/test/testcopy.cpp" //clang-unit: User library

TEST(STUB_SUITE, get_lengthSTUB_TEST4)
{
	Outer::Inner::NiceStruct instance;
	unsigned int result = instance.get_length();
	ASSERT_EQ(result, /*Fill me!*/);

}
TEST(STUB_SUITE, methodSTUB_TEST5)
{
	StandaloneStruct instance;
	instance.method((int)(-90027), (long long)(-3368690), (long)(-2520059), (short)(-763), (unsigned int)(13926), (float)(-1.907135), (double)(-2.151891), (float)(-0.424808), (bool)(0));
	ASSERT_EQ(/*Fill me!*/, /*Fill me!*/);

}
TEST(STUB_SUITE, return_structSTUB_TEST6)
{
	StandaloneStruct instance;
	Outer::Inner::NiceStruct result = instance.return_struct((Outer::Inner::NiceStruct &)(Outer::Inner::NiceStruct &));
	ASSERT_EQ(result, /*Fill me!*/);

}
TEST(STUB_SUITE, get_lengthSTUB_TEST_CHILD11)
{
	Outer::Inner::NiceStruct instance;
	unsigned int result = instance.get_length();
	ASSERT_EQ(result, /*Fill me!*/);

}
TEST(STUB_SUITE, methodSTUB_TEST_CHILD12)
{
	StandaloneStruct instance;
	instance.method((int)(-23058), (long long)(-9133069), (long)(-5898167), (short)(-393), (unsigned int)(18456), (float)(-0.877550), (double)(-2.314073), (float)(-1.580235), (bool)(1));
	ASSERT_EQ(/*Fill me!*/, /*Fill me!*/);

}
TEST(STUB_SUITE, return_structSTUB_TEST_CHILD13)
{
	StandaloneStruct instance;
	Outer::Inner::NiceStruct result = instance.return_struct((Outer::Inner::NiceStruct &)(Outer::Inner::NiceStruct &));
	ASSERT_EQ(result, /*Fill me!*/);

}
