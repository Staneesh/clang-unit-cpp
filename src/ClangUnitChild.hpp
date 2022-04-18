#pragma once
#include "ClangUnit.hpp"

class ClangUnitChild : public ClangUnit
{
public:
    ClangUnitChild(const std::vector<ParsedInputSource> &parsed_input_sources) : ClangUnit(parsed_input_sources){};

    virtual const TestCase generate_test_for_function(const ParsedFunction &parsed_function) const override;
    virtual const TestCase generate_test_for_method(const ParsedMethod &parsed_method) const override;
    virtual const std::string get_function_test_case_body(const ParsedFunction &parsed_function) const override;
};