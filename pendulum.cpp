#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include "pendulum.h"
Pendulum::Pendulum(int base_mass, int base_length, float base_angle, float base_vel, float base_acc, int max_width, int max_height, SDL_Renderer*& render) {
    mass = base_mass;
    length = base_length;
    angle = base_angle;
    vel = base_vel;
    acc = base_acc;
    window_width = max_width;
    window_height = max_height;
    x = (float)window_width/2;
    y = length*5;
    set_renderer(render);
    create_bob();
}

void Pendulum::create_bob() {
    SDL_Surface* bob_surface = NULL;
    bob_surface = SDL_LoadBMP("./src/white_circle.bmp");
    if ( bob_surface == NULL ) {
        std::cerr << "could not load bob bmp --> " << SDL_GetError() << std::endl;
    } else {
        SDL_SetColorKey( bob_surface, SDL_TRUE, SDL_MapRGB( bob_surface->format, 0, 0, 0 ));
    }
    bob_texture = SDL_CreateTextureFromSurface(renderer, bob_surface);
    if ( bob_texture == NULL ) {
        std::cerr << "Could not created bob texture --> " << SDL_GetError() << std::endl;
    }
}

void Pendulum::set_renderer(SDL_Renderer*& render) {
    renderer = render;
}

void Pendulum::set_gravity(float g) {
    gravity = g;
}

void Pendulum::update_pendulum() {
    //x += 0.1;
    //y += 0.2;
    x = length*std::sin(angle)+(float)window_width/2;
    y = length*std::cos(angle);
    bob_rect.x = x-(float)bob_rect.w/2;
    bob_rect.y = y-(float)bob_rect.h/2;
    bob_rect.w = mass/3;
    bob_rect.h = mass/3;
}

void Pendulum::draw_pendulum() {
    acc = -gravity*std::sin(angle);
    vel += acc;
    angle += vel;
    update_pendulum();
    SDL_SetRenderTarget(renderer, bob_texture);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, (float)window_width/2, 0, x, y);
    SDL_RenderCopy(renderer, bob_texture, NULL, &bob_rect);
}
