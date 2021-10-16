add_tinylang_library(
        tinylangBasic
        Version.cpp
        Lexer.cpp
        Parser.cpp
        Sema.cpp
        CodeGen.cpp
)

target_link_libraries(tinylangBasic PUBLIC ${llvm_libs})
