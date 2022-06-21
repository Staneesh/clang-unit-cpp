#pragma once

#include <string>
#include "../ParsedMethod.hpp"
#include "../ParsedFunction.hpp"
#include "../ParsedClass.hpp"

class TestsTemplates
{
private:
protected:
    // stanisz: Returns the body of the test case based on the parsed_method.
    virtual const std::string get_template_method_test_case_body(const ParsedMethod &parsed_method,
                                                                 const ParsedClass &parsed_class,
                                                                 std::string type) const;

    virtual const std::string get_template_function_test_case_body(const ParsedFunction &parsed_function, std::string type) const;

    virtual const std::vector<std::string> get_fundamental_types() const;

public:
    virtual ~TestsTemplates() = default;
};