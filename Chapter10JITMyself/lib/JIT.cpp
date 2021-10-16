//
// Created by Ciaran on 15/10/2021.
//

#ifndef TINYLANG_JIT_CPP
#define TINYLANG_JIT_CPP

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/IRTransformLayer.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/Mangling.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"

#include "llvm/ExecutionEngine/Orc/ExecutorProcessControl.h"
//#include "llvm/ExecutionEngine/Orc/TargetProcessControl.h"
//#include "llvm/ExecutionEngine/Orc/Shared/TargetProcessControlTypes.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/TargetSelect.h"


int main(int argc, char *argv[]);


/**
 * Define a single input file containing IR
 */
static llvm::cl::opt<std::string> InputFile(
        llvm::cl::Positional, llvm::cl::Required, llvm::cl::desc("<input-file>")
);

class JIT {
public:

    JIT(std::unique_ptr<llvm::orc::ExecutionSession> ExeS,
        llvm::DataLayout DataL,
        llvm::orc::JITTargetMachineBuilder JTMB) :
            DL(DataL),
            ES(std::move(ExeS)),
            Mangle(*this->ES, DL),
            ObjectLinkingLayer(std::move(createObjectLinkingLayer(*this->ES, JTMB))),
            CompileLayer(std::move(createCompileLayer(*this->ES, *ObjectLinkingLayer, std::move(JTMB)))),
            OptIRLayer(std::move(createOptIRLayer(*this->ES, *CompileLayer))),
            MainJITDylib((*this->ES).createBareJITDylib("<main>")) {

        MainJITDylib.addGenerator(
                llvm::cantFail(
                        llvm::orc::DynamicLibrarySearchGenerator::GetForCurrentProcess(DataL.getGlobalPrefix())
                )
        );
    }


    /**
     * Init is split into three parts. In C++ you cannot return an error.
     * Instea we use a simple factory function which can do the error
     * handling prior to constructing the object.
     */
    static llvm::Expected<std::unique_ptr<JIT>> create() {

        // A SymbolStringPool is used to implement string internalisation
        // and is used by multiple classes.
//        auto SSP = std::make_shared<llvm::orc::SymbolStringPool>();

        // Used for taking control of the current process.
        auto EPC = llvm::orc::SelfExecutorProcessControl::Create();
        if (!EPC) {
            return EPC.takeError();
        }

        std::unique_ptr<llvm::orc::ExecutionSession> ES
                = std::make_unique<llvm::orc::ExecutionSession>(std::move(*EPC));


        // construct a JITTargetMachineBuilder, but to do so we need the triple
        // target for the JIT process.
        llvm::orc::JITTargetMachineBuilder JTMB(ES->getExecutorProcessControl().getTargetTriple());

        // query the target machine builder for its data layout.
        auto DL = JTMB.getDefaultDataLayoutForTarget();
        if (!DL) {
            return DL.takeError();
        }


        // construct and return a JIT ptr.
        return std::make_unique<JIT>(std::move(ES), std::move(*DL), std::move(JTMB));
    }

    static std::unique_ptr<llvm::orc::RTDyldObjectLinkingLayer> createObjectLinkingLayer(
            llvm::orc::ExecutionSession &ES,
            llvm::orc::JITTargetMachineBuilder &JTMB) {
        auto GetMemoryManager = []() {
            return std::make_unique<llvm::SectionMemoryManager>();
        };
        auto OLLayer = std::make_unique<llvm::orc::RTDyldObjectLinkingLayer>(ES, GetMemoryManager);

        if (JTMB.getTargetTriple().isOSBinFormatCOFF()) {
            // issue with COFF which is used on windows. COFF does not allow
            // functions to be marked as exported,
            OLLayer->setOverrideObjectFlagsWithResponsibilityFlags(true);
            OLLayer->setAutoClaimResponsibilityForObjectSymbols(true);
        }
        return std::move(OLLayer);
    }

    /**
     * To initialize the compiuler layer, we need an IRCompiler instance. The IRCompiler instance
     * is responsible for compiling an IR module into an object file. If our JIT
     * compilier doesn't use threads then we can use the SimpleCompiler class, which compiles
     * the IR module using a given target machine. The TargetMachine class is not thread-safe.
     * Likewise the SimpleCompiler class is not thread safe. To support compilarion with multiple threads
     * we use the ConcurrentIRCompiler class which create a new TargetMachine instance for each module to compile.
     * This approach solves th eproblem with multiple threads.
     *
     */
    static std::unique_ptr<llvm::orc::IRCompileLayer> createCompileLayer(
            llvm::orc::ExecutionSession &ES,
            llvm::orc::RTDyldObjectLinkingLayer &OLLayer,
            llvm::orc::JITTargetMachineBuilder JTMB
    ) {
        auto IRCompiler = std::make_unique<llvm::orc::ConcurrentIRCompiler>(std::move(JTMB));
        auto IRCLayer = std::make_unique<llvm::orc::IRCompileLayer>(ES, OLLayer, std::move(IRCompiler));
        return std::move(IRCLayer);
    }

