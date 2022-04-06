#include <iostream>
#include <fstream>
#include <string>

// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ASTContext.h"

#include "ClangUnit.hpp"
#include "ClangUnitChild.hpp"

using namespace clang::tooling;
using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;

StatementMatcher LoopMatcher =
    forStmt(hasLoopInit(declStmt(
                hasSingleDecl(varDecl(hasInitializer(integerLiteral(equals(0))))
                                  .bind("initVarName")))),
            hasIncrement(unaryOperator(
                hasOperatorName("++"),
                hasUnaryOperand(declRefExpr(
                    to(varDecl(hasType(isInteger())).bind("incVarName")))))),
            hasCondition(binaryOperator(
                hasOperatorName("<"),
                hasLHS(ignoringParenImpCasts(declRefExpr(
                    to(varDecl(hasType(isInteger())).bind("condVarName"))))),
                hasRHS(expr(hasType(isInteger()))))))
        .bind("forLoop");

class LoopPrinter : public MatchFinder::MatchCallback
{
  static bool areSameVariable(const ValueDecl *First, const ValueDecl *Second)
  {
    return First && Second &&
           First->getCanonicalDecl() == Second->getCanonicalDecl();
  }

public:
  void run(const MatchFinder::MatchResult &Result) override
  {
    ASTContext *Context = Result.Context;
    const ForStmt *FS = Result.Nodes.getNodeAs<ForStmt>("forLoop");
    // We do not want to convert header files!
    if (!FS || !Context->getSourceManager().isWrittenInMainFile(FS->getForLoc()))
      return;
    const VarDecl *IncVar = Result.Nodes.getNodeAs<VarDecl>("incVarName");
    const VarDecl *CondVar = Result.Nodes.getNodeAs<VarDecl>("condVarName");
    const VarDecl *InitVar = Result.Nodes.getNodeAs<VarDecl>("initVarName");

    if (!areSameVariable(IncVar, CondVar) || !areSameVariable(IncVar, InitVar))
      return;
    llvm::outs() << "Potential array-based loop discovered.\n";
  }
};

// auto FunctionTemplateMatcher = functionTemplateDecl(isExpansionInMainFile()).bind("functionTemplate");
// auto FunctionTemplateMatcher = functionTemplateDecl(isExpansionInMainFile(), hasDescendant(functionDecl())).bind("functionTemplate");
auto FunctionTemplateMatcher = functionTemplateDecl(isExpansionInMainFile()).bind("functionTemplate");

class FunctionTemplatePrinter : public MatchFinder::MatchCallback
{
public:
  virtual void run(const MatchFinder::MatchResult &Result) override
  {
    if (const FunctionTemplateDecl *FTD = Result.Nodes.getNodeAs<clang::FunctionTemplateDecl>("functionTemplate"))
    {
      llvm::outs() << "FTD name from clang:" << FTD->getNameAsString() << "\n";
    }
  }
};

auto TemplateFunctionMatcher = functionDecl(isExpansionInMainFile(), isTemplateInstantiation()).bind("templateFunction");

class TemplateFunctionPrinter : public MatchFinder::MatchCallback
{
public:
  virtual void run(const MatchFinder::MatchResult &Result) override
  {
    if (const FunctionDecl *TF = Result.Nodes.getNodeAs<clang::FunctionDecl>("templateFunction"))
    {
      llvm::outs() << "TF name from clang:" << TF->getNameAsString() << "\n";
      llvm::outs() << "TF return type from clang:" << TF->getReturnType().getAsString() << "\n";
      llvm::outs() << "TF template specialization arg type from clang:" << TF->getTemplateSpecializationArgs()->get(0).getAsType().getAsString() << "\n";
      for (auto &&p : TF->parameters())
      {
        llvm::outs() << "TF parameter type: " << p->getType().getAsString() << "\n";
      }
    }
  }
};

auto FunctionMatcher = functionDecl(isExpansionInMainFile()).bind("function");

class FunctionPrinter : public MatchFinder::MatchCallback
{
public:
  virtual void run(const MatchFinder::MatchResult &Result) override
  {
    if (const FunctionDecl *F = Result.Nodes.getNodeAs<clang::FunctionDecl>("function"))
    {
      llvm::outs() << "--------------\n";
      llvm::outs() << "F name from clang:" << F->getNameAsString() << "\n";
      llvm::outs() << "F return type from clang:" << F->getReturnType().getAsString() << "\n";
      for (auto &&p : F->parameters())
      {
        llvm::outs() << "F parameter type: " << p->getType().getAsString() << "\n";
      }
      llvm::outs() << "--------------\n";
    }
  }
};

