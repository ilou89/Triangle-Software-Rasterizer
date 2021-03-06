#include "bitmap.h"
#include "modelLoader.h"
#include "renderer.h"
#include "window.h"

#include <chrono>
#include <iostream>
#include <math.h>

static const unsigned int WIDTH = 800;
static const unsigned int HEIGHT = 600;
static bool quit = false;

static void BlitWindow(std::string &imageFile);
static void printUsage(std::string name);
static bool parseArguments(int argc, char *argv[], std::string &filename, int &choice, bool &xmlSVG);

int main(int argc, char *argv[]) {
    std::string filename  = "../obj/cube.obj";
    std::string imageFile = "lines.bmp";
    int choice = 1;
    bool xmlSVG = false;

    if (!parseArguments(argc, argv, filename, choice, xmlSVG)) {
        return EXIT_FAILURE;
    }

    ModelLoader mdloader;
    if (!mdloader.loadFile(filename)) {
        std::cerr << "unable to execute loadFile" << std::endl;
        return EXIT_FAILURE;
    }

    Bitmap bitmap(WIDTH, HEIGHT);
    Renderer renderer(choice, bitmap, mdloader);

    //Transformation matrix
    float **matrix;
    matrix = new float *[3];
    for ( int i = 0; i <3; ++i ) {
        matrix[i] = new float[3];
    }


    matrix[0][0] = 0.5f; matrix[0][1] = 0.0f; matrix[0][2] = 0.0f;
    matrix[1][0] = 0.0f; matrix[1][1] = 0.2f; matrix[1][2] = 0.0f;
    matrix[2][0] = 0.0f; matrix[2][1] = 0.0f; matrix[2][2] = 1.0f;

    // while (1) {
        auto start = std::chrono::system_clock::now();

        /* Loop for benchmarking reasons */
        // for (uint32_t i = 0; i < 1; i++) {
        //     renderer.wireframe(xmlSVG);
        // }

        /* Rasterize random triangles for testing reasons */
        // renderer.rasterize();

        /* The main function that produces the rendered image */
        renderer.render(matrix);

        auto end = std::chrono::system_clock::now();
        auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Elapsed milliseconds:" << elapsed.count() << std::endl;

    // }
    bitmap.write("lines.bmp");

    /* Blit the rendered image into an SDL created window */
    BlitWindow(imageFile);

    return EXIT_SUCCESS;
}

static void printUsage(std::string name) {
    std::cerr << "Usage " << name << " [ options ]\n"
              << "options:\n"
              << "\t-h, --help\t\t Show this help message\n"
              << "\t-s, --svg \t\t Write coordinates into SVG file for offline rendering through browser\n"
              << "\t-f, --filename  FILE\t Specify the path of the .obj file\n"
              << "\t-b, --bresenham CHOICE\t Specify the drawing algorithm\n"
              << "\t\t\tChoices are: 1 for simpleBresenham (default)\n"
              << "\t\t\t             2 for integerBresenham\n"
              << "\t\t\t             3 for sliceBresenham\n"
              << std::endl;
}

static bool parseArguments(int argc, char *argv[], std::string &filename, int &choice, bool &xmlSVG) {

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

static void BlitWindow(std::string &imageFile)
{
    Window sdlWindow;
    sdlWindow.CreateWindow(imageFile);

    while(!quit)
    {
	    SDL_Event event;
	    while(SDL_PollEvent(&event) > 0)
	    {
	        switch(event.type)
            {
		        case SDL_QUIT:
		        {
		            quit = true;
		        } break;
		        case SDL_KEYDOWN:
		        {
		            if (event.key.keysym.sym == SDLK_ESCAPE)
		            {
                        quit = true;
		            }
                } break;
	        }

            sdlWindow.BlitWindow();
        }
    }
}

