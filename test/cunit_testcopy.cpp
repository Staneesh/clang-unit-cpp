#include <gtest/gtest.h> //clang-unit: System library
#include "/media/blk/HDD/llvm-project/clang-tools-extra/clang-unit/test/testcopy.cpp" //clang-unit: User library

TEST(STUB_SUITE, get_lengthSTUB_TEST3)
{
	Outer::Inner::NiceStruct instance;
	unsigned int result = instance.get_length();
	ASSERT_EQ(result, /*Fill me!*/);

}
TEST(STUB_SUITE, methodSTUB_TEST4)
{
	StandaloneStruct instance;
	instance.method((int)(-41421), (long long)(-5202362), (long)(-490027), (short)(-690), (unsigned int)(20059), (float)(-2.856689), (double)(-2.748585), (float)(-1.907135), (bool)(0));
	ASSERT_EQ(/*Fill me!*/, /*Fill me!*/);

}
TEST(STUB_SUITE, return_structSTUB_TEST5)
{
	StandaloneStruct instance;
	Outer::Inner::NiceStruct result = instance.return_struct((Outer::Inner::NiceStruct &)(Outer::Inner::NiceStruct &));
	ASSERT_EQ(result, /*Fill me!*/);

}
