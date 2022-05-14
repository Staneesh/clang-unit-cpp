#include "ParsedClass.hpp"

ParsedClass::ParsedClass(const clang::CXXRecordDecl *raw_class)
{
    this->name = raw_class->getNameAsString();

    for (auto &&e : raw_class->fields())
    {
        this->fields.push_back(ClassField(e));
    }
}

std::string ParsedClass::get_name() const
{
    return this->name;
}

std::vector<ClassField> ParsedClass::get_fields() const
{
    return this->fields;
}