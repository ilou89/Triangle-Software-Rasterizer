#ifndef __SLICEBRESENHAM_H__
#define __SLICEBRESENHAM_H__

#include "baseBresenham.h"

class SliceBresenham: public BaseBresenham {
private:
    void octant03(Point2D p, int dx, int dy, int xDirection, const Color& color) override;
    void octant12(Point2D p, int dx, int dy, int xDirection, const Color& color) override;
    void horizontalSlice(Point2D &p, int xDirection, int startSlice, const Color& color);
    void verticalSlice(Point2D &p, int runSlice, const Color& color);

public:
    SliceBresenham(Bitmap& bmp);
    ~SliceBresenham();
};

#endif //__SLICEBRESENHAM_H__

