#include "TestsMethods.hpp"
#include "SharedGenericTestGen.hpp"

const std::string TestsMethods::get_method_test_case_name(const ParsedMethod &parsed_method) const
{
    auto n = parsed_method.get_name();
    if (parsed_method.get_is_templated() && parsed_method.get_kind() == ParsedMethod::Kind::Constructor)
        n = n.substr(0, n.find('<'));
    return n + "STUB_TEST";
}

const std::string TestsMethods::get_method_test_case_body(const ParsedMethod &parsed_method,
                                                          const ParsedClass &parsed_class) const
{
    // stanisz: I am not a template method for sure, templates handled elsewhere

    std::string result = "";

    switch (parsed_method.get_kind())
    {
    case ParsedMethod::Kind::Constructor:
        result += tabbing() + "auto instance = " + method_call(parsed_method) + end_of_line();
        break;
    case ParsedMethod::Kind::Destructor:
        break;
    case ParsedMethod::Kind::RegularMethod:
        if (parsed_class.get_has_default_constructor())
        {
            result += tabbing() + parsed_class.get_name() + " instance " + end_of_line();
        }
        else
        {
            for (auto &&pm : parsed_class.get_methods())
            {
                if (pm.get_kind() == parsed_method.Kind::Constructor)
                {
                    result += tabbing() + "auto instance = " + method_call(pm) + end_of_line();
                    break;
                }
            }
        }

        break;
    }

    if (parsed_method.get_return_type() != "void")
    {
        result += tabbing() + parsed_method.get_return_type() + " result = " + "instance." + method_call(parsed_method) + ";\n";
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
            {
                if (field.get_is_private() == false)
                    result += tabbing() + assert_eq("instance." + field.get_declared_name(), fill_me());
                else
                {
                    result += tabbing() + "//" + field.get_declared_name() + end_of_line();
                    result += tabbing() + assert_eq(fill_me(), fill_me());
                }
            }
        }
        else
            result += tabbing() + assert_eq(fill_me(), fill_me());
    }

    return result;
}
