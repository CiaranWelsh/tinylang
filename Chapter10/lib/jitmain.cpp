//
// Created by Ciaran on 13/10/2021.
//

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/TargetSelect.h"


llvm::Error jitmain(
        std::unique_ptr<llvm::Module> m, std::unique_ptr<llvm::LLVMContext> ctx,
        int argc, char *argv[]
) {

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

    /**
     * Jit'ed code usually needs to access symbols in the host program or in supported libraries.
     *
     * One way to do this is to "bake in" process symbols as the code is compiled to IR by turning
     * external references into pre-resolved integer constants. However this ties the JIT'd
     * code to the current processes virtual memory layout (which means that it cannot be cached between runs)
     * It also makes debugging difficult since lower level program representations become
     * difficult to interpret, as they are all opaque integer values.
     *
     * An alternative and better solution is to maintain extermal symbolic references and let the JIT-linker
     * bind them at run time (like a shared library). To allow the JIT linker find these external
     * definitions, their addresses must be added to a JITDylib. This can be done in a one by one
     * basis using something similar to :
     *   const DataLayout &DL = getDataLayout();
     *   MangleAndInterner Mangle(ES, DL);  // create a mangler
     *   auto &JD = ES.createJITDylib("main");
     *   JD.define(
     *     absoluteSymbols({
     *       { Mangle("puts"), pointerToJITTargetAddress(&puts)},
     *       { Mangle("gets"), pointerToJITTargetAddress(&getS)}
     *     }));
     *
     * This can be a ballache to do manually, so LLVM provides an alternative: definition generators.
     * If a definition generator is attached to a JITDylib then any unsuccessful
     * lookup on that JITDylib will fall back to calling the definition generator. The
     * definition generator may choose to generate a new definition for the missing
     * symbols. Of particular use here is the DynamicLibrarySearchGenerator utility.
     * This can be used to reflect the whole exported symbol set of the process of a
     * specific dynamic library, or a subset of either of these determined by a
     * predicate.
     *
     * For instance, to enable linking against all symbols in a dynamic library:
     *     const DataLayout &DL = getDataLayout();
     *     auto &JD = ES.createJITDylib("main");
     *
     *     JD.addGenerator(DynamicLibrarySearchGenerator::Load("/path/to/lib"
     *                                                         DL.getGlobalPrefix()));
     *
     *     // IR added to JD can now link against all symbols exported by the library
     *     // at '/path/to/lib'.
     *     CompileLayer.add(JD, loadModule(...));
     *
     * Now if a symbol is missing, the DLSG looks up the symbol in the currently loaded
     * symobol set.
     */
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















