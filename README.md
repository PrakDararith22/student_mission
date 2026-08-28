# mission

## Requirements

- GCC (or any C17-compatible compiler)
- CMake 3.16+

## Build & Run

```sh
make        # build (debug)
make run    # build and run
make clean  # remove build artifacts
make release  # build with -O2 optimizations
```

## Project Structure

```
mission/
├── CMakeLists.txt
├── Makefile
├── include/
└── src/
    └── main.c
```

Add `.h` files to `include/` and `.c` files to `src/`. CMake picks them up automatically.
