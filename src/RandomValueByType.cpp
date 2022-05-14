#include "RandomValueByType.hpp"

int RandomValueByType::random_int()
{
    return -(rand() % 100000);
}

long RandomValueByType::random_long()
{
    return -(rand() % 10000000);
}

short RandomValueByType::random_short()
{
    return -(rand() % 1000);
}

char RandomValueByType::random_char()
{
    return char(32 + rand() % 94);
}

std::string RandomValueByType::random_string()
{
    std::string result = "";
    unsigned len = rand() % 15;
    for (unsigned i = 0; i < len; ++i)
    {
        result += random_char();
    }
    return result;
}

bool RandomValueByType::random_bool()
{
    return bool(rand() % 2);
}

float RandomValueByType::random_float()
{
    return float((float)rand() / (float)RAND_MAX) * (-3);
}

double RandomValueByType::random_double()
{
    return double((double)rand() / (double)RAND_MAX) * (-3);
}

std::string RandomValueByType::random_value_string(const std::string &type)
{
    std::string result = "";

    if (type.find("*") != std::string::npos) // am i a pointer?
    {
        result += type;
    }
    else if (type.find("unsigned int") != std::string::npos)
    {
        result += std::to_string(std::abs(RandomValueByType::random_int()));
    }
    else if (type.find("int") != std::string::npos)
    {
        result += std::to_string(RandomValueByType::random_int());
    }
    else if (type.find("unsigned long") != std::string::npos)
    {
        result += std::to_string(std::abs(RandomValueByType::random_long()));
    }
    else if (type.find("long") != std::string::npos)
    {
        result += std::to_string(RandomValueByType::random_long());
    }
    else if (type.find("unsigned short") != std::string::npos)
    {
        result += std::to_string(std::abs(RandomValueByType::random_short()));
    }
    else if (type.find("short") != std::string::npos)
    {
        result += std::to_string(RandomValueByType::random_short());
    }
    else if (type.find("char") != std::string::npos)
    {
        result += std::string("\'") + RandomValueByType::random_char() + "\'";
    }
    else if (type.find("std::string") != std::string::npos)
    {
        result += std::string("std::string(\"") + RandomValueByType::random_string() + "\")";
    }
    else if (type.find("bool") != std::string::npos)
    {
        result += std::to_string(RandomValueByType::random_bool());
    }
    else if (type.find("float") != std::string::npos)
    {
        result += std::to_string(RandomValueByType::random_float());
    }
    else if (type.find("double") != std::string::npos)
    {
        result += std::to_string(RandomValueByType::random_double());
    }
    else // stanim: Not supported, have a stub here:
    {
        result += type;
    }

    return result;
}