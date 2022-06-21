#include "ParsedMethod.hpp"
#include <iostream>

ParsedMethod::ParsedMethod(const clang::CXXMethodDecl *raw_method,
                           bool is_constructor, bool is_destructor)
{
    this->name = raw_method->getNameAsString();
    this->return_type = raw_method->getReturnType().getAsString();
    for (auto &&e : raw_method->parameters())
    {
        this->parameters.push_back(FunctionalParameter(e));
    }

    if (is_constructor)
    {
        this->kind = Kind::Constructor;
    }
    else if (is_destructor)
    {
        this->kind = Kind::Destructor;
    }
    else
    {
        this->kind = Kind::RegularMethod;
    }

    this->class_name = raw_method->getParent()->getQualifiedNameAsString();
    this->is_default = raw_method->isDefaulted();
    this->is_templated = raw_method->isTemplated();
}

std::string ParsedMethod::get_class_name() const
{
    return this->class_name;
}

ParsedMethod::Kind ParsedMethod::get_kind() const
{
    return this->kind;
}

std::string ParsedMethod::get_name(std::string type) const
{
    auto newname = this->name;
    if (type.length() && get_is_templated())
    {
        if (newname.find('<') != std::string::npos)
        {
            newname = newname.substr(0, newname.find('<') + 1) + type + newname.substr(newname.find('>'), newname.length());
        }
        else
        {
            newname = newname + "<" + type + ">";
        }
    }
    return newname;
}
std::string ParsedMethod::get_return_type() const
{
    return this->return_type;
}
std::vector<FunctionalParameter> ParsedMethod::get_parameters() const
{
    return this->parameters;
}

bool ParsedMethod::get_is_default() const
{
    return this->is_default;
}

bool ParsedMethod::get_is_templated() const
{
    return this->is_templated;
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