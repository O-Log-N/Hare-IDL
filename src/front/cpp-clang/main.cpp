/*******************************************************************************
Copyright (C) 2016 OLogN Technologies AG

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*******************************************************************************/


#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"

#include <cmath>

using namespace clang;
using namespace clang::tooling;
using namespace llvm;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static cl::OptionCategory myToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...");

class FindNamedClassVisitor
    : public RecursiveASTVisitor<FindNamedClassVisitor> {
private:
    ASTContext *context;
public:
    explicit FindNamedClassVisitor(ASTContext *context)
        : context(context) {}

    bool VisitCXXRecordDecl(CXXRecordDecl *declaration) {
        if (declaration->getQualifiedNameAsString().compare(0, 6, "myhare") == 0) {
            //outs() << "Found declaration " << declaration->getQualifiedNameAsString();
            //FullSourceLoc fullLocation = context->getFullLoc(declaration->getLocStart());
            //if (fullLocation.isValid())
            //    outs() << " at "
            //    << fullLocation.getSpellingLineNumber() << ":"
            //    << fullLocation.getSpellingColumnNumber();

            //outs() << "\n";

            outs() << "MAPPING(\"TODO\") PUBLISHABLE_STRUCT " << declaration->getNameAsString() << " {\n";
            
            RecordDecl::field_range r = declaration->fields();
            for (auto it = r.begin(); it != r.end(); ++it) {
                FieldDecl* current = *it;
                StringRef n = current->getName();
                QualType t = current->getType();

                llvm::outs() << t.getAsString() << " " << n.str() << ";\n";
            }
            outs() << "}\n\n";
            declaration->dump();
        }

        return true;
    }
};

class FindNamedClassConsumer : public clang::ASTConsumer {
private:
    FindNamedClassVisitor visitor;
public:
    explicit FindNamedClassConsumer(ASTContext *context)
        : visitor(context) {}

    virtual void HandleTranslationUnit(clang::ASTContext &context) {
        visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
};

class FindNamedClassAction : public clang::ASTFrontendAction {
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance &compiler, llvm::StringRef inFile) {
        return std::unique_ptr<clang::ASTConsumer>(
            new FindNamedClassConsumer(&compiler.getASTContext()));
    }
};

int main(int argc, const char **argv) {

    CommonOptionsParser optionsParser(argc, argv, myToolCategory);

    ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());

    return tool.run(newFrontendActionFactory<FindNamedClassAction>().get());
}
