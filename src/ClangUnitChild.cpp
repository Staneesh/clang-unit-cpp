#include "ClangUnitChild.hpp"
#include <filesystem>
#include <iostream>

#include "interfaces/SharedGenericTestGen.hpp"
#include "RandomValueByType.hpp"

const std::string ClangUnitChild::get_method_test_case_name(const ParsedMethod &parsed_method) const
{
    return parsed_method.get_name() + "SetterTest";
}

const std::string
ClangUnitChild::get_method_test_case_body(
    const ParsedMethod &parsed_method,
    const ParsedClass &parsed_class) const
{
    std::string result = "";
    result += tabbing() + parsed_method.get_class_name() + " instance = " + parsed_method.get_class_name() + "()" + end_of_line();

    for (auto &&field : parsed_class.get_fields())
    {
        std::string fieldnlower = field.get_declared_name();
        fieldnlower[0] = std::toupper(fieldnlower[0]);
        if (parsed_method.get_name().find(fieldnlower) != std::string::npos)
        {
            if (field.get_is_private())
            {
                std::string rvstr = RandomValueByType::random_value_string(field.get_type());
                result += tabbing() + field.get_type() + " value = " + rvstr + end_of_line();
                result += tabbing() + "instance." + method_call(parsed_method, {"value"}) + end_of_line();
                std::string getten = "get" + field.get_declared_name() + "()";
                getten[3] = std::toupper(getten[3]);
                result += tabbing() + assert_eq("instance." + getten, "value");
            }
        }
    }

    return result;
}

const TestCasesForParsedInput
ClangUnitChild::generate_tests_for_parsed_input_source(
    const ParsedInputSource &parsed_input_source) const
{
    std::vector<TestCase> result = {};
    for (auto &&method : parsed_input_source.get_methods())
    {
        bool testable =
            (method.get_kind() == ParsedMethod::Kind::RegularMethod) && (method.get_name().find("set") != std::string::npos);
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
