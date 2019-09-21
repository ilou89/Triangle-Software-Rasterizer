[![Build Status](https://travis-ci.com/ilou89/Triangle-Software-Rasterizer.svg?branch=master)](https://travis-ci.com/ilou89/Triangle-Software-Rasterizer)

# Triangle-Software-Rasterizer
This repo is an attempt to create a triangle software rasterizer.
Creating a rasterizer is usually the recommended way for beginners to be introduced to concepts of computer graphics instead of figuring them out using complex modern graphics APIs like Vulkan and OpenGL.
The rasterization is a pretty simple algorithm and operates like this: for every triangle we want to draw we figure out which pixels this triagle covers and then we paint each such pixel with a specific color. No light interaction is implemented yet.
Software rasterization, simply means that we are doing the rasterization on the CPU, instead of the GPU.

There are two rasterizer implementations, a) scanline method and b) barycentric method.
The scanline method uses Bresenham's Line Drawing Algorithm for line drawing.
Line drawing is one of the few primitive functions that lie 
at the heart of most graphics software and my implementation
of such a function is heavily inspired by the implementation on 
[Graphics Programming Black Book](https://www.amazon.com/Michael-Abrashs-Graphics-Programming-Special/dp/1576101746).
In addition a BMP image creator is implemented in order to
visualize the results of the algorithm.

## Usage
```bash
mkdir build
cd build
cmake ..
make
./drawlines
```

A lines.bmp file will be created which you can load with a BMP loader and see the results of the algorithm.
