#include "TestsMethods.hpp"
#include "SharedGenericTestGen.hpp"

const std::string TestsMethods::get_method_test_case_name(const ParsedMethod &parsed_method) const
{
    return parsed_method.get_name() + "STUB_TEST";
}

const std::string TestsMethods::get_method_test_case_body(const ParsedMethod &parsed_method,
                                                          const ParsedClass &parsed_class) const
{
    std::string result = "";
    result += tabbing() + parsed_method.get_class_name() + " instance" + end_of_line();
    if (parsed_method.get_return_type() != "void")
    {
        result += tabbing() + parsed_method.get_return_type() + " result = " + "instance." + method_call(parsed_method) + ";\n";
        result += tabbing() + assert_eq("result", fill_me());
    }
    else
    {
        result += tabbing() + "instance." + method_call(parsed_method) + end_of_line();
        result += tabbing() + assert_eq(fill_me(), fill_me());
    }

    return result;
}
