from pathlib import Path
import sys


def escape_cpp_string(value: str) -> str:
    return (
        value
        .replace("\\", "\\\\")
        .replace('"', '\\"')
        .replace("\n", "\\n")
        .replace("\r", "\\r")
    )


def main():
    templates_dir = Path(sys.argv[1])
    output_file = Path(sys.argv[2])

    templates = []

    for path in sorted(
        list(templates_dir.rglob("*.tmpl")) +
        list(templates_dir.rglob("*.addon"))
    ):
        relative_path = path.relative_to(templates_dir).as_posix()
        content = path.read_text()

        templates.append((relative_path, content))

    with output_file.open("w") as out:
        out.write('#include "embedded_templates.hpp"\n')
        out.write("#include <string_view>\n")
        out.write("\n")
        out.write("namespace cppnew {\n")
        out.write("\n")
        out.write("const EmbeddedTemplate templates[] = {\n")

        for relative_path, content in templates:
            escaped_path = escape_cpp_string(relative_path)
            escaped_content = escape_cpp_string(content)

            out.write(
                f'    {{"{escaped_path}", "{escaped_content}"}},\n'
            )

        out.write("};\n")
        out.write("\n")
        out.write(
            "const std::size_t template_count = "
            "sizeof(templates) / sizeof(templates[0]);\n"
        )
        out.write("\n")
        out.write("}\n")


if __name__ == "__main__":
    main()