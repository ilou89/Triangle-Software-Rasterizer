# Bresenham-Line-Drawing-Algorithm
Implementation of Bresenham's Line Drawing Algorithm in C++.
Line drawing is one of the few primitive functions that lie 
at the heart of most graphics software and here is my implementation
of such a function heavily inspired by the implementation on 
[Graphics Programming Black Book](https://www.amazon.com/Michael-Abrashs-Graphics-Programming-Special/dp/1576101746).
In addition a BMP image creator is implemented in order to
visualize the results of the algorithm.

## Usage
```bash
make
./drawlines
```

A lines.bmp file will be created which you can load with a BMP loader and see the results of the algorithm.
