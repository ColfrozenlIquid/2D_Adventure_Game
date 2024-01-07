#pragma once
#include "entity.hpp"

#define PLAYER_SPRITE_PATH "./sprite/player_200.bmp"

class Player : public Entity {
    public:
        Player();
        Player(SDL_Renderer* sdl_renderer);
        ~Player();
    private:
        SDL_Texture* load_Texture();
};