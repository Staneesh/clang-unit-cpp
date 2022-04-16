#include "GeneratesIncludes.hpp"

std::string GeneratesIncludes::system_include(std::string system_library) const
{
    return std::string("#include <") + system_library + "> //clang-unit: System library\n";
}

std::string GeneratesIncludes::user_include(std::string user_library) const
{
    return std::string("#include \"") + user_library + "\" //clang-unit: User library\n";
}

std::string GeneratesIncludes::includes_string(std::vector<std::string> system_libraries,
                                               std::vector<std::string> user_libraries) const
{
    std::string result = "";

    for (std::string &sl : system_libraries)
    {
        result += this->system_include(sl);
    }

    for (std::string &ul : user_libraries)
    {
        result += this->user_include(ul);
    }

    return result;
}

std::string GeneratesIncludes::get_includes(std::string source_input_path) const
{
    std::vector<std::string> system = {"gtest/gtest.h"};
    std::vector<std::string> user = {source_input_path};
    return includes_string(system, user);
}