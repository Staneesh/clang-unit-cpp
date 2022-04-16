#include "TestCasesForParsedInput.hpp"

TestCasesForParsedInput::TestCasesForParsedInput(const std::string &isp, const std::vector<TestCase> &tcases)
    : input_source_path(isp), test_cases(tcases)
{
}

void TestCasesForParsedInput::print() const
{
    llvm::outs() << "INFO: Printing TestCasesForParsedInput:\n";
    llvm::outs() << "\tinput_source_path: " << this->input_source_path << "\n";
    llvm::outs() << "test cases:\n";
    for (auto &&tc : this->test_cases)
    {
        tc.print();
    }
    llvm::outs() << "INFO: TestCasesForParsedInput printed!\n";
}

const std::string &TestCasesForParsedInput::get_input_path() const
{
    return this->input_source_path;
}

const std::vector<TestCase> &TestCasesForParsedInput::get_test_cases() const
{
    return this->test_cases;
}