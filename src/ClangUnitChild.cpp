#include "ClangUnitChild.hpp"
#include <filesystem>
#include "interfaces/SharedGenericTestGen.hpp"

const TestCase ClangUnitChild::generate_test_for_method(const ParsedMethod &parsed_method) const
{
    std::string suite_name = this->get_test_suite_name();
    std::string test_name = this->get_method_test_case_name(parsed_method);
    std::string body = this->get_method_test_case_body(parsed_method);

    test_name += "_CHILD";

    return TestCase(suite_name, test_name, body);
}

const TestCase ClangUnitChild::generate_test_for_function(const ParsedFunction &parsed_function) const
{
    std::string suite_name = this->get_test_suite_name();
    std::string test_name = this->get_function_test_case_name(parsed_function);
    std::string body = this->get_function_test_case_body(parsed_function);

    test_name += "_CHILD";

    return TestCase(suite_name, test_name, body);
}

const std::string ClangUnitChild::get_function_test_case_body(const ParsedFunction &parsed_function) const
{
    std::string result = "";
    if (parsed_function.get_return_type() != "void")
    {
        result += "\tASSERT_EQ(" + function_call(parsed_function) + ", " + function_call(parsed_function) + ");\n";
    }

    return result;
}
