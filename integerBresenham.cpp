#include "integerBresenham.h"

IntegerBresenham::IntegerBresenham(Bitmap& bmp, ModelLoader& model)
 : BaseBresenham(bmp, model)
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
    int error = -dx;
    int slope = dy2;

    bmp.setPixel(x, y, color);
    while(dx--) {
        error += slope;
        if(error >= 0) {
            y++;
            error -= dx2;
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
    int error = - dy;
    int slope = dx2;

    bmp.setPixel(x, y, color);
    while(dy--) {
        error += slope;
        if(error >= 0) {
            x += xDirection;
            error -= dy2;
        }

        y++;
        bmp.setPixel(x, y, color);
    }
}

