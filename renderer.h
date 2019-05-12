#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "bitmap.h"
#include "modelLoader.h"
#include "lineDrawerFactory.h"

class Renderer {
private:
    Bitmap &bmp;
    ModelLoader &model;
    std::unique_ptr<BaseBresenham> lineDrawer;

    void fillTriangle(Point2D v0, Point2D v1, Point2D v2);
    void fillTriangle2(Point2D v0, Point2D v1, Point2D v2);

public:
    Renderer(int choice, Bitmap &bitmap, ModelLoader &model);
    ~Renderer();

    void rasterize();
    bool wireframe(bool xmlSVG);
};

#endif //__RENDERER_H__
