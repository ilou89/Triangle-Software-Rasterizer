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
    enum LineDrawerType{
        SIMPLE = 1,
        INTEGER,
        SLICE
    };

    LineDrawerFactory();
    virtual ~LineDrawerFactory();

    static std::unique_ptr<BaseBresenham> makeLineDrawer(LineDrawerType type,
                                                         Bitmap &bmp);
};

#endif //__FACTORYLINEDRAWER_H__
