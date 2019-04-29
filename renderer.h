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

public:
    Renderer(int choice, Bitmap &bitmap, ModelLoader &model);
    ~Renderer();

    void fillBottomFlatTriangle();
    void triangle();
    bool wireframe(bool xmlSVG);
};

#endif //__RENDERER_H__
