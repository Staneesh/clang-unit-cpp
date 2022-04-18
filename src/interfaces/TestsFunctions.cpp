#include "TestsFunctions.hpp"

#include "SharedGenericTestGen.hpp"

const std::string TestsFunctions::get_function_test_case_name(const ParsedFunction &parsed_function) const
{
    return parsed_function.get_name() + "STUB_TEST";
}

const std::string TestsFunctions::get_function_test_case_body(const ParsedFunction &parsed_function) const
{
    std::string result = "";
    if (parsed_function.get_return_type() != "void")
    {
        result += "\t" + parsed_function.get_return_type() + " result = " + function_call(parsed_function) + ";\n";
        result += "\tASSERT_EQ(result, /*Fill me!*/);\n";
    }
    else
    {
        result += function_call(parsed_function) + ";\n";
        result += "\tASSERT_EQ(/*Fill me!*/, /*Fill me!*/);\n";
    }

    return result;
}
