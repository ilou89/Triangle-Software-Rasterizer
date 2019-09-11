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

    float edgeFunction(Vec3f &v0, Vec3f &v1, Vec3f &v2);
    void LineSweep(Vec3f v0, Vec3f v1, Vec3f v2, float intensity);
    void Barycentric(Vec3f v0, Vec3f v1, Vec3f v2, float intensity);

public:
    Renderer(int choice, Bitmap &bitmap, ModelLoader &model);
    ~Renderer();

    void rasterize();
    void render();
    bool wireframe(bool xmlSVG);
};

#endif //__RENDERER_H__
