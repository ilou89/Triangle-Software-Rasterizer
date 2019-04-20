#include "lineDrawerFactory.h"

LineDrawerFactory::LineDrawerFactory()
{

}

LineDrawerFactory::~LineDrawerFactory()
{

}

std::unique_ptr<BaseBresenham>
LineDrawerFactory::makeLineDrawer(int choice, Bitmap &bmp, ModelLoader& model)
{
    switch (choice) {
        case 1:
            return std::make_unique<SimpleBresenham>(bmp, model);
        case 2:
            return std::make_unique<IntegerBresenham>(bmp, model);
        case 3:
            return std::make_unique<SliceBresenham>(bmp, model);
        default:
            return std::make_unique<SimpleBresenham>(bmp, model);
    }
}
