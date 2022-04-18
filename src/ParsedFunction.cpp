#include "ParsedFunction.hpp"

ParsedFunction::ParsedFunction(const clang::FunctionDecl *raw_function)
{
    this->name = raw_function->getNameAsString();
    this->return_type = raw_function->getReturnType().getAsString();
    for (auto &&e : raw_function->parameters())
    {
        this->parameters.push_back(FunctionalParameter(e));
    }
}

std::string ParsedFunction::get_name() const
{
    return this->name;
}
std::string ParsedFunction::get_return_type() const
{
    return this->return_type;
}
std::vector<FunctionalParameter> ParsedFunction::get_parameters() const
{
    return this->parameters;
}

void ParsedFunction::print() const
{
    llvm::outs() << "INFO: Parsed Function: \n";
    llvm::outs() << "\tname: " << this->get_name() << "\n";
    llvm::outs() << "\treturn type as string: " << this->get_return_type() << "\n";
    llvm::outs() << "\tfunctional parameters:\n";
    for (auto &&e : this->get_parameters())
    {
        llvm ::outs() << "\t\t";
        e.print();
    }
}

void ParsedFunction::set_name(const std::string &name)
{
    this->name = name;
}
void ParsedFunction::set_name(const std::string &&name)
{
    this->name = name;
}
void ParsedFunction::set_return_type(const std::string &return_type)
{
    this->return_type = return_type;
}
void ParsedFunction::set_return_type(const std::string &&return_type)
{
    this->return_type = return_type;
}
void ParsedFunction::set_parameters(const std::vector<FunctionalParameter> &parameters)
{
    this->parameters = parameters;
}

void ParsedFunction::add_parameter(const FunctionalParameter &parameter)
{
    this->parameters.push_back(parameter);
}