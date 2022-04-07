#include "ClangUnit.hpp"
#include <fstream>
#include <filesystem>
#include <algorithm>

std::shared_ptr<llvm::cl::OptionCategory> ClangUnit::option_category = std::make_shared<llvm::cl::OptionCategory>("ClangUnit options");

ClangUnit::ClangUnit(int argc, const char **argv)
{
    auto ExpectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, *ClangUnit::option_category);
    if (!ExpectedParser)
    {
        // Fail gracefully for unsupported options.
        llvm::errs() << ExpectedParser.takeError();
        exit(1);
    }
    auto op = &ExpectedParser.get();
    this->source_input_paths = op->getSourcePathList();
}

std::vector<std::string> ClangUnit::get_source_output_paths()
{
    auto result = this->source_input_paths;

    std::ranges::for_each(result, [this](std::string &s)
                          { s = this->to_output_source_path(s); });

    return result;
}

void ClangUnit::open_output_files()
{
    auto source_output_paths = this->get_source_output_paths();
    HandlesOutputFiles::open_output_files(source_output_paths, this->output_files);
}

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

bool ClangUnit::run()
{
    this->open_output_files();
    this->generate_unit_test_file_preludes();

    return true;
}
