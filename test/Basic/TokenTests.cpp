//
// Created by Ciaran on 12/10/2021.
//

#include "gtest/gtest.h"
#include "tinylang/Basic/Lexer.h"

class ASTTests : public ::testing::Test {
public:
    ASTTests() = default;
};


TEST_F(ASTTests, CheckIsWhenTrue){
    Token t(Token::plus, "plus");
    ASSERT_TRUE(t.is(Token::plus));
}

TEST_F(ASTTests, CheckIsWhenFalse){
    Token t(Token::plus, "plus");
    ASSERT_FALSE(t.is(Token::minus));
}

TEST_F(ASTTests, CheckGetTextWhenTrue){
    Token t(Token::plus, "plus");
    bool eq = t.getText() == "plus";
    ASSERT_TRUE(eq);
}

TEST_F(ASTTests, CheckGetTextWhenFalse){
    Token t(Token::plus, "plus");
    bool eq = t.getText() == "minus";
    ASSERT_FALSE(eq);
}

TEST_F(ASTTests, CheckIsOneOfWhenTrue){
    Token t(Token::plus, "plus");
    bool v = t.isOneOf(Token::plus, Token::minus);
    ASSERT_TRUE(v);
}

TEST_F(ASTTests, CheckIsOneOfWhenFalse){
    Token t(Token::plus, "plus");
    bool v = t.isOneOf(Token::r_paren, Token::minus);
    ASSERT_FALSE(v);
}

TEST_F(ASTTests, CheckIsOneOfVariadic){
    Token t(Token::plus, "plus");
    bool v = t.isOneOf(Token::plus, Token::minus, Token::number);
    ASSERT_TRUE(v);
}













