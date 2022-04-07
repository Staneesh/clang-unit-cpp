#pragma once
#include <string>
#include <vector>

class GeneratesIncludes
{
private:
    // stanisz: Returns a string representing include directives
    //          based on system and user libraries.
    std::string includes_string(std::vector<std::string> &system_libraries,
                                std::vector<std::string> &user_libraries) const;

protected:
    // stanisz: Constructs a string representing an include directive
    //          for a given system_library (for example 'iostream')
    virtual std::string system_include(std::string &system_library) const;
    // stanisz: Constructs a string representing an include directive
    //          for a given user_library (for example 'code/class.h')
    virtual std::string user_include(std::string &user_library) const;
    // stanisz: Returns an includes string for a given source_input_path. Calls
    //          'includes_string' to determine how to construct a string
    virtual std::string get_includes(std::string &source_input_path) const;

public:
    virtual ~GeneratesIncludes() = default;
};