    /**
     * Instead of compiling the IR module directly to mahcine code, we install a layer that optimizer
     * the IR first. This is a deliberate design decision. We turn our JIT compimler into an optimizing JIT
     * compiiler, which produces faster code that takes longer to produce. This means a delay for the user.
     * We do not add lazy compilation, so enture modules are compiled when just a symbol is looked up.
     * This can add up to a significant time before the user sees the code executing.
     *
     * Lazy copmpilation is not a proper solution in all circumstances
     *
     * Lazy compilation is realized through moving each function into the module of its own,
     * which is compiled when the funciton name is looked up. This prevents
     * inter-procedural optimizations such as inlining, because th einliner
     * pass needs access to the boduy of th efunciton called to inline them. As a result, the
     * user sees a faster startup with lzy compiilation, but the code produced is
     * not as optimial as it could be. These design decisions depend on intended use.
     * Here we decide for fast code, accepting slkower start up times is okay. The optimization layer
     * is realized as a transformation layer. The IRTransformLayer class delegates the transformation
     * to a function in our case to the optimizeModule funciton.
     *
     */
    static std::unique_ptr<llvm::orc::IRTransformLayer> createOptIRLayer(
            llvm::orc::ExecutionSession &ES,
            llvm::orc::IRCompileLayer &CompileLayer) {
        auto OptIRLayer = std::make_unique<llvm::orc::IRTransformLayer>(
                ES, CompileLayer, optimizeModule);
        return std::move(OptIRLayer);
    }

    /**
     * The optimizeModule() funciton is an example of a transformation on an IR module.
     * The function gets the module to transform as parameter and returns the transformed one.
     * Because the JIT can potentially run with multiple threads, the IR module is wrapped
     * in a ThreadSafeModule instance.
     *
     * We require a PassBuilder instance to create an optimization pipeline.
     * First we define a couple of analysis managers and register them
     * afterward at the pass builder. Then
     * we populate a ModulePassManager instance with the default optimization
     * pipeline for th eO2 level. This is again a design decision: the O2 level
     * produces fast machine code already, but does this faster then the O3 level.
     * Afterward we run th epipeline on the module. Finally the optimized module
     * is returned to the caller.
     */
    static llvm::Expected<llvm::orc::ThreadSafeModule> optimizeModule(
            llvm::orc::ThreadSafeModule TSM,
            const llvm::orc::MaterializationResponsibility &R) {
        TSM.withModuleDo([](llvm::Module &M) {
            bool DebugPM = false;
            llvm::PassBuilder PB;
            llvm::LoopAnalysisManager LAM;
            llvm::FunctionAnalysisManager FAM;
            llvm::CGSCCAnalysisManager CGAM;
            llvm::ModuleAnalysisManager MAM;
            FAM.registerPass(
                    [&] { return PB.buildDefaultAAPipeline(); });
            PB.registerModuleAnalyses(MAM);
            PB.registerCGSCCAnalyses(CGAM);
            PB.registerFunctionAnalyses(FAM);
            PB.registerLoopAnalyses(LAM);
            PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);
            llvm::ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(
                    llvm::PassBuilder::OptimizationLevel::O2, DebugPM);
            MPM.run(M, MAM);
        });

        return std::move(TSM);
    }

    /**
     * The client of the JIT class needs a way to add the IR module, which we
     * provide with the addIRModuleI() funciton. Remember the layer stack we created:
     * we must add the IR module to the top layer, otherwise we would accidently
     * bypass some layers. This would be a programming error
     * that is not easily spotted: if the OptIRLayer
     * member is replaced by a CompileLayer member, then our JIT class still works,
     * but not as an optimizing JIT because we have bypassed this payer. This
     * is not cause for encern as regards this small implementation, but
     * in a large JIT optimization, we would introduce a function to return the top-level layer.
     */
    llvm::Error addIRModule(llvm::orc::ThreadSafeModule TSM,
                            llvm::orc::ResourceTrackerSP RT = nullptr) {
        if (!RT)
            RT = MainJITDylib.getDefaultResourceTracker();
        return OptIRLayer->add(RT, std::move(TSM));
    }

    /**
     * Likewise a client of our JIT class needs a way to look up a symbol.
     * We delegate this to the ExecutionSession instance, passing
     * in a reference to the main symbol table and the
     * mangled and internalizxed name of the requested symbol.
     */
    llvm::Expected<llvm::JITEvaluatedSymbol> lookup(llvm::StringRef Name) {
        return ES->lookup({&MainJITDylib}, Mangle(Name.str()));
    }

    /**
     * Putting the JIT compiler together was quite easy. Initializing the class
     * is a bit tricky as it involves a factory method and a constructor call
     * for the JIT class, and factory methods for each layer. This distribution is
     * caused by limitation in C++, although the code itself is simple.
     */


private:
    std::unique_ptr<llvm::orc::ExecutorProcessControl> TPC;
    std::unique_ptr<llvm::orc::ExecutionSession> ES;
    llvm::DataLayout DL;
    llvm::orc::MangleAndInterner Mangle;
    std::unique_ptr<llvm::orc::RTDyldObjectLinkingLayer> ObjectLinkingLayer;
    std::unique_ptr<llvm::orc::IRCompileLayer> CompileLayer;
    std::unique_ptr<llvm::orc::IRTransformLayer> OptIRLayer;
    llvm::orc::JITDylib &MainJITDylib;
};


llvm::Error jitmain(
        std::unique_ptr<llvm::Module> m, std::unique_ptr<llvm::LLVMContext> ctx,
        int argc, char *argv[]) {

    /**
     * Construct an orc JIT. This replaces MCJIT.
     */
    auto JIT = JIT::create();
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
//    const llvm::DataLayout &DL = (*JIT)->getDataLayout();

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
    (void) Main(argc, argv);

    // report success
    return llvm::Error::success();
}

/**
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

int main(int argc, char *argv[]) {
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


#endif //TINYLANG_JIT_CPP
