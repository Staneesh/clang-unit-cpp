#include "ClangUnit.hpp"
#include <fstream>
#include <filesystem>
#include <algorithm>

/*
std::vector<std::string> ClangUnit::get_source_output_paths()
{
    auto result = this->get_input_source_paths();

    std::ranges::for_each(result, [this](std::string &s)
                          { s = this->to_output_source_path(s); });

    return result;
}

void ClangUnit::open_output_files()
{
    auto source_output_paths = this->get_source_output_paths();
    HandlesOutputFiles::open_output_files(source_output_paths, this->output_files);
}
*/

/*
void ClangUnit::generate_unit_test_file_preludes()
{
    if (this->output_files.empty())
    {
        llvm::errs() << "ClangUnit.output_files empty in generate_unit_test_file_preludes! Exiting...\n";
        exit(1);
    }
    for (auto &&source_input_path : this->source_input_paths)
    {
        std::string result = this->get_includes(source_input_path);
        this->write_to_file(result, this->output_files[this->to_output_source_path(source_input_path)]);
    }
}
*/

ClangUnit::ClangUnit(const std::vector<ParsedInputSource> &parsed_input_sources)
    : parsed_input_sources(parsed_input_sources)
{
}

const std::string ClangUnit::get_test_suite_name(const ParsedMethod &parsed_method) const
{
    return parsed_method.get_name() + "_DEFAULT_SUITE";
}

const std::string ClangUnit::get_test_case_name(const ParsedMethod &parsed_method) const
{
    return parsed_method.get_name() + "_DEFAULT_TEST";
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

const std::vector<TestCase> ClangUnit::generate_tests_for_parsed_input_source(const ParsedInputSource &parsed_input_source) const
{
    std::vector<TestCase> result = {};
    for (auto &&method : parsed_input_source.get_methods())
    {
        result.push_back(this->generate_test_for_method(method));
    }
    return result;
}

std::vector<TestCase> ClangUnit::generate_tests() const
{
    std::vector<TestCase> result = {};
    for (auto &&current_parsed_input_source : this->parsed_input_sources)
    {
        auto generated_for_input = this->generate_tests_for_parsed_input_source(current_parsed_input_source);
        result.insert(result.end(), generated_for_input.begin(), generated_for_input.end());
    }
    return result;
}