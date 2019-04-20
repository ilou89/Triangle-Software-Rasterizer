#include "bitmap.h"

Bitmap::Bitmap(unsigned int width, unsigned int height)
 : width(width),
   height(height),
   data(nullptr)
{
   unsigned long bytes = RGB * width * height;
   data = std::make_unique<uint8_t[]>(bytes);
}

Bitmap::Bitmap(const Bitmap& rhs)
 : width(rhs.width),
   height(rhs.height),
   data(nullptr)
{
   unsigned long bytes = RGB * width * height;
   data = std::make_unique<uint8_t[]>(bytes);
   memcpy(data.get(), rhs.data.get(), bytes);
}

Bitmap&
Bitmap::operator=(const Bitmap& rhs)
{
    if(this != &rhs) {
        if(data) {
            data.reset();
        }
        width = rhs.width;
        height = rhs.height;
        unsigned long bytes = RGB * width * height;
        data = std::make_unique<uint8_t[]>(bytes);
        memcpy(data.get(), rhs.data.get(), bytes);
    }

    return *this;
}

Bitmap::~Bitmap()
{

}

bool
Bitmap::setPixel(unsigned int x, unsigned int y, const Color& color)
{
    uint8_t *raw_data = data.get();
    memcpy(raw_data + (x + y * width) * RGB, color.raw, RGB);

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
    file.write(reinterpret_cast<char *>(data.get()), width * height * RGB);

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

