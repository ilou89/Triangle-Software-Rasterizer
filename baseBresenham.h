#ifndef __BASEBRESENHAM_H__
#define __BASEBRESENHAM_H__

#include "bitmap.h"
#include "modelLoader.h"

class BaseBresenham {
protected:
    Bitmap& bmp;
    ModelLoader& model;

private:
    void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color);
    virtual void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color) = 0;
    virtual void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color) = 0;
    void vertical(unsigned int x0, unsigned int y0, int dy, const Color& color);
    void horizontal(unsigned int x0, unsigned int y0, int dx, int xDirection, const Color& color);
    void diagonal(unsigned int x0, unsigned int y0, int dx, int xDirection, const Color& color);

public:
    BaseBresenham(Bitmap& bmp, ModelLoader& model);
    virtual ~BaseBresenham();
    void drawLines();
    void wireframe();
};

#endif //__BASEBRESENHAM_H__
