#ifndef __BASEBRESENHAM_H__
#define __BASEBRESENHAM_H__

#include "bitmap.h"

class BaseBresenham {
protected:
    Bitmap& bmp;

private:
    virtual void octant03(Point2D p, int dx, int dy, int xDirection, const Color& color) = 0;
    virtual void octant12(Point2D p, int dx, int dy, int xDirection, const Color& color) = 0;
    void vertical(Point2D p, int dy, const Color& color);
    void horizontal(Point2D p, int dx, int xDirection, const Color& color);
    void diagonal(Point2D p, int dx, int xDirection, const Color& color);

public:
    BaseBresenham(Bitmap& bmp);
    virtual ~BaseBresenham();

    void line(Point2D p0, Point2D p1, const Color& color);
};

#endif //__BASEBRESENHAM_H__
