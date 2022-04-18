#include "InputParser.hpp"

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include <map>
#include <set>
#include <memory>

class MethodPrinter : public clang::ast_matchers::MatchFinder::MatchCallback
{
    // stanisz: Pair (path, method), because this will be used for all methods in all
    //          translation units.
    std::map<std::string, std::vector<ParsedMethod>> parsed_methods = {};

public:
    std::map<std::string, std::vector<ParsedMethod>> get_parsed_methods() const
    {
        return std::move(parsed_methods);
    }

    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result) override
    {
        clang::SourceManager &source_manager = Result.Context->getSourceManager();

        if (const clang::CXXMethodDecl *C = Result.Nodes.getNodeAs<clang::CXXMethodDecl>("method"))
        {
            if (C->isModulePrivate() == false // stanisz: Cannot test private methods, unless friend...?
                && C->isDeleted() == false    // stanisz: Self explanatory
            )
            {

                auto filename = source_manager.getFilename(C->getLocation()).str();
                parsed_methods[filename].push_back(ParsedMethod(C));
            }
        }
    }
};

class FunctionPrinter : public clang::ast_matchers::MatchFinder::MatchCallback
{
    // stanisz: Pair (path, method), because this will be used for all methods in all
    //          translation units.
    std::map<std::string, std::vector<ParsedFunction>> parsed_functions = {};

public:
    std::map<std::string, std::vector<ParsedFunction>> get_parsed_functions() const
    {
        return std::move(parsed_functions);
    }

    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result) override
    {
        clang::SourceManager &source_manager = Result.Context->getSourceManager();

        if (const clang::FunctionDecl *F = Result.Nodes.getNodeAs<clang::FunctionDecl>("function"))
        {
            if (F->isCXXClassMember() == false)
            {
                auto filename = source_manager.getFilename(F->getLocation()).str();
                parsed_functions[filename].push_back(ParsedFunction(F));
            }
        }
    }
};

std::string ParsedInputSource::get_path() const
{
    return this->path;
}

std::vector<ParsedMethod> ParsedInputSource::get_methods() const
{
    return this->methods;
}

std::vector<ParsedFunction> ParsedInputSource::get_functions() const
{
    return this->functions;
}

std::optional<std::vector<ParsedInputSource>> ClangUnitParser::parse(int argc, const char **argv)
{
    static llvm::cl::OptionCategory option_category = llvm::cl::OptionCategory("ClangUnit parsing options");
    auto ExpectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, option_category);
    if (!ExpectedParser)
    {
        // Fail gracefully for unsupported options.
        llvm::errs() << ExpectedParser.takeError();
        return std::nullopt;
    }
    auto op = &ExpectedParser.get();

    clang::tooling::ClangTool Tool(op->getCompilations(),
                                   op->getSourcePathList());

    llvm::outs() << "INFO: ClangTool created.\n";

    using namespace clang::ast_matchers;
    MatchFinder Finder;
    MethodPrinter MethodPrinter;
    auto MethodMatcher = cxxMethodDecl(isExpansionInMainFile(), isUserProvided()).bind("method");
    Finder.addMatcher(MethodMatcher, &MethodPrinter);
    llvm ::outs() << "INFO: MethodMatcher added.\n";
    FunctionPrinter FunctionPrinter;
    auto FunctionMatcher = functionDecl(isExpansionInMainFile()).bind("function");
    Finder.addMatcher(FunctionMatcher, &FunctionPrinter);
    llvm ::outs() << "INFO: FunctionMatcher added.\n";

    llvm::outs() << "INFO: Starting ClangTool.run()...\n";
    if (Tool.run(clang::tooling::newFrontendActionFactory(&Finder).get()) == 1)
    {
        return std::nullopt;
    }
    llvm::outs() << "INFO: ClangTool finished running.\n";

    std::vector<ParsedInputSource> parsed_input_sources = {};
    auto methods = MethodPrinter.get_parsed_methods();
    auto functions = FunctionPrinter.get_parsed_functions();

    std::set<std::string> paths;

    for (auto &&e : methods)
    {
        paths.insert(e.first);
    }
    for (auto &&e : functions)
    {
        paths.insert(e.first);
    }

    for (auto &&p : paths)
    {
        ParsedInputSource pis(p, methods[p], functions[p]);
        parsed_input_sources.push_back(pis);
    }

    llvm::outs() << "INFO: parsed_input_sources:\n";
    for (auto &&e : parsed_input_sources)
    {
        e.print();
    }

    return parsed_input_sources;
}

void ParsedInputSource::print() const
{
    llvm::outs() << "path: " << this->get_path() << "\n";
    for (auto &&r : this->get_methods())
    {
        r.print();
    }
}

ParsedInputSource::ParsedInputSource(const std::string path, std::vector<ParsedMethod> &methods, std::vector<ParsedFunction> &functions)
    : path(path), methods(methods), functions(functions) {}