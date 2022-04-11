#include "ParsedMethod.hpp"

ParsedMethod::ParsedMethod(const clang::CXXMethodDecl *raw_method)
{
    this->name = raw_method->getNameAsString();
    this->return_type = raw_method->getReturnType().getAsString();
    for (auto &&e : raw_method->parameters())
    {
        this->parameters.push_back(FunctionalParameter(e));
    }
}

std::string ParsedMethod::get_name() const
{
    return this->name;
}
std::string ParsedMethod::get_return_type() const
{
    return this->return_type;
}
std::vector<FunctionalParameter> ParsedMethod::get_parameters() const
{
    return this->parameters;
}

void ParsedMethod::print() const
{
    llvm::outs() << "INFO: Parsed Method: \n";
    llvm::outs() << "\tname: " << this->get_name() << "\n";
    llvm::outs() << "\treturn type as string: " << this->get_return_type() << "\n";
    llvm::outs() << "\tfunctional parameters:\n";
    for (auto &&e : this->get_parameters())
    {
        // llvm::outs() << "\t\ttype as string: " << e.get_type() << "\n";
        llvm ::outs() << "\t\t";
        e.print();
    }
}

void ParsedMethod::set_name(const std::string &name)
{
    this->name = name;
}
void ParsedMethod::set_name(const std::string &&name)
{
    this->name = name;
}
void ParsedMethod::set_return_type(const std::string &return_type)
{
    this->return_type = return_type;
}
void ParsedMethod::set_return_type(const std::string &&return_type)
{
    this->return_type = return_type;
}
void ParsedMethod::set_parameters(const std::vector<FunctionalParameter> &parameters)
{
    this->parameters = parameters;
}

void ParsedMethod::add_parameter(const FunctionalParameter &parameter)
{
    this->parameters.push_back(parameter);
}