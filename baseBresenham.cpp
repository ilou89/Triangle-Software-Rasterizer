#include "baseBresenham.h"

BaseBresenham::BaseBresenham(Bitmap& bmp)
 : bmp(bmp)
{

}

BaseBresenham::~BaseBresenham()
{

}

void
BaseBresenham::line(Point2D p0, Point2D p1, const Color& color)
{
    int xDirection = 1;
    int dx, dy;

    if(p0.y > p1.y) {
        std::swap(p0, p1);
    }

    dx = p1.x - p0.x;
    dy = p1.y - p0.y;

    if(dx < 0) {
        dx = -dx;
        xDirection = -xDirection;
    }

    //vertical line
    if(dx == 0) {
        vertical(p0, dy, color);
        return;
    }

    //horizontal line
    if(dy == 0){
        horizontal(p0, dx, xDirection, color);
        return;
    }

    //diagonal line
    if(dx == dy){
        diagonal(p0, dx, xDirection, color);
        return;
    }

    if(dx > dy) {
        octant03(p0, dx, dy, xDirection, color);
    } else {
        octant12(p0, dx, dy, xDirection, color);
    }
}

void
BaseBresenham::vertical(Point2D p, int dy, const Color& color)
{
    bmp.setPixel(p, color);
    while(dy--) {
        p.y++;
        bmp.setPixel(p, color);
    }
}

void
BaseBresenham::horizontal(Point2D p, int dx, int xDirection, const Color& color)
{
    bmp.setPixel(p, color);
    while(dx--) {
        p.x += xDirection;
        bmp.setPixel(p, color);
    }
}

void
BaseBresenham::diagonal(Point2D p, int dx, int xDirection, const Color& color)
{
    bmp.setPixel(p, color);
    while(dx--) {
        p.x += xDirection;
        p.y++;
        bmp.setPixel(p, color);
    }
}

