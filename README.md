# 3D Engines Assignment

This project consists in a framework made with OpenGL in C++23. Currently, it supports:
* 2D and 3D mathematic operations
* opening a window and capturing key and mouse events
* 3D FPS camera
* rendering objects in real-time
* loading textured meshes from files
* Phong lighting
* importing and exporting JSON scenes
* bounding sphere frustum culling
* fully functional transform hierarchy

## Requirements
cmake >= 3.27
g++ >= 15
msvc >= 19.42

## Building
```console
$ cmake -Bbuild -H.
$ cmake --build build
```

## Running
build/MG3TR

**Note**: Some Assimp Windows binaries are included. They may not link
since they are dependent on the Visual Studio version used and should be
compiled on the host beforehand.