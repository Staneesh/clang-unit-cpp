#include <gtest/gtest.h> //clang-unit-cpp: Required for running tests
#include "test.cpp"		 //clang-unit-cpp: Includes the tested file
// TODO: Smart way of capturing path to the tested file from clang args???

TEST(AutogeneratedStubSuite, NiceStructTestStub)
{
	Outer::Inner::NiceStruct::NiceStruct objectNiceStruct();
	/* Fill Me! */
	// TODO: Have a sequence of ASSERT_EQ that compare every member. Complex types? Recursion?
}

TEST(AutogeneratedStubSuite, NiceStructTestStub)
{
	// TODO: Have a real random values generator for args
	Outer::Inner::NiceStruct::NiceStruct objectNiceStruct(std::string &);
	/* Fill Me! */
}

TEST(AutogeneratedStubSuite, get_lengthTestStub)
{
	Outer::Inner::NiceStruct object;
	// TODO randomize arguments, what about complex types? Recursion?
	EXPECT_EQ(object.get_length(), 6);
}

TEST(AutogeneratedStubSuite, methodTestStub)
{
	StandaloneStruct object;
	object.method();
	/* Fill Me! */
}

TEST(AutogeneratedStubSuite, return_structTestStub)
{
	StandaloneStruct object;
	// TODO: THis needs to check complex return types in a smart way. What if a struct has a struct as a field?
	/*
	struct A{
		std::pair<int, int> b;
		int c;
	};
	May be ok to check if A1 == A2 based on every member, because b has '=' overloaded.
	struct A {
		int a, int b;
	}
	struct B {
		A a;
		int c;
	}
	May not be so easy, and will need to call 'compare' of some sorts recursively??
	*/
	EXPECT_EQ(object.return_struct(1, 2, Outer::Inner::NiceStruct &), Outer::Inner::NiceStruct(1, 2, Outer::Inner::NiceStruct()));
}