#include "SharedGenericTestGen.hpp"

#include "../RandomValueByType.hpp"

std::string arguments_list(const std::vector<FunctionalParameter> &params)
{
    std::string result = "";

    for (auto &&param : params)
    {
        result += "(" + param.get_type() + ")(" + RandomValueByType::random_value_string(param.get_type()) + "), ";
    }

    result = result.substr(0, result.size() - 2); // stanisz: Skip last comma

    return result;
}

std::string function_call(const ParsedMethod &parsed_method)
{
    std::string result = "";

    result += parsed_method.get_name() + "(" + arguments_list(parsed_method.get_parameters()) + ")";

    return result;
}