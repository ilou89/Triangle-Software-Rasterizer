#ifndef __FACTORYLINEDRAWER_H__
#define __FACTORYLINEDRAWER_H__

#include "baseBresenham.h"
#include "simpleBresenham.h"
#include "integerBresenham.h"
#include "sliceBresenham.h"
#include "bitmap.h"

#include <memory>

class LineDrawerFactory {
public:
    LineDrawerFactory();
    virtual ~LineDrawerFactory();

    static std::unique_ptr<BaseBresenham> makeLineDrawer(int choice, Bitmap &bmp);

};

#endif //__FACTORYLINEDRAWER_H__
