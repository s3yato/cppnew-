cmake_minimum_required(VERSION 3.20)
project(cppnew LANGUAGES CXX)

file(READ "${CMAKE_SOURCE_DIR}/npm/package.json" PACKAGE_JSON)

string(
    JSON CPPNEW_VERSION
    GET "${PACKAGE_JSON}"
    version
)

project(cppnew VERSION ${CPPNEW_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- CLI11 (header-only) через FetchContent ---
include(FetchContent)

FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.4.2
)

FetchContent_MakeAvailable(cli11)

# --- Embedded templates ---
find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(GENERATED_TEMPLATES
    ${CMAKE_CURRENT_BINARY_DIR}/generated_templates.cpp
)

file(GLOB_RECURSE TEMPLATE_FILES
    ${CMAKE_SOURCE_DIR}/templates/*.tmpl
    ${CMAKE_SOURCE_DIR}/templates/*.addon
)

add_custom_command(
    OUTPUT ${GENERATED_TEMPLATES}

    COMMAND
        ${Python3_EXECUTABLE}
        ${CMAKE_SOURCE_DIR}/tools/embed_templates.py
        ${CMAKE_SOURCE_DIR}/templates
        ${GENERATED_TEMPLATES}

    DEPENDS
        ${CMAKE_SOURCE_DIR}/tools/embed_templates.py
        ${TEMPLATE_FILES}
)

# --- Бинарник ---
add_executable(cppnew
    src/main.cpp
    src/generator.cpp
    ${GENERATED_TEMPLATES}
)

target_include_directories(cppnew PRIVATE src)
target_compile_definitions(cppnew PRIVATE
    CPPNEW_VERSION="${PROJECT_VERSION}"
)
target_link_libraries(cppnew PRIVATE CLI11::CLI11)

# --- Установка ---
install(TARGETS cppnew RUNTIME DESTINATION bin)
