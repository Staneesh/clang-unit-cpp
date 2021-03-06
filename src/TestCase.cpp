#include "TestCase.hpp"

void TestCase::print() const
{
    llvm::outs() << "TestCase:\n";
    llvm::outs() << "\tname: " << this->name << "\n";
    llvm::outs() << "\ttest_suite_name: " << this->test_suite_name << "\n";
    llvm::outs() << "\tbody: " << this->body << "\n";
}

TestCase::TestCase(const std::string &test_suite_name, const std::string &test_case_name, const std::string &test_case_body)
    : test_suite_name(test_suite_name), name(test_case_name), body(test_case_body)
{
}

std::string TestCase::to_string() const
{
    std::string result;
    result += "TEST(" + this->test_suite_name + ", " + this->name + ")\n";
    result += "{\n";
    result += this->body + "\n";
    result += "}\n";
    return result;
}

std::string TestCase::get_test_suite_name() const
{
    return this->test_suite_name;
}
std::string TestCase::get_test_case_name() const
{
    return this->name;
}
std::string TestCase::get_test_case_body() const
{
    return this->body;
}
void TestCase::set_test_suite_name(const std::string &o)
{
    this->test_suite_name = o;
}
void TestCase::set_test_case_name(const std::string &o)
{
    this->name = o;
}
void TestCase::set_test_case_body(const std::string &o)
{
    this->body = o;
}