//
// Created by Ciaran on 12/10/2021.
//


#include "gtest/gtest.h"
#include "tinylang/Basic/Lexer.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"


class LexerTests : public ::testing::Test {
public:
    LexerTests() = default;

};


TEST_F(LexerTests, GetFirstTokenText) {
    llvm::StringRef s = "A Stream to lex";
    Lexer lex(s);
    Token t;
    lex.next(t);
    ASSERT_EQ(t.getText(), "A");
}

TEST_F(LexerTests, GetFirstTokenKind) {
    llvm::StringRef s = "A Stream to lex";
    Lexer lex(s);
    Token t;
    lex.next(t);
    ASSERT_EQ(Token::ident, t.getKind());
}

TEST_F(LexerTests, CheckWeSkipInitialWhitespace) {
    llvm::StringRef s = "  Initial white space";
    Lexer lex(s);
    Token t;
    lex.next(t);
    ASSERT_EQ(t.getText(), "Initial");
}

TEST_F(LexerTests, CheckEOI) {
    llvm::StringRef s = "";
    Lexer lex(s);
    Token t;
    lex.next(t);
    ASSERT_EQ(t.getKind(), Token::eoi);
}

TEST_F(LexerTests, CheckSingleCharDigit) {
    llvm::StringRef s = "5";
    Lexer lex(s);
    Token t;
    lex.next(t);
    ASSERT_EQ(t.getKind(), Token::number);
}

TEST_F(LexerTests, CheckMultiCharDigit) {
    llvm::StringRef s = "5678";
    Lexer lex(s);
    Token t;
    lex.next(t);
    ASSERT_EQ(t.getText(), "5678");
}





















