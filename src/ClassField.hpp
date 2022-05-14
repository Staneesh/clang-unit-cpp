#pragma once

#include "clang/AST/DeclCXX.h"

#include <string>

class ClassField
{
    std::string declared_name;
    std::string type;
    bool is_private;

public:
    ClassField(const clang::FieldDecl *raw_field);
    std::string get_declared_name() const;
    std::string get_type() const;
    bool get_is_private() const;
};