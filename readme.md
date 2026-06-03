# Math

A lightweight C++17 linear algebra library focused on 2D/3D/4D math for graphics and simulation use cases.

## What is included

The library is implemented in `src/Math3d.h/.cpp` and provides:

- `matriz_2x2`, `matriz_3x3`, `matriz_4x4`, `matriz_mxn`
- `vector2`, `vector3`, `vector4` (`vector4` is an alias for `cuaternion`)
- `cuaternion` (quaternion math)
- Common operations: add/subtract/multiply, transpose, determinant, inverse, normalization
- Transform/projection helpers for 4x4 matrices (translation, rotation, scale, orthographic/perspective)

## Requirements

- CMake 3.22+
- A C++17 compatible compiler

## Build and test

From the repository root:

```bash
./cmakew -t .
```

`cmakew` configures and builds in the `build/` directory and runs the CTest suite.

## Using the library in your CMake project

This repository builds a static library target named `math`.

```cmake
add_subdirectory(path/to/math)
target_link_libraries(your_target PRIVATE math)
```

Then include the main header:

```cpp
#include "Math3d.h"
```

## Running tests directly

If you already configured the project, you can run tests from the build directory:

```bash
ctest --output-on-failure
```

## Repository layout

- `src/` — library source code
- `test/` — Catch2-based unit tests
- `cmakew` — helper script to configure/build/test quickly
