#include "TestsTemplates.hpp"
#include "SharedGenericTestGen.hpp"

const std::string TestsTemplates::get_template_method_test_case_body(const ParsedMethod &parsed_method,
                                                                     const ParsedClass &parsed_class,
                                                                     std::string type) const
{
    std::string result = "";

    switch (parsed_method.get_kind())
    {
    case ParsedMethod::Kind::Constructor:
        result += tabbing() + "auto instance = " + method_call(parsed_method, type) + end_of_line();
        break;
    case ParsedMethod::Kind::Destructor:
        break;
    case ParsedMethod::Kind::RegularMethod:
        if (parsed_class.get_has_default_constructor())
        {
            llvm::outs() << "TEmplate method seeing default constructor!\n"
                         << parsed_class.get_name() << '\n';
            result += tabbing() + parsed_class.get_name() + " instance; " + end_of_line();
        }
        else
        {
            for (auto &&pm : parsed_class.get_methods())
            {
                if (pm.get_kind() == parsed_method.Kind::Constructor)
                {
                    result += tabbing() + "auto instance = " + method_call(pm, type) + end_of_line();
                    break;
                }
            }
        }

        break;
    }

    type = parsed_class.get_is_templated() ? "" : type;

    if (parsed_method.get_return_type() != "void")
    {
        result += tabbing() + "auto result = " + "instance." + method_call(parsed_method, type) + ";\n";
        result += tabbing() + assert_eq("result", fill_me());
    }
    else
    {
        llvm::outs() << "AM HERE FOR " << parsed_method.get_name() << "\n";
        if (parsed_method.get_kind() == ParsedMethod::Kind::RegularMethod)
        {
            result += tabbing() + "instance." + method_call(parsed_method) + end_of_line();
            result += tabbing() + assert_eq(fill_me(), fill_me());
        }
        else if (parsed_method.get_kind() == ParsedMethod::Kind::Constructor)
        {
            for (auto &&field : parsed_class.get_fields())
                result += tabbing() + assert_eq("instance." + field.get_declared_name(), fill_me());
        }
        else
            result += tabbing() + assert_eq(fill_me(), fill_me());
    }

    return result;
}

const std::string TestsTemplates::get_template_function_test_case_body(const ParsedFunction &parsed_function, std::string type) const
{
    std::string result = "";

    if (parsed_function.get_return_type() != "void")
    {
        result += tabbing() + "auto result = " + function_call(parsed_function, type) + end_of_line();
        result += tabbing() + assert_eq("result", fill_me());
    }
    else
    {
        result += function_call(parsed_function, type) + end_of_line();
        result += tabbing() + assert_eq(fill_me(), fill_me());
    }
    return result;
}

const std::vector<std::string> TestsTemplates::get_fundamental_types() const
{
    return std::vector<std::string>{"int", "float", "double", "unsigned int", "long long", "char", "unsigned char", "short"};
}