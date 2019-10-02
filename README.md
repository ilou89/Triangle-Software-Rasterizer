[![Build Status](https://travis-ci.com/ilou89/Triangle-Software-Rasterizer.svg?branch=master)](https://travis-ci.com/ilou89/Triangle-Software-Rasterizer)

# Triangle-Software-Rasterizer

Fork from [kalexio's](https://github.com/kalexio) [Triangle Software Rasterizer](https://github.com/kalexio/Triangle-Software-Rasterizer). 

This repo is used for experimenting modern C++ features (smart pointers, lambda expressions, STL containers and algorithms, design patterns etc), rasterization algorithms and CI (Travis integration). 
It is not intended to create rasterizer implementation with respect to performance efficiency; the algorithms implemented can be optimized by tuning the respective implementations. 

## Usage
```bash
mkdir build
cd build
cmake ..
make
./drawlines
```

A lines.bmp file will be created which you can load with a BMP loader and see the results of the algorithm.
