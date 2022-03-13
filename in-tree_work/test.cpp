#include <iostream>

class A
{
public:
    int member;
    A()
    {
        member = 0;
    }
    A(int m)
    {
        member = m;
    }

    int member_sq()
    {
        for (int i = 0; i < 10; ++i)
        {
            continue;
        }
        return member * member;
    }
};

int foo(int n)
{
    int res = 0;

    for (int i = 0; i < n; ++i)
    {
        auto object = A(i);
        res += object.member_sq();
    }
    return res;
}

template <typename T>
T two_times(T x)
{
    return x + x;
}

auto two_times2(auto x)
{
    return x + x;
}

int foo(int a, int b)
{
    return a + b;
}

int main()
{
    std::cout << foo(5) << std::endl;
    for (int i = 0; i < 5; i++)
    {
        std::cout << i << std::endl;
    }

    std::cout << two_times(4.3) << " " << two_times(3) << std::endl;
    std::cout << two_times2(4.3) << " " << two_times2(3) << std::endl;
    return 0;
}