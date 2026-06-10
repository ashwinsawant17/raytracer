# A Raytracer for Windows in C++ using SDL3 and STB

It's built with CMake, and compiled with msvc
```
cmake -B build
cmake --build build
```

Optionally, my preferred method is to use Ninja Multi-Config to have Debug and Release profiles
```
cmake -G "Ninja Multi-Config" -B build
```

When building, you can specify the profile, or just default to Debug
```
cmake --build build --config Release
cmake --build build --config Debug
```

Those steps are optional, though. It should be relatively platform/compiler agnostic. There shouldn't be any windows specific APIs, and SDL3 allows for portability