#include "sliceBresenham.h"

SliceBresenham::SliceBresenham(Bitmap& bmp)
 : DrawLine(bmp)
{

}

SliceBresenham::~SliceBresenham()
{

}

void
SliceBresenham::octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color)
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

    horizontalSlice(x, y++, xDirection, startSlice, color);
    dy--;
    while(dy--) {
        int runLength = runSlice;
        if((error += upError) > 0) {
            runLength++;
            error -= downError;
        }
        horizontalSlice(x, y++, xDirection, runLength, color);
    }
    horizontalSlice(x, y, xDirection, endSlice, color);
}

void
SliceBresenham::octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color)
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

    verticalSlice(x, y, startSlice, color);
    x += xDirection;
    dx--;
    while(dx--) {
        int runLength = runSlice;
        if((error += upError) > 0) {
            runLength++;
            error -= downError;
        }
        verticalSlice(x, y, runLength, color);
        x += xDirection;
    }
    verticalSlice(x, y, endSlice, color);
}

void
SliceBresenham::horizontalSlice(unsigned int& x, unsigned int y, int xDirection, int runSlice, const Color& color)
{
    for(int i = 0; i < runSlice; i++) {
        bmp.setPixel(x, y, color);
        x += xDirection;
    }
}

void
SliceBresenham::verticalSlice(unsigned int x, unsigned int& y, int runSlice, const Color& color)
{
    for(int i = 0; i < runSlice; i++) {
        bmp.setPixel(x, y++, color);
    }
}

