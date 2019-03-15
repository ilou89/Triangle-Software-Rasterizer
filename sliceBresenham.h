#ifndef __SIMPLEBRESENHAM_H__
#define __SIMPLEBRESENHAM_H__

#include "baseBresenham.h"

class sliceBresenham: public DrawLine {
private:
    void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color);
    void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color);

public:
    sliceBresenham(Bitmap& bmp);
    //sliceBresenham(const sliceBresenham& rhs);
    //sliceBresenham& operator=(const sliceBresenham& rhs);
    ~sliceBresenham();
};

#endif //__SIMPLEBRESENHAM_H__

