#include "ClangUnit.h"
#include <fstream>
#include <filesystem>
#include <algorithm>

std::shared_ptr<llvm::cl::OptionCategory> ClangUnit::option_category = std::make_shared<llvm::cl::OptionCategory>("ClangUnit options");
// std::unique_ptr<clang::tooling::CommonOptionsParser> ClangUnit::options_parser = nullptr; // std::make_shared<clang::tooling::CommonOptionsParser>();

/*
std::optional<clang::tooling::CommonOptionsParser> ClangUnit::get_options_parser(int argc, const char **argv)
{
    auto ExpectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, *ClangUnit::option_category);
    if (!ExpectedParser)
    {
        // Fail gracefully for unsupported options.
        llvm::errs() << ExpectedParser.takeError();
        return {};
    }

    clang::tooling::CommonOptionsParser OptionsParser = std::move(ExpectedParser.get());

    return OptionsParser;
}
*/
std::optional<ClangUnit> ClangUnit::init(int argc, const char **argv)
{
    auto ExpectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, *ClangUnit::option_category);
    if (!ExpectedParser)
    {
        // Fail gracefully for unsupported options.
        llvm::errs() << ExpectedParser.takeError();
        return {};
    }

    return ClangUnit(ExpectedParser.get());
}

ClangUnit::ClangUnit(clang::tooling::CommonOptionsParser &op)
{
    // this->tool = std::make_shared<clang::tooling::ClangTool>(op.getCompilations(),
    //                                                          op.getSourcePathList());
    this->source_input_paths = op.getSourcePathList();
}

std::string ClangUnit::to_output_source_path(std::string &input_source_path)
{
    return std::filesystem::path(input_source_path).replace_filename(std::string("cunit_") + std::filesystem::path(input_source_path).filename().string());
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
    for (std::string &s : this->get_source_output_paths())
    {
        // stanisz: Clear file contents
        auto file = std::make_shared<std::ofstream>();
        file->open(s, std::ofstream::out | std::ofstream::trunc);
        file->close();

        // stanisz: Prepare file for appending
        file->open(s, std::ios::app);
        this->output_files[s] = file;
    }
}

void ClangUnit::write_to_file(std::string &content, std::shared_ptr<std::ofstream> file)
{
    if (file->is_open())
    {
        *file << content;
        file->flush();
        file->close();
    }
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
        std::string result = "#include <gtest/gtest.h> //clang-unit-cpp: Required for running tests\n";
        result += "#include \"" + source_input_path + "\" //clang-unit-cpp: Includes the tested file\n\n";
        this->write_to_file(result, this->output_files[this->to_output_source_path(source_input_path)]);
    }
}

bool ClangUnit::run()
{
    this->open_output_files();
    this->generate_unit_test_file_preludes();

    return true;
}
