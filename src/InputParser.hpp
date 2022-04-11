#pragma once

#include "clang/AST/DeclCXX.h"

#include <vector>
#include <filesystem>
#include <optional>
#include <string>

#include "ParsedMethod.hpp"
#include "interfaces/Printable.hpp"

class ParsedInputSource : protected Printable
{
private:
    std::string path; // stanisz: This is an absolute path.
    std::vector<ParsedMethod> methods;

public:
    ParsedInputSource(const std::string path, std::vector<ParsedMethod> &methods)
        : path(path), methods(methods){};

    std::string get_path() const;
    std::vector<ParsedMethod> get_methods() const;
    void print() const override;
};

namespace ClangUnitParser
{
    std::optional<std::vector<ParsedInputSource>> parse(int argc, const char **argv);
}
