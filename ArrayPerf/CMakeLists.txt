cmake_minimum_required(VERSION 3.10)
project(ArrayPerformance)

# File vars
set(SOURCE_FILES sortutils.cpp)
set(HEADER_FILES sortutils.hpp)
set(UNIT_TEST_FILES TestPerformance.cpp)

# Executables
add_executable(ArrayPerformance ${HEADER_FILES} ${SOURCE_FILES} main.cpp)
add_executable(UnitTestRunner ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES})

# Set to CXX17
set_property(TARGET ArrayPerformance PROPERTY CXX_STANDARD 17)
set_property(TARGET UnitTestRunner PROPERTY CXX_STANDARD 17)

# Enable compiler-specific options
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(ArrayPerformance PRIVATE /W4 /permissive-)
    set_target_properties(ArrayPerformance PROPERTIES LINK_FLAGS "/STACK:10000000")
    target_compile_options(UnitTestRunner PRIVATE /W4 /permissive-)
    set_target_properties(UnitTestRunner PROPERTIES LINK_FLAGS "/STACK:10000000")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ArrayPerformance PRIVATE -Wall -Wextra -pedantic -Wl,--stack,1000000 -O3)
    target_compile_options(UnitTestRunner PRIVATE -Wall -Wextra -pedantic)
endif()

# Auto-format
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    message("FORMATTED")
    unset(SOURCE_FILES_PATHS)
    foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES} ${UNIT_TEST_FILES} main.cpp)
        get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()

    add_custom_target(
            ClangFormat
            COMMAND ${CLANG_FORMAT}
            -i
            -style=file
            ${SOURCE_FILES_PATHS})

    add_dependencies(ArrayPerformance ClangFormat)

else()
    message("NO FORMAT")

endif()

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

# Clone googletest
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

# Build googletest
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest to build. This defines the gtest and gtest_main targets
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Link against gtest static libraries
target_link_libraries(UnitTestRunner gtest_main)