std::string comma_separated_arguments(const CXXMethodDecl *C)
{
  std::string result;
  for (auto &&arg : C->getAsFunction()->parameters())
  {
    result += arg->getType().getAsString() + ", ";
  }

  if (result.size() > 2)
  {
    result = result.substr(0, result.size() - 2);
  }

  return result;
}

namespace random_value_by_type
{
  short random_short()
  {
    return -1;
  }
  int random_int()
  {
    return -10;
  }
  long random_long()
  {
    return -100;
  }
  char random_char()
  {
    return 'a';
  }
  std::string random_string()
  {
    return std::string("test string!");
  }
  bool random_bool()
  {
    return false;
  }
  float random_float()
  {
    return -3.14;
  }
  double random_double()
  {
    return 3.1415;
  }
}

std::string comma_separated_argument_values(const CXXMethodDecl *C)
{
  std::string result;
  for (auto &&arg : C->getAsFunction()->parameters())
  {
    auto arg_type_str = arg->getType().getAsString();
    // stanim: C++ does not allow to switch over strings... wow.
    if (arg_type_str.find("*") != std::string::npos) // am i a pointer?
    {
      result += arg_type_str + ", ";
    }
    else if (arg_type_str.find("unsigned int") != std::string::npos)
    {
      result += std::to_string(std::abs(random_value_by_type::random_int())) + ", ";
    }
    else if (arg_type_str.find("int") != std::string::npos)
    {
      result += std::to_string(random_value_by_type::random_int()) + ", ";
    }
    else if (arg_type_str.find("unsigned long") != std::string::npos)
    {
      result += std::to_string(std::abs(random_value_by_type::random_long())) + ", ";
    }
    else if (arg_type_str.find("long") != std::string::npos)
    {
      result += std::to_string(random_value_by_type::random_long()) + ", ";
    }
    else if (arg_type_str.find("unsigned short") != std::string::npos)
    {
      result += std::to_string(std::abs(random_value_by_type::random_short())) + ", ";
    }
    else if (arg_type_str.find("short") != std::string::npos)
    {
      result += std::to_string(random_value_by_type::random_short()) + ", ";
    }
    else if (arg_type_str.find("char") != std::string::npos)
    {
      result += std::string("\'") + random_value_by_type::random_char() + "\'" + ", ";
    }
    else if (arg_type_str.find("std::string") != std::string::npos)
    {
      result += std::string("std::string(\"") + random_value_by_type::random_string() + "\")" + ", ";
    }
    else if (arg_type_str.find("_Bool") != std::string::npos)
    {
      result += std::to_string(random_value_by_type::random_bool()) + ", ";
    }
    else if (arg_type_str.find("float") != std::string::npos)
    {
      result += std::to_string(random_value_by_type::random_float()) + ", ";
    }
    else if (arg_type_str.find("double") != std::string::npos)
    {
      result += std::to_string(random_value_by_type::random_double()) + ", ";
    }
    else // stanim: Not supported, have a stub here:
    {
      result += arg_type_str + ", ";
    }
  }

  if (result.size() > 2)
  {
    result = result.substr(0, result.size() - 2);
  }
  return result;
}

std::string raw_method_call(const CXXMethodDecl *C)
{
  std::string result = C->getNameAsString() + "(" + comma_separated_argument_values(C) + ")";
  return result;
}

std::string method_call(const std::string &object_name, const CXXMethodDecl *C)
{
  std::string result = object_name + "." + raw_method_call(C);
  return result;
}

std::string method_unit_test_stub_body(const CXXMethodDecl *C)
{
  std::string result;

  llvm::outs() << "SEEING: " << C->getNameAsString() << " - " << C->getParent()->getNameAsString() << "\n";

  if (C->getNameAsString().compare(C->getParent()->getNameAsString()) == 0)
  {
    // I am a constructor
    result = "\t" + C->getQualifiedNameAsString() + " object" + raw_method_call(C) + ";\n\t/* Fill Me! */\n";
    for (auto &&decl : C->decls())
    {

      llvm::outs() << "DUMPING CTOR DECL:\n";
      decl->dump();
      llvm::outs() << "Finished DUMPING CTOR DECL:\n";
      llvm::outs() << "FTYPE: " << decl->getFunctionType() << "\n";
    }
  }
  else if (C->getNameAsString().compare("~" + C->getParent()->getNameAsString()) == 0)
  {
    // I am a destructor
  }
  else if (C->getReturnType().getAsString().compare("void") != 0)
  {
    result = "\t" + C->getParent()->getQualifiedNameAsString() + " object;\n\tEXPECT_EQ(object." + raw_method_call(C) + ", /* Fill Me! */);\n";
  }
  else
  {
    result = "\t" + C->getParent()->getQualifiedNameAsString() + " object;\n\tobject." + raw_method_call(C) + ";\n\t/* Fill Me! */\n";
  }
  return result;
}

