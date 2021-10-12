//
// Created by Ciaran on 12/10/2021.
//

#include "gtest/gtest.h"
#include "tinylang/Basic/Parser.h"
#include "tinylang/Basic/AST.h"

class ASTTests : public ::testing::Test {
public:
    ASTTests() = default;
};


TEST_F(ASTTests, CheckParserFailsWithNonKeyword){
    llvm::StringRef b = "word";
    Lexer lexer(b);
    Parser parser(lexer);
    AST* ast = parser.parse();
    ASSERT_FALSE(ast); // nullptr
}

TEST_F(ASTTests, CheckParseWith){
    llvm::StringRef b = "with a: a * 3";
    Lexer lexer(b);
    Parser parser(lexer);
    AST* ast = parser.parse();
}














