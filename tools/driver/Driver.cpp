//
// Created by Ciaran on 11/10/2021.
//

#include "tinylang/Basic/CodeGen.h"
#include "tinylang/Basic/Parser.h"
#include "tinylang/Basic/Sema.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"
#include "tinylang/Basic/Version.h"

static llvm::cl::opt<std::string> Input(
        llvm::cl::Positional,
        llvm::cl::desc("<input expression>"),
        llvm::cl::init("")
);

int main(int argc, const char **argv) {
    llvm::InitLLVM X(argc, argv);
    llvm::cl::ParseCommandLineOptions(argc, argv, "calc = the expression compiler\n");
    Lexer Lex(Input);
    Parser parser(Lex);
    AST *Tree = parser.parse();
    if (!Tree || parser.hasError()) {
        llvm::errs() << "Syntax errors occured\n";
        return 1;
    }

    Sema Semantic;
    if (Semantic.semantic(Tree)) {
        llvm::errs() << "Semantic errors occured\n";
        return 1;
    }
    CodeGen CodeGenerator;
    CodeGenerator.compile(Tree);
    return 0;

}