#pragma once

#include "clang/AST/DeclCXX.h"

#include <vector>
#include <filesystem>
#include <optional>
#include <string>
#include <map>

#include "ParsedMethod.hpp"
#include "ParsedFunction.hpp"
#include "ParsedClass.hpp"
#include "interfaces/Printable.hpp"

class ParsedInputSource : protected virtual Printable
{
private:
    std::string path; // stanisz: This is an absolute path.
    std::vector<ParsedMethod> methods;
    std::vector<ParsedFunction> functions;
    std::map<std::string, ParsedClass> classes; // stanisz: Qualified class name -> ParsedClass

public:
    ParsedInputSource(const std::string path, std::vector<ParsedMethod> &methods,
                      std::vector<ParsedFunction> &functions,
                      std::map<std::string, ParsedClass> &classes);

    std::string get_path() const;
    std::vector<ParsedMethod> get_methods() const;
    std::vector<ParsedFunction> get_functions() const;
    std::map<std::string, ParsedClass> get_classes() const;
    void print() const override;
};

namespace ClangUnitParser
{
    std::optional<std::vector<ParsedInputSource>> parse(int argc, const char **argv);
}
