namespace NA
{
    ////////////////////////////////////////////////////////////////////////////
    //                                 LineReader                             //
    ////////////////////////////////////////////////////////////////////////////

    namespace NB
    {
        struct StructName
        {
            virtual void format_error_message() const = 0;

            const char *what() const noexcept
            {
                format_error_message();
                return error_message_buffer;
            }

            mutable char error_message_buffer[512];
        };
    }
}

struct StandaloneStruct
{
    void method() {}
};