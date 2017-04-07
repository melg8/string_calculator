file (GLOB_RECURSE ALL_KEY_NOTES_LIB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file (GLOB_RECURSE ALL_KEY_NOTES_LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

add_library (string_calculator STATIC
             "${ALL_KEY_NOTES_LIB_HEADERS}"
             "${ALL_KEY_NOTES_LIB_SOURCES}")

header_directories (ALL_STRING_CALCULATOR_LIB_INCLUDE_DIRECTORIES)

target_include_directories (string_calculator PUBLIC
                            "${ALL_STRING_CALCULATOR_LIB_INCLUDE_DIRECTORIES}")
