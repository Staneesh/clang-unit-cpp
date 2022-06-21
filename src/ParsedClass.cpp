#include "ParsedClass.hpp"

ParsedClass::ParsedClass(const clang::CXXRecordDecl *raw_class)
{
    this->name = raw_class->getNameAsString();

    for (auto &&e : raw_class->fields())
    {
        this->fields.push_back(ClassField(e));
    }

    this->has_default_constructor = raw_class->hasDefaultConstructor();
    this->is_templated = raw_class->isTemplated();
}

std::string ParsedClass::get_name() const
{
    return this->name;
}

std::vector<ClassField> ParsedClass::get_fields() const
{
    return this->fields;
}

std::vector<ParsedMethod> ParsedClass::get_methods() const
{
    return this->methods;
}

void ParsedClass::add_method(const ParsedMethod &PM)
{
    this->methods.push_back(PM);
}

bool ParsedClass::get_has_default_constructor() const
{
    return this->has_default_constructor;
}

bool ParsedClass::get_is_templated() const
{
    return this->is_templated;
}