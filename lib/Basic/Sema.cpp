//
// Created by Ciaran on 12/10/2021.
//

#include "tinylang/Basic/Sema.h"
#include "llvm/ADT/StringSet.h"

namespace {
    class DeclCheck : public AstVisitor {
    public:
        DeclCheck() : HasError(false) = {}

        bool hasError() {
            return HasError;
        }

        void visit(Factor &Node) override {
            if (Node.getKind() == Factr::Ident){
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
                if (Scope.insert(*I).second)
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
























