#pragma once
#include <SDL2/SDL.h>

class Color {
    public:

    enum COLOR {
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        LIGHT_BLUE,
        LIGHT_RED,
        LIGHT_GREEN,
        GRAY,
        DARK_GRAY
    };

    Color() = delete;
    static SDL_Color get_Color(COLOR color);
};