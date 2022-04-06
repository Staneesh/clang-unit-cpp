#include "ClangUnitChild.hpp"

std::string ClangUnitChild::get_includes(std::string &source_input_path) const
{
    std::vector<std::string> system = {"gtestlksjdfhslkjdfd/gtest.h"};
    std::vector<std::string> user = {source_input_path};
    return includes_string(system, user);
}
