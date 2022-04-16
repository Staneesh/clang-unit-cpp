#include "TestsWriter.hpp"

TestsWriter::TestsWriter(const std::vector<TestCasesForParsedInput> &many_groups_of_test_cases)
    : many_groups_of_test_cases(many_groups_of_test_cases)
{
}

void TestsWriter::write_all() const
{
    std::map<std::string, std::vector<TestCase>> test_cases_per_file;
    std::map<std::string, std::string> out_path_to_in_path;

    for (auto &&tcases : this->many_groups_of_test_cases)
    {
        auto input_path = tcases.get_input_path();
        auto output_path = this->to_output_source_path(input_path);
        std::vector<TestCase> &test_cases_for_this_output = test_cases_per_file[output_path];
        test_cases_for_this_output.insert(test_cases_for_this_output.end(),
                                          tcases.get_test_cases().begin(),
                                          tcases.get_test_cases().end());

        out_path_to_in_path[output_path] = input_path;
    }

    for (auto &&per_file : test_cases_per_file)
    {
        // stanisz: Remove current contents
        auto file = std::ofstream(per_file.first, std::ofstream::out | std::ofstream::trunc);
        file.close();

        // stanisz: Prepare file for appending
        file = std::ofstream(per_file.first, std::ios::app);
        if (file.is_open())
        {
            // stanisz: Includes first
            file << get_includes(out_path_to_in_path[per_file.first]);

            // stanisz: Then test cases
            for (auto &&t : per_file.second)
            {
                file << t.to_string();
                file.flush();
            }
        }
        file.close();
    }
}