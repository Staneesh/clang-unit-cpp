#pragma once

#include <string>
#include <vector>
#include "../FunctionalParameter.hpp"
#include "../ParsedMethod.hpp"
#include "../ParsedFunction.hpp"

std::string arguments_list(const std::vector<FunctionalParameter> &params, std::string type = "");
std::string method_call(const ParsedMethod &parsed_method, std::string type = "");
std::string method_call(const ParsedMethod &parsed_method, const std::vector<std::string> &args, std::string type = "");
std::string function_call(const ParsedFunction &parsed_function, std::string type = "");

// stanisz: Modifying generated test body's result.
std::string end_of_line();
std::string tabbing();
std::string fill_me();
std::string assert_eq(std::string left, std::string right);