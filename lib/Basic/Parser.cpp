//
// Created by Ciaran on 11/10/2021.
//

#include "tinylang/Basic/Parser.h"


AST *Parser::parse() {
    AST *Res = parseCalc();
    expect(Token::eoi);
    return Res;
}

AST *Parser::parseCalc() {
    Expr *E;
    llvm::SmallVector<llvm::StringRef, 8> Vars;

    if (Tok.is(Token::KW_with)) {
        // if Token Tok is "with", then we expect
        // an identifier next. If we don't get one
        // we error
        advance();
        if (expect(Token::ident)) {
            // with isn't followed by anything.
            // syntax error
            goto _error;
        }
        // the first item after 'with' is an identifier
        // grab it and store in a vector
        Vars.push_back(Tok.getText());

        // advance to next token.
        advance();

        // we are either expecting a comma for more
        // variable declarations or a colon to mark then
        // end of variable declarations.
        while (Tok.is(Token::comma)) {

            // if we have a comma and the following token
            // is not an ident, error
            advance(); // represents the comma
            if (expect(Token::ident)) {
                goto _error;
            }
            // otherwise we add to our list of tokens
            Vars.push_back(Tok.getText());
            // moves to next comma or breaks out of loop if
            // not comma anymore
            advance();
        }

        // we're now expecting a colon. We check that the next Token
        // is a colon and error if not. The colon doesn't
        // actually do anything so we just consume it
        if (consume(Token::colon))
            goto _error;

        // next we parse the expression and assign it to E
        E = parseExpr();

        if (Vars.empty())
            return E;
        else
            return new WithDecl(Vars, E);
    }

    _error:
    while (!Tok.is(Token::eoi))
        advance();
    return nullptr;
}

Expr *Parser::parseExpr() {
    Expr *Left = parseTerm();
    while (Tok.isOneOf(Token::plus, Token::minus)) {
        BinaryOp::Operator Op = Tok.is(Token::plus) ? BinaryOp::Plus : BinaryOp::Minus;
        advance();
        Expr *Right = parseTerm();
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;
}


Expr *Parser::parseTerm() {
    Expr *Left = parseFactor();
    while (Tok.isOneOf(Token::star, Token::slash)) {
        BinaryOp::Operator Op = Tok.is(Token::star) ? BinaryOp::Mul : BinaryOp::Div;
        advance();
        Expr *Right = parseFactor();
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;
}

Expr *Parser::parseFactor() {
    Expr *Res = nullptr;
    switch (Tok.getKind()) {
        case Token::number:
            Res = new Factor(Factor::Number, Tok.getText());
            advance();
            break;
        case Token::ident:
            Res = new Factor(Factor::Ident, Tok.getText());
            advance();
            break;
        case Token::l_paren:
            advance();
            Res = parseExpr();
            if (!consume(Token::r_paren))
                break;
        default:
            if (!Res) error();
            while (!Tok.isOneOf(Token::r_paren, Token::star, Token::plus, Token::minus, Token::slash, Token::eoi))
                advance();
    }
    return Res;
}



























