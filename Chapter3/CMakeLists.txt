
set(TINYLANG_VERSION_STRING "0.1")
configure_file(
        include/tinylang/Basic/Version.inc.in
        ${CMAKE_CURRENT_BINARY_DIR}/include/tinylang/Basic/Version.inc
)

include(AddTinylang)

set(TINYLANG_BINARY_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include")
set(TINYLANG_SOURCE_INCLUDE_DIR "include")
set(TINYLANG_INCLUDE_DIR
        "${TINYLANG_BINARY_INCLUDE_DIR}"
        "${TINYLANG_SOURCE_INCLUDE_DIR}"
        )

# Available components:
#    ./llvm-config --components
#  aggressiveinstcombine all all-targets analysis asmparser asmprinter binaryformat
#  bitreader bitstreamreader bitwriter cfguard codegen core coroutines coverage
#  debuginfocodeview debuginfodwarf debuginfogsym debuginfomsf debuginfopdb
#  demangle dlltooldriver dwarflinker engine executionengine extensions
#  filecheck frontendopenacc frontendopenmp fuzzmutate globalisel hellonew
#  instcombine instrumentation interfacestub interpreter ipo irreader
#  jitlink libdriver lineeditor linker lto mc mca mcdisassembler mcjit
#  mcparser mirparser native nativecodegen objcarcopts object objectyaml
#  option orcjit orcshared orctargetprocess passes profiledata remarks
#  runtimedyld scalaropts selectiondag support symbolize tablegen target
#  textapi transformutils vectorize windowsmanifest x86 x86asmparser
#  x86codegen x86desc x86disassembler x86info xray
llvm_map_components_to_libnames(llvm_libs support core irreader)


include_directories(BEFORE
        "${TINYLANG_BINARY_INCLUDE_DIR}"
        "${TINYLANG_SOURCE_INCLUDE_DIR}"
        )


add_subdirectory(lib)
add_subdirectory(tools)
add_subdirectory(test)

