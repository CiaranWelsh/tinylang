cmake_minimum_required(VERSION 3.20)



if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(tinylang)

    set(CMAKE_CXX_STANDARD 20)

    find_package(LLVM CONFIG REQUIRED HINTS "D:/llvm-project/install-llvm-rel")

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

list(APPEND CMAKE_MODULE_PATH "cmake/modules")

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE)
    message(FATAL_ERROR "In-source builds are not allowed.")
endif ()

add_subdirectory(Chapter10JITMyself)

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








