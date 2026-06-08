#include "SDL3/SDL_error.h"
#include <iostream>
#include <SDL3/SDL.h>

#define WIN_H 600
#define WIN_W 800
#define BUFF_H 600
#define BUFF_W 800

int main(void) {

    std::cout << "Hello World." << std::endl;

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // initialize a window
    SDL_Window *window = SDL_CreateWindow("Raytracer", WIN_W, WIN_H, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cout << "Error initializing window: " << SDL_GetError();
    }
    
    std::cout << "Exit? Press any button to continue..." << std::endl;
    std::string input;
    std::cin >> input;


    // destroy window
    SDL_DestroyWindow(window);
    // quit SDL
    SDL_Quit();
    return 0;
} 