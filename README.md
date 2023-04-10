
Test Game / Konkyo
===================

![C/C++ CI](https://github.com/bakana808/konkyo/workflows/C/C++%20CI/badge.svg)

This project contains both a WIP game framework (nicknamed Konkyo), and a runnable test game application using the framework.

[Konkyo overview/design doc](./design.md)

## Building

### Prerequisites
- [SFML](https://github.com/SFML/SFML)
- Python
- SCons (`pip install scons`)

### Compiling
1. In the project directory, run `scons` in the terminal.

### Cleaning
1. In the project directory, run `scons -c` in the terminal.

This will build an executable named "game".