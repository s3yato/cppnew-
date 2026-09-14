#pragma once
#include <string>

struct Options {
    std::string name;
    bool is_lib = false;
    bool with_tests = false;
    bool with_ci = false;
};

void generate_project(const Options& opts); 