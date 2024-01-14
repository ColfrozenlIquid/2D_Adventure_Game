#include "color.hpp"

SDL_Color Color::get_Color(COLOR color) {
    SDL_Color sdl_color;

    switch (color) {
        case WHITE:         sdl_color = {255, 255, 255, 255}; break;
        case BLACK:         sdl_color = {  0,   0,   0, 255}; break;
        case RED:           sdl_color = {255,   0,   0, 255}; break;
        case GREEN:         sdl_color = {  0, 255,   0, 255}; break;
        case BLUE:          sdl_color = {  0,   0, 255, 255}; break;
        case YELLOW:        sdl_color = {255, 255,   0, 255}; break;
        case LIGHT_RED:     sdl_color = { 55,  13,  13, 255}; break;
        case LIGHT_GREEN:   sdl_color = {  4,  90,  13, 255}; break;
        case LIGHT_BLUE:    sdl_color = { 55,  90, 134, 255}; break;
        case GRAY:          sdl_color = {128, 128, 128, 255}; break;
        case DARK_GRAY:     sdl_color = { 48,  48,  48, 255}; break;
        default:            sdl_color = {  0,   0,   0, 255}; break;
    }

    return sdl_color;
}