std::string method_unit_test_stub(const CXXMethodDecl *C)
{
  std::string body = method_unit_test_stub_body(C);
  if (body.empty())
    return "";
  std::string result = "TEST(AutogeneratedStubSuite, " + C->getNameAsString() + "TestStub) {\n" + body + "}\n\n";
  return result;
}

auto MethodMatcher = cxxMethodDecl(isExpansionInMainFile(), isUserProvided()).bind("method");

std::string unit_test_file_prelude(const char tested_file_relative_path[])
{
  std::string result = "#include <gtest/gtest.h> //clang-unit-cpp: Required for running tests\n";
  result += "#include \"" + std::string(tested_file_relative_path) + "\" //clang-unit-cpp: Includes the tested file\n";
  return result;
}

class MethodPrinter : public MatchFinder::MatchCallback
{
public:
  virtual void run(const MatchFinder::MatchResult &Result) override
  {
    if (const CXXMethodDecl *C = Result.Nodes.getNodeAs<clang::CXXMethodDecl>("method"))
    {
      llvm::outs() << "--------------\n";
      llvm::outs() << "F name from clang:" << C->getNameAsString() << "\n";
      llvm::outs() << "F return type from clang:" << C->getReturnType().getAsString() << "\n";
      for (auto &&p : C->parameters())
      {
        llvm::outs() << "C parameter type: " << p->getType().getAsString() << "\n";
      }
      llvm::outs() << "PARENT: " << C->getParent()->getQualifiedNameAsString() << "\n";
      llvm::outs() << "IS PRIVATE ???\n";
      llvm::outs() << "--------------\n";

      if (C->isModulePrivate() == false) // cannot test private functions, unless friends?
      {
        std::ofstream test_file("test/automatically_generated.cpp", std::ios::app);
        if (test_file.is_open())
        {
          // Outputs to example.txt through a_file
          test_file << method_unit_test_stub(C);

          test_file.flush();
          // Close the file stream explicitly
          test_file.close();
        }
      }
    }
  }
};

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...\n");

int addsome(int v)
{
  return v + 15;
}

int main(int argc, const char **argv)
{
  ClangUnitChild cunitc(argc, argv);
  bool cunitc_run_result = cunitc.run();

  if (!cunitc_run_result)
  {
    llvm::errs() << "Failure in ClangUnit.run()!\n";
    return 1;
  }

  ClangUnit cunit(argc, argv);
  bool cunit_run_result = cunit.run();

  if (!cunit_run_result)
  {
    llvm::errs() << "Failure in ClangUnit.run()!\n";
    return 1;
  }

  return 0;

  /*
  auto ExpectedParser = CommonOptionsParser::create(argc, argv, MyToolCategory);
  if (!ExpectedParser)
  {
    // Fail gracefully for unsupported options.
    llvm::errs() << ExpectedParser.takeError();
    return 1;
  }
  CommonOptionsParser &OptionsParser = ExpectedParser.get();
  */

  std::ofstream test_file("test/automatically_generated.cpp", std::ios::app);
  if (test_file.is_open())
  {
    test_file << unit_test_file_prelude("test.cpp") << "\n";
    test_file.flush();
    test_file.close();
  }

  /*
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());
  */

  MatchFinder Finder;
  /*
  LoopPrinter Printer;
  Finder.addMatcher(LoopMatcher, &Printer);
  FunctionTemplatePrinter FunctionTemplatePrinter;
  Finder.addMatcher(FunctionTemplateMatcher, &FunctionTemplatePrinter);
  TemplateFunctionPrinter TemplateFunctionPrinter;
  Finder.addMatcher(TemplateFunctionMatcher, &TemplateFunctionPrinter);
  FunctionPrinter FunctionPrinter;
  Finder.addMatcher(FunctionMatcher, &FunctionPrinter);
  */
  MethodPrinter MethodPrinter;
  Finder.addMatcher(MethodMatcher, &MethodPrinter);

  // return Tool.run(newFrontendActionFactory(&Finder).get());
}