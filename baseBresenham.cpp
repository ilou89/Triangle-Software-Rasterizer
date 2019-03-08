#include "baseBresenham.h"

const Color RED   = Color(255, 0, 0, 255);
const Color GREEN = Color(0, 255, 0, 255);
const Color BLUE  = Color(0, 0, 255, 255);
const Color WHITE = Color(255, 255, 255, 255);

DrawLine::DrawLine(Bitmap& bmp)
 : bmp(bmp)
{

}

DrawLine::~DrawLine()
{

}

void
DrawLine::drawLines()
{
    //y increasing octants 0-3
    line(13, 20, 500, 400, WHITE);
    bmp.setPixel(13, 20, RED);
    bmp.setPixel(500, 400, RED);
    line(20, 13, 400, 500, GREEN);
    bmp.setPixel(20, 13, RED);
    bmp.setPixel(400, 500, RED);
    line(400, 130, 200, 550, WHITE);
    bmp.setPixel(400, 130, RED);
    bmp.setPixel(200, 550, RED);
    line(790, 200, 130, 400, GREEN);
    bmp.setPixel(790, 200, RED);
    bmp.setPixel(130, 400, RED);

    //y increasing octants 4-7
    line(700, 500, 10, 10, BLUE);
    bmp.setPixel(700, 500, RED);
    bmp.setPixel(10, 10, RED);
    line(500, 550, 10, 13, WHITE);
    bmp.setPixel(500, 550, RED);
    bmp.setPixel(10, 13, RED);
    line(200, 50, 350, 450, BLUE);
    bmp.setPixel(200, 50, RED);
    bmp.setPixel(350, 450, RED);
    line(50, 590, 790, 100, GREEN);
    bmp.setPixel(50, 590, RED);
    bmp.setPixel(790, 100, RED);
}

