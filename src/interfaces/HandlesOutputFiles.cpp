#include "HandlesOutputFiles.hpp"
#include <filesystem>

std::string HandlesOutputFiles::to_output_source_path(std::string &input_source_path) const
{
    return std::filesystem::path(input_source_path).replace_filename(std::string("cunit_") + std::filesystem::path(input_source_path).filename().string());
}