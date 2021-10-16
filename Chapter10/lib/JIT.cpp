//
// Created by Ciaran on 14/10/2021.
//

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"

/**
 * Define a single input file containing IR
 */
static llvm::cl::opt<std::string> InputFile(
        llvm::cl::Positional, llvm::cl::Required, llvm::cl::desc("<input-file>")
);

/**
 *
 *
 * @details The parseIRFile() function reads the IR passed in on the cmd line.
 * The code can be text or a bitode file. The function returns a poitner to
 * the create dmodule. Error handling is a bit different because a textual
 * IR file can be parsed, which is not necessarily syntatically correct.
 * The SMDiagnostic instance hold the error information in case of a syntax error.
 * The err message is printed and the application is exited.
 */
std::unique_ptr<llvm::Module> loadModule(
        llvm::StringRef Filename, llvm::LLVMContext &Ctx, const char *ProgName) {
    llvm::SMDiagnostic Err;
    std::unique_ptr<llvm::Module> Mod = llvm::parseIRFile(Filename, Err, Ctx);
    if (!Mod.get()) {
        Err.print(ProgName, llvm::errs());
        exit(-1);
    }
    return std::move(Mod);
}


llvm::Error jitmain(
        std::unique_ptr<llvm::Module> m, std::unique_ptr<llvm::LLVMContext> ctx,
        int argc, char *argv[]) {

    /**
     * Construct an orc JIT. This replaces MCJIT.
     */
    auto JIT = llvm::orc::LLJITBuilder().create();
    if (!JIT)
        return JIT.takeError();

    /**
     *  We add a LLVM IR module, choosing the thread safe version so that if we configure
     *  multithreading later we don't have a problem
     */
    if (auto Err = (*JIT)->addIRModule(llvm::orc::ThreadSafeModule(std::move(m), std::move((ctx))))) {
        return Err;
    }

    /**
     * Support symbols from the C library.
     */

    // data layout refers to specification of type sizes for this IR module. Here's an example:
    //    target datalayout = "e-m:e-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128"
    const llvm::DataLayout &DL = (*JIT)->getDataLayout();

    // DynamicLibrarySearchGenerator exposes symbols/names that are found in a shared library.
    auto DLSG = llvm::orc::DynamicLibrarySearchGenerator::GetForCurrentProcess(DL.getGlobalPrefix());
    if (!DLSG) {
        return DLSG.takeError();
    }
    (*JIT)->getMainJITDylib().addGenerator(std::move(*DLSG));

    /**
     * Find the "main" symbol. This must be defined in the IR module
     * provided on the command line. The lookup triggers compilation of
     * this module. Other symbols are resolved using the
     * generator added in the previous step.
     */

    llvm::Expected<llvm::JITEvaluatedSymbol> MainSym = (*JIT)->lookup("main");
    if (!MainSym)
        return MainSym.takeError();

    /**
     * Now we ask the returned JIT symbol for the address of the main function and cast
     * that address to the prototype of C main().
     */
    auto *Main = (int (*)(int, char **)) MainSym->getAddress();


    /**
     * Now, we can call the main function in the IR module and pass it
     * the arguments,
     */
    (void)Main(argc, argv);

    // report success
    return llvm::Error::success();
}

int main(int argc, char *argv[]){
    llvm::InitLLVM X(argc, argv);

    /**
     * Reliably detect host environment.
     */
    llvm::InitializeNativeTarget();

    /**
     * initialize the assembly printer and parser
     * for host platform.
     */
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();


    llvm::cl::ParseCommandLineOptions(argc, argv, "JIT\n");

    // initialize the context
    auto Ctx = std::make_unique<llvm::LLVMContext>();

    std::unique_ptr<llvm::Module> M = loadModule(InputFile, *Ctx, argv[0]);

    llvm::ExitOnError exitOnError(std::string(argv[0]) + ":");
    exitOnError(jitmain(std::move(M), std::move(Ctx), argc, argv));

    return 0;
}














