#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#define MAX_TILE_TYPES 2
#define TILE_SIZE 64
#define MAP_WIDTH 8
#define MAP_HEIGHT 4
#define MAP_RENDER_WIDTH 20
#define MAP_RENDER_HEIGHT 12

class Map {
    public:
        Map();
        Map(SDL_Renderer* sdl_renderer);
        ~Map();
    
    private:
        void init_Map();
        void load_Tiles();
        void load_Map();
        SDL_Texture* load_Texture(std::string filename);

        SDL_Texture* m_tile_textures_arr[MAX_TILE_TYPES];
        SDL_Renderer* m_renderer;

        int m_map_data[MAP_HEIGHT][MAP_WIDTH] = {
                                                    {1,1,1,1,1,1,1,1}, 
                                                    {1,0,0,0,0,0,0,1}, 
                                                    {1,0,0,0,0,0,0,1}, 
                                                    {1,1,1,1,1,1,1,1}   };
};