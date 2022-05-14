#pragma once

#include "clang/AST/DeclCXX.h"

#include <string>
#include <vector>

#include "FunctionalParameter.hpp"
#include "interfaces/Printable.hpp"

class ParsedMethod : protected Printable
{
public:
    enum Kind
    {
        Constructor,
        Destructor,
        RegularMethod,
    };

private:
    std::string name;
    std::string return_type;
    std::vector<FunctionalParameter> parameters;
    Kind kind;
    std::string class_name;
    bool is_default;

public:
    ParsedMethod(const clang::CXXMethodDecl *raw_method, bool is_constructor, bool is_destructor);
    std::string get_name() const;
    std::string get_return_type() const;
    std::vector<FunctionalParameter> get_parameters() const;
    Kind get_kind() const;
    std::string get_class_name() const;
    bool get_is_default() const;
    void set_name(const std::string &name);
    void set_name(const std::string &&name);
    void set_return_type(const std::string &return_type);
    void set_return_type(const std::string &&return_type);
    void set_parameters(const std::vector<FunctionalParameter> &parameters);

    void add_parameter(const FunctionalParameter &parameter);

    void print() const override;
};