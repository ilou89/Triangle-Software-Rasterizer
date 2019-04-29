#ifndef __INTEGERBRESENHAM_H__
#define __INTEGERBRESENHAM_H__

#include "baseBresenham.h"

class IntegerBresenham: public BaseBresenham {
private:
    void octant03(Point2D p, int dx, int dy, int xDirection, const Color& color) override;
    void octant12(Point2D p, int dx, int dy, int xDirection, const Color& color) override;

public:
    IntegerBresenham(Bitmap& bmp);
    ~IntegerBresenham();
};

#endif //__INTEGERBRESENHAM_H__

