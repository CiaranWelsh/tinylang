//
// Created by Ciaran on 12/10/2021.
//

#ifndef TINYLANG_AST_H
#define TINYLANG_AST_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

class AST;

class Expr;

class Factor;

class BinaryOp;

class WithDecl;

class AstVisitor {
public:
    virtual void visit(AST &) {};

    virtual void visit(Expr &) {};

    virtual void visit(Factor &) = 0;

    virtual void visit(BinaryOp &) = 0;

    virtual void visit(WithDecl &) = 0;
};


class AST {
public:
    virtual  ~AST() = default;

    virtual void accept(ASTVisitor &V) = 0;
};

class Expr : public AST {
public:
    Expr() = default;
};


class Factor : public Expr {
public:
    enum ValueKind {
        Ident, Number
    };

    Factor(ValueKind Kind, llvm::StringRef Val)
            : Kind(Kind), Val(Val) {}

    ValueKind getKind() const {
        return Kind;
    }

    llvm::StringRef getVal() const {
        return Val;
    }

    void accept(AstVisitor &V) override {
        V.visit(*this);
    }

private:
    ValueKind Kind;
    llvm::StringRef Val;
};

class BinaryOp : public Expr {
public:
    enum Operator {
        Plus, Minus, Mul, Div
    };

    BinaryOp(Operator Op, Expr *L, Expr *R)
            : Op(Op), Left(L), Right(R) {}

    Expr *getLeft() {
        return Left;
    }

    Expr *getRight() {
        return Right;
    }

    Operator getOperator() {
        return Op;
    }

    virtual void accept(AstVisitor &V) override {
        V.visit(*this);
    }


private:
    Expr *Left;
    Expr *Right;
    Operator Op;
};

class WithDecl : public AST {
public:
    WithDecl(llvm::SmallVector<llvm::StringRef, 8> Vars, Expr *E)
            : Vars(Vars), E(E) {};

    VarVector::const_iterator begin() {
        return Vars.begin();
    }

    VarVector::const_iterator end() {
        return Vars.end();
    }

    Expr *getExpr() {
        return E;
    }

    void accept(AstVisitor &V) override {
        V.visit(*this);
    }

private:
    using VarVector = llvm::SmallVector<llvm::StringRef, 8>;
    VarVector Vars;
    Expr *E;
};


#endif //TINYLANG_AST_H
