#include <cstdint>
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <vector>
class Window {
private:
    uint32_t win_w, win_h, buff_w, buff_h;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
public:
    Window(
        uint32_t window_w, 
        uint32_t window_h, 
        uint32_t buffer_w, 
        uint32_t buffer_h
    ) : win_w(window_w), win_h(window_h), buff_w(buffer_w), buff_h(buffer_h) {
        // initialize a window
        window = SDL_CreateWindow("Raytracer", win_w, win_h, SDL_WINDOW_RESIZABLE);
        if (window == NULL) {
            std::cout << "Error initializing window: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(-1);
        }

        // initialize a renderer
        renderer = SDL_CreateRenderer(window, nullptr);
        if (renderer == NULL) {
            std::cout << "Error initializing renderer: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(-1);
        }

        // initialize a texture
        texture = SDL_CreateTexture(
            renderer, 
            SDL_PIXELFORMAT_RGBA8888, 
            SDL_TEXTUREACCESS_STREAMING, 
            buff_w, buff_h
        );
    }


    ~Window() {
        // destroy window
        SDL_DestroyWindow(window);
        // quit SDL
        SDL_Quit();
    }

    void start() {
        // create raw frame buffer
        std::vector<uint32_t> pixels(buff_w * buff_h);
        
        bool is_running = true;
        SDL_Event event;

        // main loop
        while (is_running) {
            // poll for events
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    is_running = false;
                }
            }

            // make a visual effect to the frame buffer
            uint8_t pulse = (SDL_GetTicks() / 5) % 256;
            for (int y = 0; y < buff_h; ++y) {
                for (int x = 0; x < buff_w; ++x) {
                    // Format is 0xRRGGBBAA in memory
                    pixels[y * buff_w + x] = (pulse << 24) | (0x00 << 16) | (0x00 << 8) | 0xFF;
                }
            }

            // update the texture with the new frame buffer data
            int pitch = buff_w * sizeof(uint32_t);
            SDL_UpdateTexture(texture, nullptr, pixels.data(), pitch);

            // render that texture to the screen
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, texture, nullptr, nullptr);
            SDL_RenderPresent(renderer);
        }
    }
};