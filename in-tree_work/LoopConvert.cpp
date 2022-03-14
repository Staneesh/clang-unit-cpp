#include <iostream>
#include <fstream>

// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ASTContext.h"

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

std::string raw_method_call(const CXXMethodDecl *C)
{
  std::string result = C->getNameAsString() + "(" + comma_separated_arguments(C) + ")";
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

  llvm::outs() << C->getNameAsString() << " - " << C->getParent()->getNameAsString() << "\n";
  if (C->getNameAsString().compare(C->getParent()->getNameAsString()) == 0)
  {
    // I am a constructor
    result = "\t" + C->getNameAsString() + " object = " + raw_method_call(C) + ";\n\t/* Fill Me! */\n";
  }
  else if (C->getNameAsString().compare("~" + C->getParent()->getNameAsString()) == 0)
  {
    // I am a destructor
  }
  else if (C->getReturnType().getAsString().compare("void") != 0)
  {
    result = "\t" + C->getParent()->getNameAsString() + " object;\n\tEXPECT_EQ(object." + raw_method_call(C) + ", /* Fill Me! */);\n";
  }
  else
  {
    result = "\t" + C->getParent()->getNameAsString() + " object;\n\tobject." + raw_method_call(C) + "\n\t/* Fill Me! */\n";
  }
  return result;
}

std::string method_unit_test_stub(const CXXMethodDecl *C)
{
  std::string result = "TEST(AutogeneratedStubSuite, " + C->getNameAsString() + "TestStub) {\n" + method_unit_test_stub_body(C) + "}\n\n";
  return result;
}

auto MethodMatcher = cxxMethodDecl(isExpansionInMainFile(), isUserProvided()).bind("method");

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
      llvm::outs() << "--------------\n";

      if (true)
      {
        std::ofstream test_file("automatically_generated.cpp", std::ios::app);
        if (test_file.is_open())
        {
          // Outputs to example.txt through a_file
          test_file << method_unit_test_stub(C);
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

int main(int argc, const char **argv)
{
  auto ExpectedParser = CommonOptionsParser::create(argc, argv, MyToolCategory);

  if (!ExpectedParser)
  {
    // Fail gracefully for unsupported options.
    llvm::errs() << ExpectedParser.takeError();
    return 1;
  }
  CommonOptionsParser &OptionsParser = ExpectedParser.get();

  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());

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

  return Tool.run(newFrontendActionFactory(&Finder).get());
}