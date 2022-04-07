#pragma once
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <map>

class HandlesOutputFiles
{
private:
    void open_output_file(std::string &path_to_open,
                          std::map<std::string, std::shared_ptr<std::ofstream>> &output_files);

protected:
    void open_output_files(std::vector<std::string> &paths_to_open,
                           std::map<std::string, std::shared_ptr<std::ofstream>> &output_files);

    void write_to_file(std::string &content, std::shared_ptr<std::ofstream> file);
    // stanisz: Returns a string representing a path to the file containing
    //          generated tests based on the path of the file under testing.
    //          You can specify the exact location of the test files
    //          that will be generated by overriding this funciton which does
    //          the input->output path mapping.
    //          This will be used by the private methods of this interface
    //          as a basis to open and write contents to the test files.
    virtual std::string to_output_source_path(std::string &input_source_path) const;

public:
    virtual ~HandlesOutputFiles() = default;
};