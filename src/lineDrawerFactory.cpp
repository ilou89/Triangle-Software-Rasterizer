#include "lineDrawerFactory.h"

LineDrawerFactory::LineDrawerFactory()
{

}

LineDrawerFactory::~LineDrawerFactory()
{

}

std::unique_ptr<BaseBresenham>
LineDrawerFactory::makeLineDrawer(LineDrawerType type, Bitmap &bmp)
{
    switch (type) {
        case SIMPLE:
            return std::make_unique<SimpleBresenham>(bmp);
        case INTEGER:
            return std::make_unique<IntegerBresenham>(bmp);
        case SLICE:
            return std::make_unique<SliceBresenham>(bmp);
        default:
            return std::make_unique<SimpleBresenham>(bmp);
    }
}
