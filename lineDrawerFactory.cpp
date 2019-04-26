#include "lineDrawerFactory.h"

LineDrawerFactory::LineDrawerFactory()
{

}

LineDrawerFactory::~LineDrawerFactory()
{

}

std::unique_ptr<BaseBresenham>
LineDrawerFactory::makeLineDrawer(int choice, Bitmap &bmp)
{
    switch (choice) {
        case 1:
            return std::make_unique<SimpleBresenham>(bmp);
        case 2:
            return std::make_unique<IntegerBresenham>(bmp);
        case 3:
            return std::make_unique<SliceBresenham>(bmp);
        default:
            return std::make_unique<SimpleBresenham>(bmp);
    }
}
