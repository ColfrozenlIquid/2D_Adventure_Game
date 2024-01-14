#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "application.hpp"

#define PLAYER_START_X 100
#define PLAYER_START_Y 100

#define DEVIL_START_X 500
#define DEVIL_START_Y 500

#define CHEST_START_X 800
#define CHEST_START_Y 400

#define CAT_START_X 1000
#define CAT_START_Y 100

#define DEMON_START_X 100
#define DEMON_START_Y 550

enum Facing_Direction {
    FACE_LEFT, FACE_RIGHT
};

enum Character {
    PLAYER,
    DEVIL
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

    protected:
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
        int m_x_pos;
        int m_y_pos;
        Facing_Direction m_facing;

    private:
        SDL_Texture* load_Texture(std::string filename);
};