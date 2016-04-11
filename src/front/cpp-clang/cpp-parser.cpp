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

#include "../../idlc_include.h"
#include "cpp-parser.h"

//#include <cmath>

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"


using namespace clang;
using namespace clang::tooling;
using namespace llvm;
using namespace std;


class FindNamedClassVisitor
    : public RecursiveASTVisitor<FindNamedClassVisitor> {
private:
    ASTContext *context;
    const set<string>& names;
    Root& root;
    bool findByName;
public:
    explicit FindNamedClassVisitor(ASTContext *context, const set<string>& names, Root& root)
        : context(context), names(names), root(root), findByName(!names.empty()){}

    bool VisitCXXRecordDecl(CXXRecordDecl *declaration) {

        bool process = false;
        string name = declaration->getQualifiedNameAsString();

        if (findByName) {
            auto it = names.find(name);
            if (it != names.end()) {
                process = true;
            }
        }
        else {
            if (declaration->hasAttr<HareMappingAttr>()) {
                process = true;
                HareMappingAttr* at = declaration->getAttr<HareMappingAttr>();
                StringRef s = at->getPublishableStruct();
                if (!s.empty())
                    name = s.str();
                //for (auto it = attr->argument_begin(); it != attr->argument_end(); ++it) {
                //    outs() << "HareCXXRecordAttr argument " << *it << "\n";
                //}
            }
            else if (declaration->hasAttr<AnnotateAttr>()) {
                AnnotateAttr* at = declaration->getAttr<AnnotateAttr>();
                StringRef t = at->getAnnotation();
                if (t == "hare::mapping") {
                    process = true;
                }
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

                if (current->hasAttr<HareEncodeAsAttr>()) {
                    HareEncodeAsAttr* at = current->getAttr<HareEncodeAsAttr>();
                    llvm::outs() << t.getAsString() << " " << n << " " << at->getEncoding() << ";\n";
                }
                else if (current->hasAttr<AnnotateAttr>()) {
                    AnnotateAttr* at = current->getAttr<AnnotateAttr>();
                    StringRef anot = at->getAnnotation();
                    if (anot.startswith("hare::encode_as(")) {
                        llvm::outs() << t.getAsString() << " " << n << " " << anot << ";\n";
                    }
                }
                else
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
    explicit FindNamedClassConsumer(ASTContext *context, const set<string>& names, Root& root)
        : visitor(context, names, root) {}

    virtual void HandleTranslationUnit(clang::ASTContext &context) {
        visitor.TraverseDecl(context.getTranslationUnitDecl());
    }
};

class FindNamedClassAction : public clang::ASTFrontendAction {
private:
    const set<string>& names;
    Root& root;
public:
    FindNamedClassAction(const set<string>& names, Root& root) :names(names), root(root) {}
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance &compiler, llvm::StringRef inFile) {
        return std::unique_ptr<clang::ASTConsumer>(
            new FindNamedClassConsumer(&compiler.getASTContext(), names, root));
    }
};

class FindNamedClassActionFactory : public FrontendActionFactory {
private:
    const set<string>& names;
    Root& root;
public:
    FindNamedClassActionFactory(const set<string>& names, Root& root) :names(names), root(root) {}
    FindNamedClassAction *create() override { return new FindNamedClassAction(names, root); }
};


int parseCplusplusSourceFileInternal(const vector<string>& files, const set<string>& classNames,
    const CompilationDatabase& dataBase, const vector<string>& extraArgs, Root& root)
{
    ClangTool tool(dataBase, files);

    if(!extraArgs.empty())
        tool.appendArgumentsAdjuster(getInsertArgumentAdjuster(extraArgs,
            ArgumentInsertPosition::BEGIN));

    return tool.run(new FindNamedClassActionFactory(classNames, root));
}

Root* parseCppSourceFile(const string& fileName, const set<string>& classNames)
{
    FixedCompilationDatabase dataBase(".", vector<string>());
    vector<string> extraArgs = { "-fno-ms-compatibility", "-xc++", "-DHAREIDL_USE_CXX11_ATTRIBUTE" };
    unique_ptr<Root> root(new Root());
    int result = parseCplusplusSourceFileInternal({ fileName }, classNames, dataBase, extraArgs, *root);
    if (result != 0)
        throw "TODO!"; // TODO

    return root.release();
}

/*
int main(int argc, const char **argv)
{
    // this gives an error about compilation database not found,
    // when no -- is given at input
    CommonOptionsParser optionsParser(argc, argv, myToolCategory);

    CompilationDatabase& dataBase = optionsParser.getCompilations();
    vector<string> files = optionsParser.getSourcePathList();

    unique_ptr<Root> root(new Root());

    return parseCplusplusSourceFileInternal(files, set<string>(), dataBase, vector<string>(), *root);
}
*/