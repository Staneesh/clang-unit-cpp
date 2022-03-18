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
    void method() {}
    Outer::Inner::NiceStruct return_struct(int i, int j, Outer::Inner::NiceStruct &pass)
    {
        std::cout << i << " " << j << std::endl;
        return pass;
    }
};