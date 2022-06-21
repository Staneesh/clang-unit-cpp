#pragma once

#include "clang/AST/DeclCXX.h"

#include <string>
#include <vector>

#include "ClassField.hpp"
#include "ParsedMethod.hpp"

class ParsedClass
{
public:
private:
    std::string name;
    std::vector<ClassField> fields;
    std::vector<ParsedMethod> methods;

    bool has_default_constructor;
    bool is_templated;

public:
    ParsedClass() = default;
    ParsedClass(const clang::CXXRecordDecl *raw_class);
    std::string get_name() const;
    std::vector<ClassField> get_fields() const;
    std::vector<ParsedMethod> get_methods() const;
    bool get_has_default_constructor() const;
    bool get_is_templated() const;

    void add_method(const ParsedMethod &PM);
};