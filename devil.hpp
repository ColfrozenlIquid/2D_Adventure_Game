#pragma once
#include "entity.hpp"

#define DEVIL_SPRITE_PATH "./sprite/devil_200.bmp"

class Devil : public Entity {
    public:
        Devil();
        Devil(SDL_Renderer* sdl_renderer);
        ~Devil();
    private:
        SDL_Texture* load_Texture();
};