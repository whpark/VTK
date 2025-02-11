# Building VTK using emscripten for WebAssembly

## Table of Contents

1. [Introduction](#introduction)
2. [Prerequisites](#prerequisites)
    1. [Get CMake](#get-cmake)
    2. [Get Emscripten SDK](#get-emscripten-sdk)
    3. [Get VTK source code](#get-vtk-source-code)
3. [Build project](#build-project)
4. [Install project](#install-project)
5. [Test with an example](#test-with-an-example)
6. [Guide created using](#guide-created-using)

## Introduction

This page describes how to build and install VTK using [emscripten](https://emscripten.org) on any platform.
These steps can be followed inside a docker container that comes with preinstalled `emsdk` such as
[dockcross/web-wasm](https://hub.docker.com/r/dockcross/web-wasm). In fact, the VTK CI stage `webassembly-build`
uses that container to configure and build VTK wasm.

## Prerequisites

For this guide, you will need the following:

1. CMake [CMake](http://www.cmake.org/) version 3.10 or higher and a working compiler.
2. Emscripten SDK [emsdk](https://github.com/emscripten-core/emsdk) and any dependencies needed by emsdk.
3. The VTK source-code

If you have these then you can skip the rest of this section and proceed to [Build project](#build-project).

### Get CMake

CMake is a tool that makes cross-platform building simple. On several systems it will probably be already installed. If it is not, please use the following instructions to install it.
There are several precompiled binaries available at the [CMake download page](https://cmake.org/download/). Download version 3.12 or later.
Add CMake to your PATH environment variable if you downloaded an archive and not an installer.

### Get Emscripten SDK

Emscripten is a complete compiler toolchain to WebAssembly, using LLVM, with a special focus on speed, size, and the Web platform.
Please download the SDK from [github.com/emscripten-core/emsdk.git](https://github.com/emscripten-core/emsdk) and follow the instructions
in [emsdk/README.md](https://github.com/emscripten-core/emsdk#readme) to get started on Linux, Windows or macOS.

### Get VTK source code

Download VTK source for the version you want from [https://vtk.org/download/](https://vtk.org/download/)  (zip or tar.gz (Do NOT download the exe - this is not the VTK library.) )
You will probably want the latest one (highest version number) unless you have a specific reason to use an older one.

Alternatively the source-code can be obtained from the repository as well. This is recommended only if you intent to make changes and contribute to VTK.
Please refer to [git/develop.md](git/develop.md) for help with `git`.

## Build project

These instructions use a specific convention for the source, build and install directories that is appropriate when building VTK for wasm inside
a docker container. Please replace these _root-directory_ paths if VTK is being built outside a docker container.

1. Configure the project with CMake. `emcmake` tells CMake to use the `emscripten` toolchain for cross compilation.

```bash
$ emcmake cmake \
-S /work/src \
-B /work/build-vtk-wasm \
-GNinja \
-DBUILD_SHARED_LIBS:BOOL=OFF \
-DCMAKE_BUILD_TYPE:STRING=Release \
-DVTK_ENABLE_LOGGING:BOOL=OFF \
-DVTK_ENABLE_WRAPPING:BOOL=OFF \
-DVTK_MODULE_ENABLE_VTK_hdf5:STRING=NO \
-DVTK_MODULE_ENABLE_VTK_RenderingContextOpenGL2:STRING=DONT_WANT \
-DVTK_MODULE_ENABLE_VTK_RenderingLICOpenGL2:STRING=DONT_WANT \
-DVTK_MODULE_ENABLE_VTK_RenderingCellGrid:STRING=NO \
-DVTK_MODULE_ENABLE_VTK_sqlite:STRING=NO \
-DCMAKE_INSTALL_PREFIX=/install
```

2. Compile.
```
$ cd /work/build-vtk-wasm
$ ninja
```

## Install project

1. Install the project.

```
$ cd /work/build-vtk-wasm
$ ninja install
```

The binaries are now installed and you may use `-DVTK_DIR=/work/install/lib/cmake/vtk-9.2` to configure VTK wasm applications with CMake.

## Test with an example

If everything went well then it should now be possible to compile and run the one of the C++ examples.
Head over to [Examples/Emscripten/Cxx/Cone/README.md](https://gitlab.kitware.com/vtk/vtk/-/blob/master/Examples/Emscripten/Cxx/Cone/README.md)
and test the simple Cone example.

## Guide created using

- VTK v9.2.6-2535-gc8cebe56fb
- dockcross/web-wasm:20230222-162287d
