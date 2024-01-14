#pragma once
#include "entity.hpp"

#define DEMON_SPRITE_PATH "./sprite/demon_1_200.bmp"

class Demon : public Entity {
    public:
        Demon();
        Demon(SDL_Renderer* sdl_renderer);
        ~Demon();
    private:
        SDL_Texture* load_Texture();
};