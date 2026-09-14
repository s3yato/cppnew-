cmake_minimum_required(VERSION 3.20)
project(cppnew VERSION 0.1.0 LANGUAGES CXX)

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

# --- Бинарник ---
add_executable(cppnew
    src/main.cpp
    src/generator.cpp
)

target_include_directories(cppnew PRIVATE src)
target_link_libraries(cppnew PRIVATE CLI11::CLI11)

# --- Путь к шаблонам передаём в код через макрос ---
target_compile_definitions(cppnew PRIVATE
    CPPNEW_TEMPLATES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/templates"
)

# --- Установка: cppnew попадёт в /usr/local/bin ---
install(TARGETS cppnew RUNTIME DESTINATION bin)