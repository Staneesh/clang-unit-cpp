#pragma once

#include "clang/AST/DeclCXX.h"

#include <string>
#include <vector>

#include "FunctionalParameter.hpp"
#include "interfaces/Printable.hpp"

class ParsedFunction : protected virtual Printable
{
public:
private:
    std::string name;
    std::string return_type;
    std::vector<FunctionalParameter> parameters;

public:
    ParsedFunction(const clang::FunctionDecl *raw_function);
    std::string get_name() const;
    std::string get_return_type() const;
    std::vector<FunctionalParameter> get_parameters() const;
    void set_name(const std::string &name);
    void set_name(const std::string &&name);
    void set_return_type(const std::string &return_type);
    void set_return_type(const std::string &&return_type);
    void set_parameters(const std::vector<FunctionalParameter> &parameters);

    void add_parameter(const FunctionalParameter &parameter);

    void print() const override;
};