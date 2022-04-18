#pragma once

#include "TestCase.hpp"
#include "interfaces/Printable.hpp"
#include <vector>

class TestCasesForParsedInput : protected virtual Printable
{
private:
    std::string input_source_path;
    std::vector<TestCase> test_cases;

public:
    TestCasesForParsedInput() = delete;
    TestCasesForParsedInput(const TestCasesForParsedInput &) = default;
    TestCasesForParsedInput &operator=(const TestCasesForParsedInput &) = default;
    TestCasesForParsedInput(const std::string &isp, const std::vector<TestCase> &tcases);
    const std::string &get_input_path() const;
    const std::vector<TestCase> &get_test_cases() const;
    void print() const override;
};