#pragma once

#include <string>
#include "../ParsedFunction.hpp"

class TestsFunctions
{
private:
protected:
    // stanisz: Returns the name of the test case based on the parsed_function
    virtual const std::string get_function_test_case_name(const ParsedFunction &parsed_function) const;
    // stanisz: Returns the body of the test case based on the parsed_function.
    virtual const std::string get_function_test_case_body(const ParsedFunction &parsed_function) const;

public:
    virtual ~TestsFunctions() = default;
};