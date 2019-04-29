#include "integerBresenham.h"

IntegerBresenham::IntegerBresenham(Bitmap& bmp)
 : BaseBresenham(bmp)
{

}

IntegerBresenham::~IntegerBresenham()
{

}

void
IntegerBresenham::octant03(Point2D p, int dx, int dy, int xDirection, const Color& color)
{
    int dy2 = 2 * dy;
    int dx2 = 2 * dx;
    int error = -dx;
    int slope = dy2;

    bmp.setPixel(p, color);
    while(dx--) {
        error += slope;
        if(error >= 0) {
            p.y++;
            error -= dx2;
        }

        p.x += xDirection;
        bmp.setPixel(p, color);
    }
}

void
IntegerBresenham::octant12(Point2D p, int dx, int dy, int xDirection, const Color& color)
{
    int dy2 = 2 * dy;
    int dx2 = 2 * dx;
    int error = - dy;
    int slope = dx2;

    bmp.setPixel(p, color);
    while(dy--) {
        error += slope;
        if(error >= 0) {
            p.x += xDirection;
            error -= dy2;
        }

        p.y++;
        bmp.setPixel(p, color);
    }
}

