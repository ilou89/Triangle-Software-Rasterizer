#ifndef __BRESENHAM_H__
#define __BRESENHAM_H__

#include "baseBresenham.h"

class SimpleBresenham: public DrawLine {
private:
    void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color);
    void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color);

public:
    SimpleBresenham(Bitmap& bmp);
    //SimpleBresenham(const SimpleBresenham& rhs);
    //SimpleBresenham& operator=(const SimpleBresenham& rhs);
    ~SimpleBresenham();
};

#endif //__BRESENHAM_H__

