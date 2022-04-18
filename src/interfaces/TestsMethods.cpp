#include "TestsMethods.hpp"
#include "SharedGenericTestGen.hpp"

const std::string TestsMethods::get_method_test_case_name(const ParsedMethod &parsed_method) const
{
    return parsed_method.get_name() + "STUB_TEST";
}

const std::string TestsMethods::get_method_test_case_body(const ParsedMethod &parsed_method) const
{
    std::string result = "";
    result += "\t" + parsed_method.get_class_name() + " instance;\n";
    if (parsed_method.get_return_type() != "void")
    {
        result += "\t" + parsed_method.get_return_type() + " result = " + "instance." + method_call(parsed_method) + ";\n";
        result += "\tASSERT_EQ(result, /*Fill me!*/);\n";
    }
    else
    {
        result += "\tinstance." + method_call(parsed_method) + ";\n";
        result += "\tASSERT_EQ(/*Fill me!*/, /*Fill me!*/);\n";
    }

    return result;
}
