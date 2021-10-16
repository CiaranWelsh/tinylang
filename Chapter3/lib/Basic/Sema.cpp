//
// Created by Ciaran on 12/10/2021.
//

#include <llvm/Support/raw_ostream.h>
#include "tinylang/Basic/Sema.h"
#include "llvm/ADT/StringSet.h"

namespace {
    class DeclCheck : public ASTVisitor {
    public:
        DeclCheck() : HasError(false) {}

        bool hasError() {
            return HasError;
        }

        void visit(Factor &Node) override {
            if (Node.getKind() == Factor::Ident){
                if (Scope.find(Node.getVal()) == Scope.end()){
                    error(Not, Node.getVal());
                }
            }
        }

        void visit(BinaryOp& Node) override {
            if (Node.getLeft()){
                Node.getLeft()->accept(*this);
            } else {
                HasError = true;
            }
            if (Node.getRight()){
                Node.getRight()->accept(*this);
            } else {
                HasError = true;
            }
        }

        void visit(WithDecl& Node) override {
            for (auto I = Node.begin(), E = Node.end(); I != E; ++I){
                // the second element of the pair returned by Scope.insert
                // indicates whether the insertion took place or not.
                if (!Scope.insert(*I).second)
                    error(Twice, *I);
            }
            if (Node.getExpr())
                Node.getExpr()->accept(*this);
            else
                HasError = true;
        }

    private:

        enum ErrorType {Twice, Not};

        void error(ErrorType ET, llvm::StringRef V){
            llvm::errs() << "Variable " << V << " " << (ET == Twice ? "already" : "not")
                << " declared\n";
            HasError = true;
        }

        llvm::StringSet<> Scope;
        bool HasError;
    };
}


bool Sema::semantic(AST *Tree) {
    if (!Tree)
        return false;
    DeclCheck check;
    Tree->accept(check);
    return check.hasError();
}
























