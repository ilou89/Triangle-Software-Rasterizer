#include "sliceBresenham.h"

SliceBresenham::SliceBresenham(Bitmap& bmp)
 : BaseBresenham(bmp)
{

}

SliceBresenham::~SliceBresenham()
{

}

void
SliceBresenham::octant03(Point2D p, int dx, int dy, int xDirection, const Color& color)
{
    int runSlice = dx / dy;
    int upError = (dx % dy) * 2;
    int downError = dy * 2;
    int error = (dx % dy) - (dy * 2);
    int startSlice = (runSlice / 2) + 1;
    int endSlice = startSlice;

    if((upError == 0) && ((runSlice & 0x01) == 0)) {
        startSlice--;
    }

    if((runSlice & 0x01) != 0) {
        error += dy;
    }

    p.y++;
    xCoords.push_back(p.x);
    horizontalSlice(p, xDirection, startSlice, color);
    dy--;
    while(dy--) {
        int runLength = runSlice;
        if((error += upError) > 0) {
            runLength++;
            error -= downError;
        }
        p.y++;
        xCoords.push_back(p.x);
        horizontalSlice(p, xDirection, runLength, color);
    }
    xCoords.push_back(p.x);
    horizontalSlice(p, xDirection, endSlice, color);
}

void
SliceBresenham::octant12(Point2D p, int dx, int dy, int xDirection, const Color& color)
{
    int runSlice = dy / dx;
    int upError = (dy % dx) * 2;
    int downError = dx * 2;
    int error = (dy % dx) - (dx * 2);
    int startSlice = (runSlice / 2) + 1;
    int endSlice = startSlice;

    if((upError == 0) && ((runSlice & 0x01) == 0)) {
        startSlice--;
    }

    if((runSlice & 0x01) != 0) {
        error += dx;
    }

    verticalSlice(p, startSlice, color);
    p.x += xDirection;
    dx--;
    while(dx--) {
        int runLength = runSlice;
        if((error += upError) > 0) {
            runLength++;
            error -= downError;
        }
        verticalSlice(p, runLength, color);
        p.x += xDirection;
    }
    verticalSlice(p, endSlice, color);
}

void
SliceBresenham::horizontalSlice(Point2D &p, int xDirection, int runSlice, const Color& color)
{
    for(int i = 0; i < runSlice; i++) {
        bmp.setPixel(p, color);
        p.x += xDirection;
    }
}

void
SliceBresenham::verticalSlice(Point2D &p, int runSlice, const Color& color)
{
    for(int i = 0; i < runSlice; i++) {
        p.y++;
        xCoords.push_back(p.x);
        bmp.setPixel(p, color);
    }
}

