# Runtime
Developing this for my own understanding on how runtime are built from scratch. Most of this will be inspired by compute shaders and [IREE runtime drivers like `local-task`](https://github.com/iree-org/iree).

## Build
```bash
mkdir build
cd build

cmake ..

cmake --build .

./runner
```

## Tests
This project uses **CTest** for unit testing.
```bash
ctest
```

## Debug
You can replace the standard system `malloc`/`free` with a Debug Allocator that logs all memory operations to `stdout`.
To enable it, configure CMake with the `RUNTIME_USE_DEBUG_ALLOCATOR` flag:
```bash
cmake -DRUNTIME_USE_DEBUG_ALLOCATOR=ON ..

cmake --build .
```
