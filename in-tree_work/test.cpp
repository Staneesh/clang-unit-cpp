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

int main()
{
    std::cout << foo(5) << std::endl;
    for (int i = 0; i < 5; i++)
    {
        std::cout << i << std::endl;
    }
    return 0;
}