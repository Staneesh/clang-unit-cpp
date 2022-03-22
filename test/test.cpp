#include <iostream>
#include <vector>

namespace Outer
{
    ////////////////////////////////////////////////////////////////////////////
    //                                 LineReader                             //
    ////////////////////////////////////////////////////////////////////////////

    namespace Inner
    {
        struct NiceStruct
        {
            std::string member1;

            NiceStruct()
            {
                member1 = std::string("Hello!");
            }
            NiceStruct(std::string &pass)
            {
                member1 = pass;
            }
            ~NiceStruct()
            {
                std::cout << "Dying!" << std::endl;
            }

            unsigned get_length()
            {
                return member1.length();
            }
        };
    }
}

struct StandaloneStruct
{
    void method(int a, long long b, long c, short d, unsigned e, float f, double g, float i, bool h) {}
    Outer::Inner::NiceStruct return_struct(Outer::Inner::NiceStruct &pass)
    {
        return pass;
    }
};