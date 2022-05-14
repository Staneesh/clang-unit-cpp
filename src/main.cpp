#include "ClangUnit.hpp"
#include "ClangUnitChild.hpp"
#include "ClangUnitCtor.hpp"
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

  // parsed is of type std::vector<ParsedInputSource>
  auto parsed = std::move(parse_opt.value());

  // auto cunit = ClangUnit(parsed);
  // auto tests_for_all_inputs = cunit.generate_tests();

  auto cunit_child = ClangUnitChild(parsed);
  auto tests_produced_by_child = cunit_child.generate_tests();

  auto cunit_ctor = ClangUnitCtor(parsed);
  auto tests_produced_by_ctor = cunit_ctor.generate_tests();

  tests_produced_by_child.insert(tests_produced_by_child.end(),
                                 tests_produced_by_ctor.begin(),
                                 tests_produced_by_ctor.end());

  TestsWriter twriter(tests_produced_by_child);
  twriter.write_all();

  return 0;
}
