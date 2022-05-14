#pragma once

#include <string>
#include "../ParsedMethod.hpp"
#include "../ParsedClass.hpp"

class TestsMethods
{
private:
protected:
    // stanisz: Returns the name of the test case based on the parsed_method.
    virtual const std::string get_method_test_case_name(const ParsedMethod &parsed_method) const;
    // stanisz: Returns the body of the test case based on the parsed_method.
    virtual const std::string get_method_test_case_body(const ParsedMethod &parsed_method,
                                                        const ParsedClass &parsed_class) const;

public:
    virtual ~TestsMethods() = default;
};