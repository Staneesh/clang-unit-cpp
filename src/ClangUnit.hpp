#pragma once
#include <optional>
#include <map>

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "interfaces/GeneratesIncludes.hpp"
#include "interfaces/HandlesOutputFiles.hpp"

class ClangUnit : protected GeneratesIncludes, protected HandlesOutputFiles
{
private:
    // stanisz: Members
    static std::shared_ptr<llvm::cl::OptionCategory> option_category;

    std::vector<std::string> source_input_paths;
    std::map<std::string, std::shared_ptr<std::ofstream>> output_files;

    // stanisz: Methods
    std::vector<std::string> get_source_output_paths();
    void open_output_files();
    void generate_unit_test_file_preludes();

protected:
public:
    ClangUnit(int argc, const char **argv);
    virtual ~ClangUnit() = default;
    virtual bool run();
};
