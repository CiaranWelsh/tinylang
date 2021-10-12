//
// Created by Ciaran on 11/10/2021.
//

#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_os_ostream.h"
#include "tinylang/Basic/Version.h"

int main(int argc_, const char** argv_){
    llvm::InitLLVM X(argc_, argv_);
    llvm::outs() << "Hello, I'm tinylang " << tinylang::getTinylangVersion() << "\n";
}