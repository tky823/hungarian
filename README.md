## Build

Run these commands from the project root．CMake and a C++17 compatible compiler are required．

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Run

```sh
./build/benchmark_hungarian
```
