#ifndef __SIMPLEBRESENHAM_H__
#define __SIMPLEBRESENHAM_H__

#include "baseBresenham.h"

class SimpleBresenham: public BaseBresenham {
private:
    void octant03(Point2D p, int dx, int dy, int xDirection, const Color& color) override;
    void octant12(Point2D p, int dx, int dy, int xDirection, const Color& color) override;

public:
    SimpleBresenham(Bitmap& bmp);
    ~SimpleBresenham();
};

#endif //__SIMPLEBRESENHAM_H__

