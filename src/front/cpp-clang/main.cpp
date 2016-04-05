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
using namespace std;

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
    const set<string>& names;
public:
    explicit FindNamedClassVisitor(ASTContext *context, const set<string>& names)
        : context(context), names(names) {}

    bool VisitCXXRecordDecl(CXXRecordDecl *declaration) {

        bool process = false;
        string name = declaration->getQualifiedNameAsString();

        auto it = names.find(name);
        if (it != names.end()) {
            process = true;
        }
        else if (declaration->hasAttr<HareCXXRecordAttr>()) {
            process = true;
            HareCXXRecordAttr* attr = declaration->getAttr<HareCXXRecordAttr>();
            //for (auto it = attr->argument_begin(); it != attr->argument_end(); ++it) {
            //    outs() << "HareCXXRecordAttr argument " << *it << "\n";
            //}
        }
        else if (declaration->hasAttr<AnnotateAttr>()) {
            AnnotateAttr* attr = declaration->getAttr<AnnotateAttr>();
            StringRef t = attr->getAnnotation();
            if (t.startswith("hare::idl(")) {
                process = true;
            }
        }

        if(process) {
            //outs() << "Found declaration " << declaration->getQualifiedNameAsString();
            //FullSourceLoc fullLocation = context->getFullLoc(declaration->getLocStart());
            //if (fullLocation.isValid())
            //    outs() << " at "
            //    << fullLocation.getSpellingLineNumber() << ":"
            //    << fullLocation.getSpellingColumnNumber();

            //outs() << "\n";

            outs() << "MAPPING(\"TODO\") PUBLISHABLE_STRUCT " << name << " {\n";
            
            RecordDecl::field_range r = declaration->fields();
            for (auto it = r.begin(); it != r.end(); ++it) {
                FieldDecl* current = *it;
                string n = current->getDeclName().getAsString();
                QualType t = current->getType().getCanonicalType();

                llvm::outs() << t.getAsString() << " " << n << ";\n";
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
    explicit FindNamedClassConsumer(ASTContext *context, const set<string>& names)
        : visitor(context, names) {}

    virtual void HandleTranslationUnit(clang::ASTContext &context) {
        visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
};

class FindNamedClassAction : public clang::ASTFrontendAction {
private:
    const set<string>& names;
public:
    FindNamedClassAction(const set<string>& names) :names(names) {}
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance &compiler, llvm::StringRef inFile) {
        return std::unique_ptr<clang::ASTConsumer>(
            new FindNamedClassConsumer(&compiler.getASTContext(), names));
    }
};

class FindNamedClassActionFactory : public FrontendActionFactory {
private:
    const set<string>& names;
public:
    FindNamedClassActionFactory(const set<string>& names) :names(names) {}
    FindNamedClassAction *create() override { return new FindNamedClassAction(names); }
};


int main(int argc, const char **argv) {

    CommonOptionsParser optionsParser(argc, argv, myToolCategory);

    ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());

    set<string> names = { "foundByName" };

    return tool.run(new FindNamedClassActionFactory(names));
}
