#include "HandlesOutputFiles.hpp"
#include <filesystem>

void HandlesOutputFiles::open_output_file(std::string &path_to_open,
                                          std::map<std::string, std::shared_ptr<std::ofstream>> &output_files)
{
    // stanisz: Clear file contents
    auto file = std::make_shared<std::ofstream>();
    file->open(path_to_open, std::ofstream::out | std::ofstream::trunc);
    file->close();

    // stanisz: Prepare file for appending
    file->open(path_to_open, std::ios::app);
    output_files[path_to_open] = file;
}

void HandlesOutputFiles::open_output_files(std::vector<std::string> &paths_to_open,
                                           std::map<std::string, std::shared_ptr<std::ofstream>> &output_files)
{
    // stanisz: Always clear the map before preparing files for writing
    output_files.clear();

    for (std::string &path_to_open : paths_to_open)
    {
        this->open_output_file(path_to_open, output_files);
    }
}

void HandlesOutputFiles::write_to_file(std::string &content, std::shared_ptr<std::ofstream> file)
{
    if (file->is_open())
    {
        *file << content;
        file->flush();
    }
}

std::string HandlesOutputFiles::to_output_source_path(std::string &input_source_path) const
{
    return std::filesystem::path(input_source_path).replace_filename(std::string("cunit_") + std::filesystem::path(input_source_path).filename().string());
}