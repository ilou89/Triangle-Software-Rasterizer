#ifndef __INTEGERBRESENHAM_H__
#define __INTEGERBRESENHAM_H__

#include "baseBresenham.h"

class IntegerBresenham: public DrawLine {
private:
    void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color);
    void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color);

public:
    IntegerBresenham(Bitmap& bmp);
    ~IntegerBresenham();
};

#endif //__INTEGERBRESENHAM_H__

