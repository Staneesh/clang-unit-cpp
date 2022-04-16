#pragma once

#include <string>

namespace RandomValueByType
{
    int random_int();
    long random_long();
    short random_short();

    char random_char();
    std::string random_string();

    bool random_bool();

    float random_float();
    double random_double();
}