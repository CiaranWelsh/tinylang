//
// Created by Ciaran on 11/10/2021.
//

#ifndef TINYLANG_LEXER_H
#define TINYLANG_LEXER_H

#include "llvm/ADT/StringRef.h" // C string + its length
#include "llvm/Support/MemoryBuffer.h" // read only access to a memory buffer

class Lexer;

class Token {

public:
    enum TokenKind : unsigned short {
        eoi, // end of input
        unknown, // used for error
        ident,
        number,
        comma,
        colon,
        plus,
        minus,
        star,
        slash,
        l_paren,
        r_paren,
        KW_with
    };

    TokenKind getKind() const {
        return kindl;
    }

    llvm::StringRef getText
    const {
        return Text;
    };

    bool is(TokenKind K) const { return Kind == K; }

    bool isOneOf(TokenKind K1, TokenKind K2) const {
        return is(K1) || is(K2);
    }

    template<typename... Ts>
    bool isOneOf(TokenKind K1, TokenKind K2, Ts... Ks) const{
        return is(K1) || isOneOf(K2, Ks...);
    }

private:

    friend class Lexer;

    TokenKind Kind;
    llvm::StringRef Text;

};


class Lexer {
public:
    Lexer(const llvm::StringRef& Buffer)
        :
        BufferStart(Buffer.begin()),
        BufferPtr(Buffer.begin()){}

    void next(Token& token);

private:

    void formToken(Token& Result, const char* TokEnd, Token::TokenKind Kind);

    const char* BufferStart;
    const char* BufferPtr;
};

#endif //TINYLANG_LEXER_H
