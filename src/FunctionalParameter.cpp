#include "FunctionalParameter.hpp"

FunctionalParameter::FunctionalParameter(clang::ParmVarDecl *const &param_var_decl)
    : type(param_var_decl->getType().getAsString())
{
}

FunctionalParameter::FunctionalParameter(const std::string &type)
    : type(type)
{
}
FunctionalParameter::FunctionalParameter(const std::string &&type)
    : type(type)
{
}

std::string FunctionalParameter::get_type() const
{
    return this->type;
}

void FunctionalParameter::print() const
{
    llvm::outs() << "Functional Parameter type: " << this->get_type() << "\n";
}