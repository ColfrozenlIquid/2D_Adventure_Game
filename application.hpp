#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

enum Player_Movement_Direction {
    UP, DOWN, LEFT, RIGHT, NONE
};

class Application {
    public:
        Application();
        ~Application();

        void handle_Input();
        void prepare_Scene();
        void present_Scene();

        SDL_Renderer* get_SDL_Renderer();
        Player_Movement_Direction get_Player_Movement_Direction();

        SDL_Renderer* m_renderer;
        SDL_Window* m_window;

    private:

        void init_SDL();
        void init_SDL_Image();
        void blit_Texture(SDL_Texture* texture, int x_pos, int y_pos);
        SDL_Texture* load_Texture(std::string filename);

        void handle_Key_Up(SDL_KeyboardEvent* keyboard_event);
        void handle_Key_Down(SDL_KeyboardEvent* keyboard_event);

        Player_Movement_Direction m_player_movement_direction;
};