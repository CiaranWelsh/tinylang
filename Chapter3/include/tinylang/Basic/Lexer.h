//
// Created by Ciaran on 11/10/2021.
//

#ifndef TINYLANG_LEXER_H
#define TINYLANG_LEXER_H

#include "llvm/ADT/StringRef.h" // C string + its length
#include "llvm/Support/MemoryBuffer.h" // read only access to a memory buffer


namespace charinfo {
    LLVM_READNONE inline bool isWhitespace(char c);

    LLVM_READNONE inline bool isDigit(char c);

    LLVM_READNONE inline bool isLetter(char c);

}

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

    Token() = default;

    Token(TokenKind tk, llvm::StringRef s)
        : Kind(tk), Text(s){}

    TokenKind getKind() const {
        return Kind;
    }

    llvm::StringRef getText() const {
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
    explicit Lexer(const llvm::StringRef& Buffer)
        :
        BufferStart(Buffer.begin()),
        BufferPtr(Buffer.begin()){}

    void next(Token& token);

    const char* getBufferStart(){
        return BufferStart;
    }

    const char* getBufferPtr(){
        return BufferPtr;
    }

private:

    void formToken(Token& Result, const char* TokEnd, Token::TokenKind Kind);

    const char* BufferStart;
    const char* BufferPtr;

};

#endif //TINYLANG_LEXER_H
