#include "bresenham.h"

void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color, Bitmap& img) {
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
        octant03(x0, y0, dx, dy, xDirection, color, img);
    } else {
        octant12(x0, y0, dx, dy, xDirection, color, img);
    }
}

void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color, Bitmap& img) {
    float error = 0.0f;
    float slope = (float)dy / (float)dx;

    img.setPixel(x, y, color);
    while(dx--) {
        error += slope;
        if(error >= 0.5f) {
            y++;
            error -= 1.0f;
        }

        x += xDirection;
        img.setPixel(x, y, color);
    }
}

void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color, Bitmap& img) {
    float error = 0.0f;
    float slope = (float)dx / (float)dy;

    img.setPixel(x, y, color);
    while(dy--) {
        error += slope;
        if(error >= 0.5f) {
            x += xDirection;
            error -= 1.0f;
        }

        y++;
        img.setPixel(x, y, color);
    }
}

