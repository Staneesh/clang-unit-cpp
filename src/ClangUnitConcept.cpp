#include "ClangUnitConcept.hpp"
#include <filesystem>
#include <iostream>

#include "interfaces/SharedGenericTestGen.hpp"

const std::string ClangUnitConcept::get_method_test_case_name(const ParsedMethod &parsed_method) const
{
    return parsed_method.get_name() + "ConceptTest";
}

const std::string
ClangUnitConcept::get_method_test_case_body(
    const ParsedMethod &parsed_method,
    const ParsedClass &parsed_class) const
{
    std::string result = "";

    return result;
}

const TestCasesForParsedInput
ClangUnitConcept::generate_tests_for_parsed_input_source(
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
