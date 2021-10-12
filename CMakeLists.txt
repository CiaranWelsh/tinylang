cmake_minimum_required(VERSION 3.20)
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(tinylang)

    set(CMAKE_CXX_STANDARD 20)

    find_package(LLVM CONFIG REQUIRED)

    list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
    include(HandleLLVMOptions)
    add_definitions(${LLVM_DEFINITIONS})

    if (WIN32)
        include(ChooseMSVCCRT)
    endif ()
    include(AddLLVM)
    include(HandleLLVMOptions)
    include_directories(
            "${LLVM_BINARY_DIR}/include"
            "${LLVM_INCLUDE_DIR}"
    )
    link_directories("${LLVM_LIBRARY_DIR}")
    set(TINYLANG_BUILT_STANDALONE ON)
endif (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

list(APPEND CMAKE_MODULE_PATH
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE)
    message(FATAL_ERROR "In-source builds are not allowed.")
endif ()


set(TINYLANG_VERSION_STRING "0.1")
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/include/tinylang/Basic/Version.inc.in
        ${CMAKE_CURRENT_BINARY_DIR}/include/tinylang/Basic/Version.inc
)

include(AddTinylang)

set(TINYLANG_BINARY_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include")
set(TINYLANG_SOURCE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
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


message(STATUS "
Configuration Summary
---------------------

Tinylang Variables:
    TINYLANG_BINARY_INCLUDE_DIR      ${TINYLANG_BINARY_INCLUDE_DIR}
    TINYLANG_SOURCE_INCLUDE_DIR      ${TINYLANG_SOURCE_INCLUDE_DIR}
    TINYLANG_INCLUDE_DIR             ${TINYLANG_INCLUDE_DIR}

LLVM Variables:
    LLVM_DEFINITIONS                 ${LLVM_DEFINITIONS}
    LLVM_INCLUDE_DIR                 ${LLVM_INCLUDE_DIR}
    LLVM_LIBRARY_DIR                 ${LLVM_LIBRARY_DIR}
    LLVM_LIBRARIES                   ${LLVM_LIBRARIES}

LLVM Variables:
    LLVM_CMAKE_DIR                   ${LLVM_CMAKE_DIR}
    LLVM_DEFINITIONS                 ${LLVM_DEFINITIONS}
    LLVM_ENABLE_ASSERTIONS           ${LLVM_ENABLE_ASSERTIONS}
    LLVM_ENABLE_EH                   ${LLVM_ENABLE_EH}
    LLVM_ENABLE_RTTI                 ${LLVM_ENABLE_RTTI}
    LLVM_INCLUDE_DIRS                ${LLVM_INCLUDE_DIRS}
    LLVM_PACKAGE_VERSION             ${LLVM_PACKAGE_VERSION}
    LLVM_TOOLS_BINARY_DIR            ${LLVM_TOOLS_BINARY_DIR}
")








