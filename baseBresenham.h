#ifndef __BASEBRESENHAM_H__
#define __BASEBRESENHAM_H__

#include "bitmap.h"
#include <vector>

class BaseBresenham {
protected:
    Bitmap& bmp;
    /**
     * stores the x coordinates when a line is drawn
     * and it is used by the rasterization to find
     * the outline of the triangle to fill
     */
    std::vector<unsigned int> xCoords;

private:
    virtual void octant03(Point2D p, int dx, int dy, int xDirection, const Color& color) = 0;
    virtual void octant12(Point2D p, int dx, int dy, int xDirection, const Color& color) = 0;
    void vertical(Point2D p, int dy, const Color& color);
    void horizontal(Point2D p, int dx, int xDirection, const Color& color);
    void diagonal(Point2D p, int dx, int xDirection, const Color& color);

public:
    BaseBresenham(Bitmap& bmp);
    virtual ~BaseBresenham();

    std::vector<unsigned int> getXCoords();
    void line(Point2D p0, Point2D p1, const Color& color);
};

#endif //__BASEBRESENHAM_H__
