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
        result += tabbing() + parsed_function.get_return_type() + " result = " + function_call(parsed_function) + end_of_line();
        result += tabbing() + assert_eq("result", fill_me());
    }
    else
    {
        result += tabbing() + function_call(parsed_function) + end_of_line();
        result += tabbing() + assert_eq(fill_me(), fill_me());
    }

    return result;
}
