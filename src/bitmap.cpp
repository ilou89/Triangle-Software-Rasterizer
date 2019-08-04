#include "bitmap.h"
#include <limits>

Bitmap::Bitmap(unsigned int width, unsigned int height)
 : width(width),
   height(height),
   frameBuffer(nullptr),
   zBuffer(nullptr)
{
   unsigned long bytes = RGB * width * height;
   frameBuffer = std::make_unique<uint8_t[]>(bytes);
   zBuffer = std::make_unique<float[]>(width * height);
   float *raw_data = zBuffer.get();
   for(uint32_t i = 0; i < width * height; ++i) {
       raw_data[i] = std::numeric_limits<float>::lowest();
   }
}

Bitmap::Bitmap(const Bitmap& rhs)
 : width(rhs.width),
   height(rhs.height),
   frameBuffer(nullptr),
   zBuffer(nullptr)
{
   unsigned long bytes = RGB * width * height;
   frameBuffer = std::make_unique<uint8_t[]>(bytes);
   memcpy(frameBuffer.get(), rhs.frameBuffer.get(), bytes);
   zBuffer = std::make_unique<float[]>(width * height);
   memcpy(zBuffer.get(), rhs.zBuffer.get(), width * height);
}

Bitmap&
Bitmap::operator=(const Bitmap& rhs)
{
    if(this != &rhs) {
        if(frameBuffer) {
            frameBuffer.reset();
        }
        if(zBuffer) {
            zBuffer.reset();
        }
        width = rhs.width;
        height = rhs.height;
        unsigned long bytes = RGB * width * height;
        frameBuffer = std::make_unique<uint8_t[]>(bytes);
        memcpy(frameBuffer.get(), rhs.frameBuffer.get(), bytes);
        zBuffer = std::make_unique<float[]>(width * height);
        memcpy(zBuffer.get(), rhs.zBuffer.get(), width * height);
    }

    return *this;
}

Bitmap::~Bitmap()
{

}

bool
Bitmap::setPixel(const Point2D& p, const Color& color)
{
    uint8_t *raw_data = frameBuffer.get();
    memcpy(raw_data + (p.x + p.y * width) * RGB, color.raw, RGB);

    return true;
}

bool
Bitmap::write(const char* filename)
{
    FileHeader fileHeader;
    InfoHeader infoHeader;

    fillHeaders(fileHeader, infoHeader);

    std::ofstream file;
    file.open(filename, std::ios::out|std::ios::binary);
    if(!file.is_open()) {
        return false;
    }

    file.write(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));
    file.write(reinterpret_cast<char *>(frameBuffer.get()), width * height * RGB);

    file.close();

    return true;
}

void Bitmap::fillHeaders(FileHeader& fileHeader, InfoHeader& infoHeader)
{
    fileHeader.fileSize = sizeof(InfoHeader) + width * height * RGB;
    fileHeader.dataOffset = sizeof(FileHeader)+ sizeof(InfoHeader);

    infoHeader.width = width;
    infoHeader.height = height;
}

unsigned int
Bitmap::getWidth() const
{
    return this->width;
}

unsigned int
Bitmap::getHeight() const
{
    return this->height;
}

bool
Bitmap::zBufferTest(const Point2D& p, float z) const
{
    float *raw_data = zBuffer.get();
    if(z > raw_data[p.x + p.y * width]) {
        return true;
    }

    return false;
}

bool
Bitmap::setDepth(const Point2D& p, float z)
{
    float *raw_data = zBuffer.get();
    memcpy(raw_data + (p.x + p.y * width), &z, 4);

    return true;
}

