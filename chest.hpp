#pragma once
#include "entity.hpp"

#define CHEST_SPRITE_PATH "./sprite/chest.bmp"

class Chest : public Entity {
    public:
        Chest();
        Chest(SDL_Renderer* sdl_renderer);
        ~Chest();
    private:
        SDL_Texture* load_Texture();
};