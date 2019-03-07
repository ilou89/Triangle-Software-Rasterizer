#ifndef __BRESENHAM_H__
#define __BRESENHAM_H__

#include "bmpImage.h"

class Bresenham {
private:
    Bitmap& bmp;

    void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color);
    void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color);
    void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color);

public:
    Bresenham(Bitmap& bmp);
    //Bresenham(const Bresenham& rhs);
    //Bresenham& operator=(const Bresenham& rhs);
    ~Bresenham();

    void drawLines();
};

#endif //__BRESENHAM_H__

