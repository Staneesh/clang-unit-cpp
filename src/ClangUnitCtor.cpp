#include "ClangUnitCtor.hpp"
#include <filesystem>
#include <iostream>

#include "interfaces/SharedGenericTestGen.hpp"

const std::string ClangUnitCtor::get_method_test_case_name(const ParsedMethod &parsed_method) const
{
    return parsed_method.get_name() + "ConstructorTest";
}

const std::string
ClangUnitCtor::get_method_test_case_body(
    const ParsedMethod &parsed_method,
    const ParsedClass &parsed_class) const
{
    std::string result = "";
    result += tabbing() + parsed_method.get_class_name() + " instance = " + method_call(parsed_method) + end_of_line();

    for (auto &&field : parsed_class.get_fields())
    {
        std::string field_accessing = field.get_declared_name(); // directly
        if (field.get_is_private())
        {
            field_accessing = "get" + field_accessing + "()";
            field_accessing[3] = std::toupper(field_accessing[3]);
        }

        std::string second = fill_me();
        if (parsed_method.get_parameters().size() == 0 && parsed_method.get_is_default())
        {
            second = field.get_type() + "()";
        }

        result += tabbing() + assert_eq("instance." + field_accessing,
                                        second);
    }

    return result;
}

const TestCasesForParsedInput
ClangUnitCtor::generate_tests_for_parsed_input_source(
    const ParsedInputSource &parsed_input_source) const
{
    std::vector<TestCase> result = {};
    for (auto &&method : parsed_input_source.get_methods())
    {
        bool testable =
            method.get_kind() == ParsedMethod::Kind::Constructor;
        if (testable)
        {
            auto classes = parsed_input_source.get_classes();
            auto cls = classes[method.get_class_name()];
            result.push_back(this->generate_test_for_method(method, cls));
        }
    }
    return TestCasesForParsedInput(
        parsed_input_source.get_path(), result);
}
