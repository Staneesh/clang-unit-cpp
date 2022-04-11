#pragma once
#include <optional>
#include <map>

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "interfaces/GeneratesIncludes.hpp"
#include "interfaces/HandlesOutputFiles.hpp"

#include "InputParser.hpp"
#include "TestCase.hpp"

// stanisz: This class should be about constructing Tests (and possibly suites) based
//          on the parsed input sources. The centralization mechanism will then
//          aggregate all this and write to proper files.
class ClangUnit // : protected GeneratesIncludes, protected HandlesOutputFiles
{
private:
    // stanisz: Members
    const std::vector<ParsedInputSource> &parsed_input_sources; // stanisz: No ability to change parsed contents

    // stanisz: This should be handled by the centralization writing mechanism.
    // std::map<std::string, std::shared_ptr<std::ofstream>> output_files;
    // std::vector<std::string> get_source_output_paths();
    // void open_output_files();
    // void generate_unit_test_file_preludes();
protected:
    // stanisz: A single ClangUnit will be able to generate a single test suite. Seems logical.
    //          If I wanted to allow run-time changes, I would need to store more state in ClangUnit.
    //          In essence: set_test_suite_name( ... ) will sink the result to the object.
    virtual const std::string get_test_suite_name(const ParsedMethod &parsed_method) const;
    // stanisz: Same here.
    virtual const std::string get_test_case_name(const ParsedMethod &parsed_method) const;
    virtual const std::string get_test_case_body(const ParsedMethod &parsed_method) const;

    virtual const TestCase generate_test_for_method(const ParsedMethod &parsed_method) const;
    virtual const std::vector<TestCase> generate_tests_for_parsed_input_source(const ParsedInputSource &parsed_input_source) const;

public:
    ClangUnit() = delete;
    ClangUnit(const std::vector<ParsedInputSource> &parsed_input_sources);
    virtual ~ClangUnit() = default;

    std::vector<TestCase> generate_tests() const;
};
