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
  for (auto &&t : tests_for_all_inputs)
  {
    t.print();
  }

  TestsWriter twriter(tests_for_all_inputs);
  twriter.write_all();

  return 0;
}