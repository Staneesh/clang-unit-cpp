#pragma once
#include <optional>
#include <map>

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"

#include "interfaces/GeneratesIncludes.hpp"
#include "interfaces/HandlesOutputFiles.hpp"
#include "interfaces/TestsMethods.hpp"
#include "interfaces/TestsFunctions.hpp"
#include "interfaces/TestsTemplates.hpp"

#include "InputParser.hpp"
#include "TestCasesForParsedInput.hpp"

// stanisz: This class should be about constructing Tests (and possibly suites) based
//          on the parsed input sources. The centralization mechanism will then
//          aggregate all this and write to proper files.
class ClangUnit : protected virtual TestsMethods, protected virtual TestsFunctions, protected virtual TestsTemplates
{
private:
    // stanisz: Members
    const std::vector<ParsedInputSource> &parsed_input_sources; // stanisz: No ability to change parsed contents
    static unsigned STATIC_COUNTER;                             // stanisz: Avoiding ambiguities in gtest, increments for every test generated.

    std::string test_suite_name;

    std::string append_counter_to_test_name(const std::string &test_name) const;
    // stanisz: Returns TestCasesForParsedInput that is preprocessed and validated.
    const TestCasesForParsedInput prepared_test_cases(const TestCasesForParsedInput &tcases) const;

protected:
    // stanisz: This is called by ClangUnit() constructor. If the user would like to change
    //          only test_suite_name, he could override this function without having to
    //          override the function that uses get_test_suite_name() and invoking
    //          set_test_suite_name() beforehand.
    virtual const std::string get_default_test_suite_name() const;

    // stanisz: Returns a TestCase for a given parsed_method.
    virtual const TestCase generate_test_for_method(const ParsedMethod &parsed_method,
                                                    const ParsedClass &parsed_class) const;

    // stanisz: Returns a TestCase for a given parsed_function.
    virtual const TestCase generate_test_for_function(const ParsedFunction &parsed_function) const;

    // stanisz: Returns TestCases for a given parsed_method.
    virtual const std::vector<TestCase> generate_tests_for_template_method(const ParsedMethod &parsed_method,
                                                                           const ParsedClass &parsed_class) const;

    // stanisz: Returns TestCases for a given parsed_function.
    virtual const std::vector<TestCase> generate_tests_for_template_function(const ParsedFunction &parsed_function) const;

    // stanisz: Returns TestCasesForParsedInput that represents a collection of test cases for a given
    //          parsed_input_source.
    virtual const TestCasesForParsedInput generate_tests_for_parsed_input_source(const ParsedInputSource &parsed_input_source) const;

public:
    ClangUnit() = delete;
    ClangUnit(const std::vector<ParsedInputSource> &parsed_input_sources);
    virtual ~ClangUnit() = default;

    // stanisz: Returns test_suite_name.
    std::string get_test_suite_name() const;
    // stanisz: Sets test_suite_name to a new value.
    void set_test_suite_name(const std::string &new_name);

    // stanisz: This generates tests for all parsed input sources using a defined (possibly by user)
    //          algorithm. The user can create many different ClangUnit implemetations. All of them
    //          will be able to generate_tests() using their own implementations. TestsWriter class
    //          is resposible for the final aggregation by output path. So, if you have two
    //          ClangUnit implementations that both generate tests for the same input file,
    //          TestsWriter will be able to aggregate the results from both generate_tests() calls
    //          you perform.
    std::vector<TestCasesForParsedInput> generate_tests() const;
};
