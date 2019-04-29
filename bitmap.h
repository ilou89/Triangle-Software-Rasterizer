#ifndef __BMPIMAGE_H__
#define __BMPIMAGE_H__

#include "geometry.h"

#include <cstdint>
#include <memory>
#include <cstring>
#include <fstream>

#pragma pack(push, 2)
struct FileHeader {
    uint8_t  fileType[2]{'B', 'M'};
    uint32_t fileSize{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t dataOffset{0};
};

struct InfoHeader {
    uint32_t headerSize{40};
    uint32_t width{0};
    uint32_t height{0};
    uint16_t planes{1};
    uint16_t bitsPerPixel{24};
    uint32_t compression{0};
    uint32_t dataSize{0};
    uint32_t horizontalResolution{0};
    uint32_t verticalResolution{0};
    uint32_t colors{0};
    uint32_t importantColors{0};
};
#pragma pack(pop)

struct Color {
    union {
        struct {
            uint8_t blue;
            uint8_t green;
            uint8_t red;
            uint8_t alpha;
        };
        uint8_t raw[4];
        uint32_t value;
    };

    Color()
     : value(0) { }

    Color(uint32_t value)
     : value(value) { }

    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
     : blue(blue),
       green(green),
       red(red),
       alpha(alpha) { }

    Color(const Color& color)
     : value(color.value) { }

    Color& operator=(const Color& color) {
        if(this != &color) {
            value = color.value;
        }
        return *this;
    }
};

class Bitmap {
private:
    unsigned int width;
    unsigned int height;
    std::unique_ptr<uint8_t[]> data;

    void fillHeaders(FileHeader& fileHeader, InfoHeader& infoHeader);

public:
    enum Format {
        RGB = 3, RGBA = 4
    };

    Bitmap(unsigned int width, unsigned int height);
    Bitmap(const Bitmap& rhs);
    Bitmap& operator=(const Bitmap& rhs);
    ~Bitmap();

    bool setPixel(Point2D p, const Color& color);
    bool write(const char* filename);
    unsigned int getWidth() const;
    unsigned int getHeight() const;
};

#endif //__BMPIMAGE_H__

