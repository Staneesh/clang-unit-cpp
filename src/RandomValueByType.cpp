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
    return char(rand() % 255);
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
