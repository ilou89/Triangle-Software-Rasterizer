#include "bitmap.h"
#include "simpleBresenham.h"
#include "integerBresenham.h"
#include "sliceBresenham.h"
#include "modelLoader.h"
#include <iostream>
#include <chrono>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main() {

    Bitmap bitmap(WIDTH, HEIGHT);
    //SimpleBresenham simpleBresenham(bitmap);
    IntegerBresenham simpleBresenham(bitmap);
    //SliceBresenham simpleBresenham(bitmap);

    auto start = std::chrono::system_clock::now();
    for(uint32_t i = 0; i < 1000000; i++) {
        simpleBresenham.drawLines();
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed =
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed milliseconds:" << elapsed.count() << std::endl;

    bitmap.write("lines.bmp");

    return 0;
}

