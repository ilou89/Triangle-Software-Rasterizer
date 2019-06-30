#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL2/SDL.h>
#include <iostream>

class Window {
private:
    SDL_Window *window;
    SDL_Surface *windowSurface;
    SDL_Surface *image;

public:
    Window();
    ~Window();

    int CreateWindow(std::string &imageFile);
    void BlitWindow();
};

#endif //__WINDOW_H__
