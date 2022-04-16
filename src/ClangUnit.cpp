#include "ClangUnit.hpp"
#include <fstream>
#include <filesystem>
#include <algorithm>

unsigned ClangUnit::STATIC_COUNTER = 0;

ClangUnit::ClangUnit(const std::vector<ParsedInputSource> &parsed_input_sources)
    : parsed_input_sources(parsed_input_sources)
{
}

const std::string ClangUnit::get_test_suite_name(const ParsedMethod &parsed_method) const
{
    return "STUB_SUITE";
}

const std::string ClangUnit::get_test_case_name(const ParsedMethod &parsed_method) const
{
    return parsed_method.get_name() + "STUB_TEST" + std::to_string(STATIC_COUNTER++);
}

const std::string ClangUnit::get_test_case_body(const ParsedMethod &parsed_method) const
{
    return std::string(); // stanisz: That's a todo.
}

const TestCase ClangUnit::generate_test_for_method(const ParsedMethod &parsed_method) const
{
    std::string suite_name = this->get_test_suite_name(parsed_method);
    std::string test_name = this->get_test_case_name(parsed_method);
    std::string body = this->get_test_case_body(parsed_method);

    return TestCase(suite_name, test_name, body);
}

const TestCasesForParsedInput ClangUnit::generate_tests_for_parsed_input_source(const ParsedInputSource &parsed_input_source) const
{
    std::vector<TestCase> result = {};
    for (auto &&method : parsed_input_source.get_methods())
    {
        result.push_back(this->generate_test_for_method(method));
    }
    return TestCasesForParsedInput(parsed_input_source.get_path(), result);
}

std::vector<TestCasesForParsedInput> ClangUnit::generate_tests() const
{
    std::vector<TestCasesForParsedInput> result = {};
    for (auto &&current_parsed_input_source : this->parsed_input_sources)
    {
        auto generated_for_input = this->generate_tests_for_parsed_input_source(current_parsed_input_source);
        result.push_back(generated_for_input);
    }
    return result;
}