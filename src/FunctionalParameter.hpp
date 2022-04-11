#pragma once

#include "clang/AST/DeclCXX.h"
#include "interfaces/Printable.hpp"

class FunctionalParameter : protected Printable
{
private:
    std::string type;

public:
    FunctionalParameter(clang::ParmVarDecl *const &param_var_decl);
    FunctionalParameter(const std::string &type);
    FunctionalParameter(const std::string &&type);
    std::string get_type() const;

    void print() const override;
};