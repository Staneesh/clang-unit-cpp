#include "InputParser.hpp"

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include <map>
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
            llvm::outs() << "BLAHBLAH METHOD FIRST CHAR: " << C->getNameAsString().substr(0, 1) << "\n";
            if (C->isModulePrivate() == false && C->isDeleted() == false && C->getNameAsString().substr(0, 1) != "~")
            {
                // stanisz: Cannot test private methods, unless friend...?
                auto filename = source_manager.getFilename(C->getLocation()).str();
                parsed_methods[filename].push_back(ParsedMethod(C));
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

    llvm::outs() << "INFO: Starting ClangTool.run()...\n";
    if (Tool.run(clang::tooling::newFrontendActionFactory(&Finder).get()) == 1)
    {
        return std::nullopt;
    }
    llvm::outs() << "INFO: ClangTool finished running.\n";

    std::vector<ParsedInputSource> parsed_input_sources = {};
    auto methods = MethodPrinter.get_parsed_methods();

    for (auto &&e : methods)
    {
        ParsedInputSource pis(e.first, e.second);
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