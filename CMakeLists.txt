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

include_directories(BEFORE
        ${CMAKE_CURRENT_BINARY_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

add_subdirectory(lib)
add_subdirectory(tools)









