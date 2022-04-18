#pragma once

#include <string>
#include "../FunctionalParameter.hpp"
#include "../ParsedMethod.hpp"
#include "../ParsedFunction.hpp"

std::string arguments_list(const std::vector<FunctionalParameter> &params);
std::string method_call(const ParsedMethod &parsed_method);
std::string function_call(const ParsedFunction &parsed_function);