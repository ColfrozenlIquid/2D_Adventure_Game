#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "application.hpp"

#define PLAYER_SPRITE "./sprite/player.png"

class Entity {
    public:
        Entity();
        Entity(SDL_Renderer* sdl_Renderer);
        ~Entity();

        void blit_Texture(int x_pos, int y_pos);

    private:
        SDL_Texture* load_Texture(std::string filename);

        int m_x_pos;
        int m_y_pos;
        SDL_Texture* m_texture;
        SDL_Renderer* m_renderer;
};