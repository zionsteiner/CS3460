cmake_minimum_required(VERSION 3.10)
project(ConwaysLife)

# File vars
set(SOURCE_FILES LifeSimulator.cpp RendererConsole.cpp PatternAcorn.cpp PatternBlinker.cpp PatternBlock.cpp PatternGlider.cpp PatternGosperGliderGun.cpp)
set(HEADER_FILES LifeSimulator.hpp RendererConsole.hpp Renderer.hpp Pattern.hpp PatternAcorn.hpp PatternBlinker.hpp PatternBlock.hpp PatternGlider.hpp PatternGosperGliderGun.hpp)

# Executables
add_executable(ConwaysLife ${HEADER_FILES} ${SOURCE_FILES} main.cpp)

# Set to CXX17
set_property(TARGET ConwaysLife PROPERTY CXX_STANDARD 17)

# Enable compiler-specific options
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(ConwaysLife PRIVATE /W4 /permissive-)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ConwaysLife PRIVATE -Wall -Wextra -pedantic)
endif()

# Auto-format
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    message("FORMATTED")
    unset(SOURCE_FILES_PATHS)
    foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES} main.cpp)
        get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()

    add_custom_target(
            ClangFormat
            COMMAND ${CLANG_FORMAT}
            -i
            -style=file
            ${SOURCE_FILES_PATHS})

    add_dependencies(ConwaysLife ClangFormat)

else()
    message("NO FORMAT")

endif()
