//
// Created by Ciaran on 11/10/2021.
//

#ifndef TINYLANG_PARSER_H
#define TINYLANG_PARSER_H

#include "AST.h"
#include "Lexer.h"
#include "llvm/Support/raw_os_ostream.h"

class Parser {
public:

    Parser(Lexer& Lex): Lex(Lex), HasError(false){
        advance();
    }

    bool hasError(){
        return HasError;
    }

    AST* parse();


private:
    AST *parseCalc();

    Expr *parseExpr();

    Expr *parseTerm();

    Expr *parseFactor();

    void error() {
        llvm::errs() << "Unexpected " << Tok.getText() << "\n";
        HasError = true;
    }

    void advance() {
        Lex.next(Tok);
    }

    bool expect(Token::TokenKind Kind) {
        if (Tok.getKind() != Kind) {
            error();
            return true;
        }
        return false;
    }

    bool consume(Token::TokenKind Kind) {
        if (expect(Kind)) {
            return true;
        }
        advance();
        return false;
    }

    Lexer &Lex;
    Token Tok; // a look-a-head token
    bool HasError;
};


#endif //TINYLANG_PARSER_H
