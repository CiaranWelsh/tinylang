//
// Created by Ciaran on 12/10/2021.
//

#ifndef TINYLANG_CODEGEN_H
#define TINYLANG_CODEGEN_H

#include "tinylang/Basic/AST.h"

class CodeGen {
public:
    void compile(AST* Tree);
};

#endif //TINYLANG_CODEGEN_H
