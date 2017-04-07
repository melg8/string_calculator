header_directories (ALL_STRING_CALCULATOR_TESTS_HEADERS_DIRECTORIES)
include_directories ("${ALL_STRING_CALCULATOR_TESTS_HEADERS_DIRECTORIES}")

file (GLOB_RECURSE ALL_STRING_CALCULATOR_TESTS_APPLICATION_HEADERS
                   "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

file (GLOB_RECURSE ALL_STRING_CALCULATOR_TESTS_APPLICATION_SOURCES
                   "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

add_executable (string_calculator_tests
                "${ALL_STRING_CALCULATOR_TESTS_APPLICATION_HEADERS}"
                "${ALL_STRING_CALCULATOR_TESTS_APPLICATION_SOURCES}")

target_link_libraries (string_calculator_tests string_calculator)

add_test (string_calculator_tests string_calculator_tests)
