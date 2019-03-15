#include "bitmap.h"
#include "simpleBresenham.h"
#include "integerBresenham.h"
#include "sliceBresenham.h"
#include <iostream>
#include <chrono>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main() {

    Bitmap bitmap(WIDTH, HEIGHT);
    //SimpleBresenham simpleBresenham(bitmap);
    IntegerBresenham simpleBresenham(bitmap);

    auto start = std::chrono::system_clock::now();
    for(uint32_t i = 0; i < 1000000; i++) {
        simpleBresenham.drawLines();
    }
    auto end = chrono::system_clock::now();
    auto elapsed =
    chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Elapsed milliseconds:" << elapsed.count() << endl;

    bitmap.write("lines.bmp");

    return 0;
}

