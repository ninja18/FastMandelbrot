### Fast Mandelbrot set visualisation
This Mandelbrot set is a start point to test the learnings from OpenMP and a high level, easy to use graphical library in C/C++ with SDL2.

### Setup
- setup vcpkg package manager in `$HOME`.
- run `mkdir build && cd build`
- run `cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake ..` and `cmake --build .` to build.

### Observations

| Time(s) | Parameters                              | Implementation                                                                     |
|---------|-----------------------------------------|------------------------------------------------------------------------------------|
| 1.58754 | step size = 0.001, it = 250, limit = 10 | naive loop, draw points in loop and use std::complex and other std math functions. | 

