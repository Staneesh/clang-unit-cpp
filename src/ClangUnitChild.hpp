#pragma once
#include "ClangUnit.hpp"

class ClangUnitChild : public ClangUnit
{
public:
    ClangUnitChild(int argc, const char **argv) : ClangUnit(argc, argv){};
    std::string get_includes(std::string &source_input_path) const override;
    // bool run() override;
};