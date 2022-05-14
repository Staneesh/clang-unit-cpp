#pragma once

#include "clang/AST/DeclCXX.h"

#include <string>
#include <vector>

#include "ClassField.hpp"

class ParsedClass
{
public:
private:
    std::string name;
    std::vector<ClassField> fields;

public:
    ParsedClass() = default;
    ParsedClass(const clang::CXXRecordDecl *raw_class);
    std::string get_name() const;
    std::vector<ClassField> get_fields() const;
};