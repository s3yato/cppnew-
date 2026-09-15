#pragma once

#include <cstddef>
#include <string_view>

namespace cppnew {

struct EmbeddedTemplate {
    std::string_view path;
    std::string_view content;
};

extern const EmbeddedTemplate templates[];
extern const std::size_t template_count;

std::string_view get_template(std::string_view path);

}