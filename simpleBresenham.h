#ifndef __SIMPLEBRESENHAM_H__
#define __SIMPLEBRESENHAM_H__

#include "baseBresenham.h"

class SimpleBresenham: public BaseBresenham {
private:
    void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color) override;
    void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color) override;

public:
    SimpleBresenham(Bitmap& bmp, ModelLoader& model);
    ~SimpleBresenham();
};

#endif //__SIMPLEBRESENHAM_H__

