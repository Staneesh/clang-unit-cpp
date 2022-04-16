#pragma once

#include "interfaces/GeneratesIncludes.hpp"
#include "interfaces/HandlesOutputFiles.hpp"

#include <vector>
#include "TestCasesForParsedInput.hpp"

class TestsWriter : protected HandlesOutputFiles, protected GeneratesIncludes
{
private:
    std::vector<TestCasesForParsedInput> many_groups_of_test_cases;

public:
    TestsWriter(const std::vector<TestCasesForParsedInput> &many_groups_of_test_cases);
    void write_all() const;
};