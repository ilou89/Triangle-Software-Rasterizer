#ifndef __BRESENHAM_H__
#define __BRESENHAM_H__

#include "bmpImage.h"

void line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color, Bitmap& img);
void octant12(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color, Bitmap& img);
void octant03(unsigned int x, unsigned int y, int dx, int dy, int xDirection, const Color& color, Bitmap& img);

#endif //__BRESENHAM_H__

