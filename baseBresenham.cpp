#include "baseBresenham.h"

BaseBresenham::BaseBresenham(Bitmap& bmp)
 : bmp(bmp)
{

}

BaseBresenham::~BaseBresenham()
{

}

void
BaseBresenham::line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color)
{
    int xDirection = 1;
    int dx, dy;

    if(y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }

    dx = x1 - x0;
    dy = y1 - y0;

    if(dx < 0) {
        dx = -dx;
        xDirection = -xDirection;
    }

    //vertical line
    if(dx == 0) {
        vertical(x0, y0, dy, color);
        return;
    }

    //horizontal line
    if(dy == 0){
        horizontal(x0, y0, dx, xDirection, color);
        return;
    }

    //diagonal line
    if(dx == dy){
        diagonal(x0, y0, dx, xDirection, color);
        return;
    }

    if(dx > dy) {
        octant03(x0, y0, dx, dy, xDirection, color);
    } else {
        octant12(x0, y0, dx, dy, xDirection, color);
    }
}

void
BaseBresenham::vertical(unsigned int x0, unsigned int y0, int dy, const Color& color)
{
    bmp.setPixel(x0, y0, color);
    while(dy--) {
        y0++;
        bmp.setPixel(x0, y0, color);
    }
}

void
BaseBresenham::horizontal(unsigned int x0, unsigned int y0, int dx, int xDirection, const Color& color)
{
    bmp.setPixel(x0, y0, color);
    while(dx--) {
        x0 += xDirection;
        bmp.setPixel(x0, y0, color);
    }
}

void
BaseBresenham::diagonal(unsigned int x0, unsigned int y0, int dx, int xDirection, const Color& color)
{
    bmp.setPixel(x0, y0, color);
    while(dx--) {
        x0 += xDirection;
        y0++;
        bmp.setPixel(x0, y0, color);
    }
}

