#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "application.hpp"

#define PLAYER_SPRITE "./sprite/player.bmp"

#define PLAYER_START_X 100
#define PLAYER_START_Y 100

enum Facing_Direction {
    FACE_LEFT, FACE_RIGHT
};

class Entity {
    public:
        Entity();
        Entity(SDL_Renderer* sdl_Renderer);
        ~Entity();

        void blit_Texture(int x_pos, int y_pos);
        void move_Entity_Horizontal(int dx);
        void move_Entity_Vertical(int dy);
        void set_Entity_Facing(Facing_Direction facing);

        int get_Entity_x_pos();
        int get_Entity_y_pos();

    private:
        SDL_Texture* load_Texture(std::string filename);

        int m_x_pos;
        int m_y_pos;
        Facing_Direction m_facing;
        SDL_Texture* m_texture;
        SDL_Renderer* m_renderer;
};