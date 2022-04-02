#pragma once
#include <optional>
#include <map>

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"

class ClangUnit
{
    // stanisz: Members
    static std::shared_ptr<llvm::cl::OptionCategory> option_category;

    std::vector<std::string> source_input_paths;
    std::map<std::string, std::shared_ptr<std::ofstream>> output_files;

    // stanisz: Methods
    ClangUnit(clang::tooling::CommonOptionsParser &);

    std::string to_output_source_path(std::string &input_source_path);
    std::vector<std::string> get_source_output_paths();

    void open_output_files();
    void write_to_file(std::string &content, std::shared_ptr<std::ofstream> file);
    void generate_unit_test_file_preludes();

public:
    static std::optional<ClangUnit> init(int argc, const char **argv);
    bool run();
};
