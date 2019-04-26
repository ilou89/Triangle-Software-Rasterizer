#ifndef __SLICEBRESENHAM_H__
#define __SLICEBRESENHAM_H__

#include "baseBresenham.h"

class SliceBresenham: public BaseBresenham {
private:
    void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color) override;
    void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color) override;
    void horizontalSlice(unsigned int& x, unsigned int y, int xDirection, int startSlice, const Color& color);
    void verticalSlice(unsigned int x, unsigned int& y, int runSlice, const Color& color);

public:
    SliceBresenham(Bitmap& bmp);
    ~SliceBresenham();
};

#endif //__SLICEBRESENHAM_H__

