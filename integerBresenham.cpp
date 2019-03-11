#include "integerBresenham.h"

IntegerBresenham::IntegerBresenham(Bitmap& bmp)
 : DrawLine(bmp)
{

}

IntegerBresenham::~IntegerBresenham()
{

}

void
IntegerBresenham::octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color)
{
    int dy2 = 2 * dy;
    int dx2 = 2 * dx;
    int dy2dx2 = dy2 - dx2;
    int error = dy2 - dx;

    bmp.setPixel(x, y, color);
    while(dx--) {
        if(error >= 0) {
            y++;
            error += dy2dx2;
        } else {
            error += dy2;
        }

        x += xDirection;
        bmp.setPixel(x, y, color);
    }
}

void
IntegerBresenham::octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color)
{
    int dy2 = 2 * dy;
    int dx2 = 2 * dx;
    int dx2dy2 = dx2 - dy2;
    int error = dx2 - dy;

    bmp.setPixel(x, y, color);
    while(dy--) {
        if(error >= 0) {
            x += xDirection;
            error += dx2dy2;
        } else {
            error += dx2;
        }

        y++;
        bmp.setPixel(x, y, color);
    }
}

