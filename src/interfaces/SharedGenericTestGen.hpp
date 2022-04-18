#pragma once

#include <string>
#include "../FunctionalParameter.hpp"
#include "../ParsedMethod.hpp"

std::string arguments_list(const std::vector<FunctionalParameter> &params);
std::string function_call(const ParsedMethod &parsed_method);