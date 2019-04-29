#include "simpleBresenham.h"

SimpleBresenham::SimpleBresenham(Bitmap& bmp)
 : BaseBresenham(bmp)
{

}

SimpleBresenham::~SimpleBresenham()
{

}

void
SimpleBresenham::octant03(Point2D p, int dx, int dy, int xDirection, const Color& color)
{
    float error = 0.0f;
    float slope = (float)dy / (float)dx;

    bmp.setPixel(p, color);
    while(dx--) {
        error += slope;
        if(error >= 0.5f) {
            p.y++;
            error -= 1.0f;
        }

        p.x += xDirection;
        bmp.setPixel(p, color);
    }
}

void
SimpleBresenham::octant12(Point2D p, int dx, int dy, int xDirection, const Color& color)
{
    float error = 0.0f;
    float slope = (float)dx / (float)dy;

    bmp.setPixel(p, color);
    while(dy--) {
        error += slope;
        if(error >= 0.5f) {
            p.x += xDirection;
            error -= 1.0f;
        }

        p.y++;
        bmp.setPixel(p, color);
    }
}

