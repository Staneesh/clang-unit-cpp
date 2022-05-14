#include "ClassField.hpp"
#include <iostream>

ClassField::ClassField(const clang::FieldDecl *raw_field)
{
    this->declared_name = raw_field->getNameAsString();
    this->type = raw_field->getType().getAsString();
    if (this->type == "_Bool")
    {
        this->type = "bool";
    }
    this->is_private = raw_field->getAccess() != clang::AS_public;
}

std::string ClassField::get_declared_name() const
{
    return this->declared_name;
}
std::string ClassField::get_type() const
{
    return this->type;
}

bool ClassField::get_is_private() const
{
    return this->is_private;
}