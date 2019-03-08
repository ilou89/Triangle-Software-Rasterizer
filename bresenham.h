#ifndef __BRESENHAM_H__
#define __BRESENHAM_H__

#include "bmpImage.h"

class DrawLine {
protected:
    Bitmap& bmp;

private:
    virtual void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color) = 0;
    virtual void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color) = 0;
    virtual void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color) = 0;

public:
    DrawLine(Bitmap& bmp);
    //DrawLine(const DrawLine& rhs);
    //DrawLine& operator=(const DrawLine& rhs);
    virtual ~DrawLine();
    void drawLines();
};

class Bresenham: public DrawLine {
private:
    void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color);
    void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color);
    void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color);

public:
    Bresenham(Bitmap& bmp);
    //Bresenham(const Bresenham& rhs);
    //Bresenham& operator=(const Bresenham& rhs);
    ~Bresenham();
};

#endif //__BRESENHAM_H__

