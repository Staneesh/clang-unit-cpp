#include "ClangUnit.hpp"
#include "ClangUnitChild.hpp"
#include "InputParser.hpp"
#include "TestsWriter.hpp"

int main(int argc, const char **argv)
{
  auto parse_opt = ClangUnitParser::parse(argc, argv);
  if (parse_opt.has_value() == false)
  {
    llvm::errs() << "ERROR: ClangUnit::parse() failed! Exiting...\n";
    exit(1);
  }
  auto parsed = std::move(parse_opt.value());

  auto cunit = ClangUnit(parsed);
  auto tests_for_all_inputs = cunit.generate_tests();

  auto cunit_child = ClangUnitChild(parsed);
  auto tests_produced_by_child = cunit_child.generate_tests();

  tests_for_all_inputs.insert(tests_for_all_inputs.end(), tests_produced_by_child.begin(), tests_produced_by_child.end());

  TestsWriter twriter(tests_for_all_inputs);
  twriter.write_all();

  return 0;
}