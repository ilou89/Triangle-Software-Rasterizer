#include "bitmap.h"
#include "simpleBresenham.h"
#include "integerBresenham.h"
#include "sliceBresenham.h"
#include "modelLoader.h"
#include <iostream>
#include <chrono>
#include <getopt.h>

static const unsigned int WIDTH = 800;
static const unsigned int HEIGHT = 600;

static const char * const shortOptions = "f:hb";
static const struct option longOptions[] = {
    { "filename",  1, NULL, 'f' },
    { "help",      0, NULL, 'h' },
    { "bresenham", 1, NULL, 'b' },
};

static const char * const usageTemplate =
    "Usage: %s [ options ]\n"
    " -f, --filename FILE    The path of the .obj file to read\n"
    " -h, --help             Print this information\n"
    " -b, --bresenham CHOICE Choose between multiple implementations of line drawing algorithm\n"
    "                        Choices are: 1)simpleBresenham, 2)integerBresenham and 3)sliceBresenham\n";

static void printUsage();
static void parseArguments(int argc, char * const argv[]);

int main(int argc, char * const argv[]) {

    parseArguments(argc, argv);

    Bitmap bitmap(WIDTH, HEIGHT);
    IntegerBresenham simpleBresenham(bitmap);

    auto start = std::chrono::system_clock::now();
    //for(uint32_t i = 0; i < 1000000; i++) {
        simpleBresenham.drawLines();
    //}

    //load data
    ModelLoader mdloader;
    if(!mdloader.loadFile("obj/cube.obj")) {
        std::cerr << "unable to execute loadFile" << std::endl;
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed =
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed milliseconds:" << elapsed.count() << std::endl;

    bitmap.write("lines.bmp");


    return 0;
}

static void printUsage() {
    std::cout << usageTemplate << std::endl;
}

static void parseArguments(int argc, char * const argv[]) {
    int option;

    do {
        option = getopt_long(argc, argv, shortOptions, longOptions, NULL);
        switch (option) {
            case 'h':
                printUsage();
                break;
            case '?':
                printUsage();
                break;
            case -1:
                std::cout << "Run with the default line drawing algorithm (simpleBresenham)" << std::endl;
                break;
            default:
                break;
        }
    } while (option != -1);
}

