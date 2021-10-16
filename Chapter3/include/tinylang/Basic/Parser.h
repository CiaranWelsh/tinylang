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

    /**
     * Constructor for Parser
     *
     * @details calls the advance method which populates the
     * first Tok
     */
    explicit Parser(Lexer& Lex): Lex(Lex), HasError(false){
        advance();
    }

    bool hasError() const{
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

    /**
     * @brief advances the current token to the next
     */
    void advance() {
        Lex.next(Tok);
    }

    /**
     * @brief throws error if Tok::Kind
     * is not equal to @param Kind.
     */
    bool expect(Token::TokenKind Kind) {
        if (Tok.getKind() != Kind) {
            error();
            return true;
        }
        return false;
    }

    /**
     * @brief if the current Tok is
     * of type @param Kind return true
     * otherwise advance to the next token
     * and return false
     */
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
