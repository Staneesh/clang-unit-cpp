#pragma once
#include <string>

#include "ParsedMethod.hpp"
#include "interfaces/Printable.hpp"

class TestCase : protected virtual Printable
{
private:
    std::string test_suite_name;
    std::string name;
    std::string body;

public:
    TestCase(const std::string &test_suite_name, const std::string &test_case_name, const std::string &test_case_body);
    TestCase() = default;
    std::string get_test_suite_name() const;
    std::string get_test_case_name() const;
    std::string get_test_case_body() const;
    void set_test_suite_name(const std::string &);
    void set_test_case_name(const std::string &);
    void set_test_case_body(const std::string &);
    // stanisz: Constructs a string based on TestCase contents for writing.
    std::string to_string() const;
    void print() const override;
};