#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <random>

#define MAX_TILE_TYPES 3
#define TILE_SIZE 128
#define MAP_WIDTH 20
#define MAP_HEIGHT 12
#define MAP_RENDER_WIDTH 32
#define MAP_RENDER_HEIGHT 16

typedef struct Tile {
    int type;
    int rotation;
} Tile;

class Map {
    public:
        Map();
        Map(SDL_Renderer* sdl_renderer);
        ~Map();

        void blit_Texture(SDL_Texture* texture, int x_pos, int y_pos, int rotation);
        void draw_Map();

        void update_camera_x_position(int dx);
        void update_camera_y_position(int dy);
    
    private:
        void init_Map();
        void load_Tiles();
        void load_Map();

        void generate_Floor_Plan();

        SDL_Texture* load_Texture(std::string filename);

        SDL_Texture* m_tile_textures_arr[MAX_TILE_TYPES];
        SDL_Renderer* m_renderer;
        SDL_Point m_camera;

        Tile m_map_data[MAP_RENDER_HEIGHT][MAP_RENDER_WIDTH];
};