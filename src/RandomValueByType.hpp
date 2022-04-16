#pragma once

#include <string>

class RandomValueByType
{
private:
    static int random_int();
    static long random_long();
    static short random_short();

    static char random_char();
    static std::string random_string();

    static bool random_bool();

    static float random_float();
    static double random_double();

public:
    static std::string random_value_string(const std::string &type);
};