#pragma once
#include "ClangUnit.hpp"

class ClangUnitConcept : public ClangUnit
{
public:
    ClangUnitConcept(
        const std::vector<ParsedInputSource> &parsed_inputs)
        : ClangUnit(parsed_inputs)
    {
        this->set_test_suite_name("ConceptTesting");
    };

    virtual const std::string
    get_method_test_case_name(
        const ParsedMethod &parsed_method) const override;

    virtual const std::string
    get_method_test_case_body(
        const ParsedMethod &parsed_method,
        const ParsedClass &parsed_class) const override;

    virtual const TestCasesForParsedInput
    generate_tests_for_parsed_input_source(
        const ParsedInputSource &parsed_input_source) const override;
};