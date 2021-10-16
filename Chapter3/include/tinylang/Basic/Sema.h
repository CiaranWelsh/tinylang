//
// Created by Ciaran on 12/10/2021.
//

#ifndef TINYLANG_SEMA_H
#define TINYLANG_SEMA_H


#include "AST.h"
#include "Lexer.h"

class Sema {
public:
    bool semantic(AST* Tree);
};

#endif //TINYLANG_SEMA_H
