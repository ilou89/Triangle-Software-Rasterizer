#include "bitmap.h"
#include "modelLoader.h"
#include "renderer.h"

#include <chrono>
#include <iostream>

static const unsigned int WIDTH = 800;
static const unsigned int HEIGHT = 600;

static void printUsage(std::string name);
static bool parseArguments(int argc, char *argv[], std::string &filename, int &choice, bool &xmlSVG);

int main(int argc, char *argv[]) {
    std::string filename;
    int choice;
    bool xmlSVG;

    if (!parseArguments(argc, argv, filename, choice, xmlSVG)) {
        return 1;
    }

    ModelLoader mdloader;
    if (!mdloader.loadFile(filename)) {
        std::cerr << "unable to execute loadFile" << std::endl;
        return 1;
    }

    Bitmap bitmap(WIDTH, HEIGHT);
    Renderer renderer(choice, bitmap, mdloader);

    auto start = std::chrono::system_clock::now();

    for (uint32_t i = 0; i < 100; i++) {
        renderer.wireframe(xmlSVG);
    }

    renderer.rasterize();

    auto end = std::chrono::system_clock::now();
    auto elapsed =
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed milliseconds:" << elapsed.count() << std::endl;

    bitmap.write("lines.bmp");

    return 0;
}

static void printUsage(std::string name) {
    std::cerr << "Usage " << name << " [ options ]\n"
              << "options:\n"
              << "\t-h, --help\t\t Show this help message\n"
              << "\t-s, --svg \t\t Write coordinates into SVG file for offline rendering\n"
              << "\t-f, --filename  FILE\t Specify the path of the .obj file\n"
              << "\t-b, --bresenham CHOICE\t Specify the drawing algorithm\n"
              << "\t\t\tChoices are: 1 for simpleBresenham\n"
              << "\t\t\t             2 for integerBresenham\n"
              << "\t\t\t             3 for sliceBresenham\n"
              << std::endl;
}

static bool parseArguments(int argc, char *argv[], std::string &filename, int &choice, bool &xmlSVG) {
    filename = "obj/cube.obj";
    choice = 1;
    xmlSVG = false;

    if (argc == 1) {
        printUsage(argv[0]);
        std::cerr << "Running with default configuration\n"
                  << "cube.obj file and simpleBresenham algorithm\n"
                  << std::endl;
        return true;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            printUsage(argv[0]);
            return false;
        } else if ((arg == "-f") || (arg == "-filename")) {
            if (i + 1 < argc) {
                filename = argv[++i];
            } else {
                std::cerr << "--filename option requires one argument" << std::endl;
                return false;
            }
        } else if ((arg == "-b") || (arg == "-bresenham")) {
            if (i + 1 < argc) {
                std::istringstream stream(argv[++i]);
                stream >> choice;
            } else {
                std::cerr << "--bresenham option requires one argument" << std::endl;
                return false;
            }
        } else if ((arg == "-s") || (arg == "--svg")) {
                xmlSVG = true;
        }
    }

    return true;
}

