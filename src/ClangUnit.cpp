#include "ClangUnit.hpp"
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "RandomValueByType.hpp"

unsigned ClangUnit::STATIC_COUNTER = 0;

const std::string ClangUnit::get_default_test_suite_name() const
{
    return std::string("STUB_SUITE");
}

ClangUnit::ClangUnit(const std::vector<ParsedInputSource> &parsed_input_sources)
    : parsed_input_sources(parsed_input_sources)
{
    this->test_suite_name = this->get_default_test_suite_name();
}

std::string ClangUnit::append_counter_to_test_name(const std::string &test_name) const
{
    return test_name + std::to_string(STATIC_COUNTER++);
}

const TestCase ClangUnit::generate_test_for_method(const ParsedMethod &parsed_method,
                                                   const ParsedClass &parsed_class) const
{
    std::string suite_name = this->get_test_suite_name();
    std::string test_name = this->get_method_test_case_name(parsed_method);
    std::string body = this->get_method_test_case_body(parsed_method, parsed_class);

    return TestCase(suite_name, test_name, body);
}

const TestCase ClangUnit::generate_test_for_function(const ParsedFunction &parsed_function) const
{
    std::string suite_name = this->get_test_suite_name();
    std::string test_name = this->get_function_test_case_name(parsed_function);
    std::string body = this->get_function_test_case_body(parsed_function);

    return TestCase(suite_name, test_name, body);
}

const std::vector<TestCase> ClangUnit::generate_tests_for_template_method(const ParsedMethod &parsed_method,
                                                                          const ParsedClass &parsed_class) const
{
    std::string suite_name = this->get_test_suite_name();
    std::string test_name = this->get_method_test_case_name(parsed_method);

    std::vector<TestCase> result;
    for (auto &&type : get_fundamental_types())
    {
        std::string body = this->get_template_method_test_case_body(parsed_method, parsed_class, type);
        result.push_back(TestCase(suite_name, test_name, body));
    }

    return result;
}

const std::vector<TestCase> ClangUnit::generate_tests_for_template_function(const ParsedFunction &parsed_function) const
{
    std::string suite_name = this->get_test_suite_name();
    std::string test_name = this->get_function_test_case_name(parsed_function);

    std::vector<TestCase> result;
    for (auto &&type : get_fundamental_types())
    {
        std::string body = this->get_template_function_test_case_body(parsed_function, type);
        result.push_back(TestCase(suite_name, test_name, body));
    }

    return result;
}

const TestCasesForParsedInput ClangUnit::prepared_test_cases(const TestCasesForParsedInput &tcases) const
{
    std::vector<TestCase> new_cases;
    for (auto &&tcase : tcases.get_test_cases())
    {
        new_cases.push_back(TestCase(tcase.get_test_suite_name(),
                                     this->append_counter_to_test_name(tcase.get_test_case_name()),
                                     tcase.get_test_case_body()));
    }
    return TestCasesForParsedInput(tcases.get_input_path(), new_cases);
}

const TestCasesForParsedInput ClangUnit::generate_tests_for_parsed_input_source(const ParsedInputSource &parsed_input_source) const
{
    std::vector<TestCase> result = {};
    for (auto &&method : parsed_input_source.get_methods())
    {
        llvm::outs() << "Processing method with name " << method.get_name() << '\n';
        if (true)
        {
            auto cls = parsed_input_source.get_classes()[method.get_class_name()];
            if (method.get_is_templated())
            {
                auto template_tests = this->generate_tests_for_template_method(method, cls);
                result.insert(result.end(),
                              template_tests.begin(),
                              template_tests.end());
            }
            else
            {
                llvm::outs() << "DEBUG! Seeing non templated method and generating a test!" << method.get_name() << "\n";
                result.push_back(this->generate_test_for_method(method, cls));
            }
        }
    }
    for (auto &&function : parsed_input_source.get_functions())
    {
        llvm::outs() << function.get_name() << ": " << function.get_is_templated() << "\n";
        if (function.get_is_templated())
        {
            auto template_tests = this->generate_tests_for_template_function(function);
            result.insert(result.end(),
                          template_tests.begin(),
                          template_tests.end());
        }
        else
        {
            llvm::outs() << "Processing f with name " << function.get_name() << '\n';
            result.push_back(this->generate_test_for_function(function));
        }
    }
    return TestCasesForParsedInput(parsed_input_source.get_path(), result);
}

std::vector<TestCasesForParsedInput> ClangUnit::generate_tests() const
{
    std::vector<TestCasesForParsedInput> result = {};
    for (auto &&current_parsed_input_source : this->parsed_input_sources)
    {
        auto generated_for_input = this->generate_tests_for_parsed_input_source(current_parsed_input_source);
        generated_for_input = prepared_test_cases(generated_for_input);
        result.push_back(generated_for_input);
    }
    return result;
}

std::string ClangUnit::get_test_suite_name() const
{
    return this->test_suite_name;
}

void ClangUnit::set_test_suite_name(const std::string &new_name)
{
    this->test_suite_name = new_name;
}
