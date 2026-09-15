# cppnew

<p align="center">
  <strong>A modern project bootstrapper for C++.</strong>
</p>

<p align="center">
  Create clean, structured C++ projects in seconds.
</p>

<p align="center">
  <a href="https://github.com/s3yato/cppnew-">GitHub</a>
  ·
  <a href="https://github.com/s3yato/cppnew-/issues">Issues</a>
  ·
  <a href="https://github.com/s3yato/cppnew-/releases">Releases</a>
</p>

<p align="center">

![C++](https://img.shields.io/badge/C%2B%2B-20%2B-blue)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-green)
![License](https://img.shields.io/badge/license-MIT-black)

</p>

---

## Why cppnew?

Starting a new C++ project often means creating the same boilerplate over and over:

* `CMakeLists.txt`
* source directories
* headers
* `.gitignore`
* tests
* basic project structure

**cppnew** gives you a clean starting point with a single command.

```bash
cppnew new my-project
```

That's it.

---

## Installation

### npm

The easiest way to install `cppnew` is through npm:

```bash
npm install -g cppnew
```

Verify the installation:

```bash
cppnew --version
```

Example:

```text
cppnew 0.1.6
```

Prebuilt binaries are currently distributed for:

* macOS ARM64
* Linux x64
* Windows x64

### From source

Clone the repository:

```bash
git clone https://github.com/s3yato/cppnew-.git
cd cppnew-
```

Configure and build:

```bash
cmake -S . -B build
cmake --build build
```

The resulting binary will be located in:

```text
build/cppnew
```

---

## Quick Start

Create a new application:

```bash
cppnew new my-project
```

This generates:

```text
my-project/
├── CMakeLists.txt
├── README.md
├── .gitignore
└── src/
    └── main.cpp
```

Build it:

```bash
cd my-project

cmake -S . -B build
cmake --build build
```

Run it:

```bash
./build/my-project
```

---

## Create a Library

Create a C++ library:

```bash
cppnew new my-library --lib
```

Generated structure:

```text
my-library/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── include/
│   └── my-library/
│       └── my-library.hpp
└── src/
    └── my-library.cpp
```

The generated library uses a standard CMake structure with public headers separated from implementation files.

---

## Add Tests

Create a project with GoogleTest:

```bash
cppnew new my-project --tests
```

Then build and run the tests:

```bash
cd my-project

cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Example output:

```text
100% tests passed
```

GoogleTest is automatically configured through CMake.

---

## Commands

### Create an application

```bash
cppnew new <name>
```

Example:

```bash
cppnew new robot-simulator
```

### Create a library

```bash
cppnew new <name> --lib
```

Example:

```bash
cppnew new robotics-core --lib
```

### Create a project with tests

```bash
cppnew new <name> --tests
```

Example:

```bash
cppnew new robot-simulator --tests
```

Options can be combined:

```bash
cppnew new robotics-core --lib --tests
```

### Help

```bash
cppnew --help
```

### Version

```bash
cppnew --version
```

---

## What Does cppnew Generate?

`cppnew` is intentionally simple.

It generates projects around a predictable CMake structure instead of trying to hide the build system from you.

### Application

```text
my-project/
├── CMakeLists.txt
├── README.md
├── .gitignore
└── src/
    └── main.cpp
```

### Library

```text
my-library/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── include/
│   └── my-library/
│       └── my-library.hpp
└── src/
    └── my-library.cpp
```

### Application with Tests

```text
my-project/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── src/
│   └── main.cpp
└── tests/
    └── example_test.cpp
```

---

## Design Goals

### Simple

One command should be enough to start a project.

### Predictable

Generated projects should be understandable by any C++ developer.

### Modern

Use modern C++, CMake and testing from the beginning.

### Lightweight

No large framework. No complicated configuration.

### Extensible

The template system is designed to support additional project types and generators over time.

---

## Project Architecture

`cppnew` itself is written in modern C++.

```text
cppnew
│
├── CLI
│   └── command parsing
│
├── Generator
│   ├── template loading
│   ├── template rendering
│   ├── file generation
│   └── addons
│
└── Templates
    ├── app
    ├── lib
    ├── tests
    └── common
```

The CLI, generation logic and templates are separated so new project types can be added without rewriting the core.

Templates are embedded into the distributed binary, so the installed `cppnew` executable does not depend on a separate templates directory.

---

## Roadmap

### v0.1

* [x] C++ application generation
* [x] Library generation
* [x] GoogleTest integration
* [x] CMake project generation
* [x] CLI help
* [x] Version command
* [x] npm distribution
* [x] GitHub Releases
* [x] Cross-platform binary distribution

### Future

* [ ] `cppnew init`
* [ ] Additional project templates
* [ ] Project configuration
* [ ] Package manager integration
* [ ] More testing presets
* [ ] Improved generator system
* [ ] Additional platform support

---

## Contributing

Contributions are welcome.

If you have an idea, find a bug, or want to improve a template, open an issue or submit a pull request.

Clone the repository:

```bash
git clone https://github.com/s3yato/cppnew-.git
cd cppnew-
```

Build:

```bash
cmake -S . -B build
cmake --build build
```

---

## License

MIT © 2026 Egor Sukharnikov

---

<p align="center">
  <strong>Start writing C++, not boilerplate.</strong>
</p>

<p align="center">
  <code>cppnew new my-project</code>
</p>
