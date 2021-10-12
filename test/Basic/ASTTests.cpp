//
// Created by Ciaran on 12/10/2021.
//

#include "gtest/gtest.h"
#include "tinylang/Basic/Parser.h"

class ASTTests : public ::testing::Test {
public:
    ASTTests() = default;
};


TEST_F(ASTTests, CheckIsWhenTrue){
    Factor factorAst(Factor::Ident, "id");
//    ASTVisitor v;
//    factorAst.accept(v)

}














