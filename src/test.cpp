#include <gtest/gtest.h>   //clang-unit: System library
#include "InputParser.hpp" //clang-unit: User library

TEST(Parsing, ParsedInputsOK)
{
    char *argv[2];
    argv[0] = "p_name";
    argv[1] = "/media/blk/HDD/llvm-project/clang-tools-extra/clang-unit/test/test.cpp";
    auto parse_opt = ClangUnitParser::parse(1, (const char **)argv);
    ASSERT_EQ(parse_opt.has_value(), true);
}