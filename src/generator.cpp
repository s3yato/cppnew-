#include "generator.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace fs = std::filesystem;

#ifndef CPPNEW_TEMPLATES_DIR
#error "CPPNEW_TEMPLATES_DIR is not defined"
#endif

static std::string read_file(const fs::path& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot read " + path.string());
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

static void write_file(const fs::path& path, const std::string& content) {
    fs::create_directories(path.parent_path());
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot write " + path.string());
    out << content;
}

static std::string render(std::string text, const std::string& name) {
    const std::string placeholder = "{{NAME}}";
    size_t pos;
    while ((pos = text.find(placeholder)) != std::string::npos) {
        text.replace(pos, placeholder.size(), name);
    }
    return text;
}

static void apply_addon(const fs::path& target,
    const fs::path& addon,
    const std::string& name)
{
if (!fs::exists(addon)) return;  
if (!fs::exists(target)) return; 

std::string existing = read_file(target);
std::string addition = render(read_file(addon), name);

write_file(target, existing + addition);
}

static std::string strip_tmpl(const std::string& s) {
    const std::string suffix = ".tmpl";
    if (s.size() >= suffix.size() &&
        s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0) {
        return s.substr(0, s.size() - suffix.size());
    }
    return s;
}

static void copy_template_dir(const fs::path& src_dir,
                              const fs::path& dst_dir,
                              const std::string& name)
{
    for (const auto& entry : fs::recursive_directory_iterator(src_dir)) {
        if (!entry.is_regular_file()) continue;

        fs::path rel = fs::relative(entry.path(), src_dir);
        std::string rel_str = strip_tmpl(rel.string());
        rel_str = render(rel_str, name);

        fs::path dst_path = dst_dir / rel_str;
        std::string content = render(read_file(entry.path()), name);
        write_file(dst_path, content);
    }
}

void generate_project(const Options& opts) {
    fs::path root = opts.name;

    if (fs::exists(root)) {
        throw std::runtime_error("Directory already exists: " + root.string());
    }

    fs::path templates_root = CPPNEW_TEMPLATES_DIR;
    fs::path template_dir = templates_root / (opts.is_lib ? "lib" : "app");

    if (!fs::exists(template_dir)) {
        throw std::runtime_error("Template not found: " + template_dir.string());
    }

    fs::create_directories(root);

    copy_template_dir(template_dir, root, opts.name);
    copy_template_dir(templates_root / "common", root, opts.name);

    std::cerr << "[DEBUG] with_tests = " << opts.with_tests << "\n";

    if (opts.with_tests) {
        fs::path addon = templates_root / "tests" / "addons" / "CMakeLists.txt.addon";
        std::cerr << "[DEBUG] addon path    = " << addon << "\n";
        std::cerr << "[DEBUG] addon exists  = " << fs::exists(addon) << "\n";

        copy_template_dir(templates_root / "tests" / "files", root, opts.name);
        apply_addon(root / "CMakeLists.txt", addon, opts.name);
    }

    std::cout << "Created project: " << opts.name << "\n";
}