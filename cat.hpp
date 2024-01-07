#pragma once
#include "entity.hpp"

#define CAT_SPRITE_PATH "./sprite/cat_anim.bmp"
#define CAT_ANIMATION_FRAMES 6
#define CAT_SPRITE_SIZE 64

class Cat : public Entity {
    public:
        Cat();
        Cat(SDL_Renderer* sdl_renderer);
        ~Cat();
        void blit_Texture(int x_pos, int y_pos);
        void set_Animation_State(int state);

    private:
        SDL_Texture* load_Texture();
        int m_current_anim_state;
};