#include "SharedGenericTestGen.hpp"

#include "../RandomValueByType.hpp"

std::string arguments_list(const std::vector<FunctionalParameter> &params, std::string type)
{
    std::string result = "";

    for (auto &&param : params)
    {
        auto t = param.get_type();
        if (type.length())
        {
            t = type;
        }
        result += "(" + t + ")(" + RandomValueByType::random_value_string(t) + "), ";
    }

    result = result.substr(0, result.size() - 2); // stanisz: Skip last comma

    return result;
}

std::string method_call(const ParsedMethod &parsed_method, std::string type)
{
    std::string result = "";
    std::string name = parsed_method.get_name(type);

    result += name + "(" + arguments_list(parsed_method.get_parameters(), type) + ")";

    return result;
}

std::string method_call(const ParsedMethod &parsed_method,
                        const std::vector<std::string> &args,
                        std::string type)
{
    std::string result = "";

    result += parsed_method.get_name(type) + "(";
    for (auto &&a : args)
    {
        result += a + ", ";
    }
    result = result.substr(0, result.size() - 2); // stanisz: Skip last comma

    result += ")";

    return result;
}

std::string function_call(const ParsedFunction &parsed_function, std::string type)
{
    std::string result = "";

    result += parsed_function.get_name(type) + "(" + arguments_list(parsed_function.get_parameters(), type) + ")";

    return result;
}

std::string end_of_line()
{
    return std::string(";\n");
}

std::string tabbing()
{
    return std::string("\t");
}

std::string fill_me()
{
    return std::string("/*Fill me!*/");
}

std::string assert_eq(std::string left, std::string right)
{
    return std::string("ASSERT_EQ(" + left + ", " + right + ")" + end_of_line());
}