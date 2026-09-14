# cppnew

<p align="center">
  <strong>A modern project bootstrapper for C++.</strong>
</p>

<p align="center">
  Create clean, structured C++ projects in seconds.
</p>

<p align="center">
  <a href="https://github.com/s3yato/cppnew">GitHub</a>
  ·
  <a href="https://github.com/s3yato/cppnew/issues">Issues</a>
  ·
  <a href="https://github.com/s3yato/cppnew/releases">Releases</a>
</p>

<p align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-blue)
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

## Quick Start

### Create an application

```bash
cppnew new my-project
```

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

Run:

```bash
./build/my-project
```

---

## Create a library

```bash
cppnew new my-library --lib
```

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

---

## Add tests

Need a project with GoogleTest?

```bash
cppnew new my-project --tests
```

Then:

```bash
cd my-project

cmake -S . -B build
cmake --build build
ctest --test-dir build
```

```text
100% tests passed
```

---

## Installation

### npm

```bash
npm install -g cppnew
```

Verify the installation:

```bash
cppnew --version
```

### From source

Clone the repository:

```bash
git clone https://github.com/s3yato/cppnew.git
cd cppnew
```

Configure and build:

```bash
cmake -S . -B build
cmake --build build
```

Install:

```bash
sudo cmake --install build
```

---

## Commands

### `cppnew new`

Create a new C++ application:

```bash
cppnew new <name>
```

### `cppnew new --lib`

Create a C++ library:

```bash
cppnew new <name> --lib
```

### `cppnew new --tests`

Create a project with GoogleTest:

```bash
cppnew new <name> --tests
```

Options can be combined:

```bash
cppnew new robot-simulator --tests
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

## What does cppnew generate?

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

### With tests

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

## Design goals

### Simple

One command should be enough to start.

### Predictable

Generated projects should be understandable by any C++ developer.

### Modern

CMake, testing and a clean project structure from the beginning.

### Lightweight

No large framework. No configuration required.

### Extensible

The template system is designed to support additional project types and generators over time.

---

## Project architecture

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

The goal is to keep the CLI, generation logic and templates separated so new project types can be added without rewriting the core.

---

## Roadmap

### v0.1

* [x] C++ application generation
* [x] Library generation
* [x] GoogleTest integration
* [x] CMake project generation
* [x] CLI help
* [x] Version command
* [ ] npm distribution
* [ ] GitHub Release

### Future

* [ ] `cppnew init`
* [ ] Additional project templates
* [ ] Project configuration
* [ ] Package manager integration
* [ ] More testing presets
* [ ] Cross-platform binary distribution

---

## Contributing

Contributions are welcome.

If you have an idea, find a bug, or want to improve a template, open an issue or submit a pull request.

```bash
git clone https://github.com/YOUR_USERNAME/cppnew.git
cd cppnew

cmake -S . -B build
cmake --build build
```

---

## License

MIT © 2026 [YOUR_USERNAME](https://github.com/YOUR_USERNAME)

---

<p align="center">
  <strong>Start writing C++, not boilerplate.</strong>
</p>

<p align="center">
  <code>cppnew new my-project</code>
</p>
