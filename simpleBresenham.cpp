#include "simpleBresenham.h"

SimpleBresenham::SimpleBresenham(Bitmap& bmp, ModelLoader& model)
 : BaseBresenham(bmp, model)
{

}

SimpleBresenham::~SimpleBresenham()
{

}

void
SimpleBresenham::octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color)
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
SimpleBresenham::octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color)
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

