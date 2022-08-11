#include <iostream>
#include <SDL2/SDL.h>
#include "pendulum.h"

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

bool init();
void close();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main( int argc, char* args[] ) {
    if ( !init() ) {
        std::cerr << "Could not initialize" << std::endl;
    } else {
        bool quit = false;
        SDL_Event event;
        Pendulum main_pendulum(100, 300, 3.141/4, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, renderer);
        main_pendulum.set_renderer(renderer);
        main_pendulum.set_gravity(0.0001);
        while (!quit) {
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
            }
            SDL_SetRenderTarget(renderer, NULL);
            SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
            SDL_RenderClear(renderer);
            main_pendulum.draw_pendulum();
            SDL_RenderPresent(renderer);
        }
    }
    return 0;
}

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize SDL --> " << SDL_GetError() << std::endl;
        success = false;
    } else {
        window = SDL_CreateWindow("Pendulum", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if ( window == NULL ) {
            std::cerr << "Erro while creating SDL window --> " << SDL_GetError() << std::endl;
            success = false;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if ( renderer == NULL ) {
                std::cerr << "Renderer was not created --> " << SDL_GetError() << std::endl;
                success = false;
            }
        }
    }
    return success;
}
