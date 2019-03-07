#include "bmpImage.h"
#include "bresenham.h"
#include <iostream>
#include <chrono>

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

const Color RED   = Color(255, 0, 0, 255);
const Color GREEN = Color(0, 255, 0, 255);
const Color BLUE  = Color(0, 0, 255, 255);
const Color WHITE = Color(255, 255, 255, 255);

void runAllTestCases(Bitmap& bitmap);

int main() {

    Bitmap bitmap(WIDTH, HEIGHT);

    auto start = std::chrono::system_clock::now();
    for(uint32_t i = 0; i < 10000; i++) {
        runAllTestCases(bitmap);
    }
    auto end = chrono::system_clock::now();
    auto elapsed =
    chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << elapsed.count() << endl;

    bitmap.write("lines.bmp");

    return 0;
}


void runAllTestCases(Bitmap& bitmap) {
    //y increasing octants 0-3
    line(13, 20, 500, 400, WHITE, bitmap);
    bitmap.setPixel(13, 20, RED);
    bitmap.setPixel(500, 400, RED);
    line(20, 13, 400, 500, GREEN, bitmap);
    bitmap.setPixel(20, 13, RED);
    bitmap.setPixel(400, 500, RED);
    line(400, 130, 200, 550, WHITE, bitmap);
    bitmap.setPixel(400, 130, RED);
    bitmap.setPixel(200, 550, RED);
    line(790, 200, 130, 400, GREEN, bitmap);
    bitmap.setPixel(790, 200, RED);
    bitmap.setPixel(130, 400, RED);

    //y increasing octants 4-7
    line(700, 500, 10, 10, BLUE, bitmap);
    bitmap.setPixel(700, 500, RED);
    bitmap.setPixel(10, 10, RED);
    line(500, 550, 10, 13, WHITE, bitmap);
    bitmap.setPixel(500, 550, RED);
    bitmap.setPixel(10, 13, RED);
    line(200, 50, 350, 450, BLUE, bitmap);
    bitmap.setPixel(200, 50, RED);
    bitmap.setPixel(350, 450, RED);
    line(50, 590, 790, 100, GREEN, bitmap);
    bitmap.setPixel(50, 590, RED);
    bitmap.setPixel(790, 100, RED);
}
