#include <CLI/CLI.hpp>
#include <iostream>

#include "generator.hpp"

int main(int argc, char** argv) {
    CLI::App app{"cargo new for C++"};
    app.set_version_flag("--version", "cppnew " CPPNEW_VERSION);

    auto* new_cmd = app.add_subcommand("new", "Create a new project");
    std::string new_name;
    new_cmd->add_option("name", new_name)->required();

    bool new_lib = false;
    new_cmd->add_flag("--lib", new_lib);

    bool new_tests = false;
    new_cmd->add_flag("--tests", new_tests, "Add GoogleTest");

    auto* gen_cmd = app.add_subcommand("generate", "Generate a class, test, etc.");
    gen_cmd->alias("g");


    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }
    if(*new_cmd) {
        Options opts{new_name, new_lib, new_tests};
        try {
            generate_project(opts);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    }
    if(*gen_cmd) {
        std::cerr << "generate: not implemented yet\n";
        return 1;
    }

    return 0;
}