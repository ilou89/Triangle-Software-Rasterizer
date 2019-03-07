#include "bresenham.h"

const Color RED   = Color(255, 0, 0, 255);
const Color GREEN = Color(0, 255, 0, 255);
const Color BLUE  = Color(0, 0, 255, 255);
const Color WHITE = Color(255, 255, 255, 255);

Bresenham::Bresenham(Bitmap& bmp)
 : bmp(bmp)
{

}

//Bresenham::Bresenham(const Bresenham& rhs)
//{
//
//}
//
//Bresenham&
//Bresenham::operator=(const Bresenham& rhs)
//{
//
//}

Bresenham::~Bresenham()
{

}

void
Bresenham::drawLines()
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

void
Bresenham::line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color)
{
    int xDirection = 1;
    int dx, dy;

    if(y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }

    dx = x1 - x0;
    dy = y1 - y0;

    if(dx < 0) {
        dx = -dx;
        xDirection = -xDirection;
    }

    if(dx > dy) {
        octant03(x0, y0, dx, dy, xDirection, color);
    } else {
        octant12(x0, y0, dx, dy, xDirection, color);
    }
}

void
Bresenham::octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color)
{
    float error = 0.0f;
    float slope = (float)dy / (float)dx;

    bmp.setPixel(x, y, color);
    while(dx--) {
        error += slope;
        if(error >= 0.5f) {
            y++;
            error -= 1.0f;
        }

        x += xDirection;
        bmp.setPixel(x, y, color);
    }
}

void
Bresenham::octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color)
{
    float error = 0.0f;
    float slope = (float)dx / (float)dy;

    bmp.setPixel(x, y, color);
    while(dy--) {
        error += slope;
        if(error >= 0.5f) {
            x += xDirection;
            error -= 1.0f;
        }

        y++;
        bmp.setPixel(x, y, color);
    }
}

