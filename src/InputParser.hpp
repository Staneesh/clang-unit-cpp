#pragma once

#include "clang/AST/DeclCXX.h"

#include <vector>
#include <filesystem>
#include <optional>
#include <string>

#include "ParsedMethod.hpp"
#include "ParsedFunction.hpp"
#include "interfaces/Printable.hpp"

class ParsedInputSource : protected virtual Printable
{
private:
    std::string path; // stanisz: This is an absolute path.
    std::vector<ParsedMethod> methods;
    std::vector<ParsedFunction> functions;

public:
    ParsedInputSource(const std::string path, std::vector<ParsedMethod> &methods, std::vector<ParsedFunction> &functions);

    std::string get_path() const;
    std::vector<ParsedMethod> get_methods() const;
    std::vector<ParsedFunction> get_functions() const;
    void print() const override;
};

namespace ClangUnitParser
{
    std::optional<std::vector<ParsedInputSource>> parse(int argc, const char **argv);
}
