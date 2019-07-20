#include "window.h"

Window::Window()
{

}

Window::~Window()
{

}

int
Window::CreateWindow(std::string &imageFile)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    window = SDL_CreateWindow("Bresenham Line Drawing Displayed by SDL2",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800, 600, 0);

    if(!window) {
        std::cout << "Failed to create window\n";
        return -1;
    }

    windowSurface = SDL_GetWindowSurface(window);

    if(!windowSurface) {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }

    image = SDL_LoadBMP(imageFile.c_str());

    if(!image) {
	    std::cout << "Failed to load image\n";
	    std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
	    return -1;
    }

    return 0;
}

void
Window::BlitWindow()
{
    SDL_BlitSurface(image, NULL, windowSurface, NULL);
    SDL_UpdateWindowSurface(window);
}

