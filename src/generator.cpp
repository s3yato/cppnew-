#include "generator.hpp"
#include "embedded_templates.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>

namespace fs = std::filesystem;

static void validate_project_name(const std::string& name) {
    if (name.empty()) {
        throw std::runtime_error(
            "Project name cannot be empty"
        );
    }

    if (!std::isalpha(static_cast<unsigned char>(name[0]))) {
        throw std::runtime_error(
            "Project name must start with a letter"
        );
    }

    for (char c : name) {
        if (!std::isalnum(static_cast<unsigned char>(c)) &&
            c != '-' &&
            c != '_') {
            throw std::runtime_error(
                "Project name may contain only letters, digits, '-' and '_'"
            );
        }
    }
}

std::string_view cppnew::get_template(std::string_view path) {
    for (std::size_t i = 0; i < cppnew::template_count; ++i) {
        if (cppnew::templates[i].path == path) {
            return cppnew::templates[i].content;
        }
    }

    throw std::runtime_error(
        "Template not found: " + std::string(path)
    );
}

static void write_file(const fs::path& path, const std::string& content) {
    fs::create_directories(path.parent_path());
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot write " + path.string());
    out << content;
}

static std::string render(
    std::string text,
    const std::string& name
) {
    const std::string name_placeholder = "{{NAME}}";

    size_t pos;
    while ((pos = text.find(name_placeholder)) != std::string::npos) {
        text.replace(pos, name_placeholder.size(), name);
    }

    std::string namespace_name = name;

    for (char& c : namespace_name) {
        if (c == '-') {
            c = '_';
        }
    }

    const std::string namespace_placeholder = "{{NAMESPACE}}";

    while ((pos = text.find(namespace_placeholder)) != std::string::npos) {
        text.replace(
            pos,
            namespace_placeholder.size(),
            namespace_name
        );
    }

    return text;
}

static void apply_addon(const fs::path& target,
    const std::string& addon_path,
    const std::string& name)
{
if (!fs::exists(target)) return;

std::string existing;

{
std::ifstream in(target, std::ios::binary);
if (!in) {
throw std::runtime_error(
"Cannot read " + target.string()
);
}

std::ostringstream ss;
ss << in.rdbuf();
existing = ss.str();
}

std::string addition = render(
std::string(cppnew::get_template(addon_path)),
name
);

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

static void copy_embedded_templates(const std::string& prefix,
    const fs::path& dst_dir,
    const std::string& name)
{
    const std::string full_prefix = prefix + "/";

    for (std::size_t i = 0; i < cppnew::template_count; ++i) {
        const auto& tmpl = cppnew::templates[i];

        if (!tmpl.path.starts_with(full_prefix)) {
            continue;
        }

        std::string rel = std::string(
            tmpl.path.substr(full_prefix.size())
        );

        rel = strip_tmpl(rel);
        rel = render(rel, name);

        fs::path dst_path = dst_dir / rel;

        std::string content = render(
            std::string(tmpl.content),
            name
        );

        write_file(dst_path, content);
    }
}

void generate_project(const Options& opts) {
    validate_project_name(opts.name);
    fs::path root = opts.name;

    if (fs::exists(root)) {
        throw std::runtime_error(
            "Directory already exists: " + root.string()
        );
    }

    fs::create_directories(root);

    const std::string prefix = opts.is_lib ? "lib" : "app";

    copy_embedded_templates(prefix, root, opts.name);
    copy_embedded_templates("common", root, opts.name);

    if (opts.with_tests) {
        copy_embedded_templates("tests/files", root, opts.name);

        apply_addon(
            root / "CMakeLists.txt",
            "tests/addons/CMakeLists.txt.addon",
            opts.name
        );
    }

    std::cout << "Created project: " << opts.name << "\n";
}